#include "ibtrequestsqlmapper.h"
#include "ibtrequest.h"
#include <libbasarcmnutil_i18nstring.h>
#include <logger/loggerpool.h>

namespace libcsc
{
namespace ibt
{
IbtRequestSqlMapper::IbtRequestSqlMapper( IbtRequestPtr ibtRequest, const basar::db::sql::ResultsetRef resultSet )
: IbtRequestMapperBase( ibtRequest ), m_ResultSet( resultSet )
{
}

IbtRequestSqlMapper::~IbtRequestSqlMapper()
{
}

void IbtRequestSqlMapper::doMap()
{
    // TODO: check ResultSet
    if( m_ResultSet.isNull() )
    {
        throw;
    }

    setIbtRequestId( m_ResultSet.getInt32( "ibtrequestid" ) );
    setBranchNo( m_ResultSet.getInt16( "branchno" ) );
    setCscOrderNo( m_ResultSet.getInt32( "cscorderno" ) );
    setCscOrderPosNo( m_ResultSet.getInt32( "cscorderposno" ) );
    setIbtBranchNo( m_ResultSet.getInt16( "ibtbranchno" ) );
    setIbtCustomerNo( m_ResultSet.getInt32( "ibtcustomerno" ) );
    setCreationDateTime( m_ResultSet.getDateTime( "creationdatetime" ) );
    setProcessingState( static_cast<IbtRequestProcessingStateEnum>( m_ResultSet.getInt16( "processingstate" ) ) );
    setCustomerNo( m_ResultSet.getInt32( "customerno" ) );
    setOrderType( m_ResultSet.getString( "ordertype" ) );
    setPickingType( m_ResultSet.getString( "pickingtype" ) );
    setBookingType( m_ResultSet.getString( "bookingtype" ) );
    setArticleNo( m_ResultSet.getInt32( "articleno" ) );
    setArticleCodeType( m_ResultSet.getInt16( "articlecodetype" ) );
    setArticleCode( m_ResultSet.getString( "articlecode" ) );
    setQuantity( m_ResultSet.getInt32( "quantity" ) );
    setCustomerTourId( m_ResultSet.getString( "customertourid" ) );
    setTourWeekDay( static_cast< ::WeekDayEnum >( m_ResultSet.getInt16( "tourweekday" ) ) );
    setNLevelIbtTypeId( m_ResultSet.getInt16( "nlevelibttypeid" ) );
    setDayIbtFlag( m_ResultSet.getInt16( "dayibtflag" ) );
    setCustOrderRef( m_ResultSet.getString( "custorderref" ) );
    setManualFixPrice( m_ResultSet.getDecimal( "manualfixprice" ) );
    setPaymentTerm( m_ResultSet.getString( "paymentterm" ) );
    setIbtTourId( m_ResultSet.getString( "ibttourid" ) );
    setIbtTourDate( m_ResultSet.getDate( "ibttourdate" ) );
}

bool IbtRequestSqlMapper::isInsertable( const IbtRequestPtr ibtRequest )
{
    return ibtRequest->getIbtRequestId().isUnset();
}

bool IbtRequestSqlMapper::isUpdatable( const IbtRequestPtr ibtRequest )
{
    return (    ibtRequest->getIbtRequestId().isClean()
			 && ibtRequest->containsDirty() );
}

bool IbtRequestSqlMapper::isDeletable( const IbtRequestPtr ibtRequest )
{
    return (    ibtRequest->getIbtRequestId().isClean()
			 && 0 < ibtRequest->getIbtRequestId() );
}

const basar::VarString IbtRequestSqlMapper::getSelectSQL( const IbtRequestKey & key)
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestSqlMapper::getSelectSQL()" );

    std::stringstream ss;
    ss << 
		"SELECT "
            "r.ibtrequestid, "
            "r.branchno, "
            "r.cscorderno, "
            "r.cscorderposno, "
            "r.ibtbranchno, "
            "r.ibtcustomerno, "
            "r.creationdatetime, "
            "r.processingstate, "
            "r.customerno, "
            "r.ordertype, "
            "r.pickingtype, "
            "r.bookingtype, "
            "r.articleno, "
            "r.articlecodetype, "
            "r.articlecode, "
            "r.quantity, "
            "r.customertourid, "
            "r.tourweekday, "
            "r.nlevelibttypeid, "
            "r.dayibtflag, "
            "r.custorderref, "
            "r.manualfixprice, "
            "r.paymentterm, "
            "r.ibttourid, "
            "r.ibttourdate "
	    "FROM ibtrequest r "
        "INNER JOIN kdauftragereignis e ON e.kdauftragnr = r.cscorderno AND e.datum <= TO_CHAR(r.creationdatetime, '%Y%m%d')::integer "
        "WHERE "
            "r.branchno = " << key.branchNo <<
            " AND r.cscorderno = " << key.cscOrderNo <<
            " AND r.cscorderposno = " << key.cscOrderPosNo <<
            //" AND r.ibtbranchno = " << key.ibtBranchNo <<
            " AND e.ereignisart = 110 "; // pxOrder::States - Initial order creation

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

	return ss.str();
}

const basar::VarString IbtRequestSqlMapper::getSelectSQL( const basar::Int32 id )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestSqlMapper::getSelectSQL()" );

    std::stringstream ss;
    ss << "SELECT "
		"r.ibtrequestid, "
		"r.branchno, "
		"r.cscorderno, "
		"r.cscorderposno, "
		"r.ibtbranchno, "
		"r.ibtcustomerno, "
		"r.creationdatetime, "
		"r.processingstate, "
		"r.customerno, "
		"r.ordertype, "
		"r.pickingtype, "
		"r.bookingtype, "
		"r.articleno, "
		"r.articlecodetype, "
		"r.articlecode, "
		"r.quantity, "
		"r.customertourid, "
		"r.tourweekday, "
		"r.nlevelibttypeid, "
		"r.dayibtflag, "
		"r.custorderref, "
		"r.manualfixprice, "
		"r.paymentterm, "
		"r.ibttourid, "
		"r.ibttourdate "

		"FROM ibtrequest r "
		"WHERE "
		"r.ibtrequestid = " << id;

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

	return ss.str();
}

const basar::VarString IbtRequestSqlMapper::getSelectSQL( const IbtRequestPtr ibtRequest )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestSqlMapper::getSelectSQL()" );

    std::stringstream ss;
    ss << "SELECT "
		"r.ibtrequestid, "
		"r.branchno, "
		"r.cscorderno, "
		"r.cscorderposno, "
		"r.ibtbranchno, "
		"r.ibtcustomerno, "
		"r.creationdatetime, "
		"r.processingstate, "
		"r.customerno, "
		"r.ordertype, "
		"r.pickingtype, "
		"r.bookingtype, "
		"r.articleno, "
		"r.articlecodetype, "
		"r.articlecode, "
		"r.quantity, "
		"r.customertourid, "
		"r.tourweekday, "
		"r.nlevelibttypeid, "
		"r.dayibtflag, "
		"r.custorderref, "
		"r.manualfixprice, "
		"r.paymentterm, "
		"r.ibttourid, "
		"r.ibttourdate "

		"FROM ibtrequest r "
		"WHERE "
		"ibtrequestid = " << ibtRequest->getIbtRequestId().get() << " ";

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

	return ss.str();
}

const basar::VarString IbtRequestSqlMapper::getInsertSQL( const IbtRequestPtr ibtRequest )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestSqlMapper::getInsertSQL()" );

	std::stringstream ss;
	ss << "INSERT INTO ibtrequest "
		"( "
		"branchno, "
		"cscorderno, "
		"cscorderposno, "
		"ibtbranchno, "
		"ibtcustomerno, "
		"processingstate, "
		"customerno, "
		"ordertype, "
		"pickingtype, "
		"bookingtype, "
		"articleno, "
		"articlecodetype, "
		"articlecode, "
		"quantity, "
		"customertourid, "
		"tourweekday, "
		"nlevelibttypeid, "
		"dayibtflag, "
		"custorderref, "
		"manualfixprice, "
		"paymentterm, "
		"ibttourid, "
		"ibttourdate "
		") VALUES ( "
		<< ibtRequest->getBranchNo() << ", "
		<< ibtRequest->getCscOrderNo() << ", "
		<< ibtRequest->getCscOrderPosNo() << ", "
		<< ibtRequest->getIbtBranchNo() << ", "
		<< ibtRequest->getIbtCustomerNo() << ", "
		<< ibtRequest->getProcessingState() << ", "
		<< ibtRequest->getCustomerNo() << ", "
		<< "'" << ibtRequest->getOrderType().c_str() << "', "
		<< "'" << ibtRequest->getPickingType().c_str() << "', "
		<< "'" << ibtRequest->getBookingType().c_str() << "', "
		<< ibtRequest->getArticleNo() << ", "
		<< ibtRequest->getArticleCodeType() << ", "
		<< "'" << ibtRequest->getArticleCode().c_str() << "', "
		<< ibtRequest->getQuantity() << ", "
		<< "'" << ibtRequest->getCustomerTourId().c_str() << "', "
		<< ibtRequest->getTourWeekDay() << ", "
		<< ibtRequest->getNLevelIbtTypeId() << ", "
		<< ibtRequest->getDayIbtFlag() << ", "
		<< "'" << ibtRequest->getCustOrderRef().c_str() << "', "
		<< ibtRequest->getManualFixPrice().toNonLocString().c_str() << ", "
		<< "'" << ibtRequest->getPaymentTerm().c_str() << "', "
		<< "'" << ibtRequest->getIbtTourId().c_str() << "', "
		<< "'" << ibtRequest->getIbtTourDate().toString( "%m/%d/%Y" ).c_str() << "' "
		") ";

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

    return ss.str().c_str();
}

const basar::VarString IbtRequestSqlMapper::getUpdateSQL( const IbtRequestPtr ibtRequest )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestSqlMapper::getUpdateSQL()" );

	std::stringstream ss;
	ss << "UPDATE ibtrequest "
		"SET "
		"ibtcustomerno = " << ibtRequest->getIbtCustomerNo() << ", "
		"processingstate = " << ibtRequest->getProcessingState() << ", "
		"customerno = " << ibtRequest->getCustomerNo() << ", "
		"ordertype = '" << ibtRequest->getOrderType().c_str() << "', "
		"pickingtype = '" << ibtRequest->getPickingType().c_str() << "', "
		"bookingtype = '" << ibtRequest->getBookingType().c_str() << "', "
		"articleno = " << ibtRequest->getArticleNo() << ", "
		"articlecodetype = " << ibtRequest->getArticleCodeType() << ", "
		"articlecode = '" << ibtRequest->getArticleCode().c_str() << "', "
		"quantity = " << ibtRequest->getQuantity() << ", "
		"customertourid = '" << ibtRequest->getCustomerTourId().c_str() << "', "
		"tourweekday = " << ibtRequest->getTourWeekDay() << ", "
		"nlevelibttypeid = " << ibtRequest->getNLevelIbtTypeId() << ", "
		"dayibtflag = " << ibtRequest->getDayIbtFlag() << ", "
		"custorderref = '" << ibtRequest->getCustOrderRef().c_str() << "', "
		"manualfixprice = " << ibtRequest->getManualFixPrice().toNonLocString().c_str() << ", "
		"paymentterm = '" << ibtRequest->getPaymentTerm().c_str() << "', "
		"ibttourid = '" << ibtRequest->getIbtTourId().c_str() << "', "
		"ibttourdate = '" << ibtRequest->getIbtTourDate().toString( "%m/%d/%Y" ).c_str() << "' "
		"WHERE "
		"ibtrequestid = " << ibtRequest->getIbtRequestId().get() << " ";

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

    return ss.str();
}

const basar::VarString IbtRequestSqlMapper::getDeleteSQL( const IbtRequestPtr ibtRequest )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestSqlMapper::getDeleteSQL()" );

	std::stringstream ss;
	ss << "DELETE FROM ibtrequest "
		"WHERE "
		"ibtrequestid = " << ibtRequest->getIbtRequestId().get() << " ";

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

	return ss.str();
}

const basar::VarString IbtRequestSqlMapper::getMultiSelectSQL( const basar::Int16 branchno, const IbtRequestProcessingStateEnum state )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestSqlMapper::getMultiSelectSQL()" );

    std::stringstream ss;
    ss << "SELECT "
		"r.ibtrequestid, "
		"r.branchno, "
		"r.cscorderno, "
		"r.cscorderposno, "
		"r.ibtbranchno, "
		"r.ibtcustomerno, "
		"r.creationdatetime, "
		"r.processingstate, "
		"r.customerno, "
		"r.ordertype, "
		"r.pickingtype, "
		"r.bookingtype, "
		"r.articleno, "
		"r.articlecodetype, "
		"r.articlecode, "
		"r.quantity, "
		"r.customertourid, "
		"r.tourweekday, "
		"r.nlevelibttypeid, "
		"r.dayibtflag, "
		"r.custorderref, "
		"r.manualfixprice, "
		"r.paymentterm, "
		"r.ibttourid, "
		"r.ibttourdate "

		"FROM " << "ibtrequest r "
		"WHERE "
		"r.ibtbranchno = " << branchno <<
		" AND "
		"r.processingstate = " << state << " ";

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

	return ss.str();
}

} // end namespace ibt
} // end namespace libcsc
