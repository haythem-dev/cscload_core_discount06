#include "tendercancellationuc.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include <libutil/util.h>
#include <domainmodule/phadextransaction/transactionrecord/tenderinvoicecancellation/itenderinvoicecancellationrecordptr.h>
#include <domainmodule/phadextransaction/transactionrecord/tenderinvoicecancellation/tenderinvoicecancellationrecord.h>
#include <pxtenderprogress.hpp>
#include <pxxmit.hpp>

namespace csc_phadex
{
namespace useCase
{
TenderCancellationUC::TenderCancellationUC()
: m_Logger( LoggerPool::getLoggerUseCases() )
{
	METHODNAME_DEF( TenderCancellationUC, TenderCancellationUC );
	BLOG_TRACE_METHOD( m_Logger, fun );
}

TenderCancellationUC::~TenderCancellationUC()
{
	METHODNAME_DEF( TenderCancellationUC, ~TenderCancellationUC );
	BLOG_TRACE_METHOD( m_Logger, fun );
}

void TenderCancellationUC::injectPxOrderTransmit(pxOrderTransmitPtr xmit)
{
	m_pxOrderTransmit = xmit;
}


void TenderCancellationUC::setTenderInvoiceCancellationRecord(csc_phadex::domMod::phadexTransaction::ITenderInvoiceCancellationRecordPtr tenderCanceldm )
{
    m_InvoiceCancellation = tenderCanceldm;
}

void TenderCancellationUC::run()
{
    METHODNAME_DEF( TenderCancellationUC, run );
    BLOG_TRACE_METHOD( m_Logger, fun );

    try
    {
		pxTenderProgressList tplist(m_pxOrderTransmit.get());
		tplist.Select(m_InvoiceCancellation->getArticleNo(), m_InvoiceCancellation->getOrderNo(), nDate(m_InvoiceCancellation->getInvoiceDate()));
		if (tplist.Entries() == 0)
		{
			return;
		}
		pxTenderProgress* tp = static_cast<pxTenderProgress*>(tplist.At(0));
		m_pxOrderTransmit->nDBBeginTransaction();
		if (0 == tp->Get(cDBGET_FORUPDATE))
		{
			tp->SetReturnQty(m_InvoiceCancellation->getInvoiceQty());
			tp->Put();
		}
		if (tp->IsGoodState())
		{
			m_pxOrderTransmit->nDBCommit();
		}
		else
		{
			m_pxOrderTransmit->nDBRollBack();
		}
    }
    catch(const basar::Exception & e )
    {
        BLOG_ERROR( m_Logger, e.what() );
    }
}

} // namespace usecase
} // namespace csc_phadex
