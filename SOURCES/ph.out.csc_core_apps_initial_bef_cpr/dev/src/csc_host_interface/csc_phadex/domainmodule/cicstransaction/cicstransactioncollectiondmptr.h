#ifndef GUARD_CSC_PHADEX_DOMMOD_CICS_TRANSACTION_COLLECTION_DM_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_CICS_TRANSACTION_COLLECTION_DM_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace cicsTransaction
{
	class CICSTransactionCollectionDM;
	typedef boost::shared_ptr< csc_phadex::domMod::cicsTransaction::CICSTransactionCollectionDM > CICSTransactionCollectionDMPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_CICS_TRANSACTION_COLLECTION_DM_PTR_H
