// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__03D6985D_6DB1_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_MAINFRM_H__03D6985D_6DB1_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <eklibs/hamfcs/hComboToolBar.h>
#include <eklibs/hamfcs/hStatusBar.h>

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
//	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public: 
	CMainFrame();

// Attributes
public:

// Operations
public:
	class ChStatusBar * GetStatusBar();
	void LoadToolBarState( CString CUser );
	void CustomizeToolBar( );
	void LoadFilialen( CGetBranches* Fil );

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
//	CStatusBar  m_wndStatusBar;
//	CToolBar    m_wndToolBar;
	ChStatusBar    m_wndStatusBar;
	ChComboToolBar m_wndToolBar;
	CComboBox*     m_TbCbFiliale;
	CComboBox*     m_TbCbSonst;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCusttoolbar();
	afx_msg void OnRecordSearch();
	afx_msg void OnUpdateRecordSearch(CCmdUI* pCmdUI);
	afx_msg void OnRecordNext();
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnRecordPrev();
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	afx_msg void OnRecordDelete();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnRecordUndo();
	afx_msg void OnUpdateRecordUndo(CCmdUI* pCmdUI);
	afx_msg void OnRecordNew();
	afx_msg void OnUpdateRecordNew(CCmdUI* pCmdUI);
	afx_msg void OnRecordCopy();
	afx_msg void OnUpdateRecordCopy(CCmdUI* pCmdUI);
	afx_msg void OnRecordCut();
	afx_msg void OnUpdateRecordCut(CCmdUI* pCmdUI);
	afx_msg void OnRecordPaste();
	afx_msg void OnUpdateRecordPaste(CCmdUI* pCmdUI);
	afx_msg void OnRecordSave();
	afx_msg void OnUpdateRecordSave(CCmdUI* pCmdUI);
	afx_msg void OnViewMsStandard();
	afx_msg void OnUpdateViewMsStandard(CCmdUI* pCmdUI);
	afx_msg void OnViewAutoFrage();
	afx_msg void OnUpdateViewAutoFrage(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewRechte(CCmdUI* pCmdUI);
	afx_msg void OnViewRechte();
	afx_msg void OnArtblie();
	afx_msg void OnUpdateArtblie(CCmdUI* pCmdUI);
	afx_msg void OnArthers();
	afx_msg void OnUpdateArthers(CCmdUI* pCmdUI);
	afx_msg void OnNemwart();
	afx_msg void OnUpdateNemwart(CCmdUI* pCmdUI);
	afx_msg void OnNemwlie();
	afx_msg void OnUpdateNemwlie(CCmdUI* pCmdUI);
	afx_msg void OnArt7proz();
	afx_msg void OnUpdateArt7proz(CCmdUI* pCmdUI);
	afx_msg void OnArtsperr();
	afx_msg void OnUpdateArtsperr(CCmdUI* pCmdUI);
	afx_msg void OnNonemlie();
	afx_msg void OnUpdateNonemlie(CCmdUI* pCmdUI);
	afx_msg void OnInkons();
	afx_msg void OnUpdateInkons(CCmdUI* pCmdUI);
	afx_msg void OnPerhoeh();
	afx_msg void OnUpdatePerhoeh(CCmdUI* pCmdUI);
	afx_msg void OnPerhabvk();
	afx_msg void OnUpdatePerhabvk(CCmdUI* pCmdUI);
	afx_msg void OnPsenkabvk();
	afx_msg void OnUpdatePsenkabvk(CCmdUI* pCmdUI);
	afx_msg void OnGhaen();
	afx_msg void OnUpdateGhaen(CCmdUI* pCmdUI);
	afx_msg void OnAmblief();
	afx_msg void OnUpdateAmblief(CCmdUI* pCmdUI);
	afx_msg void OnDcPreisaend();
	afx_msg void OnUpdateDcPreisaend(CCmdUI* pCmdUI);
	afx_msg void OnGaldatNeu();
	afx_msg void OnUpdateGaldatNeu(CCmdUI* pCmdUI);
	afx_msg void OnGaldatAH();
	afx_msg void OnUpdateGaldatAH(CCmdUI* pCmdUI);
	afx_msg void OnElektrowart();
	afx_msg void OnUpdateElektrowart(CCmdUI *pCmdUI);
	afx_msg void OnElektroNeuaufn();
	afx_msg void OnUpdateElektroNeuaufn(CCmdUI *pCmdUI);
	afx_msg void OnHerstellerNachHerstellerCode();
	afx_msg void OnUpdateHerstellerNachHerstellerCode(CCmdUI* pCmdUI);
	//}}AFX_MSG

	// Handler for combobox messages
	afx_msg void OnComboChange_0();
	afx_msg void OnComboChange_1();

	afx_msg LRESULT OnDruckMessage( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()

public:
	void ChangeToView( int nViewNr );
	void ChangeBackToView( int nViewNr );
	void ChangeBackToView( CView *pView );
	class ChPflegeView*	GetViewViaNr( int nViewNr );

public:
	void SetConnectinfoToView();
	void DefineViews( );
	void CreateFormViews();
	void SetDefaultView();
	bool IsDefaultView();
	bool IsSafeToExit( );
	bool IsAutoFrage();
	void SetMenuOnOff ( int nBearbeiten, int nSave, int nDelete, 
			  		    int nSearch, int nNext, int nPrev );
	void SaveMenuState( bool& bBearbeiten, bool& bSave, bool& bDelete, 
			  		    bool& bSearch, bool& bNext, bool& bPrev ) ;

	void SetMenuState ( bool bBearbeiten, bool bSave, bool bDelete, 
			  		    bool bSearch, bool bNext, bool bPrev ) ;
	void PushMenuState(  ) ;
	void PopMenuState(  );

	void SetDruckState( bool bDruck );

	class ChPflegeView*	GetActView( ); 
	void  SetBearbeiten( int status );
	void  CleanUp();

	void  EnableTbComboBranches(  BOOL bEnable );

private:
	bool CreateToolBarWithCombobox();
	void InsertView( int nViewNr, char *cViewTitle, CView *pView );
	void InitViews( );
	void ResetViews( );
	void DeleteViews( );
	void SetView( int nViewNr, bool bForce = false );
	int  GetViewNr( CView* pView );
	int  GetActViewNr( );
	int  CloseActView( );
//	int  HandleDataChanged( ChPflegeView* ActView );

	int GetMnrFromView( int ViewNr );
	bool TestAendern();

// Views
	struct ONE_VIEW *m_AllViews;
	int  m_nAnzViews;
	int  m_nActiveView;

//	Zustaende
	bool m_bIsView;
	bool m_bPflege;
	bool m_bBearbeiten;
	bool m_bDelete;
	bool m_bSave;
	bool m_bSearch;
	bool m_bNext;
	bool m_bPrev;
	bool m_bIsDruck;

//	Schalter
	bool m_bAutoFrage;
	bool m_bMSStandard;

//  Keller
#define MAX_MS_ANZ 10
	bool m_msbBearbeiten[MAX_MS_ANZ];
	bool m_msbSave[MAX_MS_ANZ];
 	bool m_msbDelete[MAX_MS_ANZ];
	bool m_msbSearch[MAX_MS_ANZ];
	bool m_msbNext[MAX_MS_ANZ];
	bool m_msbPrev[MAX_MS_ANZ];
	int  m_msZeiger;


public:
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__03D6985D_6DB1_11D2_92F8_0060973B18D8__INCLUDED_)
