/* ---------------------------------------------------------------------- *
 *                         A U T I D E M . C                              *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Massenaenderung Preise                                       *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  03.06.2002                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "hdatum/phodate.h"
#include "libscsvoodoo/libscsvoodoo.h"

#include "sqltabs/tabsqld.h"
#include "wdbups/wpp_prot.h"
#include <zartikel.h>


#define L_ARTIKEL_NR 7


/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void AutidemUsage( char *buf )
{
   strcat( buf, "- zpmasaen 5 Database USER HNR PREISSENKUNG_ALT PREISSENKUNG_NEU\n" );
   strcat( buf, "  Massenaenderung Kennzeichen Preissenkung\n" );
}

/* ----------------- Leseschleife Artikel -------------------- */


static long Lese_Zart( int fd_lese, struct ZARTIKEL *zart, char *buf )
{
   long s;
   s = SqlBeginWork();
   if ( s == 0 )
      s = SqlFetch( fd_lese, 1, zart, NULL );
   if ( s != 0 )
      strcpy( buf, DynErrmld() );
   return s;
}

static
long I_AutidemLoop ( char *user, long lHnr, 
                     char *autidem_alt, char *autidem_neu, 
                     char *buf )
{
   long anz_art;

   int  fd_lese;
   int  fd_upd;
   long s;
   int  ret;
   int  first;

   long tagesdatum;

   char sql[ 4000 ];
   char zart_select[30];
   char zart_format[30];

   char anwender[9];
   size_t lng;

   void   *zart_desc;

   struct ZARTIKEL zart_before;
   struct ZARTIKEL zart_after;

   sprintf( zart_format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );

   lng = strlen( user );
   if ( lng >= 8 ) lng = 8;
   memset( anwender, ' ', 8 );
   anwender[8] = '\0';
   memcpy( anwender, user, lng );

   sprintf( sql, "select %s from ZARTIKEL " \
                 "where HERSTELLER_NR=%ld and PREISSENKUNG='%s'for update",
                  PROJECTION_ZARTIKEL,
                  lHnr,
                  autidem_alt );

   s = SqlOpenCsWh( &fd_lese, sql );
   if ( s != 0 )
   {
      strcpy( buf, DynErrmld() );
      return s;
   }

   sprintf( sql, "where current of %s", SqlGetCursor( fd_lese ) );
   s = SqlPrepareUpdate ( &fd_upd, "zartikel", PROJECTION_ZARTIKEL, sql );
   if ( s != 0 )
   {
      strcpy( buf, DynErrmld() );
      SqlCloseCs( fd_lese );
      return s;
   }                        

   s = SqlGetTabProjDesc( "zartikel", PROJECTION_ZARTIKEL, &zart_desc,
                          DESC_TABBUF, buf );

   if ( s != 0 )
   {
       SqlFreePrepare( fd_upd );
       SqlCloseCs( fd_lese );
       return s;
   }

   tagesdatum = GetPhoDate();

   first = 1;
   anz_art = 0;

   s  = 0;

   while ( s == 0 )
   {
        s = Lese_Zart( fd_lese, &zart_before, buf );
        if ( s == 0 )
        {
           first = 0;
           anz_art++;
           zart_after = zart_before;
           *zart_after.PREISSENKUNG = *autidem_neu;
           zart_after.DATUM_AENDER  = tagesdatum;

		   if ((zart_after.PREISSENKUNG[0]  == '0' || zart_after.PREISSENKUNG[0]  == '3') &&
			    zart_before.PREISSENKUNG[0] != '0' && zart_before.PREISSENKUNG[0] != '3' )
				zart_after.DATUM_PREISSENKUNG = 0;

		   if (zart_after.PREISSENKUNG[0]  != '0' && zart_after.PREISSENKUNG[0]  != '3' &&
			   (zart_before.PREISSENKUNG[0] == '0' || zart_before.PREISSENKUNG[0] == '3' ) )
				zart_after.DATUM_PREISSENKUNG = tagesdatum;

           strcpy( zart_after.BEARBEITER, anwender );
           s = SqlExecutePrepare( fd_upd, &zart_after, NULL );
           if ( s != 0 )
           {
                strcpy( buf, DynErrmld() );
           }
           else
           {
                sprintf( zart_select, zart_format, zart_before.ARTIKEL_NR );
                ret = Insert_Protokoll( P_UPDATE,  V_PROTO_VERTEIL, zart_desc, 
                                        &zart_before, &zart_after,
                                        zart_select, anwender, "", 0, buf );
                s = ret;
           }
           if ( s == 0 )
                SqlCommitWork();
           else
                SqlRollbackWork();
        }
   }

   if ( s == 100 )
   {
       if ( first )
          sprintf( buf, "Kein Artikel von Hersteller-Nr %ld und Preissenkung %s vorhanden", 
                        lHnr,
                        autidem_alt );
       else 
           s = 0;
   }

   Free_Protokoll( );
   SqlFreePrepare( fd_upd );
   SqlCloseCs( fd_lese );

   if ( s == 0 )
      sprintf( buf, "Anzahl Artikel geaendert: %ld\n",
               anz_art );

   return s;
}

long AutidemLoop ( char *db, char *user, char *cHnr, 
                   char *autidem_alt, char *autidem_neu, 
                   char *buf )
{
   long lHnr;
   long s;

   lHnr = atol( cHnr );
   if ( lHnr <= 0 )
   {
      strcpy( buf, "HerstellerNr > 0" );
      return 1;
   }

   if ( strcmp( autidem_alt, autidem_neu ) == 0 )
   {
      strcpy( buf, "autidem_alt = autidem_neu" );
      return 1;
   }

   if (!( (*autidem_neu >= '0' && *autidem_neu <= '5') || *autidem_neu == '9' ) )
   {
      strcpy( buf, "0 <= autidem_neu <= 5 oder autidem_neu = 9" );
      return 1;
   }

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
		s = I_AutidemLoop ( user, lHnr, autidem_alt, autidem_neu, buf );
		CloseBase( );
   }

   return s;
}
