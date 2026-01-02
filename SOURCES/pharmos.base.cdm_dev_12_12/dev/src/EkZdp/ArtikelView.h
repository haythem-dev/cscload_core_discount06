#if !defined(AFX_ARTIKELVIEW_H__F042F0A2_7156_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_ARTIKELVIEW_H__F042F0A2_7156_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ArtikelView.h : header file
//

#include <voodoo_table_header/zartikel.h>
#include <voodoo_table_header/artve.h>

#include <eklibs/hamfcs/hDlg.h>
#include <eklibs/hamfcs/hDlgEdit.h>
#include <eklibs/hamfcs/hColStatic.h>

#include <phxlib/ZartikelSelCtrl.h>
#include "hPflegeView.h"
#include "hSelectDialog.h"
#include "hPflegePage.h"
#include "ArtikelDoc.h"

#include "ArtikelPage1.h"
#include "ArtikelPage2.h"
#include "ArtikelPage3.h"
#include "ArtikelPage4.h"
#include "ArtikelPage5A.h"
#include "ArtikelPage5CH.h"
#include "ArtikelPage5D.h"
#include "ArtikelPage5F.h"
#include "ArtikelPage5HR.h"
#include "ArtikelPage5BG.h"
#include "ArtikelPage5RS.h"
#include "PflegeSheet.h"
#include "ArticleCodesConverter.h"
#include "ArtikelPage6BG.h"

#include "hDatum.h"

#include <phxlib/LsTaxtab.h>
#include <eklibs/hamfcs/hMskChar.h>

#include "GDIUtil.h" // for printing cformview !

/////////////////////////////////////////////////////////////////////////////
// CArtikelView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CArtikelView : public ChPflegeView
{

	DECLARE_DYNCREATE(CArtikelView)

	friend class CArtikelPrices;
	friend class CRefundFrance;

private:
	// member

//	BOOL m_bChanged;

	enum {  IDC_LAST_KEY = IDC_ED_ARTIKEL_ARTIKEL_CODE };

	ChDlg m_dlg;

	int m_Pos_FirstKey;
	int m_Pos_LastKey;
	int m_nMaxFields;

	int m_Pos_Nextpzn;
	int m_Pos_Selifa;
	int m_Pos_Vorblifa;
	int m_Pos_Rueblifa;
	int m_Pos_Uebernifa;

	UINT m_nStatus;

	BOOL m_bVorblIfaEnabled;
	BOOL m_bRueblifaEnabled;
	BOOL m_bUebernifaEnabled;

	BOOL m_bVorblDatacareEnabled;
	BOOL m_bRueblDatacareEnabled;
	BOOL m_bUebernDatacareEnabled;

	char m_ARTCODE[L_CARTICLECODES_ARTICLE_CODE + 1];
	CArticleCodesConverter m_CodeConverter;

public:		
	CArtikelDoc m_Doc;	// wird in ArtikelPage1 benoetigt	
	bool m_isHealthInsuranceArticle;

private:
	ChDatum m_hDatum;

	CZartikelSelCtrl m_SelBox;
	int m_nAuswahlIndex;
	int m_nAuswahlIndex2;

	struct ZARTIKEL	*m_pBufZartikel;
	struct ARTVE	*m_pBufArtve;

	// Property Sheet + Pages
	CPflegeSheet* m_pSheet;

	CArtikelPage1  m_Page0;
	CArtikelPage2  m_Page1;
	CArtikelPage3  m_Page2;
	CArtikelPage4  m_Page3;
	CArtikelPage5A  m_Page4A;
	CArtikelPage5CH m_Page4CH;
	CArtikelPage5D  m_Page4D;
	CArtikelPage5F  m_Page4F;
	CArtikelPage5HR m_Page4HR;
	CArtikelPage5BG m_Page4BG;
	CArtikelPage5RS m_Page4RS;
	CArtikelPage6BG m_Page5BG;

	ChPflegePage* m_Page[6];

	BOOL m_bFieldsEnabled;
	BOOL m_bWasActive[6];

// protected:
public:	// !!!!! Trick
	CArtikelView();           // protected constructor used by dynamic creation

// Form Data
public:
	//{{AFX_DATA(CArtikelView)
	enum { IDD = IDD_ARTIKEL };
	ChColStatic	m_ST_INFO;
	ChDlgEdit	m_ARTIKEL_NR;
	ChDlgEdit	m_ARTIKEL_CODE;
	ChDlgButton	m_PB_NEXTPZN;
	ChDlgButton	m_PB_SELIFA;
	ChDlgButton	m_PB_VORBLIFA;
	ChDlgButton	m_PB_RUEBLIFA;
	ChDlgButton	m_PB_UEBERNIFA;
	//}}AFX_DATA

// Attributes
public:
	void SetHeaderInfo( );
	struct PFL_ARTIKEL* GetBuffer();
	struct PFL_ARTIKEL* GetOldBuffer();
	BOOL AreFieldsEnabled();
	void Set_WasActive();
	BOOL IsActivePage( CWnd *pWnd );
	int  GetActivePageIndex( );
	CWnd* GetPage( int nPage );
	BOOL WasPageActive( int nPage );
	BOOL WasThisPageActive( CWnd *pWnd );
	BOOL IsNeuanlage();
	void TranslatePages();

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
	//  ChPflegeView: virtual 
	virtual int  GotoPage( UINT nr );
	virtual void UpdatePflegeDocument();

	void NextDlgCtrl();   // wegen der pushbuttons

	void ShowPruefziffer( );

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
	long LeseSatz( CString& cErrmld );
	
	BOOL SetArticleNoEditCtrl( CString& cErrmld );
	void SetArticleCodeEditCtrl();
	void SetPreferredArticleCodeEditCtrl();
	
	long LeseDataSemp( CString& cErrmld );
	void CpyFromDsOArt();
	
	long LeseLogIndex( CString& cErrmld );
	void CpyFromLogIndex();	

	char * GetDarCH_D(CString csDar);
	char * GetDarCH_F(CString csDar);
	char * GetDfoZusatz_D(CString csDar);
	char * GetDfoZusatz_F(CString csDar);
	const char * GetUnitCH(CString& csUnit);
	void GetQtyCH(double dQty, char *temp);
	void GetConcCH(char *Conc, char *temp);

	void EnablePageFields( BOOL bEnab );	// wegen Blaettern  

	int  StelleAlleFragen();

	// Suchbox
	ChSelectDialog* NewSuchDialog();
	BOOL PrimeKeyOfSelectedRecord( );
	BOOL PrimeKeyOfNextRecord( );
	BOOL PrimeKeyOfPrevRecord( );

	// nicht immer
	void DisableSpecial();
	void ShowSpecial();
	void FillCmpIndikator( );

	// IFA
	struct ZIFAART *m_pIfaBuf;
	CArtikelIfa **m_pDlgIfa;
	long LeseSatzUeberIfa( long IfaNr, long SatzNr);
	long ReadSatzUeberIfa( long IfaNr, long SatzNr, CString& cErrmld );
	long LesePznAltSatzUeberIfa( long PhzAlt );
	void ReleaseIfa();
	void EnableFieldsIfa();
	void SetIfaInfo( long lStatus );

	CArtikelDatacare **m_pDlgDatacare;
	long LeseSatzUeberDatacare( long IfaNr, long SatzNr );
	long ReadSatzUeberDatacare( long IfaNr, long SatzNr, CString& cErrmld );
	long LesePznAltSatzUeberDatacare( long PhzAlt );
	void ReleaseDatacare();
	void EnableFieldsDatacare();
	void SetDatacareInfo( long lStatus );

	// Sekbez
//	struct ZARTSEKBEZ *m_pBufSekbez;

	// Taxtabelle
public:
	CLsTaxtab *m_pTaxTb;

public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CArtikelView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	
/////////////////////////////////////////////////////////////////////////////
//printing cformview
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

protected:
	GHandle m_dib;
	void grapImage( );
	afx_msg void OnFilePrint();

// Implementation
public: // Trick
	virtual ~CArtikelView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CArtikelView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPbArtikelNextpzn();
	afx_msg void OnPbArtikelSelifa();
	afx_msg void OnPbArtikelVorblifa();
	afx_msg void OnPbArtikelRueblifa();
	afx_msg void OnPbArtikelUebernifa();
	//}}AFX_MSG
	afx_msg LRESULT OnArtifaEnd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnArtdatacareEnd(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARTIKELVIEW_H__F042F0A2_7156_11D1_92F8_0060973B18D8__INCLUDED_)
