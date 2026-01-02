// DatacarePreisaend.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "ZdpDruck.h"
#include "DatacarePreisaend.h"

#include <eklibs/hamfcs/hMskNum.h>
#include "ViewNumbers.h"

#include "ServerDatum.h"
#include <hdatum/Phodate.h>

#include <libscsvoodoo/libscsvoodoo.h>

//#include <konvbuf.h>
#include <eklibs/sqltabs/tabsqld.h>
#include <eklibs/wunxlocs/hUnixStdout.h>

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zdcart.h>
#include <voodoo_table_header/nachfw.h>

#include "FeldBreite.h"

// CDatacarePreisaend

IMPLEMENT_DYNCREATE(CDatacarePreisaend, CFormView)

CDatacarePreisaend::CDatacarePreisaend()
	: ChPflegeView(CDatacarePreisaend::IDD)
{
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;

}

CDatacarePreisaend::~CDatacarePreisaend()
{
}

void CDatacarePreisaend::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VZ, m_VZ);
}

BEGIN_MESSAGE_MAP(CDatacarePreisaend, CFormView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
END_MESSAGE_MAP()


// CDatacarePreisaend-Diagnose

#ifdef _DEBUG
void CDatacarePreisaend::AssertValid() const
{
	CFormView::AssertValid();
}

void CDatacarePreisaend::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


// CDatacarePreisaend-Meldungshandler
void CDatacarePreisaend::InitPflege()
{
	m_wndGrid.SubclassDlgItem(IDC_DC_GRID, this );
	m_wndGrid.Initialize();	
	m_wndGrid.hZeroGrid();
	m_nNumberOfRows = 0;
	FirstInitGrid( );
	m_VZ.SetMask	(ED_LONG,
				     ED_NORMAL,
					 &m_nVZ,
					 2,
					 new ChMaskNum,
					 NULL );
	m_VZ.SetDialog( TRUE );

	m_nVZ = 61;
	m_VZ.SetFocus();

}

void CDatacarePreisaend::InitVariables()
{
	m_nNumberOfRows = 0;
	m_wndGrid.hInitGrid( GRID_ROWS, -1);
	m_VZ.p_SetInput();
}

bool CDatacarePreisaend::ValidateSuchb()
{
	return true;
}


void CDatacarePreisaend::FirstInitGrid( )
{
	static struct GridColDesc gColDesc[] =
	{
		{ "Artikelbezeichnung",	 30 },	
		{ "Einheit", 12 },
		{ "AEP-Alt", 12 },
		{ "AEP-Neu", 12 },
		{ "Diff-WT", 12 },
		{ "Diff-%" , 12 },
		{ "PZN",7},
		{ "ABVERKAUF",12},
		{ NULL,				 -1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );
}


void CDatacarePreisaend::FillGrid( void *pp, int index )
{
	struct BUFF_PREISAEND *p;
	ROWCOL Row;

	CString cStr;

	Row = index;
	p = (struct BUFF_PREISAEND *) pp;

	m_wndGrid.SetValueRange(CGXRange ( Row, 1 ), p->ARTIKEL_NAME );
	m_wndGrid.SetValueRange(CGXRange ( Row, 2 ), p->EINHEIT );
	cStr.Format( "%9.2f", p->AEP );
	m_wndGrid.SetValueRange(CGXRange ( Row, 3 ), cStr );
	cStr.Format( "%9.2f", p->DC_AEP );
	m_wndGrid.SetValueRange(CGXRange ( Row, 4 ), cStr );
	cStr.Format( "%9.2f", p->DIFFWERT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 5 ), cStr );
	cStr.Format( "%9.2f", p->DIFFPROZ );
	m_wndGrid.SetValueRange(CGXRange ( Row, 6 ), cStr );
	cStr.Format( "%7.7ld", p->ARTIKEL_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 7 ), cStr );
	cStr.Format( "%7.2f", p->ABVERKAUF );
	m_wndGrid.SetValueRange(CGXRange ( Row, 8 ), cStr );
}

void CDatacarePreisaend::FillBox( int anz )
{
	int i;
	bool bInsert = true;

	BOOL bLockOld = m_wndGrid.LockUpdate(TRUE);
	m_wndGrid.SetReadOnly( FALSE );

	i = 0;
	for(i = 0;i < anz;i++)
		FillGrid( (void*) (&m_arArtikel[i]), i + 1);
	

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

void CDatacarePreisaend::GetDelimiter( char *info, char *delim )
{
	int lng;
	lng = static_cast<int>(strlen( info )) - 1;
    while ( info[lng] == ' ' ) lng--;
    *delim = info[lng++];
    info[lng] = '\0';
}

CString CDatacarePreisaend::GetSelect( bool bSortAsc )
{
	CString s;
	long datum,jahr,monat;
	long zeit;
	datum = ::ActualDateTime( &zeit );
	jahr  = datum / 10000;
	monat = datum / 100 - jahr * 100;

	if (monat < 12) 	{
		datum = jahr * 10000 + (++monat) * 100  + 1;
	}
	else
		datum = (++jahr) * 10000 + 1 * 100  + 1;

	CString csDatum;
	csDatum.Format	("%8.8d",datum);
	//"where dc_datumgueltigab = %s and dc_artikel_nr = b.artikel_nr and substr(nb_dc_plausi,13,1) <> '9' and b.artikel_nr = c.artikel_nr and c.art = '2' and c.warengruppe matches '01*' " 
	CString sql1 = "select artikel_name,einheit,d.aep,dc_aep,(dc_aep - d.aep) as diffwert, (dc_aep - d.aep) / d.aep * 100 as diffproz,dc_artikel_nr from zdcart a,zartikel b,zartwg c,zartpreis d " \
				  "where dc_datumgueltigab = %s and dc_artikel_nr = b.artikel_nr  and b.artikel_nr = c.artikel_nr and c.art = '2' and c.warengruppe matches '01*' " \
				  "and c.warengruppe <> '01720' and c.warengruppe <> '01730' " \
				  "and b.artikel_nr = d.artikel_nr and d.datumgueltigab = ( select max(datumgueltigab) from zartpreis where datumgueltigab < %s and zartpreis.artikel_nr = b.artikel_nr) " \
				  "and d.aep <> 0 and d.aep <> dc_aep order by diffproz" ;
	if (! bSortAsc ) 
		sql1 += " desc ";

	CString sql;
	sql.Format(sql1,csDatum,csDatum);

	return sql;
}

void CDatacarePreisaend::EnableOrder( BOOL mode )
{
}


int CDatacarePreisaend::BearbeiteSatz()
{
	return -1;
}

int CDatacarePreisaend::SucheSatz( )
{
	CString cErrmld;
	bool bSortAsc = false;
	int i, iGelesen;

	struct BUFF_PREISAEND stPreisaend;
	HDYNSQL	iFd = -1;
	long lRetCode;

// ??????????????????????????????
	m_nNumberOfRows = 0;
//	m_wndGrid.hZeroGrid();
	m_wndGrid.hInitGrid();
// ???????????????????????????????


	m_VZ.p_GetInput();
	iGelesen = 0;
	for ( i = 0; i < 60;i++) {
		m_arArtikel[i].ARTIKEL_NR = 0;
		m_arArtikel[i].ARTIKEL_NAME[0] = '\0';
		m_arArtikel[i].EINHEIT[0] = '\0';
		m_arArtikel[i].ABVERKAUF  = 0;
		m_arArtikel[i].AEP  = 0;
		m_arArtikel[i].DIFFWERT = 0.0;
		m_arArtikel[i].DIFFPROZ = 0.0;
		m_arArtikel[i].DC_AEP  = 0;
	}

	m_sSql = GetSelect(bSortAsc);	
	m_csFelderNachfrage = GetFelderSelectNachfrage();
	if ( m_sSql.IsEmpty() )
		return -1;

	theApp->BeginWaitAction( );
	lRetCode = SqlOpenCs(&iFd, m_sSql);
	
	iGelesen = 0;
	// die ersten 25 werden unabhängig vom Abverkauf angezeigt
	for (i = 0; i < 25;i++) {
		lRetCode = SqlBufferedFetch(iFd,1,25,&stPreisaend,NULL);
		if ( SQL_SUCCESS == lRetCode  ) {
			if (stPreisaend.DIFFPROZ > 0) {
				m_arArtikel[i] = stPreisaend;
				m_arArtikel[i].ABVERKAUF = -1;
				iGelesen ++;
			}
			else 
				break;
			if (i >= 24)
				break;
		}
		else
			break;
	}

	// Keine 25 Preiserhöhungen gefunden
	if (( iGelesen  < 24) && ( SQL_SUCCESS == lRetCode))
		InsertIntoArray(&stPreisaend);


	while (SQL_SUCCESS == (lRetCode = SqlBufferedFetch(iFd,1,25,&stPreisaend,NULL) )) {
		iGelesen++;
		cErrmld.Format("Gelesen: %6.6d",iGelesen);
		((CFrameWnd*)AfxGetMainWnd())->SetMessageText(cErrmld);
		InsertIntoArray(&stPreisaend);
			
	}
	((CFrameWnd*)AfxGetMainWnd())->SetMessageText("");
	SqlCloseCs(iFd);
	FirstInitGrid();
	SortArray(0,49);	// Preiserhöhungen
	SortArray(50,59);
	FillBox( 60 );
	m_nNumberOfRows = 60;
	theApp->SetMenuOnOff( 0, 0, 0, 0, 1, -1 );  

	if (0 == iGelesen ) {
		m_wndGrid.hInitGrid();
		m_nNumberOfRows = 0;
		theApp->SetMenuOnOff( 0, 0, 0, 0, -1, -1 );  
	}

	theApp->EndWaitAction( );
	EnableOrder( m_nNumberOfRows <= 0 );


	if ( m_nNumberOfRows > 0 )
		return  1;
	else
		return -1;
}

int CDatacarePreisaend::NextSatz( )
{
	CString cErrmld;
	int anz;
	theApp->BeginWaitAction( );
	//anz = m_hSelSql.NextSelect( cErrmld );
	anz  = 0;
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

int CDatacarePreisaend::PrevSatz()
{
	CString cErrmld;
	int anz;
	theApp->BeginWaitAction( );
	//anz = m_hSelSql.PrevSelect( cErrmld );
	anz = 0;
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


int  CDatacarePreisaend::UndoSatz()
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

void CDatacarePreisaend::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CDatacarePreisaend::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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
				//FillBox( m_nNumberOfRows );
				theApp->PopMenuState(  );
				theApp->SetMenuOnOff( 0, 0, 0, 0, 1, 1 ); 
			}
		}		
	}
}

void CDatacarePreisaend::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CDatacarePreisaend::ResizeControls( int cx, int cy ) 
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
	char ARTIKEL_NAME[31];
	char fil1[2];
	char EINHEIT[10];
	char fil2;
	char DC_AEP[12];
	char fil3;
	char AEP[12];
	char fil4;
	char DIFFWERT[12];
	char fil5;
	char DIFFPROZ[12];
	char fil6;
	char ARTIKEL_NR[8];
	char eof;

};

void CDatacarePreisaend::FillZeile( void *pp , CString& cStr )
{
	struct BUFF_PREISAEND *p;

	p = (struct BUFF_PREISAEND *) pp;

	cStr.Format("%30.30s  %10.10s %8.2f %8.2f %8.2f %8.2f %7d",p->ARTIKEL_NAME,p->EINHEIT,p->AEP,
		p->DC_AEP,p->DIFFWERT,p->DIFFPROZ,p->ARTIKEL_NR);

}

CString CDatacarePreisaend::GetListHeader()
{
	return _T( "Artikelbezeichnung                 Einheit  AEP-Alt  AEP-Neu  Diff-WT   Diff-%     PZN" );
}

CString CDatacarePreisaend::GetListStrich()
{
	return _T( "---------------------------------------------------------------------" \
		       "---------------------------" );
}

bool CDatacarePreisaend::IsPrintZeile()
{
	if (m_nSelectZeile < 60)
		return true;
	else
		return false;
	
}

void* CDatacarePreisaend::GetPrintZeile()
{
	if (m_nSelectZeile < 60)
		return &(m_arArtikel[m_nSelectZeile++]);
	else
		return NULL;
}

void CDatacarePreisaend::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
{
	CString s,csVz;
	long datum;
	long zeit;
	char datstr[15];
	datum = ::ActualDateTime( &zeit );
	ConvFromPhoDate( datstr, datum, "tt.mm.jj" );
	switch ( m_nVZ)
	{
	case 61:
		csVz = "PHOENIX Wien";
		break;
	case 62:
		csVz = "PHOENIX Graz";
		break;
	case 63:
		csVz = "PHOENIX Linz";
		break;
	case 64:
		csVz = "PHOENIX Jenbach";
		break;
	default:
		csVz = "";
	}


	s.Format("VZ:%2.2d %s %s %02d:%02d   Seite %d", m_nVZ,csVz,datstr, zeit/10000, (zeit/100)%100, nSeite );
	cText.TrimRight();
	nLng -= cText.GetLength() + s.GetLength() + 6;
	if ( nLng <= 0 ) nLng = 1;
	cStr = cText;
	while ( nLng-- > 0 )
		cStr += " ";
	cStr += s;
}

bool CDatacarePreisaend::GetInfoFromCallingView( CString& cStr, int nAction )
{

	int DruckBreite = 100;

	char datstr[12];
	long datum,jahr,monat;
	long zeit;


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
			datum = ::ActualDateTime( &zeit );

			datum = ::ActualDateTime( &zeit );
			jahr  = datum / 10000;
			monat = datum / 100 - jahr * 100;

			if (monat < 12) 	{
				datum = jahr * 10000 + (++monat) * 100  + 1;
			}
			else
				datum = (++jahr) * 10000 + monat * 100  + 1;


			ConvFromPhoDate( datstr, datum, "tt.mm.jjjj" );

			cText.Format( "Wichtige Preisänderungen per %s",datstr);
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

void CDatacarePreisaend::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}


void CDatacarePreisaend::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CDatacarePreisaend::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern

void CDatacarePreisaend::OnFileSpeichern() 
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
	// FillBox( m_nNumberOfRows );	
}

void CDatacarePreisaend::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}

///////////////////////////////////////////////////////////////////
//  Ueber UnixStdOut


void CDatacarePreisaend::FillString( char *str, CString cStr, int lng )
{
	int lng1;
	lng1 = cStr.GetLength();
	if ( lng1 > lng )
		lng1 = lng;

	memset( str, ' ',  lng  );
	memcpy( str, cStr, lng1 );
	str[lng] = '\0';
}


void* CDatacarePreisaend::BufFromGrid( int Row )
{
	static struct BUFF_PREISAEND p;

	Row++;

	FillString( p.ARTIKEL_NAME, m_wndGrid.GetValueRowCol( Row, 1 ), L_ZARTIKEL_ARTIKEL_NAME);
	FillString( p.EINHEIT, m_wndGrid.GetValueRowCol( Row, 2 ), L_ZARTIKEL_EINHEIT );
	p.AEP  = atof( m_wndGrid.GetValueRowCol( Row, 3 ) );
	p.DC_AEP  = atof( m_wndGrid.GetValueRowCol( Row, 4 ) );
	p.DIFFWERT  = atof( m_wndGrid.GetValueRowCol( Row, 5 ) );
	p.DIFFPROZ  = atof( m_wndGrid.GetValueRowCol( Row, 6 ) );
	p.ARTIKEL_NR = atol( m_wndGrid.GetValueRowCol( Row, 7 ) );

	return &p;
}

void CDatacarePreisaend::BufFromZeile( struct BUFF_PREISAEND *p, CString Zeile )
{
	struct DRUCK_ZEILE d;

	strcpy( (char *) &d, Zeile );

	p->ARTIKEL_NR = atol( d.ARTIKEL_NR );
	p->AEP = atof( d.AEP );
	p->DC_AEP = atof( d.DC_AEP );
	p->DIFFWERT = atof( d.DIFFWERT );
	p->DIFFPROZ = atof( d.DIFFPROZ );
	strcpy( p->ARTIKEL_NAME, d.ARTIKEL_NAME );
	strcpy( p->EINHEIT, d.EINHEIT );

}

CString CDatacarePreisaend::GetFelderSelectNachfrage()
{
	CString sql1,sql2;
	long datum,jahr,monat,jahr1;
	long zeit,kw;

	datum = ::ActualDateTime( &zeit );
	jahr  = datum / 10000;
	monat = datum / 100 - jahr * 100;

	datum = jahr * 10000 + monat * 100  + 28;
	if (monat != 2)
		datum += 2;

	kw = KalWeek(datum,&jahr1);
	sql1 = "";
	for (int i = 0; i < 4;i++) {
		if (0 == (jahr1 % 2))	// gerades Jahr
			sql2.Format("gj_%2.2d",kw);
		else
			sql2.Format("uj_%2.2d",kw);
		if (sql1.IsEmpty())
			sql1 = sql2;
		else
		{
			sql1 += " + ";
			sql1 += sql2;
		}
		kw--;
		if (0 == kw)
		{
			datum = (jahr-1) * 10000 + 12 * 100  + 31;	// Vorjahresletzter
			kw = KalWeek(datum,&jahr1);
		}
	}
	return sql1;
}

void CDatacarePreisaend::InsertIntoArray(struct BUFF_PREISAEND *p)
{
	long lSqlResult;
	int i;
	double dWert;
	char sql[2000];

//	sprintf (sql,"select %s from pps1au@db1_pps1_tcp:Nachfw where Artikel_Nr = %7.7d and FilialNr = %2.2d ",m_csFelderNachfrage,p->ARTIKEL_NR,m_nVZ );
	sprintf (sql,"select %s from Nachfw where Artikel_Nr = %7.7d and FilialNr = %2.2d ", m_csFelderNachfrage.GetString(),p->ARTIKEL_NR, m_nVZ );
	lSqlResult = SqlRead(sql,&dWert,NULL);
	p->ABVERKAUF =dWert;

	if (p->DIFFPROZ < 0) 	// Preiserhöhung 10 Einträge ab Feldnummer 50
		i = GetIndexKleinsterAbverkauf(50,59);
	else 	
		i = GetIndexKleinsterAbverkauf(25,49);

	if (m_arArtikel[i].ABVERKAUF < p->ABVERKAUF)
		m_arArtikel[i] = *p;

}


long CDatacarePreisaend::KalWeek (long datum, long *jahr)
{
   struct tm  t;           /* Datum und Zeit als Struktur            */
//   int        w;           /* Woche des laufenden Jahres           */
   long       w;           /* Woche des laufenden Jahres             */
   int        wt1;         /* Wochentag des 1. Januar des Jahres     */
   int        wt;          /* Wochentag: 0 = Montag ... 6 = Sonntag  */
   int        at;          /* Tag des Jahres seit 1.Jan (0-365)      */
   int        tmp;         /* Zwischenwert                           */
   int        montmp;      /* Zwischendatum                          */
   
   /***************************************************************/
   /*  Wochentag des 1.1. des eingegebenen Jahres bestimmen       */
   /*  (Mo=0, Di=1, Mi=2, Do=3, Fr=4, Sa=5, So=6)                 */
   /***************************************************************/
   t.tm_sec   = 0;
   t.tm_min   = 0;
   t.tm_hour  = 0;
   t.tm_mday  = 1;
   t.tm_mon   = 0;
   t.tm_year  = (int) (datum / 10000 - 1900);
   t.tm_wday  = 0;
   t.tm_yday  = 0;
   t.tm_isdst = 0;

   *jahr = 0;
 
   if ( t.tm_year < 70 ) return (0);

   mktime ( &t );
 
   wt1 = t.tm_wday - 1;
 
   if ( wt1 < 0 )
      wt1 = 6;
 
   /***************************************************************/
   /*  Wochentag und Tageszahl des eingegebenen Datums bestimmen  */
   /***************************************************************/
   tmp = t.tm_year;
   tmp += 1900;
   tmp *= 10000;    
   montmp = datum - tmp;
   t.tm_mon = montmp / 100 - 1;
   montmp = t.tm_mon + 1;
   t.tm_mday  = datum - tmp - (montmp * 100);
 
   mktime ( &t );
 
   wt = t.tm_wday - 1;
 
   if ( wt < 0 )
      wt = 6;
 
   at = t.tm_yday - wt + wt1;
 
   if ( wt1 < 4 )       /* 1. Jan. ist Mo., Di., Mi. o. Do.       */
      w = at / 7 + 1;   /* => gehoert zur 1. KW diesen Jahres     */
   else                 /* 1. Jan. ist ein Fr., Sa. o. So.        */
      w = at / 7;       /* => zur letzten KW des vorherg. Jahres  */
 
   if ( w > 52 )
   {
      t.tm_mday  = 31;
      t.tm_mon   = 11;
 
      mktime ( &t );
 
      wt1 = t.tm_wday - 1;
 
      if ( wt1 < 0 )
         wt1 = 6;
 
      if ( wt1 < 3 )         /* 31.12. ist Mo., Di. o. Mi.        */
      {
         w = 1;              /* => gehoert zur 1. Kalenderwoche   */
         t.tm_year++;        /*    des naechsten Jahres           */
      }
      
      *jahr = (long) ( t.tm_year + 1900 );
   }
   else if ( w <= 0 )        /* => gehoert zur letzten KW         */
   {                         /*    des vorhergehenden Jahres      */
      t.tm_mday = 31;
      t.tm_mon  = 12;
      t.tm_year = datum / 10000 - 1901;

      tmp = t.tm_year + 1900;
      tmp *= 10000;    
      datum = tmp + t.tm_mon * 100 + t.tm_mday;

      w = KalWeek ( datum , jahr );
   }
   else
      *jahr = (long) ( t.tm_year + 1900 );

   return (w);
}

int	CDatacarePreisaend::GetIndexKleinsterAbverkauf(int iUntereSchranke,int iObereSchranke)
{
	int i,iIndex;
	i = iIndex =  iUntereSchranke;
	double dAbverkauf = 9999999;
	while ( i <= iObereSchranke ) {
		if (m_arArtikel[i].ABVERKAUF < dAbverkauf) {
			iIndex = i;
			dAbverkauf = m_arArtikel[i].ABVERKAUF;
		}
		i++;
	}

	return iIndex;
}

// Ja es gibt ihn noch den Bubble-Sort
void CDatacarePreisaend::SortArray(int iUntereSchranke,int iObereSchranke)
{
	int i;
	bool bTausch = true;
	struct BUFF_PREISAEND m_ArtikelTmp;
	
	while (bTausch) {
		bTausch = false;
		for (i = iUntereSchranke+1;i <= iObereSchranke;i++) {
			if (strcmp(m_arArtikel[i].ARTIKEL_NAME,m_arArtikel[i-1].ARTIKEL_NAME) < 0) 	{
				m_ArtikelTmp = m_arArtikel[i-1];
				m_arArtikel[i-1] = m_arArtikel[i];
				m_arArtikel[i]   = m_ArtikelTmp;
				bTausch = true;
			}
		}
	}
}