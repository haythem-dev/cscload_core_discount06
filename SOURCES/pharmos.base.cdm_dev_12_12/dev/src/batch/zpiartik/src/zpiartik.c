
/* ---------------------------------------------------------------------- *
 *                            ZPIARTIK. C                                 *
 * ---------------------------------------------------------------------- *
 *   Aufgabe        : Ifa Artikel     laden                               *
 * ---------------------------------------------------------------------- *
 *   erstellt am    : 31.03.00                                            *
 *   letztes Update :                                                     *
 *   Autor          : Schmitt                                             *
 * ---------------------------------------------------------------------- */

#include "../../../cdm_version.h"

const char* getVersion()
{
    // in binary embedded full version string
    return "@(#)PHOENIX Stand: " CDM_VERSION " - 3.2.0 : zpiartik 10.12.2024 GW";
}

/*!
\page page16 zpiartik - Ifa Artikel laden
___________________________________________________________________________
\version	3.2.0
\date		10.12.2024
\internal
- GW: - CPR-240818 - support for the new ifa versions 248 and 252
        New fields processed: A02MEDCG, A05LGTMPB, A01B130B1C, A01DAT78, A01RAB130A, A01ZUZAH61
        Modified field processes: A02EUNOVEL, A06PZNORIG, A05KKETTE, A05TMAX
\endinternal

___________________________________________________________________________
\version	3.1.9
\date		26.08.2024
\internal
- GW: - CPR-240206 - New messages and new processes for the following fields
                     A02SDB, A02PSM, A05VFDAT, A05LZEIT, A02BIOZID,
                     A02BIOSIEG, BATTREG, A02EUNOVEL, A02APPFL, A02VSPFL
\endinternal

___________________________________________________________________________
\version	3.1.8
\date		28.03.2024
\internal
- GW: - CPR-231102 - New IFA Version support 20244
        New fields processed: A02AMDARKI, A02AMAUFFB, A02AMBEKI, A02AMVEKRW, A01DAPU78, A02D130A18
        Modified fields and interpretations: A02ATMP, A02AUSIMPF, A02EUNOVEL, A02AMNOG, A02PRSTRMO
                                             A02BATTREG, A02PSM, A02SDB, A02BTM
\endinternal

___________________________________________________________________________
\version	3.1.7
\date		22.02.2024
\internal
- DK: - CPR-220839 - New IFA Version support 20240
        New fields processed A00UIDIDI, A02SWUNDB, A02ATMP, A02EUNOVEL, A2AUSIMPF, A02ORDRUG, A02BEDZUL, A02ZULAUSN, A02AMNOG, A00ZINNR7, A00EOVNR7, A00NTIN, A00GTIN, A02PRSTRMO
        Modified fields and interpretations: A02 ELEKTRO, A02 STIFEAR, A02BATTREG, A02WEEEREG
        Additional changes for duplicate checks on EAN
        Additional checks for IFA full data import regarding existing pricechecks, not completed
\endinternal

___________________________________________________________________________
\version	3.1.6
\date		01.02.2024
\internal
- DK: - CPR-231102 Vorabversion neue IFA Version 20244
        A02EB130B - Kennzeichen Arzneimittel mit Erstattungsbetrag § 130b SGB V (A02EB130B): Ergänzung Wert 03
        A0247AMG - Kennzeichen Tierarzneimittel-Abgabemengen-Register (TAR) (A0247AMG): Änderung Wert 01 und Ergänzung Wert 02 / 03
\endinternal

___________________________________________________________________________
\version	3.1.5
\date		19.06.2023
\internal
- KT: CPR-230035 Retourensperre bei Preisänderungen (setzen während IFA-Einspielung)
\endinternal
___________________________________________________________________________
\version	3.1.5
\date		01.02.2023
\internal
- MH: CPR-220839 IFA 20236
      (Teil 2: Umbenennung A00OEVNR6 -> A00OEVNR, A00ZINNR6 -> A00ZINNR, 
                           A02ELEKEAR -> A02STIFEAR, A02MELDENR -> A02BATTREG
               neues Feld A02PRSTRMO)
\endinternal

___________________________________________________________________________
\version	3.1.4
\date		25.11.2022
\internal
- MH: CPR-220839 IFA 20236 
      (Teil 1: neue zulaessige Werte für A00ATYP und A02EB130B)
\endinternal
___________________________________________________________________________
\version	3.1.3
\date		20.04.2020
\internal
- - WH: CPR-IFa IFA 20224
\endinternal
___________________________________________________________________________
\version	3.1.2
\date		14.02.2019
\internal
- TH: Übernahme zifaoart.a11veripfl --> zifaart.a11veripfl
\endinternal
___________________________________________________________________________
\version	3.1.1
\date		18.01.2019
\internal
- TH: A11VERIHOC 8-stellig
\endinternal
___________________________________________________________________________
\version	3.1.0
\date		06.11.2018
\internal
- - TH: CPR-180813 IFA 20219
\endinternal
___________________________________________________________________________
\version	3.0.0
\date		22.02.2018
\internal
- - TH: CPR-171513 IFA 20215
\endinternal
________________________________________________________________________
\version	2.9.8
\date		01.08.2017
\internal
- TH: auch A11GDAT bei Ermittlung zifaart.datumgueltigab berücksichtigen
\endinternal
___________________________________________________________________________
\version	2.9.7
\date		21.04.2017
\internal
- - TH: CR-17D015 IFA 20212
\endinternal
___________________________________________________________________________
\version	2.9.6
\date		06.04.2016
\internal
- TH: IFA 20208
\endinternal
___________________________________________________________________________
\version	2.9.5
\date		08.05.2015
\internal
- TH: IFA 20204
\endinternal
___________________________________________________________________________
\version	2.9.4
\date		07.04.2015
\internal
- TH: SR-15014334: Versorgung zpreiserhoehung
\endinternal
___________________________________________________________________________
\version	2.9.3
\date		02.07.2014
\internal
- TH: IFA 20199
\endinternal
___________________________________________________________________________
\version	2.9.2
\date		10.04.2014
\internal
- TH: wandeln mit neuer zartikel/zartpreis-Struktur
\endinternal
___________________________________________________________________________
\version	2.9.1
\date		17.03.2014
\internal
- TH: SR-14000586 = kein Erstattungsbetrag ab 01.04. mehr
\endinternal
___________________________________________________________________________
\version	2.9.0
\date		21.02.2014
\internal
- TH: IFA 20195 --> A02WIRKSTO, A02ELEKTRO, A00GTIN
\endinternal

*/

/* 1.1.3 11/09/2000 */
/* 1.1.4 29/03/2001 : A02VSPFL oeffnen bei Preisaenderung (g_iartik.c) */
/* 1.1.5 15/10/2001 : DM-Taxe + EURO-Taxe in l_taxtab.c */
/* 1.1.6 31/10/2001 : auf neue definifa.idd umstellen;  A01GEPDM -> A01GEP, usw. in g_ifoart.c */
/* 1.1.7 17/11/2001 : Preiserhoehungen ( Abloesung DKART IFABAND ) MIT_PREIS_ERH_ in g_iartik.c */
/* 1.1.8 26/11/2001 : Preiserhoehungen (Fehler) IsZartpreisGelesen in g_iartik.c */
/* 1.1.9 09/12/2001 : g_iartik.c: #ifdef VOR_EURO: DATUMGUELTIGAB anders anfragen */
/* 1.2.0 05/01/2002 : Preisdatum vergleichen ZW_IFADAT_01012002 ZW_IFADAT_ARTDAT */
/* 1.2.1 10/01/2002 : Kommando ifa_ok aufufen */
/* 1.2.2 18/01/2002 : Preisdatum  ZW_IFADAT_ARTDAT: Ifa-Datum <= Artikelpreis-Datum ( vorher < )*/
/* 1.2.3 04/02/2002 : Fehler bei get_preis( ) in g_ifoart.c bei einstelligen Preisen */
/* 1.2.4 14/06/2002 : Preissenkung bei aut idem */
/* 1.2.5 15/10/2002 : Werte-Erweiterung bei A02NEGLIS um den Wert "02" */
/* 1.2.6 13/12/2002 : Feld BSSICHG in ZARTIKEL  */
/* 1.2.7 24/01/2003 : Felder ANBIETERABSCHLAG, AUTIDEMARTIKEL, */
/*                    FESTBETRARTIKEL, DATUM_ABSCHLAG in ZARTIKEL  */
/* 1.2.8 07.03.2003 : Neue Felder  REZEPTURARZNEI MEDIZINPRODUKT IMPFSTOFF CE_KENNZEICHEN  */
/*                    ARZNEIMITTEL KONTRAZEPTIVUM in ZARTIKEL ( - ) */
/*                    PREISSENKUNG lt. Heidicker in g_iartik.c */
/* 1.2.9 12/03/2003 : Felder A02IMPFST A02REZEPAM A02KONTRAZ in zifaart */
/* 1.3.0 13.06.2003 : Feld ZENTRALPPELIST in ZARTIKEL  */
/* 1.3.1 01/08/2003 : neues Feld EKORIGINALHS */
/* 1.3.2 06.11.2003 : Umstellung auf variable Datenbank  */
/* 1.3.3 13.11.2003 : Neues Feld HILFSM_VERBRAUCH in zartikel */
/* 2.0.1 03.12.2003 : Umstellung auf zifaoart ( Gesundheitsreform zum 01.01.2004 ) VOR_GH_REFORM_2004 */
/* 2.0.2 16.12.2003 : Test auf Preisaenderung (ZW_PRDIFF_OHNE_KEY) nur wenn keine Bestandslieferung */
/* 2.0.3 18.12.2003 : Rolle von A01AMPVAMG und A01AMPVSGB vertauschen in GetTaxKenn() */
/* 2.0.4 20.03.2004 : Neues Feld EAVP in zartpreis -> include <zartprei.h> aus g_iartik.c entfernen  */
/* 2.0.5 24.03.2004 : Neues Feld EAVP in zartpreis : Feld uebernehmen */
/* 2.0.6 20.08.2004 : RR: TAXPRUEFGROSSO immer setzen, wenn im zartikel auf '1' (unabhängig von IFA-Preis-Taxprüfung) */
/* 2.0.7 17.11.2004 : RR: wandeln mit neuer herstel-Struktur */
/* 2.0.8 06.04.2005 : TH: wandeln mit neuer zartikel-Struktur (psychotrop) */
/* 2.0.9 20.05.2005 : TH: neues Feld "Lifestyle"*/
/* 2.1.0 14.07.2005 : TH: pnamcode konvertiert in zifaart übernehmen*/
/* 2.2.0 03.04.2006 : TH: neue Felder A02AUSNREI, A02GENER, A02ABSCHL, A02SDB 
							Feldname von Ifa geändert: A00ANBNR --> A00ANBNR3 */
/* 2.3.0 29.08.2006 : TH: neue Felder A02NEM, A06PZNORIG */
/* 2.3.1 08.09.2006 : TH: Plausi-Prüfung für A06PZNORIG */
/* 2.3.2 09.11.2006 : TH: Aenderungen wg Mwst-Erhoehung */
/* 2.3.3 18.12.2006 : TH: bei Taxprüfgrosso-Artikeln preissenkung nur setzen, wenn sich auch der AEP tatsächlich senkt */
/* 2.3.4 12.04.2007 : TH: neue Verarbeitung für preissenkung + neues Feld datum_preissenkung */
/* 2.4.0 06.11.2007 : TH: IFA-Erweiterung - neue Felder: A02LEBENSM, A02DIAET, A02ZULREG; veraltet: A02CE, A02ABSCHL 
							neuer zwingender Fehler: Rewe-Sondergrosso-Preis */
/* 2.4.1 13.11.2007 : TH: neuer NZWING: NZ_NEM_DLM_LM_NEU + Verarbeitung zum Setzen dieses Fehlers.*/
/* 2.4.2 18.03.2008 : RR: zpreiser.h durch zpreiserhoehung.h ersetzt */
/* 2.4.3 07.07.2008 : RR: Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
						  Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 2.4.4 17.12.2008 : RR: Korrektur Rundungsfehler in kf_rund.c */
/* 2.4.5 29.09.2009 : TH: Anpassung von zwei nicht zwingenden Fehlermeldungen */
/* 2.5.0 01.03.2010 : TH: Umstellung IFA- Produkte von 20165 auf 20171. 
						  OP 43: nur nicht zwingender Fehler bei AEP==Grosso UND (Preise so schon im System ODER herst_prozent < 0) */
/* 2.5.1 02.11.2010 : TH: Amnog */
/* 2.5.3 12.11.2010 : TH: Amnog erst ab 2012 */
/* 2.5.4 29.11.2010 : TH: Amnog 2011 */
/* 2.6.0 27.04.2011 : TH: IFA 20174: 
							A09THGP statt A09THGP1 - A09THGP7 --> Versorgung ZUZAHL angepasst;  
							neue Felder A01GHABSCH, A01ERSTATT, A01SERSTAT;
							Umbennenung EAN --> GTIN; GEP --> APU;
						  bei Neuanlagen wird zartpreis.datumgueltigab auf den nächsten Tag gesetzt.*/
/* 2.6.1 07.12.2011 : TH: Amnog 2012 */
/* 2.7.0 07.05.2012 : TH: NZ_PRDIFF auch ermitteln, wenn es vorher schon andere Preisfehler gab. */
// 2.7.1 16.05.2012 : TH: IFA-20179 + PZN-8
// 2.7.2 25.07.2012 : TH: voodoo table header
// 2.7.3 25.09.2012 : TH: PZN8 - Codetyp "PZN8" auch für 7-stellige Neuanlagen schreiben
// 2.7.4 11.10.2012 : TH: PZN8- Korrektur für PznNF
// 2.7.5 09.11.2012 : TH: NZ_PZNNF_NVOR auch, wenn NF-PZN nicht in carticlecodes gefunden wurde
// 2.7.6 13.11.2012 : TH: Versorgung neue Felder zifa(o)art.a00pzn8 / a06pznnf8 / a06pznorig8
//						  neue Taxart "7" für AVP- Berechnung ab 2013
// 2.7.7 27.12.2012 : TH: neue Behandlung Erstattungsbetrag
// 2.8.0 15.03.2013 : TH: AIX build
// 2.8.1 25.03.2013 : TH: IFA 20190
// 2.8.2 04.06.2013 : TH: CR-Sales 2013 > SI0138 --> A02RESERV1 = §130 Sonderbehandlung Artikel mit reduziertem GEP buchen 
// 2.8.3 03.07.2013 : TH: neue Taxe 8 für AVP´s (Notdienstpauschale)
// 2.8.4 05.07.2013 : TH: NZ_NO_KOSMETIKUM
// 2.9.0 21.02.2014 : TH: IFA 20195 --> A02WIRKSTO, A02ELEKTRO, A00GTIN
// 2.9.1 17.03.2014 : TH: SR-14000586 = kein Erstattungsbetrag ab 01.04. mehr
// 2.9.2 10.04.2014 : TH: wandeln mit neuer zartikel/zartpreis-Struktur
// 2.9.3 02.07.2014 : TH: IFA 20199
// 2.9.4 07.04.2015 : TH: SR-15014334: Versorgung zpreiserhoehung
// 2.9.5 08.05.2015 : TH: IFA 20204


/* --------- Includes -------------- */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libscsvoodoo.h>
#include <phodate.h>


/* ----- Prototype --------- */

long GenIfaArtNeu( char *db, char *ili_file, char *idd_file, char *errmld, char *errmld_klinik );

/* ----- Eroeffnung --------- */

/* --- SET ISOLATION-Fehler bei SE -------------------------------------- */

#define SQL_SETISOLA_ERROR   (-554)

void CloseBase(  )
{
   SqlExecuteImm( "close database" );
}

long OpenBase( char *db, char *errmld )
{
   long s;
   
   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

   char base[50];
   strcpy( base, "database " );
   strcat( base, db );

   s = SqlExecuteImm( base );
   if ( s != 0 )
   {
      strcpy( errmld, base );
      strcat( errmld, ": " );
      strcat( errmld, DynErrmld() );
      return s;
   }

   s = SqlExecuteImm("set isolation to dirty read" );
   if ( s == SQL_SETISOLA_ERROR ) s = 0;
   if ( s != 0 )
   {
     strcpy( errmld, "set isolation: " );
     strcat( errmld, DynErrmld() );
     CloseBase( );
     return s;
   }

   s = SqlExecuteImm( "SET LOCK MODE TO WAIT 10" );
   if ( s == SQL_SETISOLA_ERROR ) s = 0;
   if ( s != 0 )
   {
     strcat( errmld, "set lock mode: ");
     strcat( errmld, DynErrmld() );
     CloseBase( );
     return s;
   }
   return 0;
}


void UpdateStatistics( char *relation )
{
   char sql[100];
   strcpy( sql, "update statistics for table " );
   strcat( sql, relation );
   SqlExecuteImm( sql );
}

/* ---------------- Programm-Ausahl ----------------- */

static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

static void LadeUsage( char *buf )
{
  strcat( buf, "1. zpiartik 1 database ili-Verzeichnis [idd-Verzeichnis]\n" \
               "   laedt die ifadatei in die Relation zifa\n"\
               "   ili-Verzeichnis: Pfadname des ili-Verzeichnisses\n" \
               "   idd-Verzeichnis: Pfadname des idd-Verzeichnisses\n" );
}

void ProgUsage( char *buf )
{
   Usage( buf );
   LadeUsage( buf );
}


long ProgAuswahl( int argc, char *argv[], char *buf, char *buf_klinik )
{
   long s;

   switch ( *argv[0] )
    {
      case '1':
        if ( argc == 3 )
        {
           s = GenIfaArtNeu( argv[1], argv[2], ".", buf, buf_klinik );
        }
        else if ( argc == 4 )
        {
           s = GenIfaArtNeu( argv[1], argv[2], argv[3], buf, buf_klinik );
        }
        else
        {
          s = 1;
          Usage( buf );
          LadeUsage( buf );
        }
        break;

      default:
        s = 1;
        strcpy( buf, "Programm-Teil: " );
        strcat( buf, argv[0] );
        strcat( buf, " nicht vorhanden" );
        break;
     }
   return s;
}


