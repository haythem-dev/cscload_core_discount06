
/* ---------------------------------------------------------------------- *
 *   Aufgabe        : generiert die Nachbearbeitungsgruende               *
 *                    bei Datacare-Aenderungen                            *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 31.01.2005                                          *
 *   Autor          : Hörath                                              *
 * ---------------------------------------------------------------------- */

#ifndef NB_GEN_DC_INCLUDED
#define NB_GEN_DC_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#define NO_WERT -1

/*NB_PLAUSI, NB_ZWING, NB_NZWING*/
#define NB_PL_NO_VAL '9'
#define NB_PL_OK	 '0'
#define NB_PL_ERR	 '1'

/*DCSTATUS*/
#define DCSTATUS_FREIGEG	"F"
#define DCSTATUS_GESPERRT	"S"

/*MWST-CODES*/
#define DCMWST_K	"0"
#define DCMWST_VERM	"1"
#define DCMWST_VOLL	"2"
#define DCMWST_3RD	"3"
#define ZART_MWST_VOLL "0"
#define ZART_MWST_3RD "2"
#define ZART_MWST_K	  "3"

/*DCAECODE*/
#define DCAECODE_NEW		"N"
#define DCAECODE_REACT		"R"
#define DCAECODE_AEND		" "
#define DCAECODE_AUSVERKEHR	"A"
#define DCAECODE_DEL		"L"

/*DCBOX*/
#define DCBOX_EMPTY			" "
#define DCBOX_GREEN			"G"
#define DCBOX_YELLOW		"Y"
#define DCBOX_RED			"R"
#define DCBOX_NO			"N"
	
/*REZEPTZEICHEN*/
#define REZEPTZ_BTM			"SG"


/* Kennzeichen für Preisübernahme aus ccomgroupprop*/
#define ADOPT_PRICE '1'


/*ZAENDERUNG*/
#define ZAENDERUNG_AEND				"1"
#define ZAENDERUNG_NEU				"0"
#define ZAENDERUNG_AEND_UNVOLLST	"3"
#define ZAENDERUNG_NEU_UNVOLLST		"2"

/*NBSTATUS */
#define NBSTATUS_NO_ERR		"0"
#define NBSTATUS_PLAUSI		"4"
#define NBSTATUS_ZWING		"2"
#define NBSTATUS_NZWING		"1"
#define NBSTATUS_ZWING_PL	"6"
#define NBSTATUS_ZW_PL_NZW	"7"
#define NBSTATUS_ZWING_NZW	"3"
#define NBSTATUS_NZW_PL		"5"

/*----------  Feldpositionen in NB_PLAUSI ------------- */
#define PL_PZN			0
#define PL_ARTKURZTXT	1
#define PL_ARTTXT		2
#define PL_ARTMENGE		3
#define PL_ARTEINHEIT	4
#define PL_KZTAXE		5
#define PL_KZAPOVERL	6
#define PL_ZREZEPT		7
#define PL_ZKASSE		8
#define PL_ZKASSEZUS	9
#define PL_KZCODEIN		10
#define PL_GEP			11
#define PL_AEP			12
#define PL_KKP			13
#define PL_AVP			14
#define PL_KZOHNEPRBESCH 15
#define PL_MWSTCODEGR	16
#define PL_MWSTCODEAPO	17
#define PL_CHARGE		18
#define PL_KZVERMREZGEB	19
#define PL_LIEFERANT	20
#define PL_LIEFARTNR	21
#define PL_DEFEKTUR		22
#define PL_MINDABN		23
#define PL_KZNVERFVERL	24
#define PL_KZNVERFGR	25
#define PL_HOEHE		26
#define PL_BREITE		27
#define PL_TIEFE		28
#define PL_LAGERHINW	29
#define PL_GEFAHRHINW	30
#define PL_KZABLAUF		31
#define PL_KZAPOPFL		32
#define PL_REGNR		33
#define PL_THERAPIEGRP	34
#define PL_ARTGRP		35
#define PL_KZMINIBASIS	36
#define PL_AENDERCODE	37
#define PL_HERSTCODE	38
#define PL_GEWICHT		39
#define PL_GRPHERSTOEKO	40
#define PL_KZOEKO		41
#define PL_KZ_ABGBESCHR	42
#define PL_KZVERKEHR	43
#define PL_KKPHAUSAPO	44
#define PL_HERKUNFT		45
#define PL_SORTINGRP	46
#define PL_BOXERSTATT	47
#define PL_DAR			48
#define PL_DATERSTANL	49
#define PL_DATLETZTAEND	50
#define PL_DATGUELTAB	51
#define PL_AUSLIEFVERS	52
#define PL_NEUANLEGER	53
#define PL_PARTNERNR	54
#define PL_REFERENZNR	55
#define PL_KZNGR		56
#define PL_WGRPAPOVERL	57
#define PL_ARTBEZ2		58
#define PL_UNNR			59
#define PL_GENERIKUM	60
#define PL_ORIGINALPROD	61
#define PL_ARZNEIMITTEL	62
#define PL_ABGR_VERORD	63
#define PL_SG_ZUB		64
#define PL_SG_SUBSTANZ	65
#define PL_DROGAGS_KAT1	66
#define PL_DROGAGS_KAT2	67
#define PL_DROGAGS_KAT3	68
#define PL_BLUTKONSERVE	69
#define PL_RADIOAKT_ARZNEI 70
#define PL_FUETTER_ARZNEI  71
#define PL_ARZNEI_GEWERBE  72
#define PL_DENTALARZNEI	73
#define PL_MEDIZIN_GAS	74
#define PL_KONTAKTLINSENFL 75
#define PL_ALK_UNVERST	76
#define PL_ALK_VERGAELLT   77
#define PL_GIFT			78
#define PL_ZYTOSTATIKUM	79

#define PL_PFLANZENSCH	80
#define PL_MEDPROD_ABGVO 81
#define PL_MEDPROD_KLASS 82
#define PL_ARTGRP_LTVO	83
#define PL_BIOSIEGEL	84
#define PL_ANTIBIOTIKUM	85
#define PL_FAELSCHSICHER 86


/*----------  Felder in NB_ZWING -------------- */
#define ZW_GEP_GR_AEP        0
#define ZW_AEP_GEP_0         1
#define ZW_GEP_ERR			 2
#define ZW_WRGRP_ARTBEZ      3
#define ZW_AEND_BOX_TAX      4
#define ZW_PREISE_TAX_BOX    5
#define ZW_PREISE_TAX_WRGRP  6
#define ZW_BOX_N0_TAX_N1	 7
#define ZW_AEP_ERR			 8
#define ZW_GEP_HERSTPROZ	 9
#define ZW_AEP_HERSTPROZ	10
#define ZW_SONDERGROSSO		11
#define ZW_MEDIZIN_PROD		12
#define ZW_WRGRP_UNBEKANNT	13
#define ZW_TO_MWST_3RD		14

/*----------  Felder in NB_NZWING -------------- */
#define NZ_REAKTIV           0
#define NZ_AEP_GEP_0         1
#define NZ_GEP_HINW			 2
#define NZ_AEND_LIEF_HERST   3
#define NZ_AEND_WRGRP        4
#define NZ_ART_AUSS_HANDEL	 5
#define NZ_AEP_HINW			 6
#define NZ_AH_PRICE_CHANGE	 7
#define NZ_WRGRP_HOCHPREIS	 8
#define NZ_WRGRP_HOCHPREIS_ENTFERNT 9
#define NZ_AEND_SKONTOFAEHIG 10


/*----------  Structur der Meldung ------------ */
struct ERR_MeldungDC
{
  int key;
  char *meldung;
};

/* ---------- Prototyping ------------------------ */
void SetDCErr( char* Wert, char *ZulWerte, char *Feld, int key );
void SetDC2Err( char* Wert, char *ZulWerte, char *Feld, int key );
void SetDCNumErr( long Wert, char *Feld, int key );
void SetDCPdmErr( double Wert, char *Feld, int key );
void SetDCNumBlankErr( char* Wert, char *Feld, int key );
void SetDCFlagErr( short Wert, char *Feld, int key );

void SetDCGroesser( double Wert1, double Wert2, char *Feld, int key );
void SetDCGleich( char* Wert1, char* Wert2, char *Feld, int key );
void SetDCTrueFalse( int true_false, char *Feld, int key );
void SetDCGueltigabErr( long datum, char *Feld, int key );
void SetDCTaxeErr( char *Wert1, int key1, char *Wert2, int key2, char *Feld, int key ); 

int  IsDCFeldErr( char *Feld, int key );
int  IsDCErr( char *Feld );

char *GetDCErrMeld( struct ERR_MeldungDC *err, int key );
char *Get_ZW_ErrMeldDC( int key );
char *Get_NZ_ErrMeldDC( int key );
char *Get_PL_ErrMeldDC( int key );

#ifdef __cplusplus
}
#endif

#endif /* NB_GEN_DC_INCLUDED */
