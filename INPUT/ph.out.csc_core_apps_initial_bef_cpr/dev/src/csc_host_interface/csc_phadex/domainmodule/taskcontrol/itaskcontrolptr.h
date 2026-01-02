#ifndef GUARD_CSC_PHADEX_DOMMOD_I_TASK_CONTROL_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_I_TASK_CONTROL_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
	class ITaskControl;
	typedef boost::shared_ptr< ITaskControl > ITaskControlPtr;

} // end namespace domMod
} // end namespace csc_phadex

#endif // GUARD_CSC_PHADEX_DOMMOD_I_TASK_CONTROL_PTR_H
