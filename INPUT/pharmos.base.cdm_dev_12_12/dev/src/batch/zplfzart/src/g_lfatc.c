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

#include <voodoo_table_header/carticlecodes.h>

#include "zplfzart_form.h"
#include "sql_zplfzart.h"
#include "g_lfatc.h"

#if !defined(_WIN32)
#include <libgen.h>
#endif
/* --- Prototype  ------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld );
void CloseBase( void );

/* ------------------- Globale Variablen ------------------------ */
static long anz_gelesen = 0;
static long anz_zeile_falsch = 0;
static long anz_kein_zartikel = 0;
static long anz_zartikel_problem = 0;
static long anz_del_atc = 0;
static long anz_ins_atc = 0;
static long anz_upd_atc = 0;

static long line_nr;
static int  line_pos;

struct CARTICLECODES codes;

struct ATC	
{
	long	articleno;
	char	code[L_CARTICLECODES_ARTICLE_CODE+1];
};

struct ATC atc;
struct ZARTIKEL zart;

char * spEnd4	= NULL;
char * spBegin4	= NULL;

/* --------  user -------------- */
static const char* const user = "zplfzart"  ;

/* ------------------------------------------------------------------- */
static int GetNextLineValue ( char * retvalue, int NoValExpected, int firstField, char * errmld )
{
	if (!firstField)
	{
		spBegin4 = spEnd4 + 1;
		spEnd4 = strpbrk(spBegin4, FILE_DELIMITER_ABDA);
	}

	if ( spEnd4 == NULL ) 
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
	
	if ( strcmp(spBegin4, spEnd4) == 0 ) 
		strcpy ( retvalue, "" );
	else
        strncpy( retvalue, spBegin4, strlen(spBegin4) - strlen(spEnd4));
	
	return 0;
}

/* ------------------------------------------------------------------- */
static int LineToStruct ( char* line, char *errmld)
{
	char TmpNumeric[10];
	int retcode;
	char spToken[60];

	/* strpbrk liefert Zeiger auf das erste Semikolon in line */
	spBegin4 = line;
	spEnd4 = strpbrk(line, FILE_DELIMITER_ABDA);
	
	upd_code_del = 0;
	
	line_pos = 0;

	/* 00  */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_ABDA, 1, errmld ) != 0 )
		return retcode;

	if (*spToken == 'D')
		upd_code_del = 1;
	else
		upd_code_del = 0;

	memset(spToken, '\0', 59);

	/* 01 */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_ABDA, 0, errmld ) != 0 )
		return retcode;

	strcpy( TmpNumeric, spToken );
	atc.articleno = atol( TmpNumeric );
	
	memset(TmpNumeric, '\0', 9);
	memset(spToken, '\0', 59);

	/* 02 */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_ABDA, 0, errmld ) != 0 )
		return retcode;

	strcpy( atc.code, spToken );
	
	memset(TmpNumeric, '\0', 9);
	memset(spToken, '\0', 59);

	
	/* EOL */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_ABDA, 0, errmld ) != 1 )
		return 1;
	else
		return 0;
}

/* ------------------------------------------------------------------- */
static int LoadAtc( char* errmld )
{
	int sqlret;
	
	// Umrechnung PZN8
	atc.articleno = sel_ArtNoByCode(atc.articleno);
	
	if (atc.articleno <= 0) // Code unbekannt
		return 99;

	sqlret = sel_carticlecodes(&Fd_Atc, atc.articleno, &codes, errmld);

	codes.DATE_CHANGED = GetPhoDate();

	// lesen catccode.narcotic_substance_flag
	// setzen zartikel.psychotrop = J, bestell_nicht_ausl = 1 ==> wenn btm != 1 und psychotrop != J
	if ( upd_code_del == 0 && 0 < isNarcoticStillUnset(atc.code, atc.articleno) )
	{
		if ( 0 == sel_zartikel(&Fd_ZArtikel, atc.articleno, &zart, errmld) )
		{
			*zart.BESTELL_NICHT_AUSL = '1';
			*zart.PSYCHOTROP = 'J';

			upd_zartikel(&Fd_ZArtikel, &zart, errmld);
		}
	}

	if (sqlret == 0 && upd_code_del == 1)
	{
		sqlret = del_carticlecodes(&Fd_Atc, &codes, errmld);

		if (sqlret == 0)
			anz_del_atc++;
	}
	else if (sqlret == 100 && upd_code_del == 0)
	{
		codes.ARTICLENO = atc.articleno;
		codes.PREFERRED_FLAG = 0;
		codes.CODE_TYPE = 2;
		codes.SERIAL_NUMBER = 0;
		strcpy(codes.ARTICLE_CODE, atc.code);

		sqlret = ins_carticlecodes(&Fd_Atc, &codes, errmld);
		
		if (sqlret == 0)
			anz_ins_atc++;
	}
	else if (sqlret == 0)
	{
		strcpy(codes.ARTICLE_CODE, atc.code);

		sqlret = upd_carticlecodes(&Fd_Atc, &codes, errmld);
		
		if (sqlret == 0)
			anz_upd_atc++;
	}
	
	return sqlret;
}

/* ------------------------------------------------------------------- */
static int AtcLieferung( char *errmld )
{
	int s, status;
	char zeile[MAX_LENGTH_HI + 1];

	line_nr = 0;
	status = 0;
	while ( status == 0 ) /* Schleife zum Lesen aller Datenzeilen */
	{
		status = GetHealthInsuranceZeile( fd_healthinsurancefile, zeile );
		if (status == 0)
		{
			anz_gelesen++;
			line_nr++;	
			
			if ( LineToStruct (zeile, errmld) == 0 )
			{
				s = LoadAtc (errmld);
              
				if ( s == 99 )
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

		/* kein Abbruch bei Fehler in der Verarbeitung einer Zeile, evtl. später Protokoll ausgeben */
		if (status > 2)
			status = 0;
	}

	if (status != 2) 
	{
		sprintf(errmld, "Error on reading PAC_APO.txt; file not read to the end! Status: %d,\n"
						"Zeile: %s", status, zeile);
	}
	else
		status = 0; /* EOF */

   CloseHealthInsuranceDatei( fd_healthinsurancefile );
   fd_healthinsurancefile = NULL;
   
   return status;
}

/* ------------------------------------------------------------------- */
static long Load_ATC( char *db, char* ili_file, char *errmld )
{
   int status;
   
   fd_healthinsurancefile = NULL;

   status = OpenHealthInsuranceDatei( &fd_healthinsurancefile, ili_file, errmld );
   if ( status != 0 )
   {
       sprintf(errmld, "PAC_APO-file not found under path %s\n", ili_file);
	   return status;
   }
   
    if ( OpenBase( db, errmld ) == 0 )
    {
        OpenPflege( (char*)user, errmld );
		
		Fd_Atc = -1;
		Fd_ZArtikel = -1;

		if ( OpenBufferDesc( &Fd_Atc, "carticlecodes", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 &&
			 OpenBufferDesc( &Fd_ZArtikel, "zartikel", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0)
		{
			status = AtcLieferung ( errmld );
		}
		else
			status = 1;

		CloseOneBufferDesc(Fd_Atc);
		CloseOneBufferDesc(Fd_ZArtikel);

		CloseBase( );
    }
	else
		status = 1;

   return status;
}

/* ------------------------------------------------------------------- */
#define FILE_LEN 30
long Load_AbdaATC_Daten( char *db, char *ili_direc, char *errmld )
{
	char *ili_file;

    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );

	if ( ili_file == NULL )
    {
       strcpy( errmld, "malloc-Fehler Load_AbdaATC_Daten" );
       return 1;
    }

	strcpy( ili_file, ili_direc );
    strcat( ili_file, FILENAME_ATC );
    
	if ( Load_ATC( db, ili_file, errmld ) != 0 )
    {
       free( ili_file );
	   return 1;
    }

    free( ili_file );
	
   sprintf( errmld,  "%ld Saetze gelesen aus AbdaATC-Datei\n" 
					 "%ld Saetze mit falschem Zeilenaufbau\n"
					 "%ld zartikel nicht vorhanden\n"
					 "%ld carticlecodes[2]-Verarbeitungs-Probleme\n"
					 "%ld carticlecodes[2]-Updates\n"
					 "%ld carticlecodes[2]-Inserts\n"
					 "%ld carticlecodes[2]-Deletes\n", 
					 anz_gelesen, anz_zeile_falsch, anz_kein_zartikel, anz_zartikel_problem, anz_upd_atc, anz_ins_atc, anz_del_atc);

    return 0;
}
