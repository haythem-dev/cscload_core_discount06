/* ---------------------------------------------------------------------- *
 *                         stopgibatchentry.c                             *
 * ---------------------------------------------------------------------- *
 * Projekt:  ZDP                                                          *
 * Gruppe:   cgibatchentry.dateto setzen                                  *
 * ---------------------------------------------------------------------- *
 * Autor  :  Hörath                                                       *
 * Anfang :  12.07.2014                                                   *
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

#include <cgibatchentry.h>

/* ----------------- Prototype ------------------------ */

void CloseBase( void );
long OpenBase( char *db, char *errmld );

/* ----------------- Usage ------------------------ */

void StopGiBatchEntriesUsage( char *buf )
{
   strcat( buf, "- zpmasaen 14 Database User dateto company_code\n" );
   strcat( buf, "  cgibatchentry.dateto setzen\n" );
}

/* ----- cgibatchentry ------------------------- */

static int  Fd_CGiBatchEntry = -1;

static long lStatus_CGiBatchEntry;

static struct CGIBATCHENTRY Buf_CGiBatchEntry;
static struct CGIBATCHENTRY BufOld_CGiBatchEntry;

static int GetBufferDesc_CGiBatchEntry( char * errmld )
{
    char *tabelle = "cgibatchentry";
    long lStatus;
    char errstr[80];

    strcpy( errmld, "");

    if ( Fd_CGiBatchEntry >= 0 ) 
		return 0;

    lStatus = OpenBufferDescProj( &Fd_CGiBatchEntry, tabelle, PROJECTION_CGIBATCHENTRY,
                                  NULL, NULL, V_PROTO_VERTEIL, errstr );
                                
    if ( lStatus != 0 )
    {
      sprintf( errmld, "%s: %s", tabelle, errstr );
      Fd_CGiBatchEntry = -1;
      return -1;
    }
    return 0;
}

static long StoreRecord_CGiBatchEntry( long artikel_nr, short company, long datum_ab, long datum_bis, long tagesdatum, char *user, long dateto, char* cErrmld )
{
   long lStatus;
   char PrimekeyCond[200];
   
   strcpy( cErrmld, "" );

   sprintf( PrimekeyCond, "COMPANY_CODE=%d and ARTICLENO=%ld and DATEFROM=%ld and DATETO=%ld", company, artikel_nr, datum_ab, datum_bis );

   lStatus = FdReadRecord( Fd_CGiBatchEntry, PrimekeyCond,
                           &Buf_CGiBatchEntry, cErrmld );

   if ( lStatus != 0  ) 
	   return lStatus;

   BufOld_CGiBatchEntry = Buf_CGiBatchEntry;  /* gelesenen Satz sichern */

   Buf_CGiBatchEntry.DATE_CHANGED = tagesdatum;
   Buf_CGiBatchEntry.DATETO = dateto;

   lStatus = FdDelayUpdateRecord( Fd_CGiBatchEntry, &Buf_CGiBatchEntry,
                                  &BufOld_CGiBatchEntry,
                                  PrimekeyCond, cErrmld );
   return lStatus;
}

static long InitAll( char *errmld )
{
   if ( GetBufferDesc_CGiBatchEntry( errmld ) != 0 ) 
	   return -1;

   return 0;
}


static void FreeAll()
{
   if ( Fd_CGiBatchEntry >= 0 )
      CloseOneBufferDesc( Fd_CGiBatchEntry );
   Fd_CGiBatchEntry = -1;
}

static long DoIt( char *user, long artikel_nr, short company, long datum_ab, long datum_bis, long tagesdatum,
                  long endedatum, char *errmld )
{
   long s;

   s = StoreRecord_CGiBatchEntry( artikel_nr, company, datum_ab, datum_bis, tagesdatum, user, endedatum, errmld );

   if ( s == 0 )
      s = FdTransact( errmld );

   return s;
}

static long SetDateToByCompanyCode( char *user,  char *cEndedatum, char *companyCode, char *buf )
{
   long tagesdatum;
   long endedatum;

   long artikel_nr;
   long datum_ab;
   long datum_bis;
   short company;

   long s;
   long anz;
   int  fd;
   char z_buf[101];

   tagesdatum = GetPhoDate();
   ConvToPhoDate( cEndedatum, &endedatum, "tt.mm.jjjj" );

   	sprintf( buf,// aktuell sind nur Artikel mit BTM = 0 relevant
				"select articleno, company_code, datefrom, dateto from cgibatchentry where " \
				"company_code = %s and datefrom <= %ld and (dateto > %ld or dateto = 0)",
				companyCode, endedatum, endedatum );

   s = SqlOpenCsWh( &fd, buf );

   if ( s != 0 )
   {
     strcpy( buf, "CGIBATCHENTRY\n" );
     strcat( buf, DynErrmld() );
     return s;
   }

   s = SqlFetch( fd, 1, &artikel_nr, &company, &datum_ab, &datum_bis, NULL );
   if ( s == 100 )
   {
     strcpy( buf, "Keine entsprechenden Einträge vorhanden" );
     return 0;
   }

   if ( s != 0 )
   {
     strcpy( buf, "CGIBATCHENTRY\n" );
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
      s = DoIt( user, artikel_nr, company, datum_ab, datum_bis, tagesdatum, endedatum, buf );

      if ( s == 0 )
      {
         anz++;
         s = SqlFetch( fd, 1, &artikel_nr, NULL );
         if ( s != 0 )
         {
           strcpy( buf, "CGIBATCHENTRY\n" );
           strcat( buf, DynErrmld() );
         }
      }
   }

   FreeAll( );

   SqlCloseCs( fd );

   sprintf( z_buf, "\nEs wurden %ld Einträge beendet", anz );

   if ( s == 100 )
   {
      s = 0;
      strcpy( buf, "Aktion erfolgreich" );
   }
   strcat( buf, z_buf );
   return s;
}

long StopGiBatchEntries ( char *db, char *user, char *cEndedatum, char *companyCode, char *buf )
{
   long s;
   char errmld[10];

   s = OpenBase( db, buf );
   if ( s == 0 )
   {
     s = OpenPflege( user, buf );
     if ( s == 0 )
     {
        s = SetDateToByCompanyCode( user, cEndedatum, companyCode, buf );
        ClosePflege( errmld );
     }
     CloseBase( );
   }
   return s;
}
