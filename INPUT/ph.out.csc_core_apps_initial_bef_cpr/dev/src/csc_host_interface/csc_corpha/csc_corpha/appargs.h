//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Bjoern Bischof
 *  \date       24.12.2010
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_CORPHA_CMDLINE_APPARGS_N_H
#define GUARD_CSC_CORPHA_CMDLINE_APPARGS_N_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbatch_definitions.h>

#include <libbasarcmnutil.h>
#include <sstream>
#include <iomanip>

#include "csc_corphacmdlineoption_definitions.h"

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_corpha
{
namespace cmdLine
{
struct AppArgs
{
    AppArgs()
    : m_CountryCode(::libBatch::STRING_UNSET ),
      m_BranchNo(::libBatch::NUMBER_UNSET ),
      m_ConfigFile(::libBatch::STRING_UNSET ),
      m_OrderFilter( cmdLine::ORDERFILTER_ALL ),
      m_Testing( false ),
      m_NoMail( false ),
      m_ExtendedLogging( false )
    {
    }

    bool isInitialized() const
    {
        return ( !m_CountryCode.empty() );
    }

    bool isCountryCodeValid() const
    {
        return ( !m_CountryCode.empty() );
    }

   bool isOrderFilterValid() const
   {
    if( cmdLine::ORDERFILTER_ALL == m_OrderFilter || cmdLine::ORDERFILTER_EVEN == m_OrderFilter || cmdLine::ORDERFILTER_ODD == m_OrderFilter )
    {
        return true;
    }
    return false;
   }

   bool isBranchNoValid() const
   {
        return ( 0 < m_BranchNo && m_BranchNo < 100 );
   }

   bool isConfigFileValid() const
   {
        return ( !m_ConfigFile.empty() );
   }

   std::ostream& toStream( std::ostream& strm = std::cout ) const
   {
        static basar::ConstString indentation = "\t";
        strm << "APPLICATION ARGUMENTS:" << std::endl;
        strm << indentation << "Country code: <" << m_CountryCode << ">" << std::endl;
        strm << indentation << "Branch number: <" << m_BranchNo << ">" << std::endl;
        strm << indentation << "Config file: <" << m_ConfigFile << ">" << std::endl;
        strm << indentation << "Order Filter: <" << m_OrderFilter << ">" << std::endl;
        if( m_Testing )
        {
            strm << indentation << "Test Mode" << std::endl;
        }
        if( m_NoMail )
        {
            strm << indentation << "NoMail Mode" << std::endl;
        }
        if( m_ExtendedLogging )
        {
            strm << indentation << "extended logging activated" << std::endl;
        }
        return strm;
    }

    basar::VarString    m_CountryCode;
    basar::Int16        m_BranchNo;
    basar::VarString    m_ConfigFile;
    basar::VarString    m_OrderFilter;
    bool m_Testing;
    bool m_NoMail;
    bool m_ExtendedLogging;
};

} // end namespace cmdLine
} // end namespace csc_corpha

#include "appargs.inl"

#endif // end GUARD_CSC_CORPHA_CMDLINE_APPARGS_N_H
