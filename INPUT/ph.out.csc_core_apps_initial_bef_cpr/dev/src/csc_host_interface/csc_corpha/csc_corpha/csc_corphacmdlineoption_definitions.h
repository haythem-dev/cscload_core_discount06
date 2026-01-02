//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       23.12.2010
 *  \version    00.00.00.01
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_Corpha_CMDLINE_COMMAND_LINE_DEFINITIONS_H
#define GUARD_CSC_Corpha_CMDLINE_COMMAND_LINE_DEFINITIONS_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include <libbasarcmnutil.h>

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace csc_corpha 
{
namespace cmdLine
{
    static basar::ConstString COUNTRY                     = "-country";
    static basar::ConstString BRANCHNO                    = "-branchno";
	static basar::ConstString CONFIGFILE				  = "-configfile";
	static basar::ConstString ORDERFILTER				  = "-orderfilter";
	static basar::ConstString TESTING					  = "-test";
	static basar::ConstString NOMAIL					  = "-nomail";	
	static basar::ConstString EXTENDEDLOGGING			  = "-extendedlogging";

	static basar::ConstString ORDERFILTER_ODD			  = "odd";
	static basar::ConstString ORDERFILTER_EVEN			  = "even";
	static basar::ConstString ORDERFILTER_ALL			  = "all";

} // end namespace commandLine

} // end namespace csc_corpha

#endif // end GUARD_CSC_Corpha_COMMAND_LINE_DEFINITIONS_H
