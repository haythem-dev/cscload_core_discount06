// ElektroNeuanlagenView.cpp : Implementierungsdatei
//
#include "stdafx.h"
#include "ZdpDruck.h"
#include "HerstellerNachHerstellerCodeView.h"

#include <eklibs/hamfcs/hMskDate.h>
#include <eklibs/hamfcs/hMskChar.h>
#include "ViewNumbers.h"

#include "ServerDatum.h"
#include <hdatum/Phodate.h>

#include <libscsvoodoo/libscsvoodoo.h>

//#include <konvbuf.h>
#include <eklibs/sqltabs/tabsqld.h>
#include <eklibs/wunxlocs/hUnixStdout.h>

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/herstel.h>

#include "FeldBreite.h"

// CElektroNeuanlagenView

IMPLEMENT_DYNCREATE(CHerstellerNachHerstellerCodeView, CFormView)

CHerstellerNachHerstellerCodeView::CHerstellerNachHerstellerCodeView()
	: ChPflegeView(CHerstellerNachHerstellerCodeView::IDD)
{
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
}

CHerstellerNachHerstellerCodeView::~CHerstellerNachHerstellerCodeView()
{
}

void CHerstellerNachHerstellerCodeView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HERSTELLERCODE, m_HERSTELLERCODE);

}

BEGIN_MESSAGE_MAP(CHerstellerNachHerstellerCodeView, CFormView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
END_MESSAGE_MAP()


// CElektroNeuanlagenView-Diagnose

#ifdef _DEBUG
void CHerstellerNachHerstellerCodeView::AssertValid() const
{
	CFormView::AssertValid();
}

void CHerstellerNachHerstellerCodeView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CElektroNeuanlagenView-Meldungshandler
void CHerstellerNachHerstellerCodeView::InitPflege()
{
	m_wndGrid.SubclassDlgItem(IDC_HERSTELLER_GRID, this );
	m_wndGrid.Initialize();	
	m_wndGrid.hZeroGrid();
	m_nNumberOfRows = 0;
	FirstInitGrid( );

	m_HERSTELLERCODE.SetMask(ED_CHAR,  ED_UPPER, m_HerstellerCode, 3,new ChMaskChar);
	m_HERSTELLERCODE.SetDialog( TRUE );
}

void CHerstellerNachHerstellerCodeView::InitVariables()
{
	m_HERSTELLERCODE.p_SetInput();
	m_nNumberOfRows = 0;
	m_wndGrid.hInitGrid( GRID_ROWS, -1);
//	m_wndGrid.hInitGrid();

	m_HERSTELLERCODE.SetFocus();
}

bool CHerstellerNachHerstellerCodeView::ValidateSuchb()
{
	m_HERSTELLERCODE.p_GetInput();

	return true;
}

////////////////////////////////////////////////////////////
//  Sql

void CHerstellerNachHerstellerCodeView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "Nr",			  7 },	
		{ "Name",		 22 },
		{ "PLZ",		  7 },
		{ "Ort",		 40 },
		{ "Code", 		  5 },
		{ NULL,				-1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );

}


struct BUFF_HERSTELLER
{
	long HERSTELLER_NR;
	char NAME[L_HERSTEL_NAME + 1];
	char PLZ[L_HERSTEL_PLZ + 1];
	char ORT[L_HERSTEL_ORT + 1];
	char HERSTELLER_CODE[L_HERSTEL_HERSTELLER_CODE + 1 ];
};



void CHerstellerNachHerstellerCodeView::FillGrid( void *pp, int index )
{
	struct BUFF_HERSTELLER *p;

	ROWCOL Row;
	CString cStr;
	Row = index;

	p = (struct BUFF_HERSTELLER *) pp;

	cStr.Format( "%7.7ld", p->HERSTELLER_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 1 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 2 ), p->NAME );
	m_wndGrid.SetValueRange(CGXRange ( Row, 3 ), p->PLZ );
	m_wndGrid.SetValueRange(CGXRange ( Row, 4 ), p->ORT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 5 ), p->HERSTELLER_CODE );
}

void CHerstellerNachHerstellerCodeView::FillBox( int anz )
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

void CHerstellerNachHerstellerCodeView::GetDelimiter( char *info, char *delim )
{
	int lng;
	lng = static_cast<int>(strlen( info )) - 1;
    while ( info[lng] == ' ' ) lng--;
    *delim = info[lng++];
    info[lng] = '\0';
}



CString CHerstellerNachHerstellerCodeView::GetSelect( )
{
	CString csSql,csLike;
    csLike = m_HerstellerCode;
	csLike.Trim();
	csLike += '*';

	csSql.Format( "select hersteller_nr,name,plz,ort,hersteller_code from " \
		        "herstel h where " \
				"hersteller_code matches '%s' " \
				"order by hersteller_code,hersteller_nr" ,	csLike );
	return csSql;
}


void CHerstellerNachHerstellerCodeView::EnableOrder( BOOL mode )
{
//	m_rdNr.EnableWindow( mode );
//	m_rdName.EnableWindow( mode );
}


int  CHerstellerNachHerstellerCodeView::BearbeiteSatz()
{
	return -1;

}

int CHerstellerNachHerstellerCodeView::SucheSatz( )
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

int CHerstellerNachHerstellerCodeView::NextSatz( )
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

int CHerstellerNachHerstellerCodeView::PrevSatz()
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


int  CHerstellerNachHerstellerCodeView::UndoSatz()
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

void CHerstellerNachHerstellerCodeView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CHerstellerNachHerstellerCodeView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

void CHerstellerNachHerstellerCodeView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CHerstellerNachHerstellerCodeView::ResizeControls( int cx, int cy ) 
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
	char HERSTELLER_NR[7];
	char fil1[1];
	char NAME[L_HERSTEL_NAME];
	char fil2[1];
	char PLZ[L_HERSTEL_PLZ];
	char fil3[1];
	char ORT[L_HERSTEL_ORT];
	char fil4[1];
	char HERSTELLER_CODE[L_HERSTEL_HERSTELLER_CODE];
	char eof[1];
};

void CHerstellerNachHerstellerCodeView::FillZeile( void *pp , CString& cStr )
{
	struct BUFF_HERSTELLER *p;
	struct DRUCK_ZEILE d;

	p = (struct BUFF_HERSTELLER *) pp;

	sprintf( d.HERSTELLER_NR, "%7.7ld", p->HERSTELLER_NR );
	memset( d.fil1, ' ', 1 );
	memcpy( d.NAME, p->NAME, L_HERSTEL_NAME );
	memset( d.fil2, ' ', 1 );
	memcpy( d.PLZ, p->PLZ, L_HERSTEL_PLZ );
	memset( d.fil3, ' ', 1 );
	memcpy( d.ORT, p->ORT, L_HERSTEL_ORT );
	memset( d.fil4, ' ', 1 );
	memcpy( d.HERSTELLER_CODE, p->HERSTELLER_CODE, L_HERSTEL_HERSTELLER_CODE );
	memset( d.eof, '\0', 1 );
	cStr = ( char *) &d;

}

CString CHerstellerNachHerstellerCodeView::GetListHeader()
{
	return _T( "HNR     Bezeichnung            PLZ     Ort                                      Code " );
//	            1234567 1234567890123456789012 1234567 1234567890123456789012345678901234567890 12345
}

CString CHerstellerNachHerstellerCodeView::GetListStrich()
{
	return _T( "-------------------------------------------------" \
		       "---------------------------------------------------------" );
}

bool CHerstellerNachHerstellerCodeView::IsPrintZeile()
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

void* CHerstellerNachHerstellerCodeView::GetPrintZeile()
{
		return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CHerstellerNachHerstellerCodeView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
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

bool CHerstellerNachHerstellerCodeView::GetInfoFromCallingView( CString& cStr, int nAction )
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
			CString cText;
			cText.Format( "Hersteller nach Hersteller-Code  %s", m_HerstellerCode );
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

void CHerstellerNachHerstellerCodeView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}


void CHerstellerNachHerstellerCodeView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CHerstellerNachHerstellerCodeView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern

void CHerstellerNachHerstellerCodeView::OnFileSpeichern() 
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

void CHerstellerNachHerstellerCodeView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}





void CHerstellerNachHerstellerCodeView::FillString( char *str, CString cStr, int lng )
{
	int lng1;
	lng1 = cStr.GetLength();
	if ( lng1 > lng )
		lng1 = lng;

	memset( str, ' ',  lng  );
	memcpy( str, cStr, lng1 );
	str[lng] = '\0';
}

void* CHerstellerNachHerstellerCodeView::BufFromGrid( int Row )
{
	static struct BUFF_HERSTELLER p;
	Row++;
	p.HERSTELLER_NR = atol( m_wndGrid.GetValueRowCol( Row, 1 ) );
	FillString( p.NAME, m_wndGrid.GetValueRowCol( Row, 2 ), L_HERSTEL_NAME );
	FillString( p.PLZ, m_wndGrid.GetValueRowCol( Row, 3 ), L_HERSTEL_PLZ );
	FillString( p.ORT, m_wndGrid.GetValueRowCol( Row, 4 ), L_HERSTEL_ORT );
	FillString( p.HERSTELLER_CODE, m_wndGrid.GetValueRowCol( Row, 5 ), L_HERSTEL_HERSTELLER_CODE );

	return &p;
}

void CHerstellerNachHerstellerCodeView::BufFromZeile( struct BUFF_HERSTELLER *p, CString Zeile )
{
	struct DRUCK_ZEILE d;

	strcpy( (char *) &d, Zeile );

	*d.fil1 = '\0';
	*d.fil2 = '\0';
	*d.fil3 = '\0';
	*d.fil4 = '\0';
	*d.eof  = '\0',

	p->HERSTELLER_NR = atol( d.HERSTELLER_NR );
	strcpy( p->NAME, d.NAME );
	strcpy( p->PLZ, d.PLZ );
	strcpy( p->ORT, d.ORT );
	strcpy( p->HERSTELLER_CODE, d.HERSTELLER_CODE );

}

