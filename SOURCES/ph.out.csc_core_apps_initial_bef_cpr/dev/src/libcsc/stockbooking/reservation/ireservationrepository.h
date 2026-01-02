#ifndef GUARD_LIBCSC_STOCKBOOKING_I_RESERVATION_REPOSITORY_H
#define GUARD_LIBCSC_STOCKBOOKING_I_RESERVATION_REPOSITORY_H

#include <libbasarcmnutil_bstring.h>

#include <stockbooking/reservation/iarticlereservationptr.h>
#include <stockbooking/reservation/icustomerstockreservedptr.h>


namespace libcsc {
namespace stockbooking {

class IReservationRepository
{
public:
    virtual ~IReservationRepository() {}

	virtual IArticleReservationCollectionPtr		findArticleReservation( const basar::Int16& branchNo, const basar::Int32 articleNo ) = 0;
	virtual void									saveArticleReservation(IArticleReservationPtr reservation) = 0;
	virtual void									deleteArticleReservation(IArticleReservationPtr reservation) = 0;

	virtual ICustomerStockReservedCollectionPtr		findCustomerStockReserved( const basar::Int16& branchNo, const basar::Int32 articleNo ) = 0;
	virtual void									saveCustomerStockReserved(ICustomerStockReservedPtr customerStockReserved) = 0;
	virtual void									deleteCustomerStockReserved(ICustomerStockReservedPtr customerStockReserved) = 0;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_RESERVATION_REPOSITORY_H
