
//(c)---------- Customer service program -------------------------------------//
/*
   Source: PLocalOptions.cpp
   Author: A.Schmidt-Rehschuh
   made  : 12.03.2001

   declaration:
   Dialog: implementation file
*/
//(c)-------------------------------------------------------------------------//

//--- include ----------------------------------------------------------------//

#include "stdafx.h"
#include "MainFrm.h"
#include "PLocalOptions.h"

//----------------------------------------------------------------------------//
//--- constructors/Initialization --------------------------------------------//
//----------------------------------------------------------------------------//

//--- standard initialization ------------------------------------------------//

CPLocalOptions::CPLocalOptions(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CPLocalOptions::IDD, pParent)
{
    InitData();
}

//--- DoDataExchange ---------------------------------------------------------//

void CPLocalOptions::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_REACTIVATE, m_CButtonActivateWnd);
    DDX_Control(pDX, IDC_CHECK_PROBLEMCALLS, m_CButtonProblemCalls);
    DDX_Control(pDX, IDC_CHECK_CALLPLAN, m_CButtonCallplan);
    DDX_Control(pDX, IDC_EDIT_WARN_MIN_PROBLEMCALL, m_CEditWarnMinProblemcall);
    DDX_Control(pDX, IDC_EDIT_WARN_MIN, m_CEditWarnMin);
    DDX_Control(pDX, IDC_EDIT_WARN_COUNT, m_CEditWarnCount);
    DDX_Control(pDX, IDC_EDIT_AUTO_MIN, m_CEditAutoMin);
}

//--- dialogmember Initialize ------------------------------------------------//

BEGIN_MESSAGE_MAP(CPLocalOptions, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_AUTO_MIN, OnChangeEditAutoMin)
    ON_EN_CHANGE(IDC_EDIT_WARN_COUNT, OnChangeEditWarnCount)
    ON_EN_CHANGE(IDC_EDIT_WARN_MIN, OnChangeEditWarnMin)
    ON_EN_CHANGE(IDC_EDIT_WARN_MIN_PROBLEMCALL, OnChangeEditWarnMinProblemcall)
END_MESSAGE_MAP()

//----------------------------------------------------------------------------//
//--- public-methodes --------------------------------------------------------//
//----------------------------------------------------------------------------//

const bool CPLocalOptions::IsCallplanWarnOff() const
{
    return m_bCallplanOff;
}

const bool CPLocalOptions::IsProblemCallWarnOff() const
{
    return m_bProblemCallOff;
}

const bool CPLocalOptions::IsActivateWnd() const
{
    return m_ActivateWnd;
}

const int CPLocalOptions::GetAutoMinutes() const
{
    return m_uAutoMin;
}

const int CPLocalOptions::GetAutoMMSeconds() const
{
    return m_uAutoMin * 60 * 1000;
}

const int CPLocalOptions::GetWarnCounter() const
{
    return m_uWarnCount;
}

const int CPLocalOptions::GetCallplanWarnMinutes() const
{
    return m_uWarnMin;
}

const int CPLocalOptions::GetProblemCallWarnMinutes() const
{
    return m_uWarnMinProblemCall;
}

//----------------------------------------------------------------------------//
//--- CPLocalOptions message handlers (ClassWizard) --------------------------//
//----------------------------------------------------------------------------//

//--- (ClassWizard)OnInitDialog ----------------------------------------------//

BOOL CPLocalOptions::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    InitData();
    ShowData();
    return TRUE;
}

//--- (ClassWizard)OnOK ------------------------------------------------------//

void CPLocalOptions::OnOK()
{
    if (!SaveData())
    {
       MsgBoxOK(IDP_NOT_UPDATED);
       return;
    }

    CDialogMultiLang::OnOK();
}

//--- (ClassWizard)OnChangeEditAutoMin ---------------------------------------//

void CPLocalOptions::OnChangeEditAutoMin()
{
    AllgWertKontr(&m_CEditAutoMin, 2, 60);
}

//--- (ClassWizard)OnChangeEditWarnCount -------------------------------------//

void CPLocalOptions::OnChangeEditWarnCount()
{
    AllgWertKontr(&m_CEditWarnCount, 1, 20);
}

//--- (ClassWizard)OnChangeEditWarnMin ---------------------------------------//

void CPLocalOptions::OnChangeEditWarnMin()
{
    AllgWertKontr(&m_CEditWarnMin, 1, 60);
}

//--- (ClassWizard)OnChangeEditWarnMinProblemcall ----------------------------//

void CPLocalOptions::OnChangeEditWarnMinProblemcall()
{
    AllgWertKontr(&m_CEditWarnMinProblemcall, 1, 60);
}

//----------------------------------------------------------------------------//
//--- private methodes -------------------------------------------------------//
//----------------------------------------------------------------------------//

//---- ShowData --------------------------------------------------------------//

void CPLocalOptions::ShowData()
{
    m_CButtonCallplan.SetCheck(m_bCallplanOff);
    m_CButtonProblemCalls.SetCheck(m_bProblemCallOff);
    m_CButtonActivateWnd.SetCheck(m_ActivateWnd);
    ppString str = (long)m_uAutoMin;
    m_CEditAutoMin.SetWindowText(str.c_str());
    str = (long)m_uWarnCount;
    m_CEditWarnCount.SetWindowText(str.c_str());
    str = (long)m_uWarnMin;
    m_CEditWarnMin.SetWindowText(str.c_str());
    str = (long)m_uWarnMinProblemCall;
    m_CEditWarnMinProblemcall.SetWindowText(str.c_str());
}

//---- InitData --------------------------------------------------------------//

void CPLocalOptions::InitData()
{
    m_bCallplanOff    = atoi(GetRegistry(KEY_NAME_CALLPLAN)) ? true : false;
    m_bProblemCallOff = atoi(GetRegistry(KEY_NAME_PROBLEMCALLS)) ? true : false;
    m_ActivateWnd     = atoi(GetRegistry(KEY_NAME_ACTIVATEWND)) == 0 ? true : false;
    if ((m_uAutoMin = atoi(GetRegistry(KEY_NAME_AUTOMIN))) == 0)
        m_uAutoMin = 2;
    if ((m_uWarnCount = atoi(GetRegistry(KEY_NAME_WARNCOUNT))) == 0)
        m_uWarnCount = 5;
    if ((m_uWarnMin = atoi(GetRegistry(KEY_NAME_WARNMIN))) == 0)
        m_uWarnMin = 10;
    if ((m_uWarnMinProblemCall = atoi(GetRegistry(KEY_NAME_WARNMINPROLEMCALL))) == 0)
        m_uWarnMinProblemCall = 10;
}

//---- SaveData --------------------------------------------------------------//

bool CPLocalOptions::SaveData()
{
    CString csValue;

    csValue = m_CButtonCallplan.GetCheck() ? "1" : "0";
    if (!PutRegistry(KEY_NAME_CALLPLAN, csValue))
        return false;

    csValue = m_CButtonProblemCalls.GetCheck() ? "1" : "0";
    if (!PutRegistry(KEY_NAME_PROBLEMCALLS, csValue))
        return false;

    csValue = m_CButtonActivateWnd.GetCheck() ? "0" : "1"; //doppelte verneinung
    if (!PutRegistry(KEY_NAME_ACTIVATEWND, csValue))
        return false;

    if (!CheckEntry(m_CEditAutoMin, csValue))
        return false;
    else if (!PutRegistry(KEY_NAME_AUTOMIN, csValue))
       return false;

    if (!CheckEntry(m_CEditWarnCount, csValue))
       return false;
    else if (!PutRegistry(KEY_NAME_WARNCOUNT, csValue))
        return false;

    if (!CheckEntry(m_CEditWarnMin, csValue))
        return  false;
    else if (!PutRegistry(KEY_NAME_WARNMIN, csValue))
        return false;

    if (!CheckEntry(m_CEditWarnMinProblemcall, csValue))
        return false;
    else if (!PutRegistry(KEY_NAME_WARNMINPROLEMCALL, csValue))
        return false;
    InitData();
    return true;
}

//---- PutRegistry -----------------------------------------------------------//

bool CPLocalOptions::PutRegistry(const ppString& strKeyID, const ppString& strValue)
{
    HKEY hKey;

    if (RegCreateKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        RegSetValueEx(hKey, strKeyID.c_str(), 0, REG_SZ, (BYTE*)strValue.c_str(), strValue.length());
        RegCloseKey(hKey);
        return true;
    }
    return false;
}

//---- GetRegistry -----------------------------------------------------------//

const char* CPLocalOptions::GetRegistry(const ppString& strKeyID)
{
    HKEY hKey;
    DWORD len = sizeof(m_szBuf) - 1;

    if (RegOpenKey(HKEY_CURRENT_USER, KEY_PATH, &hKey) == ERROR_SUCCESS)
    {
        if (RegQueryValueEx(hKey, strKeyID.c_str(), 0, NULL, (BYTE*)m_szBuf, &len) == ERROR_SUCCESS)
        {
          m_szBuf[len-1] = '\0';
          return m_szBuf;
       }
    }

    strcpy(m_szBuf,"0");
    return m_szBuf;
}

//---- CheckEntry ------------------------------------------------------------//

const bool CPLocalOptions::CheckEntry(CEdit& CEditCheck, CString& csValue)
{
    CEditCheck.GetWindowText(csValue);
    if (csValue.IsEmpty())
    {
       CEditCheck.SetFocus();
       return false;
    }
    return true;
}
