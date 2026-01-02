// ZdpDruckView.h : interface of the CZdpDruckView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZDPDRUCKVIEW_H__6E2D8B6F_AEC3_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_ZDPDRUCKVIEW_H__6E2D8B6F_AEC3_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CZdpDruckView : public CView
{
protected: // create from serialization only
	CZdpDruckView();
	DECLARE_DYNCREATE(CZdpDruckView)

// Attributes
public:
	CZdpDruckDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZdpDruckView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CZdpDruckView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CZdpDruckView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ZdpDruckView.cpp
inline CZdpDruckDoc* CZdpDruckView::GetDocument()
   { return (CZdpDruckDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDPDRUCKVIEW_H__6E2D8B6F_AEC3_11D2_92F8_0060973B18D8__INCLUDED_)
