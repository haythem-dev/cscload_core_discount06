// ZdpDruck.h : main header file for the EKADM application
//

#if !defined(AFX_ZDPDRUCK_H__6E2D8B67_AEC3_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_ZDPDRUCK_H__6E2D8B67_AEC3_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEk1App:
// See ZdpDruck.cpp for the implementation of this class
//

struct sServer {
	CString ServerProgramName;
	char *ServerProgram;
	int  CompressMode;
	int  FetchMode;
	int  ServerMode;
};

enum Country_Return_Type { KFZ = 1, ISO3166 };
enum SubModul_Return_Type { Verz = 1, Suffix };

CString 	GetCountry( Country_Return_Type crt = KFZ, CString Database = "" );
CString 	GetSubModule( SubModul_Return_Type srt, CString Database = "" );
long      GetWWSBinVerzeichnis( CString &cDirec, CString &errmld );


class CEk1App : public CWinApp
{
public:
	CEk1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEk1App)
	public:
	virtual BOOL InitInstance();
	virtual int  ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEk1App)
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
	int		GetServerMode();
	CString GetServerProgram( );
	CString GetServerProgramName( );
	void    SetServerProgramName(CString name);
	int     GetCompressMode();
	void    SetCompressMode( int nCompressMode );
	bool    GetBufferedMode();
	void    SetBufferedMode( bool nBufferedMode );

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
	bool    SetLockmode();
	bool    verifyUADM();
	bool    doUADMLogin();

private:
	struct  sServer    m_Server[2]; 
	int     m_nActualServer;
	CString m_strINIFile;
	bool    m_bConnected;
	bool    m_bUADM;
//	class CConSoVa1    *m_Con;
	class CConnect	   *m_Con;	
	class CGetBranches *m_Branch;

	// line-protocol
	int m_nClientProtocolMode;
	CString m_strClientProtocolFile;

	int m_nServerProtocolMode;
	CString m_strServerProtocolFile;

	// Fetch-Pufferung
	bool m_bBufferedFetch;

	// Komprimierumgs_modus
	int  m_nCompressMode;
	bool m_bCompress;

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZDPDRUCK_H__6E2D8B67_AEC3_11D2_92F8_0060973B18D8__INCLUDED_)
