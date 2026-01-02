#if !defined(AFX_GETBRANCHES_ACA1_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_GETBRANCHES_3E7CA01_ACA1_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GetBranches.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CGetBranches command target

class CGetBranches
{
public:
	CGetBranches();           // protected constructor used by dynamic creation

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
	CString GetCurrentBranchName( bool mode );
	void SetCurrentBranch( int index );
	short GetCurrentBranchNumber( );

private:
	int	 m_Fd;
	long m_nSqlCode;
	long m_nIsamCode;
	int  m_nNumberOfBranches;
	int  m_nCurrentBranchIndex;
	int  m_nHelpIndex;
	CString m_cErrMeld;
	CStringArray	m_cStandortLang;
	CWordArray		m_wFilialNr;

	long OpenCs();
	long Fetch();
	void CloseCs();
	void MakeGrossKlein( CString& cStr );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETBRANCHES_H__03E7CA01_ACA1_11D2_92F8_0060973B18D8__INCLUDED_)
