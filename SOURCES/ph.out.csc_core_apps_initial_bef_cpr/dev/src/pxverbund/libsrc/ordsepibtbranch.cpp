#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxtxtdoc.hpp"
#include "pxoeparm.hpp"
#include "pxbase/pxconstants.hpp"
#include "tourutil.hpp"
#include <logger/loggerpool.h>
#include <ibt/componentmanager/ibtcomponentmanager.h>
#include <ibt/ibtbranch/iibtbranchrepositoryptr.h>
#include <ibt/ibtbranch/iibtbranchrepository.h>
#include <ibt/ibtbranch/iibtbranchsetting.h>
#include <ibt/ibtbranch/iibtbranchsettingcollection.h>
#include "types/messagecodeenum.inc"
#include <set>

struct IbtBranchSplitInfo
{
    short               IbtBranchNo;
    nDate               CustomerTourDate;
    basar::VarString    CustomerTourId;
    bool                WaitForIbtPicking;

    IbtBranchSplitInfo(const short ibtBranchNo, const nDate& tourDate, const basar::VarString& tourId, const bool waitForIbtPicking) :
        IbtBranchNo(ibtBranchNo),
        CustomerTourDate(tourDate),
        CustomerTourId(tourId),
        WaitForIbtPicking(waitForIbtPicking)
    {
    }

    bool operator < (const IbtBranchSplitInfo& other) const
    {
        if (this->IbtBranchNo == other.IbtBranchNo)
        {
            if (this->CustomerTourDate == other.CustomerTourDate)
                return this->CustomerTourId < other.CustomerTourId;
            return this->CustomerTourDate < other.CustomerTourDate;
        }
        return this->IbtBranchNo < other.IbtBranchNo;
    }
};

long _AnzPosTotal(pxOrder* order)
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
        if (item->MengeBestaetigt() == 0)
            continue;
        if (!item->IsKnownProduct())
            continue;
        if (item->ArtBase() == NULL || !item->ArtBase()->IsGoodState())
            continue;
        anzPos++;
    }
    return anzPos;
}

long AnzPosForIbtBranch(pxOrder* order, const IbtBranchSplitInfo& info)
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
        if (item->MengeBestaetigt() == 0)
            continue;
        if (!item->IsKnownProduct())
            continue;
        if (item->ArtBase() == NULL || !item->ArtBase()->IsGoodState())
            continue;
        if (false == item->IsAuxPosted())
            continue;
        TourInfo* ti = item->getItemTourInformation(true);
        if (false == ti->getTourFound())
            continue;

        if (ti->getIBTBranchNo() == info.IbtBranchNo &&
            ti->getTourDate() == info.CustomerTourDate &&
            ti->getTourID()() == info.CustomerTourId)
        {
            anzPos++;
        }
    }
    return anzPos;
}

Order::States pxOrder::SeparateIbtBranchLines()
{
    Order::States retval = Order::LeaveAsIs;

    if (BatchSchreiben_ == cORTYPE_PURE_IBT_ORDER) // already splitted from main order
        return retval;

    libcsc::ibt::IIbtBranchRepositoryPtr ibtRepo = Session()->getIbtComponentManager()->createIbtBranchRepository();
    libcsc::ibt::IIbtBranchSettingCollectionPtr coll = ibtRepo->findIbtBranchSettings(FilialNr());

    if (0 == coll->count())
        return retval;

    std::set<IbtBranchSplitInfo> splitInfos;
    pxOrderItemListIter it(*ItemList());        // iterator itemlist
    pxOrderItem*        item;               // item object

    while ((item = (pxOrderItem*) ++it) != NULL)
    {
        if (item->IsCancelled())
            continue;
        if (item->ArtikelNr() == 0)
            continue;
        if (item->MengeBestaetigt() == 0)
            continue;
        if (!item->IsKnownProduct())
            continue;
        if (item->ArtBase() == NULL || !item->ArtBase()->IsGoodState())
            continue;
        if (false == item->IsAuxPosted())
            continue;

        TourInfo* ti = item->getItemTourInformation(true);
        if (false == ti->getTourFound())
            continue;

        // check for ibtbranchsetting.splittosingleorder
        libcsc::ibt::IIbtBranchSettingPtr branchSetting = coll->findBranchSetting(ti->getIBTBranchNo());
        if (NULL != branchSetting.get() && true == branchSetting->getSplitToSingleOrder())
        {
            splitInfos.insert(IbtBranchSplitInfo(ti->getIBTBranchNo(), ti->getTourDate(), ti->getTourID()(), branchSetting->getWaitForPicking()));
        }
    }

    // iterate through all different line tours
    std::set<IbtBranchSplitInfo>::reverse_iterator splitIt = splitInfos.rbegin();
    while (splitIt != splitInfos.rend())
    {
        if (_AnzPosTotal(this) == AnzPosForIbtBranch(this, *splitIt))
        {
            this->SetDoNotAppend();
            this->setWaitForIbtPicking(splitIt->WaitForIbtPicking);
            this->BatchSchreiben(cORTYPE_PURE_IBT_ORDER);
            if (!TourUtil::isNullOrCurrentDate(splitIt->CustomerTourDate))
            {
                DatumAuslieferung(splitIt->CustomerTourDate);
            }
            SetRouteForOrderSeparation(splitIt->CustomerTourId.c_str(), DatumAuslieferung());
            return retval;
        }

        // split all positions with IbtBranchNo, CustomerDepartureDate and CustomerTourId into new order.
        SeparateIbtBranchLines(splitIt->IbtBranchNo, splitIt->CustomerTourDate, splitIt->CustomerTourId, splitIt->WaitForIbtPicking);
        ++splitIt;
    }
    return retval;
}


Order::States pxOrder::SeparateIbtBranchLines(const short ibtBranchNo, const nDate& tourDate, const basar::VarString& tourId, const bool waitForIbtPicking)
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
        if (item->MengeBestaetigt() == 0)
            continue;
        if (!item->IsKnownProduct())
            continue;
        if (item->ArtBase() == NULL || !item->ArtBase()->IsGoodState())
            continue;
        if (false == item->IsAuxPosted())
            continue;
        TourInfo* ti = item->getItemTourInformation(true);
        if (false == ti->getTourFound())
            continue;

        if (ti->getIBTBranchNo() == ibtBranchNo && ti->getTourDate() == tourDate && ti->getTourID()() == tourId)
        {
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
                seporder->DafueAuftragNr((long)cDCTSequenceNumDDELMax);
                seporder->setPurchaseOrderNo(getPurchaseOrderNo());
                seporder->HerkunftFiliale(HerkunftFiliale());
                seporder->BatchSchreiben(cORTYPE_PURE_IBT_ORDER);
                seporder->SetPaymentTerm(PaymentTerm());
                seporder->SetPaymentType(PaymentType());
                seporder->SetTenderNo(TenderNo_);
                seporder->BTMFormularNr(BTMFormularNr());
                seporder->DatumBTM(DatumBTM());
                seporder->DatumVersand(DatumVersand());
                seporder->Bemerkungen(Bemerkungen());
                seporder->SetOrderLabel(OrderLabel());
                seporder->SetDatumValuta(DatumValuta());
                seporder->SetValutaMonManuell(ValutaMonManuell());
                seporder->setWaitForIbtPicking(waitForIbtPicking);

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
            delitem = seporder->CopyOrderItem(item, pxOrderItem::AuxDelivery, SplittType_IBT);
            delitem->UndoRedoItemDiscount(item);
            if (Session()->isSwitzerland())
            {
                delitem->UndoRedoTenderProgressCH(item);
            }

            delitem->InvoiceValue();             // recalc PreisFaktur
            // now delete item members
            item->MengeBestaetigt(0L);
            item->MengeGeliefert(0L);
            item->MengeAbgebucht(0L);
            item->MengeNatra(0L);
            item->SetSeparatePosition();

            nMessage msg(CMsgStream(), CMSG_ITM_SEPARATE_ARTGROUP, seporder->KdAuftragNr());
            nString posbem = msg.String();
            posbem.Compress('\n');
            item->Bemerkungen(posbem);
        }
    }

    // Now close seporder
    if (seporder)
    {
        //Test
        if (Session()->isSwitzerland())
        {
            seporder->SpecialOmgRebateHandling();
        }

        if (!TourUtil::isNullOrCurrentDate(tourDate))
        {
            seporder->DatumAuslieferung(tourDate);
        }
        seporder->SetRouteForOrderSeparation(tourId.c_str(), seporder->DatumAuslieferung());
        if (waitForIbtPicking)
        {
            seporder->SetDoNotAppend();
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
