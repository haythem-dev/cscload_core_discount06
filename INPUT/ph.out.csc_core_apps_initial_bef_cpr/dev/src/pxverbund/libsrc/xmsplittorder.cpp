/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderTransmit:
Order entry methods.

REVISION HISTORY

13 Mai 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/
#include "pxxmit.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxcstot.hpp"
#include "pxoeparm.hpp"
#include "pxorder.hpp"

/*----------------------------------------------------------------------------*/
/*  SeparateDefects.                                                          */
/*----------------------------------------------------------------------------*/
int
pxOrderTransmit :: SeparateDefects
(
)
{
    int State = Order::LeaveAsIs;
    if ( Order_ == NULL )
        return State;

    pxCustomerFlags& cflags = Order_->Customer()->Flags();
    const pxCustOrderType& ot = Order_->OrderType();

    if (ot.IsTransfer() )       // do not splitt on Ordertype == UW
        return State;

    if (Session()->isAustria() && ot.KdAuftragArt() == "SD")
        return State;

    if (!cflags.IsTrennDefekt())
        return State;

    pxOrder* splittorder = NULL;
    pxOrderItemListIter it(*Order_->ItemList());
    pxOrderItem *item;
    pxCustBase* customer = Order_->Customer();

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        if ( (item->IsQStateNotOnHand() && !item->IsNachliefern()  && !item->IsAuxPosted() && !item->IsDisponieren()) ||
             item->IsUnKnownProduct() || !item->IsArtStateGood() )
        {
            if ( item->IsDispoItem() )
                continue;
            if ( splittorder == NULL )
            {
                splittorder = new pxOrder(Session(), *customer);
                if ( !splittorder->IsGoodState() )
                {
                    delete splittorder;
                    splittorder = NULL;
                    break;
                }
            }

            if ( item->MengeAbgebucht() > 0 )
            {
                if ((item->MengeBestellt() - item->MengeAbgebucht()) > 0 )
                {
                    long ProductId   = item->ArtikelNr();
                    long QuanOrdered = item->MengeBestellt();
                    item->CancelItem(pxOrderItem :: ClearMengeBestellt);
                    if (item->IsGoodState() )
                    {
                        splittorder->NewOrderItemRemarks(ProductId, QuanOrdered);
                    }
                }
            }
            else
            {
                splittorder->CopyOrderItem(item, pxOrderItem::SeparateDefect, SplittType_Unknown);
                item->MengeBestellt(0L);
            }
        }
    }

    if ( splittorder )
    {
       splittorder->SetSepDefectOrder();     // for later use
       splittorder->ClearConsolidation();
       splittorder->SetProblemClearance();
       splittorder->Close(Order::EntryDeferred);
       State = Order::EntryClosed;
    }

    return State;
}

/*----------------------------------------------------------------------------*/
/*  SeparateDefects_DE Just for german appliction.                            */
/*----------------------------------------------------------------------------*/
int
pxOrderTransmit :: SeparateDefects_DE
(
)
{
    int State =  (int)Order::LeaveAsIs;
    if ( Order_ == NULL )
        return State;

    pxCustomerFlags& cflags = Order_->Customer()->Flags();
    const pxCustOrderType& ot = Order_->OrderType();

    if (ot.IsTransfer() )       // do not splitt on Ordertype == UW
        return State;

    if (!cflags.IsTrennDefekt())
        return State;

    pxOrder* splittorder =   NULL;
    pxOrderItemListIter it(*Order_->ItemList());
    pxOrderItem *item;
    pxOrderItem *splittitem;
    pxCustBase* customer = Order_->Customer();
    nString Remarks;
    nString ProductId;
    long  MengeDefekt = 0;
    long  limitcheckq = 0;

    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        MengeDefekt = 0;
        if (   (item->IsQStateNotOnHand() && !item->IsNachliefern() && !item->IsAuxPosted() && !item->IsDisponieren() && !item->IsCancelled())
            || item->IsUnKnownProduct() || !item->IsArtStateGood() )
        {
            if ( item->IsDispoItem() )
                continue;
            if ( item->IsSeparatePosition() )
                continue;
            if ( splittorder == NULL )
            {
                splittorder = new pxOrder(Session(), *customer);
                if ( !splittorder->IsGoodState() )
                {
                    delete splittorder;
                    splittorder = NULL;
                    break;
                }
                splittorder->KdAuftragNrOrg(Order_->KdAuftragNr());
            }

            if ( item->MengeAbgebucht() > 0 )
            {
                if ((item->MengeBestellt() - item->MengeAbgebucht()) > 0 )
                {
                    MengeDefekt = item->MengeBestellt() - item->MengeAbgebucht();
                }
            }
            splittitem = splittorder->CopyOrderItem(item, pxOrderItem::SeparateDefect, SplittType_Unknown);
            if ( MengeDefekt > 0 )
            {
                item->MengeBestellt(item->MengeAbgebucht());
                splittitem->MengeBestellt(MengeDefekt);
                limitcheckq += item->IsQStateLimitCheck();
                if ( limitcheckq == 0 )
                {
                item->SetFehlerMenge((short)pxOrderItem::QStateGood);
                }
            }
            else
            {
                item->MengeBestellt(0L);
            }
            splittitem->MengeAbgebucht(0L);
            splittitem->MengeGeliefert(0L);
            splittitem->MengeBestaetigt(0L);
            if ( item->MengeAbgebucht() == 0 )
            {
                item->SetSeparatePosition();
            }
        }
    }

    if ( splittorder )
    {
        splittorder->SetSepDefectOrder();     // for later use
        splittorder->ClearConsolidation();
        if ( Order_->Param()->IsSDefOrderDF() )
        {
            splittorder->SetProblemClearance();
        }
        splittorder->Close(Order::EntryDeferred);
        State = Order::EntryClosed;
    }

    return State;
}
