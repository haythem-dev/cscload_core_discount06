// DRrUnlock.cpp : implementation file
//

#include "stdafx.h"
#include <callback.h>
#include "DRrUnlock.h"

#define ZEILEN 12    /* *** Anzahl der Zeilen der Listbox *** */

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     8

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  " ",  0, LVCFMT_CENTER, //Beschwerdenummer verstecken (DB-Schlüssel)
    2,  "",  60, LVCFMT_CENTER,
    3,  "",  60, LVCFMT_CENTER,
    4,  "", 140, LVCFMT_LEFT,
    5,  "",  80, LVCFMT_LEFT,
    6,  "",  80, LVCFMT_LEFT,
    7,  "", 190, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDRrUnlock dialog


CDRrUnlock::CDRrUnlock(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDRrUnlock::IDD, pParent), CPageBrowser(ZEILEN)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[3].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_RRPARTNER);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
}

void CDRrUnlock::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}

BEGIN_MESSAGE_MAP(CDRrUnlock, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_BUTTON_UNLOCK, OnButtonUnlock)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDRrUnlock message handlers

BOOL CDRrUnlock::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    GetPage();

    return TRUE;  // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDRrUnlock::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    long fetch_rel;
    char error_msg[81];
    ppString hilfe;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    fetch_rel = 1;

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, fetch_rel))
    {
        return FALSE;
    }

    m_ListCtl.DeleteAllItems();
    if (AeGetApp()->IsNewCallback())
    {
        m_todonew.SetRegionnr(AeGetApp()->VzNr());
        m_todonew.SetVertriebszentrumnr(AeGetApp()->VzNr());
        CLetterMan kb;
        BeginWaitCursor();
        for (int i = 0; i < ZEILEN; i++)
        {
            if (AeGetApp()->IsKundeHome())
                m_todonew.SelAllLockedVz(fetch_rel);
            else
                m_todonew.SelAllLocked(fetch_rel);
            m_bCursorOpen = true;       //Datenbankcurser offen
            fetch_rel = 1;              //normaler Fetch
            if (m_todonew.rc == SRV_SQLNOTFOUND)
            {
                if (m_bFirstDataset)  //kein Satz gefunden
                {
                    CloseCursor();
                    EndWaitCursor();
                    return false;
                }
                SetItemCountOfCurrentPage(i); //Anzahl Positionen letzte Seite
                break;
            }
            m_bFirstDataset = false;
            //Ausgabe in die Listbox
            s[0] = kb.Next();
            s[1].Format("%d", m_todonew.GetCallbackno());
            s[2] = AllgDatumLong2CharTTMMJJ(m_todonew.GetCallbackdatewished(), error_msg);
            s[3] = AllgZeit2CharHHMM(m_todonew.GetCallbacktimewished() * 100);
            s[4] = m_todonew.GetNameapo(hilfe);
            s[5] = m_todonew.GetOrt(hilfe);
            s[6] = m_todonew.GetDivisionname(hilfe);
            s[7] = m_todonew.GetKritiktext(hilfe);

            if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
            {
                EndWaitCursor();
                return false;
            }
        } //Ende der for()-Schleife
    }
    else
    {
        m_todo.SetRegionnr(AeGetApp()->VzNr());
        m_todo.SetVertriebszentrumnr(AeGetApp()->VzNr());
        CLetterMan kb;
        BeginWaitCursor();
        for (int i = 0; i < ZEILEN; i++)
        {
            if (AeGetApp()->IsKundeHome())
                m_todo.SelAllLockedVz(fetch_rel);
            else
                m_todo.SelAllLocked(fetch_rel);
            m_bCursorOpen = true;       //Datenbankcurser offen
            fetch_rel = 1;              //normaler Fetch
            if (m_todo.rc == SRV_SQLNOTFOUND)
            {
                if (m_bFirstDataset)      //kein Satz gefunden
                {
                    CloseCursor();
                    EndWaitCursor();
                    return false;
                }
                SetItemCountOfCurrentPage(i); //Anzahl Positionen letzte Seite
                break;
            }
            m_bFirstDataset = false;
            //Ausgabe in die Listbox
            s[0] = kb.Next();
            s[1].Format("%d", m_todo.GetCallbackno());
            s[2] = AllgDatumLong2CharTTMMJJ(m_todo.GetCallbackdatewished(), error_msg);
            s[3] = AllgZeit2CharHHMM(m_todo.GetCallbacktimewished() * 100);
            s[4] = m_todo.GetNameapo(hilfe);
            s[5] = m_todo.GetOrt(hilfe);
            s[6] = m_todo.GetCallbackpartner(hilfe);
            s[7] = m_todo.GetKritiktext(hilfe);

            if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
            {
                EndWaitCursor();
                return false;
            }
        } //Ende der for()-Schleife
    }
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return true;
}

void CDRrUnlock::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDRrUnlock::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    BeginWaitCursor();
    if (AeGetApp()->IsKundeHome())
    {
        if (AeGetApp()->IsNewCallback())
        {
            m_todonew.SelAllLockedVz(0);    //CloseCursor
        }
        else
        {
            m_todonew.SelAllLockedVz(0);    //CloseCursor
        }
    }
    else
    {
        if (AeGetApp()->IsNewCallback())
        {
            m_todo.SelAllLocked(0);     //CloseCursor
        }
        else
        {
            m_todo.SelAllLockedVz(0);   //CloseCursor
        }
    }
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDRrUnlock::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_RR_UNLOCK) == IDYES)
        {
            m_item.SetCallbackno(atol(m_ListCtl.GetItemText(pos, 1)));
            m_item.SelNo();
            m_item.SetLockkz('0');
            m_item.UpdateItem();
            CloseCursor();
            GetPage();
        }
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDRrUnlock::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDRrUnlock::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDRrUnlock::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}

void CDRrUnlock::OnButtonUnlock()
{
    SelectEintrag();
}
