// DPromoWahl.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <promoinfo.h>
#include "DPromoWahl.h"

//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     3

static COLUMNS_TYPES Columns[] =
{
    0,  "", 20, LVCFMT_LEFT,
    1,  "", 40, LVCFMT_RIGHT,
    2,  "", 90, LVCFMT_LEFT,
    -1, "",  0, 0
};

// CDPromoWahl-Dialogfeld

IMPLEMENT_DYNAMIC(CDPromoWahl, CDialog)
CDPromoWahl::CDPromoWahl(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDPromoWahl::IDD, pParent)
{
}

CDPromoWahl::~CDPromoWahl()
{
}

void CDPromoWahl::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
}


BEGIN_MESSAGE_MAP(CDPromoWahl, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDPromoWahl-Meldungshandler

BOOL CDPromoWahl::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_KENNBUCHSTABE);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_PROMO_NR);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_PROMOTION);

    CenterWindow();

    // Add the columns.
    if (!CListCtrlHelper::AddColumns(Columns, m_List1))
    {
        return FALSE;
    }

    CPROMOQUOTAANZ anz;

    CStringArray s;
    ppString name;
    s.SetSize(NUM_COLUMNS);
    m_List1.DeleteAllItems();
    anz.SetBranchno(AeGetApp()->VzNr());
    CLetterMan kb;
    BeginWaitCursor();
    for (;;)
    {
        if (anz.SelList() != SRV_OK) break;
        s[0] = kb.Next();
        s[1].Format("%d", anz.GetPromotion_no());
        s[2] = anz.GetName(name);

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s, 0))
        {
            EndWaitCursor();
            return FALSE;
        }
    }
    anz.CloseCursor();
    EndWaitCursor();
    if (m_List1.GetItemCount() == 0)
    {
        MsgBoxOK(IDP_NO_DATA);
        CDialogMultiLang::OnCancel();
    }

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDPromoWahl::OnBnClickedOk()
{
    int pos = m_List1.GetNextItem(-1, LVNI_SELECTED);
    if (pos >= 0)
    {
        m_sPromoNr = static_cast<short>(atoi(m_List1.GetItemText(pos, 1)));
        m_promo = m_List1.GetItemText(pos, 2);
        CDialogMultiLang::OnOK();
    }
    else
    {
        MsgBoxOK( IDP_KEIN_SATZ_SEL );
    }
}
