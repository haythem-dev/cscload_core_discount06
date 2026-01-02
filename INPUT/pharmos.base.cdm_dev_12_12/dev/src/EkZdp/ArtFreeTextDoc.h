/******************************************************************************/
/**                                                                           */
/**   Author : R. Raab PRZ GmbH	    										  */
/**   Date   : 21.01.2015                                                     */
/**                                                                           */
/******************************************************************************/
#ifndef __ARTFREETEXTDOC_H__
#define __ARTFREETEXTDOC_H__

#include <voodoo_table_header/cartfreetext.h>
// #include <zpznpflege.h>

#include <eklibs/wdbups/wpp_dbas.h>

#define MAX_NUMBER_OF_LINES 5

/******************************************************************************/
class CArtFreeTextDoc
{
private:
	char	*m_Anwender;
	char	m_PrimekeyCond[500];

	char	m_Textline[MAX_NUMBER_OF_LINES][L_CARTFREETEXT_FREETEXT];
	short	m_NumberOfLinesOld;
	short	m_NumberOfLinesNew;

	int		m_Fd_ArtFreeText;
	long	m_lStatus_ArtFreeText;
	
	//	zpznpflege
/*	long   m_tagesdatum;
	int    m_Fd_Zpznpflege;
	long   m_lStatus_Zpznpflege;
	struct ZPZNPFLEGE m_ZpznpflegeBuf; */

	long	DeleteRecord_ArtFreeText	( CString& cErrmld );
	long	DeleteOneRecord_ArtFreeText ( short i, CString& cErrmld );
	long	StoreRecord_ArtFreeText		( CString& cErrmld );
	void	SetPrimekeyCondition_ArtFreeText();
	int		GetBufferDesc_ArtFreeText	( CString &cErrmld );

public:	
	CArtFreeTextDoc();           // protected constructor used by dynamic creation
	virtual ~CArtFreeTextDoc();

	struct CARTFREETEXT* GetBuffer();
	
	short	GetAllTextLines ();
	short	DismantleTextIntoLines (char *Text);

//	void SetTagesdatum( long datum );

private:
	int  GetBufferDesc( CString &cErrmld );
	struct CARTFREETEXT		m_Buf;
	struct CARTFREETEXT		m_BufOld;
	
	// Zpznpflege
/*	int  GetBufferDesc_Zpznpflege( CString &cErrmld );
	long StoreRecord_Zpznpflege( long datum, CString &cErrmld ); */

	// nicht immer
	void FillCmpIndikator( );

public:
	void FreeBufferDesc( );
	long ReadRecord  ( CString& cErrmld );
	long DeleteRecord( CString& cErrmld );
	long StoreRecord ( CString& cErrmld );
	int  InitRecord  ( CString& cErrmld );

	void InitPflegeDesc(  char* Anwender );
	void StoreBuffer();
	void RestoreBuffer();
};

#endif 
