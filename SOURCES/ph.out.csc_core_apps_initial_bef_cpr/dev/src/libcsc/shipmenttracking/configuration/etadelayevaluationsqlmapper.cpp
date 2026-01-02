#include "etadelayevaluationsqlmapper.h"
#include <string>       // std::string
#include <sstream>      // std::stringstream

namespace libcsc {
namespace shipmenttracking {


EtaDelayEvaluationSQLMapper::EtaDelayEvaluationSQLMapper(EtaDelayEvaluationPtr etaDelayEvaluation, const basar::db::sql::ResultsetRef resultSet) :
    EtaDelayEvaluationMapperBase(etaDelayEvaluation),
    m_ResultSet(resultSet)
{
}


EtaDelayEvaluationSQLMapper::~EtaDelayEvaluationSQLMapper()
{
}

const basar::VarString EtaDelayEvaluationSQLMapper::getSelectSQL(const basar::VarString& dbNameWarehouse)
{
    std::stringstream sSql;

    sSql <<
        "SELECT "
        "uptodelayedminutes, "
        "delaytext "
        "FROM " << dbNameWarehouse << ":etadelayevaluation "
        "order by uptodelayedminutes "
        ;

    return sSql.str();
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void EtaDelayEvaluationSQLMapper::doMap()
{
    if (m_ResultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("EtaDelayEvaluationSQLMapper::doMap()", "m_ResultSet is Null!", __FILE__, __LINE__), "");
    }

    setUpToDelayedMinutes   (m_ResultSet.getInt32("uptodelayedminutes"));
    setDelayText            (m_ResultSet.getString("delaytext"));
}


} // end namespace shipmenttracking
} // end namespace libcsc
