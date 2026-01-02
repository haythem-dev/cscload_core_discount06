//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      declaration of abstract connection base class
 *  \author     Bischof Bjoern
 *  \date       27.01.2009
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBBATCH_CMDLINE_OPTION_H
#define GUARD_LIBBATCH_CMDLINE_OPTION_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include <libbasarcmnutil.h>


//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace libBatch 
{
namespace cmdLine
{
//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
class CmdLineOption
{
    public:
        CmdLineOption( const basar::VarString& );
        ~CmdLineOption();

        bool isOptionUsage()          const;
        bool isOptionVersion()        const;
        bool isOptionHelp()           const;
        bool isOptionVersionHistory() const;
        bool isOptionReturnValues()   const;

    private:
        ////////////////////////////////
        // methods
        ////////////////////////////////
        CmdLineOption( const CmdLineOption& );
        CmdLineOption& operator=( const CmdLineOption& );

        ////////////////////////////////
        // variables
        ////////////////////////////////
        const log4cplus::Logger&    m_Logger;
        const basar::VarString&     m_Option;
};

} // end namespace cmdLine
} // end namespace libBatch

#endif // end GUARD_LIBBATCH_CMDLINE_OPTION_H
