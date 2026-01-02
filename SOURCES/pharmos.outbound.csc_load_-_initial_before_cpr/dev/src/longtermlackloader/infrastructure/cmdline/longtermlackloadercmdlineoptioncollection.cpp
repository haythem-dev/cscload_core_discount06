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
#include "longtermlackloadercmdlineoptioncollection.h"
#include "longtermlackloadercmdlineoption_definitions.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace cmdLine
        {

            LONGTERMLACKLOADERCmdLineOptionCollection::LONGTERMLACKLOADERCmdLineOptionCollection()
            {
                getOptions().insert( OptionCollection::value_type( LONGTERMLACKLOADER_OPTION, "This is the text for the longtermlackloaderoption." ) );
            }

            LONGTERMLACKLOADERCmdLineOptionCollection::~LONGTERMLACKLOADERCmdLineOptionCollection()
            {
            }

            basar::VarString LONGTERMLACKLOADERCmdLineOptionCollection::getUsageText() const
            {
                return basar::VarString( "LONGTERMLACKLOADER TEXT '") + libutil::infrastructure::cmdLine::USAGE + "'!";
            }

            basar::VarString LONGTERMLACKLOADERCmdLineOptionCollection::getVersionText() const
            {
                return basar::VarString( "LONGTERMLACKLOADER TEXT '") + libutil::infrastructure::cmdLine::VERSION + "'!";
            }

            basar::VarString LONGTERMLACKLOADERCmdLineOptionCollection::getHelpText() const
            {
                //return basar::VarString( "LONGTERMLACKLOADER TEXT '") + libutil::infrastructure::cmdLine::HELP + "'!";
                return libutil::infrastructure::cmdLine::CmdLineOptionCollectionBase::getHelpText() + 
						basar::VarString( "LONGTERMLACKLOADER TEXT '") + libutil::infrastructure::cmdLine::HELP + "'!";
            }

            basar::VarString LONGTERMLACKLOADERCmdLineOptionCollection::getVersionHistorieText() const
            {
                //return basar::VarString( "LONGTERMLACKLOADER TEXT '") + libutil::infrastructure::cmdLine::VERSION_HISTORY + "'!";
                return "";
            }

            basar::VarString LONGTERMLACKLOADERCmdLineOptionCollection::getReturnValuesText() const
            {
                return basar::VarString( "LONGTERMLACKLOADER TEXT '") + libutil::infrastructure::cmdLine::RETURN_VALUES + "'!";
            }

        } // end namespace cmdLine
    } // end namespace infrastructure
} // end namespace longtermlackloader
