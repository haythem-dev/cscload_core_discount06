#ifndef GUARD_CSC_DELI_USECASE_DEBTLIMITBATCHUC_H
#define GUARD_CSC_DELI_USECASE_DEBTLIMITBATCHUC_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <domainmodule/customerinvoice/icustomerinvoicingcollectionptr.h>
#include <domainmodule/debtlimit/idebtlimitimporterptr.h>
#include <domainmodule/turnover/icustomerturnoverexporterptr.h>
#include <domainmodule/cremamail/icremamailcleanerptr.h>

#include <libutil/irunnable.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace appl
    {
        class IEventSource;
        struct EventReturnStruct;
    }
}

namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class AccessorPropertyTable_YIterator;
            class Manager;
        }
    }
}

namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace csc_deli
{
namespace useCase
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration
    //-------------------------------------------------------------------------------------------------//
    class DebtLimitBatchUC : public libutil::useCase::IRunnable
    {
        public:
            DebtLimitBatchUC();
            ~DebtLimitBatchUC();

            void                                                    injectCustomerInvoicingCollection( libcsc_deli::domMod::customerInvoice::ICustomerInvoicingCollectionPtr );
            void                                                    injectDebtLimitImporter( libcsc_deli::domMod::debtLimit::IDebtLimitImporterPtr );
            void                                                    injectCustomerTurnoverExporter( libcsc_deli::domMod::turnover::ICustomerTurnoverExporterPtr );
            void                                                    injectCremaMailCleaner( libcsc_deli::domMod::cremaMail::ICremaMailCleanerPtr );

            // from IRunnable interface
            void                                                    run();

        private:
            DebtLimitBatchUC( const DebtLimitBatchUC& );
            DebtLimitBatchUC& operator = ( const DebtLimitBatchUC& );

            libcsc_deli::domMod::customerInvoice::ICustomerInvoicingCollectionPtr getCustomerInvoicingCollection() const;
            libcsc_deli::domMod::debtLimit::IDebtLimitImporterPtr                 getDebtLimitImporter() const;
            libcsc_deli::domMod::turnover::ICustomerTurnoverExporterPtr           getCustomerTurnoverExporter() const;
            libcsc_deli::domMod::cremaMail::ICremaMailCleanerPtr                  getCremaMailCleaner() const;

        private:
            const log4cplus::Logger&                                              m_Logger;

            libcsc_deli::domMod::customerInvoice::ICustomerInvoicingCollectionPtr m_CustomerInvoicingCollection;
            libcsc_deli::domMod::debtLimit::IDebtLimitImporterPtr                 m_DebtLimitImporter;
            libcsc_deli::domMod::turnover::ICustomerTurnoverExporterPtr           m_CustomerTurnoverExporter;
            libcsc_deli::domMod::cremaMail::ICremaMailCleanerPtr                  m_CremaMailCleaner;
    };
} // namespace useCase
} // namespace csc_deli

#endif // GUARD_CSC_DELI_USECASE_DEBTLIMITBATCHUC_H
