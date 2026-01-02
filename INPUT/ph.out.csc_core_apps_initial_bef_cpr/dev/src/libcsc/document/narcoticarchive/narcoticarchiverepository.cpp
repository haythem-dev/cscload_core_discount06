#include "narcoticarchiverepository.h"
#include "narcoticarchivesqlmapper.h"
#include "narcoticarchive.h"
#include <persistence/iaccessor.h>
#include <parameter/ibranchparametergetter.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

//#include "..\documentarchiveinfo\documentarchiveinforepository.h"
//#include "..\documentarchiveinfo\documentarchiveinfosqlmapper.h"
//#include "..\documentarchiveinfo\documentarchiveinfo.h"

namespace libcsc
{
	namespace document
	{
		NarcoticArchiveRepository::NarcoticArchiveRepository()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveRepository::NarcoticArchiveRepository()");
		}

		NarcoticArchiveRepository::~NarcoticArchiveRepository()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveRepository::~NarcoticArchiveRepository()");
			m_FindAccessor.reset();
		}

		void NarcoticArchiveRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveRepository::injectTransactionFactory()");
			m_TransactionFactory = transactionFactory;
		}

		void NarcoticArchiveRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveRepository::injectFindAccessor()");
			m_FindAccessor = accessor;
		}

		void NarcoticArchiveRepository::injectFindByContributionVoucherNoAccessor(persistence::IAccessorPtr accessor)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveRepository::injectFindbyContributionVoucherNoAccessor()");
			m_FindByContributionVoucherNoAccessor = accessor;
		}

		void NarcoticArchiveRepository::injectInsertAccessor(persistence::IAccessorPtr accessor)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveRepository::injectInsertAccessor()");
			m_InsertAccessor = accessor;
		}

		void NarcoticArchiveRepository::injectUpdateAccessor(persistence::IAccessorPtr accessor)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveRepository::injectUpdateAccessor()");
			m_UpdateAccessor = accessor;
		}

		void NarcoticArchiveRepository::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveRepository::injectBranchParameterGetter()");
			m_BranchParameterGetter = parameterGetter;
		}

		NarcoticArchivePtr NarcoticArchiveRepository::createEmptyNarcoticArchive() const
		{
			return boost::make_shared<NarcoticArchive>();
		}

		/// <summary>
		/// findNarcoticArchiveByContributionVoucherNo
		/// </summary>
		/// <param name="branchNo"></param>
		/// <param name="contributionVoucherNo"></param>
		/// <returns></returns>
		NarcoticArchivePtr libcsc::document::NarcoticArchiveRepository::findNarcoticArchive(const basar::Int16 branchNo, const basar::Int32 customerSupplierNo, const basar::Int32 transactionDate) const
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveRepository::findNarcoticArchiveByContributionVoucherNo()");
			NarcoticArchivePtr narcoticArchivePtr;

			try
			{
				if ((customerSupplierNo > 0) && (branchNo > 0))
				{
					basar::db::sql::ResultsetRef resultset;
					resultset = m_FindAccessor->select(
						NarcoticArchiveSQLMapper::getSelectSQL(transactionDate),
						NarcoticArchiveSQLMapper::getSelectSqlParameterBinder(branchNo, customerSupplierNo, transactionDate));

					if (resultset.next())
					{
						narcoticArchivePtr = createEmptyNarcoticArchive();
						NarcoticArchiveSQLMapper mapper(narcoticArchivePtr, resultset);
						mapper.map();
					}
				}
			}
			catch (basar::Exception&)
			{
				throw;
			}

			return narcoticArchivePtr;
		}

		/// <summary>
		/// findNarcoticArchiveByContributionVoucherNo
		/// </summary>
		/// <param name="branchNo"></param>
		/// <param name="contributionVoucherNo"></param>
		/// <returns></returns>
		NarcoticArchivePtr libcsc::document::NarcoticArchiveRepository::findNarcoticArchiveByContributionVoucherNo(const basar::Int16 branchNo, const basar::Int32 contributionVoucherNo) const
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveRepository::findNarcoticArchiveByContributionVoucherNo()");
			NarcoticArchivePtr narcoticArchivePtr;

			try
			{
				if ((contributionVoucherNo > 0) && (branchNo > 0))
				{
					basar::db::sql::ResultsetRef resultset;
					resultset = m_FindByContributionVoucherNoAccessor->select(
						NarcoticArchiveSQLMapper::getSelectByContributionVoucherNoSQL(),
						NarcoticArchiveSQLMapper::getSelectByContributionVoucherNoSqlParameterBinder(branchNo, contributionVoucherNo));

					if (resultset.next())
					{
						narcoticArchivePtr = createEmptyNarcoticArchive();
						NarcoticArchiveSQLMapper mapper(narcoticArchivePtr, resultset);
						mapper.map();
					}
				}
			}
			catch (basar::Exception&)
			{
				throw;
			}

			return narcoticArchivePtr;
		}

		/// <summary>
		/// updateAcknowledgementStatusSQL
		/// </summary>
		/// <param name="narcoticArchivePtr"></param>
		void NarcoticArchiveRepository::updateAcknowledgementStatusSQL(NarcoticArchivePtr narcoticArchivePtr) const
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveRepository::saveNarcoticArchive()");
			try
			{
				if (narcoticArchivePtr->getContributionVoucherNo() > 0)
				{
					if (narcoticArchivePtr->isDirty())
					{
						return;
					}
					
					if (narcoticArchivePtr->isClean())
					{
						m_UpdateAccessor->execute(NarcoticArchiveSQLMapper::getUpdateAcknowledgementStatusSQL(narcoticArchivePtr));
					}
				}
			}
			catch (basar::Exception&)
			{
				throw;
			}
		}

	} // end namespace document
} // end namespace libcsc
