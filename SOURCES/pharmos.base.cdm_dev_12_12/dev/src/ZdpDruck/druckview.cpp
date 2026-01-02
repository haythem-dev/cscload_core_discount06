// DruckView.cpp : implementation file
//

#include "stdafx.h"
#include "zdpdruck.h"
#include "DruckView.h"

#include <phxlib/DrawPhosix.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDruckView

IMPLEMENT_DYNCREATE(CDruckView, CFormView)

CDruckView::CDruckView()
	: ChPflegeView(CDruckView::IDD)
{
	//{{AFX_DATA_INIT(CDruckView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	theApp = ((CEk1App*)AfxGetApp());
}

CDruckView::CDruckView( int nProgNr )
	: ChPflegeView(CDruckView::IDD)
{
	theApp = ((CEk1App*)AfxGetApp());
}

CDruckView::~CDruckView()
{
}

void CDruckView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDruckView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDruckView, CFormView)
	//{{AFX_MSG_MAP(CDruckView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDruckView diagnostics

#ifdef _DEBUG
void CDruckView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDruckView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CDruckView Implementation


/////////////////////////////////////////////////////////////////////////////
// Virtuals aus hPflegeView


int  CDruckView::BearbeiteSatz()
{
	theApp->SetDruckState( true );
	CView::OnFilePrint();
	// ruft UndoSatz() auf
//	GetParent()->SendMessage( IDD_DRUCK, 1 );		// geht so nicht
	return -1;
}

int  CDruckView::UndoSatz()
{
	theApp->SetDruckState( false );
	theApp->ChangeBackToView( m_pViewCalledFrom );
	return -1;		// -2 !!!!!!!!!!!!!!!!!!!!!!!
}


/////////////////////////////////////////////////////////////////////////////
// CDruckView message handlers

void CDruckView::OnInitialUpdate() 
{

	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
//	InitPflege();	

}


void CDruckView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class

	CFormView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if ( bActivate )
	{
		if ( pActivateView != pDeactiveView )
		{
			m_pViewCalledFrom = GetViewCalledFrom( );
			// ruft BearbeiteSatz() auf
			GetParent()->SendMessage( IDD_DRUCK, 0 );
		}	
	}
}




void CDruckView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( pDC->IsPrinting() )
		return;

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(rect);
	DrawPhosix( pDC, rect,
				"Druckvorgang beendet", "Bitte 'Esc' oder 'Pfeil hoch' drücken" );				
}


//////////////////////////////////////////////////
// Drucken

#define MAXLINES_PER_PRINTPAGE 68
#define SECURITY_LINES	   2
#define LEADING_COLUMNS	   5

//	1. Aufruf
//	wird aufgerufen, bevor der Dialog "Drucken" aufgerufen wird
BOOL CDruckView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box

	m_nMaxDruck = 1;
	m_nPrintRow = 0;

//	SetPrinter( pInfo, m_nCharsProZeile > 80 );
	
	pInfo->m_bPreview = FALSE;
	pInfo->m_bDirect  = FALSE;
//	nicht noetig, wenn ueber ID_FILE_PRINT,
//				  nur wenn ueber ID_FILE_PRINT_DIRECT

	pInfo->SetMinPage( 1 );

//	pInfo->SetMaxPage( m_nMaxDruck );	// Anzahl Seiten nicht bekannt

	if ( DoPreparePrinting( pInfo ) == FALSE )
		return FALSE;
	if ( pInfo->GetFromPage() > pInfo->GetToPage() )
		return FALSE;
//	if ( pInfo->GetToPage() > (UINT) m_nPages )
//		return FALSE;	

	pInfo->SetMinPage( 1 );			// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	pInfo->m_nCurPage  = 1;

	return TRUE;
}

//  2. Aufruf
//	wird aufgerufen, nachdem der Dialog "Drucken" beendet ist
void CDruckView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class

	if ( pDC->IsPrinting() )
	{

		int px_horz = pDC->GetDeviceCaps( HORZRES ); // dots in der Horizont
		int px_vert = pDC->GetDeviceCaps( VERTRES ); // dots in der Vertikalen

		m_nMaxZeile  = MAXLINES_PER_PRINTPAGE;
		m_nPrintPage = 0;
		m_nPrintCharHeight = px_vert/( m_nMaxZeile + SECURITY_LINES); 

		CString cStr;
		int ColumnsPerLine;
		m_pViewCalledFrom->GetInfoFromCallingView( cStr, -1 ); 
		ColumnsPerLine = atoi( cStr );
		m_nPrintCharWidth  = px_horz/( ColumnsPerLine + LEADING_COLUMNS); 

		m_pNewFont = new CFont;

/*
		m_bOkFont = 
			m_pNewFont->CreateFont( 
							m_nPrintCharHeight, 
							0, 0, 0, FW_LIGHT, 0, 0, 0, ANSI_CHARSET,
			  			    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
							DEFAULT_QUALITY,
//							DEFAULT_PITCH | FF_ROMAN, NULL);
//							FIXED_PITCH | FF_ROMAN, NULL);
							DEFAULT_PITCH | FF_MODERN, NULL);	
*/

		LOGFONT logFont;
		memset(&logFont, 0, sizeof(logFont));
		// 9/10 char , 1/10 Zwischenraum
		logFont.lfHeight = (9*m_nPrintCharHeight)/10; 
		logFont.lfWidth  = m_nPrintCharWidth;
		logFont.lfWeight = FW_NORMAL;   // 400
		logFont.lfPitchAndFamily = FIXED_PITCH | FF_MODERN;
//		lstrcpy(logFont.lfFaceName, "Courier");
		m_bOkFont = m_pNewFont->CreateFontIndirect(&logFont);
/*
		if ( !m_bOkFont )
		{
			m_pNewFont->Attach(::GetStockObject(OEM_FIXED_FONT ));
		}

*/
	}
//  The default Function does nothing
//	CFormView::OnBeginPrinting(pDC, pInfo);
}

// 3. Aufruf 
// wird vor OnPrint und mit diesem zusammen fuer jede Seite aufgerufen
// kann optional das Ende des Druckauftrages feststellen
void CDruckView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if ( pDC->IsPrinting() )
	{
	// AfxMessageBox( "OnPrepareDC: IsPrinting" );
		if ( !m_bOkFont )
		{
			pInfo->m_bContinuePrinting = FALSE; 
			return;
		}

		CString cStr;
		if ( !m_pViewCalledFrom->GetInfoFromCallingView( cStr, 0 ) ) 
		{
			pInfo->m_bContinuePrinting = FALSE; 
			return;
		}

		pDC->SetMapMode( MM_TEXT );

//		m_nPrintPage = pInfo->m_nCurPage; 
	}	

//	CFormView::OnPrepareDC(pDC, pInfo);
}

// 4. Aufruf 
// wird nach OnPrepareDc und mit diesem zusammen fuer jede Seite aufgerufen
void CDruckView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( !pDC->IsPrinting() ) return;

	bool bOk;
	int  zeile;

    CString cPrintZeile;

	if ( m_bOkFont )
		m_pOldFont = pDC->SelectObject(m_pNewFont);

	TEXTMETRIC tm;
	pDC->GetTextMetrics( &tm );
//	m_nPrintCharHeight = tm.tmHeight; // + tm.tmExternalLeading;
//	m_nPrintCharWidth  = tm.tmAveCharWidth;

	m_nX0 = LEADING_COLUMNS*m_nPrintCharWidth;	// Anfangs-Druckkoordinaten
	m_nY0 = 0;

	m_nPrintPage++;

	zeile = 0;

	do
	{
		bOk = m_pViewCalledFrom->GetInfoFromCallingView( cPrintZeile, 1 );
		if ( bOk )
			pDC->TextOut( m_nX0, m_nY0 + zeile*m_nPrintCharHeight, cPrintZeile );
	}	while ( ++zeile < m_nMaxZeile && bOk );

//	pDC->SelectObject(m_pOldFont)->DeleteObject();
	if ( m_bOkFont )
		pDC->SelectObject(m_pOldFont);

//  CFormView::OnPrint ruft OnDraw auf
//	wir hier aber nicht
//	CFormView::OnPrint(pDC, pInfo);
}

// 5. Aufruf
// Am Ende des Druckauftrages
void CDruckView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( pDC->IsPrinting() )
	{
		// Werkzeuge freigeben
		if ( m_bOkFont )
		{
//			pDC->SelectObject(m_pOldFont)->DeleteObject();
			delete m_pNewFont;
		}
	}
//  The default Function does nothing
//	CFormView::OnEndPrinting(pDC, pInfo);	
}




