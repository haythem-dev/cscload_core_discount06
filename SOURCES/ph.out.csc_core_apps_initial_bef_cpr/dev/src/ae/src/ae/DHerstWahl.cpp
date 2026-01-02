// DHerstWahl.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <hersteller.h>
#include "DHerstWahl.h"


//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "",  20, LVCFMT_LEFT,
    1,  "", 202, LVCFMT_LEFT,
    2,  "",   0, LVCFMT_LEFT,
    -1, "",   0, 0
};

// CDHerstWahl-Dialogfeld

IMPLEMENT_DYNAMIC(CDHerstWahl, CDialog)
CDHerstWahl::CDHerstWahl(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDHerstWahl::IDD, pParent)
{
    m_hersteller_nr = 0;
    m_hersteller_name = _T("");
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_HERSTEL);
}

CDHerstWahl::~CDHerstWahl()
{
}

void CDHerstWahl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}

BEGIN_MESSAGE_MAP(CDHerstWahl, CDialog)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnNMDblclkList1)
END_MESSAGE_MAP()


// CDHerstWahl-Meldungshandler

void CDHerstWahl::OnBnClickedOk()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_hersteller_nr = atol(m_ListCtl.GetItemText(pos, 2));
        CDialogMultiLang::OnOK();
    }
    else
    {
        MsgBoxOK( IDP_KEIN_SATZ_SEL );
    }
}

void CDHerstWahl::OnNMDblclkList1(NMHDR* /*pNMHDR*/, LRESULT *pResult)
{
    OnBnClickedOk();
    *pResult = 0L;
}

BOOL CDHerstWahl::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    DWORD dwOldBits = m_ListCtl.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_ListCtl.SetExtendedStyle(dwOldBits);

    ppString name;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);
    //Anfangsinitialisierung durchfuehren
    m_ListCtl.DeleteAllItems();
    CHERSTELLERLISTE herst;
    herst.SetName(m_hersteller_name);
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (herst.SelList() != SRV_OK)
            break;
        s[0] = kb.Next();
        herst.GetName(name);
        s[1] = name.c_str();
        s[2].Format("%d", herst.GetHersteller_nr());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}
