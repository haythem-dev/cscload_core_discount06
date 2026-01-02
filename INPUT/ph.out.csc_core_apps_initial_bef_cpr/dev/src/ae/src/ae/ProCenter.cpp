// ProCenter.cpp : Implementierung von CProCenter
#include "stdafx.h"
#include "ProCenter.h"
#include "AeFView.h"
#include "DHPLogon.h"

/////////////////////////////////////////////////////////////////////////////
// CProCenter
CProCenter::CProCenter()
{
    TraceOnOff(FALSE);
}

CProCenter::~CProCenter()
{
}

void CProCenter::TraceOnOff(bool bTrace)
{
    CString msgText;
    msgText.Format("TraceOnOff: bTrace=%s\n", bTrace ? "true" : "false");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::TraceOnOff(bTrace);
}

void CProCenter::AgentLogOff()
{
    CString msgText;
    msgText.Format("AgentLogOff\n");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::AgentLogOff();
}

void CProCenter::AgentUnAvail(int ReasonKey)
{
    CString msgText;
    msgText.Format("AgentUnAvail, ReasonKey=%d\n", ReasonKey);
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::AgentUnAvail(ReasonKey);
}

void CProCenter::AgentAvail()
{
    CString msgText;
    msgText.Format("AgentAvail\n");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::AgentAvail();
}

void CProCenter::MakeCall(const CString& csDestinationNr)
{
    CString msgText;
    msgText.Format("MakeCall: DestinationNr=%s\n", csDestinationNr.GetString());
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::MakeCall(csDestinationNr);
}

void CProCenter::DisconnectCall()
{
    CString msgText;
    msgText.Format("DisconnectCall\n");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::DisconnectCall();
}

void CProCenter::AnswerCall()
{
    CString msgText;
    msgText.Format("AnswerCall\n");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::AnswerCall();
}

#ifdef _NEWHIPATH
void CProCenter::AcdAgentExitPostProc(long requeueCount)
{
    CString msgText;
    msgText.Format("AcdAgentExitPostProc: requeueCount=%ld\n", requeueCount);
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::AcdAgentExitPostProc(requeueCount);
}
#endif

void CProCenter::Transfer()
{
    CString msgText;
    msgText.Format("Transfer\n");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::Transfer();
}

void CProCenter::ReconnectCall()
{
    CString msgText;
    msgText.Format("ReconnectCall\n");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::ReconnectCall();
}

void CProCenter::SetPABXLINKMode4CB(
      const CString& strLocationID
    , const CString& strAgent
    , const CString& strNumber
    , const CString& strAdress_CB1
    , const UINT&    uiPort_CB1
    , const CString& strAdress_CB2
    , const UINT&    uiPort_CB2
    )
{
    CString msgText;
    msgText.Format("SetPABXLINKMode4CB: LocationID=%s, Agent=%s, Number=%s, Address_CB1=%s, Port_CB1=%d, Address_CB2=%s, Port_CB2=%d\n", strLocationID.GetString(), strAgent.GetString(), strNumber.GetString(), strAdress_CB1.GetString(), uiPort_CB1, strAdress_CB2.GetString(), uiPort_CB2);
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::SetPABXLINKMode4CB(strLocationID, strAgent, strNumber, strAdress_CB1, uiPort_CB1, strAdress_CB2, uiPort_CB2);
}

void CProCenter::SetPABXLINKMode(
      const CString& strLocationID
    , const CString& strAgent
    , const CString& strNumber
    )
{
    CString msgText;
    msgText.Format("SetPABXLINKMode: LocationID=%s, Agent=%s, Number=%s\n", strLocationID.GetString(), strAgent.GetString(), strNumber.GetString());
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::SetPABXLINKMode(strLocationID, strAgent, strNumber);
}

bool CProCenter::ServerConnect(
      const CString& strLocalServer
    , const UINT&    uiLocalServerPort
    , const UINT&    uiLocalMonitorPort
    , const UINT&    uiLocalMonitorInterval
    //, const CLoggingConfigData& logData = m_defaultLogConfig
    )
{
    CString msgText;
    msgText.Format("ServerConnect(before): LocalServer=%s, LocalServerPort=%d, LocalMonitorPort=%d, LocalMonitorInterval=%d\n", strLocalServer.GetString(), uiLocalServerPort, uiLocalMonitorPort, uiLocalMonitorInterval);
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    const bool retVal = CHPPCProxy::ServerConnect(strLocalServer, uiLocalServerPort, uiLocalMonitorPort, uiLocalMonitorInterval);

    msgText.Format("ServerConnect(after): retVal=%s\n", retVal ? "true" : "false");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    return retVal;
}

void CProCenter::ServerDisconnect()
{
    CString msgText;
    msgText.Format("ServerDisconnect\n");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::ServerDisconnect();
}

void CProCenter::AgentLogOn(
      const CString& strAgent
    , const CString& strUserPwd
    , const CString& strNumber
    )
{
    CString msgText;
    msgText.Format("AgentLogOn: Agent=%s, UserPwd=%s, Number=%s\n", strAgent.GetString(), strUserPwd.GetString(), strNumber.GetString());
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::AgentLogOn(strAgent, strUserPwd, strNumber);
}

void CProCenter::Consult(CString strNumber)
{
    CString msgText;
    msgText.Format("Consult: Number=%s\n", strNumber.GetString());
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::Consult(strNumber);
}

void CProCenter::BlindTransfer(CString strNumber)
{
    CString msgText;
    msgText.Format("BlindTransfer: Number=%s\n", strNumber.GetString());
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    CHPPCProxy::BlindTransfer(strNumber);
}

void CProCenter::SetUserAtWork(CString csWoher, BOOL bWork)
{
    CString msgText;
    msgText.Format("SetUserAtWork: Work=%s\n", bWork ? "true" : "false");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace(csWoher, "CProCenter::SetUserAtWork", msgText);

    if (!IsHiPathLogon())
    {
        return;
    }

    if (IsHiPathOpen())
    {
        if (bWork)
        {
            AeGetApp()->m_AeTrace.WriteTrace(csWoher, "CProCenter::SetUserAtWork", "Inside Hipath Work so set Pause Wish");
            SetHiPathPauseWished(TRUE);
        }
        else
        {
            AeGetApp()->m_AeTrace.WriteTrace(csWoher, "CProCenter::SetUserAtWork", "Inside Hipath Work so unset Pause Wish");
            SetHiPathPauseWished(FALSE);
        }
        return;
    }

    if (bWork)
    {
        if (IsHiPathPause())
        {
            AeGetApp()->m_AeTrace.WriteTrace(csWoher, "CProCenter::SetUserAtWork", "Set Busy but Pause is already set");
            return;
        }
        if (IsHiPathUserBusy())
        {
            AeGetApp()->m_AeTrace.WriteTrace(csWoher, "CProCenter::SetUserAtWork", "Set Busy but Busy is already set");
            return;
        }

        AeGetApp()->m_AeTrace.WriteTrace(csWoher, "CProCenter::SetUserAtWork", "AgentUnAvail and set Busy");
        AgentUnAvail(0);
        SetHiPathUserBusy(TRUE);
    }
    else
    {
        if (IsHiPathPause())
        {
            AeGetApp()->m_AeTrace.WriteTrace(csWoher, "CProCenter::SetUserAtWork", "Unset Busy but Pause is set");
            return;
        }

        AeGetApp()->m_AeTrace.WriteTrace(csWoher, "CProCenter::SetUserAtWork", "AgentAvail and unset OtherWork, Busy, Working and Pause Wish");
        AgentAvail();
        SetHiPathOtherWork(FALSE);
        SetHiPathUserBusy(FALSE);
        SetHiPathWorking(FALSE);
        SetHiPathPauseWished(FALSE);
    }
}

void CProCenter::OnServerConnected(int nServerType, int nServerState)
{
    CString msgText;
    msgText.Format("OnServerConnected: ServerType=%ld, ServerState=%ld\n", nServerType, nServerState);
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    if (nServerType == 2        // = Server_ConfigurationSynchronization
        && nServerState == 1)   // = ServerState_Connected
    {
        SetHiPathConnected(TRUE);

        AgentLogOn(GetAgentID(), GetAgentPwd(), GetNST());
    }
}

void CProCenter::OnServerDisconnected()
{
    CString msgText;
    msgText.Format("OnServerDisconnected\n");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    SetHiPathLogon(FALSE);
    SetHiPathConnected(FALSE);
}

void CProCenter::OnAgentLoggedOn(int agentState)
{
    CString msgText;
    msgText.Format("OnAgentLoggedOn: AgentState=%ld\n", agentState);
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    if (agentState == 0)
    {
        SetHiPathLogon(TRUE);
    }
    else if (agentState == 1)
    {
        MsgBoxOK( IDS_TXT_FEHLER_DBLPKT );
    }
    else if (agentState == 2)
    {
        MsgBoxOK( IDP_UNGUELT_PWD );
        CDHPLogon dlgHPLogon;
        dlgHPLogon.DoModal();
    }
    else if (agentState == 3)
    {
        MsgBoxOK( AETXT_FALSCH_NST );
        CDHPLogon dlgHPLogon;
        dlgHPLogon.DoModal();
    }
}


void CProCenter::OnAgentStateChanged(CAgentStateChange ev)
{
    CString woher;
    woher = "CProCenter::OnAgentStateChanged";
    CString msgText;
    msgText.Format("OnAgentStateChanged: "
                   "VoiceLogon=%ld "
                   "VoiceLogoff=%ld "
                   "Available=%ld "
                   "UnAvailable=%ld "
                   "Work=%ld "
                   "State=%ld "
                   "EmailLogon=%ld "
                   "EmailLogoff=%ld "
                   "WorkReason=%ld\n",
                   ev.GetVoiceLogon(),
                   ev.GetVoiceLogoff(),
                   ev.GetAvailable(),
                   ev.GetUnAvailable(),
                   ev.GetWork(),
                   ev.GetState(),
                   ev.GetEmailLogon(),
                   ev.GetEmailLogoff(),
                   ev.GetWorkReason());
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    if (ev.GetState() == AgentState_Unavailable) // 10
    {
        if (!IsHiPathUserBusy())
        {
            SetHiPathPause(TRUE);
        }
    }
    else if (ev.GetState() == AgentState_Working) // 11
    {
        if (!IsHiPathUserBusy())
        {
            SetHiPathUserBusy(TRUE);

            if (!IsHiPathPauseWished())
            {
                AfxGetMainWnd()->PostMessage(WM_HIPATHUSER, 0, 0);
            }
        }

        SetHiPathWorking(TRUE);
    }
    else if (ev.GetState() == AgentState_Available) // 9
    {
        if (IsHiPathLogon())
        {
            if (!IsHiPathUserBusy())
            {
                SetHiPathPause(FALSE);
            }
        }
    }
    else if (ev.GetState() == AgentState_Reserved) // 13
    {
        AfxMessageBox("Agent unknown");
    }
    else if (ev.GetState() == AgentState_LoggedOff) // 15
    {
        if (IsHiPathLogon())
        {
            AeGetApp()->m_AeTrace.WriteTrace(woher, "CProCenter", "AgentAvail");
            AgentAvail();
        }
    }
}


void CProCenter::OnError(CError ev)
{
    CString msgText;
    msgText.Format("OnError: Error=%s\n", ev.GetMessage().GetString());
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);
}


void CProCenter::OnPhoneRing(CPhoneRing ev)
{
    CString TelNr;
    CString Caption;
    CString msgText;
    msgText.Format("OnPhoneRing: "
                   "HandlingType=%ld "
                   "CallId=%s "
                   "ANI=%s "
                   "OrigANI=%s "
                   "DNIS=%s "
                   "CallTypeKey=%ld "
                   "CallTypeName=%s "
                   "Caption=%s "
                   "Priority=%ld "
                   "TimeInQueue=%ld\n",
                   ev.GetHandlingType(),
                   ev.GetCallId().GetString(),
                   ev.GetANI().GetString(),
                   ev.GetOrigANI().GetString(),
                   ev.GetDNIS().GetString(),
                   ev.GetCallTypeKey(),
                   ev.GetCallTypeName().GetString(),
                   ev.GetCaption().GetString(),
                   ev.GetPriority(),
                   ev.GetTimeInQueue());
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    TelNr = ev.GetOrigANI();
    AeGetApp()->Caption = ev.GetCaption();

    if (ev.GetHandlingType() != 1 || !AeGetApp()->IsDE()) // keine Direktreinrufe und nur in DE
    {
        SetDirectCall(TRUE);
    }
    else
    {
        SetDirectCall(FALSE);
    }

    if (TelNr.IsEmpty()) // Ohne Nummer
    {
        AeGetApp()->TelNr = TelNr;
    }
    else if (TelNr.GetAt(1) == '0') // extern mit Vorwahl (0 0XXX XXX...)
    {
        AeGetApp()->TelNr = TelNr.Right(TelNr.GetLength() - 1);
    }
    else if (TelNr.GetAt(0) == '0') // extern ohne Vorwahl (Ortsgespräch) (0 XXX...)
    {
        AeGetApp()->TelNr = TelNr.Right(TelNr.GetLength() - 1);
    }
    else // interner Anruf (XXX...)
    {
        AeGetApp()->TelNr = TelNr;
    }

    if (IsHiPathMesBoxActiv())
    {
        ::PostMessage(AeGetApp()->CallinWnd(), WM_COMMAND, IDCANCEL, 0);
    }

    ::PostMessage(AeGetApp()->m_pViewEing->GetSafeHwnd(), WM_PHONERING, 0, 0);
}


void CProCenter::OnPhoneStateChanged(CPhoneState ev)
{
    int state = ev.GetState();
    CString msgText;
    msgText.Format("OnPhoneStateChanged: "
                   "Make=%ld "
                   "Answer=%ld "
                   "Disconnect=%ld "
                   "Consult=%ld "
                   "Reconnect=%ld "
                   "Transfer=%ld "
                   "Conference=%ld "
                   "BlindTransfer=%ld "
                   "Hold=%ld "
                   "Retrieve=%ld "
                   "State=%ld\n",
                   ev.IsMakeCallEnabled() ? 1 : 0,
                   ev.IsAnswerCallEnabled() ? 1 : 0,
                   ev.IsDisconnectCallEnabled() ? 1 : 0,
                   ev.IsConsultCallEnabled() ? 1 : 0,
                   ev.IsReconnectCallEnabled() ? 1 : 0,
                   ev.IsTransferCallEnabled() ? 1 : 0,
                   ev.IsConferenceCallEnabled() ? 1 : 0,
                   ev.IsBlindTransferCallEnabled() ? 1 : 0,
                   ev.IsHoldCallEnabled() ? 1 : 0,
                   ev.IsRetrieveCallEnabled() ? 1 : 0,
                   ev.GetState());
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    SetHiPathCallActiv(ev.IsMakeCallEnabled() ? FALSE : TRUE);

    if (state == 5) // Anruf angenommen (RROnThePhoneState)
    {
        if (IsHiPathMesBoxActiv())
        {
            SetHiPathMesBoxActiv(FALSE);
            ::PostMessage(AeGetApp()->CallinWnd(), WM_COMMAND, IDOK, 0);
        }
        else if (AeGetApp()->ConnectWnd() != NULL)
        {
            ::PostMessage(AeGetApp()->ConnectWnd(), WM_COMMAND, IDCANCEL, 0);
        }

        SetHiPathCallActiv(TRUE);
        SetHiPathOpen(TRUE);
    }
    else if (state == 6) // Hörer aufgelegt (RRAgentHangUp)
    {
        SetHiPathOpen(FALSE);

        if (IsHiPathWorking() || IsHiPathUserBusy())
        {
            if (!(CAeDoc*)((CAeFView*)AeGetApp()->m_pViewEing)->GetDocument()->IsModified())
            {
                AfxGetMainWnd()->PostMessage(WM_HIPATHUSER, 0, 0);
            }
        }

        if (IsHiPathPauseWished() && !IsHiPathCalled())
        {
            AfxGetMainWnd()->PostMessage(WM_HIPATHUSER, 1, 0);
        }

        SetHiPathCalled(FALSE);

        if (IsHiPathMesBoxActiv())
        {
            ::PostMessage(AeGetApp()->CallinWnd(), WM_COMMAND, IDCANCEL, 0);
        }

        SetHiPathKndNr(0);
        SetHiPathVzNr(0);

        ::PostMessage(((CFrameWndMultiLang*)AeGetApp()->m_pMainWnd)->GetActiveView()->GetSafeHwnd(), WM_RENEW, 0, 0);
    }
    else if (state == 18) // tbc: Anruf Übergabe? (RRConsult)
    {
        if (AeGetApp()->IsBackrouting())
        {
            AeGetApp()->IsBackrouting = false;
            ::PostMessage(AeGetApp()->m_pViewEing->GetSafeHwnd(), WM_CONSULT, 0, 0);
        }
    }
}

void CProCenter::OnPhoneTransfer(CPhoneTransfer ev)
{
    CString msgText;
    msgText.Format("OnPhoneTransfer: "
                   "HandlingType=%ld "
                   "CallId=%s "
                   "ANI=%s "
                   "OrigANI=%s "
                   "DNIS=%s "
                   "OrigDNIS=%s "
                   "GetTransferTargetId=%s "
                   "Caption=%s ",
                   ev.GetHandlingType(),
                   ev.GetCallId().GetString(),
                   ev.GetANI().GetString(),
                   ev.GetOrigANI().GetString(),
                   ev.GetDNIS().GetString(),
                   ev.GetOrigDNIS().GetString(),
                   ev.GetCaption().GetString(),
                   ev.GetTransferTargetId().GetString());
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);
}

void CProCenter::OnPhoneConsult()
{
    CString msgText;
    msgText.Format("OnPhoneConsult\n");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);
}

void CProCenter::OnPhoneTransferred()
{
    CString msgText;
    msgText.Format("OnPhoneTransferred\n");
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

    if (AeGetApp()->ConnectWnd() != NULL)
    {
        ::PostMessage(AeGetApp()->ConnectWnd(), WM_COMMAND, IDCANCEL, 0);
    }
}

void CProCenter::OnContactStateChanged(bool exitPostProcEnabled, int requeueCount)
{
    CString msgText;
    msgText.Format("OnContactStateChanged: exitPostProcEnabled=%s, requeueCount=%d\n", exitPostProcEnabled ? "true" : "false", requeueCount);
    //TRACE(msgText);
    AeGetApp()->m_AeTrace.WriteTrace("", "", msgText);

#ifdef _NEWHIPATH
    CString woher;
    woher = "CProCenter::OnContactStateChanged";

    AeGetApp()->IsExitPostProcEnabled = exitPostProcEnabled;

    if (exitPostProcEnabled)
    {
        AeGetApp()->RequeueCount = requeueCount;

        if (!(CAeDoc*)((CAeFView*)AeGetApp()->m_pViewEing)->GetDocument()->IsModified())
        {
            if (IsHiPathPause() && !IsHiPathUserBusy())
            {
                AeGetApp()->m_AeTrace.WriteTrace(woher, "CProCenter", "IsHiPathPause");
            }
            else
            {
                if (IsHiPathOtherWork())
                {
                    AeGetApp()->m_AeTrace.WriteTrace(woher, "CProCenter", "IsHiPathOtherWork");
                    SetUserAtWork(woher, FALSE);
                    SetHiPathOtherWork(FALSE);
                }
                else
                {
                    AeGetApp()->m_AeTrace.WriteTrace(woher, "CProCenter", "AcdAgentExitPostProc");

                    AcdAgentExitPostProc(AeGetApp()->RequeueCount());
                    SetHiPathUserBusy(FALSE);
                    SetHiPathWorking(FALSE);
                    SetHiPathPauseWished(FALSE);
                }
            }
        }
        else
        {
            AeGetApp()->m_AeTrace.WriteTrace(woher, "CProCenter", "Order is open");
        }
    }
#else
    exitPostProcEnabled;
    requeueCount;
#endif
}