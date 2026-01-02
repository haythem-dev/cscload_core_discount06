// ZdpUtilDoc.cpp : Implementierung der Klasse CZdpUtilDoc
//

#include "stdafx.h"
#include "ZdpUtil.h"

#include "ZdpUtilDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilDoc

IMPLEMENT_DYNCREATE(CZdpUtilDoc, CDocument)

BEGIN_MESSAGE_MAP(CZdpUtilDoc, CDocument)
	//{{AFX_MSG_MAP(CZdpUtilDoc)
		// HINWEIS - Hier werden Mapping-Makros vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilDoc Konstruktion/Destruktion

CZdpUtilDoc::CZdpUtilDoc()
{
	// ZU ERLEDIGEN: Hier Code für One-Time-Konstruktion einfügen

}

CZdpUtilDoc::~CZdpUtilDoc()
{
}

BOOL CZdpUtilDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// ZU ERLEDIGEN: Hier Code zur Reinitialisierung einfügen
	// (SDI-Dokumente verwenden dieses Dokument)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CZdpUtilDoc Serialisierung

void CZdpUtilDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// ZU ERLEDIGEN: Hier Code zum Speichern einfügen
	}
	else
	{
		// ZU ERLEDIGEN: Hier Code zum Laden einfügen
	}
}

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilDoc Diagnose

#ifdef _DEBUG
void CZdpUtilDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CZdpUtilDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilDoc Befehle
