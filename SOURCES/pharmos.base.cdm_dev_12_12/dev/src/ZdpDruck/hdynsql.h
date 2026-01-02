#if !defined(AFX_HDYNSQL_H__9238F461_1700_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_HDYNSQL_H__9238F461_1700_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// hDynSql.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ChDynSql

class ChDynSql : public CCmdTarget
{
// Construction
public:
	ChDynSql();

// Attributes
public:

// Operations
public:
	int ScanSql( CString cSql, bool bExecute, CString& cErrmld );
	bool IsSelectStmnt( );

// Implementation
public:
	virtual ~ChDynSql();


private:
	int DynSql( char *sql, CString& cErrmld );
	int DynConnect( char *sql, CString& cErrmld );
	int DynDisconnect( char *sql, CString& cErrmld );
	int DynSetConnection( char *sql, CString& cErrmld );
	int DynSelectStmnt( char *sql, CString& cErrmld );

	int scan_select( char *str );
	int scan_into_temp( char *str );
	int test_begriff( char *str, char *begriff );
	char* scan_muster( char *str, char *muster, int *s );
	char* scan_connect( char *str, int *s );

	// Members
protected:
	long m_nSqlError;
	long m_nIsamError;
	int  m_nSqlStatus;

};

/////////////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_HDYNSQL_H__9238F461_1700_11D1_92F8_0060973B18D8__INCLUDED_)
