// DUpdTime.cpp : implementation file
//

#include "stdafx.h"
#include <callback.h>
#include "DUpdTime.h"
#include "DCallbackWork.h"

#define MAXIMUM_ANTWORTZEIT 120
#define ZEILEN 12    /* *** Anzahl der Zeilen der Listbox *** */

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     4

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 80, LVCFMT_LEFT,
    2,  "", 80, LVCFMT_LEFT,
    3,  "", 80, LVCFMT_LEFT,
    -1, "",  0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDUpdTime dialog


CDUpdTime::CDUpdTime(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDUpdTime::IDD, pParent), CPageBrowser(ZEILEN)
{
    m_CName = _T("");
    m_CTime = _T("");
    m_saDay.SetSize(7);
    m_saDay.SetAt(0, CResString::ex().getStrTblText(IDS_SUNDAY));
    m_saDay.SetAt(1, CResString::ex().getStrTblText(IDS_MONDAY));
    m_saDay.SetAt(2, CResString::ex().getStrTblText(IDS_TUESDAY));
    m_saDay.SetAt(3, CResString::ex().getStrTblText(IDS_WEDNESDAY));
    m_saDay.SetAt(4, CResString::ex().getStrTblText(IDS_THURSDAY));
    m_saDay.SetAt(5, CResString::ex().getStrTblText(IDS_FRIDAY));
    m_saDay.SetAt(6, CResString::ex().getStrTblText(IDS_SATURDAY));
    m_lPartnerNo = 0;
    m_sVzNr = 0;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TAG);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_BEGIN);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_ENDE);
}

void CDUpdTime::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_TIME, m_EditTime);
    DDX_Control(pDX, IDC_EDIT_NAME, m_EditName);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_NAME, m_CName);
    DDX_Text(pDX, IDC_EDIT_TIME, m_CTime);
}

BEGIN_MESSAGE_MAP(CDUpdTime, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_BUTTON_NEWTIME, OnButtonNewtime)
    ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
    ON_EN_CHANGE(IDC_EDIT_TIME, OnChangeEditTime)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDUpdTime message handlers

BOOL CDUpdTime::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    if (m_lPartnerNo != 0)
    {
        GetPage();
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDUpdTime::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    int Fetch_rel;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        m_Callbacktime.SetCallbackpartno(m_lPartnerNo);
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, Fetch_rel))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        m_Callbacktime.SelectCallbackPartner(Fetch_rel);
        m_bCursorOpen = true;       //Datenbankcurser offen
        Fetch_rel = 1;              //normaler Fetch
        if (m_Callbacktime.rc == SRV_SQLNOTFOUND)
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
        s[1] = m_saDay.GetAt(m_Callbacktime.GetOfficeday());
        s[2] = AllgZeit2CharHHMM((long)m_Callbacktime.GetBegintime());
        s[3] = AllgZeit2CharHHMM((long)m_Callbacktime.GetEndtime());

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

void CDUpdTime::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDUpdTime::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    BeginWaitCursor();
    m_Callbacktime.CloseCursor();
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDUpdTime::OnOK()
{
    UpdateData();
    if (m_lPartnerNo == 0)
    {
        CCALLBACKPARTNER partner;
        if (m_CName.IsEmpty())
        {
            MsgBoxOK(IDP_RR_EINGEBEN);
            GetDlgItem(IDC_EDIT_NAME)->SetFocus();
            return;
        }
        if (m_CTime.IsEmpty())
        {
            MsgBoxOK(IDP_RR_ZEIT_EINGEBEN);
            GetDlgItem(IDC_EDIT_TIME)->SetFocus();
            return;
        }
        partner.SetCallbackpartner(m_CName);
        partner.SetCallbacktime(static_cast<short>(atoi(m_CTime)));
        partner.SetVertriebszentrumnr( GetVzNr() );
        partner.InsertWithNewNo();
        m_lPartnerNo = partner.GetCallbackpartno();
    }
    else if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        SelectEintrag();
        return;
    }
    else
    {
        CCALLBACKPARTNER partner;
        if (m_CName.IsEmpty())
        {
            MsgBoxOK(IDP_RR_EINGEBEN);
            GetDlgItem(IDC_EDIT_NAME)->SetFocus();
            return;
        }
        if (m_CTime.IsEmpty())
        {
            MsgBoxOK(IDP_RR_ZEIT_EINGEBEN);
            GetDlgItem(IDC_EDIT_TIME)->SetFocus();
            return;
        }
        partner.SetCallbackpartner(m_CName);
        partner.SetCallbacktime(static_cast<short>(atoi(m_CTime)));
        partner.SetCallbackpartno(m_lPartnerNo);
        partner.SetVertriebszentrumnr( GetVzNr() );
        partner.Update();
    }
    CloseCursor();
    GetPage();
}

void CDUpdTime::SelectEintrag()
{
    CString str;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDCallbackWork dlgCallbackWork;
        dlgCallbackWork.m_Tag = m_ListCtl.GetItemText(pos, 1);
        str = m_ListCtl.GetItemText(pos, 2);
        for (int x = 0; x < str.GetLength(); x++)
        {
            if (str.GetAt(x) == ':')
                continue;
            else
                dlgCallbackWork.m_CVon += str.GetAt(x);
        }
        str = m_ListCtl.GetItemText(pos, 3);
        for (int x = 0; x < str.GetLength(); x++)
        {
            if (str.GetAt(x) == ':')
                continue;
            else
                dlgCallbackWork.m_CBis += str.GetAt(x);
        }
        dlgCallbackWork.m_lPartnerNo = m_lPartnerNo;
        dlgCallbackWork.m_lVon = static_cast<short>(atoi(dlgCallbackWork.m_CVon));
        dlgCallbackWork.m_CPartner = m_CName;
        dlgCallbackWork.m_new = FALSE;
        dlgCallbackWork.DoModal();
        CloseCursor();
        GetPage();
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDUpdTime::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDUpdTime::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDUpdTime::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}

void CDUpdTime::OnButtonNewtime()
{
    UpdateData();
    if (m_lPartnerNo == 0)
    {
        CCALLBACKPARTNER partner;
        if (m_CName.IsEmpty())
        {
            MsgBoxOK(IDP_RR_EINGEBEN);
            GetDlgItem(IDC_EDIT_NAME)->SetFocus();
            return;
        }
        if (m_CName.IsEmpty())
        {
            MsgBoxOK(IDP_RR_ZEIT_EINGEBEN);
            GetDlgItem(IDC_EDIT_TIME)->SetFocus();
            return;
        }
        partner.SetCallbackpartner(m_CName);
        partner.SetCallbacktime(static_cast<short>(atoi(m_CTime)));
        partner.SetVertriebszentrumnr( GetVzNr() );
        partner.InsertWithNewNo();
        m_lPartnerNo = partner.GetCallbackpartno();
    }
    CDCallbackWork dlgCallbackWork;
    dlgCallbackWork.m_lPartnerNo = m_lPartnerNo;
    dlgCallbackWork.m_CPartner = m_CName;
    dlgCallbackWork.m_new = TRUE;
    dlgCallbackWork.DoModal();
    CloseCursor();
    GetPage();
}

void CDUpdTime::OnChangeEditName()
{
    AllgLaengeKontr(&m_EditName, L_CALLBACKPARTNER_CALLBACKPARTNER,AeGetApp()->Modus());
}

void CDUpdTime::OnChangeEditTime()
{
    AllgWertKontr(&m_EditTime, MAXIMUM_ANTWORTZEIT);
}
