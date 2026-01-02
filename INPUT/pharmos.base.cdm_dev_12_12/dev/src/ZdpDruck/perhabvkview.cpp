// PerhabvkView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "zdpdruck.h"
#include "PerhabvkView.h"

#include "GetBranches.h"
#include "GetRegion.h"

#include <eklibs/hamfcs/hMskDate.h>
#include "ViewNumbers.h"

#include "ServerDatum.h"
#include <hdatum/Phodate.h>

#include <libscsvoodoo/libscsvoodoo.h>
#include <eklibs/sqltabs/tabsqld.h>

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/zartwg.h>
#include <voodoo_table_header/herstel.h>
#include <voodoo_table_header/carticlecodes.h>

#include "FeldBreite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPerhabvkView

IMPLEMENT_DYNCREATE(CPerhabvkView, CFormView)

CPerhabvkView::CPerhabvkView()
	: ChPflegeView(CPerhabvkView::IDD)
{
	//{{AFX_DATA_INIT(CPerhabvkView)
	//}}AFX_DATA_INIT
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
	m_ProgMode = VIEW_PERHABVK;
}

CPerhabvkView::CPerhabvkView( int nProgNr )
	: ChPflegeView(CPerhabvkView::IDD)
{
	theApp = ((CEk1App*)AfxGetApp());
	m_bDoResize = false;
	if ( nProgNr == VIEW_PERHABVK )
		m_ProgMode = VIEW_PERHABVK;	
	else
		m_ProgMode = VIEW_PSENKABVK;	
}

CPerhabvkView::~CPerhabvkView()
{
}

void CPerhabvkView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPerhabvkView)
	DDX_Control(pDX, IDC_PERHABVK_FILZU, m_pbFilzu);
	DDX_Control(pDX, IDC_PERHABVK_BRANCH, m_cbBranch);
	DDX_Control(pDX, IDC_PERHABVK_DATBIS, m_DATUMBIS);
	DDX_Control(pDX, IDC_PERHABVK_DATVON, m_DATUMVON);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPerhabvkView, CFormView)
	//{{AFX_MSG_MAP(CPerhabvkView)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_COMMAND(ID_FILE_SPEICHERN, OnFileSpeichern)
	ON_UPDATE_COMMAND_UI(ID_FILE_SPEICHERN, OnUpdateFileSpeichern)
	ON_CBN_SELCHANGE(IDC_PERHABVK_BRANCH, OnSelchangePerhabvkBranch)
	ON_BN_CLICKED(IDC_PERHABVK_FILZU, OnPerhabvkFilzu)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Diagnose CPerhabvkView

#ifdef _DEBUG
void CPerhabvkView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPerhabvkView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////
// Implementation

void CPerhabvkView::InitPflege()
{
	m_wndGrid.SubclassDlgItem(IDC_PERHABVK_GRID, this );
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


// Regionen 

long CPerhabvkView::LoadRegiones( CGetRegion* Reg )
{
	return 0;
}

long CPerhabvkView::LoadBranches( CGetBranches* Fil, short region )
{
	CString cFiliale;
	CString cErr;
	long s;
	CWordArray wNumbers;
	CStringArray sNames;

	m_cbBranch.ResetContent( );

	s = Fil->ReadBranchOffices( cErr );
	s = Fil->GetAllExistentBranches(  wNumbers,  sNames,
								  true );
	int i = 0;
	while ( i < s)
	{
		//cFiliale = sNames[i];
		m_cbBranch.AddString( sNames[i] );
		i++;
	}
	return 0;

}


void CPerhabvkView::AlterUmsatzHeader()
{
	CString cS;
	char umsh[20];

	cS = GetUmsatzName();
	sprintf( umsh, "AbVk %s", cS.GetString());
	m_wndGrid.AlterColHeader( 12, umsh );
}

CString CPerhabvkView::GetUmsatzName()
{
	int index;
	CString cS;
	if ( m_bIstFiliale )
	{
		index = m_cbBranch.GetCurSel( );
		if ( index >= 0 )
		{
			m_cbBranch.GetLBText( index, cS );
			cS.TrimRight();
			cS.TrimLeft();
		}
	}
	else
	{
			cS = "Gesamt" ;

	}
	m_cUmsatzName = cS;
	for ( index = m_cUmsatzName.GetLength(); index < 9; index++ )
		m_cUmsatzName = " " + m_cUmsatzName;
	return cS;
}

void CPerhabvkView::OutFiliale()
{
// ??????????????????????????????
	m_nNumberOfRows = 0;
//	m_wndGrid.hZeroGrid();
	m_wndGrid.hInitGrid();
// ???????????????????????????????
	if ( m_bIstFiliale )
	{
		m_pbFilzu.SetWindowText( "&Filiale abschalten" );
		m_cbBranch.ShowWindow( SW_SHOW );
	}
	else
	{
		m_pbFilzu.SetWindowText( "&Filiale zuschalten" );
		m_cbBranch.ShowWindow( SW_HIDE );
	}
	AlterUmsatzHeader();
}

void CPerhabvkView::InitVariables()
{
	long  s;
	CString cErr;
	CWordArray wNumbers;
	CStringArray sNames;



	m_nDatumVon = PhoToday();
	m_nDatumBis = 0;
	m_DATUMVON.p_SetInput();
	m_DATUMBIS.p_SetInput();
	m_nNumberOfRows = 0;
//	m_wndGrid.hInitGrid();

	m_DATUMVON.SetFocus();

	
	m_bIstFiliale = false;
	m_cbBranch.ShowWindow( SW_HIDE );
	m_cbBranch.ResetContent( );

	m_pBranch = new CGetBranches( theApp->IsStandardEngine() );

	// VZs laden
	s = m_pBranch->ReadBranchOffices(  cErr);
	s = m_pBranch->GetAllExistentBranches(  wNumbers,  sNames,  true );
	int i = 0;
	while ( i < s)
	{
		//cFiliale = sNames[i];
		m_cbBranch.AddString( sNames[i] );
		i++;
	}
	s  = 0;

	m_bGelesen = s == 0;

	if ( m_bGelesen )
	{

		m_cbBranch.EnableWindow( TRUE );
		m_pbFilzu.EnableWindow ( TRUE );
		OutFiliale();
	}
	else
	{
		m_cbBranch.EnableWindow( FALSE );
		m_pbFilzu.EnableWindow ( FALSE );
		m_wndGrid.AlterColHeader( 12, "Kein AbVk" );
	}
}

bool CPerhabvkView::ValidateSuchb()
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

void CPerhabvkView::FirstInitGrid( )
{

	static struct GridColDesc gColDesc[] =
	{
		{ "Her#",			 5 },	
		{ "Herstellername",	18 },
		{ "ArtNr", MAX_LENGTH_ARTICLE_NO},	
		{ "Artikelname",	30 },
		{ "Apopfl",			 1 },
		{ "Rezpfl",			 1 },
		{ "Grosso alt",      9 }, 
		{ "Grosso",          9 }, 		 
		{ "% Änd.",			 9 }, 
		{ "Aep alt",         9 }, 
		{ "Aep",             9 }, 
		{ "Umsatz gesamt",  15 },
		{ "Gültig ab",       9 },	
		{ "Anlage",          9 },

		{ "abs. Änd.",		 9 },
		{ "Bestand",		 6 },
		{ "LW Änd.",		 9 },
		{ "Reichw",			 9 },
		{ "SWG1",			 4 },
		{ "SWG2",			 4 },
		{ "SWG3",			 4 },
		{ "PrSenk.",		 1 },
		
		{ "",				 0 },	
		{ NULL,				-1 },
	};

	m_wndGrid.FirstInitGrid( GRID_ROWS, gColDesc );
	m_wndGrid.RightAlignCol( 5, 9 );	// 9
	m_wndGrid.RightAlignCol( 10, 10 );
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
	double AENDERUNG_PCT;
	double AEP_ALT;
	double AEP;
	long DATUM_ANLAGE;
	long DATUMGUELTIGAB;
	long ARTIKEL_NR;
	
	double AENDERUNG_ABS;
	double BESTAND;
	double AENDERUNG_LW;
	char SWG1[L_ZARTWG_WARENGRUPPE + 1];
	char SWG2[L_ZARTWG_WARENGRUPPE + 1];
	char SWG3[L_ZARTWG_WARENGRUPPE + 1];
	char PREISSENK[L_ZARTIKEL_PREISSENKUNG + 1];

	long NACHFRAGE;
	double REICHWEITE;
};


void CPerhabvkView::FillGrid( void *pp, int index )
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
	cStr.Format( "%10.2f", p->AENDERUNG_PCT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 9 ), cStr );
	cStr.Format( "%10.2f", p->AEP_ALT );
	m_wndGrid.SetValueRange(CGXRange ( Row, 10 ), cStr );
	cStr.Format( "%10.2f", p->AEP );
	m_wndGrid.SetValueRange(CGXRange ( Row, 11 ), cStr );

	cStr.Format( "%ld", (p->NACHFRAGE+5)/12 );	/* Kaufmann. Runden */
	m_wndGrid.SetValueRange(CGXRange ( Row, 12 ), cStr );


	ConvFromPhoDate( dat_str, p->DATUMGUELTIGAB, "tt.mm.jjjj" );
	m_wndGrid.SetValueRange(CGXRange ( Row, 13 ), dat_str );
	ConvFromPhoDate( dat_str, p->DATUM_ANLAGE, "tt.mm.jjjj" );
	m_wndGrid.SetValueRange(CGXRange ( Row, 14 ), dat_str );
	
	cStr.Format( "%10.2f", p->AENDERUNG_ABS );
	m_wndGrid.SetValueRange(CGXRange ( Row, 15 ), cStr );
	cStr.Format( "%10.0f", p->BESTAND );
	m_wndGrid.SetValueRange(CGXRange ( Row, 16 ), cStr );
	cStr.Format( "%10.2f", p->AENDERUNG_LW );
	m_wndGrid.SetValueRange(CGXRange ( Row, 17 ), cStr );
	cStr.Format( "%10.2f", p->REICHWEITE * 12 ); // in Monaten
	m_wndGrid.SetValueRange(CGXRange ( Row, 18 ), cStr );
	m_wndGrid.SetValueRange(CGXRange ( Row, 19 ), p->SWG1 );
	m_wndGrid.SetValueRange(CGXRange ( Row, 20 ), p->SWG2 );
	m_wndGrid.SetValueRange(CGXRange ( Row, 21 ), p->SWG3 );
	m_wndGrid.SetValueRange(CGXRange ( Row, 22 ), p->PREISSENK );
		
	cStr.Format( "%7.7ld", p->ARTIKEL_NR );
	m_wndGrid.SetValueRange(CGXRange ( Row, 23 ), cStr );
	
}

void CPerhabvkView::FillBox( int anz )
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

CString CPerhabvkView::GetSelect( )
{
	CString sql;
	CString sql1;
	CString sql2;
	CString sql3;

	CString cArtAb;
	cArtAb = "artikelabverkauf";


	sql1.Format(  "select p.hersteller_nr,sortiername,lpad(trim(ARTICLE_CODE), %d, 0),artikel_name,z.apothekenpfl,z.rezeptpfl," \
			"grosso_alt,grosso, case when (grosso = aep or grosso = 0) and aep_alt > 0 then round( (aep/aep_alt-1)*100, 2)  else round( (grosso/grosso_alt-1)*100, 2) end as aenderung_pct," \
			"aep_alt,aep,p.datum_anlage,p.datumgueltigab,p.artikel_nr," \
			"case when grosso = aep or grosso = 0 then aep - aep_alt else grosso - grosso_alt end as aenderung_abs," \
			"sum(f.daily_stockbeginn) as bestand," \
			"case when grosso = aep or grosso = 0 then (aep - aep_alt) * sum( f.daily_stockbeginn)  else (grosso - grosso_alt) *  sum(f.daily_stockbeginn) end as aenderung_lw," \
			"w1.warengruppe, w2.warengruppe, w3.warengruppe, z.preissenkung " ,
			MAX_LENGTH_ARTICLE_NO);

	sql2 =	" from zpreiserhoehung p,outer herstel h,outer zartikel z, carticlecodes, outer zartwg w1, outer zartwg w2, outer zartwg w3, outer artikelf f ";
	
	sql3 =	" where articleno = p.artikel_nr and PREFERRED_FLAG = 1 and CODE_TYPE IN " \
			"(select CODE_TYPE from CCODETYPES where ARTNR_SUBSTITUTE = 1) and " \
			"grosso_alt>0 and z.artikel_nr=p.artikel_nr and ";
	
	if (m_ProgMode == VIEW_PERHABVK)
		sql3 +=	"((grosso_alt<grosso and grosso>0) or (aep_alt<aep and aep_alt>0 and (grosso=0 or grosso=aep))) and "; // Preiserhöhungen
	else
		sql3 +=	"((grosso_alt>grosso and grosso>0) or (aep_alt>aep and (grosso=0 or grosso=aep))) and "; // Preissenkungen
	
	sql3 +=	"h.hersteller_nr=p.hersteller_nr " \
			"and w1.art = '5' and w1.artikel_nr = p.artikel_nr " \
			"and w2.art = 'A' and w2.artikel_nr = p.artikel_nr " \
			"and w3.art = 'G' and w3.artikel_nr = p.artikel_nr " \
			"and f.artikel_nr = p.artikel_nr and f.filialnr in ( " ;		


	if ( m_bIstFiliale )
	{
		sql.Format( "%d", m_pBranch->GetCurrentBranchNumber( ) );
		sql3.Append(sql);
		sql3 += " ) ";

		sql1 += ",v.nachfrage, case when v.nachfrage = 0 then 0 else round( f.daily_stockbeginn / v.nachfrage, 2) end as reichweite_tage ";
		sql1 += sql2 + ",outer ";
		sql1 += cArtAb + " v";
		sql1 += sql3 + " and v.artikel_nr=p.artikel_nr and v.filialnr=";
		sql1 += sql;
	}
	else
	{
		sql3.Append(m_pBranch->GetBranches());
		sql3 += " ) ";

		sql1 += ",p.artikel_nr, grosso " + sql2 + sql3;   // Trick, da Artikel_nr long ( wie nachfrage )
	}


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
	
	sql += " group by 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,18,19,20,21,22,23 ";
	sql += " order by p.hersteller_nr,3,p.datumgueltigab";

	return sql;
}


CString CPerhabvkView::GetArtikelInSelect( int anz )
{
	struct BUFF_PERHOEH *p;
	int i;
	CString s;
	CString cNr;

	s = "";
	i = 0;
	do
	{
		p = (BUFF_PERHOEH *)m_hSelSql.GetBuffer( i );
		if ( p != NULL )
		{
			cNr.Format( "%ld", p->ARTIKEL_NR );
			s += cNr;
			s += ",";
			i++;
		}
	} while ( i < anz && p != NULL );
	s = s.Left( s.GetLength() - 1 );
	return s;
}

CString CPerhabvkView::GetSelect1( int anz )
{
	CString sql;
	CString cArt;
	CString cFil;
	CString cArtAb;

	cArtAb = "artikelabverkauf";

	cFil = m_pBranch->GetBranches();
	cArt = GetArtikelInSelect( anz );
	sql.Format( "select artikel_nr,sum(nachfrage) from %s " \
	            "where artikel_nr in(%s) and filialnr in(%s) group by artikel_nr",
				cArtAb, cArt, cFil );

//	AfxMessageBox( sql );

	return sql;
}

long CPerhabvkView::SecondFetch( int anz, CString cErrmld )
{
	long s;
	int fd;
	int i;
	long   artikel_nr;
	double nachfrage;
	CString sql;
	struct BUFF_PERHOEH *p;

	for ( i = 0; i < anz; i++ )
	{
		p = (BUFF_PERHOEH *)m_hSelSql.GetBuffer( i );
		p->NACHFRAGE = 0;			// Trick, da Artikel_nr long ( wie nachfrage )  siehe oben
		p->REICHWEITE = 0.0;
 //		m_hSelSql.ReplaceBuffer( i, p );
	}

	sql = GetSelect1( anz );
	s = SqlOpenCs( &fd, sql );
	if ( s != 0 )
	{
		cErrmld = DynErrmld();
		return s;
	}

	int j = 0;
	while ( s == 0 )
	{
		j++;
		s = SqlFetch( fd, 1, &artikel_nr, &nachfrage, NULL );
		if ( s == 0 )
		{
			for ( i = 0; i < anz; i++ )
			{
				p = (BUFF_PERHOEH *)m_hSelSql.GetBuffer( i );
				if ( p->ARTIKEL_NR == artikel_nr )
				{
					p->NACHFRAGE = (long)( nachfrage + 0.1 );

					if (p->NACHFRAGE > 0)
						p->REICHWEITE = p->BESTAND / p->NACHFRAGE;

//					m_hSelSql.ReplaceBuffer( i, p );
				}
			}
		}	
	}

	SqlCloseCs( fd );
	return 0;
}


void CPerhabvkView::EnableOrder( BOOL mode )
{
//	m_rdNr.EnableWindow( mode );
//	m_rdName.EnableWindow( mode );
}


int  CPerhabvkView::BearbeiteSatz()
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

int CPerhabvkView::SucheSatz( )
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
		if ( !m_bIstFiliale )
		{
			long s;
			theApp->BeginWaitAction( );
			s = SecondFetch( anz, cErrmld );
			theApp->EndWaitAction( );
			if ( s != 0 )
				AfxMessageBox( s );
		}

		FirstInitGrid();
		AlterUmsatzHeader();
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

int CPerhabvkView::NextSatz( )
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
		if ( !m_bIstFiliale )
		{
			long s;
			theApp->BeginWaitAction( );
			s = SecondFetch( anz, cErrmld );
			theApp->EndWaitAction( );
			if ( s != 0 )
				AfxMessageBox( s );
		}

		FillBox( anz );
		m_nNumberOfRows = anz;
		theApp->SetMenuOnOff( 0, 0, 0, 0, 0, 1 ); 
	}

	return -1;
}

int CPerhabvkView::PrevSatz()
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
		if ( !m_bIstFiliale )
		{
			long s;
			theApp->BeginWaitAction( );
			s = SecondFetch( anz, cErrmld );
			theApp->EndWaitAction( );
			if ( s != 0 )
				AfxMessageBox( s );
		}

		FillBox( anz );
		m_nNumberOfRows = anz;
		theApp->SetMenuOnOff( 0, 0, 0, 0, 1, 0 ); 
	}

	return -1;
}


int  CPerhabvkView::UndoSatz()
{
	if ( !m_bComeBack )
	{
		m_hSelSql.CloseCursor( );

	    delete m_pBranch;

		return 0;
	}
	else
		return 0; // -1;
}

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CPerhabvkView 


void CPerhabvkView::OnPerhabvkFilzu() 
{
	m_bIstFiliale = !m_bIstFiliale;
	OutFiliale();
}

void CPerhabvkView::OnSelchangePerhabvkBranch() 
{
	int nSel = m_cbBranch.GetCurSel();
	if (nSel == CB_ERR)
		TRACE0("Combo: no selection\n");
	else
	{
		CString cs;
		m_cbBranch.GetLBText(nSel, cs);
		TRACE1("Combo: selection is now '%s'\n", cs.GetBuffer(10));
		m_pBranch->SetCurrentBranch( nSel );
		OutFiliale();
	}
}


void CPerhabvkView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	InitPflege();

	m_bComeBack = false;
}

void CPerhabvkView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
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

void CPerhabvkView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
//	AfxMessageBox( "OnSize ");
	if ( m_bDoResize )
		ResizeControls( cx, cy );	
}


void CPerhabvkView::ResizeControls( int cx, int cy ) 
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

void CPerhabvkView::FillZeile( void *pp , CString& cStr )
{
	int weite;
	char dat_str1[12];
	char dat_str2[12];
	struct BUFF_PERHOEH *p;

	p = (struct BUFF_PERHOEH *) pp;

	ConvFromPhoDate( dat_str1, p->DATUM_ANLAGE, "tt.mm.jj" );
	ConvFromPhoDate( dat_str2, p->DATUMGUELTIGAB, "tt.mm.jj" );
	
	weite = m_cUmsatzName.GetLength();

	cStr.Format( "%5.5ld %s %s %s %s %s %10.2f %10.2f %10.2f %10.2f %10.2f %*ld %s %s %10.2f %10.0f %10.2f %10.2f      %s  %s  %s  %s ",
				p->HERSTELLER_NR,
				p->SORTIERNAME,
				p->ARTICLE_CODE,
				p->ARTIKEL_NAME,
				p->APOTHEKENPFL,
				p->REZEPTPFL,
				p->GROSSO_ALT,
				p->GROSSO,
				p->AENDERUNG_PCT,
				p->AEP_ALT,
				p->AEP,
				weite,
				(p->NACHFRAGE+5)/12,
				dat_str2,
				dat_str1,
				p->AENDERUNG_ABS,
				p->BESTAND,
				p->AENDERUNG_LW,
				p->REICHWEITE * 12,
				p->SWG1,
				p->SWG2,
				p->SWG3,
				p->PREISSENK);	
}

CString CPerhabvkView::GetListHeader()
{
	CString cS;
	CString cS2;
	cS = _T( "Hers# Herstellername         PZN      Artikelname                    " \
	         "A R Grosso-alt     Grosso  %Änderung    Aep-alt        Aep " );
	cS += m_cUmsatzName;
	cS += " Guelt.Ab Anlage  ";
	cS += " Änd.abs.    Bestand     Änd.LW     Reichweite   SWG1   SWG2   SWG3   Senk    ";
	return cS;
}                                                                        

CString CPerhabvkView::GetListStrich()
{
	int i;
	CString cS;
	for ( i = 0; i < GetListHeader().GetLength(); i++ )
		cS += "-";
	return cS;
}

bool CPerhabvkView::IsPrintZeile()
{
	void* p;
	p = m_hSelSql.GetBuffer( m_nSelectZeile );
	if ( p != NULL ) 
		return true;

	CString cErrmld;
	int anz = m_hSelSql.NextSelect( cErrmld );
	if ( anz <= 0 )
		return false;

// neu 18.02.2003
	if ( !m_bIstFiliale )
	{
		long s;
		s = SecondFetch( anz, cErrmld );
		if ( s != 0 )
			return false;
	}
// neu ende 18.02.2003

	m_nNumberOfRows = anz;
	m_nSelectZeile = 0;
	p = m_hSelSql.GetBuffer( m_nSelectZeile );
	return p != NULL;
}

void* CPerhabvkView::GetPrintZeile()
{
	return m_hSelSql.GetBuffer( m_nSelectZeile++ );
}

void CPerhabvkView::GenHeader( CString& cStr, CString cText, int nSeite, int nLng )
{
	CString s;
	long datum;
	long zeit;
	char datstr[15];
	datum = ::ActualDateTime( &zeit );
	ConvFromPhoDate( datstr, datum, "tt.mm.jj" );
	s.Format( "     %s %02d:%02d        Seite %d         ",
		      datstr, zeit/10000, (zeit/100)%100, nSeite );
	cText.TrimRight();
	nLng -= cText.GetLength() + s.GetLength() + 6;
	if ( nLng <= 0 ) nLng = 1;
	cStr = cText;
	while ( nLng-- > 0 )
		cStr += " ";
	cStr += s;
}

bool CPerhabvkView::GetInfoFromCallingView( CString& cStr, int nAction )
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
			
			if (m_ProgMode == VIEW_PERHABVK)
				cText.Format( "Preiserhoehung von %s - %s, Monats-Stückabverkauf %s", cDatVon, cDatBis, m_cUmsatzName );
			else
				cText.Format( "Preissenkungen von %s - %s, Monats-Stückabverkauf %s", cDatVon, cDatBis, m_cUmsatzName );

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

void CPerhabvkView::GotoDruckView(  )
{
	m_nSelectZeile = 0;		// ev. ausgewaehlte Zeile
	m_nSeite = 0;
	m_cUmsatzName = GetUmsatzName();

	// View wechseln
	theApp->PushMenuState(  );
	m_bComeBack = true;
	SetViewCalledFrom( this );
	theApp->ChangeToView( VIEW_DRUCK );
}


void CPerhabvkView::OnFilePrint() 
{
	// TODO: Add your command handler code here
	GotoDruckView(  );
}

void CPerhabvkView::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( m_nNumberOfRows );
}

//////////////////////////////////////////////////////
// Datei speichern

void CPerhabvkView::OnFileSpeichern() 
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

void CPerhabvkView::OnUpdateFileSpeichern(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_nNumberOfRows > 0 );	
}


