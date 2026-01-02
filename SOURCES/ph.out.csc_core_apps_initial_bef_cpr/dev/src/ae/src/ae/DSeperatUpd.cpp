// DSeperatUpd.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <controlling.h>
#include "DSeperatUpd.h"


// CDSeperatUpd-Dialogfeld

IMPLEMENT_DYNAMIC(CDSeperatUpd, CDialog)
CDSeperatUpd::CDSeperatUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSeperatUpd::IDD, pParent)
    , m_bDefer(FALSE)
    , m_cHerst(_T(""))
{
    m_sKind = 0;
    m_sFunktion = 0;
    m_sGruppe = 0;
    m_cAArt.Empty();
    m_cKoArt.Empty();
    m_cBuArt.Empty();
}

CDSeperatUpd::~CDSeperatUpd()
{
}

void CDSeperatUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_GRP, m_Cobox_Grp);
    DDX_Control(pDX, IDC_COMBO_AART, m_Cobox_AArt);
    DDX_Control(pDX, IDC_COMBO_KOART, m_Cobox_KoArt);
    DDX_Control(pDX, IDC_COMBO_BUART, m_Cobox_BuArt);
    DDX_Control(pDX, IDC_CHECK_DEFER, m_CB_Defer);
    DDX_Check(pDX, IDC_CHECK_DEFER, m_bDefer);
    DDX_Control(pDX, IDC_EDIT_HERST, m_edit_Herst);
    DDX_Text(pDX, IDC_EDIT_HERST, m_cHerst);
}


BEGIN_MESSAGE_MAP(CDSeperatUpd, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_CBN_SELCHANGE(IDC_COMBO_GRP, OnCbnSelchangeComboGrp)
END_MESSAGE_MAP()


// CDSeperatUpd-Meldungshandler

BOOL CDSeperatUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CString AArt;
    int rc;
    m_Cobox_AArt.ResetContent();
    AArt.Format("   -%s", CResString::ex().getStrTblText(AETXT_KEINE_VORGABE).GetString());
    m_Cobox_AArt.AddString(AArt);
    for (int i = 0;; i++)
    {
        rc = GetOrderType().GetAufArtenListeVZ(AeGetApp()->VzNr(), i, AArt);
        if (rc == -1)
            break;
        m_Cobox_AArt.AddString(AArt);
    }
    m_Cobox_AArt.SetCurSel(m_sFunktion ? 0 : m_Cobox_AArt.FindString(-1, m_cAArt));

    CString BuArt;
    m_Cobox_BuArt.ResetContent();
    BuArt.Format("   -%s", CResString::ex().getStrTblText(AETXT_KEINE_VORGABE).GetString());
    m_Cobox_BuArt.AddString(BuArt);
    for (int i = 0;; i++)
    {
        rc = AeGetApp()->GetBuArtenListeVZ(AeGetApp()->VzNr(), i, BuArt);
        if (rc == -1)
            break;
        m_Cobox_BuArt.AddString(BuArt);
    }
    m_Cobox_BuArt.SetCurSel(m_sFunktion ? 0 : m_Cobox_BuArt.FindString(-1, m_cBuArt));

    CString KoArt;
    m_Cobox_KoArt.ResetContent();
    KoArt.Format("   -%s", CResString::ex().getStrTblText(AETXT_KEINE_VORGABE).GetString());
    m_Cobox_KoArt.AddString(KoArt);
    for (int i = 0;; i++)
    {
        rc = AeGetApp()->GetKoArtenListeVZ(AeGetApp()->VzNr(), i, KoArt);
        if (rc == -1)
            break;
        m_Cobox_KoArt.AddString(KoArt);
    }
    m_Cobox_KoArt.SetCurSel(m_sFunktion ? 0 : m_Cobox_KoArt.FindString(-1, m_cKoArt));

    m_Cobox_Grp.ResetContent();
    for (int i = 0; i < m_Gruppen->GetCount(); i++)
    {
        m_Cobox_Grp.AddString(m_Gruppen->GetAt(i));
    }
    m_Cobox_Grp.SetCurSel(m_sGruppe);
    if (!m_sFunktion)
    {
        GetDlgItem(IDC_COMBO_GRP)->EnableWindow(FALSE);
        if (m_sGruppe == 14 || m_sGruppe == 15)
        {
            GetDlgItem(IDC_CHECK_DEFER)->EnableWindow(FALSE);
            GetDlgItem(IDC_EDIT_HERST)->ShowWindow(SW_SHOW);
            GetDlgItem(IDC_EDIT_HERST)->EnableWindow(FALSE);
        }
    }
    GetDlgItem(IDC_COMBO_BUART)->EnableWindow(FALSE);
    if (AeGetApp()->IsRS() || AeGetApp()->IsBG())
    {
        GetDlgItem(IDC_COMBO_AART)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_COMBO_AART)->EnableWindow(TRUE);
    }
    else
    {
        GetDlgItem(IDC_COMBO_AART)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_COMBO_AART)->EnableWindow(FALSE);
    }
    GetDlgItem(IDC_COMBO_BUART)->ShowWindow(SW_HIDE);
    m_bSaveDefer = m_bDefer;

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDSeperatUpd::OnBnClickedOk()
{
    UpdateData();
    int sel;

    CString Text;
    ppString ppText;
    if (m_sKind == 1)
    {
        m_SepOrderCst->SetBranchno(AeGetApp()->VzNr());
        m_SepOrderCst->SetArtgrp(static_cast<short>(m_Cobox_Grp.GetCurSel()));
        m_SepOrderCst->SetCustomerno(m_iKndNr);
    }
    else
    {
        m_SepOrder->SetBranchno(AeGetApp()->VzNr());
        m_SepOrder->SetArtgrp(static_cast<short>(m_Cobox_Grp.GetCurSel()));
        m_SepOrder->SetManufacturerno(atoi(m_cHerst));
    }

    sel = m_Cobox_KoArt.GetCurSel();
    m_Cobox_KoArt.GetLBText(sel, Text);
    if (m_sKind == 1)
    {
        m_SepOrderCst->SetKoart(Text.GetAt(0));
    }
    else
    {
        m_SepOrder->SetKoart(Text.GetAt(0));
    }

    if (AeGetApp()->IsRS() || AeGetApp()->IsBG())
    {
        sel = m_Cobox_AArt.GetCurSel();
        m_Cobox_AArt.GetLBText(sel, Text);
        if (m_sKind == 1)
        {
            m_SepOrderCst->SetKdauftragart(Text.Left(2));
        }
        else
        {
            m_SepOrder->SetKdauftragart(Text.Left(2));
        }
    }
    if (m_Cobox_Grp.GetCurSel() == 14 || m_Cobox_Grp.GetCurSel() == 15)
    {
        if (atoi(m_cHerst) == 0)
        {
            MsgBoxOK(AETXT_NR_INPUT);
            return;
        }
    }

    if (m_CB_Defer.GetCheck())
    {
        if (m_sKind == 1)
        {
            m_SepOrderCst->SetDeferorder('1');
        }
        else
        {
            m_SepOrder->SetDeferorder('1');
        }
    }
    else
    {
        if (m_sKind == 1)
        {
            m_SepOrderCst->SetDeferorder('0');
        }
        else
        {
            m_SepOrder->SetDeferorder('0');
        }
    }

    if (!m_sFunktion)
    {
        if (m_sKind == 1)
        {
            m_SepOrderCst->Update();
        }
        else
        {
            m_SepOrder->Update();
        }
    }
    else
    {
        if (m_sKind == 1)
        {
            m_SepOrderCst->Insert();
        }
        else
        {
            m_SepOrder->Insert();
        }
    }
    CDialogMultiLang::OnOK();
}

void CDSeperatUpd::OnCbnSelchangeComboGrp()
{
    if (m_Cobox_Grp.GetCurSel() == 14 || m_Cobox_Grp.GetCurSel() == 15)
    {
        m_bSaveDefer = IsDlgButtonChecked(IDC_CHECK_DEFER);
        CheckDlgButton(IDC_CHECK_DEFER,TRUE);
        GetDlgItem(IDC_CHECK_DEFER)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_HERST)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_HERST)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_HERST)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_HERST)->EnableWindow(TRUE);
        if (m_Cobox_Grp.GetCurSel() == 15)
        {
            GetDlgItem(IDC_STATIC_HERST)->SetWindowText((char *)CResString::ex().getStrTblText(AETXT_KONSIGPARTNER).GetString());
        }
    }
    else
    {
        CheckDlgButton(IDC_CHECK_DEFER, m_bSaveDefer);
        GetDlgItem(IDC_CHECK_DEFER)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_HERST)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_HERST)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_HERST)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_HERST)->EnableWindow(FALSE);
    }
}
