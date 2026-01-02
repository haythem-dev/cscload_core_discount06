// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZdpDruck.h"
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

int CServerDlg::GetServerMode()
{
	return m_nServerMode;
}

void CServerDlg::SetMaxServerNumer( int nr )
{
	m_nMaxServerNumber = nr;
}

int CServerDlg::GetCompressMode()
{
	return m_nCompressMode;
}

bool CServerDlg::GetFetchMode()
{
	return m_bBufferedFetch;
}

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers
/*
void CServerDlg::OnOK() 
{
	CString cName;
	m_SERVER.GetWindowText( cName );
	cName.TrimLeft();
	cName.TrimRight();
	if ( cName.IsEmpty() )
		CDialog::OnCancel();
	else
	{
		int iPos;
		m_nServerMode   = 0;
		m_nCompressMode = 0;
		m_bBufferedFetch = false;

		iPos = cName.Find( ' ' );
		if ( iPos != -1 )
		{
			CString cNr;
			cNr = cName.Mid( iPos + 1);
//			m_nServerMode = (int)( cName.GetAt( iPos + 1) - '0' );
			m_nServerMode = (int)( cNr.GetAt( 0 ) - '0' );
			if ( m_nServerMode < 0 || m_nServerMode > m_nMaxServerNumber ) 
				m_nServerMode = 0;
			if ( cNr.GetLength() > 1 ) 
			{
				m_nCompressMode = (int)( cNr.GetAt( 1 ) - '0' );
				if ( m_nCompressMode < 0 || m_nCompressMode > 2 )
					m_nCompressMode = 0;

				if ( cNr.GetLength() > 2 ) 
					m_bBufferedFetch = ( int)( cNr.GetAt( 2 ) - '0' ) == 1;
			}
			 
			cName = cName.Left( iPos );
		}

		iPos = -1;
		m_NewName = ParseString( cName, '@', &iPos );
		if ( iPos == -2 )
			m_Database = "";
		else
			m_Database = ParseString( cName, ' ', &iPos );
		CDialog::OnOK();
	}
}

*/

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

			m_nServerMode   = 2;
			m_nCompressMode = 2;
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