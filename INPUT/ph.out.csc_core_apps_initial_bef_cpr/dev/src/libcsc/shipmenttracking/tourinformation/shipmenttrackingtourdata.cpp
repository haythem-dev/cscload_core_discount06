#include "shipmenttrackingtourdata.h"
#include <boost/make_shared.hpp>
#include <util/loggingutils.h>
#include <exceptions/exceptionhelper.h>
#include <string>       // std::string


namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingTourData::ShipmentTrackingTourData()
{
}


ShipmentTrackingTourData::~ShipmentTrackingTourData()
{
}

bool ShipmentTrackingTourData::isSameTourAs(const ShipmentTrackingTourData* other) const
{
    //NOTE: this comparison method is called only in context of a specific Branch, CustomerNo and TourId. So it is ok to compare just the ToteNo:
    return other != NULL &&
        this->getTourId() == other->getTourId() &&
        this->getPlannedTimeOfArrival().getDate() == other->getPlannedTimeOfArrival().getDate()
        ;
}

std::string ShipmentTrackingTourData::getMapKey() const
{
    std::stringstream mapKey;

    mapKey << m_DeliveryDate << "-" << m_TourId;

    return mapKey.str();
}


} // end namespace shipmenttracking
} // end namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourData& shipmentTrackingTourData)
{
    METHODNAME_DEF(ShipmentTrackingTourData, operator<<);
    try
    {
        os << "ST-TourData: {"
            << "TourId: " << shipmentTrackingTourData.getTourId()
            << ", PlannedTimeOfArrival: " << shipmentTrackingTourData.getPlannedTimeOfArrival()
            << "}";
        return os;
    }
    catch (basar::Exception & ex)
    {
        libcsc::exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourData* shipmentTrackingTourData)
{
    if (shipmentTrackingTourData != NULL)
    {
        os << *shipmentTrackingTourData;
    }
    else
    {
        os << "ST-TourData: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourDataPtr shipmentTrackingTourData)
{
    os << shipmentTrackingTourData.get();
    return os;
}
