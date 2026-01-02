//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       24.12.2010
 *  \version    00.00.00.01
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHATRA_CMDLINE_APPARGS_N_H
#define GUARD_CSC_PHATRA_CMDLINE_APPARGS_N_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbatch_definitions.h>

#include <libbasarcmnutil.h>
#include <sstream>
#include <iomanip>

//--------------------------------------------------------------------------------------------------//
// class declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phatra
{
namespace cmdLine
{
struct AppArgs
{
    AppArgs()
    : m_CountryCode(::libBatch::STRING_UNSET ),
      m_BranchNo(::libBatch::NUMBER_UNSET ),
      m_ConfigFile(::libBatch::STRING_UNSET ),
      m_Testing(false),
      m_NoMail(false),
      m_ExtendedLogging(false)
    {
    }

    bool isInitialized() const
    {
        return !m_CountryCode.empty();
    }

    bool isCountryCodeValid() const
    {
        return !m_CountryCode.empty();
    }

    bool isBranchNoValid() const
    {
        return (   0 <= m_BranchNo
                && m_BranchNo < 100 );
    }

    bool isConfigFileValid() const
    {
        return !m_ConfigFile.empty();
    }

    std::ostream& toStream( std::ostream& strm = std::cout ) const
    {
        static basar::ConstString indentation = "\t";
        strm << "APPLICATION ARGUMENTS:" << std::endl;
        strm << indentation << "Branch number: <" << m_BranchNo << ">" << std::endl;
        strm << indentation << "Config file: <" << m_ConfigFile << ">" << std::endl;
        return strm;
    }

    basar::VarString    m_CountryCode;
    basar::Int16        m_BranchNo;
    basar::VarString    m_ConfigFile;
    bool                m_Testing;
    bool                m_NoMail;
    bool                m_ExtendedLogging;
};

} // end namespace cmdLine
} // end namespace csc_phatra

#include "appargs.inl"

#endif // end GUARD_CSC_PHATRA_CMDLINE_APPARGS_N_H

