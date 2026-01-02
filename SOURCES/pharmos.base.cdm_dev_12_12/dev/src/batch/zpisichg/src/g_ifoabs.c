/* ---------------------------------------------------------------------- *
 *                            G_IFOABS.C                                  *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Liest die IFA-Artikeldatei ein und integriert         *
 *                  die Saetze in den lokalen UPDATE-POOL                 *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 04.03.00                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>

#include "ifa_satz.h"

#include "zifaoabschlag.h"
#include "g_ifoabs.h"

/* ---------------------------------------------------------------------- *
 * Funktion         : IfaOabschlag Test ob IfaOabschlag leer              *
 * ---------------------------------------------------------------------- */

int TestIfaOabschlagInsertMode( char *errmld )
{
	long status;
	long pzn;
	status = SqlRead( "select C02PZNABS from zifaoabschlag", &pzn, NULL );
	if ( status == 0 )
		return 0;
    if ( status == 100 )
        return 1;
    strcpy( errmld, "zifaoabschlag TestInsert: " );
    strcat( errmld, DynErrmld() );
	return -1;
}


/* ---------------------------------------------------------------------- *
 * Funktion         : IfaOabschlag lesen                                  *
 * ---------------------------------------------------------------------- */

static int fd_read;

long DeclareReadIfaOabschlag( char *errmld )
{
    char sql[1500];
    long status;

    strcpy( sql, "select " );
    strcat( sql, PROJECTION_ZIFAOABSCHLAG );
    strcat( sql, " from zifaoabschlag where C02PZNABS=? for update" );
    status = SqlDeclareCs( &fd_read, sql, "zifaoabschlag.C02PZNABS", NULL );
    if ( status != 0 )
    {
		strcpy( errmld, "zifaoabschlag: " );
		strcat( errmld, DynErrmld() );
		fd_read = -1;
    }
    return status;
}

long ReadIfaOabschlag( struct ZIFAOABSCHLAG *ifa, long artikel_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_read, ifa, NULL, &artikel_nr, NULL );
    if ( !( status == 0 || status == 100 ))
    {
		strcpy( errmld, "zifaoabschlag: " );
		strcat( errmld, DynErrmld() );
    }
    return status;
}


/* ---------------------------------------------------------------------- *
 * Funktion         : IfaOabschlag-Satz einfuegen                         *
 * ---------------------------------------------------------------------- */

static int fd_ins;

static long PrepareInsertIfaOabschlag( char *errmld )
{
    long status;
    status = SqlPrepareInsert ( &fd_ins, "zifaoabschlag", PROJECTION_ZIFAOABSCHLAG );
    if ( status != 0 )
    {
		strcpy( errmld, "zifaoabschlag: " );
		strcat( errmld, DynErrmld() );
		fd_ins = -1;
	}
    return status;
}

long InsertIfaOabschlag( struct ZIFAOABSCHLAG *ifa, char *errmld )
{
    long status;
    status = SqlExecutePrepare( fd_ins, ifa, NULL );
    if ( status != 0 )
    {
		strcpy( errmld, "zifaoabschlag Insert: " );
		strcat( errmld, DynErrmld() );
		return status;
    }
    status = SqlRowsProcessed();
    if ( status != 1 )
    {
		sprintf( errmld, "zifaoabschlag: %ld Saetze eingefuegt", status );
		return 1;
    }
    return 0;
}

static long InitIfaOabschlagWithDefault ( struct ZIFAOABSCHLAG *ifa, char *errmld )
{
	long status;
	status = SqlInitBufPrepare( fd_ins, ifa, NULL );
    if ( status != 0 )
	{
		strcpy( errmld, "zifaoabschlag Init: " );
		strcat( errmld, DynErrmld() );
	}
	return status;
}


/* ---------------------------------------------------------------------- *
 * Funktion         : IfaOabschlag-Satz updaten                           *
 * ---------------------------------------------------------------------- */

static int fd_upd;

static long PrepareUpdateIfaOabschlag( char *errmld )
{
    long status;
    char bed[50];
    sprintf( bed, "where current of %s", SqlGetCursor( fd_read ) );
    status = SqlPrepareUpdate ( &fd_upd, "zifaoabschlag", PROJECTION_ZIFAOABSCHLAG, bed );
    if ( status != 0 )
    {
		strcpy( errmld, "zifaoabschlag: " );
		strcat( errmld, DynErrmld() );
		fd_upd = -1;
     }
    return status;
}

long UpdateIfaOabschlag( struct ZIFAOABSCHLAG *ifa, char *errmld )
{
    long status;
    status = SqlExecutePrepare( fd_upd, ifa, NULL );
    if ( status != 0 )
    {
		strcpy( errmld, "zifaoabschlag: " );
		strcat( errmld, DynErrmld() );
    }
    return status;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : IfaOabschlag-Satz deleten                                *
 * ---------------------------------------------------------------------- */

static int fd_del;

static long PrepareDeleteIfaOabschlag( char *errmld )
{
    long status;
    char sql[70];
    sprintf( sql, "delete from zifaoabschlag where current of %s",
                   SqlGetCursor( fd_read ) );
    status = SqlPrepareStmnt ( &fd_del, sql, NULL );
    if ( status != 0 )
    {
		strcpy( errmld, "zifaoabschlag: " );
		strcat( errmld, DynErrmld() );
		fd_del = -1;
	}
    return status;
}

long DeleteIfaOabschlag( char *errmld )
{
    long status;
    status = SqlExecutePrepare( fd_del, NULL );
    if ( status != 0 )
    {
		strcpy( errmld, "zifaoabschlag: " );
		strcat( errmld, DynErrmld() );
    }
    return status;
}

/* ----------------- FDs ------------------------------- */

static void Init_All_FDs()
{
    fd_read = -1;
    fd_ins  = -1;
    fd_upd  = -1;
    fd_del  = -1;
}

void Close_IfaOabschlag_FDs()
{
    if ( fd_read != -1 ) SqlCloseCs ( fd_read );
    if ( fd_ins  != -1 ) SqlFreePrepare ( fd_ins );
    if ( fd_upd  != -1 ) SqlFreePrepare ( fd_upd );
    if ( fd_del  != -1 ) SqlFreePrepare ( fd_del );

    Init_All_FDs();
}

long Open_IfaOabschlag_FDs( char *errmld )
{
    long status;

    Init_All_FDs();

    /* Ifa lesen */
    status = DeclareReadIfaOabschlag( errmld );
    if ( status != 0 ) return status;

    /* Ifa einfuegen */
    status = PrepareInsertIfaOabschlag( errmld );
    if ( status != 0 ) return status;

    /* Ifa updaten   */
    status = PrepareUpdateIfaOabschlag( errmld );
    if ( status != 0 ) return status;

    /* Ifa loeschen  */
    status = PrepareDeleteIfaOabschlag( errmld );
    if ( status != 0 ) return status;

    return 0;
}



/* ---------------------------------------------------------------------- *
 * Funktion         : I f a B e a r b e i t e                             *
 * ---------------------------------------------------------------------- *
 * Aufgabe          : Bearbeitet einen ZIFA-Satz                          *
 * Eingabe-Parameter: ifa  = Zeiger auf den Puffer mit dem Ifa-Satz       *
 * Return-Wert      : keiner                                              *
 * Info             : - Diese Funktion wird fuer jeden gelesenen Ifa-     *
 *                      Satz ausgefuehrt.                                 *
 * ---------------------------------------------------------------------- */




/* ---------------------------------------------------------------------- *
 * Funktion         : Kopieren                                            *
 * ---------------------------------------------------------------------- */

static void str_lcpy( char *s1, char *s2, int lng1 )
{
   int lng2;
   lng2 = strlen( s2 );
   if ( lng2 < lng1 )
   {
      while ( lng2-- > 0 ) { *s1++ = *s2++; lng1--; }
      while ( lng1-- > 0 ) *s1++ = ' ';
   }
   else
      while ( lng1-- > 0 ) *s1++ = *s2++;
   *s1 = '\0';
}


static void ze_lcpy( char *s1, char ze, int lng )
{
	while ( lng-- > 0 ) *s1++ = ze;
	*s1 = '\0';
}


static long num_err( char* Wert )
{
   int i;
   int lng;

   lng = strlen( Wert );

   i = 0;
   while ( i < lng && Wert[i] == ' ' ) i++;
   if ( i == lng )
           return -1;   /* nur blanks */
   while ( i < lng && Wert[i] >= '0' && Wert[i] <= '9' ) i++;
   while ( i < lng && Wert[i] == ' ' ) i++;
   if ( i < lng )
           return -1;   /* nicht nur blanks am Ende */
   return 0;
}

static long str_tol( char *wert, int lng )
{
	char str[21];
	long num;

	str_lcpy( str, wert, lng );
	if ( num_err ( str ) == 0  )
		num = atol( str );
	else
		num = -1;

	if ( num >= 0 )
		return num;
	else
		return -1;
}

static short str_tos( char *wert, int lng )
{
	char str[21];
	int  num;
	str_lcpy( str, wert, lng );
	if ( num_err ( str ) == 0  )
		num = atoi( str );
	else
		num = -1;

	if ( num >= 0 )
		return num;
	else
		return -1;
}

static double get_preis( char *str )
{
   int lng;
   char buf[31];
   lng = strlen( str ) - 1;
   while ( lng >= 0 && str[lng] == ' ' ) lng--;
   lng++;

   if ( lng > 2 )
   {
      lng -= 2;
      memcpy( buf, str, lng );
      buf[lng] = '.';
      memcpy( &buf[lng+1], &str[lng], 2 );
      buf[lng + 3] = '\0';
   }
   else if ( lng == 2 )
   {
      memcpy( buf, "0.", 2 );
      memcpy( &buf[2], str, lng );
      buf[lng + 2] = '\0';
   }
   else
   {
      memcpy( buf, "0.0", 3 );
      memcpy( &buf[3], str, lng );
      buf[lng + 3] = '\0';
   }
   return atof( buf );
}

static double str_to_preis( char *wert, int lng )
{
	char str[21];

	str_lcpy( str, wert, lng );

	if ( num_err ( str ) == 0  )
		return get_preis( str );
	else
		return -1;
}



/* ---------------------------------------------------------------------- *
 * Funktion         : P l a u s i                                         *
 * ---------------------------------------------------------------------- */


/* --- PlausiString ----------------------------------------------------- */

#define  NOVALUE_PL     '9'

static char  NB_PLAUSI[ POSANZ_ZIFAOABSCHLAG + 1];


/* --- FehlerFelder initialisieren --- */

static void ClearNbPlausi( int pos )
{
	NB_PLAUSI[ pos ] = '0';
}

static void InitNbPlausi( )
{
	ze_lcpy( NB_PLAUSI, '1', POSANZ_ZIFAOABSCHLAG );
	ClearNbPlausi( P_ZIFAOABSCHLAG_C02PZNABS );
	ClearNbPlausi( P_ZIFAOABSCHLAG_DATUM_ANLAGE );
	ClearNbPlausi( P_ZIFAOABSCHLAG_DATUM_AENDER );
}

/* ---------- Test IFA auf "Keine Angabe" ---------------------------- */

static int TestNoValue( char *wert, int pos )
{
	if ( *wert == '\0' )
	{
		NB_PLAUSI[ pos ] = NOVALUE_PL;
		return 1;
	}
	NB_PLAUSI[ pos ] = '0';
	return 0;
}

int IsNoValue( int pos )
{
   return NB_PLAUSI[ pos ] == NOVALUE_PL;
}

/* ---------- Referenz auf Plausistring ---------------------------- */

char *GetRefToIfaOabschlagPlausi()
{
	return NB_PLAUSI;
}

int IsIfaOabschlagRecordComplete(  )
{
	int pos;
	for ( pos = 0; pos < POSANZ_ZIFAOABSCHLAG; pos++ )
	{
		if ( NB_PLAUSI[ pos ] == NOVALUE_PL ) return 0;
	}
	return 1;
}


/* ---- Datum ------------------ */

static long TestDatum( char *wert )
{
	long datum;
	if ( *wert == '\0' )
		return 0;
	datum = atol( wert );
	if ( TestPhoDate( datum ) )
		return datum;
	return 0;
}


/* ------------------ Pruefziffer ------------------------ */

static int GetPruefZiffer7 ( long zahl )
{
	int i, prziff;
	if (zahl == 0) return -1;
	prziff = 0;
	for (i=7; i>=2; i--)
	{
		zahl /= 10;
		prziff += i * ( int) ( zahl % 10 );
	}
	prziff %= 11;
	if (prziff == 10) prziff = 0;
	return prziff;
}

/*
   int TestPruefZiffer7 ( long zahl )
   Testet auf korrekte  Pruefziffer
   Eingabe-Parameter: zahl   = die zu pruefende 7-stellige Zahl
   Return-Wert      : 1 = die Zahl ist null
                      2 = die Zahl hat gueltige Pruefziffer
                      0 = die Zahl hat ungueltige Pruefziffer
*/

static int TestPruefZiffer7 ( long zahl )
{
	int prziff;
	prziff = GetPruefZiffer7( zahl );
	if ( prziff == -1 )
		return 1;
	else if ( prziff == (int) ( zahl % 10 ) )
		return 2;
	else
		return 0;
}

int IsPruefzifferOk( long zahl )
{
	if ( zahl <= 0 ) return 0;
	if ( TestPruefZiffer7 ( zahl ) != 2 ) return 0;
	return 1;
}


/* ---------- Wert aus IFA extrahieren ---------------- */

char *GetWert( sSatzArt *pSart, char* feld, char *errmld )
{
	char *wert;
	wert = GetWertFromSatzArtViaFeldName( pSart, feld );
	if ( wert == NULL )
		sprintf( errmld, "kein Wert fuer Feld %s", feld );
	return wert;
}


/* ---------- Spezielle Felder ------------------ */

int GetIfaPzn( long *pzn, sSatzArt *pSart, char *errmld )
{
	char *wert;
	*pzn = 0;
	if ( ( wert = GetWert( pSart, "C02PZNABS"  , errmld ) ) == NULL ) return 1;
	*pzn = str_tol( wert, 11 );
	return 0;
}

int GetIfaStatus( char *ssatz, sSatzArt *pSart, char *errmld )
{
   char *wert;
   *ssatz = '\0';
   if ( ( wert = GetWert( pSart, "C02SSATZ"  , errmld ) ) == NULL ) return 1;
   *ssatz = *wert;
   return 0;
}


/* -------------- IfaOabschlag fuellen ------------------- */

int IfaOabschlagFill( struct ZIFAOABSCHLAG *ifa, sSatzArt *pSart, long tages_datum, char *errmld )
{
   char *wert;

   /* --- FehlerFelder initialisieren --- */
   InitNbPlausi( );

   /* --- Datum bestimmen ---- */

   /* GueltigDatum Grundinfo */
   if ( ( wert = GetWert( pSart, "C02GDATABS", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOABSCHLAG_C02GDATABS ) )
		ifa->C02GDATABS = TestDatum( wert );    

   /* GueltigDatum Preisformation */
   /* gabs nicht mehr ab 2005, gibts wieder ab 2006 */
   if ( ( wert = GetWert( pSart, "C05GDATBPR", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOABSCHLAG_C05GDATBPR ) )
		ifa->C05GDATBPR = TestDatum( wert );    

   /* ---- Grunddaten ------ */

   /* Anbieterabschlag */
   if ( ( wert = GetWert( pSart, "C02ANBABS" , errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOABSCHLAG_C02ANBABS ) )
      str_lcpy( ifa->C02ANBABS, wert, L_ZIFAOABSCHLAG_C02ANBABS );

#ifdef VOR_12_01_2004
   /* Grosshandelsabschlag ( bssichg ) */
   if ( ( wert = GetWert( pSart, "C02GHABS" , errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOABSCHLAG_C02GHABS ) )
     str_lcpy( ifa->C02GHABS, wert, L_ZIFAOABSCHLAG_C02GHABS );

   /* Autidemartikel */
   if ( ( wert = GetWert( pSart, "C02AUTIDEM", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOABSCHLAG_C02AUTIDEM ) )
      str_lcpy( ifa->C02AUTIDEM, wert, L_ZIFAOABSCHLAG_C02AUTIDEM );
#endif

   /* Festbetrartikel */
   if ( ( wert = GetWert( pSart, "C02FBART", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOABSCHLAG_C02FBART ) )
      str_lcpy( ifa->C02FBART, wert, L_ZIFAOABSCHLAG_C02FBART );

  
   /* --- Preisinformation --- */

   /* Krankenh.Preis 8,2 */
   /* gabs nicht mehr ab 2005, gibts wieder ab 2006 */
   if ( ( wert = GetWert( pSart, "C05KAEPBPR", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOABSCHLAG_C05KAEPBPR ) )
      ifa->C05KAEPBPR = str_to_preis( wert, L_ZIFAOABSCHLAG_C05KAEPBPR );

   /* Herstellerabgabepreis 8,2 */
   /* gabs nicht mehr ab 2005, gibts wieder ab 2006 */
   if ( ( wert = GetWert( pSart, "C05GEPBPR", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOABSCHLAG_C05GEPBPR ) )
      ifa->C05GEPBPR = str_to_preis( wert, L_ZIFAOABSCHLAG_C05GEPBPR );

   /* Apo EK 8,2 */
   /* gabs nicht mehr ab 2005, gibts wieder ab 2006 */
   if ( ( wert = GetWert( pSart, "C05AEPBPR", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOABSCHLAG_C05AEPBPR ) )
      ifa->C05AEPBPR = str_to_preis( wert, L_ZIFAOABSCHLAG_C05AEPBPR );

   /* Apo VK incl MWST 8,2 */
   /* gabs nicht mehr ab 2005, gibts wieder ab 2006 */
   if ( ( wert = GetWert( pSart, "C05AVPBPR", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOABSCHLAG_C05AVPBPR ) )
      ifa->C05AVPBPR = str_to_preis( wert, L_ZIFAOABSCHLAG_C05AVPBPR );

   return 0;
}


/* ---------------------------------------------------------------------- *
 * Funktion        : IfaOabschlag-Satz aendern                            *
 * ---------------------------------------------------------------------- */



long IfaOabschlagAendere( sSatzArt *pSart, struct ZIFAOABSCHLAG *ifa,
                          long tages_datum, long Pzn, char Ssatz, 
                          long *anz_upd, long *anz_del, long *anz_ins,
                          char *errmld )
{
   long   rco;
   long   alt_datum;

   rco = ReadIfaOabschlag( ifa, Pzn, errmld );

   if ( !( rco == 100 || rco == 0 ) ) return 1;

   if ( rco == 0 )
   {
      alt_datum = ifa->DATUM_ANLAGE;
      ifa->C02PZNABS = Pzn;
      if ( IfaOabschlagFill( ifa, pSart, tages_datum, errmld ) != 0 ) return 1;
      ifa->DATUM_ANLAGE = alt_datum;
      ifa->DATUM_AENDER = tages_datum;

      if ( Ssatz == '2' )   /* Ifa Satz loeschen */
      {
         (*anz_del)++;
         rco = DeleteIfaOabschlag( errmld );
      }
      else  /* Ifa Satz aendern */
      {
         (*anz_upd)++;
         rco = UpdateIfaOabschlag( ifa, errmld );
      }
      if ( rco == 0 )
         return 0;
      else
         return 1;
   }
   else
   {
      if ( InitIfaOabschlagWithDefault( ifa, errmld ) != 0 ) return 1;

      ifa->C02PZNABS = Pzn;
      if ( IfaOabschlagFill( ifa, pSart, tages_datum, errmld ) != 0 ) return 1;
      ifa->DATUM_ANLAGE = tages_datum;
      ifa->DATUM_AENDER = 0;

      /* nur aufnehmen, wenn alle Felder belegt */
      if ( IsIfaOabschlagRecordComplete(  ) )
      {
          if ( Ssatz == '2' )   /* nichts tun, da Satz nicht vorhanden */
             rco = 0;
          else
          {
             anz_ins++;
             rco = InsertIfaOabschlag( ifa, errmld );
          }
          if ( rco == 0 )
             return 0;
          else
             return 1;
      }

      /* was soll man hier machen */
      return 2;
   }
}
