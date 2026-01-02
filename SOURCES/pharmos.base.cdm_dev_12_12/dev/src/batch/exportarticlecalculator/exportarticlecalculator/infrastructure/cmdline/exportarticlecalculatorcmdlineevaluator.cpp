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
#include "exportarticlecalculatorcmdlineevaluator.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace exportarticlecalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            EXPORTARTICLECALCULATORCmdLineEvaluator::EXPORTARTICLECALCULATORCmdLineEvaluator()
            {
            }

            bool EXPORTARTICLECALCULATORCmdLineEvaluator::doEvaluate()
            {
                AppArgs& appArgs = getAppArgs();

                getCmdLineParser()->getMandatoryInt16    ( "-branchno", appArgs.m_BranchNo );
				getCmdLineParser()->getMandatoryVarString( "-country",  appArgs.m_Country );
				getCmdLineParser()->getMandatoryInt32    ( "-datefrom", appArgs.m_DateFrom );
                getCmdLineParser()->getMandatoryVarString( "-username", appArgs.m_UserName );
                getCmdLineParser()->getMandatoryVarString( "-password", appArgs.m_Passwd   );

                return true;
            }
        } // end namespace cmdLine
    } // end namespace infrastructure
} // end namespace ibtrelevantcalculator
