//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "mainwarehousearticlesrelevantcalculatorcmdlineoptioncollection.h"
#include "mainwarehousearticlesrelevantcalculatorcmdlineoption_definitions.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace cmdLine
{

    MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection::MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection()
    {
        getOptions().insert( OptionCollection::value_type( MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_OPTION, "This is the text for the mainwarehousearticlesrelevantcalculatoroption." ) );
    }

    MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection::~MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection()
    {
    }

    basar::VarString MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection::getUsageText() const
    {
        return basar::VarString( "MAINWAREHOUSEARTICLESRELEVANTCALCULATOR TEXT '") + libutil::infrastructure::cmdLine::USAGE + "'!";
    }

    basar::VarString MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection::getVersionText() const
    {
        return basar::VarString( "MAINWAREHOUSEARTICLESRELEVANTCALCULATOR TEXT '") + libutil::infrastructure::cmdLine::VERSION + "'!";
    }

    basar::VarString MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection::getHelpText() const
    {
        return basar::VarString( "MAINWAREHOUSEARTICLESRELEVANTCALCULATOR TEXT '") + libutil::infrastructure::cmdLine::HELP + "'!";
    }

    basar::VarString MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection::getVersionHistorieText() const
    {
        return basar::VarString( "MAINWAREHOUSEARTICLESRELEVANTCALCULATOR TEXT '") + libutil::infrastructure::cmdLine::VH + "'!";
    }

    basar::VarString MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineOptionCollection::getReturnValuesText() const
    {
        return basar::VarString( "MAINWAREHOUSEARTICLESRELEVANTCALCULATOR TEXT '") + libutil::infrastructure::cmdLine::RETURN_VALUES + "'!";
    }

} // end namespace cmdLine
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

