#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxbranch.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxtxtdoc.hpp"
#include "pxoeparm.hpp"
#include "pxbase/pxconstants.hpp"
#include "tourassignmentutil.hpp"
#include "pxorderitemtour.hpp"
#include <logger/loggerpool.h>
#include "tourutil.hpp"
#include "types/messagecodeenum.inc"
#include <set>
#include "pxorderperiod.hpp"
#include "pxcustomerflags.hpp"
#include "pxcstot.hpp"

struct TourDepartureInfo
{
    long                DepartureDate;
    basar::VarString    TourId;

    TourDepartureInfo(const long departureDate, const basar::VarString& tourId) :
        DepartureDate(departureDate),
        TourId(tourId)
    {
    }

    bool operator < (const TourDepartureInfo& other) const
    {
        if (this->DepartureDate == other.DepartureDate)
            return this->TourId < other.TourId;
        return this->DepartureDate < other.DepartureDate;
    }
};

long AnzPosTotal(pxOrder* order)
{
    pxOrderItemListIter it(*order->ItemList());     // iterator itemlist
    pxOrderItem*        item;               // item object
    long                anzPos = 0;

    while ((item = (pxOrderItem*) ++it) != NULL)
    {
        if (item->IsCancelled())
            continue;
        if (item->ArtikelNr() == 0)
            continue;
        if (item->MengeGeliefert() == 0 && item->MengeVerbund() == 0 )
            continue;
        if (!item->IsKnownProduct())
            continue;
        if (item->ArtBase() == NULL || !item->ArtBase()->IsGoodState())
            continue;
        anzPos++;
    }
    return anzPos;
}

long AnzPosForTour(pxOrder* order, const TourDepartureInfo& info)
{
    pxOrderItemListIter it(*order->ItemList());     // iterator itemlist
    pxOrderItem*        item;               // item object
    long                anzPos = 0;

    while ((item = (pxOrderItem*) ++it) != NULL)
    {
        if (item->IsCancelled())
            continue;
        if (item->ArtikelNr() == 0)
            continue;
        if (item->MengeGeliefert() == 0)
            continue;
        if (!item->IsKnownProduct())
            continue;
        if (item->ArtBase() == NULL || !item->ArtBase()->IsGoodState())
            continue;
        if (item->getItemTourDate() == info.DepartureDate && item->getItemTourInformation()->getTourID()() == info.TourId)
            anzPos++;
    }
    return anzPos;
}

Order::States pxOrder::SeparateOrderLinesWithDifferentTour(int& coolerq, int& opiateq, int& zytosq)
{
    Order::States retval = Order::LeaveAsIs;

    // do split only if tour manager is used with transport exclusion on tour level
    if ( false ==  Param()->IsUseTourManagerWithTransportExclusion() )
    {
        return retval;
    }

    // do not split if the flag has been set to avoid delayed delivery
    if ( true == this->getNoDelayedDelivery() )
    {
        return retval;
    }

    // nothing to do if there are no items with deferring tours
    pxOrder::OrderItemCounts counts = this->GetOrderItemCounts();
    if( 0 == counts.DifferingTourLines )
    {
        return retval;
    }

    std::stringstream s;
    s << "O:SeparateOrderLinesWithDifferentTour Order[" << KdAuftragNr() << "] Tour[" << this->getTourInformation()->getTourID()() << "|" << this->getTourInformation()->getTourDate().GetYYYYMMDD() << "] ";
    TourUtil::writeLogINFO( s, true );

    pxOrderItemTourList oitList(Session());
    oitList.SelectForOrder(KdAuftragNr());
    pxOrderItemTourListIter oitListIt(oitList);
    pxOrderItemTour*        oit;

    long orderTourDate = getTourInformation()->getTourDate().GetYYYYMMDD();
    nString orderTourID = getTourInformation()->getTourID();

    int tourDeparturesCount = 0;
    std::set<TourDepartureInfo> tourDepartures;
    while ((oit = (pxOrderItemTour*) ++oitListIt) != NULL)
    {
        s << "O:SeparateOrderLinesWithDifferentTour Pos[" << oit->getLineNo() << "] Tour[" << oit->getTourId()() << "|" << oit->getDepartureDate() << "] ";
        TourUtil::writeLogINFO( s, true );

        if (oit->getLineNo() == 0) // skip order header entry
            continue;
        if (oit->getDeliveryBranchNo() > 0) // skip IBT positions
            continue;

        // take only positions with a tour different to the tour of the order
        if (oit->getDepartureDate() != orderTourDate || oit->getTourId() != orderTourID )
        {
            tourDepartures.insert(TourDepartureInfo(oit->getDepartureDate(), oit->getTourId()()));
            ++tourDeparturesCount;
        }
    }

    s << "O:SeparateOrderLinesWithDifferentTour Order: " << KdAuftragNr() << " TourDepartures Count: " << tourDeparturesCount;
    TourUtil::writeLog( s, true );

    // iterate through all different line tours
    std::set<TourDepartureInfo>::reverse_iterator it = tourDepartures.rbegin();
    while (it != tourDepartures.rend())
    {
        if (AnzPosTotal(this) == AnzPosForTour(this, *it))
        {
            // all pos are for the same tour
            s << "O:SeparateOrderLinesWithDifferentTour all pos on Tour[" << it->TourId << "|" << it->DepartureDate << "] -> switch order to tour";
            TourUtil::writeLogINFO( s, true );
            this->SetRouteForOrderSeparation(it->TourId.c_str(), it->DepartureDate);
            this->SetDoNotAppend();

            nDate now;
            if (now.GetYYYYMMDD() != it->DepartureDate)
            {
                return Order::EntryDeferred;
            }
            return retval;
        }

        if (this->getTourInformation()->getTourDate().GetYYYYMMDD() != it->DepartureDate || this->getTourInformation()->getTourID()() != it->TourId)
        {
            s << "O:SeparateOrderLinesWithDifferentTour split Pos with Tour[" << it->TourId << "|" << it->DepartureDate << "] ";
            TourUtil::writeLogINFO( s, true );

            // split all positions with oit->getDeliveryDate() && oit->getTourId() into new order.
            SeparateOrderLinesForTour(it->DepartureDate, it->TourId, coolerq, opiateq, zytosq);
        }
        s.str("");
        ++it;
    }
    return retval;
}


Order::States pxOrder::SeparateOrderLinesForTour(const long departureDate, const basar::VarString& tourId, int& coolerq, int& opiateq, int& zytosq)  //#splitOrder
{
    Order::States       retval = Order::LeaveAsIs;

    pxOrderItemListIter it(*ItemList_);     // iterator itemlist
    pxOrderItem*        item;               // item object
    pxOrder*            seporder = NULL;    // separated  order
    pxOrderItem*        delitem;            // item object
    nDate               now;

    while ((item = (pxOrderItem*) ++it) != NULL)
    {
        if (item->IsCancelled())
            continue;
        if (item->ArtikelNr() == 0)
            continue;
        if (item->MengeGeliefert() == 0)
        {
            std::stringstream s;
            s << "O:SeparateOrderLinesForTour Pos[" << item->PosNr() << "] already splitted, skipping!";
            TourUtil::writeLogINFO( s, true );
            continue;
        }
        if (!item->IsKnownProduct())
            continue;
        if (item->ArtBase() == NULL || !item->ArtBase()->IsGoodState())
            continue;

        if (item->getItemTourDate() == departureDate && item->getItemTourInformation()->getTourID()() == tourId)
        {
            std::stringstream s;
            s << "O:SeparateOrderLinesForTour Pos[" << item->PosNr() << "] splitting to Tour[" << tourId << "|" << departureDate << "] ";
            TourUtil::writeLogINFO(s, true);

            if (seporder == NULL)
            {
				// Gets existing order for merging postions with the same tour
                seporder = GetExistingSplitDelayDeliveryOrder();
                if (seporder == NULL)
                {
                seporder = new pxOrder(Session(), *Customer());
                if (!seporder->IsGoodState())
                {
                    delete seporder;
                    seporder = NULL;
                    break;
                }
                seporder->OrderType(KdAuftragArt_, KoArt_, BuchArt_);
                seporder->KdAuftragNrOrg(KdAuftragNr_);
                    seporder->DafueAuftragNr((long)cDCTSequenceNumDDELMax);       // TO CHECK        
                if (TourUtil::isDateInTheFuture(departureDate))
                {
                    seporder->DatumAuslieferung(departureDate);
                }
                seporder->setPurchaseOrderNo(getPurchaseOrderNo());
                seporder->HerkunftFiliale(HerkunftFiliale());
                seporder->BatchSchreiben(BatchSchreiben());
                seporder->SetPaymentTerm(PaymentTerm());
                seporder->SetPaymentType(PaymentType());
                seporder->SetTenderNo(TenderNo_);
                seporder->BTMFormularNr(BTMFormularNr_);
                seporder->DatumBTM(DatumBTM_);
                seporder->DatumVersand(departureDate);
                if (DatumValuta_ != pxConstants::NullDate)
                {
                    seporder->SetDatumValuta(DatumValuta_);
                    seporder->SetValutaMonManuell(ValutaMonManuell_);
                }
                seporder->SetRouteForOrderSeparation(tourId.c_str(), departureDate);
                // Look for Headtext
                pxTextDoc* headtext = HeadText();
                pxTextDoc* tailtext = TailText();
                pxTextDocIter headiter = pxTextDocIter(*headtext);
                pxTextDocIter tailiter = pxTextDocIter(*tailtext);
                if (headtext->Entries() > 0)
                {
                    pxTextDoc *headp = seporder->HeadText();
                    while ((headtext = (pxTextDoc *) ++headiter) != NULL)
                    {
                        nString headline = ((pxTextLine*)headtext)->Text();
                        headp->NewLine(headline);
                    }
                }
                // Look for Tailtext
                if (tailtext->Entries() > 0)
                {
                    pxTextDoc *tailp = seporder->TailText();
                    while ((tailtext = (pxTextDoc *) ++tailiter) != NULL)
                    {
                        nString tailline = ((pxTextLine*)tailtext)->Text();
                        tailp->NewLine(tailline);
                    }
                }

                }
            }
            delitem = seporder->CopyOrderItem(item, pxOrderItem::SeparateArticle, SplittType_Unknown);
            delitem->UndoRedoItemDiscount(item);
            delitem->InvoiceValue();             // recalc PreisFaktur
            // now delete item members
            item->MengeBestaetigt(0L);
            item->MengeGeliefert(0L);
            item->MengeAbgebucht(0L);
            item->MengeNatra(0L);
            item->SetSeparatePosition();
            // recalc opiateq and coolerq
            if (item->ArtBase()->ArtClass().IsOpiat())
            {
                opiateq = std::max(opiateq - 1, 0);
            }
            if (item->ArtBase()->ArtFlags().IsKuehlKette() ||
                item->ArtBase()->ArtFlags().IsGekuehlt08() ||
                item->ArtBase()->ArtFlags().IsGekuehlt20())
            {
                coolerq = std::max(coolerq - 1, 0);
            }
            if (item->ArtBase()->ArtFlags().IsZytoStatikaArtikel())
            {
                zytosq = std::max(zytosq - 1, 0);
            }

            long tag = seporder->DatumVersand().GetDay();
            long month = seporder->DatumVersand().GetMonth();
            long year = seporder->DatumVersand().GetYear();

            nString  datedel;
            sprintf((char*)datedel, "%02ld.%02ld.%04ld", tag, month, year);

            nMessage msg(CMsgStream(), CMSG_ITM_DELAYEDDELIVERY, (char*)&datedel);
            nString posbem = msg.String();
            posbem.Compress('\n');
            item->Bemerkungen(posbem);
        }
    }

    // Now close seporder
    if (seporder)
    {
        if (seporder->DatumAuslieferung() != pxConstants::NullDate && seporder->DatumAuslieferung() != now)
        {
            seporder->CloseState(Order::EntryDeferred); // set order state flags
            seporder->CloseOrder();
        }
        else
        {
            seporder->CloseState(Order::EntryClosed);
            seporder->Close(Order::EntryClosed, Order::cClose_SeparatedOrder);   // set order state flags
        }

        Error() = seporder->Error();            // copy Error
        delete seporder;
        seporder = NULL;
    }
    return retval;
}

/// <summary>
/// Searches for an existing split, deferred delivery order that matches specific criteria, opens it for insertion if possible, and returns it. If no suitable order is found, returns NULL.
/// </summary>
/// <returns>A pointer to a pxOrder object representing the matching split, deferred delivery order if found and successfully opened for insertion; otherwise, NULL.</returns>
pxOrder* pxOrder::GetExistingSplitDelayDeliveryOrder()
{
    pxOrder* order;
    pxOrderList* DeferredOrders_ = NULL; // ptr to list deferred orders

    // Deferred order list lookup :
    if (DeferredOrders_ == NULL)   // must read them from the data base
    {
        DeferredOrders_ = new pxOrderList(Session());
        DeferredOrders_->SelectByCustomerNo(Customer_->IDFNr(), "", "", Customer_->FilialNr(), Order::NOT_EntryInProgress, Order::NOT_UpdateInProgress, Order::NOT_ProblemClearance,
            Order::EntryDeferred, Order::cStateLast);
    }
    pxOrderListIter it(*DeferredOrders_);
    while ((order = (pxOrder*) ++it) != NULL)
    {
        // Checks if order allowed to append
        if (order->IsDoNotAppend())
        {
            delete (pxOrder*)it.Remove();
            continue;
        }

        if (!order->IsSplitOrderAvailableForOrderConsolidation())
        {
            delete (pxOrder*)it.Remove();
            continue;
        }

        // In case of a matching order type, the order is openend for inserting
                // new items, removed from the list of deferred orders, and appended to
                // the list of active orders.
        if (order->KdAuftragArt() == KdAuftragArt_
            && order->KoArt() == KoArt_
            && order->BuchArt() == BuchArt_
            && order->isOrderLabelEqual("")
            && order->DatumAuslieferung() != pxConstants::NullDate
            && order->KdAuftragNrOrg() > 0) 
        {
            if (order->OpenOrder(cDBOPEN_INSERT, Customer_) == nSTATE_GOOD)
            {
                return (pxOrder*)it.Remove();
            }
            else
            {
                Error() = order->Error();
                delete (pxOrder*)it.Remove(); // open order failed
            }
        }
    }

    return NULL;
}

/// <summary>
/// Determines whether split order is available for order consolidation based on customer and order parameters.
/// </summary>
/// <returns>Returns true if split order is available for order consolidation; otherwise, returns false.</returns>
bool pxOrder::IsSplitOrderAvailableForOrderConsolidation()
{
    // Keine Auftragszusammenführung für den Kunden
    if (!this->Customer()->Flags().IsAuftragZusammen())
    {
        return false;
    }

    // Flag für keine Auftragszusammenführung ist gesetzt
    if (true == IsDoNotAppend()) return false;

    // Keine Auftragszusammenführung für bestimmte Auftragsarten
    pxCustOrderTypeList* otlp = this->Customer()->OrderTypeList();
    pxCustOrderType* otp = otlp->Find(this->KdAuftragArt(), this->FilialNr(), this->IDFNr());
    if (otp && !otp->IsOrderCons())
    {
        return false;
    }

    // Max. Anzahl Positionen pro Auftrag erreicht?
    if (this->Param()->MaxPosAuftrag() > 0)
    {
        if (this->AnzPos() >= this->Param()->MaxPosAuftrag()) { return false; }
    }

    return true;
}