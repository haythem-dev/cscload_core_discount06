#ifndef GUARD_LIBCSC_PERSISTENCE_I_ACCESSOR_H
#define GUARD_LIBCSC_PERSISTENCE_I_ACCESSOR_H

#include <libbasardbsql_resultsetref.h>
#include <libbasar_definitions.h>
#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_preparedstatementref.h>
#include <persistence/isqlparameterbinderptr.h>

namespace libcsc
{
namespace persistence
{
class IAccessor
{
public:
    virtual ~IAccessor() {}

    virtual const basar::db::sql::ResultsetRef selectDirty(const basar::VarString& sql) = 0;
    virtual const basar::db::sql::ResultsetRef select( const basar::VarString & sql ) = 0;
    virtual const basar::db::sql::ResultsetRef select( const basar::VarString & sql, const ISqlParameterBinderPtr parameterBinder ) = 0;
    virtual const basar::db::sql::ExecuteReturnInfo execute( const basar::VarString & sql, const bool flagExcept = true ) = 0;
    virtual const basar::db::sql::ExecuteReturnInfo execute( const basar::VarString & sql, const ISqlParameterBinderPtr parameterBinder, const bool flagExcept = true ) = 0;
    virtual basar::Int64 getLastInsertedSerial() const = 0;
};

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_I_ACCESSOR_H
