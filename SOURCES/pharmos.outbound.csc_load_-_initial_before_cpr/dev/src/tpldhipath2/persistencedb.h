#ifndef __PERSISTENCEDB_H__
#define __PERSISTENCEDB_H__ __PERSISTENCEDB_H__

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes 
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include "persistence.h"
#include "customerroutingtable.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
// class SLogFile
///////////////////////////////////////////////////////////////////////////////////////////////////////
class PersistenceDB : public Persistence
{
public:

    PersistenceDB();
    ~PersistenceDB();
    virtual bool open( const std::string& resource );
    virtual bool close();
    virtual std::pair<bool, unsigned long> erase( const unsigned int dc, const long lDateOfRunning );

protected:
	virtual bool save( SCustomRoutingTable& customer );
    virtual SCustomRoutingTable* createCustomRoutingTable();

private:
    class RemoteConnectionNotInitialized {};
    ///////////////////////////////////////////////////////////////////////////////
    // class CRemoteConn
    ///////////////////////////////////////////////////////////////////////////////
    class CRemoteConn
    {
    public:
	    CRemoteConn( const char* spRemoteDB )
	    : SPREMOTEDB(spRemoteDB), SPCONNHANDLE("conn_rrcustom"), 
		  SPUSER("vksc"), SPPASSWORD("phoenix") 
	    {}
	    const char* const SPREMOTEDB; 
	    const char* const SPCONNHANDLE; 
	    const char* const SPUSER; 
	    const char* const SPPASSWORD; 
    };
    CRemoteConn* m_CRemoteConn;
    
    CRemoteConn* getRemoteConn( const std::string& resource = "" );
    void cleanUp();
};

#endif // __PERSISTENCEDB_H__
