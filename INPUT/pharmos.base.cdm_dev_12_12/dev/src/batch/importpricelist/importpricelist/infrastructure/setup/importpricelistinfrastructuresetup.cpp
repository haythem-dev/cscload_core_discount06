//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Michael Helmich
 *  \date       25.08.2021
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include "importpricelistinfrastructuresetup.h"
#include "infrastructure/login/login_definitions.h"
#include "infrastructure/setup/iimportpricelistlogingetter.h"
#include "infrastructure/cmdline/importpricelistcmdlineevaluator.h"
#include "infrastructure/cmdline/importpricelistcmdlineevaluatorptr.h"

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

// name of applcation to be used in UADM login
// tbd: define application IMPORTPRICELIST in UADM and use this name here
static const char* const    UADM_APPLICATION	= "IMPORTPRICELIST";

//--------------------------------------------------------------------------------------------------//
// namespace libBatch
//--------------------------------------------------------------------------------------------------//
namespace importpricelist
{
	namespace infrastructure
	{
        namespace setup
        {
			IMPORTPRICELISTInfrastructureSetup::IMPORTPRICELISTInfrastructureSetup()
		    : InfrastructureSetupBase( libutil::LoggerPool::getLoggerLibUtilAppSetup() )
		    {
			    METHODNAME_DEF( IMPORTPRICELISTInfrastructureSetup, IMPORTPRICELISTInfrastructureSetup )
			    BLOG_TRACE_METHOD( getLogger(), fun );
			}

		    IMPORTPRICELISTInfrastructureSetup::~IMPORTPRICELISTInfrastructureSetup()
		    {
			    METHODNAME_DEF( IMPORTPRICELISTInfrastructureSetup, ~IMPORTPRICELISTInfrastructureSetup)
			    BLOG_TRACE_METHOD( getLogger(), fun );
		    }

			void IMPORTPRICELISTInfrastructureSetup::doInit()
		    {
                evaluateCmdline();
				login();
				//loadTranslators();
			    establishDBConnection();
			}
    	
            void IMPORTPRICELISTInfrastructureSetup::login()
            {
				prepareLogin();
				initLogin();
			}

            void IMPORTPRICELISTInfrastructureSetup::prepareLogin()
            {
                // BB: Bad Hack 1: Down-Cast (with new LIBUTIL-Version not necessary anymore)
                boost::shared_ptr<importpricelist::infrastructure::cmdLine::IMPORTPRICELISTCmdLineEvaluator const> importpricelistCmdLine
                ( 
                    boost::static_pointer_cast<importpricelist::infrastructure::cmdLine::IMPORTPRICELISTCmdLineEvaluator>( getCmdLineEvaluator()) 
                );

                const importpricelist::infrastructure::cmdLine::AppArgs& appArgs = importpricelistCmdLine->getAppArgs();
				const libutil::infrastructure::login::UserLoginData userLoginData( infrastructure::login::USER, 
					                                                               infrastructure::login::PASSWD, 
					                                                               UADM_APPLICATION, 
					                                                               appArgs.m_BranchNo 
				                                                                 );

				// BB: Bad Hack 2: no set available ( emergency solution/workaround: existing inject used) with new LIBUTIL-Version not necessary anymore)
                // b/c of private member libutil::infrastructure::login::ILoginPtr m_Login; in class InfrastructureSetupBase
                injectLogin( m_IMPORTPRICELISTLoginGetter->getNonInteractiveLogin(userLoginData) );
            }

	        void IMPORTPRICELISTInfrastructureSetup::doShutdown()
	        {
	            shutdownDefaultImpl();
			}

            void IMPORTPRICELISTInfrastructureSetup::injectLoginGetter( IIMPORTPRICELISTLoginGetterConstPtr loginGetter )
            {
                m_IMPORTPRICELISTLoginGetter = loginGetter;
            }
        }
    } // end namespace infrastructure
} // end namespace libutil
