#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOTEPOSITIONTOLINEBUILDERMAPPER_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOTEPOSITIONTOLINEBUILDERMAPPER_PTR_H

#include <libbasar_definitions.h>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingTotePositionToLineBuilderMapper;
typedef boost::shared_ptr<ShipmentTrackingTotePositionToLineBuilderMapper> ShipmentTrackingTotePositionToLineBuilderMapperPtr;

typedef std::map<basar::Int32, ShipmentTrackingTotePositionToLineBuilderMapperPtr> ShipmentTrackingTotePositionToLineBuilderMapperInt32Map;

} // namespace shipmenttracking
} // namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOTEPOSITIONTOLINEBUILDERMAPPER_PTR_H
