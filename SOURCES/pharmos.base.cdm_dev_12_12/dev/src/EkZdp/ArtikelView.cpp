// ArtikelView.cpp : implementation file
//

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtikelView.h"
#include "ArtikelIfa.h"
#include "IfaDiff.h"
#include <eklibs/hamfcs/hMskNum.h>
#include <hdatum/phodate.h>

#include "ServerDatum.h"

#include "hSelectDialog.h"

#include <phxlib/PhxUtil.h>

#include "FeldBreite.h"
#include "MenuNumbers.h"
#include <libscsvoodoo/libscsvoodoo.h>

#include <voodoo_table_header/cliproductgrp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtikelView

IMPLEMENT_DYNCREATE(CArtikelView, CFormViewMultiLang)

CArtikelView::CArtikelView()
	: ChPflegeView(CArtikelView::IDD),
	  m_CodeConverter( m_ARTIKEL_CODE, m_ARTIKEL_NR, m_SelBox ),
	  m_isHealthInsuranceArticle (false)
{
	//{{AFX_DATA_INIT(CArtikelView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// Allocate memory for the property sheet and make sure
	// that the standard buttons don't show up.
	m_pSheet = new CPflegeSheet(_T(""), this, 0, &m_pSheet); // ??????
	m_pSheet->SetDisplayStdButtons();

}

CArtikelView::~CArtikelView()
{
}

void CArtikelView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelView)
	DDX_Control(pDX, IDC_ST_ARTIKEL_INFO, m_ST_INFO);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_NR, m_ARTIKEL_NR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_CODE, m_ARTIKEL_CODE);
	DDX_Control(pDX, IDC_PB_ARTIKEL_NEXTPZN, m_PB_NEXTPZN);
	DDX_Control(pDX, IDC_PB_ARTIKEL_SELIFA, m_PB_SELIFA);
	DDX_Control(pDX, IDC_PB_ARTIKEL_VORBLIFA, m_PB_VORBLIFA);
	DDX_Control(pDX, IDC_PB_ARTIKEL_RUEBLIFA, m_PB_RUEBLIFA);
	DDX_Control(pDX, IDC_PB_ARTIKEL_UEBERNIFA, m_PB_UEBERNIFA);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CArtikelView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(CArtikelView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_PB_ARTIKEL_NEXTPZN, OnPbArtikelNextpzn)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_SELIFA, OnPbArtikelSelifa)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_VORBLIFA, OnPbArtikelVorblifa)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_RUEBLIFA, OnPbArtikelRueblifa)
	ON_BN_CLICKED(IDC_PB_ARTIKEL_UEBERNIFA, OnPbArtikelUebernifa)
	//}}AFX_MSG_MAP
	ON_MESSAGE(ID_ARTIFA_END, OnArtifaEnd)
	ON_MESSAGE(ID_ARTDATACARE_END, OnArtdatacareEnd)

/////////////////////////////////////////////////////////////////////////////
//printing cformview
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
END_MESSAGE_MAP()

//-----------------------------------------------------------
BOOL CArtikelView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(1);

	pInfo->m_pPD->m_pd.Flags &= ~PD_NOSELECTION;
	pInfo->m_pPD->m_pd.hInstance = AfxGetInstanceHandle();

	// default preparation
	return DoPreparePrinting(pInfo);
}

//-----------------------------------------------------------
void CArtikelView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	if( pInfo == NULL )
		return;

	if( m_dib.GetHandle( ) == NULL )
		return;
	{
		GLock lock( m_dib );
		BITMAPINFOHEADER *pBMI = (BITMAPINFOHEADER*)(LPVOID)lock;

		int nColors = 0;
		if( pBMI->biBitCount <= 8 )
			nColors = ( 1<< pBMI->biBitCount );

		::StretchDIBits( pDC->GetSafeHdc( ),
				pInfo->m_rectDraw.left, 
				pInfo->m_rectDraw.top,
				pBMI->biWidth,
				pBMI->biHeight,
				0, 
				0, 
				pBMI->biWidth,
				pBMI->biHeight,
				(LPBYTE)pBMI + (pBMI->biSize + nColors * sizeof(RGBQUAD)),
				(BITMAPINFO*)pBMI,
				DIB_RGB_COLORS, 
				SRCCOPY);
	}
}

//-----------------------------------------------------------
void CArtikelView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo /* = NULL */)
{
	if( pInfo )
	{
		CClientDC dc( this );
		pDC->SetMapMode(MM_ANISOTROPIC);

		CSize sz( dc.GetDeviceCaps(LOGPIXELSX), dc.GetDeviceCaps(LOGPIXELSY) );
		pDC->SetWindowExt( sz );
		sz = CSize( pDC->GetDeviceCaps(LOGPIXELSX),pDC->GetDeviceCaps(LOGPIXELSY) );
		pDC->SetViewportExt( sz );
	}
}

//-----------------------------------------------------------
void CArtikelView::grapImage( )
{
	//Grap Image
	CPoint oldPoint = GetScrollPosition( );
	CPoint pt( 0, 0 );//scroll to up
	this->ScrollToPosition( pt );

	CClientDC dc(this);
	CRect rect;
	this->GetClientRect( rect );
	m_dib.Attach( GDIUtil::GrabDIB( &dc, rect ) );

	ScrollToPosition( oldPoint );
}

//-----------------------------------------------------------
void CArtikelView::OnFilePrint() 
{
	grapImage( );
	CFormViewMultiLang::OnFilePrint() ;
}

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelView::MakeDialog()
{
	m_Pos_FirstKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ARTIKEL_CODE );
	m_Pos_LastKey = m_dlg.GetFieldNumber();

	m_dlg.InitDialog( m_ARTIKEL_NR );

	m_Pos_Nextpzn = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_PB_NEXTPZN );
	m_Pos_Selifa = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_PB_SELIFA );
	m_Pos_Vorblifa = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_PB_VORBLIFA );
	m_Pos_Rueblifa = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_PB_RUEBLIFA );
	m_Pos_Uebernifa = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_PB_UEBERNIFA );
	m_nMaxFields = m_dlg.GetFieldNumber();
}

/////////////////////////////////////////////////////////////////////////////
// CArtikelView diagnostics

#ifdef _DEBUG
void CArtikelView::AssertValid() const
{
	CFormViewMultiLang::AssertValid();
}

void CArtikelView::Dump(CDumpContext& dc) const
{
	CFormViewMultiLang::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////
//  Validierung

class CV_ARTIKEL_ArtikelNr : public ChValBase
{
public:
	CV_ARTIKEL_ArtikelNr( struct ZARTIKEL* pBuf, CArtikelView* pView  ) 
		: ChValBase( pBuf, pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		if ( PZN_AUCH_EXTERN == GetPznNurNochIntern() &&			// in Ländern mit 7-stelliger PZN weiterhin Prüfziffer checken ! 
			 !IsCountry("CH") &&									// --> nicht in CH
			 (!IsCountry("A") || ((struct ZARTIKEL*)m_pBuf)->ARTIKEL_NR < 9000000) )   // --> nicht in AT im internen Nummernbereich
		{
			int n_ziff = TestPruefZiffer7 ( ((struct ZARTIKEL*)m_pBuf)->ARTIKEL_NR );
			BOOL bOk = n_ziff == 2;
			if ( !bOk && bMeldung )
			{
				if ( n_ziff == 1 )
					MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_PZN_NOT_NULL)) );
				else 
					MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_PZN_INCORRECT)) );
			}
			return bOk;
		}
		else
		{
			BOOL bOk = ((struct ZARTIKEL*)m_pBuf)->ARTIKEL_NR != 0;
			if ( !bOk && bMeldung )
				MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_PZN_NOT_NULL)) );
			return bOk;
		}
	}

	void NotifyProc( )	// richtige Pruefziffer ermitteln
	{
		((CArtikelView*)m_pWnd)->ShowPruefziffer( );
	}

};

void CArtikelView::ShowPruefziffer( )
{
	int prziff;
	long zahl;
	KeyGetInput();
	zahl = m_pBufZartikel->ARTIKEL_NR;
	prziff = GetPruefZiffer7( zahl );
	if ( prziff != -1 ) 
		m_pBufZartikel->ARTIKEL_NR = 10*(zahl/10) + prziff;
	KeySetInput();
	GotoFirstKey();
}

void CArtikelView::SetHeaderInfo( )
{
	CString cInfo, prefCode;
	char *format = "tt.mm.jjjj";
	char datstr[11];

	if ( m_pBufZartikel->ARTIKEL_NR > 0 )
		prefCode = CArticleCodesConverter::getPreferredCodeByNo( m_pBufZartikel->ARTIKEL_NR, cInfo );

	cInfo.Format ("%s\n%s\n%s\nVE: %5ld   %5ld   %5ld   %5ld\nId: %ld     Code: %s    NTIN: %s", 
					m_pBufZartikel->ARTIKEL_NAME, 
					m_pBufZartikel->EINHEIT, 
					m_pBufZartikel->DARREICHFORM,
                    m_pBufArtve->VERPACKEINHEIT1, 
                    m_pBufArtve->VERPACKEINHEIT2, 
                    m_pBufArtve->VERPACKEINHEIT3, 
                    m_pBufArtve->VERPACKEINHEIT4,
					m_pBufZartikel->ARTIKEL_NR,
					prefCode.Trim(),
					m_Doc.GetBuffer()->carticlecodes[21].ARTICLE_CODE); //NTIN is code_type 22

	GetDlgItem( IDC_ST_ARTIKEL_INFO )->SetWindowText( cInfo );
	
	cInfo  = CResString::ex().getStrTblText(IDS_STRING331);
	cInfo += m_pBufZartikel->BEARBEITER;
	cInfo += CResString::ex().getStrTblText(IDS_STRING332);
    ::ConvFromPhoDate( datstr, m_pBufZartikel->DATUM_ANLAGE, format );
	cInfo += datstr;
	cInfo += CResString::ex().getStrTblText(IDS_STRING333);
	::ConvFromPhoDate( datstr, m_pBufZartikel->DATUM_AENDER, format );
	cInfo += datstr;

	if ((IsCountry("D")) || (IsCountry("A")))
	{
		if (IsCountry("D"))
		{
			cInfo += CResString::ex().getStrTblText(IDS_STRING334);
			::ConvFromPhoDate( datstr, m_pBufZartikel->DATUM_IFAAENDER, format );
			cInfo += datstr;
			cInfo += CResString::ex().getStrTblText(IDS_STRING335);
			::ConvFromPhoDate( datstr, m_pBufZartikel->DATUM_IFALOESCH, format );
			cInfo += datstr;
		}
		else
		{
			cInfo += CResString::ex().getStrTblText(IDS_STRING336);
			::ConvFromPhoDate( datstr, m_pBufZartikel->DATUM_IFAAENDER, format );
			cInfo += datstr;
			cInfo += CResString::ex().getStrTblText(IDS_STRING337);
			::ConvFromPhoDate( datstr, m_pBufZartikel->DATUM_IFALOESCH, format );
			cInfo += datstr;
		}
	}

	GetDlgItem( IDC_ST_ARTIKEL_USER )->SetWindowText( cInfo );

    // in Frankreich automatisch Sekundaerbezeichnung aus Artikelbezeichnung, Einheit und Darreichform generieren
	// kann wieder ausgebaut werden, wenn Incogest-System nicht mehr mitversorgt werden muss
	// am 11.07.06 wieder ausgebaut auf Vorgabe Frankreich, mal sehen, fuer wie lange
	// am 21.07.06 wieder aktiviert, diesmal nur für Neuanlagen (Abfrage auf lStatus)
	if (IsCountry("F") && !IsPrewhole() && !IsIvrylab()&& (m_Doc.GetlStatus() == 100))
	{
		CString cs;
		cs = m_Page0.Set_Langname_Fr();

		if (!cs.IsEmpty())
		{
			m_Page0.ZeigeLangname();
		}
	} 
}

//////////////////////////////////////////////////
// return pointer to DataBuffer

struct PFL_ARTIKEL* CArtikelView::GetBuffer() 
{
	return m_Doc.GetBuffer();  
}

struct PFL_ARTIKEL* CArtikelView::GetOldBuffer() 
{
	return m_Doc.GetOldBuffer();  
}

BOOL CArtikelView::AreFieldsEnabled()
{
	return m_bFieldsEnabled;
}

void CArtikelView::Set_WasActive()
{
	m_bWasActive[m_pSheet->GetActiveIndex()] = TRUE;
}

BOOL CArtikelView::IsNeuanlage()
{
	return m_nStatus == 2;
}

/////////////////////////////////////////////////////////////
//  Dialogfelder

void CArtikelView::InitPflege()
{
	m_pDlgIfa = &((CEkZdpApp*) AfxGetApp())->m_pDlgIfa;
	m_pDlgDatacare = &((CEkZdpApp*) AfxGetApp())->m_pDlgDatacare;

	m_pTaxTb = &((CEkZdpApp*) AfxGetApp())->m_TaxTb;

	CArtikelView* pThisView = this;

	MakeDialog();

	m_pBufZartikel	= &m_Doc.GetBuffer()->zartikel;
	m_pBufArtve		= &m_Doc.GetBuffer()->artve;

	m_pIfaBuf = m_Doc.GetIfaBuffer();

//	m_pBufSekbez = m_Doc.GetSekbezBuffer();

	m_ARTIKEL_CODE.SetMask(ED_CHAR,
						 ED_UPPER,
						 m_ARTCODE,
						 L_CARTICLECODES_ARTICLE_CODE,
						 new ChMaskChar,
						 new CV_ARTIKEL_ArtikelNr( m_pBufZartikel, pThisView ));

	m_ARTIKEL_NR.SetMask(ED_LONG,
						 ED_NORMAL,
						 &m_pBufZartikel->ARTIKEL_NR,
						 L_ARTIKEL_NR,
						 new ChMaskNum,
						 new CV_ARTIKEL_ArtikelNr( m_pBufZartikel, pThisView ) );
	
	m_PB_VORBLIFA.SetMask ( IDB_BM_VORBL1, new CBitmap, NULL );
	m_PB_RUEBLIFA.SetMask ( IDB_BM_RUEBL1, new CBitmap, NULL );
	m_PB_UEBERNIFA.SetMask( IDB_BM_VORBL,  new CBitmap, NULL );

	// initialize pages
	for ( int nr = 0; nr < m_pSheet->GetPageCount(); nr++ )
		m_Page[nr]->InitPflege( this );

	// Ifa vor + rueckblaettern
	m_bVorblIfaEnabled = FALSE;
	m_bRueblifaEnabled = FALSE;
	m_bUebernifaEnabled = FALSE;

	// Datacare vor + rueckblaettern
	m_bVorblDatacareEnabled = FALSE;
	m_bRueblDatacareEnabled = FALSE;

	EnableFields( FALSE );
	// Dialog aktivieren
 	SetDialog( TRUE );


//	m_ST_INFO.SetColor( RGB( 255, 0, 0 ), RGB( 192, 192, 192 ) ); // rot
//	m_ST_INFO.SetColor( RGB( 0, 0, 255 ), RGB( 192, 192, 192 ) ); // blau

	// fuer die Artikelauswahl: default: Zartikel ( nicht Zaneuheit )
	m_nAuswahlIndex = 0;
	
	if (IsCountry("CH"))
		m_nAuswahlIndex2 = 2;
	else
		m_nAuswahlIndex2 = 0;

}

void CArtikelView::DisableSpecial()
{
	m_ARTIKEL_NR.EnableWindow(false); // Eingabe nur noch in Artikel-Code-Feld
	m_ARTIKEL_NR.ShowWindow(SW_HIDE);
}

void CArtikelView::ShowSpecial()
{
	// dummy
}

////////////////////////////////////////////////////////////////
// Suchbox

ChSelectDialog* CArtikelView::NewSuchDialog()
{
	m_SelBox.SetPflegeProgNeuheit( NH_NEUHEIT_PHARMOS );
	return new ChSelectDialog ( CResString::ex().getStrTblText(IDS_STRING338), &m_SelBox,
								HCD_SCROLLINFO );
							//	HCD_SCROLLINFO | HCD_BUTTONALTERN )
}

BOOL CArtikelView::PrimeKeyOfSelectedRecord( )
{ 
	return m_SelBox.PrimeKeyOfSelectedRecord( &m_pBufZartikel->ARTIKEL_NR ) == 0;
}

BOOL CArtikelView::PrimeKeyOfNextRecord( )
{
	return m_SelBox.PrimeKeyOfNextRecord( &m_pBufZartikel->ARTIKEL_NR ) == 0;
}

BOOL CArtikelView::PrimeKeyOfPrevRecord( )
{
	return m_SelBox.PrimeKeyOfPrevRecord( &m_pBufZartikel->ARTIKEL_NR ) == 0;
}

int CArtikelView::CloseSuche( )
{
	m_SelBox.CloseCursor();
	return 0;
}

////////////////////////////////////////////////////////////////
// Das ist neu ab 30.05.98  in BasisKlasse uebernehmen
////////////////////////////////////////////////////////////////

int CArtikelView::GetActivePageIndex( )
{
	return m_pSheet->GetActiveIndex( );
}

CWnd* CArtikelView::GetPage( int nPage )
{
	return m_pSheet->GetPage( nPage );
}

BOOL CArtikelView::IsActivePage( CWnd *pWnd )
{
	return (CPropertyPageMultiLang*) pWnd == m_pSheet->GetActivePage( );
}

BOOL CArtikelView::WasPageActive( int nPage )
{
	return m_bWasActive[nPage];
}

BOOL CArtikelView::WasThisPageActive( CWnd *pWnd )
{
	int nPage;
	for ( nPage = 0; nPage < m_pSheet->GetPageCount(); nPage++ )
	{
		if ( pWnd == m_pSheet->GetPage( nPage ) )
			return m_bWasActive[nPage];
	}
	return FALSE;
}


////////////////////////////////////////////////////////////////
// Rest kann kopiert werden
////////////////////////////////////////////////////////////////

void CArtikelView::SetDialog( BOOL bDialog )
{   
	// Dialog aktivieren
//	for ( int i = NR_FIRST_KEY; i <= NR_LAST_KEY; i++ )
//		m_dlg.SetDialog( i, bDialog );

 	m_dlg.SetDialog( bDialog );

	for ( int nr = 0; nr < m_pSheet->GetPageCount(); nr++ )
		m_Page[nr]->SetDialog( bDialog );
}

void CArtikelView::SetMSStandard( BOOL bStandard )
{   
//	for ( int i = NR_FIRST_KEY; i <= NR_LAST_KEY; i++ )
//	 	m_dlg.SetMSStandard( i, bStandard );
 	m_dlg.SetMSStandard( bStandard );

	for ( int nr = 0; nr < m_pSheet->GetPageCount(); nr++ )
		m_Page[nr]->SetMSStandard( bStandard );
}


void CArtikelView::EnableFields( BOOL bEnab )
{
	m_dlg.EnableFields( m_Pos_FirstKey, m_Pos_LastKey, !bEnab );

//////// PB-IFA
	BOOL bErlaub = ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_IFA ) &&
				   ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_ARTIKEL );
	m_dlg.EnableFields( m_Pos_Selifa,   !bEnab && bErlaub && IsCountry("D"));

	m_dlg.EnableFields( m_Pos_Vorblifa, !bEnab && m_bVorblIfaEnabled  && IsCountry("D"));
	m_dlg.EnableFields( m_Pos_Rueblifa, !bEnab && m_bRueblifaEnabled  && IsCountry("D"));
	m_dlg.EnableFields( m_Pos_Uebernifa,!bEnab && m_bUebernifaEnabled && IsCountry("D"));
////////////////////////////////////////////////////////

	// Next-Button nur in Kroatien, Bulgarien & Serbien
	m_dlg.EnableFields( m_Pos_Nextpzn, !bEnab && (IsCountry("HR") || IsCountry("BG") || IsCountry("RS")));

	m_Page[m_pSheet->GetActiveIndex()]->EnableFields( bEnab );

	m_bFieldsEnabled = bEnab;

	DisableSpecial();
}

void CArtikelView::EnablePageFields( BOOL bEnab )
{
	m_Page[m_pSheet->GetActiveIndex()]->EnableFields( bEnab );
}


void CArtikelView::ShowFields( )
{
	CString mld; 

	if (IsCountry("D"))
		m_Doc.ReadRecord_IfaOart(m_pBufZartikel->ARTIKEL_NR, mld);
	else if (IsCountry("CH"))
		m_Doc.ReadClioart(m_pBufZartikel->ARTIKEL_NR, mld);

	m_dlg.ShowFields();

	SetHeaderInfo(); // neu !!!!!

	m_Page[m_pSheet->GetActiveIndex()]->ShowFields();
	m_bWasActive[m_pSheet->GetActiveIndex()] = TRUE;
}

void CArtikelView::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );

	for ( int nr = 0; nr < m_pSheet->GetPageCount(); nr++ )
		m_Page[nr]->SetValidation( bValid );
}

void CArtikelView::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();

	for ( int nr = 0; nr < m_pSheet->GetPageCount(); nr++ )
		if ( m_bWasActive[nr] )
			m_Page[nr]->DataExchangeToBuffer( );
}


BOOL CArtikelView::Validate( )
{
	BOOL bOk = TRUE;

	int maxIndex = m_pSheet->GetPageCount();
    int aktIndex = m_pSheet->GetActiveIndex();
	int Index;
	Index = aktIndex;

	// Validierung testen
	do
	{
		bOk = m_Page[Index]->Validate( FALSE );
		if ( bOk )
		{
			Index++;
			if ( Index == maxIndex ) Index = 0;
		}
	} while ( bOk && Index != aktIndex );

	// wenn Fehler: auf fehlerhafte Page wechseln
	if ( !bOk )
	{
		if ( Index != aktIndex )
			m_pSheet->SetActivePage(Index);
		bOk = m_Page[Index]->Validate( TRUE );
	}

	return bOk;
}


BOOL CArtikelView::ValidateKey( )
{
	return m_dlg.Validate( m_Pos_FirstKey, TRUE );
}

BOOL CArtikelView::IsLastKeyFocus( )
{

	return GetFocus() == GetDlgItem( IDC_LAST_KEY );
}

// Steuerung

void CArtikelView::GotoFirstKey()
{
	SetValidation( FALSE );	
//	m_dlg[NR_FIRST_KEY].Cntrl->SetFocus( );
//	m_dlg.ActivateField( NR_FIRST_KEY );
	m_dlg.SetFocus( m_Pos_FirstKey );
	m_pSheet->ResetPlegePage();
}


void CArtikelView::GotoFirstField() //!!!!!!!!!!!!!!!!
{
	m_Page[m_pSheet->GetActiveIndex()]->ActivateField(0);
	SetValidation( TRUE );	
}

void CArtikelView::KeyGetInput()
{
	m_dlg.DataExchangeToBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}

void CArtikelView::KeySetInput()
{
	m_dlg.DataExchangeFromBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}


////////////////////////////////////////////////////////////////////////////
// Antwort auf Bearbeitungskommandos

long CArtikelView::LeseSatz( CString& cErrmld )
{
	long lStatus;

	SetIfaInfo( -1 );

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = m_Doc.ReadRecord ( cErrmld );

	m_isHealthInsuranceArticle = m_Doc.IsHealthInsuranceArticle();

	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	return lStatus;
}

/* void CArtikelView::CpyFromGalOArt()
{
	// Werte aus cgaloart in Artikelfelder kopieren!
	long lWert = 0;
	
	m_Doc.GetBuffer()->zartikel.ERSATZ_NR = m_Doc.GetGalOArt()->REPL_ARTICLE;

	strncpy ( m_Doc.GetBuffer()->zartikel.ARTIKEL_NR_HERST, m_Doc.GetGalOArt()->SUPP_PROD_NO, L_CGALOART_SUPP_PROD_NO );

	// das Vorblenden von "0" führt zu einer Fehlermeldung
	if (strcmp (m_Doc.GetGalOArt()->EAN, "0            ") != 0)
		strncpy ( m_Doc.GetBuffer()->ean.EAN_NR, m_Doc.GetGalOArt()->EAN, L_EAN_EAN_NR );

	m_Doc.GetBuffer()->artpreis->AVP = m_Doc.GetGalOArt()->PRICE_PUBL;
	
	if ( strcmp ( m_Doc.GetGalOArt()->VAT_CODE, "1" ) == 0 )		// Voll
		strcpy ( m_Doc.GetBuffer()->artpreis->KE_MWST, "0" );
	else if ( strcmp ( m_Doc.GetGalOArt()->VAT_CODE, "2" ) == 0 )	// Vermindert
		strcpy ( m_Doc.GetBuffer()->artpreis->KE_MWST, "1" );
	else if ( strcmp ( m_Doc.GetGalOArt()->VAT_CODE, "3" ) == 0 )	// Ohne
		strcpy ( m_Doc.GetBuffer()->artpreis->KE_MWST, "2" );

	if ( strcmp ( m_Doc.GetGalOArt()->IKS_CAT, "A" ) == 0 ||
		 strcmp ( m_Doc.GetGalOArt()->IKS_CAT, "B" ) == 0 )
	{
		strcpy ( m_Doc.GetBuffer()->zartikel.REZEPTPFL, "1" );
	}

	if ( strcmp ( m_Doc.GetGalOArt()->STOCK_NARC, "Y" ) == 0 )
	{
		strcpy ( m_Doc.GetBuffer()->zartikel.BTM, "1" );
	}

	if ( strcmp ( m_Doc.GetGalOArt()->HOSPCODE, "Y" ) == 0 )
	{
		strcpy ( m_Doc.GetBuffer()->zartikel.KLINIKPACKUNG, "1" );
	}

	if ( strcmp ( m_Doc.GetGalOArt()->STOCK_FRIDGE, "1" ) == 0 ||
		 strcmp ( m_Doc.GetGalOArt()->STOCK_FRIDGE, "2" ) == 0 )
	{
		strcpy ( m_Doc.GetBuffer()->zartikel.KUEHLARTIKEL, "4" );
	}

	if ( strcmp ( m_Doc.GetGalOArt()->INS_CODE, "1" ) == 0 )
	{
		strcpy ( m_Doc.GetBuffer()->zartikel.SORTIMENT_1, "1" );
	}

	if ( strcmp ( m_Doc.GetGalOArt()->CODE_BG, "B" ) == 0 )
	{
		strcpy ( m_Doc.GetBuffer()->zartikel.PSYCHOTROP, "J" );
	}

	strncpy ( m_Doc.GetBuffer()->zartswitzerland.IKS_CODE, m_Doc.GetGalOArt()->IKS_CAT, L_ZARTSWITZERLAND_IKS_CODE);

	if ( strcmp ( m_Doc.GetGalOArt()->IKS_CAT, "C" ) == 0 ) 
		strcpy ( m_Doc.GetBuffer()->zartswitzerland.VERTRBIND_LISTE_C,"1");
	else if ( strcmp ( m_Doc.GetGalOArt()->IKS_CAT, "D" ) == 0 ) 
		strcpy ( m_Doc.GetBuffer()->zartswitzerland.VERTRBIND_LISTE_D,"1");
}

void CArtikelView::CpyFromGalNam()
{		
	// Werte aus cgalonam in Artikelfelder kopieren!
	char ArtName[110];
	char Einheit[60];
	char DAR[40];
	char temp[15];
	char converted[60];
	CString csTemp;

	// deutsch
	csTemp = m_Doc.GetGalNamD()->MULTIPLIER;
	csTemp.TrimRight();
	if ( !csTemp.IsEmpty() && csTemp != "1" )
	{
		strcpy ( Einheit, csTemp );
		strcat ( Einheit, "X" );	
	}
	else
	{
		strcpy ( Einheit, "" );
	}
	GetQtyCH( m_Doc.GetGalNamD()->QTY, temp );
	strcat ( Einheit, temp );
	strcat ( Einheit, " " );
	csTemp = m_Doc.GetGalNamD()->QTY_UNIT;
	csTemp.TrimRight();
	csTemp = GetUnitCH(csTemp);
	strcat ( Einheit, csTemp );
	csTemp = Einheit;
	csTemp.MakeUpper();
	strncpy( m_Doc.GetBuffer()->zartikel.EINHEIT, csTemp, L_ZARTIKEL_EINHEIT);
	
	strcpy ( DAR, GetDarCH_D( m_Doc.GetGalNamD()->FORM ) );
	strncpy( m_Doc.GetBuffer()->zartikel.DARREICHFORM, DAR, L_ZARTIKEL_DARREICHFORM);
	
	// BASE_NAME
	csTemp = m_Doc.GetGalNamD()->BASE_NAME;
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcpy ( ArtName, csTemp );

	// SECOND_NAME
	csTemp = m_Doc.GetGalNamD()->SECOND_NAME;
	csTemp.TrimRight();
	
	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");
	
	strcat ( ArtName, csTemp );

	// DRUG_FOR
	csTemp = m_Doc.GetGalNamD()->DRUG_FOR;
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, csTemp );

	// ITEM_SIZE
	csTemp = m_Doc.GetGalNamD()->ITEM_SIZE;
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, csTemp );

	// SYN3
	csTemp = m_Doc.GetGalNamD()->SYN3;
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, csTemp );

	// evtl. Zusatz aus Darreichform
	
	strcpy (temp, GetDfoZusatz_D(m_Doc.GetGalNamD()->FORM));
	csTemp.Format("%s", temp);
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, temp );

	// CONCENTRATION
	GetConcCH(m_Doc.GetGalNamD()->CONCENTRATION, temp);
	csTemp.Format("%s", temp);
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, csTemp );

	// CONC_UNIT
	csTemp = m_Doc.GetGalNamD()->CONC_UNIT;
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, csTemp );

	csTemp = ArtName;
	csTemp.MakeUpper();
	m_Doc.ConvertUmlaute((unsigned char*)csTemp.GetString(), converted);
	strncpy( m_Doc.GetBuffer()->zartikel.ARTIKEL_NAME, converted, L_ZARTIKEL_ARTIKEL_NAME);
	
	// Name50 --> Artikel_Langname
	csTemp = m_Doc.GetGalNamD()->COMP_NAME;
	if ( !csTemp.IsEmpty() )
	{
		csTemp.TrimRight();
		m_Doc.ConvertUmlaute((unsigned char*)csTemp.GetString(), converted);
		strncpy ( m_Doc.GetBuffer()->zartikel.ARTIKEL_LANGNAME, converted, L_ZARTIKEL_ARTIKEL_LANGNAME );	
	}

	// französisch
	csTemp = m_Doc.GetGalNamF()->MULTIPLIER;
	csTemp.TrimRight();
	if ( !csTemp.IsEmpty() && csTemp != "1" )
	{
		strcpy ( Einheit, csTemp );
		strcat ( Einheit, "X" );	
	}
	else
	{
		strcpy ( Einheit, "" );
	}

	GetQtyCH( m_Doc.GetGalNamD()->QTY, temp );
	strcat ( Einheit, temp );
	strcat ( Einheit, " " );
	csTemp = m_Doc.GetGalNamF()->QTY_UNIT;
	csTemp.TrimRight();
	csTemp = GetUnitCH(csTemp);
	strcat ( Einheit, csTemp );
	csTemp = Einheit;
	csTemp.MakeUpper();
	strncpy( m_Doc.GetBuffer()->carticlelang.PACKAGINGUNIT, csTemp, L_CARTICLELANG_PACKAGINGUNIT);

	strcpy ( DAR, GetDarCH_F( m_Doc.GetGalNamF()->FORM ) );
	strncpy( m_Doc.GetBuffer()->carticlelang.PHARMAFORM, DAR, L_CARTICLELANG_PHARMAFORM);
	
	// BASE_NAME
	csTemp = m_Doc.GetGalNamF()->BASE_NAME;
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcpy ( ArtName, csTemp );
	
	// SECOND_NAME
	csTemp = m_Doc.GetGalNamF()->SECOND_NAME;
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, csTemp );

	// DRUG_FOR
	csTemp = m_Doc.GetGalNamF()->DRUG_FOR;
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, csTemp );
	
	// ITEM_SIZE
	csTemp = m_Doc.GetGalNamF()->ITEM_SIZE;
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, csTemp );

	// SYN3
	csTemp = m_Doc.GetGalNamF()->SYN3;
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, csTemp );

	// evtl. Zusatz aus Darreichform
	strcpy (temp, GetDfoZusatz_F(m_Doc.GetGalNamF()->FORM));
	csTemp.Format("%s", temp);
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, temp );

	// CONCENTRATION
	GetConcCH(m_Doc.GetGalNamF()->CONCENTRATION, temp);
	csTemp.Format("%s", temp);
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, csTemp );

	// CONC_UNIT
	csTemp = m_Doc.GetGalNamF()->CONC_UNIT;
	csTemp.TrimRight();

	if ( !csTemp.IsEmpty() )
		csTemp.Append(" ");

	strcat ( ArtName, csTemp );

	csTemp = ArtName;
	csTemp.MakeUpper();
	m_Doc.ConvertUmlaute((unsigned char*)csTemp.GetString(), converted);
	strncpy( m_Doc.GetBuffer()->carticlelang.ARTICLENAME, converted, L_CARTICLELANG_ARTICLENAME); 

	// Name50 --> Artikel_Langname_F
	csTemp = m_Doc.GetGalNamF()->COMP_NAME;
	if ( !csTemp.IsEmpty() )
	{
		csTemp.TrimRight();
		m_Doc.ConvertUmlaute((unsigned char*)csTemp.GetString(), converted);
		strncpy ( m_Doc.GetBuffer()->carticlelang.ARTICLENAMELONG, converted, L_CARTICLELANG_ARTICLENAMELONG ); 	
	}
} */

BOOL CArtikelView::SetArticleNoEditCtrl( CString& cErrmld )
{
	if ( 0 > m_CodeConverter.setArticleNoEditCtrl( cErrmld )) // Code nicht vorhanden !
	{
		CString code;
		m_ARTIKEL_CODE.GetWindowText(code);

		// trim leading zeros
		while( code[0] == '0' ){
			code.Delete(0);
		}

		m_ARTIKEL_CODE.SetWindowText(code);

		// workaround, that new articles with PZN7 can be created without creation of article code before! 
		if (code <= "9999999" && 
			code.GetLength() > 0 && code.GetLength() <= 7)
		{
			// Prüfzifferncheck bei Neuanlagen weiterhin gewünscht! 
			if ( 2 != TestPruefZiffer7 ( atoi(code) ) )
			{
				if ( !IsCountry("CH") && (!IsCountry("A") || atoi(code) < 9000000)) // kein Prüfzifferncheck in CH / in AT für den internen Nummernbereich
				{
					MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_PZN_INCORRECT)) );
					return false;
				}
			}
			
			m_ARTIKEL_NR.SetWindowText(code); // Artikel- Neuanlage ! 
		}
		else if (code.GetLength() == 8 && IsCountry("D"))
		{
			// Prüfzifferncheck auch bei PZN 8
			if ( 2 != TestPruefZiffer7 ( atoi(code) ) )
			{
				MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_PZN_INCORRECT)) );
				return false;
			}

			long lStatus = 0;
			long lPzn = 0;
			double dCount;
			CString sql;

			sql = "select nr from nummerek where nr_art = 'NEWPZN' ";
			lStatus = SqlRead(sql, &lPzn, NULL);

			if (lStatus == 0)
			{
				sql.Format( "select count(*) + (select count(*) from carticlecodes where articleno = %ld) from zartikel where artikel_nr = %ld ", lPzn, lPzn );
				lStatus = SqlRead(sql, &dCount, NULL);

				while ( lStatus == 0 && (dCount > 0.0 || TestPruefZiffer7(lPzn) == 2)) // PZN bereits vorhanden oder Prüfziffer gültig
				{
					++lPzn;
					sql.Format( "select count(*) + (select count(*) from carticlecodes where articleno = %ld) from zartikel where artikel_nr = %ld ", lPzn, lPzn );
					lStatus = SqlRead(sql, &dCount, NULL);
				}

				if ( lStatus == 0 && dCount == 0.0 ) // erste freie PZN gefunden
				{
					CString str;
					str.Format("%ld", lPzn);
					m_ARTIKEL_NR.SetWindowText(str); // Artikel- Neuanlage (PZN8)!
					
					// nächste freie Nummer abspeichern
					sql.Format("UPDATE nummerek SET nr = %ld WHERE nr_art = 'NEWPZN' ", lPzn + 1);
					SqlExecuteImm( sql );
				}
			}
		}
		else
		{
			MsgBoxOK( cErrmld );
			m_ARTIKEL_CODE.SetFocus();
			return FALSE;
		}
	}
	return TRUE;
}

void CArtikelView::SetArticleCodeEditCtrl()
{
	m_CodeConverter.setArticleCodeEditCtrl();
}

void CArtikelView::SetPreferredArticleCodeEditCtrl()
{
	m_CodeConverter.setPreferredArticleCodeEditCtrl();
}

void CArtikelView::CpyFromDsOArt()
{
	// Werte aus cdsoart in Artikelfelder kopieren!
	CString csTemp;

	strncpy(m_Doc.GetBuffer()->ean.EAN_NR, m_Doc.GetDsOArt()->EAN, L_EAN_EAN_NR);

	// Hersteller_nr und Artikel_nr des Herstellers lt. Vorgabe Frankreich nicht
//	strncpy(m_Doc.GetBuffer()->zartikel.ARTIKEL_NR_HERST, m_Doc.GetDsOArt()->ARTICLENO_MANUF, L_ZARTIKEL_ARTIKEL_NR_HERST);
//	m_Doc.GetBuffer()->zartikel.HERSTELLER_NR = m_Doc.GetDsOArt()->CODE_MANUFACTURER;
	
	m_Doc.GetBuffer()->artpreis->AEP = m_Doc.GetDsOArt()->PRICE_PHARMACY;
	m_Doc.GetBuffer()->artpreis->AVP = m_Doc.GetDsOArt()->PRICE_PUBLIC;

	strncpy(m_Doc.GetBuffer()->artpreis->KE_MWST, m_Doc.GetDsOArt()->CODE_VAT, L_ZARTPREIS_KE_MWST);

	m_Doc.GetBuffer()->artpreis->GROSSO = m_Doc.GetDsOArt()->PRICE_WHOLESALER;

	m_Doc.GetBuffer()->zartikel.HOEHE = m_Doc.GetDsOArt()->HEIGHT;
	m_Doc.GetBuffer()->zartikel.LAENGE = m_Doc.GetDsOArt()->WIDTH;
	m_Doc.GetBuffer()->zartikel.BREITE = m_Doc.GetDsOArt()->DEPTH;
	m_Doc.GetBuffer()->zartikel.GEWICHT = m_Doc.GetDsOArt()->GROSS_WEIGHT;
	m_Doc.GetBuffer()->zartikel.LAUFZEITMONATE = m_Doc.GetDsOArt()->STOCK_DURATION;

	strncpy(m_Doc.GetBuffer()->zartfrance.REIMBURSEMENT_TYPE,  m_Doc.GetDsOArt()->CODE_REFUND, L_ZARTFRANCE_REIMBURSEMENT_TYPE);
	m_Doc.GetBuffer()->zartfrance.REIMBURSEMENT_VAL = m_Doc.GetDsOArt()->REFUND_LPPR;
	strncpy(m_Doc.GetBuffer()->zartfrance.CODE_LPPR,  m_Doc.GetDsOArt()->CODE_LPPR, L_ZARTFRANCE_CODE_LPPR);

	csTemp = m_Doc.GetDsOArt()->PHARMAFORM;
	csTemp.MakeUpper();
	strncpy(m_Doc.GetBuffer()->zartikel.DARREICHFORM, csTemp, L_ZARTIKEL_DARREICHFORM);
	
	csTemp = m_Doc.GetDsOArt()->ARTICLENAME;
	csTemp.MakeUpper();
	strncpy(m_Doc.GetBuffer()->zartikel.ARTIKEL_NAME, csTemp, L_ZARTIKEL_ARTIKEL_NAME);

	csTemp = m_Doc.GetDsOArt()->PACKAGINGUNIT;
	csTemp.MakeUpper();
	strncpy(m_Doc.GetBuffer()->zartikel.EINHEIT, csTemp, L_ZARTIKEL_EINHEIT);

	csTemp = m_Doc.GetDsOArt()->ARTICLENAMELONG;
	csTemp.MakeUpper();
	strncpy(m_Doc.GetBuffer()->zartikel.ARTIKEL_LANGNAME, csTemp, L_ZARTIKEL_ARTIKEL_LANGNAME);
}

// Werte aus clioart in Artikelfelder kopieren!
void CArtikelView::CpyFromLogIndex()
{
	strncpy(m_Doc.GetBuffer()->zartikel.ARTIKEL_NR_HERST, m_Doc.GetClioart()->ARTNO1, L_ZARTIKEL_ARTIKEL_NR_HERST);

	CString Name;
	CString Errmld;
	CString PPE;
	CString cZentralppeList;
	CRdHerstel	m_RD_HERSTELLER;

	m_RD_HERSTELLER.IPlausi( m_Doc.GetClioart()->HERSTELLER_NR, Name, PPE, cZentralppeList, &Errmld);
	strcpy ( m_Doc.GetBuffer()->zartikel.ZENTRALPPELIST, cZentralppeList );
	
	/* if (m_Doc.GetClioart()->EXP)
		strcpy ( m_Doc.GetBuffer()->zartikel.VERFALL, "1" ); --> wird per Default bei alle Neuanlage gesetzt, aber keine Abhängigkeit mehr zu laufzeitmonate !
	else
		strcpy ( m_Doc.GetBuffer()->zartikel.VERFALL, "0" ); */

	CString csSwissmedic_key;
	
	if (m_Doc.GetClioart()->SMNO > 0)
	{
        csSwissmedic_key.Format("%08.8ld", m_Doc.GetClioart()->SMNO);
		m_Doc.GetBuffer()->zartswitzerland.SWISSMEDIC_REGNR = atoi(csSwissmedic_key.Left(5));

		if (m_Doc.GetBuffer()->zartswitzerland.SWISSMEDIC_REGNR > 0)
			m_Doc.GetBuffer()->zartswitzerland.SWISSMEDIC_ZUSATZ = static_cast<short>(atoi(csSwissmedic_key.Mid(5,3)));
	}

	if ( m_Doc.GetClioart()->NINCD == 10 )
		strcpy ( m_Doc.GetBuffer()->zartikel.SORTIMENT_1, "1" );

	if ( strcmp ( m_Doc.GetClioart()->SMCAT, "A" ) == 0 ||
		 strcmp ( m_Doc.GetClioart()->SMCAT, "B" ) == 0 ||
		 strcmp ( m_Doc.GetClioart()->SMCAT, "C" ) == 0 ||
		 strcmp ( m_Doc.GetClioart()->SMCAT, "D" ) == 0 ||
		 strcmp ( m_Doc.GetClioart()->SMCAT, "E" ) == 0 )
	{
		strcpy( m_Doc.GetBuffer()->zartikel.ARZNEIMITTEL, "1");
	}

	if ( strcmp ( m_Doc.GetClioart()->BG, "Y" ) == 0 )
		strcpy ( m_Doc.GetBuffer()->zartikel.BTM, "1" );

	if ( strcmp ( m_Doc.GetClioart()->COOL, "1" ) == 0 ||
		 strcmp ( m_Doc.GetClioart()->COOL, "2" ) == 0 ||
		 strcmp ( m_Doc.GetClioart()->COOL, "Y" ) == 0 )
	{
		strcpy ( m_Doc.GetBuffer()->zartikel.KUEHLARTIKEL, "4" );
	}

	sprintf( m_Doc.GetBuffer()->artpreis[0].KE_MWST, "%d", m_Doc.GetClioart()->VAT - 1 );

	strncpy ( m_Doc.GetBuffer()->zartswitzerland.IKS_CODE, m_Doc.GetClioart()->SMCAT, L_ZARTSWITZERLAND_IKS_CODE);

	if ( strcmp ( m_Doc.GetClioart()->SMCAT, "A" ) == 0 ||
		 strcmp ( m_Doc.GetClioart()->SMCAT, "B" ) == 0 )
		strcpy ( m_Doc.GetBuffer()->zartikel.REZEPTPFL, "1" );
	else if ( strcmp ( m_Doc.GetClioart()->SMCAT, "C" ) == 0 ) 
		strcpy ( m_Doc.GetBuffer()->zartswitzerland.VERTRBIND_LISTE_C, "1");
	else if ( strcmp ( m_Doc.GetClioart()->SMCAT, "D" ) == 0 ) 
		strcpy ( m_Doc.GetBuffer()->zartswitzerland.VERTRBIND_LISTE_D, "1");

	if ( strcmp ( m_Doc.GetClioart()->CLINCD, "Y" ) == 0 )
		strcpy ( m_Doc.GetBuffer()->zartikel.KLINIKPACKUNG, "1" );
	
	/* im CODE_BG stehen "B" und "C", diese sollen 1:1 ins Psychotrop-Feld übernommen werden */
	if ( strcmp ( m_Doc.GetClioart()->CDBG, "B" ) == 0 || 
		 strcmp ( m_Doc.GetClioart()->CDBG, "C" ) == 0 )
	{
		strncpy ( m_Doc.GetBuffer()->zartikel.PSYCHOTROP, m_Doc.GetClioart()->CDBG, L_ZARTIKEL_PSYCHOTROP );
	}

	m_Doc.GetBuffer()->zartikel.DATUM_AH = m_Doc.GetClioart()->OUTSAL;

	strncpy ( m_Doc.GetBuffer()->ean.EAN_NR, m_Doc.GetClioart()->BC, L_EAN_EAN_NR );

	m_Doc.GetBuffer()->artpreis[0].GROSSO = m_Doc.GetClioart()->PRICE_PEXF;
	m_Doc.GetBuffer()->artpreis[0].AVP = m_Doc.GetClioart()->PRICE_PPUB;
	m_Doc.GetBuffer()->artpreis[0].DATUMGUELTIGAB = m_Doc.GetClioart()->VDAT;

	if ( strcmp ( m_Doc.GetClioart()->STTOX, "Y" ) == 0 )
		strcpy ( m_Doc.GetBuffer()->zartikel.SIDABLATT, "1" );
	
	if ( strcmp ( m_Doc.GetClioart()->CE, "Y" ) == 0 )
		strcpy ( m_Doc.GetBuffer()->zartikel.CE_KENNZEICHEN, "1" );
	
    if ( m_Doc.GetClioart()->SMCDAT > 0 )
	   m_Doc.GetBuffer()->zartikel.DATUM_RR = m_Doc.GetClioart()->SMCDAT;
    else if ( m_Doc.GetClioart()->SIST > 0 && m_Doc.GetClioart()->SIST > m_Doc.GetClioart()->ESIST )
		m_Doc.GetBuffer()->zartikel.DATUM_RR = m_Doc.GetClioart()->SIST;
   
   if ( m_Doc.GetClioart()->BIOCID > 0 )
	   strcpy (m_Doc.GetBuffer()->zartikel.BIOZID_VERORD, "1");
   
   m_Doc.GetBuffer()->zartikel.ARTIKEL_NR_ORIG = m_Doc.GetClioart()->PHAR2;

   if ( strcmp(m_Doc.GetClioart()->GENCD, "O") == 0 )
	   strcpy (m_Doc.GetBuffer()->zartikel.PRODUKTART, "1");
   else if ( strcmp(m_Doc.GetClioart()->GENCD, "G") == 0 )
	   strcpy (m_Doc.GetBuffer()->zartikel.PRODUKTART, "2");
   else if (strcmp(m_Doc.GetClioart()->GENCD, "S") == 0)
	   strcpy(m_Doc.GetBuffer()->zartikel.PRODUKTART, "A");

   m_Doc.GetBuffer()->zartswitzerland.BAGDOSSIER = m_Doc.GetClioart()->BAGDOSSIER;
   strcpy (m_Doc.GetBuffer()->zartswitzerland.MIGCD, m_Doc.GetClioart()->MIGCD);

   strcpy ( m_Doc.GetBuffer()->carticlecodes[1].ARTICLE_CODE, m_Doc.GetClioart()->ATC );
   strcpy ( m_Doc.GetBuffer()->carticlecodes[3].ARTICLE_CODE, m_Doc.GetClioart()->BAGNO );
   strcpy ( m_Doc.GetBuffer()->carticlecodes[20].ARTICLE_CODE, m_Doc.GetClioart()->CDSO1 );
   strcpy ( m_Doc.GetBuffer()->carticlecodes[18].ARTICLE_CODE, m_Doc.GetClioart()->GTIN14 );
 
// mehrsprachig
   	char Einheit[60];
	char DARD[40];
	char DARF[40];
	char temp[15];
	CString csTemp;
	CString csTempD;
	CString csTempF;
	
// Ermittlung Einheit
	csTemp.Format("%d", m_Doc.GetClioart()->NOPCS);
	csTemp.TrimRight();
	if ( !csTemp.IsEmpty() && m_Doc.GetClioart()->NOPCS > 1 && 
		 m_Doc.GetClioart()->NOPCS != (short)m_Doc.GetClioart()->QTY) 
	{
		strcpy ( Einheit, csTemp );
		strcat ( Einheit, "X" );	
	}
	else
	{
		strcpy ( Einheit, "" );
	}
	
	GetQtyCH( m_Doc.GetClioart()->QTY, temp );
	strcat ( Einheit, temp );
	strcat ( Einheit, " " );
	
	csTempD = m_Doc.GetClioart()->QTYUD;
	csTempD.TrimRight();
	csTempD = GetUnitCH(csTempD);

	csTempF = m_Doc.GetClioart()->QTYUF;
	csTempF.TrimRight();
	csTempF = GetUnitCH(csTempF);

// Ermittlung Darreichform	
	strcpy ( DARD, GetDarCH_D( m_Doc.GetClioart()->PCKTYPD ) );
	strcpy ( DARF, GetDarCH_F( m_Doc.GetClioart()->PCKTYPF ) );

// 13.11.19: im Prewhole stehen die französischen Bezeichnungen in zartikel und die deutschen in carticlelang
	if (IsPrewhole())
	{
		strncpy( m_Doc.GetBuffer()->zartikel.EINHEIT, Einheit + csTempF, L_ZARTIKEL_EINHEIT);
		strncpy( m_Doc.GetBuffer()->carticlelang.PACKAGINGUNIT, Einheit + csTempD, L_CARTICLELANG_PACKAGINGUNIT);

		strncpy( m_Doc.GetBuffer()->zartikel.DARREICHFORM, DARF, L_ZARTIKEL_DARREICHFORM);
		strncpy( m_Doc.GetBuffer()->carticlelang.PHARMAFORM, DARD, L_CARTICLELANG_PHARMAFORM);

		strncpy( m_Doc.GetBuffer()->zartikel.ARTIKEL_NAME, m_Doc.GetClioart()->DSCRF, L_ZARTIKEL_ARTIKEL_NAME);
		strncpy( m_Doc.GetBuffer()->carticlelang.ARTICLENAME, m_Doc.GetClioart()->DSCRD, L_CARTICLELANG_ARTICLENAME);
	
		strncpy ( m_Doc.GetBuffer()->zartikel.ARTIKEL_LANGNAME, m_Doc.GetClioart()->DSCRLONGF, L_ZARTIKEL_ARTIKEL_LANGNAME );	
		strncpy ( m_Doc.GetBuffer()->carticlelang.ARTICLENAMELONG, m_Doc.GetClioart()->DSCRLONGD, L_CARTICLELANG_ARTICLENAMELONG ); 	
	}
	else
	{
		strncpy( m_Doc.GetBuffer()->zartikel.EINHEIT, Einheit + csTempD, L_ZARTIKEL_EINHEIT);
		strncpy( m_Doc.GetBuffer()->carticlelang.PACKAGINGUNIT, Einheit + csTempF, L_CARTICLELANG_PACKAGINGUNIT);

		strncpy( m_Doc.GetBuffer()->zartikel.DARREICHFORM, DARD, L_ZARTIKEL_DARREICHFORM);
		strncpy( m_Doc.GetBuffer()->carticlelang.PHARMAFORM, DARF, L_CARTICLELANG_PHARMAFORM);

		strncpy( m_Doc.GetBuffer()->zartikel.ARTIKEL_NAME, m_Doc.GetClioart()->DSCRD, L_ZARTIKEL_ARTIKEL_NAME);
		strncpy( m_Doc.GetBuffer()->carticlelang.ARTICLENAME, m_Doc.GetClioart()->DSCRF, L_CARTICLELANG_ARTICLENAME);
	
		strncpy ( m_Doc.GetBuffer()->zartikel.ARTIKEL_LANGNAME, m_Doc.GetClioart()->DSCRLONGD, L_ZARTIKEL_ARTIKEL_LANGNAME );	
		strncpy ( m_Doc.GetBuffer()->carticlelang.ARTICLENAMELONG, m_Doc.GetClioart()->DSCRLONGF, L_CARTICLELANG_ARTICLENAMELONG ); 	
	}

	strncpy ( m_Doc.GetBuffer()->zartikel.GS_EXPLOSION, m_Doc.GetClioart()->GS_EXPLOSION, L_ZARTIKEL_GS_EXPLOSION);
	strncpy ( m_Doc.GetBuffer()->zartikel.GS_BRAND, m_Doc.GetClioart()->GS_BRAND, L_ZARTIKEL_GS_BRAND);
	strncpy ( m_Doc.GetBuffer()->zartikel.GS_LEICHTENTZ, m_Doc.GetClioart()->GS_LEICHTENTZ, L_ZARTIKEL_GS_LEICHTENTZ);
	strncpy ( m_Doc.GetBuffer()->zartikel.GS_HOCHENTZ, m_Doc.GetClioart()->GS_HOCHENTZ, L_ZARTIKEL_GS_HOCHENTZ);
	strncpy ( m_Doc.GetBuffer()->zartikel.GS_GIFTIG, m_Doc.GetClioart()->GS_GIFTIG, L_ZARTIKEL_GS_GIFTIG);
	strncpy ( m_Doc.GetBuffer()->zartikel.GS_SEHRGIFTIG, m_Doc.GetClioart()->GS_SEHRGIFTIG, L_ZARTIKEL_GS_SEHRGIFTIG);
	strncpy ( m_Doc.GetBuffer()->zartikel.GS_GESUNDHSCH, m_Doc.GetClioart()->GS_GESUNDHSCH, L_ZARTIKEL_GS_GESUNDHSCH);
	strncpy ( m_Doc.GetBuffer()->zartikel.GS_REIZEND, m_Doc.GetClioart()->GS_REIZEND, L_ZARTIKEL_GS_REIZEND);
	strncpy ( m_Doc.GetBuffer()->zartikel.GS_AETZEND, m_Doc.GetClioart()->GS_AETZEND, L_ZARTIKEL_GS_AETZEND);
	strncpy ( m_Doc.GetBuffer()->zartikel.GS_UMWELT, m_Doc.GetClioart()->GS_UMWELT, L_ZARTIKEL_GS_UMWELT);

	m_Doc.GetBuffer()->csafetydatasheet.PICTOGRAM01_FLAG = m_Doc.GetClioart()->PICTOGRAM01_FLAG;
	m_Doc.GetBuffer()->csafetydatasheet.PICTOGRAM02_FLAG = m_Doc.GetClioart()->PICTOGRAM02_FLAG;
	m_Doc.GetBuffer()->csafetydatasheet.PICTOGRAM03_FLAG = m_Doc.GetClioart()->PICTOGRAM03_FLAG;
	m_Doc.GetBuffer()->csafetydatasheet.PICTOGRAM04_FLAG = m_Doc.GetClioart()->PICTOGRAM04_FLAG;
	m_Doc.GetBuffer()->csafetydatasheet.PICTOGRAM05_FLAG = m_Doc.GetClioart()->PICTOGRAM05_FLAG;
	m_Doc.GetBuffer()->csafetydatasheet.PICTOGRAM06_FLAG = m_Doc.GetClioart()->PICTOGRAM06_FLAG;
	m_Doc.GetBuffer()->csafetydatasheet.PICTOGRAM07_FLAG = m_Doc.GetClioart()->PICTOGRAM07_FLAG;
	m_Doc.GetBuffer()->csafetydatasheet.PICTOGRAM08_FLAG = m_Doc.GetClioart()->PICTOGRAM08_FLAG;
	m_Doc.GetBuffer()->csafetydatasheet.PICTOGRAM09_FLAG = m_Doc.GetClioart()->PICTOGRAM09_FLAG;

	ConvFromPhoDate ( m_Doc.GetBuffer()->csafetydatasheet.SDS_VERSION, m_Doc.GetClioart()->SDS_DATE_DE, "tt.mm.jjjj" );

	/* - Skontofähigkeit setzen wenn GEP die Grenze überschreitet - */
	CString sql;
	long lGrenze;
	sql = "select grenze_a from filiale where filialnr = 0";
	SqlRead(sql, &lGrenze, NULL);

    if (m_Doc.GetBuffer()->artpreis[0].GROSSO > lGrenze)
		strcpy(m_Doc.GetBuffer()->zartikel.SKONTOFAEHIG, "0");

	strcpy(m_Doc.GetBuffer()->zartikel.VERFALL, "1");

	if(strcmp(m_Doc.GetClioart()->SALECD, "P") == 0 || strcmp(m_Doc.GetClioart()->SALECD, "R") == 0 || m_Doc.GetBuffer()->artpreis[0].GROSSO <= 0.0)
		strcpy(m_Doc.GetBuffer()->zartikel.ARTIKEL_GESPERRT, "1");

	if(strncmp(m_Doc.GetClioart()->ATC, "L01", 3) == 0)
		strcpy(m_Doc.GetBuffer()->zartikel.ZYTOSTATIKA, "1");

	if(strcmp(m_Doc.GetClioart()->GRPCD, "P2") == 0)
		m_Doc.GetBuffer()->zartikel.KOSMETIKUM = 1;
	
	if(strncmp(m_Doc.GetClioart()->CDSO1,"11.", 3) == 0 && m_Doc.GetClioart()->NINCD == 10)
		strcpy(m_Doc.GetBuffer()->zartikel.SORTIMENT_4, "1");

	if ( m_Doc.GetClioart()->BLOOD != 0 )
		strcpy (m_Doc.GetBuffer()->zartikel.CHARGENARTIKEL, "1");


	long s;
	int  fd;
	CString cd;
	char prdgrpcd[ L_CLIPRODUCTGRP_PRDGRPCD + 1 ] = {0};

	sql.Format( "select PRDGRPCD from CLIPRODUCTGRP where PRDNO=%ld", m_Doc.GetClioart()->PRDNO );	
	s = SqlOpenCs( &fd, sql );	
	if ( s == 0 )
	{
		while (SqlFetch( fd, 1, prdgrpcd, NULL ) == 0)
		{
			cd = prdgrpcd;
			cd.Trim();

			// --> prdgrpcd aus cliproductgrp mit prdno = clioart.prdno
			if (strcmp(cd, "PHYTO") == 0)
				m_Doc.GetBuffer()->zartikel.PHYTOPHARMAKON[0] = '1';
			else if (strcmp(cd, "BLOOD") == 0)
				m_Doc.GetBuffer()->zartikel.CHARGENARTIKEL[0] = '1';
			else if (strcmp(cd, "HOM") == 0)
				m_Doc.GetBuffer()->zartikel.HOMOEOPATHIKUM[0] = '1';
			else if (strcmp(cd, "ANTHROPOSOPHIC") == 0)
				m_Doc.GetBuffer()->zartikel.ANTHROPOSOPHIKUM[0] = '1';
			else if (strcmp(cd, "VET") == 0)
				m_Doc.GetBuffer()->zartikel.TIERARZNEI[0] = '1';
			else if (strcmp(cd, "MD") == 0)
				m_Doc.GetBuffer()->zartikel.MEDIZINPRODUKT[0] = '1';
			else if (strcmp(cd, "VACC") == 0)
				m_Doc.GetBuffer()->zartikel.IMPFSTOFF[0] = '1';
		}
	}
	SqlCloseCs( fd );
}

const char * CArtikelView::GetUnitCH(CString& csUnit)
{
	char UNIT[5];
	csUnit.TrimRight();
	csUnit.MakeUpper();
	strcpy ( UNIT, csUnit );	

	if ( strcmp ( UNIT, CResString::ex().getStrTblText(IDS_STRING339) ) == 0 )
		return "M"; 
	else if ( strcmp ( UNIT, CResString::ex().getStrTblText(IDS_STRING340) ) == 0 )
		return "PA";
	else if ( strcmp ( UNIT, CResString::ex().getStrTblText(IDS_STRING341) ) == 0 )
		return "ST";
	else if ( strcmp ( UNIT, CResString::ex().getStrTblText(IDS_STRING342) ) == 0 )
		return "GR";
	else if ( strcmp ( UNIT, CResString::ex().getStrTblText(IDS_STRING343) ) == 0 )
		return "PA";
	else
		return csUnit;
}

void CArtikelView::GetQtyCH(double dQty, char *temp)
{
	CString cs;
	int i;
	
	cs.Format("%10.3f", dQty);
	cs.SetAt(6, ',');

	i = atoi(cs);

	if (cs.Right(3) == "000")
	{
        sprintf (temp, "%ld", i);
	}
	else if (cs.Right(2) == "00")
	{
        sprintf (temp, "%ld%s", i, cs.Mid(6,2).GetString());
	}
	else if (cs.Right(1) == "0")
	{
        sprintf (temp, "%ld%s", i, cs.Mid(6,3).GetString());
	}
	else 
	{
        sprintf (temp, "%ld%s", i, cs.Mid(6,4).GetString());
	}
}

void CArtikelView::GetConcCH(char *Conc, char *temp)
{
	CString cs;
	int i;
	
	cs.Format("%s", Conc);
	i = cs.Find('.');

	if (i == -1)
	{
		sprintf (temp, "");
		return;
	}
	
	if (cs.Mid(i + 1, 3) == "000")
	{
		sprintf (temp, "%s", cs.Left(i).GetString());
	}
	else if (cs.Mid(i + 2, 2) == "00")
	{
		cs.SetAt(i, ',');
		sprintf (temp, "%s", cs.Left(i + 2).GetString());
	}
	else if (cs.Mid(i + 3, 1) == "0")
	{
		cs.SetAt(i, ',');
		sprintf (temp, "%s", cs.Left(i + 3).GetString());
	}
	else 
	{
		cs.SetAt(i, ',');
		sprintf (temp, "%s", cs.Left(i + 4).GetString());
	}
}

char * CArtikelView::GetDarCH_D(CString csDar)
{
	char DAR[40];
	csDar.TrimRight();
	csDar.MakeUpper();
	strcpy ( DAR, csDar );	

	if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING344) ) == 0 )
		return "GLO"; 
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING345) ) == 0 )
		return "GRA";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING346) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING347) ) == 0 )
		return "LSG";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING348) ) == 0 )
		return "KPS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING349) ) == 0 )
		return "LIQ";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING350) ) == 0 )
		return "CRE";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING351) ) == 0 )
		return "PLV";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING352) ) == 0 )
		return "GTT";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING353) ) == 0 )
		return "LSG";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING354) ) == 0 )
		return "GEL";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING355) ) == 0 )
		return "SPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING356) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING357) ) == 0 )
		return "OEL";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING358) ) == 0 )
		return "UNG";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING359) ) == 0 )
		return "DRG";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING360) ) == 0 )
		return "LOT";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING361) ) == 0 )
		return "LSG";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING362) ) == 0 )
		return "SUP";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING363) ) == 0 )
		return "GLO";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING364) ) == 0 )
		return "VAP";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING365) ) == 0 )
		return "GTT";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING366) ) == 0 )
		return "SIR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING367) ) == 0 )
		return "EMU";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING368) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING369) ) == 0 )
		return "PAS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING370) ) == 0 )
		return "ESS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING371) ) == 0 )
		return "BAL";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING372) ) == 0 )
		return "GLM";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING373) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING374) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING375) ) == 0 )
		return "GRA";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING376) ) == 0 )
		return "TTS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING377) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING378) ) == 0 )
		return "SUS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING379) ) == 0 )
		return "SUS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING380) ) == 0 )
		return "TAB";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING381) ) == 0 )
		return "SPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING382) ) == 0 )
		return "SPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING383) ) == 0 )
		return "PDR";
	else
		return "";
}

char * CArtikelView::GetDarCH_F(CString csDar)
{
	char DAR[40];
	csDar.TrimRight();
	csDar.MakeUpper();
	strcpy ( DAR, csDar );	

	if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING384) ) == 0 )
		return "GLO"; 
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING385) ) == 0 )
		return "GRA";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING386) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING387) ) == 0 )
		return "SOL";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING388) ) == 0 )
		return "CAP";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING389) ) == 0 )
		return "LIQ";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING390) ) == 0 )
		return "CRE";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING391) ) == 0 )
		return "PDR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING392) ) == 0 )
		return "GTT";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING393) ) == 0 )
		return "SOL";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING394) ) == 0 )
		return "GEL";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING395) ) == 0 )
		return "SPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING396) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING397) ) == 0 )
		return "HUI";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING398) ) == 0 )
		return "ONG";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING399) ) == 0 )
		return "DRG";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING400) ) == 0 )
		return "LOT";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING401) ) == 0 )
		return "SOL";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING402) ) == 0 )
		return "TM ";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING403) ) == 0 )
		return "SUB";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING404) ) == 0 )
		return "SUP";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING405) ) == 0 )
		return "SIR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING406) ) == 0 )
		return "GLO";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING407) ) == 0 )
		return "VAP";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING408) ) == 0 )
		return "GTT";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING409) ) == 0 )
		return "EMU";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING410) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING411) ) == 0 )
		return "PAS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING412) ) == 0 )
		return "ESS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING413) ) == 0 )
		return "BAU";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING414) ) == 0 )
		return "MAC";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING415) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING416) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING417) ) == 0 )
		return "TTS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING418) ) == 0 )
		return "GRA";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING419) ) == 0 )
		return "CPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING420) ) == 0 )
		return "SUS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING421) ) == 0 )
		return "SUS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING422) ) == 0 )
		return "TAB";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING423) ) == 0 )
		return "SPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING424) ) == 0 )
		return "SPR";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING425) ) == 0 )
		return "PDR";
	else
		return "";
}

char * CArtikelView::GetDfoZusatz_D(CString csDar)
{
	char DAR[40];
	csDar.TrimRight();
	csDar.MakeUpper();
	strcpy ( DAR, csDar );	

	if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING426) ) == 0 )
		return "INJ";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING427) ) == 0 )
		return "FILM";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING428) ) == 0 )
		return "INF";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING429) ) == 0 )
		return "URTINKT";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING430) ) == 0 )
		return "TROCKENSUB";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING431) ) == 0 )
		return "BIOTH";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING432) ) == 0 )
		return "OPHT";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING434) ) == 0 )
		return "MILCH";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING435) ) == 0 )
		return "EFF";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING436) ) == 0 )
		return "AROMA";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING437) ) == 0 )
		return "STICK";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING438) ) == 0 )
		return "ROLL ON";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING439) ) == 0 )
		return "KAU";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING440) ) == 0 )
		return "KONZ";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING441) ) == 0 )
		return "RET";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING442) ) == 0 )
		return "BIOTH";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING443) ) == 0 )
		return "LUTSCH";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING444) ) == 0 )
		return "INJ";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING445) ) == 0 )
		return "DIL";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING446) ) == 0 )
		return "PASTE";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING447) ) == 0 )
		return "LAC";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING448) ) == 0 )
		return "AEROS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING449) ) == 0 )
		return "SCHAUM";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING450) ) == 0 )
		return "NASEN";
	else
		return "";
}

char * CArtikelView::GetDfoZusatz_F(CString csDar)
{
	char DAR[40];
	csDar.TrimRight();
	csDar.MakeUpper();
	strcpy ( DAR, csDar );	

	if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING451) ) == 0 )
		return "INJ";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING452) ) == 0 )
		return "FILM";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING453) ) == 0 )
		return "PERF";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING454) ) == 0 )
		return "SECHE";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING455) ) == 0 )
		return "BIOTH";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING456) ) == 0 )
		return "OPHT";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING457) ) == 0 )
		return "LAIT";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING458) ) == 0 )
		return "EFF";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING459) ) == 0 )
		return "AROMAT";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING460) ) == 0 )
		return "STICK";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING461) ) == 0 )
		return "ROLL ON";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING462) ) == 0 )
		return "CROQ";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING463) ) == 0 )
		return "CONC";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING464) ) == 0 )
		return "RET";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING465) ) == 0 )
		return "BIOTH";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING466) ) == 0 )
		return "SUC";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING467) ) == 0 )
		return "INJ";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING468) ) == 0 )
		return "DIL";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING469) ) == 0 )
		return "PATE";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING471) ) == 0 )
		return "LAC";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING472) ) == 0 )
		return "AEROS";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING473) ) == 0 )
		return "MOUSSE";
	else if ( strcmp ( DAR, CResString::ex().getStrTblText(IDS_STRING474) ) == 0 )
		return "NASAL";
	else
		return "";
}

/* long CArtikelView::LeseGaldat( CString& cErrmld )
{
	long lStatusArt;
	long lStatusNam;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatusArt = m_Doc.ReadCgaloart ( cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if ( lStatusArt == 0 )
	{
		CpyFromGalOArt();
	}
	else if ( lStatusArt != 100 )
	{
		return lStatusArt;
	}

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatusNam = m_Doc.ReadCgalonam ( cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if ( lStatusNam == 0 )
	{
		CpyFromGalNam();
	}
	else if ( lStatusNam != 100 )
	{
		return lStatusNam;
	}

	if ( lStatusNam == 100 && lStatusArt == 100 )
		return 100;
	else
		return 0;
} */

long CArtikelView::LeseDataSemp( CString& cErrmld )
{
	long lStatus;
	
	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = m_Doc.ReadCDsOArt ( cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if ( lStatus == 0 )
	{
		CpyFromDsOArt();
	}
	
	return lStatus;
}

long CArtikelView::LeseLogIndex( CString& cErrmld )
{
	long lStatus;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = m_Doc.ReadClioart ( cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if ( lStatus == 0 )
		CpyFromLogIndex();

	return lStatus;
}
	
int CArtikelView::SucheSatz( )
{
	int suchen = 0;

	ChSelectDialog *dlg = NewSuchDialog();

	dlg->RestoreAuswahlIndex( m_nAuswahlIndex );
	dlg->RestoreAuswahlIndex2( m_nAuswahlIndex2 );

	if ( dlg->DoModal() == IDOK )
	{
		if ( PrimeKeyOfSelectedRecord( ) )
		{
			long lStatus;
			CString cErrmld;

			KeySetInput();
			lStatus = LeseSatz( cErrmld );
			if ( lStatus != 0 )
			{
				MsgBoxOK( cErrmld );
			}
			else
			{
				ShowFields();
				SetArticleCodeEditCtrl();
				suchen = 1;
			}
		}
	}
	m_nStatus = 0;
	GotoFirstKey();

	m_nAuswahlIndex = dlg->GetAuswahlIndex( );
	m_nAuswahlIndex2 = dlg->GetAuswahlIndex2( );
	delete dlg;

	return suchen;
}

int CArtikelView::NextSatz( )
{
	if ( PrimeKeyOfNextRecord( ) )
	{
		long lStatus;
		CString cErrmld;

		KeySetInput();
		lStatus = LeseSatz( cErrmld );
	
		if ( !(lStatus == 0 || lStatus == 100 ) )
		{
			MsgBoxOK( cErrmld );
			return 0;
		}
		
		// initialize pages
		for ( int nr = 0; nr < m_pSheet->GetPageCount(); nr++ )
			m_bWasActive[nr] = FALSE;

		ShowFields();
		SetArticleCodeEditCtrl();

		if ( m_nStatus != 0 )
			EnablePageFields( TRUE );	// wegen der Preise	
//			EnableFields( TRUE );		// wegen der Preise

		if ( lStatus == 100 )
		{
			SetValidation( FALSE );	
			((CEkZdpApp*) AfxGetApp())->MeldRecordWasDeleted( );
		}

		if ( m_nStatus == 0 )
			GotoFirstKey();
		else
			GotoFirstField();
		return 1;
	}
	else
		return 0;
}

int CArtikelView::PrevSatz( )
{
	if ( PrimeKeyOfPrevRecord( ) )
	{
		long lStatus;
		CString cErrmld;

		KeySetInput();
		lStatus = LeseSatz( cErrmld );
	
		if ( !(lStatus == 0 || lStatus == 100 ) )
		{
			MsgBoxOK( cErrmld );
			return 0;
		}

		// initialize pages
		for ( int nr = 0; nr < m_pSheet->GetPageCount(); nr++ )
			m_bWasActive[nr] = FALSE;

		ShowFields();
		SetArticleCodeEditCtrl();

		if ( m_nStatus != 0 )	
			EnablePageFields( TRUE );	// wegen der Preise			
//			EnableFields( TRUE );		// wegen der Preise

		if ( lStatus == 100 )
		{
			SetValidation( FALSE );	
			((CEkZdpApp*) AfxGetApp())->MeldRecordWasDeleted( );
		}

		if ( m_nStatus == 0 )
			GotoFirstKey();
		else
			GotoFirstField();
		return 1;
	}
	else
		return 0;
}

int CArtikelView::BearbeiteSatz( )
{
/*
	if ( m_nStatus > 0 || !IsLastKeyFocus() )
	{
		m_Page[m_pSheet->GetActiveIndex()]->NextDlgCtrl();
		return 0;
	}
*/
	if ( m_nStatus > 0 )
	{
		m_Page[m_pSheet->GetActiveIndex()]->NextDlgCtrl();
		return 0;
	}

	if ( !IsLastKeyFocus() )
	{
		NextDlgCtrl();
//		((CDialogMultiLang*) this)->NextDlgCtrl( ); 
		return 0;
	}

	CString cErrmld;

	if ( FALSE == SetArticleNoEditCtrl( cErrmld ) ){
		return -1;
	}

	KeyGetInput();

	// falls nächste Nummer selektiert, aber manuell überschrieben wurde
	if (m_Doc.GetNummerekUpdate())
	{
		if (m_pBufZartikel->ARTIKEL_NR != m_Doc.GetNummerek()->NR)
		{
			m_Doc.SetNummerekUpdate (false);
		}
	}

	if ( !ValidateKey() ) 
	{
		GotoFirstKey();
		return 0;
	}

	// Taxtabelle
	long lStatus;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = ((CEkZdpApp*) AfxGetApp())->LeseTaxtabelle( cErrmld);
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
	if ( lStatus != 0 )
	{
		m_nStatus = 0;
		MsgBoxOK( cErrmld );
		return 0;
	}

	lStatus = LeseSatz( cErrmld );
	if ( !( lStatus == 0 || lStatus == 100 ) )
	{
		m_nStatus = 0;
		MsgBoxOK( cErrmld );
		return 0;
	}

	// Hinweis in Kroatien / Bulgarien / Serbien, wenn neue PZN nicht die nächste fortlaufende ist
	if ((IsCountry("HR") || IsCountry("BG") || IsCountry("RS")) && lStatus == 100)
	{
		if (!m_Doc.GetNummerekUpdate())
		{
			if ( MsgBoxYesNo( CResString::ex().getStrTblText(IDS_STRING10195), 
				 MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES )	
			return 0;
		}
	}

	if ( lStatus == 0 )
		m_nStatus = 1;
	else
		m_nStatus = 2;

	// bei Neuanlagen Basisartikel suchen, wenn Kopierfunktion an
	CEkZdpApp *theApp = ( CEkZdpApp *) AfxGetApp();
	bool bArtikelKopie = false;
	
	if ( lStatus == 100 && theApp->m_bArtikelKopie )
	{
		bool bKopierVerarbeitung = false;
        int iSavePzn = m_pBufZartikel->ARTIKEL_NR;

		// fragen, ob nochmal gleicher Basisartikel oder neue Auswahl erfolgen soll
		if ( theApp->m_KopierPzn > 0 && MsgBoxYesNo( CResString::ex().getStrTblText(IDS_STRING995) ) == IDYES )
		{
			m_pBufZartikel->ARTIKEL_NR = theApp->m_KopierPzn;
			bKopierVerarbeitung = true;
		}
		else
		{
			ChSelectDialog *dlg = NewSuchDialog();

			dlg->RestoreAuswahlIndex( m_nAuswahlIndex );
			dlg->RestoreAuswahlIndex2( m_nAuswahlIndex2 );

			if ( dlg->DoModal() == IDOK )
			{
				// MsgBoxOK(CResString::ex().getStrTblText(IDS_STRING475));
				if ( PrimeKeyOfSelectedRecord( ) )
				{
					bKopierVerarbeitung = true;
					theApp->m_KopierPzn = m_pBufZartikel->ARTIKEL_NR;
				}
			}
		}
		
		if ( bKopierVerarbeitung )
		{
			long ret;
			CString errmsg;

			// KeySetInput();

			// Stati des anzulegenden Satzes sichern
			m_Doc.SaveStati ( errmsg );

			ret = LeseSatz( errmsg );

			// Stati des anzulegenden Satzes wiederherstellen
			m_Doc.RestoreStati ( errmsg );

			// PZN in gelesenen Puffern auf die neue umschießen
			m_Doc.ChangePznInBuffer ( iSavePzn, errmsg );

			if ( ret != 0 )
			{
				MsgBoxOK( errmsg );
			}
			else
			{
				ShowFields();
				bArtikelKopie = true;
			}
		}
	}

	// bei Neuanlagen in Schweiz: Werte aus LogIndex-Tabellen vorblenden!
	if ( lStatus == 100 && !bArtikelKopie && IsCountry("CH") )
	{
		lStatus = LeseLogIndex( cErrmld ); 
		
		if ( !( lStatus == 0 || lStatus == 100 ) )
		{
			m_nStatus = 0;
			MsgBoxOK( cErrmld );
			return 0;
		}
		
		if ( lStatus == 100 )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING476) );
		else 
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING477) );
	}

	// initialize pages
	for ( int nr = 0; nr < m_pSheet->GetPageCount(); nr++ )
		m_bWasActive[nr] = FALSE;

	ShowFields();
	EnableFields( TRUE );
	GotoFirstField();

	m_Doc.InitArticleno_save();

	// speziell bei ArtikelPflege: hier IFA-Update = FALSE
	m_Doc.SetIfaPflege( FALSE );

	if ( m_nStatus == 1 )
		return 1;
	else
		return 2;
}


int CArtikelView::StelleAlleFragen() 
{
	CString cMeld;
	if ( m_Page0.AenderungsHinweis( cMeld ) )
	{
		if ( MsgBoxYesNo( cMeld ) == IDYES ) 
			return -1;
	}

	// Setzen von KZ´s auf Basis von hinterlegten Werten im Hersteller:
	int iStat;
	CString Name;
	CString Errmld;
	CString PPE;
	CString cZentralppeList;
	CString cEKORIGINALHS;
	CString cBESTELL_NUR_OZEK;
	CString cREZEPTPFL;
	CString cAPOTHEKENPFL;
	CString cNETTOARTIKEL;
	long	KONSIG_PARTNER;
	short   BUSINESSTYPENO;
	short   ANRH_ZWING_EINZIG;
	short   VERTRIEBSCLUBNR;
	short	BEZUGSSPERRE;

	CRdHerstel	m_RD_HERSTELLER;
	 
	iStat = m_RD_HERSTELLER.IPlausi( ((GetBuffer())->zartikel).HERSTELLER_NR, Name, PPE, cZentralppeList,
									cEKORIGINALHS, cBESTELL_NUR_OZEK, cREZEPTPFL, cAPOTHEKENPFL, cNETTOARTIKEL, KONSIG_PARTNER,
									BUSINESSTYPENO, ANRH_ZWING_EINZIG, VERTRIEBSCLUBNR, BEZUGSSPERRE, &Errmld);

	if ( IsNeuanlage() || ((GetBuffer())->zartikel).HERSTELLER_NR != ((GetOldBuffer())->zartikel).HERSTELLER_NR )
	{
		if ( iStat == 0 && !cEKORIGINALHS.IsEmpty() && !cBESTELL_NUR_OZEK.IsEmpty() )
		{
			if ((((GetBuffer())->zartikel).REZEPTPFL[0]	   ==  cREZEPTPFL.GetAt(0)    
															&& cREZEPTPFL.GetAt(0)    == '1' ) ||
				(((GetBuffer())->zartikel).APOTHEKENPFL[0] ==  cAPOTHEKENPFL.GetAt(0) 
															&& cAPOTHEKENPFL.GetAt(0) == '1' ) ||
				(((GetBuffer())->zartikel).NETTOARTIKEL[0] ==  cNETTOARTIKEL.GetAt(0) 
															&& cNETTOARTIKEL.GetAt(0) == '1' )		)
			{
				if (cEKORIGINALHS.GetAt(0) == '1')
					((GetBuffer())->zartikel).EKORIGINALHS[0] = '1';
				//else
				//	((GetBuffer())->zartikel).EKORIGINALHS[0] = '0';

				if (cBESTELL_NUR_OZEK.GetAt(0) == '1')
					((GetBuffer())->zartikel).BESTELL_NUR_OZEK[0] = '1';
				//else
				//	((GetBuffer())->zartikel).BESTELL_NUR_OZEK[0] = '0';

				if (BEZUGSSPERRE > 0)
					((GetBuffer())->zartikel).BEZUGSSPERRE = BEZUGSSPERRE;
			}	
			/*else
			{
				((GetBuffer())->zartikel).BESTELL_NUR_OZEK[0] = '0';
				((GetBuffer())->zartikel).EKORIGINALHS[0] = '0';
			}*/
		}
	}

	// Warnunghinweis wenn Kennzeichen BTM und BTM-Gruppe oder BTM-Faktor inkonsistent (Deutschland)
	CString cWgr;
	cWgr = ((GetBuffer())->zartwg[5]).WARENGRUPPE;
	cWgr.TrimLeft();
	cWgr.TrimRight();

	if (IsCountry("D"))
	{
		// bei diesen beiden Meldungen den Nein-Button vorblenden
		if ( ((GetBuffer())->zartikel).BTM[0] == '1' && (cWgr.IsEmpty() || cWgr == "00000") )
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING478) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		if ( ((GetBuffer())->zartikel).BTM[0] == '0' && !cWgr.IsEmpty() && cWgr != "00000"  )
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING479) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		if ( ((GetBuffer())->zartikel).BTM[0] == '1' && 
	 		 ((GetBuffer())->zartikel).BTM_FAKTOR == 0 )
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING10263) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		// Wird frühestens ab Version 16.130 einkommentiert
		//// Warnhinweis, wenn Liefernaten-Nahrungsergänzung nicht zum Artikel passt
		//if (   GetBuffer()->zartikel.NAHRUNGSTEST[0] != ' '
		//	&& GetBuffer()->zartikel.NAHRUNGSERGAENZUNG[0] != 'G'
		//	&& m_Doc.CheckLieferNahrungsergänzung())
		//{
		//	cMeld = _T(CResString::ex().getStrTblText(IDS_STRING1504));
		//	if (MsgBoxYesNo(cMeld, MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
		//		return -1;
		//}

		// Wird frühestens ab Version 16.130 einkommentiert
		//// Warnhinweis, wenn Lieferant kein Bio-Zertifikat hat
		//if (   GetBuffer()->zartikel.BIOSIEGEL == 1
		//	&& GetBuffer()->zartikel.NAHRUNGSTEST[0] != ' '
		//	&& GetBuffer()->zartikel.NAHRUNGSERGAENZUNG[0] != 'G'
		//	&& m_Doc.CheckLieferHatKeinBioZertifikat())
		//{
		//	cMeld = _T(CResString::ex().getStrTblText(IDS_STRING1503));
		//	if (MsgBoxYesNo(cMeld, MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
		//		return -1;
		//}

		// Prüfung, ob bei Gefahrstoffen die Einheit die begrenzte Menge überschreitet und die entsprechenden Sperren nicht gesetzt sind
		CString csAdr2011 = m_Doc.ReadAdr2011();
		csAdr2011.Trim();

		int i = csAdr2011.Find(' ');

		long lAdr2011_Menge			= atoi(csAdr2011.Left(i));
		CString csAdr2011_Einheit	= csAdr2011.Right(csAdr2011.GetLength()-i-1);

		CString csEinheit = GetBuffer()->zartikel.EINHEIT;
		csEinheit.Trim();

		i = csEinheit.Find(' ');

		long lEinheit_Menge			= atoi(csEinheit.Left(i));
		CString csEinheit_Einheit	= csEinheit.Right(csEinheit.GetLength()-i-1);

		if ((((GetBuffer())->zartikel).NAHRUNGSERGAENZUNG[0] != 'G' ||
			 ((GetBuffer())->zartikel).ZENTR_EKSPERRE[0] != '1' ) &&
			 !csAdr2011.IsEmpty())
		{
			// wenn im ADR-Feld nur eine 0 steht, muss der Artikel immer gesperrt werden
			if (csAdr2011 == "0")
			{
				cMeld = _T( CResString::ex().getStrTblText(IDS_STRING109) );
				if ( MsgBoxYesNo( cMeld ) == IDYES )
					return -1;
			}
			// Hinweis, falls kein Vergleich der Mengen durchgeführt werden kann
			else if (csAdr2011_Einheit != csEinheit_Einheit)
			{
				cMeld = _T( CResString::ex().getStrTblText(IDS_STRING108) );
				if ( MsgBoxYesNo( cMeld ) == IDYES )
					return -1;
			}
			else if (lAdr2011_Menge < lEinheit_Menge)
			{
				cMeld = _T( CResString::ex().getStrTblText(IDS_STRING107) );
				if ( MsgBoxYesNo( cMeld ) == IDYES )
					return -1;
			}
		}
	}

	if (IsCountry("BG"))
	{
		// Warnhinweis, wenn ABDA-Code und Sortiment2 inkonsistent (Bulgarien)
		cWgr = ((GetBuffer())->zartwg[3]).WARENGRUPPE;

		// bei diesen beiden Meldungen den Nein-Button vorblenden
		if ( ((GetBuffer())->zartikel).SORTIMENT_2[0] == '1' && cWgr.GetAt(0) != '2' )
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING1216) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		if ( ((GetBuffer())->zartikel).SORTIMENT_2[0] != '1' && cWgr.GetAt(0) == '2' )
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING1217) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		// Index des aktuell gültigen Preises ermitteln 
		int i;

		if (((GetBuffer())->artpreis[0]).DATUMGUELTIGAB == 0)
			i = 1;
		else
			i = 0;

		if (((GetBuffer())->artpreis[i]).AEP > 0.02 && ((GetBuffer())->zartikel).SORTIMENT_3[0] == '1')
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING1218) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		if (((GetBuffer())->artpreis[i]).AEP <= 0.02 && ((GetBuffer())->zartikel).SORTIMENT_3[0] != '1')
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING1219) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}
	}

	if (IsCountry("CH"))
	{
		// bei diesen beiden Meldungen den Nein-Button vorblenden
		if ( ((GetBuffer())->zartikel).REZEPTPFL[0] == '1' && 
			 ((GetBuffer())->zartswitzerland).IKS_CODE[0] != 'A' && ((GetBuffer())->zartswitzerland).IKS_CODE[0] != 'B')
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING480) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		if ( ((GetBuffer())->zartikel).REZEPTPFL[0] != '1' && 
			 ( ((GetBuffer())->zartswitzerland).IKS_CODE[0] == 'A' || ((GetBuffer())->zartswitzerland).IKS_CODE[0] == 'B') )
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING481) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		if ( ((GetBuffer())->zartswitzerland).VERTRBIND_LISTE_C[0] == '1' && 
			 ((GetBuffer())->zartswitzerland).IKS_CODE[0] != 'C' )
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING482) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		if ( ((GetBuffer())->zartswitzerland).VERTRBIND_LISTE_C[0] == '0' && 
			 ((GetBuffer())->zartswitzerland).IKS_CODE[0] == 'C' )
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING483) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		if ( ((GetBuffer())->zartswitzerland).VERTRBIND_LISTE_D[0] == '1' && 
			 ((GetBuffer())->zartswitzerland).IKS_CODE[0] != 'D' )
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING484) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		if ( ((GetBuffer())->zartswitzerland).VERTRBIND_LISTE_D[0] == '0' && 
			 ((GetBuffer())->zartswitzerland).IKS_CODE[0] == 'D' )
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING485) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;
		}

		// überprüfe differenz zwischen Grosso und AGP
		double Grosso_Diff_Max_PCT = 20.0f;
		for (int i=0;i<4;i++)
		{
			double prcGrosso = ((GetBuffer())->artpreis[i]).GROSSO;
			double prcAGP = ((GetBuffer())->artpreis[i]).AGP;
			if ((prcGrosso * prcAGP) > 0)
			{
				double ratio = (prcGrosso > prcAGP ? prcGrosso / prcAGP : prcAGP / prcGrosso);
				if (((ratio - 1.0f) *100.0f) > Grosso_Diff_Max_PCT)
				{
					cMeld = CResString::ex().getStrTblText(IDS_STRING1551);
					if (MsgBoxYesNo(cMeld, MB_ICONQUESTION | MB_DEFBUTTON2) != IDYES)
						return -1;
				}
			}
		}
	}

	// Warnhinweis, wenn neuer Preis mindestens ein Jahr in der Zukunft (für Österreich)
	int iDatDiff;

	if (((GetBuffer())->artpreis[0]).DATUMGUELTIGAB > 0 &&
		((GetBuffer())->artpreis[0]).DATUMGUELTIGAB > ::Today())
	{
		iDatDiff = ((GetBuffer())->artpreis[0]).DATUMGUELTIGAB - ::Today();

		if (iDatDiff >= 10000)
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING488) );
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
				return -1;	
		}
	}

	if (IsCountry("F"))
	{
		// in Frankreich Warnhinweis wenn Mwst-Kz = 0 gesetzt
		if ( ((GetBuffer())->artpreis[0]).KE_MWST[0] == '0' &&
			 ((GetOldBuffer())->artpreis[0]).KE_MWST[0] != '0' )
		{
			cMeld = _T( CResString::ex().getStrTblText(IDS_STRING10277) );
			if ( MsgBoxYesNo( cMeld ) != IDYES )
				return -1;	
		}
	}
	// Warnhinweis wenn Bestandsbuchung auf nicht aktiv gesetzt
	if ( ((GetBuffer())->zartikel).BESTANDSBUCHUNG[0] == '0' &&
		 ((GetOldBuffer())->zartikel).BESTANDSBUCHUNG[0] != '0' )
	{
		cMeld = _T( CResString::ex().getStrTblText(IDS_STRING10268) );
		if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
			return -1;	
	}

	// Warnhinweis wenn Artikel geloescht ( Peetz 2.6.98 )
	if ( ((GetBuffer())->zartikel).ARTIKEL_GELOESCHT[0] == '1' &&
		 ((GetOldBuffer())->zartikel).ARTIKEL_GELOESCHT[0] == '1' )
	{
		cMeld = _T( CResString::ex().getStrTblText(IDS_STRING489) );
		if ( MsgBoxYesNo( cMeld ) != IDYES )
			return -1;	
	}
	else
	{
		if ( ! (( CEkZdpApp *)AfxGetApp())->YouWantToStoreRecord( ) )
			return -1;
	}

	return 0;
}

int CArtikelView::SpeichereSatz( )
{
//	CString cMeld;

	// Aktuelles Feld verlassen 
	// damit Killfocus Ausgefuehrt wird und die aktuelle Eingabe
	// realisiert wird
//	SetValidation( FALSE ); // wegen Change focus
//	m_Page[m_pSheet->GetActiveIndex()]->NextDlgCtrl();
//	SetValidation( TRUE );  // wegen Change focus

	DataExchangeToBuffer( );

	if ( !Validate() ) return -1;

	// SetDialog( FALSE ) -> : bei Killfocus wird Keine Validierung
	// oder Postproc durchgefuehrt
	// -> gleiches Verhalten ob mit oder ohne Abfrage.
	// ( bei Abfrage KillFocus(), ohne Abfrage kein KillFocus() 
	int iStat;
	SetDialog( FALSE );	
	iStat = StelleAlleFragen();
	SetDialog( TRUE );	
	if ( iStat == -1 ) return -1;

	CString cErrmld;
	long lStatus;

	CString code;
	m_ARTIKEL_CODE.GetWindowText(code);

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = m_Doc.StoreRecord( cErrmld, code );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if ( lStatus == 0 )
	{
		m_bChanged = TRUE;
		m_nStatus = 0;
		EnableFields( FALSE );
		GotoFirstKey();
//		return 1;	// blaettern aus
		return 2;	// weiterblaettern
	}
	MsgBoxOK( cErrmld );
	return 0;
}

int CArtikelView::LoescheSatz( )
{
	CString cErrmld;

//	Artikel Loeschen ueber Loeschkennzeichen
	SetValidation( FALSE ); // wegen Change focus
	MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING490) );
	SetValidation( TRUE );
	return -1;

/* unreachable code!
	SetValidation( FALSE ); // wegen Change focus
	bFrage = (( CEkZdpApp *)AfxGetApp())->YouWantToDeleteRecord( );
	SetValidation( TRUE );
	if ( !bFrage ) return -1;

    DataExchangeToBuffer( );

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = m_Doc.DeleteRecord ( cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
	if ( lStatus == 0 )
	{
		m_bChanged = TRUE;
		m_nStatus = 0;
		EnableFields( FALSE );
		GotoFirstKey();
//		return 1;	// blaettern aus
		return 2;	// weiterblaettern
	}
	MsgBoxOK( cErrmld );
	return 0;
*/
}

int CArtikelView::UndoSatz( )
{
	if ( m_nStatus == 0 )
	{
		m_Doc.FreeBufferDesc( );
		CloseSuche();
		m_Page0.ResetVkn();

		// auch Page2 wg. Original-PZN
		m_Page1.ResetVkn();

		m_Page2.ResetVkn();

		// wg. Darreichform-Rücksetzung in der Schweiz
		if (IsCountry("CH"))
		{
			m_Page4CH.ResetVkn();
		}
/*		else if (IsCountry("A"))
		{
			m_Page4A.ResetVkn();
		} */
		else if (IsCountry("F"))
		{
			m_Page4F.ResetVkn();
		}
		else if (IsCountry("BG"))
		{
			m_Page4BG.ResetVkn();
		}
		else if (IsCountry("RS"))
		{
			m_Page4RS.ResetVkn();
		}

		return 0;
	}					
	m_nStatus = 0;
	m_ARTIKEL_NR.SetWindowText("0");
	EnableFields( FALSE );
	GotoFirstKey();

	return 1;
}

void CArtikelView::CopySatz( )
{
	DataExchangeToBuffer( );
    m_Doc.StoreBuffer();
}

void CArtikelView::CutSatz( )
{
	CString cErrmld;
	DataExchangeToBuffer( );
	m_Doc.StoreBuffer();
	if ( m_Doc.InitRecord( cErrmld ) != 0 )
		MsgBoxOK( cErrmld );
	else
		ShowFields();
}

void CArtikelView::PasteSatz( )
{
	m_Doc.RestoreBuffer();
	ShowFields();
}

void CArtikelView::InitPflegeDocument( char* Anwender )
{
	CString cErrmld;
	m_Doc.InitPflegeDesc( Anwender );
}

void CArtikelView::ReleasePflegeDocument( )
{
	ReleaseIfa();
}

void CArtikelView::UpdatePflegeDocument( )
{
}

/////////////////////////////////////////////////////////////////////////////
// CBlieferView message handlers

void CArtikelView::OnInitialUpdate() 
{

	CFormViewMultiLang::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	InitPflege();
//	m_Doc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
//	InitPflegeDocument( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
	m_nStatus = 0;
}

void CArtikelView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class

	CFormViewMultiLang::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
//		ShowFields();
		if ( pActivateView != pDeactiveView )
		{
			m_bChanged = FALSE;  // noch keine Aenderung
			m_Doc.SetTagesdatum( ::Today() );
			EnableFieldsIfa();
	 		GotoFirstKey();
		}
	}
}

////////////////////////////////////////////
// wenn mit PropertyPages

int CArtikelView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	if (CFormViewMultiLang::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	// Create the modeless property sheet. You should add the
	// property pages before creating the property sheet

	ASSERT(m_pSheet);

	m_pSheet->AddPage(&m_Page0);  
	m_pSheet->AddPage(&m_Page1);
 	m_pSheet->AddPage(&m_Page2);
 	m_pSheet->AddPage(&m_Page3);

	m_Page[0] = &m_Page0;  
	m_Page[1] = &m_Page1;  
	m_Page[2] = &m_Page2;  
	m_Page[3] = &m_Page3;  

	// Seite 5 landesspezifisch
	if (IsCountry("A"))
	{
        m_pSheet->AddPage(&m_Page4A);
		m_Page[4] = &m_Page4A;  
	} 
	else if (IsCountry("CH"))
	{
        m_pSheet->AddPage(&m_Page4CH);
		m_Page[4] = &m_Page4CH;  
	} 
	else if (IsCountry("D"))
	{
        m_pSheet->AddPage(&m_Page4D);
		m_Page[4] = &m_Page4D;  
	} 
	else if (IsCountry("F")) 
	{
        m_pSheet->AddPage(&m_Page4F);
		m_Page[4] = &m_Page4F;  
	} 
	else if (IsCountry("HR"))
	{
        m_pSheet->AddPage(&m_Page4HR);
		m_Page[4] = &m_Page4HR;  
	}
	else if (IsCountry("BG"))
	{
        m_pSheet->AddPage(&m_Page4BG);
		m_Page[4] = &m_Page4BG;  
		m_pSheet->AddPage(&m_Page5BG);
		m_Page[5] = &m_Page5BG;
	}
	else if (IsCountry("RS"))
	{
        m_pSheet->AddPage(&m_Page4RS);
		m_Page[4] = &m_Page4RS;  
	}

	if (!m_pSheet->Create(this, WS_SYSMENU | WS_CHILD | WS_VISIBLE, 0))
	{
		return -1;
	}

	m_pSheet->SetImageList(IDB_BM_PAGE, 16, 1, RGB(255,0,0));

	CRect rectSheet, rectWindow;
	m_pSheet->GetWindowRect(rectSheet);
	rectWindow = rectSheet;
	CalcWindowRect(rectWindow);

	// Adjust the positions of the frame and property sheet
	int leftpos =  10;  // 20;
	int toppos  =  70;  // 60;

	SetWindowPos(NULL, rectWindow.left,
					   rectWindow.top, 
					   rectWindow.Width()  + leftpos,
					   rectWindow.Height() + toppos,
					   SWP_NOZORDER | SWP_NOACTIVATE);

	m_pSheet->SetWindowPos(NULL, leftpos, toppos,
						   rectSheet.Width(),
						   rectSheet.Height(), 
						   SWP_NOZORDER | SWP_NOACTIVATE);

/*
	int toppos  =  80;	// 60;
	SetWindowPos(NULL, rectWindow.left,
					   rectWindow.top, 
					   rectWindow.Width() + 10,
					   rectWindow.Height() + toppos,
					   SWP_NOZORDER | SWP_NOACTIVATE);

	m_pSheet->SetWindowPos(NULL, leftpos, toppos,
						   rectSheet.Width(),
						   rectSheet.Height() + toppos, 
						   SWP_NOZORDER | SWP_NOACTIVATE);
*/
	m_pSheet->ResetPlegePage();

	return 0;
}

int CArtikelView::GotoPage( UINT nr )
{
	nr--;
//	ASSERT((int)nr < m_pSheet->GetPageCount());
	if ( (int)nr < m_pSheet->GetPageCount() )
	{
		m_pSheet->SetActivePage(nr);
		if ( m_nStatus > 0 )
			m_pSheet->SetPlegePage();	
//		SetHeaderInfo();
	}
	return 1;
}

//////////////////////////////////////
// NextDlgCtrl

void CArtikelView::NextDlgCtrl()
{
	CWnd *pWnd = GetFocus();
	if ( pWnd == GetDlgItem( IDC_PB_ARTIKEL_SELIFA ) )
	{
		OnPbArtikelSelifa();
		GotoFirstKey();
	}
	else if ( pWnd == GetDlgItem( IDC_PB_ARTIKEL_VORBLIFA ) )
	{
		OnPbArtikelVorblifa();
		GotoFirstKey();
	}
	else if ( pWnd == GetDlgItem( IDC_PB_ARTIKEL_RUEBLIFA ) )
	{
		OnPbArtikelRueblifa();
		GotoFirstKey();
	}
	else if ( pWnd != GetDlgItem( IDC_ED_ARTIKEL_ARTIKEL_NR ) )
		GotoFirstKey();
	

/*
	((CDialogMultiLang*) this)->NextDlgCtrl( ); 

	CWnd *pWnd = GetFocus();
	if ( pWnd == GetDlgItem( IDC_PB_ARTIKEL_SELIFA )   ||
	     pWnd == GetDlgItem( IDC_PB_ARTIKEL_VORBLIFA ) ||
	     pWnd == GetDlgItem( IDC_PB_ARTIKEL_RUEBLIFA )    )
		((CDialogMultiLang*) this)->NextDlgCtrl( ); 
*/
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// IFA

void CArtikelView::SetIfaInfo( long lStatus )
{
	CString cInfo;
	if ( lStatus == 0 )
	{
		cInfo = _T(CResString::ex().getStrTblText(IDS_STRING491));
	}
	else if ( lStatus == 100 )
	{
		cInfo = _T(CResString::ex().getStrTblText(IDS_STRING492));
	}
	else
		cInfo = _T("");

	GetDlgItem( IDC_ST_ARTIKEL_IFAINFO )->SetWindowText( cInfo );
}

long CArtikelView::ReadSatzUeberIfa( long IfaNr, long SatzNr, CString& cErrmld )
{
	long lStatus;

	lStatus = ((CEkZdpApp*) AfxGetApp())->LeseTaxtabelle( cErrmld);
	if ( lStatus != 0 ) return -1;

	lStatus = m_Doc.ReadRecord_Ifa( IfaNr, SatzNr, cErrmld );
	if ( lStatus != 0 )
	{
		char err[100];
		sprintf( err, CResString::ex().getStrTblText(IDS_STRING493), IfaNr, SatzNr );
		cErrmld += err;
		if ( lStatus == 100 ) lStatus = -1;
		return lStatus;
	}

	m_pBufZartikel->ARTIKEL_NR = m_pIfaBuf->A00PZN;

	SetPreferredArticleCodeEditCtrl();

	lStatus = m_Doc.ReadRecord ( cErrmld );
	if ( lStatus == 100 )
	{
		if ( m_Doc.IfaToArtikel( cErrmld ) != 0 )
		{	
			cErrmld += CResString::ex().getStrTblText(IDS_STRING494);
			return -1;
		}
	}

	return lStatus;
}

long CArtikelView::LeseSatzUeberIfa( long IfaNr, long SatzNr )
{
	long lStatus;
	CString cErrmld;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = ReadSatzUeberIfa( IfaNr, SatzNr, cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if ( !( lStatus == 0 || lStatus == 100 ) )
		MsgBoxOK( cErrmld );
	else
	{
		ShowFields();
		sprintf(m_ARTCODE, "%ld", m_pBufZartikel->ARTIKEL_NR);
	}
	SetIfaInfo( lStatus );
	return lStatus;
}

long CArtikelView::LesePznAltSatzUeberIfa( long PhzAlt )
{
	long lStatus;
	CString cErrmld;

	// auf jeden Fall lesen
	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = m_Doc.ReadRecord_Zartikel_PhzAlt( PhzAlt, cErrmld );
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
//	if ( lStatus == 100 && atol( m_pIfaBuf->C_PHZALT ) == 0 )
	if ( lStatus == 100 && PhzAlt == 0 )
		 lStatus = 0;
	else if ( lStatus == 100 )
	{
		cErrmld.Format( CResString::ex().getStrTblText(IDS_STRING495), PhzAlt );
//			atol( m_pIfaBuf->C_PHZALT ) );
		MsgBoxOK( cErrmld );
	}
	else if ( lStatus != 0 )
	{
		cErrmld += CResString::ex().getStrTblText(IDS_STRING496);
		MsgBoxOK( cErrmld );
	}
	return lStatus;
}

void CArtikelView::OnPbArtikelNextpzn() 
{
	CString cErrmld;
	long lStatus;

	lStatus = m_Doc.ReadNummerek(cErrmld);

	if (lStatus == 0)
	{
		m_pBufZartikel->ARTIKEL_NR = m_Doc.GetNummerek()->NR;
		m_Doc.SetNummerekUpdate( TRUE );
		m_ARTIKEL_NR.p_SetInput();
		sprintf(m_ARTCODE, "%ld", m_pBufZartikel->ARTIKEL_NR);
		m_ARTIKEL_CODE.p_SetInput();
		//m_ARTIKEL_NR.SetFocus();
		m_ARTIKEL_CODE.SetFocus();
	}
	else
	{
		MsgBoxOK(cErrmld);
	}

}

void CArtikelView::OnPbArtikelSelifa() 
{
	// TODO: Add your control notification handler code here

	((CEkZdpApp*) AfxGetApp())->GotoIfa( 2 );

	// aendern, wenn bei sichtbarem IFA geblaettert werden kann !!!!!!!!!!!!!!!
	m_dlg.EnableFields( m_Pos_Vorblifa,  FALSE );
	m_dlg.EnableFields( m_Pos_Rueblifa,  FALSE );
	m_dlg.EnableFields( m_Pos_Uebernifa, FALSE );
	m_dlg.EnableFields( m_Pos_Selifa,    FALSE );
}

void CArtikelView::OnPbArtikelVorblifa() 
{
	// TODO: Add your control notification handler code here
	long lStatus;
	if ( *m_pDlgIfa != NULL )
	{
		long IfaNr;
		long SatzNr;
		long PhzNr;  // hier nicht benoetigt
		if ( (*m_pDlgIfa)->PrimeKeyOfNextRecord( &IfaNr, &SatzNr, &PhzNr ) == 0 )
		{
			if ( !m_bRueblifaEnabled )
			{
				m_bRueblifaEnabled = TRUE;
				m_dlg.EnableFields( m_Pos_Rueblifa, m_bRueblifaEnabled );
			}
			lStatus = LeseSatzUeberIfa( IfaNr, SatzNr );
//			if ( m_pDlgIfa->IsWindowVisible() )
//				m_pDlgIfa->GoOn( );
		}
		else
		{
			m_bVorblIfaEnabled = FALSE;
			m_dlg.EnableFields( m_Pos_Vorblifa, m_bVorblIfaEnabled );
		}
	}
	GotoFirstKey();
}

void CArtikelView::OnPbArtikelRueblifa() 
{
	// TODO: Add your control notification handler code here
	long lStatus;
	if ( *m_pDlgIfa != NULL )
	{
		long IfaNr;
		long SatzNr;
		long PhzNr;  // hier nicht benoetigt
		if ( (*m_pDlgIfa)->PrimeKeyOfPrevRecord( &IfaNr, &SatzNr, &PhzNr ) == 0 )
		{
			if ( !m_bVorblIfaEnabled )
			{
				m_bVorblIfaEnabled = TRUE;
				m_dlg.EnableFields( m_Pos_Vorblifa, m_bVorblIfaEnabled );
			}
			m_dlg.EnableFields( m_Pos_Vorblifa, m_bVorblIfaEnabled );
			lStatus = LeseSatzUeberIfa( IfaNr, SatzNr );
//			if ( m_pDlgIfa->IsWindowVisible() )
//				m_pDlgIfa->GoOn( );
		}
		else
		{
			m_bRueblifaEnabled = FALSE;
			m_dlg.EnableFields( m_Pos_Rueblifa, m_bRueblifaEnabled );
		}
	}
	GotoFirstKey();
}

void CArtikelView::OnPbArtikelUebernifa() 
{
	// TODO: Add your control notification handler code here

	SetIfaInfo( -1 );

	CString cErrmld;
	if ( FALSE == SetArticleNoEditCtrl( cErrmld ) ){
		return;
	}

	KeyGetInput();

	if ( !ValidateKey() ) 
	{
		GotoFirstKey();
		return;
	}

	long lStatus;

	if ( m_pBufZartikel->ARTIKEL_NR != m_pIfaBuf->A00PZN )
	{
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING497) );
		GotoFirstKey();
		return;
	}

	if ( m_pIfaBuf->NBSTATUS[0] >= '2' ) 
	{
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING498) );
		GotoFirstKey();
		return;
	}

	lStatus = LeseSatzUeberIfa( m_pIfaBuf->IFANR, m_pIfaBuf->SATZNR );
	if ( lStatus == 100 )
	{
		lStatus = LesePznAltSatzUeberIfa( m_pIfaBuf->A06PZNNF );
		if (!( lStatus == 0 || lStatus == 100 ) )
		{
			GotoFirstKey();
			return;
		}

		m_nStatus = 2;
		// initialize pages
		for ( int nr = 0; nr < m_pSheet->GetPageCount(); nr++ )
			m_bWasActive[nr] = FALSE;

		ShowFields();
		EnableFields( TRUE );
		GotoFirstField();
		m_Doc.SetIfaPflege( TRUE );
		((CEkZdpApp*) AfxGetApp())->SetBearbeiten( 2 );
	}
	else if ( lStatus == 0 )
	{
		// PZN ALT hier noch Testen !!!!! in VGL-Ifa Setzen
		lStatus = LesePznAltSatzUeberIfa( m_pIfaBuf->A06PZNNF );
		if (!( lStatus == 0 || lStatus == 100 ) )
		{
			GotoFirstKey();
			return;
		}

		if ( m_Doc.CompareArtikelWithIfa( ) )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING499) );
		else
		{
			CIfaDiff dlg( m_Doc.GetVglIfaBuffer() );
			if ( dlg.DoModal() == IDOK )
			{
// PZN ALT hier noch Testen !!!!! in VGL-Ifa Setzen
//				lStatus = LesePznAltSatzUeberIfa( m_pIfaBuf->PHZALT );
//				if (!( lStatus == 0 || lStatus == 100 ) )
//				{
//					GotoFirstKey();
//					return;
//				}

				m_nStatus = 2;
				// initialize pages
				for ( int nr = 0; nr < m_pSheet->GetPageCount(); nr++ )
					m_bWasActive[nr] = FALSE;

				m_Doc.UpdateArtikelWithIfa( );

				ShowFields();
				EnableFields( TRUE );
				GotoFirstField();

				m_Doc.SetIfaPflege( TRUE );
				((CEkZdpApp*) AfxGetApp())->SetBearbeiten( 2 );
			}
		}
	}
	else
	{
		GotoFirstKey();
	}
}

// der IFA-Dialog wurde verlassen 

LRESULT CArtikelView::OnArtifaEnd( WPARAM wParam, LPARAM )
{
	long lStatus;
	if ( wParam == IDOK )
	{
		(*m_pDlgIfa)->ShowWindow( SW_HIDE );
		m_bVorblIfaEnabled = TRUE;
		m_bRueblifaEnabled = TRUE;
		m_bUebernifaEnabled = TRUE;

		CEkZdpApp *theApp = ( CEkZdpApp *) AfxGetApp();
		if ( theApp->GetActView() != this )
			theApp->OnArtikel();
		// 2 mal
		if ( theApp->GetActView() != this )
			theApp->OnArtikel();

		long IfaNr;
		long SatzNr;
		long PhzNr;  // hier nicht benoetigt
		if ( (*m_pDlgIfa)->PrimeKeyOfSelectedRecord( &IfaNr, &SatzNr, &PhzNr ) == 0 )
			lStatus = LeseSatzUeberIfa( IfaNr, SatzNr );
	}
	else
	{
		ReleaseIfa();
	}
	EnableFieldsIfa();
	GotoFirstKey();

	return 0;
}

void CArtikelView::EnableFieldsIfa()
{
	m_dlg.EnableFields( m_Pos_Vorblifa,  m_bVorblIfaEnabled );
	m_dlg.EnableFields( m_Pos_Rueblifa,  m_bRueblifaEnabled );
	m_dlg.EnableFields( m_Pos_Uebernifa, m_bUebernifaEnabled );
//	m_dlg.EnableFields( m_Pos_Selifa,    TRUE );
	BOOL bErlaub = ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_IFA ) &&
				   ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_ARTIKEL );
	m_dlg.EnableFields( m_Pos_Selifa,  bErlaub && IsCountry("D"));

}

void CArtikelView::ReleaseIfa()
{
	((CEkZdpApp*) AfxGetApp())->ReleaseIfa();

	m_bVorblIfaEnabled  = FALSE;
	m_bRueblifaEnabled  = FALSE;
	m_bUebernifaEnabled = FALSE;
}

// der Datacare-Dialog wurde verlassen 

LRESULT CArtikelView::OnArtdatacareEnd( WPARAM wParam, LPARAM)
{
	long lStatus;
	if ( wParam == IDOK )
	{
		(*m_pDlgDatacare)->ShowWindow( SW_HIDE );
		m_bVorblDatacareEnabled = TRUE;
		m_bRueblDatacareEnabled = TRUE;
		m_bUebernDatacareEnabled = TRUE;

		CEkZdpApp *theApp = ( CEkZdpApp *) AfxGetApp();
		if ( theApp->GetActView() != this )
			theApp->OnArtikel();
		// 2 mal
		if ( theApp->GetActView() != this )
			theApp->OnArtikel();

		long IfaNr;
		long SatzNr;
		long PhzNr;  // hier nicht benoetigt
		if ( (*m_pDlgDatacare)->PrimeKeyOfSelectedRecord( &IfaNr, &SatzNr, &PhzNr ) == 0 )
			lStatus = LeseSatzUeberIfa( IfaNr, SatzNr );
	}
	else
	{
		ReleaseDatacare();
	}
	EnableFieldsDatacare();
	GotoFirstKey();

	return 0;
}

void CArtikelView::EnableFieldsDatacare()
{
//	m_dlg.EnableFields( m_Pos_Vorblifa,  m_bVorblIfaEnabled );
//	m_dlg.EnableFields( m_Pos_Rueblifa,  m_bRueblifaEnabled );
//	m_dlg.EnableFields( m_Pos_Uebernifa, m_bUebernifaEnabled );
//	BOOL bErlaub = ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_IFA ) &&
//				   ((CEkZdpApp*) AfxGetApp())->DarfMenuAendern( MNR_PFL_ARTIKEL );
//	m_dlg.EnableFields( m_Pos_Selifa,  bErlaub );

}

void CArtikelView::ReleaseDatacare()
{
	((CEkZdpApp*) AfxGetApp())->ReleaseDatacare();

	m_bVorblDatacareEnabled  = FALSE;
	m_bRueblDatacareEnabled  = FALSE;
	m_bUebernDatacareEnabled = FALSE;
}


void CArtikelView::TranslatePages()
{
	m_Page0.Translation();

	// Übersetzung von Views, die hier noch gar nicht angezeigt werden, geschieht in der Page selbst
	// m_Page2.Translation();
}