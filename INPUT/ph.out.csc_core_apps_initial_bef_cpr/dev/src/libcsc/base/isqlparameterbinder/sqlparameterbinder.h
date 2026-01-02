/*
 * sqlparameterbinder.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_BASE_SQLPARAMETERBINDER_H
#define GUARD_LIBCSC_BASE_SQLPARAMETERBINDER_H

#include <persistence/isqlparameterbinder.h>
#include "base/isqlparameterbinder/idomainmoduleptr.h"

namespace libcsc {
namespace base {

// Required _Fn signature: _Fn (basar::db::sql::PreparedStatementRef, base::isqlparameterbinder::IDomainModulePtr const)
template<class _Fn>
class SqlParameterBinder : public persistence::ISqlParameterBinder
{
public:
    SqlParameterBinder(IDomainModulePtr const domainModule, _Fn _Func) : m_DomainModule(domainModule), m_Func(_Func)
    {
    }

    virtual ~SqlParameterBinder() {}

    virtual void bind(basar::db::sql::PreparedStatementRef preparedStatement) const
    {
        m_Func(preparedStatement, m_DomainModule);
    }

private:
    IDomainModulePtr const m_DomainModule;
    _Fn m_Func;

    SqlParameterBinder& operator=(SqlParameterBinder const& binder);
};

} // end namespace base
} // end namespace libcsc

#endif // GUARD_LIBCSC_BASE_SQLPARAMETERBINDER_H
