#ifndef GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_H
#define GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_H

#include <stockbooking/reservationconfig/iordertypereservationconfigpharmacygroup.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include <sstream>

namespace libcsc {
namespace stockbooking {

class OrderTypeReservationConfigPharmacyGroup : public IOrderTypeReservationConfigPharmacyGroup
{
	friend class OrderTypeReservationConfigPharmacyGroupMapperBase;
	friend std::ostream& operator << (std::ostream& str, const libcsc::stockbooking::OrderTypeReservationConfigPharmacyGroup& data);

public:
	OrderTypeReservationConfigPharmacyGroup();
	virtual ~OrderTypeReservationConfigPharmacyGroup();

	const basar::Int32&			getId() const;
	const basar::VarString&		getPharmacyGroupId() const;
	const basar::Int32&			getOrderTypeReservationConfigId() const;


	void						setId(const basar::Int32& id);
	void						setPharmacyGroupId(const basar::VarString& pharmacyGroupId);
	void						setOrderTypeReservationConfigId(const basar::Int32& reservationId);

	void						markForDeletion();
	bool						isMarkedForDeletion();

	bool						isInsertable() const;
	bool						isUpdatable() const;
	bool						isClean();
	bool						isDirty();

private:
	libcsc::Int32						m_Id;
	libcsc::Int32						m_OrderTypeReservationConfigId;
	libcsc::VarString					m_PharmacyGroupId;

	bool								m_DeletionFlag;
};

} // namespace stockbooking
} // namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_ORDERTYPE_RESERVATIONCONFIG_PHARMACYGROUP_H
