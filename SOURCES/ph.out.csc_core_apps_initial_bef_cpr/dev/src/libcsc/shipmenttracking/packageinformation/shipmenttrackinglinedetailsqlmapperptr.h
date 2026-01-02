#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAILSQLMAPPER_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAILSQLMAPPER_PTR_H

#include <libbasar_definitions.h>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingLineDetailSQLMapper;
typedef boost::shared_ptr<ShipmentTrackingLineDetailSQLMapper> ShipmentTrackingLineDetailSQLMapperPtr;

typedef std::list<ShipmentTrackingLineDetailSQLMapperPtr> ShipmentTrackingLineDetailSQLMapperCollection;

typedef boost::shared_ptr<ShipmentTrackingLineDetailSQLMapperCollection> ShipmentTrackingLineDetailSQLMapperCollectionPtr;

typedef std::map<std::string, ShipmentTrackingLineDetailSQLMapperPtr> ShipmentTrackingLineDetailSQLMapperStrMap;
typedef std::map<basar::Int32, ShipmentTrackingLineDetailSQLMapperPtr> ShipmentTrackingLineDetailSQLMapperInt32Map;

} // namespace shipmenttracking
} // namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAILSQLMAPPER_PTR_H
