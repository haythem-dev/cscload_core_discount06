#include "returnannouncementrepository.h"

#include <returns/returnannouncement/returnannouncement.h>
#include <returns/returnannouncement/returnannouncementsqlmapper.h>
#include <returns/returnannouncement/returnannouncementhead/returnannouncementhead.h>
#include <returns/returnannouncement/returnannouncementhead/returnannouncementheadsqlmapper.h>
#include <returns/returnannouncement/returnannouncementpos/returnannouncementpos.h>
#include <returns/returnannouncement/returnannouncementpos/returnannouncementpossqlmapper.h>
#include <persistence/iaccessor.h>
#include <persistence/itransactionfactory.h>
#include <exceptions/sqlduplicateexception.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>


namespace libcsc {
namespace returns {

	ReturnAnnouncementRepository::ReturnAnnouncementRepository()
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::ReturnAnnouncementRepository()");
	}

	ReturnAnnouncementRepository::~ReturnAnnouncementRepository()
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::~ReturnAnnouncementRepository()");

		m_SelectReturnAnnouncementAccessor.reset();
		m_SelectReturnAnnouncementHeadAccessor.reset();
		m_SelectReturnAnnouncementPosAccessor.reset();
		m_InsertAccessor.reset();
	}

	void ReturnAnnouncementRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::injectTransactionFactory()");
		m_TransactionFactory = transactionFactory;
	}

	void ReturnAnnouncementRepository::injectReturnAnnouncementAccessor(persistence::IAccessorPtr accessor)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::injectReturnAnnouncementAccessor()");
		m_SelectReturnAnnouncementAccessor = accessor;
	}

	void ReturnAnnouncementRepository::injectReturnAnnouncementHeadAccessor(persistence::IAccessorPtr accessor)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::injectReturnAnnouncementHeadAccessor()");
		m_SelectReturnAnnouncementHeadAccessor = accessor;
	}

	void ReturnAnnouncementRepository::injectReturnAnnouncementPosAccessor(persistence::IAccessorPtr accessor)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::injectReturnAnnouncementPosAccessor()");
		m_SelectReturnAnnouncementPosAccessor = accessor;
	}

	void ReturnAnnouncementRepository::injectInsertAccessor(persistence::IAccessorPtr accessor)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::injectInsertAccessor()");
		m_InsertAccessor = accessor;
	}

	void ReturnAnnouncementRepository::injectUpdateAccessor(persistence::IAccessorPtr accessor)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::injectUpdateAccessor()");
		m_UpdateAccessor = accessor;
	}

	ReturnAnnouncementPtr ReturnAnnouncementRepository::createEmptyReturnAnnouncement() const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::createEmptyReturnAnnouncement()");

		ReturnAnnouncementPtr returnAnnouncement = boost::make_shared<ReturnAnnouncement>();
		return returnAnnouncement;
	}

	ReturnAnnouncementPtr ReturnAnnouncementRepository::findReturnAnnouncement(basar::Int32 returnAnnouncementId) const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::findReturnAnnouncement()");

		ReturnAnnouncementPtr returnAnnouncement = boost::make_shared<ReturnAnnouncement>();

		basar::db::sql::ResultsetRef resultSet = m_SelectReturnAnnouncementAccessor->select(
			ReturnAnnouncementSqlMapper::getSelectSQL(returnAnnouncementId)
		);

		if (resultSet.next())
		{
			ReturnAnnouncementSqlMapper mapper(returnAnnouncement, resultSet);
			mapper.map();

			returnAnnouncement->m_Heads->clear();
			returnAnnouncement->m_Heads = findReturnAnnouncementHeads(returnAnnouncement->getAnnouncementId());
		}

		return returnAnnouncement;
	}

	ReturnAnnouncementHeadCollectionPtr ReturnAnnouncementRepository::findReturnAnnouncementHeads(basar::Int32 announcementId) const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::findReturnAnnouncementHeads()");

		ReturnAnnouncementHeadCollectionPtr heads = boost::make_shared<ReturnAnnouncementHeadCollection>();

		basar::db::sql::ResultsetRef resultSet = m_SelectReturnAnnouncementHeadAccessor->select(
			ReturnAnnouncementHeadSqlMapper::getSelectSQL(announcementId)
		);

		while (resultSet.next())
		{
			ReturnAnnouncementHeadPtr head = boost::make_shared<ReturnAnnouncementHead>();
			ReturnAnnouncementHeadSqlMapper mapper(head, resultSet);
			mapper.map();

			head->m_Positions = findReturnAnnouncementPositions(head->getAnnouncementHeadId());

			heads->push_back(head);
		}

		return heads;
	}

	ReturnAnnouncementPosCollectionPtr ReturnAnnouncementRepository::findReturnAnnouncementPositions(basar::Int32 announcementHeadId) const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::findReturnAnnouncementPositions()");

		ReturnAnnouncementPosCollectionPtr positions = boost::make_shared<ReturnAnnouncementPosCollection>();

		basar::db::sql::ResultsetRef resultSet = m_SelectReturnAnnouncementPosAccessor->select(
			ReturnAnnouncementPosSQLMapper::getSelectSQL(announcementHeadId)
		);

		while (resultSet.next())
		{
			ReturnAnnouncementPosPtr position = boost::make_shared<ReturnAnnouncementPos>();
			ReturnAnnouncementPosSQLMapper mapper(position, resultSet);
			mapper.map();

			positions->push_back(position);
		}

		return positions;
	}

	void ReturnAnnouncementRepository::saveReturnAnnouncement(const ReturnAnnouncementPtr& returnAnnouncement) const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::saveReturnAnnouncement()");

		libcsc::persistence::TransactionGuard transactionGuard = m_TransactionFactory->createTransaction();

		if (returnAnnouncement->isInsertable())
		{
			transactionGuard.begin();
			basar::db::sql::ExecuteReturnInfo retVal;
			retVal = m_InsertAccessor->execute(ReturnAnnouncementSqlMapper::getInsertSQL(returnAnnouncement), false);
			if (false == retVal.hasError())
			{
				ReturnAnnouncementSqlMapper mapper(returnAnnouncement);
				mapper.mapSerial(static_cast<basar::Int32>(m_InsertAccessor->getLastInsertedSerial()));
				saveReturnAnnouncementHeads(returnAnnouncement);
			}
			else if (basar::db::sql::DBErrorCode::INSERT_DUPL == retVal.getError())
			{
				if (transactionGuard.isInTransaction())
				{
					transactionGuard.rollback();
				}
				throw libcsc::exceptions::SqlDuplicateException(basar::ExceptInfo("ReturnAnnouncementRepository::saveReturnAnnouncement()", "", __FILE__, __LINE__));
			}
			transactionGuard.commit();
		}
	}

	void ReturnAnnouncementRepository::saveReturnAnnouncementHeads(const ReturnAnnouncementPtr& returnAnnouncement) const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::saveReturnAnnouncementHeads()");

		try
		{
			ReturnAnnouncementHeadCollectionPtr heads = returnAnnouncement->getHeads();
			std::list<ReturnAnnouncementHeadPtr>::iterator headIterator = heads->begin();
			for (; headIterator != heads->end(); ++headIterator)
			{
				ReturnAnnouncementHeadPtr head = (*headIterator);
				head->setAnnouncementId(returnAnnouncement->getAnnouncementId());
				head->setWholesalerReferenceId(""); // insert empty because we need the serial!

				if (head->isInsertable())
				{
					basar::db::sql::ExecuteReturnInfo retVal;
					retVal = m_InsertAccessor->execute(ReturnAnnouncementHeadSqlMapper::getInsertSQL(head));
					ReturnAnnouncementHeadSqlMapper mapper(head);
					mapper.mapSerial(static_cast<basar::Int32>(m_InsertAccessor->getLastInsertedSerial()));
					basar::VarString refId;
					refId.format("%02d%07d%010d%2.2s%08d%1.1s",
						returnAnnouncement->getBranchNo(),
						returnAnnouncement->getCustomerNo(),
						head->getAnnouncementHeadId(),
						head->getAccCheckResultCode().c_str(),
						returnAnnouncement->getAnnouncementDate(),
						" ");
					head->setWholesalerReferenceId(refId);
					head->setTransferStatus(1);
					saveReturnAnnouncementPositions(head);
					retVal = m_UpdateAccessor->execute(ReturnAnnouncementHeadSqlMapper::getUpdateSQL(head));
				}
			}
		}
		catch (const basar::Exception& ex)
		{
			std::stringstream ss;
			ss << "ReturnAnnouncementRepository::saveReturnAnnouncementHeads(): " << ex.what().c_str();
			BLOG_ERROR(LoggerPool::getLoggerReturns(), ss.str().c_str());

			throw;
		}
	}

	void ReturnAnnouncementRepository::saveReturnAnnouncementPositions(const ReturnAnnouncementHeadPtr& returnAnnouncementHead) const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementRepository::saveReturnAnnouncementPositions()");

		try
		{
			ReturnAnnouncementPosCollectionPtr positions = returnAnnouncementHead->getPositions();
			std::list<ReturnAnnouncementPosPtr>::iterator posIterator = positions->begin();

			for (; posIterator != positions->end(); ++posIterator)
			{
				ReturnAnnouncementPosPtr position = (*posIterator);
				position->setAnnouncementHeadId(returnAnnouncementHead->getAnnouncementHeadId());

				if (position->isInsertable())
				{
					m_InsertAccessor->execute(ReturnAnnouncementPosSQLMapper::getInsertSQL(position));
				}
			}
		}
		catch (const basar::Exception& ex)
		{
			std::stringstream ss;
			ss << "ReturnAnnouncementRepository::saveReturnAnnouncementPositions(): " << ex.what().c_str();
			BLOG_ERROR(LoggerPool::getLoggerReturns(), ss.str().c_str());

			throw;
		}
	}


} // namespace returns
} // namespace libcsc
