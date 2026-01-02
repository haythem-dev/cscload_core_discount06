// DddSpecialUpd.cpp : implementation file
//

#include "stdafx.h"
#include <customer.h>
#include "DddSpecialUpd.h"


// CDddSpecialUpd dialog

IMPLEMENT_DYNAMIC(CDddSpecialUpd, CDialogEx)

CDddSpecialUpd::CDddSpecialUpd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDddSpecialUpd::IDD, pParent)
    , m_From(0)
    , m_CTag(_T(""))
    , m_CTagDD(_T(""))
    , m_CT_Zeit(0)
    , m_bBTM(FALSE)
    , m_bKK(FALSE)
    , m_bK08(FALSE)
    , m_bK20(FALSE)
    , m_iWD(0)
    , m_iWDDD(0)
    , m_Zeit(0)
    , m_lFrom(0)
{
    m_iFunction = DDupdate;
}

CDddSpecialUpd::~CDddSpecialUpd()
{
}

void CDddSpecialUpd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DATEFROM, m_DTfrom);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATEFROM, m_From);
    DDX_Control(pDX, IDC_COMBO_TAG, m_combo_Tag);
    DDX_CBString(pDX, IDC_COMBO_TAG, m_CTag);
    DDX_Control(pDX, IDC_COMBO_TAG_DD, m_combo_Tag_DD);
    DDX_CBString(pDX, IDC_COMBO_TAG_DD, m_CTagDD);
    DDX_Control(pDX, IDC_DATETIMEPICKER_ZEIT, m_DT_Zeit);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ZEIT, m_CT_Zeit);
    DDX_Control(pDX, IDC_CHECK_BTM, m_CB_BTM);
    DDX_Check(pDX, IDC_CHECK_BTM, m_bBTM);
    DDX_Control(pDX, IDC_CHECK_KK, m_CB_KK);
    DDX_Check(pDX, IDC_CHECK_KK, m_bKK);
    DDX_Control(pDX, IDC_CHECK_K08, m_CB_K08);
    DDX_Check(pDX, IDC_CHECK_K08, m_bK08);
    DDX_Control(pDX, IDC_CHECK_K20, m_CB_K20);
    DDX_Check(pDX, IDC_CHECK_K20, m_bK20);
}


BEGIN_MESSAGE_MAP(CDddSpecialUpd, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER_DATEFROM, &CDddSpecialUpd::OnDtnDatetimechangeDatetimepickerDatefrom)
END_MESSAGE_MAP()


// CDddSpecialUpd message handlers

BOOL CDddSpecialUpd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    m_combo_Tag.ResetContent();
    m_combo_Tag.AddString(CResString::ex().getStrTblText(IDS_SUNDAY));
    m_combo_Tag.AddString(CResString::ex().getStrTblText(IDS_MONDAY));
    m_combo_Tag.AddString(CResString::ex().getStrTblText(IDS_TUESDAY));
    m_combo_Tag.AddString(CResString::ex().getStrTblText(IDS_WEDNESDAY));
    m_combo_Tag.AddString(CResString::ex().getStrTblText(IDS_THURSDAY));
    m_combo_Tag.AddString(CResString::ex().getStrTblText(IDS_FRIDAY));
    m_combo_Tag.AddString(CResString::ex().getStrTblText(IDS_SATURDAY));

    m_combo_Tag_DD.ResetContent();
    m_combo_Tag_DD.AddString(CResString::ex().getStrTblText(IDS_SUNDAY));
    m_combo_Tag_DD.AddString(CResString::ex().getStrTblText(IDS_MONDAY));
    m_combo_Tag_DD.AddString(CResString::ex().getStrTblText(IDS_TUESDAY));
    m_combo_Tag_DD.AddString(CResString::ex().getStrTblText(IDS_WEDNESDAY));
    m_combo_Tag_DD.AddString(CResString::ex().getStrTblText(IDS_THURSDAY));
    m_combo_Tag_DD.AddString(CResString::ex().getStrTblText(IDS_FRIDAY));
    m_combo_Tag_DD.AddString(CResString::ex().getStrTblText(IDS_SATURDAY));
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_lActDate = zeit.s.DATUM;
    if (m_iFunction == DDupdate)
    {
        m_combo_Tag.SetCurSel(m_iWD);
        m_combo_Tag.GetLBText(m_combo_Tag.GetCurSel(), m_CTag);
        m_combo_Tag_DD.SetCurSel(m_iWDDD);
        m_combo_Tag_DD.GetLBText(m_combo_Tag_DD.GetCurSel(), m_CTagDD);
        m_CT_Zeit = CTimeFromDateTimeLongNoSeconds(zeit.s.DATUM, m_Zeit);
        m_From = CTimeFromDateLongMinTime(m_lFrom);
        GetDlgItem(IDC_DATETIMEPICKER_DATEFROM)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBO_TAG)->EnableWindow(FALSE);
    }
    else
    {
        int wDay = zeit.s.WTAG;
        int wDayDD = wDay + 1;
        if (wDayDD > 6) wDayDD = 0;
        m_combo_Tag.SetCurSel(wDay);
        m_combo_Tag.GetLBText(m_combo_Tag.GetCurSel(), m_CTag);
        m_combo_Tag_DD.SetCurSel(wDayDD);
        m_combo_Tag_DD.GetLBText(m_combo_Tag_DD.GetCurSel(), m_CTagDD);
        m_CT_Zeit = CTimeFromDateLongAndHour(14, zeit.s.DATUM);
        m_From = CTimeFromDateLongMinTime(zeit.s.DATUM);
    }

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}

void CDddSpecialUpd::OnBnClickedOk()
{
    UpdateData();
    long von;
    CDELAYEDDELIVERYCSTSPECIAL m_Cst;
    m_Cst.SetBranchno(AeGetApp()->VzNr());
    m_Cst.SetWeekday(static_cast<short>(m_combo_Tag.GetCurSel()));
    m_Cst.SetTime(m_CT_Zeit.GetHour()*100+
                m_CT_Zeit.GetMinute());
    von = m_From.GetYear()*10000+
                    m_From.GetMonth()*100+
                    m_From.GetDay();
    m_Cst.SetDatefrom(von);
    m_Cst.SetDateto(von);
    m_Cst.SetDelayedweekday(static_cast<short>(m_combo_Tag_DD.GetCurSel()));
    m_Cst.SetNarcotic(m_bBTM ? '1' : '0');
    m_Cst.SetColdchain(m_bKK ? '1' : '0');
    m_Cst.SetCool08(m_bK08 ? '1' : '0');
    m_Cst.SetCool20(m_bK20 ? '1' : '0');
    m_Cst.SetActiv('1');
    BeginWaitCursor();
    if (m_iFunction == DDupdate)
    {
        if (!m_Cst.Update())
        {
            MsgBoxOK(CResString::ex().getStrTblText(IDS_SET_CHANGED));
            CDialogMultiLang::OnOK();
            return;
        }
    }
    else
    {
        if (!m_Cst.Insert())
        {
            MsgBoxOK(CResString::ex().getStrTblText(IDP_INSERTED));
            CDialogMultiLang::OnOK();
            return;
        }
    }
    EndWaitCursor();
}

void CDddSpecialUpd::OnDtnDatetimechangeDatetimepickerDatefrom(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    int wDay = pDTChange->st.wDayOfWeek;
    int wDayDD = wDay + 1;
    if (wDayDD > 6)
        wDayDD = 0;
    m_combo_Tag.SetCurSel(wDay);
    m_combo_Tag.GetLBText(m_combo_Tag.GetCurSel(), m_CTag);
    m_combo_Tag_DD.SetCurSel(wDayDD);
    m_combo_Tag_DD.GetLBText(m_combo_Tag_DD.GetCurSel(), m_CTagDD);

    *pResult = 0L;
}
