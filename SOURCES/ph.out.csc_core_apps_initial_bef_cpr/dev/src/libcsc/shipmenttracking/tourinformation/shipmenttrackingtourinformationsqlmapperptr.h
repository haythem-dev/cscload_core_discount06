#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATIONSQLMAPPER_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATIONSQLMAPPER_PTR_H

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingTourInformationSQLMapper;
typedef boost::shared_ptr<ShipmentTrackingTourInformationSQLMapper> ShipmentTrackingTourInformationSQLMapperPtr;

typedef std::list<ShipmentTrackingTourInformationSQLMapperPtr> ShipmentTrackingTourInformationSQLMapperCollection;

typedef boost::shared_ptr<ShipmentTrackingTourInformationSQLMapperCollection> ShipmentTrackingTourInformationSQLMapperCollectionPtr;

typedef std::map<std::string, ShipmentTrackingTourInformationSQLMapperPtr> ShipmentTrackingTourInformationSQLMapperMap;

} // namespace shipmenttracking
} // namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGTOURINFORMATIONSQLMAPPER_PTR_H
