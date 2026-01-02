#include "shipmenttrackingibtinformation.h"
#include <boost/make_shared.hpp>
#include <string>       // std::string

#include <util/loggingutils.h>
#include <exceptions/exceptionhelper.h>

namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingIbtInformation::ShipmentTrackingIbtInformation() :
    m_PackagePropertiesPtr(boost::make_shared<ShipmentTrackingPackageProperties>()),
    m_TourData(boost::make_shared<ShipmentTrackingTourData>())
{
}


ShipmentTrackingIbtInformation::~ShipmentTrackingIbtInformation()
{
}

} // end namespace shipmenttracking
} // end namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingIbtInformation& shipmentTrackingIbtInformation)
{
    METHODNAME_DEF(ShipmentTrackingIbtInformation, operator<<);
    try
    {
        os << "ST-IbtInformation: {"
            << "BranchNo: " << shipmentTrackingIbtInformation.getBranchNo()
            << ", CustomerNo: " << shipmentTrackingIbtInformation.getCustomerNo()
            << ", PackageProperties: " << shipmentTrackingIbtInformation.getPackageProperties()
            << ", TourData: " << shipmentTrackingIbtInformation.getTourData()
            ;

        if (shipmentTrackingIbtInformation.getRedirectedToTourData().get() != NULL)
        {
            os << ", RedirectedToTourData: " << shipmentTrackingIbtInformation.getRedirectedToTourData();
        }

        os << "}";

        return os;
    }
    catch (basar::Exception & ex)
    {
        libcsc::exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingIbtInformation* shipmentTrackingIbtInformation)
{
    if (shipmentTrackingIbtInformation != NULL)
    {
        os << *shipmentTrackingIbtInformation;
    }
    else
    {
        os << "ST-IbtInformation: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingIbtInformationPtr shipmentTrackingIbtInformation)
{
    os << shipmentTrackingIbtInformation.get();
    return os;
}
