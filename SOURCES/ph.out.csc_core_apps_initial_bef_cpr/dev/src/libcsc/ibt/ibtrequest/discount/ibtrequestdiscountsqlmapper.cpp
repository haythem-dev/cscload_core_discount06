#include "ibtrequestdiscountsqlmapper.h"
//#include "ibtrequestkey.h"
#include "ibtrequestdiscount.h"
#include <libbasarcmnutil_i18nstring.h>
#include <logger/loggerpool.h>

namespace libcsc
{
namespace ibt
{
IbtRequestDiscountSqlMapper::IbtRequestDiscountSqlMapper( IbtRequestDiscountPtr ibtRequestDiscount, const basar::db::sql::ResultsetRef resultSet )
: IbtRequestDiscountMapperBase( ibtRequestDiscount ), m_ResultSet( resultSet )
{
}

IbtRequestDiscountSqlMapper::~IbtRequestDiscountSqlMapper()
{
}

void IbtRequestDiscountSqlMapper::doMap()
{
    // TODO: check ResultSet
    if( m_ResultSet.isNull() )
    {
        throw;
    }

	setIbtRequestId( m_ResultSet.getInt32( "ibtrequestid" ) );
	setDiscountType( static_cast<IbtRequestDiscountTypeEnum>( m_ResultSet.getInt16( "discounttype" ) ) );
	setPharmacyGroupId( m_ResultSet.getString( "pharmacygroupid" ) );
	setPaymentTargetNo( m_ResultSet.getInt16( "paymenttargetno" ) );
	setDiscountValuePct( m_ResultSet.getDecimal( "discountvaluepct" ) );
	setDiscountValuePctMan( m_ResultSet.getDecimal( "discountvaluepctman" ) );
	setFixedPrice(m_ResultSet.getDecimal("fixedprice"));
}

bool IbtRequestDiscountSqlMapper::isInsertable( const IbtRequestDiscountPtr ibtRequestDiscount )
{
    return ibtRequestDiscount->getIbtRequestId().isDirty();
}

bool IbtRequestDiscountSqlMapper::isUpdatable( const IbtRequestDiscountPtr ibtRequestDiscount )
{
    return (    ibtRequestDiscount->getIbtRequestId().isClean()
			 && ibtRequestDiscount->getDiscountType().isClean()
			 && ibtRequestDiscount->getPaymentTargetNo().isClean()
			 && ibtRequestDiscount->containsDirty() );
}

bool IbtRequestDiscountSqlMapper::isDeletable( const IbtRequestDiscountPtr ibtRequestDiscount )
{
    return (    ibtRequestDiscount->getIbtRequestId().isClean()
			 && ibtRequestDiscount->getDiscountType().isClean()
			 && ibtRequestDiscount->getPaymentTargetNo().isClean()
			 && 0 < ibtRequestDiscount->getIbtRequestId() );
}


const basar::VarString IbtRequestDiscountSqlMapper::getSelectSQL( const basar::Int32 ibtRequestId )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestDiscountSqlMapper::getSelectSQL()" );

    std::stringstream ss;
    ss <<
        "SELECT "
            "ibtrequestid, "
            "discounttype, "
            "pharmacygroupid, "
            "paymenttargetno, "
            "discountvaluepct, "
            "discountvaluepctman, "
            "fixedprice "
        "FROM ibtdiscountrequest "
	    "WHERE "
            "ibtrequestid = " << ibtRequestId << " ";

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

	return ss.str();
}

const basar::VarString IbtRequestDiscountSqlMapper::getInsertSQL( const IbtRequestDiscountPtr ibtRequestDiscount )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestDiscountSqlMapper::getInsertSQL()" );

	std::stringstream ss;
	ss << "INSERT INTO ibtdiscountrequest "
		"( "
		"ibtrequestid, "
		"discounttype, "
		"paymenttargetno, "
		"pharmacygroupid, "
		"discountvaluepct, "
		"discountvaluepctman, "
		"fixedprice "
		") VALUES ( "
		<< ibtRequestDiscount->getIbtRequestId().get() << ", "
		<< ibtRequestDiscount->getDiscountType().get() << ", "
		<< ibtRequestDiscount->getPaymentTargetNo().get() << ", "
		<< "'" << ibtRequestDiscount->getPharmacyGroupId().c_str() << "', "
		<< ibtRequestDiscount->getDiscountValuePct().toNonLocString().c_str() << ", "
		<< ibtRequestDiscount->getDiscountValuePctMan().toNonLocString().c_str() << ", "
		<< ibtRequestDiscount->getFixedPrice().toNonLocString().c_str() << " "
		") ";

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

    return ss.str().c_str();
}

const basar::VarString IbtRequestDiscountSqlMapper::getUpdateSQL( const IbtRequestDiscountPtr ibtRequestDiscount )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestDiscountSqlMapper::getUpdateSQL()" );
	
	std::stringstream ss;
	ss << "UPDATE ibtdiscountrequest "
		"SET "
		"pharmacygroupid = " << "'" << ibtRequestDiscount->getPharmacyGroupId().c_str() << "', "
		"discountvaluepct = " << ibtRequestDiscount->getDiscountValuePct().toNonLocString().c_str() << ", "
		"discountvaluepctman = " << ibtRequestDiscount->getDiscountValuePctMan().toNonLocString().c_str() << ", "
		"fixedprice = " << ibtRequestDiscount->getFixedPrice().toNonLocString().c_str() << " "
		"WHERE "
		"ibtrequestid = " << ibtRequestDiscount->getIbtRequestId().get() <<
		" AND "
		"discounttype = " << ibtRequestDiscount->getDiscountType().get() <<
		" AND "
		"paymenttargetno = " << ibtRequestDiscount->getPaymentTargetNo().get() << " "; 

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

    return ss.str();
}

const basar::VarString IbtRequestDiscountSqlMapper::getDeleteSQL( const IbtRequestDiscountPtr ibtRequestDiscount )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerIbtRequest(), "IbtRequestDiscountSqlMapper::getDeleteSQL()" );

	std::stringstream ss;
	ss << "DELETE FROM ibtdiscountrequest "
		"WHERE "
		"ibtrequestid = " << ibtRequestDiscount->getIbtRequestId().get() <<
		" AND "
		"discounttype = " << ibtRequestDiscount->getDiscountType().get() <<
		" AND "
		"paymenttargetno = " << ibtRequestDiscount->getPaymentTargetNo().get() << " "; 

	BLOG_TRACE( LoggerPool::getLoggerIbtRequest(), ss.str().c_str() );

	return ss.str();
}

} // end namespace ibt
} // end namespace libcsc
