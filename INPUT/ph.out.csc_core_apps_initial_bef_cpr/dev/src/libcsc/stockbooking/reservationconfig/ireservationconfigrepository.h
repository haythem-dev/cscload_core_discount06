#ifndef GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONCONFIG_REPOSITORY_H
#define GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONCONFIG_REPOSITORY_H

#include <libbasarcmnutil_bstring.h>
#include <stockbooking/reservationconfig/ireservationtypeptr.h>
#include <stockbooking/reservationconfig/iordertypereservationconfigptr.h>
#include <stockbooking/reservationconfig/iordertypereservationconfigpharmacygroupptr.h>

namespace libcsc {
namespace stockbooking {

class IReservationConfigRepository
{
public:
	virtual ~IReservationConfigRepository() {}

	virtual void										reset() = 0;

	virtual IReservationTypeCollectionPtr				findReservationTypes() = 0;
	virtual IReservationTypePtr							findReservationType(const basar::Int32& type) = 0;

	virtual IOrderTypeReservationConfigCollectionPtr	findOrderTypeReservationConfig(
															const basar::VarString& orderType) = 0;

	virtual IOrderTypeReservationConfigPtr				findOrderTypeReservationConfigById(
															const basar::Int32& id) = 0;

	virtual void										saveOrderTypeReservationConfig(
															IOrderTypeReservationConfigPtr orderTypeReservationConfig) = 0;
	virtual void										deleteOrderTypeReservationConfig(
															IOrderTypeReservationConfigPtr orderTypeReservationConfig) = 0;

	virtual IOrderTypeReservationConfigPtr				getEmptyOrderTypeReservationConfig() = 0;

	virtual void										saveOrderTypeReservationConfigPharmacyGroup(
															IOrderTypeReservationConfigPharmacyGroupPtr orderTypeReservationConfigPharmacyGroup) = 0;
	virtual void										deleteOrderTypeReservationConfigPharmacyGroupById(
															const basar::Int32& id ) = 0;
};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_RESERVATIONCONFIG_REPOSITORY_H
