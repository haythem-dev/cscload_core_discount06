// DSonderFahrt.cpp : implementation file
//

#include "stdafx.h"
#include "DSonderFahrt.h"

/////////////////////////////////////////////////////////////////////////////
// CDSonderFahrt dialog


CDSonderFahrt::CDSonderFahrt(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSonderFahrt::IDD, pParent)
{
    m_CSonst = _T("");
}


void CDSonderFahrt::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_SONST, m_EditSonst);
    DDX_Text(pDX, IDC_EDIT_SONST, m_CSonst);
}


BEGIN_MESSAGE_MAP(CDSonderFahrt, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_SONST, OnChangeEditSonst)
    ON_BN_CLICKED(IDC_RADIO31, OnRadio31)
    ON_BN_CLICKED(IDC_RADIO32, OnRadio32)
    ON_BN_CLICKED(IDC_RADIO33, OnRadio33)
    ON_BN_CLICKED(IDC_RADIO34, OnRadio34)
    ON_BN_CLICKED(IDC_RADIO35, OnRadio35)
    ON_BN_CLICKED(IDC_RADIO39, OnRadio39)
    ON_BN_CLICKED(IDC_RADIO40, OnRadio40)
    ON_BN_CLICKED(IDC_RADIO41, OnRadio41)
    ON_BN_CLICKED(IDC_RADIO42, OnRadio42)
    ON_BN_CLICKED(IDC_RADIO36, OnRadio36)
    ON_BN_CLICKED(IDC_RADIO37, OnRadio37)
    ON_BN_CLICKED(IDC_RADIO38, OnRadio38)
    ON_BN_CLICKED(IDC_RADIO43, OnRadio43)
    ON_BN_CLICKED(IDC_RADIO45, OnRadio45)
    ON_BN_CLICKED(IDC_RADIO46, OnRadio46)
    ON_BN_CLICKED(IDC_RADIO47, OnRadio47)
    ON_BN_CLICKED(IDC_RADIO99, OnRadio99)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSonderFahrt message handlers

void CDSonderFahrt::OnChangeEditSonst()
{
   AllgLaengeKontr(&m_EditSonst, MAXIMUM_AUFT_BEM,AeGetApp()->Modus());
}

void CDSonderFahrt::OnRadio31()
{
    GetDlgItem(IDC_RADIO31)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio32()
{
    GetDlgItem(IDC_RADIO32)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio33()
{
    GetDlgItem(IDC_RADIO33)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio34()
{
    GetDlgItem(IDC_RADIO34)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio35()
{
    GetDlgItem(IDC_RADIO35)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio36()
{
    GetDlgItem(IDC_RADIO36)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio37()
{
    GetDlgItem(IDC_RADIO37)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio38()
{
    GetDlgItem(IDC_RADIO38)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio39()
{
    GetDlgItem(IDC_RADIO39)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}
void CDSonderFahrt::OnRadio40()
{
    GetDlgItem(IDC_RADIO40)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio41()
{
    GetDlgItem(IDC_RADIO41)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio42()
{
    GetDlgItem(IDC_RADIO42)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio43()
{
    GetDlgItem(IDC_RADIO43)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnOK()
{
    UpdateData();
    if (m_CSonst.IsEmpty())
    {
        MsgBoxOK(IDP_SONDER_GRUND);
        m_EditSonst.SetFocus();
        m_EditSonst.SetSel( 0, -1, FALSE );
        return;
    }
    CDialogMultiLang::OnOK();
}

BOOL CDSonderFahrt::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    if (!m_CSonst.IsEmpty())
    {
        CheckRadioButton(IDC_RADIO31,IDC_RADIO99,IDC_RADIO99);
        m_CText = m_CSonst;
        OnRadio99();
    }
    else
    {
        CheckRadioButton(IDC_RADIO31,IDC_RADIO99,IDC_RADIO31);
        OnRadio31();
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDSonderFahrt::NoPrefix()
{
    CString CBuffer;
    for (int i = 0; i < m_CSonst.GetLength();i++)
    {
        if (m_CSonst.GetAt(i) == '&')
        {
            CBuffer = m_CSonst.Left(i);
            CBuffer += m_CSonst.Right(m_CSonst.GetLength() - i - 1);
            m_CSonst = CBuffer;
        }
    }
    m_CSonst.MakeUpper();
}

void CDSonderFahrt::OnRadio45()
{
    GetDlgItem(IDC_RADIO45)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio46()
{
    GetDlgItem(IDC_RADIO46)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio47()
{
    GetDlgItem(IDC_RADIO47)->GetWindowText(m_CSonst);
    NoPrefix();
    m_EditSonst.SetWindowText(m_CSonst);
}

void CDSonderFahrt::OnRadio99()
{
    m_CSonst = m_CText;
    m_EditSonst.SetWindowText(m_CSonst);
    m_EditSonst.SetFocus();
    m_EditSonst.SetSel( 0, -1, FALSE );
}
