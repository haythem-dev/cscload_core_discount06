
//(c)---------- Customer service program -------------------------------------//
/*
   Source: CPCallPlanUndertake.cpp
   Author: A.Schmidt-Rehschuh
   made  : 12.07.2000

   declaration:
   Dialog: implementation file
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include "CPCallPlanUndertake.h"
#include "DBenVwtng.h"
#include "DKontrPwd.h"
#include "CPCallPlanLoadListe.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CCPCallPlanUndertake::CCPCallPlanUndertake(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CCPCallPlanUndertake::IDD, pParent)
    , m_srvUndertake(AeGetApp()->ErrorPath())
{
    m_CTime_LoadDate = 0;
    m_lLoadDate = 0;
    m_bIsUndertake = false;
    m_psrvAdmin = new ppCallPlanLoad(AeGetApp()->VzNr(),
                                     AeGetApp()->GetCurrentDate(),
                                     AeGetApp()->ErrorPath());
}

//--- deconstructor ----------------------------------------------------------//

CCPCallPlanUndertake::~CCPCallPlanUndertake()
{
    if (m_psrvAdmin)
       delete m_psrvAdmin;
}

//--- DoDataExchange ---------------------------------------------------------//

void CCPCallPlanUndertake::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_DATETIME_LOADDATE, m_DateCtrl_LoadDate);
    DDX_DateTimeCtrl(pDX, IDC_DATETIME_LOADDATE, m_CTime_LoadDate);
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CCPCallPlanUndertake, CDialogMultiLang)
    ON_BN_CLICKED(IDC_BUTTON_ADMINISTRATION, OnButtonAdministration)
    ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIME_LOADDATE, OnDatetimechangeDatetimeLoaddate)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- CCPCallPlanUndertake message handlers (ClassWizard) --------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CCPCallPlanUndertake::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();
    m_actDate = CTimeFromDateLongMinTime(AeGetApp()->GetCurrentDate());
    m_CTime_LoadDate = m_actDate;
    CTimeSpan y(365, 0, 0, 0);
    CTime end = m_actDate + y;
    m_DateCtrl_LoadDate.SetRange(&m_actDate, &end);
    UpdateData(FALSE);
    if (!CheckPassword())
    {
        CDialogMultiLang::EndDialog(0);
        return TRUE;
    }
    else if (!SetCurrentAdministration())
    {
        CDialogMultiLang::OnCancel();
        return FALSE;
    }
    SetDlgText();
    return TRUE;
}

//--- (ClassWizard)OnOK ------------------------------------------------------//

void CCPCallPlanUndertake::OnOK()
{
    GetDlgItem(IDCANCEL)->EnableWindow(FALSE);
    LoadSeraPlan();
    if (!LoadPhonPlan())
    {
       GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
       return;
    }
    m_bIsUndertake = true;
    GetDlgItem(IDCANCEL)->EnableWindow(TRUE);
}

//--- (ClassWizard)OnCancel --------------------------------------------------//

void CCPCallPlanUndertake::OnCancel()
{
    if (   m_bIsUndertake
        && (MsgBoxYesNo(IDP_DEL_LOADPLAN, MB_ICONQUESTION|MB_DEFBUTTON1) == IDYES)
        && !m_psrvAdmin->Delete() )
    {
        MsgBoxOK(m_psrvAdmin->GetErrorMsg());
    }

    CDialogMultiLang::OnCancel();
}

//--- (ClassWizard)OnButtonAdministration ------------------------------------//

void CCPCallPlanUndertake::OnButtonAdministration()
{
    CCPCallPlanLoadListe dlgAdmin;
    dlgAdmin.SetVzNr(AeGetApp()->VzNr());
    dlgAdmin.DoModal();
    CTime x;
    m_DateCtrl_LoadDate.GetTime(x);
    m_psrvAdmin->SetLadeDatum(x.GetYear()*10000 + x.GetMonth()*100 + x.GetDay());
    SetCurrentAdministration();
}

//----------------------------------------------------------------------------//
//--- private methodes -------------------------------------------------------//
//----------------------------------------------------------------------------//

//--- CheckPassword ----------------------------------------------------------//

bool CCPCallPlanUndertake::CheckPassword()
{
    #ifndef _DEBUG
    CDKontrPwd dlgPassWord;
    CAeUser& currentAeUser = GetAeUser();

    dlgPassWord.m_Pwd = currentAeUser.GetPasswd();
    if (!currentAeUser.UpdUser() || (dlgPassWord.DoModal() != IDOK))
        return false;
    #endif
    return true;
}

//--- CheckPassword ----------------------------------------------------------//

bool CCPCallPlanUndertake::SetCurrentAdministration()
{
    if (!m_psrvAdmin->GetUni(true))
    {
        MsgBoxOK(m_psrvAdmin->GetErrorMsg());
        return false;
    }

    GetDlgItem(IDC_STATIC_WEEKDAY)->SetWindowText(m_psrvAdmin->GetWochenTag());
    GetDlgItem(IDC_STATIC_TIMEOFF)->SetWindowText(m_psrvAdmin->GetLadeZeitAb());
    GetDlgItem(IDC_STATIC_TIMETO)->SetWindowText(m_psrvAdmin->GetLadeZeitBis());
    GetDlgItem(IDC_STATIC_SALEDEPARTMENT)->SetWindowText(ppString((long)m_psrvAdmin->GetLadeVZ()));
    GetDlgItem(IDC_STATIC_TOURID)->SetWindowText(m_psrvAdmin->GetTourID());
    GetDlgItem(IDC_STATIC_STATE)->SetWindowText(m_psrvAdmin->GetBundesLand());

    return true;
}

//--- SetDlgText -------------------------------------------------------------//

void CCPCallPlanUndertake::SetDlgText()
{
    ppDate Date = AeGetApp()->GetCurrentDate();
    ppTime Time = AeGetApp()->GetCurrentTime();

    GetDlgItem(IDC_STATIC_TIME)->SetWindowText((const char*)Time);
    GetDlgItem(IDC_STATIC_DATE)->SetWindowText((const char*)Date);
}

//--- CheckEntries -----------------------------------------------------------//

bool CCPCallPlanUndertake::CheckEntries(const bool bText/*=true*/, const bool bIsSera/*=true*/)
{
    m_srvUndertake.SetVertriebsZentrumNr(AeGetApp()->VzNr());
    m_srvUndertake.SetLadeDatum(m_psrvAdmin->GetLadeDatum());
    m_lLoadDate = m_srvUndertake.GetLadeDatum();
    if (m_srvUndertake.CheckEntries(bIsSera))
    {
        CString csText;
        CString csCount(ppString(m_srvUndertake.GetCount()));
        if (bText)
        {
            if (bIsSera) csText.Format(CResString::ex().getStrTblText(IDP_DEL_CALLPLAN_SERA), csCount.GetString());
            else csText.Format(CResString::ex().getStrTblText(IDP_DEL_CALLPLAN_PHON), csCount.GetString());
            if (MsgBoxYesNo(csText) != IDYES)
                return false;
        }
        else
        {
            csText.Format(CResString::ex().getStrTblText(IDP_COUNT_CALLPLAN), csCount.GetString(), (const char*)m_srvUndertake.GetLadeDatum());
            MsgBoxOK(csText);
        }
        m_lLoadDate = m_srvUndertake.GetLadeDatum();
    }
    else if (m_srvUndertake.GetErrorState() != ppError::is_notfound)
    {
        MsgBoxOK(m_srvUndertake.GetErrorMsg());
        return false;
    }
    m_srvUndertake.SetVertriebsZentrumNr(AeGetApp()->VzNr());
    return true;
}

//--- StartProgress-----------------------------------------------------------//

void CCPCallPlanUndertake::StartProgress(const CString& csText)
{
    m_dlgProgress.SetText(csText);
    if (m_dlgProgress.GetSafeHwnd() == 0)
        m_dlgProgress.Create();
}

//--- EndProgress ------------------------------------------------------------//

void CCPCallPlanUndertake::EndProgress()
{
    if (m_dlgProgress.GetSafeHwnd() != 0)
        m_dlgProgress.DestroyWindow();
}

//--- SetProgressCount -------------------------------------------------------//

void CCPCallPlanUndertake::SetProgressCount(const int iPos)
{
    if (m_dlgProgress.GetSafeHwnd() != 0)
        m_dlgProgress.SetProgress(iPos);
}

//--- LoadSeraPlan -----------------------------------------------------------//

bool CCPCallPlanUndertake::LoadSeraPlan()
{
    return LoadPlan(false);
}

//--- LoadPhonPlan -----------------------------------------------------------//

bool CCPCallPlanUndertake::LoadPhonPlan()
{
    return LoadPlan(true);
}

bool CCPCallPlanUndertake::LoadPlan(bool phonePlan)
{
    bool result = phonePlan ? CheckEntries(true, false) : CheckEntries();
    if (!result)
    {
        return false;
    }

    StartProgress(CResString::ex().getStrTblText(phonePlan ? IDS_PHONPLAN : IDS_SERAPLAN));
    SetProgressCount(20);
    m_srvUndertake.SetLadeDatum(m_lLoadDate);
    result = phonePlan ? m_srvUndertake.DeleteEntriesPhon() : m_srvUndertake.DeleteEntries();
    if (!result)
    {
        EndProgress();
        MsgBoxOK(m_srvUndertake.GetErrorMsg());
        return false;
    }

    SetProgressCount(40);
    m_srvUndertake.SetLadeDatum(m_lLoadDate);
    result = phonePlan ? m_srvUndertake.DeleteEventsPhon() : m_srvUndertake.DeleteEvents();
    if (!result)
    {
        EndProgress();
        MsgBoxOK(m_srvUndertake.GetErrorMsg());
        return false;
    }

    SetProgressCount(60);
    m_srvUndertake.SetLadeDatum(m_lLoadDate);
    result = phonePlan ? m_srvUndertake.UndertakePhon() : m_srvUndertake.Undertake();
    if (!result)
    {
        EndProgress();
        MsgBoxOK(m_srvUndertake.GetErrorMsg());
        return false;
    }

    SetProgressCount(90);
    result = phonePlan ? CheckEntries(false, false) : CheckEntries(false);
    if (!result)
    {
        return false;
    }

    Sleep(50);
    EndProgress();
    return true;
}

void CCPCallPlanUndertake::OnDatetimechangeDatetimeLoaddate(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
    CTime x;
    m_DateCtrl_LoadDate.GetTime(x);
    m_psrvAdmin->SetLadeDatum(x.GetYear()*10000 + x.GetMonth()*100 + x.GetDay());
    SetCurrentAdministration();

    *pResult = 0L;
}
