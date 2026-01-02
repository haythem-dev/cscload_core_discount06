#ifndef GUARD_CSC_PHADEX_DOMMOD_I_TRANSACTION_RECORD_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_I_TRANSACTION_RECORD_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
	class ITransactionRecord;
	typedef boost::shared_ptr< csc_phadex::domMod::phadexTransaction::ITransactionRecord > ITransactionRecordPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_I_TRANSACTION_RECORD_PTR_H
