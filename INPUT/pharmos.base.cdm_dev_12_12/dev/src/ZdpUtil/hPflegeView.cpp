// hPflegeView.cpp : implementation file
//

#include "stdafx.h"
#include "ZdpUtil.h"

#include "hPflegeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ChPflegeView

////////////////////////////////////////////////////////////////////
// CGenDynamicPage property page

// IMPLEMENT_DYNCREATE(ChPflegeView, CFormViewMultiLang)

/*ChPflegeView::ChPflegeView(LPCTSTR lpszTemplateName)
	: CFormViewMultiLang(lpszTemplateName)
{
	m_bChanged = FALSE;
}*/

ChPflegeView::ChPflegeView(UINT nIDTemplate)
	: CFormViewMultiLang(nIDTemplate)
{
	m_bChanged = FALSE;
}


ChPflegeView::~ChPflegeView()
{
}


BEGIN_MESSAGE_MAP(ChPflegeView, CFormViewMultiLang)
	//{{AFX_MSG_MAP(ChPflegeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////////////////////////////////////////

void ChPflegeView::CopySatz()
{
}

void ChPflegeView::CutSatz()
{
}

void ChPflegeView::PasteSatz()
{
}

void ChPflegeView::SetMSStandard( BOOL bStandard )
{
}

int  ChPflegeView::GotoPage( UINT nr )
{
	return 1;
}

BOOL ChPflegeView::DataChanged( )
{
	return m_bChanged;
}

void ChPflegeView::UpdatePflegeDocument()
{
}


// war vorher pure virtual

void ChPflegeView::InitPflege( )
{
}

void ChPflegeView::InitPflegeDocument( char* Anwender )
{
}

void ChPflegeView::ReleasePflegeDocument( )
{
}

int  ChPflegeView::SucheSatz( )
{
	return -1;
}

int  ChPflegeView::NextSatz( )
{
	return -1;
}

int  ChPflegeView::PrevSatz()
{
	return -1;
}

int  ChPflegeView::CloseSuche()
{
	return -1;
}

int  ChPflegeView::BearbeiteSatz()
{
	return -1;
}

int  ChPflegeView::SpeichereSatz()
{
	return -1;
}

int  ChPflegeView::LoescheSatz()
{
	return -1;
}

int  ChPflegeView::UndoSatz()
{
	return 0;  // -1;
}

int  ChPflegeView::CleanUp()
{
	return 0;
}

int ChPflegeView::ActionOnComboChange_0( )
{
	return -1;
}


/////////////////////////////////////////////////////
// InterView-Communication

// Initialisierung der statischen Variablen

CString ChPflegeView::m_cInterViewStorage = _T( "" );
CStringArray  ChPflegeView::m_sArray; // = NULL;
int			  ChPflegeView::m_nViewNrCalledFrom   = -1;
ChPflegeView* ChPflegeView::m_pViewCalledFrom = NULL;

int  ChPflegeView::StoreInterViewInfo( CString cStorage )
{
	m_cInterViewStorage = cStorage;
	return 0;
}

int  ChPflegeView::LoadInterViewInfo ( CString& cStorage )
{
	cStorage = m_cInterViewStorage;
	return cStorage.GetLength();
}


int  ChPflegeView::StoreViewCalledFrom( int CalledFrom )
{
	m_nViewNrCalledFrom = CalledFrom;
	return 0;
}

int  ChPflegeView::LoadViewCalledFrom(  )
{
	return m_nViewNrCalledFrom;
}


void* ChPflegeView::GetObjectReference ( int nNr )
{ 
	return NULL;
}


void ChPflegeView::SetViewCalledFrom( ChPflegeView* pView )
{
	m_pViewCalledFrom = pView;
}

ChPflegeView* ChPflegeView::GetViewCalledFrom( )
{
	return m_pViewCalledFrom;
}

bool ChPflegeView::GetInfoFromCallingView( CString& cStr, int nAction )
{
	cStr = "";
	return false;
}

bool ChPflegeView::GetInfoFromCallingView( long& nWert, int nAction )
{
	nWert = 0;
	return false;
}


// Rect

CRect ChPflegeView::GetMaxViewRect( )
{
	CRect rect( 32000, 32000, -32000, -32000 );
	return rect;
}


///////////////////////////////////////////////////////////
// Public HilfsFunktion 

void ChPflegeView::GetMaxRectCorners( CRect& rectMax, CRect rectVgl)
{

	if ( rectVgl.left   ==  32000 &&
		 rectVgl.top    ==  32000 &&
		 rectVgl.right  == -32000 &&
		 rectVgl.bottom == -32000     )  
		 return;

	if ( rectMax.left > rectVgl.left )
		rectMax.left = rectVgl.left;
	if ( rectMax.top > rectVgl.top )
		rectMax.top = rectVgl.top;
	if ( rectMax.right < rectVgl.right )
		rectMax.right = rectVgl.right;
	if ( rectMax.bottom < rectVgl.bottom )
		rectMax.bottom = rectVgl.bottom;
}
