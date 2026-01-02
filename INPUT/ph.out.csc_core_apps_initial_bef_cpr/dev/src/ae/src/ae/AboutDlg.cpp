#include "StdAfx.h"
#include "AboutDlg.h"
#include <pxverbund_version.h>

CAboutDlg::CAboutDlg() : CDialogMultiLang(CAboutDlg::IDD)
{
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_HISTORY, OnButtonHistory)
    ON_BN_CLICKED(IDC_BUTTON_DOCU, OnButtonDocu)
END_MESSAGE_MAP()

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    CString version = CSC_CORE_APPLICATIONS_VERSION;
    CString copyright = CSC_CORE_APPLICATIONS_COPYRIGHT;
    DDX_Text(pDX, IDC_STATIC_VERSION_NO, version);
    DDX_Text(pDX, IDC_STATIC_COPYRIGHT, copyright);
}

void CAboutDlg::OnButtonDocu()
{
    CPARAMETER para;
    para.SetFilialnr(0);
    para.SetProgrammname("AE");
    para.SetZweck("About");
    para.SetParametername("DocuUrl");
    ppString url;
    if (para.SelParameter() == SRV_OK)
    {
        para.GetAuspraegung(url);
        ShellExecute(0, NULL, url, NULL, NULL, SW_SHOWDEFAULT);
    }
    else
    {
        AfxMessageBox(CResString::ex().getStrTblText(IDP_ERR_DOCUURL_NOTFOUND));
    }
}

void CAboutDlg::OnButtonHistory()
{
    CPARAMETER para;
    para.SetFilialnr(0);
    para.SetProgrammname("AE");
    para.SetZweck("About");
    para.SetParametername("HistoryUrl");
    ppString url;
    if (para.SelParameter() == SRV_OK)
    {
        para.GetAuspraegung(url);
        ShellExecute(0, NULL, url, NULL, NULL, SW_SHOWDEFAULT);
    }
    else
    {
        AfxMessageBox(CResString::ex().getStrTblText(IDP_ERR_HISTORYURL_NOTFOUND));
    }
}
