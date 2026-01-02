//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "mainwarehousearticlesrelevantcalculatorcmdlineevaluator.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace cmdLine
{
    MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator::MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator()
    {
    }

    bool MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator::doEvaluate()
    {
        AppArgs& appArgs = getAppArgs();

        getCmdLineParser()->getMandatoryInt16    ( "-branchno", appArgs.m_BranchNo );
        return true;
    }
} // end namespace cmdLine
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator
