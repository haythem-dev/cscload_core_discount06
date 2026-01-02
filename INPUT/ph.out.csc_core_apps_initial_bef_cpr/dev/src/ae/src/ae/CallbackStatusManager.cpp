#include "stdafx.h"
#include "CallbackStatusManager.h"

CCallbackStatusManager::CCallbackStatusManager()
{
    CCALLBACKSTATUS  servStatus;
    short            statusID;
    ppString         strStatusName;
    short            statusTag;

    for (;;)
    {
        servStatus.SelectAll();
        if (servStatus.rc == SRV_SQLNOTFOUND)
        {
            servStatus.CloseCursor();
            break;
        }
        statusID = servStatus.GetStatusID();
        servStatus.GetStatusName(strStatusName);
        statusTag = servStatus.GetStatusTag();
        m_vecCallbackStatus.push_back(CallbackStatus(statusID, strStatusName, statusTag));
    }
}

void CCallbackStatusManager::FillCombobox(CComboBox& combobox)
{
    for (size_t  i = 0; i < m_vecCallbackStatus.size(); ++i)
    {
        combobox.AddString(m_vecCallbackStatus[i].STATUSNAME.c_str());
    }
}

short CCallbackStatusManager::GetOpenStatusID()
{
    for (size_t i = 0; i < m_vecCallbackStatus.size(); ++i)
    {
        if (m_vecCallbackStatus[i].STATUSTAG == CALLBACKSTATUS_TAG_OPEN)
        {
            return m_vecCallbackStatus[i].STATUSID;
        }
    }
    return -1;
}

bool CCallbackStatusManager::IsCloseStatus(short statusID)
{
    for (size_t i = 0; i < m_vecCallbackStatus.size(); i++)
    {
        if (m_vecCallbackStatus[i].STATUSID == statusID)
        {
            return (m_vecCallbackStatus[i].STATUSTAG == CALLBACKSTATUS_TAG_CLOSE);
        }
    }
    return false;
}

short CCallbackStatusManager::GetStatusID(ppString statusName)
{
    for (size_t i = 0; i < m_vecCallbackStatus.size(); i++)
    {
        if (m_vecCallbackStatus[i].STATUSNAME == statusName)
        {
            return m_vecCallbackStatus[i].STATUSID;
        }
    }
    return -1;
}

ppString CCallbackStatusManager::GetStatusName(short statusID)
{
    for (size_t i = 0; i < m_vecCallbackStatus.size(); i++)
    {
        if (m_vecCallbackStatus[i].STATUSID == statusID)
        {
            return  m_vecCallbackStatus[i].STATUSNAME;
        }
    }
    return ppString();
}

bool CCallbackStatusManager::GetIsCBStatusUsed()
{
    bool bRet = false;
    CPARAMETER callbackPara;
    callbackPara.SetFilialnr(0);
    callbackPara.SetProgrammname("callbackeditor");
    callbackPara.SetZweck("statusvisibility");
    callbackPara.SetParametername("CountryVisibility");
    if (callbackPara.SelParameter() == SRV_OK)
    {
        bRet = (callbackPara.GetWert() == 1);
    }
    return bRet;
}