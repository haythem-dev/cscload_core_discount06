#if !defined(AFX_ARTICLECATEGORYVIEW_H__ACA021C1_9B79_11D3_92FB_0060973B18D8__INCLUDED_)
#define AFX_ARTICLECATEGORYVIEW_H__ACA021C1_9B79_11D3_92FB_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArticleCategoryView.h : header file
//

#include <voodoo_table_header/carticlecategory.h>

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hDlgButton.h>

#include <phxlib/CarticlecategorySelCtrl.h>

#include "hPflegeView.h"
#include "hSelectDialog.h"

#include "ArticleCategoryDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CArticleCategoryView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CArticleCategoryView : public ChPflegeView
{

	DECLARE_DYNCREATE(CArticleCategoryView)

private:
	// members

//	BOOL m_bChanged;

	enum { IDC_LAST_KEY = IDC_ED_ARTICLECATEGORY_CATEGORYNO };

	ChDlg m_dlg;

	int m_Pos_FirstKey;
	int m_Pos_LastKey;
	int m_Pos_FirstField;

	UINT m_nStatus;
	int  m_nMaxFields;

	CArticleCategoryDoc m_Doc;	

	CCarticlecategorySelCtrl m_SelBox;

// protected:
public:	  
	CArticleCategoryView();           // protected constructor used by dynamic creation

// Form Data
public:
	//{{AFX_DATA(CArticleCategoryView)
	enum { IDD = IDD_ARTICLECATEGORY };
	ChDlgEdit   m_CATEGORY_NO;
	ChDlgEdit   m_NAME;
	ChDlgEdit   m_SQL;
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

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArticleCategoryView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
// protected:
public:  // Trick
	virtual ~CArticleCategoryView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CArticleCategoryView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTICLECATEGORYVIEW_H__ACA021C1_9B79_11D3_92FB_0060973B18D8__INCLUDED_)
