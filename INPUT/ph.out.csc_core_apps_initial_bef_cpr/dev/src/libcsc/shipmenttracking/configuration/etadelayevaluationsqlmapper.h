#ifndef GUARD_LIBCSC_DOCUMENT_ETADELAYEVALUATIONSQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_ETADELAYEVALUATIONSQLMAPPER_H

#include "etadelayevaluationmapperbase.h"
#include "shipmenttracking/shipmenttrackingdatafilter.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace shipmenttracking {

class EtaDelayEvaluationSQLMapper : public EtaDelayEvaluationMapperBase
{
public:
    EtaDelayEvaluationSQLMapper(EtaDelayEvaluationPtr etaDelayEvaluation, const basar::db::sql::ResultsetRef resultSet);
    virtual ~EtaDelayEvaluationSQLMapper();

    static const basar::VarString getSelectSQL(const basar::VarString& dbNameWarehouse);

protected:
    virtual void doMap();

private:
    // prohibit copy constructor and assignment operator:
    EtaDelayEvaluationSQLMapper(const EtaDelayEvaluationSQLMapper&);
    EtaDelayEvaluationSQLMapper & operator=(const EtaDelayEvaluationSQLMapper&);

    const basar::db::sql::ResultsetRef      m_ResultSet;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_ETADELAYEVALUATIONSQLMAPPER_H
