#ifndef GUARD_LIBCSC_CREMA_USERSUGGESTIONSQL_H
#define GUARD_LIBCSC_CREMA_USERSUGGESTIONSQL_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace crema {

class UserSuggestionSql
{
public:
    ~UserSuggestionSql();

    static const basar::VarString getCustomerNoQuery(
        const basar::Int16 branchNo, const basar::Int32 orderNo);

    static const basar::VarString getUserSuggestionInsertQuery(
        const basar::Int16 typeClose, const basar::Int32 reason, const basar::VarString comment, const basar::VarString user, const basar::Int16 branchNo, const basar::Int32 customerNo);

    static const basar::VarString getUserSuggestionUpdateQuery(
        const basar::Int16 typeClose, const basar::Int32 reason, const basar::VarString comment, const basar::Int32 id);

    static const basar::VarString getUserSuggestionQuery(
        const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::VarString userName);

    static const basar::VarString getUserSuggestionQuery(
        const basar::Int16 branchNo, const basar::Int32 customerNo);

private:
    UserSuggestionSql();
    UserSuggestionSql& operator=(const UserSuggestionSql&);

    static const basar::VarString getUserSuggestionBaseQuery(
        const basar::Int16 branchNo, const basar::Int32 customerNo);
};

} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_USERSUGGESTIONSQL_H
