///////////////////////////////////////////////////////////////////////////////////////////////////////
// Definition: Persistence.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include "define.h"
#include "macro.h"
#include "persistencedb.h"
#include "sql.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////////////////////////////
PersistenceDB::PersistenceDB()
: Persistence(), m_CRemoteConn( 0 )
{
	__FUNCTION__( PersistenceDB::PersistenceDB )
	DEBUG_ENTER( fun )
	DEBUG_LEAVE( fun )	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////////////////////////////////
PersistenceDB::~PersistenceDB()
{
	__FUNCTION__( ~PersistenceDB() )
	DEBUG_ENTER( fun )	

    cleanUp();

	DEBUG_LEAVE( fun )	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// SCustomRoutingTable* PersistenceDB::createCustomRoutingTable()
///////////////////////////////////////////////////////////////////////////////////////////////////////
SCustomRoutingTable* PersistenceDB::createCustomRoutingTable()
{
    return new SCustomRoutingTable();
    /*static SCustomRoutingTable obj;
    return &obj;*/
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// void PersistenceDB::cleanUp()
///////////////////////////////////////////////////////////////////////////////////////////////////////
void PersistenceDB::cleanUp()
{
	__FUNCTION__( PersistenceDB::cleanUp() )

    if( 0 != m_CRemoteConn ){
        delete m_CRemoteConn;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// bool PersistenceDB::open()
///////////////////////////////////////////////////////////////////////////////////////////////////////
bool PersistenceDB::open( const std::string& resource )
{
	__FUNCTION__( PersistenceDB::open() )
    
    tError stError;    
#ifndef NDEBUG
	if( OpenDb( resource.c_str(), &stError ) != IS_OK ){
        m_ErrMsg = stError.spError;
        return false;
	}
    if( SetIsolation(DIRTY_READ, &stError) != IS_OK ){
        m_ErrMsg = stError.spError;
        return false;
	}
#else
    
	if( ConnectDb(	getRemoteConn(resource)->SPREMOTEDB, getRemoteConn()->SPCONNHANDLE, 
					getRemoteConn()->SPUSER, getRemoteConn()->SPPASSWORD, &stError ) != IS_OK ){
        m_ErrMsg = stError.spError;
        return false;
	}
#endif

    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// PersistenceDB::CRemoteConn* PersistenceDB::getRemoteConn( const std::string& resource /*= ""*/ )
///////////////////////////////////////////////////////////////////////////////////////////////////////
PersistenceDB::CRemoteConn* PersistenceDB::getRemoteConn( const std::string& resource /*= ""*/ )
{
	__FUNCTION__( PersistenceDB::getRemoteConn() )

    if( 0 == m_CRemoteConn ){
        if( resource.empty() ){ throw PersistenceDB::RemoteConnectionNotInitialized(); }
        m_CRemoteConn = new PersistenceDB::CRemoteConn( resource.c_str() );
    }
    return m_CRemoteConn;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// bool PersistenceDB::close()
///////////////////////////////////////////////////////////////////////////////////////////////////////
bool PersistenceDB::close()
{
	__FUNCTION__( PersistenceDB::close() )

    tError stError;    
#ifndef NDEBUG
	if( CloseDb( &stError ) != IS_OK ){
        m_ErrMsg = stError.spError;        
        return false;
	}
#else
	if( DisconnectDB( getRemoteConn()->SPCONNHANDLE, &stError ) != IS_OK ){
        m_ErrMsg = stError.spError;        
        return false;
	}
#endif
    cleanUp();

    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// bool PersistenceDB::save( SCustomRoutingTable& customer )
///////////////////////////////////////////////////////////////////////////////////////////////////////
bool PersistenceDB::save( SCustomRoutingTable& customer )
{
	__FUNCTION__( PersistenceDB::save() )

#ifndef NDEBUG
    customer.toStream();
#endif

    if( customer.save() == false ){
        m_ErrMsg = customer.getErrMsg();
	    return false;
    }
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// bool PersistenceDB::erase()
///////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<bool, unsigned long> PersistenceDB::erase( const unsigned int dc, const long lDateOfRunning )
{
	__FUNCTION__( PersistenceDB::erase() )
    
	SCustomRoutingTable objSCustomRoutingTable;
	bool erased =  objSCustomRoutingTable.erase( dc, lDateOfRunning );
    if( false == erased ){
        m_ErrMsg = objSCustomRoutingTable.getErrMsg();    
    }
    
    return std::make_pair( erased, objSCustomRoutingTable.m_stS_Counter.ulDel );
}