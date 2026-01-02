#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_LIBCSC_DELIAPPLCOMPMGR_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_LIBCSC_DELIAPPLCOMPMGR_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "icustomerinvoicegetter.h"

// DM
#include "domainmodule/cremamail/icremamailcleanerptr.h"
#include "domainmodule/customer/icustomerfinderptr.h"
#include "domainmodule/customerinvoice/icustomerinvoiceflagptr.h"
#include "domainmodule/customerinvoice/icustomerinvoicingcollectionptr.h"
#include "domainmodule/customerorder/icustomerordercollectionfinderptr.h"
#include "domainmodule/debtlimit/idebtlimitcollectionptr.h"
#include "domainmodule/debtlimit/idebtlimitimporterptr.h"
#include "domainmodule/debtlimit/idebtlimitmailprocessorptr.h"
#include "domainmodule/sap/isapcollectionreaderptr.h"
#include "domainmodule/sap/isapcollectionwriterptr.h"
#include "domainmodule/turnover/icustomerturnovercollectionloaderptr.h"
#include "domainmodule/turnover/icustomerturnoverexporterptr.h"
#include "domainmodule/turnover/iturnoverfinderptr.h"

// connectionpool
#include "infrastructure/connectionpool/iconnectionpoolgetterptr.h"

// config
#include "infrastructure/parameter/iaccparameterptr.h"

// Factory
#include "icustomerinvoiceconnectedfactoryptr.h"
#include "idebtlimitdisconnectedfactoryptr.h"

// others
#include <boost/enable_shared_from_this.hpp>

//lib(s)
#include <libutil/accessor.h>
#include <libutil/dbtransaction.h>
#include <libutil/dbconnection.h>
#include <libutil/validator.h>

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
// class declaration section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace componentManager
{
    class ApplCompMgr : public libutil::infrastructure::db::dbTransaction::IDBTransactionFactory,
                        public ICustomerInvoiceGetter,
                        public boost::enable_shared_from_this< ApplCompMgr >
    {
        public:
            ApplCompMgr();
            virtual ~ApplCompMgr();

            void                                                                    injectDBConnectionPool( infrastructure::connectionPool::IConnectionPoolGetterPtr );
            void                                                                    injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr );
            void                                                                    setSession( libutil::infrastructure::session::ISessionPtr );

            /////////////////////////////////////////////////////////////////////
            // domain modules
            /////////////////////////////////////////////////////////////////////
            domMod::cremaMail::ICremaMailCleanerPtr                                 getCremaMailCleaner();
            domMod::customer::ICustomerFinderPtr                                    getCustomerFinder();
            domMod::customerInvoice::ICustomerInvoicePtr                            getCustomerInvoice();
            domMod::customerInvoice::ICustomerInvoiceFlagPtr                        getCustomerInvoiceFlag();
            domMod::customerInvoice::ICustomerInvoicingCollectionPtr                getCustomerInvoicingCollection();
            domMod::customerOrder::ICustomerOrderCollectionFinderPtr                getCustomerOrderCollectionFinder();
            domMod::debtLimit::IDebtLimitCollectionPtr                              getDebtLimitCollection();
            domMod::debtLimit::IDebtLimitImporterPtr                                getDebtLimitImporter();
            domMod::debtLimit::IDebtLimitMailProcessorPtr                           getDebtLimitMailProcessor();
            domMod::sap::ISAPCollectionReaderPtr                                    getSAPBalanceCollection();
            domMod::sap::ISAPCollectionWriterPtr                                    getSAPCustomerTurnoverCollection();
            domMod::sap::ISAPCollectionReaderPtr                                    getSAPLimitCollection();
            domMod::turnover::ICustomerTurnoverCollectionLoaderPtr                  getCustomerTurnoverCollectionLoader();
            domMod::turnover::ICustomerTurnoverExporterPtr                          getCustomerTurnoverExporter();
            domMod::turnover::ITurnoverFinderPtr                                    getTurnoverFinder();

            /////////////////////////////////////////////////////////////////////
            // factories
            /////////////////////////////////////////////////////////////////////
            ICustomerInvoiceConnectedFactoryPtr                                     getCustomerInvoiceConnectedFactory();
            IDebtLimitDisconnectedFactoryPtr                                        getDebtLimitDisconnectedFactory();

        private:
            ApplCompMgr( const ApplCompMgr& );
            ApplCompMgr& operator=( const ApplCompMgr& );

            /////////////////////////////////////////////////////////////////////
            // accessors
            /////////////////////////////////////////////////////////////////////
            libutil::infrastructure::accessor::IAccessorPtr                         getCremaMailCleanerAccessor();
            libutil::infrastructure::accessor::IAccessorPtr                         getCustomerAccessor();
            libutil::infrastructure::accessor::IAccessorPtr                         getCustomerInvoiceAccessor();
            libutil::infrastructure::accessor::IAccessorPtr                         getCustomerInvoiceCollectionAccessor();
            libutil::infrastructure::accessor::IAccessorPtr                         getCustomerInvoicingCollectionAccessor();
            libutil::infrastructure::accessor::IAccessorPtr                         getCustomerOrderCollectionAccessor();
            libutil::infrastructure::accessor::IAccessorPtr                         getCustomerTurnoverCollectionAccessor();
            libutil::infrastructure::accessor::IAccessorPtr                         getDebtLimitCollectionAccessor();
            libutil::infrastructure::accessor::IAccessorPtr                         getSAPBalanceCollectionAccessor();
            libutil::infrastructure::accessor::IAccessorPtr                         getSAPLimitCollectionAccessor();
            libutil::infrastructure::accessor::IAccessorPtr                         getSAPCustomerTurnoverCollectionAccessor();

            /////////////////////////////////////////////////////////////////////
            // configuration
            /////////////////////////////////////////////////////////////////////
            libutil::infrastructure::session::ISessionPtr                           getSession() const;
            infrastructure::parameter::IACCParameterPtr                             getAccParameter();
            libutil::infrastructure::parameter::IParameterGatewayPtr                getParameterGateway();

            /////////////////////////////////////////////////////////////////////
            // others
            /////////////////////////////////////////////////////////////////////
            virtual libutil::infrastructure::db::dbTransaction::IDBTransactionPtr   createDBTransaction();
            
            /////////////////////////////////////////////////////////////////////
            // db connection
            /////////////////////////////////////////////////////////////////////
            infrastructure::connectionPool::IConnectionPoolGetterPtr                getDBConnectionPool();
            libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr   getDBConnectionDataGetter();
            basar::db::aspect::ConnectionRef                                        getBasarDBConnection();


            ///////////////////////////////////////////////////////////////////
            // member variables
            ///////////////////////////////////////////////////////////////////
            const log4cplus::Logger&                                                m_Logger;
            infrastructure::connectionPool::IConnectionPoolGetterPtr                m_DBConnectionPool;
            libutil::infrastructure::session::ISessionPtr                           m_Session;
            libutil::infrastructure::parameter::IParameterGatewayPtr                m_ParameterGateway;
    };
} // end namnespace componentManager
} // end namnespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_COMPONENTMANAGER_LIBCSC_DELIAPPLCOMPMGR_H

