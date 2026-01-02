// DDelayedCstAll.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <customer.h>
#include "DDelayedCstAll.h"


// CDDelayedCstAll-Dialogfeld

IMPLEMENT_DYNAMIC(CDDelayedCstAll, CDialog)
CDDelayedCstAll::CDDelayedCstAll(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDDelayedCstAll::IDD, pParent)
    , m_CTag(_T(""))
    , m_CT_Zeit(0)
    , m_bBTM(FALSE)
    , m_bKK(FALSE)
    , m_bK08(FALSE)
    , m_bK20(FALSE)
{
}

CDDelayedCstAll::~CDDelayedCstAll()
{
}

void CDDelayedCstAll::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO_TAG, m_combo_Tag);
    DDX_CBString(pDX, IDC_COMBO_TAG, m_CTag);
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


BEGIN_MESSAGE_MAP(CDDelayedCstAll, CDialogMultiLang)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON_AKTIV, OnBnClickedButtonAktiv)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, OnBnClickedButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_DEAK, OnBnClickedButtonDeak)
END_MESSAGE_MAP()


// CDDelayedCstAll-Meldungshandler

void CDDelayedCstAll::OnBnClickedOk()
{
    UpdateData();
    m_Cst.SetBranchno(AeGetApp()->VzNr());
    m_Cst.SetWeekday(static_cast<short>(m_combo_Tag.GetCurSel()));
    m_Cst.SetTime(m_CT_Zeit.GetHour() * 100 + m_CT_Zeit.GetMinute());
    m_Cst.SetNarcotic(m_bBTM ? '1' : '0');
    m_Cst.SetColdchain(m_bKK ? '1' : '0');
    m_Cst.SetCool08(m_bK08 ? '1' : '0');
    m_Cst.SetCool20(m_bK20 ? '1' : '0');
    BeginWaitCursor();
    if (!m_Cst.InsertAll())
    {
        CString CStr;
        CStr.Format(CResString::ex().getStrTblText(AETXT_INSERTED), m_Cst.GetCustomerno());
        MsgBoxOK(CStr);
    }
    EndWaitCursor();
}

void CDDelayedCstAll::OnBnClickedButtonAktiv()
{
    UpdateData();
    m_Cst.SetBranchno(AeGetApp()->VzNr());
    m_Cst.SetWeekday(static_cast<short>(m_combo_Tag.GetCurSel()));
    m_Cst.SetActiv('1');
    BeginWaitCursor();
    if (!m_Cst.SetActiv())
    {
        CString CStr;
        CStr.Format(CResString::ex().getStrTblText(AETXT_AKTIVIERT), m_Cst.GetCustomerno());
        MsgBoxOK(CStr);
    }
    EndWaitCursor();
}

void CDDelayedCstAll::OnBnClickedButtonDelete()
{
    if (MsgBoxYesNo(IDP_LOESCHEN_JA) == IDYES)
    {
        UpdateData();
        m_Cst.SetBranchno(AeGetApp()->VzNr());
        m_Cst.SetWeekday(static_cast<short>(m_combo_Tag.GetCurSel()));
        BeginWaitCursor();
        if (!m_Cst.DeleteAll())
        {
            CString CStr;
            CStr.Format(CResString::ex().getStrTblText(AETXT_DELETED), m_Cst.GetCustomerno());
            MsgBoxOK(CStr);
        }
        EndWaitCursor();
    }
}

void CDDelayedCstAll::OnBnClickedButtonDeak()
{
    UpdateData();
    m_Cst.SetBranchno(AeGetApp()->VzNr());
    m_Cst.SetWeekday(static_cast<short>(m_combo_Tag.GetCurSel()));
    m_Cst.SetActiv('0');
    BeginWaitCursor();
    if (!m_Cst.SetActiv())
    {
        CString CStr;
        CStr.Format(CResString::ex().getStrTblText(AETXT_DEAKTIVIERT), m_Cst.GetCustomerno());
        MsgBoxOK(CStr);
    }
    EndWaitCursor();
}

BOOL CDDelayedCstAll::OnInitDialog()
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
    m_combo_Tag.SetCurSel(6);
    m_combo_Tag.GetLBText(m_combo_Tag.GetCurSel(), m_CTag);
    /*m_Combo_Tour.ResetContent();
    m_Combo_Tour.AddString(CResString::ex().getStrTblText(IDS_SUNDAY));
    m_Combo_Tour.AddString(CResString::ex().getStrTblText(IDS_MONDAY));
    m_Combo_Tour.AddString(CResString::ex().getStrTblText(IDS_TUESDAY));
    m_Combo_Tour.AddString(CResString::ex().getStrTblText(IDS_WEDNESDAY));
    m_Combo_Tour.AddString(CResString::ex().getStrTblText(IDS_THURSDAY));
    m_Combo_Tour.AddString(CResString::ex().getStrTblText(IDS_FRIDAY));
    m_Combo_Tour.AddString(CResString::ex().getStrTblText(IDS_SATURDAY));
    m_Combo_Tour.SetCurSel(1);
    m_Combo_Tour.GetLBText(m_Combo_Tour.GetCurSel(), m_CTour);*/
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    m_CT_Zeit = CTimeFromDateLongAndHour(14, zeit.s.DATUM);

    UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}
