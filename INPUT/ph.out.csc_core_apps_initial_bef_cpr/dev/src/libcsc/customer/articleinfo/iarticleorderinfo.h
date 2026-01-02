#ifndef GUARD_LIBCSC_CUSTOMER_IARTICLEORDERINFO_H
#define GUARD_LIBCSC_CUSTOMER_IARTICLEORDERINFO_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace customer {

    class IArticleOrderInfo
    {
    public:
        virtual ~IArticleOrderInfo() {}

        virtual basar::Int32 getArticleOrderDate() const = 0;
        virtual basar::Int32 getArticleGoodsReceiptTargetDate() const = 0;
        virtual bool getIsArticleOrderEffective() const = 0;
    };

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_IARTICLEORDERINFO_H
