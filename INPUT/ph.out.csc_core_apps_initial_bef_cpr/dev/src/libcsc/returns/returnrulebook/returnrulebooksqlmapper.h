#ifndef GUARD_LIBCSC_RETURNS_RETURNRULEBOOKSQLMAPPER_H
#define GUARD_LIBCSC_RETURNS_RETURNRULEBOOKSQLMAPPER_H

#include "returnrulebookmapperbase.h"
#include <libbasardbsql_resultsetref.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace returns {

	class ReturnRuleBookSQLMapper : public ReturnRuleBookMapperBase
	{
	public:
		ReturnRuleBookSQLMapper(ReturnRuleBookPtr returnRuleBook, const basar::db::sql::ResultsetRef resultSet);
		virtual ~ReturnRuleBookSQLMapper();

		static const basar::VarString getSelectSQL(const basar::VarString& returnreasoncode);

	protected:
		virtual void doMap();

	private:
		ReturnRuleBookSQLMapper(const ReturnRuleBookSQLMapper&);
		ReturnRuleBookSQLMapper& operator=(const ReturnRuleBookSQLMapper&);

		const basar::db::sql::ResultsetRef		m_ResultSet;
	};

} //returns
} //libcsc

#endif //GUARD_LIBCSC_RETURNS_RETURNRULEBOOKSQLMAPPER_H
