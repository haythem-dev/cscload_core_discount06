// DNewUserInfo.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include <mailsystem.h>
#include "DNewUserInfo.h"

// CDNewUserInfo-Dialogfeld

IMPLEMENT_DYNAMIC(CDNewUserInfo, CDialog)
CDNewUserInfo::CDNewUserInfo(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDNewUserInfo::IDD, pParent)
{
    m_lActDate = 0;
    m_CText = _T("");
    m_CDauer = _T("1");
    m_CT_Datum = 0;
    m_CT_ZeitVon = 0;
    m_bAlle = FALSE;
}

CDNewUserInfo::~CDNewUserInfo()
{
}

void CDNewUserInfo::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RADIO_TIP, m_CBTip);
    DDX_Text(pDX, IDC_EDIT_TEXT, m_CText);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_Edit_Text);
    DDX_Text(pDX, IDC_EDIT_DAUER, m_CDauer);
    DDX_Control(pDX, IDC_EDIT_DAUER, m_Edit_Dauer);
    DDX_Control(pDX, IDC_DATETIMEPICKER_ZEITVON, m_DT_ZeitVon);
    DDX_Control(pDX, IDC_DATETIMEPICKER_DATUM, m_DT_Datum);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_DATUM, m_CT_Datum);
    DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_ZEITVON, m_CT_ZeitVon);
    DDX_Control(pDX, IDC_CHECK_ALLE, m_CB_Alle);
    DDX_Check(pDX, IDC_CHECK_ALLE, m_bAlle);
}


BEGIN_MESSAGE_MAP(CDNewUserInfo, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_TEXT, OnChangeEditText)
END_MESSAGE_MAP()


// CDNewUserInfo-Meldungshandler

BOOL CDNewUserInfo::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    CenterWindow();
    BeginWaitCursor();
    CTM zeit;
    zeit.Server(AafilGetdatetime);
    EndWaitCursor();
    m_lActDate = zeit.s.DATUM;
    CTime anf = CTimeFromDateLongMinTime(zeit.s.DATUM);
    CTimeSpan y(5, 0, 0, 0);
    CTime end = anf + y;
    m_DT_Datum.SetRange(&anf, &end);
    m_DT_Datum.SetTime(&anf);
    m_CT_ZeitVon = CTimeFromDateTimeLong(zeit.s.DATUM, zeit.s.ZEIT);
    if (GetAeUser().IsUserInfoAll())
    {
        GetDlgItem(IDC_CHECK_ALLE)->EnableWindow(TRUE);
        GetDlgItem(IDC_CHECK_ALLE)->ShowWindow(SW_SHOW);
    }
    else
    {
        GetDlgItem(IDC_CHECK_ALLE)->EnableWindow(FALSE);
        GetDlgItem(IDC_CHECK_ALLE)->ShowWindow(SW_HIDE);
    }
    CheckRadioButton(IDC_RADIO_TIP, IDC_RADIO_WARNUNG, IDC_RADIO_TIP);
    UpdateData(FALSE);
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CDNewUserInfo::OnChangeEditText()
{
    AllgLaengeKontr(&m_Edit_Text, 240,AeGetApp()->Modus());
}

void CDNewUserInfo::OnChangeEditDauer()
{
    AllgWertKontr(&m_Edit_Dauer, 1, 20);
}

void CDNewUserInfo::OnOK()
{
    int id;         //ID of the checked radio button
    CUSERINFORMATION userinfo;

    UpdateData();
    if (m_CText.IsEmpty())
    {
        MsgBoxOK(IDP_MAIL_TEXT);
        m_Edit_Text.SetFocus();
        m_Edit_Text.SetSel(0, -1, FALSE);
        return;
    }
    userinfo.SetDate(m_CT_Datum.GetYear() * 10000
                   + m_CT_Datum.GetMonth() * 100
                   + m_CT_Datum.GetDay() );
    userinfo.SetValidtimefrom(m_CT_ZeitVon.GetHour() * 10000
                            + m_CT_ZeitVon.GetMinute() * 100
                            + m_CT_ZeitVon.GetSecond() );
    CTimeSpan minuten(0, 0, atoi(m_CDauer) + 4, 0);
    CTime CT_ZeitBis;
    CT_ZeitBis = m_CT_ZeitVon + minuten;
    userinfo.SetValidtimeto(CT_ZeitBis.GetHour() * 10000
                          + CT_ZeitBis.GetMinute() * 100
                          + CT_ZeitBis.GetSecond() );
    userinfo.CheckFree();
    if (userinfo.rc == SRV_OK)
    {
        CString CStr;
        ppString Str;
        CStr.Format(CResString::ex().getStrTblText(AETXT_USERINFO_EXISTS)
            ,userinfo.GetValidtimefrom()
            ,userinfo.GetValidtimeto()
            ,userinfo.GetInfomessage(Str));
        MsgBoxOK(CStr);
        GotoDlgCtrl(GetDlgItem(IDC_DATETIMEPICKER_ZEIT_VON));
        return;
    }
    if (IsDlgButtonChecked(IDC_CHECK_ALLE))
    {
        userinfo.SetValidbranchno(0);
    }
    else
    {
        userinfo.SetValidbranchno((GetAeUser().GetUser()).FILIALNR);
    }
    userinfo.SetDate(m_CT_Datum.GetYear() * 10000
                   + m_CT_Datum.GetMonth() * 100
                   + m_CT_Datum.GetDay() );
    userinfo.SetValidtimefrom(m_CT_ZeitVon.GetHour() * 10000
                            + m_CT_ZeitVon.GetMinute() * 100
                            + m_CT_ZeitVon.GetSecond() );
    userinfo.SetValidtimeto(CT_ZeitBis.GetHour() * 10000
                            + CT_ZeitBis.GetMinute() * 100
                            + CT_ZeitBis.GetSecond() );
    userinfo.SetUserbranchno((GetAeUser().GetUser()).FILIALNR);
    userinfo.SetUid_anlage(GetAeUser().GetUID());
    //Prioritaet bestimmen
    id = GetCheckedRadioButton(IDC_RADIO_TIP, IDC_RADIO_WARNUNG);
    if (id == IDC_RADIO_TIP) userinfo.SetPriority(0);
    else if (id == IDC_RADIO_INFO) userinfo.SetPriority(1);
    else if (id == IDC_RADIO_HINWEIS) userinfo.SetPriority(2);
    else if (id == IDC_RADIO_WICHTIG) userinfo.SetPriority(3);
    else userinfo.SetPriority(4);
    userinfo.SetInfomessage(m_CText);
    userinfo.Insert();
    CDialogMultiLang::OnOK();
}
