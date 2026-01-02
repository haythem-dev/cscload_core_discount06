#if !defined(AFX_RECHTEDLG_H__407B4B22_DFAB_11D3_92FB_0060973B18D8__INCLUDED_)
#define AFX_RECHTEDLG_H__407B4B22_DFAB_11D3_92FB_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// RechteDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRechteDlg dialog

struct sDescription
{
	short index;
	char  *name;
};


class CRechteDlg : public CDialog
{
// Construction
public:
	CRechteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRechteDlg)
	enum { IDD = IDD_RECHTE };
	CButton	m_SUPER;
	CButton	m_SUBSUPER;
	CButton	m_PASTE;
	CButton	m_COPY;
	CButton	m_SPEICHERN;
	CComboBox	m_USERNAME;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRechteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

public:

	~CRechteDlg();

	bool Initialize( struct sDescription* sMenPunkt, int MenAnz,
					 struct sDescription* sRegion,   int RegAnz,
					 short  ProgramNumber, bool bAnlageSubSuper,
					 CString LoginUserName,
					 CStringArray* LoginRechte,
					 CUIntArray*   LoginRegion,	
					 bool   bStandardEngine,
				 	 CString Database );
private:
	bool AllocButtons( );
	void InitButtons();
	void FreeButtons();
	BOOL GenStaticFeld( CStatic *pWnd, CStatic *pWndTop, LPCTSTR lpszText, 
						bool mode, bool first );
	BOOL GenRadioFeld ( CButton *pWnd, CButton *pWndTop, UINT nID, 
					    bool mode, bool first );

	void CalcStaticRect( CWnd *TopMuster, CRect *NewRect, bool mode, bool first );
	BOOL GenRadioFeld_LT( CButton* pWnd, 
						  CButton* pWndLeft, CStatic* pWndTop, UINT nID );
	void CalcRect_LT ( CWnd* LeftMuster, CWnd* TopMuster, CRect* NewRect );
	void CalcRect_LLL( CWnd* LeftMuster1, CWnd* LeftMuster2, CWnd* LeftMuster3,
					   CRect* NewRect );
	BOOL GenRadioFeld_LLL( CButton* pWnd, CButton* pWndLeft1, 
						   CButton* pWndLeft2, CButton* pWndLeft3, UINT nID );

	void GenFont( CWnd *pWnd );
	void GenDialogMaske();

	void EnableButtons( BOOL mode );
	void EnablePushButtons( BOOL mode );
	void EnableButtonsFromLoginRechten( );
	bool AreNamesEqual( CString s1, CString s2 );

	long LeseUser( CString& sErrmld );
	long LeseRechte( CString rUser, CString& sErrmld );
	void ButtonsFromRechte( );
	void RechteFromButtons( );
	long StoreRechte( CString& rErrmld );

	void CopyRechte( );
	void PasteRechte( );
	void PasteSuperUserRechte( );

	bool  IsToInsert( CString cRechte );
	short NextFreeRegion( );
	int   IsInRegion( short region );

	void GetRegionsRechte( CString& rRechte, int region,
						   CStringArray* aRechte,
						   CUIntArray*   aRegion  );
	bool SindAktuelleRechteUntermengeVonLoginRechten( );

private:
	struct sDescription* m_sMenPunkt;
	int    m_MenAnz; 
	struct sDescription* m_sRegion;
	int    m_RegAnz; 

	CStringArray m_aRechte;
	CUIntArray   m_aRegion;		
	CString      m_aktUser;

	CStringArray* m_LoginRechte;
	CUIntArray*   m_LoginRegion;		
	CString		  m_LoginUserName;
	CString		  m_DefaultDatabase;

	CStringArray m_aSaveRechte;
	CUIntArray   m_aSaveRegion;	

	enum { IDC_BASE = 3000 }; 

	CButton**	m_cButNone;
	CButton**	m_cButRead;
	CButton**	m_cButWrite;

	CStatic**	m_cStMenPunkt;
	CStatic**	m_cStRegion;

	short		m_ProgramNumber;
	short       m_nMaxMenPunkt;

	bool		m_bAnlageSubSuper;
	bool		m_bSubSuperGelesen;
	bool 		m_bPaste;

	// nur zum Test
	bool m_bStandardEngine;
	long ChangeToDatabase( CString Database );
	long ChangeToDefaultBase( );
	long ChangeToPhosix( );
	char* GetDatabase();

protected:

	// Generated message map functions
	//{{AFX_MSG(CRechteDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRechteBpSpeichern();
	afx_msg void OnCloseupRechteCbUsername();
	afx_msg void OnRechteBpCopy();
	afx_msg void OnRechteBpPaste();
	afx_msg void OnRechteBpSuper();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECHTEDLG_H__407B4B22_DFAB_11D3_92FB_0060973B18D8__INCLUDED_)
