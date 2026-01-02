// DRangeDetails.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <ranges.h>
#include "DRangeDetails.h"

//Definition der Tabellenbreite und der Ueberschriften

#define COL_KB          0
#define COL_ARTNR       1
#define COL_EINHEIT     2
#define COL_NAME        3
#define COL_BESTAND     4
#define COL_PREIS       5
#define NUM_COLUMNS     6

static COLUMNS_TYPES Columns[] =
{
    COL_KB,      "",  35, LVCFMT_LEFT,
    COL_ARTNR,   "",  60, LVCFMT_RIGHT,
    COL_EINHEIT, "",  65, LVCFMT_LEFT,
    COL_NAME,    "", 200, LVCFMT_LEFT,
    COL_BESTAND, "",  65, LVCFMT_RIGHT,
    COL_PREIS,   "",  70, LVCFMT_RIGHT,
    -1,          "",   0, 0
};


// CDRangeDetails-Dialogfeld

IMPLEMENT_DYNAMIC(CDRangeDetails, CDialog)
CDRangeDetails::CDRangeDetails(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDRangeDetails::IDD, pParent)
    , m_CRangeNr(_T(""))
    , m_CRangeName(_T(""))
    , m_CMin(_T(""))
    , m_CDone(_T(""))
    , m_CSMin(_T(""))
    , m_CDiff(_T(""))
{
    Columns[COL_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_ARTNR].Columns = CResString::ex().getStrTblText(AETXT_ARTIKEL_NR);
    Columns[COL_EINHEIT].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[COL_NAME].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns[COL_BESTAND].Columns = CResString::ex().getStrTblText(AETXT_BESTAND);
    Columns[COL_PREIS].Columns = CResString::ex().getStrTblText(AETXT_PREIS);
}

CDRangeDetails::~CDRangeDetails()
{
}

void CDRangeDetails::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
    DDX_Text(pDX, IDC_EDIT_RANGE_NR, m_CRangeNr);
    DDX_Text(pDX, IDC_EDIT_RANGE_NAME, m_CRangeName);
    DDX_Text(pDX, IDC_EDIT_MIN, m_CMin);
    DDX_Text(pDX, IDC_EDIT_DONE, m_CDone);
    DDX_Text(pDX, IDC_STATIC_MIN, m_CSMin);
    DDX_Text(pDX, IDC_EDIT_DIFF, m_CDiff);
}


BEGIN_MESSAGE_MAP(CDRangeDetails, CDialogMultiLang)
END_MESSAGE_MAP()


// CDRangeDetails-Meldungshandler

BOOL CDRangeDetails::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    CStringArray s;
    ppString Name;
    ppString Einheit;
    s.SetSize(NUM_COLUMNS);

    CRANGEMEMBERS members;
    members.SetBranchno(m_sBranchNo);
    members.SetDiscountgrpno(atoi(m_CRangeNr));

    if (m_CSMin.IsEmpty())
    {
        GetDlgItem(IDC_EDIT_MIN)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_MIN)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_DONE)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_DONE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_MIN)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_MIN)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_EDIT_DIFF)->EnableWindow(FALSE);
        GetDlgItem(IDC_EDIT_DIFF)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_DONE)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_DONE)->ShowWindow(SW_HIDE);
        GetDlgItem(IDC_STATIC_DIFF)->EnableWindow(FALSE);
        GetDlgItem(IDC_STATIC_DIFF)->ShowWindow(SW_HIDE);
    }
    CLetterMan kb;
    for (;;)
    {
        if (members.SelArticle()) break;
        else
        {
            //Ausgabe in die Listbox
            s[COL_KB] = kb.Next();
            s[COL_ARTNR].Format("%d", members.GetArtikel_nr());
            s[COL_EINHEIT] = members.GetEinheit(Einheit);
            s[COL_NAME] = members.GetArtikel_name(Name);
            s[COL_BESTAND].Format("%d", members.GetBestand());
            s[COL_PREIS].Format("%0.2f", members.GetPreisekapo());

            if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
            {
                EndWaitCursor();
                return FALSE;
            }
        }
    }
    if (m_ListCtl.GetItemCount() == 0)
    {
        for (;;)
        {
            if (members.SelManu()) break;
            else
            {
                //Ausgabe in die Listbox
                s[COL_KB] = kb.Next();
                s[COL_ARTNR].Format("%d", members.GetArtikel_nr());
                s[COL_EINHEIT] = members.GetEinheit(Einheit);
                s[COL_NAME] = members.GetArtikel_name(Name);
                s[COL_BESTAND].Format("%d", members.GetBestand());
                s[COL_PREIS].Format("%0.2f", members.GetPreisekapo());

                if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
                {
                    EndWaitCursor();
                    return FALSE;
                }
            }
        }
    }
    if (m_ListCtl.GetItemCount() == 0)
    {
        MsgBoxOK(AETXT_NO_RANGES);
        CDialogMultiLang::OnCancel();
    }
    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}
