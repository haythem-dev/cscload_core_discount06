// ElektroNeuanlagenView.cpp : Implementierungsdatei
//
#include "stdafx.h"
#include "ZdpDruck.h"
#include "ElektroNeuanlagenView.h"

#include <eklibs/hamfcs/hMskDate.h>
#include "ViewNumbers.h"

#include "ServerDatum.h"
#include <hdatum/Phodate.h>

#include <libscsvoodoo/libscsvoodoo.h>

//#include <konvbuf.h>
#include <eklibs/sqltabs/tabsqld.h>
#include <eklibs/wunxlocs/hUnixStdout.h>

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/herstel.h>
#include <voodoo_table_header/carticlecodes.h>

#include "FeldBreite.h"

// CElektroNeuanlagenView

IMPLEMENT_DYNCREATE(CElektroNeuanlagenView, CFormView)

CElektroNeuanlagenView::CElektroNeuanlagenView()
	: ChPflegeView(CElektroNeuanlagenView::IDD)
{
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
}

CElektroNeuanlagenView::~CElektroNeuanlagenView()
{
}

void CElektroNeuanlagenView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATBIS, m_DATUMBIS);
	DDX_Control(pDX, IDC_DATVON, m_DATUMVON);
}

BEGIN_MESSAGE_MAP(CElektroNeuanlagenView, CFormView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
END_MESSAGE_MAP()


// CElektroNeuanlagenView-Diagnose

#ifdef _DEBUG
void CElektroNeuanlagenView::AssertValid() const
{
	CFormView::AssertValid();
}

void CElektroNeuanlagenView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CElektroNeuanlagenView-Meldungshandler
void CElektroNeuanlagenView::InitPflege()
{
	m_wndGrid.SubclassDlgItem(IDC_ELEKTRO_GRID, this );
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

void CElektroNeuanlagenView::InitVariables()
{
	m_nDatumVon = 0;
	m_nDatumBis = 0;
	m_DATUMVON.p_SetInput();
	m_DATUMBIS.p_SetInput();
	m_nNumberOfRows = 0;
	m_wndGrid.hInitGrid( GRID_ROWS, -1);
//	m_wndGrid.hInitGrid();

	m_DATUMVON.SetFocus();
}

bool CElektroNeuanlagenView::ValidateSuchb()
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

	if ( m_nDatumBis > AddDayToPhoDate( m_nDatumVon, 31 ) )
	{
		AfxMessageBox( "Zeitraum maximal 31 Tage" );
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////
//  Sql

void CElektroNeuanlagenView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "ArtNr", MAX_LENGTH_ARTICLE_NO},	
		{ "Einheit",		 9 },
		{ "Artikelname",	30 },
		{ "Änder-Datum",	10 },
		{ "EAR",			 1 },
		{ "HestNr",		     5 },
		{ "Herstellername",	30 },
		{ "",				 0 },
		{ NULL,				-1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );

}


struct BUFF_EARART
{
	char ARTICLE_CODE[MAX_LENGTH_ARTICLE_NO + 1];
	char EINHEIT[L_ZARTIKEL_EINHEIT + 1];
	char ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME + 1];
	long DATUM_AENDER;
	char EAR[L_ZARTIKEL_ELEKTROSCHROTT + 1];
	long HERSTELLER_NR;
	char NAME[L_HERSTEL_NAME + 1 ];
	long ARTIKEL_NR;
};



void CElektroNeuanlagenView::FillGrid( void *pp, int index )
{
	struct BUFF_EARART *p;
	ROWCOL Row;

	CString cStr;
	CString temp;
	char dat_str[12];

	Row = index;

	p = (struct BUFF_EARART *) pp;

	ConvFromPhoDate( dat_str, p->DATUM_AENDER, "tt.mm.jjjj" );

	temp.Format( "%c%ds", '%', MAX_LENGTH_ARTICLE_NO );
	cStr.Format( temp, p->ARTICLE_CODE );
	m_wndGrid.SetValueRange(CGXRange ( Row, 1 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 2 ), p->EINHEIT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 3 ), p->ARTIKEL_NAME );
	m_wndGrid.SetValueRange(CGXRange ( Row, 4 ), dat_str );
	m_wndGrid.SetValueRange(CGXRange ( Row, 5 ), p->EAR );
	cStr.Format( "%5.5ld", p->HERSTELLER_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 6 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 7 ), p->NAME );
	cStr.Format( "%ld", p->ARTIKEL_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 8 ), cStr );
}

void CElektroNeuanlagenView::FillBox( int anz )
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

void CElektroNeuanlagenView::GetDelimiter( char *info, char *delim )
{
	int lng;
	lng = static_cast<int>(strlen( info )) - 1;
    while ( info[lng] == ' ' ) lng--;
    *delim = info[lng++];
    info[lng] = '\0';
}



CString CElektroNeuanlagenView::GetSelect( )
{
	CString sql;
	long zeit;

	if ( 0 == m_nDatumBis)
		 m_nDatumBis = ::ActualDateTime( &zeit );

	sql.Format( "select lpad(trim(ARTICLE_CODE), %d, 0),einheit,artikel_name,a.datum_anlage,a.elektroschrott,a.hersteller_nr,name,a.artikel_nr from " \
		        "zartikel a,outer herstel h, carticlecodes where articleno = a.artikel_nr and PREFERRED_FLAG = 1 and CODE_TYPE IN " \
				"(select CODE_TYPE from CCODETYPES where ARTNR_SUBSTITUTE = 1) and " \
				"a.datum_anlage>=%ld and a.datum_anlage<=%ld and a.elektroschrott = 'J' and " \
				"h.hersteller_nr=a.hersteller_nr " \
				"order by a.artikel_name",
				MAX_LENGTH_ARTICLE_NO,
				m_nDatumVon,
				m_nDatumBis );
	
	return sql;
}


void CElektroNeuanlagenView::EnableOrder( BOOL mode )
{
//	m_rdNr.EnableWindow( mode );
//	m_rdName.EnableWindow( mode );
}


int  CElektroNeuanlagenView::BearbeiteSatz()
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

int CElektroNeuanlagenView::SucheSatz( )
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

int CElektroNeuanlagenView::NextSatz( )
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

int CElektroNeuanlagenView::PrevSatz()
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


int  CElektroNeuanlagenView::UndoSatz()
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
// Behandlungsroutinen für Nachrichten CNemwartView 

void CElektroNeuanlagenView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CElektroNeuanlagenView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

void CElektroNeuanlagenView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CElektroNeuanlagenView::ResizeControls( int cx, int cy ) 
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

struct DRUCK_ZEILE
{
	char ARTICLE_CODE[MAX_LENGTH_ARTICLE_NO];
	char fil1[1];
	char EINHEIT[L_ZARTIKEL_EINHEIT];
	char fil2[1];
	char ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME];
	char fil3[1];
	char DATUM_AENDER[10];
	char fil4[2];
	char EAR[L_ZARTIKEL_ELEKTROSCHROTT];
	char fil5[7];
	char HERSTELLER_NR[5];
	char fil6[3];
	char NAME[L_HERSTEL_NAME];
	char eof[1];
};

void CElektroNeuanlagenView::FillZeile( void *pp , CString& cStr )
{
	struct BUFF_EARART *p;
	struct DRUCK_ZEILE d;

	p = (struct BUFF_EARART *) pp;

	memcpy( d.ARTICLE_CODE, p->ARTICLE_CODE, MAX_LENGTH_ARTICLE_NO );
	memset( d.fil1, ' ', 1 );
	memcpy( d.EINHEIT, p->EINHEIT, L_ZARTIKEL_EINHEIT );
	memset( d.fil2, ' ', 1 );
	memcpy( d.ARTIKEL_NAME, p->ARTIKEL_NAME, L_ZARTIKEL_ARTIKEL_NAME );
	memset( d.fil3, ' ', 1 );
	ConvFromPhoDate( d.DATUM_AENDER, p->DATUM_AENDER, "tt.mm.jjjj" );
	memset( d.fil4, ' ', 2 );
	memcpy( d.EAR, p->EAR, L_ZARTIKEL_ELEKTROSCHROTT );
	memset( d.fil5, ' ', 7 );
	sprintf( d.HERSTELLER_NR, "%5.5ld", p->HERSTELLER_NR );
	memset( d.fil6, ' ', 3 );
	memcpy( d.NAME, p->NAME, L_HERSTEL_NAME );
	memset( d.eof, '\0', 1 );
	cStr = ( char *) &d;

/*
	char dat_str[12];

	ConvFromPhoDate( dat_str, p->DATUM_AENDER, "tt.mm.jjjj" );
	
	cStr.Format( "%7.7ld %s %s %s  %s       %s       %5.5ld   %s",
				p->ARTIKEL_NR,
				p->EINHEIT,
				p->ARTIKEL_NAME,
				dat_str,
				p->NEM_NEU,
				GetNemAlt( p->ARTIKEL_NR ),
				p->HERSTELLER_NR,
				p->NAME  );
*/

}

CString CElektroNeuanlagenView::GetListHeader()
{
	return _T( "PZN        Einheit Artikelname                    " \
			   "Änder-Datum EAR HerstNr Herstellername"; );
}

CString CElektroNeuanlagenView::GetListStrich()
{
	return _T( "-------------------------------------------------" \
		       "---------------------------------------------------------" );
}

bool CElektroNeuanlagenView::IsPrintZeile()
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

void* CElektroNeuanlagenView::GetPrintZeile()
{
		return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CElektroNeuanlagenView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
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

bool CElektroNeuanlagenView::GetInfoFromCallingView( CString& cStr, int nAction )
{

	int DruckBreite = 110;
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
			cText.Format( "Elektro Artikel Neuanlagen vom %s - %s", cDatVon, cDatBis );
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

void CElektroNeuanlagenView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}


void CElektroNeuanlagenView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CElektroNeuanlagenView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern

void CElektroNeuanlagenView::OnFileSpeichern() 
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

void CElektroNeuanlagenView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}





void CElektroNeuanlagenView::FillString( char *str, CString cStr, int lng )
{
	int lng1;
	lng1 = cStr.GetLength();
	if ( lng1 > lng )
		lng1 = lng;

	memset( str, ' ',  lng  );
	memcpy( str, cStr, lng1 );
	str[lng] = '\0';
}

void* CElektroNeuanlagenView::BufFromGrid( int Row )
{
	static struct BUFF_EARART p;
	char dat_str[20];
	Row++;
	FillString( p.ARTICLE_CODE, m_wndGrid.GetValueRowCol( Row, 1 ), MAX_LENGTH_ARTICLE_NO );
	FillString( p.EINHEIT, m_wndGrid.GetValueRowCol( Row, 2 ), L_ZARTIKEL_EINHEIT );
	FillString( p.ARTIKEL_NAME, m_wndGrid.GetValueRowCol( Row, 3 ), L_ZARTIKEL_ARTIKEL_NAME );
	strcpy( dat_str, m_wndGrid.GetValueRowCol( Row, 4 ) );
	ConvToPhoDate( dat_str, &p.DATUM_AENDER, "tt.mm.jjjj" );
	FillString( p.EAR, m_wndGrid.GetValueRowCol( Row, 5 ), L_ZARTIKEL_ELEKTROSCHROTT );
	p.HERSTELLER_NR = atol( m_wndGrid.GetValueRowCol( Row, 7 ) );
	FillString( p.NAME, m_wndGrid.GetValueRowCol( Row, 8 ), L_HERSTEL_NAME );
	m_cNr.SetAt  ( 0, p.ARTIKEL_NR );
	return &p;
}

void CElektroNeuanlagenView::BufFromZeile( struct BUFF_EARART *p, CString Zeile )
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

	strcpy( p->ARTICLE_CODE, d.ARTICLE_CODE );
	strcpy( p->EINHEIT, d.EINHEIT );
	strcpy( p->ARTIKEL_NAME, d.ARTIKEL_NAME );
	ConvToPhoDate( d.DATUM_AENDER, &p->DATUM_AENDER, "tt.mm.jjjj" );
	strcpy( p->EAR, d.EAR );
	p->HERSTELLER_NR = atol( d.HERSTELLER_NR );
	strcpy( p->NAME, d.NAME );
	m_cNr.SetAt  ( 0, p->ARTIKEL_NR );
}

