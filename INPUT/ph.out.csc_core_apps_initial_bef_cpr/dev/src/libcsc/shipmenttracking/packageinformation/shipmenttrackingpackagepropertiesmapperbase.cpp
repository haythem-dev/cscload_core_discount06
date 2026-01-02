#include "shipmenttrackingpackagepropertiesmapperbase.h"
#include "shipmenttrackingpackageproperties.h"


namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingPackagePropertiesMapperBase::ShipmentTrackingPackagePropertiesMapperBase(ShipmentTrackingPackagePropertiesPtr shipmentTrackingPackageProperties)
    : m_PackageProperties(shipmentTrackingPackageProperties)
{
}


ShipmentTrackingPackagePropertiesMapperBase::~ShipmentTrackingPackagePropertiesMapperBase()
{
}

void ShipmentTrackingPackagePropertiesMapperBase::setPackageId(const basar::Int32 packageId)
{
    m_PackageProperties->m_PackageId = packageId;
    m_PackageProperties->m_PackageId.setClean();
}

void ShipmentTrackingPackagePropertiesMapperBase::setPackageType(const basar::VarString& packageType)
{
    m_PackageProperties->m_PackageType = packageType;
    m_PackageProperties->m_PackageType.setClean();
}

void ShipmentTrackingPackagePropertiesMapperBase::setCscOrderNo(const basar::Int32 cscOrderNo)
{
    m_PackageProperties->m_CscOrderNo = cscOrderNo;
    m_PackageProperties->m_CscOrderNo.setClean();
}

void ShipmentTrackingPackagePropertiesMapperBase::setPharmosOrderNo(const basar::Int32 pharmosOrderNo)
{
    m_PackageProperties->m_PharmosOrderNo = pharmosOrderNo;
    m_PackageProperties->m_PharmosOrderNo.setClean();
}

void ShipmentTrackingPackagePropertiesMapperBase::setDeliveryAdviceNo(const basar::Int32 deliveryAdviceNo)
{
    m_PackageProperties->m_DeliveryAdviceNo = deliveryAdviceNo;
    m_PackageProperties->m_DeliveryAdviceNo.setClean();
}

void ShipmentTrackingPackagePropertiesMapperBase::setPickingOrderNo(const basar::Int32 pickingOrderNo)
{
    m_PackageProperties->m_PickingOrderNo = pickingOrderNo;
    m_PackageProperties->m_PickingOrderNo.setClean();
}

void ShipmentTrackingPackagePropertiesMapperBase::setPickingOrderPageNo(const basar::Int16 pickingOrderPageNo)
{
    m_PackageProperties->m_PickingOrderPageNo = pickingOrderPageNo;
    m_PackageProperties->m_PickingOrderPageNo.setClean();
}

void ShipmentTrackingPackagePropertiesMapperBase::setTrackingBarcode(const basar::VarString& trackingBarcode)
{
    m_PackageProperties->m_TrackingBarcode = trackingBarcode;
    m_PackageProperties->m_TrackingBarcode.setClean();
}

void ShipmentTrackingPackagePropertiesMapperBase::setOrderClosedAt(const basar::DateTime& orderClosedAt)
{
    m_PackageProperties->m_OrderClosedAt = orderClosedAt;
    m_PackageProperties->m_OrderClosedAt.setClean();

    // update helper flag:
    m_PackageProperties->m_IsOrderClosed = orderClosedAt.isValid() && orderClosedAt.getYear() > 2010 && orderClosedAt.getYear() < 2090;
}

void ShipmentTrackingPackagePropertiesMapperBase::setPickingDoneAt(const basar::DateTime& pickingDoneAt)
{
    m_PackageProperties->m_PickingDoneAt = pickingDoneAt;
    m_PackageProperties->m_PickingDoneAt.setClean();
}

void ShipmentTrackingPackagePropertiesMapperBase::setRedirectedFromTourId(const basar::VarString& redirectedFromTourId)
{
    m_PackageProperties->m_RedirectedFromTourId = redirectedFromTourId;
    m_PackageProperties->m_RedirectedFromTourId.setClean();
}

void ShipmentTrackingPackagePropertiesMapperBase::setContentChangedAt(const basar::DateTime& contentChangedAt)
{
    m_PackageProperties->m_ContentChangedAt = contentChangedAt;

    // update helper flag:
    m_PackageProperties->m_IsContentChanged = contentChangedAt.isValid() && contentChangedAt.getYear() > 2010 && contentChangedAt.getYear() < 2090;
}

void ShipmentTrackingPackagePropertiesMapperBase::setTourRedirectedAt(const basar::DateTime& tourRedirectedAt)
{
    m_PackageProperties->m_TourRedirectedAt = tourRedirectedAt;

    // update helper flag:
    m_PackageProperties->m_IsTourRedirected = tourRedirectedAt.isValid() && tourRedirectedAt.getYear() > 2010 && tourRedirectedAt.getYear() < 2090;
}

void ShipmentTrackingPackagePropertiesMapperBase::setToteDeletedAt(const basar::DateTime& toteDeletedAt)
{
    m_PackageProperties->m_ToteDeletedAt = toteDeletedAt;
    m_PackageProperties->m_ToteDeletedAt.setClean();

    // update helper flag:
    m_PackageProperties->m_IsDeleted = toteDeletedAt.isValid() && toteDeletedAt.getYear() > 2010 && toteDeletedAt.getYear() < 2090;
}

void ShipmentTrackingPackagePropertiesMapperBase::setIsNarcotic(const bool isNarcotic)
{
    m_PackageProperties->m_IsNarcotic = isNarcotic;
}

void ShipmentTrackingPackagePropertiesMapperBase::setIsContainer(const bool isContainer)
{
    m_PackageProperties->m_IsContainer = isContainer;
}

void ShipmentTrackingPackagePropertiesMapperBase::setIsAdditionalTote(const bool isAdditionalTote)
{
    m_PackageProperties->m_IsAdditionalTote = isAdditionalTote;
}

void ShipmentTrackingPackagePropertiesMapperBase::setHasWarehouseData(bool hasWarehouseData)
{
    m_PackageProperties->m_HasWarehouseData = hasWarehouseData;
}

void ShipmentTrackingPackagePropertiesMapperBase::addTotalExpectedDeliveryQuantity(const basar::Int32 expectedDeliveryQuantity)
{
    m_PackageProperties->m_TotalExpectedDeliveryQuantity += expectedDeliveryQuantity;
}

void ShipmentTrackingPackagePropertiesMapperBase::addTotalConfirmedDeliveryQuantity(const basar::Int32 confirmedDeliveryQuantity)
{
    m_PackageProperties->m_TotalConfirmedDeliveryQuantity += confirmedDeliveryQuantity;
}

void ShipmentTrackingPackagePropertiesMapperBase::addTotalRelatedConfirmedDeliveryQuantity(const basar::Int32 confirmedDeliveryQuantity)
{
    m_PackageProperties->m_TotalRelatedConfirmedDeliveryQuantity += confirmedDeliveryQuantity;
}


} // end namespace shipmenttracking
} // end namespace libcsc

