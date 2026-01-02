#include "pxsess.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"

/*----------------------------------------------------------------------------*/
/*  CountAuxDeliveryPos:                                                      */
/*----------------------------------------------------------------------------*/
long
pxOrder :: CountAuxDeliveryPos
(
)
{   long count = 0;
    pxOrderItemListIter it(*ItemList_);
    pxOrderItem *item;
    it.Reset();
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       count += item->IsAuxPosted();
    }
    return count;
}
/*----------------------------------------------------------------------------*/
/*  CountDefects       :                                                      */
/*----------------------------------------------------------------------------*/
long
pxOrder :: CountDefects
(
)
{   long count = 0;
    pxOrderItemListIter it(*ItemList_);
    pxOrderItem *item;
    it.Reset();
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( (item->IsQStateNotOnHand() && !item->IsNachliefern()) ||
            (item->IsUnKnownProduct())  || !(item->IsArtStateGood()) )
       {
          count ++;
       }
    }
    return count;
}
