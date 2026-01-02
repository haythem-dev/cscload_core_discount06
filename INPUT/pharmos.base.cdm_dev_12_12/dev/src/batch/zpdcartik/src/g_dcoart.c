/* ---------------------------------------------------------------------- *
 * Aufgabe        : Funktionalität zur Interaktion mit der Datenbank      *
 * ---------------------------------------------------------------------- *
 * Autor          : Hörath                                               *
 * erstellt am    : 26.01.2005                                            *
 * ---------------------------------------------------------------------- */
/* --------- Includes -------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include <hdatum/phodate.h>

#include <voodoo_table_header/zdcoart.h>
#include <voodoo_table_header/zdcart.h>

#include "dc_form.h"
#include "znb_gen_dc.h"
#include "g_dcoart.h"


/* ---------------------------------------------------------------------- */
void ze_lcpy( char *s1, char ze, int lng )
{
  while ( lng-- > 0 ) *s1++ = ze;
   *s1 = '\0';
}

/* ---------------------------------------------------------------------- */
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

/* --- FehlerFelder initialisieren --- */
static char  NB_PLAUSI[ POSANZ_ZDCOART + 1 + POSANZ_UNUSED];
/* ---------------------------------------------------------------------- */
static void ClearNbPlausi( int pos )
{
   NB_PLAUSI[ pos ] = NB_PL_OK;
}

/* ---------------------------------------------------------------------- */
static void InitNbPlausi( )
{
   int i;

	ze_lcpy( NB_PLAUSI, '1', POSANZ_ZDCOART + 1 + POSANZ_UNUSED );
   ClearNbPlausi( PL_PZN );
   ClearNbPlausi( PL_DATERSTANL );
   ClearNbPlausi( PL_DATLETZTAEND );
   
   /* letzte 20 Stellen auf 9 setzen!? - werden noch nicht benötigt!*/
   for (i = POSANZ_ZDCOART + 1; i <= POSANZ_ZDCOART + 1 + POSANZ_UNUSED; i++)
   {
		NB_PLAUSI[ i ] = NB_PL_NO_VAL;
   }

   /* nicht mehr existierende Felder */
   NB_PLAUSI[ PL_GRPHERSTOEKO ] = NB_PL_NO_VAL;
   NB_PLAUSI[ PL_KZOEKO ] = NB_PL_NO_VAL;
   NB_PLAUSI[ PL_SORTINGRP ] = NB_PL_NO_VAL;
   NB_PLAUSI[ PL_PARTNERNR ] = NB_PL_NO_VAL;
   NB_PLAUSI[ PL_REFERENZNR ] = NB_PL_NO_VAL;
   NB_PLAUSI[ PL_THERAPIEGRP ] = NB_PL_NO_VAL;
}

/* ---------- Test DC auf "Keine Aenderung" ---------------------------- */
static int TestNoChangeC( char *DCwert, char *Owert, int pos )
{
   if ( strcmp(DCwert,Owert) == 0 )
   {
     NB_PLAUSI[ pos ] = NB_PL_NO_VAL;
     return 1;
   }
   NB_PLAUSI[ pos ] = NB_PL_OK;
   return 0;
}

static int TestNoChangeL( long DCwert, long Owert, int pos )
{
   if ( DCwert == Owert )
   {
     NB_PLAUSI[ pos ] = NB_PL_NO_VAL;
     return 1;
   }
   NB_PLAUSI[ pos ] = NB_PL_OK;
   return 0;
}

static int TestNoChangeD( double DCwert, double Owert, int pos )
{
   long lDC = (long)(DCwert * 100);
   long lO = (long)(Owert * 100);
	
   if ( lDC == lO )
   {
     NB_PLAUSI[ pos ] = NB_PL_NO_VAL;
     return 1;
   }
   NB_PLAUSI[ pos ] = NB_PL_OK;
   return 0;
}

/* ---------- Referenz auf Plausistring ---------------------------- */
void CopyPlausi( char *NB_PLAUSI_Zdcart )
{
   int i;
   i = 0;
   while ( NB_PLAUSI_Zdcart[i] != '\0' )
   {
     NB_PLAUSI_Zdcart[ i ] = NB_PLAUSI[ i ];
     i++;
   }
}

/* ---------- erste 15 Stellen des Artikeltextes geändert? ----------- */
static int iArtText15Changed = 0;
int IsChangeArtText15 ()
{
	return iArtText15Changed;
}

/* ---------------------------------------------------------------------- */
int DCOartFill( struct ZDCOART *dco, struct ZDCART *dc, long tages_datum, char* errmld )
{
	char *wert;
	long lwert;
	double dwert;
   long datum;
   
   /* --- FehlerFelder initialisieren --- */
   InitNbPlausi( );
   iArtText15Changed = 0;

   /* --- Datum bestimmen ---- */
   datum = dc->DC_DATUMGUELTIGAB;
   if (!(TestPhoDate(datum))) 
	   datum = 0; 
   /* wenn kein Datum vorhanden, dann datum = tagesdatum */
   if ( datum == 0 )
        datum = tages_datum;
   dco->DC_DATUMGUELTIGAB = datum;
   ClearNbPlausi( PL_DATGUELTAB );

   /* ---- auf Aenderungen prüfen ------ */
	/* Artikelkurztext */
   if ( ( wert = dc->DC_ARTIKELKURZTEXT) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ARTIKELKURZTEXT, PL_ARTKURZTXT ) )
	   str_lcpy( dco->DC_ARTIKELKURZTEXT, wert, L_ZDCOART_DC_ARTIKELKURZTEXT );

   /* Artikeltext */
   if ( ( wert = dc->DC_ARTIKELTEXT) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ARTIKELTEXT, PL_ARTTXT ) )
   {
	   // Test, ob erste 15 Stellen geändert für ZW_WRGRP_ARTBEZ
		char arttext15dc[17], arttext15dco[17];
		ze_lcpy( arttext15dc, '0', 16 );
		ze_lcpy( arttext15dco, '0', 16 );
  
		strncpy( arttext15dc, dc->DC_ARTIKELTEXT, 15 );
		strncpy( arttext15dco, dco->DC_ARTIKELTEXT, 15 );
		if ( strcmp(arttext15dc,arttext15dco) != 0 )
		{
			iArtText15Changed = 1;
		}

		str_lcpy( dco->DC_ARTIKELTEXT, wert, L_ZDCOART_DC_ARTIKELTEXT );
   }
   
	/* Artikeltext - Menge */
   if ( ( wert = dc->DC_EINH_MENGE) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_EINH_MENGE, PL_ARTMENGE ) )
         str_lcpy( dco->DC_EINH_MENGE, wert, L_ZDCOART_DC_EINH_MENGE );

   /* Artikeltext - Einheit */
   if ( ( wert = dc->DC_EINH_EINHEIT) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_EINH_EINHEIT, PL_ARTEINHEIT ) )
         str_lcpy( dco->DC_EINH_EINHEIT, wert, L_ZDCOART_DC_EINH_EINHEIT );

   /* KZ - Taxe */
   if ( ( wert = dc->DC_TAXKZ) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_TAXKZ, PL_KZTAXE ) )
   {
         str_lcpy( dco->DC_TAXKZ, wert, L_ZDCOART_DC_TAXKZ );

		 // zwingenden Fehler für Änderung nur setzen, wenn nicht "E" !!! (siehe Mail: 21.01.08)
		 if ( strcmp (dco->DC_TAXKZ, "E") != 0 ) 
			SetDCTrueFalse(1, dc->NB_DC_ZWING, ZW_AEND_BOX_TAX);
   }

    /* KZ - ApoVerlag */
   if ( ( wert = dc->DC_ARTIKELKZ) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ARTIKELKZ, PL_KZAPOVERL ) )
         str_lcpy( dco->DC_ARTIKELKZ, wert, L_ZDCOART_DC_ARTIKELKZ );

    /* Rezeptzeichen */
   if ( ( wert = dc->DC_REZEPTZEICHEN) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_REZEPTZEICHEN, PL_ZREZEPT ) )
         str_lcpy( dco->DC_REZEPTZEICHEN, wert, L_ZDCOART_DC_REZEPTZEICHEN );

   /* Kassenzeichen */
   if ( ( wert = dc->DC_KASSENZEICHEN) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_KASSENZEICHEN, PL_ZKASSE ) )
         str_lcpy( dco->DC_KASSENZEICHEN, wert, L_ZDCOART_DC_KASSENZEICHEN );

    /* Kassenzeichen - Zusatz */
   if ( ( wert = dc->DC_KASSENZ_ZUSATZ) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_KASSENZ_ZUSATZ, PL_ZKASSEZUS ) )
         str_lcpy( dco->DC_KASSENZ_ZUSATZ, wert, L_ZDCOART_DC_KASSENZ_ZUSATZ );

    /* Codein */
   if ( ( wert = dc->DC_CODEIN) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_CODEIN, PL_KZCODEIN ) )
         str_lcpy( dco->DC_CODEIN, wert, L_ZDCOART_DC_CODEIN );

    /* GEP */
   dwert = dc->DC_GEP;
   if ( !TestNoChangeD( dwert, dco->DC_GEP, PL_GEP ) )
         dco->DC_GEP = dwert;

      /* AEP */
   dwert = dc->DC_AEP;
   if ( !TestNoChangeD( dwert, dco->DC_AEP, PL_AEP ) )
         dco->DC_AEP = dwert;

      /* KKP */
   dwert = dc->DC_KKP;
   if ( !TestNoChangeD( dwert, dco->DC_KKP, PL_KKP ) )
         dco->DC_KKP = dwert;

      /* AVP */
   dwert = dc->DC_AVP;
   if ( !TestNoChangeD( dwert, dco->DC_AVP, PL_AVP ) )
         dco->DC_AVP = dwert;

  /* KZ ohne Preisbescheid */
   if ( ( wert = dc->DC_OHNE_PREISBESCH) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_OHNE_PREISBESCH, PL_KZOHNEPRBESCH ) )
         str_lcpy( dco->DC_OHNE_PREISBESCH, wert, L_ZDCOART_DC_OHNE_PREISBESCH );

    /* MWST Grosshandel */
   if ( ( wert = dc->DC_MWST_GH) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_MWST_GH, PL_MWSTCODEGR ) )
   {
	   str_lcpy( dco->DC_MWST_GH, wert, L_ZDCOART_DC_MWST_GH );
   
	   // zwingender Fehler für Änderung auf 3. Mwst (13%)
		if ( strcmp (dco->DC_MWST_GH, "3") == 0 ) 
			SetDCTrueFalse(1, dc->NB_DC_ZWING, ZW_TO_MWST_3RD);
   }

    /* MWST Apotheke */
   if ( ( wert = dc->DC_MWST_AP) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_MWST_AP, PL_MWSTCODEAPO ) )
         str_lcpy( dco->DC_MWST_AP, wert, L_ZDCOART_DC_MWST_AP );

   /* Charge */
   if ( ( wert = dc->DC_CHARGE) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_CHARGE, PL_CHARGE ) )
         str_lcpy( dco->DC_CHARGE, wert, L_ZDCOART_DC_CHARGE );

    /* Fäschungssicherheit */
	lwert = dc->DC_FAELSCHSICHER;
	if( !TestNoChangeL( lwert, dco->DC_FAELSCHSICHER, PL_FAELSCHSICHER ) )
		dco->DC_FAELSCHSICHER = (short)lwert;

   /*Biosiegel*/
	lwert = dc->DC_BIOSIEGEL;
	if( !TestNoChangeL( lwert, dco->DC_BIOSIEGEL, PL_BIOSIEGEL ) )
		dco->DC_BIOSIEGEL = (short)lwert;

   /* Antibiotikum */
	lwert = dc->DC_ANTIBIOTIKUM;
	if( !TestNoChangeL( lwert, dco->DC_ANTIBIOTIKUM, PL_ANTIBIOTIKUM ) )
		dco->DC_ANTIBIOTIKUM = (short)lwert;

	/* verminderte Rezeptgebühr */
   if ( ( wert = dc->DC_VERM_REZ_GEB) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_VERM_REZ_GEB, PL_KZVERMREZGEB ) )
         str_lcpy( dco->DC_VERM_REZ_GEB, wert, L_ZDCOART_DC_VERM_REZ_GEB );

     /* Lieferanten-Code */
   if ( ( wert = dc->DC_CODE_LIEFERANT) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_CODE_LIEFERANT, PL_LIEFERANT ) )
   {
         str_lcpy( dco->DC_CODE_LIEFERANT, wert, L_ZDCOART_DC_CODE_LIEFERANT );
		 SetDCTrueFalse(1, dc->NB_DC_NZWING, NZ_AEND_LIEF_HERST); 
   }

      /* Lieferanten-Artikelnr */
   if ( ( wert = dc->DC_ARTNR_LIEFERANT) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ARTNR_LIEFERANT, PL_LIEFARTNR ) )
         str_lcpy( dco->DC_ARTNR_LIEFERANT, wert, L_ZDCOART_DC_ARTNR_LIEFERANT );

      /* Lieferanten-Artikelnr */
   if ( ( wert = dc->DC_DEFEKTUR_LISTE) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_DEFEKTUR_LISTE, PL_DEFEKTUR ) )
         str_lcpy( dco->DC_DEFEKTUR_LISTE, wert, L_ZDCOART_DC_DEFEKTUR_LISTE );

       /* Mindestabnahme */
   lwert = dc->DC_MINDESTABNAHME;
   if ( !TestNoChangeL( lwert, dco->DC_MINDESTABNAHME, PL_MINDABN ) )
         dco->DC_MINDESTABNAHME = (short)lwert;

     /* nicht verfügbar lt. Verlag */
   if ( ( wert = dc->DC_NV_WV) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_NV_WV, PL_KZNVERFVERL ) )
         str_lcpy( dco->DC_NV_WV, wert, L_ZDCOART_DC_NV_WV );

    /* nicht verfügbar lt. Grosshandel */
   if ( ( wert = dc->DC_NV_GH) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_NV_GH, PL_KZNVERFGR ) )
         str_lcpy( dco->DC_NV_GH, wert, L_ZDCOART_DC_NV_GH );

        /* Hoehe */
   lwert = dc->DC_HOEHE;
   if ( !TestNoChangeL( lwert, dco->DC_HOEHE, PL_HOEHE ) )
         dco->DC_HOEHE = (short)lwert;

        /* Breite */
   lwert = dc->DC_BREITE;
   if ( !TestNoChangeL( lwert, dco->DC_BREITE, PL_BREITE ) )
         dco->DC_BREITE = (short)lwert;

     /* Tiefe */
   lwert = dc->DC_TIEFE;
   if ( !TestNoChangeL( lwert, dco->DC_TIEFE, PL_TIEFE ) )
         dco->DC_TIEFE = (short)lwert;

     /* Lagerhinweis */
   if ( ( wert = dc->DC_LAGERHINWEIS) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_LAGERHINWEIS, PL_LAGERHINW ) )
         str_lcpy( dco->DC_LAGERHINWEIS, wert, L_ZDCOART_DC_LAGERHINWEIS );

       /* Gefahrensymbol */
   if ( ( wert = dc->DC_GEFAHRENSYMBOL) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_GEFAHRENSYMBOL, PL_GEFAHRHINW ) )
         str_lcpy( dco->DC_GEFAHRENSYMBOL, wert, L_ZDCOART_DC_GEFAHRENSYMBOL );

       /* Ablauf - KZ */
   if ( ( wert = dc->DC_KZ_ABLAUF) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_KZ_ABLAUF, PL_KZABLAUF ) )
         str_lcpy( dco->DC_KZ_ABLAUF, wert, L_ZDCOART_DC_KZ_ABLAUF );

	 /* apo-pflichtig - KZ */
   if ( ( wert = dc->DC_APO_PFLICHTIG) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_APO_PFLICHTIG, PL_KZAPOPFL ) )
         str_lcpy( dco->DC_APO_PFLICHTIG, wert, L_ZDCOART_DC_APO_PFLICHTIG );

  	 /* Registernummer */
   if ( ( wert = dc->DC_REGISTER_NR) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_REGISTER_NR, PL_REGNR ) )
         str_lcpy( dco->DC_REGISTER_NR, wert, L_ZDCOART_DC_REGISTER_NR );

	/* Therapiegruppe */
   if ( ( wert = dc->DC_THERAPIEGRUPPE) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_THERAPIEGRUPPE, PL_THERAPIEGRP ) )
         str_lcpy( dco->DC_THERAPIEGRUPPE, wert, L_ZDCOART_DC_THERAPIEGRUPPE );

   	/* Artikelgruppe */
   if ( ( wert = dc->DC_ARTIKELGRUPPE) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ARTIKELGRUPPE, PL_ARTGRP ) )
         str_lcpy( dco->DC_ARTIKELGRUPPE, wert, L_ZDCOART_DC_ARTIKELGRUPPE );

      	/* KZ Minikarten - Basissatz */
   if ( ( wert = dc->DC_MINIK_BASISS) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_MINIK_BASISS, PL_KZMINIBASIS ) )
         str_lcpy( dco->DC_MINIK_BASISS, wert, L_ZDCOART_DC_MINIK_BASISS );

	/* Herstellercode */
   if ( ( wert = dc->DC_CODE_HERSTELLER) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_CODE_HERSTELLER, PL_HERSTCODE ) )
   {
         str_lcpy( dco->DC_CODE_HERSTELLER, wert, L_ZDCOART_DC_CODE_HERSTELLER );
		SetDCTrueFalse(1, dc->NB_DC_NZWING, NZ_AEND_LIEF_HERST); 
   }

    /* Gewicht */
   lwert = dc->DC_GEWICHT;
   if ( !TestNoChangeL( lwert, dco->DC_GEWICHT, PL_GEWICHT ) )
         dco->DC_GEWICHT = lwert;

	/* Oekogruppe Hauptverband 
   if ( ( wert = dc->DC_OELHV_GRUPPE) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_OELHV_GRUPPE, PL_GRPHERSTOEKO ) )
         str_lcpy( dco->DC_OELHV_GRUPPE, wert, L_ZDCOART_DC_OELHV_GRUPPE );
	*/

   	/* Oeko - KZ 
   if ( ( wert = dc->DC_OELHV_OEKOKZ) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_OELHV_OEKOKZ, PL_KZOEKO ) )
         str_lcpy( dco->DC_OELHV_OEKOKZ, wert, L_ZDCOART_DC_OELHV_OEKOKZ );
	*/

   /* KZ Generikum */
   if ( ( wert = dc->DC_GENERIKUM) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_GENERIKUM, PL_GENERIKUM ) )
         str_lcpy( dco->DC_GENERIKUM, wert, L_ZDCOART_DC_GENERIKUM );

   /* KZ Originalprodukt */
   if ( ( wert = dc->DC_ORIGINALPRODUKT) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ORIGINALPRODUKT, PL_ORIGINALPROD ) )
         str_lcpy( dco->DC_ORIGINALPRODUKT, wert, L_ZDCOART_DC_ORIGINALPRODUKT );

   /* KZ Arzneimittel */
   if ( ( wert = dc->DC_ARZNEIMITTEL) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ARZNEIMITTEL, PL_ARZNEIMITTEL ) )
         str_lcpy( dco->DC_ARZNEIMITTEL, wert, L_ZDCOART_DC_ARZNEIMITTEL );

   /* KZ Abgrenzungsverordnung */
   if ( ( wert = dc->DC_ABGRENZ_VERORD) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ABGRENZ_VERORD, PL_ABGR_VERORD ) )
         str_lcpy( dco->DC_ABGRENZ_VERORD, wert, L_ZDCOART_DC_ABGRENZ_VERORD );

   /* KZ Suchtgift Zubereitung */
   if ( ( wert = dc->DC_SG_ZUBEREITUNG) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_SG_ZUBEREITUNG, PL_SG_ZUB ) )
         str_lcpy( dco->DC_SG_ZUBEREITUNG, wert, L_ZDCOART_DC_SG_ZUBEREITUNG );

   /* KZ Suchtgift Substanz */
   if ( ( wert = dc->DC_SG_SUBSTANZ) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_SG_SUBSTANZ, PL_SG_SUBSTANZ ) )
         str_lcpy( dco->DC_SG_SUBSTANZ, wert, L_ZDCOART_DC_SG_SUBSTANZ );
   
   /* Abgabebeschraenkung */
   if ( ( wert = dc->DC_ABGABEBES) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ABGABEBES, PL_KZ_ABGBESCHR ) )
         str_lcpy( dco->DC_ABGABEBES, wert, L_ZDCOART_DC_ABGABEBES );

	/* KZ verkehrsfaehig */
   if ( ( wert = dc->DC_VERKEHRSFAEHIG) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_VERKEHRSFAEHIG, PL_KZVERKEHR ) )
         str_lcpy( dco->DC_VERKEHRSFAEHIG, wert, L_ZDCOART_DC_VERKEHRSFAEHIG );

	/* KKP HausApo*/
   dwert = dc->DC_KKP_HAUSAPO;
   if ( !TestNoChangeD( dwert, dco->DC_KKP_HAUSAPO, PL_KKPHAUSAPO ) )
         dco->DC_KKP_HAUSAPO = dwert;

   	/* Herkunftsland */
   if ( ( wert = dc->DC_HERKUNFTSLAND) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_HERKUNFTSLAND, PL_HERKUNFT ) )
         str_lcpy( dco->DC_HERKUNFTSLAND, wert, L_ZDCOART_DC_HERKUNFTSLAND );

  	/* Oeko-Sortierung 
   if ( ( wert = dc->DC_OELHV_SORT) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_OELHV_SORT, PL_SORTINGRP ) )
         str_lcpy( dco->DC_OELHV_SORT, wert, L_ZDCOART_DC_OELHV_SORT );
	*/

   /* KZ Drogenausgangsstoff Kat 1 */
   if ( ( wert = dc->DC_DROGENAGS_KAT1) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_DROGENAGS_KAT1, PL_DROGAGS_KAT1 ) )
         str_lcpy( dco->DC_DROGENAGS_KAT1, wert, L_ZDCOART_DC_DROGENAGS_KAT1 );
 
   /* KZ  Drogenausgangsstoff Kat 2 */
   if ( ( wert = dc->DC_DROGENAGS_KAT2) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_DROGENAGS_KAT2, PL_DROGAGS_KAT2 ) )
         str_lcpy( dco->DC_DROGENAGS_KAT2, wert, L_ZDCOART_DC_DROGENAGS_KAT2 );
 
   /* KZ  Drogenausgangsstoff Kat 3 */
   if ( ( wert = dc->DC_DROGENAGS_KAT3) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_DROGENAGS_KAT3, PL_DROGAGS_KAT3 ) )
         str_lcpy( dco->DC_DROGENAGS_KAT3, wert, L_ZDCOART_DC_DROGENAGS_KAT3 );
 
   /* KZ Blutkonserve / Gewebe */
   if ( ( wert = dc->DC_BLUTKONSERVE) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_BLUTKONSERVE, PL_BLUTKONSERVE ) )
         str_lcpy( dco->DC_BLUTKONSERVE, wert, L_ZDCOART_DC_BLUTKONSERVE );
 
	/* Box-KZ */
   if ( ( wert = dc->DC_HV_BOX) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_HV_BOX, PL_BOXERSTATT ) )
   {
        str_lcpy( dco->DC_HV_BOX, wert, L_ZDCOART_DC_HV_BOX );
		SetDCTrueFalse(1, dc->NB_DC_ZWING, ZW_AEND_BOX_TAX);
   }
   	/* Darreichform */
   if ( ( wert = dc->DC_DARREICHFORM) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_DARREICHFORM, PL_DAR ) )
         str_lcpy( dco->DC_DARREICHFORM, wert, L_ZDCOART_DC_DARREICHFORM );

	/* laufende Nummer */
   lwert = dc->DC_LFD_NR;
   if ( !TestNoChangeL( lwert, dco->DC_LFD_NR, PL_AUSLIEFVERS ) )
         dco->DC_LFD_NR = lwert;

	/* Kennung Neuanleger */
   if ( ( wert = dc->DC_NEUANLEGER) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_NEUANLEGER, PL_NEUANLEGER ) )
         str_lcpy( dco->DC_NEUANLEGER, wert, L_ZDCOART_DC_NEUANLEGER );

   	/* Partner-Nr 
   if ( ( wert = dc->DC_PARTNER) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_PARTNER, PL_PARTNERNR ) )
         str_lcpy( dco->DC_PARTNER, wert, L_ZDCOART_DC_PARTNER );
	 */

    /* Referenz-Nr 
   if ( ( wert = dc->DC_REFERENZ_NR) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_REFERENZ_NR, PL_REFERENZNR ) )
         str_lcpy( dco->DC_REFERENZ_NR, wert, L_ZDCOART_DC_REFERENZ_NR );
	*/

   	/* KZ radioaktives Arzneimittel */
   if ( ( wert = dc->DC_RADIOAKT_ARZNEI) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_RADIOAKT_ARZNEI, PL_RADIOAKT_ARZNEI ) )
         str_lcpy( dco->DC_RADIOAKT_ARZNEI, wert, L_ZDCOART_DC_RADIOAKT_ARZNEI );

   	/* KZ Fütterungs- Arzneimittel */
   if ( ( wert = dc->DC_FUETTER_ARZNEI) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_FUETTER_ARZNEI, PL_FUETTER_ARZNEI ) )
         str_lcpy( dco->DC_FUETTER_ARZNEI, wert, L_ZDCOART_DC_FUETTER_ARZNEI );

   	/* KZ Arzneimittel andere Gewerbetreibende */
   if ( ( wert = dc->DC_ARZNEI_GEWERBE) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ARZNEI_GEWERBE, PL_ARZNEI_GEWERBE ) )
         str_lcpy( dco->DC_ARZNEI_GEWERBE, wert, L_ZDCOART_DC_ARZNEI_GEWERBE );

   	/* KZ Dental- Arzneimittel */
   if ( ( wert = dc->DC_DENTALARZNEI) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_DENTALARZNEI, PL_DENTALARZNEI ) )
         str_lcpy( dco->DC_DENTALARZNEI, wert, L_ZDCOART_DC_DENTALARZNEI );

   	/* KZ medizinisches Gas */
   if ( ( wert = dc->DC_MEDIZIN_GAS) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_MEDIZIN_GAS, PL_MEDIZIN_GAS ) )
         str_lcpy( dco->DC_MEDIZIN_GAS, wert, L_ZDCOART_DC_MEDIZIN_GAS );

   	/* KZ Kontaktlinsenflüssigkeit */
   if ( ( wert = dc->DC_KONTAKTLINSENFL) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_KONTAKTLINSENFL, PL_KONTAKTLINSENFL ) )
         str_lcpy( dco->DC_KONTAKTLINSENFL, wert, L_ZDCOART_DC_KONTAKTLINSENFL );

   	/* KZ Alkohol unversteuert */
   if ( ( wert = dc->DC_ALK_UNVERST) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ALK_UNVERST, PL_ALK_UNVERST ) )
         str_lcpy( dco->DC_ALK_UNVERST, wert, L_ZDCOART_DC_ALK_UNVERST );

   	/* KZ Alkohol vergällt */
   if ( ( wert = dc->DC_ALK_VERGAELLT) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ALK_VERGAELLT, PL_ALK_VERGAELLT ) )
         str_lcpy( dco->DC_ALK_VERGAELLT, wert, L_ZDCOART_DC_ALK_VERGAELLT );

   	/* KZ Gift */
   if ( ( wert = dc->DC_GIFT) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_GIFT, PL_GIFT ) )
         str_lcpy( dco->DC_GIFT, wert, L_ZDCOART_DC_GIFT );

   	/* KZ Zytostatikum */
   if ( ( wert = dc->DC_ZYTOSTATIKUM) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ZYTOSTATIKUM, PL_ZYTOSTATIKUM ) )
         str_lcpy( dco->DC_ZYTOSTATIKUM, wert, L_ZDCOART_DC_ZYTOSTATIKUM );

   	
   /* KZ Pflanzenschutz */
   if ( ( wert = dc->DC_PFLANZENSCHUTZ) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_PFLANZENSCHUTZ, PL_PFLANZENSCH ) )
         str_lcpy( dco->DC_PFLANZENSCHUTZ, wert, L_ZDCOART_DC_PFLANZENSCHUTZ );

   	/* KZ Medizinprodukt Abgabeverordnung */
   if ( ( wert = dc->DC_MEDPROD_ABGABEV) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_MEDPROD_ABGABEV, PL_MEDPROD_ABGVO ) )
         str_lcpy( dco->DC_MEDPROD_ABGABEV, wert, L_ZDCOART_DC_MEDPROD_ABGABEV );

   	/* KZ Medizinprodukt Klassifizierung */
   if ( ( wert = dc->DC_MEDPROD_KLASSE) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_MEDPROD_KLASSE, PL_MEDPROD_KLASS ) )
         str_lcpy( dco->DC_MEDPROD_KLASSE, wert, L_ZDCOART_DC_MEDPROD_KLASSE );

   	/* KZ Artikelgruppe lt. Verordnung */
   if ( ( wert = dc->DC_ARTGRP_LTVERORD) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ARTGRP_LTVERORD, PL_ARTGRP_LTVO ) )
         str_lcpy( dco->DC_ARTGRP_LTVERORD, wert, L_ZDCOART_DC_ARTGRP_LTVERORD );


	/* nicht ueber Grosshandel */
   if ( ( wert = dc->DC_NICHTUEBERGH) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_NICHTUEBERGH, PL_KZNGR ) )
         str_lcpy( dco->DC_NICHTUEBERGH, wert, L_ZDCOART_DC_NICHTUEBERGH );

   	/* Warengruppe */
   if ( ( wert = dc->DC_WARENGRUPPE) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_WARENGRUPPE, PL_WGRPAPOVERL ) )
         str_lcpy( dco->DC_WARENGRUPPE, wert, L_ZDCOART_DC_WARENGRUPPE );

	/* Artikelbez. 2.Zeile */
   if ( ( wert = dc->DC_ABEZ_ZEILE2) == NULL ) return 1;
   if ( !TestNoChangeC( wert, dco->DC_ABEZ_ZEILE2, PL_ARTBEZ2 ) )
         str_lcpy( dco->DC_ABEZ_ZEILE2, wert, L_ZDCOART_DC_ABEZ_ZEILE2 );

   	/* UN-Nummer */
   if ( ( wert = dc->DC_UN_NR) == NULL ) return 1;
	if ( !TestNoChangeC( wert, dco->DC_UN_NR, PL_UNNR ) )
         str_lcpy( dco->DC_UN_NR, wert, L_ZDCOART_DC_UN_NR );


	return 0;
}
