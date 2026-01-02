/*----------------------------------------------------------------*
 *      BSSichG-Artikel                                           *
 *----------------------------------------------------------------*/
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include <libscsvoodoo.h>
#include <zartikel.h>

#include "bssg.h"


/*
	Es fallen nur Artikel darunter die 
		- rezeptpflichtig 
        - taxpflichtig und 
        - mit Zuzahlung sind.		????????????????????????????????????????????????????

	Ausnahmen davon sind Artikel 
        - nicht über Grosshandel 
        - Antikozeptiva ( IMS-WG 05031 ) 
        - Negativliste  ( ja oder eingeschraenkt )
        - Tierarzneimittel 
        - Life-Style Produkte ( werden noch definiert ) 

    Neue Ausnahmen seit 02.04.2003 
        - Medizinprodukt = ja
	    - Arzneimittel = nein
		- Rezepturarzneimittel = ja
		- Kontrazeptivum = ja (A02KONTRAZ = 01)
		- Impfstoff = ja


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


/* --- ZARTWG -------------------------------------- */


static int fd_wgr = -1;

void CloseImsWgr( )
{
	if ( fd_wgr != -1 )
		SqlCloseCs( fd_wgr );
	fd_wgr = -1;
}


static long GetImsWgr( long artikel_nr, char *wgr, char *errmld )
{
	long s;

	if ( fd_wgr == -1 )
	{
		char *sql;
		sql = "select warengruppe from zartwg where artikel_nr=? and art='1'";
		s = SqlDeclareCsWh( &fd_wgr, sql, "zartwg.artikel_nr", NULL );
		if ( s != 0 )
		{
			fd_wgr = -2;
			sprintf( errmld , "Fehler bei SqlDeclareCs(zartwg) (%ld)", s);
			return s;
		}
	}
	else if ( fd_wgr == -2 )
		return -1;

	s = SqlReadDeclCs( fd_wgr, wgr, NULL, &artikel_nr, NULL );
	if ( s == 100 )
		return s;
	if ( s != 0 )
        sprintf( errmld , "Fehler bei SqlReadDeclCs(zartwg) (%ld)", s);
	return s;
}




/* wgr = "" : wgr lesen nicht noetig bei Neuaufnahme */
/* wgr = "r": wgr lesen */
/* sonst:     wgr bereits gelesen */

int IsBSSichG( long artikel_nr, char *wgr,
			   char *taxpfl, char *rezeptpfl, char *nichtuebergh, char *zuzahlung_ifa,
			   char *negativliste, char *tierarznei, char *nurkva, 
			   char *medizinprodukt, char *arzneimittel, char *rezepturarznei,
			   char *kontrazeptivum, char *impfstoff,
			   char *errmld )
{
	if (!( *taxpfl == '1' && *rezeptpfl == '1' && *zuzahlung_ifa >= '3' ) )
		return 0;

	/* Ausnahmen */
	if ( *nichtuebergh == '1' || *negativliste != '0' || *tierarznei == '1'  || *nurkva == '1' )
 		return 0;


	/* Ausnahmen in Verbindung mit den neuen IFA-Feldern 11.04.2003 */
	if ( *medizinprodukt == '1' || *arzneimittel   == '0' ||
		 *rezepturarznei == '1' || *kontrazeptivum == '1' || *impfstoff == '1' )
		 return 0;



	if ( IsLifeStyle( artikel_nr ) )        /* Lifestyle */
		return 0;
		
	if ( *wgr == '\0' )   /* Neuaufnahme */
		return 1;

	if ( *wgr == 'r' )    /* muss gelesen werden */
	{
		long s;
		s = GetImsWgr( artikel_nr, wgr, errmld );
		if ( s == 100 )
			return 1;
		else if ( s != 0 )
			return -1;
	}

	if ( strcmp( wgr, "05031" ) == 0 )		/* Antikonzeptiva */
		return 0;

	if ( memcmp( wgr, "0707", 4 ) == 0 )	/* Gruppe der Impfstoffe */
		return 0;

	return 1;
}


long SetBSSichG( struct ZARTIKEL *z, int IsArtikelVorhanden, char *errmld )
{
	int ret;
	char wgr[10];
	if ( IsArtikelVorhanden )
		strcpy( wgr, "r" );
	else
		strcpy( wgr, "" );

	ret = IsBSSichG( z->ARTIKEL_NR, wgr,
		  		     z->TAXPFL, z->REZEPTPFL, z->NICHTUEBERGH, z->ZUZAHLUNG_IFA,
			         z->NEGATIVLISTE, z->TIERARZNEI, z->NURKVA, 
					 z->MEDIZINPRODUKT, z->ARZNEIMITTEL, z->REZEPTURARZNEI,
					 z->KONTRAZEPTIVUM, z->IMPFSTOFF,
					 errmld );
	if ( ret == -1 ) 
		return -1;

	if ( ret == 0 )
		strcpy( z->BSSICHG, "0" );
	else
		strcpy( z->BSSICHG, "1" );


	return 0;

}

