//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   08.07.2013
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_IBTRELEVANTCALCULATOR_COMPONENTMANAGER_IBTRELEVANTCALCULATORINFRASTRUCTURECOMPMGR_H
#define GUARD_IBTRELEVANTCALCULATOR_COMPONENTMANAGER_IBTRELEVANTCALCULATORINFRASTRUCTURECOMPMGR_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include <libutil/cmdline.h>

#include "ibtrelevantcalculator/ibtrelevantcalculator_definitions.h"
#include "loggerpool/ibtrelevantcalculator_loggerpool.h"
#include "ibtrelevantcalculatorapplcompmgr.h"
#include "infrastructure/cmdline/ibtrelevantcalculatorcmdlineevaluator.h"
#include "infrastructure/setup/iibtrelevantcalculatorlogingetter.h"
#include "infrastructure/setup/ibtrelevantcalculatorinfrastructuresetup.h"
#include "infrastructure/mail/imailparameterproxyptr.h"

// libutil
#include <boost/enable_shared_from_this.hpp>

//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace componentManager
    {
        //----------------------------------------------------------------------------//
        // class declaration setcion
        //----------------------------------------------------------------------------//
        class InfrastructureCompMgr :
            public libutil::componentManager::InfrastructureCompMgrBase< ibtrelevantcalculator::componentManager::ApplCompMgr,
                                                                         ibtrelevantcalculator::infrastructure::cmdLine::IBTRELEVANTCALCULATORCmdLineEvaluator, 
                                                                         ibtrelevantcalculator::infrastructure::setup::IBTRELEVANTCALCULATORInfrastructureSetup >,
            public infrastructure::setup::IIBTRELEVANTCALCULATORLoginGetter,
            public boost::enable_shared_from_this< InfrastructureCompMgr >
        {
            public:
                InfrastructureCompMgr( int argc, char** argv );
                ~InfrastructureCompMgr();

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

				mutable infrastructure::mail::IMailParameterProxyPtr							m_MailParameterProxy;
				
        };
    } // namespace componentManager
} // namespace ibtrelevantcalculator

#endif //GUARD_IBTRELEVANTCALCULATOR_COMPONENTMANAGER_IBTRELEVANTCALCULATORINFRASTRUCTURECOMPMGR_H
