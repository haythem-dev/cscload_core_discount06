
//////////////////////////////////////////////////////////////////
// ArtkatgDoc.cpp  implementation file

#include "stdafx.h"

#include "ArtkatgDoc.h"
#include "Ekzdp.h"

#include <libscsvoodoo/libscsvoodoo.h>

#include <eklibs/wdbups/wpp_prot.h>
#include <eklibs/wdbups/wpp_bufd.h>

CArtkatgDoc::CArtkatgDoc()
{
}

CArtkatgDoc::~CArtkatgDoc()
{
}

void CArtkatgDoc::InitPflegeDesc( char* )
{
	m_Fd = -1;
	m_Fd_Zgrppflege = -1;

	m_tagesdatum = 0;

}

struct ARTKATG* CArtkatgDoc::GetBuffer()
{
	return &m_Buf;
}

int CArtkatgDoc::InitRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

    char nr[L_ARTKATG_WARENGRUPPE + 1];
    strcpy( nr, m_Buf.WARENGRUPPE );
    FdInitTabBuf( m_Fd, &m_Buf );
    strcpy( m_Buf.WARENGRUPPE, nr );

	return 0;
}

void CArtkatgDoc::SetPrimekeyCondition ( )
{
    strcpy( m_PrimekeyCond, "WARENGRUPPE='");
    strcat( m_PrimekeyCond, m_Buf.WARENGRUPPE );
    strcat( m_PrimekeyCond, "'");
}

void CArtkatgDoc::StoreBuffer()
{
    m_BufSave = m_Buf;
}

void CArtkatgDoc::RestoreBuffer()
{
    strcpy (m_BufSave.WARENGRUPPE, m_Buf.WARENGRUPPE );
    m_Buf = m_BufSave;
    strcpy (m_Buf.WARENGRUPPE    , m_BufSave.WARENGRUPPE );
}

int CArtkatgDoc::GetBufferDesc( CString &cErrmld )
{
	char *tabelle = "artkatg";
	long lStatus;
	char errmld[100];

	cErrmld = _T("");
	
	GetBufferDesc_Zgrppflege( cErrmld )  ;

	if ( m_Fd >= 0 ) return 0;

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

void CArtkatgDoc::FreeBufferDesc( )
{
	if ( m_Fd >= 0 )
		CloseOneBufferDesc( m_Fd );
	m_Fd = -1;

	if ( m_Fd_Zgrppflege >= 0 )
		CloseOneBufferDesc( m_Fd_Zgrppflege );
	m_Fd_Zgrppflege = -1;



}

long CArtkatgDoc::ReadRecord( CString &cErrmld )
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

long CArtkatgDoc::StoreRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

	long lStatus;
	char errmld[200];
	CString str;
	m_Buf.BEZEICHNUNG[50] = '\0';
	str.Format("%s",m_Buf.BEZEICHNUNG);
	str.TrimRight();
	strcpy(m_Buf.BEZEICHNUNG,str);

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
	if (0 == lStatus)
		lStatus = StoreRecord_Zgrppflege( m_tagesdatum, cErrmld ) ;

	return lStatus;
}

long CArtkatgDoc::DeleteRecord( CString &cErrmld )
{
	if ( GetBufferDesc( cErrmld ) != 0 ) return -1;

	long lStatus;
	char errmld[200];

	SetPrimekeyCondition ( );
	lStatus = ::FdDeleteRecord( m_Fd, &m_BufOld, m_PrimekeyCond, errmld );
	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");

	// Ausgabe zgrppflege für Verteilung mittels tpulzentpfl 
	if (0 == lStatus)
		lStatus = StoreRecord_Zgrppflege( m_tagesdatum, cErrmld ) ;

	return lStatus;
}

long CArtkatgDoc::CheckDelete( )
{ 
	CString sql, cErrmld;
	long s;
	double dCount;

	// 10.03.05 RR: erstmal prüfen, ob noch Artikel auf diese Gruppe verschlüsselt
	sql.Format( "select count(*) from zartwg where art = '1' and warengruppe = '%s'", m_Buf.WARENGRUPPE );

	((CEkZdpApp*) AfxGetApp())->BeginWaitAction();
	s = SqlRead(sql, &dCount, NULL);
	((CEkZdpApp*) AfxGetApp())->EndWaitAction();

	if (s != 0)
	{
		cErrmld = CResString::ex().getStrTblText(IDS_STRING38);
		cErrmld += DynErrmld();
		MsgBoxOK( cErrmld );
		return -1;
	}

	if ( dCount != 0.0 )
	{
		sql.Format(CResString::ex().getStrTblText(IDS_STRING39), dCount);
		if (MsgBoxYesNo( sql ) != IDYES)
			return -1;
	}

	return 0;
}

void CArtkatgDoc::SetTagesdatum( long datum )
{
	m_tagesdatum = datum;
}

int CArtkatgDoc::GetBufferDesc_Zgrppflege( CString &cErrmld )
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

long CArtkatgDoc::StoreRecord_Zgrppflege( long datum, CString &cErrmld )
{
	long lStatus;

	char PrimekeyCond_Zgrppflege[100];
	char errmld[200];


	strcpy (m_ZgrppflegeBuf.KEY_GRUPPE, m_Buf.WARENGRUPPE);
	m_ZgrppflegeBuf.DATUM		= datum;

	sprintf( PrimekeyCond_Zgrppflege, "KEY_GRUPPE='%s' and DATUM=%ld and DEZAP_SA = '16'",
									m_ZgrppflegeBuf.KEY_GRUPPE, m_ZgrppflegeBuf.DATUM );

    lStatus = ::FdReadRecord( m_Fd_Zgrppflege, PrimekeyCond_Zgrppflege,
				  			  &m_ZgrppflegeBuf, errmld );

	if ( lStatus == 100 )
	{
		strcpy (m_ZgrppflegeBuf.KEY_GRUPPE, m_Buf.WARENGRUPPE);
		m_ZgrppflegeBuf.DATUM		= datum;
		strcpy (m_ZgrppflegeBuf.DEZAP_SA, "16");

		lStatus = ::FdInsertRecord( m_Fd_Zgrppflege, &m_ZgrppflegeBuf, 
										 PrimekeyCond_Zgrppflege, errmld );
	}

	if ( lStatus != 0 ) cErrmld = errmld; else cErrmld = _T("");
	return lStatus;
}

bool CArtkatgDoc::WasChangedRabgrp( )
{ 
	if (strcmp (m_Buf.RABATTGRUPPE, m_BufOld.RABATTGRUPPE) != 0)
	{
		return true;
	}

	return false;
}
