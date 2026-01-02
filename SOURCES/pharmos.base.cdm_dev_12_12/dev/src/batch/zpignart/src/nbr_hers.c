
/* ---------------------------------------------------------------------- *
 *                         N B R _ H E R S . C                            *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 *           - Setzt den Status PL_C_HERSTNUM zurueck                     *
 *             nachdem der fehlende Hersteller erfasst wurde              *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  27.10.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */

/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo.h>

#include "znb_gen.h"

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void Reset_PL_C_HERTSNUM_Usage( char *buf, char* prog )
{
   strcat( buf, "- " );
   strcat( buf, prog );
   strcat( buf, " 2 database Ifadatum\n" \
                "  Hersteller-Plausi-Fehler in zifaart ruecksetzen\n" );
}

/* ---- so sieht der NBSTATUS aus ----------- */

  /* NBSTATUS */
  /* xxxx0000 */
  /*      !!L-----  NZ  */
  /*      !L------  ZW  */
  /*      !L------  PL  */

static void SetPlausiStatus( char *nb_status, char *nb_plausi )
{
   int i;
   i = 0;
/* || nb_plausi[i] == '9' : neu ab 23.01.2001 */
   while ( nb_plausi[i] && ( nb_plausi[i] == '0' || nb_plausi[i] == '9' ) ) i++;
   if ( !nb_plausi[i] )
      *nb_status &= ~4;   /* Plausi in nb_status auf 0 */
}

static long Do_All( long ifanr, char *errmld )
{
   int  fd_sel;
   int  fd_upd;
   long s;
   long satznr;
   long anz;
   char nbstatus[2];
   char nb_plausi[100];        /* gross genug */
   char sql[200];

   anz = 0;

   sprintf( sql,
            "select SATZNR,NBSTATUS,NB_PLAUSI from ZIFAART,HERSTEL where "  \
            "IFANR=%ld and NB_PLAUSI[%d]='1' and " \
            "HERSTELLER_NR=A00ANBNR",
            ifanr, PL_A00ANBNR + 1 );
   s = SqlOpenCsWh( &fd_sel, sql );
   if ( s != 0 )
   {
     sprintf( errmld, "Fehler bei Select\n%s",
                       DynErrmld() );
     return s;
   }

   sprintf( sql, "where IFANR=%ld and SATZNR=?", ifanr );
   s = SqlPrepareUpdate( &fd_upd, "zifaart",
                                  "NBSTATUS,NB_PLAUSI",
                                  sql );
   if ( s != 0 )
   {
     sprintf( errmld, "Fehler bei PrepareForUpdate\n%s",
                       DynErrmld() );
     SqlCloseCs( fd_sel );
     return s;
   }

   while ( s == 0 )
   {
     s = SqlBeginWork();
     if ( s == 0 )
     {
        s = SqlFetch( fd_sel, 1, &satznr, nbstatus, nb_plausi, NULL );
        if ( s == 0 )
        {
          nb_plausi[PL_A00ANBNR] = '0';
          SetPlausiStatus( nbstatus, nb_plausi );
          s = SqlExecutePrepare( fd_upd, nbstatus, nb_plausi, &satznr, NULL );
         }
        if ( s == 0 )
        {
          anz++;
          s = SqlCommitWork();
        }
        else
          SqlRollbackWork();
     }
   }

   strcpy( errmld, "" );
   if ( s == 100 )
   {
      s = 0;
      if ( anz > 0 )
         sprintf( errmld,
                  "Ruecksetzen der Hersteller-Plausi-Fehler erfolgreich\n" \
                  "Es wurden %ld Ifa-Saetze bearbeitet",
                  anz );
      else
         sprintf( errmld,
                  "Alle Hersteller-Plausi-Fehler sind bereits zurueckgesetzt" );
   }
   else
   {
      sprintf( errmld, "%s\n"
                       "Es wurden %ld Ifa-Saetze bearbeitet",
                        DynErrmld(),
                        anz );
   }

   SqlFreePrepare( fd_upd );
   SqlCloseCs    ( fd_sel );
   return s;
}


long Reset_PL_C_HERSTNUM_Loop( char *db, char *c_ifadatum, char *buf )
{
   long s;
   long ifanr;
   ifanr = atol( c_ifadatum );
   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = Do_All( ifanr, buf );
     CloseBase( );
   }
   return s;
}

long Reset_PL_C_HERSTNUM_Direkt( long ifanr, char *buf )
{
   return Do_All( ifanr, buf );
}


