#include "sapreferencenouc.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include "pxxmit.hpp"
#include "pxorderremarks.hpp"
#include "domainmodule/phadextransaction/transactionrecord/sapreferencenorecord/isapreferencenorecord.h"

namespace csc_phadex
{
namespace useCase
{
SAPReferenceNoUC::SAPReferenceNoUC()
: m_Logger( LoggerPool::getLoggerUseCases() )
{
    METHODNAME_DEF(SAPReferenceNoUC, SAPReferenceNoUC);
    BLOG_TRACE_METHOD( m_Logger, fun );
}

SAPReferenceNoUC::~SAPReferenceNoUC()
{
    METHODNAME_DEF(SAPReferenceNoUC, ~SAPReferenceNoUC);
    BLOG_TRACE_METHOD( m_Logger, fun );
}

void SAPReferenceNoUC::injectPxOrderTransmit(pxOrderTransmitPtr xmit)
{
    m_pxOrderTransmit = xmit;
}

void SAPReferenceNoUC::setSAPReferenceNoRecord( csc_phadex::domMod::phadexTransaction::ISAPReferenceNoRecordPtr sapReferenceNoRecord)
{
    m_SAPReferenceNoRecord = sapReferenceNoRecord;
}

void SAPReferenceNoUC::run()
{
    METHODNAME_DEF(SAPReferenceNoUC, run );
    BLOG_TRACE_METHOD( m_Logger, fun );

    pxGenericOrderRemarkList remarklist(m_pxOrderTransmit.get());
    remarklist.SelectOrderRemarksByOrderNoAndType(m_SAPReferenceNoRecord->getCscOrderNo(), eSAPReferenceNo);
    
    if (remarklist.Entries() > 0)
    {
        remarklist.ChangeOrderRemark(m_SAPReferenceNoRecord->getCscOrderNo(), 0,
            eSAPReferenceNo, m_SAPReferenceNoRecord->getSapReferenceNo());
	}
	else
	{
        remarklist.AddOrderRemark(m_SAPReferenceNoRecord->getCscOrderNo(), 0,
            eSAPReferenceNo, m_SAPReferenceNoRecord->getSapReferenceNo());
	}
}


} // namespace usecase
} // namespace csc_phadex
