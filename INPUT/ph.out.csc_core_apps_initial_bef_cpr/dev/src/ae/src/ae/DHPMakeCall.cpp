// DHPMakeCall.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DHPMakeCall.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDHPMakeCall


CDHPMakeCall::CDHPMakeCall(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDHPMakeCall::IDD, pParent)
{
    m_csTelNr = _T("");
}


void CDHPMakeCall::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_TELNR, m_edit_TelNr);
    DDX_Text(pDX, IDC_EDIT_TELNR, m_csTelNr);
}


BEGIN_MESSAGE_MAP(CDHPMakeCall, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDHPMakeCall

BOOL CDHPMakeCall::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDHPMakeCall::OnOK()
{
    UpdateData(TRUE);
    
    CDialogMultiLang::OnOK();
}
