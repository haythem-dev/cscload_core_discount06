#include <datatypes/boolean.h>
#include "logger/loggerpool.h"
#include "cscorderibtpickingdatamapperbase.h"

namespace libcsc {
namespace cscorder {
namespace repo {

CSCOrderIBTPickingdataMapperBase::CSCOrderIBTPickingdataMapperBase(domMod::ICSCOrderIBTPickingdataPtr pickingdata)
    : m_Pickingdata(*dynamic_cast<domMod::CSCOrderIBTPickingdata*>(pickingdata.get()))
{
}

CSCOrderIBTPickingdataMapperBase::~CSCOrderIBTPickingdataMapperBase()
{
}

void CSCOrderIBTPickingdataMapperBase::map()
{
    doMap();
}

void CSCOrderIBTPickingdataMapperBase::setClean(domMod::CSCOrderIBTPickingdataPtr pickingdata)
{
    pickingdata->m_CscOrderNo.setClean();
    pickingdata->m_CscOrderPosNo.setClean();
    pickingdata->m_DeliveryPosNo.setClean();
    pickingdata->m_Quantity.setClean();
    pickingdata->m_Batch.setClean();
    pickingdata->m_ExpiryDate.setClean();
}

void CSCOrderIBTPickingdataMapperBase::setCscOrderNo(basar::Int32 const cscorderno)
{
    m_Pickingdata.m_CscOrderNo = cscorderno;
    m_Pickingdata.m_CscOrderNo.setClean();
}

void CSCOrderIBTPickingdataMapperBase::setCscOrderPosNo(basar::Int32 const cscorderposno)
{
    m_Pickingdata.m_CscOrderPosNo = cscorderposno;
    m_Pickingdata.m_CscOrderPosNo.setClean();
}

void CSCOrderIBTPickingdataMapperBase::setDeliveryPosNo(basar::Int32 const deliveryposno)
{
    m_Pickingdata.m_DeliveryPosNo = deliveryposno;
    m_Pickingdata.m_DeliveryPosNo.setClean();
}

void CSCOrderIBTPickingdataMapperBase::setQuantity(basar::Int32 const quantity)
{
    m_Pickingdata.m_Quantity = quantity;
    m_Pickingdata.m_Quantity.setClean();
}

void CSCOrderIBTPickingdataMapperBase::setBatch(basar::VarString const batch)
{
    m_Pickingdata.m_Batch = batch;
    m_Pickingdata.m_Batch.setClean();
}

void CSCOrderIBTPickingdataMapperBase::setExpiryDate(basar::Int32 const expirydate)
{
    m_Pickingdata.m_ExpiryDate = expirydate;
    m_Pickingdata.m_ExpiryDate.setClean();
}

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc
