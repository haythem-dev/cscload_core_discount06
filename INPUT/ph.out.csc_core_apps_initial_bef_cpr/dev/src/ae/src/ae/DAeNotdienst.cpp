// DAeNotdienst.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include <kndsel.h>
#include <customer.h>
#include "DAeNotdienst.h"
#include "DDruckAuftrag.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     5

static COLUMNS_TYPES Columns[] =
{
    0,  "",  55, LVCFMT_RIGHT,
    1,  "", 170, LVCFMT_LEFT,
    2,  "", 160, LVCFMT_LEFT,
    3,  "",  40, LVCFMT_RIGHT,
    4,  "", 360, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDAeNotdienst

CDAeNotdienst::CDAeNotdienst(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAeNotdienst::IDD, pParent)
{
    m_Datum = 0;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_DEC);
    Columns[4].Columns = CResString::ex().getStrTblText(IDS_BEMERK);
}

void CDAeNotdienst::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_VZ, m_editVz);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Datum);
}


BEGIN_MESSAGE_MAP(CDAeNotdienst, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_VZ, OnChangeEditVz)
    ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDAeNotdienst

BOOL CDAeNotdienst::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    // --- damit die ganze Zeile angeclickt werden kann
    DWORD dwOldBits;
    dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    CString csVz;
    csVz.Format("%d", AeGetApp()->VzNr());
    m_editVz.SetWindowText(csVz);
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_Datum = CTimeFromDateLongMinTime(zeit.s.DATUM);
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDAeNotdienst::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

void CDAeNotdienst::OnOK()
{
    //Wegen Sort
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM | LVIF_TEXT;
    lvi.iSubItem = 0;
    lvi.iItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;
    //

    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    UpdateData(TRUE);

    CString csVz;
    m_editVz.GetWindowText(csVz);
    m_sVzNr = static_cast<short>(atoi(csVz));
    ppDayType Tag((ppDayType::t_day)(m_Datum.GetDayOfWeek() - 1));
    m_csTag = Tag.GetWeekDay();
    m_ldatum = m_Datum.GetYear()*10000 + m_Datum.GetMonth()*100 + m_Datum.GetDay();
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    m_srvServicePlan.CloseCursor();
    m_srvServicePlan.SetVertriebszentrumnr(m_sVzNr);
    m_srvServicePlan.SetDatum(m_ldatum);
    for (int i = 0; ; i++)
    {
        if (m_srvServicePlan.SelListHist() != SRV_OK) break;
        // wichtig für Sort
        lvi.lParam = (LPARAM)i;
        CKNDINF kndinf;
        kndinf.s.KUNDENNR           = m_srvServicePlan.GetKundennr();
        kndinf.s.VERTRIEBSZENTRUMNR = m_sVzNr;
        kndinf.Server(AakundeSel_knd_info);
        if (kndinf.rc != SRV_OK)
        {
            s[0].Format("% 7d", kndinf.s.KUNDENNR);
        }
        else
        {
            s[0].Format("% 7d", kndinf.s.IDFNR);
            s[1] = kndinf.s.NAMEAPO;
            s[2] = kndinf.s.ORT;
        }
        CKNDTOUREN tour;
        tour.s.KUNDENNR = m_srvServicePlan.GetKundennr();
        tour.s.VERTRIEBSZENTRUMNR = m_sVzNr;
        tour.s.WEEKDAY = static_cast<short>(m_Datum.GetDayOfWeek() - 1);
        tour.s.FETCH_REL = 1;   //normaler Fetch
        tour.Server(AakundeSel_nachttouren);
        if (kndinf.rc == SRV_OK)
        {
            s[3].Format("%ld", tour.s.LAGRECHTOUR);
        }
        else
        {
            s[3].Empty();
        }
        tour.s.FETCH_REL = 0;   //close Cursor
        tour.Server(AakundeSel_nachttouren);
        ppString csText;
        s[4] = m_srvServicePlan.GetBemerkungen(csText);

        if (!CListCtrlHelper::InsertItem(m_ListCtl, NUM_COLUMNS, s, lvi))
        {
            EndWaitCursor();
            return;
        }
        // wichtig für Sort
        ++lvi.iItem;
    }
    EndWaitCursor();
}

void CDAeNotdienst::OnChangeEditVz()
{
    AllgWertKontr(&m_editVz, MAXIMUM_FILIALNR);
}

void CDAeNotdienst::OnButtonPrint()
{
    if (m_ListCtl.GetItemCount() == 0)
        return;

    char underline[111];
    memset(underline, '-', 109);
    underline[110] = '\0';

    CString vz;
    GetDlgItem(IDC_STATIC_VZ)->GetWindowText(vz);
    vz.Remove('&');

    CString titel;
    this->GetWindowText(titel);

    CString liste;
    liste.Format(CResString::ex().getStrTblText(IDS_FOR_DAY_DATE),
        vz.GetString(),
        m_sVzNr,
        titel.GetString(),
        m_csTag.GetString(),
        m_ldatum%100,
        m_ldatum%10000/100,
        m_ldatum/10000);

    CDruckAuftrag druckAuftrag;
    druckAuftrag.AddKopfZeile(liste);

    liste.Empty();
    COLUMNS_TYPES* pType = Columns;
    for (int x = 0; x < NUM_COLUMNS; x++)
    {
        liste += FormatColumn(x, pType->Columns.GetString());
        ++pType;
    }
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);
    liste = "Seite: ";
    liste += "%d";
    druckAuftrag.AddFussZeile(liste);
    int max = m_ListCtl.GetItemCount();
    for (int index = 0; index < max; index++)
    {
        liste.Empty();
        for (int x = 0; x < NUM_COLUMNS; x++)
        {
            liste += FormatColumn(x, m_ListCtl.GetItemText(index, x).GetString());
        }
        druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(1);
    druckAuftrag.DelAllData();
}

CString CDAeNotdienst::FormatColumn(int column, CString text)
{
    int len = (m_ListCtl.GetColumnWidth(column) / 8) + 1;
    CString ausgab;
    ausgab.Format("%-*.*s ", len, len, text);
    return ausgab;
}

// CompareListe ist eine stand alone Funktion
/////////////////////////////////////////////////////////////////////////////
// CompareListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
/////////////////////////////////////////////////////////////////////////////
int CALLBACK CompareListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    if (s->GetAt(lParam1) == s->GetAt(lParam2))
        return 0;
    if (s->GetAt(lParam1) > s->GetAt(lParam2))
        return 1;
    return -1;
}

void CDAeNotdienst::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    //Wegen Sort
    LV_ITEM lvi;
    //
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    int col = pNMListView->iSubItem;
    int max = m_ListCtl.GetItemCount();
    CStringArray s;
    s.SetSize(max);
    for (int index = 0; index < max; index++)
    {
        //StringArray an der ursprünglichen Position setzen
        lvi.iItem = index;
        lvi.mask = LVIF_PARAM;   //muss gesetzt sein, um lParam abzuholen
        m_ListCtl.GetItem(&lvi); //Ursprungadresse steht in lParam
        s[(int)lvi.lParam] = m_ListCtl.GetItemText(index, col);
    }
    m_ListCtl.SortItems(CompareListe, (LPARAM)&s);

    *pResult = 0L;
}
