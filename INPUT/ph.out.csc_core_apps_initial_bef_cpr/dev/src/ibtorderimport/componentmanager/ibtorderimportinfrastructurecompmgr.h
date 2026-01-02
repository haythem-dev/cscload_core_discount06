//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   08.07.2013
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_IBTORDERIMPORT_COMPONENTMANAGER_IBTORDERIMPORTINFRASTRUCTURECOMPMGR_H
#define GUARD_IBTORDERIMPORT_COMPONENTMANAGER_IBTORDERIMPORTINFRASTRUCTURECOMPMGR_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include <libutil/cmdline.h>

#include "ibtorderimport/ibtorderimport_definitions.h"
#include "loggerpool/ibtorderimport_loggerpool.h"
#include "ibtorderimportapplcompmgr.h"
#include "infrastructure/cmdline/ibtorderimportcmdlineevaluator.h"
#include "infrastructure/setup/iibtorderimportlogingetter.h"
#include "infrastructure/setup/ibtorderimportinfrastructuresetup.h"
#include "infrastructure/mail/imailparameterproxyptr.h"

#include <boost/enable_shared_from_this.hpp>

#include <persistence/connectionptr.h>

//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace ibtorderimport
{
    namespace componentManager
    {
        //----------------------------------------------------------------------------//
        // class declaration setcion
        //----------------------------------------------------------------------------//
        class InfrastructureCompMgr :
            public libutil::componentManager::InfrastructureCompMgrBase< ibtorderimport::componentManager::ApplCompMgr,
                                                                         ibtorderimport::infrastructure::cmdLine::IBTORDERIMPORTCmdLineEvaluator, 
                                                                         ibtorderimport::infrastructure::setup::IBTORDERIMPORTInfrastructureSetup >,
            public infrastructure::setup::IIBTORDERIMPORTLoginGetter,
            public boost::enable_shared_from_this< InfrastructureCompMgr >
        {
            public:
                InfrastructureCompMgr( int argc, char** argv );
                ~InfrastructureCompMgr();

				 basar::Int32																getSleepInterval()    const;

            protected:
                ////////////////////////////////////////////////////////////////////////////////////////////////
                // <creation_section>
                ////////////////////////////////////////////////////////////////////////////////////////////////
                virtual libutil::infrastructure::IQApplicationPtr                           createQApplication()        const;
                virtual libutil::infrastructure::login::ILoginPtr                           createLogin()               const;
                virtual libutil::infrastructure::user::IUserPtr                             createUser()                const;
                virtual libutil::infrastructure::i18n::ILanguageFileLoaderPtr               createLanguageFileLoader()  const;
                virtual libutil::infrastructure::db::dbConnection::DBConnectionBasePtr      createDBConnection()        const;
                virtual libutil::infrastructure::parameter::IParameterGatewayPtr            createParameterGateway()    const;
                
                virtual void                                                                doInjectInfrastructureSetupComponents() const;
				 virtual void																doInjectApplComponentManagerComponents() const;
				                
                virtual libutil::infrastructure::login::ILoginPtr                           getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const;

                ////////////////////////////////////////////////////////////////////////////////////////////////
                // </creation_section>
                ////////////////////////////////////////////////////////////////////////////////////////////////
            private:
                InfrastructureCompMgr( const InfrastructureCompMgr& );
                InfrastructureCompMgr& operator=( const InfrastructureCompMgr& );

                basar::I18nString                                                               getLanguageCode()   const;
                libutil::infrastructure::i18n::LanguageFileLoader::LanguageDirectoryCollection  getLanguageDirs()   const;
				infrastructure::mail::IMailAlertPtr												getMailAlert()		const;
				infrastructure::mail::IMailParameterProxyPtr									getMailParameterProxy() const;
				libcsc::persistence::ConnectionPtr												getCscDbConnection() const;

				mutable infrastructure::mail::IMailParameterProxyPtr							m_MailParameterProxy;
				mutable libcsc::persistence::ConnectionPtr										m_DbConnection;
				
				
        };
    } // namespace componentManager
} // namespace ibtorderimport

#endif //GUARD_IBTORDERIMPORT_COMPONENTMANAGER_IBTORDERIMPORTINFRASTRUCTURECOMPMGR_H
