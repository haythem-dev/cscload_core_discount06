#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEIBTLINK_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEIBTLINK_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/date.h>
#include <datatypes/varstring.h>
#include <datatypes/boolean.h>

namespace libcsc {
namespace document {

class DeliveryAdviceLineIbtLink
{
	friend class DeliveryAdviceLineIbtLinkMapperBase;

public:
	DeliveryAdviceLineIbtLink();
    DeliveryAdviceLineIbtLink(DeliveryAdviceLineIbtLink& deliveryAdviceLineIbtLink);
	virtual ~DeliveryAdviceLineIbtLink();

	virtual const basar::Int16&		getBranchNo() const;
	virtual const basar::Int32&		getCustomerNo() const;
	virtual const basar::Date&		getDeliveryAdviceDate() const;
	virtual const basar::VarString&	getDeliveryAdviceNo() const;
	virtual const basar::Int32&		getDeliveryAdvicePosNo() const;
	virtual const basar::Int32&		getCscOrderNo() const;
	virtual const basar::Int32&		getCscOrderPosNo() const;
	virtual const basar::Int16&		getIbtBranchNo() const;
	virtual const basar::Int32&		getIbtCustomerNo() const;
	virtual const basar::Date&		getIbtDeliveryAdviceDate() const;
	virtual const basar::VarString&	getIbtDeliveryAdviceNo() const;
	virtual const basar::Int32&		getIbtDeliveryAdvicePosNo() const;
	virtual const basar::Int32&		getIbtCscOrderNo() const;
	virtual const basar::Int32&		getIbtCscOrderPosNo() const;

	// temp property
	virtual const basar::Int32&		getPositionBookingDate() const;
	virtual const bool&				isCustomerOrderArchived() const;

    virtual void setBranchNo(const basar::Int16& branchNo);
    virtual void setCustomerNo(const basar::Int32& customerNo);
    virtual void setDeliveryAdviceDate(const basar::Date& deliveryAdviceDate);
    virtual void setDeliveryAdviceNo(const basar::VarString& deliveryAdviceNo);
    virtual void setDeliveryAdvicePosNo(const basar::Int32& deliveryAdvicePosNo);
    virtual void setCscOrderNo(const basar::Int32& cscOrderNo);
    virtual void setCscOrderPosNo(const basar::Int32& cscOrderPosNo);
    virtual void setIbtBranchNo(const basar::Int16& ibtBranchNo);
    virtual void setIbtCustomerNo(const basar::Int32& ibtCustomerNo);
    virtual void setIbtDeliveryAdviceDate(const basar::Date& ibtDeliveryAdviceDate);
    virtual void setIbtDeliveryAdviceNo(const basar::VarString& ibtDeliveryAdviceNo);
    virtual void setIbtDeliveryAdvicePosNo(const basar::Int32& ibtDeliveryAdvicePosNo);
    virtual void setIbtCscOrderNo(const basar::Int32& ibtCscOrderNo);
    virtual void setIbtCscOrderPosNo(const basar::Int32& ibtCscOrderPosNo);

	// temp property
	virtual void setPositionBookingDate(const basar::Int32& positionBookingDate);
	virtual void setCustomerOrderArchived(const bool& customerOrderArchived);

private:
	libcsc::Int16					m_BranchNo;
	libcsc::Int32					m_CustomerNo;
	libcsc::Date					m_DeliveryAdviceDate;
	libcsc::VarString				m_DeliveryAdviceNo;
	libcsc::Int32					m_DeliveryAdvicePosNo;
	libcsc::Int32					m_CscOrderNo;
	libcsc::Int32					m_CscOrderPosNo;
	libcsc::Int16					m_IbtBranchNo;
	libcsc::Int32					m_IbtCustomerNo;
	libcsc::Date					m_IbtDeliveryAdviceDate;
	libcsc::VarString				m_IbtDeliveryAdviceNo;
	libcsc::Int32					m_IbtDeliveryAdvicePosNo;
	libcsc::Int32					m_IbtCscOrderNo;
	libcsc::Int32					m_IbtCscOrderPosNo;

	// temp property
	libcsc::Int32					m_PositionBookingDate;
	libcsc::Bool					m_CustomerOrderArchived;
};

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICELINEIBTLINK_H
