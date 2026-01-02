#include "documentarchiveinforepository.h"
#include "documentarchiveinfosqlmapper.h"
#include "documentarchiveinfo.h"
#include <persistence/iaccessor.h>
#include <parameter/ibranchparametergetter.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc 
{
	namespace document 
	{
		DocumentArchiveInfoRepository::DocumentArchiveInfoRepository()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoRepository::DocumentArchiveInfoRepository()");
		}

		DocumentArchiveInfoRepository::~DocumentArchiveInfoRepository()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoRepository::~DocumentArchiveInfoRepository()");
			m_FindAccessor.reset();
		}

		void DocumentArchiveInfoRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoRepository::injectTransactionFactory()");
			m_TransactionFactory = transactionFactory;
		}

		void DocumentArchiveInfoRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoRepository::injectFindAccessor()");
			m_FindAccessor = accessor;
		}

		void DocumentArchiveInfoRepository::injectFindbyGuidAccessor(persistence::IAccessorPtr accessor)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoRepository::injectFindbyGuidAccessor()");
			m_FindByGuidAccessor = accessor;
		}

		void DocumentArchiveInfoRepository::injectInsertAccessor(persistence::IAccessorPtr accessor)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoRepository::injectInsertAccessor()");
			m_InsertAccessor = accessor;
		}

		void DocumentArchiveInfoRepository::injectUpdateAccessor(persistence::IAccessorPtr accessor)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoRepository::injectUpdateAccessor()");
			m_UpdateAccessor = accessor;
		}

		DocumentArchiveInfoPtr DocumentArchiveInfoRepository::createEmptyDocumentArchiveInfo() const
		{
			return boost::make_shared<DocumentArchiveInfo>();
		}

		DocumentArchiveInfoPtr DocumentArchiveInfoRepository::findDocumentArchiveInfo(const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum documentType, const basar::VarString& documentNo, const basar::Int32 documentDate) const
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoRepository::findDocumentArchiveInfo()");
			DocumentArchiveInfoPtr documentArchiveInfo;

			try
			{
				if ((branchNo > 0) && (customerNo > 0) && (documentType >= 0) && (documentNo.empty() == false))
				{
					basar::VarString databaseName = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);
					if (databaseName.empty())
					{
						return documentArchiveInfo;
					}
					basar::db::sql::ResultsetRef resultset;
					resultset = m_FindAccessor->select(
						DocumentArchiveInfoSQLMapper::getSelectSQL(databaseName, documentDate),
						DocumentArchiveInfoSQLMapper::getSelectSqlParameterBinder(branchNo, customerNo, documentType, documentNo, documentDate));

					if (resultset.next())
					{
						documentArchiveInfo = createEmptyDocumentArchiveInfo();
						DocumentArchiveInfoSQLMapper mapper(documentArchiveInfo, resultset);
						mapper.map();
					}
				}
			}
			catch (basar::Exception&)
			{
				throw;
			}

			return documentArchiveInfo;
		}

		DocumentArchiveInfoPtr libcsc::document::DocumentArchiveInfoRepository::findDocumentArchiveInfoByGuid(const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::VarString& documentGuid) const
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoRepository::findDocumentArchiveInfoByGuid()");
			DocumentArchiveInfoPtr documentArchiveInfo;

			try
			{
				if ((branchNo > 0) && (customerNo > 0) && (documentGuid.empty() == false))
				{
					basar::VarString databaseName = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);
					if (databaseName.empty())
					{
						return documentArchiveInfo;
					}
					basar::db::sql::ResultsetRef resultset;
					resultset = m_FindByGuidAccessor->select(
						DocumentArchiveInfoSQLMapper::getSelectByGuidSQL(databaseName),
						DocumentArchiveInfoSQLMapper::getSelectByGuidSqlParameterBinder(branchNo, customerNo, documentGuid));

					if (resultset.next())
					{
						documentArchiveInfo = createEmptyDocumentArchiveInfo();
						DocumentArchiveInfoSQLMapper mapper(documentArchiveInfo, resultset);
						mapper.map();
					}
				}
			}
			catch (basar::Exception&)
			{
				throw;
			}

			return documentArchiveInfo;
		}

		void DocumentArchiveInfoRepository::saveDocumentArchiveInfo(DocumentArchiveInfoPtr documentArchiveInfo) const
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoRepository::saveDocumentArchiveInfo()");
			try
			{
				if (documentArchiveInfo->getBranchNo() > 0)
				{
					basar::VarString databaseName = m_BranchParameterGetter->getDatabaseNameWarehouse(documentArchiveInfo->getBranchNo());
					if (documentArchiveInfo->isDirty())
					{
						m_InsertAccessor->execute(
							DocumentArchiveInfoSQLMapper::getInsertSQL(databaseName),
							DocumentArchiveInfoSQLMapper::getInsertSqlParameterBinder(documentArchiveInfo)
						);
					}
					else if (documentArchiveInfo->isClean())
					{
						m_UpdateAccessor->execute(DocumentArchiveInfoSQLMapper::getUpdateSQL(databaseName, documentArchiveInfo));
					}
				}
			}
			catch (basar::Exception&)
			{
				throw;
			}
		}

		void DocumentArchiveInfoRepository::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoRepository::injectBranchParameterGetter()");
			m_BranchParameterGetter = parameterGetter;
		}


	} // end namespace document
} // end namespace libcsc
