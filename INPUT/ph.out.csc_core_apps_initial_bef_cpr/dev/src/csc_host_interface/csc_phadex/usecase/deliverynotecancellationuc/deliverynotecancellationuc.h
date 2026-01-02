#ifndef GUARD_CSC_PHADEX_USECASE_DELIVERYNOTECANCELLATION_UC_H
#define GUARD_CSC_PHADEX_USECASE_DELIVERYNOTECANCELLATION_UC_H

#include "ideliverynotecancellationuc.h"
#include <domainmodule/phadextransaction/transactionrecord/deliverynotecancellation/ideliverynotecancellationptr.h>
#include <pxordertransmitptr.h>

namespace log4cplus
{
    class Logger;
}

namespace csc_phadex
{
namespace useCase
{
class DeliveryNoteCancellationUC : public IDeliveryNoteCancellationUC
{
public:
    DeliveryNoteCancellationUC();
    virtual ~DeliveryNoteCancellationUC();

    virtual void run();
    virtual void setDeliveryNoteCancellationRecord( csc_phadex::domMod::phadexTransaction::IDeliveryNoteCancellationPtr tr );
    virtual void injectPxOrderTransmit( pxOrderTransmitPtr xmit );

private:
    DeliveryNoteCancellationUC( const DeliveryNoteCancellationUC & );
    DeliveryNoteCancellationUC & operator= ( const DeliveryNoteCancellationUC & );
    void cancelCustomerOrder( );

    csc_phadex::domMod::phadexTransaction::IDeliveryNoteCancellationPtr m_DeliveryNoteCancellationRecord;
    pxOrderTransmitPtr			m_pxOrderTransmit;
    const log4cplus::Logger&	m_Logger;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_DELIVERYNOTECANCELLATION_UC_H
