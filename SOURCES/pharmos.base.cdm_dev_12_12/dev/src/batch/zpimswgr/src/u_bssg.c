/*----------------------------------------------------------------*
 *      BSSichG-Artikel                                           *
 *----------------------------------------------------------------*/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include <phodate.h>
#include <libscsvoodoo.h>
#include <zartikel.h>

#include "u_bssg.h"

#include "pflegevers.h"

#define L_ARTIKEL_NR 7


static char mUser[20];

/* ---------------------------------------------------- */

/*
	Es fallen nur Artikel darunter die 
		- rezeptpflichtig 
        - taxpflichtig und 
        - mit Zuzahlung sind.		????????????????????????????????????????????????????

	Ausnahmen davon sind Artikel 
        - nicht über Grosshandel 
        - Antikozeptiva ( IMS-WG 05031 ) 
        - Negativliste 
        - Tierarzneimittel 
        - Life-Style Produkte ( werden noch definiert ) 

*/

/* --- LifeStyle -------------------------------------- */

#define MAX_LIFE 2000

static long lifestyle[MAX_LIFE + 1];

long GetLifeStyle( char *errmld )
{
	int fd;
	int i;
	long s;
	s = SqlOpenCs( &fd, "select artikel_nr from zlifestyle order by artikel_nr" );
	if ( s != 0 )
	{
		sprintf( errmld , "Fehler bei SqlOpenCs(zlifestyle) (%ld)", s);
		return s;
	}
	i = 0;
	while ( s == 0 && i < MAX_LIFE )
	{
		s = SqlFetch( fd, 1, &lifestyle[i], NULL );
		if ( s == 0 )
			i++;
	}

	SqlCloseCs( fd );

	if ( s == 0 )
	{
		sprintf( errmld , "Max. LifeStyle-Artikel = %d erreicht", i );
		return -1;
	}

	if ( s != 100 )
	{
		sprintf( errmld , "Fehler bei SqlFetch(zlifestyle) (%ld)", s);
		return s;
	}
/*	printf( "Anzahl Lifestyle: %d\n", i );  */
	lifestyle[i] = -1;
	return 0;
}

static int IsLifeStyle( long artikel_nr )
{
	int i;
	i = 0;
	while ( lifestyle[i] != -1 )
	{
		if ( artikel_nr == lifestyle[i]  ) return 1;
		i++;
	}
	return 0;
}


/* --- ZARTIKEL lesen -------------------------------------- */


static int fd_art = -1;

static void CloseZartikel( )
{
	if ( fd_art != -1 )
		SqlCloseCs( fd_art );
	fd_art = -1;
}


static long GetZartikel( long artikel_nr, struct ZARTIKEL *art, char *errmld )
{
	long s;

	if ( fd_art == -1 )
	{
		char sql[3000];
		sprintf( sql, "select %s from zartikel where artikel_nr=?",
					   PROJECTION_ZARTIKEL );
		s = SqlDeclareCsWh( &fd_art, sql, "zartikel.artikel_nr", NULL );
		if ( s != 0 )
		{
			fd_art = -2;
			sprintf( errmld , "Fehler bei SqlDeclareCs(zartikel) (%ld)", s);
			return s;
		}
	}
	else if ( fd_art == -2 )
	{
		strcpy( errmld , "Fehler bei SqlDeclareCs(zartikel) (fd_art = -2)" );
		return -1;
	}

	s = SqlReadDeclCs( fd_art, art, NULL, &artikel_nr, NULL );
	if ( s == 100 )
		return s;
	if ( s != 0 )
        sprintf( errmld , "Fehler bei SqlReadDeclCs(zartikel) (%ld)", s);
	return s;
}

/* --- ZARTIKEL schreiben -------------------------------------- */

static int  Fd_Zartikel = -1;
static long lStatus_Zartikel;

static char CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];

int GetBufferDesc_Zartikel( char * errmld )
{
   char *tabelle = "zartikel";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zartikel >= 0 ) return 0;

   memset( CmpIndikator_Zartikel, '0', POSANZ_ZARTIKEL );
   CmpIndikator_Zartikel[POSANZ_ZARTIKEL] = '\0';
   CmpIndikator_Zartikel[P_ZARTIKEL_BSSICHG] = '1';

#ifdef WP_ALTE_VERSION
   lStatus = OpenBufferDesc    ( &Fd_Zartikel, tabelle, 
                                 CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errstr );
#else
   lStatus = OpenBufferDescProj( &Fd_Zartikel, tabelle, PROJECTION_ZARTIKEL,
                                 CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errstr );
#endif

   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zartikel = -1;
     return -1;
   }
   return 0;
}


long StoreRecord_Zartikel( struct ZARTIKEL *buf_old, struct ZARTIKEL *buf_neu, char* cErrmld )
{
   long lStatus;
   char errmld[200];

   char PrimekeyCond[40];
   char format[30];
   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, buf_neu->ARTIKEL_NR );

   lStatus = FdDelayUpdateRecord( Fd_Zartikel, buf_neu, buf_old,
                                  PrimekeyCond, errmld );
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
}


/* --------------------------------------------------------------- */

static int IsBSSichG( long artikel_nr, char *wgr,
			          char *taxpfl, char *rezeptpfl, char *nichtuebergh, char *zuzahlung_ifa,
			          char *negativliste, char *tierarznei, char *nurkva )
{
	if (!( *taxpfl == '1' && *rezeptpfl == '1' && *zuzahlung_ifa >= '3' ) )
		return 0;

	/* Ausnahmen */
	if ( *nichtuebergh == '1' || *negativliste == '1' || *tierarznei == '1'  || *nurkva == '1' )
 		return 0;

	if ( IsLifeStyle( artikel_nr ) )        /* Lifestyle */
		return 0;

	if ( strcmp( wgr, "05031" ) == 0 )		/* Antikonzeptiva */
		return 0;

	if ( memcmp( wgr, "0707", 4 ) == 0 )	/* Gruppe der Impfstoffe */
		return 0;

	return 1;
}


long SetBSSichG( long artikel_nr, char *wgr, char *errmld )
{
	int  ret;
	long s;
	struct ZARTIKEL buf_old;
	struct ZARTIKEL buf_neu;

    static long datum = -1;

    if ( datum == -1 )
       datum = PhoToday();

	s = GetZartikel( artikel_nr, &buf_old, errmld );
	if ( s == 100 )
		return 0;
	if ( s != 0 )
		return s;

	ret = IsBSSichG( buf_old.ARTIKEL_NR, wgr,
		  		     buf_old.TAXPFL, buf_old.REZEPTPFL, buf_old.NICHTUEBERGH, buf_old.ZUZAHLUNG_IFA,
			         buf_old.NEGATIVLISTE, buf_old.TIERARZNEI, buf_old.NURKVA );

	buf_neu = buf_old;
	if ( ret == 0 )
		strcpy( buf_neu.BSSICHG, "0" );
	else
		strcpy( buf_neu.BSSICHG, "1" );

	if ( *buf_neu.BSSICHG == *buf_old.BSSICHG )
		return 0;

	strcpy( buf_neu.BEARBEITER, mUser );
	buf_neu.DATUM_AENDER = datum;

	return StoreRecord_Zartikel( &buf_old, &buf_neu, errmld );
}

int TestBSSichG( char *wgr )
{
	return strcmp( wgr, "05031" )   == 0 ||		/* Antikonzeptiva */
		   memcmp( wgr, "0707", 4 ) == 0;		/* Gruppe der Impfstoffe */
}

long OpenBSSichG( char *user, char *errmld )
{
	long s;
	strcpy( mUser, user );
	s = GetLifeStyle( errmld );
	if ( s == 0 )
		s = GetBufferDesc_Zartikel( errmld );
	return s;
}

void CloseBSSichG()
{
	CloseZartikel( );
}

