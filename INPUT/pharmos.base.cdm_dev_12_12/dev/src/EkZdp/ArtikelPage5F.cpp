// ArtikelPage5F.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "EkZdp.h"
#include "ArtikelPage5F.h"
#include "hSelectDialog.h"
#include "ArtikelView.h"

#include <phxlib/ClpprcodeSelCtrl.h> 
#include <phxlib/ZrabgrpSelCtrl.h>
#include <phxlib/CReimbursementPctSelCtrl.h>
#include <phxlib/EphmraSelCtrl.h> 
#include <phxlib/AtcSelCtrl.h> 

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskDblPos.h>
#include <eklibs/hamfcs/hMskDate.h>

#include <hdatum/phodate.h>
#include "ServerDatum.h"
#include <libscsvoodoo/libscsvoodoo.h>

#include "RefundFrance.h"

// CArtikelPage5F-Dialogfeld

IMPLEMENT_DYNCREATE(CArtikelPage5F, CPropertyPageMultiLang)

// CArtikelPage5F::CArtikelPage5F()
CArtikelPage5F::CArtikelPage5F() : ChPflegePage(CArtikelPage5F::IDD)
{
	//{{AFX_DATA_INIT(CArtikelPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bInitialized = FALSE;
}

CArtikelPage5F::~CArtikelPage5F()
{
}

void CArtikelPage5F::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPageMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtikelPage5F)
	DDX_Control(pDX, IDC_ED_ART5F_UEBEREINH,		m_UEBEREINH);
	DDX_Control(pDX, IDC_ED_ART5F_MGEUNTER,			m_MGEUNTER);
	DDX_Control(pDX, IDC_CB_ART5F_ERST_TYP,			m_ERST_TYP);
	DDX_Control(pDX, IDC_ED_ART5F_ERST_PROZ,		m_ERST_PROZ);
	DDX_Control(pDX, IDC_ED_ART5F_ERST_WERT,		m_ERST_WERT);
	DDX_Control(pDX, IDC_ED_ART5F_ERST_BASIS,		m_ERST_BASIS);
	DDX_Control(pDX, IDC_ED_ART5F_CODE_LPPR,		m_CODE_LPPR);
	DDX_Control(pDX, IDC_CK_ART5F_RES_HOSP,			m_RES_HOSP);
	DDX_Control(pDX, IDC_CK_ART5F_NOEDI,			m_NOEDI);
	DDX_Control(pDX, IDC_CK_ART5F_VERTRBIND_EXPORT,	m_VERTRBIND_EXPORT);
	DDX_Control(pDX, IDC_CK_ART5F_VERTRBIND_LEGALL, m_VERTRBIND_LEGALL);
	DDX_Control(pDX, IDC_CK_ART5F_VERTRBIND_BREIZH, m_VERTRBIND_BREIZH);
	DDX_Control(pDX, IDC_CK_ART5F_VERTRBIND_HOSPITAL,m_VERTRBIND_HOSPITAL);
	DDX_Control(pDX, IDC_ED_ARTIKEL_RABATTGRP_SP,	m_RABATTGRP_SP);
	DDX_Control(pDX, IDC_CB_ART5F_CODE_BLOQUAGE,	m_CODE_BLOQUAGE);
	DDX_Control(pDX, IDC_ED_ARTIKEL_CODE_EPHMRA,	m_CODE_EPHMRA);
	DDX_Control(pDX, IDC_ED_ART5F_RF_DATUM,			m_RF_DATUM);
	DDX_Control(pDX, IDC_CB_ART5F_RF_ERST_TYP,		m_RF_ERST_TYP);
	DDX_Control(pDX, IDC_ED_ART5F_RF_ERST_PROZ,		m_RF_ERST_PROZ);
	DDX_Control(pDX, IDC_ED_ART5F_RF_ERST_WERT,		m_RF_ERST_WERT);
	DDX_Control(pDX, IDC_ED_ART5F_RF_ERST_BASIS,	m_RF_ERST_BASIS);
	DDX_Control(pDX, IDC_ED_ART5F_RF_CODE_LPPR,		m_RF_CODE_LPPR);
	DDX_Control(pDX, IDC_PB_REFUND_FRANCE,			m_PB_REFUND);
	DDX_Control(pDX, IDC_CK_ART5F_NACHLIEFERUNG,    m_NACHLIEFERUNG);
	DDX_Control(pDX, IDC_CK_ART5F_CONSIGNED,		m_CONSIGNED);
	DDX_Control(pDX, IDC_CO_ART5F_CUSTOMERGROUP,	m_CUSTOMERGROUP);
	DDX_Control(pDX, IDC_CB_ART5F_MAIN_CUSTOMERGROUP, m_MAIN_CUSTOMERGROUP);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CArtikelPage5F, CPropertyPageMultiLang)
	//{{AFX_MSG_MAP(CArtikelPage5F)
	ON_CBN_SELCHANGE(IDC_CB_ART5F_ERST_TYP,		OnSelchangeCbTyp)
	ON_CBN_SELCHANGE(IDC_CB_ART5F_RF_ERST_TYP,	OnSelchangeCbRfTyp)
	ON_BN_CLICKED(IDC_PB_REFUND_FRANCE, OnPbRefund)
	ON_CBN_SELCHANGE(IDC_CB_ART5F_MAIN_CUSTOMERGROUP, &CArtikelPage5F::OnSelChangeMainCustomerGroup)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////
//  Dialogfunktionen

void CArtikelPage5F::MakeDialog()
{
	m_dlg.InitDialog( m_UEBEREINH );
	m_dlg.InitDialog( m_MGEUNTER );
	m_dlg.InitDialog( m_ERST_TYP );

	m_Pos_CODE_LPPR = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_CODE_LPPR );

	m_Pos_ERST_PROZ = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ERST_PROZ );

	m_Pos_ERST_BASIS = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ERST_BASIS );

	m_Pos_ERST_WERT = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ERST_WERT );

	m_dlg.InitDialog( m_RES_HOSP );
	m_dlg.InitDialog( m_NOEDI );
	m_dlg.InitDialog( m_VERTRBIND_EXPORT );
	m_dlg.InitDialog( m_VERTRBIND_LEGALL );
	m_dlg.InitDialog( m_VERTRBIND_BREIZH );
	m_dlg.InitDialog( m_VERTRBIND_HOSPITAL );
	m_dlg.InitDialog( m_NACHLIEFERUNG );

	m_Pos_RABATTGRUPPE_SP = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_RABATTGRP_SP );

	m_dlg.InitDialog( m_CODE_BLOQUAGE );

	m_dlg.InitDialog( m_CODE_EPHMRA );

	m_dlg.InitDialog( m_RF_DATUM );
	m_dlg.InitDialog( m_RF_ERST_TYP );

	m_Pos_RF_CODE_LPPR = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_RF_CODE_LPPR );

	m_Pos_RF_ERST_PROZ = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_RF_ERST_PROZ );

	m_Pos_RF_ERST_BASIS = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_RF_ERST_BASIS );

	m_Pos_RF_ERST_WERT = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_RF_ERST_WERT );

	m_dlg.InitDialog( m_PB_REFUND );

	m_dlg.InitDialog(m_CONSIGNED);
	m_dlg.InitDialog(m_MAIN_CUSTOMERGROUP);

	m_nMaxFields = m_dlg.GetFieldNumber();
}

void CArtikelPage5F::ResetVkn( )
{
	m_RD_LPPRCODE.Reset();
	m_RD_RABATTGRP.Reset();
	m_RD_REIMBPCT.Reset();
	m_RD_EPHMRA.Reset();
}

/* class CV_ARTIKEL_Erstattung : public ChValBase
{
public:
	CV_ARTIKEL_Erstattung( CArtikelPage5F* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		// bei Änderung Erstattungstyp Felder neu freigeben / sperren
		((CArtikelPage5F*)m_pWnd)->ShowRefundFields( true );
		return true;
	}
}; */

/**---------------------------------------------------------------------------*/
BOOL CArtikelPage5F::EndValidate( int *ind, BOOL bMeldung )
{
	// damit die Erstattungswerte auch neu berechnet werden, wenn F1 ohne Verlassen des letzten Feldes gedrückt wird (kein Aufruf PostProc())
	// nicht durchführen bei Aufruf aus View, ohne dass die Page überhaupt aktiv war
	if (( (CArtikelView* )m_pView)->WasPageActive(4) )
	{
		ChangeRefundValues( 1 );
		ChangeRefundValues( 2 );
	}

	if ( m_pBufZartfrance->REIMBURSEMENT_TYPE[0] == '1' &&
	   ( m_REIMB_PCT == 0 || 
         m_pBufZartfrance->TFR_BASE_PRICE == 0 ) )
	{
		if ( bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1002) );

		*ind = m_Pos_ERST_PROZ;
		return FALSE;
	}

	if ( m_pBufCartrefundfrance->REIMBURSEMENT_TYPE[0] == '1' &&
	   ( m_RF_REIMB_PCT == 0 || 
         m_pBufCartrefundfrance->TFR_BASE_PRICE == 0 ) )
	{
		if ( bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1002) );

		*ind = m_Pos_RF_ERST_PROZ;
		return FALSE;
	}

/*	--> auch LPPR- Kits auf PZN möglich - dann muss / darf kein LPPR-Code hinterlegt sein
	if ( m_pBufZartfrance->REIMBURSEMENT_TYPE[0] == '2' &&
		 strncmp (m_pBufZartfrance->CODE_LPPR, "               ", L_ZARTFRANCE_CODE_LPPR ) == 0)
	{
		if ( bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1003) );

		*ind = m_Pos_CODE_LPPR;
		return FALSE;
	}
*/
	if ( m_pBufZartfrance->REIMBURSEMENT_TYPE[0] == '3' &&
		 m_pBufZartfrance->REIMBURSEMENT_PERC == 0 )
	{
		if ( bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1004) );

		*ind = m_Pos_ERST_PROZ;
		return FALSE;
	}

	if ( m_pBufCartrefundfrance->REIMBURSEMENT_TYPE[0] == '3' &&
		 m_pBufCartrefundfrance->REIMBURSEMENT_PERC == 0 )
	{
		if ( bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1004) );

		*ind = m_Pos_RF_ERST_PROZ;
		return FALSE;
	}

	return TRUE;
}

/**---------------------------------------------------------------------------*/
BOOL CArtikelPage5F::ShowLpprCode( short sWhichRefund, BOOL , BOOL bMeldung )
{
	int iStat;
	CString desc;
	double val;
	CString Errmld;

	// LPPR-Code ist nur relevant bei Erstattungstyp 2
	/* if (m_pBufZartfrance->REIMBURSEMENT_TYPE[0] != '2')
	{
		return TRUE;
	} */

	if (sWhichRefund == 1)
		iStat = m_RD_LPPRCODE.IPlausi( m_pBufZartfrance->CODE_LPPR, desc, val, &Errmld);
	else if (sWhichRefund == 2)
		iStat = m_RD_LPPRCODE.IPlausi( m_pBufCartrefundfrance->CODE_LPPR, desc, val, &Errmld);
	else
		return false;

	/* not needed anymore due to FR-Revival ID 30:
	if ( iStat == 0 && bShow )	
	{
		m_pBufZartfrance->REIMBURSEMENT_VAL = dErstattung;
		m_ERST_WERT.p_SetInput();
	}
	*/
	
	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

/**---------------------------------------------------------------------------*/
void CArtikelPage5F::SucheLpprCode( short sWhichRefund )
{
	CClpprcodeSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING889), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if (sWhichRefund == 1)
		{
			if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufZartfrance->CODE_LPPR ) == 0 )
			{
				m_CODE_LPPR.p_SetInput();
				m_CODE_LPPR.SetFocus();
				ShowLpprCode( sWhichRefund, TRUE );
			}
		}
		else if (sWhichRefund == 2)
		{
			if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufCartrefundfrance->CODE_LPPR ) == 0 )
			{
				m_RF_CODE_LPPR.p_SetInput();
				m_RF_CODE_LPPR.SetFocus();
				ShowLpprCode( sWhichRefund, TRUE );
			}
		}
		else
			return;
	}

	m_SelBox.CloseCursor();
}

// Erstattungs- Prozent
BOOL CArtikelPage5F::ShowReimbPct( short sWhichRefund, BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Errmld;

	if (sWhichRefund == 1)
	{
		m_REIMB_PCT = 0.0;
		iStat = m_RD_REIMBPCT.IPlausi( (long)m_pBufZartfrance->REIMBURSEMENT_PERC, m_REIMB_PCT, &Errmld);
	}
	else if (sWhichRefund == 2)
	{
		m_RF_REIMB_PCT = 0.0;
		iStat = m_RD_REIMBPCT.IPlausi( (long)m_pBufCartrefundfrance->REIMBURSEMENT_PERC, m_RF_REIMB_PCT, &Errmld);
	}
	else
		return false;
	
	if ( bShow )	// neu
	{
		CString str;

		if (sWhichRefund == 1)
		{
			str.Format(" %.2lf %%", m_REIMB_PCT);
			GetDlgItem( IDC_ST_ART5F_ERST_PROZ )->SetWindowText( str );
		}
		else
		{
			str.Format(" %.2lf %%", m_RF_REIMB_PCT);
			GetDlgItem( IDC_ST_ART5F_RF_ERST_PROZ )->SetWindowText( str );
		}
	}

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

void CArtikelPage5F::SucheReimbPct( short sWhichRefund )
{
	CReimbursementPctSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1285), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		long pct_id;
		int i = m_SelBox.PrimeKeyOfSelectedRecord( &pct_id );

		if (sWhichRefund == 1)
			m_pBufZartfrance->REIMBURSEMENT_PERC = pct_id;
		else if (sWhichRefund == 2)
			m_pBufCartrefundfrance->REIMBURSEMENT_PERC = pct_id;
		else
			return;

		if ( i == 0 )
		{
			if (sWhichRefund == 1)
			{
				m_ERST_PROZ.p_SetInput();
				m_ERST_PROZ.SetFocus();
			}
			else
			{
				m_RF_ERST_PROZ.p_SetInput();
				m_RF_ERST_PROZ.SetFocus();
			}

			ShowReimbPct( sWhichRefund, TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// Rabattgruppe
BOOL CArtikelPage5F::ShowRabGr_Sp( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;
	iStat = m_RD_RABATTGRP.IPlausi( m_pBufZartfrance->REBATE_GROUP_SPEC, Name, &Errmld);
	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_RABATTGRP_SP )->SetWindowText( Name );
	if ( iStat > 1 && bMeldung ) MsgBoxOK( Errmld );
	return iStat <= 1;
}

void CArtikelPage5F::SucheRabGr_Sp( )
{
	CZrabgrpSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING10005), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufZartfrance->REBATE_GROUP_SPEC ) == 0 )
		{
			m_RABATTGRP_SP.p_SetInput();
			m_RABATTGRP_SP.SetFocus();
			ShowRabGr_Sp( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

// EphMRA-Code

BOOL CArtikelPage5F::TestEphmraCode( BOOL bMeldung )
{
	if (strncmp (m_pBufEphmra->ARTICLE_CODE, "     ", L_CEPHMRACODE_CODE_EPHMRA) == 0)
		return true;

	BOOL bOk = m_pBufEphmra->ARTICLE_CODE[4] != ' ';
	if ( !bOk && bMeldung )
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1290) );
	return bOk;
}

BOOL CArtikelPage5F::ShowEphmraCode( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	iStat = m_RD_EPHMRA.IPlausi( m_pBufEphmra->ARTICLE_CODE, Name, &Errmld);

	if ( bShow )	// neu
		GetDlgItem( IDC_ST_ARTIKEL_CODE_EPHMRA )->SetWindowText( Name );

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

void CArtikelPage5F::SucheEphmraCode( )
{
	CEphmraSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING1287), &m_SelBox,
						HCD_SCROLLINFO );
//						HCD_SCROLLINFO | HCD_BUTTONALTERN );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( m_pBufEphmra->ARTICLE_CODE ) == 0 )
		{
			m_CODE_EPHMRA.p_SetInput();
			m_CODE_EPHMRA.SetFocus();
			ShowEphmraCode( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}

/////////////////////////////////////////////////////////////
//  Verknuepfungen lesen

/**---------------------------------------------------------------------------*/
class CV_ARTIKEL_Lppr : public ChValBase
{
public:
	CV_ARTIKEL_Lppr( CArtikelPage5F* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage5F*)m_pWnd)->ShowLpprCode( 1, bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage5F*)m_pWnd)->SucheLpprCode( 1 );
	}
	void PostProc( )
	{
		((CArtikelPage5F*)m_pWnd)->ChangeRefundValues( 1 );
	}
};

class CV_ARTIKEL_Rf_Lppr : public ChValBase
{
public:
	CV_ARTIKEL_Rf_Lppr( CArtikelPage5F* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage5F*)m_pWnd)->ShowLpprCode( 2, bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage5F*)m_pWnd)->SucheLpprCode( 2 );
	}
	void PostProc( )
	{
		((CArtikelPage5F*)m_pWnd)->ChangeRefundValues( 2 );
	}
};

class CV_ReimbPct : public ChValBase
{
public:
	CV_ReimbPct( CArtikelPage5F* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage5F*)m_pWnd)->ShowReimbPct( 1, bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage5F*)m_pWnd)->SucheReimbPct( 1 );
	}
	void PostProc( )
	{
		((CArtikelPage5F*)m_pWnd)->ChangeRefundValues( 1 );
	}
};

class CV_Rf_ReimbPct : public ChValBase
{
public:
	CV_Rf_ReimbPct( CArtikelPage5F* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage5F*)m_pWnd)->ShowReimbPct( 2, bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage5F*)m_pWnd)->SucheReimbPct( 2 );
	}
	void PostProc( )
	{
		((CArtikelPage5F*)m_pWnd)->ChangeRefundValues( 2 );
	}
};

class CV_Basis : public ChValBase
{
public:
	CV_Basis( CArtikelPage5F* pView ) : ChValBase( pView ){};
	void PostProc( )
	{
		((CArtikelPage5F*)m_pWnd)->ChangeRefundValues( 1 );
	}
};

class CV_Rf_Basis : public ChValBase
{
public:
	CV_Rf_Basis( CArtikelPage5F* pView ) : ChValBase( pView ){};
	void PostProc( )
	{
		((CArtikelPage5F*)m_pWnd)->ChangeRefundValues( 2 );
	}
};

class CV_Rf_Datum : public ChValBase
{
public:
	CV_Rf_Datum( CArtikelPage5F* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk = ((CArtikelPage5F* )m_pWnd)->TestRfDatum( );
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1424) );
		return bOk;
	}
	void PostProc( )
	{
		((CArtikelPage5F*)m_pWnd)->EnableRfType( true );
	}
};

class CV_ARTIKEL_RabGr_Sp : public ChValBase
{
public:
	CV_ARTIKEL_RabGr_Sp( CArtikelPage5F* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage5F*)m_pWnd)->ShowRabGr_Sp( bMeldung, bMeldung );
		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage5F*)m_pWnd)->SucheRabGr_Sp( );
	}
};

class CV_ARTIKEL_Code_Ephmra : public ChValBase
{
public:
	CV_ARTIKEL_Code_Ephmra( CArtikelPage5F* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtikelPage5F*)m_pWnd)->ShowEphmraCode( bMeldung, bMeldung );

		if ( bOk ) 
			bOk = ((CArtikelPage5F*)m_pWnd)->TestEphmraCode( bMeldung );

		return bOk;
	}
	void NotifyProc( )
	{
		((CArtikelPage5F*)m_pWnd)->SucheEphmraCode( );
	}
};

// CArtikelPage5F-Meldungshandler

/**---------------------------------------------------------------------------*/
void CArtikelPage5F::InitPflege( CWnd *pView  )
{ 
	CArtikelPage5F* pThisView = this;
	m_pView = pView;
	struct PFL_ARTIKEL *m_Buf	= ((CArtikelView* )pView)->GetBuffer();
	m_pBufZartfrance			= &m_Buf->zartfrance;
	m_pBufEphmra				= &m_Buf->carticlecodes[13];	// code_type = 14
	m_pBufCartrefundfrance		= &m_Buf->cartrefundfrance;

	MakeDialog();

	m_UEBEREINH.SetMask	  (ED_CHAR,
                           ED_UPPER,
	                       m_pBufZartfrance->UNIT_MULTIPLE,
                           3,
                           new ChMaskChar ); 

	m_MGEUNTER.SetMask    (ED_LONG,
                           ED_NORMAL,
						   &m_pBufZartfrance->QTY_SUBMULTIPLE,
                           4,
						   new ChMaskNum );

	m_ERST_TYP.SetMask	  ( "0123", m_pBufZartfrance->REIMBURSEMENT_TYPE );

	m_ERST_PROZ.SetMask   (ED_LONG,
                           ED_NORMAL,
						   &m_pBufZartfrance->REIMBURSEMENT_PERC,
                           3,
                           0,
						   new ChMaskDblPos,
						   new CV_ReimbPct( pThisView ));

	m_ERST_WERT.SetMask   (ED_DBL,
                           ED_NORMAL,
						   &m_pBufZartfrance->REIMBURSEMENT_VAL,
                           L_ZARTFRANCE_REIMBURSEMENT_VAL + 1,
                           N_ZARTFRANCE_REIMBURSEMENT_VAL,
						   new ChMaskDblPos );

	m_ERST_BASIS.SetMask   (ED_DBL,
                           ED_NORMAL,
						   &m_pBufZartfrance->TFR_BASE_PRICE,
// nicht mehr 04/2014	   &m_nBASIS_PREIS,
                           L_ZARTFRANCE_TFR_BASE_PRICE + 1,
                           N_ZARTFRANCE_TFR_BASE_PRICE,
						   new ChMaskDblPos,
						   new CV_Basis( pThisView ));

	m_CODE_LPPR.SetMask   (ED_CHAR,
                           ED_UPPER,
						   m_pBufZartfrance->CODE_LPPR,
						   L_ZARTFRANCE_CODE_LPPR,	
						   new ChMaskChar, 
						   new CV_ARTIKEL_Lppr( pThisView ) );

 	m_RES_HOSP.SetMask ( '1', '0', m_pBufZartfrance->RESERVE_HOSP);
 	m_NOEDI.SetMask ( '1', '0', m_pBufZartfrance->NOT_VIA_EDI);
	m_VERTRBIND_EXPORT.SetMask( 1, 0, &m_pBufZartfrance->DISTR_RESTR_EXPORT );
	m_VERTRBIND_LEGALL.SetMask ( '1', '0', m_pBufZartfrance->DISTR_RESTR_LEGALL);
	m_VERTRBIND_BREIZH.SetMask ( '1', '0', m_pBufZartfrance->DISTR_RESTR_BREIZH);
	m_VERTRBIND_HOSPITAL.SetMask ( '1', '0', m_pBufZartfrance->DISTR_RESTR_HOSP);
	m_NACHLIEFERUNG.SetMask ( '1', '0', m_pBufZartfrance->NACHLIEFERUNG);
	m_CONSIGNED.SetMask(1, 0, &m_pBufZartfrance->CONSIGNMENT_PAYMENT_FLAG);

	m_RABATTGRP_SP.SetMask		(ED_CHAR,
		                         ED_UPPER,
								 m_pBufZartfrance->REBATE_GROUP_SPEC,
				                 3,
								 new ChMaskNum,
								 new CV_ARTIKEL_RabGr_Sp( pThisView ) );

	m_CODE_BLOQUAGE.SetMask	  ( "023489CHS", m_pBufZartfrance->CODE_BLOQUAGE );

	m_CODE_EPHMRA.SetMask		(ED_CHAR,
		                         ED_UPPER,
			                     m_pBufEphmra->ARTICLE_CODE,
				                 5,
								 new ChMaskChar,
								 new CV_ARTIKEL_Code_Ephmra( pThisView ) );

	m_RF_DATUM.SetMask		(ED_LDATE,
                             ED_NORMAL,
                             &m_pBufCartrefundfrance->DATEFROM,
                             L_LDATUM,
                             new ChMaskLDate,
							 new CV_Rf_Datum( pThisView ) );

	m_RF_ERST_TYP.SetMask	( "0123", m_pBufCartrefundfrance->REIMBURSEMENT_TYPE );

	m_RF_ERST_PROZ.SetMask	(ED_LONG,
							ED_NORMAL,
							&m_pBufCartrefundfrance->REIMBURSEMENT_PERC,
							3,
							0,
							new ChMaskDblPos,
							new CV_Rf_ReimbPct( pThisView ));

	m_RF_ERST_WERT.SetMask   (ED_DBL,
                           ED_NORMAL,
						   &m_pBufCartrefundfrance->REIMBURSEMENT_VAL,
                           L_CARTREFUNDFRANCE_REIMBURSEMENT_VAL + 1,
                           N_CARTREFUNDFRANCE_REIMBURSEMENT_VAL,
						   new ChMaskDblPos );

	m_RF_ERST_BASIS.SetMask   (ED_DBL,
                           ED_NORMAL,
						   &m_pBufCartrefundfrance->TFR_BASE_PRICE,
                           L_CARTREFUNDFRANCE_TFR_BASE_PRICE + 1,
                           N_CARTREFUNDFRANCE_TFR_BASE_PRICE,
						   new ChMaskDblPos,
						   new CV_Rf_Basis( pThisView ));

	m_RF_CODE_LPPR.SetMask   (ED_CHAR,
                           ED_UPPER,
						   m_pBufCartrefundfrance->CODE_LPPR,
						   L_CARTREFUNDFRANCE_CODE_LPPR,	
						   new ChMaskChar, 
						   new CV_ARTIKEL_Rf_Lppr( pThisView ) );

	m_bInitialized = TRUE; 
}

/**---------------------------------------------------------------------------*/
void CArtikelPage5F::SetDialog( BOOL bDialog )
{   
	m_dlg.SetDialog( bDialog );
}

void CArtikelPage5F::SetMSStandard( BOOL bStandard )
{   
 	m_dlg.SetMSStandard( bStandard );
}

void CArtikelPage5F::EnableFields( BOOL bEnab )
{   
	CString csRefundCode;

	m_dlg.EnableFields( bEnab );

	m_NOEDI.EnableWindow(false);

	csRefundCode = GetActiveRefundFields (m_pBufZartfrance->REIMBURSEMENT_TYPE[0]);
	ShowRefundFields( bEnab, csRefundCode );

	csRefundCode = GetActiveRefundFields (m_pBufCartrefundfrance->REIMBURSEMENT_TYPE[0]);
	ShowNewRefundFields( bEnab, csRefundCode );
	m_CUSTOMERGROUP.EnableWindow(bEnab);

	if (bEnab)
		EnableRfType( false );

	/* war nur nötig wg. der Verwendung von m_nBASIS_PREIS statt dem direkten DB-Feld, geändert 04/2014 
	if (TRUE == bEnab)
	{
		m_nBASIS_PREIS = m_pBufZartfrance->TFR_BASE_PRICE;
		m_ERST_BASIS.p_SetInput();
		ChangeRefundValues();
	} */
}

void CArtikelPage5F::ShowFields( )
{
	FillComboBox();

	m_dlg.ShowFields();

	ShowLpprCode( 1, TRUE );
	ShowReimbPct( 1, TRUE );

	ShowLpprCode( 2, TRUE );
	ShowReimbPct( 2, TRUE );

	ShowRabGr_Sp( TRUE );
	ShowEphmraCode( TRUE );

	ShowCustomerGroup();

	SetMainCustomerGroup();
}

void CArtikelPage5F::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}

void CArtikelPage5F::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
	FillCustmerGroup();
}

void CArtikelPage5F::ActivateField( int nr )
{
	m_dlg.ActivateField( nr );
}

BOOL CArtikelPage5F::Validate( BOOL bMeldung )
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

/////////////////////////////////////////////////////////////////////////////
// CLieferPage1 message handlers

BOOL CArtikelPage5F::OnSetActive()
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
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING323) );
	} 
	return bOk;
}

BOOL CArtikelPage5F::OnKillActive()
{
	BOOL bOk = true;
	bOk = CPropertyPageMultiLang::OnKillActive();
	if ( bOk )
	{
//		AfxMessageBox( CResString::ex().getStrTblText(IDS_STRING324) );
		SetValidation( FALSE );
		DataExchangeToBuffer( );  //  Puffer wie Eingabe
	} 
	return bOk;
}

void CArtikelPage5F::NextDlgCtrl()
{
	if ( GetFocus() == GetDlgItem( IDC_PB_REFUND_FRANCE ) )
	{
		OnPbRefund();
	}
	ChPflegePage::NextDlgCtrl();

	if ( GetFocus() == GetDlgItem( IDC_PB_REFUND_FRANCE ) )
		ChPflegePage::NextDlgCtrl();
}

void CArtikelPage5F::FillComboBox()
{
	m_ERST_TYP.ResetContent();
	m_RF_ERST_TYP.ResetContent();
	m_CODE_BLOQUAGE.ResetContent();

	m_ERST_TYP.AddString(CResString::ex().getStrTblText(IDS_STRING10181));
	m_ERST_TYP.AddString(CResString::ex().getStrTblText(IDS_STRING10182));
	m_ERST_TYP.AddString(CResString::ex().getStrTblText(IDS_STRING10183));
	m_ERST_TYP.AddString(CResString::ex().getStrTblText(IDS_STRING10184));

	// Änderungen müssen auch im PriceValidDelayView nachgezogen werden
	m_RF_ERST_TYP.AddString(CResString::ex().getStrTblText(IDS_STRING10181));
	m_RF_ERST_TYP.AddString(CResString::ex().getStrTblText(IDS_STRING10182));
	m_RF_ERST_TYP.AddString(CResString::ex().getStrTblText(IDS_STRING10183));
	m_RF_ERST_TYP.AddString(CResString::ex().getStrTblText(IDS_STRING10184));

	m_CODE_BLOQUAGE.AddString("0 = Disponible");
	m_CODE_BLOQUAGE.AddString("2 = ne tenons pas");
	m_CODE_BLOQUAGE.AddString("3 = NSFPL");
	m_CODE_BLOQUAGE.AddString("4 = Suspendu");
	m_CODE_BLOQUAGE.AddString("8 = reassort");
	m_CODE_BLOQUAGE.AddString("9 = nouveautes");
	m_CODE_BLOQUAGE.AddString("C = Contingente");
	m_CODE_BLOQUAGE.AddString("H = reserve hospitaliere");
	m_CODE_BLOQUAGE.AddString("S = Substitution");
//	m_CODE_BLOQUAGE.AddString("U = Substit. Autor.");

	FillMainCustomerGroup();
}

CString CArtikelPage5F::GetActiveRefundFields( char Reimbursement_type )
{
	CString csRefundCode = "0000";

	switch ( Reimbursement_type )
	{
		case '1':
			csRefundCode = "0110";
			break;
		case '2':
			// geändert 04/2014: vorher war Prozentsatz auch pflegbar (1100)
            csRefundCode = "1000";
			break;
        case '3':
			csRefundCode = "0100";
			break;
	}

	return csRefundCode;
}

void CArtikelPage5F::ShowRefundFields( BOOL bEnab, CString csRefundCode )
{
	// Default
	m_dlg.ShowWindow(m_Pos_CODE_LPPR, FALSE );
	m_dlg.EnableFields(m_Pos_ERST_PROZ, FALSE );
	m_dlg.EnableFields(m_Pos_ERST_BASIS, FALSE );
	m_dlg.EnableFields(m_Pos_ERST_WERT, FALSE );

	// alles deaktivieren, damit niemand in Frankreich auf die Idee kommt, hier was einzupflegen --> Pflege nur noch im neuen Subdialog!
	m_ERST_TYP.EnableWindow(false);
    
    if(bEnab) //adding dummy check to avoid compilation error
    {}
	return; 
    /*
	if (bEnab)
	{
		// nie mehr aktiv, da Pflege nur noch im neuen Subdialog!
	//	if (csRefundCode[0] == '1')
	//		m_dlg.EnableFields(m_Pos_CODE_LPPR, TRUE );
		//
				
		if (csRefundCode[1] == '1')
			m_dlg.EnableFields(m_Pos_ERST_PROZ, TRUE );

		if (csRefundCode[2] == '1')
			m_dlg.EnableFields(m_Pos_ERST_BASIS, TRUE );

		if (csRefundCode[3] == '1')
			m_dlg.EnableFields(m_Pos_ERST_WERT, TRUE );
	}
    */
}

void CArtikelPage5F::ShowNewRefundFields( BOOL bEnab, CString csRefundCode )
{
	// Default
	m_dlg.ShowWindow(m_Pos_RF_CODE_LPPR, FALSE );
	m_dlg.EnableFields(m_Pos_RF_ERST_PROZ, FALSE );
	m_dlg.EnableFields(m_Pos_RF_ERST_BASIS, FALSE );
	m_dlg.EnableFields(m_Pos_RF_ERST_WERT, FALSE );
	
	// alles deaktivieren, damit niemand in Frankreich auf die Idee kommt, hier was einzupflegen --> Pflege nur noch im neuen Subdialog!
	m_RF_DATUM.EnableWindow(false);
	m_RF_ERST_TYP.EnableWindow(false);
    if (bEnab)
        {}
	return; 
	/*
	if (bEnab)
	{
		if (csRefundCode[0] == '1')
			m_dlg.EnableFields(m_Pos_RF_CODE_LPPR, TRUE );
	
		if (csRefundCode[1] == '1')
			m_dlg.EnableFields(m_Pos_RF_ERST_PROZ, TRUE );

		if (csRefundCode[2] == '1')
			m_dlg.EnableFields(m_Pos_RF_ERST_BASIS, TRUE );

		if (csRefundCode[3] == '1')
			m_dlg.EnableFields(m_Pos_RF_ERST_WERT, TRUE );
	}
    */
}

void CArtikelPage5F::ChangeRefundValues( short sWhichRefund )
{
	double  reimbursement_perc = 0.0;
    double  reimbursement_val  = 0.0;
    char    reimbursement_type = '0';
    char    code_lppr[16];
    double  tfr_base_price = 0.0;

	// Unterscheidung, welche Tabelle (aktuell = zartfrance oder zukünftig = cartrefundfrance) gerade bearbeitet werden soll
	if (sWhichRefund == 1)
		reimbursement_type = m_pBufZartfrance->REIMBURSEMENT_TYPE[0];
	/*else if (sWhichRefund == 2)
		reimbursement_type = m_pBufCartrefundfrance->REIMBURSEMENT_TYPE[0]; --> wird nur noch im neuen Subdialog gepflegt / berechnet!*/
	else
		return;

	// Erstattungstyp 0 --> alle Felder auf Default setzen
	if (reimbursement_type == '0')
	{
		strncpy (code_lppr, "               ", L_ZARTFRANCE_CODE_LPPR);
		reimbursement_perc = 0;
		tfr_base_price = 0;
		reimbursement_val = 0;
	} 
	// Erstattungstyp 1 --> LPPR-Code auf Default, Erstattungswert rechnen (Basispreis * Prozentsatz)
	else if (reimbursement_type == '1')
	{
		double BasePrice = 0.0;
		double Percent = 0.0;
		
		if (sWhichRefund == 1)
		{
			m_ERST_BASIS.p_GetInput();
			BasePrice = m_pBufZartfrance->TFR_BASE_PRICE;
			Percent = m_REIMB_PCT;
			reimbursement_perc = m_pBufZartfrance->REIMBURSEMENT_PERC;
		}
		else
		{
			m_RF_ERST_BASIS.p_GetInput();
			BasePrice = m_pBufCartrefundfrance->TFR_BASE_PRICE;
			Percent = m_RF_REIMB_PCT;
			reimbursement_perc = m_pBufCartrefundfrance->REIMBURSEMENT_PERC;
		}

		strncpy (code_lppr, "               ", L_ZARTFRANCE_CODE_LPPR);
		tfr_base_price = BasePrice;
		reimbursement_val = BasePrice * Percent / 100;
	} 
	// Erstattungstyp 2 --> Basispreis & Prozentsatz auf 0 setzen, Erstattungswert aus clpprcode & clpprcompack holen
	// geändert 04/2014, vorher wurde Erstattungswert aus lpprPrice & Prozentsatz gerechnet und damit immer auf 0 gesetzt, da Prozentsatz immer 0 war
	else if (reimbursement_type == '2')
	{
		/*
		CString sql;
		CString str;
		double lpprPrice = 0.0;

		if (sWhichRefund == 1)
			m_CODE_LPPR.GetWindowText(str);
		else
			m_RF_CODE_LPPR.GetWindowText(str);
		
		sql.Format( "select nvl(sum(reimbursement_val * quantity), " 
			"(select reimbursement_val from clpprcode where code_lppr = '%s')) "
			"from clpprcode l, clpprcompack p where l.code_lppr = p.code_lppr_element "
			"and p.article_no_pack = %ld ", str, m_pBufZartfrance->ARTICLENO);

		SqlRead(sql, &lpprPrice, NULL);
		
		reimbursement_perc = 0;
		tfr_base_price = 0;
		reimbursement_val = lpprPrice;
		strncpy (code_lppr, str, L_ZARTFRANCE_CODE_LPPR);
		*/

		strncpy (code_lppr, "               ", L_ZARTFRANCE_CODE_LPPR);
		reimbursement_perc = 0;
		tfr_base_price = 0;
		reimbursement_val = ((CArtikelView* )m_pView)->m_Doc.Read_LpprReimbValueSum(::Today());
	} 
	// Erstattungstyp 3 --> LPPR-Code & TFR-Basispreis auf Default, Erstattungswert rechnen (aktueller AVP * Prozentsatz)
	else if (reimbursement_type == '3')
	{
		double avp = 0.0;
		double Percent = 0.0;
		CString sql;

		if (sWhichRefund == 1)
		{
			Percent = m_REIMB_PCT;
			reimbursement_perc = m_pBufZartfrance->REIMBURSEMENT_PERC;

			// geändert 04/2014, AddDayToPhoDate ergänzt, damit der Wert auf Basis des heute rausgeschickten (weil morgen gültigen) Preises ermittelt wird
			sql.Format( "select avp from ZARTPREIS p where ARTIKEL_NR=%ld and DATUMGUELTIGAB= "
						"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = p.artikel_nr "
						"and DATUMGUELTIGAB <= %ld)", m_pBufZartfrance->ARTICLENO, ::AddDayToPhoDate(::Today(), 1) );
		}
		else
		{
			Percent = m_RF_REIMB_PCT;
			reimbursement_perc = m_pBufCartrefundfrance->REIMBURSEMENT_PERC;

			sql.Format( "select avp from ZARTPREIS p where ARTIKEL_NR=%ld and DATUMGUELTIGAB= "
						"(select max(DATUMGUELTIGAB) from ZARTPREIS where ARTIKEL_NR = p.artikel_nr "
						"and DATUMGUELTIGAB <= %ld)", m_pBufCartrefundfrance->ARTICLENO, m_pBufCartrefundfrance->DATEFROM );
		}

		SqlRead(sql, &avp, NULL);

		strncpy (code_lppr, "               ", L_ZARTFRANCE_CODE_LPPR);
		tfr_base_price = 0;
		reimbursement_val = avp * Percent / 100;
	} 

	// Unterscheidung, welche Tabelle (aktuell = zartfrance oder zukünftig = cartrefundfrance) gerade bearbeitet werden soll
	if (sWhichRefund == 1)
	{
		m_pBufZartfrance->REIMBURSEMENT_PERC	= reimbursement_perc;
		m_pBufZartfrance->REIMBURSEMENT_VAL		= reimbursement_val;
		strncpy (m_pBufZartfrance->CODE_LPPR, code_lppr, L_ZARTFRANCE_CODE_LPPR);
		m_pBufZartfrance->TFR_BASE_PRICE		= tfr_base_price;

		// ggfs. geänderten %-Satz anzeigen
		ShowReimbPct( sWhichRefund, ( (CArtikelView* )m_pView)->WasPageActive(4) );

		m_ERST_PROZ.p_SetInput();
		m_ERST_WERT.p_SetInput();
		m_CODE_LPPR.p_SetInput();
		m_ERST_BASIS.p_SetInput();
	}
	else if (sWhichRefund == 2)
	{
		m_pBufCartrefundfrance->REIMBURSEMENT_PERC	= reimbursement_perc;
		m_pBufCartrefundfrance->REIMBURSEMENT_VAL		= reimbursement_val;
		strncpy (m_pBufCartrefundfrance->CODE_LPPR, code_lppr, L_CARTREFUNDFRANCE_CODE_LPPR);
		m_pBufCartrefundfrance->TFR_BASE_PRICE		= tfr_base_price;

		// ggfs. geänderten %-Satz anzeigen
		ShowReimbPct( sWhichRefund, ( (CArtikelView* )m_pView)->WasPageActive(4) );

		m_RF_ERST_PROZ.p_SetInput();
		m_RF_ERST_WERT.p_SetInput();
		m_RF_CODE_LPPR.p_SetInput();
		m_RF_ERST_BASIS.p_SetInput();
	}
}

void CArtikelPage5F::OnSelchangeCbTyp()
{
	CString csRefundCode;
	m_ERST_TYP.p_GetInput();
	csRefundCode = GetActiveRefundFields (m_pBufZartfrance->REIMBURSEMENT_TYPE[0]);
	ShowRefundFields( true, csRefundCode );
	ChangeRefundValues( 1 );
}

void CArtikelPage5F::OnSelchangeCbRfTyp()
{
	CString csRefundCode;
	m_RF_ERST_TYP.p_GetInput();
	csRefundCode = GetActiveRefundFields (m_pBufCartrefundfrance->REIMBURSEMENT_TYPE[0]);
	ShowNewRefundFields( true, csRefundCode );
	ChangeRefundValues( 2 );
}

void CArtikelPage5F::EnableRfType( BOOL bFocus )
{   
	// weil Datumsfeld temporär noch deaktiviert ist
	if (!m_RF_DATUM.IsWindowEnabled())
		return;

	m_RF_DATUM.p_GetInput();

	if (m_pBufCartrefundfrance->DATEFROM > 0)
	{
		m_RF_ERST_TYP.EnableWindow (true);

		if (bFocus)
			m_RF_ERST_TYP.SetFocus();
	}
	else
	{
		m_RF_ERST_TYP.EnableWindow (false);

		ShowNewRefundFields( false, "0000" );

		if (bFocus)
			m_RABATTGRP_SP.SetFocus();
	}
}

BOOL CArtikelPage5F::TestRfDatum( )
{
	BOOL bOk = TRUE; 

	// weil sonst das Datum im Puffer auf 0 gesetzt und der Satz gelöscht wird
	if (!( (CArtikelView* )m_pView)->WasPageActive(4) )
		return bOk;

	m_RF_DATUM.p_GetInput();

	if ( m_pBufCartrefundfrance->DATEFROM > 0 )
		bOk = m_pBufCartrefundfrance->DATEFROM > ::Today();

	return bOk;
}

void CArtikelPage5F::OnPbRefund() 
{
	m_RF_DATUM.p_GetInput();
	m_RF_ERST_TYP.p_GetInput();
	m_RF_ERST_PROZ.p_GetInput();
	m_RF_ERST_WERT.p_GetInput();
	m_RF_ERST_BASIS.p_GetInput();

	CRefundFrance dlg(	&((CArtikelView* )m_pView)->m_Doc.GetBuffer()->cartrefundfrance, (CArtikelView* )m_pView );
	dlg.DoModal();

	m_RF_DATUM.p_SetInput();
	m_RF_ERST_TYP.p_SetInput();
	m_RF_ERST_PROZ.p_SetInput();
	m_RF_ERST_WERT.p_SetInput();
	m_RF_ERST_BASIS.p_SetInput();

	ChangeRefundValues(1);
}

void CArtikelPage5F::OnSelChangeMainCustomerGroup()
{
	int index = m_MAIN_CUSTOMERGROUP.GetCurSel();

	if (index >= 0)
	{
		CString sEntry;
		m_MAIN_CUSTOMERGROUP.GetLBText(index, sEntry);
		CString sClassID = sEntry.Left(sEntry.Find(" - "));
		long lClassID = atol(sClassID);
		m_pBufZartfrance->MAIN_PRE_CUSTOMERGROUP_NO = lClassID;
		m_pBufPrewholeCustomerGroup = GetMainCustomerGroup(m_pBufZartfrance->MAIN_PRE_CUSTOMERGROUP_NO, "PRE");
	}
}

void CArtikelPage5F::ShowCustomerGroup()
{
	short index = 1;
	bool fnd = true;
	CString cErrmld;
	long lStatus;

	while ((index < NUMBER_OF_PREWHOLECUSTOMERGROUP) && (fnd == true))
	{
		PREWHOLE_CUSTOMERGROUP* pItem = ((CArtikelView*)m_pView)->m_Doc.GetMainCustomerGroup(index);

		if (pItem != NULL)
		{
			((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
			lStatus = ((CArtikelView*)m_pView)->m_Doc.ReadRecord_PrewholeArtCustomerGroups(cErrmld, pItem->CUSTOMERGROUP_NO);
			((CEkZdpApp*)AfxGetApp())->EndWaitAction();

			m_CUSTOMERGROUP.SetCheck(index - 1, FALSE);
			isOldChecked[index - 1] = 0;

			if (lStatus == 0)
			{
				m_CUSTOMERGROUP.SetCheck(index - 1, TRUE);
				isOldChecked[index - 1] = 1;
			}
		}
		else
		{
			fnd = false;
		}
		index++;
	}
}

void CArtikelPage5F::FillCustmerGroup()
{
	short index = 1;
	bool fnd = true;
	CString cErrmld;
	long lStatus;

	while ((index < NUMBER_OF_PREWHOLECUSTOMERGROUP) && (fnd == true))
	{
		PREWHOLE_CUSTOMERGROUP* pItem = ((CArtikelView*)m_pView)->m_Doc.GetMainCustomerGroup(index);

		if (pItem != NULL)
		{
			BOOL isChecked = m_CUSTOMERGROUP.GetCheck(index - 1);
			if (isChecked != isOldChecked[index - 1])
			{
				if (isChecked)
				{
					((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
					lStatus = ((CArtikelView*)m_pView)->m_Doc.InsertRecord_PrewholeArtCustomerGroups(cErrmld, pItem->CUSTOMERGROUP_NO);
					isOldChecked[index - 1] = 1;
					((CEkZdpApp*)AfxGetApp())->EndWaitAction();
				}
				else
				{
					((CEkZdpApp*)AfxGetApp())->BeginWaitAction();
					lStatus = ((CArtikelView*)m_pView)->m_Doc.DeleteRecord_PrewholeArtCustomerGroups(cErrmld, pItem->CUSTOMERGROUP_NO);
					isOldChecked[index - 1] = 0;
					((CEkZdpApp*)AfxGetApp())->EndWaitAction();
				}
			}
		}
		else
		{
			fnd = false;
		}
		index++;
	}
}

struct PREWHOLE_CUSTOMERGROUP* CArtikelPage5F::GetMainCustomerGroup(long classID, CString classType)
{
	return ((CArtikelView*)m_pView)->m_Doc.GetMainCustomerGroup(classID, classType);
}
void CArtikelPage5F::FillMainCustomerGroup()
{
	// load the entries, fill the combo
	m_pBufPrewholeCustomerGroup = GetMainCustomerGroup(m_pBufZartfrance->MAIN_PRE_CUSTOMERGROUP_NO, "PRE");
	// takes care of filling dynamically the combobox with long id and description
	m_CUSTOMERGROUP.ResetContent();
	m_MAIN_CUSTOMERGROUP.ResetContent();
	short index = 0;
	bool fnd = true;
	while ((index < NUMBER_OF_PREWHOLECUSTOMERGROUP) && (fnd == true))
	{
		PREWHOLE_CUSTOMERGROUP* pItem = ((CArtikelView*)m_pView)->m_Doc.GetMainCustomerGroup(index);
		if (pItem != NULL)
		{
			CString sEntry = "";
			sEntry.Format("%ld - %s", pItem->CUSTOMERGROUP_NO, pItem->DESIGNATION);
			sEntry.Trim();
			if (index != 0)
				m_CUSTOMERGROUP.AddString(sEntry);
			m_MAIN_CUSTOMERGROUP.AddString(sEntry);
		}
		else
		{
			fnd = false;
		}
		index++;
	}
}

void CArtikelPage5F::SetMainCustomerGroup()
{
	if ((m_pBufPrewholeCustomerGroup != NULL) && (m_MAIN_CUSTOMERGROUP.GetCount() > 0))
	{
		int index = 0;
		bool fnd = false;

		CString sID;
		sID.Format("%ld ", m_pBufPrewholeCustomerGroup->CUSTOMERGROUP_NO);

		while ((index < m_MAIN_CUSTOMERGROUP.GetCount()) && (fnd == false))
		{
			CString sEntry;
			m_MAIN_CUSTOMERGROUP.GetLBText(index, sEntry);
			if (sEntry.Left(sID.GetLength()).CompareNoCase(sID) == 0)
			{
				fnd = true;
				m_MAIN_CUSTOMERGROUP.SetCurSel(index);
				m_MAIN_CUSTOMERGROUP.UpdateWindow();
			}
			index++;
		}
	}
}
