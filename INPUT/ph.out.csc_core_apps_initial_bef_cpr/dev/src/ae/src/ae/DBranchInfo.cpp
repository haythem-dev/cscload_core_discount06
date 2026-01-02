// DBranchInfo.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <filialpartner.h>
#include "DBranchInfo.h"


// CDBranchInfo-Dialogfeld

IMPLEMENT_DYNAMIC(CDBranchInfo, CDialog)
CDBranchInfo::CDBranchInfo(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDBranchInfo::IDD, pParent)
    , m_CInfo(_T(""))
    , m_CInfo2(_T(""))
{
}

CDBranchInfo::~CDBranchInfo()
{
}

void CDBranchInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_INFO, m_edit_Info);
    DDX_Text(pDX, IDC_EDIT_INFO, m_CInfo);
    DDX_Control(pDX, IDC_EDIT_INFO2, m_edit_Info2);
    DDX_Text(pDX, IDC_EDIT_INFO2, m_CInfo2);
}


BEGIN_MESSAGE_MAP(CDBranchInfo, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_EN_CHANGE(IDC_EDIT_INFO, OnEnChangeEditInfo)
    ON_EN_CHANGE(IDC_EDIT_INFO, OnEnChangeEditInfo2)
END_MESSAGE_MAP()


// CDBranchInfo-Meldungshandler

BOOL CDBranchInfo::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    ppString text;

    m_Info.SetBranchno(AeGetApp()->VzNr());
    m_Info.SetBranchinfotype(0);
    if (!m_Info.SelInfo())
    {
        m_bupdate = TRUE;
        m_CInfo = m_Info.GetInformation(text);
    }
    else
    {
        m_bupdate = FALSE;
    }
    m_Info.SetBranchinfotype(1);
    if (!m_Info.SelInfo())
    {
        m_bupdate2 = TRUE;
        m_CInfo2 = m_Info.GetInformation(text);
    }
    else
    {
        m_bupdate2 = FALSE;
    }
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDBranchInfo::OnBnClickedOk()
{
    UpdateData();
    m_Info.SetBranchno(AeGetApp()->VzNr());
    m_Info.SetInformation(m_CInfo);
    m_Info.SetBranchinfotype(0);
    if (m_bupdate)
    {
        if (!m_Info.Update())
        {
            MsgBoxOK(IDS_SET_CHANGED);
        }
    }
    else
    {
        if (!m_Info.Insert())
        {
            MsgBoxOK(IDP_INSERTED);
        }
    }
    m_Info.SetInformation(m_CInfo2);
    m_Info.SetBranchinfotype(1);
    if (m_bupdate2)
    {
        if (!m_Info.Update())
        {
            MsgBoxOK(IDS_SET_CHANGED);
        }
    }
    else
    {
        if (!m_Info.Insert())
        {
            MsgBoxOK(IDP_INSERTED);
        }
    }
}

void CDBranchInfo::OnEnChangeEditInfo()
{
    m_edit_Info.GetWindowText(m_CInfo);
    if (m_CInfo.GetLength() > L_BRANCHINFO_INFORMATION)
    {
        int start, end;
        MsgBoxOK(IDS_TXT_MAX_ANZ_ZEICHEN);
        m_edit_Info.GetSel(start, end);
        m_edit_Info.SetWindowText(m_CInfo.Left(L_BRANCHINFO_INFORMATION));
        m_edit_Info.SetSel(start, end);
    }
}

void CDBranchInfo::OnEnChangeEditInfo2()
{
    m_edit_Info2.GetWindowText(m_CInfo2);
    if (m_CInfo2.GetLength() > L_BRANCHINFO_INFORMATION)
    {
        int start, end;
        MsgBoxOK(IDS_TXT_MAX_ANZ_ZEICHEN);
        m_edit_Info2.GetSel(start, end);
        m_edit_Info2.SetWindowText(m_CInfo.Left(L_BRANCHINFO_INFORMATION));
        m_edit_Info2.SetSel(start, end);
    }
}
