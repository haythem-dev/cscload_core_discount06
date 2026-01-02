/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// include section
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "longtermlackrepository.h"
#include "longtermlacksqlmapper.h"
#include "logger/loggerpool.h"

#include <persistence/iaccessor.h>
#include <libbasarcmnutil.h>

namespace libcsc 
{
namespace stockbooking 
{

LongTermLackRepository::LongTermLackRepository()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "LongTermLackRepository::LongTermLackRepository()");
}

LongTermLackRepository::~LongTermLackRepository()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "LongTermLackRepository::~LongTermLackRepository()");

    m_CheckerLongTermLackAccessor.reset();
    m_DeleteLongTermLackAccessor.reset();
}

void LongTermLackRepository::injectCheckerLongTermLackAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "LongTermLackRepository::injectSelectLongTermLackAccessor()");
    m_CheckerLongTermLackAccessor = accessor;
}

void LongTermLackRepository::injectDeleteLongTermLackAccessor(persistence::IAccessorPtr accessor)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "LongTermLackRepository::injectDeleteLongTermLackAccessor()");
    m_DeleteLongTermLackAccessor = accessor;
}

void LongTermLackRepository::deleteLongTermLack( const basar::Int32 articleNo )
{
    static basar::VarString fun = "LongTermLackRepository::deleteLongTermLack()";
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "LongTermLackRepository::deleteLongTermLack()");
    
    try
    {
        m_DeleteLongTermLackAccessor->execute( LongTermLackSQLMapper::getDeleteSQL(articleNo) );
    }
    catch( basar::Exception& e )
    {
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), fun + ": " + e.what());
        throw;
    } catch( ... )
    {
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), fun + ": Unknown Exception!");
        throw;
    }
}

bool LongTermLackRepository::isLongTermLack( const basar::Int32 articleNo ) const
{
    static basar::VarString fun = "LongTermLackRepository::isLongTermLack()";
    LOG4CPLUS_TRACE_METHOD( libcsc::LoggerPool::getLoggerStockBooking(), fun );

    basar::Decimal numberOfLacks;
    try 
    {
        basar::db::sql::ResultsetRef resultset = 
            m_CheckerLongTermLackAccessor->select(LongTermLackSQLMapper::getSelectSQL(), LongTermLackSQLMapper::getSelectSqlParameterBinder(articleNo));
        
        if( true == resultset.next() )
        {
            numberOfLacks = resultset.getDecimal( LongTermLackSQLMapper::s_NumberOfLacksColumn );
        }
    }
    catch( basar::Exception& e )
    {
        BLOG_ERROR( libcsc::LoggerPool::getLoggerSession(), fun + ": " + e.what() );
        throw;
    }
    catch (...)
    {
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), fun + ": Unknown Exception!" );
        throw;
    }

    return basar::Decimal(0) < numberOfLacks ? true : false;
}


} // namespace stockbooking
} // namespace libcsc