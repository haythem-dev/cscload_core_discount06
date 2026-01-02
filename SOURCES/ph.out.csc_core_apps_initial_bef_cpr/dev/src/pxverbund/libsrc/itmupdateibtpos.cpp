/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Item update methods available at the API level.
*/

#include "pxitem.hpp"
#include "pxorder.hpp"

/*----------------------------------------------------------------------------*/
/*  ItemUpdateDiscountPos                                                 .   */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: ItemUpdateIBTPos
(
    pxOrderItem* item
)
{
    long  MengeBestellt;
    long  MengeVerbund;
    short VerbundFiliale;
    long Menge;

/*----------------------------------------------------------------------------*/
/*  some prechecks before further action has taking place                     */
/*----------------------------------------------------------------------------*/
    if (Order().Swiss() )                  // do not affect Swiss orders
    {
       return ErrorState();
    }

    if (!(item->IsAuxPosted()) )
    {
       return ErrorState();
    }

    if ( item == NULL)
    {
       return ErrorState();
    }

    if ( item->LinkPosNr() > 0 && item->IsGoodState() && item->IsAuxPosted())
    {

       MengeBestellt  = item->MengeBestellt();
       MengeVerbund   = item->MengeVerbund();
       VerbundFiliale = item->VerbundFilialNr();;

       pxOrderItem* pos = (pxOrderItem*)Order().ItemList()->At(item->LinkPosNr() - 1); // get item
       if (pos)
       {
          //first undo auyposting on item
          item->nDBBeginTransaction(cDBTransRecord);
          item->UndoAuxPosting();              // undo auxposting
          // reduce MengeBestaetig and MengeBestellt by auxdelivery quantity
          item->MengeBestaetigt( item->MengeBestaetigt() - MengeVerbund);
          item->MengeBestellt( item->MengeBestellt() - MengeVerbund);
          if (item->MengeBestellt() == 0 )
          {
             item->MengeBestellt(MengeBestellt);
          }
          item->SetMengeVerbund( 0L);
          Error() = item->Error();
          if ( IsGoodState() )
          {
             item->nDBCommit(cDBTransRecord);
          }
          else
          {
             item->nDBRollBack();
             return ErrorState();
          }
          Menge = MengeVerbund;
          pos->OrderQuantity (Menge,0,0,pxOrderItem::BookingTypeDefault, bPOST_DEFAULT, VerbundFiliale, 0.0);
       }
    }
    else
    {
       Order().SplittPartialIBTPosition(this);
    }
    return   ErrorState();
}
