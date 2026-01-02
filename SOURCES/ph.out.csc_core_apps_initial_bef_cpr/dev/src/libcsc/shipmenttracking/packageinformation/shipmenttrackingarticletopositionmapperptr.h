#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGARTICLETOPOSITIONMAPPER_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGARTICLETOPOSITIONMAPPER_PTR_H

#include <libbasar_definitions.h>

#include <boost/shared_ptr.hpp>
#include <list>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingArticleToPositionMapper;
typedef boost::shared_ptr<ShipmentTrackingArticleToPositionMapper> ShipmentTrackingArticleToPositionMapperPtr;

typedef std::list<ShipmentTrackingArticleToPositionMapperPtr> ShipmentTrackingArticleToPositionMapperCollection;

typedef boost::shared_ptr<ShipmentTrackingArticleToPositionMapperCollection> ShipmentTrackingArticleToPositionMapperCollectionPtr;

typedef std::map<basar::Int32, ShipmentTrackingArticleToPositionMapperPtr> ShipmentTrackingArticleToPositionMapperInt32Map;

} // namespace shipmenttracking
} // namespace libcsc

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGARTICLETOPOSITIONMAPPER_PTR_H
