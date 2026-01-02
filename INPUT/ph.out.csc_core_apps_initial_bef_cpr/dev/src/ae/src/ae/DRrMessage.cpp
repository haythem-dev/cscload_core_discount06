// DRrMessage.cpp : implementation file
//

#include "stdafx.h"
#include "DRrMessage.h"

/////////////////////////////////////////////////////////////////////////////
// CDRrMessage dialog

CDRrMessage::CDRrMessage(CView* pView)
{
    m_pView = pView;
}

CDRrMessage::CDRrMessage(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDRrMessage::IDD, pParent)
{
    m_pView = NULL;
}


void CDRrMessage::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDRrMessage, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRrMessage message handlers

void CDRrMessage::OnCancel()    // keine echte
{                               // Nachrichtenbehandlungsroutine
    if (m_pView != NULL)
    {
        // falls nichtmodales Dialogfeld, OnCancel-Funktion der
        // Basisklasse nicht aufrufen
        m_pView->PostMessage(WM_GOODBYE, IDCANCEL);
    }
    else
    {
        CDialogMultiLang::OnCancel();   // falls modales Dialogfeld
    }
}

void CDRrMessage::OnOK()
{
    if (m_pView != NULL)
    {
        // falls nichtmodales Dialogfeld, OnOK-Funktion der
        // Basisklasse nicht aufrufen
        m_pView->PostMessage(WM_GOODBYE, IDOK);
    }
    else
    {
        CDialogMultiLang::OnOK();       // falls modales Dialogfeld
    }
}

BOOL CDRrMessage::Create()
{
    return CDialogMultiLang::Create(CDRrMessage::IDD);
}

BOOL CDRrMessage::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
