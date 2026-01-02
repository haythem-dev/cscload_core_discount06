//////////////////////////////////////////////////////////////////
// ArticleCategoryDoc.cpp  implementation file

#include "stdafx.h"

#include "ArticleCategoryDoc.h"

#include "Ekzdp.h"

#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_bufd.h>

CArticleCategoryDoc::CArticleCategoryDoc()
{
}

CArticleCategoryDoc::~CArticleCategoryDoc()
{
}

void CArticleCategoryDoc::InitPflegeDesc( char* Anwender )
{
	if (Anwender){}
	m_Fd = -1;

	m_Fd_Zgrppflege = -1;

	m_tagesdatum = 0;
}

struct CARTICLECATEGORY* CArticleCategoryDoc::GetBuffer()
{
	return &m_Buf;
}

int CArticleCategoryDoc::InitRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

    long nr;
    nr = m_Buf.ARTCATEGORYNO;
	FdInitTabBuf( m_Fd, &m_Buf );
    m_Buf.ARTCATEGORYNO = nr;

	return 0;
}

void CArticleCategoryDoc::SetPrimekeyCondition( )
{ 
    sprintf ( m_PrimekeyCond, "ARTCATEGORYNO=%ld", m_Buf.ARTCATEGORYNO );
}

void CArticleCategoryDoc::StoreBuffer()
{
    m_BufSave = m_Buf;
}

void CArticleCategoryDoc::RestoreBuffer()
{
    m_BufSave.ARTCATEGORYNO = m_Buf.ARTCATEGORYNO;
    m_Buf = m_BufSave;
    m_Buf.ARTCATEGORYNO = m_BufSave.ARTCATEGORYNO;
}

int CArticleCategoryDoc::GetBufferDesc( CString &cErrmld  )
{
	if ( GetBufferDesc_Zgrppflege( cErrmld ) != 0 ) 
		return -1;
	
	if ( GetBufferDesc_Carticlecategory( cErrmld ) != 0 ) 
		return -1;

	return 0;
}

int CArticleCategoryDoc::GetBufferDesc_Carticlecategory( CString &cErrmld  )
{
	char *tabelle = "carticlecategory";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd >= 0 ) return 0;

	lStatus = OpenBufferDesc( &m_Fd, tabelle,
                              NULL, NULL, V_PROTOKOL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd = -1;
		return -1;
	}
	return 0;
}

int CArticleCategoryDoc::GetBufferDesc_Zgrppflege( CString &cErrmld )
{
	char *tabelle = "zgrppflege";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_Zgrppflege >= 0 ) return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_Zgrppflege, tabelle,
                                NULL, NULL, V_OHNE, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_Zgrppflege = -1;
		return -1;
	}
	return 0;
}

void CArticleCategoryDoc::FreeBufferDesc( )
{
	if ( m_Fd >= 0 )
		CloseOneBufferDesc( m_Fd );
	m_Fd = -1;

	if ( m_Fd_Zgrppflege >= 0 )
		CloseOneBufferDesc( m_Fd_Zgrppflege );
	m_Fd_Zgrppflege = -1;
}

long CArticleCategoryDoc::ReadRecord( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

	SetPrimekeyCondition ( );
    lStatus = ::FdReadRecord( m_Fd, m_PrimekeyCond, &m_Buf, errmld );
	if ( lStatus == 0 )
	{
		m_BufOld = m_Buf;  // gelesenen Satz sichern
		cErrmld = _T("");
	}
	else if ( lStatus == 100 )
	{
		if ( InitRecord( cErrmld ) == 0 )
			m_BufOld = m_Buf;	// initialisierten Satz sichern
		else
			lStatus = -1;
	}
	else
		cErrmld = errmld;

	m_lStatus = lStatus;
	return lStatus;
}

long CArticleCategoryDoc::StoreRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

	long lStatus;
	char errmld[200];

	SetPrimekeyCondition ( );
	if ( m_lStatus == 100 )
		lStatus = ::FdInsertRecord( m_Fd, &m_Buf, m_PrimekeyCond, errmld);
	else if ( m_lStatus == 0 )
		lStatus = ::FdUpdateRecord( m_Fd, &m_Buf, &m_BufOld, m_PrimekeyCond, errmld );
	else
	{
		lStatus = m_lStatus;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");

	// Ausgabe zgrppflege für Verteilung mittels tpulzentpfl 
	/* if (0 == lStatus)
	  lStatus = StoreRecord_Zgrppflege( m_tagesdatum, cErrmld ); */

	return lStatus;
}

long CArticleCategoryDoc::DeleteRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

	long lStatus;
	char errmld[200];

	SetPrimekeyCondition ( );
	lStatus = ::FdDeleteRecord( m_Fd, &m_BufOld, m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	
	// Ausgabe zgrppflege für Verteilung mittels tpulzentpfl 
	/* if (0 == lStatus)
		lStatus = StoreRecord_Zgrppflege( m_tagesdatum, cErrmld ) ; */

	return lStatus;
}

void CArticleCategoryDoc::SetTagesdatum( long datum )
{
	m_tagesdatum = datum;
}

long CArticleCategoryDoc::StoreRecord_Zgrppflege( long datum, CString &cErrmld )
{
	long lStatus;

	char PrimekeyCond_Zgrppflege[100];
	char errmld[200];

	sprintf (m_ZgrppflegeBuf.KEY_GRUPPE, "%3.3d", m_Buf.ARTCATEGORYNO);
	m_ZgrppflegeBuf.DATUM		= datum;

	sprintf( PrimekeyCond_Zgrppflege, "KEY_GRUPPE='%s' and DATUM=%ld and DEZAP_SA = '??'",
									m_ZgrppflegeBuf.KEY_GRUPPE, m_ZgrppflegeBuf.DATUM );

    lStatus = ::FdReadRecord( m_Fd_Zgrppflege, PrimekeyCond_Zgrppflege,
				  			  &m_ZgrppflegeBuf, errmld );

	if ( lStatus == 100 )
	{
		sprintf (m_ZgrppflegeBuf.KEY_GRUPPE, "%3.3d", m_Buf.ARTCATEGORYNO);
		m_ZgrppflegeBuf.DATUM		= datum;
		strcpy (m_ZgrppflegeBuf.DEZAP_SA, "??");

		lStatus = ::FdInsertRecord( m_Fd_Zgrppflege, &m_ZgrppflegeBuf, 
										 PrimekeyCond_Zgrppflege, errmld );
	}

	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}
