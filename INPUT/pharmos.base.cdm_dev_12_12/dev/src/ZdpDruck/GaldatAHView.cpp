// GaldatAHView.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "ZdpDruck.h"
#include "GaldatAHView.h"

#include <eklibs/hamfcs/hMskDate.h>
#include "ViewNumbers.h"

#include "ServerDatum.h"
#include <hdatum/Phodate.h>

#include <libscsvoodoo/libscsvoodoo.h>

//#include <konvbuf.h>
#include <eklibs/sqltabs/tabsqld.h>
#include <eklibs/wunxlocs/hUnixStdout.h>

#include <voodoo_table_header/zartikel.h>
#include "FeldBreite.h"

// CGaldatAHView

IMPLEMENT_DYNCREATE(CGaldatAHView, CFormView)

CGaldatAHView::CGaldatAHView()
	: ChPflegeView(CGaldatAHView::IDD)
{
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
}

CGaldatAHView::~CGaldatAHView()
{
}

void CGaldatAHView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATVON, m_DATUMVON);
	DDX_Control(pDX, IDC_DATBIS, m_DATUMBIS);

}

BEGIN_MESSAGE_MAP(CGaldatAHView, CFormView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
END_MESSAGE_MAP()


// CGaldatAHView-Diagnose

#ifdef _DEBUG
void CGaldatAHView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGaldatAHView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CGaldatAHView-Meldungshandler
void CGaldatAHView::InitPflege()
{
	m_wndGrid.SubclassDlgItem(IDC_GALDAT_GRID, this );
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

void CGaldatAHView::InitVariables()
{
	long zeit;

	m_nDatumVon = 0;
    m_nDatumBis = ::ActualDateTime( &zeit );

	m_DATUMVON.p_SetInput();
	m_DATUMBIS.p_SetInput();

	m_nNumberOfRows = 0;
	m_wndGrid.hInitGrid( GRID_ROWS, -1);
	m_DATUMVON.SetFocus();
}

bool CGaldatAHView::ValidateSuchb()
{
	m_DATUMVON.p_GetInput();
	m_DATUMBIS.p_GetInput();

	if ( TestPhoDate( m_nDatumVon ) != 2 )
	{
		AfxMessageBox( "DatumVon nicht korrekt" );
		return false;
	}
	if ( TestPhoDate( m_nDatumBis ) != 2 )
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


void CGaldatAHView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "ArtikelNr",		  7 },	
		{ "Änderung",		 10 },
		{ "Bezeichnung",     30 },
		{ "Outsal",			 10 },
		{ "AH-Datum",		 10 },
		{ "LI-Nachfolger",	  7 },
		{ "ErsatzNr",		  7 },
		{ NULL,				 -1 },
	};
	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );
}

struct BUFF_GALDAT
{
	long ARTICLENO;
	long DATE_CHANGED;
	char ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME + 1];
	long OUTSAL;
	long DATUM_AH;
	long REPL_ARTICLE;
	long ERSATZ_NR;
};


void CGaldatAHView::FillGrid( void *pp, int index )
{
	struct BUFF_GALDAT *p;
	ROWCOL Row;
	char dat_str[12];
	CString cStr;

	Row = index;

	p = (struct BUFF_GALDAT *) pp;

	cStr.Format( "%7.7ld", p->ARTICLENO );
	m_wndGrid.SetValueRange(CGXRange ( Row, 1 ), cStr );

	ConvFromPhoDate( dat_str, p->DATE_CHANGED, "tt.mm.jjjj" );
	m_wndGrid.SetValueRange(CGXRange ( Row, 2 ), dat_str );
	m_wndGrid.SetValueRange(CGXRange ( Row, 3 ), p->ARTIKEL_NAME  );
	cStr.Format( "%8.8ld", p->OUTSAL );
	m_wndGrid.SetValueRange(CGXRange ( Row, 4 ), cStr );
	cStr.Format( "%8.8ld", p->DATUM_AH );
	m_wndGrid.SetValueRange(CGXRange ( Row, 5 ), cStr );
	cStr.Format( "%7.7ld", p->REPL_ARTICLE );
	m_wndGrid.SetValueRange(CGXRange ( Row, 6 ), cStr );
	cStr.Format( "%7.7ld", p->ERSATZ_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 7 ), cStr );
}

void CGaldatAHView::FillBox( int anz )
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

void CGaldatAHView::GetDelimiter( char *info, char *delim )
{
	int lng;
	lng = static_cast<int>(strlen( info )) - 1;
    while ( info[lng] == ' ' ) lng--;
    *delim = info[lng++];
    info[lng] = '\0';
}

CString CGaldatAHView::GetSelect( )
{
	CString sql;

/* 21.11.2005 Artikel die bei uns AH sind aber bei der Galdat nicht sind nicht von Interesse */
/*            Sortierung nach Artikelname                                                    */


/*	sql.Format("select a.articleno,a.date_changed, artikel_name, salecode, datum_ah, repl_article, ersatz_nr " \
		       " from cgal30o01 a , zartikel b, cgal30o04 c where a.articleno = b.artikel_nr  and a.articleno = c.articleno " \
			   " and a.date_changed >= %ld and a.date_changed <= %ld" \
			   " and ((a.salecode = 'H' and datum_ah = 0) " \
			   " or (c.repl_article != ersatz_nr)) order by artikel_name ",m_nDatumVon,m_nDatumBis);*/

// Änderung auf LogIndex: Stand 24.06.2014 kein Datum von / bis zum Einschränken vorhanden: */
	
		sql.Format("select a.phar, a.datum_aender, b.artikel_name, a.outsal, b.datum_ah, 0 as nachfolger, b.ersatz_nr "
					" from clioart a , zartikel b where a.phar = b.artikel_nr "
					" and a.datum_aender >= %ld and a.datum_aender <= %ld "
					" and outsal > 0 and datum_ah = 0 "
					" UNION " 
					" select a.phar2, a.datum_aender, b.artikel_name, 0 as outsal, b.datum_ah, a.phar, b.ersatz_nr "
					" from clioart a , zartikel b where a.phar2 = b.artikel_nr "
					" and a.datum_aender >= %ld and a.datum_aender <= %ld "
					" and phar != ersatz_nr "
					" order by artikel_name "
			   ,m_nDatumVon,m_nDatumBis,m_nDatumVon,m_nDatumBis)
			   ;

		return sql;
}

void CGaldatAHView::EnableOrder( BOOL mode )
{
}


int CGaldatAHView::BearbeiteSatz()
{
	return -1;
}

int CGaldatAHView::SucheSatz( )
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

int CGaldatAHView::NextSatz( )
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

int CGaldatAHView::PrevSatz()
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


int  CGaldatAHView::UndoSatz()
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

void CGaldatAHView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CGaldatAHView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

void CGaldatAHView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CGaldatAHView::ResizeControls( int cx, int cy ) 
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
	char ARTICLENO[7];
	char fil1[2];
	char DATE_CHANGED[10];
	char fil2[1];
	char ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME];
	char fil3[1];
	char OUTSAL[8];
	char fil4[1];
	char DATUM_AH[8];
	char fil5[1];
	char REPL_ARTICLE[7];
	char fil6[1];
	char ERSATZ_NR[7];
	char eof[1];
};

void CGaldatAHView::FillZeile( void *pp , CString& cStr )
{
	struct BUFF_GALDAT *p;
	struct DRUCK_ZEILE d;	
	char dat_str[12];

	p = (struct BUFF_GALDAT *) pp;

	sprintf( d.ARTICLENO, "%7.7ld", p->ARTICLENO );
	memset( d.fil1, ' ', 2 );
	ConvFromPhoDate( dat_str, p->DATE_CHANGED, "tt.mm.jjjj" );
	memcpy( d.DATE_CHANGED , dat_str, 10 );
	memset( d.fil2, ' ', 1 );
	memcpy( d.ARTIKEL_NAME, p->ARTIKEL_NAME, L_ZARTIKEL_ARTIKEL_NAME );
	memset( d.fil3, ' ', 1 );
	sprintf( d.OUTSAL, "%8.8ld", p->OUTSAL );
	memset( d.fil4, ' ', 1 );
	sprintf( d.DATUM_AH, "%8.8ld", p->DATUM_AH );
	memset( d.fil5, ' ', 1 );
	sprintf( d.REPL_ARTICLE, "%7.7ld", p->REPL_ARTICLE );
	memset( d.fil6, ' ', 1 );
	sprintf( d.ERSATZ_NR, "%7.7ld", p->ERSATZ_NR );
	memset( d.eof, '\0', 1 );
	cStr = ( char *) &d;


}

CString CGaldatAHView::GetListHeader()
{
	return _T( "ArtikelNr Änderung  Bezeichnung                    AH                Ersatz-Nr"  );
}

CString CGaldatAHView::GetListStrich()
{
	return _T( "---------------------------------------------------------------------" \
		       "---------------------------" );
}

bool CGaldatAHView::IsPrintZeile()
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

void* CGaldatAHView::GetPrintZeile()
{
		return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CGaldatAHView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
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

bool CGaldatAHView::GetInfoFromCallingView( CString& cStr, int nAction )
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
			char cDatVon[12];
			char cDatBis[12];
			CString cText;
			ConvFromPhoDate ( cDatVon, m_nDatumVon, "tt.mm.jjjj" );
			ConvFromPhoDate ( cDatBis, m_nDatumBis, "tt.mm.jjjj" );
			cText.Format( "LogIndex Änderungen Differenzen AH/Ersatz-Nr  %s - %s",cDatVon, cDatBis);
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

void CGaldatAHView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}


void CGaldatAHView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CGaldatAHView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern

void CGaldatAHView::OnFileSpeichern() 
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

void CGaldatAHView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}

///////////////////////////////////////////////////////////////////
//  Ueber UnixStdOut


void CGaldatAHView::FillString( char *str, CString cStr, int lng )
{
	int lng1;
	lng1 = cStr.GetLength();
	if ( lng1 > lng )
		lng1 = lng;

	memset( str, ' ',  lng  );
	memcpy( str, cStr, lng1 );
	str[lng] = '\0';
}


void* CGaldatAHView::BufFromGrid( int Row )
{
	static struct BUFF_GALDAT p;

	Row++;
	p.ARTICLENO = atol( m_wndGrid.GetValueRowCol( Row, 1 ) );
	p.DATE_CHANGED = atol( m_wndGrid.GetValueRowCol( Row, 2 ) );
	FillString( p.ARTIKEL_NAME, m_wndGrid.GetValueRowCol( Row, 3 ), L_ZARTIKEL_ARTIKEL_NAME);
	p.OUTSAL = atol( m_wndGrid.GetValueRowCol( Row, 4 ) );
	p.DATUM_AH = atol( m_wndGrid.GetValueRowCol( Row, 5 ) );
	p.REPL_ARTICLE = atol( m_wndGrid.GetValueRowCol( Row, 6 ) );
	p.ERSATZ_NR = atol( m_wndGrid.GetValueRowCol( Row, 7 ) );

	return &p;
}

void CGaldatAHView::BufFromZeile( struct BUFF_GALDAT *p, CString Zeile )
{
	struct DRUCK_ZEILE d;

	strcpy( (char *) &d, Zeile );

	*d.fil1 = '\0';
	*d.fil2 = '\0';
	*d.fil3 = '\0';
	*d.fil4 = '\0';
	*d.fil5 = '\0';
	*d.fil6 = '\0';
	*d.eof  = '\0',

	p->ARTICLENO = atol( d.ARTICLENO );
	p->DATE_CHANGED = atol( d.DATE_CHANGED );
	strcpy( p->ARTIKEL_NAME, d.ARTIKEL_NAME );
	p->OUTSAL = atol( d.OUTSAL );
	p->DATUM_AH = atol( d.DATUM_AH );
	p->REPL_ARTICLE = atol( d.REPL_ARTICLE );
	p->ERSATZ_NR = atol( d.ERSATZ_NR );
}


