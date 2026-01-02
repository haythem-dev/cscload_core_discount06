/* ---------------------------------------------------------------------- *
 *                         Setlkenn.c                                     *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   Loeschkennzeichen Setzen                                     *
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

#include <zartikel.h>
#include <zapflege.h>

#define L_ARTIKEL_NR 7

/* ----------------- wie loeschen --------------------- */

#define LOESCH_MIT_PROTOKOL

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void SetLoekennUsage( char *buf )
{
   strcat( buf, "- zpmasaen 4 Database User Datum Landeskürzel\n" );
   strcat( buf, "  Loeschkennzeichen setzen fuer Artikel mit\n" );
   strcat( buf, "  DATUM_AH < Datum and DATUM_IFALOESCH < Datum\n" );
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
static char CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];

static int GetBufferDesc_Zartikel( char * errmld )
{
    char *tabelle = "zartikel";
    long lStatus;
    char errstr[80];

    strcpy( errmld, "");
    if ( Fd_Zartikel >= 0 ) return 0;

    memset( CmpIndikator_Zartikel, '0', POSANZ_ZARTIKEL );
    CmpIndikator_Zartikel[POSANZ_ZARTIKEL] = '\0';
    CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_AENDER] = '1';
    CmpIndikator_Zartikel[P_ZARTIKEL_BEARBEITER]   = '1';
    CmpIndikator_Zartikel[P_ZARTIKEL_ARTIKEL_GELOESCHT] = '1';

    lStatus = OpenBufferDescProj( &Fd_Zartikel, tabelle, PROJECTION_ZARTIKEL,
                                  CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errstr );
                                /* !!!!!!!bis 21.12.2000    V_PROTOKOL  */
    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_Zartikel = -1;
      return -1;
    }
    return 0;
}

static long StoreRecord_Zartikel( long artikel_nr, long datum, char *user,
                                  char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[50];
   char format[50];

   Buf_zartikel.ARTIKEL_NR = artikel_nr;

   strcpy( cErrmld, "" );

   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartikel.ARTIKEL_NR );

/* sprintf( PrimekeyCond, "ARTIKEL_NR=%ld", Buf_zartikel.ARTIKEL_NR ); */

   lStatus = FdReadRecord( Fd_Zartikel, PrimekeyCond,
                           &Buf_zartikel, cErrmld );

   if ( lStatus != 0  ) return lStatus;

   BufOld_zartikel = Buf_zartikel;  /* gelesenen Satz sichern */

   Buf_zartikel.DATUM_AENDER = datum;
   strcpy( Buf_zartikel.BEARBEITER, user );
   *Buf_zartikel.ARTIKEL_GELOESCHT = '1';

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
                  char *errmld )
{
   long s;

   s = StoreRecord_Zartikel( artikel_nr, tagesdatum, user, errmld );

   if ( s == 0 )  
      s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
  
   if ( s == 0 )
      s = FdTransact( errmld );

   return s;
}

static long SetLoekenn( char *user, long datum, char *lkz, char *buf )
{
   long tagesdatum;

   long artikel_nr;
   long s;
   long anz;
   int  fd;
   char z_buf[51];

   tagesdatum = GetPhoDate();

   /* keine Abfrage auf datum_ifaloesch in der Schweiz */
   if (strcmp(lkz, "CH") == 0)
   {
		sprintf( buf,
					"select ARTIKEL_NR from ZARTIKEL where " \
					"artikel_geloescht='0' and " \
					"datum_ah < %ld and datum_ah > 0", datum );
   }
   else
   {
		sprintf( buf,
					"select ARTIKEL_NR from ZARTIKEL where " \
					"artikel_geloescht='0' and " \
					"datum_ah < %ld and datum_ah > 0 and datum_ifaloesch < %ld and datum_ifaloesch > 0",
					datum, datum );
   }

   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "ZARTIKEL\n" );
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
     strcpy( buf, "ZARTIKEL\n" );
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
      s = DoIt( user, artikel_nr, tagesdatum, buf );

      if ( s == 0 )
      {
         anz++;
         s = SqlFetch( fd, 1, &artikel_nr, NULL );
         if ( s != 0 )
         {
           strcpy( buf, "ZARTIKEL\n" );
           strcat( buf, DynErrmld() );
         }
      }
   }

   FreeAll( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld Loeschkennzeichen gesetzt", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Aktion erfolgreich" );
   }
   strcat( buf, z_buf );
   return s;
}

long SetLoekennLoop ( char *db, char *user, char *datumstr, char *lkz, char *buf )
{
   long s;
   long datum;
   char errmld[10];

   if ( ConvToPhoDate ( datumstr, &datum, "tt.mm.jjjj" ) != 1 )
   {
       strcpy( buf, "Datum in der Form tt.mm.jjjj" );
       return 1;
   }
   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
        s = SetLoekenn( user, datum, lkz, buf );
        ClosePflege( errmld );
     }
     CloseBase( );
   }
   return s;
}
