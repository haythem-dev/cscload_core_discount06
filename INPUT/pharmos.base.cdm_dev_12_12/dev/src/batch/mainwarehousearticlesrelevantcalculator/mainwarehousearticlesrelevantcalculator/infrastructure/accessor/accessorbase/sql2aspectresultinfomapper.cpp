#include "sql2aspectresultinfomapper.h"

#include <libbasardbsql_definitions.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{
    basar::db::aspect::ExecuteResultInfo SQL2AspectResultInfoMapper::fromSQLReturnInfo( const basar::db::sql::ExecuteReturnInfo& retInfo ) const
    {
        basar::db::aspect::ExecuteResultInfo resultInfo;
        resultInfo.m_affectedRows = retInfo.getAffectedRows();

        switch( retInfo.getError() )
        {
        case basar::db::sql::DBErrorCode::SUCCESS:
            resultInfo.m_error = basar::db::aspect::SUCCESS;
            break;
        case basar::db::sql::DBErrorCode::UNKNOWN:
            resultInfo.m_error = basar::db::aspect::SQL_ERROR_UNKNOWN;
            break;
        case basar::db::sql::DBErrorCode::NONSPECIFIC:
            resultInfo.m_error = basar::db::aspect::SQL_ERROR_NONSPECIFIC;
            break;
        case basar::db::sql::DBErrorCode::LENGHT_EXCEEDED:
            resultInfo.m_error = basar::db::aspect::SQL_ERROR;
            break;
        case basar::db::sql::DBErrorCode::INSERT_DUPL:
            resultInfo.m_error = basar::db::aspect::SQL_ERROR_DUPL_INSERT;
            break;
        }

        return resultInfo;
    }

} // end namespace accessor
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator
