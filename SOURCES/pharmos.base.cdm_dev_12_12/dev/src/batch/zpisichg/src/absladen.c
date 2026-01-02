
/* ---------------------------------------------------------------------- *
 *                            A B S L A D E N . C                         *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : laden der von zartikel  mit Abschlagsinfo             *
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
#include <zapflege.h>

#define L_ARTIKEL_NR 7

#include "absladen.h"
#include "g_ifoabs.h"
#include "lifestyl.h"

#ifdef ABS_PROT_ALT
#include "abs_prot.h"
#else
#include "bss_prot.h"
#endif

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

#ifdef VOR_12_01_2004
   CmpIndikator_Zartikel[P_ZARTIKEL_BSSICHG]		  = '1';
   CmpIndikator_Zartikel[P_ZARTIKEL_AUTIDEMARTIKEL]   = '1';
#endif
   CmpIndikator_Zartikel[P_ZARTIKEL_ANBIETERABSCHLAG] = '1';
   CmpIndikator_Zartikel[P_ZARTIKEL_FESTBETRARTIKEL]  = '1';
   CmpIndikator_Zartikel[P_ZARTIKEL_DATUM_ABSCHLAG]   = '1';
#ifdef VOR_12_01_2004
   CmpIndikator_Zartikel[P_ZARTIKEL_PREISSENKUNG]     = '1';   /* 07.03.2003 lt. Heidicker */
#endif
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

#ifdef VOR_12_01_2004
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

#endif

/* ----- Transaktionen ------------------------- */

static long StartWork( char *errmld )
{
    long s;
    s = SqlBeginWork( );
    if ( s != 0 )
    {
        strcpy( errmld, "IFA-Abschlaege: " );
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
            strcpy( errmld, "IFA-Abschlaege: " );
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

/* ----- Do it ------------------------- */

static void GenWert01( char *feld, char *wert, int pos )
{
	if ( IsNoValue( pos ) ) return;

	if ( strcmp( wert, "01" ) == 0 )
		strcpy( feld, "1" );
/*
	else if ( *wert == '\0' )
		strcpy( feld,"" );
*/
	else
		strcpy( feld, "0" );
}

long  AbschlagLaden( long artikel_nr, long tages_datum, int wegfall, 
					 struct ZIFAOABSCHLAG *oifa,
					 char *user, char *errmld )
{
	long s;

#ifdef ABS_PROT_ALT
	char prot_zeile[40];
#endif

	s = ReadRecord_Zartikel( artikel_nr, errmld );
	if ( s == 100 ) return 0;   /* Artikel nicht vorhanden */
	if ( s != 0 )   return s;   /* Fehler */

	GenWert01( Buf_zartikel.ANBIETERABSCHLAG, oifa->C02ANBABS,  P_ZIFAOABSCHLAG_C02ANBABS );
#ifdef VOR_12_01_2004
	GenWert01( Buf_zartikel.BSSICHG,          oifa->C02GHABS  , P_ZIFAOABSCHLAG_C02GHABS);
#endif

#ifdef VOR_16_12_2003
	GenWert01( Buf_zartikel.AUTIDEMARTIKEL ,  oifa->C02AUTIDEM, P_ZIFAOABSCHLAG_C02AUTIDEM );
#endif
	GenWert01( Buf_zartikel.FESTBETRARTIKEL,  oifa->C02FBART,   P_ZIFAOABSCHLAG_C02FBART );

#ifdef VOR_12_01_2004
	if ( IsLifeStyle( Buf_zartikel.ARTIKEL_NR ) )
		*Buf_zartikel.BSSICHG = '0';
#endif

	if ( strcmp( Buf_zartikel.ANBIETERABSCHLAG, BufOld_zartikel.ANBIETERABSCHLAG ) == 0 &&
#ifdef VOR_12_01_2004
		 strcmp( Buf_zartikel.BSSICHG, BufOld_zartikel.BSSICHG )                   == 0 &&
	     strcmp( Buf_zartikel.AUTIDEMARTIKEL,  BufOld_zartikel.AUTIDEMARTIKEL )    == 0 &&
#endif
	     strcmp( Buf_zartikel.FESTBETRARTIKEL, BufOld_zartikel.FESTBETRARTIKEL )   == 0    )
		return 0;

	if ( !IsNoValue( P_ZIFAOABSCHLAG_C02GDATABS ) )
		Buf_zartikel.DATUM_ABSCHLAG = oifa->C02GDATABS;

	Buf_zartikel.DATUM_AENDER = tages_datum;
	strcpy( Buf_zartikel.BEARBEITER, user );

#ifdef VOR_12_01_2004
	/* 07.03.2003 lt. Heidicker */
	/* autidemartikel von '0' auf '1' */ 
	/* ->  preissenkung auf '3', wenn vorher auf '0' (bei 1,2,4 oder 5 keine Änderung)  */
	/* autidemartikel von '1' auf '0' */
	/* ->  preissenkung auf '0', wenn vorher auf '3' (bei 1,2,4 oder 5 keine Änderung)  */ 
	if ( BufOld_zartikel.AUTIDEMARTIKEL[0] == '0' &&  Buf_zartikel.AUTIDEMARTIKEL[0] == '1' )
	{
		if ( BufOld_zartikel.PREISSENKUNG[0] == '0' )
			 Buf_zartikel.PREISSENKUNG[0] = '3';
	}
	else if ( BufOld_zartikel.AUTIDEMARTIKEL[0] == '1' &&  Buf_zartikel.AUTIDEMARTIKEL[0] == '0' )
	{
		if ( BufOld_zartikel.PREISSENKUNG[0] == '3' )
			 Buf_zartikel.PREISSENKUNG[0] = '0';
	}
#endif
    /* neu ab 09.03.2004 -> Wiedereinfuehrung und dabei */
    /* AUTIDEMARTIKEL durch FESTBETRARTIKEL ersetzen */
	if ( BufOld_zartikel.FESTBETRARTIKEL[0] == '0' &&  Buf_zartikel.FESTBETRARTIKEL[0] == '1' )
	{
		if ( BufOld_zartikel.PREISSENKUNG[0] == '0' )
			 Buf_zartikel.PREISSENKUNG[0] = '3';
	}
	else if ( BufOld_zartikel.FESTBETRARTIKEL[0] == '1' &&  Buf_zartikel.FESTBETRARTIKEL[0] == '0' )
	{
		if ( BufOld_zartikel.PREISSENKUNG[0] == '3' )
			 Buf_zartikel.PREISSENKUNG[0] = '0';
	}


	s = StoreRecord_Zartikel( errmld );
	if ( s != 0 ) return s;

#ifdef VOR_12_01_2004
	if ( strcmp( BufOld_zartikel.BSSICHG, Buf_zartikel.BSSICHG ) != 0 )
	{
		s = StoreRecord_Zapflege( artikel_nr, tages_datum, errmld );
		if (  s != 0 ) return s;
	}
#endif

	/* Ausfuehren */
	/* s = FdTransact( errmld ); */
	s = FdTransactWithoutWork( errmld );
	if (  s != 0 ) return s;

#ifdef VOR_12_01_2004
#ifdef ABS_PROT_ALT
	if ( strcmp( BufOld_zartikel.BSSICHG, Buf_zartikel.BSSICHG ) != 0 )
	{
		sprintf( prot_zeile, "  %.7ld %s", artikel_nr, Buf_zartikel.BSSICHG );
		s = Abs_Protokol( prot_zeile, errmld );
	}
#else
	if ( strcmp( BufOld_zartikel.BSSICHG, Buf_zartikel.BSSICHG ) != 0 )
		s = bss_Protokol( &Buf_zartikel, BufOld_zartikel.BSSICHG, errmld );
#endif
#endif

	return s;
}


long Open_All_FDs( char *errmld )
{
	long status;
    if ( GetBufferDesc_Zartikel ( errmld ) != 0 ) return -1;
#ifdef VOR_12_01_2004
    if ( GetBufferDesc_Zapflege ( errmld ) != 0 ) return -1;
#endif
    /* IfaOart */
    status = Open_IfaOabschlag_FDs( errmld );
    if ( status != 0 ) return status;
    return 0;
}

long Close_All_FDs( )
{
  Close_IfaOabschlag_FDs();
  return 0;
}
