// GetRegion.cpp : implementation file
//

#include "stdafx.h"

#include "GetRegion.h"

#include <libscsvoodoo/libscsvoodoo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SqlGetFiliale


CGetRegion::CGetRegion(  bool bIsStandardEngine )
{
	m_Fd = -1;
	m_cErrMeld  = "";
	m_nSqlCode  = 0;
	m_nIsamCode = 0;
	m_nNumberOfRegiones = 0;
	m_nCurrentRegionIndex = 0;

	m_bIsStandardEngine = bIsStandardEngine;

	m_bImmerNeulesen    = false;
}

CGetRegion::~CGetRegion()
{
	m_cRegionNames.RemoveAll();
	m_wRegionNr.RemoveAll();
}

long CGetRegion::OpenCs( )
{
	long s;
	CString sql;
//	if ( m_bIsStandardEngine )
		sql = "select REGION,REGIONAME from REGION where region != 99" \
			  "order by REGION";
//	else
//		sql = "select REGION,REGIONAME from regioek:REGION " \
//			  "order by REGION";

	s = SqlOpenCs( &m_Fd, sql );
	if ( s != 0 ) 
		m_cErrMeld = DynErrmld();
	else
		m_cErrMeld = "";
	m_nSqlCode = s;
	m_nIsamCode = SqlIsamCode();
	m_nNumberOfRegiones = 0;
	m_nCurrentRegionIndex = 0;
	return s;
}

long CGetRegion::Fetch()
{
	long s;
	short nr;
	char  name[30];
	CString str;

	s = SqlFetch( m_Fd, 1, &nr, name, NULL );
	if ( s == 0 )
	{
		m_cErrMeld = "";
//		str = "Region ";
//		str += name;
		str = name;
		m_cRegionNames.Add( str );
		m_wRegionNr.Add( nr );
		m_nNumberOfRegiones++;
	}
	else
		m_cErrMeld = DynErrmld();
	m_nSqlCode  = s;
	m_nIsamCode = SqlIsamCode();
	return s;
}

void CGetRegion::CloseCs()
{
	if ( m_Fd != -1 )
		SqlCloseCs( m_Fd );
	m_Fd = -1;
}


long CGetRegion::ReadRegiones( CString& cErrmld )
{
	long s;
	m_cRegionNames.RemoveAll();
	m_wRegionNr.RemoveAll();
	s = OpenCs();
	while ( s == 0 )
		s = Fetch();
	CloseCs(); 
	cErrmld = m_cErrMeld;
	if ( s == 100 && m_nNumberOfRegiones > 0 )
		return 0;
	return s;
}


void CGetRegion::MakeGrossKlein( CString & cStr )
{
	int i;
	cStr.MakeLower();
	if ( !cStr.IsEmpty() ) 
	{
		i = 0;
		do
		{
			cStr.SetAt( i, toupper( cStr.GetAt(i) ) );
			while ( i < cStr.GetLength() && cStr.GetAt(i) != ' ' ) i++;
			while ( i < cStr.GetLength() && cStr.GetAt(i) == ' ' ) i++;
		}	while ( i < cStr.GetLength() );
	}
}

CString CGetRegion::MakeRegionName( CString Name )
{
	return "Region " + Name;
}


long CGetRegion::FirstRegion( CString& StandOrt, CString& cErrmld )
{
	StandOrt = "";
	m_nHelpIndex = 0;
   if ( m_bImmerNeulesen || m_nNumberOfRegiones == 0 )
		ReadRegiones( cErrmld );	// immer neu Lesen 
	if ( m_nSqlCode == 100 && m_nNumberOfRegiones > 0 )
	{
		StandOrt = MakeRegionName( m_cRegionNames.GetAt( m_nHelpIndex++ ) );
		MakeGrossKlein( StandOrt );
		return 0;
	}
	return m_nSqlCode;
	
}

long CGetRegion::NextRegion( CString& StandOrt )
{
	if ( m_nHelpIndex < m_nNumberOfRegiones )
	{
		StandOrt = MakeRegionName( m_cRegionNames.GetAt( m_nHelpIndex++ ) );
		MakeGrossKlein( StandOrt );
		return 0;
	}
	StandOrt = "";
	return 100;
}

CString CGetRegion::GetCurrentRegionName( bool mode )
{
	CString Filiale;
	if ( m_nNumberOfRegiones == 0 )
		return "";
	else
	{ 
		Filiale = MakeRegionName( m_cRegionNames.GetAt( m_nCurrentRegionIndex ) );
		if ( !mode )
			MakeGrossKlein( Filiale );
		return Filiale;
	}
}

void CGetRegion::SetCurrentRegion( int index )
{
	if ( index < m_nNumberOfRegiones )
		m_nCurrentRegionIndex = index;
}


int CGetRegion::SetCurrentRegionViaNr( short nr )
{
	int index;
	index = 0;
	while ( index < m_nNumberOfRegiones )
	{
		if ( nr == m_wRegionNr[ index ] ) 
		{
			m_nCurrentRegionIndex = index;
			return index;
		}
		index++;
	}
	return -1;		
}

short CGetRegion::GetCurrentRegionNumber( )
{
	if ( m_nCurrentRegionIndex < m_nNumberOfRegiones ) 
		return m_wRegionNr[ m_nCurrentRegionIndex ];
	else
		return -1;
}


bool CGetRegion::GetRegionName( CString& Name, short region, bool mode, bool solo )
{
	int index;
	index = 0;
	while ( index < m_nNumberOfRegiones )
	{
		if ( region == m_wRegionNr[ index ] ) 
		{
			Name = MakeRegionName( m_cRegionNames.GetAt( index ) );
			if ( !mode )
				MakeGrossKlein( Name );
			if ( solo )
			{			
				index = Name.Find( ' ' );
				if ( index >= 0 && Name.GetLength() > 2 ) 
					Name = Name.Mid( index + 1 );
			}
			return true;
		}
		index++;
	}
	Name = _T("????");
	return false;
}


int CGetRegion::GetNumberOfRegiones()
{
	return m_nNumberOfRegiones;
}

int CGetRegion::GetInfoOfRegiones( int index, short &region, CString& Name )
{
	if ( index >= 0 && index < m_nNumberOfRegiones )
	{
		region = m_wRegionNr[ index ];
		Name   = m_cRegionNames.GetAt( index );
		MakeGrossKlein( Name );
		return 0;
	}
	return -1;
}