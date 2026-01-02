//-----------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      declaration of database login class
 *  \author     Bischof Bjoern
 *  \date       31.12.2010
 *  \version    00.00.00.01 first version
 */ 
//-----------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBBATCH_CMDLINE_CONFIGURATION_H
#define GUARD_LIBBATCH_CMDLINE_CONFIGURATION_H

//-----------------------------------------------------------------------------------------------//
// namespace section
//-----------------------------------------------------------------------------------------------//
namespace libBatch
{
namespace cmdLine
{

//-----------------------------------------------------------------------------------------------//
// struct declaration section
//-----------------------------------------------------------------------------------------------//
struct CmdLineConfiguration
{
    CmdLineConfiguration( const int argc, char** argv )
    : m_Argc( argc ), m_Argv( argv )
    {}

    bool isInitialized() const
    {
        return m_Argc != 0 && m_Argv != 0;
    }

    //////////////////////////
    // member variables
    //////////////////////////
    int    m_Argc;
    char** m_Argv;
};

} // end namespace cmdLine
} // end namespace libBatch

#endif // end GUARD_LIBBATCH_CMDLINE_CONFIGURATION_H
