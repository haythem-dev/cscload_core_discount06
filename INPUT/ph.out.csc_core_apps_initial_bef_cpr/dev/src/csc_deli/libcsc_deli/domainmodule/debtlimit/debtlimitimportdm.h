#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITIMPORTDM_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITIMPORTDM_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "idebtlimitimporter.h"

#include "domainmodule/debtlimit/idebtlimitcollectionptr.h"
#include "domainmodule/debtlimit/idebtlimitmailprocessorptr.h"
#include "domainmodule/sap/isapcollectionreaderptr.h"
#include "domainmodule/customer/icustomerfinderptr.h"
#include "domainmodule/turnover/iturnoverfinderptr.h"
#include "domainmodule/customerinvoice/icustomerinvoiceflagptr.h"

#include <libutil/searchyiterator.h>
#include <libutil/accessor.h>
#include <libutil/classinfo.h>
#include <libutil/util.h>

//-------------------------------------------------------------------------------------------------//
// class definition section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace debtLimit
{
    class DebtLimitImportDM : public IDebtLimitImporter
    {
    public:
        static const libutil::misc::ClassInfo& getClassInfo();

    public:
        DebtLimitImportDM();
        ~DebtLimitImportDM();

        void                                                        injectDebtLimitCollection   ( IDebtLimitCollectionPtr      );
        void                                                        injectDebtLimitMailProcessor( IDebtLimitMailProcessorPtr   );
        void                                                        injectSAPLimitCollection    ( sap::ISAPCollectionReaderPtr );
        void                                                        injectSAPBalanceCollection  ( sap::ISAPCollectionReaderPtr );
        void                                                        injectTurnoverFinder        ( turnover::ITurnoverFinderPtr );
        void                                                        injectCustomerFinder        ( customer::ICustomerFinderPtr );
        void                                                        injectCustomerInvoiceFlag   ( customerInvoice::ICustomerInvoiceFlagPtr );

        // from IDebtLimitImport interface
        void                                                        importFromSAP();
        void                                                        calculateTurnover();
        void                                                        saveDebtLimitCollection();

    private:
        // forbidden
        DebtLimitImportDM( const DebtLimitImportDM& );
        DebtLimitImportDM& operator = ( const DebtLimitImportDM& );
        
        const log4cplus::Logger&                                    getLogger()                 const;

        IDebtLimitCollectionPtr                                     getDebtLimitCollection()    const;
        IDebtLimitMailProcessorPtr                                  getDebtLimitMailProcessor() const;
        sap::ISAPCollectionReaderPtr                                getSAPLimitCollection()     const;
        sap::ISAPCollectionReaderPtr                                getSAPBalanceCollection()   const;
        turnover::ITurnoverFinderPtr                                getTurnoverFinder()         const;
        customer::ICustomerFinderPtr                                getCustomerFinder()         const;
        customerInvoice::ICustomerInvoiceFlagPtr                    getCustomerInvoiceFlag()    const;

        void                                                        loadDebtLimits();
        void                                                        importSAPLimit();
        void                                                        importSAPBalance();

        void                                                        resetSumDebitSide();
        void                                                        eraseUnreferencedDebtLimits();
        void                                                        putInvoicedFlag( const basar::db::aspect::AccessorPropertyTable_YIterator );

    private:
        const log4cplus::Logger&                                    m_Logger;

        IDebtLimitCollectionPtr                                     m_DebtLimitCollection;
        IDebtLimitMailProcessorPtr                                  m_DebtLimitMailProcessor;
        sap::ISAPCollectionReaderPtr                                m_SAPLimitCollectionReader;
        sap::ISAPCollectionReaderPtr                                m_SAPBalanceCollectionReader;
        turnover::ITurnoverFinderPtr                                m_TurnoverFinder;
        customer::ICustomerFinderPtr                                m_CustomerFinder;
        customerInvoice::ICustomerInvoiceFlagPtr                    m_CustomerInvoiceFlag;
    };

} // end namespace debtLimit
} // end namespace domMod
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITIMPORTDM_H
