// DTourAusw.cpp : implementation file
//

#include "stdafx.h"
#include "DTourAusw.h"
#include "DTourBearb.h"
#include "aatour.h"

#define MAXIMUM_BAHNHOF 99
#define MAXIMUM_TOUR    999999

#define ZEILEN 12

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     11

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  60, LVCFMT_RIGHT,
    2,  "", 120, LVCFMT_LEFT,
    3,  "",  40, LVCFMT_RIGHT,
    4,  "",  50, LVCFMT_CENTER,
    5,  "",  50, LVCFMT_RIGHT,
    6,  "",  50, LVCFMT_RIGHT,
    7,  "",  50, LVCFMT_RIGHT,
    8,  "",  50, LVCFMT_RIGHT,
    9,  "",  50, LVCFMT_RIGHT,
    10, "",  40, LVCFMT_CENTER,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDTourAusw dialog


CDTourAusw::CDTourAusw(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDTourAusw::IDD, pParent), CPageBrowser(ZEILEN)
{
    m_CZeit = _T("");
    m_CBhf = _T("");
    m_CBezeichnung = _T("");
    m_CTour = _T("");

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TOUR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_KURZ_KILOMETER);
    Columns[4].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_AUF_ERF);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_AUF_FAKT);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_KZ_WANNEN);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_KND_SOLL);
    Columns[9].Columns = CResString::ex().getStrTblText(AETXT_KND_IST);
    Columns[10].Columns = CResString::ex().getStrTblText(AETXT_STATUS);
}

void CDTourAusw::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_TOUR, m_EditTour);
    DDX_Control(pDX, IDC_EDIT_BEZEICHNUNG, m_EditBezeichnung);
    DDX_Control(pDX, IDC_EDIT_BAHNHOF, m_EditBhf);
    DDX_Control(pDX, IDC_EDIT_ABZEIT, m_EditZeit);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_ABZEIT, m_CZeit);
    DDX_Text(pDX, IDC_EDIT_BAHNHOF, m_CBhf);
    DDX_Text(pDX, IDC_EDIT_BEZEICHNUNG, m_CBezeichnung);
    DDX_Text(pDX, IDC_EDIT_TOUR, m_CTour);
}

BEGIN_MESSAGE_MAP(CDTourAusw, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_EN_CHANGE(IDC_EDIT_ABZEIT, OnChangeEditAbzeit)
    ON_EN_CHANGE(IDC_EDIT_BAHNHOF, OnChangeEditBahnhof)
    ON_EN_CHANGE(IDC_EDIT_BEZEICHNUNG, OnChangeEditBezeichnung)
    ON_EN_CHANGE(IDC_EDIT_TOUR, OnChangeEditTour)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTourAusw message handlers

BOOL CDTourAusw::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDTourAusw::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    static CTOURUEBERS touruebers;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        CString CTourid;
        touruebers.s.TOURSTRECKE = AeGetApp()->FilialNr();
        if (m_CTour.GetLength() > 0)
        {
            m_EditZeit.SetWindowText(""); //da Tour eingetragen ungültig
            m_EditBhf.SetWindowText("");  //da Tour eingetragen ungültig
            m_EditBezeichnung.SetWindowText("");  //da Tour eingetragen ungültig
            AllgTourEingKonv(CTourid, m_CTour);
            AllgStrCopy(touruebers.s.TOURSTAT, "0", L_TOURUEBERS_TOURSTAT); //Tour als ganzes eingegeben
            AllgStrCopy(touruebers.s.BEZEICHNUNG, "", L_TOURUEBERS_BEZEICHNUNG);
        }
        else
        {
            long zeit, bhf;
            AllgStrCopy(touruebers.s.TOURSTAT, "1", L_TOURUEBERS_TOURSTAT); // Tour ind Zeit separat eingegeben
            AllgStrCopy(touruebers.s.BEZEICHNUNG, m_CBezeichnung, L_TOURUEBERS_BEZEICHNUNG);
            if (m_CBhf.GetLength() > 0 && m_CZeit.GetLength() > 0)
            {
                zeit = atol(m_CZeit);
                bhf = atol(m_CBhf);
                CTourid.Format("%04d%02d", zeit, bhf);
            }
            else if (m_CBhf.GetLength() > 0)
            {
                bhf = atol(m_CBhf);
                CTourid.Format("????%02d", bhf);
            }
            else if (m_CZeit.GetLength() > 0)
            {
                zeit = atol(m_CZeit);
                CTourid.Format("%04d??", zeit);
            }
            else
            {
                CTourid = "??????";
            }
        }
        AllgStrCopy(touruebers.s.TOURID, CTourid, L_TOURUEBERS_TOURID);
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, touruebers.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        touruebers.Server(AatourSel_tour_uebers);
        m_bCursorOpen = true;       //Datenbankcurser offen
        touruebers.s.FETCH_REL = 1;          //normaler Fetch
        if (touruebers.rc == SRV_SQLNOTFOUND)
        {
            if (m_bFirstDataset)     //kein Satz gefunden
            {
                CloseCursor();
                EndWaitCursor();
                return false;
            }
            SetItemCountOfCurrentPage(i); //Anzahl Artikel letzte Seite
            break;
        }
        m_bFirstDataset = false;
        //Ausgabe in die Listbox
        s[0] = kb.Next();
        AllgEntfSpaces(touruebers.s.TOURID);
        AllgTourAusgKonv(s[1], touruebers.s.TOURID);
        AllgEntfSpaces(touruebers.s.BEZEICHNUNG);
        s[2].Format("%s", touruebers.s.BEZEICHNUNG);
        s[3].Format("%d", touruebers.s.TOURSTRECKE);
        s[4].Format("%02d:%02d", touruebers.s.FAHRTZEIT / 100, touruebers.s.FAHRTZEIT % 100);
        s[5].Format("%d", touruebers.s.ANZ_ERFASST);
        s[6].Format("%d", touruebers.s.ANZ_FAKTUR);
        s[7].Format("%d", touruebers.s.ANZ_WANNEN);
        s[8] = " ";
        s[9] = " ";
        AllgEntfSpaces(touruebers.s.TOURSTAT);
        s[10].Format("%s", touruebers.s.TOURSTAT);

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return false;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return true;
}

void CDTourAusw::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDTourAusw::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CTOURUEBERS touruebers;
    touruebers.s.FETCH_REL = 0;
    BeginWaitCursor();
    touruebers.Server(AatourSel_tour_uebers);
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDTourAusw::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        SelectTour();
        return;
    }
    UpdateData();
    CloseCursor();
    GetPage();
}

void CDTourAusw::SelectTour()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CString AusgTour;
        CDTourBearb dlgTourBearb;
        AusgTour = m_ListCtl.GetItemText(pos, 1);
        AllgTourKonvFromAusg(dlgTourBearb.m_Tour, AusgTour);
        dlgTourBearb.DoModal();
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDTourAusw::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDTourAusw::OnChangeEditAbzeit()
{
    AllgWertKontr(&m_EditZeit, MAXIMUM_ZEIT);
}

void CDTourAusw::OnChangeEditBahnhof()
{
    AllgWertKontr(&m_EditBhf, MAXIMUM_BAHNHOF);
}

void CDTourAusw::OnChangeEditBezeichnung()
{
    AllgLaengeKontr(&m_EditBezeichnung, L_TOURUEBERS_BEZEICHNUNG,AeGetApp()->Modus());
}

void CDTourAusw::OnChangeEditTour()
{
    AllgWertKontr(&m_EditTour, MAXIMUM_TOUR);
}

void CDTourAusw::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectTour();
    *pResult = 0L;
}

void CDTourAusw::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}
