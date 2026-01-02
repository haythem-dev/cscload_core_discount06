#ifndef GUARD_CSC_PHADEX_USECASE_SAPREFERENCENO_UC_H
#define GUARD_CSC_PHADEX_USECASE_SAPREFERENCENO_UC_H

#include "isapreferencenouc.h"
#include <pxordertransmitptr.h>
#include "domainmodule/phadextransaction/transactionrecord/sapreferencenorecord/isapreferencenorecordptr.h"
//#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>

namespace log4cplus
{
    class Logger;
}

namespace csc_phadex
{
namespace useCase
{
class SAPReferenceNoUC : public ISAPReferenceNoUC
{
public:
    SAPReferenceNoUC();
    virtual ~SAPReferenceNoUC();
    
    virtual void run();
    virtual void setSAPReferenceNoRecord( csc_phadex::domMod::phadexTransaction::ISAPReferenceNoRecordPtr );
    virtual void injectPxOrderTransmit(pxOrderTransmitPtr xmit);

private:
    SAPReferenceNoUC( const SAPReferenceNoUC& );
    SAPReferenceNoUC& operator= ( const SAPReferenceNoUC& );
    
    csc_phadex::domMod::phadexTransaction::ISAPReferenceNoRecordPtr m_SAPReferenceNoRecord;
    pxOrderTransmitPtr											 m_pxOrderTransmit;
    const log4cplus::Logger & m_Logger;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_SAPREFERENCENO_UC_H
