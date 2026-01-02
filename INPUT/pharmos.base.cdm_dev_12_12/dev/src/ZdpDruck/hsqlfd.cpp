// hSqlFd.cpp : implementation file
//

#include "stdafx.h"

#include "hSqlFd.h"
#include <libscsvoodoo/libscsvoodoo.h>
 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// ChSqlFd

ChSqlFd::ChSqlFd()
{
	m_Fd = -1;
	m_SelBuf  = NULL;
	m_nBufLen = 0;
	m_bScroll = false;
	m_bHold	  = false;

	m_nMaxBufNumber = 0;
	m_nVekBreite = 0;
	m_nBlaetterIndex = 0;
	m_nAuswahlIndex = 0;

	m_bWaitInfo = true;

}

ChSqlFd::~ChSqlFd()
{
	FreeVector();
}

void ChSqlFd::SetWaitInfo( bool mode )
{
	m_bWaitInfo = mode;
}

////////////////////////////////////////////////////////////////////////
// Implementation

/*
void ChSqlFd::SetSelectBuffer( void *SelBuf )
{
	m_SelBuf = SelBuf;
}
*/

long ChSqlFd::OpenCursor( CString Sql, int OpenMode, CString &cErrmld )
{
	long s;
	int  len;
/*
	if ( m_SelBuf == 0 )
	{
		cErrmld = _T( "First perform SetSelectBuffer()" );
		return -1;
	}
*/

	if ( m_Fd != -1 ) SqlCloseCs ( m_Fd );
//	if ( m_SelBuf != NULL ) delete [] m_SelBuf;
//	CloseCursor( );

	if ( OpenMode & S_WITH_SCROLL )
	{
		m_bScroll = true;
		if ( OpenMode & S_WITH_HOLD )
		{
			m_bHold = true;
			s = SqlOpenScrollCsWh( &m_Fd, Sql );
		}
		else
		{
			m_bHold = false;
			s = SqlOpenScrollCs  ( &m_Fd, Sql );
		}
	}
	else
	{
		m_bScroll = false;
		if ( OpenMode & S_WITH_HOLD )
		{
			m_bHold = true;
			s = SqlOpenCsWh( &m_Fd, Sql );
		}
		else
		{
			m_bHold = false;
			s = SqlOpenCs  ( &m_Fd, Sql );
		}
	}

	if ( s != 0 )
	{
		cErrmld = DynErrmld();
		m_Fd = -1;
	}
	else
	{
		s = SqlGetStructLen( m_Fd, &len );
		if ( s != 0 )
		{
			cErrmld = DynErrmld();
			SqlCloseCs( m_Fd );
			m_Fd = -1;
			if ( m_SelBuf != NULL ) delete [] m_SelBuf;
			m_SelBuf = NULL;
			m_nBufLen = 0;
		}
		else
		{
			if ( m_SelBuf == NULL )
			{
				m_nBufLen = len;
				m_SelBuf = new char[len];
			}
			else
			{
				if ( m_nBufLen != len )
				{
					delete [] m_SelBuf;
					m_nBufLen = len;
					m_SelBuf = new char[len];
				}
			}
		}
	}
	m_nSqlError = s;
	return s;
}



long ChSqlFd::FetchCursor ( long Pos )
{
	m_nSqlError = SqlFetch ( m_Fd, Pos, m_SelBuf, NULL );
	return 	m_nSqlError;
}


void ChSqlFd::CloseCursor( )
{
	if ( m_Fd != -1 ) SqlCloseCs ( m_Fd );
	m_Fd = -1;
	if ( m_SelBuf != NULL ) delete [] m_SelBuf;
	m_SelBuf = NULL;
	m_nBufLen = 0;
}

int  ChSqlFd::GetCursorFd()
{
	return m_Fd;
}


long ChSqlFd::FetchNextCursor()
{
	long s;
	s = FetchCursor( 1 );
	return s;
}

long ChSqlFd::FetchPrevCursor()
{
	long s;
	s = FetchCursor( -1 );
	return s;
}


bool ChSqlFd::IsScrollCursor()
{
	return m_bScroll;
}

bool ChSqlFd::IsCursorWithHold()
{
	return m_bHold;
}



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// Vector

void ChSqlFd::FreeVector()
{
	// Vektor Deallokieren
	if ( m_nVekBreite > 0 && m_VekPtr != NULL )
	{
		int i;
		for ( i = 0; i < m_nMaxBufNumber; i++ )
			if ( m_VekPtr[i] != NULL )
				delete [] m_VekPtr[i];
		delete [] m_VekPtr;
	}
	m_VekPtr = NULL;	// neu
}


void ChSqlFd::AllocVector( int nVecWidth )
{
	// Vektor free
//	FreeVector();	// neu jetzt weiter unten 

	// Vektor Allokieren
	int i;
	m_nVekBreite = nVecWidth;
	m_VekPtr = NULL;
	if ( m_nVekBreite > 0 )
	{
		m_VekPtr = new void *[m_nMaxBufNumber];
		for ( i = 0; i < m_nMaxBufNumber; i++ ) m_VekPtr[i] = NULL;
		i = 0;
		while ( i < m_nMaxBufNumber )
			m_VekPtr[i++] = new char[m_nVekBreite];
	}
}


void* ChSqlFd::GetBuffer( int index )
{
	if ( index >= 0 && index < m_nActBufNumber && m_VekPtr[index] != NULL )
		return m_VekPtr[index];
	else
		return NULL;
}

void* ChSqlFd::GetBuffer( )
{
	return m_SelBuf;
}


// 22.02.2000
void ChSqlFd::ReplaceBuffer( int index, void* SelBuf )
{
	if ( m_nVekBreite > 0 && m_VekPtr[index] != NULL )
		memcpy( m_VekPtr[index], SelBuf, m_nVekBreite );
}

void ChSqlFd::InsertBuffer( int index )
{
	if ( m_nVekBreite > 0 && m_VekPtr[index] != NULL )
		memcpy( m_VekPtr[index], m_SelBuf, m_nVekBreite );
}

int ChSqlFd::FetchBuffer( int step, int manz )
{
	int  anzahl;
	long s;

	anzahl = 0;

	s = FetchCursor ( step );

	while ( s == 0 && anzahl < manz )
	{
//	  	DeleteItem( anzahl );       // neu
//    	InsertItem( anzahl, " " );  // neu
		InsertBuffer ( anzahl );
		anzahl++;
		if ( anzahl < manz )
			s = FetchCursor ( 1 );
	}

//	if ( anzahl > 0 )
//		if ( anzahl < manz ) ClearVek( anzahl, 1 );

	return anzahl;
}


int ChSqlFd::FirstBuffer( int buf_anz )
{
	int  anz;

	anz = FetchBuffer( 1, buf_anz );

//	if ( anz == 0 ) ClearVek( anz, 0 );   /* neu !!!!!! */
	m_nPrevind = 1;
	return anz;
}

int ChSqlFd::NextBuffer( int buf_anz )
{
	int anz;

	anz = FetchBuffer( 1, buf_anz );

	if ( anz > 0 ) m_nPrevind++;
	return anz;
}

int ChSqlFd::PrevBuffer( int buf_anz )
{
	int anz;
	anz = FetchBuffer( -(m_nActBufNumber + buf_anz - 1), buf_anz );

	if ( anz > 0 ) m_nPrevind--;
	return anz;
}



int ChSqlFd::PosFetch( int index )
{
	long s;
	if ( index >= 0 && index < m_nActBufNumber && m_VekPtr[index] != NULL )
	{
		m_nAuswahlIndex = index;
		s = FetchCursor ( - ( m_nActBufNumber - m_nAuswahlIndex - 1 ) );
		if ( s == 0)
		{
			m_nBlaetterIndex = 0;
			return 0;
		}
		else 
			return 1;
	}
	return -1;
}



int ChSqlFd::StartSelect( CString Sql, int OpenMode, int nMaxItemNumber,
					      CString& cErrmld ) 
{
	long s;

	if ( m_bWaitInfo )
		BeginWaitCursor();
	s = OpenCursor( Sql, OpenMode, cErrmld );
	if ( m_bWaitInfo )
		EndWaitCursor();	
	if ( s != 0 )
		return -1;

	// Vektor free
	FreeVector();	// jetzt hier 

	m_nDeletedItems = 0;
	m_nMaxBufNumber = nMaxItemNumber;
	AllocVector( m_nBufLen );

	if ( m_bWaitInfo )
		BeginWaitCursor();
	m_nActBufNumber = FirstBuffer( m_nMaxBufNumber );
	if ( m_bWaitInfo )
		EndWaitCursor();
	if ( m_nActBufNumber > 0 )
	{
//		if ( m_bAutoEnable )
//			CListCtrl::EnableWindow( TRUE );  // !!!!!!!!!!!!!!!!!!!
		m_bAuswahlEnde = false;
//		MarkListPos( 0 );
		return m_nActBufNumber;
	}
	else
	{
//		CListCtrl::EnableWindow( FALSE );	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		m_bAuswahlEnde = true;
		cErrmld = _T( "Kein Satz in dieser Auswahl" );
		return 0;
	}
}


int ChSqlFd::NextSelect( CString& cErrmld )  
{
	int anzahl;
	// 10.12.98
//	if ( m_nActBufNumber < m_nMaxBufNumber || m_bAuswahlEnde )
	if ( m_nActBufNumber + m_nDeletedItems < m_nMaxBufNumber || m_bAuswahlEnde )
	{
//		MarkListPos( m_nActBufNumber - 1 );   // !!!!!!!!!!!!!!!!!!!!!!!!!
		cErrmld = _T( "Ende der Auswahl" );
		return 0;
	}

	if ( m_bWaitInfo )
		BeginWaitCursor();
	anzahl = NextBuffer( m_nMaxBufNumber );
	if ( m_bWaitInfo )
		EndWaitCursor();
	if (anzahl == 0)
	{
		cErrmld = _T( "Ende der Auswahl" );
	    m_bAuswahlEnde = true;
    }
	else
	{
		// neu
		// int i;
		// for ( i = anzahl; i < m_nMaxBufNumber; i++ ) DeleteItem( i );
		// neu ende
		m_nActBufNumber = anzahl;
//		MarkListPos( 0 );
		m_nDeletedItems = 0;	// 10.12.98
	}
	return anzahl;
}

int ChSqlFd::PrevSelect( CString& cErrmld )  
{
	int anzahl;
	if ( !m_bScroll )
	{
		cErrmld = _T( "no scrolling" );
		return 0;
	}
	if ( m_nPrevind <= 1)
	{
		cErrmld = _T( "Anfang der Auswahl" );
		return 0;
	}
	if ( m_bWaitInfo )
		BeginWaitCursor();
	anzahl = PrevBuffer( m_nMaxBufNumber );
	if ( m_bWaitInfo )
		EndWaitCursor();
	if (anzahl == 0)
	{
		cErrmld = _T( "error on scrolling" );
		return 0;
	}
	else
	{
  		m_nActBufNumber = anzahl;
//		MarkListPos( anzahl - 1);

	    m_bAuswahlEnde = false;   // 22.02.2001  */

		return anzahl;
	}
}



/////////////////////////////////////////////////////////////////
// Blaettern ausserhalb der Suchbox

long ChSqlFd::NextSingleSelect( CString& cErrmld )
{
	long s;

	s = FetchCursor( 1 );
	if ( s == 0 )
		m_nBlaetterIndex++;
	else if ( s == 100 )
		cErrmld = _T( "Ende der Auswahl" );
	else
		cErrmld = DynErrmld();
	return s;
}

long ChSqlFd::PrevSingleSelect(  CString& cErrmld )
{
	long s;
	s = FetchCursor( -1 );
	if ( s == 0 )
		m_nBlaetterIndex--;
	else if ( s == 100 )
		cErrmld = _T( "Anfang der Auswahl" );
	else
		cErrmld = DynErrmld();
	return s;
}


///////////////////////////////////////////////////////////////////
// Count 

long ChSqlFd::GetSqlCount( CString Sql, long *nCount, CString& sErrmld ) 
{
	long s;
	s = SqlCount( Sql, nCount );
	if ( s != 0 )
		sErrmld = DynErrmld();
	m_nSqlError = s;
	return s;
}


//////////////////////////////////////////////////////////
// Rueckkehr in die Suchbox: Suchbox aktualisieren

int ChSqlFd::ActualSelect( int& mRichtung, CString& cErrmld )
{
	long s;
	long pos;
	long relpos;
	long seite;
	long zeile;
	int  richtung;

	relpos = m_nBlaetterIndex + m_nAuswahlIndex;

	if ( relpos >= m_nMaxBufNumber )
		richtung = 1;
	else if ( relpos < 0 )
		richtung = -1;
	else
		richtung = 0;

	mRichtung = richtung;

	if ( relpos < 0  )
		relpos = -relpos - 1;   // auch hier Nullbasis

	seite = relpos/m_nMaxBufNumber;
	zeile = relpos%m_nMaxBufNumber;

	if ( richtung == 0 )		// gleiche Seite -> kein neuer select
	 {
		pos = m_nActBufNumber - zeile - 1;
		s = FetchCursor ( pos );
//		MarkListPos( zeile );
//		return true;
		return m_nActBufNumber;
	 }
	else if ( richtung == 1 )	// in Suchbox vorblaettern
	{
		pos = - zeile - 1;

		s = FetchCursor ( pos );
		if ( s == 0 )
		{
			if ( NextSelect( cErrmld ) > 0 )  // untersuchen !!!!!!!!! 
			{
//				MarkListPos( zeile );
				m_nPrevind += seite - 1;
			}
			return m_nActBufNumber;
		}
		else					
		{
			AfxMessageBox("fetch error" );
			return 0;
		}
	 }
	else						// in Suchbox zurueckblattern 
	{
		int Save_SuchboxAnzahl = m_nActBufNumber;
		m_nActBufNumber = - zeile;	// Trick
		m_nPrevind -= seite;
		if ( PrevSelect( cErrmld ) > 0 )	// unterdsuchen !!!!! 
		{
//			MarkListPos( m_PufferAnzahl - zeile - 1);
			return m_nActBufNumber;
		}
		else
		{
			m_nActBufNumber = Save_SuchboxAnzahl;
			return 0; // ?????????????????????????????????
		}
	}
}


long ChSqlFd::GetSqlError()
{
	return m_nSqlError;
}

/////////////////////////////////////////////////////////////////////////////
// ChSqlFd message handlers
