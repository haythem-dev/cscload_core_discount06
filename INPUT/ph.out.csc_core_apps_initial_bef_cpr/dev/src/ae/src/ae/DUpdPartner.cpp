// DUpdPartner.cpp : implementation file
//

#include "stdafx.h"
#include <callback.h>
#include "DUpdPartner.h"
#include "DUpdTime.h"

#define ZEILEN 12    /* *** Anzahl der Zeilen der Listbox *** */

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     4

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "", 220, LVCFMT_LEFT,
    2,  "",  80, LVCFMT_LEFT,
    3,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDUpdPartner dialog


CDUpdPartner::CDUpdPartner(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDUpdPartner::IDD, pParent), CPageBrowser(ZEILEN)
{
    m_sVzNr = 0;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_RRPARTNER);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_RRZEIT);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
}

void CDUpdPartner::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}

BEGIN_MESSAGE_MAP(CDUpdPartner, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_NEW, OnButtonNew)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDUpdPartner message handlers

BOOL CDUpdPartner::OnInitDialog()
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

bool CDUpdPartner::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    int Fetch_rel;
    ppString Partner_name;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    m_Partner.SetVertriebszentrumnr(GetVzNr());

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, Fetch_rel))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        m_Partner.SelectAllVz(Fetch_rel);
        m_bCursorOpen = true;   //Datenbankcurser offen
        Fetch_rel = 1;          //normaler Fetch
        if (m_Partner.rc == SRV_SQLNOTFOUND)
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
        s[1] = m_Partner.GetCallbackpartner(Partner_name);
        s[2].Format("%d", m_Partner.GetCallbacktime());
        s[3].Format("%d", m_Partner.GetCallbackpartno());

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

void CDUpdPartner::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDUpdPartner::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    BeginWaitCursor();
    m_Partner.CloseCursor();
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDUpdPartner::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDUpdTime dlgUpdTime;
        dlgUpdTime.m_lPartnerNo = atol(m_ListCtl.GetItemText(pos, 3));
        dlgUpdTime.m_CName = m_ListCtl.GetItemText(pos, 1);
        dlgUpdTime.m_CTime = m_ListCtl.GetItemText(pos, 2);
        dlgUpdTime.SetVzNr(GetVzNr());
        dlgUpdTime.DoModal();
        CloseCursor();
        GetPage();
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDUpdPartner::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDUpdPartner::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDUpdPartner::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}

void CDUpdPartner::OnButtonChange()
{
    SelectEintrag();
}

void CDUpdPartner::OnButtonDelete()
{
    if (MsgBoxYesNo(IDP_SOLL_RR_DELETE) == IDNO)
        return;

    CCALLBACKTIME callbacktime;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_Partner.SetCallbackpartno(atol(m_ListCtl.GetItemText(pos, 3)));
        m_Partner.DeleteCallbackPartner();
        callbacktime.SetCallbackpartno(atol(m_ListCtl.GetItemText(pos, 3)));
        callbacktime.DeleteAllNo();
        CloseCursor();
        GetPage();
    }
}

void CDUpdPartner::OnButtonNew()
{
    CDUpdTime dlgUpdTime;
    dlgUpdTime.SetVzNr(GetVzNr());
    dlgUpdTime.DoModal();
    CloseCursor();
    GetPage();
}
