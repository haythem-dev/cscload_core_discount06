#ifndef GUARD_LIBCSC_MSV3_ORDERRESPONSE_H
#define GUARD_LIBCSC_MSV3_ORDERRESPONSE_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

namespace libcsc {
namespace msv3 {

class OrderResponse
{
	// because of OR mapping
	friend class OrderResponseMapperBase;
	friend class OrderResponseSQLMapper;

public:
	OrderResponse();
	virtual ~OrderResponse();

	virtual const libcsc::Int32&		getId() const;
	virtual const libcsc::Int32&		getTransmissionId() const;
	virtual const libcsc::VarString&	getOrderUuid() const;
	virtual const libcsc::Int32&		getCscOrderNo() const;
	virtual const libcsc::VarString&	getBundleId() const;
	virtual const libcsc::VarString&	getOrderLabel() const;
	virtual const libcsc::Int32&		getOrderSupportId() const;

	virtual void						setId(const libcsc::Int32& id);
	virtual void						setTransmissionId(const libcsc::Int32& transmissionId);
	virtual void						setOrderUuid(const libcsc::VarString& orderUuid);
	virtual void						setCscOrderNo(const libcsc::Int32& cscOrderNo);
	virtual void						setBundleId(const libcsc::VarString& bundleId);
	virtual void						setOrderLabel(const libcsc::VarString& orderLabel);
	virtual void						setOrderSupportId(const libcsc::Int32& orderSupportId);

	virtual bool						isClean();
	virtual bool						isDirty();
	virtual void						setClean();

protected:

private:
	libcsc::Int32						m_Id;
	libcsc::Int32						m_TransmissionId;
	libcsc::VarString					m_OrderUuid;
	libcsc::Int32						m_CscOrderNo;
	libcsc::VarString					m_BundleId;
	libcsc::VarString					m_OrderLabel;
	libcsc::Int32						m_OrderSupportId;
};

} // namespace msv3
} // namespace libcsc

#endif // GUARD_LIBCSC_MSV3_ORDERRESPONSE_H
