//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "debtlimitimportdm.h"

#include "domainmodule/debtlimit/idebtlimitcollection.h"
#include "domainmodule/debtlimit/idebtlimit.h"
#include "domainmodule/debtlimit/idebtlimitmailprocessor.h"
#include "domainmodule/sap/isapcollectionreader.h"
#include "domainmodule/turnover/iturnoverfinder.h"
#include "domainmodule/customer/icustomerfinder.h"
#include "domainmodule/customerorder/icustomerordercollectionfinder.h"
#include "domainmodule/customerinvoice/icustomerinvoiceflag.h"

#include "domainmodule/libcsc_deli_properties_definitions.h"
#include "loggerpool/libcsc_deli_loggerpool.h"

#include <libutil/domainmodule.h>
#include <libutil/version.h>
#include <libutil/exception.h>

//--------------------------------------------------------------------------------------------------//
// class definition section
//--------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace domMod
{
namespace debtLimit
{

    const libutil::misc::ClassInfo& DebtLimitImportDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "DebtLimitImportDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    DebtLimitImportDM::DebtLimitImportDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( DebtLimitImportDM, DebtLimitImportDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    DebtLimitImportDM::~DebtLimitImportDM()
    {
        METHODNAME_DEF( DebtLimitImportDM, ~DebtLimitImportDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void DebtLimitImportDM::injectDebtLimitCollection( IDebtLimitCollectionPtr debtLimitCollection )
    {
        m_DebtLimitCollection = debtLimitCollection;
    }

    IDebtLimitCollectionPtr DebtLimitImportDM::getDebtLimitCollection() const
    {
        CHECK_INSTANCE_EXCEPTION( m_DebtLimitCollection.get() );
        return m_DebtLimitCollection;
    }

    void DebtLimitImportDM::injectDebtLimitMailProcessor( IDebtLimitMailProcessorPtr debtLimitMailProcessor )
    {
        m_DebtLimitMailProcessor = debtLimitMailProcessor;
    }

    IDebtLimitMailProcessorPtr DebtLimitImportDM::getDebtLimitMailProcessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_DebtLimitMailProcessor.get() );
        return m_DebtLimitMailProcessor;
    }

    void DebtLimitImportDM::injectSAPLimitCollection( sap::ISAPCollectionReaderPtr sapCollection )
    {
        m_SAPLimitCollectionReader = sapCollection;
    }

    sap::ISAPCollectionReaderPtr DebtLimitImportDM::getSAPLimitCollection() const
    {
        CHECK_INSTANCE_EXCEPTION( m_SAPLimitCollectionReader.get() );
        return m_SAPLimitCollectionReader;
    }

    void DebtLimitImportDM::injectSAPBalanceCollection( sap::ISAPCollectionReaderPtr sapCollection )
    {
        m_SAPBalanceCollectionReader = sapCollection;
    }

    sap::ISAPCollectionReaderPtr DebtLimitImportDM::getSAPBalanceCollection() const
    {
        CHECK_INSTANCE_EXCEPTION( m_SAPBalanceCollectionReader.get() );
        return m_SAPBalanceCollectionReader;
    }

    void DebtLimitImportDM::injectTurnoverFinder( turnover::ITurnoverFinderPtr turnoverFinder )
    {
        m_TurnoverFinder = turnoverFinder;
    }

    turnover::ITurnoverFinderPtr DebtLimitImportDM::getTurnoverFinder() const
    {
        CHECK_INSTANCE_EXCEPTION( m_TurnoverFinder.get() );
        return m_TurnoverFinder;
    }

    void DebtLimitImportDM::injectCustomerFinder( customer::ICustomerFinderPtr customerFinder )
    {
        m_CustomerFinder = customerFinder;
    }

    customer::ICustomerFinderPtr DebtLimitImportDM::getCustomerFinder() const
    {
        CHECK_INSTANCE_EXCEPTION( m_CustomerFinder.get() );
        return m_CustomerFinder;
    }

    void DebtLimitImportDM::injectCustomerInvoiceFlag( customerInvoice::ICustomerInvoiceFlagPtr customerInvoiceFlag )
    {
        m_CustomerInvoiceFlag = customerInvoiceFlag;
    }

    customerInvoice::ICustomerInvoiceFlagPtr DebtLimitImportDM::getCustomerInvoiceFlag() const
    {
        CHECK_INSTANCE_EXCEPTION( m_CustomerInvoiceFlag.get() );
        return m_CustomerInvoiceFlag;
    }

    const log4cplus::Logger& DebtLimitImportDM::getLogger() const
    {
        return m_Logger;
    }

    void DebtLimitImportDM::resetSumDebitSide()
    {
        METHODNAME_DEF( DebtLimitImportDM, resetSumDebitSide )
        BLOG_TRACE_METHOD( getLogger(), fun );

        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = getDebtLimitCollection()->get().begin(); ! yit.isEnd(); ++yit )
        {
            yit.setDecimal( properties::SUM_DEBIT_SIDE, basar::Decimal( 0 ) );
        }
    }

    void DebtLimitImportDM::eraseUnreferencedDebtLimits()
    {
        METHODNAME_DEF( DebtLimitImportDM, eraseUnreferencedDebtLimits )
        BLOG_TRACE_METHOD( getLogger(), fun );

        BLOG_INFO( getLogger(), "Deleting debtlimits which aren't contained in import file ..." );

        // delete debtlimits which aren't referenced in sap limits file anymore
        // unreferenced debtlimits have partner name property unset (see importSAPLimit() below)
        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = getDebtLimitCollection()->get().begin(); ! yit.isEnd();  )
        {
            if( yit.isContainedAndSet( properties::PARTNER_NAME ) )
            {
                ++yit;
            }
            else
            {
                IDebtLimitPtr debtLimit = getDebtLimitCollection()->getDebtLimit( yit.getInt32( properties::PARTNER_NO ) );
                yit = getDebtLimitCollection()->erase( debtLimit );
            }
        }
    }

    void DebtLimitImportDM::putInvoicedFlag( const basar::db::aspect::AccessorPropertyTable_YIterator yit )
    {
        METHODNAME_DEF( DebtLimitImportDM, putInvoicedFlag )
        BLOG_TRACE_METHOD( getLogger(), fun );

        if( yit.getInt32( properties::DATE ) > 0 )
        {
            getCustomerInvoiceFlag()->saveInvoicedFlag( yit );
        }
    }

    void DebtLimitImportDM::loadDebtLimits()
    {
        METHODNAME_DEF( DebtLimitImportDM, loadDebtLimits )
        BLOG_TRACE_METHOD( getLogger(), fun );

        getDebtLimitCollection()->load();
    }

    void DebtLimitImportDM::importSAPLimit()
    {
        METHODNAME_DEF( DebtLimitImportDM, importSAPLimit )
        BLOG_TRACE_METHOD( getLogger(), fun );

        getSAPLimitCollection()->readCollection();
        if( getSAPLimitCollection()->isEmpty() )
        {
            BLOG_INFO( getLogger(), "No SAP limits found - none imported!" );
            return;
        }

        BLOG_INFO( getLogger(), "Importing SAP limit file ..." );
        for( basar::db::aspect::AccessorPropertyTable_YIterator yitSAPLimit = getSAPLimitCollection()->get().begin(); 
             ! yitSAPLimit.isEnd(); ++yitSAPLimit )
        {
            const basar::Int32 partnerNo = yitSAPLimit.getInt32( properties::PARTNER_NO );

            // set limit and possibly other values from sap file (if any)
            IDebtLimitPtr debtLimit = getDebtLimitCollection()->getDebtLimit( partnerNo );
            if( debtLimit->isEmpty() )
            {
                debtLimit = getDebtLimitCollection()->appendEmptyItem( partnerNo );
            }
            debtLimit->get().match( yitSAPLimit ); // update with data from sap

            // set partner name
            getCustomerFinder()->findByPartnerNo( partnerNo );
            debtLimit->get().setString( properties::PARTNER_NAME, " " ); // switch state SS_UNSET -> SS_CLEAN
            debtLimit->get().setString( properties::PARTNER_NAME, getCustomerFinder()->isEmpty() ? " " : getCustomerFinder()->get().getString( properties::PARTNER_NAME ) ); // sets UPDATE state accordingly
        }

        eraseUnreferencedDebtLimits(); // delete debtlimits which are not referenced in sap file (file is mapped 1:1 to DB table)
        getSAPLimitCollection()->backup(); // store backup of limit file
    }

    void DebtLimitImportDM::importSAPBalance()
    {
        METHODNAME_DEF( DebtLimitImportDM, importSAPBalance )
        BLOG_TRACE_METHOD( getLogger(), fun );

        getSAPBalanceCollection()->readCollection();
        if( getSAPBalanceCollection()->isEmpty() )
        {
            BLOG_INFO( getLogger(), "No SAP balances found - none imported!" );
            return;
        }
        resetSumDebitSide();

        BLOG_INFO( getLogger(), "Importing SAP balance file ..." );
        for( basar::db::aspect::AccessorPropertyTable_YIterator yitSAPBalance = getSAPBalanceCollection()->get().begin();
             ! yitSAPBalance.isEnd(); ++yitSAPBalance )
        {
            if( yitSAPBalance.isContainedAndSet( properties::PARTNER_NO ) ) // some datasets have empty partnerno
            {
                IDebtLimitPtr debtLimit = getDebtLimitCollection()->getDebtLimit( yitSAPBalance.getInt32( properties::PARTNER_NO ) );
                if( ! debtLimit->isEmpty() )
                {
                    // add sum debitside from sap file
                    basar::Decimal sumDebitSide = debtLimit->get().getDecimal( properties::SUM_DEBIT_SIDE );
                    sumDebitSide += yitSAPBalance.getDecimal( properties::SUM_DEBIT_SIDE );
                    debtLimit->get().setDecimal( properties::SUM_DEBIT_SIDE, sumDebitSide );
                }
            }

            // puts a marker that this dataset has already been imported
            putInvoicedFlag( yitSAPBalance );
        }
        getSAPBalanceCollection()->backup();
    }

    void DebtLimitImportDM::importFromSAP()
    {
        METHODNAME_DEF( DebtLimitImportDM, importFromSAP )
        BLOG_TRACE_METHOD( getLogger(), fun );

        loadDebtLimits();              // load old debtlimits from DB
        importSAPLimit();              // Important: limits have to be imported first to build the base for all debtlimits
        importSAPBalance();            // balance data is imported for all available debt limits from sap
    }

    void DebtLimitImportDM::calculateTurnover()
    {
        METHODNAME_DEF( DebtLimitImportDM, calculateTurnover )
        BLOG_TRACE_METHOD( getLogger(), fun );

        BLOG_INFO( getLogger(), "Calculating turnover ..." );
        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = getDebtLimitCollection()->get().begin();
             ! yit.isEnd(); ++yit )
        {
            getTurnoverFinder()->findByPartnerNo( yit.getInt32( properties::PARTNER_NO ) );

            yit.setDecimal( properties::SUM_TURNOVER_DAY,   getTurnoverFinder()->getTurnoverDay()     );
            yit.setDecimal( properties::SUM_TURNOVER_MONTH, getTurnoverFinder()->getTurnoverMonth()   );
            yit.setDecimal( properties::SUM_RETURNS,        getTurnoverFinder()->getSumReturns()      );
            yit.setDecimal( properties::SUM_GOODS_RECEIPT,  getTurnoverFinder()->getSumReclamations() );
        }
    }

    void DebtLimitImportDM::saveDebtLimitCollection()
    {
        METHODNAME_DEF( DebtLimitImportDM, saveDebtLimitCollection )
        BLOG_TRACE_METHOD( getLogger(), fun );

        
        BLOG_INFO( getLogger(), "Saving debtlimits into DB" );
        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = getDebtLimitCollection()->get().begin(); ! yit.isEnd(); ++yit )
        {
            const basar::Int32 partnerNo = yit.getInt32( properties::PARTNER_NO );
            IDebtLimitPtr debtLimit = getDebtLimitCollection()->getDebtLimit( partnerNo );
            if( debtLimit->isChanged() )
            {
                debtLimit->save();
            }

            // process debtlimit mails
            getDebtLimitMailProcessor()->processCremaMails( partnerNo );
        }
    }

} // end namespace debtLimit
} // end namespace domMod
} // end namespace libcsc_deli
