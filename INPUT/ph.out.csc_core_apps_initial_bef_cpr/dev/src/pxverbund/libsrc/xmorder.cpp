#include "pxxmit.hpp"
#include "pxholiday.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"
#include "pxtxtdoc.hpp"
#include "pxoeparm.hpp"
#include "pxcstbas.hpp"
#include "pxcstot.hpp"
#include "pxcustomerflags.hpp"
#include "pxordvtr.hpp"
#include "pxbranch.hpp"
#include "pxorder.hpp"
#include "pxorderperiod.hpp"
#include "pxbase/pxconstants.hpp"
#include "tourassignmentutil.hpp"
#include "pxparameter.hpp"
//#include "logger/loggerpool.h"

/*----------------------------------------------------------------------------*/
/*  Customer identification.                                                  */
/*----------------------------------------------------------------------------*/
pxCustBase*
pxOrderTransmit :: CustomerId
(
    const long customerid,
    const short   vz
)
{
    if ( vz > 0 )
    {
        Customer_ = new pxCustBase(Session(), vz, customerid);
    }
    else
    {
        Customer_ = new pxCustBase(Session(), Branch()->FilialNr(), customerid);
    }

    Error() = (Customer_->Error());     // copy error object contents
    if ( !IsGoodState() )
    {                                   // then could not find customer
        delete Customer_;               // delete object
        Customer_ = NULL;
    }
    else
    {
        if ( Customer_->Flags().IsKundeGesperrt() )
        {
            ExternalCondition(CMsgStream(), CMSG_CST_BLOCKED_FOR_ORDERENTRY, Customer_->IDFNr(), Customer_->Vertriebszentrum());

            delete Customer_;             // delete object
            Customer_ = NULL;
        }
        else
            ActiveOrders_ = new pxOrderList(Session());
    }

    return Customer_;
}

/*----------------------------------------------------------------------------*/
/*  Set order type.                                                           */
/*  In case of an order type change and having no order of that type linked   */
/*  with the order list, a new order is created and appended to the list.     */
/*  In case of an invalid order type, the default order transaction type is   */
/*  assigned. However, if no default values could be assigned, the current    */
/*  order will remain the current one. Due to this behaviour, at least a      */
/*  valid transaction type must be available or an order might NEVER be       */
/*  constructed.                                                              */
/*----------------------------------------------------------------------------*/
// von dafue aufgerufen
pxOrder*
pxOrderTransmit :: OrderType
(
    const nString& type,
    const nString& number,
    const int      kommityp,
    const int      bookingtyp,
    const OriginTypeEnum batchschreiben,
    const short    options,
    const nString& desiredTour,
    const nDate&   desiredTourDate
)
{
    nDate now;
    nString s(type);
    long num = atol( number );
    num = ( (num < 0 || num > 35 ) ? 1 : num );
    short  VZ = Customer_->Vertriebszentrum();
    long MaxPosAuftrag = 0;
    MaxPosAuftrag = ( Order_ == NULL ) ? 0 : Order_->Param()->MaxPosAuftrag();
    pxHoliDayList* holidaylist = Session()->HoliDayList(VZ);

    if ( Session()->isBulgaria() )
    {
        MaxPosAuftrag = 0;                             // it will be used later on
    }

    pxOrderType  otp(Session(), s);
    pxOrderValidTrans *vtp =
    Session()->OrderValidTransList(VZ)->Find(*Customer_, s, kommityp - '0', bookingtyp - '0');
    if ( ! vtp )                        // this is an invalid order type
    {
        ExternalError(CMsgStream(), CMSG_ORD_TYPE_COMB, (char*)type, (int)kommityp, (int)bookingtyp); // siehe messgaecodeenum.inc & message.txt [30 00700]
        return Order_;
        //s.Clear();                      // will find the default order transaction
        //vtp = Session()->OrderValidTransList(VZ)->Find(*Customer_, s);
    }

    if ( vtp )                          // ensure transaction type is valid
    {                                   // avoid unneccessary order swaps:
        if (   (Order_ == NULL)
            || (Order_->KdAuftragArt() != vtp->KdAuftragArt())
            || (IsOrderSplit() && Order_->DafueAuftragNr() != num)
            || (MaxPosAuftrag > 0 && Order_->AnzPos() == MaxPosAuftrag )
            || (IsOrderConsolidation() && Order_->CloseOptions() != options )
            || (IsSplitOrderOnTens() && otp.IsTens() && Order_->CloseOptions() != options ) )
        {
            Order_ = GetOrder(vtp, num, batchschreiben, options, desiredTour, desiredTourDate);  // must get a new current order
            if ( Order_ )
                Order_->CloseOptions( options);
        }
    }

/*----------------------------------------------------------------------------*/
/*  Set type of order. Usual the type of order is set during                  */
/*  EndOffTransmission, but to complete an Orderitem we have to now, what     */
/*  type of transmission is currently running.                                */
/*----------------------------------------------------------------------------*/
    if ( Order_ )
    {
        short DelayedDays = Order_->Param()->DelayedDays();
        const pxCustOrderType& ot = Order_->OrderType();
        if ( Order_->OrderType().IsDelayedDelivery() )
        {
            if ( !Order_->IsVerzoegerAusgeliefert())
            {
                if ( Order_->DatumAuslieferung() == pxConstants::NullDate )
                Order_->DatumAuslieferung( nDate(holidaylist->CalculateNextWorkDay(now,VZ)) );
                Order_->SetDDNotClose();
                Order_->SetVerzoegerAusgeliefert();
            }
        }
        if ( Order_->TourId().IsEmpty() )
        {
            Order_->RouteAssign();
        }

        if ( DelayedDays > 0 )  // Ivrylab  but not for branch 49
        {
            if ( !(ot.IsCollectiveOrder()) )
            {
                if ( Order_->DatumAuslieferung() == pxConstants::NullDate )
                {
                    if ( DeliveryDate() != 0L )
                    {
                        Order_->DatumAuslieferung( nDate(DeliveryDate()) );
                    }
                    else
                    {
                        Order_->DatumAuslieferung( nDate(holidaylist->CalculateNextWorkDay(((now + DelayedDays) - 1), VZ)) );
                    }
                }
            }
        }
    }

    return Order_;
}

/*----------------------------------------------------------------------------*/
/*  Set order type.                                                           */
/*  In case of an order type change and having no order of that type linked   */
/*  with the order list, a new order is created and appended to the list.     */
/*  In case of an invalid order type, the default order transaction type is   */
/*  assigned. However, if no default values could be assigned, the current    */
/*  order will remain the current one. Due to this behaviour, at least a      */
/*  valid transaction type must be available or an order might NEVER be       */
/*  constructed.                                                              */
/*----------------------------------------------------------------------------*/
// vom ksc-server aufgerufen
pxOrder*
pxOrderTransmit :: OrderType
(
    const nString& type,
    const long     number,
    const int      kommityp,
    const int      bookingtyp,
    const OriginTypeEnum batchschreiben,
    const short    options
)
{
    nDate now;
    nString s(type);
    long num =  number;
    short  VZ = Customer_->Vertriebszentrum();
    nString csubot;
    nString cpaymentterm;
    long MaxPosAuftrag = 0;
    MaxPosAuftrag = ( Order_ == NULL ) ? 0 : Order_->Param()->MaxPosAuftrag();
    if ( Session()->isBulgaria() )
    {
        MaxPosAuftrag = 0;                             // it will be used later on
    }

    pxOrderType  otp(Session(), s);
    pxOrderValidTrans *vtp =
    Session()->OrderValidTransList(VZ)->Find(*Customer_, s, kommityp - '0', bookingtyp - '0');
    if ( ! vtp )                        // this is an invalid order type
    {
        ExternalError(CMsgStream(), CMSG_ORD_TYPE_COMB, (char*)type, (int)kommityp, (int)bookingtyp); // siehe messgaecodeenum.inc & message.txt [30 00700]
        return Order_;
       // s.Clear();                      // will find the default order transaction
       // vtp = Session()->OrderValidTransList(VZ)->Find(*Customer_, s);
    }

    if ( vtp )                          // ensure transaction type is valid
    {                                   // avoid unneccessary order swaps:
        if (   (Order_ == NULL)
            || (Order_->KdAuftragArt() != vtp->KdAuftragArt())
            || (IsOrderSplit() && Order_->DafueAuftragNr() != num)
            || (MaxPosAuftrag > 0 && Order_->AnzPos() == MaxPosAuftrag )
            || (IsOrderConsolidation() && Order_->CloseOptions() != options )
            || (IsSplitOrderOnTens() && otp.IsTens() && Order_->CloseOptions() != options ) )
        {
            if ( Order_ )
            {
                csubot = Order_->SubOrderType();
                csubot.Strip();
                cpaymentterm = Order_->PaymentTerm();
                cpaymentterm.Strip();
            }

            Order_ = GetOrder(vtp, num, batchschreiben,options);  // must get a new current order
            if ( Order_ )
            {
                Order_->CloseOptions( options);
                if ( !cpaymentterm.IsEmpty() )
                {
                    Order_->SetPaymentTerm( cpaymentterm);
                }
                if (!csubot.IsEmpty() )
                {
                    Order_->SetSubOrderType( csubot);
                }
            }
        }
    }

/*----------------------------------------------------------------------------*/
/*  Set type of order. Usual the type of order is set during                  */
/*  EndOffTransmission, but to complete an Orderitem we have to now, what     */
/*  type of transmission is currently running.                                */
/*----------------------------------------------------------------------------*/
    if ( Order_ )
    {
        if ( Order_->OrderType().IsDelayedDelivery() )
        {
            pxHoliDayList* holidaylist = Session()->HoliDayList(VZ);
            if ( Order_->DatumAuslieferung() == pxConstants::NullDate )
                Order_->DatumAuslieferung( nDate(holidaylist->CalculateNextWorkDay(now,VZ)) );
            Order_->SetDDNotClose();
            Order_->SetVerzoegerAusgeliefert();
        }
    }

    return Order_;
}

/*----------------------------------------------------------------------------*/
/*  Set order type.  New Suivra France in program vborderimport2.bin          */
/*  In case of an order type change and having no order of that type linked   */
/*  with the order list, a new order is created and appended to the list.     */
/*  In case of an invalid order type, the default order transaction type is   */
/*  assigned. However, if no default values could be assigned, the current    */
/*  order will remain the current one. Due to this behaviour, at least a      */
/*  valid transaction type must be available or an order might NEVER be       */
/*  constructed. This is a special methode for New Suivra in France.          */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrderTransmit :: OrderTypeNS
(
    const nString& type,
    const nString& number,
    const short    BranchNo,
    const int      kommityp,
    const int      bookingtyp,
    const OriginTypeEnum batchschreiben,
    const short    options,
    const nString& desiredTour,
    const nDate&   desiredTourDate
)
{
    nDate now;
    nString s(type);
    long num = atol( number );
    num = ( (num < 0 || num > 35 ) ? 1 : num );
    short  VZ = Customer_->Vertriebszentrum();
    long MaxPosAuftrag = 0;
    MaxPosAuftrag = ( Order_ == NULL ) ? 0 : Order_->Param()->MaxPosAuftrag();

    if ( Session()->isBulgaria() )
    {
        MaxPosAuftrag = 0;                             // it will be used later on
    }

    pxOrderType  otp(Session(), s);
    pxOrderValidTrans *vtp =
    Session()->OrderValidTransList(VZ)->Find(*Customer_, s, kommityp - '0', bookingtyp -'0');
    if ( ! vtp )                        // this is an invalid order type
    {
        ExternalError(CMsgStream(), CMSG_ORD_TYPE_COMB, (char*)type, (int)kommityp, (int)bookingtyp); // siehe messgaecodeenum.inc & message.txt [30 00700]
        return Order_;
       // s.Clear();                      // will find the default order transaction
       // vtp = Session()->OrderValidTransList(VZ)->Find(*Customer_, s);
    }

    if ( vtp )                          // ensure transaction type is valid
    {                                   // avoid unneccessary order swaps:
        if (   (Order_ == NULL)
            || (Order_->KdAuftragArt() != vtp->KdAuftragArt())
            || (IsOrderSplit() && Order_->DafueAuftragNr() != num)
            || (MaxPosAuftrag > 0 && Order_->AnzPos() == MaxPosAuftrag )
            || (IsOrderConsolidation() && Order_->CloseOptions() != options )
            || (IsSplitOrderOnTens() && otp.IsTens() && Order_->CloseOptions() != options ) )
        {
            Order_ = GetOrder(vtp, num, batchschreiben, options, desiredTour, desiredTourDate);  // must get a new current order
            if ( Order_ )
                Order_->CloseOptions( options);
        }
    }

/*----------------------------------------------------------------------------*/
/*  Set type of order. Usual the type of order is set during                  */
/*  EndOffTransmission, but to complete an Orderitem we have to now, what     */
/*  type of transmission is currently running.                                */
/*----------------------------------------------------------------------------*/
    if ( Order_ )
    {
        Order_->OrderType(); // Init order type
        if ( Order_->OrderType().IsDelayedDelivery() )
        {
            if ( !Order_->IsVerzoegerAusgeliefert())
            {
                pxHoliDayList* holidaylist = Session()->HoliDayList(VZ);
                if ( Order_->DatumAuslieferung() == pxConstants::NullDate )
                    Order_->DatumAuslieferung( nDate(holidaylist->CalculateNextWorkDay(now,VZ)) );
                Order_->SetDDNotClose();
                Order_->SetVerzoegerAusgeliefert();
            }
        }

        if ( Order_->Param()->IsSIbtCstOrg() )
        {
            if ( Order_->AnzPos() == 0 )
            {
                Order_->TourId().Clear();
                Order_->ShuttleRouteAssign(BranchNo);
            }
        }

        if ( Order_->TourId().IsEmpty() )
        {
            if ( Order_->Param()->IsSIbtCstOrg() )
            {
                Order_->ShuttleRouteAssign(BranchNo);
            }
            else
            {
                Order_->RouteAssign();
            }
        }
        short DelayedDays = Order_->Param()->DelayedDays();
        if ( DelayedDays > 0  )  // Ivrylab
        {
            const pxCustOrderType& ot = Order_->OrderType();
            if ( !(ot.IsCollectiveOrder()) )
            {
                if ( Order_->DatumAuslieferung_ == pxConstants::NullDate )
                {
                    pxHoliDayList* holidaylist = Session()->HoliDayList(Customer_->Vertriebszentrum());
                    Order_->DatumAuslieferung( nDate(holidaylist->CalculateNextWorkDay(((now+DelayedDays) -1), Customer_->Vertriebszentrum())) );
                }
            }
        }
    }

    return Order_;
}

/*----------------------------------------------------------------------------*/
/*  Set order remarks.                                                        */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrderTransmit :: OrderRemarks
(
    const nString& remarks
)
{
    if (Order_)
    {
        Order_->Bemerkungen(remarks);
    }

    return Order_;
}

/*----------------------------------------------------------------------------*/
/*  Set the current Order type as OCPOrder (FR)                               */
/*----------------------------------------------------------------------------*/
void pxOrderTransmit::SetIsOCPOrder(bool isOcpOrder)
{
    isOCPOrder = isOcpOrder;
}

/*----------------------------------------------------------------------------*/
/*  Get if the current Order type is OCPOrder (FR)                            */
/*----------------------------------------------------------------------------*/
bool pxOrderTransmit::GetIsOCPOrder()
{
    return isOCPOrder;
}

/*----------------------------------------------------------------------------*/
/*  Set free text for current order.                                          */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrderTransmit :: FreeTextDoc
(
    const nString& textdoc
)
{
    if (Order_)
    {
        pxTextDoc *headp = Order_->HeadText();
        headp->NewLine(textdoc);
    }

    return Order_;
}

/*----------------------------------------------------------------------------*/
/*  Returns a pointer to an order.                                            */
/*  First the list of active orders is scanned for an order of a matching     */
/*  order type and, if set in the system configuration, for a matching        */
/*  customer-own order number. On a full match, the order pointer is returned.*/
/*  If no active order with a matching type could be found, the list of       */
/*  deferred orders is looked up to find one and continue entering items on   */
/*  it. However, if neither method leads to success, a new order is created.  */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrderTransmit :: GetOrder
(
    pxOrderValidTrans*   vtp,
    const long           n,
    const OriginTypeEnum batchschreiben,
    const short          options,
    const nString&       desiredTour,
    const nDate&         desiredTourDate
)
{
    pxOrder       *order  = NULL;
    pxOrder       *temp   = NULL;
    pxCustomerFlags& cflags = Customer_->Flags();
    short         filiale = Customer_->FilialNr();
    long          MaxPos  = 0;
    nString subot;
    subot.Strip();
    nString  TourId;
    nDate    DatumAuslieferung;

    pxCustOrderTypeList  *otlp = Customer_->OrderTypeList();
    pxCustOrderType      *otp  = otlp->Find(vtp->KdAuftragArt(), Customer_->Vertriebszentrum(), Customer_->KundenNr());

    if (ActiveOrders_ == NULL)        // then must construct new order list
    {
        ActiveOrders_ = new pxOrderList(Session());
    }

    pxOrderListIter iter(*ActiveOrders_); // define an iterator for it
    while ( (order = (pxOrder*) ++iter) != NULL ) // active order lookup
    {
        if (!desiredTour.IsEmpty() && order->TourId() != desiredTour)
        {
            continue;
        }
        // no consolidation for ocp and not ocp orders
        if (GetIsOCPOrder() != order->IsOCPOrder())
        {
            //BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "####GetOrder#### cannot consolidate the new order with the active order because of different ocp flag");
            continue;
        }
        MaxPos = order->Param()->MaxPosAuftrag();
        if ( Session()->isBulgaria() )
        {
            MaxPos = 0;                             // it will be used later on
        }
        if ( Session()->isFrance() && MaxPos > 0 && !order->SubOrderType().IsEmpty() )
        {
            if ( order->KdAuftragArt() == vtp->KdAuftragArt() &&
                 order->KoArt() == vtp->KoArt() &&
                 order->BuchArt() == vtp->BuchArt() &&
                 order->BatchSchreiben() == batchschreiben )
            {
                return order;
            }
        }

        if ( order->KdAuftragArt() == vtp->KdAuftragArt() &&
             order->KoArt() == vtp->KoArt() &&
             order->BuchArt() == vtp->BuchArt() &&
             // order->DafueAuftragNr() == n &&
             order->BatchSchreiben() == batchschreiben &&
             ((MaxPos == 0) || (order->AnzPos() < MaxPos))  &&
             order->CloseOptions() == options)
        {
            // matching order found, first check ordersplit and consolidation.
            // skdauftragzusammen = 1 und skdauftragsplit = 1 and die Auftragsart Auftragzusammen = 1
            if ( cflags.IsAuftragSplit() && order->Param()->IsCustomerOrderSplit() && otp &&
                 otp->IsOrderCons()  && Customer_->Flags().IsAuftragZusammen())
            {
                if ( order->DafueAuftragNr() == n )
                {
                    return order;              // customer-own order no. matches
                }
                else
                {
                    continue;
                }
            }
            temp = order;                    // found a matching order type
            // now check orderconsolidation
            if (otp )
            {
                if ( otp->IsOrderCons()  && Customer_->Flags().IsAuftragZusammen() &&
                     !(cflags.IsAuftragSplit() && order->Param()->IsCustomerOrderSplit()))
                {
                    return order;            // customer-own order no. matches
                }
                else if (cflags.IsAuftragSplit() && order->Param()->IsCustomerOrderSplit() &&
                         !(otp->IsOrderCons()  && Customer_->Flags().IsAuftragZusammen()))
                {
                    if ( order->DafueAuftragNr() == n )
                    {
                        return order;              // customer-own order no. matches
                    }
                }
            }

            if (!( cflags.IsAuftragSplit() && order->Param()->IsCustomerOrderSplit()) )
            {
                return order;
            }
        }
    }

    // Deferred order list lookup :
    if ( temp == NULL && !cflags.IsSepAuft() )  // no matching order type found
    {
        if ( DeferredOrders_ == NULL )   // must read them from the data base
        {
            DeferredOrders_ = new pxOrderList(Session());
            DeferredOrders_->SelectByCustomerNo(Customer_->IDFNr(), "", "",filiale,
                                    Order::NOT_EntryInProgress,
                                    Order::NOT_UpdateInProgress,
                                    Order::NOT_ProblemClearance,
                                    Order::EntryDeferred,
                                    Order::cStateLast );
        }
        if (!Customer_->Flags().IsAuftragZusammen())
        {
            if ( otp )
            {
                if ( otp->IsOverDrive() && vtp )
                {
                    Customer_->DiscountConditions(vtp->KdAuftragArt(), subot );
                    if ( !Customer_->IsGoodState() )
                    {
                        Error() = Customer_->Error();
                        return order;
                    }
                }
            }

            order = ActiveOrders_->NewOrder(Customer_, vtp, n, DeliveryDate_, batchschreiben);

            setDesiredTour(order, desiredTour, desiredTourDate);
            return order;
        }


        pxOrderListIter it(*DeferredOrders_);
        while ( (order = (pxOrder*) ++it) != NULL )
        {
            if (   (!desiredTour.IsEmpty() && order->TourId() != desiredTour)
                || order->IsKreditLimitErreicht()
                || order->IsSeparatedOrder()
                || (order->KdAuftragNrOrg() > 0)
                || (order->KoArt() == '2')          // no append for this  commission type
                || (order->isMSV3Order() && !order->hasDefaultOrderLabel())
                || ((order->Param()->MaxPosAuftrag() > 0) && (order->AnzPos() >= order->Param()->MaxPosAuftrag()))  // no append if MaxPos is reached
                || order->IsDoNotAppend()           // no append if this flag is on
                || ((order->BatchSchreiben() == cORTYPE_AUXILIARY) && order->Param()->IsSIbtCstOrg() && (order->DatumAuslieferung() > pxConstants::NullDate)) 
                || (order->IsOCPOrder() != GetIsOCPOrder())) // no consolidation for ocp and not ocp orders
            {
                delete (pxOrder*)it.Remove();
                continue;
            }

            if ( order->DatumAuslieferung() != pxConstants::NullDate )
            {
                if ( DeliveryDate() != 0L )
                {
                    if ( order->DatumAuslieferung() != nDate(DeliveryDate() ) )
                    {
                        delete (pxOrder*)it.Remove(); // no appropiate commission type
                        continue;
                    }
                }
                else if ( order->DatumAuslieferung() != Customer_->NextDeliveryDay() && order->DatumAuslieferung() != desiredTourDate )
                {
                    delete (pxOrder*)it.Remove(); // no appropiate commission type
                    continue;
                }
            }
            else if (desiredTour.IsEmpty()) // if specific tour is desired, it doesn´t matter if this is customers next tour!
            {
                Customer_->getCustomersNextTourId(TourId, DatumAuslieferung);
                if (!TourId.IsEmpty() && (order->TourId() != TourId))
                {
                    delete (pxOrder*)it.Remove();                                    // no append if this flag is on
                    continue;
                }
            }

            // In case of a matching order type, the order is openend for inserting
            // new items, removed from the list of deferred orders, and appended to
            // the list of active orders.
            pxOrder* openOrder = OpenOrder(vtp, n, batchschreiben, options, order, it, otp);
            if (openOrder != NULL)
            {
                //BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), "####GetOrder#### consolidation with deferred order successfully");
                return openOrder;
            }
        }
    }

    if ( otp && otp->IsOverDrive() && vtp )
    {
        Customer_->DiscountConditions(vtp->KdAuftragArt(), subot );
        if ( !Customer_->IsGoodState() )
        {
            Error() = Customer_->Error();
            return order;
        }
    }
    order = ActiveOrders_->NewOrder(Customer_, vtp, n, DeliveryDate_, batchschreiben);
    Error() = ActiveOrders_->Error();
    if ( IsGoodState() )
    {
        setDesiredTour(order, desiredTour, desiredTourDate);
    }
    return order;
}

// In case of a matching order type, the order is openend for inserting
// new items, removed from the list of deferred orders, and appended to
// the list of active orders.
pxOrder* pxOrderTransmit::OpenOrder(const pxOrderValidTrans* vtp, const long n, const OriginTypeEnum batchschreiben, const short options,
    pxOrder* order, pxOrderListIter& it, const pxCustOrderType* otp)
{
    if ((order->KdAuftragArt() != vtp->KdAuftragArt())
        || (order->KoArt() != vtp->KoArt())
        || (order->BuchArt() != vtp->BuchArt())
        //|| (order->DafueAuftragNr() != n)
        || (order->BatchSchreiben() != batchschreiben)
        || (options != Order::CLOSE_DEFAULT))
        //order->CloseOptions() == options == )
    {
        return NULL;
    }

    // skdauftragzusammen = 1 und skdauftragsplit = 1 and die Auftragsart Auftragzusammen = 1
    if ((otp != NULL) && otp->IsOrderCons() && Customer()->Flags().IsAuftragZusammen())
    {
        if (!Customer()->Flags().IsAuftragSplit() || !order->Param()->IsCustomerOrderSplit() || (order->DafueAuftragNr() == n))
        {
            if (order->OpenOrder(cDBOPEN_INSERT, Customer_) == nSTATE_GOOD)
            {
                order->DafueAuftragNr(n);
                order->BatchSchreiben(batchschreiben);
                return (pxOrder*)ActiveOrders_->Append((pxOrder*)it.Remove());
            }
            else
            {
                Error() = order->Error();
                delete (pxOrder*)it.Remove(); // order open failed
            }
        }
    }
    return NULL;
}

/*----------------------------------------------------------------------------*/
/*  Returns TRUE, if desired tour has been assigned to order.                 */
/*----------------------------------------------------------------------------*/
bool pxOrderTransmit::setDesiredTour(pxOrder *order, const nString& desiredTour, const nDate& desiredTourDate)
{
    bool ret = false;

    if ( !desiredTour.IsEmpty() )      //callsystem routeid available
    {
        ret = true;

        if (order->TourId() != desiredTour) // set desired tour only, if it is different to order´s current tour
        {
            if (desiredTourDate > TourUtil::getNullDate())
                order->DatumAuslieferung(desiredTourDate);

            order->getTourAssignmentUtil()->resetInjections();
            order->getTourAssignmentUtil()->injectDesiredTourId(desiredTour);
            order->getTourAssignmentUtil()->assignTour();

            // Wenn Wunschtour nicht gefunden dann aktuell gültige Tour buchen!
            if (desiredTourDate != order->DatumAuslieferung() &&
                TourUtil::isDateInTheFuture(order->DatumAuslieferung()))
            {
                order->DatumAuslieferung(TourUtil::getNullDate());
                order->getTourAssignmentUtil()->resetInjections();
                order->getTourAssignmentUtil()->assignTour();
            }
        }
    }

    return ret;
}

/*----------------------------------------------------------------------------*/
/*  Returns a pointer to an order.                                            */
/*  Constructs an pxOrder object by reading a record from the Database        */
/*  depend on KdAuftragNr                                                     */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrderTransmit :: NewOrder
(
    const long KdAuftragNr
)
{
    if ( Order_  == NULL)              // ensure no order is open
    {
        Order_ = new pxOrder(Session(),KdAuftragNr,cDBOPEN_INSERT);
        Customer_ = Order_->Customer();
        Order_->DoNoCustDestruct();
        if ( ActiveOrders_ == NULL )        // then must construct new order list
            ActiveOrders_ = new pxOrderList(Session());

        ActiveOrders_->Append(Order_);
    }
    return Order_;
}

/*----------------------------------------------------------------------------*/
/*  NewOrderInfo: returns a well constructed pxOrder object.                  */
/*  this pxOrder object does not insert a kdauftrag record to the database    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrderTransmit :: NewOrderInfo
(
)
{
    if ( ActiveOrders_ == NULL )        // then must construct new order list
        ActiveOrders_ = new pxOrderList(Session());

    if ( Order_  == NULL)              // ensure no order is open
    {
        if ( this->Session()->IsSubDeviceTypeOf(MSV3) )
        {
            pxOrderPeriod orderperiod(Session());
            orderperiod = this->getMSV3OrderPeriod();
            Order_ = ActiveOrders_->NewMSV3InfoOrder(Customer_, orderperiod);
        }
        else
        {
            Order_ = ActiveOrders_->NewOrderInfo(Customer_);
        }
        if ( Order_ )
        {
            Error() = Order_->Error();
        }
        else
        {
            Error() = ActiveOrders_->Error();
        }
    }
    return Order_;
}

/*----------------------------------------------------------------------------*/
/*  NewOrderProforma: returns a well constructed pxOrder object.              */
/*  this pxOrder object does not insert a kdauftrag record to the database    */
/*----------------------------------------------------------------------------*/
pxOrder*
pxOrderTransmit :: NewOrderProforma
(
)
{
    if ( ActiveOrders_ == NULL )        // then must construct new order list
        ActiveOrders_ = new pxOrderList(Session());

    if ( Order_  == NULL)               // ensure no order is open
    {
        Order_ = ActiveOrders_->NewOrderProforma(Customer_);
        Error() = Order_->Error();
    }
    return Order_;
}
