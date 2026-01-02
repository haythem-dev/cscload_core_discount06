#ifndef GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_COLLECTION_FINDER_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_COLLECTION_FINDER_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace cicsTransaction
{
	class ICICSTransactionCollectionFinder;
	typedef boost::shared_ptr< csc_phadex::domMod::cicsTransaction::ICICSTransactionCollectionFinder > ICICSTransactionCollectionFinderPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_COLLECTION_FINDER_PTR_H
