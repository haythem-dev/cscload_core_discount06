#ifndef VERSION_H
#define VERSION_H

//#define AE_APP_FILE_VERSION 8,33,32,0
//#define AE_APP_VERSION "8.33.32"

/*******************************************************************************************/
/*!
\mainpage notitle

\~german
Hier werden Sie in Zukunft die Versionhistorie der AE finden.
\~english
In the future, you will find the change history of the order entry application below.
\~
________________________________________________________________________________________
\date XX.XX.XXXX
\version 8.33.32.0
\internal
- (RI) CR 16D020: Buttons in F11 eingebaut
- (RI) About-Dialog: Buttons für Internet-Anzeige Versions-Historie und Dokumentation eingebaut
- (RI) SR-16037362: Korrektur bei Aufbereitung Fehlermeldung in Sammelauftrag, dass Auftragsart für Kunde nicht erlaubt ist.
- (RI) dkndinf.cpp: Touren Anzeige in F12 erweitert.
- (RI) aevfiew.cpp: Einblenden des Lieferzeitpunkt bei abweichender Tour
- (SB) RR-Buttons: Erweiterung für Web-Anwendung eingebaut
\endinternal
\~german
\~english
\~
________________________________________________________________________________________
\date 27.04.2016
\version 8.33.31.0
\internal
- (RI) CREMA-Abschluß für 2nd Level Support analog Cancel: Korrektur auf richtiges Recht
\endinternal
\~german
\~english
\~
________________________________________________________________________________________
\date 01.04.2016
\version 8.33.30.0
\internal
- (RI) DBePosBearb.cpp Keine Dispo für gesperrte Artikel in DE
- (RI) SR-16027081: Prüfung auf bereits verarbeiteten Verbund auch für N-Level-Verbund eingefügt
- (TH) CREMA- Texte für D angepasst (Auftragsabschluss und VA08)
- (RI) CREMA-Abschluß für 2nd Level Support analog Cancel
- (RI) dparauftrendzeit.cpp Neue Endezeit für Verbundumbuchung
- (RI) aefview.cpp Verbund möglich über ibtbranches, wenn Tourmanager an ist
\endinternal
\~german
- (RI) Keine Dispo für gesperrte Artikel in DE
- (TH) CREMA- Texte für D angepasst (Auftragsabschluss und VA08)
- (RI) CREMA-Abschluß für 2nd Level Support analog Cancel
- (RI) Neue Endezeit für Verbundumbuchung
\~english
\~
________________________________________________________________________________________
\date 22.03.2016
\version 8.33.29.0
\internal
- (RI) 16D015 Eingabe des Kritiklevels und Anzeigen der letzten 3 kritischen Rückrufe 
- (RI) dkndinf.cpp Anzeige Verbundtouren auch bei Wochentouren 
- (RI) dkndinf.cpp Nicht mehr Anzeigen Reiter Umsatz und Zahlungsbedingungen bei nicht vorhandenem Recht Kundeninfo
- (RI) daufinf.cpp Bei MSV3-Aufträgen und dazugehörigem Recht) Msgbox einblenden, ob Auftrag nur zur Ansicht eröffnet werden soll
\endinternal
\~german
- 16D015 Eingabe des Kritiklevels über Button (Return wird nicht mehr zur Eingabebestätigung akzeprtiert).
- 16D015 Anzeigen der letzten 3 kritischen Rückrufe (falls vorhanden) im offenen Auftrag.
- Crema Reiter Umsatz und Zahlungsbedingungen werden bei nicht vorhandenem Recht Kundeninfo nicht mehr in F12 angezeigt.
- Bei MSV3-Aufträgen und dazugehörigem Recht) Msgbox einblenden, ob Auftrag nur zur Ansicht eröffnet werden soll.
\~english
\~
________________________________________________________________________________________
\date 11.03.2016
\version 8.33.28.0
\internal
- (RI) aefview.cpp Nachlesen paraauftragbearb der Kundenfiliale für VB möglich Anzeige
- (RI) dinfanzauft.cpp Nachlesen paraauftragbearb der Kundenfiliale für VB möglich Anzeige
- (RI) doffauft.cpp Berücksichtigen Userrechte für MSV3 bei Anzeige zurückgestellter Aufträge
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 13.01.2016
\version 8.33.27.0
\internal
- (RI) drechteaa.cpp Neues Recht: Stornieren Crema Aufträge
- (RI) dinfanzauft.cpp Neuer Button: Crema-Auftrag stornieren (wenn User das Recht hat)
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 16.12.2015
\version 8.33.26.0
\internal
- (RI) DStellerAnz.cpp Korrektur I-15032149# AE Problem Relvar
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 11.12.2015
\version 8.33.25.0
\internal
- (RI) Schalter für Abschaltung Crema eingebaut
- (RI) DParAuftrendzeit.cpp Pflege für automatischen Cancel von Crema-Aufträgen
- (RI) DParAufBearb.cpp Pflege für Zeitangabe (in Stunden) für automatischen Cancel von Crema-Aufträgen
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 08.12.2015
\version 8.33.24.0
\internal
- (RI) CR 15A032 Für Kundengruppe 4 keine Kettentender
- (RI) CR 15A033 only active tenders with free quantities visible in ordering
- (RI) CR 15A056 We should be able to see only the available quantity for the qustomer in the order. 
- (RI) NLevel-Verbund Anzeigen nach Vorgabe angepasst.
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 11.11.2015
\version 8.33.23.0
\internal
- (MZ) Crema One Emailpflege fix für manueller DB - Datenpflege
- (MZ) SR-15052228 Bestellfensterpflegefehler bei Touren > 2459XX
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 05.11.2015
\version 8.33.23.0
\internal
- (RI) procenter.cpp: Anrufprotokoll eingebaut  (CR 15D026)
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 14.10.2015
\version 8.33.22.0
\internal
- (RI) daufend.cpp: Korrektur bei Auftragsbemerkung (nur 1 CString)  (SR-15043633)
- (RI) drechteaa.cpp: Neues Recht für  Pflege Crema EMail-Adressen  (Crema)
- (RI) dartinf.cpp: Artikelanzeige für N-Level-Verbund angepasst
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 25.08.2015
\version 8.33.20.0

\internal
- (RI) daufend.cpp: Korrektur bei Rückführung auf Zahlungsziel  (I-15015541)
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 25.08.2015
\version 8.33.20.0

\internal
- (RI) daufend.cpp: Korrektur bei der initialen Versorgung der Schalter dd und cash 
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 11.06.2015
\version 8.33.18.0

\internal
- (RI) aefview.cpp: Reverse-Substitution eingebaut (CR-14A076)
- (RI) daufend.cpp: Combo Box für Preisvorschlag  (CR-15A024)
- (RI) daufend.cpp: Korrektur bei Rückführung auf Zahlungsziel  (I-15015282)
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 11.06.2015
\version 8.33.17.0

\internal
- (RI) dorderperiod.cpp: Korrektur bei Anzeigen der Constimes (SR-15025172)
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 10.06.2015
\version 8.33.16.0

\internal
- (RI) aefview + daufdef: I-15009638 Initialisierung Variable m_PaymentType vor Komplettinitialisierung Auftrag
- (RI) allg.cpp: Neue Methode AllgAddTimeSpan
- (RI) dorderperiod.cpp: Benutzung der neuen Methode AllgAddTimeSpan zur Errechnung der Consolidationtime
\endinternal
\~german
\~english
\~

________________________________________________________________________________________
\date 02.06.2015
\version 8.33.15.0

\internal
- (RI) dpromobuch: SR-15022532 Cursor springt jetzt wieder in Suchbegriffsfeld
\endinternal
\~german
\~english
- SR-15022532 Cursor moves back to the search field
\~

________________________________________________________________________________________
\date 20.05.2015
\version 8.33.14.0

\internal
- (TH) doffauft.cpp: SR-15020067: Bugfix Anzeige offener Aufträge aus F8, wenn vorher in VA10 (Anzeige offener Aufträge) als Suchkriterium die Sortierung "Auftragsart" gewählt wurde 
- (RI) dquotasum.cpp: SR-15020313: Anzeigen Artikelcodes in Arikelquota info
\endinternal

\~german
- SR-15020067: Bugfix Anzeige offener Aufträge aus F8, wenn vorher in VA10 (Anzeige offener Aufträge) als Suchkriterium die Sortierung "Auftragsart" gewählt wurde 
\~english
\~

________________________________________________________________________________________
\date 12.05.2015
\version 8.33.13.0

\internal
- (TH) doffauft.cpp: I-15007858: Sortierung zurückgestellter Aufträge gefixt
- (TH) doffauft.cpp: Präprozessor "AUFABFR" + unused Code entfernt
\endinternal
\~german
- I-15007858: Sortierung zurückgestellter Aufträge gefixt
\~english
\~

________________________________________________________________________________________
\date 08.05.2015
\version 8.33.12.0

\internal
- (RI) DAufFrText.cpp: Felder bei Freitexteingabe vorbelegen (CR-15D027)
- (RI) Dinfanzauft.cpp: Aufrufen Rückrufe aus F6 (CR-15D028)
- (TH) Dinfanzauft.cpp: Anzeige OrderLabelCount für MSV3-Aufträge (neue aasrv-Fkt: AasrvGetCustOrderType) --> csc_core_apps >= 10.1.20.1; pplib >= 1.1.2.3
- (TH) Daufinf.cpp: Anzeige OrderPeriodId in TableWidget; Suche nach Auftragsart
\endinternal

\~german
- Neuer Dialog Pflege der neuen Verbundfilialtabelle
- in F6 (Anzeige Aufträge VA08): Suche nach Auftragart + neue Spalte Bestellfenster-Id
- in Anzeige Auftrag: neue Information Anz. freie Auftragskennungen für MSV3- Aufträge
\~english
\~

________________________________________________________________________________________
\date 14.04.2015
\version 8.33.11.0

\internal
- (RI) DIbtBranches.cpp: Neue Pflege Verbundfilialen (Tourenmanagement)
\endinternal

\~german
- Neuer Dialog Pflege der neuen Verbundfilialtabelle
\~english
\~

________________________________________________________________________________________
\date 17.03.2015
\version 8.33.10.0

\internal
- (RI) DCallbackUpd.cpp + AeFax.cpp: Neues Faxformat (CR 15D008)
  - (RI) Neue Tabelle regions (KSC-Regionen)
  - (RI) Neue Feld in Filiale (KSC-Region der Filiale)
- (RI) aefview.cpp : Neues Methode ChangeColumnText zum Ändern der Überschrift (I-15004223)
- (RI) DParKaBaKomb.cpp: Erweiterter Dialog um Schalter mit Eilbotenzuschlag (CR 14D097)

\endinternal

\~german
- Erweiterter Dialog Pflege Auftragsart/Kommiart/Buchungsart zur individuellen Einstellung, ob Eilbotenzuschlag fällig wird
- Neues Format beim Faxen aus Rückrufbearbeitung
\~english
\~


________________________________________________________________________________________
\date 24.02.2015
\version 8.33.9.0

\internal
- (RI) DAuftrEreign.cpp: Anzeigen Eventcode in Auftragsereignissen
- (RI) Aeview.cpp: Erlaubnis für User mit Recht 'Nur Infos anzeigen' zum Aufruf des Dialogs 'Positionsänderungen von VSE (SR-15007255)
- (RI) DShowRebates.cpp: Neuer Dialog zur Anzeige der Rabattstaffel (CR 14D068)
\endinternal

\~german
- Neuer Dialog zur Anzeige vorhandener nicht erreichter Rabattstaffeln nach Buchen Artikel
- Neue Spalte Eventcode (Grund der Zurückstellung mit DF) in Anzeige Auftragsereignisse  
\~english
- New dialog to show rebates that are possible but not reached after booking article
- New columne in orderevents to show reason why the order was deffered in DF
\~

________________________________________________________________________________________
\date 03.02.2015
\version 8.33.8.0

\internal
- Einbau Versionshistorie
  - in About Dialog (CAboutDlg in ae.cpp)
  - in Anmelde Dialog (dbenken.cpp)
- DVbBuchen.cpp
  - SR-15004551 bei CO (Cash order) und PO (Proforma order) als Folgeauftragsart NO vorgeben
\endinternal
\~german
\~english
- new order based on closed PO22 order will be NO00
\~

*/


/*
Here is the template for a version description.
Copy this section to the top of the version history to create a new version history entry.

________________________________________________________________________________________
\date XX.XX.XXXX
\version X.X.X.X
\internal
\endinternal
\~german
\~english
\~

*/

#endif
