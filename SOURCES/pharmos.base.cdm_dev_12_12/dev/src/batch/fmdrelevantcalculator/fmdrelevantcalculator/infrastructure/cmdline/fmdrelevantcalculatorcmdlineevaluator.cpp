//--------------------------------------------------------------------------------------------------//
/*! \brief
 *  \author     Bjoern Bischof
 *  \date       22.12.2010
 *  \version    00.00.00.01
 */
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "fmdrelevantcalculatorcmdlineevaluator.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            FMDRELEVANTCALCULATORCmdLineEvaluator::FMDRELEVANTCALCULATORCmdLineEvaluator()
            {
            }

            bool FMDRELEVANTCALCULATORCmdLineEvaluator::doEvaluate()
            {
                AppArgs& appArgs = getAppArgs();

                getCmdLineParser()->getMandatoryInt16    ( "-branchno", appArgs.m_BranchNo );
                getCmdLineParser()->getMandatoryVarString( "-username", appArgs.m_UserName );
                getCmdLineParser()->getMandatoryVarString( "-password", appArgs.m_Passwd   );

                return true;
            }
        } // end namespace cmdLine
    } // end namespace infrastructure
} // end namespace fmdrelevantcalculator
