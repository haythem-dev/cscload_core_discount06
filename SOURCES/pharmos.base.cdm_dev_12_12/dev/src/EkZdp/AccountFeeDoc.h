#ifndef ACCOUNTFEEDOC_H_INCLUDE
#define ACCOUNTFEEDOC_H_INCLUDE

// ArtnrblveDoc.h : header file
//

#include <voodoo_table_header/caccountfee.h>

#include <eklibs/wdbups/wpp_dbas.h>


class CAccountFeeDoc
{

private:
	// members
	struct CACCOUNTFEE m_Buf;
	struct CACCOUNTFEE m_BufOld;
	struct CACCOUNTFEE m_BufSave;

	char   *m_Anwender;
	char   m_PrimekeyCond[100];
	long   m_lStatus;

	int    m_Fd_AccountFee;

public:	
	CAccountFeeDoc();  
	virtual ~CAccountFeeDoc();

// Operations
	struct CACCOUNTFEE* GetBuffer();
	struct CACCOUNTFEE* GetOldBuffer();
	
// record read write delete
	void FreeBufferDesc( );
	long ReadRecord  ( CString& cErrmld );
	long DeleteRecord( CString& cErrmld );
	long StoreRecord ( CString& cErrmld );
	int  InitRecord  ( CString& cErrmld );

	void InitPflegeDesc( char* Anwender );
	void StoreBuffer();
	void RestoreBuffer();

private:
	int  GetBufferDesc( CString &cErrmld );
	void SetPrimekeyCondition( );
	// nicht immer
	void FillCmpIndikator( );
	int  IsRecordModified( CString &cErrmld );
};

/////////////////////////////////////////////////////////////////////////////
//

#endif // ACCOUNTFEEDOC_H_INCLUDE