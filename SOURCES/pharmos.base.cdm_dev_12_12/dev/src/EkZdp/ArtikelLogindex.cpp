// ArtikelLogindex.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtikelLogindex.h"
#include "IfaFiles.h"
#include "GetIfaVerz.h"
#include "GetUnixFiles.h"
#include "GuelDatum.h"
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
// CLIMBox2
/*
CLIMBox2::CLIMBox2()
{
}
*/

CLIMBox2::~CLIMBox2()
{
	CloseCursor( );
}


long CLIMBox2::GetTagesdatum()
{
	if ( m_tagesdatum == -1 )
		m_tagesdatum = ::Today();
	return m_tagesdatum;
}

CString CLIMBox2::InitSelect( CString SuchBegriff )
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
	// Suchbegriff :  "Keys\nDCNR\nMatchcode\nHerstNum" 
	// Keys: xxxx -> AENDERART STATUS NACHBEARBEITUNG IKSCODE	
	// Parsen
	iPos = SuchBegriff.Find("\n");

	SuchB0 = SuchBegriff.Left(iPos); 
	SuchB0.TrimLeft();
	SuchB0.TrimRight();

	SuchBRest = SuchBegriff.Mid(iPos + 1);

	iPos = SuchBRest.Find("\n");
	if ( iPos == -1 )
	{
		SuchB1 = SuchBRest;		// LINR
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

	sql  = "select LINR,SATZNR,LISTATUS,NBSTATUS,nvl(ARTICLE_CODE, rpad(PHAR, ";
	sql += lengthCode + ", ' ')),";
	sql += "DSCRD,QTY,QTYUD,ZAENDERUNG,CLIART.HERSTELLER_NR,SORTIERNAME,PHAR ";
	sql += "from CLIART, outer CARTICLECODES,outer HERSTEL";
	sql += " where HERSTEL.HERSTELLER_NR=CLIART.HERSTELLER_NR";
	sql += " and CARTICLECODES.ARTICLENO=PHAR";
	sql += " and PREFERRED_FLAG = 1 ";
	sql += " and CODE_TYPE in (SELECT CODE_TYPE FROM CCODETYPES WHERE ARTNR_SUBSTITUTE = 1) ";
	sql += " and LINR=";
	sql += SuchB1;

	if ( IsNumber( SuchB3 ) )
	{
		CString nr;
		if ( atol( SuchB3 ) > 0 )
		{
			nr.Format("%ld", atol( SuchB3) );
			sql += " and CLIART.HERSTELLER_NR=";
			sql += nr;
		}
		else
		{
			sql += " and CLIART.HERSTELLER_NR>=0";
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
			kenn[1] = '2';		// unvollständige Neuanlage
		else if ( ze == 'g' )	
			kenn[1] = '3';		// unvollständige Aenderung
		else
			kenn[1] = '1';

		sql += " and ZAENDERUNG=";
		sql += kenn;
	}

	if ( SuchB0.GetAt(1) != 'x' )
	{
		char kenn[4];
		strcpy ( kenn, "' '" );
		kenn[1] = SuchB0.GetAt(1);
		sql += " and LISTATUS=";
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

	if ( SuchB0.GetAt(3) == 'a' )
	{
		sql += " and SMCAT != '' ";
	}
	else if ( SuchB0.GetAt(3) != 'x' )
	{
		char kenn[4];
		strcpy ( kenn, "' '" );
		kenn[1] = SuchB0.GetAt(3);
		sql += " and SMCAT=";
		sql += kenn;
	}

	if ( mode == 1 )
	{
		sql += " order by LINR,CLIART.HERSTELLER_NR,PHAR";
		return sql;
	}

	if ( IsNumber( SuchB2 ) )
	{
		CString nr;
		nr.Format("%ld", atol( SuchB2 ) );
		sql += " and PHAR>=";
		sql += nr;
		sql += " order by LINR,PHAR";

		/* keine Suche nach ArticleCode, sondern nach dem Wert, der von Datacare geliefert wird !
        
		sql += " and lpad(trim(CARTICLECODES.ARTICLE_CODE),"+lengthCode+",'0') >= lpad('";
		sql += SuchB2 + "',"+lengthCode+",'0') ";
		*/
	}
	else
	{
		sql += " and DSCRD matches '";
		sql += SuchB2;
		sql += "*'";
		sql += " order by LINR,DSCRD";
	}

//	AfxMessageBox( sql );

	return sql;
}


void CLIMBox2::FillBuffer( CStringArray& s, void **VecPtr )
{
	s.SetSize( 11 );

	char str[12];

	s[0] = m_SelBuf.ARTIKEL_CODE;

	if ( m_SelBuf.ZAENDERUNG[0] == '1' )
	{
		/*if ( m_SelBuf.DC_DATUMGUELTIGAB <= GetTagesdatum() ) 
			s[1] = CResString::ex().getStrTblText(IDS_STRING951);
		else*/
			s[1] = CResString::ex().getStrTblText(IDS_STRING666);
	}
	else if ( m_SelBuf.ZAENDERUNG[0] == '2' )
		s[1] = "x";
	else
		s[1] = CResString::ex().getStrTblText(IDS_STRING667);

	s[2] = m_SelBuf.LISTATUS;		 //  LIstatus	
	
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

	s[6] = m_SelBuf.DSCRD;

	sprintf( str, "%.3f ", m_SelBuf.QTY );
	s[7]  = str;
	s[7] += m_SelBuf.QTYUD;
	s[7].TrimRight();

	sprintf( str, "%.5ld", m_SelBuf.HERSTELLER_NR );
	s[8] = str;
	s[8].TrimLeft();
	s[9] = m_SelBuf.SORTIERNAME;

	// ist in der IFA 8-stellig, warum auch immer 
	sprintf( str, "%.7ld", m_SelBuf.PHAR );
	s[10] = str;
	s[10].TrimLeft();

	m_VecBuf.LINR  = m_SelBuf.LINR;
	m_VecBuf.SATZNR = m_SelBuf.SATZNR;
	m_VecBuf.PHAR = m_SelBuf.PHAR;
	*VecPtr = &m_VecBuf;
}


void CLIMBox2::InitSuchBox()
{
	ListColumns Fields[] =			  
	{
		PHZNR,		_strdup(CResString::ex().getStrTblText(IDS_ARTNR)),     120,   LVCFMT_LEFT,  1, // must be left aligned
		EAENDER,	_strdup(CResString::ex().getStrTblText(IDS_EAENDER)),	21,   LVCFMT_LEFT,  0,	
		LISTAT,		_strdup(CResString::ex().getStrTblText(IDS_DCSTAT)),     21,   LVCFMT_LEFT,  0,	
		ENZWING,	_strdup(CResString::ex().getStrTblText(IDS_ENZWING)),	21,   LVCFMT_LEFT,  0,		
		EZWING,		_strdup(CResString::ex().getStrTblText(IDS_EZWING)),		21,   LVCFMT_LEFT,  0,				
		EPLAU,		_strdup(CResString::ex().getStrTblText(IDS_EPLAU)),		21,   LVCFMT_LEFT,  0,		
		ARTBEZ,		_strdup(CResString::ex().getStrTblText(IDS_ARTBEZ)),		230,  LVCFMT_LEFT,  0, //40
		EINHEIT,	_strdup(CResString::ex().getStrTblText(IDS_EINHEIT)),    80,   LVCFMT_RIGHT, 0, //40
		HERNR,		_strdup(CResString::ex().getStrTblText(IDS_HERNR)),      60,   LVCFMT_LEFT,  0,
		HERMC,		_strdup(CResString::ex().getStrTblText(IDS_MATCHCODE)),	210,  LVCFMT_LEFT,  0,
		-1        , NULL,         0,   0,			 0
	};
 
	InitBox( PUFFER_ANZAHL, Fields, sizeof( struct VecBuf )  );

	for (short ColNr = 0; ColNr < GetFieldCount(); ColNr++)
		free(Fields[ColNr].Columns);

	SetSelectBuffer( &m_SelBuf );

}

int CLIMBox2::PrimeKeyOfSelectedRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 )
{
	struct VecBuf *Info;
	Info = ( struct VecBuf *) GetSelectedVector();
	*PrimeKey1 = Info->LINR;
	*PrimeKey2 = Info->SATZNR;
	*Key3      = Info->PHAR;
	return 0;
}

int CLIMBox2::PrimeKeyOfNextRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 )
{
	long lStatus;
	lStatus = GetNextSelect();
	if ( lStatus != 0 ) return -1;
	*PrimeKey1 = m_SelBuf.LINR;
	*PrimeKey2 = m_SelBuf.SATZNR;
	*Key3      = m_SelBuf.PHAR;
	return 0;
}

int CLIMBox2::PrimeKeyOfPrevRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 )
{
	long lStatus;
	lStatus = GetPrevSelect();
	if ( lStatus != 0 ) return -1;
	*PrimeKey1 = m_SelBuf.LINR;
	*PrimeKey2 = m_SelBuf.SATZNR;
	*Key3      = m_SelBuf.PHAR;
	return 0;
}


bool CLIMBox2::IsNumber( CString cStr )
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
// CLIMBox1

CLIMBox1::CLIMBox1()
{
}


CLIMBox1::~CLIMBox1()
{
	CloseCursor( );
}


CString CLIMBox1::InitSelect( CString SuchBegriff )
{
	CString sql;
	CString SuchB1;
	CString SuchB2;
	int iPos;

	// Parsen
	iPos = SuchBegriff.Find("\n");
	if ( iPos == -1 )
	{
		SuchB1 = SuchBegriff;	// DCNR
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
	
	sql  = "select unique LINR,CLIART.HERSTELLER_NR,SORTIERNAME,ORT,PLZ from CLIART,";
	if ( SuchB2.IsEmpty() )
		sql += "outer ";
	sql += "HERSTEL";
	sql += " where HERSTEL.HERSTELLER_NR=CLIART.HERSTELLER_NR";
	sql += " and LINR=";
	sql += SuchB1;

  	if ( IsNumber( SuchB2 ) ) 
	{
 		CString nr;
		nr.Format("'%.5ld'", atol( SuchB2 ) );
		sql += " and CLIART.HERSTELLER_NR>=";
		sql += nr;
		sql += " order by LINR,CLIART.HERSTELLER_NR";
	}
	else
	{
	    sql += " and SORTIERNAME matches '";
		sql += SuchB2;
		sql += "*'";
		sql += " order by SORTIERNAME";
	}

	return sql;
}


void CLIMBox1::FillBuffer( CStringArray& s, void **)
{
	char str[12];

	sprintf( str, "%.5ld", m_SelBuf.HERSTELLER_NR );

	s.SetSize( 4 );
	s[0] = str;
	s[0].TrimLeft();
	s[1] = m_SelBuf.SORTIERNAME;
	s[2] = m_SelBuf.PLZ;
	s[3] = m_SelBuf.ORT;
//	*VecPtr = NULL;
}


void CLIMBox1::InitSuchBox()
{
	ListColumns Fields[] =
	{
		HerNr,        _strdup(CResString::ex().getStrTblText(IDS_HERNR)),       60,   LVCFMT_LEFT, 1, // must be left aligned
		Matchcode,    _strdup(CResString::ex().getStrTblText(IDS_MATCHCODE)),  240,   LVCFMT_LEFT, 0, //40
		Plz,          _strdup(CResString::ex().getStrTblText(IDS_PLZ)),         60,   LVCFMT_LEFT, 0, //70
		Ort,          _strdup(CResString::ex().getStrTblText(IDS_ORT)),        340,   LVCFMT_LEFT, 0, //80
		-1        ,   "",             0,   0,			0
	};
 
	InitBox( PUFFER_ANZAHL, Fields );

	for (short ColNr = 0; ColNr < GetFieldCount(); ColNr++)
		free(Fields[ColNr].Columns);

	SetSelectBuffer( &m_SelBuf );
}

bool CLIMBox1::IsNumber( CString cStr )
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
// CArtikelLogIndex dialog


CArtikelLogIndex::CArtikelLogIndex(CWnd* pParent /*=NULL*/)
	: CDialogMultiLang(CArtikelLogIndex::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArtikelLogIndex)
	//}}AFX_DATA_INIT
	m_pView1 = NULL;
	m_pView2 = NULL;
	m_bWithoutViews = TRUE;
	m_bFirstInit = TRUE;
	MakeDialog();
}

CArtikelLogIndex::CArtikelLogIndex(CView* pView1, CView* pView2 ) // modeless constructor
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

BOOL CArtikelLogIndex::Create( int woher )	// create on modeless constuctor
{
	BOOL bOk = CDialogMultiLang::Create(CArtikelLogIndex::IDD);
	if ( bOk ) 
		ShowWindow( SW_SHOW );		
	else
		MsgBoxOK(CResString::ex().getStrTblText(IDS_LOGINDEX_CREATE_ERR));
	m_nWoher = woher; 
	return bOk;
}


void CArtikelLogIndex::DoDataExchange(CDataExchange* pDX)
{
	CDialogMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelLogIndex)
	DDX_Control(pDX, IDC_PB_ARTLI_COPY, m_cCOPY);
	DDX_Control(pDX, IDC_PB_ARTLI_NEUGEN, m_cNEUGEN);
	DDX_Control(pDX, IDC_PB_ARTLI_NEUGEN_IKS, m_cNEUGEN_IKS);	
	DDX_Control(pDX, IDC_PB_ARTLI_ARTPFL, m_cARTPFL);
	DDX_Control(pDX, IDC_PB_ARTLI_ARTGEN, m_cARTGEN);
	DDX_Control(pDX, IDC_PB_ARTLI_ARTGEN_IKS, m_cARTGEN_IKS);
	DDX_Control(pDX, IDC_PB_ARTLI_LINEU, m_cLINEU);
	DDX_Control(pDX, IDC_ED_ARTLI_ARTSUCHB1, m_ARTSUCHB1);
	DDX_Control(pDX, IDC_ED_ARTLI_ARTSUCHB2, m_ARTSUCHB2);
	DDX_Control(pDX, IDC_ED_ARTLI_HERSTSUCHB, m_HERSTSUCHB);
	DDX_Control(pDX, IDC_LC_ARTLI_BOX1, m_BOX1);
	DDX_Control(pDX, IDC_PB_ARTLI_SUCHE1, m_SUCHE1);
	DDX_Control(pDX, IDC_PB_ARTLI_VORBL1, m_VORBL1);
	DDX_Control(pDX, IDC_PB_ARTLI_RUEBL1, m_RUEBL1);
	DDX_Control(pDX, IDC_LC_ARTLI_BOX2, m_BOX2);
	DDX_Control(pDX, IDC_PB_ARTLI_SUCHE2, m_SUCHE2);
	DDX_Control(pDX, IDC_PB_ARTLI_VORBL2, m_VORBL2);
	DDX_Control(pDX, IDC_PB_ARTLI_RUEBL2, m_RUEBL2);
	DDX_Control(pDX, IDC_CB_ARTLI_LINR, m_LINR);
	DDX_Control(pDX, IDC_CB_ARTLI_NBSATZ, m_NBSATZ);
	DDX_Control(pDX, IDC_CB_ARTLI_AENART, m_AENART);
	DDX_Control(pDX, IDC_CB_ARTLI_BEARBSTAT, m_BEARBSTAT);
	DDX_Control(pDX, IDC_CB_ARTLI_IKSCODE, m_IKSCODE);	
	DDX_Control(pDX, IDOK, m_cIDOK);
	DDX_Control(pDX, IDCANCEL, m_cIDCANCEL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtikelLogIndex, CDialogMultiLang)
	//{{AFX_MSG_MAP(CArtikelLogIndex)
	ON_BN_CLICKED(IDC_PB_ARTLI_SUCHE1, OnPbArtlogindexSuche1)
	ON_BN_CLICKED(IDC_PB_ARTLI_VORBL1, OnPbArtlogindexVorbl1)
	ON_BN_CLICKED(IDC_PB_ARTLI_RUEBL1, OnPbArtlogindexRuebl1)
	ON_BN_CLICKED(IDC_PB_ARTLI_SUCHE2, OnPbArtlogindexSuche2)
	ON_BN_CLICKED(IDC_PB_ARTLI_VORBL2, OnPbArtlogindexVorbl2)
	ON_BN_CLICKED(IDC_PB_ARTLI_RUEBL2, OnPbArtlogindexRuebl2)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_NOTIFY(NM_DBLCLK, IDC_LC_ARTLI_BOX1, OnDblclkLcArtlogindexBox1)
	ON_NOTIFY(NM_DBLCLK, IDC_LC_ARTLI_BOX2, OnDblclkLcArtlogindexBox2)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LC_ARTLI_BOX1, OnKeydownLcArtlogindexBox1)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LC_ARTLI_BOX2, OnKeydownLcArtlogindexBox2)
	ON_BN_CLICKED(IDC_PB_ARTLI_LINEU, OnPbArtlogindexLogindexneu)
	ON_BN_CLICKED(IDC_PB_ARTLI_ARTGEN, OnPbArtlogindexArtgen)
	ON_BN_CLICKED(IDC_PB_ARTLI_ARTGEN_IKS, OnPbArtlogindexArtgenIks)
	ON_BN_CLICKED(IDC_PB_ARTLI_ARTPFL, OnPbArtlogindexArtpfl)
	ON_BN_CLICKED(IDC_PB_ARTLI_NEUGEN, OnPbArtlogindexNeugen)
	ON_BN_CLICKED(IDC_PB_ARTLI_NEUGEN_IKS, OnPbArtlogindexNeugenIks)
	ON_BN_CLICKED(IDC_PB_ARTLI_COPY, OnPbArtlogindexCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////
// Suche Ueber F2

void CArtikelLogIndex::F2Suche1()
{
	OnPbArtlogindexSuche1();
}

void CArtikelLogIndex::F2Suche2()
{
	OnPbArtlogindexSuche2();
}

class CO_ArtikelLogIndex_Com1 : public ChComBase
{
public:
	CO_ArtikelLogIndex_Com1( CArtikelLogIndex* pView ) : ChComBase( pView ){};
	void DoIt( UINT nChar )
	{	
		if ( nChar == VK_F2 )
			((CArtikelLogIndex*)m_pWnd)->F2Suche1();
	}
};

class CO_ArtikelLogIndex_Com2 : public ChComBase
{
public:
	CO_ArtikelLogIndex_Com2( CArtikelLogIndex* pView ) : ChComBase( pView ){};
	void DoIt( UINT nChar )
	{	
		if ( nChar == VK_F2 )
			((CArtikelLogIndex*)m_pWnd)->F2Suche2();
	}
};

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelLogIndex::MakeDialog()
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
	m_dlg.InitDialog( m_IKSCODE );
	m_dlg.InitDialog( m_LINR );
	m_dlg.InitDialog( m_ARTSUCHB1 );
	m_dlg.InitDialog( m_ARTSUCHB2 );
	m_dlg.InitDialog( m_HERSTSUCHB );
/*
	char str[20];
	sprintf( str, "%s: %d", CResString::ex().getStrTblText(IDS_FIELDNUMBER), m_dlg.GetFieldNumber() );
	AfxMessageBox( str );
*/
}

void CArtikelLogIndex::InitPflege()
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
	m_AENART.SetMask( "x01fg", &m_cAenart, 0 ); 
	m_BEARBSTAT.SetMask( "xFS", &m_cBearbstat, 0 ); 
	m_IKSCODE.SetMask( "xaABCDE", &m_cIksCode, 0 ); 
	m_NBSATZ.SetMask( "x01234", &m_cNbsatz, 0 ); 
	m_LINR.SetMask ( "A", &m_cLogindexnr, 0 ); 


	m_ARTSUCHB1.SetMask( ED_CHAR,
			             ED_UPPER,
				         m_cArtSuchb1,
					     L_ARTSUCHB1,
						 new ChMaskChar );
	m_ARTSUCHB1.SetCommandHandler( new CO_ArtikelLogIndex_Com2( this ) );

	m_ARTSUCHB2.SetMask( ED_CHAR,
						 ED_UPPER,
	                     m_cArtSuchb2,
		                 L_ARTSUCHB2,
						 new ChMaskChar );
	m_ARTSUCHB2.SetCommandHandler( new CO_ArtikelLogIndex_Com2( this ) );

	m_HERSTSUCHB.SetMask( ED_CHAR,
						  ED_UPPER,
	                      m_cHerstSuchb,
		                  L_HERSTSUCHB,
						  new ChMaskChar );
	m_HERSTSUCHB.SetCommandHandler( new CO_ArtikelLogIndex_Com1( this ) );

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
	m_cIksCode = 'x';
	m_IKSCODE.p_SetInput();
	m_cAenart = 'x';
	m_AENART.p_SetInput();
	m_cNbsatz = 'x';
	m_NBSATZ.p_SetInput();

	// Benutzerrechte
	// m_cARTPFL.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_ARTIKEL ) );
	m_cCOPY.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_LOGINDEX ) );
	m_cNEUGEN.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_LOGINDEX ) );
	m_cNEUGEN_IKS.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_LOGINDEX ) );
	m_cARTGEN.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_LOGINDEX ) );
	m_cARTGEN_IKS.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_LOGINDEX ) );
	m_cLINEU.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_LOGINDEX ) );
}

int CArtikelLogIndex::FillBoxLogIndexNr( CString &errmld )
{
	int i;
	int nStatus;
	char mask;

	m_LINR.ResetContent( );
	i = 0;
	nStatus = 0;
	mask = 'A';
	while ( i < m_nLogindexAnz && nStatus >= 0 )
	{
		m_LogindexMask[i] = mask++;
		nStatus = m_LINR.AddString( m_LogindexDatum[i++] );
		if ( nStatus == CB_ERR )
			errmld = CResString::ex().getStrTblText(IDS_LOGINDEX_FILL_ERR);
		else if ( nStatus == CB_ERRSPACE )
			errmld = CResString::ex().getStrTblText(IDS_LOGINDEX_FILL_NOTALL);
	}
	m_LogindexMask[i] = '\0';

	if ( nStatus >= 0 )
		return 0;
	else
		return 1;
}


BOOL CArtikelLogIndex::InitLogIndex() 
{
	BOOL bOk = TRUE;
	CString errmld;

	if ( m_bFirstInit )
	{
		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		m_nLogindexAnz = SelectLogIndexNr( errmld );
		((CEkZdpApp*) AfxGetApp())->EndWaitAction();
		if ( m_nLogindexAnz > 0 )
			m_bFirstInit = FALSE;
		else
			bOk = FALSE;
	}

	if ( m_nLogindexAnz > 0 )
	{
		bOk = FillBoxLogIndexNr( errmld ) == 0;
	}

	if ( bOk )
	{
		m_LINR.SetMask ( m_LogindexMask, &m_cLogindexnr, 0 ); 

		m_dlg.DataExchangeFromBuffer();
	}
	else
	{
		MsgBoxOK( errmld );
	}

	return bOk; 
}


void CArtikelLogIndex::GoOn( int woher )
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

int CArtikelLogIndex::PrimeKeyOfSelectedRecord( long *PrimeKey1, long *PrimeKey2 ,
										   long *Key3 )
{ 
	return m_BOX2.PrimeKeyOfSelectedRecord( PrimeKey1, PrimeKey2, Key3 );
}

int CArtikelLogIndex::PrimeKeyOfNextRecord( long *PrimeKey1, long *PrimeKey2,
									   long *Key3 )
{
	return m_BOX2.PrimeKeyOfNextRecord( PrimeKey1, PrimeKey2, Key3 );
}

int CArtikelLogIndex::PrimeKeyOfPrevRecord( long *PrimeKey1, long *PrimeKey2,
									   long *Key3 )
{
	return m_BOX2.PrimeKeyOfPrevRecord( PrimeKey1, PrimeKey2, Key3 );
}



/////////////////////////////////////////////////////////////////////////////
// CArtikelDatacare message handlers

BOOL CArtikelLogIndex::OnInitDialog() 
{
	CDialogMultiLang::OnInitDialog();

	// TODO: Add extra initialization here

	InitPflege();

	FillComboBox();

	if ( !InitLogIndex() )
	{
		if ( m_bWithoutViews )
			EndDialog( -1 );
	}

	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CArtikelLogIndex::OnCancel() 
{
	// TODO: Add extra cleanup here
	if ( m_bWithoutViews )
		CDialogMultiLang::OnCancel();
	else
	{
		m_pView1->SendMessage( ID_ARTLOGINDEX_END, IDCANCEL );	// LogIndex_View
	}
}

void CArtikelLogIndex::OnOK() 
{
	// TODO: Add extra validation here
	CWnd *wnd = GetFocus();

	if ( wnd == &m_ARTSUCHB1 )
	{
		OnPbArtlogindexSuche2(); 
		return;
	}

	if ( wnd == &m_HERSTSUCHB )
	{
		OnPbArtlogindexSuche1();
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
			m_pView1->SendMessage( ID_ARTLOGINDEX_END, IDOK ); // LogIndex_View
	}
}

void CArtikelLogIndex::OnPbArtlogindexArtpfl() 
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
			m_pView2->SendMessage( ID_ARTLOGINDEX_END, IDOK ); // Artikel_View
	}
}


void CArtikelLogIndex::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	if ( m_bWithoutViews )
		CDialogMultiLang::OnClose();
	else
	{
		m_pView2->SendMessage( ID_ARTLOGINDEX_END, IDCANCEL );	// Artikel_View
	}
}

/////////////////////////////////////////////////
// ArtikelBox

void CArtikelLogIndex::OnPbArtlogindexSuche2() 
{
	// Suchbegriff :  "Keys\nLINR\nMatchcode\nHerstNum" 
	// Keys: xxxx -> AENDERART STATUS NACHBEARBEITUNG IKSCODE		
	char str[15];
	CString suchb1;
	CString suchb2;
	int index;
	// Status und AenderKeys
	m_AENART.p_GetInput();
	m_NBSATZ.p_GetInput();
	m_BEARBSTAT.p_GetInput();
	m_IKSCODE.p_GetInput(); 
	sprintf( str, "%c%c%c%c", m_cAenart, m_cBearbstat, m_cNbsatz, m_cIksCode ); 
	suchb1 = str;
	suchb1 += '\n';
	// LogindexNr
	m_LINR.p_GetInput();
	index = (int)(m_cLogindexnr - 'A'); 
	sprintf( str, "%ld", m_LogindexNummer[ index ] );
	suchb1 += str;
	// ArtikelMatchcode
	m_ARTSUCHB2.GetWindowText( suchb2 );
	suchb1 += '\n';
	suchb1 += suchb2;
	// HerstellerNr
	m_ARTSUCHB1.GetWindowText( suchb2 );
	suchb1 += '\n';
	suchb1 += suchb2;

	if ( m_BOX2.StartSelect( suchb1, WITH_SCROLL | WITH_HOLD ) )
		m_VORBL2.EnableWindow( TRUE );
	else
	{
		m_VORBL2.EnableWindow( FALSE );
		m_SUCHE2.SetFocus();
	}
	m_RUEBL2.EnableWindow( FALSE );
	
}

void CArtikelLogIndex::OnPbArtlogindexVorbl2() 
{
	// TODO: Add your control notification handler code here

	if ( m_BOX2.NextSelect() )  
		m_RUEBL2.EnableWindow( TRUE );
	else
		m_VORBL2.EnableWindow( FALSE );
}

void CArtikelLogIndex::OnPbArtlogindexRuebl2() 
{
	// TODO: Add your control notification handler code here
	if ( m_BOX2.PrevSelect() ) 
		m_VORBL2.EnableWindow( TRUE );
	else
		m_RUEBL2.EnableWindow( FALSE );	
}

void CArtikelLogIndex::OnDblclkLcArtlogindexBox2(NMHDR* , LRESULT* pResult) 
{
	*pResult = 0;
//  Doppelklickk wie OnOK()
	if ( m_nWoher == 1 ) 
		OnOK();					 // goto LogIndex-Pflege
	else
		OnPbArtlogindexArtpfl(); // goto Artikel-Pflege
}

// Blaettertaste innerhalb der Listbox
void CArtikelLogIndex::OnKeydownLcArtlogindexBox2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;

	switch ( pLVKeyDow->wVKey )
	{
	case VK_NEXT:
		OnPbArtlogindexVorbl2();
		break;
	case VK_PRIOR:
		OnPbArtlogindexRuebl2();
		break;
	}
}

////////////////////////////////////////////////
// Herstellerbox

void CArtikelLogIndex::OnPbArtlogindexSuche1() 
{
	// TODO: Add your control notification handler code here
	char str[15];
	CString suchb1;
	CString suchb2;
	int index;
	// DatacareNr
	m_LINR.p_GetInput();
	index = (int)(m_cLogindexnr - 'A'); 
	sprintf( str, "%ld", m_LogindexNummer[ index ] );
	// Matchcode
	m_HERSTSUCHB.GetWindowText( suchb2 );
	suchb1 = str;
	suchb1 += '\n';
	suchb1 += suchb2;

	if ( m_BOX1.StartSelect( suchb1, WITH_SCROLL | WITH_HOLD ) )
		m_VORBL1.EnableWindow( TRUE );
	else
	{
		m_VORBL1.EnableWindow( FALSE );
		m_SUCHE1.SetFocus();
	}
	m_RUEBL1.EnableWindow( FALSE );
	
}

void CArtikelLogIndex::OnPbArtlogindexVorbl1() 
{
	// TODO: Add your control notification handler code here
	if ( m_BOX1.NextSelect() )  
		m_RUEBL1.EnableWindow( TRUE );
	else
		m_VORBL1.EnableWindow( FALSE );	
}


void CArtikelLogIndex::OnPbArtlogindexRuebl1() 
{
	// TODO: Add your control notification handler code here
	if ( m_BOX1.PrevSelect() ) 
		m_VORBL1.EnableWindow( TRUE );
	else
		m_RUEBL1.EnableWindow( FALSE );		
}


void CArtikelLogIndex::OnDblclkLcArtlogindexBox1(NMHDR*, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
	if ( m_BOX1.ItemChoise( FALSE ) )	// Hersteller angwaehlt
	{
		sprintf( m_cArtSuchb1, "%ld", atol( (LPCTSTR) m_BOX1.GetSelectedInfo() ) );
		m_ARTSUCHB1.p_SetInput();
	}
}

// Blaettertaste innerhalb der Listbox
void CArtikelLogIndex::OnKeydownLcArtlogindexBox1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;

	switch ( pLVKeyDow->wVKey )
	{
	case VK_NEXT:
		OnPbArtlogindexVorbl1();
		break;
	case VK_PRIOR:
		OnPbArtlogindexRuebl1();
		break;
	}
}

void CArtikelLogIndex::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}


int CArtikelLogIndex::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogMultiLang::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}


///////////////////////////////////////////////////
// Datacare-Nummer selectieren

int CArtikelLogIndex::SelectLogIndexNr( CString &errmld ) 
{
	long s;
	int  fd;
	int  anz;

	long linr;

	s = SqlOpenCs( &fd, "select unique LINR from CLIART order by LINR desc" );	
	if ( s != 0 )
	{
		errmld = DynErrmld();
		return -1;
	}

	s = SqlFetch( fd, 1, &linr, NULL );
	if ( s == 100 )
	{
		errmld = CResString::ex().getStrTblText(IDS_LOGINDEX_NO);
		SqlCloseCs( fd );
		return -1;
	}

	anz = 0;

	do
	{
		char nr[20];
		if ( linr < 1000000 )
			sprintf( nr, "%.4ld / %.2ld", linr/100, linr%100 );
		else
			sprintf( nr, "%.4ld / %.2ld / %.2ld", 
			             linr/10000, (linr%10000)/100, linr%100 );

		strcpy( m_LogindexDatum[anz], nr );
		m_LogindexNummer[anz] = linr;
		anz++;
		s = SqlFetch( fd, 1, &linr, NULL );
	} while ( s == 0 && anz < LOGINDEX_ANZ );

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
// Neue Logindex-Datei laden

#define UEB_LNG 400

long CArtikelLogIndex::GenLogIndexNeu( CString &errmld )
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
	s = gV.GetLogIndexVerzeichnisse( "0", cPfad, DateiNamen, errmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();   	

	if ( s != 0 ) 
		return s;

	anz = static_cast<int>(DateiNamen.GetSize()); 
	if ( anz >= 1 )  // >=1: immer anzeigen; >1: nur anzeigen, wenn mehr als 1
	{
		CIfaFiles dlg( DateiNamen, _strdup(CResString::ex().getStrTblText(IDS_LOGINDEX_LIEF)),
				   _strdup(CResString::ex().getStrTblText(IDS_LOGINDEX_LIEF_LIST)) );
		if ( dlg.DoModal( ) != IDOK ) return 47114711;
		anz = dlg.GetFileNumber();
	}
	else 
	{
		// diese Meldung kommt nie
		errmld = CResString::ex().getStrTblText(IDS_LOGINDEX_NO_CHANGE);
		return -1;
	}

	CGetUnixFiles gU;
	CString cDirec;

	s = gU.GetWWSDateiUnterVerz(cDirec, bin, errmld);

	if ( s != 0 )
		strcpy ( buf, errmld );
	else
	{
		sprintf( buf, "%szpliartik 1 %s %s", 
					cDirec.GetString(),
					((CEkZdpApp*) AfxGetApp())->GetDbaseName().GetString(),
					(cPfad + DateiNamen[anz]).GetString());

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
		CString cLogIndexNr;
		cLogIndexNr.Format( "%ld", atol( buf ) ); // LogIndexNr an 1. Stelle in buf

		sprintf( buf, "%szplignart 3 %s %s %s", 
					cDirec.GetString(),
					((CEkZdpApp*) AfxGetApp())->GetDbaseName().GetString(),
					cLogIndexNr.GetString(),
					(cPfad + DateiNamen[anz]).GetString());

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

void CArtikelLogIndex::OnPbArtlogindexLogindexneu() 
{
	CString errmld;
	long lStatus;
	
	lStatus = GenLogIndexNeu(  errmld );
	
	if ( lStatus == 47114711 ) return;
//	Meldung immer ausgeben
//	if ( lStatus != 0 )
		MsgBoxOK( errmld );
	
	if ( lStatus != -1 )
	{
		m_bFirstInit = TRUE;
		if ( !InitLogIndex() )
			OnCancel();
	}
}


/////////////////////////////////////////////////////
// Artikel generieren

void CArtikelLogIndex::GeneriereArtikel( char *mode, long datum )
{
	CString errmld;
#define UEB_LNG1 250
	char buf[UEB_LNG1 + 1];
	CString cDirec;
	CString cDirec_bin;
	int  rcv_lng = UEB_LNG1;

	// LogIndexNr
	char str[20];
	m_LINR.p_GetInput();
	int index = (int)(m_cLogindexnr - 'A'); 

	sprintf( str, "%ld", m_LogindexNummer[ index ] );
	long linr = atol( str );

	char datstr[11];
	ConvFromPhoDate ( datstr, datum, "tt.mm.jjjj" );

	if ( *mode == '0' ) // 0 = alle Änderung / Neuanlagen mit / ohne IKS
		errmld.Format( 
		 CResString::ex().getStrTblText(IDS_LOGINDEX_ARTIKEL), 
			 linr/10000, linr/100%100, linr%100, datstr ); 
	else if ( *mode == '1' ) // 1 = alle Neuanlagen mit / ohne IKS
		errmld.Format(
		 CResString::ex().getStrTblText(IDS_LOGINDEX_ARTIKEL_NEU), 
			 linr/10000, linr/100%100, linr%100, datstr ); 
	else if ( *mode == '2' ) // 2 = alle Änderung / Neuanlagen mit IKS
		errmld.Format(
		 CResString::ex().getStrTblText(IDS_LOGINDEX_ARTIKEL_IKS), 
			 linr/10000, linr/100%100, linr%100, datstr ); 
	else if ( *mode == '4' ) // 4 = alle Neuanlagen mit IKS
		errmld.Format(
		 CResString::ex().getStrTblText(IDS_LOGINDEX_ARTIKEL_NEU_IKS), 
			 linr/10000, linr/100%100, linr%100, datstr ); 

	if ( MsgBoxYesNo( errmld ) != IDYES )	
		return;

	// Aufruf Serverprogramm UNIX
	long s;
	CGetUnixFiles gU;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	s = gU.GetWWSDateiUnterVerz( cDirec, logindex, errmld );

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
	sprintf( lf_verz, "lf%.6ld", linr%1000000 );

	sprintf( buf, "%szplignart %s %s %ld p%s %s",
					cDirec_bin.GetString(),
					mode, 
					((CEkZdpApp*) AfxGetApp())->GetDbaseName().GetString(),
					linr, 
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

	MsgBoxOK( errmld );

	if ( s == 1 )
	{
//		AfxMessageBox( buf );
	}	
	else
	{
		m_bFirstInit = TRUE;
		if ( !InitLogIndex() )
		{
/*			if ( *mode != '0' )	  // wegen Defpa druecken
				OnCancel();
			else */
				m_LINR.ResetContent( );
		}
	}
}

void CArtikelLogIndex::OnPbArtlogindexArtgen() 
{
	CGuelDatum dlg;
	if ( dlg.DoModal() == IDOK )
	{
		long datum;
		datum = dlg.GetGuelDatum();
		GeneriereArtikel( "0", datum );	
	}
}

void CArtikelLogIndex::OnPbArtlogindexArtgenIks() 
{
	CGuelDatum dlg;
	if ( dlg.DoModal() == IDOK )
	{
		long datum;
		datum = dlg.GetGuelDatum();
		GeneriereArtikel( "2", datum );	
	}
}

void CArtikelLogIndex::OnPbArtlogindexNeugen() 
{
	CGuelDatum dlg;
	if ( dlg.DoModal() == IDOK )
	{
		long datum;
		datum = dlg.GetGuelDatum();
		GeneriereArtikel( "1", datum );	
	}
}

void CArtikelLogIndex::OnPbArtlogindexNeugenIks() 
{
	CGuelDatum dlg;
	if ( dlg.DoModal() == IDOK )
	{
		long datum;
		datum = dlg.GetGuelDatum();
		GeneriereArtikel( "4", datum );	
	}
}

/////////////////////////////////////////////////////////////////
// Datacare-Dateien von Client nach Server kopieren 

int CArtikelLogIndex::IsLogIndexDateiname( CString Datei )
{
	Datei.MakeLower();
	
	return 1;
}

void CArtikelLogIndex::OnPbArtlogindexCopy() 
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
		sprintf(WinVerz, "%c:\\logindex", Laufwerke[j]);
				
		if ( gU.GetFileOnWin( WinVerz, DateiNamen, cErrmld ) )
		{
			break;
		}

		// letztes Laufwerk wurde erfolglos durchsucht
		int len = static_cast<int>(strlen(Laufwerke));
		if ( j == (len - 1))
		{
			cErrmld.Format( CResString::ex().getStrTblText(IDS_LOGINDEX_NO_LIST),
						Laufwerke ); 

			MsgBoxOK( cErrmld );
			return;
		}
	}

	sprintf(IfaText, CResString::ex().getStrTblText(IDS_DATA_LIST), WinVerz);

	anz = static_cast<int>(DateiNamen.GetSize());

	// hier: Dateien nur anzeigen
	CIfaFiles dlg( DateiNamen, _strdup(CResString::ex().getStrTblText(IDS_LOGINDEX_DATA)), IfaText );

	if ( dlg.DoModal( ) != IDOK ) return;
	
	status = 0;
	cErrmld.Empty();
	for ( i = 0; i < anz; i++ )
	{
		if ( IsLogIndexDateiname( DateiNamen[i] ) == 0 && status <= 10 ) // max 10 anzeigen
		{
			cErrmld += DateiNamen[i] + "\n";
			status++;
		}
	}
	if ( status > 0 )
	{
		if ( status == 1 )
			cErrmld += CResString::ex().getStrTblText(IDS_LOGINDEX_NO_FILE);
		else
			cErrmld += CResString::ex().getStrTblText(IDS_LOGINDEX_NO_FILES);
		cErrmld += CResString::ex().getStrTblText(IDS_DELETE_FILE);
		if ( status > 1 )
			cErrmld += CResString::ex().getStrTblText(IDS_PLURAL);
		MsgBoxOK( cErrmld );
		return;
	}

	if ( gU.GetWWSDateiUnterVerz( UnxVerz, logindex, cErrmld ) != 0 )
	{
		MsgBoxOK( cErrmld );
		return;
	}

	UnxVerz += "lfakt/";

	status = 0;
	i = 0;

	while( i < anz && status == 0 )
	{
		if ( IsLogIndexDateiname( DateiNamen[i] ) != 0 )
		{
			CString VonDatei  = WinVerz;
			VonDatei += "\\" + DateiNamen[i];
// Datei soll im UNIX immer den gleichen Dateinamen haben, damit vom Programm zplilf die Datumsinformation herausgelesen werden kann
//			CString NachDatei = UnxVerz + DateiNamen[i];
			CString NachDatei = UnxVerz;
			NachDatei += "logindex.csv";
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
		sprintf( buf2, "%szplilf 2 c",
					  cDirec.GetString());

		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		s = UnxPipwSystem ( buf2, "", buf, &rcv_lng );

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
				if ( IsLogIndexDateiname( DateiNamen[i] ) != 0 )
				{
	// Datei soll im UNIX immer den gleichen Dateinamen haben, damit vom Programm zpdatacarelf die Datumsinformation herausgelesen werden kann
	//				CString NachDatei = UnxVerz + DateiNamen[i];
					CString NachDatei = UnxVerz;
					NachDatei += "logindex.csv";
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

void CArtikelLogIndex::FillComboBox()
{
	m_NBSATZ.ResetContent();
	m_AENART.ResetContent();
	m_BEARBSTAT.ResetContent();
	m_IKSCODE.ResetContent();

	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10128));
	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10129));
	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10130));
	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10131));
	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10132));
	m_NBSATZ.AddString(CResString::ex().getStrTblText(IDS_STRING10133));

	m_AENART.AddString(CResString::ex().getStrTblText(IDS_STRING10134));
	m_AENART.AddString(CResString::ex().getStrTblText(IDS_STRING10135));
	m_AENART.AddString(CResString::ex().getStrTblText(IDS_STRING10138));
	m_AENART.AddString("unvollst. Neuanl.");
	m_AENART.AddString("unvollst. Änder.");

	m_BEARBSTAT.AddString(CResString::ex().getStrTblText(IDS_STRING10134));
	m_BEARBSTAT.AddString(CResString::ex().getStrTblText(IDS_STRING10141));
	m_BEARBSTAT.AddString(CResString::ex().getStrTblText(IDS_STRING10142));

	m_IKSCODE.AddString(CResString::ex().getStrTblText(IDS_STRING10134));
	m_IKSCODE.AddString("A-E");
	m_IKSCODE.AddString("A");
	m_IKSCODE.AddString("B");
	m_IKSCODE.AddString("C");
	m_IKSCODE.AddString("D");
	m_IKSCODE.AddString("E");
}
