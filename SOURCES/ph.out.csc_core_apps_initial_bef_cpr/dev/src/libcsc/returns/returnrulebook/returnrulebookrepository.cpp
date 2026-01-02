#include "returnrulebookrepository.h"

#include "returnrulebook.h"
#include "returnrulebooksqlmapper.h"

#include <persistence/iaccessor.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>


namespace libcsc {
namespace returns{

	ReturnRuleBookRepository::ReturnRuleBookRepository()
	{

	}

	ReturnRuleBookRepository::~ReturnRuleBookRepository()
	{

	}

	void ReturnRuleBookRepository::injectReturnRuleBookAccessor(persistence::IAccessorPtr accessor)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnRuleBookRepository::injectReturnRuleBookAccessor()");

		m_SelectReturnRuleBoookAccessor = accessor;
	}

	ReturnRuleBookCollectionPtr ReturnRuleBookRepository::findReturnRuleBook(const basar::VarString& returnReasonCode) const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnRuleBookRepository::findReturnRuleBook()");

		ReturnRuleBookCollectionPtr coll = boost::make_shared<ReturnRuleBookCollection>();

		basar::db::sql::ResultsetRef resultset = m_SelectReturnRuleBoookAccessor->select(
			ReturnRuleBookSQLMapper::getSelectSQL(returnReasonCode));

		while (resultset.next())
		{
			ReturnRuleBookPtr returnRuleBook = boost::make_shared<ReturnRuleBook>();
			ReturnRuleBookSQLMapper mapper(returnRuleBook, resultset);
			mapper.map();
			coll->push_back(returnRuleBook);
		}
		return coll;
	}


} //returns
} //libcsc
