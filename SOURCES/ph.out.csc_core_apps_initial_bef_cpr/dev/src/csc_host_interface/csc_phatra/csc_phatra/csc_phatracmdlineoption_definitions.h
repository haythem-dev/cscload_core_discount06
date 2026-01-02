//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       23.12.2010
 *  \version    00.00.00.01
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHATRA_CMDLINE_COMMAND_LINE_DEFINITIONS_H
#define GUARD_CSC_PHATRA_CMDLINE_COMMAND_LINE_DEFINITIONS_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace csc_phatra 
{
namespace cmdLine
{
    static basar::ConstString BRANCHNO                    = "-branchno";
	static basar::ConstString CONFIGFILE				  = "-configfile";
    static basar::ConstString TESTING                     = "-testing";
    static basar::ConstString NO_MAIL                     = "-nomail";
    static basar::ConstString EXTENDED_LOGGING            = "-extlog";
} // end namespace commandLine

} // end namespace csc_phatra

#endif // end GUARD_CSC_PHATRA_COMMAND_LINE_DEFINITIONS_H

