//#####################################################################################################//
// INCLUDES 
//#####################################################################################################//
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "slogfile.h"
#include "customerroutingtable.h"
#include "macro.h"
#include "define.h"
#include "sql.h"
#include "date.h"

using std::boolalpha;
using std::ostringstream;

extern "C"
{
	retClient prepareSCustomRoutingTable( tError* pstError );
	void freeSCustomRoutingTable();
	retClient saveSCustomRoutingTable( struct SQLSCUSTOMROUTINGTABLE* p, struct S_Counter* pCnt, tError* pstError );
    retClient eraseSCustomRoutingTable( unsigned int uiDcNo, long lDate, struct S_Counter* pCnt, tError* pstError, char* szSqlBuffer );
}
//#####################################################################################################//
// bool SCustomRoutingTable::save()
//#####################################################################################################//
bool SCustomRoutingTable::save()
{
	__FUNCTION__( SCustomRoutingTable::save() )
	DEBUG_ENTER( fun )
	
	bool bSaved = true;
	static bool b_Already_Prepared = false;
		
	if( b_Already_Prepared == false ){
		if( prepare() == false ){
			bSaved = false;
		} else {
			b_Already_Prepared = true;
		}
	}

	if( bSaved == true ){
		if( saveSCustomRoutingTable( &m_stSQLSTRUCT, &m_stS_Counter, &m_stError ) != IS_OK ){
			cout << fun << " saveSCustomRoutingTable != IS_OK " << endl;
			bSaved = false;
		}
	}

    return bSaved;
	DEBUG_LEAVE( fun ) 
}
//#####################################################################################################//
// bool erase( const unsigned int uiDCNo, const long lDateOfRunning )
//#####################################################################################################//
bool SCustomRoutingTable::erase( const unsigned int uiDCNo, const long lDateOfRunning )
{
	__FUNCTION__( SCustomRoutingTable::erase() )
	DEBUG_ENTER( fun ) 
    bool bErased = true;
    
	ostringstream os;
	os << "Aufruf Methode 'eraseSCustomRoutingTable(" << uiDCNo << ", " << lDateOfRunning << "..., ... " << ")'";
	SLogFile::Exemplar()->log( fun, SLogFile::OK, os.str().c_str() );
	
	char szSqlBuffer[1024];
	strncpy( szSqlBuffer, " ", 1024 );
	szSqlBuffer[1023] = 0;
	if( eraseSCustomRoutingTable( uiDCNo, lDateOfRunning, &m_stS_Counter, &m_stError, szSqlBuffer ) != IS_OK ){
	    bErased = false;
	}

	SLogFile::Exemplar()->log( fun, SLogFile::OK, szSqlBuffer );


	DEBUG_LEAVE( fun ) 
	return bErased;
}
//#####################################################################################################//
// bool SCustomRoutingTable::prepare()
//#####################################################################################################//
bool SCustomRoutingTable::prepare()
{
	__FUNCTION__( SCustomRoutingTable::prepare() )
	DEBUG_ENTER( fun ) 

	bool bPrepared = false;

	if( prepareSCustomRoutingTable( &m_stError ) == IS_OK ){
		bPrepared = true;
	}

	DEBUG_LEAVE( fun )
	return bPrepared;
}
//#####################################################################################################//
// constructor
//#####################################################################################################//
SCustomRoutingTable::SCustomRoutingTable()
{
	init();
}
//#####################################################################################################//
// constructor
//#####################################################################################################//
SCustomRoutingTable::SCustomRoutingTable( const string& delimiter )
:m_stSQLSTRUCT( delimiter )
{
}
//#####################################################################################################//
// destructor
//#####################################################################################################//
SCustomRoutingTable::~SCustomRoutingTable()
{
	free();
}
//#####################################################################################################//
// void SCustomRoutingTable::init()
//#####################################################################################################//
void SCustomRoutingTable::init()
{
	__FUNCTION__( SCustomRoutingTable::init() )
	DEBUG_ENTER( fun ) 
	
	m_stSQLSTRUCT.init();	
	
	DEBUG_LEAVE( fun )
}
//#####################################################################################################//
// void SCustomRoutingTable::free()
//#####################################################################################################//
void SCustomRoutingTable::free()
{
	__FUNCTION__( SCustomRoutingTable::free() )
	DEBUG_ENTER( fun )
	
	freeSCustomRoutingTable();

	DEBUG_LEAVE( fun ) 
}
//#####################################################################################################//
// const char* SCustomRoutingTable::getErrMsg()
//#####################################################################################################//
const char* SCustomRoutingTable::getErrMsg()
{
	__FUNCTION__( SCustomRoutingTable::getErrMsg() )
	DEBUG_ENTER( fun )
	DEBUG_LEAVE( fun )
	return m_stError.spError;
}
//#####################################################################################################//
// void SCustomRoutingTable::toStream( ostream& strm /* = std::cout */ )
//#####################################################################################################//
void SCustomRoutingTable::toStream( ostream& strm /* = std::cout */ )
{
	__FUNCTION__( SCustomRoutingTable::toStream() )
	DEBUG_ENTER( fun )

	cout << endl;

   	COUT( m_stSQLSTRUCT.ORIGIN				)
	COUT( m_stSQLSTRUCT.CALLTYPE			)
	COUT( m_stSQLSTRUCT.INITIALPRIORITY		)
	COUT( m_stSQLSTRUCT.RESERVEAGENTID		)
	COUT( m_stSQLSTRUCT.RESERVEAGENTSITE	)
	COUT( m_stSQLSTRUCT.RESERVEAGENTTIME	)
	COUT( m_stSQLSTRUCT.CAPTION				)
	COUT( m_stSQLSTRUCT.CALLDATA			)
	COUT( m_stSQLSTRUCT.DDE					)

	DEBUG_LEAVE( fun ) 
}
//#####################################################################################################//
// void SCustomRoutingTable::toSerialize( ostream& strm /*= std::cout*/ )
//#####################################################################################################//
void SCustomRoutingTable::toSerialize( ostream& strm /*= std::cout*/ )
{
	__FUNCTION__( SCustomRoutingTable::toSerialize() )
	DEBUG_ENTER( fun )
    
    m_stSQLSTRUCT.toSerialize( m_stS_Counter, strm );

	DEBUG_LEAVE( fun ) 
}
