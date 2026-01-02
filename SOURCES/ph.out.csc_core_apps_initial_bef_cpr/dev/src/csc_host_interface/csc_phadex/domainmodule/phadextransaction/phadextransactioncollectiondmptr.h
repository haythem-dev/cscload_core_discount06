#ifndef GUARD_CSC_PHADEX_DOMMOD_PHADEX_TRANSACTION_COLLECTION_DM_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_PHADEX_TRANSACTION_COLLECTION_DM_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
	class PhadexTransactionCollectionDM;
	typedef boost::shared_ptr< csc_phadex::domMod::phadexTransaction::PhadexTransactionCollectionDM > PhadexTransactionCollectionDMPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_PHADEX_TRANSACTION_COLLECTION_DM_PTR_H
