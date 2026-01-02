#if !defined(AFX_NEWAUTIDEMVIEW_H__7B793145_F865_4A33_A52B_26B0F5B11E0A__INCLUDED_)
#define AFX_NEWAUTIDEMVIEW_H__7B793145_F865_4A33_A52B_26B0F5B11E0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewautidemView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Formularansicht CNewautidemView 

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "hPflegeView.h"
//#include "hSqlFd.h"
//#include "hGridMsgHnd.h"

#include <eklibs/hamfcs/hDlgEdit.h>

class CNewautidemView : public ChPflegeView
{
public:
	CNewautidemView();   
	
	DECLARE_DYNCREATE(CNewautidemView)

// Formulardaten
public:
	//{{AFX_DATA(CNewautidemView)
	enum { IDD = IDD_NEWAUTIDEM };
	CEdit	m_SPALTE;
	CComboBox	m_cbACTION;
	//}}AFX_DATA

// Attribute
private:
	void InitPflege();
	void InitVariables();
	bool ExtractPznFromCsv( CString &cErrmld, char *ColumnHeader, long *nAnz );
	bool GenAutidem( CString &cErrmld, long *nAnz );
	bool IsDigit( CString cS );
	bool TestAutidem( CString cFile_Name, CString &cErrmld, long *nAnz );

// private Date
private:
	CZdpUtilApp* theApp;
	bool m_bComeBack;
	bool m_bDoResize;

public:

	// virtuals aus ChPflegeView
	int BearbeiteSatz();
//	int SucheSatz( );
//	int NextSatz( );
//	int PrevSatz( );
	int UndoSatz();
	int SpeichereSatz( );
//	int LoescheSatz( );
	bool GetInfoFromCallingView( CString& cStr, int nAction );

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CNewautidemView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CNewautidemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CNewautidemView)
	afx_msg void OnSelchangeNewautidemCbAction();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_NEWAUTIDEMVIEW_H__7B793145_F865_4A33_A52B_26B0F5B11E0A__INCLUDED_
