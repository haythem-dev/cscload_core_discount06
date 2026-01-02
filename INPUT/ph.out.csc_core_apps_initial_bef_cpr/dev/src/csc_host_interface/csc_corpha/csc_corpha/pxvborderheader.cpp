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

#include "pxvborderheader.h"

#include "pxvbsession.h"

#include "pxvbdbconnection.h"
#include "pxvbdbconnection_definitions.h"

#include "pxvborderdm_definitions.h"

#include <discount/orderpositiondiscount/orderpositiondiscountcollection.h>
#include <discount/orderpositiondiscount/orderpositiondiscount.h>

#include <pxorderdiscacc.hpp>
#include <pxcustinf.hpp>
#include <pxnumb.hpp>
#include <pxcstot.hpp>
#include <pxcstbas.hpp>
#include <pxcustomerflags.hpp>
#include "pxordvtr.hpp"
#include "types/messagecodeenum.inc"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

namespace domMod
{
namespace corpha
{
namespace pxVerbund
{
    //----------------------------------------------------------------------------//
    PXVBOrderHeader::PXVBOrderHeader( ::pxOrder* order )
        : m_OrderTypeValid( false ), m_pxOrder( order )
    {
        METHODNAME_DEF( PXVBOrderHeader, PXVBOrderHeader ); (void) fun; // no logger available
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    PXVBOrderHeader::~PXVBOrderHeader()
    {
        METHODNAME_DEF( PXVBOrderHeader, ~PXVBOrderHeader ); (void) fun; // no logger available
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderHeader::injectLogger( libcsc_utils::ICSC_LoggerPtr logger )
    {
        METHODNAME_DEF( PXVBOrderHeader, injectLogger ); (void) fun; // no logger available
        m_Logger = logger;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderHeader::injectPXVBSession( pxVerbund::IPXVBSessionPtr sess )
    {
        METHODNAME_DEF( PXVBOrderHeader, injectPXVBSession ); (void) fun; // no logger available
        m_PXVBSession = sess;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderHeader::injectPXVBDBConnection( pxVerbund::IPXVBDBConnectionPtr conn )
    {
        METHODNAME_DEF( PXVBOrderHeader, injectPXVBDBConnection ); (void) fun; // no logger available
        m_PXVBDBConnection = conn;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderHeader::shutdown()
    {
        METHODNAME_DEF( PXVBOrderHeader, shutdown );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderHeader::initCountrySpecific()
    {
        METHODNAME_DEF( PXVBOrderHeader, initCountrySpecific );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        initBulgarianSpecific();
        initSerbianSpecific();
        initFranceSpecific();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderHeader::initBulgarianSpecific()
    {
        METHODNAME_DEF( PXVBOrderHeader, initBulgarianSpecific );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if (!m_PXVBSession->get()->isBulgaria())
        {
            return;
        }

        // discount account Bulgaria
        if( getOrder()->OrderType().IsDiscountAccount() )
        {
            m_pxOrderDiscAcc = ::pxOrderDiscAccPtr( new ::pxOrderDiscAcc( m_PXVBSession->get(), getOrder()->Vertriebszentrum(), getOrder()->KdAuftragNr() ) );
            if( m_pxOrderDiscAcc->Get() )
            {
                m_pxOrderDiscAcc.reset();
            }
        }

        // calculation mode
        {
            m_pxOrderCalcMode = ::pxOrderCalcModePtr( new ::pxOrderCalcMode( m_PXVBSession->get(), getOrder()->KdAuftragNr() ) );
            if( m_pxOrderCalcMode->Get() )
            {
                m_pxOrderCalcMode.reset();
            }
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderHeader::initFranceSpecific()
    {
        METHODNAME_DEF( PXVBOrderHeader, initFranceSpecific );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if (!m_PXVBSession->get()->isFrance() && !m_PXVBSession->get()->isFrancePrewhole())
        {
            return;
        }

        if( 48 == getOrder()->OrderFilialNr() || 43 == getOrder()->OrderFilialNr() )
        {
            setPrewholesaleBatchOrderNo();
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderHeader::setPrewholesaleBatchOrderNo()
    {
        METHODNAME_DEF( PXVBOrderHeader, setPrewholesaleBatchOrderNo );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        basar::VarString logmsg("");

        if( getOrder()->BatchAuftragNr() == 0 )
        {
            try
            {
                m_PXVBDBConnection->beginTransaction( MULTI_RECORD );
                pxOrder order( m_PXVBSession->get(), getOrder()->KdAuftragNr(), cDBGET_FORUPDATE );
                if( !order.IsGoodState() )
                {
                    m_Logger->log(log4cplus::ERROR_LOG_LEVEL, "setPrewholesaleBatchOrderNo: Order is not in GoodState when trying to add batchorderno in PXVBOrderHeader::setPrewholesaleBatchOrderNo");
                }
                else
                {
                    long batchorderno = 0;
                    // branch specific number ranges!!!
                    if( 48 == order.OrderFilialNr() )
                    {
                        pxNumber pxnum(m_PXVBSession->get());
                        batchorderno = pxnum.GetNextNumber(cNUM_BatchOrderNo);
                        logmsg.format( "setPrewholesaleBatchOrderNo: BatchOrderNo determined (cNUM_BatchOrderNo) for branch 48: %ld", batchorderno );
                        m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmsg );
                    }
                    else if ( 43 == order.OrderFilialNr() )
                    {
                        pxNumber pxnum(m_PXVBSession->get());
                        batchorderno = pxnum.GetNextNumber(cNUM_BatchOrderNo2);

                        logmsg.format( "setPrewholesaleBatchOrderNo: BatchOrderNo determined (cNUM_BatchOrderNo2) for branch 43: %ld", batchorderno );
                        m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmsg );
                    }
                    order.SetBatchAuftragNr( batchorderno );
                    getOrder()->SetBatchAuftragNr( batchorderno );
                    order.VSEPut();
                    if( !order.IsGoodState() )
                    {
                        m_Logger->log(log4cplus::ERROR_LOG_LEVEL, "setPrewholesaleBatchOrderNo: Order is not in GoodState when trying to put batchorderno in PXVBOrderHeader::setPrewholesaleBatchOrderNo");
                    }
                }
                m_PXVBDBConnection->commitTransaction( MULTI_RECORD );
            }
            catch( ... )
            {
                m_Logger->log(log4cplus::ERROR_LOG_LEVEL, "caught generic exception in PXVBOrderHeader::setPrewholesaleBatchOrderNo");
                m_PXVBDBConnection->rollbackTransaction();
            }
        }
        else
        {
            m_Logger->log( log4cplus::INFO_LOG_LEVEL, "setPrewholesaleBatchOrderNo: BatchOrderNo already available." );
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderHeader::initSerbianSpecific()
    {
        METHODNAME_DEF( PXVBOrderHeader, initSerbianSpecific );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if (!m_PXVBSession->get()->isSerbia())
        {
            return;
        }

        // link for proforma invoice
        {
            m_pxOrderProLink = ::pxOrderProLinkPtr( new ::pxOrderProLink( m_PXVBSession->get(), getOrder()->KdAuftragNr() ) );
            if( m_pxOrderProLink->Get() )
            {
                m_pxOrderProLink.reset();
            }
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderHeader::init()
    {
        METHODNAME_DEF( PXVBOrderHeader, initialize );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        determineOrderType();
        initCountrySpecific();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderHeader::determineOrderType()
    {
        METHODNAME_DEF( PXVBOrderHeader, determineOrderType );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        getOrder()->OrderType( getOrder()->KdAuftragArt(), getOrder()->KoArt(), getOrder()->BuchArt() );
        if( !getOrder()->IsGoodState() )
        {
            m_PXVBDBConnection->beginTransaction( SINGLE_RECORD );
            ::pxOrder order( m_PXVBSession->get(), getOrder()->KdAuftragNr(), cDBGET_FORUPDATE );
            if( order.IsGoodState() )
            {
                nMessage msg( order.CMsgStream(), CMSG_ORD_TYPE_CUST, (char*)order.KdAuftragArt(), order.IDFNr() );
                nString ordermsg = msg.String();
                ordermsg.Compress('\n');
                order.Bemerkungen(ordermsg);
                order.OrderStatus(Order::EntryDeferred);
                order.OrderStatus(Order::ProblemClearance);
            }
            order.VSEPut();
            if( order.IsGoodState() )
            {
                m_PXVBDBConnection->commitTransaction( SINGLE_RECORD );
            }
            m_OrderTypeValid = false;
        }
        m_OrderTypeValid = true;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    basar::Int16 PXVBOrderHeader::getNumberOfDiscountRecords()
    {
        // TODO HR-08 -> return number of discount records for the current order (kdauftrag)
        basar::Int16 countDiscounts = 0;

        libcsc::discount::OrderPositionDiscountListPtr discountList = getOrder()->getDiscountList();
        libcsc::discount::OrderPositionDiscountList::const_iterator iter = discountList->begin();
        for( ; iter != discountList->end(); ++iter )
        {
            libcsc::discount::OrderPositionDiscountPtr discount( *iter );
            switch( discount->getDiscountMode() )
            {
                case libcsc::discount::DM_WHOLESALE_REBATE_IN_KIND_MODE:
                case libcsc::discount::DM_WHOLESALE_INDUSTRY_REBATE_IN_KIND_MODE:
                    // ignore rubber ducks
                    break;

                default:
                    if (0 == discount->getPositionNo())
                        ++countDiscounts;

                    break;
            }
        }

        return countDiscounts;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    bool PXVBOrderHeader::isOrderTypeValid()
    {
        METHODNAME_DEF( PXVBOrderHeader, isOrderTypeCombinationValid );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_OrderTypeValid;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxOrder* PXVBOrderHeader::getOrder()
    {
        METHODNAME_DEF( PXVBOrderHeader, getOrder );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_pxOrder;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxTextDoc* PXVBOrderHeader::getHeadText()
    {
        METHODNAME_DEF( PXVBOrderHeader, getHeadText );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return getOrder()->HeadText();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxTextDoc* PXVBOrderHeader::getFooterText()
    {
        METHODNAME_DEF( PXVBOrderHeader, getFooterText );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return getOrder()->TailText();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxCustOrderInfoPtr PXVBOrderHeader::getOrderInfo()
    {
        METHODNAME_DEF( PXVBOrderHeader, getOrderInfo );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( 0 == m_pxCustOrderInfo.get() )
        {
            m_pxCustOrderInfo = ::pxCustOrderInfoPtr( new ::pxCustOrderInfo( m_PXVBSession->get(), getOrder()->KdAuftragNr() ) );
            /* CHECK_WITH_YSI
                Tue Oct 23 12:05:17 2012
                STATUS : nSTATE_CONDITION
                MESSAGE_ID : 69001   DEVICE : CORPHA
                EINTRAG FUER AUFTRAGNUMMER 16248 NICHT GEFUNDEN.
            */
        }

        if( !m_pxCustOrderInfo->IsGoodState() )
        {
            m_pxCustOrderInfo.reset();
            return m_pxCustOrderInfo;
        }

        if( !getOrder()->Customer()->Flags().IsMehrfachBestell() )
        {
            m_pxCustOrderInfo->CheckMembers();
        }

        return m_pxCustOrderInfo;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxOrderDiscAccPtr PXVBOrderHeader::getOrderDiscountAccount()
    {
        METHODNAME_DEF( PXVBOrderHeader, getOrderDiscountAccount );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_pxOrderDiscAcc;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxOrderCalcModePtr PXVBOrderHeader::getOrderCalcMode()
    {
        METHODNAME_DEF( PXVBOrderHeader, getOrderCalcMode );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_pxOrderCalcMode;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxOrderProLinkPtr PXVBOrderHeader::getOrderProLink()
    {
        METHODNAME_DEF( PXVBOrderHeader, getOrderProLink );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_pxOrderProLink;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    bool PXVBOrderHeader::isCalcExpressCharge()
    {
        METHODNAME_DEF( PXVBOrderHeader, getOrderValidTrans );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        short pickingtype = getOrder()->KoArt() - '0';
        short bookingtype = getOrder()->BuchArt() - '0';

        pxOrderValidTrans* vtran = m_PXVBSession->get()->OrderValidTransList( this->getOrder()->Vertriebszentrum() )->Find( *(this->getOrder()->Customer()), this->getOrder()->KdAuftragArt(), pickingtype, bookingtype );
        if( !vtran )
        {
            m_Logger->log(log4cplus::ERROR_LOG_LEVEL, "PXVBOrderHeader::isCalcExpressCharge failed! No valid pxOrderValidTrans found!");
            return false;
        }

        if( true == vtran->isCalcExpressDeliveryCharge() )
        {
            // SR-15071807: Kennzeichen Eilbotengebühr nur im Originalauftrag setzen (Nicht in abgesplitteten Aufträgen)
            if( this->getOrder()->KdAuftragNrOrg() > 0 && this->getOrder()->KdAuftragNrOrg() != this->getOrder()->KdAuftragNr() )
            {
                m_Logger->log(log4cplus::INFO_LOG_LEVEL, "PXVBOrderHeader::isCalcExpressCharge - no urgent delivery charge due to kdauftragnrorg!");
                return false;
            }

            if( this->getOrder()->IsSeparateArtGroup() )
            {
                m_Logger->log(log4cplus::INFO_LOG_LEVEL, "PXVBOrderHeader::isCalcExpressCharge - no urgent delivery charge due to IsSeparateArtGroup!");
                return false;
            }
            else
            {
                m_Logger->log(log4cplus::INFO_LOG_LEVEL, "PXVBOrderHeader::isCalcExpressCharge - IsSeparateArtGroup not set!");
            }

            if( this->getOrder()->IsSeparatedOrder() )
            {
                m_Logger->log(log4cplus::INFO_LOG_LEVEL, "PXVBOrderHeader::isCalcExpressCharge - no urgent delivery charge due to IsSeparatedOrder!");
                return false;
            }
            else
            {
                m_Logger->log(log4cplus::INFO_LOG_LEVEL, "PXVBOrderHeader::isCalcExpressCharge - IsSeparatedOrder not set!");
            }

            m_Logger->log(log4cplus::INFO_LOG_LEVEL, "PXVBOrderHeader::isCalcExpressCharge -> TRUE!");
            return true;
        }
        return false;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    // TODO HR-08 -> method to get new discount list into member from pxverbund for order
    libcsc::discount::OrderPositionDiscountListPtr PXVBOrderHeader::getNewDiscountList()
    {
        return getOrder()->getDiscountList();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    /*  // TODO HR-08 -> method to get iterator for new discount list
    ::pxNewDiscountListIter PXVBOrderHeader::getNewDiscountListIter()
    {
        ::pxNewDiscountListIter retval = ::pxNewDiscountListIter(*getNewDiscountList());
        return retval;
    }
    */
    //----------------------------------------------------------------------------//

} // namespace pxVerbund
} // namespace corpha
} // namespace domMod
