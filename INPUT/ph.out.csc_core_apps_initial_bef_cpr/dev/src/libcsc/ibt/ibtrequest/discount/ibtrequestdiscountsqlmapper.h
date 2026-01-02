#ifndef GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_SQLMAPPER_H
#define GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_SQLMAPPER_H

#include <ibt/ibtrequest/discount/ibtrequestdiscountmapperbase.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc
{
namespace ibt
{
class IbtRequestDiscountSqlMapper : public IbtRequestDiscountMapperBase
{
public:
	IbtRequestDiscountSqlMapper( IbtRequestDiscountPtr ibtRequestDiscount, const basar::db::sql::ResultsetRef resultSet );
	virtual ~IbtRequestDiscountSqlMapper();

	static bool isInsertable( const IbtRequestDiscountPtr ibtRequestDiscount );
	static bool isUpdatable( const IbtRequestDiscountPtr ibtRequestDiscount );
	static bool isDeletable( const IbtRequestDiscountPtr ibtRequestDiscount );

	static const basar::VarString getSelectSQL( const basar::Int32 ibtRequestId );
	static const basar::VarString getInsertSQL( const IbtRequestDiscountPtr ibtRequestDiscount );
	static const basar::VarString getUpdateSQL( const IbtRequestDiscountPtr ibtRequestDiscount );
	static const basar::VarString getDeleteSQL( const IbtRequestDiscountPtr ibtRequestDiscount );

protected:
    virtual void doMap();

private:
	IbtRequestDiscountSqlMapper( const IbtRequestDiscountSqlMapper & );
	IbtRequestDiscountSqlMapper & operator=( const IbtRequestDiscountSqlMapper & );

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUESTDISCOUNT_SQLMAPPER_H
