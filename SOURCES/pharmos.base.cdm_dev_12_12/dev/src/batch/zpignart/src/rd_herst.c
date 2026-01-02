/* ---------------------------------------------------------------------- *
 *                         R D _ H E R S . C                              *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 *           - liest den Hersteller                                       *
 *             fuer autidem und zentralppelist                            *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  27.10.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo.h>



static int fd_herstel = -1;

static long  LastHerstellerNr = -1;
static long  LastStatus = 0;

static short LastErstattungstage;
static char  LastZentralppelist[2];

static char  Lastekoriginalhs[2];
static char  Lastbestell_nur_ozek[2];
static char  Lastrezeptpfl[2];
static char  Lastapothekenpfl[2];
static char  Lastnettoartikel[2];
static short Lastbezugssperre;


void CloseHerstel( )
{
	if ( fd_herstel != -1 )
		SqlCloseCs( fd_herstel );
	fd_herstel = -1;
}


static long GetHerstel( char *errmld )
{
	long s;

	if ( fd_herstel == -1 )
	{
		char *sql;
		sql = "select erstattungstage, zentralppelist, ekoriginalhs, bestell_nur_ozek, rezeptpfl, apothekenpfl, nettoartikel, bezugssperre from herstel where hersteller_nr=?";
		s = SqlDeclareCsWh( &fd_herstel, sql, "herstel.hersteller_nr", NULL );
		if ( s != 0 )
		{
			fd_herstel = -2;
			sprintf( errmld , "Fehler bei SqlDeclareCs(herstel) (%ld)", s);
			return s;
		}
	}
	else if ( fd_herstel == -2 )
		return -1;

	s = SqlReadDeclCs( fd_herstel, 
		               &LastErstattungstage, LastZentralppelist, 
					   Lastekoriginalhs, Lastbestell_nur_ozek, 
					   Lastrezeptpfl, Lastapothekenpfl, Lastnettoartikel, &Lastbezugssperre, NULL, 
					   &LastHerstellerNr, NULL );
	if ( s == 100 )
		return s;
	if ( s != 0 )
        sprintf( errmld , "Fehler bei SqlReadDeclCs(herstel) (%ld)", s);
	return s;
}


static long LeseHerstel( long hersteller_nr, short *erstattungstage, char *zentralppelist, 
						char *ekoriginalhs, char *bestell_nur_ozek, 
						char *rezeptpfl, char *apothekenpfl, char *nettoartikel, short * bezugssperre,
						char *errmld )
{
	long s;
	if ( LastHerstellerNr != hersteller_nr )
	{	
		LastHerstellerNr = hersteller_nr;
		s = GetHerstel( errmld );
		if ( s != 0 )
		{
			LastErstattungstage = 0;
			strcpy( LastZentralppelist, "0" );
			
			strcpy( Lastekoriginalhs, "0" );
			strcpy( Lastbestell_nur_ozek, "0" );
			strcpy( Lastrezeptpfl, "0" );
			strcpy( Lastapothekenpfl, "0" );
			strcpy( Lastnettoartikel, "0" );
			Lastbezugssperre = 0;
		}
		LastStatus = s;
	}
	else
		s = LastStatus;

	*erstattungstage = LastErstattungstage;
	strcpy( zentralppelist, LastZentralppelist );

	strcpy( ekoriginalhs, Lastekoriginalhs );
	strcpy( bestell_nur_ozek, Lastbestell_nur_ozek );
	strcpy( rezeptpfl, Lastrezeptpfl );
	strcpy( apothekenpfl, Lastapothekenpfl );
	strcpy( nettoartikel, Lastnettoartikel );
	*bezugssperre = Lastbezugssperre;

	return s;
}

long LeseErstattungstage( long hersteller_nr, short *erstattungstage, char *errmld )
{
	char zentralppelist[2];
	char  ekoriginalhs[2];
	char  bestell_nur_ozek[2];
	char  rezeptpfl[2];
	char  apothekenpfl[2];
	char  nettoartikel[2];
	short bezugssperre;
	return LeseHerstel( hersteller_nr, erstattungstage, zentralppelist, 
						ekoriginalhs, bestell_nur_ozek, 
						rezeptpfl, apothekenpfl, nettoartikel, &bezugssperre, errmld );
}

long LeseZentralppelist( long hersteller_nr, char *zentralppelist, char *errmld )
{
	short erstattungstage;
	char  ekoriginalhs[2];
	char  bestell_nur_ozek[2];
	char  rezeptpfl[2];
	char  apothekenpfl[2];
	char  nettoartikel[2];
	short bezugssperre;
	return LeseHerstel( hersteller_nr, &erstattungstage, zentralppelist, 
						ekoriginalhs, bestell_nur_ozek, 
						rezeptpfl, apothekenpfl, nettoartikel, &bezugssperre, errmld );
}

long LeseHerstelSortimente( long hersteller_nr, char *ekoriginalhs, char *bestell_nur_ozek, 
						char *rezeptpfl, char *apothekenpfl, char *nettoartikel, short * bezugssperre, char *errmld )
{
	short erstattungstage;
	char zentralppelist[2];
	return LeseHerstel( hersteller_nr, &erstattungstage, zentralppelist, 
						ekoriginalhs, bestell_nur_ozek, 
						rezeptpfl, apothekenpfl, nettoartikel, bezugssperre, errmld );
}

