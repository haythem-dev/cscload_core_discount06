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

/* --------------------------- */
#include <eklibs/ifalib/ifa_stat.h>
#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_dbas.h>

#include <voodoo_table_header/chealthinsurance.h>
#include <voodoo_table_header/chealthinsurancearticles.h>

#include "zplfzart_form.h"
#include "sql_zplfzart.h"
#include "g_lfhealthinsurance.h"

#if !defined(_WIN32)
#include <libgen.h>
#endif

/* --- Prototype  ------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld );
void CloseBase( void );

/* ------------------- Globale Variablen ------------------------ */
static long anz_gelesen = 0;
static long anz_zeile_falsch = 0;
static long anz_hi_problem = 0;
static long anz_updchi = 0;
static long anz_inschi = 0;
static long anz_delchi = 0;

static long line_nr;
static int  line_pos;

struct CHEALTHINSURANCE chi;
struct CHEALTHINSURANCEARTICLES chia;
struct CHEALTHINSURANCEGROUPS chig;

struct HEALTH_INSURANCE	
{
	long	articleno;
	long	healthinsuranceid;
	long	healthinsurancegroup;
	char	healthinsurancename[L_CHEALTHINSURANCE_HEALTHINSURANCENAME + 1];
};

struct HEALTH_INSURANCE hi;

char * spEnd3	= NULL;
char * spBegin3	= NULL;

/* --------  user -------------- */
static const char* const user = "zplfzart"  ;

/* ------------------------------------------------------------------- */
static int GetNextLineValue ( char * retvalue, int NoValExpected, int firstField, char * errmld )
{
	if (!firstField)
	{
		spBegin3 = spEnd3 + 1;
		spEnd3 = strpbrk(spBegin3, FILE_DELIMITER_ABDA);
	}

	if ( spEnd3 == NULL ) 
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
	
	if ( strcmp(spBegin3, spEnd3) == 0 ) 
		strcpy ( retvalue, "" );
	else
        strncpy( retvalue, spBegin3, strlen(spBegin3) - strlen(spEnd3));
	
	return 0;
}

/* ------------------------------------------------------------------- */
static int LineToStruct (enum EAbdaFileArt mode, char* line, char *errmld)
{
	char TmpNumeric[10];
	int retcode;
	char spToken[60];

	/* strpbrk liefert Zeiger auf das erste Semikolon in line */
	spBegin3 = line;
	spEnd3 = strpbrk(line, FILE_DELIMITER_ABDA);
	
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
	
	if ( mode == IZG_APO || mode == PZG_APO )
		hi.healthinsurancegroup = atol( TmpNumeric );
	else // if ( mode == IKZ_APO )
		hi.healthinsuranceid = atol( TmpNumeric );
	
	memset(TmpNumeric, '\0', 9);
	memset(spToken, '\0', 59);

	/* 02 */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_ABDA, 0, errmld ) != 0 )
		return retcode;

	if ( mode == IZG_APO  )
	{
		strcpy( TmpNumeric, spToken );
		hi.healthinsuranceid = atol( TmpNumeric );
	}
	else if ( mode == IKZ_APO )
	{
		strcpy( hi.healthinsurancename, spToken );
	}
	else //if ( mode == PZG_APO )
	{
		strcpy( TmpNumeric, spToken );
		hi.articleno = atol( TmpNumeric );
	}

	memset(TmpNumeric, '\0', 9);
	memset(spToken, '\0', 59);

	/* EOL */
	if ( retcode = GetNextLineValue( spToken, NUMBER_FIELDS_ABDA, 0, errmld ) != 1 )
		return 1;
	else
		return 0;
}

/* ------------------------------------------------------------------- */
static int SaveHealthInsuranceArticles( char* errmld )
{
	int sqlret;

	// Umrechnung PZN8
	hi.articleno = sel_ArtNoByCode(hi.articleno);
	
	if (hi.articleno <= 0) // Code unbekannt
		return 99;
	
	sqlret = sel_chealthinsurancearticle (&Fd_CHealthInsuranceArticles, hi.healthinsurancegroup, hi.articleno, &chia, errmld);

	if (sqlret == 0 && upd_code_del == 1)
	{
		sqlret = del_chealthinsurancearticle(&Fd_CHealthInsuranceArticles, &chia, errmld);

		if (sqlret == 0)
			anz_delchi++;
	}
	else if (sqlret == 100 && upd_code_del == 0)
	{
		chia.ARTICLENO = hi.articleno;
		chia.HEALTHINSURANCEGROUP = hi.healthinsurancegroup;

		sqlret = ins_chealthinsurancearticle(&Fd_CHealthInsuranceArticles, &chia, errmld);
		
		if (sqlret == 0)
			anz_inschi++;
	}

	return sqlret;
}

/* ------------------------------------------------------------------- */
static int SaveHealthInsuranceGroups( char* errmld )
{
	int sqlret;
	
	sqlret = sel_chealthinsurancegroups (&Fd_CHealthInsuranceGroups, hi.healthinsurancegroup, hi.healthinsuranceid, &chig, errmld);

	if (sqlret == 0 && upd_code_del == 1)
	{
		sqlret = del_chealthinsurancegroups(&Fd_CHealthInsuranceGroups, &chig, errmld);

		if (sqlret == 0)
			anz_delchi++;
	}
	else if (sqlret == 100 && upd_code_del == 0)
	{
		chig.HEALTHINSURANCEID = hi.healthinsuranceid;
		chig.HEALTHINSURANCEGROUP = hi.healthinsurancegroup;

		sqlret = ins_chealthinsurancegroups(&Fd_CHealthInsuranceGroups, &chig, errmld);
		
		if (sqlret == 0)
			anz_inschi++;
	}

	return sqlret;
}

/* ------------------------------------------------------------------- */
static int SaveHealthInsurance( char* errmld )
{
	int sqlret;
	
	sqlret = sel_chealthinsurance (&Fd_CHealthInsurance, hi.healthinsuranceid, &chi, errmld);

	if (sqlret == 0)
	{
		if (upd_code_del == 1)
		{
			sqlret = del_chealthinsurance(&Fd_CHealthInsurance, &chi, errmld);

			if (sqlret == 0)
				anz_delchi++;
		}
		else
		{
			strcpy (chi.HEALTHINSURANCENAME, hi.healthinsurancename);

			sqlret = upd_chealthinsurance(&Fd_CHealthInsurance, &chi, errmld);

			if (sqlret == 0)
				anz_updchi++;
		}
	}
	else if (sqlret == 100 && upd_code_del == 0)
	{
		chi.HEALTHINSURANCEID = hi.healthinsuranceid;
		strcpy (chi.HEALTHINSURANCENAME, hi.healthinsurancename);
		
		sqlret = ins_chealthinsurance(&Fd_CHealthInsurance, &chi, errmld);
		
		if (sqlret == 0)
			anz_inschi++;
	}

	return sqlret;
}

/* ------------------------------------------------------------------- */
static int LoadHealthInsurance ( enum EAbdaFileArt mode, char *errmld )
{
	if (mode == PZG_APO)
		return SaveHealthInsuranceArticles( errmld );
	else if (mode == IKZ_APO)
		return SaveHealthInsurance( errmld );
	else // IZG_APO
		return SaveHealthInsuranceGroups( errmld );
}

/* ------------------------------------------------------------------- */
static int HealthInsuranceLieferung( enum EAbdaFileArt mode, char *errmld )
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
			
			if ( LineToStruct (mode, zeile, errmld) == 0 )
			{
				s = LoadHealthInsurance (mode, errmld);
              
				if ( s != 0 && s != 100)
				{
					anz_hi_problem++;
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
		sprintf(errmld, "Error on reading abda-file; file not read to the end! Status: %d,\n"
						"Zeile: %s", status, zeile);
	}
	else
		status = 0; /* EOF */

   CloseHealthInsuranceDatei( fd_healthinsurancefile );
   fd_healthinsurancefile = NULL;
   
   return status;
}

/* ------------------------------------------------------------------- */
static long Load_HealthInsurance( enum EAbdaFileArt mode, char *db, char* ili_file, char *errmld )
{
   int status;
   	
   fd_healthinsurancefile = NULL;
   
   status = OpenHealthInsuranceDatei( &fd_healthinsurancefile, ili_file, errmld );
   if ( status != 0 )
   {
       sprintf(errmld, "hi-file not found under path %s\n", ili_file);
	   return 999;
   }
   
    if ( OpenBase( db, errmld ) == 0 )
    {
        status = OpenPflege( (char*)user, errmld );
		
		Fd_CHealthInsurance = -1;
		Fd_CHealthInsuranceArticles = -1;
		Fd_CHealthInsuranceGroups = -1;

		if ( OpenBufferDesc( &Fd_CHealthInsurance, "chealthinsurance", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 && 
			OpenBufferDesc( &Fd_CHealthInsuranceGroups, "chealthinsurancegroups", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0 && 
			 OpenBufferDesc( &Fd_CHealthInsuranceArticles, "chealthinsurancearticles", NULL, NULL, V_PROTO_VERTEIL, errmld ) == 0)
		{
			status = HealthInsuranceLieferung ( mode, errmld );
		}
		else
			status = 1;

		CloseOneBufferDesc(Fd_CHealthInsurance);
		CloseOneBufferDesc(Fd_CHealthInsuranceGroups);
		CloseOneBufferDesc(Fd_CHealthInsuranceArticles);

		ClosePflege(errmld);

        CloseBase( );
    }
	else
		status = 1;

   return status;
}

/* ------------------------------------------------------------------- */
#define FILE_LEN 30
long Load_HealthInsurance_Daten( char *db, char *ili_direc, char *errmld )
{
	char *ili_file;
	int status;

	char message[500] = {0};

    ili_file = malloc( strlen( ili_direc ) + FILE_LEN + 1 );

	if ( ili_file == NULL  )
    {
       strcpy( errmld, "malloc-Fehler Load_HealthInsurance_Daten" );
       return 1;
    }

// --- EAbdaFileArt::IZG_APO ---
	strcpy( ili_file, ili_direc );
    strcat( ili_file, FILENAME_HI_IZG );

	status = Load_HealthInsurance( IZG_APO, db, ili_file, errmld );
    
	if ( status != 0 && status != 999)
    {
       free( ili_file );
	   return 1;
    }

	sprintf( errmld, "%ld Saetze gelesen aus IZG_APO-Datei\n" 
					 "%ld Saetze mit falschem Zeilenaufbau\n"
					 "%ld chealthinsurancegroups-Verarbeitungs-Probleme\n"
					 "%ld chealthinsurancegroups-Inserts\n"
					 "%ld chealthinsurancegroups-Deletes\n\n", 
					 anz_gelesen, anz_zeile_falsch, anz_hi_problem, anz_inschi, anz_delchi );

// --- EAbdaFileArt::IKZ_APO ---
	strcpy( ili_file, ili_direc );
    strcat( ili_file, FILENAME_HI_IKZ );
	anz_gelesen = anz_zeile_falsch = anz_hi_problem = anz_updchi = anz_inschi = anz_delchi = 0;
    
	status = Load_HealthInsurance( IKZ_APO, db, ili_file, message );
    
	if ( status != 0 && status != 999)
	{
       free( ili_file );
	   return 1;
    }

    sprintf( message, "%ld Saetze gelesen aus IKZ_APO-Datei\n" 
					 "%ld Saetze mit falschem Zeilenaufbau\n"
					 "%ld chealthinsurance-Verarbeitungs-Probleme\n"
					 "%ld chealthinsurance-Updates\n"
					 "%ld chealthinsurance-Inserts\n"
					 "%ld chealthinsurance-Deletes\n\n", 
					 anz_gelesen, anz_zeile_falsch, anz_hi_problem, anz_updchi, anz_inschi, anz_delchi );

	strcat( errmld, message );

// --- EAbdaFileArt::PZG_APO ---
	strcpy( ili_file, ili_direc );
    strcat( ili_file, FILENAME_HI_PZG );
	anz_gelesen = anz_zeile_falsch = anz_hi_problem = anz_updchi = anz_inschi = anz_delchi = 0;
    
	status = Load_HealthInsurance( PZG_APO, db, ili_file, message );
    
	if ( status != 0 && status != 999)
	{
       free( ili_file );
	   return 1;
    }

    sprintf( message, "%ld Saetze gelesen aus PZG_APO-Datei\n" 
					 "%ld Saetze mit falschem Zeilenaufbau\n"
					 "%ld chealthinsurancearticles-Verarbeitungs-Probleme\n"
					 "%ld chealthinsurancearticles-Inserts\n"
					 "%ld chealthinsurancearticles-Deletes\n", 
					 anz_gelesen, anz_zeile_falsch, anz_hi_problem, anz_inschi, anz_delchi );

	strcat( errmld, message );

// ---
	
	free( ili_file );
	
    return 0;
}
