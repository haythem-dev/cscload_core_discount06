//(c)---------- Customer service program -------------------------------------//
/*
   Source: mainfrm.h
   Author: Ae-Programmer
   made  : 27.04.2000

   declaration:
   Dialog: maintenance for callplan
*/

//----------------------------------------------------------------------------//
//--- define -----------------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- pc-registry ------------------------------------------------------------//

#define KEY_PATH                    "Software\\PRZ\\Phosix"
#define KEY_NAME_WINPOS             "Window"
#define KEY_NAME_USER               "User"
#define KEY_NAME_ORDERSORT          "OrdSort"
#define KEY_NAME_FASTOPEN           "FastOpen"
#define KEY_NAME_ANRPLAN            "AnrPlan"
#define KEY_NAME_ANRPLAN_EIGEN      "AnrPlanEigen"
#define KEY_NAME_NOPARA             "NoPara"
#define KEY_NAME_STDAKBART          "StdAKBArt"
#define KEY_FORMAT_WINPOS           "%d, %d, %d, %d"
#define KEY_NAME_KUNDEIDF           "KindeIDF"
#define KEY_NAME_KUNDEHOME          "KundeHome"
#define KEY_NAME_ALLEVZ             "AlleVz"
#define KEY_NAME_NURDAFUE           "NurDafue"
#define KEY_NAME_BRANCH             "Branch"
#define KEY_NAME_BRANCHNAME         "BranchName"
#define KEY_NAME_RRMELD             "RRMeld"
#define KEY_NAME_RRNOTDONE          "RRNotDone"
#define KEY_NAME_NOBEEP             "NoBeep"
#define KEY_NAME_POSZUSAMMEN        "PosZusammen"
#define KEY_NAME_MELDOFFAUF         "MeldOffAuff"
#define KEY_NAME_AUSWAHLKURZ        "AuswahlKurz"
#define KEY_NAME_ANZEIGEALLE        "AnzeigeAlle"
#define KEY_NAME_ANZEIGEALLEDEF     "AnzeigeAlleDef"
#define KEY_NAME_LISTBOX_CPCHECK    "LBcpcheck"
#define KEY_NAME_LISTBOX_CPPROBLEM  "LBcpproblem"
#define KEY_NAME_SELECTEDAART       "SelectedAArt"
#define KEY_NAME_MAILVZEIGEN        "MailVzEigen"
#define KEY_NAME_SOFORT             "Sofort"
#define KEY_NAME_NST                "NST"
#define KEY_NAME_HPBRANCH           "ProcenterBranchNo"
#define KEY_NAME_MATCHCODE          "MatchCode"
#define KEY_NAME_POOLNR             "PoolNr"
#define KEY_NAME_TERMINAL           "Terminal"
#define KEY_NAME_ANZRABATTE         "AnzRabatte"
#define KEY_NAME_NOVA10             "NoVA10"
#define KEY_NAME_NURAKTF11          "NurAktF11"
#define KEY_NAME_NOBATCH            "NoBatch"
#define KEY_NAME_SCHRIFT            "Schrift"
#define KEY_NAME_NOPROMO            "NoPromo"
#define KEY_NAME_NOKIPPZEIT         "NoKippzeit"
#define KEY_NAME_FIRSTLETTER        "FirstLetter"
#define KEY_NAME_KOMMANOTAB         "KommaNoTab"
#define KEY_NAME_VBANZEIGE          "VBAnzeige"
#define KEY_NAME_TELEFONIETYP       "TelefonieTyp"

//Callplan
#define KEY_NAME_CALLPLAN           "CPlan"
#define KEY_NAME_PROBLEMCALLS       "PCall"
#define KEY_NAME_AUTOMIN            "AutoMin"
#define KEY_NAME_WARNCOUNT          "WarnCount"
#define KEY_NAME_WARNMIN            "WarnMin"
#define KEY_NAME_WARNMINPROLEMCALL  "WarnProblem"
#define KEY_NAME_ACTIVATEWND        "ActivateWnd"
#define KEY_NAME_LANGUAGE           "Language"
#define KEY_NAME_PORTNR             "Portnr"

#ifdef _DEBUG
#define KEY_NAME_PASSWD     "Password"
#endif

//----------------------------------------------------------------------------//
//--- class CMainFrame (Frame) -----------------------------------------------//
//----------------------------------------------------------------------------//

class CMainFrame : public CFrameWndMultiLang
{
    DECLARE_DYNCREATE(CMainFrame)

protected: // create from serialization only
    CMainFrame();

    BOOL PreCreateWindow(CREATESTRUCT& cs);
    afx_msg void OnUpdateDate(CCmdUI* pCmdUI);
    afx_msg void OnUpdateTime(CCmdUI* pCmdUI);
    afx_msg LRESULT OnCommandHelp(WPARAM wParam, LPARAM lParam);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnQueryEndSession();
    afx_msg void OnClose();
    afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
    afx_msg LRESULT OnHiPathUser(WPARAM wParam, LPARAM lParam);
    DECLARE_MESSAGE_MAP()


public: // Attributes
    int m_nDatePaneNo;
    int m_nTimePaneNo;

public: // Implementation
    virtual ~CMainFrame();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
    CStatusBar  m_wndStatusBar;
    CToolBar    m_wndToolBar;
    CToolBar    m_wndToolBarHP;

    BOOL m_FirstTime;

private:
    BOOL InitStatusBar(UINT *pIndicators, int nSize, int nSeconds);
};
