/******************************************************************************/
/**                                                                           */
/**   Author : NTT Data										            	  */
/**   Date   : 20.11.2022                                                     */
/**                                                                           */
/******************************************************************************/
#include "stdafx.h"

#include "ArticleSubseqDeliveryDoc.h"

#include "Ekzdp.h"

#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_bufd.h>
#include "FeldBreite.h"

/*----------------------------------------------------------------------------*/
CArticleSubseqDeliveryDoc::CArticleSubseqDeliveryDoc()
{
}

/*----------------------------------------------------------------------------*/
CArticleSubseqDeliveryDoc::~CArticleSubseqDeliveryDoc()
{
}

/*----------------------------------------------------------------------------*/
struct CSUBSEQDELIVERIES* CArticleSubseqDeliveryDoc::GetBuffer()
{
	return &m_Buf;
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryDoc::SetPrimekeyCondition_ArtCode ( )
{
	sprintf( m_PrimekeyCond, "ARTICLENO=%ld and branchno=%d ", 
		m_Buf.lArtikelnr, m_Buf.iFilialnr);
}

/*----------------------------------------------------------------------------*/
int CArticleSubseqDeliveryDoc::GetBufferDesc_ArtCode( CString &cErrmld )
{
	char *tabelle = "carticlecodes";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

	if ( m_Fd_ArtCode >= 0 )
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_ArtCode, tabelle,
                                NULL, NULL, V_PROTO_VERTEIL, errmld ); 

	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_ArtCode = -1;
		return -1;
	}
	return 0;
}

/*----------------------------------------------------------------------------*/
int CArticleSubseqDeliveryDoc::GetBufferDesc_Zpznpflege( CString &cErrmld )
{
	char *tabelle = "zpznpflege";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

	if ( m_Fd_Zpznpflege >= 0 ) 
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Zpznpflege, tabelle,
                                NULL, NULL, V_OHNE, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zpznpflege = -1;
		return -1;
	}
	return 0;
}


/*----------------------------------------------------------------------------*/
long CArticleSubseqDeliveryDoc::StoreRecord_ArtCode( CString &cErrmld, const bool resetPreviousPreferred )
{
	long lStatus = 0;
// 	char errmld[200];

	struct CSUBSEQDELIVERIES BufTemp = m_Buf;

	if (resetPreviousPreferred == true)
	{
		lStatus = ReadRecord( cErrmld, resetPreviousPreferred );

		if ( lStatus == 0 )
		{
			SetPrimekeyCondition_ArtCode();
			strcpy(m_Buf.szSubseqDelFlag, "");

//			m_Buf.DATE_CHANGED = m_tagesdatum;

// 			lStatus = ::FdDelayUpdateRecord( m_Fd_ArtCode, &m_Buf, &m_BufOld, 
// 											m_PrimekeyCond, errmld);
// 
// 			if ( lStatus != 0 ) 
// 				cErrmld = errmld; 
// 			else 
// 				cErrmld = _T("");
		}
	}

	if (lStatus != 0)
		return lStatus;

	m_Buf = BufTemp;

	ReadRecord( cErrmld );

	m_Buf = BufTemp;

// 	m_Buf.DATE_CHANGED = m_tagesdatum;
// 
// 	if ( m_lStatus_ArtCode == 100 )
// 	{
// 		lStatus = ::FdDelayInsertRecord( m_Fd_ArtCode, &m_Buf, 
// 										 m_PrimekeyCond, errmld);
// 
// 		if ( lStatus != 0 ) 
// 			cErrmld = errmld; 
// 		else 
// 			cErrmld = _T("");
// 	}
// 	else if ( m_lStatus_ArtCode == 0 )
// 	{
// 		lStatus = ::FdDelayUpdateRecord( m_Fd_ArtCode, &m_Buf, &m_BufOld, 
// 										 m_PrimekeyCond, errmld);
// 
// 		if ( lStatus != 0 ) 
// 			cErrmld = errmld; 
// 		else 
// 			cErrmld = _T("");
// 	}
// 	else
// 	{
// 		lStatus = m_lStatus_ArtCode;
// 	}
	
	return lStatus;
}


/*----------------------------------------------------------------------------*/
long CArticleSubseqDeliveryDoc::DeleteRecord_ArtCode( CString &/*cErrmld*/ )
{
	long lStatus = 0;
// 	char errmld[200];
// 
// 	ReadRecord( cErrmld );
// 
// 	if ( m_lStatus_ArtCode == 100 ) 
// 		return 0;
// 
// 	lStatus = ::FdDelayDeleteRecord( m_Fd_ArtCode, &m_Buf, 
// 									 m_PrimekeyCond, errmld );
// 	
// 	if ( lStatus != 0 )
// 		cErrmld = errmld; 
// 	else 
// 		cErrmld = _T("");

	return lStatus;
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryDoc::InitPflegeDesc( char* Anwender )
{
	m_Anwender = Anwender;
	
	m_Fd_ArtCode  = -1;
	m_Fd_Zpznpflege = -1;
	
	m_tagesdatum = 0;
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryDoc::FreeBufferDesc( )
{
	if ( m_Fd_ArtCode >= 0 )
		CloseOneBufferDesc( m_Fd_ArtCode );
	m_Fd_ArtCode = -1;

	if ( m_Fd_Zpznpflege >= 0 )
		CloseOneBufferDesc( m_Fd_Zpznpflege );
	m_Fd_Zpznpflege = -1;
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryDoc::StoreBuffer()
{
//	hier dummy
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryDoc::RestoreBuffer()
{
//	hier dummy
}

/*----------------------------------------------------------------------------*/
int CArticleSubseqDeliveryDoc::GetBufferDesc( CString &cErrmld )
{
   	if ( GetBufferDesc_ArtCode( cErrmld ) != 0 ) 
	   return -1;

   	if ( GetBufferDesc_Zpznpflege( cErrmld ) != 0 ) 
		return -1;
	
   return 0;
}

/*----------------------------------------------------------------------------*/
int CArticleSubseqDeliveryDoc::InitRecord  ( CString& cErrmld )
{
	if (cErrmld.GetLength()){}
	return 0;
}

/*----------------------------------------------------------------------------*/
long CArticleSubseqDeliveryDoc::ReadRecord( CString &/*cErrmld*/, const bool /*resetPreviousPreferred*/ )
{
	long lStatus = 0;
// 	char errmld[200];

// 	if (resetPreviousPreferred == false)
// 		SetPrimekeyCondition_ArtCode ( );
// 	else
// 	{
// 		sprintf( m_PrimekeyCond, "ARTICLENO=%ld and PREFERRED_FLAG=1", 
// 					m_Buf.ARTICLENO );
// 	}
// 
//     lStatus = ::FdReadRecord( m_Fd_ArtCode, m_PrimekeyCond, 
// 								&m_Buf, errmld );
// 		
// 	if ( !( lStatus == 0 || lStatus == 100 ) )
// 	{                                
// 		cErrmld = errmld;
// 	}
// 	m_lStatus_ArtCode = lStatus;
// 
// 	m_BufOld = m_Buf;

	return lStatus;
}

/*----------------------------------------------------------------------------*/
long CArticleSubseqDeliveryDoc::StoreRecord( CString &/*cErrmld*/, const bool /*resetPreviousPreferred*/ )
{
	return -1;

// 	if ( GetBufferDesc( cErrmld ) != 0 )  
// 		return -1;
// 
// 	if ( StoreRecord_ArtCode( cErrmld, resetPreviousPreferred ) != 0 ) 
// 		return -1;
//  
// 	char errmld[200];
// 	if ( FdTransact( errmld ) != 0 ) 
// 	{
// 		cErrmld = errmld;
// 		return -1;
// 	}
// 	else
// 	{
// 		// Ausgabe zpznpflege für Verteilung mittels tpulzentpfl 
// 		return StoreRecord_Zpznpflege( m_tagesdatum, cErrmld );
// 	}
}

/*----------------------------------------------------------------------------*/
long CArticleSubseqDeliveryDoc::DeleteRecord( CString &/*cErrmld*/ )
{
	return -1;
// 	if ( GetBufferDesc( cErrmld ) != 0 ) 
// 		return -1;
// 
//     if ( DeleteRecord_ArtCode( cErrmld ) != 0 ) 
// 		return -1;
//     
// 	char errmld[200];
// 	if ( FdTransact( errmld ) != 0 ) 
// 	{
// 		cErrmld = errmld;
// 		return -1;
// 	}
// 	else
// 	{
// 		// Ausgabe zpznpflege für Verteilung mittels tpulzentpfl 
// 		return StoreRecord_Zpznpflege( m_tagesdatum, cErrmld );
// 	}
}

/*----------------------------------------------------------------------------*/
void CArticleSubseqDeliveryDoc::SetTagesdatum( long datum )
{
	m_tagesdatum = datum;
}

/*----------------------------------------------------------------------------*/
long CArticleSubseqDeliveryDoc::StoreRecord_Zpznpflege( long /*datum*/, CString &/*cErrmld*/ )
{
	long lStatus = 0;

// 	char PrimekeyCond_Zpznpflege[100];
// 	char errmld[200];
// 
// 	m_ZpznpflegeBuf.ARTIKEL_NR = m_Buf.ARTICLENO;
// 	m_ZpznpflegeBuf.DATUM		= datum;
// 
// 	sprintf( PrimekeyCond_Zpznpflege, "ARTIKEL_NR=%ld and DATUM=%ld and DEZAP_SA = '34'", 
// 									m_ZpznpflegeBuf.ARTIKEL_NR, m_ZpznpflegeBuf.DATUM );
// 
//     lStatus = ::FdReadRecord( m_Fd_Zpznpflege, PrimekeyCond_Zpznpflege,
// 				  			  &m_ZpznpflegeBuf, errmld );
// 
// 	if ( lStatus == 100 )
// 	{
// 		m_ZpznpflegeBuf.ARTIKEL_NR = m_Buf.ARTICLENO;
// 		m_ZpznpflegeBuf.DATUM		= datum;
// 		strcpy (m_ZpznpflegeBuf.DEZAP_SA, "34"); 
// 
// 		lStatus = ::FdInsertRecord( m_Fd_Zpznpflege, &m_ZpznpflegeBuf, 
// 										 PrimekeyCond_Zpznpflege, errmld );
// 	}
// 
// 	if ( lStatus != 0 ) 
// 		cErrmld = errmld;
// 	else 
// 		cErrmld = _T("");

	return lStatus;
}

/*----------------------------------------------------------------------------*/
short CArticleSubseqDeliveryDoc::ReadCodeTypeLength(const short /*codeType*/)
{
	short codeLength = 0;
// 
// 	CString sql;
// 		
// 	sql.Format( "select CODE_LENGTH from CCODETYPES where CODE_TYPE = %d", codeType );
// 
// 	SqlRead(sql, &codeLength, NULL);
	
	return codeLength;
}

/*----------------------------------------------------------------------------*/
short CArticleSubseqDeliveryDoc::ReadCodeTypeMaxNumber(const short /*codeType*/)
{
	short maxNum = 0;
// 
// 	CString sql;
// 		
// 	sql.Format( "select MAX_NUMBER from CCODETYPES where CODE_TYPE = %d", codeType );
// 
// 	SqlRead(sql, &maxNum, NULL);
	
	return maxNum;
}
