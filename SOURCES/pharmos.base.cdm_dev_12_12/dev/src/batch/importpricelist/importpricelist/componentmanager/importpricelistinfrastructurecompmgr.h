//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   25.08.2021
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_IMPORTPRICELIST_COMPONENTMANAGER_IMPORTPRICELISTINFRASTRUCTURECOMPMGR_H
#define GUARD_IMPORTPRICELIST_COMPONENTMANAGER_IMPORTPRICELISTINFRASTRUCTURECOMPMGR_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include <libutil/cmdline.h>

#include "importpricelist/importpricelist_definitions.h"
#include "loggerpool/importpricelist_loggerpool.h"
#include "importpricelistapplcompmgr.h"
#include "infrastructure/cmdline/importpricelistcmdlineevaluator.h"
#include "infrastructure/setup/iimportpricelistlogingetter.h"
#include "infrastructure/setup/importpricelistinfrastructuresetup.h"

// libutil
#include <boost/enable_shared_from_this.hpp>

//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace importpricelist
{
    namespace componentManager
    {
        //----------------------------------------------------------------------------//
        // class declaration setcion
        //----------------------------------------------------------------------------//
        class InfrastructureCompMgr :
            public libutil::componentManager::InfrastructureCompMgrBase< importpricelist::componentManager::ApplCompMgr,
			                                                             importpricelist::infrastructure::cmdLine::IMPORTPRICELISTCmdLineEvaluator,
			                                                             importpricelist::infrastructure::setup::IMPORTPRICELISTInfrastructureSetup >,
            public infrastructure::setup::IIMPORTPRICELISTLoginGetter,
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
} // namespace importpricelist

#endif //GUARD_IMPORTPRICELIST_COMPONENTMANAGER_IMPORTPRICELISTINFRASTRUCTURECOMPMGR_H
