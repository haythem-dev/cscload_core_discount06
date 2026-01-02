#include "bookingcompletedchecker.h"
#include "persistence/iaccessor.h"
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace ibt
{
BookingCompletedChecker::BookingCompletedChecker()
{
}

BookingCompletedChecker::~BookingCompletedChecker()
{
	m_SelectAccessor.reset();
}

void BookingCompletedChecker::injectSelectAccessor( persistence::IAccessorPtr accessor )
{
	m_SelectAccessor = accessor;
}

//basar::VarString BookingCompletedChecker::getRemoteDbIfNecessary( const basar::Int16 branchNo, const basar::Int32 orderNo ) const
//{
//	basar::VarString retval("");
//
//	std::stringstream sql;	
//
//	sql <<	"select first 1 r.datenbank_name from rechner r where "
//			"r.datenbank_name not in (select datenbank_name from rechner where filialnr=" << branchNo << ") "
//			"and r.filialnr in ( "
//			"select distinct filialnr1 from nachlieferpos n1 where n1.postyp=1 and n1.kdauftragnr=" << orderNo << " "
//			"and n1.datum in (select pe.datum from kdauftragereignis pe where pe.kdauftragnr=n1.kdauftragnr) "
//			")";
//
//	basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select( sql.str().c_str() );	
//
//	if( true == resultset.next() )
//	{
//		retval = resultset.getString(0);
//		retval.trim();
//	}
//
//	return retval;
//}

/*virtual*/ bool BookingCompletedChecker::isIBTBookingCompleted( const basar::Int16 branchNo, const basar::Int32 orderNo/*, const basar::Int32 orderLineNo*/) const
{	
	// SR-16070785 check ibt booking completed only in case of a real order
	if( 9999999 == orderNo ) return false; 

	//basar::VarString remoteDb = this->getRemoteDbIfNecessary( branchNo, orderNo );
	//basar::VarString orderLineCondition("");

	//if( orderLineNo > 0 )
	//{
	//	std::stringstream tmp;
	//	tmp << " and n4.ursprungposnr=" << orderLineNo << " ";		       
	//	orderLineCondition = tmp.str();
	//}

	//std::stringstream sql;
	//sql <<	"select count(*) from nachlieferpos n4 "
	//		"join kdauftrag a on a.kdauftragnr=n4.ursprungauftragnr "
	//		"where n4.filialnr1=" << branchNo << " and n4.ursprungauftragnr=" << orderNo << orderLineCondition.c_str() << " "
	//		"and n4.postyp=4 and n4.datum in (select pe.datum from kdauftragposereignis pe where pe.kdauftragnr=n4.ursprungauftragnr and pe.posnr=n4.ursprungposnr) "			
	//		"group by n4.ursprungauftragnr having count(*) > 0 ";

	//if( !remoteDb.empty() )
	//{
	//	sql <<	"union "
	//			"select count(*) from " << remoteDb.c_str() << ":nachlieferpos n4 "
	//			"join kdauftrag a on a.kdauftragnr=n4.ursprungauftragnr "
	//			"where n4.filialnr1=" << branchNo << " and n4.ursprungauftragnr=" << orderNo << orderLineCondition.c_str() << " "
	//			"and n4.postyp=4 and n4.datum in (select pe.datum from kdauftragposereignis pe where pe.kdauftragnr=n4.ursprungauftragnr and pe.posnr=n4.ursprungposnr) "			
	//			"group by n4.ursprungauftragnr having count(*) > 0 ";
	//}

	std::stringstream sql;
	sql <<
		"SELECT r.ibtrequestid "
		"FROM ibtrequest r "
		"INNER JOIN kdauftragereignis e ON e.kdauftragnr = r.cscorderno AND e.datum <= TO_CHAR(r.creationdatetime, '%Y%m%d')::integer "
		"WHERE r.branchno = " << branchNo << " "
		"AND r.cscorderno = " << orderNo << " "
		"AND r.processingstate = 2 "
		"AND e.ereignisart = 110 "; // pxOrder::States - Initial order creation


	basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select( sql.str().c_str() );
	return ( true == resultset.next() );			
}

} // end namespace ibt
} // end namespace libcsc
