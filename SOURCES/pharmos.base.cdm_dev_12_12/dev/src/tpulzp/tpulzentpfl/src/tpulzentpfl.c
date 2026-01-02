/******************************************************************************/
/*     Hauptmodul: tpulzentpfl                                                */
/*         Source: tpulzentpfl.cpp                                            */
/*          Autor: A. Schmidt-Rehschuh                                        */
/*       Erstellt: 27.03.1998                                                 */
/*        Sprache: C/Esql-C                                                   */
/*        Erzeugt: manuell                                                    */
/*        Aufgabe: entladen auf dezap aus zentraler artikelpflege             */
/*                                                                            */
/******************************************************************************/

/*** VERSION ******************************************************************/
#include "../../../cdm_version.h"

static char *SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 5.5.5 : tpulzentpfl : 04.09.2024 ";
static char *VERSION = "5.5.5 (04.09.2024)"; 

/*!
\page page37 tpulzentpfl
___________________________________________________________________________
\version	5.5.5
\date		04.09.2024
\internal
- RR: neue Satzart 03 (DKSOA), versorgen aus cbaselistarticles
\endinternal
\~german   
neue Satzart 03 (DKSOA), versorgen aus cbaselistarticles
\~english 
new record type 03 (DKSOA), filled from cbaselistarticles
\~
___________________________________________________________________________
\version	5.5.4
\date		29.11.2023
\internal
- RR: neues Feld ZAPMEDPROD, versorgen aus zartikel.medizinprodukt
\endinternal
\~german   
neues Feld ZAPMEDPROD, versorgen aus zartikel.medizinprodukt
\~english 
new field ZAPMEDPROD, filled from zartikel.medizinprodukt
\~
___________________________________________________________________________
\version	5.5.3
\date		20.01.2022
\internal
- RR: neue Felder ZAPCMI und ZAPSNT, versorgen aus 2 neuen zartikel-Feldern
	  Aktivkennzeichen in DKRBF 1:1 versorgen statt Switch auf J/N
\endinternal
\~german   
neue Felder ZAPCMI und ZAPSNT, versorgen aus 2 neuen zartikel-Feldern
Aktivkennzeichen in DKRBF 1:1 versorgen statt Switch auf J/N
\~english 
(changes for Germany, Austria & Switzerland)
\~
___________________________________________________________________________
\version	5.5.2
\date		22.09.2021
\internal
- RR: in der Schweiz das neue Feld zartpreis.agp in ZAPAEP stellen 
\endinternal
\~german   
in der Schweiz das neue Feld zartpreis.agp in ZAPAEP stellen 
\~english 
(change for Switzerland)
\~
___________________________________________________________________________
\version	5.5.1
\date		03.08.2021
\internal
- RR: neues Feld ZAPHAEMO, versorgen aus zartikel.tfg
	  in der Schweiz das neue Feld zartpreis.agp in ZAPAEP stellen --> vorerst wieder deaktiviert
	  Bugfix bzgl. DKAIN (AIN-WIRK 'N' statt 'C' in cobolbuf.h)
\endinternal
\~german   
neues Feld ZAPHAEMO, versorgen aus zartikel.tfg
in der Schweiz das neue Feld zartpreis.agp in ZAPAEP stellen --> vorerst wieder deaktiviert
\~english 
(changes for Germany & Switzerland)
\~
___________________________________________________________________________
\version	5.5.0
\date		27.04.2021
\internal
- RR: zartikel.mvdaartikel in ZAP-POOL für Deutschland
	  ZAPVAT mit '0' initialisieren, falls kein zartpreis-Satz gefunden
	  neue Satzart 55 aus cregisters (für BG)
	  für BG Ministerium-Produktcode in ZAP-WIRK stellen
	  Deaktivierung Satzart 10 (DKGFG)
\endinternal
\~german   
(Aenderung fuer Bulgarien)
\~english 
transfer INN to Pharmos
\~
___________________________________________________________________________
\version	5.4.10
\date		08.12.2020
\internal
- RR: zartikel.kuehlartikel in ZAP-KUEHLKZ
\endinternal
\~german   
Kuehlkennzeichen nach Pharmos übertragen
\~english 
transfer coolage flag to Pharmos
\~
___________________________________________________________________________
\version	5.4.9
\date		18.03.2020
\internal
- RR: neue Satzart 54 aus cpromotions
\endinternal
\~german   
(Aenderung fuer Kroatien)
\~english 
transfer promotion data to Pharmos
\~
___________________________________________________________________________
\version	5.4.8
\date		22.01.2020
\internal
- RR: Satzart 46 deaktivert (ccustservices --> DKLLV)
      zartikel.datum_fmdpflícht --> ZAP-SHDAT
	  cdiscform.relevant_babr   --> ZAP47BABRREL 
	  zartswitzerland.migcd		--> ZAP-MEDK
\endinternal
\~german   
(interne Anpassung)
FMD-Pflicht-Datum nach Pharmos übertragen
in der Schweiz Bonusabrechnungs-Relevanz für Rabattformen nach Pharmos übertragen
in der Schweiz Kennzeichen für MiGeL versorgen aus Mig-CD
\~english 
(internal change)
(change only relevant for Germany)
(2 changes only relevant for Switzerland)
\~
___________________________________________________________________________
\version	5.4.7
\date		29.10.2019
\internal
- RR: für Bulgarien artve.ORIGINALKARTON in ZAPMINM
\endinternal
\~german   
Änderung nur relevant für Bulgarien
\~english 
in Bulgaria copy value from ORIGINALKARTON to field MINM
\~
___________________________________________________________________________
\version	5.4.6
\date		09.10.2019
\internal
- RR: neues Vertriebsbindung Frankreich in ZAPVBC
\endinternal
\~german   
Änderung nur relevant für Frankreich
\~english 
put new distribution restriction for France in ZAPVBC
\~
___________________________________________________________________________
\version	5.4.5
\date		31.10.2018
\internal
- RR: neues Feld ZAP-FMDREL aus zartikel.fmd_relevant versorgen
	  neue Felder ZAP-ZMHSGEP & ZAP-ZMHSAEP aus zartpreis versorgen
\endinternal
\~german   
neues Feld ZAP-FMDREL aus zartikel.fmd_relevant versorgen
\~english 
fill new field ZAP-FMDREL out of zartikel.fmd_relevant
\~
___________________________________________________________________________
\version	5.4.4
\date		19.06.2018
\internal
- RR: neues Feld ZAP-VAT 1:1 aus zartpreis.ke_mwst versorgen
\endinternal
\~german   
neues Feld ZAP-VAT 1:1 aus zartpreis.ke_mwst versorgen
\~english 
fill new field ZAP-VAT 1:1 out of zartpreis.ke_nwst
\~
___________________________________________________________________________
\version	5.4.3
\date		26.02.2018
\internal
- RR: kein Setzen von ZAP-CHARGE = 'A' mehr (wird im Pharmos nicht mehr benoetigt)
	  daraus resultierend Verarbeitung cgibatchentry komplett deaktiviert
	  versorgen neue DEZAP-SA 53 (DKAUA) aus cordertype & Co.
\endinternal
\~german   
kein Setzen von ZAP-CHARGE = 'A' mehr (wird im Pharmos nicht mehr benoetigt)
versorgen neue DEZAP-SA 53 (DKAUA) aus cordertype & Co.
\~english 
\~
___________________________________________________________________________
\version	5.4.2
\date		16.11.2017
\internal
- RR: Default für Parameter MAX_DAY von 28 auf 99 erhöht (längeres Speichern z**pflege),
	  Parameter-Von-Datum statt Bis-Datum für Kalkulation lDateCdiscount verwenden 
	  (SR-17107535: beim Rausschicken am Monatsletzten wurden Sätze des aktuellen Monats gelöscht)
\endinternal
\~german   
Default für Parameter MAX_DAY von 28 auf 99 erhöht (längeres Speichern z**pflege),
Parameter-Von-Datum statt Bis-Datum für Kalkulation lDateCdiscount verwenden 
(SR-17107535: beim Rausschicken am Monatsletzten wurden Sätze des aktuellen Monats gelöscht)
\~english 
\~
___________________________________________________________________________
\version	5.4.1
\date		04.07.2017
\internal
- RR: neues Kriterium für Vergabe ZAP-CHARGE = 'E' in Deutschland,
	  neues Kriterium für Vergabe ZAP-CHARGE = 'E' in der Schweiz,
	  anderer Datumsparameter fuer startBrowseCdiscount_Pzn (Übertragung Monatsrabatte, 
	  die schon abgelaufen sind, aber im laufenden Monat noch gültig waren)
\endinternal
\~german   
neues Kriterium für Vergabe ZAP-CHARGE = 'E' in Deutschland, 
neues Kriterium für Vergabe ZAP-CHARGE = 'E' in der Schweiz,
Übertragung von im aktuellen Monat abgelaufenen Rabatten
\~english 
\~
___________________________________________________________________________
\version	5.4.0
\date		03.03.2017
\internal
- RR: 3 neue Felder in DKART-Struktur,
	  neues Feld in DKCRR-Struktur,
	  neue Struktur DKRBF,
	  neue Struktur DKSPS
\endinternal
\~german   
3 neue Felder in DKART-Struktur (für Apotheken-Automat Deutschland, Defekteinstufung Österreich)
neues Feld Retouren-Löschdatum für Chargenrückrufe
neue Strukturen für Rabattformen und Speditionsdaten
\~english 
3 new fields in DKART structure (for Germany and Austria)
new field returns delete date for batch recalls
new structures for rebate forms and shipper data
\~
___________________________________________________________________________
\version	5.3.3
\date		08.07.2016
\internal
- RR: neues Feld Maximum in DKRGR-Struktur,
	  neue Struktur DKFOK
\endinternal
\~german   
neues Feld Maximum in DKRGR-Struktur (für Frankreich)
neue Struktur für Formularkennzeichen
\~english 
new field maximum in DKRGR structure (for France)
new structure for form types
\~
___________________________________________________________________________
\version	5.3.2
\date		22.06.2016
\internal
- RR: Aufbereitung Hersteller-Telefon und -Telefax korrigiert (falls nur Vorwahl gepflegt war, wurden dahinter binäre Nullen generiert) 
\endinternal
\~german   
interne Anpassung bei Aufbereitung Hersteller-Telefon und Telefax
\~english 
internal change in calculation of manufacturer phone and fax
\~
___________________________________________________________________________
\version	5.3.1
\date		16.03.2016
\internal
- RR: je ein neues Feld in den Satzarten 12 & 26 versorgen 
\endinternal
\~german   
übertragen VIS-Gruppierung auf Einkaufsgruppenebene sowie Kennzeichen GEP-Druck auf Rechnung auf Rabattgruppenebene ans Pharmos
\~english 
transfer to Pharmos VIS grouping on purchasing group level and GEP-print-on-invoice-flag on rebate group level
\~
___________________________________________________________________________
\version	5.3.0
\date		29.02.2016
\internal
- RR: 2 neue Satzarten 48 & 49 aus cstoragecriteria und cintrastatcountry versorgen 
\endinternal
\~german   
versorgen neue Strukturen für Einlagerungskriterien und Intrastat-Länder
\~english 
transfer new structures for storage criteria and Intrastat countries
\~
___________________________________________________________________________
\version	5.2.4
\date		12.02.2016
\internal
- RR: neues Feld ZAPGSRAUM aus csafetydatasheet versorgen 
\endinternal
\~german   
neues Feld Gefahrstoffraum nach Pharmos übertragen
\~english 
transfer new field danger good store room to Pharmos
\~
___________________________________________________________________________
\version	5.2.3
\date		26.11.2015
\internal
- RR: neue LIF-P09-Tabelle fuer Satzart 20 aus herstellersalescondition versorgen 
\endinternal
\~german   
Um bestimmte herstellerbezogene Werte, die momentan hart in einigen Pharmos-Programmen hinterlegt sind,
konfigurierbar zu machen, werden die Werte aus der neuen ZDP-Verwaltung ins Pharmos übertragen
\~english 
In order to make manufacturer-related values that are currently located in some Pharmos programs
configurable, these values from the new ZDP maintenance are transferred towards Pharmos
\~
___________________________________________________________________________
\version	5.2.2
\date		20.11.2015
\internal
- RR: ZAP-MWST in Österreich 1:1 aus zartpreis versorgen (analog Frankreich, Kroatien & Prewhole-CH) 
\endinternal
_______________

\version	5.2.1
\date		16.11.2015
\internal
- RR: 3 neue Felder in DEZAP-Satzart '00'
\endinternal
_______________

\version	5.2.0
\date		07.07.2015
\internal
- RR: 2 neue DEZAP-Satzarten 45 & 46, neues Feld herstel.r_name2 nach DKLIF übertragen
\endinternal
_______________

\version	5.1.9
\date		13.05.2015
\internal
- RR: neues Feld herstel.r_name2 nach DKLIF übertragen
\endinternal
_______________

\version	5.1.8
\date		10.02.2015
\internal
- RR: ein neues Feld von cmonthdiscsort nach DKMRS übertragen
\endinternal
_______________
*/

/* 2.0.1   08.11.2003 : Umstellung auf variable Datenbank  */
/* 2.0.2   28.10.2004 : 2 neue Felder (arzneimittel, ekoriginalhs) */
/* 2.0.3   11.01.2005 : Beginn Ablösung dezapzep.h durch HSQL-generierte Header */
/*						(Tabellen zartwg, zartsekbez, zartfeb2, herstel, ean) */
/* 2.1.0   13.01.2005 : Abschluss o.a. Ablösung (Tabellen zartpreis, zartikel) */
/* 2.1.1   02.03.2005 : Verarbeitung zartaustria für Österreich */
/* 2.2.0   10.03.2005 : Verarbeitung zgrppflege (WGR-Stammänderungen) und als */
/*                      erste Stammdatei die zdkwgr in ZAP-Satzart 15 */
/* 2.2.1   11.03.2005 : Versorgung ZAP-PSS aus neuem zartikel-Feld Psychotrop */
/*                      Ausgabe aussagekraeftiger Displays am Ende */
/* 2.2.2   17.03.2005 : Verarbeitung zdkwgr-Löschungen */
/* 2.2.3   30.03.2005 : unterschiedliche ftdezaps pro Land aufrufen */
/* 2.3.0   04.04.2005 : neue DEZAP-Satzarten 16-19 aus zgrppflege */
/* 2.3.1   05.04.2005 : div. kleinere Korrekturen für Österreich */
/* 2.3.2   07.04.2005 : Volumen wird ab sofort gerundet (analog Pharmos) */
/* 2.3.3   14.04.2005 : eliminieren ZAPSKUBZ und ZAPMAM */
/* 2.3.4   26.04.2005 : neue DEZAP-Satzart 20 aus zgrppflege (DKLIF) */
/* 2.3.5   03.05.2005 : neue DEZAP-Satzart 21 aus zgrppflege (DKATX) */
/* 2.3.6   10.05.2005 : zartwg.art = '7' = KEYTXT (Schlüssel Artikeltext Österreich) */
/* 2.3.7   19.05.2005 : Kleinbuchstaben aus DKLIF-Bemerkung in Großbuchstaben umwandeln */
/* 2.4.0   20.05.2005 : Verarbeitung zpznpflege (Änderungen in "Artikel-Anhängseln") */
/* 2.4.1   22.06.2005 : neue DEZAP-Satzart 22 aus zpznpflege (DKCRR) */
/* 2.4.2   27.06.2005 : neues Feld rueck_mon_vor_verf in SIW und ORPA (nur Österreich) */ 
/* 2.4.3   01.07.2005 : Verarbeitung zartswitzerland für die Schweiz */
/* 2.4.4   04.07.2005 : Verarbeitung carticlelang für die Schweiz */
/* 2.5.0   08.07.2005 : Umstellung EAN-Verarbeitung auf zpznpflege (bisher wurde für jeden */
/*                      zapflege-Satz auch eine EAN in die DEZAP geschrieben, unabhängig */
/*                      davon, ob sie sich überhaupt geändert hat. Außerdem sind EAN- */
/*                      Löschungen niemals eingestellt worden) */
/* 2.5.1   15.07.2005 : erzeugen FEUKL = 'L ', wenn zartikel.gs_lichtgesch gesetzt ist */
/* 2.5.2   18.07.2005 : neue DEZAP-Satzart 13 aus zpznpflege (DKSTE) */
/* 2.5.3   19.07.2005 : neue DEZAP-Satzarten 23 & 24 aus zpznpflege (DKGAL) bzw. zgrppflege (DKGAH) */
/* 2.5.4   21.07.2005 : Korrektur beim Versorgen von KZAL2 Österreich (hat 1. Stelle von ANRH kaputtgemacht) */
/* 2.5.5   29.07.2005 : kein Filetransfer (ftdezap) mehr in der Schweiz */
/* 2.5.6   02.08.2005 : Filename nur dezap<?F>.dat ohne Datum (einfacher fuer ZBW), vorerst nur in CH, */
/*						sämtliche WriteToDezap*** durch einen WriteToDezap ersetzt */						
/* 2.5.7   04.08.2005 : Ausgabe eines 99er Satzes mit Summen pro Satzart */
/* 2.5.8   30.08.2005 : IHNR und IZLA versorgen (neue Spannenfelder für D) */
/* 2.5.9   13.10.2005 : Änderungen von 2.5.5 und 2.5.6 bzgl. ftdezap auch für Österreich */
/* 2.6.0   20.10.2005 : Änderungen von 2.5.5 und 2.5.6 bzgl. ftdezap nun generell */
/* 2.6.1   03.11.2005 : neue DEZAP-Satzart 25 aus zgrppflege (DKLID) */
/* 2.6.2   15.11.2005 : NRDATV und NRDATB eliminiert (analog VSE) */
/* 2.6.3   16.11.2005 : umfangreichere Aufrufinformationen ins Logfile */
/* 2.6.4   21.11.2005 : wandeln mit neuer cgalonam-Struktur (qty decimal statt integer), */
/*                      neues DEZAP-Feld "Elektro" */
/* 2.6.5   29.11.2005 : den Fall abfangen, dass Hersteller nicht gefunden (Neuanlage und Löschung an einem Tag) */
/* 2.6.6   08.02.2006 : WGRRGRP versorgen aus zartwg (art = 9), */
/*                      MWST nicht J/N für Frankreich */ 
/* 2.6.7   02.03.2006 : Schweiz-Abfragen um pps1pch erweitern */
/* 2.6.8   06.03.2006 : Verarbeitung zartfrance für Frankreich */
/* 2.6.9   14.03.2006 : Getränkesteuer mit '0' liefern statt 'N' */
/* 2.7.0   23.03.2006 : neue DEZAP-Satzart 08 aus zpznpflege (DKRIS) */
/* 3.0.0   29.03.2006 : Erweiterung DEZAP von 380 auf 500 Bytes */
/* 3.0.1   11.04.2006 : Änderung in GetStreet (memset) wg. falscher Straßenaufbereitung */
/* 3.0.2   19.06.2006 : 3 neue Felder in DEZAP */
/* 3.0.3   28.06.2006 : neue DEZAP-Satzart 12 aus zgrppflege (DKEGR) */
/* 3.0.4   15.08.2006 : neue DEZAP-Satzart 26 aus zgrppflege (DKRGR) */
/* 3.0.5   25.08.2006 : versorgen ZAPPAEND aus zautidemsperre */
/* 3.0.6   30.08.2006 : PAEND generell auf "N" setzen, wenn Artikel außer Handel ist */
/* 3.0.7   21.09.2006 : wandeln mit neuer zartfrance-Struktur (Vergrößerung code_lppr von 8 auf 15 Stellen) */
/* 3.0.8   28.09.2006 : neue DEZAP-Satzarten 27 aus zgrppflege (DKZAB) und 28 aus zpznpflege (DKRAB), */
/*						Fehlerkorrektur bei 6-stelligen Preisen (verschoben statt abgeschnitten) */
/* 3.0.9   19.10.2006 : Verarbeitung für Kroatien (neue Tabellen carticlecodes und zartcroatia) */
/* 3.1.0   02.11.2006 : ZAPPAEND-Versorgung aus zautidemsperre nur für Deutschland beschraenkt */
/* 3.1.1   14.11.2006 : Swissmedic-Registrierungsnummer in CH in die Therapiegruppe stellen, */
/*						ZAPPAEND in Kroatien anders versorgen (KZ für Euro-Umrechnungs-Preisänderung */
/* 3.1.2   15.11.2006 : in CH Therapiegruppe = '00000' (statt "0    ", wenn swissmedic_regnr = 0 */
/* 3.1.3   11.12.2006 : neue DEZAP-Satzart 29 aus zgrppflege (DKRAL) */
/* 3.1.4   13.12.2006 : auch in Prewhole CH Mwst-KZ direkt übertragen (nicht J/N) */
/* 3.1.5   18.12.2006 : andere langid in pps1pch (DE statt FR) */
/* 3.1.6   10.01.2007 : neue DEZAP-Felder aus zartikel und zartswitzerland für Prewhole CH */
/* 3.1.7   31.01.2007 : Umstellung DB Österreich von pps1ca auf pps1au */
/* 3.1.8   06.03.2007 : neue Felder für Frankreich versorgen */
/* 3.1.9   27.03.2007 : neue DEZAP-Satzart 30 aus zgrppflege (DKSER) */
/* 3.2.0   02.04.2007 : Umstellung DB Schweiz von pps1cch auf pps1ch */
/* 3.2.1   09.05.2007 : setzen NLH = 'J', wenn Datum wieder lieferbar noch nicht erreicht */
/* 3.2.2   25.06.2007 : Switch datum_av ---> datum_lieferbar_ab (Deutschland) */
/* 3.2.3   10.07.2007 : neue Struktur SA 28 (DKRAB) */
/* 3.2.4   31.07.2007 : neues Feld ZAP-MINM, versorgen aus artve nur für Frankreich */
/* 3.2.5   10.09.2007 : Umstellung DB Deutschland von pps1cg auf pps1g, */
/*                      neues Feld in DKRAB-Struktur */
/* 3.2.6   25.09.2007 : versorgen ZAP-MWE aus zartikel.datum_mwe */
/* 3.2.7   09.01.2008 : 2 Vertriebsbindungen Frankreich aus neuen zartfrance-Feldern versorgen */
/* 3.2.8   04.02.2008 : neue DEZAP-Satzart 31 aus zgrppflege (DKRPG) */
/* 3.2.9   05.02.2008 : Verarbeitung Satzart 28 (DKRAB) auch aus zgrppflege (Rabatt-Produktgruppenebene) */
/* 3.3.0   16.04.2008 : versorgen neues Feld EGR-AEPBAS (Satzart 12) */
/* 3.3.1   17.04.2008 : versorgen neues Feld ZAP-PFLSV (Satzart 00) */
/* 3.3.2   09.05.2008 : Funktion GetDeleteDate neu geschrieben, da nicht mehr verwendbar auf Solaris 11 */
/* 3.3.3   27.05.2008 : versorgen neues Feld RGR-PRBAS (Satzart 26) */
/* 3.3.4   08.07.2008 : Änderungen in Log-Ausgabe wg. anderer Verzeichnisstruktur auf neuer Unix-Maschine, */
/* 3.3.5   07.08.2008 : Abfragen auf DBs pps1g, pps1ch und pps1pch durch zpps1de, zpps1ch und zpps1pch ersetzt */
/* 3.3.6   02.09.2008 : Abfragen auf DBs pps1au, pps1hr, pps1fr, pps1pfr, pps1iv und pps1piv durch zpps2at, zpps2hr, zpps2fr, zpps2pfr, zpps2iv und zpps2piv ersetzt */
/* 3.3.7   04.11.2008 : Hersteller-Retourenadresse bei Satzart 20 mitversorgen */
/* 3.3.8   10.11.2008 : andere Basiswerte für zartikel.pflschutz_verord */
/*						ZAP-CHARGE für alle Länder aus zartikel füllen, dazu cgibatchentry verarbeiten */
/*						neues Feld ZAP-KONSNR (aus zartikel.konsig_partner_nr) */
/* 3.3.9   13.01.2009 : MAX_DAY von 7 auf 28 hochgesetzt (Problem mit nicht gelaufenem Änderungsdienst */
/*						am 24.12., das erst am 12.01. erkannt wurde) */
/* 3.4.0   20.01.2009 : zartaustria.RUECK_MON_VOR_VERF in ZAPIHNR statt ZAPORPA einstellen */
/* 3.4.1   26.02.2009 : neue Struktur DKEAN-Satz (Satzart 09) ---> neues Feld VFIL, nur mit 00 vorbelegen */
/* 3.4.2   16.03.2009 : für die Schweiz artve.originalkarton in ZAP-VE stellen */
/* 3.4.3   26.05.2009 : neues Feld zartaustria.vertrbind_bdorf in ZAPVB1 stellen */
/* 3.4.4   06.08.2009 : neue Dateistrukturen DKRAB & DKRPG */
/*						neues Feld in DKEGR */
/*						Verarbeitung Bulgarien & Serbien (Tabellen zartbulgaria, zartserbia) */
/* 3.4.5   16.09.2009 : versorgen zweier neuer Felder aus zartserbia, */
/*						füllen der 5 neuen Hunderttausenderfelder für die Preise */
/* 3.4.6   22.09.2009 : ändern der GEPNA-Berechnung für Bulgarien */
/* 3.4.7   05.10.2009 : 2 neue Felder in DKEGR, */
/*						MINM für Serbien aus zartserbia versorgen */
/* 3.4.8   15.10.2009 : CHECK-Macro umgedreht, denn sonst liefert es bei Feldinhalt Blank TRUE */
/* 3.4.9   07.12.2009 : zartcroatia.exchange_rate von 7,5 auf 12,6 vergrößert */
/* 3.5.0   21.12.2009 : füllen neue Felder in DKSTE-Struktur aus ccpvalidityperiod */
/* 3.5.1   13.01.2010 : carticlecodes.code_type ist jetzt smallint statt char(1) */
/* 3.5.2   14.01.2010 : neues DEZAP-Feld WEBU für Gutschriftspreis Bulgarien */
/* 3.5.3   21.01.2010 : neue DEZAP-Satzart 33 (DKAZB) */
/* 3.5.4   08.02.2010 : zartbulgaria.price_group nach ZAP-INFGR */
/*						Reihenfolge bei Versorgung Feuergefährlichkeitsklasse geändert */
/*						neues cservices-Feld in DKSER übertragen */
/* 3.5.5   16.02.2010 : DKSER-Struktur auch für Bulgarien füllen (bisher nur Frankreich) */
/* 3.5.6   09.04.2010 : neue DEZAP-Satzart 10 (DKGFG) */
/*						für Kroatien artve.originalkarton in ZAPBUEN */
/* 3.5.7   10.05.2010 : füllen neue Felder in DKRPG-Struktur aus cdiscgrp */
/* 3.5.8   14.05.2010 : 2 neue Felder in zzahlbed versorgen */
/* 3.5.9   18.05.2010 : nochmal Änderung in DKRPG-Struktur */
/* 3.6.0   09.06.2010 : cdiscount.monthlydiscount 1:1 in DEZAP statt J/N */
/* 3.6.1   15.07.2010 : ZAPVBED in BG setzen, wenn Preisgruppe ungleich 04 */
/* 3.6.2   11.08.2010 : neue DEZAP-Satzart 34 (DKACO) */
/* 3.6.3   27.09.2010 : Anpassung der GEPNA-Berechnung Bulgarien */
/* 3.6.4   17.12.2010 : in Österreich 2. Saisonart statt 1. ans Pharmos übergeben */
/* 3.6.5   16.03.2011 : in Frankreich Sonder-Rabattgruppe in ZAPINFGR */
/* 3.6.6   22.03.2011 : Fehlerkorrektur Versorgung ZAPINFGR Frankreich */
/* 3.6.7   18.05.2011 : versorgen neues Feld ZAP-FAELGEF (Satzart 00) */
/* 3.6.8   21.09.2011 : neue DEZAP-Satzarten 35 (DRRAM) & 36 (DKMRS) */
/* 3.6.9   30.09.2011 : 2 neue DEZAP-Artikelfelder AGR & MAM (momentan noch nicht versorgen) */
/* 3.7.0   12.10.2011 : neue Felder AGR & MAM jetzt aus zartikel versorgen */
/*						neues Feld cmonthdiscsort.cash_disc_possible nach DKMRS übertragen */
/* 3.7.1   21.11.2011 : 3 neue Felder von cmonthdiscsort nach DKMRS übertragen */
/* 3.7.2   28.11.2011 : 3 neue Felder von cmonthdiscsort nach DKMRS übertragen */
/* 3.7.3   16.12.2011 : neues Feld herstel.adm_pauschale in DEZAP-DKLIF-Struktur */
/* 3.7.4   16.02.2012 : ZAP-MWST in Kroatien 1:1 aus zartpreis versorgen (analog Frankreich & Prewhole-CH) */
/*						versorgen von 4 Feldern aus zartbulgaria */
/*						neues Feld ZAP-ORGPZN aus schon vorhandenem zartikel.artikel_nr_orig versorgen */
/*						Fehlerkorrektur beim Initialisieren des DRRAM-Bereichs (memset) */
/* 3.7.5   22.02.2012 : 1 neues Feld von cmonthdiscsort nach DKMRS übertragen */
/* 3.7.6   01.03.2012 : in Processing saemtliche breaks durch saubere Abbrueche ersetzt (wg. Problem vom 29.02., */
/*						dass bei einem Lesefehler von cgibatchentry keine weiteren Artikel mehr verarbeitet wurden); */
/*						first 1 bei cgibatchentry eingebaut, damit es bei mehreren Einträgen zu keinem Abbruch kommt */
/* 3.7.7   14.03.2012 : neue Vertriebsbindung Frankreich in ZAP-VBB einstellen */
/* 3.7.8   09.05.2012 : 8 Vertriebsbindung für Kroatien versorgen */
/* 3.7.9   18.05.2012 : in Kroatien ZAP20-PREISL mit Wert aus neuem Feld herstel.rechnungssplitt versorgen */
/* 3.8.0   20.06.2012 : 1 neues Feld von cmonthdiscsort nach DKMRS übertragen */
/* 3.8.1   16.07.2012 : 2 neue Felder von zrabgrp nach DKRGR übertragen */
/* 4.0.0   01.08.2012 : Umstellung auf voodoo_table_header, Aufnahme von Landeskuerzel & Prewhole-Flag in */
/*						parameter-struct (um die bisher harten Datenbankabfragen zu vermeiden); */
/*						Abfragen auf zpps1*** ersetzt durch diesen struct */
/* 4.0.1   03.08.2012 : neue DEZAP-Satzart 36 (DKGHZ), nur für Großhandel Frankreich */
/* 4.0.2   06.08.2012 : Abfragen auf zpps2*** ersetzt durch parameter-struct (siehe Version 4.0.0) */
/* 4.0.3   21.11.2012 : neue Struktur Pharmos-Datei DKSTE */
/* 4.0.4   28.11.2012 : ZAPCHARGE = 'E' auch in der Schweiz setzen für IKS-Codes A-E */
/* 4.0.5   05.12.2012 : in Frankreich zautidemsperre verarbeiten für sofort gültige Preisänderungen (ohne neue-Preis-Mimik) */
/* 4.0.6   18.12.2012 : für Deutschland 2 neue Vertriebsbindungen sowie Erstattungswert versorgen */
/* 4.0.7   01.02.2013 : Erstattungswert aus zartpreis statt zartikel versorgen */
/* 4.0.8   22.02.2013 : in Bulgarien VBA versorgen aus neuem zartbulgaria-Feld */
/*						in Artikel-Struktur neues Feld BGN versorgen mit gleichem Wert wie BTMGRP */
/* 4.0.9   15.03.2013 : für Ivrylab zartikel.businesstypeno in ZAPINFGR stellen */
/*						neues Feld ZAPPFAND, versorgen aus zartwg / cdeposittypes */
/* 4.1.0   19.03.2013 : AIX build */
/* 4.1.1   03.04.2013 : neue DEZAP-Satzart 39 (DEPAU), nur für Prewhole Österreich */
/* 4.1.2   12.04.2013 : 7 zusätzliche Felder in DKGFG-Struktur (Satzart 10) versorgen */
/* 4.1.3   12.06.2013 : 2 neue DEZAP-Felder (Satzart 00) versorgen */
/* 4.1.4   02.07.2013 : Anpassungen fuer neue Unix-Maschine (CONV-Makro, durchgeführt von M. Köppendörfer) */
/* 4.1.5   03.07.2013 : Anpassungen fuer neue Unix-Maschine wieder raus, dafuer Aufruf des CONV-Makros mit harten Strings bei GEPNA umgestellt */
/* 4.1.6   11.07.2013 : 3 neue Felder von cmonthdiscsort nach DKMRS übertragen */
/*						keine Versorgung DKBGR mehr */
/* 4.1.7   15.07.2013 : Log-Ausgabe des RCs von CloseDatabase(), wegen immer wieder auftretendem Loop auf iat21pre */
/*						kein Aufruf von GetNumberOfBranch() mehr, SetNumberOfBranch() beim OpenLogfile() aufrufen statt beim OpenDatabase() */
/* 4.1.8   23.07.2013 : Log-Ausgabe aus Vorversion wieder raus, da Fehler nicht hier liegt, sondern im Signal Handling vom zpcronpf */
/* 5.0.0   24.07.2013 : diverse Optimierungen im Rahmen von Unix Foundation durch Michael Eichenlaub & Marco Koeppendoerfer */
/* 5.0.1   25.07.2013 : in DoubleToString() nachkomma nicht mehr bei der Feldlängendefinition berücksichtigen (war wohl ursprünglich ein Denkfehler) */
/* 5.0.2   04.10.2013 ; AH- und RR-Kennzeichen erst mit "J" füllen, wenn entsprechendes Datum tatsächlich erreicht ist (Aufruf LongToStringDateCheck) */
/* 5.0.3   18.11.2013 : zartikel.kosmetikum nach Pharmos uebertragen */
/* 5.0.4   05.12.2013 : neue DEZAP-Satzart 42 (DKKGR) */
/* 5.0.5   09.12.2013 : 2 neue Felder von cmonthdiscsort nach DKMRS übertragen */
/* 5.0.6   13.12.2013 : zartikel.biosiegel nach Pharmos uebertragen */
/* 5.0.7   10.02.2014 : JKL-Code Serbien (aus carticlecodes) in ZAP-INNR stellen */
/* 5.0.8   14.02.2014 : DKKGR-Flag-Tabelle versorgen aus ccustgrpflagtypes und ccustomergrpflags */
/* 5.0.9   02.04.2014 : 2 neue Felder in Artikel-Satzart, dafuer 3 andere eliminiert */
/* 5.1.0   05.05.2014 : ZAP-WIRK im Format P5 statt N3 */
/* 5.1.1   09.05.2014 : keine Versorgung DKWIR, DKGAL, DKGAH mehr */
/* 5.1.2   16.05.2014 : Wirkstoffgruppe steht ab sofort nicht mehr in zartikel, sondern in zartwg (Umstellung auf 5 Stellen) */
/* 5.1.3   09.07.2014 : neues Feld VCLUBNR aus zartwg */
/*						AvoidOverflow für originalkarton Kroatien aufrufen (weil Feld nur 3-stellig ist und es Wert >= 1000 gibt) */
/* 5.1.4   26.08.2014 : GESKL und FEUKL aus csafetydatasheet füllen, falls aufgrund der zartikel-Flags nichts ermittelt werden konnte */
/* 5.1.5   24.10.2014 : neues Feld KUVERF aus carticleext.shortexpiryflag versorgen */
/* 5.1.6   31.10.2014 : ein neues Feld von cmonthdiscsort nach DKMRS übertragen */
/* 5.1.7   16.12.2014 : ein neues Feld von cmonthdiscsort nach DKMRS übertragen, */
/*						bei PZN-Rabatten zusätzliche dateto abfragen, um keine abgelaufenen Sätze zu übertragen (DEZAP zu groß 08.12.) */
/* 5.1.8   10.02.2015 : ein neues Feld von cmonthdiscsort nach DKMRS übertragen */
/* 5.1.9   13.05.2015 : neues Feld herstel.r_name2 nach DKLIF übertragen */
/* 5.2.0   07.07.2015 : 2 neue DEZAP-Satzarten 45 & 46, neues Feld herstel.r_name2 nach DKLIF übertragen */
/* 5.2.1   16.11.2015 : 3 neue Felder in DEZAP-Satzart '00' */

/*** INCLUDE ******************************************************************/

 #include <stdio.h>
 #include <time.h>
 #include <sys/time.h>
 #include <string.h>
 #include <malloc.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <libgen.h>

 #include "tpulzentpfl.h"

 #include "dezap.h"			/* Satzart 00 */
 #include "dezapdksoa.h"	/* Satzart 03 */
 #include "dezapdkris.h"	/* Satzart 08 */
 #include "dezapdkean.h"	/* Satzart 09 */
/*  #include "dezapdkgfg.h"	   Satzart 10 */
 #include "dezapdkaff.h"	/* Satzart 11 */
 #include "dezapdkegr.h"	/* Satzart 12 */
 #include "dezapdkste.h"	/* Satzart 13 */
 #include "dezapdkwgr.h"	/* Satzart 15 */
 #include "dezapdkiwg.h"	/* Satzart 16 */
 #include "dezapdktgr.h"	/* Satzart 17 */
/*  #include "dezapdkbgr.h"	   Satzart 18 */
/*  #include "dezapdkwir.h"	   Satzart 19 */
 #include "dezapdklif.h"	/* Satzart 20 */
 #include "dezapdkatx.h"	/* Satzart 21 */
 #include "dezapdkcrr.h"	/* Satzart 22 */
/* #include "dezapdkgal.h"	   Satzart 23 */
/* #include "dezapdkgah.h"	   Satzart 24 */
 #include "dezapdklid.h"	/* Satzart 25 */
 #include "dezapdkrgr.h"	/* Satzart 26 */
 #include "dezapdkzab.h"	/* Satzart 27 */
 #include "dezapdkrab.h"	/* Satzart 28 */
 #include "dezapdkral.h"	/* Satzart 29 */
 #include "dezapdkser.h"	/* Satzart 30 */
 #include "dezapdkrpg.h"	/* Satzart 31 */
 #include "dezapdkazb.h"	/* Satzart 33 */
 #include "dezapdkaco.h"	/* Satzart 34 */
 #include "dezapdrram.h"	/* Satzart 35 */
 #include "dezapdkmrs.h"	/* Satzart 36 */
 #include "dezapdkghz.h"	/* Satzart 37 */
 #include "dezapdepau.h"    /* Satzart 39 */
 #include "dezapdkkgr.h"	/* Satzart 42 */
 #include "dezapdkmvs.h"	/* Satzart 45 */
/* #include "dezapdkllv.h"	   Satzart 46 */
 #include "dezapdkrbf.h"	/* Satzart 47 */
 #include "dezapdklkr.h"	/* Satzart 48 */
 #include "dezapdklkz.h"	/* Satzart 49 */
 #include "dezapdkfok.h"	/* Satzart 51 */
 #include "dezapdksps.h"	/* Satzart 52 */
 #include "dezapdkaua.h"	/* Satzart 53 */
 #include "dezapdkpro.h"	/* Satzart 54 */
 #include "dezapdkain.h"	/* Satzart 55 */
 #include "dezapcheck.h"	/* Satzart 99 */

/*  #include "dezapzep.h" */

 #include "cobolbuf.h"
 #include "struct.h"
 #include "cdb.h"
 #include "logfile.h"
 #include "zeitstempel.h"
 #include "qtime.h"
 #include "tpulconvert.h"
 #include "ascitocobol.h"
 #include "tpuldb.h"

 #include <voodoo_table_header/zartwg.h>
 #include <voodoo_table_header/carticlecodes.h>
 #include <voodoo_table_header/herstellersalescondition.h>
 #include <voodoo_table_header/zartsekb.h>
 #include <voodoo_table_header/cdeposittypes.h>
 #include <voodoo_table_header/zartfeb2.h>
 #include <voodoo_table_header/csafetydatasheet.h>
 #include <voodoo_table_header/carticleext.h>
 #include <voodoo_table_header/zautidemsperre.h>
/*  #include "cgibatchentry.h" */
 #include <voodoo_table_header/artve.h>
 #include <voodoo_table_header/herstel.h>
 #include <voodoo_table_header/ean.h>
 #include <voodoo_table_header/zartprei.h>
 #include <voodoo_table_header/zartikel.h>
 #include <voodoo_table_header/zartaustria.h>
 #include <voodoo_table_header/zartcroatia.h>
 #include <voodoo_table_header/zartbulgaria.h>
 #include <voodoo_table_header/zartserbia.h>
 #include <voodoo_table_header/zgrppflege.h>
 #include <voodoo_table_header/zpznpflege.h>
 #include <voodoo_table_header/zdkwgr.h>
 #include <voodoo_table_header/artkatg.h>
 #include <voodoo_table_header/zdktgr.h>
/*  #include "zdkbtm.h" */
 #include <voodoo_table_header/zdkwir.h>
 #include <voodoo_table_header/carticletext.h>
 #include <voodoo_table_header/zchargenrueckruf.h>
 #include <voodoo_table_header/cdiscount.h>
 #include <voodoo_table_header/zartswitzerland.h>
 #include <voodoo_table_header/carticlelang.h>
 #include <voodoo_table_header/cartcompack.h>
 #include <voodoo_table_header/ccpvalidityperiod.h>
 #include <voodoo_table_header/cdiscgrp.h>
 #include <voodoo_table_header/cgaloart.h>
 #include <voodoo_table_header/cgalonam.h>
 #include <voodoo_table_header/cgalocom.h>
 #include <voodoo_table_header/herstel_dispo.h>
 #include <voodoo_table_header/zartfrance.h>
 #include <voodoo_table_header/zartverk.h>
 #include <voodoo_table_header/cpharmgrp.h>
 #include <voodoo_table_header/zrabgrp.h>
 #include <voodoo_table_header/zzahlbed.h>
 #include <voodoo_table_header/cdisclist.h>
 #include <voodoo_table_header/cservices.h>
 #include <voodoo_table_header/cdiscgrpmem.h>
 #include <voodoo_table_header/cdiscmodel.h>
 #include <voodoo_table_header/cmonthdiscsort.h>
 #include <voodoo_table_header/chighpaymtargetfee.h>
 #include <voodoo_table_header/ccustomergroup.h>
 #include <voodoo_table_header/cordertype.h>
 #include <voodoo_table_header/cmonthvirtsort.h>
/* #include "ccustservices.h" */
 #include <voodoo_table_header/cstoragecriteria.h>
 #include <voodoo_table_header/cintrastatcountry.h>
 #include <voodoo_table_header/cformtypes.h>
 #include <voodoo_table_header/cdiscform.h>
 #include <voodoo_table_header/cshipper.h>
 #include <voodoo_table_header/cpromotions.h>
 #include <voodoo_table_header/cregisters.h>
 #include <voodoo_table_header/cbaselistarticles.h>

/*** weil 'include ""cdb.h" zu kompliziert ist !!!!!!!!!!!!!!!!!!!!!!!! */
  bool SetLockMode( int iSec );
/*** !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

/*** GLOBALE ******************************************************************/

 int debug_enabled = 0;           /* not used here but needed in some modules */
 int test_enabled = FALSE;        /* for test without transmission */

/*** DEFINE *******************************************************************/

 #define L_DEZAP_BYTE   500
 #define DATABASE "ide21   "			
 #define LOGFILE  "tpulzentpfl.log"
 #define OUTPUT_FILE "dezap.dat"
 #define MAX_DAY 99
 #define KUERZEL "D "
 #define PREWHOLE 0

 typedef struct timeval timeval_t;

 static const country_info sCI[] =  {
                                    { "zpps1de",	"D",	0 },
                                    { "zpps2at",	"A",	0 },	
                                    { "zpps1ch",	"CH",	0 },	
                                    { "zpps1pch",	"CH",	1 },	
                                    { "zpps2hr",	"HR",	0 },	
                                    { "zpps2fr",	"F",	0 },	
                                    { "zpps2pfr",	"F",	1 },	
                                    { "zpps2iv",	"F",	0 },	
                                    { "zpps2piv",	"F",	1 },	
                                    { "zpps2bg",	"BG",	0 },	
                                    { "zpps2rs",	"RS",	0 },	
                                    { "zpps2pat",	"A",	1 },	
                                    { "ide21",		"D",	0 },	
                                    { "iat21",		"A",	0 },	
                                    { "ich21",		"CH",	0 },	
                                    { "ich21pre",	"CH",	1 },	
                                    { "ihr21",		"HR",	0 },	
                                    { "ifr21",		"F",	0 },	
                                    { "ifr21pre",	"F",	1 },	
                                    { "ibg21",		"BG",	0 },	
                                    { "irs21",		"RS",	0 },	
                                    { "iat21pre",	"A",	1 }
								};  
/*get MAX_ANZ_DB automagically*/
static const size_t MAX_ANZ_DB = sizeof(sCI) / sizeof(sCI[0]);

/*** DECLARATION ***************************************************************/

 static int  CheckProcess( const char *progname, int *ipPid );
 static bool OpenLogfile( char *spProg, short filialnr );
 static bool CloseLogfile( void );
 static bool OpenDatabase( const char *db );
/*  static bool CloseDatabase( void ); */
 static bool GetParameter( parameter *d, char **argv, int argc );
 static bool OpenOutput( char *spFile, FILE **fp);
 static bool CloseOutput( FILE *fp );
 static long DeleteZapflege( void );     /* hajo */
 static long DeleteZgrppflege( void );     
 static long DeleteZpznpflege( void );     
 static long Processing( FILE *fp, parameter *p, long *plCount );
 static long GetDeleteDate( int iDay );
 static rterror WriteToDezap( char *spBuf, FILE *fp, int iSize, long *plCount ); /* hajo */
 static int GetCountryIndex( char *DB );

 
/*** copyZgrppflegeKeyGrp *********************************************************************/
/*** function for copying zgrppflege.KEY_GRUPPE (6 bytes) in smaller sized char arrays        */
/*** caller is responsible, that only sizeof(dest) -1 bytes are needed                        */
 static void copyZgrppflegeKeyGrp(char * dest, const char* const source, size_t dest_length)
 {
	 size_t length = dest_length;

	 /*copy bytes, reserve space for \0, strncpy pads \0s if source is too short*/
	 strncpy(dest, source, length - 1);
	 dest[length - 1] = '\0';
 }

/*** MAIN *********************************************************************/

 int main( int argc, char **argv )
 {
   const char *fun = "main";
   long lCountSet = 0;
   FILE *fp;
   parameter sPara;
   int iPid = -1;
   long lCount[MAX_ZAP_SATZART+1];
/* bool db_close_rc; */
   char fil_string[3];
   short filialnr = 0;

   if ( !CheckProcess( "tpulzentpfl", &iPid ) )
   {
          printf( "process is currently active (%d)\n", iPid );
          return is_activ;
   }
   else if ( !GetParameter( &sPara, argv, argc )        )
   {
     printf( "usage:\n" );
     printf( "tpulzentpfl [ -file <FILE> -db <database> -dm <DestinationHost> "  \
	      "-dd <DestinationDir> -df <DestinationFile> ]\n" );

     return call_error;
   }

/* printf("\n%d",sPara.lDate);
   printf("\n%d",sPara.lDateTo);
   printf("\n%d",sPara.lDay);
   printf("\n%s",sPara.spFile);
   printf("\n%s",sPara.spDestinationHost);
   printf("\n%s",sPara.spDestinationFile);
   printf("\n%s",sPara.spUser);
   printf("\n%s",sPara.spPassword);
   printf("\n%s",sPara.spDatabase); */

   /* Filialnummer aus Name der Ausgabedatei ermitteln (lautet beim Aufruf aus zpcronpf immer "dezap<Filiale>.dat" */
   if (strlen (sPara.spFile) >= 7)
   {
		strncpy (fil_string, sPara.spFile + 5, 2);
		fil_string[2] = '\0';
		filialnr = atoi(fil_string);
   }

   if ( !OpenLogfile( argv[0], filialnr ) )
   {
		printf( "can't open the specified logfile\n" );
        return log_error;
   }
   else if ( !WriteLog( fun, 0, "------------------------------------------------" ) || 
			 !WriteLog( fun, 0, "Programm gestartet, DB = %s", sPara.spDatabase ) || 
	         !WriteLog( fun, 0, "Datumsbereich : %ld - %ld", sPara.lDate, sPara.lDateTo ) || 
			 !WriteLog( fun, 0, "Landeskuerzel : %s", sPara.Kuerzel ) || 
			 !WriteLog( fun, 0, "Versionsnummer: %s", VERSION ) )    
   {
		printf( "Schreiben in Logfile nicht moeglich!\n" );
        return log_error;
   }
   else if ( !OpenDatabase( sPara.spDatabase ) )
   {
		printf( "Datenbank konnte nicht geoeffnet werden!\n" );
        WriteLog( fun, -1, "Programm-Abbruch" );
        return db_error;
   }
   else if ( (rterror)startBrowse( sPara.lDate, sPara.lDateTo, sPara.lDay, sPara.spDatabase, sPara.Kuerzel, sPara.Prewhole ) != no_error )
   {
		WriteLog( fun, -1, "Programm-Abbruch" );
        return db_error;
   }
   else if ( !OpenOutput( sPara.spFile, &fp) )
   {
		printf( "Ausgabedatei %s nicht geöffnet", sPara.spFile );
		WriteLog( fun, -1, "Ausgabedatei %s nicht geöffnet", sPara.spFile );
        return open_error;
   }

   /* Counter-Array initialisieren */
   for (int i = 0; i <= MAX_ZAP_SATZART; i++)
   {
	   lCount[i] = 0;
   } 

   if ( ( lCountSet = Processing( fp, &sPara, &lCount[0] ) ) < 0 )
   {
		WriteLog( fun, -1, "Programm mit Fehler beendet!" );
		return be_impaired;
   } 

   endBrowse( lCountSet ? TRUE : FALSE );

   /* Ausgabe Check-Satz (Satzart 99) */
   struct AUFB         describecheck[] = { DEZAPCHECK_SATZ };
   dezapcheckO         dezapcheck;
   char                szBufCheck[L_DEZAP_BYTE + 1];
   char				   anz[6];
   long				   l = 0;

   memset( (char *)&dezapcheck, ' ', sizeof( dezapcheckO ) );
   strncpy (dezapcheck.ZAPSA99, "99", 2);

   /* Anzeige ausgegebene Sätze pro Satzart */
   for (int i = 0; i <= MAX_ZAP_SATZART; i++)
   {
	   sprintf(anz, "%5.5ld", lCount[i]);
	   strncpy(dezapcheck.ZAP99ANZ[i], anz, 5);

	   /* Test !!!! */
	   /* strcpy(dezapcheck.ZAP99FILLER, "\0");
	   printf("%s", dezapcheck); */

	   if (lCount[i] > 0)
	   {
			WriteLog( fun, 0, "%ld Saetze mit Satzart %.2d geschrieben.", lCount[i], i );
	   }
   } 

   WandelCobol( szBufCheck, (char *)&dezapcheck, describecheck, SATZANZAHL( describecheck ) );

	/* Test !!!! */
	/* strcpy(szBufCheck+500, "\0");
	printf("%s", szBufCheck); */

   if ( (rterror)WriteToDezap( szBufCheck, fp, L_DEZAP_BYTE, &l ) != no_error )
   {
        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufCheck, sPara.spFile );
   }

   CloseOutput( fp ); 

   /* zum Testen auf sofumi1 mit User r.raab Filetransfer abschalten */
   /* nun auch für die Schweiz & Österreich Filetransfer abschalten */
   /* Filetransfer ist nun generell abgeschaltet */
   /* if ((strcmp(sPara.spUser, "r.raab") != 0) &&
	   (strcmp(sPara.spDatabase, "pps1cch") != 0) &&
	   (strcmp(sPara.spDatabase, "pps1ca") != 0))
   {
		if ( lCountSet )
		{
			WriteLog( fun, 0, "Datentransfer gestartet" );
			if ( !SendFileToHost( &sPara ) )
				{
					CloseLogfile();
					return send_error;
				}
			WriteLog( fun, 0, "Datentransfer beendet" );
		}
   } */

   WriteLog( fun, 0, "%ld zapflege-Saetze geloescht (aelter %ld)", DeleteZapflege( ), sPara.lDay );
   WriteLog( fun, 0, "%ld zgrppflege-Saetze geloescht (aelter %ld)", DeleteZgrppflege( ), sPara.lDay );
   WriteLog( fun, 0, "%ld zpznpflege-Saetze geloescht (aelter %ld)", DeleteZpznpflege( ), sPara.lDay ); 

   /* Konsolausgabe des RCs von CloseDatabase wg. immer wieder auftretendem Loop auf neuer Unix-Maschine
   db_close_rc = CloseDatabase(); 

   WriteLog( fun, 0, "Returncode CloseDatabase: %d", db_close_rc ); */

   CloseLogfile();

   return no_error;
 }

/***GET-PARAMETER *************************************************************/

static int CheckProcess( const char *progname, int *ipPid )
{
   FILE *infile;
   char buf[512];
   int  i;
   int  n;
   int  pos;
   int  lng;

   *ipPid = 0;

   i = strlen(progname) - 1;
   while ( i >= 0 && progname[i] != '/' ) i--;
   const char* process = &progname[i+1];
   if ( ( lng = strlen(process) ) == 0 ) return 0;

   strcpy( buf, "ps -ef|grep -v grep|grep " );
   strcat( buf, process );

   if ( ( infile = (FILE *)popen( buf, "r") ) == NULL )
      return 0;

   for( i = 0; i < 512; i++ )
   {
     int ch = getc(infile);
     if (ch == EOF)
         break;
     else
         buf[i] = (char)ch;
     
     if ( buf[i] == '\n' )
     {
        int pid;
        buf[i] = '\0';

        /* skip leading blanks */
        n = 0;
        while ( buf[n] && buf[n] == ' ' ) n++;
        /* pos second field -> pid */
        while ( buf[n] && buf[n] != ' ' ) n++;
        while ( buf[n] && buf[n] == ' ' ) n++;
        pid = atol( &buf[n] );
        
        /* pos 8th field -> processname */
        pos = 0;
        while ( pos++ < 6 )
        {
            while ( buf[n] && buf[n] != ' ' ) n++;
            while ( buf[n] && buf[n] == ' ' ) n++;
        }

        /* scan processname without path */
        while ( buf[n] && buf[n] != ' ' ) n++;
        n--;
        while ( buf[n] != '/' && buf[n] != ' ' ) n--;
        n++;
        if ( strncmp( &buf[n], process, lng ) == 0 )
        {
            if ( getpid() != pid )
            {
               *ipPid = pid;
               pclose( infile );
               return 0;
            }
            *ipPid = pid;
        }

        i = 0;
      }
   }
   pclose (infile);
   return 1;
}

/***GET-PARAMETER *************************************************************/

 static bool GetParameter( parameter *p, char **argv, int argc )
 {
   bool bSkip;
   bool bUntil = FALSE;
   int  iCount;
   char *szpArgv;
   int index;

   memset( (char *)p, '\0', sizeof( parameter ) );    /* initialize para */

   /* initialize here all datas you need for parameter! */
   strcpy(p->spFile, OUTPUT_FILE);
   strcpy(p->spDatabase,DATABASE);
   p->lDate = GetCurrentDate();
   p->lDateTo = GetCurrentDate();
   p->lDay = GetDeleteDate( MAX_DAY );
   /* p->Kuerzel is now a 3 byte char array, define KUERZEL needs to be copied b/c p->Kuerzel has to stay writeable  */
   /* p->Kuerzel is later replaced with real Kuerzel */
   /* Kuerzel is 2 byte at most, thus it's \0-terminated (see memset, line 601)*/
   strncpy( p->Kuerzel, KUERZEL, strlen(KUERZEL)  );
   p->Prewhole = PREWHOLE;
   /* end-initializing */

   bSkip = FALSE;

	for ( iCount = 1; iCount < argc; iCount++ )
	{
		if ( bSkip )
		{
			bSkip = FALSE;
			continue;
        }

        szpArgv = argv[iCount];

		if ( !strcmp( szpArgv, "-file" ) )
        {
			strcpy(p->spFile, argv[iCount + 1]);
            bSkip = TRUE;
        }
		else if ( !strcmp( szpArgv, "-db" ) )
        {
			strcpy(p->spDatabase, argv[iCount + 1]);
			bSkip = TRUE;
        }
        else if ( !strcmp( szpArgv, "-ld" ) )
        {
			p->lDate = atol( argv[iCount + 1] );
            if ( !bUntil )
				p->lDateTo = p->lDate;

            bSkip = TRUE;
		}
        else if ( !strcmp( szpArgv, "-to" ) )
        {
			p->lDateTo = atol( argv[iCount + 1] );
			bUntil = TRUE;
            bSkip = TRUE;
		}
        else if ( !strcmp( szpArgv, "-day" ) )
        {
			p->lDay = GetDeleteDate( atoi( argv[iCount + 1] ) );
			bSkip = TRUE;
		}
        else if ( !strcmp( szpArgv, "-test" ) )
        {
			test_enabled = TRUE;
		}
		else
             return FALSE;
	} /* end for */

	index = GetCountryIndex ( p->spDatabase );

	if (index != -1)
	{
		strncpy (p->Kuerzel, sCI[index].Kuerzel, strlen(sCI[index].Kuerzel) );
		/*terminate p->Kuerzel after Kuerzel-character (needed for single char Kuerzels*/
		p->Kuerzel[strlen(sCI[index].Kuerzel)] = '\0';
		p->Prewhole = sCI[index].Prewhole;
	}

    return TRUE;
 }

/*** OPEN-LOGFILE *************************************************************/

static bool OpenLogfile( char *spProg, short filialnr )
{
   /* beim Programmlauf auf den Datenbanken pps1cch und pps1chr kam es zu einem Abbruch im */
   /* CloseLogfile. Da die tatsächlichen Aktivitäten außerhalb des tpulzentpfl passieren,  */
   /* konnte die Ursache leider nicht genau nachvollzogen werden. Wir vermuten, dass in der*/
   /* Funktion SetDirName (logfile.c) kein Speicher allokiert wird, wenn sie so wie bisher */
   /* aufgerufen wird, aber beim EndLog ein free versucht wird und das zum Abbruch führt.  */
   /* Warum das nur auf diesen beiden Datenbanken passiert, ist schleierhaft.              */

	char pfad[1024] = { 0 };

	getcwd(pfad, sizeof(pfad));

	strcat(pfad, "/../log"); 

	SetProgramName( spProg );

	if ( SetDirName ( pfad    ) == (char *)0 || 
		 SetFileName( LOGFILE ) == (char *)0 )
	{
		return FALSE;
	}

	/* Filialnummer schon hier (vor 1. Log-Ausgabe) setzen statt wie bisher erst im OpenDatabase */
	SetNumberOfBranch( filialnr );            /* set branch for logging */

	return TRUE;
}

/*** OPEN-LOGFILE *************************************************************/

 static bool CloseLogfile( void )
 {
   EndLog();
   return TRUE;
 }

/*** OPEN-DATABASE ************************************************************/

 static bool OpenDatabase( const char *db)
 {
/* int iBranchNo = 0; */
   
   const char *fun = "OpenDatabase";

   if ( !OpenDb( db ) )
   {
      char meld[100];
      sprintf( meld, "Datenbank %s konnte nicht geoeffnet werden", db );
      WriteLog( fun, -1, meld );
      return FALSE;
   }
   else if ( !SetIsolation( DIRTY_READ ) )
   {
      WriteLog( fun, -1, "Set Isolation konnte nicht gesetzt werden" );
      return FALSE;
   }
   else if ( !SetLockMode( 20 ) )
   {
      WriteLog( fun, -1, "Set Lock Mode To Wait konnte nicht gesetzt werden" );
      return FALSE;
   }
   /* ermitteln Filialnummer und setzen fürs Logfile erfolgt nun anderweitig 
   else if ( !GetNumberOfBranch( &iBranchNo, D_INT ) )
   {
      WriteLog( fun, 1, "FilialNr nicht lokalisiert" );
   }
   SetNumberOfBranch( iBranchNo ); */

   return TRUE;
 }

/*** CLOSE-DATABASE ************************************************************

 static bool CloseDatabase( void )
 {
   return CloseDb();
 } */

/*** OPEN-OUTPUT **************************************************************/

 static bool OpenOutput( char *spFile, FILE **fp)
 {
    bool bReturn;
    char *spPtr;

	/* vorerst nur für die Schweiz & Österreich ohne Datum */
	/* nun generell ohne Datum (wird später von ZBW-Prozeduren angehängt) */
	/* if ((strcmp(spDatabase, "pps1cch") == 0) ||
	    (strcmp(spDatabase, "pps1ca") == 0)) */
	{
        if ( ( spPtr = (char *)malloc( (strlen(spFile) + 1) * sizeof(char) ) ) == (char *)0)
           return FALSE;

        strcpy( spPtr, spFile );
	}
	/* else
	{
        if ( ( spPtr = (char *)malloc( (strlen(spFile) + 10) * sizeof(char) ) ) == (char *)0)
           return FALSE;

        sprintf( spPtr, "%s.%08ld", spFile, lDate );
	} */

    bReturn = (bool)(( *fp = fopen( spPtr, "w" ) ) == (FILE *)0 ? FALSE : TRUE);
    free( spPtr );
    return bReturn;
 }

/*** CLOSE-OUTPUT *************************************************************/

 static bool CloseOutput( FILE *fp )
 {
   fclose( fp );
   return TRUE;
 }

/*** WRITE-TO-DEZAP ***********************************************************/

 static rterror WriteToDezap( char *spBuf, FILE *fp, int iSize, long *plCount )
 {
   spBuf[iSize] = '\n';
   if ( !fwrite( (char *)spBuf, iSize, 1, fp ) )
         return write_error;

   /* zu Testzwecken: keine gepufferte Ausgabe mehr */
   /* fflush ( fp ); */

   (*plCount)++;

   return no_error;
 }

/*** DELETE-ZAPFLEGE ***********************************************************/

 static long DeleteZapflege( void )
 {
    long lCount = 1;

    Begin();
    for(;;)
    {
        if ( (lCount++ % 50) == 0 )
        {
            Commit();
            Begin();
        }

		if ( DeleteNextArticle() )
            break;
    }
    Commit();

    return lCount - 2;
 }

/*** DELETE-ZGRPPFLEGE ***********************************************************/

 static long DeleteZgrppflege( void )
 {
    long lCount = 1;

    Begin();
    for(;;)
    {
        if ( (lCount++ % 50) == 0 )
        {
            Commit();
            Begin();
        }

		if ( DeleteNextGroup() )
            break;
    }
    Commit();

    return lCount - 2;
 }

/*** DELETE-ZPZNPFLEGE ***********************************************************/

 static long DeleteZpznpflege( void )
 {
    long lCount = 1;

    Begin();
    for(;;)
    {
        if ( (lCount++ % 50) == 0 )
        {
            Commit();
            Begin();
        }

		if ( DeleteNextPZN() )
            break;
    }
    Commit();

    return lCount - 2;
 }

/*** GET-DELETE-DATE ***********************************************************/

static long GetDeleteDate( int iDay )
{
    struct	tm  *t;
    long	tt;
    char	szBuf[9];

	tt = time(0L);                  /* Zeit in sec ab 01.01.1970 00:00:00 */
    t  = localtime(&tt);                                      /* Ortszeit */

	t->tm_mday -= iDay;

	/* mktime korrigiert falsche Werte automatisch, d.h. 00.05. = 30.04. */
	mktime (t);

	/* tm_year = akt. - 1900, tm_mon = akt. Monat - 1, tm_mday = aktueller Tag */
	sprintf( szBuf, "%04d%02d%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday );
    return atol( szBuf );
}

static int GetCountryIndex( char *DB )
{
	/*since MAX_ANZ_DB is size_t = unsigned*/
	/*also cast return value to int, for special meaning of -1*/
	for (size_t i = 0; i < MAX_ANZ_DB; i++)
	{
		if (strcmp(sCI[i].Datenbank, DB) == 0)
			return (int)i;
	}

	return -1;
}

/*** PROCESSING ***************************************************************/

 static long Processing( FILE *fp, parameter *p, long *plCount )
 {
   /* Beschreibungen des DEZAP-Aufbaus aus cobolbuf.h */
   struct AUFB         describe[] = { DEZAP_SATZ };
   struct AUFB         describedksoa[] = { DEZAPDKSOA_SATZ };
   struct AUFB         describeean[] = { DEZAPEAN_SATZ };
   struct AUFB         describedkwgr[] = { DEZAPDKWGR_SATZ };
   struct AUFB         describedkiwg[] = { DEZAPDKIWG_SATZ };
   struct AUFB         describedktgr[] = { DEZAPDKTGR_SATZ };
/* struct AUFB         describedkbgr[] = { DEZAPDKBGR_SATZ }; */
/* struct AUFB         describedkwir[] = { DEZAPDKWIR_SATZ }; */
   struct AUFB         describedklif[] = { DEZAPDKLIF_SATZ };
   struct AUFB         describedkatx[] = { DEZAPDKATX_SATZ };
   struct AUFB         describedkcrr[] = { DEZAPDKCRR_SATZ };
   struct AUFB         describedkrab[] = { DEZAPDKRAB_SATZ };
   struct AUFB         describedkaff[] = { DEZAPDKAFF_SATZ };
   struct AUFB         describedkste[] = { DEZAPDKSTE_SATZ };
/* struct AUFB         describedkgal[] = { DEZAPDKGAL_SATZ }; 
   struct AUFB         describedkgah[] = { DEZAPDKGAH_SATZ }; */
   struct AUFB         describedklid[] = { DEZAPDKLID_SATZ };
   struct AUFB         describedkris[] = { DEZAPDKRIS_SATZ };
   struct AUFB         describedkegr[] = { DEZAPDKEGR_SATZ };
   struct AUFB         describedkrgr[] = { DEZAPDKRGR_SATZ };
   struct AUFB         describedkzab[] = { DEZAPDKZAB_SATZ };
   struct AUFB         describedkral[] = { DEZAPDKRAL_SATZ };
   struct AUFB         describedkser[] = { DEZAPDKSER_SATZ };
   struct AUFB         describedkrpg[] = { DEZAPDKRPG_SATZ };
   struct AUFB         describedkazb[] = { DEZAPDKAZB_SATZ };
/* struct AUFB         describedkgfg[] = { DEZAPDKGFG_SATZ }; */
   struct AUFB         describedkaco[] = { DEZAPDKACO_SATZ };
   struct AUFB         describedrram[] = { DEZAPDRRAM_SATZ };
   struct AUFB         describedkmrs[] = { DEZAPDKMRS_SATZ };
   struct AUFB         describedkghz[] = { DEZAPDKGHZ_SATZ };
   struct AUFB         describedepau[] = { DEZAPDEPAU_SATZ };
   struct AUFB         describedkkgr[] = { DEZAPDKKGR_SATZ };
   struct AUFB         describedkmvs[] = { DEZAPDKMVS_SATZ };
/* struct AUFB         describedkllv[] = { DEZAPDKLLV_SATZ }; */
   struct AUFB         describedklkr[] = { DEZAPDKLKR_SATZ };
   struct AUFB         describedklkz[] = { DEZAPDKLKZ_SATZ };
   struct AUFB         describedkfok[] = { DEZAPDKFOK_SATZ };
   struct AUFB         describedkrbf[] = { DEZAPDKRBF_SATZ };
   struct AUFB         describedksps[] = { DEZAPDKSPS_SATZ };
   struct AUFB         describedkaua[] = { DEZAPDKAUA_SATZ };
   struct AUFB         describedkpro[] = { DEZAPDKPRO_SATZ };
   struct AUFB         describedkain[] = { DEZAPDKAIN_SATZ };

   /* Strukturen zum Einlesen in die Datenbank */
   dezapzartikelSTR				article;
   dezapzartpreisSTR			price;
   dezapeanSTR					ean;
   dezapzartsekbezSTR			secondary;
   dezapcdeposittypesSTR		deposittypes;
   dezapzartwgSTR				goodsgroup;
   dezapcarticlecodesSTR		articlecodes;
   dezaphsalescondSTR			hsalescond;
   dezapherstelSTR				manufacturer;
   dezapzartfeb2STR				fixedamount;
   dezapcsafetydatasheetSTR		csafetydatasheet;
   dezapcarticleextSTR			carticleext;
   dezapzautidemsperreSTR		zautidemsperre;
/* dezapcgibatchentrySTR		cgibatchentry; */
   dezapartveSTR				artve;
   dezapzartaustriaSTR			austria;
   dezapzartcroatiaSTR			croatia;
   dezapzartbulgariaSTR			bulgaria;
   dezapzartserbiaSTR			serbia;
   dezapzgrppflegeSTR			zgrppflege;
   dezapzpznpflegeSTR			zpznpflege;
   dezapzdkwgrSTR				zdkwgr;
   dezapzdkiwgSTR				zdkiwg;
   dezapzdktgrSTR				zdktgr;
/* dezapzdkbgrSTR				zdkbgr; */
/* dezapzdkwirSTR				zdkwir; */
   dezapcarticletextSTR			carticletext;
   dezapzchargenrueckrufSTR		zchargenrueckruf;
   dezapcdiscountSTR			cdiscount;
   dezapzartswitzerlandSTR		switzerland;
   dezapcarticlelangSTR			carticlelang;
   dezapcartcompackSTR			cartcompack;
   dezapccpvalidityperiodSTR	ccpvalidityperiod;
   dezapcdiscgrpSTR				cdiscgrp;
/* dezapcgaloartSTR				cgaloart;
   dezapcgalonamSTR				cgalonam;
   dezapcgalocomSTR				cgalocom; */
   dezapherstel_dispoSTR		manufacturer_dispo;
   dezapzartfranceSTR			france;
   dezapzartverkSTR				zartverk;
   dezapcpharmgrpSTR			cpharmgrp;
   dezapzrabgrpSTR				zrabgrp;
   dezapzzahlbedSTR				zzahlbed;
   dezapcdisclistSTR			cdisclist;
   dezapcservicesSTR			cservices;
   dezapcdiscgrpmemSTR			cdiscgrpmem;
   dezapcdiscmodelSTR			cdiscmodel;
   dezapcmonthdiscsortSTR		cmonthdiscsort;
   dezapchighpaymtargetfeeSTR	chighpaymtargetfee;
   dezapccustomergroupSTR		ccustomergroup;
   dezapccustomergrpflagSTR		ccustomergrpflags;
   dezapcmonthvirtsortSTR		cmonthvirtsort;
/* dezapccustservicesSTR		ccustservices; */
   dezapcstoragecriteriaSTR		cstoragecriteria;
   dezapcintrastatcountrySTR	cintrastatcountry;
   dezapcformtypesSTR			cformtypes;
   dezapcdiscformSTR			cdiscform;
   dezapcshipperSTR				cshipper;
   dezapcordertypeSTR			cordertype;
   dezapcordertypeflagSTR		cordertypeflags;
   dezapcpromotionsSTR			cpromotions;
   dezapcregistersSTR			cregisters;
   dezapcbaselistarticlesSTR	cbaselistarticles;

   /* DEZAP-Strukturen aus jeweiliger Header-Datei */
   dezapO              dezap;
   dezapeanO           dezapean;
   dezapdkwgrO         dezapdkwgr;
   dezapdkiwgO         dezapdkiwg;
   dezapdktgrO         dezapdktgr;
/* dezapdkbgrO         dezapdkbgr; */ 
/* dezapdkwirO         dezapdkwir; */
   dezapdklifO         dezapdklif;
   dezapdkatxO         dezapdkatx;
   dezapdkcrrO         dezapdkcrr;
   dezapdkrabO         dezapdkrab;
   dezapdkaffO         dezapdkaff;
   dezapdksteO         dezapdkste;
/* dezapdkgalO         dezapdkgal;
   dezapdkgahO         dezapdkgah; */
   dezapdklidO         dezapdklid;
   dezapdkrisO         dezapdkris;
   dezapdkegrO         dezapdkegr;
   dezapdkrgrO         dezapdkrgr;
   dezapdkzabO         dezapdkzab;
   dezapdkralO         dezapdkral;
   dezapdkserO         dezapdkser;
   dezapdkrpgO         dezapdkrpg;
   dezapdkazbO         dezapdkazb;
/* dezapdkgfgO         dezapdkgfg; */
   dezapdkacoO         dezapdkaco;
   dezapdrramO         dezapdrram;
   dezapdkmrsO         dezapdkmrs;
   dezapdkghzO         dezapdkghz;
   dezapdepauO         dezapdepau;
   dezapdkkgrO         dezapdkkgr;
   dezapdkmvsO         dezapdkmvs;
/* dezapdkllvO         dezapdkllv; */
   dezapdklkrO         dezapdklkr;
   dezapdklkzO         dezapdklkz;
   dezapdkfokO         dezapdkfok;
   dezapdkrbfO         dezapdkrbf;
   dezapdkspsO         dezapdksps;
   dezapdkauaO         dezapdkaua;
   dezapdkproO         dezapdkpro;
   dezapdkainO         dezapdkain;
   dezapdksoaO         dezapdksoa;

   /* Puffer, in die jeweils pro Satzart geschrieben wird */
   char                szBuf[L_DEZAP_BYTE + 1];
   char                szBufEan[L_DEZAP_BYTE + 1];
   char                szBufDkwgr[L_DEZAP_BYTE + 1];
   char                szBufDkiwg[L_DEZAP_BYTE + 1];
   char                szBufDktgr[L_DEZAP_BYTE + 1];
/* char                szBufDkbgr[L_DEZAP_BYTE + 1]; */
/* char                szBufDkwir[L_DEZAP_BYTE + 1]; */
   char                szBufDklif[L_DEZAP_BYTE + 1];
   char                szBufDkatx[L_DEZAP_BYTE + 1];
   char                szBufDkcrr[L_DEZAP_BYTE + 1];
   char                szBufDkrab[L_DEZAP_BYTE + 1];
   char                szBufDkaff[L_DEZAP_BYTE + 1];
   char                szBufDkste[L_DEZAP_BYTE + 1];
/* char                szBufDkgal[L_DEZAP_BYTE + 1];
   char                szBufDkgah[L_DEZAP_BYTE + 1]; */
   char                szBufDklid[L_DEZAP_BYTE + 1];
   char                szBufDkris[L_DEZAP_BYTE + 1];
   char                szBufDkegr[L_DEZAP_BYTE + 1];
   char                szBufDkrgr[L_DEZAP_BYTE + 1];
   char                szBufDkzab[L_DEZAP_BYTE + 1];
   char                szBufDkral[L_DEZAP_BYTE + 1];
   char                szBufDkser[L_DEZAP_BYTE + 1];
   char                szBufDkrpg[L_DEZAP_BYTE + 1];
   char                szBufDkazb[L_DEZAP_BYTE + 1];
/* char                szBufDkgfg[L_DEZAP_BYTE + 1]; */
   char                szBufDkaco[L_DEZAP_BYTE + 1];
   char                szBufDrram[L_DEZAP_BYTE + 1];
   char                szBufDkmrs[L_DEZAP_BYTE + 1];
   char                szBufDkghz[L_DEZAP_BYTE + 1];
   char                szBufDepau[L_DEZAP_BYTE + 1];
   char                szBufDkkgr[L_DEZAP_BYTE + 1];
   char                szBufDkmvs[L_DEZAP_BYTE + 1];
/* char                szBufDkllv[L_DEZAP_BYTE + 1]; */
   char                szBufDklkr[L_DEZAP_BYTE + 1];
   char                szBufDklkz[L_DEZAP_BYTE + 1];
   char                szBufDkfok[L_DEZAP_BYTE + 1];
   char                szBufDkrbf[L_DEZAP_BYTE + 1];
   char                szBufDksps[L_DEZAP_BYTE + 1];
   char                szBufDkaua[L_DEZAP_BYTE + 1];
   char                szBufDkpro[L_DEZAP_BYTE + 1];
   char                szBufDkain[L_DEZAP_BYTE + 1];
   char                szBufDksoa[L_DEZAP_BYTE + 1];

   /* Checkfelder, ob indizierte Satzart vollgeschrieben wurde */
   bool                bSaveEan;
   bool                bSaveDkste;
   bool                bSaveDkwgr;
   bool                bSaveDkiwg;
   bool                bSaveDktgr;
/* bool                bSaveDkbgr; */
/* bool                bSaveDkwir; */
   bool                bSaveDkatx;
   bool                bSaveDkcrr;
   bool                bSaveDkrab;
   bool                bSaveDkaff;
   bool                bSaveDklid;
   bool                bSaveDkegr;
   bool                bSaveDkrgr;
   bool                bSaveDkzab;
   bool                bSaveDkral;
   bool                bSaveDkser;
   bool                bSaveDkrpg;
   bool                bSaveDkazb;
   bool                bSaveDkaco;
   bool                bSaveDkmrs;
   bool                bSaveDkghz;
   bool                bSaveDepau;
   bool                bSaveDkkgr;
   bool                bSaveDkmvs;
/* bool                bSaveDkllv; */
   bool                bSaveDklkr;
   bool                bSaveDklkz;
   bool                bSaveDkfok;
   bool                bSaveDkrbf;
   bool                bSaveDksps;
   bool                bSaveDkaua;
   bool                bSaveDkpro;
   bool                bSaveDksoa;

   rterror             rc;
   long                lCountSet = 0;
   long                lDate, lDateCdiscount;
   int                 iSize;
   int				   iIndex;
   bool                bChronometer;
   const char          *fun = "Processing";

   iSize = L_DEZAP_BYTE;

   lDate = p->lDateTo > GetCurrentDate() ? p->lDateTo : GetCurrentDate();

   /* fuer cdiscount muss alles gelesen werden, was im laufenden Monat jemals gültig war --> aus 201707xx muss 20170701 gemacht werden */
   lDateCdiscount = ((int) (p->lDate / 100)) * 100 + 1;
    
   bChronometer = (bool)((char *)getenv( "TIMER" ) == (char *)0 ? FALSE : TRUE);

   /* Datenbereiche für Nicht-Artikel-Satzarten initialisieren */
   memset( (char *)&dezapean, ' ', sizeof( dezapeanO ) );
   memset( (char *)&dezapdkwgr, ' ', sizeof( dezapdkwgrO ) );
   memset( (char *)&dezapdkiwg, ' ', sizeof( dezapdkiwgO ) );
   memset( (char *)&dezapdktgr, ' ', sizeof( dezapdktgrO ) );
/* memset( (char *)&dezapdkbgr, ' ', sizeof( dezapdkbgrO ) ); */
/* memset( (char *)&dezapdkwir, ' ', sizeof( dezapdkwirO ) ); */
   memset( (char *)&dezapdklif, ' ', sizeof( dezapdklifO ) );
   memset( (char *)&dezapdkatx, ' ', sizeof( dezapdkatxO ) );
   memset( (char *)&dezapdkcrr, ' ', sizeof( dezapdkcrrO ) );
   memset( (char *)&dezapdkrab, ' ', sizeof( dezapdkrabO ) );
   memset( (char *)&dezapdkaff, ' ', sizeof( dezapdkaffO ) );
   memset( (char *)&dezapdkste, ' ', sizeof( dezapdksteO ) );
/* memset( (char *)&dezapdkgal, ' ', sizeof( dezapdkgalO ) );
   memset( (char *)&dezapdkgah, ' ', sizeof( dezapdkgahO ) ); */
   memset( (char *)&dezapdklid, ' ', sizeof( dezapdklidO ) );
   memset( (char *)&dezapdkris, ' ', sizeof( dezapdkrisO ) );
   memset( (char *)&dezapdkegr, ' ', sizeof( dezapdkegrO ) );
   memset( (char *)&dezapdkrgr, ' ', sizeof( dezapdkrgrO ) );
   memset( (char *)&dezapdkzab, ' ', sizeof( dezapdkzabO ) );
   memset( (char *)&dezapdkral, ' ', sizeof( dezapdkralO ) );
   memset( (char *)&dezapdkser, ' ', sizeof( dezapdkserO ) );
   memset( (char *)&dezapdkrpg, ' ', sizeof( dezapdkrpgO ) );
   memset( (char *)&dezapdkazb, ' ', sizeof( dezapdkazbO ) );
/* memset( (char *)&dezapdkgfg, ' ', sizeof( dezapdkgfgO ) ); */
   memset( (char *)&dezapdkaco, ' ', sizeof( dezapdkacoO ) );
   memset( (char *)&dezapdrram, ' ', sizeof( dezapdrramO ) );
   memset( (char *)&dezapdkmrs, ' ', sizeof( dezapdkmrsO ) );
   memset( (char *)&dezapdkghz, ' ', sizeof( dezapdkghzO ) );
   memset( (char *)&dezapdepau, ' ', sizeof( dezapdepauO ) );
   memset( (char *)&dezapdkkgr, ' ', sizeof( dezapdkkgrO ) );
   memset( (char *)&dezapdkmvs, ' ', sizeof( dezapdkmvsO ) );
/* memset( (char *)&dezapdkllv, ' ', sizeof( dezapdkllvO ) ); */
   memset( (char *)&dezapdklkr, ' ', sizeof( dezapdklkrO ) );
   memset( (char *)&dezapdklkz, ' ', sizeof( dezapdklkzO ) );
   memset( (char *)&dezapdkfok, ' ', sizeof( dezapdkfokO ) );
   memset( (char *)&dezapdkrbf, ' ', sizeof( dezapdkrbfO ) );
   memset( (char *)&dezapdksps, ' ', sizeof( dezapdkspsO ) );
   memset( (char *)&dezapdkaua, ' ', sizeof( dezapdkauaO ) );
   memset( (char *)&dezapdkpro, ' ', sizeof( dezapdkproO ) );
   memset( (char *)&dezapdkain, ' ', sizeof( dezapdkainO ) );
   memset( (char *)&dezapdksoa, ' ', sizeof( dezapdksoaO ) );

   /* Beginn Verarbeitung aus zapflege (Satzart 00) */ 
   while( ( rc = (rterror)GetNextArticle( &article ) ) == no_error )
   {
		 memset( (char *)&dezap, ' ', sizeof( dezapO ) );
         price.ARTIKEL_NR = article.ARTIKEL_NR;
		 price.DATUMGUELTIGAB = lDate;
         
		 secondary.ARTIKEL_NR = article.ARTIKEL_NR;
		 goodsgroup.ARTIKEL_NR = article.ARTIKEL_NR;
		 articlecodes.ARTICLENO = article.ARTIKEL_NR;
		 fixedamount.ARTIKEL_NR = article.ARTIKEL_NR;
		 csafetydatasheet.ARTICLENO = article.ARTIKEL_NR;
		 carticleext.ARTICLENO = article.ARTIKEL_NR;
		 zautidemsperre.ARTIKEL_NR = article.ARTIKEL_NR;
/* 		 cgibatchentry.ARTICLENO = article.ARTIKEL_NR; */
		 artve.ARTIKEL_NR = article.ARTIKEL_NR;
		 austria.ARTIKEL_NR = article.ARTIKEL_NR;
		 croatia.ARTICLENO = article.ARTIKEL_NR;
		 bulgaria.ARTICLENO = article.ARTIKEL_NR;
		 serbia.ARTICLENO = article.ARTIKEL_NR;
		 switzerland.ARTIKEL_NR = article.ARTIKEL_NR;
		 france.ARTICLENO = article.ARTIKEL_NR;

         if (( article.AWL_AKTIV[0] == 'J') || ( article.AWL_AKTIV[0] == 'Z'))
         {
			 manufacturer.HERSTELLER_NR = article.AWL1;
         }
         else
         {
			 manufacturer.HERSTELLER_NR = article.HERSTELLER_NR;
         }

         if ( bChronometer )
         {
                SETSTART();
         }

         if ( ( rc = (rterror)GetPriceOfArticle( &price ) ) == db_error )
		 {
			 WriteLog( fun, -1, "Programm-Abbruch" );
			 return be_impaired;
		 }
         else if ( rc == eof )
		 {
			 /* RR: was soll dieser Quatsch??? Wenn kein Satz gefunden, ist auch die Struktur leer */
/*			 WriteLog( fun, 100, "Artikel %d hat keinen Preis!", price.ARTIKEL_NR ); */
			 WriteLog( fun, 100, "Artikel %d hat keinen Preis!", article.ARTIKEL_NR ); 

			 /* RR 26.04.21: numerischen Default-Wert für VAT-Feld */
			 price.KE_MWST[0] = '0';
		 }

         if ( bChronometer )
         {
            SETEND( "GetPriceOfArticle" );
            SETSTART();
         }

         if ( ( rc = (rterror)GetSecondaryOfArticle( &secondary ) ) == db_error )
		 {
			 WriteLog( fun, -1, "Programm-Abbruch" );
			 return be_impaired;
		 }

         if ( bChronometer )
         {
            SETEND( "GetSecondaryOfArticle" );
            SETSTART();
         }

         if ( ( rc = (rterror)GetManufacturerOfArticle( &manufacturer ) ) == db_error )
		 {
			 WriteLog( fun, -1, "Programm-Abbruch" );
			 return be_impaired;
		 }

         if ( bChronometer )
         {
            SETEND( "GetManufacturer" );
            SETSTART();
         }

         if ( ( rc = (rterror)GetFixedAmountOfArticle( &fixedamount ) ) == db_error )
		 {
			 WriteLog( fun, -1, "Programm-Abbruch" );
			 return be_impaired;
		 }

		 /* Bereich sauber initialisieren, falls nicht gefunden */
 		 if ( rc == eof )
		 {
			 fixedamount.ARTIKEL_NR = article.ARTIKEL_NR;
			 fixedamount.FESTBETRAG2 = 0.0;
		 }

         if ( bChronometer )
         {
            SETEND( "GetFixedAmountOfArticle" );
            SETSTART();
         }

         if ( ( rc = (rterror)GetCsafetydatasheet( &csafetydatasheet ) ) == db_error )
		 {
			 WriteLog( fun, -1, "Programm-Abbruch" );
			 return be_impaired;
		 }

		 /* Bereich sauber initialisieren, falls nicht gefunden */
 		 if ( rc == eof )
		 {
			 csafetydatasheet.ARTICLENO = article.ARTIKEL_NR;
			 csafetydatasheet.PICTOGRAM01_FLAG = 0;
			 csafetydatasheet.PICTOGRAM02_FLAG = 0;
			 csafetydatasheet.PICTOGRAM03_FLAG = 0;
			 csafetydatasheet.PICTOGRAM04_FLAG = 0;
			 csafetydatasheet.PICTOGRAM05_FLAG = 0;
			 csafetydatasheet.PICTOGRAM06_FLAG = 0;
			 csafetydatasheet.PICTOGRAM07_FLAG = 0;
			 csafetydatasheet.PICTOGRAM08_FLAG = 0;
			 csafetydatasheet.PICTOGRAM09_FLAG = 0;
			 strncpy (csafetydatasheet.CALCSTORAGECLASSID, "    ", L_CSAFETYDATASHEET_CALCSTORAGECLASSID);
			 csafetydatasheet.DANGERGOODSTOREROOM = 0;
		 }

         if ( bChronometer )
         {
            SETEND( "GetCsafetydatasheet" );
            SETSTART();
         }

         if ( ( rc = (rterror)GetCarticleext( &carticleext ) ) == db_error )
		 {
			 WriteLog( fun, -1, "Programm-Abbruch" );
			 return be_impaired;
		 }

		 /* Bereich sauber initialisieren, falls nicht gefunden */
 		 if ( rc == eof )
		 {
			 carticleext.ARTICLENO = article.ARTIKEL_NR;
			 carticleext.SHORTEXPIRYFLAG = 0;
		 }

         if ( bChronometer )
         {
            SETEND( "GetCarticleext" );
            SETSTART();
         }

		if ( ( rc = (rterror)GetZautidemsperre( &zautidemsperre ) ) == db_error )
		{
			WriteLog( fun, -1, "Programm-Abbruch" );
			return be_impaired;
		}

		/* Bereich sauber initialisieren, falls nicht gefunden */
 		if ( rc == eof )
		{
			zautidemsperre.ARTIKEL_NR = article.ARTIKEL_NR;
			zautidemsperre.DATUMGUELTIGAB = 0;
		}

		/* gefundenes Datum in bestimmten Fällen nicht berücksichtigen */
 		if ( rc == no_error )
		{
			/* in Deutschland außer Handel */
			if (IsCountry(p->Kuerzel, "D") && 
		        article.DATUM_AH > 0)
			{
				zautidemsperre.DATUMGUELTIGAB = 0;
			}

			/* in Frankreich, wenn Preisdatum != zautidemsperre-Datum */
			if (IsCountry(p->Kuerzel, "F") && 
		        price.DATUMGUELTIGAB != zautidemsperre.DATUMGUELTIGAB)
			{
				zautidemsperre.DATUMGUELTIGAB = 0;
			}
		}

		if ( bChronometer )
		{
			SETEND( "GetZautidemsperre" );
			SETSTART();
		}

/*		 if ( ( rc = (rterror)GetCgibatchentry( &cgibatchentry ) ) == db_error )
		 {
			 WriteLog( fun, -1, "Programm-Abbruch" );
			 return be_impaired;
		 }

		 / * Bereich sauber initialisieren, falls nicht gefunden * /
 		 if ( rc == eof )
		 {
			 cgibatchentry.ARTICLENO = article.ARTIKEL_NR;
			 cgibatchentry.COMPANY_CODE = 0;
		 }

         if ( bChronometer )
         {
            SETEND( "GetCgibatchentry" );
            SETSTART();
         } */

		 if ( ( rc = (rterror)GetArtve( &artve ) ) == db_error )
		 {
			 WriteLog( fun, -1, "Programm-Abbruch" );
			 return be_impaired;
		 }

		/* Bereich sauber initialisieren, falls nicht gefunden */
 		if ( rc == eof )
		{
			artve.ARTIKEL_NR = article.ARTIKEL_NR;
			artve.VERPACKEINHEIT1 = 0;
			artve.VERPACKEINHEIT2 = 0;
			artve.VERPACKEINHEIT3 = 0;
			artve.VERPACKEINHEIT4 = 0;
			artve.ORIGINALKARTON = 0;
		}

		if ( bChronometer )
		{
			SETEND( "GetArtve" );
			SETSTART();
		}

		 /* in Österreich (und nur dort) zusätzlich zartaustria lesen */
		 if (IsCountry(p->Kuerzel, "A"))
		 {
			if ( ( rc = (rterror)GetAustrianFields( &austria ) ) == db_error )
		    {
		        WriteLog( fun, -1, "Programm-Abbruch" );
			    return be_impaired;
		    }

			if ( bChronometer )
			{
				SETEND( "GetAustrianFields" );
				SETSTART();
			}
		 }

		 /* in Kroatien (und nur dort) zusätzlich zartcroatia lesen */
		 if (IsCountry(p->Kuerzel, "HR"))
		 {
			if ( ( rc = (rterror)GetCroatianFields( &croatia ) ) == db_error )
		    {
		        WriteLog( fun, -1, "Programm-Abbruch" );
			    return be_impaired;
		    }

			if ( bChronometer )
			{
				SETEND( "GetCroatianFields" );
				SETSTART();
			}
		 }

		 /* in Bulgarien (und nur dort) zusätzlich zartbulgaria lesen */
		 if (IsCountry(p->Kuerzel, "BG"))
		 {
			if ( ( rc = (rterror)GetBulgarianFields( &bulgaria ) ) == db_error )
		    {
		        WriteLog( fun, -1, "Programm-Abbruch" );
			    return be_impaired;
		    }

			if ( bChronometer )
			{
				SETEND( "GetBulgarianFields" );
				SETSTART();
			}
		 }

		 /* in Serbien (und nur dort) zusätzlich zartserbia lesen */
		 if (IsCountry(p->Kuerzel, "RS"))
		 {
			if ( ( rc = (rterror)GetSerbianFields( &serbia ) ) == db_error )
		    {
		        WriteLog( fun, -1, "Programm-Abbruch" );
			    return be_impaired;
		    }

			if ( bChronometer )
			{
				SETEND( "GetSerbianFields" );
				SETSTART();
			}
		 }

		 /* in der Schweiz (und nur dort) zusätzlich zartswitzerland lesen */
		 if (IsCountry(p->Kuerzel, "CH"))
		 {
			if ( ( rc = (rterror)GetSwissFields( &switzerland ) ) == db_error )
		    {
		        WriteLog( fun, -1, "Programm-Abbruch" );
			    return be_impaired;
		    }

			if ( bChronometer )
			{
				SETEND( "GetSwissFields" );
				SETSTART();
			}
		 }

		 /* in Frankreich (und nur dort) zusätzlich zartfrance lesen */
		 if (IsCountry(p->Kuerzel, "F"))
		 {
			if ( ( rc = (rterror)GetFrenchFields( &france ) ) == db_error )
		    {
		        WriteLog( fun, -1, "Programm-Abbruch" );
			    return be_impaired;
		    }

			if ( bChronometer )
			{
				SETEND( "GetFrenchFields" );
				SETSTART();
			}
		 }

		 InitGoodsgroupOfArticle( &goodsgroup );            /* more then one sentence <-- vermutlich sollte das "record" heißen */
         while( ( rc = (rterror)GetGoodsgroupOfArticle( &goodsgroup ) ) == no_error )
         {
			 // für Pfand erst den Wert ermitteln und dann in DEZAP stellen
			 if ( goodsgroup.ART[0] == 'C' )
			 {
				strncpy (deposittypes.DEPOSIT_TYPE, goodsgroup.WARENGRUPPE, L_ZARTWG_WARENGRUPPE); 

				if ( ( rc = (rterror)GetDepositValueOfArticle( &deposittypes ) ) == db_error )
				{
					WriteLog( fun, -1, "Programm-Abbruch" );
					return be_impaired;
				}

				ConvertDeposit( &dezap, &deposittypes, describe );
			 }
			 else
				ConvertGoodsgroup( &dezap, &goodsgroup, describe, p );
         }
         if ( rc == db_error )
	     {
		    WriteLog( fun, -1, "Programm-Abbruch" );
		    return be_impaired;
		 }

         if ( bChronometer )
         {
             SETEND( "GetGoodsgroupOfArticle" );
             SETSTART();
         }

		 InitCodes( &articlecodes );            /* more then one sentence */
         while( ( rc = (rterror)GetCodes( &articlecodes ) ) == no_error )
         {
			 ConvertCodes( &dezap, &articlecodes, describe, p );
         }

         if ( rc == db_error )
	     {
		    WriteLog( fun, -1, "Programm-Abbruch" );
		    return be_impaired;
		 }

         if ( bChronometer )
         {
             SETEND( "GetCodes" );
             SETSTART();
         }

         ConvertArticle( &dezap, &article, &csafetydatasheet, describe, p );
         if ( bChronometer )
         {
             SETEND( "ConvertArticle" );
             SETSTART();
         }

         ConvertPrice( &dezap, &price, describe, p );
         if ( bChronometer )
         {
             SETEND( "ConvertPrice" );
             SETSTART();
         }

         ConvertSecondary( &dezap, &secondary, describe );
         if ( bChronometer )
         {
             SETEND( "ConvertSecondary" );
             SETSTART();
         }

		 ConvertFixedAmount( &dezap, &fixedamount, describe );
		 if ( bChronometer )
		 {
		 	 SETEND( "ConvertFixedAmount" );
		     SETSTART();
		 }

		 ConvertArticleExt( &dezap, &carticleext );
		 if ( bChronometer )
		 {
		 	 SETEND( "ConvertArticleExt" );
		     SETSTART();
		 }

		 /* in Deutschland & (ab 05.12.12) Frankreich (und nur dort) zusätzlich zautidemsperre verarbeiten */
		 if (IsCountry(p->Kuerzel, "D") ||
			 IsCountry(p->Kuerzel, "F"))
		 {
			ConvertZautidemsperre( &dezap, &zautidemsperre, describe );
			if ( bChronometer )
			{
		 		SETEND( "ConvertZautidemsperre" );
				SETSTART();
			}
		 }

		 ConvertBatchInfo( &dezap, &article, &switzerland, describe, p );
		 if ( bChronometer )
		 {
		 	SETEND( "ConvertBatchInfo" );
			SETSTART();
		 }

		 /* fuer Großhandel Frankreich, Großhandel Schweiz und Kroatien (und nur dort) zusätzlich artve verarbeiten; neu 29.10.19: Bulgarien */
         if ((IsCountry(p->Kuerzel, "F") && p->Prewhole == 0) ||
			 (IsCountry(p->Kuerzel, "CH") && p->Prewhole == 0) ||
			  IsCountry(p->Kuerzel, "HR") ||
			  IsCountry(p->Kuerzel, "BG"))
		 {
			ConvertArtve( &dezap, &artve, describe, p );
			if ( bChronometer )
			{
		 		SETEND( "ConvertArtve" );
				SETSTART();
			}
		 }

		 /* in Österreich (und nur dort) zusätzlich zartaustria verarbeiten */
		 if (IsCountry(p->Kuerzel, "A"))
		 {
		 	 ConvertAustria( &dezap, &austria, describe );
			 if ( bChronometer )
			 {
				SETEND( "ConvertAustria" );
				SETSTART();
			 }
		 }

		 /* in Kroatien (und nur dort) zusätzlich zartcroatia verarbeiten */
		 if (IsCountry(p->Kuerzel, "HR"))
		 {
		 	 ConvertCroatia( &dezap, &croatia, describe );
			 if ( bChronometer )
			 {
				SETEND( "ConvertCroatia" );
				SETSTART();
			 }

			 ConvertCroatiaSpecial( &dezap, &croatia, &price, describe );
			 if ( bChronometer )
			 {
				SETEND( "ConvertCroatiaSpecial" );
				SETSTART();
			 }
		 }

		 /* in Bulgarien (und nur dort) zusätzlich zartbulgaria verarbeiten */
		 if (IsCountry(p->Kuerzel, "BG"))
		 {
		 	 ConvertBulgaria( &dezap, &bulgaria, &price, describe );
			 if ( bChronometer )
			 {
				SETEND( "ConvertBulgaria" );
				SETSTART();
			 }
		 }

		 /* in Serbien (und nur dort) zusätzlich zartserbia verarbeiten */
		 if (IsCountry(p->Kuerzel, "RS"))
		 {
		 	 ConvertSerbia( &dezap, &serbia, describe );
			 if ( bChronometer )
			 {
				SETEND( "ConvertSerbia" );
				SETSTART();
			 }
		 }

		 /* in der Schweiz (und nur dort) zusätzlich zartswitzerland verarbeiten */
		 if (IsCountry(p->Kuerzel, "CH"))
		 {
		 	 ConvertSwitzerland( &dezap, &switzerland, describe );
			 if ( bChronometer )
			 {
				SETEND( "ConvertSwitzerland" );
				SETSTART();
			 }
		 }

		 /* in Frankreich (und nur dort) zusätzlich zartfrance verarbeiten */
		 if (IsCountry(p->Kuerzel, "F"))
		 {
		 	 ConvertFrance( &dezap, &france, describe, p );
			 if ( bChronometer )
			 {
				SETEND( "ConvertFrance" );
				SETSTART();
			 }
		 }

         ConvertManufacturerArticle( &dezap, &manufacturer, describe );
         if ( bChronometer )
         {
             SETEND( "ConvertManufacturerArticle" );
             SETSTART();
         }

     #ifdef __DEBUG_ON__
         DruckeDezap(&dezap);
     #endif

         WandelCobol( szBuf, (char *)&dezap, describe, SATZANZAHL( describe ) );
         if ( bChronometer )
         {
             SETEND( "WandelCobol" );
             SETSTART();
         }

         if ( ( rc = (rterror)WriteToDezap( szBuf, fp, iSize, plCount ) ) != no_error )
         {
			 WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                              szBuf, p->spFile );
			 break;
         }

         if ( bChronometer )
         {
                 SETEND( "WriteToDezap" );
         }

         if ( (lCountSet++) % 100 == 0)
                fflush( fp );
	}

   /* Beginn Verarbeitung aus zgrppflege (Satzarten 12, 15 - 21, 24-29, 31-32, 35-37) */ 
	while( ( rc = (rterror)GetNextGroup( &zgrppflege ) ) == no_error )
	{
		if (strncmp(zgrppflege.DEZAP_SA, "12", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 12: DKEGR */
		{
			copyZgrppflegeKeyGrp(cpharmgrp.PHARMACYGROUPID, zgrppflege.KEY_GRUPPE, sizeof(cpharmgrp.PHARMACYGROUPID));
			
			if ( ( rc = (rterror)GetCpharmgrp( &cpharmgrp ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				copyZgrppflegeKeyGrp(cpharmgrp.PHARMACYGROUPID, zgrppflege.KEY_GRUPPE, sizeof(cpharmgrp.PHARMACYGROUPID)); 
			}

	        bSaveDkegr = (bool)ConvertDkegr( &dezapdkegr, &cpharmgrp, describedkegr, rc );

			if(bSaveDkegr)
			{
                WandelCobol( szBufDkegr, (char *)&dezapdkegr, describedkegr, SATZANZAHL( describedkegr ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkegr, fp, iSize, plCount + 12 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkegr, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkegr, ' ', sizeof( dezapdkegrO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "15", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 15: DKWGR */
		{
			copyZgrppflegeKeyGrp(zdkwgr.WGR_GRUPPE, zgrppflege.KEY_GRUPPE, sizeof(zdkwgr.WGR_GRUPPE));
	        if ( ( rc = (rterror)GetZdkwgr( &zdkwgr ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				copyZgrppflegeKeyGrp(zdkwgr.WGR_GRUPPE, zgrppflege.KEY_GRUPPE, sizeof(zdkwgr.WGR_GRUPPE));
			}

	        bSaveDkwgr = (bool)ConvertDkwgr( &dezapdkwgr, &zdkwgr, describedkwgr, rc );

			if(bSaveDkwgr)
			{
                WandelCobol( szBufDkwgr, (char *)&dezapdkwgr, describedkwgr, SATZANZAHL( describedkwgr ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkwgr, fp, iSize, plCount + 15 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkwgr, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkwgr, ' ', sizeof( dezapdkwgrO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "16", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 16: DKIWG */
		{
			copyZgrppflegeKeyGrp(zdkiwg.WARENGRUPPE, zgrppflege.KEY_GRUPPE, sizeof(zdkiwg.WARENGRUPPE));
	        if ( ( rc = (rterror)GetZdkiwg( &zdkiwg ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				copyZgrppflegeKeyGrp(zdkiwg.WARENGRUPPE, zgrppflege.KEY_GRUPPE, sizeof(zdkiwg.WARENGRUPPE));
			}

	        bSaveDkiwg = (bool)ConvertDkiwg( &dezapdkiwg, &zdkiwg, describedkiwg, rc );

			if(bSaveDkiwg)
			{
                WandelCobol( szBufDkiwg, (char *)&dezapdkiwg, describedkiwg, SATZANZAHL( describedkiwg ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkiwg, fp, iSize, plCount + 16 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkiwg, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkiwg, ' ', sizeof( dezapdkiwgO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "17", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 17: DKTGR */
		{
			copyZgrppflegeKeyGrp(zdktgr.TGR_GRUPPE, zgrppflege.KEY_GRUPPE, sizeof(zdktgr.TGR_GRUPPE));
	        if ( ( rc = (rterror)GetZdktgr( &zdktgr ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				copyZgrppflegeKeyGrp(zdktgr.TGR_GRUPPE, zgrppflege.KEY_GRUPPE, sizeof(zdktgr.TGR_GRUPPE));
			}

	        bSaveDktgr = (bool)ConvertDktgr( &dezapdktgr, &zdktgr, describedktgr, rc );

			if(bSaveDktgr)
			{
                WandelCobol( szBufDktgr, (char *)&dezapdktgr, describedktgr, SATZANZAHL( describedktgr ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDktgr, fp, iSize, plCount + 17 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDktgr, p->spFile );
                        break;
                }

                memset( (char *)&dezapdktgr, ' ', sizeof( dezapdktgrO ) );
			}
		} 
/* 		else if (strncmp(zgrppflege.DEZAP_SA, "18", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   // Satzart 18: DKBGR
		{
			strcpy (zdkbgr.BTM_GRUPPE, zgrppflege.KEY_GRUPPE); 
	        if ( ( rc = (rterror)GetZdkbgr( &zdkbgr ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			// wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können
			if ( rc == eof )
			{
				strcpy (zdkbgr.BTM_GRUPPE, zgrppflege.KEY_GRUPPE); 
			}

	        bSaveDkbgr = (bool)ConvertDkbgr( &dezapdkbgr, &zdkbgr, describedkbgr, rc );

			if(bSaveDkbgr)
			{
                WandelCobol( szBufDkbgr, (char *)&dezapdkbgr, describedkbgr, SATZANZAHL( describedkbgr ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkbgr, fp, iSize, plCount + 18 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkbgr, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkbgr, ' ', sizeof( dezapdkbgrO ) );
			}
		} */
/*		else if (strncmp(zgrppflege.DEZAP_SA, "19", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   // Satzart 19: DKWIR
		{
			copyZgrppflegeKeyGrp(zdkwir.WIR_BEREICH, zgrppflege.KEY_GRUPPE, sizeof(zdkwir.WIR_BEREICH));
	        if ( ( rc = (rterror)GetZdkwir( &zdkwir ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			// wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können 
			if ( rc == eof )
			{
				copyZgrppflegeKeyGrp(zdkwir.WIR_BEREICH, zgrppflege.KEY_GRUPPE, sizeof(zdkwir.WIR_BEREICH));
			}

	        bSaveDkwir = (bool)ConvertDkwir( &dezapdkwir, &zdkwir, describedkwir, rc );

			if(bSaveDkwir)
			{
                WandelCobol( szBufDkwir, (char *)&dezapdkwir, describedkwir, SATZANZAHL( describedkwir ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkwir, fp, iSize, plCount + 19 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkwir, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkwir, ' ', sizeof( dezapdkwirO ) );
			}
		} */
		else if (strncmp(zgrppflege.DEZAP_SA, "20", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 20: DKLIF */
		{
            manufacturer.HERSTELLER_NR = atoi(zgrppflege.KEY_GRUPPE);

			if ( ( rc = (rterror)GetManufacturerOfArticle( &manufacturer ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

	        /* obwohl Hersteller eigentlich nicht direkt gelöscht werden, kann es vorkommen, */
			/* dass einer nicht gefunden wird (versehentliche Neuanlage und direkte Löschung */
			/* (konkreter Fall: 98998 vom 28.11.05) */
			if ( rc != eof )
			{
				ConvertManufacturer( &dezapdklif, &manufacturer, describedklif, p );

				// erstmal PA09-Datenbereich komplett initialisieren
				hsalescond.ARTID = 0;
				strcpy (hsalescond.SALESCONDITIONVALUE, "0,00");

				for ( iIndex = 0; iIndex < ANZ_DKLIF_P09_ELEMENTE; iIndex++)
					ConvertSalesCondition( &dezapdklif, &hsalescond, describedklif, p, iIndex );

				// Werte aus herstellersalescondition dazulesen
	            hsalescond.HERSTELLER_NR = manufacturer.HERSTELLER_NR;
								
				InitHSalesCondition( &hsalescond );           

				iIndex = 0;

				while( ( rc = (rterror)GetHSalesCondition( &hsalescond ) ) == no_error )
				{
					ConvertSalesCondition( &dezapdklif, &hsalescond, describedklif, p, iIndex );

					iIndex++;
				}

				WandelCobol( szBufDklif, (char *)&dezapdklif, describedklif, SATZANZAHL( describedklif ) );
				if ( ( rc = (rterror)WriteToDezap( szBufDklif, fp, iSize, plCount + 20 ) ) != no_error )
				{
						WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDklif, p->spFile );
						break;
				}

				memset( (char *)&dezapdklif, ' ', sizeof( dezapdklifO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "21", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 21: DKATX */
		{
			copyZgrppflegeKeyGrp(carticletext.TEXTNO, zgrppflege.KEY_GRUPPE, sizeof(carticletext.TEXTNO));			
	        if ( ( rc = (rterror)GetCarticletext( &carticletext ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				copyZgrppflegeKeyGrp(carticletext.TEXTNO, zgrppflege.KEY_GRUPPE, sizeof(carticletext.TEXTNO)); 
			}

	        bSaveDkatx = (bool)ConvertDkatx( &dezapdkatx, &carticletext, describedkatx, rc );

			if(bSaveDkatx)
			{
                WandelCobol( szBufDkatx, (char *)&dezapdkatx, describedkatx, SATZANZAHL( describedkatx ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkatx, fp, iSize, plCount + 21 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkatx, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkatx, ' ', sizeof( dezapdkatxO ) );
			}
		}
/*		else if (strncmp(zgrppflege.DEZAP_SA, "24", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   // Satzart 24: DKGAH 
		{
            cgalocom.COMP_NO = atoi(zgrppflege.KEY_GRUPPE);

			if ( ( rc = (rterror)GetCgalocom( &cgalocom ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			// wenn Satz nicht gefunden, muss zumindest der Key nochmal versorgt werden, um den Löschsatz schreiben zu können 
			if ( rc == eof )
			{
	            cgalocom.COMP_NO = atoi(zgrppflege.KEY_GRUPPE);
			}

	        ConvertDkgah( &dezapdkgah, &cgalocom, describedkgah, rc );

            WandelCobol( szBufDkgah, (char *)&dezapdkgah, describedkgah, SATZANZAHL( describedkgah ) );
            if ( ( rc = (rterror)WriteToDezap( szBufDkgah, fp, iSize, plCount + 24 ) ) != no_error )
            {
                    WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                    szBufDkgah, p->spFile );
                    break;
            }

            memset( (char *)&dezapdkgah, ' ', sizeof( dezapdkgahO ) );
		} */
		else if (strncmp(zgrppflege.DEZAP_SA, "25", L_ZGRPPFLEGE_DEZAP_SA) == 0) 
	   /* Satzart 25: DKLID */
		{
            manufacturer_dispo.HERSTELLER_NR = atoi(zgrppflege.KEY_GRUPPE);

			if ( ( rc = (rterror)GetManufacturer_Dispo( &manufacturer_dispo ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

	        /* obwohl Hersteller eigentlich nicht direkt gelöscht werden, kann es vorkommen, */
			/* dass einer nicht gefunden wird (versehentliche Neuanlage und direkte Löschung */
			/* (konkreter Fall: 98998 vom 28.11.05) */
			if ( rc != eof )
			{
				bSaveDklid = (bool)ConvertDklid( &dezapdklid, &manufacturer_dispo, describedklid, rc );

				if(bSaveDklid)
				{
					WandelCobol( szBufDklid, (char *)&dezapdklid, describedklid, SATZANZAHL( describedklid ) );
					if ( ( rc = (rterror)WriteToDezap( szBufDklid, fp, iSize, plCount + 25 ) ) != no_error )
					{
							WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDklid, p->spFile );
							break;
					}

					memset( (char *)&dezapdklid, ' ', sizeof( dezapdklidO ) );
				}
			}
		}
		else if (strncmp(zgrppflege.DEZAP_SA, "26", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 26: DKRGR */
		{
			copyZgrppflegeKeyGrp (zrabgrp.RABATTGRUPPE, zgrppflege.KEY_GRUPPE, sizeof(zrabgrp.RABATTGRUPPE)); 
	        if ( ( rc = (rterror)GetZrabgrp( &zrabgrp ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				copyZgrppflegeKeyGrp (zrabgrp.RABATTGRUPPE, zgrppflege.KEY_GRUPPE, sizeof(zrabgrp.RABATTGRUPPE)); 
			}

	        bSaveDkrgr = (bool)ConvertDkrgr( &dezapdkrgr, &zrabgrp, describedkrgr, rc );

			if(bSaveDkrgr)
			{
                WandelCobol( szBufDkrgr, (char *)&dezapdkrgr, describedkrgr, SATZANZAHL( describedkrgr ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkrgr, fp, iSize, plCount + 26 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkrgr, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkrgr, ' ', sizeof( dezapdkrgrO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "27", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 27: DKZAB */
		{
			copyZgrppflegeKeyGrp (zzahlbed.ZAHLUNGSBEDINGUNG, zgrppflege.KEY_GRUPPE, sizeof(zzahlbed.ZAHLUNGSBEDINGUNG)); 
	        if ( ( rc = (rterror)GetZzahlbed( &zzahlbed ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				copyZgrppflegeKeyGrp (zzahlbed.ZAHLUNGSBEDINGUNG, zgrppflege.KEY_GRUPPE, sizeof(zzahlbed.ZAHLUNGSBEDINGUNG)); 
			}

	        bSaveDkzab = (bool)ConvertDkzab( &dezapdkzab, &zzahlbed, describedkzab, rc );

			if(bSaveDkzab)
			{
                WandelCobol( szBufDkzab, (char *)&dezapdkzab, describedkzab, SATZANZAHL( describedkzab ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkzab, fp, iSize, plCount + 27 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkzab, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkzab, ' ', sizeof( dezapdkzabO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "2A", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 2A: DKRAB (Rabatt-Produktgruppenebene) */
		{
			bool bDezapGefuellt = FALSE;

			if ( (rterror)startBrowseCdiscount_Rpg( atoi (zgrppflege.KEY_GRUPPE) ) != no_error )
			{
				WriteLog( fun, -1, "Programm-Abbruch" );
				return be_impaired;
			}
	
			while ( ( rc = (rterror)GetNextCdiscount_Rpg( &cdiscount ) ) != db_error )
			{
				/* wenn kein Satz mehr gefunden, aber schon mindestens einer geschrieben, Schleife verlassen */
				if ( rc == eof && bDezapGefuellt)
				{
					break;
				}

				/* Returncode merken für spätere Abfrage */
				rterror rc_save = rc;

				cdiscount.DISCOUNTGRPNO = atoi (zgrppflege.KEY_GRUPPE);
				cdiscount.ARTICLENO = 0;
				cdiscount.MANUFACTURERNO = 0;
				cdiscount.ARTCATEGORYNO = 0;

				bSaveDkrab = (bool)ConvertDkrab( &dezapdkrab, &cdiscount, describedkrab, rc );
				bDezapGefuellt = TRUE;

				if(bSaveDkrab)
				{
					WandelCobol( szBufDkrab, (char *)&dezapdkrab, describedkrab, SATZANZAHL( describedkrab ) ); 

					if ( ( rc = (rterror)WriteToDezap( szBufDkrab, fp, iSize, plCount + 28 ) ) != no_error )
					{
							WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDkrab, p->spFile );
							break;
					}

					memset( (char *)&dezapdkrab, ' ', sizeof( dezapdkrabO ) );
				}

				/* wenn überhaupt kein DB-Satz gefunden, musste noch ein Satz mit Löschkennzeichen geschrieben werden, daher Schleife erst hier verlassen */
				if ( rc_save == eof )
				{
					break;
				}
			}

			endBrowseCdiscount_Rpg( );
		}
		else if (strncmp(zgrppflege.DEZAP_SA, "2B", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 2B: DKRAB (Herstellerebene) */
		{
			bool bDezapGefuellt = FALSE;

			if ( (rterror)startBrowseCdiscount_Hnr( atoi (zgrppflege.KEY_GRUPPE) ) != no_error )
			{
				WriteLog( fun, -1, "Programm-Abbruch" );
				return be_impaired;
			}
	
			while ( ( rc = (rterror)GetNextCdiscount_Hnr( &cdiscount ) ) != db_error )
			{
				/* wenn kein Satz mehr gefunden, aber schon mindestens einer geschrieben, Schleife verlassen */
				if ( rc == eof && bDezapGefuellt)
				{
					break;
				}

				/* Returncode merken für spätere Abfrage */
				rterror rc_save = rc;

				cdiscount.MANUFACTURERNO = atoi (zgrppflege.KEY_GRUPPE);
				cdiscount.ARTICLENO = 0;
				cdiscount.DISCOUNTGRPNO = 0;
				cdiscount.ARTCATEGORYNO = 0;

				bSaveDkrab = (bool)ConvertDkrab( &dezapdkrab, &cdiscount, describedkrab, rc );
				bDezapGefuellt = TRUE;

				if(bSaveDkrab)
				{
					WandelCobol( szBufDkrab, (char *)&dezapdkrab, describedkrab, SATZANZAHL( describedkrab ) ); 

					if ( ( rc = (rterror)WriteToDezap( szBufDkrab, fp, iSize, plCount + 28 ) ) != no_error )
					{
							WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDkrab, p->spFile );
							break;
					}

					memset( (char *)&dezapdkrab, ' ', sizeof( dezapdkrabO ) );
				}

				/* wenn überhaupt kein DB-Satz gefunden, musste noch ein Satz mit Löschkennzeichen geschrieben werden, daher Schleife erst hier verlassen */
				if ( rc_save == eof )
				{
					break;
				}
			}

			endBrowseCdiscount_Hnr( );
		}
		else if (strncmp(zgrppflege.DEZAP_SA, "2C", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 2C: DKRAB (Artikelgruppenebene) */
		{
			bool bDezapGefuellt = FALSE;

			if ( (rterror)startBrowseCdiscount_Agn( atoi (zgrppflege.KEY_GRUPPE) ) != no_error )
			{
				WriteLog( fun, -1, "Programm-Abbruch" );
				return be_impaired;
			}
	
			while ( ( rc = (rterror)GetNextCdiscount_Agn( &cdiscount ) ) != db_error )
			{
				/* wenn kein Satz mehr gefunden, aber schon mindestens einer geschrieben, Schleife verlassen */
				if ( rc == eof && bDezapGefuellt)
				{
					break;
				}

				/* Returncode merken für spätere Abfrage */
				rterror rc_save = rc;

				cdiscount.ARTCATEGORYNO = atoi (zgrppflege.KEY_GRUPPE);
				cdiscount.ARTICLENO = 0;
				cdiscount.MANUFACTURERNO = 0;
				cdiscount.DISCOUNTGRPNO = 0;

				bSaveDkrab = (bool)ConvertDkrab( &dezapdkrab, &cdiscount, describedkrab, rc );
				bDezapGefuellt = TRUE;

				if(bSaveDkrab)
				{
					WandelCobol( szBufDkrab, (char *)&dezapdkrab, describedkrab, SATZANZAHL( describedkrab ) ); 

					if ( ( rc = (rterror)WriteToDezap( szBufDkrab, fp, iSize, plCount + 28 ) ) != no_error )
					{
							WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDkrab, p->spFile );
							break;
					}

					memset( (char *)&dezapdkrab, ' ', sizeof( dezapdkrabO ) );
				}

				/* wenn überhaupt kein DB-Satz gefunden, musste noch ein Satz mit Löschkennzeichen geschrieben werden, daher Schleife erst hier verlassen */
				if ( rc_save == eof )
				{
					break;
				}
			}

			endBrowseCdiscount_Agn( );
		}
		else if (strncmp(zgrppflege.DEZAP_SA, "29", L_ZGRPPFLEGE_DEZAP_SA) == 0 &&
				 IsCountry(p->Kuerzel, "F"))
	   /* Satzart 29: DKRAL (nur in Frankreich) */
		{
			strncpy (cdisclist.ORDER_TYPE, zgrppflege.KEY_GRUPPE, 2); 
			strncpy (cdisclist.SUB_ORDER_TYPE, zgrppflege.KEY_GRUPPE + 2, 3);

	        if ( ( rc = (rterror)GetCdisclist( &cdisclist ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				strncpy (cdisclist.ORDER_TYPE, zgrppflege.KEY_GRUPPE, 2); 
				strncpy (cdisclist.SUB_ORDER_TYPE, zgrppflege.KEY_GRUPPE + 2, 3);
			}

	        bSaveDkral = (bool)ConvertDkral( &dezapdkral, &cdisclist, describedkral, rc );

			if(bSaveDkral)
			{
                WandelCobol( szBufDkral, (char *)&dezapdkral, describedkral, SATZANZAHL( describedkral ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkral, fp, iSize, plCount + 29 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkral, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkral, ' ', sizeof( dezapdkralO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "30", L_ZGRPPFLEGE_DEZAP_SA) == 0 &&
				(IsCountry(p->Kuerzel, "F") ||
				 IsCountry(p->Kuerzel, "BG") ))
	   /* Satzart 30: DKSER (nur in Frankreich und neu auch in Bulgarien) */
		{
			cservices.SERVICE_NO = atoi (zgrppflege.KEY_GRUPPE); 

	        if ( ( rc = (rterror)GetCservices( &cservices ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Service-Nr. nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				cservices.SERVICE_NO = atoi (zgrppflege.KEY_GRUPPE); 
			}

	        bSaveDkser = (bool)ConvertDkser( &dezapdkser, &cservices, describedkser, rc );

			if(bSaveDkser)
			{
                WandelCobol( szBufDkser, (char *)&dezapdkser, describedkser, SATZANZAHL( describedkser ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkser, fp, iSize, plCount + 30 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkser, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkser, ' ', sizeof( dezapdkserO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "31", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 31: DKRPG */
		{
			bool bDezapGefuellt = FALSE;

		    cdiscgrp.DISCOUNTGRPNO = atoi (zgrppflege.KEY_GRUPPE);

	        if ( ( rc = (rterror)GetCdiscgrp ( &cdiscgrp ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die RPG nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
			    cdiscgrp.DISCOUNTGRPNO = atoi (zgrppflege.KEY_GRUPPE);

				bSaveDkrpg = (bool)ConvertDkrpg( &dezapdkrpg, &cdiscgrp, &cdiscgrpmem, describedkrpg, rc );
				bDezapGefuellt = TRUE;

				if(bSaveDkrpg)
				{
					WandelCobol( szBufDkrpg, (char *)&dezapdkrpg, describedkrpg, SATZANZAHL( describedkrpg ) ); 

					if ( ( rc = (rterror)WriteToDezap( szBufDkrpg, fp, iSize, plCount + 31 ) ) != no_error )
					{
							WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDkrpg, p->spFile );
							break;
					}

					memset( (char *)&dezapdkrpg, ' ', sizeof( dezapdkrpgO ) );
				}
			}
			else
			{
				if ( (rterror)startBrowseCdiscgrpmem( atoi (zgrppflege.KEY_GRUPPE) ) != no_error )
				{
					WriteLog( fun, -1, "Programm-Abbruch" );
					return be_impaired;
				} 
	
				while ( ( rc = (rterror)GetNextCdiscgrpmem( &cdiscgrpmem ) ) != db_error )
				{
					/* wenn kein Satz mehr gefunden, aber schon mindestens einer geschrieben, Schleife verlassen */
					if ( rc == eof && bDezapGefuellt)
					{
						break;
					}

					/* Returncode merken für spätere Abfrage */

					cdiscgrpmem.DISCOUNTGRPNO = atoi (zgrppflege.KEY_GRUPPE);

					bSaveDkrpg = (bool)ConvertDkrpg( &dezapdkrpg, &cdiscgrp, &cdiscgrpmem, describedkrpg, rc );
					bDezapGefuellt = TRUE;

					if(bSaveDkrpg)
					{
						WandelCobol( szBufDkrpg, (char *)&dezapdkrpg, describedkrpg, SATZANZAHL( describedkrpg ) ); 

						if ( ( rc = (rterror)WriteToDezap( szBufDkrpg, fp, iSize, plCount + 31 ) ) != no_error )
						{
								WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
											szBufDkrpg, p->spFile );
								break;
						}

						memset( (char *)&dezapdkrpg, ' ', sizeof( dezapdkrpgO ) );
					}
				}

				endBrowseCdiscgrpmem( );
			}
		}
		else if (strncmp(zgrppflege.DEZAP_SA, "35", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 35: DRRAM */
		{
		    cdiscmodel.DISCOUNTMODELNO = atoi (zgrppflege.KEY_GRUPPE);

	        if ( ( rc = (rterror)GetCdiscmodel( &cdiscmodel ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			    cdiscmodel.DISCOUNTMODELNO = atoi (zgrppflege.KEY_GRUPPE);

			ConvertDrram( &dezapdrram, &cdiscmodel, describedrram, rc );

			WandelCobol( szBufDrram, (char *)&dezapdrram, describedrram, SATZANZAHL( describedrram ) );

			if ( ( rc = (rterror)WriteToDezap( szBufDrram, fp, iSize, plCount + 35 ) ) != no_error )
			{
					WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
								szBufDrram, p->spFile );
					break;
			}

			memset( (char *)&dezapdrram, ' ', sizeof( dezapdrramO ) );
		}
		else if (strncmp(zgrppflege.DEZAP_SA, "36", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 36: DKMRS */
		{
		    cmonthdiscsort.MONTHLYDISCOUNTGRP = atoi (zgrppflege.KEY_GRUPPE);

			if ( ( rc = (rterror)GetCmonthdiscsort( &cmonthdiscsort ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			    cmonthdiscsort.MONTHLYDISCOUNTGRP = atoi (zgrppflege.KEY_GRUPPE);

	        bSaveDkmrs = (bool)ConvertDkmrs( &dezapdkmrs, &cmonthdiscsort, describedkmrs, rc );

			if(bSaveDkmrs)
			{
                WandelCobol( szBufDkmrs, (char *)&dezapdkmrs, describedkmrs, SATZANZAHL( describedkmrs ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkmrs, fp, iSize, plCount + 36 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkmrs, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkmrs, ' ', sizeof( dezapdkmrsO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "37", L_ZGRPPFLEGE_DEZAP_SA) == 0 &&
				(IsCountry(p->Kuerzel, "F") && p->Prewhole == 0))
	   /* Satzart 37: DKGHZ (nur für Großhandel Frankreich) */
		{
		    strncpy (chighpaymtargetfee.CUSTCLASSIFICATION, zgrppflege.KEY_GRUPPE, 1);
		    chighpaymtargetfee.FROMPAYMTARGETDAYS = atoi (zgrppflege.KEY_GRUPPE+1);

			if ( ( rc = (rterror)GetChighpaymtargetfee( &chighpaymtargetfee ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				strncpy (chighpaymtargetfee.CUSTCLASSIFICATION, zgrppflege.KEY_GRUPPE, 1);
				chighpaymtargetfee.FROMPAYMTARGETDAYS = atoi (zgrppflege.KEY_GRUPPE+1);
			}

	        bSaveDkghz = (bool)ConvertDkghz( &dezapdkghz, &chighpaymtargetfee, describedkghz, rc );

			if(bSaveDkghz)
			{
                WandelCobol( szBufDkghz, (char *)&dezapdkghz, describedkghz, SATZANZAHL( describedkghz ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkghz, fp, iSize, plCount + 37 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkghz, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkghz, ' ', sizeof( dezapdkghzO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "42", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 42: DKKGR */
		{
		    ccustomergroup.CUSTOMERGROUPNO = atoi (zgrppflege.KEY_GRUPPE);

			if ( ( rc = (rterror)GetCcustomergroup( &ccustomergroup ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			    ccustomergroup.CUSTOMERGROUPNO = atoi (zgrppflege.KEY_GRUPPE);
			/* ansonsten noch die Flag-Tabelle initialisieren und alle relevanten Flags dazulesen */
			else
			{
				InitCustGrpFlagArray();

				if ( (rterror)startBrowseCcustomergroupflags( ccustomergroup.CUSTOMERGROUPNO ) != no_error )
				{
					WriteLog( fun, -1, "Programm-Abbruch" );
					return be_impaired;
				}
		
				while ( (rterror)GetNextCcustomergrpflags( &ccustomergrpflags ) == no_error )
				{
					FillCustGrpFlagArray (ccustomergrpflags.customergrpflag, ccustomergrpflags.index_dkkgr);
				}

				endBrowseCcustomergroupflags( );
			}

	        bSaveDkkgr = (bool)ConvertDkkgr( &dezapdkkgr, &ccustomergroup, describedkkgr, rc );

			if(bSaveDkkgr)
			{
                WandelCobol( szBufDkkgr, (char *)&dezapdkkgr, describedkkgr, SATZANZAHL( describedkkgr ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkkgr, fp, iSize, plCount + 42 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkkgr, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkkgr, ' ', sizeof( dezapdkkgrO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "45", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 45: DKMVS */
		{
		    cmonthvirtsort.MONTHLYVIRTUALGROUP = atoi (zgrppflege.KEY_GRUPPE);

			if ( ( rc = (rterror)GetCmonthvirtsort( &cmonthvirtsort ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			    cmonthvirtsort.MONTHLYVIRTUALGROUP = atoi (zgrppflege.KEY_GRUPPE);

	        bSaveDkmvs = (bool)ConvertDkmvs( &dezapdkmvs, &cmonthvirtsort, describedkmvs, rc );

			if(bSaveDkmvs)
			{
                WandelCobol( szBufDkmvs, (char *)&dezapdkmvs, describedkmvs, SATZANZAHL( describedkmvs ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkmvs, fp, iSize, plCount + 45 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkmvs, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkmvs, ' ', sizeof( dezapdkmvsO ) );
			}
		} 
/*		else if (strncmp(zgrppflege.DEZAP_SA, "46", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   // Satzart 46: DKLLV
		{
		    ccustservices.SERVICE_NO = atoi (zgrppflege.KEY_GRUPPE);

			if ( ( rc = (rterror)GetCcustservices( &ccustservices ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			// wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können
			if ( rc == eof )
			    ccustservices.SERVICE_NO = atoi (zgrppflege.KEY_GRUPPE);

	        bSaveDkllv = (bool)ConvertDkllv( &dezapdkllv, &ccustservices, describedkllv, rc );

			if(bSaveDkllv)
			{
                WandelCobol( szBufDkllv, (char *)&dezapdkllv, describedkllv, SATZANZAHL( describedkllv ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkllv, fp, iSize, plCount + 46 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkllv, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkllv, ' ', sizeof( dezapdkllvO ) );
			}
		}  */
		else if (strncmp(zgrppflege.DEZAP_SA, "47", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 47: DKRBF */
		{
		    cdiscform.DISCOUNTFORMNO = atoi (zgrppflege.KEY_GRUPPE);

			if ( ( rc = (rterror)GetCdiscform( &cdiscform ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			    cdiscform.DISCOUNTFORMNO = atoi (zgrppflege.KEY_GRUPPE);

	        bSaveDkrbf = (bool)ConvertDkrbf( &dezapdkrbf, &cdiscform, describedkrbf, rc );

			if(bSaveDkrbf)
			{
                WandelCobol( szBufDkrbf, (char *)&dezapdkrbf, describedkrbf, SATZANZAHL( describedkrbf ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkrbf, fp, iSize, plCount + 47 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkrbf, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkrbf, ' ', sizeof( dezapdkrbfO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "48", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 48: DKLKR */
		{
		    cstoragecriteria.STORAGECRITERIANO = atoi (zgrppflege.KEY_GRUPPE);

			if ( ( rc = (rterror)GetCstoragecriteria( &cstoragecriteria ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			    cstoragecriteria.STORAGECRITERIANO = atoi (zgrppflege.KEY_GRUPPE);

	        bSaveDklkr = (bool)ConvertDklkr( &dezapdklkr, &cstoragecriteria, describedklkr, rc );

			if(bSaveDklkr)
			{
                WandelCobol( szBufDklkr, (char *)&dezapdklkr, describedklkr, SATZANZAHL( describedklkr ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDklkr, fp, iSize, plCount + 48 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDklkr, p->spFile );
                        break;
                }

                memset( (char *)&dezapdklkr, ' ', sizeof( dezapdklkrO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "49", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 49: DKLKZ */
		{
			copyZgrppflegeKeyGrp (cintrastatcountry.COUNTRYCODE, zgrppflege.KEY_GRUPPE, sizeof(cintrastatcountry.COUNTRYCODE)); 

			if ( ( rc = (rterror)GetCintrastatcountry( &cintrastatcountry ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
				copyZgrppflegeKeyGrp (cintrastatcountry.COUNTRYCODE, zgrppflege.KEY_GRUPPE, sizeof(cintrastatcountry.COUNTRYCODE)); 

	        bSaveDklkz = (bool)ConvertDklkz( &dezapdklkz, &cintrastatcountry, describedklkz, rc );

			if(bSaveDklkz)
			{
                WandelCobol( szBufDklkz, (char *)&dezapdklkz, describedklkz, SATZANZAHL( describedklkz ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDklkz, fp, iSize, plCount + 49 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDklkz, p->spFile );
                        break;
                }

                memset( (char *)&dezapdklkz, ' ', sizeof( dezapdklkzO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "51", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 51: DKFOK */
		{
			copyZgrppflegeKeyGrp(cformtypes.FORMTYPE, zgrppflege.KEY_GRUPPE, sizeof(cformtypes.FORMTYPE));
	        if ( ( rc = (rterror)GetCformtypes( &cformtypes ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				copyZgrppflegeKeyGrp(cformtypes.FORMTYPE, zgrppflege.KEY_GRUPPE, sizeof(cformtypes.FORMTYPE));
			}

	        bSaveDkfok = (bool)ConvertDkfok( &dezapdkfok, &cformtypes, describedkfok, rc );

			if(bSaveDkfok)
			{
                WandelCobol( szBufDkfok, (char *)&dezapdkfok, describedkfok, SATZANZAHL( describedkfok ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkfok, fp, iSize, plCount + 51 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkfok, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkfok, ' ', sizeof( dezapdkfokO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "52", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 52: DKSPS */
		{
		    cshipper.SHIPPERNO = atoi (zgrppflege.KEY_GRUPPE);

			if ( ( rc = (rterror)GetCshipper( &cshipper ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			    cshipper.SHIPPERNO = atoi (zgrppflege.KEY_GRUPPE);

	        bSaveDksps = (bool)ConvertDksps( &dezapdksps, &cshipper, describedksps, rc );

			if(bSaveDksps)
			{
                WandelCobol( szBufDksps, (char *)&dezapdksps, describedksps, SATZANZAHL( describedksps ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDksps, fp, iSize, plCount + 52 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDksps, p->spFile );
                        break;
                }

                memset( (char *)&dezapdksps, ' ', sizeof( dezapdkspsO ) );
			}
		}
		else if (strncmp(zgrppflege.DEZAP_SA, "53", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 53: DKAUA */
		{
			copyZgrppflegeKeyGrp (cordertype.CSCORDERTYPE, zgrppflege.KEY_GRUPPE, sizeof(cordertype.CSCORDERTYPE)); 

			if ( ( rc = (rterror)GetCordertype( &cordertype ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				copyZgrppflegeKeyGrp (cordertype.CSCORDERTYPE, zgrppflege.KEY_GRUPPE, sizeof(cordertype.CSCORDERTYPE)); 
			}
			/* ansonsten noch die Flag-Tabelle initialisieren und alle relevanten Flags dazulesen */
			else
			{
				InitOrderTypeFlagArray();

				if ( (rterror)startBrowseCordertypeflags( cordertype.CSCORDERTYPE ) != no_error )
				{
					WriteLog( fun, -1, "Programm-Abbruch" );
					return be_impaired;
				}
		
				while ( (rterror)GetNextCordertypeflags( &cordertypeflags ) == no_error )
				{
					FillOrderTypeFlagArray (cordertypeflags.ordertypeflag, cordertypeflags.index_dkaua);
				}

				endBrowseCordertypeflags( );
			}

	        bSaveDkaua = (bool)ConvertDkaua( &dezapdkaua, &cordertype, describedkaua, rc );

			if(bSaveDkaua)
			{
                WandelCobol( szBufDkaua, (char *)&dezapdkaua, describedkaua, SATZANZAHL( describedkaua ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkaua, fp, iSize, plCount + 53 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkaua, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkaua, ' ', sizeof( dezapdkauaO ) );
			}
		} 
		else if (strncmp(zgrppflege.DEZAP_SA, "54", L_ZGRPPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 54: DKPRO */
		{
		    cpromotions.PROMOTION_NO = atoi (zgrppflege.KEY_GRUPPE);

			if ( ( rc = (rterror)GetCpromotions( &cpromotions ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			    cpromotions.PROMOTION_NO = atoi (zgrppflege.KEY_GRUPPE);

	        bSaveDkpro = (bool)ConvertDkpro( &dezapdkpro, &cpromotions, describedkpro, rc );

			if(bSaveDkpro)
			{
                WandelCobol( szBufDkpro, (char *)&dezapdkpro, describedkpro, SATZANZAHL( describedkpro ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkpro, fp, iSize, plCount + 54 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkpro, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkpro, ' ', sizeof( dezapdkproO ) );
			}
		}
		else if (strncmp(zgrppflege.DEZAP_SA, "55", L_ZGRPPFLEGE_DEZAP_SA) == 0)
		/* Satzart 55: DKAIN */
		{
			copyZgrppflegeKeyGrp (cregisters.MINISTRYPRODUCTCODE, zgrppflege.KEY_GRUPPE, sizeof(zgrppflege.KEY_GRUPPE)); 

			if ( ( rc = (rterror)GetCregisters( &cregisters ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die Gruppe nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
				copyZgrppflegeKeyGrp (cregisters.MINISTRYPRODUCTCODE, zgrppflege.KEY_GRUPPE, sizeof(zgrppflege.KEY_GRUPPE)); 

			ConvertDkain( &dezapdkain, &cregisters, describedkain, rc );

			WandelCobol( szBufDkain, (char *)&dezapdkain, describedkain, SATZANZAHL( describedkain ) );

			if ( ( rc = (rterror)WriteToDezap( szBufDkain, fp, iSize, plCount + 55 ) ) != no_error )
			{
					WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
								szBufDkain, p->spFile );
					break;
			}

			memset( (char *)&dezapdkain, ' ', sizeof( dezapdkain ) );
		}
	}

   /* jetzt noch pro (indizierter) Satzart prüfen, ob noch ein halbvoller DEZAP-Satz weggeschrieben werden muss */
    if(strncmp(dezapdkegr.ZAPSA12,"  ",L_DEZAPDKEGR_ZAPSA12))
    {
        WandelCobol( szBufDkegr, (char *)&dezapdkegr, describedkegr, SATZANZAHL( describedkegr ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkegr, fp, iSize, plCount + 12 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkegr, p->spFile );
        }
    }
   
    if(strncmp(dezapdkwgr.ZAPSA15,"  ",L_DEZAPDKWGR_ZAPSA15))
    {
        WandelCobol( szBufDkwgr, (char *)&dezapdkwgr, describedkwgr, SATZANZAHL( describedkwgr ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkwgr, fp, iSize, plCount + 15 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkwgr, p->spFile );
        }
    }
   
    if(strncmp(dezapdkiwg.ZAPSA16,"  ",L_DEZAPDKIWG_ZAPSA16))
    {
        WandelCobol( szBufDkiwg, (char *)&dezapdkiwg, describedkiwg, SATZANZAHL( describedkiwg ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkiwg, fp, iSize, plCount + 16 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkiwg, p->spFile );
        }
    }
   
    if(strncmp(dezapdktgr.ZAPSA17,"  ",L_DEZAPDKTGR_ZAPSA17))
    {
        WandelCobol( szBufDktgr, (char *)&dezapdktgr, describedktgr, SATZANZAHL( describedktgr ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDktgr, fp, iSize, plCount + 17 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDktgr, p->spFile );
        }
    }
   
/*     if(strncmp(dezapdkbgr.ZAPSA18,"  ",L_DEZAPDKBGR_ZAPSA18))
    {
        WandelCobol( szBufDkbgr, (char *)&dezapdkbgr, describedkbgr, SATZANZAHL( describedkbgr ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkbgr, fp, iSize, plCount + 18 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkbgr, p->spFile );
        }
    } */
   
/*    if(strncmp(dezapdkwir.ZAPSA19,"  ",L_DEZAPDKWIR_ZAPSA19))
    {
        WandelCobol( szBufDkwir, (char *)&dezapdkwir, describedkwir, SATZANZAHL( describedkwir ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkwir, fp, iSize, plCount + 19 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkwir, p->spFile );
        }
    } */
   
    if(strncmp(dezapdkatx.ZAPSA21,"  ",L_DEZAPDKATX_ZAPSA21))
    {
        WandelCobol( szBufDkatx, (char *)&dezapdkatx, describedkatx, SATZANZAHL( describedkatx ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkatx, fp, iSize, plCount + 21 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkatx, p->spFile );
        }
    }
   
    if(strncmp(dezapdklid.ZAPSA25,"  ",L_DEZAPDKLID_ZAPSA25))
    {
        WandelCobol( szBufDklid, (char *)&dezapdklid, describedklid, SATZANZAHL( describedklid ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDklid, fp, iSize, plCount + 25 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDklid, p->spFile );
        }
    }
   
    if(strncmp(dezapdkrgr.ZAPSA26,"  ",L_DEZAPDKRGR_ZAPSA26))
    {
        WandelCobol( szBufDkrgr, (char *)&dezapdkrgr, describedkrgr, SATZANZAHL( describedkrgr ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkrgr, fp, iSize, plCount + 26 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkrgr, p->spFile );
        }
    }
   
    if(strncmp(dezapdkzab.ZAPSA27,"  ",L_DEZAPDKZAB_ZAPSA27))
    {
        WandelCobol( szBufDkzab, (char *)&dezapdkzab, describedkzab, SATZANZAHL( describedkzab ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkzab, fp, iSize, plCount + 27 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkzab, p->spFile );
        }
    }
   
    if(strncmp(dezapdkrab.ZAPSA28,"  ",L_DEZAPDKRAB_ZAPSA28))
    {
        WandelCobol( szBufDkrab, (char *)&dezapdkrab, describedkrab, SATZANZAHL( describedkrab ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkrab, fp, iSize, plCount + 28 ) ) != no_error )
        {
			WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                    szBufDkrab, p->spFile );
        }

		/* weil später nochmal Verarbeitung aus zpznpflege mit gleichem Puffer */
        memset( (char *)&dezapdkrab, ' ', sizeof( dezapdkrabO ) );
    }

    if(strncmp(dezapdkral.ZAPSA29,"  ",L_DEZAPDKRAL_ZAPSA29))
    {
        WandelCobol( szBufDkral, (char *)&dezapdkral, describedkral, SATZANZAHL( describedkral ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkral, fp, iSize, plCount + 29 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkral, p->spFile );
        }
    }
   
    if(strncmp(dezapdkser.ZAPSA30,"  ",L_DEZAPDKSER_ZAPSA30))
    {
        WandelCobol( szBufDkser, (char *)&dezapdkser, describedkser, SATZANZAHL( describedkser ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkser, fp, iSize, plCount + 30 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkser, p->spFile );
        }
    }
   
    if(strncmp(dezapdkrpg.ZAPSA31,"  ",L_DEZAPDKRPG_ZAPSA31))
    {
        WandelCobol( szBufDkrpg, (char *)&dezapdkrpg, describedkrpg, SATZANZAHL( describedkrpg ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkrpg, fp, iSize, plCount + 31 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkrpg, p->spFile );
        }
    }
   
    if(strncmp(dezapdkmrs.ZAPSA36,"  ",L_DEZAPDKMRS_ZAPSA36))
    {
        WandelCobol( szBufDkmrs, (char *)&dezapdkmrs, describedkmrs, SATZANZAHL( describedkmrs ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkmrs, fp, iSize, plCount + 36 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkmrs, p->spFile );
        }
    }
   
    if(strncmp(dezapdkghz.ZAPSA37,"  ",L_DEZAPDKGHZ_ZAPSA37))
    {
        WandelCobol( szBufDkghz, (char *)&dezapdkghz, describedkghz, SATZANZAHL( describedkghz ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkghz, fp, iSize, plCount + 37 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkghz, p->spFile );
        }
    }
   
    if(strncmp(dezapdkkgr.ZAPSA42,"  ",L_DEZAPDKKGR_ZAPSA42))
    {
        WandelCobol( szBufDkkgr, (char *)&dezapdkkgr, describedkkgr, SATZANZAHL( describedkkgr ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkkgr, fp, iSize, plCount + 42 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkkgr, p->spFile );
        }
    }
   
    if(strncmp(dezapdkmvs.ZAPSA45,"  ",L_DEZAPDKMVS_ZAPSA45))
    {
        WandelCobol( szBufDkmvs, (char *)&dezapdkmvs, describedkmvs, SATZANZAHL( describedkmvs ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkmvs, fp, iSize, plCount + 45 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkmvs, p->spFile );
        }
    }
   
/*  if(strncmp(dezapdkllv.ZAPSA46,"  ",L_DEZAPDKLLV_ZAPSA46))
    {
        WandelCobol( szBufDkllv, (char *)&dezapdkllv, describedkllv, SATZANZAHL( describedkllv ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkllv, fp, iSize, plCount + 46 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkllv, p->spFile );
        }
    } */
   
    if(strncmp(dezapdkrbf.ZAPSA47,"  ",L_DEZAPDKRBF_ZAPSA47))
    {
        WandelCobol( szBufDkrbf, (char *)&dezapdkrbf, describedkrbf, SATZANZAHL( describedkrbf ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkrbf, fp, iSize, plCount + 47 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkrbf, p->spFile );
        }
    }
   
    if(strncmp(dezapdklkr.ZAPSA48,"  ",L_DEZAPDKLKR_ZAPSA48))
    {
        WandelCobol( szBufDklkr, (char *)&dezapdklkr, describedklkr, SATZANZAHL( describedklkr ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDklkr, fp, iSize, plCount + 48 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDklkr, p->spFile );
        }
    }
   
    if(strncmp(dezapdklkz.ZAPSA49,"  ",L_DEZAPDKLKZ_ZAPSA49))
    {
        WandelCobol( szBufDklkz, (char *)&dezapdklkz, describedklkz, SATZANZAHL( describedklkz ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDklkz, fp, iSize, plCount + 49 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDklkz, p->spFile );
        }
    }
   
    if(strncmp(dezapdkfok.ZAPSA51,"  ",L_DEZAPDKFOK_ZAPSA51))
    {
        WandelCobol( szBufDkfok, (char *)&dezapdkfok, describedkfok, SATZANZAHL( describedkfok ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkfok, fp, iSize, plCount + 51 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkfok, p->spFile );
        }
    }
   
    if(strncmp(dezapdksps.ZAPSA52,"  ",L_DEZAPDKSPS_ZAPSA52))
    {
        WandelCobol( szBufDksps, (char *)&dezapdksps, describedksps, SATZANZAHL( describedksps ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDksps, fp, iSize, plCount + 52 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDksps, p->spFile );
        }
    }
   
    if(strncmp(dezapdkaua.ZAPSA53,"  ",L_DEZAPDKAUA_ZAPSA53))
    {
        WandelCobol( szBufDkaua, (char *)&dezapdkaua, describedkaua, SATZANZAHL( describedkaua ) );

		if ( ( rc = (rterror)WriteToDezap( szBufDkaua, fp, iSize, plCount + 53 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                szBufDkaua, p->spFile );
        }
	}

    if(strncmp(dezapdkpro.ZAPSA54,"  ",L_DEZAPDKPRO_ZAPSA54))
    {
        WandelCobol( szBufDkpro, (char *)&dezapdkpro, describedkpro, SATZANZAHL( describedkpro ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkpro, fp, iSize, plCount + 54 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                        szBufDkpro, p->spFile );
        }
    }
   
   /* Beginn Verarbeitung aus zpznpflege (Satzarten 08, 09, 11, 13, 22, 23, 28, 33 & 34) */ 
   while( ( rc = (rterror)GetNextPZN( &zpznpflege ) ) == no_error )
   {
	   if (strncmp(zpznpflege.DEZAP_SA, "03", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 03: DKSOA */
		{
			bool bDezapGefuellt = FALSE;

			if ( (rterror)startBrowseCbaselistarticles( zpznpflege.ARTIKEL_NR ) != no_error )
			{
				WriteLog( fun, -1, "Programm-Abbruch" );
				return be_impaired;
			}
	
			while ( ( rc = (rterror)GetNextCbaselistarticles( &cbaselistarticles ) ) != db_error )
			{
				/* wenn kein Satz mehr gefunden, aber schon mindestens einer geschrieben, Schleife verlassen */
				if ( rc == eof && bDezapGefuellt)
				{
					break;
				}

				/* Returncode merken für spätere Abfrage */
				rterror rc_save = rc;

				cbaselistarticles.ARTICLENO = zpznpflege.ARTIKEL_NR;

				bSaveDksoa = (bool)ConvertDksoa( &dezapdksoa, &cbaselistarticles, describedksoa, rc );
				bDezapGefuellt = TRUE;

				if(bSaveDksoa)
				{
					WandelCobol( szBufDksoa, (char *)&dezapdksoa, describedksoa, SATZANZAHL( describedksoa ) ); 

					if ( ( rc = (rterror)WriteToDezap( szBufDksoa, fp, iSize, plCount + 03 ) ) != no_error )
					{
							WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDksoa, p->spFile );
							break;
					}

					memset( (char *)&dezapdksoa, ' ', sizeof( dezapdksoaO ) );
				}

				/* wenn überhaupt kein DB-Satz gefunden, musste noch ein Satz mit Löschkennzeichen geschrieben werden, daher Schleife erst hier verlassen */
				if ( rc_save == eof )
				{
					break;
				}
			}

			endBrowseCbaselistarticles( );
		}
		else if (strncmp(zpznpflege.DEZAP_SA, "08", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 08: DKRIS */
		{
			bool bDezapGefuellt = FALSE;

			if ( (rterror)startBrowseZartverk( zpznpflege.ARTIKEL_NR ) != no_error )
			{
				WriteLog( fun, -1, "Programm-Abbruch" );
				return be_impaired;
			}
	
			while ( ( rc = (rterror)GetNextZartverk( &zartverk ) ) != db_error )
			{
				/* Füllen der Struktur nur, wenn noch ein Satz gefunden oder gar keiner vorhanden */
				if ( !( rc == eof && bDezapGefuellt))
				{
					/* Returncode merken für spätere Abfrage */

					zartverk.ARTIKEL_NR_BAS = zpznpflege.ARTIKEL_NR;

					ConvertDkris( &dezapdkris, &zartverk, describedkris, rc );
					bDezapGefuellt = TRUE;
				}

				/* wenn kein DB-Satz mehr gefunden, muss jetzt DEZAP geschrieben werden */
				if ( rc == eof )
				{
					WandelCobol( szBufDkris, (char *)&dezapdkris, describedkris, SATZANZAHL( describedkris ) ); 

					if ( ( rc = (rterror)WriteToDezap( szBufDkris, fp, iSize, plCount + 8 ) ) != no_error )
					{
							WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDkste, p->spFile );
							break;
					}

					memset( (char *)&dezapdkris, ' ', sizeof( dezapdkrisO ) );
					break;
				}
			}

			endBrowseZartverk ( );
		}
		else if (strncmp(zpznpflege.DEZAP_SA, "09", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 09: DKEAN */
		{
			ean.ARTIKEL_NR = zpznpflege.ARTIKEL_NR;

	        if ( ( rc = (rterror)GetEan( &ean ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die PZN nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
				ean.ARTIKEL_NR = zpznpflege.ARTIKEL_NR;
			}

			bSaveEan = (bool)ConvertDkean( &dezapean, &ean, describeean, rc );

			if(bSaveEan)
			{
                WandelCobol( szBufEan, (char *)&dezapean, describeean, SATZANZAHL( describeean ) );

				if ( ( rc = (rterror)WriteToDezap( szBufEan, fp, iSize, plCount + 9 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufEan, p->spFile );
                        break;
                }

                memset( (char *)&dezapean, ' ', sizeof( dezapeanO ) );
	         }
		} 
		/* else if (strncmp(zpznpflege.DEZAP_SA, "10", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   // Satzart 10: DKGFG (nur Gefahrstoffsymbole) 
		{
		    article.ARTIKEL_NR = zpznpflege.ARTIKEL_NR;

	        if ( ( rc = (rterror)GetZartikel( &article ) ) == no_error )
			{
				ConvertDkgfg( &dezapdkgfg, &article, describedkgfg, rc );

				WandelCobol( szBufDkgfg, (char *)&dezapdkgfg, describedkgfg, SATZANZAHL( describedkgfg ) );
				if ( ( rc = (rterror)WriteToDezap( szBufDkgfg, fp, iSize, plCount + 10 ) ) != no_error )
				{
						WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDkgfg, p->spFile );
						break;
				}

				memset( (char *)&dezapdkgfg, ' ', sizeof( dezapdkgfgO ) );
			}
		}  */
		else if (strncmp(zpznpflege.DEZAP_SA, "11", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 11: DKAFF */
		{
		    carticlelang.ARTICLENO = zpznpflege.ARTIKEL_NR;

			// im Prewhole CH stehen die deutschen Bezeichnungen in carticlelang
			if (IsCountry(p->Kuerzel, "CH") && p->Prewhole == 1)
				strcpy (carticlelang.LANGID, "DE");
			// im Wholesale CH stehen die französischen Bezeichnungen in carticlelang
			else if (IsCountry(p->Kuerzel, "CH") && p->Prewhole == 0)
				strcpy (carticlelang.LANGID, "FR");
			// in Bulgarien stehen die englischen Bezeichnungen in carticlelang
			else if (IsCountry(p->Kuerzel, "BG") )
				strcpy (carticlelang.LANGID, "EN");
			else
				strcpy (carticlelang.LANGID, "??");

	        if ( ( rc = (rterror)GetCarticlelang( &carticlelang ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die PZN nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
			    carticlelang.ARTICLENO = zpznpflege.ARTIKEL_NR;
			}

	        bSaveDkaff = (bool)ConvertDkaff( &dezapdkaff, &carticlelang, describedkaff, rc );

			if(bSaveDkaff)
			{
                WandelCobol( szBufDkaff, (char *)&dezapdkaff, describedkaff, SATZANZAHL( describedkaff ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkaff, fp, iSize, plCount + 11 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkaff, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkaff, ' ', sizeof( dezapdkaffO ) );
			}
		} 
		else if (strncmp(zpznpflege.DEZAP_SA, "13", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 13: DKSTE */
		{
			bool bDezapGefuellt = FALSE;

		    ccpvalidityperiod.ARTICLE_NO_PACK = zpznpflege.ARTIKEL_NR;

	        if ( ( rc = (rterror)GetCcpvalidityperiod ( &ccpvalidityperiod ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die PZN nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
			    ccpvalidityperiod.ARTICLE_NO_PACK = zpznpflege.ARTIKEL_NR;

				ConvertDkste( &dezapdkste, &cartcompack, &ccpvalidityperiod, describedkste, rc );

				WandelCobol( szBufDkste, (char *)&dezapdkste, describedkste, SATZANZAHL( describedkste ) ); 

				if ( ( rc = (rterror)WriteToDezap( szBufDkste, fp, iSize, plCount + 13 ) ) != no_error )
				{
						WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
									szBufDkste, p->spFile );
						break;
				}

				memset( (char *)&dezapdkste, ' ', sizeof( dezapdksteO ) );
			}
			else
			{
				if ( (rterror)startBrowseCartcompack( zpznpflege.ARTIKEL_NR ) != no_error )
				{
					WriteLog( fun, -1, "Programm-Abbruch" );
					return be_impaired;
				}

				while ( ( rc = (rterror)GetNextCartcompack( &cartcompack ) ) != db_error )
				{
					/* kein Satz mehr gefunden: wenn schon mindestens einer geschrieben, Schleife verlassen, 
					   ansonsten PZN merken fürs Schreiben eines Satzes mit Löschkennzeichen */
					if ( rc == eof )
					{
						if ( bDezapGefuellt )
							break;
						else
						    ccpvalidityperiod.ARTICLE_NO_PACK = zpznpflege.ARTIKEL_NR;
					}

					bSaveDkste = (bool)ConvertDkste( &dezapdkste, &cartcompack, &ccpvalidityperiod, describedkste, rc );
					bDezapGefuellt = TRUE;

					if(bSaveDkste)
					{
						WandelCobol( szBufDkste, (char *)&dezapdkste, describedkste, SATZANZAHL( describedkste ) ); 

						if ( ( rc = (rterror)WriteToDezap( szBufDkste, fp, iSize, plCount + 13 ) ) != no_error )
						{
								WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
											szBufDkste, p->spFile );
								break;
						}

						memset( (char *)&dezapdkste, ' ', sizeof( dezapdksteO ) );
					}

				}

				endBrowseCartcompack ( );
			}
		}
		else if (strncmp(zpznpflege.DEZAP_SA, "22", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 22: DKCRR */
		{
			bool bDezapGefuellt = FALSE;

			if ( (rterror)startBrowseZchargenrueckruf( zpznpflege.ARTIKEL_NR ) != no_error )
			{
				WriteLog( fun, -1, "Programm-Abbruch" );
				return be_impaired;
			}
	
			while ( ( rc = (rterror)GetNextZchargenrueckruf( &zchargenrueckruf ) ) != db_error )
			{
				/* wenn kein Satz mehr gefunden, aber schon mindestens einer geschrieben, Schleife verlassen */
				if ( rc == eof && bDezapGefuellt)
				{
					break;
				}

				/* Returncode merken für spätere Abfrage */
				rterror rc_save = rc;

				zchargenrueckruf.ARTIKEL_NR = zpznpflege.ARTIKEL_NR;

				bSaveDkcrr = (bool)ConvertDkcrr( &dezapdkcrr, &zchargenrueckruf, describedkcrr, rc );
				bDezapGefuellt = TRUE;

				if(bSaveDkcrr)
				{
					WandelCobol( szBufDkcrr, (char *)&dezapdkcrr, describedkcrr, SATZANZAHL( describedkcrr ) ); 

					if ( ( rc = (rterror)WriteToDezap( szBufDkcrr, fp, iSize, plCount + 22 ) ) != no_error )
					{
							WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDkcrr, p->spFile );
							break;
					}

					memset( (char *)&dezapdkcrr, ' ', sizeof( dezapdkcrrO ) );
				}

				/* wenn überhaupt kein DB-Satz gefunden, musste noch ein Satz mit Löschkennzeichen geschrieben werden, daher Schleife erst hier verlassen */
				if ( rc_save == eof )
				{
					break;
				}
			}

			endBrowseZchargenrueckruf( );
		}
/*		else if (strncmp(zpznpflege.DEZAP_SA, "23", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   // Satzart 23: DKGAL 
		{
		    cgaloart.ARTICLENO = zpznpflege.ARTIKEL_NR;
		    cgalonam.ARTICLENO = zpznpflege.ARTIKEL_NR;

	        if ( ( rc = (rterror)GetCgaloart( &cgaloart ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			// wenn Satz nicht gefunden, muss zumindest die PZN nochmal versorgt werden, um den Löschsatz schreiben zu können 
			if ( rc == eof )
			{
			    carticlelang.ARTICLENO = zpznpflege.ARTIKEL_NR;
			}

			ConvertDkgal( &dezapdkgal, &cgaloart, describedkgal, rc );

			// jetzt noch die Bezeichnungen in mehreren Sprachen 
			InitCgalonam( &cgalonam );            

			while( ( rc = (rterror)GetCgalonam( &cgalonam ) ) == no_error )
			{
				ConvertCgalonam( &dezapdkgal, &cgalonam, describedkgal );
			}

			if ( rc == db_error )
					break;

			WandelCobol( szBufDkgal, (char *)&dezapdkgal, describedkgal, SATZANZAHL( describedkgal ) ); 

			if ( ( rc = (rterror)WriteToDezap( szBufDkgal, fp, iSize, plCount + 23 ) ) != no_error )
			{
					WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
								szBufDkgal, p->spFile );
					break;
			}

			memset( (char *)&dezapdkgal, ' ', sizeof( dezapdkgalO ) );

		} */
		else if (strncmp(zpznpflege.DEZAP_SA, "28", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 28: DKRAB (PZN-Ebene) */
		{
			bool bDezapGefuellt = FALSE;

			if ( (rterror)startBrowseCdiscount_Pzn( zpznpflege.ARTIKEL_NR, lDateCdiscount ) != no_error )
			{
				WriteLog( fun, -1, "Programm-Abbruch" );
				return be_impaired;
			}
	
			while ( ( rc = (rterror)GetNextCdiscount_Pzn( &cdiscount ) ) != db_error )
			{
				/* wenn kein Satz mehr gefunden, aber schon mindestens einer geschrieben, Schleife verlassen */
				if ( rc == eof && bDezapGefuellt)
				{
					break;
				}

				/* Returncode merken für spätere Abfrage */
				rterror rc_save = rc;

				cdiscount.ARTICLENO = zpznpflege.ARTIKEL_NR;
				cdiscount.DISCOUNTGRPNO = 0;
				cdiscount.MANUFACTURERNO = 0;
				cdiscount.ARTCATEGORYNO = 0;

				bSaveDkrab = (bool)ConvertDkrab( &dezapdkrab, &cdiscount, describedkrab, rc );
				bDezapGefuellt = TRUE;

				if(bSaveDkrab)
				{
					WandelCobol( szBufDkrab, (char *)&dezapdkrab, describedkrab, SATZANZAHL( describedkrab ) ); 

					if ( ( rc = (rterror)WriteToDezap( szBufDkrab, fp, iSize, plCount + 28 ) ) != no_error )
					{
							WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDkrab, p->spFile );
							break;
					}

					memset( (char *)&dezapdkrab, ' ', sizeof( dezapdkrabO ) );
				}

				/* wenn überhaupt kein DB-Satz gefunden, musste noch ein Satz mit Löschkennzeichen geschrieben werden, daher Schleife erst hier verlassen */
				if ( rc_save == eof )
				{
					break;
				}
			}

			endBrowseCdiscount_Pzn( );
		}
		else if (strncmp(zpznpflege.DEZAP_SA, "33", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 33: DKAZB */
		{
		    article.ARTIKEL_NR = zpznpflege.ARTIKEL_NR;

	        if ( ( rc = (rterror)GetZartikel( &article ) ) == db_error )
	        {
		       WriteLog( fun, -1, "Programm-Abbruch" );
		       return be_impaired;
		    }

			/* wenn Satz nicht gefunden, muss zumindest die PZN nochmal versorgt werden, um den Löschsatz schreiben zu können */
			if ( rc == eof )
			{
			    article.ARTIKEL_NR = zpznpflege.ARTIKEL_NR;
			}

	        bSaveDkazb = (bool)ConvertDkazb( &dezapdkazb, &article, describedkazb, rc );

			if(bSaveDkazb)
			{
                WandelCobol( szBufDkazb, (char *)&dezapdkazb, describedkazb, SATZANZAHL( describedkazb ) );
                if ( ( rc = (rterror)WriteToDezap( szBufDkazb, fp, iSize, plCount + 33 ) ) != no_error )
                {
                        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                                      szBufDkazb, p->spFile );
                        break;
                }

                memset( (char *)&dezapdkazb, ' ', sizeof( dezapdkazbO ) );
			}
		} 
		else if (strncmp(zpznpflege.DEZAP_SA, "34", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 34: DKACO */
		{
			bool bDezapGefuellt = FALSE;

			if ( (rterror)startBrowseCarticlecodes( zpznpflege.ARTIKEL_NR ) != no_error )
			{
				WriteLog( fun, -1, "Programm-Abbruch" );
				return be_impaired;
			}
	
			while ( ( rc = (rterror)GetNextCarticlecodes( &articlecodes ) ) != db_error )
			{
				/* wenn kein Satz mehr gefunden, aber schon mindestens einer geschrieben, Schleife verlassen */
				if ( rc == eof && bDezapGefuellt)
				{
					break;
				}

				/* Returncode merken für spätere Abfrage */
				rterror rc_save = rc;

				articlecodes.ARTICLENO = zpznpflege.ARTIKEL_NR;

				bSaveDkaco = (bool)ConvertDkaco( &dezapdkaco, &articlecodes, describedkaco, rc );
				bDezapGefuellt = TRUE;

				if(bSaveDkaco)
				{
					WandelCobol( szBufDkaco, (char *)&dezapdkaco, describedkaco, SATZANZAHL( describedkaco ) ); 

					if ( ( rc = (rterror)WriteToDezap( szBufDkaco, fp, iSize, plCount + 34 ) ) != no_error )
					{
							WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
										szBufDkcrr, p->spFile );
							break;
					}

					memset( (char *)&dezapdkaco, ' ', sizeof( dezapdkacoO ) );
				}

				/* wenn überhaupt kein DB-Satz gefunden, musste noch ein Satz mit Löschkennzeichen geschrieben werden, daher Schleife erst hier verlassen */
				if ( rc_save == eof )
				{
					break;
				}
			}

			endBrowseCarticlecodes( );
		}
		else if (strncmp(zpznpflege.DEZAP_SA, "39", L_ZPZNPFLEGE_DEZAP_SA) == 0)
	   /* Satzart 39: DEPAU */
		{
		    article.ARTIKEL_NR = zpznpflege.ARTIKEL_NR;

	        if ( ( rc = (rterror)GetZartikel( &article ) ) == no_error )
			{
				bSaveDepau = (bool)ConvertDepau( &dezapdepau, &article, describedepau, rc );

				if(bSaveDepau)
				{
					WandelCobol( szBufDepau, (char *)&dezapdepau, describedepau, SATZANZAHL( describedepau ) );
					if ( ( rc = (rterror)WriteToDezap( szBufDepau, fp, iSize, plCount + 39 ) ) != no_error )
					{
							WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
											szBufDepau, p->spFile );
							break;
					}

					memset( (char *)&dezapdepau, ' ', sizeof( dezapdepauO ) );
				}
			}
		} 
	}

    /* jetzt noch pro (indizierter) Satzart prüfen, ob noch ein halbvoller DEZAP-Satz weggeschrieben werden muss */
    if(strncmp(dezapdksoa.ZAPSA03,"  ",L_DEZAPDKSOA_ZAPSA03))
    {
        WandelCobol( szBufDksoa, (char *)&dezapdksoa, describedksoa, SATZANZAHL( describedksoa ) );

		if ( ( rc = (rterror)WriteToDezap( szBufDksoa, fp, iSize, plCount + 3 ) ) != no_error )
        {
	        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
		            szBufDksoa, p->spFile );
        }
    }

    if(strncmp(dezapean.ZAPSA09,"  ",L_DEZAPDKEAN_ZAPSA09))
    {
        WandelCobol( szBufEan, (char *)&dezapean, describeean, SATZANZAHL( describeean ) );

		if ( ( rc = (rterror)WriteToDezap( szBufEan, fp, iSize, plCount + 9 ) ) != no_error )
        {
	        WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
		            szBufEan, p->spFile );
        }
    }

    if(strncmp(dezapdkaff.ZAPSA11,"  ",L_DEZAPDKAFF_ZAPSA11))
    {
        WandelCobol( szBufDkaff, (char *)&dezapdkaff, describedkaff, SATZANZAHL( describedkaff ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkaff, fp, iSize, plCount + 11 ) ) != no_error )
        {
			WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
				    szBufDkaff, p->spFile );
        }
    }

    if(strncmp(dezapdkste.ZAPSA13,"  ",L_DEZAPDKSTE_ZAPSA13))
    {
        WandelCobol( szBufDkste, (char *)&dezapdkste, describedkste, SATZANZAHL( describedkste ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkste, fp, iSize, plCount + 13 ) ) != no_error )
        {
			WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
				    szBufDkste, p->spFile );
        }
    }

    if(strncmp(dezapdkcrr.ZAPSA22,"  ",L_DEZAPDKCRR_ZAPSA22))
    {
        WandelCobol( szBufDkcrr, (char *)&dezapdkcrr, describedkcrr, SATZANZAHL( describedkcrr ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkcrr, fp, iSize, plCount + 22 ) ) != no_error )
        {
			WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                    szBufDkcrr, p->spFile );
        }
    }

    if(strncmp(dezapdkrab.ZAPSA28,"  ",L_DEZAPDKRAB_ZAPSA28))
    {
        WandelCobol( szBufDkrab, (char *)&dezapdkrab, describedkrab, SATZANZAHL( describedkrab ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkrab, fp, iSize, plCount + 28 ) ) != no_error )
        {
			WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                    szBufDkrab, p->spFile );
        }
    }

    if(strncmp(dezapdkazb.ZAPSA33,"  ",L_DEZAPDKAZB_ZAPSA33))
    {
        WandelCobol( szBufDkazb, (char *)&dezapdkazb, describedkazb, SATZANZAHL( describedkazb ) );
        if ( ( rc = (rterror)WriteToDezap( szBufDkazb, fp, iSize, plCount + 33 ) ) != no_error )
        {
                WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                          szBufDkazb, p->spFile );
        }
    }

    if(strncmp(dezapdkaco.ZAPSA34,"  ", L_DEZAPDKACO_ZAPSA34))
    {
        WandelCobol( szBufDkaco, (char *)&dezapdkaco, describedkaco, SATZANZAHL( describedkaco ) );

		if ( ( rc = (rterror)WriteToDezap ( szBufDkaco, fp, iSize, plCount + 34 ) ) != no_error )
        {
			WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
                    szBufDkaco, p->spFile );
        }
    }

    if(strncmp(dezapdepau.ZAPSA39,"  ", L_DEZAPDEPAU_ZAPSA39))
    {
		WandelCobol( szBufDepau, (char *)&dezapdepau, describedepau, SATZANZAHL( describedepau ) );
		if ( ( rc = (rterror)WriteToDezap( szBufDepau, fp, iSize, plCount + 39 ) ) != no_error )
		{
				WriteLog( fun, -1, "satz <%19s> konnte nicht in datei %s eingefuegt werden",
								szBufDepau, p->spFile );
		}
    }

    return (rc == db_error || rc == write_error) ? be_impaired : lCountSet;
 }
