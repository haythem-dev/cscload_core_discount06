#ifndef GUARD_LIBCSC_IBT_IBTREQUEST_H
#define GUARD_LIBCSC_IBT_IBTREQUEST_H

#include <ibt/ibtrequest/iibtrequest.h>
#include <datatypes/decimal.h>
#include <datatypes/int16.h>
#include <datatypes/varstring.h>
#include <datatypes/datetime.h>
#include <datatypes/date.h>
#include <datatypes/weekdayenum.h>
#include <datatypes/propertycollection.h>
#include <ibt/ibtrequest/discount/ibtrequestdiscount.h>
#include <ibt/ibtrequest/discount/ibtrequestdiscountptr.h>
#include <ibt/ibtrequest/remark/ibtrequestremark.h>
#include <ibt/ibtrequest/remark/ibtrequestremarkptr.h>
#include <ibt/ibtrequest/iibtrequestfactoryptr.h>
#include <boost/enable_shared_from_this.hpp>

namespace libcsc
{
namespace ibt 
{
class IbtRequest : public IIbtRequest,
				   public boost::enable_shared_from_this<IbtRequest>
{
    // because of OR mapping
    friend class IbtRequestMapperBase;
	friend class IbtRequestRepository;

public:
	IbtRequest();
    virtual ~IbtRequest();

	void injectRequestFactory( IIbtRequestFactoryPtr factory );

	virtual const libcsc::Int32 & getIbtRequestId() const;
	virtual const basar::Int16 & getBranchNo() const;
	virtual const basar::Int32 & getCscOrderNo() const;
	virtual const basar::Int32 & getCscOrderPosNo() const;
	virtual const basar::Int16 & getIbtBranchNo() const;
	virtual const basar::Int32 & getIbtCustomerNo() const;
	virtual const basar::DateTime & getCreationDateTime() const;
	virtual const IbtRequestProcessingStateEnum & getProcessingState() const;
	virtual const basar::Int32 & getCustomerNo() const;
	virtual const basar::VarString & getOrderType() const;
	virtual const basar::VarString & getPickingType() const;
	virtual const basar::VarString & getBookingType() const;
	virtual const basar::Int32 & getArticleNo() const;
	virtual const basar::Int16 & getArticleCodeType() const;
	virtual const basar::VarString & getArticleCode() const;
	virtual const basar::Int32 & getQuantity() const;
	virtual const basar::VarString & getCustomerTourId() const;
	virtual const ::WeekDayEnum & getTourWeekDay() const;
	virtual const basar::Int16 & getNLevelIbtTypeId() const;
	virtual const basar::Int16 & getDayIbtFlag() const;
	virtual const basar::VarString & getCustOrderRef() const;
	virtual const basar::Decimal & getManualFixPrice() const;
	virtual const basar::VarString & getPaymentTerm() const;
	virtual const basar::VarString & getIbtTourId() const;
	virtual const basar::Date & getIbtTourDate() const;

	virtual const IIbtRequestDiscountCollection & getDiscounts() const;
	virtual const IIbtRequestRemarkCollection & getRemarks() const;

	virtual IIbtRequestDiscountPtr getDiscount( const IbtRequestDiscountTypeEnum discountType, const basar::Int16 paymentTargetNo );
	virtual IIbtRequestRemarkPtr getRemark( const IbtRequestRemarkLevelEnum remarkLevel, const OrderRemarkTypeEnum remarkType );

	virtual void setIbtRequestId( const basar::Int32 ibtRequestId );
	virtual void setBranchNo( const basar::Int16 branchNo );
	virtual void setCscOrderNo( const basar::Int32 cscOrderNo );
	virtual void setCscOrderPosNo( const basar::Int32 cscOrderPosNo );
	virtual void setIbtBranchNo( const basar::Int16 ibtBranchNo );
	virtual void setIbtCustomerNo( const basar::Int32 ibtCustomerNo );
	virtual void setCreationDateTime( const basar::DateTime & creationDateTime );
	virtual void setProcessingState( const IbtRequestProcessingStateEnum processingState );
	virtual void setCustomerNo( const basar::Int32 customerNo );
	virtual void setOrderType( const basar::VarString & orderType );
	virtual void setPickingType( const basar::VarString & pickingType );
	virtual void setBookingType( const basar::VarString & bookingType );
	virtual void setArticleNo( const basar::Int32 articleNo );
	virtual void setArticleCodeType( const basar::Int16 articleCodeType );
	virtual void setArticleCode( const basar::VarString & articleCode );
	virtual void setQuantity( const basar::Int32 quantity );
	virtual void setCustomerTourId( const basar::VarString & customerTourId );
	virtual void setTourWeekDay( const ::WeekDayEnum tourWeekDay );
	virtual void setNLevelIbtTypeId( const basar::Int16 nLevelIbtTypeId );
	virtual void setDayIbtFlag( const basar::Int16 dayIbtFlag );
	virtual void setCustOrderRef( const basar::VarString & custOrderRef );
	virtual void setManualFixPrice( const basar::Decimal & manualFixPrice );
	virtual void setPaymentTerm( const basar::VarString & paymentTerm );
	virtual void setIbtTourId( const basar::VarString & ibttourid );
	virtual void setIbtTourDate( const basar::Date & ibttourdate );

	virtual std::ostream & toStream( std::ostream & strm /* = std::cout */ ) const;

    virtual void markAsBooked();
    virtual bool hasToBeBooked();
	virtual bool isProcessed();

	void setClean();
	bool containsDirty() const;

private:
    IbtRequest( const IbtRequest & );
    IbtRequest & operator=( const IbtRequest & );

	libcsc::Int32 m_IbtRequestId;
	libcsc::Int16 m_BranchNo;
	libcsc::Int32 m_CscOrderNo;
	libcsc::Int32 m_CscOrderPosNo;
	libcsc::Int16 m_IbtBranchNo;
	libcsc::Int32 m_IbtCustomerNo;
	libcsc::DateTime m_CreationDateTime;
	IbtRequestProcessingState m_ProcessingState;
	libcsc::Int32 m_CustomerNo;
	libcsc::VarString m_OrderType;
	libcsc::VarString m_PickingType;
	libcsc::VarString m_BookingType;
	libcsc::Int32 m_ArticleNo;
	libcsc::Int16 m_ArticleCodeType;
	libcsc::VarString m_ArticleCode;
	libcsc::Int32 m_Quantity;
	libcsc::VarString m_CustomerTourId;
	libcsc::WeekDayEnum m_TourWeekDay;
	libcsc::Int16 m_NLevelIbtTypeId;
	libcsc::Int16 m_DayIbtFlag;
	libcsc::VarString m_CustOrderRef;
	libcsc::Decimal m_ManualFixPrice;
	libcsc::VarString m_PaymentTerm;
	libcsc::VarString m_IbtTourId;
	libcsc::Date m_IbtTourDate;
	libcsc::PropertyCollection		m_PropertyCollection;

	IIbtRequestDiscountCollection	m_Discounts;
	IIbtRequestRemarkCollection		m_Remarks;
	IIbtRequestFactoryPtr			m_Factory;
};

} // namespace ibt
} // namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUEST_H
