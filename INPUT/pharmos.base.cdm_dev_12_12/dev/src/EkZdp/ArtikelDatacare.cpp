// ArtikelDatacare.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtikelDatacare.h"
#include "ArtikelDoc.h"
#include "AtcDoc.h"
#include "DatacareDoc.h"
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
#include <phxlib/EanTest.h>

#include "Shlobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
// CDCMBox2
/*
CDCMBox2::CDCMBox2()
{
}
*/

CDCMBox2::~CDCMBox2()
{
	CloseCursor( );
}


long CDCMBox2::GetTagesdatum()
{
	if ( m_tagesdatum == -1 )
		m_tagesdatum = ::Today();
	return m_tagesdatum;
}

CString CDCMBox2::InitSelect( CString SuchBegriff )
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
		SuchB1 = SuchBRest;		// DCNR
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

	sql  = "select DCNR,SATZNR,DC_DATUMGUELTIGAB,DCSTATUS,NBSTATUS,nvl(ARTICLE_CODE, rpad(DC_ARTIKEL_NR, ";
	sql += lengthCode + ", ' ')),";
	sql += "DC_ARTIKELTEXT,DC_EINH_MENGE,DC_EINH_EINHEIT,ZAENDERUNG,ZDCART.HERSTELLER_NR,SORTIERNAME,DC_ARTIKEL_NR ";
	sql += "from ZDCART, outer CARTICLECODES,outer HERSTEL";
	sql += " where HERSTEL.HERSTELLER_NR=ZDCART.HERSTELLER_NR";
	sql += " and CARTICLECODES.ARTICLENO=DC_ARTIKEL_NR";
	sql += " and PREFERRED_FLAG = 1 ";
	sql += " and CODE_TYPE in (SELECT CODE_TYPE FROM CCODETYPES WHERE ARTNR_SUBSTITUTE = 1) ";
	sql += " and DCNR=";
	sql += SuchB1;

	if ( IsNumber( SuchB3 ) )
	{
		CString nr;
		if ( atol( SuchB3 ) > 0 )
		{
			nr.Format("%ld", atol( SuchB3) );
			sql += " and ZDCART.HERSTELLER_NR=";
			sql += nr;
		}
		else
		{
			sql += " and ZDCART.HERSTELLER_NR>=0";
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
		sql += " and ZAENDERUNG=";
		sql += kenn;
		if ( ze == '2' || ze == '3' )
		{	
			char heute[14];
			sprintf( heute, "%ld", GetTagesdatum() );
			sql += " and DC_DATUMGUELTIGAB ";
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
		sql += " and DCSTATUS=";
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
		sql += " order by DCNR,ZDCART.HERSTELLER_NR,DC_ARTIKEL_NR";
		return sql;
	}

	if ( IsNumber( SuchB2 ) )
	{
		CString nr;
		nr.Format("%ld", atol( SuchB2 ) );
		sql += " and DC_ARTIKEL_NR>=";
		sql += nr;
		sql += " order by DCNR,DC_ARTIKEL_NR";

		/* keine Suche nach ArticleCode, sondern nach dem Wert, der von Datacare geliefert wird !
        
		sql += " and lpad(trim(CARTICLECODES.ARTICLE_CODE),"+lengthCode+",'0') >= lpad('";
		sql += SuchB2 + "',"+lengthCode+",'0') ";
		*/
	}
	else
	{
		sql += " and DC_ARTIKELTEXT matches '";
		sql += SuchB2;
		sql += "*'";
		sql += " order by DCNR,DC_ARTIKELTEXT";
	}

//	AfxMessageBox( sql );

	return sql;
}


void CDCMBox2::FillBuffer( CStringArray& s, void **VecPtr )
{
	s.SetSize( 11 );

	char str[12];

	s[0] = m_SelBuf.ARTIKEL_CODE;

	if ( m_SelBuf.ZAENDERUNG[0] == '1' )
	{
		if ( m_SelBuf.DC_DATUMGUELTIGAB <= GetTagesdatum() )  /* ????? */
			s[1] = CResString::ex().getStrTblText(IDS_STRING951);
		else
			s[1] = CResString::ex().getStrTblText(IDS_STRING666);
	}
	else if ( m_SelBuf.ZAENDERUNG[0] == '2' )
		s[1] = "x";
	else
		s[1] = CResString::ex().getStrTblText(IDS_STRING667);

	s[2] = m_SelBuf.DCSTATUS;		 //  Datacarestatus	
	
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

	s[6] = m_SelBuf.DC_ARTIKELTEXT;

	s[7]  = m_SelBuf.DC_EINH_MENGE;
	s[7] += m_SelBuf.DC_EINH_EINH;

	sprintf( str, "%.5ld", m_SelBuf.HERSTELLER_NR );
	s[8] = str;
	s[8].TrimLeft();
	s[9] = m_SelBuf.SORTIERNAME;

	// ist in der IFA 8-stellig, warum auch immer 
	sprintf( str, "%.7ld", m_SelBuf.DC_ARTIKEL_NR );
	s[10] = str;
	s[10].TrimLeft();

	m_VecBuf.DCNR  = m_SelBuf.DCNR;
	m_VecBuf.SATZNR = m_SelBuf.SATZNR;
	m_VecBuf.DC_ARTIKEL_NR = m_SelBuf.DC_ARTIKEL_NR;
	*VecPtr = &m_VecBuf;
}


void CDCMBox2::InitSuchBox()
{
	ListColumns Fields[] =			  
	{
		PHZNR,		_strdup(CResString::ex().getStrTblText(IDS_ARTNR)),     120,   LVCFMT_LEFT,  1, // must be left aligned
		EAENDER,	_strdup(CResString::ex().getStrTblText(IDS_EAENDER)),	21,   LVCFMT_LEFT,  0,	
		DCSTAT,		_strdup(CResString::ex().getStrTblText(IDS_DCSTAT)),     21,   LVCFMT_LEFT,  0,	
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

int CDCMBox2::PrimeKeyOfSelectedRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 )
{
	struct VecBuf *Info;
	Info = ( struct VecBuf *) GetSelectedVector();
	*PrimeKey1 = Info->DCNR;
	*PrimeKey2 = Info->SATZNR;
	*Key3      = Info->DC_ARTIKEL_NR;
	return 0;
}

int CDCMBox2::PrimeKeyOfNextRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 )
{
	long lStatus;
	lStatus = GetNextSelect();
	if ( lStatus != 0 ) return -1;
	*PrimeKey1 = m_SelBuf.DCNR;
	*PrimeKey2 = m_SelBuf.SATZNR;
	*Key3      = m_SelBuf.DC_ARTIKEL_NR;
	return 0;
}

int CDCMBox2::PrimeKeyOfPrevRecord( long *PrimeKey1, long *PrimeKey2, long *Key3 )
{
	long lStatus;
	lStatus = GetPrevSelect();
	if ( lStatus != 0 ) return -1;
	*PrimeKey1 = m_SelBuf.DCNR;
	*PrimeKey2 = m_SelBuf.SATZNR;
	*Key3      = m_SelBuf.DC_ARTIKEL_NR;
	return 0;
}


bool CDCMBox2::IsNumber( CString cStr )
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
// CDCMBox1

CDCMBox1::CDCMBox1()
{
}


CDCMBox1::~CDCMBox1()
{
	CloseCursor( );
}


CString CDCMBox1::InitSelect( CString SuchBegriff )
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
	
	sql  = "select unique DCNR,ZDCART.HERSTELLER_NR,SORTIERNAME,ORT,PLZ from ZDCART,";
	if ( SuchB2.IsEmpty() )
		sql += "outer ";
	sql += "HERSTEL";
	sql += " where HERSTEL.HERSTELLER_NR=ZDCART.HERSTELLER_NR";
	sql += " and DCNR=";
	sql += SuchB1;

//	if ( SuchB2.GetLength() > 0 && SuchB2.GetAt( 0 ) == '#' )
  	if ( IsNumber( SuchB2 ) ) 
	{
 		CString nr;
//		nr.Format("'%.5ld'", atol( SuchB2.Mid(1)));
		nr.Format("'%.5ld'", atol( SuchB2 ) );
		sql += " and ZDCART.HERSTELLER_NR>=";
		sql += nr;
		sql += " order by DCNR,ZDCART.HERSTELLER_NR";
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


void CDCMBox1::FillBuffer( CStringArray& s, void **VecPtr )
{
	if (VecPtr){}
	char str[12];

	// ist in der IFA 8-stellig, warum auch immer 
	sprintf( str, "%.5ld", m_SelBuf.HERSTELLER_NR );

	s.SetSize( 4 );
	s[0] = str;
	s[0].TrimLeft();
	s[1] = m_SelBuf.SORTIERNAME;
	s[2] = m_SelBuf.PLZ;
	s[3] = m_SelBuf.ORT;
//	*VecPtr = NULL;
}


void CDCMBox1::InitSuchBox()
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

bool CDCMBox1::IsNumber( CString cStr )
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
// CArtikelDatacare dialog


CArtikelDatacare::CArtikelDatacare(CWnd* pParent /*=NULL*/)
	: CDialogMultiLang(CArtikelDatacare::IDD, pParent)
{
	//{{AFX_DATA_INIT(CArtikelDatacare)
	//}}AFX_DATA_INIT
	m_pView1 = NULL;
	m_pView2 = NULL;
	m_bWithoutViews = TRUE;
	m_bFirstInit = TRUE;
	MakeDialog();
}

CArtikelDatacare::CArtikelDatacare(CView* pView1, CView* pView2 ) // modeless constructor
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

BOOL CArtikelDatacare::Create( int woher )	// create on modeless constuctor
{
	BOOL bOk = CDialogMultiLang::Create(CArtikelDatacare::IDD);
	if ( bOk ) 
		ShowWindow( SW_SHOW );		
	else
		MsgBoxOK(CResString::ex().getStrTblText(IDS_DATACARE_CREATE_ERR));
	m_nWoher = woher; 
	return bOk;
}


void CArtikelDatacare::DoDataExchange(CDataExchange* pDX)
{
	CDialogMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelDatacare)
	DDX_Control(pDX, IDC_PB_ARTDC_COPY, m_cCOPY);
	DDX_Control(pDX, IDC_PB_ARTDC_NEUGEN, m_cNEUGEN);
	DDX_Control(pDX, IDC_PB_ARTDC_ARTPFL, m_cARTPFL);
	DDX_Control(pDX, IDC_PB_ARTDC_ARTGEN, m_cARTGEN);
	DDX_Control(pDX, IDC_PB_ARTDC_DCNEU, m_cDCNEU);
	DDX_Control(pDX, IDC_PB_ARTDC_EAN, m_cDCEAN);
	DDX_Control(pDX, IDC_PB_ARTDC_DEMANDESTIMATION, m_cDCDEMEST);
	DDX_Control(pDX, IDC_ED_ARTDC_ARTSUCHB1, m_ARTSUCHB1);
	DDX_Control(pDX, IDC_ED_ARTDC_ARTSUCHB2, m_ARTSUCHB2);
	DDX_Control(pDX, IDC_ED_ARTDC_HERSTSUCHB, m_HERSTSUCHB);
	DDX_Control(pDX, IDC_LC_ARTDC_BOX1, m_BOX1);
	DDX_Control(pDX, IDC_PB_ARTDC_SUCHE1, m_SUCHE1);
	DDX_Control(pDX, IDC_PB_ARTDC_VORBL1, m_VORBL1);
	DDX_Control(pDX, IDC_PB_ARTDC_RUEBL1, m_RUEBL1);
	DDX_Control(pDX, IDC_LC_ARTDC_BOX2, m_BOX2);
	DDX_Control(pDX, IDC_PB_ARTDC_SUCHE2, m_SUCHE2);
	DDX_Control(pDX, IDC_PB_ARTDC_VORBL2, m_VORBL2);
	DDX_Control(pDX, IDC_PB_ARTDC_RUEBL2, m_RUEBL2);
	DDX_Control(pDX, IDC_CB_ARTDC_DCNR, m_DCNR);
	DDX_Control(pDX, IDC_CB_ARTDC_NBSATZ, m_NBSATZ);
	DDX_Control(pDX, IDC_CB_ARTDC_AENART, m_AENART);
	DDX_Control(pDX, IDC_CB_ARTDC_BEARBSTAT, m_BEARBSTAT);
	DDX_Control(pDX, IDOK, m_cIDOK);
	DDX_Control(pDX, IDCANCEL, m_cIDCANCEL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtikelDatacare, CDialogMultiLang)
	//{{AFX_MSG_MAP(CArtikelDatacare)
	ON_BN_CLICKED(IDC_PB_ARTDC_SUCHE1, OnPbArtdatacareSuche1)
	ON_BN_CLICKED(IDC_PB_ARTDC_VORBL1, OnPbArtdatacareVorbl1)
	ON_BN_CLICKED(IDC_PB_ARTDC_RUEBL1, OnPbArtdatacareRuebl1)
	ON_BN_CLICKED(IDC_PB_ARTDC_SUCHE2, OnPbArtdatacareSuche2)
	ON_BN_CLICKED(IDC_PB_ARTDC_VORBL2, OnPbArtdatacareVorbl2)
	ON_BN_CLICKED(IDC_PB_ARTDC_RUEBL2, OnPbArtdatacareRuebl2)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_NOTIFY(NM_DBLCLK, IDC_LC_ARTDC_BOX1, OnDblclkLcArtdatacareBox1)
	ON_NOTIFY(NM_DBLCLK, IDC_LC_ARTDC_BOX2, OnDblclkLcArtdatacareBox2)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LC_ARTDC_BOX1, OnKeydownLcArtdatacareBox1)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LC_ARTDC_BOX2, OnKeydownLcArtdatacareBox2)
	ON_BN_CLICKED(IDC_PB_ARTDC_DCNEU, OnPbArtdatacareDatacareneu)
	ON_BN_CLICKED(IDC_PB_ARTDC_EAN, OnPbArtdatacareEan)
	ON_BN_CLICKED(IDC_PB_ARTDC_DEMANDESTIMATION, OnPbArtdatacareDemEst)
	ON_BN_CLICKED(IDC_PB_ARTDC_ARTGEN, OnPbArtdatacareArtgen)
	ON_BN_CLICKED(IDC_PB_ARTDC_ARTPFL, OnPbArtdatacareArtpfl)
	ON_BN_CLICKED(IDC_PB_ARTDC_NEUGEN, OnPbArtdatacareNeugen)
	ON_BN_CLICKED(IDC_PB_ARTDC_COPY, OnPbArtdatacareCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////////
// Suche Ueber F2

void CArtikelDatacare::F2Suche1()
{
	OnPbArtdatacareSuche1();
}

void CArtikelDatacare::F2Suche2()
{
	OnPbArtdatacareSuche2();
}

class CO_ArtikelDatacare_Com1 : public ChComBase
{
public:
	CO_ArtikelDatacare_Com1( CArtikelDatacare* pView ) : ChComBase( pView ){};
	void DoIt( UINT nChar )
	{	
		if ( nChar == VK_F2 )
			((CArtikelDatacare*)m_pWnd)->F2Suche1();
	}
};

class CO_ArtikelDatacare_Com2 : public ChComBase
{
public:
	CO_ArtikelDatacare_Com2( CArtikelDatacare* pView ) : ChComBase( pView ){};
	void DoIt( UINT nChar )
	{	
		if ( nChar == VK_F2 )
			((CArtikelDatacare*)m_pWnd)->F2Suche2();
	}
};

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelDatacare::MakeDialog()
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
	m_dlg.InitDialog( m_DCNR );
	m_dlg.InitDialog( m_ARTSUCHB1 );
	m_dlg.InitDialog( m_ARTSUCHB2 );
	m_dlg.InitDialog( m_HERSTSUCHB );
/*
	char str[20];
	sprintf( str, "%s: %d", CResString::ex().getStrTblText(IDS_FIELDNUMBER), m_dlg.GetFieldNumber() );
	AfxMessageBox( str );
*/
}

void CArtikelDatacare::InitPflege()
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
	m_DCNR.SetMask ( "A", &m_cDatacarenr, 0 ); 


	m_ARTSUCHB1.SetMask( ED_CHAR,
			             ED_UPPER,
				         m_cArtSuchb1,
					     L_ARTSUCHB1,
						 new ChMaskChar );
	m_ARTSUCHB1.SetCommandHandler( new CO_ArtikelDatacare_Com2( this ) );

	m_ARTSUCHB2.SetMask( ED_CHAR,
						 ED_UPPER,
	                     m_cArtSuchb2,
		                 L_ARTSUCHB2,
						 new ChMaskChar );
	m_ARTSUCHB2.SetCommandHandler( new CO_ArtikelDatacare_Com2( this ) );

	m_HERSTSUCHB.SetMask( ED_CHAR,
						  ED_UPPER,
	                      m_cHerstSuchb,
		                  L_HERSTSUCHB,
						  new ChMaskChar );
	m_HERSTSUCHB.SetCommandHandler( new CO_ArtikelDatacare_Com1( this ) );

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
	// m_cARTPFL.EnableWindow( ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_ARTIKEL ) );

}

int CArtikelDatacare::FillBoxDatacareNr( CString &errmld )
{
	int i;
	int nStatus;
	char mask;

	m_DCNR.ResetContent( );
	i = 0;
	nStatus = 0;
	mask = 'A';
	while ( i < m_nDatacareAnz && nStatus >= 0 )
	{
		m_DatacareMask[i] = mask++;
		nStatus = m_DCNR.AddString( m_DatacareDatum[i++] );
		if ( nStatus == CB_ERR )
			errmld = CResString::ex().getStrTblText(IDS_DATACARE_FILL_ERR);
		else if ( nStatus == CB_ERRSPACE )
			errmld = CResString::ex().getStrTblText(IDS_DATACARE_FILL_NOTALL);
	}
	m_DatacareMask[i] = '\0';

	if ( nStatus >= 0 )
		return 0;
	else
		return 1;
}


BOOL CArtikelDatacare::InitDatacare() 
{
	BOOL bOk = TRUE;
	CString errmld;

	if ( m_bFirstInit )
	{
		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		m_nDatacareAnz = SelectDatacareNr( errmld );
		((CEkZdpApp*) AfxGetApp())->EndWaitAction();
		if ( m_nDatacareAnz > 0 )
			m_bFirstInit = FALSE;
		else
			bOk = FALSE;
	}

	if ( m_nDatacareAnz > 0 )
	{
		bOk = FillBoxDatacareNr( errmld ) == 0;
	}

	if ( bOk )
	{
		m_DCNR.SetMask ( m_DatacareMask, &m_cDatacarenr, 0 ); 

		m_dlg.DataExchangeFromBuffer();
	}
	else
	{
		MsgBoxOK( errmld );
	}

	return bOk; 
}


void CArtikelDatacare::GoOn( int woher )
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

int CArtikelDatacare::PrimeKeyOfSelectedRecord( long *PrimeKey1, long *PrimeKey2 ,
										   long *Key3 )
{ 
	return m_BOX2.PrimeKeyOfSelectedRecord( PrimeKey1, PrimeKey2, Key3 );
}

int CArtikelDatacare::PrimeKeyOfNextRecord( long *PrimeKey1, long *PrimeKey2,
									   long *Key3 )
{
	return m_BOX2.PrimeKeyOfNextRecord( PrimeKey1, PrimeKey2, Key3 );
}

int CArtikelDatacare::PrimeKeyOfPrevRecord( long *PrimeKey1, long *PrimeKey2,
									   long *Key3 )
{
	return m_BOX2.PrimeKeyOfPrevRecord( PrimeKey1, PrimeKey2, Key3 );
}



/////////////////////////////////////////////////////////////////////////////
// CArtikelDatacare message handlers

BOOL CArtikelDatacare::OnInitDialog() 
{
	CDialogMultiLang::OnInitDialog();

	// TODO: Add extra initialization here

	InitPflege();

	FillComboBox();

	if ( !InitDatacare() )
	{
		if ( m_bWithoutViews )
			EndDialog( -1 );
	}

	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CArtikelDatacare::OnCancel() 
{
	// TODO: Add extra cleanup here
	if ( m_bWithoutViews )
		CDialogMultiLang::OnCancel();
	else
	{
		m_pView1->SendMessage( ID_ARTDATACARE_END, IDCANCEL );	// Datacare_View
//		m_pView2->SendMessage( ID_ARTDATACARE_END, IDCANCEL );	// Artikel_View
	}
}

void CArtikelDatacare::OnOK() 
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
		OnPbArtdatacareSuche2(); 
		return;
	}

	if ( wnd == &m_HERSTSUCHB )
	{
		OnPbArtdatacareSuche1();
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
			m_pView1->SendMessage( ID_ARTDATACARE_END, IDOK ); // Datacare_View
	}
}

void CArtikelDatacare::OnPbArtdatacareArtpfl() 
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
			m_pView2->SendMessage( ID_ARTDATACARE_END, IDOK ); // Artikel_View
	}
}


void CArtikelDatacare::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	if ( m_bWithoutViews )
		CDialogMultiLang::OnClose();
	else
	{
//		m_pView1->SendMessage( ID_ARTDATACARE_END, IDCANCEL );	// Datacare_View
		m_pView2->SendMessage( ID_ARTDATACARE_END, IDCANCEL );	// Artikel_View
	}
}

/////////////////////////////////////////////////
// ArtikelBox

void CArtikelDatacare::OnPbArtdatacareSuche2() 
{
	// TODO: Add your control notification handler code here
	// Suchbegriff :  "Keys\nDCNR\nMatchcode\nHerstNum" 
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
	// DatacareNr
	m_DCNR.p_GetInput();
	index = (int)(m_cDatacarenr - 'A'); 
	sprintf( str, "%ld", m_DatacareNummer[ index ] );
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

void CArtikelDatacare::OnPbArtdatacareVorbl2() 
{
	// TODO: Add your control notification handler code here

	if ( m_BOX2.NextSelect() )  
		m_RUEBL2.EnableWindow( TRUE );
	else
		m_VORBL2.EnableWindow( FALSE );
}

void CArtikelDatacare::OnPbArtdatacareRuebl2() 
{
	// TODO: Add your control notification handler code here
	if ( m_BOX2.PrevSelect() ) 
		m_VORBL2.EnableWindow( TRUE );
	else
		m_RUEBL2.EnableWindow( FALSE );	
}

void CArtikelDatacare::OnDblclkLcArtdatacareBox2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR){}
	*pResult = 0;
//  Doppelklickk wie OnOK()
	if ( m_nWoher == 1 ) 
		OnOK();					 // goto Datacare-Pflege
	else
		OnPbArtdatacareArtpfl(); // goto Artikel-Pflege
}

// Blaettertaste innerhalb der Listbox
void CArtikelDatacare::OnKeydownLcArtdatacareBox2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;

	switch ( pLVKeyDow->wVKey )
	{
	case VK_NEXT:
		OnPbArtdatacareVorbl2();
		break;
	case VK_PRIOR:
		OnPbArtdatacareRuebl2();
		break;
	}
}

////////////////////////////////////////////////
// Herstellerbox

void CArtikelDatacare::OnPbArtdatacareSuche1() 
{
	// TODO: Add your control notification handler code here
	char str[15];
	CString suchb1;
	CString suchb2;
	int index;
	// DatacareNr
	m_DCNR.p_GetInput();
	index = (int)(m_cDatacarenr - 'A'); 
	sprintf( str, "%ld", m_DatacareNummer[ index ] );
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

void CArtikelDatacare::OnPbArtdatacareVorbl1() 
{
	// TODO: Add your control notification handler code here
	if ( m_BOX1.NextSelect() )  
		m_RUEBL1.EnableWindow( TRUE );
	else
		m_VORBL1.EnableWindow( FALSE );	
}


void CArtikelDatacare::OnPbArtdatacareRuebl1() 
{
	// TODO: Add your control notification handler code here
	if ( m_BOX1.PrevSelect() ) 
		m_VORBL1.EnableWindow( TRUE );
	else
		m_RUEBL1.EnableWindow( FALSE );		
}


void CArtikelDatacare::OnDblclkLcArtdatacareBox1(NMHDR* pNMHDR, LRESULT* pResult) 
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
void CArtikelDatacare::OnKeydownLcArtdatacareBox1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;

	switch ( pLVKeyDow->wVKey )
	{
	case VK_NEXT:
		OnPbArtdatacareVorbl1();
		break;
	case VK_PRIOR:
		OnPbArtdatacareRuebl1();
		break;
	}
}


void CArtikelDatacare::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}


int CArtikelDatacare::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialogMultiLang::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}


///////////////////////////////////////////////////
// Datacare-Nummer selectieren

int CArtikelDatacare::SelectDatacareNr( CString &errmld ) 
{
	long s;
	int  fd;
	int  anz;

	long dcnr;

	s = SqlOpenCs( &fd, "select unique DCNR from ZDCART order by DCNR desc" );	
	if ( s != 0 )
	{
		errmld = DynErrmld();
		return -1;
	}

	s = SqlFetch( fd, 1, &dcnr, NULL );
	if ( s == 100 )
	{
		errmld = CResString::ex().getStrTblText(IDS_DATACARE_NO);
		SqlCloseCs( fd );
		return -1;
	}

	anz = 0;
/*
	do
	{
		ConvFromPhoDate ( m_DatacareDatum[anz], DatacareDatum, "tt.mm.jjjj" );
		m_DatacareNummer[anz] = dcnr;
		anz++;
		s = SqlFetch( fd, 1, &dcnr, &DatacareDatum, NULL );
	} while ( s == 0 && anz <= DATACARE_ANZ );
*/
/*
	do
	{
		DatacareDatum = dcnr/100;
		ConvFromPhoDate ( m_DatacareDatum[anz], DatacareDatum, "tt.mm.jjjj" );
		char nr[10];
		sprintf( nr, " / %.2ld", dcnr%100 );
		strcat( m_DatacareDatum[anz], nr );
		m_DatacareNummer[anz] = dcnr;
		anz++;
		s = SqlFetch( fd, 1, &dcnr, NULL );
	} while ( s == 0 && anz <= DATACARE_ANZ );
*/
	do
	{
		char nr[20];
		if ( dcnr < 1000000 )
			sprintf( nr, "%.4ld / %.2ld", dcnr/100, dcnr%100 );
		else
			sprintf( nr, "%.4ld / %.2ld / %.2ld", 
			             dcnr/10000, (dcnr%10000)/100, dcnr%100 );

		strcpy( m_DatacareDatum[anz], nr );
		m_DatacareNummer[anz] = dcnr;
		anz++;
		s = SqlFetch( fd, 1, &dcnr, NULL );
	} while ( s == 0 && anz < DATACARE_ANZ );

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
// Neue Datacare-Datei laden

// #define UEB_LNG (MAX_AENKEY*MAX_AENART*12)

#define UEB_LNG 400

long CArtikelDatacare::GenDatacareNeu( CString &errmld )
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
	s = gV.GetDatacareVerzeichnisse( "0", cPfad, DateiNamen, errmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();   	

	if ( s != 0 ) 
		return s;

	anz = static_cast<int>(DateiNamen.GetSize()); 
	if ( anz >= 1 )  // >=1: immer anzeigen; >1: nur anzeigen, wenn mehr als 1
	{
		CIfaFiles dlg( DateiNamen, _strdup(CResString::ex().getStrTblText(IDS_DATACARE_LIEF)),
				   _strdup(CResString::ex().getStrTblText(IDS_DATACARE_LIEF_LIST)) );
		if ( dlg.DoModal( ) != IDOK ) return 47114711;
		anz = dlg.GetFileNumber();
	}
	else 
	{
		// diese Meldung kommt nie
		errmld = CResString::ex().getStrTblText(IDS_DATACARE_NO_CHANGE);
		return -1;
	}

	CGetUnixFiles gU;
	CString cDirec;

	s = gU.GetWWSDateiUnterVerz(cDirec, bin, errmld);

	if ( s != 0 )
		strcpy ( buf, errmld );
	else
	{
		sprintf( buf, "%szpdcartik 1 %s %s", 
					cDirec.GetString(),
					((CEkZdpApp*) AfxGetApp())->GetDbaseName().GetString(),
					(cPfad + DateiNamen[anz]).GetString());  

/*	strcpy( buf, "zpdcartik 1 " );   // Programmname + mode auf UnixSeite 
	strcat( buf, ((CEkZdpApp*) AfxGetApp())->GetDbaseName() ); 
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
		CString cDatacareNr;
		cDatacareNr.Format( "%ld", atol( buf ) ); // DatacareNr an 1. Stelle in buf

		sprintf( buf, "%szpdcgnart 3 %s %s %s", 
					cDirec.GetString(),
					((CEkZdpApp*) AfxGetApp())->GetDbaseName().GetString(),
					cDatacareNr.GetString(),
					(cPfad + DateiNamen[anz]).GetString() );  

/*		strcpy( buf, "zpdcgnart 3 " );		 // Programmname + mode auf UnixSeite 
		strcat( buf, ((CEkZdpApp*) AfxGetApp())->GetDbaseName() );  
		strcat( buf, " " );
		strcat( buf, (LPCTSTR) cDatacareNr );	
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

void CArtikelDatacare::processAsmFile(CStdioFile * stdiofile)
{
	CString errmld;
	long lStatus_zartwg;
	long lStatus_zartaustria;
	char mld [200] = {};

	CString line; 
	bool isHeaderLine = true;
	int iDcNr = 0;

	int iCntChange = 0;
	int iCntDelete = 0;
	
	short artZdkwir = 13; // E
	CArtikelDoc artDoc; // alle notwendigen DB- Funktionen sind bereits dort vorhanden
	artDoc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
	artDoc.SetTagesdatum(::Today());

	CString wgr;
	CString qty;
				
	if (artDoc.GetBufferDesc_Zartwg(errmld)		!= 0 || 
		artDoc.GetBufferDesc_Zartaustria(errmld)!= 0 || 
		artDoc.GetBufferDesc_Zartikel(errmld)	!= 0 || 
		artDoc.GetBufferDesc_Zapflege(errmld)	!= 0 )
	{
		MsgBoxOK(errmld);
		return;
	}

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();

// --- Schleife über alle Zeilen im Datenfile ---
	while( stdiofile->ReadString( line ) ) 
	{ 
		if (isHeaderLine == true) // Kopfzeile im Datenfile
		{
			isHeaderLine = false;
			if ( line.Left(5) != "ARTSM" )
			{
				MsgBoxOK("Die Kopfzeile muss mit 'ARTSM' beginnen!");				
				return;
			}

			iDcNr = atoi(line.Mid(29, 8));

			if (iDcNr < 20100000 || iDcNr > 20999999)
			{
				MsgBoxOK("Datum in der Kopfzeile ist nicht pausibel!");				
				return;
			}
		}
		else // Datenzeilen:
		{
			artDoc.m_Buf.zartikel.ARTIKEL_NR = atoi(line.Left(7)); // PZN aus DC-File
			
			if ( 0 != artDoc.ReadRecord_Zartikel(errmld) ) // nix zu tun, wenn wir den Artikel nicht kennen!
				continue;

			lStatus_zartwg = artDoc.ReadRecord_Zartwg(artZdkwir, errmld); // Suche in tabelle zartwg via artikel_nr, art E
			lStatus_zartaustria = artDoc.ReadRecord_Zartaustria(errmld); 

			if ( (lStatus_zartwg != 0 && lStatus_zartwg != 100) || (lStatus_zartaustria != 0 && lStatus_zartaustria != 100) )
			{
				MsgBoxOK(errmld);
				return;
			}
			else
			{
				artDoc.m_BufOld.zartwg[artZdkwir] = artDoc.m_Buf.zartwg[artZdkwir]; // im Doc nicht implizit!
				artDoc.m_BufOld.zartaustria = artDoc.m_Buf.zartaustria; // im Doc nicht implizit!
			}

			
			wgr = line.Mid(7, 5);
			wgr.Trim();
			// leading zeros
			while( wgr.GetLength() < 5 ){
				wgr.Insert(0, '0');
			}

			strcpy(artDoc.m_Buf.zartwg[artZdkwir].WARENGRUPPE, wgr); 

			qty = line.Mid(18, 11);
			qty.Insert(4, '.');
			artDoc.m_Buf.zartaustria.INGREDIENTQTY = atof(qty); 
			
			if (line.Mid(30, 1) == "L")
			{
				if (lStatus_zartwg == 100)
					continue;
				else
				{
					if (strcmp(artDoc.m_BufOld.zartwg[artZdkwir].WARENGRUPPE, artDoc.m_Buf.zartwg[artZdkwir].WARENGRUPPE) == 0)
					{
						if (artDoc.DeleteRecord_Zartwg(artZdkwir, errmld) != 0)
						{
							MsgBoxOK(errmld);
							return;
						}
						else
						{
							++iCntDelete;
							artDoc.StoreRecord_Zapflege	( ::Today(), errmld );
						}
					}
				}
			}
			else
			{
				if (strcmp(artDoc.m_BufOld.zartwg[artZdkwir].WARENGRUPPE, artDoc.m_Buf.zartwg[artZdkwir].WARENGRUPPE) != 0)
				{
					if (artDoc.StoreRecord_Zartwg(artZdkwir, errmld) != 0)
					{
						MsgBoxOK(errmld);
						return;
					}
					else
					{
						++iCntChange;
						artDoc.StoreRecord_Zapflege	( ::Today(), errmld );
					}
				}

				if (artDoc.m_BufOld.zartaustria.INGREDIENTQTY != artDoc.m_Buf.zartaustria.INGREDIENTQTY)
				{
					if (artDoc.StoreRecord_Zartaustria(errmld) != 0)
					{
						MsgBoxOK(errmld);
						return;
					}
					else
					{
						++iCntChange;
						artDoc.StoreRecord_Zapflege	( ::Today(), errmld );
					}
				}
			}

			if ( FdTransact( mld ) != 0 )
			{
				MsgBoxOK(mld);
				return;
			}
		} // Ende Datenzeile
	} // Ende Datei

	stdiofile->Close(); 

	CloseOneBufferDesc( artDoc.m_Fd_Zartwg );
	CloseOneBufferDesc( artDoc.m_Fd_Zartaustria );
	CloseOneBufferDesc( artDoc.m_Fd_Zapflege );
	CloseOneBufferDesc( artDoc.m_Fd_Zartikel );

	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	// Status- Message an User
	errmld.Format("Zuordnungen PZN - Wirkstoff / Inhaltsstoffmenge erfolgreich geladen:\n   %ld Wirkstoffe bzw. Inhaltsstoffmengen wurden verändert,\n   "
						"%ld Wirkstoffzuordnungen wurden gelöscht.",
						iCntChange, iCntDelete);
	MsgBoxOK(errmld);
}

void CArtikelDatacare::processKlgFile(CStdioFile * stdiofile)
{
	CString errmld;
	long lStatus;

	CString line; 
	bool isHeaderLine = true;
	int iDcNr = 0;

	int iCntChange = 0;
	int iCntDelete = 0;

	CAtcDoc atcDoc; // alle notwendigen DB- Funktionen sind bereits dort vorhanden
	atcDoc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
				
	if (atcDoc.GetBufferDesc(errmld)	!= 0 )
	{
		MsgBoxOK(errmld);
		return;
	}

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();

// --- Schleife über alle Zeilen im Datenfile ---
	while( stdiofile->ReadString( line ) ) 
	{ 
		if (isHeaderLine == true) // Kopfzeile im Datenfile
		{
			isHeaderLine = false;
			if ( line.Left(9) != "KLGRUPPEN" )
			{
				MsgBoxOK("Die Kopfzeile muss mit 'KLGRUPPEN' beginnen!");				
				return;
			}

			iDcNr = atoi(line.Mid(29, 8));

			if (iDcNr < 20100000 || iDcNr > 20999999)
			{
				MsgBoxOK("Datum in der Kopfzeile ist nicht pausibel!");				
				return;
			}
		}
		else // Datenzeilen:
		{
			if (line.Left(6) != "ATCSIS")
				continue;

			// skip leading Q as this is no official ATC- code, but only showing veterinary products ...
			if (line.Mid(10,1) == "Q")
				strcpy(atcDoc.m_Buf.CODE_ATC, line.Mid(11,9).Trim());
			else
				strcpy(atcDoc.m_Buf.CODE_ATC, line.Mid(10,10).Trim());

			lStatus = atcDoc.ReadRecord(errmld);

			if ( lStatus != 0 && lStatus != 100 )
			{
				MsgBoxOK(errmld);
				return;
			}

			strcpy(atcDoc.m_Buf.NAME_ATC, line.Mid(20, 80).MakeUpper()); 
						
			if (line.Mid(100, 1) == "L")
			{
				if (lStatus == 100)
					continue;
				else
				{
					if (atcDoc.DeleteRecord(errmld) != 0)
					{
						MsgBoxOK(errmld);
						return;
					}
					else
					{
						++iCntDelete;
					}
				}
			}
			else
			{
				if (strncmp(atcDoc.m_BufOld.NAME_ATC, atcDoc.m_Buf.NAME_ATC, 80) != 0)
				{
					if (atcDoc.StoreRecord(errmld) != 0)
					{
						MsgBoxOK(errmld);
						return;
					}
					else
					{
						++iCntChange;
					}
				}
			}
		}
	}

	stdiofile->Close(); 

	atcDoc.FreeBufferDesc(  );

	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	// Status- Message an User
	errmld.Format("ATC- Stamm erfolgreich geladen:\n   %ld ATC-Codes wurden verändert / neu angelegt,\n   "
						"%ld ATC-Codes wurden gelöscht.",
						iCntChange, iCntDelete);

	MsgBoxOK(errmld);
}

void CArtikelDatacare::processAklFile(CStdioFile * stdiofile)
{
	CString errmld;
	long lStatus;
	char mld [200] = {};

	CString line; 
	bool isHeaderLine = true;
	int iDcNr = 0;

	int iCntChange = 0;
	int iCntDelete = 0;
	
	short codeType_Atc = 2 - 1; // 1 is added in doc implicitly again!
	CArtikelDoc artDoc; // alle notwendigen DB- Funktionen sind bereits dort vorhanden
	artDoc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
	artDoc.SetTagesdatum(::Today());
				
	if (artDoc.GetBufferDesc_Carticlecodes(errmld)	!= 0 || 
		artDoc.GetBufferDesc_Zartikel(errmld)		!= 0 || 
		artDoc.GetBufferDesc_Zpznpflege(errmld)		!= 0 )
	{
		MsgBoxOK(errmld);
		return;
	}

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();

// --- Schleife über alle Zeilen im Datenfile ---
	while( stdiofile->ReadString( line ) ) 
	{ 
		if (isHeaderLine == true) // Kopfzeile im Datenfile
		{
			isHeaderLine = false;
			if ( line.Left(5) != "ARTKL" )
			{
				MsgBoxOK("Die Kopfzeile muss mit 'ARTKL' beginnen!");				
				return;
			}

			iDcNr = atoi(line.Mid(29, 8));

			if (iDcNr < 20100000 || iDcNr > 20999999)
			{
				MsgBoxOK("Datum in der Kopfzeile ist nicht pausibel!");				
				return;
			}
		}
		else // Datenzeilen:
		{
			if (line.Mid(7, 6) != "ATCSIS")
				continue;

			artDoc.m_Buf.zartikel.ARTIKEL_NR = atoi(line.Left(7)); // PZN aus DC-File

			if ( 0 != artDoc.ReadRecord_Zartikel(errmld) ) // nix zu tun, wenn wir den Artikel nicht kennen!
				continue;

			lStatus = artDoc.ReadRecord_Carticlecodes(codeType_Atc, errmld); // Suche in tabelle carticlecodes via artikel_nr, code_type 2
			
			if ( lStatus != 0 && lStatus != 100 )
			{
				MsgBoxOK(errmld);
				return;
			}
			else
			{
				artDoc.m_BufOld.carticlecodes[codeType_Atc] = artDoc.m_Buf.carticlecodes[codeType_Atc]; // im Doc nicht implizit!
			}

			// skip leading Q as this is no official ATC- code, but only showing veterinary products ...
			if (line.Mid(17,1) == "Q")
				strcpy(artDoc.m_Buf.carticlecodes[codeType_Atc].ARTICLE_CODE, line.Mid(18, 9)); 
			else
				strcpy(artDoc.m_Buf.carticlecodes[codeType_Atc].ARTICLE_CODE, line.Mid(17, 10)); 

			if (line.Mid(27, 1) == "L")
			{
				if (lStatus == 100)
					continue;
				else
				{
					if (strncmp(artDoc.m_BufOld.carticlecodes[codeType_Atc].ARTICLE_CODE, artDoc.m_Buf.carticlecodes[codeType_Atc].ARTICLE_CODE, 9) == 0)
					{
						if (artDoc.DeleteRecord_Carticlecodes(codeType_Atc, errmld) != 0)
						{
							MsgBoxOK(errmld);
							return;
						}
						else
						{
							++iCntDelete;
							artDoc.StoreRecord_Zpznpflege	( ::Today(), "34"	, errmld );
						}
					}
				}
			}
			else
			{
				if (strncmp(artDoc.m_BufOld.carticlecodes[codeType_Atc].ARTICLE_CODE, artDoc.m_Buf.carticlecodes[codeType_Atc].ARTICLE_CODE, 9) != 0)
				{
					if (artDoc.StoreRecord_Carticlecodes(codeType_Atc, errmld) != 0)
					{
						MsgBoxOK(errmld);
						return;
					}
					else
					{
						++iCntChange;
						artDoc.StoreRecord_Zpznpflege	( ::Today(), "34"	, errmld );
					}
				}
			}

			if ( FdTransact( mld ) != 0 )
			{
				MsgBoxOK(mld);
				return;
			}
		} // Ende Datenzeile
	} // Ende Datei

	stdiofile->Close(); 

	CloseOneBufferDesc( artDoc.m_Fd_Carticlecodes );
	CloseOneBufferDesc( artDoc.m_Fd_Zpznpflege );
	CloseOneBufferDesc( artDoc.m_Fd_Zartikel );

	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	// Status- Message an User
	errmld.Format("Zuordnungen PZN - ATC erfolgreich geladen:\n   %ld ATC-Codes wurden verändert / neu angelegt,\n   "
						"%ld ATC-Codes wurden gelöscht.",
						iCntChange, iCntDelete);
	MsgBoxOK(errmld);
}

void CArtikelDatacare::OnPbArtdatacareDemEst()
{
	// Datacare- Neuanlagen des zueghörigen Tages müssen bereits geladen sein, so dass die zugehörigen Suchtmitteldaten auch hinterlegt werden können!
	if ( MsgBoxYesNo( "Wurden die Artikel- Neuanlagen bereits generiert?", MB_ICONQUESTION | MB_DEFBUTTON2 ) == IDNO )
		return;

	char BASED_CODE szFilter[] = 
		 "Txt Files (*.txt)|*.txt|All Files (*.*)|*.*||";

	CFileDialog dlg( TRUE, "txt",
							NULL,
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT,
							szFilter, this);


	// Auswahl der DC- EAN- Datei
	if ( dlg.DoModal() != IDOK )
		return;

	POSITION pos ( dlg.GetStartPosition() );
	CString sFileName;
	CString fileType;

	CStdioFile stdiofile; 
	
	while( pos ) // get all files selected by user
	{
		sFileName = dlg.GetNextPathName(pos);

		if ( sFileName.IsEmpty( ) )
			return;

		fileType = sFileName.Mid(sFileName.ReverseFind('\\') + 1, 3);
		fileType.MakeUpper();

		if (fileType == "AKL") // Zuordnung PZN - ATC --> carticlecodes mit code_type = 2
		{
			if ( stdiofile.Open( sFileName, CFile::modeRead) )
			{
				processAklFile(&stdiofile);
			}
		}
		else if (fileType == "KLG") // ATC- Stamm --> catccode
		{
			if ( stdiofile.Open( sFileName, CFile::modeRead) )
			{
				processKlgFile(&stdiofile);
			}
		}
		else if (fileType == "ASM") // Zuordnung PZN - zdkwir --> zartwg mit art = E; Zuordnung PZN - Inhaltsstoffmenge --> zartaustria.ingredientqty 
		{
			if ( stdiofile.Open( sFileName, CFile::modeRead) )
			{
				processAsmFile(&stdiofile);
			}
		}
	}

	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
}

void CArtikelDatacare::OnPbArtdatacareEan()
{
	CString errmld;
	long lStatus;

	// Datacare- Änderungen des zueghörigen Tages müssen bereits geladen sein, so dass EAN´s für Neuanlagen in zdcart hinterlegt werden können!
	if ( MsgBoxYesNo( "Wurden die Artikel- Änderungen bereits geladen?", MB_ICONQUESTION | MB_DEFBUTTON2 ) == IDNO )
		return;
		
	char BASED_CODE szFilter[] = 
		 "Txt Files (*.txt)|*.txt|All Files (*.*)|*.*||";

	CFileDialog dlg( TRUE, "txt",
							NULL,
							OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
							szFilter ); 

	// Auswahl der DC- EAN- Datei
	if ( dlg.DoModal() != IDOK )
		return;

	CString sFileName;
	sFileName = dlg.GetPathName();	
	
	if ( sFileName.IsEmpty( ) )
		return;

	CString line; 
	CStdioFile stdiofile; 
	bool isHeaderLine = true;

	// Counter
	int iCntEanAender	= 0;
	int iCntEanNeu		= 0;
	int iCntEanLoesch	= 0;
	int iCntEanSkip		= 0;
	int iCntEanUnbekannt= 0;
	int iCntEanAlt		= 0;

	CString sql;
	int iPzn;
	int iDcNr = 0;
	char mld [200] = {};						

	CArtikelDoc artDoc; // alle notwendigen DB- Funktionen sind bereits dorrt vorhanden
	
	if (artDoc.GetBufferDesc_Ean(errmld)		!= 0 || 
		artDoc.GetBufferDesc_Zpznpflege(errmld) != 0 || 
		artDoc.GetBufferDesc_Zapflege(errmld)	!= 0	)
	{
		MsgBoxOK(errmld);
		return;
	}

	if ( stdiofile.Open( sFileName, CFile::modeRead) )
	{
	// --- Schleife über alle Zeilen im Datenfile ---
		while( stdiofile.ReadString( line ) ) 
		{ 
			if (isHeaderLine == true) // Kopfzeile im Datenfile
			{
				isHeaderLine = false;
				if ( line.Left(3) != "BAR" )
				{
					MsgBoxOK("Die Kopfzeile muss mit 'BAR' beginnen!");				
					return;
				}

				iDcNr = atoi(line.Mid(29, 8));

				if (iDcNr < 20100000 || iDcNr > 20999999)
				{
					MsgBoxOK("Datum in der Kopfzeile ist nicht pausibel!");				
					return;
				}
			}
			else // Datenzeilen:
			{
				if (line.Mid(26, 1) != "1" || line.Mid(27, 1) != "J")
				{
					iCntEanSkip++;
					continue;
				}

				artDoc.m_Buf.zartikel.ARTIKEL_NR = atoi(line.Left(7)); // PZN aus DC-File
				lStatus = artDoc.ReadRecord_Ean(errmld); // Suche in tabelle ean via artikel_nr

				if ( lStatus != 0 && lStatus != 100 )
				{
					MsgBoxOK(errmld);
					return;
				}
				else
				{
					artDoc.m_BufOld.ean = artDoc.m_Buf.ean; // im Doc nicht implizit!
				}

                strcpy(artDoc.m_Buf.ean.EAN_NR, line.Mid(7, 13)); // EAN aus DC-File

				if (TestEan13PruefZiffer(artDoc.m_Buf.ean.EAN_NR) != 2)
				{
					iCntEanSkip++; // EAN ungültig
					continue;
				}

				if ( line.Mid(29, 1) == "L" ) // Lösch- Kennzeichen aus DC-File
				{
					if (lStatus == 100)
					{
						iCntEanSkip++; // nix zu löschen vorhanden
						continue;
					}
					else
					{
						if (artDoc.IsRecordModified_Ean(errmld) == 0 )
						{
							if (artDoc.DeleteRecord_Ean(errmld) == 0)
								iCntEanLoesch++;
							else
							{
								MsgBoxOK(errmld);
								return;
							}
						}
						else
						{
							iCntEanSkip++; // bei uns ist eine andere EAN als bei Datacare hinterlegt = nicht löschen
							continue;
						}
					}
				}
				else
				{
					if (artDoc.IsRecordModified_Ean(errmld) > 0 )
					{
						sql.Format("select artikel_nr from EAN where EAN_NR='%s'", artDoc.m_Buf.ean.EAN_NR); // Prüfen, ob EAN bereits für eine andere PZN hinterlegt

						if ( SqlRead(sql, &iPzn, NULL) == 0 )
						{
							// löschen alte Zuordnung
							artDoc.m_Buf.zartikel.ARTIKEL_NR = iPzn;
							artDoc.ReadRecord_Ean(errmld); // zuerst Buffer mit zu löschenden Daten füllen
							artDoc.m_BufOld.ean = artDoc.m_Buf.ean; // im Doc nicht implizit!

							if (artDoc.DeleteRecord_Ean(errmld) == 0)
							{
								artDoc.StoreRecord_Zpznpflege	( ::Today(), "09"	, errmld );
								artDoc.StoreRecord_Zapflege		( ::Today()			, errmld );
							
								iCntEanAlt++;
							}
							else
							{
								MsgBoxOK(errmld);
								return;
							}

							// Buffer für zu ändernde PZN nochmal einlesen
							artDoc.m_Buf.zartikel.ARTIKEL_NR = atoi(line.Left(7)); // PZN aus DC-File
							artDoc.ReadRecord_Ean(errmld);
							artDoc.m_BufOld.ean = artDoc.m_Buf.ean; // im Doc nicht implizit!
						}

						sql.Format( "select artikel_nr from zartikel where artikel_nr = %ld", artDoc.m_Buf.ean.ARTIKEL_NR );
												
						if ( lStatus == 100 && SqlRead(sql, &iPzn, NULL) == 100 )
						{
							// PZN (noch) nicht in unserem Stamm
							CDatacareDoc dcDoc;
							dcDoc.m_Fd = -1;
							dcDoc.m_Buf.DCNR = iDcNr;
							dcDoc.m_Buf.DC_ARTIKEL_NR = artDoc.m_Buf.zartikel.ARTIKEL_NR;

							if (dcDoc.ReadRecord(errmld) == 0)
							{
								// ean in zdcart schreiben, wenn PZN dort vorhanden...
								strcpy(dcDoc.m_Buf.DC_EAN_NR, line.Mid(7, 13)); // EAN aus DC-File

								if (dcDoc.StoreRecord(errmld, false) == 0)
								{
									iCntEanNeu++;
								}
								else
								{
									MsgBoxOK(errmld);
									return;
								}
							}
							else
							{
								dcDoc.FreeBufferDesc();
								iCntEanUnbekannt++;
								continue;
							}

							dcDoc.FreeBufferDesc();
						}
						else
						{
							if (artDoc.StoreRecord_Ean(errmld) == 0)
								iCntEanAender++;
							else
							{
								MsgBoxOK(errmld);
								return;
							}
						}
					}
					else
					{
						iCntEanSkip++; //Kombination EAN - PZN bereits hinterlegt = nix zu tun
						continue;
					}
				}

				artDoc.StoreRecord_Zpznpflege	( ::Today(), "09"	, errmld );
				artDoc.StoreRecord_Zapflege		( ::Today()			, errmld );

				if ( FdTransact( mld ) != 0 )
				{
					MsgBoxOK(mld);
					return;
				}
			}
		} 
	// --- Ende: Schleife über alle Zeilen im Datenfile ---

		stdiofile.Close(); 
	}

	CloseOneBufferDesc( artDoc.m_Fd_Ean );
	CloseOneBufferDesc( artDoc.m_Fd_Zapflege );
	CloseOneBufferDesc( artDoc.m_Fd_Zpznpflege );

	// Status- Message an User
	errmld.Format("Datacare- EAN´s erfolgreich geladen:\n   %ld EAN´s in Datacare-Neuanlagen hinterlegt,\n   "
						"%ld EAN´s geändert,\n   %ld EAN´s gelöscht,\n   %ld veraltete Verbindungen PZN - EAN gelöscht,\n   %ld Zeilen überlesen,\n   %ld PZN´s unbekannt.",
						iCntEanNeu, iCntEanAender, iCntEanLoesch, iCntEanAlt, iCntEanSkip, iCntEanUnbekannt);
	MsgBoxOK(errmld);
}

void CArtikelDatacare::OnPbArtdatacareDatacareneu() 
{
	CString errmld;
	long lStatus;
	
	lStatus = GenDatacareNeu(  errmld );
	
	if ( lStatus == 47114711 ) return;
//	Meldung immer ausgeben
//	if ( lStatus != 0 )
		MsgBoxOK( errmld );
	
	if ( lStatus != -1 )
	{
		m_bFirstInit = TRUE;
		if ( !InitDatacare() )
			OnCancel();
	}
}


/////////////////////////////////////////////////////
// Artikel generieren

void CArtikelDatacare::GeneriereArtikel( char *mode, long datum )
{
	CString errmld;
#define UEB_LNG1 250
	char buf[UEB_LNG1 + 1];
	CString cDirec;
	CString cDirec_bin;
	int  rcv_lng = UEB_LNG1;

	// DatacareNr
	char str[20];
	m_DCNR.p_GetInput();
	int index = (int)(m_cDatacarenr - 'A'); 

	sprintf( str, "%ld", m_DatacareNummer[ index ] );
	long dcnr = atol( str );

	char datstr[11];
	ConvFromPhoDate ( datstr, datum, "tt.mm.jjjj" );

	if ( *mode == '0' )
		errmld.Format( 
		 CResString::ex().getStrTblText(IDS_DATACARE_ARTIKEL), 
			 dcnr/10000, dcnr/100%100, dcnr%100, datstr ); 
	else
		errmld.Format(
		 CResString::ex().getStrTblText(IDS_DATACARE_ARTIKEL_NEU), 
			 dcnr/10000, dcnr/100%100, dcnr%100, datstr ); 

	if ( MsgBoxYesNo( errmld ) != IDYES )	
		return;

	// Aufruf Serverprogramm UNIX
	long s;
	CGetUnixFiles gU;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	s = gU.GetWWSDateiUnterVerz( cDirec, datacare, errmld );

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
	sprintf( lf_verz, "lf%.6ld", dcnr%1000000 );

	sprintf( buf, "%szpdcgnart %s %s %ld p%s %s",
					cDirec_bin.GetString(), 
					mode, 
					((CEkZdpApp*) AfxGetApp())->GetDbaseName().GetString(),
					dcnr, 
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
		if ( !InitDatacare() )
		{
/*			if ( *mode != '0' )	  // wegen Defpa druecken
				OnCancel();
			else */
				m_DCNR.ResetContent( );
		}
	}
}

void CArtikelDatacare::OnPbArtdatacareArtgen() 
{
	CGuelDatum dlg;
	if ( dlg.DoModal() == IDOK )
	{
		long datum;
		datum = dlg.GetGuelDatum();
		GeneriereArtikel( "0", datum );	
	}
}


void CArtikelDatacare::OnPbArtdatacareNeugen() 
{
	CGuelDatum dlg;
	if ( dlg.DoModal() == IDOK )
	{
		long datum;
		datum = dlg.GetGuelDatum();
		GeneriereArtikel( "1", datum );	
	}
}

/////////////////////////////////////////////////////////////////
// Datacare-Dateien von Client nach Server kopieren


int CArtikelDatacare::IsDatacareDateiname( CString Datei )
{
	Datei.MakeLower();
	if ( Datei.Left( 2 ) == "ar" && atoi(Datei.Mid(2,6)) && Datei.Mid(8) == ".txt" ) return 1;
	return 0;
}

void CArtikelDatacare::OnPbArtdatacareCopy() 
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
		sprintf(WinVerz, "%c:\\datacare", Laufwerke[j]);
				
		if ( gU.GetFileOnWin( WinVerz, DateiNamen, cErrmld ) )
		{
			break;
		}

		// letztes Laufwerk wurde erfolglos durchsucht
		int len = static_cast<int>(strlen(Laufwerke));

		if ( j == (len - 1))
		{
			cErrmld.Format( CResString::ex().getStrTblText(IDS_DATACARE_NO_LIST),
						Laufwerke ); 

			MsgBoxOK( cErrmld );
			return;
		}
	}

	sprintf(IfaText, CResString::ex().getStrTblText(IDS_DATA_LIST), WinVerz);

	anz = static_cast<int>(DateiNamen.GetSize());

	// hier: Dateien nur anzeigen
	CIfaFiles dlg( DateiNamen, _strdup(CResString::ex().getStrTblText(IDS_DATACARE_DATA)), IfaText );

	if ( dlg.DoModal( ) != IDOK ) return;
	
	status = 0;
	cErrmld.Empty();
	for ( i = 0; i < anz; i++ )
	{
		if ( IsDatacareDateiname( DateiNamen[i] ) == 0 && status <= 10 ) // max 10 anzeigen
		{
			cErrmld += DateiNamen[i] + "\n";
			status++;
		}
	}
	if ( status > 0 )
	{
		if ( status == 1 )
			cErrmld += CResString::ex().getStrTblText(IDS_DATACARE_NO_FILE);
		else
			cErrmld += CResString::ex().getStrTblText(IDS_DATACARE_NO_FILES);
		cErrmld += CResString::ex().getStrTblText(IDS_DELETE_FILE);
		if ( status > 1 )
			cErrmld += CResString::ex().getStrTblText(IDS_PLURAL);
		MsgBoxOK( cErrmld );
		return;
	}

	if ( gU.GetWWSDateiUnterVerz( UnxVerz, datacare, cErrmld ) != 0 )
	{
		MsgBoxOK( cErrmld );
		return;
	}

	UnxVerz += "lfakt/";

	status = 0;
	i = 0;

	while( i < anz && status == 0 )
	{
		if ( IsDatacareDateiname( DateiNamen[i] ) != 0 )
		{
			CString VonDatei  = WinVerz;
			VonDatei += "\\" + DateiNamen[i];
// Datei soll im UNIX immer den gleichen Dateinamen haben, damit vom Programm zpdatacarelf die Datumsinformation herausgelesen werden kann
//			CString NachDatei = UnxVerz + DateiNamen[i];
			CString NachDatei = UnxVerz;
			NachDatei += "datacare.txt";
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
		sprintf( buf2, "%szpdatacarelf 2 c",
					  cDirec.GetString() );  

		((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		s = UnxPipwSystem ( buf2, "", buf, &rcv_lng );
//		s = UnxPipwSystem( "zpdatacarelf 2 c", "", buf, &rcv_lng );
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
				if ( IsDatacareDateiname( DateiNamen[i] ) != 0 )
				{
	// Datei soll im UNIX immer den gleichen Dateinamen haben, damit vom Programm zpdatacarelf die Datumsinformation herausgelesen werden kann
	//				CString NachDatei = UnxVerz + DateiNamen[i];
					CString NachDatei = UnxVerz;
					NachDatei += "datacare.txt";
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

void CArtikelDatacare::FillComboBox()
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
