//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   08.07.2013
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_LONGTERMLACKLOADER_COMPONENTMANAGER_LONGTERMLACKLOADERINFRASTRUCTURECOMPMGR_H
#define GUARD_LONGTERMLACKLOADER_COMPONENTMANAGER_LONGTERMLACKLOADERINFRASTRUCTURECOMPMGR_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include <libutil/cmdline.h>

#include "login/login_definitions.h"
#include "longtermlackloader/longtermlackloader_definitions.h"
#include "loggerpool/longtermlackloader_loggerpool.h"
#include "longtermlackloaderapplcompmgr.h"
#include "cmdline/longtermlackloadercmdlineevaluator.h"
#include "cmdline/longtermlackloadercmdlineoptioncollection.h"
#include "infrastructure/setup/ilongtermlackloaderdbconnectiongetter.h"
#include "infrastructure/setup/longtermlackloaderinfrastructuresetup.h"
#include "infrastructure/setup/ilongtermlackloaderlogingetter.h"

#include <boost/enable_shared_from_this.hpp>

//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace componentManager
    {
        //----------------------------------------------------------------------------//
        // class declaration setcion
        //----------------------------------------------------------------------------//
        class InfrastructureCompMgr :
            public libutil::componentManager::InfrastructureCompMgrBase< longtermlackloader::componentManager::ApplCompMgr,
                                                                         longtermlackloader::infrastructure::cmdLine::LONGTERMLACKLOADERCmdLineEvaluator, 
                                                                         longtermlackloader::infrastructure::setup::LONGTERMLACKLOADERInfrastructureSetup >,
			                                                             public infrastructure::setup::ILongTermLackLoaderLoginGetter,
                                                                         public boost::enable_shared_from_this< InfrastructureCompMgr >
        {
            public:
                InfrastructureCompMgr( int argc, char** argv );
                ~InfrastructureCompMgr();

            protected:
                ////////////////////////////////////////////////////////////////////////////////////////////////
                // <creation_section>
                ////////////////////////////////////////////////////////////////////////////////////////////////
                virtual libutil::infrastructure::IQApplicationPtr                           createQApplication()                    const;
                virtual libutil::infrastructure::login::ILoginPtr                           createLogin()                           const;
                virtual libutil::infrastructure::user::IUserPtr                             createUser()                            const;
                virtual libutil::infrastructure::i18n::ILanguageFileLoaderPtr               createLanguageFileLoader()              const;
                virtual libutil::infrastructure::db::dbConnection::DBConnectionBasePtr      createDBConnection()                    const;
                virtual libutil::infrastructure::parameter::IParameterGatewayPtr            createParameterGateway()                const;
                //virtual libutil::misc::ConstClassInfoPtr                                    createClassInfo()           const;
                virtual void                                                                doInjectInfrastructureSetupComponents() const;
                virtual libutil::infrastructure::parameter::IParameterGatewayPtr            doGetDBParameterGateway()	            const;
				////////////////////////////////////////////////////////////////////////////////////////////////
                // </creation_section>
                ////////////////////////////////////////////////////////////////////////////////////////////////


				//virtual libutil::infrastructure::db::dbConnection::IDBConnectionPtr getDBConnection( libutil::infrastructure::db::dbConnection::DBServerInfo & ) const;
                virtual libutil::infrastructure::login::ILoginPtr getNonInteractiveLogin(const libutil::infrastructure::login::UserLoginData&) const;
                
            private:
                InfrastructureCompMgr( const InfrastructureCompMgr& );
                InfrastructureCompMgr& operator=( const InfrastructureCompMgr& );

                libutil::infrastructure::login::UserLoginData                                   getLoginData()      const;
                basar::I18nString                                                               getLanguageCode()   const;
                libutil::infrastructure::i18n::LanguageFileLoader::LanguageDirectoryCollection  getLanguageDirs()   const;
			
			private:
                ////////////////////////////////////////////////////////////////////////////////////////////////
                // private member section
                ////////////////////////////////////////////////////////////////////////////////////////////////
				//mutable libutil::infrastructure::db::dbConnection::IDBConnectionPtr				m_DBConnection;
        };
    } // namespace componentManager
} // namespace longtermlackloader

#endif //GUARD_LONGTERMLACKLOADER_COMPONENTMANAGER_LONGTERMLACKLOADERINFRASTRUCTURECOMPMGR_H
