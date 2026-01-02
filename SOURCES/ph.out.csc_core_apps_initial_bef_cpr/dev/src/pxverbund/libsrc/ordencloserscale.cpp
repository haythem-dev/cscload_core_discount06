#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxoeparm.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxbranch.hpp"
#include "pxcustinf.hpp"
#include "pxencloserscale.hpp"
#include "pxtxtdoc.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

void pxOrder::XMLEncloserScaleSetEncloserDone()
{
    pxCustRouteList* rl = RouteList();
    if (rl == NULL) return;

    pxCustRoute* routex = rl->Find(this->TourId());                                     // check current route
    routex->SetSencloserDone();
    nDBBeginTransaction(cDBTransRecord);
    routex->Put();
    if (routex->IsGoodState())
    {
        nDBCommit(cDBTransRecord);
    }
}
/*----------------------------------------------------------------------------*/
/*  XMLEncloserScaleAssignNextRoute: check the state to be returned to the    */
/*  caller. If this order is assigned during RouteAssignNext() to the next    */
/*  working day (DatumAusLieferung > current day), then the order has to be   */
/*  placed into the EntryDeferred state                                       */
/*----------------------------------------------------------------------------*/
Order::States pxOrder::XMLEncloserScaleAssignNextRoute
(
    Order::States state
)
{
    nDate now;
    Order::States  State = Order::LeaveAsIs;

    if ( state == Order::EntryClosed )
    {
        if ( this->DatumAuslieferung() != pxConstants::NullDate && this->DatumAuslieferung() == now )
        {
            return State;
        }

        this->RouteAssignNext();
        if ( this->DatumAuslieferung() > now )
        {
            State = Order::EntryDeferred;
        }
    }
    return State;
}

/*----------------------------------------------------------------------------*/
/*  XMLEncloserScale                                                          */
/*----------------------------------------------------------------------------*/
Order::States
pxOrder :: XMLEncloserScale
(
    Order::States state
)
{
    Order::States State = Order::LeaveAsIs;
    const pxOrderEntryParamPtr param = Param();
    pxEncloserScale*   entriep  = NULL;
    long tour                  = 0;
    nDate now;
    nClock currenttime;
    long  cdaysecs = currenttime.GetDaySeconds();                 // absolute current time in seconds since midnight
    long  toursecs             = 0;
    long  encTilttime          = 0;
    long  timeSlot             = 0;
    long  ldzNormal(param->DurchlaufNormal() * 60);                // Lagerdurchlaufzeit Normal  in seconds
    long  ldzEilbote(param->DurchlaufEilbote() * 60);              // Lagerdurchlaufzeit Eilbote in seconds
    pxEncloserScaleList*  ScaleList = NULL;
    char  EilCommiType = '3';

    if ( !hasToBeCheckEncloserScale() )
        return State;

    tour         = atol((char*)(nString)(TourId())(0,4));
    nClock ctour(tour * 100);
    toursecs     = ctour.GetDaySeconds();                          // absolute tour time in seconds since midnight
    timeSlot     = toursecs - cdaysecs;                            // difference between Tourtime and Currenttime in seconds
    encTilttime  = toursecs - (param->EncloserTiltTime() * 60);    // absolute Beifügerkippzeit in seconds since midnight
    ScaleList    = Customer()->EncloserScaleList();

    // is time slot reached
    if ( cdaysecs < encTilttime )                                  // time before EncloserTiltTime
    {
       return State;                                               // nothing to do
    }

    pxCustRouteList* rl = RouteList();
    if ( rl == NULL )
    {
       return State;                                               // not possible to do anything
    }

    pxCustRoute* route = rl->Find(this->TourId());                        // check current route
    if ( route )
    {
        if ( route->IsSencloserDone() )                            // already positions enclosed to this tour
        {
           return State = XMLEncloserScaleAssignNextRoute( state );  // check DatumAuslieferung bezüglich Statusrückmeldung
        }
    }

    // now check customers encloserscale entries
    if ( ScaleList == NULL )                                       // customer has now entries
    {
        return State = XMLEncloserScaleAssignNextRoute(state);    // check DatumAuslieferung bezüglich Statusrückmeldung
    }

    // now look for customer encloserscale entry that is at nearest to timeslot
    entriep = ScaleList->FindNearest( timeSlot );
    if ( entriep == NULL )                                          // No entry found, so go to next tour
    {
        return State = XMLEncloserScaleAssignNextRoute(state);      // check DatumAuslieferung bezüglich Statusrückmeldung
    }

    // entry found
    if ( timeSlot > ldzNormal )                                     // time enough, normal handling
    {
        XMLEncloserScaleSetEncloserDone();

        if ( AnzPos_ <= entriep->MaxPositions() )
        {
            return State;
        }
        else
        {
            SplittEncloseScale( entriep->MaxPositions(),KoArt_,state );
            return State;
        }
    }
    else if ( timeSlot < ldzNormal  && timeSlot >  ldzEilbote )
    {
        XMLEncloserScaleSetEncloserDone();

        if ( AnzPos_ <= entriep->MaxPositions() )
        {
            return State;
        }
        else
        {
            SplittEncloseScale( entriep->MaxPositions(), KoArt_ ,state);
            OrderType(KdAuftragArt_,EilCommiType ,BuchArt_);
            return State;
        }
    }
    else if( timeSlot < ldzEilbote )
    {
       XMLEncloserScaleSetEncloserDone();

       if ( AnzPos_ <= entriep->MaxPositions() )
       {
          State = Order::EntryDeferred;
          SetProblemClearance();                                  // manual clearance required
          SetRouteCheck();                                        // must do a manual route check
          return State;
       }
       else
       {
          SplittEncloseScale( entriep->MaxPositions(), KoArt_ ,state);
          State = Order::EntryDeferred;
          SetProblemClearance();                                  // manual clearance required
          return State;
       }
    }

    return State;
 }


/*----------------------------------------------------------------------------*/
/* SplittEncloseScale                                                         */
/* The current Order(*this) will be splittet FromPos on, that means within    */
/* this order the count of position until FromPos stay within this order, the */
/* rest positions FromPos on are going into a new order.                      */
/* The new orders commitype = CommiType. CloseOption 0 = Close order and      */
/* CloseOption 1 = Defer new order.                                           */
/* The new order always gets the next TourId from this orders TourId_ on.     */
/*----------------------------------------------------------------------------*/
int pxOrder::SplittEncloseScale(const long FromPos, const char KoArt, Order::States state)
{
    nDate today;
    pxCustBase* customer = Customer();
    pxOrderItem *item;
    pxOrderItem *newitem;
    pxOrder* seporder                  = NULL;   // separated  order
    pxCustOrderInfo* custinfo          = NULL;
    pxCustOrderInfo* sepordercustinfo  = NULL;
    pxOrderItemListIter it(*ItemList());
    nString KdAuftragArt;                      // ordertype
    char   CommiType   = ' ';                 // commi
    char   BuchArt = ' ';                     // book
    long   calculatedFromPos = FromPos;       // calculated position within ItemList
/*----------------------------------------------------------------------------*/
/*  some prechecks before further action has taking place                     */
/*----------------------------------------------------------------------------*/
    if ( CommType_->IsNoShipment() )
    {
       return ErrorState();
    }

    if ( IsDoNotSplittOrder() )
    {
       return ErrorState();
    }

    if ( IsSeparatedOrder() )                                     // if oder already separated
    {
       return ErrorState();                                       // do not try to split it again(anchor)
    }


    KdAuftragArt.Strip();
    KdAuftragArt = KdAuftragArt_;
    BuchArt      = BuchArt_;
    CommiType    = KoArt;

    pxCustRouteList *rl = RouteList();
    if ( rl == NULL )
    {
       return ErrorState();                                        // not possible to do anything
    }

    it.Reset();
    // Check ItemList for Valid positions.
    while ((item = (pxOrderItem*) ++it) != NULL)
    {
       if ((item->IsCancelled()) || (item->ArtikelNr() == 0) || (!item->IsKnownProduct()) || (item->MengeGeliefert() == 0) || (item->IsNachliefern()))
       {
          ++calculatedFromPos;
          continue;
       }
    }

    if ( calculatedFromPos >= AnzPos() )                           // prevent wrong positioning within ItemList
    {
       return ErrorState();
    }

    it.Reset();
    it += calculatedFromPos;                                                // preset iterator to PromPos
    // Now splitt this order from FromPos on
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
          continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if ( item->MengeGeliefert() == 0 )
          continue;
       if (!item->IsNachliefern() )
       {
          if ( seporder == NULL )
          {
             seporder = new pxOrder(Session(),*customer);
             if ( !seporder->IsGoodState() )
             {
                delete seporder;
                seporder = NULL;
                break;
             }
             seporder->OrderType(KdAuftragArt,CommiType,BuchArt);
             seporder->KdAuftragNrOrg(KdAuftragNr());
             seporder->DafueAuftragNr((long) cDCTSequenceNumDDELMax);
             seporder->DatumAuslieferung(DatumAuslieferung());
             seporder->setPurchaseOrderNo(getPurchaseOrderNo());
             seporder->HerkunftFiliale(HerkunftFiliale());
             seporder->BatchSchreiben(BatchSchreiben());
             seporder->SetPaymentTerm(PaymentTerm());
             seporder->Bemerkungen(Bemerkungen());
             seporder->SetOrderLabel(OrderLabel());
             seporder->SetSeparatedOrder();
             seporder->SetEncloserSplitt();
             seporder->RouteAssignNext( this->getTourInformation() ); // TourManagerIssue: Tourensuche bei Beifügern!!!

             if ( IsAuftragVomXML() )
                seporder->SetAuftragVomXML();

             // Look for Headtext
             pxTextDoc* headtext = HeadText();
             pxTextDoc* tailtext = TailText();
             pxTextDocIter headiter  = pxTextDocIter(*headtext);
             pxTextDocIter tailiter  = pxTextDocIter(*tailtext);
             if (headtext->Entries() > 0)
             {
                pxTextDoc *headp = seporder->HeadText();
                while ( (headtext = (pxTextDoc *) ++headiter) != NULL )
                {
                   nString headline = ((pxTextLine*) headtext)->Text();
                   headp->NewLine(headline);
                }
             }
             // Look for Tailtext
             if (tailtext->Entries() > 0)
             {
                pxTextDoc *tailp = seporder->TailText();
                while ( (tailtext = (pxTextDoc *) ++tailiter) != NULL )
                {
                   nString tailline = ((pxTextLine*) tailtext)->Text();
                   tailp->NewLine(tailline);
                }
             }
             custinfo = new pxCustOrderInfo(Session(), KdAuftragNr_);
             if ( custinfo->IsGoodState() )
             {
                 sepordercustinfo = new pxCustOrderInfo(*custinfo);
                 sepordercustinfo->SetOrderNr(seporder->KdAuftragNr());
                 sepordercustinfo->Put();
                 delete sepordercustinfo;
             }
             delete custinfo;
          }
          newitem = seporder->CopyOrderItem(item, pxOrderItem::SeparateArticle, SplittType_Unknown);
          newitem->UndoRedoItemDiscount(item);
          //newitem->IBTDeliveryItem(item);
          // now delete item members
          item->MengeBestaetigt( 0L);
          item->MengeGeliefert( 0L);
          item->MengeAbgebucht( 0L);
          item->MengeNatra( 0L);
          item->SetSeparatePosition();
          nString KdAuftragNr;
          KdAuftragNr = seporder->KdAuftragNr();

          nMessage msg(CMsgStream(), CMSG_ITM_SEPARATE_ARTGROUP_S, (char*)&KdAuftragNr);
          nString posbem = msg.String();
          posbem.Compress('\n');
          item->Bemerkungen(posbem);
       }
    }
    // Now close seporder
    if ( seporder )
    {
       seporder->Close(state);                 // set order state flags
       Error() = seporder->Error();            // copy Error
       delete seporder;
       seporder = NULL;
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  CheckEncloserTime: this function checks the current time against          */
/*  param.EncloserTiltTime(). The main problem is to block the route check    */
/*  for the encloserscale functionallity(just for XML orders) during order    */
/*  closing. This function checks the current time against the                */
/*  EncloserTiltTime. As long as current time is before the EncloserTiltTime  */
/*  this function always returns false. False means, during order closeing    */
/*  the normal RouteCheck will be done, otherwise we must block RouteCheck for*/
/*  this order. True means: block RouteCheck for this order                   */
/*  This function is called in pxOrder::Close and pxOrder::AAClose            */
/*----------------------------------------------------------------------------*/
bool pxOrder::CheckEncloserTime() // OK auch mit TourManager
{
    bool retval = false;
    long tour                  = 0;
    nDate now;
    nClock currenttime;
    long  cdaysecs = currenttime.GetDaySeconds();                 // absolute current time in seconds since midnight
    long  toursecs             = 0;
    long  encTilttime          = 0;

    if ( !hasToBeCheckEncloserScale() )
        return retval;

    tour         = atol((char*)(nString)(TourId())(0,4));
    nClock ctour(tour * 100);
    toursecs     = ctour.GetDaySeconds();                          // absolute tour time in seconds since midnight
    encTilttime  = toursecs - (Param()->EncloserTiltTime() * 60);     // absolute Beifügerkippzeit in seconds since midnight

    // is time slot reached
    if ( cdaysecs > encTilttime ) // time behind EncloserTiltTime
    {
       retval = true;             // block routecheck during orderclosing
    }
    return retval;
}


/*----------------------------------------------------------------------------*/
/* hasToBeCheckEncloserScale(): do some prechecks, before encloserscale       */
/* operations                                                                 */
/*----------------------------------------------------------------------------*/
bool pxOrder::hasToBeCheckEncloserScale() // OK auch mit TourManager
{
    bool retval = true;
    nDate now;

    // only running in Swiss and Austria
    if (!Session()->isSwitzerland() && !Session()->isAustria())   // just for Swiss and Austrian appl
       retval = false;

    // just for XML orders
    if ( !IsAuftragVomXML() )
        retval = false;

    // only if param.EncloserTiltTime() > 0
    if ( Param()->EncloserTiltTime() == 0 )                      // nothing to do
        retval = false;


    if( this->TourId().IsEmpty() )
    {
        retval = false;                                       // nothing to do
    }

    if ( IsEncloserSplitt() )
        retval = false;                                       // nothing to do

    if ( DatumAuslieferung() != pxConstants::NullDate && DatumAuslieferung() != now )
        retval = false;

    if ( IsSeparatedOrder() )                                 // if oder already separated
        retval = false;                                       // do not try to split it again(anchor)

    return retval;
}
