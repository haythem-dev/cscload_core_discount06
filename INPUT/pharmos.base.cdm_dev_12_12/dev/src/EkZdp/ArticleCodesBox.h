/******************************************************************************/
/**                                                                           */
/**   Author : T. Hörath PRZ GmbH											  */
/**   Date   : 11.01.2005                                                     */
/**                                                                           */
/******************************************************************************/

#ifndef __ARTICLECODESBOX_H__
#define __ARTICLECODESBOX_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <eklibs/hamfcs/hSqlListCtrl.h>

#include <voodoo_table_header/carticlecodes.h>
#include <voodoo_table_header/ccodetypes.h>

/*----------------------------------------------------------------------------*/
class CArticleCodesBox : public ChSqlListCtrl
{
public:
	CArticleCodesBox();
	virtual ~CArticleCodesBox();

	void CloseCursor( );

	virtual void	InitSuchBox(  );

	int	PrimeKeyOfSelectedRecord( CARTICLECODES * pSelCode );
	int SelectedCode( CARTICLECODES * pSelCode );

protected:
	virtual CString InitSelect( CString SuchBegriff );
	virtual void FillBuffer( CStringArray& s, void **vekp );

	enum { PUFFER_ANZAHL = 15 };
	
	struct SelBuf
	{
		char	ARTICLE_CODE [L_CARTICLECODES_ARTICLE_CODE + 1];
		short	CODE_TYPE;
		char	TYPE_NAME [L_CCODETYPES_NAME + 1];
		short	PREFERRED;
		long	ARTICLE_NO;
		short	SERIAL_NUMBER;
	};	

	struct SelBuf m_SelBuf;

	enum ARTICLECODE_COLUMNS
	{ ArticleCode, CodeType, TypeName, Preferred, Serial};

	int  m_fdCode;
};

#endif 
