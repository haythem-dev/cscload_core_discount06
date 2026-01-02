// ZdpUtil.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "Shlobj.h" 
#include "ZdpUtil.h"
#include <phxlib/countryquery.h>

#include "MainFrm.h"
#include "ZdpUtilDoc.h"
#include "ZdpUtilView.h"
#include "GetBranches.h"
#include "MenuNumbers.h"
#include "LineprotDlg.h"

#include "ConSoVa2.h"	
#include "UADMLoginManager.h"
#include <libscsvoodoo/libscsvoodoo.h>

// fuer Knoedel
#include <eklibs/hamfcs/hBmpButton.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "../cdm_version.h"

#define ZDPUTIL_VERSION "1.111"
static char* SCCSID = "@(#)PHOENIX Stand: " CDM_VERSION " - 1.111 : ZdpUtil 02.12.2025 : KT";

/*!
\page page1 ZdpUtil.exe

\version	1.110
\date		18.11.2025
\internal
- CPR0002596 - FR - Medical Device Actors in ZDP Improvement
\endinternal
\customer
\de
- CPR0002596 - FR - Medical Device Actors in ZDP Improvement
\en
- CPR0002596 - FR - Medical Device Actors in ZDP Improvement
\endcustomer
____________________________________________________________________________________
\version	1.109
\date		11.11.2025
\internal
- TA: CPR0002057 - All - integration into UADM and use of new login and password policy
\endinternal
\customer
\de
- CPR0002057 - All - Integration in UADM und Nutzung des neuen Logins und Password Policy
\en
- CPR0002057 - All - integration into UADM and use of new login and password policy
\endcustomer
____________________________________________________________________________________
\version	1.108
\date		18.08.2025
\internal
- CPR-240526 - AT - Extension of EAN-Code in SA15 for class 3 medical Products
\endinternal
\customer
\de
- CPR-240526 - AT - Extension of EAN-Code in SA15 for class 3 medical Products
\en
- CPR-240526 - AT - Extension of EAN-Code in SA15 for class 3 medical Products
\endcustomer
____________________________________________________________________________________
\version	1.107
\date		30.06.2025
\internal
- SCTASK0054765 - HR - datefrom = today is now allowed for discounts in Croatia
\endinternal
\customer
\de
- SCTASK0054765 - HR - datefrom = today is now allowed for discounts in Croatia
\en
- SCTASK0054765 - HR - datefrom = today is now allowed for discounts in Croatia
\endcustomer
____________________________________________________________________________________

\version	1.106
\date		23.01.2025
\internal
- CPR-230792 - DE - Add missing examination and conversion pzn -> articleno
- CPR-240764 - HR - New field: discountarticle can be uploaded to cdiscounts
\endinternal
\customer
\de
- CPR-230792 - DE - Pruefung fuer fehlende pzn ergaenzt -> articleno
- CPR-240764 - HR - Neues Feld: Naturalrabatt für Cdiscounts verfügbar
\en
- CPR-230792 - DE - Add missing examination and conversion pzn -> articleno
- CPR-240764 - HR - New field: discountarticle can be uploaded to cdiscounts
\endcustomer
____________________________________________________________________________________

\version	1.105
\date		11.11.2024
\internal
- I-24098179 - DE - Multiple product base lists bug fix
\endinternal
\customer
\de
- I-24098179 - DE - Multiple product base lists bug fix
\en
- I-24098179 - DE - Multiple product base lists bug fix
\endcustomer
____________________________________________________________________________________

\version	1.104
\date		23.09.2024
\internal
- CPR-221104 - DE - Multiple product base lists
\endinternal
\customer
\de
- CPR-221104 - DE - Multiple product base lists
\en
- CPR-221104 - DE - Multiple product base lists
\endcustomer
____________________________________________________________________________________

\version	1.103
\date		01.08.2024
\internal
- SR-24090413/SR-24098106: Mass update of bliesort activated also for HR and FR
\endinternal
\customer
\de
- SR-24090413/SR-24098106: Massenupdate von bliesort für Kroatien und Frankreich aktiviert
\en
- SR-24090413/SR-24098106: Mass update of bliesort activated for Croatia and France
\endcustomer
____________________________________________________________________________________

\version	1.102
\date		01.02.2024
\internal
- CPR-230792: Enhance ZDPUtil for Masterdata maintenance
- CPR-221009: Qick Fix Frankreich AEP == GEP / Grosso
			  Artikelpage1 : AEP == GEP / Grosso
			  Artikelprices : AEP == GEP / Grosso
\endinternal
\customer
\de
- CPR-230792: Erweiterung fuer die Stammdatenpflege
- CPR-221009: Qick Fix Frankreich AEP == GEP / Grosso
			  Artikelpage1 : AEP == GEP / Grosso
			  Artikelprices : AEP == GEP / Grosso
\en
- CPR-230792: Enhance ZDPUtil for Masterdata maintenance
- CPR-221009: Qick Fix Frankreich AEP == GEP / Grosso
			  Artikelpage1 : AEP == GEP / Grosso
			  Artikelprices : AEP == GEP / Grosso
\endcustomer
____________________________________________________________________________________

\version	1.101
\date		11.01.2024
\internal
- KO: CPR-221009: new allowed value 27 for CARTICLECODES.CODETYPE
\endinternal
\customer
\de
- CPR-221009: neuer zulaessiger Wert 27 fuer CARTICLECODES.CODETYPE
\en
- CPR-221009: new allowed value 27 for CARTICLECODES.CODETYPE
\endcustomer
____________________________________________________________________________________

\version	1.100
\date		06.11.2023
\internal
- KT: SR-23122143: new allowed value 12 for CDISCOUNT.DISCOUNTSPEC
\endinternal
\customer
\de
- SR-23122143: neuer zulaessiger Wert 12 fuer CDISCOUNT.DISCOUNTSPEC
\en
- SR-23122143: new allowed value 12 for CDISCOUNT.DISCOUNTSPEC
\endcustomer
____________________________________________________________________________________

\version	1.99
\date		28.11.2022
\internal
- MH: CPR-220839: new allowed value 'F' for ZARTIKEL.PRODUKTART, only valid for Germany
- OW: CPR-220062: new allowed value 'ABCDE' for ZARTIKKEL.PRODUKTART, only valid for Switzerland 
\endinternal
\customer
\de
- CPR-220839: neuer zulaessiger Wert 'F' fuer ZARTIKEL.PRODUKTART, nur gueltig in Deutschland
- CPR-220062: neuer zulaessiger Wert 'ABCDE' fuer ZARTIKKEL.PRODUKTART, nur gueltig in der Schweiz 
\en
- CPR-220839: new allowed value 'F' for ZARTIKEL.PRODUKTART, only vaid for Germany
- CPR-220062: new allowed value 'ABCDE' for ZARTIKKEL.PRODUKTART, only valid for Switzerland 
\endcustomer
____________________________________________________________________________________

\version	1.98
\date		24.06.2022
\internal
- KT: I-22037373 DE zartikel: field 'gewicht' added - 'datum_mwe' was set automatically, if measure or weight is updated
- KT: max. number of fields in the fields mask: changed from 50 to 55
\endinternal
\customer
\de
- I-22037373 DE Laden der zartikel Felder: Länge, Höhe, Breite, Gewicht
\en
- I-22037373 DE Loading of zartikel fields: Länge, Höhe, Breite, Gewicht
\endcustomer
____________________________________________________________________________________

\version	1.97
\date		24.02.2022
\internal
- KT: SR-22018790 DE Laden der Felder laenge, hoehe, breite von zartikel
\endinternal
\customer
\de
- SR-22018790 DE Laden der zartikel Felder: Länge, Höhe, Breite
\en
- SR-22018790 DE Loading of zartikel fields: Länge, Höhe, Breite
\endcustomer
____________________________________________________________________________________

\version	1.96
\date		08.02.2022
\internal
- KT: CPR-210587 DE Laden zartikel.cmi_flag
\endinternal
\customer
\de
- CPR-210587 DE Laden von Kennzeichen "CMI" (zartikel.cmi_flag)
\en
- CPR-210587 DE Loading of zartikel.cmi_flag (de)
\endcustomer
____________________________________________________________________________________
\version	1.95
\date		02.12.2021
\internal
- KT: CPR-210155 HR Laden cdiscount.promotion_no
\endinternal
\customer
\de
- CPR-210155 HR Laden von cdiscount.promotion_no
\en
- CPR-210155 HR Loading of cdiscount.promotion_no
\endcustomer
____________________________________________________________________________________
\version	1.94
\date		09.07.2021
\internal
- KT: CPR-210155 - Mode 20 zum Laden von ean.ean_nr
- KT: Löschen von Datensätzen aus Tabelle 'ean' möglich
- KT: "nur mit kurzem Verfall lieferbar" (carticleext.shortexpiryflag) ladbar
- KT: "Einkauf nicht möglich" (zartikel.bestellsperre) ladbar
- KT: Neuer Menüpunkt: Utilities->Protokoll Datei holen (Upd Excel)
\endinternal
\customer
\de
-  CPR-210155 - Mode 20 zum Laden von "ean_nr" (ean.ean_nr)
-  Laden von "nur mit kurzem Verfall lieferbar" (carticleext.shortexpiryflag)
-  Laden von "Einkauf nicht möglich" (zartikel.bestellsperre)
-  Neuer Menüpunkt: 'Utilities->Protokoll Datei holen (Upd Excel)' zum Übertragen von Protokoll-Dateien nach Windows
\en
-  CPR-200089 - new mode 20 for loading ean.ean_nr
-  Loading of carticleext.shortexpiryflag (de)
-  Loading of zartikel.bestellsperre (de)
-  New menu: 'Utilities->Protokoll Datei holen (Upd Excel)' 
\endcustomer
____________________________________________________________________________________
\version	1.93
\date		05.03.2021
\internal
- KT: CPR-200089 - Mode 19 zum Laden von cibt
\endinternal
\customer
\de
-  CPR-200089 - Mode 19 zum Laden von "festver. Regionalhausartikel" (cibt.isfixedregional)
\en
-  CPR-200089 - new mode 19 for loading cibt.isfixedregional (de)
\endcustomer
____________________________________________________________________________________
\version	1.92
\date		14.10.2019
\internal
- WH: Laden von export interdit (fr)
\endinternal
\customer
\de
-  Laden von export interdit (fr)
\en
-  Loading of export interdit (fr)
\endcustomer
____________________________________________________________________________________
\version	1.91
\date		24.09.2019
\internal
- WH: Laden von g_un_nr / datum_lieferbar_ab 
\endinternal
\customer
\de
-  Laden von g_un_nr / datum_lieferbar_ab 
\en
-  Loading of g_un_nr / datum_lieferbar_ab 
\endcustomer
____________________________________________________________________________________
\version	1.90
\date		11.01.2019
\internal
- TH: DACH-BT Laden zartikel.chargenartikel
\endinternal
\customer
	\de
	- DACH-BT Laden zartikel.chargenartikel
	\en
	
\endcustomer
____________________________________________________________________________________
\version	1.89
\date		12.11.2018
\internal
- TH: CPR-170598 Laden der zartikel-Felder nem_phagropruefung, nem_zertifikat, apo_auto_faehig_knapp, apo_auto_faehig_rowa
\endinternal
\customer
	\de
	- CPR-170598 Laden der zartikel-Felder nem_phagropruefung, nem_zertifikat, apo_auto_faehig_knapp, apo_auto_faehig_rowa
	\en

\endcustomer

____________________________________________________________________________________
\version	1.88
\date		21.06.2018
\internal
- TH: neues Kriterium "Rabatt-% vom Wert" zum Beenden von Rabatten
\endinternal
\customer
	\de
	- neues Kriterium "Rabatt-% vom Wert" zum Beenden von Rabatten
	\en
	- new value "discount value %" for stopping discounts
\endcustomer

____________________________________________________________________________________
\version	1.87
\date		20.04.2018
\internal
- TH: CPR-170659 - Mode 18 zum Laden von cimexblock
\endinternal
\customer
	\de
	CPR-170659 - Mode 18 zum Laden von Import / Export- Sperren
	\en
	CPR-170659 - new mode 18 for loading import / export blocks
\endcustomer
____________________________________________________________________________________
\version	1.86
\date		23.02.2018
\internal
- TH: CPR-170692 Laden zweier zusätzlicher zartikel-Felder --> ARTIKEL_GELOESCHT / NICHT_UEBER_XML
- TH: Laden zartaustria.nachlieferung
\endinternal
\customer
	\de
	CPR-170692 Laden zweier zusätzlicher zartikel-Felder --> ARTIKEL_GELOESCHT / NICHT_UEBER_XML
	Laden zartaustria.nachlieferung / Wafo- Artikel (AT)
	\en
	CPR-170692 Loading of two additional zartikel-fields --> ARTIKEL_GELOESCHT / NICHT_UEBER_XML
\endcustomer

____________________________________________________________________________________
\version	1.85
\date		15.09.2017
\internal
- TH: Umbennung zweier Felder UpdExcel / PflFelder --> NIEDRSPANNE_ELAC / NIEDRSPANNE_SONST
\endinternal
\customer
	\de
	Umbennung zweier Felder UpdExcel / PflFelder --> NIEDRSPANNE_ELAC / NIEDRSPANNE_SONST
	\en
	
\endcustomer
____________________________________________________________________________________
\version	1.84
\date		17.03.2017
\internal
- TH: CR-15A029 - Mode 16 zum Laden von zartserbia
\endinternal
\customer
	\de
	CR-15A029 - Mode 16 zum Laden von zartserbia
	\en
	CR-15A029 - new mode 16 for loading Serbian distribution restrictions
\endcustomer
____________________________________________________________________________________
\version	1.83
\date		22.02.2017
\internal
- TH: CR-16D056 - Mode 15 zum Laden von zchargenrueckruf
\endinternal
\customer
	\de
	CR-16D056 - Mode 15 zum Laden von zchargenrueckruf
	\en
	CR-16D056 - new mode 15 for loading zchargenrueckruf
\endcustomer
____________________________________________________________________________________
\version	1.82
\date		06.10.2016
\internal
- TH: CR-16A023 - Deaktivierung von zartfrance.code_lppr
\endinternal
\customer
	\de
	CR-16A023 - Deaktivierung von zartfrance.code_lppr
	\en
	CR-16A023 - zartfrance.code_lppr deactivated
\endcustomer
____________________________________________________________________________________
\version	1.81
\date		12.08.2016
\internal
- TH: SR-16067705 - neues Feld zartikel.artikel_gesperrt
\endinternal
\customer
	\de
	SR-16067705 - neues Feld zartikel.artikel_gesperrt
	\en
	SR-16067705 - new field zartikel.artikel_gesperrt
\endcustomer
____________________________________________________________________________________
\version	1.80
\date		25.07.2016
\internal
- TH: BugFix I-16029079 - dateto set to "today" if no date is given explicitly
\endinternal
\customer
	\de
	I-16029079 - dateto set to "today" if no date is given explicitly
	\en
	I-16029079 - dateto set to "today" if no date is given explicitly
\endcustomer
____________________________________________________________________________________
\version	1.79
\date		19.07.2016
\internal
- TH: BugFix SR-16060480 - dateto is also allowed to be "today"
\endinternal
\customer
	\de
	BugFix SR-16060480 - dateto is also allowed to be "today"
	\en
	BugFix SR-16060480 - dateto is also allowed to be "today"
\endcustomer
____________________________________________________________________________________
\version	1.78
\date		11.07.2016
\internal
- TH: BugFix for Articlecodes
- TH: Plausi- Check monthlydiscount <-> discountspec (AT)
- TH: Sicherheitsnachfrage für Beenden Rabatte ohne Angabe einer PZN
- TH: Plausi- Prüfung Start-/Endedatum bei Einspielen/Beenden von Rabatten in Abhängigkeit von Monatsrabatt
- TH: CR-16D054 testRun zputil vorab, um die Anzahl der betroffenen Zeilen zu ermitteln (vorerst nur für das Beenden von Discounts)
- TH: FR PULSE - neues Feld carticleext.high_therapeutic_value
\endinternal
\customer
	\de
	Plausi- Check monthlydiscount <-> discountspec (AT)
	Sicherheitsnachfrage für Beenden Rabatte ohne Angabe einer PZN
	Plausi- Prüfung Start-/Endedatum bei Einspielen/Beenden von Rabatten in Abhängigkeit von Monatsrabatt
	CR-16D054 vorab wird die Anzahl der betroffenen Zeilen ermittelt (vorerst nur für das Beenden von Discounts)
	FR PULSE - neues Feld carticleext.high_therapeutic_value
 	\en
	Plausi- Check monthlydiscount <-> discountspec (AT)
	confirmation required for stopping discounts without article number
	checking dates for monthly discounts
	when stopping discounts, number of affected rows is displayed in advance
	FR PULSE - new flag carticleext.high_therapeutic_value
\endcustomer

____________________________________________________________________________________
\version	1.77
\date		08.12.2015
\internal
- RK: CR-15D087: DE Neue Felder bei zdputil
- RK: SR-15059217: ZDP-Schweiz - UTIL Zusatzfelder
\endinternal
\customer
	\de
 - CR-15D087: Neue Felder bei zdputil (DE)
 - SR-15059217: UTIL Zusatzfelder (CH)
 	\en
 - CR-15D087: new fields for Germany
 - SR-15059217: new fields for Switzerland
\endcustomer
____________________________________________________________________________________
\version	1.76
\date		22.10.2015
\internal
- TH: neues Feld zartikel.zentralppelist
\endinternal

________________________________________________________________________________________
\version	1.75
\date		20.07.2015
\internal
- TH: Abfangen "blanks" tatsächlich nur in csv- Dateinamen, nicht im gesamten Pfad
\endinternal

________________________________________________________________________________________
\version	1.74
\date		14.07.2015
\internal
- TH: neues Feld zartikel.verbundsperre
\endinternal

________________________________________________________________________________________
\version	1.73
\date		29.06.2015
\internal
- TH: Stingray / ObjectiveGrid removed
\endinternal

________________________________________________________________________________________
\version	1.72
\date		25.02.2015
\internal
- TH: Abfangen "blanks" in csv- Dateinamen
\endinternal

*/

// 1.01 : 02.09.2002 Autidem -> Neue Artikel 
// 1.02 : 05.09.2002 Autidem -> Uebernahme Dateiname bei GenAutidem, Eieruhr bei GenAutidem 
// 1.03 : 30.10.2002 IFA-Festbetrags-Lieferung generieren ( GenFestbView )
// 1.04 : 05.11.2002 Rechtscreibefehler, OK-Meldung in GenFestbView
// 1.05 : 19.02.2004 Umstellung auf var. DB 
// 1.06 : 21.04.2004 Umstellung auf eshu, neues Logo
// 1.07 : 01.07.2004 Anmeldeprozedur aendern 
// 1.08 : 04.07.2005 TH: variable Updates aus EXCEL-Datei 
// 1.09 : 08.02.2006 TH: neues Feld zartikel.nahrungstest für Updates aus EXCEL-Datei 
// 1.10 : 10.03.2006 TH: Updates aus EXCEL-Datei auch für zartwg + Vorbereitungen für zartpreis
// 1.11 : 01.09.2006 TH: Art 'A' für zartwg
// 1.12 : 18.10.2006 TH: pps1chr --> pps1hr (DB-Zusammenlegung für Kroatien)
// 1.13 : 08.01.2007 TH: neues Feld zartikel.preissenkung für Updates aus EXCEL-Datei + 
//						 vollständige Verarbeitung für zartpreis
// 1.14 : 01.02.2007 TH: pps1ca -> pps1au + zartpreis noch nicht aktiv!
// 1.15 : 05.03.2007 TH: Fehler behoben -> Prüfung / Umwandlung von Datum nur, wenn Mask == Edit
// 1.16 : 11.04.2007 TH: zartpreis aktiviert
// 1.17 : 09.05.2007 TH: gep / aep dürfen nicht auf 0 gesetzt werden
// 1.18 : 06.09.2007 TH: database change pps1cg --> pps1g; pps1cch --> pps1ch
// 1.19 : 25.03.2008 TH: neue Felder pflegbar: zartikel.awl1 + awl_aktiv
// 1.20 : 18.04.2008 TH: Tabelle cdiscount wird versorgt via txt-File mit definiertem, festen Aufbau
// 1.21 : 21.07.2008 TH: Anpassungen für NUMA
// 1.22 : 07.11.2008 TH: neue gültige Werte für cdiscount.discounttype + discountspec (0-7)
// 1.23 : 16.12.2008 TH: Berechtigung für UpdFromExcelView korrigiert
// 1.30 : 30.04.2009 TH: neuer mode 5 zum Laden von cdiscount (dynamisch) 
// 1.31 : 09.06.2009 TH: neuer mode 6 zum Beenden von Rabatten (dynamisches Where- Statement) 
// 1.32 : 29.07.2009 TH: Ersetzen von . durch , bei CDiscount- Double- Werten 
// 1.33 : 18.09.2009 TH: ports for RS + BG; pharmacy group excluded;
// 1.34 : 22.12.2009 TH: stop cdiscount with flexible date
// 1.35 : 23.12.2009 TH: customer no for flexible cdiscount
// 1.36 : 05.02.2010 TH: leere pharmacygroupid in cdiscount nicht erlaubt
// 1.37 : 21.04.2010 TH: Korrektur der Comboboxes Rabattart / Rabattspezifikation zum Laden von CDiscount
// 1.38 : 09.07.2010 TH: neues Feld pflegbar: zartikel.artikel_nr_herst
// 1.39 : 18.08.2010 TH: neuer Port für PWSAT
// 1.40 : 24.08.2010 TH: artve aktiviert
// 1.41 : 06.10.2010 TH: VPE = 0 ist gültig
// 1.42 : 08.04.2011 TH: Versorgung zartpreis.lieferbasispreis
// 1.43 : 17.05.2011 TH: Anpassung Erzeugung FB-Datei an IFA 20174
// 1.44 : 01.06.2011 TH: CR-240 = neues Kriterium "IDF" für CDiscount beenden / "AH-Datum" für Update zartikel
// 1.45 : 28.03.2012 TH: CR-11P271 = 5 neue zartikel- Felder, die geladen werden können (sortiment_1 - sortiment_5)
// 1.46 : 11.05.2012 TH: PZN 8
// 1.47 : 06.06.2012 TH: CR-SA0111
// 1.48 : 24.07.2012 TH: Vorbereitung UnixFoundation
// 1.49 : 09.08.2012 TH: SR-081422 Datum-AH in der Vergangenheit
// 1.50 : 22.10.2012 TH: neuer Mode 8 zum Laden von CDiscGrpMem
// 1.51 : 25.10.2012 TH: Beenden von Monatsrabatten rückwirkend bis zum Monatsletzten des Vormonats
// 1.52 : 21.11.2012 TH: neues, fixes Fileformat (BG) zum Laden von cdiscount
// 1.53 : 30.11.2012 TH: SR-88273 - Eingabe customerno=0 ist nun gültig
// 1.54 : 05.02.2013 TH: mode 9 (zartfrance) + mode 10 (carticlecodes) für FR-Revival 3, zusätzliche Felder für zartikel + zartpreis
// 1.55 : 08.02.2013 TH: BugFix SR-91874 (zdkwgr immer 5-stellig)
// 1.56 : 15.02.2013 TH: 4 neue Felder zum Beenden von cdiscount
// 1.57 : 04.03.2013 TH: IC09 statt IC06 für Generierung Festbetragsdatei
// 1.58 : 19.03.2013 TH: AIX ports
// 1.59 : 02.05.2013 TH: neue Felder / Abläufe für BG
// 1.60 : 06.06.2013 TH: baseqty = 0 erlaubt, wenn base_value > 0 (BG)
// 1.61 : 09.07.2013 TH: discountspec 8 - 11
// 1.62 : 23.07.2013 TH: HNR in zartikel darf nicht 0 sein!
// 1.63 : 18.09.2013 TH: DB_MONEY=. auf AIX (SR-104573)
// 1.64 : 16.01.2014 TH: neue Felder pharmgrpexl_2, pharmgrpexl_3, monthlydiscount
// 1.65 : 08.04.2014 TH: removal of vignette = 2 neue zartpreis- Felder
// 1.66 : 25.07.2014 TH: mode 12 (cgibatchentry)
// 1.67 : 06.08.2014 TH: 3.Saison-Warengruppe (G) = CR-14Z007
// 1.68 : 12.08.2014 TH: ini- file replaced by registry
// 1.69 : 19.08.2014 TH: SetRegistryKey("ZDP") for storing of customized toolbar
// 1.70 : 07.11.2014 TH: SR-14026362 = zusätzliche Felder für CH
// 1.71 : 27.11.2014 TH: SR-14029889 = Unterstützung Codetyp 6 (Intrastat)
// 1.72 : 25.02.2015 TH: Abfangen "blanks" in csv- Dateinamen
// 1.73 : 29.06.2015 TH: Stingray / ObjectiveGrid removed
// 1.74 : 14.07.2015 TH: neues Feld zartikel.verbundsperre
// 1.75 : 20.07.2015 TH: Abfangen "blanks" tatsächlich nur in csv- Dateinamen, nicht im gesamten Pfad
// 1.76 : 22.10.2015 TH: neues Feld zartikel.zentralppelist


/////////////////////////////////////////////////////////////////////////////
// CZdpUtilApp

BEGIN_MESSAGE_MAP(CZdpUtilApp, CWinAppMultiLang)
	//{{AFX_MSG_MAP(CZdpUtilApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TASCHENRECHNER, OnCalculator)
	ON_COMMAND(ID_SERVER, OnServer)
	ON_UPDATE_COMMAND_UI(ID_SERVER, OnUpdateServer)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Dateibasierte Standard-Dokumentbefehle
	ON_COMMAND(ID_FILE_NEW, CWinAppMultiLang::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinAppMultiLang::OnFileOpen)
	// Standard-Druckbefehl "Seite einrichten"
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinAppMultiLang::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilApp Konstruktion

CZdpUtilApp::CZdpUtilApp()
{
	m_Con = NULL;
	m_Branch = NULL;

	m_Server[0].ServerProgram = _T("zdpuiserv" );
	m_Server[0].ServerProgramName = _T("zdpuiserv");
	m_Server[0].DialogServer = _T("");

	m_nActualServer = 0;
	m_strINIFile = "";
	m_bConnected = false;
	m_bUADM = false;
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CZdpUtilApp-Objekt

CZdpUtilApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CConnect Class

class CConnect : public CConSoVa2	// 3
{
public:
	 void DoThingsBeforeCloseDatabase();
};

void CConnect::DoThingsBeforeCloseDatabase()
{
	((CMainFrame*)AfxGetMainWnd())->CleanUp();
}

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilApp Initialisierung

BOOL CZdpUtilApp::InitInstance()
{
	// define the INI File
	char appPath[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, appPath, sizeof(appPath));
	PathRemoveFileSpec(appPath);

	m_strINIFile = CString(appPath);
	m_strINIFile.Append("\\");
	m_strINIFile.Append(UADM_APPLICATION_NAME);
	m_strINIFile.Append(".ini");

	verifyUADM();

//	LoadStdProfileSettings();  // Standard INI-Dateioptionen laden (einschließlich MRU)
	LoadStdProfileSettings(0);	// do not load

	SetRegistryKey("ZDP"); // needed for adaptable toolbar

	// Dokumentvorlagen der Anwendung registrieren. Dokumentvorlagen
	//  dienen als Verbindung zwischen Dokumenten, Rahmenfenstern und Ansichten.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CZdpUtilDoc),
		RUNTIME_CLASS(CMainFrame),       // Haupt-SDI-Rahmenfenster
		RUNTIME_CLASS(CZdpUtilView));
	AddDocTemplate(pDocTemplate);

	// Befehlszeile parsen, um zu prüfen auf Standard-Umgebungsbefehle DDE, Datei offen
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Verteilung der in der Befehlszeile angegebenen Befehle
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Das einzige Fenster ist initialisiert und kann jetzt angezeigt und aktualisiert werden.
//	m_pMainWnd->ShowWindow(SW_SHOW);
//	m_pMainWnd->UpdateWindow();

	//	Maximize Window
	CMainFrame* pMainFrame;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
//	pMainFrame->ShowWindow( SW_SHOWMAXIMIZED );
	pMainFrame->ShowWindow( SW_SHOW );
	pMainFrame->UpdateWindow();

	//  Initialize Views
 	pMainFrame->DefineViews();
	pMainFrame->SetDefaultView( ); // Bild schneller da

	//  Create Formviews
 	pMainFrame->CreateFormViews();

	m_Con = new CConnect();

	// new: use UADM for login instead of hardcoded old way
	if (IsUADM() == true)
	{
		doUADMLogin();
	}
	else
	{
		//	Connect to server and database via old way
	m_Con->InitValues( THIS_PROGRAM_NUMBER, MNR_MAX_MENUS, "phosix" );

	m_Branch = new CGetBranches;

	if ( m_Con->TryDefaultConnect( _T("ZdpUtilPipeSrv"), //name is searched for in wws.ini
			m_Server[m_nActualServer].ServerProgram))
	{
		// load branches
		((CMainFrame*)AfxGetMainWnd())->LoadFilialen( m_Branch );

		// load user spezific customized Toolbar
		((CMainFrame*)AfxGetMainWnd())->LoadToolBarState( GetUserName() );

		pMainFrame->SetDefaultView( );
	}
	}
	return TRUE;
}

int CZdpUtilApp::ExitInstance() 
{
	//  end connection
	delete m_Branch;
	delete m_Con;
	
	return CWinAppMultiLang::ExitInstance();

}	

///////////////////////////////////////////////////////////////////
// Public Functions

//---------------------------------------------------------
BOOL IsCountry(char *Lkz)
{
	CCountryQuery CQ;
	CString Database;
	
	Database = ((CZdpUtilApp*) AfxGetApp())->GetDbaseName();

	return CQ.CQ_IsCountry(Database, Lkz);
}

//---------------------------------------------------------
BOOL IsPrewhole()
{
	CCountryQuery CQ;
	CString Database;
	
	Database = ((CZdpUtilApp*) AfxGetApp())->GetDbaseName();

	return CQ.CQ_IsPrewhole(Database);
}

//---------------------------------------------------------
BOOL IsIvrylab()
{
	CCountryQuery CQ;
	CString Database;
	
	Database = ((CZdpUtilApp*) AfxGetApp())->GetDbaseName();

	return CQ.CQ_IsPrewhole(Database);
}

//---------------------------------------------------------
CString GetCountry( Country_Return_Type crt, CString Database )
{
	CCountryQuery CQ;

	if (crt == KFZ)
		return CQ.CQ_GetCountryKFZ(Database);
	else
		return CQ.CQ_GetCountryISO3166(Database);
}

//---------------------------------------------------------
CString GetSubModule( SubModul_Return_Type srt, CString Database )
{
	CCountryQuery CQ;

	if (srt == Verz)
		return CQ.CQ_GetSubModuleVerz(Database);
	else
		return CQ.CQ_GetSubModuleSuffix(Database);
}

//---------------------------------------------------------
long GetWWSDateiVerz( CString &cDirec, CString &errmld )
{
	long s;
	char log_path[300];

	if ( ( s = UnxGetenv ( "WSS", log_path ) ) != 0 )
	{
		errmld  = "Umgebungsvariable $WSS auf Server unbekannt\n";
		errmld += DynErrmld();
	}
	else
	{
		cDirec  = log_path;

		CString Server;
		Server = ((CZdpUtilApp*) AfxGetApp())->GetServerName();

		cDirec += _T( "/" );
		cDirec += GetCountry( ISO3166, ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() ).MakeLower();
		cDirec += _T( "/cdm" );
		cDirec += _T( "/" );
		cDirec += GetSubModule( Verz, ((CZdpUtilApp*) AfxGetApp())->GetDbaseName() );
	}

	return s;
}

//---------------------------------------------------------
long GetWWSDateiUnterVerz( CString &cDirec, Verzeichnis_Typ vt, CString &errmld )
{
	long s;
	s = GetWWSDateiVerz( cDirec, errmld );

	if ( s != 0 )
		return s;
	
	CString Server;
	Server = ((CZdpUtilApp*) AfxGetApp())->GetServerName();

	switch (vt)
	{
		case bin:			cDirec += "bin/"; break;
		case util:			cDirec += "data/zputil/"; break;
		default:
			break;
	}
	
	return s;
}

//---------------------------------------------------------
INT_PTR	MsgBoxOK(const char * const spMsg, UINT uiType, const char * const spCaption)
{
	return MsgBox1(spMsg, 
		CResString::ex().getStrTblText(IDS_MSG_OK), 
		uiType,
		spCaption);
}

//---------------------------------------------------------
INT_PTR	MsgBoxOK(UINT uiMsg, UINT uiType, UINT uiCaption)
{
	return MsgBox1(uiMsg, 
		IDS_MSG_OK, 
		uiType, 
		uiCaption);
}

//---------------------------------------------------------
INT_PTR	MsgBoxYesNo(const char * const spMsg, UINT uiType, const char * const spCaption)
{
	return MsgBox2(spMsg, 
		CResString::ex().getStrTblText(IDS_MSG_YES), 
		CResString::ex().getStrTblText(IDS_MSG_NO), 
		uiType, 
		spCaption);
}

//---------------------------------------------------------
INT_PTR	MsgBoxYesNo(UINT uiMsg, UINT uiType, UINT uiCaption)
{
	return MsgBox2(uiMsg, 
		IDS_MSG_YES, 
		IDS_MSG_NO, 
		uiType, 
		uiCaption);
}

//---------------------------------------------------------
CString CZdpUtilApp::GetServerProgramName( )
{
	return  m_Server[m_nActualServer].ServerProgramName;
}

//---------------------------------------------------------
void CZdpUtilApp::SetServerProgramName (CString name)
{
	m_Server[m_nActualServer].ServerProgramName = name;
}

//---------------------------------------------------------
CString CZdpUtilApp::GetServerProgram( )
{
	return  m_Server[m_nActualServer].ServerProgram;
}

bool CZdpUtilApp::IsSyncronized()
{
	return m_Con->IsSyncronized();
}


CString CZdpUtilApp::GetServerHandler( )
{
	return m_Con->GetServerHandler();
}

CString CZdpUtilApp::GetServerName( )
{
	return m_Con->GetServerName();
}

CString CZdpUtilApp::GetDbaseName( )
{
	return m_Con->GetDbaseName();
}

CString CZdpUtilApp::GetUserName( )
{
	return m_Con->GetUserName();
}

char* CZdpUtilApp::GetRefToAnwender( )
{
	return m_Con->GetRefToAnwender();
}

bool CZdpUtilApp::IsUADM()
{
	return m_bUADM;
}

bool CZdpUtilApp::IsStandardEngine()
{
	return m_Con->IsStandardEngine();
}

bool CZdpUtilApp::DarfRechtePflegen()
{
	return m_Con->DarfRechtePflegen();
}

bool CZdpUtilApp::DarfSubSuperAnlegen( )
{
	return m_Con->DarfSubSuperAnlegen( );
}

bool CZdpUtilApp::DarfMenuPflegen( int MenuNr )
{
	if (IsUADM() == true)
	{
		return m_Con->DarfMenuPflegen(m_Con->GetUADMRegionNo(), MenuNr);
	}
	// else
	// Zentrale Pflege -> Region REGION_ZDP ( 99 )
	return m_Con->DarfMenuPflegen( REGION_ZDP, MenuNr );
}

bool CZdpUtilApp::DarfMenuAendern( int MenuNr )
{
	if (IsUADM() == true)
	{
		return m_Con->DarfMenuAendern(m_Con->GetUADMRegionNo(), MenuNr);
	}
	// else
	// Zentrale Pflege -> Region REGION_ZDP ( 99 )
	return m_Con->DarfMenuAendern( REGION_ZDP, MenuNr );
}

bool CZdpUtilApp::ReadUserRights( CString& cErrmld )
{
	return m_Con->ReadUserRights( cErrmld );
}

CStringArray* CZdpUtilApp::GetLoginRechte()
{
	return m_Con->GetLoginRechte();
}

CUIntArray* CZdpUtilApp::GetLoginRegion()
{
	return m_Con->GetLoginRegion();	
}

// Branches

CString CZdpUtilApp::GetCurrentBranchName( bool mode )
{
//	return m_Con->GetFilialName();
	return m_Branch->GetCurrentBranchName( mode );
}

void CZdpUtilApp::SetCurrentBranch( int index )
{
	m_Branch->SetCurrentBranch( index );
}

short CZdpUtilApp::GetCurrentBranchNumber( )
{
	return m_Branch->GetCurrentBranchNumber( );
}

bool CZdpUtilApp::IsConnected( )
{
	if ( m_Con == NULL )
		return false;
	else
		return m_Con->IsConnected();
}

////////////////////////////////////////////////////
// View wechseln

void CZdpUtilApp::ChangeToView( int nViewNr )
{
	((CMainFrame*)AfxGetMainWnd())->ChangeToView( nViewNr );
}

void CZdpUtilApp::ChangeBackToView( int nViewNr ) 
{
	((CMainFrame*)AfxGetMainWnd())->ChangeBackToView( nViewNr ) ;
}

void CZdpUtilApp::ChangeBackToView( CView *pView )
{
	((CMainFrame*)AfxGetMainWnd())->ChangeBackToView( pView ) ;
}


////////////////////////////////////////////////////
// Menu Steuerung


void CZdpUtilApp::EnableTbComboBranches( BOOL bEnable )
{
	((CMainFrame*)AfxGetMainWnd())->EnableTbComboBranches( bEnable );
}


void CZdpUtilApp::SetMenuOnOff( int nBearbeiten, int nSave, int nDelete, 
			  			    int nSearch, int nNext, int nPrev ) 
{
	((CMainFrame*)AfxGetMainWnd())->
		SetMenuOnOff( nBearbeiten, nSave, nDelete, nSearch, nNext, nPrev );
}

void CZdpUtilApp::SaveMenuState( bool& bBearbeiten, bool& bSave, bool& bDelete, 
			  				 bool& bSearch, bool& bNext, bool& bPrev ) 
{
	((CMainFrame*)AfxGetMainWnd())->
		SaveMenuState( bBearbeiten, bSave, bDelete, bSearch, bNext, bPrev );
}

void CZdpUtilApp::SetMenuState( bool bBearbeiten, bool bSave, bool bDelete, 
			  				bool bSearch, bool bNext, bool bPrev ) 
{
	((CMainFrame*)AfxGetMainWnd())->
		SetMenuState( bBearbeiten, bSave, bDelete, bSearch, bNext, bPrev );
}

void CZdpUtilApp::PushMenuState(  ) 
{	
	((CMainFrame*)AfxGetMainWnd())->PushMenuState(  );
}

void CZdpUtilApp::PopMenuState(  ) 
{	
	((CMainFrame*)AfxGetMainWnd())->PopMenuState(  );
}


void CZdpUtilApp::SetDruckState( bool bDruck )
{
	((CMainFrame*)AfxGetMainWnd())->SetDruckState( bDruck );
}

////////////////////////////////////////////////////
// Central Questions


bool CZdpUtilApp::YouWantToDo( CString Frage )
{
	if ( ((CMainFrame*)AfxGetMainWnd())->IsAutoFrage() ) return true; 
	return AfxMessageBox( Frage, MB_YESNO | MB_ICONQUESTION ) == IDYES;
}	

bool CZdpUtilApp::YouWantToStoreRecord( )
{
	if ( ((CMainFrame*)AfxGetMainWnd())->IsAutoFrage() ) return true; 
	return AfxMessageBox( "Satz speichern", MB_YESNO | MB_ICONQUESTION ) == IDYES;
}

bool CZdpUtilApp::YouWantToDeleteRecord( )
{
	if ( ((CMainFrame*)AfxGetMainWnd())->IsAutoFrage() ) return true; 
	return AfxMessageBox( "Satz loeschen", MB_YESNO | MB_ICONQUESTION ) == IDYES;
}

bool CZdpUtilApp::IsSafeToExit( )
{
	if ( ((CMainFrame*)AfxGetMainWnd())->IsSafeToExit( ) )
	{
		bool bFrage;
		if ( ((CMainFrame*)AfxGetMainWnd())->IsAutoFrage() ) 
			bFrage = true; 	
		else
			bFrage = AfxMessageBox( "Anwendung beenden",
									MB_YESNO | MB_ICONQUESTION ) == IDYES;
		if ( bFrage && IsConnected() )
			m_Con->DoThingsBeforeCloseDatabase();
		return bFrage;

	}
	else
	{
		AfxMessageBox( "Bitte zuerst Bearbeitung beenden" );
		return false;
	}
}

////////////////////////////////////////////////////
// Wait Messages	

void CZdpUtilApp::BeginWaitAction( )
{
	BeginWaitCursor();
	((CMainFrame*)AfxGetMainWnd())->GetStatusBar()->PleaseWait();
}

void CZdpUtilApp::EndWaitAction( )
{
	((CMainFrame*)AfxGetMainWnd())->GetStatusBar()->EndPleaseWait();
	EndWaitCursor();
}

////////////////////////////////////////////////////
// Other Messages

void CZdpUtilApp::MeldRecordWasDeleted( ) 
{
	AfxMessageBox( "Satz wurde zwischenzeitlich gelöscht" );
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialog für Info über Anwendung

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogdaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	ChBmpButton	m_cBmpB1;
	CStatic	m_cBmpText;
	//}}AFX_DATA

	// Überladungen für virtuelle Funktionen, die vom Anwendungs-Assistenten erzeugt wurden
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
private:
	void BmToggle( );
	bool b_toggle;

protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnPaint();
	afx_msg void OnAboutPb();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_ABOUT_PB, m_cBmpB1);
	DDX_Control(pDX, IDC_ABOUT_KNOEDEL, m_cBmpText);
	//}}AFX_DATA_MAP
}

void CAboutDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
	CString cStr;
	char info[15];
	memcpy(info, &SCCSID[19], 14);
	info[14] = '\0';
	cStr = "ZDPUtil Version ";   cStr += info;
	((CStatic*)GetDlgItem(IDC_ABOUT_VERSION))->SetWindowText(cStr);
	memcpy(info, &SCCSID[44], 11);
	info[10] = '\0';
	cStr = "Last Update:  ";   cStr += info;
	((CStatic*)GetDlgItem(IDC_ABOUT_DATE))->SetWindowText(cStr);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ABOUT_PB, OnAboutPb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CAboutDlg::BmToggle( ) 
{
	if ( b_toggle )
	{
    	m_cBmpB1.InitBitmap(IDB_BM_KNOEDEL );	
		m_cBmpText.SetWindowText( "Knödel" );
	}
	else
	{
		m_cBmpB1.InitBitmap(IDB_BM_VOGESE );
		m_cBmpText.SetWindowText( "Vogese" );		
	}
	b_toggle = !b_toggle;
}

void CAboutDlg::OnAboutPb() 
{
	// TODO: Add your control notification handler code here
	if ( b_toggle )
		CDialog::OnCancel();	
	else
		BmToggle( ) ;		
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	b_toggle = true;
	BmToggle( ) ;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// App command to run the dialog
void CZdpUtilApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CZdpUtilApp commands

/////////////////////////////////////////////////////////////////////////////
// Calculator

void CZdpUtilApp::OnCalculator() 
{
	// TODO: Add your command handler code here

	HWND hCalcWnd = ::FindWindow("SciCalc", NULL );
	if ( hCalcWnd != NULL ) 
	{
		::BringWindowToTop(hCalcWnd);			 // in Vordergrund holen
		::ShowWindow( hCalcWnd, SW_SHOWNORMAL ); // restourieren, falls minimiert
	}
	else if( WinExec("CALC.EXE",SW_SHOW) < 32 )
		AfxMessageBox("CALC.EXE not found");	
}

///////////////////////////////////////////////////////////////////////////
// Server

void CZdpUtilApp::OnServer()
{
	if (IsUADM() == true)
	{
		doUADMLogin();
	}
	else
	{
		int s = m_Con->TryDialogConnect( m_Server[m_nActualServer].ServerProgram );
	if ( s == 0 )
	{
		// load branches
		((CMainFrame*)AfxGetMainWnd())->LoadFilialen( m_Branch );

		// load user spezific customized Toolbar
		((CMainFrame*)AfxGetMainWnd())->LoadToolBarState( GetUserName() );
	}
	((CMainFrame*)AfxGetMainWnd())->SetDefaultView( ); // ?????? hier ???
	}
}

void CZdpUtilApp::OnUpdateServer(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( ((CMainFrame*)AfxGetMainWnd())->IsDefaultView( ) );
}

bool CZdpUtilApp::verifyUADM()
{
	// indicator for UADM is the new ZDPUTIL.ini file
	FILE* pFile = NULL;
	if (m_strINIFile.IsEmpty() == false)
	{
		fopen_s(&pFile, m_strINIFile, "r"); // just to check if the file exists
		if (pFile != NULL)
		{
			// exists, so use the new UADM
			fclose(pFile);
			m_bUADM = true;
			return true;
		}
	}
	return false;
}

bool CZdpUtilApp::doUADMLogin()
{
	// the m_Con object is the real connection to the backend
	if (m_bConnected == true)
	{
		// reset the old connection
		m_Con->DoThingsBeforeCloseDatabase();
		m_Con->CloseConnection();
		m_bConnected = false;
		((CMainFrame*)AfxGetMainWnd())->LoadToolBarState(GetUserName());
		SetServerProgramName(m_Con->GetServerProgram());
		((CMainFrame*)AfxGetMainWnd())->SetConnectinfoToView();
		((CMainFrame*)AfxGetMainWnd())->SetDefaultView();
	}

	CString regKey("Software");
	regKey.Append("\\");
	regKey.Append("ZDP"); // instead of UADM_APPLICATION_NAME, get the registry from ZDP

	// the login manager uses the UADM server and db, which is different to the application backend server
	UADM::CUADMLoginManager loginMgr;
	if (loginMgr.initialize(m_strINIFile.GetString(), regKey.GetString(), UADM_APPLICATION_NAME, CDM_VERSION " - " ZDPUTIL_VERSION) == true)
	{
		m_bConnected = false;
		while (m_bConnected == false)
		{
			// new login via UADM library
			if (loginMgr.loginWithDialog("", this->m_pMainWnd->m_hWnd) == false)
			{
				m_bConnected = false;
				return false;
			}
			BeginWaitCursor();
			loginMgr.getUserID();
			CString strUsername = loginMgr.getUsername().c_str();
			loginMgr.getLanguage().c_str();
			CString strEnv = loginMgr.getEnvironment().c_str();
			CString strServerName = CString(loginMgr.getServername().c_str());
			CString strDbaseName = CString(loginMgr.getDatabase().c_str());
			CString strService = CString(loginMgr.getServiceName().c_str());
			CString strCountry = loginMgr.getCountry().c_str();
			CString strRegionBranch = loginMgr.getRegionBranchNo().c_str();
			int intPortNo = loginMgr.getPortNoVal();
			m_Con->Initialize(MNR_MAX_MENUS, strUsername);
			// start the connection to the target server and DB
			m_bConnected = m_Con->OpenConnection(strServerName, strService, strDbaseName, intPortNo, loginMgr.getRegionBranchNoVal());
			if (m_bConnected == false)
			{
				m_Con->CloseConnection();

				CString strText = "";
#ifdef _DEBUG
				// for developers
				strText.Format("Cannot connect ZDPUtil Backend Voodoo service %s on server %s with port %i", m_Con->GetServerProgram(), strServerName, intPortNo);
#else
				// for business users
				strText.Format("Cannot connect ZDPUtil Backend service on %s environment for %s with region / branch %s", strEnv, strCountry, strRegionBranch);
#endif
				MsgBoxOK(strText);
			}
		}
		// handover permissions from uadm login manager to old zdputil connection manager
		// --------------------------------------------------
		// read userrights from UADM
		// --------------------------------------------------
		CString rightWrite = UADM_RIGHT_WRITE;
		CString rightRead = UADM_RIGHT_READ;
		CString rights = "";
		// menus starts with 1, but will be indexed with 0 in the rights string
		for (int i = 1; i <= MNR_MAX_MENUS; i++)
		{
			if (loginMgr.verifyPermission(i, rightWrite.GetString()) == true)
			{
				rights += RIGHT_WRITE;
			}
			else if (loginMgr.verifyPermission(i, rightRead.GetString()) == true)
			{
				rights += RIGHT_READ;
			}
			else
			{
				rights += RIGHT_NONE;
			}
		}
		m_Con->SetLoginRechte(rights);

		// check and set language
		//CheckLanguage();

		// load user spezific customized Toolbar
		((CMainFrame*)AfxGetMainWnd())->LoadToolBarState(GetUserName());
		SetServerProgramName(m_Con->GetServerProgram());
		((CMainFrame*)AfxGetMainWnd())->SetConnectinfoToView();
		((CMainFrame*)AfxGetMainWnd())->SetDefaultView();
		return true;
	}
	return false;
}