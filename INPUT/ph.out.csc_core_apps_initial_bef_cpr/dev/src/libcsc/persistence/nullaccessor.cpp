#include "nullaccessor.h"
#include <logger/loggerpool.h>

namespace libcsc
{
namespace persistence
{
NullAccessor::NullAccessor()
{
}

NullAccessor::~NullAccessor()
{
}

const basar::db::sql::ResultsetRef NullAccessor::selectDirty(const basar::VarString&)
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "NullAccessor::selectDirty()" );

    return basar::db::sql::ResultsetRef();
}

const basar::db::sql::ResultsetRef NullAccessor::select(const basar::VarString&)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "NullAccessor::select()");

    return basar::db::sql::ResultsetRef();
}

const basar::db::sql::ResultsetRef NullAccessor::select( const basar::VarString &, const ISqlParameterBinderPtr )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "NullAccessor::select()" );

    return basar::db::sql::ResultsetRef();
}

const basar::db::sql::ExecuteReturnInfo NullAccessor::execute( const basar::VarString &, const bool )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "NullAccessor::execute()" );

    return basar::db::sql::ExecuteReturnInfo();
}

const basar::db::sql::ExecuteReturnInfo NullAccessor::execute( const basar::VarString &, const ISqlParameterBinderPtr, const bool )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "NullAccessor::execute()" );

    return basar::db::sql::ExecuteReturnInfo();
}

basar::Int64 NullAccessor::getLastInsertedSerial() const
{
    return 0;
}

} // end namespace persistence
} // end namespace libcsc

