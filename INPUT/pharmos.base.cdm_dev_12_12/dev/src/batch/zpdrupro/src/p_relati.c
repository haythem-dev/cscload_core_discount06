
/* ---------------------------------------------------------------------- *
 *                           P _ R E L A T . C                            *
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

#include <phodate.h>
#include <libscsvoodoo.h>

#include <wpp_prot.h>

#include "h_protok.h"

/* --- Prototype ---------------------------- */

long Lese_Info( char *tabelle, long protokol_nr, char *aen_art,
                int *diffsqld, char *errrmld );
long Show_Info( char *tabelle, char *aen_art, int NoVglSpez, int diffsqld,
                long datum, long uhrzeit,
                char *key_select, char *user, char *errmld );

/* --- Protokol ---------------------------------------------------- */

void CloseCs_Protokoll( int fd )
{
  if ( fd != -1 )
    SqlCloseCs( fd );
}

long FetchProtokoll( int fd, struct s_PROTOKOL *prot, char *errmld )
{
   long s;
   s = SqlFetch( fd, 1, prot, NULL );
   if ( !( s == 0 || s == 100 ) )
      sprintf( errmld, "PROTOKOL:\n%s\n", DynErrmld() );
   return s;
}

long OpenProtokoll( int *fd, char *sql, char *errmld )
{
   long s;
   s = SqlOpenCsWh( fd, sql );
   if ( s != 0 )
   {
      *fd = -1;
      sprintf( errmld, "PROTOKOL:\n%s\n", DynErrmld() );
   }
   return s;
}


void GetAllSelect( char *sql, char *relation, long von_date, long bis_date,
                int aenart_index, int b_ifa, char *order_by, char *sql_bed )
{
   char aen_kenn[50];

   sprintf( sql, "select %s from protokol where relation='%s' and datum",
                 p_PROTOKOL,
                 relation );

   if ( bis_date == 0 )
     sprintf( &sql[strlen(sql)], "=%ld", von_date );
   else
     sprintf( &sql[strlen(sql)], ">=%ld and datum<=%ld", von_date, bis_date );

   if ( aenart_index != AE_ALLES )
   {
     strcat( sql, " and " );
     if ( aenart_index == AE_AEND )
       sprintf( aen_kenn, "aenderungsart='%c'", P_UPDATE );
     else if ( aenart_index == AE_NEU )
       sprintf( aen_kenn, "aenderungsart='%c'", P_INSERT );
     else if ( aenart_index == AE_LOESCH )
       sprintf( aen_kenn, "aenderungsart='%c'", P_DELETE );
     else if ( aenart_index == AE_AEND_NEU )
       sprintf( aen_kenn, "(aenderungsart='%c' or aenderungsart='%c')",
                P_UPDATE,
                P_INSERT );
     else if ( aenart_index == AE_AEND_LOESCH )
       sprintf( aen_kenn, "(aenderungsart='%c' or aenderungsart='%c')",
                P_UPDATE,
                P_DELETE );
     else if ( aenart_index == AE_NEU_LOESCH )
       sprintf( aen_kenn, "(aenderungsart='%c' or aenderungsart='%c')",
                P_INSERT,
                P_DELETE );
     strcat( sql, aen_kenn );
   }

   if ( b_ifa == 0 )
   {
     strcat( sql, " and anwender!='IFA     ' and anwender!='IFA-FEB '" );
     strcat( sql, " and anwender!='PHAGROFR' and anwender!='dc'" );
   }

   if ( sql_bed != NULL )
   {
     strcat( sql, " and " );
     strcat( sql, sql_bed );
   }

   strcat( sql, " order by " );
   if ( order_by == NULL )
      strcat( sql, "protokol_nr" );
   else
      strcat( sql, order_by );

/* printf ("%s\n", sql ); */

}

static long RelProt( char *relation, int b_ifa, int aenart_ind,
                     long von_date, long bis_date, char *order_by, char *buf )
{
   long s;
   long s1;
   long s2;
   int  fd;
   int  diffsqld;
   struct s_PROTOKOL prot;
   char sql[450+150];

   GetAllSelect( sql, relation, von_date, bis_date, aenart_ind, b_ifa,
                 order_by, NULL );

   s = OpenProtokoll( &fd, sql, buf );

   if ( s != 0 )
     return s;

   s = FetchProtokoll( fd, &prot, buf );
   if ( s == 100 )
   {
      CloseCs_Protokoll( fd );
      sprintf( buf, "PROTOKOL:\n%s\n", "Kein Satz vorhanden" );
      return s;
   }

   s1 = 0;
   s2 = 0;
   while ( s == 0 && s1 == 0 && s2 == 0 )
   {
      s1 = Lese_Info( relation, prot.PROTOKOL_NR, prot.AENDERUNGSART,
                      &diffsqld, buf );
      if ( s1 == 100 )
        s1 = 0;
      else
        s2 = Show_Info( relation, prot.AENDERUNGSART, 1, diffsqld,
                        prot.DATUM, prot.UHRZEIT,
                        prot.KEY_SELECT, prot.ANWENDER, buf );

      if ( s1 == 0 && s2 == 0 )
         s = FetchProtokoll( fd, &prot, buf );
   }

   CloseCs_Protokoll( fd );
   if ( s1 != 0 ) return s1;
   if ( s2 != 0 ) return s2;
   if ( s == 100 ) s = 0;
   return s;
}

long RelProtSortDate( char *relation, int b_ifa, int aenart_ind,
                      long von_date, long bis_date, char *buf )
{
   return RelProt( relation, b_ifa, aenart_ind,
                   von_date, bis_date, NULL, buf );
}

long RelProtSortNumb( char *relation, int b_ifa, int aenart_ind,
                      long von_date, long bis_date, char *buf )
{
   return RelProt( relation, b_ifa, aenart_ind,
                   von_date, bis_date, "key_select", buf );
}

