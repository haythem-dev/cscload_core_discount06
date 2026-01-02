/* ---------------------------------------------------------------------- *
 *                         Setlkenn.c                                     *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Artikel-KZ abhängig von Wirkstoff-Typ setzen                 *
 * ---------------------------------------------------------------------- *
 * Autor  :  Hörath                                                       *
 * Anfang :  12.05.2014                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hdatum/phodate.h"
#include "libscsvoodoo/libscsvoodoo.h"

#include  "wdbups/wpp_prot.h"
#include  "wdbups/wpp_dbas.h"

#include <zartikel.h>
#include <zapflege.h>

#define L_ARTIKEL_NR 7

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void UpdArticleFlagsByIngredientTypeUsage( char *buf )
{
   strcat( buf, "- zpmasaen 13 Database User WirkstoffNr WirkstoffTyp-ALT WirkstoffTyp-NEU\n" );
   strcat( buf, "  Artikel-KZ abhängig von Wirkstoff-Typ setzen\n" );
}

/* -----  Zapflege  ------------------------- */

static int  Fd_Zapflege = -1;

static struct ZAPFLEGE Buf_zapflege;

static int GetBufferDesc_Zapflege( char * errmld )
{
   char *tabelle = "zapflege";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zapflege >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zapflege, tabelle, PROJECTION_ZAPFLEGE,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zapflege = -1;
     return -1;
   }
   return 0;
}

static long StoreRecord_Zapflege( long artikel_nr, long datum, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[50];

   Buf_zapflege.ARTIKEL_NR = artikel_nr;
   Buf_zapflege.DATUM      = datum;

   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "ARTIKEL_NR=%ld and DATUM=%ld",
                          Buf_zapflege.ARTIKEL_NR,
                          Buf_zapflege.DATUM );

   lStatus = FdReadRecord( Fd_Zapflege, PrimekeyCond,
                           &Buf_zapflege, cErrmld );

   if ( !( lStatus == 0 || lStatus == 100 ) ) return -1;

   if ( lStatus == 100 )
   {
      Buf_zapflege.ARTIKEL_NR = artikel_nr;
      Buf_zapflege.DATUM      = datum;
      lStatus = FdDelayInsertRecord( Fd_Zapflege, &Buf_zapflege,
                                     PrimekeyCond, cErrmld);
   }
   return lStatus;
}

/* ----- Zartikel ------------------------- */

static int  Fd_Zartikel = -1;

static long lStatus_Zartikel;

static struct ZARTIKEL Buf_zartikel;
static struct ZARTIKEL BufOld_zartikel;

static int GetBufferDesc_Zartikel( char * errmld )
{
    char *tabelle = "zartikel";
    long lStatus;
    char errstr[80];

    strcpy( errmld, "");
    if ( Fd_Zartikel >= 0 ) 
		return 0;

    lStatus = OpenBufferDescProj( &Fd_Zartikel, tabelle, PROJECTION_ZARTIKEL,
                                  NULL, NULL, V_PROTO_VERTEIL, errstr );
                                
    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_Zartikel = -1;
      return -1;
    }
    return 0;
}

static long StoreRecord_Zartikel( long artikel_nr, long datum, char *user, char *ingredienttype_old, char *ingredienttype_new, 
                                  char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[50];
   char format[50];

   Buf_zartikel.ARTIKEL_NR = artikel_nr;

   strcpy( cErrmld, "" );

   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartikel.ARTIKEL_NR );

   lStatus = FdReadRecord( Fd_Zartikel, PrimekeyCond,
                           &Buf_zartikel, cErrmld );

   if ( lStatus != 0  ) 
	   return lStatus;

   BufOld_zartikel = Buf_zartikel;  /* gelesenen Satz sichern */

   Buf_zartikel.DATUM_AENDER = datum;
   strcpy( Buf_zartikel.BEARBEITER, user );

   if ( *ingredienttype_old == 'B' )
   {
		// Wirkstoff-Typ "B" entfernt
		// --> alle Artikel mit dieser Wirkstoffgruppe und btm != '1', psychotrop=N	
	   *Buf_zartikel.PSYCHOTROP = 'N';
   }
   else if ( *ingredienttype_new == 'B' )
   {
		// Wirkstoff-Typ "B" neu gesetzt
		// --> alle Artikel mit dieser Wirkstoffgruppe und btm != '1', psychotrop=J / bestell_nicht_ausl=1
	   *Buf_zartikel.PSYCHOTROP = 'J';
	   *Buf_zartikel.BESTELL_NICHT_AUSL = '1';
   }

   lStatus = FdDelayUpdateRecord( Fd_Zartikel, &Buf_zartikel,
                                  &BufOld_zartikel,
                                  PrimekeyCond, cErrmld );
   return lStatus;
}

static long InitAll( char *errmld )
{
   if ( GetBufferDesc_Zartikel( errmld ) != 0 ) return -1;
   if ( GetBufferDesc_Zapflege( errmld ) != 0 ) return -1;
   return 0;
}


static void FreeAll()
{
   if ( Fd_Zartikel >= 0 )
      CloseOneBufferDesc( Fd_Zartikel );
   Fd_Zartikel = -1;
   if ( Fd_Zapflege >= 0 )
      CloseOneBufferDesc( Fd_Zapflege );
   Fd_Zapflege = -1;
}

static long DoIt( char *user, long artikel_nr, long tagesdatum,
                  char *ingredienttype_old, char *ingredienttype_new, char *errmld )
{
   long s;

   s = StoreRecord_Zartikel( artikel_nr, tagesdatum, user, ingredienttype_old, ingredienttype_new, errmld );

   if ( s == 0 )  
      s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
  
   if ( s == 0 )
      s = FdTransact( errmld );

   return s;
}

static long SetArticleFlagByIngredientType( char *user, char *wirkstoffnr, char *ingredienttype_old, char *ingredienttype_new, char *buf )
{
   long tagesdatum;

   long artikel_nr;
   long s;
   long anz;
   int  fd;
   char z_buf[101];

   tagesdatum = GetPhoDate();

   	sprintf( buf,// aktuell sind nur Artikel mit BTM = 0 relevant
				"select a.ARTIKEL_NR from ZARTWG w, ZARTIKEL a where " \
				"a.artikel_nr = w.artikel_nr and " \
				"a.btm != '1' and " \
				"art='E' and " \
				"warengruppe = '%s'",
				wirkstoffnr );

   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "ZARTWG\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd, 1, &artikel_nr, NULL );
   if ( s == 100 )
   {
     strcpy( buf, "Keine entsprechenden Artikel vorhanden" );
     return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "ZARTWG\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = InitAll( buf );
   if ( s != 0 )
   {
      FreeAll( );
      SqlCloseCs( fd );
      return s;
   }

   anz = 0;
   while ( s == 0 )
   {
      s = DoIt( user, artikel_nr, tagesdatum, ingredienttype_old, ingredienttype_new, buf );

      if ( s == 0 )
      {
         anz++;
         s = SqlFetch( fd, 1, &artikel_nr, NULL );
         if ( s != 0 )
         {
           strcpy( buf, "ZARTWG\n" );
           strcat( buf, DynErrmld() );
         }
      }
   }

   FreeAll( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld Artikel geändert", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Aktion erfolgreich" );
   }
   strcat( buf, z_buf );
   return s;
}

long UpdArticleFlagsByIngredientTypeLoop ( char *db, char *user, char *wirkstoffnr, char *ingredienttype_old, char *ingredienttype_new, char *buf )
{
   long s;
   char errmld[10];

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
        s = SetArticleFlagByIngredientType( user, wirkstoffnr, ingredienttype_old, ingredienttype_new, buf );
        ClosePflege( errmld );
     }
     CloseBase( );
   }
   return s;
}
