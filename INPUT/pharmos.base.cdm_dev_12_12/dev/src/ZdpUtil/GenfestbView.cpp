// GenfestbView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ZdpUtil.h"
#include "GenfestbView.h"
#include "GenIfaLieferung.h"
#include <eklibs/hamfcs/hMskDate.h>
#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenfestbView

IMPLEMENT_DYNCREATE(CGenfestbView, CFormView)

CGenfestbView::CGenfestbView()
	: ChPflegeView(CGenfestbView::IDD)
{
	//{{AFX_DATA_INIT(CGenfestbView)
	//}}AFX_DATA_INIT
	theApp = ((CZdpUtilApp*)AfxGetApp());
	m_bDoResize  = false;
	m_cIliFile = "liefer.ili";
}

CGenfestbView::~CGenfestbView()
{
}

void CGenfestbView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenfestbView)
	DDX_Control(pDX, IDC_GENFESTB_TRENN, m_TRENN);
	DDX_Control(pDX, IDC_GENFESTB_POSPZN, m_POSPZN);
	DDX_Control(pDX, IDC_GENFESTB_POSFEST, m_POSFEST);
	DDX_Control(pDX, IDC_GENFESTB_FILE, m_FILE);
	DDX_Control(pDX, IDC_GENFESTB_VERZ, m_VERZ);
	DDX_Control(pDX, IDC_GENFESTB_LIEFDAT, m_LIEFDAT);
	DDX_Control(pDX, IDC_GENFESTB_GUELDAT, m_GUELDAT);
	DDX_Control(pDX, IDC_GENFESTB_SATZART, m_cbSATZART);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGenfestbView, CFormView)
	//{{AFX_MSG_MAP(CGenfestbView)
	ON_BN_CLICKED(IDC_GENFESTB_PB_FILE, OnGenfestbPbFile)
	ON_BN_CLICKED(IDC_GENFESTB_PB_VERZ, OnGenfestbPbVerz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CGenfestbView

#ifdef _DEBUG
void CGenfestbView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGenfestbView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


//////////////////////////////////////////////////////////////////
// Implementation

#define MAX_SPALTE 50

void CGenfestbView::InitPflege()
{
//	m_SPALTE.SetLimitText( MAX_SPALTE );
	m_LIEFDAT.SetMask(ED_LDATE,
			          ED_NORMAL,
					  &m_nLiefDat,
					  10,
					  new ChMaskLDate);
	m_LIEFDAT.SetDialog( );
	m_GUELDAT.SetMask(ED_LDATE,
			          ED_NORMAL,
					  &m_nGuelDat,
					  10,
					  new ChMaskLDate);
	m_GUELDAT.SetDialog( );

	m_POSPZN.SetMask (ED_INT,
			          ED_NORMAL,
					  &m_nPosPzn,
					  3,
					  new ChMaskNum);
	m_POSPZN.SetDialog( );
	m_POSFEST.SetMask(ED_INT,
			          ED_NORMAL,
					  &m_nPosFest,
					  3,
					  new ChMaskNum);
	m_POSFEST.SetDialog( );

	m_TRENN.SetMask(ED_CHAR,
		            ED_NORMAL,
					m_cTrenn,
					1,
					new ChMaskChar);
	m_TRENN.SetDialog( );
}

void CGenfestbView::InitVariables()
{
	m_cbSATZART.SetCurSel(0);
	m_nLiefDat = 0;
	m_LIEFDAT.p_SetInput( );
	m_nGuelDat = 0;
	m_GUELDAT.p_SetInput( );
	m_FILE.SetWindowText("");
	m_VERZ.SetWindowText("");
	m_nPosPzn  = 0;
	m_POSPZN.p_SetInput( );
	m_nPosFest = 0;
	m_POSFEST.p_SetInput( );
	strcpy( m_cTrenn, "" );
	m_TRENN.p_SetInput( );

	((CStatic *) GetDlgItem( IDC_GENFESTB_DATAUF ))->SetWindowText( "" );

}


/////////////////////////////////////////////////////////////////////////////
// Virtuals aus ChPfegeView

int  CGenfestbView::BearbeiteSatz()
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

int  CGenfestbView::SpeichereSatz( )
{
	int  ind;
	long s;
	CString cSsatz;
	CString cDatei;
	CString cVerz;
	CString cErrmld;
	CGenIfaLieferung GenIfa;
	char satzart[2];
	char errmld[300];

    UpdateData( TRUE );

	m_LIEFDAT.p_GetInput( );
	m_GUELDAT.p_GetInput( );
	m_FILE.GetWindowText( cDatei );
	m_VERZ.GetWindowText( cVerz );

	m_POSPZN.p_GetInput( );
	m_POSFEST.p_GetInput( );
	m_TRENN.p_GetInput( );

	ind = m_cbSATZART.GetCurSel();

	if ( m_nLiefDat == 0 )
	{
		AfxMessageBox( "Lieferdatum ungültig" );	
		m_LIEFDAT.SetFocus();		
		return 0;
	}
	if ( m_nGuelDat == 0 )
	{
		AfxMessageBox( "Gültigkeitdatum ungültig" );	
		m_GUELDAT.SetFocus();		
		return 0;
	}
	cDatei.TrimLeft();
	if ( cDatei.IsEmpty()  )
	{
		AfxMessageBox( "Übernahmedatei fehlt" );	
		m_FILE.SetFocus();		
		return 0;
	}

	int index;
	index = cVerz.Find( m_cIliFile );
	if ( index == -1 )
	{
		cErrmld.Format( "Dateiname muss %s sein", m_cIliFile );
		AfxMessageBox ( cErrmld );
		m_VERZ.SetFocus();	
		return 0;
	}
	cVerz = cVerz.Left( index );
	index = cVerz.GetLength() - 1;
	if ( index >= 0 )
	{
		char ze;
		ze = cVerz.GetAt( index );
		if ( ze == '\\' || ze == '/' )
			cVerz = cVerz.Left( index );
	}


	if ( m_nPosPzn < 1 )
	{
		AfxMessageBox( "FeldNr PZN >= 1" );	
		m_POSPZN.SetFocus();		
		return 0;
	}
	if ( m_nPosFest < 1 )
	{
		AfxMessageBox( "FeldNr Festbetrag >= 1" );	
		m_POSFEST.SetFocus();		
		return 0;
	}
	if ( m_nPosPzn == m_nPosFest )
	{
		AfxMessageBox( "FeldNummern dürfen nicht gleich sein" );	
		m_POSPZN.SetFocus();		
		return 0;
	}

	if ( isdigit( *m_cTrenn ) || *m_cTrenn == '.' || *m_cTrenn == ',' || 
         *m_cTrenn == '+' || *m_cTrenn == '+' )
	{
		AfxMessageBox( "Trennzeichen nicht Ziffer, nicht Punkt, nicht Komma, nicht Plus, nicht Minus" );	
		m_TRENN.SetFocus();		
		return 0;
	}

	if ( ind != CB_ERR )
	{
		m_cbSATZART.GetLBText( ind, cSsatz );
		satzart[0] = cSsatz.GetAt( 0 );
		satzart[1] = '\0';
		s = GenIfa.GenFeb_2( m_nPosPzn, m_nPosFest, 
			                 (char*)(LPCTSTR)m_cTrenn, satzart, m_nGuelDat, m_nLiefDat,
			 		         (char*)(LPCTSTR)cDatei, (char*)(LPCTSTR)cVerz, errmld );
		if ( s != 0 )
			AfxMessageBox( errmld );
		else
		{
			cErrmld.Format( "Die Dateien\n%s und liefd001.ild\nwurden im Verzeichnis\n%s\nerzeugt", 
							 m_cIliFile, cVerz );
			AfxMessageBox ( cErrmld );
		}
	}
	else
		AfxMessageBox( "§s wurde keine Satzart ausgewählt" );

	return 0;
}


int  CGenfestbView::UndoSatz()
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
// Behandlungsroutinen für Nachrichten CGenfestbView 

void CGenfestbView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CGenfestbView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

bool CGenfestbView::GetInfoFromCallingView( CString& cStr, int nAction )
{
	return true;
}

////////////////////////////////////////////////
// EingabeFile


void CGenfestbView::GenZeilenAufbau() 
{
	BOOL ret;
	CString cErrmld;
	CString cZeile;
	CString sFileName;
	class CStdioFile TextDat;
	CFileException e; 

    UpdateData( TRUE );

	m_FILE.GetWindowText( sFileName );

	if ( sFileName.IsEmpty() )
	{
		AfxMessageBox( "Es wurde kein Dateiname eingegeben" );
		return;
	}

	ret = TextDat.Open( sFileName, CFile::modeRead, &e );
	if ( !ret )
	{
		cErrmld.Format( "%s\nTextDat.Open ( not found: %s )", sFileName, e.m_cause );
		return;
	}	
	try
	{
		ret = TextDat.ReadString( cZeile );	
		if (!ret)
			cErrmld.Format( "%s\nTextDat.Read ( %s )", sFileName, "Keine Zeile vorhanden" );
	}
	catch (CFileException* e)
	{
		cErrmld.Format( "%s\nTextDat.Read ( %s )", sFileName, e->m_cause );
		ret = FALSE;
		throw;
	}
	TextDat.Close( );
	if ( !ret )
		cZeile.Empty();

	((CStatic *) GetDlgItem( IDC_GENFESTB_DATAUF ))->SetWindowText( cZeile );
}

void CGenfestbView::OnGenfestbPbFile() 
{

	// Input 
	char BASED_CODE szFilter[] = 
		 "All Files (*.*)|*.*||";
	CFileDialog dlg( TRUE,  "*",
							NULL,
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							szFilter );         

	if ( dlg.DoModal() != IDOK )
		return;

	CString sFileName;
	sFileName = dlg.GetPathName();	
	if ( sFileName.IsEmpty( ) )
		return;	

	m_FILE.SetWindowText( sFileName );

	GenZeilenAufbau();

	return;
	
}

////////////////////////////////////////////////
// AusgabeVerzeichnis

void CGenfestbView::OnGenfestbPbVerz() 
{

	// Input 
	char BASED_CODE szFilter[] = 
		 "All Files (*.*)|*.*||";
	CFileDialog dlg( FALSE,  "ili",
							m_cIliFile,
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
							);         

	if ( dlg.DoModal() != IDOK )
		return;

	m_VERZ.SetWindowText( "" );

	CString sFileName;
	sFileName = dlg.GetFileName();
	if ( sFileName != m_cIliFile )
	{
		CString cErrmld;
		cErrmld.Format( "Dateiname muss %s sein", m_cIliFile );
		AfxMessageBox ( cErrmld );
		return;
	}

	sFileName = dlg.GetPathName();	
	if ( sFileName.IsEmpty( ) )
		return;	

	m_VERZ.SetWindowText( sFileName );

	return;	
}

