#ifndef GUARD_LIBCSC_IBT_IBTREQUEST_SQLMAPPER_H
#define GUARD_LIBCSC_IBT_IBTREQUEST_SQLMAPPER_H

#include <ibt/ibtrequest/ibtrequestmapperbase.h>
#include <ibt/ibtrequest/ibtrequestkey.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc
{
namespace ibt
{
class IbtRequestSqlMapper : public IbtRequestMapperBase
{
public:
	IbtRequestSqlMapper( IbtRequestPtr ibtRequest, const basar::db::sql::ResultsetRef resultSet );
	virtual ~IbtRequestSqlMapper();

	static bool isInsertable( const IbtRequestPtr ibtRequest );
	static bool isUpdatable( const IbtRequestPtr ibtRequest );
	static bool isDeletable( const IbtRequestPtr ibtRequest );

	static const basar::VarString getSelectSQL( const basar::Int32 id );
	static const basar::VarString getSelectSQL( const IbtRequestKey & key );
	static const basar::VarString getSelectSQL( const IbtRequestPtr ibtRequest );
	static const basar::VarString getInsertSQL( const IbtRequestPtr ibtRequest );
	static const basar::VarString getUpdateSQL( const IbtRequestPtr ibtRequest );
	static const basar::VarString getDeleteSQL( const IbtRequestPtr ibtRequest );

	static const basar::VarString getMultiSelectSQL( const basar::Int16 branchno, const IbtRequestProcessingStateEnum state );

protected:
    virtual void doMap();

private:
	IbtRequestSqlMapper( const IbtRequestSqlMapper & );
	IbtRequestSqlMapper & operator=( const IbtRequestSqlMapper & );

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUEST_SQLMAPPER_H
