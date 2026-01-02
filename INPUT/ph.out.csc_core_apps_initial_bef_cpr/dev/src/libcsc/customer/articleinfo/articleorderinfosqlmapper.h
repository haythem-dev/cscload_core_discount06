#ifndef GUARD_LIBCSC_CUSTOMER_ARTICLEORDERINFOSQLMAPPER_H
#define GUARD_LIBCSC_CUSTOMER_ARTICLEORDERINFOSQLMAPPER_H

#include <customer/articleinfo/articleorderinfomapperbase.h>

#include <libbasardbsql_resultsetref.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class ArticleOrderInfoSqlMapper : public ArticleOrderInfoMapperBase
{
public:
    ArticleOrderInfoSqlMapper(ArticleOrderInfoPtr ArticleOrderInfo, const basar::db::sql::ResultsetRef resultSet);
    virtual ~ArticleOrderInfoSqlMapper();

    static const basar::VarString getSelectSQL(const basar::Int16 branchNo, const basar::Int32 articleNo);

protected:
    virtual void doMap();

private:
    ArticleOrderInfoSqlMapper(const ArticleOrderInfoSqlMapper&);
    ArticleOrderInfoSqlMapper& operator=(const ArticleOrderInfoSqlMapper&);

    const basar::db::sql::ResultsetRef  m_ResultSet;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ARTICLEORDERINFOSQLMAPPER_H
