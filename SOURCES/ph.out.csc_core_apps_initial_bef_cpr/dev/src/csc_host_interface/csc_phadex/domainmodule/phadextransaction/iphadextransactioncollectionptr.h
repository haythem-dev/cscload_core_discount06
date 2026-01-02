#ifndef GUARD_CSC_PHADEX_DOMMOD_I_PHADEX_TRANSACTION_COLLECTION_FINDER_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_I_PHADEX_TRANSACTION_COLLECTION_FINDER_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
    class IPhadexTransactionCollection;
    typedef boost::shared_ptr< csc_phadex::domMod::phadexTransaction::IPhadexTransactionCollection > IPhadexTransactionCollectionPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_I_PHADEX_TRANSACTION_COLLECTION_FINDER_PTR_H
