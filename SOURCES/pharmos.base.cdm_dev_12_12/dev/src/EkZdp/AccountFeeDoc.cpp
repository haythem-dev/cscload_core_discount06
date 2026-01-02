//////////////////////////////////////////////////////////////////
// ArtnrblveDoc.cpp  implementation file

#include "stdafx.h"
#include "ekzdp.h"
#include "AccountFeeDoc.h"

#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_bufd.h>

#include "ServerDatum.h"

#include "FeldBreite.h"

CAccountFeeDoc::CAccountFeeDoc()
{
}

CAccountFeeDoc::~CAccountFeeDoc()
{
}

struct CACCOUNTFEE* CAccountFeeDoc::GetBuffer()
{
	return &m_Buf;
}

struct CACCOUNTFEE* CAccountFeeDoc::GetOldBuffer()
{
	return &m_BufOld;
}

void CAccountFeeDoc::InitPflegeDesc( char* Anwender )
{
	m_Anwender			= Anwender;
	m_Fd_AccountFee		= -1;
}

void CAccountFeeDoc::StoreBuffer()
{
    m_BufSave = m_Buf;
}

void CAccountFeeDoc::SetPrimekeyCondition( )
{
	sprintf( m_PrimekeyCond, "ACCOUNTTYPEID=%d and ACCOUNTUNITID=%d and ACCOUNTITEMSTYLEID=%d and MANUFACTURERNO=%d ",
							m_Buf.ACCOUNTTYPEID, m_Buf.ACCOUNTUNITID, m_Buf.ACCOUNTITEMSTYLEID, m_Buf.MANUFACTURERNO
		              ); 
}

void CAccountFeeDoc::FreeBufferDesc( )
{
	if ( m_Fd_AccountFee >= 0 )
		CloseOneBufferDesc( m_Fd_AccountFee );
	m_Fd_AccountFee = -1;
}

int CAccountFeeDoc::IsRecordModified( CString &cErrmld )
{
	char errmld[100];
	int s;
	s = ::FdIsRecordModified( m_Fd_AccountFee, &m_Buf, &m_BufOld, errmld );

	if ( s == 0 ) 
		return 0;
	
	cErrmld = errmld;
	return s;
}

void CAccountFeeDoc::RestoreBuffer()
{
//	hier dummy
}

int CAccountFeeDoc::GetBufferDesc( CString &cErrmld  )
{
	char *tabelle = "caccountfee";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	if ( m_Fd_AccountFee >= 0 ) 
		return 0;

	lStatus = ::OpenBufferDesc( &m_Fd_AccountFee, tabelle,
                                NULL, NULL, V_PROTO_VERTEIL, errmld );
	if ( lStatus != 0 )
	{
		cErrmld = errmld;
		cErrmld += CResString::ex().getStrTblText(IDS_TABLE);
		cErrmld += tabelle;
		m_Fd_AccountFee = -1;
		return -1;
	}
	return 0;
}


int CAccountFeeDoc::InitRecord( CString &cErrmld )
{
	if (cErrmld.GetLength()) {}

	short nr1, nr2, nr3;
	long nr4;
	nr1  = m_Buf.ACCOUNTTYPEID;
	nr2 = m_Buf.ACCOUNTUNITID;
	nr3 = m_Buf.ACCOUNTITEMSTYLEID;
	nr4 = m_Buf.MANUFACTURERNO;
    FdInitTabBuf( m_Fd_AccountFee, &m_Buf );
    m_Buf.ACCOUNTTYPEID = nr1;
    m_Buf.ACCOUNTUNITID = nr2;
	m_Buf.ACCOUNTITEMSTYLEID = nr3;
	m_Buf.MANUFACTURERNO = nr4;
	return 0;
}

long CAccountFeeDoc::ReadRecord( CString &cErrmld )
{
	long lStatus;
	char errmld[200];

	if ( GetBufferDesc( cErrmld ) != 0 ) 
		return -1;

	SetPrimekeyCondition ( );

	lStatus = ::FdReadRecord( m_Fd_AccountFee, m_PrimekeyCond, 
								&m_Buf, errmld );

	if ( !( lStatus == 0 || lStatus == 100 ) ) 
	{                                
		cErrmld = errmld;
	}

	if ( lStatus == 100 )
		InitRecord( cErrmld );

	m_lStatus = lStatus;

	m_BufOld = m_Buf;  // gelesenen Satz sichern: erst hier

	return m_lStatus;
}

long CAccountFeeDoc::StoreRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) 
		return -1;

	long lStatus = 0;
	char errmld[200];

	SetPrimekeyCondition ( );
	if ( m_lStatus == 100 )
	{
		lStatus = ::FdInsertRecord( m_Fd_AccountFee, &m_Buf, 
											 m_PrimekeyCond, errmld);
	}
	else if ( m_lStatus == 0 )
	{
		lStatus = ::FdUpdateRecord( m_Fd_AccountFee, &m_Buf,
								 			 &m_BufOld,
											 m_PrimekeyCond, errmld );
	}
	else
	{
		lStatus = m_lStatus;
		strcpy( errmld, CResString::ex().getStrTblText(IDS_INTER_ERR) );
	}	
	
	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}

long CAccountFeeDoc::DeleteRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) 
		return -1;
    	
	long lStatus;
	char errmld[200];
	
	if ( m_lStatus == 100 ) 
		return 0;

	SetPrimekeyCondition ( );
	lStatus = ::FdDeleteRecord( m_Fd_AccountFee, &m_BufOld, 
									 m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) 
		cErrmld = errmld; 
	else 
		cErrmld = _T("");

	return lStatus;
}
