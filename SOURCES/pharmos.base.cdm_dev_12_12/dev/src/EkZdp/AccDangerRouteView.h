#if !defined(AFX_ACCDANGERROUTEVIEW_H__60F359A1_A886_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ACCDANGERROUTEVIEW_H__60F359A1_A886_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AccDangerRouteView.h : header file
//

#include <voodoo_table_header/caccdangerroute.h>

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>

#include <phxlib/caccdangerrouteSelCtrl.h>

#include "hPflegeView.h"
#include "hSelectDialog.h"

#include "AccDangerRouteDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CAccDangerRouteView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CAccDangerRouteView : public ChPflegeView
{

	DECLARE_DYNCREATE(CAccDangerRouteView)

private:
	// members

//	BOOL m_bChanged;

	enum {  IDC_LAST_KEY = IDC_ED_ADR_VERPACKUNGSGRUPPE };

	ChDlg m_dlg;

	struct CACCDANGERROUTE*	m_pBuf;

	int m_Pos_FirstKey;
	int m_Pos_LastKey;
	int m_Pos_FirstField;

	UINT m_nStatus;
	int  m_nMaxFields;

	CAccDangerRouteDoc m_Doc;

	CCaccdangerrouteSelCtrl m_SelBox;

// protected:
public:	  // !!!!! Trick 
	CAccDangerRouteView();           // protected constructor used by dynamic creation

// Form Data
public:
	//{{AFX_DATA(CAccDangerRouteView)
	enum { IDD = IDD_ACCDANGERROUTE };
	ChDlgEdit		m_UNNR;
	ChDlgEdit		m_VPGRUPPE;
	ChDlgEdit		m_LQ_ADR2009;
	ChDlgEdit		m_ADR2011;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	//  ChPflegeView: pure virtual 
	virtual void InitPflege( );
	virtual void InitPflegeDocument( char* Anwender );
	virtual void ReleasePflegeDocument( );
	virtual int  SucheSatz( );
	virtual int  NextSatz( );
	virtual int  PrevSatz();
	virtual int  CloseSuche();
	virtual int  BearbeiteSatz();
	virtual int  SpeichereSatz();
	virtual int  LoescheSatz();
	virtual int  UndoSatz();
	virtual void CopySatz();
	virtual void CutSatz();
	virtual void PasteSatz();
	virtual void SetMSStandard( BOOL bStandard );

private:
	void InitDlgDaten( );
	void MakeDialog( );
	void EnableFields( BOOL bEnable );
	void ShowFields( );
	void SetDialog( BOOL bDialog = TRUE );
	void DataExchangeToBuffer( );
	void SetValidation( BOOL bValid );
	BOOL Validate( );
	BOOL ValidateKey( );
	BOOL EndValidate( int *ind );
	BOOL IsLastKeyFocus( );
	void GotoFirstKey();
	void GotoFirstField();
	void KeyGetInput();
	void KeySetInput();
	
	// Suchbox
	ChSelectDialog* NewSuchDialog();
	BOOL PrimeKeyOfSelectedRecord( );
	BOOL PrimeKeyOfNextRecord( );
	BOOL PrimeKeyOfPrevRecord( );

	// nicht immer
	void DisableSpecial();
	void ShowSpecial();

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccDangerRouteView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
// protected:
public:  // Trick
	virtual ~CAccDangerRouteView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAccDangerRouteView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCDANGERROUTEVIEW_H__60F359A1_A886_11D1_92F8_0060973B18D8__INCLUDED_)
