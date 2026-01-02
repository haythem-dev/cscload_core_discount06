// DCallbackFetch.cpp : implementation file
//

#include "stdafx.h"
#include <kritiksatz.h>
#include <callback.h>
#include "DCallbackFetch.h"
#include "DCallbackUpd.h"

#define ZEILEN 12    /* *** Anzahl der Zeilen der Listbox *** */

#define NUM_CB_KB          0
#define NUM_CB_KRITIKNR    1
#define NUM_CB_ANZSHIFT    2
#define NUM_CB_DATUM       3
#define NUM_CB_TIME        4
#define NUM_CB_APO         5
#define NUM_CB_ORT         6
#define NUM_CB_PARTNER     7
#define NUM_CB_TITEL       8
#define NUM_CB_BEZEICHNUNG 9
#define NUM_CB_REFERENCE   10
#define NUM_CB_KDNR        11
#define NUM_CB_POSNR       12
#define NUM_CB_KDKLASSE    13
#define NUM_CB_VZNR        14
#define NUM_CB_STATUS      15
#define NUM_CB_COLUMNS     16


static COLUMNS_TYPES Columns[] =
{
    NUM_CB_KB,          "",   30, LVCFMT_LEFT,
    NUM_CB_KRITIKNR,    " ",   0, LVCFMT_CENTER, //Beschwerdenummer verstecken (DB-Schlüssel)
    NUM_CB_ANZSHIFT,    "",   30, LVCFMT_CENTER,
    NUM_CB_DATUM,       "",   60, LVCFMT_CENTER,
    NUM_CB_TIME,        "",   50, LVCFMT_CENTER,
    NUM_CB_APO,         "",  140, LVCFMT_LEFT,
    NUM_CB_ORT,         "",   80, LVCFMT_LEFT,
    NUM_CB_PARTNER,     "",   80, LVCFMT_LEFT,
    NUM_CB_TITEL,       " ", 120, LVCFMT_LEFT,
    NUM_CB_BEZEICHNUNG, "",    0, LVCFMT_LEFT,
    NUM_CB_REFERENCE  , "",  192, LVCFMT_LEFT,
    NUM_CB_KDNR,        " ",   0, LVCFMT_CENTER, //Kundennummer verstecken (DB-Schlüssel)
    NUM_CB_POSNR,       " ",   0, LVCFMT_CENTER, //Posnr verstecken (DB-Schlüssel)
    NUM_CB_KDKLASSE,    "",   74, LVCFMT_LEFT,
    NUM_CB_VZNR,        " ",   0, LVCFMT_CENTER, //Vz-Nr verstecken (für Folge-Modul)
    NUM_CB_STATUS,      "",   70, LVCFMT_LEFT,
    -1,                 "",    0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDCallbackFetch dialog


CDCallbackFetch::CDCallbackFetch(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCallbackFetch::IDD, pParent), CPageBrowser(ZEILEN)
{
    Columns[NUM_CB_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[NUM_CB_ANZSHIFT].Columns = CResString::ex().getStrTblText(AETXT_KZ_ANZ_SHIFT);
    Columns[NUM_CB_DATUM].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[NUM_CB_TIME].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[NUM_CB_APO].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    Columns[NUM_CB_ORT].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[NUM_CB_PARTNER].Columns = CResString::ex().getStrTblText(AETXT_RRPARTNER);
    Columns[NUM_CB_TITEL].Columns = CResString::ex().getStrTblText(AETXT_RUECKRUFGRUND);
    Columns[NUM_CB_KDKLASSE].Columns = CResString::ex().getStrTblText(AETXT_KDKLASSE);

    if (AeGetApp()->IsCBStatusUsed())
    {
        Columns[NUM_CB_REFERENCE].Columns = CResString::ex().getStrTblText(AETXT_REFERENCE);
        Columns[NUM_CB_STATUS].Columns = CResString::ex().getStrTblText(AETXT_STATUS_LANG);
    }
    else
    {
        Columns[NUM_CB_REFERENCE].Width = 0;
        Columns[NUM_CB_STATUS].Width = 0;
        Columns[NUM_CB_APO].Width = 240;
        Columns[NUM_CB_PARTNER].Width = 150;
        Columns[NUM_CB_TITEL].Width = 212;
    }
}

void CDCallbackFetch::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST2, m_ListCtl2);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Control(pDX, IDC_COMBO_STATUS, m_ComboStatus);
    DDX_Control(pDX, IDC_COMBO_DIVISION, m_ComboDivision);
    DDX_Control(pDX, IDC_COMBO_REASON, m_ComboReason);
}

BEGIN_MESSAGE_MAP(CDCallbackFetch, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_BN_CLICKED(IDC_BUTTON_SELECT, OnSelect)
    ON_CBN_SELCHANGE(IDC_COMBO_DIVISION, OnCbnSelchangeComboDivision)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCallbackFetch message handlers

BOOL CDCallbackFetch::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_WEISS);
    idResources.push_back(IDI_ICON_LOW_CRITICAL);
    idResources.push_back(IDI_ICON_WARN);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    // Init comboboxes
    if (AeGetApp()->IsCBStatusUsed())
    {
        m_ComboStatus.AddString(_T("")); // don't filter status in this case
        m_CallbackStatusManager.FillCombobox(m_ComboStatus);
        m_ComboStatus.SetCurSel(0);
    }
    else
    {
        GetDlgItem(IDC_STATIC_STATUS)->ShowWindow(SW_HIDE);
        m_ComboStatus.ShowWindow(SW_HIDE);
    }
    InitComboboxDivisison();
    m_ComboReason.AddString(_T(""));
    m_ComboReason.SetCurSel(0);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl)
        || !CListCtrlHelper::AddColumns(Columns, m_ListCtl2))
    {
        return FALSE;
    }
    GetWished();    // List-Box für von Kunden gewünschten Terminen mit Eintraegen versorgen
    GetPage();

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDCallbackFetch::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    long fetch_rel;
    char error_msg[81];
    CStringArray s;
    ppString hilfe;
    s.SetSize(NUM_CB_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        if (AeGetApp()->IsNewCallback())
        {
            m_todonew.SetUid(GetAeUser().GetUID());
            m_todonew.SetFilialnr(AeGetApp()->VzNr());
            m_todonew.SetVertriebszentrumnr(AeGetApp()->VzNr());
            m_todonew.SetRegionnr(AeGetApp()->VzNr());
        }
        else
        {
            m_todo.SetUid(GetAeUser().GetUID());
            m_todo.SetFilialnr(AeGetApp()->VzNr());
            m_todo.SetVertriebszentrumnr(AeGetApp()->VzNr());
            m_todo.SetRegionnr(AeGetApp()->VzNr());
        }
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, fetch_rel))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    int listtype;
    CLetterMan kb;
    BeginWaitCursor();
    int i = 0;
    while(i < ZEILEN)
    {
        if (AeGetApp()->IsNewCallback())
        {
            if (AeGetApp()->IsKundeHome())
                m_todonew.SelCallbackOpenVz(fetch_rel);
            else
                m_todonew.SelCallbackOpen(fetch_rel);
            m_bCursorOpen = true;       //Datenbankcurser offen
            fetch_rel = 1;              //normaler Fetch
            if (m_todonew.rc == SRV_SQLNOTFOUND)
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
            s[NUM_CB_KB] = kb.Next();
            s[NUM_CB_KRITIKNR].Format("%d", m_todonew.GetKritiknr());
            s[NUM_CB_ANZSHIFT].Format("%d", m_todonew.GetShiftcount());
            s[NUM_CB_DATUM] = AllgDatumLong2CharTTMMJJ(m_todonew.GetCallbackdatewished(), error_msg);
            s[NUM_CB_TIME] = AllgZeit2CharHHMM(m_todonew.GetCallbacktimewished() * 100);
            s[NUM_CB_APO] = m_todonew.GetNameapo(hilfe);
            s[NUM_CB_ORT] = m_todonew.GetOrt(hilfe);
            s[NUM_CB_PARTNER] = m_todonew.GetDivisionname(hilfe);
            s[NUM_CB_BEZEICHNUNG] = m_todonew.GetKritiktext(hilfe);
            s[NUM_CB_KDNR].Format("%d", m_todonew.GetIdfnr());
            s[NUM_CB_POSNR].Format("%d", m_todonew.GetCallbackno());
            s[NUM_CB_TITEL] = m_todonew.GetTitel(hilfe);
            s[NUM_CB_KDKLASSE] = m_todonew.GetKzkdklasse(hilfe);
            s[NUM_CB_VZNR].Format("%d", m_todonew.GetVertriebszentrumnr());
            if (AeGetApp()->IsCBStatusUsed())
            {
                s[NUM_CB_REFERENCE] = m_todonew.GetReference(hilfe);
                s[NUM_CB_STATUS] = m_todonew.GetStatus(hilfe);
            }
            listtype = m_todonew.GetKritiklevel();
        }
        else
        {
            if (AeGetApp()->IsKundeHome())
                m_todo.SelCallbackOpenVz(fetch_rel);
            else
                m_todo.SelCallbackOpen(fetch_rel);
            m_bCursorOpen = true;   //Datenbankcurser offen
            fetch_rel = 1;          //normaler Fetch
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
            s[NUM_CB_KB] = kb.Next();
            s[NUM_CB_KRITIKNR].Format("%d", m_todo.GetKritiknr());
            s[NUM_CB_ANZSHIFT].Format("%d", m_todo.GetShiftcount());
            s[NUM_CB_DATUM] = AllgDatumLong2CharTTMMJJ(m_todo.GetCallbackdatewished(), error_msg);
            s[NUM_CB_TIME] = AllgZeit2CharHHMM(m_todo.GetCallbacktimewished() * 100);
            s[NUM_CB_APO] = m_todo.GetNameapo(hilfe);
            s[NUM_CB_ORT] = m_todo.GetOrt(hilfe);
            s[NUM_CB_PARTNER] = m_todo.GetCallbackpartner(hilfe);
            s[NUM_CB_BEZEICHNUNG] = m_todo.GetKritiktext(hilfe);
            s[NUM_CB_KDNR].Format("%d", m_todo.GetIdfnr());
            s[NUM_CB_POSNR].Format("%d", m_todo.GetCallbackno());
            s[NUM_CB_TITEL] = m_todo.GetTitel(hilfe);
            s[NUM_CB_KDKLASSE] = m_todo.GetKzkdklasse(hilfe);
            s[NUM_CB_VZNR].Format("%d", m_todo.GetVertriebszentrumnr());
            if (AeGetApp()->IsCBStatusUsed())
            {
                s[NUM_CB_REFERENCE] = m_todo.GetReference(hilfe);
                s[NUM_CB_STATUS] = m_todo.GetStatus(hilfe);
            }
            listtype = 0;
        }

        CString strSelectedStatus;
        CString strSelectedDivision;
        CString strSelectedReason;

        if (AeGetApp()->IsCBStatusUsed())
        {
            m_ComboStatus.GetLBText(m_ComboStatus.GetCurSel(), strSelectedStatus);
        }
        m_ComboDivision.GetLBText(m_ComboDivision.GetCurSel(), strSelectedDivision);
        m_ComboReason.GetLBText(m_ComboReason.GetCurSel(), strSelectedReason);

        if ((strSelectedStatus.IsEmpty() || strSelectedStatus == s.ElementAt(NUM_CB_STATUS))
            && (strSelectedDivision.IsEmpty() || strSelectedDivision == s.ElementAt(NUM_CB_PARTNER))
            && (strSelectedReason.IsEmpty() || strSelectedReason == s.ElementAt(NUM_CB_TITEL)))
        {
            if (!CListCtrlHelper::AppendImageItem(m_ListCtl, NUM_CB_COLUMNS, s, listtype))
            {
                EndWaitCursor();
                return false;
            }
            i++;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return true;
}

void CDCallbackFetch::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDCallbackFetch::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    BeginWaitCursor();
    if (AeGetApp()->IsNewCallback())
    {
        m_todonew.SelCallbackOpen(0);   // CloseCursor
    }
    else
    {
        m_todo.SelCallbackOpen(0);  // CloseCursor
    }
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDCallbackFetch::InitComboboxDivisison()
{
    CCALLBACKDIVISION   servdivision;
    ppString            strDivisionName;

    BeginWaitCursor();
    servdivision.SetBranchno(AeGetApp()->VzNr());
    servdivision.SetCallbackstart(AeGetApp()->StartNoCallback());
    servdivision.SetCallbackend(AeGetApp()->StartNoCallback() + 100);

    m_ComboDivision.AddString(_T("")); // don't filter division in this case
    m_ComboDivision.SetItemData(0, 0);
    for (int i = 1;; i++)
    {
        if (servdivision.SelList() != SRV_OK)
            break;
        servdivision.GetDivisionname(strDivisionName);
        m_ComboDivision.AddString(strDivisionName);
        m_ComboDivision.SetItemData(i, servdivision.GetCallbackdivisionno());
    }
    m_ComboDivision.SetCurSel(0);
    EndWaitCursor();
}

void CDCallbackFetch::OnCbnSelchangeComboDivision()
{
    BeginWaitCursor();
    m_ComboReason.ResetContent();
    m_ComboReason.AddString(_T("")); // don't filter reason in this case

   // Get selected division and fill m_ComboReason with related reasons
    CCALLBACKREASONS servReason;
    ppString         strReasonName;
    short            selectedCallbackdivisionno = 0;
    int              selectedIndex = m_ComboDivision.GetCurSel();
    if (selectedIndex != CB_ERR && selectedIndex != 0)
    {
        selectedCallbackdivisionno = (short)m_ComboDivision.GetItemData(selectedIndex);
        servReason.SetCallbackdivisionno(selectedCallbackdivisionno);
        servReason.SetBranchno(AeGetApp()->VzNr());
        for (int i = 1;; i++)
        {
            if (servReason.SelList() != SRV_OK)
                break;
            servReason.GetCallbackreason(strReasonName);
            m_ComboReason.AddString(strReasonName);
            // m_ComboReason.SetItemData(i, servReason.GetReasonno());
        }
    }
    m_ComboReason.SetCurSel(0);
    EndWaitCursor();
}

void CDCallbackFetch::OnSelect()
{
    UpdateData();
    CloseCursor();
    GetPage();
}

void CDCallbackFetch::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        SelectEintrag();
        return;
    }
    UpdateData();
    CloseCursor();
    GetPage();
}

void CDCallbackFetch::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDCallbackUpd dlgCallbackUpd;
        dlgCallbackUpd.m_lKritiknr = atol(m_ListCtl.GetItemText(pos, NUM_CB_KRITIKNR));
        dlgCallbackUpd.m_lIdf = atol(m_ListCtl.GetItemText(pos, NUM_CB_KDNR));
        dlgCallbackUpd.m_lRRNr = atol(m_ListCtl.GetItemText(pos, NUM_CB_POSNR));
        dlgCallbackUpd.m_CGrund = m_ListCtl.GetItemText(pos, NUM_CB_BEZEICHNUNG);
        dlgCallbackUpd.m_Titel = m_ListCtl.GetItemText(pos, NUM_CB_TITEL);
        dlgCallbackUpd.m_sVzNr = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, NUM_CB_VZNR)));
        if (dlgCallbackUpd.DoModal() == IDOK)
        {
            CloseCursor();
            if (dlgCallbackUpd.m_bAuftr)
                CDialogMultiLang::OnOK();
            GetPage();
        }
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDCallbackFetch::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDCallbackFetch::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDCallbackFetch::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}


BOOL CDCallbackFetch::GetWished()
{
    //Variablen
    char error_msg[81];
    CStringArray s;
    ppString hilfe;
    s.SetSize(NUM_CB_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    if (AeGetApp()->IsNewCallback())
    {
        m_todonew.SetUid(GetAeUser().GetUID());
        m_todonew.SetFilialnr(AeGetApp()->VzNr());
        m_todonew.SetVertriebszentrumnr(AeGetApp()->VzNr());
        m_todonew.SetRegionnr(AeGetApp()->VzNr());
        m_ListCtl2.DeleteAllItems();
        CLetterMan kb;
        BeginWaitCursor();
        for (int i = 0; ; i++)
        {
            if (AeGetApp()->IsKundeHome())
                m_todonew.SelCallbackWishedVz(1);
            else
                m_todonew.SelCallbackWished(1);
            if (m_todonew.rc == SRV_SQLNOTFOUND)
            {
                break;
            }
            //Ausgabe in die Listbox
            s[NUM_CB_KB] = kb.Next();
            s[NUM_CB_KRITIKNR].Format("%d", m_todonew.GetKritiknr());
            s[NUM_CB_ANZSHIFT].Format("%d", m_todonew.GetShiftcount());
            s[NUM_CB_DATUM] = AllgDatumLong2CharTTMMJJ(m_todonew.GetCallbackdatewished(), error_msg);
            s[NUM_CB_TIME] = AllgZeit2CharHHMM(m_todonew.GetCallbacktimewished() * 100);
            s[NUM_CB_APO] = m_todonew.GetNameapo(hilfe);
            s[NUM_CB_ORT] = m_todonew.GetOrt(hilfe);
            s[NUM_CB_PARTNER] = m_todonew.GetDivisionname(hilfe);
            s[NUM_CB_BEZEICHNUNG] = m_todonew.GetKritiktext(hilfe);
            s[NUM_CB_REFERENCE] = m_todonew.GetReference(hilfe);
            s[NUM_CB_KDNR].Format("%d", m_todonew.GetIdfnr());
            s[NUM_CB_POSNR].Format("%d", m_todonew.GetCallbackno());
            s[NUM_CB_TITEL] = m_todonew.GetTitel(hilfe);
            s[NUM_CB_KDKLASSE] = m_todonew.GetKzkdklasse(hilfe);
            s[NUM_CB_VZNR].Format("%d", m_todonew.GetVertriebszentrumnr());

            if (!CListCtrlHelper::AppendItem(m_ListCtl2, NUM_CB_COLUMNS, s))
            {
                EndWaitCursor();
                return FALSE;
            }
        } //Ende der for()-Schleife
        m_todonew.SelCallbackFuture(0);
    }
    else
    {
        m_todo.SetUid(GetAeUser().GetUID());
        m_todo.SetFilialnr(AeGetApp()->VzNr());
        m_todo.SetVertriebszentrumnr(AeGetApp()->VzNr());
        m_todo.SetRegionnr(AeGetApp()->VzNr());
        m_ListCtl2.DeleteAllItems();
        CLetterMan kb;
        BeginWaitCursor();
        for (int i = 0; ; i++)
        {
            if (AeGetApp()->IsKundeHome())
                m_todo.SelCallbackWishedVz(1);
            else
                m_todo.SelCallbackWished(1);
            if (m_todo.rc == SRV_SQLNOTFOUND)
            {
                break;
            }
            //Ausgabe in die Listbox
            s[NUM_CB_KB] = kb.Next();
            s[NUM_CB_KRITIKNR].Format("%d", m_todo.GetKritiknr());
            s[NUM_CB_ANZSHIFT].Format("%d", m_todo.GetShiftcount());
            s[NUM_CB_DATUM] = AllgDatumLong2CharTTMMJJ(m_todo.GetCallbackdatewished(), error_msg);
            s[NUM_CB_TIME] = AllgZeit2CharHHMM(m_todo.GetCallbacktimewished() * 100);
            s[NUM_CB_APO] = m_todo.GetNameapo(hilfe);
            s[NUM_CB_ORT] = m_todo.GetOrt(hilfe);
            s[NUM_CB_PARTNER] = m_todo.GetCallbackpartner(hilfe);
            s[NUM_CB_BEZEICHNUNG] = m_todo.GetKritiktext(hilfe);
            s[NUM_CB_REFERENCE] = m_todo.GetReference(hilfe);
            s[NUM_CB_KDNR].Format("%d", m_todo.GetIdfnr());
            s[NUM_CB_POSNR].Format("%d", m_todo.GetCallbackno());
            s[NUM_CB_TITEL] = m_todo.GetTitel(hilfe);
            s[NUM_CB_KDKLASSE] = m_todo.GetKzkdklasse(hilfe);
            s[NUM_CB_VZNR].Format("%d", m_todo.GetVertriebszentrumnr());

            if (!CListCtrlHelper::AppendItem(m_ListCtl2, NUM_CB_COLUMNS, s))
            {
                EndWaitCursor();
                return FALSE;
            }
        } //Ende der for()-Schleife
        m_todo.SelCallbackFuture(0);
    }
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST2));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return TRUE;
}
