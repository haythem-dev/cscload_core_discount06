#ifndef GUARD_LIBCSC_STOCKBOOKING_LONGTERMLACK_SQL_MAPPER_H
#define GUARD_LIBCSC_STOCKBOOKING_LONGTERMLACK_SQL_MAPPER_H

#include "longtermlackmapperbase.h"

#include <libbasardbsql_resultsetref.h>
#include <persistence/isqlparameterbinderptr.h>
#include <libbasardbsql_preparedstatementref.h>

namespace libcsc
{
namespace stockbooking
{
    
    class LongTermLackSQLMapper : public LongTermLackMapperBase
    {
        class LongTermLackArticle
        {
            public:
                static const basar::Int16 ARTICLE_UNPROCESSIBLE = 0;
        };
        
        ///////////////////////////////////////////////////////////////
        // static section
        ///////////////////////////////////////////////////////////////
        public:
            static const basar::VarString s_NumberOfLacksColumn;
            
            static const basar::VarString getDeleteSQL( const basar::Int32 articleNo );
            static const basar::VarString getSelectSQL();
            
            static const libcsc::persistence::ISqlParameterBinderPtr getSelectSqlParameterBinder( const basar::Int32 articleNo );
            static void bindSelectSQL( basar::db::sql::PreparedStatementRef prepStmt, const basar::Int32 articleNo );

        public:
            LongTermLackSQLMapper( const basar::Int32 articleNo, const basar::db::sql::ResultsetRef resultSet );
	        virtual ~LongTermLackSQLMapper();
	        
        protected:
	        virtual void doMap();

        private:
            LongTermLackSQLMapper( const LongTermLackSQLMapper& );
            LongTermLackSQLMapper& operator=( const LongTermLackSQLMapper& );

	        const basar::db::sql::ResultsetRef		m_ResultSet;
    };

}
}

#endif
