#ifndef GUARD_LIBCSC_STOCKBOOKING_COMPONENT_MANAGER_H
#define GUARD_LIBCSC_STOCKBOOKING_COMPONENT_MANAGER_H

#include <boost/enable_shared_from_this.hpp>
#include <persistence/itransactionfactory.h>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>
#include <parameter/ibranchparametergetterptr.h>

#include <stockbooking/reservationconfig/ireservationconfigrepositoryptr.h>
#include <stockbooking/reservation/ireservationrepositoryptr.h>
#include <stockbooking/bulkrangeselector/ibulkrangeselectorptr.h>

#include <stockbooking/longtermlack/ilongtermlackcheckerptr.h>
#include <stockbooking/longtermlack/ilongtermlackdeleterptr.h>
#include <stockbooking/longtermlack/longtermlackrepositoryptr.h>

class pxSession;

namespace libcsc {
namespace stockbooking {

class StockBookingComponentManager : public persistence::ITransactionFactory,
							 public boost::enable_shared_from_this<StockBookingComponentManager>
{
public:
	StockBookingComponentManager();
	virtual ~StockBookingComponentManager();

	void injectConnection( persistence::ConnectionPtr connection );
	void injectTransactionHandler (nDataBase * transHandler);
	void injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter);

	virtual libcsc::persistence::TransactionGuard	createTransaction() const;

	IReservationConfigRepositoryPtr				getReservationConfigRepository() const;
	IReservationRepositoryPtr					getReservationRepository(pxSession * session);
	IBulkRangeSelectorPtr						getBulkRangeSelector() const;
    ILongTermLackCheckerPtr                     getLongTermLackChecker() const;
    ILongTermLackDeleterPtr                     getLongTermLackDeleter() const;

private:
	StockBookingComponentManager( const StockBookingComponentManager & );
	StockBookingComponentManager & operator=( const StockBookingComponentManager & );

    LongTermLackRepositoryPtr                   getLongTermLackRepository() const;

	persistence::IAccessorPtr					createAccessor() const;
	IReservationConfigRepositoryPtr				createReservationConfigRepository() const;
	IReservationRepositoryPtr					createReservationRepository(pxSession * session) ;
	IBulkRangeSelectorPtr						createBulkRangeSelector() const;
	parameter::IBranchParameterGetterPtr		createBranchParameterGetter( pxSession * session );
    LongTermLackRepositoryPtr                   createLongTermLackRepository() const;

	persistence::ConnectionPtr					m_Connection;
	nDataBase *									m_TransactionHandler;

	mutable IReservationConfigRepositoryPtr		m_ReservationConfigRepository;
	mutable IReservationRepositoryPtr			m_ReservationRepository;
	mutable IBulkRangeSelectorPtr				m_BulkRangeSelector;
    mutable LongTermLackRepositoryPtr           m_LongTermLackRepository;

	parameter::IBranchParameterGetterPtr		m_BranchParameterGetter;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif //end GUARD_LIBCSC_STOCKBOOKING_COMPONENT_MANAGER_H
