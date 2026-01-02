// DDistressRouting.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <customer.h>
#include <controlling.h>
#include <filialpartner.h>
#include "NMDProgress.h"
#include "DDistressRouting.h"

//Definitionen Richtung
#define PFEIL_DOWN  0;
#define PFEIL_UP    1;

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS1     7

static COLUMNS_TYPES Columns1[] =
{
    0,  "",  55, LVCFMT_RIGHT,
    1,  "",  27, LVCFMT_RIGHT,
    2,  "", 140, LVCFMT_LEFT,
    3,  "", 140, LVCFMT_LEFT,
    4,  "",   0, LVCFMT_RIGHT,
    5,  "",  32, LVCFMT_LEFT,
    6,  "",  47, LVCFMT_LEFT,
    -1, "",   0, 0
};


#define NUM_COLUMNS2     7

static COLUMNS_TYPES Columns2[] =
{
    0,  "",  55, LVCFMT_RIGHT,
    1,  "",  27, LVCFMT_RIGHT,
    2,  "", 140, LVCFMT_LEFT,
    3,  "", 140, LVCFMT_LEFT,
    4,  "",  27, LVCFMT_RIGHT,
    5,  "",  32, LVCFMT_LEFT,
    6,  "",  47, LVCFMT_LEFT,
    -1, "",   0, 0
};

// CDDistressRouting-Dialogfeld

IMPLEMENT_DYNAMIC(CDDistressRouting, CDialog)
CDDistressRouting::CDDistressRouting(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDDistressRouting::IDD, pParent)
{
    Columns1[0].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns1[1].Columns = CResString::ex().getStrTblText(AETXT_VB);
    Columns1[2].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns1[3].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns1[4].Columns = CResString::ex().getStrTblText(AETXT_VZ);
    Columns1[5].Columns = CResString::ex().getStrTblText(AETXT_ABC);
    Columns1[6].Columns = CResString::ex().getStrTblText(AETXT_PLZ);

    Columns2[0].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns2[1].Columns = CResString::ex().getStrTblText(AETXT_VB);
    Columns2[2].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns2[3].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns2[4].Columns = CResString::ex().getStrTblText(AETXT_VZ);
    Columns2[5].Columns = CResString::ex().getStrTblText(AETXT_ABC);
    Columns2[6].Columns = CResString::ex().getStrTblText(AETXT_PLZ);
    m_iOrder1 = 0;
    m_iCol1 = -1;
    m_iOrder2 = 0;
    m_iCol2 = -1;
}

CDDistressRouting::~CDDistressRouting()
{
}

void CDDistressRouting::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl1);
    DDX_Control(pDX, IDC_LIST2, m_ListCtl2);
    DDX_Control(pDX, IDC_COMBO_DEST_BRANCH, m_combo_DestBranch);
}


BEGIN_MESSAGE_MAP(CDDistressRouting, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
    ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnBnClickedButtonRemove)
    ON_CBN_SELCHANGE(IDC_COMBO_DEST_BRANCH, OnCbnSelchangeComboDestBranch)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnLvnColumnclickList1)
    ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST2, OnLvnColumnclickList2)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST2, OnNMDblclkList2)
END_MESSAGE_MAP()


// CDDistressRouting-Meldungshandler

BOOL CDDistressRouting::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    CCHECKDISTRESS distress;
    distress.SetFilialnr(AeGetApp()->VzNr());
    if (!distress.IsInWork())
    {
        MsgBoxOK(AETXT_DISTRESS_IN_WORD);
        CDialogMultiLang::OnCancel();
        return TRUE;
    }

    DWORD dwOldBits = m_ListCtl1.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES;
    m_ListCtl1.SetExtendedStyle(dwOldBits);

    DWORD dwOldBits2 = m_ListCtl2.GetExtendedStyle();
    dwOldBits2 |= LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES;
    m_ListCtl2.SetExtendedStyle(dwOldBits2);

    // Add the columns
    if (   !CListCtrlHelper::AddColumns(Columns1, m_ListCtl1)
        || !CListCtrlHelper::AddColumns(Columns2, m_ListCtl2) )
    {
        return FALSE;
    }
    // Daten einlesen

    //Wegen Sort
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM | LVIF_TEXT;
    lvi.iSubItem = 0;
    lvi.iItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;

    LV_ITEM lvi2;
    lvi2.mask = LVIF_PARAM | LVIF_TEXT;
    lvi2.iSubItem = 0;
    lvi2.iItem = 0;
    lvi2.pszText = LPSTR_TEXTCALLBACK;

    int iProgress = 0;
    m_Distress.SetBranchno(AeGetApp()->VzNr());
    BeginWaitCursor();
    m_Distress.GetCount();
    int iMax = m_Distress.GetCustomerno();
    CNMDProgress dlgProgress;
    dlgProgress.SetText(CResString::ex().getStrTblText(AETXT_EINLESEN));
    if (dlgProgress.GetSafeHwnd() == 0)
        dlgProgress.Create();
    if (dlgProgress.GetSafeHwnd() != 0)
        dlgProgress.SetMaxCount(iMax);

    CStringArray s;
    ppString cOrt;
    ppString cApo;
    ppString cAbc;
    ppString cPlz;
    s.SetSize(NUM_COLUMNS1);
    m_ListCtl1.DeleteAllItems();
    for (int i = 0; ; i++)
    {
        if (m_Distress.SelNot())
            break;
        ++iProgress;
        if (dlgProgress.GetSafeHwnd() != 0)
            dlgProgress.SetProgress(iProgress);
        // wichtig für Sort
        lvi.lParam = (LPARAM)i;
        s[0].Format("% 8ld", m_Distress.GetCustomerno());
        s[1].Format("%02ld", m_Distress.GetPersonalnrvertr());
        m_Distress.GetNameapo(cApo);
        s[2] = cApo;
        m_Distress.GetOrt(cOrt);
        s[3] = cOrt;
        s[4].Format("% 2d", m_Distress.GetDestbranchno());
        m_Distress.GetKzkdklasse(cAbc);
        s[5] = cAbc;
        m_Distress.GetPostleitzahl(cPlz);
        s[6] = cPlz;

        if (!CListCtrlHelper::InsertItem(m_ListCtl1, NUM_COLUMNS1, s, lvi))
        {
            EndWaitCursor();
            return FALSE;
        }
        // wichtig für Sort
        lvi.iItem++;
    }
    m_iCountlist1 = m_ListCtl1.GetItemCount();
    s.SetSize(NUM_COLUMNS2);
    m_Distress.SetBranchno( AeGetApp()->VzNr() );
    m_ListCtl2.DeleteAllItems();
    for (int i = 0;; i++)
    {
        if (m_Distress.SelRouted())
            break;
        // wichtig für Sort
        ++iProgress;
        if (dlgProgress.GetSafeHwnd() != 0)
            dlgProgress.SetProgress(iProgress);
        lvi2.lParam = (LPARAM)i;
        s[0].Format("% 8ld", m_Distress.GetCustomerno());
        s[1].Format("%02ld", m_Distress.GetPersonalnrvertr());
        m_Distress.GetNameapo(cApo);
        s[2] = cApo;
        m_Distress.GetOrt(cOrt);
        s[3] = cOrt;
        s[4].Format("% 2d", m_Distress.GetDestbranchno());
        m_Distress.GetKzkdklasse(cAbc);
        s[5] = cAbc;
        m_Distress.GetPostleitzahl(cPlz);
        s[6] = cPlz;

        if (!CListCtrlHelper::InsertItem(m_ListCtl2, NUM_COLUMNS1, s, lvi2))
        {
            EndWaitCursor();
            return FALSE;
        }
        // wichtig für Sort
        lvi2.iItem++;
    }
    m_iCountlist2 = m_ListCtl2.GetItemCount();
    CZIELFILIALEN fil;
    CString cDestBranch;
    ppString csName;
    fil.SetFilialnr( AeGetApp()->VzNr() );
    for (;;)
    {
        if (fil.SelList() != SRV_OK)
            break;
        cDestBranch.Format("%2d %s", fil.GetFilialnr(), fil.GetName(csName));
        m_combo_DestBranch.AddString(cDestBranch);
    }
    m_combo_DestBranch.SetCurSel(0);
    m_combo_DestBranch.GetLBText(m_combo_DestBranch.GetCurSel(), cDestBranch);
    m_sDestBranch = static_cast<short>(atoi(cDestBranch.Left(2)));

    if (dlgProgress.GetSafeHwnd() != 0)
        dlgProgress.DestroyWindow();

    EndWaitCursor();
    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDDistressRouting::OnBnClickedButtonAdd()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS2);

    CCHECKDISTRESS distress;
    distress.SetFilialnr(AeGetApp()->VzNr());
    if (!distress.IsInWork())
    {
        MsgBoxOK(AETXT_DISTRESS_IN_WORD);
        return;
    }

    //Wegen Sort
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM | LVIF_TEXT;
    lvi.iSubItem = 0;
    lvi.iItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;

    for (;;)
    {
        int pos = m_ListCtl1.GetNextItem(-1, LVNI_SELECTED);
        if (pos < 0)
            break;

        m_Distress.SetBranchno(AeGetApp()->VzNr());
        m_Distress.SetCustomerno(atol(m_ListCtl1.GetItemText(pos, 0)));
        m_Distress.SetDestbranchno(m_sDestBranch);
        m_Distress.Update();
        lvi.lParam = (LPARAM)m_iCountlist2;
        s[0] = m_ListCtl1.GetItemText(pos, 0);
        s[1] = m_ListCtl1.GetItemText(pos, 1);
        s[2] = m_ListCtl1.GetItemText(pos, 2);
        s[3] = m_ListCtl1.GetItemText(pos, 3);
        s[4].Format("% 2d", m_sDestBranch);
        s[5] = m_ListCtl1.GetItemText(pos, 5);
        s[6] = m_ListCtl1.GetItemText(pos, 6);
        ++m_iCountlist2;

        if (!CListCtrlHelper::InsertItem(m_ListCtl2, NUM_COLUMNS2, s, lvi))
        {
            EndWaitCursor();
            return;
        }
        m_ListCtl1.DeleteItem(pos);
    }
}

void CDDistressRouting::OnBnClickedButtonRemove()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS1);

    CCHECKDISTRESS distress;
    distress.SetFilialnr(AeGetApp()->VzNr());
    if (!distress.IsInWork())
    {
        MsgBoxOK(AETXT_DISTRESS_IN_WORD);
        return;
    }

    //Wegen Sort
    LV_ITEM lvi;
    lvi.mask = LVIF_PARAM | LVIF_TEXT;
    lvi.iSubItem = 0;
    lvi.iItem = 0;
    lvi.pszText = LPSTR_TEXTCALLBACK;

    for (;;)
    {
        int pos = m_ListCtl2.GetNextItem(-1, LVNI_SELECTED);
        if (pos < 0) break;

        m_Distress.SetBranchno(AeGetApp()->VzNr());
        m_Distress.SetCustomerno(atol(m_ListCtl2.GetItemText(pos, 0)));
        m_Distress.SetDestbranchno(0);
        m_Distress.Update();
        lvi.lParam = (LPARAM) m_iCountlist1;
        s[0] = m_ListCtl2.GetItemText(pos, 0);
        s[1] = m_ListCtl2.GetItemText(pos, 1);
        s[2] = m_ListCtl2.GetItemText(pos, 2);
        s[3] = m_ListCtl2.GetItemText(pos, 3);
        s[4] = "0";
        s[5] = m_ListCtl2.GetItemText(pos, 5);
        s[6] = m_ListCtl2.GetItemText(pos, 6);
        m_iCountlist1++;

        if (!CListCtrlHelper::InsertItem(m_ListCtl1, NUM_COLUMNS1, s, lvi))
        {
            EndWaitCursor();
            return;
        }
        m_ListCtl2.DeleteItem(pos);
    }
}

void CDDistressRouting::OnCbnSelchangeComboDestBranch()
{
    CString cDestBranch;
    m_combo_DestBranch.GetLBText(m_combo_DestBranch.GetCurSel(),cDestBranch);
    m_sDestBranch = static_cast<short>(atoi(cDestBranch.Left(2)));
}

// CompareListe ist eine stand alone Funktion
/////////////////////////////////////////////////////////////////////////////
// CompareListe(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
/////////////////////////////////////////////////////////////////////////////
int CALLBACK CompareDistressListeUp(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    if (s->GetAt(lParam1) == s->GetAt(lParam2)) return 0;
    else if (s->GetAt(lParam1) > s->GetAt(lParam2)) return 1;
    else return -1;
}

int CALLBACK CompareDistressListeDown(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    CStringArray* s = (CStringArray*)lParamSort;
    if (s->GetAt(lParam1) == s->GetAt(lParam2))
        return 0;
    else if (s->GetAt(lParam1) > s->GetAt(lParam2))
        return -1;
    else
        return 1;
}

void CDDistressRouting::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    //LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    int col;
    int max;
    int index;
    //Wegen Sort
    LV_ITEM lvi;

    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    col = pNMListView->iSubItem;

    max = m_ListCtl1.GetItemCount();
    CStringArray s;
    CString sorttext;
    s.SetSize(m_iCountlist1);
    for (index = 0;index < m_iCountlist1;index++)
    {
        //StringArray an der ursprünglichen Position setzen
        lvi.iItem = index;
        lvi.mask = LVIF_PARAM;  //muss gesetzt sein, um lParam abzuholen
        if (!m_ListCtl1.GetItem(&lvi)) continue;    //Ursprungadresse steht in lParam
        s[(int)lvi.lParam] = m_ListCtl1.GetItemText(index, col);
    }
    if (m_iCol1 == col)
    {
        if (m_iOrder1 == 0)
        {
            m_ListCtl1.SortItems(CompareDistressListeDown, (LPARAM)&s);
            m_iOrder1 = 1;
        }
        else
        {
            m_ListCtl1.SortItems(CompareDistressListeUp, (LPARAM)&s);
            m_iOrder1 = 0;
        }
    }
    else
    {
        m_ListCtl1.SortItems(CompareDistressListeUp, (LPARAM)&s);
        m_iOrder1 = 0;
    }
    m_iCol1 = col;

    *pResult = 0L;
}

void CDDistressRouting::OnLvnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
    //LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    int col;
    int max;
    int index;
    //Wegen Sort
    LV_ITEM lvi2;

    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    col = pNMListView->iSubItem;
    max = m_ListCtl2.GetItemCount();
    CStringArray s;
    s.SetSize(m_iCountlist2);
    for (index = 0;index < m_iCountlist2;index++)
    {
        //StringArray an der ursprünglichen Position setzen
        lvi2.iItem = index;
        lvi2.mask = LVIF_PARAM; //muss gesetzt sein, um lParam abzuholen
        if (!m_ListCtl2.GetItem(&lvi2)) continue;   //Ursprungadresse steht in lParam
        //m_ListCtl2.GetItem(&lvi2);    //Ursprungadresse steht in lParam
        s[(int)lvi2.lParam] = m_ListCtl2.GetItemText(index, col);
    }

    //LVCOLUMN lvcol;

    //lvcol.mask = LVCF_IMAGE;

    //// Double the column width of the first column.
    //for (int iSubItem = 0; iSubItem < NUM_COLUMNS1; iSubItem++)
    //{
    //  if (m_ListCtl2.GetColumn(iSubItem, &lvcol))
    //  {
    //      lvcol.iImage = -1;
    //      m_ListCtl2.SetColumn(iSubItem, &lvcol);
    //  }
    //}

    if (m_iCol2 == col)
    {
        if (m_iOrder2 == 0)
        {
            m_ListCtl2.SortItems(CompareDistressListeDown, (LPARAM)&s);
            m_iOrder2 = 1;
        }
        else
        {
            m_ListCtl2.SortItems(CompareDistressListeUp, (LPARAM)&s);
            m_iOrder2 = 0;
        }
    }
    else
    {
        m_ListCtl2.SortItems(CompareDistressListeUp, (LPARAM)&s);
        m_iOrder2 = 0;
    }
    m_iCol2 = col;
    //if (m_ListCtl2.GetColumn(col, &lvcol))
    //{
    //  lvcol.iImage = m_iOrder2;
    //  m_ListCtl2.SetColumn(col, &lvcol);
    //}

    *pResult = 0L;
}

void CDDistressRouting::OnNMDblclkList1(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    OnBnClickedButtonAdd();
    *pResult = 0L;
}

void CDDistressRouting::OnNMDblclkList2(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    OnBnClickedButtonRemove();
    *pResult = 0L;
}
