// ZdpDruckDoc.cpp : implementation of the CZdpDruckDoc class
//

#include "stdafx.h"
#include "ZdpDruck.h"

#include "ZdpDruckDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZdpDruckDoc

IMPLEMENT_DYNCREATE(CZdpDruckDoc, CDocument)

BEGIN_MESSAGE_MAP(CZdpDruckDoc, CDocument)
	//{{AFX_MSG_MAP(CZdpDruckDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZdpDruckDoc construction/destruction

CZdpDruckDoc::CZdpDruckDoc()
{
	// TODO: add one-time construction code here

}

CZdpDruckDoc::~CZdpDruckDoc()
{
}

BOOL CZdpDruckDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_sAr.SetSize( 3 );
	m_sAr[0] = "AaaaaaaaaaaaaaAAAAAAAAAaaaaaaaaaaa";
	m_sAr[1] = "bbbbbbbbbbbbbbbbbbbbbbbbaaa";	
	m_sAr[2] = "CCCCCCCCCCcccccccccccc";
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CZdpDruckDoc serialization

void CZdpDruckDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		m_sAr.Serialize( ar );
	}
	else
	{
		// TODO: add loading code here
		m_sAr.Serialize( ar );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CZdpDruckDoc diagnostics

#ifdef _DEBUG
void CZdpDruckDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CZdpDruckDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZdpDruckDoc commands

BOOL CZdpDruckDoc::SaveModified() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	if ( ( (CEk1App *)AfxGetApp())->IsSafeToExit( ) ) 
		return CDocument::SaveModified();
	else 
		return FALSE;
}

void CZdpDruckDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	m_sAr.RemoveAll();

	CDocument::DeleteContents();
}
