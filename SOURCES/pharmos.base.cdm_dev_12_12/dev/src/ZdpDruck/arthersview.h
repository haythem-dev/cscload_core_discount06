#if !defined(AFX_ARTHERSVIEW_H__65DE20C3_EF98_11D3_92FB_0060973B18D8__INCLUDED_)
#define AFX_ARTHERSVIEW_H__65DE20C3_EF98_11D3_92FB_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArthersView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CArthersView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "hPflegeView.h"
#include "hSqlFd.h"
//#include "hDynSql.h"
//#include "hDynBuf.h"
#include "hGridMsgHnd.h"

#include <eklibs/hamfcs/hDlgEdit.h>
#include <phxlib/RdHerstel.h>

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/carticlecodes.h>
#include <voodoo_table_header/artnrbl.h>
#include "stdafx.h"


class CArthersView : public ChPflegeView
{
public:
	CArthersView(); 
	
	DECLARE_DYNCREATE(CArthersView)

// Form Data
public:
	//{{AFX_DATA(CArthersView)
	enum { IDD = IDD_ARTHERS };
	CButton	m_rdNr;
	CButton	m_rdName;
	ChDlgEdit	m_Suchb;
	//}}AFX_DATA

// Attributes
private:
	void InitPflege();
	void InitVariables();
	bool ValidateSuchb();
	void FirstInitGrid();
	void ResizeControls( int cx, int cy );
	void FillGrid( void *pp, int index );
	void FillBox( int anz );
	CString GetSelect(  );
	void EnableOrder( BOOL mode );
	void GotoDruckView(  );

	bool IsPrintZeile();
	void* GetPrintZeile();
	CString GetListHeader();
	void FillZeile( void *pp , CString& cStr );
	void GenHeader( CString& cStr, CString cText, int nSeite, int nLng );
	void ScanName( CString Name );

	// virtuals aus ChPflegeView
	int BearbeiteSatz();
	int SucheSatz( );
	int NextSatz( );
	int PrevSatz( );
	int UndoSatz();
//	int LoescheSatz( );
	bool GetInfoFromCallingView( CString& cStr, int nAction );

public:
	void SucheHersteller( );
	BOOL ShowHersteller( BOOL bShow, BOOL bMeldung = FALSE );

// Operations
public:

// private Date
private:
	CEk1App* theApp;
	bool m_bComeBack;
	bool m_bDoResize;

	enum { GRID_ROWS = 20 };
	ChGridMsgHnd m_wndGrid;

	int	m_nNumberOfRows;
	ChSqlFd	m_hSelSql;
	CString	m_sSql;

	CRdHerstel	m_RD_HERSTELLER;

	long m_nSuchNr;

	// Drucken
	int  m_nSeite;
	int  m_nZeile;
	int  m_nSelectZeile;
	CString m_cName;

//  SelectStructur
	#define PROJ_ARTHERS \
			" lpad(trim(C.ARTICLE_CODE), %d, 0)," \
			"V.VERPACKEINHEIT1,V.VERPACKEINHEIT2," \
			"V.VERPACKEINHEIT3,V.VERPACKEINHEIT4," \
			"Z.ARTIKEL_NAME,Z.EINHEIT"
		

	struct  BUFF_ARTHERS {
		    char ARTICLE_CODE[MAX_LENGTH_ARTICLE_NO + 1];
			long VERPACKEINHEIT1;
		    long VERPACKEINHEIT2;
			long VERPACKEINHEIT3;
			long VERPACKEINHEIT4;
		    char ARTIKEL_NAME[L_ZARTIKEL_ARTIKEL_NAME + 1];
			char EINHEIT[L_ZARTIKEL_EINHEIT + 1];
	};



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArthersView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CArthersView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CArthersView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetfocusArthersSuchb();
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnFileSpeichern();
	afx_msg void OnUpdateFileSpeichern(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTHERSVIEW_H__65DE20C3_EF98_11D3_92FB_0060973B18D8__INCLUDED_)
