#include <stockbooking/componentmanager/stockbookingcomponentmanager.h>

#include <stockbooking/reservationconfig/reservationconfigrepositoryptr.h>
#include <stockbooking/reservationconfig/reservationconfigrepository.h>

#include <stockbooking/reservation/reservationrepositoryptr.h>
#include <stockbooking/reservation/reservationrepository.h>

#include <stockbooking/bulkrangeselector/bulkrangeselector.h>
#include <stockbooking/bulkrangeselector/bulkrangeselectorptr.h>
#include <stockbooking/longtermlack/longtermlackrepository.h>

#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>
#include <parameter/branchparametergetter.h>


namespace libcsc {
namespace stockbooking {

StockBookingComponentManager::StockBookingComponentManager()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::StockBookingComponentManager()" );
}

StockBookingComponentManager::~StockBookingComponentManager()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::~StockBookingComponentManager()" );
}

void StockBookingComponentManager::injectConnection( persistence::ConnectionPtr connection )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::injectConnection()" );

	m_Connection = connection;
}

void StockBookingComponentManager::injectTransactionHandler (nDataBase * transHandler)
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::injectTransactionHandler()" );

	m_TransactionHandler = transHandler;
}

void StockBookingComponentManager::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
{
	m_BranchParameterGetter = parameterGetter;
}


libcsc::persistence::TransactionGuard StockBookingComponentManager::createTransaction() const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::createTransaction()" );

	return persistence::TransactionGuard( m_TransactionHandler );
}


IReservationConfigRepositoryPtr StockBookingComponentManager::getReservationConfigRepository() const
{
	BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::getReservationConfigRepository()");

	if (NULL == m_ReservationConfigRepository.get())
	{
		m_ReservationConfigRepository = createReservationConfigRepository();
	}
	return m_ReservationConfigRepository;
}

IReservationRepositoryPtr StockBookingComponentManager::getReservationRepository(pxSession * session)
{
	BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::getReservationRepository()");

	if (NULL == m_ReservationRepository.get())
	{
		m_ReservationRepository = createReservationRepository(session);
	}
	return m_ReservationRepository;
}

IBulkRangeSelectorPtr StockBookingComponentManager::getBulkRangeSelector() const
{
	BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::getBulkRangeSelector()");

	if (NULL == m_BulkRangeSelector.get())
	{
		m_BulkRangeSelector = createBulkRangeSelector();
	}
	return m_BulkRangeSelector;
}

LongTermLackRepositoryPtr StockBookingComponentManager::createLongTermLackRepository() const
{
    LongTermLackRepositoryPtr ptr( boost::make_shared< LongTermLackRepository >() );
    ptr->injectCheckerLongTermLackAccessor( createAccessor() );
    ptr->injectDeleteLongTermLackAccessor ( createAccessor() );
        
    return ptr;
}

LongTermLackRepositoryPtr StockBookingComponentManager::getLongTermLackRepository() const
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::getLongTermLackRepository()");
    
    if( NULL == m_LongTermLackRepository.get() )
    {
        m_LongTermLackRepository = createLongTermLackRepository();
    }
 
    return m_LongTermLackRepository;
}

ILongTermLackCheckerPtr StockBookingComponentManager::getLongTermLackChecker() const
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::getLongTermLackChecker()");

    return getLongTermLackRepository();
}

ILongTermLackDeleterPtr StockBookingComponentManager::getLongTermLackDeleter() const
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::getLongTermLackDeleter()");

    return getLongTermLackRepository();
}

persistence::IAccessorPtr StockBookingComponentManager::createAccessor() const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "StockBookingComponentManager::createAccessor()" );
	return persistence::IAccessorPtr( new persistence::Accessor( m_Connection->getDbSqlConnection() ) );
}

IReservationConfigRepositoryPtr StockBookingComponentManager::createReservationConfigRepository() const
{
	ReservationConfigRepositoryPtr repo = boost::make_shared<ReservationConfigRepository>();
	repo->injectSelectReservationTypesAccessor(createAccessor());
	repo->injectSelectOrderTypesReservationConfigAccessor(createAccessor());
	repo->injectInsertOrderTypesReservationConfigAccessor(createAccessor());
	repo->injectUpdateOrderTypesReservationConfigAccessor(createAccessor());
	repo->injectDeleteOrderTypesReservationConfigAccessor(createAccessor());
	repo->injectSelectOrderTypesReservationConfigPharmacyGroupAccessor(createAccessor());
	repo->injectInsertOrderTypesReservationConfigPharmacyGroupAccessor(createAccessor());
	repo->injectDeleteOrderTypesReservationConfigPharmacyGroupAccessor(createAccessor());
	return repo;
}

IReservationRepositoryPtr StockBookingComponentManager::createReservationRepository( pxSession * session )
{
	ReservationRepositoryPtr repo = boost::make_shared<ReservationRepository>();
	repo->injectSelectArticleReservationAccessor(createAccessor());
	repo->injectInsertArticleReservationAccessor(createAccessor());
	repo->injectUpdateArticleReservationAccessor(createAccessor());
	repo->injectDeleteArticleReservationAccessor(createAccessor());
	repo->injectSelectCustomerStockReservedAccessor(createAccessor());
	repo->injectUpdateCustomerStockReservedAccessor(createAccessor());
	repo->injectDeleteCustomerStockReservedAccessor(createAccessor());
	repo->injectBranchParameterGetter( createBranchParameterGetter( session ) ); //m_BranchParameterGetter
	return repo;
}

parameter::IBranchParameterGetterPtr StockBookingComponentManager::createBranchParameterGetter( pxSession * session )
{
	return parameter::IBranchParameterGetterPtr( new parameter::BranchParameterGetter( session ) );
}

IBulkRangeSelectorPtr StockBookingComponentManager::createBulkRangeSelector() const
{
	BulkRangeSelectorPtr bulk = boost::make_shared<BulkRangeSelector>();
	bulk->injectSelectAccessor(createAccessor());
	return bulk;
}

//IBulkRangeSelectorPtr StockBookingComponentManager::createBulkRangeSelector() const
//{
//    BulkRangeSelectorPtr bulk = boost::make_shared<BulkRangeSelector>();
//    bulk->injectSelectAccessor(createAccessor());
//    return bulk;
//}


} // end namespace stockbooking
} // end namespace libcsc
