// DCustomerOrderCheck.cpp : implementation file
//
#include "stdafx.h"
#include <controlling.h>
#include "DKndWahl.h"
#include "DCustomerOrderCheck.h"

//Definition der Breite der ListCtrl-Spalten

#define NUMBER_OF_COLUMNS     7

static COLUMNS_TYPES Columns[] =
{
    0,  "",  25, LVCFMT_LEFT,
    1,  "",  70, LVCFMT_LEFT,
    2,  "", 250, LVCFMT_LEFT,
    3,  "",  75, LVCFMT_RIGHT,
    4,  "", 140, LVCFMT_LEFT,
    5,  "",  65, LVCFMT_LEFT,
    6,  "", 140, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
//  DCustomerOrderCheck dialog


IMPLEMENT_DYNAMIC(DCustomerOrderCheck, CDialog)

DCustomerOrderCheck::DCustomerOrderCheck(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(DCustomerOrderCheck::IDD, pParent), CPageBrowser(0)
{
    // List View Column structure

    //Texte der ListCtrl - Spalten
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KB);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_IDF_NR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_APOTHEKENNAME);
    Columns[3].Columns = "";
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_ORT);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_CUST_ORDER_CHECK_PRUEFZEIT);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_CUST_ORDER_CHECK_STATUS);

    //Im ListCtrl angezeigte Texte für die Stati (Kurzform)
    m_cStringArrayStatusTextShort.SetSize(3);
    m_cStringArrayStatusTextShort[0] = CResString::ex().getStrTblText(AETXT_CUST_ORDER_CHECK_STATUS_0_SHORT);
    m_cStringArrayStatusTextShort[1] = CResString::ex().getStrTblText(AETXT_CUST_ORDER_CHECK_STATUS_1_SHORT);
    m_cStringArrayStatusTextShort[2] = CResString::ex().getStrTblText(AETXT_CUST_ORDER_CHECK_STATUS_2_SHORT);
}

void DCustomerOrderCheck::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COC_LISTCTRL, m_ListCustomerOrderCheckTable);  //ListCtrl-Control-Member
    DDX_Control(pDX, IDC_COC_DATETIMEPICKER1, m_DateTimePicker);        //Zeitauswahlfeld-Control-Member
    DDX_Control(pDX, IDC_COC_COMBO_STATUS, m_combo_Status);             //Status-Combobox-Control-Member
    DDX_Control(pDX, IDC_COC_EDIT_IDF, m_edit_Customer);                //Kunde-Textfeld-Control-Member
    DDX_Text(pDX, IDC_COC_COMBO_STATUS,m_cstr_combo_Status);            //Member für Inhalt der Status-Combobox
}


BEGIN_MESSAGE_MAP(DCustomerOrderCheck, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnOK)                                   //Button "Selektieren"
    ON_BN_CLICKED(IDC_COC_BUTTON_KND, OnSelectKunde)            //Button "Auswahl Kunde"
    ON_NOTIFY(LVN_KEYDOWN, IDC_COC_LISTCTRL, OnKeydownListCtrl) //Behandlung Tastatur-Ereignis im ListCtrl
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)                           //Behandlung Tastatur-Ereignis im Dialog
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//  DCustomerOrderCheck message handlers

BOOL  DCustomerOrderCheck::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    m_lKdnr = 0;
    m_icheckordertime = 0;
    m_sorderstatus = 0;

    //Befüllen der Combobox
    m_combo_Status.AddString(CResString::ex().getStrTblText(AETXT_CUST_ORDER_CHECK_STATUS_ALL));
    m_combo_Status.AddString(CResString::ex().getStrTblText(AETXT_CUST_ORDER_CHECK_STATUS_0));
    m_combo_Status.AddString(CResString::ex().getStrTblText(AETXT_CUST_ORDER_CHECK_STATUS_1));
    m_combo_Status.AddString(CResString::ex().getStrTblText(AETXT_CUST_ORDER_CHECK_STATUS_2));
    m_combo_Status.SetCurSel(0); //ersten Eintrag selektieren

    m_DateTimePicker.SetFormat("HH:mm");    //Voreinstellen des Zeit-Auswahl-Feldes auf HH:MM

    //Spalten des ListCtrls einfügen
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCustomerOrderCheckTable))
    {
        return FALSE;
    }

    m_iZeilenListCtrl = m_ListCustomerOrderCheckTable.GetCountPerPage();    //Init auf Anzahl der Zeilen im ListCtrl
    Init(m_iZeilenListCtrl);                                                //Init auf Anzahl der Zeilen im ListCtrl

    UpdateData(false);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


afx_msg void DCustomerOrderCheck::OnOK()
{
    CTime   cTimeFromDialog;    //Dummy für Entnahme der Zeit aus dem Zeit-Selektions-Feld

    CString strBuffer;

    UpdateData(true);
    CloseCursor();              //Schließen des Cursors für erneute Selektion

    //Aufnahme Wert des Feldes Kunde
    GetDlgItem(IDC_COC_EDIT_IDF)->GetWindowText(strBuffer);
    m_lKdnr = atol(strBuffer);

    //Aufnahme Wert des Zeit-Selektions-Feldes
    m_DateTimePicker.GetTime(cTimeFromDialog);
    m_icheckordertime = cTimeFromDialog.GetHour() * 10000 + cTimeFromDialog.GetMinute() * 100;

    //Aufnahme Wert des Feldes Status
    m_sorderstatus = static_cast<short>(m_combo_Status.GetCurSel() - 1);

    //Start des Selekts
    GetPage();
}

afx_msg void DCustomerOrderCheck::OnSelectKunde()
{
    //Auswahl eines Kunden
    CDKndWahl dlgKndWahl;

    //Start Kundeauswahl-Dialog
    if (dlgKndWahl.DoModal() != IDOK)
    {
        return;
    }
    CString Str;
    Str.Format("%ld", dlgKndWahl.GetIdfNr());

    //Platzieren der Kundennummer im Textfeld IDFnr
    m_edit_Customer.SetWindowText(Str);
    m_edit_Customer.SetFocus();
}

void DCustomerOrderCheck::CloseCursor()
{
    if (!m_bCursorOpen)
        return;
    BeginWaitCursor();
    m_CustomerOrderCheck.CloseCursor();     //Cursor auf Server-Seite schließen
    EndWaitCursor();
    ResetCursor();
    Reset();
}

bool DCustomerOrderCheck::GetPage(const int nKzUpDown/*=NEXT_PG*/)
{
    ppString        strBuffer;
    char            chBuffer[20];

    long            FETCH_REL;              //Art des Fetches

    CStringArray    cStringArrayItems;      //Dummy für den Inhalt einer ListCtrl-Zeile

    cStringArrayItems.SetSize(NUMBER_OF_COLUMNS);

    UpdateData();

    //Anfangsinitialisierung durchfuehren
    if (m_bFirstDataset)  //Erstmaliger Aufruf
    {
        FETCH_REL = 1;

        //Befüllen der Felder für die Selektion
        m_CustomerOrderCheck.s.BRANCHNO = AeGetApp()->VzNr();
        m_CustomerOrderCheck.s.VERTRIEBSZENTRUMNR = AeGetApp()->VzNr();
        m_CustomerOrderCheck.s.CUSTOMERNO = m_lKdnr;
        m_CustomerOrderCheck.s.KUNDENNR = m_lKdnr;
        m_CustomerOrderCheck.s.CHECKORDERTIME = m_icheckordertime;
        m_CustomerOrderCheck.s.ORDERSTATUS = m_sorderstatus;
    }

    if (!GetFetchPositionOnPageSwitch(nKzUpDown, FETCH_REL))
    {
        return false;
    }

    m_ListCustomerOrderCheckTable.DeleteAllItems();
    CLetterMan kb;
    BeginWaitCursor();
    for (int i = 0; i < m_iZeilenListCtrl; i++)
    {
        m_CustomerOrderCheck.SelList(FETCH_REL);            //Ausführen des Selects / nächster Satz
        m_bCursorOpen = true;                               //Datenbankcurser offen
        FETCH_REL = 1;                                      //nach initialem Fetch nun normaler Fetch
        if (m_CustomerOrderCheck.rc != SRV_OK)
        {
            if (m_CustomerOrderCheck.rc < SRV_OK)
                break;         //Fehler DB
            if (m_bFirstDataset)
            {
                //kein Satz gefunden
                CloseCursor();
                EndWaitCursor();
                return false;
            }
            SetItemCountOfCurrentPage(i); //Anzahl aktuelle Zeilen im Listcontrol
            break;
        }
        m_bFirstDataset = false;

        cStringArrayItems[0] = kb.Next();                               //Zeichen

        strBuffer.format("%d", m_CustomerOrderCheck.GetCustomerno());   //IDF
        cStringArrayItems[1] = strBuffer.c_str();

        AllgEntfSpaces(m_CustomerOrderCheck.s.NAMEAPO);                 //Apothekenname
        m_CustomerOrderCheck.GetNameapo(strBuffer);
        cStringArrayItems[2] = strBuffer.c_str();

        AllgEntfSpaces(m_CustomerOrderCheck.s.POSTLEITZAHL);            //Postleitzahl
        m_CustomerOrderCheck.GetPostleitzahl(strBuffer);
        cStringArrayItems[3] = strBuffer.c_str();

        AllgEntfSpaces(m_CustomerOrderCheck.s.ORT);                     //Ort
        m_CustomerOrderCheck.GetOrt(strBuffer);
        cStringArrayItems[4] = strBuffer.c_str();

        strBuffer = AllgZeitLong2CharHHMMSS(m_CustomerOrderCheck.GetCheckordertime(), chBuffer);
        cStringArrayItems[5] = strBuffer.c_str();                       //Prüfzeit

        //Status
        cStringArrayItems[6] = m_cStringArrayStatusTextShort.GetAt(m_CustomerOrderCheck.GetOrderstatus());

        //Ausgabe in die Listbox
        if (!CListCtrlHelper::AppendItem(m_ListCustomerOrderCheckTable, NUMBER_OF_COLUMNS, cStringArrayItems))
        {
            EndWaitCursor();
            return false;
        }
    }
    CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCustomerOrderCheckTable, 0);
    EndWaitCursor();

    return true;
}

void DCustomerOrderCheck::MarkListPosChar(int Letter)
{
    int pos;
    if (CListCtrlHelper::GetListPositionByChar(m_ListCustomerOrderCheckTable, Letter, pos))
    {
        CListCtrlHelper::SetFocusSelectedFocusedVisible(m_ListCustomerOrderCheckTable, pos);
    }
}

void DCustomerOrderCheck::OnKeydownListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
    if (OnKeydownList(pNMHDR, pResult, m_ListCustomerOrderCheckTable, false))
    {
        return;
    }

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (CLetterMan::InAZRange(pLVKeyDow->wVKey))
    {
        MarkListPosChar((int)(pLVKeyDow->wVKey));
        *pResult = 1L;
    }
}

LRESULT DCustomerOrderCheck::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    return CPageBrowser::OnHookNextPrev(lpMsg);
}
