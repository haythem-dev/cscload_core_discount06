//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
// global
#include "libcsc_deliapplcompmgr.h"
#include "loggerpool/libcsc_deli_loggerpool.h"

#include "infrastructure/connectionpool/iconnectionpoolgetter.h"

// dm
#include "domainmodule/cremamail/cremamailcleanupdm.h"
#include "domainmodule/cremamail/cremamailcleanupdmptr.h"

#include "domainmodule/customer/customerdm.h"
#include "domainmodule/customer/customerdmptr.h"

#include "domainmodule/customerinvoice/customerinvoicedm.h"
#include "domainmodule/customerinvoice/customerinvoicedmptr.h"
#include "domainmodule/customerinvoice/customerinvoicingcollectiondm.h"
#include "domainmodule/customerinvoice/customerinvoicingcollectiondmptr.h"

#include "domainmodule/customerorder/customerordercollectiondm.h"
#include "domainmodule/customerorder/customerordercollectiondmptr.h"

#include "domainmodule/debtlimit/debtlimitcollectiondm.h"
#include "domainmodule/debtlimit/debtlimitcollectiondmptr.h"
#include "domainmodule/debtlimit/debtlimitdm.h"
#include "domainmodule/debtlimit/debtlimitdmptr.h"
#include "domainmodule/debtlimit/debtlimitimportdm.h"
#include "domainmodule/debtlimit/debtlimitimportdmptr.h"
#include "domainmodule/debtlimit/debtlimitmaildm.h"
#include "domainmodule/debtlimit/debtlimitmaildmptr.h"

#include "domainmodule/sap/sapbalancecollectiondm.h"
#include "domainmodule/sap/sapbalancecollectiondmptr.h"
#include "domainmodule/sap/sapcustomerturnovercollectiondm.h"
#include "domainmodule/sap/sapcustomerturnovercollectiondmptr.h"
#include "domainmodule/sap/saplimitcollectiondm.h"
#include "domainmodule/sap/saplimitcollectiondmptr.h"

#include "domainmodule/turnover/customerturnovercollectiondm.h"
#include "domainmodule/turnover/customerturnovercollectiondmptr.h"
#include "domainmodule/turnover/customerturnoverexportdm.h"
#include "domainmodule/turnover/customerturnoverexportdmptr.h"
#include "domainmodule/turnover/turnoverdm.h"
#include "domainmodule/turnover/turnoverdmptr.h"

// factory
#include "customerinvoiceconnectedfactory.h"
#include "customerinvoiceconnectedfactoryptr.h"

#include "debtlimitdisconnectedfactory.h"
#include "debtlimitdisconnectedfactoryptr.h"

// accessor
#include "infrastructure/accessor/accessordecorator/accessorproxyuniondecorator.h"

#include "infrastructure/accessor/cremamail/cremamailcleanupacc.h"
#include "infrastructure/accessor/cremamail/cremamailcleanupacc_definitions.h"

#include "infrastructure/accessor/customer/customeracc.h"
#include "infrastructure/accessor/customer/customeracc_definitions.h"

#include "infrastructure/accessor/customerinvoice/customerinvoiceacc.h"
#include "infrastructure/accessor/customerinvoice/customerinvoiceacc_definitions.h"
#include "infrastructure/accessor/customerinvoice/customerinvoicecollectionacc.h"
#include "infrastructure/accessor/customerinvoice/customerinvoicecollectionacc_definitions.h"
#include "infrastructure/accessor/customerinvoice/customerinvoicingcollectionacc.h"

#include "infrastructure/accessor/customerorder/customerordercollectionacc.h"
#include "infrastructure/accessor/customerorder/customerordercollectionacc_definitions.h"

#include "infrastructure/accessor/customerturnover/customerturnovercollectionacc.h"
#include "infrastructure/accessor/customerturnover/customerturnovercollectionacc_definitions.h"

#include "infrastructure/accessor/debtlimit/debtlimitcollectionacc.h"
#include "infrastructure/accessor/debtlimit/debtlimitcollectionacc_definitions.h"

#include "infrastructure/accessor/sap/sapbalancecollectionacc.h"
#include "infrastructure/accessor/sap/saplimitcollectionacc.h"
#include "infrastructure/accessor/sap/sapcustomerturnovercollectionacc.h"

// config
#include "infrastructure/parameter/accparameter.h"
#include "infrastructure/parameter/accparameterptr.h"

// libs
#include <libutil/util.h>
#include <libutil/session.h>
#include <infrastructure/db/dbconnection/dbconnectionparametername_definitions.h>

#include <boost/make_shared.hpp>

//----------------------------------------------------------------------------//
// using declaration section
//----------------------------------------------------------------------------//


//----------------------------------------------------------------------------//
// class definition section
//----------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace componentManager
{

    ApplCompMgr::ApplCompMgr()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerCsc_deli() )
    {
        METHODNAME_DEF( ApplCompMgr, ApplCompMgr )
        BLOG_TRACE_METHOD( m_Logger, fun );
    }

    ApplCompMgr::~ApplCompMgr()
    {
        METHODNAME_DEF( ApplCompMgr, ~ApplCompMgr )
        BLOG_TRACE_METHOD( m_Logger, fun );
    }

    void ApplCompMgr::injectDBConnectionPool( infrastructure::connectionPool::IConnectionPoolGetterPtr connectionPool )
    {
        m_DBConnectionPool = connectionPool;
    }

    void ApplCompMgr::injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr parameterGateway )
    {
        m_ParameterGateway = parameterGateway;
    }

    libutil::infrastructure::parameter::IParameterGatewayPtr ApplCompMgr::getParameterGateway()
    {
        CHECK_INSTANCE_EXCEPTION( m_ParameterGateway.get() );
        return m_ParameterGateway;
    }

    void ApplCompMgr::setSession( libutil::infrastructure::session::ISessionPtr session )
    {
        m_Session = session;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // <DM getting>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    domMod::cremaMail::ICremaMailCleanerPtr ApplCompMgr::getCremaMailCleaner()
    {
        domMod::cremaMail::CremaMailCleanupDMPtr dm = boost::make_shared< domMod::cremaMail::CremaMailCleanupDM >();
        dm->injectCremaMailCleanupAccessor( getCremaMailCleanerAccessor() );

        return dm;
    }

    domMod::customer::ICustomerFinderPtr ApplCompMgr::getCustomerFinder()
    {
        domMod::customer::CustomerDMPtr dm = boost::make_shared< domMod::customer::CustomerDM >();
        dm->injectCustomerAccessor( getCustomerAccessor() );

        return dm;
    }

    domMod::customerInvoice::ICustomerInvoicePtr ApplCompMgr::getCustomerInvoice()
    {
        domMod::customerInvoice::CustomerInvoiceDMPtr dm = boost::make_shared< domMod::customerInvoice::CustomerInvoiceDM >();
        dm->injectCustomerInvoiceAccessor( getCustomerInvoiceAccessor() );

        return dm;
    }

    domMod::customerInvoice::ICustomerInvoiceFlagPtr ApplCompMgr::getCustomerInvoiceFlag()
    {
        domMod::customerInvoice::CustomerInvoiceDMPtr dm = boost::dynamic_pointer_cast< domMod::customerInvoice::CustomerInvoiceDM >( getCustomerInvoice() );

        return dm;
    }

    domMod::customerInvoice::ICustomerInvoicingCollectionPtr ApplCompMgr::getCustomerInvoicingCollection()
    {
        domMod::customerInvoice::CustomerInvoicingCollectionDMPtr dm = boost::make_shared< domMod::customerInvoice::CustomerInvoicingCollectionDM >();
        dm->injectCustomerInvoicingCollectionAccessor( getCustomerInvoicingCollectionAccessor() );
        dm->injectCustomerInvoiceFactory( getCustomerInvoiceConnectedFactory() );

        return dm;
    }

    domMod::customerOrder::ICustomerOrderCollectionFinderPtr ApplCompMgr::getCustomerOrderCollectionFinder()
    {
        domMod::customerOrder::CustomerOrderCollectionDMPtr dm = boost::make_shared< domMod::customerOrder::CustomerOrderCollectionDM >();
        dm->injectCustomerOrderCollectionAccessor( getCustomerOrderCollectionAccessor() );

        return dm;
    }

    domMod::turnover::ICustomerTurnoverCollectionLoaderPtr ApplCompMgr::getCustomerTurnoverCollectionLoader()
    {
        domMod::turnover::CustomerTurnoverCollectionDMPtr dm = boost::make_shared< domMod::turnover::CustomerTurnoverCollectionDM >();
        dm->injectCustomerTurnoverCollectionAccessor( getCustomerTurnoverCollectionAccessor() );

        return dm;
    }

    domMod::turnover::ICustomerTurnoverExporterPtr ApplCompMgr::getCustomerTurnoverExporter()
    {
        domMod::turnover::CustomerTurnoverExportDMPtr dm = boost::make_shared< domMod::turnover::CustomerTurnoverExportDM >();
        dm->injectCustomerTurnoverCollection( getCustomerTurnoverCollectionLoader() );
        dm->injectSAPCustomerTurnoverCollection( getSAPCustomerTurnoverCollection() );

        return dm;
    }

    domMod::debtLimit::IDebtLimitCollectionPtr ApplCompMgr::getDebtLimitCollection()
    {
        domMod::debtLimit::DebtLimitCollectionDMPtr dm = boost::make_shared< domMod::debtLimit::DebtLimitCollectionDM >();
        dm->injectDebtLimitCollectionAccessor( getDebtLimitCollectionAccessor() );
        dm->injectDebtLimitDisconnectedFactory( getDebtLimitDisconnectedFactory() );

        return dm;
    }

    domMod::debtLimit::IDebtLimitImporterPtr ApplCompMgr::getDebtLimitImporter()
    {
        domMod::debtLimit::DebtLimitImportDMPtr dm = boost::make_shared< domMod::debtLimit::DebtLimitImportDM >();
        dm->injectCustomerFinder        ( getCustomerFinder()         );
        dm->injectCustomerInvoiceFlag   ( getCustomerInvoiceFlag()    );
        dm->injectDebtLimitCollection   ( getDebtLimitCollection()    );
        dm->injectDebtLimitMailProcessor( getDebtLimitMailProcessor() );
        dm->injectSAPBalanceCollection  ( getSAPBalanceCollection()   );
        dm->injectSAPLimitCollection    ( getSAPLimitCollection()     );
        dm->injectTurnoverFinder        ( getTurnoverFinder()         );

        return dm;
    }

    domMod::debtLimit::IDebtLimitMailProcessorPtr ApplCompMgr::getDebtLimitMailProcessor()
    {
        domMod::debtLimit::DebtLimitMailDMPtr dm = boost::make_shared< domMod::debtLimit::DebtLimitMailDM >();
        dm->injectConnection( getBasarDBConnection().getSqlConnection() );
        dm->injectParameterGateway( getParameterGateway() );
        dm->setSession( getSession() );

        return dm;
    }

    domMod::sap::ISAPCollectionReaderPtr ApplCompMgr::getSAPBalanceCollection()
    {
        domMod::sap::SAPBalanceCollectionDMPtr dm = boost::make_shared< domMod::sap::SAPBalanceCollectionDM >();
        dm->injectSAPBalanceCollectionAccessor( getSAPBalanceCollectionAccessor() );

        return dm;
    }

    domMod::sap::ISAPCollectionWriterPtr ApplCompMgr::getSAPCustomerTurnoverCollection()
    {
        domMod::sap::SAPCustomerTurnoverCollectionDMPtr dm = boost::make_shared< domMod::sap::SAPCustomerTurnoverCollectionDM >();
        dm->injectSAPCustomerTurnoverCollectionAccessor( getSAPCustomerTurnoverCollectionAccessor() );

        return dm;
    }

    domMod::sap::ISAPCollectionReaderPtr ApplCompMgr::getSAPLimitCollection()
    {
        domMod::sap::SAPLimitCollectionDMPtr dm = boost::make_shared< domMod::sap::SAPLimitCollectionDM >();
        dm->injectSAPLimitCollectionAccessor( getSAPLimitCollectionAccessor() );

        return dm;
    }

    domMod::turnover::ITurnoverFinderPtr ApplCompMgr::getTurnoverFinder()
    {
        domMod::turnover::TurnoverDMPtr dm = boost::make_shared< domMod::turnover::TurnoverDM >();
        dm->injectCustomerInvoiceCollectionAccessor( getCustomerInvoiceCollectionAccessor() );
        dm->injectCustomerOrderCollectionFinder( getCustomerOrderCollectionFinder() );

        return dm;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // </DM getting>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // <Factories>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ICustomerInvoiceConnectedFactoryPtr ApplCompMgr::getCustomerInvoiceConnectedFactory()
    {
        CustomerInvoiceConnectedFactoryPtr factory = boost::make_shared< CustomerInvoiceConnectedFactory >();
        factory->injectCustomerInvoiceGetter( shared_from_this() );

        return factory;
    }

    IDebtLimitDisconnectedFactoryPtr ApplCompMgr::getDebtLimitDisconnectedFactory()
    {
        DebtLimitDisconnectedFactoryPtr factory = boost::make_shared< DebtLimitDisconnectedFactory >();
        factory->injectDBConnection( getDBConnectionDataGetter() );

        return factory;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // </Factories>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // <ACC getting>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getCremaMailCleanerAccessor()
    {
        infrastructure::accessor::cremaMail::CleanupSendMailFlagForAmount();
    
        using infrastructure::accessor::AccessorProxyUnionDecorator;
        return boost::make_shared< AccessorProxyUnionDecorator >( infrastructure::accessor::cremaMail::lit::CREMA_MAIL_CLEANUP_ACC, 
                                                                  getDBConnectionPool() );
    }

    libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getCustomerAccessor()
    {
        infrastructure::accessor::customer::SelectCustomerByPartnerNo();

        using infrastructure::accessor::AccessorProxyUnionDecorator;
        return boost::make_shared< AccessorProxyUnionDecorator >( infrastructure::accessor::customer::lit::CUSTOMER_ACC, getDBConnectionPool() );
    }

    libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getCustomerInvoiceAccessor()
    {
        infrastructure::accessor::customerInvoice::FindCustomerInvoiceByPattern();

        using libutil::infrastructure::accessor::AccessorProxy;
        return boost::make_shared< AccessorProxy >( infrastructure::accessor::customerInvoice::lit::CUSTOMER_INVOICE_ACC, 
                                                    getBasarDBConnection() );
    }

    libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getCustomerInvoiceCollectionAccessor()
    {
        infrastructure::accessor::customerInvoice::FindCustomerInvoiceCollectionByKey();

        using infrastructure::accessor::AccessorProxyUnionDecorator;
        return boost::make_shared< AccessorProxyUnionDecorator >( infrastructure::accessor::customerInvoice::lit::CUSTOMER_INVOICE_COLLECTION_ACC, 
                                                                  getDBConnectionPool() );
    }

    libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getCustomerInvoicingCollectionAccessor()
    {
        typedef boost::shared_ptr< infrastructure::accessor::customerInvoice::CustomerInvoicingCollectionACC > CustomerInvoicingCollectionACCPtr;
        CustomerInvoicingCollectionACCPtr acc = boost::make_shared< infrastructure::accessor::customerInvoice::CustomerInvoicingCollectionACC >();
        acc->injectACCParameter( getAccParameter() );

        return acc;
    }

    libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getCustomerOrderCollectionAccessor()
    {
        infrastructure::accessor::customerOrder::FindCustomerOrderCollection();

        using infrastructure::accessor::AccessorProxyUnionDecorator;
        return boost::make_shared< AccessorProxyUnionDecorator >( infrastructure::accessor::customerOrder::lit::CUSTOMER_ORDER_COLLECTION_ACC, 
                                                                  getDBConnectionPool() );
    }

    libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getCustomerTurnoverCollectionAccessor()
    {
        infrastructure::accessor::customerTurnover::FindCustomerTurnoverCollection();

        using infrastructure::accessor::AccessorProxyUnionDecorator;
        return boost::make_shared< AccessorProxyUnionDecorator >( infrastructure::accessor::customerTurnover::lit::CUSTOMER_TURNOVER_COLLECTION_ACC,
                                                                  getDBConnectionPool() );
    }

    libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getDebtLimitCollectionAccessor()
    {
        infrastructure::accessor::debtLimit::SelectDebtLimitCollection();

        using libutil::infrastructure::accessor::AccessorProxy;
        return boost::make_shared< AccessorProxy >( infrastructure::accessor::debtLimit::lit::DEBTLIMIT_COLLECTION_ACC, getBasarDBConnection() );
    }

    libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getSAPBalanceCollectionAccessor()
    {
        typedef boost::shared_ptr< infrastructure::accessor::sap::SAPBalanceCollectionACC > SAPBalanceCollectionACCPtr;
        SAPBalanceCollectionACCPtr acc = boost::make_shared< infrastructure::accessor::sap::SAPBalanceCollectionACC >();
        acc->injectACCParameter( getAccParameter() );

        return acc;
    }

    libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getSAPCustomerTurnoverCollectionAccessor()
    {
        typedef boost::shared_ptr< infrastructure::accessor::sap::SAPCustomerTurnoverCollectionACC > SAPCustomerTurnoverCollectionACCPtr;
        SAPCustomerTurnoverCollectionACCPtr acc = boost::make_shared< infrastructure::accessor::sap::SAPCustomerTurnoverCollectionACC >();
        acc->injectACCParameter( getAccParameter() );

        return acc;
    }

    libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getSAPLimitCollectionAccessor()
    {
        typedef boost::shared_ptr< infrastructure::accessor::sap::SAPLimitCollectionACC > SAPLimitCollectionACCPtr;
        SAPLimitCollectionACCPtr acc = boost::make_shared< infrastructure::accessor::sap::SAPLimitCollectionACC >();
        acc->injectACCParameter( getAccParameter() );

        return acc;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // </ACC getting>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    libutil::infrastructure::session::ISessionPtr ApplCompMgr::getSession() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Session.get() );
        return m_Session;
    }

    infrastructure::parameter::IACCParameterPtr ApplCompMgr::getAccParameter()
    {
        infrastructure::parameter::ACCParameterPtr param = boost::make_shared< infrastructure::parameter::ACCParameter >();
        param->setAreaId( getSession()->getUser()->getAreaID() );
        param->injectParameterGateway( getParameterGateway() );
        
        return param;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // <OTHERS>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    libutil::infrastructure::db::dbTransaction::IDBTransactionPtr ApplCompMgr::createDBTransaction()
    {
        METHODNAME_DEF( ApplCompMgr, createDBTransaction )
        BLOG_TRACE_METHOD( m_Logger, fun );

        return boost::make_shared< libutil::infrastructure::db::dbTransaction::TransactionGuard >( getBasarDBConnection() );
    }

    infrastructure::connectionPool::IConnectionPoolGetterPtr ApplCompMgr::getDBConnectionPool()
    {
        CHECK_INSTANCE_EXCEPTION( m_DBConnectionPool.get() );
        return m_DBConnectionPool;
    }

    basar::db::aspect::ConnectionRef ApplCompMgr::getBasarDBConnection()
    {
        return getDBConnectionDataGetter()->getCurrentConnection();
    }

    libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr ApplCompMgr::getDBConnectionDataGetter()
    {
        return getDBConnectionPool()->getConnection( "default" );
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // </OTHERS>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // end namnespace componentManager
} // end namnespace libcsc_deli
