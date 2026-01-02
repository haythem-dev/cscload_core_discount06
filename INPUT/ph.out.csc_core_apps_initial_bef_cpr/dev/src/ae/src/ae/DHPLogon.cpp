// DHPLogon.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "DHPLogon.h"
#include <filinf.h>
#include <comutil.h>

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDHPLogon


CDHPLogon::CDHPLogon(CWnd* pParent /*=NULL*/)
    : CDialogMultiLang(CDHPLogon::IDD, pParent)
{
    m_csID = _T("");
    m_csNST = _T("");
    m_csPasswd = _T("");
}


void CDHPLogon::DoDataExchange(CDataExchange* pDX)
{
    CDialogMultiLang::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_PASSWD, m_edit_Passwd);
    DDX_Control(pDX, IDC_EDIT_NST, m_edit_NST);
    DDX_Control(pDX, IDC_EDIT_HPBRANCH, m_edit_HPBRANCH);
    DDX_Control(pDX, IDC_EDIT_ID, m_edit_ID);
    DDX_Text(pDX, IDC_EDIT_ID, m_csID);
    DDX_Text(pDX, IDC_EDIT_NST, m_csNST);
    DDX_Text(pDX, IDC_EDIT_HPBRANCH, m_csHPBRANCH);
    DDX_Text(pDX, IDC_EDIT_PASSWD, m_csPasswd);
    DDX_Control(pDX, IDC_CHECK_HIPATH, m_CBHiPath);
    DDX_Control(pDX, IDC_CHECK_LYNC, m_CBLync);
}


BEGIN_MESSAGE_MAP(CDHPLogon, CDialogMultiLang)
    ON_EN_CHANGE(IDC_EDIT_HPBRANCH, OnChangeEditHPBranch)
    ON_BN_CLICKED(IDC_CHECK_HIPATH, &CDHPLogon::OnBnClickedCheckHipath)
    ON_BN_CLICKED(IDC_CHECK_LYNC, &CDHPLogon::OnBnClickedCheckLync)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CDHPLogon

BOOL CDHPLogon::OnInitDialog()
{
    CDialogMultiLang::OnInitDialog();

    if (AeGetApp()->IsDE())
    {
        GetDlgItem( IDC_EDIT_HPBRANCH )->EnableWindow(TRUE);
        GetDlgItem( IDC_EDIT_HPBRANCH )->ShowWindow(SW_SHOW);
        GetDlgItem( IDC_STATIC_HPBRANCH )->EnableWindow(TRUE);
        GetDlgItem( IDC_STATIC_HPBRANCH )->ShowWindow(SW_SHOW);
    }
    GetDlgItem(IDC_CHECK_HIPATH)->EnableWindow(FALSE);
    GetDlgItem(IDC_CHECK_HIPATH)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_CHECK_LYNC)->EnableWindow(FALSE);
    GetDlgItem(IDC_CHECK_LYNC)->ShowWindow(SW_HIDE);
#ifdef _DEBUG
    GetDlgItem(IDC_CHECK_HIPATH)->EnableWindow(TRUE);
    GetDlgItem(IDC_CHECK_HIPATH)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_CHECK_LYNC)->EnableWindow(TRUE);
    GetDlgItem(IDC_CHECK_LYNC)->ShowWindow(SW_SHOW);

    if (AeGetApp()->TelefonieTyp() == 1)
    {
        m_CBLync.SetCheck(BST_CHECKED);
        m_CBHiPath.SetCheck(BST_UNCHECKED);
    }
    else
    {
        m_CBLync.SetCheck(BST_UNCHECKED);
        m_CBHiPath.SetCheck(BST_CHECKED);
    }
#endif

    m_csID = GetAeUser().GetAgentID();
    m_csNST = AeGetApp()->m_ProCenter.GetNST();
    m_csHPBRANCH.Format("%d", AeGetApp()->ProcenterBranchno());
    UpdateData(FALSE);

    if (!m_csID.IsEmpty())
    {
        GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
        return FALSE;
    }

    return TRUE;
}

void CDHPLogon::OnOK()
{
    //TRACE("CDHPLogon::OnOK\n");
    AeGetApp()->m_AeTrace.WriteTrace("", "", "CDHPLogon::OnOK\n");

    UpdateData(TRUE);
    BeginWaitCursor();
    AeGetApp()->m_ProCenter.SetNST(m_csNST);
    AeGetApp()->ProcenterBranchno = static_cast<short>(atoi(m_csHPBRANCH));
    AeGetApp()->m_ProCenter.SetAgentID(m_csID);
    AeGetApp()->m_ProCenter.SetAgentPwd(m_csPasswd);

    AeGetApp()->TelefonieTyp = (m_CBHiPath.GetCheck() == BST_CHECKED) ? 0 : 1;

    if (!AeGetApp()->m_ProCenter.IsHiPathConnected())
    {
        if (AeGetApp()->ProcenterBranchno() != AeGetApp()->VzNr())
        {
            CFILINF filinf;
            filinf.s.FILIALNR = AeGetApp()->ProcenterBranchno();
            BeginWaitCursor();
            filinf.Server(AafilGet_filiale_Procenter);
            AllgEntfSpaces(filinf.s.PROCENTERNAME);
            AllgEntfSpaces(filinf.s.BALANCE1);
            AllgEntfSpaces(filinf.s.BALANCE2);
            AllgEntfSpaces(filinf.s.PROCENTERLOCATION);
            AeGetApp()->ProCenterName = filinf.s.PROCENTERNAME;
            AeGetApp()->ProCenterLocation = filinf.s.PROCENTERLOCATION;
            AeGetApp()->Balance1 = filinf.s.BALANCE1;
            AeGetApp()->Balance2 = filinf.s.BALANCE2;
        }

        CString cti_servername = AeGetApp()->ProCenterName();
        CString cti_location   = AeGetApp()->ProCenterLocation();
        CString cti_balance1   = AeGetApp()->Balance1();
        CString cti_balance2   = AeGetApp()->Balance2();
        UINT cti_serverport;
        UINT cti_monitorport;
        UINT cti_monitorintevall;
        UINT cti_balance1port;
        UINT cti_balance2port;

        if (!cti_location.IsEmpty())
        {
            cti_serverport      = 17010;
            cti_balance1port    = 20001;
            cti_balance2port    = 20001;
            cti_monitorport     = 5200;
            cti_monitorintevall = 3000;
            if (!cti_balance1.IsEmpty())
            {
    // mit Connect balancing
                AeGetApp()->m_ProCenter.SetPABXLINKMode4CB(
                      cti_location
                    , m_csID
                    , m_csNST
                    , cti_balance1
                    , cti_balance1port
                    , cti_balance2
                    , cti_balance2port );
            }
            else
            {
                AeGetApp()->m_ProCenter.SetPABXLINKMode(
                      cti_location
                    , m_csID
                    , m_csNST );
            }
        }
        else
        {
            cti_serverport      = 5100;
            cti_monitorport     = 5200;
            cti_monitorintevall = 3000;
        }

        const bool success = AeGetApp()->m_ProCenter.ServerConnect(cti_servername, cti_serverport, cti_monitorport, cti_monitorintevall);
        if (!success)
        {
            AfxMessageBox("Failed");
            EndWaitCursor();
            CDialogMultiLang::OnCancel();
            return;
        }

        if (!AeGetApp()->IsLogging())
        {
            AeGetApp()->m_ProCenter.TraceOnOff(FALSE);
        }
    }
    else
    {
        AeGetApp()->m_ProCenter.AgentLogOn(
              AeGetApp()->m_ProCenter.GetAgentID()
            , AeGetApp()->m_ProCenter.GetAgentPwd()
            , AeGetApp()->m_ProCenter.GetNST() );
    }

    EndWaitCursor();

    CDialogMultiLang::OnOK();
}

void CDHPLogon::OnChangeEditHPBranch()
{
    AllgWertKontr(&m_edit_HPBRANCH, MAXIMUM_FILIALNR);
    return;
}


void CDHPLogon::OnBnClickedCheckHipath()
{
    if (m_CBHiPath.GetCheck() == BST_CHECKED)
    {
        m_CBLync.SetCheck(BST_UNCHECKED);
        m_CBHiPath.SetCheck(BST_CHECKED);
    }
    else
    {
        m_CBLync.SetCheck(BST_CHECKED);
        m_CBHiPath.SetCheck(BST_UNCHECKED);
    }
}


void CDHPLogon::OnBnClickedCheckLync()
{
    if (m_CBLync.GetCheck() == BST_CHECKED)
    {
        m_CBLync.SetCheck(BST_CHECKED);
        m_CBHiPath.SetCheck(BST_UNCHECKED);
    }
    else
    {
        m_CBLync.SetCheck(BST_UNCHECKED);
        m_CBHiPath.SetCheck(BST_CHECKED);
    }
}
