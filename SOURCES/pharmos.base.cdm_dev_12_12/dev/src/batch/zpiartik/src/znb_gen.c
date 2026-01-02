/* ---------------------------------------------------------------------- *
 *                        Z N B _ G E N . C                               *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : generiert die Nachbearbeitungsgruende               *
 *                    bei IFA-Aenderungen                                 *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 23.03.98                                            *
 *   letztes Update : 12.04.00                                            *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <hdatum/phodate.h>

#include "znb_gen.h"

struct ERR_Meldung PL_Meldung[] =
{
  { PL_A00PZN          , "PZN: Pruefziffer falsch" },
  { PL_A00ANBNR        , "IFA-Hersteller nicht vorhanden" },
  { PL_A00ATYP         , "A00ATYP ungueltig" },
  { PL_A00LKZ          , "Loeschkennz. ungueltig" },
  { PL_A00EAN          , "EAN-Nr fehlerhaft" },
  { PL_A00NTIN         , "NTIN fehlerhaft" },
  { PL_A05VFDAT        , "A00VFDAT ungueltig" },
  { PL_A05LZEIT        , "Laufzeit Monate nicht numerisch" },
  { PL_A05KKETTE       , "A05KKETTE ungueltig" },
  { PL_A05LICHT        , "A05LICHT  ungueltig" },
  { PL_A05FEUCHT       , "A05FEUCHT ungueltig" },
  { PL_A05LAGE         , "A05LAGE   ungueltig" },
  { PL_A05ZERBR        , "A05ZERBR  ungueltig" },
  { PL_A01AMPVAMG      , "A01AMPVAMG ungueltig" },
  { PL_A01AMPVSGB      , "A01AMPVSGB ungueltig" },
  { PL_A01GEPDM        , "Grosso ungueltig" },
  { PL_A01UVP          , "A01UVP ungueltig" },
  { PL_A01AEPDM        , "ApoEK ungueltig" },
  { PL_A01AVPDM        , "ApoVK ungueltig" },
  { PL_A01MWST         , "Kennz. MWST ungueltig" },
  { PL_A02AM           , "A02AM ungueltig" },
  { PL_A02MP           , "A02MP ungueltig" },
  { PL_A02APPFL        , "A02APPFL ungueltig" },
  { PL_A02VSPFL        , "A02VSPFL ungueltig" },
  { PL_A02BTM          , "A02BTM ungueltig" },
  { PL_A02TFG          , "A02TFG ungueltig" },
  { PL_A02DROCH        , "A02DROCH ungueltig" },
  { PL_A02TIERAM       , "A02TIERAM ungueltig" },
  { PL_A02NEGLIS       , "A02NEGLIS ungueltig" },
  { PL_A03VTSTAT       , "A03VTSTAT ungueltig" },
  { PL_A03VWGGH        , "A03VWGGH ungueltig" },
  { PL_A03VWGAPO       , "A03VWGAPO ungueltig" },
  { PL_A03VWGKAP       , "A03VWGKAP ungueltig" },
  { PL_A03VWGSEH       , "A03VWGSEH ungueltig" },
  { PL_A03VKSTAT       , "A03VKSTAT ungueltig" },
  { PL_A06PZNNF        , "A06PZNNF: Pruefziffer falsch" },
  { PL_ZUZAHL          , "Zuzahlung ungueltig" },
  { PL_A02HMZV         , "A02HMZV ungueltig"  },
  { PL_TAXKENN         , "Taxe inkonsistent" },
  { PL_A01ZBV          , "A01ZBV ungueltig"  },
  { PL_A02LIFSTYL	   , "A02LIFSTYL ungueltig" },
  
  { PL_A02AUSNREI	   , "A02AUSNREI ungueltig" },
  { PL_A02GENER		   , "A02GENER ungueltig" },
  { PL_A02SDB		   , "A02SDB ungueltig" },
  {	PL_A02NEM		   , "A02NEM ungueltig" },
  {	PL_A06PZNORIG	   , "A06PZNORIG: Pruefziffer falsch" },
  { PL_A02LEBENSM	   , "A02LEBENSM ungueltig" },
  { PL_A02DIAET		   , "A02DIAET ungueltig" },

  { PL_A02HOMOEO   ,  "A02HOMOEO ungueltig"   } ,
  { PL_A02ANTHRO   ,  "A02ANTHRO ungueltig"    } ,
  { PL_A02PHYTO    ,  "A02PHYTO ungueltig"    } ,
  { PL_A02BIOZID   ,  "A02BIOZID ungueltig"   } ,
  { PL_A02PSM      ,  "A02PSM ungueltig"      } ,
  { PL_A02TREZEP   ,  "A02TREZEP ungueltig"   } ,
  { PL_A0247AMG    ,  "A0247AMG ungueltig"     } ,
  { PL_A01SERSTAT  ,  "Erstatt-Betrag ungueltig" },
  { PL_A01SAB130A  ,  "Abschlags-Betrag ungueltig" },
  { PL_A02VERIFIZ  ,  "A11VERIFIZ ungueltig" },
  { PL_A0252B	   ,  "A0252B ungueltig" },
  { PL_A02BIOSIEG  ,  "A02BIOSIEG ungueltig" },
  { PL_A02KOSMET   ,  "A02KOSMET ungueltig" },
  { PL_A02STERIL   ,  "A02STERIL ungueltig" },

  { PL_A02EB130B   ,  "A02EB130B ungueltig" },
  { PL_ABZUG_130  ,   "Abzug nach §130, aber Erstattbetrag=0" },
  { PL_A02WIRKSTO   , "A02WIRKSTO ungueltig" },
  { PL_A02ELEKTRO   , "A02ELEKTRO ungueltig" },
  { PL_A02EXPLOS   ,  "A02EXPLOS ungueltig" },
  { PL_A02BIOTECH   , "A02BIOTECH ungueltig" },
  { PL_A02STIFEAR   , "A02STIFEAR ungueltig" },
  { PL_A02WEEEREG   , "A02WEEEREG ungueltig" },
  //{ PL_A02BATTG	    , "A02BATTG ungueltig" }, wurde durch A02BATTREG ersetzt
  { PL_A02BATTREG   , "A02BATTREG ungueltig" },
  { PL_A02SWUNDB    , "A02SWUNDB ungueltig" },
  { PL_A02ATMP      , "A02ATMP ungueltig" },
  { PL_A02AUSIMPF   , "A02AUSIMPF ungueltig" },
  { PL_A02EUNOVEL   , "A02EUNOVEL ungueltig" },
  { PL_A02BEDZUL    , "A02BEDZUL ungueltig" },
  { PL_A02ZULAUSN   , "A02ZULAUSN ungueltig" },
  { PL_A02AMNOG     , "A02AMNOG ungueltig" },
  { PL_A02ORDRUG    , "A02ORDRUG ungueltig"},
  { PL_A02PRSTRMO    , "A02PRSTRMO ungueltig" },

  /* ----------- IFA Version 20244 ----------- */
  { PL_A02AMDARKI   , "A02AMDARKI ungueltig"},
  { PL_A02AMAUFFB   , "A02AMAUFFB ungueltig"},
  { PL_A02AMBEKI    , "A02AMBEKI ungueltig"},
  { PL_A02AMVEKRW   , "A02AMVEKRW ungueltig"},
  { PL_A01DAPU78    , "A01DAPU78 ungueltig"},
  { PL_A02D130A18   , "A02D130A18 ungueltig"},

  /* ----------- IFA Version 20248 ----------- */
  { PL_A02MEDCG     , "A02MEDCG ungueltig"},
  { PL_A05LGTMPB    , "A05LGTMPB ungueltig"},

  /* ----------- IFA Version 20252 ----------- */
  { PL_A01B130B1C   , "A01B130B1C ungueltig"},
  { PL_A01DAT78     , "A01DAT78 ungueltig" },
  { PL_A01RAB130A   , "A01RAB130A ungueltig" },
  { PL_A01ZUZAH61   , "A01ZUZAH61 ungueltig" },

  { NO_WERT            , "" },
};


struct ERR_Meldung ZW_Meldung[] =
{
  { ZW_SONDER_GEP      , "Achtung Sondergrosso-Preis" },
  { ZW_AEP_GR_GEP      , "AEP nicht groesser GROSSO" },
  { ZW_AVP_GR_AEP      , "AVP nicht groesser AEP" },
  { ZW_PROZ_PLUS_MINUS , "Kein Zuschlag/Abschlag GROSSO/AEP vorhanden" },
  { ZW_GEP_AUF_NULL    , "Aenderung GROSSO auf 0,00" },
  { ZW_AEP_AUF_NULL    , "Aenderung AEP auf 0,00" },
  { ZW_GEP_TROTZ_PPE   , "Aenderung GROSSO trotz Preisvorgabe PPE" },
  { ZW_AEP_TROTZ_PPE   , "Aenderung AEP trotz Preisvorgabe PPE" },
  { ZW_GEP_TROTZ_PARAM , "Aenderung GROSSO trotz Preisvorgabe PARAM" },
  { ZW_AEP_TROTZ_PARAM , "Aenderung AEP trotz Preisvorgabe PARAM" },
  { ZW_TAXPRUEFGROSSO  , "Aenderung GROSSO/AEP/AVP trotz Taxpruefgrosso" },
  { ZW_PRDIFF_OHNE_KEY , "IFA-Preisaend. aber kein Indikator 4 / 5" },
  { ZW_PRDIFF_SAMEDATE , "IFA-Preisaend., Preisdiff. bei gleichem Datum" },

  { ZW_LOESCH_KENN_NEU , "Neuaufnahme, IFA-Satz traegt Loeschkennzeichen" },
  { ZW_ART_OHNE_PREIS  , "Artikel ohne Preis" },
  { ZW_EAN_MEHRFACH    , "Gleiche EAN-NR bei unterschiedlicher Artikel-Nr" },
  { ZW_NTIN_MEHRFACH   , "Gleiche NTIN bei unterschiedlicher Artikel-Nr" },
  { ZW_GTIN_MEHRFACH   , "Gleiche GTIN bei unterschiedlicher Artikel-Nr" },
  { ZW_PROZ_PLUS       , "%-Vorzeichen +" },
  { ZW_PROZ_MINUS      , "%-Vorzeichen -" },
  { ZW_PZNNF_GLEICH    , "PZN-Nachfolger = PZN" },

  { ZW_TAXPRUEF        , "Preise nicht nach Taxe" },
  { ZW_PREISPRUEF      , "NichtTaxPreise falsch" },

  { ZW_PREIS_ZUGROSS   , "Preise zu hoch" },

  { ZW_IFA_COMPLETE    , "Ifa-Satz nicht vollstaendig" },

  //{ ZW_IFADAT_01012002 , "Ifa-Datum <  01.01.2002 oder <= ArtPreis-Datum" },
  { ZW_IFADAT_ARTDAT   , "Ifa-Datum <= Artikelpreis-Datum" },
  { ZW_REWE_SONDER_GEP , "Achtung Rewe-Sondergrosso-Preis" },
  { ZW_KOMB_LEBENSM_NEM_DIAET, "ungueltige Kombination aus Lebensm./Nem/Diaet" },
  { ZW_NO_FMD_CHECK_REQUIRED , "Bei Arzneimittel für neuartige Therapien, ist keine FMD Prüfung erforderlich"},
  { ZW_CHG_APPFL       , "Änderung Apothekenpflicht"},
  { ZW_CHG_VSPFL       , "Änderung Rezeptpflicht"},
  { NO_WERT            , "" },
};

struct ERR_Meldung NZ_Meldung[] =
{
  { NZ_PRDIFF       , "Preisdifferenz zum Artikelstamm zu gross" },
  { NZ_PZNNF_NVOR   , "Kein Artikelstamm fuer PZN-Nachfolger vorhanden" },
  { NZ_PZNNF_DIFF   , "IFA-PZN neu weicht vom Artikelstamm ab" },
  { NZ_PREISE_UNG   , "IFA-Satz ohne gueltige Preise" },
  { NZ_MWST_DIFF    , "IFA-MWST-Aenderung zum Artikelstamm-Eintrag" },
  { NZ_LOESCH_AH_AV , "IFA-Loeschung ohne AH/AV im Artikelstamm" },
  { NZ_AEN_BEI_AH   , "IFA-Neuaufn-/Aenderung bei AH im Artikelstamm" },
  { NZ_NURKVA_PRUEF , "nur KVA im Artikelstamm pruefen" },
  { NZ_VTBIFA_PRUEF , "VertrBindApo im Artikelstamm pruefen" },
  { NZ_IFA_COMPLETE , "Ifa-Satz nicht vollstaendig" },
  { NZ_AEND_NEM		, "IFA-Loeschung NEM-Art. - rechtl. Status nachfragen!" },
  { NZ_NEM_DLM_LM_NEU,"IFA-Neu/Änderung Kennz. NEM/DLM/LM" },
  { NZ_AEP_EQ_GR_UEBN,"AEP=Grosso (Ifa-Preise werden übernommen)" },
  { NZ_AEP_EQ_GR_CALC,"AEP=Grosso (Grosso wird errechnet)" },
  { NZ_NO_BIOZID	, "laut IFA kein Biozid-Artikel" },
  { NZ_NO_PSM		, "laut IFA kein Pflanzenschutzmittel" },
  { NZ_PREISE_GROSSO_AEP, "IFA-Preismeldung ohne Grosso oder AEP" },
  { NZ_EAN_DIFF, "Unterschiedliche EAN-NR bei gleicher Artikel-Nr" },
  { NZ_NTIN_DIFF, "Unterschiedliche NTIN bei gleicher Artikel-Nr" },
  { NZ_GTIN_DIFF, "Unterschiedliche GTIN bei gleicher Artikel-Nr" },
  { NZ_UNNR_DIFF,	"UN-Nummer IFA ungleich Artikelstamm" },
  { NZ_NO_KOSMETIKUM, "laut IFA kein Kosmetikum" },
  { NZ_EAR_REG_MISSING            , "IFA Stiftung EAR Registrierung ohne Registriernummern" },
  { NZ_EAR_REG_REDUNDANT          , "IFA Stiftung EAR Registriernummern ohne Registrierungspflicht" },
  { NZ_REG_ELECTRO_IFA_REG_MISSING, "Registrierter Elektroartikel ohne IFA Registrierung Stiftung EAR" },
  { NZ_REG_ELECTRO_IFA_EAR_MISSING, "Registrierter Elektroartikel ohne IFA Registriernummer Stiftung EAR" },
  { NZ_CHG_ELECTRO_REG	, "Nachträgliche Registrierungspflicht bei bestehendem Elektroartikel" },
  { NZ_CHG_BATTREG_REG	, "Nachträgliche Batterieregisteriung in bestehendem Elektroartikel" },
  { NZ_CHG_BATTG_IFA    , "Elektroartikel nach Batteriegesetz ohne IFA Batterieregistriernummer" },
  { NZ_UNKNOWN_ELECTRO  , "Elektrokennzeichnung des Artikels entspricht nicht den IFA Daten"},
  { NZ_WRONG_ELECTRO_REG, "Registrierter Elektroartikel ohne erkennbare Registriernummern"},
  { NZ_EAR_DIFF         , "IFA Abweichung der WEEEREG zur Hersteller EAR" },
  { NZ_EAN_DUPL_IGNORED , "IFA EAN Duplikat wird ignoriert. Artikel hat bereits eine EAN." },
  { NZ_GROSSO_AEP_NULL_ART, "Grosso=0, AEP=0 oder Grosso=AEP, aber Artikelpreis vom Bestand kann übernommen werden."},
  { NZ_GR_EQ_AEP_CALC, "Grosso=AEP oder AEP=0 (AEP wird errechnet)" },
  { NZ_AEP_ART_GRO, "IFA AEP entspricht GROSSO, AEP aus neuem Grosso wird berechnet."},
  { NZ_IFA_AH_NOPRICE, "Artikel außer Handel bei IFA, Preise werden bei Datenvollabzug nicht berücksichtigt."},
  { NZ_NOVEL_FOOD, "Novel-Food EU-VO"},
  { NZ_CHG_SIDABLATT, "Änderung Sicherheitsdatenblatt"},
  { NZ_CHG_PSM,       "Änderung Pflanzenschutzverordnung"},
  { NZ_CHG_LZEIT,     "Änderung Laufzeit in Monaten"},
  { NZ_CHG_BIOZID,    "Laut IFA Biozid Artikel"},
  { NZ_CHG_BIOSIEGEL, "Änderung Bioartikel"},
  { NZ_CHG_MEDCANG_SET, "Artikel lt. MedCanG"},
  { NZ_CHG_MEDCANG_RESET, "kein Artikel lt. MedCanG"},
  { NO_WERT         , "" },
};


char *GetIfaErrMeld( struct ERR_Meldung *err, int key )
{
  int i;
  i = 0;
  while ( err[i].key != NO_WERT && err[i].key != key ) i++;
  if ( err[i].key == key )
    return err[i].meldung;
  else
    return "";
}

char *Get_ZW_ErrMeld( int key )
{
  return GetIfaErrMeld( ZW_Meldung, key );
}

char *Get_NZ_ErrMeld( int key )
{
  return GetIfaErrMeld( NZ_Meldung, key );
}

char *Get_PL_ErrMeld( int key )
{
  return GetIfaErrMeld( PL_Meldung, key );
}


void SetIfaTrueFalse( int true_false, char *Feld, int key )
{
   if ( Feld[key] != NOVALUE_PL )
      Feld[key] = (char) ( true_false ? '1' : '0' );
}

void SetIfaErr( char* Wert, char *ZulWerte, char *Feld, int key )
{
  if ( Feld[key] != NOVALUE_PL )
  {
     int i;
     i = 0;
     while ( ZulWerte[i] && ZulWerte[i] != *Wert ) i++;
     Feld[key] = (char) ( ZulWerte[i] ? '0' : '1' );
  }
}

void SetIfa2Err( char* Wert, char *ZulWerte, char *Feld, int key )
{
  if ( Feld[key] != NOVALUE_PL )
  {
     int i;
     i = 0;
     while ( ZulWerte[i] && memcmp( &ZulWerte[i], Wert, 2 ) != 0 ) i += 2;
     Feld[key] = (char) ( ZulWerte[i] ? '0' : '1' );
  }
}

/*
void SetIfaNumErr( char* Wert, char *Feld, int key )
{
  int i;
  i = 0;
  while ( Wert[i] && Wert[i] >= '0' && Wert[i] <= '9' ) i++;
  Feld[key] = (char) ( Wert[i] ? '1' : '0' );
}
*/

/*
void SetIfaNumErr( char* Wert, char *Feld, int key )
{
  if ( Feld[key] != NOVALUE_PL )
  {
     int i;
     int lng;

     lng = strlen( Wert ) - 1;
     while ( lng >= 0 && Wert[lng] == ' ' ) lng--;
     lng++;

     i = 0;
     while ( i < lng && Wert[i] >= '0' && Wert[i] <= '9' ) i++;

     if (  i == lng )
        Feld[key] = '0';
     else
        Feld[key] = '1';
  }
}
*/
void SetIfaCharNumErr(char* Wert, int minVal, int maxVal, int lng, char* Feld, int key)
{
    if (Feld[key] != NOVALUE_PL)
    {
        char result = '0';
        if (strlen(Wert) > lng || strlen(Wert) == 0)
        { // string too long or empty
            result = '1';
        }
        else
        {
            for (int i = 0; i < strlen(Wert); i++)
            {
                if (!isdigit(Wert[i]) && !isspace(Wert[i]))
                { //not a digit
                    result = '1';
                    break;
                }
            }
        }
        if (result == '0')
        {
            int num = atoi(Wert);
            if (num < minVal || num > maxVal)
            { // not in given range
                result = '1';
            }
        }
        Feld[key] = result;
    }
}


void SetIfaShortErr(short Wert, short minVal, short maxVal, char* Feld, int key)
{
    if (Feld[key] != NOVALUE_PL)
    {
        if (Wert >= minVal && Wert <= maxVal)
            Feld[key] = '0';
        else
            Feld[key] = '1';
    }
}

void SetIfaShort2Err(short Wert, short minVal, short maxVal, short addVal, char* Feld, int key)
{
    if (Feld[key] != NOVALUE_PL)
    {
        if ((Wert >= minVal && Wert <= maxVal) || Wert == addVal)
            Feld[key] = '0';
        else
            Feld[key] = '1';
    }
}

void SetIfaNumErr( long Wert, char *Feld, int key )
{
  if ( Feld[key] != NOVALUE_PL )
  {
     if (  Wert >= 0 )
        Feld[key] = '0';
     else
        Feld[key] = '1';
  }
}

void SetIfaPdmErr( double Wert, char *Feld, int key )
{
  if ( Feld[key] != NOVALUE_PL )
  {
/*   if (  Wert >= 0 )  */
     if (  Wert > -0.0001 )  
        Feld[key] = '0';
     else
        Feld[key] = '1';
  }
}

void SetIfaNumBlankErr( char* Wert, char *Feld, int key )
{
  if ( Feld[key] != NOVALUE_PL )
  {
     int i;
     i = 0;
     while ( Wert[i] && ( (Wert[i]>='0' && Wert[i]<='9') || Wert[i]==' ') ) i++;
     Feld[key] = (char) ( Wert[i] ? '1' : '0' );
  }
}


/*
void SetIfaGroesser( char* Wert1, char* Wert2, char *Feld, int key )
{
  if ( strcmp( Wert1, Wert2 ) >= 0 )
     Feld[key] = '1';
   else
     Feld[key] = '0';
}
*/

void SetIfaGroesser( double Wert1, double Wert2, char *Feld, int key )
{
  if ( Wert1 >= Wert2 )
     Feld[key] = '1';
   else
     Feld[key] = '0';
}

int IsIfaFeldErr( char *Feld, int key )
{
/*   return Feld[key] == '1';  */
  return Feld[key] != '0';
}

int IsIfaErr( char *Feld )
{
    int i;
    i = 0;
/*
    while ( Feld[i] && Feld[i] == '0' ) i++;
*/
    /* wegen NOVALUE_PL */
    while ( Feld[i] && ( Feld[i] == NOVALUE_PL || Feld[i] == '0' ) ) i++;
    return (char) (Feld[i] ? 1 : 0 );
}



void SetIfaGueltigabErr( long datum, char *Feld, int key )
{
  if ( Feld[key] != NOVALUE_PL )
  {
     if (  datum == 0 )
        Feld[key] = '1';
     else
        Feld[key] = '0';
  }
}

int Check_IFA_Zuzahlung( char *Zuzahlung )
{
  int  bOk;
  char *str;

  str = Zuzahlung;

  bOk = strlen( str ) == 7;
  if ( bOk )
     bOk = *str >= '1' && *str <= '6';
  if ( bOk )
  {
    str++;
    while ( bOk && *str )
    {
      bOk = *str == '0';
      str++;
    }
  }
  return bOk;
}


void SetIfaZuzahlErr( char *Wert, char *Feld, int key )
{
  if ( Feld[key] != NOVALUE_PL )
       Feld[key] = (char) ( !Check_IFA_Zuzahlung( Wert ) ? '1' : '0' );
}


void SetIfaGleich( char* Wert1, char* Wert2, char *Feld, int key )
{
  if ( strcmp( Wert1, Wert2 ) == 0 )
     Feld[key] = '1';
   else
     Feld[key] = '0';
}


/* neu fuer 2004 */
void SetIfaTaxeErr( char *Wert1, int key1, char *Wert2, int key2, char *Feld, int key )
{
  if ( Feld[key1] != NOVALUE_PL && Feld[key2] != NOVALUE_PL )
  {
	  if ( strcmp( Wert1, "01" ) == 0  && strcmp( Wert2, "01" ) == 0 )
		  Feld[key] = '1';
	  else
	      Feld[key] = '0';
  }
}
