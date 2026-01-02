//--------------------------------------------------------------------------------------------------//
/*! \brief 
 *  \author     Bjoern Bischof
 *  \date       23.12.2010
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LIBBATCH_CMDLINE_DEFINITIONS_H
#define GUARD_LIBBATCH_CMDLINE_DEFINITIONS_H

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
    static basar::ConstString USAGE         = "-usage";
    static basar::ConstString VERSION       = "-version";
    static basar::ConstString HELP          = "-help";
    static basar::ConstString VH            = "-vh";
    static basar::ConstString RETURN_VALUES = "-return_values";

} // end namespace cmdLine
} // end namespace libBatch

#endif // end GUARD_LIBBATCH_CMDLINE_DEFINITIONS_H
