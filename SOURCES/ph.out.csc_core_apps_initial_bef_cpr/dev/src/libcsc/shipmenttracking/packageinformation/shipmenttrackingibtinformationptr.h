#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATION_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATION_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingIbtInformation;
typedef boost::shared_ptr<ShipmentTrackingIbtInformation> ShipmentTrackingIbtInformationPtr;

} // namespace shipmenttracking
} // namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingIbtInformation& shipmentTrackingIbtInformation);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingIbtInformation* shipmentTrackingIbtInformation);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingIbtInformationPtr shipmentTrackingIbtInformation);

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTINFORMATION_PTR_H
