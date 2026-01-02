//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "turnoverdm.h"
#include "turnoverdm_definitions.h"

#include "domainmodule/customerorder/icustomerordercollectionfinder.h"

#include "infrastructure/accessor/customerinvoice/customerinvoicecollectionacc_definitions.h"
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
namespace turnover
{
    const libutil::misc::ClassInfo& TurnoverDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "TurnoverDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    TurnoverDM::TurnoverDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( TurnoverDM, TurnoverDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    TurnoverDM::~TurnoverDM()
    {
        METHODNAME_DEF( TurnoverDM, ~TurnoverDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void TurnoverDM::injectCustomerInvoiceCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr TurnoverDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    void TurnoverDM::injectCustomerOrderCollectionFinder( customerOrder::ICustomerOrderCollectionFinderPtr customerOrderCollectionFinder )
    {
        m_CustomerOrderCollectionFinder = customerOrderCollectionFinder;
    }

    customerOrder::ICustomerOrderCollectionFinderPtr TurnoverDM::getCustomerOrderCollectionFinder() const
    {
         CHECK_INSTANCE_EXCEPTION( m_CustomerOrderCollectionFinder.get() );
         return m_CustomerOrderCollectionFinder;
    }

    basar::db::aspect::AccessorPropertyTableRef TurnoverDM::get() const
    {
        return m_Accessor->getPropertyTable();
    }

    void TurnoverDM::resetSearchYit()
    {
        METHODNAME_DEF( TurnoverDM, resetSearchYit )
        BLOG_TRACE_METHOD( getLogger(), fun );

        getSearchYIterator()->reset();
    }

    basar::db::aspect::AccessorPropertyTable_YIterator TurnoverDM::getSearchYit()
    {
        METHODNAME_DEF( TurnoverDM, getSearchYit )
        BLOG_TRACE_METHOD( getLogger(), fun );

        return getSearchYIterator()->get();
    }

    void TurnoverDM::findByPartnerNo( basar::Int32 partnerNo )
    {
        METHODNAME_DEF( TurnoverDM, findByPartnerNo )
        BLOG_TRACE_METHOD( getLogger(), fun );

        resetSearchYit();
        getSearchYit().setInt32( properties::PARTNER_NO, partnerNo );

        using infrastructure::accessor::customerInvoice::lit::FIND_CUSTOMER_INVOICE_COLLECTION_BY_KEY;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( FIND_CUSTOMER_INVOICE_COLLECTION_BY_KEY, getSearchYit() );
        }
        catch( basar::Exception & e  )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, FIND_CUSTOMER_INVOICE_COLLECTION_BY_KEY, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, FIND_CUSTOMER_INVOICE_COLLECTION_BY_KEY, executeResultInfo )
        }

        m_CustomerOrderCollectionFinder->findByPartnerNo( partnerNo );
        calculateTurnover();
    }

    libutil::domMod::SearchYIteratorPtr TurnoverDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = libutil::domMod::SearchYIteratorPtr(
                new libutil::domMod::SearchYIterator( properties::PARTNER_NO.toDescriptionString() ) 
            );
        }

        return m_SearchYIterator;
    }

    const log4cplus::Logger& TurnoverDM::getLogger() const
    {
        return m_Logger;
    }

    void TurnoverDM::calculateTurnover()
    {
        METHODNAME_DEF( TurnoverDM, calculateTurnover )
        BLOG_TRACE_METHOD( getLogger(), fun );

        m_TurnoverMonth   = basar::Decimal( 0 );
        m_SumReturns      = basar::Decimal( 0 );
        m_SumReclamations = basar::Decimal( 0 );

        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = get().begin(); ! yit.isEnd(); ++yit )
        {
            basar::Int16     docType = yit.getInt16  ( properties::DOC_TYPE  );
            if( docType == docTypeTurnover )
            {
                m_TurnoverMonth += yit.getDecimal( properties::AMOUNT );
            }

            if( docType == docTypeReturns )
            {
                basar::VarString textKey = yit.getString ( properties::TEXT_KEY );
                if( textKey == keyReturns )
                {
                    m_SumReturns += yit.getDecimal( properties::AMOUNT );
                }
                if( textKey == keyReclamations )
                {
                    m_SumReclamations += yit.getDecimal( properties::AMOUNT );
                }
            }
        }

        m_SumReturns      *= -1;
        m_SumReclamations *= -1;
    }

    basar::Decimal TurnoverDM::getTurnoverDay() const
    {
        return m_CustomerOrderCollectionFinder->getDeliveryValue();
    }

    basar::Decimal TurnoverDM::getTurnoverMonth() const
    {
        return m_TurnoverMonth;
    }

    basar::Decimal TurnoverDM::getSumReclamations() const
    {
        return m_SumReclamations;
    }

    basar::Decimal TurnoverDM::getSumReturns() const
    {
        return m_SumReturns;
    }

} // end namespace turnover
} // end namespace domMod
} // end namespace libcsc_deli
