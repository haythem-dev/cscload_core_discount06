#include "shipmenttrackingetaanddeliverydata.h"
#include <boost/make_shared.hpp>
#include <util/loggingutils.h>
#include <exceptions/exceptionhelper.h>
#include <string>       // std::string


namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingEtaAndDeliveryData::ShipmentTrackingEtaAndDeliveryData()
{
}


ShipmentTrackingEtaAndDeliveryData::~ShipmentTrackingEtaAndDeliveryData()
{
}

} // end namespace shipmenttracking
} // end namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingEtaAndDeliveryData& shipmentTrackingEtaAndDeliveryData)
{
    METHODNAME_DEF(ShipmentTrackingEtaAndDeliveryData, operator<<);
    try
    {
        os << "ST-EtaAndDeliveryData: {"
            << "EstimatedTimeOfArrival: " << shipmentTrackingEtaAndDeliveryData.getEstimatedTimeOfArrival()
            << ", Min: " << shipmentTrackingEtaAndDeliveryData.getEstimatedTimeOfArrivalMin()
            << ", Max: " << shipmentTrackingEtaAndDeliveryData.getEstimatedTimeOfArrivalMax()
            << ", DeliveredAt: " << shipmentTrackingEtaAndDeliveryData.getDeliveredAt()
            << ", DelayInMinutes: " << shipmentTrackingEtaAndDeliveryData.getDelayInMinutes()
            << ", DelayInfo: " << shipmentTrackingEtaAndDeliveryData.getDelayInfo()
            << "}";

        return os;
    }
    catch (basar::Exception & ex)
    {
        libcsc::exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingEtaAndDeliveryData* shipmentTrackingEtaAndDeliveryData)
{
    if (shipmentTrackingEtaAndDeliveryData != NULL)
    {
        os << *shipmentTrackingEtaAndDeliveryData;
    }
    else
    {
        os << "ST-EtaAndDeliveryData: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingEtaAndDeliveryDataPtr shipmentTrackingEtaAndDeliveryData)
{
    os << shipmentTrackingEtaAndDeliveryData.get();
    return os;
}
