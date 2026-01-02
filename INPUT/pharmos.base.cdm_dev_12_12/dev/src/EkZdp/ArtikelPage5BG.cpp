// ArtikelPage5BG.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "EkZdp.h"
#include "ArtikelPage5BG.h"
#include "ArtikelView.h"
#include "ServerDatum.h"

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDbl.h>
#include <eklibs/hamfcs/hMskDblPos.h>
#include <phxlib/PhxUtil.h>

#include <phxlib/DformSelCtrl.h>

#include <libscsvoodoo/libscsvoodoo.h>

// CArtikelPage5BG-Dialogfeld

IMPLEMENT_DYNCREATE(CArtikelPage5BG, CPropertyPageMultiLang)

// CArtikelPage5BG::CArtikelPage5BG()
CArtikelPage5BG::CArtikelPage5BG() : ChPflegePage(CArtikelPage5BG::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bInitialized = FALSE;
	m_GepnaVal = 0.0;
}

CArtikelPage5BG::~CArtikelPage5BG()
{
}

void CArtikelPage5BG::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage5BG)
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_NAME_BG,				m_ARTIKEL_NAME_BG);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EINHEIT_BG,						m_EINHEIT_BG);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DARREICHFORM_BG,				m_DARREICHFORM_BG);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_NAME_EN,				m_ARTIKEL_NAME_EN);
	DDX_Control(pDX, IDC_ED_ARTIKEL_EINHEIT_EN,						m_EINHEIT_EN);
	DDX_Control(pDX, IDC_ED_ARTIKEL_DARREICHFORM_EN,				m_DARREICHFORM_EN);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_LANGNAME_BG,			m_ARTIKEL_LANGNAME_BG);
	DDX_Control(pDX, IDC_ED_ARTIKEL_ARTIKEL_LANGNAME_EN,			m_ARTIKEL_LANGNAME_EN);
	DDX_Control(pDX, IDC_ST_PAGE5BG_SPR_ZEIL1,						m_ST_SPR_ZEIL1);
	DDX_Control(pDX, IDC_ST_PAGE5BG_SPR_ZEIL2,						m_ST_SPR_ZEIL2);
	DDX_Control(pDX, IDC_ST_PAGE5BG_SPR_ZEIL3,						m_ST_SPR_ZEIL3);
	DDX_Control(pDX, IDC_ST_PAGE5BG_SPR_ZEIL4,						m_ST_SPR_ZEIL4);
	DDX_Control(pDX, IDC_ED_ARTIKEL_KRANKENKASSENCODE,				m_KRANKENKASSENCODE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_RECHNUNGSRABATT,				m_RECHNUNGSRABATT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_NATURALRABATT,					m_NATURALRABATT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GEPNA,							m_GEPNA);
	DDX_Control(pDX, IDC_ED_ARTIKEL_JAEHRL_RECHNUNGSRABATT,			m_JAEHRL_RECHNUNGSRABATT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_JAEHRL_NATURALRABATT,			m_JAEHRL_NATURALSRABATT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_KUNDENRABATTREDUKTION,			m_KUNDENRABATTREDUKTION);
	DDX_Control(pDX, IDC_ED_ARTIKEL_KRANKENKASSENERSTATTUNGSWERT,	m_KRANKENKASSENERSTATTUNG);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GUTSCHRIFTSPREIS,				m_GUTSCHRIFTSPREIS);
	DDX_Control(pDX, IDC_CO_ARTIKEL_ZENTRALLAGER_BG,				m_ZENTRALLAGER);
	DDX_Control(pDX, IDC_CO_ARTIKEL_PREISGRUPPE,					m_PREISGRUPPE);
	DDX_Control(pDX, IDC_CK_ARTIKEL_AUFKLEBER_KK,					m_AUFKLEBER);
	DDX_Control(pDX, IDC_CK_ARTIKEL_LISTE5,							m_LISTE5);
	DDX_Control(pDX, IDC_CK_ARTIKEL_NICHT_AN_DROG,					m_NICHT_AN_DROG);
	DDX_Control(pDX, IDC_CK_ARTIKEL_NICHT_AN_GH,					m_NICHT_AN_GH);
	DDX_Control(pDX, IDC_CK_EXPENSIVE,								m_EXPENSIVE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_KRANKENKASSENKOMPENSATION,		m_KRANKENKASSENKOMPENSATION);
	DDX_Control(pDX, IDC_ED_ARTIKEL_FREIVERKAUFKOMPENSATION,		m_FREIVERKAUFKOMPENSATION);
	DDX_Control(pDX, IDC_ED_ARTIKEL_SKONTO_HERSTELLER,				m_SKONTO_HERSTELLER);
	DDX_Control(pDX, IDC_ED_ARTIKEL_YEARLYBONUSPCT,					m_YEARLY_BONUS_PCT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_OTHERREBATESPCT,				m_OTHER_REBATES_PCT);
	DDX_Control(pDX, IDC_ED_ARTIKEL_GEPNANA,						m_GEPNANA);
	//}}AFX_DATA_MAP

	// Font aendern (erst hier, weil erst nach DoDataExchange die Member gefüllt ist
	CEkZdpApp* pApp = (CEkZdpApp*) AfxGetApp();
	m_pConstantFont = pApp->GetConstantFont();
	m_ARTIKEL_NAME_BG.SetFont( m_pConstantFont );
	m_ARTIKEL_NAME_EN.SetFont( m_pConstantFont );
}

BEGIN_MESSAGE_MAP(CArtikelPage5BG, CPropertyPageMultiLang)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage5BG::MakeDialog()
{
	m_dlg.InitDialog( m_ARTIKEL_NAME_BG );
	m_dlg.InitDialog( m_EINHEIT_BG );
	m_dlg.InitDialog( m_DARREICHFORM_BG );
	m_dlg.InitDialog( m_EINHEIT_EN );

	m_Pos_ARTIKEL_NAME = m_dlg.GetFieldNumber();

	m_dlg.InitDialog( m_ARTIKEL_NAME_EN );
	m_dlg.InitDialog( m_DARREICHFORM_EN );
	m_dlg.InitDialog( m_ARTIKEL_LANGNAME_BG );
	m_dlg.InitDialog( m_ARTIKEL_LANGNAME_EN );

	m_dlg.InitDialog( m_KRANKENKASSENCODE );

	m_dlg.InitDialog( m_RECHNUNGSRABATT );
	m_dlg.InitDialog( m_NATURALRABATT );
	m_dlg.InitDialog( m_GEPNA );
	m_dlg.InitDialog( m_JAEHRL_RECHNUNGSRABATT );
	m_dlg.InitDialog( m_JAEHRL_NATURALSRABATT );
	m_dlg.InitDialog( m_KUNDENRABATTREDUKTION );
	m_dlg.InitDialog( m_KRANKENKASSENERSTATTUNG );
	m_dlg.InitDialog( m_GUTSCHRIFTSPREIS );

	m_dlg.InitDialog( m_ZENTRALLAGER );

	m_Pos_PREISGRUPPE = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_PREISGRUPPE );

	m_dlg.InitDialog( m_AUFKLEBER );
	m_dlg.InitDialog( m_LISTE5 );
	m_dlg.InitDialog( m_NICHT_AN_DROG );
	m_dlg.InitDialog( m_NICHT_AN_GH );
	m_dlg.InitDialog( m_EXPENSIVE );

	m_dlg.InitDialog( m_KRANKENKASSENKOMPENSATION );
	m_dlg.InitDialog( m_SKONTO_HERSTELLER );
	m_dlg.InitDialog( m_YEARLY_BONUS_PCT );
	m_dlg.InitDialog( m_OTHER_REBATES_PCT );
	m_dlg.InitDialog( m_GEPNANA );

	m_dlg.InitDialog( m_FREIVERKAUFKOMPENSATION );
	
	m_nMaxFields = m_dlg.GetFieldNumber();
}

/////////////////////////////////////////////////////////////
//  Validierung

class CV_ARTIKEL_Name5BG : public ChValBase
{
public:
	CV_ARTIKEL_Name5BG( char *pBuf, CArtikelView* pView ) 
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

class CV_ARTIKEL_Einheit5BG : public ChValBase
{
public:
	CV_ARTIKEL_Einheit5BG( CArtikelView* pView ) : ChValBase( pView ){};
	void PostProc( )
	{
		((CArtikelView*)m_pWnd)->SetHeaderInfo();
	}
};

class CV_ARTIKEL_CalcGepna5BG : public ChValBase
{
public:
	CV_ARTIKEL_CalcGepna5BG( CArtikelPage5BG* pView, CArtikelView* pView1 ) : ChValBase( pView, pView1 ){};
	void PostProc( )
	{
		((CArtikelPage5BG*)m_pWnd)->CalcGepna();
	}
};

class CV_ARTIKEL_CalcGepnana5BG : public ChValBase
{
public:
	CV_ARTIKEL_CalcGepnana5BG( CArtikelPage5BG* pView, CArtikelView* pView1 ) : ChValBase( pView, pView1 ){};
	void PostProc( )
	{
		((CArtikelPage5BG*)m_pWnd)->CalcGepnana();
	}
};

class CV_ARTIKEL_Dform5BG : public ChValBase
{
public:
	CV_ARTIKEL_Dform5BG( CArtikelPage5BG* pView, CArtikelView* pView1 )
		: ChValBase( pView, pView1 ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtikelPage5BG*)m_pWnd)->ShowDform_BG( bMeldung, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtikelPage5BG*)m_pWnd)->SucheDform_BG( );
	}
	void PostProc( )
	{
		((CArtikelView*)m_pWnd1)->SetHeaderInfo();
	}
};

class CV_ARTIKEL_Dform5EN : public ChValBase
{
public:
	CV_ARTIKEL_Dform5EN( CArtikelPage5BG* pView, CArtikelView* pView1 )
		: ChValBase( pView, pView1 ){};
	BOOL Validate( BOOL bMeldung )
	{
		return ((CArtikelPage5BG*)m_pWnd)->ShowDform_EN( bMeldung, bMeldung );
	}
	void NotifyProc( )
	{
		((CArtikelPage5BG*)m_pWnd)->SucheDform_EN( );
	}
	void PostProc( )
	{
		((CArtikelView*)m_pWnd1)->SetHeaderInfo();
	}
};

/* ändern auf Page 5 & Krankenkassencode, wenn Mastertabelle da und PHXLIB angepasst
// Wirkstoff
BOOL CArtikelPage3::ShowWirkstoff( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	iStat = m_RD_WIRKSTOFF.IPlausi( m_pBufZartikel->WIRKSTOFF_NR, Name, &Errmld);
	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_WIRKSTOFF_NR )->SetWindowText( Name );
	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage3::SucheWirkstoff( )
{
	CZdkwirSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING294), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufZartikel->WIRKSTOFF_NR ) == 0 )
		{
			m_WIRKSTOFF_NR.p_SetInput();
			m_WIRKSTOFF_NR.SetFocus();
			ShowWirkstoff( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}
*/
// CArtikelPage5BG-Meldungshandler

void CArtikelPage5BG::InitPflege( CWnd *pView  )
{ 
	CArtikelPage5BG* pThisView = this;
	m_pView = pView;
	struct PFL_ARTIKEL *m_Buf = ((CArtikelView* )pView)->GetBuffer();
	m_pBufZartikel			= &m_Buf->zartikel;
	m_pBufCarticlelang		= &m_Buf->carticlelang;
	m_pBufZartbulgaria		= &m_Buf->zartbulgaria;
	m_pBufKrankenkassencode	= &m_Buf->zartwg[10];	// art = B

	m_pBufMinistryProductCode = &m_Buf->carticlecodes[22];		// code_type = 23

	MakeDialog();

	m_ARTIKEL_NAME_BG.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->zartikel.ARTIKEL_NAME,
							L_ZARTIKEL_ARTIKEL_NAME,
							new ChMaskChar,
							new CV_ARTIKEL_Name5BG( m_pBufZartikel->ARTIKEL_NAME,
												(CArtikelView *)m_pView ) );

	m_EINHEIT_BG.SetMask	(ED_CHAR,
							ED_UPPER | ED_RIGHT,
							m_Buf->zartikel.EINHEIT,
							L_ZARTIKEL_EINHEIT,
							new ChMaskChar,
			  	        	new CV_ARTIKEL_Einheit5BG( (CArtikelView *)m_pView ) );

	m_DARREICHFORM_BG.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->zartikel.DARREICHFORM,
							L_ZARTIKEL_DARREICHFORM,
							new ChMaskChar,
							new CV_ARTIKEL_Dform5BG( pThisView, 
												(CArtikelView *)m_pView ) );
								
	m_ARTIKEL_NAME_EN.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->carticlelang.ARTICLENAME,
							L_CARTICLELANG_ARTICLENAME,
							new ChMaskChar,
							new CV_ARTIKEL_Name5BG( m_pBufCarticlelang->ARTICLENAME,
												(CArtikelView *)m_pView ) );

	m_EINHEIT_EN.SetMask   (ED_CHAR,
							ED_UPPER | ED_RIGHT,
							m_Buf->carticlelang.PACKAGINGUNIT,
							L_CARTICLELANG_PACKAGINGUNIT,
							new ChMaskChar,
			  	        	new CV_ARTIKEL_Einheit5BG( (CArtikelView *)m_pView ) );

	m_DARREICHFORM_EN.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->carticlelang.PHARMAFORM,
							L_CARTICLELANG_PHARMAFORM,
							new ChMaskChar,
							new CV_ARTIKEL_Dform5EN( pThisView, 
												(CArtikelView *)m_pView ) );
								
	m_ARTIKEL_LANGNAME_BG.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->zartikel.ARTIKEL_LANGNAME,
							L_ZARTIKEL_ARTIKEL_LANGNAME,
							new ChMaskChar );
				  	
	m_ARTIKEL_LANGNAME_EN.SetMask(ED_CHAR,
							ED_UPPER,
							m_Buf->carticlelang.ARTICLENAMELONG,
							L_CARTICLELANG_ARTICLENAMELONG,
							new ChMaskChar );
				  	    
	m_KRANKENKASSENCODE.SetMask	(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufKrankenkassencode->WARENGRUPPE,
				                 5,
								 new ChMaskChar );
//								 new CV_ARTIKEL_BtmGr( pThisView ) );

	m_RECHNUNGSRABATT.SetMask	(ED_DBL,
								 ED_NORMAL,
								 &m_pBufZartbulgaria->INVOICE_REBATE_PCT,
								 L_ZARTBULGARIA_INVOICE_REBATE_PCT + 1,
								 N_ZARTBULGARIA_INVOICE_REBATE_PCT,
								 new ChMaskDblPos,
							 	 new CV_ARTIKEL_CalcGepna5BG( pThisView, (CArtikelView *)m_pView )  );

	m_NATURALRABATT.SetMask		(ED_DBL,
								 ED_NORMAL,
								 &m_pBufZartbulgaria->REBATE_IN_KIND_PCT,
								 L_ZARTBULGARIA_REBATE_IN_KIND_PCT + 1,
								 N_ZARTBULGARIA_REBATE_IN_KIND_PCT,
								 new ChMaskDblPos,
							 	 new CV_ARTIKEL_CalcGepna5BG( pThisView, (CArtikelView *)m_pView ) );

	m_GEPNA.SetMask				(ED_DBL,
								 ED_NORMAL,
								 &m_GepnaVal,
								 9 + 1,
								 2,
								 new ChMaskDblPos );

	m_JAEHRL_RECHNUNGSRABATT.SetMask   (ED_DBL,
										ED_NORMAL,
										&m_pBufZartbulgaria->ANNUAL_INV_REB_PCT,
										L_ZARTBULGARIA_ANNUAL_INV_REB_PCT + 1,
										N_ZARTBULGARIA_ANNUAL_INV_REB_PCT,
										new ChMaskDblPos );

	m_JAEHRL_NATURALSRABATT.SetMask	(ED_DBL,
									 ED_NORMAL,
									 &m_pBufZartbulgaria->ANNUAL_REB_I_K_PCT,
									 L_ZARTBULGARIA_ANNUAL_REB_I_K_PCT + 1,
									 N_ZARTBULGARIA_ANNUAL_REB_I_K_PCT,
									 new ChMaskDblPos );

	m_KUNDENRABATTREDUKTION.SetMask	(ED_DBL,
									 ED_NORMAL,
									 &m_pBufZartbulgaria->CUST_REB_RED_PCT,
									 L_ZARTBULGARIA_CUST_REB_RED_PCT + 1,
									 N_ZARTBULGARIA_CUST_REB_RED_PCT,
									 new ChMaskDbl );						// ChMaskDbl, damit auch ein Minus eingegeben werden kann

	m_KRANKENKASSENERSTATTUNG.SetMask  (ED_DBL,
										ED_NORMAL,
										&m_pBufZartbulgaria->HI_REIMBURSEMENT,
										L_ZARTBULGARIA_HI_REIMBURSEMENT + 1,
										N_ZARTBULGARIA_HI_REIMBURSEMENT,
										new ChMaskDblPos );

	m_GUTSCHRIFTSPREIS.SetMask		(ED_DBL,
									 ED_NORMAL,
									 &m_pBufZartbulgaria->CREDIT_NOTE_PRICE,
									 L_ZARTBULGARIA_CREDIT_NOTE_PRICE + 1,
									 N_ZARTBULGARIA_CREDIT_NOTE_PRICE,
									 new ChMaskDblPos );

	m_ZENTRALLAGER.SetMask			( "0123"  , &m_pBufZartbulgaria->CENTRAL_WAREHOUSE ); 

	m_PREISGRUPPE.SetMask			( "1234"  , &m_pBufZartbulgaria->PRICE_GROUP ); 

	m_AUFKLEBER.SetMask				(1, 0, &m_pBufZartbulgaria->HI_STICKER );

	m_LISTE5.SetMask				(1, 0, &m_pBufZartbulgaria->LIST_5 );

	m_NICHT_AN_DROG.SetMask			(1, 0, &m_pBufZartbulgaria->DISTR_RESTR_NODRST );
	m_NICHT_AN_GH.SetMask			(1, 0, &m_pBufZartbulgaria->DISTR_RESTR_NOWHS );
	m_EXPENSIVE.SetMask				(1, 0, &m_pBufZartbulgaria->EXPENSIVE);

	m_KRANKENKASSENKOMPENSATION.SetMask  (ED_DBL,
										ED_NORMAL,
										&m_pBufZartbulgaria->SUPPL_HI_REIMB,
										L_ZARTBULGARIA_SUPPL_HI_REIMB + 1,
										N_ZARTBULGARIA_SUPPL_HI_REIMB,
										new ChMaskDblPos );

	m_FREIVERKAUFKOMPENSATION.SetMask  (ED_DBL,
									ED_NORMAL,
									&m_pBufZartbulgaria->SUPPL_FS_REIMB,
									L_ZARTBULGARIA_SUPPL_FS_REIMB + 1,
									N_ZARTBULGARIA_SUPPL_FS_REIMB,
									new ChMaskDblPos );

	m_SKONTO_HERSTELLER.SetMask  (ED_DBL,
								ED_NORMAL,
								&m_pBufZartbulgaria->SUPPL_DISCOUNT_PCT,
								L_ZARTBULGARIA_SUPPL_DISCOUNT_PCT + 1,
								N_ZARTBULGARIA_SUPPL_DISCOUNT_PCT,
								new ChMaskDblPos,
								new CV_ARTIKEL_CalcGepnana5BG( pThisView, (CArtikelView *)m_pView ) );

	m_YEARLY_BONUS_PCT.SetMask  (ED_DBL,
								ED_NORMAL,
								&m_pBufZartbulgaria->YEARLY_BONUS_PCT,
								L_ZARTBULGARIA_YEARLY_BONUS_PCT + 1,
								N_ZARTBULGARIA_YEARLY_BONUS_PCT,
								new ChMaskDblPos,
								new CV_ARTIKEL_CalcGepnana5BG( pThisView, (CArtikelView *)m_pView ) );

	m_OTHER_REBATES_PCT.SetMask  (ED_DBL,
								ED_NORMAL,
								&m_pBufZartbulgaria->OTHER_REBATES_PCT,
								L_ZARTBULGARIA_OTHER_REBATES_PCT + 1,
								N_ZARTBULGARIA_OTHER_REBATES_PCT,
								new ChMaskDblPos,
								new CV_ARTIKEL_CalcGepnana5BG( pThisView, (CArtikelView *)m_pView ) );

	m_GEPNANA.SetMask			(ED_DBL,
								 ED_NORMAL,
								 &m_GepnanaVal,
								 9 + 1,
								 2,
								 new ChMaskDblPos);

	m_bInitialized = TRUE; 

}
void CArtikelPage5BG::SetDialog( BOOL bDialog )
{   
	m_dlg.SetDialog( bDialog );
}

void CArtikelPage5BG::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtikelPage5BG::EnableFields( BOOL bEnab )
{   
	m_dlg.EnableFields( bEnab );

	DisableSpecial();

	if (bEnab == TRUE)
		CalcGepna();
}

void CArtikelPage5BG::DisableSpecial()
{
	m_GEPNA.EnableWindow(false);
	m_GEPNANA.EnableWindow(false);
	m_EXPENSIVE.EnableWindow(false);
	m_FREIVERKAUFKOMPENSATION.EnableWindow(false);
}

void CArtikelPage5BG::ShowFields( )
{
	FillComboBox();

	m_dlg.ShowFields();
}

void CArtikelPage5BG::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtikelPage5BG::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

void CArtikelPage5BG::ActivateField( int nr )
{
	m_dlg.ActivateField( nr );
}

BOOL CArtikelPage5BG::Validate( BOOL bMeldung )
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

BOOL CArtikelPage5BG::EndValidate( int *ind, BOOL bMeldung )
{
	BOOL bOk = true;
	
	*ind = 0;

	if (( (CArtikelView* )m_pView)->WasPageActive(4) )
	{
		if (m_PREISGRUPPE.GetCurSel() == -1)
		{
			bOk = false;
			*ind = m_Pos_PREISGRUPPE;

			if ( bMeldung )
				MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1148) );
		}
	}

	return bOk;
}

/////////////////////////////////////////////////////////////////////////////
// CLieferPage1 message handlers

BOOL CArtikelPage5BG::OnSetActive()
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


BOOL CArtikelPage5BG::OnKillActive()
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

void CArtikelPage5BG::ResetVkn( )
{
	m_RD_DFORM_BG.Reset();
	m_RD_DFORM_EN.Reset();
//	m_RD_KRANKENKASSENCODE.Reset();
}

/////////////////////////////////////////////////////////////
//  Verknuepfungen lesen

// GEPNA
void CArtikelPage5BG::CalcGepna()
{
	double grosso = 0.0;

	CString sql;
	long s;

	sql.Format( "select grosso from ZARTPREIS p where ARTIKEL_NR=%ld and DATUMGUELTIGAB= "
					"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = p.artikel_nr "
					"and DATUMGUELTIGAB <= %ld)", m_pBufZartbulgaria->ARTICLENO, ::Today() );

	s = SqlRead(sql, &grosso, NULL);

	if (s == 0)
	{	
		m_RECHNUNGSRABATT.p_GetInput();
		m_NATURALRABATT.p_GetInput();

		m_GepnaVal = grosso * (100 - (m_pBufZartbulgaria->INVOICE_REBATE_PCT + 
			((m_pBufZartbulgaria->REBATE_IN_KIND_PCT / 
			(100 + 
			m_pBufZartbulgaria->REBATE_IN_KIND_PCT)) 
			* 100))) / 100;

		::KaufmRunden( &m_GepnaVal, 2);
	}
	else
		m_GepnaVal = 0;

	m_GEPNA.p_SetInput();

	CalcGepnana();
}


// GEPNANA
void CArtikelPage5BG::CalcGepnana()
{
	m_YEARLY_BONUS_PCT.p_GetInput();
	m_OTHER_REBATES_PCT.p_GetInput();
	m_SKONTO_HERSTELLER.p_GetInput();

	m_GepnanaVal = 0.0;

	if (m_GepnaVal != 0.0)
	{
		m_GepnanaVal = m_GepnaVal * ((	100 - 
										(m_pBufZartbulgaria->YEARLY_BONUS_PCT + 
										m_pBufZartbulgaria->OTHER_REBATES_PCT + 
										m_pBufZartbulgaria->SUPPL_DISCOUNT_PCT )) / 100);

		::KaufmRunden( &m_GepnanaVal, 2);
	}
	
	m_GEPNANA.p_SetInput();
}


// DFORM

BOOL CArtikelPage5BG::ShowDform_BG( BOOL , BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	iStat = m_RD_DFORM_BG.IPlausi( m_pBufZartikel->DARREICHFORM, Name, &Errmld);

	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage5BG::SucheDform_BG( )
{
	CDformSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_SEL_DAR), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufZartikel->DARREICHFORM ) == 0 )
		{
			m_DARREICHFORM_BG.p_SetInput();
			m_DARREICHFORM_BG.SetFocus();
		}
	}

	m_SelBox.CloseCursor();
}

BOOL CArtikelPage5BG::ShowDform_EN( BOOL , BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	iStat = m_RD_DFORM_EN.IPlausi( m_pBufCarticlelang->PHARMAFORM, Name, &Errmld);

	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage5BG::SucheDform_EN( )
{
	CDformSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_SEL_DAR), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufCarticlelang->PHARMAFORM ) == 0 )
		{
			m_DARREICHFORM_EN.p_SetInput();
			m_DARREICHFORM_EN.SetFocus();
		}
	}

	m_SelBox.CloseCursor();
}

void CArtikelPage5BG::Set_Artikel_Name( )
{
	m_dlg.DataExchangeFromBuffer( m_Pos_ARTIKEL_NAME );
}

void CArtikelPage5BG::FillComboBox()
{
	m_ZENTRALLAGER.ResetContent();

	m_ZENTRALLAGER.AddString(CResString::ex().getStrTblText(IDS_STRING269));
	m_ZENTRALLAGER.AddString(CResString::ex().getStrTblText(IDS_STRING1084));
	m_ZENTRALLAGER.AddString(CResString::ex().getStrTblText(IDS_STRING1085));
	m_ZENTRALLAGER.AddString(CResString::ex().getStrTblText(IDS_STRING1086));

	m_PREISGRUPPE.ResetContent();

	m_PREISGRUPPE.AddString(CResString::ex().getStrTblText(IDS_STRING1141));
	m_PREISGRUPPE.AddString(CResString::ex().getStrTblText(IDS_STRING1142));
	m_PREISGRUPPE.AddString(CResString::ex().getStrTblText(IDS_STRING1143));
	m_PREISGRUPPE.AddString(CResString::ex().getStrTblText(IDS_STRING1144));
}
