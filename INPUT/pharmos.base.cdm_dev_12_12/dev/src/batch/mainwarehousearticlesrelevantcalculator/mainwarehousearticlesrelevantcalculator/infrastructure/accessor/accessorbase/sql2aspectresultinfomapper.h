#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_SQL2ASPECTRESULTINFOMAPPER_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_SQL2ASPECTRESULTINFOMAPPER_H

#include <libbasardbaspect_definitions.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace sql
        {
            struct ExecuteReturnInfo;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{

    class SQL2AspectResultInfoMapper
    {
    public:
        basar::db::aspect::ExecuteResultInfo fromSQLReturnInfo( const basar::db::sql::ExecuteReturnInfo& ) const;
    };

} // end namespace accessor
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_SQL2ASPECTRESULTINFOMAPPER_H
