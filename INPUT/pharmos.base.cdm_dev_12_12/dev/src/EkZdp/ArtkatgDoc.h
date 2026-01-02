#ifndef ARTKATGDOC_H_INCLUDE
#define ARTKATGDOC_H_INCLUDE

// ArtkatgDoc.h : header file
//

#include <voodoo_table_header/artkatg.h>
#include <voodoo_table_header/zgrppflege.h>

#include <eklibs/wdbups/wpp_dbas.h>


class CArtkatgDoc
{

private:
	// members
	struct ARTKATG m_Buf;
	char	temp[200];
	struct ARTKATG m_BufOld;
	struct ARTKATG m_BufSave;
	char   m_PrimekeyCond[100];
	int    m_Fd;
	long   m_lStatus;

	//	zgrppflege
	long   m_tagesdatum;
	int    m_Fd_Zgrppflege;
	long   m_lStatus_Zgrppflege;
	struct ZGRPPFLEGE m_ZgrppflegeBuf;


public:	 
	CArtkatgDoc();           // protected constructor used by dynamic creation

// Operations
public:

	struct ARTKATG* GetBuffer();

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

	long CheckDelete ();
	bool WasChangedRabgrp ();

	void SetTagesdatum( long datum );

private:
	void SetPrimekeyCondition( );

	// Zgrppflege
	int  GetBufferDesc_Zgrppflege( CString &cErrmld );
	long StoreRecord_Zgrppflege( long datum, CString &cErrmld );

	// nicht immer
	void FillCmpIndikator( );

// Implementation
public:  
	virtual ~CArtkatgDoc();

};

/////////////////////////////////////////////////////////////////////////////
//

#endif // ARTKATGDOC_H_INCLUDE