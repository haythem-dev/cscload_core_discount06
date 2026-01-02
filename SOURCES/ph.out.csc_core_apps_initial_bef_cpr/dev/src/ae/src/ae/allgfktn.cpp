//Allgemeine Funktionen mit Verbindung zur MFC
//

#include "stdafx.h"
#include <ctype.h>
#include <phodate.h>
#include "texte.h"

//Fehlerbehandlungen

void FehlerBehandlung(int rc, const char* error_msg)
{
    CString s;
    static int err = 0;
    if (rc == -1)
    {
        s = CResString::ex().getStrTblText(IDS_TXT_PROGRAMMABBRUCH);
        s += error_msg;
        if (err == 0)
        {
            err = 1;
            AfxMessageBox(s);
            AfxAbort();
        }
    }
    else if (rc < -1)
    {
        s = CResString::ex().getStrTblText(IDS_TXT_WARNUNG_DBLPKT);
        s += error_msg;
        AfxMessageBox(s);
    }
}

int AllgLaengeKontr(CEdit* edit, int len)
{
    return AllgLaengeKontr(edit, len, 0);
}

int AllgLaengeKontr(CEdit* edit, int len, int modus)
{
    return AllgLaengeKontr(edit, len, 240, modus);
}

int AllgLaengeKontr(CEdit* edit, int len, int maxlen, int modus)
{
    CString CBuf, CStr;
    bool bAusgabe = false;    //String muss nicht neu ausgegeben werden
    int selp;

    if (len > maxlen || len < 1)
    {
        char str[81];
        sprintf(str, "%s AllgLaengeKontr %d", CResString::ex().getStrTblText(IDS_TXT_FEHLER_DBLPKT).GetString(), len);
        AfxMessageBox(str);
        return -1;
    }
    selp = len;
    edit->GetWindowText(CBuf);

    if (modus == 0)
    {
        for (int i = 0; i < CBuf.GetLength(); i++) //Umwandlug Umlaute
        {
            if      (CBuf.GetAt(i) == 'Ä') CStr += "AE", bAusgabe = true, selp = i + 2;
            else if (CBuf.GetAt(i) == 'Ü') CStr += "UE", bAusgabe = true, selp = i + 2;
            else if (CBuf.GetAt(i) == 'Ö') CStr += "OE", bAusgabe = true, selp = i + 2;
            else if (CBuf.GetAt(i) == 'ß') CStr += "ss", bAusgabe = true, selp = i + 2;
            else if (CBuf.GetAt(i) == 'ä') CStr += "ae", bAusgabe = true, selp = i + 2;
            else if (CBuf.GetAt(i) == 'ü') CStr += "ue", bAusgabe = true, selp = i + 2;
            else if (CBuf.GetAt(i) == 'ö') CStr += "oe", bAusgabe = true, selp = i + 2;
            else                           CStr += CBuf.GetAt(i);
        }
    }

    if (CStr.GetLength() > len)
    {
        AfxMessageBox(CResString::ex().getStrTblText(IDS_TXT_MAX_ANZ_ZEICHEN));
        char* buf = new char[maxlen + 1];
        AllgStrCopy(buf, CStr, len);
        buf[len] = '\0';
        CStr = buf;
        delete[] buf;
        bAusgabe = true;
    }

    if (bAusgabe)
    {
        edit->SetWindowText(CStr);
        edit->SetSel(selp, selp, FALSE); //Selektion aufheben
        return -1;
    }

    return 0;
}


int AllgWertKontr(CEdit* edit, __int64 max)
{
    char buf[22], error_msg[81];
    long b;
    edit->GetWindowText(buf, 20);
    if (buf[0] == '\0')
        return 0;
    if (AllgReadLong(buf, &b, 0L, max, error_msg) < 0)
    {
        FehlerBehandlung(-2, error_msg);
        edit->SetWindowText("");
        edit->SetFocus();;
        return -1;
    }
    return 0;
}

int AllgWertKontr(CEdit* edit, __int64 min, __int64 max)
{
    char buf[22], error_msg[81];
    long b;
    edit->GetWindowText(buf, 20);
    if (buf[0] == '\0')
        return 0;
    if (AllgReadLong(buf, &b, min, max, error_msg) < 0)
    {
        FehlerBehandlung(-2, error_msg);
        edit->SetWindowText("");
        edit->SetFocus();;
        return -1;
    }
    return 0;
}

int AllgCStrCharToChar(CString& str, char FromChar, char ToChar)
{
    for (int i = 0;i < str.GetLength();i++)
    {
        if (str[i] == FromChar) str.SetAt(i, ToChar);
    }
    return 0;
}

int AllgWedDezimalKontr(CEdit* edit, int GesammtStellen, int NachkommaStellen)
{
    int i;
    int komma = 0;
    int vk = 1;
    int nk = 1;
    int error = 0;
    int VorkommaStellen;
    char error_msg[80 + 1];
    char buf[81 + 1];

    VorkommaStellen = GesammtStellen - NachkommaStellen;
    edit->GetWindowText(buf, 81);
    if (buf[0] == '\0')
    {
        return 0;
    }
    buf[81] = '\0';
    if (VorkommaStellen + NachkommaStellen + 1 > 80)      /* Stellen maximal */
    {
        error = 1;
    }
    for (i = 0; (buf[i] != '\0') && (error == 0); i++)
    {
        if (buf[i] != ' ')
        {
            if ((buf[i] == ',') || (buf[i] == '.'))
            {
                if (komma++ > 0)                            /* nur 1 Komma erlaubt   */
                {
                    error = 1;
                }
            }
            else
            {
                if ((buf[i] >= '0') && (buf[i] <= '9'))
                {
                    if (komma == 0)
                    {
                        if (vk++ > VorkommaStellen)         /* Vorkommastellen */
                        {
                            error = 1;
                        }
                    }
                    else
                    {
                        if (nk++ > NachkommaStellen)        /* Nachkommastellen */
                        {
                            error = 1;
                        }
                    }
                }
                else
                {
                    error = 1;
                }                                /* Ziffern */
            }
        }
    }
    if (error == 0)
    {
        return 0;
    }
    else
    {
        sprintf(error_msg, CResString::ex().getStrTblText(IDS_TXT_MAX_VOR_NACH_KOMMA), VorkommaStellen, NachkommaStellen);
        FehlerBehandlung(-2, error_msg);
        edit->SetWindowText("");
        edit->SetFocus();
        return -1;
    }
}

int AllgCharInDigit(CEdit* edit)
{
    char buf[81 + 1];
    edit->GetWindowText(buf, 81);
    if (buf[0] == '\0')
        return 0;
    buf[81] = '\0';
    int len = strlen(buf);
    for (int i = 0; i < len; i++)
    {
        if (!isdigit((int)buf[i]))
        {
            FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_NUR_ZIFFERN_ERL).GetString());
            buf[i] = '\0';
            edit->SetWindowText(buf);
            edit->SetFocus();
            edit->SetSel(-1, 0, FALSE); //Selektion aufheben
            return -1;
        }
    }
    return 0;
}

void AllgTourAusgKonv(CString& AusgTour, const char* Tour)
{  //Zusammenspiel mit AllgTourKonvFromAusg beachten
    if (strlen(Tour) != 6) //Format fehlerhaft
    {
        AusgTour = Tour;
        return;
    }
    AusgTour.Format("%2.2s:%2.2s/%2.2s", Tour, Tour + 2, Tour + 4);
}

void AllgTourKonvFromAusg(CString& Tour, const char* AusgTour)
{  //Zusammenspiel mit AllgTourAusgKonv beachten
    if (strlen(AusgTour) != 8) //Format fehlerhaft
    {
        Tour = AusgTour;
        return;
    }
    Tour.Format("%2.2s%2.2s%2.2s", AusgTour, AusgTour + 3, AusgTour + 6);
}

void AllgTourGetBhf(CString& Bhf, const char* Tour)
{
    if (strlen(Tour) != 6) //Format fehlerhaft
    {
        Bhf = " ";
        return;
    }
    Bhf.Format("%2.2s", Tour + 4);
}

void AllgTourEingKonv(CString& Tour, CString EingTour)
{
    long tour = atol(EingTour);
    Tour.Format("%04d%02d", tour % 10000, tour / 10000);
}

int AllgZeitKontr(CEdit* edit)
{
    char buf[22], error_msg[81];
    long b;
    int x, y;
    CString CBuf;
    edit->GetWindowText(CBuf);
    if (CBuf.IsEmpty()) return 0;
    for (x = 0, y = 0; x < CBuf.GetLength(); x++)
    {
        if (CBuf.GetAt(x) >= '0' && CBuf.GetAt(x) <= '9')
        {
            buf[y] = CBuf.GetAt(x);
            y++;
            buf[y] = '\0';
        }
        else if (CBuf.GetAt(x) != ':' && CBuf.GetAt(x) != ' ')
        {
            FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_NUR_ZIFFERN_ERL).GetString());
            edit->SetFocus();
            return -1;
        }
    }
    if (buf[0] == '\0')
        return 0;
    if (AllgReadLong(buf, &b, 0L, 2359, error_msg) < 0)
    {
        FehlerBehandlung(-2, error_msg);
        edit->SetWindowText("");
        edit->SetFocus();
        return -1;
    }
    return 0;
}

int AllgDatumKontr(CEdit* edit, int Format)
{
    char buf[22];
    char test[5];
    long b;
    int x, y;
    int len;
    CString CBuf;
    edit->GetWindowText(CBuf);
    if (CBuf.IsEmpty()) return 0;
    for (x = 0, y = 0, buf[0] = '\0'; x < CBuf.GetLength(); x++)
    {
        if (CBuf.GetAt(x) >= '0' && CBuf.GetAt(x) <= '9')
        {
          buf[y] = CBuf.GetAt(x);
          y++;
          buf[y] = '\0';
        }
        else if (CBuf.GetAt(x) != '.' && CBuf.GetAt(x) != ' ')
        {
            FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_NUR_ZIFFERN_ERL).GetString());
            edit->SetFocus();
            return -1;
        }
    }
    if (buf[0] == '\0') return 0;
    len = strlen(buf);
    if (len >= 2)
    {
        sprintf(test, "%2.2s", buf);
        b = atol(test);
        len = len - 2;
    }
    else
    {
        if (Format == ALGF_FORM_DATUM_MMJJ)
        {
            if (buf[0] > '1')
            {
                FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
                edit->SetFocus();
                return -1;
            }
        }
        else
        {
            if (buf[0] > '3')
            {
                FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
                edit->SetFocus();
                return -1;
            }
        }
        return 0;
    }
    if (Format == ALGF_FORM_DATUM_MMJJ)
    {
        if (b > 12)
        {
            FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
            edit->SetFocus();
            return -1;
        }
    }
    else
    {
        if (b > 31)
        {
            FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
            edit->SetFocus();
            return -1;
        }
    }
    if (len == 0) return 0;
    if (len >= 2)
    {
        sprintf(test, "%2.2s", &buf[2]);
        b = atol(test);
        len = len - 2;
    }
    else
    {
        if (Format != ALGF_FORM_DATUM_MMJJ)
        {
            if (buf[2] > '1')
            {
                FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
                edit->SetFocus();
                return -1;
            }
        }
        return 0;
    }
    if (Format != ALGF_FORM_DATUM_MMJJ)
    {
        if (b > 12)
        {
            FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
            edit->SetFocus();
            return -1;
        }
    }
    if (len > 4)
    {
        FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
        edit->SetFocus();
        return -1;
    }
    if (len > 2 && Format != ALGF_FORM_DATUM_TTMMJJ)
    {
        FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
        edit->SetFocus();
        return -1;
    }
    if (len > 0 && Format == ALGF_FORM_DATUM_TTMM)
    {
        FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
        edit->SetFocus();
        return -1;
    }
    return 0;
}

long AllgZeitEingKonv(CString EingZeit)
{
    int zeit = 0;
    int x, y, z;
    int hhmmss[3] = { 0,0,0 };
    char test[3];
    int len = EingZeit.GetLength();

    for (x = 0, z = 0;;)
    {
        for (y = 0, test[0] = '\0'; y < 2; y++)
        {
            if (EingZeit.GetAt(x) >= '0' && EingZeit.GetAt(x) <= '9')
            {
                test[y] = EingZeit.GetAt(x);
                test[y + 1] = '\0';
            }
            else if (EingZeit.GetAt(x) == ':')
            {
                x++;
                break;
            }
            else
            {
                FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_ZEIT).GetString());
                return -1;
            }
            if (++x >= len) break;
        }
        hhmmss[z] = atoi(test);
        z++;
        if (x >= len) break;
        else if (EingZeit.GetAt(x) == ':')
        {
            if (++x >= len) break;
        }
    }
    if (hhmmss[0] > 23)
    {
        FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_ZEIT).GetString());
        return -1;
    }
    if (hhmmss[1] > 59)
    {
        FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_ZEIT).GetString());
        return -1;
    }
    if (hhmmss[2] > 59)
    {
        FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_ZEIT).GetString());
        return -1;
    }
    zeit = hhmmss[0] * 10000 + hhmmss[1] * 100 + hhmmss[2];
    return zeit;
}

long AllgDatumEingKonv(CString EingDatum, int Format)
{
    int day_tab[4][12] =
    {
       { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
       { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
       { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
       { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
    };
    tm* zeit;
    time_t acttime;
    long jahr = 0;
    long jahrhundert = 0;
    int monat;
    int schaltjahr;
    long datum = 0;
    int ttmmjj[3] = { 0,0,0 };
    char test[5];
    int ymax;
    int x = 0;
    int y;
    acttime = time(&acttime);

    for (y = 0, test[0] = '\0'; y < 2; y++)
    {
        if (x >= EingDatum.GetLength())
        {
            FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
            return -1;
        }
        if (EingDatum.GetAt(x) >= '0' && EingDatum.GetAt(x) <= '9')
        {
            test[y] = EingDatum.GetAt(x);
            test[y + 1] = '\0';
        }
        else if (EingDatum.GetAt(x) == '.') break;
        else
        {
            FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
            return -1;
        }
        x++;
    }
    if (Format == ALGF_FORM_DATUM_TTMM) ttmmjj[0] = atoi(test);
    if (Format == ALGF_FORM_DATUM_TTMMJJ) ttmmjj[0] = atoi(test);
    if (Format == ALGF_FORM_DATUM_MMJJ) ttmmjj[1] = atoi(test);

    if (Format == ALGF_FORM_DATUM_MMJJ) ymax = 4;
    else ymax = 2;

    for (y = 0, test[0] = '\0'; y < ymax; y++)
    {
        if (x >= EingDatum.GetLength())
        {
            break;
        }
        if (EingDatum.GetAt(x) >= '0' && EingDatum.GetAt(x) <= '9')
        {
            test[y] = EingDatum.GetAt(x);
            test[y + 1] = '\0';
        }
        else if (EingDatum.GetAt(x) == '.') break;
        else
        {
            FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
            return -1;
        }
        x++;
    }
    if (Format == ALGF_FORM_DATUM_TTMM) ttmmjj[1] = atoi(test);
    if (Format == ALGF_FORM_DATUM_TTMMJJ) ttmmjj[1] = atoi(test);
    if (Format == ALGF_FORM_DATUM_MMJJ) ttmmjj[2] = atoi(test);

    if (Format != ALGF_FORM_DATUM_TTMMJJ && x <= EingDatum.GetLength())
    {
        FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
        return -1;
    }

    for (y = 0, test[0] = '\0'; y < 4; y++)
    {
        if (x >= EingDatum.GetLength())
        {
            break;
        }
        if (EingDatum.GetAt(x) >= '0' && EingDatum.GetAt(x) <= '9')
        {
            test[y] = EingDatum.GetAt(x);
            test[y + 1] = '\0';
        }
        else
        {
            FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
            return -1;
        }
        x++;
    }
    ttmmjj[2] = atoi(test);
    if (ttmmjj[2] < 100)
    {
        zeit = localtime(&acttime);
        jahr = zeit->tm_year + 1900;
        jahrhundert = jahr / 100;
    }
 
    if (ttmmjj[2] == 0)  // Eingabe ohne Jahr
    {
        ttmmjj[2] = jahr;
    }
    else if (ttmmjj[2] < 100)  // Eingabe ohne jahrhundert
    {
        ttmmjj[2] = ttmmjj[2] + jahrhundert * 100;
    }
    if (ttmmjj[2] < 1900 || ttmmjj[2] > 2099)
    {
        FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
        return -1;
    }
    if (ttmmjj[1] > 12 || ttmmjj[1] < 1)
    {
        FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
        return -1;
    }

    schaltjahr = ttmmjj[2] % 4;
    monat = ttmmjj[1];
    if (ttmmjj[0] > day_tab[schaltjahr][monat - 1])
    {
        FehlerBehandlung(-2, (char*)CResString::ex().getStrTblText(IDS_TXT_FEHL_DATUM).GetString());
        return -1;
    }
    if (ttmmjj[0] == 0)
    {
        ttmmjj[0] = 1; //NASE
    }
    datum = ttmmjj[2] * 10000 + ttmmjj[1] * 100 + ttmmjj[0];
    return datum;
}


CTime CTimeFromTimeLong(int nYear, int nMonth, int nDay, long lTime)
{
    return CTime(nYear, nMonth, nDay,
        lTime / 10000,
        lTime / 100 % 100,
        lTime % 100);
}

CTime CTimeFromDateLong(int nHour, int nMin, int nSec, long lDate, int nDST /*= -1*/)
{
    return CTime(
        lDate / 10000,
        lDate / 100 % 100,
        lDate % 100,
        nHour, nMin, nSec, nDST);
}

CTime CTimeFromDateLongAndHour(int nHour, long lDate)
{
    return CTimeFromDateLong(nHour, 0, 0, lDate);
}

CTime CTimeFromDateLongMinTime(long lDate)
{
    return CTimeFromDateLong(0, 0, 0, lDate);
}

CTime CTimeFromDateLongMaxTime(long lDate)
{
    return CTimeFromDateLong(23, 59, 59, lDate);
}

CTime CTimeFromDateTimeLong(long lDate, long lTime)
{
    return CTimeFromDateLong(
        lTime / 10000,
        lTime / 100 % 100,
        lTime % 100,
        lDate);
}

CTime CTimeFromDateTimeLongNoSeconds(long lDate, long lTime)
{
    return CTimeFromDateLong(
        lTime / 100,
        lTime % 100,
        0,
        lDate);
}

long GetTotalSeconds(CTime& time)
{
    return (time.GetHour() * 3600)
         + (time.GetMinute() * 60)
         + time.GetSecond();
}

CTimeSpan CTimeSpanFromTimeLong(long lTime)
{
    return CTimeSpan(0,
        lTime / 10000,
        lTime / 100 % 100,
        lTime % 100);
}

CString DDMMYYYYStringFromDateLong(long lDate)
{
    CString str;
    str.Format("%02d.%02d.%04d",
        lDate % 100,
        lDate / 100 % 100,
        lDate / 10000);
    return str;
}

CString DDMMYYYYStringNoDotsFromDateLong(long lDate)
{
    CString str;
    str.Format("%08ld", lDate % 100 * 1000000 + (lDate / 100) % 100 * 10000 + lDate / 10000);
    return str;
}

// lTime : 800 = 08:00
CString HHmmStringFromShortTimeLong(long lTime)
{
    if (lTime > 2359)
    {
        return HHmmStringFromTimeLong(lTime);
    }

    CString str;
    str.Format("%02d:%02d",
        lTime / 100,
        lTime % 100);
    return str;
}

// lTime : 80000 = 08:00
CString HHmmStringFromTimeLong(long lTime)
{
    CString str;
    str.Format("%02d:%02d",
        lTime / 10000,
        lTime / 100 % 100);
    return str;
}

CString HHmmSSStringFromTimeLong(long lTime)
{
    CString str;
    str.Format("%02d:%02d:%02d",
        lTime / 10000,
        lTime / 100 % 100,
        lTime % 100);
    return str;
}

CTime GetEastern(long date)
{
    int year, month, day;
    PhoDateToDmy(date, &day, &month, &year);
    long gregdate = DmyToGreg(day, month, year);
    GregToDmy(gregdate, &day, &month, &year);
    long eastern = GregOstern(year);
    GregToDmy(eastern, &day, &month, &year);
    return CTime(year, month, day, 0, 0, 0, 0);
}

int AllgLaengeKontrWnd(CComboBox* cbx, int len)
{
    return AllgLaengeKontrWnd(cbx, len, 0);
}

int AllgLaengeKontrWnd(CComboBox* cbx, int len, int /*modus*/)
{
    char buf[241];
    CString CBuf, CStr;
    BOOL bAusgabe = FALSE;    //String muss nicht neu ausgegeben werden

    if (len > 240 || len < 1)
    {
        char str[81];
        sprintf(str, "%s AllgLaengeKontr %d", CResString::ex().getStrTblText(IDS_TXT_FEHLER_DBLPKT).GetString(), len);
        AfxMessageBox(str);
        return -1;
    }

    cbx->GetWindowText(CBuf);

    for (int i = 0; i < CBuf.GetLength(); i++) //Umwandlug Umlaute
    {
        if      (CBuf.GetAt(i) == 'Ä') CStr += "AE", bAusgabe = TRUE;
        else if (CBuf.GetAt(i) == 'Ü') CStr += "UE", bAusgabe = TRUE;
        else if (CBuf.GetAt(i) == 'Ö') CStr += "OE", bAusgabe = TRUE;
        else if (CBuf.GetAt(i) == 'ß') CStr += "ss", bAusgabe = TRUE;
        else if (CBuf.GetAt(i) == 'ä') CStr += "ae", bAusgabe = TRUE;
        else if (CBuf.GetAt(i) == 'ü') CStr += "ue", bAusgabe = TRUE;
        else if (CBuf.GetAt(i) == 'ö') CStr += "oe", bAusgabe = TRUE;
        else                           CStr += CBuf.GetAt(i);
    }

    if (CStr.GetLength() > len)
    {
        AfxMessageBox(CResString::ex().getStrTblText(IDS_TXT_MAX_ANZ_ZEICHEN));
        AllgStrCopy(buf, CStr, len + 1);
        buf[len] = '\0';
        CStr = buf;
        bAusgabe = TRUE;
    }

    if (bAusgabe)
    {
        cbx->SetWindowText(CStr);
        cbx->SetFocus();
        cbx->SetEditSel(len, len); //Selektion aufheben
        return -1;
    }

    return 0;
}


// Vom User eingestellte Spaltenbreiten aus Win-DB
void AllgSetColumnWidthUser(CListCtrl& lc, char* name, char* keypath, int anz)
{
    HKEY hKey;
    char szBuffer[180+1];
    DWORD len = sizeof(szBuffer) - 1;
    if (RegOpenKey(HKEY_CURRENT_USER, keypath, &hKey) == ERROR_SUCCESS)
    {
        if (RegQueryValueEx(hKey, name, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {
            // Werte gefunden
            szBuffer[len] = '\0';
            int width,pos;
            int found = 0;
            CString Spalten = szBuffer;
            for (int i = 0; i < anz; i++)
            {
                if (sscanf(Spalten, "%d", &width) == 0)
                    break;
                if (width > 0)
                {
                    found = 1;
                    break;
                }
            }
            if (found > 0)
            {
                for (int i = 0; i < anz; i++)
                {
                    if (sscanf(Spalten, "%d", &width) == 0)
                        break;
                    lc.SetColumnWidth(i, width);
                    if ((pos = Spalten.Find(", ")) == -1)
                        break;
                    Spalten = Spalten.Right(Spalten.GetLength() - pos - 2);
                }
            }
        }
        RegCloseKey(hKey);
    }
}

// Vom User eingestellte Spaltenbreiten in Win-DB
void AllgWriteColumnWidthUser(CListCtrl& lc, char* name, char* keypath, int anz)
{
    CString szBuffer;
    CString szNext;
    for (int i = 0; i < anz; i++)
    {
        if (i == 0)
            szBuffer.Format("%d", lc.GetColumnWidth(i));
        else
        {
            szNext.Format(", %d", lc.GetColumnWidth(i));
            szBuffer += szNext;
        }
    }
    HKEY hKey;
    if (RegCreateKey(HKEY_CURRENT_USER, keypath, &hKey) == ERROR_SUCCESS)
    {   // Werte setzen
        RegSetValueEx(hKey, name, 0, REG_SZ, (BYTE*)szBuffer.operator LPCTSTR(), szBuffer.GetLength());
        RegCloseKey(hKey);
    }
}

BOOL AllgCheckPrintableSign(CEdit* edit)
{
    CString Chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-.:,;<>!\"§$%&/()=?#+€ ";
    int charlen = 86;
    CString str;
    edit->GetWindowText(str);
    if (str.IsEmpty())
        return TRUE;
    char chN = str[str.GetLength() - 1];     //letztes Zeichen lesen
    for (int c = 0; c < charlen; c++)
    {
        if (chN == Chars.GetAt(c))
        {
            return TRUE;    //Feld ist leer
        }
    }
    str.GetBufferSetLength(str.GetLength() - 1);    //letztes Zeichen löschen
    int len = str.GetLength();
    edit->SetWindowText(str);
    edit->SetFocus();
    edit->SetSel(len, len, FALSE); //Selektion aufheben        return;

    return FALSE;
}

BOOL AllgCheckPrintableSignWnd(CComboBox* cbx)
{
    CString Chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789*-.:,;<>!\"§$%&/()=?#+€ ";
    int charlen = 86;
    CString str;
    cbx->GetWindowText(str);
    if (str.IsEmpty())
        return TRUE;
    char chN = str[str.GetLength() - 1];     //letztes Zeichen lesen
    for (int c = 0; c < charlen; c++)
    {
        if (chN == Chars.GetAt(c))
        {
            return TRUE;                //Feld ist leer
        }
    }
    str.GetBufferSetLength(str.GetLength() - 1);    //letztes Zeichen löschen
    int len = str.GetLength();
    cbx->SetWindowText(str);
    cbx->SetFocus();
    cbx->SetEditSel(len, len); //Selektion aufheben       return;

    return FALSE;
}
