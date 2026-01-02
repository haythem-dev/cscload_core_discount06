#ifndef GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSINSERTSQLPARAMETERBINDER_H
#define GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSINSERTSQLPARAMETERBINDER_H

#include <persistence/isqlparameterbinder.h>
#include <cscorder/cscorderflags/icscorderflagsptr.h>

namespace libcsc {
namespace cscorder {

namespace domMod {
class ICSCOrderFlags;
}

namespace repo {

class CSCOrderFlagsInsertSqlParameterBinder : public persistence::ISqlParameterBinder
{
	public:
		CSCOrderFlagsInsertSqlParameterBinder(domMod::ICSCOrderFlagsPtr cscOrderFlags);
		virtual ~CSCOrderFlagsInsertSqlParameterBinder();

		virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

	private:
		domMod::ICSCOrderFlagsPtr m_CSCOrderFlags;

		CSCOrderFlagsInsertSqlParameterBinder& operator=(CSCOrderFlagsInsertSqlParameterBinder const& binder);		
};		

} // end namespace repo
} // end namespace cscorder
} // end namespace libcsc

#endif // GUARD_LIBCSC_CSCORDER_REPO_CSCORDERFLAGSINSERTSQLPARAMETERBINDER_H
