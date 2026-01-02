#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "deliveryadviceptr.h"


namespace libcsc {
namespace document {

class DeliveryAdviceMapperBase
{
public:
    DeliveryAdviceMapperBase(DeliveryAdvicePtr deliveryAdvice);

    void            map();
    void            mapKeysOnly();
protected:
    virtual ~DeliveryAdviceMapperBase();

    virtual void    doMap() = 0;
    virtual void    doMapKeysOnly() = 0;

    void setBranchNo( const basar::Int16 branchNo );
    void setCustomerNo( const basar::Int32 customerNo );
    void setDeliveryAdviceDate( const basar::Date& deliveryAdviceDate );
    void setDeliveryAdviceNo( const basar::VarString & deliveryAdviceNo );

    void setPharmosOrderNo( const basar::Int32 pharmosOrderNo );
    void setCSCOrderNo( const basar::Int32 cscOrderNo );
    void setCompleted( const basar::VarString & completed );
    void setSpecialDocumentType( const basar::VarString & specialdocumenttype );
    void setTourId( const basar::VarString & tourId );
    void setDueDate( const basar::Date dueDate );
    void setOrderType( const basar::VarString & orderType );
    void setPickingType( const basar::VarString & pickingType );
    void setBookingType( const basar::VarString & bookingType );
    void setRequested( const basar::Int16 requested );
    void setConfirmed( const basar::Int16 confirmed );
    void setOrderLabel( const basar::VarString & orderLabel );
    void setCancelled( const basar::Int16 cancelled );
    void setBatchCorrectionAdvice(const basar::Int16 batchCorrectionAdvice);
    void setLineFee(const basar::Decimal& lineFee);
    void setPackageFee(const basar::Decimal& packageFee);
    void setContractId(const basar::VarString& contractId);

    void setDepositValue(const basar::Decimal & depositValue);
    void setNetTurnover(const basar::Decimal& netTurnover);
    void setDiscountRetail(const basar::Decimal& discountRetail);
    void setDiscountWholesale(const basar::Decimal& discountWholesale);
    void setVatAmount(const basar::Decimal& vatAmount);
    void setLogisticServiceCost(const basar::Decimal & logisticservicecost);

    void setDocumentId(const basar::VarString& documentId);

private:
    DeliveryAdvicePtr m_DeliveryAdvice;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICEMAPPER_BASE_H
