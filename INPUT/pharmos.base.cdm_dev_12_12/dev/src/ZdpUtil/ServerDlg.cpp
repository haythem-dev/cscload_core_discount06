// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZdpUtil.h"
#include "ServerDlg.h"
#include <phxlib/phxutil.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog


CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerDlg)
	//}}AFX_DATA_INIT
	m_nMaxServerNumber = 0;
}


void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
	DDX_Control(pDX, IDC_SERVER_SERVER, m_SERVER);
	DDX_Control(pDX, IDC_SERVER_DBASE,  m_DBASE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



CString CServerDlg::GetServerName()
{
	return m_NewServerName;
}

void CServerDlg::SetServerName( CString Name )
{
	m_NewServerName = Name;
}

CString CServerDlg::GetDbaseName()
{
	return m_NewDbaseName;
}

void CServerDlg::SetDbaseName( CString Name )
{
	m_NewDbaseName = Name;
}

void CServerDlg::SetMaxServerNumer( int nr )
{
	m_nMaxServerNumber = nr;
}


/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers

void CServerDlg::OnOK() 
{

	CWnd *wnd = GetFocus();
	if ( wnd == &m_SERVER )
		m_DBASE.SetFocus();
	else
	{
		CString cServer;
		CString cDbase;
		m_SERVER.GetWindowText( cServer );
		cServer.TrimLeft();
		cServer.TrimRight();
		m_DBASE.GetWindowText( cDbase );
		cDbase.TrimLeft();
		cDbase.TrimRight();

		if ( cServer.IsEmpty() && cDbase.IsEmpty() )
			CDialog::OnCancel();
		else if ( !cServer.IsEmpty() && !cDbase.IsEmpty() )
		{
			m_NewServerName = cServer;
			m_NewDbaseName = cDbase;

			CDialog::OnOK();
		}
		else
			AfxMessageBox( "Servername und Databasename\nbeide leer oder beide nicht leer" );
	}
}

BOOL CServerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_SERVER.SetWindowText( m_NewServerName );
	m_DBASE.SetWindowText ( m_NewDbaseName );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}