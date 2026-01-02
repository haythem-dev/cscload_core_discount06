#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxshuttlecustinfo.hpp"
#include "pxoclpar.hpp"
#include "pxeventreason.hpp"
#include "cremamailhandler.h"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"
#include "pxparameter.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"
#include "pxgoodsdelivery.hpp"


int pxOrder::AAClose(Order::States state, Order::CloseArgs args)
{
    SetDoNotAppend(); // not available for order consolidation any longer

    pxShuttleCustInfo* ShuttleInfo = NULL;
    bool ValidRoute = false;

    Order::States SepGroupState = Order::LeaveAsIs;
    /*----------------------------------------------------------------------------*/
    /*  Basic sanity checks.                                                      */
    /*----------------------------------------------------------------------------*/
    ClearError();
    if (!ItemList_)                    // then order item processing not open
        return ExternalError(CMsgStream(), CMSG_ORD_NOTOPEN, KdAuftragNr_);

    if (state >= Order::cStateLast || state < ~Order::cStateLast || state == Order::Cancelled)
        return ExternalError(CMsgStream(), CMSG_ORD_INVALID_STATE, KdAuftragNr_, (int)state);
    if (state == Order::LeaveAsIs && IsEntryInProgress())
        state = Order::EntryDeferred;
    nDate dateddel = DatumAuslieferung();   // date delayeddelivery
    nDate now;

    /*----------------------------------------------------------------------------*/
    /*  Additional sanity checks.                                                 */
    /*----------------------------------------------------------------------------*/
    if (!IsPseudoLock())
    {
        if (!IsLocked())                  // order still locked ??
        {
            ExternalError(CMsgStream(), CMSG_ORD_LOCK_DISAPPEARED, KdAuftragNr_);
            return NULL;
        }
    }

    /*----------------------------------------------------------------------------*/
    /*  Route assignment. A valid route must be assigned if order entry is still  */
    /*  active and this order is to be shipped.                                   */
    /*----------------------------------------------------------------------------*/
    if (!IsOrderViewing())
    {
        if (IsEntryInProgress())
        {
            ClearRouteCheck();            // must not do a route check for this order
            if (CommType().IsNoShipment())
                OrderTourId_.Clear();           // then clear route assignment
            else
            {
                if (this->TourId().IsEmpty())
                    RouteAssign();          // assign default route

                if (Param()->IsSIbtCstOrg() && BatchSchreiben() == cORTYPE_AUXILIARY)
                {
                    if (ShuttleCustomer(FilialNr_))
                    {
                        ShuttleInfo = new pxShuttleCustInfo(Session(), ShuttleCustomer_, FilialNr_);
                        ShuttleInfo->GetShuttleInfo();
                        if (ShuttleInfo->IsGoodState())
                        {
                            ValidRoute = ShuttleInfo->IsValidRouteForOrderClosure(this->TourId(), this->DatumAuslieferung());
                            if (!ValidRoute)
                            {
                                std::stringstream s;
                                s << "pxOrder::AAClose: Invalid Route after ShuttleInfo->IsValidRouteForOrderClosure for OrderNo: " << this->KdAuftragNr() << " TourId: " << this->TourId() << " Shuttle: " << ShuttleCustomer_->FilialNr() << "-" << ShuttleCustomer_->IDFNr();
                                BLOG_DEBUG(libcsc::LoggerPool::getLoggerTourManager(), s.str());
                            }
                        }
                        delete ShuttleInfo;
                    }
                }
                else
                {
                    if (CheckEncloserTime())
                    {
                        ValidRoute = true;
                    }
                    else
                    {
                        ValidRoute = IsValidRouteForOrderClose(this->TourId());
                        if (!ValidRoute)
                        {
                            std::stringstream s;
                            s << "pxOrder::AAClose: Invalid Route after IsValidRouteForOrderClose for OrderNo: " << this->KdAuftragNr() << " TourId: " << this->TourId();
                            BLOG_DEBUG(libcsc::LoggerPool::getLoggerTourManager(), s.str());
                        }
                    }
                }
                if (!ValidRoute)
                {                             // route is not valid
                    if (!(Session()->Device()->IsVideo()))
                    {                       // no video device, seems to be DCT
                        SetProblemClearance(); // manual clearance required
                        SetEventCode(pxEventReason::NoValidRoute); // OK
                        {
                            std::stringstream s;
                            s << "pxOrder::AAClose: EventCode NoValidRouteRoute due to invalid route for OrderNo: " << this->KdAuftragNr();
                            BLOG_INFO(libcsc::LoggerPool::getLoggerTourManager(), s.str());
                        }
                        SetRouteCheck();     // must do a manual route check
                        state = Order::EntryDeferred;  // force this state
                    }
                    if (state == Order::EntryDeferred)
                        ClearError();        // allow this order to be deferred
                    else                    // route assignment required
                        return ErrorState(); // when closing order entry
                }
                if (state == Order::EntryDeferred)
                    ClearError();
            }

            /*----------------------------------------------------------------------------*/
            /*  Scan all order items to build an item property summary.                   */
            /*----------------------------------------------------------------------------*/
            int coolerq = 0;        // no. of items requiring coolers
            int commiq = 0;        // items to be commissioned
            int opiateq = 0;        // no. of opiates
            int reshospital = 0;        // no. of reserve hospital
            int todisposalq = 0;        // items to disposal
            int toserviceq = 0;        // items to Customer Service branch
            int auxposq = 0;        // items with aux.positions
            int postrestdel = 0;        // postable restdelivery positions
            int zytosq = 0;        // no. of zytostatika
            int k04 = 0;        // no. of KuehlKetten Artikel
            int k08 = 0;        // no. of Gekuehlt08  Artikel
            int k20 = 0;        // no. of Gekuehlt20  Artikel
            int danggood = 0;        // count of dangerous articles
            int positivlistq = 0;        // count of positivlist articles (RS)
            int healthfundq = 0;        // article with pricetype = healthfund(KK BG)
            int retailq = 0;        // article with pricetype = retail(EV BG)
            int prisoq = 0;        // Privatsortiment
            int psychoq = 0;        // Psychotrp


/*----------------------------------------------------------------------------*/
/*  Automatic Restdelivery, just if AutoRestDelivery                          */
/*----------------------------------------------------------------------------*/
            if (Param()->IsAutoRestDelivery() &&
                !(Session()->Device()->IsVideo()) &&
                (StockTrans().IsDebit()) && KdAuftragNrOrg_ == 0 &&
                BatchAuftragNr_ == 0)
            {
                postrestdel = PostRestDelivery();  // Automatic Restdelivery
                if (IsGoodState() && postrestdel > 0)
                {
                    // just for non swiss customers
                    // kruekke
                    if (!Param()->IsDefektDispo())
                    {
                        SetProblemClearance();
                        SetEventCode(pxEventReason::WithReleasedDeliveryPositions);
                    }
                }
            }

            /*----------------------------------------------------------------------------*/
            /*  This is an order for delayed delivery, so prevent closing this order by   */
            /*  mistake                                                                   */
            /*----------------------------------------------------------------------------*/
            if (dateddel != pxConstants::NullDate && dateddel > now)
                state = Order::EntryDeferred;

            /*----------------------------------------------------------------------------*/
            /*  This is a "CC" order, special for France                                  */
            /*  Check if any nachliferpos is present for that order                       */
            /*----------------------------------------------------------------------------*/
            pxGoodsDeliveryList* GDlist = NULL;
            pxGoodsDelivery* GDentry = NULL;

            if  (this->OrderType().IsChronicIllnessOrder()) { //Session()->isFrance() &&
                // Check nachliefer pos
                nString         KdAuftragArt = "CC";

                GDlist = new pxGoodsDeliveryList(this->Session(), this->KdAuftragNr(), this->FilialNr(), this->IDFNr(), KdAuftragArt);

                if (!GDlist->Entries())               // no entries found
                {
                    delete GDlist;                       // delete the list
                    GDlist = NULL;
                }
            }

            /*----------------------------------------------------------------------------*/
            /*  Now scan the list of positions                                            */
            /*----------------------------------------------------------------------------*/
            pxOrderItemListIter it(*ItemList_);
            pxOrderItem* item;
            

            while ((item = (pxOrderItem*) ++it) != NULL)
            {
                if (!item->IsCancelled())
                {
                    // Special for France / CC order type
                    if (this->OrderType().IsChronicIllnessOrder() && GDlist != NULL) { ////Session()->isFrance() &&
                        // Check if requested quantity was fullfiled or not
                        pxGoodsDeliveryListIter GDiter(*GDlist);
                        while ((GDentry = (pxGoodsDelivery*) ++GDiter) != NULL){
                             if (GDentry->ArtikelNr() == item->ArtikelNr() && (item->PosNr() == GDentry->DeliveryPos()->PosNr())) {
                                if (item->Open() == nSTATE_GOOD)
                                {
                                   Session()->nDBBeginTransaction(cDBTransSet);   // open database transaction
                                   if (item->GetQtyInStock() > 0 )
                                   {  
                                       long QToPost = std::min(item->GetQtyInStock(), GDentry->DeliveryPos()->Menge()); // item->MengeBestellt());
                                       item->OrderQuantity(item->MengeAbgebucht()+QToPost, GDentry->DeliveryPos()->MengeNatra(), -1);
                                   }
                                   if (item != NULL) {
                                       GDentry->DeliveryPos()->Delete();              // delete NachLieferPos entry
                                       if (GDentry->DeliveryPos()->IsGoodState())   // if ok
                                       {
                                           delete GDiter.Remove();                     // delete object from list and
                                           Session()->nDBCommit(cDBTransSet);            // commit changes
                                       }
                                       else
                                       {
                                           Session()->nDBRollBack();                     // rollback changes
                                       }

                                       break;
                                   }
                                }
                             }
                        }
                    }
                    todisposalq += item->IsToDisposal();
                    toserviceq += item->IsToCustomerService();
                    toserviceq += item->IsAuxPosted();
                    toserviceq += item->IsInfoBelegDrucken();
                    auxposq += item->IsAuxPosted();

                    if (((item->MengeGeliefert() + item->MengeVerbund()) > 0) && item->IsProductStocked())
                    {
                        commiq += item->IsToCommission();
                        if (item->ArtBase() && item->ArtBase()->IsGoodState())
                        {
                            if (item->MengeGeliefert() > 0)
                            {
                                zytosq += item->ArtBase()->ArtFlags().IsZytoStatikaArtikel();
                                psychoq += item->ArtBase()->IsKzPsychoStoffe();
                            }
                            danggood += item->ArtBase()->ArtFlags().IsGefahrGutArtikel();
                            opiateq += item->ArtBase()->ArtClass().IsOpiat();
                            reshospital += item->ArtBase()->IsReserveHospital();
                            positivlistq += item->ArtBase()->IsPositivListe();
                            if (item->MengeGeliefert() > 0)
                            {
                                k04 += (item->ArtBase()->ArtFlags().IsKuehlKette() && (!item->ArtBase()->ArtClass().IsOpiat()));
                                k08 += (item->ArtBase()->ArtFlags().IsGekuehlt08() && (!item->ArtBase()->ArtClass().IsOpiat()));
                                k20 += (item->ArtBase()->ArtFlags().IsGekuehlt20() && (!item->ArtBase()->ArtClass().IsOpiat()));
                                // coolerq  += item->ArtBase()->ArtFlags().IsKuehlKette();
                                //if ( Param()->IsCoolerUnder8Degrees() )
                                //    coolerq  += item->ArtBase()->ArtFlags().IsGekuehlt08();
                            }
                        }
                    }
                    healthfundq += item->IsPriceTypeHealthFund();
                    retailq += item->IsPriceTypeRetail();
                    prisoq += item->IsPriso();
                }
            }

            if (GDlist != NULL) {
                delete GDlist;
                GDlist = NULL;
            }
            
            coolerq += (k04 + k08 + k20);

            if (danggood > 0)
                SetMitGefahrenGut();

            AnzBTM_ = opiateq;
            if ((toserviceq > 0) || (todisposalq > 0))
                SetCustomerService();   // customer service must be informed

            ClearAuxPositions();        // clear bit

            if (auxposq > 0)
                SetAuxPositions();      // mark order with aux positions

            if (Param()->IsSCrema() && !IsNoDebtLimitCheck() && !IsProblemClearance() && WertLieferung_ > pxConstants::mZero && !Param()->IsSStopCrema() && KdAuftragNrOrg_ == 0)
            {
                if (!IsKreditLimitErreicht())
                {
                    if (IsCreditSumOnTop())
                    {
                        CremaMailHandler handler(Session());
                        handler.sendMail(DLPercentage_, CustomerDebtLimit_, UsedCustomerCredit_, OrderValue_, KdAuftragNr_, this->Customer());

                        SetKreditLimitErreicht();
                        state = Order::EntryDeferred;     // force this state
                        ExternalError(CMsgStream(), CMSG_ORD_CREDITLIMIT_ONTOP);
                        if (!(Session()->Device()->IsVideo()) || args == Order::cClose_SeparatedOrder)
                        {
                            ClearError();           // to defere this Order
                        }
                        else
                        {
                            return ErrorState(); // go back to Video user
                        }
                    }
                    else
                    {
                        CremaMailHandler handler(Session());
                        handler.sendMail(DLPercentage_, CustomerDebtLimit_, UsedCustomerCredit_, OrderValue_, KdAuftragNr_, this->Customer());
                    }
                }
            }
            else if (state == Order::EntryClosed && !Session()->isBulgaria() && !IsNoDebtLimitCheck() && !Param()->IsSCrema() && !IsProblemClearance() && WertLieferung_ > pxConstants::mZero)
            {
                if (IsCreditSumOnTop() && !IsKreditLimitErreicht())
                {
                    SetKreditLimitErreicht();
                    state = Order::EntryDeferred;     // force this state
                    ExternalError(CMsgStream(), CMSG_ORD_CREDITLIMIT_ONTOP);
                    if (!(Session()->Device()->IsVideo()) || args == Order::cClose_SeparatedOrder)
                    {
                        ClearError();           // to defere this Order
                    }
                    else
                    {
                        return ErrorState(); // go back to Video user
                    }
                }
            }

            if (!Session()->isBulgaria() || (Session()->isBulgaria() && Param()->IsSCrema()))
            {
                if ((IsKreditLimitErreicht() || IsNoDebtLimitCheck()) && state == Order::EntryClosed)
                {
                    if (args != Order::cClose_UnConditional && !IsNoDebtLimitCheck())
                    {
                        state = Order::EntryDeferred;
                        ExternalError(CMsgStream(), CMSG_ORD_CLOSE_NOT_ALLOWED);
                        if (!(Session()->Device()->IsVideo()) || args == Order::cClose_SeparatedOrder)
                        {
                            ClearError();           // to defere this Order
                        }
                        else
                        {
                            return ErrorState(); // go back to Video user
                        }
                    }
                    else
                    {
                        CompleteCreditLimit();
                    }
                }
            }

            if (IsSeparateArtGroup() && state == Order::EntryClosed)
            {
                if (args != Order::cClose_UnConditional)
                {
                    state = Order::EntryDeferred;
                    ExternalError(CMsgStream(), CMSG_ORD_CLOSE_NOT_ALLOWED);
                    if (!(Session()->Device()->IsVideo()))
                    {
                        ClearError();           // to defere this Order
                    }
                    else
                    {
                        return ErrorState();
                    }
                }
            }

            if (IsDefferedForInternet() && state == Order::EntryClosed)
            {
                if (args != Order::cClose_UnConditional)
                {
                    state = Order::EntryDeferred;
                    ExternalError(CMsgStream(), CMSG_ORD_CLOSE_NOT_ALLOWED);
                    if (!(Session()->Device()->IsVideo()))
                    {
                        ClearError();           // to defere this Order
                    }
                    else
                    {
                        return ErrorState();
                    }
                }
            }

            if (!(Session()->Device()->IsVideo()))
            {                       // no video device, seems to be DCT
                if (IsProblemClearance())
                    state = Order::EntryDeferred;
            }

            if (IsOrderConsolidation())
                SetConsolidation();

            /*----------------------------------------------------------------------------*/
            /*           XML Beifüger for the Swiss application                           */
            /*----------------------------------------------------------------------------*/
            if (state == Order::EntryClosed)
            {
                SepGroupState = XMLEncloserScale(state);
                if (SepGroupState != Order::LeaveAsIs)
                    state = (Order::States)SepGroupState;
                CountSpecialProducts(coolerq, opiateq, zytosq);
            }
            /*----------------------------------------------------------------------------*/
            /*          Special OMG Rebate Handling for the Swiss application             */
            /*----------------------------------------------------------------------------*/
            if (Session()->isSwitzerland() && state == Order::EntryClosed)
            {
                SpecialOmgRebateHandling();
            }

            /*----------------------------------------------------------------------------*/
            /*        Calculate Rangecondition                                            */
            /*----------------------------------------------------------------------------*/
            if (state == Order::EntryClosed && !Session()->isBulgaria())
            {
                if ((!IsSeparateArtGroup() && KdAuftragNrOrg_ == 0) || IsEncloserSplitt()) // splitt order ??
                {
                    RangeCalculation();           // calculate rangeconditions
                }
            }

            /*----------------------------------------------------------------------------*/
            /*        Do DayNightMerge on this order                                      */
            /*----------------------------------------------------------------------------*/
            SepGroupState = DayNightMergeProcessing(auxposq);
            if (SepGroupState != Order::LeaveAsIs)
            {
                state = (Order::States)SepGroupState;
            }

            /*----------------------------------------------------------------------------*/
            /*        IBTSPLITT ANNA                                                      */
            /*----------------------------------------------------------------------------*/
            if (state == Order::EntryClosed || closeIBTAtOnce())
            {
                SeparateIbtBranchLines();
            }

            /*----------------------------------------------------------------------------*/
            /*        Do Seperate Reference Number                                        */
            /*        Special function for VersandApotheke                                */
            /*----------------------------------------------------------------------------*/
            SepGroupState = SeparateReferenceNr(auxposq); // versandapo
            if (SepGroupState != Order::LeaveAsIs)
            {
                state = (Order::States)SepGroupState;
            }

            /*----------------------------------------------------------------------------*/
            /*        Splitting of special article just if OrderConsolidation             */
            /*----------------------------------------------------------------------------*/
            if (!IsSeparateArtGroup() && KdAuftragNrOrg_ == 0 && !Session()->isBulgaria())  // already separated ???
            {
                if (state == Order::EntryClosed)
                {
                    SepGroupState = SeparateSpecials(coolerq, opiateq, reshospital, zytosq, auxposq, psychoq);
                    if (SepGroupState != Order::LeaveAsIs)
                        state = (Order::States)SepGroupState;
                }
            }

            if (state == Order::EntryClosed)
            {
                if (Croatia())
                {
                    CloseValDateCroatia();
                    ValMonthManuell();
                    // RestDeliveryValdate();
                }
                else
                {
                    CloseValDate();
                    ValMonthManuell();
                    RestDeliveryValdate();
                }

                if (CheckHighValuePositions())   // Serbia application
                {
                    SetHighValuePosition();
                    state = Order::EntryDeferred;
                    SetProblemClearance();
                    SetEventCode(pxEventReason::HighValuePosition);
                    CloseState(state);               // set order state flags
                    ClearError();
                    return CloseOrder();             // finally close the order
                }
                /*----------------------------------------------------------------------------*/
                /*  Implement Delayeddelivery Split here to prevent illegal booking of        */
                /*  automatic positions p.e coolbox etc                                       */
                /*----------------------------------------------------------------------------*/
                if (KdAuftragNrOrg_ == 0)       // this is not a delayed order
                {
                    SepGroupState = SeparateDelayedDelivery(0L, coolerq, opiateq, zytosq);
                    if (SepGroupState != Order::LeaveAsIs)
                        state = (Order::States)SepGroupState;
                }

                SeparateContainer();          // calculate container

                SeparatePrisoPositions(prisoq);           // splitt Priso Positions

                SeparateReferenceNr(auxposq);                                   // versandapo

                SepGroupState = SeparateManufacturerPositions();          // split positions from manufacturer (IvryLab inventory)
                if (SepGroupState != Order::LeaveAsIs)
                    state = (Order::States)SepGroupState;

                ChangeContainerLevel();                   // change stocklevel(Serbian application)

                SeparatePositivListPositions(positivlistq);

                //if (Session()->isBulgaria() && args != Order::cClose_SeparatedOrder && !IsSeparatedOrder() && KdAuftragNrOrg_ == 0 && dateddel == pxConstants::NullDate)
                if (Session()->isBulgaria() && args != Order::cClose_SeparatedOrder && !IsSeparatedOrder() && KdAuftragNrOrg_ == 0)
                {
                    
                        logItemDiscountValuePct();
                        CheckPromotionValidity(state);
                        TargetPromotionCalculation();           // calculate rangeconditions
                        if (this->IsNoCreditLimitCheck())     // Ticket SR-15068713 Flag was set in methode CheckPromotionValidity
                        {                                       // this happens only if this->DatumAuslieferung() not = 0
                            this->ClearNoCreditLimitCheck();    // clear flag
                            this->ReCalcValuesOrderValues();    // we have to do a recalculation of the order values
                            if (!(isCashOrder() && IsNoDebtLimitCheck()))
                            {
                                this->RedoCreditDayTurnOver(OrderValue_);      // now redo credit sum day turn over. Undo was done in methode CheckPromotionValidity
                            }
                            if (!this->IsKreditLimitErreicht())
                            {
                                nMoney DiffValue = this->checkCreditLimitOverflow(); // check credit limit overflow(may some conditions changed)
                                if (DiffValue != pxConstants::mZero)
                                {
                                    ExternalCondition(CMsgStream(), CMSG_ORD_CREDITLIMIT_EXHAUSTED, (double)DiffValue);
                                    if (!(Session()->Device()->IsVideo()))
                                    {
                                        state = Order::EntryDeferred;
                                        SetProblemClearance();
                                        SetEventCode(pxEventReason::CreditLimitExceeded);
                                        ClearError();
                                        CloseState(state);               // set order state flags
                                        return CloseOrder();             // finally close the order
                                    }
                                    else
                                    {
                                        return ErrorState();
                                    }
                                }
                            }
                        }//end SR-15068713
                    

                    if (IsRebateArtSelection())
                    {
                        state = Order::EntryDeferred;
                        SetProblemClearance();
                        SetEventCode(pxEventReason::RebateArticleSelection);
                        CloseState(state);               // set order state flags
                        return CloseOrder();             // finally close the order
                    }
                }

                SeparatePriceType(healthfundq, retailq);
                if (SepGroupState != Order::LeaveAsIs)
                    state = (Order::States)SepGroupState;

                SepGroupState = SeparateBigOrder();
                if (SepGroupState != Order::LeaveAsIs)
                    state = (Order::States)SepGroupState;

                SepGroupState = SeparateListFivePositions();
                if (SepGroupState != Order::LeaveAsIs)
                    state = (Order::States)SepGroupState;

                /*----------------------------------------------------------------------------*/
                /*           Splitting of special article just for Bulgarian application      */
                /*----------------------------------------------------------------------------*/
                if ((Session()->isBulgaria()))  // just bulgarian application ???
                {
                    SepGroupState = SeparateSpecials(coolerq, opiateq, reshospital, zytosq, auxposq, psychoq);
                    if (SepGroupState != Order::LeaveAsIs)
                    {
                        state = (Order::States)SepGroupState;
                    }
                }

                // split order lines with different tour
                if (state == Order::EntryClosed)
                {
                    SepGroupState = SeparateOrderLinesWithDifferentTour(coolerq, opiateq, zytosq);
                    if (SepGroupState != Order::LeaveAsIs)
                    {
                        state = SepGroupState;
                    }
                }

                if (state == Order::EntryClosed)
                {
                    AutoItems(coolerq, opiateq, zytosq, commiq); // automatic order item entry
                    BookAddOnChargeArticleNoDependOnCodeBlocage();    // book addoncharge article depen on codeblocage for this order->KdAuftragArt()
                }
                // wird im ksc nicht mehr gebraucht
                if (IsGoodState())
                    TriggerInvoice(commiq, state);   //  determine if order may be invoiced
                if (CommType().IsShipDisposal() || CommType().IsShipDeliveryNote())
                    SetCustomerService();
            }
            LogisticVolume_ = CalcLogisticVolume();         // Calculate volume for collective orders

        }                               // end-if IsEntryInProgress()

        CloseState(state);              // set order state flags

    }                                   // end-if !IsOrderViewing()

    return CloseOrder();                // finally close the order
}
