#include <crema/usersuggestion/usersuggestionsql.h>
#include "logger/loggerpool.h"
#include <sstream>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace crema {

UserSuggestionSql::UserSuggestionSql()
{
}

UserSuggestionSql::~UserSuggestionSql()
{
}

const basar::VarString UserSuggestionSql::getCustomerNoQuery(
    const basar::Int16 branchNo, const basar::Int32 orderNo)
{
    std::stringstream sql;
    sql << "SELECT kda.idfnr from kdauftrag kda"
        << " where kda.kdauftragnr = " << orderNo << " and kda.vertriebszentrumnr = " << branchNo << ";";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

const basar::VarString UserSuggestionSql::getUserSuggestionInsertQuery(
    const basar::Int16 typeClose, const basar::Int32 reason, const basar::VarString comment, const basar::VarString user, const basar::Int16 branchNo, const basar::Int32 customerNo)
{
    std::stringstream sql;
    sql << "Insert into CremaWebUserSuggestion(choice, choicereason, choicecomment, editorname, customerno, branchno, lastChanged)"
        << " values(" << typeClose << ", " << reason << ", '" << comment << "', '" << user << "', " << customerNo << ", " << branchNo << ", CURRENT YEAR TO SECOND);";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

const basar::VarString UserSuggestionSql::getUserSuggestionUpdateQuery(
    const basar::Int16 typeClose, const basar::Int32 reason, const basar::VarString comment, const basar::Int32 id)
{
    std::stringstream sql;
    sql << "Update CremaWebUserSuggestion set choice = " << typeClose << ", choicereason = " << reason << ", choicecomment = '" << comment
        << "', lastChanged = CURRENT YEAR TO SECOND where id = " << id << ";";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

const basar::VarString UserSuggestionSql::getUserSuggestionQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::VarString userName)
{
    std::stringstream sql;
    sql << getUserSuggestionBaseQuery(branchNo, customerNo)
        << " and editorname = '" << userName << "';";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

const basar::VarString UserSuggestionSql::getUserSuggestionQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo)
{
    std::stringstream sql;
    sql << getUserSuggestionBaseQuery(branchNo, customerNo)
        << " order by lastChanged desc;";

    BLOG_TRACE(LoggerPool::getLoggerParameter(), sql.str());

    return sql.str();
}

const basar::VarString UserSuggestionSql::getUserSuggestionBaseQuery(
    const basar::Int16 branchNo, const basar::Int32 customerNo)
{
    std::stringstream sql;
    sql << "select first 1 * from CremaWebUserSuggestion where customerNo = " << customerNo << " and branchNo = " << branchNo;

    return sql.str();
}

} // end namespace crema
} // end namespace libcsc
