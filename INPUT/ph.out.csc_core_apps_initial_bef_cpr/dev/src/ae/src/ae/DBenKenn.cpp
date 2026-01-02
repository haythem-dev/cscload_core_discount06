// dbenkenn.cpp : implementation file
//

#include "stdafx.h"
#include "dbenkenn.h"

/////////////////////////////////////////////////////////////////////////////
// CDBenKenn dialog


CDBenKenn::CDBenKenn(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDBenKenn::IDD, pParent)
{
    m_edit_kennung = _T("");
    m_edit_pwd = _T("");
}


void CDBenKenn::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_KENNUNG, m_edit_kennung);
    DDV_MaxChars(pDX, m_edit_kennung, 8);
    DDX_Text(pDX, IDC_EDIT_PWD, m_edit_pwd);
    DDV_MaxChars(pDX, m_edit_pwd, 8);
}


BEGIN_MESSAGE_MAP(CDBenKenn, CDialogMultiLang)
    ON_BN_CLICKED(ID_ENDE, OnEnde)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDBenKenn message handlers

void CDBenKenn::OnEnde()
{
    CDialogMultiLang::OnOK();
}

void CDBenKenn::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_EDIT_KENNUNG))
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_PWD));
    else
        CDialogMultiLang::OnOK();
}
