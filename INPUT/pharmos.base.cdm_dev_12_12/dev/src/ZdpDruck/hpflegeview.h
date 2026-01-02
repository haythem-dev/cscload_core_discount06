#if !defined(AFX_HPFLEGEVIEW_H__4C345F85_3EF7_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_HPFLEGEVIEW_H__4C345F85_3EF7_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// hPflegeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ChPflegeView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class ChPflegeView : public CFormView
{

// DECLARE_DYNCREATE(ChPflegeView)

protected:
    ChPflegeView(LPCTSTR lpszTemplateName);
	ChPflegeView(UINT nIDTemplate);

private:
	ChPflegeView();  // nicht benutzbar


// Data
protected:
	static CString m_cInterViewStorage;
	static int	   m_nViewNrCalledFrom;
	static CStringArray m_sArray;
	static ChPflegeView* m_pViewCalledFrom;

// Form Data
public:
	//{{AFX_DATA(ChPflegeView)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	void  GetMaxRectCorners( CRect& rectMax, CRect rectVgl);

public:
	BOOL DataChanged( );

// Operations
public:
	virtual void InitPflege( );
	virtual void InitPflegeDocument( char* Anwender );
	virtual void UpdatePflegeDocument();
	virtual void ReleasePflegeDocument( );
	virtual int  SucheSatz( );
	virtual int  NextSatz( );
	virtual int  PrevSatz();
	virtual int  CloseSuche();
	virtual int  BearbeiteSatz();
	virtual int  SpeichereSatz();
	virtual int  LoescheSatz();
	virtual int  UndoSatz();
	virtual int  CleanUp();
	virtual void CopySatz();
	virtual void CutSatz();
	virtual void PasteSatz();
	virtual void SetMSStandard( BOOL bStandard );
	virtual int  GotoPage( UINT nr );

	virtual int  StoreInterViewInfo( CString  cStorage );
	virtual int  LoadInterViewInfo ( CString& cStorage );

	virtual int  StoreViewCalledFrom( int CalledFrom );
	virtual int  LoadViewCalledFrom(  );

	virtual void SetViewCalledFrom( ChPflegeView* pView );
	virtual ChPflegeView* GetViewCalledFrom( );

	virtual void* GetObjectReference ( int nNr );

	virtual bool GetInfoFromCallingView( CString& cStr, int nAction );
	virtual bool GetInfoFromCallingView( long& nWert, int nAction );

	virtual CRect GetMaxViewRect( );

	virtual int ActionOnComboChange_0( );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ChPflegeView)
	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~ChPflegeView();
	BOOL m_bChanged;

	// Generated message map functions
	//{{AFX_MSG(ChPflegeView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HPFLEGEVIEW_H__4C345F85_3EF7_11D1_92F8_0060973B18D8__INCLUDED_)
