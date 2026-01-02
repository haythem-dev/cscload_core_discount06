#if !defined(AFX_DRUCKVIEW_H__65FC8244_F119_11D3_92FB_0060973B18D8__INCLUDED_)
#define AFX_DRUCKVIEW_H__65FC8244_F119_11D3_92FB_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DruckView.h : header file
//

#include "hPflegeView.h"

/////////////////////////////////////////////////////////////////////////////
// CDruckView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CDruckView : public ChPflegeView
{
public:
	CDruckView(); 
	CDruckView( int nProgNr );     

	DECLARE_DYNCREATE(CDruckView)

// Form Data
public:
	//{{AFX_DATA(CDruckView)
	enum { IDD = IDD_DRUCK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

private:
	// ref to View
	CZdpUtilApp* theApp;
	ChPflegeView *m_pViewCalledFrom;

	// Drucken
	int  m_nPrintRow;
	int  m_nPrintPage;
	int  m_nPrintCharHeight;
	int	 m_nPrintCharWidth;
	int	 m_nX0;
	int  m_nY0;

	BOOL m_bOkFont; 
	CFont* m_pNewFont;
	CFont* m_pOldFont;

	int m_nMaxDruck;
	int	m_nMaxZeile;

// Attributes
public:

// Operations
public:
	// virtuals aus ChPflegeView
	int BearbeiteSatz();
	int UndoSatz( );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDruckView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CDruckView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CDruckView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRUCKVIEW_H__65FC8244_F119_11D3_92FB_0060973B18D8__INCLUDED_)
