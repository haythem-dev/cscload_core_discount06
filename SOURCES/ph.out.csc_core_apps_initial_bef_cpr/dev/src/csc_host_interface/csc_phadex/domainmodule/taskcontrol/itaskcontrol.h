#ifndef GUARD_CSC_PHADEX_DOMMOD_I_TASK_CONTROL_H
#define GUARD_CSC_PHADEX_DOMMOD_I_TASK_CONTROL_H

#include <libbasar_definitions.h>

namespace csc_phadex
{
namespace domMod
{
class ITaskControl
{
public:
	virtual ~ITaskControl() {};
	virtual void heartBeat( const basar::Int16 branchno, const basar::VarString & applicationName ) = 0;
	virtual void heartBeat() = 0;
};

} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_TASK_CONTROL_H
