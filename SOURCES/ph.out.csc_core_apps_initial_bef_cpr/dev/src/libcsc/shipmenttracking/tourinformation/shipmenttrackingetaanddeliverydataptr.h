#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATA_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATA_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingEtaAndDeliveryData;
typedef boost::shared_ptr<ShipmentTrackingEtaAndDeliveryData> ShipmentTrackingEtaAndDeliveryDataPtr;

} // namespace shipmenttracking
} // namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingEtaAndDeliveryData& shipmentTrackingEtaAndDeliveryData);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingEtaAndDeliveryData* shipmentTrackingEtaAndDeliveryData);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingEtaAndDeliveryDataPtr shipmentTrackingEtaAndDeliveryData);

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGETAANDDELIVERYDATA_PTR_H
