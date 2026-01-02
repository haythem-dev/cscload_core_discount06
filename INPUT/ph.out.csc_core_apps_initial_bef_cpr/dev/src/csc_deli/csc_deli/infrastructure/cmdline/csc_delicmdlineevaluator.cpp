//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "csc_delicmdlineevaluator.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace csc_deli
{
namespace infrastructure
{
namespace cmdLine
{
    CSC_DELICmdLineEvaluator::CSC_DELICmdLineEvaluator()
    {
    }

    bool CSC_DELICmdLineEvaluator::doEvaluate()
    {
        AppArgs& appArgs = getAppArgs();

        getCmdLineParser()->getMandatoryVarString( "-country",     appArgs.m_CountryCode );

        return true;
    }
} // end namespace cmdLine
} // end namespace infrastructure
} // end namespace csc_deli
