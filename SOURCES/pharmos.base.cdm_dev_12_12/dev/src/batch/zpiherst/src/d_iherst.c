
/* ---------------------------------------------------------------------- *
 *                            d_iherst.c                                  *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Loescht die IFA-Herstellerdatei ais der Relation      *
 *                  zifaher                                               *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 25.09.98                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

#include <zifaher.h>

/* --- Prototype  ------------------------------------------------------- */

void CloseBase( void );
long OpenBase ( char *db, char *errmld );

/* --- Loeschen ------------------------------------------------------ */


static long FirstRecord( long ifanr, long * satznr, char *errmld )
{
   char sql[200];
   long status;
   sprintf( sql,
            "select H_SATZNR from ZIFAHER where H_IFANR=%ld " \
            "order by H_SATZNR",
            ifanr );
   status = SqlRead( sql, satznr, NULL );
   if ( status != 0 )
   {
     strcpy( errmld, "zifaher 1. Satz:\n" );
     strcat( errmld, DynErrmld() );
   }
   return status;
}

static long LastRecord( long ifanr, long * satznr, char *errmld )
{
   char sql[200];
   long status;
   sprintf( sql,
            "select H_SATZNR from ZIFAHER where H_IFANR=%ld " \
            "order by H_SATZNR desc",
            ifanr );
   status = SqlRead( sql, satznr, NULL );
   if ( status != 0 )
   {
     strcpy( errmld, "zifaher letzter Satz:\n" );
     strcat( errmld, DynErrmld() );
   }
   return status;
}


static long delete_all( long ifanr, long satznr, char *errmld )
{
   char sql[200];
   long status;
   sprintf ( sql,
             "delete from zifaher where H_IFANR=%ld and H_SATZNR<=%ld",
             ifanr,
             satznr );

   status = SqlExecuteImm ( sql );
   if ( status != 0 )
   {
     strcpy( errmld, "zifaher delete_all:\n" );
     strcat( errmld, DynErrmld() );
   }
   return status;

}

static long delete_ifadatei( long ifanr, char *errmld )
{
   long satznr1;
   long satznr2;
   long status;

   status =  FirstRecord( ifanr, &satznr1, errmld );
   if ( status != 0 ) return status;
   status =  LastRecord ( ifanr, &satznr2, errmld );
   if ( status != 0 ) return status;
   while ( status == 0 && satznr1 <= satznr2 )
   {
      satznr1 += 100;
      status = delete_all( ifanr, satznr1, errmld );
   }
   return status;
}

long DeleteIfaHer( char *db, long ifadatum, char *errmld )
{
   long status;

   status = OpenBase( db, errmld );
   if ( status == 0 )
   {
      status = delete_ifadatei( ifadatum, errmld );
      CloseBase( );
   }

    if ( status != 0 )
      return 1;
    strcpy( errmld, "Loeschen erfolgreich" );
    return 0;
}


