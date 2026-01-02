//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Steffen Heinlein
 *  \date       18.09.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <icsc_logger.h>
#include <classinfo_macros.h>
#include "pxvborderitem.h"
#include "pxvbsession.h"
#include "pxvborderentryparamchecker.h"
#include "pxvborderdm_definitions.h"

//#include "pxdeliveryposlistptr.h"
#include "pxorderposcalcmodeptr.h"
#include "pxitemdiscount.hpp"

#include <discount/orderpositiondiscount/orderpositiondiscountcollection.h>
#include <discount/orderpositiondiscount/orderpositiondiscount.h>

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{

    using ::pxVerbund::subsequentDelivery::pxDeliveryPosList;

    struct null_deleter
    {
        void operator()(void const *) const
        {
        }
    };

    //----------------------------------------------------------------------------//
    PXVBOrderItem::PXVBOrderItem( ::pxOrder* order, ::pxOrderItem* item )
        : m_pxOrder( order ), m_pxOrderItem( item )
    {
        METHODNAME_DEF( PXVBOrderItem, PXVBOrderItem ); (void) fun; // no logger available
        m_pxOrderItem->OrderRef( *getOrder() );
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    PXVBOrderItem::~PXVBOrderItem()
    {
        METHODNAME_DEF( PXVBOrderItem, ~PXVBOrderItem ); (void) fun; // no logger available
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderItem::injectLogger( libcsc_utils::ICSC_LoggerPtr logger )
    {
        METHODNAME_DEF( PXVBOrderItem, injectLogger ); (void) fun; // no logger available
        m_Logger = logger;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderItem::injectPXVBOrderEntryParamChecker( pxVerbund::IPXVBOrderEntryParamCheckerPtr oeparam )
    {
        METHODNAME_DEF( PXVBOrderItem, injectPXVBOrderEntryParamChecker ); (void) fun; // no logger available
        m_PXVBOrderEntryParamChecker = oeparam;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderItem::injectPXVBSession( pxVerbund::IPXVBSessionPtr sess )
    {
        METHODNAME_DEF( PXVBOrderItem, injectPXVBSession ); (void) fun; // no logger available
        m_PXVBSession = sess;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderItem::shutdown()
    {
        METHODNAME_DEF( PXVBOrderItem, shutdown );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    bool PXVBOrderItem::checkDispo()
    {
        METHODNAME_DEF( PXVBOrderItem, checkDispo );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( getOrderItem()->IsDispoItem() )
        {
            return true;
        }
        return false;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    bool PXVBOrderItem::isMSV3Item()
    {
        METHODNAME_DEF( PXVBOrderItem, isMSV3Item );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        bool retval = false;
        if( 6 == getOrderItem()->SubGeraetTyp() ) // MSV3
        {
            retval = true;
        }
        if (11 == getOrderItem()->SubGeraetTyp()) // MSV3V2
        {
            retval = true;
        }
        return retval;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    bool PXVBOrderItem::hasToBeTransferred()
    {
        METHODNAME_DEF( PXVBOrderItem, hasToBeTransferred );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( getOrderItem()->IsNichtNachPharmos() )
        {
            return false;
        }
        return true;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxOrder* PXVBOrderItem::getOrder()
    {
        METHODNAME_DEF( PXVBOrderItem, getOrder ); (void) fun; // logger not available
        // BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_pxOrder;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxOrderItem* PXVBOrderItem::getOrderItem()
    {
        METHODNAME_DEF( PXVBOrderItem, getOrderItem );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_pxOrderItem;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderItem::initCountrySpecific()
    {
        METHODNAME_DEF( PXVBOrderItem, initCountrySpecific );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        initBulgarianSpecific();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderItem::initBulgarianSpecific()
    {
        METHODNAME_DEF( PXVBOrderItem, initBulgarianSpecific );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if (!m_PXVBSession->get()->isBulgaria())
        {
            return;
        }

        // calculation mode
        {
            m_pxOrderPosCalcMode = ::pxOrderPosCalcModePtr( new ::pxOrderPosCalcMode( m_PXVBSession->get(), getOrder()->KdAuftragNr(), getOrderItem()->PosNr() ) );
            if( m_pxOrderPosCalcMode->Get() )
            {
                m_pxOrderPosCalcMode.reset();
            }
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderItem::init()
    {
        METHODNAME_DEF( PXVBOrderItem, initialize );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        initCountrySpecific();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    // TODO HR-08 -> method to get new discount list into member from pxverbund for order line
    libcsc::discount::OrderPositionDiscountListPtr PXVBOrderItem::getNewDiscountList()
    {
        return getOrderItem()->getDiscountList();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxItemDiscountListPtr PXVBOrderItem::getDiscountList()
    {
        METHODNAME_DEF( PXVBOrderItem, getDiscountList );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( 0 == m_pxItemDiscountList.get() )
        {
            m_pxItemDiscountList = ::pxItemDiscountListPtr( new ::pxItemDiscountList( m_PXVBSession->get() ) );
            if( ! (m_pxItemDiscountList->Select( getOrderItem()->KdAuftragNr(), getOrderItem()->PosNr() ) ) )
            {
                m_pxItemDiscountList.reset();
            }
        }
        return m_pxItemDiscountList;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxOrderPosCalcModePtr PXVBOrderItem::getOrderPosCalcMode()
    {
        METHODNAME_DEF( PXVBOrderItem, getOrderPosCalcMode );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_pxOrderPosCalcMode;
    }
    //----------------------------------------------------------------------------//


} // namespace pxVerbund
} // namespace corpha
} // namespace domMod
