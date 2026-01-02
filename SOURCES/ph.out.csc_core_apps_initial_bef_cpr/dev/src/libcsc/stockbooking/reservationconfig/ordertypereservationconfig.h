#ifndef GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_H
#define GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_H

#include <stockbooking/reservationconfig/iordertypereservationconfig.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/boolean.h>
#include <datatypes/varstring.h>
#include "ordertypereservationconfigpharmacygroupptr.h"

namespace libcsc {
namespace stockbooking {

class OrderTypeReservationConfig : public IOrderTypeReservationConfig
{
	friend class OrderTypeReservationConfigMapperBase;
	friend class ReservationConfigRepository;


public:
	OrderTypeReservationConfig();
	virtual ~OrderTypeReservationConfig();

	const basar::Int32&			getId() const;
	const basar::Int32&			getReservationType() const;
	const bool&					getWithPharmacyGroup() const;
	const basar::VarString&		getReservationName() const;
	const basar::VarString&		getOrderType() const;
	const basar::VarString&		getOrderTypeReservationConfigName() const;
	const basar::Int16&			getPriority() const;
	const bool&					getReservedStockOnly() const;
	const bool&					getFreeStockHasPriority() const;
	const IOrderTypeReservationConfigPharmacyGroupCollectionPtr getPharmacyGroups() const;

	IOrderTypeReservationConfigPharmacyGroupPtr addPharmacyGroup(const basar::VarString& pharmacyGroup);
	bool						containsPharmacyGroup(const basar::VarString& pharmacyGroup);

	void						setId(const basar::Int32& id);
	void						setOrderType(const basar::VarString& orderType);
	void						setReservationType(const basar::Int32& reservationType);
	void						setOrderTypeReservationConfigName(const basar::VarString& name);
	void						setPriority(const basar::Int16& priority);
	void						setReservedStockOnly(const bool& reservedOnly);
	void						setFreeStockHasPriority(const bool& freeStockHasPriority);

	bool						isInsertable() const;
	bool						isUpdatable() const;
	bool						isClean() const;
	//bool						isDirty();
	bool						operator < (const IOrderTypeReservationConfig& rhs) const;

private:
	libcsc::Int32						m_Id;								// ordertypereservationconfig.id
	libcsc::Int32						m_ReservationType;					// cscreservationtypes.cscreservationtype join ordertypereservationconfig.cscreservationtype
	libcsc::Bool						m_WithPharmacyGroup;				// cscreservationtypes.withpharmacygroup
	libcsc::VarString					m_ReservationName;					// cscreservationtypes.cscreservationtypename
	libcsc::VarString					m_OrderType;						// ordertypereservationconfig.cscordertype
	libcsc::VarString					m_OrderTypeReservationConfigName;	// ordertypereservationconfig.
	libcsc::Int16						m_Priority;							// ordertypereservationconfig.priority
	libcsc::Bool						m_ReservedStockOnly;				// ordertypereservationconfig.reservedstockonly
	libcsc::Bool						m_FreeStockHasPriority;				// ordertypereservationconfig.freestockhaspriority
	IOrderTypeReservationConfigPharmacyGroupCollectionPtr m_PharmacyGroups;
};

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_H
