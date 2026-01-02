// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MainFrm.h"
#include "SplashWnd.h"
#include "AeFView.h"

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndMultiLang)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndMultiLang)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_DATE, OnUpdateDate)
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_TIME, OnUpdateTime)
    ON_WM_CREATE()
    ON_WM_QUERYENDSESSION()
    ON_WM_CLOSE()
    ON_WM_ENTERIDLE()
    // Global help commands
    //ON_COMMAND(ID_HELP_INDEX, CFrameWndMultiLang::OnHelpIndex)
    //ON_COMMAND(ID_HELP_USING, CFrameWndMultiLang::OnHelpUsing)
    //ON_COMMAND(ID_HELP, CFrameWndMultiLang::OnHelp)
    //ON_COMMAND(ID_CONTEXT_HELP, CFrameWndMultiLang::OnContextHelp)
    //ON_COMMAND(ID_DEFAULT_HELP, CFrameWndMultiLang::OnHelpIndex)
    //ON_COMMAND(ID_HELP_FINDER, CFrameWndMultiLang::OnHelpFinder)
    //ON_COMMAND(ID_DEFAULT_HELP, CFrameWndMultiLang::OnHelpFinder)
    //ON_MESSAGE(WM_COMMANDHELP, OnCommandHelp)
    ON_MESSAGE(WM_HIPATHUSER, OnHiPathUser)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars

// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
    // same order as in the bitmap 'toolbar.bmp'
    ID_KUNDE_KND_WAHL,
    ID_KUNDE_OFFENE_AUFTRGE,
    ID_AUFTRAG_SAVE,
        ID_SEPARATOR,
    ID_KUNDE_ANRUFEN,
    ID_AUFTR_DEF,
    ID_AUFTR_BEARB,
    ID_BEARB_DEFNACHBEA,
    ID_AUF_FREITEXT,
    ID_AE_KOPF_FUSS,
        ID_SEPARATOR,
    ID_INF_KUNDE,
    ID_INF_ART,
    ID_INF_AUF,
        ID_SEPARATOR,
    ID_NEXT,
    ID_PRIOR,
        ID_SEPARATOR,
    ID_APP_ABOUT,
    ID_CONTEXT_HELP,
};

// toolbar buttons for HiPath - IDs are command buttons
static UINT BASED_CODE buttonsHP[] =
{
    // same order as in the bitmap 'toolbar1.bmp'
    ID_HIPATH_CALL_END,
    ID_HIPATH_CALL,
        ID_SEPARATOR,
    ID_HIPATH_LOGON,
    ID_HIPATH_LOGOFF,
        ID_SEPARATOR,
    ID_HIPATH_PAUSE_START,
    ID_HIPATH_PAUSE_STOP,
        ID_SEPARATOR,
    ID_HIPATH_ROUTBACK,
};


static UINT BASED_CODE indicators[] =
{
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    m_FirstTime = TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWndMultiLang::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect r(20,10,20+611, 10+449);

    // Registry abfragen
    HKEY hKey;
    char szBuffer[30+1];
    DWORD  len = sizeof(szBuffer) - 1;
    if (RegOpenKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        if (RegQueryValueEx(hKey, KEY_NAME_WINPOS, 0, NULL, (BYTE*)szBuffer,&len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            sscanf(szBuffer, KEY_FORMAT_WINPOS, &r.left, &r.top, &r.right, &r.bottom);
        }
        MoveWindow(r);

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_ORDERSORT, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->OrderSort = atoi(szBuffer);
        }
        else
        {
            AeGetApp()->OrderSort = 0;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_POOLNR, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->PoolNr = static_cast<short>(atoi(szBuffer));
        }
        else
        {
            AeGetApp()->PoolNr = 0;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_FASTOPEN, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsFastOpenOrder = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsFastOpenOrder = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_NOPARA, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsNoParaCall = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsNoParaCall = true;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_ANRPLAN, 0, NULL, (BYTE*)szBuffer,&len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsAnrufPlan = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsAnrufPlan = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_ANRPLAN_EIGEN, 0, NULL, (BYTE*)szBuffer,&len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsAnrufPlanEigen = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsAnrufPlanEigen = false;
        }

        //Setzen der Standard Auftrags- Kommi und Buchungsart für den aktuellen Arbeitsplatz
        len = sizeof(szBuffer) - 1;
        AeGetApp()->IsStdAKBArt = false;
        if (RegQueryValueEx(hKey, KEY_NAME_STDAKBART, 0, NULL, (BYTE*)szBuffer,&len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            CString Buffer = szBuffer;
            CString Msg;
            if (Buffer.GetLength() == 4)
            {
                AeGetApp()->StdAuftArt = Buffer.Left(2);
                AeGetApp()->StdKommArt = Buffer.GetAt(2);
                AeGetApp()->StdBuchArt = Buffer.GetAt(3);
                if (Buffer != "NO00")
                {
                    AeGetApp()->IsStdAKBArt = true;
                    Msg.Format(CResString::ex().getStrTblText(IDP_INFO_STD_KOMB_AKB_ART), Buffer.GetString());
                    MsgBoxOK(Msg, MB_ICONINFORMATION);
                }
            }
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_KUNDEIDF, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsKundeIDF = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsKundeIDF = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_NURAKTF11, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsNurAktF11 = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsNurAktF11 = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_NOBATCH, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsNoBatch = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsNoBatch = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_NOPROMO, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsNoPromo = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsNoPromo = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_KOMMANOTAB, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsKommaNoTab = (szBuffer[0] == '1' ? true : false);
        }
        else
        {
            AeGetApp()->IsKommaNoTab = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_NOKIPPZEIT, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsNoKippzeit = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsNoKippzeit = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_FIRSTLETTER, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsFirstLetter = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsFirstLetter = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_KUNDEHOME, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsKundeHome = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsKundeHome = true;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_ALLEVZ, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsAlleVz = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsAlleVz = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_NURDAFUE, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsNurDafue = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsNurDafue = true;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_RRMELD, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsRRMeld = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsRRMeld = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_RRNOTDONE, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsRRNotDone = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsRRNotDone = true;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_NOBEEP, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsNoBeep = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsNoBeep = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_POSZUSAMMEN, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsPosZusammen = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsPosZusammen = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_MELDOFFAUF, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsOffAufMeld = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsOffAufMeld = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_AUSWAHLKURZ, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsAuswahlKurz = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsOffAufMeld = false; // TODO SetAuswahlKurz ???
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_ANZEIGEALLE, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsAnzeigeAlle = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsAnzeigeAlle = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_ANZEIGEALLEDEF, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsAnzeigeAlleDef = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsAnzeigeAlleDef = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_MAILVZEIGEN, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsMailVzEigen = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsMailVzEigen = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_SOFORT, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsSofort = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsSofort = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_SELECTEDAART, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            AeGetApp()->SelectedAArt = szBuffer;
        }
        else
        {
            AeGetApp()->SelectedAArt = "";
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_NST, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            AeGetApp()->m_ProCenter.SetNST(szBuffer);
        }
        else
        {
            AeGetApp()->m_ProCenter.SetNST("");
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_MATCHCODE, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsMatchCode = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsMatchCode = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_ANZRABATTE, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsAnzRabatte = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsAnzRabatte = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_NOVA10, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsNoVA10 = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsNoVA10 = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_TERMINAL, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->Geraet = szBuffer;
        }
        else
        {
            AeGetApp()->Geraet = "";
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_SCHRIFT, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->IsSchrift = (szBuffer[0] == '1');
        }
        else
        {
            AeGetApp()->IsSchrift = false;
        }

        len = sizeof(szBuffer) - 1;
        if (RegQueryValueEx(hKey, KEY_NAME_TELEFONIETYP, 0, NULL, (BYTE*)szBuffer, &len) == ERROR_SUCCESS)
        {   // Werte gefunden
            szBuffer[len] = '\0';
            AeGetApp()->TelefonieTyp = (szBuffer[0] == '1' ? 1 : 0);
        }
        else
        {
            AeGetApp()->TelefonieTyp = 0;
        }

        RegCloseKey(hKey);
    }

    if (!m_wndToolBar.Create(this) ||
        !m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
        !m_wndToolBar.SetButtons(buttons,
          sizeof(buttons)/sizeof(UINT)))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }

    if (!m_wndStatusBar.Create(this) ||
        !m_wndStatusBar.SetIndicators(indicators,
          sizeof(indicators)/sizeof(UINT)))
    {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndToolBar);

    SetWindowText(CResString::ex().getStrTblText(AETXT_PHOSIX_AUFTRAGSANN));

    m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

    // CG: The following line was added by the Splash Screen component.
    CSplashWnd::ShowSplashScreen(this);
    // CG: The following block was inserted by 'Status Bar' component.
    {
        // Find out the size of the static variable 'indicators' defined
        // by AppWizard and copy it
        int nOrigSize = sizeof(indicators) / sizeof(UINT);

        UINT* pIndicators = new UINT[nOrigSize + 2];
        memcpy(pIndicators, indicators, sizeof(indicators));

        // Call the Status Bar Component's status bar creation function
        if (!InitStatusBar(pIndicators, nOrigSize, 60))
        {
            TRACE0("Failed to initialize Status Bar\n");
            return -1;
        }
        delete[] pIndicators;
    }
    if (!GetAeUser().UpdSeraPlan())
    {
        GetMenu()->DeleteMenu(10, MF_BYPOSITION);
        GetMenu()->DeleteMenu(10, MF_BYPOSITION);
        DrawMenuBar();
    }

    if (GetAeUser().IsHiPathUser())
    {
        if (!m_wndToolBarHP.Create(this) ||
            !m_wndToolBarHP.LoadBitmap(IDR_TOOLBAR1) ||
            !m_wndToolBarHP.SetButtons(buttonsHP, sizeof(buttonsHP) / sizeof(UINT)))
        {
            TRACE0("Failed to create toolbarHP\n");
            return -1;      // fail to create
        }
        // TODO: Delete these two lines if you don't want the toolbar to be dockable
        m_wndToolBarHP.EnableDocking(CBRS_ALIGN_ANY);
        EnableDocking(CBRS_ALIGN_ANY);

        CFrameWndMultiLang* pFrame = (CFrameWndMultiLang*)(m_wndToolBar.GetDockingFrame());
        pFrame->RecalcLayout();
        CRect rect;
        m_wndToolBar.GetWindowRect(&rect);
        rect.OffsetRect(1000, 0);
        pFrame->DockControlBar(&m_wndToolBarHP, AFX_IDW_DOCKBAR_TOP, &rect);

        m_wndToolBarHP.SetBarStyle(m_wndToolBarHP.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
    }
    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT &cs)
{
    if (CFrameWndMultiLang::PreCreateWindow(cs) == 0)
        return FALSE;
    cs.style &= ~(LONG)FWS_ADDTOTITLE;  //Kein Dokumentname im Frame
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWndMultiLang::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWndMultiLang::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//Verhindern, daß bei der Beendigung von Windows AE beendet wird
BOOL CMainFrame::OnQueryEndSession()
{
    if (!CFrameWndMultiLang::OnQueryEndSession())
        return FALSE;

    MsgBoxOK(IDP_END_SESSION);

    return FALSE; //Windows wird nicht beendet
}

void CMainFrame::OnUpdateDate(CCmdUI* pCmdUI)
{
    // CG: This function was inserted by 'Status Bar' component.

    // Get current date and format it
    CTime time = CTime::GetCurrentTime();
    CString strDate = time.Format(_T("%d.%m.%y"));

    // BLOCK: compute the width of the date string
    CSize size;
    {
        HGDIOBJ hOldFont = NULL;
        HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
        CClientDC dc(NULL);
        if (hFont != NULL)
            hOldFont = dc.SelectObject(hFont);
        size = dc.GetTextExtent(strDate);
        if (hOldFont != NULL)
            dc.SelectObject(hOldFont);
    }

    // Update the pane to reflect the current date
    UINT nID, nStyle;
    int nWidth;
    m_wndStatusBar.GetPaneInfo(m_nDatePaneNo, nID, nStyle, nWidth);
    m_wndStatusBar.SetPaneInfo(m_nDatePaneNo, nID, nStyle, size.cx);
    pCmdUI->SetText(strDate);
    pCmdUI->Enable(TRUE);

}

void CMainFrame::OnUpdateTime(CCmdUI* pCmdUI)
{
    // CG: This function was inserted by 'Status Bar' component.

    // Get current date and format it
    CTime time = CTime::GetCurrentTime();
    if (m_FirstTime)
        m_FirstTime = FALSE;
    else if (time.GetSecond() != 0)
        return;
    CString strTime = time.Format(_T("%X"));
    strTime = strTime.Left(5);

    // BLOCK: compute the width of the date string
    CSize size;
    {
        HGDIOBJ hOldFont = NULL;
        HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
        CClientDC dc(NULL);
        if (hFont != NULL)
            hOldFont = dc.SelectObject(hFont);
        size = dc.GetTextExtent(strTime);
        if (hOldFont != NULL)
            dc.SelectObject(hOldFont);
    }

    // Update the pane to reflect the current time
    UINT nID, nStyle;
    int nWidth;
    m_wndStatusBar.GetPaneInfo(m_nTimePaneNo, nID, nStyle, nWidth);
    m_wndStatusBar.SetPaneInfo(m_nTimePaneNo, nID, nStyle, size.cx);
    pCmdUI->SetText(strTime);
    pCmdUI->Enable(TRUE);

}

BOOL CMainFrame::InitStatusBar(UINT *pIndicators, int nSize, int nSeconds)
{
    // CG: This function was inserted by 'Status Bar' component.

    // Create an index for the DATE pane
    m_nDatePaneNo = nSize++;
    pIndicators[m_nDatePaneNo] = ID_INDICATOR_DATE;
    // Create an index for the TIME pane
    m_nTimePaneNo = nSize++;
    nSeconds = 1;
    pIndicators[m_nTimePaneNo] = ID_INDICATOR_TIME;

    m_wndStatusBar.SetTimer(0x1000, nSeconds * 1000, NULL);

    return m_wndStatusBar.SetIndicators(pIndicators, nSize);

}

void CMainFrame::OnClose()
{
    HKEY hKey;
    char szBuffer[30];
    CRect rect;

    GetWindowRect(rect);
    sprintf(szBuffer, KEY_FORMAT_WINPOS, rect.left, rect.top, rect.right, rect.bottom);
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {   // Werte setzen
        RegSetValueEx(hKey, KEY_NAME_WINPOS, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    sprintf(szBuffer, "%d", AeGetApp()->OrderSort());
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_ORDERSORT, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    sprintf(szBuffer, "%d", AeGetApp()->PoolNr());
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_POOLNR, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    sprintf(szBuffer, "%d", AeGetApp()->ProcenterBranchno());
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_HPBRANCH, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsFastOpenOrder() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_FASTOPEN, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsAnrufPlan() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_ANRPLAN, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsAnrufPlanEigen() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_ANRPLAN_EIGEN, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsNoParaCall() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_NOPARA, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsKundeIDF() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_KUNDEIDF, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsNurAktF11() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_NURAKTF11, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsNoBatch() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_NOBATCH, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsNoPromo() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_NOPROMO, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsNoKippzeit() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_NOKIPPZEIT, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsFirstLetter() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_FIRSTLETTER, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsKommaNoTab() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_KOMMANOTAB, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsSchrift() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_SCHRIFT, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsKundeHome() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_KUNDEHOME, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsRRMeld() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_RRMELD, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsRRNotDone() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_RRNOTDONE, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsNoBeep() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_NOBEEP, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsPosZusammen() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_POSZUSAMMEN, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsOffAufMeld() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_MELDOFFAUF, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsAuswahlKurz() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_AUSWAHLKURZ, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsAnzeigeAlle() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_ANZEIGEALLE, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsAnzeigeAlleDef() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_ANZEIGEALLEDEF, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsMailVzEigen() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_MAILVZEIGEN, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsSofort() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_SOFORT, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    sprintf(szBuffer, "%s", AeGetApp()->SelectedAArt().GetString());
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_SELECTEDAART, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    sprintf(szBuffer, "%s", AeGetApp()->m_ProCenter.GetNST().GetString());
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_NST, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsMatchCode() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_MATCHCODE, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsAnzRabatte() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_ANZRABATTE, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->IsNoVA10() ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_NOVA10, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    strcpy(szBuffer, AeGetApp()->TelefonieTyp() == 1 ? "1" : "0");
    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, KEY_NAME_TELEFONIETYP, 0, REG_SZ, (BYTE*)szBuffer, strlen(szBuffer));
        RegCloseKey(hKey);
    }

    if (AeGetApp()->m_ProCenter.IsHiPathLogon())
    {
        AeGetApp()->m_ProCenter.AgentLogOff();
    }
    if (AeGetApp()->m_ProCenter.IsHiPathConnected())
    {
        AeGetApp()->m_ProCenter.ServerDisconnect();
    }

    ((CAeFView*)AeGetApp()->m_pViewEing)->SaveListColumns();
    CFrameWndMultiLang::OnClose();
}

LRESULT CMainFrame::OnCommandHelp(WPARAM wParam, LPARAM lParam)
{
    if (lParam == 0) {
        if (m_nIDTracking > 0xe001) {
            // Das Menü des Rahmens (Systemmenü)
            lParam = HID_BASE_COMMAND + m_nIDTracking;
        }
        else {
            CView* pView = GetActiveView();
            if (pView) {
                //Leite die Hilfeanforderung an die Sicht weiter
                return pView->SendMessage(WM_COMMANDHELP, wParam, 0L);
            }
            else {
                lParam = HID_BASE_RESOURCE + IDR_MAINFRAME;
            }
        }
    }
    if (lParam != 0) {
        AfxGetApp()->WinHelp(lParam);
        return TRUE;
    }
    return FALSE;
}

void CMainFrame::OnEnterIdle(UINT nWhy, CWnd* pWho)
{
    CFrameWndMultiLang::OnEnterIdle(nWhy, pWho);
}

LRESULT CMainFrame::OnHiPathUser(WPARAM wParam, LPARAM /*lParam*/)
{
    CString woher;
    woher = "CMainFrame::OnHiPathUser";
    if (wParam == 0)
    {
#ifdef _NEWHIPATH
        if (AeGetApp()->m_ProCenter.IsHiPathPause() && !AeGetApp()->m_ProCenter.IsHiPathUserBusy())
        {
        }
        else
        {
            if (AeGetApp()->m_ProCenter.IsHiPathOtherWork())
            {
                AeGetApp()->m_ProCenter.SetUserAtWork(woher, FALSE);
                AeGetApp()->m_ProCenter.SetHiPathOtherWork(FALSE);
            }
            else
            {
                AeGetApp()->m_AeTrace.WriteTrace(woher, "CMainFrame", "AcdAgentExitPostProc");
                AeGetApp()->m_ProCenter.AcdAgentExitPostProc(AeGetApp()->RequeueCount());
                AeGetApp()->m_ProCenter.SetHiPathUserBusy(FALSE);
                AeGetApp()->m_ProCenter.SetHiPathWorking(FALSE);
                AeGetApp()->m_ProCenter.SetHiPathPauseWished(FALSE);
            }
        }
#endif
        AeGetApp()->m_ProCenter.SetUserAtWork(woher, FALSE);
    }
    else
    {
        AeGetApp()->m_ProCenter.SetUserAtWork(woher, TRUE);
    }
    return 0L;
}
