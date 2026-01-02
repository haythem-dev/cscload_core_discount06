#include "tenderdiscountsqlmapper.h"
#include <discount/tender/tenderdiscount.h>
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace discount
{
TenderDiscountSQLMapper::TenderDiscountSQLMapper( 
	TenderDiscountPtr tenderDiscount, 
	const basar::db::sql::ResultsetRef resultSet 
		)
: TenderDiscountMapperBase( tenderDiscount ),
  m_ResultSet( resultSet )
{
}

TenderDiscountSQLMapper::~TenderDiscountSQLMapper()
{
}

const basar::VarString TenderDiscountSQLMapper::getSelectSQL( const TenderDiscountSearchParams & params )
{
	// Important! If TenderPharmacyGroupPriority contains entries, these pharmacy groups have
	// a higher priority and have to be selected first. All other pharmacy groups get a priority
	// of 99. Result is sorted by priority number, pharmacygroupid, datefrom ascending.

	std::stringstream select;
    select << "SELECT "
	"NVL( prio.priority, 99 ) as priority, "
	"thead.pharmacygroupid, " 
	"thead.datefrom as datefrom, " 
    "tpos.tenderno as tenderno, "
    "tpos.contractqty as contractqty, "
    "tpos.articleno as articleno, "
    "thead.dateto as dateto, "
    "thead.contractno, "
    "tpos.discountcalcfrom, "
    "tpos.discountapplyto, ";

    if( params.customerNo.isDirty() )
    {
        select << " cpgr.branchno AS branchno, ";
    }
    else
    {
        select << "thead.branchno AS branchno, ";
    }

    select << " tpos.adddiscountpct as discountpercent, "
    "CASE WHEN tpos.ownquotaflag = 1 then "
    "    CAST( tpos.contractqty - tpos.ownquotaqty + SUM( NVL( tprog.returnqty, 0 ) ) - SUM( NVL( tprog.deliveryqty, 0 ) ) AS INT ) "
    "ELSE "
    "    CAST( tpos.contractqty + SUM( NVL( tprog.returnqty, 0 ) ) - SUM( NVL( tprog.deliveryqty, 0 ) ) AS INT ) "
    "END as availablequantity, "

	"tpos.recallflag, "
	"tpos.tenderstate::SMALLINT AS tenderstate "

    "FROM tenderpos as tpos "
    "LEFT OUTER JOIN tenderprogress tprog ON tprog.tenderno = tpos.tenderno and tprog.articleno = tpos.articleno " 
    "INNER JOIN tenderhead thead ON thead.tenderno = tpos.tenderno "
	"LEFT OUTER JOIN TenderPharmacyGroupPriority prio ON thead.pharmacygroupid = prio.pharmacygroupid ";

    if( params.customerNo.isDirty() )
    {
        select <<	"INNER JOIN customerpharmacygr cpgr ON thead.pharmacygroupid = cpgr.pharmacygroupid "
				"INNER JOIN kundeschalter ks ON ks.idfnr = cpgr.customerno AND cpgr.branchno = ks.vertriebszentrumnr "
				"INNER JOIN kunde kd on kd.idfnr = cpgr.customerno AND kd.filialnr = cpgr.branchno "
				"INNER JOIN filiale f on f.filialnr = cpgr.branchno ";
    }

    select << " WHERE tpos.articleno = " << params.articleNo.get();

    if( params.customerNo.isDirty() )
    {
        select << " AND ks.skdkundeaegesperrt = '0' AND kd.originalfilialnr = 0 AND cpgr.customerno = " << params.customerNo.get();
    }
    
	std::stringstream group;
	group << "GROUP BY "
	"priority, thead.pharmacygroupid, thead.datefrom, tpos.tenderno, tpos.contractqty, tpos.articleno, thead.dateto, "
	"thead.contractno, tpos.discountcalcfrom, tpos.discountapplyto, branchno, tpos.adddiscountpct, tpos.ownquotaflag, tpos.ownquotaqty, tpos.recallflag, tpos.tenderstate ";
	
	std::stringstream order;
	if( false == params.activeOnly )
	{
		order << "ORDER BY priority, thead.pharmacygroupid, tenderstate DESC, thead.datefrom ";
	}
	else
	{
		order << "ORDER BY tenderstate DESC, priority, thead.pharmacygroupid, thead.datefrom ";
	}

	std::stringstream sql;
	sql << select.str() << " AND thead.tenderstate = 1 AND tpos.tenderstate = 1 " << group.str();
	if( false == params.activeOnly )
	{
		sql << " UNION " << select.str() << " AND thead.tenderstate = 0 AND tpos.tenderstate = 0 " << group.str();
	}
	sql << order.str();

    std::stringstream msg;
    msg << "TenderDiscountSQLMapper::getSelectSql: <" << sql.str().c_str() << ">";
    BLOG_TRACE( libcsc::LoggerPool::getLoggerSession(), msg.str() );

    return sql.str();
}

void TenderDiscountSQLMapper::doMap()
{
	// TODO: check ResultSet
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setTenderNo( m_ResultSet.getInt32( "tenderno" ) );
	setDiscountPercent( m_ResultSet.getDecimal( "discountpercent" ) );
    setPharmacyGroupId( m_ResultSet.getString( "pharmacygroupid" ) ) ;
    setContractNo( m_ResultSet.getString( "contractno") ) ;
    setAvailableQuantity( m_ResultSet.getInt32( "availablequantity" ) ) ;
    setFromDate( m_ResultSet.getInt32( "datefrom" ) );
    setToDate( m_ResultSet.getInt32( "dateto" ) );
    setContractQuantity( m_ResultSet.getInt32( "contractqty" ) );
    setArticleNumber( m_ResultSet.getInt32( "articleno" ) );
    setBranchNumber( m_ResultSet.getInt16( "branchno" ) );
    setRecallFlag( 0 < m_ResultSet.getInt16( "recallflag" ) );
    setTenderState( m_ResultSet.getInt16( "tenderstate" ) );
    setDiscountCalcFrom( m_ResultSet.getInt16( "discountcalcfrom" ) );
    setDiscountApplyTo( m_ResultSet.getInt16( "discountapplyto" ) );
}

} // end namespace discount
} // end namespace libcsc

