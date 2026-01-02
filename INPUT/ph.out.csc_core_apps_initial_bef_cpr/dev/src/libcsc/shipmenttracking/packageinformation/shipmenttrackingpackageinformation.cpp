#include "shipmenttrackingpackageinformation.h"
#include <boost/make_shared.hpp>
#include <util/loggingutils.h>
#include <exceptions/exceptionhelper.h>


namespace libcsc {
namespace shipmenttracking {

ShipmentTrackingPackageInformation::ShipmentTrackingPackageInformation(ShipmentTrackingTourDataPtr tourData) :
    m_PackageProperties(boost::make_shared<ShipmentTrackingPackageProperties>()),
    //m_IbtInformationPtr(boost::make_shared<ShipmentTrackingIbtInformation>()),  <-- NOTE: do not fill until really needed!
    m_LineDetails(boost::make_shared<ShipmentTrackingLineDetailCollection>()),
    m_TourData(tourData)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformation, ShipmentTrackingPackageInformation);

    if (tourData.get() == NULL)
    {
        throw basar::Exception(basar::ExceptInfo(fun, "tourData is Null!", __FILE__, __LINE__), "");
    }
}


ShipmentTrackingPackageInformation::~ShipmentTrackingPackageInformation()
{
}

} // end namespace shipmenttracking
} // end namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformation& shipmentTrackingPackageInformation)
{
    METHODNAME_DEF(ShipmentTrackingPackageInformation, operator<<);
    try
    {
        os << "ST-PackageInformation: {"
            << "PackageProperties: " << shipmentTrackingPackageInformation.getPackageProperties()
            << ", Tour: " << shipmentTrackingPackageInformation.getTourData()
            ;

        if (shipmentTrackingPackageInformation.getRedirectedFromTourData().get() != NULL)
        {
            os << ", RedirectedFromTourData: " << shipmentTrackingPackageInformation.getRedirectedFromTourData();
        }

        if (shipmentTrackingPackageInformation.getRedirectedToTourData().get() != NULL)
        {
            os << ", RedirectedToTourData: " << shipmentTrackingPackageInformation.getRedirectedToTourData();
        }

        os
            << ", IbtInformation: " << shipmentTrackingPackageInformation.getIbtInformation()
            << ", LineDetails: " << shipmentTrackingPackageInformation.getLineDetailCollection()
            << "}";

        return os;
    }
    catch (basar::Exception & ex)
    {
        libcsc::exceptions::ExceptionHelper::processBasarException(ex, libcsc::LoggerPool::getLoggerShipmentTracking(), fun, __FILE__, __LINE__);
        throw;
    }
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformation* shipmentTrackingPackageInformation)
{
    if (shipmentTrackingPackageInformation != NULL)
    {
        os << *shipmentTrackingPackageInformation;
    }
    else
    {
        os << "ST-PackageInformation: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformationPtr shipmentTrackingPackageInformation)
{
    os << shipmentTrackingPackageInformation.get();
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformationCollection& shipmentTrackingPackageInformations)
{
    os << "[";

    
    int ii = 0;
    for (libcsc::shipmenttracking::ShipmentTrackingPackageInformationCollection::const_iterator it = shipmentTrackingPackageInformations.begin();
        it != shipmentTrackingPackageInformations.end();
        it++, ii++
        )
    {
        if (ii > 0)
        {
            os << ", ";
        }

        os << *it;
    }
    os << "]";

    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformationCollection* shipmentTrackingPackageInformations)
{
    if (shipmentTrackingPackageInformations != NULL)
    {
        os << *shipmentTrackingPackageInformations;
    }
    else
    {
        os << "ST-PackageInformationCollection: <null>";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformationCollectionPtr shipmentTrackingPackageInformations)
{
    os << shipmentTrackingPackageInformations.get();
    return os;
}
