#pragma once
#include <promoinfo.h>

//Definition der Tabellenbreite und der Ueberschriften
#define COL_PROMOLIST_MENGE         0
#define COL_PROMOLIST_RABATT        1
#define COL_PROMOLIST_WERT          2
#define COL_PROMOLIST_ART           3
#define COL_PROMOLIST_ZZ            4
#define COL_PROMOLIST_VON           5
#define COL_PROMOLIST_BIS           6
#define COL_PROMOLIST_PROMOTION     7
#define COL_PROMOLIST_PROMOTYP      8
#define COL_PROMOLIST_PROMONO       9
#define COL_PROMOLIST_QUOTA         10
#define COL_PROMOLIST_MIN           11
#define COL_PROMOLIST_REST          12
#define COL_PROMOLIST_PZN           13
#define COL_PROMOLIST_EINHEIT       14
#define COL_PROMOLIST_ARTIKELNAME   15
#define NUM_PROMOLIST_COLUMNS       16

// CDViewRabs-Dialogfeld

class CDViewRabs : public CDialogMultiLang
{
    DECLARE_DYNAMIC(CDViewRabs)

public:
    CDViewRabs(CWnd* pParent = NULL);   // Standardkonstruktor
    CDViewRabs(CView* pWview);
    BOOL Create();
    virtual ~CDViewRabs();
    void GetPage();
    void GetRabs(long qty);
    void RepositionWindow();

    enum { IDD = IDD_AE_VIEW_RAB };
    CListCtrl m_List1;
    CDISCOUNTANZ m_Discount;    //neue Rabatte
    typedef struct PROMOLIST
    {
        discountanzS anz;
        short promotyp;
        char promoname[31];
    } spromolist;
    vector<spromolist> m_pldisc; // pointer to class list
    vector <spromolist>::iterator m_itdisc;
    short m_sFilialnr;
    long m_ArtikelNr;
    long m_lKndNr;
    int m_iFound;
    int m_iBasis;
    short m_sPreistyp;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    virtual BOOL OnInitDialog();
    virtual void OnCancel();
    afx_msg void OnDestroy();
    DECLARE_MESSAGE_MAP()

private:
    CView* m_pView;
    void FillListBox();
    CPROMOQUOTACHECK m_check;
};
