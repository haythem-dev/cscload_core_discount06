/* ---------------------------------------------------------------------- *
 *                         autret.c                                       *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   aut idem Artikel Retourensperre zuruechsetzen                *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  29.05.2002                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo.h>
#include <phodate.h>

#include <wpp_prot.h>
#include <wpp_dbas.h>

#include <zartikel.h>
#include <zapflege.h>

#include "autwpx.h"


#define L_ARTIKEL_NR 7

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );


/* ----------------- Usage ------------------------ */

void AutidemRetSperreUsage( char *buf )
{
strcat( buf, "3. Aut Idem Artikel Retourensperre aufheben\n"\
             "   zpautidm 3 database tage\n" \
			 "              Sperre aufheben bei Artikel mit gueltigkeitsdatum<=heute-tage\n\n" );
}

/* ----- Zartikel ------------------------- */

static int  Fd_Zartikel = -1;

static long lStatus_Zartikel;

static struct ZARTIKEL Buf_zartikel;
static struct ZARTIKEL BufOld_zartikel;
static char CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];

static int GetBufferDesc_Zartikel( char * errmld )
{
    char *tabelle = "zartikel";
    long lStatus;
    char errstr[80];

    strcpy( errmld, "");
    if ( Fd_Zartikel >= 0 ) return 0;

    memset( CmpIndikator_Zartikel, '0', POSANZ_ZARTIKEL );
    CmpIndikator_Zartikel[POSANZ_ZARTIKEL] = '\0';
/*
    CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_AENDER]   = '1';
    CmpIndikator_Zartikel[P_ZARTIKEL_BEARBEITER]     = '1';
*/
    CmpIndikator_Zartikel[P_ZARTIKEL_RETOURENSPERRE] = '1';

/*  lStatus = OpenBufferDesc( &Fd_Zartikel, tabelle,
                               CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errstr ); */
								/* !!!!!!!bis 21.12.2000    V_PROTOKOL  */

	/* direkter Aufruf von OpenBufferDescProj, um Select * beim Read zu vermeiden */
    lStatus = OpenBufferDescProj( &Fd_Zartikel, tabelle, PROJECTION_ZARTIKEL,
                               CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errstr ); 

    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_Zartikel = -1;
      return -1;
    }
    return 0;
}


static char PrimekeyCond_Zartikel[50];

static long ReadRecord_Zartikel( long artikel_nr, char* cErrmld )
{
   long lStatus;
   char format[50];

   Buf_zartikel.ARTIKEL_NR = artikel_nr;

   strcpy( cErrmld, "" );

   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond_Zartikel, format, Buf_zartikel.ARTIKEL_NR );

   lStatus = FdReadRecord( Fd_Zartikel, PrimekeyCond_Zartikel,
                           &Buf_zartikel, cErrmld );

   if ( lStatus != 0  ) return lStatus;

   return 0;

}

static long StoreRecord_Zartikel( long tagesdatum, char *user,
								  char *retourensperre,
                                  char* cErrmld )
{
   long lStatus;

   BufOld_zartikel = Buf_zartikel;  /* gelesenen Satz sichern */

   Buf_zartikel.DATUM_AENDER = tagesdatum;
   strcpy( Buf_zartikel.BEARBEITER, user );
   *Buf_zartikel.RETOURENSPERRE = *retourensperre;

   lStatus = FdDelayUpdateRecord( Fd_Zartikel, &Buf_zartikel,
                                  &BufOld_zartikel,
                                  PrimekeyCond_Zartikel, cErrmld );
   return lStatus;
}



static long InitAll( char *errmld )
{
   if ( GetBufferDesc_Zartikel( errmld ) != 0 ) return -1;
   if ( GetBufferDesc_Zapflege( errmld ) != 0 ) return -1;
   return 0;
}


static void FreeAll()
{
   if ( Fd_Zartikel >= 0 )
      CloseOneBufferDesc( Fd_Zartikel );
   Fd_Zartikel = -1;

   Close_Zapflege();

}




static long Entsperre( int artikel_nr, long tagesdatum, char *user, long *anz2, char *errmld )
{
	long s;
	
	s = ReadRecord_Zartikel( artikel_nr, errmld );
	if ( s == 0 )
	{
		if ( Buf_zartikel.DATUM_AH == 0 ) 
		{
			s = StoreRecord_Zartikel( tagesdatum, user, "0", errmld );
			if ( s == 0 )
				s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
			if ( s == 0 )
				s = FdTransactWithoutWork( errmld );
			if ( s == 0 )
				(*anz2)++;
		}
	}
	else if ( s == 100 )
		s = 0;
	return s;
}

static long ZautidemsperreLoop( long tagesdatum, long datum, char *user, char *buf )
{
	int  fd;
	long s;
	long anz1;
	long anz2;
	long artikel_nr;
	char sql[100];

	sprintf( sql, "select artikel_nr from zautidemsperre where datumgueltigab<=%ld for update",
			      datum );
	s = SqlOpenCsWh( &fd, sql );
	if ( s != 0 )
    {
		strcpy( buf, "Open zautidemsperre: " );
		strcat( buf, DynErrmld() );
		return s;
    }

	sprintf( sql, "delete from zautidemsperre where current of %s", 
		          SqlGetCursor( fd ) );

	anz1 = 0;
	anz2 = 0;
	do
	{
		s = SqlBeginWork();
		if ( s == 0 )
		{
			s = SqlFetch( fd, 1, &artikel_nr, NULL );
			if ( s != 0 )
			{
				if ( s == 100 )
				{
					if ( anz1 == 0 )
						strcpy( buf, "zautidemsperre: kein Artikel im Zeitraum vorhanden" );
					else
						sprintf( buf, "%ld Artikel untersucht, %ld Artikel entsperrt", 
						         anz1, anz2 );
				}
				else
				{
					strcpy( buf, "Fetch zautidemsperre: " );
					strcat( buf, DynErrmld() );
				}
			}
			else
			{
				anz1++;
				s = SqlExecuteImm( sql );
				if ( s == 0 )
					s = Entsperre( artikel_nr, tagesdatum, user, &anz2, buf );
				else
				{
					strcpy( buf, "zautidemsperre: " );
					strcat( buf, DynErrmld() );
				}
			}

			if ( s == 0 )
				SqlCommitWork();
			else
				SqlRollbackWork();
		}
		else
		{
			strcpy( buf, "zautidemsperre: " );
			strcat( buf, DynErrmld() );
		}

	} while ( s == 0 );

	if ( s != 100 )
	{
		if ( anz2 > 0 )
		{
			char errmld[100];
			sprintf( errmld, "\n(%ld Artikel untersucht, %ld Artikel entsperrt)", 
			         anz1, anz2 );
			strcat( buf, errmld );
		}
	}
	else
		s = 0;


	SqlCloseCs( fd );
	return s;
}


long AutidemRetSperre( char *db, char *ctage, char *user, char *buf )
{
   long s;
   long datum;
   long tage;
   long tagesdatum;

   tage = atol( ctage );

   tagesdatum = PhoToday();
   datum = AddDayToPhoDate( tagesdatum , -tage );

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
        s = OpenPflege( user, buf );
		if ( s == 0 )
		{
			char errmld[10];
			s = InitAll( buf );
			if ( s == 0 )
		         s = ZautidemsperreLoop( tagesdatum, datum, user,  buf );
			FreeAll();
			ClosePflege( errmld );
		}
       CloseBase( );
   }
   return s;
}

