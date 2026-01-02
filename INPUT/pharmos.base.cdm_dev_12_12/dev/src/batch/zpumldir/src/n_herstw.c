
/* ---------------------------------------------------------------------- *
 *                           N _ H E R S T W . C                          *
 * ---------------------------------------------------------------------- *
 * Projekt:  Zentrale Pflege                                              *
 * Gruppe:   Umlisten                                                     *
 * Modul:    Herstellerwechsel                                            *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  09.12.1998                                                   *
 * Update :  09.12.1998                                                   *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <eklibs/hconfkt/hconfkt.h>

#include <voodoo_table_header/artnrbl.h>

#include "n_basic.h"

#define LNG_ZAHL     5
#define L_BESLA_NR   5
#define L_ARTIKEL_NR 7
#define L_ANWENDER   8
#define LNG_AEN     11


/* ------------- Umwandel-Funktionen --------------- */

static void anz_cpy ( char *str1, char *str2, int lng )
{
    memcpy( str1, str2, lng );
    str1[lng] = '\0';
}

static long Loesche_Alles( long besla_nr, long artikel_nr, char *errmld )
{
   long s;

   /* bliesort loeschen */
   s = Lese_Bliesort( besla_nr, artikel_nr, errmld );
   if ( s == 0 )
       s = Delete_Bliesort( besla_nr, artikel_nr, errmld );
   else if ( s == 100 )
       s = 0;

   /* Artikel-Nr Bliefer loeschen ???? */
   if ( s == 0 )
   {
      char nr_bliefer_vorh[50];
      s = Lese_Artnrbl( besla_nr, artikel_nr, nr_bliefer_vorh, errmld );
      if ( s == 0 )
         s = Delete_Artnrbl( besla_nr, artikel_nr, nr_bliefer_vorh, errmld );
      else if ( s == 100 )
         s = 0;
   }

   return s;
}

static long Einfuege_Alles( long besla_nr, long artikel_nr, char *art_nr_bl,
                            char *errmld )
{
   long s;

   /* bliesort einfuegen */

   s = Lese_Bliesort( besla_nr, artikel_nr, errmld );
   if ( s == 100 )
      s = Insert_Bliesort( besla_nr, artikel_nr, errmld );

   /* Artikel-Nr Bliefer einfuegen */
   if ( s == 0 && *art_nr_bl )
   {
      char nr_bliefer_vorh[50];
      s = Lese_Artnrbl( besla_nr, artikel_nr, nr_bliefer_vorh, errmld );
      if ( s == 100 )
         s = Insert_Artnrbl( besla_nr, artikel_nr, art_nr_bl, errmld );
      else if ( s == 0 )
      {
        /* nix machen */
        /* oder updaten ????? */
      }
   }

   return s;
}

static long Do_HerstWechsel( char *r_info, int r_lng, char *errmld, char *db )
{
    char *r_str;
    char *a_str;
    long  artikel_nr;
    long  besla_nr;
    long  besla_nr_pflege;
    long  s;
    int   anz;
    char  art_nr_bl[L_ARTNRBL_ARTIKEL_NR_BLIEFER + 1];
    char user[L_ANWENDER + 1];

    r_info[r_lng] = '\0';
    r_str = r_info;

    if ( r_lng < L_ANWENDER + L_ARTIKEL_NR )
    {
       strcpy( errmld, "Uebergabe-Parameter falsch" );
       return -1;
    }


    anz_cpy( user, r_str, L_ANWENDER );          r_str += L_ANWENDER;
    artikel_nr = s_atol( r_str, L_ARTIKEL_NR );  r_str += L_ARTIKEL_NR;

    if ( OnFirst( user, errmld ) != 0 ) return -1;
    if ( OpenForHerwechsel( errmld )!= 0 ) return -1;

    /* nur hier zaneuheit */

    if ( StartTransaction( errmld ) != 0 ) return -1;

    besla_nr_pflege = 0;

    s = 0;
    while ( *r_str && s == 0 )
    {
       if ( *r_str == 'x' )      /* Loeschen */
       {
         r_str++;
         besla_nr = s_atol( r_str, L_BESLA_NR );  r_str += L_BESLA_NR;
         s = Loesche_Alles( besla_nr, artikel_nr, errmld );
       }
       else if ( *r_str == 'n' ) /* Neuaufnahme */
       {
         r_str++;
         besla_nr = s_atol( r_str, L_BESLA_NR );  r_str += L_BESLA_NR;

         if ( besla_nr_pflege == 0 )
              besla_nr_pflege = besla_nr;

         anz = 0;
         a_str = r_str;
         while ( *r_str != '\1' )
         {
           r_str++;
           anz++;
         }
         if ( anz > L_ARTNRBL_ARTIKEL_NR_BLIEFER )
              anz = L_ARTNRBL_ARTIKEL_NR_BLIEFER;
         anz_cpy ( art_nr_bl, a_str, anz );
         r_str++;

         s = Einfuege_Alles( besla_nr, artikel_nr, art_nr_bl, errmld );
       }
       else                     /* Fehler */
       {
         s = -1;
         strcpy( errmld, "Uebertragungspuffer zerstoert" );
       }
    }

    if ( s == 0 && besla_nr_pflege != 0 )
	{
         s = Insert_Pflege( besla_nr_pflege, artikel_nr, errmld );
#ifdef MIT_NEM
		 if ( s == 0 && (strcmp (db, "zpps1de") == 0 || strcmp (db, "ide21") == 0))
			 s = StoreRecord_Zartikel( artikel_nr, besla_nr_pflege, errmld  );
#endif
	}

    if ( s == 0 )
         s = DeleteRecord_Zaneuheit( '2', artikel_nr, errmld );

    if ( s == 0 )
       s = CommitTransaction( errmld );
    else
       CancelTransaction( );

    return s;
}

int Serv_HerstWechsel( char *r_info, int r_lng, char *w_info, int *w_lng, char *db )
{
    long s;
    char errmld[100];

    s =  Do_HerstWechsel( r_info, r_lng, errmld, db );

    if ( s == 0 )
        strcpy( w_info, "Umlisten ok" );
    else
        strcpy( w_info, errmld );

    *w_lng = strlen( w_info );
    if ( s == 0 )
      return 0;

    return -1;
}

void Serv_HerstWechselFreeAll( void )
{
  OnLast( );
}

