#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTORDERTOPACKAGEMAPMAKER_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTORDERTOPACKAGEMAPMAKER_PTR_H

#include <libbasar_definitions.h>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingIbtOrderToPackageMapMaker;
typedef boost::shared_ptr<ShipmentTrackingIbtOrderToPackageMapMaker> ShipmentTrackingIbtOrderToPackageMapMakerPtr;

typedef std::list<ShipmentTrackingIbtOrderToPackageMapMakerPtr> ShipmentTrackingIbtOrderToPackageMapMakerCollection;

typedef boost::shared_ptr<ShipmentTrackingIbtOrderToPackageMapMakerCollection> ShipmentTrackingIbtOrderToPackageMapMakerCollectionPtr;

typedef std::map<basar::Int32, ShipmentTrackingIbtOrderToPackageMapMakerPtr> ShipmentTrackingIbtOrderToPackageMapMakerInt32Map;

} // namespace shipmenttracking
} // namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGIBTORDERTOPACKAGEMAPMAKER_PTR_H
