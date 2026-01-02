#ifndef GUARD_CSC_PHADEX_USECASE_DELIVERYNOTECOMPLETED_UC_H
#define GUARD_CSC_PHADEX_USECASE_DELIVERYNOTECOMPLETED_UC_H

#include "ideliverynotecompleteduc.h"
#include <domainmodule/phadextransaction/transactionrecord/deliverynotecompleted/ideliverynotecompletedptr.h>
#include "document/deliveryadvice/deliveryadvicelineibtlink/deliveryadvicelineibtlinkptr.h"
#include <pxordertransmitptr.h>
#include <libbasar_definitions.h>

namespace log4cplus
{
    class Logger;
}

namespace csc_phadex
{
namespace useCase
{
class DeliveryNoteCompletedUC : public IDeliveryNoteCompletedUC
{
public:
    DeliveryNoteCompletedUC();
    virtual ~DeliveryNoteCompletedUC();

    virtual void run();
    virtual void setDeliveryNoteCompletedRecord( csc_phadex::domMod::phadexTransaction::IDeliveryNoteCompletedPtr tr );
    virtual void injectPxOrderTransmit( pxOrderTransmitPtr xmit );

private:
    DeliveryNoteCompletedUC( const DeliveryNoteCompletedUC & );
    DeliveryNoteCompletedUC & operator= ( const DeliveryNoteCompletedUC & );

    void completeCustomerOrder();
    void completeShuttleOrder();
    basar::Int32 writePickingData(libcsc::document::DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink);
    void decreaseQuantityConfirmed(
        libcsc::document::DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink, basar::Int32 sumLackQty);
    void clearWaitForIbtPickingFlag(basar::Int32 cscOrderNo);
    void checkCustomerOrderForCompletion(libcsc::document::DeliveryAdviceLineIbtLinkPtr ibtLink);
    void setShuttleOrdertoCompleted(libcsc::document::DeliveryAdviceLineIbtLinkPtr ibtLink);

    csc_phadex::domMod::phadexTransaction::IDeliveryNoteCompletedPtr m_DeliveryNoteCompletedRecord;
    pxOrderTransmitPtr          m_pxOrderTransmit;
    const log4cplus::Logger&    m_Logger;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_DELIVERYNOTECOMPLETED_UC_H
