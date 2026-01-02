#ifndef GUARD_CSC_PHADEX_DOMMOD_I_DELIVERY_NOTE_CANCELLATION_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_I_DELIVERY_NOTE_CANCELLATION_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
    class IDeliveryNoteCancellation;
    typedef boost::shared_ptr< csc_phadex::domMod::phadexTransaction::IDeliveryNoteCancellation > IDeliveryNoteCancellationPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_I_DELIVERY_NOTE_CANCELLATION_PTR_H
