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
#include <libbasarcmnutil_datetime.h>

#include "pxvborderdm.h"
#include "pxvborderdm_definitions.h"
#include "pxvbdbconnection.h"
#include "pxvbdbconnection_definitions.h"
#include "pxvbsession.h"
#include "pxvborderentryparamchecker.h"
#include "pxvborderheader.h"
#include "pxvborderitem.h"
#include "pxvborderdm_definitions.h"
#include "recordtypecollection.h"
#include "recordtypeorderresponse.h"

#include "pxartbaseptr.h"
#include <pxcstbas.hpp>
#include <pxstockbooking.hpp>
#include <articleaccountinfo.hpp>
#include <pxordevt.hpp>
#include <pxordervalues.hpp>
#include <pxarticlecodes.hpp>
#include <pxcstot.hpp>
#include <pxcomtyp.hpp>
#include <pxstktra.hpp>

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
    PXVBOrderDM::PXVBOrderDM( ::pxOrder* order )
    {
        m_PXVBOrderHeader = PXVBOrderHeaderPtr( new PXVBOrderHeader( order ) );
        setTime();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    PXVBOrderDM::~PXVBOrderDM()
    {
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::finishWithoutTransfer()
    {
        METHODNAME_DEF( PXVBOrderDM, finishWithoutTransfer );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( 0 == getOrderHeader()->getOrder()->AnzPos() )
        {
            try
            {
                m_PXVBDBConnection->beginTransaction( SINGLE_RECORD );

                pxOrder order( m_PXVBSession->get(), getOrderHeader()->getOrder()->KdAuftragNr(), cDBGET_FORUPDATE );
                if( order.IsGoodState() )
                {
                    order.OrderStatus( Order::Invoiceable );
                    order.OrderStatus( Order::Invoiced );
                    order.SendeStatus( pxOrder::cVSEok );
                }
                order.VSEPut();
                if( order.IsGoodState() )
                {
                    m_PXVBDBConnection->commitTransaction( SINGLE_RECORD );
                }
                else
                {
                    basar::VarString msg;
                    msg.format("could not finish order %ld without transfer: order not in good state after put", getOrderHeader()->getOrder()->KdAuftragNr());
                    m_Logger->log(log4cplus::ERROR_LOG_LEVEL, msg);

                    m_PXVBDBConnection->rollbackTransaction();
                }
            }
            catch(...)
            {
                m_PXVBDBConnection->rollbackTransaction();
            }
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::finishTransfer( domMod::corpha::recordtypes::RecordTypeCollectionPtr collection )
    {
        METHODNAME_DEF( PXVBOrderDM, finishTransfer );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        try
        {
            int A1_Processed = 0;
            int P1_Processed = 0;
            int S1_Processed = 0;
            m_PXVBDBConnection->beginTransaction( MULTI_RECORD );
            pxOrder order( m_PXVBSession->get(), collection->getCSCOrderNo(), cDBGET_FORUPDATE );
            order.OrderType( order.KdAuftragArt(), order.KoArt(), order.BuchArt() );
            while( !collection->isEmpty() )
            {
                recordtypes::RecordTypeBasePtr record = collection->getRecord();
                if( order.IsGoodState() )
                {
                    recordtypes::RecordType rectype = processResponseRecord( order, record, collection->getCSCOrderNo() );
                    switch (rectype)
                    {
                        case recordtypes::A1: A1_Processed++; break;
                        case recordtypes::P1: P1_Processed++; break;
                        case recordtypes::S1: S1_Processed++; break;
                        case recordtypes::UNKNOWN:
                        default:                              break;
                    }
                }
            }
            if (0 == A1_Processed && 0 == S1_Processed)
            {
                // do nothing, retry later to transfer
            }
            else if (0 == A1_Processed && 0 < S1_Processed)
            {
                order.SendeStatus(pxOrder::cVSEAnyErr);
                std::stringstream s;
                s << "Order <" << order.KdAuftragNr() << ">: No A1 record found! set error state!";
                m_Logger->log(log4cplus::ERROR_LOG_LEVEL, s.str());

                pxOrderEvent event( order, Order::OrderSendCancel );
                event.Put();
            }
            else
            {
                pxOrderEvent event( order, Order::OrderSendEnd );
                event.Put();
            }
            order.VSEPut();
            m_PXVBDBConnection->commitTransaction( MULTI_RECORD );
        }
        catch(...)
        {
            m_Logger->log(log4cplus::ERROR_LOG_LEVEL, "caught generic exception in PXVBOrderDM::finishTransfer");
            m_PXVBDBConnection->rollbackTransaction();
        }

    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    recordtypes::RecordType PXVBOrderDM::processResponseRecord( pxOrder& order, const recordtypes::RecordTypeBasePtr record, const basar::Long64 orderno )
    {
        METHODNAME_DEF( PXVBOrderDM, processResponseRecord );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );
        (void) orderno;

        domMod::corpha::recordtypes::OrderResponseValues values = record->deserialize();

        //basar::VarString msg;
        //msg.format("Got answer from Cics, Values are: RecordType: %s (%d), CSCOrderNo: %ld, CSCOrderLineNo: %ld, PharmosOrderNo: %ld, Status: %ld, DeliveryQty: %ld",
        //  values.RecType.c_str(), values.Type, values.CSCOrderNo, values.CSCOrderLineNo, values.PharmosOrderNo, values.Status, values.DeliveryQty);
        //m_Logger->log(log4cplus::INFO_LOG_LEVEL, msg);

        switch( values.Type )
        {
            case domMod::corpha::recordtypes::A1:
                processResponseRecordA1( order, values );
                return domMod::corpha::recordtypes::A1;
            case domMod::corpha::recordtypes::P1:
                processResponseRecordP1( order, values );
                return domMod::corpha::recordtypes::P1;
            case domMod::corpha::recordtypes::S1:
                processResponseRecordS1( order, values );
                return domMod::corpha::recordtypes::S1;
            default:
                break;
        }
        return domMod::corpha::recordtypes::UNKNOWN;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::processResponseRecordA1( pxOrder& order, const domMod::corpha::recordtypes::OrderResponseValues& values )
    {
        METHODNAME_DEF( PXVBOrderDM, processResponseRecordA1 );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        basar::VarString logmessage("");
        logmessage.format( "%s   -> OrderTransferResponse A1 received PharmosOrderNo: %ld | Status: %ld", getLogDetails( order ).c_str(), values.PharmosOrderNo, values.Status );
        m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );

        order.OrderType( order.KdAuftragArt(), order.KoArt(), order.BuchArt() );
        order.VSEAuftragNr( values.PharmosOrderNo );
        switch( values.Status )
        {
            case 0:
                order.SendeStatus( pxOrder::cVSEAnyErr );
                logmessage.format( "%s   -> ResponseRecord A1 has Status 0: VSEAnyError", getLogDetails( order ).c_str() );
                m_Logger->log( log4cplus::WARN_LOG_LEVEL, logmessage );
                break;
            case 1:
                order.SendeStatus( pxOrder::cVSEok );
                break;
            case 3:
                order.Bemerkungen( "Kunde auf VSE nicht gefunden" );
                order.OrderStatus( Order::EntryDeferred );
                order.OrderStatus( Order::ProblemClearance );
                order.SendeStatus( pxOrder::cVSEnoTransmit );
                logmessage.format( "%s   -> ResponseRecord A1 has Status 3: Customer not available in PHARMOS", getLogDetails( order ).c_str() );
                m_Logger->log( log4cplus::WARN_LOG_LEVEL, logmessage );
                break;
            case 4:
                order.Bemerkungen( "Tour auf VSE nicht gefunden" );
                order.SendeStatus( pxOrder::cVSETidErr );
                logmessage.format( "%s   -> ResponseRecord A1 has Status 4: Tour not available in PHARMOS", getLogDetails( order ).c_str() );
                m_Logger->log( log4cplus::WARN_LOG_LEVEL, logmessage );
                break;
            case 5:
                order.Bemerkungen( "Auftrag auf VSE schon vorhanden" );
                order.SendeStatus( pxOrder::cVSEKdbErr );
                logmessage.format( "%s   -> ResponseRecord A1 has Status 4: Order already available in PHARMOS", getLogDetails( order ).c_str() );
                m_Logger->log( log4cplus::WARN_LOG_LEVEL, logmessage );
                break;
            case 8:
                order.SendeStatus( pxOrder::cVSEAnyErr );
                logmessage.format( "%s   -> ResponseRecord A1 has Status 8: VSEAnyError", getLogDetails(order).c_str() );
                m_Logger->log( log4cplus::ERROR_LOG_LEVEL, logmessage );
                break;
            case 9:
                order.SendeStatus( pxOrder::cVSEok );
                break;
            default:
                order.SendeStatus( pxOrder::cVSEAnyErr );
                logmessage.format( "%s   -> ResponseRecord A1 has Status default: VSEAnyError", getLogDetails(order).c_str() );
                m_Logger->log( log4cplus::WARN_LOG_LEVEL, logmessage );
                break;
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::processResponseRecordP1( pxOrder& order, const domMod::corpha::recordtypes::OrderResponseValues& values )
    {
        METHODNAME_DEF( PXVBOrderDM, processResponseRecordP1 );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        basar::VarString logmessage("");
        logmessage.format( "%s   -> OrderTransferResponse P1 received Status: %ld | OrderLine: %ld | Qty: %ld",
                            getLogDetails(order).c_str(), values.Status, values.CSCOrderLineNo, values.DeliveryQty );
        m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );

        pxOrderItem orderitem( order, values.CSCOrderLineNo );
        if( !orderitem.IsGoodState() )
        {
            basar::VarString msg("");
            msg.format("%s   -> found no OrderItem - Status: %ld | OrderLine: %ld",
                getLogDetails(order).c_str(), values.Status, values.CSCOrderLineNo);
            m_Logger->log( log4cplus::INFO_LOG_LEVEL, msg.c_str() );
        }
        else
        {
            orderitem.Get( cDBGET_FORUPDATE );
            struct ArticleAccountInfo info;
            info.PurchaseOrderNo    = orderitem.Order().KdAuftragNr();
            info.PositionNo         = orderitem.PosNr();
            info.CustomerSupplierNo = orderitem.Order().Customer()->IDFNr();
            info.StockTransaction   = orderitem.Order().StockTrans().StockTransactionCode();
            info.CommiType          = orderitem.Order().CommType().ShipCode();
            switch( values.Status )
            {
                case 1: // DKART not available for this article
                    {
                        m_PXVBSession->get()->getStockBooking()->AddQtyInStock(*orderitem.ArtBase(), orderitem.MengeAbgebucht(), TRANSACTIONTYPE_VSEAMOUNT, &info);
                        orderitem.MengeGeliefert( 0 );
                        orderitem.MengeAbgebucht( 0 );
                        orderitem.SendeStatus( pxOrderItem::cVSEArtErr );
                        updateNarcoticsTransfer( orderitem );
                        long qtyInStock = m_PXVBSession->get()->getStockBooking()->GetAvailableQtyInStock(*orderitem.ArtBase());
                        pxStockRev stockrev( m_PXVBSession->get(), order.FilialNr(), orderitem.ArtikelNr(), qtyInStock, 0L );
                        break;
                    }

                case 2: // stock difference between PHARMOS and KSC, set stop selling for article
                case 3: // stock difference between PHARMOS and KSC, don´t set stop selling for article
                    {
                        m_PXVBSession->get()->getStockBooking()->AddQtyInStock(*orderitem.ArtBase(), values.DeliveryQty, TRANSACTIONTYPE_VSEAMOUNT, &info);
                        if( 2 == values.Status )
                        {
                            orderitem.ArtBase()->StopSelling();
                        }

                        orderitem.MengeGeliefert( orderitem.MengeGeliefert() - values.DeliveryQty );
                        if( orderitem.MengeGeliefert() < 0 ) orderitem.MengeGeliefert(0);

                        orderitem.MengeAbgebucht( orderitem.MengeAbgebucht() - values.DeliveryQty );
                        if( orderitem.MengeAbgebucht() < 0 ) orderitem.MengeAbgebucht(0);

                        orderitem.MengeBestaetigt( orderitem.MengeBestaetigt() - values.DeliveryQty );
                        if( orderitem.MengeBestaetigt() < 0 ) orderitem.MengeBestaetigt(0);

                        if( orderitem.MengeNatra() > orderitem.MengeGeliefert() )
                        {
                            orderitem.MengeNatra( orderitem.MengeGeliefert() );
                        }

                        updateNarcoticsTransfer( orderitem );
                        orderitem.SendeStatus( pxOrderItem::cVSEBstErr );
                        order.SendeStatus( pxOrder::cVSEPosErr );
                        long qtyInStock = m_PXVBSession->get()->getStockBooking()->GetAvailableQtyInStock(*orderitem.ArtBase());
                        pxStockRev stockrev( m_PXVBSession->get(), order.FilialNr(), orderitem.ArtikelNr(), qtyInStock, (qtyInStock - values.DeliveryQty) );

                        pxOrderPosChange poschange( m_PXVBSession->get(), order.KdAuftragNr(), orderitem.PosNr() );
                        poschange.SetMengeBestellt( orderitem.MengeBestellt() );
                        poschange.SetMengeBestaetigt( orderitem.MengeBestaetigt() );
                        poschange.SetMengeAlt( orderitem.MengeBestaetigt() + values.DeliveryQty );
                        poschange.SetSWChecked( '0' );
                        poschange.Put();

                        if( m_PXVBSession->get()->isBulgaria() )
                        {
                            pxOrderValues ordervalues( m_PXVBSession->get(), order.KdAuftragNr() );
                            if( !ordervalues.Get( cDBGET_FORUPDATE ) )
                            {
                                ordervalues.ReduceOrderValues( &orderitem, values.DeliveryQty );
                                ordervalues.Put();
                            }
                        }
                        orderitem.ArtBase()->Put();
                        break;
                    }

                default:
                    {
                        orderitem.SendeStatus( pxOrderItem::cVSEAnyErr );
                        break;
                    }
            }
            orderitem.Put();
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::processResponseRecordS1( pxOrder& order, const domMod::corpha::recordtypes::OrderResponseValues& values )
    {
        METHODNAME_DEF( PXVBOrderDM, processResponseRecordS1 );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        basar::VarString logmessage("");
        logmessage.format( "%s   -> OrderTransferResponse S1 received. Status: %d ", getLogDetails(order).c_str(), values.Status );
        m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );

        if( 0 == values.Status ) // error
        {
            throw; // ROLLBACK
        }
        else if( 9 == values.Status ) // order cancelled
        {
            throw; // ROLLBACK
        }
        else
        {
            order.VSEAuftragNr( values.PharmosOrderNo ); // in case of missing A1 record!
            switch( order.SendeStatus() )
            {
                case pxOrder::cVSEok:           // 1 order on VSE OK
                case pxOrder::cVSEPosErr:       // 2 order transmitted but q-difference
                case pxOrder::cVSETidErr:       // 4 order on VSE but tourid error
                case pxOrder::cVSEKdbErr:       // 5 order was already on VSE
                    {
                        if( order.IsInvoiceable() )
                        {
                            order.OrderStatus( Order::Invoiced );
                        }
                        else
                        {
                            order.OrderStatus( Order::ShipmentInProgress );
                            order.OrderStatus( Order::ShipmentClosed );
                            order.OrderStatus( Order::Invoiceable );
                            order.OrderStatus( Order::Invoiced );
                        }
                    }
                    break;
                default:
                    break;
            }

            completeNarcoticsTransfer( order, values.PharmosOrderNo );
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::completeNarcoticsTransfer( pxOrder& order, basar::Long64 pharmosorderno )
    {
        METHODNAME_DEF( PXVBOrderDM, completeNarcoticsTransfer );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( m_PXVBOrderEntryParamChecker->checkNarcoticsTransfer() )
        {
            basar::VarString logmessage("");
            logmessage.format( "%s   -> CompleteNarcTransferEntries for PharmosOrderNo: %d ", getLogDetails(order).c_str(), pharmosorderno );
            m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );

            order.CompleteNarcTransferEntries(pharmosorderno);
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::updateNarcoticsTransfer( pxOrderItem& item )
    {
        METHODNAME_DEF( PXVBOrderDM, updateNarcoticsTransfer );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( item.ArtBase()->ArtClass().IsOpiat() && m_PXVBOrderEntryParamChecker->checkNarcoticsTransfer() )
        {
            item.DeleteNarcTransfer();
            item.InsertNarcTransfer();
            basar::VarString logmessage("");
            logmessage.format( "%s   -> NarcoticsTransfer: ArticleNo: %d ", getLogDetails( item.Order() ).c_str(), item.ArtikelNr() );
            m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::injectLogger( libcsc_utils::ICSC_LoggerPtr logger )
    {
        METHODNAME_DEF( PXVBOrderDM, injectLogger ); (void) fun; // logger not yet available

        m_Logger = logger;
        getOrderHeader()->injectLogger( logger );
        m_PackageLabelCollection.injectLogger( logger );
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::injectPXVBDBConnection( pxVerbund::IPXVBDBConnectionPtr conn )
    {
        METHODNAME_DEF( PXVBOrderDM, injectPXVBDBConnection ); (void) fun;  // logger not yet available

        m_PXVBDBConnection = conn;
        getOrderHeader()->injectPXVBDBConnection( conn );
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::injectPXVBSession( pxVerbund::IPXVBSessionPtr sess )
    {
        METHODNAME_DEF( PXVBOrderDM, injectPXVBSession ); (void) fun;  // logger not yet available

        m_PXVBSession = sess;
        getOrderHeader()->injectPXVBSession( sess );
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::injectPXVBOrderEntryParamChecker( pxVerbund::IPXVBOrderEntryParamCheckerPtr oeparam )
    {
        METHODNAME_DEF( PXVBOrderDM, injectPXVBOrderEntryParamChecker ); (void) fun; // logger not yet available

        m_PXVBOrderEntryParamChecker = oeparam;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    bool PXVBOrderDM::isMSV3Order()
    {
        METHODNAME_DEF(PXVBOrderDM, isMSV3Order);
        BLOG_TRACE_METHOD(m_Logger->getLogger(), fun);

        if (!getOrderHeader()->getOrder()->German())
        {
            return false;
        }
        return hasOrderLabel();
    }

    bool PXVBOrderDM::isSwimpATOrder()
    {
        METHODNAME_DEF(PXVBOrderDM, isSwimpATOrder);
        BLOG_TRACE_METHOD(m_Logger->getLogger(), fun);

        if (!getOrderHeader()->getOrder()->Austria())
        {
            return false;
        }
        return hasOrderLabel();
    }

    bool PXVBOrderDM::hasOrderLabel()
    {
        basar::VarString orderlabel = basar::VarString(getOrderHeader()->getOrder()->OrderLabel()());
        orderlabel.trim(basar::cmnutil::BString::FIRST_END);
        return orderlabel == "" ? false : true;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    bool PXVBOrderDM::hasOrderTypeWithPackageLabels()
    {
        METHODNAME_DEF( PXVBOrderDM, hasOrderTypeWithPackageLabels );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        bool retval = false;
        if( ORDERTYPE_WEBSHOP == getOrderHeader()->getOrder()->KdAuftragArt()() )
        {
            retval = true;
        }
        return retval;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    bool PXVBOrderDM::hasToBeTransferred()
    {
        METHODNAME_DEF( PXVBOrderDM, checkOrderTransfer );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        if( !getOrderHeader()->isOrderTypeValid() )
        {
            basar::VarString logmessage("");
            logmessage.format( "%s   -> no OrderTransfer due to OrderType", getLogDetails().c_str() );
            m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );
            return false;
        }

        if( 0 == getOrderHeader()->getOrder()->AnzPos() )
        {
            basar::VarString logmessage("");
            logmessage.format( "%s   -> no OrderTransfer due to AnzPos", getLogDetails().c_str() );
            m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );
            return false;
        }

        return true;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    basar::Long64 PXVBOrderDM::getTime()
    {
        METHODNAME_DEF( PXVBOrderDM, getTime );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_Time;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::setTime()
    {
        METHODNAME_DEF( PXVBOrderDM, setTime ); (void) fun; // logger not yet available

        m_Time = basar::DateTime::getCurrent().getTime();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::setEventOrderTransferStarted()
    {
        METHODNAME_DEF( PXVBOrderDM, setEventOrderTransferStarted );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        basar::VarString logmessage("");
        logmessage.format( "%s -> startOrderTransfer Lines: %d (Time: %d)", getLogDetails().c_str(), getOrderHeader()->getOrder()->AnzPos(), m_Time );
        m_Logger->log( log4cplus::INFO_LOG_LEVEL, logmessage.c_str() );

        pxOrderEvent event( *(getOrderHeader()->getOrder()), Order::OrderSendStart );
        event.Put();


    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::shutdown()
    {
        METHODNAME_DEF( PXVBOrderDM, shutdown );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        try
        {
            delete m_pxOrderItemList;
        }
        catch( ... )
        {
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::init()
    {
        METHODNAME_DEF( PXVBOrderDM, initialize );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        getOrderHeader()->init();
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    pxVerbund::PXVBOrderHeaderPtr PXVBOrderDM::getOrderHeader()
    {
        METHODNAME_DEF( PXVBOrderDM, getOrderHeader );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        return m_PXVBOrderHeader;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    void PXVBOrderDM::checkArticleCode( ::pxOrderItem* item )
    {
        METHODNAME_DEF( PXVBOrderDM, checkArticleCode );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        pxArticleCodes* ArticleCode = NULL;
        nString articlecode;

        articlecode = item->ArticleCode();
        articlecode.Strip();
        if( "" == articlecode )
        {
            if( 0 != item->ArtikelNr() )
            {
                ArticleCode = item->GetArticleCode( item->ArtikelNr() );
                if( ArticleCode )
                {
                    item->SetArticleCodeValues( ArticleCode->CodeType(), ArticleCode->ArticleCode() );
                    item->Put();
                    delete ArticleCode;
                }
            }
        }
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    pxVerbund::PXVBOrderItemPtr PXVBOrderDM::createOrderItem( ::pxOrderItem* item )
    {
        METHODNAME_DEF( PXVBOrderDM, createOrderItem );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        pxVerbund::PXVBOrderItemPtr retval( new pxVerbund::PXVBOrderItem( getOrderHeader()->getOrder(), item ) );
        retval->injectPXVBSession( m_PXVBSession );
        retval->injectPXVBOrderEntryParamChecker( m_PXVBOrderEntryParamChecker );
        retval->injectLogger( m_Logger );
        retval->init();

        checkArticleCode( item );
        return retval;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    ::pxOrderItemListIter PXVBOrderDM::getOrderItemIterator()
    {
        METHODNAME_DEF( PXVBOrderDM, getOrderItems );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        m_pxOrderItemList = new ::pxOrderItemList( m_PXVBSession->get() );
        m_pxOrderItemList->Select( getOrderHeader()->getOrder()->KdAuftragNr() );
        ::pxOrderItemListIter retval = ::pxOrderItemListIter( *m_pxOrderItemList );
        return retval;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    basar::VarString PXVBOrderDM::getLogDetails( pxOrder& order )
    {
        METHODNAME_DEF( PXVBOrderDM, getLogDetails );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        basar::VarString retval("");
        retval.format( "<%d>|<%d>|", order.FilialNr(), order.KdAuftragNr() );

        return retval;
    }
    //----------------------------------------------------------------------------//

    //----------------------------------------------------------------------------//
    basar::VarString PXVBOrderDM::getLogDetails()
    {
        METHODNAME_DEF( PXVBOrderDM, getLogDetails );
        BLOG_TRACE_METHOD( m_Logger->getLogger(), fun );

        basar::VarString retval("");
        retval.format( "<%d>|<%d>|", getOrderHeader()->getOrder()->FilialNr(), getOrderHeader()->getOrder()->KdAuftragNr() );

        return retval;
    }
    //----------------------------------------------------------------------------//

} // namespace pxVerbund
} // namespace corpha
} // namespace domMod
