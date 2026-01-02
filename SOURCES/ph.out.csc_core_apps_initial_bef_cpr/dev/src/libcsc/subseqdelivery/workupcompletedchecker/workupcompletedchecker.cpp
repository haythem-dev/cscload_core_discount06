#include "workupcompletedchecker.h"
#include "persistence/iaccessor.h"
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace sud
{
WorkupCompletedChecker::WorkupCompletedChecker()
{
}



WorkupCompletedChecker::~WorkupCompletedChecker()
{
	m_SelectAccessor.reset();
}

void WorkupCompletedChecker::injectSelectAccessor( persistence::IAccessorPtr accessor )
{
	m_SelectAccessor = accessor;
}


/*virtual*/ bool WorkupCompletedChecker::isSUDWorkupCompleted( const basar::Int32 orderNo, const basar::Int32 customerNo, const basar::Int32 orderLineNo /*= 0*/ ) const
{
	basar::VarString orderLineCondition("");

	if( orderLineNo > 0 )
	{
		std::stringstream tmp;
		tmp << " and n4.posnr=" << orderLineNo << " ";		       
		orderLineCondition = tmp.str();
	}

	std::stringstream sql;
	sql <<	"select count(*) from nachlieferpos n4 "
			"where n4.kdauftragnr=" << orderNo << "and n4.KundenNr=" << customerNo << orderLineCondition.c_str() << " "
			"and (n4.postyp=2 or n4.postyp=3 or n4.postyp=5) and n4.status=2 having count(*) > 0 ";			

	basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select( sql.str().c_str() );
	return ( true == resultset.next() );			
}

} // end namespace sud
} // end namespace libcsc
