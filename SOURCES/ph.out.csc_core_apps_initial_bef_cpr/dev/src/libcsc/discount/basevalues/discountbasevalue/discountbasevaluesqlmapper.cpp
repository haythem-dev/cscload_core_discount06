#include "discountbasevaluesqlmapper.h"
#include "discountbasevalue.h"
#include "discount/basevalues/orderbasevalue/iorderbasevaluegetter.h"
#include "discount/basevalues/orderbasevalue/orderitembasevaluecollection.h"
#include "discountbasevaluesinglearticlesqlparameterbinder.h"
#include <sstream>
#include <logger/loggerpool.h>
#include <string.h>
#include <libbasarcmnutil.h>

namespace libcsc
{
namespace discount
{
DiscountBaseValueSQLMapper::DiscountBaseValueSQLMapper( 
	DiscountBaseValuePtr value, 
	const basar::db::sql::ResultsetRef resultSet 
		)
: DiscountBaseValueMapperBase( value ),
  m_ResultSet( resultSet )
{
}

DiscountBaseValueSQLMapper::~DiscountBaseValueSQLMapper()
{
}


const libcsc::persistence::ISqlParameterBinderPtr DiscountBaseValueSQLMapper::getSingleArticleSqlParameterBinder( const IOrderBaseValueGetterPtr orderBaseValue )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountBaseValue(), "DiscountBaseValueSQLMapper::getSingleArticleSqlParameterBinder()" );

	return libcsc::persistence::ISqlParameterBinderPtr( new DiscountBaseValueSingleArticleSqlParameterBinder( orderBaseValue ) );
}

const basar::VarString DiscountBaseValueSQLMapper::getSelectSQLBranchDate( const IOrderBaseValueGetterPtr orderBaseValue, const bool isSelectForSingleArticle )
{
	std::stringstream ss;
	ss << "SELECT "
            "d.branchno, "
            "d.articleno, "
			"d.discountgrpno, "
			"d.pharmacygroupid, "
			"d.customerno, "
			"d.grpdiscounttyp, "
            "TO_DATE(d.datefrom::CHAR(8), '%Y%m%d')::DATE AS datefrom, "
            "TO_DATE(d.dateto::CHAR(8), '%Y%m%d')::DATE AS dateto, "
            //"datefrom, "
            //"dateto, "
            "d.baseqty, "
			"d.discountspec, "
			"d.discounttype, "
			"d.discountqty, "
			"d.discountvaluepct, "
			"d.discountqtypct, "
			"d.surchargepct, "
			"d.pharmgrpexcluded, "
			"d.fixedprice, "
			"d.refundpct, "
			"d.internaldiscount, "
			"d.discountarticle, "
			"d.pharmgrpexcl_2, "
			"d.pharmgrpexcl_3, "
			"d.base_value, "
			"d.base_mult_std_qty, "
			"d.no_multiple_qty, "
			"d.fixeddiscountvalue, "
			"d.manufacturerno, "
			"d.artcategoryno, "
			"d.paymenttargetno, "
			"d.grossprofitpct, "
			"d.addondiscountok, "
			"d.paymenttermtype, "
			"d.targetqty, "
			"d.exceedancepct, "
			"d.refundtype, "
			"d.article_no_pack, "
			"d.refundvalue, "
			"d.promotion_no, "
			"d.maxqty, "
			"d.turnovercalcimpact, "
			"d.addondiscount, "
			"d.monthlydiscount, "
			"NVL(p.preisekapo, 0) as discountarticleprice, "
			"NVL(pr.name, '') as promotionname "
		"FROM discount d, OUTER artikelpreis p, " // JOIN artikelpreis for AEP of rebate-in-kind article
			"OUTER promotions pr "
		"WHERE d.discountarticle = p.artikel_nr and d.promotion_no = pr.promotion_no and d.branchno = ";
	
	if( isSelectForSingleArticle )
	{
		ss << "?";
	}
	else
	{
		ss << orderBaseValue->getBranchNo();
	}
	
	ss << " and "
		"d.datefrom <= cast(to_char(current, '%Y%m%d') as integer) and "
		"d.dateto   >= cast(to_char(current, '%Y%m%d') as integer) and "
		"d.monthlydiscount = 0 "; // skip monthlydiscount - only calculated in Pharmos !
			
	if (isSelectForSingleArticle)
	{
		ss <<  " and ((baseqty <= ? and baseqty > 0) or (base_value <= ? and base_value > 0)) ";
	}

	return ss.str().c_str();
}

const basar::VarString DiscountBaseValueSQLMapper::getSelectSQLCustPharmGrp( const IOrderBaseValueGetterPtr orderBaseValue, const bool isSelectForSingleArticle )
{
	std::stringstream ss;
	ss << "select pharmacygroupid from customerpharmacygr where  branchno = d.branchno and customerno = ";

	if( isSelectForSingleArticle )
	{
		ss << "?";
	}
	else
	{
		ss << orderBaseValue->getCustomerNo();
	}
	ss << " ";

	return ss.str().c_str();
}

const basar::VarString DiscountBaseValueSQLMapper::getSelectSQLPharmGrp( const IOrderBaseValueGetterPtr orderBaseValue, const bool onlyDedicated, const bool isSelectForSingleArticle )
{
	basar::VarString sql;

	sql = "(d.pharmacygroupid in ( "
			+ getSelectSQLCustPharmGrp( orderBaseValue, isSelectForSingleArticle ) + ") ";

	if (!onlyDedicated)
		sql += "or d.pharmacygroupid = '000'"; 

	sql += ") and d.pharmgrpexcluded not in ( "
			+ getSelectSQLCustPharmGrp( orderBaseValue, isSelectForSingleArticle ) + 
			") and d.pharmgrpexcl_2 not in ( "
			+ getSelectSQLCustPharmGrp( orderBaseValue, isSelectForSingleArticle ) + 
			") and d.pharmgrpexcl_3 not in ( "
			+ getSelectSQLCustPharmGrp( orderBaseValue, isSelectForSingleArticle ) + ") ";

	return sql;
}

const basar::VarString DiscountBaseValueSQLMapper::getSelectSQLManufacturerByArticles( const IOrderBaseValueGetterPtr orderBaseValue )
{
	std::stringstream ss;
	ss << " select hersteller_nr from artikelzentral where artikel_nr in ( ";
	ss << orderBaseValue->getOrderItemBaseValueCollection()->getArticleNumbers() << " ) ";
	
	return ss.str().c_str();
}

const basar::VarString DiscountBaseValueSQLMapper::getSelectSQLDiscGrp( const IOrderBaseValueGetterPtr orderBaseValue, const bool onlyDedicated, const bool isSelectForSingleArticle )
{
	std::stringstream ss;
	if( isSelectForSingleArticle )
	{
		ss << " d.discountgrpno = 0 "; // on article level, discounts with range group are irrelevant
	}
	else
	{
		ss <<  "(d.discountgrpno in ( "
				"select discountgrpno from discountgrpmem where branchno = d.branchno and (articleno in ( ";
		ss << orderBaseValue->getOrderItemBaseValueCollection()->getArticleNumbers() << " ) or manufacturerno in ( ";
		ss << getSelectSQLManufacturerByArticles( orderBaseValue ) << " ))) ";


		if( !onlyDedicated )
		{
			ss << "or d.discountgrpno = 0"; 
		}

		ss << ") ";
	}

	return ss.str().c_str();
}

const basar::VarString DiscountBaseValueSQLMapper::getSelectSQLCustomer( const IOrderBaseValueGetterPtr orderBaseValue, const bool onlyDedicated, const bool isSelectForSingleArticle )
{
	std::stringstream ss;
	ss << " (d.customerno = ";
	if( isSelectForSingleArticle )
	{
		ss << "?";
	}
	else
	{
		ss << orderBaseValue->getCustomerNo();
	}
	ss << " ";

	if( !onlyDedicated )
	{
		ss << "or d.customerno = 0"; 
	}
	ss << ") ";

	return ss.str().c_str();
}

const basar::VarString DiscountBaseValueSQLMapper::getSelectSQLArticle( const IOrderBaseValueGetterPtr orderBaseValue, const bool onlyDedicated, const bool isSelectForSingleArticle )
{
	std::stringstream ss;
	ss << " (d.articleno in ( ";
	if( isSelectForSingleArticle )
	{
		ss << "?";
	}
	else
	{
		ss << orderBaseValue->getOrderItemBaseValueCollection()->getArticleNumbers();
	}
	ss << " ) "; 
	
	if(    !onlyDedicated 
		&& !isSelectForSingleArticle ) // on article level, only discounts with current articleno are relevant
	{
		ss << "or d.articleno = 0"; 
	}
	ss << ") ";

	return ss.str().c_str();
}

const basar::VarString DiscountBaseValueSQLMapper::getSelectSQLManufacturer( const IOrderBaseValueGetterPtr orderBaseValue, const bool onlyDedicated, const bool isSelectForSingleArticle )
{
	std::stringstream ss;

	if( isSelectForSingleArticle )
	{
		ss << " d.manufacturerno = 0 "; // on article level, discounts for manufacturers are irrelevant (= range logic)
	}
	else
	{
		ss << " (d.manufacturerno in ( "; 
		ss << getSelectSQLManufacturerByArticles( orderBaseValue );
		ss << ") ";

		if( !onlyDedicated )
		{
			ss << "or d.manufacturerno = 0"; 
		}
		ss << ") ";
	}

	return ss.str().c_str();
}

const basar::VarString DiscountBaseValueSQLMapper::combineSelectSQLParts( const IOrderBaseValueGetterPtr orderBaseValue, const basar::Int16 section, const bool isSelectForSingleArticle )
{
	basar::VarString sql;
	const basar::VarString sqlAnd	= " and ";
																									//											|	singleArticle:
	sql =  getSelectSQLBranchDate	( orderBaseValue, isSelectForSingleArticle );					// prepStmt-Index (branchno):		0		|	branchno 0, baseqty 1, basevalue 2
	sql += sqlAnd;
	sql += getSelectSQLCustomer		( orderBaseValue, 1 == section, isSelectForSingleArticle );		// prepStmt-Index (customerno):		1		|	customerno 3
	sql += sqlAnd;
	sql += getSelectSQLPharmGrp		( orderBaseValue, 2 == section, isSelectForSingleArticle );		// prepStmt-Index (customerno):		2 - 5	|	customerno 4 - 7
	sql += sqlAnd;
	sql += getSelectSQLDiscGrp		( orderBaseValue, 3 == section, isSelectForSingleArticle );		// prepStmt-Index (listOfItems):	6 - 7	|	NN
	sql += sqlAnd;
	sql += getSelectSQLArticle		( orderBaseValue, 4 == section, isSelectForSingleArticle );		// prepStmt-Index (listOfItems):	8		|	articleno 8
	sql += sqlAnd;
	sql += getSelectSQLManufacturer	( orderBaseValue, 5 == section, isSelectForSingleArticle );		// prepStmt-Index (listOfItems):	9		|	NN

	// TODO order by !? fixedprice (desc), ...

	return sql;
}

const basar::VarString & DiscountBaseValueSQLMapper::getSingleArticleSelectSQL()
{
	static basar::VarString sql;
	if( sql.empty() )
	{
		sql = getSelectSQL( IOrderBaseValueGetterPtr(), true );
	}

	if( LoggerPool::getLoggerDiscountBaseValue().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "DiscountBaseValueSQLMapper::getSingleArticleSelectSQL():" << std::endl;
		ss << sql.c_str() << std::endl;
		LoggerPool::getLoggerDiscountBaseValue().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	return sql;
}

const basar::VarString DiscountBaseValueSQLMapper::getSingleArticleSelectDESQL(const IOrderBaseValueGetterPtr orderBaseValue)
{
	std::stringstream sql;
	sql << "SELECT "
			"d.branchno, "
			"d.articleno, "
			"d.discountgrpno, "
			"d.pharmacygroupid, "
			"d.customerno, "
			"d.grpdiscounttyp, "
			"TO_DATE(d.datefrom::CHAR(8), '%Y%m%d')::DATE AS datefrom, "
			"TO_DATE(d.dateto::CHAR(8), '%Y%m%d')::DATE AS dateto, "
			"d.baseqty, "
			"d.discountspec, "
			"d.discounttype, "
			"d.discountqty, "
			"d.discountvaluepct, "
			"d.discountqtypct, "
			"d.surchargepct, "
			"d.pharmgrpexcluded, "
			"d.fixedprice, "
			"d.refundpct, "
			"d.internaldiscount, "
			"d.discountarticle, "
			"d.pharmgrpexcl_2, "
			"d.pharmgrpexcl_3, "
			"d.base_value, "
			"d.base_mult_std_qty, "
			"d.no_multiple_qty, "
			"d.fixeddiscountvalue, "
			"d.manufacturerno, "
			"d.artcategoryno, "
			"d.paymenttargetno, "
			"d.grossprofitpct, "
			"d.addondiscountok, "
			"d.paymenttermtype, "
			"d.targetqty, "
			"d.exceedancepct, "
			"d.refundtype, "
			"d.article_no_pack, "
			"d.refundvalue, "
			"d.promotion_no, "
			"d.maxqty, "
			"d.turnovercalcimpact, "
			"d.addondiscount, "
			"d.monthlydiscount, "
			"0.0 as discountarticleprice, "
			"'' as promotionname "
		"FROM "
			"discount d "
		"WHERE "
			"d.branchno = " << orderBaseValue->getBranchNo() << " and "
			"d.articleno in (" << orderBaseValue->getArticleNo() << ", 0) and "
			"d.customerno in (" << orderBaseValue->getCustomerNo() << ", 0) and " 
			"(d.pharmacygroupid in     (select pharmacygroupid from customerpharmacygr where branchno = d.branchno and customerno = " << orderBaseValue->getCustomerNo() << ") or d.pharmacygroupid = '000') and "
			"d.pharmgrpexcluded not in (select pharmacygroupid from customerpharmacygr where branchno = d.branchno and customerno = " << orderBaseValue->getCustomerNo() << ") and "
			"d.pharmgrpexcl_2   not in (select pharmacygroupid from customerpharmacygr where branchno = d.branchno and customerno = " << orderBaseValue->getCustomerNo() << ") and "
			"d.pharmgrpexcl_3   not in (select pharmacygroupid from customerpharmacygr where branchno = d.branchno and customerno = " << orderBaseValue->getCustomerNo() << ") and "
			"d.discountgrpno = 0 and "
			"d.manufacturerno = 0 and "
			"d.monthlydiscount = 0 and " <<
			basar::Date::getCurrent().getDate() << " between d.datefrom and d.dateto and "
			"((baseqty <= " << orderBaseValue->getItemQty() << " and baseqty > 0) or (base_value <= " << orderBaseValue->getItemValue().toFloat64() << " and base_value > 0)) ";

	if (LoggerPool::getLoggerDiscountBaseValue().isEnabledFor(log4cplus::TRACE_LOG_LEVEL))
	{
		std::stringstream ss;
		ss << "DiscountBaseValueSQLMapper::getSingleArticleSelectDESQL():" << std::endl;
		ss << sql.str() << std::endl;
		LoggerPool::getLoggerDiscountBaseValue().forcedLog(log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__);
	}

	return sql.str();
}


const basar::VarString DiscountBaseValueSQLMapper::getMultiArticleSelectSQL( const IOrderBaseValueGetterPtr orderBaseValue )
{
	basar::VarString sql = getSelectSQL( orderBaseValue, false );

	if( LoggerPool::getLoggerDiscountBaseValue().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
	{
		std::stringstream ss;
		ss << "DiscountBaseValueSQLMapper::getMultiArticleSelectSQL():" << std::endl;
		ss << sql.c_str() << std::endl;
		LoggerPool::getLoggerDiscountBaseValue().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
	}

	return sql;
}

const basar::VarString DiscountBaseValueSQLMapper::getSelectSQL( const IOrderBaseValueGetterPtr orderBaseValue, const bool isSelectForSingleArticle )
{
	basar::VarString sql;
	const basar::VarString sqlUnion	= " UNION ";

	basar::Int16 section = 1;
	basar::Int16 maxSections = 5;

	while (section <= maxSections)
	{
		sql += combineSelectSQLParts( orderBaseValue, section, isSelectForSingleArticle );
		
		if (section < maxSections)
			sql += sqlUnion;

		++section;
	}
	
	return sql;
}

void DiscountBaseValueSQLMapper::bindSingleArticleSelectSQL( basar::db::sql::PreparedStatementRef prepStmt, const IOrderBaseValueGetterPtr orderBaseValue )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountBaseValue(), "DiscountBaseValueSQLMapper::bindSingleArticleSelectSQL()" );

	const basar::Int16 numOfParaPerUnion	= 9;
	const basar::Int16 numOfUnions			= 5;

	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int16 branchno = 0;
	static basar::Int32 custno = 0;
	static basar::Int32 articleno = 0;
	static basar::Int32 baseqty = 0;
	static basar::Decimal basevalue( 0.0 );

	branchno = orderBaseValue->getBranchNo();
	custno = orderBaseValue->getCustomerNo();
	articleno = orderBaseValue->getArticleNo();
	baseqty	= orderBaseValue->getItemQty();
	basevalue = orderBaseValue->getItemValue();

	basar::Int16 counter = 0;
	std::stringstream ss;
	ss << "DiscountBaseValueSQLMapper::bindSingleArticleSelectSQL(), bind parameter values:" << std::endl;

	while (counter < numOfParaPerUnion * numOfUnions)
	{
		switch (counter % numOfParaPerUnion)
		{
		case 0:
			ss << counter << ": " << branchno << " (branchno)" << std::endl;
			prepStmt.setInt16( counter, branchno );
			break;

		case 1: 
			ss << counter << ": " << baseqty << " (baseqty)" << std::endl;
			prepStmt.setInt32( counter, baseqty );
			break;

		case 2:
			ss << counter << ": " << basevalue << " (basevalue)" << std::endl;
			prepStmt.setDecimal( counter, basevalue );
			break;

		case 3:	// fall through
		case 4:
		case 5:
		case 6: 
		case 7:
			ss << counter << ": " << custno << " (custno)" << std::endl;
			prepStmt.setInt32( counter, custno );
			break;

		case 8:	// fall through
			ss << counter << ": " << articleno << " (articleno)" << std::endl;
			prepStmt.setInt32( counter, articleno );
			break;

		default: 
			break;
		}

		++counter;			
	}

	BLOG_TRACE( LoggerPool::getLoggerDiscountBaseValue(), ss.str().c_str() );
}


void DiscountBaseValueSQLMapper::doMap()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerDiscountBaseValue(), "DiscountBaseValueSQLMapper::doMap()" );

	// TODO: check ResultSet
	if( m_ResultSet.isNull() )
	{
		throw;
	}

    setBranchNo         ( m_ResultSet.getInt16      ( "branchno"        ) );
    setArticleNo		( m_ResultSet.getInt32		( "articleno"       ) );
    setDateFrom         ( m_ResultSet.getDate       ( "datefrom"        ) );
    setDateTo           ( m_ResultSet.getDate       ( "dateto"          ) );
	setDiscountGrpNo	( m_ResultSet.getInt32		( "discountgrpno"   ) );
	setPharmacyGrpId	( m_ResultSet.getString		( "pharmacygroupid" ) );
	setCustomerNo		( m_ResultSet.getInt32		( "customerno"      ) );
	setGrpDiscountType	( m_ResultSet.getInt16		( "grpdiscounttyp"  ) );
	setBaseQty			( m_ResultSet.getInt32		( "baseqty" ) );
	setDiscountSpec		( m_ResultSet.getInt16		( "discountspec" ) );
	setDiscountType		( m_ResultSet.getInt16		( "discounttype" ) );
	setDiscountQty		( m_ResultSet.getInt16		( "discountqty" ) );
	setDiscountValuePct	( m_ResultSet.getDecimal	( "discountvaluepct" ) );
	setDiscountQtyPct	( m_ResultSet.getDecimal	( "discountqtypct" ) );
    setDiscountValuePct ( m_ResultSet.getDecimal    ( "discountvaluepct" ) );
	setSurchargePct		( m_ResultSet.getDecimal	( "surchargepct" ) );
	setPharmGrpExcl_1	( m_ResultSet.getString		( "pharmgrpexcluded" ) );
	setPharmGrpExcl_2	( m_ResultSet.getString		( "pharmgrpexcl_2" ) );
	setPharmGrpExcl_3	( m_ResultSet.getString		( "pharmgrpexcl_3" ) );
	setFixedPrice		( m_ResultSet.getDecimal	( "fixedprice" ) );
	setRefundPct		( m_ResultSet.getDecimal	( "refundpct" ) );
	setInternalDiscount	( m_ResultSet.getString		( "internaldiscount" ) );
	setDiscountArticle	( m_ResultSet.getInt32		( "discountarticle" ) );
	setDiscountArticlePrice(m_ResultSet.getDecimal	( "discountarticleprice" ));
	setBaseValue		( m_ResultSet.getDecimal	( "base_value" ) );
	setBaseMultStdQty	( m_ResultSet.getInt32		( "base_mult_std_qty" ) );
	setNoMultipleQty	( m_ResultSet.getString		( "no_multiple_qty" ) );
	setFixedDiscountVal ( m_ResultSet.getDecimal	( "fixeddiscountvalue" ) );
	setManufacturerNo	( m_ResultSet.getInt32		( "manufacturerno" ) );
	setArtCategoryNo	( m_ResultSet.getInt32		( "artcategoryno" ) );
	setPaymentTargetNo	( m_ResultSet.getInt16		( "paymenttargetno" ) );
	setGrossProfitPct	( m_ResultSet.getDecimal	( "grossprofitpct" ) );
	setAddOnDiscountOk	( m_ResultSet.getString		( "addondiscountok" ) );
	setPaymentTermType	( m_ResultSet.getString		( "paymenttermtype" ) );
	setTargetQty		( m_ResultSet.getInt32		( "targetqty" ) );
	setExceedancePct	( m_ResultSet.getDecimal	( "exceedancepct" ) );
	setRefundType		( m_ResultSet.getInt16		( "refundtype" ) );
	setArticleNoPack	( m_ResultSet.getInt32		( "article_no_pack" ) );
	setRefundValue		( m_ResultSet.getDecimal	( "refundvalue" ) );
	setPromotionNo		( m_ResultSet.getInt16		( "promotion_no" ) );
	setMaxQty			( m_ResultSet.getInt32		( "maxqty" ) );
	setTurnoverCalcImpact(m_ResultSet.getString		( "turnovercalcimpact" ) );
	setAddOnDiscount	( m_ResultSet.getString		( "addondiscount" ) );
	setMonthlyDiscount	( m_ResultSet.getString		( "monthlydiscount" ) );
	setPromotionName	( m_ResultSet.getString		( "promotionname" ) );
}

} // end namespace discount
} // end namespace libcsc

