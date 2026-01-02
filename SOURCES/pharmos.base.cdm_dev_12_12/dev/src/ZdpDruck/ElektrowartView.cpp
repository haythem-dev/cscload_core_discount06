// ElektrowartView.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "ZdpDruck.h"
#include "ElektrowartView.h"


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
// CElektrowartView

IMPLEMENT_DYNCREATE(CElektrowartView, CFormView)

CElektrowartView::CElektrowartView()
	: ChPflegeView(CElektrowartView::IDD)
{
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
}

CElektrowartView::~CElektrowartView()
{
}

void CElektrowartView::DoDataExchange(CDataExchange* pDX)
{
	ChPflegeView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATBIS, m_DATUMBIS);
	DDX_Control(pDX, IDC_DATVON, m_DATUMVON);
}

BEGIN_MESSAGE_MAP(CElektrowartView, CFormView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
END_MESSAGE_MAP()


// CElektrowartView-Diagnose

#ifdef _DEBUG
void CElektrowartView::AssertValid() const
{
	CFormView::AssertValid();
}

void CElektrowartView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CElektrowartView-Meldungshandler
void CElektrowartView::InitPflege()
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

void CElektrowartView::InitVariables()
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

bool CElektrowartView::ValidateSuchb()
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

	if ( m_nDatumBis > AddDayToPhoDate( m_nDatumVon, 20 ) )
	{
		AfxMessageBox( "Zeitraum maximal 20 Tage" );
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////
//  Sql

void CElektrowartView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "ArtNr", MAX_LENGTH_ARTICLE_NO},	
		{ "Einheit",		 9 },
		{ "Artikelname",	30 },
		{ "Änder-Datum",	10 },
		{ "EAR-neu",		 1 },
		{ "EAR-alt",		 1 },
		{ "HestNr",		     5 },
		{ "Herstellername",	30 },
		{ "",				 0 },
		{ NULL,				-1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );

}


struct BUFF_ART
{
	char ARTICLE_CODE[MAX_LENGTH_ARTICLE_NO + 1];
	char EINHEIT[L_ZARTIKEL_EINHEIT + 1];
	char ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME + 1];
	char EAR_NEU[L_ZARTIKEL_ELEKTROSCHROTT + 1];
	long DATUM_AENDER;
	long HERSTELLER_NR;
	char NAME[L_HERSTEL_NAME + 1 ];
	long ARTIKEL_NR;
};

CString CElektrowartView::GetEARAlt( long artikel_nr )
{
	int i; 
	i = 0;
	while ( i < m_cNr.GetSize() && (long)m_cNr.GetAt(i) != artikel_nr ) i++;
	if ( i < m_cNr.GetSize() )
		return m_cEAR.GetAt( i );
	else
		return "";
}

void CElektrowartView::FillGrid( void *pp, int index )
{
	struct BUFF_ART *p;
	ROWCOL Row;

	CString cStr;
	CString temp;
	char dat_str[12];

	Row = index;

	p = (struct BUFF_ART *) pp;

	ConvFromPhoDate( dat_str, p->DATUM_AENDER, "tt.mm.jjjj" );

	temp.Format( "%c%ds", '%', MAX_LENGTH_ARTICLE_NO );
	cStr.Format( temp, p->ARTICLE_CODE );
	m_wndGrid.SetValueRange(CGXRange ( Row, 1 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 2 ), p->EINHEIT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 3 ), p->ARTIKEL_NAME );
	m_wndGrid.SetValueRange(CGXRange ( Row, 4 ), dat_str );
	m_wndGrid.SetValueRange(CGXRange ( Row, 5 ), p->EAR_NEU );
	m_wndGrid.SetValueRange(CGXRange ( Row, 6 ), GetEARAlt( p->ARTIKEL_NR ) );
	cStr.Format( "%5.5ld", p->HERSTELLER_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 7 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 8 ), p->NAME );
	cStr.Format( "%ld", p->ARTIKEL_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 9 ), cStr );
}

void CElektrowartView::FillBox( int anz )
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

void CElektrowartView::GetDelimiter( char *info, char *delim )
{
	int lng;
	lng = static_cast<int>(strlen( info )) - 1;
    while ( info[lng] == ' ' ) lng--;
    *delim = info[lng++];
    info[lng] = '\0';
}

long CElektrowartView::Lese_Protinfo( CString& cErrmld, CStringArray& cNem, CDWordArray& cNr )
{
	int  fd; 
	long s;
	long protokol_nr;
	long akt_protokol_nr;
	char akt_image;
	char image[10];
	char teil[10];
	char info[200];
	char buf_before[2000];
	char buf_after[2000];
	char delim_before;
	char delim_after;
	int  diff_before;
	int  diff_after;
	int  i;
	char zart_before[2000];
	char zart_after[2000];
	char ear_before;
	char ear_after;
	CString sql;
	char errmld[100];
	struct sqltab_struct *tab_desc;

	sql.Format( "select protokol_nr,image,teil,info from protinfo where " \
		        "protokol_nr in (select protokol_nr from protokol where " \
				"relation='zartikel' and datum>=%ld and datum <=%ld and aenderungsart='2') " \
				"order by protokol_nr,image,teil",
				m_nDatumVon, m_nDatumBis );


	s = SqlOpenCs( &fd, sql );
	if ( s != 0 )
	{
		cErrmld = DynErrmld();
		return s;
	}

	s = SqlFetch( fd, 1, &protokol_nr, image, teil, info, NULL ); 

	if ( s != 0 )
	{
		cErrmld = DynErrmld();
		SqlCloseCs( fd );
		if ( s == 100 )
			cErrmld = "Keine Artikeländerung im angegebenen Zeitraum";
		return s;
	}

    s = SqlGetTabDesc( "zartikel", ( void ** ) &tab_desc, DESC_COLNAMES, errmld );
	if ( s != 0 )
	{
		cErrmld = errmld;
		SqlCloseCs( fd );
		return s;
	}

	do
	{
		akt_protokol_nr = protokol_nr;
		akt_image = *image;
		*buf_before = '\0';
		do
		{
			strcat( buf_before, info );

			s = SqlFetch( fd, 1, &protokol_nr, image, teil, info, NULL );  

		}   while ( s == 0 && protokol_nr == akt_protokol_nr && *image == akt_image );

		if ( s == 0 && protokol_nr == akt_protokol_nr )
		{
			akt_image = *image;
			*buf_after = '\0';
			do
			{
				strcat( buf_after, info );

				s = SqlFetch( fd, 1, &protokol_nr, image, teil, info, NULL );  

			}   while ( s == 0 && protokol_nr == akt_protokol_nr && *image == akt_image );

			GetDelimiter( buf_before, &delim_before );
			GetDelimiter( buf_after , &delim_after  ); 
			diff_before = SqlLoadTabBuf( buf_before, delim_before, zart_before, tab_desc, errmld );
			diff_after  = SqlLoadTabBuf( buf_after,  delim_after,  zart_after,  tab_desc, errmld );
			if ( diff_before != diff_after )
			{
				cErrmld.Format( "diff: %d  %d", diff_before, diff_after );
				s = 4712;
				cErrmld = "SqlLoadBuf: Konsistenz-Error";
			}
			else
			{
				long artikel_nr;
				artikel_nr = (( struct ZARTIKEL *) zart_before )->ARTIKEL_NR;
				if ( artikel_nr == (( struct ZARTIKEL *) zart_after )->ARTIKEL_NR ) 
				{
					ear_before = *(( struct ZARTIKEL *) zart_before )->ELEKTROSCHROTT;
					ear_after  = *(( struct ZARTIKEL *) zart_after  )->ELEKTROSCHROTT;
					if ( ear_before != ear_after )
					{
						CString cInfo;
						cInfo.Format( "%c", ear_before );
						i = 0;
						while ( i < cNr.GetSize() && (long)cNr.GetAt(i) != artikel_nr ) i++;
						if ( i < cNr.GetSize() )
							cNem.SetAt( i, cInfo );
						else
						{
							cNem.Add( cInfo );
							cNr.Add( artikel_nr );
						}						
					}
				}
				else
				{
					s = 4713;
					cErrmld = "BufBefor, BufAfter: ungleiche Artikel-Nummern";
				}
			} 
		} 
		else
		{
			s = 4711;
			cErrmld = "Fehler in Protokolldatei";
		}
	} while ( s == 0 );

	if ( s == 100 )
		s =0;
	else if ( s < 0 )
		cErrmld = DynErrmld();

    SqlFreeTabDesc ( tab_desc );
	SqlCloseCs( fd );

	return s;
}

CString CElektrowartView::GetSelect_Client( )
{
	CString cErrmld;
	CString sql;
	CString cArt;
	long s;
	int  i;
	int anz;
	theApp->BeginWaitAction( );
	s = Lese_Protinfo( cErrmld, m_cEAR, m_cNr );
	theApp->EndWaitAction( );
	if ( s != 0 )
	{
		AfxMessageBox( cErrmld );
		sql.Empty();
		return sql;
	}
	anz = static_cast<int>(m_cNr.GetSize());
	if ( anz == 0 )
	{
		AfxMessageBox( "Kein Artikel mit EAR-Änderung im angegebenen Zeitraum" );
		sql.Empty();
		return sql;
	}
		
	sql.Format("select lpad(trim(ARTICLE_CODE), %d, 0),einheit,artikel_name,elektroschrott,z.datum_aender,"\
		  "z.hersteller_nr,name,z.artikel_nr " \
		  "from zartikel z, outer herstel h, carticlecodes where articleno = z.artikel_nr and PREFERRED_FLAG = 1 and CODE_TYPE IN " \
		  "(select CODE_TYPE from CCODETYPES where ARTNR_SUBSTITUTE = 1) and z.artikel_nr in (",
		  MAX_LENGTH_ARTICLE_NO);

	for ( i = 0; i < anz - 1; i++ )
	{
		cArt.Format( "%ld,", m_cNr.GetAt( i ) );
		sql += cArt;
	}
	cArt.Format( "%ld", m_cNr.GetAt( i ) );
	sql += cArt;
	sql += ") and h.hersteller_nr=z.hersteller_nr order by artikel_name";

//	AfxMessageBox( sql );

	return sql;
}


CString CElektrowartView::GetSelect( )
{
	m_cEAR.RemoveAll();
	m_cNr.RemoveAll();
	return GetSelect_Client();
}


void CElektrowartView::EnableOrder( BOOL mode )
{
//	m_rdNr.EnableWindow( mode );
//	m_rdName.EnableWindow( mode );
}


int  CElektrowartView::BearbeiteSatz()
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

int CElektrowartView::SucheSatz( )
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

/////////////////////////////////////
/*	if ( IsViaStdout() )
	{
		theApp->BeginWaitAction( );
		ReadViaStdout();
		theApp->EndWaitAction( );
		return -1;
	} */ 
/////////////////////////////////////

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

int CElektrowartView::NextSatz( )
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

int CElektrowartView::PrevSatz()
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


int  CElektrowartView::UndoSatz()
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

void CElektrowartView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CElektrowartView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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
				if ( !IsViaStdout() )
					FillBox( m_nNumberOfRows );	
				theApp->PopMenuState(  );
				theApp->SetMenuOnOff( 0, 0, 0, 0, 1, 1 ); 
			}
		}		
	}
}

void CElektrowartView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CElektrowartView::ResizeControls( int cx, int cy ) 
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
	char EAR_NEU[L_ZARTIKEL_ELEKTROSCHROTT];
	char fil5[7];
	char EAR_ALT[L_ZARTIKEL_ELEKTROSCHROTT];
	char fil6[7];
	char HERSTELLER_NR[5];
	char fil7[3];
	char NAME[L_HERSTEL_NAME];
	char eof[1];
};

void CElektrowartView::FillZeile( void *pp , CString& cStr )
{
	struct BUFF_ART *p;
	struct DRUCK_ZEILE d;

	p = (struct BUFF_ART *) pp;

	memcpy( d.ARTICLE_CODE, p->ARTICLE_CODE, MAX_LENGTH_ARTICLE_NO );
	memset( d.fil1, ' ', 1 );
	memcpy( d.EINHEIT, p->EINHEIT, L_ZARTIKEL_EINHEIT );
	memset( d.fil2, ' ', 1 );
	memcpy( d.ARTIKEL_NAME, p->ARTIKEL_NAME, L_ZARTIKEL_ARTIKEL_NAME );
	memset( d.fil3, ' ', 1 );
	ConvFromPhoDate( d.DATUM_AENDER, p->DATUM_AENDER, "tt.mm.jjjj" );
	memset( d.fil4, ' ', 2 );
	memcpy( d.EAR_NEU, p->EAR_NEU, L_ZARTIKEL_ELEKTROSCHROTT );
	memset( d.fil5, ' ', 7 );
	strcpy( d.EAR_ALT, GetEARAlt( p->ARTIKEL_NR ) );
	memset( d.fil6, ' ', 7 );
	sprintf( d.HERSTELLER_NR, "%5.5ld", p->HERSTELLER_NR );
	memset( d.fil7, ' ', 3 );
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

CString CElektrowartView::GetListHeader()
{
	return _T( "PZN        Einheit Artikelname                    " \
			   "Änder-Datum EAR-neu EAR-alt HerstNr Herstellername"; );
}

CString CElektrowartView::GetListStrich()
{
	return _T( "-------------------------------------------------" \
		       "---------------------------------------------------------" );
}

bool CElektrowartView::IsPrintZeile()
{
	if ( IsViaStdout() )
		return m_nSelectZeile < m_nNumberOfRows;
	else
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
}

void* CElektrowartView::GetPrintZeile()
{
	if ( IsViaStdout() )
	{
		if ( m_nSelectZeile < m_nNumberOfRows )
			return BufFromGrid( m_nSelectZeile++ );
		else
			return NULL;
	}
	else
		return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CElektrowartView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
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

bool CElektrowartView::GetInfoFromCallingView( CString& cStr, int nAction )
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
			cText.Format( "Artikel mit Elektro-Änderung vom %s - %s", cDatVon, cDatBis );
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

void CElektrowartView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}


void CElektrowartView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CElektrowartView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern

void CElektrowartView::OnFileSpeichern() 
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
	if ( !IsViaStdout() )
		FillBox( m_nNumberOfRows );	
}

void CElektrowartView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}



///////////////////////////////////////////////////////////////////
//  Ueber UnixStdOut

bool CElektrowartView::IsViaStdout()
{
	return true;
//	return theApp->GetServerMode() == 0;
}

void CElektrowartView::FillString( char *str, CString cStr, int lng )
{
	int lng1;
	lng1 = cStr.GetLength();
	if ( lng1 > lng )
		lng1 = lng;

	memset( str, ' ',  lng  );
	memcpy( str, cStr, lng1 );
	str[lng] = '\0';
}

void* CElektrowartView::BufFromGrid( int Row )
{
	static struct BUFF_ART p;
	char dat_str[20];
	char ear_alt[L_ZARTIKEL_ELEKTROSCHROTT + 1];
	Row++;
	FillString( p.ARTICLE_CODE, m_wndGrid.GetValueRowCol( Row, 1 ), MAX_LENGTH_ARTICLE_NO );
	FillString( p.EINHEIT, m_wndGrid.GetValueRowCol( Row, 2 ), L_ZARTIKEL_EINHEIT );
	FillString( p.ARTIKEL_NAME, m_wndGrid.GetValueRowCol( Row, 3 ), L_ZARTIKEL_ARTIKEL_NAME );
	strcpy( dat_str, m_wndGrid.GetValueRowCol( Row, 4 ) );
	ConvToPhoDate( dat_str, &p.DATUM_AENDER, "tt.mm.jjjj" );
	FillString( p.EAR_NEU, m_wndGrid.GetValueRowCol( Row, 5 ), L_ZARTIKEL_ELEKTROSCHROTT );
	FillString( ear_alt, m_wndGrid.GetValueRowCol( Row, 6 ), L_ZARTIKEL_ELEKTROSCHROTT );
	p.HERSTELLER_NR = atol( m_wndGrid.GetValueRowCol( Row, 7 ) );
	FillString( p.NAME, m_wndGrid.GetValueRowCol( Row, 8 ), L_HERSTEL_NAME );

	m_cEAR.SetAt ( 0, ear_alt );
	m_cNr.SetAt  ( 0, p.ARTIKEL_NR );
	return &p;
}

void CElektrowartView::BufFromZeile( struct BUFF_ART *p, CString Zeile )
{
	struct DRUCK_ZEILE d;

	strcpy( (char *) &d, Zeile );

	*d.fil1 = '\0';
	*d.fil2 = '\0';
	*d.fil3 = '\0';
	*d.fil4 = '\0';
	*d.fil5 = '\0';
	*d.fil6 = '\0';
	*d.fil7 = '\0';
	*d.eof  = '\0',

	strcpy( p->ARTICLE_CODE, d.ARTICLE_CODE );
	strcpy( p->EINHEIT, d.EINHEIT );
	strcpy( p->ARTIKEL_NAME, d.ARTIKEL_NAME );
	ConvToPhoDate( d.DATUM_AENDER, &p->DATUM_AENDER, "tt.mm.jjjj" );
	strcpy( p->EAR_NEU, d.EAR_NEU );
	p->HERSTELLER_NR = atol( d.HERSTELLER_NR );
	strcpy( p->NAME, d.NAME );
	m_cEAR.SetAt ( 0, d.EAR_ALT );
	m_cNr.SetAt  ( 0, p->ARTIKEL_NR );
}

int CElektrowartView::ReadViaStdout()
{
	CString Errmld;
	CString Command;
	CString Zeile;
	int s;
	int i;
	struct BUFF_ART p;
	ChUnixStdout m_Ux;

	m_wndGrid.hInitGrid( GRID_ROWS, -1);
	m_nNumberOfRows = 0;

	Command.Format( "srvzdpdruck 1 %ld %ld %s", m_nDatumVon, m_nDatumBis, theApp->GetDbaseName() );
	s = m_Ux.Open( Command, Errmld );

	if ( s != 0 )
	{
		AfxMessageBox( Errmld );
		return s;
	}

	// 1. member besetzen
	m_cEAR.RemoveAll();
	m_cNr.RemoveAll();
	m_cEAR.Add( " " );
	m_cNr.Add( 0 );

	BOOL bLockOld = m_wndGrid.LockUpdate(TRUE);
	m_wndGrid.SetReadOnly( FALSE );

	i = 1;
	while ( s == 0 )
	{
		s = m_Ux.Read( Zeile, Errmld );
		if ( s == 0 )
		{
			if ( Zeile.GetAt(0) == '_' )
			{
				Errmld = Zeile.Mid( 1 );
				s = -1;
			}
			else
			{
				if ( i > GRID_ROWS )
					m_wndGrid.SetRowCount( m_wndGrid.GetRowCount() + 1 );
				BufFromZeile( &p, Zeile );
				FillGrid( &p, i );
				i++;
				m_nNumberOfRows++;
			}
		}
	}

	m_wndGrid.hInitRestGrid( i );

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

	if ( s != 1 )
		AfxMessageBox( Errmld );

	m_Ux.Close();

	return s;

}
