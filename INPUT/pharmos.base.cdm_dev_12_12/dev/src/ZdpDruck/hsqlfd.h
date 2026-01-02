#if !defined(AFX_HSQLFD_H__9238F461_1700_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_HSQLSEL_H__9238F461_1700_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// hSqlFd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ChSqlFd window

class ChSqlFd : public CCmdTarget
{
// Construction
public:
	ChSqlFd();

// Attributes
public:

	enum
	{	
		S_WITHOUT_SCROLL = 0,
		S_WITH_SCROLL    = 1,
		S_WITHOUT_HOLD   = 0,
		S_WITH_HOLD      = 2
	};


// Operations
public:

// Implementation
public:
	virtual ~ChSqlFd();

	void SetSelectBuffer( void *SelBuf );
	int  GetCursorFd();
	virtual void CloseCursor( );   // neu 05.11.98
	long FetchNextCursor();
	long FetchPrevCursor();

	long GetSqlError();

	virtual long OpenCursor( CString  SuchBegriff, int OpenMode, 
							 CString& sErrmld );
	virtual long FetchCursor ( long Pos );
// 	virtual CString InitSelect( CString SuchBegriff ) = 0;

	bool IsScrollCursor();
	bool IsCursorWithHold();


///////////////////////////////////////////////	

	int StartSelect( CString Sql, int OpenMode, int nMaxItemNumber,
					 CString& sErrmld );
	int NextSelect ( CString& sErrmld );
	int PrevSelect ( CString& sErrmld );
	void* GetBuffer( );
	void* GetBuffer( int index );
	int PosFetch   ( int index );

	long NextSingleSelect( CString& sErrmld );
	long PrevSingleSelect( CString& sErrmld );
	int  ActualSelect( int& mRichtung, CString& sErrmld );

	long GetSqlCount( CString Sql, long *nCount, CString& sErrmld ) ;

	void SetWaitInfo( bool mode );

	void ReplaceBuffer( int index, void* SelBuf );

private:
	void FreeVector();
	void AllocVector( int nVecWidth );
	void InsertBuffer( int index );
	int  FetchBuffer( int step, int manz );

	int  FirstBuffer( int buf_anz );
	int  NextBuffer ( int buf_anz );
	int  PrevBuffer ( int buf_anz );

	// Members
protected:
	int  m_Fd;
	void *m_SelBuf;
	int	 m_nBufLen;

	bool m_bScroll;
	bool m_bHold;

	int	 m_nMaxBufNumber;
	int	 m_nActBufNumber;
	int	 m_nDeletedItems;
	int	 m_nVekBreite;
	long m_nPrevind;
	long m_nBlaetterIndex;
	int  m_nAuswahlIndex;
	bool m_bAuswahlEnde;
	bool m_bWaitInfo;
	long m_nSqlError;

	void **m_VekPtr;

};

/////////////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_HSQLFD_H__9238F461_1700_11D1_92F8_0060973B18D8__INCLUDED_)
