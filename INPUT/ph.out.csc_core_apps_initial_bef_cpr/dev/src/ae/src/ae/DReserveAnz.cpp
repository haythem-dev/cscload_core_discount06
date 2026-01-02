// DReserveAnz.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DArtInf.h"
#include <artikel.h>
#include "DDruckAuftrag.h"
#include "DReserveAnz.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 60, LVCFMT_RIGHT,
    2,  "", 60, LVCFMT_RIGHT,
    3,  "", 70, LVCFMT_RIGHT,
    4,  "", 60, LVCFMT_RIGHT,
    5,  "", 60, LVCFMT_RIGHT,
    -1, "",  0, 0
};

// CDReserveAnz-Dialogfeld

IMPLEMENT_DYNAMIC(CDReserveAnz, CDialog)
CDReserveAnz::CDReserveAnz(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDReserveAnz::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BEST);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_EK_GRP);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_BESTAND_RESERVIERT);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_PROZENT);
}

CDReserveAnz::~CDReserveAnz()
{
}

void CDReserveAnz::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDReserveAnz, CDialogMultiLang)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnBnClickedButtonDruck)
END_MESSAGE_MAP()


// CDReserveAnz-Meldungshandler

BOOL CDReserveAnz::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    CARTIKELRESERVE artikelreserve;
    CStringArray s;
    ppString EKGR;
    s.SetSize(NUM_COLUMNS);
    artikelreserve.SetBranchno(AeGetApp()->VzNr());
    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (artikelreserve.SelListBestand() != SRV_OK) break;
        s[0] = kb.Next();
        s[1].Format("%ld", artikelreserve.GetArticleno());
        s[2].Format("%ld", artikelreserve.GetMaxqty());
        s[3] = artikelreserve.GetPharmacygroupid(EKGR);
        s[4].Format("%ld", artikelreserve.GetReservedqty());
        s[5].Format("%d", artikelreserve.GetReservepct());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return TRUE;
        }
    }
    artikelreserve.CloseCursor();
    EndWaitCursor();
    if (m_ListCtl.GetItemCount() == 0)
        MsgBoxOK(IDP_NO_DATA);
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return FALSE;  // return TRUE unless you set the focus to a control
                   // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

LRESULT CDReserveAnz::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F11)
    {
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString CStr;
            CStr  = m_ListCtl.GetItemText(pos, 1);
            long ArtNr = atol (CStr);
            CDArtInf dlgArtInf;
            dlgArtInf.SetArtNr(ArtNr);
            dlgArtInf.SetFilialNr(AeGetApp()->VzNr());
            dlgArtInf.DoModal();
        }
        return 1L;
    }
    return 0L;
}

void CDReserveAnz::OnBnClickedButtonDruck()
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
    liste.Format(CResString::ex().getStrTblText(IDS_RESERVE_LIST), Datum);
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);
    liste.Format("%-7.7s %-7.7s %6.6s %-10.10s %-7.7s",
                CResString::ex().getStrTblText(AETXT_PZN).GetString(),
                CResString::ex().getStrTblText(AETXT_BEST).GetString(),
                CResString::ex().getStrTblText(AETXT_EK_GRP).GetString(),
                CResString::ex().getStrTblText(AETXT_BESTAND_RESERVIERT).GetString(),
                CResString::ex().getStrTblText(AETXT_PROZENT).GetString() );
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
    liste.Format("% 7.7s % 7.7s % 6.6s % 10.10s % 7.7s",
            m_ListCtl.GetItemText(pos, 1).GetString(),
            m_ListCtl.GetItemText(pos, 2).GetString(),
            m_ListCtl.GetItemText(pos, 3).GetString(),
            m_ListCtl.GetItemText(pos, 4).GetString(),
            m_ListCtl.GetItemText(pos, 5).GetString() );
    druckAuftrag.AddPosZeile(liste);
    }
    druckAuftrag.Druck(0);
    druckAuftrag.DelAllData();
}
