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
#include "pxcustdeldelivery.hpp"
#include "pxitemdiscount.hpp"
#include "pxholiday.hpp"

/*----------------------------------------------------------------------------*/
/* ChangeContainerLevel: just for Serbian applikation                         */
/* split positione position for where ArtBase()->ContainerGroesse() > 0 &&    */
/* item->MengeGeliefert_ >= item->ArtBase()->ContainerGroesse()               */
/* A2MIN Regelung                                                             */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ChangeContainerLevel
(
)
{
    nDate today;
    pxOrderItem *item;
    pxOrderItem *newitem;
    pxOrderItemListIter it(*ItemList());
    pxItemDiscount *entriep = NULL;
    pxItemDiscount *newentriep = NULL;

/*----------------------------------------------------------------------------*/
/*  some prechecks before further action has taking place                     */
/*----------------------------------------------------------------------------*/
    if (!Session()->isSerbia())
       return ErrorState();

    if ( Param()->ContainerLevel() == 0 )
       return ErrorState();

    if ( CommType_->IsNoShipment() )
    {
       return ErrorState();
    }
/*----------------------------------------------------------------------------*/
/* Calculate count of and Containerpack items                                 */
/*----------------------------------------------------------------------------*/
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsCancelled() )
           continue;
       if ( item->IsSeparatePosition() )
           continue;
       if ( item->ArtikelNr() == 0 )
          continue;
       if ( !item->IsKnownProduct() )
          continue;
       if ( item->MengeGeliefert() == 0 )
          continue;
       if ( item->ArtBase()->ArtFlags().IsContainerArtikel() )
          continue;
       if ( item->ArtBase()->ContainerGroesse() > 0 &&
            item->MengeGeliefert_ >= item->ArtBase()->ContainerGroesse() )
       {
          if (  (item->MengeGeliefert_ % item->ArtBase()->ContainerGroesse()) == 0 )
          {
             item->SetContainerLevel(Param()->ContainerLevel());
             continue;
          }
          /* QtyOrigin = */ item->MengeBestellt();
          newitem = CopyOrderItem(item, pxOrderItem::SeparateContainer, SplittType_Unknown);
          // Recalculate rebates for the new item depend on the quantity ordered by the original
          // position.(QtyOrigin)

          pxItemDiscountList* srcdlist = item->ItemDiscountList();
          if (srcdlist)
          {
             pxItemDiscountListIter  cursor(*srcdlist);
             while ( (entriep = (pxItemDiscount*) ++cursor) != NULL )
             {
                newentriep = new pxItemDiscount(Session(), KdAuftragNr_, newitem->PosNr(),
                                        entriep->DiscountType(), entriep->PharmacyGroupId());
                newentriep->SetDiscountValuePct(entriep->DiscountValuePct());
                newentriep->SetPaymentTargetNo(entriep->PaymentTargetNo());
                newentriep->SetDiscountValPctMan(entriep->DiscountValPctMan());
                newentriep->SetDiscountCategory(entriep->DiscountCategory());
                newentriep->SetInternalDiscountFlag(entriep->InternalDiscountFlag());
                newentriep->SetRefundValuePct(entriep->RefundValuePct());
                newentriep->Put();
                newitem->ItemDiscountList()->Append(newentriep);
             }
             if ( item->MengeGeliefert() == 0 )
             {
                entriep->Delete();
                delete cursor.Remove();
                entriep = NULL;
             }
          }
          newitem->SetDirty();
          newitem->SetSeparatePosition();
        //newitem->SetContainerLevel(param.ContainerLevel());
          item->SetLinkPosNr(newitem->PosNr());
          item->SetDirty();
       }
    }
    return ErrorState();
}
