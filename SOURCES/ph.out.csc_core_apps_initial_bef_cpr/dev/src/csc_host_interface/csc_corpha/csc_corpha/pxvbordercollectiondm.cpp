//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Steffen Heinlein
 *  \date       08.10.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include <iapplconfiguration.h>

#include "pxvbordercollectiondm.h"
#include "ipxvbservicelocator.h"
#include "pxvbcomponentmanager.h"
#include "pxvbsession.h"
#include "pxvborderdm.h"

extern bool pxGlobalDataBaseSort;

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{
    struct null_deleter
    {
        void operator()(void const *) const
        {
        }
    };

    //----------------------------------------------------------------------------//
    PXVBOrderCollectionDM::PXVBOrderCollectionDM( libcsc_utils::ICSC_LoggerPtr logger, domMod::corpha::pxVerbund::IPXVBServiceLocatorPtr svclocator, libcsc_utils::IApplConfigurationPtr applconfig )
    : m_Logger( logger ), m_PXVBServiceLocator( svclocator ), m_ApplConfiguration( applconfig ), m_pxOrderList( NULL ), m_pxOrderListIter( *m_pxOrderList )
    {
        METHODNAME_DEF( PXVBOrderCollectionDM, PXVBOrderCollectionDM );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    PXVBOrderCollectionDM::~PXVBOrderCollectionDM()
    {
        METHODNAME_DEF( PXVBOrderCollectionDM, ~PXVBOrderCollectionDM );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        deleteOrderList();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderCollectionDM::deleteOrderList()
    {
        METHODNAME_DEF( PXVBOrderCollectionDM, deleteOrderList );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( NULL != m_pxOrderList )
        {
            delete m_pxOrderList;
            m_pxOrderList = NULL;
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxOrderListIter PXVBOrderCollectionDM::getOrderListIterator()
    {
        METHODNAME_DEF( PXVBOrderCollectionDM, getOrderListIterator );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( NULL == m_pxOrderListIter.Current() )
        {
            throw basar::cmnutil::BasarException( basar::ExceptInfo( fun, "pxOrderListIterator may not be used without calling findOrder2BeTransferred before", __FILE__, __LINE__ ), "ERROR" );
        }
        return m_pxOrderListIter;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderCollectionDM::findOrders2BeTransferred( pxVerbund::OrderSelectionMode mode )
    {
        METHODNAME_DEF( PXVBOrderCollectionDM, findOrders2BeTransferred );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        basar::VarString logmessage("");
        logmessage.format( "searching for the next %d orders to be transferred", m_ApplConfiguration->getMaxSelectOrders() );
        m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );

        deleteOrderList();

        m_pxOrderList = new ::pxOrderList( m_PXVBServiceLocator->getPXVBSession()->get() );

        pxGlobalDataBaseSort = true; // switch of CompareTo handling in ordbase.cpp in pxverbund, use sort by tourid from kauftrag.h in pxdb // pxGlobalDataBaseSort = global flag in pxverbund
        m_pxOrderList->SelectVSE(   ::pxOrder::cVSEnoTransmit
                                    , m_ApplConfiguration->getMaxSelectOrders()
                                    , m_ApplConfiguration->getBranchNo()
                                    , mode
                                    , ::Order::EntryClosed
                                    , ::Order::cStateLast );
        pxGlobalDataBaseSort = false; // switch off pxGlobalDataBaseSort again
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    PXVBOrderDMPtr PXVBOrderCollectionDM::getFirst()
    {
        METHODNAME_DEF( PXVBOrderCollectionDM, getFirst );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        PXVBOrderDMPtr retval;

        if( m_pxOrderList->Entries() > 0 )
        {
            m_pxOrderListIter = ::pxOrderListIter(*m_pxOrderList);
            retval = createPXVBOrderDM( static_cast< pxOrder* >(++m_pxOrderListIter) );
        }
        return retval;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    PXVBOrderDMPtr PXVBOrderCollectionDM::getNext()
    {
        METHODNAME_DEF( PXVBOrderCollectionDM, getNext );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return createPXVBOrderDM( static_cast< pxOrder* >(++m_pxOrderListIter) );
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    bool PXVBOrderCollectionDM::isEnd()
    {
        METHODNAME_DEF( PXVBOrderCollectionDM, isEnd );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( NULL == m_pxOrderListIter.Current() )
        {
            return true;
        }
        return false;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    PXVBOrderDMPtr PXVBOrderCollectionDM::createPXVBOrderDM( pxOrder* order )
    {
        METHODNAME_DEF( PXVBOrderCollectionDM, createPXVBOrderDM );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( isEnd() )
        {
            return PXVBOrderDMPtr();
        }

        PXVBOrderDMPtr retval;
        //add null_deleter to object instance, order pointer orginates out of a pxVerbund list object and is deleted upon list's destruction
        retval = PXVBOrderDMPtr( new PXVBOrderDM( order ), null_deleter() );
        retval->injectLogger( m_Logger );
        retval->injectPXVBDBConnection( m_PXVBServiceLocator->getPXVBDBConnection() );
        retval->injectPXVBSession( m_PXVBServiceLocator->getPXVBSession() );
        retval->injectPXVBOrderEntryParamChecker( m_PXVBServiceLocator->getPXVBOrderEntryParamChecker() );
        retval->init();
        return retval;
    }
    //----------------------------------------------------------------------------//


} // namespace pxVerbund
} // namespace corpha
} // namespace domMod
