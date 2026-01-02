#if !defined(AFX_INKONSVIEW_H__FB4FB5F6_BB2D_4BF9_BAAE_E94582F0A9C5__INCLUDED_)
#define AFX_INKONSVIEW_H__FB4FB5F6_BB2D_4BF9_BAAE_E94582F0A9C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InkonsView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Formularansicht CInkonsView 

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "hPflegeView.h"
#include "hSqlFd.h"
#include "hGridMsgHnd.h"

#include <eklibs/hamfcs/hDlgEdit.h>

class CInkonsView : public ChPflegeView
{
public:
	CInkonsView();  

	DECLARE_DYNCREATE(CInkonsView)

// Formulardaten
public:
	//{{AFX_DATA(CInkonsView)
	enum { IDD = IDD_INKONS };
	ChDlgEdit	m_DATUMBIS;
	ChDlgEdit	m_DATUMVON;
	//}}AFX_DATA

// Attribute
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
	CString GetListStrich();
	void FillZeile( void *pp , CString& cStr );
	void GenHeader( CString& cStr, CString cText, int nSeite, int nLng );
//	void ScanName( CString Name );

	// virtuals aus ChPflegeView
	int BearbeiteSatz();
	int SucheSatz( );
	int NextSatz( );
	int PrevSatz( );
	int UndoSatz();
//	int LoescheSatz( );
	bool GetInfoFromCallingView( CString& cStr, int nAction );

// Operationen
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

	long m_nDatumVon;
	long m_nDatumBis;

	CStringArray m_cNem;
	CDWordArray  m_cPzn;

	// Drucken
	int  m_nSeite;
	int  m_nZeile;
	int  m_nSelectZeile;
	CString m_cName;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CInkonsView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CInkonsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CInkonsView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnFileSpeichern();
	afx_msg void OnUpdateFileSpeichern(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_INKONSVIEW_H__FB4FB5F6_BB2D_4BF9_BAAE_E94582F0A9C5__INCLUDED_
