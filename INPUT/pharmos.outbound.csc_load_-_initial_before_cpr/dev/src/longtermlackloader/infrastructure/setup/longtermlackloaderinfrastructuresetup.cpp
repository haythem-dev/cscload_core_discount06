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
#include "longtermlackloaderversion/longtermlackloader_version.h"
#include "longtermlackloaderinfrastructuresetup.h"
#include "infrastructure/setup/ilongtermlackloaderdbconnectiongetter.h"
#include "infrastructure/cmdline/longtermlackloadercmdlineevaluator.h"
#include "infrastructure/cmdline/longtermlackloadercmdlineevaluatorptr.h"
#include "infrastructure/setup/ilongtermlackloaderlogingetter.h"
#include "longtermlackloader/longtermlackloader_definitions.h"

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

//#pragma warning (push)
//#pragma warning(disable: 4127 4244 4311 4312 4800 4251)
//#include <QApplication>

//#pragma warning (pop)

//--------------------------------------------------------------------------------------------------//
// namespace libBatch
//--------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
	namespace infrastructure
	{
        namespace setup
        {
	        LONGTERMLACKLOADERInfrastructureSetup::LONGTERMLACKLOADERInfrastructureSetup()
		    : InfrastructureSetupBase( libutil::LoggerPool::getLoggerLibUtilAppSetup() )
		    {
			    METHODNAME_DEF( LONGTERMLACKLOADERInfrastructureSetup, LONGTERMLACKLOADERInfrastructureSetup )
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

		    LONGTERMLACKLOADERInfrastructureSetup::~LONGTERMLACKLOADERInfrastructureSetup()
		    {
			    METHODNAME_DEF( LONGTERMLACKLOADERInfrastructureSetup, ~LONGTERMLACKLOADERInfrastructureSetup)
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

            void LONGTERMLACKLOADERInfrastructureSetup::injectLoginGetter( IILongTermLackLoaderLoginGetterPtr longTermLackLoaderLoginGetter )
            {
                m_LongTermLackLoaderLoginGetter  = longTermLackLoaderLoginGetter;
            }

		    void LONGTERMLACKLOADERInfrastructureSetup::doInit()
		    {
                //prepareDBConnection();
				//establishDBConnection();
                
                evaluateCmdline();
                login();
                establishDBConnection();
		    }

            void LONGTERMLACKLOADERInfrastructureSetup::login()
            {
                prepareLogin();
                initLogin();
            }

            void LONGTERMLACKLOADERInfrastructureSetup::prepareLogin()
            {
                // BB: Bad Hack 1: Down-Cast (with new LIBUTIL-Version not necessary anymore)
                boost::shared_ptr< longtermlackloader::infrastructure::cmdLine::LONGTERMLACKLOADERCmdLineEvaluator const > cmdLine
                (
                    boost::static_pointer_cast<longtermlackloader::infrastructure::cmdLine::LONGTERMLACKLOADERCmdLineEvaluator>(getCmdLineEvaluator())
                );

                const longtermlackloader::infrastructure::cmdLine::AppArgs& appArgs = cmdLine->getAppArgs();
                const libutil::infrastructure::login::UserLoginData userLoginData( 
                    appArgs.m_UserName, appArgs.m_Passwd, longtermlackloader::LONGTERMLACKLOADER_APPLICATION_NAME, appArgs.m_AreaID
                );

                // BB: Bad Hack 2: no set available ( emergency solution/workaround: existing inject used) with new LIBUTIL-Version not necessary anymore)
                // b/c of private member libutil::infrastructure::login::ILoginPtr m_Login; in class InfrastructureSetupBase
                injectLogin( m_LongTermLackLoaderLoginGetter->getNonInteractiveLogin(userLoginData) );
            }

    //        void LONGTERMLACKLOADERInfrastructureSetup::prepareDBConnection()
    //        {
    //            // BB: Bad Hack
    //            boost::shared_ptr<longtermlackloader::infrastructure::cmdLine::LONGTERMLACKLOADERCmdLineEvaluator const> cmdLine
    //            ( 
    //                boost::static_pointer_cast<longtermlackloader::infrastructure::cmdLine::LONGTERMLACKLOADERCmdLineEvaluator>( getCmdLineEvaluator()) 
    //            );
    //            const longtermlackloader::infrastructure::cmdLine::AppArgs& appArgs = cmdLine->getAppArgs();

				//libutil::infrastructure::db::dbConnection::DBServerInfo dbServerInfo;
				//dbServerInfo.setInfx( appArgs.m_DBSrv, appArgs.m_DB );
				//injectDBConnection( getDBConnectionGetter()->getDBConnection(dbServerInfo) );
				//
    //        }

	        void LONGTERMLACKLOADERInfrastructureSetup::doShutdown()
	        {
	            shutdownDefaultImpl();
	        }

			/*IDBConnectionGetterConstPtr LONGTERMLACKLOADERInfrastructureSetup::getDBConnectionGetter()
			{
				return m_DBConnectionGetter;
			}

            void LONGTERMLACKLOADERInfrastructureSetup::injectDBConnectionGetter( IDBConnectionGetterConstPtr dbConnectionGetter )
            {
                m_DBConnectionGetter = dbConnectionGetter;
            }*/
        }
    } // end namespace infrastructure
} // end namespace libutil
