
/* ---------------------------------------------------------------------- *
 *                           P _ A R T R E L . C                          *
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
long Show_Info_Preis( char *tabelle, char *aen_art, int diffsqld,
                      long datum, long uhrzeit, char *key_select, char *user,
                      char *errmld, void *preis_buf );

long OpenProtokoll    ( int *fd, char *sql, char *errmld );
long FetchProtokoll   ( int  fd, struct s_PROTOKOL *prot, char *errmld );
void CloseCs_Protokoll( int  fd );

void remove_blank( char *str );

void PosNextPage( void );

long GetArtikelNrFromKey( char *key_sel );


/* -------------------------------------------------------------- *
 *       Interner GetSelect                                       *
 * -------------------------------------------------------------- */

void GetAllSelect( char *sql, char *relation, long von_date, long bis_date,
                  int aenart_index, int b_ifa, char *order_by, char *sql_bed );

static void GetSelect( char *sql, char *relation, long von_date, long bis_date,
                       int aenart_index, int b_ifa, char *sql_bed   )
{
   GetAllSelect( sql, relation, von_date, bis_date,
                 aenart_index, b_ifa, NULL, sql_bed );
}


/* -------------------------------------------------------------- *
 *  Zartikel: Protokoll-Nr des naechsten Artikel mit gleicher PZN *
 *            im Protokoll lesen                                  *
 * -------------------------------------------------------------- */

static int fd_nextart = -1;

static long DeclCsWh_NextArtikel( char *errmld )
{
   long s;
   char sql[200];

   if ( fd_nextart != -1 ) return 0;

   sprintf( sql,
            "select PROTOKOL_NR,KEY_SELECT from PROTOKOL " \
            "where PROTOKOL_NR>? and RELATION='zartikel          ' " \
            "order by PROTOKOL_NR" );

   s = SqlDeclareCs ( &fd_nextart, sql, "PROTOKOL.PROTOKOL_NR",
                                        NULL );
   if ( s  != 0 )
   {
      fd_nextart = -1;
      strcpy( errmld, DynErrmld() );
   }
   return s;
}

long CloseCs_NextArtikel( char *errmld )
{
   long s;
   if ( fd_nextart == -1 ) return 0;
   s = SqlCloseCs( fd_nextart );
   if ( s != 0 && errmld != NULL )
   {
     strcpy( errmld, "CloseCs_NextArtikel : " );
     strcat( errmld, DynErrmld() );
   }
   fd_nextart = -1;
   return s;
}


static long ArtikelNr_from_KeySelect( char *key_select )
{
   long artikel_nr;
   artikel_nr = -1;
   while ( *key_select && *key_select != '=' ) key_select++;
   if ( *key_select != '\0' )
     artikel_nr = atol( ++key_select );
   return artikel_nr;
}

static long Fetch_NextArtikel( long protokol_nr, char* key_select,
                               long *neue_protokol_nr, char *errmld )
{
   long s;
   long artikel_nr;
   long next_artikel_nr;
   long next_protokol_nr;
   char next_key_select[L_PROTOKOL_KEY_SELECT + 1];

   *neue_protokol_nr = -1;

   s = DeclCsWh_NextArtikel( errmld );
   if ( s != 0 ) return s;

   s = SqlReadDeclCs ( fd_nextart,
                       &next_protokol_nr, next_key_select, NULL,
                       &protokol_nr, NULL );

   if ( !( s == 0 || s == 100 ) )
   {
     strcpy( errmld, "Fetch_NextArtikel:\n" );
     strcat( errmld, DynErrmld() );
   }
   if ( s == 100 )
     return s;

   artikel_nr      = ArtikelNr_from_KeySelect( key_select );
   next_artikel_nr = ArtikelNr_from_KeySelect( next_key_select );
   if ( artikel_nr == -1 || next_artikel_nr == -1 ||
        artikel_nr != next_artikel_nr )
     return 100;

   *neue_protokol_nr = next_protokol_nr;
   return 0;
}

/* -------------------------------------------------------------- *
 *       ZARTPREIS lesen                                          *
 * -------------------------------------------------------------- */

struct  Z_PREIS  {
   long    ARTIKEL_NR           ;
   long    DATUMGUELTIGAB       ;
   double  GROSSO               ;
   double  AEP                  ;
   double  AVP                  ;
   char    KE_MWST           [2];
   double  HERST_PROZENT        ;
 };

static struct Z_PREIS zpreis;

static char *proj_preis =
       "ARTIKEL_NR,DATUMGUELTIGAB,GROSSO,AEP,AVP,KE_MWST,HERST_PROZENT";

static int fd_preis = -1;

static long DeclCsWh_Preis( char *errmld )
{
   long s;
   char sql[200];

   if ( fd_preis != -1 ) return 0;

   sprintf( sql,
            "select %s from ZARTPREIS where ARTIKEL_NR=? and DATUMGUELTIGAB<?"\
            " order by ARTIKEL_NR,DATUMGUELTIGAB desc",
            proj_preis );

   s = SqlDeclareCs ( &fd_preis, sql, "ZARTPREIS.ARTIKEL_NR",
                                      "ZARTPREIS.DATUMGUELTIGAB",
                                       NULL );
   if ( s  != 0 )
   {
      fd_preis = -1;
      strcpy( errmld, DynErrmld() );
   }
   return s;
}

long CloseCs_Preis( char *errmld )
{
   long s;
   if ( fd_preis == -1 ) return 0;
   s = SqlCloseCs( fd_preis );
   if ( s != 0 && errmld != NULL )
   {
     strcpy( errmld, "CloseCs_Preis : " );
     strcat( errmld, DynErrmld() );
   }
   fd_preis = -1;
   return s;
}

static long Fetch_Preis( long artikel_nr, long datum, char *errmld )
{
   long s;

   s = DeclCsWh_Preis( errmld );
   if ( s != 0 ) return s;

   s = SqlReadDeclCs ( fd_preis, &zpreis, NULL,
                       &artikel_nr, &datum, NULL );

   if ( !( s == 0 || s == 100 ) )
   {
     strcpy( errmld, "ZARTPREIS:\n" );
     strcat( errmld, DynErrmld() );
   }

   return s;
}

static long Lese_Preis( char *key_select, char *errmld )
{
  long artikel_nr;
  long datum;
  artikel_nr = -1;
  datum = -1;
  while ( *key_select && *key_select != '=' ) key_select++;
  if ( *key_select == '\0' ) return 100;
  artikel_nr = atol( ++key_select );
  while ( *key_select && *key_select != '=' ) key_select++;
  if ( *key_select == '\0' ) return 100;
  datum = atol( ++key_select );
  return Fetch_Preis( artikel_nr, datum, errmld );
}


long Show_Preis( struct s_PROTOKOL *prot, char *key_sel, int diffsqld,
                 char *buf  )
{
   long s;
   void *ref_zpreis;
   s = Lese_Preis( prot->KEY_SELECT, buf );
   if ( s == 0 )
      ref_zpreis = &zpreis;
   else
      ref_zpreis = NULL;
   if ( s == 0 || s == 100 )
      s = Show_Info_Preis( prot->RELATION, prot->AENDERUNGSART, diffsqld,
                           prot->DATUM, prot->UHRZEIT,
                           key_sel, prot->ANWENDER, buf, ref_zpreis );
   return s;
}


static long PreisProtokol( long von_date, long bis_date,
                           int b_ifa, struct s_PROTOKOL *art_prot,
                           long next_protokol_nr, long save_artikel_nr,
                           char *buf )
{
   long s;
   long s1;
   long s2;
   int  fd;
   int diffsqld;
   char *relation;
   char *key_sel;
   char sql[450+100];
   char sql_bed[160];
   char art_key_sel[L_PROTOKOL_KEY_SELECT + 1];
   struct s_PROTOKOL prot;
   char tmp[2];

   strcpy( tmp, " " );
   
   relation = "zartpreis";

   strcpy( art_key_sel, art_prot->KEY_SELECT );
   remove_blank( art_key_sel );

   if ( next_protokol_nr > art_prot->PROTOKOL_NR )
     sprintf( sql_bed, "PROTOKOL_NR>%ld and PROTOKOL_NR<%ld " \
                       "and ANWENDER='%s' and KEY_SELECT matches '%s*'",
                       art_prot->PROTOKOL_NR,
                       next_protokol_nr,
                       art_prot->ANWENDER,
                       art_key_sel );
   else
     sprintf( sql_bed, "PROTOKOL_NR>%ld " \
                       "and ANWENDER='%s' and KEY_SELECT matches '%s*'",
                       art_prot->PROTOKOL_NR,
                       art_prot->ANWENDER,
                       art_key_sel );

   GetSelect( sql, relation, von_date, bis_date, AE_ALLES, b_ifa, sql_bed );

   s = OpenProtokoll( &fd, sql, buf );
   if ( s != 0 )
   {
     return s;
   }

   s = FetchProtokoll( fd, &prot, buf );
   if ( s == 100 )
   {
      CloseCs_Protokoll( fd );
      sprintf( buf, "PROTOKOL:\n%s\n", "Kein ZARTPREIS-Satz vorhanden" );
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
      {
        if ( save_artikel_nr == GetArtikelNrFromKey( prot.KEY_SELECT ) )
           key_sel = tmp;
        else
           key_sel = prot.KEY_SELECT;

        s2 = Show_Preis( &prot, key_sel, diffsqld, buf );
      }
      if ( s1 == 0 && s2 == 0 )
         s = FetchProtokoll( fd, &prot, buf );
   }

   CloseCs_Protokoll( fd );

   if ( s == 100 )
      return 0;
   else
      return 1;
}

/* ------------------------- Zartwg / Ean ------------------------- */

static long Artwg_Ean_Protokol( char *relation,
                                long von_date, long bis_date,
                                int b_ifa, struct s_PROTOKOL *art_prot,
                                long next_protokol_nr, char *buf )
{
   long s;
   long s1;
   long s2;
   int  fd;
   int diffsqld;
   char sql[450+100];
   char sql_bed[160];
   char key_sel[L_PROTOKOL_KEY_SELECT + 1];
   struct s_PROTOKOL prot;
   char tmp[2];

   strcpy( tmp, " " );

   strcpy( key_sel, art_prot->KEY_SELECT );
   remove_blank( key_sel );

   if ( next_protokol_nr > art_prot->PROTOKOL_NR )
     sprintf( sql_bed, "PROTOKOL_NR>%ld and PROTOKOL_NR<%ld " \
                       "and ANWENDER='%s' and KEY_SELECT matches '%s*'",
                       art_prot->PROTOKOL_NR,
                       next_protokol_nr,
                       art_prot->ANWENDER,
                       key_sel );
   else
     sprintf( sql_bed, "PROTOKOL_NR>%ld " \
                       "and ANWENDER='%s' and KEY_SELECT matches '%s*'",
                       art_prot->PROTOKOL_NR,
                       art_prot->ANWENDER,
                       key_sel );

   GetSelect( sql, relation, von_date, bis_date, AE_ALLES, b_ifa, sql_bed );

   s = OpenProtokoll( &fd, sql, buf );
   if ( s != 0 )
   {
     return s;
   }

   s = FetchProtokoll( fd, &prot, buf );
   if ( s == 100 )
   {
      CloseCs_Protokoll( fd );
      sprintf( buf, "PROTOKOL:\n%s\n", "Kein ZARTWG-Satz vorhanden" );
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
        s2 = Show_Info( relation, prot.AENDERUNGSART, 0, diffsqld,
                        prot.DATUM, prot.UHRZEIT,
                        tmp, prot.ANWENDER, buf );
                  /*    prot.KEY_SELECT, prot.ANWENDER, buf );  */
                  /* Keyselect wird nicht gedruckt */

      if ( s1 == 0 && s2 == 0 )
         s = FetchProtokoll( fd, &prot, buf );
   }

   CloseCs_Protokoll( fd );

   if ( s == 100 )
      return 0;
   else
      return 1;
}


/* ------------------------- Zartsekbez ------------------------- */

#ifndef SEKBEZ_INTEGRIERT

static long Zartsekbez_Protokol( long von_date, long bis_date,
                                 int b_ifa, char *buf )
{
   long s;
   long s1;
   long s2;
   int  fd;
   int diffsqld;
   char *relation;
   char sql[450+100];
   struct s_PROTOKOL prot;

   relation = "zartsekbez";

   GetSelect( sql, relation, von_date, bis_date, AE_ALLES, b_ifa, NULL );

   s = OpenProtokoll( &fd, sql, buf );
   if ( s != 0 )
   {
     return s;
   }

   s = FetchProtokoll( fd, &prot, buf );
   if ( s == 100 )
   {
      CloseCs_Protokoll( fd );
      sprintf( buf, "PROTOKOL:\n%s\n", "Kein ZARTSEKBEZ-Satz vorhanden" );
      return s;
   }

   PosNextPage();   /* Neue Seite anfangen */

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

   if ( s == 100 )
      return 0;
   else
      return 1;
}


#endif


/* ------------------------- Zartikel ------------------------- */

long ArtProtSortDate( char *relation, int b_ifa, int aenart_ind,
                      long von_date, long bis_date, char *buf )
{
   long s;
   long s1;
   long s2;
   long save_artikel_nr;
   int  fd;
   int diffsqld;
   long next_protokol_nr;
   struct s_PROTOKOL prot;
   char sql[450+100];
   char key_sel[100];
   char sel_mc[500];
   char matchcode[51];
   char articlecode[31];

   GetSelect( sql, relation, von_date, bis_date, aenart_ind, b_ifa, NULL );

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
       memset(key_sel, '\0', 100);
	   memset(matchcode, '\0', 50);
	   s1 = Lese_Info( relation, prot.PROTOKOL_NR, prot.AENDERUNGSART,
                      &diffsqld, buf );
      
	  save_artikel_nr = GetArtikelNrFromKey( prot.KEY_SELECT );
		  
	  if ( s1 == 100 )
        s1 = 0;
      else
	  {
		//sprintf(key_sel, "%07ld ", save_artikel_nr);
		sprintf(sel_mc, "select artikel_mc, article_code from zartikel, carticlecodes "
							"where artikel_nr = %ld and artikel_nr = articleno and preferred_flag = 1 and code_type in (select code_type from ccodetypes where artnr_substitute = 1)", 
							save_artikel_nr);
		SqlRead(sel_mc, matchcode, articlecode, NULL  );   
		sprintf(key_sel, "%08ld ", atoi(articlecode));
		strcat(key_sel, matchcode);

        s2 = Show_Info( relation, prot.AENDERUNGSART, 0, diffsqld,
                        prot.DATUM, prot.UHRZEIT,
                        key_sel, prot.ANWENDER, buf );
	  }

      if ( s1 == 0 && s2 == 0 )
      {
		  s = Fetch_NextArtikel( prot.PROTOKOL_NR, prot.KEY_SELECT, 
                                &next_protokol_nr, buf );
         if ( s == 100 || s == 0 )
         {
           s = Artwg_Ean_Protokol( "zartwg",
                                   von_date, bis_date, b_ifa, &prot,
                                   next_protokol_nr, buf );
           if ( s == 100 || s == 0 )
           {
              s = Artwg_Ean_Protokol( "ean",
                                      von_date, bis_date, b_ifa, &prot,
                                      next_protokol_nr, buf );
#ifdef SEKBEZ_INTEGRIERT
              if ( s == 100 || s == 0 )
              {
                 s = Artwg_Ean_Protokol( "zartsekbez",
                                         von_date, bis_date, b_ifa, &prot,
                                         next_protokol_nr, buf );
#endif
                 if ( s == 100 || s == 0 )
                 {
                   s = PreisProtokol( von_date, bis_date, b_ifa, &prot,
                                      next_protokol_nr, save_artikel_nr, buf );
                   if ( s == 100 || s == 0 )
                       s = FetchProtokoll( fd, &prot, buf );
                 }
#ifdef SEKBEZ_INTEGRIERT
              }
#endif
           }
         }
      }
   }

#ifndef SEKBEZ_INTEGRIERT

   if ( s1 == 0 && s2 == 0 && s == 100 )
   {
      s = Zartsekbez_Protokol( von_date, bis_date, b_ifa, buf );
      if ( s == 0 ) s = 100;
   }
#endif

   CloseCs_Preis( NULL );
   CloseCs_Protokoll( fd );

   if ( s1 != 0 ) return s1;
   if ( s2 != 0 ) return s2;
   if ( s == 100 ) s = 0;
   return s;
}


