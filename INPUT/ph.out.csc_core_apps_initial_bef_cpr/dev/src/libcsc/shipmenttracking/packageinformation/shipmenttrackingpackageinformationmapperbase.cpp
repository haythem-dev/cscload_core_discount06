#include "shipmenttrackingpackageinformationmapperbase.h"
#include "shipmenttrackinglinedetail.h"


namespace libcsc {
namespace shipmenttracking {


ShipmentTrackingPackageInformationMapperBase::ShipmentTrackingPackageInformationMapperBase(ShipmentTrackingPackageInformationPtr shipmentTrackingPackageInformation)
    : m_PackageInformation(shipmentTrackingPackageInformation)
{
}


ShipmentTrackingPackageInformationMapperBase::~ShipmentTrackingPackageInformationMapperBase()
{
}

void ShipmentTrackingPackageInformationMapperBase::setPackageProperties(const ShipmentTrackingPackagePropertiesPtr packageProperties)
{
    if (packageProperties.get() != NULL)
    {
        m_PackageInformation->m_PackageProperties = packageProperties;
    }
}

void ShipmentTrackingPackageInformationMapperBase::setLineDetailCollection(const ShipmentTrackingLineDetailCollectionPtr lineDetailCollection)
{
    if (lineDetailCollection.get() != NULL)
    {
        m_PackageInformation->m_LineDetails = lineDetailCollection;
    }
}

void ShipmentTrackingPackageInformationMapperBase::setIbtImformation(const ShipmentTrackingIbtInformationPtr ibtInformation)
{
    if (ibtInformation.get() != NULL &&
        ibtInformation->getBranchNo() > 0
        )
    {
        m_PackageInformation->m_IbtInformation = ibtInformation;
    }
}

void ShipmentTrackingPackageInformationMapperBase::setRedirectedToTourData(const ShipmentTrackingTourDataPtr redirectedToTourData)
{
    m_PackageInformation->m_RedirectedToTourData = redirectedToTourData;
}

void ShipmentTrackingPackageInformationMapperBase::setRedirectedFromTourData(const ShipmentTrackingTourDataPtr redirectedFromTourData)
{
    m_PackageInformation->m_RedirectedFromTourData = redirectedFromTourData;
}

ShipmentTrackingLineDetailCollection::iterator ShipmentTrackingPackageInformationMapperBase::addLineDetail(const ShipmentTrackingLineDetailPtr lineDetail)
{
    m_PackageInformation->m_LineDetails->push_back(lineDetail);

    return --m_PackageInformation->m_LineDetails->end();
}

ShipmentTrackingLineDetailCollection::iterator ShipmentTrackingPackageInformationMapperBase::removeLineDetailFromList(ShipmentTrackingLineDetailCollection::iterator lineDetailIterator)
{
    if (lineDetailIterator != m_PackageInformation->m_LineDetails->end())
    {
        m_PackageInformation->m_LineDetails->erase(lineDetailIterator);
    }
    return m_PackageInformation->m_LineDetails->end();
}


} // end namespace shipmenttracking
} // end namespace libcsc

