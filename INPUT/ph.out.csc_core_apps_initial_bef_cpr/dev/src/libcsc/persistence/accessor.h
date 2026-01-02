#ifndef GUARD_LIBCSC_PERSISTENCE_ACCESSOR_H
#define GUARD_LIBCSC_PERSISTENCE_ACCESSOR_H

#include <persistence/iaccessor.h>
#include <libbasardbsql_connectionref.h>
#include <libbasardbsql_statementref.h>

// CSCArchitecture libcsc::infrastructure::accessor::

namespace libcsc
{
namespace persistence
{
class Accessor : public IAccessor // SelectAccessor & ExecuteAccessor
{
public:
    Accessor( basar::db::sql::ConnectionRef connection );
    virtual ~Accessor();

    virtual const basar::db::sql::ResultsetRef selectDirty(const basar::VarString& sql);
    virtual const basar::db::sql::ResultsetRef select( const basar::VarString & sql );
    virtual const basar::db::sql::ResultsetRef select( const basar::VarString & sql, const ISqlParameterBinderPtr parameterBinder );

    virtual const basar::db::sql::ExecuteReturnInfo execute( const basar::VarString & sql, const bool flagExcept = true );
    virtual const basar::db::sql::ExecuteReturnInfo execute( const basar::VarString & sql, const ISqlParameterBinderPtr parameterBinder, const bool flagExcept = true );

    virtual basar::Int64 getLastInsertedSerial() const;

private:
    basar::db::sql::ConnectionRef           m_Connection;
    basar::db::sql::StatementRef            m_SelectStatement;
    basar::db::sql::PreparedStatementRef    m_PrepSelStatement;
    basar::db::sql::PreparedStatementRef    m_PrepExecuteStatement;

    basar::Int64 m_LastInsertedSerial;
};

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_ACCESSOR_H
