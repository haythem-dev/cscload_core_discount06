// DSeperateOrder.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <controlling.h>
#include "DSeperateOrder.h"


// CDSeperateOrder-Dialogfeld

IMPLEMENT_DYNAMIC(CDSeperateOrder, CDialog)
CDSeperateOrder::CDSeperateOrder(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDSeperateOrder::IDD, pParent)
{
    m_bChanged = FALSE;
    m_bExist = FALSE;
}

CDSeperateOrder::~CDSeperateOrder()
{
}

void CDSeperateOrder::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK1, m_CB_1);
    DDX_Control(pDX, IDC_CHECK2, m_CB_2);
    DDX_Control(pDX, IDC_CHECK3, m_CB_3);
    DDX_Control(pDX, IDC_CHECK4, m_CB_4);
    DDX_Control(pDX, IDC_CHECK5, m_CB_5);
    DDX_Control(pDX, IDC_CHECK99, m_CB_99);
}


BEGIN_MESSAGE_MAP(CDSeperateOrder, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_CHECK2, OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK3, OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK4, OnBnClickedCheck4)
    ON_BN_CLICKED(IDC_CHECK5, OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK99, OnBnClickedCheck99)
END_MESSAGE_MAP()


// CDSeperateOrder-Meldungshandler

BOOL CDSeperateOrder::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    m_Sep.SetBranchno(AeGetApp()->VzNr());
    if (!m_Sep.Sel())
    {
        m_bExist = TRUE;
        if (m_Sep.GetNarcotic() == '1') m_CB_1.SetCheck(BST_CHECKED);
        if (m_Sep.GetColdchain() == '1') m_CB_2.SetCheck(BST_CHECKED);
        if (m_Sep.GetCool08() == '1') m_CB_3.SetCheck(BST_CHECKED);
        if (m_Sep.GetCool20() == '1') m_CB_4.SetCheck(BST_CHECKED);
        if (m_Sep.GetReservehospital() == '1') m_CB_5.SetCheck(BST_CHECKED);
        if (m_Sep.GetDeferorder() == '1') m_CB_99.SetCheck(BST_CHECKED);
    }


    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDSeperateOrder::OnBnClickedOk()
{
    if (m_bChanged)
    {
        m_Sep.SetNarcotic(m_CB_1.GetCheck() == BST_CHECKED ? '1' : '0');
        m_Sep.SetColdchain(m_CB_2.GetCheck() == BST_CHECKED ? '1' : '0');
        m_Sep.SetCool08(m_CB_3.GetCheck() == BST_CHECKED ? '1' : '0');
        m_Sep.SetCool20(m_CB_4.GetCheck() == BST_CHECKED ? '1' : '0');
        m_Sep.SetReservehospital(m_CB_5.GetCheck() == BST_CHECKED ? '1' : '0');
        m_Sep.SetDeferorder(m_CB_99.GetCheck() == BST_CHECKED ? '1' : '0');
        m_bExist ? m_Sep.Update() : m_Sep.Insert();
    }
    CDialogMultiLang::OnOK();
}

void CDSeperateOrder::OnBnClickedCheck1()
{
    m_bChanged = TRUE;
}

void CDSeperateOrder::OnBnClickedCheck2()
{
    m_bChanged = TRUE;
}

void CDSeperateOrder::OnBnClickedCheck3()
{
    m_bChanged = TRUE;
}

void CDSeperateOrder::OnBnClickedCheck4()
{
    m_bChanged = TRUE;
}

void CDSeperateOrder::OnBnClickedCheck5()
{
    m_bChanged = TRUE;
}

void CDSeperateOrder::OnBnClickedCheck99()
{
    m_bChanged = TRUE;
}
