///////////////////////////////////////////////////////////////////////////////////////////////////////
// Definition: Persistence.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include "define.h"
#include "macro.h"
#include "persistencefile.h"
#include "sql.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
///////////////////////////////////////////////////////////////////////////////////////////////////////
PersistenceFile::PersistenceFile( const std::string& delimiter )
: Persistence(), m_Delimiter( delimiter )
{
	__FUNCTION__( PersistenceFile::PersistenceFile )
	DEBUG_ENTER( fun )
	DEBUG_LEAVE( fun )	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
///////////////////////////////////////////////////////////////////////////////////////////////////////
PersistenceFile::~PersistenceFile()
{
	__FUNCTION__( ~PersistenceFile() )
	DEBUG_ENTER( fun )	
	DEBUG_LEAVE( fun )	
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// SCustomRoutingTable* PersistenceFile::createCustomRoutingTable()
///////////////////////////////////////////////////////////////////////////////////////////////////////
SCustomRoutingTable* PersistenceFile::createCustomRoutingTable()
{
    __FUNCTION__( PersistenceFile::createCustomRoutingTable() )
    DEBUG_ENTER( fun )	
    DEBUG_LEAVE( fun )	
    return new SCustomRoutingTable( m_Delimiter );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// bool PersistenceFile::open()
///////////////////////////////////////////////////////////////////////////////////////////////////////
bool PersistenceFile::open( const std::string& resource )
{
	__FUNCTION__( PersistenceFile::open() )
    
//
//Flag                        Meaning
//
//std::ios::app               Append data to the end of the output file.
//std::ios::ate               Go to the end of the file when opened.
//std::ios::in                Open for input (must be supplied to the open member function of 
//                            std::ifstream variables).
//std::ios::out               Open file for output (must be supplied to the open member function of 
//                            std::ofstream variables).
//std::ios::binary            Binary file (if not present, the file is opened as an ASCII file). 
//                            See the later section "Binary I/O" for a definition of a binary file.
//std::ios::trunc             Discard contents of existing file when opening for write.
//std::ios::nocreate          Fail if the file does not exist. (Output files only. 
//                            Opening an input file always fails if there is no file.)
//std::ios::noreplace         Do not overwrite existing file. If a file exists, cause the open to fail.

    m_persof.open( resource.c_str(), ios::trunc | ios::out );
    
    if( !m_persof.is_open() ){
        m_ErrMsg = "Error with opening the file <";
        m_ErrMsg.append( resource ); 
        m_ErrMsg.append( ">."); 
        return false;
    }

    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// bool PersistenceFile::close()
///////////////////////////////////////////////////////////////////////////////////////////////////////
bool PersistenceFile::close()
{
	__FUNCTION__( PersistenceFile::close() )
    
    if( m_persof.is_open() ){
        m_persof.close();
    }

    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////
bool PersistenceFile::save( SCustomRoutingTable& customer )
{
	__FUNCTION__( PersistenceFile::save() )

    if( false == m_persof.is_open() ){
        m_ErrMsg = std::string(fun) + "Output file is not open!";
        return false;
    }
    customer.toSerialize( m_persof );
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// bool PersistenceFile::erase()
///////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<bool, unsigned long> PersistenceFile::erase( const unsigned int dc, const long lDateOfRunning )
{
    return std::make_pair( true, 0UL );
}