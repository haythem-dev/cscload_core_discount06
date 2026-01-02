// DZeitart.cpp : implementation file
//

#include "stdafx.h"
#include "DZeitart.h"
#include "zeitart.h"

#define MAXIMUM_ZUSATZ  2
#define ZEILEN 12    /* *** Anzahl der Zeilen der Listbox *** */

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     9

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "",  50, LVCFMT_LEFT,
    2,  "",  80, LVCFMT_LEFT,
    3,  "",  50, LVCFMT_LEFT,
    4,  "",  60, LVCFMT_RIGHT,
    5,  "",  60, LVCFMT_RIGHT,
    6,  " ",  0, LVCFMT_LEFT,
    7,  "",  50, LVCFMT_LEFT,
    8,  " ",  0, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDZeitart dialog


CDZeitart::CDZeitart(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDZeitart::IDD, pParent)
    , m_CZeitart(_T("")), CPageBrowser(ZEILEN)
{
    m_CZeitkey = _T("");
    m_CZeitart = _T("");

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_ZEITART);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_ZEITKEY);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_TAG);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_BEGIN);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_ENDE);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_ZUSATZ);
}

void CDZeitart::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ZEITKEY, m_Edit_Zeitkey);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_ZEITKEY, m_CZeitkey);
    DDX_Control(pDX, IDC_COMBO_ZEITART, m_Combo_Zeitart);
    DDX_CBString(pDX, IDC_COMBO_ZEITART, m_CZeitart);
}


BEGIN_MESSAGE_MAP(CDZeitart, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_DELETE, OnDelete)
    ON_EN_CHANGE(IDC_EDIT_ZEITKEY, OnChangeEditZeitkey)
    ON_BN_CLICKED(IDC_NEU, OnNeu)
    ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_CBN_SELCHANGE(IDC_COMBO_ZEITART, OnCbnSelchangeComboZeitart)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDZeitart message handlers

BOOL CDZeitart::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    m_Filiale = AeGetApp()->FilialNr();
    m_Vz = AeGetApp()->VzNr();

    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_SUNDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_MONDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_TUESDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_WEDNESDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_THURSDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_FRIDAY));
    m_Tagtab.Add(CResString::ex().getStrTblText(IDS_SHORT_SATURDAY));

    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART1));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART2));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART3));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART4));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART5));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART6));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART7));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART8));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART9));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART10));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART11));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART12));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART13));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART99));
    m_Combo_Zeitart.SetCurSel(0);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDZeitart::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    CZEITARTV zeitartv;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        CString zkey;
        if (m_CZeitkey.IsEmpty()) zkey = m_CZeitkey + '%';
        else zkey = m_CZeitkey;
        strcpy(zeitartv.s.ZEITSCHLUESSEL, zkey);
        zeitartv.s.ZEITART = m_Combo_Zeitart.GetCurSel() + 1;
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, zeitartv.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    zeitartv.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        zeitartv.Server(AafilSel_zeitarten);
        m_bCursorOpen = true;       //Datenbankcurser offen
        zeitartv.s.FETCH_REL = 1;          //normaler Fetch
        if (zeitartv.rc == SRV_SQLNOTFOUND)
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
        s[1].Format("%d", zeitartv.s.ZEITART);
        AllgEntfSpaces(zeitartv.s.ZEITSCHLUESSEL);
        s[2] = zeitartv.s.ZEITSCHLUESSEL;
        //AllgEntfSpaces(zeitartv.s.TAGESTYP);
        s[3] = m_Tagtab.GetAt(zeitartv.s.WEEKDAY);
        s[4].Format("%d", zeitartv.s.ZEITBEGIN);
        s[5].Format("%d", zeitartv.s.ZEITENDE);
        s[6].Format("%d", zeitartv.s.LFDNR);
        s[7].Format("%s", zeitartv.s.ZEITZUSATZ);
        s[8].Format("%d", zeitartv.s.WEEKDAY);

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

void CDZeitart::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDZeitart::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CZEITARTV zeitartv;
    zeitartv.s.FETCH_REL = 0;
    BeginWaitCursor();
    zeitartv.Server(AafilSel_zeitarten);
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDZeitart::OnOK()
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

void CDZeitart::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDUpdZeitart dlgUpdZeitart;
        dlgUpdZeitart.m_iZeitart = atoi(m_ListCtl.GetItemText(pos, 1));
        dlgUpdZeitart.m_CKey = m_ListCtl.GetItemText(pos, 2);
        dlgUpdZeitart.m_CTag = m_ListCtl.GetItemText(pos, 3);
        dlgUpdZeitart.m_CZusatz = m_ListCtl.GetItemText(pos, 7);
        m_Lfd = atol(m_ListCtl.GetItemText(pos, 6));
        long anfang = atol(m_ListCtl.GetItemText(pos, 4));
        long ende = atol(m_ListCtl.GetItemText(pos, 5));
        dlgUpdZeitart.m_iTag = atol(m_ListCtl.GetItemText(pos, 8));
        dlgUpdZeitart.m_iAnfhh = anfang / 10000;
        dlgUpdZeitart.m_iAnfmm = anfang / 100 % 100;
        dlgUpdZeitart.m_iAnfss = anfang % 100;
        dlgUpdZeitart.m_iEndhh = ende / 10000;
        dlgUpdZeitart.m_iEndmm = ende / 100 % 100;
        dlgUpdZeitart.m_iEndss = ende % 100;
        dlgUpdZeitart.m_pTagtab = &m_Tagtab;
        if (dlgUpdZeitart.DoModal() == IDOK)
        {
            CZEITARTV zeitartv;
            zeitartv.s.LFDNR = m_Lfd;
            zeitartv.s.ZEITART = dlgUpdZeitart.m_iZeitart;
            strcpy(zeitartv.s.ZEITSCHLUESSEL, dlgUpdZeitart.m_CKey);
            strcpy(zeitartv.s.TAGESTYP, dlgUpdZeitart.m_CTag);
            strcpy(zeitartv.s.ZEITZUSATZ, dlgUpdZeitart.m_CZusatz);
            zeitartv.s.VERTRIEBSZENTRUMNR = m_Vz;
            zeitartv.s.ZEITBEGIN = dlgUpdZeitart.m_iAnfhh * 10000 + dlgUpdZeitart.m_iAnfmm * 100 + dlgUpdZeitart.m_iAnfss;
            zeitartv.s.ZEITENDE = dlgUpdZeitart.m_iEndhh * 10000 + dlgUpdZeitart.m_iEndmm * 100 + dlgUpdZeitart.m_iEndss;
            zeitartv.s.WEEKDAY = static_cast<short>(dlgUpdZeitart.m_iTag);
            zeitartv.Server(AafilUpd_zeitarten);
            CloseCursor();
            GetPage();
        }
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDZeitart::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDZeitart::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDZeitart::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}

void CDZeitart::OnDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_ZEITART_DEL) == IDYES)
        {
            CZEITARTV zeitartv;
            m_Lfd = atol(m_ListCtl.GetItemText(pos, 6));
            zeitartv.s.LFDNR = m_Lfd;
            zeitartv.Server(AafilDel_zeitart);
            CloseCursor();
            GetPage();
        }
    }
}

void CDZeitart::OnChangeEditZeitkey()
{
    m_bFirstDataset = true;

}

void CDZeitart::OnCbnSelchangeComboZeitart()
{
    m_bFirstDataset = true;
}

void CDZeitart::OnNeu()
{
    // TODO: there is no check if a data set already exists in DB, so an -239 (duplicate unique index) could occur
    //       - and makes the app CRASH ! (fancy kind of code)
    //       as there is no select for the insert values and I don't want to loop through all ZEITARTEN entries, I let this issue open ...

    CDUpdZeitart dlgUpdZeitart;
    dlgUpdZeitart.m_pTagtab = &m_Tagtab;
    dlgUpdZeitart.m_iZeitart = m_Combo_Zeitart.GetCurSel() + 1;
    if (dlgUpdZeitart.DoModal() == IDOK)
    {
        CZEITARTV zeitartv;
        zeitartv.s.LFDNR = 0;
        zeitartv.s.ZEITART = dlgUpdZeitart.m_iZeitart;
        zeitartv.s.VERTRIEBSZENTRUMNR = m_Vz;
        strcpy(zeitartv.s.ZEITSCHLUESSEL, dlgUpdZeitart.m_CKey);
        strcpy(zeitartv.s.TAGESTYP, dlgUpdZeitart.m_CTag);
        strcpy(zeitartv.s.ZEITZUSATZ, dlgUpdZeitart.m_CZusatz);
        zeitartv.s.ZEITBEGIN = dlgUpdZeitart.m_iAnfhh * 10000 + dlgUpdZeitart.m_iAnfmm * 100 + dlgUpdZeitart.m_iAnfss;
        zeitartv.s.ZEITENDE = dlgUpdZeitart.m_iEndhh * 10000 + dlgUpdZeitart.m_iEndmm * 100 + dlgUpdZeitart.m_iEndss;
        zeitartv.s.WEEKDAY = static_cast<short>(dlgUpdZeitart.m_iTag);
        zeitartv.Server(AafilIns_zeitarten);
        CloseCursor();
        GetPage();
    }
}

void CDZeitart::OnUpdate()
{
    SelectEintrag();
}

/////////////////////////////////////////////////////////////////////////////
// CDUpdZeitart dialog


CDUpdZeitart::CDUpdZeitart(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDUpdZeitart::IDD, pParent)
    , m_CZeitart(_T(""))
    , m_CTag(_T(""))
{
    m_iAnfhh = 0;
    m_iAnfmm = 0;
    m_iAnfss = 0;
    m_iEndhh = 0;
    m_iEndmm = 0;
    m_iEndss = 0;
    m_CKey = _T("");
    m_CZusatz = _T("");
    m_iZeitart = 1;
    m_iTag = 0;
}


void CDUpdZeitart::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ZUSATZ, m_EditZusatz);
    DDX_Control(pDX, IDC_EDIT_KEY, m_EditKey);
    DDX_Control(pDX, IDC_EDIT_END_SS, m_EditEndss);
    DDX_Control(pDX, IDC_EDIT_END_MM, m_EditEndmm);
    DDX_Control(pDX, IDC_EDIT_END_HH, m_EditEndhh);
    DDX_Control(pDX, IDC_EDIT_ANF_SS, m_EditAnfss);
    DDX_Control(pDX, IDC_EDIT_ANF_MM, m_EditAnfmm);
    DDX_Control(pDX, IDC_EDIT_ANF_HH, m_EditAnfhh);
    DDX_Text(pDX, IDC_EDIT_ANF_HH, m_iAnfhh);
    DDX_Text(pDX, IDC_EDIT_ANF_MM, m_iAnfmm);
    DDX_Text(pDX, IDC_EDIT_ANF_SS, m_iAnfss);
    DDX_Text(pDX, IDC_EDIT_END_HH, m_iEndhh);
    DDX_Text(pDX, IDC_EDIT_END_MM, m_iEndmm);
    DDX_Text(pDX, IDC_EDIT_END_SS, m_iEndss);
    DDX_Text(pDX, IDC_EDIT_KEY, m_CKey);
    DDX_Text(pDX, IDC_EDIT_ZUSATZ, m_CZusatz);
    DDX_Control(pDX, IDC_COMBO_ZEITART, m_Combo_Zeitart);
    DDX_CBString(pDX, IDC_COMBO_ZEITART, m_CZeitart);
    DDX_Control(pDX, IDC_COMBO_TAG, m_Combo_Tag);
    DDX_CBString(pDX, IDC_COMBO_TAG, m_CTag);
}


BEGIN_MESSAGE_MAP(CDUpdZeitart, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_ANF_HH, OnChangeEditAnfHh)
    ON_EN_CHANGE(IDC_EDIT_ANF_MM, OnChangeEditAnfMm)
    ON_EN_CHANGE(IDC_EDIT_ANF_SS, OnChangeEditAnfSs)
    ON_EN_CHANGE(IDC_EDIT_END_HH, OnChangeEditEndHh)
    ON_EN_CHANGE(IDC_EDIT_END_MM, OnChangeEditEndMm)
    ON_EN_CHANGE(IDC_EDIT_END_SS, OnChangeEditEndSs)
    ON_EN_CHANGE(IDC_EDIT_KEY, OnChangeEditKey)
    ON_EN_CHANGE(IDC_EDIT_ZUSATZ, OnChangeEditZusatz)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDUpdZeitart message handlers

BOOL CDUpdZeitart::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART1));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART2));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART3));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART4));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART5));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART6));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART7));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART8));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART9));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART10));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART11));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART12));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART13));
    m_Combo_Zeitart.AddString(CResString::ex().getStrTblText(AETXT_ZEITART99));
    m_Combo_Zeitart.SetCurSel(m_iZeitart - 1);

    for (int i = 0; i < 7; i++)
    {
        m_Combo_Tag.AddString(m_pTagtab->GetAt(i));
    }
    m_Combo_Tag.SetCurSel(m_iTag);

    if (!m_CKey.IsEmpty())
    {
        m_Combo_Zeitart.EnableWindow(FALSE);
        m_EditKey.EnableWindow(FALSE);
        m_Combo_Tag.EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDUpdZeitart::OnChangeEditAnfHh()
{
    AllgWertKontr(&m_EditAnfhh, MAXIMUM_HOUR);
}

void CDUpdZeitart::OnChangeEditAnfMm()
{
    AllgWertKontr(&m_EditAnfmm, MAXIMUM_MIN);
}

void CDUpdZeitart::OnChangeEditAnfSs()
{
    AllgWertKontr(&m_EditAnfss, MAXIMUM_MIN);
}

void CDUpdZeitart::OnChangeEditEndHh()
{
    AllgWertKontr(&m_EditEndhh, MAXIMUM_HOUR);
}

void CDUpdZeitart::OnChangeEditEndMm()
{
    AllgWertKontr(&m_EditEndmm, MAXIMUM_MIN);
}

void CDUpdZeitart::OnChangeEditEndSs()
{
    AllgWertKontr(&m_EditEndss, MAXIMUM_MIN);
}

void CDUpdZeitart::OnOK()
{
    m_iZeitart = m_Combo_Zeitart.GetCurSel() + 1;
    m_iTag = m_Combo_Tag.GetCurSel();

    CDialogMultiLang::OnOK();
}

void CDUpdZeitart::OnChangeEditKey()
{
    AllgLaengeKontr(&m_EditKey, L_ZEITARTV_ZEITSCHLUESSEL,AeGetApp()->Modus());
}

void CDUpdZeitart::OnChangeEditZusatz()
{
    AllgWertKontr(&m_EditZusatz, MAXIMUM_ZUSATZ);
}
