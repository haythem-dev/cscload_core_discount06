// DOrderInformationDetails2.cpp : implementation file
//

#include "stdafx.h"
#include "DOrderInformationDetails2.h"
#include <deliveryadvicelinediscounts.h>

//Definition der Tabellenbreite Discount

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_DISCOUNT_DISCOUNTMODE       0
#define COL_DISCOUNT_DISCOUNT           1
#define COL_DISCOUNT_DISCOUNTVALUE      2
#define COL_DISCOUNT_DISCOUNTTYPE       3
#define COL_DISCOUNT_HIERARCHY          4
#define COL_DISCOUNT_CALCULATIONBASIS   5
#define COL_DISCOUNT_DELETEREASON       6
#define COL_DISCOUNT_ANZ_LIST           7

static COLUMNS_TYPES SpaltenDiscount[] =
{
    COL_DISCOUNT_DISCOUNTMODE,     "", 240, LVCFMT_LEFT,
    COL_DISCOUNT_DISCOUNT,         "",  65, LVCFMT_RIGHT,
    COL_DISCOUNT_DISCOUNTVALUE,    "",  70, LVCFMT_LEFT,
    COL_DISCOUNT_DISCOUNTTYPE,     "",  70, LVCFMT_LEFT,
    COL_DISCOUNT_HIERARCHY,        "",  70, LVCFMT_LEFT,
    COL_DISCOUNT_CALCULATIONBASIS, "", 120, LVCFMT_LEFT,
    COL_DISCOUNT_DELETEREASON,     "", 120, LVCFMT_LEFT,
    -1,                            "",   0, 0
};


// CDOrderInformationDetails2 dialog

IMPLEMENT_DYNAMIC(CDOrderInformationDetails2, CPropertyPage)

CDOrderInformationDetails2::CDOrderInformationDetails2()
    : CTabPageMultiLang(IDD_AE_ORDER_INFORMATION_DETAILS2)
{
    m_listpos = 0;

}

CDOrderInformationDetails2::~CDOrderInformationDetails2()
{
}

void CDOrderInformationDetails2::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_DETAILS2, m_ListCtlDetails2);
}


BEGIN_MESSAGE_MAP(CDOrderInformationDetails2, CTabPageMultiLang)
END_MESSAGE_MAP()


// CDOrderInformationDetails2 message handlers

LPCTSTR CDOrderInformationDetails2::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_INFO_DETAILS2);
    return _T(m_csTitle);
}

BOOL CDOrderInformationDetails2::OnInitDialog()
{
    CTabPageMultiLang::OnInitDialog();

    SpaltenDiscount[COL_DISCOUNT_DISCOUNTMODE].Columns = CResString::ex().getStrTblText(AETXT_DISCOUNTMODE);
    SpaltenDiscount[COL_DISCOUNT_DISCOUNT].Columns = CResString::ex().getStrTblText(AETXT_RABATT);
    SpaltenDiscount[COL_DISCOUNT_DISCOUNTVALUE].Columns = CResString::ex().getStrTblText(AETXT_DISCOUNTVALUE);
    SpaltenDiscount[COL_DISCOUNT_DISCOUNTTYPE].Columns = CResString::ex().getStrTblText(AETXT_RABATT_FORM);
    SpaltenDiscount[COL_DISCOUNT_HIERARCHY].Columns = CResString::ex().getStrTblText(AETXT_HIERARCHY);
    SpaltenDiscount[COL_DISCOUNT_DELETEREASON].Columns = CResString::ex().getStrTblText(AETXT_DELETEREASON);
    SpaltenDiscount[COL_DISCOUNT_CALCULATIONBASIS].Columns = CResString::ex().getStrTblText(AETXT_BASIS);

    if (!CListCtrlHelper::AddColumns(SpaltenDiscount, m_ListCtlDetails2))
    {
        return FALSE;
    }

    FillList();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDOrderInformationDetails2::OnSetActive()
{
    return CTabPageMultiLang::OnSetActive();
}

void CDOrderInformationDetails2::FillList()
{
    int rc;
    char error_msg[81];
    //Lieferscheinlistbox Discounts füllen
    CStringArray s;
    CString cstr;
    ppString text;
    s.SetSize(COL_DISCOUNT_ANZ_LIST);
    CDELIVERYADVICELINEDISCOUNTS line;
    line.SetDeliveryadviceposno(m_listpos);
    m_ListCtlDetails2.DeleteAllItems();
    BeginWaitCursor();
    for (;;)
    {
        rc = ::ServerNr(PIPE_AE_SRV, AasrvSelDeliveryAdviceLineDiscount, (void *)&line.s, DELIVERYADVICELINEDISCOUNTS_BES, DELIVERYADVICELINEDISCOUNTS_ANZ, error_msg);
        if (rc < SRV_OK)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
        if (rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        s[COL_DISCOUNT_DISCOUNTMODE] = line.GetDiscountmodename(text);
        s[COL_DISCOUNT_DISCOUNT].Format("%0.2lf", line.GetDiscount());
        s[COL_DISCOUNT_DISCOUNTVALUE].Format("%0.2lf", line.GetDadiscountvalue());
        if (line.GetDiscounttype() == 1)
        {
            cstr = CResString::ex().getStrTblText(AETXT_DISCOUNT_TYPE_1);
        }
        else if (line.GetDiscounttype() == 2)
        {
            cstr = CResString::ex().getStrTblText(AETXT_DISCOUNT_TYPE_2);
        }
        else if (line.GetDiscounttype() == 3)
        {
            cstr = CResString::ex().getStrTblText(AETXT_DISCOUNT_TYPE_3);
        }
        else if (line.GetDiscounttype() == 4)
        {
            cstr = CResString::ex().getStrTblText(AETXT_DISCOUNT_TYPE_4);
        }
        else if (line.GetDiscounttype() == 5)
        {
            cstr = CResString::ex().getStrTblText(AETXT_DISCOUNT_TYPE_5);
        }
        else
        {
            cstr.Empty();
        }
        s[COL_DISCOUNT_DISCOUNTTYPE] = cstr;
        s[COL_DISCOUNT_HIERARCHY].Format("%d", line.GetHierarchy());
        s[COL_DISCOUNT_CALCULATIONBASIS].Format("%d", line.GetCalculationbasis());
        s[COL_DISCOUNT_DELETEREASON].Format("%d", line.GetDeletereason());

        if (!CListCtrlHelper::AppendItem(m_ListCtlDetails2, COL_DISCOUNT_ANZ_LIST, s))
        {
            EndWaitCursor();
            return;
        }
    }
    EndWaitCursor();
}
