/* ---------------------------------------------------------------------- *
 *                            G_IFOART.C                                  *
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

#include "g_ifoart.h"
#include "pnamcode.h"

#include "wpp_prot.h"
#include "wpp_dbas.h"

/* ---------------------------------------------------------------------- *
 * Funktion         : ifaoart Test ob ifaoart leer                        *
 * ---------------------------------------------------------------------- */

int TestIfaOartInsertMode( char *errmld )
{
    long status;
    long pzn;
	char sql[100];
	sprintf( sql, "select A00PZN from %s", REL_P_IFAOART );
    status = SqlRead( sql, &pzn, NULL );
    if ( status == 0 )
            return 0;
    if ( status == 100 )
            return 1;
    sprintf( errmld, "%s TestInsert: %s", REL_P_IFAOART, DynErrmld() );
    return -1;
}


/* ---------------------------------------------------------------------- *
 * Funktion         : ifaoart lesen                                       *
 * ---------------------------------------------------------------------- */

static int fd_read;

static long DeclareReadIfaOart( char *errmld )
{
    char sql[1500];
	char desc[100];
    long status;

    sprintf( sql, "select %s from %s where A00PZN=? for update",
                   PROJ_P_IFAOART,
				   REL_P_IFAOART );
    sprintf( desc, "%s.A00PZN", REL_P_IFAOART );

    status = SqlDeclareCs( &fd_read, sql, desc, NULL );
    if ( status != 0 )
    {
      sprintf( errmld, "%s: %s", REL_P_IFAOART, DynErrmld() );
      fd_read = -1;
    }
    return status;
}

long ReadIfaOart( struct P_IFAOART *ifa, long artikel_nr, char *errmld )
{
    long status;
    status = SqlReadDeclCs( fd_read, ifa, NULL, &artikel_nr, NULL );
    if ( !( status == 0 || status == 100 ))
    {
      sprintf( errmld, "%s: %s", REL_P_IFAOART, DynErrmld() );
    }
    return status;
}


/* ---------------------------------------------------------------------- *
 * Funktion         : ifaoart-Satz einfuegen                              *
 * ---------------------------------------------------------------------- */

static int fd_ins;

static long PrepareInsertIfaOart( char *errmld )
{
    long status;
    status = SqlPrepareInsert ( &fd_ins, REL_P_IFAOART, PROJ_P_IFAOART );
    if ( status != 0 )
    {
      sprintf( errmld, "%s: %s", REL_P_IFAOART, DynErrmld() );
      fd_ins= -1;
     }
    return status;
}

long InsertIfaOart( struct P_IFAOART *ifa, char *errmld )
{
    long status;
    status = SqlExecutePrepare( fd_ins, ifa, NULL );
    if ( status != 0 )
    {
      sprintf( errmld, "%s Insert: %s", REL_P_IFAOART, DynErrmld() );
      return status;
    }
    status = SqlRowsProcessed();
    if ( status != 1 )
    {
      sprintf( errmld, "%s: %ld Saetze eingefuegt", REL_P_IFAOART, status );
      return 1;
    }
    return 0;
}

long InitIfaOartWithDefault ( struct P_IFAOART *ifa, char *errmld )
{
    long status;
    //status = SqlInitBufPrepare( fd_ins, ifa, NULL );
	int m_Fd;
	status = OpenBufferDescProj( &m_Fd, "zifaoart", "*", 
                              NULL, NULL, V_OHNE, errmld ); 
	FdInitTabBuf( m_Fd, ifa );
    if ( status != 0 )
    {
      sprintf( errmld, "%s Init: %s", REL_P_IFAOART, DynErrmld() );
    }
	CloseOneBufferDesc( m_Fd );
    return status;
}


/* ---------------------------------------------------------------------- *
 * Funktion         : ifaoart-Satz updaten                                *
 * ---------------------------------------------------------------------- */

static int fd_upd;

static long PrepareUpdateIfaOart( char *errmld )
{
    long status;
    char bed[50];
    sprintf( bed, "where current of %s", SqlGetCursor( fd_read ) );
    status = SqlPrepareUpdate ( &fd_upd, REL_P_IFAOART, PROJ_P_IFAOART, bed );
    if ( status != 0 )
    {
      sprintf( errmld, "%s: %s", REL_P_IFAOART, DynErrmld() );
      fd_ins= -1;
     }
    return status;
}

long UpdateIfaOart( struct P_IFAOART *ifa, char *errmld )
{
    long status;
    status = SqlExecutePrepare( fd_upd, ifa, NULL );
    if ( status != 0 )
    {
      sprintf( errmld, "%s: %s", REL_P_IFAOART, DynErrmld() );
    }
    return status;
}

/* ---------------------------------------------------------------------- *
 * Funktion         : ifaoart-Satz deleten                                *
 * ---------------------------------------------------------------------- */

static int fd_del;

static long PrepareDeleteIfaOart( char *errmld )
{
    long status;
    char sql[70];
    sprintf( sql, "delete from %s where current of %s",
		           REL_P_IFAOART,
                   SqlGetCursor( fd_read ) );
    status = SqlPrepareStmnt ( &fd_del, sql, NULL );
    if ( status != 0 )
    {
      sprintf( errmld, "%s: %s", REL_P_IFAOART, DynErrmld() );
      fd_ins= -1;
     }
    return status;
}

long DeleteIfaOart( char *errmld )
{
    long status;
    status = SqlExecutePrepare( fd_del, NULL );
    if ( status != 0 )
    {
      sprintf( errmld, "%s: %s", REL_P_IFAOART, DynErrmld() );
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

void Close_IfaOart_FDs()
{
    if ( fd_read != -1 ) SqlCloseCs ( fd_read );
    if ( fd_ins  != -1 ) SqlFreePrepare ( fd_ins );
    if ( fd_upd  != -1 ) SqlFreePrepare ( fd_upd );
    if ( fd_del  != -1 ) SqlFreePrepare ( fd_del );

    Init_All_FDs();
}

long Open_IfaOart_FDs( char *errmld )
{
    long status;

    Init_All_FDs();

    /* Ifa lesen */
    status = DeclareReadIfaOart( errmld );
    if ( status != 0 ) return status;

    /* Ifa einfuegen */
    status = PrepareInsertIfaOart( errmld );
    if ( status != 0 ) return status;

    /* Ifa updaten   */
    status = PrepareUpdateIfaOart( errmld );
    if ( status != 0 ) return status;

    /* Ifa loeschen  */
    status = PrepareDeleteIfaOart( errmld );
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
   size_t lng2;
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
   size_t lng;

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
   // commented statements are without further purpose
   //char str[21];
   int  num;
   //str_lcpy( str, wert, lng );
   if ( num_err ( wert ) == 0  )
           num = atoi( wert );
   else
           num = -1;

   if ( num >= 0 )
     return num;
   else
         return -1;
}

/*
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
   else
   {
      memcpy( buf, "0.", 2 );
      memcpy( &buf[2], str, lng );
      buf[lng + 2] = '\0';
   }
   return atof( buf );
}
*/

static double get_preis( char *str )
{
   size_t lng;
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

static char  NB_PLAUSI[ POSANZ_ZIFAOART + 1];



/* --- FehlerFelder initialisieren --- */

static void ClearNbPlausi( int pos )
{
   NB_PLAUSI[ pos ] = '0';
}

static void InitNbPlausi( )
{
   ze_lcpy( NB_PLAUSI, '1', POSANZ_ZIFAOART );
   ClearNbPlausi( P_ZIFAOART_A00PZN );
   ClearNbPlausi( P_ZIFAOART_A00PZN8 ); // abgeleites Feld von A00PZN
   ClearNbPlausi( P_ZIFAOART_A06PZNNF8 ); // abgeleites Feld von A06PZNNF
   ClearNbPlausi( P_ZIFAOART_A06PZNORIG8 ); // abgeleites Feld von A06PZNORIG
   ClearNbPlausi( P_ZIFAOART_DATUMGUELTIGAB );
   ClearNbPlausi( P_ZIFAOART_DATUM_ANLAGE );
   ClearNbPlausi( P_ZIFAOART_DATUM_AENDER );
   ClearNbPlausi( P_ZIFAOART_ARTIKEL_MC );
   ClearNbPlausi( P_ZIFAOART_A01ERSTATT ); // wird seit 2014 nicht mehr geliefert.

   /* Keine Reserve-Felder ab IFA-Version 248 */
   ClearNbPlausi( P_ZIFAOART_A01RESERV1 );
   ClearNbPlausi( P_ZIFAOART_A01RESERV2 );
   ClearNbPlausi( P_ZIFAOART_A01RESERV3 );
   ClearNbPlausi( P_ZIFAOART_A02RESERV1 );
   ClearNbPlausi( P_ZIFAOART_A02RESERV2 );
   ClearNbPlausi( P_ZIFAOART_A02RESERV3 );

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

static int TestNullZeroOrEmpty(char* str)
{
    if (str == NULL)
    {
        return 1; // string is null
    }

    // Trim leading and trailing white spaces
    while (isspace(*str))
    {
        str++;
    }

    if (*str == '\0')
    {
        return 1; // string is empty
    }

    long number = 0;
    if (sscanf(str, "%d", &number) == 1)
    {
        if (number == 0)
        {
            return 1; // Nummer is 0
        }
    }
    return 0; // string is not null or empty
}

/* ---------- Referenz auf Plausistring ---------------------------- */

char *GetRefToIfaOartPlausi()
{
        return NB_PLAUSI;
}


int IsIfaOartRecordComplete(  )
{
   int pos;
   for ( pos = 0; pos < POSANZ_ZIFAOART; pos++ )
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

/* --- Generiert Matchcode aus Artikelname --- */

#define MC_LNG  ( L_ZIFAOART_ARTIKEL_MC )
#define AR_LNG  ( L_ZIFAOART_A00PBEZ )

static void MakeArtMc( char *mc, char *name )
{
   int i;
   int j;

   i = 0;
   j = 0;
   while ( name[j] && j < AR_LNG && i < MC_LNG )
   {
      if ( name[j] != ' ' ) mc[i++] = name[j];
      j++;
   }
   while ( i < MC_LNG ) mc[i++] = ' ';
   mc[i] = '\0';
}



/* ------------------ Puefziffer ------------------------ */

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

int TestPruefZiffer7 ( long zahl )
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

static char *GetWert( sSatzArt *pSart, char* feld, char *errmld )
{
   char *wert;
   wert = GetWertFromSatzArtViaFeldName( pSart, feld );
   if ( wert == NULL )
      sprintf( errmld, "kein Wert fuer Feld %s", feld );
   return wert;
}


/* ---------- Spezielle Felder ------------------ */

#define  L_ZIFAOART_A00PZN 11

int GetIfaPzn( long *pzn, sSatzArt *pSart, char *errmld )
{
   char *wert;
   *pzn = 0;
   if ( ( wert = GetWert( pSart, "A00PZN"  , errmld ) ) == NULL ) return 1;
   *pzn = str_tol( wert, L_ZIFAOART_A00PZN );
   return 0;
}

#define  L_ZIFAOART_A06PZNNF 11

/* nur in zpifaart */
int GetIfaPznNF( long *pzn, sSatzArt *pSart, char *errmld )
{
   char *wert;
   *pzn = 0;
   if ( ( wert = GetWert( pSart, "A06PZNNF"  , errmld ) ) == NULL ) return 1;
   *pzn = str_tol( wert, L_ZIFAOART_A06PZNNF );
   return 0;
}

int GetIfaStatus( char *ssatz, sSatzArt *pSart, char *errmld )
{
   char *wert;
   *ssatz = '\0';
   if ( ( wert = GetWert( pSart, "A00SSATZ"  , errmld ) ) == NULL ) return 1;
   *ssatz = *wert;
   return 0;
}

int GetLoeschKenn( char *LoeKenn, sSatzArt *pSart, char *errmld )
{
   char *wert;
   /* --- Loeschkennzeichen --- */
   *LoeKenn = '\0';
   if ( ( wert = GetWert( pSart, "A00LKZ", errmld ) ) == NULL ) return 1;
   *LoeKenn = *wert;
   return 0;
}

int GetA01SGEPDM( char *Kenn, sSatzArt *pSart, char *errmld )
{
   char *wert;
   /* --- Kennzeichen --- */
   *Kenn = '\0';
							/*   "A01SGEPDM" */
   if ( ( wert = GetWert( pSart, "A01SAPU", errmld ) ) == NULL ) return 1;
   *Kenn = *wert;
   return 0;
}

int GetA01SUVP( char *Kenn, sSatzArt *pSart, char *errmld )
{
   char *wert;
   /* --- Kennzeichen --- */
   *Kenn = '\0';
							
   if ( ( wert = GetWert( pSart, "A01SUVP", errmld ) ) == NULL ) return 1;
   *Kenn = *wert;
   return 0;
}

int GetA01SAEPDM( char *Kenn, sSatzArt *pSart, char *errmld )
{
   char *wert;
   /* --- Kennzeichen --- */
   *Kenn = '\0';
							/*   "A01SAEPDM"  */
   if ( ( wert = GetWert( pSart, "A01SAEP", errmld ) ) == NULL ) return 1;
   *Kenn = *wert;
   return 0;
}

int GetA01SAVPDM( char *Kenn, sSatzArt *pSart, char *errmld )
{
   char *wert;
   /* --- Kennzeichen --- */
   *Kenn = '\0';
							/*   "A01SAVPDM"  */
   if ( ( wert = GetWert( pSart, "A01SAVP", errmld ) ) == NULL ) return 1;
   *Kenn = *wert;
   return 0;
}

int GetA01SZBV  ( char *Kenn, sSatzArt *pSart, char *errmld )
{
   // value no longer avialable in ifa version 248, set default
   // char *wert;
   
   /* --- Kennzeichen --- */
   *Kenn = '\0';
   
   /* if ((wert = GetWert(pSart, "A01SZBV", errmld)) == NULL) return 1;
   *Kenn = *wert; */
   
   return 0;
}

int GetA01SAB130A  ( char *Kenn, sSatzArt *pSart, char *errmld )
{
   char *wert;
   /* --- Kennzeichen --- */
   *Kenn = '\0';
   if ( ( wert = GetWert( pSart, "A01SAB130A", errmld ) ) == NULL ) return 1;
   *Kenn = *wert;
   return 0;
}


/* -------------- IfaOart fuellen ------------------- */

int IfaOartFill( struct P_IFAOART *ifa, sSatzArt *pSart, long tages_datum, char *errmld )
{
   char *wert;
   long datum;
   long vgldat;

   /* --- FehlerFelder initialisieren --- */
   InitNbPlausi( );

   /* --- Datum bestimmen ---- */

   /* GueltigDatum Preisformation */
   if ( ( wert = GetWert( pSart, "A01GDAT", errmld ) ) == NULL ) return 1;
   datum = TestDatum( wert );    /* datum = Datum Preisinfo */

   /* wenn Datum aus Preisinfo nicht vorhanden, dann */
   /* datum = groesstes sonstige datum */
   if ( datum == 0 )
   {
      /* GueltigDatum Grunddaten */
      if ( ( wert = GetWert( pSart, "A00GDAT", errmld ) ) == NULL ) return 1;
      vgldat = TestDatum( wert );
      if ( vgldat > datum ) datum = vgldat;

      /* GueltigDatum Lagerinformation */
      if ( ( wert = GetWert( pSart, "A05GDAT", errmld ) ) == NULL ) return 1;
      vgldat = TestDatum( wert );
      if ( vgldat > datum ) datum = vgldat;

      /* GueltigDatum Packungsinformation */
      if ( ( wert = GetWert( pSart, "A04GDAT", errmld ) ) == NULL ) return 1;
      vgldat = TestDatum( wert );
      if ( vgldat > datum ) datum = vgldat;

      /* GueltigDatum Rechtsinformation */
      if ( ( wert = GetWert( pSart, "A02GDAT", errmld ) ) == NULL ) return 1;
      vgldat = TestDatum( wert );
      if ( vgldat > datum ) datum = vgldat;

      /* GueltigDatum Vertriebsformation */
      if ( ( wert = GetWert( pSart, "A03GDAT", errmld ) ) == NULL ) return 1;
      vgldat = TestDatum( wert );
      if ( vgldat > datum ) datum = vgldat;

      /* GueltigDatum Verweisinformation */
      if ( ( wert = GetWert( pSart, "A06GDAT", errmld ) ) == NULL ) return 1;
      vgldat = TestDatum( wert );
      if ( vgldat > datum ) datum = vgldat;

      /* --- ZuzahlungsInfo ( Therapiegerechte Verpackungsgrössen ) --- */ 
      if ( ( wert = GetWert( pSart, "A09GDAT", errmld ) ) == NULL ) return 1;
      vgldat = TestDatum( wert );
      if ( vgldat > datum ) datum = vgldat;

	  /* ---  --- */ 
      if ( ( wert = GetWert( pSart, "A11GDAT", errmld ) ) == NULL ) return 1;
      vgldat = TestDatum( wert );
      if ( vgldat > datum ) datum = vgldat;

      /* wenn kein Datum vorhanden, dann datum = tagesdatum */
      if ( datum == 0 )
         datum = tages_datum;
   }
   ifa->DATUMGUELTIGAB = datum;
   ClearNbPlausi( P_ZIFAOART_DATUMGUELTIGAB );

   /* ---- Grunddaten ------ */

   /* Artikelname */
   if ( ( wert = GetWert( pSart, "A00PBEZ" , errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A00PBEZ ) )
   {
      str_lcpy( ifa->A00PBEZ, wert, L_ZIFAOART_A00PBEZ );
      /* Artikel_Mc */
      MakeArtMc( ifa->ARTIKEL_MC, ifa->A00PBEZ );
   }

   /* Packung: Menge */
   if ( ( wert = GetWert( pSart, "A00PGMENG" , errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A00PGMENG ) )
      str_lcpy( ifa->A00PGMENG, wert, L_ZIFAOART_A00PGMENG );

   /* Packung: Mengeneinheit */
   if ( ( wert = GetWert( pSart, "A00PGEINH" , errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A00PGEINH ) )
     str_lcpy( ifa->A00PGEINH, wert, L_ZIFAOART_A00PGEINH );

   /* Darreichung */
   if ( ( wert = GetWert( pSart, "A00DARFO", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A00DARFO ) )
      str_lcpy( ifa->A00DARFO, wert, L_ZIFAOART_A00DARFO );

   /* Herstellernummer */
#define  L_ZIFAOART_A00ANBNR  11

   /*  A00ANBNR7 (formerly A00ANBNR6) */
   /*  A00ANBNRx changes its suffix from time to time, so its
       corresponding db column has no suffix, see also A00OEVNR / A00ZINNR */
   if ( ( wert = GetWert( pSart, "A00ANBNR7", errmld ) ) == NULL ) return 1; // fieldname changed by ifa
   if ( !TestNoValue( wert, P_ZIFAOART_A00ANBNR ) )
      ifa->A00ANBNR = str_tol( wert, L_ZIFAOART_A00ANBNR );

   /* Artikeltyp: Klinikpackung */
   if ( ( wert = GetWert( pSart, "A00ATYP", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A00ATYP ) )
      str_lcpy( ifa->A00ATYP, wert, L_ZIFAOART_A00ATYP );

   /* GTIN und EAN-Nummer aus GTIN */
   if ( ( wert = GetWert( pSart, "A00GTIN", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A00GTIN ) )
      str_lcpy( ifa->A00GTIN, wert, L_ZIFAOART_A00GTIN );

   if ( *wert != '0' && *wert != '\0' ) // 14- stellige EAN (= Ziffer!=0 an 1.Stelle) wird aktuell nicht übernommen!
	   strcpy(wert, "0000000000000");
   else if ( *wert != '\0' )
	   wert = wert + 1; // shift 1 right

   if ( !TestNoValue( wert, P_ZIFAOART_A00EAN ) )
      str_lcpy( ifa->A00EAN, wert, L_ZIFAOART_A00EAN );
   
   /* NTIN */
   if ( ( wert = GetWert( pSart, "A00NTIN", errmld ) ) == NULL ) return 1;

   if ( *wert != '\0' )
      wert = wert + 1; // shift 1 right - no leading zeros in carticlecodes!
	
   if ( !TestNoValue( wert, P_ZIFAOART_A00NTIN ) )
      str_lcpy( ifa->A00NTIN, wert, L_ZIFAOART_A00NTIN );

   /* ArtikelNr-Hersteller */
   if ( ( wert = GetWert( pSart, "A00ARTNR", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A00ARTNR ) )
      str_lcpy( ifa->A00ARTNR, wert, L_ZIFAOART_A00ARTNR );

   /* Hilfsmittel PositionsNr */
   /* field is no longer available in the ifa file (version 248) */
   /* if ((wert = GetWert(pSart, "A00HMNR", errmld)) == NULL) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A00HMNR ) )
      str_lcpy( ifa->A00HMNR , wert, L_ZIFAOART_A00HMNR ); */

   /* PNAM */
   if ( ( wert = GetWert( pSart, "A00PNAM", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A00PNAM ) )
   {
          ConvertToWIN32Code( ( unsigned char *) wert );
      str_lcpy( ifa->A00PNAM, wert, L_ZIFAOART_A00PNAM );
   }

   /* WGA */
   if ( ( wert = GetWert( pSart, "A00WGA", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A00WGA ) )
      str_lcpy( ifa->A00WGA, wert, L_ZIFAOART_A00WGA );

   /* ---- Lagerinformation */

   /* Kennz. Verfalldatum  */
   if ( ( wert = GetWert( pSart, "A05VFDAT", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A05VFDAT ) )
      str_lcpy( ifa->A05VFDAT, wert, L_ZIFAOART_A05VFDAT );

   /* Laufzeit in Monaten <= 60 */
#define  L_ZIFAOART_A05LZEIT 6
   if ( ( wert = GetWert( pSart, "A05LZEIT", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A05LZEIT ) )
      ifa->A05LZEIT = str_tos( wert, L_ZIFAOART_A05LZEIT );

   /* Kennzeichen Kuehlkette */
   if ( ( wert = GetWert( pSart, "A05KKETTE", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A05KKETTE ) )
      str_lcpy( ifa->A05KKETTE, wert, L_ZIFAOART_A05KKETTE );

   /* Lagertemperatur max */
   if ( ( wert = GetWert( pSart, "A05TMAX", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A05TMAX ) )
      str_lcpy( ifa->A05TMAX, wert, L_ZIFAOART_A05TMAX );

   /* Lagertemperatur min */
   if ( ( wert = GetWert( pSart, "A05TMIN", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A05TMIN ) )
      str_lcpy( ifa->A05TMIN, wert, L_ZIFAOART_A05TMIN );

   /* Kennz. lichtempfindlich */
   if ( ( wert = GetWert( pSart, "A05LICHT", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A05LICHT ) )
      str_lcpy( ifa->A05LICHT, wert, L_ZIFAOART_A05LICHT );

   /* Kennz. feuchtempfindlich */
   if ( ( wert = GetWert( pSart, "A05FEUCHT", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A05FEUCHT ) )
      str_lcpy( ifa->A05FEUCHT, wert, L_ZIFAOART_A05FEUCHT );

   /* Kennz. lageempfindlich */
   if ( ( wert = GetWert( pSart, "A05LAGE", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A05LAGE ) )
      str_lcpy( ifa->A05LAGE, wert, L_ZIFAOART_A05LAGE );

   /* Kennz. zerbrechlich */
   if ( ( wert = GetWert( pSart, "A05ZERBR", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A05ZERBR ) )
      str_lcpy( ifa->A05ZERBR, wert, L_ZIFAOART_A05ZERBR );

   /* Kennz. Eichung */
   if ( ( wert = GetWert( pSart, "A05EICH", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A05EICH ) )
      str_lcpy( ifa->A05EICH, wert, L_ZIFAOART_A05EICH );

   /* Laufzeit Eichung */
#define  L_ZIFAOART_A05LZEICH  6
   if ( ( wert = GetWert( pSart, "A05LZEICH", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A05LZEICH ) )
      ifa->A05LZEICH = str_tos( wert, L_ZIFAOART_A05LZEICH );

   /* --- Packungsinformation --- */

   /* Laenge */
   if ( ( wert = GetWert( pSart, "A04LAENGE", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A04LAENGE ) )
      str_lcpy( ifa->A04LAENGE, wert, L_ZIFAOART_A04LAENGE );

   /* Hoehe  */
   if ( ( wert = GetWert( pSart, "A04HOEHE", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A04HOEHE ) )
      str_lcpy( ifa->A04HOEHE, wert, L_ZIFAOART_A04HOEHE );

   /* Breite */
   if ( ( wert = GetWert( pSart, "A04BREITE", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A04BREITE ) )
      str_lcpy( ifa->A04BREITE, wert, L_ZIFAOART_A04BREITE );

   /* Gewicht */
   if ( ( wert = GetWert( pSart, "A04GWCHT", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A04GWCHT ) )
      str_lcpy( ifa->A04GWCHT, wert, L_ZIFAOART_A04GWCHT );

   /* Verpackungsart */
   if ( ( wert = GetWert( pSart, "A04VPART", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A04VPART ) )
      str_lcpy( ifa->A04VPART, wert, L_ZIFAOART_A04VPART );

   /* Mindestbestellmenge */
   if ( ( wert = GetWert( pSart, "A04MBEST", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A04MBEST ) )
      str_lcpy( ifa->A04MBEST, wert, L_ZIFAOART_A04MBEST );

   /* --- Preisinformation --- */

   /* Krankenh.Preis 8,2 */
							/*   "A01KAEPDM"    */
   if ( ( wert = GetWert( pSart, "A01KAEP", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01KAEPDM ) )
      ifa->A01KAEPDM = str_to_preis( wert, L_ZIFAOART_A01KAEPDM );

   /* Herstellerabgabepreis 8,2 */
							/*   "A01GEPDM"   */
   if ( ( wert = GetWert( pSart, "A01APU", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01GEPDM ) )
      ifa->A01GEPDM = str_to_preis( wert, L_ZIFAOART_A01GEPDM );

   /* Kennz. AMPreisV: Taxplichtig, Nettoaertikel */
   if ( ( wert = GetWert( pSart, "A01AMPVSGB", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01AMPVSGB ) )
      str_lcpy( ifa->A01AMPVSGB, wert, L_ZIFAOART_A01AMPVSGB );

   if ( ( wert = GetWert( pSart, "A01AMPVAMG", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01AMPVAMG ) )
      str_lcpy( ifa->A01AMPVAMG, wert, L_ZIFAOART_A01AMPVAMG );

   /* Apo EK 8,2 */
							/*   "A01AEPDM"   */
   if ( ( wert = GetWert( pSart, "A01AEP", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01AEPDM ) )
      ifa->A01AEPDM = str_to_preis( wert, L_ZIFAOART_A01AEPDM );

   /* Apo VK incl MWST 8,2 */
							/*   "A01AVPDM"   */ 
   if ( ( wert = GetWert( pSart, "A01AVP", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01AVPDM ) )
      ifa->A01AVPDM = str_to_preis( wert, L_ZIFAOART_A01AVPDM );

   /* ZBV-Preis */
   /* field is no longer available in the ifa file (version 248) */
   /* if ((wert = GetWert(pSart, "A01ZBV", errmld)) == NULL) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01ZBV ) )
      ifa->A01ZBV = str_to_preis( wert, L_ZIFAOART_A01ZBV ); */

   /* UVP-Preis */
   if ( ( wert = GetWert( pSart, "A01UVP", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01UVP ) )
      ifa->A01UVP = str_to_preis( wert, L_ZIFAOART_A01UVP );

   /* MWST Kennzeichen */
   if ( ( wert = GetWert( pSart, "A01MWST", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01MWST ) )
      str_lcpy( ifa->A01MWST, wert, L_ZIFAOART_A01MWST );

   /* --- Rechtsinformation --- */

   /* Kennz. Arzneimittel */
   if ( ( wert = GetWert( pSart, "A02AM", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02AM ) )
      str_lcpy( ifa->A02AM, wert, L_ZIFAOART_A02AM );

   /* Kennz. Medizinprodukt */
   if ( ( wert = GetWert( pSart, "A02MP", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02MP ) )
      str_lcpy( ifa->A02MP, wert, L_ZIFAOART_A02MP );

   /* Kennz. Apothekenpflichtig */
   if ( ( wert = GetWert( pSart, "A02APPFL", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02APPFL ) )
      str_lcpy( ifa->A02APPFL, wert, L_ZIFAOART_A02APPFL );

   /* Kennz. Verschreibungspflichtig */
   if ( ( wert = GetWert( pSart, "A02VSPFL", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02VSPFL ) )
      str_lcpy( ifa->A02VSPFL, wert, L_ZIFAOART_A02VSPFL );

   /* Betaeubungsmittel */
   if ( ( wert = GetWert( pSart, "A02BTM", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02BTM ) )
      str_lcpy( ifa->A02BTM, wert, L_ZIFAOART_A02BTM );

   /* Kennz. TFG */
   if ( ( wert = GetWert( pSart, "A02TFG", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02TFG ) )
      str_lcpy( ifa->A02TFG, wert, L_ZIFAOART_A02TFG );

   /* Kennz. Droge/Chemikalie */
   if ( ( wert = GetWert( pSart, "A02DROCH", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02DROCH ) )
      str_lcpy( ifa->A02DROCH, wert, L_ZIFAOART_A02DROCH );

   /* Kennz. Tier-AM */
   if ( ( wert = GetWert( pSart, "A02TIERAM", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02TIERAM ) )
      str_lcpy( ifa->A02TIERAM, wert, L_ZIFAOART_A02TIERAM );

   /* Negativ-Kennzeichen */
   if ( ( wert = GetWert( pSart, "A02NEGLIS", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02NEGLIS ) )
      str_lcpy( ifa->A02NEGLIS, wert, L_ZIFAOART_A02NEGLIS );

   /* Hilfsmittel zum Verbrauch */
   if ( ( wert = GetWert( pSart, "A02HMZV", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02HMZV ) )
      str_lcpy( ifa->A02HMZV, wert, L_ZIFAOART_A02HMZV );

   /* --- Vertriebsinformation --- */

   /* Vertriebsstatus */
   if ( ( wert = GetWert( pSart, "A03VTSTAT", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A03VTSTAT ) )
      str_lcpy( ifa->A03VTSTAT, wert, L_ZIFAOART_A03VTSTAT );

   /* Kennz. Vertriebsweg Grosshandel */
   if ( ( wert = GetWert( pSart, "A03VWGGH", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A03VWGGH ) )
      str_lcpy( ifa->A03VWGGH, wert, L_ZIFAOART_A03VWGGH );

   /* Kennz. Vertriebsweg Apotheke */
   if ( ( wert  = GetWert( pSart, "A03VWGAPO", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A03VWGAPO ) )
      str_lcpy( ifa->A03VWGAPO, wert, L_ZIFAOART_A03VWGAPO );

   /* Kennz. Vertriebsweg Krankenhaus-Apotheke */
   if ( ( wert  = GetWert( pSart, "A03VWGKAP", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A03VWGKAP ) )
      str_lcpy( ifa->A03VWGKAP, wert, L_ZIFAOART_A03VWGKAP );

   /* Kennz. Vertriebsweg sonstiger Einzelhandel */
   if ( ( wert  = GetWert( pSart, "A03VWGSEH", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A03VWGSEH ) )
      str_lcpy( ifa->A03VWGSEH, wert, L_ZIFAOART_A03VWGSEH );

   /* Verkehrsfaehigkeits-Status */
   if ( ( wert  = GetWert( pSart, "A03VKSTAT", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A03VKSTAT ) )
      str_lcpy( ifa->A03VKSTAT, wert, L_ZIFAOART_A03VKSTAT );

   /* --- Verweisinformation --- */

   /* PZN Nachfolger */
   if ( ( wert = GetWert( pSart, "A06PZNNF", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A06PZNNF ) )
   {
		ifa->A06PZNNF8 = str_tol( wert, L_ZIFAOART_A06PZNNF );
		ifa->A06PZNNF = sel_ArtNoByCode( str_tol( wert, L_ZIFAOART_A06PZNNF ), errmld );
   }

   /* --- ZuzahlungsInfo ( Therapiegerechte Verpackungsgrössen ) --- */

   /* A09THGP */
   if ( ( wert = GetWert( pSart, "A09THGP", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A09THGP ) )
      str_lcpy( ifa->A09THGP, wert, L_ZIFAOART_A09THGP );


   /* A02LIFSTYL */ 
   if ( ( wert = GetWert( pSart, "A02LIFSTYL", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02LIFSTYL ) )
      str_lcpy( ifa->A02LIFSTYL, wert, L_ZIFAOART_A02LIFSTYL );

   /* A02AUSNREI */ 
   if ( ( wert = GetWert( pSart, "A02AUSNREI", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02AUSNREI ) )
      str_lcpy( ifa->A02AUSNREI, wert, L_ZIFAOART_A02AUSNREI );

   /* A02GENER */ 
   if ( ( wert = GetWert( pSart, "A02GENER", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02GENER ) )
      str_lcpy( ifa->A02GENER, wert, L_ZIFAOART_A02GENER );

   /* A02SDB */ 
   if ( ( wert = GetWert( pSart, "A02SDB", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02SDB ) )
      str_lcpy( ifa->A02SDB, wert, L_ZIFAOART_A02SDB );

   /* A02NEM */ 
   if ( ( wert = GetWert( pSart, "A02NEM", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02NEM ) )
      str_lcpy( ifa->A02NEM, wert, L_ZIFAOART_A02NEM );

   /* A06PZNORIG */ 
#define  L_ZIFAOART_A06PZNORIG 11
   if ( ( wert = GetWert( pSart, "A06PZNORIG", errmld ) ) == NULL )
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A06PZNORIG ) )
   {
		ifa->A06PZNORIG8 = str_tol( wert, L_ZIFAOART_A06PZNORIG );
		ifa->A06PZNORIG = sel_ArtNoByCode( str_tol( wert, L_ZIFAOART_A06PZNORIG ), errmld );
   }

   /* A02ZULREG */ 
   if ( ( wert = GetWert( pSart, "A02ZULREG", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02ZULREG ) )
      str_lcpy( ifa->A02ZULREG, wert, L_ZIFAOART_A02ZULREG );

   /* A02LEBENSM */ 
   if ( ( wert = GetWert( pSart, "A02LEBENSM", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02LEBENSM ) )
      str_lcpy( ifa->A02LEBENSM, wert, L_ZIFAOART_A02LEBENSM );

   /* A02DIAET */ 
   if ( ( wert = GetWert( pSart, "A02DIAET", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02DIAET ) )
      str_lcpy( ifa->A02DIAET, wert, L_ZIFAOART_A02DIAET );





   /* A02HOMOEO */ 
   if ( ( wert = GetWert( pSart, "A02HOMOEO", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02HOMOEO ) )
      str_lcpy( ifa->A02HOMOEO, wert, L_ZIFAOART_A02HOMOEO );

   /* A02ANTHRO */ 
   if ( ( wert = GetWert( pSart, "A02ANTHRO", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02ANTHRO ) )
      str_lcpy( ifa->A02ANTHRO, wert, L_ZIFAOART_A02ANTHRO );

   /* A02PHYTO */ 
   if ( ( wert = GetWert( pSart, "A02PHYTO", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02PHYTO ) )
      str_lcpy( ifa->A02PHYTO, wert, L_ZIFAOART_A02PHYTO );

   /* A02BIOZID */ 
   if ( ( wert = GetWert( pSart, "A02BIOZID", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02BIOZID ) )
      str_lcpy( ifa->A02BIOZID, wert, L_ZIFAOART_A02BIOZID );

   /* A02PSM */ 
   if ( ( wert = GetWert( pSart, "A02PSM", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02PSM ) )
      str_lcpy( ifa->A02PSM, wert, L_ZIFAOART_A02PSM );

   /* A02TREZEP */ 
   if ( ( wert = GetWert( pSart, "A02TREZEP", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02TREZEP ) )
      str_lcpy( ifa->A02TREZEP, wert, L_ZIFAOART_A02TREZEP );

   /* A0247AMG */ 
   if ( ( wert = GetWert( pSart, "A0247AMG", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A0247AMG ) )
      str_lcpy( ifa->A0247AMG, wert, L_ZIFAOART_A0247AMG );

    /* // Wegfall 06/2012: A01GHABSCH 
   if ( ( wert = GetWert( pSart, "A01GHABSCH", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01GHABSCH ) )
      str_lcpy( ifa->A01GHABSCH, wert, L_ZIFAOART_A01GHABSCH ); */ 

   	/* // Wegfall 07/2014:  "A01ERSTATT" --> umbenannt in "A01RB130B"
   if ( ( wert = GetWert( pSart, "A01RB130B", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01ERSTATT ) )
      ifa->A01ERSTATT = str_to_preis( wert, L_ZIFAOART_A01ERSTATT ); */

   /*   "A00PPN" */ 
   if ( ( wert = GetWert( pSart, "A00PPN", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A00PPN ) )
	  str_lcpy( ifa->A00PPN, wert, L_ZIFAOART_A00PPN );
     
   /*   "A01AB130A2" */ 
   if ( ( wert = GetWert( pSart, "A01AB130A2", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01AB130A2 ) )
	  ifa->A01AB130A2 = str_to_preis( wert, L_ZIFAOART_A01AB130A2 );
	    
   /*   "A11VERIFIZ" */ 
   if ( ( wert = GetWert( pSart, "A11VERIFIZ", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02VERIFIZ ) )
	  str_lcpy( ifa->A02VERIFIZ, wert, L_ZIFAOART_A02VERIFIZ );
  
   /*   "A0252B" */ 
   if ( ( wert = GetWert( pSart, "A0252B", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A0252B ) )
	  str_lcpy( ifa->A0252B, wert, L_ZIFAOART_A0252B );

    /*   "A02BIOSIEG" */ 
   if ( ( wert = GetWert( pSart, "A02BIOSIEG", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02BIOSIEG ) )
	  str_lcpy( ifa->A02BIOSIEG, wert, L_ZIFAOART_A02BIOSIEG );

    /*   "A02KOSMET" */ 
   if ( ( wert = GetWert( pSart, "A02KOSMET", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02KOSMET ) )
	  str_lcpy( ifa->A02KOSMET, wert, L_ZIFAOART_A02KOSMET );

    /*   "A02STERIL" */ 
   if ( ( wert = GetWert( pSart, "A02STERIL", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02STERIL ) )
	  str_lcpy( ifa->A02STERIL, wert, L_ZIFAOART_A02STERIL );

   /* Reserve-fields no longer available in ifa version 248 */
   /*   "A01RESERV1" *
   if ( ( wert = GetWert( pSart, "A01RESERV1", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01RESERV1 ) )
	  ifa->A01RESERV1 = str_to_preis( wert, L_ZIFAOART_A01RESERV1 );

   *   "A01RESERV2" *
   if ( ( wert = GetWert( pSart, "A01RESERV2", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01RESERV2 ) )
	  ifa->A01RESERV2 = str_to_preis( wert, L_ZIFAOART_A01RESERV2 );

   *   "A01RESERV3" *
   if ( ( wert = GetWert( pSart, "A01RESERV3", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01RESERV3 ) )
	  ifa->A01RESERV3 = str_to_preis( wert, L_ZIFAOART_A01RESERV3 );

   *   "A02RESERV1" *
   if ( ( wert = GetWert( pSart, "A02RESERV1", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02RESERV1 ) )
	  str_lcpy( ifa->A02RESERV1, wert, L_ZIFAOART_A02RESERV1 );

   *   "A02RESERV2" *
   if ( ( wert = GetWert( pSart, "A02RESERV2", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02RESERV2 ) )
	  str_lcpy( ifa->A02RESERV2, wert, L_ZIFAOART_A02RESERV2 );

   *   "A02RESERV3" * 
   if ( ( wert = GetWert( pSart, "A02RESERV3", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02RESERV3 ) )
	  str_lcpy( ifa->A02RESERV3, wert, L_ZIFAOART_A02RESERV3 );
   */

   /*   "A02130A18" */ 
   if ( ( wert = GetWert( pSart, "A02130A18", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02130A18 ) )
	  str_lcpy( ifa->A02130A18, wert, L_ZIFAOART_A02130A18 );

   /*   "A02130A1A8" */ 
   if ( ( wert = GetWert( pSart, "A02130A1A8", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02130A1A8 ) )
	  str_lcpy( ifa->A02130A1A8, wert, L_ZIFAOART_A02130A1A8 );

   /*   "A02ELEKTRO" */ 
   if ( ( wert = GetWert( pSart, "A02ELEKTRO", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02ELEKTRO ) )
      str_lcpy( ifa->A02ELEKTRO, wert, L_ZIFAOART_A02ELEKTRO );

   /*   "A02WIRKSTO" */ 
   if ( ( wert = GetWert( pSart, "A02WIRKSTO", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02WIRKSTO ) )
      str_lcpy( ifa->A02WIRKSTO, wert, L_ZIFAOART_A02WIRKSTO );

   /*   "A01PPU" */ 
   if ( ( wert = GetWert( pSart, "A01PPU", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01PPU ) )
	  ifa->A01PPU = str_to_preis( wert, L_ZIFAOART_A01PPU );

   /*   "A01APU783A" */ 
   if ( ( wert = GetWert( pSart, "A01APU783A", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01APU783A ) )
	  ifa->A01APU783A = str_to_preis( wert, L_ZIFAOART_A01APU783A );

   /*   "A01AEPPPU" */ 
   if ( ( wert = GetWert( pSart, "A01AEPPPU", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01AEPPPU ) )
	  ifa->A01AEPPPU = str_to_preis( wert, L_ZIFAOART_A01AEPPPU );

   /*   "A01AVPPPU" */ 
   if ( ( wert = GetWert( pSart, "A01AVPPPU", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A01AVPPPU ) )
	  ifa->A01AVPPPU = str_to_preis( wert, L_ZIFAOART_A01AVPPPU );

   /*   "A02EB130B" */ 
   if ( ( wert = GetWert( pSart, "A02EB130B", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02EB130B ) )
	  str_lcpy( ifa->A02EB130B, wert, L_ZIFAOART_A02EB130B );

   /*   "A02EXPLOS" */ 
   if ( ( wert = GetWert( pSart, "A02EXPLOS", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02EXPLOS ) )
	  str_lcpy( ifa->A02EXPLOS, wert, L_ZIFAOART_A02EXPLOS );

   /*   "A02BIOTECH" */ 
   if ( ( wert = GetWert( pSart, "A02BIOTECH", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02BIOTECH ) )
	  str_lcpy( ifa->A02BIOTECH, wert, L_ZIFAOART_A02BIOTECH );

   /*   "A02STIFEAR" (formerly A02ELEKEAR) */ 
   if ( ( wert = GetWert( pSart, "A02STIFEAR", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02STIFEAR ) )
	  str_lcpy( ifa->A02STIFEAR, wert, L_ZIFAOART_A02STIFEAR );

   /*   "A02WEEEREG" */ 
   if ( ( wert = GetWert( pSart, "A02WEEEREG", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02WEEEREG ) )
	  str_lcpy( ifa->A02WEEEREG, wert, L_ZIFAOART_A02WEEEREG );

   /*   "A02BATTG" - no longer delivered by IFA (from rel. 20236 on) 
   *    But will be determined from A02BATREG implicitly */
   ClearNbPlausi(P_ZIFAOART_A02BATTG);

   /*   "A02BATTREG" */
   if ((wert = GetWert(pSart, "A02BATTREG", errmld)) == NULL)
	   return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02BATTREG))
       str_lcpy(ifa->A02BATTREG, wert, L_ZIFAOART_A02BATTREG);

   /*   "A02BOPST" */ 
   if ( ( wert = GetWert( pSart, "A02BOPST", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02BOPST ) )
		ifa->A02BOPST = str_tol( wert, 8 ); 

   /*   "A02BATTREG" (formerly A02MELDENR) 
        Weil aber A02BATTG nicht mehr geliefert wird, wird auf Basis der Batterieregistriernummer
        der Wert implizit 00 oder 01 gesetzt unabhängig von aktuellen ZIFAOART Werten. */ 

   if ( ( wert = GetWert( pSart, "A02BATTREG", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02BATTREG ) )
   {
		str_lcpy( ifa->A02BATTREG, wert, L_ZIFAOART_A02BATTREG );
       if (!TestNullZeroOrEmpty(ifa->A02BATTREG))
       {
           str_lcpy(ifa->A02BATTG, "01", L_ZIFAOART_A02BATTG);
       }
       else
       {
           str_lcpy(ifa->A02BATTG, "00", L_ZIFAOART_A02BATTG);
       }
   }

   /*   "A11GDAT" */ 
   if ( ( wert = GetWert( pSart, "A11GDAT", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A11GDAT ) )
		ifa->A11GDAT = str_tol( wert, 8 );

   /*   "A11VERIPFL" */ 
   if ( ( wert = GetWert( pSart, "A11VERIPFL", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A11VERIPFL ) )
	    str_lcpy( ifa->A11VERIPFL, wert, L_ZIFAOART_A11VERIPFL );

   /*   "A11VERIHOC" */ 
   if ( ( wert = GetWert( pSart, "A11VERIHOC", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A11VERIHOC ) )
		ifa->A11VERIHOC = str_tol( wert, 8 );

   /*   "A02MP31" */ 
   if ( ( wert = GetWert( pSart, "A02MP31", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02MP31 ) )
	    str_lcpy( ifa->A02MP31, wert, L_ZIFAOART_A02MP31 );

   /*   "A02VERB31" */ 
   if ( ( wert = GetWert( pSart, "A02VERB31", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02VERB31 ) )
	    str_lcpy( ifa->A02VERB31, wert, L_ZIFAOART_A02VERB31 );

   /*   "A02CMR" */ 
   if ( ( wert = GetWert( pSart, "A02CMR", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02CMR ) )
	    str_lcpy( ifa->A02CMR, wert, L_ZIFAOART_A02CMR );

   /*   "A02MPKLASS" */ 
   if ( ( wert = GetWert( pSart, "A02MPKLASS", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02MPKLASS ) )
	    str_lcpy( ifa->A02MPKLASS, wert, L_ZIFAOART_A02MPKLASS );

   /*   "A02INVITRO" */ 
   if ( ( wert = GetWert( pSart, "A02INVITRO", errmld ) ) == NULL ) return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02INVITRO ) )
	    str_lcpy( ifa->A02INVITRO, wert, L_ZIFAOART_A02INVITRO );

   /* A02UNNR */ 
   if ( ( wert = GetWert( pSart, "A02UNNR", errmld ) ) == NULL ) 
	   return 1;
   if ( !TestNoValue( wert, P_ZIFAOART_A02UNNR ) )
      str_lcpy( ifa->A02UNNR, wert, L_ZIFAOART_A02UNNR );

   /*   A00UDIDI */
   if ((wert = GetWert(pSart, "A00UDIDI", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A00UDIDI))
	   str_lcpy(ifa->A00UDIDI, wert, L_ZIFAOART_A00UDIDI);

   /*   A02SWUNBD */
#define  L_ZIFAOART_A02SWUNDB  6
   if ((wert = GetWert(pSart, "A02SWUNDB", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02SWUNDB))
	   ifa->A02SWUNDB = str_tos(wert, L_ZIFAOART_A02SWUNDB);

   /*   A02ATMP */
#define  L_ZIFAOART_A02ATMP  6
   if ((wert = GetWert(pSart, "A02ATMP", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02ATMP))
	   ifa->A02ATMP = str_tos(wert, L_ZIFAOART_A02ATMP);

   /*   A02AUSIMPF */
#define  L_ZIFAOART_A02AUSIMPF  6
   if ((wert = GetWert(pSart, "A02AUSIMPF", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02AUSIMPF))
	   ifa->A02AUSIMPF = str_tos(wert, L_ZIFAOART_A02AUSIMPF);

   /*  EU-NOVEL */
#define  L_ZIFAOART_A02EUNOVEL  6
   if ((wert = GetWert(pSart, "A02EUNOVEL", errmld)) == NULL) return 1;

   if (!TestNoValue(wert, P_ZIFAOART_A02EUNOVEL))
	   ifa->A02EUNOVEL = str_tos(wert, L_ZIFAOART_A02EUNOVEL);

   /*  A00ZINNR (formerly A00ZINNR6) */
   /*  A00ZINNRx changes its suffix from time to time, so its
       corresponding db column has no suffix, see also A00ANBNR / A00OEVNR */
   if ((wert = GetWert(pSart, "A00ZINNR7", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A00ZINNR))
	   str_lcpy(ifa->A00ZINNR, wert, L_ZIFAOART_A00ZINNR);

   /*  A00OEVNR7 (formerly A00OEVNR6) */
   /*  A00OEVNRx changes its suffix from time to time, so its
       corresponding db column has no suffix, see also A00ANBNR / A00ZINNR */
   if ((wert = GetWert(pSart, "A00OEVNR7", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A00OEVNR))
	   str_lcpy(ifa->A00OEVNR, wert, L_ZIFAOART_A00OEVNR);

   /*   A02ORDRUG */
   if ((wert = GetWert(pSart, "A02ORDRUG", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02ORDRUG))
	   str_lcpy(ifa->A02ORDRUG, wert, L_ZIFAOART_A02ORDRUG);

   /*   A02BEDZUL */
   if ((wert = GetWert(pSart, "A02BEDZUL", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02BEDZUL))
	   str_lcpy(ifa->A02BEDZUL, wert, L_ZIFAOART_A02BEDZUL);

   /*   A02ZULAUSN */
   if ((wert = GetWert(pSart, "A02ZULAUSN", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02ZULAUSN))
	   str_lcpy(ifa->A02ZULAUSN, wert, L_ZIFAOART_A02ZULAUSN);

   /*   A02AMNOG */
   if ((wert = GetWert(pSart, "A02AMNOG", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02AMNOG))
	   str_lcpy(ifa->A02AMNOG, wert, L_ZIFAOART_A02AMNOG);

   /*   A02PRSTRMO */
   if ((wert = GetWert(pSart, "A02PRSTRMO", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02PRSTRMO))
       str_lcpy(ifa->A02PRSTRMO, wert, L_ZIFAOART_A02PRSTRMO);

   /* ------------ IFA Version 20244 ------------ */
   /*   A02AMDARKI */
   if ((wert = GetWert(pSart, "A02AMDARKI", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02AMDARKI))
       str_lcpy(ifa->A02AMDARKI, wert, L_ZIFAOART_A02AMDARKI);

   /*   A02AMAUFFB */
   if ((wert = GetWert(pSart, "A02AMAUFFB", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02AMAUFFB))
       str_lcpy(ifa->A02AMAUFFB, wert, L_ZIFAOART_A02AMAUFFB);

   /*   A02AMBEKI */
   if ((wert = GetWert(pSart, "A02AMBEKI", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02AMBEKI))
       str_lcpy(ifa->A02AMBEKI, wert, L_ZIFAOART_A02AMBEKI);

   /*   A02AMVEKRW */
   if ((wert = GetWert(pSart, "A02AMVEKRW", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02AMVEKRW))
       str_lcpy(ifa->A02AMVEKRW, wert, L_ZIFAOART_A02AMVEKRW);

   /*   A01DAPU78 */
   if ((wert = GetWert(pSart, "A01DAPU78", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A01DAPU78))
       ifa->A01DAPU78 = str_tol(wert, 8);

   /*   A02D130A18 */
   if ((wert = GetWert(pSart, "A02D130A18", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02D130A18))
       ifa->A02D130A18 = str_tol(wert, 8);

   /* ------------ IFA Version 20248 ------------ */
   /*   A02MEDCG */
   if ((wert = GetWert(pSart, "A02MEDCG", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A02MEDCG))
       str_lcpy(ifa->A02MEDCG, wert, L_ZIFAOART_A02MEDCG);

   /*   A05LGTMPB */
   if ((wert = GetWert(pSart, "A05LGTMPB", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A05LGTMPB))
       str_lcpy(ifa->A05LGTMPB, wert, L_ZIFAOART_A05LGTMPB);

   /* ------------ IFA Version 20252 ------------ */
   /*   A01B130B1C */
   if ((wert = GetWert(pSart, "A01B130B1C", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A01B130B1C))
       str_lcpy(ifa->A01B130B1C, wert, L_ZIFAOART_A01B130B1C);

   /*   A01DAT78 */
   if ((wert = GetWert(pSart, "A01DAT78", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A01DAT78))
       ifa->A01DAT78 = str_tol(wert, 8);

   /*   A01RAB130A */
   if ((wert = GetWert(pSart, "A01RAB130A", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A01RAB130A))
       ifa->A01RAB130A = str_to_preis(wert, L_ZIFAOART_A01RAB130A);

   /*   A01ZUZAH61 */
   if ((wert = GetWert(pSart, "A01ZUZAH61", errmld)) == NULL) return 1;
   if (!TestNoValue(wert, P_ZIFAOART_A01ZUZAH61))
       ifa->A01ZUZAH61 = str_to_preis(wert, L_ZIFAOART_A01ZUZAH61);

   return 0;
}

/* -----------------------------------------------------*/
/* Sichern alte zifaoart Werte fuer den spaeteren Check */
/* Aktuell nur Apotheken und Verschreibungpflicht       */
/* -----------------------------------------------------*/
void OldIfaOartFill(struct P_IFAOART* ifa, struct P_IFAOART* old_ifa)
{
    strcpy(old_ifa->A02APPFL, ifa->A02APPFL);
    strcpy(old_ifa->A02VSPFL, ifa->A02VSPFL);

    return;
}

/* ---------------------------------------------------------------------- *
 * Funktion        : ifaoart-Satz aendern                                 *
 * ---------------------------------------------------------------------- */

long IfaOartAendere( sSatzArt *pSart, struct P_IFAOART *ifa, struct P_IFAOART *old_ifa,
                     long tages_datum, long Pzn, char Ssatz, char LoeKenn,
                                         long *anz_upd, long *anz_del, long *anz_ins,
                                         char *errmld )
{
   long   rco;
   long   alt_datum;

   rco = ReadIfaOart( ifa, Pzn, errmld );

   if ( !( rco == 100 || rco == 0 ) ) return 1;

   if ( rco == 0 ) // Änderung
   {
      alt_datum = ifa->DATUM_ANLAGE;
      ifa->A00PZN = Pzn;
	  GetIfaPzn( &ifa->A00PZN8, pSart, errmld );
      OldIfaOartFill(ifa, old_ifa);   // Sichern der alten zifaoart Werte fuer spaetere Checks
      if ( IfaOartFill( ifa, pSart, tages_datum, errmld ) != 0 ) return 1;
      ifa->DATUM_ANLAGE = alt_datum;
      ifa->DATUM_AENDER = tages_datum;

      if ( LoeKenn == 'X' || Ssatz == '2' )   /* Ifa Satz loeschen */
      {
         (*anz_del)++;
         rco = DeleteIfaOart( errmld );
      }
      else  /* Ifa Satz aendern */
      {
         (*anz_upd)++;
         rco = UpdateIfaOart( ifa, errmld );
      }
      if ( rco == 0 )
         return 0;
      else
         return 1;
   }
   else // Neuanlage
   {
      if ( InitIfaOartWithDefault( ifa, errmld ) != 0 ) return 1;

      ifa->A00PZN = Pzn;
	  GetIfaPzn( &ifa->A00PZN8, pSart, errmld );
      if ( IfaOartFill( ifa, pSart, tages_datum, errmld ) != 0 ) return 1;
      OldIfaOartFill(ifa, old_ifa);   // Sichern der frisch geladenen IFA Werte fuer spaetere Checks
      ifa->DATUM_ANLAGE = tages_datum;
      ifa->DATUM_AENDER = 0;

          /* nur aufnehmen, wenn alle Felder belegt */
      if ( IsIfaOartRecordComplete(  ) )
      {
          if ( LoeKenn == 'X' || Ssatz == '2' )   /* nichts tun, da Satz nicht vorhanden */
             rco = 0;
          else
          {
             anz_ins++;
             rco = InsertIfaOart( ifa, errmld );
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
