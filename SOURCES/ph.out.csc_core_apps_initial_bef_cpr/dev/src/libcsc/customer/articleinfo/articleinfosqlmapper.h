#ifndef GUARD_LIBCSC_CUSTOMER_ARTICLEINFOSQLMAPPER_H
#define GUARD_LIBCSC_CUSTOMER_ARTICLEINFOSQLMAPPER_H

#include <customer/articleinfo/articleinfomapperbase.h>
#include "types/articleinquiryperioddatetypeenum.inc"

#include <libbasardbsql_resultsetref.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class ArticleInfoSqlMapper : public ArticleInfoMapperBase
{
public:
    ArticleInfoSqlMapper(
        ArticleInfoPtr articleInfo,
        const basar::db::sql::ResultsetRef resultSet
            );
    virtual ~ArticleInfoSqlMapper();

    static const basar::VarString getSelectSQL(const basar::Int16 branchNo, const basar::Int32 articleNo);
    static const basar::VarString getSelectArtInfoTextSQL(const basar::Int32 articleNo);

    static const basar::VarString getSelectArticleNosByPeriodSQL(const basar::Int16 branchNo, basar::Int32 positionsPerPage,
        const basar::Int32 articleNoFrom, const basar::Int32 dateFrom, const basar::Int32 dateTo, ArticleInquiryPeriodDateTypeEnum dateType);

protected:
    virtual void doMap();
    virtual void doMapArtInfoText();

private:
    ArticleInfoSqlMapper(const ArticleInfoSqlMapper&);
    ArticleInfoSqlMapper& operator=(const ArticleInfoSqlMapper&);

    const basar::db::sql::ResultsetRef  m_ResultSet;

    const int m_BitNumberNarcoticInEtartklasse1;

    const int m_BitNumberColdchainInEtartschalter1;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ARTICLEINFOSQLMAPPER_H
