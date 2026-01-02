// ArthersView.cpp : implementation file
//

#include "stdafx.h"
#include "zdpdruck.h"
#include "ArthersView.h"

#include "hSelectDialog.h"
#include <phxlib/HerstelSelCtrl.h>
#include "ViewNumbers.h"

#include "ServerDatum.h"
#include <hdatum/Phodate.h>

#include <eklibs/hamfcs/hMskNum.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArthersView

IMPLEMENT_DYNCREATE(CArthersView, CFormView)

CArthersView::CArthersView()
	: ChPflegeView(CArthersView::IDD)
{
	//{{AFX_DATA_INIT(CArthersView)
	//}}AFX_DATA_INIT
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
}

CArthersView::~CArthersView()
{
}

void CArthersView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArthersView)
	DDX_Control(pDX, IDC_ARTHERS_RD_NR, m_rdNr);
	DDX_Control(pDX, IDC_ARTHERS_RD_NAME, m_rdName);
	DDX_Control(pDX, IDC_ARTHERS_SUCHB, m_Suchb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArthersView, CFormView)
	//{{AFX_MSG_MAP(CArthersView)
	ON_WM_SIZE()
	ON_EN_SETFOCUS(IDC_ARTHERS_SUCHB, OnSetfocusArthersSuchb)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArthersView diagnostics

#ifdef _DEBUG
void CArthersView::AssertValid() const
{
	CFormView::AssertValid();
}

void CArthersView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////
// Implementation

void CArthersView::SucheHersteller( )
{
	CHerstelSelCtrl m_SelBox( IM_NUMBER_S );

	ChSelectDialog dlg( "Auswahl Hersteller", &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( &m_nSuchNr ) == 0 )
		{
			m_Suchb.p_SetInput();
			m_Suchb.SetFocus();
			ShowHersteller( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// Hersteller

void CArthersView::ScanName( CString Name )
{
	int pos;
	pos = Name.Find( '\n' );
	if ( pos >= 0 )	
		m_cName = Name.Left( pos ) + ", " + Name.Mid( pos + 1);
	else
		m_cName = Name;
}


BOOL CArthersView::ShowHersteller( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	CString PPE;
	iStat = m_RD_HERSTELLER.IPlausi( m_nSuchNr, Name, PPE, &Errmld);
	if ( bShow )	// neu
		GetDlgItem( IDC_ARTHERS_SHOW )->SetWindowText( Name );
/*
	if ( iStat > 1 && bMeldung ) AfxMessageBox( Errmld );
	return iStat <= 1;
*/
	// 0 nicht zulassen
	if ( iStat > 0 && bMeldung ) AfxMessageBox( Errmld );

	ScanName( Name );

	m_nNumberOfRows = 0;
	m_wndGrid.hInitGrid();

	return iStat == 0;
}

class CV_ARTIKEL_Hersteller : public ChValBase
{
public:
	CV_ARTIKEL_Hersteller( CArthersView* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArthersView*)m_pWnd)->ShowHersteller( bMeldung, bMeldung );
	}
	void NotifyProc( )
	{
		((CArthersView*)m_pWnd)->SucheHersteller( );
	}
};

void CArthersView::InitPflege()
{
	m_wndGrid.SubclassDlgItem(IDC_ARTHERS_GRID, this );
	m_wndGrid.Initialize();	
	m_wndGrid.hZeroGrid();
	m_nNumberOfRows = 0;
	FirstInitGrid( );

	m_Suchb.SetMask	(ED_LONG,
				     ED_NORMAL,
					 &m_nSuchNr,
					 5,
					 new ChMaskNum,
					 new CV_ARTIKEL_Hersteller( this ) );
	m_Suchb.SetDialog( TRUE );

	m_nSuchNr = 0;

	m_rdNr.SetCheck( 1 );
}

void CArthersView::InitVariables()
{
	m_nSuchNr = 0;
	m_Suchb.p_SetInput();
	m_nNumberOfRows = 0;
	m_wndGrid.hInitGrid();

}

bool CArthersView::ValidateSuchb()
{
	m_Suchb.p_GetInput();
	if ( !m_Suchb.Validate( TRUE ) )
		return false;
	return true;
}

////////////////////////////////////////////////////////////
//  Sql

void CArthersView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "PZN",	MAX_LENGTH_ARTICLE_NO },	
		{ "Einheit",		 9 },
		{ "Name",			30 },
		{ "VPE1",			 6 },
		{ "VPE2",			 6 },
		{ "VPE3",			 6 },
		{ "VPE4",			 6 },
		{ NULL,				-1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );

}


void CArthersView::FillGrid( void *pp, int index )
{
	struct BUFF_ARTHERS *p;
	ROWCOL Row;

	CString cStr;
	CString temp;

	Row = index;
	p = (struct BUFF_ARTHERS *) pp;

	temp.Format( "%c%ds", '%', MAX_LENGTH_ARTICLE_NO );
	cStr.Format( temp, p->ARTICLE_CODE );
	m_wndGrid.SetValueRange(CGXRange ( Row, 1 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 2 ), p->EINHEIT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 3 ), p->ARTIKEL_NAME );
	cStr.Format( "%6.0ld", p->VERPACKEINHEIT1 );
	m_wndGrid.SetValueRange(CGXRange ( Row, 4 ), cStr );
	cStr.Format( "%6.0ld", p->VERPACKEINHEIT2 );
	m_wndGrid.SetValueRange(CGXRange ( Row, 5 ), cStr );
	cStr.Format( "%6.0ld", p->VERPACKEINHEIT3 );
	m_wndGrid.SetValueRange(CGXRange ( Row, 6 ), cStr );
	cStr.Format( "%6.0ld", p->VERPACKEINHEIT4 );
	m_wndGrid.SetValueRange(CGXRange ( Row, 7 ), cStr );
}

void CArthersView::FillBox( int anz )
{
	void *p;
	int i;

	BOOL bLockOld = m_wndGrid.LockUpdate(TRUE);
	m_wndGrid.SetReadOnly( FALSE );

	i = 0;
	do
	{
		p = m_hSelSql.GetBuffer( i );
		if ( p != NULL )
		{
			FillGrid( p, i + 1);
			i++;
		}
	} while ( i < anz && p != NULL );
	
	
	m_wndGrid.hInitRestGrid( ++i );

	m_wndGrid.SetReadOnly( );
	m_wndGrid.LockUpdate(bLockOld);
	m_wndGrid.RedrawRowCol( 1, 1,
							m_wndGrid.GetRowCount( ),
							m_wndGrid.GetColCount( ) );

	// Deselect whole table
	m_wndGrid.SelectRange(CGXRange( ).SetTable( ), FALSE);
	// Select Row 1
	m_wndGrid.SelectRange(CGXRange( ).SetRows(1,1), TRUE);
	m_wndGrid.SetCurrentCell( 1, 0 );
	m_wndGrid.Redraw();
}

CString CArthersView::GetSelect( )
{
	CString sql;
	CString snr;
	CString cAktOrder;
	long nr;

	UpdateData( TRUE );
	m_Suchb.GetWindowText( snr );
	snr.TrimLeft();
	snr.TrimRight();

	nr = atol( snr );

	if ( m_rdName.GetCheck() == 1 )
		cAktOrder = "Z.ARTIKEL_NAME";
	else
		cAktOrder = "1";

	CString selFields;
	selFields.Format(PROJ_ARTHERS, MAX_LENGTH_ARTICLE_NO);

	sql.Format( "select %s from CARTICLECODES C,ZARTIKEL Z,outer ARTVE V where " \
				"Z.HERSTELLER_NR=%ld and " \
				"Z.ARTIKEL_NR=C.ARTICLENO and " \
				"C.PREFERRED_FLAG = 1 and C.CODE_TYPE IN (select CODE_TYPE from CCODETYPES where ARTNR_SUBSTITUTE = 1) and " \
		        "V.ARTIKEL_NR=Z.ARTIKEL_NR " \
				"order by %s",
				selFields,
				nr,
				cAktOrder );

	return sql;
}


void CArthersView::EnableOrder( BOOL mode )
{
	m_rdNr.EnableWindow( mode );
	m_rdName.EnableWindow( mode );
}


int  CArthersView::BearbeiteSatz()
{
	if ( GetFocus() == &m_Suchb )
	{
	EnableOrder( TRUE );

		if ( SucheSatz() == 1 )
			return 3;
		else 
			return -1;
	}
	else
		return -1;
}

int CArthersView::SucheSatz( )
{
	CString cErrmld;
	int anz;

	if ( !ValidateSuchb() )
		return -1;

// ??????????????????????????????
	m_nNumberOfRows = 0;
//	m_wndGrid.hZeroGrid();
	m_wndGrid.hInitGrid();
// ???????????????????????????????

	m_sSql = GetSelect();

	theApp->BeginWaitAction( );

	anz = m_hSelSql.StartSelect(m_sSql,
								m_hSelSql.S_WITH_SCROLL | m_hSelSql.S_WITHOUT_HOLD,
								GRID_ROWS,
								cErrmld);

	theApp->EndWaitAction( );
	if ( anz <= 0 )
	{
		AfxMessageBox( cErrmld );
		m_wndGrid.hInitGrid();
		m_nNumberOfRows = 0;
		theApp->SetMenuOnOff( 0, 0, 0, 0, -1, -1 );  
	}
	else
	{
		FirstInitGrid();
		FillBox( anz );
		m_nNumberOfRows = anz;
			theApp->SetMenuOnOff( 0, 0, 0, 0, 1, -1 );  
	}

	EnableOrder( m_nNumberOfRows <= 0 );

	if ( m_nNumberOfRows > 0 )
		return  1;
	else
		return -1;
}

int CArthersView::NextSatz( )
{
	CString cErrmld;
	int anz;
	theApp->BeginWaitAction( );
	anz = m_hSelSql.NextSelect( cErrmld );
	theApp->EndWaitAction( );
	if ( anz <= 0 )
	{
		AfxMessageBox( cErrmld );
		theApp->SetMenuOnOff( 0, 0, 0, 0, -1, 0 ); 
	}
	else
	{
//		FirstInitGrid();	// !!!!!!!!!!!!!!!!!!!!
		FillBox( anz );
		m_nNumberOfRows = anz;
		theApp->SetMenuOnOff( 0, 0, 0, 0, 0, 1 ); 
	}

	return -1;
}

int CArthersView::PrevSatz()
{
	CString cErrmld;
	int anz;
	theApp->BeginWaitAction( );
	anz = m_hSelSql.PrevSelect( cErrmld );
	theApp->EndWaitAction( );
	if ( anz <= 0 )
	{
		AfxMessageBox( cErrmld );
		theApp->SetMenuOnOff( 0, 0, 0, 0, 0, -1 ); 
	}
	else
	{
		FillBox( anz );
		m_nNumberOfRows = anz;
		theApp->SetMenuOnOff( 0, 0, 0, 0, 1, 0 ); 
	}

	return -1;
}


int  CArthersView::UndoSatz()
{
	if ( !m_bComeBack )
	{
		m_hSelSql.CloseCursor( );
		return 0;
	}
	else
		return 0; // -1;
}

/////////////////////////////////////////////////////////////////////////////
// CArthersView message handlers

void CArthersView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CArthersView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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
				theApp->SetMenuOnOff( 1, -1, 0, 1, 0, 0 ); 
			}
			else
			{
				m_bComeBack = false;
				FillBox( m_nNumberOfRows );
				theApp->PopMenuState(  );
				theApp->SetMenuOnOff( 0, 0, 0, 0, 1, 1 ); 
			}
		}	
	}
}

void CArthersView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CArthersView::ResizeControls( int cx, int cy ) 
{
	CFrameWnd *pFrameWnd = GetParentFrame();

	CRect thisRect;
	CRect FrameRect;
	CRect CtrlRect;

	int RandBreite;
	int CtrlBreite;
	int RandHoehe;

	pFrameWnd->GetWindowRect( FrameRect );	
	this->GetWindowRect( thisRect );
	m_wndGrid.GetWindowRect( CtrlRect );

//	RandBreite = CtrlRect.left - FrameRect.left;
	RandBreite = CtrlRect.left - thisRect.left;
	CtrlBreite = cx - 2*RandBreite;

	if ( m_wndGrid.GetGridBreite() < CtrlBreite )
		CtrlBreite = m_wndGrid.GetGridBreite();

	CtrlRect.right = CtrlRect.left + CtrlBreite;
/*
	CString s; 
	s.Format( "f.left=%d f.right=%d\nt.left=%d t.rigth=%d\n" \
			  "f.topp=%d f.bottt=%d\nt.topp=%d t.bottt=%d\n",
			   FrameRect.left, FrameRect.right, Rect.left, Rect.right, 
			   FrameRect.top, FrameRect.bottom, Rect.top, Rect.bottom   );
	AfxMessageBox( s );
*/


//	RandHoehe = 2*m_wndGrid.GetRowHeight( 0 );
//	CtrlRect.bottom = FrameRect.bottom - RandHoehe;

	RandHoehe = ( 15*m_wndGrid.GetRowHeight( 0 ) ) / 10;
	int rand1 = thisRect.bottom - RandHoehe;
	int rand2 = CtrlRect.top + m_wndGrid.GetGridHoehe();
	if ( rand1 < rand2 )
		CtrlRect.bottom = rand1;
	else
		CtrlRect.bottom = rand2;

	ScreenToClient( CtrlRect );
	m_wndGrid.MoveWindow( CtrlRect, FALSE );

	Invalidate();	// !!!!!!!!!!!!!!!!!!!!!!!!!

}


///////////////////////////////////////////////////
//

void CArthersView::OnSetfocusArthersSuchb() 
{
	// TODO: Add your control notification handler code here
	EnableOrder( TRUE );		
}

//////////////////////////////////////////////////
//	Drucken

void CArthersView::FillZeile( void *pp , CString& cStr )
{
	struct BUFF_ARTHERS *p;

	p = (struct BUFF_ARTHERS *) pp;
	
	cStr.Format( "%s %s %s %5.0ld %5.0ld %5.0ld %5.0ld",
				p->ARTICLE_CODE,
				p->EINHEIT,
				p->ARTIKEL_NAME,
				p->VERPACKEINHEIT1,
				p->VERPACKEINHEIT2,
				p->VERPACKEINHEIT3,
				p->VERPACKEINHEIT4 );
}

CString CArthersView::GetListHeader()
{
	return _T( "PZN        Einheit Artikelname                   " \
			   "  Vpe1  Vpe1  Vpe3  Vpe4"; );
}


bool CArthersView::IsPrintZeile()
{
	void* p;
	p = m_hSelSql.GetBuffer( m_nSelectZeile );
	if ( p != NULL ) 
		return true;

	CString cErrmld;
	int anz = m_hSelSql.NextSelect( cErrmld );
	if ( anz <= 0 )
		return false;

	m_nNumberOfRows = anz;
	m_nSelectZeile = 0;
	p = m_hSelSql.GetBuffer( m_nSelectZeile );
	return p != NULL;
}

void* CArthersView::GetPrintZeile()
{
	return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CArthersView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
{
	CString s;
	long datum;
	long zeit;
	char datstr[15];
	datum = ::ActualDateTime( &zeit );
	ConvFromPhoDate( datstr, datum, "tt.mm.jj" );
	s.Format( "%s %02d:%02d   Seite %d",
		      datstr, zeit/10000, (zeit/100)%100, nSeite );
	cText.TrimRight();
	nLng -= cText.GetLength() + s.GetLength();
	if ( nLng <= 0 ) nLng = 1;
	cStr = cText;
	while ( nLng-- > 0 )
		cStr += " ";
	cStr += s;
}

bool CArthersView::GetInfoFromCallingView( CString& cStr, int nAction )
{

	if ( nAction == -1 )
	{
		cStr.Format( "%d", 72 );		// Druckbreite
		return true;
	}


	cStr = " ";
	if ( !IsPrintZeile() )
		return false;

	if ( nAction == 0 )
	{
		m_nZeile = 0;
		return true;
	}

	switch( ++m_nZeile )
	{
	case 1:
		{
			CString cText;
			cText.Format( "Artikelsortiment Hersteller: %ld", m_nSuchNr );
			GenHeader( cStr, cText, ++m_nSeite, 72 );
		}
		break;
	case 2:
		cStr = "                 " + m_cName;
		break;
	case 3:
		break;
	case 4:
		cStr = GetListHeader();
		break;
	case 5:
		cStr  = "------------------------------------------------";
		cStr += "------------------------";
		break;
	case 6:
		break;
	default:
		FillZeile( GetPrintZeile(), cStr );	
		break;
	}

	return true;
}

void CArthersView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}

void CArthersView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );	
}

void CArthersView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );	
}


//////////////////////////////////////////////////////
// Datei speichern

void CArthersView::OnFileSpeichern() 
{
	char BASED_CODE szFilter[] = 
		 "List Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	CFileDialog dlg( FALSE, "txt",
							NULL,
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							szFilter );         

	if ( dlg.DoModal() != IDOK )
		return;

	CString sFileName;
	sFileName = dlg.GetPathName();	
	if ( sFileName.IsEmpty( ) )
		return;

	CStdioFile f;
	CFileException e; 
	CString sErrmld;
	
	if( !f.Open( sFileName,  CFile::modeCreate | CFile::modeWrite, &e ) )
    {
		sErrmld.Format( "Datei wurde nicht eröffnet ( %d )", e.m_cause );
		AfxMessageBox( 	sErrmld );
		return;
    }

	// schleife
	CString s;

	s = GetListHeader();
	s += _T("\n");
	f.Write( (LPCTSTR) s, s.GetLength() );

	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile

	while  ( IsPrintZeile() )
	{
		void *pp;
		while ( pp = GetPrintZeile() )
		{
			FillZeile( pp, s );	
			s += _T("\n");
			f.Write( (LPCTSTR) s, s.GetLength() );
		}	
	} 

	f.Close();

	// SelectBox am Ende des Druckauftrages Fuellen
	FillBox( m_nNumberOfRows );	
}

void CArthersView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}
