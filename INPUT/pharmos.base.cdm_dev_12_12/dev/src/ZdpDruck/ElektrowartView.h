#pragma once

#include "hPflegeView.h"
#include "hSqlFd.h"
#include "hGridMsgHnd.h"

#include <eklibs/hamfcs/hDlgEdit.h>

// CElektrowartView-Formularansicht

class CElektrowartView : public ChPflegeView
{
	DECLARE_DYNCREATE(CElektrowartView)
public:
	CElektrowartView();           // Dynamische Erstellung verwendet geschützten Konstruktor


public:
	enum { IDD = IDD_ELEKTRO_AEND };
	ChDlgEdit	m_DATUMBIS;
	ChDlgEdit	m_DATUMVON;

private:
	void InitPflege();
	void InitVariables();
	bool ValidateSuchb();
	void FirstInitGrid();
	void ResizeControls( int cx, int cy );
	void FillGrid( void *pp, int index );
	void FillBox( int anz );
	void GetDelimiter( char *info, char *delim );
	long Lese_Protinfo( CString& cErrmld, CStringArray& cNem, CDWordArray& cNr);
	CString GetEARAlt( long nr );
	CString GetSelect(  );
	CString GetSelect_Client( );
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

	CStringArray m_cEAR;
	CDWordArray  m_cNr;

	// Drucken
	int  m_nSeite;
	int  m_nZeile;
	int  m_nSelectZeile;
	CString m_cName;

	//  Ueber UnixStdOut
	bool  IsViaStdout();
	int   ReadViaStdout();
	void  BufFromZeile( struct BUFF_ART *p, CString Zeile );
	void* BufFromGrid( int Row );
	void  FillString( char *str, CString cStr, int lng );
	void  FillZeileFromGrid( int Row , CString& cStr );

public:
	virtual void OnInitialUpdate();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);


protected:
	virtual ~CElektrowartView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnFileSpeichern();
	afx_msg void OnUpdateFileSpeichern(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};


