/*
 * callbacksqlmapper.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_CALLBACKSQLMAPPER_H
#define GUARD_LIBCSC_CALLBACK_CALLBACKSQLMAPPER_H

#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_preparedstatementref.h>
#include <libbasardbsql_resultsetref.h>
#include <persistence/isqlparameterbinderptr.h>
#include <base/isqlparameterbinder/idomainmoduleptr.h>
#include "callback/domainmodule/icallbackptr.h"
#include "callback/domainmodule/icallbackoverviewitemptr.h"
#include "callback/domainmodule/icallbackposptr.h"
#include "callback/domainmodule/icallbackcustomerptr.h"
#include "callback/domainmodule/icallbackdivisionptr.h"
#include "callback/domainmodule/icallbackreasonptr.h"
#include "callback/domainmodule/icallbackstatusptr.h"
#include "callback/domainmodule/icallbackitemptr.h"
#include "callback/domainmodule/icritptr.h"
#include "callback/domainmodule/icritposptr.h"
#include "callback/repository/findcallbacksrequest.h"
#include "callback/repository/findcustomersrequest.h"

namespace libcsc {
namespace callback {
namespace repo {

class CallbackSqlMapper
{
public:
    CallbackSqlMapper();
    virtual ~CallbackSqlMapper();

    static basar::VarString const getCallbackItemSelectSQL(basar::Int32 const callbackNo, basar::VarString const& dbName);
    static domMod::ICallbackItemPtr mapCallbackItem(basar::db::sql::ResultsetRef const resultSet);

    static basar::VarString const getCallbackSelectSQL(basar::Int32 const callbackNo, basar::VarString const& dbName);
    static domMod::ICallbackPtr mapCallback(basar::db::sql::ResultsetRef const resultSet);

    static basar::VarString const getCallbackPosSelectSQL(basar::Int32 const critNo, basar::VarString const& dbName);
    static domMod::ICallbackPosPtr mapCallbackPos(basar::db::sql::ResultsetRef const resultSet);

    static basar::VarString const getUpdateCallbackItemSQL(basar::VarString const& dbName);
    static persistence::ISqlParameterBinderPtr const getUpdateCallbackItemSqlParameterBinder(base::IDomainModulePtr const domainModule);
    static void bindUpdateCallbackItemSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICallbackItemPtr const callbackItem);

    static basar::VarString const getUpdateCallbackStatusSQL(basar::VarString const& dbName);
    static persistence::ISqlParameterBinderPtr const getUpdateCallbackStatusSqlParameterBinder(base::IDomainModulePtr const domainModule);
    static void bindUpdateCallbackStatusSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICallbackItemPtr const callbackItem);

    static basar::VarString const getMaxPosSelectSQL(basar::Int32 const critNo, basar::VarString const& posTypeTag, basar::VarString const& dbName);

    static basar::VarString const getInsertCritPosSQL(basar::VarString const& dbName);
    static persistence::ISqlParameterBinderPtr const getInsertCritPosSqlParameterBinder(base::IDomainModulePtr const domainModule);
    static void bindInsertCritPosSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICritPosPtr const critPos);

    static basar::VarString const getCallbackDivisionsSelectSQL(basar::Int16 const branchNo, basar::VarString const& dbName);
    static basar::VarString const getCallbackDivisionSelectSQL(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::VarString const& dbName);
    static domMod::ICallbackDivisionPtr mapCallbackDivision(basar::db::sql::ResultsetRef const resultSet);

    static basar::VarString const getCallbackReasonsSelectSQL(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::VarString const& dbName);
    static basar::VarString const getCallbackReasonSelectSQL(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo, basar::VarString const& dbName);
    static domMod::ICallbackReasonPtr mapCallbackReason(basar::db::sql::ResultsetRef const resultSet);

    static basar::VarString const getCallbackStatusesSelectSQL(basar::VarString const& dbName);
    static domMod::ICallbackStatusPtr mapCallbackStatus(basar::db::sql::ResultsetRef const resultSet);

    static basar::VarString const getCallbackStatusVisibilitySelectSQL(basar::VarString const& dbName);
	static bool mapCallbackStatusVisibility(basar::db::sql::ResultsetRef const resultSet);

    static basar::VarString const getFindCustomersSelectSQL(FindCustomersRequestPtr const findCustomersRequest, basar::VarString const& dbName);
    static domMod::ICallbackCustomerPtr mapCustomer(basar::db::sql::ResultsetRef const resultSet);

    static basar::VarString const getFindCustomersCountSelectSQL(FindCustomersRequestPtr const findCustomersRequest, basar::VarString const& dbName);

    static basar::VarString const getMaxCritNoSelectSQL(basar::VarString const& dbName);

    static basar::VarString const getInsertCritSQL(basar::VarString const& dbName);
    static persistence::ISqlParameterBinderPtr const getInsertCritSqlParameterBinder(base::IDomainModulePtr const domainModule);
    static void bindInsertCritItemSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICritPtr const crit);

    static basar::VarString const getMaxCallbackNoSelectSQL(basar::VarString const& dbName);

    static basar::VarString const getInsertCallbackItemSQL(basar::VarString const& dbName);
    static persistence::ISqlParameterBinderPtr const getInsertCallbackItemSqlParameterBinder(base::IDomainModulePtr const domainModule);
    static void bindInsertCallbackItemSQL(basar::db::sql::PreparedStatementRef prepStmt, domMod::ICallbackItemPtr const callbackItem);

    static basar::VarString const getCallbackCustomerSelectSQL(basar::Int16 const branchNo, basar::Int32 const customerNo, basar::VarString const& dbName);
    static domMod::ICallbackCustomerPtr mapCallbackCustomer(basar::db::sql::ResultsetRef const resultSet);

    static basar::VarString const getCallbackUserNameSelectSQL(basar::Int16 const branchNo, basar::Int32 const uid, basar::VarString const& dbName);

    static basar::VarString const getFindCallbacksSelectSQL(FindCallbacksRequestPtr const findCallbacksRequest, basar::VarString const& dbName);
    static domMod::ICallbackOverviewItemPtr mapCallback4Overview(basar::db::sql::ResultsetRef const resultSet);

    static basar::VarString const getFindCallbacksCountSelectSQL(FindCallbacksRequestPtr const findCallbacksRequest, basar::VarString const& dbName);

private:
    static void getSelectSqlByNameForFindCustomers(std::stringstream& ss, basar::VarString pharmacyName, basar::VarString ownerName, basar::VarString city);
    static void getSelectSqlByCustomerNoForFindCustomers(std::stringstream& ss, basar::Int32 const customerNo);
    static void getSelectSqlByMatchCodeFindCustomers(std::stringstream& ss, basar::VarString matchCode, basar::VarString ownerName, basar::VarString city);

    static void getSelectSqlByNameForFindCustomersCount(std::stringstream& ss, basar::VarString pharmacyName, basar::VarString ownerName, basar::VarString city);
    static void getSelectSqlByCustomerNoForFindCustomersCount(std::stringstream& ss, basar::Int32 const customerNo);
    static void getSelectSqlByMatchCodeForFindCustomersCount(std::stringstream& ss, basar::VarString matchCode, basar::VarString ownerName, basar::VarString city);

    static void getCommonWherePartForFindCustomers(std::stringstream& ss, bool const lockedCustomers);
    static void getCommonSelectSqlOutroForFindCustomers(std::stringstream& ss, basar::Int16 const branchNo, bool const onlyOwnBranch, basar::VarString const& dbName);
    static void getBranchNoRange(basar::Int16 const& branchNo, bool const onlyOwnBranch, basar::Int16& branchNoFrom, basar::Int16& branchNoTo);

    static void getWherePartByNameForFindCustomers(std::stringstream& ss, basar::VarString pharmacyName, basar::VarString ownerName, basar::VarString city);
    static void getWherePartByCustomerForFindCustomers(std::stringstream& ss, basar::Int32 const customerNo);
    static void getWherePartByMatchCodeForFindCustomers(std::stringstream& ss, basar::VarString matchCode, basar::VarString ownerName, basar::VarString city);

    static void getCommonFromWherePartForFindCallbacks(std::stringstream& ss, FindCallbacksRequestPtr const findCallbacksRequest, basar::VarString const& dbName);
    static void getWherePart4CustomerNoForFindCallbacks(std::stringstream& ss, basar::Int32 customerNo);
    static void getWherePart4ReasonsForFindCallbacks(std::stringstream& ss, basar::Int16 reasonNo);
    static void getWherePart4DivisionForFindCallbacks(std::stringstream& ss, basar::Int16 divisionNo);
    static void getWherePart4StatusForFindCallbacks(std::stringstream& ss, basar::Int16 statusNo);
};

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_CALLBACKSQLMAPPER_H
