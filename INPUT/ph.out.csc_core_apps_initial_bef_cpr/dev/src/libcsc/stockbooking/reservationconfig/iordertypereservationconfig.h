#ifndef GUARD_LIBCSC_STOCKBOOKING_I_ORDERTYPE_RESERVATIONCONFIG_H
#define GUARD_LIBCSC_STOCKBOOKING_I_ORDERTYPE_RESERVATIONCONFIG_H

#include <libbasar_definitions.h>

#include <stockbooking/reservationconfig/iordertypereservationconfigpharmacygroupptr.h>

namespace libcsc {
namespace stockbooking {

class IOrderTypeReservationConfig
{
public:
	virtual ~IOrderTypeReservationConfig() {}

	virtual const basar::Int32&			getId() const = 0;
	virtual const basar::Int32&			getReservationType() const = 0;
	virtual const bool&					getWithPharmacyGroup() const = 0;
	virtual const basar::VarString&		getReservationName() const = 0;
	virtual const basar::VarString&		getOrderType() const = 0;
	virtual const basar::VarString&		getOrderTypeReservationConfigName() const = 0;
	virtual const basar::Int16&			getPriority() const = 0;
	virtual const bool&					getReservedStockOnly() const = 0;
	virtual const bool&					getFreeStockHasPriority() const = 0;
	virtual const IOrderTypeReservationConfigPharmacyGroupCollectionPtr getPharmacyGroups() const = 0;

	virtual IOrderTypeReservationConfigPharmacyGroupPtr addPharmacyGroup(const basar::VarString& pharmacyGroup) = 0;
	virtual bool						containsPharmacyGroup(const basar::VarString& pharmacyGroup) = 0;

	virtual void						setId(const basar::Int32& id) = 0;
	virtual void						setOrderType(const basar::VarString& orderType) = 0;
	virtual void						setReservationType(const basar::Int32& reservationType) = 0;
	virtual void						setOrderTypeReservationConfigName(const basar::VarString& name) = 0;
	virtual void						setPriority(const basar::Int16& priority) = 0;
	virtual void						setReservedStockOnly(const bool& reservedOnly) = 0;
	virtual void						setFreeStockHasPriority(const bool& freeStockHasPriority) = 0;

	virtual bool						isInsertable() const = 0;
	virtual bool						isUpdatable() const = 0;
	virtual bool						isClean() const = 0;
	virtual bool						operator < (const IOrderTypeReservationConfig& rhs) const = 0;

};

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_I_ORDERTYPE_RESERVATIONCONFIG_H
