#pragma once

#include "ArtInfData.h"
#include "SalesBindingListCtrl.h"
#include <artikel.h>
#include <customer.h>
#include <articleomg.h>

// dartinf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDArtInf


class CDArtInf
{
public:
    CDArtInf();
    CDArtInf(long ArtikelNr);

    void SetArtNr(long ArtikelNr) { m_ArtikelNr = ArtikelNr; }
    void SetKndNr(long KndNr) { m_lKndNr = KndNr; }
    void SetFilialNr(short FilialNr) { m_FilialNr = FilialNr; }
    void SetOrgFilialNr(short OrgFilialNr) { m_OrgFilialNr = OrgFilialNr; }
    short GetOrgFilialNr()          { return m_OrgFilialNr; }
    short GetFilialNr()             { return m_FilialNr; }
    long GetArtNr()                 { return m_ArtikelNr; }
    int DoModal();                  //Ausgabe der Artikelinformation, bei ArtNr == -1 wird
                                    //zunächst ein Dialog zur Artikeldefinition angezeigt
    CString m_CBemerkungKond;       //Erscheint auf dem ersten Dialog
    BOOL m_bNoPriceGroup2;          //Unterdrückt die Rabattgruppe 2 in der Auftragsannahme
    BOOL m_bNoPriceGroup3;          //Unterdrückt die Rabattgruppe 3 in der Auftragsannahme
    BOOL m_bAufnahme;               //aus eröffnetem Auftrag
    short m_sImportArticle;         //Select mit oder ohne Importartikel
    short m_sPreistyp;              //Preistyp Bulgarien
    CDISCOUNTANZ m_Discount;        //neue Rabatte
    BOOL m_bNoStellerTest;          //nicht pruefen auf Steller (kommt aus Stelleranzeige)

private:
    long m_ArtikelNr;
    long m_lKndNr;
    short m_FilialNr;
    short m_OrgFilialNr;
    long m_lQuota;
    long m_lKumqty;
    long m_lRest;
    bool m_bCheck;
    int m_iBasis;
    SArtInfData m_ArtInfData;
    SArtInfPackageData m_ArtInfPackageData;
    SArtInfIbtData m_ArtInfIbtData;
    SArtInfDiscountData m_ArtInfDiscountData;

    void InitData();
};

/////////////////////////////////////////////////////////////////////////////
// CPSArtInf

class CPSArtInf : public CPropertySheetMultiLang
{
    DECLARE_DYNAMIC(CPSArtInf)

// Construction
public:
    CPSArtInf(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
    CPSArtInf(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
    virtual ~CPSArtInf();

protected:
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CDArtInf1 dialog

class CDArtInf1 : public CPropertyPageMultiLang
{
    DECLARE_DYNCREATE(CDArtInf1)

// Construction
public:
    CDArtInf1(SArtInfData* pArtInfData, SArtInfIbtData* pArtInfIbtData, SArtInfDiscountData* pArtInfDiscountData);
    ~CDArtInf1();

    virtual BOOL OnSetActive();

    double m_dAGP;
    short m_Taxlevel;
    short m_TextkeyHosp;
    long m_NatraStaffelNr;
    char m_Etartklasse1[16+1];
    char m_Etartschalter1[16+1];
    char m_Etartschalter2[16+1];
    char m_Etartschalter3[16+1];
    char m_Etartschalter4[16+1];
    char m_Etartschalter5[16+1];
    char m_CArtikelaktiv[1+1];
    char m_CPositivliste[1+1];
    char m_cChargenArtikel[1+1];
    char m_CPrisoart;
    bool m_bPsycho;
    bool m_bTFG;
    bool m_bKontingent_PPE;
    bool m_bMedizinProdukt;
    bool m_bKuehlMittel;
    bool m_bKuehlUltra;
    BOOL m_bNoPriceGroup2;          //Unterdrückt die Rabattgruppe 2 in der Auftragsannahme
    BOOL m_bNoPriceGroup3;          //Unterdrückt die Rabattgruppe 3 in der Auftragsannahme
    short m_sImportarticle;
    char m_CWafotyp[1 + 1];
    long m_lDatumlieferbarab;

    CString m_CArtBest;
    CString m_CLagOrt;
    CString m_CStation;
    CString m_CVerfall;
    CString m_CAep;
    CString m_CAvp;
    CString m_CGep;
    CString m_CBemerkung;
    CString m_CProz;
    CString m_CAlter;
    CString m_CKKCode;
    CString m_CHC;
    CString m_CArtText;
    CString m_CKontigent;
    CString m_CReserviert;
    CString m_CMwst;
    CString m_CAGP;

protected:
    CDArtInf1();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnBnClickedButtonArtikelkonto();

    enum { IDD = IDD_AE_ART_INF1 };

    DECLARE_MESSAGE_MAP()

private:
    bool m_init;
    SArtInfData* m_pArtInfData;
    SArtInfIbtData* m_pArtInfIbtData;
    SArtInfDiscountData* m_pArtInfDiscountData;
    CListBox  m_ListKz;
    CListCtrl m_ListNatra;
    CListCtrl m_ListNetto;
    CString m_CLPPR;
    CListCtrl m_ListCharge;
    CStatic m_Icon[10];

    void ShowIcon(CStatic& icon, UINT nIDResource);
};

/////////////////////////////////////////////////////////////////////////////
// CDArtInf2 dialog

class CDArtInf2 : public CPropertyPageMultiLang
{
    DECLARE_DYNCREATE(CDArtInf2)

// Construction
public:
    CDArtInf2(SArtInfData* pArtInfData, SArtInfPackageData* pArtInfPackageData);
    ~CDArtInf2();

    virtual BOOL OnSetActive();

protected:
    CDArtInf2();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    enum { IDD = IDD_AE_ART_INF2 };

    DECLARE_MESSAGE_MAP()

private:
    bool m_init;
    SArtInfData* m_pArtInfData;
    SArtInfPackageData* m_pArtInfPackageData;
    CListCtrl m_ListLagOrt;
};

/////////////////////////////////////////////////////////////////////////////
// CDArtInf3 dialog

class CDArtInf3 : public CPropertyPageMultiLang
{
    DECLARE_DYNCREATE(CDArtInf3)

// Construction
public:
    CDArtInf3(SArtInfData* pArtInfData);
    ~CDArtInf3();

    virtual BOOL OnSetActive();

    short m_VzNr;
    long m_lHerstNr;

protected:
    CDArtInf3();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    afx_msg void OnButtonInfoliste();
    afx_msg void OnButtonWissensDB();
    afx_msg void OnButtonInternet();
    afx_msg void OnButtonGoogle();
    afx_msg void OnButtonEMail();

    enum { IDD = IDD_AE_ART_INF3 };

    DECLARE_MESSAGE_MAP()

private:
    bool m_init;
    SArtInfData* m_pArtInfData;
    CListCtrl m_CListOffBest;
    CString m_CHomePage;
    CString m_CEmail;
};

/////////////////////////////////////////////////////////////////////////////
// CDARTINF4 dialog

class CDArtInf4 : public CPropertyPageMultiLang
{
    DECLARE_DYNCREATE(CDArtInf4)

// Construction
public:
    CDArtInf4(SArtInfData* pArtInfData, SArtInfIbtData* pArtInfIbtData);
    ~CDArtInf4();

    virtual BOOL OnSetActive();

    char m_CPrisoart;
    long m_lRest;
    bool m_bCheck;

protected:
    CDArtInf4();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    enum { IDD = IDD_AE_ART_INF4 };

    DECLARE_MESSAGE_MAP()

private:
    bool m_init;
    SArtInfData* m_pArtInfData;
    SArtInfIbtData* m_pArtInfIbtData;
    CListCtrl m_ListStockNotActiveIbt;
    CListCtrl m_ListStockDailyStart;
    CListCtrl m_ListStockActive;

    bool GetIbtType(CString& ibtType, const short sVBTyp);
    void GetIbtType(CString& ibtType, UINT uiTextIfEmpty, UINT uiTextElse);

    bool InsertStockActive(CStringArray& s);
    bool InsertStockNotActiveIbt(CStringArray& s);
    bool InsertStockDailyStart(CStringArray& s);

    CString UpdateStock(long& lStock);
};

// CDArtInf5-Dialogfeld

class CDArtInf5 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDArtInf5)

public:
    CDArtInf5(SArtInfData* pArtInfData, SArtInfDiscountData* pArtInfDiscountData);
    virtual ~CDArtInf5();

    virtual BOOL OnSetActive();

    double m_dAEP;
    double m_dGROSSO;
    int m_iBasis;
    double m_dAGP;
    double m_dGEP;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    enum { IDD = IDD_AE_ART_INF5 };

    DECLARE_MESSAGE_MAP()

private:
    bool m_init;
    SArtInfData* m_pArtInfData;
    SArtInfDiscountData* m_pArtInfDiscountData;
    CListCtrl m_List1;
    CListCtrl m_ListOMG;
    CImageList m_ImageSmall;
};

// CDArtInf6-Dialogfeld

class CDArtInf6 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDArtInf6)

public:
    CDArtInf6(SArtInfData* pArtInfData);
    virtual ~CDArtInf6();

    virtual BOOL OnSetActive();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

    enum { IDD = IDD_AE_ART_INF6 };

    DECLARE_MESSAGE_MAP()

private:
    bool m_init;
    bool m_first;
    SArtInfData* m_pArtInfData;
    CString m_CText;
    CEdit m_Edit_Text;
};

// CDArtInf7-Dialogfeld

class CDArtInf7 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDArtInf7)

public:
    CDArtInf7(SArtInfData* pArtInfData);
    virtual ~CDArtInf7();

    virtual BOOL OnSetActive();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    enum { IDD = IDD_AE_ART_INF7 };

    DECLARE_MESSAGE_MAP()

private:
    bool m_init;
    SArtInfData* m_pArtInfData;
    CListCtrl m_ListReserve;

    bool AddStockReserveToListBox(short reservType, UINT uiStringId);
};

// CDArtInf8-Dialogfeld

class CDArtInf8 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDArtInf8)

public:
    CDArtInf8(SArtInfData* pArtInfData);
    virtual ~CDArtInf8();

    virtual BOOL OnSetActive();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    enum { IDD = IDD_AE_ART_INF8 };

    DECLARE_MESSAGE_MAP()

private:
    bool m_init;
    SArtInfData* m_pArtInfData;
    CListCtrl m_ListLPPR;
};

// CDArtInf9-Dialogfeld

class CDArtInf9 : public CPropertyPageMultiLang
{
    DECLARE_DYNAMIC(CDArtInf9)

public:
    CDArtInf9(SArtInfData* pArtInfData);
    virtual ~CDArtInf9();

    virtual BOOL OnSetActive();

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    enum { IDD = IDD_AE_ART_INF9 };

    DECLARE_MESSAGE_MAP()

private:
    bool m_init;
    SArtInfData* m_pArtInfData;
    CSalesBindingListCtrl m_LstCtrlBindungen;
    CSalesBindingListCtrl m_LstCtrlBindungenCst;
};
