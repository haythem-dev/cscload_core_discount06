// DMailMessage.cpp : implementation file
//

#include "stdafx.h"
#include <mailsystem.h>
#include "DMailMessage.h"
#include "DDruckAuftrag.h"

/////////////////////////////////////////////////////////////////////////////
// CDMailMessage dialog

CDMailMessage::CDMailMessage(CView* pView)
{
    m_pView = pView;
}

CDMailMessage::CDMailMessage(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDMailMessage::IDD, pParent)
{
    m_CText = _T("");
    m_CDatum = _T("");
    m_CZeit = _T("");
    m_pView = NULL;
}


void CDMailMessage::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_BITMAP, m_Static_Bitmap);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_Edit_Text);
    DDX_Text(pDX, IDC_EDIT_TEXT, m_CText);
    DDX_Text(pDX, IDC_STATIC_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_STATIC_ZEIT, m_CZeit);
}


BEGIN_MESSAGE_MAP(CDMailMessage, CDialogMultiLang)
    ON_WM_PAINT()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_BN_CLICKED(IDC_BUTTON_READ, OnBnClickedButtonRead)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDMailMessage message handlers

void CDMailMessage::OnOK()
{
}

BOOL CDMailMessage::Create()
{
    return CDialogMultiLang::Create(CDMailMessage::IDD);
}

BOOL CDMailMessage::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_bHasPicture = false;

    GetText();
    int len = m_CText.GetLength();
    m_Edit_Text.SetFocus();
    m_Edit_Text.SetSel( len, len, FALSE );

    return FALSE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
void CDMailMessage::OnCancel()
{
    if (m_pView != NULL)
    {
        // falls nichtmodales Dialogfeld, OnCancel-Funktion der
        // Basisklasse nicht aufrufen
        m_pView->PostMessage(WM_GOODBYEMAIL, IDCANCEL);
    }
    else
    {
        CDialogMultiLang::OnCancel();   // falls modales Dialogfeld
    }
}

void CDMailMessage::GetText()
{
    ppString text;
    char datum[11];
    CMAILMESSAGE mes;
    mes.SetNewsno(m_lNewsno);
    mes.SelMailMessage();
    mes.GetMessage(text);
    m_CText = text.c_str();
    if (mes.GetPriority() == 0) SetBitmap(IDB_BITMAP_TIP);
    else if (mes.GetPriority() == 1) SetBitmap(IDB_BITMAP_INFO);
    else if (mes.GetPriority() == 2) SetBitmap(IDB_BITMAP_HINWEIS);
    else if (mes.GetPriority() == 3) SetBitmap(IDB_BITMAP_WICHTIG);
    else SetBitmap(IDB_BITMAP_WARNUNG);
    m_CDatum = AllgDatumLong2CharTTMMJJJJ(mes.GetTm_date(),datum);
    m_CZeit = AllgZeit2CharHHMM(mes.GetTm_time());
    UpdateData(FALSE);
}

void CDMailMessage::SetBitmap(const UINT id)
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

void CDMailMessage::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    if (m_bHasPicture)
    {
        m_Static_Bitmap.GetClientRect( m_Rect );
        m_Static_Bitmap.ClientToScreen( m_Rect ); // Convert to Dialog coordinates
        ScreenToClient( m_Rect );
        dc.BitBlt( m_Rect.left
               , m_Rect.top
               , m_bmInfo.bmWidth
               , m_bmInfo.bmHeight
               , &m_dcMem
               , 0, 0, SRCCOPY
               );
        //m_Static_Bitmap.ShowWindow(SW_SHOWNA /*SS_BITMAP*/);
    }

    return;

    // Do not call CDialogMultiLang::OnPaint() for painting messages
}

void CDMailMessage::OnDestroy()
{
    CDialogMultiLang::OnDestroy();

    if (m_bHasPicture)
    {
        // Need to DeleteObject() the bitmap which was loaded.
        m_Bitmap.DeleteObject();
        m_dcMem.DeleteDC();
    }

}

void CDMailMessage::OnButtonDruck()
{
    CDruckAuftrag druckAuftrag;
    CString ausgabe;
    CString cs(m_CText);    // multi line edit control evt. mit Status "read-only"
    int len = m_CText.GetLength();
    int i = 1;
    while (i > 0)
    {
        ausgabe.Empty();
        i = cs.Find("\r\n");
        if (i >= 0)
        {
            if (i > 81)     // bei mehr als 81 Zeichen Zeilenumbruch vorher auf Liste
            {
                for (i = 81; i > 0; i--)    //suchen letztes Blank
                {
                    if (cs.GetAt(i) == ' ')
                        break;
                }
                if (i == 0)
                    i = 80;
            }
            ausgabe = cs.Left(i);   // ausgabe enthält eine zeile !
            len = cs.GetLength();
            cs = cs.Right(len - i - 2);
        }
        else
        {
            if (cs.GetLength() > 81)    // bei mehr als 81 Zeichen Zeilenumbruch vorher auf Liste
            {
                for (i = 81; i > 0; i--)    //suchen letztes Blank
                {
                    if (cs.GetAt(i) == ' ')
                        break;
                }
                if (i == 0)
                    i = 80;
                ausgabe = cs.Left(i);   // ausgabe enthält eine zeile !
                len = cs.GetLength();
                cs = cs.Right(len - i - 2);
            }
            else
                ausgabe = cs;
        }
        druckAuftrag.AddPosZeile(ausgabe);
    }
    druckAuftrag.Druck(FALSE);
    druckAuftrag.DelAllData();
}

void CDMailMessage::OnBnClickedButtonRead()
{
    CMAILITEMS item;
    item.SetFilialnr(static_cast<short>(m_iFilialnr));
    item.SetUid(m_lUid);
    item.SetNewsno(m_lNewsno);
    item.DeleteMessage();

    if (m_pView != NULL)
    {
        // falls nichtmodales Dialogfeld, OnOK-Funktion der
        // Basisklasse nicht aufrufen
        m_pView->PostMessage(WM_GOODBYEMAIL, IDOK);
    }
    else
    {
        CDialogMultiLang::OnOK();       // falls modales Dialogfeld
    }
}
