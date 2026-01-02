#pragma once

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "hPflegeView.h"
#include "hSqlFd.h"
#include "hGridMsgHnd.h"

#include <eklibs/hamfcs/hDlgEdit.h>
#include "afxwin.h"

// CDatacarePreisaend-Formularansicht

class CDatacarePreisaend : public ChPflegeView
{
	DECLARE_DYNCREATE(CDatacarePreisaend)

public:
	CDatacarePreisaend();           // Dynamische Erstellung verwendet geschützten Konstruktor
protected:
	virtual ~CDatacarePreisaend();

public:
	enum { IDD = IDD_DC_PREISAEND };


// Attribute
public:


	struct BUFF_PREISAEND
	{
	char ARTIKEL_NAME[31];
	char EINHEIT[10];
	double AEP;
	double DC_AEP;
	double DIFFWERT;
	double DIFFPROZ;
	long ARTIKEL_NR;
	double ABVERKAUF;
	};

	

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
	CString GetSelect( bool bSortAsc = true );
	CString GetFelderSelectNachfrage();
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
	struct BUFF_PREISAEND m_arArtikel[60];
	enum { GRID_ROWS = 60 };
	ChGridMsgHnd m_wndGrid;

	int	m_nNumberOfRows;
	ChSqlFd	m_hSelSql;
	CString	m_sSql;
	long m_nVZ;
	CString m_csFelderNachfrage;

	// Drucken
	int  m_nSeite;
	int  m_nZeile;
	int  m_nSelectZeile;
	CString m_cName;


	void  BufFromZeile( struct BUFF_PREISAEND *p, CString Zeile );
	void* BufFromGrid( int Row );
	void  FillString( char *str, CString cStr, int lng );
	void  FillZeileFromGrid( int Row , CString& cStr );
	void  InsertIntoArray(struct BUFF_PREISAEND *p);
	long  KalWeek (long datum, long *jahr);
	int	  GetIndexKleinsterAbverkauf(int iUntereSchranke,int iObereSchranke);
	void  SortArray(int iUntereSchranke,int iObereSchranke);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFilePrint();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnFileSpeichern();
	afx_msg void OnUpdateFileSpeichern(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
public:
	ChDlgEdit m_VZ;
};


