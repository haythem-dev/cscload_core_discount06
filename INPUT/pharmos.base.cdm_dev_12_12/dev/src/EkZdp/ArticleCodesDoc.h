/******************************************************************************/
/**                                                                           */
/**   Author : T. Hörath PRZ GmbH											  */
/**   Date   : 11.01.2006                                                     */
/**                                                                           */
/******************************************************************************/
#ifndef __ARTICLECODESDOC_H__
#define __ARTICLECODESDOC_H__

#include <voodoo_table_header/carticlecodes.h>
#include <voodoo_table_header/zpznpflege.h>

#include <eklibs/wdbups/wpp_dbas.h>

/******************************************************************************/
class CArticleCodesDoc
{
private:
	char   *m_Anwender;
	char   m_PrimekeyCond[500];

	int    m_Fd_ArtCode;
	long   m_lStatus_ArtCode;
	
	//	zpznpflege
	long   m_tagesdatum;
	int    m_Fd_Zpznpflege;
	long   m_lStatus_Zpznpflege;
	struct ZPZNPFLEGE m_ZpznpflegeBuf;

	long DeleteRecord_ArtCode  ( CString& cErrmld );
	long StoreRecord_ArtCode   ( CString& cErrmld, const bool resetPreviousPreferred );
	void SetPrimekeyCondition_ArtCode();
	int  GetBufferDesc_ArtCode ( CString &cErrmld );

public:	
	CArticleCodesDoc();           // protected constructor used by dynamic creation
	virtual ~CArticleCodesDoc();

	struct CARTICLECODES* GetBuffer();

	void SetTagesdatum( long datum );

private:
	int  GetBufferDesc( CString &cErrmld );
	struct CARTICLECODES m_Buf;
	struct CARTICLECODES m_BufOld;
	
	// Zpznpflege
	int  GetBufferDesc_Zpznpflege( CString &cErrmld );
	long StoreRecord_Zpznpflege( long datum, CString &cErrmld );

	// nicht immer
	void FillCmpIndikator( );

public:
	void FreeBufferDesc( );
	long ReadRecord  ( CString& cErrmld, const bool resetPreviousPreferred = false );
	long DeleteRecord( CString& cErrmld );
	long StoreRecord ( CString& cErrmld, const bool resetPreviousPreferred = false );
	int  InitRecord  ( CString& cErrmld );

	short ReadCodeTypeLength(const short codeType);
	short ReadCodeTypeMaxNumber(const short codeType);

	void InitPflegeDesc(  char* Anwender );
	void StoreBuffer();
	void RestoreBuffer();
};

#endif 
