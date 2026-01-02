#ifndef GUARD_LIBCSC_CUSTOMER_PROMOTIONSSQL_H
#define GUARD_LIBCSC_CUSTOMER_PROMOTIONSSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

class PromotionsSql
{
public:
    ~PromotionsSql();

    static const basar::VarString GetPromotionsQuery(
        const basar::Int16 branchNo, const basar::Int32 customerNo, basar::Int32 today);

private:
    PromotionsSql();
    PromotionsSql& operator=(const PromotionsSql&);
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_PROMOTIONSSQL_H
