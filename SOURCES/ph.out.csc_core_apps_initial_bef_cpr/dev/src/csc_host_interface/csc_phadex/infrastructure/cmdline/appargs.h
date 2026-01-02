#ifndef GUARD_CSC_PHADEX_INFRASTRUCTURE_CMDLINE_APP_ARGS_H
#define GUARD_CSC_PHADEX_INFRASTRUCTURE_CMDLINE_APP_ARGS_H

namespace csc_phadex
{
namespace infrastructure
{
namespace cmdLine
{
class AppArgs
{
public:
	AppArgs()
	: country( "" ), branchNo( 0 ), configFile( "" )
	{
	}

	basar::VarString	country;
	basar::Int16		branchNo;
	basar::VarString	configFile;
};
}
}
}


#endif // GUARD_CSC_PHADEX_INFRASTRUCTURE_CMDLINE_APP_ARGS_H
