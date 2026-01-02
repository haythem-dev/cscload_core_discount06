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
#include "loadcontractshrcmdlineevaluator.h"

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace loadcontractshr
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            LoadContractsHrCmdLineEvaluator::LoadContractsHrCmdLineEvaluator()
            {
            }

            bool LoadContractsHrCmdLineEvaluator::doEvaluate()
            {
                AppArgs& appArgs = getAppArgs();

				getCmdLineParser()->getVarString("-mode", appArgs.m_Mode);
                getCmdLineParser()->getMandatoryVarString( "-path", appArgs.m_Path );
                getCmdLineParser()->getMandatoryVarString( "-username", appArgs.m_UserName );
                getCmdLineParser()->getMandatoryVarString( "-password", appArgs.m_Passwd   );

                return true;
            }
        } // end namespace cmdLine
    } // end namespace infrastructure
} // end namespace loadcontractshr

