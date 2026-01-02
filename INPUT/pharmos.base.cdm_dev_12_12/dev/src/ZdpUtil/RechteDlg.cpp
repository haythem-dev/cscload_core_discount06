// RechteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZdpUtil.h"
#include "RechteDlg.h"
#include <phxlib/AllgRechte.h>
// #include <wudu.h>
#include <libscsvoodoo/libscsvoodoo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRechteDlg dialog


CRechteDlg::CRechteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRechteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRechteDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	InitButtons();
	m_bStandardEngine = false;
	theApp = ((CZdpUtilApp*)AfxGetApp());
}

CRechteDlg::~CRechteDlg()
{
	FreeButtons();
//	ChangeToPhosix();
	ChangeToDefaultBase( );
}

void CRechteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRechteDlg)
	DDX_Control(pDX, IDC_RECHTE_BP_SUPER, m_SUPER);
	DDX_Control(pDX, IDC_RECHTE_CK_SUBSUPER, m_SUBSUPER);
	DDX_Control(pDX, IDC_RECHTE_BP_PASTE, m_PASTE);
	DDX_Control(pDX, IDC_RECHTE_BP_COPY, m_COPY);
	DDX_Control(pDX, IDC_RECHTE_BP_SPEICHERN, m_SPEICHERN);
	DDX_Control(pDX, IDC_RECHTE_CB_USERNAME, m_USERNAME);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRechteDlg, CDialog)
	//{{AFX_MSG_MAP(CRechteDlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RECHTE_BP_SPEICHERN, OnRechteBpSpeichern)
	ON_CBN_CLOSEUP(IDC_RECHTE_CB_USERNAME, OnCloseupRechteCbUsername)
	ON_BN_CLICKED(IDC_RECHTE_BP_COPY, OnRechteBpCopy)
	ON_BN_CLICKED(IDC_RECHTE_BP_PASTE, OnRechteBpPaste)
	ON_BN_CLICKED(IDC_RECHTE_BP_SUPER, OnRechteBpSuper)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////7
// StandardEngine 


long CRechteDlg::ChangeToDatabase( CString Database )
{
	long s;
	CString sql;

	if ( !m_bStandardEngine )
		return 0;

	sql = "database " + Database;
	s = SqlExecuteImm( sql );	
	if ( s != 0 )
	{
		CString cErrmld;
		cErrmld  = "Wechsel zu ";
		cErrmld += Database;
		cErrmld += ":\n";
		cErrmld += DynErrmld();
		AfxMessageBox( cErrmld );
	}
	return s;
}

long CRechteDlg::ChangeToDefaultBase( )
{
//	return ChangeToDatabase( "regioek" );
	return 0;
}

long CRechteDlg::ChangeToPhosix( )
{
//	return ChangeToDatabase( "phosix" );
	return 0;
}

char* CRechteDlg::GetDatabase()
{
	if ( m_bStandardEngine )
		return "";
//	return "phosix:";
	return "";	
}

/////////////////////////////////////////////////////////////////////////////
// Buttons

void CRechteDlg::InitButtons()
{
	m_cButNone    = NULL;
	m_cButRead    = NULL;
	m_cButWrite   = NULL;
	m_cStMenPunkt = NULL;
	m_cStRegion   = NULL;
}

void CRechteDlg::FreeButtons()
{
	int i;
	int anz = m_MenAnz*m_RegAnz;
	if ( m_cButNone != NULL )
	{
		for ( i = 0; i < anz; i++ )
			if ( m_cButNone[i] != NULL ) 
				delete m_cButNone[i];
		free( m_cButNone );
	}

	if ( m_cButRead != NULL )
	{
		for ( i = 0; i < anz; i++ )
			if ( m_cButRead[i] != NULL ) 
				delete m_cButRead[i];
		free( m_cButRead );
	}

	if ( m_cButWrite != NULL )
	{
		for ( i = 0; i < anz; i++ )
			if ( m_cButWrite[i] != NULL ) 
				delete m_cButWrite[i];
		free( m_cButWrite );
	}

	if ( m_cStMenPunkt != NULL )
	{
		for ( i = 0; i < m_MenAnz; i++ )
			if ( m_cStMenPunkt[i] != NULL ) 
				delete m_cStMenPunkt[i];
		free( m_cStMenPunkt );
	}

	if ( m_cStRegion != NULL )
	{
		for ( i = 0; i < m_RegAnz; i++ )
			if ( m_cStRegion[i] != NULL ) 
				delete m_cStRegion[i];
		free( m_cStRegion );
	}

	InitButtons();
}

bool CRechteDlg::AllocButtons( )
{
	int i;
	int anz;
	int size;
	anz = m_MenAnz * m_RegAnz;
	size = anz * sizeof( CButton** );

	m_cButNone = (CButton**) malloc( size );
	if ( m_cButNone == NULL ) return false;
	for ( i = 0; i < anz; i++ )
		m_cButNone[i] = NULL;

	m_cButRead = (CButton**) malloc( size );
	if ( m_cButRead == NULL ) return false;
	for ( i = 0; i < anz; i++ )
		m_cButRead[i] = NULL;

	m_cButWrite = (CButton**) malloc( size );
	if ( m_cButWrite == NULL ) return false;
	for ( i = 0; i < anz; i++ )
		m_cButWrite[i] = NULL;

	anz = m_MenAnz;
	size = anz * sizeof( CStatic** );
	m_cStMenPunkt = (CStatic**) malloc( size );
	if ( m_cStMenPunkt == NULL ) return false;
	for ( i = 0; i < anz; i++ )
		m_cStMenPunkt[i] = NULL;

	anz = m_RegAnz;
	size = anz * sizeof( CStatic** );
	m_cStRegion = (CStatic**) malloc( size );
	if ( m_cStRegion == NULL ) return false;
	for ( i = 0; i < anz; i++ )
		m_cStRegion[i] = NULL;

	return true;
}


bool CRechteDlg::Initialize( struct sDescription* sMenPunkt, int MenAnz,
							 struct sDescription* sRegion,   int RegAnz,
							 short  ProgramNumber, bool bAnlageSubSuper,
							 CString LoginUserName,
							 CStringArray* LoginRechte,
							 CUIntArray*   LoginRegion,		
							 bool bStandardEngine,
							 CString Database )
{
	m_sMenPunkt = sMenPunkt;
	m_MenAnz    = MenAnz;

	m_sRegion   = sRegion;
	m_RegAnz    = RegAnz;


	m_nMaxMenPunkt = -1;
	for ( int i = 0; i < MenAnz; i++ )
	{
		if ( m_nMaxMenPunkt < sMenPunkt[i].index )
			m_nMaxMenPunkt = sMenPunkt[i].index;
	}

	m_ProgramNumber = ProgramNumber;

	m_bStandardEngine = bStandardEngine;
	m_bAnlageSubSuper = bAnlageSubSuper;
	m_LoginUserName   = LoginUserName;
	m_LoginRechte     = LoginRechte;
	m_LoginRegion     =	LoginRegion;	
	m_DefaultDatabase = Database;
 
	if ( !AllocButtons() )
	{
		FreeButtons();
		return false;
	}
	return true;
}


// Ermittelt den aktuellen Font und uebergibt ihn an das ControlFeld

void CRechteDlg::GenFont( CWnd *pWnd )
{
	CWnd* m_pWndParent = this;
	CFont* pDlgFont = (CFont*)m_pWndParent->GetFont();
	pWnd->SetFont(pDlgFont);
}


void CRechteDlg::CalcStaticRect( CWnd *TopMuster, CRect *NewRect, 
								 bool mode, bool first )
{
	CRect TopRect;
	TopMuster->GetWindowRect( TopRect );

	int nWidth,  nHeigh;
	nWidth  = TopRect.right  - TopRect.left;
	nHeigh  = TopRect.bottom - TopRect.top;

	if ( mode )
	{
		NewRect->left  = TopRect.left;
		if ( first )
			NewRect->top   = TopRect.top;
		else
			NewRect->top   = TopRect.top + 6*nHeigh/5;
	}
	else
	{
		if ( first )
			NewRect->left  = TopRect.left;
		else
			NewRect->left  = TopRect.left + 6*nWidth/5;
		NewRect->top   = TopRect.top;
	}

	NewRect->right  = NewRect->left + nWidth;
	NewRect->bottom = NewRect->top  + nHeigh;
	ScreenToClient( NewRect );
}

BOOL CRechteDlg::GenStaticFeld( CStatic *pWnd, CStatic *pWndTop,
							    LPCTSTR lpszText, bool mode, bool first )
{
	BOOL bOk;
	CRect rect;

	CalcStaticRect( pWndTop, &rect, mode, first );

	bOk = pWnd->Create( lpszText, pWndTop->GetStyle(), rect, this );

	if ( bOk )
	{
		GenFont ( pWnd );
//		pWnd->ModifyStyleEx( 0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME );
		pWnd->ShowWindow( SW_SHOW );	
	}

	return bOk;
}	
	

BOOL CRechteDlg::GenRadioFeld( CButton *pWnd, CButton *pWndTop, UINT nID, 
							   bool mode, bool first )
{
	BOOL bOk;
	CRect rect;

	CalcStaticRect( pWndTop, &rect, mode, first );

	bOk = pWnd->Create( "", pWndTop->GetStyle(), rect, this, nID );

	if ( bOk )
	{
		GenFont ( pWnd );
//		pWnd->ModifyStyleEx( 0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME );
		pWnd->ShowWindow( SW_SHOW );	
	}

	return bOk;
}	


void CRechteDlg::GenDialogMaske()
{
	int i;
	int j;
	int k;
	bool first;
	CStatic *pStaticTop;

	pStaticTop = (CStatic*)GetDlgItem(IDC_RECHTE_ST_MEN_MUSTER );
	first = true;
	for ( i = 0; i < m_MenAnz; i++ )
	{
		m_cStMenPunkt[i] = new CStatic;
		GenStaticFeld( m_cStMenPunkt[i], pStaticTop, m_sMenPunkt[i].name,
					   true, first );
		pStaticTop = m_cStMenPunkt[i];
		first = false;
	}
	pStaticTop = (CStatic*)GetDlgItem(IDC_RECHTE_ST_MEN_MUSTER );
	pStaticTop->DestroyWindow( );

	pStaticTop = (CStatic*)GetDlgItem(IDC_RECHTE_ST_REG_MUSTER );
	first = true;
	for ( i = 0; i < m_RegAnz; i++ )
	{
		m_cStRegion[i] = new CStatic;
		GenStaticFeld( m_cStRegion[i], pStaticTop, m_sRegion[i].name, 
					   false, first );
		pStaticTop = m_cStRegion[i];
		first = false;
	}
	pStaticTop = (CStatic*)GetDlgItem(IDC_RECHTE_ST_REG_MUSTER );
	pStaticTop->DestroyWindow( );

	UINT idc = IDC_BASE;

	CButton *pButNoneTop;
	CButton *pButReadTop;
	CButton *pButWriteTop;

	CButton *pButNoneTop_Save;
	CButton *pButReadTop_Save;
	CButton *pButWriteTop_Save;

	pButNoneTop  = (CButton*)GetDlgItem( IDC_RECHTE_RB_NONE ); 
	pButReadTop  = (CButton*)GetDlgItem( IDC_RECHTE_RB_READ ); 
	pButWriteTop = (CButton*)GetDlgItem( IDC_RECHTE_RB_WRITE ); 
	k = 0;	
	for ( i = 0; i < m_RegAnz; i++ )
	{
		pButNoneTop_Save  = pButNoneTop;

		pButReadTop_Save  = pButReadTop;
		pButWriteTop_Save = pButWriteTop;

		first = true;
		for ( j = 0; j < m_MenAnz; j++ )
		{
			m_cButNone[k]  = new CButton;
			GenRadioFeld( m_cButNone[k], pButNoneTop, idc++, true, first );
			pButNoneTop = m_cButNone[k];

			m_cButRead[k]  = new CButton;
			GenRadioFeld( m_cButRead[k], pButReadTop, idc++, true, first );
			pButReadTop = m_cButRead[k];
			m_cButWrite[k] = new CButton;
			GenRadioFeld( m_cButWrite[k], pButWriteTop, idc++, true, first );
			pButWriteTop = m_cButWrite[k];

			k++;
			first = false;
		}
		pButNoneTop_Save->DestroyWindow( );
		pButReadTop_Save->DestroyWindow( );
		pButWriteTop_Save->DestroyWindow( );

		if ( i < m_RegAnz - 1 )
		{
			pButNoneTop = new CButton;
 			GenRadioFeld_LT( pButNoneTop, m_cButNone[i*m_MenAnz], m_cStRegion[i+1],
							 IDC_RECHTE_RB_NONE );
			pButReadTop = new CButton;
			GenRadioFeld_LLL( pButReadTop, m_cButNone[i*m_MenAnz], 
							  m_cButRead[i*m_MenAnz], pButNoneTop, 
							  IDC_RECHTE_RB_READ );
			pButWriteTop = new CButton;
			GenRadioFeld_LLL( pButWriteTop, m_cButRead[i*m_MenAnz], 
							  m_cButWrite[i*m_MenAnz], pButReadTop, 
							  IDC_RECHTE_RB_WRITE );
		}
	}

}

void CRechteDlg::CalcRect_LT( CWnd* LeftMuster, CWnd* TopMuster, CRect* NewRect )
{
	CRect LeftRect;
	LeftMuster->GetWindowRect( LeftRect );
	CRect TopRect;
	TopMuster->GetWindowRect( TopRect );

	int nWidth,  nHeigh;
	nWidth  = LeftRect.right - LeftRect.left;
	nHeigh  = LeftRect.bottom - LeftRect.top;

	NewRect->left  = TopRect.left;
	NewRect->top   = LeftRect.top;

	NewRect->right  = NewRect->left + nWidth;
	NewRect->bottom = NewRect->top  + nHeigh;
	ScreenToClient( NewRect );
}

BOOL CRechteDlg::GenRadioFeld_LT( CButton* pWnd, 
								  CButton* pWndLeft, CStatic* pWndTop, UINT nID )
{
	BOOL bOk;
	CRect rect;

	CalcRect_LT( pWndLeft, pWndTop, &rect );

	bOk = pWnd->Create( "", pWndLeft->GetStyle(), rect, this, nID );

	if ( bOk )
	{
		GenFont ( pWnd );
//		pWnd->ModifyStyleEx( 0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME );
		pWnd->ShowWindow( SW_SHOW );	
	}

	return bOk;
}	


void CRechteDlg::CalcRect_LLL( CWnd* LeftMuster1, CWnd* LeftMuster2, 
							   CWnd* LeftMuster3, CRect* NewRect )
{
	CRect LeftRect1;
	LeftMuster1->GetWindowRect( LeftRect1 );
	CRect LeftRect2;
	LeftMuster2->GetWindowRect( LeftRect2 );
	CRect LeftRect3;
	LeftMuster3->GetWindowRect( LeftRect3 );

	int nWidth,  nHeigh;
	nWidth  = LeftRect2.right  - LeftRect2.left;
	nHeigh  = LeftRect2.bottom - LeftRect2.top;

	NewRect->left  = LeftRect3.left + ( LeftRect2.left - LeftRect1.left);
	NewRect->top   = LeftRect3.top;

	NewRect->right  = NewRect->left + nWidth;
	NewRect->bottom = NewRect->top  + nHeigh;
	ScreenToClient( NewRect );
}

BOOL CRechteDlg::GenRadioFeld_LLL( CButton* pWnd, CButton* pWndLeft1, 
								   CButton* pWndLeft2, CButton* pWndLeft3, 
								   UINT nID )
{
	BOOL bOk;
	CRect rect;

	CalcRect_LLL( pWndLeft1, pWndLeft2, pWndLeft3, &rect );

	bOk = pWnd->Create( "", pWndLeft2->GetStyle(), rect, this, nID );

	if ( bOk )
	{
		GenFont ( pWnd );
//		pWnd->ModifyStyleEx( 0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME );
		pWnd->ShowWindow( SW_SHOW );	
	}

	return bOk;
}	


void CRechteDlg::EnablePushButtons( BOOL mode )
{
	m_COPY.EnableWindow( mode );
	m_SUPER.EnableWindow( mode );
	m_SPEICHERN.EnableWindow( mode );
	if ( mode )
	{
		if ( m_bPaste )
			m_PASTE.EnableWindow( mode );
	}
	else
		m_PASTE.EnableWindow( mode );
}

void CRechteDlg::EnableButtons( BOOL mode )
{
	int i, j, k;
	k = 0;	
	for ( i = 0; i < m_RegAnz; i++ )
		for ( j = 0; j < m_MenAnz; j++ )
		{
			m_cButNone[k]->EnableWindow( mode );
			m_cButRead[k]->EnableWindow( mode );
			m_cButWrite[k]->EnableWindow( mode );
			k++;
		}
	EnablePushButtons( mode );
}


void CRechteDlg::GetRegionsRechte( CString& rRechte, int region,
								   CStringArray* aRechte,
								   CUIntArray*   aRegion  )	
{
	int l;
	l = 0;
	while ( l < aRegion->GetSize() && 
		    (int) aRegion->GetAt( l ) != region )
		l++;
	if ( l == aRegion->GetSize() ) // keine Rechte in region 
	{
		rRechte.Empty();
		for ( l = 0; l < m_nMaxMenPunkt + 1; l++ )
			rRechte += "0";	 
	}
	else
		rRechte = aRechte->GetAt( l );
}

void CRechteDlg::EnableButtonsFromLoginRechten( )
{
	int i;
	int j;
	int k;
//	int l;
	int region;
	CString rRechte;
	k = 0;
	for ( i = 0; i < m_RegAnz; i++ )
	{
		region = m_sRegion[i].index;

		GetRegionsRechte( rRechte, region, m_LoginRechte, m_LoginRegion );
	
		for ( j = 0; j < m_MenAnz; j++ )
		{
			switch( rRechte.GetAt( m_sMenPunkt[j].index ) )
			{
			case '1':
				m_cButNone[k]->EnableWindow( TRUE );
				m_cButRead[k]->EnableWindow( TRUE );
				m_cButWrite[k]->EnableWindow( FALSE );
				break;
			case '2':
				m_cButNone[k]->EnableWindow( TRUE );
				m_cButRead[k]->EnableWindow( TRUE );
				m_cButWrite[k]->EnableWindow( TRUE );
				break;
			default:
				m_cButNone[k]->EnableWindow( TRUE );
				m_cButRead[k]->EnableWindow( FALSE );
				m_cButWrite[k]->EnableWindow( FALSE );
				break;
			}
			k++;
		}
	}
}


bool CRechteDlg::SindAktuelleRechteUntermengeVonLoginRechten( )
{
	int i;
	int j;
	int k;
	int region;
	CString lRechte;
	CString aRechte;
	for ( i = 0; i < m_RegAnz; i++ )
	{
		region = m_sRegion[i].index;

		GetRegionsRechte( lRechte, region, m_LoginRechte, m_LoginRegion );
		GetRegionsRechte( aRechte, region, &m_aRechte, &m_aRegion );

		for ( j = 0; j < m_MenAnz; j++ )
		{
			k = m_sMenPunkt[j].index;
			if ( aRechte.GetAt(k) > lRechte.GetAt(k) ) return false;
		}
	}
	return true;
}


///////////////////////////////////////////////////////////////////
// Usernamen lesen

long CRechteDlg::LeseUser( CString& sErrmld ) 
{
	int fd;
	int pos;
	int anz;
	long s;
	char superuser[2];
	char username[20];

	CString Name;
	CString sql;

	sql.Format( "select username,allg_rechte[%d] from %spasswd " \
				" where filialnr=-1 order by username",
				AR_ANL_SUPER+1,
				GetDatabase() );

	s = SqlOpenCs( &fd, sql );

	if ( s != 0 )
	{
		sErrmld.Format("%s\n%s", _T( "passwd\n" ), DynErrmld() );
		return s;
	}

	anz = 0;
	pos = 0;
	while ( s == 0 && pos >= 0 )
	{
		s = SqlFetch( fd, 1, username, superuser, NULL );
		if ( s == 0 )
		{
			Name = username;
			Name.TrimLeft();
			Name.TrimRight();
			if ( m_bAnlageSubSuper ||
				 *superuser == '0' && m_LoginUserName != Name )
			{
				pos = m_USERNAME.AddString( username );
				anz++;
			}
		}
	}
	SqlCloseCs( fd );
	if ( s == 0 )
	{
		sErrmld = _T( "Fehler beim Füllen der Combobox" );
		return -1;
	}
	if ( s != 100 )	
	{
		sErrmld.Format("%s\n%s", _T( "passwd\n" ), DynLastErrmld() );
		return s;
	}
	if ( anz == 0 )
	{
		sErrmld = _T( "Kein Eintrag in der Passwortdatei" );
		return -1;
	}
	return 0;
}


short CRechteDlg::NextFreeRegion( )
{
	bool bFound;
	int  i;
	int  j;
	short region;
	bFound = true;
	i = 0;
	while ( bFound && i < m_RegAnz )
	{
		region = m_sRegion[i].index;
		bFound = false;
		for ( j = 0; j < m_aRegion.GetSize(); j++ )
		{
			if ( (short) m_aRegion.GetAt( j ) == region ) 
				bFound = true;
		}
		i++;
	}
	return region;
}


int CRechteDlg::IsInRegion( short region )
{
	for ( int j = 0; j < m_RegAnz; j++ )
	{
		if ( m_sRegion[j].index == region ) 
			return j;
	}
	return -1;
}


long CRechteDlg::LeseRechte( CString rUser, CString& sErrmld )
{
	int fd;
	int i;
	long s;
	short region;
	char rechte[101];

	CString sql;

	sql.Format( "select rights,region from %suserrights " \
		        "where username='%s' and programnumber=%d order by region",
		        GetDatabase(), rUser, m_ProgramNumber ); 

	s = SqlOpenCs( &fd, sql );

	if ( s != 0 )
	{
		sErrmld.Format("%s\n%s", _T( "userrights\n" ), DynErrmld() );
		return s;
	}

	m_aRechte.RemoveAll( );
	m_aRegion.RemoveAll( );

	memset( rechte, ' ', m_nMaxMenPunkt + 1 );
	rechte[m_nMaxMenPunkt + 1] = '\0';
	for ( i = 0; i < m_RegAnz; i++ )
	{
		m_aRegion.Add( m_sRegion[i].index );
		m_aRechte.Add( rechte );
	}
	
	m_bSubSuperGelesen = false;
	while ( s == 0 )
	{
		s = SqlFetch( fd, 1, rechte, &region, NULL );
		if ( s == 0 )
		{
			if ( region == -1 )  // SubSuper 
			{
				m_bSubSuperGelesen = true;
			}
			else
			{
				i = IsInRegion( region );
				if ( i != -1 )   // nur gueltige Regionen
					m_aRechte.SetAt( i, rechte );
			}
		}
	}
	SqlCloseCs( fd );
	if ( s == 0 )
	{
		sErrmld = _T( "Fehler beim Lesen der Rechte" );
		return -1;
	}
	if ( s != 100 )	
	{
		sErrmld.Format("%s\n%s", _T( "userrights\n" ), DynLastErrmld() );
		return s;
	}

	return 0;
}


void CRechteDlg::ButtonsFromRechte( )
{
	int i;
	int j;
	int k;
	int ind;
	CString rRechte;
	k = 0;
	for ( i = 0; i < m_RegAnz; i++ )
	{
		rRechte = m_aRechte.GetAt( i );
		for ( j = 0; j < m_MenAnz; j++ )
		{
			
//			switch( rRechte.GetAt( j ) )
			ind = m_sMenPunkt[j].index;
			switch( rRechte.GetAt( ind ) )
			{
			case '1':
				m_cButNone[k]->SetCheck( 0 );
				m_cButRead[k]->SetCheck( 1 );
				m_cButWrite[k]->SetCheck( 0 );
				break;
			case '2':
				m_cButNone[k]->SetCheck( 0 );
				m_cButRead[k]->SetCheck( 0 );
				m_cButWrite[k]->SetCheck( 1 );
				break;
			default:
				rRechte.SetAt( ind, '0' );	// auf jeden fall korrigieren
				m_cButNone[k]->SetCheck( 1 );
				m_cButRead[k]->SetCheck( 0 );
				m_cButWrite[k]->SetCheck( 0 );
				break;
			}
			k++;
		}
	}
}


void CRechteDlg::RechteFromButtons( )
{
	int i;
	int j;
	int k;
	int ind;
	CString rRechte;

	k = 0;
	for ( i = 0; i < m_RegAnz; i++ )
	{
		rRechte = m_aRechte.GetAt( i );
		for ( j = 0; j < rRechte.GetLength(); j++ )
			rRechte.SetAt( j, ' ' );
		for ( j = 0; j < m_MenAnz; j++ )
		{

//			ind = j;
			ind = m_sMenPunkt[j].index;
			if ( m_cButRead[k]->GetCheck( ) == 1 )
				rRechte.SetAt( ind, '1' );
			else if ( m_cButWrite[k]->GetCheck( ) == 1 )
				rRechte.SetAt( ind, '2' );
			else
				rRechte.SetAt( ind, '0' );
			m_aRechte.SetAt( i, rRechte );
			k++;
		}
	}
}


bool CRechteDlg::IsToInsert( CString cRechte )
{
	int  i;
	char ze;
	bool bInsert;
	bInsert = false;
	i = 0;
	while( i < cRechte.GetLength() && !bInsert )
	{
		ze = cRechte.GetAt(i++);
		if ( ze == '1' || ze == '2' ) 
			bInsert = true;
	}
	return bInsert;
}

long CRechteDlg::StoreRechte( CString& rErrmld )
{

	CString sql;
	int i;
	long s;
	short region;

	RechteFromButtons( );

	s = 0;
	s = SqlBeginWork();
	if ( s != 0 )
	{
		rErrmld = _T( "Transaktion userrights\n" ); 
		rErrmld += DynErrmld();
		return s;
	}


	sql.Format( "delete from %suserrights where "\
		        "username='%s' and programnumber=%d",
				GetDatabase(), m_aktUser, m_ProgramNumber );
	s = SqlExecuteImm( sql ); 
	rErrmld = _T( "Rechte löschen\n" ); 

	if ( m_bAnlageSubSuper && s == 0 )
	{
		if ( m_SUBSUPER.GetCheck() == 1 )
		{
			region = -1;	// !!!!!!!!
			sql.Format( "insert into %suserrights values('%s',%d,%d,'%s')",
				 		GetDatabase(), m_aktUser, m_ProgramNumber, region, " " );
			s = SqlExecuteImm( sql ); 
		}
	}

	i = 0;
	while ( i < m_RegAnz && s == 0 )
	{
		if ( IsToInsert( m_aRechte.GetAt(i) ) )
		{
			region = m_aRegion.GetAt( i );
			sql.Format( "insert into %suserrights values('%s',%d,%d,'%s')",
				 		GetDatabase(), m_aktUser, m_ProgramNumber, region,
						m_aRechte.GetAt(i) );
			s = SqlExecuteImm( sql ); 

			rErrmld = _T( "Rechte abspeichern\n" ); 

		}
		i++;
	}

	if ( s == 0 )
		SqlCommitWork();
	else
	{
		rErrmld += DynErrmld();
		SqlRollbackWork();
	}
	return s;
}


void CRechteDlg::CopyRechte( )
{
	int i;
	m_aSaveRechte.RemoveAll( );
//	m_aSaveRegion.RemoveAll( );	
	for ( i = 0; i < m_RegAnz; i++ )
	{
		m_aSaveRechte.Add( m_aRechte.GetAt( i ) );
//		m_aSaveRegion.Add( m_aRegion.GetAt( i ) );
	}
}

void CRechteDlg::PasteRechte( )
{
	int i;
	m_aRechte.RemoveAll( );
//	m_aRegion.RemoveAll( );
	for ( i = 0; i < m_RegAnz; i++ )
	{
		m_aRechte.Add( m_aSaveRechte.GetAt( i ) );
//		m_aRegion.Add( m_aSaveRegion.GetAt( i ) );
	}
}

void CRechteDlg::PasteSuperUserRechte( )
{
	int i;
	int region;
	CString rRechte;

	m_aRechte.RemoveAll( );
//	m_aRegion.RemoveAll( );

	for ( i = 0; i < m_RegAnz; i++ )
	{
		region = m_sRegion[i].index;

		GetRegionsRechte( rRechte, region, m_LoginRechte, m_LoginRegion );
	
		m_aRechte.Add( rRechte );
//		m_aRegion.Add( region );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CRechteDlg message handlers


void CRechteDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CRechteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CString sErrmld;
	long s;

	GenDialogMaske();

	m_PASTE.EnableWindow( FALSE );
	m_bPaste = false;

	if ( !m_bAnlageSubSuper )
		m_SUBSUPER.ShowWindow( SW_HIDE );

	// user lesen
	theApp->BeginWaitAction();

	ChangeToPhosix( );

	s = LeseUser( sErrmld );

	theApp->EndWaitAction();
	if ( s != 0 )
		AfxMessageBox( sErrmld );

	m_USERNAME.SetCurSel( 0 );
	m_USERNAME.SetFocus();
	OnCloseupRechteCbUsername(); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRechteDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();

	NextDlgCtrl();
}

void CRechteDlg::OnRechteBpSpeichern() 
{
	// TODO: Add your control notification handler code here
	CString rErrmld;
	long s;
	theApp->BeginWaitAction();
	s = StoreRechte( rErrmld );
	theApp->EndWaitAction();
	if ( s != 0 )
		AfxMessageBox( rErrmld );
}


bool CRechteDlg::AreNamesEqual( CString s1, CString s2 )
{
	s1.TrimLeft();
	s1.TrimRight();
	s2.TrimLeft();
	s2.TrimRight();
	return s1 == s2;
}

void CRechteDlg::OnCloseupRechteCbUsername() 
{
	// TODO: Add your control notification handler code here
	CString rUser;
	CString rErrmld;
	long s;
	int nIndex;
	nIndex = m_USERNAME.GetCurSel();
	if ( nIndex >= 0 )
	{
		m_USERNAME.GetLBText( nIndex,  rUser );
		theApp->BeginWaitAction();
		s = LeseRechte( rUser, rErrmld );
		theApp->EndWaitAction();
		if ( s == 0 )
		{
			m_aktUser = rUser;

			// SubSuper-Check
			if ( m_bAnlageSubSuper )
			{
				if ( m_bSubSuperGelesen )
					m_SUBSUPER.SetCheck( 1 );
				else
					m_SUBSUPER.SetCheck( 0 );
			}

			ButtonsFromRechte( );

			// Siehe LeseUser( ) 
			if ( AreNamesEqual( m_aktUser, m_LoginUserName ) )
				EnableButtons( m_bAnlageSubSuper );
			else
			{
				if ( m_bAnlageSubSuper )
					EnableButtons( TRUE );
				else
				{
					if ( m_bSubSuperGelesen )
						EnableButtons( FALSE );  // SubSuper - SubSuper 
					else
					{
						if ( SindAktuelleRechteUntermengeVonLoginRechten( ) )
						{
							EnableButtonsFromLoginRechten( );
							EnablePushButtons( TRUE );
						}
						else
							EnableButtons( FALSE ); 
					}
				}
			}
		}
		else
		{
			m_SPEICHERN.EnableWindow ( FALSE );
			AfxMessageBox( rErrmld );
		}
	}
}

void CRechteDlg::OnRechteBpCopy() 
{
	// TODO: Add your control notification handler code here
	RechteFromButtons( );
	CopyRechte( );
	m_PASTE.EnableWindow( TRUE );
	m_bPaste = true;
}

void CRechteDlg::OnRechteBpPaste() 
{
	// TODO: Add your control notification handler code here
	PasteRechte( );
	ButtonsFromRechte( );
}

void CRechteDlg::OnRechteBpSuper() 
{
	// TODO: Add your control notification handler code here
	PasteSuperUserRechte( );
	ButtonsFromRechte( );	
}
