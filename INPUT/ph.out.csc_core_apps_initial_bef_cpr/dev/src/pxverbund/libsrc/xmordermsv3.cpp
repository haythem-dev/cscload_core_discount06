#include "pxxmit.hpp"
#include "pxholiday.hpp"
#include "pxmsv3order.hpp"
#include "pxorderperiod.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxcstot.hpp"
#include "pxordvtr.hpp"
#include "pxoeparm.hpp"
#include "pxorder.hpp"
#include "tourmanager.hpp"
#include <pxbase/pxconstants.hpp>
#include "pxparameter.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* get the order period id and the connected tourid for MSV3                  */
/*----------------------------------------------------------------------------*/
pxOrderPeriod pxOrderTransmit::getMSV3OrderPeriod()
{
    pxOrderPeriod retval(this->Session());
    retval = TourManager::getCurrentMSV3OrderPeriod( this->Session(), this->Customer()->Vertriebszentrum(), this->Customer()->IDFNr() );
    return retval;
}

/*----------------------------------------------------------------------------*/
/* check if we can do order consolidation with the order in process           */
/*----------------------------------------------------------------------------*/
bool pxOrderTransmit::doConsolidationWithCurrentMSV3Order( const pxOrderPeriod& orderperiod, const nString& ordertype, const nString& orderlabel )
{
    if( NULL != this->Order_ )
    {
        if( 0 < this->Order_->Param()->MaxPosAuftrag() && this->Order_->AnzPos() >= this->Order_->Param()->MaxPosAuftrag() ) // check if max. allowed order lines are reached
        {
            return false;
        }

        if( ordertype != this->Order_->KdAuftragArt() ) // check if it´s the same ordertype
        {
            return false;
        }

        if( !this->Order_->isOrderLabelEqual( orderlabel ) ) // check if the orderlabel is the same
        {
            return false;
        }

        if ((pxConstants::NullDate == Order_->DatumAuslieferung()) || !(this->Session()->getIgnoreOrderPeriodDD()) )
        {
            if (orderperiod.ID() != this->Order_->OrderPeriodID()) // is the current order in the same order period?
            {
                return false;
            }
        }

        // Keine Auftragszusammenführung mit Aufträgen die im gleichen Bestellfenster sind aber ein Datumauslieferung für einen anderen Wochentag haben!
        if( "RK" != Order_->KdAuftragArt() )
        {
            TourInfo normalTour = this->Order_->getNormalDeliveryTourInfo(orderperiod.TourID(), orderperiod.WeekDay());
            if( normalTour.getTourFound() )
            {
                if( normalTour.getTourID() != this->Order_->TourId() ||
                    normalTour.getTourDate().GetYYYYMMDD() != this->Order_->getTourInformation()->getTourDate().GetYYYYMMDD() )
                {
                    return false;
                }
            }
        }
        return true;
    }
    else // NULL == this->Order_
    {
        if( Customer_->Flags().IsAuftragZusammen() )
        {
            return true;
        }

        return false;
    }
}

/*----------------------------------------------------------------------------*/
/* check if the ordertype is allowed for MSV3 for this customer               */
/*----------------------------------------------------------------------------*/
bool pxOrderTransmit::isOrderTypeAllowedForMSV3( const nString& ordertype )
{
    if( 0 == ordertype.Compare("RK") )
    {
        return true;
    }

    // get customer order type settings
    pxCustOrderType* customerOrderType = new pxCustOrderType(Session());
    if( 0 == customerOrderType->getCustomerOrderType( this->Customer_->Vertriebszentrum(), this->Customer_->IDFNr(), ordertype ) )
    {
        if( !customerOrderType->isAllowedForMSV3() )
        {
            ExternalError( CMsgStream(), CMSG_XMIT_MSV3_ORDERTYPE_NOT_ALLOWED ); // siehe pxxmit.hpp & message.txt [20 00700]
            return false;
        }
    }
    else
    {
        ExternalError( CMsgStream(), CMSG_XMIT_MSV3_ORDERTYPE_NOT_ALLOWED ); // siehe pxxmit.hpp & message.txt [20 00700]
        return false;
    }
    return true;
}

/*----------------------------------------------------------------------------*/
/* Get new order or existing order from consolidation for MSV3 orders         */
/* called for every item to check max positioncount                           */
/*----------------------------------------------------------------------------*/
pxOrder* pxOrderTransmit::OrderTypeMSV3( const nString& _ordertype, const nString& _orderlabel, const int _pickingtype, const int _bookingtype )
{
    short branchno = Customer_->Vertriebszentrum(); // kunde aus session; filiale über kunde ermitteln
    nString orderlabel(_orderlabel);

    nString ordertype(_ordertype);
    pxOrderType pxordertype(Session(), ordertype);

    // check if combination of ordertype, bookingtype and pickingtype is valid for customer
    // if combination of ordertype, bookingtype and pickingtype is not valid for customer, return error
    pxOrderValidTrans *validordertypecombination = Session()->OrderValidTransList(branchno)->Find( *Customer_, ordertype, _pickingtype, _bookingtype );
    if ( !validordertypecombination )
    {
        ExternalError( CMsgStream(), CMSG_XMIT_MSV3_ORDERTYPE_NOT_ALLOWED ); // siehe pxxmit.hpp & message.txt [20 00700]
        return Order_;
    }

    // get MSV3 orderperiod
    pxOrderPeriod orderperiod(Session());
    orderperiod = this->getMSV3OrderPeriod();

    bool changedOrderLabelToDefault = false;
    nString originalOrderLabel(orderlabel);
    originalOrderLabel.Strip();

    if ( validordertypecombination )
    {
        if( 0 == _ordertype.Compare("RK") )
        {
            orderlabel = "MSV3-RUECKNAHME";
        }
        else
        {
            pxCustOrderType* customerOrderType = new pxCustOrderType(Session());
            if( 0 == customerOrderType->getCustomerOrderType( branchno, Customer_->IDFNr(), _ordertype ) )
            {
                orderlabel = processMSV3OrderLabel( orderlabel, customerOrderType, orderperiod.ID() );
                orderlabel.Strip();
                if( originalOrderLabel != orderlabel ) changedOrderLabelToDefault = true;
            }
        }

        if( !isOrderTypeAllowedForMSV3( validordertypecombination->KdAuftragArt() ) )
        {
            return this->Order_;
        }

        if( !this->doConsolidationWithCurrentMSV3Order( orderperiod, validordertypecombination->KdAuftragArt(), orderlabel ) )
        {
            this->Order_ = GetOrderMSV3(validordertypecombination, orderlabel, orderperiod );  // must get a new current order
        }

        if( NULL == this->Order_ )
        {
            this->Order_ = GetOrderMSV3(validordertypecombination, orderlabel, orderperiod );  // must get a new current order
        }

        if( Order_ )
        {
            if ( Order_->OrderType().IsDelayedDelivery() )
            {
                nDate now;
                pxHoliDayList* holidaylist = Session()->HoliDayList( branchno );
                if( Order_->DatumAuslieferung() == nDate(0L) )
                {
                    Order_->DatumAuslieferung( nDate(holidaylist->CalculateNextWorkDay(now,branchno)) ); // set delivery date to next working day
                }
                Order_->SetDDNotClose(); // do not close due to delayed delivery
                Order_->SetVerzoegerAusgeliefert();
            }
        }
    }

    // set an event if the order label has been changed to the default of the order type due to limitation of custom order labels
    if( changedOrderLabelToDefault )
    {
        Order_->WriteOrderLabelChangedToDefaultEvent();
    }

    return Order_;
}

/*----------------------------------------------------------------------------*/
/*  processing for MSV3 orderlabels                            SH, 23.08.2013 */
/*----------------------------------------------------------------------------*/
const nString& pxOrderTransmit::processMSV3OrderLabel( const nString& _orderlabel, pxCustOrderType* customerOrderType, const long orderperiodid )
{
    if( customerOrderType->isDefaultOrderLabel(_orderlabel) )
    {
        // no further checks for default orderlabels
        return _orderlabel;
    }

    if( !customerOrderType->isUsageOfCustomOrderLabelsAllowed() )
    {
        // use default orderlabel if custom orderlabels are not allowed
        return customerOrderType->getDefaultOrderLabel();
    }

    // get list of already used orderlabels within orderperiodtime
    short OrderLabelCount = 0;
    bool NewOrderLabel = true;
    pxMSV3OrderList* msv3orderlist = new pxMSV3OrderList( Session() );
    msv3orderlist->SelectMSV3OrderLabel( Customer_->Vertriebszentrum(), Customer_->IDFNr(), customerOrderType->KdAuftragArt(), orderperiodid );

    // check if orderlabel has already been used and count used custom order labels
    if( msv3orderlist->Entries() > 0 )
    {
        pxMSV3Order* msv3order = NULL;
        pxMSV3OrderListIter iter = pxMSV3OrderListIter(*msv3orderlist);
        while( (msv3order = (pxMSV3Order*) ++iter) != NULL )
        {
            if( msv3order->isOrderLabelEqual( _orderlabel ) )
            {
                NewOrderLabel = false;
                break;
            }
            else
            {
                ++OrderLabelCount;
            }
        }
    }

    if( NULL != msv3orderlist )
    {
        delete msv3orderlist;
        msv3orderlist = NULL;
    }

    if( !NewOrderLabel ) // if orderlabel has already been used -> OK, use custom orderlabel
    {
        return _orderlabel;
    }

    ++OrderLabelCount;
    // if orderlabel has not been used -> check if max allowed custom orderlabels is reached
    if( OrderLabelCount > customerOrderType->OrderLabelCount() )
    {
        return customerOrderType->OrderIdentificatio();
    }

    return _orderlabel;
}

/*----------------------------------------------------------------------------*/
/*  get order from active orders, deferred orders or create new order         */
/*----------------------------------------------------------------------------*/
pxOrder* pxOrderTransmit :: GetOrderMSV3( const pxOrderValidTrans* vtp, const nString& _orderlabel, const pxOrderPeriod& _orderperiod )
{
    pxOrder *order;
    short filiale = Customer_->FilialNr();
    nString subot;
    subot.Strip();

    pxCustOrderTypeList *otlp = Customer_->OrderTypeList();
    pxCustOrderType *otp = otlp->Find(vtp->KdAuftragArt(), Customer_->Vertriebszentrum(), Customer_->KundenNr());

    if ( ActiveOrders_ == NULL )        // then must construct new order list
    {
        ActiveOrders_ = new pxOrderList(Session());
    }

    if ((false == Customer_->Flags().IsAuftragZusammen()) || (NULL != otp && false == otp->IsOrderCons()))
    {
        order = ActiveOrders_->NewOrderMSV3(Customer_, vtp, 0, _orderlabel, _orderperiod );
        Error() = ActiveOrders_->Error();
        return order;
    }

    pxOrderListIter iter(*ActiveOrders_); // define an iterator for it
    while ( (order = (pxOrder*) ++iter) != NULL ) // active order lookup
    {
        // I-16003871 Prüfung ob Auftrag für Auftragszusammenführung herangezogen werden darf oder nicht (Fall: 1. Position Kühlartikel -> Verzögert -> Problem: andere Positionen aus erneuter Übertragung wurden auch verzögert!
        if( !order->IsAvailableForOrderConsolidation() )
        {
            continue;
        }

        //For DD orders check if orderperiod is allowd to be ignored
        if ((pxConstants::NullDate != order->DatumAuslieferung()) && (this->Session()->getIgnoreOrderPeriodDD()) )
        {
            if (order->KdAuftragArt() == vtp->KdAuftragArt() && order->KoArt() == vtp->KoArt() && order->BuchArt() == vtp->BuchArt()
                && order->isOrderLabelEqual(_orderlabel))
            {
                // matching order found, first check ordersplit and consolidation.
                // skdauftragzusammen = 1 und skdauftragsplit = 1 and die Auftragsart Auftragzusammen = 1
                if (otp && otp->IsOrderCons() && Customer_->Flags().IsAuftragZusammen())
                {
                    return order;  // customer-own order no. matches
                }
            } 
        }
        else if ( order->KdAuftragArt() == vtp->KdAuftragArt() && order->KoArt() == vtp->KoArt() && order->BuchArt() == vtp->BuchArt()
            && order->isOrderLabelEqual( _orderlabel ) && order->OrderPeriodID() == _orderperiod.ID() )
        {
            // matching order found, first check ordersplit and consolidation.
            // skdauftragzusammen = 1 und skdauftragsplit = 1 and die Auftragsart Auftragzusammen = 1
            if ( otp && otp->IsOrderCons() && Customer_->Flags().IsAuftragZusammen())
            {
                return order;  // customer-own order no. matches
            }
        }
    }


    // Deferred order list lookup :
    if ( DeferredOrders_ == NULL )   // must read them from the data base
    {
        DeferredOrders_ = new pxOrderList(Session());
        DeferredOrders_->SelectByCustomerNo(Customer_->IDFNr(), "", "",filiale, Order::NOT_EntryInProgress, Order::NOT_UpdateInProgress, Order::NOT_ProblemClearance,
                              Order::EntryDeferred, Order::cStateLast );
    }
    pxOrderListIter it(*DeferredOrders_);
    while ( (order = (pxOrder*) ++it) != NULL )
    {
        if ( order->IsDoNotAppend() )
        {
            delete (pxOrder*)it.Remove();
            continue;
        }

        // I-16003871 Prüfung ob Auftrag für Auftragszusammenführung herangezogen werden darf oder nicht (Fall: 1. Position Kühlartikel -> Verzögert -> Problem: andere Positionen aus erneuter Übertragung wurden auch verzögert!
        if( !order->IsAvailableForOrderConsolidation() )
        {
            delete (pxOrder*)it.Remove();
            continue;
        }

        //// Keine Auftragszusammenführung wenn Auftrag auf anderen Wochentag verzögert wurde!
        if( "RK" != order->KdAuftragArt() )
        {
            TourInfo normalTour = order->getNormalDeliveryTourInfo(_orderperiod.TourID(), _orderperiod.WeekDay());
            if( normalTour.getTourFound() )
            {
                if( normalTour.getTourID() != order->TourId() || normalTour.getTourDate().GetYYYYMMDD() != order->getTourInformation()->getTourDate().GetYYYYMMDD() )
                {
                    delete (pxOrder*)it.Remove();
                    continue;
                }
            }
        }

        // In case of a matching order type, the order is openend for inserting
        // new items, removed from the list of deferred orders, and appended to
        // the list of active orders.
        //For DD orders check if orderperiod is allowd to be ignored
        if ((pxConstants::NullDate != order->DatumAuslieferung()) && (this->Session()->getIgnoreOrderPeriodDD()) )
        {
            if (order->KdAuftragArt() == vtp->KdAuftragArt() && order->KoArt() == vtp->KoArt() && order->BuchArt() == vtp->BuchArt()
                && order->isOrderLabelEqual(_orderlabel) )
            {
                if (order->OpenOrder(cDBOPEN_INSERT, Customer_) == nSTATE_GOOD)
                {
                    return (pxOrder*)ActiveOrders_->Append((pxOrder*)it.Remove());
                }
                else
                {
                    Error() = order->Error();
                    delete (pxOrder*)it.Remove(); // open order failed
                }
            }
        }
        else if ( order->KdAuftragArt() == vtp->KdAuftragArt() && order->KoArt() == vtp->KoArt() && order->BuchArt() == vtp->BuchArt()
            && order->OrderPeriodID() == _orderperiod.ID() && order->isOrderLabelEqual(_orderlabel) )
        {
            if ( order->OpenOrder(cDBOPEN_INSERT, Customer_) == nSTATE_GOOD )
            {
                return (pxOrder*) ActiveOrders_->Append((pxOrder*)it.Remove());
            }
            else
            {
                Error() = order->Error();
                delete (pxOrder*)it.Remove(); // open order failed
            }
        }
    }

    order = ActiveOrders_->NewOrderMSV3(Customer_, vtp, 0, _orderlabel, _orderperiod );
    Error() = ActiveOrders_->Error();
    return order;
}


/*----------------------------------------------------------------------------*/
/* Get new order or existing order from consolidation for MSV3 orders         */
/* called for every item to check max positioncount                           */
/*----------------------------------------------------------------------------*/
pxOrder* pxOrderTransmit::OrderTypeMSV3_2(const basar::VarString& _ordertype, const basar::VarString& _orderlabel,
    const int _pickingtype, const int _bookingtype, const long _orderperiodid)
{
    short               branchno = Customer_->Vertriebszentrum();
    pxOrderValidTrans*  validOrderTypeCombination = NULL;

    // we have already an order and maxpos parameter is either unset or not yet reached
    if (NULL != Order_ &&
        (0 == Order_->Param()->MaxPosAuftrag() || Order_->AnzPos() < Order_->Param()->MaxPosAuftrag()))
    {
        return Order_;
    }

    // check if combination of ordertype, bookingtype and pickingtype is valid for customer
    // if combination of ordertype, bookingtype and pickingtype is not valid for customer, return error
    validOrderTypeCombination = Session()->OrderValidTransList(branchno)->Find(*Customer_, _ordertype.c_str(), _pickingtype, _bookingtype);
    if (NULL == validOrderTypeCombination)
    {
        ExternalError(CMsgStream(), CMSG_XMIT_MSV3_ORDERTYPE_NOT_ALLOWED);
        return Order_;
    }

    // get MSV3 orderperiod
    pxOrderPeriod orderPeriod(Session(), _orderperiodid);
    orderPeriod.Get();
    if (false == orderPeriod.IsGoodState())
    {
        ExternalError(CMsgStream(), CMSG_XMIT_MSV3_ORDERPERIOD_NOTFOUND, _orderperiodid);
        return Order_;
    }

    // must get a new current order
    Order_ = GetOrderMSV3(validOrderTypeCombination, _orderlabel.c_str(), orderPeriod);
    if (NULL != Order_)
    {
        if (Order_->OrderType().IsDelayedDelivery())
        {
            // set delivery date to next working day
            if (pxConstants::NullDate == Order_->DatumAuslieferung())
            {
                nDate now;
                pxHoliDayList* holidaylist = Session()->HoliDayList(branchno);
                Order_->DatumAuslieferung( nDate(holidaylist->CalculateNextWorkDay(now,branchno)) );
            }
            Order_->SetDDNotClose(); // do not close due to delayed delivery
            Order_->SetVerzoegerAusgeliefert();
        }
    }

    // set an event if the order label has been changed to the default of the order type due to limitation of custom order labels
    //if( changedOrderLabelToDefault )
    //{
    //  Order_->WriteOrderLabelChangedToDefaultEvent();
    //}

    return Order_;
}
