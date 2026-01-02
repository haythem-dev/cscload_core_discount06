// DVbLief.cpp : implementation file
//

#include "stdafx.h"
#include "DVbLief.h"
#include "vblief.h"
#include "DDruckAuftrag.h"


//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     9

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  55, LVCFMT_LEFT,
    2,  "", 130, LVCFMT_LEFT,
    3,  "",  50, LVCFMT_LEFT,
    4,  "",  80, LVCFMT_LEFT,
    5,  "",  55, LVCFMT_LEFT,
    6,  "",  40, LVCFMT_LEFT,
    7,  "",  55, LVCFMT_LEFT,
    8,  "", 130, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDVbLief dialog


CDVbLief::CDVbLief(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDVbLief::IDD, pParent), CPageBrowser(0)
{
    m_CDatum = _T("");
    m_CHaus = _T("");

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_KURZWAHL);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_TELEFON);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
}

void CDVbLief::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_HAUS, m_EditHaus);
    DDX_Control(pDX, IDC_EDIT_DATUM, m_EditDatum);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_EDIT_HAUS, m_CHaus);
}

BEGIN_MESSAGE_MAP(CDVbLief, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_EN_CHANGE(IDC_EDIT_DATUM, OnChangeEditDatum)
    ON_EN_CHANGE(IDC_EDIT_HAUS, OnChangeEditHaus)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDVbLief message handlers

BOOL CDVbLief::OnInitDialog()
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

bool CDVbLief::GetPage(int /*nKzUpDown=NEXT_PG*/)
{
    CVBLIEF vblief;
    long helpdate;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        vblief.s.FETCH_REL = 1;          //normaler Fetch
        vblief.s.IDFNR = atol(m_CHaus);  // Idfnr für Hausnr.-uebergabe benutzt
        vblief.s.MENGE = AeGetApp()->VzNr();  // Menge für VZnr.-uebergabe benutzt
        m_lKumMenge = 0;
        m_lKumZeilen = 0;
        if (m_CDatum.IsEmpty())
        {
            vblief.s.DATUM = 0;
        }
        else if ((helpdate = AllgDatumEingKonv(m_CDatum, ALGF_FORM_DATUM_TTMMJJ)) < 0)
        {
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_DATUM));
            return FALSE;
        }
        else vblief.s.DATUM = helpdate;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        vblief.Server(Aaauft_Sel_vblief);
        m_bCursorOpen = true;       //Datenbankcurser offen
        vblief.s.FETCH_REL = 1;          //normaler Fetch
        if (vblief.rc == SRV_SQLNOTFOUND)
        {
            if (m_bFirstDataset)      //kein Satz gefunden
            {
                CloseCursor();
                EndWaitCursor();
                return FALSE;
            }
            break;
        }
        m_bFirstDataset = false;
        //Ausgabe in die Listbox
        s[0] = kb.Next();
        s[1].Format("%d", vblief.s.IDFNR);
        AllgEntfSpaces(vblief.s.NAMEAPO);
        s[2] = vblief.s.NAMEAPO;
        AllgEntfSpaces(vblief.s.TELKURZWAHL);
        s[3] = vblief.s.TELKURZWAHL;
        AllgEntfSpaces(vblief.s.TELNR);
        s[4] = vblief.s.TELNR;
        s[5].Format("%d", vblief.s.ARTIKEL_NR);
        s[6].Format("%d", vblief.s.MENGE);
        m_lKumMenge += vblief.s.MENGE;
        m_lKumZeilen++;
        AllgEntfSpaces(vblief.s.EINHEIT);
        s[7] = vblief.s.EINHEIT;
        AllgEntfSpaces(vblief.s.ARTIKEL_NAME);
        s[8] = vblief.s.ARTIKEL_NAME;

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    // Ausgeben kumulierte Werte
    s[0] = kb.Next();
    s[1].Empty();
    s[2] = "Zeilen:";
    s[3].Format("%d", m_lKumZeilen);
    s[4].Empty();
    s[5] = "Menge";
    s[6].Format("%d", m_lKumMenge);
    s[7].Empty();
    s[8].Empty();

    if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
    {
        EndWaitCursor();
        return FALSE;
    }

    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return TRUE;
}

void CDVbLief::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDVbLief::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CVBLIEF vblief;
    vblief.s.FETCH_REL = 0;
    BeginWaitCursor();
    vblief.Server(Aaauft_Sel_vblief);
    EndWaitCursor();
    ResetCursor();
}

void CDVbLief::OnOK()
{
    UpdateData();
    CloseCursor();
    GetPage();
}

void CDVbLief::OnChangeEditDatum()
{
    AllgDatumKontr(&m_EditDatum,ALGF_FORM_DATUM_TTMMJJ);
}

void CDVbLief::OnButtonDruck()
{
    if (m_bFirstDataset)
        return;
    CDruckAuftrag druckAuftrag;
    CString liste;
    char underline[111];
    int maxpos, pos;
    memset(underline, '-', 110);
    underline[110] = '\0';
    liste.Format("%-7.7s %-40.40s %-4.4s %-20.20s %-7.7s %-4.4s %-9.9s %-29.29s",
        CResString::ex().getStrTblText(AETXT_IDF_NR).GetString(),
        CResString::ex().getStrTblText(AETXT_APOTHEKENNAME).GetString(),
        CResString::ex().getStrTblText(AETXT_KURZWAHL).GetString(),
        CResString::ex().getStrTblText(AETXT_TELEFON).GetString(),
        CResString::ex().getStrTblText(AETXT_PZN).GetString(),
        CResString::ex().getStrTblText(AETXT_MENGE).GetString(),
        CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
        CResString::ex().getStrTblText(AETXT_ARTIKELNAME).GetString() );
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);
    liste = CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d";
    druckAuftrag.AddFussZeile(liste);

    maxpos = m_ListCtl.GetItemCount();
    for (pos = 0; pos < maxpos; pos++)
    {
        liste.Format("%-7.7s %-40.40s %-4.4s %-20.20s %-7.7s %-4.4s %-9.9s %-29.29s",
            m_ListCtl.GetItemText(pos, 1).GetString(),
            m_ListCtl.GetItemText(pos, 2).GetString(),
            m_ListCtl.GetItemText(pos, 3).GetString(),
            m_ListCtl.GetItemText(pos, 4).GetString(),
            m_ListCtl.GetItemText(pos, 5).GetString(),
            m_ListCtl.GetItemText(pos, 6).GetString(),
            m_ListCtl.GetItemText(pos, 7).GetString(),
            m_ListCtl.GetItemText(pos, 8).GetString());
        druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(2);
    druckAuftrag.DelAllData();
}


void CDVbLief::OnChangeEditHaus()
{
    AllgWertKontr(&m_EditHaus, MAXIMUM_FILIALE);
}
