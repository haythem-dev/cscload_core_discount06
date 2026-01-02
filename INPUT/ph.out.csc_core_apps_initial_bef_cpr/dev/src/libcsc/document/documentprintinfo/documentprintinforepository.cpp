#include "documentprintinforepository.h"
#include "documentprintinfosqlmapper.h"
#include "documentprintinfo.h"

#include <persistence/iaccessor.h>
#include <parameter/ibranchparametergetter.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace document {

DocumentPrintInfoRepository::DocumentPrintInfoRepository()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoRepository::DocumentPrintInfoRepository()");
}

DocumentPrintInfoRepository::~DocumentPrintInfoRepository()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoRepository::~DocumentPrintInfoRepository()");
}

void DocumentPrintInfoRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoRepository::injectTransactionFactory()");
	m_TransactionFactory = transactionFactory;
}

void DocumentPrintInfoRepository::injectInsertAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoRepository::injectInsertAccessor()");
	m_InsertAccessor = accessor;
}

void DocumentPrintInfoRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoRepository::injectFindAccessor()");
	m_FindAccessor = accessor;
}

DocumentPrintInfoPtr DocumentPrintInfoRepository::createEmptyDocumentPrintInfo() const
{
	return boost::make_shared<DocumentPrintInfo>();
}

void DocumentPrintInfoRepository::saveDocumentPrintInfo(DocumentPrintInfoPtr documentPrintInfo) const
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoRepository::saveDocumentPrintInfo()");
	try
	{
		if (documentPrintInfo->getBranchNo() > 0 )
		{
			basar::VarString databaseName = m_BranchParameterGetter->getDatabaseName(documentPrintInfo->getBranchNo());
			if (documentPrintInfo->isDirty())
			{
				m_InsertAccessor->execute(
					DocumentPrintInfoSQLMapper::getInsertSQL(databaseName),
					DocumentPrintInfoSQLMapper::getInsertSqlParameterBinder(documentPrintInfo)
				);
			}
		}
	}
	catch( basar::Exception & )
	{
		throw;
	}
}

DocumentPrintInfoPtr DocumentPrintInfoRepository::findDocumentPrintInfo(const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum documentType,
	const basar::VarString & documentNo, const basar::Int32 documentDate) const
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoRepository::findDocumentPrintInfo()");

	DocumentPrintInfoPtr docPrintInfo;

	try
	{
		if ((branchNo > 0) && (customerNo > 0) && (documentType >= 0) && (documentNo.empty() == false) && (documentDate > 0))
		{
			basar::VarString databaseName = m_BranchParameterGetter->getDatabaseName(branchNo);

			if (databaseName.empty())
			{
				return docPrintInfo;
			}

			basar::db::sql::ResultsetRef resultset;
			resultset = m_FindAccessor->select(
				DocumentPrintInfoSQLMapper::getSelectSQL(databaseName),
				DocumentPrintInfoSQLMapper::getSelectSqlParameterBinder(branchNo, customerNo, documentType, documentDate, documentNo)
				);

			if (resultset.next())
			{
				docPrintInfo = createEmptyDocumentPrintInfo();
				DocumentPrintInfoSQLMapper mapper(docPrintInfo, resultset);
				mapper.map();
			}
		}
	}
	catch (basar::Exception &)
	{
		throw;
	}

	return docPrintInfo;
}

void DocumentPrintInfoRepository::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoRepository::injectBranchParameterGetter()");
	m_BranchParameterGetter = parameterGetter;
}

} // end namespace document
} // end namespace libcsc
