// AltFil.cpp : implementation file
//

#include "stdafx.h"
#include "AltFil.h"
#include <alterfil.h>
#include "ppDataTypes.h"

#define ZEILEN 12    /* Anzahl der Zeilen der Listbox */

//Definition der Tabellenbreite und der Ueberschriften

#define COL_ALTFIL_KB       0
#define COL_ALTFIL_FOLGE    1
#define COL_ALTFIL_FILI     2
#define COL_ALTFIL_AKTIV    3
#define COL_ALTFIL_IDF      4
#define COL_ALTFIL_BGA      5
#define COL_ALTFIL_STDBGA   6
#define COL_ALTFIL_TAGENDE  7
#define COL_ALTFIL_TOURAB   8
#define COL_ALTFIL_TOURBIS  9
#define COL_ALTFIL_TYPTEXT  10
#define COL_ALTFIL_TYPNR    11
#define COL_ALTFIL_AKTIVNR  12

#define NUM_COLUMNS     13

static COLUMNS_TYPES Columns[] =
{
    COL_ALTFIL_KB,      "",  20, LVCFMT_LEFT,
    COL_ALTFIL_FOLGE,   "",  45, LVCFMT_RIGHT,
    COL_ALTFIL_FILI,    "",  45, LVCFMT_RIGHT,
    COL_ALTFIL_AKTIV,   "",  40, LVCFMT_LEFT,
    COL_ALTFIL_IDF,     "",   0, LVCFMT_RIGHT,
    COL_ALTFIL_BGA,     "", 100, LVCFMT_RIGHT,
    COL_ALTFIL_STDBGA,  "",  60, LVCFMT_LEFT,
    COL_ALTFIL_TAGENDE, "", 100, LVCFMT_RIGHT,
    COL_ALTFIL_TOURAB,  "",  80, LVCFMT_RIGHT,
    COL_ALTFIL_TOURBIS, "",  90, LVCFMT_RIGHT,
    COL_ALTFIL_TYPTEXT, "", 100, LVCFMT_LEFT,
    COL_ALTFIL_TYPNR,   "",   0, LVCFMT_LEFT,
    COL_ALTFIL_AKTIVNR, "",   0, LVCFMT_LEFT,
    -1,                 "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CAltFil dialog


CAltFil::CAltFil(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CAltFil::IDD, pParent), CPageBrowser(ZEILEN)
{
    Columns[COL_ALTFIL_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_ALTFIL_FOLGE].Columns = CResString::ex().getStrTblText(AETXT_FOLGE);
    Columns[COL_ALTFIL_FILI].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    Columns[COL_ALTFIL_AKTIV].Columns = CResString::ex().getStrTblText(AETXT_AKTIV);
    Columns[COL_ALTFIL_IDF].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[COL_ALTFIL_BGA].Columns = CResString::ex().getStrTblText(AETXT_BGA_NR_TAG);
    Columns[COL_ALTFIL_TOURBIS].Columns = CResString::ex().getStrTblText(AETXT_VB_TOUR_ZEIT);
    Columns[COL_ALTFIL_TAGENDE].Columns = CResString::ex().getStrTblText(AETXT_VB_TOUR_ZEIT_TAG);
    Columns[COL_ALTFIL_TOURAB].Columns = CResString::ex().getStrTblText(AETXT_IBT_TOUR_AB);
    Columns[COL_ALTFIL_TYPTEXT].Columns = CResString::ex().getStrTblText(AETXT_VB_TYP);
    Columns[COL_ALTFIL_TYPNR].Columns = CResString::ex().getStrTblText(AETXT_VB_TYP);
    Columns[COL_ALTFIL_AKTIVNR].Columns = CResString::ex().getStrTblText(AETXT_AKTIV);
    Columns[COL_ALTFIL_STDBGA].Columns = CResString::ex().getStrTblText(AETXT_STD_BGA_NR);
}

void CAltFil::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}

BEGIN_MESSAGE_MAP(CAltFil, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_DELETE, OnDelete)
    ON_BN_CLICKED(IDC_NEU, OnNeu)
    ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAltFil message handlers

BOOL CAltFil::OnInitDialog()
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

bool CAltFil::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    CALTFIL altfil;
    ppTime p;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        altfil.s.FILIALNR = m_FilialNr;
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, altfil.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        //altfil.CursorServerCall(AafilSel_altfil, a.s.FETCH_REL);
        altfil.Server(AafilSel_altfil);
        m_bCursorOpen = true;       //Datenbankcurser offen
        altfil.s.FETCH_REL = 1;          //normaler Fetch
        if (altfil.rc == SRV_SQLNOTFOUND)
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
        s[COL_ALTFIL_KB] = kb.Next();
        s[COL_ALTFIL_FOLGE].Format("%d", altfil.s.REIHENFOLGENR);
        s[COL_ALTFIL_FILI].Format("%d", altfil.s.VERBUNDFILIALNR);
        if (altfil.s.FILIALTYP > 1) s[COL_ALTFIL_AKTIV] = CResString::ex().getStrTblText(AETXT_JA);
        else s[COL_ALTFIL_AKTIV] = CResString::ex().getStrTblText(AETXT_NEIN);
        s[COL_ALTFIL_IDF].Format("%d", altfil.s.KDNR);
        if (altfil.s.TAGTOURBGANR == 0)
        {
            s[COL_ALTFIL_BGA].Format("%d", AeGetApp()->BGANR_EK());
            s[COL_ALTFIL_STDBGA] = CResString::ex().getStrTblText(AETXT_JA);
        }
        else
        {
            s[COL_ALTFIL_BGA].Format("%d", altfil.s.TAGTOURBGANR);
            s[COL_ALTFIL_STDBGA] = CResString::ex().getStrTblText(AETXT_NEIN);
        }
        p.SetTime(altfil.s.VBTOURZEIT / 100);    // ausgeben ohne Sekunden
        s[COL_ALTFIL_TOURBIS] = (const char*)p;
        p.SetTime(altfil.s.VBTAGTOURZEIT / 100); // ausgeben ohne Sekunden
        //ppTime p(altfil.s.VBTAGTOURZEIT, ppTime::display_hhmm, true);
        s[COL_ALTFIL_TAGENDE] = (const char*)p;
        s[COL_ALTFIL_TOURAB].Format("%0.2d:%0.2d", altfil.s.IBTDELIVERYTIME / 100, altfil.s.IBTDELIVERYTIME % 100);
        if      (altfil.s.VBTYP == 0) s[COL_ALTFIL_TYPTEXT] = CResString::ex().getStrTblText(AETEXT_NORMAL);
        else if (altfil.s.VBTYP == 1) s[COL_ALTFIL_TYPTEXT] = CResString::ex().getStrTblText(AETXT_PRIVATSORTIMENT);
        else if (altfil.s.VBTYP == 2) s[COL_ALTFIL_TYPTEXT] = CResString::ex().getStrTblText(AETXT_VETO);
        else if (altfil.s.VBTYP == 3) s[COL_ALTFIL_TYPTEXT] = CResString::ex().getStrTblText(AETXT_REGIONAL);
        else if (altfil.s.VBTYP == 4) s[COL_ALTFIL_TYPTEXT] = CResString::ex().getStrTblText(AETXT_TAGVERBUND);
        else if (altfil.s.VBTYP == 5) s[COL_ALTFIL_TYPTEXT] = CResString::ex().getStrTblText(AETXT_NATIONAL);
        else                          s[COL_ALTFIL_TYPTEXT].Empty();
        s[COL_ALTFIL_TYPNR].Format("%d", altfil.s.VBTYP);
        s[COL_ALTFIL_AKTIVNR].Format("%d", altfil.s.FILIALTYP);

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

void CAltFil::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CAltFil::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CALTFIL altfil;
    altfil.s.FETCH_REL = 0;
    BeginWaitCursor();
    altfil.Server( AafilSel_altfil );
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CAltFil::OnOK()
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

void CAltFil::SelectEintrag()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CUpdAltfil dlgUpdAltfil;
        dlgUpdAltfil.m_CFolge = m_ListCtl.GetItemText(pos, COL_ALTFIL_FOLGE);
        dlgUpdAltfil.m_CFilnr = m_ListCtl.GetItemText(pos, COL_ALTFIL_FILI);
        dlgUpdAltfil.m_CKdnr = m_ListCtl.GetItemText(pos, COL_ALTFIL_IDF);
        dlgUpdAltfil.m_bAb = ((m_ListCtl.GetItemText(pos, COL_ALTFIL_AKTIVNR) == "2") || (m_ListCtl.GetItemText(pos, COL_ALTFIL_AKTIVNR) == "3")) ? TRUE : FALSE;
        dlgUpdAltfil.m_CBgaTag = m_ListCtl.GetItemText(pos, COL_ALTFIL_BGA);
        dlgUpdAltfil.m_CZeit = m_ListCtl.GetItemText(pos, COL_ALTFIL_TOURBIS);
        dlgUpdAltfil.m_CZeitTag = m_ListCtl.GetItemText(pos, COL_ALTFIL_TAGENDE);
        dlgUpdAltfil.m_CFahrzeit = m_ListCtl.GetItemText(pos, COL_ALTFIL_TOURAB);
        dlgUpdAltfil.m_sTyp = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, COL_ALTFIL_TYPNR)));
        if (dlgUpdAltfil.DoModal() == IDOK)
        {
            CALTFIL altfil;
            altfil.s.VBTOURZEIT = dlgUpdAltfil.m_EditTourzeit.GetTimeLong() * 100;          // mit Sekunden abspeichern
            altfil.s.VBTAGTOURZEIT = dlgUpdAltfil.m_EditTourzeitTag.GetTimeLong() * 100;    // mit Sekunden abspeichern
            altfil.s.TAGTOURBGANR = atol(dlgUpdAltfil.m_CBgaTag);
            altfil.s.REIHENFOLGENR = atol(dlgUpdAltfil.m_CFolge);
            altfil.s.VERBUNDFILIALNR = static_cast<short>(atoi(dlgUpdAltfil.m_CFilnr));
            altfil.s.IBTDELIVERYTIME = static_cast<short>(dlgUpdAltfil.m_EditFahrzeit.GetTimeLong()); // mit Sekunden abspeichern
            altfil.s.VBTYP = dlgUpdAltfil.m_sTyp;
            altfil.s.KDNR = atol(dlgUpdAltfil.m_CKdnr);
            altfil.s.FILIALNR = m_FilialNr;
            altfil.s.FILIALTYP = dlgUpdAltfil.m_bAb ? 2 : 0;
            altfil.Server(AafilUpd_altfil);
            CloseCursor();
            GetPage();
        }
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CAltFil::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CAltFil::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CAltFil::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}

void CAltFil::OnDelete()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        if (MsgBoxYesNo(IDP_ALTFIL_DEL) == IDYES)
        {
            CALTFIL altfil;
            altfil.s.REIHENFOLGENR = atol(m_ListCtl.GetItemText(pos, COL_ALTFIL_FOLGE));
            altfil.s.FILIALNR = m_FilialNr;
            altfil.s.VBTYP = static_cast<short>( atoi(m_ListCtl.GetItemText(pos, COL_ALTFIL_TYPNR)) );
            altfil.Server( AafilDel_altfil );
            CloseCursor();
            GetPage();
        }
    }
}

void CAltFil::OnNeu()
{
    CUpdAltfil dlgUpdAltfil;
    // mit aktiv vorbelegen
    dlgUpdAltfil.m_bAb = 2;
    if (dlgUpdAltfil.DoModal() == IDOK)
    {
        CALTFIL altfil;
        altfil.s.VBTOURZEIT = dlgUpdAltfil.m_EditTourzeit.GetTimeLong() * 100;  // mit Sekunden abspeichern
        altfil.s.VBTAGTOURZEIT = dlgUpdAltfil.m_EditTourzeitTag.GetTimeLong() * 100;    // mit Sekunden abspeichern
        altfil.s.TAGTOURBGANR = atol(dlgUpdAltfil.m_CBgaTag);
        altfil.s.REIHENFOLGENR = atol(dlgUpdAltfil.m_CFolge);
        altfil.s.VERBUNDFILIALNR = static_cast<short>( atoi(dlgUpdAltfil.m_CFilnr) );
        altfil.s.IBTDELIVERYTIME = static_cast<short>( dlgUpdAltfil.m_EditFahrzeit.GetTimeLong() ); // mit Sekunden abspeichern
        altfil.s.VBTYP = dlgUpdAltfil.m_sTyp;
        altfil.s.KDNR = atol(dlgUpdAltfil.m_CKdnr);
        altfil.s.FILIALNR = m_FilialNr;
        if (dlgUpdAltfil.m_bAb) altfil.s.FILIALTYP = 2;
        else altfil.s.FILIALTYP = 0;
        altfil.Server( AafilIns_altfil );
        CloseCursor();
        GetPage();
    }
}

void CAltFil::OnUpdate()
{
    SelectEintrag();
}

/////////////////////////////////////////////////////////////////////////////
// CUpdAltfil dialog

CUpdAltfil::CUpdAltfil(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CUpdAltfil::IDD, pParent)
    , m_CFahrzeit(_T(""))
{
    m_bAb = FALSE;
    m_CFilnr = _T("");
    m_CFolge = _T("");
    m_CKdnr = _T("");
    m_CBgaTag = _T("");
    m_sTyp = 0;
}

void CUpdAltfil::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_TOURZEIT_TAG, m_EditTourzeitTag);
    DDX_Control(pDX, IDC_EDIT_TOURZEIT, m_EditTourzeit);
    DDX_Control(pDX, IDC_EDIT_BGA_TAG, m_EditBgaTag);
    DDX_Control(pDX, IDC_EDIT_KDNR, m_EditKdnr);
    DDX_Control(pDX, IDC_EDIT_FOLGE, m_EditFolge);
    DDX_Control(pDX, IDC_EDIT_FILNR, m_EditFilnr);
    DDX_Check(pDX, IDC_CHECK_AB, m_bAb);
    DDX_Text(pDX, IDC_EDIT_FILNR, m_CFilnr);
    DDX_Text(pDX, IDC_EDIT_FOLGE, m_CFolge);
    DDX_Text(pDX, IDC_EDIT_KDNR, m_CKdnr);
    DDX_Text(pDX, IDC_EDIT_BGA_TAG, m_CBgaTag);
    DDX_Control(pDX, IDC_EDIT_FAHRZEIT, m_EditFahrzeit);
    DDX_Text(pDX, IDC_EDIT_FAHRZEIT, m_CFahrzeit);
    DDX_Control(pDX, IDC_COMBO_TYP, m_ComboTyp);
}


BEGIN_MESSAGE_MAP(CUpdAltfil, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_FILNR, OnChangeEditFilnr)
    ON_EN_CHANGE(IDC_EDIT_FOLGE, OnChangeEditFolge)
    ON_EN_CHANGE(IDC_EDIT_KDNR, OnChangeEditKdnr)
    ON_EN_CHANGE(IDC_EDIT_BGA_TAG, OnChangeEditBgaTag)
    ON_CBN_SELCHANGE(IDC_COMBO_TYP, OnCbnSelchangeComboTyp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdAltfil message handlers

void CUpdAltfil::OnChangeEditFilnr()
{
    AllgWertKontr(&m_EditFilnr, MAXIMUM_FILIALE);
}

void CUpdAltfil::OnChangeEditFolge()
{
    AllgWertKontr(&m_EditFolge, MAXIMUM_FILIALE);
}

void CUpdAltfil::OnChangeEditKdnr()
{
    AllgWertKontr(&m_EditKdnr, MAXIMUM_IDF);
}

void CUpdAltfil::OnOK()
{
    UpdateData();
    m_CFahrzeit = m_EditFahrzeit.GetTimeChar();
    m_sTyp = static_cast<short>(m_ComboTyp.GetCurSel());
    if (m_sTyp == 0 || m_sTyp == 4)
    {
        if (m_EditFahrzeit.GetTimeLong() == 0)
        {
            MsgBoxOK(AETXT_VB_TOUR_AB_FILL);
            m_EditFahrzeit.SetFocus();
            return;
        }
    }
    if (m_ComboTyp.GetCurSel() != 4)
    {
        m_EditTourzeitTag.SetTimeLong(0);
        m_EditTourzeit.SetTimeLong(0);
    }
    else
    {
        if (m_EditTourzeitTag.GetTimeLong() == 0)
        {
            MsgBoxOK(AETXT_VB_TAG_ENDE);
            m_EditTourzeitTag.SetFocus();
            return;
        }
        if (m_EditTourzeit.GetTimeLong() == 0)
        {
            MsgBoxOK(AETXT_VB_TAG_ZEIT);
            m_EditTourzeit.SetFocus();
            return;
        }
    }
    m_CZeit = m_EditTourzeit.GetTimeChar();
    m_CZeitTag = m_EditTourzeitTag.GetTimeChar();
    CDialogMultiLang::OnOK();
}

BOOL CUpdAltfil::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_ComboTyp.ResetContent();
    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETEXT_NORMAL));
    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_PRIVATSORTIMENT));
    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_VETO));
    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_REGIONAL));
    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_TAGVERBUND));
    m_ComboTyp.AddString(CResString::ex().getStrTblText(AETXT_NATIONAL));
    m_ComboTyp.SetCurSel(m_sTyp);

    if (!m_CFolge.IsEmpty())
    {
        m_EditFolge.EnableWindow(FALSE);
        m_ComboTyp.EnableWindow(FALSE);
    }
    m_EditTourzeit.SetTimeChar(m_CZeit);
    m_EditTourzeitTag.SetTimeChar(m_CZeitTag);
    m_EditFahrzeit.SetTimeChar(m_CFahrzeit);
    if (m_sTyp == 4)
    {
        m_EditTourzeitTag.EnableWindow(TRUE);
        m_EditTourzeit.EnableWindow(TRUE);
    }
    else
    {
        m_EditTourzeitTag.EnableWindow(FALSE);
        m_EditTourzeit.EnableWindow(FALSE);
        m_EditBgaTag.EnableWindow(FALSE);
        m_EditBgaTag.EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_BGA)->SetWindowText(CResString::ex().getStrTblText(AETXT_STD_BGA_NR));
    }
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CUpdAltfil::OnChangeEditBgaTag()
{
    AllgWertKontr(&m_EditBgaTag, MAXIMUM_IDF);
}

void CUpdAltfil::OnCbnSelchangeComboTyp()
{
    if (m_ComboTyp.GetCurSel() == 4)
    {
        m_EditTourzeitTag.EnableWindow(TRUE);
        m_EditTourzeit.EnableWindow(TRUE);
    }
    else
    {
        m_EditTourzeitTag.EnableWindow(FALSE);
        m_EditTourzeit.EnableWindow(FALSE);
    }
}
