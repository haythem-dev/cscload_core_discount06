// Entsperr.cpp : implementation file
//

#include "stdafx.h"
#include <lockview.h>
#include "Entsperr.h"

/////////////////////////////////////////////////////////////////////////////
// CEntsperr dialog


CEntsperr::CEntsperr(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CEntsperr::IDD, pParent)
{
    m_CAuftrNr = _T("");
}


void CEntsperr::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_AUFTR_NR, m_EditAuftrNr);
    DDX_Text(pDX, IDC_EDIT_AUFTR_NR, m_CAuftrNr);
}


BEGIN_MESSAGE_MAP(CEntsperr, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_AUFTR_NR, OnChangeEditAuftrNr)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntsperr message handlers

BOOL CEntsperr::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CEntsperr::OnChangeEditAuftrNr()
{
    AllgWertKontr(&m_EditAuftrNr, MAXIMUM_AUFTRAG_NR);
}

void CEntsperr::OnOK()
{
    if (!UpdateData())
        return;
    //Abfrage ob Auftrag eigenes VZ
    if (MsgBoxYesNo(IDP_SOLL_ENTSPERR) == IDYES)
    {
        CLOCKMAN clockman;
        strcpy(clockman.s.RESOURCEKEY, m_CAuftrNr);
        CString Name = GetAeUser().GetTermID();
        strcpy(clockman.s.NAMEWORKSTATION, Name);
        clockman.s.TM_YEAR = (AeGetApp()->VzNr());
        BeginWaitCursor();
        clockman.Server(AasrvUnlock, PIPE_AE_SRV);
        EndWaitCursor();
        if (clockman.rc == SRV_SQLNOTFOUND)
            MsgBoxOK(IDP_KEIN_AUFTRAG);
    }
    CDialogMultiLang::OnOK();
}
