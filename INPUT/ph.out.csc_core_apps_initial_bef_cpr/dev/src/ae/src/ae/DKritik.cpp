// DKritik.cpp : implementation file
//

#include "stdafx.h"
#include "DKritik.h"
#include "DKndWahl.h"
#include "DKritikErf.h"
#include "DKritikUpd.h"
#include <kritiksatz.h>
#include "CallbackStatusManager.h"

#define ZEILEN 12    /* *** Anzahl der Zeilen der Listbox *** */

//Definition der Tabellenbreite und der Ueberschriften
#define NUM_CB_KB          0
#define NUM_CB_KRITIKNR    1
#define NUM_CB_DATUM       2
#define NUM_CB_TIME        3
#define NUM_CB_APO         4
#define NUM_CB_ORT         5
#define NUM_CB_PARTNER     6
#define NUM_CB_TITEL       7
#define NUM_CB_KDNR        8
#define NUM_CB_UID         9
#define NUM_CB_VZNR        10
#define NUM_CB_BEZEICHNUNG 11
#define NUM_CB_REFERENCE   12
#define NUM_CB_POSNR       13
#define NUM_CB_STATUS      14
#define NUM_COLUMNS        15

static COLUMNS_TYPES Columns[] =
{
   NUM_CB_KB         ,  "",   30, LVCFMT_LEFT,
   NUM_CB_KRITIKNR   ,  " ",   0, LVCFMT_CENTER, //Beschwerdenummer verstecken (DB-Schlüssel)
   NUM_CB_DATUM      ,  "",   60, LVCFMT_CENTER,
   NUM_CB_TIME       ,  "",   60, LVCFMT_CENTER,
   NUM_CB_APO        ,  "",  140, LVCFMT_LEFT,
   NUM_CB_ORT        ,  "",   80, LVCFMT_LEFT,
   NUM_CB_PARTNER    ,  "",   80, LVCFMT_LEFT,
   NUM_CB_TITEL      ,  "",  120, LVCFMT_LEFT,
   NUM_CB_KDNR       ,  " ",   0, LVCFMT_CENTER, //Kundennummer verstecken (DB-Schlüssel)
   NUM_CB_UID        ,  " ",   0, LVCFMT_CENTER, //Anwender verstecken (für Folge-Maske)
   NUM_CB_VZNR       ,  " ",   0, LVCFMT_CENTER, //VZ-Nr
   NUM_CB_BEZEICHNUNG,  "",    0, LVCFMT_LEFT,
   NUM_CB_REFERENCE  ,  "",  203, LVCFMT_LEFT,
   NUM_CB_POSNR      ,  " ",   0, LVCFMT_CENTER,
   NUM_CB_STATUS     ,  "",   69, LVCFMT_LEFT,
    -1, "",    0, 0
};

/////////////////////////////////////////////////////////////////////////////
// CDKritik dialog


CDKritik::CDKritik(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDKritik::IDD, pParent), CPageBrowser(ZEILEN)
{
    m_CIdf = _T("");
    m_CTitel = _T("");
    m_CTime_Bis = 0;
    m_CTime_Von = 0;
    m_bVZ = FALSE;
    m_Funktion = 0;
    m_IsKundeHome = true;

    Columns[NUM_CB_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[NUM_CB_DATUM].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[NUM_CB_TIME].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[NUM_CB_APO].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKE);
    Columns[NUM_CB_ORT].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[NUM_CB_PARTNER].Columns = CResString::ex().getStrTblText(AETXT_RRPARTNER);
    Columns[NUM_CB_TITEL].Columns = CResString::ex().getStrTblText(AETXT_RUECKRUFGRUND);
    if (AeGetApp()->IsCBStatusUsed())
    {
        Columns[NUM_CB_REFERENCE].Columns = CResString::ex().getStrTblText(AETXT_REFERENCE);
        Columns[NUM_CB_STATUS].Columns = CResString::ex().getStrTblText(AETXT_STATUS_LANG);
    }
    else
    {
        Columns[NUM_CB_REFERENCE].Width = 0;
        Columns[NUM_CB_STATUS].Width = 0;
        Columns[NUM_CB_APO].Width = 250;
        Columns[NUM_CB_PARTNER].Width = 150;
        Columns[NUM_CB_TITEL].Width = 212;
    }
}

void CDKritik::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_VZ, m_CB_Vz);
    DDX_Control(pDX, IDC_DATETIMEPICKER_VON, m_DT_Von);
    DDX_Control(pDX, IDC_DATETIMEPICKER_BIS, m_DT_Bis);
    DDX_Control(pDX, IDC_EDIT_TITEL, m_EditTitel);
    DDX_Control(pDX, IDC_EDIT_IDF, m_EditIdf);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_IDF, m_CIdf);
    DDX_Text(pDX, IDC_EDIT_TITEL, m_CTitel);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIS, m_CTime_Bis);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_VON, m_CTime_Von);
    DDX_Check(pDX, IDC_CHECK_VZ, m_bVZ);
    DDX_Control(pDX, IDC_COMBO_STATUS, m_ComboStatus);
    DDX_Control(pDX, IDC_COMBO_DIVISION, m_ComboDivision);
    DDX_Control(pDX, IDC_COMBO_REASON, m_ComboReason);
}


BEGIN_MESSAGE_MAP(CDKritik, CDialogMultiLang)
    ON_WM_DESTROY()
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
    ON_EN_CHANGE(IDC_EDIT_IDF, OnChangeEditIdf)
    ON_EN_CHANGE(IDC_EDIT_TITEL, OnChangeEditTitel)
    ON_BN_CLICKED(IDC_BUTTON_KND, OnButtonKnd)
    ON_BN_CLICKED(IDC_BUTTON_NEU, OnButtonNeu)
    ON_BN_CLICKED(IDC_CHECK_VZ, OnCheckVz)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
    ON_CBN_SELCHANGE(IDC_COMBO_DIVISION, OnCbnSelchangeComboDivision)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDKritik message handlers

BOOL CDKritik::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // create the small icon image list
    std::vector<UINT> idResources;
    idResources.push_back(IDI_ICON_WEISS);
    idResources.push_back(IDI_ICON_LOW_CRITICAL);
    idResources.push_back(IDI_ICON_WARN);
    CListCtrlHelper::CreateAndSetImageList(m_ListCtl, m_ImageSmall, idResources);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    CTime datum = CTimeFromDateLongMinTime(zeit.s.DATUM);
    m_DT_Bis.SetTime(&datum);


    m_IsKundeHome = AeGetApp()->IsKundeHome();

    if (m_IsKundeHome)
    {
        m_CB_Vz.SetCheck(TRUE);

    }
    if (!GetAeUser().IsMehrVz())
    {
        AeGetApp()->IsKundeHome = true;
        m_CB_Vz.SetCheck(TRUE);
        m_CB_Vz.EnableWindow(FALSE);
    }

    // Init comboboxes
    if (AeGetApp()->IsCBStatusUsed())
    {
        m_ComboStatus.AddString(_T("")); // don't filter status in this case
        CCallbackStatusManager callbackStatusManager;
        callbackStatusManager.FillCombobox(m_ComboStatus);
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

    if (m_CIdf.GetLength())
    {
        GetPage();
        GetDlgItem(IDC_BUTTON_NEU)->SetFocus();
        return FALSE;
    }
    return TRUE;  // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}

bool CDKritik::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    //Variablen
    CKRITIK kritik;
    char str[128];
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        UpdateData();
        kritik.s.REGIONNR = AeGetApp()->VzNr();
        AllgStrCopy(kritik.s.TITEL, m_CTitel, L_KRITIK_TITEL);
        kritik.s.IDFNR = atol(m_CIdf);
        kritik.s.DATUM = (m_CTime_Von.GetYear() * 10000 + m_CTime_Von.GetMonth() * 100 + m_CTime_Von.GetDay());
        kritik.s.ZEIT = (m_CTime_Bis.GetYear() * 10000 + m_CTime_Bis.GetMonth() * 100 + m_CTime_Bis.GetDay());
        if (kritik.s.IDFNR)
        {
            m_Funktion = AakritikSel_kritik_idf;
            if (AeGetApp()->IsKundeHome())
                kritik.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
        }
        else
        {
            m_Funktion = AakritikSel_kritik;
            if (AeGetApp()->IsKundeHome())
                kritik.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
            else kritik.s.VERTRIEBSZENTRUMNR = 0;
        }
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, kritik.s.FETCH_REL))
    {
        return false;
    }

    m_ListCtl.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    int i = 0;
    while(i < ZEILEN)
    {
        kritik.Server(m_Funktion);
        m_bCursorOpen = true;       //Datenbankcurser offen
        kritik.s.FETCH_REL = 1;          //normaler Fetch
        if (kritik.rc == SRV_SQLNOTFOUND)
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
        s[NUM_CB_KRITIKNR].Format("%ld", kritik.s.KRITIKNR);
        s[NUM_CB_DATUM] = AllgDatumLong2CharTTMMJJ(kritik.s.DATUM, str);
        s[NUM_CB_TIME] = AllgZeitLong2CharHHMMSS(kritik.s.ZEIT, str);
        AllgEntfSpaces(kritik.s.NAMEAPO);
        s[NUM_CB_APO] = kritik.s.NAMEAPO;
        AllgEntfSpaces(kritik.s.ORT);
        s[NUM_CB_ORT] = kritik.s.ORT;
        AllgEntfSpaces(kritik.s.DIVISIONNAME);
        s[NUM_CB_PARTNER] = kritik.s.DIVISIONNAME;
        AllgEntfSpaces(kritik.s.TITEL);
        s[NUM_CB_TITEL] = kritik.s.TITEL;
        s[NUM_CB_KDNR].Format("%ld", kritik.s.IDFNR);
        s[NUM_CB_UID] = kritik.s.USERNAME64;
        s[NUM_CB_VZNR].Format("%ld", kritik.s.VERTRIEBSZENTRUMNR);
        AllgEntfSpaces(kritik.s.KRITIKTEXT);
        s[NUM_CB_BEZEICHNUNG] = kritik.s.KRITIKTEXT;
        s[NUM_CB_POSNR].Format("%ld", kritik.s.CALLBACKNO);
        AllgEntfSpaces(kritik.s.CALLBACKSTATUSNAME);
        if (AeGetApp()->IsCBStatusUsed())
        {
            s[NUM_CB_REFERENCE] = kritik.s.REFERENCE;
            s[NUM_CB_STATUS] = kritik.s.CALLBACKSTATUSNAME;
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
            if (!CListCtrlHelper::AppendImageItem(m_ListCtl, NUM_COLUMNS, s, kritik.s.KRITIKLEVEL))
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

void CDKritik::OnDestroy()
{
    CDialogMultiLang::OnDestroy();
    CloseCursor();
}

void CDKritik::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    CKRITIK kritik;
    kritik.s.FETCH_REL = 0;
    BeginWaitCursor();
    kritik.Server(m_Funktion);
    EndWaitCursor();
    ResetCursor();
    Reset();
}

void CDKritik::OnOK()
{
    if (GetFocus() == GetDlgItem(IDC_LIST1))
    {
        SelectEintrag();
        return;
    }
    UpdateData();
    if (m_CTime_Von.GetTime() > m_CTime_Bis.GetTime())
    {
        MsgBoxOK(IDP_ZEIT_BIS_LOW);
        GotoDlgCtrl(GetDlgItem(IDC_DATETIMEPICKER_VON));
        return;
    }
    CloseCursor();
    GetPage();
}

void CDKritik::SelectEintrag()
{
    CDKritikUpd dlgKritikUpd;
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        dlgKritikUpd.m_lKritiknr = atol(m_ListCtl.GetItemText(pos, NUM_CB_KRITIKNR));
        dlgKritikUpd.m_CTitel = m_ListCtl.GetItemText(pos, NUM_CB_TITEL);
        dlgKritikUpd.m_CIdf = m_ListCtl.GetItemText(pos, NUM_CB_KDNR);
        dlgKritikUpd.m_CDatum = m_ListCtl.GetItemText(pos, NUM_CB_DATUM);
        dlgKritikUpd.m_CZeit = m_ListCtl.GetItemText(pos, NUM_CB_TIME);
        dlgKritikUpd.m_CUser = m_ListCtl.GetItemText(pos, NUM_CB_UID);
        dlgKritikUpd.m_sVzNr = static_cast<short>(atoi(m_ListCtl.GetItemText(pos, NUM_CB_VZNR)));
        dlgKritikUpd.m_lRRNr = static_cast<long>(atoi(m_ListCtl.GetItemText(pos, NUM_CB_POSNR)));
        if (dlgKritikUpd.DoModal() == IDOK)
        {
            CloseCursor();
            GetPage();
        }
    }
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDKritik::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}

void CDKritik::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    SelectEintrag();
    *pResult = 0L;
}

void CDKritik::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    OnKeydownList(pNMHDR, pResult, m_ListCtl);
}

void CDKritik::OnChangeEditIdf()
{
    AllgWertKontr(&m_EditIdf, MAXIMUM_IDF);
}

void CDKritik::OnChangeEditTitel()
{
    //AllgLaengeKontr(&m_EditTitel, L_KRITIK_TITEL,AeGetApp()->Modus());
    AllgLaengeKontr(&m_EditTitel, L_KRITIK_TITEL, 1);    //auch Umlaute erlaubt
}

void CDKritik::OnButtonKnd()
{
    CDKndWahl dlgKndWahl;
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    CString CStr;
    CStr.Format("%ld", dlgKndWahl.GetIdfNr());
    SetKndVz(dlgKndWahl.GetKndVz());
    GetDlgItem(IDC_EDIT_IDF)->SetWindowText(CStr);
    CloseCursor();
    GetPage();
}

void CDKritik::OnButtonNeu()
{
    CDKritikErf dlgKritikErf;
    dlgKritikErf.m_CIdf = m_CIdf;
    dlgKritikErf.SetKndVz(GetKndVz());
    if (dlgKritikErf.DoModal() == IDOK)
    {
        CloseCursor();
        GetPage();
    }
}

void CDKritik::OnCheckVz()
{
    AeGetApp()->IsKundeHome = IsDlgButtonChecked(IDC_CHECK_VZ) ? true : false;
}

void CDKritik::InitComboboxDivisison()
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

void CDKritik::OnCbnSelchangeComboDivision()
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
