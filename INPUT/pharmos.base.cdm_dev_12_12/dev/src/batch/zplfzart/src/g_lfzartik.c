/* ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die Galdat-Artikeldatei ein und schreibt        *
 *                  die Saetze in Oart-Tabellen			                  *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                                *
 * erstellt am    : 08.06.2005                                            *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include <hdatum/phodate.h>
#include <hdatum/phozeit.h>

/* --------------------------- */
#include <eklibs/ifalib/ifa_stat.h>
#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_dbas.h>

#include <voodoo_table_header/zartikel.h>

#include "zplfzart_form.h"
#include "sql_zplfzart.h"
#include "g_lfzartik.h"

#if !defined(_WIN32)
#include <libgen.h>
#endif
/* --- Prototype  ------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld );
void CloseBase( void );

/* ------------------- Globale Variablen ------------------------ */
static long anz_gelesen = 0;
static long anz_pzn_falsch = 0;
static long anz_zeile_falsch = 0;
static long anz_kein_zartikel = 0;
static long anz_zartikel_problem = 0;
static long anz_updzartikel = 0;

static long line_nr;
static int  line_pos;

struct ZARTIKEL zart;

struct MASSE	
{
	long	artikel_nr;
	long	laenge;
	long	breite;
	long	hoehe;
	long	gewicht;
};

struct MASSE masse;

char * spEnd	= NULL;
char * spBegin	= NULL;

/* --------  user -------------- */
static const char* const user = "zplfzart"  ;

/* ---------------------------------------------------------------------- */
int CheckPruefziffer ( long pzn )
{
	int i;
	long zahl, prziff;

	if ( pzn <= 0 ) 
		return 0;

    zahl = pzn;
	
	prziff = 0;
    for (i=7; i>=2; i--)
    {
            zahl /= 10;
            prziff += i * ( zahl % 10 );
    }
    prziff %= 11;

    if (prziff == 10) 
		prziff = 0;

	if ( prziff == ( pzn % 10 ) )
		return 1;
    else
		return 0;
}

/* ------------------------------------------------------------------- */
static int GetNextLineValue ( char * retvalue, int NoValExpected, char * errmld )
{
	spBegin = spEnd + 1;
	spEnd = strpbrk(spBegin, FILE_DELIMITER_MWE);

	if ( spEnd == NULL ) 
	{
		if ( line_pos != NoValExpected )
		{
			sprintf ( errmld, "Es wurde nicht die erwartete Anzahl an Feldern <%ld> in einer Datenzeile gefunden!", NoValExpected);
			return 2;
		}
		else
			return 1;
	}

	line_pos++;
	
	if ( strcmp(spBegin, spEnd) == 0 ) 
		strcpy ( retvalue, "" );
	else
        strncpy( retvalue, spBegin, strlen(spBegin) - strlen(spEnd));
	
	return 0;
}

/* ------------------------------------------------------------------- */
static int LineToStruct (char *errmld)
{
	char TmpNumeric[16];
	int retcode;
	char spToken[20];
	
	upd_code_del = 0;
	
	line_pos = 1;
	
	/* 02 - unbekannt ---> keine Verarbeitung */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_MWE, errmld ) != 0 )
		return retcode;

	memset(spToken, '\0', 19);

	/* 03 - unbekannt ---> keine Verarbeitung */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_MWE, errmld ) != 0 )
		return retcode;

	memset(spToken, '\0', 19);
	
	/* 04 - Länge */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_MWE, errmld ) != 0 )
		return retcode;

	strcpy( TmpNumeric, spToken );
	masse.laenge = atol( TmpNumeric );
	memset(TmpNumeric, '\0', 15);
	memset(spToken, '\0', 19);

	/* 05 - Breite */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_MWE, errmld ) != 0 )
		return retcode;

	strcpy( TmpNumeric, spToken );
	masse.breite = atol( TmpNumeric );
	memset(TmpNumeric, '\0', 15);
	memset(spToken, '\0', 19);

	/* 06 - Höhe */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_MWE, errmld ) != 0 )
		return retcode;

	strcpy( TmpNumeric, spToken );
	masse.hoehe = atol( TmpNumeric );
	memset(TmpNumeric, '\0', 15);
	memset(spToken, '\0', 19);

	/* 07 - Volumen ---> keine Verarbeitung */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_MWE, errmld ) != 0 )
		return retcode;

	memset(spToken, '\0', 19);
	
	/* 08 - Gewicht */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_MWE, errmld ) != 0 )
		return retcode;

	strcpy( TmpNumeric, spToken );
	masse.gewicht = atol( TmpNumeric );
	memset(TmpNumeric, '\0', 15);
	memset(spToken, '\0', 19);

	/* EOL */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_MWE, errmld ) != 1 )
		return 1;
	else
		return 0;
}

/* ------------------------------------------------------------------- */
static int ExtractPZNFromLine (char* line, char *errmld)
{
	char cPZN[14];
	memset(cPZN, '\0', 14);

	/* strpbrk liefert Zeiger auf das erste Semikolon in line */
	spBegin = line;
	spEnd = strpbrk(line, FILE_DELIMITER_MWE);
	
	strncpy(cPZN, spBegin, strlen(spBegin) - strlen(spEnd));

	memset(&zart,0,sizeof(zart));
	masse.artikel_nr = atol( cPZN );
	
	if ( CheckPruefziffer ( masse.artikel_nr ) != 1 )
		return 1;
	else
		return 0;
}

/* ------------------------------------------------------------------- */
static int UpdateProductFile( char* errmld )
{
	int sqlret;
	int zart_changed = 0;

	sqlret = sel_zartikel(&Fd_ZArtikel, masse.artikel_nr, &zart, errmld);

	if (sqlret == 0)
	{
		zart.LAENGE		= masse.laenge;
		zart.BREITE		= masse.breite;
		zart.HOEHE		= masse.hoehe;
		zart.GEWICHT	= masse.gewicht;
		zart.DATUM_MWE  = tages_datum;

		sqlret = upd_zartikel(&Fd_ZArtikel, &zart, errmld);
		
		if (sqlret == 0)
			anz_updzartikel++;
	}

	return sqlret;
}

/* ------------------------------------------------------------------- */
static int LoadArticle ( char *errmld )
{
	int sqlret;

	sqlret = UpdateProductFile( errmld );

	if ( sqlret == 99 ) // Satz unverändert
	{
		sqlret = 0;
	}

	return sqlret;
}

/* ------------------------------------------------------------------- */
static int MWELieferung( char* db, char *errmld )
{
	int s, status;
	char zeile[MAX_LENGTH_MWE + 1];

	line_nr = 0;
	status = 0;
	while ( status == 0 ) /* Schleife zum Lesen aller Datenzeilen aus mwe.txt*/
	{
		status = GetMWEZeile( fd_mwefile, zeile );
		if (status == 0)
		{
			anz_gelesen++;
			line_nr++;	
			
			if ( ExtractPZNFromLine( zeile, errmld ) == 0 || !strcmp(db, "ich21") || !strcmp(db, "ich21pre"))
			{
				if ( LineToStruct (errmld) == 0 )
				{
					s = LoadArticle (errmld);
              
					if ( s == 100 )
					{
						anz_kein_zartikel++;
						status = 5;
					}
					else if ( s != 0 )
					{
						anz_zartikel_problem++;
						status = 6;
					}
				}
				else 
				{
					anz_zeile_falsch++;
					status = 4;
				}
			}
			else 
			{
				anz_pzn_falsch++;
				status = 3;
			}
		}

		/* kein Abbruch bei Fehler in der Verarbeitung einer Zeile, evtl. später Protokoll ausgeben */
		if (status > 2)
			status = 0;
	}

	if (status != 2) 
	{
		sprintf(errmld, "Error on reading mwe.txt; file not read to the end! Status: %d,\n"
						"Zeile: %s", status, zeile);
	}
	else
		status = 0; /* EOF */

   CloseMWEDatei( fd_mwefile );
   fd_mwefile = NULL;
   
   return status;
}

/* ------------------------------------------------------------------- */
static long Load_MWE( char *db, char* ili_file, char *errmld )
{
   int status;
   long time;
   int weekday;
   	
   tages_datum = GetPhoDate();

   /* in zapflege immer mit Datum des Folgetags schreiben */
   zapflege_datum = tages_datum;

   do
   {
		zapflege_datum = AddDayToPhoDate(zapflege_datum, 1);
		weekday = WeekdayOfPhoDate(zapflege_datum);
   } while (weekday >= 5);

   time = GetPhoTime();
   
   fd_mwefile = NULL;

   /* öffnen des MWE-Files und Protokoll-File */
   status = OpenMWEDatei( &fd_mwefile, ili_file, errmld );
   if ( status != 0 )
   {
       sprintf(errmld, "mwe-file not found under path %s\n", ili_file);
	   return status;
   }
   
    if ( OpenBase( db, errmld ) == 0 )
    {
        OpenPflege( (char*)user, errmld );
		
		Fd_ZArtikel = -1;

		if ( OpenBufferDesc( &Fd_ZArtikel, "zartikel", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 )
		{
			status = MWELieferung ( db, errmld );
		}
		else
			status = 1;

		CloseOneBufferDesc(Fd_ZArtikel);

        CloseBase( );
    }
	else
		status = 1;

   return status;
}

/* ------------------------------------------------------------------- */
#define FILE_LEN 30
long Load_MWE_Daten( char *db, char *ili_direc, char *errmld )
{
	char *ili_file;

    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );

	if ( ili_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler Load_MWE_Daten" );
       return 1;
    }

	strcpy( ili_file, ili_direc );
    strcat( ili_file, FILENAME_MWE );
    
	if ( Load_MWE( db, ili_file, errmld ) != 0 )
    {
       free( ili_file );
	   return 1;
    }

    free( ili_file );
	
   sprintf( errmld,  "%ld Saetze gelesen aus MWE-Datei\n" 
					 "%ld Saetze mit falscher PZN\n"
					 "%ld Saetze mit falschem Zeilenaufbau\n"
					 "%ld zartikel nicht vorhanden\n"
					 "%ld zartikel-Verarbeitungs-Probleme\n"
					 "%ld zartikel-Updates\n", 
					 anz_gelesen, anz_pzn_falsch, anz_zeile_falsch, anz_kein_zartikel, anz_zartikel_problem, anz_updzartikel );

    return 0;
}
