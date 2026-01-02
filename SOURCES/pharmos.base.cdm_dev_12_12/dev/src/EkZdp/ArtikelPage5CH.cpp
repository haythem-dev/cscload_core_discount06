// ArtikelPage5CH.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "EkZdp.h"
#include "ArtikelPage5CH.h"
#include "ArtikelView.h"

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDblPos.h>

#include <phxlib/DformSelCtrl.h>
#include <phxlib/assortmentselctrl.h>

// CArtikelPage5CH-Dialogfeld

IMPLEMENT_DYNCREATE(CArtikelPage5CH, CPropertyPageMultiLang)

// CArtikelPage5CH::CArtikelPage5CH()
CArtikelPage5CH::CArtikelPage5CH() : ChPflegePage(CArtikelPage5CH::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bInitialized = FALSE;
}

CArtikelPage5CH::~CArtikelPage5CH()
{
}

void CArtikelPage5CH::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage5CH)
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_NAME_D,		m_ARTIKEL_NAME_D);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EINHEIT_D,			m_EINHEIT_D);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DARREICHFORM_D,		m_DARREICHFORM_D);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_NAME_F,		m_ARTIKEL_NAME_F);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EINHEIT_F,			m_EINHEIT_F);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DARREICHFORM_F,		m_DARREICHFORM_F);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_LANGNAME_D, m_ARTIKEL_LANGNAME_D);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_LANGNAME_F, m_ARTIKEL_LANGNAME_F);
	DDX_Control(pDX, IDC_ED_ARTIKEL_IKS_CODE,			m_IKS_CODE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_SWISSMEDIC_REGNR,	m_SWISSMEDIC_REGNR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_SWISSMEDIC_ZUSATZ,	m_SWISSMEDIC_ZUSATZ);
	DDX_Control(pDX, IDC_ED_ARTIKEL_WARNPROZVORPLM,		m_WARNPROZVORPLM);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ANTIBIOTIKA_FNR,	m_ANTIBIOTIKA_FNR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ZOLLPOS_NR,			m_ZOLLPOS_NR);
	DDX_Control(pDX, IDC_ED_ARTIKEL_BAGDOSSIER,			m_BAGDOSSIER);
	DDX_Control(pDX, IDC_ED_ARTIKEL_MIGCD,				m_MIGCD);
	DDX_Control(pDX, IDC_ED_ARTIKEL_PFLICHTLAGERMENGE,	m_PFLICHTLAGERMENGE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_BUENDELPACKUNG_CH,	m_BUENDELPACKUNG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_NUR_APO,	m_VERTRBIND_NUR_APO);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_NUR_SPIT, m_VERTRBIND_NUR_SPIT);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_KUENZLE,	m_VERTRBIND_KUENZLE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_INLAND,	m_VERTRBIND_INLAND);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_KANTONAL, m_VERTRBIND_KANTONAL);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_PREWHOLE, m_VERTRBIND_PREWHOLE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_LISTE_C,	m_VERTRBIND_LISTE_C);
	DDX_Control(pDX, IDC_CK_ARTIKEL_VERTRBIND_LISTE_D,	m_VERTRBIND_LISTE_D);
	DDX_Control(pDX, IDC_ST_PAGE5CH_SPR_ZEIL1,			m_ST_SPR_ZEIL1);
	DDX_Control(pDX, IDC_ST_PAGE5CH_SPR_ZEIL2,			m_ST_SPR_ZEIL2);
	DDX_Control(pDX, IDC_ST_PAGE5CH_SPR_ZEIL3,			m_ST_SPR_ZEIL3);
	DDX_Control(pDX, IDC_ST_PAGE5CH_SPR_ZEIL4,			m_ST_SPR_ZEIL4);
	DDX_Control(pDX, IDC_ED_ARTIKEL_CODE_ASSORTMENT,	m_CODE_ASSORTMENT);
	//}}AFX_DATA_MAP

	// Font aendern (erst hier, weil erst nach DoDataExchange die Member gefüllt ist
	CEkZdpApp* pApp = (CEkZdpApp*) AfxGetApp();
	m_pConstantFont = pApp->GetConstantFont();
	m_ARTIKEL_NAME_D.SetFont( m_pConstantFont );
	m_ARTIKEL_NAME_F.SetFont( m_pConstantFont );
}

BEGIN_MESSAGE_MAP(CArtikelPage5CH, CPropertyPageMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage5CH::MakeDialog()
{
	m_dlg.InitDialog( m_ARTIKEL_NAME_D );
	m_dlg.InitDialog( m_EINHEIT_D );
	m_dlg.InitDialog( m_DARREICHFORM_D );
	m_dlg.InitDialog( m_EINHEIT_F );

	m_Pos_ARTIKEL_NAME = m_dlg.GetFieldNumber();

	m_dlg.InitDialog( m_ARTIKEL_NAME_F );
	m_dlg.InitDialog( m_DARREICHFORM_F );
	m_dlg.InitDialog( m_ARTIKEL_LANGNAME_D );
	m_dlg.InitDialog( m_ARTIKEL_LANGNAME_F );
	m_dlg.InitDialog( m_IKS_CODE );
	m_dlg.InitDialog( m_SWISSMEDIC_REGNR );
	m_dlg.InitDialog( m_SWISSMEDIC_ZUSATZ );
	m_dlg.InitDialog( m_WARNPROZVORPLM );
	m_dlg.InitDialog( m_ANTIBIOTIKA_FNR );
	m_dlg.InitDialog( m_ZOLLPOS_NR );
	m_dlg.InitDialog( m_BAGDOSSIER );
	m_dlg.InitDialog( m_MIGCD );
	m_dlg.InitDialog( m_PFLICHTLAGERMENGE );
	m_dlg.InitDialog( m_BUENDELPACKUNG );
	m_dlg.InitDialog( m_VERTRBIND_NUR_APO );
	m_dlg.InitDialog( m_VERTRBIND_NUR_SPIT );
	m_dlg.InitDialog( m_VERTRBIND_KUENZLE );

	m_Pos_VERTRBIND_INLAND = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_VERTRBIND_INLAND );

	m_dlg.InitDialog( m_VERTRBIND_KANTONAL );
	m_dlg.InitDialog( m_VERTRBIND_PREWHOLE );

	m_Pos_VERTRBIND_LISTE_C = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_VERTRBIND_LISTE_C );

	m_Pos_VERTRBIND_LISTE_D = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_VERTRBIND_LISTE_D );

	m_dlg.InitDialog( m_CODE_ASSORTMENT );

	m_nMaxFields = m_dlg.GetFieldNumber();
}

/////////////////////////////////////////////////////////////
//  Validierung

class CV_ARTIKEL_Name5CH : public ChValBase
{
public:
	CV_ARTIKEL_Name5CH( char *pBuf, CArtikelView* pView ) 
		: ChValBase( pBuf, pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk = ((( char *)m_pBuf)[0])!= ' ';
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_NO_SPACE_BEGIN) );
		return bOk;
	}

	void PostProc( )
	{
		((CArtikelView*)m_pWnd)->SetHeaderInfo();
	}
};

class CV_ARTIKEL_Einheit5CH : public ChValBase
{
public:
	CV_ARTIKEL_Einheit5CH( CArtikelView* pView ) : ChValBase( pView ){};
	void PostProc( )
	{
		((CArtikelView*)m_pWnd)->SetHeaderInfo();
	}
};

class CV_ARTIKEL_Dform5CHD : public ChValBase
{
public:
	CV_ARTIKEL_Dform5CHD( CArtikelPage5CH* pView, CArtikelView* pView1 )
		: ChValBase( pView, pView1 ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtikelPage5CH*)m_pWnd)->ShowDform_D( bMeldung, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtikelPage5CH*)m_pWnd)->SucheDform_D( );
	}
	void PostProc( )
	{
		((CArtikelView*)m_pWnd1)->SetHeaderInfo();
	}
};

class CV_ARTIKEL_Dform5CHF : public ChValBase
{
public:
	CV_ARTIKEL_Dform5CHF( CArtikelPage5CH* pView, CArtikelView* pView1 )
		: ChValBase( pView, pView1 ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtikelPage5CH*)m_pWnd)->ShowDform_F( bMeldung, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtikelPage5CH*)m_pWnd)->SucheDform_F( );
	}
	void PostProc( )
	{
		((CArtikelView*)m_pWnd1)->SetHeaderInfo();
	}
};

class CV_ARTIKEL_IKSCode : public ChValBase
{
public:
	CV_ARTIKEL_IKSCode( CArtikelPage5CH* pView, CArtikelView* pView1 )
		: ChValBase( pView, pView1 ){};
	void PostProc( )
	{
		((CArtikelPage5CH*)m_pWnd)->SetRezeptpfl( );
		((CArtikelPage5CH*)m_pWnd)->SetVertriebsbind( );
	}
};

class CV_ARTIKEL_Code_Assortment : public ChValBase
{
public:
	CV_ARTIKEL_Code_Assortment( CArtikelPage5CH* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		PostProc();
		
		BOOL bOk;
		bOk = ((CArtikelPage5CH*)m_pWnd)->ShowAssortmentCode( bMeldung, bMeldung );

		if ( bOk ) 
			bOk = ((CArtikelPage5CH*)m_pWnd)->TestAssortmentCode( bMeldung );

		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage5CH*)m_pWnd)->SucheAssortmentCode( );
	}
};

void CArtikelPage5CH::SetVertriebsbind( )
{
	if ( !m_IKS_CODE.WasCharPressed( ) ) return;

	if ( strcmp ( m_pBufZartswitzerland->IKS_CODE, "D") == 0 ) 
	{
		m_pBufZartswitzerland->VERTRBIND_LISTE_D[0] = '1';
		m_pBufZartswitzerland->VERTRBIND_LISTE_C[0] = '0';
	}
	else if ( strcmp ( m_pBufZartswitzerland->IKS_CODE, "C") == 0 ) 
	{
		m_pBufZartswitzerland->VERTRBIND_LISTE_C[0] = '1';
		m_pBufZartswitzerland->VERTRBIND_LISTE_D[0] = '0';
	}
	else
	{
		m_pBufZartswitzerland->VERTRBIND_LISTE_C[0] = '0';
		m_pBufZartswitzerland->VERTRBIND_LISTE_D[0] = '0';
	}

	m_dlg.DataExchangeFromBuffer( m_Pos_VERTRBIND_LISTE_D );
	m_dlg.DataExchangeFromBuffer( m_Pos_VERTRBIND_LISTE_C );
}

void CArtikelPage5CH::SetRezeptpfl( )
{
	if ( !m_IKS_CODE.WasCharPressed( ) ) return;

	if ( strcmp ( m_pBufZartswitzerland->IKS_CODE, "A") == 0 ||
			strcmp ( m_pBufZartswitzerland->IKS_CODE, "B") == 0 )
		m_pBufZartikel->REZEPTPFL[0] = '1';
	else
		m_pBufZartikel->REZEPTPFL[0] = '0';

	// auf Seite 1 im Dialogfeld aktivieren
	CArtikelPage1 *pP1;
	pP1 = (CArtikelPage1 *)((CArtikelView*)m_pView)->GetPage(0);
	pP1->Set_Rezeptpfl();
}

// CArtikelPage5CH-Meldungshandler

void CArtikelPage5CH::InitPflege( CWnd *pView  )
{ 
	CArtikelPage5CH* pThisView = this;
	m_pView = pView;
	struct PFL_ARTIKEL *m_Buf	= ((CArtikelView* )pView)->GetBuffer();
	m_pBufZartswitzerland		= &m_Buf->zartswitzerland;
	m_pBufZartikel				= &m_Buf->zartikel;
	m_pBufCarticlelang			= &m_Buf->carticlelang;

	m_pBufAssortment = &m_Buf->carticlecodes[20];		// code_type = 21
	
	MakeDialog();

	m_ARTIKEL_NAME_D.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->zartikel.ARTIKEL_NAME,
							L_ZARTIKEL_ARTIKEL_NAME,
							new ChMaskChar,
							new CV_ARTIKEL_Name5CH( m_pBufZartikel->ARTIKEL_NAME,
												(CArtikelView *)m_pView ) );

	m_EINHEIT_D.SetMask		(ED_CHAR,
							ED_UPPER | ED_RIGHT,
							m_Buf->zartikel.EINHEIT,
							L_ZARTIKEL_EINHEIT,
							new ChMaskChar,
			  	        	new CV_ARTIKEL_Einheit5CH( (CArtikelView *)m_pView ) );

	m_DARREICHFORM_D.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->zartikel.DARREICHFORM,
							L_ZARTIKEL_DARREICHFORM,
							new ChMaskChar,
							new CV_ARTIKEL_Dform5CHD( pThisView, 
												(CArtikelView *)m_pView ) );
								
	m_ARTIKEL_NAME_F.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->carticlelang.ARTICLENAME,
							L_CARTICLELANG_ARTICLENAME,
							new ChMaskChar,
							new CV_ARTIKEL_Name5CH( m_pBufCarticlelang->ARTICLENAME,
												(CArtikelView *)m_pView ) );

	m_EINHEIT_F.SetMask		(ED_CHAR,
							ED_UPPER | ED_RIGHT,
							m_Buf->carticlelang.PACKAGINGUNIT,
							L_CARTICLELANG_PACKAGINGUNIT,
							new ChMaskChar,
			  	        	new CV_ARTIKEL_Einheit5CH( (CArtikelView *)m_pView ) );

	m_DARREICHFORM_F.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->carticlelang.PHARMAFORM,
							L_CARTICLELANG_PHARMAFORM,
							new ChMaskChar,
							new CV_ARTIKEL_Dform5CHF( pThisView, 
												(CArtikelView *)m_pView ) );
								
	m_ARTIKEL_LANGNAME_D.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->zartikel.ARTIKEL_LANGNAME,
							L_ZARTIKEL_ARTIKEL_LANGNAME,
							new ChMaskChar );
				  	
	m_ARTIKEL_LANGNAME_F.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->carticlelang.ARTICLENAMELONG,
							L_CARTICLELANG_ARTICLENAMELONG,
							new ChMaskChar );
				  	    
	m_IKS_CODE.SetMask		(ED_CHAR,
		                     ED_UPPER,
			                 m_pBufZartswitzerland->IKS_CODE,
				             L_ZARTSWITZERLAND_IKS_CODE,
							 new ChMaskChar,
							 new CV_ARTIKEL_IKSCode( pThisView, (CArtikelView *)m_pView ) );

	m_SWISSMEDIC_REGNR.SetMask (ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartswitzerland->SWISSMEDIC_REGNR,
                             5,
							 new ChMaskNum );

	m_SWISSMEDIC_ZUSATZ.SetMask (ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartswitzerland->SWISSMEDIC_ZUSATZ,
                             3,
							 new ChMaskNum );

	m_WARNPROZVORPLM.SetMask (ED_DBL,
                              ED_NORMAL,
                              &m_pBufZartswitzerland->WARNPROZVORPLM,
                              L_ZARTSWITZERLAND_WARNPROZVORPLM + 1,
                              N_ZARTSWITZERLAND_WARNPROZVORPLM,
                              new ChMaskDblPos );

	m_ANTIBIOTIKA_FNR.SetMask (ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartswitzerland->ANTIBIOTIKA_FNR,
                             4,
							 new ChMaskNum );

	m_ZOLLPOS_NR.SetMask   (ED_CHAR,
							ED_UPPER,
							m_Buf->zartswitzerland.ZOLLPOS_NR,
							L_ZARTSWITZERLAND_ZOLLPOS_NR,
							new ChMaskChar );

	m_BAGDOSSIER.SetMask	(ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartswitzerland->BAGDOSSIER,
                             10,
							 new ChMaskNum );

	m_MIGCD.SetMask			(ED_CHAR,
							ED_UPPER,
							m_pBufZartswitzerland->MIGCD,
							L_ZARTSWITZERLAND_MIGCD,
							new ChMaskChar );
				  	    
	m_PFLICHTLAGERMENGE.SetMask (ED_LONG,
                             ED_NORMAL,
                             &m_pBufZartswitzerland->PFLICHTLAGERMENGE,
                             6,
							 new ChMaskNum );

	m_BUENDELPACKUNG.SetMask ( '1', '0', m_pBufZartswitzerland->BUENDELPACKUNG);

	m_CODE_ASSORTMENT.SetMask	(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufAssortment->ARTICLE_CODE,
								 11,
								 new ChMaskChar,
								 new CV_ARTIKEL_Code_Assortment( pThisView ) );

	m_VERTRBIND_NUR_APO.SetMask		( '1', '0', m_pBufZartswitzerland->VERTRBIND_NUR_APO);
	m_VERTRBIND_NUR_SPIT.SetMask	( '1', '0', m_pBufZartswitzerland->VERTRBIND_NUR_SPIT);
	m_VERTRBIND_KUENZLE.SetMask		( '1', '0', m_pBufZartswitzerland->VERTRBIND_KUENZLE);
	m_VERTRBIND_INLAND.SetMask		( '1', '0', m_pBufZartswitzerland->VERTRBIND_INLAND);
	m_VERTRBIND_KANTONAL.SetMask	( '1', '0', m_pBufZartswitzerland->VERTRBIND_KANTONAL);
	m_VERTRBIND_PREWHOLE.SetMask	( '1', '0', m_pBufZartswitzerland->VERTRBIND_PREWHOLE);
	m_VERTRBIND_LISTE_C.SetMask		( '1', '0', m_pBufZartswitzerland->VERTRBIND_LISTE_C);
	m_VERTRBIND_LISTE_D.SetMask		( '1', '0', m_pBufZartswitzerland->VERTRBIND_LISTE_D);

	m_bInitialized = TRUE; 

}
void CArtikelPage5CH::SetDialog( BOOL bDialog )
{   
	m_dlg.SetDialog( bDialog );
}

void CArtikelPage5CH::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtikelPage5CH::EnableFields( BOOL bEnab )
{   
	m_dlg.EnableFields( bEnab );

	if (!IsPrewhole())
	{
		m_WARNPROZVORPLM.EnableWindow(false);
		m_ANTIBIOTIKA_FNR.EnableWindow(false);
		m_ZOLLPOS_NR.EnableWindow(false);
		m_PFLICHTLAGERMENGE.EnableWindow(false);
	}

	m_BUENDELPACKUNG.EnableWindow(false); //auf Anfo von Fr. Fretz am 20.05.2015 nicht mehr nötig.
}

void CArtikelPage5CH::ShowFields( )
{
	// Übersetzung erst hier, weil beim Aufruf von TranslatePages im View noch nicht sichtbar
	Translation();

	m_dlg.ShowFields();
	ShowAssortmentCode( TRUE );
}

void CArtikelPage5CH::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtikelPage5CH::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}


void CArtikelPage5CH::ActivateField( int nr )
{
	m_dlg.ActivateField( nr );
}


BOOL CArtikelPage5CH::Validate( BOOL bMeldung )
{
	int i = 0;
	BOOL bOk = TRUE;

	SetValidation( FALSE );

	bOk = m_dlg.Validate( &i, bMeldung );
	if ( bOk )
		bOk = EndValidate( &i, bMeldung );

	if ( !bOk && bMeldung )
		m_dlg.ActivateField( i );
	
	SetValidation( TRUE ); 

	return bOk; 
}

/////////////////////////////////////////////////////////////
//  EndValidierung 

BOOL CArtikelPage5CH::EndValidate( int *ind, BOOL bMeldung )
{
	if (bMeldung){}
	*ind = 0;

	/* PostProcs aufrufen hier !!!!! */

	if ( GetFocus() == &m_IKS_CODE ) 
	{
		SetRezeptpfl( );
		SetVertriebsbind( );
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLieferPage1 message handlers

BOOL CArtikelPage5CH::OnSetActive()
{
	BOOL bOk = true;
	bOk = CPropertyPageMultiLang::OnSetActive();
	if ( bOk && m_bInitialized )
	{
		ShowFields();
		((CArtikelView* )m_pView)->Set_WasActive();
		EnableFields( ((CArtikelView* )m_pView)->AreFieldsEnabled() );
		GetParent()->SendMessage( WM_USER+10 );
		SetValidation( TRUE );
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING321) );
	} 
	return bOk;
}


BOOL CArtikelPage5CH::OnKillActive()
{
	BOOL bOk = true;
	bOk = CPropertyPageMultiLang::OnKillActive();
	if ( bOk )
	{
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING322) );
		SetValidation( FALSE );
		DataExchangeToBuffer( );  //  Puffer wie Eingabe
	} 
	return bOk;
}
 
/////////////////////////////////////////////
// Verknuepfungen Ruecksetzen

void CArtikelPage5CH::ResetVkn( )
{
	m_RD_DFORM_D.Reset();
	m_RD_DFORM_F.Reset();
}

/////////////////////////////////////////////////////////////
//  Verknuepfungen lesen

// DFORM

BOOL CArtikelPage5CH::ShowDform_D( BOOL bShow, BOOL bMeldung )
{
	if (bShow){}
	int iStat;
	CString Name;
	CString Errmld;

	iStat = m_RD_DFORM_D.IPlausi( m_pBufZartikel->DARREICHFORM, Name, &Errmld);

	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage5CH::SucheDform_D( )
{
	CDformSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_SEL_DAR), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufZartikel->DARREICHFORM ) == 0 )
		{
			m_DARREICHFORM_D.p_SetInput();
			m_DARREICHFORM_D.SetFocus();
		}
	}

	m_SelBox.CloseCursor();
}

BOOL CArtikelPage5CH::ShowDform_F( BOOL bShow, BOOL bMeldung )
{
	if (bShow) {}
	int iStat;
	CString Name;
	CString Errmld;

	iStat = m_RD_DFORM_F.IPlausi( m_pBufCarticlelang->PHARMAFORM, Name, &Errmld);

	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage5CH::SucheDform_F( )
{
	CDformSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_SEL_DAR), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufCarticlelang->PHARMAFORM ) == 0 )
		{
			m_DARREICHFORM_F.p_SetInput();
			m_DARREICHFORM_F.SetFocus();
		}
	}

	m_SelBox.CloseCursor();
}

void CArtikelPage5CH::Set_Artikel_Name( )
{
	m_dlg.DataExchangeFromBuffer( m_Pos_ARTIKEL_NAME );
}

void CArtikelPage5CH::Translation() 
{
	if (IsPrewhole())
	{
		m_ST_SPR_ZEIL1.SetWindowText( "franz." );
		m_ST_SPR_ZEIL2.SetWindowText( "deutsch" );
		m_ST_SPR_ZEIL3.SetWindowText( "Langname franz." );
		m_ST_SPR_ZEIL4.SetWindowText( "Langname deutsch" );
	}
}

void CArtikelPage5CH::Set_Vertrbind_Inland( )
{
	m_dlg.DataExchangeFromBuffer( m_Pos_VERTRBIND_INLAND );
}


BOOL CArtikelPage5CH::TestAssortmentCode( BOOL bMeldung )
{
	if (strncmp (m_pBufAssortment->ARTICLE_CODE, "           ", 11) == 0)
		return true;

	BOOL bOk =	m_pBufAssortment->ARTICLE_CODE[2] == '.' &&
				m_pBufAssortment->ARTICLE_CODE[5] == '.' &&
				m_pBufAssortment->ARTICLE_CODE[8] == '.' &&
				m_pBufAssortment->ARTICLE_CODE[10]!= ' ';

	if ( !bOk && bMeldung )
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1456) );

	return bOk;
}

BOOL CArtikelPage5CH::ShowAssortmentCode( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	iStat = m_RD_ASSORTMENT.IPlausi( m_pBufAssortment->ARTICLE_CODE, Name, &Errmld);
	
	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_CODE_ASSORTMENT )->SetWindowText( Name );

	// Font aendern (in den mehrzeiligen Statics kleiner, um etwas Platz auf dem Dialog zu schaffen)
	// nur, wenn die Seite auch schon aktiv war, sonst schmiert das Programm ab
	if (((CArtikelView* )m_pView)->WasPageActive(4) == TRUE)
	{
		CEkZdpApp* pApp = (CEkZdpApp*) AfxGetApp();
		m_pSmallFont = pApp->GetSmallFont();
		GetDlgItem( IDC_ST_ARTIKEL_CODE_ASSORTMENT )->SetFont( m_pSmallFont );
	}

	if ( iStat > 1 && bMeldung ) 
	{
		MsgBoxOK( Errmld );
	}

	return iStat <= 1;
}

void CArtikelPage5CH::SucheAssortmentCode( )
{
	CAssortmentSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1455), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufAssortment->ARTICLE_CODE ) == 0 )
		{
			m_CODE_ASSORTMENT.p_SetInput();
			m_CODE_ASSORTMENT.SetFocus();
			ShowAssortmentCode( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}