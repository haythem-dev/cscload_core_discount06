// NonemlieView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "zdpdruck.h"
#include "NonemlieView.h"

#include <eklibs/hamfcs/hMskDate.h>
#include "ViewNumbers.h"

#include "ServerDatum.h"
#include <hdatum/Phodate.h>

#include <libscsvoodoo/libscsvoodoo.h>
#include <eklibs/sqltabs/tabsqld.h>

#include <voodoo_table_header/liefer.h>
#include <voodoo_table_header/herstel.h>

#include "FeldBreite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNonemlieView

IMPLEMENT_DYNCREATE(CNonemlieView, CFormView)

CNonemlieView::CNonemlieView()
	: ChPflegeView(CNonemlieView::IDD)
{
	//{{AFX_DATA_INIT(CNonemlieView)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
}

CNonemlieView::~CNonemlieView()
{
}

void CNonemlieView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNonemlieView)
	DDX_Control(pDX, IDC_NONEMLIE_DATBIS, m_DATUMBIS);
	DDX_Control(pDX, IDC_NONEMLIE_DATVON, m_DATUMVON);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNonemlieView, CFormView)
	//{{AFX_MSG_MAP(CNonemlieView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CNonemlieView

#ifdef _DEBUG
void CNonemlieView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNonemlieView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////
// Implementation

void CNonemlieView::InitPflege()
{
	m_wndGrid.SubclassDlgItem(IDC_NONEMLIE_GRID, this );
	m_wndGrid.Initialize();	
	m_wndGrid.hZeroGrid();
	m_nNumberOfRows = 0;
	FirstInitGrid( );

	m_DATUMVON.SetMask(ED_LDATE,
					   ED_NORMAL,
					   &m_nDatumVon,
                       L_LDATUM,
                       new ChMaskLDate);
					  
	m_DATUMVON.SetDialog( TRUE );

	m_nDatumVon = 0;

	m_DATUMBIS.SetMask(ED_LDATE,
					   ED_NORMAL,
					   &m_nDatumBis,
                       L_LDATUM,
                       new ChMaskLDate);
					  
	m_DATUMBIS.SetDialog( TRUE );

	m_nDatumBis = 0;

}

void CNonemlieView::InitVariables()
{
	m_nDatumVon = 0;
	m_nDatumBis = 0;
	m_DATUMVON.p_SetInput();
	m_DATUMBIS.p_SetInput();
	m_nNumberOfRows = 0;
	m_wndGrid.hInitGrid();

	m_DATUMVON.SetFocus();
}

bool CNonemlieView::ValidateSuchb()
{
	m_DATUMVON.p_GetInput();
	m_DATUMBIS.p_GetInput();

	if ( TestPhoDate( m_nDatumVon ) == 0 )	// Null zulassen
	{
		AfxMessageBox( "DatumVon nicht korrekt" );
		return false;
	}
	if ( TestPhoDate( m_nDatumBis ) == 0 )	// Null zulassen
	{
		AfxMessageBox( "DatumBis nicht korrekt" );
		return false;
	}

	if ( m_nDatumVon > m_nDatumBis )
	{
		AfxMessageBox( "DatumVon <= DatumBis" );
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////
//  Sql

void CNonemlieView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "LiefNr",			  5 },	
		{ "Lieferantenname", 30 },
		{ "Ort",             30 },
		{ "Änder-Datum",	 10 },
		{ "NEM",			  1 },
		{ NULL,				 -1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );

}


struct BUFF_NONEMLIE
{
	long LANT_NR;
	char LANT_NAME[L_LIEFER_LANT_NAME + 1];
	char ORT[L_LIEFER_ORT + 1];
	char NEM[L_LIEFER_NAHRUNGSERGAENZUNG + 1];
	long DATUM_AENDER;
};


void CNonemlieView::FillGrid( void *pp, int index )
{
	struct BUFF_NONEMLIE *p;
	ROWCOL Row;

	CString cStr;

	char dat_str[12];

	Row = index;

	p = (struct BUFF_NONEMLIE *) pp;

	ConvFromPhoDate( dat_str, p->DATUM_AENDER, "tt.mm.jjjj" );

	cStr.Format( "%5.5ld", p->LANT_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 1 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 2 ), p->LANT_NAME );
	m_wndGrid.SetValueRange(CGXRange ( Row, 3 ), p->ORT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 4 ), dat_str );
	m_wndGrid.SetValueRange(CGXRange ( Row, 5 ), p->NEM );
}

void CNonemlieView::FillBox( int anz )
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



//////////////////////////////////////////////////////////////
// Tabellenbeschreibung


CString CNonemlieView::GetSelect( )
{
	CString sql;

	sql = "select lant_nr,lant_name,ort,nahrungsergaenzung,datum_aender " \
		  "from liefer where ";
	if ( m_nDatumVon > 0 )
	{
		CString sql1;
		sql1.Format( "datum_aender>=%ld and datum_aender<=%ld and ",
					 m_nDatumVon,
					 m_nDatumBis );
		sql += sql1;
	}

	sql += "nahrungsergaenzung='N' order by lant_name";


/*
	sql.Format( "select lant_nr,lant_name,ort,nahrungsergaenzung,datum_aender " \
		        "from liefer where " \
				"datum_aender>=%ld and datum_aender<=%ld and " \
				"nahrungsergaenzung='N' " \
				"order by lant_name",
				m_nDatumVon,
				m_nDatumBis );
*/				 
//	AfxMessageBox( sql );

	return sql;
}


void CNonemlieView::EnableOrder( BOOL mode )
{
//	m_rdNr.EnableWindow( mode );
//	m_rdName.EnableWindow( mode );
}


int  CNonemlieView::BearbeiteSatz()
{

	if ( GetFocus() == &m_DATUMBIS )
	{
		if ( SucheSatz() == 1 )
			return 3;
		else 
			return -1;
	}
	else
	{
		((CDialog*) this)->NextDlgCtrl( );
		return -1;
	}
}

int CNonemlieView::SucheSatz( )
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

	if ( m_sSql.IsEmpty() )
		return -1;

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

int CNonemlieView::NextSatz( )
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

int CNonemlieView::PrevSatz()
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


int  CNonemlieView::UndoSatz()
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
// Behandlungsroutinen für Nachrichten CNonemlieView 

void CNonemlieView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CNonemlieView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

void CNonemlieView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CNonemlieView::ResizeControls( int cx, int cy ) 
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

//////////////////////////////////////////////////
//	Drucken

void CNonemlieView::FillZeile( void *pp , CString& cStr )
{
	char dat_str[12];
	struct BUFF_NONEMLIE *p;

	p = (struct BUFF_NONEMLIE *) pp;

	ConvFromPhoDate( dat_str, p->DATUM_AENDER, "tt.mm.jjjj" );
	
	cStr.Format( "%5.5ld  %s %s %s  %s",
				p->LANT_NR,
				p->LANT_NAME,
				p->ORT,
				dat_str,
				p->NEM );
}

CString CNonemlieView::GetListHeader()
{
	return _T( "LiefNr Lieferantenname                Ort                            " \
		       "Änder-Datum NEM" );
}

CString CNonemlieView::GetListStrich()
{
	return _T( "---------------------------------------------------------------------" \
		       "---------------" );
}

bool CNonemlieView::IsPrintZeile()
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

void* CNonemlieView::GetPrintZeile()
{
	return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CNonemlieView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
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
	nLng -= cText.GetLength() + s.GetLength() + 6;
	if ( nLng <= 0 ) nLng = 1;
	cStr = cText;
	while ( nLng-- > 0 )
		cStr += " ";
	cStr += s;
}

bool CNonemlieView::GetInfoFromCallingView( CString& cStr, int nAction )
{

	int DruckBreite = 90;
	if ( nAction == -1 )
	{
		cStr.Format( "%d", DruckBreite );		// Druckbreite
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
			cText = "Lieferanten ohne NEM-Kennung";
			if ( m_nDatumVon > 0 )
			{
				char cDatVon[12];
				char cDatBis[12];
				CString cText1;
				ConvFromPhoDate ( cDatVon, m_nDatumVon, "tt.mm.jjjj" );
				ConvFromPhoDate ( cDatBis, m_nDatumBis, "tt.mm.jjjj" );
				cText1.Format( " vom %s - %s", cDatVon, cDatBis );
				cText += cText1;
			}
			GenHeader( cStr, cText, ++m_nSeite, DruckBreite );
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
		cStr  = GetListStrich();
		break;
	case 6:
		break;
	default:
		FillZeile( GetPrintZeile(), cStr );	
		break;
	}

	return true;
}

void CNonemlieView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}


void CNonemlieView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CNonemlieView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern

void CNonemlieView::OnFileSpeichern() 
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

void CNonemlieView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}

