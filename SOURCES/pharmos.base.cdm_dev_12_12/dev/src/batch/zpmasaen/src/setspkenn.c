/* ---------------------------------------------------------------------- *
 *                         Setspkenn.c                                    *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Loeschkennzeichen Setzen                                     *
 * ---------------------------------------------------------------------- *
 * Autor  :  Raab                                                         *
 * Anfang :  30.08.2004                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hdatum/phodate.h"
#include "libscsvoodoo/libscsvoodoo.h"

#include  "wdbups/wpp_prot.h"
#include  "wdbups/wpp_dbas.h"

#include <zartikel.h>
#include <zapflege.h>

#define L_ARTIKEL_NR 7

/* ----------------- wie loeschen --------------------- */

#define LOESCH_MIT_PROTOKOL

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void SetSpekennUsage( char *buf )
{
   strcat( buf, "- zpmasaen 7 Database USER Datum\n" );
   strcat( buf, "  Sperrkennzeichen setzen fuer Artikel mit\n" );
   strcat( buf, "  DATUM_AH < Datum\n" );
}

void BlockExpiredPseudoArticlesLoeUsage( char *buf )
{
   strcat( buf, "- zpmasaen 12 Database USER Datum\n" );
   strcat( buf, "  Sperrkennzeichen setzen fuer Artikel mit\n" );
   strcat( buf, "  ccpvalidityperiod.dateto < Datum\n" );
}

/* -----  Zapflege  ------------------------- */

static int  Fd_Zapflege = -1;

static struct ZAPFLEGE Buf_zapflege;

static int GetBufferDesc_Zapflege( char * errmld )
{
   char *tabelle = "zapflege";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zapflege >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zapflege, tabelle, PROJECTION_ZAPFLEGE,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zapflege = -1;
     return -1;
   }

   return 0;
}

static long StoreRecord_Zapflege( long artikel_nr, long datum, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[50];

   Buf_zapflege.ARTIKEL_NR = artikel_nr;
   Buf_zapflege.DATUM      = datum;

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and DATUM=%ld",
                          Buf_zapflege.ARTIKEL_NR,
                          Buf_zapflege.DATUM );

   lStatus = FdReadRecord( Fd_Zapflege, PrimekeyCond,
                           &Buf_zapflege, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

   if ( lStatus == 100 )
   {
      Buf_zapflege.ARTIKEL_NR = artikel_nr;
      Buf_zapflege.DATUM      = datum;
      lStatus = FdDelayInsertRecord( Fd_Zapflege, &Buf_zapflege,
                                     PrimekeyCond, cErrmld);
   }

   return lStatus;
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
    CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_AENDER] = '1';
    CmpIndikator_Zartikel[P_ZARTIKEL_BEARBEITER]   = '1';
    CmpIndikator_Zartikel[P_ZARTIKEL_ARTIKEL_GELOESCHT] = '1';

    lStatus = OpenBufferDescProj( &Fd_Zartikel, tabelle, PROJECTION_ZARTIKEL,
                                  CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errstr );
                                /* !!!!!!!bis 21.12.2000    V_PROTOKOL  */
    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_Zartikel = -1;
      return -1;
    }

    return 0;
}

static long StoreRecord_Zartikel( long artikel_nr, long datum, char *user, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[50];
   char format[50];

   Buf_zartikel.ARTIKEL_NR = artikel_nr;

   strcpy( cErrmld, "" );

   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartikel.ARTIKEL_NR );

/* sprintf( PrimekeyCond, "ARTIKEL_NR=%ld", Buf_zartikel.ARTIKEL_NR ); */

   lStatus = FdReadRecord( Fd_Zartikel, PrimekeyCond,
                           &Buf_zartikel, cErrmld );

   if ( lStatus != 0  ) return lStatus;

   BufOld_zartikel = Buf_zartikel;  /* gelesenen Satz sichern */

   Buf_zartikel.DATUM_AENDER = datum;
   strcpy( Buf_zartikel.BEARBEITER, user );
   *Buf_zartikel.ARTIKEL_GESPERRT = '1';

   lStatus = FdDelayUpdateRecord( Fd_Zartikel, &Buf_zartikel,
                                  &BufOld_zartikel,
                                  PrimekeyCond, cErrmld );
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

   if ( Fd_Zapflege >= 0 )
      CloseOneBufferDesc( Fd_Zapflege );
   Fd_Zapflege = -1;
}

static long DoIt( char *user, long artikel_nr, long tagesdatum,
                  char *errmld )
{
   long s;

   s = StoreRecord_Zartikel( artikel_nr, tagesdatum, user, errmld );

   if ( s == 0 )  
      s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
  
   if ( s == 0 )
      s = FdTransact( errmld );

   return s;
}

long CheckLagerorte ( long artikel_nr )
{
   long s;
   char buf[500];
   double dCount;

   sprintf( buf,
/*          "select count(*) from artikelf where ARTIKEL_NR=%ld and lagerfachnr != '99999999'", */
            "select count(*) from artikelf where ARTIKEL_NR=%ld and lagerfachnr != (select pseudolagerort from rfiliale where rfiliale.filialnr = artikelf.filialnr)", 
            artikel_nr );

   s = SqlRead( buf, &dCount, NULL ); 

   if ( s != 0 )
   {
		return -1;
   }
   else
   {
		return (int)dCount;
   }
}

static long SetSpekenn( char *user, long datum, char *buf, int isMode12 )
{
   long tagesdatum, grenzdatum;

   long artikel_nr;
   long s;
   long anz;
   int  fd;
   char z_buf[51];

   tagesdatum = GetPhoDate();

   if (isMode12 == 0)
   {
		// keine Artikel mit Änderung in den letzten 6 Monaten
		if (tagesdatum%10000 > 700)
		{
			grenzdatum = tagesdatum - 600;
		}
		else
		{
			grenzdatum = tagesdatum - 9400;
		}

		sprintf( buf,
					"select ARTIKEL_NR from ZARTIKEL where " \
					"artikel_gesperrt = '0' and datum_aender < %ld and " \
					"datum_ah < %ld and datum_ah > 0",grenzdatum, datum);
   }
   else
   {
		sprintf( buf,
					"select ARTIKEL_NR from ZARTIKEL, ccpvalidityperiod where artikel_nr = article_no_pack and " \
					"artikel_gesperrt != '1' and compack_type in (3,4) and dateto <= %ld " \
					"and article_no_pack not in (select articleno from cdiscount where dateto > %ld)", datum, datum);
   }

   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "ZARTIKEL\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd, 1, &artikel_nr, NULL );
   if ( s == 100 )
   {
     strcpy( buf, "Keine entsprechenden Artikel vorhanden" );
     return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "ZARTIKEL\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = InitAll( buf );
   if ( s != 0 )
   {
      FreeAll( );
      SqlCloseCs( fd );
      return s;
   }

   anz = 0;
   while ( s == 0 )
   {
		// erst prüfen, ob Artikel nicht noch irgendwo gültige Lagerorte hat
	    if (isMode12 == 1 || CheckLagerorte(artikel_nr) <= 0)
	    {
			s = DoIt( user, artikel_nr, tagesdatum, buf );

			if ( s == 0 )
			{
				anz++;
			}
	    }

		if ( s == 0 )
		{
			s = SqlFetch( fd, 1, &artikel_nr, NULL );
			if ( s != 0 )
			{
			strcpy( buf, "ZARTIKEL\n" );
			strcat( buf, DynErrmld() );
			}
		}
   }

   FreeAll( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld Sperrkennzeichen gesetzt", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Aktion erfolgreich" );
   }

   strcat( buf, z_buf );
   return s;
}

long SetSpekennLoop ( char *db, char *user, char *datumstr, char *buf )
{
   long s;
   long datum;
   char errmld[10];

   if ( ConvToPhoDate ( datumstr, &datum, "tt.mm.jjjj" ) != 1 )
   {
       strcpy( buf, "Datum in der Form tt.mm.jjjj" );
       return 1;
   }

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
        s = SetSpekenn( user, datum, buf, 0 );
        ClosePflege( errmld );
     }
     CloseBase( );
   }

   return s;
}

long BlockExpiredPseudoArticles ( char *db, char *user, char *datumstr, char *buf )
{
   long s;
   long datum;
   char errmld[10];

   if ( ConvToPhoDate ( datumstr, &datum, "tt.mm.jjjj" ) != 1 )
   {
       strcpy( buf, "Datum in der Form tt.mm.jjjj" );
       return 1;
   }

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
        s = SetSpekenn( user, datum, buf, 1 );
        ClosePflege( errmld );
     }
     CloseBase( );
   }

   return s;
}


