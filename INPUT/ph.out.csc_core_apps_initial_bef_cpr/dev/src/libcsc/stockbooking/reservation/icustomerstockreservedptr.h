#ifndef GUARD_LIBCSC_STOCKBOOKING_I_CUSTOMERSTOCKRESERVED_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_I_CUSTOMERSTOCKRESERVED_PTR_H

#include <boost/shared_ptr.hpp>
#include <vector>

namespace libcsc {
namespace stockbooking {

class ICustomerStockReserved;
typedef boost::shared_ptr<ICustomerStockReserved> ICustomerStockReservedPtr;

typedef std::vector<ICustomerStockReservedPtr> ICustomerStockReservedCollection;

typedef boost::shared_ptr<ICustomerStockReservedCollection> ICustomerStockReservedCollectionPtr;

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_CUSTOMERSTOCKRESERVED_PTR_H
