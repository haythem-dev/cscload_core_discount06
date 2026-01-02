#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGBATCHTOTOTELINEMAPPER_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGBATCHTOTOTELINEMAPPER_PTR_H

#include <libbasar_definitions.h>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingBatchToToteLineMapper;
typedef boost::shared_ptr<ShipmentTrackingBatchToToteLineMapper> ShipmentTrackingBatchToToteLineMapperPtr;

typedef std::map<std::string, ShipmentTrackingBatchToToteLineMapperPtr> ShipmentTrackingBatchToToteLineMapperStrMap;

} // namespace shipmenttracking
} // namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGBATCHTOTOTELINEMAPPER_PTR_H
