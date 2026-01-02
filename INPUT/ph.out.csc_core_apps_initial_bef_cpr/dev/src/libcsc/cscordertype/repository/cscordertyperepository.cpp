#include "cscordertyperepository.h"
#include "persistence/iaccessor.h"
#include <sstream>
#include "logger/loggerpool.h"
#include <persistence/itransactionfactory.h>
#include <libbasarcmnutil_exceptions.h>
#include <cscordertype/cscordertype.h>
#include <cscordertype/cscordertypeptr.h>
#include <cscordertype/sqlmapper/cscordertypesqlmapper.h>
#include <cscordertype/cscordertypebatchconfig/cscordertypebatchconfigsqlmapper.h>
#include <cscordertype/cscordertypebatchconfig/cscordertypebatchconfig.h>
#include <cscordertype/ordertypeflagtype/ordertypeflagtypesqlmapper.h>
#include <cscordertype/ordertypeflagtype/ordertypeflagtype.h>
#include <boost/make_shared.hpp>

namespace libcsc
{
namespace cscordertype
{
CSCOrderTypeRepository::CSCOrderTypeRepository()
{
}

CSCOrderTypeRepository::~CSCOrderTypeRepository()
{
	m_Accessor.reset();
}

void CSCOrderTypeRepository::reset()
{
	m_CSCOrderTypeList.reset();
}

void CSCOrderTypeRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
{
	m_TransactionFactory = transactionFactory;
}

void CSCOrderTypeRepository::injectAccessor( persistence::IAccessorPtr accessor )
{
	m_Accessor = accessor;
}

ICSCOrderTypePtr CSCOrderTypeRepository::createOrderType() const
{
	CSCOrderTypePtr orderTypePtr( new CSCOrderType() );
	CSCOrderTypeBatchConfigPtr batchConfig( new CSCOrderTypeBatchConfig() );
	orderTypePtr->m_BatchConfig = batchConfig;
	return orderTypePtr;
}

void CSCOrderTypeRepository::injectSelectCSCOrderTypeAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::injectSelectCSCOrderTypeAccessor()");
	m_SelectCSCOrderTypeAccessor = accessor;
}

void CSCOrderTypeRepository::injectInsertCSCOrderTypeAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::injectInsertCSCOrderTypeAccessor()");
	m_InsertCSCOrderTypeAccessor = accessor;
}

void CSCOrderTypeRepository::injectUpdateCSCOrderTypeAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::injectUpdateCSCOrderTypeAccessor()");
	m_UpdateCSCOrderTypeAccessor = accessor;
}

void CSCOrderTypeRepository::injectDeleteCSCOrderTypeAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::injectDeleteCSCOrderTypeAccessor()");
	m_DeleteCSCOrderTypeAccessor = accessor;
}

void CSCOrderTypeRepository::injectSelectCSCOrderTypeBatchConfigAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::injectSelectCSCOrderTypeBatchConfigAccessor()");
	m_SelectCSCOrderTypeBatchConfigAccessor = accessor;
}

void CSCOrderTypeRepository::injectInsertCSCOrderTypeBatchConfigAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::injectInsertCSCOrderTypeBatchConfigAccessor()");
	m_InsertCSCOrderTypeBatchConfigAccessor = accessor;
}

void CSCOrderTypeRepository::injectUpdateCSCOrderTypeBatchConfigAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::injectUpdateCSCOrderTypeBatchConfigAccessor()");
	m_UpdateCSCOrderTypeBatchConfigAccessor = accessor;
}

void CSCOrderTypeRepository::injectDeleteCSCOrderTypeBatchConfigAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::injectDeleteCSCOrderTypeBatchConfigAccessor()");
	m_DeleteCSCOrderTypeBatchConfigAccessor = accessor;
}

void CSCOrderTypeRepository::injectSelectCSCOrderTypeFlagTypeAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::injectSelectCSCOrderTypeFlagTypeAccessor()");
	m_SelectCSCOrderTypeFlagTypeAccessor = accessor;
}

CSCOrderTypeCollectionPtr CSCOrderTypeRepository::findOrderTypes( const basar::Int16 branchNo ) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::findOrderTypes()" );

	if (NULL == m_CSCOrderTypeList.get())
	{
		m_CSCOrderTypeList = boost::make_shared<CSCOrderTypeCollection>();

		try
		{
			basar::db::sql::ResultsetRef resultset = m_Accessor->select(CSCOrderTypeSqlMapper::getMultiSelectSQL(branchNo));
			while (resultset.next())
			{
				CSCOrderTypePtr orderTypePtr(new CSCOrderType());
				CSCOrderTypeSqlMapper mapper(orderTypePtr, resultset);
				mapper.map();

				CSCOrderTypeBatchConfigPtr batchConfig(new CSCOrderTypeBatchConfig());
				basar::db::sql::ResultsetRef confresultset = m_SelectCSCOrderTypeBatchConfigAccessor->select(CSCOrderTypeBatchConfigSqlMapper::getSelectSQL(branchNo, orderTypePtr->getOrderType()));
				if (confresultset.next())
				{
					CSCOrderTypeBatchConfigSqlMapper batchConfigMapper(batchConfig, confresultset);
					batchConfigMapper.map();
				}
				else
				{
					batchConfig->setBranchNo(branchNo);
					batchConfig->setOrderType(orderTypePtr->getOrderType());
					batchConfig->setAllowDesiredBatch(false);
					batchConfig->setAllowFixedBatch(false);
					batchConfig->setForbidUserChange(false);
				}

				orderTypePtr->m_BatchConfig = batchConfig;

				libcsc::cscordertype::OrderTypeFlagTypeCollectionPtr orderTypeFlagTypeCollection = boost::make_shared<OrderTypeFlagTypeCollection>();
				basar::db::sql::ResultsetRef flagTypeResultSet = m_SelectCSCOrderTypeFlagTypeAccessor->select(OrderTypeFlagTypeSqlMapper::getSelectSQL(orderTypePtr->getOrderType()));
				while (flagTypeResultSet.next())
				{
					OrderTypeFlagTypePtr orderTypeFlagType(new OrderTypeFlagType());
					OrderTypeFlagTypeSqlMapper orderTypeFlagTypeMapper(orderTypeFlagType, flagTypeResultSet);
					orderTypeFlagTypeMapper.map();

					orderTypeFlagTypeCollection->push_back(orderTypeFlagType);
				}

				orderTypePtr->m_OrderTypeFlagTypeCollection = orderTypeFlagTypeCollection;
				m_CSCOrderTypeList->push_back(orderTypePtr);
			}

		}
		catch (const basar::Exception & e)
		{
			std::stringstream s;
			s << "Error CSCOrderTypeRepository::findOrderTypes(): " << e.what().c_str();
			BLOG_ERROR(libcsc::LoggerPool::getLoggerParameter(), s.str().c_str());
			throw;
		}
	}

	return m_CSCOrderTypeList;
}

ICSCOrderTypePtr CSCOrderTypeRepository::findOrderType( const basar::Int16 branchNo, const basar::VarString & orderType ) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::findOrderType()" );

	CSCOrderTypePtr orderTypePtr;
	try
	{
		basar::db::sql::ResultsetRef resultset = m_SelectCSCOrderTypeAccessor->select( CSCOrderTypeSqlMapper::getSingleSelectSQL( branchNo, orderType ) );
		if( resultset.next() )
		{
			orderTypePtr = CSCOrderTypePtr( new CSCOrderType() );
			CSCOrderTypeSqlMapper mapper( orderTypePtr, resultset );
			mapper.map();

			CSCOrderTypeBatchConfigPtr batchConfig( new CSCOrderTypeBatchConfig() );
			basar::db::sql::ResultsetRef confresultset = m_SelectCSCOrderTypeBatchConfigAccessor->select( CSCOrderTypeBatchConfigSqlMapper::getSelectSQL( branchNo, orderType ) );
			if(confresultset.next() )
			{
				CSCOrderTypeBatchConfigSqlMapper batchConfigMapper( batchConfig, confresultset);
				batchConfigMapper.map();
			}
			else
			{
				batchConfig->setBranchNo( branchNo );
				batchConfig->setOrderType( orderType );
				batchConfig->setAllowDesiredBatch(false);
				batchConfig->setAllowFixedBatch(false);
				batchConfig->setForbidUserChange(false);
			}

			orderTypePtr->m_BatchConfig = batchConfig;

			libcsc::cscordertype::OrderTypeFlagTypeCollectionPtr orderTypeFlagTypeCollection = boost::make_shared<OrderTypeFlagTypeCollection>();
			basar::db::sql::ResultsetRef flagTypeResultSet = m_SelectCSCOrderTypeFlagTypeAccessor->select(OrderTypeFlagTypeSqlMapper::getSelectSQL(orderTypePtr->getOrderType()));
			while (flagTypeResultSet.next())
			{
				OrderTypeFlagTypePtr orderTypeFlagType(new OrderTypeFlagType());
				OrderTypeFlagTypeSqlMapper orderTypeFlagTypeMapper(orderTypeFlagType, flagTypeResultSet);
				orderTypeFlagTypeMapper.map();

				orderTypeFlagTypeCollection->push_back(orderTypeFlagType);
			}

			orderTypePtr->m_OrderTypeFlagTypeCollection = orderTypeFlagTypeCollection;
		}
	}
	catch( const basar::Exception & e )
	{
		std::stringstream s;
		s << "Error CSCOrderTypeRepository::findOrderType(): " << e.what().c_str() ;
		BLOG_ERROR( libcsc::LoggerPool::getLoggerParameter(), s.str().c_str() );
		throw;
	}

	return orderTypePtr;
}

void CSCOrderTypeRepository::saveOrderType( const ICSCOrderTypePtr iorderType ) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::saveOrderType()" );

	persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
	try
	{
		CSCOrderTypePtr orderType = boost::dynamic_pointer_cast<CSCOrderType>( iorderType );
		if( CSCOrderTypeSqlMapper::isInsertable( orderType ) )
		{
			m_InsertCSCOrderTypeAccessor->execute( CSCOrderTypeSqlMapper::getInsertSQL( orderType ) );
		}
		else if( CSCOrderTypeSqlMapper::isUpdatable( orderType ) )
		{
			//Check Standard-Auftragsart neu gesetzt Ronnie
			if (orderType->getStandard())
			{
				if (NULL == m_CSCOrderTypeList)
				{
					findOrderTypes(orderType->getBranchNo());
				}

				CSCOrderTypeCollection::const_iterator it;
				it = m_CSCOrderTypeList->begin();
				for (it = m_CSCOrderTypeList->begin(); it != m_CSCOrderTypeList->end(); it++)
				{
					if ((*it)->getOrderType() == orderType->getOrderType())
					{
						if ((*it)->getStandard() == orderType->getStandard()) break;
					}
					else if ((*it)->getStandard())
					{
						CSCOrderTypePtr orderTypeold = boost::dynamic_pointer_cast<CSCOrderType>((*it));
						orderTypeold->setStandard(false);
						m_UpdateCSCOrderTypeAccessor->execute(CSCOrderTypeSqlMapper::getUpdateSQL(orderTypeold));
						break;
					}
				}
			}
			m_UpdateCSCOrderTypeAccessor->execute( CSCOrderTypeSqlMapper::getUpdateSQL( orderType ) );
		}

		CSCOrderTypeBatchConfigPtr batchConfig = boost::dynamic_pointer_cast<CSCOrderTypeBatchConfig>( orderType->getBatchConfig() );
		saveOrderTypeBatchConfig( batchConfig );

		orderType->setClean();
		guard.commit();
	}
	catch( const basar::Exception & e )
	{
		guard.rollback();

		std::stringstream ss;
		ss << "CSCOrderTypeRepository::saveOrderType(): " << e.what().c_str();
		BLOG_ERROR( LoggerPool::getLoggerParameter(), ss.str().c_str() );
		throw;
	}

}

void CSCOrderTypeRepository::saveOrderTypeBatchConfig( CSCOrderTypeBatchConfigPtr batchConfig ) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::saveOrderTypeBatchConfig()" );

	try
	{
		if( CSCOrderTypeBatchConfigSqlMapper::isInsertable( batchConfig ) )
		{
			m_InsertCSCOrderTypeBatchConfigAccessor->execute( CSCOrderTypeBatchConfigSqlMapper::getInsertSQL( batchConfig ) );
		}
		else if( CSCOrderTypeBatchConfigSqlMapper::isUpdatable( batchConfig ) )
		{
			m_UpdateCSCOrderTypeBatchConfigAccessor->execute( CSCOrderTypeBatchConfigSqlMapper::getUpdateSQL( batchConfig ) );
		}

		batchConfig->setClean();
	}
	catch( const basar::Exception & e )
	{
		BLOG_ERROR( LoggerPool::getLoggerParameter(), e.what().c_str() );
		throw;
	}
}

void CSCOrderTypeRepository::deleteOrderType( const ICSCOrderTypePtr iorderType ) const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "CSCOrderTypeRepository::deleteOrderType()" );

	persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
	try
	{
		CSCOrderTypePtr orderType = boost::dynamic_pointer_cast<CSCOrderType>( iorderType );
		m_DeleteCSCOrderTypeAccessor->execute(CSCOrderTypeSqlMapper::getDeleteSQL(orderType));
		if (CSCOrderTypeBatchConfigSqlMapper::isDeletable(orderType->m_BatchConfig))
		{
			m_DeleteCSCOrderTypeBatchConfigAccessor->execute(CSCOrderTypeBatchConfigSqlMapper::getDeleteSQL(orderType->m_BatchConfig));
		}


		guard.commit();
	}
	catch( const basar::Exception & e )
	{
		guard.rollback();

		std::stringstream ss;
		ss << "CSCOrderTypeRepository::deleteOrderType(): " << e.what().c_str();
		BLOG_ERROR( LoggerPool::getLoggerParameter(), ss.str().c_str() );
		throw;
	}
}

} // end namespace cscordertype
} // end namespace libcsc
