// DPromoQuota.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DPromoQuota.h"
#include "DKndWahl.h"
#include "DPromoWahl.h"

//Definition der Tabellenbreite und der Ueberschriften

#define COL_PROMO_KB            0
#define COL_PROMO_NUMMER        1
#define COL_PROMO_PROMO_NAME    2
#define COL_PROMO_PZN           3
#define COL_PROMO_BRANCH_QTY    4
#define COL_PROMO_BRANCH_KUM    5
#define COL_PROMO_IDF           6
#define COL_PROMO_APO           7
#define COL_PROMO_ORT           8
#define COL_PROMO_CST_QTY       9
#define COL_PROMO_CST_MIN       10
#define COL_PROMO_CST_KUM       11


#define NUM_COLUMNS     12

static COLUMNS_TYPES Columns[] =
{
    COL_PROMO_KB,         "",  20, LVCFMT_LEFT,
    COL_PROMO_NUMMER,     "",  50, LVCFMT_RIGHT,
    COL_PROMO_PROMO_NAME, "", 125, LVCFMT_LEFT,
    COL_PROMO_PZN,        "",  58, LVCFMT_RIGHT,
    COL_PROMO_BRANCH_QTY, "",  58, LVCFMT_RIGHT,
    COL_PROMO_BRANCH_KUM, "",  58, LVCFMT_RIGHT,
    COL_PROMO_IDF,        "",  54, LVCFMT_RIGHT,
    COL_PROMO_APO,        "", 125, LVCFMT_LEFT,
    COL_PROMO_ORT,        "", 125, LVCFMT_LEFT,
    COL_PROMO_CST_QTY,    "",  50, LVCFMT_RIGHT,
    COL_PROMO_CST_MIN,    "",  50, LVCFMT_RIGHT,
    COL_PROMO_CST_KUM,    "",  50, LVCFMT_RIGHT,
    -1,                   "",   0, 0
};

// CDPromoQuota-Dialogfeld

IMPLEMENT_DYNAMIC(CDPromoQuota, CDialog)
CDPromoQuota::CDPromoQuota(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDPromoQuota::IDD, pParent)
    , m_cKndNr(_T(""))
    , m_cPromoNr(_T(""))
{
}

CDPromoQuota::~CDPromoQuota()
{
}

void CDPromoQuota::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_IDF, m_cKndNr);
    DDX_Text(pDX, IDC_EDIT_PROMONO, m_cPromoNr);
    DDX_Control(pDX, IDC_EDIT_IDF, m_edit_IDF);
    DDX_Control(pDX, IDC_EDIT_PROMONO, m_edit_PromoNo);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDPromoQuota, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_KUNDE, OnBnClickedButtonKunde)
    ON_BN_CLICKED(IDC_BUTTON_PROMO, OnBnClickedButtonPromo)
    ON_BN_CLICKED(IDC_BUTTON_ALL, OnBnClickedButtonAll)
    ON_BN_CLICKED(IDC_BUTTON_ANZ_KND, OnBnClickedButtonAnzKnd)
    ON_BN_CLICKED(IDC_BUTTON_ANZ_PROMO, OnBnClickedButtonAnzPromo)
    ON_EN_CHANGE(IDC_EDIT_IDF, OnEnChangeEditIdf)
    ON_EN_CHANGE(IDC_EDIT_PROMONO, OnEnChangeEditPromono)
END_MESSAGE_MAP()


// CDPromoQuota-Meldungshandler

void CDPromoQuota::OnBnClickedButtonKunde()
{
    CDKndWahl dlgKndWahl;
    dlgKndWahl.m_apo = m_CMC;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        m_lKunde = 0L;
        return;
    }
    m_lKunde = dlgKndWahl.GetIdfNr();
    m_CMC.Format("%d",m_lKunde);
}

void CDPromoQuota::OnBnClickedButtonPromo()
{
    CDPromoWahl dlgPromoWahl;
    dlgPromoWahl.m_promo = m_CPromo;
    if (dlgPromoWahl.DoModal() != IDOK)
    {
        m_sPromo = 0;
        return;
    }
    m_sPromo = dlgPromoWahl.m_sPromoNr;
    m_CPromo.Format("%d",m_sPromo);
}

void CDPromoQuota::OnBnClickedButtonAll()
{
    m_kb.Reset();
    ppString Name;
    ppString NameApo;
    ppString Ort;
    m_List1.DeleteAllItems();
    m_Promoanz.SetBranchno(AeGetApp()->VzNr());
    BeginWaitCursor();
    for (;;)
    {
        if (m_Promoanz.SelList() != SRV_OK) break;
        m_s[COL_PROMO_NUMMER].Format("%d", m_Promoanz.GetPromotion_no());
        m_s[COL_PROMO_PROMO_NAME] = m_Promoanz.GetName(Name);
        m_s[COL_PROMO_PZN].Format("%d", m_Promoanz.GetArticleno());
        m_s[COL_PROMO_BRANCH_QTY].Format("%d", m_Promoanz.GetBranchquotaqty());
        m_s[COL_PROMO_BRANCH_KUM].Format("%d", m_Promoanz.GetSoldqtybranch());
        m_s[COL_PROMO_IDF].Empty();
        m_s[COL_PROMO_APO].Empty();
        m_s[COL_PROMO_ORT].Empty();
        m_s[COL_PROMO_CST_QTY].Format("%d", m_Promoanz.GetCustomerquotaqty());
        m_s[COL_PROMO_CST_MIN].Format("%d", m_Promoanz.GetCustomerminqty());
        FillList();
        m_Promoanzcst.SetBranchno(AeGetApp()->VzNr());
        m_Promoanzcst.SetPromotion_no(m_Promoanz.GetPromotion_no());
        m_Promoanzcst.SetArticleno(m_Promoanz.GetArticleno());
        m_s[COL_PROMO_NUMMER].Empty();
        m_s[COL_PROMO_PROMO_NAME].Empty();
        m_s[COL_PROMO_PZN].Empty();
        m_s[COL_PROMO_BRANCH_QTY].Empty();
        m_s[COL_PROMO_BRANCH_KUM].Empty();
        for (;;)
        {
            if (m_Promoanzcst.SelListPromo() != SRV_OK)
                break;
            m_s[COL_PROMO_IDF].Format("%d", m_Promoanzcst.GetCustomerno());
            m_s[COL_PROMO_APO] = m_Promoanzcst.GetNameapo(NameApo);
            m_s[COL_PROMO_ORT] = m_Promoanzcst.GetOrt(Ort);
            m_s[COL_PROMO_CST_QTY].Format("%d", m_Promoanzcst.GetCustomerquotaqty());
            m_s[COL_PROMO_CST_MIN].Empty();
            m_s[COL_PROMO_CST_KUM].Format("%d", m_Promoanzcst.GetSoldqtycst());
            FillList();
        }
        m_Promoanzcst.CloseCursor();
    }
    m_Promoanz.CloseCursor();
    EndWaitCursor();
    if (m_List1.GetItemCount() == 0)
    {
        MsgBoxOK(IDP_NO_DATA);
    }
}

void CDPromoQuota::OnBnClickedButtonAnzKnd()
{
    UpdateData();
    if (m_cKndNr.IsEmpty())
    {
        MsgBoxOK(IDP_MUSS_KUNDENNR);
        return;
    }
    m_kb.Reset();
    ppString Name;
    ppString NameApo;
    ppString Ort;
    m_List1.DeleteAllItems();
    m_Promoanzcst.SetBranchno(AeGetApp()->VzNr());
    m_Promoanzcst.SetCustomerno(atol(m_cKndNr));
    BeginWaitCursor();
    for (;;)
    {
        if (m_Promoanzcst.SelListCst() != SRV_OK)
            break;
        m_Promoanz.SetBranchno(AeGetApp()->VzNr());
        m_Promoanz.SetPromotion_no(m_Promoanzcst.GetPromotion_no());
        m_Promoanz.SetArticleno(m_Promoanzcst.GetArticleno());
        m_Promoanz.SelQuotaPzn();
        m_s[COL_PROMO_NUMMER].Format("%d", m_Promoanzcst.GetPromotion_no());
        m_s[COL_PROMO_PROMO_NAME] = m_Promoanzcst.GetName(Name);
        m_s[COL_PROMO_PZN].Format("%d", m_Promoanz.GetArticleno());
        m_s[COL_PROMO_BRANCH_QTY].Format("%d", m_Promoanz.GetBranchquotaqty());
        m_s[COL_PROMO_BRANCH_KUM].Format("%d", m_Promoanz.GetSoldqtybranch());
        m_s[COL_PROMO_IDF].Format("%d", m_Promoanzcst.GetCustomerno());
        m_s[COL_PROMO_APO] = m_Promoanzcst.GetNameapo(NameApo);
        m_s[COL_PROMO_ORT] = m_Promoanzcst.GetOrt(Ort);
        m_s[COL_PROMO_CST_QTY].Format("%d", m_Promoanzcst.GetCustomerquotaqty());
        m_s[COL_PROMO_CST_MIN].Format("%d", m_Promoanz.GetCustomerminqty());
        m_s[COL_PROMO_CST_KUM].Format("%d", m_Promoanzcst.GetSoldqtycst());
        FillList();
    }
    m_Promoanzcst.CloseCursor();
    EndWaitCursor();
    if (m_List1.GetItemCount() == 0)
    {
        MsgBoxOK(IDP_NO_DATA);
    }
}

void CDPromoQuota::OnBnClickedButtonAnzPromo()
{
    UpdateData();
    if (m_cPromoNr.IsEmpty())
    {
        MsgBoxOK(AETXT_MUSS_PROMO);
        return;
    }
    m_kb.Reset();
    ppString Name;
    ppString NameApo;
    ppString Ort;
    m_List1.DeleteAllItems();
    BeginWaitCursor();
    m_Promoanz.SetBranchno(AeGetApp()->VzNr());
    m_Promoanz.SetPromotion_no(static_cast<short>(atoi(m_cPromoNr)));
    for (;;)
    {
        if (m_Promoanz.SelQuota())
        {
            break;
        }
        m_s[COL_PROMO_NUMMER].Format("%d", m_Promoanz.GetPromotion_no());
        m_s[COL_PROMO_PROMO_NAME] = m_Promoanz.GetName(Name);
        m_s[COL_PROMO_PZN].Format("%d", m_Promoanz.GetArticleno());
        m_s[COL_PROMO_BRANCH_QTY].Format("%d", m_Promoanz.GetBranchquotaqty());
        m_s[COL_PROMO_BRANCH_KUM].Format("%d", m_Promoanz.GetSoldqtybranch());
        m_s[COL_PROMO_IDF].Empty();
        m_s[COL_PROMO_APO].Empty();
        m_s[COL_PROMO_ORT].Empty();
        m_s[COL_PROMO_CST_QTY].Format("%d", m_Promoanz.GetCustomerquotaqty());
        m_s[COL_PROMO_CST_MIN].Format("%d", m_Promoanz.GetCustomerminqty());
        m_s[COL_PROMO_CST_KUM].Empty();
        FillList();
        m_Promoanzcst.SetBranchno(AeGetApp()->VzNr());
        m_Promoanzcst.SetPromotion_no(m_Promoanz.GetPromotion_no());
        m_Promoanzcst.SetArticleno(m_Promoanz.GetArticleno());
        for (;;)
        {
            if (m_Promoanzcst.SelListPromo() != SRV_OK)
                break;
            m_s[COL_PROMO_NUMMER].Empty();
            m_s[COL_PROMO_PROMO_NAME].Empty();
            m_s[COL_PROMO_PZN].Empty();
            m_s[COL_PROMO_BRANCH_QTY].Empty();
            m_s[COL_PROMO_BRANCH_KUM].Empty();
            m_s[COL_PROMO_IDF].Format("%d", m_Promoanzcst.GetCustomerno());
            m_s[COL_PROMO_APO] = m_Promoanzcst.GetNameapo(NameApo);
            m_s[COL_PROMO_ORT] = m_Promoanzcst.GetOrt(Ort);
            m_s[COL_PROMO_CST_QTY].Format("%d", m_Promoanzcst.GetCustomerquotaqty());
            m_s[COL_PROMO_CST_MIN].Format("%d", m_Promoanz.GetCustomerminqty());
            m_s[COL_PROMO_CST_KUM].Format("%d", m_Promoanzcst.GetSoldqtycst());
            FillList();
        }
        m_Promoanzcst.CloseCursor();
    }
    m_Promoanz.CloseCursor();

    EndWaitCursor();
    if (m_List1.GetItemCount() == 0)
    {
        MsgBoxOK(IDP_NO_DATA);
    }
}

BOOL CDPromoQuota::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    Columns[COL_PROMO_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_PROMO_NUMMER].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
    Columns[COL_PROMO_PROMO_NAME].Columns = CResString::ex().getStrTblText(AETXT_PROMOTION);
    Columns[COL_PROMO_PZN].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Columns[COL_PROMO_BRANCH_QTY].Columns = CResString::ex().getStrTblText(AETXT_PROMO_QTY);
    Columns[COL_PROMO_BRANCH_KUM].Columns = CResString::ex().getStrTblText(AETXT_PROMO_KUM);
    Columns[COL_PROMO_IDF].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[COL_PROMO_APO].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns[COL_PROMO_ORT].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[COL_PROMO_CST_QTY].Columns = CResString::ex().getStrTblText(AETXT_PROMO_QTY);
    Columns[COL_PROMO_CST_MIN].Columns = CResString::ex().getStrTblText(AETXT_MIN_QTY);
    Columns[COL_PROMO_CST_KUM].Columns = CResString::ex().getStrTblText(AETXT_PROMO_KUM);

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }
    m_s.SetSize(NUM_COLUMNS);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDPromoQuota::OnEnChangeEditIdf()
{
    CString str;

    m_edit_IDF.GetWindowText(str);                  //IDF lesen
    if (str.IsEmpty())
        return;                                     //Feld ist leer
    char chN = str[str.GetLength() - 1];            //letztes Zeichen lesen
    if (str.GetLength() == 1 && !isdigit(chN))
    {
        m_CMC = str;
        OnBnClickedButtonKunde();
        m_cKndNr.Format("%ld", m_lKunde);
        GetDlgItem(IDC_EDIT_IDF)->SetWindowText(m_cKndNr);
        m_edit_IDF.SetFocus();
        m_edit_IDF.SetSel(0, -1, FALSE);
        m_edit_IDF.SetSel(-1, 0, FALSE);            //Selektion aufheben
        return;
    }
    AllgWertKontr(&m_edit_IDF, MAXIMUM_IDF);
}

void CDPromoQuota::OnEnChangeEditPromono()
{
    CString str;

    m_edit_PromoNo.GetWindowText(str);              //IDF lesen
    if (str.IsEmpty())
        return;                                     //Feld ist leer
    char chN = str[str.GetLength() - 1];            //letztes Zeichen lesen
    if (str.GetLength() == 1 && !isdigit(chN))
    {
        m_CPromo = str;
        OnBnClickedButtonPromo();
        m_cPromoNr.Format("%ld", m_sPromo);
        GetDlgItem(IDC_EDIT_PROMONO)->SetWindowText(m_cPromoNr);
        m_edit_PromoNo.SetFocus();
        m_edit_PromoNo.SetSel(0, -1, FALSE);
        m_edit_PromoNo.SetSel(-1, 0, FALSE);        //Selektion aufheben
        return;
    }
    AllgWertKontr(&m_edit_PromoNo, MAXIMUM_IDF);
}

// List-Box mit Eintraegen versorgen
void CDPromoQuota::FillList()
{
    m_s[COL_PROMO_KB] = m_kb.Next();

    if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, m_s, 0))
    {
        EndWaitCursor();
    }
}
