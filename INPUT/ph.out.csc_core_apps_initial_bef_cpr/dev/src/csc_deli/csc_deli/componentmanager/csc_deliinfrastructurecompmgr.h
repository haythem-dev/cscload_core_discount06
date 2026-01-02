#ifndef GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIINFRASTRUCTURECOMPMGR_H
#define GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIINFRASTRUCTURECOMPMGR_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include <libutil/cmdline.h>

#include "csc_deli/csc_deli_definitions.h"
#include "loggerpool/libcsc_deli_loggerpool.h"
#include "csc_deliapplcompmgr.h"
#include "infrastructure/cmdline/csc_delicmdlineevaluator.h"
#include "infrastructure/cmdline/csc_delicmdlineoptioncollection.h"
#include "infrastructure/setup/icsc_delilogingetter.h"
#include "infrastructure/setup/csc_deliinfrastructuresetup.h"

#include <infrastructure/connectionpool/iconnectionpoolptr.h>
#include <infrastructure/connectionpool/idbconnectionfactory.h>

// libutil
#include <boost/enable_shared_from_this.hpp>

//----------------------------------------------------------------------------//
// namespace setcion
//----------------------------------------------------------------------------//
namespace csc_deli
{
namespace componentManager
{
    //----------------------------------------------------------------------------//
    // class declaration setcion
    //----------------------------------------------------------------------------//
    class InfrastructureCompMgr :
        public libutil::componentManager::InfrastructureCompMgrBase< ApplCompMgr, infrastructure::cmdLine::CSC_DELICmdLineEvaluator,
                                                                     infrastructure::setup::CSC_DELIInfrastructureSetup >,
        public infrastructure::setup::ICSC_DELILoginGetter,
        public libcsc_deli::infrastructure::connectionPool::IDBConnectionFactory,
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
            void                                                                        doInjectApplComponentManagerComponents() const;

            virtual libutil::infrastructure::login::ILoginPtr                           getNonInteractiveLogin( const libutil::infrastructure::login::UserLoginData& ) const;

            ////////////////////////////////////////////////////////////////////////////////////////////////
            // </creation_section>
            ////////////////////////////////////////////////////////////////////////////////////////////////
        private:
            InfrastructureCompMgr( const InfrastructureCompMgr& );
            InfrastructureCompMgr& operator=( const InfrastructureCompMgr& );

            libutil::infrastructure::login::UserLoginData                                   getLoginData()                               const;
            basar::I18nString                                                               getLanguageCode()                            const;
            libutil::infrastructure::i18n::LanguageFileLoader::LanguageDirectoryCollection  getLanguageDirs()                            const;
            libutil::infrastructure::parameter::IParameterGatewayPtr                        getDBParameterGateway( basar::Int16 areaId ) const;
            libutil::infrastructure::db::dbConnection::IDBConnectionPtr                     getDBConnection( basar::Int16 areaId )       const;
            libcsc_deli::infrastructure::connectionPool::IConnectionPoolPtr                 getDBConnectionPool()                        const;

        private:
            mutable libcsc_deli::infrastructure::connectionPool::IConnectionPoolPtr         m_DBConnectionPool;
    };
} // namespace componentManager
} // namespace csc_deli

#endif //GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIINFRASTRUCTURECOMPMGR_H
