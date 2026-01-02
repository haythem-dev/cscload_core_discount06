#if !defined(AFX_ACCOUNTFEEVIEW_H__09C691E1_DCB7_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_ACCOUNTFEEVIEW_H__09C691E1_DCB7_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtnrblveView.h : header file
//

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>

#include "hPflegeView.h"
#include "hSelectDialog.h"

#include <phxlib/RdCaccountitemstyle.h>
#include <phxlib/RdCaccountunit.h>
#include <phxlib/RdCaccounttype.h>
#include <phxlib/rdherstel.h>

#include "AccountFeeDoc.h"

#include <phxlib/CAccountUnitSelCtrl.h>
#include <phxlib/CAccountTypeSelCtrl.h>
#include <phxlib/CAccountItemStyleSelCtrl.h>
#include <phxlib/CAccountFeeSelCtrl.h>
#include <phxlib/herstelselctrl.h>

/////////////////////////////////////////////////////////////////////////////
// CArtnrblveView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CAccountFeeView : public ChPflegeView
{

	DECLARE_DYNCREATE(CAccountFeeView)

private:
	// members

	enum {  IDC_LAST_KEY = IDC_ED_ACCOUNTFEE_MANUFACTURER };

	ChDlg m_dlg;

	int m_Pos_FirstKey;
	int m_Pos_LastKey;
	int m_Pos_FirstField;

	UINT m_nStatus;
	int  m_nMaxFields;

	CAccountFeeDoc m_Doc;

	struct CACCOUNTFEE *m_pBufFee;

	CAccountFeeSelCtrl m_SelBox;

public:
	CAccountFeeView();         

	// Form Data
public:
	//{{AFX_DATA(CAccountFeeView)
	enum { IDD = IDD_ACCOUNTFEE };
	ChDlgEdit	m_TYPE;
	ChDlgEdit	m_UNIT;
	ChDlgEdit	m_ITEMSTYLE;
	ChDlgEdit   m_MANUFACTURER;
	ChDlgEdit	m_FEE;
	//}}AFX_DATA


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

	BOOL ShowType( BOOL bMeldung = FALSE );
	void SucheType();
	BOOL ShowUnit( BOOL bMeldung = FALSE );
	void SucheUnit();
	BOOL ShowItemStyle( BOOL bMeldung = FALSE );
	void SucheItemStyle();
	BOOL ShowManufacturer( BOOL bMeldung = FALSE );
	void SucheManufacturer();

private:
	void InitDlgDaten( );
	void MakeDialog( );
	void EnableFields( BOOL bEnable );
	void ShowFields( );
	void SetDialog( BOOL bDialog = TRUE );
	void DataExchangeToBuffer( );
	void SetValidation( BOOL bValid );
	BOOL Validate( );
	BOOL EndValidate( int *ind, BOOL bMeldung );
	BOOL ValidateKey();
	BOOL IsLastKeyFocus( );
	void GotoFirstKey();
	void GotoLastKey();
	void GotoKey();
	void GotoFirstField();
	void KeyGetInput();
	void KeySetInput();

	// Suchbox
	ChSelectDialog* NewSuchDialog();
	BOOL PrimeKeyOfSelectedRecord( );
	
	// nicht immer
	void DisableSpecial();
	void ShowSpecial();

	int m_nAuswahlIndex;
	int m_nAuswahlIndex2;

	CRdCaccountitemstyle	m_RD_ITEMSTYLE;
	CRdCaccountunit			m_RD_UNIT;
	CRdCaccounttype			m_RD_TYPE;
	CRdHerstel				m_RD_HERSTEL;

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArtnrblveView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

public:
	virtual ~CAccountFeeView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CArtnrblveView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTFEEVIEW_H__09C691E1_DCB7_11D2_92F8_0060973B18D8__INCLUDED_)
