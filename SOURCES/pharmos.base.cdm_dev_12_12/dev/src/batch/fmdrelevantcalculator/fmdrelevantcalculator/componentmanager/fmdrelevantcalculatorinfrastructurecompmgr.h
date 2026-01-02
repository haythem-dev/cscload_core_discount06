//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   08.07.2013
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_FMDRELEVANTCALCULATORINFRASTRUCTURECOMPMGR_H
#define GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_FMDRELEVANTCALCULATORINFRASTRUCTURECOMPMGR_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include <libutil/cmdline.h>

#include "fmdrelevantcalculator/fmdrelevantcalculator_definitions.h"
#include "loggerpool/fmdrelevantcalculator_loggerpool.h"
#include "fmdrelevantcalculatorapplcompmgr.h"
#include "infrastructure/cmdline/fmdrelevantcalculatorcmdlineevaluator.h"
#include "infrastructure/setup/ifmdrelevantcalculatorlogingetter.h"
#include "infrastructure/setup/fmdrelevantcalculatorinfrastructuresetup.h"
#include "infrastructure/mail/imailparameterproxyptr.h"

// libutil
#include <boost/enable_shared_from_this.hpp>

//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    namespace componentManager
    {
        //----------------------------------------------------------------------------//
        // class declaration setcion
        //----------------------------------------------------------------------------//
        class InfrastructureCompMgr :
            public libutil::componentManager::InfrastructureCompMgrBase< fmdrelevantcalculator::componentManager::ApplCompMgr,
                                                                         fmdrelevantcalculator::infrastructure::cmdLine::FMDRELEVANTCALCULATORCmdLineEvaluator, 
                                                                         fmdrelevantcalculator::infrastructure::setup::FMDRELEVANTCALCULATORInfrastructureSetup >,
            public infrastructure::setup::IFMDRELEVANTCALCULATORLoginGetter,
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
} // namespace fmdrelevantcalculator

#endif //GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_FMDRELEVANTCALCULATORINFRASTRUCTURECOMPMGR_H
