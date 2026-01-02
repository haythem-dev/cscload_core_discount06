#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordervalues.hpp"
#include "pxordevt.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxoclpar.hpp"
#include "pxshuttlecustinfo.hpp"
#include "pxeventreason.hpp"
#include "cremamailhandler.h"
#include "pxstockbooking.hpp"
#include "pxtxtdoc.hpp"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"
#include "ibtrequesthandler.h"
#include <libbasarcmnutil_datetime.h>
#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_datetimetools.h>
#include <libbasarcmnutil_timespan.h>
#include "pxparameter.hpp"
#ifdef WIN32
#include <windows.h>
#endif

int pxOrder::Close(Order::States state, Order::CloseArgs args)
{
    basar::DateTime closeStartTimestamp = basar::cmnutil::DateTime::getCurrent();
    std::stringstream closePerformanceMessurement;
    closePerformanceMessurement.str(std::string());
    closePerformanceMessurement << "pxOrder::Close [" << this->KdAuftragNr() << "] Bad Performance:";
    closePerformanceMessurement << "\n\t\t\t" << closeStartTimestamp.toStrDateTime() << " -> close Start Timestamp ";

    pxShuttleCustInfo* ShuttleInfo = NULL;

    bool ValidRoute = false;

    // Log starting of order closure!!!
    {
        std::stringstream orderCloseStarted;
        orderCloseStarted.str(std::string());
        orderCloseStarted << "pxOrder::Close ORDERNO[" << this->KdAuftragNr() << "]  CLOSE STARTED";
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStarted.str());
    }

    std::stringstream orderCloseStates;
    orderCloseStates.str(std::string());
    orderCloseStates << "pxOrder::Close ORDERNO[" << this->KdAuftragNr() << "] ";
    orderCloseStates << "State(" << state << ") -> ";

    Order::States savestate = Order::LeaveAsIs;
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
    {
        state = Order::EntryDeferred;
        orderCloseStates << "Deferred#01(" << state << ") ";
    }

    nDate dateddel = DatumAuslieferung();  // date delayeddelivery
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
/*----------------------------------------------------------------------------*/
/*  Route assignment. The TourId_ will be cleared under the following         */
/*  circumstances: CommType is NoShipment.                                    */
/*  The next reason is: if date of delayed delivery(AusLieferungsDatum_)      */
/*  is not today, so clear TourId_, because on the day of delivery, the next  */
/*  reachable Tour will be calculated automaticly.                            */
/*----------------------------------------------------------------------------*/
            /* if ( CommType().IsNoShipment() || (dateddel > now && KdAuftragNrOrg_ == 0))
                TourId_.Clear();            // then clear route assignment
            */
            if (CommType().IsNoShipment())
            {
                OrderTourId_.Clear();            // then clear route assignment
            }
            else
            {
                if (this->TourId().IsEmpty())
                {
                    RouteAssign(); // assign current route
                }

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
                                s << "pxOrder::Close: Invalid Route after ShuttleInfo->IsValidRouteForOrderClosure for OrderNo: " << this->KdAuftragNr() << " TourId: " << this->TourId() << " Shuttle: " << ShuttleCustomer_->FilialNr() << "-" << ShuttleCustomer_->IDFNr();
                                BLOG_INFO(libcsc::LoggerPool::getLoggerTourManager(), s.str());
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
                            s << "pxOrder::Close: Route not valid after IsValidRouteForOrderClose! OrderNo: " << this->KdAuftragNr() << " TourID: " << this->TourId();
                            BLOG_INFO(libcsc::LoggerPool::getLoggerTourManager(), s.str());
                            state = setNoValidRoute("invalid route");
                            orderCloseStates << "NoValidRoute#01(" << state << ") ";
                        }
                    }
                }
                if (!ValidRoute && AnzPos_ > 0)
                {                             // route is not valid
                    if (!(Session()->Device()->IsVideo()) || args == Order::cClose_SeparatedOrder)
                    {                       // no video device, seems to be DCT
                        /*if ( KdAuftragNrOrg_ == 0 || (KdAuftragNrOrg_ > 0 && dateddel == pxConstants::NullDate ) )
                        { */
                        state = setNoValidRoute("invalid route");
                        orderCloseStates << "NoValidRoute#02(" << state << ") ";
                        /* } */
                    }
                    if (state == Order::EntryDeferred)
                    {
                        ClearError();        // allow this order to be deferred
                    }
                    else
                    {
                        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                        // route assignment required
                        return ErrorState(); // when closing order entry
                    }
                }

                if (!(Session()->Device()->IsVideo()) && AnzPos_ == 0)
                {
                    if (!ValidRoute)
                    {
                        ClearError();
                    }
                }

                if (state == Order::EntryDeferred)
                {
                    ClearError();
                }

                if (this->TourId().IsEmpty())
                {
                    state = setNoValidRoute("empty TourId");
                    orderCloseStates << "NoValidRoute#03(" << state << ") ";
                }
            }

            /*----------------------------------------------------------------------------*/
            /*  Scan all order items to build an item property summary.                   */
            /*----------------------------------------------------------------------------*/
            bool quantityLimitCheck = false; // max. quantity per position exceeded
            int coolerq = 0;        // no. of items requiring coolers
            int commiq = 0;        // items to be commissioned
            int opiateq = 0;        // no. of opiates
            int reshospital = 0;        // no. of reserve hospital positions
            int todisposalq = 0;        // items to disposal
            int toserviceq = 0;        // items to Customer Service branch
            int auxposq = 0;        // items with aux.positions
            int postrestdel = 0;        // postable restdelivery positions
            int zytosq = 0;        // no. of zytostatika
            int k04 = 0;        // no. of KuehlKetten Artikel
            int k08 = 0;        // no. of Gekuehlt08  Artikel
            int k20 = 0;        // no. of Gekuehlt20  Artikel
            int danggood = 0;        // count of dangerous articles
            int freightage = 0;        // Freightage article
            int positivlistq = 0;        // positiv list article
            int healthfundq = 0;        // article with pricetype = healthfund(KK BG)
            int retailq = 0;        // article with pricetype = retail(EV BG)
            int prisoq = 0;        // Privatsortiment
            int psychoq = 0;        // Psychotrop

/*----------------------------------------------------------------------------*/
/*  Automatic Restdelivery, just if AutoRestDelivery                          */
/*----------------------------------------------------------------------------*/
            closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement Point 1 ";

            // 07.11.2012 IsAuftragVomXML() rausgenommen weil Nachlieferpositonen nicht aufgelöst wurden. ?? warum war die Abfrage drin
            if (   Param()->IsAutoRestDelivery()
                && !(Session()->Device()->IsVideo())
                && (StockTrans().IsDebit())
                && KdAuftragNrOrg_ == 0
                && AnzPos_ > 0
                && BatchAuftragNr_ == 0 && !IsNoDebtLimitCheck() )
            {
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement start PostRestDelivery";
                postrestdel = PostRestDelivery();  // Automatic Restdelivery
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished PostRestDelivery";
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
            dateddel = DatumAuslieferung();

            //dateddel = DatumAuslieferung();
            if (dateddel != pxConstants::NullDate && IsCollectiveOrderDiscountable())
            {
                savestate = state;
                state = Order::EntryDeferred;
                orderCloseStates << "Deferred#02(" << state << ") ";

                if ((!IsSeparateArtGroup() && KdAuftragNrOrg_ == 0)) // splitt order ??
                {
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement start RangeCalculation ";
                    RangeCalculation();           // calculate rangeconditions
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished RangeCalculation ";
                }
            }
            else
                if (dateddel != pxConstants::NullDate)
                {
                    savestate = state;
                    state = Order::EntryDeferred;
                    orderCloseStates << "Deferred#03(" << state << ") ";

                    if (!(Session()->Device()->IsVideo()))
                    {
                        ClearError();
                    }
                    // order from vborderimport or ibtorderimport(Verbundauftrag)
                    if (savestate == Order::EntryClosed && BatchSchreiben() == cORTYPE_AUXILIARY && dateddel <= now)
                    {
                        if (Param()->MaxPosVerbund() > 0)
                        {
                            if (AnzPos() > Param()->MaxPosVerbund())
                            {
                                state = savestate;
                                orderCloseStates << "MaxPosVB#01(" << state << ") ";
                            }
                        }
                    }
                }

            // this order must be closed unconditional
            if (savestate == Order::EntryClosed && args == Order::cClose_UnConditional && (dateddel <= now))
            {
                if (Session()->Device()->IsVideo())
                {
                    state = savestate;
                    orderCloseStates << "Unconditional#01(" << state << ") ";
                }
            }

            if (dateddel <= now && BatchSchreiben_ > 0 && savestate == Order::EntryClosed && Session()->Device()->IsVideo())
            {
                // read kdauftragendezeit
                pxOrderCloseParamList closeparamlist(Session());
                closeparamlist.Select(VertriebsZentrumNr_);
                if (!closeparamlist.FindBatchSchreiben(BatchSchreiben_))
                {
                    state = savestate;
                    orderCloseStates << "BatchSchreiben#01(" << state << ") ";
                }
            }

            /*----------------------------------------------------------------------------*/
            /*  Now scan the list of positions                                            */
            /*----------------------------------------------------------------------------*/
            quantityLimitCheck = checkQuantityLimit();

            pxOrderItemListIter it(*ItemList_);
            pxOrderItem* item;
            while ((item = (pxOrderItem*) ++it) != NULL)
            {
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement start PositionList " << item->PosNr();
                if (!item->IsCancelled())
                {
                    todisposalq += item->IsToDisposal();
                    toserviceq += item->IsToCustomerService();
                    toserviceq += item->IsAuxPosted();
                    toserviceq += item->IsInfoBelegDrucken();
                    auxposq += item->IsAuxPosted();

                    if (item->ArtBase() && Param()->PZNFreightage() > 0)
                    {
                        if (item->ArtikelNr() == Param()->PZNFreightage())
                            ++freightage;
                    }

                    if (((item->MengeGeliefert() + item->MengeVerbund()) > 0) && item->IsProductStocked())
                    {
                        if (item->MengeGeliefert() > 0)
                        {
                            zytosq += item->ArtBase()->ArtFlags().IsZytoStatikaArtikel();
                        }

                        danggood += item->ArtBase()->ArtFlags().IsGefahrGutArtikel();
                        commiq += item->IsToCommission();
                        if (item->MengeGeliefert() > 0)
                        {
                            k04 += (item->ArtBase()->ArtFlags().IsKuehlKette() && (!item->ArtBase()->ArtClass().IsOpiat()));
                            k08 += (item->ArtBase()->ArtFlags().IsGekuehlt08() && (!item->ArtBase()->ArtClass().IsOpiat()));
                            k20 += (item->ArtBase()->ArtFlags().IsGekuehlt20() && (!item->ArtBase()->ArtClass().IsOpiat()));
                            // coolerq  += item->ArtBase()->ArtFlags().IsKuehlKette();
                            //if ( Param()->IsCoolerUnder8Degrees() )
                            //   coolerq  += item->ArtBase()->ArtFlags().IsGekuehlt08();
                        }
                        opiateq += item->ArtBase()->ArtClass().IsOpiat();
                        reshospital += item->ArtBase()->IsReserveHospital();
                        positivlistq += item->ArtBase()->IsPositivListe();
                        psychoq += item->ArtBase()->IsKzPsychoStoffe();
                    }
                    healthfundq += item->IsPriceTypeHealthFund();
                    retailq += item->IsPriceTypeRetail();
                    prisoq += item->IsPriso();
                }

                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished PositionList " << item->PosNr();
            }

            // Calculate Freightage depend on count freightage article
            Freightage(freightage);

            coolerq += (k04 + k08 + k20);

            if (danggood > 0)
                SetMitGefahrenGut();

            AnzBTM_ = opiateq;
            if ((toserviceq > 0) || (todisposalq > 0))
                SetCustomerService();   // customer service must be informed

            ClearAuxPositions();       // clear bit

            if (auxposq > 0)
                SetAuxPositions();      // mark order with aux positions


            if (!(Session()->Device()->IsVideo()) && args != Order::cClose_UnConditional)
            {                       // no video device, seems to be DCT
                if (true == quantityLimitCheck && (BatchSchreiben() == cORTYPE_UNKNOWN))
                {
                    SetProblemClearance();
                    SetEventCode(pxEventReason::LimitCheck);
                    SetQuantityLimitCheck();
                }
                /*----------------------------------------------------------------------------*/
                /*  If the value of all corrupt positions > Param()->DefwertKeinAbschl(), so   */
                /*  the orderstate = SetPromblemClearance and the Bit CorruptLimitCheck raises*/
                /*----------------------------------------------------------------------------*/
                if ((Param()->DefwertKeinAbschl() > 0) && !IsProblemClearance())
                {
                    if (CheckCorruptLimit())
                    {
                        SetProblemClearance();
                        SetEventCode(pxEventReason::CorruptLimitCheck);
                        SetCorruptLimitCheck();
                    }
                }

                if (IsProblemClearance())
                {
                    state = Order::EntryDeferred;
                    orderCloseStates << "Deferred#04(" << state << ") ";
                    ClearConsolidation();
                }
            }

            if (Param()->IsSCrema() && !IsNoDebtLimitCheck() && !IsProblemClearance() && WertLieferung_ > pxConstants::mZero && !Param()->IsSStopCrema() && KdAuftragNrOrg_ == 0)
            {
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement start KreditLimit ";
                if (!IsKreditLimitErreicht())
                {
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement start KreditLimit erreicht ";
                    if (IsCreditSumOnTop())
                    {
                        CremaMailHandler handler(Session());
                        handler.sendMail(DLPercentage_, CustomerDebtLimit_, UsedCustomerCredit_, OrderValue_, KdAuftragNr_, this->Customer());

                        SetKreditLimitErreicht();
                        state = Order::EntryDeferred;
                        orderCloseStates << "Deferred#05(" << state << ") ";
                        ExternalError(CMsgStream(), CMSG_ORD_CREDITLIMIT_ONTOP);
                        if (!(Session()->Device()->IsVideo()) || args == Order::cClose_SeparatedOrder)
                        {
                            ClearError();           // to defere this Order
                        }
                        else
                        {
                            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                            return ErrorState(); // go back to Video user
                        }
                    }
                    else
                    {
                        CremaMailHandler handler(Session());
                        handler.sendMail(DLPercentage_, CustomerDebtLimit_, UsedCustomerCredit_, OrderValue_, KdAuftragNr_, this->Customer());
                    }
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished KreditLimit erreicht ";
                }
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished KreditLimit ";
            }
            else if (state == Order::EntryClosed && !Session()->isBulgaria() && !IsNoDebtLimitCheck() && !Param()->IsSCrema() && !IsProblemClearance() && WertLieferung_ > pxConstants::mZero)
            {
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement start KreditLmt ";
                if (IsCreditSumOnTop() && !IsKreditLimitErreicht())
                {
                    SetKreditLimitErreicht();
                    state = Order::EntryDeferred;
                    orderCloseStates << "Deferred#06(" << state << ") ";
                    ExternalError(CMsgStream(), CMSG_ORD_CREDITLIMIT_ONTOP);
                    if (!(Session()->Device()->IsVideo()) || args == Order::cClose_SeparatedOrder)
                    {
                        ClearError();           // to defere this Order
                    }
                    else
                    {
                        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                        return ErrorState(); // go back to Video user
                    }
                }
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished KreditLmt ";
            }

            if (!Session()->isBulgaria() || (Session()->isBulgaria() && Param()->IsSCrema()))
            {
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started KreditLimitDeferred ";
                if ((IsKreditLimitErreicht() || IsNoDebtLimitCheck()) && state == Order::EntryClosed)
                {
                    if (args != Order::cClose_UnConditional && !IsNoDebtLimitCheck())
                    {
                        state = Order::EntryDeferred;
                        orderCloseStates << "Deferred#07(" << state << ") ";
                        ExternalError(CMsgStream(), CMSG_ORD_CLOSE_NOT_ALLOWED);
                        if (!(Session()->Device()->IsVideo()) || args == Order::cClose_SeparatedOrder)
                        {
                            ClearError();           // to defere this Order
                        }
                        else
                        {
                            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                            return ErrorState(); // go back to Video user
                        }
                    }
                    else
                    {
                        CompleteCreditLimit();
                    }
                }
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished KreditLimitDeferred ";
            }

            if (IsSeparateArtGroup() && state == Order::EntryClosed)
            {
                if (args != Order::cClose_UnConditional)
                {
                    state = Order::EntryDeferred;
                    orderCloseStates << "Deferred#08(" << state << ") ";
                    ExternalError(CMsgStream(), CMSG_ORD_CLOSE_NOT_ALLOWED);
                    if (!(Session()->Device()->IsVideo()))
                    {
                        ClearError();           // to defere this Order
                    }
                    else
                    {
                        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                        return ErrorState();
                    }
                }
            }

            if (IsDefferedForInternet() && state == Order::EntryClosed)
            {
                if (args != Order::cClose_UnConditional)
                {
                    state = Order::EntryDeferred;
                    orderCloseStates << "Deferred#09(" << state << ") ";
                    ExternalError(CMsgStream(), CMSG_ORD_CLOSE_NOT_ALLOWED);
                    if (!(Session()->Device()->IsVideo()))
                    {
                        ClearError();           // to defere this Order
                    }
                    else
                    {
                        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                        return ErrorState();
                    }
                }
            }

            if (IsOrderConsolidation())
            {
                SetConsolidation();
            }

            /*----------------------------------------------------------------------------*/
            /*           XML Beifüger for the Swiss application                           */
            /*----------------------------------------------------------------------------*/
            if (state == Order::EntryClosed)
            {
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started XMLBeifueger ";
                SepGroupState = XMLEncloserScale(state);
                if (SepGroupState != Order::LeaveAsIs)
                {
                    state = (Order::States)SepGroupState;
                    orderCloseStates << "XMLBeifueger#01(" << state << ") ";
                }
                CountSpecialProducts(coolerq, opiateq, zytosq);
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished XMLBeifueger ";
            }

            /*----------------------------------------------------------------------------*/
            /*          Special OMG Reabte Handling for the Swiss applicatiobn            */
            /*----------------------------------------------------------------------------*/
            if (Session()->isSwitzerland() && state == Order::EntryClosed)
            {
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started CH Tender ";
                SpecialOmgRebateHandling();
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished CH Tender ";
            }

            /*----------------------------------------------------------------------------*/
            /*        Calculate Rangecondition                                            */
            /*----------------------------------------------------------------------------*/
            if (state == Order::EntryClosed && !Session()->isBulgaria())
            {
                if ((!IsSeparateArtGroup() && KdAuftragNrOrg_ == 0) || IsEncloserSplitt()) // splitt order ??
                {
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started RangeCalculation (not BG)";
                    RangeCalculation();           // calculate rangeconditions
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished RangeCalculation (not BG)";
                }
            }

            /*----------------------------------------------------------------------------*/
            /*        Do DayNightMerge on this order                                      */
            /*----------------------------------------------------------------------------*/
            closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started DayNightMerge";
            SepGroupState = DayNightMergeProcessing(auxposq);
            if (SepGroupState != Order::LeaveAsIs)
            {
                state = (Order::States)SepGroupState;
                orderCloseStates << "SepDayNightMerge#01(" << state << ") ";
            }
            closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished DayNightMerge";

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
            closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started SepReference";
            SepGroupState = SeparateReferenceNr(auxposq); // versandapo
            if (SepGroupState != Order::LeaveAsIs)
            {
                state = (Order::States)SepGroupState;
                orderCloseStates << "SepReferenceNr#01(" << state << ") ";
            }
            closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished SepReference";

            /*----------------------------------------------------------------------------*/
            /*        Splitting of special article just if OrderConsolidation             */
            /*----------------------------------------------------------------------------*/
            if ((!IsSeparateArtGroup() && KdAuftragNrOrg_ == 0 && !Session()->isBulgaria()) || IsEncloserSplitt())  // already separated ???
            {
                if (dateddel == pxConstants::NullDate)
                {
                    if (IsOrderConsolidation())
                    {
                        closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started SepSpecials OrderCons";
                        SepGroupState = SeparateSpecials(coolerq, opiateq, reshospital, zytosq, auxposq, psychoq);
                        if (SepGroupState != Order::LeaveAsIs)
                        {
                            state = (Order::States)SepGroupState;
                            orderCloseStates << "SepSpecials#01(" << state << ") ";
                        }
                        closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished SepSpecials OrderCons";
                    }
                    else
                        if (state == Order::EntryClosed)
                        {
                            closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started SepSpecials";
                            SepGroupState = SeparateSpecials(coolerq, opiateq, reshospital, zytosq, auxposq, psychoq);
                            if (SepGroupState != Order::LeaveAsIs)
                            {
                                state = (Order::States)SepGroupState;
                                orderCloseStates << "SepSpecials#02 (" << state << ") ";
                            }
                            closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished SepSpecials";
                        }
                }
                else
                    if (Session()->isFrancePrewhole())
                    {
                        closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started SepSpecials PFR";
                        SepGroupState = SeparateSpecials(coolerq, opiateq, reshospital, zytosq, auxposq, psychoq);
                        if (SepGroupState != Order::LeaveAsIs)
                        {
                            state = (Order::States)SepGroupState;
                            orderCloseStates << "SepSpecials#03(" << state << ") ";
                        }
                        closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished SepSpecials PFR";
                    }
            }

            if (dateddel == pxConstants::NullDate && !Session()->isBulgaria() && false == quantityLimitCheck)
            {
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started SepContainer";
                SepGroupState = SeparateContainer();  // calculate container
                if (SepGroupState != Order::LeaveAsIs)
                {
                    state = (Order::States)SepGroupState; // SepContainer#01
                    orderCloseStates << "SepContainer (" << state << ") ";
                }
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished SepContainer";
            }

            if (state == Order::EntryClosed)
            {
                ReduceCustConditions();            // french application

                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started CloseValuta";
                if (Croatia())
                {
                    CloseValDateCroatia();
                    ValMonthManuell();
                    //RestDeliveryValdate();
                }
                else
                {
                    CloseValDate();
                    ValMonthManuell();
                    RestDeliveryValdate();
                }
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished CloseValuta";

                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started CloseTender";
                CloseTenderPos();                  // Serbia/Bulgarien application
                CloseTenderHead();                 // Serbia/Bulgarien application
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished CloseTender";

                if (CheckHighValuePositions())   // Serbia application
                {
                    SetHighValuePosition();
                    if (!(Session()->Device()->IsVideo()))
                    {
                        state = Order::EntryDeferred;
                        orderCloseStates << "Deferred#10(" << state << ") ";
                        SetProblemClearance();
                        SetEventCode(pxEventReason::HighValuePosition);
                        CloseState(state);           // set order state flags
                        ClearError();
                        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                        return CloseOrder();         // finally close the order
                    }
                    else
                    {
                        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                        return ErrorState();
                    }
                }

                /*----------------------------------------------------------------------------*/
                /*  Implement Delayeddelivery Split here to prevent illegal booking of        */
                /*  automatic positions p.e coolbox etc                                       */
                /*----------------------------------------------------------------------------*/
                if ((KdAuftragNrOrg_ == 0 || IsSeparateArtGroup()) || IsEncloserSplitt())  // this is not a delayed order
                {
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started SeparateDD";
                    SepGroupState = SeparateDelayedDelivery(0L, coolerq, opiateq, zytosq);
                    if (SepGroupState != Order::LeaveAsIs)
                    {
                        state = (Order::States)SepGroupState;
                        orderCloseStates << "DelayedDelivery (" << state << ") ";
                    }
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished SeparateDD";
                }

                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started Separate Priso,CAP,Manufacturer";
                SeparatePrisoPositions(prisoq);           // splitt Priso Positions
                SeparateCapPositions();                   // split Cap positions(kdauftragpos->BusinessOrderType == 4)

                SepGroupState = SeparateManufacturerPositions();          // split positions from manufacturer (IvryLab inventory)
                if (SepGroupState != Order::LeaveAsIs)
                {
                    state = (Order::States)SepGroupState; // SepManufacturer
                    orderCloseStates << "SepManufacturer (" << state << ") ";
                }
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished Separate Priso,CAP,Manufacturer";

                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started SeparateReference VA";
                SeparateReferenceNr(auxposq); // versandapo
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished SeparateReference VA";

                ChangeContainerLevel();                   // change stocklevel(Serbian application)

                SepGroupState = SeparatePositivListPositions(positivlistq);
                if (SepGroupState != Order::LeaveAsIs)
                {
                    state = (Order::States)SepGroupState; // SepPosList
                    orderCloseStates << "SepPositiveList (" << state << ") ";
                }

                if (Session()->isBulgaria() && args != Order::cClose_SeparatedOrder && (args != Order::cClose_UnConditional || (args == Order::cClose_UnConditional && IsNoDebtLimitCheck())))
                {
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
                                nMoney DiffValue = this->checkCreditLimitOverflow();  // check credit limit overflow(may some conditions changed)
                                if (DiffValue != pxConstants::mZero)
                                {
                                    ExternalCondition(CMsgStream(), CMSG_ORD_CREDITLIMIT_EXHAUSTED, (double)DiffValue);
                                    if (!(Session()->Device()->IsVideo()))
                                    {
                                        state = Order::EntryDeferred;
                                        orderCloseStates << "Deferred#11(" << state << ") ";
                                        SetProblemClearance();
                                        SetEventCode(pxEventReason::CreditLimitExceeded);
                                        ClearError();
                                        CloseState(state);               // set order state flags
                                        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                                        return CloseOrder();             // finally close the order
                                    }
                                    else
                                    {
                                        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                                        return ErrorState();
                                    }
                                }
                            }
                        }//end SR-15068713
                    
                    if (IsRebateArtSelection())
                    {
                        if (!(Session()->Device()->IsVideo()))
                        {
                            state = Order::EntryDeferred;
                            orderCloseStates << "Deferred#12(" << state << ") ";
                            SetProblemClearance();
                            SetEventCode(pxEventReason::RebateArticleSelection);
                            CloseState(state);               // set order state flags
                            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                            return CloseOrder();             // finally close the order
                        }
                        else
                        {
                            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                            return ErrorState();
                        }
                    }

                    if (IsNoRebateQty())
                    {
                        if (Session()->Device()->IsVideo())
                        {
                            BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());
                            return ErrorState();
                        }
                    }
                }

                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started SepPriceType";
                SepGroupState = SeparatePriceType(healthfundq, retailq);
                if (SepGroupState != Order::LeaveAsIs)
                {
                    state = (Order::States)SepGroupState;
                    orderCloseStates << "SepPriceType (" << state << ") ";
                }
                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished SepPriceType";

                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started Sep BigOrder,List5";

                SepGroupState = SeparateBigOrder();
                if (SepGroupState != Order::LeaveAsIs)
                {
                    state = (Order::States)SepGroupState;
                    orderCloseStates << "SepBigOrder (" << state << ") ";
                }


                SepGroupState = SeparateListFivePositions();
                if (SepGroupState != Order::LeaveAsIs)
                {
                    state = (Order::States)SepGroupState;
                    orderCloseStates << "SepListFive (" << state << ") ";
                }

                closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished Sep BigOrder,List5";

                /*----------------------------------------------------------------------------*/
                /*           Splitting of special article just for Bulgarian application      */
                /*----------------------------------------------------------------------------*/
                if (Session()->isBulgaria())  // just bulgarian application ???
                {
                    SepGroupState = SeparateSpecials(coolerq, opiateq, reshospital, zytosq, auxposq, psychoq);
                    if (SepGroupState != Order::LeaveAsIs)
                    {
                        state = (Order::States)SepGroupState;
                        orderCloseStates << "SepSpecials#04(" << state << ") ";
                    }
                }

                // split order lines with different tour
                if (state == Order::EntryClosed)
                {
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started SepTour";
                    SepGroupState = SeparateOrderLinesWithDifferentTour(coolerq, opiateq, zytosq);
                    if (SepGroupState != Order::LeaveAsIs)
                    {
                        state = SepGroupState;
                        orderCloseStates << "SepTour (" << state << ") ";
                    }
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished SepTour";
                }

                if (state == Order::EntryClosed)
                {
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started AutoItems";
                    AutoItems(coolerq, opiateq, zytosq, commiq); // automatic order item entry
                    BookAddOnChargeArticleNoDependOnCodeBlocage();          // book addoncharge article depend on codeblocage for this order->KdAuftragArt()
                    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished AutoItems";
                }

                // wird im ksc nicht mehr gebraucht
                if (IsGoodState())
                    TriggerInvoice(commiq, state);   //  determine if order may be invoiced
                if (CommType().IsShipDisposal() || CommType().IsShipDeliveryNote())
                    SetCustomerService();
            }

            closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started LogVol & DelayedRebateO";
            LogisticVolume_ = CalcLogisticVolume();                // Calculate volume for collective orders
            SepGroupState = checkDelayedRebateOrder(state, healthfundq, retailq);
            if (SepGroupState != Order::LeaveAsIs)
            {
                state = (Order::States)SepGroupState;
                orderCloseStates << "DelayedRebateOrder (" << state << ") ";
            }
            closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished LogVol & DelayedRebateO";

        }                                // end-if IsEntryInProgress()
        CloseState(state);               // set order state flags
    }                                    // end-if !IsOrderViewing()


    BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), orderCloseStates.str());

    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement started pxOrder::CloseOrder()";
    int ret = CloseOrder();                 // finally close the order
    closePerformanceMessurement << "\n\t\t\t" << basar::cmnutil::DateTime::getCurrent().toStrDateTime() << " -> close Measurement finished pxOrder::CloseOrder()";

    basar::DateTime closeEndTimestamp = basar::cmnutil::DateTime::getCurrent();
    basar::TimeSpan closeDuration = closeEndTimestamp - closeStartTimestamp;
    if (closeDuration.toNumeric().seconds > 5 || closeDuration.toNumeric().minutes > 0)
    {
        closePerformanceMessurement << "\n\t\t\t" << closeEndTimestamp.toStrDateTime() << " -> close End Timestamp ";
        closePerformanceMessurement << "\n\t\t\t" << closeDuration.toNormalizedString() << " -> close Duration ";
        BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), closePerformanceMessurement.str());
    }
    return ret;
}

Order::States pxOrder::setNoValidRoute(std::string reasonDetail)
{
    SetProblemClearance(); // manual clearance required
    SetEventCode(pxEventReason::NoValidRoute); // OK
    {
        std::stringstream s;
        s << "pxOrder::Close: EventCode NoValidRoute due to " << reasonDetail << " for OrderNo: " << KdAuftragNr();
        BLOG_INFO(libcsc::LoggerPool::getLoggerTourManager(), s.str());
    }
    SetRouteCheck();     // must do a manual route check
    return Order::EntryDeferred;
}

/*----------------------------------------------------------------------------*/
/*  Final order close activities:                                             */
/*  - Close order items and text documents.                                   */
/*  - Commit changes against the data base or roll them back in case of error.*/
/*  - Finally release all items, thus marking the order as closed.            */
/*----------------------------------------------------------------------------*/
int
pxOrder::CloseOrder()
{
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

    if (IsGoodState() && !IsOrderViewing())
    {
        CheckPaymentDate();              // BG application sets Paymentdate
        CloseItems();                    // Close all order items left open
        nDBBeginTransaction(cDBTransSet);
        CloseTextDocs();                 // Close text documents
        CloseCstDiscAccBalance();        // Close customers discount account
        if (IsNoCics() && IsEntryClosed())
        {
            if (!(Session()->Device()->IsVideo()))
            {
                SetEntryDeferred();
                ClearEntryClosed();
                SetProblemClearance();
                SetEventCode(pxEventReason::NoCicsAvailable);
                ClearError();
            }
            else
            {
                return ErrorState();
            }
        }
        if (Session()->isBulgaria())
        {
            if (IsEntryClosed() && !IsNullDocument())
            {
                if (WertLieferung_ == pxConstants::mZero)
                {
                    SetEntryDeferred();
                    ClearEntryClosed();
                    SetProblemClearance();
                    SetEventCode(pxEventReason::OrderIsNullDocument);
                    ClearInvoiceable();
                    SetNullDocument();
                    ClearError();
                }
            }
        }

        if (OrderValues())             // Bulgarien Ordervaluse(KDAUFTRAGWERTE)
        {
            OrderValues()->Put();        // Write to database
            Error() = OrderValues()->Error();

        }
        if (OrderCalcMode())
        {
            CloseOrderCalcMode();
        }

        try
        {
            getIbtRequestHandler().closeAllIbtRequests(this);                   // Close Auxiliaries in remote databases
        }
        catch (nError& err)
        {
            Error() = err;
        }
        SetRestDeliveryPositionsToReadyForWorkup(); // set status = 1 for nachlieferpos postyp 3 entries with status = 0
        SetDisposalPositionsToReadyForWorkup();     // set status = 1 for nachlieferpos postyp 2 entries with status 0
        pxOrderEvent event(*this);       // construct order event
        event.Put();                     // write it into the data base
        UnLock();                        // at the end unlock order and lockmanager
    }

    if (!IsGoodState())               // an error occurred
    {
        nDBRollBack();                  // roll them back in case of any error
        ErrorState(nSTATE_FATALERROR);  // force fatal error state
    }
    else
        nDBCommit(cDBTransSet);          // commit changes
    ItemList_->Clear();                 // clear and free order item list
    delete ItemList_;
    ItemList_ = NULL;

    // Cleanup for BG CPR-211062
    if (Session()->isBulgaria())
    {
        HeadText_ = NULL;
        TailText_ = NULL;
        ItemListProforma_ = NULL;
        Customer_ = NULL;
        CommType_ = NULL;
        StockTrans_ = NULL;
        OrderType_ = NULL;
        RangeCollectList_ = NULL;
        SepOrderArtGroupList_ = NULL;
        OrdTaxValues_ = NULL;
        OrderDiscAccList_ = NULL;
        BalanceCollectList_ = NULL;
        ValuesCollectList_ = NULL;
        OrderValues_ = NULL;
        OrderCalcMode_ = NULL;
        OrderPosDiscountList_ = NULL;
    }

    Session()->InitCurrentOrder();
    return ErrorState();
}


/*----------------------------------------------------------------------------*/
/*  Set order state flags during close.                                       */
/*----------------------------------------------------------------------------*/
void
pxOrder::CloseState
(
    const Order::States state
)
{
    if (IsGoodState())
    {
        switch (state)                // clear some state flags
        {
        case Order::EntryDeferred:
            ClearEntryClosed();
            break;

        case Order::EntryClosed:
            ClearEntryDeferred();
            break;

        case Order::ShipmentClosed:
            ClearShipmentInProgress();
            break;

        case Order::Invoiced:
            ClearInvoiceable();
            break;

        default:
            break;
        }

        if (state < 0)              // before setting desired closing state
            State_.ClearBit(~state);
        else
            State_.SetBit(state);
    }
}

/*----------------------------------------------------------------------------*/
/*  Set order state flags after VSE Transmission                              */
/*----------------------------------------------------------------------------*/
void
pxOrder::OrderStatus
(
    Order::States state
)
{
    if (IsGoodState())
    {
        switch (state)                // clear some state flags
        {
        case Order::EntryDeferred:
        {
            ClearEntryClosed();
            ClearInvoiceable();
            ClearFakturierbar();
            break;
        }

        default:
            break;
        }

        if (state < 0)              // before setting desired closing state
            State_.ClearBit(~state);
        else
            State_.SetBit(state);
        SetDirty();
    }
}

/*----------------------------------------------------------------------------*/
/*  Close all order items and re-calculate order values.                      */
/*----------------------------------------------------------------------------*/
int
pxOrder::CloseItems()
{
    if (IsGoodState())
    {
        ItemList_->Sort(cASCENDING, pxOrderItemList::SortByArticleNo);
        pxOrderItemListIter it(*ItemList_);
        pxOrderItem* item;
        InitValues();                    // init order values
        while (((item = (pxOrderItem*) ++it) != NULL) && IsGoodState())
        {
            nDBBeginTransaction(cDBTransSet);
            if (!item->IsCancelled() && !item->IsItemClosed())
            {
                if (IsEntryClosed())
                {
                    Session()->getStockBooking()->ReleaseReservationForOpenOrder(*item, item->MengeAbgebucht());
                    item->InsertNarcTransfer();
                    item->SetItemClosed();
                    item->SetDirty();
                }
                item->CalcAvp();
                item->Close();             // close current item
                Error() = item->Error();
            }
            ItemValues(item);             // calc this items value
            if (IsGoodState())
            {
                nDBCommit(cDBTransSet);
            }
            else
            {
                nDBRollBack();
            }
        }
        if(Session()->isBulgaria() && !Customer()->IsCashPayer() && !this->isCashOrder() && !OrderType().IsDiscountAccount())
        {
            WertLieferung_ = CalcGrossShipValue();
        }
        AverageItemValue();

        ItemList_->Sort(cASCENDING, pxOrderItemList::SortByPosNr);

    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Close order-related text documents.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrder::CloseTextDocs()
{
    nDBBeginTransaction(cDBTransSet);
    while (IsGoodState())
    {
        if (HeadText_ != NULL)
        {
            HeadText_->Put();
            Error() = HeadText_->Error();
            delete HeadText_;
            HeadText_ = NULL;
            continue;
        }

        if (TailText_ != NULL)
        {
            TailText_->Put();
            Error() = TailText_->Error();
            delete TailText_;
            TailText_ = NULL;
        }
        break;
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Unlock the order, re-write into the data base.                            */
/*----------------------------------------------------------------------------*/
int
pxOrder::UnLock()
{
    ClearEntryInProgress();
    ClearUpdateInProgress();

    if (IsPseudoLock())
        return ErrorState();

    if (Param()->IsSIbtCstOrg())
    {
        if (IsAuxPositions())
        {
            SetStammhausNewSuivra();
        }
    }
    tKDAUFTRAG record;
    record.KdAuftragNr = KdAuftragNr_; // primary key
    int retval = nDBReadLock(&record);     // read-lock record for subsequent update
    if (retval == cDBXR_NORMAL)
    {
        pxOrder shadoworder /*= pxOrder*/(Session(), record);
        if (shadoworder.IsEntryInProgress())
        {
            Put();                     // update this order
        }
        else
        {
            ExternalError(CMsgStream(), CMSG_ORD_NOMORE_INPROGRESS, KdAuftragNr_);
        }
    }

    m_LockGuard.reset(); // release lock if set and sets ptr to NULL
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Determine if order may be invoiced immediately.                           */
/*  This is true if either no order item or the entire order is not be        */
/*  commissioned. An entry is inserted into the invoice queue to trigger      */
/*  the invoice process in that case.                                         */
/*----------------------------------------------------------------------------*/
int
pxOrder::TriggerInvoice
(
    const int commiq,                    // no of items to be commissioned
    const Order::States state
)
{
    if ((CommType().IsNoShipment() || CommType().IsShipDisposal() || CommType().IsShipDeliveryNote()) || (commiq <= 0))
    {
        // nDBBeginTransaction(cDBTransSet);
        // pxInvoiceQueue *invoice = new pxInvoiceQueue( Session() );
        // invoice->NewEntry(KdAuftragNr_);
        // Error() = invoice->Error();
        if (state == Order::EntryDeferred)
            return ErrorState();

        SetInvoiceable();
        // delete invoice;
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Automatic order item entry.                                               */
/*  Some products require additional articles to be entered as order items.   */
/*  For instance, some medical products must be shipped in a cooler box.      */
/*  Upon order entry close, we post these order items automatically.          */
/*----------------------------------------------------------------------------*/
int
pxOrder::AutoItems
(
    const int   coolerq,
    const int   opiateq,
    const int   zytosq,
    const int   commiq
)
{
    long  n;
    long  ProductId[2];
    const long InvProductId = 9999999;  // indicates invalid product id

/*----------------------------------------------------------------------------*/
/*  Automatic cooler box posting.                                             */
/*----------------------------------------------------------------------------*/
    if (coolerq > 0)
    {                                   // then there are items requiring coolers
        ProductId[0] = ((n = Param()->PZNKuehlBox1()) == InvProductId) ? 0 : n;
        ProductId[1] = ((n = Param()->PZNKuehlBox2()) == InvProductId) ? 0 : n;
        int count = 0;
        for (int i = 0; i < 2; i++)
        {
            if (ProductId[i] > 0)
            {
                pxOrderItem* item = NewOrderItem_03_DefaultWithAutoItemAndIgnLack(ProductId[i], 0);
                if (item)                           // then item entered
                {
                    item->SetKuehlboxPosition();
                    item->SetDirty();               // item is updated during order item close
                    ++count;
                }
            }
        }
        if (count == 0)
            SetKuehlBoxDisabled();
    }

    /*----------------------------------------------------------------------------*/
    /*  Determine if an opiate delivery note must be created.                     */
    /*----------------------------------------------------------------------------*/
    if ((opiateq) && Param()->IsOpiateDeliveryNote())
    {
        SetBTMErwerbScheinBuchen();
        ProductId[0] = ((n = Param()->PZNBTMSchein()) == InvProductId) ? 0 : n;
        if (ProductId[0] > 0)
        {
            pxOrderItem* item = NewOrderItem_03_DefaultWithAutoItemAndIgnLack(ProductId[0], 1);
            if (item)
            {
                SetBTMErwerbScheinBuchen();
            }
        }
    }

    /*----------------------------------------------------------------------------*/
    /*  Automatic zystatika bag posting.                                          */
    /*----------------------------------------------------------------------------*/
    if (zytosq > 0)
    {                                   // then there are items requiring coolers
        ProductId[0] = ((n = Param()->PZNZytostatika()) == InvProductId) ? 0 : n;
        if (ProductId[0] > 0)
        {
            pxOrderItem* item = NewOrderItem_03_DefaultWithAutoItemAndIgnLack(ProductId[0], 1);
            if (item)
            {
                SetMitZytostatika();
            }
        }
    }
    /*----------------------------------------------------------------------------*/
    /*  Automatic AddOnCharge position if the minimum OrderValue is not reached   */
    /*----------------------------------------------------------------------------*/
    if (!IsOCPOrder())
    {
        ProductId[0] = ((n = Param()->PZNAddOnCharge()) == InvProductId) ? 0 : n;
        nMoney   MBestellWert = static_cast<double>(Param()->MindestBestellWert());
        if ((ProductId[0] > 0) && (MBestellWert > pxConstants::mZero))
        {
            if (WertLieferung_ < MBestellWert)
            {
                NewOrderItem_03_DefaultWithAutoItemAndIgnLack(ProductId[0], 1);
            }
        }
    }
    else
    {
        basar::VarString channelId = basar::VarString("");
        int offerID = 0;
        double freightCost = 0;
        double carriageFree = 0;
        if (getOCPOrderInfo(channelId, offerID, freightCost, carriageFree))
        {
            double ocpordervalue = 0.0f;
            getOCPOrderValue(ocpordervalue);
            if (((double)WertAuftrag() < carriageFree) || ((ocpordervalue > 0.0f) && (ocpordervalue < carriageFree)))
            {
                std::stringstream ovalue;
                ovalue.str(std::string());
                ovalue << "Booking OCP addoncharge (freightCost): " << freightCost << " as thisOrderValue/calcOrderValue = " << (double)WertAuftrag() << "/" << ocpordervalue << " less then minOrderValue(carriageFree) = " << carriageFree;
                BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), ovalue.str());
                // now book additional addoncharge article but without articleno (similar to a dispo free text item with freightcost as value)
                NewOrderItem_15_DefaultWithAutoItemOCP(freightCost);
            }
            else
            {
                std::stringstream s;
                s << "Not adding OCP addoncharge (freightCost) as thisOrderValue/calcOrderValue = " << (double)WertAuftrag() << "/" << ocpordervalue << " greater then minOrderValue (carriageFree) = " << carriageFree;
                BLOG_INFO(libcsc::LoggerPool::getLoggerSession(), s.str());
            }
        }
    }

    /*----------------------------------------------------------------------------*/
    /*  Automatic PZNFranko to manipulate Preis during kommission                 */
    /*----------------------------------------------------------------------------*/
    ProductId[0] = ((n = Param()->PZNFranko()) == InvProductId) ? 0 : n;
    if (ProductId[0] > 0)
    {
        NewOrderItem_03_DefaultWithAutoItemAndIgnLack(ProductId[0], 0);
    }

    /*----------------------------------------------------------------------------*/
    /*  Automatic advertising product delivery, if an advertising campaign is     */
    /*  active.                                                                   */
    /*----------------------------------------------------------------------------*/
    pxCustomerFlags& cflags = Customer()->Flags();

    if (!((CommType().IsShipNormal() || CommType().IsShipSpecial())
        && Param()->IsAdvertising() && cflags.IsWerbeFachBelegt()))
        return ErrorState();

    ReCalcValues();                     // re-calc order ship value
    if (WertLieferung() > pxConstants::mZero && commiq - opiateq - coolerq >= 3)
    {
        ProductId[0] = ((n = Param()->PZNWerbefach()) == InvProductId) ? 0 : n;
        ProductId[1] = ((n = Param()->PZNWerbefach2()) == InvProductId) ? 0 : n;
        for (int i = 0; i < 2; i++)
        {
            if (ProductId[i] > 0)
            {
                pxOrderItem* item = NewOrderItem_03_DefaultWithAutoItemAndIgnLack(ProductId[i], 1);
                if (item)
                {
                    SetMitWerbung();
                }
            }
        }

        // Clear customer-related flag to avoid duplicate deliveries:
        if (IsMitWerbung())
        {
            cflags.ClearWerbeFachBelegt();
            nDBBeginTransaction(cDBTransRecord);
            cflags.Put();                 // update flag entity
            if (cflags.IsGoodState())
                nDBCommit(cDBTransRecord); // commit changes
            else
                nDBRollBack();
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Freightage. If this order contains a freightage position and              */
/*  WertLieferung() equals the price of the freightage position, so           */
/*  delte this item and remove it from the itemlist.                          */
/*----------------------------------------------------------------------------*/
int
pxOrder::Freightage
(
    const int freightage
)
{
    if (freightage == 0)               // count of freightage items > 0
        return ErrorState();
    /*----------------------------------------------------------------------------*/
    /*  Now scan the list of positions for freightage articleno                   */
    /*----------------------------------------------------------------------------*/
    pxOrderItemListIter it(*ItemList_);
    pxOrderItem* item;
    while ((item = (pxOrderItem*) ++it) != NULL)
    {
        if (item->ArtikelNr() == Param()->PZNFreightage())
        {
            if (WertLieferung() == item->PreisEKApo())
            {
                item->Delete();
                Error() = item->Error();   // catch error
                if (IsGoodState())
                    delete it.Remove();     // delete entry from list
            }
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  SetOrderCompleted: This order is set invoiceable and invoiced. After that */
/*  the order is written back to the database                                 */
/*----------------------------------------------------------------------------*/
int
pxOrder::SetOrderCompleted
(
)
{
    ClearError();                 // clear error this order must be closed
    OrderStatus(Order::EntryClosed);
    OrderStatus(Order::Invoiceable);
    OrderStatus(Order::Invoiced);
    SendeStatus(cVSEok);
    CloseOrder();
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Create an order item for an advertising product.                          */
/*----------------------------------------------------------------------------*/
Order::States pxOrder::checkDelayedRebateOrder(Order::States state, int& healthfundq, int& retailq)
{
    nDate dateddel = DatumAuslieferung();  // date delayeddelivery
    nDate now;
    Order::States State = Order::LeaveAsIs;

    if (state == Order::EntryClosed)
        return State;
    if (!(OrderType().IsDiscountAccount()))
        return State;

    if (dateddel != pxConstants::NullDate && Session()->isBulgaria() && dateddel > now)
    {
        State = SeparatePriceType(healthfundq, retailq);

        State = SeparateBigOrder();

        State = SeparateListFivePositions();
    }
    return State;
}
