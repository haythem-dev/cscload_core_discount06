#ifndef GUARD_LIBCSC_CUSTOMER_IARTICLEORDERINFOPTR_H
#define GUARD_LIBCSC_CUSTOMER_IARTICLEORDERINFOPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc {
namespace customer {

    class IArticleOrderInfo;
    typedef boost::shared_ptr<IArticleOrderInfo> IArticleOrderInfoPtr;

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_IARTICLEORDERINFOPTR_H
