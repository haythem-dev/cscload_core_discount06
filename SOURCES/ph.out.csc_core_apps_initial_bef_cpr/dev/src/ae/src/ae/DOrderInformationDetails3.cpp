// DOrderInformationDetails3.cpp : implementation file
//

#include "stdafx.h"
#include "DOrderInformationDetails3.h"
#include <deliveryadvicelinereturn.h>

//Definition der Tabellenbreite Returns

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_RETURNS_BLOCKEDFORRETURNS           0
#define COL_RETURNS_QTY_RETURNED                1
#define COL_RETURNS_QTY_RETURNED_REBATEINKIND   2
#define COL_RETURNS_QTY_RETURN_REJECTED         3
#define COL_RETURNS_ANZ_LIST                    4

static COLUMNS_TYPES SpaltenReturns[] =
{
    COL_RETURNS_BLOCKEDFORRETURNS,         "", 90, LVCFMT_LEFT,
    COL_RETURNS_QTY_RETURNED,              "", 50, LVCFMT_RIGHT,
    COL_RETURNS_QTY_RETURNED_REBATEINKIND, "", 70, LVCFMT_RIGHT,
    COL_RETURNS_QTY_RETURN_REJECTED,       "", 70, LVCFMT_RIGHT,
    -1,                                    "",  0, 0
};


// CDOrderInformationDetails3 dialog

IMPLEMENT_DYNAMIC(CDOrderInformationDetails3, CPropertyPage)

CDOrderInformationDetails3::CDOrderInformationDetails3()
    : CTabPageMultiLang(IDD_AE_ORDER_INFORMATION_DETAILS3)
{
    m_listpos = 0;
}

CDOrderInformationDetails3::~CDOrderInformationDetails3()
{
}

void CDOrderInformationDetails3::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_DETAILS3, m_ListCtlDetails3);
}


BEGIN_MESSAGE_MAP(CDOrderInformationDetails3, CTabPageMultiLang)
END_MESSAGE_MAP()


// CDOrderInformationDetails3 message handlers

LPCTSTR CDOrderInformationDetails3::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_INFO_DETAILS3);
    return _T(m_csTitle);
}



BOOL CDOrderInformationDetails3::OnInitDialog()
{
    CTabPageMultiLang::OnInitDialog();

    SpaltenReturns[COL_RETURNS_BLOCKEDFORRETURNS].Columns = CResString::ex().getStrTblText(AETXT_RETOUREN_SPERRE);
    SpaltenReturns[COL_RETURNS_QTY_RETURNED].Columns = CResString::ex().getStrTblText(AETXT_MENGE);
    SpaltenReturns[COL_RETURNS_QTY_RETURNED_REBATEINKIND].Columns = CResString::ex().getStrTblText(AETXT_RABATT_QTY);
    SpaltenReturns[COL_RETURNS_QTY_RETURN_REJECTED].Columns = CResString::ex().getStrTblText(AETXT_REJECTED);

    if (!CListCtrlHelper::AddColumns(SpaltenReturns, m_ListCtlDetails3))
    {
        return FALSE;
    }

    FillList();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDOrderInformationDetails3::OnSetActive()
{
    return CTabPageMultiLang::OnSetActive();
}

void CDOrderInformationDetails3::FillList()
{
    int rc;
    char error_msg[81];
    //Lieferscheinlistbox Discounts füllen
    CStringArray s;
    CString cstr;
    ppString text;
    s.SetSize(COL_RETURNS_ANZ_LIST);
    CDELIVERYADVICELINERETURN line;
    line.SetDeliveryadviceposno(m_listpos);
    m_ListCtlDetails3.DeleteAllItems();
    BeginWaitCursor();
    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvSelDeliveryAdviceLineReturn, (void *)&line.s, DELIVERYADVICELINERETURN_BES, DELIVERYADVICELINERETURN_ANZ, error_msg);
        if (rc < SRV_OK)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
        if (rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        if (line.GetBlockedforreturns() == 1)
        {
            s[COL_RETURNS_BLOCKEDFORRETURNS] = CResString::ex().getStrTblText(AETXT_JA);
        }
        else
        {
            s[COL_RETURNS_BLOCKEDFORRETURNS] = CResString::ex().getStrTblText(AETXT_NEIN);
        }
        s[COL_RETURNS_QTY_RETURNED].Format("%d", line.GetQty_returned());
        s[COL_RETURNS_QTY_RETURNED_REBATEINKIND].Format("%d", line.GetQty_returned_rebateinkind());
        s[COL_RETURNS_QTY_RETURN_REJECTED].Format("%d", line.GetQty_return_rejected());

        if (!CListCtrlHelper::AppendItem(m_ListCtlDetails3, COL_RETURNS_ANZ_LIST, s))
        {
            EndWaitCursor();
            return;
        }
    }
    EndWaitCursor();
}
