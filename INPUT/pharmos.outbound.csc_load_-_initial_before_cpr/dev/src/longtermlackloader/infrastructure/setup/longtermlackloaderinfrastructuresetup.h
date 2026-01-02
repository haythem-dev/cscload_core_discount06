//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       12.06.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_SETUP_LONGTERMLACKLOADERINFRASTRUCTURESETUP_H
#define GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_SETUP_LONGTERMLACKLOADERINFRASTRUCTURESETUP_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include "infrastructure/setup/ilongtermlackloaderdbconnectiongetterconstptr.h"
#include "infrastructure/setup/ilongtermlackloaderlogingetterptr.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace setup
        {
            class LONGTERMLACKLOADERInfrastructureSetup : public libutil::infrastructure::InfrastructureSetupBase
            {
                public:
                    LONGTERMLACKLOADERInfrastructureSetup();
                    virtual ~LONGTERMLACKLOADERInfrastructureSetup();
                
                    //void injectDBConnectionGetter( IDBConnectionGetterConstPtr );
                    void injectLoginGetter( IILongTermLackLoaderLoginGetterPtr );

                protected:
                    virtual void    doInit();
                    virtual void    doShutdown();
                
                private:
                    ////////////////////////////////
                    // methods
                    ////////////////////////////////
                    LONGTERMLACKLOADERInfrastructureSetup( const LONGTERMLACKLOADERInfrastructureSetup& r );
                    LONGTERMLACKLOADERInfrastructureSetup& operator=( const LONGTERMLACKLOADERInfrastructureSetup& r );

                    void login();
                    void prepareLogin();

                    /*void					prepareDBConnection();
                    IDBConnectionGetterConstPtr	getDBConnectionGetter();*/

                    ////////////////////////////////
                    // variables
                    ////////////////////////////////
                    //IDBConnectionGetterConstPtr m_DBConnectionGetter;
                    IILongTermLackLoaderLoginGetterPtr m_LongTermLackLoaderLoginGetter;
            };
        }
    }
}

#endif
