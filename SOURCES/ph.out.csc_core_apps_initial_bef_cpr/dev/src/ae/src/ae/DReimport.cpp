// DReimport.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DArtInf.h"
#include <artikel.h>
#include <artsel.h>
#include "DReimport.h"

//Definition der Tabellenbreite und der Ueberschriften

#define COL_KB      0
#define COL_ARTCODE 1
#define COL_BESTAND 2
#define COL_EINHEIT 3
#define COL_NAME    4
#define COL_DAF     5
#define COL_AEP     6
#define COL_PZN     7
#define NUM_COLUMNS 8

static COLUMNS_TYPES Columns[] =
{
    COL_KB,      "",  30, LVCFMT_RIGHT,
    COL_ARTCODE, "",  70, LVCFMT_LEFT,
    COL_BESTAND, "",  40, LVCFMT_RIGHT,
    COL_EINHEIT, "",  70, LVCFMT_LEFT,
    COL_NAME,    "", 200, LVCFMT_LEFT,
    COL_DAF,     "",  40, LVCFMT_LEFT,
    COL_AEP,     "",  60, LVCFMT_LEFT,
    COL_PZN,     "",   0, LVCFMT_LEFT,
    -1,          "",   0, 0
};

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDReimport


CDReimport::CDReimport(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDReimport::IDD, pParent), CPageBrowser(0)
{
    m_lPZN = 0;

    Columns[COL_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_PZN].Columns = CResString::ex().getStrTblText(AETXT_PZN);
    Columns[COL_BESTAND].Columns = CResString::ex().getStrTblText(AETXT_BEST);
    Columns[COL_EINHEIT].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[COL_NAME].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns[COL_DAF].Columns = CResString::ex().getStrTblText(AETXT_DAF);
    Columns[COL_AEP].Columns = CResString::ex().getStrTblText(AETXT_AEP);
}


void CDReimport::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ListCtl);
}


BEGIN_MESSAGE_MAP(CDReimport, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, OnKeydownList1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDReimport

BOOL CDReimport::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    //Variablen
    int first;
    CStringArray s;
    ppString hilfe;
    CARTAESEL code;
    s.SetSize(NUM_COLUMNS);

    if (m_lPZN == 0)
    {
        CDialogMultiLang::OnCancel();
        return TRUE;
    }

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_ListCtl))
    {
        return FALSE;
    }

    first = 0;
    m_CReimp.SetPzn(m_lPZN);
    CLetterMan kb;
    for (;;)
    {
        if (m_CReimp.SelAuswahl() != 0) break;
        first = 1;
        s[COL_KB] = kb.Next();
        code.s.ARTIKEL_NR = m_CReimp.GetPzn();
        code.Server(AatartSel_Preferred);
        AllgEntfSpaces(code.s.ARTICLE_CODE);
        s[COL_ARTCODE] = code.s.ARTICLE_CODE;
        s[COL_PZN].Format("%ld", m_CReimp.GetPzn());
        s[COL_BESTAND].Format("%ld", m_CReimp.GetBestand());
        s[COL_EINHEIT] = m_CReimp.GetEinheit(hilfe);
        s[COL_NAME] = m_CReimp.GetArtikel_name(hilfe);
        s[COL_DAF] = m_CReimp.GetDarreichform(hilfe);
        s[COL_AEP].Format("%0.2lf", m_CReimp.GetPreisekapo());

        if (!CListCtrlHelper::AppendItem(m_ListCtl, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    m_CReimp.CloseCursor();
    if (first == 0)
    {
        CDialogMultiLang::OnCancel();
        return TRUE;
    }
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_ListCtl, 0);

    return FALSE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDReimport::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{

    OnOK();
    *pResult = 0L;
}

void CDReimport::OnOK()
{
    int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_lPZN = atol(m_ListCtl.GetItemText(pos, COL_PZN));
        m_CArtikelName = m_ListCtl.GetItemText(pos, COL_NAME);
        m_CEinheit = m_ListCtl.GetItemText(pos, COL_EINHEIT);
        m_CDarfor = m_ListCtl.GetItemText(pos, COL_DAF);
        CDialogMultiLang::OnOK();
    }
}

void CDReimport::OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult)
{
    if (OnKeydownList(pNMHDR, pResult, m_ListCtl, false, false))
    {
        return;
    }

    LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
    if (pLVKeyDow->wVKey == VK_F11)
    {
        CDArtInf dlgArtInf;
        long ArtNr = 0;
        int pos = m_ListCtl.GetNextItem(-1, LVNI_SELECTED);
        if (pos >= 0)
        {
            CString CStr = m_ListCtl.GetItemText(pos, COL_PZN);
            ArtNr = atol(CStr);
        }
        if (ArtNr != 0) dlgArtInf.SetArtNr(ArtNr);
        dlgArtInf.DoModal();
        *pResult = 1L;
        return;             //Message wird nicht weitergeleitet
    }
    *pResult = 0L;
}
