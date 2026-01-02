
/* ---------------------------------------------------------------------- *
 *                         Z P I G N A R T . C                            *
 * ---------------------------------------------------------------------- *
 * Projekt:  Einkauf                                                      *
 * Gruppe:   Generiert die Artikel aus IFA                                *
 * ---------------------------------------------------------------------- *
 * Autor  :  Schmitt                                                      *
 * Anfang :  28.06.1998                                                   *
 * Update :                                                               *
 * ---------------------------------------------------------------------- */
#include "../../../cdm_version.h"

const char* getVersion()
{
    // in binary embedded full version string
    return "@(#)PHOENX Stand: " CDM_VERSION " - 2.9.2: zpignart 10.12.2024 : GW";
}

static char *Programm = "zpignart";

/*!
\page page19 zpignart - Generiert die Artikel aus IFA
___________________________________________________________________________
\version	2.9.2
\date		10.12.2024
\internal
- GW: - CPR-240818 - support for the new ifa versions 248 and 252
        New fields processed: A02MEDCG, A05LGTMPB, A01B130B1C, A01DAT78, A01RAB130A, A01ZUZAH61
        Modified field processes: A02EUNOVEL, A06PZNORIG, A05KKETTE, A05TMAX
\endinternal

___________________________________________________________________________
\version	2.9.1
\date		26.08.2024
\internal
- GW: - CPR-240206 - New messages and new processes for the following fields
                     A02SDB, A02PSM, A05VFDAT, A05LZEIT, A02BIOZID,
                     A02BIOSIEG, BATTREG, A02EUNOVEL, A02APPFL, A02VSPFL
\endinternal

___________________________________________________________________________
\version	2.9.0
\date		28.03.2024
\internal
- GW: - CPR-231102 - New IFA Version support 20244
        New fields processed: A02AMDARKI, A02AMAUFFB, A02AMBEKI, A02AMVEKRW, A01DAPU78, A02D130A18
        Modified fields and interpretations: A02ATMP, A02AUSIMPF, A02EUNOVEL, A02AMNOG, A02PRSTRMO
                                             A02BATTREG, A02PSM, A02SDB, A02BTM
\endinternal

___________________________________________________________________________
\version	2.8.9
\date		22.02.2024
\internal
- DK: - CPR-220839 - New IFA Version support 20240
        New fields processed A00UIDIDI, A02SWUNDB, A02ATMP, A02EUNOVEL, A2AUSIMPF, A02ORDRUG, A02BEDZUL, A02ZULAUSN, A02AMNOG, A00ZINNR7, A00EOVNR7, A00NTIN, A00GTIN, A02PRSTRMO
        Modified fields and interpretations: A02 ELEKTRO, A02 STIFEAR, A02BATTREG, A02WEEEREG
        Additional changes for duplicate checks on EAN
        Additional checks for IFA full data import regarding existing pricechecks, not completed
\endinternal

___________________________________________________________________________
\version	2.8.8
\date		01.02.2024
\internal
- DK: - CPR-231102 Vorabversion neue IFA Version 20244
        A02EB130B - Kennzeichen Arzneimittel mit Erstattungsbetrag § 130b SGB V (A02EB130B): Ergänzung Wert 03
        A0247AMG - Kennzeichen Tierarzneimittel-Abgabemengen-Register (TAR) (A0247AMG): Änderung Wert 01 und Ergänzung Wert 02 / 03
\endinternal

___________________________________________________________________________
\version	2.8.7
\date		25.11.2022
\internal
- MH: CPR-220839 IFA 20236
      (Teil 1: neue zulaessige Werte für A00ATYP und A02EB130B)
\endinternal
___________________________________________________________________________
\version	2.8.6
\date		14.08.2019
\internal
- TH: SR-19083302 --> setzen rezeptpfl / apothekenpfl / vertrbind_ifa auf Basis von A02MP, A02APPFL, A02VSPFL
- TH: A02TIERAM wird wieder in zartikel.tierarznei übernommen
\endinternal
___________________________________________________________________________
\version	2.8.5
\date		27.03.2019
\internal
- TH: init zartikel.chargenartikel bei Neuanlagen in DE & AT
\endinternal
___________________________________________________________________________
\version	2.8.4
\date		12.03.2019
\internal
- TH: Bugfix --> Übernahme zifaart.a11veripfl nur für Werte > 0; zpznpflege für NTIN´s nicht bei Neuanlagen.
\endinternal
___________________________________________________________________________
\version	2.8.3
\date		14.02.2019
\internal
- TH: Übernahme zifaart.a11veripfl --> zartikel.datum_fmdpflicht
\endinternal
___________________________________________________________________________
\version	2.8.2
\date		08.02.2019
\internal
- TH: zartikel.chargenartikel is not reset automatically anymore
\endinternal
___________________________________________________________________________
\version	2.8.1
\date		06.11.2018
\internal
- TH: CPR-180813 IFA 20219
\endinternal
___________________________________________________________________________
\version	2.8.0
\date		22.02.2018
\internal
- - TH: CPR-171513 IFA 20215
\endinternal
___________________________________________________________________________
\version	2.7.0
\date		21.04.2017
\internal
- - TH: CR-17D015 IFA 20212
\endinternal
___________________________________________________________________________
\version	2.6.9
\date		21.05.2016
\internal
- TH: CR-16D007: IFA-20208
\endinternal

___________________________________________________________________________
\version	2.6.8
\date		16.07.2015
\internal
- TH: wandeln mit neuer zartikel-Struktur
\endinternal
___________________________________________________________________________
\version	2.6.7
\date		21.05.2015
\internal
- TH: weitere Anpassungen für IFA-20204
\endinternal
___________________________________________________________________________
\version	2.6.6
\date		08.05.2015
\internal
- TH: IFA-20204
\endinternal
___________________________________________________________________________
\version	2.6.5
\date		08.07.2014
\internal
- TH: Berücksichtigung herstel.vertriebsclubnr --> zartwg.art F
\endinternal
___________________________________________________________________________
\version	2.6.4
\date		07.07.2014
\internal
- TH: IFA-20199
\endinternal
___________________________________________________________________________
\version	2.6.3
\date		23.05.2014
\internal
- TH: Übernahme Wirkstoff nicht mehr von zartikel.wirkstoff_nr, sondern aus zartwg.art=E
\endinternal

*/

/* 1.1.5 21.12.2000 V_PROTO_VERTEIL bei zartikel und zartpreis ( vorher V_PROTOKOL ) */
/* 1.1.6 23.01.2001 || nb_plausi[i] == '9' in  nbr_hers.c ( vorher nur Abfrage auf '0' ) */
/* 1.1.7 06.07.2001 neue Felder in zartikel NAHRUNGSTEST, NAHRUNGSERGAENZUNG */
/* 1.1.8 12.09.2001 Make_NemArtikel */
/* 1.1.9 09.12.2001 : art_prot.c: #ifdef VOR_EURO: DATUMGUELTIGAB anders anfragen */
/* 1.2.0 24.05.2002 ZARTIKEL: PREISSENKUNG,  --- wpp_ --- */ 
/* 1.2.1 25.06.2002 AUTIDEM */ 
/* 1.2.2 26.09.2002 ARTIKEL_NR_HERST */ 
/* 1.2.3 15/10/2002 Werte-Erweiterung bei A02NEGLIS um den Wert "02" */
/* 1.2.4 10/12/2002 Erweiterung ZSPANNENKUERZ ( nbr_art.c g_autidm.c ) */
/* 1.2.5 13/12/2002 Feld BSSICHG in ZARTIKEL  */
/* 1.2.6 19/12/2002 Feld BSSICHG automatisch setzten */
/* 1.2.7 24/01/2003 Felder ANBIETERABSCHLAG, AUTIDEMARTIKEL, */
/*                  FESTBETRARTIKEL, DATUM_ABSCHLAG in ZARTIKEL  */
/* 1.2.8 07/03/2003 Neue Felder  REZEPTURARZNEI MEDIZINPRODUKT IMPFSTOFF CE_KENNZEICHEN  */
/*                  ARZNEIMITTEL KONTRAZEPTIVUM in ZARTIKEL ( + ) */
/*                  PREISSENKUNG lt. Heidicker in nbr_art.c */
/* 1.2.9 12/03/2003 Make_Arzneimittel() Make_Medizinprodukt() Make_CE() Make_Impstoff() */
/*                  Make_Rezepturarznei() Make_Kontrazeptivum() in zart_gen.c */
/* 1.3.0 02/04/2003 Neue Ausnahmen in IsBSSichG() ( g_bssg.c ) */
/* 1.3.1 13/06/2003 neues Feld ZENTRALPPELIST */
/* 1.3.2 17/07/2003 neues Feld ZENTRALPPELIST mit Hersteller-ZENTRALPPELIST versorgen */
/*                  neuer Modul rd_herst.c, in nbr_art.c und ebenfalls in g_autidm.c benutzt */
/* 1.3.3 01/08/2003 neues Feld EKORIGINALHS */
/* 1.3.4 06.11.2003 Umstellung auf variable Datenbank  */
/* 1.3.5 13.11.2003 Neues Feld HILFSM_VERBRAUCH in zartikel */
/* 2.0.1 03.12.2003 Umstellung auf zifaoart ( Gesundheitsreform zum 01.01.2004 ) VOR_GH_REFORM_2004 */
/* 2.0.2 18.12.2003 Rolle von A01AMPVAMG und A01AMPVSGB vertauschen in GetTaxKenn() */
/* 2.0.3 24.12.2003 bssichg entfaellt wieder, da neues Gesetz */
/*                  DATUM_AH von IFA nur uebernehmen, wenn DATUM_AH.ZARTIKEL = 0 ( Sonderfall )*/  
/* 2.0.4 30.12.2003 DATUM_AH von IFA stets uebernehmen ( wie vor dem 24.12.2003 ) */  
/* 2.0.5 17.02.2004 Pflege artikelz, artpreis ausschalten (MIT_ARTIKELZ_PFLEGE, MIT_ARTPREIS_PFLEGE) */
/*                  Fehler taxpfl bei Protokoll in ifa_Zeile_2() (ifa_prot.c) */
/*                  Fehler taxpfl bei spannenkuerzung und autidem in Do_All() (nbr_art.c) */
/* 2.0.6 10.03.2004 Abhaengigkeit REZEPTPFL, RABATTFAEHIG ( zart_gen.c: VOR_09_03_2004 ) */
/*                  AUTIDEMARTIKEL durch FESTBETRARTIKEL ersetzen (nbr_art.c) */
/* 2.0.7 15.03.2004	ZENTRALPPELIST nicht vom Herteller uebernehmen wenn BTM (nbr_art.c) */
/* 2.0.8 20.03.2004 Neues Feld EAVP in zartpreis ( nur neu compiliert ) */
/* 2.0.9 24.03.2004 Neues Feld EAVP in zartpreis bearbeiten */
/* 2.1.0 06.04.2004	ZENTRALPPELIST nicht vom Herteller uebernehmen, */
/*                  wenn Kuehlkette oder unter 8 Grad (nbr_art.c) */
/* 2.1.1 19.05.2005 Lifestyle Tabelle mit versorgen */
/* 2.1.2 12.07.2005 Zpznpflege schreiben bei EAN Änderung */
/* 2.1.3 14.07.2005 Artikellangname und abgabebest_if uebernehmen */
/* 2.1.4 19.07.2005 Init auf GS_LICHTGESCH */
/* 2.1.5 21.11.2005 KH Init neue Artikelstammfelder */
/* 2.1.6 03.04.2006 KH Neue Felder AMG_AUSNAHMEREG,ZULASS_GENER,ABSCHLAG_130,SIDABLATT */
/* 2.1.7 24.04.2006	KH Aussetzen ABGABEBEST_IFA laut Vorgabe angepasst */
/* 2.1.8 28.04.2006 KH Originalartikel + Modifikation NEM	*/
/* 2.1.9 29.03.2007 KH Mwst-Kz für keine MwSt von ' ' auf '2' */
/* 2.2.0 10.04.2007 KH Preissenkungen */
/* 2.2.1 07.11.2007 KH Neue IFA Felder A02LEBENSM und A02DIAET + Anpassen Nahrungstest,Nahrungsergaenzung Verarbeitung*/
/* 2.2.2 07.07.2008 RR Änderungen im logfile.c wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine,
					   Ausgabe Log auch bei Aufruf aus Windows (EkZdp) */
/* 2.2.3 12.09.2008 KH Übernahme Maße und Gewicht nur wenn Kennzeichen Mess-/Wiegeeinheit nicht gesetzt */
/* 2.2.4 12.11.2008 RR füllen zartikel.chargenartikel in Abhängigkeit von tierarznei und tfg */
/* 2.2.5 17.12.2008 RR Korrektur Rundungsfehler in kf_rund.c */
/* 2.2.6 23.12.2008 TH Rezeptpflicht automatisch auch dann setzen, wenn Artikel bereits BTM ist. */
/* 2.2.7 14.01.2009 RR Init Felder biozid_verord und pflanzenschutz_verord */
/* 2.2.8 17.03.2009 RR Umsetzung Chargenartikel nach hinten verschoben, da bei Neuanlage das Tierarznei- */
/*					   Feld ggfs. vom Vorgänger-Artikel übernommen wird und das nicht berücksichtigt war */
/* 2.2.9 24.11.2009 RR Init neues zartikel-Feld bestell_nur_ozek */
/* 2.3.0 01.03.2010 TH Umstellung IFA- Produkte von 20165 auf 20171;
						OP 52: carticlecodes (typ 7) aus Feld A02ZULREG versorgen;
						OP 24: automatische Übernahme von Infos bei IFA-Reimport-Neuzugängen;
						OP 43: Errechnung Grosso aus AEP - herst_prozent */
/* 2.3.1 16.08.2010 TH Schreiben CArticleCodes bei Artikel- Neuanlagen */
/* 2.3.2 02.12.2010 TH zartikel.taxpfl = 3 darf nicht durch 2 überschrieben werden */
/* 2.3.3 14.01.2011 TH zartikel.preissenkung in Abhängigkeit von zartikel.festbetrag1 (nicht mehr festbetrartikel) setzen.*/
/* 2.3.4 09.03.2011 TH Make_BESTELL_NICHT_AUSL */
/* 2.3.5 06.04.2011 TH CR-186 5 neue Felder in herstel --> Basis für automatischer Versorgung Artikelstamm- KZ */
// 2.3.6 11.04.2011 TH: CR-186 Beim Herstellerwechsel die Artikelstamm-Kennzeichen "EK nur Original-Herst." und/oder"ZWH nur OZEK" lt. Hersteller setzen, aber nicht lt. Hersteller löschen.
/* 2.4.0 27.04.2011 TH: IFA 20174: 
							neue Felder A01GHABSCH --> zartikel.BSSICHG, A01ERSTATT --> zartikel.ERSTATTBETRAG;	
							Ermittlung zartikel.taxpfl abhängig von A01GHABSCH.*/
// 2.4.1 28.11.2011 TH: Behandlung von A01GHABSCH für die Übergangszeit 01.-15.12. wg Amnog- Umstellung
//						Setzen des Tagesdatums (nicht des Gültigkeitsdatums) in zartikel.datum_anlage
// 2.4.2 07.12.2011 TH: AMNOG 2012
// 2.4.3 16.05.2012 TH: IFA-20179 + PZN-8
// 2.4.4 25.07.2012 TH: voodoo table header
// 2.4.5 11.10.2012 TH: neues Vorgehen PZN 8
// 2.4.6 13.11.2012 TH: Anpassung Protokolle (zpignart + zpifagen) auf PZN 8
// 2.4.7 27.12.2012 TH: neue Behandlung Erstattungsbetrag
// 2.5.0 15.03.2013 TH: AIX build
// 2.5.1 25.03.2013 TH: IFA 20190
// 2.5.2 04.06.2013 TH: CR-Sales 2013 > SI0138 --> zartpreis.disc_deduced_yet = §130 Sonderbehandlung Artikel mit reduziertem GEP buchen 
// 2.5.3 05.07.2013 TH: Versorgung zartikel.kosmetikum
// 2.6.0 25.02.2014 TH: IFA-2019
// 2.6.1 17.03.2014 TH: SR-14000586 = neues Feld "Spanne" auf Protokoll; kein Erstattungsbetrag ab 01.04. mehr
// 2.6.2 10.04.2014 TH: wandeln mit neuer zartikel/zartpreis-Struktur
// 2.6.3 23.05.2014 TH: Übernahme Wirkstoff nicht mehr von zartikel.wirkstoff_nr, sondern aus zartwg.art=E
// 2.6.4 07.07.2014 TH: IFA-20199
// 2.6.5 08.07.2014 TH: Berücksichtigung herstel.vertriebsclubnr --> zartwg.art F
// 2.6.6 08.05.2015 TH: IFA-20204
// 2.6.7 21.05.2015 TH: weitere Anpassungen für IFA-20204
// 2.6.8 16.07.2015 TH: wandeln mit neuer zartikel-Struktur


/* --- Include-Dateien einbinden ---------------------------------------- */

#include <stdio.h>                                /* C-Standard-Libraries */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <libscsvoodoo.h>


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

   char base[50];
   strcpy( base, "database " );
   strcat( base, db );

   /* dummy call to prevent from optimizing version string out of binary */
   const char* version = getVersion();

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

/* ---------------- Programm-Ausahl Prototype ----------------- */
long GenArtLoop ( char *db, char *param1, char *param2, char *param3, char *param4,
                  char *buf );
void GenArtUsage( char *buf, char *prog );

long Reset_PL_C_HERSTNUM_Loop  ( char *db, char *c_ifadatum, char *buf );
void Reset_PL_C_HERTSNUM_Usage ( char *buf, char *prog );

long Zifaart_Protokol_Loop  ( char *db, char *c_ifadatum, char *verzeichnis, char *buf );
void Zifaart_Protokol_Usage ( char *buf, char *prog );


/* ---------------- Programm-Ausahl ----------------- */

static void Usage( char *buf )
{
   strcpy( buf, "usage:\n" );
}

void ProgUsage( char *buf )
{
   Usage( buf );
   GenArtUsage( buf, Programm );
   Reset_PL_C_HERTSNUM_Usage( buf, Programm );
   Zifaart_Protokol_Usage( buf, Programm );
}

long ProgAuswahl( int argc, char *argv[], char *buf )
{
   long s;

   if ( strlen( argv[0] ) != 1 )
   {
     s = 1;
     strcpy( buf, "Programm-Teil: " );
     strcat( buf, argv[0] );
     strcat( buf, " nicht vorhanden" );
     return 1;
   }

   switch ( *argv[0] )
    {
      case '0':
      case '1':
		/* Reihenfolge argv[1], argv[0], ist richtig !!!!!!  */
        if ( argc == 4  )
           s = GenArtLoop( argv[1], argv[0], argv[2], argv[3], NULL,    buf );
        else if ( argc == 5 )
           s = GenArtLoop( argv[1], argv[0], argv[2], argv[3], argv[4], buf );
        else
        {
          s = 1;
          Usage( buf );
          GenArtUsage( buf, Programm );
        }
        break;

      case '2':
        if ( argc == 3 )
        {
          s = Reset_PL_C_HERSTNUM_Loop ( argv[1], argv[2], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          Reset_PL_C_HERTSNUM_Usage( buf, Programm );
        }
        break;

      case '3':
        if ( argc == 3 )
        {
          s = Zifaart_Protokol_Loop( argv[1], argv[2], NULL, buf );
        }
        else if ( argc == 4 )
        {
          s = Zifaart_Protokol_Loop( argv[1], argv[2], argv[3], buf );
        }
        else
        {
          s = 1;
          Usage( buf );
          Zifaart_Protokol_Usage( buf, Programm );
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


