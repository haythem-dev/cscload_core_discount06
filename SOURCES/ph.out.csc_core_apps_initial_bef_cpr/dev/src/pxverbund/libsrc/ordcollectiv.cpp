#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxcomtyp.hpp"
#include "pxcstot.hpp"

/*----------------------------------------------------------------------------*/
/*  CalcLogisticVolume: this methode calculates the logistic volume for this  */
/*  this order, depend on the postions within this order.                     */
/*  this order, depend on the postions within this order.                     */
/*----------------------------------------------------------------------------*/
long
pxOrder :: CalcLogisticVolume
(
)
{
    ClearError();
    long volume = 0;
    pxOrderItemList* itemlist = NULL;
    pxOrderItem *item;


    if ( !( IsCollectiveOrderDiscountable()) )
    {
       return volume;
    }

    if ( !ItemList_ )          // order not opened
    {
       itemlist = new pxOrderItemList(*this);
       itemlist->Select();     // read its items
       if ( !itemlist->IsGoodState() )
       {
          itemlist->Clear();
          delete itemlist;
          return volume;
       }
/*----------------------------------------------------------------------------*/
/*     Now scan the list of positions                                         */
/*----------------------------------------------------------------------------*/
       pxOrderItemListIter it(*itemlist);
       while ( (item = (pxOrderItem*) ++it) != NULL )
       {
          if ( !item->IsCancelled() )
          {
             if (  ( item->MengeGeliefert() + item->MengeVerbund()  > 0 ) &&
                     item->IsProductStocked() )
             {
                volume += item->ArtBase()->Laenge()*item->ArtBase()->Breite()*item->ArtBase()->Hoehe();
             }
          }
       }
       itemlist->Clear();
       delete itemlist;
       return volume;
    }

/*----------------------------------------------------------------------------*/
/*     Now scan the list of positions                                         */
/*----------------------------------------------------------------------------*/
    pxOrderItemListIter it(*ItemList_);
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( !item->IsCancelled() )
       {
          if ( ( ( item->MengeGeliefert() + item->MengeVerbund() ) > 0 ) &&
                  item->IsProductStocked()  )
          {
             volume += item->ArtBase()->Laenge()*item->ArtBase()->Breite()*item->ArtBase()->Hoehe();
          }
       }
    }
    if ( itemlist )
    {
       itemlist->Clear();
       delete itemlist;
    }
    return volume;
}
