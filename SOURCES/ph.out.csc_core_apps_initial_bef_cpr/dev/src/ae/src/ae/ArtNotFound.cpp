// ArtNotFound.cpp : implementation file
//

#include "stdafx.h"
#include "ArtNotFound.h"
#include "DInfoListe.h"


// CArtNotFound dialog

IMPLEMENT_DYNAMIC(CArtNotFound, CDialog)

CArtNotFound::CArtNotFound(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CArtNotFound::IDD, pParent)
    , m_cFehltext(_T(""))
    , m_cBezeichnung(_T(""))
    , m_bNoShort(FALSE)
    , m_bAufnahme(FALSE)
{
    m_lArtNo = 0;
}

CArtNotFound::~CArtNotFound()
{
}

void CArtNotFound::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_FEHLTEXT, m_cFehltext);
}


BEGIN_MESSAGE_MAP(CArtNotFound, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_GOOGLE, OnButtonGoogle)
    ON_BN_CLICKED(IDC_BUTTON_INFO, OnButtonInfo)
END_MESSAGE_MAP()


// CArtNotFound message handlers

BOOL CArtNotFound::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    if (!m_bNoShort)
    {
        GetDlgItem(IDOK)->SetWindowText(CResString::ex().getStrTblText(IDS_MSG_OK));
        GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
        GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

    }
    if (!AeGetApp()->IsDE())
    {
        GetDlgItem( IDC_BUTTON_GOOGLE )->ShowWindow(SW_HIDE);
        GetDlgItem( IDC_BUTTON_GOOGLE )->EnableWindow(FALSE);
        GetDlgItem( IDC_BUTTON_INFO )->ShowWindow(SW_HIDE);
        GetDlgItem( IDC_BUTTON_INFO )->EnableWindow(FALSE);
    }
    CenterWindow();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CArtNotFound::OnButtonGoogle()
{
    CString url;
    url.Format("http://www.google.de/#q=%s", m_cBezeichnung.GetString());
    ShellExecute(0, NULL, url, NULL, NULL, SW_SHOWDEFAULT);
}

void CArtNotFound::OnButtonInfo()
{
    CDInfoListe dlgInfoListe;
    dlgInfoListe.m_such = m_cBezeichnung;
    dlgInfoListe.m_bAufnahme = m_bAufnahme;
    dlgInfoListe.DoModal();
    m_lArtNo = dlgInfoListe.m_ArtNr;
    if (m_lArtNo > 0)
    {
        CDialogMultiLang::OnCancel();
    }
}
