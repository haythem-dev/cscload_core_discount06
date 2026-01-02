#include "shipmenttrackinglinedetailmapperbase.h"
#include "shipmenttrackinglinedetail.h"

#include <util/loggingutils.h>

namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingLineDetailMapperBase::ShipmentTrackingLineDetailMapperBase(ShipmentTrackingLineDetailPtr lineDetail) :
    m_LineDetail(lineDetail)
{
}


ShipmentTrackingLineDetailMapperBase::~ShipmentTrackingLineDetailMapperBase()
{
}

void ShipmentTrackingLineDetailMapperBase::setOrderPosNo(const basar::Int32 orderPosNo)
{
    m_LineDetail->m_OrderPosNo = orderPosNo;
    m_LineDetail->m_OrderPosNo.setClean();
}

void ShipmentTrackingLineDetailMapperBase::setIbtOrderPosNo(const basar::Int32 ibtOrderPosNo)
{
    m_LineDetail->m_IbtOrderPosNo = ibtOrderPosNo;
    m_LineDetail->m_IbtOrderPosNo.setClean();
}

void ShipmentTrackingLineDetailMapperBase::setTotePosNo(const basar::Int32 totePosNo)
{
    m_LineDetail->m_TotePosNo = totePosNo;
    m_LineDetail->m_TotePosNo.setClean();
}

void ShipmentTrackingLineDetailMapperBase::setExpectedDeliveryQuantity(const basar::Int32 expectedDeliveryQuantity)
{
    m_LineDetail->m_ExpectedDeliveryQuantity = expectedDeliveryQuantity;
    m_LineDetail->m_ExpectedDeliveryQuantity.setClean();
}

void ShipmentTrackingLineDetailMapperBase::setConfirmedDeliveryQuantity(const basar::Int32 confirmedDeliveryQuantity)
{
    m_LineDetail->m_ConfirmedDeliveryQuantity = confirmedDeliveryQuantity;
    m_LineDetail->m_ConfirmedDeliveryQuantity.setClean();
}

void ShipmentTrackingLineDetailMapperBase::setArticleNr(const basar::Int32 articleNr)
{
    m_LineDetail->m_ArticleNr = articleNr;
    m_LineDetail->m_ArticleNr.setClean();
}

void ShipmentTrackingLineDetailMapperBase::setArticleCode(const basar::VarString& articleCode)
{
    m_LineDetail->m_ArticleCode = articleCode;
    m_LineDetail->m_ArticleCode.setClean();
}

void ShipmentTrackingLineDetailMapperBase::setArticleName(const basar::VarString& articleName)
{
    m_LineDetail->m_ArticleName = articleName;
    m_LineDetail->m_ArticleName.setClean();
}

void ShipmentTrackingLineDetailMapperBase::setIsNarcotic(const bool isNarcotic)
{
    m_LineDetail->m_IsNarcotic = isNarcotic;
    m_LineDetail->m_IsNarcotic.setClean();
}

void ShipmentTrackingLineDetailMapperBase::setBatch(const basar::VarString& batch)
{
    m_LineDetail->m_Batch = batch;
    m_LineDetail->m_Batch.setClean();
}

void ShipmentTrackingLineDetailMapperBase::setHasWarehouseData(bool hasWarehouseData)
{
    m_LineDetail->m_HasWarehouseData = hasWarehouseData;
}

void ShipmentTrackingLineDetailMapperBase::setOwnerPackageInfo(ShipmentTrackingPackageInformationPtr ownerPackageInfo)
{
    m_LineDetail->m_OwnerPackageInfo = ownerPackageInfo;
}


} // end namespace shipmenttracking
} // end namespace libcsc

