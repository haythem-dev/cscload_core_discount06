//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "debtlimitbatchuc.h"

#include "loggerpool/libcsc_deli_loggerpool.h"

#include <domainmodule/customerinvoice/icustomerinvoicingcollection.h>
#include <domainmodule/debtlimit/idebtlimitimporter.h>
#include <domainmodule/turnover/icustomerturnoverexporter.h>
#include <domainmodule/cremamail/icremamailcleaner.h>

#include <libutil/util.h>

#include <libbasardbaspect_accessorpropertytable.h>
#include <libbasardbaspect_accessorpropertytable_yiterator.h>

//-------------------------------------------------------------------------------------------------//
// namespace sections
//-------------------------------------------------------------------------------------------------//
namespace csc_deli
{
namespace useCase
{
    DebtLimitBatchUC::DebtLimitBatchUC()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerUseCases() )
    {
        METHODNAME_DEF( DebtLimitBatchUC, DebtLimitBatchUC )
        BLOG_TRACE_METHOD( m_Logger, fun );
    }

    DebtLimitBatchUC::~DebtLimitBatchUC()
    {
        METHODNAME_DEF( DebtLimitBatchUC, ~DebtLimitBatchUC )
        BLOG_TRACE_METHOD( m_Logger, fun );
    }

    void DebtLimitBatchUC::injectCustomerInvoicingCollection( libcsc_deli::domMod::customerInvoice::ICustomerInvoicingCollectionPtr customerInvoicingColl )
    {
        m_CustomerInvoicingCollection = customerInvoicingColl;
    }

    libcsc_deli::domMod::customerInvoice::ICustomerInvoicingCollectionPtr DebtLimitBatchUC::getCustomerInvoicingCollection() const
    {
        CHECK_INSTANCE_EXCEPTION( m_CustomerInvoicingCollection.get() );
        return m_CustomerInvoicingCollection;
    }

    void DebtLimitBatchUC::injectDebtLimitImporter( libcsc_deli::domMod::debtLimit::IDebtLimitImporterPtr debtLimitImporter )
    {
        m_DebtLimitImporter = debtLimitImporter;
    }

    libcsc_deli::domMod::debtLimit::IDebtLimitImporterPtr DebtLimitBatchUC::getDebtLimitImporter() const
    {
        CHECK_INSTANCE_EXCEPTION( m_DebtLimitImporter.get() );
        return m_DebtLimitImporter;
    }

    void DebtLimitBatchUC::injectCustomerTurnoverExporter( libcsc_deli::domMod::turnover::ICustomerTurnoverExporterPtr cstTurnoverExporter )
    {
        m_CustomerTurnoverExporter = cstTurnoverExporter;
    }

    libcsc_deli::domMod::turnover::ICustomerTurnoverExporterPtr DebtLimitBatchUC::getCustomerTurnoverExporter() const
    {
        CHECK_INSTANCE_EXCEPTION( m_CustomerTurnoverExporter.get() );
        return m_CustomerTurnoverExporter;
    }

    void DebtLimitBatchUC::injectCremaMailCleaner( libcsc_deli::domMod::cremaMail::ICremaMailCleanerPtr cremaMailCleaner )
    {
        m_CremaMailCleaner = cremaMailCleaner;
    }

    libcsc_deli::domMod::cremaMail::ICremaMailCleanerPtr DebtLimitBatchUC::getCremaMailCleaner() const
    {
        CHECK_INSTANCE_EXCEPTION( m_CremaMailCleaner.get() );
        return m_CremaMailCleaner;
    }

    void DebtLimitBatchUC::run()
    {
        METHODNAME_DEF( DebtLimitBatchUC, run )
        BLOG_TRACE_METHOD( m_Logger, fun );

        try
        {
            getCustomerInvoicingCollection()->readCollection();
            getCustomerInvoicingCollection()->save();
            
            getDebtLimitImporter()->importFromSAP();
            getDebtLimitImporter()->calculateTurnover();
            getDebtLimitImporter()->saveDebtLimitCollection();

            getCustomerTurnoverExporter()->loadCustomerTurnoverCollection();
            getCustomerTurnoverExporter()->exportToSAP();

            getCremaMailCleaner()->cleanup();
        }
        catch( basar::Exception& e )
        {
            BLOG_INFO( m_Logger, e.what() );
        }
    }
} // namespace usecase
} // namespace csc_deli
