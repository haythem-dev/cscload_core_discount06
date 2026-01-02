/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// include section
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "longtermlackselectsqlparameterbinder.h"
#include "longtermlacksqlmapper.h"

namespace libcsc
{
namespace stockbooking
{

LongTermLackSelectSqlParameterBinder::LongTermLackSelectSqlParameterBinder( const basar::Int32 articleNo )
: m_ArticleNo( articleNo )
{
}

LongTermLackSelectSqlParameterBinder::~LongTermLackSelectSqlParameterBinder()
{
}

void LongTermLackSelectSqlParameterBinder::bind( basar::db::sql::PreparedStatementRef preparedStatement ) const
{
	LongTermLackSQLMapper::bindSelectSQL( preparedStatement, m_ArticleNo );
}

}
}

