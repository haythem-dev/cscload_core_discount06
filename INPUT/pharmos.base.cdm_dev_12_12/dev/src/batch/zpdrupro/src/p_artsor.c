
/* ---------------------------------------------------------------------- *
 *                           P _ A R T S O R . C                          *
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

long OpenProtokoll    ( int *fd, char *sql, char *errmld );
long FetchProtokoll   ( int  fd, struct s_PROTOKOL *prot, char *errmld );
void CloseCs_Protokoll( int  fd );

long Show_Preis( struct s_PROTOKOL *prot, char *key_sel, int diffsqld, char *buf  );
long CloseCs_Preis( char *errmld );

/* ----------------- Select -------------------------------- */

static void ArtSortSelect( char *sql, long von_date, long bis_date,
                           int aenart_index, int b_ifa,
                           char *sql_bed )
{
   char aen_kenn[50];

   if ( aenart_index == AE_ALLES )
   {
     strcpy( aen_kenn, "" );
   }
   else
   {
     if ( aenart_index == AE_AEND )
       sprintf( aen_kenn, " and aenderungsart='%c'", P_UPDATE );
     else if ( aenart_index == AE_NEU )
       sprintf( aen_kenn, " and aenderungsart='%c'", P_INSERT );
     else if ( aenart_index == AE_LOESCH )
       sprintf( aen_kenn, " and aenderungsart='%c'", P_DELETE );
     else if ( aenart_index == AE_AEND_NEU )
       sprintf( aen_kenn, " and (aenderungsart='%c' or aenderungsart='%c')",
                P_UPDATE,
                P_INSERT );
     else if ( aenart_index == AE_AEND_LOESCH )
       sprintf( aen_kenn, " and (aenderungsart='%c' or aenderungsart='%c')",
                P_UPDATE,
                P_DELETE );
     else if ( aenart_index == AE_NEU_LOESCH )
       sprintf( aen_kenn, " and (aenderungsart='%c' or aenderungsart='%c')",
                P_INSERT,
                P_DELETE );
   }


   sprintf( sql, "select %s from protokol where " \
                 "((relation='zartikel'%s) or relation='ean'" \
                 " or relation='zartwg' or relation='zartpreis'" \
                 " or relation='zartsekbez' or relation='zartaustria'" \
				 " or relation='zartswitzerland' or relation='carticlelang')" \
                 " and datum",
                 p_PROTOKOL,
                 aen_kenn );

   if ( bis_date == 0 )
     sprintf( &sql[strlen(sql)], "=%ld", von_date );
   else
     sprintf( &sql[strlen(sql)], ">=%ld and datum<=%ld", von_date, bis_date );

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

   strcat( sql, " order by key_select,protokol_nr" );

/* printf ("%s\n", sql ); */

}


long GetArtikelNrFromKey( char *key_sel )
{
   while( *key_sel != '=' ) key_sel++;
   if ( *key_sel != '=' ) return 0;
   return atol( ++key_sel );
}

/* ------------------------- Zartikel ------------------------- */

long ArtProtSortNumb( char *relation, int b_ifa, int aenart_ind,
                      long von_date, long bis_date, char *buf )
{
   long s;
   long s1;
   long s2;
   long save_artikel_nr;
   int  fd;
   int  diffsqld;
   char key_sel[100];
   struct s_PROTOKOL prot;
   char sql[850+150];
   char matchcode[51];
   char articlecode[31];
   char sel_mc[500];
   long artnr_temp;
		   

   ArtSortSelect( sql, von_date, bis_date, aenart_ind, b_ifa,
                  NULL );

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

   save_artikel_nr = -1;

   s1 = 0;
   s2 = 0;
   while ( s == 0 && s1 == 0 && s2 == 0 )
   {
		memset(key_sel, '\0', 100);
		memset(matchcode, '\0', 50);

	   	   s1 = Lese_Info( prot.RELATION, prot.PROTOKOL_NR, prot.AENDERUNGSART,
                      &diffsqld, buf );

      if ( s1 == 0 )
      {
        if ( memcmp( prot.RELATION, "zartikel", 8 ) == 0 )
        {
           save_artikel_nr = GetArtikelNrFromKey( prot.KEY_SELECT );
           
		   sprintf(sel_mc, "select artikel_mc, article_code from zartikel, carticlecodes "
							"where artikel_nr = %ld and artikel_nr = articleno and preferred_flag = 1 and code_type in (select code_type from ccodetypes where artnr_substitute = 1)", 
							save_artikel_nr);
		   SqlRead(sel_mc, matchcode, articlecode, NULL  );   
		   sprintf(key_sel, "%08ld ", atoi(articlecode));
		   strcat(key_sel, matchcode);
        }
        else
        {
           if ( save_artikel_nr == GetArtikelNrFromKey( prot.KEY_SELECT ) )
		   {
			  key_sel[0] = ' ';
			  key_sel[1] = '\0';
		   }
           else
		   {
              artnr_temp = GetArtikelNrFromKey( prot.KEY_SELECT );
			  
			  sprintf(sel_mc, "select artikel_mc, article_code from zartikel, carticlecodes "
							"where artikel_nr = %ld and artikel_nr = articleno and preferred_flag = 1 and code_type in (select code_type from ccodetypes where artnr_substitute = 1)", 
							artnr_temp);
			  SqlRead(sel_mc, matchcode, articlecode, NULL  );   
			  sprintf(key_sel, "%08ld ", atoi(articlecode));
			  strcat(key_sel, matchcode);	
		   }
        }

        if ( memcmp( prot.RELATION, "zartpreis", 9 ) != 0 )
           s2 = Show_Info( prot.RELATION, prot.AENDERUNGSART, 0, diffsqld,
                           prot.DATUM, prot.UHRZEIT,
                           key_sel, prot.ANWENDER, buf );
         else
           s2 = Show_Preis( &prot, key_sel, diffsqld, buf );

      }
      if ( s1 == 0 && s2 == 0 )
         s = FetchProtokoll( fd, &prot, buf );

   }

   CloseCs_Preis( NULL );
   CloseCs_Protokoll( fd );

   if ( s1 != 0 ) return s1;
   if ( s2 != 0 ) return s2;
   if ( s == 100 ) s = 0;
   return s;
}

