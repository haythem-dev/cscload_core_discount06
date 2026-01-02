// ZdpUtilView.h : Schnittstelle der Klasse CZdpUtilView
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZDPUTILVIEW_H__202956E7_D09E_4D9C_A011_93F05640DF09__INCLUDED_)
#define AFX_ZDPUTILVIEW_H__202956E7_D09E_4D9C_A011_93F05640DF09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CZdpUtilView : public CView
{
protected: // Nur aus Serialisierung erzeugen
	CZdpUtilView();
	DECLARE_DYNCREATE(CZdpUtilView)

// Attribute
public:
	CZdpUtilDoc* GetDocument();

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CZdpUtilView)
	public:
	virtual void OnDraw(CDC* pDC);  // überladen zum Zeichnen dieser Ansicht
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementierung
public:
	virtual ~CZdpUtilView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generierte Message-Map-Funktionen
protected:
	//{{AFX_MSG(CZdpUtilView)
		// HINWEIS - An dieser Stelle werden Member-Funktionen vom Klassen-Assistenten eingefügt und entfernt.
		//    Innerhalb dieser generierten Quelltextabschnitte NICHTS VERÄNDERN!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Testversion in ZdpUtilView.cpp
inline CZdpUtilDoc* CZdpUtilView::GetDocument()
   { return (CZdpUtilDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ZDPUTILVIEW_H__202956E7_D09E_4D9C_A011_93F05640DF09__INCLUDED_)
