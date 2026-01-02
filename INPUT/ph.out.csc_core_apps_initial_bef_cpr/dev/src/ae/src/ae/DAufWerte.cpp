// DAufWerte.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "ordervalues.h"
#include "DAufWerte.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     5

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_RIGHT,
    1,  "", 70, LVCFMT_RIGHT,
    2,  "", 90, LVCFMT_RIGHT,
    3,  "", 90, LVCFMT_RIGHT,
    4,  "", 90, LVCFMT_RIGHT,
    -1, "",  0, 0
};


// CDAufWerte-Dialogfeld

IMPLEMENT_DYNAMIC(CDAufWerte, CDialog)
CDAufWerte::CDAufWerte(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDAufWerte::IDD, pParent)
{
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_MWST);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_WERT_NETTO);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_WERT_BRUTTO);
    Columns[4].Columns = CResString::ex().getStrTblText(AETXT_WERT_TAX);
}

CDAufWerte::~CDAufWerte()
{
}

void CDAufWerte::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDAufWerte, CDialogMultiLang)
END_MESSAGE_MAP()


// CDAufWerte-Meldungshandler

BOOL CDAufWerte::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    DWORD dwOldBits = m_List1.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_List1.SetExtendedStyle(dwOldBits);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }

    CORDERVALUES oval;
    //Variablen
    double sumnetto = 0.0;
    double sumtax = 0.0;
    double sumbrutto = 0.0;
    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    //Anfangsinitialisierung durchfuehren
    m_List1.DeleteAllItems();

    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        oval.Server(AasrvGetOrderVals, PIPE_AE_SRV);
        if (oval.rc != SRV_OK)
            break;
        s[0] = kb.Next();
        s[1].Format("%0.2lf", oval.GetSalestaxrate());
        s[2].Format("%0.2lf", oval.GetOrdvalnet());
        sumnetto += oval.GetOrdvalnet();
        s[3].Format("%0.2lf", oval.GetOrdvalnet() + oval.GetOrdvaltax());
        sumbrutto += (oval.GetOrdvalnet() + oval.GetOrdvaltax());
        s[4].Format("%0.2lf", oval.GetOrdvaltax());
        sumtax += oval.GetOrdvaltax();

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    EndWaitCursor();
    // Ausgeben Summenwerte
    s[0] = kb.Next();
    s[1] = CResString::ex().getStrTblText(AETXT_SUMME);
    s[2].Format("%0.2lf", sumnetto);
    s[3].Format("%0.2lf", sumbrutto);
    s[4].Format("%0.2lf", sumtax);

    if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
    {
        EndWaitCursor();
        return FALSE;
    }

    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);

    return TRUE;
}
