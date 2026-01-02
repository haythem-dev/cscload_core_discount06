#include "tendersqlmapper.h"
#include <tender/tender.h>
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace tender
{
TenderSQLMapper::TenderSQLMapper( 
    TenderPtr tender, 
    const basar::db::sql::ResultsetRef resultSet 
    )
: TenderMapperBase( tender ),
  m_ResultSet( resultSet )
{
}

TenderSQLMapper::~TenderSQLMapper()
{
}

const basar::VarString TenderSQLMapper::getTenderSelectSQL( const basar::Int32 tenderNo )
{
	std::stringstream sql;
    sql << "SELECT "
	"thead.pharmacygroupid, " 
	"thead.datefrom as datefrom, " 
	"tpos.tenderno as tenderno, "
	"tpos.contractqty as contractqty, "
	"tpos.articleno as articleno, "
	"thead.dateto as dateto, "
	"thead.contractno AS contractno, "
	"thead.branchno AS branchno, "
	"tpos.adddiscountpct as discountpercent, "
	"thead.tenderstate::SMALLINT AS tenderstate, "
	"CASE WHEN tpos.ownquotaflag = 1 then "
	"    CAST( tpos.contractqty - tpos.ownquotaqty + SUM( NVL( tprog.returnqty, 0 ) ) - SUM( NVL( tprog.deliveryqty, 0 ) ) AS INT ) "
	"ELSE "
	"    CAST( tpos.contractqty + SUM( NVL( tprog.returnqty, 0 ) ) - SUM( NVL( tprog.deliveryqty, 0 ) ) AS INT ) "
	"END AS remainingquantity, "
	"tpos.recallflag AS recallflag "

	"FROM tenderpos as tpos "
	"INNER JOIN tenderhead thead ON thead.tenderno = tpos.tenderno "
	"LEFT OUTER JOIN tenderprogress tprog ON tprog.tenderno = tpos.tenderno and tprog.articleno = tpos.articleno " 

	"WHERE tpos.tenderno = " << tenderNo << 

	"GROUP BY "
	"thead.pharmacygroupid, thead.datefrom, tpos.tenderno, tpos.contractqty, tpos.articleno, thead.dateto, "
	"thead.contractno, thead.branchno, tpos.adddiscountpct, thead.tenderstate, tpos.ownquotaflag, tpos.ownquotaqty, tpos.recallflag ";

    std::stringstream msg;
    msg << "TenderSQLMapper::getTenderSelectSQL:<" << sql.str().c_str() << ">" ;
    BLOG_TRACE( libcsc::LoggerPool::getLoggerTenderDiscount(), msg.str().c_str() );

    return sql.str().c_str();
}

const basar::VarString TenderSQLMapper::getSuccessorTenderSelectSQL( const TenderPtr tender, const basar::Int32 tenderState )
{
	std::stringstream sql;
    sql << "SELECT "

	"NVL( prio.priority, 99 ) as priority, "

	"thead.pharmacygroupid, " 
	"thead.datefrom AS datefrom, " 
	"tpos.tenderno AS tenderno, "
	"tpos.contractqty AS contractqty, "
	"tpos.articleno AS articleno, "
	"thead.dateto AS dateto, "
	"thead.contractno AS contractno, "
	"thead.branchno AS branchno, "
	"tpos.adddiscountpct AS discountpercent, "
	"thead.tenderstate::SMALLINT AS tenderstate, "
	"CASE WHEN tpos.ownquotaflag = 1 then "
	"    CAST( tpos.contractqty - tpos.ownquotaqty + SUM( NVL( tprog.returnqty, 0 ) ) - SUM( NVL( tprog.deliveryqty, 0 ) ) AS INT ) "
	"ELSE "
	"    CAST( tpos.contractqty + SUM( NVL( tprog.returnqty, 0 ) ) - SUM( NVL( tprog.deliveryqty, 0 ) ) AS INT ) "
	"END AS remainingquantity, "
	"tpos.recallflag AS recallflag "

	"FROM tenderpos as tpos "
	"INNER JOIN tenderhead thead ON thead.tenderno = tpos.tenderno "
	"LEFT OUTER JOIN tenderprogress tprog ON tprog.tenderno = tpos.tenderno and tprog.articleno = tpos.articleno "
	
	"LEFT OUTER JOIN TenderPharmacyGroupPriority prio ON thead.pharmacygroupid = prio.pharmacygroupid "

	"WHERE thead.tenderstate = " << tenderState << " "
    "AND tpos.tenderno <> " << tender->getTenderNo().get() << " "
	"AND thead.pharmacygroupid = '" << tender->getPharmacyGroupId().c_str() << "' "
    "AND tpos.articleno = " << tender->getArticleNo().get() << " "
    //"AND thead.dateto >= " << tender->getToDate().get().getDate() << " "

	"GROUP BY "
	"priority, thead.pharmacygroupid, thead.datefrom, tpos.tenderno, tpos.contractqty, tpos.articleno, thead.dateto, "
	"thead.contractno, thead.branchno, tpos.adddiscountpct, thead.tenderstate, tpos.ownquotaflag, tpos.ownquotaqty, tpos.recallflag "

	"ORDER BY priority, thead.pharmacygroupid, thead.datefrom, tpos.tenderno " << std::endl;

    std::stringstream msg;
    msg << "TenderSQLMapper::getSuccessorTenderSelectSQL:<" << sql.str().c_str() << ">" ;
    BLOG_TRACE( libcsc::LoggerPool::getLoggerTenderDiscount(), msg.str().c_str() );

    return sql.str().c_str();
}

const basar::Date TenderSQLMapper::getTenderEndDate( const basar::Date & fromDate, const basar::Int32 omgDuration )
{
	basar::Date endDate( fromDate );
	endDate.addMonths( omgDuration );
	basar::Int32 daysOfMonth = basar::Date::getDaysOfMonth( endDate.getYear(), endDate.getMonth() );
	endDate = basar::Date( endDate.getYear(), endDate.getMonth(), daysOfMonth );
	endDate.addDays( -1 );
    if( basar::cmnutil::Date::SUNDAY == endDate.getDayOfWeek() )
    {
        endDate.addDays( -2 );
    }
    else if( basar::cmnutil::Date::SATURDAY == endDate.getDayOfWeek() )
    {
        endDate.addDays( -1 );
    }
    return endDate;
}

const basar::VarString TenderSQLMapper::getTenderHeadStateUpdateSQL(
	const basar::Int32 tenderNo, const basar::Int32 tenderState, const basar::Int32 oldTenderState, const basar::Int32 omgDuration )
{
	std::stringstream dateFrom;
	std::stringstream dateTo;
	switch( tenderState )
	{
		case 0:
		{
			dateTo << ", dateTo = 99991231 ";
			break;
		}
		case 1:
		{
			if( 0 == oldTenderState )
			{
				dateFrom << ", dateFrom = " << basar::Date::getCurrent().getDate() << " ";
			}
			dateTo << ", dateTo = " << getTenderEndDate( basar::Date::getCurrent(), omgDuration ).getDate() << " ";
			break;
		}
		case 8:
		{
			dateTo << ", dateTo = " << basar::Date::getCurrent().getDate() << " ";
			break;
		}
		case 9:
		{
			dateTo << ", dateTo = " << basar::Date::getCurrent().getDate() << " ";
			break;
		}
	}

	std::stringstream changeDate;
	changeDate << ", changedate = " << basar::Date::getCurrent().getDate() << " ";

	std::stringstream sql;
	sql << "UPDATE tenderhead SET tenderstate=" << tenderState << dateFrom.str().c_str() << dateTo.str().c_str() << changeDate.str().c_str() << " WHERE tenderno=" << tenderNo;

    std::stringstream msg;
    msg << "TenderSQLMapper::getTenderHeadStateUpdateSQL:<" << sql.str().c_str() << ">" ;
    BLOG_TRACE( libcsc::LoggerPool::getLoggerTenderDiscount(), msg.str().c_str() );

    return sql.str().c_str();
}

const basar::VarString TenderSQLMapper::getTenderPosStateUpdateSQL( const basar::Int32 tenderNo, const basar::Int32 tenderState )
{
	std::stringstream sql;
	sql << "UPDATE tenderpos SET tenderstate=" << tenderState << ", changedate = " << basar::Date::getCurrent().getDate() << " WHERE tenderno=" << tenderNo;

    std::stringstream msg;
    msg << "TenderSQLMapper::getTenderPosStateUpdateSQL:<" << sql.str().c_str() << ">" ;
    BLOG_TRACE( libcsc::LoggerPool::getLoggerTenderDiscount(), msg.str().c_str() );

    return sql.str().c_str();
}

void TenderSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setTenderNo( m_ResultSet.getInt32( "tenderno" ) );
	setTenderState( m_ResultSet.getInt16( "tenderstate" ) );
	setRemainingQuantity( m_ResultSet.getInt32( "remainingquantity" ) );
	setPharmacyGroupId( m_ResultSet.getString( "pharmacygroupid" ) ) ;
	setFromDate( m_ResultSet.getInt32( "datefrom" ) );
	setToDate( m_ResultSet.getInt32( "dateto" ) );
	setContractQuantity( m_ResultSet.getInt32( "contractqty" ) );
	setArticleNo( m_ResultSet.getInt32( "articleno" ) );
	setContractNo( m_ResultSet.getString( "contractno" ) );
	setBranchNo( m_ResultSet.getInt16( "branchno" ) );
	setDiscountPercent( m_ResultSet.getDecimal( "discountpercent" ) );
	setRecallFlag( 1 == m_ResultSet.getInt16( "recallflag" )  );
}

} // end namespace tender
} // end namespace libcsc

