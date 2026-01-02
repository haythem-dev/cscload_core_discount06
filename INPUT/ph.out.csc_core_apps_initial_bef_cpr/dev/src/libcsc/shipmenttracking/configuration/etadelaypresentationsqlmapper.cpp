#include "etadelaypresentationsqlmapper.h"
#include <string>       // std::string
#include <sstream>      // std::stringstream

namespace libcsc {
namespace shipmenttracking {


EtaDelayPresentationSQLMapper::EtaDelayPresentationSQLMapper(EtaDelayPresentationPtr etaDelayPresentation, const basar::db::sql::ResultsetRef resultSet) :
    EtaDelayPresentationMapperBase(etaDelayPresentation),
    m_ResultSet(resultSet)
{
}


EtaDelayPresentationSQLMapper::~EtaDelayPresentationSQLMapper()
{
}

const basar::VarString EtaDelayPresentationSQLMapper::getSelectSQL(
    const basar::VarString& dbNameWarehouse,
    const basar::Int16& branchNo)
{
    std::stringstream sSql;

    sSql <<
        "SELECT "
        "edp.branchno, "
        "edp.roundingto, "
        "edp.arrivaltimeframeinminutes "
        "FROM " << dbNameWarehouse << ":etadelaypresentation edp "
        "WHERE "
        "edp.branchno = " << branchNo 
        ;

    return sSql.str();
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void EtaDelayPresentationSQLMapper::doMap()
{
    if (m_ResultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("EtaDelayPresentationSQLMapper::doMap()", "m_ResultSet is Null!", __FILE__, __LINE__), "");
    }

    setBranchNo                 (m_ResultSet.getInt16("branchno"));
    setRoundingTo               (m_ResultSet.getInt16("roundingto"));
    setArrivalTimeFrameInMinutes(m_ResultSet.getInt16("arrivaltimeframeinminutes"));
}


} // end namespace shipmenttracking
} // end namespace libcsc
