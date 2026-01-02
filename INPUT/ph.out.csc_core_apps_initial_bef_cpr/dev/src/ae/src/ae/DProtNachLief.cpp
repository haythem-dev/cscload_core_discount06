// DProtNachLief.cpp : implementation file
//

#include "stdafx.h"
#include "DProtNachLief.h"
#include "DKndWahl.h"
#include "DArtDef.h"
#include "nachlprot.h"

#define AENDTYP_DELETE 1
#define AENDTYP_MENGENAENDERUNG 2
#define AENDTYP_LIEFERMOEGLICHKEIT 3
#define AENDTYP_FOLGE 4

#define ZEILEN 14    /* *** Anzahl der Zeilen der Listbox *** */

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     12

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 60, LVCFMT_RIGHT,
    2,  "", 60, LVCFMT_RIGHT,
    3,  "", 60, LVCFMT_RIGHT,
    4,  "", 60, LVCFMT_RIGHT,
    5,  "", 50, LVCFMT_RIGHT,
    6,  "", 60, LVCFMT_RIGHT,
    7,  "", 60, LVCFMT_RIGHT,
    8,  "", 60, LVCFMT_RIGHT,
    9,  "", 60, LVCFMT_RIGHT,
    10, "", 60, LVCFMT_RIGHT,
    11, "", 60, LVCFMT_RIGHT,
    -1, "",  0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDProtNachLief dialog


CDProtNachLief::CDProtNachLief(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDProtNachLief::IDD, pParent), CPageBrowser(ZEILEN)
{
    m_CIdfNr = _T("");
    m_CArtNr = _T("");

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_DATUM_ALT);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_AUFTRNR_ALT);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_AENDERUNGSART);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_DATUM_NEU);
    Columns[5].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_AUFTRNR_NEU);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_MENGE_ALT_KZ);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_MENGE_NEU);
    Columns[9].Columns = CResString::ex().getStrTblText(AETXT_MENGE_GEL);
    Columns[10].Columns = CResString::ex().getStrTblText(AETXT_MENGE_OFFEN);
    Columns[11].Columns = CResString::ex().getStrTblText(IDS_ANWENDER);
}

void CDProtNachLief::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ART_NR, m_EditArtNr);
    DDX_Control(pDX, IDC_EDIT_IDF, m_EditIdfNr);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_IDF, m_CIdfNr);
    DDX_Text(pDX, IDC_EDIT_ART_NR, m_CArtNr);
}

BEGIN_MESSAGE_MAP(CDProtNachLief, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_BUTTON_ARTNR, OnButtonArtnr)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnButtonKnd)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDProtNachLief message handlers

BOOL CDProtNachLief::OnInitDialog()
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

bool CDProtNachLief::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    CNACHLPROTV nachlprotv;
    CARTAESEL code;
    char str[81];
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        UpdateData();
        nachlprotv.s.IDFNR = atol(m_CIdfNr);
        if (m_CArtNr.IsEmpty() || nachlprotv.s.IDFNR == 0)
        {
            MsgBoxOK(IDS_ITEM_AND_CUSTNR_REQ);
            return false;
        }
        BeginWaitCursor();
        strcpy(code.s.ARTICLE_CODE, m_CArtNr);
        code.Server(AatartSel_NoByCode);
        EndWaitCursor();
        nachlprotv.s.ARTIKEL_NR = code.s.ARTIKEL_NR;
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, nachlprotv.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        nachlprotv.Server(AaauftGet_prot_nl);
        m_bCursorOpen = true;       //Datenbankcurser offen
        nachlprotv.s.FETCH_REL = 1;          //normaler Fetch
        if (nachlprotv.rc == SRV_SQLNOTFOUND)
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
        ppGDateLongToCharTTMMJJ(nachlprotv.s.DATUM, str);
        s[1] = str;
        s[2].Format("%ld", nachlprotv.s.KDAUFTRAGNR);
        if (nachlprotv.s.AENDTYP == AENDTYP_DELETE)
            s[3] = CResString::ex().getStrTblText(AETXT_LOESC);
        else if (nachlprotv.s.AENDTYP == AENDTYP_MENGENAENDERUNG)
            s[3] = CResString::ex().getStrTblText(AETXT_AENDER);
        else if (nachlprotv.s.AENDTYP == AENDTYP_FOLGE)
            s[3] = CResString::ex().getStrTblText(AETXT_ART_UMGESCHL);
        else
            s[3] = CResString::ex().getStrTblText(AETXT_NACHLIEF);
        ppGDateLongToCharTTMMJJ(nachlprotv.s.DATUM_NEU, str);
        s[4] = str;
        ppGTimeLongToCharHHMM(nachlprotv.s.ZEIT_NEU, str);
        s[5] = str;
        s[6].Format("%ld", nachlprotv.s.KDAUFTRAG_NR_NEU);
        s[7].Format("%ld", nachlprotv.s.NL_MENGE_ALT);
        s[8].Format("%ld", nachlprotv.s.NL_MENGE_AKTUELL);
        s[9].Format("%ld", nachlprotv.s.NL_MENGE_GELIEFER);
        s[10].Format("%ld", nachlprotv.s.NL_MENGE_NEU);
        s[11] = nachlprotv.s.USERNAME;

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

void CDProtNachLief::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDProtNachLief::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CNACHLPROTV nachlprotv;
    nachlprotv.s.FETCH_REL = 0;
    BeginWaitCursor();
    nachlprotv.Server(AaauftGet_prot_nl);
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDProtNachLief::OnOK()
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

void CDProtNachLief::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
    /*  CNACHLPROTV nachlprotv;
        ***nachlprotv.m_Bespielfeld = m_ListCtl.GetItemText(pos, 1); ***
        nachlprotv.DoModal(); */
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDProtNachLief::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDProtNachLief::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDProtNachLief::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}

void CDProtNachLief::OnButtonArtnr()
{
    CDArtDef dlgArtDef;
    if (dlgArtDef.DoModal() != IDOK)
    {
        return;
    }
    CString CStr;
    CStr.Format("%ld", dlgArtDef.GetArtNr());
    GetDlgItem(IDC_EDIT_ART_NR)->SetWindowText(dlgArtDef.GetArticleCode());
}

void CDProtNachLief::OnButtonKnd()
{
    CDKndWahl dlgKndWahl;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    CString CStr;
    CStr.Format("%ld", dlgKndWahl.GetKndNr());
    GetDlgItem(IDC_EDIT_IDF)->SetWindowText(CStr);
}
