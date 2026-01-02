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
#include "longtermlackloadercmdlineevaluator.h"
#include <libutil/exception.h>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            LONGTERMLACKLOADERCmdLineEvaluator::LONGTERMLACKLOADERCmdLineEvaluator()
            {
            }

            bool LONGTERMLACKLOADERCmdLineEvaluator::doEvaluate()
            {
                /*try
                {*/
                    AppArgs& appArgs = getAppArgs();
                    getCmdLineParser()->getMandatoryInt16    ( "-areaid",   appArgs.m_AreaID   ) ;
                    getCmdLineParser()->getMandatoryVarString( "-user",     appArgs.m_UserName );
                    getCmdLineParser()->getMandatoryVarString( "-password", appArgs.m_Passwd   ) ;
                    
                /*}
                catch( libutil::exceptions::CmdLineException& e )
                {
                    libutil::exceptions::ExceptionHandler::processBasarException(e, getLogger(), fun, __FILE__, __LINE__);
                    throw;
                }*/
                return true;

            }
        }
    }
}
