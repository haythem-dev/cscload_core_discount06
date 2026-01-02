#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATIONMAPPER_BASE_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATIONMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "shipmenttrackingpackageinformation.h"
#include "shipmenttrackinglinedetailptr.h"


namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingPackageInformationMapperBase
{
public:
    ShipmentTrackingPackageInformationMapperBase(ShipmentTrackingPackageInformationPtr shipmentTrackingPackageInformation);

    const ShipmentTrackingPackageInformationPtr&     getPackageInformation()    const { return m_PackageInformation; }
    ShipmentTrackingLineDetailCollection::iterator addLineDetail(const ShipmentTrackingLineDetailPtr lineDetail);
    ShipmentTrackingLineDetailCollection::iterator removeLineDetailFromList(ShipmentTrackingLineDetailCollection::iterator lineDetailIterator);

protected:
    virtual ~ShipmentTrackingPackageInformationMapperBase();

    void setPackageProperties(const ShipmentTrackingPackagePropertiesPtr packageProperties);
    void setLineDetailCollection(const ShipmentTrackingLineDetailCollectionPtr lineDetailCollection);

    void setIbtImformation(const ShipmentTrackingIbtInformationPtr ibtInformation);
    void setRedirectedToTourData(const ShipmentTrackingTourDataPtr redirectedToTourData);
    void setRedirectedFromTourData(const ShipmentTrackingTourDataPtr redirectedFromTourData);

    ShipmentTrackingPackageInformationPtr m_PackageInformation;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATIONMAPPER_BASE_H
