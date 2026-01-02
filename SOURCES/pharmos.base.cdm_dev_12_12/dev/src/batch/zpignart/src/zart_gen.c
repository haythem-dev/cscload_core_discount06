
/* ---------------------------------------------------------------------- *
 *                        A R T _ G E N . C                               *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : generiert ZARTIKEL, ZPREIS,EAN aus ZIFAART          *
 *                    bei IFA-Aenderungen                                 *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 30.03.98                                            *
 *   letztes Update : 24.08.06                                            *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <phodate.h>

#include <zifaart.h>
#include <zartikel.h>
#include <zartprei.h>
#include <cartpriceext.h>
#include <zlifestyle.h>
#include <ean.h>
#include <artve.h>

#include "znb_gen.h"
#include "zart_gen.h"

/* ----- Initialwerte fuer spezielle Artikelfelder ------- */
void InitRestArtikel( struct ZARTIKEL *zart, char *user )
{
/*
   strcpy( Buf_zartikel.BEARBEITER, user );
*/
   strcpy( zart->BEARBEITER, user );

   *zart->ERSATZ_NR_AKTIV   = '0';
/* hier weg: Peetz 15.7.98
   memset( zart->RABATTFAEHIG, '0', L_ZARTIKEL_RABATTFAEHIG );
*/
   *zart->PRIVATSORTIMENT   = 'N';
   *zart->TAXPRUEFGROSSO    = '0';
   *zart->SONDERGROSSO      = ' ';
   *zart->BESTANDSBUCHUNG   = '1';   /* Peetz 2.6.98 */
   *zart->INDIKATOR         = '0';
   *zart->SKONTOFAEHIG      = '1';   /* Peetz 2.6.98 */
   *zart->PREIS0ARTIKEL     = '0';
   *zart->MELDEPFL          = '0';
   *zart->MVDAARTIKEL       = '0';
   *zart->ZYTOSTATIKA       = '0';
   *zart->SICHTWAHL         = '0';
   *zart->RETOURENSPERRE    = '0';
   *zart->ZENTR_EKSPERRE    = '0';
   *zart->ARTIKEL_GELOESCHT = '0';
   *zart->SOMMER_KK         = '0';
   *zart->PRODUKTART        = '0';   /* Peetz 15.7.98 */
   *zart->BESTELLSPERRE     = '0';
   *zart->KATALOG           = ' ';
   *zart->LABORARTIKEL      = '0';
   memset( zart->ZUZAHLUNG_IFA, '0', L_ZARTIKEL_ZUZAHLUNG_IFA );
   *zart->ZUZAHLUNG_IFA     = '0';
   *zart->ARTIKEL_GESPERRT  = '1';   /* Peetz 2.6.98 Neuaufnahmen sperren */
   *zart->VERTRBIND         = ' ';
   *zart->NATURALRABATT     = '0';
   *zart->PRISMAEDISK       = '0';
   *zart->GS_EXPLOSION      = '0';
   *zart->GS_BRAND          = '0';
   *zart->GS_LEICHTENTZ     = '0';
   *zart->GS_HOCHENTZ       = '0';
   *zart->GS_GIFTIG         = '0';
   *zart->GS_SEHRGIFTIG     = '0';
   *zart->GS_GESUNDHSCH     = '0';
   *zart->GS_REIZEND        = '0';
   *zart->GS_AETZEND        = '0';
   *zart->GS_UMWELT         = '0';
   *zart->GS_VORSLAGERN     = '0';
   *zart->GS_SVORSLAGERN    = '0';
   *zart->AWL_AKTIV         = 'N';
   *zart->SORTIMENT_1       = '0';
   *zart->SORTIMENT_2       = '0';
   *zart->SORTIMENT_3       = '0';
   *zart->SORTIMENT_4       = '0';
   *zart->SORTIMENT_5       = '0';
   *zart->PERF              = '0';
   *zart->TIERARZNEI        = '0';   /* 13.07.99 */
   *zart->NAHRUNGSERGAENZUNG = 'N';  /* 06.07.01 */
   *zart->PREISSENKUNG      = '0';   /* 24.05.02 */
   *zart->BSSICHG           = '0';   /* 12.12.02 */
   *zart->ANBIETERABSCHLAG  = '0';	 /* 24.01.03 */
   *zart->AUTIDEMARTIKEL    = '0';
   *zart->FESTBETRARTIKEL   = '0';
   *zart->REZEPTURARZNEI    = '0';	 /* 06.03.03 */
   *zart->MEDIZINPRODUKT    = '0';
   *zart->IMPFSTOFF         = '0';
   *zart->CE_KENNZEICHEN    = '0';
   *zart->ARZNEIMITTEL      = '0';
   *zart->KONTRAZEPTIVUM    = '0';
   *zart->ZENTRALPPELIST    = '0';
   *zart->EKORIGINALHS      = '0';
   *zart->BESTELL_NUR_OZEK  = '0';  /* 24.11.09 */
   *zart->BESTELL_NICHT_AUSL= '0';
   *zart->FAELSCH_GEFAHR	= '0';
   *zart->EAN_NICHTVORHANDEN='0';
   *zart->HILFSM_VERBRAUCH	= '0';
   *zart->ABGABEBEST_IFA	= ' ';
   *zart->GS_LICHTGESCH		= '0';
   *zart->PSYCHOTROP		= 'N';	/* 21.11.05 */
   *zart->STELLER			= 'N';	/* 21.11.05 */
   *zart->ELEKTROSCHROTT	= 'N';	/* 21.11.05 */
   *zart->NIEDRSPANNE_ELAC	= '0';	/* 21.11.05 */
   *zart->NIEDRSPANNE_SONST	= '0';	/* 21.11.05 */
   *zart->AMG_AUSNAHMEREG	= '0';	/* 03.04.06 */
   *zart->ZULASS_GENER		= '0';	/* 03.04.06 */
   *zart->ABSCHLAG_130		= '0';	/* 03.04.06 */
   *zart->SIDABLATT			= '0';	/* 03.04.06 */
   *zart->MEDIZINISCHE_GASE = '0';	/* 24.08.06 */
   *zart->KONTINGENT_PPE    = '0';	/* 24.08.06 */
   zart->ARTIKEL_NR_ORIG	= 0  ;	/* 24.08.06 */
   
   *zart->BIOZID_VERORD		= '0';	/* 14.01.09 */
   *zart->PFLSCHUTZ_VERORD	= 'N';	/* 14.01.09 */

   *zart->HOMOEOPATHIKUM = '0';		/* 08.03.10 */
   *zart->ANTHROPOSOPHIKUM = '0';		/* 08.03.10 */
   *zart->PHYTOPHARMAKON = '0';		/* 08.03.10 */
   *zart->TREZEPTARZNEI = '0';		/* 08.03.10 */
   *zart->AMG_47 = '0';		/* 08.03.10 */
   *zart->BATTERIEGESETZ		= 'N';
   *zart->NEM_PHAGROPRUEFUNG	= '0';
   *zart->NEM_ZERTIFIKAT		= '0';
   *zart->CHARGENARTIKEL		= '0';
   zart->SERIAL_NUMBER_TRACKING = 0;
   zart->ZULASSUNGSINHABERNR = 0;
   zart->OERTLICHEVERTRETERNR = 0;
   zart->WUNDPRODUKT = 0;
   zart->NEUARTIGETHERAPIE = 0;
   zart->BEDINGTEZULASSUNG = 0;
   zart->AUSNAHMEABSCHLAGSPFLICHT = 0;
   zart->NOVELFOOD = 0;
   zart->ORPHANDRUG = 0;
   zart->AMNOGVERFAHREN = 0;
   zart->ZULASSUNGAUSNAHMEFAELLE = 0;

   /* --------- IFA Version 20244 ---------- */
   *zart->BATTREG              = '0';
   zart->AM_DARREICH_ALTERSGER = 0;
   zart->AM_FESTBETR_AUFGEH    = 0;
   zart->AM_KINDER             = 0;
   zart->AM_VERSKRIT_WIRKSTOFF = 0;

   /* --------- IFA Version 20248 ---------- */
   zart->MED_CANNABIS_GES      = 0;
   zart->LAGTEMP_BEACHTEN      = 0;
}

/* ------------ Ifa-Zuzahlung nach ZZ --------------- */
int IFA_Zuzahlung_to_ZZ( char *Zuzahlung, char *ZZ )
{
    int bOk;
    char *str;

    str = Zuzahlung;

    bOk = strlen( str ) == 7;
    if ( bOk )
    bOk = *str >= '1' && *str <= '9';
    if ( bOk )
    {
       str++;
       while ( bOk && *str )
       {
          bOk = *str >= '0' && *str <= '9';
          str++;
       }
    }

    if ( !bOk )
    {
       strcpy( ZZ, "  " );
       return 0;
    }

    if ( strcmp( &Zuzahlung[1], "000000" ) == 0 )
    {
      switch ( *Zuzahlung )
      {
        case '1':
        case '2':
          strcpy( ZZ, "  " );
          break;
        case '3':
        case '4':
          strcpy( ZZ, "N1" );
          break;
        case '5':
          strcpy( ZZ, "N2" );
          break;
        case '6':
          strcpy( ZZ, "N3" );
          break;
        case '7':
          strcpy( ZZ, "A2" );
          break;
        case '8':
          strcpy( ZZ, "A3" );
          break;
        case '9':
          strcpy( ZZ, "ZP" );
          break;

      }
    }
    else
    {
       if ( *Zuzahlung >= '7' && *Zuzahlung <= '8' )
          strcpy( ZZ, "AP" );
       else
          strcpy( ZZ, "KP" );
    }
    return 1;
}


/* ------ gegebenenfalls AH_DATUM / BTM / ZZ an Artikel haengen ----- */
static void ChangeArtikelName( struct ZARTIKEL *Buf )
{
    char str[12];
    if ( Buf->DATUM_AH != 0 )
    {
      ConvFromPhoDate( str, Buf->DATUM_AH, "mmjj" );
      memcpy( &Buf->ARTIKEL_NAME[26], str, 4 );
    }
    else
    {
      IFA_Zuzahlung_to_ZZ( Buf->ZUZAHLUNG_IFA, str );
      memset( &Buf->ARTIKEL_NAME[26], ' ', 2 );
      memcpy( &Buf->ARTIKEL_NAME[28], str, 2 );
      if ( Buf->BTM[0] == '1' )
        memcpy( &Buf->ARTIKEL_NAME[26], "BM", 2 );
    }
}

/* ----- Default values for ARTVE ------- */
void InitArtveFields( struct ARTVE *spArtve)
{
    spArtve->VERPACKEINHEIT1 = 1;
    spArtve->VERPACKEINHEIT2 = 0;
    spArtve->VERPACKEINHEIT3 = 0;
    spArtve->VERPACKEINHEIT4 = 0;
    spArtve->ORIGINALKARTON  = 0;
}

/* ------- make Artikelfelder ------------------------ */
static int IsNullZeroOrEmpty(char* str)
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

int IsNoValue( struct ZIFAART *ifa, int pos )
{
   return ifa->NB_PLAUSI[ pos ] == NOVALUE_PL;
}


int IsAnyNoValue( struct ZIFAART *ifa  )
{
   int pos;
   for ( pos = 0; pos < L_ZIFAART_NB_PLAUSI; pos++ )
   {
      if ( ifa->NB_PLAUSI[ pos ] == NOVALUE_PL ) return 1;
   }
   return 0;
}

static void Cpy01Direct(char* art, char* ifa, int NoValue) {
	if (!NoValue){
		if (strcmp(ifa, "01") == 0){
			*art = '1';
		}
		else{
			*art = '0';
		}
		art[1] = '\0';
	}
}

static void Cpy01DirectBiozid(char* art, char* ifa) {

	if (strcmp(ifa, "01") == 0)
	{
		*art = '1';
	}
	else
	{
		*art = '0';
	}

	art[1] = '\0';
}


static void Cpy01DirectAMG_47( char *art, char *ifa, int NoValue )
{
   if ( !NoValue )
   {
		if (strcmp(ifa, "01") == 0) {
        *art = '1';
		}
		else if(strcmp(ifa, "02") == 0) {
			*art = '2';
		}
		else if (strcmp(ifa, "03") == 0) {
			*art = '3';
		}
		else {
        *art = '0';
		}
      art[1] = '\0';
   }
}

static void Cpy01Kenn( char *art, char *ifa, int IsArtikelVorhanden,
                       int NoValue )
{
   if ( NoValue ) return;
   if ( IsArtikelVorhanden )
   {
     if ( strcmp( ifa, "01" ) == 0 )
       *art = '1';
     else if ( strcmp( ifa, "00" ) == 0 )
       *art = '0';
   }
   else
   {
      if ( strcmp( ifa, "01" ) == 0 )
        *art = '1';
      else
        *art = '0';
   }
   art[1] = '\0';
}


static void Cpy02Kenn( char *art, char *ifa, int IsArtikelVorhanden,
                       int NoValue )
{
   if ( NoValue ) return;
   if ( IsArtikelVorhanden )
   {
     if ( strcmp( ifa, "01" ) == 0 )
       *art = '1';
     else if ( strcmp( ifa, "02" ) == 0 )
       *art = '2';
     else if ( strcmp( ifa, "00" ) == 0 )
       *art = '0';
   }
   else
   {
      if ( strcmp( ifa, "01" ) == 0 )
        *art = '1';
     else if ( strcmp( ifa, "02" ) == 0 )
        *art = '2';
      else
        *art = '0';
   }
   art[1] = '\0';
}
/* Hersteller-Nr */
static void Make_HERSTELLER_NR( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf )
{
   if ( !IsNoValue( IfaBuf, PL_A00ANBNR ) )
      Buf->HERSTELLER_NR = IfaBuf->A00ANBNR;
}

/* Artikelname */
static void Make_ARTIKEL_NAME( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                               int IsArtikelVorhanden )
{
   if ( IsArtikelVorhanden ) return;
   if ( IsNoValue( IfaBuf, PL_A00PBEZ ) ) return;

   memset( Buf->ARTIKEL_NAME, ' ', L_ZARTIKEL_ARTIKEL_NAME );
   memcpy( Buf->ARTIKEL_NAME, IfaBuf->A00PBEZ, L_ZIFAART_A00PBEZ );
   Buf->ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME] = '\0';
}

/* Packung / Einheit */

static char *Einh_IFA = "G  GL M P ";
static char *Einh_ART = "GRGR L MPG";

static void NormiereEinheit( char *str, char *einheit )
{
   int i;
   for ( i = 0; i < (int) strlen( Einh_IFA ); i += 2 )
   {
	 if ( memcmp( einheit, &Einh_IFA[i], 2 ) == 0 )
	 {
		 memcpy( str, &Einh_ART[i], 2 );
		 return;
	 }
   }
   memcpy( str, einheit, 2 );
}


static size_t ShiftMenge( char *str, char *menge )
{
   size_t lng;
   size_t anf;
   size_t end;
   end = strlen( menge ) - 1;
   while ( end >= 0 && menge[end] == ' ' ) end--;
   end++;
   anf = 0;
   while ( anf < end && menge[anf] == ' ' ) anf++;
   lng = end - anf;
   if ( lng > 0 )
      memcpy( str, &menge[anf], lng );
   str[lng] = '\0';
   return lng;
}

void Build_EINHEIT( char *ArtEinheit, char *PgEinh, char *PgMeng )
{
   char str[20];
   char *pstr;
   size_t  maxlng;
   size_t  lng;
   size_t  pos;


   memset( ArtEinheit, ' ', L_ZARTIKEL_EINHEIT );
   ArtEinheit[L_ZARTIKEL_EINHEIT] = '\0';

   /* A00PGMENG rechtsbuendig */
   maxlng = L_ZARTIKEL_EINHEIT - 2;
   lng = ShiftMenge( str, PgMeng );
   if ( lng > maxlng ) 
	   lng = maxlng;
   pos = maxlng - lng;
   if ( pos > 0 )
      pos--;	/* 1 blank lassen zwischen Groesse und Einheit */
   if (  lng > 0 )
      memcpy( &ArtEinheit[pos], str, lng );

   NormiereEinheit( &ArtEinheit[L_ZARTIKEL_EINHEIT - 2], PgEinh );

   /* aus Punkt wird Komma */
   pstr = ArtEinheit;
   while ( *pstr )
   {
      if ( *pstr == '.' ) *pstr = ',';
      pstr++;
   }
}

static void Make_EINHEIT( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                          int IsArtikelVorhanden )
{
   if ( IsArtikelVorhanden ) return;
   if ( IsNoValue( IfaBuf, PL_A00PGEINH ) && 
        IsNoValue( IfaBuf, PL_A00PGMENG )     ) return; 
   Build_EINHEIT( Buf->EINHEIT, IfaBuf->A00PGEINH, IfaBuf->A00PGMENG );
}

/* Darreichungsform */
static void Make_DARREICHFORM( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                               int IsArtikelVorhanden )
{
   char *df_ifa = IfaBuf->A00DARFO;
   char *df_phoenix = Buf->DARREICHFORM;

   if ( IsArtikelVorhanden ) return;
   if ( IsNoValue( IfaBuf, PL_A00DARFO ) ) return;

   if ( strcmp( df_ifa,      "DRA" ) == 0 )
        strcpy( df_phoenix,  "DRG" );
   else if ( strcmp( df_ifa, "FLU" ) == 0 )
        strcpy( df_phoenix,  "FLG" );
   else if ( strcmp( df_ifa, "KAP" ) == 0 )
        strcpy( df_phoenix,  "KPS" );
   else if ( strcmp( df_ifa, "LOE" ) == 0 )
        strcpy( df_phoenix,  "LSG" );
   else if ( strcmp( df_ifa, "PST" ) == 0 )
        strcpy( df_phoenix,  "PAS" );
   else if ( strcmp( df_ifa, "PUD" ) == 0 )
        strcpy( df_phoenix,  "PDR" );
   else if ( strcmp( df_ifa, "PUL" ) == 0 )
        strcpy( df_phoenix,  "PLV" );
   else if ( strcmp( df_ifa, "SAF" ) == 0 )
        strcpy( df_phoenix,  "SFT" );
   else if ( strcmp( df_ifa, "SAL" ) == 0 )
        strcpy( df_phoenix,  "SLB" );
   else if ( strcmp( df_ifa, "TAB" ) == 0 )
        strcpy( df_phoenix,  "TBL" );
   else
        strcpy( df_phoenix, df_ifa );
}


/* Nicht ueber GH */
static void Make_NICHTUEBERGH( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                               int IsArtikelVorhanden )
{
   char *art = Buf->NICHTUEBERGH;
   char *ifa = IfaBuf->A03VWGGH;
   if ( IsArtikelVorhanden )
   {
      if ( IsNoValue( IfaBuf, PL_A03VWGGH ) ) return;
      if ( strcmp( ifa, "00" ) == 0 )
        strcpy( art, "1" );
      else if ( strcmp( ifa, "01" ) == 0 )
        strcpy( art, "0" );
   }
   else
   {
      strcpy( art, "0" );
      if ( strcmp( ifa, "00" ) == 0 )
        strcpy( art, "1" );
   }
}

/* Rezeptpflichtig */
static void CpyRezPfl( char *art, char *ifa, char *mp, int IsArtikelVorhanden,
                       int NoValue )
{
   if ( NoValue == 2 ) return;
   if ( IsArtikelVorhanden )
   {
     if ( strcmp( ifa, "00" ) == 0 || (strcmp( ifa, "03" ) == 0  && strcmp( mp, "01" ) == 0 ) )
       *art = '0';
     else if ( strcmp( ifa, "01" ) == 0 ||
               strcmp( ifa, "02" ) == 0 ||
               (strcmp( ifa, "03" ) == 0  && strcmp( mp, "01" ) != 0 )   )
       *art = '1';
   }
   else
   {
      *art = '0';
      if ( strcmp( ifa, "01" ) == 0 ||
           strcmp( ifa, "02" ) == 0 ||
           (strcmp( ifa, "03" ) == 0  && strcmp( mp, "01" ) != 0 )   )
        *art = '1';
   }
   art[1] = '\0';
}

static void Make_REZEPTPFL( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                            int IsArtikelVorhanden )
{
   CpyRezPfl( Buf->REZEPTPFL, IfaBuf->A02VSPFL, IfaBuf->A02MP, IsArtikelVorhanden,
              IsNoValue( IfaBuf, PL_A02VSPFL ) + IsNoValue( IfaBuf, PL_A02MP ));

   if ( (!IsNoValue( IfaBuf, PL_A02BTM ) && strcmp( IfaBuf->A02BTM, "01" ) == 0 ) ||
	    ( IsNoValue( IfaBuf, PL_A02BTM ) && Buf->BTM[0] == '1' ))
      *Buf->REZEPTPFL = '1';

   // Immer lt. CPR-240206
   // Wenn A02VSPFL == "02" -> REZEPTPFL = "0"
   if ( strcmp(IfaBuf->A02VSPFL, "02") == 0 )
   {
      strcpy(Buf->REZEPTPFL, "0");
   }
}

/* Apothekenpflichtig */
static void Make_APOTHEKENPFL( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf )
{

   if ( !IsNoValue( IfaBuf, PL_A02VSPFL ) || !IsNoValue ( IfaBuf, PL_A02APPFL ) || !IsNoValue ( IfaBuf, PL_A02MP ) )
   {
	 if ( (strcmp( IfaBuf->A02APPFL, "01" ) == 0 || (strcmp( IfaBuf->A02APPFL, "02" ) == 0 && strcmp( IfaBuf->A02MP, "01" ) != 0)) &&
          (strcmp( IfaBuf->A02VSPFL, "  " ) == 0 || strcmp( IfaBuf->A02VSPFL, "00" ) == 0 || (strcmp( IfaBuf->A02VSPFL, "03" ) == 0 && strcmp( IfaBuf->A02MP, "01" ) == 0 ) ) )
        strcpy( Buf->APOTHEKENPFL, "1" );
      else
        strcpy( Buf->APOTHEKENPFL, "0" );
   }
}


/* Taxpflichtig */
static void Make_TAXPFL( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                         int IsArtikelVorhanden )
{
   char *art = Buf->TAXPFL;
   char *ifa_amg;
   char *ifa_sgb;

   if ( IsNoValue( IfaBuf, PL_A01AMPVAMG ) ) return;
   if ( IsNoValue( IfaBuf, PL_A01AMPVSGB ) ) return;

   ifa_amg = IfaBuf->A01AMPVAMG;
   ifa_sgb = IfaBuf->A01AMPVSGB;

   if ( !IsNoValue( IfaBuf, PL_A01AMPVAMG ) ) 
   {
		if ( strcmp( ifa_amg, "01" ) == 0 )
		{
			if ( strcmp( IfaBuf->A02TIERAM, "01" ) == 0 )
				strcpy( art, "1" );
			else
			{ 
				strcpy( art, "2" );
			}
			return;
		}
   }
   if ( !IsNoValue( IfaBuf, PL_A01AMPVSGB ) ) 
   {
		if ( strcmp( ifa_sgb, "01" ) == 0 )
		{
			strcpy( art, "1" ); /* strcpy( art, "2" ); */		/* RX */
			return;
		}
   }
   if ( IsArtikelVorhanden )
   {
		if ( strcmp( ifa_amg, "  " ) != 0 || strcmp( ifa_sgb, "  " ) != 0 )
			strcpy( art, "0" );	
   }
   else
		strcpy( art, "0" );
}


/* Nettoartikel  */
static void Make_NETTOARTIKEL( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf )
{
   char *art     = Buf->NETTOARTIKEL;
   char *amp_amg = IfaBuf->A01AMPVAMG;
   char *amp_sgb = IfaBuf->A01AMPVSGB;
   char *apf     = IfaBuf->A02APPFL;

   if ( !IsNoValue( IfaBuf, PL_A01AMPVAMG ) || !IsNoValue( IfaBuf, PL_A01AMPVSGB ) || 
	    !IsNoValue( IfaBuf, PL_A02APPFL ) )
   {
     if ( ( strcmp( amp_amg, "00" ) == 0 || strcmp( amp_sgb, "00" ) == 0 ) &&
          ( strcmp( apf, "00" ) == 0 || strcmp( apf, "  " ) == 0 ) )
       *art = '1';
     else
       *art = '0';
	art[1] = '\0';
   }
}

/* Negativartikel */
static void Make_NEGATIVLISTE( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                               int IsArtikelVorhanden )
{
   Cpy02Kenn( Buf->NEGATIVLISTE, IfaBuf->A02NEGLIS, IsArtikelVorhanden,
              IsNoValue( IfaBuf, PL_A02NEGLIS ) );
}

/* Nur KVA */
static void Make_NURKVA( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf )
{
   int IsKAP;
   int IsGH;
   int IsAPO;
   int IsSEH;

   IsKAP = !IsNoValue( IfaBuf, PL_A03VWGKAP );
   IsGH  = !IsNoValue( IfaBuf, PL_A03VWGGH  );
   IsAPO = !IsNoValue( IfaBuf, PL_A03VWGAPO );
   IsSEH = !IsNoValue( IfaBuf, PL_A03VWGSEH );

   /* wenn eines vom Aenderungsdienst kommt */
   if ( IsKAP || IsGH || IsAPO || IsSEH )
   {
      if ( strcmp( IfaBuf->A03VWGKAP, "01" ) == 0 &&
           strcmp( IfaBuf->A03VWGGH,  "01" ) != 0 &&
           strcmp( IfaBuf->A03VWGAPO, "01" ) != 0 &&
           strcmp( IfaBuf->A03VWGSEH, "01" ) != 0    )
         strcpy( Buf->NURKVA, "1" );
      else
         strcpy( Buf->NURKVA, "0" );
   }
}

/* Klinikpackung */
static void Make_KLINIKPACKUNG( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                                int IsArtikelVorhanden )
{
   if ( !IsArtikelVorhanden ) // 04/2017: nur noch bei Neuaufnahmen!
   {
		Cpy01Direct( Buf->KLINIKPACKUNG, IfaBuf->A00ATYP, IsNoValue( IfaBuf, PL_A00ATYP ) );
   }
}

/* Verfallkennzeichen: wird nur uebernommen, wenn Zustand = '0' war ( s. Protokol)  */
char Build_VERFALL(  struct ZIFAART *IfaBuf )
{
   if ( IsNoValue( IfaBuf, PL_A05VFDAT ) )
       return ' ';
   if ( IfaBuf->A05VFDAT[1] == '1' )
       return '1';
   else
       return '0';
}

static void Make_VERFALL( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                          int IsArtikelVorhanden )
{
   char Verfall;
   Verfall = Build_VERFALL( IfaBuf );
   if ( IsArtikelVorhanden )
   {
      if ( *Buf->VERFALL == '0' && Verfall != ' ' )
           *Buf->VERFALL = Verfall;
   }
   else
   {
      if ( Verfall == ' ' ) Verfall = '0';
      *Buf->VERFALL = Verfall;
      Buf->VERFALL[1] = '\0';
   }
}

/* Vertriebsbindung: wird nur uebernommen, wenn Zustand = '0' war ( s. Protokol)  */
char Build_VERTRBIND_IFA( struct ZIFAART *IfaBuf )
{
   int IsAPO;
   int IsSEH;
   int IsAPP;
   int IsVSP;
   int IsMP;

   IsAPO = !IsNoValue( IfaBuf, PL_A03VWGAPO );
   IsSEH = !IsNoValue( IfaBuf, PL_A03VWGSEH );
   IsAPP = !IsNoValue( IfaBuf, PL_A02APPFL );
   IsVSP = !IsNoValue( IfaBuf, PL_A02VSPFL  );
   IsMP  = !IsNoValue( IfaBuf, PL_A02MP  );

   if ( IsAPO || IsSEH || IsAPP || IsVSP || IsMP )
   {
      if ( strcmp( IfaBuf->A03VWGAPO, "01" ) == 0 &&
           strcmp( IfaBuf->A03VWGSEH, "00" ) == 0 &&		/* 16.11 2000 */
		   (strcmp( IfaBuf->A02APPFL, "00" ) == 0 || strcmp( IfaBuf->A02APPFL,  "  " ) == 0 || (strcmp( IfaBuf->A02APPFL, "02" ) == 0 && strcmp( IfaBuf->A02MP, "01" ) == 0)) &&
           (strcmp( IfaBuf->A02VSPFL, "00" ) == 0 || strcmp( IfaBuf->A02VSPFL,  "  " ) == 0 || (strcmp( IfaBuf->A02VSPFL, "03" ) == 0 && strcmp( IfaBuf->A02MP, "01" ) == 0)) )
       return '1';
      else
       return '0';
   }
   return ' ';
}

static void Make_VERTRBIND_IFA( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
							    int IsArtikelVorhanden )
{
   char Vtb;
   Vtb = Build_VERTRBIND_IFA( IfaBuf );
   if ( IsArtikelVorhanden )
   {
      if ( *Buf->VERTRBIND_IFA == '0' && Vtb != ' ' )
           *Buf->VERTRBIND_IFA = Vtb;
   }
   else
   {
      if ( Vtb == ' ' ) Vtb = '0';
      *Buf->VERTRBIND_IFA = Vtb;
      Buf->VERTRBIND_IFA[1] = '\0';
   }

   // Immer lt. CPR-240206
   // Wenn A02VSPFL == "02" -> VERTRBIND_IFA = "1"
   if ( strcmp(IfaBuf->A02VSPFL, "02") == 0 )
   {
      strcpy(Buf->VERTRBIND_IFA, "1");
   }
}

/* Rezeptpflichtig */
static void CpyBtm( char *art, char *ifa, int IsArtikelVorhanden,
                       int NoValue )
{
   if ( NoValue ) 
	   return;

   if ( IsArtikelVorhanden )
   {
     if ( strcmp( ifa, "00" ) == 0 ||
          strcmp( ifa, "02" ) == 0   )
       *art = '0';
     else if ( strcmp( ifa, "01" ) == 0 )
       *art = '1';
   }
   else
   {
      *art = '0';

      if ( strcmp( ifa, "01" ) == 0 )
        *art = '1';
   }
   art[1] = '\0';
}

/* ---------- Sperre automatisch setzen mit IFA Version 20244 --------- */
static void Make_EK_SPERRE(struct ZARTIKEL* Buf)
{
	Buf->NAHRUNGSERGAENZUNG[0] = 'G';
	Buf->ZENTR_EKSPERRE[0] = '1';
}

/* Betaeubungsmittel */
static void Make_BTM( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                      int IsArtikelVorhanden )
{
   CpyBtm( Buf->BTM, IfaBuf->A02BTM, IsArtikelVorhanden, IsNoValue( IfaBuf, PL_A02BTM ) );

   if (!IsArtikelVorhanden || !IsNoValue( IfaBuf, PL_A02BTM ))
   {
	   if (strcmp( IfaBuf->A02BTM, "02" ) == 0)
	   {
		   *Buf->PSYCHOTROP = 'J';
		   *Buf->BESTELL_NICHT_AUSL = '1';
	   }
	   else if (strcmp( IfaBuf->A02BTM, "01" ) == 0)
	   {
	      *Buf->PSYCHOTROP = 'N';
	   }
   }

   /* ------ Neuartikel und BTM -> Sperre automatisch setzen mit IFA Version 20244 ----- */
   if (!IsArtikelVorhanden &&
	   (strcmp(IfaBuf->A02BTM, "01") == 0))
   {
	   Make_EK_SPERRE( Buf );
   }
}

/* ChargenDoku ( TFG ) */
static void Make_TFG( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                      int IsArtikelVorhanden )
{
   Cpy02Kenn( Buf->TFG, IfaBuf->A02TFG, IsArtikelVorhanden,
              IsNoValue( IfaBuf, PL_A02TFG ) );
}


/* Tierarznei */  /* !! warum keine Uebernahme */
static void Make_TIERARZNEI( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                             int IsArtikelVorhanden )
{
   //Cpy01Kenn( Buf->TIERARZNEI, IfaBuf->A02TIERAM, IsArtikelVorhanden,
   //           IsNoValue( IfaBuf, PL_A02TIERAM ) );

   if (!IsNoValue(IfaBuf, PL_A02TIERAM))
   {
	   if (strcmp(IfaBuf->A02TIERAM, "01") == 0)
	   {
		   strncpy(Buf->TIERARZNEI, "1", 2);
		   strncpy(Buf->VERTRBIND, "G", 2);			//SR-24128659
	   }
	   else
	   {
		   strncpy(Buf->TIERARZNEI, "0", 2);
		   if (*Buf->VERTRBIND == 'G')				//SR-24128659
			   strncpy(Buf->VERTRBIND, " ", 2);
	   }
   }
}


/* Zuzahlung */
static void Make_ZUZAHLUNG_IFA( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                                int IsArtikelVorhanden )
{
   if ( !IsNoValue( IfaBuf, PL_ZUZAHL ) )
      strcpy( Buf->ZUZAHLUNG_IFA, IfaBuf->ZUZAHL );
}

/* Laufzeit in Monaten */
static void Make_LAUFZEITMONATE( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                                 int IsArtikelVorhanden, int *ToStoreSwg1 )
{
	if (!IsNoValue(IfaBuf, PL_A05LZEIT))
	{
		Buf->LAUFZEITMONATE = IfaBuf->A05LZEIT;

		// SWG1 Warengruppe setzen bei Neuanlage und Laufzeit > 0 und < 15 Monate
		if (!IsArtikelVorhanden && IfaBuf->A05LZEIT > 0 && IfaBuf->A05LZEIT < 15)
		{
			*ToStoreSwg1 = 1;    // zartwg.art = 5, Warengruppe KL
		}
	}
}


static int IsKeineAngabe_Blank( char *ifa )
{
   while ( *ifa && *ifa == ' ' ) ifa++;
   return !(*ifa);

}

static void CpyZahl( long *art, char *ifa, int IsArtikelVorhanden,
                     int NoValue )
{
   if ( NoValue ) return;
   if ( IsArtikelVorhanden )
   {
     if ( !IsKeineAngabe_Blank( ifa ) )
        *art = atol( ifa );
   }
   else
   {
     if ( !IsKeineAngabe_Blank( ifa ) )
        *art = atol( ifa );
     else
        *art = 0;
   }
}


/* Laenge */
static void Make_LAENGE( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                         int IsArtikelVorhanden )
{
   if (( IsArtikelVorhanden ) && ( Buf->DATUM_MWE > 0))
     return;

   CpyZahl( &Buf->LAENGE, IfaBuf->A04LAENGE, IsArtikelVorhanden,
            IsNoValue( IfaBuf, PL_A04LAENGE ) );
}

/* Breite */
static void Make_BREITE( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                         int IsArtikelVorhanden )
{
   if (( IsArtikelVorhanden ) && ( Buf->DATUM_MWE > 0))
     return;

   CpyZahl( &Buf->BREITE, IfaBuf->A04BREITE, IsArtikelVorhanden,
            IsNoValue( IfaBuf, PL_A04BREITE ) );
}

/* Hoehe  */
static void Make_HOEHE( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                        int IsArtikelVorhanden )
{
   if (( IsArtikelVorhanden ) && ( Buf->DATUM_MWE > 0))
     return;

   CpyZahl( &Buf->HOEHE, IfaBuf->A04HOEHE, IsArtikelVorhanden,
            IsNoValue( IfaBuf, PL_A04HOEHE ) );
}

/* Gewicht */
static void Make_GEWICHT( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                          int IsArtikelVorhanden )
{
   if (( IsArtikelVorhanden ) && ( Buf->DATUM_MWE > 0))
     return;

   CpyZahl( &Buf->GEWICHT, IfaBuf->A04GWCHT, IsArtikelVorhanden,
            IsNoValue( IfaBuf, PL_A04GWCHT ) );
}


/* Artikel_nr_herst 26.09.2002 */
static void Make_ARTIKEL_NR_HERST( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
								   int IsArtikelVorhanden )
{
	if ( !IsArtikelVorhanden )
	{
		if ( !IsNoValue( IfaBuf, PL_A00ARTNR ) ) 
		{
			memcpy( Buf->ARTIKEL_NR_HERST, IfaBuf->A00ARTNR, L_ZARTIKEL_ARTIKEL_NR_HERST );
			Buf->ARTIKEL_NR_HERST[L_ZARTIKEL_ARTIKEL_NR_HERST] = '\0';
		}
	}
}




/* Kuehlartikel: wird nur uebernommen, wenn Zustand = '0' war ( s. Protokol)  */
char Build_KUEHLARTIKEL( struct ZIFAART *IfaBuf, int IsArtikelVorhanden, int *ToStoreSwg1 )
{
	int temp;
    temp = atoi( IfaBuf->A05TMAX );

	/* TH - nach Klärung aller betroffener Applikationen aktivieren ...
	if ( !IsNoValue( IfaBuf, PL_A05TMAX ) )
	{
		 if ( *IfaBuf->A05TMAX != ' ' && temp < 0 )
           return '5';
	}*/

	if ( !IsNoValue( IfaBuf, PL_A05KKETTE ) )
	{
		if ( strcmp( IfaBuf->A05KKETTE, "01" ) == 0 )
		{
			if (!IsArtikelVorhanden)
			    *ToStoreSwg1 = 2;  // Ifa Version 248: zartwg.art = 5, Warengruppe KK
			return '4';
		}
	}

   if ( !IsNoValue( IfaBuf, PL_A05TMAX ) )  /* maximale Temperatur */
   {
      if ( *IfaBuf->A05TMAX != ' ' )
      {
		if (temp <= 19)
		{
		  if (!IsArtikelVorhanden && temp == 8)
			  *ToStoreSwg1 = 3;  // Ifa Version 248: zartwg.art = 5, Warengruppe K8
		  return '1';
		}
        else if ( temp <= 24 )
           return '2';
        else if ( temp <= 29 )
           return '3';
        else
           return '0';
      }
   }
   return ' ';
}

static void Make_KUEHLARTIKEL( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                               int IsArtikelVorhanden, int *ToStoreSwg1)
{
   char KuehlArt;
   KuehlArt = Build_KUEHLARTIKEL( IfaBuf, IsArtikelVorhanden, ToStoreSwg1 );
   if ( IsArtikelVorhanden )
   {
     if ( *Buf->KUEHLARTIKEL == '0' && KuehlArt != ' ' )
        *Buf->KUEHLARTIKEL = KuehlArt;
   }
   else
   {
      if ( KuehlArt == ' ' ) 
		  KuehlArt = '0';

      *Buf->KUEHLARTIKEL = KuehlArt;
      Buf->KUEHLARTIKEL[1] = '\0';
   }
}


/* Ersatz-Nr */
static void Make_ERSATZ_NR( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf )
{
   if ( !IsNoValue( IfaBuf, PL_A06PZNNF ) )
   {
      if ( IfaBuf->A06PZNNF > 0 )
          Buf->ERSATZ_NR = IfaBuf->A06PZNNF;
   }
}


/* Datum Rueckruf */
static void Make_DATUM_RR( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                           long datum )
{
   if ( IsNoValue( IfaBuf, PL_A03VKSTAT ) ) return;

   if ( strcmp( IfaBuf->A03VKSTAT, "00" ) == 0 )
      Buf->DATUM_RR = datum;
}

static void CpyMwst( char *art, char *ifa, int IsArtikelVorhanden )
{
   if ( IsArtikelVorhanden )
   {
      if ( strcmp( ifa, "00" ) == 0 )
        *art = '0';
      else if ( strcmp( ifa, "01" ) == 0 )
        *art = '1';
      else if ( strcmp( ifa, "02" ) == 0 )
        *art = '2';
   }
   else
   {
      strcpy( art, "0" );
      if ( strcmp( ifa, "01" ) == 0 )
        *art = '1';
      else if ( strcmp( ifa, "02" ) == 0 )
        *art = '2';
   }
}



/* ---- NEM-Artikel ----- 12.09.2001 */

static void Make_NemArtikel( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                             int IsArtikelVorhanden )
{
   if ( IsArtikelVorhanden )
   {
	    /* Artikelaenderung */ 
	   if ((Buf->NAHRUNGSTEST[0] == 'Z') || (Buf->NAHRUNGSTEST[0] == 'L')  || (Buf->NAHRUNGSTEST[0] == '*')) 
	   {
		   /* Bei Z,L und * keine Aenderung */
		   return;
	   }

	   if ( IsNoValue( IfaBuf, PL_A02DIAET ) && IsNoValue( IfaBuf, PL_A02NEM ) && IsNoValue( IfaBuf, PL_A02LEBENSM ))
	   {
			/* CR-269: keine neuen Info´s von IFA --> keine Änderung! */
		    return;
	   }
   }
   else
   {
		*Buf->NAHRUNGSTEST = ' ';

		/* IFA Version 20244: Wert 'G' nicht ueberschreiben,        */
		/* wurde bspw. in Make_BTM gesetzt und soll auch so bleiben */
		if (Buf->NAHRUNGSERGAENZUNG[0] != 'G')
		{
			*Buf->NAHRUNGSERGAENZUNG = 'N';
		}
   }

    /* NEM Artikel */
	if ((strcmp( IfaBuf->A02LEBENSM,   "01" ) == 0 ) && 
		( strcmp( IfaBuf->A02NEM,   "01" ) == 0 ) &&
	   ((strcmp( IfaBuf->A02DIAET,    "00" ) == 0 ) || 
	   (strcmp( IfaBuf->A02DIAET,     "  " ) == 0 ) || 
	   IsNoValue( IfaBuf, PL_A02DIAET )))
		{
			*Buf->NAHRUNGSTEST = 'K';
		}
	/* Diaetisches Lebensmittel */ 
	if ((strcmp( IfaBuf->A02LEBENSM,   "01" ) == 0 ) && 
	   ((strcmp( IfaBuf->A02DIAET,     "01" ) == 0 ) || ( strcmp( IfaBuf->A02DIAET,   "99" ) == 0)) && 
	   ((strcmp( IfaBuf->A02NEM,      "00" ) == 0 ) || 
	   ( strcmp( IfaBuf->A02NEM,      "  " ) == 0 ) || 
	   IsNoValue( IfaBuf, PL_A02NEM )))
		{
			*Buf->NAHRUNGSTEST = 'D';
		}
	/* Lebensmittel 99 und Rest nicht gesetzt*/
	if (
	   (strcmp( IfaBuf->A02LEBENSM,   "99" ) == 0 ) &&
	   ((strcmp( IfaBuf->A02DIAET,    "00" ) == 0 ) || 
	   (strcmp( IfaBuf->A02DIAET,     "  " ) == 0 ) || 
	   (IsNoValue( IfaBuf, PL_A02DIAET ))) &&
	   ((strcmp( IfaBuf->A02NEM,      "00" ) == 0 ) || 
	   ( strcmp( IfaBuf->A02NEM,      "  " ) == 0 ) || 
	   IsNoValue( IfaBuf, PL_A02NEM )))
		{
			*Buf->NAHRUNGSTEST = 'F';
		}
   
      if (( !IsArtikelVorhanden ) && (Buf->NAHRUNGSTEST[0] != ' '))
	  {
		  *Buf->NAHRUNGSERGAENZUNG ='G';
          strcpy( Buf->ZENTR_EKSPERRE, "1" );
	  }

   
}


/* Arzneimittel 12.03.2003 */
static void Make_Arzneimittel( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                               int IsArtikelVorhanden )
{
   Cpy01Kenn( Buf->ARZNEIMITTEL, IfaBuf->A02AM, IsArtikelVorhanden,
              IsNoValue( IfaBuf, PL_A02AM ) );
}

/* Medizinprodukt 12.03.2003 */
static void Make_Medizinprodukt( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                                 int IsArtikelVorhanden )
{
   Cpy01Kenn( Buf->MEDIZINPRODUKT, IfaBuf->A02MP, IsArtikelVorhanden,
              IsNoValue( IfaBuf, PL_A02MP ) );
}

/* CE-Kennzeichen 12.03.2003 */
static void Make_CE( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                     int IsArtikelVorhanden )
{
//   Cpy01Kenn( Buf->CE_KENNZEICHEN, IfaBuf->A02CE, IsArtikelVorhanden,
//              IsNoValue( IfaBuf, PL_A02CE ) );
}

/* Hilfsmittel zum Verbrauch */
static void Make_HilfsmittelVerbrauch( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                                       int IsArtikelVorhanden )
{
   Cpy01Kenn( Buf->HILFSM_VERBRAUCH, IfaBuf->A02HMZV, IsArtikelVorhanden,
              IsNoValue( IfaBuf, PL_A02HMZV ) );
}

static void Make_ABGABEBEST( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                                       int IsArtikelVorhanden )
{
    /* A02VSPFL = '02', dann abgabebest_ifa = '9'
	   A02VSPFL = '03', dann abgabebest_ifa = '6'
       A02VSPFL = blank, 00, 01 dann abgabebest_ifa = blank */

	if ( !IsNoValue( IfaBuf, PL_A02VSPFL ) )
	{
		if (strcmp(IfaBuf->A02VSPFL,"02") == 0)
			strcpy( Buf->ABGABEBEST_IFA, "9" );
		else if (strcmp(IfaBuf->A02VSPFL,"03") == 0)
			strcpy( Buf->ABGABEBEST_IFA, "6" );
		else if (((strcmp(IfaBuf->A02VSPFL,"00") == 0) || (strcmp(IfaBuf->A02VSPFL,"01") == 0) || (strcmp(IfaBuf->A02VSPFL,"  ") == 0)) && 
			(strcmp(Buf->ABGABEBEST_IFA, "8") != 0) && (strcmp(Buf->ABGABEBEST_IFA, "7") != 0) )
			strcpy( Buf->ABGABEBEST_IFA, " " );
	}

	/* A02APPFL = '02', dann abgabebest_ifa = '7'
	   A02APPFL = blank, 00, 01 dann abgabebest_ifa = blank */

	if ( !IsNoValue( IfaBuf, PL_A02APPFL ) )
	{
		if (strcmp(IfaBuf->A02APPFL,"02") == 0 && strcmp(Buf->ABGABEBEST_IFA, "6") != 0) // 6 hat höhere Prio als 7!
			strcpy( Buf->ABGABEBEST_IFA, "7" );
		else if (((strcmp(IfaBuf->A02APPFL,"00") == 0) || (strcmp(IfaBuf->A02APPFL,"01") == 0) || (strcmp(IfaBuf->A02APPFL,"  ") == 0)) && 
			(strcmp(Buf->ABGABEBEST_IFA, "6") != 0) && (strcmp(Buf->ABGABEBEST_IFA, "8") != 0) && (strcmp(Buf->ABGABEBEST_IFA, "9") != 0) )
			strcpy( Buf->ABGABEBEST_IFA, " " );
	}

	/* A02DROCH = '01', dann abgabebest_ifa = '8'
	   A02DROCH = blank, 00 dann abgabebest_ifa = blank */

	if ( !IsNoValue( IfaBuf, PL_A02DROCH ) )
	{
		if (strcmp(IfaBuf->A02DROCH,"01") == 0)
			strcpy( Buf->ABGABEBEST_IFA, "8" );
		else if (((strcmp(IfaBuf->A02DROCH,"00") == 0) || (strcmp(IfaBuf->A02DROCH,"  ") == 0)) && 
			(strcmp(Buf->ABGABEBEST_IFA, "6") != 0) && (strcmp(Buf->ABGABEBEST_IFA, "7") != 0) && (strcmp(Buf->ABGABEBEST_IFA, "9") != 0) )
			strcpy( Buf->ABGABEBEST_IFA, " " );
	}
}

static void Make_LANGNAME( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                                       int IsArtikelVorhanden )
{
	if ( strlen(IfaBuf->A00PNAM) > 0 )
	{
		strcpy( Buf->ARTIKEL_LANGNAME,IfaBuf->A00PNAM );
	}

}

/* Ausnahme §51 AMG 03.04.06 */
static void	Make_Amg_Ausnahmereg( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{

  Cpy01Direct( Buf->AMG_AUSNAHMEREG, IfaBuf->A02AUSNREI, IsNoValue( IfaBuf, PL_A02AUSNREI ) );
}


/* Generika AVWG 03.04.06 */
static void	Make_Zulass_Generika( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
  Cpy01Direct( Buf->ZULASS_GENER, IfaBuf->A02GENER, IsNoValue( IfaBuf, PL_A02GENER ) );
}

static void	Make_HOMOEO( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
  Cpy01Direct( Buf->HOMOEOPATHIKUM, IfaBuf->A02HOMOEO, IsNoValue( IfaBuf, PL_A02HOMOEO ) );
}

static void	Make_ANTHRO( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
  Cpy01Direct( Buf->ANTHROPOSOPHIKUM, IfaBuf->A02ANTHRO, IsNoValue( IfaBuf, PL_A02ANTHRO ) );
}

static void	Make_PHYTO( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
  Cpy01Direct( Buf->PHYTOPHARMAKON, IfaBuf->A02PHYTO, IsNoValue( IfaBuf, PL_A02PHYTO ) );
}

static void	Make_BIOZID( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden, int* ToStoreAbdaWg)
{
	if ( !IsArtikelVorhanden
		|| strcmp(IfaBuf->A02BIOZID, "01") == 0
		|| strcmp(IfaBuf->A02BIOZID, "00") == 0   // CPR-240206: Auch Update!
		|| strcmp(IfaBuf->A02BIOZID, ""  ) == 0)  // CPR-240206: Auch Update!
    {
		// bei Neuanlage Übernahme 1:1 (leer / 00 --> 0; 01 -> 1)
		// bei Änderung (leer / 00 --> 0; 01 --> 1)

		Cpy01DirectBiozid( Buf->BIOZID_VERORD, IfaBuf->A02BIOZID );
	}

	// ABDA Warengruppe setzen bei Neuanlage und Biozid-Produkt, wenn A02PSM und A02SDB nicht gesetzt sind
	if (!IsArtikelVorhanden && 
		(strcmp(IfaBuf->A02BIOZID, "01") == 0) &&
		(strcmp(IfaBuf->A02PSM, "01") != 0) &&
		(strcmp(IfaBuf->A02SDB, "01") != 0))
	{
		*ToStoreAbdaWg = 5;    // zartwg.art = 4, Warengruppe BIOZ
	}
}

static void	Make_WIRKSTOFF( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf )
{
	// bei Neuanlage Übernahme 1:1 (leer / 00 --> 0; 01 -> 1)
	// bei Artikel-Änderung Übernahme nur, wenn Feld über IFA tatsächlich gemeldet

	if ( !IsNoValue( IfaBuf, PL_A02WIRKSTO ) )
	{
		if (strcmp(IfaBuf->A02WIRKSTO, "01") == 0)
			Buf->WIRKSTOFF = 1;
		else
			Buf->WIRKSTOFF = 0;
	}
}

static void	Make_BATTERIEGESETZ( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden, int * ToStoreAbdaWg )
{
	if (strcmp(IfaBuf->A02BATTG, "01") == 0)
	{
		if ( !IsArtikelVorhanden ||																// Neuanlage
			 (!IsNoValue( IfaBuf, PL_A02BATTG ) && strcmp(Buf->BATTERIEGESETZ, "N") == 0) )	// Artikel- Änderung, IFA=01, aktueller zartikel = N (für zartikel != N nix machen)
		{
			*Buf->BATTERIEGESETZ = 'J';	
			*Buf->BESTELL_NICHT_AUSL = '1';
			
			*ToStoreAbdaWg = 1; // zartwg.art = 4, warengruppe = BATT		
		}
	}
	else if ( !IsArtikelVorhanden ) // Neuanlage
	{
		*Buf->BATTERIEGESETZ = 'N';	// passiert auch schon in InitRestArtikel
	}
}

static void Make_ELEKTRO_SPERRE(struct ZARTIKEL* Buf, int* ToStoreAbdaWg)
{
	Buf->NAHRUNGSERGAENZUNG[0] = 'G';
	Buf->ZENTR_EKSPERRE[0] = '1';
	Buf->BESTELL_NICHT_AUSL[0] = '1';
	*ToStoreAbdaWg = 1; // zartwg.art = 4, warengruppe = BATT
}

static void	Make_ELEKTRO( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden, int * ToStoreAbdaWg )
{
	// Die Fehlerfälle mit zwingenden Fehlern wurden ZPIARTIK markiert und werden nicht synchronisiert
	// Trotzdem sind nicht alle Elektroänderungen semantisch korrekt. Deshalb wurde beschlossen
	// Bei allen Änderungen an Bestandsartikeln zunächst die Einkaufsperre zu setzen
	short modified = 0;

	// Wenn keines der folgenden Elektro-Felder aus der IFA mitgeliefert wurde, keine Pruefungen und Zuweisungen
	// durchfuehren, da sonst evtl. manuell freigegebene Artikel wieder gesperrt wuerden
	if (IsNoValue(IfaBuf, PL_A02ELEKTRO) &&
		IsNoValue(IfaBuf, PL_A02BATTREG) &&
		IsNoValue(IfaBuf, PL_A02STIFEAR) &&
		IsNoValue(IfaBuf, PL_A02WEEEREG)
	   ) return;

	if (strcmp(IfaBuf->A02ELEKTRO, "00") == 0 || strcmp(IfaBuf->A02ELEKTRO, "  ") == 0)
	{
		// Dieser Schalter drückt nicht aus, dass es kein Elektroartikel ist, sondern nur
		// dass der Elektroartikel nicht der Elektrostoffverordnung unterliegt.
		// Es kann auf Basis der A02STIFFEAR immer noch ein registrierter Elektroartikel sein
		// oder Aufgrund von A02BATTREG ein rein Batterie betriebener Elektroartikel bzw. eine Batterie
		// Bei einem registrierten Elektroartikel wird unabhängig von A02ELEKTRO der Status R erwartet
		// Bei einem reinem Elektroartikel kann der Status N und BATTG = J sein
		if (!IsNullZeroOrEmpty(IfaBuf->A02WEEEREG))
		{
			if (!IsArtikelVorhanden || (Buf->ELEKTROSCHROTT[0] != 'R' && Buf->ELEKTROSCHROTT[0] != 'I'))
			{
				// nicht infektiöse Elektroartikel werden registriert
				Buf->ELEKTROSCHROTT[0] = 'R';
				modified = 1;
			}
		}
		else if (!IsArtikelVorhanden)
		{
			Buf->ELEKTROSCHROTT[0] = 'N';
		}
		if (!IsNullZeroOrEmpty(IfaBuf->A02BATTREG))
		{
			// Nur der Status 'N' wird überschrieben alle übrigen Stati markieren besondere Batterien
			// und beinhalten explizit den Status 'J'
			if (!IsArtikelVorhanden || Buf->BATTERIEGESETZ[0] == 'N')
			{
				Buf->BATTERIEGESETZ[0] = 'J';
				modified = 1;
			}
		}
		else if (!IsArtikelVorhanden)
		{
			Buf->BATTERIEGESETZ[0] = 'N';
		}
		// Auf Basis von A02ELEKTRO kann nicht ermittelt werden, dass es kein Elektroartikel ist
		// sondern nur dass er nicht der Elektroschrottverordnung unterliegt
		// also bleibt der Status im Bestand unverändert wenn es keine Registriernummern gibt.
	}
	else if (strcmp(IfaBuf->A02ELEKTRO, "01") == 0)
	{
		// Der Artikel unterliegt der Elektroschrott Verordnung
		// Ein registrierter Artikel beinhaltet bereits die Elektroschrottverordnung
		// Ein infektiöser Artikel wird nicht überschrieben weil manuell so definiert
		if (!IsArtikelVorhanden || Buf->ELEKTROSCHROTT[0] == 'N')
		{
			Buf->ELEKTROSCHROTT[0] = 'J';
			modified = 1;
		}
	}

	if (strcmp(IfaBuf->A02STIFEAR, "00") == 0 || strcmp(IfaBuf->A02STIFEAR, "  ") == 0)
	{
		// Dieser Schalter kennzeichnet ob ein Elektroartikel für die Wertstoffrückführung bei Entsorgung registriert wurde
		// oder nicht. Eine Registrierung führt implizit auch zu einem registrieten Elektroartikel bei den Stammdaten
		// weil der Schalter ELEKTROSCHROTT sich nicht rein auf die Elektro Stoffverordnung bezieht.
		// Der Schalter A02STIFEAR wird implizit 1 angenommen wenn A02WEEREG gesetzt ist. Es kann jedoch sein
		// dass die Registrierung in IFA falsch war und an sich zur BATTREG gehört. Dieser Fehler kann nicht
		// automatisch korrigiert weden.
		if (!IsNullZeroOrEmpty(IfaBuf->A02WEEEREG))
		{
			// Die bestehend Registriernummer wird verarbeitet als ob A02STIFEAR = "01" wäre
			if (!IsArtikelVorhanden || (Buf->ELEKTROSCHROTT[0] != 'R' && Buf->ELEKTROSCHROTT[0] != 'I'))
			{
				// nicht infektiöse Elektroartikel werden registriert
				Buf->ELEKTROSCHROTT[0] = 'R';
				modified = 1;
			}
		}
		else
		{
			if (IsArtikelVorhanden && (Buf->ELEKTROSCHROTT[0] == 'R'))
			{
				// Arikel ist nicht registriert
				Buf->ELEKTROSCHROTT[0] = 'J';
				modified = 1;
	        }
		}
		if (!IsNullZeroOrEmpty(IfaBuf->A02BATTREG))
		{
			// Nur der Status 'N' wird überschrieben alle übrigen Stati markieren besondere Batterien
			// und beinhalten explizit den Status 'J'
			if (IsArtikelVorhanden && Buf->BATTERIEGESETZ[0] == 'N')
			{
				Buf->BATTERIEGESETZ[0] = 'J';
				modified = 1;
			}
		}
	}
	else if (strcmp(IfaBuf->A02STIFEAR, "01") == 0)
	{
		// Nur bei WEEEREG wird es zum ELEKTROSCHROTT = 'R' wenn der Status 'J' oder 'N' ist
		// Status 'I' kann auch registriert sein, muss aber nicht, Status 'I' wird nicht verändert
		if (IsArtikelVorhanden && (Buf->ELEKTROSCHROTT[0] == 'N' || Buf->ELEKTROSCHROTT[0] == 'J') && !IsNullZeroOrEmpty(IfaBuf->A02WEEEREG))
		{
			Buf->ELEKTROSCHROTT[0] = 'R';
			modified = 1;
		}
		if (!IsNullZeroOrEmpty(IfaBuf->A02BATTREG))
		{
			if (IsArtikelVorhanden && (Buf->BATTERIEGESETZ[0] == 'N'))
			{
				Buf->BATTERIEGESETZ[0] = 'J';
				modified = 1;
			}
		}
	}

	if (!IsNullZeroOrEmpty(IfaBuf->A02WEEEREG))
	{
		// Sobald eine WEEREG / EAR von IFA übergeben wurde, ist es ein registrierter Elektroartikel
		// die WEEREG wird später als EAR (code_type = 1) in die Tabelle carticlecodes übernommen
		if (Buf->ELEKTROSCHROTT[0] != 'R' && Buf->ELEKTROSCHROTT[0] != 'I')
		{
			Buf->ELEKTROSCHROTT[0] = 'R';
			modified = 1;
		}
	}

	if (!IsNullZeroOrEmpty(IfaBuf->A02BATTREG))
	{
		// Eine reine BATTREG verändert nicht den Elektroschrott Status
		// BATTREG in zartikel uebernehmen mit IFA Version 20244
		strcpy(Buf->BATTREG, IfaBuf->A02BATTREG);

		// Bei neuen Artikeln oder Batteriegesetz == 'N' Batteriegesetz auf 'J' setzen, wenn A02BATTREG angegeben ist
		// Wird in den obigen Bedinungen nicht hinreichend beruecksichtigt
		if (!IsArtikelVorhanden || Buf->BATTERIEGESETZ[0] == 'N')
		{
			Buf->BATTERIEGESETZ[0] = 'J';
		}

		// Bei neuen Artikeln Elektro-Sperre setzen
		if (!IsArtikelVorhanden)
		{
			modified = 1;
		}
	}

	if (modified > 0)
	{
		Make_ELEKTRO_SPERRE(Buf, ToStoreAbdaWg);
	}
}

static void	Make_LAGEEMPFL( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf )
{
	// bei Neuanlage Übernahme 1:1 (leer / 00 --> 0=nein; 01 -> 1=liegend; 02 -> 2=aufrecht)
	// bei Artikel-Änderung Übernahme nur, wenn Feld über IFA tatsächlich gemeldet

	if ( !IsNoValue( IfaBuf, PL_A05LAGE ) )
	{
		if (strcmp(IfaBuf->A05LAGE,"02") == 0)
			Buf->LAGEEMPF = 2;
		else if (strcmp(IfaBuf->A05LAGE,"01") == 0)
			Buf->LAGEEMPF = 1;
		else
			Buf->LAGEEMPF = 0;
	}
}

static void	Make_KOSMETIKUM( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
	if ( !IsArtikelVorhanden || strcmp(IfaBuf->A02KOSMET, "01") == 0 )
    {
		// bei Neuanlage Übernahme 1:1 (leer / 00 --> 0; 01 -> 1)
		// bei Änderung (leer / 00 --> kein Update; 01 --> 1)

		if ( !IsNoValue( IfaBuf, PL_A02KOSMET ) )
		{
			if (strcmp(IfaBuf->A02KOSMET, "01") == 0)
				Buf->KOSMETIKUM = 1;
			else
				Buf->KOSMETIKUM = 0;
		}
	}
}

static void	Make_UNNR( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
	if ( !IsArtikelVorhanden )
    {
		// bei Neuanlage Übernahme 1:1 
		// bei Änderung keine Datenübernahme!

		if ( !IsNoValue( IfaBuf, PL_A02UNNR ) && strcmp (IfaBuf->A02UNNR, "0   ") != 0)
			strcpy(Buf->G_UN_NR, IfaBuf->A02UNNR);
	}
}

static void	Make_DATUM_FMDPFLICHT( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
	if ( !IsArtikelVorhanden || !IsNoValue( IfaBuf, PL_A11VERIPFL ) )
	{
		if ( atoi( IfaBuf->A11VERIPFL ) > 0 )
		{
			int temp;
			char year[5] = { 0 }; // 4 chars + terminator */
			char month[3] = { 0 }; // 2 chars + terminator */
			
			memset(year, 0, 5);
			memset(month, 0, 3);

			strncpy(year, IfaBuf->A11VERIPFL + 2, 4);
			strncpy(month, IfaBuf->A11VERIPFL, 2);

			temp = atoi (year) * 10000;
			Buf->DATUM_FMDPFLICHT = temp;

			temp = atoi (month) * 100;
			Buf->DATUM_FMDPFLICHT += temp;

			Buf->DATUM_FMDPFLICHT += 1; // first day of month
		}
		else
			Buf->DATUM_FMDPFLICHT = 0;
	}
}

static void	Make_EXPLOSIV( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
	if ( IsNoValue( IfaBuf, PL_A02EXPLOS ) ) 
	   return;

    if ( strcmp( IfaBuf->A02EXPLOS, "01" ) == 0 )
	    Buf->EXPLOSIVGRUNDSTOFF = 1;
	
	// --> bei bestehenden Artikeln das Kennzeichen nie auf 0 zurücksetzen !!!
    else if ( !IsArtikelVorhanden ) // strcmp( IfaBuf->A02EXPLOS, "00" ) || strcmp( IfaBuf->A02EXPLOS, "  " )
		Buf->EXPLOSIVGRUNDSTOFF = 0; 
}

static void	Make_BIOTECH( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
	if ( IsNoValue( IfaBuf, PL_A02BIOTECH ) ) 
	   return;

    if ( strcmp( IfaBuf->A02BIOTECH, "01" ) == 0 )
	    Buf->BIOTECH_ARZNEI = 1;
    else if ( strcmp( IfaBuf->A02BIOTECH, "02" ) == 0 )
	    Buf->BIOTECH_ARZNEI = 2;
    else if ( strcmp( IfaBuf->A02BIOTECH, "03" ) == 0 )
	    Buf->BIOTECH_ARZNEI = 3;
    else // if ( strcmp( IfaBuf->A02BIOTECH, "00") == 0 || strcmp( IfaBuf->A02BIOTECH, "  ") == 0 )
		Buf->BIOTECH_ARZNEI = 0;
}

// Sonstiges Wundprodukt Ja/Nein Feld in Artikel Maske 3 WGR / Sortiment
// Leer - keine Angabe = nein
// 00 - nein
// 01 - ja
static void	Make_SONST_WUNDPRODUKT(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf)
{
	if (IsNoValue(IfaBuf, PL_A02SWUNDB))
		return;

	if (IfaBuf->A02SWUNDB == 1)
		Buf->WUNDPRODUKT = 1;
	else 
		Buf->WUNDPRODUKT = 0;
}

// Prüfung auf Arzneimittel für neuartike Therapien ohne FMD Prüfung
// Leer - keine Angabe = nein
// 00 - nein
// 01 - Gentherapeutikum = ja
// 02 - somatisches Zelltherpeutikum = ja
// 03 - Tumorimpfstoff = ja
// 04 - Biotechnologischh bearbeitetes Gewebeprodukt = ja
// 05 - kombiniertes ATMP = ja
// 99 - sonstges ATMP = ja
static void Make_AM_NEUART_THERAPIE(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf, int IsArtikelVorhanden)
{
	if (IsNoValue(IfaBuf, PL_A02ATMP))
		return;

	if (IfaBuf->A02ATMP == 99)
	{
		Buf->NEUARTIGETHERAPIE = 9;
	}
	else
	{
		Buf->NEUARTIGETHERAPIE = IfaBuf->A02ATMP + 1;
	}
}

// Kennzeichnung für Impfstoffe §130a Absatz 2 SGB V / Ausnahmen von der Abschlagsprflich sind zu kennzeichnen
// Leer - keine Angabe = nein
// 00 - kein Impfstoff = nein
// 01 - Impfstoff abschlagpflichtig - Abschlag ermittelbar = ja
// 02 - Impfstoff nicht abschlagpflichtig = nein
// 03 - Impfstoff abschlagpflichtig - Abschlag nicht ermittelbar = ja
// 04 - Impfstoff nicht abschlagfplichtig  = nein
static void	Make_AUSNAHME_ABSCHLAGPFLICHT(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf)
{
	if (IsNoValue(IfaBuf, PL_A02AUSIMPF))
		return;

	Buf->AUSNAHMEABSCHLAGSPFLICHT = IfaBuf->A02AUSIMPF + 1;
}

// Kennzeichnung EU-Novel-Food Verordnung
// Leer - keine Angabe = nein
// 00 - nicht betroffen, kein Lebensmittel = nein
// 01 - kein Novel-Food = nein
// 02 - unbekanntes Novel Food = ja
// 03 - Novel Food EU-VO = ja
static void	Make_NOVEL_FOOD(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf, int IsArtikelVorhanden, int* ToStoreAbdaWg)
{
	if (IsNoValue(IfaBuf, PL_A02EUNOVEL))
		return;

	Buf->NOVELFOOD = IfaBuf->A02EUNOVEL + 1;

	/* -------- Automatisch Sperre setzen mit IFA Version 20244 -------- */
	/* IFA Version 20252: keine Sperren und keinen ABDA-Code mehr setzen
	if (!IsArtikelVorhanden &&
		(IfaBuf->A02EUNOVEL == 3))
	{
		Make_EK_SPERRE(Buf);
		*ToStoreAbdaWg = 3;    zartwg.art = 4, Warengruppe SPNOV
	}
	*/

}

// Kennzeichnung Arzneimittel für seltene Leiden (Orphan Drug)
// Leer - keine Angabe
// 00 - nein
// 01 - ja
static void	Make_ORPHANDRUG(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf)
{
	if (IsNoValue(IfaBuf, PL_A02ORDRUG))
		return;

	if (IsNullZeroOrEmpty(IfaBuf->A02ORDRUG))
		Buf->ORPHANDRUG = 0;
	else
		Buf->ORPHANDRUG = 1;
}

// Kennzeichnung für bedingte Zulassung
// Leer - keine Angabe
// 00 - nein
// 01 - ja
static void	Make_BEDINGTZULASSUNG(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf)
{
	if (IsNoValue(IfaBuf, PL_A02BEDZUL))
		return;

	if (IsNullZeroOrEmpty(IfaBuf->A02BEDZUL))
		Buf->BEDINGTEZULASSUNG = 0;
	else
		Buf->BEDINGTEZULASSUNG = 1;
}

// Kennzeichnung Zulassung Ausnahmefälle
// Leer - keine Angabe
// 00 - nein
// 01 - ja
static void	Make_ZULASSUNGAUSNAHMEFAELLE(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf)
{
	if (IsNoValue(IfaBuf, PL_A02ZULAUSN))
		return;

	if (IsNullZeroOrEmpty(IfaBuf->A02ZULAUSN))
		Buf->ZULASSUNGAUSNAHMEFAELLE = 0;
	else
		Buf->ZULASSUNGAUSNAHMEFAELLE = 1;
}

// Kennzeichnung Amnog-Verfahren
// Leer - keine Angabe
// 00 - nein
// 01 - ja befindet sich im Bewertungsverfahren
// 02 - ja Bewertungsverfahren ist abgeschlossen
static void	Make_AMNOGVERFAHREN(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf)
{
	if (IsNoValue(IfaBuf, PL_A02AMNOG))
		return;

	if (strcmp(IfaBuf->A02AMNOG,"00") == 0)
		Buf->AMNOGVERFAHREN = 1;
	else if (strcmp(IfaBuf->A02AMNOG,"01") == 0)
		Buf->AMNOGVERFAHREN = 2;
	else if (strcmp(IfaBuf->A02AMNOG,"02") == 0)
		Buf->AMNOGVERFAHREN = 3;
	else
		Buf->AMNOGVERFAHREN = 0;
}

// Übernahme Zulassungsinhabernummer
// 5 stelliges numerisches Feld
static void	Make_ZULASSUNGSINHABERNR(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf)
{
	if (IsNoValue(IfaBuf, PL_A00ZINNR))
		return;

	if (!IsNullZeroOrEmpty(IfaBuf->A00ZINNR))
	{
		sscanf(IfaBuf->A00ZINNR, "%ld", &(Buf->ZULASSUNGSINHABERNR));
	}
}

// Übernahme örtlicher Vertreter-Nr.
// 5 stelliges numerisches Feld
static void	Make_OERTLICHEVERTRETERNR(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf)
{
	if (IsNoValue(IfaBuf, PL_A00OEVNR))
		return;

	if (!IsNullZeroOrEmpty(IfaBuf->A00OEVNR))
	{
		sscanf(IfaBuf->A00OEVNR,"%ld",&(Buf->OERTLICHEVERTRETERNR));
	}
}

// Kennzeichnung ob Serial-Number-Tracking aktiv ist
// Wenn das Feld A00UDIDI nicht leer ist, ist Serial Number Tracking aktiv.
static void Make_SERIAL_NO_TRACKING(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf)
{
	if (IsNoValue(IfaBuf, P_ZIFAART_A00UDIDI))
		return;
	size_t length = strlen(IfaBuf->A00UDIDI);
	if (length > 0)
	{
		// Prüfung ob Feld nicht mit Leerzeichen oder Nullen gefüllt ist
		short isEmpty = 1;
		int i = 0;
		while (isEmpty && i < length)
		{
			if (IfaBuf->A00UDIDI[i++] != ' ' && IfaBuf->A00UDIDI[i++] != '0')
			{
				isEmpty = 0;
			}
		}
		if (!isEmpty)
		{
			Buf->SERIAL_NUMBER_TRACKING = 1;
			Buf->CHARGENARTIKEL[0] = '1';
		}
	}
}

static void	Make_BESTELL_NICHT_AUSL( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
	// nur bei Neuanlage
	if ( !IsArtikelVorhanden )
	{
		if (Buf->NAHRUNGSTEST[0] == 'K' || Buf->NAHRUNGSTEST[0] == 'D' || 
			Buf->NAHRUNGSTEST[0] == 'F' )
		{
			*Buf->BESTELL_NICHT_AUSL = '1';		
		}
	}

	// Neuanlage + Änderung
	if ( !IsNoValue( IfaBuf, PL_A02BIOZID ) && Buf->BIOZID_VERORD[0] == '1' )
	{
		*Buf->BESTELL_NICHT_AUSL = '1';		
	}

	if ( !IsNoValue( IfaBuf, PL_A02KOSMET ) && Buf->KOSMETIKUM == 1 && Buf->BESTELL_NICHT_AUSL[0] != '1' )
	{
		*Buf->BESTELL_NICHT_AUSL = '2';		
	}
}

static void	Make_PSM( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden, int *ToStoreAbdaWg)
{
	if ( !IsArtikelVorhanden || 
		 (	strcmp(IfaBuf->A02PSM, "01")	   == 0 && 
			strcmp(Buf->PFLSCHUTZ_VERORD, "R") != 0 && 
			strcmp(Buf->PFLSCHUTZ_VERORD, "E") != 0 && 
			strcmp(Buf->PFLSCHUTZ_VERORD, "S") != 0 )
		)
    {
		// bei Neuanlage Übernahme 1:1 (leer / 00 --> N; 01 -> J)
		// bei Änderung (leer / 00 --> kein Update; 01 --> J - R/E/S nicht überschreiben !)

		if ( !IsNoValue( IfaBuf, PL_A02PSM ) )
		{
			if (strcmp(IfaBuf->A02PSM,"01") == 0)
				strcpy(Buf->PFLSCHUTZ_VERORD,"J");
			else
				strcpy(Buf->PFLSCHUTZ_VERORD,"N");
		}
	}

	/* -------- Automatisch Sperre setzen mit IFA Version 20244 -------- */
	if (!IsArtikelVorhanden &&
		(strcmp(IfaBuf->A02PSM, "01") == 0))
	{
		Make_EK_SPERRE( Buf );
		*ToStoreAbdaWg = 2;    // zartwg.art = 4, Warengruppe PFLSP
	}

}

static void	Make_TREZEP( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
  Cpy01Direct( Buf->TREZEPTARZNEI, IfaBuf->A02TREZEP, IsNoValue( IfaBuf, PL_A02TREZEP ) );
}

static void	Make_AMG( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
  Cpy01DirectAMG_47( Buf->AMG_47, IfaBuf->A0247AMG, IsNoValue( IfaBuf, PL_A0247AMG ) );
}

static void	Make_BSSICHG( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
  /* ab 2012 gibt es A01GHABSCH nicht mehr (war nur AMNOG- Übergang 2011)
  //Cpy01Direct( Buf->BSSICHG, IfaBuf->A01GHABSCH, IsNoValue( IfaBuf, PL_A01GHABSCH ) );*/
}

static void	Make_ERSTATTBETRAG( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden ) /* ab 01.04.2014 wird kein Erstattungsbetrag mehr geliefert! */
{
  if ( !IsNoValue( IfaBuf, PL_A01SERSTAT ) )
		Buf->ERSTATTBETRAG = IfaBuf->A01ERSTATT;
}

static void	Make_PPN( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf)
{
	if ( !IsNoValue( IfaBuf, PL_A00PPN ) )
		strcpy(Buf->PPN, IfaBuf->A00PPN);
}

static void	Make_Abschlag_130a2( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf)
{
	if ( !IsNoValue( IfaBuf, PL_A01SAB130A ) )
		Buf->ABSCHLAG_130A2 = IfaBuf->A01AB130A2;
}

static void	Make_Pilot_SecurPharm( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf)
{
	if ( !IsNoValue( IfaBuf, PL_A02VERIFIZ ) )
	{
		if (strcmp(IfaBuf->A02VERIFIZ, "01") == 0)
			Buf->PILOT_SECURPHARM = 1;
		else
			Buf->PILOT_SECURPHARM = 0;
	}
}

static void	Make_Abgabeverbot_52b( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf)
{
	if ( !IsNoValue( IfaBuf, PL_A0252B ) )
	{
		if (strcmp(IfaBuf->A0252B, "01") == 0)
			Buf->AUSNAHME_52B = 1;
		else
			Buf->AUSNAHME_52B = 0;
	}
}

static void	Make_Biosiegel( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf,
                            int IsArtikelVorhanden, int* ToStoreSwg2)
{
	if ( !IsNoValue( IfaBuf, PL_A02BIOSIEG ) )
	{
		if (strcmp(IfaBuf->A02BIOSIEG, "01") == 0)
			Buf->BIOSIEGEL = 1;
		else
			Buf->BIOSIEGEL = 0;

		// SWG2 Warengruppe setzen bei Neuanlage und Biosiegel = "01"
		if (!IsArtikelVorhanden && strcmp(IfaBuf->A02BIOSIEG, "01") == 0)
		{
			*ToStoreSwg2 = 1;    // zartwg.art = A, Warengruppe BI
			strcpy(Buf->BESTELL_NUR_OZEK, "1");
		}
	}
}

static void	Make_Steril( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf)
{
	if ( !IsNoValue( IfaBuf, PL_A02STERIL ) )
	{
		if (strcmp(IfaBuf->A02STERIL, "01") == 0)
			Buf->STERIL = 1;
		else
			Buf->STERIL = 0;

		
	}
}


/* Abschlag §130a 3b 03.04.06 */
static void	Make_Abschlag_130( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
//  Cpy01Direct( Buf->ABSCHLAG_130, IfaBuf->A02ABSCHL, IsNoValue( IfaBuf, PL_A02ABSCHL ) );
}

/* Sicherh.Datenbl.erforderl. */
static void	Make_Sidablatt( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden, int *ToStoreAbdaWg)
{
  Cpy01Direct( Buf->SIDABLATT, IfaBuf->A02SDB, IsNoValue( IfaBuf, PL_A02SDB ) );

  /* ---------- Automatisch Sperre setzen mit IFA Version 20244 -------- */
  /* ---------- Nicht, wenn es sich um ein Arzneimittel handelt -------- */
  /* ---------- Nicht, wenn es sich um ein Planzenschutzmittel handelt - */
  if (!IsArtikelVorhanden &&
	  (strcmp(IfaBuf->A02SDB, "01") == 0) &&
	  (strcmp(IfaBuf->A02AM,  "01") != 0) &&
	  (strcmp(IfaBuf->A02PSM, "01") != 0))
  {
	  Make_EK_SPERRE( Buf );
	  *ToStoreAbdaWg = 4;    // zartwg.art = 4, Warengruppe SDBSP
  }
}

static void	Make_Produktart( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden )
{
	if ( !IsNoValue( IfaBuf, PL_A00ATYP ) )
	{
		if (strcmp(IfaBuf->A00ATYP,"03") == 0)
			strcpy(Buf->PRODUKTART,"5");
		else if (strcmp(IfaBuf->A00ATYP,"04") == 0)
			strcpy(Buf->PRODUKTART,"7");
		else if (strcmp(IfaBuf->A00ATYP,"05") == 0)
			strcpy(Buf->PRODUKTART,"8");
		else if (strcmp(IfaBuf->A00ATYP, "06") == 0)
			strcpy(Buf->PRODUKTART, "F");
		else // A00ATYP=="00" / "01"
		{
			// 02/2018: Produktart nur auf 0 setzen, wenn aktueller Wert = 5/7/8/F, sonst keine Änderung!
			if ( Buf->PRODUKTART[0] == '5' || Buf->PRODUKTART[0] == '7' || Buf->PRODUKTART[0] == '8' || Buf->PRODUKTART[0] == 'F')
				strcpy(Buf->PRODUKTART,"0");
		}
	}
}
/* Artikelnummer Originalartikel */
static void Make_PznOrig( struct ZARTIKEL *Buf, struct ZIFAART *IfaBuf, int IsArtikelVorhanden)
{
	// --> Hr. Peetz 09.04.10: Änderung auf Wert "0000000" bedeutet keine Angabe - 
	//							vorhandene Werte im Artikelstamm sind zu löschen
	// if (IfaBuf->A06PZNORIG != 0) 
	if ( !IsNoValue( IfaBuf, PL_A06PZNORIG ) )
		Buf->ARTIKEL_NR_ORIG = IfaBuf->A06PZNORIG;
}

/* ------- IFA Version 20244 ------- */
static void	Make_AM_DARREICH_ALTERSGER(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf, int IsArtikelVorhanden)
{
	// bei Neuanlage Übernahme 1:1 (leer / 00 --> 0=nein; 01 -> 1=altersgerecht)
	// bei Artikel-Änderung Übernahme nur, wenn Feld über IFA tatsächlich gemeldet

	if (!IsArtikelVorhanden || !IsNoValue(IfaBuf, PL_A02AMDARKI))
	{
		if (strcmp(IfaBuf->A02AMDARKI, "01") == 0)
			Buf->AM_DARREICH_ALTERSGER = 1;
		else
			Buf->AM_DARREICH_ALTERSGER = 0;
	}
}

static void	Make_AM_FESTBETR_AUFGEH(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf, int IsArtikelVorhanden)
{
	// bei Neuanlage Übernahme 1:1 (leer / 00 --> 0=nein; 01 -> 1=Festbetrag aufgehoben)
	// bei Artikel-Änderung Übernahme nur, wenn Feld über IFA tatsächlich gemeldet

	if (!IsArtikelVorhanden || !IsNoValue(IfaBuf, PL_A02AMAUFFB))
	{
		if (strcmp(IfaBuf->A02AMAUFFB, "01") == 0)
			Buf->AM_FESTBETR_AUFGEH = 1;
		else
			Buf->AM_FESTBETR_AUFGEH = 0;
	}
}

static void	Make_AM_KINDER(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf, int IsArtikelVorhanden)
{
	// Arzneimittel fuer Kinder:
	// bei Neuanlage Übernahme 1:1 (leer / 00 --> 0=nein; 01 -> 1=Festbetrag aufgehoben;
	//                                                    02 -> 2=kein Festbetrag)
	// bei Artikel-Änderung Übernahme nur, wenn Feld über IFA tatsächlich gemeldet

	if (!IsArtikelVorhanden || !IsNoValue(IfaBuf, PL_A02AMBEKI))
	{
		if (strcmp(IfaBuf->A02AMBEKI, "02") == 0)
			Buf->AM_KINDER = 2;
		else if (strcmp(IfaBuf->A02AMBEKI, "01") == 0)
			Buf->AM_KINDER = 1;
		else
			Buf->AM_KINDER = 0;
	}
}

static void	Make_AM_VERSKRIT_WIRKSTOFF(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf, int IsArtikelVorhanden)
{
	// Versorgungskritischer Wirkstoff:
	// bei Neuanlage Übernahme 1:1 (leer / 00 --> 0=nein; 01 -> 1=Festbetrag aufgehoben;
	//                                                    02 -> 2=kein Festbetrag)
	// bei Artikel-Änderung Übernahme nur, wenn Feld über IFA tatsächlich gemeldet

	if (!IsArtikelVorhanden || !IsNoValue(IfaBuf, PL_A02AMVEKRW))
	{
		if (strcmp(IfaBuf->A02AMVEKRW, "02") == 0)
			Buf->AM_VERSKRIT_WIRKSTOFF = 2;
		else if (strcmp(IfaBuf->A02AMVEKRW, "01") == 0)
			Buf->AM_VERSKRIT_WIRKSTOFF = 1;
		else
			Buf->AM_VERSKRIT_WIRKSTOFF = 0;
	}
}
/* ------ IFA Version 20244 Ende ------- */

/* ------- IFA Version 20248 ------- */
static void	Make_LAGTEMP_BEACHTEN(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf, int IsArtikelVorhanden)
{
	// bei Neuanlage Uebernahme 1:1 (leer / 00 --> 0=nein; 01 -> 1)
	// bei Artikel-Aenderung Uebernahme nur, wenn Feld über IFA tatsaechlich gemeldet

	if (!IsArtikelVorhanden || !IsNoValue(IfaBuf, PL_A05LGTMPB))
	{
		if (strcmp(IfaBuf->A05LGTMPB, "01") == 0)
			Buf->LAGTEMP_BEACHTEN = 1;
		else
			Buf->LAGTEMP_BEACHTEN = 0;
	}
}

static void	Make_MED_CANNABIS_GES(struct ZARTIKEL* Buf, struct ZIFAART* IfaBuf, int IsArtikelVorhanden,
	                              int *ToStoreAbdaWg, int *ToStoreWg2)
{
	// Cannabis Gesetz:
	// bei Neuanlage Uebernahme 1:1 (leer / 00 --> 0=nein; 01 -> 1=Cannabis med.;
	//                                                     02 -> 2=Cannabis med. wiss.
	// bei Artikel-Aenderung Uebernahme nur, wenn Feld über IFA tatsaechlich gemeldet

	if (!IsArtikelVorhanden || !IsNoValue(IfaBuf, PL_A02MEDCG))
	{
		if (strcmp(IfaBuf->A02MEDCG, "02") == 0)
			Buf->MED_CANNABIS_GES = 2;
		else if (strcmp(IfaBuf->A02MEDCG, "01") == 0)
			Buf->MED_CANNABIS_GES = 1;
		else
			Buf->MED_CANNABIS_GES = 0;

		/* Wenn Neuanlage und A02MEDCG == 01 oder 02 */
		if (!IsArtikelVorhanden &&
			((strcmp(IfaBuf->A02MEDCG, "01") == 0) || (strcmp(IfaBuf->A02MEDCG, "02") == 0)))
		{
			Make_EK_SPERRE(Buf); // Sperre setzen
			strcpy ( Buf->CHARGENARTIKEL, "1" ); // Chargenartikel setzen
			strcpy ( Buf->PSYCHOTROP, "J");      // Psychotrop setzen
			*ToStoreWg2 = 1;                     // Warengruppe 2 setzen

			if (strcmp(IfaBuf->A05VFDAT, "01") != 0) // Verfall und Warengruppe setzen, wenn IFA != 01
			{
				strcpy(Buf->VERFALL, "1");  // Kennzeichen Verfall setzen
				*ToStoreAbdaWg = 6;         // zartwg.art = 4, Warengruppe VDINT
			}
		}
	}
}
/* ------ IFA Version 20248 Ende ------- */

/* ---- IFA-Loeschung ---- */
int GetIsIfaLoeschung( struct ZIFAART *IfaBuf )
{

    return !IsNoValue( IfaBuf, PL_A00LKZ )   && *IfaBuf->A00LKZ   == 'X' ||
           !IsNoValue( IfaBuf, PL_A00SSATZ ) && *IfaBuf->A00SSATZ == '2';
/*
    return !IsNoValue( IfaBuf, PL_A00LKZ )   && *IfaBuf->A00LKZ   == 'X';
*/
}

/* ---- IFA-AH ---- */
int GetIsIfaAH( struct ZIFAART *IfaBuf )
{
    return !IsNoValue( IfaBuf, PL_A03VTSTAT ) &&
           strcmp( IfaBuf->A03VTSTAT,  "00" ) == 0;
}

void IfaSatzToArtikel( struct ZIFAART *IfaBuf, struct ZARTIKEL *Buf, int IsArtikelVorhanden,
	                   int *ToStoreAbdaWg, int *ToStoreSwg1, int *ToStoreSwg2, int *ToStoreWg2)
{
   long datum_gueltig;
   long datum_ah;

   /* Gueltigkeitsdatum */
   datum_gueltig = IfaBuf->DATUMGUELTIGAB;
   if (datum_gueltig > Buf->DATUM_IFAAENDER)
   {
   Buf->DATUM_IFAAENDER = datum_gueltig;
   }
   if ( !IsArtikelVorhanden )
		// Buf->DATUM_ANLAGE = datum_gueltig; // Tagesdatum, da in gültigAb bei Neuanlagen "morgen" steht wegen Preisen !!!
		   Buf->DATUM_ANLAGE = GetPhoDate();
	
   /* Abgabebestimmung */
   Make_ABGABEBEST( Buf, IfaBuf, IsArtikelVorhanden );

   /* Artikel-Nr */
   Buf->ARTIKEL_NR = IfaBuf->A00PZN;

   /* Hersteller-Nr */
   Make_HERSTELLER_NR( Buf, IfaBuf );

   /* Negativliste */
   Make_NEGATIVLISTE( Buf, IfaBuf, IsArtikelVorhanden );

   /* Artikelname */
   Make_ARTIKEL_NAME( Buf, IfaBuf, IsArtikelVorhanden );

   /* Artikellangname */
   Make_LANGNAME( Buf, IfaBuf, IsArtikelVorhanden);

   /* Packung / Einheit */
   Make_EINHEIT( Buf, IfaBuf, IsArtikelVorhanden );

   /* Darreichungsform */
   Make_DARREICHFORM( Buf, IfaBuf, IsArtikelVorhanden );

   /* Preisempfehlung */      /* !! entfaellt */
   strcpy( Buf->PREISEMPFEHLUNG, "0" );

   /* Verfallkennzeichen */
   Make_VERFALL( Buf, IfaBuf, IsArtikelVorhanden );

   /* Klinikpackung */
   Make_KLINIKPACKUNG( Buf, IfaBuf, IsArtikelVorhanden );

   /* Nicht ueber GH */
   Make_NICHTUEBERGH( Buf, IfaBuf, IsArtikelVorhanden );

   /* Nur KVA */
   Make_NURKVA( Buf, IfaBuf );

   /* Apothekenpflichtig */
   Make_APOTHEKENPFL( Buf, IfaBuf );

   /* Betaeubungsmittel */
   Make_BTM( Buf, IfaBuf, IsArtikelVorhanden );

   /* Rezeptpflichtig */
   Make_REZEPTPFL( Buf, IfaBuf, IsArtikelVorhanden );

   /* Taxpflichtig */
   Make_TAXPFL( Buf, IfaBuf, IsArtikelVorhanden );

   /* Nettoartikel  */
   Make_NETTOARTIKEL( Buf, IfaBuf );

   /* Rabattfaehigkeit */
   if ( !IsArtikelVorhanden )
   {
	 if ( *Buf->REZEPTPFL == '1' )		 		
        memcpy( Buf->RABATTFAEHIG, "01", L_ZARTIKEL_RABATTFAEHIG );
     else
        memcpy( Buf->RABATTFAEHIG, "00", L_ZARTIKEL_RABATTFAEHIG );
   }
   
   /* ChargenDoku ( TFG ) */
   Make_TFG( Buf, IfaBuf, IsArtikelVorhanden );

   /* Vertriebsbindung */
   Make_VERTRBIND_IFA( Buf, IfaBuf, IsArtikelVorhanden );

   /* Laufzeit in Monaten */
   Make_LAUFZEITMONATE( Buf, IfaBuf, IsArtikelVorhanden, ToStoreSwg1 );

   /* Kuehlartikel */
   Make_KUEHLARTIKEL( Buf, IfaBuf, IsArtikelVorhanden, ToStoreSwg1 );

   /* Tierarznei */  /* !! warum keine Uebernahme */
   Make_TIERARZNEI( Buf, IfaBuf, IsArtikelVorhanden );

   /* A06PZNNF */
   Make_ERSATZ_NR( Buf, IfaBuf );

   /* Zuzahlung */
   Make_ZUZAHLUNG_IFA( Buf, IfaBuf, IsArtikelVorhanden );

   /* Laenge */
   Make_LAENGE( Buf, IfaBuf, IsArtikelVorhanden );

   /* Breite */
   Make_BREITE( Buf, IfaBuf, IsArtikelVorhanden );

   /* Hoehe  */
   Make_HOEHE( Buf, IfaBuf, IsArtikelVorhanden );

   /* Gewicht */
   Make_GEWICHT( Buf, IfaBuf, IsArtikelVorhanden );

   /* ---- NEM-Artikel ----- 12.09.2001 */
   Make_NemArtikel( Buf, IfaBuf, IsArtikelVorhanden );

  /* ---- ARTIKEL_NR_HERST ----- 26.09.2002 */
   Make_ARTIKEL_NR_HERST( Buf, IfaBuf, IsArtikelVorhanden );

   /* Arzneimittel 12.03.2003 */
   Make_Arzneimittel( Buf, IfaBuf, IsArtikelVorhanden );

   /* Medizinprodukt 12.03.2003 */
   Make_Medizinprodukt( Buf, IfaBuf, IsArtikelVorhanden );

   /* CE-Kennzeichen 12.03.2003 */
   Make_CE( Buf, IfaBuf, IsArtikelVorhanden );

	/* Hilfsmittel zum Verbrauch */
	Make_HilfsmittelVerbrauch( Buf, IfaBuf, IsArtikelVorhanden );

	/* Ausnahme §51 AMG 03.04.06 */
	Make_Amg_Ausnahmereg( Buf, IfaBuf, IsArtikelVorhanden );
	/* Generika AVWG 03.04.06 */
	Make_Zulass_Generika( Buf, IfaBuf, IsArtikelVorhanden );
	/* Abschlag §130a 3b 03.04.06 */
	Make_Abschlag_130( Buf, IfaBuf, IsArtikelVorhanden );
	/* Sicherh.Datenbl.erforderl. */
	Make_Sidablatt( Buf, IfaBuf, IsArtikelVorhanden, ToStoreAbdaWg);
	/* Produktart setzen Pandemie/Standard */
	Make_Produktart( Buf, IfaBuf, IsArtikelVorhanden );
	/* Artikelnummer Originalpzn */
	Make_PznOrig(Buf, IfaBuf,IsArtikelVorhanden);

	Make_HOMOEO(Buf, IfaBuf,IsArtikelVorhanden);
	Make_ANTHRO(Buf, IfaBuf,IsArtikelVorhanden);
	Make_PHYTO(Buf, IfaBuf,IsArtikelVorhanden);
	Make_BIOZID(Buf, IfaBuf,IsArtikelVorhanden, ToStoreAbdaWg);
	Make_KOSMETIKUM(Buf, IfaBuf,IsArtikelVorhanden);
	Make_PSM(Buf, IfaBuf,IsArtikelVorhanden, ToStoreAbdaWg);
	Make_TREZEP(Buf, IfaBuf,IsArtikelVorhanden);
	Make_AMG(Buf, IfaBuf,IsArtikelVorhanden);
	Make_WIRKSTOFF(Buf, IfaBuf);
	Make_ELEKTRO(Buf, IfaBuf, IsArtikelVorhanden, ToStoreAbdaWg);
	//Behandlung Batteriegesetz in Make_ELEKTRO enthalten
	//Make_BATTERIEGESETZ(Buf, IfaBuf, IsArtikelVorhanden, ToStoreAbdaWg); 
	Make_LAGEEMPFL(Buf, IfaBuf);

	Make_BESTELL_NICHT_AUSL(Buf, IfaBuf, IsArtikelVorhanden);

	Make_BSSICHG(Buf, IfaBuf,IsArtikelVorhanden);
	
	// wird ab 2013 wegen historischer Abspeicherung für IVC in zartpreis abgespeichert:
	// Make_ERSTATTBETRAG(Buf, IfaBuf,IsArtikelVorhanden);

	Make_PPN(Buf, IfaBuf);
	Make_Abschlag_130a2(Buf, IfaBuf);
	Make_Pilot_SecurPharm(Buf, IfaBuf);
	Make_Abgabeverbot_52b(Buf, IfaBuf);
	Make_Biosiegel(Buf, IfaBuf, IsArtikelVorhanden, ToStoreSwg2);
	Make_Steril(Buf, IfaBuf);
	Make_EXPLOSIV(Buf, IfaBuf, IsArtikelVorhanden);
	Make_BIOTECH(Buf, IfaBuf, IsArtikelVorhanden);
	Make_SONST_WUNDPRODUKT(Buf, IfaBuf);
	Make_AUSNAHME_ABSCHLAGPFLICHT(Buf, IfaBuf);
	Make_NOVEL_FOOD(Buf, IfaBuf, IsArtikelVorhanden, ToStoreAbdaWg);
	Make_UNNR(Buf, IfaBuf, IsArtikelVorhanden);
	Make_DATUM_FMDPFLICHT(Buf, IfaBuf, IsArtikelVorhanden);
	Make_AM_NEUART_THERAPIE(Buf, IfaBuf, IsArtikelVorhanden);
	Make_ORPHANDRUG(Buf, IfaBuf);
	Make_BEDINGTZULASSUNG(Buf, IfaBuf);
	Make_ZULASSUNGAUSNAHMEFAELLE(Buf, IfaBuf);
	Make_AMNOGVERFAHREN(Buf, IfaBuf);
	Make_ZULASSUNGSINHABERNR(Buf, IfaBuf);
	Make_OERTLICHEVERTRETERNR(Buf, IfaBuf);
//	Make_SERIAL_NO_TRACKING(Buf, IfaBuf);

	/* ------- IFA Version 20244 -------- */
	Make_AM_DARREICH_ALTERSGER(Buf, IfaBuf, IsArtikelVorhanden);
	Make_AM_FESTBETR_AUFGEH(Buf, IfaBuf, IsArtikelVorhanden);
	Make_AM_KINDER(Buf, IfaBuf, IsArtikelVorhanden);
	Make_AM_VERSKRIT_WIRKSTOFF(Buf, IfaBuf, IsArtikelVorhanden);

	/* ------- IFA Version 20248 -------- */
	Make_LAGTEMP_BEACHTEN(Buf, IfaBuf, IsArtikelVorhanden);
	Make_MED_CANNABIS_GES(Buf, IfaBuf, IsArtikelVorhanden, ToStoreAbdaWg, ToStoreWg2);

    /* Datums-Eintraege */
   datum_ah = 0;
   Buf->DATUM_RR = 0;
   Buf->DATUM_IFALOESCH = 0;

   /* Datum Rueckruf */
   Make_DATUM_RR( Buf, IfaBuf, datum_gueltig );

  /* Datum AH / Retourensperre */
  // Nur wenn Datum AH noch nicht gesetzt ist, ansonsten darf der Wert nicht mehr geändert werden.
   if ( GetIsIfaAH( IfaBuf ) && datum_ah == 0 )
      datum_ah = datum_gueltig;
   else
      datum_ah = 0;

   if ( IsArtikelVorhanden )
   {
      if ( Buf->DATUM_AH == 0 || datum_ah > 0 )
      {
          if ( Buf->DATUM_AH == 0 && datum_ah > 0 )
             strcpy( Buf->RETOURENSPERRE, "1" );
		  if (Buf->DATUM_AH == 0)
		  {
			  // Datum AH nur übernehmen, wenn der Artikel nicht schon Außerhandel gesetzt wurde
			  Buf->DATUM_AH = datum_ah;
          }
       }
   }
   else
   {
      if ( datum_ah > 0 )
          strcpy( Buf->RETOURENSPERRE, "1" );
      Buf->DATUM_AH = datum_ah;
   }

   /* Loeschdatum */
   if ( GetIsIfaLoeschung( IfaBuf ) )
   {
      Buf->DATUM_IFALOESCH = datum_gueltig;
   }
   else
      Buf->DATUM_IFALOESCH = 0;  /* Loeschdatum ruecksetzen */

   /* gegebenenfalls AH_DATUM / BTM / ZZ an Artikel haengen */
   ChangeArtikelName( Buf );
}

/* ---- Preise --------------------- */

int HasPreisAValue( struct ZIFAART *IfaBuf )
{
   if ( !IsNoValue( IfaBuf, PL_A01GEPDM ) &&
        !IsNoValue( IfaBuf, PL_A01AEPDM ) &&
        !IsNoValue( IfaBuf, PL_A01AVPDM ) &&
		// !IsNoValue( IfaBuf, PL_A01SERSTAT ) && /* ab 01.04.2014 wird kein Erstattungsbetrag mehr geliefert! */
		// !IsNoValue( IfaBuf, PL_A02RESERV1 ) &&
		!IsNoValue( IfaBuf, PL_A02EB130B ) &&
        !IsNoValue( IfaBuf, PL_A01UVP   )    )    /* EAVP */
        return 1;
   else
        return 0;
}

void IfaSatzToPreis( struct ZIFAART *IfaBuf, struct ZARTPREIS *Buf,
                     int IsArtikelVorhanden )
{
   Buf->ARTIKEL_NR = IfaBuf->A00PZN;
   Buf->GROSSO = IfaBuf->GROSSO;
   Buf->AEP    = IfaBuf->AEP;
   Buf->AVP    = IfaBuf->AVP;
   Buf->EAVP   = IfaBuf->EAVP;
   // Buf->ERSTATTBETRAG = IfaBuf->A01ERSTATT; /* ab 01.04.2014 wird kein Erstattungsbetrag mehr geliefert! */
   Buf->DATUMGUELTIGAB = IfaBuf->DATUMGUELTIGAB;

   //if ( strcmp( IfaBuf->A02RESERV1, "01" ) == 0 )
   if ( strcmp( IfaBuf->A02EB130B, "01" ) == 0 )
	   Buf->DISC_DEDUCED_YET = 1;
   else if (strcmp(IfaBuf->A02EB130B, "02") == 0)
	   Buf->DISC_DEDUCED_YET = 2;
   else if (strcmp(IfaBuf->A02EB130B, "03") == 0)
	   Buf->DISC_DEDUCED_YET = 3;
   else
	   Buf->DISC_DEDUCED_YET = 0;

   /* !!!!!!!!!!!!!!!!!! pruefen !!!!!!!!!!!!!!!!!!! */
   CpyMwst( Buf->KE_MWST, IfaBuf->A01MWST, IsArtikelVorhanden );

   /* -------- In Abh. von A02EB130B Pricemodel setzen (IFA Version 20244) ------- */
   if (strcmp(IfaBuf->A02EB130B, "02") == 0)
   {
	   if (strcmp(IfaBuf->A02PRSTRMO, "01") == 0)
		   Buf->PRICEMODEL = 1;
	   else if (strcmp(IfaBuf->A02PRSTRMO, "02") == 0)
		   Buf->PRICEMODEL = 2;
	   else if (strcmp(IfaBuf->A02PRSTRMO, "03") == 0)
		   Buf->PRICEMODEL = 3;
	   else
		   Buf->PRICEMODEL = 0;
   }
   else
	   Buf->PRICEMODEL = 0;
}

int HasArtPriceExtAValue( struct ZIFAART *IfaBuf )
{
   if ( !IsNoValue( IfaBuf, PL_A01PPU ) ||
        !IsNoValue( IfaBuf, PL_A01APU783A ) ||
        !IsNoValue( IfaBuf, PL_A01AEPPPU ) ||
		!IsNoValue( IfaBuf, PL_A01AVPPPU   )    )  
        return 1;
   else
        return 0;
}

void IfaSatzToArtPriceExt( struct ZIFAART *IfaBuf, struct CARTPRICEEXT *Buf )
{
   Buf->ARTICLENO = IfaBuf->A00PZN;
   Buf->DATEVALIDFROM = IfaBuf->DATUMGUELTIGAB;
	
   if ( !IsNoValue( IfaBuf, PL_A01AEPPPU ) )
		Buf->A01AEPPPU = IfaBuf->A01AEPPPU;

   if ( !IsNoValue( IfaBuf, PL_A01APU783A ) )
		Buf->A01APU783A = IfaBuf->A01APU783A;

   if ( !IsNoValue( IfaBuf, PL_A01AVPPPU ) )
		Buf->A01AVPPPU = IfaBuf->A01AVPPPU;

   if ( !IsNoValue( IfaBuf, PL_A01PPU ) )
		Buf->A01PPU = IfaBuf->A01PPU;
}

/* ---- EAN --------------------- */

/* 04.03.99 -> IFA fuert 0000000000000 ein */
int TestEanNr( char *ean )
{
  int i;

  /* keine EAN, wenn nur 0 oder blank */
  i = 0;
  while ( ean[i] && ( ean[i] == ' ' || ean[i] == '0' ) ) i++;
  if ( ean[i] == '\0' )
    return 0;

  i = 0;
  while ( ean[i] && ean[i] >= '0' && ean[i] <= '9' ) i++;
  if ( ean[i] == '\0' )
    return  1;     /* EAN-Nr korrekt */
  else
    return -1;     /* EAN-Nr falsch */
}

int HasEanAValue( struct ZIFAART *IfaBuf )
{
   return !IsNoValue( IfaBuf, PL_A00EAN );
}

void IfaSatzToEan ( struct ZIFAART *IfaBuf, struct EAN *Buf,
                    int IsArtikelVorhanden )
{
   Buf->ARTIKEL_NR = IfaBuf->A00PZN;
   if ( !IsNoValue( IfaBuf, PL_A00EAN ) &&
        TestEanNr( IfaBuf->A00EAN ) == 1   )
      strcpy( Buf->EAN_NR, IfaBuf->A00EAN );
   else
   {
      memset( Buf->EAN_NR, ' ', L_EAN_EAN_NR );
      Buf->EAN_NR[L_EAN_EAN_NR] = '\0';
   }
}
