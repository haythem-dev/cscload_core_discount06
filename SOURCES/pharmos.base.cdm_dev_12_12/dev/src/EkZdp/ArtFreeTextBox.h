/******************************************************************************/
/**                                                                           */
/**   Author : R. Raab PRZ GmbH	    										  */
/**   Date   : 21.01.2015                                                     */
/**                                                                           */
/******************************************************************************/

#ifndef __ARTFREETEXTBOX_H__
#define __ARTFREETEXTBOX_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <eklibs/hamfcs/hSqlListCtrl.h>

#include <voodoo_table_header/cartfreetext.h>
#include <voodoo_table_header/carticlecodes.h>

/*----------------------------------------------------------------------------*/
class CArtFreeTextBox : public ChSqlListCtrl
{
public:
public:
	struct CARTFREETEXTCODES{
		char	ARTIKEL_CODE			[L_CARTICLECODES_ARTICLE_CODE + 1];	// Key
	};

	CArtFreeTextBox();
	virtual ~CArtFreeTextBox();

	void CloseCursor( );

	virtual void	InitSuchBox(  );

	int	PrimeKeyOfSelectedRecord( CARTFREETEXT * pSelArtFreeText );
	int SelectedArtFreeText( CARTFREETEXT *pSelArtFreeText, CARTFREETEXTCODES *pSelArtFreeTextCodes );

protected:
	virtual CString InitSelect( CString SuchBegriff );
	virtual void FillBuffer( CStringArray& s, void **vekp );

	enum { PUFFER_ANZAHL = 5 };
	
	struct SelBuf
	{
		char	ARTIKEL_CODE_KEY [L_CARTICLECODES_ARTICLE_CODE + 1];
		short	TEXTTYPENO;
		long	DATEFROM;
		long	DATETO;
		char	FREETEXT [L_CARTFREETEXT_FREETEXT + 1];
	};	

	struct SelBuf m_SelBuf;

	enum ARTFREETEXT_COLUMNS
	{ Article, Texttypeno, Datefrom, Dateto, Freetext };

	int  m_fdArtFreeText;
};

#endif 
