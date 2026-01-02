#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEIBTLINK_BASE_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEIBTLINK_BASE_H

#include <libbasar_definitions.h>
#include "deliveryadvicelineibtlinkptr.h"

namespace libcsc {
namespace document {

class DeliveryAdviceLineIbtLinkMapperBase
{
public:
	
	DeliveryAdviceLineIbtLinkMapperBase(DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink);
	
	void map();
    void mapCustomerOrders();
    void mapCustomerOrderDetails();
    void mapDeliveryAdvice4CustomerOrder();
    void mapShuttleOrders();
    void mapShuttleOrderDetails();
    void mapDeliveryAdvice4ShuttleOrder();

protected:

	virtual ~DeliveryAdviceLineIbtLinkMapperBase();

	virtual void doMap() = 0;
    virtual void doMapCustomerOrders() = 0;
    virtual void doMapCustomerOrderDetails() = 0;
    virtual void doMapDeliveryAdvice4CustomerOrder() = 0;
    virtual void doMapShuttleOrders() = 0;
    virtual void doMapShuttleOrderDetails() = 0;
    virtual void doMapDeliveryAdvice4ShuttleOrder() = 0;

	void setBranchNo(const basar::Int16 branchNo);
	void setCustomerNo(const basar::Int32 customerNo);
	void setDeliveryAdviceDate(const basar::Date& deliveryAdviceDate);
	void setDeliveryAdviceNo(const basar::VarString& deliveryAdviceNo );
	void setDeliveryAdvicePosNo(const basar::Int32 deliveryAdvicePosNo);
	void setCscOrderNo(const basar::Int32 cscOrderNo);
	void setCscOrderPosNo(const basar::Int32 cscOrderPosNo);
	void setIbtBranchNo(const basar::Int16 ibtBranchNo);
	void setIbtCustomerNo(const basar::Int32 ibtCustomerNo);
	void setIbtDeliveryAdviceDate(const basar::Date& deliveryAdviceDate);
	void setIbtDeliveryAdviceNo(const basar::VarString& deliveryAdviceNo);
	void setIbtDeliveryAdvicePosNo(const basar::Int32 deliveryAdvicePosNo);
	void setIbtCscOrderNo(const basar::Int32 cscOrderNo);
	void setIbtCscOrderPosNo(const basar::Int32 cscOrderPosNo);

	// temp property
	void setPositionBookingDate(const basar::Int32& positionBookingDate);
	void setCustomerOrderArchived(const bool& customerOrderArchived);

	DeliveryAdviceLineIbtLinkPtr m_DeliveryAdviceLineIbtLink;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEIBTLINK_BASE_H
