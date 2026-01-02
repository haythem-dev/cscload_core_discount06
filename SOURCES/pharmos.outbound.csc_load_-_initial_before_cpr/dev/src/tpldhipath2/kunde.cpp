//#####################################################################################################//
// INCLUDES 
//#####################################################################################################//
#include <stdio.h>
#include <string.h>
#include "kunde.h"
#include "macro.h"
#include "define.h"
#include "sql.h"

extern "C"
{
	retClient prepareSKundeSelect( tError* pstError );
	void freeSKundeSelect();
	retClient loadSKundeSelect( struct S_SQLKUNDE* p, struct S_Counter* pCnt, tError* pstError );
}
//#####################################################################################################//
// void SKundeSelect::load()
//#####################################################################################################//
bool SKundeSelect::load()
{
	__FUNCTION__( SKundeSelect::load() )
	DEBUG_ENTER( fun )
	
	bool bLoaded = true;
	
	if( loadSKundeSelect( &m_stSQLSTRUCT, &m_stS_Counter, &m_stError ) != IS_OK ){
		bLoaded = false;
	}

    // Letzten Leerstrings des Apo-Namens entfernen
    std::string sSegment = m_stSQLSTRUCT.NAMEAPO;
    trim( sSegment );
    strncpy( m_stSQLSTRUCT.NAMEAPO,	sSegment.c_str(), sSegment.length() );

    // Letzten Leerstrings des Ortes entfernen
    sSegment = m_stSQLSTRUCT.ORT;
    trim( sSegment );
    strncpy( m_stSQLSTRUCT.ORT,	sSegment.c_str(), sSegment.length() );

	DEBUG_LEAVE( fun ) 
	return bLoaded;
}
//#####################################################################################################//
// void SKundeSelect::trim()
//#####################################################################################################//
void SKundeSelect::trim( string& sSegment )
{
    __FUNCTION__( SKundeSelect::trim() )
	DEBUG_ENTER( fun )
    
    string::size_type st_Pos = sSegment.find_last_not_of(" "); 
	if( string::npos != st_Pos ){
		// sSegment ist kein Leerstring und kein String mit Leerzeichen
		sSegment[static_cast<int>(st_Pos) + 1] = 0;
	} 
    
    DEBUG_LEAVE( fun ) 
}
//#####################################################################################################//
// constructor
//#####################################################################################################//
SKundeSelect::SKundeSelect()
{
	init();

}
//#####################################################################################################//
// destructor
//#####################################################################################################//
SKundeSelect::~SKundeSelect()
{
	freeSKundeSelect();
}
//#####################################################################################################//
// void SKundeSelect::init()
//#####################################################################################################//
void SKundeSelect::init()
{
	__FUNCTION__( SKundeSelect::init() )
	DEBUG_ENTER( fun ) 
	
	m_stSQLSTRUCT.init();	
	m_stS_Counter.init();
	
	DEBUG_LEAVE( fun )
}
//#####################################################################################################//
// bool SKundeSelect::prepare()
//#####################################################################################################//
bool SKundeSelect::prepare()
{
	__FUNCTION__( SKundeSelect::prepare() )
	DEBUG_ENTER( fun ) 

	bool bPrepared = false;

	if( prepareSKundeSelect( &m_stError ) == IS_OK ){
		bPrepared = true;
	}

	DEBUG_LEAVE( fun )
	return bPrepared;
}
//#####################################################################################################//
// void S_ArtVe::free()
//#####################################################################################################//
void SKundeSelect::free()
{
	__FUNCTION__( SKundeSelect::free() )
	DEBUG_ENTER( fun )
	
	freeSKundeSelect();

	DEBUG_LEAVE( fun ) 
}
//#####################################################################################################//
// const char* SKundeSelect::getErrMsg()
//#####################################################################################################//
const char* SKundeSelect::getErrMsg()
{
	__FUNCTION__( SKundeSelect::getErrMsg() )
	DEBUG_ENTER( fun )
	DEBUG_LEAVE( fun )
	return m_stError.spError;
}
//#####################################################################################################//
// void SKundeSelect::toStream( ostream& = std::cout )
//#####################################################################################################//
void SKundeSelect::toStream( ostream& strm /* = std::cout */ )
{
	__FUNCTION__( SKundeSelect::toStream() )
	DEBUG_ENTER( fun )

	cout << endl;

    COUT( m_stSQLSTRUCT.KUNDENNR				)
	COUT( m_stSQLSTRUCT.VERTRIEBSZENTRUMNR		)
	COUT( m_stSQLSTRUCT.NAMEAPO                 )
	COUT( m_stSQLSTRUCT.ORT		                )
	COUT( m_stSQLSTRUCT.KUNDE_TELNR				)
	COUT( m_stSQLSTRUCT.KZKDKLASSE				)
	COUT( m_stSQLSTRUCT.PHONEPRIORITY			)
	COUT( m_stSQLSTRUCT.CUSTOMERPHONENO_TELNR	)
	COUT( m_stSQLSTRUCT.KZSPRACHE				)

	DEBUG_LEAVE( fun ) 
}