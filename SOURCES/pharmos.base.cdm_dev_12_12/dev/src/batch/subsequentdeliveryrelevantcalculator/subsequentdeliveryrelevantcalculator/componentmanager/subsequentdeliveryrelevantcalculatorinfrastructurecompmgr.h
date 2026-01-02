//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   14.10.2022
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_INFRASTRUCTURECOMPMGR_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_INFRASTRUCTURECOMPMGR_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include <libutil/cmdline.h>

#include "loggerpool/subsequentdeliveryrelevantcalculator_loggerpool.h"
#include "subsequentdeliveryrelevantcalculatorapplcompmgr.h"
#include "infrastructure/cmdline/subsequentdeliveryrelevantcalculatorcmdlineevaluator.h"
#include "infrastructure/setup/isubsequentdeliveryrelevantcalculatorlogingetter.h"
#include "infrastructure/setup/subsequentdeliveryrelevantcalculatorinfrastructuresetup.h"

// libutil
#include <boost/enable_shared_from_this.hpp>

//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
    namespace componentManager
    {
        //----------------------------------------------------------------------------//
        // class declaration setcion
        //----------------------------------------------------------------------------//
        class InfrastructureCompMgr :
            public libutil::componentManager::InfrastructureCompMgrBase< subsequentdeliveryrelevantcalculator::componentManager::ApplCompMgr,
			                                                             subsequentdeliveryrelevantcalculator::infrastructure::cmdLine::SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator,
			                                                             subsequentdeliveryrelevantcalculator::infrastructure::setup::SUBSEQUENTDELIVERYRELEVANTCALCULATORInfrastructureSetup >,
            public infrastructure::setup::ISUBSEQUENTDELIVERYRELEVANTCALCULATORLoginGetter,
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
        };
    } // namespace componentManager
} // namespace subsequentdeliveryrelevantcalculator

#endif //GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_INFRASTRUCTURECOMPMGR_H
