#ifndef GUARD_LIBCSC_SUD_I_WORKUP_COMPLETED_CHECKER_H
#define GUARD_LIBCSC_SUD_I_WORKUP_COMPLETED_CHECKER_H


#include <libbasar_definitions.h>

namespace libcsc
{
namespace sud
{
class IWorkupCompletedChecker
{
public:
	virtual ~IWorkupCompletedChecker() {}	

	virtual bool isSUDWorkupCompleted( const basar::Int32 orderNo, const basar::Int32 customerNo, const basar::Int32 orderLineNo = 0 ) const = 0;
};

} // end namespace sud
} // end namespace libcsc

#endif // GUARD_LIBCSC_SUD_I_WORKUP_COMPLETED_CHECKER_H
