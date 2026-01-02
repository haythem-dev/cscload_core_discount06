// DOrderInformationDetails1.cpp : implementation file
//

#include "stdafx.h"
#include "DOrderInformationDetails1.h"
#include <deliveryadvicelinedetails.h>

//Definition der Tabellenbreite Details

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_DETAILS_QTY_DELIVEREY   0
#define COL_DETAILS_QTY_LACK        1
#define COL_DETAILS_BATCH           2
#define COL_DETAILS_EXPIRYDATE      3
#define COL_DETAILS_PACKAGEID       4
#define COL_DETAILS_TRACKINGID      5
#define COL_DETAILS_ANZ_LIST        6

static COLUMNS_TYPES SpaltenDetails[] =
{
    COL_DETAILS_QTY_DELIVEREY, "",  60, LVCFMT_LEFT,
    COL_DETAILS_QTY_LACK,      "",  45, LVCFMT_RIGHT,
    COL_DETAILS_BATCH,         "",  70, LVCFMT_LEFT,
    COL_DETAILS_EXPIRYDATE,    "",  90, LVCFMT_LEFT,
    COL_DETAILS_PACKAGEID,     "",  70, LVCFMT_LEFT,
    COL_DETAILS_TRACKINGID,    "", 200, LVCFMT_LEFT,
    -1,                        "",   0, 0
};


// CDOrderInformationDetails1 dialog

IMPLEMENT_DYNAMIC(CDOrderInformationDetails1, CPropertyPage)

CDOrderInformationDetails1::CDOrderInformationDetails1()
    : CTabPageMultiLang(IDD_AE_ORDER_INFORMATION_DETAILS1)
{
    m_listpos = 0;
}

CDOrderInformationDetails1::~CDOrderInformationDetails1()
{
}

void CDOrderInformationDetails1::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_DETAILS1, m_ListCtlDetails1);
}


BEGIN_MESSAGE_MAP(CDOrderInformationDetails1, CTabPageMultiLang)
END_MESSAGE_MAP()


// CDOrderInformationDetails1 message handlers

LPCTSTR CDOrderInformationDetails1::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_INFO_DETAILS1);
    return _T(m_csTitle);
}



BOOL CDOrderInformationDetails1::OnInitDialog()
{
    CTabPageMultiLang::OnInitDialog();

    SpaltenDetails[COL_DETAILS_QTY_DELIVEREY].Columns = CResString::ex().getStrTblText(AETXT_LIEF);
    SpaltenDetails[COL_DETAILS_QTY_LACK].Columns = CResString::ex().getStrTblText(AETXT_DEFEKT_SMALL_TITLE);
    SpaltenDetails[COL_DETAILS_BATCH].Columns = CResString::ex().getStrTblText(AETXT_CHARGE);
    SpaltenDetails[COL_DETAILS_EXPIRYDATE].Columns = CResString::ex().getStrTblText(AETXT_VERFALLDATUM);
    SpaltenDetails[COL_DETAILS_PACKAGEID].Columns = CResString::ex().getStrTblText(AETXT_PACKAGEID);
    SpaltenDetails[COL_DETAILS_TRACKINGID].Columns = CResString::ex().getStrTblText(AETXT_TRACKINGID);

    if (!CListCtrlHelper::AddColumns(SpaltenDetails, m_ListCtlDetails1))
    {
        return FALSE;
    }

    FillList();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDOrderInformationDetails1::OnSetActive()
{
    return CTabPageMultiLang::OnSetActive();
}

void CDOrderInformationDetails1::FillList()
{
    //Lieferscheinlistbox Details füllen
    CStringArray s;
    CString cstr;
    ppString text;
    s.SetSize(COL_DETAILS_ANZ_LIST);
    CDELIVERYADVICELINEDETAILS line;
    line.SetDeliveryposno(m_listpos);
    m_ListCtlDetails1.DeleteAllItems();
    BeginWaitCursor();
    for (;;)
    {
        char error_msg[81];
        int rc = ::ServerNr(PIPE_AE_SRV, AasrvSelDeliveryAdviceLineDetails, (void*)&line.s, DELIVERYADVICELINEDETAILS_BES, DELIVERYADVICELINEDETAILS_ANZ, error_msg);
        if (rc < SRV_OK)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
        if (rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        s[COL_DETAILS_QTY_DELIVEREY].Format("%d", line.GetQty_delivery());
        s[COL_DETAILS_QTY_LACK].Format("%d", line.GetQty_lack());
        s[COL_DETAILS_BATCH] = line.GetBatch(text);
        if (line.GetExpirydate() > 0)
        {
            cstr = DDMMYYYYStringFromDateLong(line.GetExpirydate());
        }
        else
        {
            cstr.Empty();
        }
        s[COL_DETAILS_EXPIRYDATE] = cstr;
        s[COL_DETAILS_PACKAGEID].Format("%d", line.GetPackageid());
        s[COL_DETAILS_TRACKINGID] = line.GetTrackingid(text);

        if (!CListCtrlHelper::AppendItem(m_ListCtlDetails1, COL_DETAILS_ANZ_LIST, s))
        {
            EndWaitCursor();
            return;
        }
    }
    EndWaitCursor();
}
