#ifndef GUARD_STOCKBOOKING_LONGTERMLACK_SELECTSQL_PARAMETERBINDER_H
#define GUARD_STOCKBOOKING_LONGTERMLACK_SELECTSQL_PARAMETERBINDER_H

#include <libbasar_definitions.h>
#include <persistence/isqlparameterbinder.h>


namespace libcsc
{
namespace stockbooking
{
class LongTermLackSelectSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
    public:
        LongTermLackSelectSqlParameterBinder( const basar::Int32 articleNo );
	    virtual ~LongTermLackSelectSqlParameterBinder();

	    virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const;

    private:
        LongTermLackSelectSqlParameterBinder( const LongTermLackSelectSqlParameterBinder& );
        LongTermLackSelectSqlParameterBinder& operator=( const LongTermLackSelectSqlParameterBinder&) ;

    private:
        const basar::Int32 m_ArticleNo;
};

}
}

#endif 
