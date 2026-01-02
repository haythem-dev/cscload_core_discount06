/* ---------------------------------------------------------------------- *
 *                         autiart.c                                      *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   aut idem Artikel markieren                                   *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  29.05.2002                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>/* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo.h>
#include <phodate.h>

#include <wpp_prot.h>
#include <wpp_dbas.h>

#include <zartikel.h>
#include <zapflege.h>

#include "asciidat.h"


/* #define IS_TEST */

/* #define IS_UPD_TEST */
#define L_ARTIKEL_NR 7

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );


/* ----------------- Usage ------------------------ */

void InitAutidemUsage( char *buf )
{
strcat( buf, "0. AutIdem Artikel aus PZN-Datei markieren\n"\
	         "       mit protokol/verteilen\n" \
             "   zpautidm 0 database user datei [number]\n\n" );
strcat( buf, "1. AutIdem Artikel aus PZN-Datei mit kennzeichen markieren\n"\
	         "       mit protokol/verteilen\n" \
             "   zpautidm 1 database kennzeichen user datei [number]\n" \
			 "              kennzeichen = 0 | 1 | 2 | 3\n\n" );
strcat( buf, "2. AutIdem Artikel aus PZN-Datei mit kennzeichen markieren\n"\
	         "       ohne protokol/verteilen\n" \
             "   zpautidm 2 database kennzeichen user datei [number]\n" \
			 "              kennzeichen = 0 | 1 | 2 | 3\n\n" );
}


/*
long GetArtikelNr( int fd, long *pzn, char *errmld )
{
	char buffer [100];
	int  status;
    status = AscRead( buffer, fd );
	printf( "%d  %ld\n", status, *pzn );
    if ( status == 0 )
    {
        if ( strlen( buffer ) > 0 )
        {
			*pzn = atol( buffer );
			return 0;
		}
		strcpy( errmld, "Satz nicht vollstaendig gelesen" );
		return -1;
	}
	else
		return 1;
}
*/

/* ------------------------------------------------------------------- */
long sel_ArtNoByCode	( const long code )
{
    long artNo;
	char sql[150];

	sprintf( sql, "SELECT articleno FROM carticlecodes WHERE article_code ='%ld' "
					"AND code_type IN (SELECT code_type FROM ccodetypes WHERE artnr_substitute = 1)", code);
  
	if ( SqlRead( sql, &artNo, NULL ) != 0 )
	{
		artNo = -1;
	}

	return artNo;
}

long GetArtikelNr( int fd, long *pzn, char *errmld )
{
	char buffer [100];
	int  status;
    status = AscRead( buffer, fd );

/*	printf( "status=%d  %s\n", status, buffer ); */

    if ( strlen( buffer ) > 0 )
		*pzn = sel_ArtNoByCode(atol( buffer )); //TH-PZN8
	else
		*pzn = 0;

	if ( status == 0 && pzn >= 0)
		return 0;
	else
		return 1;
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
    CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_AENDER] = '1';
    CmpIndikator_Zartikel[P_ZARTIKEL_BEARBEITER]   = '1';
*/
    CmpIndikator_Zartikel[P_ZARTIKEL_PREISSENKUNG] = '1';

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

static long StoreRecord_Zartikel( long datum, char *user,
								  char *autidem,
                                  char* cErrmld )
{
   long lStatus;

   BufOld_zartikel = Buf_zartikel;  /* gelesenen Satz sichern */

   Buf_zartikel.DATUM_AENDER = datum;
   strcpy( Buf_zartikel.BEARBEITER, user );
   *Buf_zartikel.PREISSENKUNG = *autidem;

   lStatus = FdDelayUpdateRecord( Fd_Zartikel, &Buf_zartikel,
                                  &BufOld_zartikel,
                                  PrimekeyCond_Zartikel, cErrmld );
   return lStatus;
}


static long ReadAndStoreRecord_Zartikel( long artikel_nr, long datum, char *user,
								         char *autidem,
                                         char* cErrmld )
{
   long lStatus;

   lStatus = ReadRecord_Zartikel( artikel_nr, cErrmld );

   if ( lStatus != 0  ) return lStatus;

#ifdef IS_TEST
   return 0;
#endif

   return StoreRecord_Zartikel( datum, user, autidem, cErrmld );

}



static long InitAll( char *errmld )
{
   if ( GetBufferDesc_Zartikel( errmld ) != 0 ) return -1;
#ifdef VON_STREBER_ERLAUBT
   if ( GetBufferDesc_Zapflege( errmld ) != 0 ) return -1;
#endif
   return 0;
}


static void FreeAll()
{
   if ( Fd_Zartikel >= 0 )
      CloseOneBufferDesc( Fd_Zartikel );
   Fd_Zartikel = -1;

#ifdef VON_STREBER_ERLAUBT
  Close_Zapflege();
#endif

}


static long getcount( char *ccount )
{
	int i;
	i = 0;
	while ( i < ( int) strlen( ccount ) )
	{
		if ( !isdigit( ccount[i] ) ) return -1;
		i++;
	}
	return atol( ccount );
}




static long DoIt( char *user, long artikel_nr, long tagesdatum, char *autidem,
                  char *errmld )
{
   long s;

   s = ReadAndStoreRecord_Zartikel( artikel_nr, tagesdatum, user, autidem, errmld );

   if ( s == 100 )
		return 12345;   

#ifdef IS_TEST
   return 0;
#endif

#ifdef VON_STREBER_ERLAUBT
   if ( s == 0 )  
      s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
#endif
   
   if ( s == 0 )
      s = FdTransact( errmld );

   return s;
}


static long AutidemArtikel( char *autidem, char *user, char *cDatei, long count, long proz, char *buf )
{
   long tagesdatum;

   int  fd;
   int  status;

   long artikel_nr;
 
   long s;
   long s1;
   long anz;
   long upd_anz;

   char z_buf[251];

   tagesdatum = GetPhoDate();

   status = AscOpenRd( cDatei, &fd, 1024, &AscNormFkt );
   if ( status != RDA_OK )
   {
      sprintf( buf, "Fehler %d beim Oeffnen der Datei\n%s",
                     status, cDatei );
     return 1;
   }

   s = InitAll( buf );
   if ( s != 0 )
   {
      FreeAll( );
      AscClose( fd);
      return s;
   }

   upd_anz = 0;
   anz = 0;
   s1 = 0;

   while ( s == 0 && s1 == 0 && ( count == 0 || anz < count ) )
   {
	  s = GetArtikelNr( fd, &artikel_nr, buf );
	  if ( artikel_nr > 0 )
	  {
		anz++;
		if ( proz > 0 && anz%proz == 0 ) 
		{
			char ausgabe[30];
			sprintf( ausgabe, "%6ld  %7.ld", anz, artikel_nr );
			printf( "%s\n", ausgabe );
		}

#ifndef IS_UPD_TEST
		s1 = DoIt( user, artikel_nr, tagesdatum, autidem, buf );
		if ( s1 == 12345 )
			s1 = 0;
		else if ( s1 == 0 )
			upd_anz++;
#endif

	  }
   }

   FreeAll( );

   AscClose( fd);

   sprintf( z_buf, "\nEs wurden %ld/%ld Artikel gelesen/AutIdem-gekennzeichnet", anz, upd_anz );

   if ( s == 100 || anz == count )
   {
      s = 0;
      strcpy( buf, "Aktion erfolgreich" );
   }
   strcat( buf, z_buf );
   return s;
}


long InitAutidemArtikel( char *db, char *cmode, char *user, char *cdatei, char *ccount, char *buf )
{
   long s;
   long count;
   long proz;

   char autidem[2];

   char errmld[10];

   if ( *cmode == '0' || *cmode == '1' || *cmode == '2' || *cmode == '3' )
   {
	   strcpy( autidem, " " );
	   *autidem = *cmode;
   }
   else
   {
	   strcpy( buf, "mode = 0 | 1 | 2 | 3" );
	   return -1;
   }



   if ( ccount == NULL )
   {
	   count = 0;
	   proz  = -1;
   }
   else
   {
	   count = getcount( ccount );
	   if ( count < 0 )
	   {
		   strcpy( buf, "count >= 0" );
		   return -1;
	   }
	   if ( count == 0 )
		   proz = 1;
	   else
	   {
		   proz = count/10;
		   if ( proz == 0 )
		      proz = 1;
	   }
   }

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
         s = AutidemArtikel( autidem, user, cdatei, count, proz, buf );
         ClosePflege( errmld );
     }
     CloseBase( );
   }
   return s;
}


/* Ohne Protokoll / Verteil */

static int m_fd = -1;
static int m_fdupd = -1;


static void CloseAll()
{
	if ( m_fd != -1 )
		SqlCloseCs( m_fd );
	if ( m_fdupd != -1 )
		SqlFreePrepare( m_fdupd );
}

static long DoItOhne( char *user, long artikel_nr, long tagesdatum, char *autidem,
                      char *buf )
{
	long s;

	long datum_aender;
	char bearbeiter[10];
	char preissenkung[10];
	char cmd[200];

	if ( m_fd == -1 )
	{
		char *sql;

		sql = "select datum_aender,bearbeiter,preissenkung from zartikel where artikel_nr=? for update";
		s = SqlDeclareCsWh ( &m_fd, sql, "zartikel.artikel_nr", NULL );
		if ( s != 0 )
		{
			strcpy( buf, "SqlDeclareCsWh: ");
			strcat( buf, DynErrmld() );
			return s;
		}
	}
	s = SqlOpenDeclCs( m_fd, &artikel_nr, NULL );
	if ( s != 0 )
	{
		strcpy( buf, "SqlOpenDeclCs: ");
		strcat( buf, DynErrmld() );
		return s;
	}
	s = SqlFetch( m_fd, 1, &datum_aender, bearbeiter, preissenkung, NULL );
    if ( s == 100 )
		return 12345; 
	if ( s != 0 )
	{
		strcpy( buf, "SqlOpenDeclCs: ");
		strcat( buf, DynErrmld() );
		return s;
	}
	if ( strcmp( preissenkung, autidem ) == 0 )
		return 0;


	sprintf ( cmd, "update zartikel set datum_aender=%ld,bearbeiter='%s',preissenkung='%s' "\
		           "where artikel_nr=%ld",
				   tagesdatum, user, autidem, artikel_nr );

/*
	s = SqlExecuteImm( cmd );

	if ( s != 0 )
	{
		strcpy( buf, "SqlExecuteImm: ");
		strcat( buf, DynErrmld() );
	}
*/
	if ( m_fdupd == -1 )
	{
		sprintf( cmd, "update zartikel set datum_aender=?,bearbeiter=?,preissenkung=? "\
		              "where artikel_nr=?" );
		s = SqlPrepareStmnt ( &m_fdupd, cmd, "zartikel.datum_aender","zartikel.bearbeiter",
		                                     "zartikel.preissenkung", "zartikel.artikel_nr", NULL );
		if ( s != 0 )
		{
			strcpy( buf, "SqlPrepareUpdate: ");
			strcat( buf, DynErrmld() );
			return s;
		}				           
	}

	s = SqlExecutePrepare( m_fdupd, &tagesdatum, user, autidem, &artikel_nr, NULL );

	if ( s != 0 )
	{
		strcpy( buf, "SqlExecutePrepare: ");
		strcat( buf, DynErrmld() );
	}

	return s;
}

static long AutidemArtikelOhne( char *autidem, char *user, char *cDatei, long count, long proz, char *buf )
{
   long tagesdatum;

   int  fd;
   int  status;

   long artikel_nr;
 
   long s;
   long s1;
   long anz;
   long upd_anz;

   char z_buf[251];


   tagesdatum = GetPhoDate();

   status = AscOpenRd( cDatei, &fd, 1024, &AscNormFkt );
   if ( status != RDA_OK )
   {
      sprintf( buf, "Fehler %d beim Oeffnen der Datei\n%s",
                    status, cDatei );
     return 1;
   }

   s  = 0;
   s1 = 0;
   upd_anz = 0;
   anz = 0;

   while ( s == 0 && s1 == 0 && ( count == 0 || anz < count ) )

   {
	  s = GetArtikelNr( fd, &artikel_nr, buf );
	  if ( artikel_nr > 0 )
	  {
		anz++;
		if ( proz > 0 && anz%proz == 0 ) 
		{
			char ausgabe[30];
			sprintf( ausgabe, "%6ld  %7.ld", anz, artikel_nr );
			printf( "%s\n", ausgabe );
		}

#ifndef IS_UPD_TEST
		s1 = DoItOhne( user, artikel_nr, tagesdatum, autidem, buf );
		if ( s1 == 12345 )
			s1 = 0;
		else if ( s1 == 0 )
			upd_anz++;
#endif

	  }
 
   }

	CloseAll();

   AscClose( fd);

   sprintf( z_buf, "\nEs wurden %ld/%ld Artikel gelesen/AutIdem-gekennzeichnet", anz, upd_anz );

   if ( s == 100 || anz == count )
   {
      s = 0;
      strcpy( buf, "Aktion erfolgreich" );
   }
   strcat( buf, z_buf );
   return s;
}

long InitAutidemArtikelOhne( char *db, char *cmode, char *user, char *cdatei, char *ccount, char *buf )
{
   long s;
   long count;
   long proz;

   char autidem[2];

   if ( *cmode == '0' || *cmode == '1' || *cmode == '2' || *cmode == '3' )
   {
	   strcpy( autidem, " " );
	   *autidem = *cmode;
   }
   else
   {
	   strcpy( buf, "mode = 0 | 1 | 2 | 3" );
	   return -1;
   }



   if ( ccount == NULL )
   {
	   count = 0;
	   proz  = -1;
   }
   else
   {
	   count = getcount( ccount );
	   if ( count < 0 )
	   {
		   strcpy( buf, "count >= 0" );
		   return -1;
	   }
	   if ( count == 0 )
		   proz = 1;
	   else
	   {
		   proz = count/10;
		   if ( proz == 0 )
		      proz = 1;
	   }
   }

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
       s = AutidemArtikelOhne( autidem, user, cdatei, count, proz, buf );
       CloseBase( );
   }
   return s;
}




/* -------------------------------------------------------------------------- */
/* --- aktuell im Einsatz ---------------------------- */

/*
PZNs querlesen mit zartikel 
> wenn im zartikel Feld Preissenkung Wert > 0 (= Wert 1,2 oder 3) 
     > dann keine weitere Aktionen (Werte im Feld Preissenkung bleiben erhalten) 
> wenn im zartikel Feld Preissenkung Wert = 0 
     > beim Artikel Hersteller-Nummer ermitteln und im herstel (Hersteller-Stamm) 
     > Feld herstell_verguetet querlesen       
        > Feld herstell_verguetet (herstel)     Feld preissenkung (zartikel) 
             0 (Standard)    erzeugt für die PZN     3 (Kennz. zum ....)*** 
             J (Ja)          erzeugt für die PZN     2 (mit Vergütung) 
             N (nein)        erzeugt für die PZN     3 (Kennz. zum ....)*** 
*/



static int her_fd = -1;

static long ReadHerstel( long hersteller_nr, char *herstell_verguetet, char *errmld )
{
	long s;

	if ( her_fd == -1 )
	{
		s = SqlDeclareCs( &her_fd, 
		                  "select herstell_verguetet from herstel where hersteller_nr=?",
						  "herstel.hersteller_nr", NULL );
		if ( s != 0 )
		{
			sprintf( errmld, "ReadHerstel\n%s", DynErrmld() );
			return s;
		}
	}
	s = SqlReadDeclCs( her_fd, herstell_verguetet, NULL, &hersteller_nr, NULL );
	if (!( s == 0 || s == 100 ) )
		sprintf( errmld, "ReadHerstel\n%s", DynErrmld() );
	return s;
}

static void CloseHerstel()
{
	if ( her_fd != -1 )
		SqlCloseCs( her_fd );
}


static long DoItSpez( char *user, long artikel_nr, long tagesdatum, 
                      char *errmld )
{
	long s;
	char autidem[2];
	char herstell_verguetet[10];

	s = ReadRecord_Zartikel( artikel_nr, errmld );

	if ( s == 100 )
	{
		strcpy( errmld, "" );
		return 12345;   
	}

	if ( *Buf_zartikel.PREISSENKUNG != '0' )
		return 12345;   

	if ( Buf_zartikel.HERSTELLER_NR == 0 )
		return 12345;   

	s = ReadHerstel( Buf_zartikel.HERSTELLER_NR, herstell_verguetet, errmld );
	if ( s == 100 )
		return 12345;   
	if ( s != 0 )
		return s;

	if ( *herstell_verguetet == 'J' )
		strcpy( autidem, "2" );
	else
		strcpy( autidem, "3" );
	
#ifdef IS_TEST
   return 0;
#endif

	s = StoreRecord_Zartikel( tagesdatum, user, autidem, errmld );

#ifdef VON_STREBER_ERLAUBT
   if ( s == 0 )  
      s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
#endif
   
   if ( s == 0 )
      s = FdTransact( errmld );

   return s;
}


static long InsAutidemArtikel( char *user, char *cDatei, long count, long proz, char *buf )
{
   long tagesdatum;

   int  fd;
   int  status;

   long artikel_nr;
 
   long s;
   long s1;
   long anz;
   long upd_anz;

   char z_buf[251];

   strcpy( buf, "" );

   tagesdatum = GetPhoDate();

   status = AscOpenRd( cDatei, &fd, 1024, &AscNormFkt );
   if ( status != RDA_OK )
   {
      sprintf( buf, "Fehler %d beim Oeffnen der Datei\n%s",
                     status, cDatei );
     return 1;
   }

   s = InitAll( buf );
   if ( s != 0 )
   {
      FreeAll( );
      AscClose( fd);
      return s;
   }

   upd_anz = 0;
   anz = 0;
   s1  = 0;

   while ( s == 0 && s1 == 0 && ( count == 0 || anz < count ) )
   {
	  s = GetArtikelNr( fd, &artikel_nr, buf );
	  if ( artikel_nr > 0 )
	  {
		anz++;
 		if ( proz > 0 && anz%proz == 0 ) 
		{
			char ausgabe[30];
			sprintf( ausgabe, "%6ld  %8.ld", anz, artikel_nr );
			printf( "%s\n", ausgabe );
		}

#ifndef IS_UPD_TEST
		s1 = DoItSpez( user, artikel_nr, tagesdatum, buf );
		if ( s1 == 12345 )
			s1 = 0;
		else if ( s1 == 0 )
			upd_anz++;
#endif

	  }

   }

   CloseHerstel();
   FreeAll( );

   AscClose( fd);

   sprintf( z_buf, "\nEs wurden %ld/%ld Artikel gelesen/AutIdem-gekennzeichnet", anz, upd_anz );

/*
   if ( s == 100 || anz == count )
   {
      s = 0;
      strcpy( buf, "Aktion erfolgreich" );
   }
*/

   strcat( buf, z_buf );
   return s;
}


long SetAutidemArtikel( char *db, char *user, char *cdatei, char *ccount, char *buf )
{
   long s;
   long count;
   long proz;
   char errmld[10];

   if ( ccount == NULL )
   {
	   count = 0;
	   proz  = -1;
   }
   else
   {
	   count = getcount( ccount );
	   if ( count < 0 )
	   {
		   strcpy( buf, "count >= 0" );
		   return -1;
	   }
	   if ( count == 0 )
		   proz = 1;
	   else
	   {
		   proz = count/10;
		   if ( proz == 0 )
		      proz = 1;
	   }
   }

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
         s = InsAutidemArtikel( user, cdatei, count, proz, buf );
         ClosePflege( errmld );
     }
     CloseBase( );
   }
   return s;
}


