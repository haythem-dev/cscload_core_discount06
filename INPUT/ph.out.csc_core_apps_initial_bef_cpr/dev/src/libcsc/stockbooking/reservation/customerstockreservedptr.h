#ifndef GUARD_LIBCSC_STOCKBOOKING_CUSTOMERSTOCKRESERVED_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_CUSTOMERSTOCKRESERVED_PTR_H

#include <boost/shared_ptr.hpp>
#include <vector>

namespace libcsc {
namespace stockbooking {

class CustomerStockReserved;
typedef boost::shared_ptr<CustomerStockReserved> CustomerStockReservedPtr;

//typedef std::vector<CustomerStockReservedPtr> CustomerStockReservedCollection;

//typedef boost::shared_ptr<CustomerStockReservedCollection> CustomerStockReservedCollectionPtr;

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_CUSTOMERSTOCKRESERVED_PTR_H
