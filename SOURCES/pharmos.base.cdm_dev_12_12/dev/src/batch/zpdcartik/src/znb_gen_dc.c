/* ---------------------------------------------------------------------- *
 *   Aufgabe        : generiert die Nachbearbeitungsgruende               *
 *                    bei Datacare-Aenderungen                            *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 31.01.2005                                          *
 *   Autor          : Hörath                                              *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <hdatum/phodate.h>

#include "znb_gen_dc.h"

/* ------------------------------------------------------------------- */
struct ERR_MeldungDC PL_MeldungDC[] =
{
	{PL_PZN	, "PZN: Prüfziffer falsch"},
	{PL_ARTKURZTXT	, "allgemeiner Plausi-Fehler"},
	{PL_ARTTXT	, "allgemeiner Plausi-Fehler"},
	{PL_ARTMENGE	, "Einheit-Menge nicht numerisch"},
	{PL_ARTEINHEIT	, "allgemeiner Plausi-Fehler"},
	{PL_KZTAXE	, "ungültiger Wert für Tax-Kennzeichen"},
	{PL_KZAPOVERL	, "ungültiger Wert für Artikel-Kennzeichen"},
	{PL_ZREZEPT	, "allgemeiner Plausi-Fehler"},
	{PL_ZKASSE	, "allgemeiner Plausi-Fehler"},
	{PL_ZKASSEZUS	, "allgemeiner Plausi-Fehler"},
	{PL_KZCODEIN	, "ungültiger Wert für Codein-Kennzeichen"},
	{PL_GEP	, "GEP nicht numerisch"},
	{PL_AEP	, "AEP nicht numerisch"},
	{PL_KKP	, "KKP nicht numerisch"},
	{PL_AVP	, "AVP nicht numerisch"},
	{PL_KZOHNEPRBESCH	, "ungültiger Wert für Codein-Kennzeichen"},
	{PL_MWSTCODEGR	, "ungültiger Wert für MwstCode-Grosshandel"},
	{PL_MWSTCODEAPO	, "ungültiger Wert für MwstCode-Apotheke"},
	{PL_CHARGE	, "ungültiger Wert für Charge-Kennzeichen"},
	{PL_KZVERMREZGEB	, "ungültiger Wert für verm. Rezeptgebühr-Kennzeichen"},
	{PL_LIEFERANT	, "allgemeiner Plausi-Fehler"},
	{PL_LIEFARTNR	, "allgemeiner Plausi-Fehler"},
	{PL_DEFEKTUR	, "allgemeiner Plausi-Fehler"},
	{PL_MINDABN	, "Mindestabnahme-Menge nicht numerisch"},
	{PL_KZNVERFVERL	, "ungültiger Wert für nicht verfügbar-Kennzeichen Verlag-Warenverzeichnis"},
	{PL_KZNVERFGR	, "ungültiger Wert für nicht verfügbar-Kennzeichen Grosshandel"},
	{PL_HOEHE	, "Höhe nicht numerisch"},
	{PL_BREITE	, "Breite nicht numerisch"},
	{PL_TIEFE	, "Tiefe nicht numerisch"},
	{PL_LAGERHINW	, "ungültiger Wert für Lagerhinweis-Kennzeichen"},
	{PL_GEFAHRHINW	, "allgemeiner Plausi-Fehler"},
	{PL_KZABLAUF	, "ungültiger Wert für Ablauf-Kennzeichen"},
	{PL_KZAPOPFL	, "ungültiger Wert für Kennzeichen apothekenpflichtiger Artikel"},
	{PL_REGNR	, "Registernummer nicht numerisch"},
	{PL_THERAPIEGRP	, "Therapiegruppe nicht numerisch"},
	{PL_ARTGRP	, "ungültiger Wert für Artikelgruppe"},
	{PL_KZMINIBASIS	, "ungültiger Wert für Minikarten-Kennzeichen"},
	{PL_AENDERCODE	, "ungültiger Wert für Änderungs-Code"},
	{PL_HERSTCODE	, "allgemeiner Plausi-Fehler"},
	{PL_GEWICHT	, "Gewicht nicht numerisch"},
	{PL_GRPHERSTOEKO	, "allgemeiner Plausi-Fehler"},
	{PL_KZOEKO	, "ungültiger Wert für Ökonomie-Kennzeichen"},
	{PL_KZ_ABGBESCHR	, "ungültiger Wert für Abgabebeschränkung-Kennzeichen"},
	{PL_KZVERKEHR	, "ungültiger Wert für Verkehrsfähig-Kennzeichen"},
	{PL_KKPHAUSAPO	, "KKP-Hausapotheke nicht numerisch"},
	{PL_HERKUNFT	, "allgemeiner Plausi-Fehler"},
	{PL_SORTINGRP	, "allgemeiner Plausi-Fehler"},
	{PL_BOXERSTATT	, "ungültiger Wert für Box-Kennzeichen"},
	{PL_DAR	, "allgemeiner Plausi-Fehler"},
	{PL_DATERSTANL	, "Erstanlage-Datum nicht numerisch"},
	{PL_DATLETZTAEND	, "Datum letzte Änderung nicht numerisch"},
	{PL_DATGUELTAB	, "Gültigkeits-Datum nicht numerisch"},
	{PL_AUSLIEFVERS	, "Auslieferungsversion nicht numerisch"},
	{PL_NEUANLEGER	, "allgemeiner Plausi-Fehler"},
	{PL_PARTNERNR	, "allgemeiner Plausi-Fehler"},
	{PL_REFERENZNR	, "allgemeiner Plausi-Fehler"},
	{PL_KZNGR	, "allgemeiner Plausi-Fehler"},
	{PL_WGRPAPOVERL	, "ungültiger Wert für Kennzeichen nicht über Grosshandel"},
	{PL_ARTBEZ2	, "allgemeiner Plausi-Fehler"},
	{PL_UNNR	, "allgemeiner Plausi-Fehler"},

	{PL_GENERIKUM		, "allgemeiner Plausi-Fehler"},
	{PL_ORIGINALPROD	, "allgemeiner Plausi-Fehler"},
	{PL_ARZNEIMITTEL	, "ungültiger Wert für KZ Arzneimittel"},
	{PL_ABGR_VERORD		, "ungültiger Wert für KZ Abgrenzungsverordnung"},
	{PL_SG_ZUB			, "ungültiger Wert für KZ Suchtgift Zubereitung"},
	{PL_SG_SUBSTANZ		, "ungültiger Wert für KZ Suchtgift Substanz"},
	{PL_DROGAGS_KAT1	, "ungültiger Wert für KZ Drogenausgangsstoff Kat 1"},
	{PL_DROGAGS_KAT2	, "ungültiger Wert für KZ Drogenausgangsstoff Kat 2"},
	{PL_DROGAGS_KAT3	, "ungültiger Wert für KZ Drogenausgangsstoff Kat 3"},
	{PL_BLUTKONSERVE	, "ungültiger Wert für KZ Blutkonserve / Gewebe"},
	{PL_RADIOAKT_ARZNEI	, "ungültiger Wert für KZ radioaktives Arzneimittel"},
	{PL_FUETTER_ARZNEI	, "ungültiger Wert für KZ Fütterungs- Arzneimittel"},
	{PL_ARZNEI_GEWERBE	, "ungültiger Wert für KZ Arzneimittel andere Gewerbetreibende"},
	{PL_DENTALARZNEI	, "ungültiger Wert für KZ Dental- Arzneimittel"},
	{PL_MEDIZIN_GAS		, "ungültiger Wert für KZ medizinisches Gas"},
	{PL_KONTAKTLINSENFL	, "ungültiger Wert für KZ Kontaktlinsenflüssigkeit"},
	{PL_ALK_UNVERST		, "ungültiger Wert für KZ Alkohol unversteuert"},
	{PL_ALK_VERGAELLT	, "ungültiger Wert für KZ Alkohol vergällt"},
	{PL_GIFT			, "ungültiger Wert für KZ Gift"},
	{PL_ZYTOSTATIKUM	, "ungültiger Wert für KZ Zytostatikum"},

	{PL_PFLANZENSCH		, "ungültiger Wert für KZ Pflanzenschutzmittel"},
	{PL_MEDPROD_ABGVO	, "ungültiger Wert für KZ Medizinprodukt - Zuordnung Abgabeverordnung"},
	{PL_MEDPROD_KLASS	, "ungültiger Wert für KZ Medizinprodukt - Klassifizierung"},
	{PL_ARTGRP_LTVO		, "ungültiger Wert für KZ Artikelgruppe lt. Verordnung"},
	{PL_BIOSIEGEL		, "ungültiger Wert für Biosiegel"},
	{PL_ANTIBIOTIKUM	, "ungültiger Wert für Antibiotikum"},
	{PL_FAELSCHSICHER	, "ungültiger Wert für Faelschungssicherheit"},
	
};

/* ------------------------------------------------------------------- */
struct ERR_MeldungDC ZW_MeldungDC[] =
{
	  {ZW_GEP_GR_AEP	, "GEP größer 0 und größer AEP"},
	  {ZW_AEP_GEP_0		, "AEP und GEP gleich 0 und nicht beide im Artikelstamm gefüllt"},
	  {ZW_GEP_ERR		, "Änderung Artikelstamm-Grosso auf 0"},
	  {ZW_WRGRP_ARTBEZ	, "Warengruppe 01*** und Änderung Artikelbez. 1-15"},
	  {ZW_AEND_BOX_TAX	, "Box- oder Tax-Kennzeichen geändert"},
	  {ZW_PREISE_TAX_BOX, "Preise bei Taxprüfung entsprechen nicht dem Box-KZ"},
	  {ZW_PREISE_TAX_WRGRP,"Preise bei Taxprüfung entsprechen nicht der Warengruppe"},
	  {ZW_BOX_N0_TAX_N1	, "Box-KZ gefüllt und Tax-KZ nicht 1 / L / E oder 2 (bei Box = N)"},
	  {ZW_AEP_ERR		, "Änderung Artikelstamm-AEP auf 0"},
	  {ZW_GEP_HERSTPROZ	, "Grosso kann nicht berechnet werden, % = +"},
	  {ZW_AEP_HERSTPROZ	, "AEP kann nicht berechnet werden, % = -"},
	  {ZW_SONDERGROSSO	, "Achtung Sondergrosso-Preis"},
	  {ZW_MEDIZIN_PROD	, "Achtung Medizinprodukt-Felder unplausibel"},
	  {ZW_WRGRP_UNBEKANNT,"Warengruppe unbekannt!"},
	  {ZW_TO_MWST_3RD	, "Änderung auf Mwst 13%"},
	  
};

/* ------------------------------------------------------------------- */
struct ERR_MeldungDC NZ_MeldungDC[] =
{
	{NZ_REAKTIV	,		"Änderungscode Reaktivierung"},
	{NZ_AEP_GEP_0	,	"AEP und GEP gleich 0, im Artikelstamm beide gefüllt"},
	{NZ_GEP_HINW,		"Artikelstamm-Grosso bleibt auf 0"},
	{NZ_AEND_LIEF_HERST,"Änderung von Lieferanten- oder Herstellercode"},
	{NZ_AEND_WRGRP	,	"autom. generierte Änderung im Feld Warengruppe"},
	{NZ_ART_AUSS_HANDEL,"Artikel bekommt Außer-Handel-Datum"},
	{NZ_AEP_HINW	,   "Artikelstamm-AEP bleibt auf 0"},
	{NZ_AH_PRICE_CHANGE,"Preisänderung bei AH-Artikel"},
	{NZ_WRGRP_HOCHPREIS,"Hochpreis- Warengruppe wurde automatisch gesetzt"},
	{NZ_WRGRP_HOCHPREIS_ENTFERNT,"Hochpreis- Warengruppe wurde automatisch entfernt"},
	{NZ_AEND_SKONTOFAEHIG,"Änderung der Skontofähigkeit"},	
};

/* ------------------------------------------------------------------- */
char *GetDCErrMeld( struct ERR_MeldungDC *err, int key )
{
  int i;
  i = 0;
  
  while ( err[i].key != NO_WERT && err[i].key != key ) 
	  i++;

  if ( err[i].key == key )
    return err[i].meldung;
  else
    return "";
}

/* ------------------------------------------------------------------- */
char *Get_ZW_ErrMeldDC( int key )
{
  return GetDCErrMeld( ZW_MeldungDC, key );
}

/* ------------------------------------------------------------------- */
char *Get_NZ_ErrMeldDC( int key )
{
  return GetDCErrMeld( NZ_MeldungDC, key );
}

/* ------------------------------------------------------------------- */
char *Get_PL_ErrMeldDC( int key )
{
  return GetDCErrMeld( PL_MeldungDC, key );
}

/* ------------------------------------------------------------------- */
void SetDCTrueFalse( int true_false, char *Feld, int key )
{
   if ( Feld[key] != NB_PL_NO_VAL )
      Feld[key] = ( true_false ? NB_PL_ERR : NB_PL_OK );
}

/* ------------------------------------------------------------------- */
void SetDCErr( char* Wert, char *ZulWerte, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     int i;
     i = 0;
     while ( ZulWerte[i] && ZulWerte[i] != *Wert ) i++;
     Feld[key] = ( ZulWerte[i] ? NB_PL_OK : NB_PL_ERR );
  }
}

/* ------------------------------------------------------------------- */
void SetDC2Err( char* Wert, char *ZulWerte, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     int i;
     i = 0;
     while ( ZulWerte[i] && memcmp( &ZulWerte[i], Wert, 2 ) != 0 ) i += 2;
     Feld[key] = ( ZulWerte[i] ? NB_PL_OK : NB_PL_ERR );
  }
}

/* ------------------------------------------------------------------- */
void SetDCNumErr( long Wert, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     if (  Wert >= 0 )
        Feld[key] = NB_PL_OK;
     else
        Feld[key] = NB_PL_ERR;
  }
}

/* ------------------------------------------------------------------- */
void SetDCPdmErr( double Wert, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
/*   if (  Wert >= 0 )  */
     if (  Wert > -0.0001 )  
        Feld[key] = NB_PL_OK;
     else
        Feld[key] = NB_PL_ERR;
  }
}

/* ------------------------------------------------------------------- */
void SetDCNumBlankErr( char* Wert, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     int i;
     i = 0;
     while ( Wert[i] && (Wert[i]>='0' && Wert[i]<='9' || Wert[i]==' ' || Wert[i]==',') ) i++;
     Feld[key] = ( Wert[i] ? NB_PL_ERR : NB_PL_OK );
  }
}

/* ------------------------------------------------------------------- */
void SetDCGroesser( double Wert1, double Wert2, char *Feld, int key )
{
  if ( Wert1 >= Wert2 )
     Feld[key] = NB_PL_ERR;
   else
     Feld[key] = NB_PL_OK;
}

/* ------------------------------------------------------------------- */
int IsDCFeldErr( char *Feld, int key )
{
	if ( Feld[key] == NB_PL_OK )
		return 0;
	
	if ( Feld[key] == NB_PL_NO_VAL )
		return 0;

	return 1;
}

/* ------------------------------------------------------------------- */
int IsDCErr( char *Feld )
{
    int i;
    i = 0;

	while ( Feld[i] && ( Feld[i] == NB_PL_NO_VAL || Feld[i] == '0' ) ) 
		i++;
    return (char) (Feld[i] ? 1 : 0 );
}

/* ------------------------------------------------------------------- */
void SetDCGueltigabErr( long datum, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     if (  datum == 0 )
        Feld[key] = NB_PL_ERR;
     else
        Feld[key] = NB_PL_OK;
  }
}

/* ------------------------------------------------------------------- */
void SetDCGleich( char* Wert1, char* Wert2, char *Feld, int key )
{
  if ( strcmp( Wert1, Wert2 ) == 0 )
     Feld[key] = NB_PL_ERR;
   else
     Feld[key] = NB_PL_OK;
}

/* ------------------------------------------------------------------- */
void SetDCTaxeErr( char *Wert1, int key1, char *Wert2, int key2, char *Feld, int key )
{
  if ( Feld[key1] != NB_PL_NO_VAL && Feld[key2] != NB_PL_NO_VAL )
  {
	  if ( strcmp( Wert1, "01" ) == 0  && strcmp( Wert2, "01" ) == 0 )
		  Feld[key] = NB_PL_ERR;
	  else
	      Feld[key] = NB_PL_OK;
  }
}

/* ------------------------------------------------------------------- */
void SetDCFlagErr( short Wert, char *Feld, int key )
{
  if ( Feld[key] != NB_PL_NO_VAL )
  {
     if (  Wert == 0 || Wert == 1 )
        Feld[key] = NB_PL_OK;
     else
        Feld[key] = NB_PL_ERR;
  }
}
