//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   14.10.2022
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_APPLCOMPMGR_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_APPLCOMPMGR_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/irunnableptr.h>
#include "infrastructure/cmdline/subsequentdeliveryrelevantcalculatorcmdlineevaluator.h"

// dm
#include <domainmodule/article/articledm.h>
#include <domainmodule/deliveryparam/deliveryparamdm.h>
#include "domainmodule/subsequentdeliveryconfig/subsequentdeliveryconfigdm.h"

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
namespace subsequentdeliveryrelevantcalculator
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
                domMod::article::ArticleDMPtr						                    getArticleDM();
                libutil::infrastructure::accessor::IAccessorPtr                         getArticleAccessor();
                domMod::deliveryparam::DeliveryParamDMPtr			                    getDeliveryParamDM();
                libutil::infrastructure::accessor::IAccessorPtr		                    getDeliveryParamAccessor();
                domMod::subsequentdeliveryconfig::SubsequentDeliveryConfigDMPtr         getSubsequentDeliveryConfigDM();
                libutil::infrastructure::accessor::IAccessorPtr                         getSubsequentDeliveryConfigAccessor();

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

				infrastructure::cmdLine::AppArgs                                        m_AppArgs;
        };

    } // end namespace componentManager
} // end namespace subsequentdeliveryrelevantcalculator

#endif
