#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATA_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATA_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingTourData;
typedef boost::shared_ptr<ShipmentTrackingTourData> ShipmentTrackingTourDataPtr;

} // namespace shipmenttracking
} // namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourData& shipmentTrackingTourData);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourData* shipmentTrackingTourData);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingTourDataPtr shipmentTrackingTourData);

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURDATA_PTR_H
