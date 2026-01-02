/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Internal order item posting methods for a stocked product.

REVISION HISTORY

10 January 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"

/*----------------------------------------------------------------------------*/
/*  UndoRedoDelayedPurchaseItem: This is a split function for delayed         */
/*  DI positions                                                              */
/*  On the original position(src), the dispodelivery quantity will be         */
/*  canceled by an negativ artikelkonto entry and also the MengeGeliefert_    */
/*  will be canceled by an negativ artikelkonto entry                         */
/*  After that we will rebook  this item within the new order                 */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedoDelayedPurchaseItem
(
    pxOrderItem* src                    // container item
)
{
    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return
    short flags = 0;

    long MengeBestellt = src->MengeBestellt();

    if ( !src->IsDisponieren() )
    {
       return ErrorState();
    }
    src->nDBBeginTransaction(cDBTransRecord);
    pxVerbund::subsequentDelivery::pxDeliveryPos* dp = src->AuxDelList()->Find(src->KdAuftragNr(), src->PosNr(), pxVerbund::subsequentDelivery::pxDPT_DISPOSAL_ITEM);
    if (dp)
    {
       dp->Delete();
    }

    src->ClearDisponieren();              // clear dispo marker
    Error() = src->Error();
    if ( IsGoodState() )
    {
       src->nDBCommit(cDBTransRecord);
    }
    else
    {
       src->nDBRollBack();
       return ErrorState();
    }

    // Now rebook this object with original MengeBestellt_.
    // Init some member
    MengeBestellt_   = 0;
    MengeAbgebucht_  = 0;
    MengeGeliefert_  = 0;
    MengeBestaetigt_ = 0;
    flags |= bPOST_IGN_LACK;

    InitOrderItem_Core(ArtikelNr_, MengeBestellt,0L,0L,
                 pxOrderItem::PurchaseOrder, pxOrderItem::TypeProductStocked,
                 flags);

    if (!IsGoodState())
    {
       ClearError();
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  UndoRedoDelayedRestDeliveryItem: This is a split function for delayed     */
/*  NL positions                                                              */
/*  On the original position(src), the restdelivery quantity will be          */
/*  canceled by an negativ artikelkonto entry and also the MengeGeliefert_    */
/*  will be canceled by an negativ artikelkonto entry                         */
/*  After that we will rebook  this item within the new order                 */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedoDelayedRestDeliveryItem
(
    pxOrderItem* src                    // container item
)
{
    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return
    short flags = 0;

    long MengeBestellt = src->MengeBestellt();

    if ( !src->IsNachliefern() )
    {
       return ErrorState();
    }
    src->nDBBeginTransaction(cDBTransRecord);
    pxVerbund::subsequentDelivery::pxDeliveryPos* dp = src->AuxDelList()->Find(src->KdAuftragNr(), src->PosNr(), pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
    if (dp)
    {
       dp->Delete();
    }

    src->ClearNachliefern();              // clear restdelivery marker
    Error() = src->Error();
    if ( IsGoodState() )
    {
       src->nDBCommit(cDBTransRecord);
    }
    else
    {
       src->nDBRollBack();
       return ErrorState();
    }

    // Now rebook this object with original MengeBestellt_.
    // Init some member
    MengeBestellt_   = 0;
    MengeAbgebucht_  = 0;
    MengeGeliefert_  = 0;
    MengeBestaetigt_ = 0;
    flags |= bPOST_IGN_LACK;

    InitOrderItem_Core(ArtikelNr_, MengeBestellt,0L,0L,
                 pxOrderItem::RestDelivery, pxOrderItem::TypeProductStocked,
                 flags);

    if (!IsGoodState())
    {
       ClearError();
    }
    return ErrorState();
}
