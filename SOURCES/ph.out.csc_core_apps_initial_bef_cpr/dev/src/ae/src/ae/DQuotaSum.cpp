// DQuotaSum.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artikel.h>
#include <artsel.h>
#include "DDruckAuftrag.h"
#include "DQuotaSum.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     8

static COLUMNS_TYPES Columns[] =
{
    0,  "",  90, LVCFMT_RIGHT,
    1,  "",  90, LVCFMT_RIGHT,
    2,  "", 200, LVCFMT_LEFT,
    3,  "", 100, LVCFMT_RIGHT,
    4,  "",  60, LVCFMT_LEFT,
    5,  "",   0, LVCFMT_LEFT,
    6,  "",   0, LVCFMT_RIGHT,
    7,  "",   0, LVCFMT_RIGHT,
    -1, "",   0, 0
};


// CDQuotaSum-Dialogfeld

IMPLEMENT_DYNAMIC(CDQuotaSum, CDialog)
CDQuotaSum::CDQuotaSum(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDQuotaSum::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_ANZ_KUNDEN);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_ZEITRAUM);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_ABC);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    m_iDetails = 0;
}

CDQuotaSum::~CDQuotaSum()
{
}

void CDQuotaSum::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDQuotaSum, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnBnClickedButtonDruck)
    ON_BN_CLICKED(IDC_BUTTON_DETAILS, OnBnClickedButtonDetails)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnLvnColumnclickList1)
END_MESSAGE_MAP()


// CDQuotaSum-Meldungshandler

BOOL CDQuotaSum::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    //Wegen Sort
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM | LVIF_TEXT;
    lvi.iSubItem = 0;
    lvi.iItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;

    int iProgress = 0;
    int iMax;
    CARTICLEQUOTADETAIL count;
    count.SetBranchno(AeGetApp()->VzNr());
    BeginWaitCursor();
    count.SelCount();
    iMax = count.GetCustomerno();
    m_dlgProgress.SetText(CResString::ex().getStrTblText(AETXT_PREPARE));
    if (m_dlgProgress.GetSafeHwnd() == 0)
        m_dlgProgress.Create();
    if (m_dlgProgress.GetSafeHwnd() != 0)
        m_dlgProgress.SetTimer(1);

    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    CARTIKELQUOTA sum;
    CARTAESEL artsel;
    m_ListCtl.DeleteAllItems();
    ppString cArtikel;
    ppString cEinheit;
    sum.SetBranchno(AeGetApp()->VzNr());
    for (int i = 0; ; i++)
    {
        if (sum.SelKumVz()) break;

        if (i == 0) //beim ersten mal
        {
            if (m_dlgProgress.GetSafeHwnd() != 0)
                m_dlgProgress.DestroyWindow();
            m_dlgProgress.SetText(CResString::ex().getStrTblText(AETXT_EINLESEN));
            if (m_dlgProgress.GetSafeHwnd() == 0)
                m_dlgProgress.Create();
            if (m_dlgProgress.GetSafeHwnd() != 0)
                m_dlgProgress.SetMaxCount(iMax);
        }

        iProgress += sum.GetCustomerno();
        if (m_dlgProgress.GetSafeHwnd() != 0)
            m_dlgProgress.SetProgress(iProgress);
        // wichtig für Sort
        lvi.lParam = (LPARAM)i;
        artsel.s.ARTIKEL_NR = sum.GetArticleno();
        artsel.Server(AatartSel_Preferred);
        AllgEntfSpaces(artsel.s.ARTICLE_CODE);
        s[0] = artsel.s.ARTICLE_CODE;
        s[1] = sum.GetEinheit(cEinheit);
        s[2] = sum.GetArtikel_name(cArtikel);
        s[3].Format("%d", sum.GetCustomerno());
        if (sum.GetValidity() == 'M')
            s[4].Format("%s", (CResString::ex().getStrTblText(AETXT_MONAT).GetString()));
        else if (sum.GetValidity() == 'W')
            s[4].Format("%s", (CResString::ex().getStrTblText(AETXT_WOCHE).GetString()));
        else if (sum.GetValidity() == 'T')
            s[4].Format("%s", (CResString::ex().getStrTblText(AETXT_TAG).GetString()));
        else
            s[4].Format("%s", (CResString::ex().getStrTblText(AETXT_UNBEGRENZT).GetString()));
        s[5] = " ";
        s[6] = " ";
        s[7].Format("%d", sum.GetArticleno());

        if (!CListCtrlHelper::InsertItem(m_ListCtl, NUM_COLUMNS, s, lvi))
        {
            EndWaitCursor();
            return FALSE;
        }
        // wichtig für Sort
        lvi.iItem++;
    }
    m_iCountlist = m_ListCtl.GetItemCount();
    sum.CloseCursor();

    if (m_dlgProgress.GetSafeHwnd() != 0)
        m_dlgProgress.DestroyWindow();

    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDQuotaSum::OnBnClickedButtonDruck()
{
    CDruckAuftrag druckAuftrag;
    CTM zeit;
    CString liste,apo,ort,name;
    char Datum[11];
    int pos, maxpos;
    char underline[111];
    memset(underline, '-', 110);
    underline[110] = '\0';
    zeit.Server(AafilGetdatetime);
    AllgDatumLong2CharTTMMJJJJ(zeit.s.DATUM, Datum);
    this->GetWindowText(name);
    liste.Format("%s", name.GetString());
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);

    if (m_iDetails)
    {
        liste.Format("%-13.13s %-9.9s %-30.30s %-10.10s %-8.8s %-3.3s %-5.5s",
                CResString::ex().getStrTblText(AETXT_PZN).GetString(),
                CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
                CResString::ex().getStrTblText(AETXT_BEZEICHNUNG).GetString(),
                CResString::ex().getStrTblText(AETXT_ANZ_KUNDEN).GetString(),
                CResString::ex().getStrTblText(AETXT_ZEITRAUM).GetString(),
                CResString::ex().getStrTblText(AETXT_ABC).GetString(),
                CResString::ex().getStrTblText(AETXT_MENGE).GetString() );
    }
    else
    {
        liste.Format("%-13.13s    %-9.9s    %-30.30s    %-10.10s    %-8.8s",
                CResString::ex().getStrTblText(AETXT_PZN).GetString(),
                CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
                CResString::ex().getStrTblText(AETXT_BEZEICHNUNG).GetString(),
                CResString::ex().getStrTblText(AETXT_ANZ_KUNDEN).GetString(),
                CResString::ex().getStrTblText(AETXT_ZEITRAUM).GetString() );
    }
    druckAuftrag.AddKopfZeile(liste);

    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);
    liste = CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d";
    liste += "                                        ";
    liste += CResString::ex().getStrTblText(AETXT_DATUM);
    liste += ": ";
    liste += Datum;
    druckAuftrag.AddFussZeile(liste);
    maxpos = m_ListCtl.GetItemCount();
    for (pos = 0; pos < maxpos; pos++)
    {
        if (m_iDetails)
        {
            liste.Format("%-13.13s %-9.9s %-30.30s %-10.10s %-8.8s %-3.3s %-5.5s",
                m_ListCtl.GetItemText(pos, 0).GetString(),
                m_ListCtl.GetItemText(pos, 1).GetString(),
                m_ListCtl.GetItemText(pos, 2).GetString(),
                m_ListCtl.GetItemText(pos, 3).GetString(),
                m_ListCtl.GetItemText(pos, 4).GetString(),
                m_ListCtl.GetItemText(pos, 5).GetString(),
                m_ListCtl.GetItemText(pos, 6).GetString() );
        }
        else
        {
            liste.Format("%-13.13s    %-9.9s    %-30.30s    %-10.10s    %-8.8s",
                m_ListCtl.GetItemText(pos, 0).GetString(),
                m_ListCtl.GetItemText(pos, 1).GetString(),
                m_ListCtl.GetItemText(pos, 2).GetString(),
                m_ListCtl.GetItemText(pos, 3).GetString(),
                m_ListCtl.GetItemText(pos, 4).GetString() );
        }
        druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(1);
    druckAuftrag.DelAllData();
}

void CDQuotaSum::OnBnClickedButtonDetails()
{
    //Wegen Sort
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM | LVIF_TEXT;
    lvi.iSubItem = 0;
    lvi.iItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;

    int iProgress = 0;
    int iMax;
    CARTICLEQUOTADETAIL sum;
    sum.SetBranchno(AeGetApp()->VzNr());
    BeginWaitCursor();
    sum.SelCount();
    iMax = sum.GetCustomerno();
    m_dlgProgress.SetText(CResString::ex().getStrTblText(AETXT_PREPARE));
    if (m_dlgProgress.GetSafeHwnd() == 0)
        m_dlgProgress.Create();
    if (m_dlgProgress.GetSafeHwnd() != 0)
        m_dlgProgress.SetTimer(1);

    m_iDetails = 1;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    CARTAESEL artsel;
    m_ListCtl.SetColumnWidth(5, 40);
    m_ListCtl.SetColumnWidth(6, 50);
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    ppString cArtikel;
    ppString cEinheit;
    ppString cABC;
    sum.SetBranchno(AeGetApp()->VzNr());
    for (int i = 0;;i++)
    {
        if (sum.SelKumVzDetail()) break;

        if (i == 0) //beim ersten mal
        {
            if (m_dlgProgress.GetSafeHwnd() != 0)
                m_dlgProgress.DestroyWindow();
            m_dlgProgress.SetText(CResString::ex().getStrTblText(AETXT_EINLESEN));
            if (m_dlgProgress.GetSafeHwnd() == 0)
                m_dlgProgress.Create();
            if (m_dlgProgress.GetSafeHwnd() != 0)
                m_dlgProgress.SetMaxCount(iMax);
        }

        iProgress += sum.GetCustomerno();
        if (m_dlgProgress.GetSafeHwnd() != 0)
            m_dlgProgress.SetProgress(iProgress);
        // wichtig für Sort
        lvi.lParam = (LPARAM)i;
        artsel.s.ARTIKEL_NR = sum.GetArticleno();
        artsel.Server(AatartSel_Preferred);
        AllgEntfSpaces(artsel.s.ARTICLE_CODE);
        s[0] = artsel.s.ARTICLE_CODE;
        s[1] = sum.GetEinheit(cEinheit);
        s[2] = sum.GetArtikel_name(cArtikel);
        s[3].Format("%d", sum.GetCustomerno());
        if (sum.GetValidity() == 'M')
            s[4].Format("%s", (CResString::ex().getStrTblText(AETXT_MONAT).GetString()));
        else if (sum.GetValidity() == 'W')
            s[4].Format("%s", (CResString::ex().getStrTblText(AETXT_WOCHE).GetString()));
        else if (sum.GetValidity() == 'T')
            s[4].Format("%s", (CResString::ex().getStrTblText(AETXT_TAG).GetString()));
        else
            s[4].Format("%s", (CResString::ex().getStrTblText(AETXT_UNBEGRENZT).GetString()));
        s[5] = sum.GetKzkdklasse(cABC);
        s[6].Format("%d", sum.GetQuota());
        s[7].Format("%d", sum.GetArticleno());

        if (!CListCtrlHelper::InsertItem(m_ListCtl, NUM_COLUMNS, s, lvi))
        {
            EndWaitCursor();
            return;
        }
        // wichtig für Sort
        lvi.iItem++;
    }
    m_iCountlist = m_ListCtl.GetItemCount();
    sum.CloseCursor();

    if (m_dlgProgress.GetSafeHwnd() != 0)
        m_dlgProgress.DestroyWindow();

    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
    GetDlgItem(IDC_BUTTON_DETAILS)->EnableWindow(FALSE);
}

// CompareListe ist eine stand alone Funktion
/////////////////////////////////////////////////////////////////////////////
// CompareListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
/////////////////////////////////////////////////////////////////////////////
int CALLBACK CompareQuotaListeUp(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    if (s->GetAt(lParam1) == s->GetAt(lParam2))
        return 0;
    else if (s->GetAt(lParam1) > s->GetAt(lParam2))
        return 1;
    else
        return -1;
}

int CALLBACK CompareQuotaListeDown(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    if (s->GetAt(lParam1) == s->GetAt(lParam2))
        return 0;
    else if (s->GetAt(lParam1) > s->GetAt(lParam2))
        return -1;
    else
        return 1;
}


void CDQuotaSum::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    int col;
    int max;
    int index;
    //Wegen Sort
    LV_ITEM lvi;
    //
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    col = pNMListView->iSubItem;

    max = m_ListCtl.GetItemCount();
    CStringArray s;
    CString sorttext;
    s.SetSize(m_iCountlist);
    for (index = 0; index < m_iCountlist; index++)
    {
        //StringArray an der ursprünglichen Position setzen
        lvi.iItem = index;
        lvi.mask = LVIF_PARAM;  //muss gesetzt sein, um lParam abzuholen
        if (!m_ListCtl.GetItem(&lvi))
            continue;    //Ursprungadresse steht in lParam
        s[(int)lvi.lParam] = m_ListCtl.GetItemText(index,col);
    }
    if (m_iCol == col)
    {
        if (m_iOrder == 0)
        {
            m_ListCtl.SortItems(CompareQuotaListeDown, (LPARAM)&s);
            m_iOrder = 1;
        }
        else
        {
            m_ListCtl.SortItems(CompareQuotaListeUp, (LPARAM)&s);
            m_iOrder = 0;
        }
    }
    else
    {
        m_ListCtl.SortItems(CompareQuotaListeUp, (LPARAM)&s);
        m_iOrder = 0;
    }
    m_iCol = col;

    *pResult = 0L;
}
