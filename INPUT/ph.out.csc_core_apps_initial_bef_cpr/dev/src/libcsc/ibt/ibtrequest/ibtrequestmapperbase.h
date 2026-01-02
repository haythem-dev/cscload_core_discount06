#ifndef GUARD_LIBCSC_IBT_IBTREQUEST_MAPPERBASE_H
#define GUARD_LIBCSC_IBT_IBTREQUEST_MAPPERBASE_H

#include <libbasar_definitions.h>
#include <types/weekdayenum.inc>
#include <ibt/ibtrequest/ibtrequestptr.h>
#include <ibt/ibtrequest/ibtrequestprocessingstateenum.h>

namespace libcsc 
{
namespace ibt
{
class IbtRequestMapperBase
{
public:
    IbtRequestMapperBase( IbtRequestPtr ibtRequest );

    void map();

protected:
    virtual ~IbtRequestMapperBase();

    virtual void doMap() = 0;

	void setIbtRequestId( const basar::Int32 ibtRequestId );
	void setBranchNo( const basar::Int16 branchNo );
	void setCscOrderNo( const basar::Int32 cscOrderNo );
	void setCscOrderPosNo( const basar::Int32 cscOrderPosNo );
	void setIbtBranchNo( const basar::Int16 ibtBranchNo );
	void setIbtCustomerNo( const basar::Int32 ibtCustomerNo );
	void setCreationDateTime( const basar::DateTime & creationDateTime );
	void setProcessingState( const IbtRequestProcessingStateEnum processingState );
	void setCustomerNo( const basar::Int32 customerNo );
	void setOrderType( const basar::VarString & orderType );
	void setPickingType( const basar::VarString & pickingType );
	void setBookingType( const basar::VarString & bookingType );
	void setArticleNo( const basar::Int32 articleNo );
	void setArticleCodeType( const basar::Int16 articleCodeType );
	void setArticleCode( const basar::VarString & articleCode );
	void setQuantity( const basar::Int32 quantity );
	void setCustomerTourId( const basar::VarString & customerTourId );
	void setTourWeekDay( const ::WeekDayEnum tourWeekDay );
	void setNLevelIbtTypeId( const basar::Int16 nLevelIbtTypeId );
	void setDayIbtFlag( const basar::Int16 dayIbtFlag );
	void setCustOrderRef( const basar::VarString & custOrderRef );
	void setManualFixPrice( const basar::Decimal & manualFixPrice );
	void setPaymentTerm( const basar::VarString & paymentTerm );
	void setIbtTourId( const basar::VarString & ibttourid );
	void setIbtTourDate( const basar::Date & ibttourdate );

private:
    IbtRequestPtr	m_IbtRequest;
};

} // end namespace ibt
} // end namespace libcsc

#endif // GUARD_LIBCSC_IBT_IBTREQUEST_MAPPERBASE_H
