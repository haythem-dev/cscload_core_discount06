// DWannauswahl.cpp : implementation file
//

#include "stdafx.h"
#include "DDruckAuftrag.h"
#include "DWannauswahl.h"

//Definitionen Bearbeitet
#define DONE_YES    0
#define DONE_NO     1

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "", 40, LVCFMT_LEFT,
    1,  "", 50, LVCFMT_RIGHT,
    2,  "", 50, LVCFMT_CENTER,
    -1, "",  0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDWannauswahl dialog


CDWannauswahl::CDWannauswahl(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDWannauswahl::IDD, pParent), CPageBrowser(0)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_KZ_WANNEN);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_POS);
}

void CDWannauswahl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}

BEGIN_MESSAGE_MAP(CDWannauswahl, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BUTTON_ALL, OnButtonAll)
    ON_BN_CLICKED(IDC_BUTTON_SELECTED, OnButtonSelected)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_BUTTON_ANZ_SEITE, OnButtonAnzSeite)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDWannauswahl message handlers

BOOL CDWannauswahl::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_OK);
    idResources.push_back(IDI_ICON_NO);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    ppNTubPosition tubPosition;
    CAUFWANNEN aufwannen;
    BeginWaitCursor();
    for (it = m_lAuf->begin(); it != m_lAuf->end(); it++)
    {
        aufwannen.s.POSNR = it->POSNR;
        aufwannen.s.KDAUFTRAGNR = atol(m_Auftr_Nr);
        aufwannen.s.DATUM = m_datum;
        aufwannen.Server( AaauftSel_tub_pos );
        tubPosition.Number = aufwannen.s.KOBEHAELTNR;
        tubPosition.Lager_ort = aufwannen.s.LAGERFACHNR;
        tubPosition.Pos_nr = aufwannen.s.POSNR;
        m_Wann.insert(m_Wann.end(),tubPosition);
    }
    //nase m_Wann.sort(ppNTubPositionCompare());
    m_Wann.sort();
    FillList();
    EndWaitCursor();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDWannauswahl::FillList()
{
    //Variablen
    int wannennr;
    int anzpos;
    ppString Str;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    wannennr = m_Wann.begin()->Number;
    anzpos = 0;

    CLetterMan kb;
    for (wann_it = m_Wann.begin(); wann_it != m_Wann.end(); wann_it++)
    {
        if (wannennr == wann_it->Number)
        {
            anzpos++;
        }
        else
        {
            s[0] = kb.Next();
            s[1].Format("%ld", wannennr);
            s[2].Format("%d", anzpos);

            wannennr = wann_it->Number;
            anzpos = 1;

            if (!CListCtrlHelper::AppendImageItem(m_ListCtl, NUM_COLUMNS, s, DONE_NO))
            {
                return FALSE;
            }
        }

    } //Ende der for()-Schleife
    s[0] = kb.Next();
    s[1].Format("%ld", wannennr);
    s[2].Format("%d", anzpos);

    if (!CListCtrlHelper::AppendImageItem(m_ListCtl, NUM_COLUMNS, s, DONE_NO))
    {
        return FALSE;
    }

    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return TRUE;
}

void CDWannauswahl::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
}

void CDWannauswahl::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    int pos;
    OnKeydownList(pNMHDR, pResult, m_ListCtl, pos, true, false);

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (CLetterMan::InRange(pLVKeyDow->wVKey, m_ListCtl.GetItemCount()))
    {
        if (CListCtrlHelper::GetImage(m_ListCtl, pos) == DONE_YES) DelMarked(pos);
        else SetMarked(pos);
    }
}

void CDWannauswahl::OnButtonAll()
{
    int max = m_ListCtl.GetItemCount();
    for (int pos = 0; pos < max; pos++)
    {
        SetMarked(pos);
    }
    OnButtonSelected();
}

void CDWannauswahl::OnButtonSelected()
{
    int max = m_ListCtl.GetItemCount();
    if (m_DruckAuftrag.StartDruck(TRUE))
    {
        for (int pos = 0; pos < max; pos++)
        {
            if (CListCtrlHelper::GetImage(m_ListCtl, pos) == DONE_YES) Druck(pos);
        }
        m_DruckAuftrag.EndDruck();
    }
    CDialogMultiLang::OnCancel();
}

void CDWannauswahl::OnClickList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (CListCtrlHelper::GetImage(m_ListCtl, pos) == DONE_YES) DelMarked(pos);
    else SetMarked(pos);

    *pResult = 0L;
}

void CDWannauswahl::SetMarked(int pos)
{
    CListCtrlHelper::SetImageItemSelected(m_ListCtl, pos, DONE_YES);
}

void CDWannauswahl::DelMarked(int pos)
{
    CListCtrlHelper::SetImageItemSelected(m_ListCtl, pos, DONE_NO);
}

void CDWannauswahl::Druck(int pos)
{
    CString liste;
    CString Str;
    char underline[111] = {0};
    int menge = 0;
    memset(underline, '-', 110);
    underline[110] = '\0';
    short len = AeGetApp()->LagerortLen();
    if (len == 0)
    {
        len = 8;
    }
    int offset = 8 - len;

    liste.Format("%-15.15s %07.7s % 27.27s %-16.16s %-14.14s %-8.8s %-10.10s %-2.2s",
                    CResString::ex().getStrTblText(AETXT_KUNDEN_NR).GetString(), m_IDF_Nr.GetString(),
                    CResString::ex().getStrTblText(AETXT_TELEFON).GetString(), m_Tel.GetString(),
                    CResString::ex().getStrTblText(AETXT_ZEILEN).GetString(), m_Zln.GetString(),
                    CResString::ex().getStrTblText(AETXT_A_ART).GetString(), m_AA.GetString());
    m_DruckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-26.26s % 8.8s %-16.16s %-14.14s %-8.8s %-10.10s %-2.2s",
                    CResString::ex().getStrTblText(AETXT_INHABER).GetString(), m_Inhaber.GetString(),
                    CResString::ex().getStrTblText(AETXT_KURZWAHL).GetString(), m_Tel_KW.GetString(),
                    CResString::ex().getStrTblText(AETXT_AUF_WERT).GetString(), m_AW.GetString(),
                    CResString::ex().getStrTblText(AETXT_KOM_ART).GetString(), m_KA.GetString());
    m_DruckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-26.26s % 4.4s-%-3.3s %-16.16s %-14.14s %-8.8s %-10.10s %-2.2s",
                    CResString::ex().getStrTblText(AETXT_APOTHEKENNAME).GetString(), m_Apotheke.GetString(),
                    CResString::ex().getStrTblText(AETXT_ZEILEN_DAFUE).GetString(), CResString::ex().getStrTblText(AETXT_ART).GetString(), m_Dafue_Typ.GetString(),
                    CResString::ex().getStrTblText(AETXT_LIF_WERT).GetString(), m_Lif_Wert.GetString(),
                    CResString::ex().getStrTblText(AETXT_BUCH_ART).GetString(), m_BA.GetString());
    m_DruckAuftrag.AddKopfZeile(liste);

    liste.Format("%-8.8s %-6.6s %-26.26s % 8.8s %-16.16s %-14.14s %-8.8s %-4s: %-10.10s",
                    CResString::ex().getStrTblText(AETXT_PLZ_ORT).GetString(), m_PLZ.GetString(), m_Ort.GetString(),
                    CResString::ex().getStrTblText(AETXT_AUF_NR).GetString(), m_Auftr_Nr.GetString(),
                    CResString::ex().getStrTblText(AETXT_D_ZEILEN_WERT).GetString(), m_Dzw.GetString(),
                    CResString::ex().getStrTblText(AETXT_TOUR).GetString(), m_Tour.GetString());
    m_DruckAuftrag.AddKopfZeile(liste);

    if (m_LA_Nr.IsEmpty())
    {
        liste.Format("                                           %-8.8s %-16.16s %-14.14s %-8.8s %-10.10s %3.3s",
                    CResString::ex().getStrTblText(AETXT_AUF_NR_VSE).GetString(), m_Vsenr.GetString(),
                    CResString::ex().getStrTblText(AETXT_RECHNR).GetString(), m_Rech_Nr.GetString(),
                    CResString::ex().getStrTblText(AETXT_WANNEN_NR).GetString(), m_ListCtl.GetItemText(pos, 1).GetString());
    }
    else
    {
        liste.Format("                                           %-8.8s %-16.16s %-11.11s %-13.13s %-14.14s %-8.8s %-10.10s %5.5s",
                    CResString::ex().getStrTblText(AETXT_AUF_NR_VSE).GetString(), m_Vsenr.GetString(),
                    CResString::ex().getStrTblText(AETXT_RECHNR).GetString(), m_Rech_Nr.GetString(),
                    CResString::ex().getStrTblText(AETXT_WANNEN_NR).GetString(), m_ListCtl.GetItemText(pos, 1).GetString(),
                    m_Lauft_Nr.GetString(), m_LA_Nr.GetString());
    }
    m_DruckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-52.52s",
                    CResString::ex().getStrTblText(AETXT_PHONIE_INFO).GetString(), m_Kndtext.GetString());
    m_DruckAuftrag.AddKopfZeile(liste);

    liste.Format("%-15.15s %-52.52s",
                    CResString::ex().getStrTblText(IDS_BEMERK).GetString(), m_Bemerk.GetString());
    m_DruckAuftrag.AddKopfZeile(liste);

    m_DruckAuftrag.AddKopfZeile(underline);
    liste.Format("%-*.*s %-5.5s %-9.9s %-4.4s %-30.30s %-13.13s %-3.3s %-60.60s",
        len, len,
        CResString::ex().getStrTblText(AETXT_LAGERORT).GetString(),
            CResString::ex().getStrTblText(AETXT_MENGE).GetString(),
            CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
            CResString::ex().getStrTblText(AETXT_DAF).GetString(),
            CResString::ex().getStrTblText(AETXT_ARTIKELNAME).GetString(),
            CResString::ex().getStrTblText(AETXT_PZN).GetString(),
            CResString::ex().getStrTblText(AETXT_PNR).GetString(),
            CResString::ex().getStrTblText(IDS_BEMERK).GetString());
    m_DruckAuftrag.AddKopfZeile(liste);

    m_DruckAuftrag.AddKopfZeile(underline);
    m_DruckAuftrag.AddFussZeile(underline);
    liste = CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d";
    liste += "                                        ";
    liste += CResString::ex().getStrTblText(AETXT_DATUM);
    liste += ": ";
    liste += m_Datum;
    m_DruckAuftrag.AddFussZeile (liste);
    int wannennr = atoi(m_ListCtl.GetItemText(pos, 1));
    for (wann_it = m_Wann.begin(); wann_it != m_Wann.end(); wann_it++)
    {
        if (wann_it->Number != wannennr)
            continue;
        for (it = m_lAuf->begin(); it != m_lAuf->end(); it++)
        {
            if (it->POSNR == wann_it->Pos_nr)
            {
                // wann_it->Lager_ort.c_str()
                menge = it->MENGEABGEBUCHT + it->MENGENATRA - it->MENGE;
                if (it->ARTIKEL_NR == -1)
                {
                    liste.Format("%-*.*s %5ld %-9.9s %-4.4s %-30.30s                 %3ld %-60.60s",
                        len, len, wann_it->Lager_ort.c_str() + offset,
                        menge,
                        it->EINHEIT,
                        it->DARREICHFORM,
                        it->ARTIKEL_NAME,
                        it->POSNR,
                        it->BEMERKUNG);
                }
                else
                {
                    AllgEntfSpaces(it->ARTICLE_CODE);
                    liste.Format("%-*.*s %5ld %-9.9s %-4.4s %-30.30s %-13.13s %3ld %-60.60s",
                        len, len, wann_it->Lager_ort.c_str() + offset,
                        menge,
                        it->EINHEIT,
                        it->DARREICHFORM,
                        it->ARTIKEL_NAME,
                        it->ARTICLE_CODE,
                        it->POSNR,
                        it->BEMERKUNG);
                }
                m_DruckAuftrag.AddPosZeile(liste);
            }
        }
    }
    m_DruckAuftrag.PageDruck();
    m_DruckAuftrag.DelAllData();
}

void CDWannauswahl::OnButtonAnzSeite()
{
    CDWannAnz dlgWannAnz;
    CDWannAnz::ANZ anz;
    dlgWannAnz.m_lAuf.clear();
    dlgWannAnz.m_CAufNr = m_Auftr_Nr;
    int pos = m_ListCtl.GetNextItem(-1,LVNI_SELECTED);
    int wannennr = atoi(m_ListCtl.GetItemText(pos, 1));
    dlgWannAnz.m_CSeite = m_ListCtl.GetItemText(pos, 1);
    for (wann_it = m_Wann.begin(); wann_it != m_Wann.end(); wann_it++)
    {
        if (wann_it->Number != wannennr)
            continue;
        for (it = m_lAuf->begin(); it != m_lAuf->end(); it++)
        {
            if (it->POSNR == wann_it->Pos_nr)
            {
                strcpy(anz.LAGERORT, wann_it->Lager_ort.c_str());
                anz.MENGE = it->MENGEABGEBUCHT + it->MENGENATRA;
                strcpy(anz.EINHEIT, it->EINHEIT);
                strcpy(anz.DARREICHFORM, it->DARREICHFORM);
                strcpy(anz.ARTIKEL_NAME, it->ARTIKEL_NAME);
                AllgEntfSpaces(it->ARTICLE_CODE);
                strcpy(anz.ARTICLE_CODE, it->ARTICLE_CODE);
                anz.ARTIKEL_NR = it->ARTIKEL_NR;
                anz.POSNR = it->POSNR;
                strcpy(anz.BEMERKUNG, it->BEMERKUNG);
                anz.MENGEBESTELLT = it->MENGEBESTELLT;
                dlgWannAnz.m_lAuf.insert(dlgWannAnz.m_lAuf.end(), anz);
            }
        }
    }
    dlgWannAnz.DoModal();
}

void CDWannauswahl::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnButtonAnzSeite();
    *pResult = 0L;
}
/////////////////////////////////////////////////////////////////////////////
// CDWannAnz dialog

#define NUM_COLUMNS1    9

static COLUMNS_TYPES Columns1[] =
{
    0,  "",  65, LVCFMT_RIGHT,
    1,  "",  50, LVCFMT_RIGHT,
    2,  "",  50, LVCFMT_RIGHT,
    3,  "",  70, LVCFMT_RIGHT,
    4,  "",  50, LVCFMT_RIGHT,
    5,  "", 190, LVCFMT_LEFT,
    6,  "",  60, LVCFMT_CENTER,
    7,  "",  40, LVCFMT_RIGHT,
    8,  "", 200, LVCFMT_LEFT,
    -1, "",   0, 0
};


CDWannAnz::CDWannAnz(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDWannAnz::IDD, pParent)
{
    m_CAufNr = _T("");
    m_CSeite = _T("");

    Columns1[0].Columns = CResString::ex().getStrTblText(AETXT_LAGERORT);
    Columns1[1].Columns = CResString::ex().getStrTblText(AETXT_AMGE);
    Columns1[2].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns1[3].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns1[4].Columns = CResString::ex().getStrTblText(AETXT_DAF);
    Columns1[5].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns1[6].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Columns1[7].Columns = CResString::ex().getStrTblText(AETXT_PNR);
    Columns1[8].Columns = CResString::ex().getStrTblText(IDS_BEMERK);
}


void CDWannAnz::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_STATIC_AUF_NR, m_CAufNr);
    DDX_Text(pDX, IDC_STATIC_SEITE, m_CSeite);
}


BEGIN_MESSAGE_MAP(CDWannAnz, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDWannAnz message handlers

BOOL CDWannAnz::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CString Hilfe;
    char str[241];
    short len = AeGetApp()->LagerortLen();
    if (len == 0)
        len = 8;
    int offset = 8 - len;

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns1, m_ListCtl))
    {
        return FALSE;
    }

    for (it = m_lAuf.begin(); it != m_lAuf.end(); it++)
    {
        int pos = m_ListCtl.GetItemCount();
        Hilfe.Format("%-*.*s", len, len, it->LAGERORT + offset);
        if (m_ListCtl.InsertItem(pos, Hilfe) == -1)
            return FALSE;
        m_ListCtl.SetItemText(pos, 1, _ltoa(it->MENGEBESTELLT, str, 10));
        m_ListCtl.SetItemText(pos, 2, _ltoa(it->MENGE, str, 10));
        m_ListCtl.SetItemText(pos, 3, it->EINHEIT);
        m_ListCtl.SetItemText(pos, 4, it->DARREICHFORM);
        m_ListCtl.SetItemText(pos, 5, it->ARTIKEL_NAME);
        if (it->ARTIKEL_NR != -1)
        {
            m_ListCtl.SetItemText(pos, 6, it->ARTICLE_CODE);
        }
        m_ListCtl.SetItemText(pos, 7, _ltoa(it->POSNR, str, 10));
        m_ListCtl.SetItemText(pos, 8, it->BEMERKUNG);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
