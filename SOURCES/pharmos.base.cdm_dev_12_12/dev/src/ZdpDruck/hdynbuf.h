#if !defined(AFX_HDYNBUF_H__9238F461_1700_11D1_92F8_0060973B18D8__INCLUDED_)
#define AFX_HDYNBUF_H__9238F461_1700_11D1_92F8_0060973B18D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// hDynBuf.h : header file
//


////////////////////////////////////////////////////////
// Structur des Fetch-Buffers

struct sqlv_struct
{
    int    sqlpos;				// position in fetch buffer
    char*  sqlcolumn;			// pointer to column name         
	char   sqltype;				// type of variable 
	int	   sqldatasize;			// size of data	
};

struct sqld_struct
{
	int    sqld;				// number of columns
    int    maxcolnamesize;		// max size of column name
	int    structsize;			// size of buffer
    void*  buf;					// pointer to buffer
    struct sqlv_struct **sqs;	
};


/////////////////////////////////////////////////////////////////////////////
// ChDynBuf

class ChDynBuf : public CCmdTarget
{
// Construction
public:
	ChDynBuf();

// Attributes
public:
	void  FreeFetchBuf ( );
	int   AllocFetchBuf( char *bas, bool bAllocBuf );
	long  GetFetchBufferDesc( int nFd, CString& cErrmld );
	char* GetFirstColumnName( int& size );
	char* GetNextColumnName( int& size);
	int   GetColumnNumber();
	char* GetFirstColumn( char *buf );
	char* GetNextColumn( char *buf );

// Operations
public:


// Implementation
public:
	virtual ~ChDynBuf();


private:
	void InternFreeFetchBuf ( struct sqld_struct *sqldat );
	int  sonlng( char *str, char son );
	int  InternAllocFetchBuf( char *bas, struct sqld_struct *sqldat,
							  bool bAllocBuf );
	char* GetColumn( char *buf, struct sqlv_struct *sq );
	void  out_dbl( char *zeile, double d );

// Members
private:
	struct sqld_struct m_StruDesc;
	int m_nColumnNameIndex;
	int m_nColumnIndex;

};

/////////////////////////////////////////////////////////////////////////////


#endif // !defined(AFX_HDYNBUF_H__9238F461_1700_11D1_92F8_0060973B18D8__INCLUDED_)
