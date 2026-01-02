// DChooseFiliale.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DChooseFiliale.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     2

static COLUMNS_TYPES Columns[] =
{
    0,  "",  60, LVCFMT_LEFT,
    1,  "", 180, LVCFMT_LEFT,
    -1, "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDChooseFiliale


CDChooseFiliale::CDChooseFiliale(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDChooseFiliale::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_FIL_NAME);
}


void CDChooseFiliale::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDChooseFiliale, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDChooseFiliale

void CDChooseFiliale::OnOK()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        CString str = m_ListCtl.GetItemText(pos, 0);
        m_FilialNr = static_cast<short>(atoi(str));
        CDialogMultiLang::OnOK();
    }
}

void CDChooseFiliale::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    OnOK();
    *pResult = 0L;
}

BOOL CDChooseFiliale::OnInitDialog()
{
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    CDialogMultiLang::OnInitDialog();

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    const std::vector<Filiale>& filialen = AeGetApp()->HoleFilialen();
    for (std::vector<Filiale>::const_iterator iter = filialen.begin(); iter != filialen.end(); ++iter)
    {
        s[0].Format("%d", iter->RegionTeilNr);
        s[1] = iter->Name;

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            return FALSE;
        }
    }

    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}
