#ifndef GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace cicsTransaction
{
	class ICICSTransaction;
	typedef boost::shared_ptr< csc_phadex::domMod::cicsTransaction::ICICSTransaction > ICICSTransactionPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_I_CICS_TRANSACTION_PTR_H
