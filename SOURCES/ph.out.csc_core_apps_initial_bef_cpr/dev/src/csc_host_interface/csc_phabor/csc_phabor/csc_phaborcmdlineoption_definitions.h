//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       23.12.2010
 *  \version    00.00.00.01
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHABOR_CMDLINE_COMMAND_LINE_DEFINITIONS_H
#define GUARD_CSC_PHABOR_CMDLINE_COMMAND_LINE_DEFINITIONS_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace csc_phabor 
{
namespace cmdLine
{
    static basar::ConstString COUNTRY                     = "-country";
    static basar::ConstString BRANCHNO                    = "-branchno";
	static basar::ConstString CONFIGFILE				  = "-configfile";
	static basar::ConstString EXTENDED_LOGGING            = "-extlog";
	static basar::ConstString TRANSFER                    = "-transfer";
	static basar::ConstString PROCESS                     = "-process";
	static basar::ConstString TESTING                     = "-testing";
	static basar::ConstString NOMAIL                      = "-nomail";
} // end namespace commandLine

} // end namespace csc_phabor

#endif // end GUARD_CSC_PHABOR_COMMAND_LINE_DEFINITIONS_H
