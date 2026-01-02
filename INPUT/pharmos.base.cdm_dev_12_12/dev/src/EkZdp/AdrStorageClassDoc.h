#ifndef ADRSTORAGECLASSDOC_H_INCLUDE
#define ADRSTORAGECLASSDOC_H_INCLUDE

// AdrStorageClassDoc.h : header file
//

#include <voodoo_table_header/cadrstorageclass.h>
#include <voodoo_table_header/caccdangerroute.h>
// #include <voodoo_table_header/zgrppflege.h>

#include <eklibs/wdbups/wpp_dbas.h>


class CAdrStorageClassDoc
{

private:
	// members
	struct CADRSTORAGECLASS m_Buf;
	struct CADRSTORAGECLASS m_BufOld;
	struct CADRSTORAGECLASS m_BufSave;

	char   m_PrimekeyCond[100];
	int	   m_Fd;
	long   m_lStatus;

	//	zgrppflege
/*	long   m_tagesdatum;
	int    m_Fd_Zgrppflege;
	long   m_lStatus_Zgrppflege;
	struct ZGRPPFLEGE m_ZgrppflegeBuf; */

public:	  
	CAdrStorageClassDoc();           // protected constructor used by dynamic creation

// Operations
public:
	struct CADRSTORAGECLASS* GetBuffer();

	// record read write delete
private:
	int  GetBufferDesc( CString &cErrmld );

public:
	void FreeBufferDesc( );
	long ReadRecord  ( CString& cErrmld );
	long DeleteRecord( CString& cErrmld );
	long StoreRecord ( CString& cErrmld );
	int  InitRecord  ( CString& cErrmld );

	void InitPflegeDesc( char* Anwender );
	void StoreBuffer();
	void RestoreBuffer();

//	void SetTagesdatum( long datum );

private:
	void SetPrimekeyCondition( );

	// Zgrppflege
/*	int  GetBufferDesc_Zgrppflege( CString &cErrmld );
	long StoreRecord_Zgrppflege( long datum, CString &cErrmld ); */

	// nicht immer
	void FillCmpIndikator( );

// Implementation
public:  
	virtual ~CAdrStorageClassDoc();

};

/////////////////////////////////////////////////////////////////////////////
//

#endif // ADRSTORAGECLASSDOC_H_INCLUDE