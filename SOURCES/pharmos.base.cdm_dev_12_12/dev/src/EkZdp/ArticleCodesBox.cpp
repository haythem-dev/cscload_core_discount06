/******************************************************************************/
/**                                                                           */
/**   Author : T. Hörath PRZ GmbH		                                   */
/**   Date   : 18.05.2005                                                     */
/**                                                                           */
/******************************************************************************/

#include "stdafx.h"
#include "ekzdp.h"
#include "ArticleCodesBox.h"
#include "phxlib/PhxUtil.h"
#include <hdatum/phodate.h>
#include <libscsvoodoo/libscsvoodoo.h>
#include "ServerDatum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*----------------------------------------------------------------------------*/
CArticleCodesBox::CArticleCodesBox()
{
	m_fdCode    = -1;
}

/*----------------------------------------------------------------------------*/
CArticleCodesBox::~CArticleCodesBox()
{
	CloseCursor( );
}

/*----------------------------------------------------------------------------*/
void CArticleCodesBox::CloseCursor( )
{
	if ( m_fdCode >= 0 )
	{
		SqlCloseCs( m_fdCode );
		m_fdCode = -1;
	}
	
	ChSqlListCtrl::CloseCursor();
}

/*----------------------------------------------------------------------------*/
CString CArticleCodesBox::InitSelect( CString SuchBegriff )
{
	CString sql;
	
	// sql
	sql = "select ARTICLE_CODE, a.CODE_TYPE, NAME, PREFERRED_FLAG, ARTICLENO, SERIAL_NUMBER "
				"from CARTICLECODES a, CCODETYPES c where a.CODE_TYPE = c.CODE_TYPE "
				"and c.ARTNR_SUBSTITUTE = 1 and ARTICLENO = ";

	sql += SuchBegriff;
	sql += " ORDER BY PREFERRED_FLAG desc, a.CODE_TYPE, SERIAL_NUMBER ";

	return sql;
}

/*----------------------------------------------------------------------------*/
void CArticleCodesBox::FillBuffer( CStringArray& s, void **VecPtr )
{
	char str[10];

	s.SetSize( PUFFER_ANZAHL );
	
	sprintf( str, "%ld", m_SelBuf.ARTICLE_NO);
	s[5] = str;
	
	s[0] = m_SelBuf.ARTICLE_CODE;
		
	sprintf( str, "%d", m_SelBuf.CODE_TYPE);
	s[1] = str;
	
	s[2] = m_SelBuf.TYPE_NAME;
	
	if (m_SelBuf.PREFERRED == 1)
		s[3] = "X";
	else
		s[3] = " ";
	
	sprintf( str, "%d", m_SelBuf.SERIAL_NUMBER);
	s[4] = str;
	
	*VecPtr = &m_SelBuf;
}

/*----------------------------------------------------------------------------*/
void CArticleCodesBox::InitSuchBox(  )
{
	ListColumns ArtCode_Fields[] =
	{
		ArticleCode,	_strdup(CResString::ex().getStrTblText(IDS_ARTCODE)),		   200, LVCFMT_LEFT,  1, 
		CodeType,		_strdup(CResString::ex().getStrTblText(IDS_CODETYPE)),			80, LVCFMT_RIGHT, 0, 
		TypeName,       _strdup(CResString::ex().getStrTblText(IDS_TYPENAME)),		   150, LVCFMT_LEFT,  0, 
		Preferred,		_strdup(CResString::ex().getStrTblText(IDS_PREFERRED)),			70, LVCFMT_RIGHT, 0,
		Serial,			_strdup(CResString::ex().getStrTblText(IDS_SERIAL)),			70, LVCFMT_RIGHT, 0,
		-1        ,		"",																 0,			   0, 0
	};

	InitBox( PUFFER_ANZAHL, ArtCode_Fields, sizeof( struct SelBuf )  );

	for (short ColNr = 0; ColNr < GetFieldCount(); ColNr++)
		free(ArtCode_Fields[ColNr].Columns);

	SetScrollMessage( FALSE );
	SetSelectBuffer( &m_SelBuf );
}

/*----------------------------------------------------------------------------*/
int CArticleCodesBox::PrimeKeyOfSelectedRecord( CARTICLECODES * pSelCode )
{
	if ( !ItemChoise( FALSE ) )
		return -1;

	struct SelBuf *Info;
	Info = ( struct SelBuf *) GetSelectedVector();

	pSelCode->ARTICLENO			= Info->ARTICLE_NO;
	pSelCode->CODE_TYPE			= Info->CODE_TYPE;
	pSelCode->SERIAL_NUMBER		= Info->SERIAL_NUMBER;
	
	return 0;
}

/*----------------------------------------------------------------------------*/
int CArticleCodesBox::SelectedCode( CARTICLECODES * pSelCode )
{
	if ( !ItemChoise( FALSE ) )
	{
		if ( !ItemChoise( FALSE ) )
		{
			memset ( pSelCode, 0, sizeof( pSelCode) );
			return -1;
		}
	}

	struct SelBuf *Info;
	Info = ( struct SelBuf *) GetSelectedVector();

	pSelCode->ARTICLENO			= Info->ARTICLE_NO;
	pSelCode->CODE_TYPE			= Info->CODE_TYPE;
	pSelCode->SERIAL_NUMBER		= Info->SERIAL_NUMBER;
	
	strcpy(pSelCode->ARTICLE_CODE,	  Info->ARTICLE_CODE);
	pSelCode->PREFERRED_FLAG		= Info->PREFERRED;
	
	return 0;
}
