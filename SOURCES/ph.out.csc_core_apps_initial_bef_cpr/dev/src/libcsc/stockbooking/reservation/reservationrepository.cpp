#include "reservationrepository.h"
#include <stockbooking/reservation/articlereservationsqlmapper.h>
#include <stockbooking/reservation/articlereservation.h>
#include <stockbooking/reservation/customerstockreservedsqlmapper.h>
#include <stockbooking/reservation/customerstockreserved.h>
#include <persistence/iaccessor.h>
#include <logger/loggerpool.h>
#include <parameter/ibranchparametergetter.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace stockbooking {

ReservationRepository::ReservationRepository()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::ReservationRepository()");
}

ReservationRepository::~ReservationRepository()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::~ReservationRepository()");

	m_SelectArticleReservationAccessor.reset();
	m_InsertArticleReservationAccessor.reset();
	m_UpdateArticleReservationAccessor.reset();
	m_DeleteArticleReservationAccessor.reset();

	m_SelectCustomerStockReservedAccessor.reset();
	m_UpdateCustomerStockReservedAccessor.reset();
	m_DeleteCustomerStockReservedAccessor.reset();

}

void ReservationRepository::injectSelectArticleReservationAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::injectSelectArticleReservationAccessor()");
	m_SelectArticleReservationAccessor = accessor;
}

void ReservationRepository::injectInsertArticleReservationAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::injectInsertArticleReservationAccessor()");
	m_InsertArticleReservationAccessor = accessor;
}

void ReservationRepository::injectUpdateArticleReservationAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::injectUpdateArticleReservationAccessor()");
	m_UpdateArticleReservationAccessor = accessor;
}

void ReservationRepository::injectDeleteArticleReservationAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::injectDeleteArticleReservationAccessor()");
	m_DeleteArticleReservationAccessor = accessor;
}

void ReservationRepository::injectSelectCustomerStockReservedAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::injectSelectCustomerStockReservedAccessor()");
	m_SelectCustomerStockReservedAccessor = accessor;
}

void ReservationRepository::injectUpdateCustomerStockReservedAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::injectUpdateCustomerStockReservedAccessor()");
	m_UpdateCustomerStockReservedAccessor = accessor;
}

void ReservationRepository::injectDeleteCustomerStockReservedAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::injectDeleteCustomerStockReservedAccessor()");
	m_DeleteCustomerStockReservedAccessor = accessor;
}



IArticleReservationCollectionPtr ReservationRepository::findArticleReservation( const basar::Int16& branchNo, const basar::Int32 articleNo )
{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::findArticleReservation() collection");
		IArticleReservationCollectionPtr coll = boost::make_shared<IArticleReservationCollection>();
		try
		{
			basar::db::sql::ResultsetRef resultset = m_SelectArticleReservationAccessor->select( ArticleReservationSQLMapper::getSelectSQL( branchNo, articleNo ) );
			while (resultset.next())
			{
				ArticleReservationPtr articleReservation = boost::make_shared<ArticleReservation>();
				ArticleReservationSQLMapper mapper(articleReservation, resultset);
				mapper.map();
				coll->push_back(articleReservation);
			}
		}
		catch( basar::Exception & )
		{
			throw;
		}

		return coll;

}

void ReservationRepository::saveArticleReservation(IArticleReservationPtr articleReservation)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::saveArticleReservation()");
		if (articleReservation->isInsertable())
		{
			m_InsertArticleReservationAccessor->execute(ArticleReservationSQLMapper::getInsertSQL(articleReservation));
		}
		else if (articleReservation->isUpdatable())
		{
			m_UpdateArticleReservationAccessor->execute(ArticleReservationSQLMapper::getUpdateSQL(articleReservation));
		}
}

void ReservationRepository::deleteArticleReservation(IArticleReservationPtr articleReservation)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::deleteArticleReservation()");
	try
	{
		m_DeleteArticleReservationAccessor->execute( ArticleReservationSQLMapper::getDeleteSQL(articleReservation) );
	}
	catch (basar::Exception &)
	{
		throw;
	}
}

ICustomerStockReservedCollectionPtr ReservationRepository::findCustomerStockReserved( const basar::Int16& branchNo, const basar::Int32 articleNo )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::findCustomerStockReserved()");

		ICustomerStockReservedCollectionPtr coll = boost::make_shared<ICustomerStockReservedCollection>();
		try
		{
			basar::VarString databaseName = m_BranchParameterGetter->getDatabaseName( branchNo );
			basar::db::sql::ResultsetRef resultset = m_SelectCustomerStockReservedAccessor->select( CustomerStockReservedSQLMapper::getSelectSQL( databaseName, branchNo, articleNo ) );
			while (resultset.next())
			{
				CustomerStockReservedPtr customerStockReserved = boost::make_shared<CustomerStockReserved>();
				CustomerStockReservedSQLMapper mapper(customerStockReserved, resultset);
				mapper.map();
				coll->push_back(customerStockReserved);
			}
		}
		catch( basar::Exception & )
		{
			throw;
		}
		return coll;

}

void ReservationRepository::saveCustomerStockReserved(ICustomerStockReservedPtr customerStockReserved)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::saveCustomerStockReserved()");
	try
	{
		if (customerStockReserved->isUpdatable())
		{
			basar::VarString databaseName = m_BranchParameterGetter->getDatabaseName( customerStockReserved->getBranchNo() );
			m_UpdateArticleReservationAccessor->execute(CustomerStockReservedSQLMapper::getUpdateSQL(databaseName, customerStockReserved));
		}
	}
	catch (basar::Exception &)
	{
		throw;
	}
}

void ReservationRepository::deleteCustomerStockReserved(ICustomerStockReservedPtr customerStockReserved)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::deleteCustomerStockReserved()");
	try
	{
		basar::VarString databaseName = m_BranchParameterGetter->getDatabaseName( customerStockReserved->getBranchNo() );
		m_DeleteCustomerStockReservedAccessor->execute( CustomerStockReservedSQLMapper::getDeleteSQL(databaseName, customerStockReserved) );
	}
	catch (basar::Exception &)
	{
		throw;
	}

}

void ReservationRepository::injectBranchParameterGetter( parameter::IBranchParameterGetterPtr parameterGetter )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "ReservationRepository::injectBranchParameterGetter()");
	m_BranchParameterGetter = parameterGetter;
}

}
}