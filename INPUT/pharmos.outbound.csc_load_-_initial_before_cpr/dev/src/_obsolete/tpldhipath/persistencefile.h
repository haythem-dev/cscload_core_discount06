#ifndef __PERSISTENCEFILE_H__
#define __PERSISTENCEFILE_H__ __PERSISTENCEFILE_H__

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Includes 
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <string>
#include "persistence.h"
#include "customerroutingtable.h"
#include <fstream>


///////////////////////////////////////////////////////////////////////////////////////////////////////
// class SLogFile
///////////////////////////////////////////////////////////////////////////////////////////////////////
class PersistenceFile : public Persistence
{
public:

    PersistenceFile( const std::string& delimiter );
    ~PersistenceFile();
    virtual bool open( const std::string& resource );
    virtual bool close();
    virtual std::pair<bool, unsigned long> erase( const unsigned int dc, const long lDateOfRunning );

protected:
	virtual bool save( SCustomRoutingTable& customer );
    virtual SCustomRoutingTable* createCustomRoutingTable();

private:
    std::string     m_Delimiter;
    std::ofstream   m_persof;
};

#endif // __PERSISTENCEFILE_H__
