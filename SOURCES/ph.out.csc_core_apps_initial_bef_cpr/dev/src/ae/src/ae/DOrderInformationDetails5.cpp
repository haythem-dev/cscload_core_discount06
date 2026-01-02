// DOrderInformationDetails5.cpp : implementation file
//

#include "stdafx.h"
#include "DOrderInformationDetails5.h"
#include <deliveryadviceremark.h>

//Definition der Tabellenbreite REMARK

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_REMARK_TYPE     0
#define COL_REMARK_TEXT     1
#define COL_REMARK_ANZ_LIST 2

static COLUMNS_TYPES SpaltenREMARK[] =
{
    COL_REMARK_TYPE, "", 300, LVCFMT_LEFT,
    COL_REMARK_TEXT, "", 400, LVCFMT_LEFT,
    -1,              "",   0, 0
};


// CDOrderInformationDetails5 dialog

IMPLEMENT_DYNAMIC(CDOrderInformationDetails5, CPropertyPage)

CDOrderInformationDetails5::CDOrderInformationDetails5()
    : CTabPageMultiLang(IDD_AE_ORDER_INFORMATION_DETAILS5)
{
    m_listpos = 0;
}

CDOrderInformationDetails5::~CDOrderInformationDetails5()
{
}

void CDOrderInformationDetails5::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_DETAILS5, m_ListCtlDetails5);
}


BEGIN_MESSAGE_MAP(CDOrderInformationDetails5, CTabPageMultiLang)
END_MESSAGE_MAP()


// CDOrderInformationDetails5 message handlers

LPCTSTR CDOrderInformationDetails5::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_INFO_DETAILS5);
    return _T(m_csTitle);
}



BOOL CDOrderInformationDetails5::OnInitDialog()
{
    CTabPageMultiLang::OnInitDialog();

    SpaltenREMARK[COL_REMARK_TYPE].Columns = CResString::ex().getStrTblText(AETXT_TYP);
    SpaltenREMARK[COL_REMARK_TEXT].Columns = CResString::ex().getStrTblText(AETXT_TEXT);

    if (!CListCtrlHelper::AddColumns(SpaltenREMARK, m_ListCtlDetails5))
    {
        return FALSE;
    }

    FillList();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDOrderInformationDetails5::OnSetActive()
{
    return CTabPageMultiLang::OnSetActive();
}

void CDOrderInformationDetails5::FillList()
{
    int rc;
    char error_msg[81];
    //Lieferscheinlistbox Discounts füllen
    CStringArray s;
    CString cstr;
    ppString text;
    s.SetSize(COL_REMARK_ANZ_LIST);
    CDELIVERYADVICEREMARK line;
    line.SetCscorderposno(m_listpos);
    m_ListCtlDetails5.DeleteAllItems();
    BeginWaitCursor();
    for (;;)
    {
        //return;
        rc = ::ServerNr(PIPE_AE_SRV, AasrvSelDeliveryAdviceRemarks, (void *)&line.s, DELIVERYADVICEREMARK_BES, DELIVERYADVICEREMARK_ANZ, error_msg);
        if (rc < SRV_OK)
        {
            FehlerBehandlung(rc, error_msg);
            return;
        }
        if (rc == SRV_SQLNOTFOUND)
        {
            break;
        }
        AeGetApp()->GetRemarkTypes(line.GetRemarktype(), cstr);
        s[COL_REMARK_TYPE] = cstr;
        line.GetRemarktext(text);
        s[COL_REMARK_TEXT] = text;

        if (!CListCtrlHelper::AppendItem(m_ListCtlDetails5, COL_REMARK_ANZ_LIST, s))
        {
            EndWaitCursor();
            return;
        }
    }
    EndWaitCursor();
}
