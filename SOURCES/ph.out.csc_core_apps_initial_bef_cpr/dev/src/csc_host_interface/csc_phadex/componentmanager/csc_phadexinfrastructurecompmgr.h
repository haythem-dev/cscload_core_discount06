//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   08.07.2013
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_CSC_PHADEX_COMPONENTMANAGER_CSC_PHADEXINFRASTRUCTURECOMPMGR_H
#define GUARD_CSC_PHADEX_COMPONENTMANAGER_CSC_PHADEXINFRASTRUCTURECOMPMGR_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include <libutil/cmdline.h>

#include <infrastructure/login/login_definitions.h>
#include <loggerpool/csc_phadex_loggerpool.h>
#include <componentmanager/csc_phadexapplcompmgr.h>
#include <infrastructure/cmdline/csc_phadexcmdlineevaluator.h>
#include <infrastructure/cmdline/csc_phadexcmdlineoptioncollection.h>
#include <infrastructure/setup/icsc_phadexlogingetter.h>
#include <infrastructure/setup/csc_phadexinfrastructuresetup.h>

// libutil
#include <boost/enable_shared_from_this.hpp>

//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace csc_phadex
{
    namespace componentManager
    {
        //----------------------------------------------------------------------------//
        // class declaration setcion
        //----------------------------------------------------------------------------//
        class InfrastructureCompMgr :
            public libutil::componentManager::InfrastructureCompMgrBase< csc_phadex::componentManager::ApplCompMgr,
                                                                         csc_phadex::infrastructure::cmdLine::CscPhadexCmdLineEvaluator, 
                                                                         csc_phadex::infrastructure::setup::CscPhadexInfrastructureSetup >,
            public infrastructure::setup::ICscPhadexLoginGetter,
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
                virtual libutil::infrastructure::parameter::IParameterGatewayPtr            doGetDBParameterGateway() const;

                //virtual libutil::infrastructure::login::ILoginPtr                           getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const;

                ////////////////////////////////////////////////////////////////////////////////////////////////
                // </creation_section>
                ////////////////////////////////////////////////////////////////////////////////////////////////
            private:
                InfrastructureCompMgr( const InfrastructureCompMgr& );
                InfrastructureCompMgr& operator=( const InfrastructureCompMgr& );

                //libutil::infrastructure::login::UserLoginData                                   getLoginData()      const;
                basar::I18nString                                                               getLanguageCode()   const;
                libutil::infrastructure::i18n::LanguageFileLoader::LanguageDirectoryCollection  getLanguageDirs()   const;
        };
    } // namespace componentManager
} // namespace csc_phadex

#endif //GUARD_CSC_PHADEX_COMPONENTMANAGER_CSC_PHADEXINFRASTRUCTURECOMPMGR_H
