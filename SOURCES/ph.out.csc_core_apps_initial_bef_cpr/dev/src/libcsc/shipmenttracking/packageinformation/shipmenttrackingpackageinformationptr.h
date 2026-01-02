#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATION_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATION_PTR_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <list>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingPackageInformation;
typedef boost::shared_ptr<ShipmentTrackingPackageInformation> ShipmentTrackingPackageInformationPtr;

typedef std::list<ShipmentTrackingPackageInformationPtr> ShipmentTrackingPackageInformationCollection;

typedef boost::shared_ptr<ShipmentTrackingPackageInformationCollection> ShipmentTrackingPackageInformationCollectionPtr;


typedef std::map<std::string, ShipmentTrackingPackageInformationPtr> ShipmentTrackingPackageInformationMap;

// --------------
// Weak Pointers:
typedef boost::weak_ptr<ShipmentTrackingPackageInformation> ShipmentTrackingPackageInformationWeakPtr;

} // namespace shipmenttracking
} // namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformation& shipmentTrackingPackageInformation);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformation* shipmentTrackingPackageInformation);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformationPtr shipmentTrackingPackageInformation);

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformationCollection& shipmentTrackingPackageInformations);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformationCollection* shipmentTrackingPackageInformations);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingPackageInformationCollectionPtr shipmentTrackingPackageInformations);

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGPACKAGEINFORMATION_PTR_H
