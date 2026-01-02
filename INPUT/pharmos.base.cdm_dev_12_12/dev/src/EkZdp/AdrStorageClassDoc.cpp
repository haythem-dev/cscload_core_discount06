//////////////////////////////////////////////////////////////////
// AdrStorageClassDoc.cpp  implementation file

#include "stdafx.h"
#include "ekzdp.h"
#include "AdrStorageClassDoc.h"

#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_bufd.h>

CAdrStorageClassDoc::CAdrStorageClassDoc()
{
}

CAdrStorageClassDoc::~CAdrStorageClassDoc()
{
}

void CAdrStorageClassDoc::InitPflegeDesc( char* Anwender )
{
	if (Anwender) {}
	m_Fd = -1;
/*	m_Fd_Zgrppflege = -1;

	m_tagesdatum = 0; */
}

struct CADRSTORAGECLASS* CAdrStorageClassDoc::GetBuffer()
{
	return &m_Buf;
}

int CAdrStorageClassDoc::InitRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) 
		return -1;

	m_Buf.GG_KLASSE[L_CADRSTORAGECLASS_GG_KLASSE] = '\0';
	m_Buf.G_UN_NR[L_CADRSTORAGECLASS_G_UN_NR] = '\0';
	m_Buf.VERPACKUNGSGRUPPE[L_CADRSTORAGECLASS_VERPACKUNGSGRUPPE] = '\0';

	char klasse[L_CADRSTORAGECLASS_GG_KLASSE + 1];
    char unnr[L_CADRSTORAGECLASS_G_UN_NR + 1];
    char vpgr[L_CADRSTORAGECLASS_VERPACKUNGSGRUPPE + 1];

	strcpy( klasse, m_Buf.GG_KLASSE );
	strcpy( unnr, m_Buf.G_UN_NR );
	strcpy( vpgr, m_Buf.VERPACKUNGSGRUPPE );

	FdInitTabBuf( m_Fd, &m_Buf );

	strcpy( m_Buf.GG_KLASSE, klasse ); 
    strcpy( m_Buf.G_UN_NR, unnr );
    strcpy( m_Buf.VERPACKUNGSGRUPPE, vpgr );

	return 0;
}

void CAdrStorageClassDoc::SetPrimekeyCondition( )
{
	sprintf( m_PrimekeyCond, "GG_KLASSE='%s' and G_UN_NR='%s' and VERPACKUNGSGRUPPE='%s'", 
			 m_Buf.GG_KLASSE, m_Buf.G_UN_NR, m_Buf.VERPACKUNGSGRUPPE);
}

void CAdrStorageClassDoc::StoreBuffer()
{
    m_BufSave = m_Buf;
}

void CAdrStorageClassDoc::RestoreBuffer()
{
	strcpy (m_BufSave.GG_KLASSE, m_Buf.GG_KLASSE );
    strcpy (m_BufSave.G_UN_NR, m_Buf.G_UN_NR );
    strcpy (m_BufSave.VERPACKUNGSGRUPPE, m_Buf.VERPACKUNGSGRUPPE );

    m_Buf = m_BufSave;

	strcpy (m_Buf.GG_KLASSE, m_BufSave.GG_KLASSE );
    strcpy (m_Buf.G_UN_NR, m_BufSave.G_UN_NR );
    strcpy (m_Buf.VERPACKUNGSGRUPPE, m_BufSave.VERPACKUNGSGRUPPE );
}

int CAdrStorageClassDoc::GetBufferDesc( CString &cErrmld )
{
	char *tabelle = "cadrstorageclass";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");

//	GetBufferDesc_Zgrppflege( cErrmld )  ;

	if ( m_Fd >= 0 ) 
		return 0;

	lStatus = OpenBufferDesc( &m_Fd, tabelle,
                              NULL, NULL, V_PROTO_VERTEIL, errmld );

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

void CAdrStorageClassDoc::FreeBufferDesc( )
{
	if ( m_Fd >= 0 )
		CloseOneBufferDesc( m_Fd );
	m_Fd = -1;

/*	if ( m_Fd_Zgrppflege >= 0 )
		CloseOneBufferDesc( m_Fd_Zgrppflege );
	m_Fd_Zgrppflege = -1; */
}

long CAdrStorageClassDoc::ReadRecord( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if ( GetBufferDesc( cErrmld ) != 0 ) 
		return -1;

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

long CAdrStorageClassDoc::StoreRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) 
		return -1;

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

	return lStatus;
}

long CAdrStorageClassDoc::DeleteRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) 
		return -1;

	long lStatus;
	char errmld[200];

	SetPrimekeyCondition ( );
	lStatus = ::FdDeleteRecord( m_Fd, &m_BufOld, m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");

	return lStatus;
}
