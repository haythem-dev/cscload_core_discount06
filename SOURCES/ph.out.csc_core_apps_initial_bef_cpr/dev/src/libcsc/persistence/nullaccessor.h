#ifndef GUARD_LIBCSC_PERSISTENCE_NULL_ACCESSOR_H
#define GUARD_LIBCSC_PERSISTENCE_NULL_ACCESSOR_H

#include <persistence/iaccessor.h>

namespace libcsc
{
namespace persistence
{
class NullAccessor : public IAccessor
{
public:
    NullAccessor();
    virtual ~NullAccessor();

    virtual const basar::db::sql::ResultsetRef selectDirty(const basar::VarString&);
    virtual const basar::db::sql::ResultsetRef select( const basar::VarString & );
    virtual const basar::db::sql::ResultsetRef select( const basar::VarString &, const ISqlParameterBinderPtr );

    virtual const basar::db::sql::ExecuteReturnInfo execute( const basar::VarString &, const bool );
    virtual const basar::db::sql::ExecuteReturnInfo execute( const basar::VarString &, const ISqlParameterBinderPtr, const bool );

    virtual basar::Int64 getLastInsertedSerial() const;
};

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_NULL_ACCESSOR_H
