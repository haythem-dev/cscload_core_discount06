#include "cscordertypebatchconfigsqlmapper.h"
#include "cscordertypebatchconfig.h"
#include <logger/loggerpool.h>

namespace libcsc
{
namespace cscordertype
{
CSCOrderTypeBatchConfigSqlMapper::CSCOrderTypeBatchConfigSqlMapper( CSCOrderTypeBatchConfigPtr batchConfig, const basar::db::sql::ResultsetRef resultSet )
: CSCOrderTypeBatchConfigMapperBase( batchConfig ), m_ResultSet( resultSet )
{
}

CSCOrderTypeBatchConfigSqlMapper::~CSCOrderTypeBatchConfigSqlMapper()
{
}

void CSCOrderTypeBatchConfigSqlMapper::doMap()
{
    // TODO: check ResultSet
    if( m_ResultSet.isNull() )
    {
        throw;
    }

	setBranchNo( m_ResultSet.getInt16( "branchno" ) );
	setOrderType( m_ResultSet.getString( "cscordertype" ) );
	setAllowDesiredBatch( 0 != m_ResultSet.getInt16( "allowdesiredbatch" ) );
	setAllowFixedBatch( 0 != m_ResultSet.getInt16( "allowfixedbatch" ) );
	setForbidUserChange( 0 != m_ResultSet.getInt16( "forbiduserchange" ) );
}

bool CSCOrderTypeBatchConfigSqlMapper::isInsertable( const CSCOrderTypeBatchConfigPtr batchConfig )
{
	return ( batchConfig->getBranchNo().isDirty() && batchConfig->getOrderType().isDirty() );
}

bool CSCOrderTypeBatchConfigSqlMapper::isUpdatable( const CSCOrderTypeBatchConfigPtr batchConfig )
{
	return ( batchConfig->getBranchNo().isClean() && batchConfig->getOrderType().isClean() && batchConfig->containsDirty() );
}

bool CSCOrderTypeBatchConfigSqlMapper::isDeletable( const CSCOrderTypeBatchConfigPtr batchConfig )
{
	return ( batchConfig->getBranchNo().isClean() && batchConfig->getOrderType().isClean() );
}

const basar::VarString CSCOrderTypeBatchConfigSqlMapper::getSelectSQL( const basar::Int16 branchNo, const basar::VarString & orderType )
{
	// TODO
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "CSCOrderTypeBatchConfigSqlMapper::getSelectSQL()" );

	std::stringstream ss;
	ss << "SELECT "
		"branchno, "
		"cscordertype, "
		"allowdesiredbatch, "
		"allowfixedbatch, "
		"forbiduserchange "
		"FROM ordertypebatchconfig WHERE branchno = " << branchNo << " AND cscordertype = '" << orderType << "'";

	BLOG_TRACE( LoggerPool::getLoggerParameter(), ss.str().c_str() );

	return ss.str();

}

const basar::VarString CSCOrderTypeBatchConfigSqlMapper::getInsertSQL( const CSCOrderTypeBatchConfigPtr batchConfig )
{
	// TODO
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "CSCOrderTypeBatchConfigSqlMapper::getInsertSQL()" );

	std::stringstream ss;
	ss << "INSERT INTO ordertypebatchconfig "
		"( "
		"branchno, "
		"cscordertype, "
		"allowdesiredbatch, "
		"allowfixedbatch, "
		"forbiduserchange "
		") VALUES ( "
		<< batchConfig->getBranchNo().get() << ", "
		<< "'" << batchConfig->getOrderType().c_str() << "', "
		<< ( batchConfig->getAllowDesiredBatch() ? "1" : "0" ) << ", "
		<< ( batchConfig->getAllowFixedBatch().get() ? "1" : "0" ) << ", "
		<< ( batchConfig->getForbidUserChange().get() ? "1" : "0" ) << " "
		") ";

	BLOG_TRACE( LoggerPool::getLoggerParameter(), ss.str().c_str() );

    return ss.str().c_str();
}

const basar::VarString CSCOrderTypeBatchConfigSqlMapper::getUpdateSQL( const CSCOrderTypeBatchConfigPtr batchConfig )
{
	// TODO
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "CSCOrderTypeBatchConfigSqlMapper::getUpdateSQL()" );

	std::stringstream ss;
	ss << "UPDATE ordertypebatchconfig set "
		"allowdesiredbatch = " << (batchConfig->getAllowDesiredBatch() ? "1" : "0") <<
		",allowfixedbatch = " << (batchConfig->getAllowFixedBatch().get() ? "1" : "0") <<
		",forbiduserchange = " << (batchConfig->getForbidUserChange().get() ? "1" : "0") <<
		"WHERE " <<
		"branchno = " << batchConfig->getBranchNo().get() <<
		"and cscordertype = '" << batchConfig->getOrderType().c_str() <<
		"' "
		;

	BLOG_TRACE( LoggerPool::getLoggerParameter(), ss.str().c_str() );

    return ss.str().c_str();
}

const basar::VarString CSCOrderTypeBatchConfigSqlMapper::getDeleteSQL( const CSCOrderTypeBatchConfigPtr batchConfig )
{
	// TODO
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "CSCOrderTypeBatchConfigSqlMapper::getDeleteSQL()" );

	std::stringstream ss;
	ss << "DELETE FROM ordertypebatchconfig WHERE branchno = " << batchConfig->getBranchNo().get() << " AND cscordertype = '" << batchConfig->getOrderType().c_str() << "'";

	BLOG_TRACE( LoggerPool::getLoggerParameter(), ss.str().c_str() );

    return ss.str().c_str();
}

} // end namespace cscordertype
} // end namespace libcsc
