#include "pxorder.hpp"
//#include "pxitem.hpp"
#include "pxcomtyp.hpp"

/*----------------------------------------------------------------------------*/
/* SplittPartialIBTPosition                                                   */
/* If the complete ordered quantity is delivered by Inter Branch Transfer,    */
/* no action takes place on item. Just if a part of the ordered               */
/* quantity is deliverd by IBT then this methode generates a separate IBT     */
/* position for the  IBT quantity                                             */
/*----------------------------------------------------------------------------*/
int
pxOrder ::  SplittPartialIBTPosition
(
    pxOrderItem* item
)
{
/*----------------------------------------------------------------------------*/
/*  some prechecks before further action has taking place                     */
/*----------------------------------------------------------------------------*/
    if (!(item->IsAuxPosted()) )
    {
       return ErrorState();
    }

    if ( IsPseudoLock() )                     // Do not Splitt if PreudoLock
    {
       return ErrorState();                  // INC-031782 INC-032063
    }

    if ( CommType_->IsNoShipment() )
    {
       return ErrorState();
    }

	if ( (item->MengeBestellt_ + item->MengeNatra_ )  >  item->MengeVerbund() )
    {
       long QtyOrigin = item->MengeBestellt();
       pxOrderItem* newitem = CopyOrderItem(item, pxOrderItem::AuxDelivery, SplittType_Unknown);
       // Recalculate rebates for the new item depend on the quantity ordered by the original position.(QtyOrigin)
       if ( item->MengeNatra() == 0 )
       {
          newitem->SetMengeBestelltOrg(QtyOrigin);
          newitem->CalcDiscount(QtyOrigin);
          newitem->SetDirty();
       }
       item->nDBBeginTransaction(cDBTransRecord);
       item->SetMengeBestelltOrg(QtyOrigin);
       item->SetLinkPosNr(newitem->PosNr());
       item->SetPartialIBTQantity();
       item->SetDirty();
       item->ItemUpdate();
       if ( item->IsGoodState() )
       {
          item->nDBCommit(cDBTransRecord);
       }
       else
       {
          item->nDBRollBack();
       }
    }
    return ErrorState();
}
