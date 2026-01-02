#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATION_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATION_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingTourInformation;
typedef boost::shared_ptr<ShipmentTrackingTourInformation> ShipmentTrackingTourInformationPtr;

typedef std::list<ShipmentTrackingTourInformationPtr> ShipmentTrackingTourInformationCollection;

typedef boost::shared_ptr<ShipmentTrackingTourInformationCollection> ShipmentTrackingTourInformationCollectionPtr;

} // namespace shipmenttracking
} // namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourInformation& shipmentTrackingTourInformation);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourInformation* shipmentTrackingTourInformation);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourInformationPtr shipmentTrackingTourInformation);

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATION_PTR_H
