#ifndef GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAIL_PTR_H
#define GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAIL_PTR_H

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <list>
#include <map>

namespace libcsc {
namespace shipmenttracking {

class ShipmentTrackingLineDetail;
typedef boost::shared_ptr<ShipmentTrackingLineDetail> ShipmentTrackingLineDetailPtr;

typedef std::list<ShipmentTrackingLineDetailPtr> ShipmentTrackingLineDetailCollection;
typedef boost::shared_ptr<ShipmentTrackingLineDetailCollection> ShipmentTrackingLineDetailCollectionPtr;

typedef std::map<std::string, ShipmentTrackingLineDetailPtr> ShipmentTrackingLineDetailStrMap;

// --------------
// Weak Pointers:
typedef boost::weak_ptr<ShipmentTrackingLineDetail> ShipmentTrackingLineDetailWeakPtr;

typedef std::list<ShipmentTrackingLineDetailWeakPtr> ShipmentTrackingLineDetailWeakCollection;
typedef boost::shared_ptr<ShipmentTrackingLineDetailWeakCollection> ShipmentTrackingLineDetailWeakCollectionPtr;

typedef std::map<std::string, ShipmentTrackingLineDetailWeakPtr> ShipmentTrackingLineDetailWeakStrMap;

typedef std::map<std::string, ShipmentTrackingLineDetailWeakCollectionPtr> ShipmentTrackingLineDetailWeakStrToClollectionMap;
typedef boost::shared_ptr<ShipmentTrackingLineDetailWeakStrToClollectionMap> ShipmentTrackingLineDetailWeakStrToClollectionMapPtr;


} // namespace shipmenttracking
} // namespace libcsc

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetail& shipmentTrackingLineDetail);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetail* shipmentTrackingLineDetail);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailPtr shipmentTrackingLineDetail);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakPtr shipmentTrackingLineDetail);

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailCollection& shipmentTrackingLineDetails);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailCollection* shipmentTrackingLineDetails);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailCollectionPtr shipmentTrackingLineDetails);

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakCollection& shipmentTrackingLineDetails);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakCollection* shipmentTrackingLineDetails);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakCollectionPtr shipmentTrackingLineDetails);

std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakStrToClollectionMap& shipmentTrackingLineDetailWeakStrToCollectionMap);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakStrToClollectionMap* shipmentTrackingLineDetailWeakStrToCollectionMap);
std::ostream& operator<<(std::ostream& os, const libcsc::shipmenttracking::ShipmentTrackingLineDetailWeakStrToClollectionMapPtr shipmentTrackingLineDetailWeakStrToCollectionMap);

#endif // GUARD_LIBCSC_SHIPMENTTRACKING_SHIPMENTTRACKINGLINEDETAIL_PTR_H
