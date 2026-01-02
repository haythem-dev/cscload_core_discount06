/******************************************************************************/
/**                                                                           */
/**   Author : R. Raab PRZ GmbH	    										  */
/**   Date   : 10.10.2007                                                     */
/**                                                                           */
/******************************************************************************/

#include "stdafx.h"
#include "ekzdp.h"
#include "ArtFreeTextBox.h"
#include <phxlib/PhxUtil.h>
#include <hdatum/phodate.h>
#include <libscsvoodoo/libscsvoodoo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*----------------------------------------------------------------------------*/
CArtFreeTextBox::CArtFreeTextBox()
{
	m_fdArtFreeText    = -1;
}

/*----------------------------------------------------------------------------*/
CArtFreeTextBox::~CArtFreeTextBox()
{
	CloseCursor( );
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextBox::CloseCursor( )
{
	if ( m_fdArtFreeText >= 0 )
	{
		SqlCloseCs( m_fdArtFreeText );
		m_fdArtFreeText = -1;
	}
	
	ChSqlListCtrl::CloseCursor();
}

/*----------------------------------------------------------------------------*/
CString CArtFreeTextBox::InitSelect( CString SuchBegriff )
{
	CString sql;
	CString sql2;

	int iPos;

	CString cSuchbKey;
	CString cSuchbHeute;
	CString KeyNr;

	char cSuche;

	bool und_noetig = false;

	iPos = SuchBegriff.Find(";");

	while (iPos > 0)
	{
		cSuche = SuchBegriff.GetAt(0);
		cSuchbKey = SuchBegriff.Mid(1, iPos - 1);
		SuchBegriff = SuchBegriff.Mid(iPos + 1);
		iPos = SuchBegriff.Find(";");

		KeyNr.Format("%ld", atol( cSuchbKey ) );

		if (und_noetig)
			sql2 += "and ";
		else
			und_noetig = true;

		sql2 += "FT.ARTICLENO = ";
		sql2 += KeyNr;
	}

	// sql
	sql =	"select KEYCODE.ARTICLE_CODE, TEXTTYPENO, DATEFROM, DATETO, FREETEXT " 
			"from CARTFREETEXT as FT, outer CARTICLECODES as KEYCODE where ";

	sql += sql2;
	
	sql += " and FT.ARTICLENO = KEYCODE.ARTICLENO ";
	sql += " and KEYCODE.PREFERRED_FLAG = 1";
	sql += " and FT.LINE_NUMBER = 1";
	sql += " and KEYCODE.CODE_TYPE in (SELECT CODE_TYPE FROM CCODETYPES WHERE ARTNR_SUBSTITUTE = 1)";
	sql += " order by 1, 2, 3, 4"; 

	return sql;
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextBox::FillBuffer( CStringArray& s, void **VecPtr )
{
	char str[12];

	s.SetSize( PUFFER_ANZAHL ); 

	CString code;
	code = m_SelBuf.ARTIKEL_CODE_KEY;

	if (code.Trim().IsEmpty())
		s[0] = '0';
	else
	{
		s[0] = m_SelBuf.ARTIKEL_CODE_KEY;
		s[0].Trim();	// damit keine Punkte am Ende des Feldes angezeigt werden, weil es länger ist als die Spalte
	}
	
	sprintf( str, "%d", m_SelBuf.TEXTTYPENO);
	s[1] = str;
	
	ConvFromPhoDate( str, m_SelBuf.DATEFROM, "tt.mm.jjjj" );
	s[2] = str;
	
	ConvFromPhoDate( str, m_SelBuf.DATETO, "tt.mm.jjjj" );
	s[3] = str;
	
	s[4] = m_SelBuf.FREETEXT;
	s[4].Trim();	// damit keine Punkte am Ende des Feldes angezeigt werden, weil es länger ist als die Spalte
		
	*VecPtr = &m_SelBuf;
}

/*----------------------------------------------------------------------------*/
void CArtFreeTextBox::InitSuchBox(  )
{
	ListColumns ArtFreeText_Fields[] =
	{
		Article,        _strdup(CResString::ex().getStrTblText(IDS_ARTNR)),				100, LVCFMT_LEFT,  1, 
		Texttypeno,		_strdup(CResString::ex().getStrTblText(IDS_STRING1399)),		50, LVCFMT_RIGHT, 0, 
		Datefrom,		_strdup(CResString::ex().getStrTblText(IDS_DATEFROM)),			75, LVCFMT_RIGHT, 0, 
		Dateto,			_strdup(CResString::ex().getStrTblText(IDS_DATETO)),			75, LVCFMT_LEFT,  1, 
		Freetext,		_strdup(CResString::ex().getStrTblText(IDS_STRING74)),			480, LVCFMT_LEFT,  0, // must be left aligned
		-1        ,		"",																0,			   0, 0
	};

	InitBox( 15, ArtFreeText_Fields, sizeof( struct SelBuf )  );

	for (short ColNr = 0; ColNr < GetFieldCount(); ColNr++)
		free(ArtFreeText_Fields[ColNr].Columns);

	SetScrollMessage( FALSE );
	SetSelectBuffer( &m_SelBuf );
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextBox::PrimeKeyOfSelectedRecord( CARTFREETEXT * pSelArtFreeText )
{
	if ( !ItemChoise( FALSE ) )
		return -1;

	struct SelBuf *Info;
	Info = ( struct SelBuf *) GetSelectedVector();
		
/*	pSelArtFreeText->CUSTOMERNO			= Info->CUSTOMERNO;
	strcpy (pSelArtFreeText->ORDER_TYPE, Info->ORDER_TYPE); */
	strcpy (pSelArtFreeText->FREETEXT, Info->FREETEXT);

	return 0;
}

/*----------------------------------------------------------------------------*/
int CArtFreeTextBox::SelectedArtFreeText( CARTFREETEXT *pSelArtFreeText, CARTFREETEXTCODES *pSelArtFreeTextCodes)
{
	if ( !ItemChoise( FALSE ) )
	{
		if ( !ItemChoise( FALSE ) )
		{
			memset ( pSelArtFreeText, 0, sizeof( pSelArtFreeText) );
			return -1;
		}
	}

	struct SelBuf *Info;
	Info = ( struct SelBuf *) GetSelectedVector();

	strcpy ( pSelArtFreeTextCodes->ARTIKEL_CODE, Info->ARTIKEL_CODE_KEY );

	pSelArtFreeText->TEXTTYPENO		= Info->TEXTTYPENO;
	pSelArtFreeText->DATEFROM		= Info->DATEFROM;
	pSelArtFreeText->DATETO			= Info->DATETO;

	strcpy (pSelArtFreeText->FREETEXT, Info->FREETEXT);

	return 0;
}
