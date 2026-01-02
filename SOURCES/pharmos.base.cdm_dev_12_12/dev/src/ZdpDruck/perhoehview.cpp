// PerhoehView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "zdpdruck.h"
#include "PerhoehView.h"

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
// CPerhoehView

IMPLEMENT_DYNCREATE(CPerhoehView, CFormView)

CPerhoehView::CPerhoehView()
	: ChPflegeView(CPerhoehView::IDD)
{
	//{{AFX_DATA_INIT(CPerhoehView)
		// HINWEIS: Der Klassen-Assistent fügt hier Elementinitialisierung ein
	//}}AFX_DATA_INIT
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
}

CPerhoehView::~CPerhoehView()
{
}

void CPerhoehView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPerhoehView)
	DDX_Control(pDX, IDC_PERHOEH_DATBIS, m_DATUMBIS);
	DDX_Control(pDX, IDC_PERHOEH_DATVON, m_DATUMVON);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPerhoehView, CFormView)
	//{{AFX_MSG_MAP(CPerhoehView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CPerhoehView

#ifdef _DEBUG
void CPerhoehView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPerhoehView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////
// Implementation

void CPerhoehView::InitPflege()
{
	m_wndGrid.SubclassDlgItem(IDC_PERHOEH_GRID, this );
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

void CPerhoehView::InitVariables()
{
	m_nDatumVon = PhoToday();
	m_nDatumBis = 0;
	m_DATUMVON.p_SetInput();
	m_DATUMBIS.p_SetInput();
	m_nNumberOfRows = 0;
	m_wndGrid.hInitGrid();

	m_DATUMVON.SetFocus();
}

bool CPerhoehView::ValidateSuchb()
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

	if ( m_nDatumVon != 0 && m_nDatumBis != 0 && m_nDatumVon > m_nDatumBis )
	{
		AfxMessageBox( "Datum Anlage  <= Datum gültig ab" );
		return false;
	}
	return true;
}

////////////////////////////////////////////////////////////
//  Sql

void CPerhoehView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "Herst#",			 5 },	
		{ "Herstellername",	30 },
		{ "ArtNr", MAX_LENGTH_ARTICLE_NO},	
		{ "Artikelname",	30 },
    { "Apothekenpflichtig", 1},
    { "Rezeptpflichtig", 1},
		{ "Grosso alt",     10 }, 
		{ "Grosso",         10 }, 		 
		{ "%Erhöhung",      10 }, 
		{ "Aep alt",        10 }, 
		{ "Aep",            10 }, 
		{ "Gültig ab",       9 },	
		{ "Anlage",          9 },
		{ NULL,				-1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );
	m_wndGrid.RightAlignCol( 5, 9 );

}


struct BUFF_PERHOEH
{
	long HERSTELLER_NR;
	char SORTIERNAME[L_HERSTEL_SORTIERNAME + 1 ];
	char ARTICLE_CODE[MAX_LENGTH_ARTICLE_NO + 1];
	char ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME + 1];
  char APOTHEKENPFL[L_ZARTIKEL_APOTHEKENPFL + 1];
  char REZEPTPFL[L_ZARTIKEL_REZEPTPFL + 1];
  double GROSSO_ALT;
	double GROSSO;
	double STEIGERUNG;
	double AEP_ALT;
	double AEP;
	long DATUM_ANLAGE;
	long DATUMGUELTIGAB;
};


void CPerhoehView::FillGrid( void *pp, int index )
{
	struct BUFF_PERHOEH *p;
	ROWCOL Row;

	CString cStr;
	CString temp;
	char dat_str[12];

	Row = index;

	p = (struct BUFF_PERHOEH *) pp;


	cStr.Format( "%5.5ld", p->HERSTELLER_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 1 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 2 ), p->SORTIERNAME );
	
	temp.Format( "%c%ds", '%', MAX_LENGTH_ARTICLE_NO );
	cStr.Format( temp, p->ARTICLE_CODE );
	m_wndGrid.SetValueRange(CGXRange ( Row, 3 ), cStr );

	m_wndGrid.SetValueRange(CGXRange ( Row, 4 ), p->ARTIKEL_NAME );
	m_wndGrid.SetValueRange(CGXRange ( Row, 5 ), p->APOTHEKENPFL );
	m_wndGrid.SetValueRange(CGXRange ( Row, 6 ), p->REZEPTPFL );

	cStr.Format( "%10.2f", p->GROSSO_ALT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 7 ), cStr );
	cStr.Format( "%10.2f", p->GROSSO );
	m_wndGrid.SetValueRange(CGXRange ( Row, 8 ), cStr );
	cStr.Format( "%10.2f", p->STEIGERUNG );
	m_wndGrid.SetValueRange(CGXRange ( Row, 9 ), cStr );
	cStr.Format( "%10.2f", p->AEP_ALT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 10 ), cStr );
	cStr.Format( "%10.2f", p->AEP );
	m_wndGrid.SetValueRange(CGXRange ( Row, 11 ), cStr );
	ConvFromPhoDate( dat_str, p->DATUMGUELTIGAB, "tt.mm.jjjj" );
	m_wndGrid.SetValueRange(CGXRange ( Row, 12 ), dat_str );
	ConvFromPhoDate( dat_str, p->DATUM_ANLAGE, "tt.mm.jjjj" );
	m_wndGrid.SetValueRange(CGXRange ( Row, 13 ), dat_str );
}

void CPerhoehView::FillBox( int anz )
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




CString CPerhoehView::GetSelect( )
{
	CString sql;
	CString sql1;

	sql1.Format(  "select p.hersteller_nr,sortiername,lpad(trim(ARTICLE_CODE), %d, 0),artikel_name,z.apothekenpfl,z.rezeptpfl," \
			"grosso_alt,grosso, round( (grosso/grosso_alt-1)*100, 2) Steigerung," \
			"aep_alt,aep,p.datum_anlage,p.datumgueltigab " \
			"from zpreiserhoehung p,outer herstel h,outer zartikel z, carticlecodes where articleno = p.artikel_nr and PREFERRED_FLAG = 1 and CODE_TYPE IN " \
			"(select CODE_TYPE from CCODETYPES where ARTNR_SUBSTITUTE = 1) " \
			"and grosso_alt>0 and z.artikel_nr=p.artikel_nr and " \
			"h.hersteller_nr=p.hersteller_nr", 
			MAX_LENGTH_ARTICLE_NO);

	if ( m_nDatumVon > 0 && m_nDatumBis > 0 )
		sql.Format( "%s " \
					"and p.datumgueltigab>%ld and p.datumgueltigab<=%ld",
					sql1,
					m_nDatumVon,
					m_nDatumBis
					);
	else if ( m_nDatumVon > 0 && m_nDatumBis == 0 )
		sql.Format( "%s " \
					"and p.datumgueltigab>%ld",
					sql1,
					m_nDatumVon
					);	
	else if ( m_nDatumVon == 0 && m_nDatumBis > 0 )
		sql.Format( "%s " \
					"and p.datumgueltigab<=%ld",
					sql1,
					m_nDatumBis
					);
	else
		sql = sql1;
				 
	sql += " order by p.hersteller_nr,3,p.datumgueltigab";

//	AfxMessageBox( sql );

	return sql;
}


void CPerhoehView::EnableOrder( BOOL mode )
{
//	m_rdNr.EnableWindow( mode );
//	m_rdName.EnableWindow( mode );
}


int  CPerhoehView::BearbeiteSatz()
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

int CPerhoehView::SucheSatz( )
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

int CPerhoehView::NextSatz( )
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

int CPerhoehView::PrevSatz()
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


int  CPerhoehView::UndoSatz()
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
// Behandlungsroutinen für Nachrichten CPerhoehView 

void CPerhoehView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CPerhoehView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

void CPerhoehView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CPerhoehView::ResizeControls( int cx, int cy ) 
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

void CPerhoehView::FillZeile( void *pp , CString& cStr )
{
	char dat_str1[12];
	char dat_str2[12];
	struct BUFF_PERHOEH *p;

	p = (struct BUFF_PERHOEH *) pp;

	ConvFromPhoDate( dat_str1, p->DATUM_ANLAGE, "tt.mm.jj" );
	ConvFromPhoDate( dat_str2, p->DATUMGUELTIGAB, "tt.mm.jj" );
	
	cStr.Format( "%5.5ld %s %s %s %s %s %10.2f %10.2f %10.2f %10.2f %10.2f %s %s",
				p->HERSTELLER_NR,
				p->SORTIERNAME,
				p->ARTICLE_CODE,
				p->ARTIKEL_NAME,
				p->APOTHEKENPFL,
				p->REZEPTPFL,
				p->GROSSO_ALT,
				p->GROSSO,
				p->STEIGERUNG,
				p->AEP_ALT,
				p->AEP,
				dat_str2,
				dat_str1 );
}

CString CPerhoehView::GetListHeader()
{
	return _T( "Hers# Herstellername         PZN      Artikelname                    " \
			   "A R Grosso-alt     Grosso  %Erhöhung    Aep-alt        Aep Guelt.Ab Anlage  " );
}                                                                        

CString CPerhoehView::GetListStrich()
{
	return _T( "--------------------------------------------------------------------" \
		       "------------------------------------------------------------------------" );
}

bool CPerhoehView::IsPrintZeile()
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

void* CPerhoehView::GetPrintZeile()
{
	return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CPerhoehView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
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

bool CPerhoehView::GetInfoFromCallingView( CString& cStr, int nAction )
{

	int DruckBreite = 100;

	DruckBreite = GetListHeader().GetLength() + 4;

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
			cText.Format( "Preiserhoehung von %s - %s", cDatVon, cDatBis );
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

void CPerhoehView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}


void CPerhoehView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CPerhoehView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern

void CPerhoehView::OnFileSpeichern() 
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

void CPerhoehView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}


