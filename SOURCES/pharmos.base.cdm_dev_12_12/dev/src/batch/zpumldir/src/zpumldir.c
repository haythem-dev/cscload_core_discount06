
/* ---------------------------------------------------------------------- *
 *                         Z P U M L D I R . C                            *
 *            Server fuer Massenaenderungen BLIESORT, ARTNRBL             *
 *                          ueber Pipw                                    *
 * ---------------------------------------------------------------------- */
#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.4.4 : zpumldir 16.07.2015 : Rolf Raab";
}

/*!
\page page33 zpumldir - Server fuer Massenaenderungen BLIESORT, ARTNRBL ueber Pipw
___________________________________________________________________________
\version	1.4.4
\date		16.07.2015
\internal
- TH: wandeln mit neuer zartikel-Struktur
\endinternal
___________________________________________________________________________
\version	1.4.3
\date		10.04.2014
\internal
- TH: wandeln mit neuer zartikel/zartpreis-Struktur
\endinternal
___________________________________________________________________________
\version	1.4.2
\date		11.03.2014
\internal
- TH: wandeln mit neuer zartikel-Struktur
\endinternal
___________________________________________________________________________
\version	1.4.1
\date		28.03.2013
\internal
- TH: wandeln mit neuer zartikel-Struktur
\endinternal
___________________________________________________________________________
\version	1.4.0
\date		13.03.2013
\internal
- TH: AIX build
\endinternal

*/

/* 1.0.3 24.05.2002 ZARTIKEL: PREISSENKUNG,  --- wpp_ --- */ 
/* 1.0.4 13.12.2002 Feld BSSICHG in ZARTIKEL  */
/* 1.0.5 24.01.2003 Felder ANBIETERABSCHLAG, AUTIDEMARTIKEL, */
/*                  FESTBETRARTIKEL, DATUM_ABSCHLAG in ZARTIKEL  */
/* 1.0.6 06.03.2003 Neue Felder  REZEPTURARZNEI MEDIZINPRODUKT IMPFSTOFF CE_KENNZEICHEN */
/*                  ARZNEIMITTEL KONTRAZEPTIVUM in ZARTIKEL ( - ) */
/* 1.0.7 13/06/2003 neues Feld ZENTRALPPELIST */
/* 1.0.8 01/08/2003 neues Feld EKORIGINALHS */
/* 1.0.9 03.11.2003 Umstellung auf variable Datenbank  */
/* 1.1.0 13.11.2003 Neues Feld HILFSM_VERBRAUCH in zartikel */
/* 1.1.1 16.03.2005 RR: zartikel in Projektion lesen, anstatt "select *" */
/* 1.1.2 21.03.2005 RR: sql-Buffer zu o.a. Änderung entsprechend vergrößert */
/* 1.1.3 13.05.2005 RR: neuer Wert 'A' für nahrungsergänzung, behandeln wie 'V' */
/* 1.1.4 18.05.2005 RR: NEM-Automatismen nur in Deutschland (Datenbank abfragen) */
/* 1.1.5 19.07.2005 RR: undefinierter Programmabbruch bei Herstellerwechsel */
/*					--> einfach nochmal durchgewandelt, dann ging's */
/* 1.1.6 30.03.2006 RR: wandeln mit neuer zartikel-Struktur */
/* 1.1.7 16.06.2006 RR: wandeln mit neuer zartikel-Struktur */
/* 1.1.8 09.08.2006 RR: wandeln mit neuer zartikel-Struktur */
/* 1.1.9 05.01.2007 RR: wandeln mit neuer zartikel-Struktur */
/* 1.2.0 29.03.2007 RR: wandeln mit neuer zartikel-Struktur */
/* 1.2.1 21.06.2007 RR: wandeln mit neuer zartikel-Struktur */
/* 1.2.2 06.09.2007 RR: Änderung DB Deutschland von pps1cg auf pps1g */
/* 1.2.3 19.09.2007 RR: wandeln mit neuer zartikel-Struktur */
/* 1.2.4 08.07.2008 RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 1.2.5 09.09.2008 RR: Änderung DB Deutschland von pps1g auf zpps1de */
/* 1.2.6 11.11.2008 RR: wandeln mit neuer zartikel-Struktur */
/* 1.2.7 24.11.2009 RR: wandeln mit neuer zartikel-Struktur */
/* 1.2.8 14.04.2010 RR: wandeln mit neuer zartikel-Struktur */
/* 1.2.9 12.10.2011 RR: wandeln mit neuer zartikel-Struktur */
/* 1.3.0 22.05.2012 RR: wandeln mit neuer zartikel-Struktur */
/* 1.3.1 25.07.2012 TH: Änderung DB Deutschland von zpps1de auf ide21 */
/* 1.3.2 10.09.2012 RR: wandeln mit neuer zartikel-Struktur */
/* 1.4.0 13.03.2013 TH: AIX build */
/* 1.4.1 28.03.2013 TH: wandeln mit neuer zartikel-Struktur */
/* 1.4.2 11.03.2014 TH: wandeln mit neuer zartikel-Struktur */
/* 1.4.3 10.04.2014 TH: wandeln mit neuer zartikel/zartpreis-Struktur */
/* 1.4.4 16.07.2015 TH: wandeln mit neuer zartikel-Struktur */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo/libscsvoodoo.h>
//#include <hdatum/phodate.h>

/* -------------- Herstellerwechsel --------------------- */

int  Serv_HerstWechsel        ( char *ustr, int r_lng, char *rstr, int *lng, char *db );
void Serv_HerstWechselFreeAll ( void );

/* -------------  Umlisten -------------------------- */

int  Serv_UmlistenEinzel ( char *ustr, char *rstr, int *lng, char *db );
int  Serv_UmlistenGesamt ( char *ustr, char *rstr, int *lng, char *db );
void Serv_UmlistenFreeAll( void );

/* ----- Eroeffnung --------- */

/* --- SET ISOLATION-Fehler bei SE -------------------------------------- */

#define SQL_SETISOLA_ERROR   (-554)

void CloseBase(  )
{
   SqlExecuteImm( "close database" );
}

long OpenBase( char *db, char *errmld )
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


static int Server( int prog_nr, char *r_info, int r_lng,
                   char *w_info, int *w_lng, char *db )
{
    int status;
    switch ( prog_nr )
    {
           case 10:
             status = Serv_UmlistenGesamt( r_info, w_info, w_lng, db );
             Serv_UmlistenFreeAll( );
             break;
           case 11:
             status = Serv_UmlistenEinzel( r_info, w_info, w_lng, db );
             Serv_UmlistenFreeAll( );
             break;

           case  2:
             status = Serv_HerstWechsel( r_info, r_lng, w_info, w_lng, db );
             Serv_HerstWechselFreeAll( );
             break;

           default:
             status = 1;
             sprintf( w_info, "Programm-Teil %d nicht vorhanden", prog_nr );
             break;
    }
    return status;
}

/* ---------------- Programm-Ausahl ----------------- */

static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

static void GenUmlistenGesamt( char *buf )
{
  strcat( buf, "1. alle Artikel umlisten:\n" \
               "   zpumldir 10 database 'parameter'\n" );
}

static void GenUmlistenEinzel( char *buf )
{
  strcat( buf, "2. einzelne Artikel umlisten:\n" \
               "   zpumldir 11 database 'parameter'\n" );
}

static void GenHerstWechsel( char *buf )
{
  strcat( buf, "3. Herstellerwechsel:\n" \
               "   zpumldir 2 database 'parameter'\n" );
}

void ProgUsage( char *buf )
{
   Usage( buf );
   GenUmlistenGesamt( buf );
   GenUmlistenEinzel( buf );
   GenHerstWechsel  ( buf );
}


long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

   if ( argc < 2 )
   {
	   ProgUsage( buf );
	   return 1;
   }

   if ( strcmp( argv[0], "10" ) == 0 ||
        strcmp( argv[0], "11" ) == 0 ||
        strcmp( argv[0], "2"  ) == 0    )
   {
      char *r_info;
      char *w_info;
      int  r_lng;
      int  w_lng;
      s = OpenBase( argv[1], buf );
      if ( s == 0 )
      {
         r_info = buf;
         w_info = buf;
         r_lng = strlen( r_info );
         s = (long) Server( atoi( argv[0]), r_info, r_lng, w_info, &w_lng, argv[1] );
         CloseBase();
      }
   }
   else
   {
      s = 1;
      strcpy( buf, "Programm-Teil: " );
      strcat( buf, argv[0] );
      strcat( buf, " nicht vorhanden" );
   }
   return s;
}
