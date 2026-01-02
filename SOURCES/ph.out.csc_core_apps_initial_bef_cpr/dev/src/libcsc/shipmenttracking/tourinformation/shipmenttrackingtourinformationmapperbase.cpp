#include "shipmenttracking/shipmenttrackingutils.h"
#include "shipmenttrackingtourdata.h"
#include "shipmenttrackingtourinformation.h"
#include "shipmenttrackingtourinformationmapperbase.h"

#include <util/loggingutils.h>

namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingTourInformationMapperBase::ShipmentTrackingTourInformationMapperBase(ShipmentTrackingTourInformationPtr packageInformation)
    : m_TourInformation(packageInformation)
{
}


ShipmentTrackingTourInformationMapperBase::~ShipmentTrackingTourInformationMapperBase()
{
}

ShipmentTrackingPackageInformationCollection::iterator ShipmentTrackingTourInformationMapperBase::addNextPackage(const ShipmentTrackingPackageInformationPtr& packageInformation)
{
    //METHODNAME_DEF(ShipmentTrackingTourInformationMapperBase, addNextPackage);
    //BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << " m_TourData: " << m_TourInformation->m_TourData);

    m_TourInformation->m_PackageInformations->push_back(packageInformation);

    return --m_TourInformation->m_PackageInformations->end();
}

void ShipmentTrackingTourInformationMapperBase::insertPackageToList(ShipmentTrackingPackageInformationCollection::iterator packageInfoIterator, const ShipmentTrackingPackageInformationPtr& packageInformation)
{
    //METHODNAME_DEF(ShipmentTrackingTourInformationMapperBase, insertPackageToList);
    //BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << " m_TourData: " << m_TourInformation->m_TourData);

    m_TourInformation->m_PackageInformations->insert(packageInfoIterator, packageInformation);
}

ShipmentTrackingPackageInformationCollection::iterator ShipmentTrackingTourInformationMapperBase::removePackageFromList(ShipmentTrackingPackageInformationCollection::iterator packageInfoIterator)
{
    METHODNAME_DEF(ShipmentTrackingTourInformationMapperBase, removePackageFromList);
    //BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << " m_TourData: " << m_TourInformation->m_TourData);

    if (packageInfoIterator != m_TourInformation->m_PackageInformations->end())
    {
        m_TourInformation->m_PackageInformations->erase(packageInfoIterator);
    }
    else
    {
        LOG4CPLUS_TRACE(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "Package already removed from: " << m_TourInformation->m_TourData);
    }

    return m_TourInformation->m_PackageInformations->end();
}

void ShipmentTrackingTourInformationMapperBase::replaceTourInformation(ShipmentTrackingTourDataPtr redirectedToTourData)
{
    METHODNAME_DEF(ShipmentTrackingTourInformationMapperBase, replaceTourInformation);
    //BLOG_TRACE_METHODEX(libcsc::LoggerPool::getLoggerShipmentTracking(), fun); //NOTE: creating RedirectedTo TourInfo. Cannot trace the unset: << " m_TourData: " << m_TourInformation->m_TourData

    if (redirectedToTourData.get() != NULL &&
        redirectedToTourData->getTourId().find_first_not_of(' ') != std::string::npos &&
        redirectedToTourData->getPlannedTimeOfArrival().isValid()
        )
    {
        m_TourInformation->m_TourData = redirectedToTourData;
    }
    else if (redirectedToTourData.get() != NULL)
    {
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "redirectedToTourData TourId: " << redirectedToTourData->getTourId() << ", PlannedTimeOfArrival: " << redirectedToTourData->getPlannedTimeOfArrival());
    }
    else
    {
        LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerShipmentTracking(), fun << "redirectedToTourData == NULL");
    }
}


} // end namespace shipmenttracking
} // end namespace libcsc

