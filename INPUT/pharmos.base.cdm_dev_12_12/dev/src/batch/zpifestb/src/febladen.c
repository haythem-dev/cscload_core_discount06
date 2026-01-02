
/* ---------------------------------------------------------------------- *
 *                            F E B L A D E N . C                         *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : laden der von zarrtikel / zartfeb mit Festbetraegen   *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 21.05.98                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>

/* -------  Spezielle includes ----------------------------------------- */

#include <wpp_prot.h>
#include <wpp_dbas.h>

#include <zartikel.h>
#include <zartwg.h>
#include <zartfeb2.h>
#include <zapflege.h>

#define L_ARTIKEL_NR 7

/* ----- Protokol ------------------------------ */

#include "feb_prot.h"

/* ---------------------------------------------------------------------- *
 * Funktion         : Preis   lesen                                       *
 * ---------------------------------------------------------------------- */

static int fd_zpreis = -1;

static long DeclareZpreis( long tages_datum, char *errmld )
{
    char sql[400];
    long status;

    sprintf( sql, "select AVP from ZARTPREIS where ARTIKEL_NR=? " \
                  "and DATUMGUELTIGAB=" \
                  "(select max(DATUMGUELTIGAB) from ZARTPREIS where " \
                  "DATUMGUELTIGAB<=%ld " \
                  "and ARTIKEL_NR=?)",
                  tages_datum );

    status = SqlDeclareCs( &fd_zpreis, sql,
                           "ZARTPREIS.ARTIKEL_NR",
                           "ZARTPREIS.ARTIKEL_NR", NULL );

    if ( status != 0 )
    {
      strcpy( errmld, "ZARTPREIS: " );
      strcat( errmld, DynErrmld() );
      fd_zpreis = -1;
    }
   return status;
}

static long ReadPreis( long artikel_nr, double *avp, char *errmld )
{
   long status;
   double zp_avp;
   status = SqlReadDeclCs( fd_zpreis, &zp_avp, NULL,
                                      &artikel_nr, &artikel_nr, NULL );
   *avp = 0.0;
   if ( status == 0 )
     *avp = zp_avp;
   else if ( status == 100 )    /* neu 22.10.2000: kein Preissatz vorhanden */
   {
     *avp = -1;     
     status = 0;
   }
   else
   {
     strcpy( errmld, "ZARTPREIS: " );
     strcat( errmld, DynErrmld() );
   }
   return status;
}

static void CloseZpreis( void )
{
    if ( fd_zpreis  != -1 ) SqlCloseCs ( fd_zpreis );
    fd_zpreis  = -1;
}

/* ---------- Primekeycondition fuer alles ----------- */

static char PrimekeyCond[100];

/* ----- Zartikel ------------------------- */

static char CmpIndikator_Zartikel[POSANZ_ZARTIKEL + 1];
static int  Fd_Zartikel = -1;
static long lStatus_Zartikel;

static struct ZARTIKEL Buf_zartikel;
static struct ZARTIKEL BufOld_zartikel;

void FillCmpIndikator_Zartikel ( )
{
   memset( CmpIndikator_Zartikel, '0', POSANZ_ZARTIKEL );
   CmpIndikator_Zartikel[POSANZ_ZARTIKEL] = '\0';

/* nichts vergleichen ?: doch, sonst geht es nicht */

   CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_FESTBETRAG1]  = '1';
   CmpIndikator_Zartikel[P_ZARTIKEL_FESTBETRAG1]        = '1';
}

int GetBufferDesc_Zartikel( char * errmld )
{
   char *tabelle = "zartikel";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zartikel >= 0 ) return 0;

   FillCmpIndikator_Zartikel ( );
   lStatus = OpenBufferDescProj( &Fd_Zartikel, tabelle, PROJECTION_ZARTIKEL,
                                 CmpIndikator_Zartikel, NULL, V_PROTO_VERTEIL, errstr );
                                /* !!!!!!!bis 20.12.2000      V_PROTOKOL  */
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zartikel = -1;
     return -1;
   }
   return 0;
}

void SetPrimekeyCondition_Zartikel ( )
{
   char format[30];
   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartikel.ARTIKEL_NR );
/*
   sprintf( PrimekeyCond, "ARTIKEL_NR=%ld", Buf_zartikel.ARTIKEL_NR );
*/
}

long ReadRecord_Zartikel( long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_zartikel.ARTIKEL_NR = artikel_nr;
   SetPrimekeyCondition_Zartikel ( );
   lStatus = FdReadRecord( Fd_Zartikel, PrimekeyCond,
                           &Buf_zartikel, errstr );

   if ( lStatus == 0 )
   {
      BufOld_zartikel = Buf_zartikel;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else
      strcpy ( cErrmld, errstr );
   lStatus_Zartikel = lStatus;
   return lStatus;
}

long StoreRecord_Zartikel( char* cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Zartikel ( );
   lStatus = FdDelayUpdateRecord( Fd_Zartikel, &Buf_zartikel,
                                  &BufOld_zartikel,
                                  PrimekeyCond, errmld );
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
}

/* ----- Zartwg (wg. Wirkstoff) ------------------------- */

static int  Fd_Zartwg = -1;
static long lStatus_Zartwg;

static struct ZARTWG Buf_zartwg;

int GetBufferDesc_Zartwg( char * errmld )
{
   char *tabelle = "zartwg";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zartwg >= 0 ) 
	   return 0;

   lStatus = OpenBufferDescProj( &Fd_Zartwg, tabelle, PROJECTION_ZARTWG,
                                 NULL, NULL, V_OHNE, errstr );

   if ( lStatus != 0 )
   {
		sprintf( errmld, "%s: %s", tabelle, errstr );
		Fd_Zartwg = -1;
		return -1;
   }

   return 0;
}

void SetPrimekeyCondition_Zartwg ( )
{
   char format[60];
   sprintf( format, "ARTIKEL_NR=%c%d.ld AND ART = 'E'", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartikel.ARTIKEL_NR );
}

long ReadRecord_Zartwg( long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_zartwg.ARTIKEL_NR = artikel_nr;
   SetPrimekeyCondition_Zartwg ( );
   lStatus = FdReadRecord( Fd_Zartwg, PrimekeyCond,
                           &Buf_zartwg, errstr );

   if ( lStatus == 0 )
      strcpy( cErrmld, "" );
   else
   /* kein Fehler, wenn zartwg nicht gefunden */
   {
		strcpy (Buf_zartwg.WARENGRUPPE, "");
		lStatus = 0;
		strcpy ( cErrmld, errstr );
   }

   lStatus_Zartwg = lStatus;
   return lStatus;
}

/* -----  Zartfeb2  ------------------------- */

static int  Fd_Zartfeb2 = -1;
static long lStatus_Zartfeb2;

static struct ZARTFEB2 Buf_zartfeb2;
static struct ZARTFEB2 BufOld_zartfeb2;

int GetBufferDesc_Zartfeb2( char * errmld )
{
   char *tabelle = "zartfeb2";
   long lStatus;
   char errstr[80];

   strcpy( errmld, "");
   if ( Fd_Zartfeb2 >= 0 ) return 0;

   lStatus = OpenBufferDescProj( &Fd_Zartfeb2, tabelle, PROJECTION_ZARTFEB2,
                                 NULL, NULL,
                                 V_OHNE,
                                 errstr );
   if ( lStatus != 0 )
   {
     sprintf( errmld, "%s: %s", tabelle, errstr );
     Fd_Zartfeb2 = -1;
     return -1;
   }
   return 0;
}

void SetPrimekeyCondition_Zartfeb2 ( )
{
   char format[30];
   sprintf( format, "ARTIKEL_NR=%c%d.ld", '%', L_ARTIKEL_NR );
   sprintf( PrimekeyCond, format, Buf_zartfeb2.ARTIKEL_NR );
/*
   sprintf( PrimekeyCond, "ARTIKEL_NR=%ld", Buf_zartfeb2.ARTIKEL_NR );
*/
}

long ReadRecord_Zartfeb2( long artikel_nr, char *cErrmld )
{
   long lStatus;
   char errstr[200];

   Buf_zartfeb2.ARTIKEL_NR = artikel_nr;
   SetPrimekeyCondition_Zartfeb2 ( );
   lStatus = FdReadRecord( Fd_Zartfeb2, PrimekeyCond,
                           &Buf_zartfeb2, errstr );

   if ( lStatus == 0 )
   {
      BufOld_zartfeb2 = Buf_zartfeb2;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else if ( lStatus == 100 )
   {
      Buf_zartfeb2.ARTIKEL_NR        = artikel_nr;
      Buf_zartfeb2.FESTBETRAG2       = 0.0;
      Buf_zartfeb2.DATUM_FESTBETRAG2 = 0;
      BufOld_zartfeb2 = Buf_zartfeb2;  /* gelesenen Satz sichern */
      strcpy( cErrmld, "" );
   }
   else
      strcpy ( cErrmld, errstr );
   lStatus_Zartfeb2 = lStatus;
   return lStatus;
}

long StoreRecord_Zartfeb2( char* cErrmld )
{
   long lStatus;
   char errmld[200];

   SetPrimekeyCondition_Zartfeb2 ( );
   if ( lStatus_Zartfeb2 == 100 )
      lStatus = FdDelayInsertRecord( Fd_Zartfeb2, &Buf_zartfeb2,
                                     PrimekeyCond, errmld);
   else if ( lStatus_Zartfeb2 == 0 )
      lStatus = FdDelayUpdateRecord( Fd_Zartfeb2, &Buf_zartfeb2,
                                     &BufOld_zartfeb2,
                                     PrimekeyCond, errmld );
   else
   {
     lStatus = lStatus_Zartfeb2;
     strcpy( cErrmld, "Zartfeb2 Interner Fehler" );
   }
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
}

long DeleteRecord_Zartfeb2( char *cErrmld )
{
   long lStatus;
   char errmld[200];
   if ( lStatus_Zartfeb2 == 100 ) return 0;
   SetPrimekeyCondition_Zartfeb2 ( );
   lStatus = FdDelayDeleteRecord( Fd_Zartfeb2, &BufOld_zartfeb2,
                                  PrimekeyCond, errmld );
   if ( lStatus != 0 )
      strcpy( cErrmld, errmld );
   else
      strcpy( cErrmld, "" );
   return lStatus;
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

/* ------------------------------------------------------------- *
 *     Festbetraege  laden                                       *
 * ------------------------------------------------------------- */

long FebLadenInit( long tagesdatum, char *mode, char *errmld )
{
    if ( GetBufferDesc_Zartikel ( errmld ) != 0 ) 
		return -1;

    if ( GetBufferDesc_Zartwg ( errmld ) != 0 ) 
		return -1;

	if ( GetBufferDesc_Zapflege ( errmld ) != 0 ) 
		return -1;

	if ( *mode == '1' || *mode == '3' )
    {
       if ( GetBufferDesc_Zartfeb2( errmld ) != 0 ) 
		   return -1;
    }
    /* als letztes wegen FebladenClose */
    if ( DeclareZpreis( tagesdatum, errmld ) != 0 )           
		return -1;

    return 0;
}

static void FillProt( struct FEB_PROT *info, struct ZARTIKEL *art, struct ZARTWG *wg,
                      double avp, double fest_neu, double fest_alt,
                      int wegfall, long code )
{
   info->ARTIKEL_NR   = art->ARTIKEL_NR;
   info->ARTIKEL_CODE   = code;
   strcpy( info->ARTIKEL_NAME, art->ARTIKEL_NAME );
   strcpy( info->EINHEIT     , art->EINHEIT );
   strcpy( info->DARREICHFORM, art->DARREICHFORM );
/* strcpy( info->WIRKSTOFF_NR, art->WIRKSTOFF_NR ); */
   strcpy( info->WIRKSTOFF_NR, wg->WARENGRUPPE );
   info->AVP       = avp;
   info->FEST_NEU  = fest_neu;
   info->FEST_ALT  = fest_alt;
   info->WEGFALL   = wegfall;
}

static long FebLadenZartikel( int alle,
                              int wegfall, long artikel_nr, long datum,
                              long festbetrag, char febstufe, long tagesdatum, char *errmld, long code )
{
  long s;
  struct FEB_PROT info;
  double fest_alt;
  double fest_neu;
  double fest_diff;
  double avp;

  s = ReadRecord_Zartikel( artikel_nr, errmld );

  if ( s == 100 ) 
	  return 0;   /* Artikel nicht vorhanden */

  if ( s != 0 )   
	  return s;   /* Fehler */

  ReadRecord_Zartwg( artikel_nr, errmld );

  fest_alt = Buf_zartikel.FESTBETRAG1;

  if ( !alle && fest_alt > 0.004 ) return 0;

  Buf_zartikel.DATUM_FESTBETRAG1 = datum;

  if ( wegfall )    /* bei Wegfall Preis auf 0, Datum eintragen */
     fest_neu = 0.0;
  else
     fest_neu = ( ( double ) festbetrag ) / 100.0;

  Buf_zartikel.FESTBETRAG1 = fest_neu;

  if (febstufe != 0)
	Buf_zartikel.STUFE_FESTBETRAG1[0] = febstufe;  // Wert nur updaten, wenn hier etwas geliefert wird (febstufe != null) !
  
  s = StoreRecord_Zartikel( errmld );
  if ( s != 0 ) return s;

  /* zapflege nur, wenn sich der Wert tatsächlich geändert hat */
  fest_diff = fest_alt - fest_neu;

  if ( fest_diff > 0.004 || fest_diff < - 0.004 ) 
  {
	s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
	if (  s != 0 ) return s;
  }

  /* Ausfuehren */
  /* s = FdTransact( errmld ); */
  s = FdTransactWithoutWork( errmld );
  if (  s != 0 ) return s;

  s = ReadPreis( artikel_nr, &avp, errmld );
  if (  s != 0 ) return s;

  FillProt( &info, &Buf_zartikel, &Buf_zartwg, avp, fest_neu, fest_alt, wegfall, code );

  s = feb_Protokol( &info, errmld );

  return s;
}

static long FebLadenZartfeb2( int alle,
                              int wegfall, long artikel_nr, long datum,
                              long festbetrag, long tagesdatum, char *errmld, long code )
{
  long s;
  struct FEB_PROT info;
  double fest_alt;
  double fest_neu;
  double fest_diff;
  double avp;

  s = ReadRecord_Zartikel( artikel_nr, errmld );

  if ( s == 100 ) 
	  return 0;   /* Artikel nicht vorhanden */

  if ( s != 0 )   
	  return s;   /* Fehler */

  ReadRecord_Zartwg( artikel_nr, errmld );

  s = ReadRecord_Zartfeb2( artikel_nr, errmld );
  if ( !( s == 0 || s == 100 ) ) return s;   /* Fehler */

  fest_alt = Buf_zartfeb2.FESTBETRAG2;

  if ( !alle && fest_alt > 0.004 ) return 0;

  if ( wegfall )
  {
     if ( s == 100 ) return 0;
     s = DeleteRecord_Zartfeb2( errmld );
     if ( s != 0 ) return s;
     fest_neu = 0.0;
  }
  else
  {
     Buf_zartfeb2.DATUM_FESTBETRAG2 = datum;
     Buf_zartfeb2.FESTBETRAG2 = ( ( double ) festbetrag ) / 100.0;
     s = StoreRecord_Zartfeb2( errmld );
     if ( s != 0 ) return s;
     fest_neu = Buf_zartfeb2.FESTBETRAG2;
  }

  /* zapflege nur, wenn sich der Wert tatsächlich geändert hat */
  fest_diff = fest_alt - fest_neu;

  if ( fest_diff > 0.004 || fest_diff < - 0.004 ) 
  {
	s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
	if (  s != 0 ) return s;
  }

  /* Ausfuehren */
  s = FdTransactWithoutWork( errmld );
  if (  s != 0 ) return s;

  s = ReadPreis( artikel_nr, &avp, errmld );
  if (  s != 0 ) return s;

  FillProt( &info, &Buf_zartikel, &Buf_zartwg, avp, fest_neu, fest_alt, wegfall, code );
  s = feb_Protokol( &info, errmld );

  return s;
}

static long StartWork( char *errmld )
  {
    long s;
    s = SqlBeginWork( );
    if ( s != 0 )
      {
        strcpy( errmld, "IFA-Festbetraege: " );
        strcat( errmld, DynErrmld() );
       }
    return s;
   }

static long EndWork( long status, char *errmld )
  {
    long s;
    if ( status == 0 )
      {
        s = SqlCommitWork( );
        if ( s != 0 )
          {
            strcpy( errmld, "IFA-Festbetraege: " );
            strcat( errmld, DynErrmld() );
           }
        return s;
       }
     else
      {
        s = SqlRollbackWork( );
        return status;
       }
   }


long FebLaden( char *mode, int wegfall, long artikel_nr, long datum,
               long festbetrag, char febstufe, long tagesdatum, char *errmld, long code )
{
   long s;
   int alle;

   if ( *mode == '0' || *mode == '1' )
     alle = 1;
   else
     alle = 0;

   s = StartWork( errmld );
   if ( s == 0 )
   {

     if ( *mode == '0' || *mode == '2' )
        s = FebLadenZartikel( alle, wegfall, artikel_nr, datum,
                              festbetrag, febstufe, tagesdatum, errmld, code );
     else
        s = FebLadenZartfeb2( alle, wegfall, artikel_nr, datum,
                              festbetrag, tagesdatum, errmld, code );
     s = EndWork( s, errmld );
   }
   return s;
}

long FebLadenClose( char *mode )
{
/* dummy !!!!!!!!!!!!!! */
  CloseZpreis( );
  return 0;
}



/* ------------------------------------------------------------- *
 *     Festbetraege2 loeschen                                    *
 * ------------------------------------------------------------- */


static long DoLoescheFestb2( int fd_delete, int fd_read,
                             long artikel_nr, long tagesdatum, char *errmld )
{
  long s;
  long art_nr;
  art_nr = artikel_nr;
  s = SqlExecutePrepare( fd_delete, &art_nr, NULL );
  if ( s == 0 )
  {
     s = SqlReadDeclCs( fd_read, &art_nr, NULL, &art_nr, NULL );
     if ( s == 0 )
     {
        s = StoreRecord_Zapflege( artikel_nr, tagesdatum, errmld );
        if (  s == 0 )
        {
           /* Ausfuehren */
           s = FdTransactWithoutWork( errmld );
        }
     }
     else if ( s == 100 )
     {
       s = 0;
     }
     else
     {
       strcpy( errmld, "Lesen Zartikel\n" );
       strcat( errmld, DynErrmld() );
     }
   }
   else
   {
      strcpy( errmld, "Loeschen Festbetrag-2\n" );
      strcat( errmld, DynErrmld() );
   }
   return s;
}


static long LoescheFestb2( int fd_delete, int fd_read,
                           long artikel_nr, long tagesdatum, char *errmld )
{
   long s;

   s = SqlBeginWork(  );
   if ( s != 0 )
   {
     strcpy( errmld, DynErrmld() );
     return s;
   }

   s = DoLoescheFestb2( fd_delete, fd_read, artikel_nr, tagesdatum, errmld );
   if ( s == 0 )
   {
       s = SqlCommitWork();
       if ( s != 0 )
          strcpy( errmld, DynErrmld() );
   }
   else
      SqlRollbackWork();
   return s;
}


long DeleteAll_Zartfeb2( long tagesdatum, char *errmld )
{
   int  fd_sel;
   int  fd_read;
   int  fd_delete;
   long s;
   long artikel_nr;

   if ( GetBufferDesc_Zapflege ( errmld ) != 0 ) return -1;

   s = SqlPrepareStmnt( &fd_delete,
                        "delete from ZARTFEB2 where ARTIKEL_NR=?",
                        "ZARTFEB2.ARTIKEL_NR",
                        NULL );
   if ( s != 0 )
   {
      strcpy( errmld, "Prepare Delete von ZARTFEB2\n" );
      strcat( errmld, DynErrmld() );
      return s;
   }
   s = SqlDeclareCs( &fd_read,
                     "select ARTIKEL_NR from ZARTIKEL where ARTIKEL_NR=?",
                     "ZARTIKEL.ARTIKEL_NR",
                     NULL );
   if ( s != 0 )
   {
     strcpy( errmld, "Declare Cursor von ZARTIKEL\n" );
     strcat( errmld, DynErrmld() );
     SqlFreePrepare( fd_delete );
     return s;
   }

   s = SqlOpenCsWh( &fd_sel, "select ARTIKEL_NR from ZARTFEB2" );
   if ( s != 0 )
   {
     strcpy( errmld, "Oeffnen von ZARTFEB2 \n" );
     strcat( errmld, DynErrmld() );
     SqlCloseCs( fd_read );
     SqlFreePrepare( fd_delete );
     return s;
   }
   s = SqlFetch( fd_sel, 1, &artikel_nr, NULL );
   if ( s == 100 )
   {
     strcpy( errmld, "Festbetrag-2 bereits geloescht" );
     SqlCloseCs( fd_sel );
     SqlCloseCs( fd_read );
     SqlFreePrepare( fd_delete );
     return 0;
   }
   if ( s != 0 )
   {
     strcpy( errmld, "Lesen von ZARTFEB2 \n" );
     strcat( errmld, DynErrmld() );
     SqlCloseCs( fd_sel );
     SqlCloseCs( fd_read );
     SqlFreePrepare( fd_delete );
     return s;
   }

   while ( s == 0 )
   {
      s = LoescheFestb2( fd_delete, fd_read, artikel_nr, tagesdatum, errmld );
      if ( s == 0 )
      {
         s = SqlFetch( fd_sel, 1, &artikel_nr, NULL );
         if ( !( s == 0 || s == 100 ) )
         {
           strcpy( errmld, "Lesen von ZARTFEB2 \n" );
           strcat( errmld, DynErrmld() );
         }
      }
   }

   if ( s == 100 ) s = 0;
   SqlCloseCs( fd_sel );
   SqlCloseCs( fd_read );
   SqlFreePrepare( fd_delete );
   if ( s == 0 )
      strcpy( errmld, "Loeschen der Festbetraege-2 erfolgreich" );
   return s;
}

