#ifndef GUARD_LIBCSC_RETURNS_RETURNPERIODSQLMAPPER_H
#define GUARD_LIBCSC_RETURNS_RETURNPERIODSQLMAPPER_H

#include "returnperiodmapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
	namespace returns {

		class ReturnPeriodSQLMapper : public ReturnPeriodMapperBase
		{
		public:
			ReturnPeriodSQLMapper(ReturnPeriodPtr returnPeriod, const basar::db::sql::ResultsetRef resultSet);
			virtual ~ReturnPeriodSQLMapper();

			static const basar::VarString getSelectAllSQL();

		protected:
			virtual void doMap();

		private:
			ReturnPeriodSQLMapper(const ReturnPeriodSQLMapper&);
			ReturnPeriodSQLMapper& operator=(const ReturnPeriodSQLMapper&);

			const basar::db::sql::ResultsetRef		m_ResultSet;
		};

	} //returns
} //libcsc

#endif // GUARD_LIBCSC_RETURNS_RETURNPERIODSQLMAPPER_H
