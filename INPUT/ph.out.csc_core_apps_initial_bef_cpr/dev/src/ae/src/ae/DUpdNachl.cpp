// DUpdNachl.cpp : implementation file
//

#include "stdafx.h"
#include <artsel.h>
#include "nachlprot.h"
#include <kndsel.h>
#include "DDruckAuftrag.h"
#include "DKndInf.h"
#include "DKndWahl.h"
#include "DArtDef.h"
#include "DArtInf.h"
#include "DUpdNachl.h"
#include "druckpara.h"

static struct NACHLIEF sNachlief; // Speichern Select-bedingungen

#define AENDTYP_DELETE 1
#define AENDTYP_MENGENAENDERUNG 2
#define AENDTYP_LIEFERMOEGLICHKEIT 3
#define AENDTYP_FOLGE 4

#define ZEILEN 15    /* *** Anzahl der Zeilen der Listbox *** */

//Definition der Tabellenbreite und der Ueberschriften

#define COL_KB          0
#define COL_AART        1
#define COL_DATUM       2
#define COL_IDF         3
#define COL_APO         4
#define COL_AUFNR       5
#define COL_ARTCODE     6
#define COL_MENGE       7
#define COL_BESTAND     8
#define COL_EINHEIT     9
#define COL_NAME        10
#define COL_VZ          11
#define COL_TYP         12
#define COL_POSNR       13
#define COL_DATUMORG    14
#define COL_BEMERKUNG   15
#define COL_PZN         16
#define NUM_COLUMNS     17

static COLUMNS_TYPES Columns[] =
{
    COL_KB,        "",  20, LVCFMT_LEFT,
    COL_AART,      "",  35, LVCFMT_RIGHT,
    COL_DATUM,     "",  70, LVCFMT_RIGHT,
    COL_IDF,       "",  60, LVCFMT_RIGHT,
    COL_APO,       "",  90, LVCFMT_LEFT,
    COL_AUFNR,     "",  60, LVCFMT_RIGHT,
    COL_ARTCODE,   "",  90, LVCFMT_LEFT,
    COL_MENGE,     "",  50, LVCFMT_RIGHT,
    COL_BESTAND,   "",  70, LVCFMT_RIGHT,
    COL_EINHEIT,   "",  70, LVCFMT_LEFT,
    COL_NAME,      "", 210, LVCFMT_LEFT,
    COL_VZ,        "",  30, LVCFMT_LEFT,
    COL_TYP,       "",  40, LVCFMT_CENTER,
    COL_POSNR,     "",   0, LVCFMT_CENTER,
    COL_DATUMORG,  "",   0, LVCFMT_CENTER,
    COL_BEMERKUNG, "",  80, LVCFMT_LEFT,
    COL_PZN,       "",  60, LVCFMT_RIGHT,
    -1,            "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDUpdNachl dialog


CDUpdNachl::CDUpdNachl(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDUpdNachl::IDD, pParent)
    , m_bQuota(FALSE), CPageBrowser(ZEILEN)
{
    m_bDispo = FALSE;
    m_bNachl = FALSE;
    m_CDatum = _T("");
    m_CIdf = _T("");
    m_CPzn = _T("");
    m_bDatum = FALSE;
    m_bAh = FALSE;
    m_bBestell = FALSE;
    m_bFolge = FALSE;
    m_bNgf = FALSE;
    m_lIdfNr = 0;
    m_lKndNr = 0;

    Columns[COL_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_AART].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
    Columns[COL_DATUM].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[COL_IDF].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[COL_APO].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    Columns[COL_AUFNR].Columns = CResString::ex().getStrTblText(AETXT_AUF_NR);
    Columns[COL_ARTCODE].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[COL_MENGE].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns[COL_BESTAND].Columns = CResString::ex().getStrTblText(AETXT_BESTAND);
    Columns[COL_EINHEIT].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[COL_NAME].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns[COL_VZ].Columns = CResString::ex().getStrTblText(AETXT_VZ);
    Columns[COL_TYP].Columns = CResString::ex().getStrTblText(AETXT_TYP);
    Columns[COL_POSNR].Columns = CResString::ex().getStrTblText(AETXT_POS);
    Columns[COL_DATUM].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[COL_BEMERKUNG].Columns = CResString::ex().getStrTblText(IDS_BEMERK);
    Columns[COL_PZN].Columns = CResString::ex().getStrTblText(AETXT_ARTIKEL_NR);
}

void CDUpdNachl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_VZ2, m_CBHome);
    DDX_Control(pDX, IDC_CHECK_NGF, m_CBNgf);
    DDX_Control(pDX, IDC_CHECK_FOLGE, m_CBFolge);
    DDX_Control(pDX, IDC_CHECK_BESTELL, m_CBBestell);
    DDX_Control(pDX, IDC_CHECK_AH, m_CBAh);
    DDX_Control(pDX, IDC_CHECK_DATUM, m_CBDatum);
    DDX_Control(pDX, IDC_EDIT_PZN, m_EditPzn);
    DDX_Control(pDX, IDC_EDIT_DATUM, m_EditDatum);
    DDX_Control(pDX, IDC_EDIT_IDF, m_EditIdf);
    DDX_Control(pDX, IDC_CHECK_NACHL, m_CBNachl);
    DDX_Control(pDX, IDC_CHECK_DISPO, m_CBDispo);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Check(pDX, IDC_CHECK_DISPO, m_bDispo);
    DDX_Check(pDX, IDC_CHECK_NACHL, m_bNachl);
    DDX_Text(pDX, IDC_EDIT_DATUM, m_CDatum);
    DDX_Text(pDX, IDC_EDIT_IDF, m_CIdf);
    DDX_Text(pDX, IDC_EDIT_PZN, m_CPzn);
    DDX_Check(pDX, IDC_CHECK_DATUM, m_bDatum);
    DDX_Check(pDX, IDC_CHECK_AH, m_bAh);
    DDX_Check(pDX, IDC_CHECK_BESTELL, m_bBestell);
    DDX_Check(pDX, IDC_CHECK_FOLGE, m_bFolge);
    DDX_Check(pDX, IDC_CHECK_NGF, m_bNgf);
    DDX_Control(pDX, IDC_CHECK_QUOTA, m_CBQuota);
    DDX_Check(pDX, IDC_CHECK_QUOTA, m_bQuota);
    DDX_Control(pDX, IDC_COMBO_AUFART, m_Cobox_Auf);
}

BEGIN_MESSAGE_MAP(CDUpdNachl, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnButtonKnd)
    ON_BN_CLICKED(IDC_CHECK_DISPO, OnCheckDispo)
    ON_BN_CLICKED(IDC_CHECK_NACHL, OnCheckNachl)
    ON_EN_CHANGE(IDC_EDIT_DATUM, OnChangeEditDatum)
    ON_EN_CHANGE(IDC_EDIT_IDF, OnChangeEditIdf)
    ON_BN_CLICKED(IDC_BUTTON_ARTIKEL, OnButtonArtikel)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK, OnButtonDruck)
    ON_BN_CLICKED(IDC_CHECK_AH, OnCheckAh)
    ON_BN_CLICKED(IDC_CHECK_BESTELL, OnCheckBestell)
    ON_BN_CLICKED(IDC_CHECK_FOLGE, OnCheckFolge)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK_LIST, OnButtonDruckList)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK_VB, OnButtonDruckVb)
    ON_BN_CLICKED(IDC_CHECK_NGF, OnCheckNgf)
    ON_BN_CLICKED(IDC_CHECK_VZ2, OnCheckVz2)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_BN_CLICKED(IDC_BUTTON_DRUCK_LIEF, OnBnClickedButtonDruckLief)
    ON_BN_CLICKED(IDC_CHECK_QUOTA, OnBnClickedCheckQuota)
    ON_CBN_SELCHANGE(IDC_COMBO_AUFART, OnCbnSelchangeComboAufart)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDUpdNachl message handlers

BOOL CDUpdNachl::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    m_bDeleted = FALSE;

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    m_CBNachl.SetCheck(1);
    //m_CBDispo.SetCheck(1);

    CString AArt;
    int rc;
    m_Cobox_Auf.ResetContent();
    m_AArt = "  ";
    m_Cobox_Auf.AddString(CResString::ex().getStrTblText(AETXT_ALLE));
    for (int i = 0;;i++)
    {
        rc = GetOrderType().GetAufArtenListeVZ(AeGetApp()->VzNr(), i, AArt);
        if (rc == -1) break;
        if (GetOrderType().IsNachlief(AeGetApp()->VzNr(), AArt.Left(2)))
        {
            m_Cobox_Auf.AddString(AArt);
        }
    }
    m_Cobox_Auf.SetCurSel(0);

    if (m_lIdfNr != 0) // wenn idf uebergeben
    {
        m_CIdf.Format("%ld", m_lIdfNr);
        UpdateData(FALSE);
        OnOK();
        return FALSE; //Cursor bleibt in der Listbox
    }

    if (AeGetApp()->IsKundeHome())
    {
        m_CBHome.SetCheck(TRUE);
    }
    if (!GetAeUser().IsMehrVz())
    {
        AeGetApp()->IsKundeHome = true;
        m_CBHome.SetCheck(TRUE);
        m_CBHome.EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDUpdNachl::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    char Out1[11];
    CStringArray s;
    CARTAESEL code;
    s.SetSize(NUM_COLUMNS);

    if (AeGetApp()->IsKundeHome())
        m_nachl.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    else
        m_nachl.s.VERTRIEBSZENTRUMNR = 0;
    m_nachl.s.REGIONNR = AeGetApp()->VzNr();
    strcpy(m_nachl.s.KDAUFTRAGART, m_AArt);

    //Anfangsinitialisierung durchfuehren
    if (m_bDeleted == TRUE)
    {
        m_nachl.s.FETCH_REL = (GetPageBeforeReset() - 1) * ZEILEN + 1;
        m_nachl.s.IDFNR = sNachlief.IDFNR;
        m_nachl.s.ARTIKEL_NR = sNachlief.ARTIKEL_NR;
        m_nachl.s.POSTYP = sNachlief.POSTYP;
        m_nachl.s.DATUM = sNachlief.DATUM;
        m_bDeleted = FALSE;
        RestorePageBeforeReset();
    }
    else if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        UpdateData();
        m_SelKz = 0;
        if (m_CBAh.GetCheck() == 1) m_SelKz += 1;
        if (m_CBFolge.GetCheck() == 1) m_SelKz += 10;
        if (m_CBBestell.GetCheck() == 1) m_SelKz += 100;
        if (m_CBNgf.GetCheck() == 1) m_SelKz = 2;
        if (m_CBQuota.GetCheck() == 1) m_SelKz = 3;

        m_nachl.s.FETCH_REL = 1;
        if (m_CDatum.IsEmpty()) m_nachl.s.DATUM = 0;
        else if ((m_nachl.s.DATUM = AllgDatumEingKonv(m_CDatum, ALGF_FORM_DATUM_TTMMJJ)) < 0)
        {
            GotoDlgCtrl(GetDlgItem(IDC_EDIT_DATUM));
            return false;
        }
        if (m_CBDatum.GetCheck() == 0) m_nachl.s.POSNR = 0;
        else m_nachl.s.POSNR = m_nachl.s.DATUM;
        m_nachl.s.IDFNR = atol(m_CIdf);
        if (!m_CPzn.IsEmpty())
        {
            CARTAESEL code2;
            BeginWaitCursor();
            strcpy(code2.s.ARTICLE_CODE, m_CPzn);
            code2.Server(AatartSel_NoByCode);
            EndWaitCursor();
            m_nachl.s.ARTIKEL_NR = code2.s.ARTIKEL_NR;
            if (code2.s.ARTIKEL_NR == 0)
            {
                MsgBoxOK(IDP_PZN_UNBEKANNT);
                GotoDlgCtrl(GetDlgItem(IDC_EDIT_PZN));
                return false;
            }
        }
        else
        {
            m_nachl.s.ARTIKEL_NR = 0;
        }
        //m_nachl.s.ARTIKEL_NR = atol(m_CPzn);
        if (m_bDispo && m_bNachl) m_nachl.s.POSTYP = 0;
        //else if (m_bDispo) m_nachl.s.POSTYP = 2;
        else if (m_bDispo) m_nachl.s.POSTYP = 5;
        else m_nachl.s.POSTYP = 3;
        sNachlief.IDFNR = m_nachl.s.IDFNR;
        sNachlief.ARTIKEL_NR = m_nachl.s.ARTIKEL_NR;
        sNachlief.POSTYP = m_nachl.s.POSTYP;
        sNachlief.DATUM = m_nachl.s.DATUM;
        SetCurrentPage(1);
    }
    else
    {
        if (!GetFetchPositionOnPageSwitch(nKzUpDown, m_nachl.s.FETCH_REL))
        {
            return false;
        }
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        m_nachl.s.STATUS = m_SelKz;
        m_nachl.Server(AaauftSel_nachl);
        m_bCursorOpen = true;       //Datenbankcurser offen
        m_nachl.s.FETCH_REL = 1;    //normaler Fetch
        if (m_nachl.rc == SRV_SQLNOTFOUND)
        {
            if (m_bFirstDataset)  //kein Satz gefunden
            {
                CloseCursor();
                EndWaitCursor();
                MsgBoxOK(IDP_KEIN_NACHL_POS);
                return false;
            }
            SetItemCountOfCurrentPage(i); //Anzahl Positionen letzte Seite
            break;
        }
        m_bFirstDataset = false;
        //Ausgabe in die Listbox
        s[COL_KB] = kb.Next();
        s[COL_AART] = m_nachl.s.KDAUFTRAGART;
        AllgDatumLong2CharTTMMJJJJ(m_nachl.s.DATUM, Out1),
            s[COL_DATUM] = Out1;
        s[COL_IDF].Format("%d", m_nachl.s.IDFNR);
        s[COL_APO] = m_nachl.s.MATCHCODE;
        s[COL_AUFNR].Format("%d", m_nachl.s.KDAUFTRAGNR);
        s[COL_PZN].Format("%d", m_nachl.s.ARTIKEL_NR);
        s[COL_MENGE].Format("%d", m_nachl.s.MENGE);
        s[COL_BESTAND].Format("%d", m_nachl.s.BESTAND);
        s[COL_EINHEIT] = m_nachl.s.EINHEIT;
        s[COL_NAME] = m_nachl.s.ARTIKEL_NAME;
        code.s.ARTIKEL_NR = m_nachl.s.ARTIKEL_NR;
        code.Server(AatartSel_Preferred);
        AllgEntfSpaces(code.s.ARTICLE_CODE);
        s[COL_ARTCODE] = code.s.ARTICLE_CODE;
        s[COL_VZ].Format("%d", m_nachl.s.VERTRIEBSZENTRUMNR);
        if (m_nachl.s.POSTYP == 5) s[COL_TYP] = CResString::ex().getStrTblText(AETXT_KZ_RESERVE);
        else s[COL_TYP] = CResString::ex().getStrTblText(AETXT_KZ_NACHL);
        s[COL_POSNR].Format("%d", m_nachl.s.POSNR);
        s[COL_DATUMORG].Format("%d", m_nachl.s.DATUM);
        s[COL_BEMERKUNG] = m_nachl.s.BEMERKUNGEN;

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

void CDUpdNachl::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDUpdNachl::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    m_nachl.s.FETCH_REL = 0;
    BeginWaitCursor();
    m_nachl.s.STATUS = m_SelKz;
    m_nachl.Server(AaauftSel_nachl);
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDUpdNachl::OnOK()
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

void CDUpdNachl::SelectEintrag()
{
    CString CStr;

    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CDNachlAen dlgNachlAen;

        if (m_ListCtl.GetItemText(pos, COL_TYP) == CResString::ex().getStrTblText(AETXT_KZ_RESERVE))
            MsgBoxOK(IDP_NUR_NACHL);
        else
        {
            dlgNachlAen.m_CIdfNr = m_ListCtl.GetItemText(pos, COL_IDF);
            dlgNachlAen.m_CAuftrNr = m_ListCtl.GetItemText(pos, COL_AUFNR);
            dlgNachlAen.m_CPZN = m_ListCtl.GetItemText(pos, COL_PZN);
            dlgNachlAen.m_CArtCode = m_ListCtl.GetItemText(pos, COL_ARTCODE);
            dlgNachlAen.m_CMenge = m_ListCtl.GetItemText(pos, COL_MENGE);
            dlgNachlAen.m_CTyp = m_ListCtl.GetItemText(pos, COL_TYP);
            dlgNachlAen.m_Posnr = atol(m_ListCtl.GetItemText(pos, COL_POSNR));
            dlgNachlAen.m_Datum = atol(m_ListCtl.GetItemText(pos, COL_DATUMORG));
            dlgNachlAen.m_VzNr = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, COL_VZ)));
            dlgNachlAen.m_AArt = m_AArt;
            dlgNachlAen.DoModal();
            if (dlgNachlAen.m_bUpdated == TRUE)
            {
                m_ListCtl.SetItemText(pos, COL_MENGE, dlgNachlAen.m_CMenge);
            }
            else if (dlgNachlAen.m_bFolge == TRUE)
            {
                CStr.Format("%ld", dlgNachlAen.m_lFolgeNr);
                m_ListCtl.SetItemText(pos, COL_PZN, CStr);
            }
            else if (dlgNachlAen.m_bDeleted == TRUE)
            {
                CloseCursor();
                m_bDeleted = TRUE;
                GetPage();
                CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, pos);
            }
        }
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDUpdNachl::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    LRESULT res = CPageBrowser::OnHookNextPrev(lpMsg);
    if (res != 0L)
    {
        return res;
    }

    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        //Ausgabe der Kundeninformationen
        CKndInf dlgKndInf;
        long KndNr = 0;
        short VzNr = 0;
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString CStr = m_ListCtl.GetItemText(pos, COL_IDF);
            KndNr = atol(CStr);
            CStr = m_ListCtl.GetItemText(pos, COL_VZ);
            VzNr = static_cast<short>(atoi(CStr));
        }
        if (KndNr != 0) dlgKndInf.SetIdfNr(KndNr);
        if (VzNr == 0) dlgKndInf.SetKndVz(AeGetApp()->VzNr());
        else dlgKndInf.SetKndVz(VzNr);
        dlgKndInf.DoModal();
        return 1L;
    }
    if (((LPMSG)lpMsg)->wParam == VK_F11)
    {
        CDArtInf dlgArtInf;
        long ArtNr = 0;
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString CStr = m_ListCtl.GetItemText(pos, COL_PZN);
            ArtNr = atol (CStr);
        }
        if (ArtNr != 0) dlgArtInf.SetArtNr(ArtNr);
        dlgArtInf.DoModal();
        return 1L;
    }
    return 0L;
}

void CDUpdNachl::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDUpdNachl::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}

void CDUpdNachl::OnButtonKnd()
{
    CDKndWahl dlgKndWahl;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    CString CStr;
    CStr.Format("%ld", dlgKndWahl.GetKndNr());
    GetDlgItem(IDC_EDIT_IDF)->SetWindowText(CStr);
    CloseCursor();
    GetPage();
}

void CDUpdNachl::OnCheckDispo()
{
    if (m_CBDispo.GetCheck() == 0) m_CBNachl.SetCheck(1);
    else if (m_CBDispo.GetCheck() == 1) m_CBNachl.SetCheck(0);
}

void CDUpdNachl::OnCheckNachl()
{
    if (m_CBNachl.GetCheck() == 0) m_CBDispo.SetCheck(1);
    else if (m_CBNachl.GetCheck() == 1) m_CBDispo.SetCheck(0);
}

void CDUpdNachl::OnChangeEditDatum()
{
    AllgDatumKontr(&m_EditDatum, ALGF_FORM_DATUM_TTMMJJ);
}

void CDUpdNachl::OnChangeEditIdf()
{
    AllgWertKontr(&m_EditIdf, MAXIMUM_IDF);
}

void CDUpdNachl::OnButtonArtikel()
{
    CDArtDef dlgArtDef;
    if (dlgArtDef.DoModal() != IDOK)
    {
        return;
    }
    CString CStr;
    CStr.Format("%ld", dlgArtDef.GetArtNr());
    //etDlgItem(IDC_EDIT_PZN)->SetWindowText(CStr);
    GetDlgItem(IDC_EDIT_PZN)->SetWindowText(dlgArtDef.GetArticleCode());
    CloseCursor();
    GetPage();
}

void CDUpdNachl::OnButtonDruck()
{
    CNachlDruck dlgNachlDruck;
    dlgNachlDruck.DoModal();
}

void CDUpdNachl::OnCheckAh()
{
    if (m_CBAh.GetCheck() == 1)
    {
        m_CBNgf.SetCheck(0);
        m_CBQuota.SetCheck(0);
    }
}

void CDUpdNachl::OnCheckBestell()
{
    if (m_CBBestell.GetCheck() == 1)
    {
        m_CBNgf.SetCheck(0);
        m_CBQuota.SetCheck(0);
    }
}

void CDUpdNachl::OnCheckFolge()
{
    if (m_CBFolge.GetCheck() == 1)
    {
        m_CBNgf.SetCheck(0);
        m_CBQuota.SetCheck(0);
    }
}

void CDUpdNachl::OnCheckNgf()
{
    if (m_CBNgf.GetCheck() == 1)
    {
        m_CBAh.SetCheck(0);
        m_CBBestell.SetCheck(0);
        m_CBFolge.SetCheck(0);
        m_CBQuota.SetCheck(0);
    }
}

void CDUpdNachl::OnBnClickedCheckQuota()
{
    if (m_CBQuota.GetCheck() == 1)
    {
        m_CBAh.SetCheck(0);
        m_CBBestell.SetCheck(0);
        m_CBFolge.SetCheck(0);
        m_CBNgf.SetCheck(0);
    }
}

void CDUpdNachl::OnButtonDruckVb()
{
    CDRUCKPARA dr;
    BeginWaitCursor();
    dr.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    dr.Server(AadruckNachl_vbmoegl);
    EndWaitCursor();
}

void CDUpdNachl::OnButtonDruckList()
{
    if (m_bFirstDataset) return; //Listbox leer
    CDruckAuftrag druckAuftrag;
    CKNDAUSKU knd;
    CARTINF art;
    CARTAESEL code;
    CString liste;
    int satzzahl;
    char underline[111];
    char Out1[11];
    int nureinsatz = 0;
    memset(underline, '-', 110);
    underline[110] = '\0';
    BeginWaitCursor();
    liste.Format("%s", CResString::ex().getStrTblText(AETXT_NACHLIEFERUNG).GetString());
    druckAuftrag.AddKopfZeile(liste);
    liste = " ";
    druckAuftrag.AddKopfZeile(liste);
    liste.Format("%-2.2s %-10.10s %-8.8s %-5.5s %-7.7s %-25.20s %-15.12s %-13.13s %-9.9s %-30.30s",
        CResString::ex().getStrTblText(AETXT_A_ART).GetString(),
        CResString::ex().getStrTblText(AETXT_DATUM).GetString(),
        CResString::ex().getStrTblText(AETXT_AUF_NR).GetString(),
        CResString::ex().getStrTblText(AETXT_MENGE).GetString(),
        CResString::ex().getStrTblText(AETXT_IDF_NR).GetString(),
        CResString::ex().getStrTblText(AETXT_APOTHEKE).GetString(),
        CResString::ex().getStrTblText(AETXT_ORT).GetString(),
        CResString::ex().getStrTblText(AETXT_ARTICLE_CODE).GetString(),
        CResString::ex().getStrTblText(AETXT_EINHEIT).GetString(),
        CResString::ex().getStrTblText(AETXT_ARTIKELNAME).GetString() );
    druckAuftrag.AddKopfZeile(liste);
    druckAuftrag.AddKopfZeile(underline);
    druckAuftrag.AddFussZeile(" ");           // Leerzeile
    liste = "          ";
    liste += CResString::ex().getStrTblText(AETXT_SEITE);
    liste += "%d";
    druckAuftrag.AddFussZeile(liste);
    m_nachl.s.FETCH_REL = GetFetchStartPosition();
    if (m_nachl.s.FETCH_REL == 0) nureinsatz = 1;
    for (satzzahl = 0; ; satzzahl++)
    {
        m_nachl.s.STATUS = m_SelKz;
        if (nureinsatz == 0)
        {
            m_nachl.Server(AaauftSel_nachl);
            if (m_nachl.rc == SRV_SQLNOTFOUND)
                break;
        }
        knd.s.KUNDENNR = m_nachl.s.IDFNR;
        knd.s.VERTRIEBSZENTRUMNR = m_nachl.s.VERTRIEBSZENTRUMNR;
        /* später wieder korrekt mit kunden und vznr
        knd.s.KUNDENNR = m_nachl.s.KUNDENNR;
        knd.s.VERTRIEBSZENTRUMNR = m_nachl.s.VERTRIEBSZENTRUMNR;
        */
        knd.Server(AakundeSel_ausku);
        if (knd.rc != SRV_OK)
        {
            knd.s.NAMEAPO[0] = '\0';
            knd.s.ORT[0] = '\0';
        }
        //art.s.ARTIKEL_NR = m_nachl.s.ARTIKEL_NR;
        //art.Server(AatartInf_art_nr);
        //if (art.rc != SRV_OK)
        //{
        //    art.s.EINHEIT[0] = '\0';
        //    art.s.ARTIKEL_NAME[0] = '\0';
        //}
        code.s.ARTIKEL_NR = m_nachl.s.ARTIKEL_NR;
        code.Server( AatartSel_Preferred );
        AllgEntfSpaces(code.s.ARTICLE_CODE);
        AllgDatumLong2CharTTMMJJJJ(m_nachl.s.DATUM, Out1),
        liste.Format("%-10.10s %8d %5d %7d %-25.25s %-15.15s %-15.15s  %-9.9s %-30.30s",
            Out1,
            m_nachl.s.KDAUFTRAGNR,
            m_nachl.s.MENGE,
            m_nachl.s.IDFNR,
            knd.s.NAMEAPO,
            knd.s.ORT,
            code.s.ARTICLE_CODE,
            m_nachl.s.EINHEIT,
            m_nachl.s.ARTIKEL_NAME);
        m_bCursorOpen = true;       //Datenbankcurser offen
        m_nachl.s.FETCH_REL = 1;    //normaler Fetch
        druckAuftrag.AddPosZeile(liste);
        if (nureinsatz != 0) break;
    }
    if (nureinsatz == 0)
    {
        m_nachl.s.FETCH_REL = GetFetchPosition(satzzahl);
        if (m_nachl.s.FETCH_REL != 0) m_nachl.Server(AaauftSel_nachl);
    }
    EndWaitCursor();
    druckAuftrag.Druck(TRUE);
    druckAuftrag.DelAllData();
}

void CDUpdNachl::OnCbnSelchangeComboAufart()
{
    CString AArt;

    //Auftragsart bestimmen
    m_Cobox_Auf.GetLBText(m_Cobox_Auf.GetCurSel(),AArt);
    m_AArt = AArt.Left(2);
}

/////////////////////////////////////////////////////////////////////////////
// CDNachlAen dialog


CDNachlAen::CDNachlAen(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDNachlAen::IDD, pParent)
    , m_CArtCode(_T(""))
{
    m_CMenge = _T("");
    m_CAuftrNr = _T("");
    m_CIdfNr = _T("");
    m_CPZN = _T("");
    m_CTyp = _T("");
    m_CFolge = _T("");
    m_CFMenge = _T("");
}


void CDNachlAen::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_FOLGE, m_CBFolge);
    DDX_Control(pDX, IDCANCEL, m_CBCancel);
    DDX_Control(pDX, IDC_BUTTON_DEL, m_CBDel);
    DDX_Control(pDX, IDC_BUTTON_UPD, m_CBUpd);
    DDX_Control(pDX, IDC_EDIT_MENGE, m_EditMenge);
    DDX_Text(pDX, IDC_EDIT_MENGE, m_CMenge);
    DDX_Text(pDX, IDC_STATIC_AUFTR, m_CAuftrNr);
    DDX_Text(pDX, IDC_STATIC_IDF, m_CIdfNr);
    DDX_Text(pDX, IDC_STATIC_PZN, m_CPZN);
    DDX_Text(pDX, IDC_STATIC_TYP, m_CTyp);
    DDX_Text(pDX, IDC_STATIC_FOLGE, m_CFolge);
    DDX_Text(pDX, IDC_STATIC_MENGE, m_CFMenge);
    DDX_Text(pDX, IDC_STATIC_ARTCODE, m_CArtCode);
}


BEGIN_MESSAGE_MAP(CDNachlAen, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
    ON_BN_CLICKED(IDC_BUTTON_UPD, OnButtonUpd)
    ON_EN_CHANGE(IDC_EDIT_MENGE, OnChangeEditMenge)
    ON_BN_CLICKED(IDC_BUTTON_FOLGE, OnButtonFolge)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDNachlAen message handlers

void CDNachlAen::OnButtonDel()
{
    if (MsgBoxYesNo(IDP_SOLL_DEL_SATZ) == IDYES)
    {
        UpdateData();
        BeginWaitCursor();
        InsertNachliefProt(AENDTYP_DELETE);
        EndWaitCursor();
        m_bDeleted = TRUE;
        CDialogMultiLang::OnOK();
    }
}

void CDNachlAen::InsertNachliefProt(short sAendTyp)
{
    CNACHLPROT nachlprot;
    nachlprot.s.VERTRIEBSZENTRUMNR = (sAendTyp == AENDTYP_FOLGE) ? 0 : m_VzNr;
    nachlprot.s.DATUM = m_Datum;
    nachlprot.s.POSNR = m_Posnr;
    nachlprot.s.KDAUFTRAGNR = atol(m_CAuftrNr);
    nachlprot.s.POSTYP = (m_CTyp == CResString::ex().getStrTblText(AETXT_KZ_NACHL)) ? 3 : 2;
    nachlprot.s.NL_MENGE_AKTUELL = (sAendTyp == AENDTYP_DELETE) ? 0L : atol(m_CMenge);
    nachlprot.s.NL_MENGE_GELIEFER = (sAendTyp == AENDTYP_FOLGE) ? m_lFolgeNr : 0L;
    nachlprot.s.NL_MENGE_NEU = 0L;
    nachlprot.s.NL_MENGE_ALT = m_lMengeAlt;
    nachlprot.s.ARTIKEL_NR = atol(m_CPZN);
    nachlprot.s.AENDTYP = sAendTyp;
    nachlprot.s.UID = GetAeUser().GetUID();
    nachlprot.s.KDAUFTRAG_NR_NEU = 0L;
    nachlprot.s.IDFNR = atol(m_CIdfNr);
    nachlprot.Server(AaauftIns_prot);
}

void CDNachlAen::OnButtonUpd()
{
    UpdateData();
    if (atol(m_CMenge) > WARN_BUCH_MENGE)
    {
        MsgBoxOK(IDP_WARN_MENGE);
    }
    BeginWaitCursor();
    InsertNachliefProt(AENDTYP_MENGENAENDERUNG);
    EndWaitCursor();
    m_bUpdated = TRUE;
    CDialogMultiLang::OnOK();
}

void CDNachlAen::OnChangeEditMenge()
{
    AllgWertKontr(&m_EditMenge, MAXIMUM_BUCH_MENGE);
    SetDefID(IDC_BUTTON_UPD);
}

void CDNachlAen::OnCancel()
{
    CDialogMultiLang::OnCancel();
}

void CDNachlAen::OnButtonFolge()
{
    UpdateData();
    BeginWaitCursor();
    InsertNachliefProt(AENDTYP_FOLGE);
    EndWaitCursor();
    m_bFolge = TRUE;
    CDialogMultiLang::OnOK();
}

BOOL CDNachlAen::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CARTFOLGE artfolge;
    CString CStr;
    m_lMengeAlt = atol(m_CMenge);
    m_bUpdated = FALSE;
    m_bFolge = FALSE;
    m_bDeleted = FALSE;
    artfolge.s.ARTIKEL_NR = atol(m_CPZN);
    artfolge.Server(AatartSel_folge);
    if (artfolge.rc == SRV_OK)
    {
        m_CBFolge.EnableWindow( TRUE );
        m_lFolgeNr = artfolge.s.ARTIKEL_NR;
        CStr.Format("%ld", artfolge.s.ARTIKEL_NR);
        GetDlgItem(IDC_STATIC_FOLGE)->SetWindowText(CStr);
        CStr.Format("%ld", artfolge.s.BESTAND);
        GetDlgItem(IDC_STATIC_MENGE)->SetWindowText(CStr);
        GetDlgItem(IDC_STATIC_FOLGET)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_FOLGE)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_MENGET)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_MENGE)->ShowWindow(SW_SHOW);
    }
    else
    {
        m_CBFolge.EnableWindow(FALSE);
        m_lFolgeNr = 0;
        GetDlgItem(IDC_STATIC_FOLGET)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_FOLGE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MENGET)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MENGE)->ShowWindow(SW_HIDE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}
/////////////////////////////////////////////////////////////////////////////
// CNachlDruck dialog


CNachlDruck::CNachlDruck(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CNachlDruck::IDD, pParent)
{
}


void CNachlDruck::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNachlDruck, CDialogMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNachlDruck message handlers

BOOL CNachlDruck::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CheckRadioButton(IDC_RADIO_DATUM, IDC_RADIO_KUNDE, IDC_RADIO_DATUM);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CNachlDruck::OnOK()
{
    CDRUCKPARA dr;
    if (IsDlgButtonChecked(IDC_RADIO_DATUM))
    {
        dr.s.POSART[0] = '0';
    }
    else if (IsDlgButtonChecked(IDC_RADIO_KUNDE))
    {
        dr.s.POSART[0] = '1';
    }
    else
    {
        dr.s.POSART[0] = '2';
    }

    if (IsDlgButtonChecked(IDC_CHECK_AH))
    {
        dr.s.POSART[1] = IsDlgButtonChecked(IDC_CHECK_NF) ? '3' : '1';
    }
    else if (IsDlgButtonChecked(IDC_CHECK_NF))
    {
        dr.s.POSART[1] = '2';
    }
    else
    {
        dr.s.POSART[1] = '0';
    }
    BeginWaitCursor();
    dr.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    dr.Server(AadruckNachl);
    EndWaitCursor();

    CDialogMultiLang::OnOK();
}

void CDUpdNachl::OnCheckVz2()
{
    AeGetApp()->IsKundeHome = IsDlgButtonChecked(IDC_CHECK_VZ2) ? true : false;
}

void CDUpdNachl::OnBnClickedButtonDruckLief()
{
    CDRUCKPARA dr;
    UpdateData();
    dr.s.DATUM = m_CDatum.IsEmpty() ? 0 : AllgDatumEingKonv(m_CDatum, ALGF_FORM_DATUM_TTMMJJ);
    BeginWaitCursor();
    dr.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
    dr.Server(AadruckNachl_liefer);
    EndWaitCursor();
}
