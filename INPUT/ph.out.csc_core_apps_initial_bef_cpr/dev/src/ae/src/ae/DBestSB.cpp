// dbestsb.cpp : implementation file
//

#include "stdafx.h"
#include "DBestSB.h"

/////////////////////////////////////////////////////////////////////////////
// CDBestSB dialog


CDBestSB::CDBestSB(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDBestSB::IDD, pParent)
{
    m_ArtName = _T("");
    m_ArtEinheit = _T("");
    m_ArtNr = _T("");
    m_CDarreichform = _T("");
}


void CDBestSB::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_ART_NAME, m_ArtName);
    DDX_Text(pDX, IDC_ART_EINH, m_ArtEinheit);
    DDX_Text(pDX, IDC_ART_NR, m_ArtNr);
    DDX_Text(pDX, IDC_ART_DARR, m_CDarreichform);
}


BEGIN_MESSAGE_MAP(CDBestSB, CDialogMultiLang)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDBestSB message handlers

BOOL CDBestSB::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
