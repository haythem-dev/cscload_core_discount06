#ifndef _ALLGFKTN_H
#define _ALLGFKTN_H

#include "texte.h"
#include <ppgeneric.h>

extern "C"  //Definition von C-Funktionen
{
#include <bufkon.h>  // Programme zur Netz-Konvertierung
#include "allg.h"  // Allgemeine Funktionen
}

#include <sockclient.h>

#define ALGF_FORM_DATUM_MMJJ    1 //oder MMJJJJ
#define ALGF_FORM_DATUM_TTMM    2
#define ALGF_FORM_DATUM_TTMMJJ  3 //oder TTMMJJJJ

void  FehlerBehandlung(int rc, const char* error_msg);

int   AllgLaengeKontr(CEdit* edit, int len);
int   AllgLaengeKontr(CEdit* edit, int len, int modus);
int   AllgLaengeKontr(CEdit* edit, int len, int maxlen, int modus);
int   AllgLaengeKontrWnd(CComboBox* cbx, int len);
int   AllgLaengeKontrWnd(CComboBox* cbx, int len, int modus);
int   AllgWertKontr(CEdit* edit, __int64 max);
int   AllgWertKontr(CEdit* edit, __int64 min, __int64 max);
int   AllgCStrCharToChar(CString& str, char FromChar, char ToChar);
int   AllgWedDezimalKontr(CEdit* edit, int GesammtStellen, int NachkommaStellen);
int   AllgCharInDigit(CEdit* edit);
BOOL  AllgCheckPrintableSign(CEdit* edit);
BOOL  AllgCheckPrintableSignWnd(CComboBox* cbx);

void  AllgTourAusgKonv(CString& AusgTour, const char* Tour);
void  AllgTourKonvFromAusg(CString& Tour, const char* AusgTour);
void  AllgTourGetBhf(CString& Bhf, const char* Tour);
void  AllgTourEingKonv(CString& Tour, CString EingTour);

int   AllgZeitKontr(CEdit* edit);
int   AllgDatumKontr(CEdit* edit, int Format = ALGF_FORM_DATUM_TTMMJJ);
long  AllgZeitEingKonv(CString EingZeit);
long  AllgDatumEingKonv(CString EingDatum,int Format = ALGF_FORM_DATUM_TTMMJJ);
CTime CTimeFromTimeLong(int nYear, int nMonth, int nDay, long lTime);
CTime CTimeFromDateLong(int nHour, int nMin, int nSec, long lDate, int nDST = -1);
CTime CTimeFromDateLongAndHour(int nHour, long lDate);
CTime CTimeFromDateLongMinTime(long lDate);
CTime CTimeFromDateLongMaxTime(long lDate);
CTime CTimeFromDateTimeLong(long lDate, long lTime);
CTime CTimeFromDateTimeLongNoSeconds(long lDate, long lTime);
long  GetTotalSeconds(CTime& time);
CTimeSpan CTimeSpanFromTimeLong(long lTime);
CString DDMMYYYYStringFromDateLong(long lDate);
CString DDMMYYYYStringNoDotsFromDateLong(long lDate);
CString HHmmStringFromShortTimeLong(long lTime);
CString HHmmStringFromTimeLong(long lTime);
CString HHmmSSStringFromTimeLong(long lTime);
CTime GetEastern(long date);

// Vom User eingestellte Spaltenbreiten in/aus Win-DB
void AllgSetColumnWidthUser(CListCtrl& lc, char* name, char* keypath, int anz);
void AllgWriteColumnWidthUser(CListCtrl& lc, char* name, char* keypath, int anz);


#ifndef WM_HOOKFKT
#define WM_HOOKFKT ( WM_USER + 100 )
#endif

#define WM_UPDATE_TOOLBAR ( WM_USER + 101 )

#endif
