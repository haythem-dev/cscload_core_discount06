// AmbliefView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "zdpdruck.h"
#include "AmbliefView.h"

#include <eklibs/hamfcs/hMskDate.h>
#include "ViewNumbers.h"

#include "ServerDatum.h"
#include <hdatum/Phodate.h>

#include <libscsvoodoo/libscsvoodoo.h>

//#include <konvbuf.h>
#include <eklibs/sqltabs/tabsqld.h>
#include <eklibs/wunxlocs/hUnixStdout.h>

#include <voodoo_table_header/liefer.h>

#include "FeldBreite.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAmbliefView

IMPLEMENT_DYNCREATE(CAmbliefView, CFormView)

CAmbliefView::CAmbliefView()
	: ChPflegeView(CAmbliefView::IDD)
{
	//{{AFX_DATA_INIT(CAmbliefView)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;

}

CAmbliefView::~CAmbliefView()
{
}

void CAmbliefView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAmbliefView)
		// HINWEIS: Der Klassen-Assistent fügt hier DDX- und DDV-Aufrufe ein
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAmbliefView, CFormView)
	//{{AFX_MSG_MAP(CAmbliefView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CAmbliefView

#ifdef _DEBUG
void CAmbliefView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAmbliefView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CAmbliefView 
void CAmbliefView::InitPflege()
{
	m_wndGrid.SubclassDlgItem(IDC_AMBLIEF_GRID, this );
	m_wndGrid.Initialize();	
	m_wndGrid.hZeroGrid();
	m_nNumberOfRows = 0;
	FirstInitGrid( );
}

void CAmbliefView::InitVariables()
{
	m_nNumberOfRows = 0;
	m_wndGrid.hInitGrid( GRID_ROWS, -1);

}

bool CAmbliefView::ValidateSuchb()
{
	return true;
}


void CAmbliefView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "LiefNr",			  5 },	
		{ "Lieferantenname", 30 },
		{ "Ort",             30 },
		{ "AMB",	          1 },
		{ "Bemerkungen",	 20 },
		{ NULL,				 -1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );

}


struct BUFF_AMBLIEF
{
	long LANT_NR;
	char LANT_NAME[L_LIEFER_LANT_NAME + 1];
	char ORT[L_LIEFER_ORT + 1];
	char AMB[L_LIEFER_ARZNEIMITTELBEZUG + 1];
	char BEMERKUNGEN[L_LIEFER_BEMERKUNGEN + 1];	/* Nur die ersten 20 Stellen */
	char LANT_MC[L_LIEFER_LANT_MC + 1];
};


void CAmbliefView::FillGrid( void *pp, int index )
{
	struct BUFF_AMBLIEF *p;
	ROWCOL Row;

	CString cStr;

	Row = index;

	p = (struct BUFF_AMBLIEF *) pp;

	cStr.Format( "%5.5ld", p->LANT_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 1 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 2 ), p->LANT_NAME );
	m_wndGrid.SetValueRange(CGXRange ( Row, 3 ), p->ORT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 4 ), p->AMB );
	m_wndGrid.SetValueRange(CGXRange ( Row, 5 ), p->BEMERKUNGEN  );

}

void CAmbliefView::FillBox( int anz )
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

void CAmbliefView::GetDelimiter( char *info, char *delim )
{
	int lng;
	lng = static_cast<int>(strlen( info )) - 1;
    while ( info[lng] == ' ' ) lng--;
    *delim = info[lng++];
    info[lng] = '\0';
}

CString CAmbliefView::GetSelect( )
{
/*	CString sql = "select lant_nr,lant_name,ort,arzneimittelbezug " \
		          " from liefer where not arzneimittelbezug  in ('A','B','C')" \
				  " and lant_nr in " \
                  " (select distinct lant_nr from herlief where hersteller_nr in " \
                  " (select distinct hersteller_nr from zartikel where arzneimittel = 1)) " \
                  " order by lant_name";*/ 

/*	CString sql = "select lant_nr,lant_name,ort,arzneimittelbezug " \
		          " from liefer where not arzneimittelbezug  in ('A','B','C')" \
				  " and lant_nr in " \
				  " (select distinct lant_nr from bliefer where besla_nr in " \
				  " (select distinct besla_nr from bliesort a ,zartikel b where a.artikel_nr = b.artikel_nr and " \
				  " b.arzneimittel = 1 and b.datum_ah = 0 and b.nichtuebergh != '1')) " \
				  " order by lant_name"; */

	CString sql = "select lant_nr,lant_name,ort,arzneimittelbezug,bemerkungen,lant_mc " \
		          " from liefer where not arzneimittelbezug  in ('A','B','C','T','V','M','H','P','D','E')" \
				  " and lant_nr in " \
				  " (select distinct lant_nr from bliefer where besla_nr in " \
				  " (select distinct besla_nr from bliesort  where artikel_nr in " \
				  " (select artikel_nr from zartikel  where  " \
				  " arzneimittel = 1 and datum_ah = 0 and nichtuebergh != '1' and amg_ausnahmereg != 1 and medizinische_gase != 1 ))) " \
				  " order by lant_mc";


	return sql;
}

void CAmbliefView::EnableOrder( BOOL mode )
{
}


int CAmbliefView::BearbeiteSatz()
{
	return -1;
}

int CAmbliefView::SucheSatz( )
{
	CString cErrmld;
	int anz;

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

int CAmbliefView::NextSatz( )
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

int CAmbliefView::PrevSatz()
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


int  CAmbliefView::UndoSatz()
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
// Behandlungsroutinen für Nachrichten CNemwliefView 

void CAmbliefView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CAmbliefView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

void CAmbliefView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CAmbliefView::ResizeControls( int cx, int cy ) 
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

struct DRUCK_ZEILE
{
	char LANT_NR[5];
	char fil1[2];
	char LANT_NAME[L_LIEFER_LANT_NAME];
	char fil2[1];
	char ORT[L_LIEFER_ORT];
	char fil3[1];
	char AMB[L_LIEFER_ARZNEIMITTELBEZUG];
	char fil4[1];
	char BEMERKUNGEN[20];
	char eof[1];
};

void CAmbliefView::FillZeile( void *pp , CString& cStr )
{
	struct BUFF_AMBLIEF *p;
	struct DRUCK_ZEILE d;	

	p = (struct BUFF_AMBLIEF *) pp;

	sprintf( d.LANT_NR, "%5.5ld", p->LANT_NR );
	memset( d.fil1, ' ', 2 );
	memcpy( d.LANT_NAME, p->LANT_NAME, L_LIEFER_LANT_NAME );
	memset( d.fil2, ' ', 1 );
	memcpy( d.ORT, p->ORT, L_LIEFER_ORT );
	memset( d.fil3, ' ', 1 );
	memcpy( d.AMB, p->AMB, L_LIEFER_ARZNEIMITTELBEZUG );
	memset( d.fil4, ' ', 1 );
	memcpy( d.BEMERKUNGEN, p->BEMERKUNGEN, 20 );
	memset( d.eof, '\0', 1 );
	cStr = ( char *) &d;


}

CString CAmbliefView::GetListHeader()
{
	return _T( "LiefNr Lieferantenname                Ort                            " \
		       "AMB Bemerkungen" );
}

CString CAmbliefView::GetListStrich()
{
	return _T( "---------------------------------------------------------------------" \
		       "---------------------------" );
}

bool CAmbliefView::IsPrintZeile()
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

void* CAmbliefView::GetPrintZeile()
{
		return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CAmbliefView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
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

bool CAmbliefView::GetInfoFromCallingView( CString& cStr, int nAction )
{

	int DruckBreite = 100;
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
//			char cDatVon[12];
//			char cDatBis[12];
			CString cText;
//			ConvFromPhoDate ( cDatVon, m_nDatumVon, "tt.mm.jjjj" );
//			ConvFromPhoDate ( cDatBis, m_nDatumBis, "tt.mm.jjjj" );
			cText.Format( "Lieferanten mit Arzneimittelbezug ungleich A,B,C,T,V,M,P,H,D oder E");
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

void CAmbliefView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}


void CAmbliefView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CAmbliefView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern

void CAmbliefView::OnFileSpeichern() 
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

void CAmbliefView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}

///////////////////////////////////////////////////////////////////
//  Ueber UnixStdOut


void CAmbliefView::FillString( char *str, CString cStr, int lng )
{
	int lng1;
	lng1 = cStr.GetLength();
	if ( lng1 > lng )
		lng1 = lng;

	memset( str, ' ',  lng  );
	memcpy( str, cStr, lng1 );
	str[lng] = '\0';
}


void* CAmbliefView::BufFromGrid( int Row )
{
	static struct BUFF_AMBLIEF p;

	Row++;
	p.LANT_NR = atol( m_wndGrid.GetValueRowCol( Row, 1 ) );
	FillString( p.LANT_NAME, m_wndGrid.GetValueRowCol( Row, 2 ), L_LIEFER_LANT_NAME);
	FillString( p.ORT, m_wndGrid.GetValueRowCol( Row, 3 ), L_LIEFER_ORT );
	FillString( p.AMB, m_wndGrid.GetValueRowCol( Row, 4 ), L_LIEFER_ARZNEIMITTELBEZUG );
	FillString( p.BEMERKUNGEN, m_wndGrid.GetValueRowCol( Row, 5 ), 20 );

	//m_cNem.SetAt ( 0, nem_alt );
	//m_cNr.SetAt  ( 0, p.LANT_NR );
	return &p;
}

void CAmbliefView::BufFromZeile( struct BUFF_AMBLIEF *p, CString Zeile )
{
	struct DRUCK_ZEILE d;

	strcpy( (char *) &d, Zeile );

	*d.fil1 = '\0';
	*d.fil2 = '\0';
	*d.fil3 = '\0';
	*d.fil4 = '\0';
	*d.eof  = '\0',

	p->LANT_NR = atol( d.LANT_NR );
	strcpy( p->LANT_NAME, d.LANT_NAME );
	strcpy( p->ORT, d.ORT );

	strcpy( p->AMB, d.AMB );
	strcpy( p->BEMERKUNGEN, d.BEMERKUNGEN );

	//m_cNem.SetAt ( 0, d.NEM_ALT );
	//m_cNr.SetAt  ( 0, p->LANT_NR );
}





