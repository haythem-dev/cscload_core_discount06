// DUmsHercode.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "DUmsHercode.h"
#include <statistics.h>

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "", 30, LVCFMT_LEFT,
    1,  "", 70, LVCFMT_LEFT,
    2,  "", 80, LVCFMT_LEFT,
    -1, "",  0, 0
};


// CDUmsHercode-Dialogfeld

IMPLEMENT_DYNAMIC(CDUmsHercode, CDialog)
CDUmsHercode::CDUmsHercode(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDUmsHercode::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_HERSTEL);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_UMSATZ);
    m_lAufnr = 0;
}

CDUmsHercode::~CDUmsHercode()
{
}

void CDUmsHercode::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDUmsHercode, CDialogMultiLang)
END_MESSAGE_MAP()


// CDUmsHercode-Meldungshandler

BOOL CDUmsHercode::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }
    CAUFWERTHERST aufwert;
    aufwert.SetKdauftragnr(m_lAufnr);
    CStringArray s;
    long FETCH_REL;
    ppString sHercode;
    s.SetSize(NUM_COLUMNS);
    FETCH_REL = 1;
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        aufwert.SelList(FETCH_REL);
        if (aufwert.rc != SRV_OK)
            break;
        s[0] = kb.Next();
        s[1].Format("%s", aufwert.GetHersteller_code(sHercode));
        s[2].Format("%.2lf", aufwert.GetPreisekapo());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    aufwert.CloseCursor();
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetFocusSelectedFocused(m_ListCtl, 0);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}
