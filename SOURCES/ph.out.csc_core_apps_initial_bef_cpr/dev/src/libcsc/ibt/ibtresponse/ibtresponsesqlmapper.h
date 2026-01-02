#ifndef GUARD_LIBCSC_IBT_IBTRESPONSE_SQLMAPPER_H
#define GUARD_LIBCSC_IBT_IBTRESPONSE_SQLMAPPER_H

#include <ibt/ibtresponse/ibtresponsemapperbase.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc
{
namespace ibt
{
class IbtResponseSqlMapper : public IbtResponseMapperBase
{
public:
    IbtResponseSqlMapper( IbtResponsePtr ibtResponse, const basar::db::sql::ResultsetRef resultSet );
    virtual ~IbtResponseSqlMapper();

    static bool isInsertable( const IbtResponsePtr ibtResponse );    
    static bool isUpdateable( const IbtResponsePtr ibtResponse );    
	static const basar::VarString getInsertSQL( const IbtResponsePtr ibtResponse );
	static const basar::VarString getUpdateSQL( const IbtResponsePtr ibtResponse );
	static const basar::VarString getSelectSQL( const basar::Int32 ibtOrderNo, const basar::Int32 ibtPosNo );
    
protected:
    virtual void doMap();

private:
	IbtResponseSqlMapper( const IbtResponseSqlMapper & );
	IbtResponseSqlMapper & operator=( const IbtResponseSqlMapper & );

    const basar::db::sql::ResultsetRef m_ResultSet;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTRESPONSE_SQLMAPPER_H
