// ZdpUtil.h : Haupt-Header-Datei für die Anwendung ZdpUtil
//

#if !defined(AFX_ZDPUTIL_H__3D56D502_9FF8_4977_8D5A_AADA2694B4E9__INCLUDED_)
#define AFX_ZDPUTIL_H__3D56D502_9FF8_4977_8D5A_AADA2694B4E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CZdpUtilApp:
// Siehe ZdpUtil.cpp für die Implementierung dieser Klasse
//

#include "libsccpattern.h"
#include "libscgmmultilang.h"

using sccmn::VSingleton;
using scgui::CResString;
using scgui::CWinAppMultiLang;
using scgui::CFrameWndMultiLang;
using scgui::CFormViewMultiLang;
using scgui::CDialogMultiLang;
using scgui::CPropertyPageMultiLang;
using scgui::MsgBox1;
using scgui::MsgBox2;

INT_PTR		MsgBoxOK(const char * const spMsg, UINT uiType = MB_ICONEXCLAMATION, const char * const spCaption = NULL);
INT_PTR		MsgBoxOK(UINT uiMsg, UINT uiType = MB_ICONEXCLAMATION, UINT uiCaption = AFX_IDS_APP_TITLE);
INT_PTR		MsgBoxYesNo(const char * const spMsg, UINT uiType = MB_ICONQUESTION | MB_DEFBUTTON1, const char * const spCaption = NULL);
INT_PTR		MsgBoxYesNo(UINT uiMsg, UINT uiType = MB_ICONQUESTION | MB_DEFBUTTON1,UINT uiCaption = AFX_IDS_APP_TITLE);

BOOL		IsCountry(char *Lkz);
BOOL		IsPrewhole();
BOOL		IsIvrylab();
	
struct sServer
{
	CString ServerProgramName;
	char *ServerProgram;
	char *DialogServer;
};

	enum Country_Return_Type { KFZ = 1, ISO3166 };
	enum SubModul_Return_Type { Verz = 1, Suffix };

	enum Verzeichnis_Typ { bin = 1, util };

	CString 	GetCountry( Country_Return_Type crt = KFZ, CString Database = "" );
	CString 	GetSubModule( SubModul_Return_Type srt, CString Database = "" );
	long		GetWWSDateiVerz( CString &cDirec, CString &errmld );
	long		GetWWSDateiUnterVerz( CString &cDirec, Verzeichnis_Typ vt, CString &errmld );
	

class CZdpUtilApp : public CWinAppMultiLang
{
public:
	CZdpUtilApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZdpUtilApp)
	public:
	virtual BOOL InitInstance();
	virtual int  ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZdpUtilApp)
	afx_msg void OnAppAbout();
	afx_msg void OnCalculator();
	afx_msg void OnServer();
	afx_msg void OnUpdateServer(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	bool    IsUADM();
	bool    IsSyncronized();
	CString GetServerHandler( );
	CString GetServerName();
	CString GetDbaseName();
	CString GetUserName( );
	char*   GetRefToAnwender( );

	CString GetServerProgram( );
	CString GetServerProgramName( );
	void SetServerProgramName (CString name);

	bool    DarfRechtePflegen();
	bool    DarfSubSuperAnlegen( );
	bool    DarfMenuPflegen( int MenuNr );
	bool	DarfMenuAendern( int MenuNr );
	bool    ReadUserRights( CString& cErrmld );
	CStringArray* GetLoginRechte();
	CUIntArray*   GetLoginRegion();

	bool    IsStandardEngine();

	CString GetCurrentBranchName( bool mode);
	void    SetCurrentBranch( int index );
	short	GetCurrentBranchNumber( );
	bool	IsConnected();
	bool	YouWantToDo( CString Frage );
	bool    YouWantToStoreRecord( );
	bool    YouWantToDeleteRecord( );
	bool    IsSafeToExit( );
	void	BeginWaitAction( );
	void	EndWaitAction( );
	void	MeldRecordWasDeleted( );
	void	SetMenuOnOff ( int nBearbeiten, int nSave, int nDelete, 
						   int nSearch, int nNext, int nPrev );
	void	SaveMenuState( bool& bBearbeiten, bool& bSave, bool& bDelete, 
						   bool& bSearch, bool& bNext, bool& bPrev );
	void	SetMenuState ( bool bBearbeiten, bool bSave, bool bDelete, 
			  			   bool bSearch, bool bNext, bool bPrev );
	void    PushMenuState(  );
	void	PopMenuState(  );
	void	SetDruckState( bool bDruck );

	void    EnableTbComboBranches( BOOL bEnable );

	void	ChangeToView( int nViewNr );
	void	ChangeBackToView( int nViewNr );
	void	ChangeBackToView( CView *pView );


private:
	bool    verifyUADM();
	bool    doUADMLogin();
	struct  sServer    m_Server[1]; 
	int     m_nActualServer;
	CString m_strINIFile;
	bool m_bConnected;
	bool m_bUADM;

	class CConnect	   *m_Con;	
	class CGetBranches *m_Branch;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ZDPUTIL_H__3D56D502_9FF8_4977_8D5A_AADA2694B4E9__INCLUDED_)
