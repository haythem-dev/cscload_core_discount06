#if !defined(AFX_ARTNAMEVIEW_H__FD029FC1_644E_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_ARTNAMEVIEW_H__FD029FC1_644E_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtnameView.h : header file
//

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>

#include "ArtnameDoc.h"
#include "hPflegeView.h"
#include "ArticleCodesConverter.h"

#include <voodoo_table_header/zartikel.h>
#include <phxlib/RdDform.h>
#include <phxlib/RdHerstel.h>

/////////////////////////////////////////////////////////////////////////////
// CArtnameView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CArtnameView : public ChPflegeView
{

	DECLARE_DYNCREATE(CArtnameView)

private:
	UINT m_nStatus;
	int  m_nMaxFields;

// protected:
public:
	CArtnameView();           // protected constructor used by dynamic creation


// Form Data
public:
	//{{AFX_DATA(CArtnameView)
	enum { IDD = IDD_ARTNAME };
	ChDlgEdit	m_cSEKBEZ_1;
	ChDlgEdit	m_cGESPERRT_1;
	ChDlgEdit	m_cEINHEIT_1;
	ChDlgEdit	m_cDFORM_1;
	ChDlgEdit	m_cARTIKEL_NR_1;
	ChDlgEdit	m_cARTIKEL_CODE;
	ChDlgEdit	m_cARTIKEL_NAME_1;
	ChDlgEdit	m_cEINHEIT_2;
	ChDlgEdit	m_cDFORM_2;
	ChDlgEdit	m_cARTIKEL_NAME_2;
	ChDlgEdit	m_cSUCHB;
	CStatic		m_ST_HERST_NR;
	//}}AFX_DATA

private:
	enum { ANZ_LINES = ANZ_ARTIKEL_2, ANZ_COLUMNS = 10 };
	enum { IDC_BASE = 3000 }; 
	enum { NR_EINHEIT = 0, NR_ARTIKEL_NAME = 1, NR_DFORM = 2,
		   NR_SEKBEZ  = 3, NR_ARTIKEL_NR = 4, NR_GESPERRT = 5,
		   NR_EINHEIT2 = 6, NR_ARTIKEL_NAME2 = 7, NR_DFORM2 = 8,
		   NR_ARTIKEL_CODE = 9 };

	ChDlgEdit*	m_cEdit [ANZ_LINES][ANZ_COLUMNS ];
	int m_nLines;
	int m_nColumns;
	int m_nActualLines;
	ChDlg m_dlg;
	void  MakeOneColum(  int nr, CEdit *pWndTop );
	void  CalcRect( CWnd *TopMuster, CRect *NewRect );
	BOOL  GenEditFeld( CEdit *pWnd, int idc, CEdit *pWndTop );
	void  GenFont( CWnd *pWnd );
	struct struArtName *m_pBuf[ ANZ_LINES ];
	struct struArtName *m_pBufOld[ ANZ_LINES ];

	CArtnameDoc m_Doc;	

	BOOL m_bPrev;
	BOOL m_bNext;

	CRdDform	m_RD_DFORM;
	CRdHerstel	m_RD_HERSTELLER;

	char m_ARTCODE [L_CARTICLECODES_ARTICLE_CODE + 1];

// Attributes
public:	
	virtual void InitPflege( );
	virtual void InitPflegeDocument( char* Anwender );
	virtual void ReleasePflegeDocument( );
	virtual int  SucheSatz( );
	virtual int  NextSatz( );
	virtual int  PrevSatz();
	virtual int  CloseSuche();
	virtual int  BearbeiteSatz();
	virtual int  SpeichereSatz();
	virtual int  LoescheSatz();
	virtual int  UndoSatz();


// Operations
public:
	BOOL ShowDform( ChDlgEdit *pEdit, BOOL bMeldung );
	void SucheDform( ChDlgEdit *pEdit );
	BOOL ShowHersteller( int iHersteller_nr, CString &cErrmld );

private:
	void InitDlgDaten( );
	void MakeDialog( );
	void ShowFields( );
	void EnableLines( int toLine );
	void DataExchangeToBuffer( );
	BOOL Validate( );
	void SetValidation( BOOL bValid );
	void SetMSStandard( BOOL bStandard );
	void SetArticleCodeEditCtrl( ChDlgEdit& noEdit, ChDlgEdit& codeEdit );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArtnameView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CArtnameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CArtnameView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTNAMEVIEW_H__FD029FC1_644E_11D2_92F8_0060973B18D8__INCLUDED_)
