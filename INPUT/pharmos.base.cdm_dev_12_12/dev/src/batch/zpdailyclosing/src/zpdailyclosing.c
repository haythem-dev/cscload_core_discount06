/* ---------------------------------------------------------------------- *
 *                            ZPDAILYCLOSING.C                            *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : ZDP Automatismen im Tagesabschluss                  *
 * ---------------------------------------------------------------------- *
 *   Autor          : Hörath                                              *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
	// in binary embedded full version string
	return "@(#)PHOENIX Stand: " CDM_VERSION " - 1.4.0 zpdailyclosing";
}

/*!
\page page9 zpdailyclosing - ZDP Automatismen im Tagesabschluss
________________________________________________________________________________________
\version	1.4.0
\date		28.06.2021
\internal
- WH: Hersteller Nummer als Article Codes setzen
\endinternal
________________________________________________________________________________________
\version	1.3.0
\date		11.02.2019
\internal
- TH: neuer Mode 3: Erzeugung NTIN (DACH-BT).
\endinternal
________________________________________________________________________________________
\version	1.2.0
\date		06.10.2016
\internal
- TH: CR-16A023: Erweiterung Mode 2: Berechnung Erstattungswert (zartfrance) auch für LPPR´s.
\endinternal
________________________________________________________________________________________
\version	1.1.0
\date		13.01.2016
\internal
- TH: neuer Mode 2: Berechnung Erstattungswert (zartfrance) aus zartpreis.avp (INC-16000905).
\endinternal

________________________________________________________________________________________
\version	1.0.0
\date		15.04.2015
\internal
- TH: Setzen AH- Datum in ArtikelName.
\endinternal

*/

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

/* ----- Prototype --------- */

long CreateProdNoLoop ( char *db, char *user, char *buf );
void CreateProdNoUsage( char *buf );

long CreateNtinLoop ( char *db, char *user, char *buf );
void CreateNtinUsage( char *buf );

long SetArticleNameLoop ( char *db, char *user, char * datefrom, char * dateto, char *buf );
void SetArticleNameUsage( char *buf );

long SetReimbursementValFranceLoop ( char *db, char *user, char * datefrom, char * dateto, char *buf );
void SetReimbursementValFranceUsage( char *buf );

/* ----- Eroeffnung --------- */

/* --- SET ISOLATION-Fehler bei SE -------------------------------------- */

#define SQL_SETISOLA_ERROR   (-554)


static int IsolaError = 0;

int IsStandartEngine( )
{
	return IsolaError;
}

void CloseBase(  )
{
   SqlExecuteImm( "close database" );
}

long OpenBase( char *db, char *errmld )
{
   long s;
   char base[50];

   IsolaError = 0;

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
   if ( s == SQL_SETISOLA_ERROR ) 
   {
	   IsolaError = 1;
	   s = 0;
   }
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

/* ---------------- Programm-Ausahl ----------------- */

static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

void ProgUsage( char *buf )
{
   Usage( buf );
   SetArticleNameUsage ( buf );
}

long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

   int mode = atoi(argv[0]);

   switch ( mode )
    {
      case 1:
        if ( argc == 5 )
        {
          s = SetArticleNameLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          SetArticleNameUsage( buf );
        }
        break;

	case 2:
        if ( argc == 5 )
        {
          s = SetReimbursementValFranceLoop( argv[1], argv[2], argv[3], argv[4], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          SetReimbursementValFranceUsage( buf );
        }
        break;

	case 3:
        if ( argc == 3 )
        {
          s = CreateNtinLoop( argv[1], argv[2], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          CreateNtinUsage( buf );
        }
        break;
	case 4:
		if ( argc == 2 )
		{
			s  = CreateProdNoLoop( argv[1], argv[2], buf );
		}
		else
		{
			s = 1;
			Usage(buf);
			CreateProdNoUsage(buf);
		}
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
