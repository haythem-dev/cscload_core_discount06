#include <document/taxrates/taxratesrepository.h>
#include <document/taxrates/taxratessqlmapper.h>
#include <document/taxrates/taxratessql.h>
#include <document/taxrates/taxrates.h>

#include <persistence/iaccessor.h>
#include <logger/loggerpool.h>
#include <parameter/branchparametergetter.h>
#include <boost/make_shared.hpp>

#include <libbasarcmnutil.h>


namespace libcsc {
namespace document {

TaxratesRepository::TaxratesRepository()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "TaxratesRepository::TaxratesRepository()");
}

TaxratesRepository::~TaxratesRepository()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "TaxratesRepository::~TaxratesRepository()");

    m_SelectTaxratesAccessor.reset();
}

void TaxratesRepository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "TaxratesRepository::injectFindAccessor()");

    m_SelectTaxratesAccessor = accessor;
}

TaxratesCollectionPtr TaxratesRepository::getTaxrates()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "TaxratesRepository::getTaxrates()");

    TaxratesCollectionPtr result = boost::make_shared<TaxratesCollection>();

    try
    {
        basar::db::sql::ResultsetRef resultset = m_SelectTaxratesAccessor->select(TaxratesSql::getTaxratesQuery());
        while (resultset.next())
        {
            TaxratesPtr taxrates = boost::make_shared<Taxrates>();
            TaxratesSqlMapper mapper(taxrates, resultset);
            mapper.map();
            result->push_back(taxrates);
        }

        return result;
    }
    catch (basar::Exception& e)
    {
        std::stringstream s;
        s << "getTaxrates: " << e.what();
        BLOG_ERROR(LoggerPool::getLoggerSession(), s.str());
        throw;
    }
}

} // end namespace document
} // end namespace libcsc
