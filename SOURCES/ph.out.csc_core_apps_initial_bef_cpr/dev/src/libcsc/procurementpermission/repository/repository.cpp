/*
 * repository.cpp
 *
 *  Created on: 09.02.2016
 *  Author: sebastian.barth
 */

#include "repository.h"
#include "requestsqlmapper.h"
#include <persistence/iaccessor.h>
#include <libbasarcmnutil_exceptions.h>
#include "exceptions/sqlnotfoundexception.h"


namespace libcsc {
namespace procurementpermission {
namespace repo {

Repository::Repository(log4cplus::Logger const& logger)
    : m_Logger(logger)
{
}

Repository::~Repository()
{
    m_FindAccessor.reset();
}

IRepositoryPtr Repository::create(log4cplus::Logger const& logger)
{
    return IRepositoryPtr(new Repository(logger));
}

void Repository::injectFindAccessor(persistence::IAccessorPtr accessor)
{
    m_FindAccessor = accessor;
}

bool Repository::isExportPermitted(basar::VarString const& targetIfaCountryCode, basar::Long32 const articleNo)
{
    try
    {
        basar::db::sql::ResultsetRef resultset = m_FindAccessor->select(RequestSqlMapper::getSelectSQL(targetIfaCountryCode, articleNo));
        if ( !resultset.next() )
        {
            throw libcsc::exceptions::SqlNotFoundException(basar::ExceptInfo("Repository::isExportPermitted()", "", __FILE__, __LINE__ ) );
        }
        return (resultset.getInt32(0) == 0);
    }
    catch (basar::Exception const&)
    {
        BLOG_ERROR(m_Logger, "Exception in libcsc::procurementpermission::repo::Repository::isExportPermitted()");
        throw;
    }
}

} // end namespace repo
} // end namespace procurementpermission
} // end namespace libcsc
