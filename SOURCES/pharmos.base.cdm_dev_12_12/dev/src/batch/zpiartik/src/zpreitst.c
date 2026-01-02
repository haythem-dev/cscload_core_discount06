/* ---------------------------------------------------------------------- *
 *                            ZPREITST.C                                  *
 * ---------------------------------------------------------------------- *
 * Aufgabe        : Preistest nach Peetz                                  *
 * ---------------------------------------------------------------------- *
 * Autor          : Schmitt                                               *
 * erstellt am    : 11.07.98                                              *
 * letztes Update :                                                       *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <zifaart.h>
#include "znb_gen.h"
#include "l_taxtab.h"

/* --- Taxartikel ----- */

static char GetTaxKenn( struct ZIFAART *ifa )
{
	if ( strcmp( ifa->A01AMPVAMG, "01" ) == 0 )
	{
		if ( strcmp( ifa->A02TIERAM, "01" ) == 0 )
			return '1';
		else
			return '2';     /* '1'; */
	}
	if ( strcmp( ifa->A01AMPVSGB, "01" ) == 0 )
		return '1';     /* '2'; */
    return '0';
}


static int IsIfaTaxArtikel( struct ZIFAART *ifa )
{
	return GetTaxKenn( ifa ) != '0';
}

/* --- Nettoartikel --- */

int IsIfaNettoArtikel( struct ZIFAART *ifa )
{

   return ( (strcmp( ifa->A01AMPVAMG, "00" ) == 0 && strcmp( ifa->A01AMPVSGB, "00" ) == 0)  ||
	        (strcmp( ifa->A01AMPVAMG, "00" ) == 0 && strcmp( ifa->A01AMPVSGB, "  " ) == 0)  ||
		   	(strcmp( ifa->A01AMPVAMG, "  " ) == 0 && strcmp( ifa->A01AMPVSGB, "00" ) == 0)     
          ) 
		  &&
          ( strcmp( ifa->A02APPFL, "00" ) == 0 || strcmp( ifa->A02APPFL, "  " ) == 0 );
}

/* --- GH - Artikel --- */

static int IsIfaUeberGh( struct ZIFAART *ifa )
{
/* return *ifa->VERTR_WEG == '0';  */
   return strcmp( ifa->A03VWGGH, "01" ) == 0;
}

/* --- Ist Grosso gleich Null --- */

static int IsIfaGrossoNull( struct ZIFAART *ifa )
{
    return ifa->A01GEPDM >= -0.005 && ifa->A01GEPDM <= 0.005;
}


/* --- IfaPreisAenderung --- */

static int IsIfaPreisAenderung( struct ZIFAART *ifa )
{
   return *ifa->A01SGEPDM == '4' || *ifa->A01SGEPDM == '5' ||
          *ifa->A01SAEPDM == '4' || *ifa->A01SAEPDM == '5' ||
          *ifa->A01SAVPDM == '4' || *ifa->A01SAVPDM == '5' ||
          *ifa->A01SUVP   == '4' || *ifa->A01SUVP   == '5';
}


static int TestIfaPreisAenderung( struct ZIFAART *ifa,
                                  long ifa_gro, long ifa_aep, long ifa_avp, long ifa_eavp,
                                  long art_gro, long art_aep, long art_avp, long art_eavp )
{
  if ( !IsIfaPreisAenderung( ifa ) &&
       ( ifa_gro != art_gro || ifa_aep != art_aep || ifa_avp != art_avp || ifa_eavp != art_eavp )
      )
  {
    SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_PRDIFF_OHNE_KEY );
    return 0;
  }
  return 1;
}

/* ------------------ Taxartikel  -------------------- */

static int IsIfaAepNachTaxe( struct ZIFAART *ifa ) 
{
   double diff;
   double aep;
   char tax_kz;

   /* keine AEP- Taxprüfung wenn AEP == GEP oder NGH- Artikel
   diff = ifa->AEP - ifa->GROSSO;
   if ( (diff > -0.005 && diff < 0.005) || !IsIfaUeberGh( ifa )) 
	   return 1;
   */

   // keine AEP- Taxprüfung wenn NGH- Artikel
   if ( !IsIfaUeberGh( ifa )) 
	   return 1;

   tax_kz = GetTaxKenn( ifa );

   CalcAek( ifa->GROSSO, &aep, ifa->DATUMGUELTIGAB, tax_kz );
   diff = ifa->AEP - aep;
   
   if ( diff < -0.005 || diff > 0.005 ) 
   {
	   /* ab 2012 wieder entfernt, da es taxpfl = 3 dann nicht mehr gibt (war nur AMNOG- Übergangsjahr 2011)
	   if (tax_kz == '2') // wenn Prüfung mit taxkz = 2 falsch, dann nochmal mit TaxKz = 3 versuchen
	   {
	       tax_kz = '3';
		   CalcAek( ifa->GROSSO, &aep, ifa->DATUMGUELTIGAB, tax_kz );
		   diff = ifa->AEP - aep;
		   
		   if ( diff < -0.005 || diff > 0.005 ) 
			   return 0;
	   }
	   else */
          return 0;
   }
   
   return 1;
}

static int IsIfaAvpNachTaxe( struct ZIFAART *ifa )
{
   int mwst;
   double diff;
   double avp;

   if ( strcmp( ifa->A01MWST, "01" ) == 0  )        /* Vermindert */
      mwst = TAXTAB_IS_VERMMWST;
   else if ( strcmp( ifa->A01MWST, "02" ) == 0 )    /* Ohne */
      mwst = TAXTAB_IS_OHNEMWST;
   else                                             /* Voll */
      mwst = TAXTAB_IS_VOLLMWST;
   CalcAvkMwst( ifa->AEP, &avp, mwst, ifa->DATUMGUELTIGAB, GetTaxKenn( ifa ) );
   diff = ifa->AVP - avp;
   if ( diff < -0.005 || diff > 0.005 ) return 0;
   return 1;
}

/* ------ Taxartikel -------------------- */

static int TestTaxArtikel( struct ZIFAART *ifa,
                           int IsArtGrossoNull, int IsTaxPruefGrosso )
{
	if ( IsTaxPruefGrosso )
	SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_TAXPRUEFGROSSO );

  if ( ! IsIfaGrossoNull( ifa ) )  /* IFA-Grosso != 0 */
  {
    if ( ! IsIfaAepNachTaxe( ifa ) || !IsIfaAvpNachTaxe( ifa ) )
    {
      SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_TAXPRUEF );
      return 0;
    }
  }
  else   /* IFA-Grosso = 0 */
  {
    if ( IsIfaUeberGh( ifa ) || !IsIfaAvpNachTaxe( ifa ) )
    {
      SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_TAXPRUEF );
      if ( !IsArtGrossoNull )
        SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_GEP_AUF_NULL );
      return 0;
    }

    if ( !IsArtGrossoNull )
    {
      SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_GEP_AUF_NULL );
      return 0;
    }

  }
  return 1;
}

static int TestTaxArtikelNeu( struct ZIFAART *ifa ) 
{
  if ( ! IsIfaGrossoNull( ifa ) )
  {
    if ( ! IsIfaAepNachTaxe( ifa ) || !IsIfaAvpNachTaxe( ifa ) )
    {
      SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_TAXPRUEF );
      return 0;
    }
  }
  else
  {
    if ( IsIfaUeberGh( ifa ) || !IsIfaAvpNachTaxe( ifa ) )
    {
      SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_TAXPRUEF );
      return 0;
    }
  }
  return 1;
}


/* --------------- Nichttaxartikel ------------------------- */

/* --- folgende Faelle sind eventuell richtig --- */
/*     grosso   aep    avp         Status        Fall  */
/*       0       0      0       event. richtig    1    */
/*       0       0      3       event. richtig    1    */
/*       0       2      0       event. richtig    2    */
/*       0       2      3       event. richtig    2    */
/*       1       0      0       event. richtig    3    */
/*       1       0      3       event. richtig    3    */
/*       1       2      0       immer  richtig    4    */
/*       1       2      3       immer  richtig    4    */


#define PREISE_BEDOK1 1
#define PREISE_BEDOK2 2
#define PREISE_BEDOK3 3
#define PREISE_OK     4
#define PREISE_NOTOK  0

static int GetIfaPreisFall( long gro, long aep, long avp, struct ZIFAART *ifa )
{
   if ( gro == 0 )
   {
     if ( aep == 0 && avp == 0     ) return PREISE_BEDOK1;
     if ( aep == 0 && avp >= 0     ) return PREISE_BEDOK1;
     if ( aep >  0 && avp == 0     ) return PREISE_BEDOK2;
     if ( aep >  0 && avp >  aep   ) return PREISE_BEDOK2;
   }
   else
   {
     if ( aep == 0 && avp == 0     ) return PREISE_BEDOK3;
     if ( aep == 0 && avp >  gro   ) return PREISE_BEDOK3;

     if ( aep >  gro && avp == 0   ) return PREISE_OK;
     if ( aep >  gro && avp > aep  ) return PREISE_OK;

	 // Für alle NGH- Artikel darf ab 2011 AEP == GEP sein !
	 if ( !IsIfaUeberGh( ifa )) 
	 {
		 if ( aep == gro && avp == 0   ) return PREISE_OK;
		 if ( aep == gro && avp > aep  ) return PREISE_OK;
	 }
	 
   }
   return PREISE_NOTOK;
}

static int TestFallNichtTaxNichtNetto( int IfaPreisFall, struct ZIFAART *ifa,
                                       long a_gro, long a_aep, long a_avp )
{
   /*  0  0  0   */
   /*  0  0  3   */
   if ( IfaPreisFall == PREISE_BEDOK1 )
   {
      if ( a_gro == 0 && a_aep == 0 ) return 1;
      if ( a_gro >  0  )
         SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_GEP_AUF_NULL );
      if ( a_aep >  0 )
         SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_AEP_AUF_NULL );
      return 0;
   }

   /*  0  2  0    */
   /*  0  2  3    */
   else if ( IfaPreisFall == PREISE_BEDOK2 )
   {
/*    if ( a_gro > 0 ) return 1;  */
      if ( a_gro == 0 ) return 1;       /* !!!!! neu !!!! */
      SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_GEP_AUF_NULL );
      return 0;
   }
   /*  1  0  0    */
   /*  1  0  3    */
   else    /* PREISE_BEDOK3 */
   {
      SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_PREISPRUEF );
      return 0;
   }
}

static int TestFallNetto( int IfaPreisFall, struct ZIFAART *ifa,
                          long a_gro, long a_aep, long a_avp, long prozPM  )
{
   /*  0  0  0   */
   /*  0  0  3   */
   if ( IfaPreisFall == PREISE_BEDOK1 )
   {
      if ( a_gro == 0 && a_aep == 0 ) return 1;
      if ( a_gro >  0  )
         SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_GEP_AUF_NULL );
      if ( a_aep >  0 )
         SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_AEP_AUF_NULL );
      return 0;
   }

   /*  0  2  0    */
   /*  0  2  3    */
   else if ( IfaPreisFall == PREISE_BEDOK2 )
   {
      if ( a_gro == 0 ) return 1;       /* !!!!! neu !!!! */
      if ( a_gro > 0 && a_aep > 0 )
      {
         if ( prozPM < 0 ) return 3;    /* ok */
         SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_GEP_AUF_NULL );
         if ( prozPM == 0 )
            SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_PROZ_PLUS_MINUS );
         else
            SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_PROZ_PLUS );
      }
      else
        SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_PREISPRUEF );
      return 0;
    }
   /*  1  0  0    */
   /*  1  0  3    */
   else      /* PREISE_BEDOK3 */
   {
      if ( a_gro > 0 && a_aep > 0 )
      {
         if ( prozPM > 0 ) return 2;  /* ok */

         SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_AEP_AUF_NULL );
         if ( prozPM == 0 )
           SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_PROZ_PLUS_MINUS );
         else
           SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_PROZ_MINUS );
      }
      else
        SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_PREISPRUEF );
      return 0;
   }
}


static int FehlerNurIfa( struct ZIFAART *ifa, long gro, long aep, long avp,
						 long art_gro, long art_aep, long art_avp, long ProzentPM )
{
   if ( gro > 0 )
   {
     if ( aep == gro ) 
     {
        if ( avp == gro )
           SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_AVP_GR_AEP );
        
		// wenn im aktuellen zartpreis bereits gep == aep ODER zartikel.herst_prozent < 0 vorhanden, 
		// dann nur nicht zwingender Fehler
		if ( art_aep == art_gro )
			SetIfaTrueFalse( 1, ifa->NB_NZWING, NZ_AEP_EQ_GR_UEBN );
		else if ( ProzentPM < 0 )
			SetIfaTrueFalse( 1, ifa->NB_NZWING, NZ_AEP_EQ_GR_CALC );
		else if (IsIfaUeberGh( ifa ))
			SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_AEP_GR_GEP );
	
		return 0;
     }
     if ( aep > gro && avp <= aep && avp > 0 )
     {
        SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_AVP_GR_AEP );
        return 0;
     }
   }
   return 1;
}


/* ---- Netto-Artikel --- */

static int TestNettoArtikel( struct ZIFAART *ifa,
                             long ifa_gro, long ifa_aep, long ifa_avp,
                             long art_gro, long art_aep, long art_avp,
                             long ProzentPM )
{
   int fall;
   int s;

   if ( FehlerNurIfa( ifa, ifa_gro, ifa_aep, ifa_avp, 
							art_gro, art_aep, art_avp, ProzentPM ) == 0 ) 
		return 0;

   fall = GetIfaPreisFall( ifa_gro, ifa_aep, ifa_avp, ifa );

   if ( fall == PREISE_OK )  
	   return 1;

   if ( fall == PREISE_NOTOK )
   {
      SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_PREISPRUEF );
      return 0;
   }

   /* weiterTesten */
   s = TestFallNetto( fall, ifa, art_gro, art_aep, art_avp, ProzentPM );

   return s;
}


/* ---- Nicht Tax- und nicht Netto-Artikel --- */

static
int TestNichtTaxNichtNettoArtikel( struct ZIFAART *ifa,
                                   long ifa_gro, long ifa_aep, long ifa_avp,
                                   long art_gro, long art_aep, long art_avp )
{
   int fall;
   int s;

   fall = GetIfaPreisFall( ifa_gro, ifa_aep, ifa_avp, ifa );
   if ( fall == PREISE_OK )  return 1;
   if ( fall == PREISE_NOTOK )
   {
      SetIfaTrueFalse( 1, ifa->NB_ZWING, ZW_PREISPRUEF );
      return 0;
   }

   /* weiterTesten */
   s = TestFallNichtTaxNichtNetto( fall, ifa, art_gro, art_aep, art_avp );

   return s;
}


void KaufmRunden( double *wert, int stellen );

static long PreisAusProzent ( long l_preis, long l_proz )
{
  double preis;
  double proz;
  double wert;

  proz  = (double) l_proz  / 100.0;
  preis = (double) l_preis / 100.0;

  wert = preis*proz/100.0;

  wert += preis;
  KaufmRunden( &wert, 2);

  return (long)( wert*100.0 + 0.1 );
 }

/* ---- global ------------------------- */

void TestIfaPreisMeldung( struct ZIFAART *ifa, double herstProz ) // CR-270 aus 03/2012
{
	if ( ifa->A01GEPDM	<   0.005	&&				// IFA liefert Grosso = 0
		 herstProz		<= -0.005		)			// herst_prozent < 0 
	{
		return; // --> Grosso wird errechnet = kein NZWING notwendig!
	}

	SetIfaTrueFalse( ((*ifa->A01SGEPDM == '4' || *ifa->A01SGEPDM == '5') && *ifa->A01SAEPDM == ' ') || 
					 ((*ifa->A01SAEPDM == '4' || *ifa->A01SAEPDM == '5') && *ifa->A01SGEPDM == ' '),
					ifa->NB_NZWING, NZ_PREISE_GROSSO_AEP );
}


int TestPreis_Aenderung( struct ZIFAART *ifa,
                         int IsTaxPruefGrosso, long ProzentPM,
                         long ifa_gro, long ifa_aep, long ifa_avp, long ifa_eavp,
                         long art_gro, long art_aep, long art_avp, long art_eavp )
{
  int s;

  int IsArtGrossoNull;

  IsArtGrossoNull = art_gro == 0;

  if ( IsIfaTaxArtikel( ifa ) )
  {
    s = TestTaxArtikel( ifa, IsArtGrossoNull, IsTaxPruefGrosso );
  }
  else if ( IsIfaNettoArtikel( ifa ) )
  {
    s = TestNettoArtikel ( ifa,
                           ifa_gro, ifa_aep, ifa_avp,
                           art_gro, art_aep, art_avp,
                           ProzentPM );

/*  Hier Preise aus Prozent berechnen */
    if ( s == 2 )  /* ok : prozPM > 0 */
    {
      ifa_aep = PreisAusProzent ( ifa_gro, ProzentPM );
      s = 1;
    }
    else if ( s == 3 /* ok : prozPM < 0 */ || 
			  (ifa_gro == ifa_aep && ProzentPM < 0)	)  
    {
      ifa_gro = PreisAusProzent ( ifa_aep, ProzentPM );
      s = 1;
    }

  }
  else
  {
    s = TestNichtTaxNichtNettoArtikel( ifa,
                                       ifa_gro, ifa_aep, ifa_avp,
                                       art_gro, art_aep, art_avp );
  }

  /* Test, zu grosse Preisabweichung */
  /* 20 % vom AEP nach oben oder nach unten */
  // if ( s == 1 ) // --> immer, nicht nur wenn vorher alles OK war! 
  {
     if ( art_aep > 0 && ifa_aep > 0 &&
          ( 10*ifa_aep < 8*art_aep || 10*ifa_aep > 12*art_aep ) )
        SetIfaTrueFalse( 1, ifa->NB_NZWING, NZ_PRDIFF );
  }

  /* Test, ob bei unterschiedlichen Preisen IFA-Preisaenderung gesetzt */
/*
  if ( s == 1 )
    s = TestIfaPreisAenderung( ifa,
                               ifa_gro, ifa_aep, ifa_avp,
                               art_gro, art_aep, art_avp );
*/
  if ( s == 1 )
  {
	if ( *ifa->A00SSATZ != '0' )	/* Test nur wenn keine Bestandslieferung (16.12.2004) */
		s = TestIfaPreisAenderung( ifa,
			                       ifa_gro, ifa_aep, ifa_avp, ifa_eavp,
				                   art_gro, art_aep, art_avp, art_eavp );
  }

  return s;
}


int TestPreis_Neuaufnahme( struct ZIFAART *ifa )
{
  if ( IsIfaTaxArtikel( ifa ) )
     return TestTaxArtikelNeu( ifa );
  else   /* keine Pruefung bei NichtTaxartikeln */
     return 1;
}

