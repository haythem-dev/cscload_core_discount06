// ArtblieView.cpp : implementation file
//

#include "stdafx.h"
#include "zdpdruck.h"
#include "ArtblieView.h"

#include "hSelectDialog.h"
#include <phxlib/BlieferSelCtrl.h>

#include <eklibs/hamfcs/hMskNum.h>
#include "ViewNumbers.h"

#include "ServerDatum.h"
#include <hdatum/Phodate.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtblieView

IMPLEMENT_DYNCREATE(CArtblieView, CFormView)

CArtblieView::CArtblieView()
	: ChPflegeView(CArtblieView::IDD)
{
	//{{AFX_DATA_INIT(CArtblieView)
	//}}AFX_DATA_INIT
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
}

CArtblieView::~CArtblieView()
{
}

void CArtblieView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtblieView)
	DDX_Control(pDX, IDC_ARTBLIE_RD_NR, m_rdNr);
	DDX_Control(pDX, IDC_ARTBLIE_RD_NAME, m_rdName);
	DDX_Control(pDX, IDC_ARTBLIE_SUCHB, m_Suchb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtblieView, CFormView)
	//{{AFX_MSG_MAP(CArtblieView)
	ON_WM_SIZE()
	ON_EN_SETFOCUS(IDC_ARTBLIE_SUCHB, OnSetfocusArtblieSuchb)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArtblieView diagnostics

#ifdef _DEBUG
void CArtblieView::AssertValid() const
{
	CFormView::AssertValid();
}

void CArtblieView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////
// Implementation

void CArtblieView::SucheBliefer( )
{
	CBlieferSelCtrl m_SelBox( IM_NUMBER_S );

	ChSelectDialog dlg( "Auswahl Bestelladresse", &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( &m_nSuchNr ) == 0 )
		{
			m_Suchb.p_SetInput();
			m_Suchb.SetFocus();
			ShowBliefer( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// Bliefer

void CArtblieView::ScanName( CString Name )
{
	int pos;
	pos = Name.Find( '\n' );
	if ( pos >= 0 )	
		m_cName = Name.Left( pos ) + ", " + Name.Mid( pos + 1 );
	else
		m_cName = Name;
}



BOOL CArtblieView::ShowBliefer( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	iStat = m_RD_BLIEFER.IPlausi( m_nSuchNr, Name, &Errmld);
	if ( bShow )	// neu
		GetDlgItem( IDC_ARTBLIE_SHOW )->SetWindowText( Name );
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

class CV_ARTIKEL_Bliefer : public ChValBase
{
public:
	CV_ARTIKEL_Bliefer( CArtblieView* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtblieView*)m_pWnd)->ShowBliefer( bMeldung, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtblieView*)m_pWnd)->SucheBliefer();
	}
};

void CArtblieView::InitPflege()
{
	m_wndGrid.SubclassDlgItem(IDC_ARTBLIE_GRID, this );
	m_wndGrid.Initialize();	
	m_wndGrid.hZeroGrid();
	m_nNumberOfRows = 0;
	FirstInitGrid( );


	m_Suchb.SetMask	(ED_LONG,
				     ED_NORMAL,
					 &m_nSuchNr,
					 5,
					 new ChMaskNum,
					 new CV_ARTIKEL_Bliefer( this ) );
	m_Suchb.SetDialog( TRUE );

	m_nSuchNr = 0;

	m_rdNr.SetCheck( 1 );
}

void CArtblieView::InitVariables()
{
	m_nSuchNr = 0;
	m_Suchb.p_SetInput();
	m_nNumberOfRows = 0;
	m_wndGrid.hInitGrid();

}

bool CArtblieView::ValidateSuchb()
{
	m_Suchb.p_GetInput();
	if ( !m_Suchb.Validate( TRUE ) )
		return false;
	return true;
}

////////////////////////////////////////////////////////////
//  Sql

void CArtblieView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "PZN",  MAX_LENGTH_ARTICLE_NO },	
		{ "Einheit",		 9 },
		{ "Name",			30 },
		{ "VPE1",			 6 },
		{ "VPE2",			 6 },
		{ "VPE3",			 6 },
		{ "VPE4",			 6 },
		{ "Lief-ArtikelNr",	15 },
		{ NULL,				-1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );

}

void CArtblieView::FillGrid( void *pp, int index )
{
	struct BUFF_ARTBLIE *p;
	ROWCOL Row;

	CString cStr;
	CString temp;

	Row = index;
	p = (struct BUFF_ARTBLIE *) pp;

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
	m_wndGrid.SetValueRange(CGXRange ( Row, 8 ), p->ARTIKEL_NR_BLIEFER );
}

void CArtblieView::FillBox( int anz )
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

CString CArtblieView::GetSelect( )
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
		cAktOrder = "S.BESLA_NR,1";

	CString selFields;
	selFields.Format(PROJ_ARTBLIE, MAX_LENGTH_ARTICLE_NO);

	sql.Format( "select %s from CARTICLECODES C,ZARTIKEL Z,BLIESORT S,outer ARTVE V,outer ARTNRBL B where " \
				"S.BESLA_NR=%ld and " \
		        "Z.ARTIKEL_NR=C.ARTICLENO and " \
				"C.PREFERRED_FLAG = 1 and C.CODE_TYPE IN (select CODE_TYPE from CCODETYPES where ARTNR_SUBSTITUTE = 1) and " \
		        "Z.ARTIKEL_NR=S.ARTIKEL_NR and " \
		        "V.ARTIKEL_NR=S.ARTIKEL_NR and " \
				"B.ARTIKEL_NR=S.ARTIKEL_NR and B.BESLA_NR=S.BESLA_NR " \
				"order by %s",
				selFields,
				nr,
				cAktOrder );

	return sql;
}


void CArtblieView::EnableOrder( BOOL mode )
{
	m_rdNr.EnableWindow( mode );
	m_rdName.EnableWindow( mode );
}


int  CArtblieView::BearbeiteSatz()
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

int CArtblieView::SucheSatz( )
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

int CArtblieView::NextSatz( )
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

int CArtblieView::PrevSatz()
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


int  CArtblieView::UndoSatz()
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
// CArtblieView message handlers

void CArtblieView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CArtblieView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

void CArtblieView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CArtblieView::ResizeControls( int cx, int cy ) 
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

void CArtblieView::OnSetfocusArtblieSuchb() 
{
	// TODO: Add your control notification handler code here
	EnableOrder( TRUE );	
}


//////////////////////////////////////////////////
//	Drucken

void CArtblieView::FillZeile( void *pp , CString& cStr )
{
	struct BUFF_ARTBLIE *p;

	p = (struct BUFF_ARTBLIE *) pp;
	
	cStr.Format( "%s %s %s %5.0ld %5.0ld %5.0ld %5.0ld %s",
				p->ARTICLE_CODE,
				p->EINHEIT,
				p->ARTIKEL_NAME,
				p->VERPACKEINHEIT1,
				p->VERPACKEINHEIT2,
				p->VERPACKEINHEIT3,
				p->VERPACKEINHEIT4,
				p->ARTIKEL_NR_BLIEFER  );
}

CString CArtblieView::GetListHeader()
{
	return _T( "PZN        Einheit Artikelname                   " \
	           "  Vpe1  Vpe1  Vpe3  Vpe4 ArtikelNrLief" );
}

bool CArtblieView::IsPrintZeile()
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

void* CArtblieView::GetPrintZeile()
{
	return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CArtblieView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
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


bool CArtblieView::GetInfoFromCallingView( CString& cStr, int nAction )
{

	if ( nAction == -1 )
	{
		cStr.Format( "%d", 86 );		// Druckbreite
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
			cText.Format( "Artikelsortiment Lieferant: %ld", m_nSuchNr );
			GenHeader( cStr, cText, ++m_nSeite, 86 );
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
		cStr += "--------------------------------------";
		break;
	case 6:
		break;
	default:
		FillZeile( GetPrintZeile(), cStr );	
		break;
	}

	return true;
}

void CArtblieView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}

void CArtblieView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CArtblieView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern


void CArtblieView::OnFileSpeichern() 
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

void CArtblieView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );		
}
