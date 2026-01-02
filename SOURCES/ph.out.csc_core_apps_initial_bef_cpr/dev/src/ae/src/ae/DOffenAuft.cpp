// DOffenAuft.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artsel.h>
#include "DOffenAuft.h"
#include <statistics.h>
#include "DDruckAuftrag.h"


//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     9

static COLUMNS_TYPES Columns[] =
{
    0,  "",  60, LVCFMT_LEFT,
    1,  "",  70, LVCFMT_LEFT,
    2,  "", 200, LVCFMT_LEFT,
    3,  "",  30, LVCFMT_LEFT,
    4,  "",  80, LVCFMT_LEFT,
    5,  "",  50, LVCFMT_LEFT,
    6,  "",  40, LVCFMT_LEFT,
    7,  "",  50, LVCFMT_LEFT,
    8,  "",  80, LVCFMT_LEFT,
    -1, "",   0, 0
};

// CDOffenAuft-Dialogfeld

IMPLEMENT_DYNAMIC(CDOffenAuft, CDialog)
CDOffenAuft::CDOffenAuft(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDOffenAuft::IDD, pParent)
    , m_cAArt(_T(""))
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_HERSTEL);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_DRF);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_NATRA);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_KURZ_BESTAND);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
}

CDOffenAuft::~CDOffenAuft()
{
}

void CDOffenAuft::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_AART, m_edit_AArt);
    DDX_Text(pDX, IDC_EDIT_AART, m_cAArt);
    DDX_Control(pDX, IDC_LIST, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDOffenAuft, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnBnClickedButtonDruck)
    ON_EN_CHANGE(IDC_EDIT_AART, OnEnChangeEditAart)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, OnLvnColumnclickList)
END_MESSAGE_MAP()


// CDOffenAuft-Meldungshandler

BOOL CDOffenAuft::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_cAArt = "UW";
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDOffenAuft::OnBnClickedOk()
{
    //Wegen Sort
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM | LVIF_TEXT;
    lvi.iSubItem = 0;
    lvi.iItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;
    //

    COFFENAUFTRAG offenauftrag;
    CARTAESEL artaesel;
    ppString Einheit;
    ppString Drf;
    ppString Name;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    UpdateData();
    offenauftrag.SetKdauftragart(m_cAArt);
    offenauftrag.SetFilialnr(AeGetApp()->VzNr());
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    for (int i = 0; ; i++)
    {
        if (offenauftrag.SelList() != SRV_OK)
            break;
        // wichtig für Sort
        lvi.lParam = (LPARAM) i;
        s[0].Format("% 11d", offenauftrag.GetHersteller_nr());
        s[1] = offenauftrag.GetEinheit(Einheit);
        s[2] = offenauftrag.GetArtikel_name(Name);
        s[3] = offenauftrag.GetDarreichform(Drf);
        artaesel.s.ARTIKEL_NR = offenauftrag.GetArtikel_nr();
        BeginWaitCursor();
        artaesel.Server(AatartSel_Preferred);
        AllgEntfSpaces(artaesel.s.ARTICLE_CODE);
        EndWaitCursor();
        s[4] = artaesel.s.ARTICLE_CODE;
        s[5].Format("% 7d", offenauftrag.GetMengebestellt());
        s[6].Format("% 5d", offenauftrag.GetMengenatra());
        s[7].Format("% 7d", offenauftrag.GetBestand());
        s[8] = DDMMYYYYStringFromDateLong(offenauftrag.GetDatumauslieferung());

        if (!CListCtrlHelper::InsertItem(m_ListCtl, NUM_COLUMNS, s, lvi, 1))
        {
            EndWaitCursor();
            return;
        }
        // wichtig für Sort
        ++lvi.iItem;
    }
    offenauftrag.CloseCursor();
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK( IDP_NO_DATA );
    GotoDlgCtrl(GetDlgItem(IDC_LIST));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);
}

void CDOffenAuft::OnBnClickedButtonDruck()
{
    CDruckAuftrag druckAuftrag;
    CTM zeit;
    CString liste, name, test;
    char Datum[11];
    int pos, maxpos;
    char underline[111];
    memset(underline, '-', 110);
    underline[110] = '\0';
    zeit.Server(AafilGetdatetime);
    AllgDatumLong2CharTTMMJJJJ(zeit.s.DATUM, Datum);
    this->GetWindowText(name);
    liste.Format("      %s     %s", name.GetString(), Datum);
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);

    liste.Format("%-11.11s %-9.9s %-30.30s %3.3s %-13.13s %-7.7s %-5.5s %-7.7s %-10.10s",
                CResString::ex().getStrTblText(AETXT_HERSTEL).GetString(),
                CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
                CResString::ex().getStrTblText(AETXT_BEZEICHNUNG).GetString(),
                CResString::ex().getStrTblText(AETXT_DRF).GetString(),
                CResString::ex().getStrTblText(AETXT_ARTICLE_CODE).GetString(),
                CResString::ex().getStrTblText(AETXT_MENGE).GetString(),
                CResString::ex().getStrTblText(AETXT_NATRA).GetString(),
                CResString::ex().getStrTblText(AETXT_KURZ_BESTAND).GetString(),
                CResString::ex().getStrTblText(AETXT_DATUM).GetString()
                );
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
    test = m_ListCtl.GetItemText(pos, 4);
    liste.Format("%-11.11s %-9.9s %-30.30s %3.3s %13.13s %-7.7s %-5.5s %-7.7s %-10.10s",
            m_ListCtl.GetItemText(pos, 0).GetString(),
            m_ListCtl.GetItemText(pos, 1).GetString(),
            m_ListCtl.GetItemText(pos, 2).GetString(),
            m_ListCtl.GetItemText(pos, 3).GetString(),
            m_ListCtl.GetItemText(pos, 4).GetString(),
            m_ListCtl.GetItemText(pos, 5).GetString(),
            m_ListCtl.GetItemText(pos, 6).GetString(),
            m_ListCtl.GetItemText(pos, 7).GetString(),
            m_ListCtl.GetItemText(pos, 8).GetString()
            );
    druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(1);
    druckAuftrag.DelAllData();
}

void CDOffenAuft::OnEnChangeEditAart()
{
    AllgLaengeKontr(&m_edit_AArt, L_OFFENAUFTRAG_KDAUFTRAGART,AeGetApp()->Modus());
}

// CompareListe ist eine stand alone Funktion
/////////////////////////////////////////////////////////////////////////////
// CompareListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
/////////////////////////////////////////////////////////////////////////////
int CALLBACK CompareOffenListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    if (s->GetAt(lParam1) == s->GetAt(lParam2))
        return 0;
    else if (s->GetAt(lParam1) > s->GetAt(lParam2))
        return 1;
    else
        return -1;
}

void CDOffenAuft::OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
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
        lvi.mask = LVIF_PARAM;      //muss gesetzt sein, um lParam abzuholen
        m_ListCtl.GetItem(&lvi);    //Ursprungadresse steht in lParam
        s[(int)lvi.lParam] = m_ListCtl.GetItemText(index,col);
    }
    m_ListCtl.SortItems(CompareOffenListe, (LPARAM)&s);

    *pResult = 0L;
}
