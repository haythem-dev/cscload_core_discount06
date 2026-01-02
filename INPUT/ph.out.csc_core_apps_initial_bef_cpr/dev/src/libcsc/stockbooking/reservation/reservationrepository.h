#ifndef GUARD_LIBCSC_STOCKBOOKING_RESERVATION_REPOSITORY_H
#define GUARD_LIBCSC_STOCKBOOKING_RESERVATION_REPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasarcmnutil_bstring.h>
#include <stockbooking/reservation/ireservationrepository.h>
#include <stockbooking/reservation/articlereservationptr.h>
#include <stockbooking/reservation/customerstockreservedptr.h>
#include <stockbooking/reservation/iarticlereservationptr.h>
#include <stockbooking/reservation/icustomerstockreservedptr.h>

#include <parameter/ibranchparametergetterptr.h>



namespace libcsc {
namespace stockbooking {

class ReservationRepository : public IReservationRepository
{
public:
	ReservationRepository();
    virtual ~ReservationRepository();

	virtual void injectSelectArticleReservationAccessor(persistence::IAccessorPtr accessor);
	virtual void injectInsertArticleReservationAccessor(persistence::IAccessorPtr accessor);
	virtual void injectUpdateArticleReservationAccessor(persistence::IAccessorPtr accessor);
	virtual void injectDeleteArticleReservationAccessor(persistence::IAccessorPtr accessor);

	virtual void injectSelectCustomerStockReservedAccessor(persistence::IAccessorPtr accessor);
	virtual void injectUpdateCustomerStockReservedAccessor(persistence::IAccessorPtr accessor);
	virtual void injectDeleteCustomerStockReservedAccessor(persistence::IAccessorPtr accessor);

	void injectBranchParameterGetter( parameter::IBranchParameterGetterPtr parameterGetter );

	virtual IArticleReservationCollectionPtr		findArticleReservation( const basar::Int16& branchNo, const basar::Int32 articleNo );
	virtual void									saveArticleReservation(IArticleReservationPtr reservation);
	virtual void									deleteArticleReservation(IArticleReservationPtr reservation);

	virtual ICustomerStockReservedCollectionPtr		findCustomerStockReserved( const basar::Int16& branchNo, const basar::Int32 articleNo );
	virtual void									saveCustomerStockReserved(ICustomerStockReservedPtr customerStockReserved);
	virtual void									deleteCustomerStockReserved(ICustomerStockReservedPtr customerStockReserved);


private:

	ReservationRepository& operator=(const ReservationRepository&);

	persistence::IAccessorPtr m_SelectArticleReservationAccessor;
	persistence::IAccessorPtr m_InsertArticleReservationAccessor;
	persistence::IAccessorPtr m_UpdateArticleReservationAccessor;
	persistence::IAccessorPtr m_DeleteArticleReservationAccessor;

	persistence::IAccessorPtr m_SelectCustomerStockReservedAccessor;
	persistence::IAccessorPtr m_UpdateCustomerStockReservedAccessor;
	persistence::IAccessorPtr m_DeleteCustomerStockReservedAccessor;

	parameter::IBranchParameterGetterPtr m_BranchParameterGetter;


};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_RESERVATION_REPOSITORY_H
