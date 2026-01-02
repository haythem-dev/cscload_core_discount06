#pragma once

// DPlanTag.h : header file
//
/////////////////////////////////////////////////////////////////////////////

class CRUFPTAG;
class CDPlanTagUpd;
class CDPlanTagRuf;

class CDPlanTag : public CDialogMultiLang, CPageBrowser
{
// Construction
public:
    CDPlanTag(CWnd* pParent = NULL);   // standard constructor
    void SetListbox(int pos, CDPlanTagUpd*);
    CString EventPosition(int stat);                // StatusEreignis
    void    SetRufPlanKndInfo(CDPlanTagRuf* d, int pos);
    bool    m_bCall;                                // true -> direkter aufruf F5
    bool    m_bNoParaCalls;
    short   m_VzNr;

    enum { IDD = IDD_AE_ANRUFPLAN_TAG };
    CEdit   m_CEditDatum;
    CEdit   m_CEditRufzeitab;
    CStatic m_CStaticAuswahl;
    CButton m_CRadioAlle;
    CEdit   m_EditIdf;
    CListCtrl m_ListCtl;
    CString m_CIdf;
    CString m_CStringAuswahl;
    CString m_CCall;
    CEdit m_CEditPool;
    CString m_CPool;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    void CallGetPage();
    int  GetStatusSelect(int* newRow);       // STatus aus Radiobuttons
    int  CheckDeleted();
    int  CheckAndSetGrasp(int skip);         // Zugriff testen!
    int  EventStatus(CString stat);          // Status
    long GetIdfNrOfListBox(CString& idfNr, short& VzNo);     // Idf aus Listbox everywhere
    long GetRufZeitOfListBox(CString& rufzeit);
    long GetAktRufZeitOfListBox(CString& aktrufzeit);
    int  GetLockOfListBox();                 // select status
    bool GetPage(const int nKzUpDown = NEXT_PG);    // List-Box mit Eintraegen versorgen
    void SelectEintrag(int call);
    void CloseCursor();                      // DB-Cursor schliessen

    virtual BOOL OnInitDialog();
    afx_msg void OnDestroy();
    afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnButtonKnd();
    afx_msg void OnChangeEditIdf();
    afx_msg void OnChangeEditRufzeitab();
    afx_msg void OnButtonAendern();
    afx_msg void OnButtonHinzufuegen();
    virtual void OnOK();
    afx_msg void OnButtonLoeschen();
    afx_msg void OnButtonHistorie();
    afx_msg void OnButtonAnrufen();
    afx_msg void OnChangeEditDatum();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnEnChangeEditPool();

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDPlanTagUpd dialog

class CDPlanTagUpd : public CDialogMultiLang
{
// Construction
public:
    CDPlanTagUpd(CWnd* pParent = NULL);   // standard constructor
    int CheckPrio( BOOL bFromWindow = FALSE );      // Radiobuttons auswerten

    enum { IDD = IDD_AE_ANRUFPLAN_TAG_AEN };
    CButton m_CRadioAnrufart;
    CStatic m_CStaticAnrufart;
    CEdit   m_CEditBemerkung;
    CStatic m_CStaticPrio;
    CStatic m_CStaticAuswahl;
    CEdit   m_EditAnrufzeit;
    CButton m_CRadio10;
    CEdit   m_EditRr_nr;
    CStatic m_CStaticKurzwahl;
    CStatic m_CStaticKndklasse;
    CStatic m_CStaticName;
    CStatic m_CStaticTelnr;
    CStatic m_CStaticPlz;
    CStatic m_CStaticOrt;
    CStatic m_CStaticDatum;
    CStatic m_CStaticApo;
    CButton m_CBrr;
    CString m_CApo;
    CString m_CDatum;
    CString m_CName;
    CString m_COrt;
    CString m_CPlz;
    CString m_CTelnr;
    CString m_CEditrr_nr;
    CString m_CKurzwahl;
    CString m_CIdfnr;
    CString m_CStringAuswahl;
    CString m_CAnrufzeit;
    BOOL    m_CBoolRr;
    CString m_CPrio;
    CString m_CBemerkung;
    CString m_CAnrufart;
    short m_sVzNr;
    CEdit m_CEditPool;
    CString m_CPool;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    int SelectKunde(long lIdfNr, short sVzNr);               // DBabfrage Kunde
    void SetRadioButton();
    void SetAnrufArt();

    virtual void OnOK();
    afx_msg void OnCheckRr();
    virtual void OnCancel();
    virtual BOOL OnInitDialog();
    afx_msg void OnClickSpinAnrufzeit(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRclickSpinAnrufzeit(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnReturnSpinAnrufzeit(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnChangeEditAnrufzeit();
    afx_msg void OnRadio1();
    afx_msg void OnRadio2();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);
    afx_msg void OnEnChangeEditPool();

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDPlanTagPrt dialog

class CDPlanTagPrt : public CDialogMultiLang
{
// Construction
public:
    int m_iIsLocked;
    CString m_CDlgText;
    CDPlanTagPrt(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_ANRUFPLAN_PRT };
    CListCtrl m_ListCtl;
    CStatic m_CStaticPlz;
    CStatic m_CStaticOrt;
    CStatic m_CStaticName;
    CStatic m_CStaticDatum;
    CStatic m_CStaticApo;
    CString m_CIdfnr;
    CString m_CRufzeit;
    short m_sVzNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    int SelectKunde(long IdfNr, short sVzNr);

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonEntsperren();
    virtual void OnOK();

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDPlanTagLoe dialog

class CDPlanTagLoe : public CDialogMultiLang
{
// Construction
public:
    CDPlanTagLoe(CWnd* pParent = NULL);   // standard constructor
    int CheckDeleteStat();
    int CheckSetRadio();
    int m_iChoice;                        // merken auswahl radiobutton

    enum { IDD = IDD_AE_ANRUFPLAN_LOE };
    CButton m_CRadio10;
    CEdit   m_CEditBemerkung;
    CString m_CBemerkung;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnRadio10();
    afx_msg void OnRadio11();
    afx_msg void OnRadio12();
    afx_msg void OnRadio13();
    afx_msg void OnRadio14();

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDPlanTagRuf dialog

class CDPlanTagRuf : public CDialogMultiLang
{
// Construction
public:
    CDPlanTagRuf(CWnd* pParent = NULL);   // standard constructor

    enum { IDD = IDD_AE_ANRUFPLAN_RUF };
    CButton m_CParaauftrag;
    CListBox m_CListTour;
    CStatic m_CStaticAnrufart;
    CButton m_CButtonPhonienichtda;
    CButton m_CButtonPhoniebelegt;
    CButton m_CButtonAponichtda;
    CButton m_CButtonApobelegt;
    CStatic m_CStaticRufzeit;
    CStatic m_CStaticIdfnr;
    CStatic m_CStaticZeit;
    CStatic m_CStaticTelnr;
    CStatic m_CStaticRufart;
    CStatic m_CStaticRrnr;
    CStatic m_CStaticRr;
    CStatic m_CStaticPrio;
    CStatic m_CStaticPlz;
    CStatic m_CStaticOrt;
    CStatic m_CStaticName;
    CStatic m_CStaticKurzwahl;
    CStatic m_CStaticKndklasse;
    CStatic m_CStaticDatum;
    CStatic m_CStaticBemerkung;
    CStatic m_CStaticApo;
    CStatic m_CStaticAktrufzeit;
    CString m_CAktrufzeit;
    CString m_CApo;
    CString m_CBemerkung;
    CString m_CDatum;
    CString m_CKndklasse;
    CString m_CKurzwahl;
    CString m_CName;
    CString m_Cort;
    CString m_CPlz;
    CString m_CPrio;
    CString m_CRr;
    CString m_CRrnr;
    CString m_CRufart;
    CString m_CRufzeit;
    CString m_CTelnr;
    CString m_CZeit;
    CString m_CIdfnr;
    BOOL    m_CApobelegt;
    CString m_CAnrufart;
    CString m_CZuerledigen;
    CString m_CBearbeitet;
    CString m_CGeloescht;
    BOOL    m_bNotFound;
    short   m_sVzNr;
    long    m_KndNr;
    CString m_CPool;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    int  SelectKunde(long IdfNr);                   // DBabfrage Kunde
    int  SelectAnruf(long IdfNr, long RufZeit);
    int  InsertServer(CDPlanTagUpd* d);
    int  UpdateServer(int Stat, int Prio, CString csOldTime);
    int  DeleteServer(int Stat, int delStat, CString Bemerkung);
    void SetRufPlanData(CRUFPTAG* d);
    void CheckCallTime(long callTime, long timeLeft, long timeRight, UINT uiStringId);
    void ShowRecord(long lUrzeit = 0, const char* spText = NULL);
    long GetServerTime();

    virtual BOOL OnInitDialog();
    afx_msg void OnButtonAendern();
    afx_msg void OnButtonHistorie();
    afx_msg void OnButtonHinzufuegen();
    afx_msg void OnButtonKeinauftrag();
    afx_msg void OnButtonKndinf();
    afx_msg void OnButtonKndkontakt();
    afx_msg void OnButtonLoeschen();
    afx_msg void OnButtonAuftragverschieben();
    virtual void OnOK();
    afx_msg void OnParaauftragoeffnen();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDPlanTagVer dialog

class CDPlanTagVer : public CDialogMultiLang
{
// Construction
public:
    CDPlanTagVer(CWnd* pParent = NULL);   // standard constructor
    int CheckMaxTimeMovement();
    int SetTimeToNewTime(int iMin);

    enum { IDD = IDD_AE_ANRUFPLAN_VER };
    CEdit   m_CEditNeuerufzeit;
    CStatic m_CStaticRufzeit;
    CEdit   m_CEditBemerkung;
    CStatic m_CStaticAktanrufzeit;
    CString m_CAktanrufzeit;
    CString m_CBemerkung;
    CString m_CRufzeit;
    CString m_CIdfnr;
    CString m_CNeuerufzeit;
    short m_sVzNr;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    CString m_scAktrufzeit;

    int NoRadioSet();
    int CheckSetRadio();
    int UpdateServer(CString csOldTime);
    int GetStatusVerbindung();

    virtual void OnOK();
    virtual BOOL OnInitDialog();
    afx_msg void OnRadio10();
    afx_msg void OnRadio11();
    afx_msg void OnRadio12();
    afx_msg void OnRadio13();
    afx_msg void OnRadio14();
    afx_msg void OnChangeEditNeuerufzeit();

    DECLARE_MESSAGE_MAP()
};
