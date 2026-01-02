#ifndef GUARD_LIBCSC_TENDER_SQL_MAPPER_H
#define GUARD_LIBCSC_TENDER_SQL_MAPPER_H

#include "tendermapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <persistence/isqlparameterbinderptr.h>
#include <libbasar_definitions.h>

namespace libcsc
{
namespace tender
{
class TenderSQLMapper : public TenderMapperBase
{
public:
    TenderSQLMapper( 
        TenderPtr tender, 
        const basar::db::sql::ResultsetRef resultSet 
            );
    virtual ~TenderSQLMapper();
    
	static const basar::VarString getTenderSelectSQL( const basar::Int32 tenderNo );
    static const basar::VarString getSuccessorTenderSelectSQL( const TenderPtr tender, const basar::Int32 tenderState );

	static const basar::VarString getTenderHeadStateUpdateSQL( const basar::Int32 tenderNo, const basar::Int32 tenderState, 
															   const basar::Int32 oldTenderState, const basar::Int32 omgDuration );
	static const basar::VarString getTenderPosStateUpdateSQL( const basar::Int32 tenderNo, const basar::Int32 tenderState );

protected:
    virtual void doMap();

private:
    TenderSQLMapper( const TenderSQLMapper & );
    TenderSQLMapper & operator=( const TenderSQLMapper & );
    
	static const basar::Date getTenderEndDate( const basar::Date & fromDate, const basar::Int32 omgDuration );

    const basar::db::sql::ResultsetRef  m_ResultSet;
};

} // end namespace tender
} // end namespace libcsc

#endif // GUARD_LIBCSC_TENDER_SQL_MAPPER_H
