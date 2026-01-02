#ifndef GUARD_CSC_PHADEX_INFRASTRUCTURE_CMDLINE_CSC_PHADEXCMDLINEEVALUATOR_H
#define GUARD_CSC_PHADEX_INFRASTRUCTURE_CMDLINE_CSC_PHADEXCMDLINEEVALUATOR_H

#include <libutil/cmdline.h>
#include "csc_phadexcmdlineoptioncollection.h"
#include "appargs.h"

namespace csc_phadex
{
namespace infrastructure
{
namespace cmdLine
{
class CscPhadexCmdLineEvaluator : public libutil::infrastructure::cmdLine::CmdLineEvaluatorBase<
											AppArgs, 
											csc_phadex::infrastructure::cmdLine::CscPhadexCmdLineOptionCollection
												>
{
public:
	CscPhadexCmdLineEvaluator();

private:
	virtual bool doEvaluate();

	CscPhadexCmdLineEvaluator( CscPhadexCmdLineEvaluator& );
	CscPhadexCmdLineEvaluator& operator=( CscPhadexCmdLineEvaluator& );
};
}
}
}

#endif
