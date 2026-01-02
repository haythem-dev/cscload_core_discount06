/******************************************************************************/
/**                                                                           */
/**   Author : T. Hörath PRZ GmbH											  */
/**   Date   : 11.01.2006                                                     */
/**                                                                           */
/******************************************************************************/

#include "stdafx.h"
#include "ekzdp.h"
#include "ArticleCodesView.h"
#include "ServerDatum.h"
#include "FeldBreite.h"

#include <eklibs/hamfcs/hMskNum.h>
#include <eklibs/hamfcs/hMskChar.h>
#include <eklibs/hamfcs/hMskUmlaut.h>
#include <eklibs/hamfcs/hMskDate.h>
#include <eklibs/hamfcs/hMskDbl.h>
#include <eklibs/hamfcs/hMskDblPos.h>

#include <phxlib/PhxUtil.h>

#include <libscsvoodoo/libscsvoodoo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CArticleCodesView, CFormViewMultiLang)

/*----------------------------------------------------------------------------*/
CArticleCodesView::CArticleCodesView()
	: ChPflegeView(CArticleCodesView::IDD), m_PrefCodeType(0),
	  m_CodeConverter( m_ARTIKEL_CODE, m_ED_ARTNR, m_ArtSelBox )
{
}

/*----------------------------------------------------------------------------*/
CArticleCodesView::~CArticleCodesView()
{
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::DoDataExchange(CDataExchange* pDX)
{
	CFormViewMultiLang::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CArticleCodesView)
	DDX_Control(pDX, IDC_ST_ARTCODE_ART_INFO,			m_ST_ART_INFO);
	DDX_Control(pDX, IDC_ED_ARTCODE_ARTIKEL,			m_ED_ARTNR);
	DDX_Control(pDX, IDC_CB_ARTCODE_PZNNEW_ACTION,		m_CB_VERGABE_ART_PZN_NEU);
	DDX_Control(pDX, IDC_LC_ARTCODE_BOX,				m_BOX);
	DDX_Control(pDX, IDC_CK_ARTCODE_PREFERRED,			m_CK_PREFERRED);
	DDX_Control(pDX, IDC_ED_ARTCODE_PZNNEW,				m_ED_PZN_NEU);
	DDX_Control(pDX, IDC_CB_ARTCODE_CODETYPE,			m_CB_CODE_TYPE);
	DDX_Control(pDX, IDC_ED_ARTCODE_CODE,				m_ED_ARTICLE_CODE);
	DDX_Control(pDX, IDC_ED_ARTCODE_CODE_KEY,			m_ARTIKEL_CODE);
	//}}AFX_DATA_MAP
}

/*----------------------------------------------------------------------------*/
BEGIN_MESSAGE_MAP(CArticleCodesView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(CArticleCodesView)
	ON_CBN_SELCHANGE(IDC_CB_ARTCODE_PZNNEW_ACTION,	OnSelchangeCbVergabeArtPznNeu)
	ON_CBN_SELCHANGE(IDC_CB_ARTCODE_CODETYPE, OnSelchangeCbCodeType)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LC_ARTCODE_BOX,	OnItemchangedLcBox)
	//}}AFX_MSG_MAP
/////////////////////////////////////////////////////////////////////////////
//printing cformview
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
END_MESSAGE_MAP()

//-----------------------------------------------------------
BOOL CArticleCodesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(1);

	pInfo->m_pPD->m_pd.Flags &= ~PD_NOSELECTION;
	pInfo->m_pPD->m_pd.hInstance = AfxGetInstanceHandle();

	// default preparation
	return DoPreparePrinting(pInfo);
}

//-----------------------------------------------------------
void CArticleCodesView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
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
void CArticleCodesView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo /* = NULL */)
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
void CArticleCodesView::grapImage( )
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
void CArticleCodesView::OnFilePrint() 
{
	grapImage( );
	CFormViewMultiLang::OnFilePrint() ;
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::OnItemchangedLcBox(NMHDR* pNMHDR, LRESULT* pResult) 
{
	/* markierte Zeile in Edit-Felder übertragen */
	 if (pNMHDR){}
	*pResult = 0;

	int pos;
	if ((pos = m_BOX.GetNextItem(-1, LVNI_SELECTED)) >= 0 /* && m_bShowSelect*/ )
	{
		m_BOX.SelectedCode(m_pBuf);
	}
	else
	{
		//reset empty
		memset(m_pBuf, 0, BUFLEN_CARTICLECODES);
		
		if (m_nStatus == 1)
			m_pBuf->ARTICLENO = m_nARTIKEL_NR;
	}

	m_dlg.DataExchangeFromBuffer ();

	if (m_pBuf->PREFERRED_FLAG == 1)
		m_CK_PREFERRED.EnableWindow(false);
	else if (m_nStatus == 1)
		m_CK_PREFERRED.EnableWindow(true);

	m_BufOld = *m_pBuf;
}

/*----------------------------------------------------------------------------*/
BOOL CArticleCodesView::ShowArtikel( BOOL bMeldung )
{
	int iStat;
	CString Name;
	CString Errmld;

	if (m_nARTIKEL_NR == 0)
	{
		m_ST_ART_INFO.SetWindowText( "" );
		return true;
	}

	m_RD_ZARTIKEL.Reset();
	iStat = m_RD_ZARTIKEL.IPlausi( m_nARTIKEL_NR, Name, &Errmld);
	m_ST_ART_INFO.SetWindowText( Name );

	if ( iStat != 0 && bMeldung ) 
		MsgBoxOK( Errmld );

	return iStat == 0;         
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::SucheArtikel( CEdit *pWnd )
{
	if (pWnd){}
	m_ArtSelBox.SetPflegeProgNeuheit( NH_NEUHEIT_PHARMOS );

	ChSelectDialog dlg( CResString::ex().getStrTblText(IDS_STRING338), &m_ArtSelBox,
						HCD_SCROLLINFO );

	dlg.RestoreAuswahlIndex( m_nAuswahlIndex );
	dlg.RestoreAuswahlIndex2( m_nAuswahlIndex2 );

	if ( dlg.DoModal() == IDOK )
	{
		if ( m_ArtSelBox.PrimeKeyOfSelectedRecord( &m_nARTIKEL_NR ) == 0 )
		{
			CString s;
			s.Format( "%ld", m_nARTIKEL_NR );
			m_ED_ARTNR.SetWindowText( s );
			ShowArtikel(true);
			SetArticleCodeEditCtrl();
		}
	}

	m_nAuswahlIndex = dlg.GetAuswahlIndex( );
	m_nAuswahlIndex2 = dlg.GetAuswahlIndex2( );

	m_ArtSelBox.CloseCursor();
}

/**---------------------------------------------------------------------------*/
void CArticleCodesView::MakeDialog()
{
	m_Pos_FirstKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ARTIKEL_CODE  );
	m_Pos_LastKey = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ED_ARTNR );
	
	m_dlg.InitDialog( m_CB_VERGABE_ART_PZN_NEU );

	m_Pos_FirstField = m_dlg.GetFieldNumber();
	m_dlg.InitDialog( m_ED_ARTICLE_CODE );
	m_dlg.InitDialog( m_ED_PZN_NEU );
	
	m_dlg.InitDialog( m_CB_CODE_TYPE );
	m_dlg.InitDialog( m_CK_PREFERRED );
	
	m_nMaxFields = m_dlg.GetFieldNumber();	
}

/**---------------------------------------------------------------------------*/
void CArticleCodesView::SetDialog( BOOL bDialog )
{   
 	m_dlg.SetDialog( bDialog );
}

/**---------------------------------------------------------------------------*/
BOOL CArticleCodesView::EndValidate( int *ind )
{
	BOOL bOk = true;
	CString csErrmld;

	*ind = 0;

	if ( !bOk )
		AfxMessageBox( csErrmld );

	*ind = m_Pos_FirstField;
	return bOk;
}

/*----------------------------------------------------------------------------*/
class CV_ARTICLECODE_Artikel : public ChValBase
{
public:
	CV_ARTICLECODE_Artikel( CArticleCodesView* pView ) : ChValBase( pView ){};
	BOOL Validate( BOOL bMeldung )
	{
		if (bMeldung) {}
		return ((CArticleCodesView*)m_pWnd)->ShowArtikel( TRUE );
	}
	void PostProc( )
	{
		((CArticleCodesView*)m_pWnd)->ShowArtikel( FALSE );
	}
	void NotifyProc( )
	{
		((CArticleCodesView*)m_pWnd)->SucheArtikel( (CEdit*)m_pWnd1 );
	}
};

/*----------------------------------------------------------------------------*/
class CV_ARTICLECODE_PznNeu : public ChValBase
{
public:
	CV_ARTICLECODE_PznNeu( CArticleCodesView* pView ) : ChValBase( pView ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		if (((CArticleCodesView*)m_pWnd)->m_nARTIKEL_NR > 0)
			return true;

		// Berechnung PZN aus Code
		if (((CArticleCodesView*)m_pWnd)->m_nVERGABE_ART_PZN_NEU == 0)
		{
			((CArticleCodesView*)m_pWnd)->m_pBuf->ARTICLENO = 0;
			((CArticleCodesView*)m_pWnd)->m_ED_PZN_NEU.p_SetInput();
			
			/* nächste freie PZN aus Parameter ermitteln und setzen (nummerek !?) 
			in nummerek für jedes Land NEWPZN hinterlegen und Wert auf erste ungültige PZN setzen;
			bei Anlage neues Codes mit automatischer PZN- Ermittlung prüfen, ob diese PZN noch frei ist;
			wenn nein, dann in Schleife mit Start bei dieser Nr die nächste freie ungültige PZn suchen;
			mit Anlage des Codes dann auch die nächste freie PZN in Parameter stellen --> siehe SpeichereSatz
			(somit muss dann nicht bei jeder Neuanlage von vorne gesucht werden, sondern nur noch ab dem
			Punkt, wo das letzte Mal der Parameter umgesetzt wurde)
			*/

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
					((CArticleCodesView*)m_pWnd)->m_pBuf->ARTICLENO = lPzn;
					((CArticleCodesView*)m_pWnd)->m_ED_PZN_NEU.p_SetInput();
				}
			}
		}
		else if (((CArticleCodesView*)m_pWnd)->m_nVERGABE_ART_PZN_NEU == 1)
		{
			CString code;
			((CArticleCodesView*)m_pWnd)->m_ED_ARTICLE_CODE.GetWindowText(code);

			// PZN errechnen aus ArticleCode
			if (((CArticleCodesView*)m_pWnd)->m_pBuf->CODE_TYPE == 8 && code.GetLength() == 13) //GTIN
			{
				((CArticleCodesView*)m_pWnd)->m_pBuf->ARTICLENO = atoi(code.Right(7));
			}
			else if (((CArticleCodesView*)m_pWnd)->m_pBuf->CODE_TYPE == 9 && code.GetLength() == 13) //ACL
			{
				((CArticleCodesView*)m_pWnd)->m_pBuf->ARTICLENO = atoi(code.Mid(5,7));
			}
			else //PZN kann nicht errechnet werden!
			{
				((CArticleCodesView*)m_pWnd)->m_pBuf->ARTICLENO = 0;
			}
			
			((CArticleCodesView*)m_pWnd)->m_ED_PZN_NEU.p_SetInput();
			
		}
		// else m_nVERGABE_ART_PZN_NEU == 2     <-- manuelle Vergabe durch User
		
		int n_ziff = TestPruefZiffer7 ( ((CArticleCodesView*)m_pWnd)->m_pBuf->ARTICLENO );
		BOOL bOk = n_ziff != 1;

		if ( !bOk && bMeldung )
			MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_PZN_NOT_NULL)) );

		if (bOk)
		{
			CString Name;
			bOk = 0 != ((CArticleCodesView*)m_pWnd)->m_RD_ZARTIKEL.IPlausi( 
							((CArticleCodesView*)m_pWnd)->m_pBuf->ARTICLENO, Name);
			
			if ( !bOk && bMeldung ) 
			{
				MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_STRING1189)) );
			}
		}

		return bOk;
	}
};

/*----------------------------------------------------------------------------*/
class CV_ARTICLECODE_Code : public ChValBase
{
public:
	CV_ARTICLECODE_Code( CArticleCodesView* pView ) : ChValBase( pView ){};
	
	BOOL Validate( BOOL bMeldung )
	{
		short codeType = ((CArticleCodesView*)m_pWnd)->m_pBuf->CODE_TYPE;
		CString code;
		((CArticleCodesView*)m_pWnd)->m_ED_ARTICLE_CODE.GetWindowText(code);

		BOOL bOk = code.IsEmpty() == false;

		if (!bOk && bMeldung)
		{
			MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_STRING1190)) );
		}

		if (bOk)
		{
			// Code darf nur numerisch sein
			bOk = ((CArticleCodesView*)m_pWnd)->IsNumber(code);

			if (!bOk && 
				((codeType == 12 && code.GetAt(0) == 'ß' && ((CArticleCodesView*)m_pWnd)->IsNumber(code.Right(code.GetLength() - 1))) /*führendes "ß" OK wegen GoodsIn AT*/ || 
				  codeType == 19) /*Ersatz-Barcode in CH darf lt. Definition auch alphanumerisch sein*/ )
			{
				bOk = true;
			}
				
			if (bOk && code.GetAt(0) == '0')
			{
				// keine führenden Nullen
				bOk = false;
			}

			if (!bOk && bMeldung)
			{
				MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_STRING1238)) );
			}
		}
		
		if (bOk)
		{
			// maximale Länge zu einem CodeType prüfen
			bOk = code.GetLength() <= ((CArticleCodesView*)m_pWnd)->m_Doc.ReadCodeTypeLength(codeType);

			if (!bOk && bMeldung)
			{
				MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_STRING1191)) );
			}
		}

		if (bOk)
		{
			// Prüfziffer von GTIN, ACL, Tierarznei checken
			if ( codeType == 8 || codeType == 9 || codeType == 10  )
			{
				bool oddEven = true;
				int sum = 0;
				int counter = code.GetLength() - 2;
				char digit;

				while (counter >= 0)
				{
					digit = code.GetAt(counter);

					if (oddEven)
						sum = sum + (atoi(&digit) * 3);
					else
						sum = sum + atoi(&digit);
					
					oddEven = !oddEven;
					
					counter--;
				}

				digit = (int)code.GetAt(code.GetLength() - 1); // letzte Stelle ist Prüfziffer

				if ( (10 - (sum % 10)) == 10 )
					bOk = 0 == atoi(&digit); 
				else
					bOk = (10 - (sum % 10)) == atoi(&digit); 

				if (!bOk && bMeldung)
				{
					MsgBoxOK( _T(CResString::ex().getStrTblText(IDS_STRING1239)) );
				}			
			}
		}

		return bOk;
	}
};

/*----------------------------------------------------------------------------*/
bool CArticleCodesView::IsNumber( CString cStr )
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

/*----------------------------------------------------------------------------*/
void CArticleCodesView::InitPflege()
{
	MakeDialog();

	CArticleCodesView* pThisView = this;
	m_pBuf = m_Doc.GetBuffer();

	m_ARTIKEL_CODE.SetMask(ED_CHAR,
						 ED_UPPER,
						 m_ARTCODE,
						 L_CARTICLECODES_ARTICLE_CODE,
						 new ChMaskChar,
						 new CV_ARTICLECODE_Artikel( pThisView ));

	m_ED_ARTNR.SetMask	(ED_LONG,
							ED_NORMAL,
							&m_nARTIKEL_NR,
			                L_ARTIKEL_NR,
							new ChMaskNum,
							new CV_ARTICLECODE_Artikel( pThisView ) );
	m_ED_ARTNR.SetDialog( TRUE );

	m_ED_PZN_NEU.SetMask(ED_LONG,
							ED_NORMAL,
							&m_pBuf->ARTICLENO,
							L_ARTIKEL_NR,
							new ChMaskNum,
							new CV_ARTICLECODE_PznNeu( pThisView ));
	m_ED_PZN_NEU.SetDialog( TRUE );

	m_ED_ARTICLE_CODE.SetMask (ED_CHAR,
                           ED_UPPER,
						   m_pBuf->ARTICLE_CODE,
                           L_CARTICLECODES_ARTICLE_CODE,
                           new ChMaskUmlaut,
						   new CV_ARTICLECODE_Code( pThisView )
						   );
	m_ED_ARTICLE_CODE.SetDialog( TRUE );

	m_CK_PREFERRED.SetMask			( CB_YES, CB_NO, &m_pBuf->PREFERRED_FLAG );

	m_CB_CODE_TYPE.SetMask			( "08091011121316192022252627", 2, &m_pBuf->CODE_TYPE );
	
	m_CB_VERGABE_ART_PZN_NEU.SetMask( "012", &m_nVERGABE_ART_PZN_NEU ); 


	EnableFields( FALSE );	

	m_BOX.InitSuchBox();
	//m_BOX.SetMultiLineSelection();
	
	m_nAuswahlIndex = 0;
}

/*----------------------------------------------------------------------------*/
int CArticleCodesView::CloseSuche( )
{
	m_BOX.CloseCursor();
	return 0;
}

/*----------------------------------------------------------------------------*/
int CArticleCodesView::DoSuche()
{
	CString SuchBegriff="";

	m_bPrev = FALSE;
	m_bNext = FALSE;

	m_ED_ARTNR.GetWindowText( SuchBegriff );

	if ( m_BOX.StartSelect( SuchBegriff, WITH_SCROLL | WITH_HOLD ) )
	{
		m_bPrev = TRUE;
		m_bNext = TRUE;
		m_PrefCodeType = m_pBuf->CODE_TYPE;
	}
	else
	{
		m_CK_PREFERRED.EnableWindow(false);
		m_pBuf->PREFERRED_FLAG = 1;
		m_pBuf->ARTICLENO = m_nARTIKEL_NR;
		m_CK_PREFERRED.p_SetInput();
		m_ED_PZN_NEU.p_SetInput();
		m_CB_CODE_TYPE.SetCurSel(0);
	}

	OnSelchangeCbCodeType();
	
	m_bShowSelect = true;

	m_BOX.SetFocus();

	return 1;
}

/*----------------------------------------------------------------------------*/
int CArticleCodesView::SucheSatz( )
{
	if ( m_nStatus == 0 )
	{
		SucheArtikel( &m_ED_ARTNR );
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
int CArticleCodesView::NextSatz( )
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
int CArticleCodesView::PrevSatz( )
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
void CArticleCodesView::EnableFields( BOOL bEnab )
{
	m_dlg.EnableFields( m_Pos_FirstKey, m_Pos_LastKey, !bEnab );
	m_dlg.EnableFields( m_Pos_FirstField - 1, m_nMaxFields - 1, bEnab );

	m_BOX.EnableWindow( bEnab );
	m_BOX.ClearBox();

	m_ED_ARTNR.EnableWindow(false); // Eingabe nur noch in Artikel-Code-Feld
	m_ED_ARTNR.ShowWindow(SW_HIDE);
}

/*----------------------------------------------------------------------------*/
BOOL CArticleCodesView::SetArticleNoEditCtrl( CString& cErrmld )
{
	if ( 0 > m_CodeConverter.setArticleNoEditCtrl( cErrmld )){
		MsgBoxOK( cErrmld );
		m_ARTIKEL_CODE.SetFocus();
		return FALSE;
	}
	return TRUE;
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::SetArticleCodeEditCtrl()
{
	m_CodeConverter.setArticleCodeEditCtrl();
}

/*----------------------------------------------------------------------------*/
int CArticleCodesView::DoBearbeiten( )
{
	memset(m_pBuf, 0, BUFLEN_CARTICLECODES);
	m_bShowSelect = false;
	
	CString cErrmld;
	CString code;
	m_ARTIKEL_CODE.GetWindowText(code);

	if (code.IsEmpty())
		code = "0";

	if (atoi(code) == 0) // 0 ist hier gültige Eingabe !!!
		m_ED_ARTNR.SetWindowText(code);
	else
	{
		if ( FALSE == SetArticleNoEditCtrl( cErrmld ) ){
			return -1;
		}
	}
	
	KeyGetInput();
	m_ED_ARTNR.p_GetInput();

	if ( !m_ED_ARTNR.Validate( TRUE ) )
		return -1;

	m_nStatus = 1;
	
	EnableFields( TRUE );

	if (m_nARTIKEL_NR > 0)
		m_CB_VERGABE_ART_PZN_NEU.EnableWindow(false);

	OnSelchangeCbVergabeArtPznNeu();
	
	m_ED_ARTICLE_CODE.SetFocus();

	( ( CEkZdpApp *) AfxGetApp() )->SetRecordSearch( TRUE, TRUE );

 	return DoSuche() + 10; // suchen weiterhin möglich! 
}

void CArticleCodesView::KeyGetInput()
{
	m_dlg.DataExchangeToBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}

void CArticleCodesView::KeySetInput()
{
	m_dlg.DataExchangeFromBuffer( m_Pos_FirstKey, m_Pos_LastKey );
}

/*----------------------------------------------------------------------------*/
int CArticleCodesView::BearbeiteSatz( )
{
	if ( !IsLastKeyFocus() )
	{
		((CDialogMultiLang*) this)->NextDlgCtrl( );
		return 0;
	}

	return DoBearbeiten();
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::DataExchangeToBuffer( )
{
	m_dlg.DataExchangeToBuffer();
}

/**---------------------------------------------------------------------------*/
BOOL CArticleCodesView::Validate( )
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
//		m_dlg.ActivateField( i );
		m_dlg.SetFocus( i );
		return bOk;
	}

//	SetValidation( TRUE );
	return TRUE;
}

/*----------------------------------------------------------------------------*/
BOOL CArticleCodesView::IsLastKeyFocus( )
{
	return GetFocus() == GetDlgItem( IDC_LAST_KEY );
}

/*----------------------------------------------------------------------------*/
int CArticleCodesView::SpeichereSatz( )
{
	DataExchangeToBuffer( );

	if ( !Validate() ) 
		return -1;

	// Focus schon hier auf die Box setzen, damit nicht erst nach dem Speichern beim Neuaufbau
	// der Box nochmal ein Validate eines Dialogfeldes aufgerufen wird (und ggfs. eine Fehler-
	// meldung kommt, weil die Werte schon nicht mehr gefüllt sind)
	m_BOX.SetFocus();

	if ( ! (( CEkZdpApp *)AfxGetApp())->YouWantToStoreRecord( ) )
		return -1;

	bool resetPreviousPreferred = false;
	
	if (m_CK_PREFERRED.IsWindowEnabled() == TRUE && m_pBuf->PREFERRED_FLAG == 1)
	{
		if ( MsgBoxYesNo( CResString::ex().getStrTblText(IDS_STRING1188), MB_ICONQUESTION | MB_DEFBUTTON2 ) != IDYES ) 
			return -1;
		else
			resetPreviousPreferred = true;
	}
	
	CString cErrmld;
	long lStatus;
	lStatus = 0;

	double dCount;
	CString sql;
	sql.Format( "select count(*) from carticlecodes where article_code = '%s' "
				" and articleno != %ld and code_type in ( "
				" select code_type from ccodetypes where artnr_substitute = 1 )", 
				m_pBuf->ARTICLE_CODE,
				m_nARTIKEL_NR );

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = SqlRead(sql, &dCount, NULL);
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
 
	if ( lStatus != 0 || dCount != 0.0 )
	{	/* ------------------------------------------------------------------------------------
		-- wenn > 0, dann ist code schon als Ersatz für eine andere PZN hinterlegt (unabhängig vom type):
		---------------------------------------------------------------------------------------*/
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1198) );
		return -1;
	}

	sql.Format( "select count(*) from carticlecodes where article_code = '%s' "
				" and code_type = %d", 
				m_pBuf->ARTICLE_CODE,
				m_pBuf->CODE_TYPE );

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = SqlRead(sql, &dCount, NULL);
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();
 
	if ( (lStatus != 0 || dCount != 0.0) && strcmp(m_BufOld.ARTICLE_CODE, m_pBuf->ARTICLE_CODE) != 0)
	{	/* ------------------------------------------------------------------------------------
		-- wenn > 0, dann existiert der code schon als Ersatz für diesen codetype (unabhängig von PZN):
		---------------------------------------------------------------------------------------*/
		MsgBoxOK( CResString::ex().getStrTblText(IDS_STRING1199) );
		return -1;
	}

	long max = 0;
	sql.Format( "select max(serial_number), count(*) from carticlecodes where code_type = %d and articleno = %ld", 
				m_pBuf->CODE_TYPE, m_nARTIKEL_NR );

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	lStatus = SqlRead(sql, &max, &dCount, NULL);
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if (lStatus == 0 && max > 0)
	{
		/* ------------------------------------------------------------------------------------
		-- Satz für existierenden Codetyp ändern oder zusätzlichen Satz (nächste serial_number setzen!) angelegen?
		---------------------------------------------------------------------------------------*/
		if ((short)dCount < m_Doc.ReadCodeTypeMaxNumber(m_pBuf->CODE_TYPE) && 
			(m_BufOld.CODE_TYPE != m_pBuf->CODE_TYPE ||
					(strcmp(m_BufOld.ARTICLE_CODE, m_pBuf->ARTICLE_CODE) != 0 &&
					MsgBoxYesNo( CResString::ex().getStrTblText(IDS_STRING67), MB_ICONQUESTION | MB_DEFBUTTON1 ) != IDYES ) ))
		{
			m_pBuf->SERIAL_NUMBER = (short)max + 1;
			
			if (m_CK_PREFERRED.IsWindowEnabled() == FALSE) // nicht das preferred- flag in einen neuen Satz übernehmen!
				m_pBuf->PREFERRED_FLAG = 0;
		}
	}
	else
		m_pBuf->SERIAL_NUMBER = 1; // erster Code für diesen Codetyp
	

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	
	lStatus = m_Doc.StoreRecord( cErrmld, resetPreviousPreferred );
	
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if ( lStatus != 0 )
	{
		MsgBoxOK( cErrmld );
		return -1;
	}
	else
	{
		if (m_nVERGABE_ART_PZN_NEU == 0 && m_nARTIKEL_NR == 0) // nur bei Neuanlagen !
		{
			// Speicherung erfolgreich - nächste PZN in nummerek schreiben
			sql.Format("UPDATE nummerek SET nr = %ld WHERE nr_art = 'NEWPZN' ", m_pBuf->ARTICLENO + 1);
			lStatus = SqlExecuteImm( sql );
		}

		// geänderten Key löschen!?
		if (  m_BufOld.CODE_TYPE != m_pBuf->CODE_TYPE &&
			  strcmp(m_BufOld.ARTICLE_CODE, m_pBuf->ARTICLE_CODE) == 0 &&
			  m_BufOld.PREFERRED_FLAG != 1)
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

	m_bShowSelect = false;
		
	return DoSuche() - 3; 
}

/*----------------------------------------------------------------------------*/
int CArticleCodesView::LoescheSatz( )
{
	int iCount = m_BOX.GetSelectedCount();
	if ( iCount <= 0 ) 
	{
		MsgBoxOK(CResString::ex().getStrTblText(IDS_STRING548));
		m_BOX.SetFocus();
		return 0;
	}

	if (/*m_BOX.GetItemCount() > 1 && */m_pBuf->PREFERRED_FLAG == 1)
	{
		MsgBoxOK(CResString::ex().getStrTblText(IDS_STRING1187));
		m_BOX.SetFocus();
		return 0;
	}

	m_ED_ARTNR.p_GetInput();
	m_CB_CODE_TYPE.p_GetInput();
	
	if ( !m_ED_ARTNR.Validate( TRUE ) || 
		 !m_CB_CODE_TYPE.Validate( TRUE ) ) 
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
		
	nStat = m_BOX.PrimeKeyOfSelectedRecord( m_pBuf );
	if ( nStat == 0 )
	{
		m_pBuf->ARTICLENO		= m_nARTIKEL_NR;
		lStatus = m_Doc.DeleteRecord( cErrmld );
	}
	
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	return DoSuche() - 3;
}

/*----------------------------------------------------------------------------*/
int CArticleCodesView::UndoSatz( )
{
	if ( m_nStatus == 0 )
	{
		m_Doc.FreeBufferDesc( );
		CloseSuche();
		return 0;
	}
	else
	{
		m_pBuf->ARTICLENO = 0;
		m_ED_PZN_NEU.p_SetInput();
	}

	m_nStatus = 0;
	EnableFields( FALSE );

	m_ARTIKEL_CODE.SetFocus();
	m_ARTIKEL_CODE.SetSel(0, -1);
	( ( CEkZdpApp *) AfxGetApp() )->SetRecordSearch( m_bNext, m_bPrev );
	return 1;
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::InitPflegeDocument( char* Anwender )
{
	m_Doc.InitPflegeDesc( Anwender );
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::ReleasePflegeDocument( )
{
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::OnInitialUpdate() 
{
	CFormViewMultiLang::OnInitialUpdate();
	
	InitPflege();
	m_Doc.InitPflegeDesc( ((CEkZdpApp *)AfxGetApp())->GetRefToAnwender() );
	m_nStatus = 0;
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	CFormViewMultiLang::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
		if ( pActivateView != pDeactiveView )
		{
			FillComboBox();

			m_bChanged = FALSE;  // noch keine Aenderung

			m_BOX.ClearBox();
			m_nStatus = 0;

			m_Doc.SetTagesdatum( ::Today() );
		}
	}
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::OnSelchangeCbVergabeArtPznNeu() 
{
	m_nVERGABE_ART_PZN_NEU = static_cast<short>(m_CB_VERGABE_ART_PZN_NEU.GetCurSel());

	if (m_CB_VERGABE_ART_PZN_NEU.IsWindowEnabled() && m_nVERGABE_ART_PZN_NEU == 2 && m_nARTIKEL_NR == 0)
		// manuelle Vergabe der PZN bei Artikel- Neuanlage
		m_ED_PZN_NEU.EnableWindow(true);
	else
		m_ED_PZN_NEU.EnableWindow(false);
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::OnSelchangeCbCodeType() 
{
	m_CB_CODE_TYPE.p_GetInput();
	
	if (m_BOX.GetItemCount() >= 1 && 
		m_pBuf->CODE_TYPE != m_PrefCodeType)
	{
		m_CK_PREFERRED.SetCheck(0);
		m_CK_PREFERRED.EnableWindow(true);		
	}
	else
	{
		m_CK_PREFERRED.SetCheck(1);
		m_CK_PREFERRED.EnableWindow(false);		
	}
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::FillComboBox()
{
	m_CB_VERGABE_ART_PZN_NEU.ResetContent();
	m_CB_CODE_TYPE.ResetContent();
	
	m_CB_VERGABE_ART_PZN_NEU.AddString(CResString::ex().getStrTblText(IDS_STRING1179));
	m_CB_VERGABE_ART_PZN_NEU.AddString(CResString::ex().getStrTblText(IDS_STRING1180));
	m_CB_VERGABE_ART_PZN_NEU.AddString(CResString::ex().getStrTblText(IDS_STRING1181));

	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1182));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1183));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1184));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1185));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1304));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1231));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1186));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING70));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING112));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1493));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1611));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_STRING1614));
	m_CB_CODE_TYPE.AddString(CResString::ex().getStrTblText(IDS_OCP_CODE_TYPE));
	
	m_CB_VERGABE_ART_PZN_NEU.SetCurSel( 0 );
	m_CB_CODE_TYPE.SetCurSel( 0 );
}

/*----------------------------------------------------------------------------*/
void CArticleCodesView::SetValidation( BOOL bValid )
{
	m_dlg.SetValidation( bValid );
}
