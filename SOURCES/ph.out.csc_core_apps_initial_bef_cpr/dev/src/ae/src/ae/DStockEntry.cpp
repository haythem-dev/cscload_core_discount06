// DStockEntry.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artsel.h>
#include <artikel.h>
#include "DDruckAuftrag.h"
#include "DStockEntry.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  80, LVCFMT_LEFT,
    2,  "",  55, LVCFMT_LEFT,
    3,  "",  70, LVCFMT_LEFT,
    4,  "", 300, LVCFMT_LEFT,
    5,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

// CDStockEntry-Dialogfeld

IMPLEMENT_DYNAMIC(CDStockEntry, CDialog)
CDStockEntry::CDStockEntry(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDStockEntry::IDD, pParent)
    , m_date_Datum(COleDateTime::GetCurrentTime())
    , m_cVZ(_T(""))
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_HERSTEL);
}

CDStockEntry::~CDStockEntry()
{
}

void CDStockEntry::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DATUM, m_DT_Datum);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATUM, m_date_Datum);
    DDX_Control(pDX, IDC_EDIT_VZ, m_edit_Vz);
    DDX_Text(pDX, IDC_EDIT_VZ, m_cVZ);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}

BEGIN_MESSAGE_MAP(CDStockEntry, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_VZ, OnEnChangeEditVz)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnBnClickedButtonDruck)
END_MESSAGE_MAP()

// CDStockEntry-Meldungshandler

void CDStockEntry::OnEnChangeEditVz()
{
    AllgWertKontr(&m_edit_Vz, MAXIMUM_FILIALNR);
}

void CDStockEntry::OnBnClickedOk()
{
    UpdateData();

    m_StockEntry.SetDate(m_date_Datum.GetYear()*10000
                        +m_date_Datum.GetMonth()*100
                        +m_date_Datum.GetDay());
    m_StockEntry.SetBranchno(static_cast<short>(atoi(m_cVZ)));

    GetPage();
}

BOOL CDStockEntry::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    CTime end = CTimeFromDateLongMinTime(zeit.s.DATUM);
    CTimeSpan y(30, 0, 0, 0);
    CTime ctime = end - y;
    m_DT_Datum.SetRange(&ctime,&end);
    m_DT_Datum.SetTime(&end);
    m_cVZ.Format("%d", AeGetApp()->VzNr());

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    UpdateData(FALSE);
    m_StockEntry.SetDate(m_date_Datum.GetYear()*10000
                        +m_date_Datum.GetMonth()*100
                        +m_date_Datum.GetDay());
    m_StockEntry.SetBranchno(static_cast<short>(atoi(m_cVZ)));

    if (AeGetApp()->IsRS())
    {
        m_ListCtl.SetColumnWidth(5,300);
        RepositionWindow();
    }
    CenterWindow();

    GetPage();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDStockEntry::GetPage()
{
    CHERSTELLER herst;
    CARTAESEL code;
    ppString cEinheit;
    ppString cName;
    ppString cHerName;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (m_StockEntry.SelList() != SRV_OK) break;
        s[0] = kb.Next();
        code.s.ARTIKEL_NR = m_StockEntry.GetArticleno();
        code.Server(AatartSel_Preferred);
        AllgEntfSpaces(code.s.ARTICLE_CODE);
        s[1] = code.s.ARTICLE_CODE;
        s[2].Format("%ld", m_StockEntry.GetBestand());
        s[3].Format("%s", m_StockEntry.GetEinheit(cEinheit));
        s[4].Format("%s", m_StockEntry.GetArtikel_name(cName));
        if (AeGetApp()->IsRS())
        {
            herst.SetArtikel_nr(m_StockEntry.GetArticleno());
            if (!herst.SelHersteller())
            {
                s[5].Format("%s", herst.GetName(cHerName));
            }
            else
            {
                s[5].Empty();
            }
        }

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    m_StockEntry.CloseCursor();
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
}

void CDStockEntry::OnBnClickedButtonDruck()
{
    CDruckAuftrag druckAuftrag;
    CTM zeit;
    CString liste;
    char Datum[11];
    int pos, maxpos;
    char underline[111];
    memset(underline, '-', 110);
    underline[110] = '\0';
    zeit.Server(AafilGetdatetime);
    AllgDatumLong2CharTTMMJJJJ(zeit.s.DATUM, Datum);
    GetWindowText(liste);
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);

    liste.Format("%-7.7s %5.5s %-9.9s %-30.30s",
                CResString::ex().getStrTblText(AETXT_PZN).GetString(),
                CResString::ex().getStrTblText(AETXT_MENGE).GetString(),
                CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
                CResString::ex().getStrTblText(AETXT_ARTIKELNAME).GetString() );
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);
    liste = CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d";
    liste += "                                        ";
    liste += CResString::ex().getStrTblText(AETXT_DATUM);
    liste += ": ";
    liste += Datum;
    druckAuftrag.AddFussZeile (liste);
    maxpos = m_ListCtl.GetItemCount();
    for (pos = 0; pos < maxpos; pos++)
    {
        liste.Format("%-7.7s %5.5s %-9.9s %-30.30s",
            m_ListCtl.GetItemText(pos, 1).GetString(),
            m_ListCtl.GetItemText(pos, 2).GetString(),
            m_ListCtl.GetItemText(pos, 3).GetString(),
            m_ListCtl.GetItemText(pos, 4).GetString() );
        druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(0);
    druckAuftrag.DelAllData();
}

void CDStockEntry::RepositionWindow()
{
    int iExpand = 300;
    int iListTop;
    int iListBottom;
    int iListLeft;
    int iListRight;
    CRect rectDesk;
    CRect rectWin;
    CRect rectList;

    GetDesktopWindow()->GetWindowRect( &rectDesk );   //fullscreen
    GetWindowRect( &rectWin );

    /* set to the left,upper corner */
    int iLeft  = rectWin.TopLeft().x;
    int iTop   = rectWin.TopLeft().y;
    int iRight = rectWin.BottomRight().x + iExpand;
    int iBottom = rectWin.BottomRight().y;

    //komplettes Fenster anpassen
    rectWin.SetRect( iLeft, iTop, iRight, iBottom);
    MoveWindow(rectWin);

    //Listbox anpassen
    m_ListCtl.GetClientRect( &rectList );
    m_ListCtl.ClientToScreen( &rectList ); // Convert to Dialog coordinates
    iListTop = rectList.TopLeft().y;
    iListBottom = rectList.BottomRight().y;
    iListLeft = rectList.TopLeft().x;
    iListRight = rectList.BottomRight().x + iExpand;
    rectList.SetRect( iListLeft, iListTop, iListRight, iListBottom);
    ScreenToClient( rectList );
    m_ListCtl.MoveWindow(rectList,true);
}
