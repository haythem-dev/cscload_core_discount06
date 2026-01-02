#ifndef ARTNRBLDOC_H_INCLUDE
#define ARTNRBLDOC_H_INCLUDE

// ArtnrblDoc.h : header file
//

#include <artnrbl.h>

#include <wpp_dbas.h>


class CArtnrblDoc
{

private:
	// members
	struct ARTNRBL m_Buf;
	struct ARTNRBL m_BufOld;
	struct ARTNRBL m_BufSave;
	char   m_PrimekeyCond[100];
	int	   m_Fd;
	long   m_lStatus;

public:	
	CArtnrblDoc();           // protected constructor used by dynamic creation

// Operations
public:

	struct ARTNRBL* GetBuffer();

	// record read write delete
private:
	int  GetBufferDesc( CString &cErrmld );
	bool IsToDelete_Artnrbl( );
public:
	void FreeBufferDesc( );
	long ReadRecord  ( CString& cErrmld );
	long DeleteRecord( CString& cErrmld );
	long StoreRecord ( CString& cErrmld );
	int  InitRecord  ( CString& cErrmld );

	void InitPflegeDesc( char* Anwender );
	void StoreBuffer();
	void RestoreBuffer();

private:
	void SetPrimekeyCondition( );
	// nicht immer
	void FillCmpIndikator( );

// Implementation
public: 
	virtual ~CArtnrblDoc();

};

/////////////////////////////////////////////////////////////////////////////
//

#endif // ARTNRBLDOC_H_INCLUDE