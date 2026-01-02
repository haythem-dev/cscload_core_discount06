#pragma once

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "hPflegeView.h"
#include "hSqlFd.h"
#include "hGridMsgHnd.h"

#include <eklibs/hamfcs/hDlgEdit.h>


// CGaldatAHView-Formularansicht

class CGaldatAHView : public ChPflegeView
{
	DECLARE_DYNCREATE(CGaldatAHView)

protected:

	virtual ~CGaldatAHView();

public:
	CGaldatAHView();           // Dynamische Erstellung verwendet geschützten Konstruktor
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

	// virtuals aus ChPflegeView
	int BearbeiteSatz();
	int SucheSatz( );
	int NextSatz( );
	int PrevSatz( );
	int UndoSatz();
	bool GetInfoFromCallingView( CString& cStr, int nAction );

	enum { IDD = IDD_GALDAT_AH };
	ChDlgEdit	m_DATUMBIS;
	ChDlgEdit	m_DATUMVON;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnInitialUpdate();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnFileSpeichern();
	afx_msg void OnUpdateFileSpeichern(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()

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

	// Drucken
	int  m_nSeite;
	int  m_nZeile;
	int  m_nSelectZeile;
	CString m_cName;

	void  BufFromZeile( struct BUFF_GALDAT *p, CString Zeile );
	void* BufFromGrid( int Row );
	void  FillString( char *str, CString cStr, int lng );
	void  FillZeileFromGrid( int Row , CString& cStr );


};


