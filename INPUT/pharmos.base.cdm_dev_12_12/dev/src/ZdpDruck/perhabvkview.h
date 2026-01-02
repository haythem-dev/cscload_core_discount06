#if !defined(AFX_PERHABVKVIEW_H__4AA39B12_6F32_487D_A4FA_B2BE9873470C__INCLUDED_)
#define AFX_PERHABVKVIEW_H__4AA39B12_6F32_487D_A4FA_B2BE9873470C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PerhabvkView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Formularansicht CPerhabvkView 

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "hPflegeView.h"
#include "hSqlFd.h"
#include "hGridMsgHnd.h"

#include <eklibs/hamfcs/hDlgEdit.h>


class CPerhabvkView : public ChPflegeView
{
public:
	CPerhabvkView();  
	
	CPerhabvkView( int nProgNr );

	DECLARE_DYNCREATE(CPerhabvkView)

// Formulardaten
public:
	//{{AFX_DATA(CPerhabvkView)
	enum { IDD = IDD_PERHABVK };
	CButton	m_pbFilzu;
	CComboBox	m_cbBranch;
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
	CString GetSelect1( int anz );
	CString GetArtikelInSelect( int anz );
	long SecondFetch( int anz, CString cErrmld );

	void EnableOrder( BOOL mode );
	void GotoDruckView(  );

	long LoadRegiones( class CGetRegion* Reg );
	long LoadBranches( class CGetBranches* Fil, short region );

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
	CString GetUmsatzName();
	void AlterUmsatzHeader();
	void OutFiliale();

// Operationen
public:

// private Date
private:
	CEk1App* theApp;
	bool m_bComeBack;
	bool m_bDoResize;
	int  m_ProgMode;

	enum { GRID_ROWS = 20 };
	ChGridMsgHnd m_wndGrid;

	int	m_nNumberOfRows;
	ChSqlFd	m_hSelSql;
	CString	m_sSql;

	long m_nDatumVon;
	long m_nDatumBis;

	bool  m_bIstFiliale;
	bool  m_bGelesen;

	class CGetRegion   *m_pRegion;
	class CGetBranches *m_pBranch;

	// Drucken
	int  m_nSeite;
	int  m_nZeile;
	int  m_nSelectZeile;
	CString m_cName;
	CString m_cUmsatzName;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CPerhabvkView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CPerhabvkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CPerhabvkView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnFileSpeichern();
	afx_msg void OnUpdateFileSpeichern(CCmdUI* pCmdUI);
	afx_msg void OnSelchangePerhabvkBranch();
	afx_msg void OnPerhabvkFilzu();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_PERHABVKVIEW_H__4AA39B12_6F32_487D_A4FA_B2BE9873470C__INCLUDED_
