#pragma once;

// ProCenter.h : Deklaration von CProCenter

#pragma warning( push )
#pragma warning( disable: 4100) //unreferenced formal parameter
#include "HPPCProxy.h"
#pragma warning( pop )

/////////////////////////////////////////////////////////////////////////////
// CProCenter
class CProCenter : private CHPPCProxy
{
private:
    BOOL m_bHiPathConnected;        //Mit Hipath connected
    BOOL m_bHiPathLogon;            //An Hipath angemeldet
    BOOL m_bHiPathPause;            //Pause an Hipath gemeldet
    BOOL m_bHiPathUserBusy;         //User ist beschäftigt Pause an Hipath gemeldet
    BOOL m_bHiPathMesBoxActiv;      //MessageBox ausgegeben wg. Anruf
    BOOL m_bHiPathOpen;             //Auftrag durch Hipath-Anruf eröffnet
    BOOL m_bHiPathCallActiv;        //Im Gespräch
    BOOL m_bHiPathPauseWished;      //Pause an Hipath gewünscht
    BOOL m_bHiPathOtherWork;        //Agentunavailable aufgrund anderer Tätigkeit
    BOOL m_bHiPathWorking;          //Workingstatus von Hipath empfangen
    BOOL m_bHiPathCalled;           //Anruf von Hipath empfangen

    BOOL m_bDirectCall;             // Direktanruf

    long m_lHiPathKndNr;            // Kundennr. des reinrufenden Kunden
    short m_sHiPathVzNr;            // Vznr. des reinrufenden Kunden

    CString m_csNST;                //Nebenstellennr. von Hicom
    CString m_csAgentID;            //Agent-Id von Hicom
    CString m_csAgentPwd;           //Agent-Password von Hicom

public:
    CProCenter();
    virtual ~CProCenter();

    BOOL IsHiPathConnected() { return m_bHiPathConnected; }
    BOOL IsHiPathLogon() { return m_bHiPathLogon; }
    BOOL IsHiPathPause() { return m_bHiPathPause; }
    BOOL IsHiPathUserBusy() { return m_bHiPathUserBusy; }
    BOOL IsHiPathMesBoxActiv() { return m_bHiPathMesBoxActiv; }
    BOOL IsHiPathOpen() { return m_bHiPathOpen; }
    BOOL IsHiPathCallActiv() { return m_bHiPathCallActiv; }
    BOOL IsHiPathPauseWished() { return m_bHiPathPauseWished; }
    BOOL IsHiPathOtherWork() { return m_bHiPathOtherWork; }
    BOOL IsHiPathWorking() { return m_bHiPathWorking; }
    BOOL IsHiPathCalled() { return m_bHiPathCalled; }

    void SetHiPathConnected(BOOL b) { m_bHiPathConnected = b; }
    void SetHiPathLogon(BOOL b) { m_bHiPathLogon = b; }
    void SetHiPathPause(BOOL b) { m_bHiPathPause = b; }
    void SetHiPathUserBusy(BOOL b) { m_bHiPathUserBusy = b; }
    void SetHiPathMesBoxActiv(BOOL b) { m_bHiPathMesBoxActiv = b; }
    void SetHiPathOpen(BOOL b) { m_bHiPathOpen = b; }
    void SetHiPathCallActiv(BOOL b) { m_bHiPathCallActiv = b; }
    void SetHiPathPauseWished(BOOL b) { m_bHiPathPauseWished = b; }
    void SetHiPathOtherWork(BOOL b) { m_bHiPathOtherWork = b; }
    void SetHiPathWorking(BOOL b) { m_bHiPathWorking = b; }
    void SetHiPathCalled(BOOL b) { m_bHiPathCalled = b; }

    void SetDirectCall(BOOL b) { m_bDirectCall = b; }
    BOOL IsDirectCall() { return m_bDirectCall; }

    long GetHiPathKndNr() { return m_lHiPathKndNr; }
    void SetHiPathKndNr(long l) { m_lHiPathKndNr = l; }

    void SetHiPathVzNr(short s) { m_sHiPathVzNr = s; }
    short GetHiPathVzNr() { return m_sHiPathVzNr; }

    CString GetNST() { return m_csNST; }
    CString GetAgentID() { return m_csAgentID; }
    CString GetAgentPwd() { return m_csAgentPwd; }

    void SetNST(CString s) { m_csNST = s; }
    void SetAgentID(CString s) { m_csAgentID = s; }
    void SetAgentPwd(CString s) { m_csAgentPwd = s; }

    void SetUserAtWork(CString csWoher, BOOL bWork);    //Setzen Userbusy wenn an Hipath angemeldet

    void TraceOnOff(bool bTrace);
    void AgentLogOff();
    void AgentUnAvail(int ReasonKey);
    void AgentAvail();
    void MakeCall(const CString& csDestinationNr);
    void DisconnectCall();
    void AnswerCall();

#ifdef _NEWHIPATH
    void AcdAgentExitPostProc(long requeueCount);
#endif

    void Transfer();
    void ReconnectCall();

    void SetPABXLINKMode4CB(
        const CString& strLocationID,
        const CString& strAgent,
        const CString& strNumber,
        const CString& strAdress_CB1,
        const UINT&    uiPort_CB1,
        const CString& strAdress_CB2,
        const UINT&    uiPort_CB2);

    void SetPABXLINKMode(
        const CString& strLocationID,
        const CString& strAgent,
        const CString& strNumber);

    bool ServerConnect(
        const CString& strLocalServer,
        const UINT&    uiLocalServerPort,
        const UINT&    uiLocalMonitorPort,
        const UINT&    uiLocalMonitorInterval);

    void ServerDisconnect();
    void AgentLogOn(const CString& strAgent, const CString& strUserPwd, const CString& strNumber);
    void Consult(CString strNumber);
    void BlindTransfer(CString strNumber);

    void OnServerConnected(int nServerType, int nServerState);
    void OnServerDisconnected();

    void OnAgentLoggedOn(int agentState);
    void OnAgentStateChanged(CAgentStateChange ev);
    void OnPhoneStateChanged(CPhoneState ev);
    void OnPhoneRing(CPhoneRing ev);
    void OnPhoneConsult();
    void OnPhoneTransfer(CPhoneTransfer ev);
    void OnPhoneTransferred();
    void OnContactStateChanged(bool exitPostProcEnabled, int requeueCount);

    void OnError(CError ev);
};
