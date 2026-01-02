/* ---------------------------------------------------------------------- *
 *                            ZPPROTOK. C                                 *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Manipuliert die Protokoll-Datei                     *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 09.07.98                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 2.1.0 : zpprotok 13.03.13 : Rolf Raab";

/*!
\page page31 zpprotok - Manipuliert die Protokoll-Datei
___________________________________________________________________________
\version	2.1.0
\date		13.03.2013
\internal
- TH: AIX build
\endinternal
___________________________________________________________________________
\version	2.0.6
\date		08.07.2008
\internal
- RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, Ausgabe Log auch bei Aufruf aus Windows (EkZdp).
\endinternal
___________________________________________________________________________
\version	2.0.5
\date		 02.04.2007
\internal
- RR: Ausgabe in Logfile
\endinternal
___________________________________________________________________________
\version	2.0.4
\date		11.12.2003
\internal
- Programm beschleunigen
\endinternal
___________________________________________________________________________
\version	2.0.3
\date		12.08.2003
\internal
- Datenbank variabel
\endinternal

*/

/* 2.0.3 : 12.08.03 : Datenbank variabel */
/* 2.0.4 : 11.12.03 : Programm beschleunigen */
/* 2.0.5 : 02.04.07 : RR: Ausgabe in Logfile */
/* 2.0.6 : 08.07.08 : RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						  Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 2.1.0 : 13.03.13 : TH: AIX build */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

/* ---------- prototype -------------------- */

long PrepareProtokolForDelete( char *errmld );
long ExecuteProtokolForDelete( long protokol_nr, char *errmld );
void FreeProtokolForDelete   ( void );

long Updinfo_DeclareCsWh( char *errmld );
long Updinfo_ReadDeclCs ( long protokol_nr, char *errmld );
void Updinfo_CloseDeclCs( void );

long SpezialLoesche ( long nr, long *count, char *errmld );
long ProtInfoLoesche( long nr, long *count, char *errmld );

/* --------------- Datum testen -------------------- */

static long TestDatum( char *S_datum, long *ab_datum, char *errmld )
{
   *ab_datum = 0;
   if ( strlen( S_datum ) != 10 ||
        ConvToPhoDate ( S_datum, ab_datum, "tt.mm.jjjj" ) == 0 )
   {
     strcpy( errmld, "Datum in der Form tt.mm.jjjj" );
     return 1;
   }
   if ( *ab_datum > GetPhoDate() )
   {
     strcpy( errmld, "Datum muss kleiner gleich Tagesdatum sein" );
     return 1;
   }
   return 0;
}


/* --------------- Tabellen-Namen testen ----------- */

static long TestTable( char *relation, int maxlng, char *table, char *errmld )
{
   int i;
   int j;
   int lng;
   char ze;

   lng = strlen( relation );
   if ( lng > maxlng )
   {
     sprintf( errmld, "Max Tabellen-Laenge = %d", maxlng );
     return 1;
   }

   j = 0;
   for ( i = 0; i < lng; i++ )
   {
     ze = relation[i];
     if ( ze != ' ' )
     {
       if ( isupper( ze ) )  ze = (char) tolower( ze );
       table[j++] = ze;
     }
   }
   for ( i = j; i < maxlng; i++ )
     table[i] = ' ';
   table[maxlng] = '\0';
   return 0;
}

/* --------------- Select generieren --------------- */

#define REL_ART 1
#define ALL_ART 0

static long GenSelect( char *S_datum, char *relation, char *sql, int *art, char *errmld )
{
   #define TAB_LEN 18
   long ab_datum;
   char table[TAB_LEN + 1];


   *art = ALL_ART;

   if ( S_datum == NULL )
   {
     ab_datum = AddDayToPhoDate ( GetPhoDate( ), -30 );
   }
   else
   {
     if ( TestDatum( S_datum, &ab_datum, errmld ) != 0 ) 
         return 1;
   }

   if ( relation != NULL )
   {
     *art = REL_ART;
     if ( TestTable( relation, TAB_LEN, table, errmld ) != 0 ) 
         return 1;
     sprintf( sql, "select PROTOKOL_NR from PROTOKOL where DATUM<=%ld" \
                   " and RELATION='%s'",
                   ab_datum,
                   table );
   }
   else
     sprintf( sql, "select PROTOKOL_NR from PROTOKOL where DATUM<=%ld",
                   ab_datum );

   return 0;
}

#define NO_MODE   -1
#define HALF_MODE  0
#define FULL_MODE  1

static long TestSelect( char *S_datum, char *relation, long *protokol_nr, int *mode, char *errmld )
{
    long s;
   long ab_datum;
   long nr_prot; 
   long nr_vert;
   char sql[200];

   *protokol_nr = 0;
   *mode = NO_MODE;

   if ( S_datum == NULL )
   {
     ab_datum = AddDayToPhoDate ( GetPhoDate( ), -30 );
   }
   else
   {
     if ( TestDatum( S_datum, &ab_datum, errmld ) != 0 ) 
         return 1;
   }

   if ( relation != NULL )
       return 0;

   sprintf ( sql, "select max(protokol_nr) from protokol where datum=(" \
                  "select max (datum) from protokol where datum<=%ld )",
                  ab_datum );
   s = SqlRead( sql, &nr_prot, NULL );
   if ( s == 100 )
       return 0;
   if ( s != 0 )
   {
     sprintf( errmld, "TestSelect: %s", DynErrmld() );
     return s;
   }
   if ( nr_prot == 0 )   /* keine Protokoll-Nr */
       return 0;

   sprintf ( sql, "select max(protokol_nr) from vertinfo where protokol_nr<%ld",
                  nr_prot );
   s = SqlRead( sql, &nr_vert, NULL );
   if ( s == 100 || nr_vert == 0 )
   {
        *protokol_nr = nr_prot;
        *mode = FULL_MODE;
        return 0;
    }
   if ( s != 0 )
   {
     sprintf( errmld, "TestSelect: %s", DynErrmld() );
     return s;
   }

   *protokol_nr = nr_vert;
   *mode = HALF_MODE;
   return 0;
}

/* --------------- Hauptschleife: Leseschleife ----- */

static long LeseLoop( char *sql, long *count, char *errmld )
{
   int  fd;
   long s;
   long protokol_nr;

/*  printf("%s\n%ld\n", sql, *count );   */

   s = SqlOpenCsWh( &fd, sql );
   if ( s == 0 )
   {
     s = SqlFetch( fd, 1, &protokol_nr, NULL );
     if ( s == 100 )
     {
        /* strcpy( errmld, "Kein Satz vorhanden\n" ); */
     }
     else if ( s != 0 )
     {
        strcpy( errmld, DynErrmld() );
     }
     else
     {
        while ( s == 0 )
        {
           s = Updinfo_ReadDeclCs ( protokol_nr, errmld );
           if ( s == 100 )
           {
              s = ExecuteProtokolForDelete( protokol_nr, errmld );
              if ( s == 0 ) (*count)++;
           }

           if ( s == 0 )
           {
             s = SqlFetch( fd, 1, &protokol_nr, NULL );
             if ( !( s == 0 || s == 100 ) )
                strcpy( errmld, DynErrmld() );
           }
        }
     }
     SqlCloseCs( fd );
     if ( s == 100 ) s = 0;  /* !!!!!!!!!!!!!!! */
   }
   else
   {
     strcpy( errmld, DynErrmld() );
   }

   return s;
}


#define ANZ_LOE_PROTINFO 250

long ProtInfoLoescheLoop( long max_nr, char *errmld )
{
    long s;
    long nr;
    long min_nr;
    long anz;
    int  bende;

    s = SqlRead( "select min(protokol_nr) from protinfo", &min_nr, NULL );
    if ( s != 0 )
    {
       sprintf( errmld, "Min_Nr: %s", DynErrmld() );
       return s;
    }   

/*  printf( "%ld %ld\n", min_nr, max_nr );  */

    if ( min_nr >= max_nr ) 
        return 0;

    bende = 0;
    nr = min_nr - 1;
    do
    {
        if ( nr + ANZ_LOE_PROTINFO < max_nr ) 
            nr += ANZ_LOE_PROTINFO;
        else
        {
            nr = max_nr;
            bende = 1;
        }
        s = ProtInfoLoesche( nr, &anz, errmld );

/*      printf( "%ld %ld\n", nr, anz );  */

    } while ( s == 0 && !bende );

    return 0;
}

#define ANZ_LOE 100

long SpezialLoop( long max_nr, long *count, char *errmld )
{
    long s;
    long nr;
    long min_nr;
    long anz;
    int  bende;

/*  printf("Spezialloop bis %ld\n", max_nr ); */


    s = SqlRead( "select min(protokol_nr) from protokol", &min_nr, NULL );
    if ( s != 0 )
    {
       sprintf( errmld, "Min_Nr: %s", DynErrmld() );
       return s;
    }

    /* loescht protinfo-Saetze ohne connect zu protokol-Saetzen */
    s = ProtInfoLoescheLoop( min_nr, errmld );
    if ( s != 0 )
        return s;

/*  printf( "%ld %ld\n", min_nr, max_nr ); */

    bende = 0;
    nr = min_nr - 1;
    do
    {
        if ( nr + ANZ_LOE < max_nr ) 
            nr += ANZ_LOE;
        else
        {
            nr = max_nr;
            bende = 1;
        }

        s = SpezialLoesche( nr, &anz, errmld );

/*      printf( "%ld %ld\n", nr, anz );  */

        if ( s == 0 )
            *count += anz;
    } while ( s == 0 && !bende );

    return 0;
}



/* ----- Eroeffnung --------- */

/* --- SET ISOLATION-Fehler bei SE -------------------------------------- */

#define SQL_SETISOLA_ERROR   (-554)

static void CloseBase(  )
{
   SqlExecuteImm( "close database" );
}

static long OpenBase( char *db, char *errmld )
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


void OutMeldung( long count, char *errmld )
{
    char meld[100];
    sprintf( meld,
             "%ld Protokolleintraege wurden geloescht", count );
    if ( *errmld )
        strcat( errmld, "\n" );
    strcat( errmld, meld );
}

static long MainLoop( char *db, char *S_datum, char *relation, char *errmld )
{
   long s;
   long protokol_nr;
   long count;
   int  mode;
   int  art;
   char sql[100];

   if ( GenSelect( S_datum, relation, sql, &art, errmld ) != 0 ) return 1;


   count = 0;

   s = OpenBase( db, errmld );
   if ( s == 0 )
   {
      s = Updinfo_DeclareCsWh( errmld );
      if ( s == 0 )
      {
         s = PrepareProtokolForDelete ( errmld );
         if ( s == 0 )
         {
            if ( art == ALL_ART )
            {
                s = TestSelect( S_datum, relation, &protokol_nr, &mode, errmld );
                if ( s == 0 )
                {
                    *errmld = '\0';
                    if ( mode != NO_MODE )
                        s = SpezialLoop( protokol_nr, &count, errmld );
                    if ( s == 0 && mode != FULL_MODE )
                        s = LeseLoop( sql, &count, errmld );
                    OutMeldung( count, errmld );
                }
            }
            else
            {
                s = LeseLoop( sql, &count, errmld );
                OutMeldung( count, errmld );
            }
            FreeProtokolForDelete (  );
         }
         Updinfo_CloseDeclCs(  );

         /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
         SqlExecuteImm("update statistics for table protokol" );
         SqlExecuteImm("update statistics for table protinfo" );
      }
      CloseBase( );
   }

   return s;
}


/* ---------------- Programm-Ausahl ----------------- */

static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

static void ProgUsage_1( char *buf )
{
   strcat( buf, "- zpprotok 1 database datum\n" );
   strcat( buf, "  Protokol loeschen bis datum\n" );
}

static void ProgUsage_2( char *buf )
{
   strcat( buf, "- zpprotok 2 database datum relation\n" );
   strcat( buf, "  Protokol von relation loeschen bis datum\n" );
}

static void ProgUsage_3( char *buf )
{
   strcat( buf, "- zpprotok 3 database\n" );
   strcat( buf, "  Protokol loeschen bis Tagesdatum - 30 Tage\n" );
}


void ProgUsage( char *buf )
{
   Usage( buf );
   ProgUsage_1( buf );
   ProgUsage_2( buf );
   ProgUsage_3( buf );
}


long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;
 
   switch ( *argv[0] )
    {
      case '1':
        if ( argc == 3 )
        {
           s = MainLoop( argv[1], argv[2], NULL, buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          ProgUsage_1( buf );
        }
        break;
      case '2':
        if ( argc == 4 )
        {
          s = MainLoop( argv[1], argv[2], argv[3], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          ProgUsage_2( buf );
        }
        break;
      case '3':
        if ( argc == 2 )
        {
          s = MainLoop( argv[1], NULL, NULL, buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          ProgUsage_3( buf );
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


