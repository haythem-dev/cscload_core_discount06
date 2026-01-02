#if !defined(AFX_GETBRANCHES_ACA1_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_GETBRANCHES_ACA1_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GetBranches.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CGetBranches command target

class CGetBranches
{
private:
	CGetBranches();       
    
public:
	CGetBranches(  bool bIsStandardEngine );

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CGetBranches();

public:
	long ReadBranchOffices( CString& cErrmld );
	long FirstStandortLang( CString& StandOrt, CString& cErrmld );
	long NextStandortLang ( CString& StandOrt );
	long FirstRegionStandortLang( short region, CString& StandOrt,
								  CString& cErrmld );
	long NextRegionStandortLang ( short region, CString& StandOrt );
	CString GetCurrentBranchName( bool mode );
	void SetCurrentBranch( int index );
	short GetCurrentBranchNumber( );
	int  SetCurrentBranchViaFilialnr( short filialnr );
	int  GetAllBranchNumbers( CWordArray& wNumbers );
	int  GetAllBranches( CWordArray& wNumbers, CStringArray& sNames, bool mode );
	int  GetAllExistentBranches( CWordArray& wNumbers, CStringArray& sNames, 
								 bool mode );
	CString GetBranchShortName( short filialnr );
	CString GetBranchType( short filialnr );

	CString GetBranchesInRegion( );
	CString GetBranches( );
private:
	int	 m_Fd;
	long m_nSqlCode;
	long m_nIsamCode;
	int  m_nNumberOfRegionBranches;
	int  m_nNumberOfBranches;
	int  m_nCurrentBranchIndex;
	int  m_nHelpIndex;
	int  m_nBeginOfRegionIndex;

	bool m_bIsStandardEngine;
	bool m_bImmerNeulesen;

	CString m_cErrMeld;
	CWordArray		m_wRegion;
	CStringArray	m_cStandortLang;
	CStringArray	m_cStandortKurz;
	CStringArray	m_cFilialArt;
	CWordArray		m_wFilialNr;

	long OpenCs();
	long Fetch();
	void CloseCs();
	void MakeGrossKlein( CString& cStr );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETBRANCHES_ACA1_11D2_92F8_0060973B18D8__INCLUDED_)
