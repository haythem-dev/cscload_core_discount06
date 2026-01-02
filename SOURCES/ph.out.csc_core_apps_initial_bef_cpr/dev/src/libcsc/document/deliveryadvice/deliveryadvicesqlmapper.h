#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICESQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICESQLMAPPER_H

#include "deliveryadvicemapperbase.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace document {

class DeliveryAdviceSQLMapper : public DeliveryAdviceMapperBase
{
public:
    DeliveryAdviceSQLMapper(DeliveryAdvicePtr deliveryAdvice, const basar::db::sql::ResultsetRef resultSet);
    virtual ~DeliveryAdviceSQLMapper();

    static const basar::VarString getSelectByDateRangeSQL(
        const basar::VarString& dbName,
        const basar::Int16& branchNo,
        const basar::Int32& customerNo,
        const enum ConfirmationStatusEnum& confirmationStatus,
        const basar::Date& searchPeriodStart,
        const basar::Date& searchPeriodEnd
        );

    static const basar::VarString getSelectByKeySQL(
        const basar::VarString& dbName,
        const basar::Int16& branchNo,
        const basar::Int32& customerNo,
        const basar::Date& deliveryAdviceDate,
        const basar::VarString& deliveryAdviceNo,
        const basar::Int32& cscOrderNo,
        const bool& completedOnly
    );

    static const basar::VarString getSelectDnNumbersByReferencesSQL(
        const basar::VarString& dbName,
        const basar::Int16& branchNo,
        const basar::Int32& customerNo,
        const std::vector<std::string>& deliveryAdviceReferences);

    static const basar::VarString getSelectForBatchAdvice(
        const basar::VarString& dbName,
        const basar::Int16& branchNo,
        const bool& batchCorrectionOnly );

    static const basar::VarString getUpdateSQL( const basar::VarString & dbName, const DeliveryAdvicePtr deliveryAdvice );

protected:
    virtual void doMap();
    virtual void doMapKeysOnly();

private:
    DeliveryAdviceSQLMapper(const DeliveryAdviceSQLMapper&);
    DeliveryAdviceSQLMapper & operator=(const DeliveryAdviceSQLMapper&);

    const basar::db::sql::ResultsetRef      m_ResultSet;

    static const basar::VarString getCommonSelectPartSQL(
        const basar::VarString& dbName, const basar::Int16& branchNo, const basar::Int32& customerNo, const bool onlyFirstResult);
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICESQLMAPPER_H
