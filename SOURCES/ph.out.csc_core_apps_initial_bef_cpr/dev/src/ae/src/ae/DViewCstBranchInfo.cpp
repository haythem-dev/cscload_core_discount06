// DViewCstBranchInfo.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <customer.h>
#include "DViewCstBranchInfo.h"

#define Zeilenende "\r\n"
#define maxlen 50

// CDViewCstBranchInfo-Dialogfeld

CDViewCstBranchInfo::CDViewCstBranchInfo(CView* pView)
{
    m_pView = pView;
}

IMPLEMENT_DYNAMIC(CDViewCstBranchInfo, CDialog)
CDViewCstBranchInfo::CDViewCstBranchInfo(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDViewCstBranchInfo::IDD, pParent)
{
}

CDViewCstBranchInfo::~CDViewCstBranchInfo()
{
}

void CDViewCstBranchInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDViewCstBranchInfo, CDialogMultiLang)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


// CDViewCstBranchInfo-Meldungshandler

BOOL CDViewCstBranchInfo::Create()
{
    return CDialogMultiLang::Create(CDViewCstBranchInfo::IDD);
}

BOOL CDViewCstBranchInfo::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    RepositionWindow();

    bool bFound = false;

    CString Infotext;
    CString huelse;
    ppString input;
    CCSTBRANCHINFO info;
    info.SetBranchno(m_sBranchNo);
    for (;;)
    {
        if (info.SelListValid() != SRV_OK)
            break;
        bFound = true;
        huelse = info.GetInfotext(input);
        Infotext += huelse;
        Infotext += Zeilenende;
    }
    this->ShowWindow(bFound ? SW_SHOW : SW_HIDE);

    GetDlgItem(IDC_EDIT_INFO)->SetWindowText(Infotext);

    this->EnableWindow(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDViewCstBranchInfo::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
}

void CDViewCstBranchInfo::RepositionWindow()
{
    CRect rectDesk;
    CRect rectWin;

    GetDesktopWindow()->GetWindowRect( &rectDesk );   //fullscreen
    GetWindowRect( &rectWin );

    /* set to the left,upper corner */
    int iLeft  = rectDesk.BottomRight().x - rectWin.Width() - 2;
    int iTop   = rectDesk.BottomRight().y - rectWin.Height() - 50;
    int iRight = rectDesk.BottomRight().x - 2;
    int iBottom = rectDesk.BottomRight().y - 50;

    rectWin.SetRect( iLeft, iTop, iRight, iBottom);
    MoveWindow(rectWin);
}


// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDViewCstBranchInfo::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_ESCAPE)
    {
        return 1L;      //Message wird nicht weitergeleitet
    }

    return 0L;
}
