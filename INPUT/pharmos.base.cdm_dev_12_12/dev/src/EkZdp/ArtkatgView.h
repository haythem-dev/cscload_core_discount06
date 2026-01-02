#if !defined(AFX_ARTKATGVIEW_H__02196521_5FF5_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ARTKATGVIEW_H__02196521_5FF5_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtkatgView.h : header file
//

#include <voodoo_table_header/artkatg.h>

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>

#include <phxlib/ArtkatgSelCtrl.h>

#include "hPflegeView.h"
#include "hSelectDialog.h"

#include "ArtkatgDoc.h"
#include <phxlib/RdZrabgrp.h>

/////////////////////////////////////////////////////////////////////////////
// CArtkatgView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CArtkatgView : public ChPflegeView
{

	DECLARE_DYNCREATE(CArtkatgView)

private:
	// members

//	BOOL m_bChanged;

	enum {  IDC_LAST_KEY = IDC_ED_ARTKATG_WARENGRUPPE };

	ChDlg m_dlg;

	int m_Pos_FirstKey;
	int m_Pos_LastKey;
	int m_Pos_FirstField;
	int m_Pos_Laden;

	UINT m_nStatus;
	int  m_nMaxFields;

	CArtkatgDoc m_Doc;

	CArtkatgSelCtrl m_SelBox;

	CRdZrabgrp	m_RD_RABATTGRP;

	// protected:
public:	  // !!!!! Trick 
	CArtkatgView();           // protected constructor used by dynamic creation

// Form Data
public:
	//{{AFX_DATA(CArtkatgView)
	enum { IDD = IDD_ARTKATG };
	ChDlgButton	m_PB_LADEN;
	ChDlgEdit	m_WARENGRUPPE;
	ChDlgEdit	m_BEZEICHNUNG;
	ChDlgEdit	m_RABATTGRUPPE;
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
	BOOL CheckRabGr( char *csRabgrp);

private:
	void InitDlgDaten( );
	void MakeDialog( );
	void EnableFields( BOOL bEnable );
	void ShowFields( );
	void SetDialog( BOOL bDialog = TRUE );
	void DataExchangeToBuffer( );
	void SetValidation( BOOL bValid );
	BOOL Validate( );
	BOOL ValidateKey();
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
	//{{AFX_VIRTUAL(CArtkatgView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
//protected:
public:  // Trick
	virtual ~CArtkatgView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CArtkatgView)
	afx_msg void OnPbArtkatgLaden();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTKATGVIEW_H__02196521_5FF5_11D1_92F8_0060973B18D8__INCLUDED_)
