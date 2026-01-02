#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERSQLMAPPER_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERSQLMAPPER_H

#include <customer/customermapperbase.h>

#include <libbasardbsql_resultsetref.h>
#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class CustomerSqlMapper : public CustomerMapperBase
{
public:
    CustomerSqlMapper(
        CustomerPtr customer, 
        const basar::db::sql::ResultsetRef resultSet 
            );
    virtual ~CustomerSqlMapper();

    static const basar::VarString getSelectSQL(const basar::Int16 branchNo, const basar::Int32 customerno,
        bool withTender, bool withCreditLimit, bool withLogisticSurcharge);

    static const basar::VarString getUpdateCreditLimitSQL(const basar::Int32 partnerNo,
        const basar::Decimal& newLimit);

protected:
    virtual void doMap(int countryPhoneCode);
    virtual void doMapTender();
    virtual void doMapCreditLimit();
    virtual void doMapLogisticSurcharge();

private:
    CustomerSqlMapper(const CustomerSqlMapper&);
    CustomerSqlMapper& operator=(const CustomerSqlMapper&);
    
    const basar::db::sql::ResultsetRef  m_ResultSet;
};

} // end namespace cscordertype
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERSQLMAPPER_H
