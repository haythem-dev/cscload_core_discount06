#include "deliveryadvice.h"

#include "deliveryadviceline/deliveryadviceline.h"
#include "deliveryadviceline/deliveryadvicelinereturn.h"

namespace libcsc {
namespace document {

DeliveryAdvice::DeliveryAdvice()
{
}

DeliveryAdvice::~DeliveryAdvice()
{
}

const basar::Int16 & DeliveryAdvice::getBranchNo() const
{
    return m_BranchNo;
}

const basar::Int32 & DeliveryAdvice::getCustomerNo() const
{
    return m_CustomerNo;
}

const basar::Date & DeliveryAdvice::getDeliveryAdviceDate() const
{
    return m_DeliveryAdviceDate;
}

const basar::VarString & DeliveryAdvice::getDeliveryAdviceNo() const
{
    return m_DeliveryAdviceNo;
}

const basar::Int32& DeliveryAdvice::getPharmosOrderNo() const
{
    return m_PharmosOrderNo;
}

const basar::Int32& DeliveryAdvice::getCscOrderNo() const
{
    return m_CscOrderNo;
}

const libcsc::VarString& DeliveryAdvice::getCompleted() const
{
    return m_Completed;
}

const basar::VarString& DeliveryAdvice::getSpecialDocumentType() const
{
    return m_SpecialDocumentType;
}

const basar::VarString& DeliveryAdvice::getTourId() const
{
    return m_TourId;
}

const basar::Date& DeliveryAdvice::getDueDate() const
{
    return m_DueDate;
}

const basar::VarString& DeliveryAdvice::getOrderType() const
{
    return m_OrderType;
}

const basar::VarString& DeliveryAdvice::getPickingType() const
{
    return m_PickingType;
}

const basar::VarString& DeliveryAdvice::getBookingType() const
{
    return m_BookingType;
}

const libcsc::Int16& DeliveryAdvice::getRequested() const
{
    return m_Requested;
}

const libcsc::Int16& DeliveryAdvice::getConfirmed() const
{
    return m_Confirmed;
}

const libcsc::Int16& DeliveryAdvice::getCancelled() const
{
    return m_Cancelled;
}

const libcsc::Int16& DeliveryAdvice::getBatchCorrectionAdvice() const
{
    return m_BatchCorrectionAdvice;
}

const basar::VarString& DeliveryAdvice::getOrderLabel() const
{
    return m_OrderLabel;
}

const basar::Decimal& DeliveryAdvice::getLineFee() const
{
    return m_LineFee;
}

const basar::Decimal& DeliveryAdvice::getPackageFee() const
{
    return m_PackageFee;
}

const basar::VarString& DeliveryAdvice::getContractId() const
{
    return m_ContractId;
}

const basar::Decimal& DeliveryAdvice::getDepositValue() const
{
    return m_DepositValue;
}

const basar::Decimal& DeliveryAdvice::getNetTurnover() const
{
    return m_NetTurnover;
}

const basar::Decimal& DeliveryAdvice::getDiscountRetail() const
{
    return m_DiscountRetail;
}

const basar::Decimal& DeliveryAdvice::getDiscountWholesale() const
{
    return m_DiscountWholesale;
}

const basar::Decimal& DeliveryAdvice::getVatAmount() const
{
    return m_VatAmount;
}

const basar::Decimal& DeliveryAdvice::getLogisticServiceCost() const
{
    return m_LogisticServiceCost;
}

const basar::VarString& DeliveryAdvice::getDocumentId() const
{
    return m_DocumentId;
}

const DeliveryAdviceRemarksCollectionPtr DeliveryAdvice::getRemarksCollection() const
{
    return m_Remarks;
}

const DeliveryAdviceVatTotalsCollectionPtr DeliveryAdvice::getDeliveryAdviceVatTotalsCollection() const
{
    return m_VatTotals;
}

const DeliveryAdviceLineCollectionPtr DeliveryAdvice::getDeliveryAdviceLineCollection() const
{
    return m_DeliveryAdviceLines;
}

bool DeliveryAdvice::isClean() const
{
    return
        m_BranchNo.isClean() &&
        m_CustomerNo.isClean() &&
        m_DeliveryAdviceDate.isClean() &&
        m_DeliveryAdviceNo.isClean();
}

bool DeliveryAdvice::isConfirmed() const
{
    return m_Confirmed > 0;
}

bool DeliveryAdvice::isCancelled() const
{
    return m_Cancelled > 0;
}

bool DeliveryAdvice::isCompleted() const
{
    return m_Completed == "1";
}

void DeliveryAdvice::setConfirmed()
{
    m_Confirmed = 1;
}

void DeliveryAdvice::setCancelled()
{
    m_Cancelled = 1;
}

void DeliveryAdvice::setUnCancelled()
{
    m_Cancelled = 0;
}

void DeliveryAdvice::setCompleted()
{
    m_Completed = "1";
}

void DeliveryAdvice::setBatchCorrectionAdvice(basar::Int16 batchCorrectionAdvice)
{
    m_BatchCorrectionAdvice = batchCorrectionAdvice;
}

void DeliveryAdvice::incrementRequestCounter()
{
    m_Requested = m_Requested + 1;
}

bool DeliveryAdvice::areAllIbtPositionsCompleted()
{
    bool openIbtPositions = false;

    DeliveryAdviceLineCollection::const_iterator it = m_DeliveryAdviceLines->begin();
    while (it != m_DeliveryAdviceLines->end())
    {
        DeliveryAdviceLinePtr line = *it;
        if (line->getLineType() == DeliveryAdviceLine::LINETYPE_IBT) // 1 == Verbund
        {
            if (NULL == line->getIbtLink().get())
            {
                openIbtPositions = true;
                break;
            }
        }
        ++it;
    }
    return (openIbtPositions == false);
}

} // namespace document
} // namespace libcsc
