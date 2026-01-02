// DStellerAnz.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <artikel.h>
#include <artsel.h>
#include "DArtInf.h"
#include "DStellerAnz.h"

//Definition der Tabellenbreite und der Ueberschriften

#define COL_STELLER_KB      0
#define COL_STELLER_MENGE   1
#define COL_STELLER_BESTAND 2
#define COL_STELLER_EINHEIT 3
#define COL_STELLER_NAME    4
#define COL_STELLER_DRF     5
#define COL_STELLER_CODE    6
#define COL_STELLER_PZN     7

#define NUM_COLUMNS         8

static COLUMNS_TYPES Columns[] =
{
    COL_STELLER_KB,      "",  20, LVCFMT_RIGHT,
    COL_STELLER_MENGE,   "",  50, LVCFMT_RIGHT,
    COL_STELLER_BESTAND, "",  50, LVCFMT_RIGHT,
    COL_STELLER_EINHEIT, "",  70, LVCFMT_LEFT,
    COL_STELLER_NAME,    "", 210, LVCFMT_LEFT,
    COL_STELLER_DRF,     "",  40, LVCFMT_LEFT,
    COL_STELLER_CODE,    "",  70, LVCFMT_LEFT,
    COL_STELLER_PZN,     "",   0, LVCFMT_RIGHT,
    -1,                  "",   0, 0
};

// CDStellerAnz-Dialogfeld

IMPLEMENT_DYNAMIC(CDStellerAnz, CDialog)
CDStellerAnz::CDStellerAnz(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDStellerAnz::IDD, pParent)
{
    Columns[COL_STELLER_KB].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[COL_STELLER_MENGE].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    Columns[COL_STELLER_BESTAND].Columns = CResString::ex().getStrTblText(AETXT_KURZ_BESTAND);
    Columns[COL_STELLER_EINHEIT].Columns = CResString::ex().getStrTblText(AETXT_EINHEIT);
    Columns[COL_STELLER_NAME].Columns = CResString::ex().getStrTblText(AETXT_ARTIKELNAME);
    Columns[COL_STELLER_DRF].Columns = CResString::ex().getStrTblText(AETXT_DRF);
    Columns[COL_STELLER_CODE].Columns = CResString::ex().getStrTblText(AETXT_ARTICLE_CODE);
    Columns[COL_STELLER_PZN].Columns = CResString::ex().getStrTblText(AETXT_PZN);

    m_lArtikelNr = 0;
    m_sVzNr = 0;
    m_bNosteller = FALSE;
}

CDStellerAnz::~CDStellerAnz()
{
}

void CDStellerAnz::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDStellerAnz, CDialogMultiLang)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
    ON_MESSAGE(WM_HOOKFKT, OnHookFkt)
END_MESSAGE_MAP()


// CDStellerAnz-Meldungshandler

BOOL CDStellerAnz::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();

    //Variablen
    CStringArray s;

    DWORD dwOldBits = m_List1.GetExtendedStyle();
    dwOldBits |= LVS_EX_FULLROWSELECT;
    m_List1.SetExtendedStyle(dwOldBits);

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }

    s.SetSize(NUM_COLUMNS);
    ppString drf;
    ppString einheit;
    ppString name;

    //Anfangsinitialisierung durchfuehren
    m_List1.DeleteAllItems();
    CSTELLER stell;
    CSTELLERTYP stelltyp;
    CARTAESEL code;
    stelltyp.SetArticle_no_pack(m_lArtikelNr);
    //stelltyp.SetFilialnr(m_sVzNr);
    CLetterMan kb;
    BeginWaitCursor();
    if (!stelltyp.SelTyp())
    {
        if (stelltyp.GetCompack_type() == 1 || stelltyp.GetCompack_type() == 2)
        {
            CARTINF inf;
            inf.s.ARTIKEL_NR = m_lArtikelNr;
            inf.s.FILIALNR = m_sVzNr;
            inf.Server(AatartInf_art_nr);
            if (inf.rc == SRV_OK)
            {
                s[COL_STELLER_KB] = kb.Next();
                s[COL_STELLER_MENGE].Format("0");
                s[COL_STELLER_BESTAND].Format("%d", inf.s.BESTAND);
                s[COL_STELLER_EINHEIT].Format("%s", inf.s.EINHEIT);
                s[COL_STELLER_NAME].Format("%s", inf.s.ARTIKEL_NAME);
                s[COL_STELLER_DRF].Format("%s", inf.s.DARREICHFORM);
                code.s.ARTIKEL_NR = inf.s.ARTIKEL_NR;
                code.Server(AatartSel_Preferred);
                AllgEntfSpaces(code.s.ARTICLE_CODE);
                s[COL_STELLER_CODE] = code.s.ARTICLE_CODE;
                s[COL_STELLER_PZN].Format("%d", inf.s.ARTIKEL_NR);

                if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
                {
                    EndWaitCursor();
                    return FALSE;
                }
            }
        }
    }
    else
    {
        m_bNosteller = TRUE;
        CDialogMultiLang::OnOK();
        return TRUE;
    }

    stell.SetArticle_no_pack(m_lArtikelNr);
    stell.SetFilialnr(m_sVzNr);
    for (;;)
    {
        if (stell.SelList() != SRV_OK)
            break;
        s[COL_STELLER_KB] = kb.Next();
        s[COL_STELLER_MENGE].Format("%d", stell.GetQuantity());
        s[COL_STELLER_BESTAND].Format("%d", stell.GetBestand());
        stell.GetEinheit(einheit);
        s[COL_STELLER_EINHEIT] = einheit;
        stell.GetArtikel_name(name);
        s[COL_STELLER_NAME] = name;
        stell.GetDarreichform(drf);
        s[COL_STELLER_DRF] = drf;
        code.s.ARTIKEL_NR = stell.GetArticle_no_element();
        code.Server(AatartSel_Preferred);
        AllgEntfSpaces(code.s.ARTICLE_CODE);
        s[COL_STELLER_CODE] = code.s.ARTICLE_CODE;
        s[COL_STELLER_PZN].Format("%d", stell.GetArticle_no_element());

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    EndWaitCursor();
    GotoDlgCtrl(GetDlgItem(IDC_LIST1));
    CListCtrlHelper::SetItemStateSelectedFocused(m_List1, 0);

    return TRUE;
}

// Bearbeitung von Tastaturereignissen auf dem gesammten Dialog
// (unabhängig vom ausgewählten Bedienelement)
LRESULT CDStellerAnz::OnHookFkt(WPARAM /*wParam*/, LPARAM lpMsg)
{
    if (((LPMSG)lpMsg)->wParam == VK_F11)
    {
        int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
        if (pos < 0)
            return 0L;
        CDArtInf dlgArtInf(atol(m_List1.GetItemText(pos, COL_STELLER_PZN)));
        dlgArtInf.m_bNoStellerTest = true;
        dlgArtInf.DoModal();
        return 1L;
    }
    return 0L;
}

void CDStellerAnz::OnDblclkList1(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    *pResult = 0L;

    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
        return;
    CDArtInf dlgArtInf(atol(m_List1.GetItemText(pos, COL_STELLER_PZN)));
    dlgArtInf.m_bNoStellerTest = true;
    dlgArtInf.DoModal();
}

void CDStellerAnz::OnOK()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos < 0)
        return;
    CDArtInf dlgArtInf(atol(m_List1.GetItemText(pos, COL_STELLER_PZN)));
    dlgArtInf.m_bNoStellerTest = true;
    dlgArtInf.DoModal();
}
