// SqlGetFiliale.cpp : implementation file
//

#include "stdafx.h"

#include "GetBranches.h"

#include <libscsvoodoo/libscsvoodoo.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SqlGetFiliale


CGetBranches::CGetBranches( bool bIsStandardEngine )
{
	m_Fd = -1;
	m_cErrMeld  = "";
	m_nSqlCode  = 0;
	m_nIsamCode = 0;
	m_nNumberOfRegionBranches = 0;
	m_nNumberOfBranches = 0;
	m_nCurrentBranchIndex = 0;
	m_nBeginOfRegionIndex = 0;

	m_bIsStandardEngine = bIsStandardEngine;

	m_bImmerNeulesen    = false;
}

CGetBranches::~CGetBranches()
{
	m_cStandortLang.RemoveAll();
	m_cStandortKurz.RemoveAll();
	m_cFilialArt.RemoveAll();
	m_wFilialNr.RemoveAll();
	m_wRegion.RemoveAll();
}

long CGetBranches::OpenCs( )
{
	long s;
	CString sql;
//	if ( m_bIsStandardEngine )
		sql = "select REGION,FILIALNR,STANDORT_LANG,STANDORT_KURZ,FILIAL_ART from RFILIALE " \
			  "order by REGION,STANDORT_LANG";
//	else
//		sql = "select REGION,FILIALNR,STANDORT_LANG,STANDORT_KURZ,FILIAL_ART from regioek:RFILIALE " \
//			  "order by REGION,STANDORT_LANG";
	s = SqlOpenCs( &m_Fd, sql );
	if ( s != 0 ) 
		m_cErrMeld = DynErrmld();
	else
		m_cErrMeld = "";
	m_nSqlCode = s;
	m_nIsamCode = SqlIsamCode();
	m_nNumberOfRegionBranches = 0;
	m_nNumberOfBranches = 0;
	m_nCurrentBranchIndex = 0;
	m_nBeginOfRegionIndex = 0;
	return s;
}

long CGetBranches::Fetch()
{
	long s;
	short region;
	short filialnr;
	char  standort_lang[50];
	char  standort_kurz[10];
	char  filial_art[10];

	s = SqlFetch( m_Fd, 1,
		          &region, &filialnr, standort_lang, standort_kurz, filial_art, NULL );
	if ( s == 0 )
	{
		m_cErrMeld = "";
		m_cStandortLang.Add( standort_lang );
		m_cStandortKurz.Add( standort_kurz );
		m_cFilialArt.Add( filial_art );
		m_wFilialNr.Add( filialnr );
		m_wRegion.Add( region );
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
	m_cStandortKurz.RemoveAll();
	m_cFilialArt.RemoveAll();
	m_wFilialNr.RemoveAll();
	m_wRegion.RemoveAll();
	s = OpenCs();
	while ( s == 0 )
		s = Fetch();
	CloseCs(); 
	cErrmld = m_cErrMeld;
//	cErrmld.Format( "%s, %d", m_cErrMeld, m_nNumberOfBranches );
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
    if ( m_bImmerNeulesen || m_nNumberOfBranches == 0 )
		ReadBranchOffices( cErrmld );	// nicht immer neu Lesen 
	m_nBeginOfRegionIndex = m_nNumberOfBranches;  // !!!!!!!!!!!!!!!!
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


long CGetBranches::FirstRegionStandortLang( short region, CString& StandOrt,
							 				CString& cErrmld )
{
	StandOrt = "";
	m_nHelpIndex = 0;
   if ( m_bImmerNeulesen || m_nNumberOfBranches == 0 )
		ReadBranchOffices( cErrmld );	// immer neu Lesen 
	m_nBeginOfRegionIndex = m_nNumberOfBranches;  // !!!!!!!!!!!!!!!!
	if ( m_nSqlCode == 100 && m_nNumberOfBranches > 0 )
	{
		while ( m_nHelpIndex < m_nNumberOfBranches &&
		        m_wRegion.GetAt(m_nHelpIndex) != region ) m_nHelpIndex++;
		m_nBeginOfRegionIndex = m_nHelpIndex;
		return NextRegionStandortLang( region, StandOrt );
	}
	return m_nSqlCode;
	
}

long CGetBranches::NextRegionStandortLang( short region, CString& StandOrt )
{
	if ( m_nHelpIndex < m_nNumberOfBranches &&
		 m_wRegion.GetAt(m_nHelpIndex) == region )
	{
		m_nNumberOfRegionBranches++;
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
	index += m_nBeginOfRegionIndex;
	if ( index < m_nNumberOfBranches )
		m_nCurrentBranchIndex = index;
}

int CGetBranches::SetCurrentBranchViaFilialnr( short filialnr )
{
	int index;
	index = 0;
	while ( index < m_nNumberOfBranches )
	{
		if ( filialnr == m_wFilialNr[ index ] ) 
		{
			m_nCurrentBranchIndex = index;
			return index - m_nBeginOfRegionIndex;
			return index;
		}
		index++;
	}
	return -1;		
}

short CGetBranches::GetCurrentBranchNumber( )
{
	if ( m_nCurrentBranchIndex < m_nNumberOfBranches ) 
		return m_wFilialNr[ m_nCurrentBranchIndex ];
	else
		return -1;
}

int CGetBranches::GetAllBranchNumbers( CWordArray& wNumbers  )
{
	int   index;
	int   anzahl;
	short region;

	wNumbers.RemoveAll();
	index = m_nBeginOfRegionIndex;
	if ( index >= m_nNumberOfBranches ) 
		return 0;

	region = m_wRegion[ index ];
	anzahl = 0;
	while ( index < m_nNumberOfBranches && m_wRegion[ index ] == region )
	{
	 	wNumbers.Add( m_wFilialNr[ index++ ] );
		anzahl++;
	}
	return anzahl;
}

int CGetBranches::GetAllBranches( CWordArray& wNumbers, CStringArray& sNames,
								  bool mode )
{
	int   index;
	int   anzahl;
	short region;
	CString cFiliale;

	wNumbers.RemoveAll();
	sNames.RemoveAll();
	index = m_nBeginOfRegionIndex;
	if ( index >= m_nNumberOfBranches ) 
		return 0;

	region = m_wRegion[ index ];
	anzahl = 0;
	while ( index < m_nNumberOfBranches && m_wRegion[ index ] == region )
	{
	 	cFiliale = m_cStandortLang[ index ];
		if ( !mode )
			MakeGrossKlein( cFiliale );
	 	sNames.Add	( cFiliale );
	 	wNumbers.Add( m_wFilialNr[ index++ ] );
		anzahl++;
	}
	return anzahl;
}


CString CGetBranches::GetBranchesInRegion( )
{
	CString cNr;
	CString s;
	int   index;
	short region;

	index = m_nBeginOfRegionIndex;
	if ( index >= m_nNumberOfBranches ) 
		return "";

	region = m_wRegion[ index ];

	s = "";
	while ( index < m_nNumberOfBranches && m_wRegion[ index ] == region )
	{
		cNr.Format( "%d", m_wFilialNr[index++] );
		s += cNr;
		s += ",";
	}
	s = s.Left( s.GetLength() - 1 );
	return s;
}

CString CGetBranches::GetBranches( )
{
	CString cNr;
	CString s;
	int   index = 0;

	s = "";
	while ( index < m_nNumberOfBranches  )
	{
		if (m_wFilialNr[index] != 21 && m_wFilialNr[index] != 27 ) // PPE und Hageda explizit aus der Liste aller VZ´s ausschließen
		{
			cNr.Format( "%d", m_wFilialNr[index] );
			s += cNr;
			s += ",";
		}

		++index;
	}
	s = s.Left( s.GetLength() - 1 );
	return s;
}


int CGetBranches::GetAllExistentBranches( CWordArray& wNumbers, 
										  CStringArray& sNames,
								          bool mode )
{
	int   index;
	int   anzahl;
	CString cFiliale;

	wNumbers.RemoveAll();
	sNames.RemoveAll();
	index = 0;
	anzahl = 0;
	while ( index < m_nNumberOfBranches  )
	{
	 	cFiliale = m_cStandortLang[ index ];
		if ( !mode )
			MakeGrossKlein( cFiliale );
	 	sNames.Add	( cFiliale );
	 	wNumbers.Add( m_wFilialNr[ index++ ] );
		anzahl++;
	}
	return anzahl;
}

CString CGetBranches::GetBranchShortName( short filialnr )
{
	int index;
	index = 0;
	while ( index < m_nNumberOfBranches )
	{
		if ( filialnr == m_wFilialNr[ index ] ) 
		{
			return m_cStandortKurz[ index ];
		}
		index++;
	}
	return "";		
}

CString CGetBranches::GetBranchType( short filialnr )
{
	int index;
	index = 0;
	while ( index < m_nNumberOfBranches )
	{
		if ( filialnr == m_wFilialNr[ index ] ) 
		{
			return m_cFilialArt[ index ];
		}
		index++;
	}
	return "";		
}