// DInfoListe.cpp : implementation file
//

#include "stdafx.h"
#include "koplist.h"
#include <lieferinfo.h>
#include "DInfoListe.h"
#include "allg.h"
#include <artsel.h>

#define ANZ_CHAR_COPY   6

void DelTabs(CKOPLIST* koplist);
void ReplaceTabs(int len, char* feld);

/////////////////////////////////////////////////////////////////////////////
// CDInfoListe dialog


void CDInfoListe::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_INFO, m_StaticInfo);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Control(pDX, IDC_PZN, m_PZN);
    DDX_Control(pDX, IDC_DISPO, m_DISPO);
    DDX_Control(pDX, IDC_BEMERK, m_BEMERK);
    DDX_Control(pDX, IDC_INPUT, m_INPUT);
    DDX_Control(pDX, IDC_COPY, m_COPY);
    DDX_Control(pDX, IDC_SUCH, m_SUCH);
    DDX_Control(pDX, IDC_TEXT1, m_TEXT1);
    DDX_Control(pDX, IDC_ZURUECK, m_ZURUECK);
    DDX_Control(pDX, IDC_WEITER, m_WEITER);
    DDX_Control(pDX, IDC_HERSTINFO, m_HERSTINFO);
    DDX_Control(pDX, IDC_CHK_HERST_BLOCKED, m_CHK_HERST_BLOCKED);
    DDX_Control(pDX, IDC_CHK_HERST_QUALIFIED, m_CHK_HERST_QUALIFIED);
    DDX_Text(pDX, IDC_SUCH, m_such);
    DDV_MaxChars(pDX, m_such, 26);
    DDX_Text(pDX, IDC_TEXT1, m_text1);
    DDX_Text(pDX, IDC_INPUT, m_input);
    DDX_Text(pDX, IDC_BEMERK, m_bemerk);
    DDX_Text(pDX, IDC_DISPO, m_dispo);
    DDX_Text(pDX, IDC_PZN, m_pzn);
    DDX_Text(pDX, IDC_STATIC_INFO, m_CInfo);
    DDX_Text(pDX, IDC_EDIT_CODE, m_ArtCode);
    DDX_Control(pDX, IDC_EDIT_CODE, m_edit_ArtCode);
}

BEGIN_MESSAGE_MAP(CDInfoListe, CDialogMultiLang)
    ON_BN_CLICKED(IDC_WEITER, OnWeiter)
    ON_BN_CLICKED(IDC_ZURUECK, OnZurueck)
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_COPY, OnCopy)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDInfoListe message handlers

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     7

static COLUMNS_TYPES Columns[] =
{
    0,  "",  30, LVCFMT_LEFT,
    1,  "", 245, LVCFMT_LEFT,
    2,  "", 245, LVCFMT_LEFT,
    3,  "", 245, LVCFMT_LEFT,
    4,  "", 245, LVCFMT_LEFT,
    5,  "",  60, LVCFMT_LEFT,
    6,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

CDInfoListe::CDInfoListe(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDInfoListe::IDD, pParent)
    , m_ArtCode(_T(""))
{
    m_such = "";
    m_text1 = "";
    m_input = "";
    m_bemerk = "";
    m_dispo = "";
    m_pzn = "";
    m_CInfo = _T("");
    m_ArtNr = 0;
    m_Name = "";
    m_bAufnahme = FALSE;
    m_bIsVkMenu  = false;

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_BEZEICHNUNG);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_ALTERNATIVNAME);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_DISPO_HINWEIS);
    Columns[4].Columns = CResString::ex().getStrTblText(IDS_BEMERK);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_PZN);
}

void CDInfoListe::OnOK()
{
    if (!UpdateData())
        return;

    seite = 0;

    BeginWaitCursor();

    CKOPLIST koplist;

    if (declare_switch)
    {
        koplist.s.FETCH_REL = 0;
        koplist.Server(IftselSel_tellistt);
    }
    declare_switch = true;
    koplist.s.FETCH_REL = 1;

    CString list = m_such;
    list.Trim();

    if (AeGetApp()->IsFirstLetter())
    {
        sprintf(koplist.s.BEZEICHNUNG, "%s%%", list.GetString());    //lesen eingegebenen Suchbegriff ab Stelle 1
    }
    else
    {
        sprintf(koplist.s.BEZEICHNUNG, "%%%s%%", list.GetString());  //lesen eingegebenen Suchbegriff komplett im Feld
    }
    m_INPUT.SetWindowText(list);
    m_COPY.EnableWindow(FALSE);
    m_ZURUECK.EnableWindow(FALSE);
    m_WEITER.EnableWindow(TRUE);

    m_List1.DeleteAllItems();
    while (m_List1.GetItemCount() == 0)
    {
        FillList(koplist);

        // Truncate the search string by one letter and try again
        if (m_List1.GetItemCount() == 0)
        {
            if (list.GetLength() == 1) break;
            list.Truncate(list.GetLength() - 1);
            sprintf(koplist.s.BEZEICHNUNG, "%s%%", list.GetString());  //lesen ab eingegebenem suchbegriff
            koplist.s.FETCH_REL = 0;
            koplist.Server(IftselSel_tellistt);
            koplist.s.FETCH_REL = 1;
        }
    }

    int nItemCount = m_List1.GetItemCount();
    if (nItemCount < 10) m_WEITER.EnableWindow(FALSE);

    EndWaitCursor();

    MarkListPos(0);
    ReadFromList(0);
    if (nItemCount > 0)
    {
        if (m_bAufnahme) m_COPY.EnableWindow(TRUE);
        GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    }
    else
    {
        GotoDlgCtrl(GetDlgItem(IDC_SUCH));
    }
}

void CDInfoListe::FillList(CKOPLIST& koplist)
{
    m_List1.DeleteAllItems();

    CLetterMan kb;
    for (int i = 0; i < 10; i++)
    {
        koplist.Server(IftselSel_tellistt);
        koplist.s.FETCH_REL = 1;
        if (koplist.rc == SRV_OK)
        {
            DelTabs(&koplist);
            AllgEntfSpaces(koplist.s.BEZEICHNUNG);
            AllgEntfSpaces(koplist.s.ALTERNATIV_NAME);
            AllgEntfSpaces(koplist.s.DISPO_HINWEIS);
            AllgEntfSpaces(koplist.s.BEMERKUNG);
            AddPosToList(kb.Next(),
                koplist.s.BEZEICHNUNG,
                koplist.s.ALTERNATIV_NAME,
                koplist.s.DISPO_HINWEIS,
                koplist.s.BEMERKUNG,
                koplist.s.PZN);
        }
        else
        {
            break;
        }
    }
}

void CDInfoListe::OnWeiter()
{
    // TODO: Add your control notification handler code here
    if (!UpdateData())
        return;

    ++seite;

    BeginWaitCursor();

    CKOPLIST koplist;
    koplist.s.FETCH_REL = 1;

    FillList(koplist);

    if (m_List1.GetItemCount() < 10) m_WEITER.EnableWindow(FALSE);
    m_ZURUECK.EnableWindow(TRUE);

    EndWaitCursor();

    MarkListPos(0);
    ReadFromList(0);
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
}

void CDInfoListe::OnZurueck()
{
    if (!UpdateData())
        return;

    --seite;

    BeginWaitCursor();

    int anz = m_List1.GetItemCount();
    anz = anz + 10 - 1;
    anz *= -1;

    CKOPLIST koplist;
    koplist.s.FETCH_REL = anz;

    FillList(koplist);

    if (m_List1.GetItemCount() < 10) m_WEITER.EnableWindow(FALSE);
    if (seite <= 0)
        m_ZURUECK.EnableWindow(FALSE);
    else
        m_ZURUECK.EnableWindow(TRUE);

    EndWaitCursor();

    m_WEITER.EnableWindow(TRUE);
    MarkListPos(0);
    ReadFromList(0);
    GotoDlgCtrl (GetDlgItem(IDC_LIST1));
}

LRESULT CDInfoListe::OnHookFkt(WPARAM /*wParam*/,LPARAM lpMsg)
{
    int key = (int)((LPMSG)lpMsg)->wParam;

    if (key == VK_NEXT)
    {
        if (m_WEITER.IsWindowEnabled() == TRUE)
            OnWeiter();
        return 1L;   // message nicht weiterleiten
    }
    if (key == VK_PRIOR)
    {
        if (m_ZURUECK.IsWindowEnabled() == TRUE)
            OnZurueck();
        return 1L;   // message nicht weiterleiten
    }
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        int pos;

        if (key == VK_LBUTTON)
        {
            pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
            MarkListPos(pos);
            PosWechseln();
            return 1L;   // message nicht weiterleiten
        }
        if (key == VK_UP)
        {
            pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
            --pos;
            MarkListPos(pos);
            PosWechseln();
            return 1L;   // message nicht weiterleiten
        }
        if (key == VK_DOWN)
        {
            pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
            ++pos;
            MarkListPos(pos);
            PosWechseln();
            return 1L;   // message nicht weiterleiten
        }

        if (key == KEY_ALT)
        {
            m_bIsVkMenu = true;
            return 0L;
        }

        if (!m_bIsVkMenu && CLetterMan::InRange(static_cast<WORD>(key), m_List1.GetItemCount()))
        {
            pos = key - AeGetApp()->Letter_A();
            MarkListPos(pos);
            PosWechseln();
            return 1L;   // message nicht weiterleiten
        }
        if (m_bIsVkMenu)
            m_bIsVkMenu = false;

        if (key == ' ')
            GotoDlgCtrl(GetDlgItem(IDC_SUCH));
    }
    if (m_COPY.IsWindowEnabled())
    {
        if (key == VK_F8)
        {
            OnCopy();
            return 1L;   // message nicht weiterleiten
        }
    }
    return 0;
}

void CDInfoListe::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    KillTimer(1001);
    CKOPLIST koplist;
    if (declare_switch)
    {
        BeginWaitCursor();
        koplist.s.FETCH_REL = 0;
        koplist.Server(IftselSel_tellistt);
        EndWaitCursor();
    }
}

BOOL CDInfoListe::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }

    declare_switch = false;

    m_List1.DeleteAllItems();            //loesche listbox

    m_ZURUECK.EnableWindow(FALSE);
    m_WEITER.EnableWindow(FALSE);
    m_COPY.EnableWindow(FALSE);
    m_edit_ArtCode.SetReadOnly(TRUE);
    m_HERSTINFO.SetReadOnly(TRUE);
    m_INPUT.SetReadOnly(TRUE);
    // default: don't show supplier/manufacturer info
    // show info only if a supplier/manufacturer has been selected
    ShowHerstInfo(FALSE);

    CKOPLIST koplist;
    koplist.s.PZN = -1;
    m_CInfo += "\0";
    koplist.Server(IftselSel_info);
    if (koplist.rc == SRV_OK)
    {
        AllgEntfSpaces(koplist.s.BEMERKUNG);
        m_CInfo += "     ***Zentral: ";
        m_CInfo += koplist.s.BEMERKUNG;
    }

    koplist.s.PZN = AeGetApp()->VzNr() * (-1);
    koplist.Server(IftselSel_info);
    if (koplist.rc == SRV_OK)
    {
        AllgEntfSpaces(koplist.s.BEMERKUNG);
        m_CInfo += "     ***Lokal: ";
        m_CInfo += koplist.s.BEMERKUNG;
    }

    UpdateData(FALSE);
    if (!m_such.IsEmpty())
    {
        OnOK();
    }

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDInfoListe::OnCopy()
{
    CString CStr;
    m_edit_ArtCode.GetWindowText(CStr);
    m_ArtNr = atol(CStr);
    m_TEXT1.GetWindowText(m_Name);

    CDialogMultiLang::OnOK();
}

void DelTabs(CKOPLIST* koplist)
{
    ReplaceTabs(L_KOPLIST_BEZEICHNUNG, koplist->s.BEZEICHNUNG);
    ReplaceTabs(L_KOPLIST_ALTERNATIV_NAME, koplist->s.ALTERNATIV_NAME);
    ReplaceTabs(L_KOPLIST_DISPO_HINWEIS, koplist->s.DISPO_HINWEIS);
    ReplaceTabs(L_KOPLIST_BEMERKUNG, koplist->s.BEMERKUNG);
}

void ReplaceTabs(int len, char* feld)
{
    for (int i = 0; i < len || feld[i] != '\0'; i++)
    {
        if (feld[i] == '\t') feld[i] = ' ';
    }
}

void CDInfoListe::MarkListPos(int pos)
{
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_List1, pos);
}

void CDInfoListe::AddPosToList(char* kb,
                               CString Name,
                               CString AltName,
                               CString Dispo,
                               CString Bemerk,
                               long PZN)
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    s[0] = kb;
    s[1] = Name;
    s[2] = AltName;
    s[3] = Dispo;
    s[4] = Bemerk;
    if (Name.Left(2) == "HH")
    {
        s[5].Format("%d", PZN);
    }
    else
    {
        if (PZN > 0)
        {
            CARTAESEL code;
            code.s.ARTIKEL_NR = PZN;
            code.Server(AatartSel_Preferred);
            AllgEntfSpaces(code.s.ARTICLE_CODE);
            s[5] = code.s.ARTICLE_CODE;
        }
        else
        {
            s[5].Empty();
        }
    }
    s[6].Format("%ld", PZN);

    CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s);
}

void CDInfoListe::ReadFromList(int pos)
{
    m_TEXT1.SetWindowText(m_List1.GetItemText(pos, 2));
    m_DISPO.SetWindowText(m_List1.GetItemText(pos, 3));
    m_BEMERK.SetWindowText(m_List1.GetItemText(pos, 4));
    m_PZN.SetWindowText(m_List1.GetItemText(pos, 6));
    m_edit_ArtCode.SetWindowText(m_List1.GetItemText(pos, 5));
    if (m_such.Left(2) == "HH")
    {
        GetDlgItem(IDC_STATIC_PZN)->SetWindowTextA(CResString::ex().getStrTblText(AETXT_HERSTEL) + ":");
        ShowHerstInfo(TRUE);

        // interpret the entered number as BESLA_NR and search
        // for the corresponding supplier data
        int besla_nr = atoi(m_List1.GetItemText(pos, 6));
        CString strHerstInfo;
        CString strHerstBlocked = "";
        CString strHerstQualified = "";
        if (besla_nr > 0)
        {
            CLIEFERINFO lieferinfo;

            lieferinfo.s.FETCH_REL = 0;
            lieferinfo.s.BESLA_NR = besla_nr;
            lieferinfo.Server(LieferselSel_info);
            if (lieferinfo.rc == 0)
            {
                AllgEntfFirstSpaces(lieferinfo.s.BESLA_NAME);
                AllgEntfFirstSpaces(lieferinfo.s.PLZ_STRASSE);
                AllgEntfFirstSpaces(lieferinfo.s.ORT);
                AllgEntfFirstSpaces(lieferinfo.s.E_MAIL);
                AllgEntfSpaces(lieferinfo.s.BESLA_NAME);
                AllgEntfSpaces(lieferinfo.s.PLZ_STRASSE);
                AllgEntfSpaces(lieferinfo.s.ORT);
                AllgEntfSpaces(lieferinfo.s.E_MAIL);

                strHerstInfo =
                      lieferinfo.s.BESLA_NAME + CString("\r\n")
                    + lieferinfo.s.PLZ_STRASSE + CString(" ") + lieferinfo.s.ORT + CString("\r\n")
                    + lieferinfo.s.E_MAIL;
                strHerstBlocked = lieferinfo.s.EINKAUFSVERBOT;
                strHerstQualified = "1";
                if (strcmp(lieferinfo.s.ARZNEIMITTELBEZUG, "K") == 0 || strcmp(lieferinfo.s.ARZNEIMITTELBEZUG, "N") == 0)
                {
                    strHerstQualified = "0";
                }
            }
            else
            {
                strHerstInfo = "<keine Daten für Bestell-Lieferanten-Nr. " + m_List1.GetItemText(pos, 6) + ">";
            }
        }

        m_HERSTINFO.SetWindowText(strHerstInfo);
        m_CHK_HERST_BLOCKED.SetCheck(strHerstBlocked == "1" ? BST_CHECKED : BST_UNCHECKED);
        m_CHK_HERST_QUALIFIED.SetCheck(strHerstQualified == "1" ? BST_CHECKED : BST_UNCHECKED);
    }
    else
    {
        GetDlgItem(IDC_STATIC_PZN)->SetWindowTextA(CResString::ex().getStrTblText(AETXT_PZN) + ":");
        ShowHerstInfo(FALSE);
    }
}

void CDInfoListe::PosWechseln()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        return;
    }
    ReadFromList(pos);
}

void CDInfoListe::OnClickList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    MarkListPos(pos);
    PosWechseln();
    *pResult = 0L;
}

void CDInfoListe::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    if (!m_Timer)
    {
        SetTimer(1001, 180000, NULL);
        m_Timer = TRUE;
    }

    // Do not call CDialogMultiLang::OnPaint() for painting messages
}

void CDInfoListe::OnTimer(UINT nIDEvent)
{
    if (nIDEvent == 1001)
    {
        CString str;
        CKOPLIST koplist;
        koplist.s.PZN = -1;
        koplist.Server(IftselSel_info);
        if (koplist.rc == SRV_OK)
        {
            AllgEntfSpaces(koplist.s.BEMERKUNG);
            str += CResString::ex().getStrTblText(IDS_CENTRAL);
            str += koplist.s.BEMERKUNG;
        }
        koplist.s.PZN = AeGetApp()->VzNr() * (-1);
        koplist.Server(IftselSel_info);
        if (koplist.rc == SRV_OK)
        {
            AllgEntfSpaces(koplist.s.BEMERKUNG);
            str += CResString::ex().getStrTblText(IDS_LOCAL);
            str += koplist.s.BEMERKUNG;
        }
        m_StaticInfo.SetWindowText((LPCTSTR)str);
    }

    CDialogMultiLang::OnTimer(nIDEvent);
}

void CDInfoListe::ShowHerstInfo(BOOL fShow)
{
    GetDlgItem(IDC_STATIC_HERSTINFO)->ShowWindow(fShow);
    GetDlgItem(IDC_STATIC_HERSTINFO2)->ShowWindow(fShow);
    m_HERSTINFO.ShowWindow(fShow);
    m_CHK_HERST_BLOCKED.ShowWindow(fShow);
    m_CHK_HERST_QUALIFIED.ShowWindow(fShow);
}
