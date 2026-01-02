// DCountryUpd.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artikel.h>
#include "DCountryUpd.h"


// CDCountryUpd-Dialogfeld

IMPLEMENT_DYNAMIC(CDCountryUpd, CDialog)
CDCountryUpd::CDCountryUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCountryUpd::IDD, pParent)
    , m_CCode(_T(""))
    , m_CSera(_T(""))
    , m_CPrint(_T(""))
    , m_CXMLCode(_T(""))
    , m_CXMLText(_T(""))
    , m_bAktiv(TRUE)
    , m_bVB(FALSE)
{
}

CDCountryUpd::~CDCountryUpd()
{
}

void CDCountryUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_CODE, m_edit_Code);
    DDX_Text(pDX, IDC_EDIT_CODE, m_CCode);
    DDX_Control(pDX, IDC_EDIT_SERA, m_edit_Sera);
    DDX_Text(pDX, IDC_EDIT_SERA, m_CSera);
    DDX_Control(pDX, IDC_EDIT_PRINT, m_edit_Print);
    DDX_Text(pDX, IDC_EDIT_PRINT, m_CPrint);
    DDX_Control(pDX, IDC_EDIT_XML_CODE, m_edit_XMLCode);
    DDX_Text(pDX, IDC_EDIT_XML_CODE, m_CXMLCode);
    DDX_Control(pDX, IDC_EDIT_XML_TEXT, m_edit_XMLText);
    DDX_Text(pDX, IDC_EDIT_XML_TEXT, m_CXMLText);
    DDX_Control(pDX, IDC_CHECK_AKTIV, m_CB_Aktiv);
    DDX_Control(pDX, IDC_CHECK_VB, m_CB_VB);
    DDX_Check(pDX, IDC_CHECK_AKTIV, m_bAktiv);
    DDX_Check(pDX, IDC_CHECK_VB, m_bVB);
}


BEGIN_MESSAGE_MAP(CDCountryUpd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_CODE, OnEnChangeEditCode)
    ON_EN_CHANGE(IDC_EDIT_SERA, OnEnChangeEditSera)
    ON_EN_CHANGE(IDC_EDIT_PRINT, OnEnChangeEditPrint)
    ON_EN_CHANGE(IDC_EDIT_XML_CODE, OnEnChangeEditXmlCode)
    ON_EN_CHANGE(IDC_EDIT_XML_TEXT, OnEnChangeEditXmlText)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDCountryUpd-Meldungshandler

BOOL CDCountryUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    if (!m_sFunktion)
    {
        GetDlgItem(IDC_EDIT_CODE)->EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDCountryUpd::OnEnChangeEditCode()
{
    AllgLaengeKontr(&m_edit_Code, L_CCODE_INFOCODE, AeGetApp()->Modus());
}

void CDCountryUpd::OnEnChangeEditSera()
{
    AllgLaengeKontr(&m_edit_Sera, L_CCODE_SERACODE, AeGetApp()->Modus());
}

void CDCountryUpd::OnEnChangeEditPrint()
{
    AllgLaengeKontr(&m_edit_Print, L_CCODE_PRINTCODE, AeGetApp()->Modus());
}

void CDCountryUpd::OnEnChangeEditXmlCode()
{
    AllgLaengeKontr(&m_edit_XMLCode, L_CCODE_XMLCODE, AeGetApp()->Modus());
}

void CDCountryUpd::OnEnChangeEditXmlText()
{
    AllgLaengeKontr(&m_edit_XMLText, L_CCODE_XMLTEXT, AeGetApp()->Modus());
}

void CDCountryUpd::OnBnClickedOk()
{
    UpdateData();
    m_CountryCode->SetInfocode(m_CCode);
    m_CountryCode->SetArticleactiv(m_CB_Aktiv.GetCheck() ? '1' : '0');
    m_CountryCode->SetAuxdelivery(m_CB_VB.GetCheck() ? '1' : '0');
    m_CountryCode->SetSeracode(m_CSera);;
    m_CountryCode->SetPrintcode(m_CPrint);;
    m_CountryCode->SetXmlcode(m_CXMLCode);;
    m_CountryCode->SetXmltext(m_CXMLText);;
    if (!m_sFunktion)
    {
        m_CountryCode->Update();
    }
    else
    {
        m_CountryCode->Insert();
    }
    CDialogMultiLang::OnOK();
}
