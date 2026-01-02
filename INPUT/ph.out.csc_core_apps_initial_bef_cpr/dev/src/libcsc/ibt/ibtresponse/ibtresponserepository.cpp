#include "ibtresponserepository.h"
#include <persistence/iaccessor.h>
#include <persistence/itransactionfactory.h>
#include <libbasarcmnutil_exceptions.h>
#include <logger/loggerpool.h>
#include "ibtresponsesqlmapper.h"
#include "ibtresponse.h"

namespace libcsc
{
namespace ibt
{
IbtResponseRepository::IbtResponseRepository()
{
}

IbtResponseRepository::~IbtResponseRepository()
{
    m_Accessor.reset();
}

void IbtResponseRepository::injectTransactionFactory( persistence::ITransactionFactoryPtr transactionFactory )
{
    m_TransactionFactory = transactionFactory;
}

void IbtResponseRepository::injectAccessor( persistence::IAccessorPtr accessor )
{
    m_Accessor = accessor;
}

IIbtResponsePtr IbtResponseRepository::createResponse( const basar::Int32 ibtRequestId )
{
	IbtResponsePtr ibtResponse( new IbtResponse() );
	ibtResponse->setIbtRequestId( ibtRequestId );
	//m_IbtResponses.push_back( ibtResponse );
	return ibtResponse;
}

void IbtResponseRepository::saveIbtResponse( IIbtResponsePtr iibtResponse )
{
	IbtResponsePtr ibtResponse = boost::dynamic_pointer_cast<IbtResponse>( iibtResponse );
	saveIbtResponse( ibtResponse );
}

void IbtResponseRepository::saveIbtResponse( IbtResponsePtr ibtResponse )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtResponseRepository::save()" );

	persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
	try
	{
		if( IbtResponseSqlMapper::isInsertable( ibtResponse ) )
		{
			m_Accessor->execute( IbtResponseSqlMapper::getInsertSQL( ibtResponse ) );
			ibtResponse->setIbtResponseId( static_cast<basar::Int32>(m_Accessor->getLastInsertedSerial()) );
		}
		else if (IbtResponseSqlMapper::isUpdateable( ibtResponse ) )
		{
			m_Accessor->execute(IbtResponseSqlMapper::getUpdateSQL( ibtResponse ) );
		}
		ibtResponse->setClean();
		guard.commit();
	}
	catch( const basar::Exception & e )
	{
		guard.rollback();
		std::stringstream ss;
		ss << "IbtResponseRepository::save(): " << e.what().c_str();
		BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );
		throw;
	}
}

IIbtResponsePtr IbtResponseRepository::findIbtResponse( const basar::Int32 ibtOrderNo, const basar::Int32 ibtPosNo )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtResponseRepository::findIbtResponse()" );

	IbtResponsePtr ibtResponse( new IbtResponse() );

	try
	{
		basar::db::sql::ResultsetRef resultset = m_Accessor->select( IbtResponseSqlMapper::getSelectSQL( ibtOrderNo, ibtPosNo ) );
		if( resultset.next() )
		{
			IbtResponseSqlMapper mapper( ibtResponse, resultset );
			mapper.map();
		}
	}
	catch( const basar::Exception & e )
	{
		BLOG_ERROR( LoggerPool::getLoggerIbtRequest(), e.what().c_str() );
		throw;
	}

	std::stringstream ss;
	ss << "IbtResponseRepository::findIbtResponse(): ibtResponse == \n" << *ibtResponse;
	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

	return ibtResponse;
}


} // end namespace ibt
} // end namespace libcsc
