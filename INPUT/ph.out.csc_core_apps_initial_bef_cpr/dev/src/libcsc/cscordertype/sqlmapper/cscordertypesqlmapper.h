#ifndef GUARD_LIBCSC_CSCORDERTYPE_MAPPER_H
#define GUARD_LIBCSC_CSCORDERTYPE_MAPPER_H

#include "cscordertypemapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <persistence/isqlparameterbinderptr.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace cscordertype
{
class CSCOrderTypeSqlMapper : public CSCOrderTypeMapperBase
{
public:
    CSCOrderTypeSqlMapper( 
        CSCOrderTypePtr orderType, 
        const basar::db::sql::ResultsetRef resultSet 
            );
    virtual ~CSCOrderTypeSqlMapper();

	static bool isInsertable( const CSCOrderTypePtr orderType );
	static bool isUpdatable( const CSCOrderTypePtr orderType );
	static bool isDeletable( const CSCOrderTypePtr orderType );
    
	static const basar::VarString getMultiSelectSQL( const basar::Int16 branchNo );
	static const basar::VarString getSingleSelectSQL( const basar::Int16 branchNo, const basar::VarString & orderType );
	static const basar::VarString getInsertSQL( const CSCOrderTypePtr orderType );
	static const basar::VarString getUpdateSQL( const CSCOrderTypePtr orderType );
	static const basar::VarString getDeleteSQL( const CSCOrderTypePtr orderType );

protected:
    virtual void doMap();

private:
    CSCOrderTypeSqlMapper( const CSCOrderTypeSqlMapper & );
    CSCOrderTypeSqlMapper & operator=( const CSCOrderTypeSqlMapper & );
    
    const basar::db::sql::ResultsetRef  m_ResultSet;
};

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDERTYPE_MAPPER_H
