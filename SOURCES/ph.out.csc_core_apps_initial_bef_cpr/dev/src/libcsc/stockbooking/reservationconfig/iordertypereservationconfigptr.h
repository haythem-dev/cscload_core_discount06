#ifndef GUARD_LIBCSC_STOCKBOOKING_I_ORDERTYPE_RESERVATIONCONFIG_PTR_H
#define GUARD_LIBCSC_STOCKBOOKING_I_ORDERTYPE_RESERVATIONCONFIG_PTR_H

#include <boost/shared_ptr.hpp>
#include <vector>
#include <map>

namespace libcsc {
namespace stockbooking {

class IOrderTypeReservationConfig;
typedef boost::shared_ptr<IOrderTypeReservationConfig> IOrderTypeReservationConfigPtr;

typedef std::vector<IOrderTypeReservationConfigPtr> IOrderTypeReservationConfigCollection;

typedef boost::shared_ptr<IOrderTypeReservationConfigCollection> IOrderTypeReservationConfigCollectionPtr;

typedef std::map<basar::VarString, IOrderTypeReservationConfigCollectionPtr> IOrderTypeReservationConfigCollectionMap;

typedef boost::shared_ptr<IOrderTypeReservationConfigCollectionMap> IOrderTypeReservationConfigCollectionMapPtr;

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_ORDERTYPE_RESERVATIONCONFIG_PTR_H
