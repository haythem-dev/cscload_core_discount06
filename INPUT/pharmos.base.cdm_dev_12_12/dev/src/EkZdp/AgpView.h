#if !defined(AFX_CAGPVIEW_H__A46AA19E_8898_4D49_B4CA_EB600FA0CFDE_INCLUDED_)
#define AFX_CAGPVIEW_H__A46AA19E_8898_4D49_B4CA_EB600FA0CFDE_INCLUDED_
        
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <voodoo_table_header/cliart.h>
#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hColStatic.h>
#include "hPflegePage.h"
#include "AgpDoc.h"
#include "afxwin.h"
#include "afxcmn.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

// CAgpView form view, home screen for artikel AGP detail.
class CAgpView : public ChPflegeView
{
	DECLARE_DYNCREATE(CAgpView)

private:

	struct AGP_CONTROLS
	{
		CString agpPreis;
		CString gueltigAb;
		CStatic *agpCtl;
		CStatic *gueltigAbCtl;
	};

	enum { IDC_LAST_KEY = IDC_ED_AGP_PZN };	
	struct PFL_AGP*	m_pBuf;
	CAgpDoc m_Doc;	
	UINT m_nStatus;
	int	m_nMaxFields;
	int m_Pos_FirstKey;
	int m_Pos_LastKey;
	int m_Pos_FirstField;
	BOOL m_bNext;
	BOOL m_bPrev;
	int m_nAgpAnzl;
	struct CAGPART* m_AgpArtData;
	ChDlg m_dlg;
	CStatic m_agpPreis1;
	CStatic m_gueltigAb1;
	CStatic m_agpPreis2;
	CStatic m_gueltigAb2;
	CStatic m_agpPreis3;
	CStatic m_gueltigAb3;
	CStatic m_agpPreis4;
	CStatic m_gueltigAb4;
	CStatic m_agpPreis5;
	CStatic m_gueltigAb5;
	CStatic m_agpPreis6;
	CStatic m_gueltigAb6;
	CStatic m_agpPreis7;
	CStatic m_gueltigAb7;
	CStatic m_agpPreis8;
	CStatic m_gueltigAb8;
	CStatic m_agpPreis9;
	CStatic m_gueltigAb9;
	CStatic m_agpPreis10;
	CStatic m_gueltigAb10;
	CStatic m_agpDetails;
	enum { AGPART_ANZ = 10 };
	struct AGP_CONTROLS m_agpControls[AGPART_ANZ];
public:
	//  ChPflegeView: pure virtual 
	virtual void InitPflege();
	virtual void InitPflegeDocument(char* Anwender);
	virtual void ReleasePflegeDocument();
	virtual int  SucheSatz();
	virtual int  NextSatz();
	virtual int  PrevSatz();
	virtual int  CloseSuche();
	virtual int  BearbeiteSatz();
	virtual int  SpeichereSatz();
	virtual int  LoescheSatz();
	virtual int  UndoSatz();
	virtual void CopySatz();
	virtual void CutSatz();
	virtual void PasteSatz();
	virtual void SetMSStandard(BOOL bStandard);


private:
	void InitDlgDaten();
	void MakeDialog();
	void EnableFields(BOOL bEnable);
	void ShowFields();
	void SetDialog(BOOL bDialog = TRUE);
	void DataExchangeToBuffer();
	BOOL IsLastKeyFocus();
	void GotoFirstKey();
	void GotoFirstField();
	void KeyGetInput();
	void KeySetInput();
	void InitAGPControls();
	void ResetAGPControls();
	void FillAGPControls();
	void GetAgpImportDetail();
	void FillAgpImportDetails();
	// Agp suchen
	CArtikelAgp **m_pDlgAgp;
	void ReleaseAgp();
	BOOL PrimeKeyOfSelectedRecord();
	BOOL PrimeKeyOfNextRecord();
	BOOL PrimeKeyOfPrevRecord(); 

public:
	enum { IDD = IDD_AGP };
	CAgpView();           // protected constructor used by dynamic creation
	virtual ~CAgpView();	
	ChDlgEdit m_AgpPZN;   // PZN value from control		
	virtual void OnInitialUpdate();
	afx_msg LRESULT OnArtAgpEnd(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);	

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAGPVIEW_H__A46AA19E_8898_4D49_B4CA_EB600FA0CFDE_INCLUDED__)

