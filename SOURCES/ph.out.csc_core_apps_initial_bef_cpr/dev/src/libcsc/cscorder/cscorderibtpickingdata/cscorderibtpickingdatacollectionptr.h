#ifndef GUARD_LIBCSC_CALLBACK_DOMMOD_CSCORDERIBTPICKINGDATACOLLETIONPTR_H
#define GUARD_LIBCSC_CALLBACK_DOMMOD_CSCORDERIBTPICKINGDATACOLLETIONPTR_H

#include <boost/make_shared.hpp>
#include "cscorderibtpickingdataposcollection.h"

namespace libcsc {
namespace cscorder {
namespace domMod {

typedef boost::shared_ptr<CSCOrderIBTPickingdataCollection> CSCOrderIBTPickingdataCollectionPtr;

inline CSCOrderIBTPickingdataCollectionPtr makeCSCOrderIBTPickingdataCollection()
{
    return boost::make_shared<CSCOrderIBTPickingdataCollection>();
}

} // namespace domMod
} // namespace cscorder
} // namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_DOMMOD_CSCORDERIBTPICKINGDATACOLLETIONPTR_H
