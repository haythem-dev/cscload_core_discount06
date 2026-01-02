#include "shipmenttrackingpackageproperties.h"
#include <boost/make_shared.hpp>
#include <util/loggingutils.h>
#include <exceptions/exceptionhelper.h>
#include <string>       // std::string

namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingPackageProperties::ShipmentTrackingPackageProperties() :
    m_IsContainer(false),
    m_IsNarcotic(false),
    m_IsAdditionalTote(false),
    m_IsOrderClosed(false),
    m_IsContentChanged(false),
    m_IsTourRedirected(false),
    m_IsDeleted(false),
    m_HasWarehouseData(false),
    m_TotalExpectedDeliveryQuantity(0),
    m_TotalConfirmedDeliveryQuantity(0),
    m_TotalRelatedConfirmedDeliveryQuantity(0)
{
    // Setting Warhouse Data Defaults. The DKTSV info may be completely missing.
    m_PackageId = 0;
    m_PackageId.setClean();

    m_PackageType = "Tote";
    m_PackageType.setClean();

    m_PickingOrderNo = 0;
    m_PickingOrderNo.setClean();

    m_PickingOrderPageNo = 0;
    m_PickingOrderPageNo.setClean();

    m_TrackingBarcode = "";
    m_TrackingBarcode.setClean();

    basar::DateTime invalidDateTime;
    invalidDateTime.setInvalid();

    m_PickingDoneAt = invalidDateTime;
    m_PickingDoneAt.setClean();

    m_RedirectedFromTourId = "";
    m_RedirectedFromTourId.setClean();

    m_ContentChangedAt.setInvalid();

    m_TourRedirectedAt.setInvalid();

    m_ToteDeletedAt = invalidDateTime;
    m_ToteDeletedAt.setClean();
}

ShipmentTrackingPackageProperties::~ShipmentTrackingPackageProperties()
{
}

bool ShipmentTrackingPackageProperties::isSamePackageAs(const ShipmentTrackingPackageProperties* other) const
{
    //NOTE: this comparison method is called only in context of a specific Branch, CustomerNo and TourId. So it is ok to compare just the ToteNo:
    return other != NULL &&
        this->getPackageId() == other->getPackageId() &&
        this->getTrackingBarcode() == other->getTrackingBarcode()

        //NOTE: shall it be necessary to compare the IBT tote (package) info with a local package info, it would be necessary to compare also:
        //&& this->getCscOrderNo() == other->getCscOrderNo()
        ;
}

std::string ShipmentTrackingPackageProperties::getOutboundMapKey() const
{
    std::stringstream mapKey;

    mapKey << getCscOrderNo() << "-" << getPackageType();

    return mapKey.str();
}

std::string ShipmentTrackingPackageProperties::getWarehouseMapKey() const
{
    std::stringstream mapKey;

    mapKey << getTrackingBarcode() << "-" << getPackageId();

    return mapKey.str();
}

} // end namespace shipmenttracking
} // end namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageProperties& shipmentTrackingPackageProperties)
{
    METHODNAME_DEF(ShipmentTrackingPackageProperties, operator<<);
    try
    {
        os << "ST-PackageProperties: {"
            //<< "this: " << ((void*)(&shipmentTrackingPackageProperties)) << ", "
            << "PackageId: " << shipmentTrackingPackageProperties.getPackageId()
            << ", PackageType: " << shipmentTrackingPackageProperties.getPackageType()
            << ", CscOrderNo: " << shipmentTrackingPackageProperties.getCscOrderNo()
            << ", PharmosOrderNo: " << shipmentTrackingPackageProperties.getPharmosOrderNo()
            << ", DeliveryAdviceNo: " << shipmentTrackingPackageProperties.getDeliveryAdviceNo()
            << ", PickingOrderNo: " << shipmentTrackingPackageProperties.getPickingOrderNo()
            << ", PickingOrderPageNo: " << shipmentTrackingPackageProperties.getPickingOrderPageNo()
            << ", TrackingBarcode: " << shipmentTrackingPackageProperties.getTrackingBarcode()
            << ", OrderClosedAt: " << shipmentTrackingPackageProperties.getOrderClosedAt()
            << ", PickingDoneAt: " << shipmentTrackingPackageProperties.getPickingDoneAt()
            << ", isContentChanged: " << shipmentTrackingPackageProperties.isContentChanged()
            << ", isTourRedirected: " << shipmentTrackingPackageProperties.isTourRedirected()
            << ", isDeleted: " << shipmentTrackingPackageProperties.isDeleted()
            << ", RedirectedFromTourId: " << shipmentTrackingPackageProperties.getRedirectedFromTourId()
            << ", ToteContentChanged: " << shipmentTrackingPackageProperties.isToteContentChanged()
            << ", ContentChangedAt: " << shipmentTrackingPackageProperties.getContentChangedAt()
            << ", TourRedirectedAt: " << shipmentTrackingPackageProperties.getTourRedirectedAt()
            << ", ToteDeletedAt: " << shipmentTrackingPackageProperties.getToteDeletedAt()
            << ", TotalExpectedDeliveryQuantity: " << shipmentTrackingPackageProperties.getTotalExpectedDeliveryQuantity()
            << ", TotalConfirmedDeliveryQuantity: " << shipmentTrackingPackageProperties.getTotalConfirmedDeliveryQuantity()
            << ", TotalRelatedConfirmedDeliveryQuantity: " << shipmentTrackingPackageProperties.getTotalRelatedConfirmedDeliveryQuantity()
            << ", HasWarehouseData: " << shipmentTrackingPackageProperties.hasWarehouseData()
            << "}";

        return os;
    }
    catch (basar::Exception & ex)
    {
        libcsc::exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageProperties* shipmentTrackingPackageProperties)
{
    if (shipmentTrackingPackageProperties != NULL)
    {
        os << *shipmentTrackingPackageProperties;
    }
    else
    {
        os << "ST-PackageProperties: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackagePropertiesPtr shipmentTrackingPackageProperties)
{
    os << shipmentTrackingPackageProperties.get();
    return os;
}
