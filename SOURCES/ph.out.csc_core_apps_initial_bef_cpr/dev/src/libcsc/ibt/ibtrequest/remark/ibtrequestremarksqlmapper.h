#ifndef GUARD_LIBCSC_IBT_IBTREQUESTREMARK_SQLMAPPER_H
#define GUARD_LIBCSC_IBT_IBTREQUESTREMARK_SQLMAPPER_H

#include <ibt/ibtrequest/remark/ibtrequestremarkmapperbase.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc
{
namespace ibt
{
class IbtRequestRemarkSqlMapper : public IbtRequestRemarkMapperBase
{
public:
    IbtRequestRemarkSqlMapper( IbtRequestRemarkPtr ibtRequestRemark, const basar::db::sql::ResultsetRef resultSet );
    virtual ~IbtRequestRemarkSqlMapper();

	static bool isInsertable( const IbtRequestRemarkPtr ibtRequestRemark );
	static bool isUpdatable( const IbtRequestRemarkPtr ibtRequestRemark );
	static bool isDeletable( const IbtRequestRemarkPtr ibtRequestRemark );

	static const basar::VarString getSelectSQL( const basar::Int32 ibtRequestId );
	static const basar::VarString getInsertSQL( const IbtRequestRemarkPtr ibtRequestRemark );
	static const basar::VarString getUpdateSQL( const IbtRequestRemarkPtr ibtRequestRemark );
	static const basar::VarString getDeleteSQL( const IbtRequestRemarkPtr ibtRequestRemark );

protected:
    virtual void doMap();

private:

	IbtRequestRemarkSqlMapper( const IbtRequestRemarkSqlMapper & );
	IbtRequestRemarkSqlMapper & operator=( const IbtRequestRemarkSqlMapper & );

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUESTREMARK_SQLMAPPER_H
