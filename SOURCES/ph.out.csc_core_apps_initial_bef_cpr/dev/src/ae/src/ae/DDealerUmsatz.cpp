// DDealerUmsatz.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <controlling.h>
#include "DDealerUmsatz.h"


//Definition der Tabellenbreite und der Ueberschriften

#define NUM_COLUMNS     10

static COLUMNS_TYPES Columns[] =
{
    0,  "",  70, LVCFMT_RIGHT,
    1,  "",  70, LVCFMT_RIGHT,
    2,  "",  70, LVCFMT_RIGHT,
    3,  "",  70, LVCFMT_RIGHT,
    4,  "",  40, LVCFMT_RIGHT,
    5,  "", 100, LVCFMT_RIGHT,
    6,  "", 100, LVCFMT_RIGHT,
    7,  "", 100, LVCFMT_RIGHT,
    8,  "", 100, LVCFMT_RIGHT,
    9,  "", 100, LVCFMT_RIGHT,
    -1, "",   0, 0
};

// CDDealerUmsatz-Dialogfeld

IMPLEMENT_DYNAMIC(CDDealerUmsatz, CDialog)
CDDealerUmsatz::CDDealerUmsatz(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDDealerUmsatz::IDD, pParent)
{
    m_CT_DatumBis = 0;
    m_CT_DatumVon = 0;
    Columns[0].Columns = CResString::ex().getStrTblText(AETXT_RECHNUNG_NR);
    Columns[1].Columns = CResString::ex().getStrTblText(AETXT_AUFNR_FILI);
    Columns[2].Columns = CResString::ex().getStrTblText(AETXT_AUFNR_KSC);
    Columns[3].Columns = CResString::ex().getStrTblText(AETXT_DATUM);
    Columns[4].Columns = CResString::ex().getStrTblText(IDS_TIME);
    Columns[5].Columns = CResString::ex().getStrTblText(AETXT_UMS_GES);
    Columns[6].Columns = CResString::ex().getStrTblText(AETXT_UMS_1);
    Columns[7].Columns = CResString::ex().getStrTblText(AETXT_UMS_2);
    Columns[8].Columns = CResString::ex().getStrTblText(AETXT_UMS_3);
    Columns[9].Columns = CResString::ex().getStrTblText(AETXT_UMS_4);
}

CDDealerUmsatz::~CDDealerUmsatz()
{
}

void CDDealerUmsatz::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_List1);
    DDX_Control(pDX, IDC_LIST2, m_List2);
    DDX_Text(pDX, IDC_EDIT_UID, m_CUID);
    DDX_Text(pDX, IDC_EDIT_NAME, m_CName);
    DDX_Control(pDX, IDC_DATETIMEPICKER_VON, m_DT_DatumVon);
    DDX_Control(pDX, IDC_DATETIMEPICKER_BIS, m_DT_DatumBis);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIS, m_CT_DatumBis);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_VON, m_CT_DatumVon);
}


BEGIN_MESSAGE_MAP(CDDealerUmsatz, CDialogMultiLang)
END_MESSAGE_MAP()


// CDDealerUmsatz-Meldungshandler

BOOL CDDealerUmsatz::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    CTM zeit;
    zeit.Server(AafilGetdatetime);
    CTime end = CTimeFromDateLongMinTime(zeit.s.DATUM);
    CTimeSpan y(3600, 0, 0, 0);
    CTimeSpan z(30, 0, 0, 0);
    CTime ctime = end - y;
    CTime anf(zeit.s.DATUM / 10000
            , zeit.s.DATUM / 100 % 100
            , 1
            , 0, 0, 0 );
    m_DT_DatumVon.SetRange(&ctime, &end);
    m_DT_DatumVon.SetTime(&anf);
    m_DT_DatumBis.SetRange(&ctime, &end);
    m_DT_DatumBis.SetTime(&end);
    CenterWindow();

    // Add the columns.
    if (   !CListCtrlHelper::AddColumns(Columns, m_List1)
        || !CListCtrlHelper::AddColumns(Columns, m_List2) )
    {
        return FALSE;
    }
    m_CUID.Format("%d", GetAeUser().GetUID());
    GetDlgItem( IDC_EDIT_UID )->SetWindowText(m_CUID);
    if (GetAeUser().IsDealerInfoAll())
    {
        GetDlgItem( IDC_EDIT_NAME )->EnableWindow(TRUE);
    }
    m_CName = GetAeUser().GetUserName();
    GetDlgItem(IDC_EDIT_NAME)->SetWindowText(m_CName);
    GetPage();
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDDealerUmsatz::GetPage()
{
    UpdateData();

    if (atoi(m_CUID) == GetAeUser().GetUID())
    {
        CString oldname = GetAeUser().GetUserName();
        if (!oldname.IsEmpty() && (oldname != m_CName))
        {
            CAEPWD  pwd;
            pwd.s.FILIALNR = GetAeUser().GetUserBranchNo();
            AllgStrCopy(pwd.s.USERNAME, m_CName, L_AEPWD_USERNAME);
            BeginWaitCursor();
            pwd.Server(AafilReadpasswd);
            EndWaitCursor();
            m_CUID.Format("%d", pwd.s.UID);
            GetDlgItem( IDC_EDIT_UID )->SetWindowText(m_CUID);
        }
    }
    if (m_CT_DatumVon.GetTime() > m_CT_DatumBis.GetTime())
    {
        MsgBoxOK(IDP_ZEIT_BIS_LOW);
        GotoDlgCtrl(GetDlgItem(IDC_DATETIMEPICKER_VON));
        return;
    }
    m_List1.DeleteAllItems();
    m_List2.DeleteAllItems();

    CDEALERUMSATZ dums;
    dums.SetBranchno(GetAeUser().GetUserBranchNo());
    dums.SetUid(atoi(m_CUID));
    dums.SetDateinvoice(m_CT_DatumVon.GetYear() * 10000 +
                        m_CT_DatumVon.GetMonth() * 100 +
                        m_CT_DatumVon.GetDay());
    dums.SetTimeinvoice(m_CT_DatumBis.GetYear() * 10000 +
                        m_CT_DatumBis.GetMonth() * 100 +
                        m_CT_DatumBis.GetDay());
    BeginWaitCursor();

    CStringArray s;
    s.SetSize(NUM_COLUMNS);

    double dVolume = 0.0;
    double dVolume1 = 0.0;
    double dVolume2 = 0.0;
    double dVolume3 = 0.0;
    double dVolume4 = 0.0;

    for (;;)
    {
        if (dums.SelList() != SRV_OK)
            break;
        s[0].Format("%d", dums.GetInvoiceno());
        s[1].Format("%d", dums.GetOrdernovse());
        s[2].Format("%d", dums.GetOrdernoksc());
        s[3] = DDMMYYYYStringFromDateLong(dums.GetDateinvoice());
        s[4] = HHmmStringFromTimeLong(dums.GetTimeinvoice());
        s[5].Format("%.2lf", dums.GetInvoicevolume());
        s[6].Format("%.2lf", dums.GetVolume1());
        s[7].Format("%.2lf", dums.GetVolume2());
        s[8].Format("%.2lf", dums.GetVolume3());
        s[9].Format("%.2lf", dums.GetVolume4());
        dVolume += dums.GetInvoicevolume();
        dVolume1 += dums.GetVolume1();
        dVolume2 += dums.GetVolume2();
        dVolume3 += dums.GetVolume3();
        dVolume4 += dums.GetVolume4();

        if (!CListCtrlHelper::AppendItem(m_List1, NUM_COLUMNS, s))
        {
            EndWaitCursor();
            return;
        }
    }
    s[0].Empty();
    s[1].Empty();
    s[2].Empty();
    s[3].Empty();
    s[4].Empty();
    s[5].Format("%.2lf", dVolume);
    s[6].Format("%.2lf", dVolume1);
    s[7].Format("%.2lf", dVolume2);
    s[8].Format("%.2lf", dVolume3);
    s[9].Format("%.2lf", dVolume4);

    CListCtrlHelper::AppendItem(m_List2, NUM_COLUMNS, s);
    EndWaitCursor();
}

void CDDealerUmsatz::OnOK()
{
    GetPage();
    UpdateData(FALSE);
}
