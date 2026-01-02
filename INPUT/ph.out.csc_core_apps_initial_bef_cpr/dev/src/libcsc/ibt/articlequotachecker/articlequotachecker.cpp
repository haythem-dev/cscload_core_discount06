#include "articlequotachecker.h"
#include "persistence/iaccessor.h"
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace ibt
{
ArticleQuotaChecker::ArticleQuotaChecker()
{
}

ArticleQuotaChecker::~ArticleQuotaChecker()
{
	m_SelectAccessor.reset();
}

void ArticleQuotaChecker::injectSelectAccessor( persistence::IAccessorPtr accessor )
{
	m_SelectAccessor = accessor;
}

/*virtual*/ bool ArticleQuotaChecker::isArticleQuotaAvailable( const basar::Int16 localBranchNo, const basar::Int16 ibtBranchNo, const basar::Int32 articleNo, basar::Int32& remainingQty ) const
{	
	try
	{
		std::stringstream sql;
		sql << 	"select CAST((q.quota - q.kumqty) AS INTEGER) as rqty from articlequota q "
				"inner join filiale fi on q.customerno = fi.bganr_ek "
				"where q.branchno = " << ibtBranchNo << " "
				"and fi.filialnr = " << localBranchNo << " "
				"and q.quota >= q.kumqty "
				"and q.articleno = " << articleNo << ";";

		basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select( sql.str().c_str() );
		if( true == resultset.next() )
		{		
			remainingQty = resultset.getInt32("rqty");		
			return true;		
		}
		return false;
	}
	catch(...)
	{
		return false;
	}	
}

} // end namespace ibt
} // end namespace libcsc
