#include "environmentchecker.h"
#include "persistence/iaccessor.h"
#include <sstream>
#include "logger/loggerpool.h"

namespace libcsc
{
namespace ibt
{
EnvironmentChecker::EnvironmentChecker()
{
}

EnvironmentChecker::~EnvironmentChecker()
{
	m_SelectAccessor.reset();
}

void EnvironmentChecker::injectSelectAccessor( persistence::IAccessorPtr accessor )
{
	m_SelectAccessor = accessor;
}

bool EnvironmentChecker::isUseOtherDB( const basar::Int16 branchNo, const basar::Int32 articleNo ) const
{
	std::stringstream sql;
	sql << "select count(*) "
		"from ibtbranches ib "
		"join ibtbrancharticleconfig icfg on icfg.branchno=ib.branchno "
		"join rechner rl on rl.filialnr=ib.branchno "
		"join rechner rr on rr.filialnr=ib.ibtbranchno "
		"where ib.branchno=" <<  branchNo << " "
		"and icfg.articleno=" << articleNo << " " 
		"and ib.nlevelibttypeid in (icfg.ibttypeid, 3) "
		"and rr.datenbank_name!=rl.datenbank_name";
		
	basar::db::sql::ResultsetRef resultset = m_SelectAccessor->select( sql.str().c_str() );
	return ( true == resultset.next() );
}

} // end namespace ibt
} // end namespace libcsc
