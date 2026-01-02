#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_MAINWAREHOUSEARTICLESRELEVANTCALCULATORINFRASTRUCTURECOMPMGR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_MAINWAREHOUSEARTICLESRELEVANTCALCULATORINFRASTRUCTURECOMPMGR_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include <libutil/cmdline.h>

#include "infrastructure/login/login_definitions.h"
#include "mainwarehousearticlesrelevantcalculator/mainwarehousearticlesrelevantcalculator_definitions.h"
#include "loggerpool/mainwarehousearticlesrelevantcalculator_loggerpool.h"
#include "mainwarehousearticlesrelevantcalculatorapplcompmgr.h"
#include "infrastructure/cmdline/mainwarehousearticlesrelevantcalculatorcmdlineevaluator.h"
#include "infrastructure/cmdline/mainwarehousearticlesrelevantcalculatorcmdlineoptioncollection.h"
#include "infrastructure/setup/imainwarehousearticlesrelevantcalculatorlogingetter.h"
#include "infrastructure/setup/mainwarehousearticlesrelevantcalculatorinfrastructuresetup.h"

// libutil
#include <boost/enable_shared_from_this.hpp>

//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
namespace componentManager
{
    //----------------------------------------------------------------------------//
    // class declaration setcion
    //----------------------------------------------------------------------------//
    class InfrastructureCompMgr :
        public libutil::componentManager::InfrastructureCompMgrBase< mainwarehousearticlesrelevantcalculator::componentManager::ApplCompMgr,
                                                                     mainwarehousearticlesrelevantcalculator::infrastructure::cmdLine::MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator, 
                                                                     mainwarehousearticlesrelevantcalculator::infrastructure::setup::MAINWAREHOUSEARTICLESRELEVANTCALCULATORInfrastructureSetup >,
        public infrastructure::setup::IMAINWAREHOUSEARTICLESRELEVANTCALCULATORLoginGetter,
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
            virtual boost::shared_ptr< const libutil::misc::ClassInfo >                 createClassInfo()           const;

            virtual void                                                                doInjectInfrastructureSetupComponents() const;

            virtual libutil::infrastructure::login::ILoginPtr                           getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const;

            ////////////////////////////////////////////////////////////////////////////////////////////////
            // </creation_section>
            ////////////////////////////////////////////////////////////////////////////////////////////////
        private:
            InfrastructureCompMgr( const InfrastructureCompMgr& );
            InfrastructureCompMgr& operator=( const InfrastructureCompMgr& );

            basar::I18nString                                                               getLanguageCode()   const;
            libutil::infrastructure::i18n::LanguageFileLoader::LanguageDirectoryCollection  getLanguageDirs()   const;
    };
} // namespace componentManager
} // namespace mainwarehousearticlesrelevantcalculator

#endif //GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_MAINWAREHOUSEARTICLESRELEVANTCALCULATORINFRASTRUCTURECOMPMGR_H
