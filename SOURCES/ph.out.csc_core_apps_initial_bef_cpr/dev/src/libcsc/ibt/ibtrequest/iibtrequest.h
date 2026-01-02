#ifndef GUARD_LIBCSC_IBT_I_IBTREQUEST_H
#define GUARD_LIBCSC_IBT_I_IBTREQUEST_H

#include <libbasar_definitions.h>
#include <datatypes/int32.h>
#include <datatypes/weekdayenum.h>
#include <base/istreamable.h>
#include <ibt/ibtrequest/ibtrequestprocessingstateenum.h>
#include <ibt/ibtrequest/discount/iibtrequestdiscountptr.h>
#include <ibt/ibtrequest/discount/ibtrequestdiscounttypeenum.h>
#include <ibt/ibtrequest/remark/iibtrequestremarkptr.h>
#include <ibt/ibtrequest/remark/ibtrequestremarklevelenum.h>
#include <types/orderremarktypeenum.inc>

namespace libcsc 
{
namespace ibt 
{
class IIbtRequest : public base::IStreamable
{
public:
	virtual ~IIbtRequest() {};

	virtual const libcsc::Int32 & getIbtRequestId() const = 0;
	virtual const basar::Int16 & getBranchNo() const = 0;
	virtual const basar::Int32 & getCscOrderNo() const = 0;
	virtual const basar::Int32 & getCscOrderPosNo() const = 0;
	virtual const basar::Int16 & getIbtBranchNo() const = 0;
	virtual const basar::Int32 & getIbtCustomerNo() const = 0;
	virtual const basar::DateTime & getCreationDateTime() const = 0;
	virtual const IbtRequestProcessingStateEnum & getProcessingState() const = 0;
	virtual const basar::Int32 & getCustomerNo() const = 0;
	virtual const basar::VarString & getOrderType() const = 0;
	virtual const basar::VarString & getPickingType() const = 0;
	virtual const basar::VarString & getBookingType() const = 0;
	virtual const basar::Int32 & getArticleNo() const = 0;
	virtual const basar::Int16 & getArticleCodeType() const = 0;
	virtual const basar::VarString & getArticleCode() const = 0;
	virtual const basar::Int32 & getQuantity() const = 0;
	virtual const basar::VarString & getCustomerTourId() const = 0;
	virtual const ::WeekDayEnum & getTourWeekDay() const = 0;
	virtual const basar::Int16 & getNLevelIbtTypeId() const = 0;
	virtual const basar::Int16 & getDayIbtFlag() const = 0;
	virtual const basar::VarString & getCustOrderRef() const = 0;
	virtual const basar::Decimal & getManualFixPrice() const = 0;
	virtual const basar::VarString & getPaymentTerm() const = 0;
	virtual const basar::VarString & getIbtTourId() const = 0;
	virtual const basar::Date & getIbtTourDate() const = 0;

	virtual const IIbtRequestDiscountCollection & getDiscounts() const = 0;
	virtual const IIbtRequestRemarkCollection & getRemarks() const = 0;

	virtual IIbtRequestDiscountPtr getDiscount( const IbtRequestDiscountTypeEnum discountType, const basar::Int16 paymentTargetNo ) = 0;
	virtual IIbtRequestRemarkPtr getRemark( const IbtRequestRemarkLevelEnum remarkLevel, const OrderRemarkTypeEnum remarkType ) = 0;

	virtual void markAsBooked() = 0;
	virtual bool hasToBeBooked() = 0;
	virtual bool isProcessed() = 0;

	virtual void setBranchNo( const basar::Int16 branchNo ) = 0;
	virtual void setCscOrderNo( const basar::Int32 cscOrderNo ) = 0;
	virtual void setCscOrderPosNo( const basar::Int32 cscOrderPosNo ) = 0;
	virtual void setIbtBranchNo( const basar::Int16 ibtBranchNo ) = 0;
	virtual void setIbtCustomerNo( const basar::Int32 ibtCustomerNo ) = 0;
	virtual void setCreationDateTime( const basar::DateTime & creationDateTime ) = 0;
	virtual void setProcessingState( const IbtRequestProcessingStateEnum processingState ) = 0;
	virtual void setCustomerNo( const basar::Int32 customerNo ) = 0;
	virtual void setOrderType( const basar::VarString & orderType ) = 0;
	virtual void setPickingType( const basar::VarString & pickingType ) = 0;
	virtual void setBookingType( const basar::VarString & bookingType ) = 0;
	virtual void setArticleNo( const basar::Int32 articleNo ) = 0;
	virtual void setArticleCodeType( const basar::Int16 articleCodeType ) = 0;
	virtual void setArticleCode( const basar::VarString & articleCode ) = 0;
	virtual void setQuantity( const basar::Int32 quantity ) = 0;
	virtual void setCustomerTourId( const basar::VarString & customerTourId ) = 0;
	virtual void setTourWeekDay( const ::WeekDayEnum tourWeekDay ) = 0;
	virtual void setNLevelIbtTypeId( const basar::Int16 nLevelIbtTypeId ) = 0;
	virtual void setDayIbtFlag( const basar::Int16 dayIbtFlag ) = 0;
	virtual void setCustOrderRef( const basar::VarString & custOrderRef ) = 0;
	virtual void setManualFixPrice( const basar::Decimal & manualFixPrice ) = 0;
	virtual void setPaymentTerm( const basar::VarString & paymentTerm ) = 0;
	virtual void setIbtTourId( const basar::VarString & ibttourid ) = 0;
	virtual void setIbtTourDate( const basar::Date & ibttourdate ) = 0;
};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_I_IBTREQUEST_H

