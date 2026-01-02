#ifndef KSCCLIENT_VERSION_H
#define KSCCLIENT_VERSION_H

#define KSCCLIENT_VERSION "1.2.3.0"

/*!

________________________________________________________________________________________
\date 2020-03-16
\version 1.2.3.0
\internal
- (SB) Include pathes updated
\endinternal
________________________________________________________________________________________
\date 2019-11-05
\version 1.2.1.0
\internal
- (SB) Updated to 64-Bit
\endinternal
________________________________________________________________________________________
\date 2019-08-07
\version 1.2.0.1
\internal
- (SB) Callback methods removed as callback does now only use csc service.
\endinternal
________________________________________________________________________________________
\date 2018-06-06
\version 1.1.11.0
\internal
- (SB) New version of csc core applications
\endinternal
________________________________________________________________________________________
\date 2017-09-01
\version 1.1.10.0
\internal
- (SB) New-callback methods
- (RI) New method: SetNoRouting (switch off customerrouting for this order)
\endinternal
________________________________________________________________________________________
\date 2017-05-29
\version 1.1.9.0
\internal
- (DK) Update auf neueste core applications
\endinternal
________________________________________________________________________________________
\date 2016-03-17
\version 1.1.7.0
\internal
- (FN) Neue Felder in struct für
- (FN) SA0138 AT Ermittlung XML-Rückmeldungen
\endinternal
________________________________________________________________________________________
\date 2016-02-26
\version 1.1.6.0
\internal
- (FN) fixed CopyInfo()	4 newest fields were missing.
- (FN) interface changed to const parameters where appropriate.
\endinternal
________________________________________________________________________________________
\date 2016-02-25
\version 1.1.5.0
\internal
- (BG) TourManager: neue Methode SetTourAndDeliveryDate
- (MZ) Deutschlandbesorger - KundenDispo:
  - added AddDispoItem()-Method used by sendOrder.cpp in kd2ropos (batch) 
\endinternal
\~german
  - Neue Methode fuer KundenDispo-Feature "Deutschlandbesorger"
  - Neue Methode um Tour und Datum Auslieferung im Auftrag zu setzen
\~english
  - Added new method for CustomerDispo-Feature "Deutschlandbesorger"
  - Added new method to change Tour and DeliveryDate
\~
________________________________________________________________________________________
\date 05.11.2015
\version 1.1.4.0
\internal
- (SH) callksc.c: Neue Funktion AddOrderItemCodeRefFreeLineRef für CR-15A018
\endinternal
________________________________________________________________________________________
\date 15.09.2015
\version 1.1.3.0
\internal
- (SH) callksc.c: Neue Funktion GetManufacturerForArticle für CR-15A018
\endinternal
________________________________________________________________________________________
\date 06.08.2015
\version 1.1.2.0
\internal
- (RI) callksc.c: Neue Funktion SetOrderRelationNo RS-DGEP-Projekt
\endinternal
*/


/*
Here is the template for a version description.
Copy this section to the top of the version history to create a new version history entry.

________________________________________________________________________________________
\date 2020-02-11
\version 01.02.02.00
\internal
\endinternal
\~german
\~english
\~

 */

#endif
