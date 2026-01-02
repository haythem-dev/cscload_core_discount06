#ifndef GUARD_CSC_PHADEX_DOMMOD_I_TENDER_INVOICE_CANCELLATION_RECORD_PTR_H
#define GUARD_CSC_PHADEX_DOMMOD_I_TENDER_INVOICE_CANCELLATION_RECORD_PTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
namespace domMod
{
namespace phadexTransaction
{
	class ITenderInvoiceCancellationRecord;
	typedef boost::shared_ptr< csc_phadex::domMod::phadexTransaction::ITenderInvoiceCancellationRecord > ITenderInvoiceCancellationRecordPtr;
}
}
}

#endif // GUARD_CSC_PHADEX_DOMMOD_I_TENDER_INVOICE_CANCELLATION_RECORD_PTR_H
