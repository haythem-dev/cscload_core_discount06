// DCountDown.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DCountDown.h"

#define AEST_DOWN       1       //Timeridentifikation for CountDown
#define AEST_DOWN_ZEIT  1000    //1 Sekunde

// CDCountDown-Dialogfeld

CDCountDown::CDCountDown(CView* pView)
{
    m_pView = pView;
}

IMPLEMENT_DYNAMIC(CDCountDown, CDialog)
CDCountDown::CDCountDown(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCountDown::IDD, pParent)
{
    m_pView = NULL;
    m_id = 0;
    m_lCountDown = 0;
    m_red = 255;
    m_green = 255;
    m_blue = 255;
}

CDCountDown::~CDCountDown()
{
}

void CDCountDown::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_BITMAP, m_Static_Bitmap);
    DDX_Text(pDX, IDC_STATIC_COUNTDOWN, m_CText);
}

BEGIN_MESSAGE_MAP(CDCountDown, CDialogMultiLang)
    ON_WM_PAINT()
    ON_WM_DESTROY()
    ON_WM_TIMER()
    ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CDCountDown-Meldungshandler

BOOL CDCountDown::Create()
{
    return CDialogMultiLang::Create(CDCountDown::IDD);
}

BOOL CDCountDown::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_bHasPicture = false;

    SetBitmap(m_id);
    long lMinuten = m_lCountDown / 60;
    m_CText.Format(CResString::ex().getStrTblText(AETXT_COUNTDOWN), lMinuten);
    GetDlgItem(IDC_STATIC_COUNTDOWN)->SetWindowText(m_CText);
    SetTimer(AEST_DOWN, AEST_DOWN_ZEIT, NULL);
    m_red = 255;
    m_green = 255;
    m_blue = 255;

    this->EnableWindow(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDCountDown::SetBitmap(const UINT id)
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
    this->EnableWindow(FALSE);
}

void CDCountDown::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    if (m_bHasPicture)
    {
        m_Static_Bitmap.GetClientRect(m_Rect);
        m_Static_Bitmap.ClientToScreen(m_Rect); // Convert to Dialog coordinates
        ScreenToClient(m_Rect);
        dc.BitBlt( m_Rect.left
                 , m_Rect.top
                 , m_bmInfo.bmWidth
                 , m_bmInfo.bmHeight
                 , &m_dcMem
                 , 0, 0, SRCCOPY );
    }

    this->EnableWindow(FALSE);

    // Do not call CDialogMultiLang::OnPaint() for painting messages
}

void CDCountDown::OnDestroy()
{
    CDialogMultiLang::OnDestroy();

    if (m_bHasPicture)
    {
        // Need to DeleteObject() the bitmap which was loaded.
        m_Bitmap.DeleteObject();
        m_dcMem.DeleteDC();
    }
}
void CDCountDown::OnTimer(UINT nIDEvent)
{
    if (nIDEvent == AEST_DOWN)
    {
        if (m_id == IDB_BITMAP_WARNUNG)
        {
            if (m_green == 255)
            {
                m_red = 255;
                m_green = 0;
                m_blue = 0;
            }
            else
            {
                m_red = 255;
                m_green = 255;
                m_blue = 255;
            }
        }
        else
        {
            m_red = 255;
            m_green = 255;
            m_blue = 255;
        }
        if (--m_lCountDown == 0)
        {
            Beep(256, 3000);
            KillTimer(AEST_DOWN);
            if (m_pView != NULL)
            {
                // falls nichtmodales Dialogfeld, OnCancel-Funktion der
                // Basisklasse nicht aufrufen
                m_pView->PostMessage(WM_GOODBYEDOWN, IDCANCEL);
            }
            else
            {
                CDialogMultiLang::OnCancel();   // falls modales Dialogfeld
            }
            return;
        }
        long lMinuten = m_lCountDown / 60;
        m_CText.Format(CResString::ex().getStrTblText(AETXT_COUNTDOWN), lMinuten);
        GetDlgItem(IDC_STATIC_COUNTDOWN)->SetWindowText(m_CText);
        if (lMinuten > 20)
        {
            if (m_lCountDown % 600 == 0)   // alle 10 Minuten Piepsen
                Beep(440, 1000);
        }
        else if (lMinuten > 10)
        {
            if (m_lCountDown % 300 == 0)   // alle 5 Minuten Piepsen
                Beep(700, 1000);
        }
        else if (lMinuten > 5)
        {
            if (m_lCountDown % 60 == 0)    // alle 1 Minuten Piepsen
                Beep(880, 1000);
        }
        else if (m_lCountDown % 30 == 0)   // jede Minute Piepsen
            Beep(1012, 1000);
    }
    Invalidate();

    this->EnableWindow(FALSE);
    CDialogMultiLang::OnTimer(nIDEvent);
}

void CDCountDown::OnCancel()
{
}

HBRUSH CDCountDown::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogMultiLang::OnCtlColor(pDC, pWnd, nCtlColor);
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_COUNTDOWN)
        pDC->SetBkColor(RGB(m_red,m_green,m_blue));
    this->EnableWindow(FALSE);
    return hbr;
}
