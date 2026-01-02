#if !defined(AFX_GETREGION_ACA1_11D2_92F8_0060973B18D8__INCLUDED_)
#define AFX_GETREGION_ACA1_11D2_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// GetRegion.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CGetRegion command target

class CGetRegion {

private:
	CGetRegion(); 
	
public:
	CGetRegion( bool bIsStandardEngine );

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CGetRegion();

public:
	long ReadRegiones( CString& cErrmld );
	long FirstRegion( CString& StandOrt, CString& cErrmld );
	long NextRegion ( CString& StandOrt );
	CString GetCurrentRegionName( bool mode );
	void SetCurrentRegion( int index );
	int  SetCurrentRegionViaNr( short nr );
	short GetCurrentRegionNumber( );
	bool GetRegionName( CString& Name, short region, bool mode, bool solo );
	int  GetNumberOfRegiones();
	int  GetInfoOfRegiones( int index, short &region, CString& Name );

private:
	int	 m_Fd;
	long m_nSqlCode;
	long m_nIsamCode;
	int  m_nNumberOfRegiones;
	int  m_nCurrentRegionIndex;
	int  m_nHelpIndex;

	bool m_bIsStandardEngine;
	bool m_bImmerNeulesen;

	CString m_cErrMeld;
	CStringArray	m_cRegionNames;
	CStringArray	m_cRegionRawNames;
	CWordArray		m_wRegionNr;

	long OpenCs();
	long Fetch();
	void CloseCs();
	void MakeGrossKlein( CString& cStr );
	CString MakeRegionName( CString Name );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETREGION_ACA1_11D2_92F8_0060973B18D8__INCLUDED_)
