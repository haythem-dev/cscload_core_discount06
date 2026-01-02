//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       20.08.2010
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "csc_phadexcmdlineoptioncollection.h"
#include "csc_phadexcmdlineoption_definitions.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace csc_phadex
{
    namespace infrastructure
    {
        namespace cmdLine
        {

            CscPhadexCmdLineOptionCollection::CscPhadexCmdLineOptionCollection()
            {
                getOptions().insert( OptionCollection::value_type( CSC_PHADEX_OPTION, "This is the text for the csc_phadexoption." ) );
            }

            CscPhadexCmdLineOptionCollection::~CscPhadexCmdLineOptionCollection()
            {
            }

            basar::VarString CscPhadexCmdLineOptionCollection::getUsageText() const
            {
                return basar::VarString( "CSC_PHADEX TEXT '") + libutil::infrastructure::cmdLine::USAGE + "'!";
            }

            basar::VarString CscPhadexCmdLineOptionCollection::getVersionText() const
            {
                return basar::VarString( "CSC_PHADEX TEXT '") + libutil::infrastructure::cmdLine::VERSION + "'!";
            }

            basar::VarString CscPhadexCmdLineOptionCollection::getHelpText() const
            {
                return basar::VarString( "CSC_PHADEX TEXT '") + libutil::infrastructure::cmdLine::HELP + "'!";
            }

            basar::VarString CscPhadexCmdLineOptionCollection::getVersionHistorieText() const
            {
                return basar::VarString( "CSC_PHADEX TEXT '") + libutil::infrastructure::cmdLine::VH + "'!";
            }

            basar::VarString CscPhadexCmdLineOptionCollection::getReturnValuesText() const
            {
                return basar::VarString( "CSC_PHADEX TEXT '") + libutil::infrastructure::cmdLine::RETURN_VALUES + "'!";
            }

        } // end namespace cmdLine
    } // end namespace infrastructure
} // end namespace csc_phadex
