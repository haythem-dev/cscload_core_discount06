#include "transmedstatusiddeliveredtocustomersqlfetcher.h"
#include <string>       // std::string
#include <sstream>      // std::stringstream

namespace libcsc {
namespace shipmenttracking {


TransmedStatusIdDeliveredToCustomerSqlFetcher::TransmedStatusIdDeliveredToCustomerSqlFetcher(const basar::db::sql::ResultsetRef resultSet) :
    m_ResultSet(resultSet)
{
}


TransmedStatusIdDeliveredToCustomerSqlFetcher::~TransmedStatusIdDeliveredToCustomerSqlFetcher()
{
}

const basar::VarString TransmedStatusIdDeliveredToCustomerSqlFetcher::getSelectSQL(const basar::VarString& dbNameWarehouse)
{
    std::stringstream sSql;

    sSql <<
        "SELECT ts.id "
        "FROM " << dbNameWarehouse << ":transmedstatus ts "
        "JOIN " << dbNameWarehouse << ":transmedstatuscategory tc ON tc.id=ts.categoryid "
        "WHERE tc.description='DeliveredToCustomer' "
        ;

    return sSql.str();
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
basar::Int16 TransmedStatusIdDeliveredToCustomerSqlFetcher::fetch()
{
    if (m_ResultSet.isNull())
    {
        throw basar::Exception(basar::ExceptInfo("TransmedStatusIdDeliveredToCustomerSqlFetcher::basar::Int16()", "m_ResultSet is Null!", __FILE__, __LINE__), "");
    }

    return m_ResultSet.getInt16("id");
}


} // end namespace shipmenttracking
} // end namespace libcsc
