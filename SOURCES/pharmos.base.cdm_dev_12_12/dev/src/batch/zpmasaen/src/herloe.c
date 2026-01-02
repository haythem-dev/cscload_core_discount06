/* ---------------------------------------------------------------------- *
 *                         H E R L O E . C                                *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Hersteller loeschen                                          *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  10.10.1998                                                   *
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

#include <herstel.h>
#include <cimexmanufacturermapping.h>

#define L_HERSTELLER_NR 5

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void HerLoeUsage( char *buf )
{
   strcat( buf, "- zpmasaen 3 Database USER Datum\n" );
   strcat( buf, "  Hersteller mit Loeschdatum <= Datum loeschen\n" );
}

/* ----------------- Loeschen mit Protokoll ------------------ */

static int m_Fd_Herstel = -1;

int GetBufferDesc_Herstel( char *cErrmld )
{
   char *tabelle = "herstel";
   long s;
   char errmld[100];

   *cErrmld = '\0';

   if ( m_Fd_Herstel >= 0 ) return 0;

   s = OpenBufferDescProj( &m_Fd_Herstel, tabelle, PROJECTION_HERSTEL,
                           NULL, NULL, V_PROTO_VERTEIL,
                           errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );;
     m_Fd_Herstel = -1;
     return -1;
   }
   return 0;
}

long Delete_Herstel( long hersteller_nr, char *cErrmld )
{
   long s;
   char errmld[200];
   char m_PrimekeyCond[30];
   char format[30];
   struct HERSTEL her;

   if (  GetBufferDesc_Herstel( cErrmld ) != 0 ) return -1;

   her.HERSTELLER_NR = hersteller_nr;
   sprintf( format, "HERSTELLER_NR=%c%d.ld", '%', L_HERSTELLER_NR );
   sprintf( m_PrimekeyCond, format, her.HERSTELLER_NR );

/* sprintf( m_PrimekeyCond, "HERSTELLER_NR=%ld", her.HERSTELLER_NR ); */

   s = FdReadRecord( m_Fd_Herstel, m_PrimekeyCond, &her, errmld );
   if ( s == 0 )
   {
     s = FdDelayDeleteRecord( m_Fd_Herstel, &her, m_PrimekeyCond, errmld );
     if ( s != 0 )
     {
       strcpy( cErrmld, "FdDeleteHerstel\n" );
       strcat( cErrmld, errmld );
     }
   }
   else if ( s == 100 )
     s = 0;
   else
   {
     strcpy( cErrmld, "FdReadHerstel\n" );
     strcat( cErrmld, errmld );
   }

   return s;
}

static int m_Fd_Cimexmanufacturermapping = -1;

int GetBufferDesc_Cimexmanufacturermapping( char *cErrmld )
{
   char *tabelle = "cimexmanufacturermapping";
   long s;
   char errmld[100];

   *cErrmld = '\0';

   if ( m_Fd_Cimexmanufacturermapping >= 0 ) return 0;

   s = OpenBufferDescProj( &m_Fd_Cimexmanufacturermapping, tabelle, PROJECTION_CIMEXMANUFACTURERMAPPING,
                           NULL, NULL, V_PROTO_VERTEIL,
                           errmld );
   if ( s != 0 )
   {
     strcpy( cErrmld, errmld );
     strcat( cErrmld, "\ntable " );
     strcat( cErrmld, tabelle );;
     m_Fd_Cimexmanufacturermapping = -1;
     return -1;
   }
   return 0;
}

long Delete_Cimexmanufacturermapping( long hersteller_nr, char *cErrmld )
{
   long s;
   char errmld[200];
   char m_PrimekeyCond[30];
   char format[30];
   struct CIMEXMANUFACTURERMAPPING her;

   if (  GetBufferDesc_Cimexmanufacturermapping( cErrmld ) != 0 ) return -1;

   her.HERSTELLER_NR = hersteller_nr;
   sprintf( format, "HERSTELLER_NR=%c%d.ld", '%', L_HERSTELLER_NR );
   sprintf( m_PrimekeyCond, format, her.HERSTELLER_NR );

   s = FdReadRecord( m_Fd_Cimexmanufacturermapping, m_PrimekeyCond, &her, errmld );
   if ( s == 0 )
   {
     s = FdDelayDeleteRecord( m_Fd_Cimexmanufacturermapping, &her, m_PrimekeyCond, errmld );
     if ( s != 0 )
     {
       strcpy( cErrmld, "FdDeleteCimexmanufacturermapping\n" );
       strcat( cErrmld, errmld );
     }
   }
   else if ( s == 100 )
     s = 0;
   else
   {
     strcpy( cErrmld, "FdReadCimexmanufacturermapping\n" );
     strcat( cErrmld, errmld );
   }

   return s;
}

/* ----------------- Funktion ------------------------ */

static long Init_Loeschen( char *errmld )
{
   return 0;
}

static long Execute_Loeschen( long hersteller_nr, char *errmld )
{
   long s;

   s = Delete_Herstel( hersteller_nr, errmld );

   if ( s == 0 )
      s = Delete_Cimexmanufacturermapping( hersteller_nr, errmld );

   if ( s == 0 )
      s = FdTransactWithoutWork( errmld );
   if ( s != 0 )
   {
      return s;
   }
   return 0;
}

static void Free_Loeschen( )
{
}


static long LoescheAll( char *user, long hersteller_nr, long tagesdatum,
                        char *buf )
{
   long s;

   s = SqlBeginWork();
   if ( s != 0 )
   {
     strcpy( buf, DynErrmld() );
     return -1;
   }

   s = Execute_Loeschen( hersteller_nr, buf );

   if ( s == 0 )
   {
      s = SqlCommitWork();
      if ( s != 0 )
         strcpy( buf, DynErrmld() );
   }
   else
      SqlRollbackWork();

   return s;
}

static long LoescheHersteller( char *user, long loedatum, char *buf )
{
   long tagesdatum;
   long hersteller_nr;
   long s;
   long anz;
   int  fd;
   char z_buf[51];

   tagesdatum = GetPhoDate();

   if ( loedatum == 0 )
      sprintf( buf,
               "select HERSTELLER_NR from HERSTEL where DATUM_LOESCH>0" );
   else
      sprintf( buf,
               "select HERSTELLER_NR from HERSTEL where " \
               "DATUM_LOESCH > 0 and DATUM_LOESCH<=%ld",
               loedatum );

   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "HERSTEL\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd, 1, &hersteller_nr, NULL );
   if ( s == 100 )
   {
     if ( loedatum == 0 )
        strcpy( buf, "Keine Hersteller mit Loeschdatum vorhanden" );
     else
     {
        ConvFromPhoDate( z_buf, loedatum, "tt.mm.jjjj" );
        sprintf( buf, "Keine Hersteller mit Loeschdatum <= %s vorhanden",
                      z_buf );
     }
     return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "HERSTEL\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = Init_Loeschen( buf );
   if ( s != 0 )
   {
      Free_Loeschen( );
      SqlCloseCs( fd );
      return s;
   }

   anz = 0;
   while ( s == 0 )
   {
      s = LoescheAll( user, hersteller_nr, tagesdatum, buf );

      if ( s == 0 )
      {
         anz++;
         s = SqlFetch( fd, 1, &hersteller_nr, NULL );
         if ( s != 0 )
         {
           strcpy( buf, "HERSTEL\n" );
           strcat( buf, DynErrmld() );
         }
      }
   }

   Free_Loeschen( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld Hersteller geloescht", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Loeschen erfolgreich" );
   }
   strcat( buf, z_buf );
   return s;
}

long HerLoeLoop ( char *db, char *user, char *cDatum, char *buf )
{
   long s;
   long loedatum;
   size_t lng;
   char errmld[10];

   lng = strlen( cDatum );
   if ( lng == 1 && *cDatum == '0' )
      loedatum = 0;
   else if ( lng != 10 )
      loedatum = -1;
   else
   {
      if ( ConvToPhoDate( cDatum, &loedatum, "tt.mm.jjjj" ) == 0 )
        loedatum = -1;
   }

   if ( loedatum == -1 )
   {
      strcpy( buf, "Datum nicht korrekt" );
      return -1;
   }

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
         s = LoescheHersteller( user, loedatum, buf );
        ClosePflege( errmld );
     }
     CloseBase( );
   }
   return s;
}
