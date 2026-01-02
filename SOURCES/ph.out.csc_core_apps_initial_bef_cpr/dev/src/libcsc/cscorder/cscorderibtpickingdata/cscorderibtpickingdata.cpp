#include "logger/loggerpool.h"
#include "cscorderibtpickingdata.h"

namespace libcsc {
namespace cscorder {
namespace domMod {

CSCOrderIBTPickingdata::CSCOrderIBTPickingdata()
{
}

CSCOrderIBTPickingdata::~CSCOrderIBTPickingdata()
{
}

Int32 const& CSCOrderIBTPickingdata::getCscOrderNo() const
{
    return m_CscOrderNo;
}

Int32 const& CSCOrderIBTPickingdata::getCscOrderPosNo() const
{
    return m_CscOrderPosNo;
}

Int32 const& CSCOrderIBTPickingdata::getDeliveryPosNo() const
{
    return m_DeliveryPosNo;
}

Int32 const& CSCOrderIBTPickingdata::getQuantity() const
{
    return m_Quantity;
}

VarString const& CSCOrderIBTPickingdata::getBatch() const
{
    return m_Batch;
}

Int32 const& CSCOrderIBTPickingdata::getExpiryDate() const
{
    return m_ExpiryDate;
}

void CSCOrderIBTPickingdata::setCscOrderNo(Int32 const& cscorderno)
{
    m_CscOrderNo = cscorderno;
}

void CSCOrderIBTPickingdata::setCscOrderPosNo(Int32 const& cscorderposno)
{
    m_CscOrderPosNo = cscorderposno;
}

void CSCOrderIBTPickingdata::setDeliveryPosNo(Int32 const& deliveryposno)
{
    m_DeliveryPosNo = deliveryposno;
}

void CSCOrderIBTPickingdata::setQuantity(Int32 const& quantity)
{
    m_Quantity = quantity;
}

void CSCOrderIBTPickingdata::setBatch(VarString const& batch)
{
    m_Batch = batch;
}

void CSCOrderIBTPickingdata::setExpiryDate(Int32 const& expirydate)
{
    m_ExpiryDate = expirydate;
}

} // namespace domMod
} // namespace cscorder
} // namespace libcsc
