// ZdpUtilView.cpp : Implementierung der Klasse CZdpUtilView
//

#include "stdafx.h"
#include "ZdpUtil.h"

#include "ZdpUtilDoc.h"
#include "ZdpUtilView.h"

#include <phxlib/drawphosix.h>
#include "RwProfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilView

IMPLEMENT_DYNCREATE(CZdpUtilView, CView)

BEGIN_MESSAGE_MAP(CZdpUtilView, CView)
	//{{AFX_MSG_MAP(CZdpUtilView)
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
//	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilView Konstruktion/Destruktion

CZdpUtilView::CZdpUtilView()
{
	// ZU ERLEDIGEN: Hier Code zur Konstruktion einfügen,
}

CZdpUtilView::~CZdpUtilView()
{
}

BOOL CZdpUtilView::PreCreateWindow(CREATESTRUCT& cs)
{
	// ZU ERLEDIGEN: Ändern Sie hier die Fensterklasse oder das Erscheinungsbild, indem Sie
	//  CREATESTRUCT cs modifizieren.

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilView Zeichnen

void CZdpUtilView::OnDraw(CDC* pDC)
{
	CZdpUtilDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(rect);
	CString Filiale;
	Filiale = _T("");
	CZdpUtilApp *theApp = ( CZdpUtilApp*) AfxGetApp();

	if ( theApp->IsConnected() )
	{
/*
		Filiale = _T("Connect: ");
		Filiale += theApp->GetServerName();
		Filiale.TrimRight();
		Filiale += _T("@");
		Filiale += theApp->GetDbaseName();
		Filiale.TrimRight();
		Filiale += _T("  Filiale: ");
		Filiale += theApp->GetCurrentBranchName( false );
		Filiale.TrimRight();
		Filiale += _T("  User: ");
		Filiale += theApp->GetUserName( );
		Filiale.TrimRight();
*/
		Filiale = _T("Connect: ");
/*
		Filiale += theApp->GetCurrentBranchName( false );
		Filiale.TrimRight();
		Filiale += _T("@");
*/
		Filiale += theApp->GetServerProgramName();
		Filiale += _T("://");

		Filiale += theApp->GetDbaseName();
		Filiale.TrimRight();
		Filiale += _T("@");
		Filiale += theApp->GetServerName();

		Filiale += _T("  User: ");
		Filiale += theApp->GetUserName( );
		Filiale.TrimRight();
	}
	else	// Anmeldeprozedur
	{
		if (theApp->IsUADM() == true)
		{
			Filiale = "";
		}
		else
		{
		CRwProfile prof;
		CString server, database;
		prof.ReadLastServerDbNames(server, database);
		Filiale = _T("Anmeldung an: ");
		Filiale += server;
		Filiale.TrimRight();
		Filiale += _T("@");
		Filiale += database;
	}
	}

	DrawPhosix( pDC, rect, "ZDPUtil", Filiale );
}

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilView Drucken

BOOL CZdpUtilView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Standardvorbereitung
	return DoPreparePrinting(pInfo);
}

void CZdpUtilView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Zusätzliche Initialisierung vor dem Drucken hier einfügen
}

void CZdpUtilView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// ZU ERLEDIGEN: Hier Bereinigungsarbeiten nach dem Drucken einfügen
}

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilView Diagnose

#ifdef _DEBUG
void CZdpUtilView::AssertValid() const
{
	CView::AssertValid();
}

void CZdpUtilView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CZdpUtilDoc* CZdpUtilView::GetDocument() // Die endgültige (nicht zur Fehlersuche kompilierte) Version ist Inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZdpUtilDoc)));
	return (CZdpUtilDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilView Nachrichten-Handler
