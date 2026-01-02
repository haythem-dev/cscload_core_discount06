#ifndef GUARD_LIBCSC_DOCUMENT_ETADELAYPRESENTATIONSQLMAPPER_H
#define GUARD_LIBCSC_DOCUMENT_ETADELAYPRESENTATIONSQLMAPPER_H

#include "etadelaypresentationmapperbase.h"
#include "shipmenttracking/shipmenttrackingdatafilter.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace shipmenttracking {

class EtaDelayPresentationSQLMapper : public EtaDelayPresentationMapperBase
{
public:
    EtaDelayPresentationSQLMapper(EtaDelayPresentationPtr etaDelayPresentation, const basar::db::sql::ResultsetRef resultSet);
    virtual ~EtaDelayPresentationSQLMapper();

    static const basar::VarString getSelectSQL(
        const basar::VarString& dbNameWarehouse,
        const basar::Int16& branchNo
        );

protected:
    virtual void doMap();

private:
    // prohibit copy constructor and assignment operator:
    EtaDelayPresentationSQLMapper(const EtaDelayPresentationSQLMapper&);
    EtaDelayPresentationSQLMapper & operator=(const EtaDelayPresentationSQLMapper&);

    const basar::db::sql::ResultsetRef      m_ResultSet;
};

} // end namespace shipmenttracking
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_ETADELAYPRESENTATIONSQLMAPPER_H
