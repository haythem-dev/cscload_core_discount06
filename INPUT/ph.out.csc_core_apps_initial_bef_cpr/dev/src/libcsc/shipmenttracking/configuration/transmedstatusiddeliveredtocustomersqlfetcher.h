#ifndef GUARD_LIBCSC_DOCUMENT_TRANSMEDSTATUSIDDELIVEREDTOCUSTOMERSQLFETCHER_H
#define GUARD_LIBCSC_DOCUMENT_TRANSMEDSTATUSIDDELIVEREDTOCUSTOMERSQLFETCHER_H

#include "shipmenttracking/shipmenttrackingdatafilter.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace shipmenttracking {

class TransmedStatusIdDeliveredToCustomerSqlFetcher
{
public:
    TransmedStatusIdDeliveredToCustomerSqlFetcher(const basar::db::sql::ResultsetRef resultSet);
    virtual ~TransmedStatusIdDeliveredToCustomerSqlFetcher();

    static const basar::VarString getSelectSQL(const basar::VarString& dbNameWarehouse);

    basar::Int16    fetch();

private:
    // prohibit copy constructor and assignment operator:
    TransmedStatusIdDeliveredToCustomerSqlFetcher(const TransmedStatusIdDeliveredToCustomerSqlFetcher&);
    TransmedStatusIdDeliveredToCustomerSqlFetcher & operator=(const TransmedStatusIdDeliveredToCustomerSqlFetcher&);

    const basar::db::sql::ResultsetRef      m_ResultSet;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_TRANSMEDSTATUSIDDELIVEREDTOCUSTOMERSQLFETCHER_H
