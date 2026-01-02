#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_CURRENTWHSLINECONTEXT_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_CURRENTWHSLINECONTEXT_PTR_H

#include <libbasar_definitions.h>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingCurrentWhsLineContext;
typedef boost::shared_ptr<ShipmentTrackingCurrentWhsLineContext> ShipmentTrackingCurrentWhsLineContextPtr;

typedef std::list<ShipmentTrackingCurrentWhsLineContextPtr> ShipmentTrackingCurrentWhsLineContextCollection;

typedef boost::shared_ptr<ShipmentTrackingCurrentWhsLineContextCollection> ShipmentTrackingCurrentWhsLineContextCollectionPtr;

} // namespace shipmenttracking
} // namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingCurrentWhsLineContext& currentWhsLineContext);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingCurrentWhsLineContext* currentWhsLineContext);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingCurrentWhsLineContextPtr currentWhsLineContext);

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_CURRENTWHSLINECONTEXT_PTR_H
