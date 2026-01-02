// SqlGetFiliale.cpp : implementation file
//

#include "stdafx.h"

#include "GetBranches.h"

// #include <wudu.h>
#include <libscsvoodoo/libscsvoodoo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SqlGetFiliale


CGetBranches::CGetBranches()
{
	m_Fd = -1;
	m_cErrMeld  = "";
	m_nSqlCode  = 0;
	m_nIsamCode = 0;
	m_nNumberOfBranches = 0;
	m_nCurrentBranchIndex = 0;
}

CGetBranches::~CGetBranches()
{
	m_cStandortLang.RemoveAll();
	m_wFilialNr.RemoveAll();
}

long CGetBranches::OpenCs()
{
	long s;
	CString sql;
	sql = "select FILIALNR,STANDORT_LANG from FILIALE " \
		  "order by STANDORT_LANG";
	s = SqlOpenCs( &m_Fd, sql );
	if ( s != 0 ) 
		m_cErrMeld = DynErrmld();
	else
		m_cErrMeld = "";
	m_nSqlCode = s;
	m_nIsamCode = SqlIsamCode();
	m_nNumberOfBranches = 0;
	m_nCurrentBranchIndex = 0;
	return s;
}

long CGetBranches::Fetch()
{
	long s;
	short filialnr;
	char  standort_lang[50];
	s = SqlFetch( m_Fd, 1, &filialnr, standort_lang, NULL );
	if ( s == 0 )
	{
		m_cErrMeld = "";
		m_cStandortLang.Add( standort_lang );
		m_wFilialNr.Add( filialnr );
		m_nNumberOfBranches++;
	}
	else
		m_cErrMeld = DynErrmld();
	m_nSqlCode  = s;
	m_nIsamCode = SqlIsamCode();
	return s;
}

void CGetBranches::CloseCs()
{
	if ( m_Fd != -1 )
		SqlCloseCs( m_Fd );
	m_Fd = -1;
}


long CGetBranches::ReadBranchOffices( CString& cErrmld )
{
	long s;
	m_cStandortLang.RemoveAll();
	m_wFilialNr.RemoveAll();
	s = OpenCs();
	while ( s == 0 )
		s = Fetch();
	CloseCs(); 
	cErrmld = m_cErrMeld;
	if ( s == 100 && m_nNumberOfBranches > 0 )
		return 0;
	return s;
}


void CGetBranches::MakeGrossKlein( CString & cStr )
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

long CGetBranches::FirstStandortLang( CString& StandOrt, CString& cErrmld )
{
	StandOrt = "";
	m_nHelpIndex = 0;
 //  if ( m_nNumberOfBranches == 0 )
		ReadBranchOffices( cErrmld );	// immer neu Lesen 
	if ( m_nSqlCode == 100 && m_nNumberOfBranches > 0 )
	{
		StandOrt = m_cStandortLang.GetAt( m_nHelpIndex++ );
		MakeGrossKlein( StandOrt );
		return 0;
	}
	return m_nSqlCode;
	
}

long CGetBranches::NextStandortLang( CString& StandOrt )
{
	if ( m_nHelpIndex < m_nNumberOfBranches )
	{
		StandOrt = m_cStandortLang.GetAt( m_nHelpIndex++ );
		MakeGrossKlein( StandOrt );
		return 0;
	}
	StandOrt = "";
	return 100;
}

CString CGetBranches::GetCurrentBranchName( bool mode )
{
	CString Filiale;
	if ( m_nNumberOfBranches == 0 )
		return "";
	else
	{ 
		Filiale = m_cStandortLang.GetAt( m_nCurrentBranchIndex );
		if ( !mode )
			MakeGrossKlein( Filiale );
		return Filiale;
	}
}

void CGetBranches::SetCurrentBranch( int index )
{
	if ( index < m_nNumberOfBranches )
		m_nCurrentBranchIndex = index;
}

short CGetBranches::GetCurrentBranchNumber( )
{
	if ( m_nCurrentBranchIndex < m_nNumberOfBranches ) 
		return m_wFilialNr[ m_nCurrentBranchIndex ];
	else
		return -1;
}