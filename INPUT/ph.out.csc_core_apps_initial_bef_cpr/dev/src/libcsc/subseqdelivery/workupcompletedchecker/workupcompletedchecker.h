#ifndef GUARD_LIBCSC_SUD_WORKUP_COMPLETED_CHECKER_H
#define GUARD_LIBCSC_SUD_WORKUP_COMPLETED_CHECKER_H

#include <subseqdelivery/workupcompletedchecker/iworkupcompletedchecker.h>
#include <persistence/iaccessorptr.h>

namespace libcsc
{
namespace sud
{
class WorkupCompletedChecker : public IWorkupCompletedChecker
{
public:
	WorkupCompletedChecker();
	virtual ~WorkupCompletedChecker();

	void injectSelectAccessor( persistence::IAccessorPtr accessor );		

	virtual bool isSUDWorkupCompleted( const basar::Int32 orderNo, const basar::Int32 customerNo, const basar::Int32 orderLineNo = 0 ) const;

private:

	persistence::IAccessorPtr			m_SelectAccessor;
};

} // end namespace sud
} // end namespace libcsc

#endif // GUARD_LIBCSC_SUD_WORKUP_COMPLETED_CHECKER_H
