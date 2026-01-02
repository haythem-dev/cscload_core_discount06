// DTourBearb.cpp : implementation file
//

#include "stdafx.h"
#include "DTourBearb.h"
#include "DInfAnzAuft.h"
#include "DTourEtAend.h"
#include "DDruckAuftrag.h"
#include "aatour.h"
#include "aeorderstat.h"
#include "aaclasses.h"


//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     15

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  40, LVCFMT_RIGHT,
    2,  "",  50, LVCFMT_RIGHT,
    3,  "",  30, LVCFMT_CENTER,
    4,  "", 119, LVCFMT_LEFT,
    5,  "",  80, LVCFMT_LEFT,
    6,  "",  40, LVCFMT_LEFT,
    7,  "",  30, LVCFMT_RIGHT,
    8,  "",  30, LVCFMT_RIGHT,
    9,  "",  40, LVCFMT_RIGHT, /*AET_ANZ_ZUR_WANNEN*/
    10, "",  30, LVCFMT_RIGHT,
    11, "",  30, LVCFMT_RIGHT,
    12, "",  30, LVCFMT_RIGHT,
    13, "",   1, LVCFMT_RIGHT, /*SO*/
    14, "",  30, LVCFMT_CENTER,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDTourBearb dialog


CDTourBearb::CDTourBearb(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDTourBearb::IDD, pParent), CPageBrowser(0)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_KURZ_FOLGE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_KURZ_AUFTR_NR);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_KZ_AUFTRAGSART);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_KURZWAHL);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_KZ_URSPR_BAHNHOF);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_KZ_ANZ_WANNEN);
    Columns[10].Columns = CResString::ex().getStrTblText(AETXT_ANZ_ZUS_WANNEN);
    Columns[11].Columns = CResString::ex().getStrTblText(AETXT_ANZ_SONDERWANNEN);
    Columns[12].Columns = CResString::ex().getStrTblText(AETXT_ANZ_BEIPACKS);
    Columns[14].Columns = CResString::ex().getStrTblText(AETXT_ST);
}


void CDTourBearb::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDTourBearb, CDialogMultiLang)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_BUTTON_FOLGE, OnButtonFolge)
    ON_BN_CLICKED(IDC_BUTTON_SOWANNE, OnButtonSowanne)
    ON_BN_CLICKED(IDC_BUTTON_TOUR, OnButtonTour)
    ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTourBearb message handlers

BOOL CDTourBearb::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    Ausgabe();
    return FALSE;  // return TRUE unless you set the focus to a control
                   // EXCEPTION: OCX Property Pages should return FALSE
}

void CDTourBearb::Ausgabe()
{
    AusgabeKopf();
    AusgabeAuftraege();
}

void CDTourBearb::AusgabeKopf()
{
    CTOURUEBERS touruebers;
    CString CStr;

    touruebers.s.TOURSTRECKE = AeGetApp()->FilialNr();
    AllgStrCopy(touruebers.s.TOURID, m_Tour, L_TOURUEBERS_TOURID);
    touruebers.Server(AatourGet_tour_kopf);

    AllgTourAusgKonv(CStr, m_Tour);
    GetDlgItem(IDC_STATIC_TOURID)->SetWindowText(CStr);
    GetDlgItem(IDC_STATIC_BEZEICHNUNG)->SetWindowText(touruebers.s.BEZEICHNUNG);
    CStr.Format("%d", touruebers.s.TOURSTRECKE);
    GetDlgItem(IDC_STATIC_KM)->SetWindowText(CStr);
    CStr.Format("%02d:%02d", touruebers.s.FAHRTZEIT/100, touruebers.s.FAHRTZEIT%100);
    GetDlgItem(IDC_STATIC_FAHRZEIT)->SetWindowText(CStr);
    CStr.Format("%d", touruebers.s.ANZ_ERFASST);
    GetDlgItem(IDC_STATIC_ERFASST)->SetWindowText(CStr);
    CStr.Format("%d", touruebers.s.ANZ_FAKTUR);
    GetDlgItem(IDC_STATIC_FAKTURIERT)->SetWindowText(CStr);
    CStr.Format("%d", touruebers.s.ANZ_WANNEN);
    GetDlgItem(IDC_STATIC_WANNEN)->SetWindowText(CStr);
    GetDlgItem(IDC_STATIC_SOL)->SetWindowText("");
    GetDlgItem(IDC_STATIC_IST)->SetWindowText("");
    GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(touruebers.s.TOURSTAT);
}

void CDTourBearb::AusgabeAuftraege()
{
    CTOURINHALT tourinhalt;
    CStringArray s;
    COrdStat     ordStat;
    s.SetSize(NUM_COLUMNS);
    CString CStr;

    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    AllgStrCopy(tourinhalt.s.TOURID, m_Tour, L_TOURUEBERS_TOURID);
    tourinhalt.s.ANZBTM = AeGetApp()->FilialNr(); // zweckenfremdet
    CLetterMan kb;
    for (int i = 1; ; i++)
    {
        tourinhalt.s.FETCH_REL = 1;          //normaler Fetch
        tourinhalt.Server(AatourSel_auf_tour);
        if (tourinhalt.rc != SRV_OK)
            break;
        s[0] = kb.Next();
        s[1].Format("%d", tourinhalt.s.REIHENFOLGENR);
        s[2].Format("%d", tourinhalt.s.KDAUFTRAGNR);
        AllgEntfSpaces(tourinhalt.s.KDAUFTRAGART);
        s[3].Format("%s", tourinhalt.s.KDAUFTRAGART);
        AllgEntfSpaces(tourinhalt.s.NAMEAPO);
        s[4].Format("%s", tourinhalt.s.NAMEAPO);
        AllgEntfSpaces(tourinhalt.s.ORT);
        s[5].Format("%s", tourinhalt.s.ORT);
        s[6].Format("%s", tourinhalt.s.TELKURZWAHL);
        AllgTourGetBhf(s[7], tourinhalt.s.TOURIDALT);
        s[8].Format("%d", tourinhalt.s.ANZBEHAELT);
        s[9] = " "; //nase
        s[10].Format("%d", tourinhalt.s.ANZBEHAELTWECHSEL);
        s[11].Format("%d", tourinhalt.s.ANZSONDERWANNE);
        s[12].Format("%d", tourinhalt.s.ANZCONTAINER);
        s[13] = " "; //nase
        ordStat.SetOrdStat(tourinhalt.s.KDAUFTRAGSTAT);
        ordStat.GetOrdStatCStr(s[14]);

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
     }
    tourinhalt.s.FETCH_REL  = 0;             //close Cursor
    tourinhalt.Server(AatourSel_auf_tour);
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, 0);
    EndWaitCursor();
}

void CDTourBearb::MarkListPosChar(int Letter)
{
    int pos;
    if (CListCtrlHelper::GetListPositionByChar(m_ListCtl, Letter, pos))
    {
        CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCtl, pos);
    }
}

void CDTourBearb::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    if (OnKeydownList(pNMHDR, pResult, m_ListCtl, false, false))
    {
        return;
    }

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (CLetterMan::InAZRange(pLVKeyDow->wVKey))
    {
        MarkListPosChar((int)(pLVKeyDow->wVKey));
        /*if ((GetKeyState(VK_SHIFT) & 0x8000) == 0x8000)
        {
            CString cstr;
            long artikel_nr;
            long m;
            artikel_nr=SelListPos(&m,cstr,cstr,cstr);
            if (artikel_nr!=0)
            {
                CDArtInf dlgArtInf( artikel_nr );
                dlgArtInf.DoModal();
            }
        }*/
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == VK_F5)
    {
        Aenderung(ETAA_TOUR);
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == VK_F6)
    {
        Aenderung(ETAA_TOURFOLGE);
        *pResult = 1L;
        return;
    }
    if (pLVKeyDow->wVKey == VK_F7)
    {
        Aenderung(ETAA_SONDERWANNE);
        *pResult = 1L;
        return;
    }
}

void CDTourBearb::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        CString Status;
        long AufNr = GetAuftrNr(Status);
        if (AufNr == 0) return;
        CDInfAnzAuft dlgInfAnzAuft;
        dlgInfAnzAuft.m_AuftrNr = AufNr;
        dlgInfAnzAuft.DoModal();
        return;
    }
}

long CDTourBearb::GetAuftrNr(CString &Status)
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return 0;
    }
    CString AufNr = m_ListCtl.GetItemText(pos, 2);
    Status = m_ListCtl.GetItemText(pos, 14);
    return atol(AufNr);
}

void CDTourBearb::Aenderung(int AenderungsArt)
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    CString Status = m_ListCtl.GetItemText(pos, 14);
    if (!(GetAeUser().UpdTour()))
    {
        MsgBoxOK(IDP_FKT_KENN_FALSE);
        return;
    }
    if (Status != CResString::ex().getStrTblText(AETXT_ORDSTAT_FAKTURENDE))
    {
        MsgBoxOK(IDP_AE_NICHT_ZUL);
        return;
    }
    CDTourEtAend dlgTourEtAend;
    dlgTourEtAend.m_iAendArt = AenderungsArt;
    dlgTourEtAend.m_CTour = m_Tour;
    dlgTourEtAend.m_CAuftrNr = m_ListCtl.GetItemText(pos, 2);
    dlgTourEtAend.m_CKndOrt = m_ListCtl.GetItemText(pos, 5);
    dlgTourEtAend.m_CKndName = m_ListCtl.GetItemText(pos, 4);
    if (dlgTourEtAend.DoModal() == IDOK)
        Ausgabe();
}

void CDTourBearb::OnButtonFolge()
{
    Aenderung(ETAA_TOURFOLGE);
}

void CDTourBearb::OnButtonSowanne()
{
    Aenderung(ETAA_SONDERWANNE);
}

void CDTourBearb::OnButtonTour()
{
    Aenderung(ETAA_TOUR);
}

void CDTourBearb::OnButtonPrint()
{
    CDruckAuftrag druckAuftrag;
    CString liste;
    CString CStr;
    char underline[111];
    int maxpos, pos;
    memset(underline, '-', 110);
    underline[110] = '\0';
    liste = CResString::ex().getStrTblText(AETXT_TOUR);
    GetDlgItem(IDC_STATIC_TOURID)->GetWindowText(CStr);
    liste = liste + ':' + CStr + ' ' + CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
    GetDlgItem(IDC_STATIC_BEZEICHNUNG)->GetWindowText(CStr);
    liste = liste + ':' + CStr + ' ' + CResString::ex().getStrTblText(AETXT_KURZ_KILOMETER);
    GetDlgItem(IDC_STATIC_KM)->GetWindowText(CStr);
    liste = liste + ':' + CStr + ' ' + CResString::ex().getStrTblText(AETXT_FAHRZEIT);
    GetDlgItem(IDC_STATIC_FAHRZEIT)->GetWindowText(CStr);
    liste = liste + ':' + CStr + ' ' + CResString::ex().getStrTblText(AETXT_ORDSTAT_ERFASST);
    GetDlgItem(IDC_STATIC_ERFASST)->GetWindowText(CStr);
    liste = liste + ':' + CStr + ' ' + CResString::ex().getStrTblText(AETXT_ORDSTAT_FAKTURENDE);
    GetDlgItem(IDC_STATIC_FAKTURIERT)->GetWindowText(CStr);
    liste = liste + ':' + CStr;
    druckAuftrag.AddKopfZeile(liste);
    liste = ' ';
    druckAuftrag.AddKopfZeile(liste);
    liste.Format("%-3.3s %-4.4s %-2.2s %-35.35s %-25.25s %-4.4s %-4.4s %-2.2s %-2.2s %-2.2s %-2.2s %-2.2s",
        CResString::ex().getStrTblText(AETXT_KURZ_FOLGE).GetString(),
        CResString::ex().getStrTblText(AETXT_KURZ_AUFTR_NR).GetString(),
        CResString::ex().getStrTblText(AETXT_KZ_AUFTRAGSART).GetString(),
        CResString::ex().getStrTblText(AETXT_APOTHEKENNAME).GetString(),
        CResString::ex().getStrTblText(AETXT_ORT).GetString(),
        CResString::ex().getStrTblText(AETXT_KURZWAHL).GetString(),
        CResString::ex().getStrTblText(AETXT_KZ_URSPR_BAHNHOF).GetString(),
        CResString::ex().getStrTblText(AETXT_KZ_ANZ_WANNEN).GetString(),
        CResString::ex().getStrTblText(AETXT_ANZ_ZUS_WANNEN).GetString(),
        CResString::ex().getStrTblText(AETXT_ANZ_SONDERWANNEN).GetString(),
        CResString::ex().getStrTblText(AETXT_ANZ_BEIPACKS).GetString(),
        CResString::ex().getStrTblText(AETXT_ST).GetString() );
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(underline);
    liste = CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d";
    druckAuftrag.AddFussZeile (liste);

    maxpos = m_ListCtl.GetItemCount();
    for (pos = 0; pos < maxpos; pos++)
    {
        liste.Format("%-3.3s %-4.4s %-2.2s %-35.35s %-25.25s %-4.4s %-4.4s %-2.2s %-2.2s %-2.2s %-2.2s %-2.2s",
            m_ListCtl.GetItemText(pos, 1).GetString(),
            m_ListCtl.GetItemText(pos, 2).GetString(),
            m_ListCtl.GetItemText(pos, 3).GetString(),
            m_ListCtl.GetItemText(pos, 4).GetString(),
            m_ListCtl.GetItemText(pos, 5).GetString(),
            m_ListCtl.GetItemText(pos, 6).GetString(),
            m_ListCtl.GetItemText(pos, 7).GetString(),
            m_ListCtl.GetItemText(pos, 8).GetString(),
            m_ListCtl.GetItemText(pos, 10).GetString(),
            m_ListCtl.GetItemText(pos, 11).GetString(),
            m_ListCtl.GetItemText(pos, 12).GetString(),
            m_ListCtl.GetItemText(pos, 14).GetString());
        druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(0);
    druckAuftrag.DelAllData();
}
