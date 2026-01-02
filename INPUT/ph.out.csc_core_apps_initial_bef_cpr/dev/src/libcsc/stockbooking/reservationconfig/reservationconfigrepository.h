#ifndef GUARD_LIBCSC_STOCKBOOKING_RESERVATIONCONFIG_REPOSITORY_H
#define GUARD_LIBCSC_STOCKBOOKING_RESERVATIONCONFIG_REPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasarcmnutil_bstring.h>
#include <map>
#include <stockbooking/reservationconfig/ireservationconfigrepository.h>
#include <stockbooking/reservationconfig/ordertypereservationconfigptr.h>

namespace libcsc {
namespace stockbooking {

class ReservationConfigRepository : public IReservationConfigRepository
{
public:
	ReservationConfigRepository();
    virtual ~ReservationConfigRepository();

	virtual void reset();

	virtual void injectSelectReservationTypesAccessor(persistence::IAccessorPtr accessor);

	virtual void injectSelectOrderTypesReservationConfigAccessor(persistence::IAccessorPtr accessor);
	virtual void injectInsertOrderTypesReservationConfigAccessor(persistence::IAccessorPtr accessor);
	virtual void injectUpdateOrderTypesReservationConfigAccessor(persistence::IAccessorPtr accessor);
	virtual void injectDeleteOrderTypesReservationConfigAccessor(persistence::IAccessorPtr accessor);

	virtual void injectSelectOrderTypesReservationConfigPharmacyGroupAccessor(persistence::IAccessorPtr accessor);
	virtual void injectInsertOrderTypesReservationConfigPharmacyGroupAccessor(persistence::IAccessorPtr accessor);
	virtual void injectDeleteOrderTypesReservationConfigPharmacyGroupAccessor(persistence::IAccessorPtr accessor);


	virtual IReservationTypeCollectionPtr				findReservationTypes();
	virtual IReservationTypePtr							findReservationType(const basar::Int32& type);

	virtual IOrderTypeReservationConfigCollectionPtr	findOrderTypeReservationConfig(
															const basar::VarString& orderType);

	virtual IOrderTypeReservationConfigPtr				findOrderTypeReservationConfigById(
															const basar::Int32& id);

	virtual void										saveOrderTypeReservationConfig(
															IOrderTypeReservationConfigPtr orderTypeReservationConfig);

	virtual void										deleteOrderTypeReservationConfig(
															IOrderTypeReservationConfigPtr orderTypeReservationConfig);

	virtual IOrderTypeReservationConfigPtr				getEmptyOrderTypeReservationConfig();

	virtual void										saveOrderTypeReservationConfigPharmacyGroup(
															IOrderTypeReservationConfigPharmacyGroupPtr orderTypeReservationConfigPharmacyGroup);

	virtual void										deleteOrderTypeReservationConfigPharmacyGroupById(
															const basar::Int32& id);

private:
	virtual void										readOrderTypeReservationConfig();
	virtual void findOrderTypeReservationConfigPharmacyGroup(OrderTypeReservationConfigPtr reservationConfig);
	virtual void deleteOrderTypeReservationConfigPharmacyGroupByReservationId(IOrderTypeReservationConfigPtr orderTypeReservationConfig);

	ReservationConfigRepository& operator=(const ReservationConfigRepository&);

	IReservationTypeCollectionPtr											m_ReservationTypeList;
	// TODO cache OrderTypeReservationConfig in map
	IOrderTypeReservationConfigCollectionMapPtr								m_OrderTypesReservationConfigMap;

    persistence::IAccessorPtr m_SelectReservationTypesAccessor;
    persistence::IAccessorPtr m_SelectOrderTypeReservationConfigAccessor;
	persistence::IAccessorPtr m_InsertOrderTypeReservationConfigAccessor;
	persistence::IAccessorPtr m_UpdateOrderTypeReservationConfigAccessor;
	persistence::IAccessorPtr m_DeleteOrderTypeReservationConfigAccessor;

	persistence::IAccessorPtr m_SelectOrderTypeReservationConfigPharmacyGroupAccessor;
	persistence::IAccessorPtr m_InsertOrderTypeReservationConfigPharmacyGroupAccessor;
	persistence::IAccessorPtr m_DeleteOrderTypeReservationConfigPharmacyGroupAccessor;

};

} // end namespace stockbooking
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_RESERVATIONCONFIG_REPOSITORY_H
