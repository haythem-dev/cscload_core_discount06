//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       12.06.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "ibtorderimportinfrastructuresetup.h"
#include "infrastructure/setup/iibtorderimportlogingetter.h"
#include "infrastructure/cmdline/ibtorderimportcmdlineevaluator.h"
#include "infrastructure/cmdline/ibtorderimportcmdlineevaluatorptr.h"

#include <libutil/applcomponent.h>
#include <libutil/util.h>
#include <libutil/log4cplus.h>
#include <libutil/dbconnection.h>
#include <libutil/login.h>
#include <libutil/exception.h>
#include <libutil/login.h>
#include <libutil/parameter.h>
#include <libutil/languagefileloader.h>

#include <libbasarcmnutil.h>

#include <persistence/connection.h>

static const char* const    UADM_APPLICATION	= "ORDER_ENTRY";

//--------------------------------------------------------------------------------------------------//
// namespace libBatch
//--------------------------------------------------------------------------------------------------//
namespace ibtorderimport
{
	namespace infrastructure
	{
        namespace setup
        {
	        IBTORDERIMPORTInfrastructureSetup::IBTORDERIMPORTInfrastructureSetup()
		    : InfrastructureSetupBase( libutil::LoggerPool::getLoggerLibUtilAppSetup() )
		    {
			    METHODNAME_DEF( IBTORDERIMPORTInfrastructureSetup, IBTORDERIMPORTInfrastructureSetup )
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

		    IBTORDERIMPORTInfrastructureSetup::~IBTORDERIMPORTInfrastructureSetup()
		    {
			    METHODNAME_DEF( IBTORDERIMPORTInfrastructureSetup, ~IBTORDERIMPORTInfrastructureSetup)
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

		    void IBTORDERIMPORTInfrastructureSetup::doInit()
		    {
                evaluateCmdline();
                login();
			    establishCscDbConnection();
		    }

			libutil::infrastructure::parameter::IParameterGatewayPtr IBTORDERIMPORTInfrastructureSetup::getDbParameterGateway() const
			{
				CHECK_INSTANCE_EXCEPTION(m_DbParameterGateway.get());
			
				return m_DbParameterGateway;
			}

			libcsc::persistence::ConnectionPtr IBTORDERIMPORTInfrastructureSetup::getCscDbConnection() const
			{
				CHECK_INSTANCE_EXCEPTION(m_CscDbConnection.get());
			
				return m_CscDbConnection;
			}

			const ibtorderimport::infrastructure::cmdLine::AppArgs& IBTORDERIMPORTInfrastructureSetup::getAppArgs()
			{
				boost::shared_ptr<ibtorderimport::infrastructure::cmdLine::IBTORDERIMPORTCmdLineEvaluator const> ibtorderimportCmdLine
                ( 
                    boost::static_pointer_cast<ibtorderimport::infrastructure::cmdLine::IBTORDERIMPORTCmdLineEvaluator>( getCmdLineEvaluator()) 
                );

				return ibtorderimportCmdLine->getAppArgs();
			}

			basar::VarString IBTORDERIMPORTInfrastructureSetup::getDbServer()
			{
				basar::I18nString paramValue;

				getDbParameterGateway()->getParameterValue(
					getAppArgs().m_BranchNo, 
					basar::I18nString(libutil::infrastructure::db::dbConnection::DBSRV_PARAMETERNAME),
					paramValue);

				return paramValue;
			}
			
			basar::VarString IBTORDERIMPORTInfrastructureSetup::getDatabase()
			{
				basar::I18nString paramValue;

				getDbParameterGateway()->getParameterValue(
					getAppArgs().m_BranchNo, 
					basar::I18nString(libutil::infrastructure::db::dbConnection::DB_PARAMETERNAME),
					paramValue);

				return paramValue;
			}

			void IBTORDERIMPORTInfrastructureSetup::establishCscDbConnection()
			{
				getCscDbConnection()->open( getDbServer(), getDatabase() );
			}

			void IBTORDERIMPORTInfrastructureSetup::releaseCscDbConnection()
			{
				getCscDbConnection()->close();
			}
    	
            void IBTORDERIMPORTInfrastructureSetup::login()
            {
                prepareLogin();
                initLogin();
            }

            void IBTORDERIMPORTInfrastructureSetup::prepareLogin()
            {
                const ibtorderimport::infrastructure::cmdLine::AppArgs& appArgs = getAppArgs();
				const libutil::infrastructure::login::UserLoginData userLoginData( appArgs.m_UserName, appArgs.m_Passwd, UADM_APPLICATION, appArgs.m_BranchNo );

				// BB: Bad Hack 2: no set available ( emergency solution/workaround: existing inject used) with new LIBUTIL-Version not necessary anymore)
                // b/c of private member libutil::infrastructure::login::ILoginPtr m_Login; in class InfrastructureSetupBase
                injectLogin( m_IBTORDERIMPORTLoginGetter->getNonInteractiveLogin(userLoginData) );
            }

	        void IBTORDERIMPORTInfrastructureSetup::doShutdown()
	        {
	            releaseCscDbConnection();
	        }

            void IBTORDERIMPORTInfrastructureSetup::injectLoginGetter( IIBTORDERIMPORTLoginGetterConstPtr loginGetter )
            {
                m_IBTORDERIMPORTLoginGetter = loginGetter;
            }

			void IBTORDERIMPORTInfrastructureSetup::injectCscDbConnection( libcsc::persistence::ConnectionPtr dbConnection )
			{
				m_CscDbConnection = dbConnection;
			}

			void IBTORDERIMPORTInfrastructureSetup::injectDbParameterGateway ( libutil::infrastructure::parameter::IParameterGatewayPtr dbParameterGateway )
			{
				m_DbParameterGateway = dbParameterGateway;
			}
        }
    } // end namespace infrastructure
} // end namespace libutil
