#ifndef GUARD_LIBCSC_PERSISTENCE_I_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_PERSISTENCE_I_SQL_PARAMETER_BINDER_H

#include <libbasardbsql_preparedstatementref.h>

namespace libcsc
{
namespace persistence
{
class ISqlParameterBinder
{
public:
	virtual ~ISqlParameterBinder() {}

	virtual void bind( basar::db::sql::PreparedStatementRef preparedStatement ) const = 0;
};

} // end namespace persistence
} // end namespace libcsc

#endif // GUARD_LIBCSC_PERSISTENCE_I_SQL_PARAMETER_BINDER_H
