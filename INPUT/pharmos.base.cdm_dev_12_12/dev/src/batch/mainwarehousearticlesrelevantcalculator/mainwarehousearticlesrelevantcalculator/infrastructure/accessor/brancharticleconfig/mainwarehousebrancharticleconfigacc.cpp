#include "mainwarehousebrancharticleconfigacc.h"
#include "mainwarehousebrancharticleconfigacc_definitions.h"

#include "domainmodule/mainwarehousearticlesrelevantcalculator_properties_definitions.h"

#include "infrastructure/accessor/accessorbase/sql2aspectresultinfomapper.h"
#include <libbasardbsql_statementref.h>
#include <libutil/util.h>

#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"

namespace mainwarehousearticlesrelevantcalculator
{
namespace infrastructure
{
namespace accessor
{
namespace branchArticleConfig
{
    MainwarehouseBranchArticleConfigACC::MainwarehouseBranchArticleConfigACC()
        : AccessorBase( lit::MAINWAREHOUSE_BRANCH_ARTICLE_CONFIG_ACC )
    {
    }

    MainwarehouseBranchArticleConfigACC::~MainwarehouseBranchArticleConfigACC()
    {
        // is this really necessary?
        if( ! m_InsertStatement.isNull() )
        {
            if( m_InsertStatement.isOpen() )
            {
                m_InsertStatement.close();
            }

            m_InsertStatement.reset();
        }

        if( ! m_UpdateStatement.isNull() )
        {
            if( m_UpdateStatement.isOpen() )
            {
                m_UpdateStatement.close();
            }

            m_UpdateStatement.reset();
        }
    }

    void MainwarehouseBranchArticleConfigACC::registerAccessorMethods( AccMethodCaller& accMethodCaller )
    {
        accMethodCaller.registerAccessMethod( article::lit::INSERT_FLAG,             &MainwarehouseBranchArticleConfigACC::insertOrderAtMainwarehouseFlag, this );
        accMethodCaller.registerAccessMethod( article::lit::UPDATE_FLAG,             &MainwarehouseBranchArticleConfigACC::updateOrderAtMainwarehouseFlag, this );
        accMethodCaller.registerAccessMethod( article::lit::ERASE_DEPRECATED_CONFIG, &MainwarehouseBranchArticleConfigACC::eraseDeprecatedConfig,          this );
    }

    void MainwarehouseBranchArticleConfigACC::setupPropertyDescriptionList( basar::property::PropertyDescriptionListRef pdl ) const
    {
        pdl.push_back( properties::ARTICLE_NO     );
        pdl.push_back( properties::RELEVANCE_FLAG );
        pdl.push_back( properties::ADMISSION_PARAM_GROUPID );
    }

    void MainwarehouseBranchArticleConfigACC::setSession( libutil::infrastructure::session::ISessionPtr session )
    {
        m_Session = session;
    }

    basar::VarString MainwarehouseBranchArticleConfigACC::getAreaId() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Session.get() );
        basar::VarString areaId;
        areaId.itos( m_Session->getUser()->getAreaID() );
        return areaId;
    }

    basar::VarString MainwarehouseBranchArticleConfigACC::getUserName() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Session.get() );
        return m_Session->getUser()->getUserName();
    }

    void MainwarehouseBranchArticleConfigACC::injectConnection( libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr dbConnectionData )
    {
        m_ConnectionData = dbConnectionData;
    }

    basar::db::sql::ConnectionRef MainwarehouseBranchArticleConfigACC::getConnection() const
    {
        CHECK_INSTANCE_EXCEPTION( m_ConnectionData.get() );
        return m_ConnectionData->getCurrentConnection().getSqlConnection();
    }

    const basar::db::aspect::ExecuteResultInfo MainwarehouseBranchArticleConfigACC::insertOrderAtMainwarehouseFlag( basar::db::aspect::AccessorPropertyTable_YIterator yit, 
                                                                                                                    bool flagExcept )
    {
        if( m_InsertStatement.isNull() || ! m_InsertStatement.isOpen() )
        {
            const basar::VarString constSQL(
                "INSERT INTO pumainwarehousebrancharticleconfig "
                "(branchno"   ", articleno, orderatmainwarehouseflag, lastchangedate, userlastchange, admissionparamgroupid)  VALUES (" + 
                getAreaId() + ", ?"      ", ?"                     ", CURRENT, '" +    getUserName()        + "' , ? )"
            );

			BLOG_INFO( LoggerPool::getLoggerDomModules(), "creating INSERT stmt:" + constSQL );

            m_InsertStatement = getConnection().createPreparedStatement( constSQL );
			}

        // fill data
        m_InsertStatement.setInt32( 0, yit.getInt32( properties::ARTICLE_NO     ) );
        m_InsertStatement.setInt16( 1, yit.getInt16( properties::RELEVANCE_FLAG ) );
        m_InsertStatement.setInt16(2, yit.getInt16(properties::ADMISSION_PARAM_GROUPID));

        basar::db::sql::ExecuteReturnInfo ret = m_InsertStatement.execute( flagExcept );

        SQL2AspectResultInfoMapper mapper;
        return mapper.fromSQLReturnInfo( ret );
    }

    const basar::db::aspect::ExecuteResultInfo MainwarehouseBranchArticleConfigACC::updateOrderAtMainwarehouseFlag( basar::db::aspect::AccessorPropertyTable_YIterator yit, 
                                                                                                                    bool flagExcept )
    {
        if( m_UpdateStatement.isNull() || ! m_UpdateStatement.isOpen() )
        {
            const basar::VarString constSQL(
                "UPDATE pumainwarehousebrancharticleconfig SET"
                " orderatmainwarehouseflag = ?, lastchangedate = CURRENT, userlastchange = '" + getUserName() + "'"
                " ,admissionparamgroupid = ? "
                " WHERE branchno = " + getAreaId() + " AND articleno = ?"
            );

			BLOG_INFO( LoggerPool::getLoggerDomModules(), "creating UPDATE stmt:" + constSQL );

			m_UpdateStatement = getConnection().createPreparedStatement( constSQL );
        }

        // fill data
        m_UpdateStatement.setInt16( 0, yit.getInt16( properties::RELEVANCE_FLAG ) );
        m_UpdateStatement.setInt16(1, yit.getInt16(properties::ADMISSION_PARAM_GROUPID));
        m_UpdateStatement.setInt32( 2, yit.getInt32( properties::ARTICLE_NO     ) );

        basar::db::sql::ExecuteReturnInfo ret = m_UpdateStatement.execute( flagExcept );

        SQL2AspectResultInfoMapper mapper;
        return mapper.fromSQLReturnInfo( ret );
    }

    const basar::db::aspect::ExecuteResultInfo MainwarehouseBranchArticleConfigACC::eraseDeprecatedConfig( basar::db::aspect::AccessorPropertyTable_YIterator yit,
                                                                                                           bool flagExcept )
    {
        static const basar::VarString constSQL(
            "DELETE FROM pumainwarehousebrancharticleconfig c WHERE c.branchno = " + getAreaId() + "  AND c.articleno NOT IN "
			"(SELECT artikel_nr FROM artikelf WHERE filialnr = c.branchno)"
        );

		BLOG_INFO( LoggerPool::getLoggerDomModules(), "creating DELETE stmt:" + constSQL );

        basar::db::sql::StatementRef      stmt = getConnection().createStatement();
        basar::db::sql::ExecuteReturnInfo  ret = stmt.execute( constSQL, flagExcept );

        stmt.close();
        stmt.reset();

		BLOG_INFO( LoggerPool::getLoggerDomModules(), "rows deleted=" + ret.getAffectedRows() );

        SQL2AspectResultInfoMapper mapper;
        return mapper.fromSQLReturnInfo( ret );
    }

} // end namespace branchArticleConfig
} // end namespace accessor
} // end namespace infrastructure
} // end namespace mainwarehousearticlesrelevantcalculator
