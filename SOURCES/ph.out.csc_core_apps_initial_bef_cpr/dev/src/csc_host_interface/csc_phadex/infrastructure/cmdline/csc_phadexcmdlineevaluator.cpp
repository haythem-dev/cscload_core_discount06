#include "csc_phadexcmdlineevaluator.h"

namespace csc_phadex
{
namespace infrastructure
{
namespace cmdLine
{
CscPhadexCmdLineEvaluator::CscPhadexCmdLineEvaluator()
{
}

bool CscPhadexCmdLineEvaluator::doEvaluate()
{
	AppArgs & appArgs = getAppArgs();
	getCmdLineParser()->getMandatoryVarString( "-country", appArgs.country );
	getCmdLineParser()->getMandatoryInt16( "-branchno", appArgs.branchNo );
	getCmdLineParser()->getMandatoryVarString( "-configFile", appArgs.configFile );

	//getCmdLineParser()->getMandatoryVarString( "-user",     appArgs.m_UserName );
	//getCmdLineParser()->getMandatoryVarString( "-password", appArgs.m_Passwd   );

	return true;
}
} // end namespace cmdLine
} // end namespace infrastructure
} // end namespace csc_phadex
