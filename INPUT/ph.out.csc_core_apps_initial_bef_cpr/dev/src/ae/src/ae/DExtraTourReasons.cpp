// DExtraTourReasons.cpp : implementation file
//

#include "stdafx.h"
#include "DExtraTourReasons.h"

//Definition der Tabellenbreite und der Ueberschriften

#define COL_AART    0
#define COL_REASON  1
#define NUM_COLUMNS 2

static COLUMNS_TYPES Columns[] =
{
    COL_AART,   "",  35, LVCFMT_LEFT,
    COL_REASON, "", 240, LVCFMT_LEFT,
    -1,         "",   0, 0
};


// CFCOrders dialog

IMPLEMENT_DYNAMIC(CDExtraTourReasons, CDialog)

CDExtraTourReasons::CDExtraTourReasons(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDExtraTourReasons::IDD, pParent)
{
    Columns[COL_AART].Columns = CResString::ex().getStrTblText(AETXT_A_ART);
    Columns[COL_REASON].Columns = CResString::ex().getStrTblText(AETXT_EXTRA_TOUR_REASON);
}

CDExtraTourReasons::~CDExtraTourReasons()
{
}

void CDExtraTourReasons::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Control(pDX, IDC_COMBO_AART, m_AArt);
    DDX_Text(pDX, IDC_EDIT_REASON, m_Reason);
}


BEGIN_MESSAGE_MAP(CDExtraTourReasons, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDExtraTourReasons::OnBnClickedButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_INSERT, &CDExtraTourReasons::OnBnClickedButtonInsert)
END_MESSAGE_MAP()


// CDExtraTourReasons message handlers

BOOL CDExtraTourReasons::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    // Combobox Auftragsarten füllen
    m_AArt.AddString(CResString::ex().getStrTblText(AETXT_S2));
    m_AArt.AddString(CResString::ex().getStrTblText(AETXT_S3));
    m_AArt.SetCurSel(0);

    GetPage();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDExtraTourReasons::OnBnClickedButtonDelete()
{
    UpdateData();
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
    {
        MsgBoxOK(IDP_KEIN_SATZ_SEL);
        return;
    }
    m_extrareasons.SetCscordertype(m_ListCtl.GetItemText(pos, COL_AART));
    m_extrareasons.SetExtratourreason(m_ListCtl.GetItemText(pos, COL_REASON));
    m_extrareasons.Delete();
    GetPage();
}

void CDExtraTourReasons::OnBnClickedButtonInsert()
{
    UpdateData();
    CString KdAuftrArt;
    m_AArt.GetLBText(m_AArt.GetCurSel(),KdAuftrArt);

    m_extrareasons.SetCscordertype(KdAuftrArt);
    m_extrareasons.SetExtratourreason(m_Reason);
    m_extrareasons.Insert();
    m_Reason.Empty();
    UpdateData(false);
    GetPage();
}

void CDExtraTourReasons::GetPage()
{
    ppString GetExtratourreason;
    ppString aart;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    m_ListCtl.DeleteAllItems();
    BeginWaitCursor();
    for (;;)
    {
        if (m_extrareasons.SelListAll() != SRV_OK)
            break;
        //Ausgabe in die Listbox
        s[COL_AART] = m_extrareasons.GetCscordertype(aart);
        s[COL_REASON] = m_extrareasons.GetExtratourreason(GetExtratourreason);

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    m_extrareasons.CloseCursor();
    EndWaitCursor();
}
