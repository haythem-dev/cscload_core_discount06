// DViewKnd.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "AeFView.h"
#include <customer.h>
#include "DViewKnd.h"


// CDViewKnd-Dialogfeld

CDViewKnd::CDViewKnd(CView* pView)
{
    m_pView = pView;
    m_bVersion = false;
}

IMPLEMENT_DYNAMIC(CDViewKnd, CDialog)
CDViewKnd::CDViewKnd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDViewKnd::IDD, pParent)
{
    m_dKLWert1 = 0;
    m_dKLWert2 = 0;
//  m_dKLWert3 = 0;
    m_bVersion = false;
}

CDViewKnd::~CDViewKnd()
{
}

void CDViewKnd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_INFO, m_cs_Info);
}


BEGIN_MESSAGE_MAP(CDViewKnd, CDialogMultiLang)
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDViewKnd-Meldungshandler

BOOL CDViewKnd::Create()
{
    return CDialogMultiLang::Create(CDViewKnd::IDD);
}

BOOL CDViewKnd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CFont*  pobjCFont;
    CFont  objCFont;
    LOGFONT lf;

    pobjCFont = m_cs_Info.GetFont();
    pobjCFont->GetLogFont(&lf);
    lf.lfWeight *= 2;
    objCFont.CreateFontIndirect(&lf);

    m_cs_Info.SetFont(&objCFont);

    RepositionWindow();

    InitalWerte();

    this->EnableWindow(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDViewKnd::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
}

void CDViewKnd::OnCancel()
{
/*  if (m_pView != NULL)
    {
        // falls nichtmodales Dialogfeld, OnCancel-Funktion der
        // Basisklasse nicht aufrufen
        m_pView->PostMessage(WM_GOODBYEKND, IDCANCEL);
    }
    else
    {
        CDialogMultiLang::OnCancel();   // falls modales Dialogfeld
    }*/
}

void CDViewKnd::RepositionWindow()
{
    CRect rectDesk;
    CRect rectWin;

    GetDesktopWindow()->GetWindowRect( &rectDesk );   //fullscreen
    GetWindowRect( &rectWin );

    /* set to the left,upper corner */
    int iLeft  = rectDesk.BottomRight().x - rectWin.Width() - 2;
    int iTop   = rectDesk.BottomRight().y - rectWin.Height() - 50;
    int iRight = rectDesk.BottomRight().x - 2;
    int iBottom = rectDesk.BottomRight().y - 50;

    rectWin.SetRect( iLeft, iTop, iRight, iBottom);
    MoveWindow(rectWin);
}

void CDViewKnd::SetAndShowCreditLimitValue1(double creditValue)
{
    m_dKLWert1 = creditValue;
    ShowCreditLimitValue(m_dKLWert1, 1);
}

void CDViewKnd::SetAndShowCreditLimitValue2(double creditValue)
{
    m_dKLWert2 = creditValue;
    ShowCreditLimitValue(m_dKLWert2, 2);
}

/*
void CDViewKnd::SetAndShowCreditLimitValue3(double creditValue)
{
    m_dKLWert3 = creditValue;
    ShowCreditLimitValue(m_dKLWert3, 3);
}
*/

void CDViewKnd::ShowCreditLimitValue(double creditValue, const short creditLimitControlNo)
{
    int idLabel;
    int idValue;
    GetCreditLimitControlIds(creditLimitControlNo, idLabel, idValue);

    CString sCreditValue;
    sCreditValue.Format("%0.2lf", creditValue);
    GetDlgItem(idValue)->SetWindowText(sCreditValue);
}

HBRUSH CDViewKnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_STATIC_KL_WERT1)
        pDC->SetTextColor(wert_kl1);
    else if (pWnd->GetDlgCtrlID() ==    IDC_STATIC_KL_WERT2)
        pDC->SetTextColor(wert_kl2);
//  else if (pWnd->GetDlgCtrlID() ==    IDC_STATIC_KL_WERT3)
//      pDC->SetTextColor(wert_kl3);
    else if (pWnd->GetDlgCtrlID() ==    IDC_STATIC_APOL)
        pDC->SetTextColor(liz_apo);
    else if (pWnd->GetDlgCtrlID() ==    IDC_STATIC_BTML)
        pDC->SetTextColor(liz_btm);
    else if (pWnd->GetDlgCtrlID() ==    IDC_STATIC_KK)
        pDC->SetTextColor(is_kk);
    else if (pWnd->GetDlgCtrlID() ==    IDC_STATIC_EH)
        pDC->SetTextColor(is_eh);
    else if (pWnd->GetDlgCtrlID() ==    IDC_STATIC_ZZ_WERT)
        pDC->SetTextColor(wert_fv);
    else if (pWnd->GetDlgCtrlID() ==    IDC_STATIC_ZZ_WERT_KK)
        pDC->SetTextColor(wert_kk);
    else if (pWnd->GetDlgCtrlID() ==    IDC_STATIC_ZZ_WERT_L5)
        pDC->SetTextColor(wert_l5);
    else if (pWnd->GetDlgCtrlID() ==    IDC_STATIC_INFO)
        pDC->SetTextColor(RGB(250,0,0));
    this->EnableWindow(FALSE);
    return hbr;
}

void CDViewKnd::InitalWerte()
{
    InitCreditLimitValues();

    CKUNDELIZENSEN liz;
    liz.SetVertriebszentrumnr(m_sFilialnr);
    liz.SetKundennr(m_lKndNr);
    liz.SelLicenses();

    ppString ApoL;
    liz.GetApolizens(ApoL);
    CString cApoL = ApoL;
    liz_apo = cApoL.IsEmpty() ? RGB(250,0,0) : RGB(0, 0, 250);
    GetDlgItem(IDC_STATIC_APOL)->SetWindowText(cApoL.IsEmpty() ? CResString::ex().getStrTblText(AETXT_KEINE) : ApoL);

    ppString BTML;
    liz.GetBtmlizens(BTML);
    CString cBTML = BTML;
    liz_btm = cBTML.IsEmpty() ? RGB(250, 0, 0) : RGB(0, 0, 250);
    GetDlgItem(IDC_STATIC_BTML)->SetWindowText(cBTML.IsEmpty() ? CResString::ex().getStrTblText(AETXT_KEINE) : BTML);

    is_kk = AeGetApp()->IsKndKasse() ? RGB(0, 0, 250) : RGB(250, 0, 0);
    GetDlgItem(IDC_STATIC_KK)->SetWindowText(CResString::ex().getStrTblText(AeGetApp()->IsKndKasse() ? AETXT_JA : AETXT_NEIN));

    is_eh = AeGetApp()->IsKndRetail() ? RGB(0, 0, 250) : RGB(250, 0, 0);
    GetDlgItem(IDC_STATIC_EH)->SetWindowText(CResString::ex().getStrTblText(AeGetApp()->IsKndRetail() ? AETXT_JA : AETXT_NEIN));

    GetDlgItem(IDC_STATIC_ZZ_TEXT)->EnableWindow(TRUE);
    GetDlgItem(IDC_STATIC_ZZ_TEXT)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_ZZ_WERT)->EnableWindow(TRUE);
    GetDlgItem(IDC_STATIC_ZZ_WERT)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_ZZ_WERT)->SetWindowText(CResString::ex().getStrTblText(AETXT_BAR));
    GetDlgItem(IDC_STATIC_ZZ_TEXT_KK)->EnableWindow(TRUE);
    GetDlgItem(IDC_STATIC_ZZ_TEXT_KK)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_ZZ_WERT_KK)->EnableWindow(TRUE);
    GetDlgItem(IDC_STATIC_ZZ_WERT_KK)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_ZZ_WERT_KK)->SetWindowText(CResString::ex().getStrTblText(AETXT_BAR));
    GetDlgItem(IDC_STATIC_ZZ_TEXT_L5)->EnableWindow(TRUE);
    GetDlgItem(IDC_STATIC_ZZ_TEXT_L5)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_ZZ_WERT_L5)->EnableWindow(TRUE);
    GetDlgItem(IDC_STATIC_ZZ_WERT_L5)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_ZZ_WERT_L5)->SetWindowText(CResString::ex().getStrTblText(AETXT_BAR));

    wert_fv = RGB(250, 0, 0);
    wert_kk = RGB(250, 0, 0);
    wert_l5 = RGB(250, 0, 0);

    CCSTPAYTERM pt;
    pt.SetBranchno(m_sFilialnr);
    pt.SetCustomerno(m_lKndNr);

    while (pt.SelList() == SRV_OK)
    {
        int ctrlId;
        COLORREF* pColorValue = NULL;

        switch (pt.GetPreis_typ())
        {
        case 0:
            ctrlId = IDC_STATIC_ZZ_WERT;
            pColorValue = &wert_fv;
            break;
        case 1:
            ctrlId = IDC_STATIC_ZZ_WERT_KK;
            pColorValue = &wert_kk;
            break;
        case 5:
            ctrlId = IDC_STATIC_ZZ_WERT_L5;
            pColorValue = &wert_l5;
            break;
        default:
            continue;
        }

        if (pt.GetPaymentarget() == 0)
        {
            GetDlgItem(ctrlId)->SetWindowText(CResString::ex().getStrTblText(AETXT_BAR));
            *pColorValue = RGB(250, 0, 0);
        }
        else
        {
            CString ZZ;
            ZZ.Format("%d", pt.GetPaymentarget());
            *pColorValue = RGB(0, 0, 250);
            GetDlgItem(ctrlId)->SetWindowText(ZZ);
        }
    }
}

void CDViewKnd::InitCreditLimitValues()
{
    m_dKLWert1 = 0.0;
    m_dKLWert2 = 0.0;

    CKREDITLIMIT kl;
    kl.SetKundennr(m_lKndNr);
    kl.SetVertriebszentrumnr(m_sFilialnr);

    if (m_bVersion)
    {
/* alt */
        if ((kl.SelLimit() != SRV_OK) || (kl.GetLimit() == 0))
        {
            HideCreditLimitLine(2);
        }
        else
        {
            ShowCreditLimitLine(2, kl);
        }
    }
    else
    {
/* neu */
        if ((kl.SelLimit2() != SRV_OK) || (kl.GetLimit() == 0))
        {
            HideCreditLimitLine(2);
        }
        else
        {
            ShowCreditLimitLine(2, kl);
        }
        if (kl.SelLimitMain() != SRV_OK)
        {
            if ((kl.SelLimit1() != SRV_OK) || (kl.GetLimit() == 0))
            {
                HideCreditLimitLine(1);
            }
            else
            {
                ShowCreditLimitLine(1, kl);
            }
        }
        else if (kl.GetLimit() == 0)
        {
            HideCreditLimitLine(1);
        }
        else
        {
            ShowCreditLimitLine(1, kl);
        }
    }
}

void CDViewKnd::ShowCreditLimitLine(const short creditLimitControlNo, CKREDITLIMIT& kl)
{
    int idLabel;
    int idValue;
    GetCreditLimitControlIds(creditLimitControlNo, idLabel, idValue);

    GetDlgItem(idLabel)->EnableWindow(TRUE);
    GetDlgItem(idLabel)->ShowWindow(SW_SHOW);
    GetDlgItem(idValue)->EnableWindow(TRUE);
    GetDlgItem(idValue)->ShowWindow(SW_SHOW);

    double creditValue = kl.GetLimit() - kl.GetSum_debitside() - kl.GetSum_dayturnover() + kl.GetSum_returns();

    switch (creditLimitControlNo)
    {
    case 1:
        wert_kl1 = RGB(0, 0, 250);
        SetAndShowCreditLimitValue1(creditValue);
        break;
    case 2:
        wert_kl2 = RGB(0, 0, 250);
        SetAndShowCreditLimitValue2(creditValue);
        break;
//  case 3:
//      wert_kl3 = RGB(0, 0, 250);
//      SetAndShowCreditLimitValue3(creditValue);
//      break;
    default:
        assert(0);
        break;
    }
}

void CDViewKnd::HideCreditLimitLine(const short creditLimitControlNo)
{
    int idLabel;
    int idValue;
    GetCreditLimitControlIds(creditLimitControlNo, idLabel, idValue);

    GetDlgItem(idLabel)->EnableWindow(FALSE);
    GetDlgItem(idLabel)->ShowWindow(SW_HIDE);
    GetDlgItem(idValue)->EnableWindow(FALSE);
    GetDlgItem(idValue)->ShowWindow(SW_HIDE);

    switch (creditLimitControlNo)
    {
    case 1:
        wert_kl1 = RGB(250, 0, 0);
        break;
    case 2:
        wert_kl2 = RGB(250, 0, 0);
        break;
//  case 3:
//      wert_kl3 = RGB(250, 0, 0);
//      break;
    default:
        assert(0);
        break;
    }
}

void CDViewKnd::ResetCreditLimitValues()
{
    CKREDITLIMIT kl;
    kl.SetKundennr(m_lKndNr);
    kl.SetVertriebszentrumnr(m_sFilialnr);

    if (m_bVersion)
    {
/* alt */
        if (!kl.SelLimit() && (kl.GetLimit() > 0.0))
        {
            double creditLimit = kl.GetLimit() - kl.GetSum_debitside() - kl.GetSum_dayturnover();
            SetAndShowCreditLimitValue2(creditLimit);
        }
    }
    else
    {
/* neu */
        if (!kl.SelLimit2()&& (kl.GetLimit() > 0.0))
        {
            double creditLimit = kl.GetLimit() - kl.GetSum_debitside() - kl.GetSum_dayturnover();
            SetAndShowCreditLimitValue2(creditLimit);
        }
        if (kl.SelLimitMain())
        {
            if (!kl.SelLimit1() && (kl.GetLimit() > 0.0))
            {
                double creditLimit = kl.GetLimit() - kl.GetSum_debitside() - kl.GetSum_dayturnover();
                SetAndShowCreditLimitValue1(creditLimit);
            }
        }
        else if (kl.GetLimit() > 0.0)
        {
            double creditLimit = kl.GetLimit() - kl.GetSum_debitside() - kl.GetSum_dayturnover();
            SetAndShowCreditLimitValue1(creditLimit);
        }
    }
}

void CDViewKnd::UpdateCreditLimitValues()
{
    CKREDITLIMIT kl;
    kl.SetKundennr(m_lKndNr);
    kl.SetVertriebszentrumnr(m_sFilialnr);

    if (!kl.SelLimit2() && (kl.GetLimit() > 0.0))
    {
        double creditLimit = kl.GetLimit() - kl.GetSum_debitside() - kl.GetSum_dayturnover() + kl.GetSum_returns();
        SetAndShowCreditLimitValue2(creditLimit);
    }
    if (kl.SelLimitMain())
    {
        if (!kl.SelLimit1() && (kl.GetLimit() > 0.0))
        {
            double creditLimit = kl.GetLimit() - kl.GetSum_debitside() - kl.GetSum_dayturnover() + kl.GetSum_returns();
            SetAndShowCreditLimitValue1(creditLimit);
        }
    }
    else if (kl.GetLimit() > 0.0)
    {
        double creditLimit = kl.GetLimit() - kl.GetSum_debitside() - kl.GetSum_dayturnover() + kl.GetSum_returns();
        SetAndShowCreditLimitValue1(creditLimit);
    }
}

void CDViewKnd::GetCreditLimitControlIds(const short creditLimitControlNo, int& idLabel, int& idValue)
{
    switch (creditLimitControlNo)
    {
    case 1:
        idLabel = IDC_STATIC_KL1;
        idValue = IDC_STATIC_KL_WERT1;
        break;
    case 2:
        idLabel = IDC_STATIC_KL2;
        idValue = IDC_STATIC_KL_WERT2;
        break;
    case 3:
        idLabel = IDC_STATIC_KL3;
        idValue = IDC_STATIC_KL_WERT3;
        break;
    default:
        idLabel = 0;
        idValue = 0;
        break;
    }
}

double CDViewKnd::GetCreditLimitValue1()
{
    return m_dKLWert1;
}

double CDViewKnd::GetCreditLimitValue2()
{
    return m_dKLWert2;
}

/*
double CDViewKnd::GetCreditLimitValue3()
{
    return m_dKLWert3;
}
*/
