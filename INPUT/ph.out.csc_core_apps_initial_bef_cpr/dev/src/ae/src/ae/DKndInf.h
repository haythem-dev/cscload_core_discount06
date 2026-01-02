#pragma once
// dkndinf.h : header file
//

#include "SalesBindingListCtrl.h"
#include <vector>
#include <atltime.h>
#include <customer.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CKndInf

class CKndInf
{
public:
    CKndInf()                       { m_IdfNr = -1; m_KndNr = -1; m_VzNr = AeGetApp()->VzNr(); }
    CKndInf(long IdfNr)             { m_IdfNr = IdfNr; }
    CKndInf(long KndNr, short Vz)   { m_KndNr = KndNr; m_VzNr = Vz; }
    void SetIdfNr(long IdfNr)       { m_IdfNr = IdfNr; }
    void SetKndNr(long KndNr)       { m_KndNr = KndNr; }
    void SetKndVz(short VzNr)       { m_VzNr = VzNr; }
    long GetIdfNr()                 { return m_IdfNr; }
    long GetKndNr()                 { return m_KndNr; }
    short GetVzNr()                 { return m_VzNr; }
    int DoModal();                  //Ausgabe der Artikelinformation, bei IdfNr == -1 wird
                                    //zunächst ein Dialog zur Artikeldefinition angezeigt
protected:
    long m_IdfNr;
    long m_KndNr;
    long m_MainNr; //Haupt-IDF bei Kette
    BOOL m_KzAeGesperrt;
    short m_VzNr;
    BOOL m_bKtoExist; //Eintrage in Rabattkonto vorhanden
};


/////////////////////////////////////////////////////////////////////////////
// CPSKndInf

class CPSKndInf : public CPropertySheetMultiLang
{
    DECLARE_DYNAMIC(CPSKndInf)

// Construction
public:
    CPSKndInf(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
    CPSKndInf(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

    virtual ~CPSKndInf();

    int m_KettePage;

protected:
    virtual BOOL OnInitDialog();
    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDKndInf1 dialog

class CDKndInf1 : public CPropertyPageMultiLang
{
    DECLARE_DYNCREATE(CDKndInf1)

// Construction
public:
    CDKndInf1();
    ~CDKndInf1();
    virtual BOOL OnSetActive();
    BOOL m_init;
    long m_IdfNr;
    long m_KndNr;
    BOOL m_KzAeGesperrt;
    short m_VzNr;
    char m_Schwerpunkt1[1+1];
    char m_Schwerpunkt2[1+1];
    char m_Schwerpunkt3[1+1];
    char m_Schwerpunkt4[1+1];
    char m_Schwerpunkt5[1+1];
    char m_Anrufgenerell[1+1];
    char m_AuftragZusammen[1+1];
    char m_Kritisch[1+1];
    char m_Vipkunde[1+1];
    char m_Midas[1+1];
    char m_RetailPermit[1+1];
    char m_Etkdmerkmal1[16+1];
    char m_Etkdmerkmal2[16+1];
    TM   m_TMZeit;
    double m_dLog;
    short m_OrgFili;
    short m_sMailB2SR;
    short m_sMailCDB;
    double m_dLinefee;
    double m_dPackagefee;
    char m_cSendcollectivinvoice[2];
    bool m_bCall;

    enum { IDD = IDD_AE_KND_INF1 };
    CListBox m_ListInfo;
    CListBox m_ListVb;
    CListCtrl m_ListTour;
    CListCtrl m_ListRufe;
    CListCtrl m_ListAufarten;
    CString m_CApoName;
    CString m_CBasisNatrab;
    CString m_CDatumNeu;
    CString m_CEilGebuehr;
    CString m_CEilSperre;
    CString m_CIdfNummer;
    CString m_CImsKreis;
    CString m_CInfo;
    CString m_CInfoPhono;
    CString m_CInfoPhono2;
    CString m_CInfoPhono3;
    CString m_CInfoVersand;
    CString m_CInfoVersand2;
    CString m_CKundeName;
    CString m_CLfdUms;
    CString m_COffen1;
    CString m_COffen2;
    CString m_COrt;
    CString m_CPhonoMalus;
    CString m_CPlz;
    CString m_CStrasse;
    CString m_CTeleKw;
    CString m_CTeleNr;
    CString m_CTeleNrDafue;
    CString m_CTeleNr2;
    CString m_CUrlaub;
    CString m_CVb;
    CString m_CVb1;
    CString m_CVb2;
    CString m_CVersandKosten;
    CString m_CFaxNr;
    CString m_CVerbund;
    CString m_CDfuArt;
    CString m_CAbc;
    CString m_CEmail;
    CListCtrl m_ListEKGruppe;
    CString m_CLog;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnButtonMail();
    afx_msg void OnButtonCall();
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDKndInf2 dialog

class CDKndInf2 : public CPropertyPageMultiLang
{
    DECLARE_DYNCREATE(CDKndInf2)

// Construction
public:
    CDKndInf2();
    ~CDKndInf2();
    virtual BOOL OnSetActive( );
    BOOL m_init;
    long m_IdfNr;
    long m_KndNr;
    BOOL m_KzAeGesperrt;
    short m_VzNr;

    enum { IDD = IDD_AE_KND_INF2 };
    CString m_CApoName;
    CString m_CIdfNummer;
    CString m_CKundeName;
    CString m_COrt;
    CString m_CPlz;
    CString m_CStrasse;
    CString m_CTeleKw;
    CString m_CTeleNr;
    CString m_CUmsatz;
    CString m_CWert1;
    CString m_CWert10;
    CString m_CWert11;
    CString m_CWert12;
    CString m_CWert2;
    CString m_CWert3;
    CString m_CWert4;
    CString m_CWert5;
    CString m_CWert6;
    CString m_CWert7;
    CString m_CWert8;
    CString m_CWert9;
    CString m_CMonat1;
    CString m_CMonat10;
    CString m_CMonat11;
    CString m_CMonat12;
    CString m_CMonat2;
    CString m_CMonat3;
    CString m_CMonat4;
    CString m_CMonat5;
    CString m_CMonat6;
    CString m_CMonat7;
    CString m_CMonat8;
    CString m_CMonat9;
    CString m_CAbc;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    int ReadPos();
    long hoch[12];
    int m_anz;
    double m_max;
    CString* m_pstr[12];
    CString* m_pmon[12];
    vector <KNDMONUMS> lMonUms;
    vector <KNDMONUMS>::iterator it;

    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg void OnButtonAuftr();
    afx_msg void OnButtonUmsAe();
    afx_msg void OnButtonUmsGp();
    afx_msg void OnButtonUmsNn();
    afx_msg void OnButtonZeil();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    DECLARE_MESSAGE_MAP()
};


// CDKndInf3-Dialogfeld

class CDKndInf3 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDKndInf3)

public:
    CDKndInf3();
    virtual ~CDKndInf3();

    enum { IDD = IDD_AE_KND_INF3 };
    BOOL m_init;
    long m_KndNr;
    short m_VzNr;
    CEdit m_edit_BTM;
    CEdit m_edit_Dispo;
    CEdit m_edit_Doku;
    CEdit m_edit_Kippzeit;
    CEdit m_edit_Lager;
    CEdit m_edti_Eil;
    CEdit m_edit_Tour;
    CEdit m_edit_Filinf;
    CEdit m_edit_Filinf2;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnSetActive();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    DECLARE_MESSAGE_MAP()
};


// CDKndInf4-Dialogfeld

class CDKndInf4 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDKndInf4)

public:
    struct TOURWOCHE_TOUR
    { //Struktur für die Anzeige der Toureninformationen
        int     iWochenTag;     //Wochentag
        CString CStrTourID;     //ID der Tour
        CString CStrConsTime1;  //Zusammenführungszeit 1
        CString CStrConsTime2;  //Zusammenführungszeit 2
        CString CStrConsTime3;  //Zusammenführungszeit 3
        CString CStrVBTour;     //Verbundtour
        CString CStrBTM;        //mit BTM
        CString CStrKK;         //mit Kuehlkette
        CString CStrK08;        //mit Kuehl unter 8 Grad
        CString CStrK20;        //mit Kuehl unter 20 Grad
        CString CStrRT;         //mit Tour fuer Retouren
        CString CStrTour;       //Tour unaufbereitet
        CString CStrAArt;       //Auftragsart
        CString CStrPsycho;		//Transport exclusion psychotropics

        void SetConsTime(int iPosition, long lConsTime)
        {   //Ermöglicht das Setzen der Constime in Abhängigkeit von der Anzahl der Treffer
            switch (iPosition)
            {
            case 1:
                CStrConsTime1.Format("%ld", lConsTime);
                break;
            case 2:
                CStrConsTime2.Format("%ld", lConsTime);
                break;
            case 3:
                CStrConsTime3.Format("%ld", lConsTime);
                break;
            default:
                break;
            }
        }

        void SetConsTimeUnavailabe(int iPosition)
        {   //Ermöglicht das Befüllen der Constime mit Dummywerten
            switch (iPosition)
            {
            case 1:
                CStrConsTime1 = CResString::ex().getStrTblText(AETXT_CONS_TIME_UNAVAILABLE);
                break;
            case 2:
                CStrConsTime2 = CResString::ex().getStrTblText(AETXT_CONS_TIME_UNAVAILABLE);
                break;
            case 3:
                CStrConsTime3 = CResString::ex().getStrTblText(AETXT_CONS_TIME_UNAVAILABLE);
                break;
            default:
                break;
            }
        }
    };

public:
                            CDKndInf4(CWnd* pParent = NULL);   // Standardkonstruktor
    virtual                 ~CDKndInf4();

    enum { IDD = IDD_AE_KND_INF4 };
    CListCtrl m_ListTourenMO; //Listcontrol für die Touren am MO
    CListCtrl m_ListTourenDI; //Listcontrol für die Touren am DI
    CListCtrl m_ListTourenMI; //Listcontrol für die Touren am MI
    CListCtrl m_ListTourenDO; //Listcontrol für die Touren am DO
    CListCtrl m_ListTourenFR; //Listcontrol für die Touren am FR
    CListCtrl m_ListTourenSA; //Listcontrol für die Touren am SA
    CListCtrl m_ListTourenSO; //Listcontrol für die Touren am SO
    long                    m_KndNr; //Kundendaten
    short                   m_VzNr; //Kundendaten
    long                    m_IdfNr; //Kundendaten
    CString                 m_CApoName; //Kundendaten
    CString                 m_CKundeName; //Kundendaten
    CString                 m_CAbc; //Kundendaten
    CString                 m_CIdfNummer; //Kundendaten
    CString                 m_COrt; //Kundendaten
    CString                 m_CPlz; //Kundendaten
    CString                 m_CStrasse; //Kundendaten
    CString                 m_CTeleKw; //Kundendaten
    CString                 m_CTeleNr; //Kundendaten
    CString                 CStrMain; //Hauptbesellzeit
    CString                 CStrTill; //Besellzeitende

protected:
    BOOL                    m_init;
    vector<TOURWOCHE_TOUR>* m_pvecTourWocheTour; //Vektor zum Puffern der gefundenen Einträge
    BOOL                    m_binitMO;//Schalter ist true, wenn Treffer für den MO gefunden wurden
    BOOL                    m_binitDI;//Schalter ist true, wenn Treffer für den DI gefunden wurden
    BOOL                    m_binitMI;//Schalter ist true, wenn Treffer für den MI gefunden wurden
    BOOL                    m_binitDO;//Schalter ist true, wenn Treffer für den DO gefunden wurden
    BOOL                    m_binitFR;//Schalter ist true, wenn Treffer für den FR gefunden wurden
    BOOL                    m_binitSA;//Schalter ist true, wenn Treffer für den SA gefunden wurden
    BOOL                    m_binitSO;//Schalter ist true, wenn Treffer für den SO gefunden wurden

    long                    m_lStdMinutenConsTime; //Falls keine Auftragszusammenführungszeit gefunden wird, wird diese Anzahl Minuten von der Tourzeit abgezogen

    void                    setDialogTourWeekDayEnabled(const int iWeekDay);//setzt die Schalter m_binitMO - m_binitSO abhängig vom Wochentag auf true
                                                                               //in Abhängigkeit vom Wochentag
    BOOL                    initListBox(const int iWeekDay);//Initialisiert das dem Wochentag zugeordnete Listcontrol
    BOOL                    getInitStateforTagesTyp(const int iWeekDay) const;//Liefert den Wert des Schalters, der dem Wochentag zugeordnet ist (m_binitMO - m_binitSO)
    CWnd*                   getDialogforTagesTyp(const int iWeekDay) const;//Liefert das dem Wochentag zugeordnete Listcontrol als Pointer zurück

protected:
    virtual void            DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL            OnInitDialog();
    virtual BOOL            OnSetActive();
    DECLARE_MESSAGE_MAP()
};


// CDKndInf5-Dialogfeld

class CDKndInf5 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDKndInf5)

public:
    CDKndInf5();
    virtual ~CDKndInf5();

// Dialogfelddaten
    enum { IDD = IDD_AE_KUNDE_INF5 };
    long                    m_KndNr; //Kundendaten
    short                   m_VzNr; //Kundendaten
    CString m_CKundeName;
    CString m_CApoName;
    CString m_CPlz;
    CString m_COrt;
    CString m_CStrasse;
    CString m_CIdfNummer;
    CString m_CAbc;
    CString m_CTeleNr;
    CString m_CTeleKw;
    CListCtrl m_LstCtrl;
    CListCtrl m_LstCtrlDebt;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();
    DECLARE_MESSAGE_MAP()

    BOOL m_init;
    void FillKL(CKREDITLIMIT* pKL);
};


// CDKndInf6-Dialogfeld

class CDKndInf6 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDKndInf6)

public:
    CDKndInf6();
    virtual ~CDKndInf6();

    enum { IDD = IDD_AE_KND_INF6 };
    long                    m_KndNr; //Kundendaten
    long                    m_MainNr; //Haupt-IDF bei Kette
    short                   m_VzNr; //Kundendaten
    CString m_CKundeName;
    CString m_CApoName;
    CString m_CPlz;
    CString m_COrt;
    CString m_CStrasse;
    CString m_CIdfNummer;
    CString m_CAbc;
    CString m_CTeleNr;
    CString m_CTeleKw;
    CListCtrl m_LstCtrl1;
    CListCtrl m_LstCtrl2;

    afx_msg LRESULT OnHookFkt(WPARAM wParam, LPARAM lParam);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();
    DECLARE_MESSAGE_MAP()

    BOOL m_init;
};


// CDKndInf7-Dialogfeld

class CDKndInf7 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDKndInf7)

public:
    CDKndInf7();   // Standardkonstruktor
    virtual ~CDKndInf7();

    enum { IDD = IDD_AE_KND_INF7 };
    long                    m_KndNr; //Kundendaten
    long                    m_MainNr; //Haupt-IDF bei Kette
    short                   m_VzNr; //Kundendaten
    TM      m_TMZeit;
    CString m_CKundeName;
    CString m_CApoName;
    CString m_CPlz;
    CString m_COrt;
    CString m_CStrasse;
    CString m_CIdfNummer;
    CString m_CAbc;
    CString m_CTeleNr;
    CString m_CTeleKw;
    CListCtrl m_LstCtrl1;
    CListCtrl m_LstCtrl2;
    BOOL m_bKtoExist; //Eintrage in Rabattkonto vorhanden
    CDateTimeCtrl m_DT_Von;
    CDateTimeCtrl m_DT_Bis;
    CTime m_tVon;
    CTime m_tBis;

    void FillLists(long von, long bis);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();
    afx_msg void OnBnClickedButtonAnz();
    DECLARE_MESSAGE_MAP()

    BOOL m_init;

private:
    static bool FillList(CCSTDISCACC& disc, double& sum, CListCtrl& listCtrl);
};


// CDKndInf8-Dialogfeld

class CDKndInf8 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDKndInf8)

public:
    CDKndInf8();   // Standardkonstruktor
    virtual ~CDKndInf8();

    enum { IDD = IDD_AE_KND_INF8 };
    long                    m_KndNr; //Kundendaten
    short                   m_VzNr; //Kundendaten
    TM      m_TMZeit;
    CString m_CKundeName;
    CString m_CApoName;
    CString m_CPlz;
    CString m_COrt;
    CString m_CStrasse;
    CString m_CIdfNummer;
    CString m_CAbc;
    CString m_CTeleNr;
    CString m_CTeleKw;
    CEdit m_edit_sum_offen;
    CEdit m_edit_sum_due;
    CEdit m_edit_sum_overdue;
    CEdit m_edit_sum_offen_zz;
    CEdit m_edit_sum_due_zz;
    CEdit m_edit_sum_overdue_zz;
    CEdit m_edit_sum_offen_cash;
    CEdit m_edit_sum_due_cash;
    CEdit m_edit_sum_overdue_cash;
    CListCtrl m_LstCtrl1;
    CListCtrl m_LstCtrl2;
    CListCtrl m_LstCtrl3;

    BOOL WriteList1(CStringArray& s);
    BOOL WriteList2(CStringArray& s);
    BOOL WriteList3(CStringArray& s);

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    afx_msg void OnButtonOpen();
    afx_msg void OnButtonDue();
    afx_msg void OnButtonOverdue();

    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();
    DECLARE_MESSAGE_MAP()

    BOOL m_init;
};


// CDKndInf9-Dialogfeld

class CDKndInf9 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDKndInf9)

public:
    CDKndInf9();
    virtual ~CDKndInf9();

    enum { IDD = IDD_AE_KND_INF9 };
    long    m_KndNr; //Kundendaten
    short   m_VzNr; //Kundendaten
    CString m_CKundeName;
    CString m_CApoName;
    CString m_CPlz;
    CString m_COrt;
    CString m_CStrasse;
    CString m_CIdfNummer;
    CString m_CAbc;
    CString m_CTeleNr;
    CString m_CTeleKw;
    CListCtrl m_LstCtrl1;

protected:
    BOOL m_init;

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();
    DECLARE_MESSAGE_MAP()
};


// CDKndInf10-Dialogfeld

class CDKndInf10 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDKndInf10)

public:
    CDKndInf10();
    virtual ~CDKndInf10();

    enum { IDD = IDD_AE_KND_INF10 };
    long    m_KndNr; //Kundendaten
    short   m_VzNr; //Kundendaten
    CString m_CKundeName;
    CString m_CApoName;
    CString m_CPlz;
    CString m_COrt;
    CString m_CStrasse;
    CString m_CIdfNummer;
    CString m_CAbc;
    CString m_CTeleNr;
    CString m_CTeleKw;
    CListCtrl m_LstCtrlAArt;
    CListCtrl m_LstCtrlOrders;
    CListCtrl m_LstCtrlBFToday;
    CListCtrl m_LstCtrlVDat;

protected:
    BOOL m_init;

    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    DECLARE_MESSAGE_MAP()
};


// CDKndInf10-Dialogfeld

class CDKndInf11 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDKndInf11)

public:
    CDKndInf11();
    virtual ~CDKndInf11();

    enum { IDD = IDD_AE_KND_INF11 };
    long    m_KndNr; //Kundendaten
    short   m_VzNr; //Kundendaten
    CString m_CKundeName;
    CString m_CApoName;
    CString m_CPlz;
    CString m_COrt;
    CString m_CStrasse;
    CString m_CIdfNummer;
    CString m_CAbc;
    CString m_CTeleNr;
    CString m_CTeleKw;

protected:
    BOOL m_init;

    virtual BOOL OnInitDialog();
    virtual BOOL OnSetActive();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    DECLARE_MESSAGE_MAP()

private:
    CSalesBindingListCtrl m_LstCtrlBindungen;
};
