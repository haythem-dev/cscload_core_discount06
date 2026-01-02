// ZdpDruckView.cpp : implementation of the CZdpDruckView class
//

#include "stdafx.h"
#include "ZdpDruck.h"

#include "ZdpDruckDoc.h"
#include "ZdpDruckView.h"

#include <phxlib/DrawPhosix.h>

#include "RwProfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZdpDruckView

IMPLEMENT_DYNCREATE(CZdpDruckView, CView)

BEGIN_MESSAGE_MAP(CZdpDruckView, CView)
	//{{AFX_MSG_MAP(CZdpDruckView)
	//}}AFX_MSG_MAP
	// Standard printing commands
//	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
//	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZdpDruckView construction/destruction

CZdpDruckView::CZdpDruckView()
{
	// TODO: add construction code here
}

CZdpDruckView::~CZdpDruckView()
{
}

BOOL CZdpDruckView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CZdpDruckView drawing

void CZdpDruckView::OnDraw(CDC* pDC)
{
	CZdpDruckDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(rect);
	CString Filiale;
	Filiale = _T("");
	CEk1App *theApp = ( CEk1App *) AfxGetApp();

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
		Filiale += theApp->GetServerProgramName();
		Filiale += _T("://");

//		Filiale += theApp->GetCurrentBranchName( false );
//		Filiale.TrimRight();
//		Filiale += _T("@");
		Filiale += theApp->GetDbaseName();
		Filiale.TrimRight();
		Filiale += _T("@");
		Filiale += theApp->GetServerName();

		Filiale += _T("  User: ");
		Filiale += theApp->GetUserName( );
		Filiale.TrimRight();
	}
	else	
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
	DrawPhosix( pDC, rect, "ZDPDruck", Filiale );
}

/////////////////////////////////////////////////////////////////////////////
// CZdpDruckView printing

BOOL CZdpDruckView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	AfxMessageBox("ZdpDruck: On Prepare Printing" );
	return DoPreparePrinting(pInfo);
}

void CZdpDruckView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
	AfxMessageBox("ZdpDruck: On Begin Printing" );
}

void CZdpDruckView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CZdpDruckView diagnostics

#ifdef _DEBUG
void CZdpDruckView::AssertValid() const
{
	CView::AssertValid();
}

void CZdpDruckView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CZdpDruckDoc* CZdpDruckView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZdpDruckDoc)));
	return (CZdpDruckDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZdpDruckView message handlers
