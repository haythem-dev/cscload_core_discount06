// DOrderInformationDetails4.cpp : implementation file
//

#include "stdafx.h"
#include "DOrderInformationDetails4.h"
#include <deliveryadvicelineibtlink.h>

//Definition der Tabellenbreite IBT

/*----------------------------------------------------------------------------*/
// Defines für Default-Spalten-Nummern
/*----------------------------------------------------------------------------*/
#define COL_IBT_IBTBRANCHNO             0
#define COL_IBT_IBTCUSTOMERNO           1
#define COL_IBT_IBTDELIVERYADVICEDATE   2
#define COL_IBT_IBTDELIVERYADVICENO     3
#define COL_IBT_IBTDELIVERYADVICEPOSNO  4
#define COL_IBT_IBTCSCORDERNO           5
#define COL_IBT_IBTCSCORDERPOSNO        6
#define COL_IBT_ANZ_LIST                7

static COLUMNS_TYPES SpaltenIBT[] =
{
    COL_IBT_IBTBRANCHNO,            "", 40, LVCFMT_LEFT,
    COL_IBT_IBTCUSTOMERNO,          "", 90, LVCFMT_RIGHT,
    COL_IBT_IBTDELIVERYADVICEDATE,  "", 70, LVCFMT_LEFT,
    COL_IBT_IBTDELIVERYADVICENO,    "", 90, LVCFMT_LEFT,
    COL_IBT_IBTDELIVERYADVICEPOSNO, "", 40, LVCFMT_LEFT,
    COL_IBT_IBTCSCORDERNO,          "", 90, LVCFMT_LEFT,
    COL_IBT_IBTCSCORDERPOSNO,       "", 90, LVCFMT_LEFT,
    -1,                             "",  0, 0
};


// CDOrderInformationDetails4 dialog

IMPLEMENT_DYNAMIC(CDOrderInformationDetails4, CPropertyPage)

CDOrderInformationDetails4::CDOrderInformationDetails4()
    : CTabPageMultiLang(IDD_AE_ORDER_INFORMATION_DETAILS4)
{
    m_listpos = 0;

}

CDOrderInformationDetails4::~CDOrderInformationDetails4()
{
}

void CDOrderInformationDetails4::DoDataExchange(CDataExchange* pDX)
{
    CTabPageMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_DETAILS4, m_ListCtlDetails4);
}


BEGIN_MESSAGE_MAP(CDOrderInformationDetails4, CTabPageMultiLang)
END_MESSAGE_MAP()


// CDOrderInformationDetails4 message handlers

LPCTSTR CDOrderInformationDetails4::GetTabTitle()
{
    m_csTitle = CResString::ex().getStrTblText(AETXT_INFO_DETAILS4);
    return _T(m_csTitle);
}



BOOL CDOrderInformationDetails4::OnInitDialog()
{
    CTabPageMultiLang::OnInitDialog();

    SpaltenIBT[COL_IBT_IBTBRANCHNO].Columns = CResString::ex().getStrTblText(AETXT_FILIALE);
    SpaltenIBT[COL_IBT_IBTCUSTOMERNO].Columns = CResString::ex().getStrTblText(AETXT_IBT_CUSTOMER);
    SpaltenIBT[COL_IBT_IBTDELIVERYADVICEDATE].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    SpaltenIBT[COL_IBT_IBTDELIVERYADVICENO].Columns = CResString::ex().getStrTblText(AETXT_RECHNUNG_NR);
    SpaltenIBT[COL_IBT_IBTDELIVERYADVICEPOSNO].Columns = CResString::ex().getStrTblText(AETXT_POS);
    SpaltenIBT[COL_IBT_IBTCSCORDERNO].Columns = CResString::ex().getStrTblText(AETXT_AUFNR_KSC);
    SpaltenIBT[COL_IBT_IBTCSCORDERPOSNO].Columns = CResString::ex().getStrTblText(AETXT_POSNR_KSC);

    if (!CListCtrlHelper::AddColumns(SpaltenIBT, m_ListCtlDetails4))
    {
        return FALSE;
    }

    FillList();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDOrderInformationDetails4::OnSetActive()
{
    return CTabPageMultiLang::OnSetActive();
}

void CDOrderInformationDetails4::FillList()
{
    //Lieferscheinlistbox Discounts füllen
    CStringArray s;
    CString cstr;
    ppString text;
    s.SetSize(COL_IBT_ANZ_LIST);
    CDELIVERYADVICELINEIBTLINK line;
    line.SetDeliveryadviceposno(m_listpos);
    m_ListCtlDetails4.DeleteAllItems();
    BeginWaitCursor();
    char error_msg[81];
    int rc = ::ServerNr(PIPE_AE_SRV, AasrvSelDeliveryAdviceLineIBTLink, (void*)&line.s, DELIVERYADVICELINEIBTLINK_BES, DELIVERYADVICELINEIBTLINK_ANZ, error_msg);
    if (rc < SRV_OK)
    {
        FehlerBehandlung(rc, error_msg);
        return;
    }
    if (rc == SRV_SQLNOTFOUND)
    {
        EndWaitCursor();
        return;
    }
    s[COL_IBT_IBTBRANCHNO].Format("%d", line.GetIbtbranchno());
    s[COL_IBT_IBTCUSTOMERNO].Format("%d", line.GetIbtcustomerno());
    if (line.GetIbtdeliveryadvicedate() > 0)
    {
        cstr = DDMMYYYYStringFromDateLong(line.GetIbtdeliveryadvicedate());
    }
    else
    {
        cstr.Empty();
    }
    s[COL_IBT_IBTDELIVERYADVICEDATE] = cstr;
    s[COL_IBT_IBTDELIVERYADVICENO] = line.GetIbtdeliveryadviceno(text);
    s[COL_IBT_IBTDELIVERYADVICEPOSNO].Format("%d", line.GetIbtdeliveryadviceposno());
    s[COL_IBT_IBTCSCORDERNO].Format("%d", line.GetIbtcscorderno());
    s[COL_IBT_IBTCSCORDERPOSNO].Format("%d", line.GetIbtcscorderposno());

    CListCtrlHelper::AppendItem(m_ListCtlDetails4, COL_IBT_ANZ_LIST, s);

    EndWaitCursor();
}
