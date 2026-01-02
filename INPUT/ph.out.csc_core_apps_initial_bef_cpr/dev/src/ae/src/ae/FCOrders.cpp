// FCOrders.cpp : implementation file
//

#include "stdafx.h"
#include "FCOrders.h"
#include "FCOrdersSel.h"

//Definition der Tabellenbreite und der Ueberschriften

#define COL_KB      0
#define COL_IDF     1
#define COL_APO     2
#define COL_AUFNR   3
#define COL_DATUM   4
#define COL_AART    5
#define NUM_COLUMNS 6

static COLUMNS_TYPES Columns[] =
{
    COL_KB,    "",  35, LVCFMT_LEFT,
    COL_IDF,   "",  60, LVCFMT_RIGHT,
    COL_APO,   "", 240, LVCFMT_LEFT,
    COL_AUFNR, "",  70, LVCFMT_RIGHT,
    COL_DATUM, "",  80, LVCFMT_LEFT,
    COL_AART,  "",  46, LVCFMT_LEFT,
    -1,        "",   0, 0
};

// CFCOrders dialog

IMPLEMENT_DYNAMIC(CFCOrders, CDialog)

CFCOrders::CFCOrders(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CFCOrders::IDD, pParent)
{
    m_bCursorOpen = false; //Datenbankcurser geschlossen
    Columns[COL_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_IDF].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[COL_APO].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns[COL_AUFNR].Columns = CResString::ex().getStrTblText(AETXT_AUF_NR);
    Columns[COL_DATUM].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[COL_AART].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
}

CFCOrders::~CFCOrders()
{
}

void CFCOrders::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_CTRL, m_ListCtl);
}

BEGIN_MESSAGE_MAP(CFCOrders, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_OFFEN, &CFCOrders::OnBnClickedButtonOffen)
    ON_BN_CLICKED(IDC_BUTTON_TO_COMPLETE, &CFCOrders::OnBnClickedButtonToComplete)
    ON_BN_CLICKED(IDC_BUTTON_TO_CLOSE, &CFCOrders::OnBnClickedButtonToClose)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST_CTRL, OnDblclkListCtrl)
END_MESSAGE_MAP()

// CFCOrders message handlers

BOOL CFCOrders::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    //dwOldBits |= LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES;
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    //HICON hIcon;

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CFCOrders::OnBnClickedButtonOffen()
{
    m_nFunktion = AaauftSelList_FCOrdersAll;
    GetPage();
}

void CFCOrders::OnBnClickedButtonToComplete()
{
    m_nFunktion = AaauftSelList_FCOrdersToSolve;
    GetPage();
}

void CFCOrders::OnBnClickedButtonToClose()
{
    m_nFunktion = AaauftSelList_FCOrdersToClose;
    GetPage();
}

void CFCOrders::GetPage()
{
    //CloseCursor();
    ppString name;
    ppString aart;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    CFCORDERSSEL fcorders;
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    fcorders.SetVertriebszentrumnr(AeGetApp()->VzNr());
    fcorders.s.FETCH_REL = 1;   //normaler Fetch
    CLetterMan kb;
    for (;;)
    {
        fcorders.Server(m_nFunktion);

        m_bCursorOpen = true;          //Datenbankcurser offen
        if (fcorders.rc != SRV_OK)
        {
            break;
        }
        //Ausgabe in die Listbox
        s[COL_KB] = kb.Next();
        s[COL_IDF].Format("%d", fcorders.GetKundennr());
        s[COL_APO] = fcorders.GetNameapo(name);
        s[COL_AUFNR].Format("%d", fcorders.GetKdauftragnr());
        s[COL_DATUM] = DDMMYYYYStringFromDateLong(fcorders.GetDatum());
        s[COL_AART] = fcorders.GetKdauftragart(aart);

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    if (m_ListCtl.GetItemCount() == 0)
    {
        MsgBoxOK(IDP_KEIN_AUFTRAG);
    }
    CloseCursor();
    EndWaitCursor();
}

void CFCOrders::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CFCORDERSSEL fcorders;
    fcorders.s.FETCH_REL = 0;
    BeginWaitCursor();
    fcorders.Server(m_nFunktion);
    EndWaitCursor();
    m_bCursorOpen = false;
}

void CFCOrders::OnDblclkListCtrl(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SetAuftrNr();
    *pResult = 0L;
}

void CFCOrders::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST_CTRL))
    {
        SetAuftrNr();
        return;
    }
}

void CFCOrders::SetAuftrNr()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    m_AufNr = atol(m_ListCtl.GetItemText(pos, COL_AUFNR));
    CDialogMultiLang::OnOK();
}
