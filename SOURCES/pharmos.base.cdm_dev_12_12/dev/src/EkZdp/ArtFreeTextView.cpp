/******************************************************************************/
/**                                                                           */
/**   Author : R. Raab PRZ GmbH	    										  */
/**   Date   : 10.10.2007                                                     */
/**                                                                           */
/******************************************************************************/

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtFreeTextView.h"
#include "ServerDatum.h"
#include "FeldBreite.h"

#include <phxlib/CtexttypesSelCtrl.h>

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskUmlaut.h>
#include <eklibs/hamfcs/hMskDate.h>
#include <eklibs/hamfcs/hMskDbl.h>
#include <eklibs/hamfcs/hMskDblPos.h>

#include <phxlib/PhxUtil.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CArtFreeTextView, CFormViewMultiLang)

/*----------------------------------------------------------------------------*/
CArtFreeTextView::CArtFreeTextView()
	: ChPflegeView(CArtFreeTextView::IDD),
	  m_CodeConverterBasis( m_ED_ARTCODE, m_ED_ARTNR, m_ArtBasisSelBox )
{
}

/*----------------------------------------------------------------------------*/
CArtFreeTextView::~CArtFreeTextView()
{
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArtFreeTextView)
	DDX_Control(pDX, IDC_ST_ARTFREETEXT_ART_INFO,			m_ST_SELECTION_INFO);
	DDX_Control(pDX, IDC_ED_ARTFREETEXT_ARTIKELNR,			m_ED_ARTNR);
	DDX_Control(pDX, IDC_ED_ARTFREETEXT_ARTIKEL_CODE,		m_ED_ARTCODE);
	DDX_Control(pDX, IDC_ED_ARTFREETEXT_TEXTTYP,			m_ED_TEXTTYPE);
	DDX_Control(pDX, IDC_ED_ARTFREETEXT_DATEFROM,			m_ED_DATEFROM);
	DDX_Control(pDX, IDC_ED_ARTFREETEXT_DATETO,				m_ED_DATETO);
	DDX_Control(pDX, IDC_ED_ARTFREETEXT_TEXT,				m_ED_TEXT);
	DDX_Control(pDX, IDC_LC_ARTFREETEXT_BOX,				m_BOX);
	//}}AFX_DATA_MAP
}

/*----------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CArtFreeTextView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(CArtFreeTextView)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LC_ARTFREETEXT_BOX, OnItemchangedLcBox)
	//}}AFX_MSG_MAP
/////////////////////////////////////////////////////////////////////////////
//printing cformview
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
END_MESSAGE_MAP()

//-----------------------------------------------------------
BOOL CArtFreeTextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(1);

	pInfo->m_pPD->m_pd.Flags &= ~PD_NOSELECTION;
	pInfo->m_pPD->m_pd.hInstance = AfxGetInstanceHandle();

	// default preparation
	return DoPreparePrinting(pInfo);
}

//-----------------------------------------------------------
void CArtFreeTextView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
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
void CArtFreeTextView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo /* = NULL */)
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
void CArtFreeTextView::grapImage( )
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
void CArtFreeTextView::OnFilePrint() 
{
	grapImage( );
	CFormViewMultiLang::OnFilePrint() ;
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextView::OnItemchangedLcBox(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pNMHDR) {}
	/* markierte Zeile in Edits */
	*pResult = 0;

	int pos;
	CArtFreeTextBox::CARTFREETEXTCODES codeBuff;

	if ((pos = m_BOX.GetNextItem(-1, LVNI_SELECTED)) >= 0 && m_bShowSelect )
	{
		m_BOX.SelectedArtFreeText(m_pBuf, &codeBuff);	
		m_bAskForDelete = true;
	}
	else
	{
		//reset empty
		memset(m_pBuf, 0, BUFLEN_CARTFREETEXT);
	}

	m_pBuf->ARTICLENO = m_nARTIKEL_NR;

	// alle Textzeilen für die Kombination PZN / Texttyp / Datum ermitteln
	m_Doc.GetAllTextLines();

	m_dlg.DataExchangeFromBuffer ();

	ShowTexttype (TRUE);

	m_BufOld = *m_pBuf;
}

/*----------------------------------------------------------------------------*/
BOOL CArtFreeTextView::ShowArtikel( BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	if (m_nARTIKEL_NR == 0)
	{
		m_csArtikelName.Empty();
		ShowSelectedInfo();
		return true;
	}

	iStat = m_RD_ZARTIKEL.IPlausi( m_nARTIKEL_NR, Name, &Errmld);

	if ( iStat == 0)
	{
		// weil im Feld Name schon ein Zeilenumbruch drin ist, den wir hier nicht brauchen können
		int i = Name.Find("\n", 0);

		if (i > 0)
			Name = Name.Left( i );

		m_csArtikelName.Format("%s", Name);
		ShowSelectedInfo();
	}

	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0;         
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextView::SucheArtikel( CEdit *pWnd )
{
	if (pWnd){}
	m_ArtBasisSelBox.SetPflegeProgNeuheit( NH_NEUHEIT_PHARMOS );

	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING338), &m_ArtBasisSelBox,
						HCD_SCROLLINFO );

	dlg.RestoreAuswahlIndex( m_nAuswahlIndex );
	dlg.RestoreAuswahlIndex2( m_nAuswahlIndex2 );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_ArtBasisSelBox.PrimeKeyOfSelectedRecord( &m_nARTIKEL_NR ) == 0 )
		{
			CString s;
			s.Format( "%ld", m_nARTIKEL_NR );
			m_ED_ARTNR.SetWindowText( s );
			m_ED_ARTCODE.SetFocus();
			ShowArtikel(true);
			SetKeyArticleCodeEditCtrl();
		}
	}

	m_nAuswahlIndex = dlg.GetAuswahlIndex( );
	m_nAuswahlIndex2 = dlg.GetAuswahlIndex2( );

	m_ArtBasisSelBox.CloseCursor();
}

// Texttyp
BOOL CArtFreeTextView::ShowTexttype( BOOL bShow, BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	iStat = m_RD_CTEXTTYPES.IPlausi( m_pBuf->TEXTTYPENO, Name, m_sMAX_LENGTH, m_sVALIDITYPERIOD, m_sMAXNUMBEROFLINES, &Errmld);

	if ( bShow )	// neu
	{
		GetDlgItem( IDC_ST_ARTFREETEXT_TEXTTYP_INFO )->SetWindowText( Name );

		// Editierbarkeit der Datumsfelder abhängig von der Einstellung im Texttyp 
		m_ED_DATEFROM.EnableWindow(m_sVALIDITYPERIOD);
		m_ED_DATETO.EnableWindow(m_sVALIDITYPERIOD);
	}

	if ( iStat > 1 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat <= 1;
}

void CArtFreeTextView::SucheTexttype( )
{
	CTextTypesSelCtrl m_SelBox;
	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING75), &m_SelBox,
						HCD_SCROLLINFO );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_SelBox.PrimeKeyOfSelectedRecord( &m_pBuf->TEXTTYPENO ) == 0 )
		{
			m_ED_TEXTTYPE.p_SetInput();
			m_ED_TEXTTYPE.SetFocus();
			ShowTexttype( TRUE );
		}
	}
	m_SelBox.CloseCursor();
}


/**---------------------------------------------------------------------------*/
void CArtFreeTextView::MakeDialog()
{
	m_Pos_FirstKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ED_ARTCODE );

	m_Pos_LastKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ED_ARTNR );

	m_Pos_FirstField = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ED_TEXTTYPE );

	m_Pos_DATVON = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ED_DATEFROM );
	m_dlg.InitDialog( m_ED_DATETO );

	m_Pos_TEXT = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ED_TEXT);

	m_nMaxFields = m_dlg.GetFieldNumber();	
}

void CArtFreeTextView::SetDialog( BOOL bDialog )
{   
 	m_dlg.SetDialog( bDialog );
}

BOOL CArtFreeTextView::EndValidate( int *ind )
{
	BOOL bOk = true;
	CString csErrmld;

	CString csText;
    char	FREETEXT_SAVE[255];
	short	sZeilen;

	// bei der Einstellung "mit Gültigkeitszeitraum" muss auch einer eingegeben werden
	if (m_sVALIDITYPERIOD == 1 && 
  	   (m_pBuf->DATEFROM == 0 ||
		m_pBuf->DATETO == 0))
	{
		bOk = false;
		csErrmld = CResString::ex().getStrTblText(IDS_STRING740);
		*ind = m_Pos_DATVON;
	}
	
	csText.Format("%s", m_pBuf->FREETEXT);
	csText.Trim();

	// Text darf nicht leer sein
	if (csText.GetLength() == 0)
	{
		bOk = false;
		csErrmld = CResString::ex().getStrTblText(IDS_STRING883);
		*ind = m_Pos_TEXT;
	}

	// Text darf nicht länger als das erlaubte Maximum sein
	if (csText.GetLength() > m_sMAX_LENGTH)
	{
		bOk = false;
		csErrmld.Format ("%s %d", CResString::ex().getStrTblText(IDS_STRING76), m_sMAX_LENGTH);
		*ind = m_Pos_TEXT;
	}

	// aktuellen Wert des Puffers sichern
	strcpy (FREETEXT_SAVE, m_pBuf->FREETEXT);

	// Anzahl Zeilen ermitteln
	sZeilen = m_Doc.DismantleTextIntoLines (m_pBuf->FREETEXT);

	// Puffers wiederherstellen
	strcpy (m_pBuf->FREETEXT, FREETEXT_SAVE);

	// Text darf nicht mehr Zeilen haben als das erlaubte Maximum 
	if (sZeilen > m_sMAXNUMBEROFLINES)
	{
		bOk = false;
		csErrmld.Format ("%s %d", CResString::ex().getStrTblText(IDS_STRING77), m_sMAXNUMBEROFLINES);
		*ind = m_Pos_TEXT;
	}

	if ( !bOk )
		AfxMessageBox( csErrmld );

	*ind = m_Pos_FirstField;
	return bOk;
}

/*----------------------------------------------------------------------------*/
bool CArtFreeTextView::IsNumber( CString cStr )
{
	CString str;
	str = cStr;
	str.TrimLeft();
	str.TrimRight();

	if ( str.IsEmpty() ) 
		return false;

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

/*----------------------------------------------------------------------------*/
class CV_ARTFREETEXT_Artikel : public ChValBase
{
public:
	CV_ARTFREETEXT_Artikel( CArtFreeTextView* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		if (bMeldung){}
		return ((CArtFreeTextView*)m_pWnd)->ShowArtikel( TRUE );
	}

	void PostProc( )
	{
		((CArtFreeTextView*)m_pWnd)->ShowArtikel( FALSE );
	}

	void NotifyProc( )
	{
		((CArtFreeTextView*)m_pWnd)->SucheArtikel( (CEdit*)m_pWnd1 );
	}
};

/*---------------------------------------------------------------------------*/
class CV_ARTFREETEXT_DateFrom : public ChValBase
{
public:
	CV_ARTFREETEXT_DateFrom( struct CARTFREETEXT* pBuf ) : ChValBase( pBuf ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		if (bMeldung){}
		BOOL bOk = TRUE;
/*		BOOL bOk = (( struct CARTFREETEXT*)m_pBuf)->DATEFROM != 0;
		
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_DATEFROM_EMPTY) ); */
		
		return bOk;
	}
};

/*---------------------------------------------------------------------------*/
class CV_ARTFREETEXT_DateTo : public ChValBase
{
public:
	CV_ARTFREETEXT_DateTo( struct CARTFREETEXT* pBuf ) : ChValBase( pBuf ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk = TRUE;

//		if ( (( struct CARTFREETEXT*)m_pBuf)->DATETO == 0 || 
	    if ( (( struct CARTFREETEXT*)m_pBuf)->DATETO < (( struct CARTFREETEXT*)m_pBuf)->DATEFROM)
			bOk = FALSE;
		
		if ( !bOk && bMeldung )
			MsgBoxOK( CResString::ex().getStrTblText(IDS_DATETO_ERR) );
		
		return bOk;
	}
};

class CV_ARTFREETEXT_Texttype : public ChValBase
{
public:
	CV_ARTFREETEXT_Texttype( CArtFreeTextView* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		BOOL bOk;
		bOk = ((CArtFreeTextView*)m_pWnd)->ShowTexttype( bMeldung, bMeldung );

		return bOk;
	}

	void PostProc( )
	{
		((CArtFreeTextView*)m_pWnd)->ShowTexttype( FALSE );
		((CArtFreeTextView*)m_pWnd)->CheckTexttypeChange( );
	}

	void NotifyProc( )
	{
		((CArtFreeTextView*)m_pWnd)->SucheTexttype( );
	}
};

/*----------------------------------------------------------------------------*/
void CArtFreeTextView::InitPflege()
{
	MakeDialog();
	CArtFreeTextView* pThisView = this;
	m_pBuf = m_Doc.GetBuffer();

	m_ED_ARTCODE.SetMask(ED_CHAR,
						 ED_UPPER,
						 m_ARTCODE_BASIS,
						 L_CARTICLECODES_ARTICLE_CODE,
						 new ChMaskChar,
						 new CV_ARTFREETEXT_Artikel( pThisView ) );
	m_ED_ARTCODE.SetDialog( TRUE );

	m_ED_ARTNR.SetMask	(ED_LONG,
							ED_NORMAL,
							&m_nARTIKEL_NR,
			                L_ARTIKEL_NR,
							new ChMaskNum,
							new CV_ARTFREETEXT_Artikel( pThisView ) );
	m_ED_ARTNR.SetDialog( TRUE );
	
	m_ED_TEXTTYPE.SetMask	(ED_LONG,
							ED_NORMAL,
							&m_pBuf->TEXTTYPENO,
							3,
							new ChMaskNum, 
							new CV_ARTFREETEXT_Texttype( pThisView ) );
	m_ED_TEXTTYPE.SetDialog( TRUE );

	m_ED_DATEFROM.SetMask(ED_LDATE,
							ED_NORMAL,
							&m_pBuf->DATEFROM,
							L_LDATUM,
							new ChMaskLDate,
							new CV_ARTFREETEXT_DateFrom(m_pBuf));
	m_ED_DATEFROM.SetDialog( TRUE );

	m_ED_DATETO.SetMask(ED_LDATE,
							ED_NORMAL,
							&m_pBuf->DATETO,
							L_LDATUM,
							new ChMaskLDate,
							new CV_ARTFREETEXT_DateTo(m_pBuf));
	m_ED_DATETO.SetDialog( TRUE );

	m_ED_TEXT.SetMask	   (ED_CHAR,
							ED_NORMAL,
							m_pBuf->FREETEXT,
							L_CARTFREETEXT_FREETEXT,
							new ChMaskUmlaut);
	EnableFields( FALSE );	
	//SetDialog();

	m_BOX.InitSuchBox();
	m_BOX.SetMultiLineSelection();
	
	m_nAuswahlIndex = 0;
	if (IsCountry("CH"))
		m_nAuswahlIndex2 = 2;
	else
		m_nAuswahlIndex2 = 0;
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextView::CloseSuche( )
{
	m_BOX.CloseCursor();
	return 0;
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextView::DoSuche() 
{
	CString SuchBegriff;
	CString SuchBegriff_temp;
	CString SuchBegriff1;

	m_bPrev = FALSE;
	m_bNext = FALSE;

	if (m_nARTIKEL_NR > 0)
	{
		m_ED_ARTNR.GetWindowText( SuchBegriff1 );
		SuchBegriff1.Trim();
		SuchBegriff_temp.Format( "1%s;", SuchBegriff1 );
		SuchBegriff += SuchBegriff_temp;
	}

	if ( m_BOX.StartSelect( SuchBegriff, WITH_SCROLL | WITH_HOLD ) )
	{
		m_bPrev = TRUE;
		m_bNext = TRUE;
		m_BOX.SetFocus();
	}
	else
		GotoFirstField();

	m_bShowSelect = true;

	return 1;
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextView::SucheSatz( )
{
	if ( m_nStatus == 0 )
	{
		SucheArtikel(&m_ED_ARTNR);
		return 0;
	}
	else
		return DoSuche();
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextView::NextSatz( )
{
	BOOL bOk;
	
	bOk = m_BOX.NextSelect();
	
	if ( !bOk ) 
		m_bNext = FALSE;
	
    if ( bOk )
		return 1;
	else
		return 0;
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextView::PrevSatz( )
{
	BOOL bOk;
	
	bOk = m_BOX.PrevSelect();
	
	if ( !bOk ) 
		m_bPrev = FALSE;
	
    if ( bOk )
		return 1;
	else
		return 0;
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextView::EnableFields( BOOL bEnab )
{
	m_dlg.EnableFields( m_Pos_FirstKey, m_Pos_LastKey, !bEnab );

	// Spezialität dieses Dialogs aufgrund der dynamischen Eingabemöglichkeit der Keyfelder
	if (bEnab)
	{
		if (!m_bKeyArtikel)
			m_ED_ARTCODE.EnableWindow(bEnab);
	} 
	
	m_ED_TEXTTYPE.EnableWindow( bEnab );
	m_ED_DATEFROM.EnableWindow( bEnab );
	m_ED_DATETO.EnableWindow( bEnab );
	m_ED_TEXT.EnableWindow( bEnab );

	m_BOX.EnableWindow( bEnab );
	m_BOX.ClearBox();

	m_bFieldsEnabled = bEnab;

	DisableSpecial();
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextView::DisableSpecial( )
{
	m_ED_ARTNR.EnableWindow(false);
	m_ED_ARTNR.ShowWindow(SW_HIDE);
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextView::DoBearbeiten( )
{
	CString cErrmld;

	if ( FALSE == SetKeyArticleNoEditCtrl( cErrmld ) ){
		return -1;
	}

	memset(m_pBuf, 0, BUFLEN_CARTFREETEXT);
	m_bShowSelect = false;
	m_bAskForDelete = false;
		
	m_ED_ARTNR.p_GetInput();

	if ( !m_ED_ARTNR.Validate( TRUE ) )
		return -1;

	int iKombi = 0;

	if ( m_nARTIKEL_NR > 0)
	{
        iKombi ++;
		
		if (!AreFieldsEnabled())
			m_bKeyArtikel = true;
	}
	else
		m_bKeyArtikel		= false;

	if (iKombi == 0)
	{
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING10279) );
		return -1;
	}

	m_nStatus = 1;
	
	EnableFields( TRUE );	
	m_dlg.SetValidation( m_Pos_FirstField, TRUE );

	( ( CEkZdpApp *) AfxGetApp() )->SetRecordSearch( TRUE, TRUE );

	return 	DoSuche() + 10; // suchen weiterhin möglich! 
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextView::BearbeiteSatz( )
{
	if ( !IsLastKeyFocus() )
	{
		((CDialogMultiLang*) this)->NextDlgCtrl( );
		return 0;
	}

	return DoBearbeiten();
}

void CArtFreeTextView::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

/**---------------------------------------------------------------------------*/
BOOL CArtFreeTextView::Validate( )
{
	int i = 0;
	BOOL bOk = TRUE;
	SetValidation( FALSE );
	i = m_Pos_FirstField;

	while ( i < m_nMaxFields && bOk )
	{
		bOk = m_dlg.Validate( i, TRUE );
		if ( bOk ) i++;
	}

	if ( bOk )
		bOk = EndValidate( &i );

	if ( !bOk )
	{
		m_dlg.SetFocus( i );
		return bOk;
	}
	
	SetValidation( TRUE );
	return TRUE;
}

BOOL CArtFreeTextView::IsLastKeyFocus( )
{
	return GetFocus() == GetDlgItem( IDC_LAST_KEY );
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextView::SpeichereSatz( )
{
	DataExchangeToBuffer( );

	if ( !Validate() ) 
		return -1;

	CString cErrmld;
/*	if ( FALSE == SetArticleNoEditCtrl( m_CodeConverterAufschlag, cErrmld ) ){
		return -1;
	} */

	// Focus schon hier auf die Box setzen, damit nicht erst nach dem Speichern beim Neuaufbau
	// der Box nochmal ein Validate eines Dialogfeldes aufgerufen wird (und ggfs. eine Fehler-
	// meldung kommt, weil die Werte schon nicht mehr gefüllt sind)
	m_BOX.SetFocus();

	if ( !m_ED_ARTNR.Validate( TRUE ) ) 
		return -1;

	if ( ! (( CEkZdpApp *)AfxGetApp())->YouWantToStoreRecord( ) )
		return -1;
	
	long lStatus;

	lStatus = 0;

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	
	m_pBuf->ARTICLENO		= m_nARTIKEL_NR;

	lStatus = m_Doc.StoreRecord( cErrmld );
	
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if ( lStatus != 0 )
	{
		MsgBoxOK( cErrmld );
		return -1;
	}
	else
	{
		// geänderten Key löschen!?
		if ( (m_BufOld.ARTICLENO != m_pBuf->ARTICLENO || 
			  m_BufOld.TEXTTYPENO !=  m_pBuf->TEXTTYPENO || 
			  m_BufOld.DATEFROM != m_pBuf->DATEFROM ||
			  m_BufOld.DATETO != m_pBuf->DATETO ) &&
			( m_bAskForDelete == true ) )
		{
			CString cMeld = _T( CResString::ex().getStrTblText(IDS_DEL_PREV_KEY) );

			// auf Wunsch von Fr. Samsinger MsgBox mit "nein" vorbelegen
			if ( MsgBoxYesNo( cMeld, MB_ICONQUESTION | MB_DEFBUTTON2 ) == IDYES ) 
//			if ( MsgBoxYesNo( cMeld ) == IDYES )
			{
				((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
				*m_pBuf = m_BufOld;

				lStatus = m_Doc.DeleteRecord( cErrmld );
				((CEkZdpApp*) AfxGetApp())->EndWaitAction();

				if ( lStatus != 0 )
				{
					MsgBoxOK( cErrmld );
					return -1;
				}
			}
		}
	}

	m_bChanged = TRUE;

	//THTH in listctrl auf gerade eingefügten Satz positioniern?
	m_bShowSelect = false;
	m_bAskForDelete = false;

	ResetKeys();

	return DoSuche() - 3; 
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextView::LoescheSatz( )
{
	int iCount = m_BOX.GetSelectedCount();
	if ( iCount <= 0 ) 
	{
		MsgBoxOK(CResString::ex().getStrTblText(IDS_STRING548));
		m_BOX.SetFocus();
		return 0;
	}

	m_ED_ARTNR.p_GetInput();

	if ( !m_ED_ARTNR.Validate( TRUE ) )
		return -1;

	if ( ! (( CEkZdpApp *)AfxGetApp())->YouWantToDeleteRecord( ) ) 
		return 0;

	int nStat;
	CString cErrmld;
	long lStatus;

	lStatus = 0;
	nStat = 0;

	while ( iCount > 0 )
	{
		if ( m_BOX.ItemChoise(FALSE) == FALSE ) // necessary to set m_LastSelectedPosition = -1
			break; 
		iCount--;
	}

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
		
	while ( nStat == 0 && lStatus == 0 )
	{
		nStat = m_BOX.PrimeKeyOfSelectedRecord( m_pBuf );
		if ( nStat == 0 )
		{
			m_pBuf->ARTICLENO		= m_nARTIKEL_NR;

			lStatus = m_Doc.DeleteRecord( cErrmld );
		}
	}

	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if ( lStatus != 0 )
	{
		while ( nStat == 0 )	// Select-Liste abarbeiten
			nStat = m_BOX.PrimeKeyOfSelectedRecord( m_pBuf );
		
		MsgBoxOK( cErrmld );
		return -1;
	}

	m_bChanged = TRUE;

	ResetKeys();

	return DoSuche() - 3;
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextView::UndoSatz( )
{
	if ( m_nStatus == 0 )
	{
		m_Doc.FreeBufferDesc( );
		CloseSuche();
		ResetVkn();
		return 0;
	}
	m_nStatus = 0;
	ResetKeys();
	EnableFields( FALSE );

	m_ED_ARTCODE.SetFocus();
	( ( CEkZdpApp *) AfxGetApp() )->SetRecordSearch( m_bNext, m_bPrev );
	return 1;
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextView::InitPflegeDocument( char* Anwender )
{
	m_Doc.InitPflegeDesc( Anwender );
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextView::ReleasePflegeDocument( )
{
}

/*----------------------------------------------------------------------------*/
BOOL CArtFreeTextView::SetKeyArticleNoEditCtrl( CString& cErrmld )
{
	m_ED_ARTCODE.p_GetInput();

	BOOL ret = TRUE;
	CString code;
	code.Format("%s", m_ARTCODE_BASIS);
	code.Trim();

	if ( code.IsEmpty() || 
	   ( IsNumber(code) && atol(code) == 0 ) ) // 0 sollte nicht als code interpretiert werden da es vor ernum auch nicht so war 
	{
		m_ED_ARTNR.SetWindowText("");
		m_ED_ARTNR.p_GetInput();

	} 
	else if ( FALSE == SetArticleNoEditCtrl( m_CodeConverterBasis, cErrmld ))
	{
		m_ED_ARTCODE.SetFocus();
		m_ED_ARTNR.SetWindowText("");
		ret = FALSE;
	}

	return ret;
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextView::SetKeyArticleCodeEditCtrl()
{
	m_CodeConverterBasis.setArticleCodeEditCtrl();
}

/*----------------------------------------------------------------------------*/
BOOL CArtFreeTextView::SetArticleNoEditCtrl( CArticleCodesConverter& codeConverter, CString& cErrmld )
{
	BOOL ret = TRUE;

	if ( 0 > codeConverter.setArticleNoEditCtrl( cErrmld ))
	{
		MsgBoxOK( cErrmld );
		ret = FALSE;
	}

	codeConverter.getArticleNoEditCtrl().p_GetInput();

	return ret;;
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextView::OnInitialUpdate() 
{
	CFormViewMultiLang::OnInitialUpdate();
	
	InitPflege();
	m_Doc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
	m_nStatus = 0;
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CFormViewMultiLang::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
		if ( pActivateView != pDeactiveView )
		{
			m_bChanged = FALSE;  // noch keine Aenderung

			m_BOX.ClearBox();
			m_nStatus = 0;

//			m_Doc.SetTagesdatum( ::Today() );
		}
	}
}

void CArtFreeTextView::SetValidation( BOOL bValid )
{
	if (bValid){}
	//m_dlg.SetValidation( bValid );
}

void CArtFreeTextView::ResetVkn( )
{
	m_RD_ZARTIKEL.Reset();
	m_RD_CTEXTTYPES.Reset();
}

void CArtFreeTextView::CheckTexttypeChange( )
{
	m_ED_TEXTTYPE.p_GetInput();

	// bei neuem Texttyp Textfeld löschen
	if (m_pBuf->TEXTTYPENO != m_BufOld.TEXTTYPENO)
	{
		m_pBuf->FREETEXT[0] = '\0';
		m_ED_TEXT.p_SetInput();
	}
	
	// Positionierung je nachdem, ob Datumsfelder eingegeben werden können oder nicht
	if (m_ED_DATEFROM.IsWindowEnabled())
		m_ED_DATEFROM.SetFocus();
	else
		m_ED_TEXT.SetFocus();
}

void CArtFreeTextView::ShowSelectedInfo() 
{
	CString Anzeige;

	Anzeige.Empty();

	if (!m_csArtikelName.IsEmpty())
		Anzeige.Append(m_csArtikelName);

	m_ST_SELECTION_INFO.SetWindowText( Anzeige ); 
}

BOOL CArtFreeTextView::AreFieldsEnabled()
{
	return m_bFieldsEnabled;
}

void CArtFreeTextView::ResetKeys()
{
	// Werte für Felder, die nicht ursprünglich selektiert wurden, wieder zurücksetzen
	if (!m_bKeyArtikel)
	{
		m_nARTIKEL_NR = 0;
		m_csArtikelName.Empty();
	}
}
 
void CArtFreeTextView::GotoFirstField()
{
	m_dlg.SetFocus( m_Pos_FirstField );
}

