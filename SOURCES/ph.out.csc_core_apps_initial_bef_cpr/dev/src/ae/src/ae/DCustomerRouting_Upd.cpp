// DCustomerRouting_Upd.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <customer.h>
#include "DCustomerRouting_Upd.h"


// CDCustomerRouting_Upd-Dialogfeld

IMPLEMENT_DYNAMIC(CDCustomerRouting_Upd, CDialog)
CDCustomerRouting_Upd::CDCustomerRouting_Upd(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDCustomerRouting_Upd::IDD, pParent)
    , m_CVz2(_T(""))
    , m_CVz(_T(""))
    , m_CApo(_T(""))
    , m_COrt(_T(""))
    , m_CTag(_T(""))
    , m_CT_Von(0)
    , m_CT_Bis(0)
{
    m_iTag = 0;
}

CDCustomerRouting_Upd::~CDCustomerRouting_Upd()
{
}

void CDCustomerRouting_Upd::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DATETIMEPICKER_VON, m_DateTime_Von);
    DDX_Control(pDX, IDC_DATETIMEPICKER_BIS, m_DateTime_Bis);
    DDX_Control(pDX, IDC_EDIT_VZ2, m_Edit_VZ2);
    DDX_Text(pDX, IDC_EDIT_VZ2, m_CVz2);
    DDX_Text(pDX, IDC_EDIT_VZ, m_CVz);
    DDX_Text(pDX, IDC_EDIT_APO, m_CApo);
    DDX_Text(pDX, IDC_EDIT_ORT, m_COrt);
    DDX_Control(pDX, IDC_COMBO_TAG, m_Combo_Tag);
    DDX_CBString(pDX, IDC_COMBO_TAG, m_CTag);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_VON, m_CT_Von);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_BIS, m_CT_Bis);
}


BEGIN_MESSAGE_MAP(CDCustomerRouting_Upd, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_VZ2, OnEnChangeEditVz2)
    ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CDCustomerRouting_Upd-Meldungshandler

void CDCustomerRouting_Upd::OnEnChangeEditVz2()
{
    AllgWertKontr(&m_Edit_VZ2, MAXIMUM_FILIALNR);
}

void CDCustomerRouting_Upd::OnBnClickedOk()
{
    UpdateData();
    if (m_CVz2.IsEmpty())
    {
        MsgBoxOK(IDP_FP_FILINR_EINGEBEN);
        GotoDlgCtrl(GetDlgItem(IDC_EDIT_VZ2));
        return;
    }
    if (m_CT_Von.GetTime() > m_CT_Bis.GetTime())
    {
        MsgBoxOK(IDP_ZEIT_BIS_LOW);
        GotoDlgCtrl(GetDlgItem(IDC_DATETIMEPICKER_VON));
        return;
    }
    CCUSTROUT Routing;
    Routing.SetBranchno(m_sVznr);
    Routing.SetCustomerno(m_lKundennr);
    Routing.SetZeit_von(m_Zeitalt);
    Routing.SetDayofweek(m_CTag);
    m_iTag = m_Combo_Tag.GetCurSel();
    Routing.SetWeekday(static_cast<short>(m_iTag));
    Routing.SetDestbranchno(static_cast<short>(atoi(m_CVz2)));
    long vonHH = m_CT_Von.GetHour();
    long vonMM = m_CT_Von.GetMinute();
    long von = vonHH*100 + vonMM;
    long bisHH = m_CT_Bis.GetHour();
    long bisMM = m_CT_Bis.GetMinute();
    long bis = bisHH*100 + bisMM;

    Routing.SetTimefrom(von);
    Routing.SetTimeto(bis);
    if (m_ifunktion == UPDATE)
        Routing.Update();
    else
        Routing.Insert();
    OnOK();
}

BOOL CDCustomerRouting_Upd::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    //füllen Combobox mit Wochentagen
    for (int i = 0; i < 7; i++)
    {
        m_Combo_Tag.AddString(m_pTagtab->GetAt(i));
    }
    m_Combo_Tag.SetCurSel(m_iTag);
    if (m_ifunktion == UPDATE)
        m_Combo_Tag.EnableWindow(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zurückgeben.
}
