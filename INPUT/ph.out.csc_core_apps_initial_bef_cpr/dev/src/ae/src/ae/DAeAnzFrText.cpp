// DAeAnzFrText.cpp : implementation file
//

#include "stdafx.h"
#include "DAeAnzFrText.h"

/////////////////////////////////////////////////////////////////////////////
// CDAeAnzFrText dialog


CDAeAnzFrText::CDAeAnzFrText(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAeAnzFrText::IDD, pParent)
{
    m_CAePreis = _T("");
    m_CBemerk = _T("");
    m_CDarr = _T("");
    m_CEinh = _T("");
    m_CGrPreis = _T("");
    m_CMenge = _T("");
    m_CName = _T("");
    m_CRabDM = _T("");
    m_CRabProz = _T("");
}


void CDAeAnzFrText::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_STATIC_AEPREIS, m_CAePreis);
    DDX_Text(pDX, IDC_STATIC_BEMERK, m_CBemerk);
    DDX_Text(pDX, IDC_STATIC_DARR, m_CDarr);
    DDX_Text(pDX, IDC_STATIC_EINH, m_CEinh);
    DDX_Text(pDX, IDC_STATIC_GRPREIS, m_CGrPreis);
    DDX_Text(pDX, IDC_STATIC_MENGE, m_CMenge);
    DDX_Text(pDX, IDC_STATIC_NAME, m_CName);
    DDX_Text(pDX, IDC_STATIC_RAB_DM, m_CRabDM);
    DDX_Text(pDX, IDC_STATIC_RAB_PROZ, m_CRabProz);
    DDX_Control(pDX, IDC_COMBO_TAX, m_ComboTax);
}


BEGIN_MESSAGE_MAP(CDAeAnzFrText, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAeAnzFrText message handlers

BOOL CDAeAnzFrText::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    double dTax;
    CString Tax;
    char cStd;
    int rc;

    for (int i = 0;; i++)
    {
        rc = AeGetApp()->GetTaxRates(i, cStd, dTax);
        if (rc == -1)
            break;
        Tax.Format("%0.2lf %%", dTax);
        m_ComboTax.AddString(Tax);
    }

    CAUFPOSBUCH aufposbuch;
    aufposbuch.s.POSNR = m_posnr;
    aufposbuch.s.STATUS = m_datum;
    aufposbuch.s.KDAUFTRAGNR = m_auftragnr;
    aufposbuch.Server(AaauftSel_frt);
    if (aufposbuch.rc != SRV_OK)
        return TRUE;
    m_CBemerk = aufposbuch.s.BEMERKUNG;
    m_CDarr = aufposbuch.s.DARREICHFORM;
    m_CName = aufposbuch.s.ARTIKEL_NAME;
    m_CEinh = aufposbuch.s.EINHEIT;
    m_CAePreis.Format("%.2f", aufposbuch.s.PREISEKAPO);
    m_CGrPreis.Format("%.2f", aufposbuch.s.PREISEKGROSSO);
    m_CRabDM.Format("%.2f", aufposbuch.s.RABATTFESTDM);
    m_CRabProz.Format("%.2f", aufposbuch.s.RABATTFEST);
    m_CMenge.Format("%d", aufposbuch.s.MENGEABGEBUCHT);
    if (aufposbuch.s.PREISEKAPO != 0 || aufposbuch.s.PREISEKGROSSO != 0)
    {
        CheckRadioButton(IDC_RADIO10, IDC_RADIO13, IDC_RADIO12);
    }
    else if (aufposbuch.s.STATUS == ITEM_STAT_DISPO)
    {
        CheckRadioButton(IDC_RADIO10, IDC_RADIO13, IDC_RADIO10);
    }
    else if (aufposbuch.s.STATUS == ITEM_STAT_NACHLIEFERN)
    {
        CheckRadioButton(IDC_RADIO10, IDC_RADIO13, IDC_RADIO11);
    }
    else if (aufposbuch.s.STATUS == ITEM_STAT_NORMAL)
    {
        CheckRadioButton(IDC_RADIO10, IDC_RADIO13, IDC_RADIO13);
    }
    m_ComboTax.SetCurSel(atoi(aufposbuch.s.MWSTSCHLUESSEL));
    if (aufposbuch.s.TAXPFLICHTIG[0] == '1')
        CheckDlgButton(IDC_CHECK_TAX, TRUE);
    else
        CheckDlgButton(IDC_CHECK_TAX, FALSE);
    if (aufposbuch.s.RABATTFAEHIG[0] == '1')
        CheckDlgButton(IDC_CHECK_RABATT, TRUE);
    else
        CheckDlgButton(IDC_CHECK_RABATT, FALSE);
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
