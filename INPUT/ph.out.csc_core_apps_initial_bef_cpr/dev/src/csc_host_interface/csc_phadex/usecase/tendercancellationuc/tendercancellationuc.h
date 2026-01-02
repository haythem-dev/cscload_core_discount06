#ifndef GUARD_CSC_PHADEX_USECASE_TENDERCANCELLATION_UC_H
#define GUARD_CSC_PHADEX_USECASE_TENDERCANCELLATION_UC_H

#include "itendercancellationuc.h"
#include <domainmodule/phadextransaction/transactionrecord/tenderinvoicecancellation/itenderinvoicecancellationrecordptr.h>
#include <pxordertransmitptr.h>


namespace log4cplus
{
	class Logger;
}

namespace csc_phadex
{
namespace useCase
{
class TenderCancellationUC : public ITenderCancellationUC
{
public:
	TenderCancellationUC();
	virtual ~TenderCancellationUC();

	virtual void run();
    virtual void setTenderInvoiceCancellationRecord( csc_phadex::domMod::phadexTransaction::ITenderInvoiceCancellationRecordPtr tr );
	virtual void injectPxOrderTransmit(pxOrderTransmitPtr xmit);

private:
	TenderCancellationUC( const TenderCancellationUC & );
	TenderCancellationUC & operator= ( const TenderCancellationUC & );

    csc_phadex::domMod::phadexTransaction::ITenderInvoiceCancellationRecordPtr m_InvoiceCancellation; 
	pxOrderTransmitPtr          m_pxOrderTransmit;
	const log4cplus::Logger & m_Logger;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_TENDERCANCELLATION_UC_H
