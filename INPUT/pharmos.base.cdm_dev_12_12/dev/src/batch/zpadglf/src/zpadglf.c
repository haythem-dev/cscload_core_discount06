/* ---------------------------------------------------------------------- *
 *                            zpadglf.c                                   *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Tabelle adgdat leeren und neu befuellen             *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 13.03.06                                            *
 *   letztes Update :                                                     *
 *   Autor          : K.Hinz                                              *
 * ---------------------------------------------------------------------- */
#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.2.0 : zpadglf 19/03/2013 Klaus Hinz";

/*!
\page page3 zpadglf

________________________________________________________________________________________
\version	1.2.0
\date		19.03.2013
\internal
- TH: AIX build
\endinternal

________________________________________________________________________________________
\version	1.1.1
\date		25.07.2012
\internal
- TH: voodoo table header
\endinternal

________________________________________________________________________________________
\version	1.1.0
\date		15.05.2012
\internal
- TH: PZN 8
\endinternal

*/

/* 1.0.2 05.01.2007 : RR: Problem: beim Laden der ADG-Datei auf der pps1 werden bei allen PZNs, */
/*						  die weniger als 7 Stellen haben, hinten 9er angehängt. Das tritt aber weder */
/*						  auf der sofumi1 auf noch beim Aufruf auf pps1 unter Windows. 2 Stellen ge- */
/*						  ändert (Line-End für zeilevortab und keine Hochkommas beim SQL-Insert */
/* 1.0.3 08.07.2008 : RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, */
/*						  Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.1.0 15.05.2012 : TH: PZN 8 */
/* 1.1.1 25.07.2012 : TH: voodoo table header */
/* 1.2.0 19.03.2013 : TH: AIX build */



/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <libscsvoodoo.h>

#include "zpadglf.h"
#include "zadgoreimp.h"

/* ----- Prototype --------- */
void LadeAdgdat(char *db, char *directory,char *buf);
int  OpenAdgDatei  ( FILE **fd, const char * const datei, char *errmld );
void CloseAdgDatei ( FILE *fd );
int GetAdgZeile( FILE * fd, char *zeile );
long GetEintragundKuerzeString(char *zeile);
/* SQL-Funktionen */
long OpenBase( const char * const db, char *errmld );
void CloseBase();
long truncate_table_adgdat(char *errmld);
int sel_zartikel	( const long art_nr, long * datum_ah, char *errmld);
int ins_zadgoreimp		( const struct ZADGOREIMP * const adg, char* errmld);
int upd_zadgoreimp	( const struct ZADGOREIMP * const adg, char* errmld);
int sel_zadgoreimp	( const long hersteller_nr, const long pzn_orig, char *errmld);
long sel_ArtNoByCode	( const long code, char *errmld);
/* ---------------- Programm-Ausahl ----------------- */

FILE	  *fd_file; /* Handle auf reimport.txt */

void ProgUsage( char *buf )
{
  strcat( buf, "1. zpadglf 1 database Verzeichnis \n" \
               "   laedt die adg-datei in die Relation zadgoreimp\n"\
               "   Verzeichnis: Pfadname, unter dem reimport.txt liegt\n" );
}


long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   switch ( *argv[0] )
    {
      case '1':
        if ( argc != 3 )        
        {
          s = 1;
          ProgUsage( buf );
        }
		else
			LadeAdgdat(argv[1], argv[2],buf);
			s = 0;
        break;

      default:
        s = 1;
        strcpy( buf, "Programm-Teil: " );
        strcat( buf, argv[0] );
        strcat( buf, " nicht vorhanden" );
        break;
     }
   return s;
}

/* ---------------------------------------------------------------------- */
int  OpenAdgDatei( FILE **fd, const char * const datei, char *errmld )
{
#ifndef WIN32
	char systemcall [254];
	sprintf(systemcall, "dos2unix %s %s", datei, datei);
	system(systemcall); 
#endif
	
	*fd = fopen(datei, "rt");
	if (*fd == NULL)
	{
       sprintf( errmld, "Fehler beim Oeffnen der Datei\n%s",
                        datei );
       return 1;
    }
    return 0;
}

/* ---------------------------------------------------------------------- */
void CloseAdgDatei( FILE *fd )
{
    if (fd != NULL)
	{
		fclose(fd);
		fd = NULL;
	}
}

/* ---------------------------------------------------------------------- */
int GetAdgZeile( FILE * fd, char *zeile )
{
    if (fgets(zeile, NO_SIGNS, fd) == NULL)
	{
		if (feof(fd) != 0)
			return 2;/*Dateiende*/
		else
			return 1;/*Error*/
	}
	return 0;
}
/* ---------------------------------------------------------------------- */
void LadeAdgdat(char *db, char *directory,char *buf)
{
	long lGelesen = 0, lInserts = 0,lUpdates=0;
	char *adg_file;
	int status, sqlstatus;
	long lHersteller,lPzn, lPznReimport,datum_ah;
	struct ZADGOREIMP stZadgoreimp;
	char zeile[NO_SIGNS + 1];
    adg_file = malloc( strlen( directory ) + FILE_LEN + 1 );

    if ( adg_file == NULL  )
    {
       strcpy( buf, "malloc-Fehler LadeAdgdat" );
       return ;
    }

	strcpy( adg_file, directory );
    strcat( adg_file, FILENAME );

	status = OpenAdgDatei( &fd_file, adg_file, buf );
	if ( 0 != status)
	{
		free( adg_file );
		return;
	}
    if ( OpenBase( db, buf ) == 0 )
	{
   		/* Tabelle leeren */
		status = truncate_table_adgdat(buf );

		/* Herstellernummer, Reimport-PZN, Original-PZN */
		while (0 == status)
		{
			status = GetAdgZeile( fd_file, zeile );
			if ( 0 == status)
			{
				lHersteller  =  GetEintragundKuerzeString(zeile); /*KeyFeld */
				lPznReimport =  GetEintragundKuerzeString(zeile); /*KeyFeld */
				lPzn =  GetEintragundKuerzeString(zeile);

				//-- PZN-8: Einträge könnten AC sein - daher via carticlecodes in PZN umwandeln:
				lPznReimport = sel_ArtNoByCode(lPznReimport, buf);
				lPzn		 = sel_ArtNoByCode(lPzn, buf);
				
				if (lPznReimport <= 0 || lPzn <= 0)
				{
					status = 1; // Error
					continue;
				}
				//--

				stZadgoreimp.HERSTELLER_NR = lHersteller;
				stZadgoreimp.ARTIKEL_NR_ORIG = lPzn;
				stZadgoreimp.ARTIKEL_NR_REIMP = lPznReimport;
				lGelesen++;
				/* Lesen */
				sqlstatus =  sel_zadgoreimp( lHersteller, lPzn, buf);
				if (100 == sqlstatus)
				{
					sqlstatus = ins_zadgoreimp( &stZadgoreimp, buf);
					lInserts++;
				}
				else
				{
					sqlstatus = sel_zartikel( lPznReimport, &datum_ah, buf );
					if (( 0 == sqlstatus) && ( 0 == datum_ah))
					{
						sqlstatus = upd_zadgoreimp( &stZadgoreimp, buf);
						lUpdates++;
					}
				}
			}
		}
		sprintf( buf, "Gelesen %ld \nInserts %ld \nUpdates %ld",lGelesen,lInserts,lUpdates );
	}
	
	free( adg_file );
	CloseBase();

}


/* ------------------------------------------------------------------- */
#define SQL_SETISOLA_ERROR   (-554)
void CloseBase(  )
{
   SqlExecuteImm( "close database" );
}

/* ------------------------------------------------------------------- */
long OpenBase( const char * const db, char *errmld )
{
   long s;

   char base[50];
   strcpy( base, "database " );
   strcat( base, db );

   s = SqlExecuteImm( base );
   if ( s != 0 )
   {
      strcpy( errmld, base );
      strcat( errmld, ": " );
      strcat( errmld, DynErrmld() );
      return s;
   }

   s = SqlExecuteImm("set isolation to dirty read" );
   if ( s == SQL_SETISOLA_ERROR ) s = 0;
   if ( s != 0 )
   {
     strcpy( errmld, "set isolation: " );
     strcat( errmld, DynErrmld() );
     CloseBase( );
     return s;
   }

   s = SqlExecuteImm( "SET LOCK MODE TO WAIT 10" );
   if ( s == SQL_SETISOLA_ERROR ) s = 0;
   if ( s != 0 )
   {
     strcat( errmld, "set lock mode: ");
     strcat( errmld, DynErrmld() );
     CloseBase( );
     return s;
   }
   return 0;
}

/* ------------------------------------------------------------------- */
void UpdateStatistics( const char * const relation )
{
   char sql[100];
   strcpy( sql, "update statistics for table " );
   strcat( sql, relation );
   SqlExecuteImm( sql );
}
/* ------------------------------------------------------------------- */
int sel_zartikel	( const long art_nr, long * datum_ah,  char *errmld)
{
    char sql[150];
    int status;
	long pzn;
    
    sprintf( sql, "select artikel_nr, datum_ah "
				"from zartikel where artikel_nr=%ld",
                  art_nr );

    status = SqlRead( sql, &pzn, datum_ah, NULL );
    if ( status != 0 && status != 100)
	{
		strcpy( errmld, "zartikel (Suche nach Artikelnr): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}
/* ------------------------------------------------------------------- */
int sel_zadgoreimp	( const long hersteller_nr, const long pzn_orig, char *errmld)
{
    char sql[150];
    int status;
	long pzn;
    
    sprintf( sql, "select artikel_nr_orig "
				"from zadgoreimp where artikel_nr_orig=%ld and hersteller_nr = %ld",
                  pzn_orig, hersteller_nr );

    status = SqlRead( sql, &pzn, NULL );
    if ( status != 0 && status != 100)
	{
		strcpy( errmld, "zadgoreimp (Suche nach Artikelnr): " );
		strcat( errmld, DynErrmld() );
	}
    return status;
}

/* ------------------------------------------------------------------- */
long sel_ArtNoByCode	( const long code, char *errmld)
{
    long artNo;
	char sql[150];

	sprintf( sql, "SELECT articleno FROM carticlecodes WHERE article_code ='%ld' "
					"AND code_type IN (SELECT code_type FROM ccodetypes WHERE artnr_substitute = 1)", code);
  
	if ( SqlRead( sql, &artNo, NULL ) != 0 )
	{
		artNo = -1;
		strcpy( errmld, "carticlecodes (Suche nach Code): " );
		strcat( errmld, DynErrmld() );
	}

	return artNo;
}

/* ------------------------------------------------------------------- */
int ins_zadgoreimp		( const struct ZADGOREIMP * const adg, char* errmld)
{
	int status;
	char sql[2500];
   
    sprintf( sql, 
		"insert into zadgoreimp (  %s  ) values ( "
		"%ld, %ld, %ld)",	PROJECTION_ZADGOREIMP,adg->HERSTELLER_NR,adg->ARTIKEL_NR_ORIG,adg->ARTIKEL_NR_REIMP);
    
    status = SqlExecuteImm( sql );
    if ( status != 0 ) 
	{
		strcpy( errmld, "zadgoreimp (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
    return status;

}

int upd_zadgoreimp	( const struct ZADGOREIMP * const adg, char* errmld)
{

	int status;
	char sql[2500];
   
    sprintf( sql, 
		"update zadgoreimp set artikel_nr_reimp = %ld where hersteller_nr = %ld and artikel_nr_orig = %ld ",
		adg->ARTIKEL_NR_REIMP,adg->HERSTELLER_NR,adg->ARTIKEL_NR_ORIG);
    
    status = SqlExecuteImm( sql );
    if ( status != 0 ) 
	{
		strcpy( errmld, "zadgoreimp (Insert einer Zeile): " );
		strcat( errmld, DynErrmld() );
	}
    return status;

}


/* ------------------------------------------------------------------- */
long truncate_table_adgdat(char *errmld)
{
   char command[50];
   long s;

   strcpy(command, "delete from zadgoreimp" );

   s = SqlExecuteImm( command );
   if ( s != 0 )
   {
      strcpy( errmld, command );
      strcat( errmld, ": " );
      strcat( errmld, DynErrmld() );
   }
   return s;
}

long GetEintragundKuerzeString(char* zeile)
{
	short sStart;
	char *pdest;
	char zeilevortab[NO_SIGNS + 1];

	pdest = strchr(zeile,'\t');

    if (pdest != NULL)
	{
		sStart = (int) (pdest - zeile);
		strncpy(zeilevortab,zeile,sStart++);
		zeilevortab[sStart - 1] = '\0';
		strcpy(zeile,zeile+sStart);
	}
	else 
		strcpy(zeilevortab,zeile);

	return atol(zeilevortab);
}
