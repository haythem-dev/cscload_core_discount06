// DDelayedArt.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artikel.h>
#include "DDelayedArt.h"


// CDDelayedArt-Dialogfeld

IMPLEMENT_DYNAMIC(CDDelayedArt, CDialog)
CDDelayedArt::CDDelayedArt(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDDelayedArt::IDD, pParent)
{
    m_bChanged = FALSE;
    m_bExist = FALSE;
}

CDDelayedArt::~CDDelayedArt()
{
}

void CDDelayedArt::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK1, m_CB_1);
    DDX_Control(pDX, IDC_CHECK2, m_CB_2);
    DDX_Control(pDX, IDC_CHECK3, m_CB_3);
    DDX_Control(pDX, IDC_CHECK4, m_CB_4);
}


BEGIN_MESSAGE_MAP(CDDelayedArt, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK2, OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK3, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK4, OnBnClickedCheck4)
END_MESSAGE_MAP()


// CDDelayedArt-Meldungshandler

BOOL CDDelayedArt::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    m_Art.SetBranchno(AeGetApp()->VzNr());
    if (!m_Art.Sel())
    {
        m_bExist = TRUE;
        if (m_Art.GetNarcotic() == '1') m_CB_1.SetCheck(BST_CHECKED);
        if (m_Art.GetColdchain() == '1') m_CB_2.SetCheck(BST_CHECKED);
        if (m_Art.GetCool08() == '1') m_CB_3.SetCheck(BST_CHECKED);
        if (m_Art.GetCool20() == '1') m_CB_4.SetCheck(BST_CHECKED);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDDelayedArt::OnBnClickedOk()
{
    if (m_bChanged)
    {
        m_Art.SetNarcotic(m_CB_1.GetCheck() == BST_CHECKED ? '1' : '0');
        m_Art.SetColdchain(m_CB_2.GetCheck() == BST_CHECKED ? '1' : '0');
        m_Art.SetCool08(m_CB_3.GetCheck() == BST_CHECKED ? '1' : '0');
        m_Art.SetCool20(m_CB_4.GetCheck() == BST_CHECKED ? '1' : '0');
        m_bExist ? m_Art.Update() : m_Art.Insert();
    }
    CDialogMultiLang::OnOK();
}

void CDDelayedArt::OnBnClickedCheck1()
{
    m_bChanged = TRUE;
}

void CDDelayedArt::OnBnClickedCheck2()
{
    m_bChanged = TRUE;
}

void CDDelayedArt::OnBnClickedCheck3()
{
    m_bChanged = TRUE;
}

void CDDelayedArt::OnBnClickedCheck4()
{
    m_bChanged = TRUE;
}
