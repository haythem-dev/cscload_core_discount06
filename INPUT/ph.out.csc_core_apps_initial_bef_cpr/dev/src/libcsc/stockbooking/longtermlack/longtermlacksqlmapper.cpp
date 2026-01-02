/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// include section
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "longtermlacksqlmapper.h"
#include "longtermlackselectsqlparameterbinder.h"
#include "logger/loggerpool.h"

#include <sstream>

namespace libcsc
{
namespace stockbooking
{
    
const basar::VarString LongTermLackSQLMapper::s_NumberOfLacksColumn = "NumberOfLacks";

LongTermLackSQLMapper::LongTermLackSQLMapper( const basar::Int32 articleNo, const basar::db::sql::ResultsetRef resultSet )
: LongTermLackMapperBase(articleNo ), m_ResultSet( resultSet )
{
}

LongTermLackSQLMapper::~LongTermLackSQLMapper()
{
}

const basar::VarString LongTermLackSQLMapper::getDeleteSQL( const basar::Int32 articleNo )
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "LongTermLackSQLMapper::getDeleteSQL()");

    std::stringstream sql;
    sql << "DELETE FROM longtermlack WHERE articleno = " << articleNo << ";";
    return sql.str();
}

const basar::VarString LongTermLackSQLMapper::getSelectSQL()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "LongTermLackSQLMapper::getSelectSQL()");

    std::stringstream sql;
    sql << "SELECT count(*) AS " << s_NumberOfLacksColumn.c_str() << " from longtermlack WHERE articleno = ? and enabled > " << LongTermLackArticle::ARTICLE_UNPROCESSIBLE << ";";
        
    return sql.str();
}

const libcsc::persistence::ISqlParameterBinderPtr LongTermLackSQLMapper::getSelectSqlParameterBinder(const basar::Int32 articleNo)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "LongTermLackSQLMapper::getSelectSqlParameterBinder()");

    return libcsc::persistence::ISqlParameterBinderPtr( new LongTermLackSelectSqlParameterBinder(articleNo) );
}

void LongTermLackSQLMapper::bindSelectSQL( basar::db::sql::PreparedStatementRef prepStmt, const basar::Int32 articleNo )
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerStockBooking(), "LongTermLackSQLMapper::bindSelectSQL()");
    
    basar::UInt32 counter = 0;
    static basar::Int32 articleNumber = 0;
    articleNumber = articleNo;
    prepStmt.setInt32( counter, articleNumber );
}

void LongTermLackSQLMapper::doMap()
{
}

}
}

