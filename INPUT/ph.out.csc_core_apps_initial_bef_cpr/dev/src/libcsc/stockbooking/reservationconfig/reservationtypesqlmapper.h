#ifndef GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPESQLMAPPER_H
#define GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPESQLMAPPER_H

#include "reservationtypemapperbase.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace stockbooking {

class ReservationTypeSQLMapper : public ReservationTypeMapperBase
{
public:
	ReservationTypeSQLMapper(ReservationTypePtr reservationType, const basar::db::sql::ResultsetRef resultSet);
	virtual ~ReservationTypeSQLMapper();

	static const basar::VarString getSelectSQL();
protected:
	virtual void doMap();

private:
	ReservationTypeSQLMapper(const ReservationTypeSQLMapper&);
	ReservationTypeSQLMapper & operator=(const ReservationTypeSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_STOCKBOOKING_RESERVATIONTYPESQLMAPPER_H
