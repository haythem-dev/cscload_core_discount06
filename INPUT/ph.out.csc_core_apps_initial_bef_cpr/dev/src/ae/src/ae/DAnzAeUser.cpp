// DAnzAeUser.cpp : implementation file
//

#include "stdafx.h"
#include "DAnzAeUser.h"

#define ZEILEN 17    /* *** Anzahl der Zeilen der Listbox *** */

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     4

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 60, LVCFMT_LEFT,
    2,  "", 60, LVCFMT_RIGHT,
    3,  "", 80, LVCFMT_LEFT,
    -1, "",  0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDAnzAeUser dialog


CDAnzAeUser::CDAnzAeUser(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAnzAeUser::IDD, pParent), CPageBrowser(ZEILEN)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_TERMINAL);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_NUMMER);
    Columns[3].Columns = CResString::ex().getStrTblText(IDS_ANWENDER);
}

void CDAnzAeUser::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}

BEGIN_MESSAGE_MAP(CDAnzAeUser, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDAnzAeUser message handlers

BOOL CDAnzAeUser::OnInitDialog()
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

bool CDAnzAeUser::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    CAEPWD aepwd;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        aepwd.s.FILIALNR = m_FilialNr;
        AllgStrCopy(aepwd.s.AA, "1", L_AEPWD_AA);
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, aepwd.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        aepwd.Server(AafilSel_aa_passwd);
        m_bCursorOpen = true;       //Datenbankcurser offen
        aepwd.s.FETCH_REL = 1;          //normaler Fetch
        if (aepwd.rc == SRV_SQLNOTFOUND)
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
        AllgEntfSpaces(aepwd.s.TERMID);
        s[1] = aepwd.s.TERMID;
        s[2].Format("%d", aepwd.s.UID);
        AllgEntfSpaces(aepwd.s.USERNAME);
        s[3] = aepwd.s.USERNAME;

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

void CDAnzAeUser::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDAnzAeUser::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CAEPWD aepwd;
    aepwd.s.FETCH_REL = 0;
    BeginWaitCursor();
    aepwd.Server(AafilSel_aa_passwd);
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDAnzAeUser::OnOK()
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

void CDAnzAeUser::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        /*
        CAEPWD aepwd;
        ***aepwd.m_Bespielfeld = m_ListCtl.GetItemText(pos, 1); ***
        aepwd.DoModal();
        */
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDAnzAeUser::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDAnzAeUser::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDAnzAeUser::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}
