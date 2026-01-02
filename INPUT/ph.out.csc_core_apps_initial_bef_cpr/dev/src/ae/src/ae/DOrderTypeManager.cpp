// DOrderTypeManager.cpp : implementation file
//

#include "stdafx.h"
#include <auftragsart.h>
#include "DReservationConfig.h"
#include <ordertypereservationconfig.h>
#include <ordertypereservationconfigcpg.h>
#include "DOrderTypeManager.h"

//Definition der Tabellenbreite und der Ueberschriften

#define COL_CONFIG_KB           0
#define COL_CONFIG_NAME         1
#define COL_CONFIG_RESERVTYP    2
#define COL_CONFIG_PRIORITY     3
#define COL_CONFIG_ID           4
#define COL_CONFIG_STOCKONLY    5
#define COL_CONFIG_FREEFIRST    6
#define NUM_COLUMNS_CONFIG      7

static COLUMNS_TYPES ColumnsConfig[] =
{
    COL_CONFIG_KB,        "",  35, LVCFMT_LEFT,
    COL_CONFIG_NAME,      "", 120, LVCFMT_LEFT,
    COL_CONFIG_RESERVTYP, "",  35, LVCFMT_LEFT,
    COL_CONFIG_PRIORITY,  "",  35, LVCFMT_LEFT,
    COL_CONFIG_ID,        "",   0, LVCFMT_LEFT,
    COL_CONFIG_STOCKONLY, "",   0, LVCFMT_LEFT,
    COL_CONFIG_FREEFIRST, "",   0, LVCFMT_LEFT,
    -1,                   "",   0, 0
};


// CDOrderTypeManager dialog

IMPLEMENT_DYNAMIC(CDOrderTypeManager, CDialog)

CDOrderTypeManager::CDOrderTypeManager(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(IDD_AE_ORDERTYPE_MANAGER, pParent)
    , m_bNatra(FALSE)
    , m_bNetto(FALSE)
    , m_bBild(FALSE)
    , m_bDafue(FALSE)
    , m_bHand(FALSE)
    , m_bDiscount(FALSE)
    , m_bStandard(FALSE)
    , m_bMuss(FALSE)
    , m_bFreePrice(FALSE)
    , m_bAufCons(FALSE)
    , m_bAufNachl(FALSE)
    , m_bNoQuota(FALSE)
    , m_bDeferOrder(FALSE)
    , m_bNoPart(FALSE)
    , m_bNoDD(FALSE)
    , m_bOnlyEH(FALSE)
    , m_bNoPromo(FALSE)
    , m_bDefaultKennung(FALSE)
    , m_bIVC(FALSE)
    , m_bOrgInvoice(FALSE)
    , m_bAllowDesired(FALSE)
    , m_bAllowFixed(FALSE)
    , m_bForbidChange(FALSE)
    , m_bUpdate(FALSE)
    , m_bGlobal(FALSE)
    , m_bConsultationNeeded(FALSE)
    , m_bNoLinefee(FALSE)
    , m_bNoPackagefee(FALSE)
    , m_bMustHeadline(FALSE)
    , m_bStockreservation(FALSE)
{
    m_CBezeichnung = _T("");
    m_CKBst = _T("");
    m_sSaleCenterNo = 0;
}

CDOrderTypeManager::~CDOrderTypeManager()
{
}

void CDOrderTypeManager::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_AART, m_CTabCtrlOrderTypeManager);
    DDX_Control(pDX, IDC_EDIT_KBST, m_EditKBst);
    DDX_Text(pDX, IDC_EDIT_KBST, m_CKBst);
}


BEGIN_MESSAGE_MAP(CDOrderTypeManager, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_KBST, OnChangeEditKbst)
END_MESSAGE_MAP()


// CDOrderTypeManager message handlers
// DOrderTypeManager.cpp : implementation file
//

//----------------------------------------------------------------------------//
//--- CDOrderTypeManager message handlers (ClassWizard) -------------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CDOrderTypeManager::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    if (!m_CKBst.IsEmpty())
    {
        GetDlgItem(IDC_EDIT_KBST)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_KB)->EnableWindow(FALSE);
        ppString cBez;
        CAUFTRAGSART aart;
        int rc;
        char error_msg[81];
        aart.SetBranchno(m_sSaleCenterNo);
        aart.SetKdauftragart(m_CKBst);

        rc = ::ServerNr(PIPE_AE_SRV, AasrvSelCscOrderType, (void *)&aart.s, AUFTRAGSART_BES, AUFTRAGSART_ANZ, error_msg);
        if (rc < 0)
        {
            FehlerBehandlung(rc, error_msg);
            return FALSE;
        }

        // char(1)
        if (aart.GetSkdauftragartnatra() == '1') m_bNatra = TRUE;
        if (aart.GetSkdauftragartnetto() == '1') m_bNetto = TRUE;
        if (aart.GetSbildschirm() == '1') m_bBild = TRUE;
        if (aart.GetSdafue() == '1') m_bDafue = TRUE;
        if (aart.GetDisinkindenterable() == '1') m_bHand = TRUE;
        if (aart.GetSdiscountable() == '1') m_bDiscount = TRUE;
        if (aart.GetSstandard() == '1') m_bStandard = TRUE;
        if (aart.GetSmustsuborder() == '1') m_bMuss = TRUE;
        if (aart.GetSfreeprice() == '1') m_bFreePrice = TRUE;
        if (aart.GetSordercons() == '1') m_bAufCons = TRUE;
        if (aart.GetSrestdel() == '1') m_bAufNachl = TRUE;
        if (aart.GetSnoquota() == '1') m_bNoQuota = TRUE;
        if (aart.GetSdeferorder() == '1') m_bDeferOrder = TRUE;
        if (aart.GetSnopartqty() == '1') m_bNoPart = TRUE;
        if (aart.GetSnodd() == '1') m_bNoDD = TRUE;
        if (aart.GetSonlyeh() == '1') m_bOnlyEH = TRUE;
        if (aart.GetSglobal() == '1') m_bGlobal = TRUE;
        // short
        if (aart.GetSnopromotions() == 1) m_bNoPromo = TRUE;
        if (aart.GetSdefaultkennung() == 1) m_bDefaultKennung = TRUE;
        if (aart.GetSivcvoucherno() == 1) m_bIVC = TRUE;
        if (aart.GetSoriginalinvoiceno() == 1) m_bOrgInvoice = TRUE;
        if (aart.GetAllowdesiredbatch() == 1) m_bAllowDesired = TRUE;
        if (aart.GetAllowfixedbatch() == 1) m_bAllowFixed = TRUE;
        if (aart.GetForbiduserchange() == 1) m_bForbidChange = TRUE;
        if (aart.GetSconsultationneeded() == 1) m_bConsultationNeeded = TRUE;
        if (aart.GetSnolinefee() == 1) m_bNoLinefee = TRUE;
        if (aart.GetSnopackagefee() == 1) m_bNoPackagefee = TRUE;
        if (aart.GetSmustheadline() == 1) m_bMustHeadline = TRUE;
        if (aart.GetStockreservation() == 1) m_bStockreservation = TRUE;

        m_CBezeichnung = aart.GetBezeichnung(cBez);
    }

    m_PageDOrderTypeManager1.m_pFather = this;
    m_PageDOrderTypeManager2.m_pFather = this;
    m_PageDOrderTypeManager3.m_pFather = this;
    m_PageDOrderTypeManager4.m_pFather = this;
    m_PageDOrderTypeManager5.m_pFather = this;
    m_PageDOrderTypeManager6.m_pFather = this;

    //add pages
    m_CTabCtrlOrderTypeManager.AddPage(&m_PageDOrderTypeManager1);
    m_CTabCtrlOrderTypeManager.AddPage(&m_PageDOrderTypeManager2);
    m_CTabCtrlOrderTypeManager.AddPage(&m_PageDOrderTypeManager3);
    m_CTabCtrlOrderTypeManager.AddPage(&m_PageDOrderTypeManager4);
    m_CTabCtrlOrderTypeManager.AddPage(&m_PageDOrderTypeManager5);
    if (AeGetApp()->IsFR() || AeGetApp()->IsDE() || AeGetApp()->IsAT())
    {
        m_CTabCtrlOrderTypeManager.AddPage(&m_PageDOrderTypeManager6);
    }

    if (!m_bUpdate)
    {
        m_EditKBst.SetFocus();
    }
    else
    {
        // *** this should be done in order to be able to use the shortcut keys
        m_CTabCtrlOrderTypeManager.GetCurrentPage()->OnSetActive();
        m_CTabCtrlOrderTypeManager.GetCurrentPage()->SetFocus();
    }


    return FALSE;
}

void CDOrderTypeManager::OnCancel()
{
    if (AreChanged()) return;
    CDialogMultiLang::OnCancel();
}

void CDOrderTypeManager::OnOK()
{
    int rc;
    CAUFTRAGSART aart;
    char error_msg[81];
    // Versorgen Struct

    UpdateData();
    if (m_CKBst.IsEmpty())
    {
        MsgBoxOK(AETXT_NO_ORDERTYPE);
        return;
    }

    aart.SetBranchno(m_sSaleCenterNo);
    aart.SetKdauftragart(m_CKBst);

    aart.SetBezeichnung(m_CBezeichnung);
    // char(1)
    aart.SetSkdauftragartnatra(m_bNatra ? '1' : '0');
    aart.SetSkdauftragartnetto(m_bNetto ? '1' : '0');
    aart.SetSbildschirm(m_bBild ? '1' : '0');
    aart.SetSdafue(m_bDafue ? '1' : '0');
    aart.SetDisinkindenterable(m_bHand ? '1' : '0');
    aart.SetSdiscountable(m_bDiscount ? '1' : '0');
    aart.SetSstandard(m_bStandard ? '1' : '0');
    aart.SetSmustsuborder(m_bMuss ? '1' : '0');
    aart.SetSfreeprice(m_bFreePrice ? '1' : '0');
    aart.SetSordercons(m_bAufCons ? '1' : '0');
    aart.SetSrestdel(m_bAufNachl ? '1' : '0');
    aart.SetSnoquota(m_bNoQuota ? '1' : '0');
    aart.SetSdeferorder(m_bDeferOrder ? '1' : '0');
    aart.SetSnopartqty(m_bNoPart ? '1' : '0');
    aart.SetSnodd(m_bNoDD ? '1' : '0');
    aart.SetSonlyeh(m_bOnlyEH ? '1' : '0');
    aart.SetSglobal(m_bGlobal ? '1' : '0');
    // short
    aart.SetSnopromotions(m_bNoPromo ? 1 : 0);
    aart.SetSdefaultkennung(m_bDefaultKennung ? 1 : 0);
    aart.SetSivcvoucherno(m_bIVC ? 1 : 0);
    aart.SetSoriginalinvoiceno(m_bOrgInvoice ? 1 : 0);
    aart.SetAllowdesiredbatch(m_bAllowDesired ? 1 : 0);
    aart.SetAllowfixedbatch(m_bAllowFixed ? 1 : 0);
    aart.SetForbiduserchange(m_bForbidChange ? 1 : 0);
    aart.SetSmustheadline(m_bMustHeadline ? 1 : 0);
    aart.SetSoriginalinvoiceno(m_bOrgInvoice ? 1 : 0);
    aart.SetStockreservation(m_bStockreservation ? 1 : 0);

    // Schreiben auf Server
    if (m_bUpdate)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvUpdateCscOrderType, (void *)&aart.s, AUFTRAGSART_BES, AUFTRAGSART_ANZ, error_msg);
    }
    else
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvInsertCscOrderType, (void *)&aart.s, AUFTRAGSART_BES, AUFTRAGSART_ANZ, error_msg);
    }
    if (rc < 0)
    {
        FehlerBehandlung(rc, error_msg);
        return;
    }
    CDialogMultiLang::OnOK();
}

void CDOrderTypeManager::OnChangeEditKbst()
{
    AllgLaengeKontr(&m_EditKBst, L_PARAART_KDAUFTRAGART, AeGetApp()->Modus());
}

//--- Testen, ob Seiten geaendert ----------------------------------------------//

bool CDOrderTypeManager::AreChanged()
{
    CTabPageMultiLang* CTabPageMultiLang;
    for (int i = 0; (CTabPageMultiLang = m_CTabCtrlOrderTypeManager.GetPage(i)) != NULL; i++)
    {
        if (CTabPageMultiLang->IsChanged())
        {
            CString str;
            str.Format(CResString::ex().getStrTblText(IDS_CHANGED_NOT_SAVED), CTabPageMultiLang->GetTabTitle());
            if (MsgBoxYesNo(str) != IDYES)
                return true;
        }
    }
    return false;
}

// CDOrderTypeManager1 dialog

IMPLEMENT_DYNAMIC(CDOrderTypeManager1, CPropertyPage)

CDOrderTypeManager1::CDOrderTypeManager1()
    : CTabPageMultiLang(IDD_AE_ORDERTYPE_MANAGER1)
{

}

CDOrderTypeManager1::~CDOrderTypeManager1()
{
}

void CDOrderTypeManager1::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_BEZEICHNUNG, m_pFather->m_EditBezeichnung);
    DDX_Text(pDX, IDC_EDIT_BEZEICHNUNG, m_pFather->m_CBezeichnung);
    DDX_Check(pDX, IDC_CHECK_BILD, m_pFather->m_bBild);
    DDX_Check(pDX, IDC_CHECK_DAFUE, m_pFather->m_bDafue);
    DDX_Check(pDX, IDC_CHECK_STANDARD, m_pFather->m_bStandard);
    DDX_Check(pDX, IDC_CHECK_IMMER_GUELT, m_pFather->m_bGlobal);
    DDX_Check(pDX, IDC_CHECKSTOCKRESERVATION, m_pFather->m_bStockreservation);
}


BEGIN_MESSAGE_MAP(CDOrderTypeManager1, CTabPageMultiLang)
    ON_EN_CHANGE(IDC_EDIT_BEZEICHNUNG, OnChangeEditBezeichnung)
    ON_BN_CLICKED(IDC_CHECK_IMMER_GUELT, OnBnClickedCheckImmerGuelt)
    ON_BN_CLICKED(IDC_CHECK_BILD, &CDOrderTypeManager1::OnBnClickedCheckBild)
    ON_BN_CLICKED(IDC_CHECK_DAFUE, &CDOrderTypeManager1::OnBnClickedCheckDafue)
    ON_BN_CLICKED(IDC_CHECK_STANDARD, &CDOrderTypeManager1::OnBnClickedCheckStandard)
    ON_BN_CLICKED(IDC_CHECKSTOCKRESERVATION, &CDOrderTypeManager1::OnBnClickedCheckstockreservation)
END_MESSAGE_MAP()


// CDOrderTypeManager1 message handlers
// DOrderTypeManager.cpp : implementation file
//

//--- GetTabTitle ------------------------------------------------------------//

LPCTSTR CDOrderTypeManager1::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_TYP_MANAGER1);
    return _T(m_csTitle);
}

void CDOrderTypeManager1::OnChangeEditBezeichnung()
{
    AllgLaengeKontr(&m_pFather->m_EditBezeichnung, L_PARAART_BEZEICHNUNG, AeGetApp()->Modus());
    GetDlgItem(IDC_EDIT_BEZEICHNUNG)->GetWindowTextA(m_pFather->m_CBezeichnung);
}

void CDOrderTypeManager1::OnBnClickedCheckImmerGuelt()
{
    if (IsDlgButtonChecked(IDC_CHECK_IMMER_GUELT))
    {
        m_pFather->m_PageDOrderTypeManager3.m_natra.EnableWindow(TRUE);
        m_pFather->m_PageDOrderTypeManager3.m_natra.ShowWindow(SW_SHOW);
        m_pFather->m_PageDOrderTypeManager3.m_netto.EnableWindow(TRUE);
        m_pFather->m_PageDOrderTypeManager3.m_netto.ShowWindow(SW_SHOW);
        m_pFather->m_bGlobal = TRUE;
    }
    else
    {
        m_pFather->m_PageDOrderTypeManager3.m_natra.EnableWindow(FALSE);
        m_pFather->m_PageDOrderTypeManager3.m_natra.ShowWindow(SW_HIDE);
        m_pFather->m_PageDOrderTypeManager3.m_netto.EnableWindow(FALSE);
        m_pFather->m_PageDOrderTypeManager3.m_netto.ShowWindow(SW_HIDE);
        m_pFather->m_bGlobal = FALSE;
    }
}

BOOL CDOrderTypeManager1::OnInitDialog()
{
    CTabPageMultiLang::OnInitDialog();

    if (!m_pFather->m_bUpdate)
    {
        // Standard darf bei Neuanlage nicht gesetzt werden
        CheckDlgButton(IDC_CHECK_STANDARD, FALSE);
        GetDlgItem(IDC_CHECK_STANDARD)->EnableWindow(FALSE);
    }

    if (m_pFather->m_bStandard)
    {
        CheckDlgButton(IDC_CHECK_STANDARD, TRUE);
        // Standard darf nicht weg, sondern nur neu gesetzt werden
        GetDlgItem(IDC_CHECK_STANDARD)->EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDOrderTypeManager1::OnSetActive()
{
    if (!m_pFather->m_bUpdate)
    {
        // Standard darf bei Neuanlage nicht gesetzt werden
        CheckDlgButton(IDC_CHECK_STANDARD, FALSE);
        GetDlgItem(IDC_CHECK_STANDARD)->EnableWindow(FALSE);
    }

    if (m_pFather->m_bStandard)
    {
        CheckDlgButton(IDC_CHECK_STANDARD, TRUE);
        // Standard darf nicht weg, sondern nur neu gesetzt werden
        GetDlgItem(IDC_CHECK_STANDARD)->EnableWindow(FALSE);
    }
    m_bIsActive = true;
    return CTabPageMultiLang::OnSetActive();
}

void CDOrderTypeManager1::OnBnClickedCheckBild()
{
    if (IsDlgButtonChecked(IDC_CHECK_BILD))
    {
        m_pFather->m_bBild = TRUE;
    }
    else
    {
        m_pFather->m_bBild = FALSE;
    }
}
void CDOrderTypeManager1::OnBnClickedCheckstockreservation()
{
	if (IsDlgButtonChecked(IDC_CHECKSTOCKRESERVATION))
	{
		m_pFather->m_bStockreservation = TRUE;
	}
	else
	{
		m_pFather->m_bStockreservation = FALSE;
	}
}
void CDOrderTypeManager1::OnBnClickedCheckDafue()
{
    if (IsDlgButtonChecked(IDC_CHECK_DAFUE))
    {
        m_pFather->m_bDafue = TRUE;
    }
    else
    {
        m_pFather->m_bDafue = FALSE;
    }
}

void CDOrderTypeManager1::OnBnClickedCheckStandard()
{
    if (IsDlgButtonChecked(IDC_CHECK_STANDARD))
    {
        m_pFather->m_bStandard = TRUE;
    }
    else
    {
        m_pFather->m_bStandard = FALSE;
    }
}

// CDOrderTypeManager2 dialog

IMPLEMENT_DYNAMIC(CDOrderTypeManager2, CPropertyPage)

CDOrderTypeManager2::CDOrderTypeManager2()
    : CTabPageMultiLang(IDD_AE_ORDERTYPE_MANAGER2)
{

}

CDOrderTypeManager2::~CDOrderTypeManager2()
{
}

void CDOrderTypeManager2::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_AUF_CONS, m_pFather->m_bAufCons);
    DDX_Check(pDX, IDC_CHECK_AUF_NACHL, m_pFather->m_bAufNachl);
    DDX_Check(pDX, IDC_CHECK_AUF_NOQUOTA, m_pFather->m_bNoQuota);
    DDX_Check(pDX, IDC_CHECK_AUF_DEFER_ORDER, m_pFather->m_bDeferOrder);
    DDX_Check(pDX, IDC_CHECK_AUF_NOPART, m_pFather->m_bNoPart);
    DDX_Check(pDX, IDC_CHECK_AUF_NODD, m_pFather->m_bNoDD);
}


BEGIN_MESSAGE_MAP(CDOrderTypeManager2, CTabPageMultiLang)
    ON_BN_CLICKED(IDC_CHECK_AUF_NACHL, OnBnClickedCheckAufNachl)
    ON_BN_CLICKED(IDC_CHECK_AUF_CONS, &CDOrderTypeManager2::OnBnClickedCheckAufCons)
    ON_BN_CLICKED(IDC_CHECK_AUF_DEFER_ORDER, &CDOrderTypeManager2::OnBnClickedCheckAufDeferOrder)
    ON_BN_CLICKED(IDC_CHECK_AUF_NOPART, &CDOrderTypeManager2::OnBnClickedCheckAufNopart)
    ON_BN_CLICKED(IDC_CHECK_AUF_NODD, &CDOrderTypeManager2::OnBnClickedCheckAufNodd)
    ON_BN_CLICKED(IDC_CHECK_AUF_NOQUOTA, &CDOrderTypeManager2::OnBnClickedCheckAufNoquota)
END_MESSAGE_MAP()


// CDOrderTypeManager2 message handlers
// DOrderTypeManager.cpp : implementation file
//

//--- GetTabTitle ------------------------------------------------------------//

LPCTSTR CDOrderTypeManager2::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_TYP_MANAGER2);
    return _T(m_csTitle);
}

void CDOrderTypeManager2::OnBnClickedCheckAufNachl()
{
    if (IsDlgButtonChecked(IDC_CHECK_AUF_NACHL))
    {
        GetDlgItem(IDC_CHECK_AUF_NOPART)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_AUF_NOPART)->ShowWindow(SW_SHOW);
        m_pFather->m_bAufNachl = TRUE;
    }
    else
    {
        GetDlgItem(IDC_CHECK_AUF_NOPART)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_AUF_NOPART)->ShowWindow(SW_HIDE);
        m_pFather->m_bAufNachl = FALSE;
    }
}

BOOL CDOrderTypeManager2::OnSetActive()
{
    if (m_pFather->m_bAufNachl)
    {
        GetDlgItem(IDC_CHECK_AUF_NOPART)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_AUF_NOPART)->ShowWindow(SW_SHOW);
    }
    else
    {
        GetDlgItem(IDC_CHECK_AUF_NOPART)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_AUF_NOPART)->ShowWindow(SW_HIDE);
    }
#ifdef _DEBUG
    GetDlgItem(IDC_CHECK_AUF_NOQUOTA)->EnableWindow(TRUE); // Only for developer
#endif
    m_bIsActive = true;
    return CTabPageMultiLang::OnSetActive();
}

void CDOrderTypeManager2::OnBnClickedCheckAufCons()
{
    if (IsDlgButtonChecked(IDC_CHECK_AUF_CONS))
    {
        m_pFather->m_bAufCons = TRUE;
    }
    else
    {
        m_pFather->m_bAufCons = FALSE;
    }
}

void CDOrderTypeManager2::OnBnClickedCheckAufDeferOrder()
{
    if (IsDlgButtonChecked(IDC_CHECK_AUF_DEFER_ORDER))
    {
        m_pFather->m_bDeferOrder = TRUE;
    }
    else
    {
        m_pFather->m_bDeferOrder = FALSE;
    }
}


void CDOrderTypeManager2::OnBnClickedCheckAufNopart()
{
    if (IsDlgButtonChecked(IDC_CHECK_AUF_NOPART))
    {
        m_pFather->m_bNoPart = TRUE;
    }
    else
    {
        m_pFather->m_bNoPart = FALSE;
    }
}

void CDOrderTypeManager2::OnBnClickedCheckAufNodd()
{
    if (IsDlgButtonChecked(IDC_CHECK_AUF_NODD))
    {
        m_pFather->m_bNoDD = TRUE;
    }
    else
    {
        m_pFather->m_bNoDD = FALSE;
    }
}

void CDOrderTypeManager2::OnBnClickedCheckAufNoquota()
{
    if (IsDlgButtonChecked(IDC_CHECK_AUF_NOQUOTA))
    {
        m_pFather->m_bNoQuota = TRUE;
    }
    else
    {
        m_pFather->m_bNoQuota = FALSE;
    }
}

// CDOrderTypeManager3 dialog

IMPLEMENT_DYNAMIC(CDOrderTypeManager3, CPropertyPage)

CDOrderTypeManager3::CDOrderTypeManager3()
    : CTabPageMultiLang(IDD_AE_ORDERTYPE_MANAGER3)
{
}

CDOrderTypeManager3::~CDOrderTypeManager3()
{
}

void CDOrderTypeManager3::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_HAND, m_pFather->m_bHand);
    DDX_Check(pDX, IDC_CHECK_DISCOUNT, m_pFather->m_bDiscount);
    DDX_Check(pDX, IDC_CHECK_MUSS, m_pFather->m_bMuss);
    DDX_Check(pDX, IDC_CHECK_FREE_PRICE, m_pFather->m_bFreePrice);
    DDX_Check(pDX, IDC_CHECK_AUF_ONLYEH, m_pFather->m_bOnlyEH);
    DDX_Check(pDX, IDC_CHECK_AUF_NO_PROMO, m_pFather->m_bNoPromo);
    DDX_Check(pDX, IDC_CHECK_NATRA, m_pFather->m_bNatra);
    DDX_Check(pDX, IDC_CHECK_NETTO, m_pFather->m_bNetto);
    DDX_Control(pDX, IDC_CHECK_NATRA, m_natra);
    DDX_Control(pDX, IDC_CHECK_NETTO, m_netto);
    DDX_Check(pDX, IDC_CHECK_RET_AVIS, m_pFather->m_bConsultationNeeded);
    DDX_Check(pDX, IDC_CHECK_NO_LINEFEE, m_pFather->m_bNoLinefee);
    DDX_Check(pDX, IDC_CHECK_NO_PACKAGEFEE, m_pFather->m_bNoPackagefee);
}


BEGIN_MESSAGE_MAP(CDOrderTypeManager3, CTabPageMultiLang)
    ON_BN_CLICKED(IDC_CHECK_HAND, &CDOrderTypeManager3::OnBnClickedCheckHand)
    ON_BN_CLICKED(IDC_CHECK_DISCOUNT, &CDOrderTypeManager3::OnBnClickedCheckDiscount)
    ON_BN_CLICKED(IDC_CHECK_MUSS, &CDOrderTypeManager3::OnBnClickedCheckMuss)
    ON_BN_CLICKED(IDC_CHECK_FREE_PRICE, &CDOrderTypeManager3::OnBnClickedCheckFreePrice)
    ON_BN_CLICKED(IDC_CHECK_AUF_ONLYEH, &CDOrderTypeManager3::OnBnClickedCheckAufOnlyeh)
    ON_BN_CLICKED(IDC_CHECK_AUF_NO_PROMO, &CDOrderTypeManager3::OnBnClickedCheckAufNoPromo)
    ON_BN_CLICKED(IDC_CHECK_NATRA, &CDOrderTypeManager3::OnBnClickedCheckNatra)
    ON_BN_CLICKED(IDC_CHECK_NETTO, &CDOrderTypeManager3::OnBnClickedCheckNetto)
END_MESSAGE_MAP()


// CDOrderTypeManager3 message handlers
// DOrderTypeManager.cpp : implementation file
//

//--- GetTabTitle ------------------------------------------------------------//

LPCTSTR CDOrderTypeManager3::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_TYP_MANAGER3);
    return _T(m_csTitle);
}

BOOL CDOrderTypeManager3::OnSetActive()
{
    if (m_pFather->m_bGlobal)
    {
        m_natra.EnableWindow(TRUE);
        m_natra.ShowWindow(SW_SHOW);
        m_netto.EnableWindow(TRUE);
        m_netto.ShowWindow(SW_SHOW);
    }
    else
    {
        m_natra.EnableWindow(FALSE);
        m_natra.ShowWindow(SW_HIDE);
        m_netto.EnableWindow(FALSE);
        m_netto.ShowWindow(SW_HIDE);
    }
    if (AeGetApp()->IsCH())
    {
        GetDlgItem(IDC_CHECK_NO_LINEFEE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHECK_NO_PACKAGEFEE)->ShowWindow(SW_SHOW);
    }
    if (AeGetApp()->IsDE())
    {
        GetDlgItem(IDC_CHECK_RET_AVIS)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHECK_RET_AVIS)->EnableWindow(TRUE);
    }

    m_bIsActive = true;
    return CTabPageMultiLang::OnSetActive();
}

void CDOrderTypeManager3::OnBnClickedCheckHand()
{
    m_pFather->m_bHand = IsDlgButtonChecked(IDC_CHECK_HAND) ? TRUE : FALSE;
}

void CDOrderTypeManager3::OnBnClickedCheckDiscount()
{
    m_pFather->m_bDiscount = IsDlgButtonChecked(IDC_CHECK_DISCOUNT) ? TRUE : FALSE;
}

void CDOrderTypeManager3::OnBnClickedCheckMuss()
{
    m_pFather->m_bMuss = IsDlgButtonChecked(IDC_CHECK_MUSS) ? TRUE : FALSE;
}

void CDOrderTypeManager3::OnBnClickedCheckFreePrice()
{
    m_pFather->m_bFreePrice = IsDlgButtonChecked(IDC_CHECK_FREE_PRICE) ? TRUE : FALSE;
}

void CDOrderTypeManager3::OnBnClickedCheckAufOnlyeh()
{
    m_pFather->m_bOnlyEH = IsDlgButtonChecked(IDC_CHECK_AUF_ONLYEH) ? TRUE : FALSE;
}

void CDOrderTypeManager3::OnBnClickedCheckAufNoPromo()
{
    m_pFather->m_bNoPromo = IsDlgButtonChecked(IDC_CHECK_AUF_NO_PROMO) ? TRUE : FALSE;
}

void CDOrderTypeManager3::OnBnClickedCheckNatra()
{
    m_pFather->m_bNatra = IsDlgButtonChecked(IDC_CHECK_NATRA) ? TRUE : FALSE;
}

void CDOrderTypeManager3::OnBnClickedCheckNetto()
{
    m_pFather->m_bNetto = IsDlgButtonChecked(IDC_CHECK_NETTO) ? TRUE : FALSE;
}

// CDOrderTypeManager4 dialog

IMPLEMENT_DYNAMIC(CDOrderTypeManager4, CPropertyPage)

CDOrderTypeManager4::CDOrderTypeManager4()
    : CTabPageMultiLang(IDD_AE_ORDERTYPE_MANAGER4)
{
    ColumnsConfig[COL_CONFIG_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    ColumnsConfig[COL_CONFIG_NAME].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
    ColumnsConfig[COL_CONFIG_RESERVTYP].Columns = CResString::ex().getStrTblText(AETXT_TYP);
    ColumnsConfig[COL_CONFIG_PRIORITY].Columns = CResString::ex().getStrTblText(AETXT_PRIO);
    ColumnsConfig[COL_CONFIG_ID].Columns = CResString::ex().getStrTblText(AETXT_KURZ_TOUR_ID);
    ColumnsConfig[COL_CONFIG_STOCKONLY].Columns = "Stockonly";
    ColumnsConfig[COL_CONFIG_FREEFIRST].Columns = "Freefirst";
}

CDOrderTypeManager4::~CDOrderTypeManager4()
{
}

void CDOrderTypeManager4::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDOrderTypeManager4, CTabPageMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_PLUS, OnBnClickedButtonPlus)
    ON_BN_CLICKED(IDC_BUTTON_MINUS, OnBnClickedButtonMinus)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
END_MESSAGE_MAP()


// CDOrderTypeManager4 message handlers
// DOrderTypeManager.cpp : implementation file
//

//--- GetTabTitle ------------------------------------------------------------//

LPCTSTR CDOrderTypeManager4::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_TYP_MANAGER4);
    return _T(m_csTitle);
}


BOOL CDOrderTypeManager4::OnInitDialog()
{
    CTabPageMultiLang::OnInitDialog();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(ColumnsConfig, m_ListCtl))
    {
        return FALSE;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDOrderTypeManager4::OnSetActive()
{
    if (!GetAeUser().IsPflegeReservationConfig())
    {
        // Reservierungszuordnung darf nur mit Recht verwaltet werden
        GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_HIDE);
    }

    if (!m_pFather->m_bUpdate)
    {
        // Reservierungszuordnung darf bei Neuanlage nicht gesetzt werden
        GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_LIST1)->EnableWindow(FALSE);
        GetDlgItem(IDC_LIST1)->ShowWindow(SW_HIDE);
    }
    else
    {
        //ordertypereservationconfigs lesen
        ReadDataInListBox();
    }
    m_bIsActive = true;
    return CTabPageMultiLang::OnSetActive();
}

void CDOrderTypeManager4::ReadDataInListBox()
{
    CORDERTYPERESERVATIONCONFIG config;
    CStringArray s;
    s.SetSize(NUM_COLUMNS_CONFIG);
    ppString name;
    int rc = 0;
    char error_msg[81];

    config.SetCscordertype(m_pFather->m_CKBst);
    CLetterMan kb;
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvGetReservationConfigListByOrderType, (void *)&config.s, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ, error_msg);
        if (rc < 0)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
        if (rc != 0) break;
        s[COL_CONFIG_KB] = kb.Next();
        s[COL_CONFIG_NAME] = config.GetOrdertypereservationconfigname(name);
        s[COL_CONFIG_RESERVTYP].Format("%d", config.GetCscreservationtype());
        s[COL_CONFIG_PRIORITY].Format("%d", config.GetPriority());
        s[COL_CONFIG_ID].Format("%d", config.GetId());
        s[COL_CONFIG_STOCKONLY].Format("%d", config.GetReservedstockonly());
        s[COL_CONFIG_FREEFIRST].Format("%d", config.GetFreestockhaspriority());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS_CONFIG, s))
        {
            EndWaitCursor();
            return;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    if (GetAeUser().IsPflegeReservationConfig())
    {
        // Reservierungszuordnung darf nur mit Recht verwaltet werden
        if (m_ListCtl.GetItemCount() > 0)
        {
            GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_HIDE);
        }
        else
        {
            GetDlgItem(IDC_BUTTON_MINUS)->EnableWindow(FALSE);
            GetDlgItem(IDC_BUTTON_MINUS)->ShowWindow(SW_HIDE);
            GetDlgItem(IDC_BUTTON_PLUS)->EnableWindow(TRUE);
            GetDlgItem(IDC_BUTTON_PLUS)->ShowWindow(SW_SHOW);
        }
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
}

void CDOrderTypeManager4::OnNMDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    if (!GetAeUser().IsPflegeReservationConfig())
    {
        *pResult = 0L;
        return;
    }
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDReservationConfig dlgReservationConfig;
        dlgReservationConfig.m_iConfigID = atoi(m_ListCtl.GetItemText(pos, COL_CONFIG_ID));
        dlgReservationConfig.m_iReserveType = atoi(m_ListCtl.GetItemText(pos, COL_CONFIG_RESERVTYP));
        dlgReservationConfig.m_sPriority = (short)atoi(m_ListCtl.GetItemText(pos, COL_CONFIG_PRIORITY));
        dlgReservationConfig.m_cBez = m_ListCtl.GetItemText(pos, COL_CONFIG_NAME);
        dlgReservationConfig.m_cAArt = m_pFather->m_CKBst;

        if (atoi(m_ListCtl.GetItemText(pos, COL_CONFIG_STOCKONLY)) == 1)
        {
            dlgReservationConfig.m_bOnlyRes = TRUE;
        }
        else
        {
            dlgReservationConfig.m_bOnlyRes = FALSE;
        }
        if (atoi(m_ListCtl.GetItemText(pos, COL_CONFIG_FREEFIRST)) == 1)
        {
            dlgReservationConfig.m_bFreeFirst = TRUE;
        }
        else
        {
            dlgReservationConfig.m_bFreeFirst = FALSE;
        }
        if (dlgReservationConfig.DoModal() == IDOK)
        {
            CString prio;
            prio.Format("%d", dlgReservationConfig.m_sPriority);
            m_ListCtl.SetItemText(pos, COL_CONFIG_PRIORITY, prio);
            if (dlgReservationConfig.m_bOnlyRes)
            {
                prio = "1";
            }
            else
            {
                prio = "0";
            }
            m_ListCtl.SetItemText(pos, COL_CONFIG_STOCKONLY, prio);
            if (dlgReservationConfig.m_bFreeFirst)
            {
                prio = "1";
            }
            else
            {
                prio = "0";
            }
            m_ListCtl.SetItemText(pos, COL_CONFIG_FREEFIRST, prio);
        }
    }
    *pResult = 0L;
}

BOOL CDOrderTypeManager4::CheckExist(int Reservtyp, int Prio)
{
    if (this->m_ListCtl.GetItemCount() == 0)
    {
        return FALSE;
    }
    for (int i = 0; i < m_ListCtl.GetItemCount(); i++)
    {
        if (atoi(m_ListCtl.GetItemText(i, COL_CONFIG_PRIORITY)) == Prio)
        {
            if (atoi(m_ListCtl.GetItemText(i, COL_CONFIG_RESERVTYP)) == Reservtyp) return TRUE;
        }
    }
    return FALSE;
}

void CDOrderTypeManager4::OnBnClickedButtonMinus()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
        {
            char error_msg[81];
            CORDERTYPERESERVATIONCONFIG config;
            //delete config
            config.SetId(atol(m_ListCtl.GetItemText(pos, COL_CONFIG_ID)));
            int rc = ::ServerNr(PIPE_AE_SRV, AasrvDeleteReservationConfig, (void *)&config.s, ORDERTYPERESERVATIONCONFIG_BES, ORDERTYPERESERVATIONCONFIG_ANZ, error_msg);
            if (rc < 0)
            {
                FehlerBehandlung(rc, error_msg);
                return;
            }
            MsgBoxOK(AETXT_ROW_DELETED);
            ReadDataInListBox();
        }
    }
    else
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
    }
}

void CDOrderTypeManager4::OnBnClickedButtonPlus()
{
    CDReservationConfig configdlg;
    configdlg.m_cAArt = m_pFather->m_CKBst;
    configdlg.m_pFather = this;
    if (configdlg.DoModal() == IDOK)
    {
        ReadDataInListBox();
    }
}

// CDOrderTypeManager5 dialog

IMPLEMENT_DYNAMIC(CDOrderTypeManager5, CPropertyPage)

CDOrderTypeManager5::CDOrderTypeManager5()
    : CTabPageMultiLang(IDD_AE_ORDERTYPE_MANAGER5)
{
}

CDOrderTypeManager5::~CDOrderTypeManager5()
{
}

void CDOrderTypeManager5::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_ALLOW_DESIRED_BATCH, m_pFather->m_bAllowDesired);
    DDX_Check(pDX, IDC_CHECK_ALLOW_FIXED_BATCH, m_pFather->m_bAllowFixed);
    DDX_Check(pDX, IDC_CHECK_FORBID_USER_CHANGE, m_pFather->m_bForbidChange);
}


BEGIN_MESSAGE_MAP(CDOrderTypeManager5, CTabPageMultiLang)
    ON_BN_CLICKED(IDC_CHECK_ALLOW_DESIRED_BATCH, &CDOrderTypeManager5::OnBnClickedCheckAllowDesiredBatch)
    ON_BN_CLICKED(IDC_CHECK_ALLOW_FIXED_BATCH, &CDOrderTypeManager5::OnBnClickedCheckAllowFixedBatch)
    ON_BN_CLICKED(IDC_CHECK_FORBID_USER_CHANGE, &CDOrderTypeManager5::OnBnClickedCheckForbidUserChange)
END_MESSAGE_MAP()


// CDOrderTypeManager5 message handlers
// DOrderTypeManager.cpp : implementation file
//

//--- GetTabTitle ------------------------------------------------------------//

LPCTSTR CDOrderTypeManager5::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_TYP_MANAGER5);
    return _T(m_csTitle);
}

BOOL CDOrderTypeManager5::OnSetActive()
{
    m_bIsActive = true;
    return CTabPageMultiLang::OnSetActive();
}

void CDOrderTypeManager5::OnBnClickedCheckAllowDesiredBatch()
{
    if (IsDlgButtonChecked(IDC_CHECK_ALLOW_DESIRED_BATCH))
    {
        m_pFather->m_bAllowDesired = TRUE;
        m_pFather->m_bAllowFixed = FALSE;
        CheckDlgButton(IDC_CHECK_ALLOW_FIXED_BATCH, FALSE);
    }
    else
    {
        m_pFather->m_bAllowDesired = FALSE;
    }
}

void CDOrderTypeManager5::OnBnClickedCheckAllowFixedBatch()
{
    if (IsDlgButtonChecked(IDC_CHECK_ALLOW_FIXED_BATCH))
    {
        m_pFather->m_bAllowFixed = TRUE;
        m_pFather->m_bAllowDesired = FALSE;
        CheckDlgButton(IDC_CHECK_ALLOW_DESIRED_BATCH, FALSE);
    }
    else
    {
        m_pFather->m_bAllowFixed = FALSE;
    }
}

void CDOrderTypeManager5::OnBnClickedCheckForbidUserChange()
{
    m_pFather->m_bForbidChange = IsDlgButtonChecked(IDC_CHECK_FORBID_USER_CHANGE) ? TRUE : FALSE;
}


// CDOrderTypeManager6 dialog

IMPLEMENT_DYNAMIC(CDOrderTypeManager6, CPropertyPage)

CDOrderTypeManager6::CDOrderTypeManager6()
    : CTabPageMultiLang(IDD_AE_ORDERTYPE_MANAGER6)
{
}

CDOrderTypeManager6::~CDOrderTypeManager6()
{
}

void CDOrderTypeManager6::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Check(pDX, IDC_CHECK_AUF_MIT_KENNUNG, m_pFather->m_bDefaultKennung);
    DDX_Check(pDX, IDC_CHECK_AUF_MIT_IVC, m_pFather->m_bIVC);
    DDX_Check(pDX, IDC_CHECK_AUF_MIT_ORGINVOICE, m_pFather->m_bOrgInvoice);
}


BEGIN_MESSAGE_MAP(CDOrderTypeManager6, CTabPageMultiLang)
    ON_BN_CLICKED(IDC_CHECK_AUF_MIT_KENNUNG, &CDOrderTypeManager6::OnBnClickedCheckAufMitKennung)
    ON_BN_CLICKED(IDC_CHECK_AUF_MIT_IVC, &CDOrderTypeManager6::OnBnClickedCheckAufMitIvc)
    ON_BN_CLICKED(IDC_CHECK_AUF_MIT_ORGINVOICE, &CDOrderTypeManager6::OnBnClickedCheckAufMitOrginvoice)
    ON_BN_CLICKED(IDC_CHECK_MUST_HEADLINE, &CDOrderTypeManager6::OnBnClickedCheckMustHeadline)
END_MESSAGE_MAP()


// CDOrderTypeManager6 message handlers

//--- GetTabTitle ------------------------------------------------------------//

LPCTSTR CDOrderTypeManager6::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_TYP_MANAGER6);
    return _T(m_csTitle);
}

BOOL CDOrderTypeManager6::OnSetActive()
{
    if ((m_pFather->m_CKBst == "NO") && AeGetApp()->IsDE())
    {
        GetDlgItem(IDC_CHECK_AUF_MIT_KENNUNG)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_AUF_MIT_KENNUNG)->ShowWindow(SW_SHOW);
        if (m_pFather->m_bDefaultKennung)
            CheckDlgButton(IDC_CHECK_AUF_MIT_KENNUNG, TRUE);
    }
    if (AeGetApp()->IsDE())
    {
        GetDlgItem(IDC_CHECK_AUF_MIT_IVC)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_AUF_MIT_IVC)->ShowWindow(SW_SHOW);
        if (m_pFather->m_bIVC)
            CheckDlgButton(IDC_CHECK_AUF_MIT_IVC, TRUE);
    }
    if (AeGetApp()->IsFR())
    {
        GetDlgItem(IDC_CHECK_AUF_MIT_ORGINVOICE)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_AUF_MIT_ORGINVOICE)->ShowWindow(SW_SHOW);
        if (m_pFather->m_bOrgInvoice)
            CheckDlgButton(IDC_CHECK_AUF_MIT_ORGINVOICE, TRUE);
    }
    GetDlgItem(IDC_CHECK_MUST_HEADLINE)->ShowWindow(SW_SHOW);
    if (m_pFather->m_bMustHeadline)
        CheckDlgButton(IDC_CHECK_MUST_HEADLINE, TRUE);

    m_bIsActive = true;
    return CTabPageMultiLang::OnSetActive();
}

void CDOrderTypeManager6::OnBnClickedCheckAufMitKennung()
{
    m_pFather->m_bDefaultKennung = IsDlgButtonChecked(IDC_CHECK_AUF_MIT_KENNUNG) ? TRUE : FALSE;
}

void CDOrderTypeManager6::OnBnClickedCheckAufMitIvc()
{
    m_pFather->m_bIVC = IsDlgButtonChecked(IDC_CHECK_AUF_MIT_IVC) ? TRUE : FALSE;
}

void CDOrderTypeManager6::OnBnClickedCheckAufMitOrginvoice()
{
    m_pFather->m_bOrgInvoice = IsDlgButtonChecked(IDC_CHECK_AUF_MIT_ORGINVOICE) ? TRUE : FALSE;
}

void CDOrderTypeManager6::OnBnClickedCheckMustHeadline()
{
    m_pFather->m_bMustHeadline = IsDlgButtonChecked(IDC_CHECK_MUST_HEADLINE) ? TRUE : FALSE;
}

