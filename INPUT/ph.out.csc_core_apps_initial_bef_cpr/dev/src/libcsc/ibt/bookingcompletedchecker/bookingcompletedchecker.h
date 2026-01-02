#ifndef GUARD_LIBCSC_IBT_BOOKING_COMPLETED_CHECKER_H
#define GUARD_LIBCSC_IBT_BOOKING_COMPLETED_CHECKER_H

#include <ibt/bookingcompletedchecker/ibookingcompletedchecker.h>
#include <persistence/iaccessorptr.h>

namespace libcsc
{
namespace ibt
{
class BookingCompletedChecker : public IBookingCompletedChecker
{
public:
	BookingCompletedChecker();
	virtual ~BookingCompletedChecker();

	void injectSelectAccessor( persistence::IAccessorPtr accessor );		

	virtual bool isIBTBookingCompleted( const basar::Int16 branchNo, const basar::Int32 orderNo/*, const basar::Int32 orderLineNo = 0*/) const;

private:

	//basar::VarString getRemoteDbIfNecessary( const basar::Int16 branchNo, const basar::Int32 orderNo ) const;

	persistence::IAccessorPtr			m_SelectAccessor;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_BOOKING_COMPLETED_CHECKER_H
