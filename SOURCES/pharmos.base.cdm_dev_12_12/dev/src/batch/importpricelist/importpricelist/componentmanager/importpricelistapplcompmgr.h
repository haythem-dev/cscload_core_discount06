//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   25.08.2021
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_IMPORTPRICELIST_COMPONENTMANAGER_IMPORTPRICELISTAPPLCOMPMGR_H
#define GUARD_IMPORTPRICELIST_COMPONENTMANAGER_IMPORTPRICELISTAPPLCOMPMGR_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/irunnableptr.h>
#include "infrastructure/cmdline/importpricelistcmdlineevaluator.h"

// dm
#include <domainmodule/articlecodes/articlecodesdm.h>
#include <domainmodule/pricedata/pricedatadm.h>
#include <domainmodule/pricelist2pharmacygroup/pricelist2pharmacygroupdm.h>
#include <domainmodule/pricelistproc/pricelistprocdm.h>

// uc
#include "iusecasegetter.h"

// libutil
#include <libutil/applcomponent.h>
#include <boost/enable_shared_from_this.hpp>
#include <libutil/accessor.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class ConnectionRef;
        }
    }
}

namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// class declaration setcion
//-------------------------------------------------------------------------------------------------//
namespace importpricelist
{
    namespace componentManager
    {
        class ApplCompMgr : public libutil::componentManager::ApplCompMgrBase,
                            public IUseCaseGetter,
                            public boost::enable_shared_from_this< ApplCompMgr >
        {
            public:
                ApplCompMgr();
                virtual ~ApplCompMgr();

				void setCmdLineArguments( const infrastructure::cmdLine::AppArgs& appArgs );

                /////////////////////////////////////////////////////////////////////
                // use case
                /////////////////////////////////////////////////////////////////////
                libutil::useCase::IRunnablePtr                                          getMainUC();
                
            protected:
                virtual void                                                            doClear();

                /////////////////////////////////////////////////////////////////////
                // domain modules
                /////////////////////////////////////////////////////////////////////
				domMod::pricedata::PriceDataDMPtr								        getPriceDataDM();
				libutil::infrastructure::accessor::IAccessorPtr                         getPriceDataAccessor();
				domMod::pricelist2pharmacygroup::PriceList2PharmacyGroupDMPtr			getPriceList2PharmacyGroupDM();
				libutil::infrastructure::accessor::IAccessorPtr                         getPriceList2PharmacyGroupAccessor();
				domMod::pricelistproc::PriceListProcDMPtr					            getPriceListProcDM();
				libutil::infrastructure::accessor::IAccessorPtr                         getPriceListProcAccessor();
				domMod::articlecodes::ArticleCodesDMPtr						            getArticleCodesDM();
				libutil::infrastructure::accessor::IAccessorPtr                         getArticleCodesAccessor();

				/////////////////////////////////////////////////////////////////////
				// accessors
				/////////////////////////////////////////////////////////////////////
//				libutil::infrastructure::accessor::IAccessorPtr							getExportExclusionParameterAccessor();
           
                /////////////////////////////////////////////////////////////////////
                // db connection
                /////////////////////////////////////////////////////////////////////
                libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr   getDBConnection();

            private:
                ApplCompMgr( const ApplCompMgr& );
                ApplCompMgr& operator=( const ApplCompMgr& );
                
            private:
                ///////////////////////////////////////////////////////////////////
                // member variables
                ///////////////////////////////////////////////////////////////////
                const log4cplus::Logger&                                                m_Logger;

				importpricelist::infrastructure::cmdLine::AppArgs				        m_AppArgs;
        };

    } // end namnespace componentManager
} // end namnespace importpricelist

#endif
