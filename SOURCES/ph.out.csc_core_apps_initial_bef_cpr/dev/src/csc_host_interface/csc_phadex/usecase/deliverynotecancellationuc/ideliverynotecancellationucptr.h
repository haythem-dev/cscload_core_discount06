#ifndef GUARD_CSC_PHADEX_USECASE_I_DELIVERYNOTECANCELLATION_UC_PTR_H
#define GUARD_CSC_PHADEX_USECASE_I_DELIVERYNOTECANCELLATION_UC_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace useCase
{
    class IDeliveryNoteCancellationUC;
    typedef boost::shared_ptr< IDeliveryNoteCancellationUC > IDeliveryNoteCancellationUCPtr;
}
}

#endif //end GUARD_CSC_PHADEX_USECASE_I_DELIVERYNOTECANCELLATION_UC_PTR_H
