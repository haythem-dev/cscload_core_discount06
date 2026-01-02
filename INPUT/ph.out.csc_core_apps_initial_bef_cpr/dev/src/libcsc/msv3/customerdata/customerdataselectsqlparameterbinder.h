#ifndef GUARD_LIBCSC_MSV3_CUSTOMERDATA_SELECT_SQL_PARAMETER_BINDER_H
#define GUARD_LIBCSC_MSV3_CUSTOMERDATA_SELECT_SQL_PARAMETER_BINDER_H

#include <persistence/isqlparameterbinder.h>
#include <libbasarcmnutil_bstring.h>

namespace libcsc {
namespace msv3 {

class CustomerDataSelectSqlParameterBinder : public libcsc::persistence::ISqlParameterBinder
{
public:
	CustomerDataSelectSqlParameterBinder(const short branchno, const int customerno);
	virtual ~CustomerDataSelectSqlParameterBinder();

	virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const;

private:
	short				m_BranchNo;
	int					m_CustomerNo;	
};

} // end namespace msv3
} // end namespace libcsc

#endif // GUARD_LIBCSC_MSV3_CUSTOMERDATA_SELECT_SQL_PARAMETER_BINDER_H
