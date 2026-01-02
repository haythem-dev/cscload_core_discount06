#ifndef GUARD_LIBCSC_MSV3_ORDERRESPONSEMAPPER_BASE_H
#define GUARD_LIBCSC_MSV3_ORDERRESPONSEMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "orderresponseptr.h"

namespace libcsc {
namespace msv3 {

class OrderResponseMapperBase
{
public:
	OrderResponseMapperBase(OrderResponsePtr orderResponse);

	void			map();
	void			mapSerial(const basar::Int32& id);

protected:
	virtual ~OrderResponseMapperBase();

	virtual void	doMap() = 0;
	virtual void	doMapSerial(const basar::Int32& id) = 0;

	virtual void	setId(const basar::Int32& transmissionId);
	virtual void	setTransmissionId(const basar::Int32& transmissionId);
	virtual void	setOrderUuid(const basar::VarString& orderUuid);
	virtual void	setCscOrderNo(const basar::Int32& cscOrderNo);
	virtual void	setBundleId(const basar::VarString& bundleId);
	virtual void	setOrderLabel(const basar::VarString& orderLabel);
	virtual void	setOrderSupportId(const basar::Int32& orderSupportId);

	virtual void	setClean();
//private:
	OrderResponsePtr m_OrderResponse;
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_ORDERRESPONSEMAPPER_BASE_H
