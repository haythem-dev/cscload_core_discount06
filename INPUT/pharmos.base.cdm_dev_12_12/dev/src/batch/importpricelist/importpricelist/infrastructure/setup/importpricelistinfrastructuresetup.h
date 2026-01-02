//--------------------------------------------------------------------------------------------------//
/*! \file       
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       12.06.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IMPORTPRICELIST_INFRASTRUCTURE_SETUP_IMPORTPRICELISTINFRASTRUCTURESETUP_H
#define GUARD_IMPORTPRICELIST_INFRASTRUCTURE_SETUP_IMPORTPRICELISTINFRASTRUCTURESETUP_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <libutil/infrastructurecomponent.h>
#include "infrastructure/setup/iimportpricelistlogingetterptr.h"

//--------------------------------------------------------------------------------------------------//
// namespace section
//--------------------------------------------------------------------------------------------------//
namespace importpricelist
{
    namespace infrastructure
    {
        namespace setup
        {
            class IMPORTPRICELISTInfrastructureSetup : public libutil::infrastructure::InfrastructureSetupBase
            {
                public:
                    IMPORTPRICELISTInfrastructureSetup();
	                virtual ~IMPORTPRICELISTInfrastructureSetup();
        	    
                    void injectLoginGetter( IIMPORTPRICELISTLoginGetterConstPtr );

                protected:
                    virtual void    doInit();
	                virtual void    doShutdown();
        	    
                private:
                    ////////////////////////////////
                    // methods
                    ////////////////////////////////
                    IMPORTPRICELISTInfrastructureSetup( const IMPORTPRICELISTInfrastructureSetup& r );
	                IMPORTPRICELISTInfrastructureSetup& operator=( const IMPORTPRICELISTInfrastructureSetup& r );

                    void login();
                    void prepareLogin();

                    ////////////////////////////////
                    // variables
                    ////////////////////////////////
                    IIMPORTPRICELISTLoginGetterConstPtr m_IMPORTPRICELISTLoginGetter;
            };
        }
    }
}

#endif
