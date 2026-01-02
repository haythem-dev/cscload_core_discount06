// NewautidemView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZdpUtil.h"
#include "NewautidemView.h"
#include "ExcelCsv.h"
// #include <wudu.h>
#include <libscsvoodoo/libscsvoodoo.h>

#include <phxlib/phxutil.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewautidemView

IMPLEMENT_DYNCREATE(CNewautidemView, CFormView)

CNewautidemView::CNewautidemView()
	: ChPflegeView(CNewautidemView::IDD)
{
	//{{AFX_DATA_INIT(CNewautidemView)
	//}}AFX_DATA_INIT
	theApp = ((CZdpUtilApp*)AfxGetApp());
	m_bDoResize  = false;
}

CNewautidemView::~CNewautidemView()
{
}

void CNewautidemView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewautidemView)
	DDX_Control(pDX, IDC_NEWAUTIDEM_SPALTE, m_SPALTE);
	DDX_Control(pDX, IDC_NEWAUTIDEM_CB_ACTION, m_cbACTION);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewautidemView, CFormView)
	//{{AFX_MSG_MAP(CNewautidemView)
	ON_CBN_SELCHANGE(IDC_NEWAUTIDEM_CB_ACTION, OnSelchangeNewautidemCbAction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CNewautidemView

#ifdef _DEBUG
void CNewautidemView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNewautidemView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////
// Implementation

#define MAX_SPALTE 50

void CNewautidemView::InitPflege()
{
	m_SPALTE.SetLimitText( MAX_SPALTE );
}

void CNewautidemView::InitVariables()
{
	m_cbACTION.SetCurSel(0);
}

/////////////////////////////////////////////////////////////////////////////
// Virtuals aus ChPfegeView

int  CNewautidemView::BearbeiteSatz()
{
/*
	if ( GetFocus() == &m_GUELDAT)
	{
		if ( SucheSatz() == 1 )
			return 3;
		else 
			return -1;
	}
	else
*/
	{
		((CDialog*) this)->NextDlgCtrl( );
		return -1;
	}
}


bool CNewautidemView::ExtractPznFromCsv( CString &cErrmld, char *ColumnHeader, long *nAnz )// PZN8 --> Umwandlung erst in zpautidm
		
{
	bool bOk;
	int  ret;
	long anz;
	char mld[200];
	CString cZeile;
	CString cItem;
	CExcelCsv Ecsv;

	CStdioFile f;
	CFileException e; 
	bool bFirst;


	cErrmld.Empty();


	// Input 
	char BASED_CODE szFilter[] = 
		 "Csv Files (*.csv)|*.csv|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE, "csv",
							NULL,
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							szFilter );         

	if ( dlg.DoModal() != IDOK )
		return false;

	CString sFileName;
	sFileName = dlg.GetPathName();	
	if ( sFileName.IsEmpty( ) )
		return false;

	// Output 
	char BASED_CODE szTxtFilter[] = 
		 "List Files (*.txt)|*.txt|All Files (*.*)|*.*||";

	CFileDialog outdlg( FALSE, "txt",
								dlg.GetFileTitle( ),		// NULL,
								OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
								szTxtFilter );         

	if ( outdlg.DoModal() != IDOK )
		return false;

	CString sOutFileName;
	sOutFileName = outdlg.GetPathName();	
	if ( sOutFileName.IsEmpty( ) )
		return false;


	bOk = true;
	bFirst = true;

	anz = 0;

	theApp->BeginWaitAction();

	if ( Ecsv.ReadHeaderLine( (LPCTSTR ) sFileName, ColumnHeader, mld ) >= 0 )
	{
		ret = 0;
		while ( ret == 0 && bOk )
		{
			ret = Ecsv.ReadLine( cZeile, cItem );
			if ( ret == 0 )
			{
				if (! cItem.IsEmpty() )
				{
					if ( bFirst )
					{
						if( !f.Open( sOutFileName,  CFile::modeCreate | CFile::modeWrite, &e ) )
						{
							cErrmld.Format( "Datei wurde nicht eröffnet ( %d )", e.m_cause );
							bOk =  false;
						}
						else
							bFirst = false;
					}
					if ( bOk )
					{
//						AfxMessageBox( cItem );
//						f.WriteString( (LPCTSTR) cItem );
						cItem += "\n";
						f.Write( (LPCTSTR) cItem, cItem.GetLength() );
						anz++;
					}
				}
			}
		}
		if ( !bFirst )
			f.Close();
	}
	else
	{
		cErrmld = mld;
		bOk = false;
	}

	theApp->EndWaitAction();

	*nAnz = anz;

	return bOk;
}


bool CNewautidemView::IsDigit( CString cS )
{
	int pos;
	cS.TrimLeft();
	cS.TrimRight();
	pos = 0;
	for ( pos = 0; pos < cS.GetLength(); pos++ )
	{
		if (!isdigit( cS.GetAt( pos ) ) )
			return false;
	}
	return true;
}

bool CNewautidemView::TestAutidem( CString cFile_Name, CString &cErrmld, long *nAnz )
{

	CString cZeile;
	CString sFileName;
	BOOL ret;
	int  err_mode;
	long znr;
	long anz;
	class CStdioFile TextDat;
	CFileException e; 


	*nAnz = 0;

	if ( cFile_Name.IsEmpty() )
	{
		// Input 
		char BASED_CODE szFilter[] = 
			 "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
		CFileDialog dlg( TRUE, "txt",
								NULL,
								OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
								szFilter );         

		if ( dlg.DoModal() != IDOK )
			return false;

		sFileName = dlg.GetPathName();	
	}
	else
	{
		sFileName = cFile_Name;
	}
	if ( sFileName.IsEmpty( ) )
		return false;

	ret = TextDat.Open( sFileName, CFile::modeRead, &e );
	if ( !ret )
	{
		cErrmld.Format( "%s\nTextDat.Open ( not found: %s )", sFileName, e.m_cause );
		return false;
	}	

	err_mode = 0;
	znr = 0;
	anz = 0;
	while ( ret )
	{
		try
		{
			znr++;
			ret = TextDat.ReadString( cZeile );
			if ( ret )
			{
				anz++;
				if ( !IsDigit( cZeile ) )
				{
					cErrmld.Format( "Zahl in Zeile %ld ist nicht numerisch", znr );
					err_mode = 1;
					ret = FALSE;
				}
				/*else if ( TestPruefZiffer7( atol( cZeile ) ) == 0 )// PZN8 --> Umwandlung erst in zpautidm
				{
					cErrmld.Format( "Zahl in Zeile %ld hat ungültige Prüfziffer", znr );
					err_mode = 1;
					ret = FALSE;
				}*/
			}

		}
		catch (CFileException* e)
		{
			cErrmld.Format( "%s\nTextDat.Read ( %s )", sFileName, e->m_cause );
			ret = FALSE;
			err_mode = 2;
			throw;
		}

	}
	TextDat.Close( );
	if ( err_mode != 0 )
		return false;
	*nAnz = anz;
	return true;

}

bool CNewautidemView::GenAutidem( CString &cErrmld, long *nAnz )
{
	BOOL ret;
	class CStdioFile TextDat;
	CFileException e; 
	CString cDirec;

#define MAX_BUF 2048
	char buf[ MAX_BUF + 1 ];
	long anz_gelesen;
	long lStatus;
	int  unx_fd;
	int  err_mode;
	int rcv_lng;

	cErrmld.Empty();

	*nAnz = 0;

	// Input 
	char BASED_CODE szFilter[] = 
		 "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE, "txt",
							NULL,
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							szFilter );         

	if ( dlg.DoModal() != IDOK )
		return false;

	CString sFileName;
	sFileName = dlg.GetPathName();	
	if ( sFileName.IsEmpty( ) )
		return false;	

	if ( UnxGetenv ( "WWS", buf ) != 0 )
	{
		cErrmld  = "Umgebungsvariable $WWS auf Server unbekannt\n";
		cErrmld += DynErrmld();
		return false;
	}


	long nTestAnz;
	if ( !TestAutidem( sFileName, cErrmld, &nTestAnz ) )
		return false;

	cDirec  = buf;
	cDirec += _T( "/daten/idmdaten/" ); // nobody knows, what this should be for !?
	cDirec += dlg.GetFileName( );

	CString cZeile;

	ret = TextDat.Open( sFileName, CFile::modeRead, &e );
	if ( !ret )
	{
		cErrmld.Format( "%s\nTextDat.Open ( not found: %s )", sFileName, e.m_cause );
		return false;
	}

	ret = UnxFopen( &unx_fd, cDirec, "w" ) == 0;
	if ( !ret )
	{
		TextDat.Close( );
		cErrmld.Format( "%s\n %s )", cDirec, DynErrmld() );
		return false;
	}

	err_mode = 0;
	while ( ret )
	{
		try
		{
			anz_gelesen = TextDat.Read( buf, MAX_BUF );
			if ( anz_gelesen > 0 )
			{
				ret = UnxFwrite( unx_fd, buf, anz_gelesen ) == 0;
				if ( !ret )
				{
					cErrmld.Format( "%s\n %s )", cDirec, DynErrmld() );
					err_mode = 1;
				}
			}
			if ( ret )
				ret = anz_gelesen == MAX_BUF;

		}
		catch (CFileException* e)
		{
			cErrmld.Format( "%s\nTextDat.Read ( %s )", sFileName, e->m_cause );
			ret = FALSE;
			err_mode = 2;
			throw;
		}

	}
	UnxFclose( unx_fd );
	TextDat.Close( );
	if ( err_mode != 0 )
		return false;
	
	strcpy( buf, "zpautidm 0 " );   // Programmname + mode auf UnixSeite 
	strcat( buf, theApp->GetRefToAnwender( ) );	
	strcat( buf, " " );
	strcat( buf, (LPCTSTR) cDirec );

//	AfxMessageBox( buf );

	rcv_lng = MAX_BUF;

	theApp->BeginWaitAction();

	lStatus = UnxPipwSystem ( buf, "", buf, &rcv_lng );

	theApp->EndWaitAction();

	buf[rcv_lng] ='\0';

	if ( lStatus < 0 || rcv_lng == 0 )
	{
		strcpy( buf, DynErrmld() );
		lStatus = 1;
	}

	if ( lStatus == 1 )
	{
		cErrmld  = "zpautidm\n";
		cErrmld += buf;
		return false;
	}

	cErrmld = buf;

	return true;
}

int  CNewautidemView::SpeichereSatz( )
{
	long nAnz;
	char cHeader[MAX_SPALTE + 2];
	CString cErrmld;
	CString cSpaltenHeader;
    UpdateData( TRUE );

	switch ( m_cbACTION.GetCurSel( ) )
	{
	case 0:
		m_SPALTE.GetWindowText( cSpaltenHeader );
		cSpaltenHeader.TrimRight();
		if ( cSpaltenHeader.IsEmpty() )
		{
			AfxMessageBox( "Überschrift der PZN-Spalte darf nicht leer sein" );
			return 0;
		}

		if ( ! theApp->YouWantToDo( "Aktion durchführen" ) ) return -1;
	    strcpy( cHeader, cSpaltenHeader );
		if ( ExtractPznFromCsv( cErrmld, cHeader, &nAnz ) )
		{
			cErrmld.Format( "%ld Artikel-Nummern wurden gespeichert", nAnz );
			AfxMessageBox( cErrmld );
			return 0;
		}
		else
		{
			if ( !cErrmld.IsEmpty() )
				AfxMessageBox( cErrmld );
			return -1;
		}
		break;

	case 1:
		if ( ! theApp->YouWantToDo( "Aktion durchführen" ) ) return -1;
		if ( !TestAutidem( "", cErrmld, &nAnz ) )
		{
			AfxMessageBox( cErrmld );
			return -1;
		}
		else
		{
			cErrmld.Format( "Test erfolgreich\n%ld Artikelnummern wurden getestet", nAnz );
			AfxMessageBox( cErrmld );
			return 0;
		}
		break;
	case 2:
		if ( ! theApp->YouWantToDo( "Aktion durchführen" ) ) return -1;

		if ( GenAutidem( cErrmld, &nAnz ) )
		{
//			cErrmld.Format( "%ld Artikel-Nummern wurden bearbeitet", nAnz );
			AfxMessageBox( cErrmld );
			return 0;
		}
		else
		{
			if ( !cErrmld.IsEmpty() )
				AfxMessageBox( cErrmld );
			return -1;
		}
		break;
	}


	return 0;
}


int  CNewautidemView::UndoSatz()
{
	if ( !m_bComeBack )
	{
/*
//		m_wndGrid.SetCurrentCell( 0, 0 );   
		m_wndGrid.ShowWindow( SW_HIDE );     // sieht so besser aus 
		ClearInfo();
		m_hSelSql.CloseCursor( );
*/
		return 0;
	}
	else
		return 0; // -1;
}


/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CNewautidemView 


void CNewautidemView::OnSelchangeNewautidemCbAction() 
{
	BOOL bShow;
	bShow = m_cbACTION.GetCurSel( ) == 0;
	GetDlgItem( IDC_NEWAUTIDEM_ST_SPALTE )->ShowWindow( bShow );
	m_SPALTE.ShowWindow( bShow );
}

void CNewautidemView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CNewautidemView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class

	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
		if ( pActivateView != pDeactiveView )
		{
			m_bDoResize = true;
			if ( !m_bComeBack )
			{
				InitVariables();
//				theApp->SetMenuOnOff( 1, -1, 0, 1, 0, 0 ); 
				theApp->SetMenuOnOff( 1, 1, -1, -1, -1, -1 ); 
			}
			else
			{
				m_bComeBack = false;
//				FuelleGridBox( m_nFetchCount );
				theApp->PopMenuState(  );
//				theApp->SetMenuOnOff( 0, 0, 0, 0, 1, 1 ); 
				theApp->SetMenuOnOff( 1, 1, -1, -1, -1, -1 ); 
			}
		}		
	}
}



////////////////////////////////////////////////
// Drucken

bool CNewautidemView::GetInfoFromCallingView( CString& cStr, int nAction )
{
	return true;
}


