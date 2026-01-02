
/* ---------------------------------------------------------------------- *
 *                           P _ A L L P R O . C                          *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   Protokoll                                                    *
 * Modul:                                                                 *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  21.12.1998                                                   *
 * Update :  21.12.1998                                                   *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <phodate.h>
#include <libscsvoodoo.h>

#include "h_protok.h"

/* --- Prototype ---------------------------- */

void StoreHeaderTablename( char *bezeichnung );
void StorePrinfileName   ( char *bezeichnung );
void StorePrintfileDate  ( char *bezeichnung );

long CloseCs_Protinfo( char *errmld );
void ClosePrintFile( void );

char *GetCommandBuffer( void );
void FreeCommandBuffer( void );

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


/* --- Parameter scannen ------------------------------------------ */

static int ScanParam( char *param, int *b_ifa, int *aenart_ind, int *sort,
                      char *errmld )
{
   if ( *param != '-' )
   {
      strcpy( errmld, "- vor [ip] fehlt\n" );
      return 1;
   }

   /* default-Werte */
   *b_ifa = 0;
   *aenart_ind = AE_AEND;
   *sort = 0;

   param++;
   if ( *param != '\0' )
   {
      if ( *param >= '0'  && *param <= '1' )
         *b_ifa = (int)( *param - '0' );
      else
      {
        strcpy( errmld, "Parameter i von [ips]: 0 <= i <= 1\n" );
        return 1;
      }
      param++;
      if ( *param != '\0' )
      {
        if ( *param >= '1'  && *param <= '7' )
          *aenart_ind = (int)( *param - '0' );
        else
        {
          strcpy( errmld, "Parameter p von [ips]: 1 <= p <= 7\n" );
          return 1;
        }
        param++;
        if ( *param != '\0' )
        {
          if ( *param >= '0'  && *param <= '1' )
            *sort = (int)( *param - '0' );
          else
          {
            strcpy( errmld, "Parameter s von [ips]: 0 <= s <= 1\n" );
            return 1;
          }
        }
      }
   }

   return 0;
}

static long WandleDatum( char *datstr, char *errmld )
{
  long datum;
  if ( datstr == NULL )
  {
    return 0;
  }
  if ( strlen( datstr ) != 10 ||
       ConvToPhoDate ( datstr, &datum, "tt.mm.jjjj" ) == 0 )
  {
     strcpy( errmld, "Datum in der Form tt.mm.jjjj" );
     return -1;
  }
  return datum;
}

static int TestParam( char *param, char *von_datum, char *bis_datum,
                      int *b_ifa, int *aenart_ind, int *sort,
                      long *von_date, long *bis_date,
                      char *errmld )
{
   if ( ScanParam( param, b_ifa, aenart_ind, sort, errmld ) != 0 )
     return 1;

   *von_date = WandleDatum( von_datum, errmld );
   *bis_date = WandleDatum( bis_datum, errmld );
   if ( *von_date == -1 )
      return 1;
   if ( *bis_date == -1 )
      return 1;

   if ( *von_date == 0 && *bis_date == 0 )
        *von_date = GetPhoDate();
   return 0;
}


static void MakeLower( char *str )
{
  while ( *str )
  {
     *str = (char) tolower( *str );
     str++;
  }
}

/* ------------------------- Zartikel ------------------------- */

long ArtProtSortNumb( char *relation, int b_ifa, int aenart_ind,
                      long von_date, long bis_date, char *buf );

long ArtProtSortDate( char *relation, int b_ifa, int aenart_ind,
                      long von_date, long bis_date, char *buf );


long ArtikelProtokol( char *db, char *param, char *von_datum, char *bis_datum,
                      char *buf )
{
   int  b_ifa;
   int  aenart_ind;
   int  sort;
   long von_date;
   long bis_date;
   long s;
   char *relation;
   char *bezeichnung;

   if ( TestParam( param, von_datum, bis_datum, &b_ifa, &aenart_ind, &sort,
                   &von_date, &bis_date, buf ) != 0 )
     return 1;

   if ( OpenBase( db, buf ) != 0 )
     return 1;

   relation    = "zartikel";
   bezeichnung = "zentraler artikel";
   StoreHeaderTablename( bezeichnung );
   StorePrinfileName( "artikel" );

   if ( bis_date <= 0 || von_date == bis_date )
   {
		char cFromDate [20];
		sprintf (cFromDate, "%ld", von_date);
		StorePrintfileDate(cFromDate);
   }
   else
   {
		char cFromDate [20];
		sprintf (cFromDate, "%ld_%ld", von_date, bis_date);
		StorePrintfileDate(cFromDate);
   }

   if ( sort == 0 )
     s = ArtProtSortDate( relation,
                          b_ifa, aenart_ind, von_date, bis_date, buf );
   else
     s = ArtProtSortNumb( relation,
                          b_ifa, aenart_ind, von_date, bis_date, buf );

   CloseCs_Protinfo( NULL );
   CloseBase(  );
   ClosePrintFile( );

   if ( s == 0 )
   {
/*    h_system( GetCommandBuffer(  ) );  */
      FreeCommandBuffer( );
      strcpy( buf, "Protokoll wurde erstellt" );
      return 0;
   }
   else
   {
      FreeCommandBuffer( );
      return 1;
   }
}

/* -------------------- Relationen allgemein ----------------- */

long RelProtSortDate( char *relation, int b_ifa, int aenart_ind,
                      long von_date, long bis_date, char *buf );

long RelProtSortNumb( char *relation, int b_ifa, int aenart_ind,
                      long von_date, long bis_date, char *buf );

long RelationProtokol( char *db, char *relation, char *param,
                       char *von_datum, char *bis_datum, char *buf )
{
   int  b_ifa;
   int  aenart_ind;
   int  sort;
   long von_date;
   long bis_date;
   long s;
   char bezeichnung[50];

   if ( TestParam( param, von_datum, bis_datum, &b_ifa, &aenart_ind, &sort,
                   &von_date, &bis_date, buf ) != 0 )
     return 1;

   if ( OpenBase( db, buf ) != 0 )
     return 1;

   MakeLower( relation );
   strcpy( bezeichnung, "relation \"" );
   strcat( bezeichnung, relation );
   strcat( bezeichnung, "\"" );
   StoreHeaderTablename( bezeichnung );
   StorePrinfileName( relation );

   if ( bis_date <= 0 || von_date == bis_date )
   {
		char cFromDate [20];
		sprintf (cFromDate, "%ld", von_date);
		StorePrintfileDate(cFromDate);
   }
   else
   {
		char cFromDate [20];
		sprintf (cFromDate, "%ld_%ld", von_date, bis_date);
		StorePrintfileDate(cFromDate);
   }

   if ( sort == 0 )
     s = RelProtSortDate( relation,
                          b_ifa, aenart_ind, von_date, bis_date, buf );
   else
     s = RelProtSortNumb( relation,
                          b_ifa, aenart_ind, von_date, bis_date, buf );

   CloseCs_Protinfo( NULL );
   CloseBase(  );
   ClosePrintFile( );

   if ( s == 0 )
   {
/*    h_system( GetCommandBuffer(  ) );  */
      FreeCommandBuffer( );
      strcpy( buf, "Protokoll wurde erstellt" );
      return 0;
   }
   else
   {
      FreeCommandBuffer( );
      return 1;
   }

}

