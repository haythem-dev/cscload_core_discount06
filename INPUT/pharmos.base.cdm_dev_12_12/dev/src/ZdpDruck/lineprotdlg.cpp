// LineprotDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "zdpdruck.h"
#include "LineprotDlg.h"
#include <libscsvoodoo/libscsvoodoo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CLineprotDlg 


CLineprotDlg::CLineprotDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLineprotDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineprotDlg)
	m_strFile = _T("");
	//}}AFX_DATA_INIT
}


void CLineprotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineprotDlg)
	DDX_Text(pDX, IDC_PROT_FILE, m_strFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineprotDlg, CDialog)
	//{{AFX_MSG_MAP(CLineprotDlg)
	ON_BN_CLICKED(IDC_PROT_MODE1, OnProtMode1)
	ON_BN_CLICKED(IDC_PROT_MODE2, OnProtMode2)
	ON_BN_CLICKED(IDC_PROT_MODE3, OnProtMode3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////
// implementation

void CLineprotDlg::InitVars( int nProtocolMode, CString strProtocolFile, CString header )
{
	m_nProtocolMode     = nProtocolMode;
	m_strProtocolFile   = strProtocolFile;
	m_strHeader         = header;
}

void CLineprotDlg::GetVars ( int &nProtocolMode, CString& strProtocolFile )
{
	nProtocolMode     = m_nProtocolMode;
	strProtocolFile   = m_strProtocolFile;
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CLineprotDlg 

BOOL CLineprotDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText( m_strHeader );

	if ( m_nProtocolMode == UDUPROT_MODE_1 )
		((CButton *)GetDlgItem( IDC_PROT_MODE1 ))->SetCheck( 1 );
	else if ( m_nProtocolMode == UDUPROT_MODE_2 )
		((CButton *)GetDlgItem( IDC_PROT_MODE2 ))->SetCheck( 1 );
	else
		((CButton *)GetDlgItem( IDC_PROT_MODE3 ))->SetCheck( 1 );
	m_strFile = m_strProtocolFile;
	UpdateData( FALSE );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CLineprotDlg::OnOK() 
{
	CString strFile;
	UpdateData( TRUE );

	strFile = m_strFile;
	strFile.TrimLeft();
	strFile.TrimRight();

	if ( m_nProtocolMode == UDUPROT_MODE_0 )
		strFile.Empty();

	if ( m_nProtocolMode != UDUPROT_MODE_0 && strFile.IsEmpty() )
	{
		AfxMessageBox( "Bitte Pfadname der Protokolldatei eingeben" );
		return;
	}

	m_strProtocolFile = strFile;
	
	CDialog::OnOK();
}

void CLineprotDlg::OnProtMode1() 
{
	m_nProtocolMode = UDUPROT_MODE_1;
}

void CLineprotDlg::OnProtMode2() 
{
	m_nProtocolMode = UDUPROT_MODE_2;
}

void CLineprotDlg::OnProtMode3() 
{
	m_nProtocolMode = UDUPROT_MODE_0;
}
