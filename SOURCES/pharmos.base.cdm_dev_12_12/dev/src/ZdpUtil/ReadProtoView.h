#if !defined(__READPROTOVIEW_H__)
#define __READPROTOVIEW_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReadProtoView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Formularansicht CReadProtoView 

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "hPflegeView.h"
//#include <eklibs/hamfcs/hDlgEdit.h>

class CReadProtoView : public ChPflegeView
{
public:
	CReadProtoView();  
	
	DECLARE_DYNCREATE(CReadProtoView)

// Formulardaten
public:
	//{{AFX_DATA(CReadProtoView)
	enum { IDD = IDD_READPROTO };
	CEdit		m_CSV_Filename;
	CComboBox	m_cbProtoFiles;
	//}}AFX_DATA

// Attribute
private:
	//void InitPflege();
	void InitVariables();

	void ExtractDateiName(char *name, CString& cName);
	long GetFileNames(CString cPfad, CStringArray& DateiNamen, CString& errmld);

// private Date
private:
	CZdpUtilApp* theApp;
	bool m_bComeBack;
	bool m_bDoResize;

public:

	// virtuals aus ChPflegeView
//	int BearbeiteSatz();
//	int SucheSatz( );
//	int NextSatz( );
//	int PrevSatz( );
//	int UndoSatz();
//  int SpeichereSatz( );
//	int LoescheSatz( );
//	bool GetInfoFromCallingView( CString& cStr, int nAction );

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CReadProtoView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CReadProtoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CReadProtoView)
	afx_msg void OnReadProtoSearchCsv();
	afx_msg void OnReadProtoSearchUnx();
	afx_msg void OnReadProtoTransferToWin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // __READPROTOVIEW_H__
