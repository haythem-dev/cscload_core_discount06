// DUserInfo.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DUserInfo.h"


// CDUserInfo-Dialogfeld

CDUserInfo::CDUserInfo(CView* pView)
{
    m_pView = pView;
}

IMPLEMENT_DYNAMIC(CDUserInfo, CDialog)
CDUserInfo::CDUserInfo(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDUserInfo::IDD, pParent)
{
    m_cUserInfo = _T("");
    m_sPrio = 0;
    m_pView = NULL;
}

CDUserInfo::~CDUserInfo()
{
}

void CDUserInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_BITMAP, m_Static_Bitmap);
}


BEGIN_MESSAGE_MAP(CDUserInfo, CDialogMultiLang)
    ON_WM_PAINT()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BUTTON_READ, OnButtonRead)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


// CDUserInfo-Meldungshandler

BOOL CDUserInfo::Create()
{
    return CDialogMultiLang::Create(CDUserInfo::IDD);
}

BOOL CDUserInfo::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_bHasPicture = false;
    GetDlgItem(IDC_EDIT_TEXT)->SetWindowText(m_cUserInfo);

    if      (m_sPrio == 0) SetBitmap(IDB_BITMAP_TIP);
    else if (m_sPrio == 1) SetBitmap(IDB_BITMAP_INFO);
    else if (m_sPrio == 2) SetBitmap(IDB_BITMAP_HINWEIS);
    else if (m_sPrio == 3) SetBitmap(IDB_BITMAP_WICHTIG);
    else SetBitmap(IDB_BITMAP_WARNUNG);

    RepositionWindow();

    Beep(880, 400);
    Beep(528, 400);
    Beep(660, 600);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDUserInfo::OnDestroy()
{
    CDialogMultiLang::OnDestroy();

    if (m_bHasPicture)
    {
        // Need to DeleteObject() the bitmap which was loaded.
        m_Bitmap.DeleteObject();
        m_dcMem.DeleteDC();
    }
}

void CDUserInfo::OnCancel()
{
}

void CDUserInfo::RepositionWindow()
{
    CenterWindow();
}

void CDUserInfo::SetBitmap(const UINT id)
{
    if (m_bHasPicture)
    {
        // Need to DeleteObject() the bitmap which was loaded.
        m_Bitmap.DeleteObject();
        m_dcMem.DeleteDC();
    }
    m_Bitmap.LoadBitmap(id);
    m_Bitmap.GetObject(sizeof(BITMAP), &m_bmInfo);

    CClientDC dc(this);

    m_dcMem.CreateCompatibleDC(&dc);               // DC erzeugen
    m_dcMem.SelectObject(&m_Bitmap);

    m_bHasPicture = true;
}

void CDUserInfo::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    if (m_bHasPicture)
    {
        m_Static_Bitmap.GetClientRect(m_Rect);
        m_Static_Bitmap.ClientToScreen(m_Rect); // Convert to Dialog coordinates
        ScreenToClient( m_Rect );
        dc.BitBlt(m_Rect.left
                , m_Rect.top
                , m_bmInfo.bmWidth
                , m_bmInfo.bmHeight
                , &m_dcMem
                , 0, 0, SRCCOPY);
    }
}

void CDUserInfo::OnButtonRead()
{
    CDialogMultiLang::OnCancel();
}

void CDUserInfo::OnOK()
{
}

LRESULT CDUserInfo::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_RETURN)
    {
        return 1;
    }
    return 0;
}
