#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/decimal.h>

#include <document/deliveryadvice/deliveryadvicevattotalsptr.h>
#include <document/deliveryadvice/deliveryadviceremarksptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelineptr.h>

namespace libcsc {
namespace document {

class DeliveryAdvice
{
    friend class DeliveryAdviceMapperBase;
    friend class DeliveryAdviceRepository;

public:
    DeliveryAdvice();
    virtual ~DeliveryAdvice();

    virtual const basar::Int16 &        getBranchNo() const;
    virtual const basar::Int32 &        getCustomerNo() const;
    virtual const basar::Date&          getDeliveryAdviceDate() const;
    virtual const basar::VarString &    getDeliveryAdviceNo() const;

    virtual const basar::Int32&         getPharmosOrderNo() const;
    virtual const basar::Int32&         getCscOrderNo() const;
    virtual const libcsc::VarString&    getCompleted() const;
    virtual const basar::VarString&     getSpecialDocumentType() const;
    virtual const basar::VarString&     getTourId() const;
    virtual const basar::Date&          getDueDate() const;
    virtual const basar::VarString&     getOrderType() const;
    virtual const basar::VarString&     getPickingType() const;
    virtual const basar::VarString&     getBookingType() const;
    virtual const libcsc::Int16&        getRequested() const;
    virtual const libcsc::Int16&        getConfirmed() const;
    virtual const libcsc::Int16&        getCancelled() const;
    virtual const libcsc::Int16&        getBatchCorrectionAdvice() const;
    virtual const basar::VarString&     getOrderLabel() const;
    virtual const basar::Decimal&       getLineFee() const;
    virtual const basar::Decimal&       getPackageFee() const;
    virtual const basar::VarString&     getContractId() const;

    virtual const basar::Decimal&       getDepositValue() const;
    virtual const basar::Decimal&       getNetTurnover() const;
    virtual const basar::Decimal&       getDiscountRetail() const;
    virtual const basar::Decimal&       getDiscountWholesale() const;
    virtual const basar::Decimal&       getVatAmount() const;
    virtual const basar::Decimal&       getLogisticServiceCost() const;

    virtual const basar::VarString&     getDocumentId() const;

    virtual const DeliveryAdviceRemarksCollectionPtr    getRemarksCollection() const;
    virtual const DeliveryAdviceVatTotalsCollectionPtr  getDeliveryAdviceVatTotalsCollection() const;
    virtual const DeliveryAdviceLineCollectionPtr       getDeliveryAdviceLineCollection() const;

    virtual bool                        isClean() const;
    virtual bool                        isConfirmed() const;
    virtual bool                        isCancelled() const;
    virtual bool                        isCompleted() const;

    virtual void                        setConfirmed();
    virtual void                        setCancelled();
    virtual void                        setUnCancelled();
    virtual void                        setCompleted();
    virtual void                        setBatchCorrectionAdvice(basar::Int16 batchCorrectionAdvice);
    virtual void                        incrementRequestCounter();

    virtual bool                        areAllIbtPositionsCompleted();

protected:

private:
    libcsc::Int16                       m_BranchNo;
    libcsc::Int32                       m_CustomerNo;
    libcsc::Date                        m_DeliveryAdviceDate;
    libcsc::VarString                   m_DeliveryAdviceNo;

    libcsc::Int32                       m_PharmosOrderNo;
    libcsc::Int32                       m_CscOrderNo;
    libcsc::VarString                   m_Completed;
    libcsc::VarString                   m_SpecialDocumentType;
    libcsc::VarString                   m_TourId;
    libcsc::Date                        m_DueDate;
    libcsc::VarString                   m_OrderType;
    libcsc::VarString                   m_PickingType;
    libcsc::VarString                   m_BookingType;
    libcsc::Int16                       m_Requested;
    libcsc::Int16                       m_Confirmed;
    libcsc::VarString                   m_OrderLabel;
    libcsc::Int16                       m_Cancelled;
    libcsc::Int16                       m_BatchCorrectionAdvice;
    libcsc::Decimal                     m_LineFee;
    libcsc::Decimal                     m_PackageFee;
    libcsc::VarString                   m_ContractId;

    libcsc::Decimal                     m_DepositValue;
    libcsc::Decimal                     m_NetTurnover;
    libcsc::Decimal                     m_DiscountRetail;
    libcsc::Decimal                     m_DiscountWholesale;
    libcsc::Decimal                     m_VatAmount;
    libcsc::Decimal                     m_LogisticServiceCost;

    libcsc::VarString                   m_DocumentId;

    DeliveryAdviceVatTotalsCollectionPtr    m_VatTotals;
    DeliveryAdviceLineCollectionPtr         m_DeliveryAdviceLines;
    DeliveryAdviceRemarksCollectionPtr      m_Remarks;
};

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_H
