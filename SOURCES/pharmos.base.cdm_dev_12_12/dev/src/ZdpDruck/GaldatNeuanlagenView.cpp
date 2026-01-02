// GaldatNeuanlagenView.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "ZdpDruck.h"
#include "GaldatNeuanlagenView.h"

#include <eklibs/hamfcs/hMskDate.h>
#include "ViewNumbers.h"

#include "ServerDatum.h"
#include <hdatum/Phodate.h>

#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/sqltabs/tabsqld.h>
#include <eklibs/wunxlocs/hUnixStdout.h>

#include <voodoo_table_header/clioart.h>
#include <voodoo_table_header/clicompany.h>
#include "FeldBreite.h"

// CGaldatNeuanlagenView

IMPLEMENT_DYNCREATE(CGaldatNeuanlagenView, CFormView)

CGaldatNeuanlagenView::CGaldatNeuanlagenView()
	: ChPflegeView(CGaldatNeuanlagenView::IDD)
{
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
}

CGaldatNeuanlagenView::~CGaldatNeuanlagenView()
{
}

void CGaldatNeuanlagenView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATVON, m_DATUMVON);
	DDX_Control(pDX, IDC_DATBIS, m_DATUMBIS);

}

BEGIN_MESSAGE_MAP(CGaldatNeuanlagenView, CFormView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
END_MESSAGE_MAP()


// CGaldatNeuanlagenView-Diagnose

#ifdef _DEBUG
void CGaldatNeuanlagenView::AssertValid() const
{
	CFormView::AssertValid();
}

void CGaldatNeuanlagenView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CGaldatNeuanlagenView-Meldungshandler
/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CAmbliefView 
void CGaldatNeuanlagenView::InitPflege()
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

void CGaldatNeuanlagenView::InitVariables()
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

bool CGaldatNeuanlagenView::ValidateSuchb()
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


void CGaldatNeuanlagenView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "ArtikelNr",		  7 },	
		{ "Neuanlage",		 10 },
		{ "Bezeichnung",     50 },
		{ "Swiss-Medic-Cat",  1 },
		{ "Hersteller",		 20 },
		{ NULL,				 -1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );

}


struct BUFF_LOGINDEX
{
	long ARTICLENO;
	long DATE_CREATED;
	char COMP_NAME[L_CLIOART_DSCRLONGD + 1];
	char SWISSMEDIC_CAT[L_CLIOART_SMCAT + 1];
	char HERSTELLER_NAME[L_CLICOMPANY_NAMS + 1];
};


void CGaldatNeuanlagenView::FillGrid( void *pp, int index )
{
	struct BUFF_LOGINDEX *p;
	ROWCOL Row;
	char dat_str[12];
	CString cStr;

	Row = index;

	p = (struct BUFF_LOGINDEX *) pp;

	cStr.Format( "%7.7ld", p->ARTICLENO );
	m_wndGrid.SetValueRange(CGXRange ( Row, 1 ), cStr );

	ConvFromPhoDate( dat_str, p->DATE_CREATED, "tt.mm.jjjj" );
	m_wndGrid.SetValueRange(CGXRange ( Row, 2 ), dat_str );
	m_wndGrid.SetValueRange(CGXRange ( Row, 3 ), p->COMP_NAME  );
	m_wndGrid.SetValueRange(CGXRange ( Row, 4 ), p->SWISSMEDIC_CAT  );
	m_wndGrid.SetValueRange(CGXRange ( Row, 5 ), p->HERSTELLER_NAME  );
}

void CGaldatNeuanlagenView::FillBox( int anz )
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

void CGaldatNeuanlagenView::GetDelimiter( char *info, char *delim )
{
	int lng;
	lng = static_cast<int>(strlen( info )) - 1;
    while ( info[lng] == ' ' ) lng--;
    *delim = info[lng++];
    info[lng] = '\0';
}

CString CGaldatNeuanlagenView::GetSelect( )
{
	CString sql;
	long zeit;


	if ( 0 == m_nDatumBis)
		 m_nDatumBis = ::ActualDateTime( &zeit );

	/* sql.Format("select a.articleno,date_created, comp_name, swissmedic_cat, name_short " \
		       " from cgal30o01 a , cgal30o03 b, cgal30o19 c, outer cgal30o12 d where a.articleno = b.articleno and b.lang_code = 'D' " \
			   "  and a.articleno = c.articleno and  c.role = 'H' and c.comp_no = d.comp_no and date_created >= %ld and date_created <= %ld" \
			   " and not a.articleno  in ( select artikel_nr from zartikel) order by name_short ",m_nDatumVon,m_nDatumBis);
	*/

	// Änderung auf LogIndex: Stand 24.06.2014 kein Datum von / bis zum Einschränken + kein Herstellername vorhanden: */

	sql.Format("select phar, datum_anlage, dscrlongd, smcat, nams "
			"from clioart, clicompany where compno = prtno and "
			"datum_anlage >= %ld and datum_anlage <= %ld and "
			"phar not  in ( select artikel_nr from zartikel) order by nams ", m_nDatumVon,m_nDatumBis);

	return sql;
}

void CGaldatNeuanlagenView::EnableOrder( BOOL mode )
{
}


int CGaldatNeuanlagenView::BearbeiteSatz()
{
	return -1;
}

int CGaldatNeuanlagenView::SucheSatz( )
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

int CGaldatNeuanlagenView::NextSatz( )
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

int CGaldatNeuanlagenView::PrevSatz()
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


int  CGaldatNeuanlagenView::UndoSatz()
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

void CGaldatNeuanlagenView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CGaldatNeuanlagenView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

void CGaldatNeuanlagenView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CGaldatNeuanlagenView::ResizeControls( int cx, int cy ) 
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
	char DATE_CREATED[10];
	char fil2[1];
	char COMP_NAME[L_CLIOART_DSCRLONGD];
	char fil3[1];
	char SWISSMEDIC_CAT[L_CLIOART_SMCAT];
	char fil4[1];
	char HERSTELLER_NAME[L_CLICOMPANY_NAMS];
	char eof[1];
};

void CGaldatNeuanlagenView::FillZeile( void *pp , CString& cStr )
{
	struct BUFF_LOGINDEX *p;
	struct DRUCK_ZEILE d;	
	char dat_str[12];

	p = (struct BUFF_LOGINDEX *) pp;

	sprintf( d.ARTICLENO, "%7.7ld", p->ARTICLENO );
	memset( d.fil1, ' ', 2 );
	ConvFromPhoDate( dat_str, p->DATE_CREATED, "tt.mm.jjjj" );
	memcpy( d.DATE_CREATED , dat_str, 10 );
	memset( d.fil2, ' ', 1 );
	memcpy( d.COMP_NAME, p->COMP_NAME, L_CLIOART_DSCRLONGD );
	memset( d.fil3, ' ', 1 );
	memcpy( d.SWISSMEDIC_CAT, p->SWISSMEDIC_CAT, L_CLIOART_SMCAT );
	memset( d.fil4, ' ', 1 );
	memcpy( d.HERSTELLER_NAME, p->HERSTELLER_NAME, L_CLICOMPANY_NAMS );
	memset( d.eof, '\0', 1 );
	cStr = ( char *) &d;


}

CString CGaldatNeuanlagenView::GetListHeader()
{
	return _T( "ArtikelNr Neuanlage Bezeichnung                                        " \
		       "IKS_CAT Hersteller" );
}

CString CGaldatNeuanlagenView::GetListStrich()
{
	return _T( "---------------------------------------------------------------------" \
		       "---------------------------" );
}

bool CGaldatNeuanlagenView::IsPrintZeile()
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

void* CGaldatNeuanlagenView::GetPrintZeile()
{
		return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CGaldatNeuanlagenView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
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

bool CGaldatNeuanlagenView::GetInfoFromCallingView( CString& cStr, int nAction )
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
			cText.Format( "Galdat Neuanlagen ohne Zartikelsatz %s - %s",cDatVon, cDatBis);
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

void CGaldatNeuanlagenView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}


void CGaldatNeuanlagenView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CGaldatNeuanlagenView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern

void CGaldatNeuanlagenView::OnFileSpeichern() 
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

void CGaldatNeuanlagenView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}

///////////////////////////////////////////////////////////////////
//  Ueber UnixStdOut


void CGaldatNeuanlagenView::FillString( char *str, CString cStr, int lng )
{
	int lng1;
	lng1 = cStr.GetLength();
	if ( lng1 > lng )
		lng1 = lng;

	memset( str, ' ',  lng  );
	memcpy( str, cStr, lng1 );
	str[lng] = '\0';
}


void* CGaldatNeuanlagenView::BufFromGrid( int Row )
{
	static struct BUFF_LOGINDEX p;

	Row++;
	p.ARTICLENO = atol( m_wndGrid.GetValueRowCol( Row, 1 ) );
	p.DATE_CREATED = atol( m_wndGrid.GetValueRowCol( Row, 2 ) );
	FillString( p.COMP_NAME, m_wndGrid.GetValueRowCol( Row, 3 ), L_CLIOART_DSCRLONGD);
	FillString( p.SWISSMEDIC_CAT, m_wndGrid.GetValueRowCol( Row, 4 ), L_CLIOART_SMCAT );
	FillString( p.HERSTELLER_NAME, m_wndGrid.GetValueRowCol( Row, 5 ), L_CLICOMPANY_NAMS);
	return &p;
}

void CGaldatNeuanlagenView::BufFromZeile( struct BUFF_LOGINDEX *p, CString Zeile )
{
	struct DRUCK_ZEILE d;

	strcpy( (char *) &d, Zeile );

	*d.fil1 = '\0';
	*d.fil2 = '\0';
	*d.fil3 = '\0';
	*d.fil4 = '\0';
	*d.eof  = '\0',

	p->ARTICLENO = atol( d.ARTICLENO );
	p->DATE_CREATED = atol( d.DATE_CREATED );
	strcpy( p->COMP_NAME, d.COMP_NAME );
	strcpy( p->SWISSMEDIC_CAT, d.SWISSMEDIC_CAT );
	strcpy( p->HERSTELLER_NAME, d.HERSTELLER_NAME );
}


