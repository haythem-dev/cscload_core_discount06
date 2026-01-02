// ArtikelIfa.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtikelIfa.h"
#include "IfaFiles.h"
#include "GetIfaVerz.h"
#include "GetUnixFiles.h"
#include "GuelDatum.h"
// #include <wudu.h>
#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/wunxlocs/UnixSys.h>
#include <hdatum/phodate.h>
#include "MenuNumbers.h"
#include "ServerDatum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
// CMbox2
/*
CMbox2::CMbox2()
{
}
*/

CMbox2::~CMbox2()
{
	CloseCursor( );
}


long CMbox2::GetTagesdatum()
{
	if ( m_tagesdatum == -1 )
		m_tagesdatum = ::Today();
	return m_tagesdatum;
}

CString CMbox2::InitSelect( CString SuchBegriff )
{
	CString sql;
	CString SuchB0;
	CString SuchB1;
	CString SuchB2;
	CString SuchB3;
	CString SuchBRest;
	int iPos;
	int mode;

//	AfxMessageBox( SuchBegriff );
	// Suchbegriff :  "Keys\nIFANR\nMatchcode\nHerstNum" 
	// Keys: xxx -> AENDERART STATUS NACHBEARBEITUNG	
	// Parsen
	iPos = SuchBegriff.Find("\n");

	SuchB0 = SuchBegriff.Left(iPos); 
	SuchB0.TrimLeft();
	SuchB0.TrimRight();

	SuchBRest = SuchBegriff.Mid(iPos + 1);

	iPos = SuchBRest.Find("\n");
	if ( iPos == -1 )
	{
		SuchB1 = SuchBRest;		// IFANR
		SuchB2 = _T("");		// Matchcode
	}
	else
	{
		SuchB1 = SuchBRest.Left(iPos);
		SuchB2 = SuchBRest.Mid(iPos + 1);
	}

	SuchB1.TrimLeft();
	SuchB1.TrimRight();
//	SuchB2.TrimLeft();
//	SuchB2.TrimRight();

	iPos = SuchB2.Find("\n");
	if ( iPos == -1 )
	{
		SuchB3 = _T("");		// Hersteller
	}
	else
	{
		CString Save;
		Save = SuchB2;
		SuchB2 = Save.Left(iPos);
		SuchB3 = Save.Mid(iPos + 1);
	}

	SuchB2.TrimLeft();
	SuchB2.TrimRight();
	SuchB3.TrimLeft();
	SuchB3.TrimRight();

/*
	AfxMessageBox( SuchB1 );
	AfxMessageBox( SuchB2 );
	AfxMessageBox( SuchB3 );
*/

	
	mode = 0;

	CString lengthCode;
	lengthCode.Format("%d", L_CARTICLECODES_ARTICLE_CODE);

	sql  = "select IFANR,SATZNR,DATUMGUELTIGAB,IFASTATUS,NBSTATUS,nvl(ARTICLE_CODE, rpad(A00PZN, ";
	sql += lengthCode + ", ' ')),";
	sql += "A00PBEZ,A00PGMENG,A00PGEINH,A00ANBNR,AENDERUNG,HERSTELLER_NR,SORTIERNAME,A00PZN ";
	sql += "from ZIFAART,outer CARTICLECODES,outer HERSTEL";
	sql += " where HERSTELLER_NR=A00ANBNR";
	sql += " and CARTICLECODES.ARTICLENO=ZIFAART.A00PZN ";
	sql += " and PREFERRED_FLAG = 1 ";
	sql += " and CODE_TYPE in (SELECT CODE_TYPE FROM CCODETYPES WHERE ARTNR_SUBSTITUTE = 1) ";
	sql += " and IFANR=";
	sql += SuchB1;

	if ( IsNumber( SuchB3 ) )
	{
		CString nr;
		if ( atol( SuchB3 ) > 0 )
		{
			nr.Format("%ld", atol( SuchB3) );
			sql += " and A00ANBNR=";
			sql += nr;
		}
		else
		{
//			sql += " and A00ANBNR matches '*'";
			sql += " and A00ANBNR>=0";
			mode = 1;
		}
	}

	if ( SuchB0.GetAt(0) != 'x' )
	{
		char kenn[4];
		char ze;
		ze = SuchB0.GetAt(0);
		strcpy ( kenn, "' '" );
		if ( ze == '0' )
			kenn[1] = '0';
		else if ( ze == 'f' )
			kenn[1] = '2';		// fehlerhafte Neuanlage
		else if ( ze == 'g' )	
			kenn[1] = '3';		// fehlerhafte Aenderung
		else
			kenn[1] = '1';
		sql += " and AENDERUNG=";
		sql += kenn;
		if ( ze == '2' || ze == '3' )
		{	
			char heute[14];
//			sprintf( heute, "%ld", ::Today() );
			sprintf( heute, "%ld", GetTagesdatum() );
			sql += " and DATUMGUELTIGAB ";
			if ( ze == '2' )
				sql += "<= ";
			else
				sql += "> ";
			sql += heute;
		}
	}

	if ( SuchB0.GetAt(1) != 'x' )
	{
		char kenn[4];
		strcpy ( kenn, "' '" );
		kenn[1] = SuchB0.GetAt(1);
		sql += " and IFASTATUS=";
		sql += kenn;
	}

	if ( SuchB0.GetAt(2) != 'x' )
	{   
		char status;
		status = SuchB0.GetAt(2);				
		if ( status == '0' )					// ohne Fehler
			sql += " and NBSTATUS='0'";			
		else if ( status == '1' )				// nicht zwingend exclusiv
			sql += " and NBSTATUS='1'";		  
		else if ( status == '2' )				// zwingend
			sql += " and (NBSTATUS='2' or NBSTATUS='3' or NBSTATUS>='6')";   
		else if ( status == '3' )				// Plausi-Fehler
			sql += " and NBSTATUS>='4'";		   
		else								// zur Nachbearbeitung								
		    sql += " and NBSTATUS>='2'";    
	}


	if ( mode == 1 )
	{
		sql += " order by IFANR,A00ANBNR,A00PBEZ";
		return sql;
	}

	if ( IsNumber( SuchB2 ) )
	{
 		if ( SuchB2.GetLength( ) > 7 )
		{
			sql += " and A00PZN>= (SELECT articleno FROM carticlecodes WHERE CODE_TYPE in (SELECT CODE_TYPE FROM CCODETYPES WHERE ARTNR_SUBSTITUTE = 1) and ";
			sql += " lpad(trim(ARTICLE_CODE)," + lengthCode + ", '0') = lpad(";
			sql += SuchB2 + "," + lengthCode + ",'0'))";
		}
		else
		{ // für PZN-7 Neuanlagen existiert hier noch gar kein AC !!!
			CString nr;
			nr.Format("%ld", atol( SuchB2 ) );
			sql += " and A00PZN>=";
			sql += nr;
		}		
		
		/* keine Suche nach ArticleCode, sondern nach dem Wert, der von Ifa geliefert wird !
        sql += "and ARTICLENO IN (SELECT articleno FROM carticlecodes WHERE ";
		
		sql += " lpad(trim(ARTICLE_CODE)," + lengthCode + ", '0') >= lpad(";
		sql += SuchB2 + "," + lengthCode + ",'0'))";*/
		

		sql += " order by IFANR,A00PZN";
	}
	else
	{
		sql += " and A00PBEZ matches '";
		sql += SuchB2;
		sql += "*'";
		sql += " order by IFANR,A00PBEZ";
	}

//	AfxMessageBox( sql );

	return sql;
}


void CMbox2::FillBuffer( CStringArray& s, void **VecPtr )
{
	s.SetSize( 11 );

	s[0] = m_SelBuf.ARTIKEL_CODE;

	if ( m_SelBuf.AENDERUNG[0] == '1' )
	{
//		if ( m_SelBuf.DATUMGUELTIGAB <= ::Today() )
		if ( m_SelBuf.DATUMGUELTIGAB <= GetTagesdatum() )  /* ????? */
			s[1] = CResString::ex().getStrTblText(IDS_STRING951);
		else
			s[1] = CResString::ex().getStrTblText(IDS_STRING666);
	}
	else if ( m_SelBuf.AENDERUNG[0] == '2' )
		s[1] = "x";
	else
		s[1] = CResString::ex().getStrTblText(IDS_STRING667);

	s[2] = m_SelBuf.IFASTATUS;		 //  Ifastatus	
	
	if ( *m_SelBuf.NBSTATUS & 1 )    //  Nicht Zwingend
		s[3] = "x";
	else
		s[3] = " ";

	if ( *m_SelBuf.NBSTATUS & 2 )    //  Zwingend
		s[4] = "x";
	else
		s[4] = " ";

	if ( *m_SelBuf.NBSTATUS & 4 )    //  Plausi
		s[5] = "x";
	else
		s[5] = " ";

	s[6] = m_SelBuf.A00PBEZ;

	s[7]  = m_SelBuf.A00PGMENG;
	s[7] += m_SelBuf.A00PGEINH;

	char str[12];
	sprintf( str, "%.5ld", m_SelBuf.A00ANBNR );
	s[8] = str;
	s[8].TrimLeft();
	s[9] = m_SelBuf.SORTIERNAME;

	sprintf( str, "%.8ld", m_SelBuf.A00PZN );
	s[10] = str;
	s[10].TrimLeft();

	m_VecBuf.IFANR  = m_SelBuf.IFANR;
	m_VecBuf.SATZNR = m_SelBuf.SATZNR;
	m_VecBuf.A00PZN = m_SelBuf.A00PZN;
	*VecPtr = &m_VecBuf;
}


void CMbox2::InitSuchBox()
{
	ListColumns Fields[] =			  
	{
		PHZNR,  _strdup(CResString::ex().getStrTblText(IDS_ARTNR)),      120,   LVCFMT_LEFT,  1, // must be left aligned
		EAENDER,_strdup(CResString::ex().getStrTblText(IDS_EAENDER)),	21,   LVCFMT_LEFT,  0,	
		IFASTAT,_strdup(CResString::ex().getStrTblText(IDS_DCSTAT)),		21,   LVCFMT_LEFT,  0,	
		ENZWING,_strdup(CResString::ex().getStrTblText(IDS_ENZWING)),	21,   LVCFMT_LEFT,  0,		
		EZWING, _strdup(CResString::ex().getStrTblText(IDS_EZWING)),		21,   LVCFMT_LEFT,  0,				
		EPLAU,  _strdup(CResString::ex().getStrTblText(IDS_EPLAU)),		21,   LVCFMT_LEFT,  0,		
		ARTBEZ,	_strdup(CResString::ex().getStrTblText(IDS_ARTBEZ)),		230,  LVCFMT_LEFT,  0, //40
		EINHEIT,_strdup(CResString::ex().getStrTblText(IDS_EINHEIT)),    80,   LVCFMT_RIGHT, 0, //40
		HERNR,  _strdup(CResString::ex().getStrTblText(IDS_HERNR)),      60,   LVCFMT_LEFT,  0,
		HERMC,  _strdup(CResString::ex().getStrTblText(IDS_MATCHCODE)),	210,  LVCFMT_LEFT,   0,
		-1        , NULL,         0,   0,			 0
	};
 
	InitBox( PUFFER_ANZAHL, Fields, sizeof( struct VecBuf )  );

	for (short ColNr = 0; ColNr < GetFieldCount(); ColNr++)
		free(Fields[ColNr].Columns);

	SetSelectBuffer( &m_SelBuf );

}

int CMbox2::PrimeKeyOfSelectedRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 )
{
	struct VecBuf *Info;
	Info = ( struct VecBuf *) GetSelectedVector();
	*PrimeKey1	= Info->IFANR;
	*PrimeKey2	= Info->SATZNR;
	*Key3		= Info->A00PZN;
	return 0;
}

int CMbox2::PrimeKeyOfNextRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 )
{
	long lStatus;
	lStatus = GetNextSelect();
	if ( lStatus != 0 ) return -1;
	*PrimeKey1 = m_SelBuf.IFANR;
	*PrimeKey2 = m_SelBuf.SATZNR;
	*Key3      = m_SelBuf.A00PZN;
	return 0;
}

int CMbox2::PrimeKeyOfPrevRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 )
{
	long lStatus;
	lStatus = GetPrevSelect();
	if ( lStatus != 0 ) return -1;
	*PrimeKey1 = m_SelBuf.IFANR;
	*PrimeKey2 = m_SelBuf.SATZNR;
	*Key3      = m_SelBuf.A00PZN;
	return 0;
}


bool CMbox2::IsNumber( CString cStr )
{
	CString str;
	str = cStr;
	str.TrimLeft();
	str.TrimRight();
	if ( str.IsEmpty() ) return false;

	int i;
	i = 0;
	while ( i < str.GetLength( ) )
	{
		if ( !isdigit( (unsigned char)str.GetAt( i ) ) )
			return false;
		i++;
	}
	return true;
}

//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
// CMbox1

CMbox1::CMbox1()
{
}


CMbox1::~CMbox1()
{
	CloseCursor( );
}


CString CMbox1::InitSelect( CString SuchBegriff )
{
	CString sql;
	CString SuchB1;
	CString SuchB2;
	int iPos;

	// Parsen
	iPos = SuchBegriff.Find("\n");
	if ( iPos == -1 )
	{
		SuchB1 = SuchBegriff;	// IFANR
		SuchB2 = _T("");		// Matchcode
	}
	else
	{
		SuchB1 = SuchBegriff.Left(iPos);
		SuchB2 = SuchBegriff.Mid(iPos + 1);
	}

	SuchB1.TrimLeft();
	SuchB1.TrimRight();
	SuchB2.TrimLeft();
	SuchB2.TrimRight();
	
	sql  = "select unique IFANR,A00ANBNR,SORTIERNAME,ORT,PLZ from ZIFAART,";
	if ( SuchB2.IsEmpty() )
		sql += "outer ";
	sql += "HERSTEL";
	sql += " where HERSTELLER_NR=A00ANBNR";
	sql += " and IFANR=";
	sql += SuchB1;

//	if ( SuchB2.GetLength() > 0 && SuchB2.GetAt( 0 ) == '#' )
  	if ( IsNumber( SuchB2 ) ) 
	{
 		CString nr;
//		nr.Format("'%.5ld'", atol( SuchB2.Mid(1)));
		nr.Format("'%.5ld'", atol( SuchB2 ) );
		sql += " and A00ANBNR>=";
		sql += nr;
		sql += " order by IFANR,A00ANBNR";
	}
	else
	{
	    sql += " and SORTIERNAME matches '";
		sql += SuchB2;
		sql += "*'";
		sql += " order by SORTIERNAME";
	}

//	AfxMessageBox( sql );

	return sql;
}


void CMbox1::FillBuffer( CStringArray& s, void **VecPtr )
{
	if (VecPtr){}
	char str[12];

	sprintf( str, "%.8ld", m_SelBuf.A00ANBNR );

	s.SetSize( 4 );
	s[0] = str;
	s[0].TrimLeft();
	s[1] = m_SelBuf.SORTIERNAME;
	s[2] = m_SelBuf.PLZ;
	s[3] = m_SelBuf.ORT;
//	*VecPtr = NULL;
}


void CMbox1::InitSuchBox()
{
	ListColumns Fields[] =
	{
		HerNr,      _strdup(CResString::ex().getStrTblText(IDS_HERNR)),      60,   LVCFMT_LEFT, 1, // must be left aligned
		Matchcode,	_strdup(CResString::ex().getStrTblText(IDS_MATCHCODE)),	240,  LVCFMT_LEFT, 0, //40
		Plz,        _strdup(CResString::ex().getStrTblText(IDS_PLZ)),        60,   LVCFMT_LEFT, 0, //70
		Ort,        _strdup(CResString::ex().getStrTblText(IDS_ORT)),        340,  LVCFMT_LEFT, 0, //80
		-1        ,   "",             0,   0,			0
	};
 
	InitBox( PUFFER_ANZAHL, Fields );

	for (short ColNr = 0; ColNr < GetFieldCount(); ColNr++)
		free(Fields[ColNr].Columns);

	SetSelectBuffer( &m_SelBuf );
}

bool CMbox1::IsNumber( CString cStr )
{
	CString str;
	str = cStr;
	str.TrimLeft();
	str.TrimRight();
	if ( str.IsEmpty() ) return false;

	int i;
	i = 0;
	while ( i < str.GetLength( ) )
	{
		if ( !isdigit( (unsigned char)str.GetAt( i ) ) )
			return false;
		i++;
	}
	return true;
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////	


/////////////////////////////////////////////////////////////////////////////
// CArtikelIfa dialog


CArtikelIfa::CArtikelIfa(CWnd* pParent /*=NULL*/)
	: CDialogMultiLang(CArtikelIfa::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArtikelIfa)
	//}}AFX_DATA_INIT
	m_pView1 = NULL;
	m_pView2 = NULL;
	m_bWithoutViews = TRUE;
	m_bFirstInit = TRUE;
	MakeDialog();
}

CArtikelIfa::CArtikelIfa(CView* pView1, CView* pView2 ) // modeless constructor
    : CDialogMultiLang()
{
    m_pView1 = pView1;
    m_pView2 = pView2;
	if ( pView1 == NULL || pView2 == NULL )
		m_bWithoutViews = TRUE;
	else
		m_bWithoutViews = FALSE;
	m_bFirstInit = TRUE;
	MakeDialog();
}

BOOL CArtikelIfa::Create( int woher )	// create on modeless constuctor
{
	BOOL bOk = CDialogMultiLang::Create(CArtikelIfa::IDD);
	if ( bOk ) 
		ShowWindow( SW_SHOW );		
	else
		MsgBoxOK(CResString::ex().getStrTblText(IDS_IFA_CREATE_ERR) );
	m_nWoher = woher; 
	return bOk;
}


void CArtikelIfa::DoDataExchange(CDataExchange* pDX)
{
	CDialogMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelIfa)
	DDX_Control(pDX, IDC_PB_ARTIFA_COPY, m_cCOPY);
	DDX_Control(pDX, IDC_PB_ARTIFA_NEUGEN, m_cNEUGEN);
	DDX_Control(pDX, IDC_PB_ARTIFA_ARTPFL, m_cARTPFL);
	DDX_Control(pDX, IDC_PB_ARTIFA_ARTGEN, m_cARTGEN);
	DDX_Control(pDX, IDC_PB_ARTIFA_IFANEU, m_cIFANEU);
	DDX_Control(pDX, IDC_ED_ARTIFA_ARTSUCHB1, m_ARTSUCHB1);
	DDX_Control(pDX, IDC_ED_ARTIFA_ARTSUCHB2, m_ARTSUCHB2);
	DDX_Control(pDX, IDC_ED_ARTIFA_HERSTSUCHB, m_HERSTSUCHB);
	DDX_Control(pDX, IDC_LC_ARTIFA_BOX1, m_BOX1);
	DDX_Control(pDX, IDC_PB_ARTIFA_SUCHE1, m_SUCHE1);
	DDX_Control(pDX, IDC_PB_ARTIFA_VORBL1, m_VORBL1);
	DDX_Control(pDX, IDC_PB_ARTIFA_RUEBL1, m_RUEBL1);
	DDX_Control(pDX, IDC_LC_ARTIFA_BOX2, m_BOX2);
	DDX_Control(pDX, IDC_PB_ARTIFA_SUCHE2, m_SUCHE2);
	DDX_Control(pDX, IDC_PB_ARTIFA_VORBL2, m_VORBL2);
	DDX_Control(pDX, IDC_PB_ARTIFA_RUEBL2, m_RUEBL2);
	DDX_Control(pDX, IDC_CB_ARTIFA_IFANR, m_IFANR);
	DDX_Control(pDX, IDC_CB_ARTIFA_NBSATZ, m_NBSATZ);
	DDX_Control(pDX, IDC_CB_ARTIFA_AENART, m_AENART);
	DDX_Control(pDX, IDC_CB_ARTIFA_BEARBSTAT, m_BEARBSTAT);
	DDX_Control(pDX, IDOK, m_cIDOK);
	DDX_Control(pDX, IDCANCEL, m_cIDCANCEL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtikelIfa, CDialogMultiLang)
	//{{AFX_MSG_MAP(CArtikelIfa)
	ON_BN_CLICKED(IDC_PB_ARTIFA_SUCHE1, OnPbArtifaSuche1)
	ON_BN_CLICKED(IDC_PB_ARTIFA_VORBL1, OnPbArtifaVorbl1)
	ON_BN_CLICKED(IDC_PB_ARTIFA_RUEBL1, OnPbArtifaRuebl1)
	ON_BN_CLICKED(IDC_PB_ARTIFA_SUCHE2, OnPbArtifaSuche2)
	ON_BN_CLICKED(IDC_PB_ARTIFA_VORBL2, OnPbArtifaVorbl2)
	ON_BN_CLICKED(IDC_PB_ARTIFA_RUEBL2, OnPbArtifaRuebl2)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_NOTIFY(NM_DBLCLK, IDC_LC_ARTIFA_BOX1, OnDblclkLcArtifaBox1)
	ON_NOTIFY(NM_DBLCLK, IDC_LC_ARTIFA_BOX2, OnDblclkLcArtifaBox2)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LC_ARTIFA_BOX1, OnKeydownLcArtifaBox1)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LC_ARTIFA_BOX2, OnKeydownLcArtifaBox2)
	ON_BN_CLICKED(IDC_PB_ARTIFA_IFANEU, OnPbArtifaIfaneu)
	ON_BN_CLICKED(IDC_PB_ARTIFA_ARTGEN, OnPbArtifaArtgen)
	ON_BN_CLICKED(IDC_PB_ARTIFA_ARTPFL, OnPbArtifaArtpfl)
	ON_BN_CLICKED(IDC_PB_ARTIFA_NEUGEN, OnPbArtifaNeugen)
	ON_BN_CLICKED(IDC_PB_ARTIFA_COPY, OnPbArtifaCopy)
	ON_BN_CLICKED(IDC_PB_ARTIFA_DEFPA, OnPbArtifaDefpa)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////
// Suche Ueber F2

void CArtikelIfa::F2Suche1()
{
	OnPbArtifaSuche1();
}

void CArtikelIfa::F2Suche2()
{
	OnPbArtifaSuche2();
}

class CO_ARTIKELIFA_Com1 : public ChComBase
{
public:
	CO_ARTIKELIFA_Com1( CArtikelIfa* pView ) : ChComBase( pView ){};
	void DoIt( UINT nChar )
	{	
		if ( nChar == VK_F2 )
			((CArtikelIfa*)m_pWnd)->F2Suche1();
	}
};

class CO_ARTIKELIFA_Com2 : public ChComBase
{
public:
	CO_ARTIKELIFA_Com2( CArtikelIfa* pView ) : ChComBase( pView ){};
	void DoIt( UINT nChar )
	{	
		if ( nChar == VK_F2 )
			((CArtikelIfa*)m_pWnd)->F2Suche2();
	}
};

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelIfa::MakeDialog()
{
	m_dlg.InitDialog( m_SUCHE1 );
	m_dlg.InitDialog( m_VORBL1 );
	m_dlg.InitDialog( m_RUEBL1 );
	m_dlg.InitDialog( m_SUCHE2 );
	m_dlg.InitDialog( m_VORBL2 );
	m_dlg.InitDialog( m_RUEBL2 );
	m_dlg.InitDialog( m_AENART );
	m_dlg.InitDialog( m_NBSATZ );
	m_dlg.InitDialog( m_BEARBSTAT );
	m_dlg.InitDialog( m_IFANR );
	m_dlg.InitDialog( m_ARTSUCHB1 );
	m_dlg.InitDialog( m_ARTSUCHB2 );
	m_dlg.InitDialog( m_HERSTSUCHB );
/*
	char str[20];
	sprintf( str, "%s: %d", CResString::ex().getStrTblText(IDS_FIELDNUMBER), m_dlg.GetFieldNumber() );
	AfxMessageBox( str );
*/
}

void CArtikelIfa::InitPflege()
{

//	MakeDialog();	// hier nicht, sondern im Constructor
	m_BOX1.InitSuchBox();
	m_SUCHE1.SetMask( IDB_BM_SUCHE1, new CBitmap, NULL );
	m_VORBL1.SetMask( IDB_BM_VORBL1, new CBitmap, NULL );
	m_RUEBL1.SetMask( IDB_BM_RUEBL1, new CBitmap, NULL );

	m_BOX2.InitSuchBox();
	m_SUCHE2.SetMask( IDB_BM_SUCHE1, new CBitmap, NULL );
	m_VORBL2.SetMask( IDB_BM_VORBL1, new CBitmap, NULL );
	m_RUEBL2.SetMask( IDB_BM_RUEBL1, new CBitmap, NULL );

	// Scroll-Information
	m_BOX1.SetScrollInfo( ID_ARTIFA_VORBL1, ID_ARTIFA_RUEBL1, TRUE );
	m_BOX2.SetScrollInfo( ID_ARTIFA_VORBL2, ID_ARTIFA_RUEBL2, TRUE );

	// FullRowSelect
//	m_BOX1.SetFullRowSel( FALSE );
//	m_BOX2.SetFullRowSel( TRUE );
//	m_BOX1.m_bClientWidthSel = TRUE;
//	m_BOX2.m_bClientWidthSel = FALSE;

//	m_AENART.SetMask( "x10", &m_cAenart, 0 ); 
	m_AENART.SetMask( "x0231fg", &m_cAenart, 0 ); 
	m_BEARBSTAT.SetMask( "xFS", &m_cBearbstat, 0 ); 
	m_NBSATZ.SetMask( "x01234", &m_cNbsatz, 0 ); 
	m_IFANR.SetMask ( "A", &m_cIfanr, 0 ); 


	m_ARTSUCHB1.SetMask( ED_CHAR,
			             ED_UPPER,
				         m_cArtSuchb1,
					     L_ARTSUCHB1,
						 new ChMaskChar );
	m_ARTSUCHB1.SetCommandHandler( new CO_ARTIKELIFA_Com2( this ) );

	m_ARTSUCHB2.SetMask( ED_CHAR,
						 ED_UPPER,
	                     m_cArtSuchb2,
		                 L_ARTSUCHB2,
						 new ChMaskChar );
	m_ARTSUCHB2.SetCommandHandler( new CO_ARTIKELIFA_Com2( this ) );

	m_HERSTSUCHB.SetMask( ED_CHAR,
						  ED_UPPER,
	                      m_cHerstSuchb,
		                  L_HERSTSUCHB,
						  new ChMaskChar );
	m_HERSTSUCHB.SetCommandHandler( new CO_ARTIKELIFA_Com1( this ) );

//  m_dlg.EnableFields( TRUE );

	m_VORBL1.EnableWindow( FALSE );	
	m_RUEBL1.EnableWindow( FALSE );	

	m_VORBL2.EnableWindow( FALSE );	
	m_RUEBL2.EnableWindow( FALSE );	

	// Dialog aktivieren
 	m_dlg.SetDialog( TRUE );

	// Daten initialisiern
	m_cBearbstat = 'x';
	m_BEARBSTAT.p_SetInput();
	m_cAenart = 'x';
	m_AENART.p_SetInput();
	m_cNbsatz = 'x';
	m_NBSATZ.p_SetInput();

	// Benutzerrechte
	m_cARTPFL.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_ARTIKEL ) );
	m_cCOPY.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_IFA ) );
	m_cNEUGEN.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_IFA ) );
	m_cARTGEN.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_IFA ) );
	m_cIFANEU.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_IFA ) );
}

int CArtikelIfa::FillBoxIfaNr( CString &errmld )
{
	int i;
	int nStatus;
	char mask;

	m_IFANR.ResetContent( );
	i = 0;
	nStatus = 0;
	mask = 'A';
	while ( i < m_nIfaAnz && nStatus >= 0 )
	{
		m_IfaMask[i] = mask++;
		nStatus = m_IFANR.AddString( m_IfaDatum[i++] );
		if ( nStatus == CB_ERR )
			errmld = CResString::ex().getStrTblText(IDS_IFA_FILL_ERR);
		else if ( nStatus == CB_ERRSPACE )
			errmld = CResString::ex().getStrTblText(IDS_IFA_FILL_NOTALL);
	}
	m_IfaMask[i] = '\0';

	if ( nStatus >= 0 )
		return 0;
	else
		return 1;
}


BOOL CArtikelIfa::InitIfa() 
{
	BOOL bOk = TRUE;
	CString errmld;

	if ( m_bFirstInit )
	{
		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		m_nIfaAnz = SelectIfaNr( errmld );
		((CEkZdpApp*) AfxGetApp())->EndWaitAction();
		if ( m_nIfaAnz > 0 )
			m_bFirstInit = FALSE;
		else
			bOk = FALSE;
	}

	if ( m_nIfaAnz > 0 )
	{
		bOk = FillBoxIfaNr( errmld ) == 0;
	}

	if ( bOk )
	{
		m_IFANR.SetMask ( m_IfaMask, &m_cIfanr, 0 ); 

		m_dlg.DataExchangeFromBuffer();
	}
	else
	{
		MsgBoxOK( errmld );
	}

	return bOk; 
}


void CArtikelIfa::GoOn( int woher )
{
	BOOL bOk;
	int  mRichtung;
	bOk = m_BOX2.ActualSelect( mRichtung );
	ShowWindow( SW_SHOW );
	if ( bOk )
	{
		if ( mRichtung == 1 )			// vorgeblaettert
		{
			m_RUEBL2.EnableWindow( TRUE );	
		}
		else if ( mRichtung == -1 )		// rueckgeblaettert
		{
			m_VORBL2.EnableWindow( TRUE );	
		}
	}
	m_nWoher = woher; 
}

int CArtikelIfa::PrimeKeyOfSelectedRecord( long *PrimeKey1, long *PrimeKey2 ,
										   long *Key3 )
{ 
	return m_BOX2.PrimeKeyOfSelectedRecord( PrimeKey1, PrimeKey2, Key3 );
}

int CArtikelIfa::PrimeKeyOfNextRecord( long *PrimeKey1, long *PrimeKey2,
									   long *Key3 )
{
	return m_BOX2.PrimeKeyOfNextRecord( PrimeKey1, PrimeKey2, Key3 );
}

int CArtikelIfa::PrimeKeyOfPrevRecord( long *PrimeKey1, long *PrimeKey2,
									   long *Key3 )
{
	return m_BOX2.PrimeKeyOfPrevRecord( PrimeKey1, PrimeKey2, Key3 );
}



/////////////////////////////////////////////////////////////////////////////
// CArtikelIfa message handlers

BOOL CArtikelIfa::OnInitDialog() 
{
	CDialogMultiLang::OnInitDialog();

	// TODO: Add extra initialization here

	InitPflege();

	FillComboBox();

	if ( !InitIfa() )
	{
		if ( m_bWithoutViews )
			EndDialog( -1 );
	}

	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CArtikelIfa::OnCancel() 
{
	// TODO: Add extra cleanup here
	if ( m_bWithoutViews )
		CDialogMultiLang::OnCancel();
	else
	{
		m_pView1->SendMessage( ID_ARTIFA_END, IDCANCEL );	// IFA_View
//		m_pView2->SendMessage( ID_ARTIFA_END, IDCANCEL );	// Artikel_View
	}
}

void CArtikelIfa::OnOK() 
{
	// TODO: Add extra validation here
	CWnd *wnd = GetFocus();
/*
	if ( !(wnd == &m_BOX2 || wnd == &m_cIDOK ))
	{
		NextDlgCtrl();
		return;
	}
*/

	if ( wnd == &m_ARTSUCHB1 )
	{
		OnPbArtifaSuche2(); 
		return;
	}

	if ( wnd == &m_HERSTSUCHB )
	{
		OnPbArtifaSuche1();
		return;
	}

	if ( !(wnd == &m_BOX2 || wnd == &m_cIDOK ))
	{
		NextDlgCtrl();
		return;
	}

	m_dlg.DataExchangeToBuffer();
	if ( !m_BOX2.ItemChoise( ) )
		OnClose();
	else
	{		
		if ( m_bWithoutViews )
			CDialogMultiLang::OnOK();
		else
			m_pView1->SendMessage( ID_ARTIFA_END, IDOK ); // IFA_View
	}
}

void CArtikelIfa::OnPbArtifaArtpfl() 
{
	// TODO: Add your control notification handler code here
	m_dlg.DataExchangeToBuffer();
	if ( !m_BOX2.ItemChoise( ) )
		OnClose();
	else
	{		
		if ( m_bWithoutViews )
			CDialogMultiLang::OnOK();
		else
			m_pView2->SendMessage( ID_ARTIFA_END, IDOK ); // Artikel_View
	}
}


void CArtikelIfa::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	if ( m_bWithoutViews )
		CDialogMultiLang::OnClose();
	else
	{
//		m_pView1->SendMessage( ID_ARTIFA_END, IDCANCEL );	// IFA_View
		m_pView2->SendMessage( ID_ARTIFA_END, IDCANCEL );	// Artikel_View
	}
}

/////////////////////////////////////////////////
// ArtikelBox

void CArtikelIfa::OnPbArtifaSuche2() 
{
	// TODO: Add your control notification handler code here
	// Suchbegriff :  "Keys\nIFANR\nMatchcode\nHerstNum" 
	// Keys: xxx -> AENDERART STATUS NACHBEARBEITUNG		
	char str[15];
	CString suchb1;
	CString suchb2;
	int index;
	// Status und AenderKeys
	m_AENART.p_GetInput();
	m_NBSATZ.p_GetInput();
	m_BEARBSTAT.p_GetInput();
	sprintf( str, "%c%c%c", m_cAenart, m_cBearbstat, m_cNbsatz ); 
	suchb1 = str;
	suchb1 += '\n';
	// IfaNr
	m_IFANR.p_GetInput();
	index = (int)(m_cIfanr - 'A'); 
	sprintf( str, "%ld", m_IfaNummer[ index ] );
	suchb1 += str;
	// ArtikelMatchcode
	m_ARTSUCHB2.GetWindowText( suchb2 );
	suchb1 += '\n';
	suchb1 += suchb2;
	// HerstellerNr
	m_ARTSUCHB1.GetWindowText( suchb2 );
	suchb1 += '\n';
	suchb1 += suchb2;

// ((CMainFrame*)AfxGetMainWnd())->GetStatusBar()->PleaseWait();

	if ( m_BOX2.StartSelect( suchb1, WITH_SCROLL | WITH_HOLD ) )
		m_VORBL2.EnableWindow( TRUE );
	else
	{
		m_VORBL2.EnableWindow( FALSE );
		m_SUCHE2.SetFocus();
	}
	m_RUEBL2.EnableWindow( FALSE );
	
}

void CArtikelIfa::OnPbArtifaVorbl2() 
{
	// TODO: Add your control notification handler code here

	if ( m_BOX2.NextSelect() )  
		m_RUEBL2.EnableWindow( TRUE );
	else
		m_VORBL2.EnableWindow( FALSE );
}

void CArtikelIfa::OnPbArtifaRuebl2() 
{
	// TODO: Add your control notification handler code here
	if ( m_BOX2.PrevSelect() ) 
		m_VORBL2.EnableWindow( TRUE );
	else
		m_RUEBL2.EnableWindow( FALSE );	
}

void CArtikelIfa::OnDblclkLcArtifaBox2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR){}
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
//  Doppelklickk wie OnOK()
	if ( m_nWoher == 1 ) 
		OnOK();					// goto Ifa-Pflege
	else
		OnPbArtifaArtpfl();		// goto Artikel-Pflege
}

// Blaettertaste innerhalb der Listbox
void CArtikelIfa::OnKeydownLcArtifaBox2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;

	switch ( pLVKeyDow->wVKey )
	{
	case VK_NEXT:
		OnPbArtifaVorbl2();
		break;
	case VK_PRIOR:
		OnPbArtifaRuebl2();
		break;
	}
}

////////////////////////////////////////////////
// Herstellerbox

void CArtikelIfa::OnPbArtifaSuche1() 
{
	// TODO: Add your control notification handler code here
	char str[15];
	CString suchb1;
	CString suchb2;
	int index;
	// IfaNr
	m_IFANR.p_GetInput();
	index = (int)(m_cIfanr - 'A'); 
	sprintf( str, "%ld", m_IfaNummer[ index ] );
	// Matchcode
	m_HERSTSUCHB.GetWindowText( suchb2 );
	suchb1 = str;
	suchb1 += '\n';
	suchb1 += suchb2;

// ((CMainFrame*)AfxGetMainWnd())->GetStatusBar()->PleaseWait();

	if ( m_BOX1.StartSelect( suchb1, WITH_SCROLL | WITH_HOLD ) )
		m_VORBL1.EnableWindow( TRUE );
	else
	{
		m_VORBL1.EnableWindow( FALSE );
		m_SUCHE1.SetFocus();
	}
	m_RUEBL1.EnableWindow( FALSE );
	
}

void CArtikelIfa::OnPbArtifaVorbl1() 
{
	// TODO: Add your control notification handler code here
	if ( m_BOX1.NextSelect() )  
		m_RUEBL1.EnableWindow( TRUE );
	else
		m_VORBL1.EnableWindow( FALSE );	
}


void CArtikelIfa::OnPbArtifaRuebl1() 
{
	// TODO: Add your control notification handler code here
	if ( m_BOX1.PrevSelect() ) 
		m_VORBL1.EnableWindow( TRUE );
	else
		m_RUEBL1.EnableWindow( FALSE );		
}


void CArtikelIfa::OnDblclkLcArtifaBox1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR){}
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
	if ( m_BOX1.ItemChoise( FALSE ) )	// Hersteller angwaehlt
	{
		sprintf( m_cArtSuchb1, "%ld", atol( (LPCTSTR) m_BOX1.GetSelectedInfo() ) );
		m_ARTSUCHB1.p_SetInput();
	}
}

// Blaettertaste innerhalb der Listbox
void CArtikelIfa::OnKeydownLcArtifaBox1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;

	switch ( pLVKeyDow->wVKey )
	{
	case VK_NEXT:
		OnPbArtifaVorbl1();
		break;
	case VK_PRIOR:
		OnPbArtifaRuebl1();
		break;
	}
}

void CArtikelIfa::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}

int CArtikelIfa::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogMultiLang::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}


///////////////////////////////////////////////////
// IFA-Nummer selectieren

int CArtikelIfa::SelectIfaNr( CString &errmld ) 
{
	long s;
	int  fd;
	int  anz;

	long ifanr;
//	long ifadatum;

	s = SqlOpenCs( &fd,
//				   "select unique ifanr,ifadatum from ifa order by ifanr desc" );
					"select unique IFANR from ZIFAART order by IFANR desc" );	
	if ( s != 0 )
	{
		errmld = DynErrmld();
		return -1;
	}

//	s = SqlFetch( fd, 1, &ifanr, &ifadatum, NULL );
	s = SqlFetch( fd, 1, &ifanr, NULL );
	if ( s == 100 )
	{
		errmld = CResString::ex().getStrTblText(IDS_IFA_NO);
		SqlCloseCs( fd );
		return -1;
	}

	anz = 0;
/*
	do
	{
		ConvFromPhoDate ( m_IfaDatum[anz], ifadatum, "tt.mm.jjjj" );
		m_IfaNummer[anz] = ifanr;
		anz++;
		s = SqlFetch( fd, 1, &ifanr, &ifadatum, NULL );
	} while ( s == 0 && anz <= IFA_ANZ );
*/
/*
	do
	{
		ifadatum = ifanr/100;
		ConvFromPhoDate ( m_IfaDatum[anz], ifadatum, "tt.mm.jjjj" );
		char nr[10];
		sprintf( nr, " / %.2ld", ifanr%100 );
		strcat( m_IfaDatum[anz], nr );
		m_IfaNummer[anz] = ifanr;
		anz++;
		s = SqlFetch( fd, 1, &ifanr, NULL );
	} while ( s == 0 && anz <= IFA_ANZ );
*/
	do
	{
		char nr[20];
		if ( ifanr < 1000000 )
			sprintf( nr, "%.4ld / %.2ld", ifanr/100, ifanr%100 );
		else
			sprintf( nr, "%.4ld / %.2ld / %.2ld", 
			             ifanr/10000, (ifanr%10000)/100, ifanr%100 );
		strcpy( m_IfaDatum[anz], nr );
		m_IfaNummer[anz] = ifanr;
		anz++;
		s = SqlFetch( fd, 1, &ifanr, NULL );
	} while ( s == 0 && anz < IFA_ANZ );
	if ( s < 0 )
	{
		errmld = DynErrmld();
		SqlCloseCs( fd );
		return -1;
	}
	SqlCloseCs( fd );

	return anz;
}


/////////////////////////////////////////////////////////////////
// Neue IFA-Datei laden

// #define UEB_LNG (MAX_AENKEY*MAX_AENART*12)

#define UEB_LNG 400

long CArtikelIfa::GenIfaNeu( CString &errmld )
{
	long s;
	int anz;
	int  rcv_lng;
	char buf[UEB_LNG + 1];
/*
	char log_path[200];
*/
	CString cPfad;
	CStringArray DateiNamen;
	CGetIfaVerz gV;

	/* 0 = SatzartMode fuer Artikel */
	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	s = gV.GetIfaVerzeichnisse( "0", cPfad, DateiNamen, errmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();   	
	if ( s != 0 ) 
		return s;

	anz = static_cast<int>(DateiNamen.GetSize()); 
	if ( anz >= 1 )  // >=1: immer anzeigen; >1: nur anzeigen, wenn mehr als 1
	{
		CIfaFiles dlg( DateiNamen );
		if ( dlg.DoModal( ) != IDOK ) 
			return 47114711;
		anz = dlg.GetFileNumber();
	}
	else 
	{
		// diese Meldung kommt nie
		errmld = CResString::ex().getStrTblText(IDS_IFA_NO_CHANGE);
		return -1;
	}

	// Test, ob Hersteller bereits geladen: -1 Fehler, 0 bereits geladen, 1 nicht geladen 
	CString Errstr;
	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	s = gV.IfaSatzartBereitsGeladen( "1", DateiNamen[anz], Errstr );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();  
// 	if ( s != 0 )
 	if ( s == 1 )
	{
//		if ( MsgBoxYesNo( CResString::ex().getStrTblText(IDS_HERST_LADEN) ) == IDYES )		
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1172) );		
		return 47114711;
	}

	CGetUnixFiles gU;
	CString cDirec;

	s = gU.GetWWSDateiUnterVerz(cDirec, bin, errmld);

	if ( s != 0 )
		strcpy ( buf, errmld );
	else
	{
		sprintf( buf, "%szpiartik 1 %s %s %s", 
					cDirec.GetString(),
					((CEkZdpApp*) AfxGetApp())->GetDbaseName().GetString(),
					(cPfad + DateiNamen[anz]).GetString(),
					(cPfad + "idd").GetString());

/*	strcpy( buf, "zpiartik 1 " );   // Programmname + mode auf UnixSeite 
	strcat( buf, ((CEkZdpApp*) AfxGetApp())->GetDbaseName() );  
	strcat( buf, " " );
	strcat( buf, (LPCTSTR) cPfad );	
	strcat( buf, (LPCTSTR) DateiNamen[anz] );
	strcat( buf, " " );
	strcat( buf, (LPCTSTR) cPfad );	
	strcat( buf, "idd" ); */

		rcv_lng = UEB_LNG;

		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		s = UnxPipwSystem ( buf, "", buf, &rcv_lng );
		((CEkZdpApp*) AfxGetApp())->EndWaitAction();

		buf[rcv_lng] ='\0';

		if ( s < 0 || rcv_lng == 0 )
		{
			strcpy( buf, DynErrmld() );

			if (strlen(buf) == 0)
				strcpy( buf, CResString::ex().getStrTblText(IDS_STRING549) );

			s = 1;
		}

		if ( s == 1 )
		{
			errmld = buf;
			return -1;
		}
	}

	errmld = buf;  // AUCH OK_Nachricht ausgeben 

	if (s == 0)
	{
		// Protokoll erzeugen
		CString cIfaNr;
		cIfaNr.Format( "%ld", atol( buf ) ); // IfaNr an 1. Stelle in buf

		sprintf( buf, "%szpignart 3 %s %s %s", 
					cDirec.GetString(),
					((CEkZdpApp*) AfxGetApp())->GetDbaseName().GetString(),
					cIfaNr.GetString(),
					(cPfad + DateiNamen[anz]).GetString());

/*		strcpy( buf, "zpignart 3 " );		 // Programmname + mode auf UnixSeite 
		strcat( buf, ((CEkZdpApp*) AfxGetApp())->GetDbaseName() ); 
		strcat( buf, " " );
		strcat( buf, (LPCTSTR) cIfaNr );	
		strcat( buf, " " );
		strcat( buf, (LPCTSTR) cPfad );	
		strcat( buf, (LPCTSTR) DateiNamen[anz] ); */
	 
		rcv_lng = UEB_LNG;

		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		s = UnxPipwSystem ( buf, "", buf, &rcv_lng );
		((CEkZdpApp*) AfxGetApp())->EndWaitAction();

		buf[rcv_lng] ='\0';

		if ( s < 0 || rcv_lng == 0 )
		{
			strcpy( buf, DynErrmld() );

			if (strlen(buf) == 0)
				strcpy( buf, CResString::ex().getStrTblText(IDS_STRING549) );

			s = 1;
		}

		errmld += CResString::ex().getStrTblText(IDS_PROTOKOL1);

		errmld += buf;
	}

	return 0;
}


void CArtikelIfa::OnPbArtifaIfaneu() 
{
	// TODO: Add your control notification handler code here
	CString errmld;
	long lStatus;
	lStatus = GenIfaNeu(  errmld );
	if ( lStatus == 47114711 ) return;
//	Meldung immer ausgeben
//	if ( lStatus != 0 )
		MsgBoxOK( errmld );
	if ( lStatus != -1 )
	{
		m_bFirstInit = TRUE;
		if ( !InitIfa() )
			OnCancel();
	}
}


/////////////////////////////////////////////////////
// Artikel generieren

void CArtikelIfa::GeneriereArtikel( char *mode, long datum )
{
	CString errmld;
#define UEB_LNG1 250
	char buf[UEB_LNG1 + 1];
	CString cDirec;
	CString cDirec_bin;
	int  rcv_lng = UEB_LNG1;

	// IfaNr
	char str[20];
	m_IFANR.p_GetInput();
	int index = (int)(m_cIfanr - 'A'); 

	sprintf( str, "%ld", m_IfaNummer[ index ] );
	long ifanr = atol( str );

	char datstr[11];
	ConvFromPhoDate ( datstr, datum, "tt.mm.jjjj" );

	if ( *mode == '0' )
		errmld.Format( 
		CResString::ex().getStrTblText(IDS_IFA_ARTIKEL), 
			 ifanr/10000, ifanr/100%100, ifanr%100, datstr ); 
	else
		errmld.Format(
		 CResString::ex().getStrTblText(IDS_IFA_ARTIKEL_NEU), 
			 ifanr/10000, ifanr/100%100, ifanr%100, datstr ); 

	if ( MsgBoxYesNo( errmld ) != IDYES )	
		return;

	// Aufruf Serverprogramm UNIX
	long s;
	CGetUnixFiles gU;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	s = gU.GetWWSDateiUnterVerz( cDirec, ifa, errmld );

	if ( s != 0 )
	{
		MsgBoxOK( errmld );
		return;
	}
	
	s = gU.GetWWSDateiUnterVerz( cDirec_bin, bin, errmld );

	if ( s != 0 )
	{
		MsgBoxOK( errmld );
		return;
	}
	
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	char lf_verz[20];
	sprintf( lf_verz, "lf%.6ld", ifanr%1000000 );

	sprintf( buf, "%szpignart %s %s %ld p%s %s",
					cDirec_bin.GetString(),
                    mode, 
					((CEkZdpApp*) AfxGetApp())->GetDbaseName().GetString(),
					ifanr, 
					(cDirec + lf_verz).GetString(),
					datstr ); 

//	AfxMessageBox( buf );  return;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	s = UnxPipwSystem ( buf, "", buf, &rcv_lng );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	buf[rcv_lng] ='\0';

	if ( s < 0 || rcv_lng == 0 )
	{
		errmld = DynErrmld();
		s = 1;
	}
	else
		errmld = buf;

	if ( s == 0 && *mode == '0' )
	{
		errmld += CResString::ex().getStrTblText(IDS_DEFPA1);
		errmld += CResString::ex().getStrTblText(IDS_DEFPA2);
	}

	MsgBoxOK( errmld );

	if ( s == 1 )
	{
//		AfxMessageBox( buf );
	}	
	else
	{
		m_bFirstInit = TRUE;
		if ( !InitIfa() )
		{
			if ( *mode != '0' )	  // wegen Defpa druecken
				OnCancel();
			else
				m_IFANR.ResetContent( );
		}
	}
}

void CArtikelIfa::OnPbArtifaArtgen() 
{
	// TODO: Add your control notification handler code here

	CGuelDatum dlg;
	if ( dlg.DoModal() == IDOK )
	{
		long datum;
		datum = dlg.GetGuelDatum();
		GeneriereArtikel( "0", datum );	
	}
}


void CArtikelIfa::OnPbArtifaNeugen() 
{
	// TODO: Add your control notification handler code here

	CGuelDatum dlg;
	if ( dlg.DoModal() == IDOK )
	{
		long datum;
		datum = dlg.GetGuelDatum();
		GeneriereArtikel( "1", datum );	
	}
}

/////////////////////////////////////////////////////////////////
// IFA-Dateien von Client nach Server kopieren


int CArtikelIfa::IsIfaDateiname( CString Datei )
{
	Datei.MakeLower();
	if ( Datei == "liefer.ili" ) return 1; 
	if ( Datei.Left( 5 ) == "liefd" && Datei.Mid(8) == ".ild" ) return 2;
	return 0;
}


void CArtikelIfa::OnPbArtifaCopy() 
{
	int anz;
	int i;
	int status;
	CString cErrmld;
	CStringArray DateiNamen;
	CString UnxVerz;

	CGetUnixFiles gU;
	char WinVerz[12];
	char IfaText[36];
	char *Laufwerke;

	// unter Citrix liegt das Datacare-Verzeichnis auf Laufwerk H
	Laufwerke = "hdc";

	for (int j = 0; ; j++)
	{
		sprintf(WinVerz, "%c:\\ifa", Laufwerke[j]);
				
		if ( gU.GetFileOnWin( WinVerz, DateiNamen, cErrmld ) )
		{
			break;
		}

		// letztes Laufwerk wurde erfolglos durchsucht
		int len = static_cast<int>(strlen(Laufwerke));
		if ( j == (len - 1))
		{
			cErrmld.Format( CResString::ex().getStrTblText(IDS_STRING1032),
						Laufwerke ); 

			MsgBoxOK( cErrmld );
			return;
		}
	}

	sprintf(IfaText, CResString::ex().getStrTblText(IDS_DATA_LIST), WinVerz);

	anz = static_cast<int>(DateiNamen.GetSize());

	// hier: Dateien nur anzeigen
	CIfaFiles dlg( DateiNamen, _strdup(CResString::ex().getStrTblText(IDS_IFA_FILE)), IfaText );

	if ( dlg.DoModal( ) != IDOK ) 
		return;
	
	status = 0;
	cErrmld.Empty();
	for ( i = 0; i < anz; i++ )
	{
		if ( IsIfaDateiname( DateiNamen[i] ) == 0 && status <= 10 ) // max 10 anzeigen
		{
			cErrmld += DateiNamen[i] + "\n";
			status++;
		}
	}
	if ( status > 0 )
	{
		if ( status == 1 )
			cErrmld += CResString::ex().getStrTblText(IDS_IFA_NO_FILE);
		else
			cErrmld += CResString::ex().getStrTblText(IDS_IFA_NO_FILES);
		cErrmld += CResString::ex().getStrTblText(IDS_DELETE_FILE);
		if ( status > 1 )
			cErrmld += CResString::ex().getStrTblText(IDS_PLURAL);
		MsgBoxOK( cErrmld );
		return;
	}

	if ( gU.GetWWSDateiUnterVerz( UnxVerz, ifa, cErrmld ) != 0 )
	{
		MsgBoxOK( cErrmld );
		return;
	}

	UnxVerz += "lfakt/";

	status = 0;
	i = 0;

	while( i < anz && status == 0 )
	{
		if ( IsIfaDateiname( DateiNamen[i] ) != 0 )
		{
			CString VonDatei  = WinVerz;
			VonDatei += "\\" + DateiNamen[i];
			CString NachDatei = UnxVerz + DateiNamen[i];
			NachDatei.MakeLower();
//			AfxMessageBox( VonDatei + "\n" + NachDatei );
			status = gU.CopyFromWinToUnix( VonDatei, NachDatei, cErrmld ) ;
		}
		i++;
	}

	if ( status != 0 )
	{
		MsgBoxOK( cErrmld );
		return;
	}


	// Verzeichnis generieren
#define UEB_LNG2 300
	char buf[UEB_LNG2 + 1];
	char buf2[UEB_LNG + 1];
	int rcv_lng = UEB_LNG2;
	long s;

	CString cDirec;
	s = gU.GetWWSDateiUnterVerz(cDirec, bin, cErrmld);

	if ( s != 0 )
		strcpy ( buf, cErrmld );
	else
	{
		sprintf( buf2, "%szpifalf 2 c",
					  cDirec.GetString());

		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		s = UnxPipwSystem ( buf2, "", buf, &rcv_lng );
//		s = UnxPipwSystem( "zpifalf 2 c", "", buf, &rcv_lng );
		((CEkZdpApp*) AfxGetApp())->EndWaitAction();
		buf[rcv_lng] = '\0';

		if (  s < 0 || rcv_lng == 0 )
		{
			cErrmld = DynErrmld();
			MsgBoxOK( cErrmld );
			return;
		}
		
		if ( s != 0 )	// Dateien in lfakt loeschen
		{
			for ( i = 0; i < anz; i++ )
			{
				if ( IsIfaDateiname( DateiNamen[i] ) != 0 )
				{
					CString NachDatei = UnxVerz + DateiNamen[i];
					NachDatei.MakeLower();
	//				AfxMessageBox(  NachDatei );
					UnxUnlink( NachDatei );
				}
			}
		}
	}

	// Auch ok-Nachricht anzeigen
	MsgBoxOK( buf );
}

/////////////////////////////////////////////////////////////////
// sequentielle Datei DEFPA generieren und zum DKART SHICKEN

void CArtikelIfa::GeneriereDefpa( long datum )
{

	CString errmld;
#define UEB_LNG1 250
	char buf[UEB_LNG1 + 1];
	CString cDirec;
	CString cDirec_bin;
	int  rcv_lng = UEB_LNG1;
	char datstr[11];

	ConvFromPhoDate ( datstr, datum, "tt.mm.jjjj" );
	errmld.Format( CResString::ex().getStrTblText(IDS_DEFPA_CREATE), datstr ); 
	if ( MsgBoxYesNo( errmld ) != IDYES )	
		return;

	// Aufruf Serverprogramm UNIX
	long s;
	CGetUnixFiles gU;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	s = gU.GetWWSDateiUnterVerz( cDirec, ifa, errmld );

	if ( s != 0 )
	{
		MsgBoxOK( errmld );
		return;
	}

	s = gU.GetWWSDateiUnterVerz( cDirec_bin, bin, errmld );

	if ( s != 0 )
	{
		MsgBoxOK( errmld );
		return;
	}

	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
	
	sprintf( buf, "%szpdefpa 2 %s %svzdefpa/defpa %ld %ld", 
					cDirec_bin.GetString(),
					((CEkZdpApp*) AfxGetApp())->GetDbaseName().GetString(),
					cDirec.GetString(),
					datum, 
					datum ); 

//	AfxMessageBox( buf );  return;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	s = UnxPipwSystem ( buf, "", buf, &rcv_lng );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	buf[rcv_lng] ='\0';

	if ( s < 0 || rcv_lng == 0 )
	{
		errmld = DynErrmld();
		s = 1;
	}
	else
		errmld = buf;

//	AfxMessageBox( errmld );

	if ( s == 0 )
	{
		// Uebertragungs zu VSEZ auf Unix 
		long pid_sohn;
		sprintf( buf, "cp_defpa %svzdefpa/defpa", cDirec.GetString());
		s = UnxNwsystem ( buf, &pid_sohn );
		if ( s == 0  )
			errmld += CResString::ex().getStrTblText(IDS_VSEZ_COPY_ERR1);
		else
		{
			errmld += CResString::ex().getStrTblText(IDS_VSEZ_COPY_ERR2);
			errmld += DynErrmld();
		}
	}	

	MsgBoxOK( errmld );
}

void CArtikelIfa::OnPbArtifaDefpa() 
{
	CGuelDatum dlg;
	dlg.InitWerte( _strdup(CResString::ex().getStrTblText(IDS_DEFPA_CREATE2)), false );
	if ( dlg.DoModal() == IDOK )
	{
		long datum;
		datum = dlg.GetGuelDatum();
		GeneriereDefpa( datum );	
	}
}

void CArtikelIfa::FillComboBox()
{
	m_NBSATZ.ResetContent();
	m_AENART.ResetContent();
	m_BEARBSTAT.ResetContent();

	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10128));
	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10129));
	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10130));
	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10131));
	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10132));
	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10133));

	m_AENART.AddString(CResString::ex().getStrTblText(IDS_STRING10134));
	m_AENART.AddString(CResString::ex().getStrTblText(IDS_STRING10135));
	m_AENART.AddString(CResString::ex().getStrTblText(IDS_STRING10136));
	m_AENART.AddString(CResString::ex().getStrTblText(IDS_STRING10137));
	m_AENART.AddString(CResString::ex().getStrTblText(IDS_STRING10138));
	m_AENART.AddString(CResString::ex().getStrTblText(IDS_STRING10139));
	m_AENART.AddString(CResString::ex().getStrTblText(IDS_STRING10140));

	m_BEARBSTAT.AddString(CResString::ex().getStrTblText(IDS_STRING10134));
	m_BEARBSTAT.AddString(CResString::ex().getStrTblText(IDS_STRING10141));
	m_BEARBSTAT.AddString(CResString::ex().getStrTblText(IDS_STRING10142));
}
