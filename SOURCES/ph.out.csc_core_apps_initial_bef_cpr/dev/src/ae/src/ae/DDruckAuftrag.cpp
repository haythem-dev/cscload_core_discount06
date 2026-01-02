// DDruckAuftrag.cpp : implementation file
//
#include "stdafx.h"
#include "DDruckAuftrag.h"

extern "C"
{
    #include "allg.h"
}

void CDruckAuftrag::AddKopfZeile(const CString& Kopf)
{
    CString K = Kopf;
    doppproz(K);
    m_CListKopf.AddTail(K);
}

void CDruckAuftrag::AddFussZeile(const CString& Fuss)
{
    CString F = Fuss;
    doppproz(F);
    m_CListFuss.AddTail(F);
}

void CDruckAuftrag::DelAllData()
{
    m_CListKopf.RemoveAll();
    m_CListPos.RemoveAll();
    m_CListFuss.RemoveAll();
}

void CDruckAuftrag::Druck(BOOL Querdruck)   // Daten drucken
{
    if (!StartDruck(Querdruck))
        return;
    PageDruck();
    EndDruck();
}

bool CDruckAuftrag::StartDruck(BOOL Querdruck)  // Drucker einrichten
{
    CPrintDialog druck(FALSE);
    // speichern der Flags, da GetDefaults() diese verandert
    DWORD tempFlags = druck.m_pd.Flags;

    // Werte des Standarddruckers holen
    if (druck.GetDefaults())
    {
        ASSERT(druck.m_pd.hDevMode!=NULL);
        DEVMODE FAR* pDevMode = (DEVMODE FAR*)GlobalLock(druck.m_pd.hDevMode);
        ASSERT(pDevMode!=NULL);
        // Werte vorbelegen
        pDevMode->dmOrientation = Querdruck ? DMORIENT_LANDSCAPE : DMORIENT_PORTRAIT;
        pDevMode->dmPaperSize = DMPAPER_A4;

        GlobalUnlock(druck.m_pd.hDevMode);
        // Flags wiederherstellen
        druck.m_pd.Flags = tempFlags;
    }
    if (druck.DoModal() == IDCANCEL)
        return FALSE;
    dc = CDC::FromHandle (druck.GetPrinterDC());

// Versuch des Fonts
    m_pFont = NULL;
    LOGFONT lFont;

    if (!(dc->GetCurrentFont()->GetLogFont(&lFont)))
    {
        AfxMessageBox("error in getlogfont!");
    }
    else
    {
        TEXTMETRIC tMetr;
        dc->GetTextMetrics(&tMetr);
        lFont.lfWidth  = 0;
        lFont.lfHeight = -100;
        m_pFont = new CFont();
        strcpy(lFont.lfFaceName, "Courier");
        lFont.lfWeight = FW_NORMAL;
        lFont.lfUnderline = false;

        // auf nicht proportionale schrift aendern
        lFont.lfPitchAndFamily = (FIXED_PITCH || FF_DONTCARE);
        if (m_pFont->CreateFontIndirect(&lFont))
        {
            dc->SelectObject(m_pFont);
        }
    }

    // Grösse von Grossbuchstaben berechnen
    CSize extentChar = dc->GetTextExtent("M", 1);
    nCharHeight = extentChar.cy;
    nCharWidth = extentChar.cx;
    // Seitengrösse in Zeilenzahl holen
    nExtPage = (dc -> GetDeviceCaps(VERTRES) - nCharHeight ) / nCharHeight;
// Ende des Versuch

    di.lpszDocName = AET_AUFTRAGSERF_SYSTEM;
    di.lpszOutput = NULL;
    di.cbSize = sizeof(DOCINFO);
    di.lpszDatatype = NULL;
    di.fwType = NULL;
    int rc = dc->StartDoc(&di);
    if (rc < 0)
    {
        LPVOID pszError;
        CString strErrMsg;
        DWORD errCode = GetLastError();
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, errCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&pszError, 0, NULL);
        strErrMsg.Format("GetLastError() = %d\n", errCode);
        strErrMsg += (LPTSTR)pszError;
        LocalFree(pszError);
        AfxMessageBox(strErrMsg);
        sprintf(szError, "%s[%d]", AET_DRUCKER_FEHLER, rc);
        AfxMessageBox(szError, MB_OK);
        return FALSE;
    }

    return TRUE;
}

void CDruckAuftrag::PageDruck() // Ausgabe der Daten auf Drucker
{
    anzposgesamt = m_CListPos.GetCount();
    if (anzposgesamt == 0)
        return; // Anzahl Positionen
    anzfuss = m_CListFuss.GetCount(); // Anzahl Fusszeilen
    anzkopf = m_CListKopf.GetCount(); // Anzahl Kopfzeilen
    beginfuss = nExtPage - anzfuss;
    anzpos = nExtPage - anzkopf - anzfuss;
    if (anzpos < 1)
    {
        AfxMessageBox(AET_LISTE_FEHLER, MB_OK);
        return;
    }
    anzseiten = anzposgesamt / anzpos; //Anzahl der zu druckenden Seiten
    if ((anzposgesamt % anzpos) > 0)
        anzseiten++; //plus 1 angefangene Seite
    poszeile = m_CListPos.GetHeadPosition();
    for (int seite = 0; seite < anzseiten; seite++)
    {
        dc -> StartPage();
        int zeile = 0;
        // Ausgeben Kopfzeilen sofern vorhanden
        if (!m_CListKopf.IsEmpty())
        {
            poskopf = m_CListKopf.GetHeadPosition();
            for (int i = 0; i < anzkopf; i++)
            {
                Str.Format(m_CListKopf.GetNext(poskopf), seite + 1, anzseiten);
                dc->TextOut(0, zeile++ * nCharHeight, Str);
            }
        }
        // Ausgeben der Positionen
        for (int i = 0; i < anzpos; i++)
        {
            if (poszeile == NULL)
                break;
            Str = m_CListPos.GetNext(poszeile);
            dc->TextOut(0, zeile++ * nCharHeight, Str);
        }
        // Ausgeben Fusszeilen sofern vorhanden
        if (!m_CListFuss.IsEmpty())
        {
            zeile = beginfuss;
            posfuss = m_CListFuss.GetHeadPosition();
            for (int i = 0; i < anzfuss; i++)
            {
                Str.Format(m_CListFuss.GetNext(posfuss), seite + 1, anzseiten);
                dc->TextOut(0, zeile++ * nCharHeight, Str);
            }
        }
        dc->EndPage();
    }
}

void CDruckAuftrag::EndDruck()  // Drucker schließen
{
    dc->EndDoc();
}

void CDruckAuftrag::doppproz(CString& str)
{
    CString buffer;
    for (int i = 0; i < str.GetLength(); i++)
    {
        if (str.GetAt(i) == '%')
        {
            if (i < str.GetLength() - 1)    // wenn letztes Zeichen %
            {
                if (str.GetAt(i + 1) == 'd')
                    continue;   //und das darauffolgende kein d
                if (str.GetAt(i + 1) == '%')
                {
                    ++i;
                    continue;
                }
            }
            buffer = str.Left(i + 1);     // dann %-Zeichen verdoppeln
            buffer += '%';
            buffer += str.Right(str.GetLength() - (i + 1));
            str = buffer;
            ++i;
        }
    }
}

void CDruckAuftrag::AddZeile (CString &Position)
{
    AddPosZeile(Position);
}
