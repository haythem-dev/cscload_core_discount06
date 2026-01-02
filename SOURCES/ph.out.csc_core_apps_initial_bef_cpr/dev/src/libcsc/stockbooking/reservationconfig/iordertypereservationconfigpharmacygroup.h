#ifndef GUARD_LIBCSC_STOCKBOOKING_I_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_H
#define GUARD_LIBCSC_STOCKBOOKING_I_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace stockbooking {

class IOrderTypeReservationConfigPharmacyGroup
{
public:
	virtual ~IOrderTypeReservationConfigPharmacyGroup() {}

	virtual const basar::Int32&			getId() const = 0;
	virtual const basar::VarString&		getPharmacyGroupId() const = 0;
	virtual const basar::Int32&			getOrderTypeReservationConfigId() const = 0;

	virtual void						setId(const basar::Int32& id) = 0;
	virtual void						setPharmacyGroupId(const basar::VarString& pharmacyGroupId) = 0;
	virtual void						setOrderTypeReservationConfigId(const basar::Int32& reservationId) = 0;

	virtual void						markForDeletion() = 0;
	virtual bool						isMarkedForDeletion() = 0;

	virtual bool						isInsertable() const = 0;
//	virtual bool						isUpdatable() const = 0;
};

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_H
