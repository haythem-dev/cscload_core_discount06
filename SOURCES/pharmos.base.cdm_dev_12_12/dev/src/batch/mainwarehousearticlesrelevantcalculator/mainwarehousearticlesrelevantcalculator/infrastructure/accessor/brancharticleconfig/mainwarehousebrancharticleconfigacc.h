#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_MAINWAREHOUSEBRANCHARTICLECONFIG_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_MAINWAREHOUSEBRANCHARTICLECONFIG_H

#include "infrastructure/accessor/accessorbase/accessorbase.h"

#include <libbasardbsql_preparedstatementref.h>

#include <libbasardbsql_connectionref.h>
#include <libutil/dbconnection.h>
#include <libutil/session.h>

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{
namespace branchArticleConfig
{
    class MainwarehouseBranchArticleConfigACC : public AccessorBase
    {
    public:
        MainwarehouseBranchArticleConfigACC();
        ~MainwarehouseBranchArticleConfigACC();

        void                                                                  setSession( libutil::infrastructure::session::ISessionPtr );
        void                                                                  injectConnection( libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr );

        const basar::db::aspect::ExecuteResultInfo                            insertOrderAtMainwarehouseFlag( basar::db::aspect::AccessorPropertyTable_YIterator, bool flagExcept );
        const basar::db::aspect::ExecuteResultInfo                            updateOrderAtMainwarehouseFlag( basar::db::aspect::AccessorPropertyTable_YIterator, bool flagExcept );
        const basar::db::aspect::ExecuteResultInfo                            eraseDeprecatedConfig         ( basar::db::aspect::AccessorPropertyTable_YIterator, bool flagExcept );

    private:
        // overridden
        void                                                                  registerAccessorMethods( AccMethodCaller& );
        void                                                                  setupPropertyDescriptionList( basar::property::PropertyDescriptionListRef ) const;

        basar::VarString                                                      getAreaId()         const;
        basar::VarString                                                      getUserName()       const;
        basar::db::sql::ConnectionRef                                         getConnection()     const;

    private:
        libutil::infrastructure::session::ISessionPtr                         m_Session;
        libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr m_ConnectionData;

        basar::db::sql::PreparedStatementRef                                  m_InsertStatement;
        basar::db::sql::PreparedStatementRef                                  m_UpdateStatement;
    };

} // end namespace branchArticleConfig
} // end namespace accessor
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator

#endif // GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_ACCESSOR_MAINWAREHOUSEBRANCHARTICLECONFIG_H
