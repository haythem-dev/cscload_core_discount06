//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "debtlimitcollectiondm.h"

#include "idebtlimit.h"

#include "componentmanager/idebtlimitdisconnectedfactory.h"
#include "domainmodule/libcsc_deli_properties_definitions.h"
#include "infrastructure/accessor/debtlimit/debtlimitcollectionacc_definitions.h"
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

    const libutil::misc::ClassInfo& DebtLimitCollectionDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "DebtLimitCollectionDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    DebtLimitCollectionDM::DebtLimitCollectionDM()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( DebtLimitCollectionDM, DebtLimitCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    DebtLimitCollectionDM::~DebtLimitCollectionDM()
    {
        METHODNAME_DEF( DebtLimitCollectionDM, ~DebtLimitCollectionDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    void DebtLimitCollectionDM::injectDebtLimitCollectionAccessor( libutil::infrastructure::accessor::IAccessorPtr accessor )
    {
        m_Accessor = accessor;
    }

    libutil::infrastructure::accessor::IAccessorPtr DebtLimitCollectionDM::getAccessor() const
    {
        CHECK_INSTANCE_EXCEPTION( m_Accessor.get() );
        return m_Accessor;
    }

    void DebtLimitCollectionDM::injectDebtLimitDisconnectedFactory( componentManager::IDebtLimitDisconnectedFactoryPtr factory )
    {
        m_DebtLimitDisconnectedFactory = factory;
    }

    componentManager::IDebtLimitDisconnectedFactoryPtr DebtLimitCollectionDM::getDebtLimitDisconnectedFactory()
    {
        CHECK_INSTANCE_EXCEPTION( m_DebtLimitDisconnectedFactory.get() );
        return m_DebtLimitDisconnectedFactory;
    }

    basar::db::aspect::AccessorPropertyTableRef DebtLimitCollectionDM::get() const
    {
        return getAccessor()->getPropertyTable();
    }

    bool DebtLimitCollectionDM::isEmpty() const
    {
        return 0 == getAccessor().get() || m_Accessor->getPropertyTable().isNull() ||
               m_Accessor->getPropertyTable().isEmpty();
    }

    IDebtLimitPtr DebtLimitCollectionDM::getDebtLimit( basar::Int32 partnerNo )
    {
        METHODNAME_DEF( DebtLimitCollectionDM, getDebtLimit )
        BLOG_TRACE_METHOD( getLogger(), fun );

        if( m_IndexPartnerNo.empty() ) // create index if missing
        {
            createIndex();
        }

        basar::db::aspect::AccessorPropertyTable_YIterator yit = get().end();
        
        // check if debtLimit is contained in collection and get it if available
        IndexPartnerNo::const_iterator it = m_IndexPartnerNo.find( partnerNo );
        if( it != m_IndexPartnerNo.end() )
        {
            yit = it->second;
        }

        return getDebtLimitDisconnectedFactory()->create( yit );
    }

    IDebtLimitPtr DebtLimitCollectionDM::appendEmptyItem( basar::Int32 partnerNo )
    {
        basar::db::aspect::AccessorPropertyTable_YIterator yit = getAccessor()->getPropertyTable().insert( basar::FOR_INSERT );
        m_IndexPartnerNo[ partnerNo ] = yit;

        // set all decimal values to 0
        yit.setDecimal( properties::LIMIT,              basar::Decimal( 0 ) );
        yit.setDecimal( properties::SUM_DEBIT_SIDE,     basar::Decimal( 0 ) );
        yit.setDecimal( properties::SUM_CREDIT_SIDE,    basar::Decimal( 0 ) );
        yit.setDecimal( properties::SUM_TURNOVER_MONTH, basar::Decimal( 0 ) );
        yit.setDecimal( properties::SUM_TURNOVER_DAY,   basar::Decimal( 0 ) );
        yit.setDecimal( properties::SUM_RETURNS,        basar::Decimal( 0 ) );
        yit.setDecimal( properties::SUM_GOODS_RECEIPT,  basar::Decimal( 0 ) );
        yit.setInt32  ( properties::PARTNER_NO,         partnerNo           );

        return getDebtLimitDisconnectedFactory()->create( yit );
    }

    basar::db::aspect::AccessorPropertyTable_YIterator DebtLimitCollectionDM::erase( IDebtLimitPtr debtLimit )
    {
        basar::db::aspect::AccessorPropertyTable_YIterator yit = debtLimit->get();
        debtLimit->erase();
        
        // adjust index
        m_IndexPartnerNo.erase( yit.getInt32( properties::PARTNER_NO ) );

        return get().erase( yit );
    }

    libutil::domMod::SearchYIteratorPtr DebtLimitCollectionDM::getSearchYIterator()
    {
        if( NULL == m_SearchYIterator.get() )
        {
            m_SearchYIterator = libutil::domMod::SearchYIteratorPtr(
                new libutil::domMod::SearchYIterator( properties::SUM_RETURNS.toDescriptionString()        +
                                                      properties::SUM_TURNOVER_DAY.toDescriptionString()   +
                                                      properties::SUM_TURNOVER_MONTH.toDescriptionString() +
                                                      properties::SUM_CREDIT_SIDE.toDescriptionString()    +
                                                      properties::SUM_DEBIT_SIDE.toDescriptionString()
                )
            );
        }

        return m_SearchYIterator;
    }

    const log4cplus::Logger& DebtLimitCollectionDM::getLogger() const
    {
        return m_Logger;
    }

    void DebtLimitCollectionDM::load()
    {
        METHODNAME_DEF( DebtLimitCollectionDM, load )
        BLOG_TRACE_METHOD( getLogger(), fun );

        m_IndexPartnerNo.clear(); // delete old index

        using infrastructure::accessor::debtLimit::lit::SELECT_DEBTLIMIT_COLLECTION;

        basar::db::aspect::ExecuteResultInfo executeResultInfo;
        try
        {
            executeResultInfo = getAccessor()->execute( SELECT_DEBTLIMIT_COLLECTION, getSearchYIterator()->get() );
        }
        catch( basar::Exception& e )
        {
            libutil::exceptions::ExceptionHandler::processAccessorException( e, getLogger(), fun, SELECT_DEBTLIMIT_COLLECTION, 
                                                                             __FILE__, __LINE__ );
            throw;
        }

        if( executeResultInfo.hasError() )
        {
            THROW_ACCESSOR_EXECUTION_EXCEPTION( fun, SELECT_DEBTLIMIT_COLLECTION, executeResultInfo )
        }
    }

    void DebtLimitCollectionDM::createIndex()
    {
        METHODNAME_DEF( DebtLimitCollectionDM, createIndex )
        BLOG_TRACE_METHOD( getLogger(), fun );

        m_IndexPartnerNo.clear();
        for( basar::db::aspect::AccessorPropertyTable_YIterator yit = get().begin(); ! yit.isEnd(); ++yit )
        {
            m_IndexPartnerNo[ yit.getInt32( properties::PARTNER_NO ) ] = yit;
        }
    }

} // end namespace debtLimit
} // end namespace domMod
} // end namespace libcsc_deli
