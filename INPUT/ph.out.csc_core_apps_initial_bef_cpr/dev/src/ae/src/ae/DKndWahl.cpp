// dkndwahl.cpp : implementation file
//

#include "stdafx.h"
#include "DKndWahl.h"
#include <kndsel.h>
#include <customer.h>
#include "DKndInf.h"
#include "MainFrm.h"

#define ZEILEN 10

//Definitionen Buchen
#define GESPERRT_NO     0
#define GESPERRT_YES    1
#define AKTIV           2
#define NO_AKTIV        3

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     12

static COLUMNS_TYPES Columns[] =
{
    0,  "",  30, LVCFMT_LEFT,
    1,  "",  55, LVCFMT_RIGHT,
    2,  "", 170, LVCFMT_LEFT,
    3,  "", 180, LVCFMT_LEFT,
    4,  "", 180, LVCFMT_LEFT,
    5,  "",  50, LVCFMT_CENTER,
    6,  "", 120, LVCFMT_LEFT,
    7,  "", 140, LVCFMT_LEFT,
    8,  "",  30, LVCFMT_LEFT,
    9,  "",  20, LVCFMT_CENTER,
    10, "",  20, LVCFMT_LEFT,
    11, "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDKndWahl dialog


CDKndWahl::CDKndWahl(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDKndWahl::IDD, pParent)
    , m_CName(_T("")), CPageBrowser(ZEILEN)
{
    m_apo = _T("");
    m_inhaber = _T("");
    m_ort = _T("");
    m_CKndNr = _T("");
    m_KndNr = -1;           // Kundennummer für ungültig erklären
    m_KndVz = 0;
    m_strHeader = "";
    m_bActivateAeGesperrt = false;
    m_bDeActivateKundeHome = false;

    SetOffAeGesperrt();     // nur nicht gesperrte Kunden
    SetDisableAeGesperrt(); // Checkbutton muß enabled werden
    m_IsKundeHome = true;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_MATCHCODE);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_INHABER);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_KURZWAHL);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_STRASSE);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_VZ);
    Columns[9].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[10].Columns = CResString::ex().getStrTblText(AETXT_ORIGINAL);
    Columns[11].Columns = CResString::ex().getStrTblText(AETXT_KUNDEN_NR);
}

void CDKndWahl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_GESPERRT, m_CBGesperrt);
    DDX_Control(pDX, IDC_CHECK_HOME, m_CBHome);
    DDX_Control(pDX, IDC_EDIT_ORT, m_cOrt);
    DDX_Control(pDX, IDC_EDIT_APOTHEKE, m_cMatchCode);
    DDX_Control(pDX, IDC_EDIT_INHABER, m_cInhaber);
    DDX_Control(pDX, IDC_EDIT_KD_NR, m_cKndNr);
    DDX_Control(pDX, IDC_LISTCTRL_KUNDE, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_APOTHEKE, m_apo);
    DDX_Text(pDX, IDC_EDIT_INHABER, m_inhaber);
    DDX_Text(pDX, IDC_EDIT_ORT, m_ort);
    DDX_Text(pDX, IDC_EDIT_KD_NR, m_CKndNr);
    DDX_Control(pDX, IDC_EDIT_NAME, m_EditName);
    DDX_Text(pDX, IDC_EDIT_NAME, m_CName);
}

BEGIN_MESSAGE_MAP(CDKndWahl, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_EN_CHANGE(IDC_EDIT_APOTHEKE, OnChangeEditApotheke)
    ON_EN_CHANGE(IDC_EDIT_INHABER, OnChangeEditInhaber)
    ON_EN_CHANGE(IDC_EDIT_KD_NR, OnChangeEditKdNr)
    ON_EN_CHANGE(IDC_EDIT_ORT, OnChangeEditOrt)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LISTCTRL_KUNDE, OnKeydownListctrlKunde)
    ON_NOTIFY(NM_DBLCLK, IDC_LISTCTRL_KUNDE, OnDblclkListctrlKunde)
    ON_NOTIFY(NM_RCLICK, IDC_LISTCTRL_KUNDE, OnRclickListctrlKunde)
    ON_BN_CLICKED(IDC_CHECK_HOME, OnCheckHome)
    ON_BN_CLICKED(IDC_CHECK_GESPERRT, OnCheckGesperrt)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_EN_CHANGE(IDC_EDIT_NAME, OnEnChangeEditName)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDKndWahl message handlers

BOOL CDKndWahl::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    if (!m_strHeader.empty())
        SetWindowText(m_strHeader);

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_NOACHTUNG);
    idResources.push_back(IDI_ICON_NO);
    idResources.push_back(IDI_ICON_AKTIV);
    idResources.push_back(IDI_ICON_NO_AKTIV);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    AllgSetColumnWidthUser(m_ListCtl, "CDKndWahl", KEY_PATH, 11);


    // CG: The following block was added by the ToolTips component.
    {
        // Create the ToolTip control.
        m_tooltip.Create(this);
        m_tooltip.Activate(TRUE);
    }


    if (m_bDeActivateKundeHome)
    {
        m_CBHome.ShowWindow(SW_HIDE);
    }
    else
    {
        m_IsKundeHome = AeGetApp()->IsKundeHome();
        if (m_IsKundeHome)
        {
            m_CBHome.SetCheck(TRUE);
        }
        if (!GetAeUser().IsMehrVz())
        {
            AeGetApp()->IsKundeHome = true;
            m_CBHome.SetCheck(TRUE);
            m_CBHome.EnableWindow(FALSE);
        }
    }

    if (!m_EnableAeGesperrt)
    {
        m_CBGesperrt.ShowWindow(SW_HIDE);
        SetOffAeGesperrt();     // nur nicht gesperrte Kunden
    }
    else if (m_EnableAeGesperrt && m_bActivateAeGesperrt)
    {
        m_CBGesperrt.SetCheck(TRUE);
        SetOnAeGesperrt();
    }

    if (AeGetApp()->IsMatchCode())
    {
        GetDlgItem( IDC_EDIT_NAME )->SetFocus();
        return FALSE;
    }
    if (AeGetApp()->IsKundeIDF())
    {
        GetDlgItem( IDC_EDIT_KD_NR )->SetFocus();
        return FALSE;
    }
    if (!m_apo.IsEmpty())
    {
        m_cMatchCode.SetFocus();
        m_cMatchCode.SetSel(0, -1, FALSE);
        m_cMatchCode.SetSel(-1, 0, FALSE);      //Selektion aufheben
        return FALSE;
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDKndWahl::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    LRESULT res = CPageBrowser::OnHookNextPrev(lpMsg);
    if (res != 0L)
    {
        return res;
    }

    if (((LPMSG)lpMsg)->wParam == VK_F12)
    {
        OnInfKunde();
        return 1L;      //Message wird nicht weitergeleitet
    }
    return 0L;
}

void CDKndWahl::OnKeydownListctrlKunde(NMHDR* pNMHDR, LRESULT* pResult)
{
    int pos;
    OnKeydownList(pNMHDR, pResult, m_ListCtl, pos);

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (CLetterMan::InRange(pLVKeyDow->wVKey, m_ListCtl.GetItemCount()))
    {
        if ((GetKeyState(VK_SHIFT) & 0x8000) == 0x8000)
        {
            CString str2 = m_ListCtl.GetItemText(pos, 1);
            CKndInf dlgKndInf;
            dlgKndInf.SetIdfNr(atol(str2));
            dlgKndInf.DoModal();
        }
        //else
        //{
        //    //SelectKunde();
        //}
        //return;
    }
    //if ((GetKeyState(VK_SHIFT) & 0x80) == 0x80)
    //{
    //    ;  //Artikelinformation implementieren
    //}
}

void CDKndWahl::OnOK()
{

    if (GetFocus() == GetDlgItem(IDC_LISTCTRL_KUNDE))
    {
        SelectKunde();
        return;
    }
    if (GetFocus() == GetDlgItem(IDOK))
    {
        if (SelectKunde() == 0)
            return;
    }

    UpdateData();
    if (m_CName.GetLength() > 0)
    {
        m_nFunktion = AakundeSel_name;
    }
    else if (m_CKndNr.GetLength() > 0)
    {
        m_nFunktion = AakundeSel_idf;
    }
    else
    {
        m_nFunktion = AakundeSel_mc;
    }
    CloseCursor();
    GetPage();
}

void CDKndWahl::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CKNDSEL kndsel;
    kndsel.s.FETCH_REL = 0;
    BeginWaitCursor();
    kndsel.Server(m_nFunktion);
    EndWaitCursor();
    ResetCursor();
    Reset();
}

bool CDKndWahl::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    static CKNDSEL kndsel;
    char str[81] = { 0 };
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    long lActTime = 0;
    char cWoTag[3] = { 0 };
    short sWeekday = 0;
    CCUSTROUT routing;
    int iImage;

    if (AeGetApp()->IsDayNight())
    {
        CTM zeit;
        const char* pGerDay[] = { "SO", "MO", "DI", "MI", "DO", "FR", "SA" };
        zeit.Server(AafilGetdatetime);
        strcpy(cWoTag, pGerDay[zeit.s.WTAG]);
        sWeekday = static_cast<short>(zeit.s.WTAG);
        lActTime = zeit.s.ZEIT / 100;
    }

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        kndsel.s.REGIONNR = AeGetApp()->VzNr();
        kndsel.s.VERTRIEBSZENTRUMNR = AeGetApp()->IsKundeHome() ? AeGetApp()->VzNr() : 0;
        if (AeGetApp()->IsKundeHome() != m_IsKundeHome)
        {
            m_IsKundeHome = AeGetApp()->IsKundeHome();
        }
        strcpy(kndsel.s.MATCHCODE, m_apo);
        strcpy(kndsel.s.NAMEINHABER, m_inhaber);
        strcpy(kndsel.s.NAMEAPO, m_CName);
        strcpy(kndsel.s.ORT, m_ort);
        if (m_CKndNr.GetLength() > 0)
        {
            kndsel.s.IDFNR = atol(m_CKndNr);
        }
        kndsel.s.SKDKUNDEAEGESPERRT[0] = m_AeGesperrt[0];
        kndsel.s.SKDKUNDEAEGESPERRT[1] = '\0';
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, kndsel.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < ZEILEN; i++)
    {
        kndsel.Server(m_nFunktion);
        m_bCursorOpen = true;       //Datenbankcurser offen
        kndsel.s.FETCH_REL = 1;          //normaler Fetch
        if (kndsel.rc == SRV_SQLNOTFOUND)
        {
            if (m_bFirstDataset)     //kein Satz gefunden
            {
                MsgBoxOK(IDP_KEIN_KUNDE);
                CloseCursor();
                EndWaitCursor();
                return false;
            }
            SetItemCountOfCurrentPage(i); //Anzahl Artikel letzte Seite
            break;
        }
        m_bFirstDataset = false;
        //Ausgabe in die Listbox
        s[0] = kb.Next();
        sprintf(str, "%d", kndsel.s.IDFNR);
        s[1] = str;
        AllgEntfSpaces(kndsel.s.NAMEAPO);
        s[2] = kndsel.s.NAMEAPO;
        AllgEntfSpaces(kndsel.s.MATCHCODE);
        s[3] = kndsel.s.MATCHCODE;
        AllgEntfSpaces(kndsel.s.NAMEINHABER);
        s[4] = kndsel.s.NAMEINHABER;
        AllgEntfSpaces(kndsel.s.TELKURZWAHL);
        s[5] = kndsel.s.TELKURZWAHL;
        AllgEntfSpaces(kndsel.s.ORT);
        s[6] = kndsel.s.ORT;
        AllgEntfSpaces(kndsel.s.STRASSE);
        s[7] = kndsel.s.STRASSE;
        s[8].Format("%d", kndsel.s.VERTRIEBSZENTRUMNR);
        s[9] = kb.Current();
        if (kndsel.s.ORIGINALFILIALNR == 0)
        {
            sprintf(str,"%d", kndsel.s.FILIALNR);
            s[10]=str;
        }
        else
        {
            sprintf(str,"%d", kndsel.s.ORIGINALFILIALNR);
            s[10]=str;
        }
        s[11].Format("%d", kndsel.s.KUNDENNR);
        if (kndsel.s.SKDKUNDEAEGESPERRT[0] == '0')
        {
            if (AeGetApp()->IsDayNight())
            {
                routing.CloseCursor();
                if (kndsel.s.ORIGINALFILIALNR == 0)
                {
                    routing.SetBranchno(kndsel.s.VERTRIEBSZENTRUMNR);
                }
                else
                {
                    routing.SetBranchno(kndsel.s.ORIGINALFILIALNR);
                }
                routing.SetCustomerno(kndsel.s.KUNDENNR);
                routing.SetTimefrom(lActTime);
                routing.SetTimeto(lActTime);
                routing.SetDayofweek(cWoTag);
                routing.SetWeekday(sWeekday);
                if (!routing.SelActRouting())
                {
                    if (kndsel.s.ORIGINALFILIALNR == 0)
                    {
                        iImage = NO_AKTIV;
                    }
                    else
                    {
                        if (kndsel.s.ORIGINALFILIALNR == kndsel.s.VERTRIEBSZENTRUMNR)
                        {
                            iImage = NO_AKTIV;
                        }
                        else if (routing.GetDestbranchno() == kndsel.s.VERTRIEBSZENTRUMNR)
                        {
                            iImage = AKTIV;
                        }
                        else
                        {
                            iImage = NO_AKTIV;
                        }
                    }
                }
                else
                {
                    if (kndsel.s.ORIGINALFILIALNR == 0)
                    {
                        iImage = AKTIV;
                    }
                    else
                    {
                        if (kndsel.s.ORIGINALFILIALNR == kndsel.s.VERTRIEBSZENTRUMNR)
                            iImage = AKTIV;
                        else
                            iImage = NO_AKTIV;
                    }
                }
            }
            else
            {
                iImage = GESPERRT_NO;
            }
        }
        else
        {
            iImage = GESPERRT_YES;
        }

        if (!CListCtrlHelper::AppendImageItem(m_ListCtl, NUM_COLUMNS, s, iImage))
        {
            EndWaitCursor();
            return false;
        }
    } //Ende der for()-Schleife
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LISTCTRL_KUNDE));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    if (m_KndVz != 0)
    {
        OnOK();
    }
    return true;
}

void CDKndWahl::OnDestroy()
{
    AllgWriteColumnWidthUser(m_ListCtl, "CDKndWahl", KEY_PATH, 11);
    CDialogMultiLang::OnDestroy();

    CloseCursor();
}

void CDKndWahl::OnChangeEditApotheke()
{
    DropListSelect();
    m_KndVz = 0;
    CString str;
    char s[2];

    m_cMatchCode.GetWindowText(str);                    //Einheit lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (str.GetLength() == 1 && isdigit((int)chN))
    {
        str.GetBufferSetLength(str.GetLength() - 1);    //letztes Zeichen löschen
        m_cMatchCode.SetWindowText(str);                //String zurückschreiben
        s[0] = chN, s[1] = '\0';
        m_cKndNr.SetWindowText(s);                      //erster Buchstabe im Feld Bezeichner
        m_cKndNr.SetFocus();
        m_cKndNr.SetSel(0, -1, FALSE);
        m_cKndNr.SetSel(-1, 0, FALSE);                  //Selektion aufheben
        return;
    }                                                   //Kein Ende der Eingabe
    m_cKndNr.SetWindowText("");
    AllgLaengeKontr(&m_cMatchCode, L_KNDSEL_MATCHCODE, AeGetApp()->Modus());
}

void CDKndWahl::OnChangeEditInhaber()
{
    DropListSelect();
    m_KndVz = 0;
    AllgLaengeKontr(&m_cInhaber, L_KNDSEL_NAMEINHABER,AeGetApp()->Modus());
}

void CDKndWahl::OnChangeEditKdNr()
{
    DropListSelect();
    m_KndVz = 0;
    CString str;
    m_cKndNr.GetWindowText(str);                        //Kundennr lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (!isdigit((int)chN))
    {
        if (AeGetApp()->IsMatchCode())
        {
            m_EditName.SetWindowText(str);              //String zurückschreiben
            m_EditName.SetFocus();
            m_EditName.SetSel(0, -1, FALSE);
            m_EditName.SetSel(-1, 0, FALSE);            //Selektion aufheben
            m_cKndNr.SetWindowText("");
            return;
        }
        else
        {
            m_cMatchCode.SetWindowText(str);            //String zurückschreiben
            m_cMatchCode.SetFocus();
            m_cMatchCode.SetSel(0, -1, FALSE);
            m_cMatchCode.SetSel(-1, 0, FALSE);          //Selektion aufheben
            m_cKndNr.SetWindowText("");
            return;
        }
    }                                                   //Kein Ende der Eingabe
    AllgWertKontr(&m_cKndNr, MAXIMUM_IDF);
}

void CDKndWahl::OnChangeEditOrt()
{
    DropListSelect();
    m_KndVz = 0;
    AllgLaengeKontr(&m_cOrt, L_KNDSEL_ORT,AeGetApp()->Modus());
}

void CDKndWahl::OnDblclkListctrlKunde(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectKunde();
    *pResult = 0L;
}

int CDKndWahl::SelectKunde()
{
    m_bAktiv = true;

    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        char s[81];
        sprintf(s, "%ld", pos);
        CString str = m_ListCtl.GetItemText(pos, 1);
        m_IdfNr = atol(str);
        str = m_ListCtl.GetItemText(pos, 11);
        m_KndNr = atol(str);
        str = m_ListCtl.GetItemText(pos, 10);
        m_KndOrgFiliale = static_cast<short>(atoi(str));
        str = m_ListCtl.GetItemText(pos, 8);
        m_KndFiliale = m_KndVz = static_cast<short>(atoi(str));
        int nImage = CListCtrlHelper::GetImage(m_ListCtl, pos);
        if (nImage == GESPERRT_YES)
        {
            m_KzAeGesperrt = true;
        }
        else if (nImage == AKTIV)
        {
            m_KzAeGesperrt = false;
            m_bAktiv = true;
        }
        else if (nImage == NO_AKTIV)
        {
            m_KzAeGesperrt = false;
            m_bAktiv = false;
        }
        else
        {
            m_KzAeGesperrt = false;
        }
        m_CApotheke = m_ListCtl.GetItemText(pos, 2);
        m_COrt = m_ListCtl.GetItemText(pos, 6);
        CDialogMultiLang::OnOK();
        return 0;
    }
    return -1;
}

void CDKndWahl::OnRclickListctrlKunde(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
/* //NASE
    CMenu menu;
    menu.LoadMenu(IDR_MENU_KD_WAHL);
    menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, 30, 50, this);
*/
    *pResult = 0L;
}

BOOL CDKndWahl::PreTranslateMessage(MSG* pMsg)
{
    // CG: The following block was added by the ToolTips component.
    {
        // Let the ToolTip process this message.
        m_tooltip.RelayEvent(pMsg);

        return CDialogMultiLang::PreTranslateMessage(pMsg);
    }
}
void CDKndWahl::OnInfKunde( )
{
    CString str;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CKndInf dlgKndInf;
        str = m_ListCtl.GetItemText(pos, 1);
        dlgKndInf.SetIdfNr(atol(str));
        str = m_ListCtl.GetItemText(pos, 8);
        dlgKndInf.SetKndVz(static_cast<short>(atoi(str)));
        dlgKndInf.DoModal();
    }
}

void CDKndWahl::OnCheckHome()
{
    AeGetApp()->IsKundeHome = IsDlgButtonChecked(IDC_CHECK_HOME) ? true : false;
}

void CDKndWahl::OnCheckGesperrt()
{
    if (IsDlgButtonChecked(IDC_CHECK_GESPERRT))
        SetOnAeGesperrt();      // auch gesperrte Kunden
    else
        SetOffAeGesperrt();     // nur nicht gesperrte Kunden

}

void CDKndWahl::DropListSelect()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
        CListCtrlHelper::SetItemStateClear(m_ListCtl, pos);
}

void CDKndWahl::OnEnChangeEditName()
{
    DropListSelect();
    m_KndVz = 0;
    CString str;
    char s[2];

    m_EditName.GetWindowText(str);                      //Einheit lesen
    if (str.IsEmpty())
        return;                                         //Feld ist leer
    char chN = str[str.GetLength() - 1];                //letztes Zeichen lesen
    if (str.GetLength() == 1 && isdigit((int)chN))
    {
        str.GetBufferSetLength(str.GetLength() - 1);    //letztes Zeichen löschen
        m_EditName.SetWindowText(str);                  //String zurückschreiben
        s[0] = chN, s[1] = '\0';
        m_cKndNr.SetWindowText(s);                      //erster Buchstabe im Feld Bezeichner
        m_cKndNr.SetFocus();
        m_cKndNr.SetSel(0, -1, FALSE);
        m_cKndNr.SetSel(-1, 0, FALSE);                  //Selektion aufheben
        return;
    }                                                   //Kein Ende der Eingabe
    m_cKndNr.SetWindowText("");
    AllgLaengeKontr(&m_EditName, L_KNDSEL_NAMEINHABER, AeGetApp()->Modus());
}
