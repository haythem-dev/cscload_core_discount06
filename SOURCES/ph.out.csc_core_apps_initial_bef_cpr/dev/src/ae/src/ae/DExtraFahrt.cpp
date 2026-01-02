// CExtraFahrt.cpp : implementation file
//

#include "stdafx.h"
#include "DExtraFahrt.h"

/////////////////////////////////////////////////////////////////////////////
// CCExtraFahrt dialog


CDExtraFahrt::CDExtraFahrt(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDExtraFahrt::IDD, pParent)
{
    m_CSonst = _T("");
    m_AArt = _T("");
}


void CDExtraFahrt::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_SONST, m_EditSonst);
    DDX_Text(pDX, IDC_EDIT_SONST, m_CSonst);
}


BEGIN_MESSAGE_MAP(CDExtraFahrt, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_SONST, OnChangeEditSonst)
    ON_BN_CLICKED(IDC_RADIO31, OnRadio31)
    ON_BN_CLICKED(IDC_RADIO32, OnRadio32)
    ON_BN_CLICKED(IDC_RADIO33, OnRadio33)
    ON_BN_CLICKED(IDC_RADIO34, OnRadio34)
    ON_BN_CLICKED(IDC_RADIO35, OnRadio35)
    ON_BN_CLICKED(IDC_RADIO36, OnRadio36)
    ON_BN_CLICKED(IDC_RADIO37, OnRadio37)
    ON_BN_CLICKED(IDC_RADIO38, OnRadio38)
    ON_BN_CLICKED(IDC_RADIO39, OnRadio39)
    ON_BN_CLICKED(IDC_RADIO40, OnRadio40)
    ON_BN_CLICKED(IDC_RADIO41, OnRadio41)
    ON_BN_CLICKED(IDC_RADIO42, OnRadio42)
    ON_BN_CLICKED(IDC_RADIO43, OnRadio43)
    ON_BN_CLICKED(IDC_RADIO44, OnRadio44)
    ON_BN_CLICKED(IDC_RADIO45, OnRadio45)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCExtraFahrt message handlers

void CDExtraFahrt::OnChangeEditSonst()
{
    AllgLaengeKontr(&m_EditSonst, MAXIMUM_AUFT_BEM, AeGetApp()->Modus());
}

void CDExtraFahrt::OnRadio31()
{
    GetDlgItem(IDC_RADIO31)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio32()
{
    GetDlgItem(IDC_RADIO32)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio33()
{
    GetDlgItem(IDC_RADIO33)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio34()
{
    GetDlgItem(IDC_RADIO34)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio35()
{
    GetDlgItem(IDC_RADIO35)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio36()
{
    GetDlgItem(IDC_RADIO36)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio37()
{
    GetDlgItem(IDC_RADIO37)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio38()
{
    GetDlgItem(IDC_RADIO38)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio39()
{
    GetDlgItem(IDC_RADIO39)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}
void CDExtraFahrt::OnRadio40()
{
    GetDlgItem(IDC_RADIO40)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio41()
{
    GetDlgItem(IDC_RADIO41)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio42()
{
    GetDlgItem(IDC_RADIO42)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio43()
{
    GetDlgItem(IDC_RADIO43)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio44()
{
    GetDlgItem(IDC_RADIO43)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnRadio45()
{
    GetDlgItem(IDC_RADIO43)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDExtraFahrt::OnOK()
{
    UpdateData();
    if (m_CSonst.IsEmpty())
    {
        MsgBoxOK(IDP_SONDER_GRUND);
        m_EditSonst.SetFocus();
        m_EditSonst.SetSel(0, -1, FALSE);
        return;
    }
    CDialogMultiLang::OnOK();
}

BOOL CDExtraFahrt::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_ButtonTab1[0] = GetDlgItem(IDC_RADIO31);
    m_ButtonTab1[1] = GetDlgItem(IDC_RADIO32);
    m_ButtonTab1[2] = GetDlgItem(IDC_RADIO33);
    m_ButtonTab1[3] = GetDlgItem(IDC_RADIO34);
    m_ButtonTab1[4] = GetDlgItem(IDC_RADIO35);
    m_ButtonTab1[5] = GetDlgItem(IDC_RADIO36);
    m_ButtonTab1[6] = GetDlgItem(IDC_RADIO37);
    m_ButtonTab1[7] = GetDlgItem(IDC_RADIO38);
    m_ButtonTab1[8] = GetDlgItem(IDC_RADIO39);
    m_ButtonTab1[9] = GetDlgItem(IDC_RADIO40);
    m_ButtonTab1[10] = GetDlgItem(IDC_RADIO41);
    m_ButtonTab1[11] = GetDlgItem(IDC_RADIO42);
    m_ButtonTab1[12] = GetDlgItem(IDC_RADIO43);
    m_ButtonTab1[13] = GetDlgItem(IDC_RADIO44);
    m_ButtonTab1[14] = GetDlgItem(IDC_RADIO45);

    ppString name;

    m_extrareasons.SetCscordertype(m_AArt);
    BeginWaitCursor();
    for (int i = 0; i < 16; i++)
    {
        if (m_extrareasons.SelList() != SRV_OK)
            break;
        m_ButtonTab1[i]->EnableWindow(TRUE);
        m_ButtonTab1[i]->ShowWindow(SW_SHOW);
        m_ButtonTab1[i]->SetWindowText(m_extrareasons.GetExtratourreason(name));
    }
    CheckRadioButton(IDC_RADIO31, IDC_RADIO45, IDC_RADIO31);
    OnRadio31();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDExtraFahrt::NoPrefix()
{
    CString CBuffer;
    for (int i = 0; i < m_CSonst.GetLength(); i++)
    {
        if (m_CSonst.GetAt(i) == '&')
        {
            CBuffer = m_CSonst.Left(i);
            CBuffer += m_CSonst.Right(m_CSonst.GetLength() - i - 1);
            m_CSonst = CBuffer;
        }
    }
    m_CSonst.MakeUpper();
    if (m_CSonst == CResString::ex().getStrTblText(AETXT_SONSTIGE_TEXT))
    {
        m_CSonst.Empty();
        m_EditSonst.SetFocus();
        m_EditSonst.SetSel(0, -1, FALSE);
    }
}
