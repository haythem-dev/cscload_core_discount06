#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATIONMAPPER_BASE_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATIONMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "shipmenttrackingtourdataptr.h"
#include "shipmenttrackingtourinformationptr.h"
#include "shipmenttracking/packageinformation/shipmenttrackingpackageinformationptr.h"


namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingTourInformationMapperBase
{
public:
    ShipmentTrackingTourInformationMapperBase(ShipmentTrackingTourInformationPtr packageInformation);

    const ShipmentTrackingTourInformationPtr&     getTourInformation()    const { return m_TourInformation; }

    ShipmentTrackingPackageInformationCollection::iterator addNextPackage(const ShipmentTrackingPackageInformationPtr& packageInformation);

    void insertPackageToList(ShipmentTrackingPackageInformationCollection::iterator packageInfoIterator, const ShipmentTrackingPackageInformationPtr& packageInformation);
    ShipmentTrackingPackageInformationCollection::iterator removePackageFromList(ShipmentTrackingPackageInformationCollection::iterator packageInfoIterator);

protected:
    virtual ~ShipmentTrackingTourInformationMapperBase();

    void replaceTourInformation(ShipmentTrackingTourDataPtr redirectedToTourData);

    ShipmentTrackingTourInformationPtr m_TourInformation;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATIONMAPPER_BASE_H
