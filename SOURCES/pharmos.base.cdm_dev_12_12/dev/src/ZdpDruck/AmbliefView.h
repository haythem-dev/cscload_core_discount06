#if !defined(AFX_AMBLIEFVIEW_H__74E15E57_CD9E_49EA_ABEB_8AF83040EE9B__INCLUDED_)
#define AFX_AMBLIEFVIEW_H__74E15E57_CD9E_49EA_ABEB_8AF83040EE9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AmbliefView.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Formularansicht CAmbliefView 

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "hPflegeView.h"
#include "hSqlFd.h"
#include "hGridMsgHnd.h"

#include <eklibs/hamfcs/hDlgEdit.h>

class CAmbliefView : public ChPflegeView
{
public:
	CAmbliefView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CAmbliefView)

// Formulardaten
public:
	//{{AFX_DATA(CAmbliefView)
	enum { IDD = IDD_AMBLIEF };
		// HINWEIS: Der Klassen-Assistent fügt hier Datenelemente ein
	//}}AFX_DATA

// Attribute
public:

// Operationen
public:
	void InitPflege();
	void InitVariables();
	bool ValidateSuchb();
	void FirstInitGrid();
	void ResizeControls( int cx, int cy );
	void FillGrid( void *pp, int index );
	void FillBox( int anz );
	void GetDelimiter( char *info, char *delim );
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


//	CStringArray m_cNem;
//	CDWordArray  m_cNr;

	// Drucken
	int  m_nSeite;
	int  m_nZeile;
	int  m_nSelectZeile;
	CString m_cName;


	void  BufFromZeile( struct BUFF_AMBLIEF *p, CString Zeile );
	void* BufFromGrid( int Row );
	void  FillString( char *str, CString cStr, int lng );
	void  FillZeileFromGrid( int Row , CString& cStr );



// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CAmbliefView)
	protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CAmbliefView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CAmbliefView)
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

#endif // AFX_AMBLIEFVIEW_H__74E15E57_CD9E_49EA_ABEB_8AF83040EE9B__INCLUDED_
