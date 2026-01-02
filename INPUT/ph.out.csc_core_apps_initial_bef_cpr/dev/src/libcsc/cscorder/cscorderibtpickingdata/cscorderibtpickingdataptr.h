#ifndef GUARD_LIBCSC_CSCORDER_DOMMOD_CSCORDERIBTPICKINGDATAPTR_H
#define GUARD_LIBCSC_CSCORDER_DOMMOD_CSCORDERIBTPICKINGDATAPTR_H

#include <boost/make_shared.hpp>

namespace libcsc {
namespace cscorder {
namespace domMod {

class CSCOrderIBTPickingdata;
typedef boost::shared_ptr<CSCOrderIBTPickingdata> CSCOrderIBTPickingdataPtr;

inline CSCOrderIBTPickingdataPtr makeCSCOrderIBTPickingdata()
{
    return boost::make_shared<CSCOrderIBTPickingdata>();
}

} // namespace domMod
} // namespace cscorder
} // namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_DOMMOD_CSCORDERIBTPICKINGDATAPTR_H
