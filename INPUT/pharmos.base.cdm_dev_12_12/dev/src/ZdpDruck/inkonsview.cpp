// InkonsView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "zdpdruck.h"
#include "InkonsView.h"

#include <eklibs/hamfcs/hMskDate.h>
#include "ViewNumbers.h"

#include "ServerDatum.h"
#include <hdatum/Phodate.h>

#include <libscsvoodoo/libscsvoodoo.h>
#include <eklibs/sqltabs/tabsqld.h>

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/herstel.h>
#include <voodoo_table_header/carticlecodes.h>

#include "FeldBreite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInkonsView

IMPLEMENT_DYNCREATE(CInkonsView, CFormView)

CInkonsView::CInkonsView()
	: ChPflegeView(CInkonsView::IDD)
{
	//{{AFX_DATA_INIT(CInkonsView)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
}

CInkonsView::~CInkonsView()
{
}

void CInkonsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInkonsView)
	DDX_Control(pDX, IDC_INKONS_DATBIS, m_DATUMBIS);
	DDX_Control(pDX, IDC_INKONS_DATVON, m_DATUMVON);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInkonsView, CFormView)
	//{{AFX_MSG_MAP(CInkonsView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CInkonsView

#ifdef _DEBUG
void CInkonsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CInkonsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////
// Implementation

void CInkonsView::InitPflege()
{
	m_wndGrid.SubclassDlgItem(IDC_INKONS_GRID, this );
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

void CInkonsView::InitVariables()
{
	m_nDatumVon = 0;
	m_nDatumBis = 0;
	m_DATUMVON.p_SetInput();
	m_DATUMBIS.p_SetInput();
	m_nNumberOfRows = 0;
	m_wndGrid.hInitGrid();

	m_DATUMVON.SetFocus();
}

bool CInkonsView::ValidateSuchb()
{
	m_DATUMVON.p_GetInput();
	m_DATUMBIS.p_GetInput();

	if ( TestPhoDate( m_nDatumVon ) == 0 )
	{
		AfxMessageBox( "DatumVon nicht korrekt" );
		return false;
	}
	if ( TestPhoDate( m_nDatumBis ) == 0 )
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

void CInkonsView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "ArtNr", MAX_LENGTH_ARTICLE_NO},	
		{ "Einheit",		 9 },
		{ "Artikelname",	30 },
		{ "Anlagedatum",	10 },
		{ "NahrTest",		 1 },
		{ "NahrErg",         1 },
		{ "HestNr",		     5 },
		{ "Herstellername",	30 },
		{ NULL,				-1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );

}


struct BUFF_INKONS
{
	char ARTICLE_CODE[MAX_LENGTH_ARTICLE_NO + 1];
	char EINHEIT[L_ZARTIKEL_EINHEIT + 1];
	char ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME + 1];
	long DATUM_ANLAGE;
	char NAHRUNGSTEST[L_ZARTIKEL_NAHRUNGSTEST + 1];
	char NAHRUNGSERGAENZUNG[L_ZARTIKEL_NAHRUNGSERGAENZUNG + 1];
	long HERSTELLER_NR;
	char NAME[L_HERSTEL_NAME + 1 ];
};


void CInkonsView::FillGrid( void *pp, int index )
{
	struct BUFF_INKONS *p;
	ROWCOL Row;

	CString cStr;
	CString temp;
	char dat_str[12];

	Row = index;

	p = (struct BUFF_INKONS *) pp;

	temp.Format( "%c%ds", '%', MAX_LENGTH_ARTICLE_NO );
	cStr.Format( temp, p->ARTICLE_CODE );
	m_wndGrid.SetValueRange(CGXRange ( Row, 1 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 2 ), p->EINHEIT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 3 ), p->ARTIKEL_NAME );
	ConvFromPhoDate( dat_str, p->DATUM_ANLAGE, "tt.mm.jjjj" );
	m_wndGrid.SetValueRange(CGXRange ( Row, 4 ), dat_str );
	m_wndGrid.SetValueRange(CGXRange ( Row, 5 ), p->NAHRUNGSTEST );
	m_wndGrid.SetValueRange(CGXRange ( Row, 6 ), p->NAHRUNGSERGAENZUNG );
	cStr.Format( "%5.5ld", p->HERSTELLER_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 7 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 8 ), p->NAME );
}

void CInkonsView::FillBox( int anz )
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


CString CInkonsView::GetSelect( )
{
	CString sql;

	sql.Format( "select lpad(trim(ARTICLE_CODE), %d, 0),einheit,artikel_name,z.datum_anlage,nahrungstest," \
		   "nahrungsergaenzung,z.hersteller_nr,name from " \
		   "zartikel z,outer herstel h, carticlecodes where articleno = z.artikel_nr and PREFERRED_FLAG = 1 and CODE_TYPE IN " \
		   "(select CODE_TYPE from CCODETYPES where ARTNR_SUBSTITUTE = 1) and ",
		   MAX_LENGTH_ARTICLE_NO);

	if ( m_nDatumVon > 0 )
	{
		CString sql1;
		sql1.Format( "z.datum_aender>=%ld and z.datum_aender<=%ld and ",
					 m_nDatumVon,
					 m_nDatumBis );
		sql += sql1;
	}

	sql += "z.hersteller_nr=h.hersteller_nr and nahrungstest !=' ' and " \
		   "nahrungsergaenzung='N' order by hersteller_nr,artikel_name";
				 
//	AfxMessageBox( sql );

	return sql;
}


void CInkonsView::EnableOrder( BOOL mode )
{
//	m_rdNr.EnableWindow( mode );
//	m_rdName.EnableWindow( mode );
}


int  CInkonsView::BearbeiteSatz()
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

int CInkonsView::SucheSatz( )
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

int CInkonsView::NextSatz( )
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

int CInkonsView::PrevSatz()
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


int  CInkonsView::UndoSatz()
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
// Behandlungsroutinen für Nachrichten CInkonsView 

void CInkonsView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CInkonsView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

void CInkonsView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CInkonsView::ResizeControls( int cx, int cy ) 
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

void CInkonsView::FillZeile( void *pp , CString& cStr )
{
	char dat_str[12];
	struct BUFF_INKONS *p;

	p = (struct BUFF_INKONS *) pp;

	ConvFromPhoDate( dat_str, p->DATUM_ANLAGE, "tt.mm.jjjj" );
	
	cStr.Format( "%s %s %s %s  %s        %s       %5.5ld   %s",

				p->ARTICLE_CODE,
				p->EINHEIT,
				p->ARTIKEL_NAME,
				dat_str,
				p->NAHRUNGSTEST,
				p->NAHRUNGSERGAENZUNG,
				p->HERSTELLER_NR,
				p->NAME  );

}

CString CInkonsView::GetListHeader()
{
	return _T( "PZN        Einheit Artikelname                    " \
			   "Anlagedatum NahrTest NahrErg HerstNr Herstellername"; );
}

CString CInkonsView::GetListStrich()
{
	return _T( "-------------------------------------------------" \
		       "-----------------------------------------------------------" );
}

bool CInkonsView::IsPrintZeile()
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

void* CInkonsView::GetPrintZeile()
{
	return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CInkonsView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
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

bool CInkonsView::GetInfoFromCallingView( CString& cStr, int nAction )
{

	int DruckBreite = 114;
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
			cText =  "Inkonsistente Nem-Artikel";
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

void CInkonsView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}


void CInkonsView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CInkonsView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern

void CInkonsView::OnFileSpeichern() 
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

void CInkonsView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}

