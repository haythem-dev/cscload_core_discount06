//////////////////////////////////////////////////////////////////
// RablistDoc.cpp  implementation file

#include "stdafx.h"
#include "ekzdp.h"
#include "AccDangerRouteDoc.h"

#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_bufd.h>

CAccDangerRouteDoc::CAccDangerRouteDoc()
{
}

CAccDangerRouteDoc::~CAccDangerRouteDoc()
{
}

void CAccDangerRouteDoc::InitPflegeDesc( char* Anwender )
{
	if (Anwender) {}

	m_Fd = -1;
/*	m_Fd_Zgrppflege = -1;

	m_tagesdatum = 0; */
}

struct CACCDANGERROUTE* CAccDangerRouteDoc::GetBuffer()
{
	return &m_Buf;
}

int CAccDangerRouteDoc::InitRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) 
		return -1;

	m_Buf.G_UN_NR[L_CACCDANGERROUTE_G_UN_NR] = '\0';
	m_Buf.VERPACKUNGSGRUPPE[L_CACCDANGERROUTE_VERPACKUNGSGRUPPE] = '\0';

    char unnr[L_CACCDANGERROUTE_G_UN_NR + 1];
    char vpgr[L_CACCDANGERROUTE_VERPACKUNGSGRUPPE + 1];

	strcpy( unnr, m_Buf.G_UN_NR );
	strcpy( vpgr, m_Buf.VERPACKUNGSGRUPPE );

	FdInitTabBuf( m_Fd, &m_Buf );

    strcpy( m_Buf.G_UN_NR, unnr );
    strcpy( m_Buf.VERPACKUNGSGRUPPE, vpgr );

	return 0;
}

void CAccDangerRouteDoc::SetPrimekeyCondition( )
{
	sprintf( m_PrimekeyCond, "G_UN_NR='%s' and VERPACKUNGSGRUPPE='%s'", 
			 m_Buf.G_UN_NR, m_Buf.VERPACKUNGSGRUPPE);
}

void CAccDangerRouteDoc::StoreBuffer()
{
    m_BufSave = m_Buf;
}

void CAccDangerRouteDoc::RestoreBuffer()
{
    strcpy (m_BufSave.G_UN_NR, m_Buf.G_UN_NR );
    strcpy (m_BufSave.VERPACKUNGSGRUPPE, m_Buf.VERPACKUNGSGRUPPE );

    m_Buf = m_BufSave;

    strcpy (m_Buf.G_UN_NR, m_BufSave.G_UN_NR );
    strcpy (m_Buf.VERPACKUNGSGRUPPE, m_BufSave.VERPACKUNGSGRUPPE );
}

int CAccDangerRouteDoc::GetBufferDesc( CString &cErrmld )
{
	char *tabelle = "caccdangerroute";
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

void CAccDangerRouteDoc::FreeBufferDesc( )
{
	if ( m_Fd >= 0 )
		CloseOneBufferDesc( m_Fd );
	m_Fd = -1;

/*	if ( m_Fd_Zgrppflege >= 0 )
		CloseOneBufferDesc( m_Fd_Zgrppflege );
	m_Fd_Zgrppflege = -1; */
}

long CAccDangerRouteDoc::ReadRecord( CString &cErrmld )
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

long CAccDangerRouteDoc::StoreRecord( CString &cErrmld )
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
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR).GetString() );
	}
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");

	// Ausgabe zgrppflege für Verteilung mittels tpulzentpfl 
/*	if (0 == lStatus)
		lStatus = StoreRecord_Zgrppflege( m_tagesdatum, cErrmld );  */

	return lStatus;
}

long CAccDangerRouteDoc::DeleteRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) 
		return -1;

	long lStatus;
	char errmld[200];

	SetPrimekeyCondition ( );
	lStatus = ::FdDeleteRecord( m_Fd, &m_BufOld, m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");

	// Ausgabe zgrppflege für Verteilung mittels tpulzentpfl 
/*	if (0 == lStatus)
		lStatus = StoreRecord_Zgrppflege( m_tagesdatum, cErrmld ) ; */

	return lStatus;
}

/*void CAccDangerRouteDoc::SetTagesdatum( long datum )
{
	m_tagesdatum = datum;
}

int CAccDangerRouteDoc::GetBufferDesc_Zgrppflege( CString &cErrmld )
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

long CAccDangerRouteDoc::StoreRecord_Zgrppflege( long datum, CString &cErrmld )
{
	long lStatus;

	char PrimekeyCond_Zgrppflege[100];
	char errmld[200];

	strcpy (m_ZgrppflegeBuf.KEY_GRUPPE, m_Buf.ORDER_TYPE);
	strcat (m_ZgrppflegeBuf.KEY_GRUPPE, m_Buf.SUB_ORDER_TYPE);
	m_ZgrppflegeBuf.DATUM		= datum;

	sprintf( PrimekeyCond_Zgrppflege, "KEY_GRUPPE='%s' and DATUM=%ld and DEZAP_SA = '29'",
									m_ZgrppflegeBuf.KEY_GRUPPE, m_ZgrppflegeBuf.DATUM );

    lStatus = ::FdReadRecord( m_Fd_Zgrppflege, PrimekeyCond_Zgrppflege,
				  			  &m_ZgrppflegeBuf, errmld );

	if ( lStatus == 100 )
	{
		strcpy (m_ZgrppflegeBuf.KEY_GRUPPE, m_Buf.ORDER_TYPE);
		strcat (m_ZgrppflegeBuf.KEY_GRUPPE, m_Buf.SUB_ORDER_TYPE);
		m_ZgrppflegeBuf.DATUM		= datum;
		strcpy (m_ZgrppflegeBuf.DEZAP_SA, "29");

		lStatus = ::FdInsertRecord( m_Fd_Zgrppflege, &m_ZgrppflegeBuf, 
										 PrimekeyCond_Zgrppflege, errmld );
	}

	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
} */
