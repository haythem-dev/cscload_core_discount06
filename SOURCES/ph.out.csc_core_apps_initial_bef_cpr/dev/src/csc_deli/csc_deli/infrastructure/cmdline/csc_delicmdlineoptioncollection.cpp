//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "csc_delicmdlineoptioncollection.h"
#include "csc_delicmdlineoption_definitions.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace csc_deli
{
namespace infrastructure
{
namespace cmdLine
{
    CSC_DELICmdLineOptionCollection::CSC_DELICmdLineOptionCollection()
    {
        getOptions().insert( OptionCollection::value_type( CSC_DELI_OPTION, "This is the text for the csc_delioption." ) );
    }

    CSC_DELICmdLineOptionCollection::~CSC_DELICmdLineOptionCollection()
    {
    }

    basar::VarString CSC_DELICmdLineOptionCollection::getUsageText() const
    {
        return basar::VarString( "CSC_DELI TEXT '") + libutil::infrastructure::cmdLine::USAGE + "'!";
    }

    basar::VarString CSC_DELICmdLineOptionCollection::getVersionText() const
    {
        return basar::VarString( "CSC_DELI TEXT '") + libutil::infrastructure::cmdLine::VERSION + "'!";
    }

    basar::VarString CSC_DELICmdLineOptionCollection::getHelpText() const
    {
        return basar::VarString( "CSC_DELI TEXT '") + libutil::infrastructure::cmdLine::HELP + "'!";
    }

    basar::VarString CSC_DELICmdLineOptionCollection::getVersionHistorieText() const
    {
        return basar::VarString( "CSC_DELI TEXT '") + libutil::infrastructure::cmdLine::VH + "'!";
    }

    basar::VarString CSC_DELICmdLineOptionCollection::getReturnValuesText() const
    {
        return basar::VarString( "CSC_DELI TEXT '") + libutil::infrastructure::cmdLine::RETURN_VALUES + "'!";
    }

} // end namespace cmdLine
} // end namespace infrastructure
} // end namespace csc_deli
