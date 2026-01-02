// dartdef.cpp : implementation file
//

#include "stdafx.h"
#include "DArtDef.h"
#include "DArtInf.h"
#include "DHerstWahl.h"

//Definitionen Lieferbereitschaft
#define LIEFBER_OK   0
#define LIEFBER_NO   1
//Definitionen DE-Besorger
#define LIEFBER_DEGETTER 2

#define ZEILEN 11

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     8

static COLUMNS_TYPES Columns[] =
{
    0,  "",  30, LVCFMT_LEFT,
    1,  "",  80, LVCFMT_RIGHT,
    2,  "", 202, LVCFMT_LEFT,
    3,  "",  45, LVCFMT_CENTER,
    4,  "", 170, LVCFMT_LEFT,
    5,  "",   0, LVCFMT_RIGHT,
    6,  "",  60, LVCFMT_RIGHT,
    7,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDArtDef dialog


CDArtDef::CDArtDef(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDArtDef::IDD, pParent)
    , m_CHerstname(_T("")), CPageBrowser(ZEILEN)
{
    m_CDarr = _T("");
    m_CPackGr = _T("");
    m_CMatchCode = _T("");
    m_CArtNr = _T("");
    m_CZusatz = _T("");
    m_CNormpackung = _T("");
    m_CHerstnr = _T("");
    m_ArtikelNr = -1;   //ArtikelNr ungültig setzen
    m_bAufnahme = FALSE;
    m_sImport = 0;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_DAF);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_BESTAND);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_KK_CODE);
}

void CDArtDef::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_HERSTNR, m_EditHerstnr);
    DDX_Control(pDX, IDC_EDIT_NORMPACKUNG, m_EditNormpackung);
    DDX_Control(pDX, IDC_EDIT_ZUSATZ, m_EditZusatz);
    DDX_Control(pDX, IDC_EDIT_PZN, m_EditArtNr);
    DDX_Control(pDX, IDC_EDIT_NAME, m_EditMatchCode);
    DDX_Control(pDX, IDC_EDIT_EINHEIT, m_EditPackGr);
    DDX_Control(pDX, IDC_EDIT_DARR, m_EditDarr);
    DDX_Control(pDX, IDC_LISTCTRL_ART, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_DARR, m_CDarr);
    DDX_Text(pDX, IDC_EDIT_EINHEIT, m_CPackGr);
    DDX_Text(pDX, IDC_EDIT_NAME, m_CMatchCode);
    DDX_Text(pDX, IDC_EDIT_PZN, m_CArtNr);
    DDX_Text(pDX, IDC_EDIT_ZUSATZ, m_CZusatz);
    DDX_Text(pDX, IDC_EDIT_NORMPACKUNG, m_CNormpackung);
    DDX_Text(pDX, IDC_EDIT_HERSTNR, m_CHerstnr);
    DDV_MaxChars(pDX, m_CHerstnr, 17);
    DDX_Control(pDX, IDC_CHECK3, m_CBNurAktF11);
    DDX_Control(pDX, IDC_EDIT_HERSTNAME, m_EditHerstName);
    DDX_Text(pDX, IDC_EDIT_HERSTNAME, m_CHerstname);
}


BEGIN_MESSAGE_MAP(CDArtDef, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_DARR, OnChangeEditDarr)
    ON_EN_CHANGE(IDC_EDIT_EINHEIT, OnChangeEditEinheit)
    ON_EN_CHANGE(IDC_EDIT_NAME, OnChangeEditName)
    ON_EN_CHANGE(IDC_EDIT_PZN, OnChangeEditPzn)
    ON_EN_CHANGE(IDC_EDIT_ZUSATZ, OnChangeEditZusatz)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LISTCTRL_ART, OnKeydownListctrlArt)
    ON_WM_DESTROY()
    ON_EN_CHANGE(IDC_EDIT_NORMPACKUNG, OnChangeEditNormpackung)
    ON_EN_CHANGE(IDC_EDIT_HERSTNR, OnChangeEditHerstnr)
    ON_BN_CLICKED(IDC_BUTTON_COPY, OnButtonCopy)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_BN_CLICKED(IDC_CHECK3, OnBnClickedCheck3)
    ON_EN_CHANGE(IDC_EDIT_HERSTNAME, OnEnChangeEditHerstname)
    ON_BN_CLICKED(IDC_RADIO_IMPORT0, &CDArtDef::OnBnClickedRadioImport)
    ON_BN_CLICKED(IDC_RADIO_IMPORT1, &CDArtDef::OnBnClickedRadioImport)
    ON_BN_CLICKED(IDC_RADIO_IMPORT2, &CDArtDef::OnBnClickedRadioImport)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDArtDef message handlers

BOOL CDArtDef::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_OK);
    idResources.push_back(IDI_ICON_NO);
    idResources.push_back(IDI_ICON_DE_BESORGER);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    if (!m_bAufnahme) GetDlgItem(IDC_BUTTON_COPY)->ShowWindow(SW_HIDE);
    m_bAufnahme = FALSE;

    if (!m_CMatchCode.IsEmpty())
    {
        m_EditMatchCode.SetFocus();
        m_EditMatchCode.SetSel(0, -1, FALSE);
        m_EditMatchCode.SetSel(-1, 0, FALSE);       //Selektion aufheben
        return FALSE;
    }

    if (AeGetApp()->IsBG())
    {
        GetDlgItem(IDC_CHECK3)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_CHECK3)->EnableWindow(TRUE);
        GetDlgItem(IDC_EDIT_HERSTNAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_EDIT_HERSTNAME)->EnableWindow(TRUE);
        GetDlgItem(IDC_STATIC_HERSTNAME)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_HERSTNAME)->EnableWindow(TRUE);
        if (AeGetApp()->IsNurAktF11())
        {
            m_CBNurAktF11.SetCheck(TRUE);
        }
        else
        {
            m_CBNurAktF11.SetCheck(FALSE);
        }
        m_ListCtl.SetColumnWidth(2, 290);
        m_ListCtl.SetColumnWidth(7, 70);
    }
    if (AeGetApp()->IsDispoImportCst())
    {
        GetDlgItem(IDC_STATIC_FILTER)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_STATIC_FILTER)->EnableWindow(TRUE);
        GetDlgItem(IDC_RADIO_IMPORT2)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_RADIO_IMPORT2)->EnableWindow(TRUE);
        GetDlgItem(IDC_RADIO_IMPORT1)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_RADIO_IMPORT1)->EnableWindow(TRUE);
        GetDlgItem(IDC_RADIO_IMPORT0)->ShowWindow(SW_SHOW);
        GetDlgItem(IDC_RADIO_IMPORT0)->EnableWindow(TRUE);
        CheckRadioButton(IDC_RADIO_IMPORT0, IDC_RADIO_IMPORT2, IDC_RADIO_IMPORT0);
    }
    else
    {
        GetDlgItem(IDC_STATIC_FILTER)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_FILTER)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO_IMPORT2)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_RADIO_IMPORT2)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO_IMPORT1)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_RADIO_IMPORT1)->EnableWindow(FALSE);
        GetDlgItem(IDC_RADIO_IMPORT0)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_RADIO_IMPORT0)->EnableWindow(FALSE);
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDArtDef::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LISTCTRL_ART))
    {
        if (WaehleListPos() >= 0)
            return;
    }
    if (GetFocus() == GetDlgItem(IDOK))
    {
        if (WaehleListPos() >= 0)
            return;
    }

    UpdateData();
    if (m_CHerstnr.GetLength() > 0)
    {
        SelectHerstnr(m_CHerstnr);
        return;
    }
    if (m_CArtNr.GetLength() > 0)
    {
        SelectArtikelNr(m_CArtNr);
        return;
    }

    if (m_CHerstname.GetLength() == 0)
    {
        // Überprüfung der Matchcode-Eingabe
        if (m_CMatchCode.GetLength() < 3)
        {
            MsgBoxOK(IDP_MIND_DREI_ZEICHEN);
            m_EditMatchCode.SetFocus();
            m_EditMatchCode.SetSel(0, -1, FALSE);
            return;
        }
        if (m_CMatchCode.GetAt(0) == '%' || m_CMatchCode.GetAt(1) == '%' || m_CMatchCode.GetAt(2) == '%')
        {
            MsgBoxOK(IDP_NO_PROZENT);
            m_EditMatchCode.SetFocus();
            m_EditMatchCode.SetSel(0, -1, FALSE);
            return;
        }
        if (m_CMatchCode.GetAt(0) == '_' || m_CMatchCode.GetAt(1) == '_' || m_CMatchCode.GetAt(2) == '_')
        {
            MsgBoxOK(IDP_NO_UNDERLINE);
            m_EditMatchCode.SetFocus();
            m_EditMatchCode.SetSel(0, -1, FALSE);
            return;
        }
    }
    CloseCursor();
    if (m_CHerstname.GetLength() > 0)
    {
        CDHerstWahl hw;
        hw.SetHerstName(m_CHerstname);
        if (hw.DoModal() == IDCANCEL) return;
        m_HerstNr = hw.GetHerstNr();
        m_nFunktion = AatartSel_herstname;
    }
    else if (atol(m_CPackGr) == 0)
    {
        m_nFunktion = AatartSel_mc;
    }
    else
    {
        m_nFunktion = AatartSel_mc_pkgr;
    }
    GetPage();
}

void CDArtDef::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CARTSEL artsel;
    artsel.s.FETCH_REL = 0;
    BeginWaitCursor();
    artsel.Server( m_nFunktion );
    EndWaitCursor();
    m_ListCtl.DeleteAllItems();
    ResetCursor();
    Reset();
}

bool CDArtDef::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    static CARTSEL artsel;

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        artsel.s.IMPORTARTICLE = m_sImport;

        strcpy(artsel.s.ARTIKEL_MC, m_CMatchCode);
        artsel.s.PACKGROESSE = atol(m_CPackGr);
        AllgStrCopy(artsel.s.ARTIKEL_NAME,m_CZusatz     ,L_ARTAESEL_ARTIKEL_NAME);
        AllgStrCopy(artsel.s.DARREICHFORM,m_CDarr       ,L_ARTAESEL_DARREICHFORM);
        AllgStrCopy(artsel.s.NORMPACKUNG,m_CNormpackung ,L_ARTAESEL_NORMPACKUNG);
        artsel.s.HERSTELLER_NR = m_HerstNr;

        artsel.s.BESTAND = AeGetApp()->IsNurAktF11() ? 1 : 0;
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, artsel.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    m_kb.Reset();
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        artsel.Server(m_nFunktion);
        m_bCursorOpen = true;       //Datenbankcurser offen
        artsel.s.FETCH_REL = 1;          //normaler Fetch
        if (artsel.rc == SRV_SQLNOTFOUND)
        {
            if (m_bFirstDataset)      //kein Satz gefunden
            {
                MsgBoxOK(IDP_KEIN_ARTIKEL);
                CloseCursor();
                EndWaitCursor();
                return false;
            }
            SetItemCountOfCurrentPage(i); //Anzahl Artikel letzte Seite
            break;
        }
        m_bFirstDataset = false;
        //Ausgabe in die Listbox
        if (!FillList(artsel))
            return false;

    } //Ende der for()-Schleife
    EndWaitCursor();
    CListCtrlHelper::SetFocusSelectedFocused(m_ListCtl, 0);
    return true;
}

long CDArtDef::WaehleListPos()
{
    long n = SelListPos();
    if (n != -1)
    {
        m_ArtikelNr = n;
        CloseCursor();
        CDialogMultiLang::OnOK();
        return 0;
    }
    return -1;
}

long CDArtDef::SelListPos()
{
    CString str;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        char s[81];
        sprintf(s,"%ld",pos);
        m_cArticleCode = m_ListCtl.GetItemText(pos, 4);
        m_ArtikelName = m_ListCtl.GetItemText(pos, 2);
        str = m_ListCtl.GetItemText(pos, 5);
        return atol(str);
    }
    return -1;
}

void CDArtDef::SelectArtikelNr(CString ArtNr)
{
    CARTSEL artsel;
    CARTAESEL artaesel;
    for (int i = 0; i < ArtNr.GetLength(); i++)
    {
        if (ArtNr.GetAt(i) == '0')
        {
            ArtNr = ArtNr.Right(ArtNr.GetLength() - 1);
            --i;
        }
        else
        {
            break;
        }
    }
    strcpy(artaesel.s.ARTICLE_CODE, ArtNr);
    BeginWaitCursor();
    artaesel.Server(AatartSel_NoByCode);
    EndWaitCursor();
    if (artaesel.rc != SRV_OK)
    {
        m_EditArtNr.SetFocus();
        m_EditArtNr.SetSel(0, -1, FALSE);
        return;
    }
    m_ArtikelNr = artaesel.s.ARTIKEL_NR;
    m_cArticleCode = ArtNr;

    artsel.s.ARTIKEL_NR = m_ArtikelNr;
    BeginWaitCursor();
    artsel.s.IMPORTARTICLE = m_sImport;
    artsel.Server(AatartSel_art_nr);
    EndWaitCursor();
    m_ListCtl.DeleteAllItems();
    if (artsel.rc == SRV_OK)
    {
        m_ArtikelName = artsel.s.ARTIKEL_NAME;
        m_ArtikelNr = artsel.s.ARTIKEL_NR;
        CloseCursor();
        CDialogMultiLang::OnOK();
        return;
    }
    m_EditArtNr.SetFocus();
    m_EditArtNr.SetSel(0, -1, FALSE);
}

void CDArtDef::SelectHerstnr(CString Herstnr)
{
    CARTSEL artsel;
    bool bErsterSatz = TRUE;
    strncpy(artsel.s.ARTIKEL_NAME, Herstnr, LS_ARTLIEFER_ARTIKEL_NR_BLIEFER); // Artikelname wird missbraucht
    BeginWaitCursor();
    m_ListCtl.DeleteAllItems();
    m_kb.Reset();
    for (;;)
    {
        artsel.Server(AatartFetch_artnrlief);
        if (artsel.rc == SRV_SQLNOTFOUND)
        {
            if (bErsterSatz == TRUE)        //kein Satz gefunden
            {
                MsgBoxOK(IDP_KEIN_ARTIKEL);
                m_EditHerstnr.SetFocus();
                m_EditHerstnr.SetSel(0, -1, FALSE);
                return;
            }
            break;
        }
        if (artsel.rc == SRV_OK)
        {
            bErsterSatz = FALSE;
            //Ausgabe in die Listbox
            if (!FillList(artsel))
                return;
        }
    }
    EndWaitCursor();
    CListCtrlHelper::SetFocusSelectedFocused(m_ListCtl, 0);
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDArtDef::OnHookFkt( WPARAM /*wParam*/, LPARAM lpMsg )
{
    LRESULT res = CPageBrowser::OnHookNextPrev(lpMsg);
    if (res != 0L)
    {
        return res;
    }

    if (((LPMSG)lpMsg)->wParam == VK_F11)
    {
        if (GetFocus() == GetDlgItem(IDC_LISTCTRL_ART))
        {
            CDArtInf dlgArtInf(SelListPos());
            dlgArtInf.DoModal();
            return 1L;                                  //Message wird nicht weitergeleitet
        }
        else if (GetFocus() == GetDlgItem(IDC_EDIT_PZN))
        {
            m_EditArtNr.GetWindowText(m_CArtNr);
            for (int i = 0; i < m_CArtNr.GetLength(); i++)
            {
                if (m_CArtNr.GetAt(i) == '0')
                {
                    m_CArtNr = m_CArtNr.Right(m_CArtNr.GetLength() - 1);
                    i--;
                }
                else
                {
                    break;
                }
            }
            if (m_CArtNr.GetLength() > 0)
            {
                CARTAESEL code;
                strcpy(code.s.ARTICLE_CODE, m_CArtNr);
                code.Server(AatartSel_NoByCode);
                if (code.rc != SRV_OK)
                {
                    m_EditArtNr.SetFocus();
                    m_EditArtNr.SetSel(0, -1, FALSE);
                    return 1L;
                }
                CDArtInf dlgArtInf(code.s.ARTIKEL_NR);
                dlgArtInf.DoModal();
                m_EditArtNr.SetFocus();
                m_EditArtNr.SetSel(0, -1, FALSE);
                return 1L;                              //Message wird nicht weitergeleitet
            }
        }
    }

    return 0L;
}


void CDArtDef::OnKeydownListctrlArt(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (CLetterMan::InRange(pLVKeyDow->wVKey, m_ListCtl.GetItemCount()))
    {
        if ((GetKeyState(VK_SHIFT) & 0x8000) == 0x8000)
        {
            CDArtInf dlgArtInf(SelListPos());
            dlgArtInf.DoModal();
        }
        //else
        //{
        //    //WaehleListPos();
        //}
        //return;
    }
    //if ((GetKeyState(VK_SHIFT) & 0x80) == 0x80)
    //{
    //    ;  //Artikelinformation implementieren
    //}
}

void CDArtDef::OnChangeEditDarr()
{
    DropListSelect();
    AllgLaengeKontr(&m_EditDarr, L_ARTSEL_DARREICHFORM,AeGetApp()->Modus());

}

void CDArtDef::OnChangeEditEinheit()
{
    DropListSelect();
    AllgLaengeKontr(&m_EditPackGr, L_ARTSEL_EINHEIT,AeGetApp()->Modus());

}

void CDArtDef::OnChangeEditName()
{
    DropListSelect();
    CString str;
    char s[2];

    m_EditMatchCode.GetWindowText( str );               //Einheit lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (str.GetLength() == 1 && isdigit((int)chN))
    {
        str.GetBufferSetLength(str.GetLength() - 1);    //letztes Zeichen löschen
        m_EditMatchCode.SetWindowText(str);             //String zurückschreiben
        s[0] = chN, s[1] = '\0';
        m_EditArtNr.SetWindowText(s);                   //erster Buchstabe im Feld Bezeichner
        m_EditArtNr.SetFocus();
        m_EditArtNr.SetSel(0, -1, FALSE);
        m_EditArtNr.SetSel(-1, 0, FALSE);               //Selektion aufheben
        return;
    }                                                   //Kein Ende der Eingabe
    AllgLaengeKontr(&m_EditMatchCode, L_ARTSEL_ARTIKEL_MC, AeGetApp()->Modus());
}

void CDArtDef::OnChangeEditPzn()
{
    DropListSelect();

    CString str;

    m_EditArtNr.GetWindowText( str );
    if (str.IsEmpty())                                  //Feld ist leer
        return;
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (isdigit((int)chN))
    {
        if (str.GetLength() > 25)
        {
            m_EditArtNr.SetWindowText("");
        }
        return;
    }
    else if (chN == '-')
    {
        m_EditArtNr.SetWindowText("");
        m_EditArtNr.SetFocus();
        m_EditArtNr.SetSel(0, -1, FALSE);
    }
    else
    {
        m_EditArtNr.SetWindowText("");
        m_EditMatchCode.SetWindowText(str);
        m_EditMatchCode.SetFocus();
        m_EditMatchCode.SetSel(0, -1, FALSE);
        m_EditMatchCode.SetSel(-1, 0, FALSE);       //Selektion aufheben
    }
}

void CDArtDef::OnChangeEditZusatz()
{
    DropListSelect();
    AllgLaengeKontr(&m_EditZusatz, L_ARTSEL_ARTIKEL_NAME, AeGetApp()->Modus());
}

void CDArtDef::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDArtDef::OnChangeEditNormpackung()
{
    DropListSelect();
    CString str;

    m_EditNormpackung.GetWindowText(str);               //Einheit lesen
    if (str.IsEmpty() || str == "N1" || str == "N2" || str == "N3")
        return;                                         //Feld ist leer
    if (str == "1")
    {
        m_EditNormpackung.SetWindowText("N1");
        m_EditNormpackung.SetFocus();
        m_EditNormpackung.SetSel(0, -1, FALSE);
        m_EditNormpackung.SetSel(-1, 0, FALSE);         //Selektion aufheben
        return;
    }
    if (str == "2")
    {
        m_EditNormpackung.SetWindowText("N2");
        m_EditNormpackung.SetFocus();
        m_EditNormpackung.SetSel(0, -1, FALSE);
        m_EditNormpackung.SetSel(-1, 0, FALSE);         //Selektion aufheben
        return;
    }
    if (str == "3")
    {
        m_EditNormpackung.SetWindowText("N3");
        m_EditNormpackung.SetFocus();
        m_EditNormpackung.SetSel(0, -1, FALSE);
        m_EditNormpackung.SetSel(-1, 0, FALSE);         //Selektion aufheben
        return;
    }
    if (str.IsEmpty() || str == "N1" || str == "N2" || str == "N3")
        ;
    else
    {
        MsgBoxOK(IDP_UNG_EING_NORMP);
        m_EditNormpackung.SetWindowText("");
    }
}

void CDArtDef::DropListSelect()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
        CListCtrlHelper::SetItemStateClear(m_ListCtl, pos);
}

void CDArtDef::OnChangeEditHerstnr()
{
    DropListSelect();
}

BOOL CDArtDef::FillList(CARTSEL artsel)
{
    char str[81];
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    AllgEntfSpaces(artsel.s.EINHEIT);
    s[1] = artsel.s.EINHEIT;
    AllgEntfSpaces(artsel.s.ARTIKEL_NAME);
    if (AeGetApp()->IsBG())
    {
        ppString name;
        ppString kkcode;
        m_infbg.SetArtikel_nr(artsel.s.ARTIKEL_NR);
        m_infbg.SelArtInfBG();
        s[2] = m_infbg.GetArtikel_langname(name);
        s[7] = m_infbg.GetHealthfundcode(kkcode);
    }
    else
    {
        s[2] = artsel.s.ARTIKEL_NAME;
    }
    AllgEntfSpaces(artsel.s.DARREICHFORM);
    s[3] = artsel.s.DARREICHFORM;
    CARTAESEL code;
    code.s.ARTIKEL_NR = artsel.s.ARTIKEL_NR;
    BeginWaitCursor();
    code.Server(AatartSel_Preferred);
    AllgEntfSpaces(code.s.ARTICLE_CODE);
    EndWaitCursor();
    s[4] = code.s.ARTICLE_CODE;
    sprintf(str, "%ld", artsel.s.ARTIKEL_NR);
    s[5] = str;
    if (artsel.s.BESTAND < 0)
    {
        s[6].Empty();
    }
    else
    {
        sprintf(str, "%ld", artsel.s.BESTAND);
        s[6] = str;
    }

    s[0] = m_kb.Next();
    int likz;
    if (artsel.s.BESTAND > 0) likz = LIEFBER_OK;
    else likz = LIEFBER_NO;

    int index;
    if (!CListCtrlHelper::GetAppendImageItem(m_ListCtl, NUM_COLUMNS, s, likz, index))
    {
        EndWaitCursor();
        return FALSE;
    }
    if (artsel.s.IMPORTARTICLE == 1)
    {
        CListCtrlHelper::SetImageItem(m_ListCtl, index, 2, LIEFBER_DEGETTER);
    }
    return TRUE;
}

void CDArtDef::OnButtonCopy()
{
    CString str;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_cArticleCode = m_ListCtl.GetItemText(pos, 4);
        str = m_ListCtl.GetItemText(pos, 5);
        m_ArtikelNr = atol(str);
        CloseCursor();
        m_bAufnahme = TRUE;
        CDialogMultiLang::OnOK();
    }
}

void CDArtDef::OnBnClickedCheck3()
{
    AeGetApp()->IsNurAktF11 = IsDlgButtonChecked(IDC_CHECK3) ? true : false;
}

void CDArtDef::OnEnChangeEditHerstname()
{
    DropListSelect();
    AllgLaengeKontr(&m_EditHerstName, L_ARTSEL_HERSTELLER_CODE,AeGetApp()->Modus());
}

void CDArtDef::OnBnClickedRadioImport()
{
    if (GetCheckedRadioButton(IDC_RADIO_IMPORT1, IDC_RADIO_IMPORT2) == IDC_RADIO_IMPORT0)
        m_sImport = 0;
    else if (GetCheckedRadioButton(IDC_RADIO_IMPORT1, IDC_RADIO_IMPORT2) == IDC_RADIO_IMPORT1)
        m_sImport = 1;
    else
        m_sImport = 2;
}
