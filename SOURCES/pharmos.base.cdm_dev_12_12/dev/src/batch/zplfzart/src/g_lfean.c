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

#include <voodoo_table_header/ean.h>

#include "zplfzart_form.h"
#include "sql_zplfzart.h"
#include "g_lfean.h"

#if !defined(_WIN32)
#include <libgen.h>
#endif
/* --- Prototype  ------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld );
void CloseBase( void );

/* ------------------- Globale Variablen ------------------------ */
static long anz_gelesen = 0;
static long anz_zeile_falsch = 0;
static long anz_ean_pzn_vorh = 0;
static long anz_nur_ean_vorh = 0;
static long anz_nur_pzn_vorh = 0;
static long anz_ean_problem = 0;
static long anz_insertean = 0;

static long line_nr;
static int  line_pos;

struct EAN ean_struct;

struct EAN_PZN	
{
	char	ean[14];
	long	artikel_nr;
};

struct EAN_PZN ean_pzn;

char * spEnd2	= NULL;
char * spBegin2	= NULL;

/* --------  user -------------- */
static const char* const user = "zplfzart"  ;

/* ------------------------------------------------------------------- */
static int GetNextLineValue ( char * retvalue, int NoValExpected, int firstField, char * errmld )
{
	if (!firstField)
	{
		spBegin2 = spEnd2 + 1;
		spEnd2 = strpbrk(spBegin2, FILE_DELIMITER_EAN);
	}

	if ( spEnd2 == NULL ) 
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
	
	if ( strcmp(spBegin2, spEnd2) == 0 ) 
		strcpy ( retvalue, "" );
	else
        strncpy( retvalue, spBegin2, strlen(spBegin2) - strlen(spEnd2));
	
	return 0;
}

/* ------------------------------------------------------------------- */
static int LineToStruct (char* line, char *errmld)
{
	char TmpNumeric[16];
	int retcode;
	char spToken[20];
	
	/* strpbrk liefert Zeiger auf das erste Semikolon in line */
	spBegin2 = line;
	spEnd2 = strpbrk(line, FILE_DELIMITER_MWE);
	
	upd_code_del = 0;
	
	line_pos = 0;
	
	/* 01 - EAN */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_EAN, 1, errmld ) != 0 )
		return retcode;

	strcpy( ean_pzn.ean, spToken );
	memset(spToken, '\0', 19);

	/* 02 - PZN */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_EAN, 0, errmld ) != 0 )
		return retcode;

	strcpy( TmpNumeric, spToken );
	ean_pzn.artikel_nr = atol( TmpNumeric );
	memset(TmpNumeric, '\0', 15);
	memset(spToken, '\0', 19);

	/* EOL */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_EAN, 0, errmld ) != 1 )
		return 1;
	else
		return 0;
}

/* ------------------------------------------------------------------- */
static int InsertEan( char* errmld )
{
	int sqlret;

	strcpy (ean_struct.EAN_NR, ean_pzn.ean);
	ean_struct.ARTIKEL_NR = ean_pzn.artikel_nr;
	strcpy (ean_struct.ART_PFL, "S");

	sqlret = ins_ean(&Fd_Ean, &ean_struct, errmld);
	
	if (sqlret == 0)
		anz_insertean++;

	return sqlret;
}

/* ------------------------------------------------------------------- */
static int LoadEan ( char *errmld )
{
	int sqlret;

	sqlret = InsertEan( errmld );
	
	return sqlret;
}

/* ------------------------------------------------------------------- */
static int EANLieferung( char *errmld )
{
	int s, status;
	char zeile[MAX_LENGTH_EAN + 1];

	line_nr = 0;
	status = 0;
	while ( status == 0 ) /* Schleife zum Lesen aller Datenzeilen aus ean.txt */
	{
		status = GetEANZeile( fd_eanfile, zeile );
		if (status == 0)
		{
			anz_gelesen++;
			line_nr++;	
			
			if ( LineToStruct (zeile, errmld) == 0 )
			{
				// hier erst noch checken, ob EAN / PZN oder beides schon existiert
				s = sel_ean(&Fd_Ean, ean_pzn.ean, ean_pzn.artikel_nr, &ean_struct, errmld);

				if ( s != 0 )
					status = s;

				if ( s == 3 )
					anz_ean_pzn_vorh++;
				else if ( s == 4 )
					anz_nur_ean_vorh++;
				else if ( s == 5 )
					anz_nur_pzn_vorh++;
				else if ( s != 0 )
				{
					anz_ean_problem++;
					status = 6;
				}
				else
				{
					s = LoadEan (errmld);
	            
					if ( s != 0 )
					{
						anz_ean_problem++;
						status = 7;
					}
				}
			}
			else 
			{
				anz_zeile_falsch++;
				status = 8;
			}
		}

		/* kein Abbruch bei Fehler in der Verarbeitung einer Zeile, evtl. später Protokoll ausgeben */
		if (status > 2)
			status = 0;
	}

	if (status != 2) 
	{
		sprintf(errmld, "Error on reading ean.txt; file not read to the end! Status: %d,\n"
						"Zeile: %s", status, zeile);
	}
	else
		status = 0; /* EOF */

   CloseEANDatei( fd_eanfile );
   fd_eanfile = NULL;
  
   return status;
}

/* ------------------------------------------------------------------- */
static long Load_EAN( char *db, char* ili_file, char *errmld )
{
   int status;
   	
   tages_datum = GetPhoDate();
   
   fd_eanfile = NULL;
   
   /* öffnen des EAN-Files und Protokoll-File */
   status = OpenEANDatei( &fd_eanfile, ili_file, errmld );
   if ( status != 0 )
   {
       sprintf(errmld, "ean-file not found under path %s\n", ili_file);
	   return status;
   }
   
    if ( OpenBase( db, errmld ) == 0 )
    {
        OpenPflege( (char*)user, errmld );
		
		Fd_Ean = -1;

		if ( OpenBufferDesc( &Fd_Ean, "ean", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 )
		{
			status = EANLieferung ( errmld );
		}
		else
			status = 1;

		CloseOneBufferDesc(Fd_Ean);

        CloseBase( );
    }
	else
		status = 1;

   return status;
}

/* ------------------------------------------------------------------- */
#define FILE_LEN 22
long Load_EAN_Daten( char *db, char *ili_direc, char *errmld )
{
	char *ili_file;

    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );
	if ( ili_file == NULL  )
    {
       strcpy( errmld, "malloc-Fehler Load_EAN_Daten" );
       return 1;
    }

	strcpy( ili_file, ili_direc );
    strcat( ili_file, FILENAME_EAN );
    
	if ( Load_EAN( db, ili_file, errmld ) != 0 )
    {
		free( ili_file );
		return 1;
    }

    free( ili_file );
	
	sprintf( errmld, "%ld Saetze gelesen aus EAN-Datei\n" 
					 "%ld Saetze mit falschem Zeilenaufbau\n"
					 "%ld EAN-PZN-Kombination schon vorhanden\n"
					 "%ld EAN schon mit anderer PZN vorhanden\n"
					 "%ld PZN schon mit anderer EAN vorhanden\n"
					 "%ld ean-Verarbeitungs-Probleme\n"
					 "%ld ean-Inserts\n", 
					 anz_gelesen, anz_zeile_falsch, anz_ean_pzn_vorh, anz_nur_ean_vorh, anz_nur_pzn_vorh, anz_ean_problem, anz_insertean );

    return 0;
}
