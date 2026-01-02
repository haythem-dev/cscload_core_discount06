
//////////////////////////////////////////////////////////////////
// ArtnrblDoc.cpp  implementation file

#include "stdafx.h"

#include "ArtnrblDoc.h"

#include <wpp_prot.h>
#include <wpp_bufd.h>

#include "FeldBreite.h"

CArtnrblDoc::CArtnrblDoc()
{
}

CArtnrblDoc::~CArtnrblDoc()
{
}

void CArtnrblDoc::InitPflegeDesc( char* Anwender )
{
	m_Fd = -1;
}

struct ARTNRBL* CArtnrblDoc::GetBuffer()
{
	return &m_Buf;
}

int CArtnrblDoc::InitRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

    long artnr;
	long beslanr;
    beslanr =  m_Buf.BESLA_NR;
    artnr =  m_Buf.ARTIKEL_NR;
    FdInitTabBuf( m_Fd, &m_Buf );
    m_Buf.BESLA_NR = beslanr;
    m_Buf.ARTIKEL_NR = artnr;
	return 0;
}

void CArtnrblDoc::SetPrimekeyCondition( )
{
//	sprintf( m_PrimekeyCond, "BESLA_NR=%ld and ARTIKEL_NR=%ld", 
//			m_Buf.BESLA_NR, m_Buf.ARTIKEL_NR );

	char format[50];
	sprintf( format, "BESLA_NR=%c%d.ld and ARTIKEL_NR=%c%d.ld",
					 '%', L_BESLA_NR, 
		             '%', L_ARTIKEL_NR );
	sprintf( m_PrimekeyCond, format,
			 m_Buf.BESLA_NR,
			 m_Buf.ARTIKEL_NR );
}

void CArtnrblDoc::StoreBuffer()
{
    m_BufSave = m_Buf;
}

void CArtnrblDoc::RestoreBuffer()
{
    m_BufSave.BESLA_NR = m_Buf.BESLA_NR;
    m_BufSave.ARTIKEL_NR = m_Buf.ARTIKEL_NR;
    m_Buf = m_BufSave;
    m_Buf.BESLA_NR = m_BufSave.BESLA_NR;
    m_Buf.ARTIKEL_NR = m_BufSave.ARTIKEL_NR;  
}

int CArtnrblDoc::GetBufferDesc( CString &cErrmld  )
{
	char *tabelle = "artnrbl";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd >= 0 ) return 0;

	lStatus = OpenBufferDesc( &m_Fd, tabelle,
                              NULL, NULL, V_PROTO_VERTEIL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += "\ntable ";
		cErrmld += tabelle;
		m_Fd = -1;
		return -1;
	}
	return 0;
}

void CArtnrblDoc::FreeBufferDesc( )
{
	if ( m_Fd >= 0 )
		CloseOneBufferDesc( m_Fd );
	m_Fd = -1;
}

long CArtnrblDoc::ReadRecord( CString &cErrmld )
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

bool CArtnrblDoc::IsToDelete_Artnrbl( )
{
	char vgl_str[ L_ARTNRBL_ARTIKEL_NR_BLIEFER + 1 ];
	memset( vgl_str, ' ', L_ARTNRBL_ARTIKEL_NR_BLIEFER );
	vgl_str[ L_ARTNRBL_ARTIKEL_NR_BLIEFER ] = '\0';
	return  ( strcmp( m_Buf.ARTIKEL_NR_BLIEFER, vgl_str ) == 0 );
}

long CArtnrblDoc::StoreRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

	long lStatus;
	char errmld[200];

	SetPrimekeyCondition ( );
	if ( m_lStatus == 100 )
	{
		if ( !IsToDelete_Artnrbl() )
			lStatus = ::FdInsertRecord( m_Fd, &m_Buf, m_PrimekeyCond, errmld);
		else
			lStatus = 0;
	}
	else if ( m_lStatus == 0 )
	{
		if ( IsToDelete_Artnrbl() )
			lStatus = ::FdDeleteRecord( m_Fd, &m_BufOld,
										m_PrimekeyCond, errmld );
		else
			lStatus = ::FdUpdateRecord( m_Fd, &m_Buf, &m_BufOld,
										m_PrimekeyCond, errmld );
	}
	else
	{
		lStatus = m_lStatus;
		strcpy( errmld, "Interner Fehler" );
	}
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

long CArtnrblDoc::DeleteRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

	long lStatus;
	char errmld[200];

	SetPrimekeyCondition ( );
	lStatus = ::FdDeleteRecord( m_Fd, &m_BufOld, m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}



