#if !defined(AFX_GENFESTBVIEW_H__F78D2B13_A726_4B3A_9218_8CFCDE9C8D7C__INCLUDED_)
#define AFX_GENFESTBVIEW_H__F78D2B13_A726_4B3A_9218_8CFCDE9C8D7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenfestbView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Formularansicht CGenfestbView 

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "hPflegeView.h"
#include <eklibs/hamfcs/hDlgEdit.h>

class CGenfestbView : public ChPflegeView
{
public:
	CGenfestbView();  
	
	DECLARE_DYNCREATE(CGenfestbView)

// Formulardaten
public:
	//{{AFX_DATA(CGenfestbView)
	enum { IDD = IDD_GENFESTB };
	ChDlgEdit	m_TRENN;
	ChDlgEdit	m_POSPZN;
	ChDlgEdit	m_POSFEST;
	CEdit	m_FILE;
	CEdit	m_VERZ;
	ChDlgEdit	m_LIEFDAT;
	ChDlgEdit	m_GUELDAT;
	CComboBox	m_cbSATZART;
	//}}AFX_DATA

// Attribute
private:
	void InitPflege();
	void InitVariables();

	void GenZeilenAufbau();
	int  ScanPznFestb( char *trenn, int *nPosPzn, int *nPosFestb );

// private Date
private:
	CZdpUtilApp* theApp;
	bool m_bComeBack;
	bool m_bDoResize;

	long m_nLiefDat;
	long m_nGuelDat;

	int  m_nPosPzn;
	int  m_nPosFest;

	char m_cTrenn[2];

	char* m_cIliFile;

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
	//{{AFX_VIRTUAL(CGenfestbView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CGenfestbView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CGenfestbView)
	afx_msg void OnGenfestbPbFile();
	afx_msg void OnGenfestbPbVerz();
	afx_msg void OnGenfestbPbDatauf();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_GENFESTBVIEW_H__F78D2B13_A726_4B3A_9218_8CFCDE9C8D7C__INCLUDED_
