#ifndef GUARD_LIBCSC_CSCORDERTYPE_BATCHCONFIG_SQLMAPPER_H
#define GUARD_LIBCSC_CSCORDERTYPE_BATCHCONFIG_SQLMAPPER_H

#include <cscordertype/cscordertypebatchconfig/cscordertypebatchconfigmapperbase.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc
{
namespace cscordertype
{
class CSCOrderTypeBatchConfigSqlMapper: public CSCOrderTypeBatchConfigMapperBase
{
public:
	CSCOrderTypeBatchConfigSqlMapper( CSCOrderTypeBatchConfigPtr batchConfig, const basar::db::sql::ResultsetRef resultSet );
	virtual ~CSCOrderTypeBatchConfigSqlMapper();

	static bool isInsertable( const CSCOrderTypeBatchConfigPtr batchConfig );
	static bool isUpdatable( const CSCOrderTypeBatchConfigPtr batchConfig );
	static bool isDeletable( const CSCOrderTypeBatchConfigPtr batchConfig );

	static const basar::VarString getSelectSQL( const basar::Int16 branchNo, const basar::VarString & orderType );
	static const basar::VarString getInsertSQL( const CSCOrderTypeBatchConfigPtr batchConfig );
	static const basar::VarString getUpdateSQL( const CSCOrderTypeBatchConfigPtr batchConfig );
	static const basar::VarString getDeleteSQL( const CSCOrderTypeBatchConfigPtr batchConfig );

protected:
    virtual void doMap();

private:
	CSCOrderTypeBatchConfigSqlMapper( const CSCOrderTypeBatchConfigSqlMapper & );
	CSCOrderTypeBatchConfigSqlMapper & operator=( const CSCOrderTypeBatchConfigSqlMapper & );

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_BATCHCONFIG_SQLMAPPER_H
