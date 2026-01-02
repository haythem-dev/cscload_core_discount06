/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Internal order item posting methods for a stocked product.

REVISION HISTORY

25 September 2012 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"

/*----------------------------------------------------------------------------*/
/*  UndoRedoPurchaseItem: This is a split function for DI positions           */
/*  On the the original position(src), the dispodelivery quantity will be     */
/*  canceled by an negativ artikelkonto entry.                                */
/*  The ordered quantity(MengeBestellt) on SRC is reduced by the dispodelivery*/
/*  quantity.After that, the drestdelivery quantity of SRC will be booked on   */
/*  THIS object(NewOrderItem).                                                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedoPurchaseItem
(
    pxOrderItem* src                    // container item
)
{
    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return
    short flags = 0;

    long MengeBestellt = src->MengeBestellt();

    long    MengeDisponiert  = src->MengeDisponiert();

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

    src->ClearDisponieren();              // clear restdelivery marker
    // reduce MengeBestaetig and MengeBestellt by auxdelivery quantity
    src->MengeBestaetigt( src->MengeBestaetigt() - MengeDisponiert);
    src->MengeBestellt( src->MengeBestellt() - MengeDisponiert);
    if (src->MengeBestellt() == 0 )
    {
       src->MengeBestellt(MengeBestellt);
    }
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

    // Now rebook the auxdelivery quantity on this object.
    // Init some member
    MengeBestellt_   = 0;
    MengeAbgebucht_  = 0;
    MengeGeliefert_  = 0;
    MengeBestaetigt_ = 0;
    flags |= bPOST_IGN_LACK;

    InitOrderItem_Core(ArtikelNr_, MengeDisponiert,0L,0L,
                 pxOrderItem::PurchaseOrder, pxOrderItem::TypeProductStocked,
                 flags);

    if (!IsGoodState())
    {
       ClearError();
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
/*  UndoRedoDispoItem: This is a split function for DI positions              */
/*  On the the original position(src), the dispodelivery quantity will be     */
/*  canceled by an negativ artikelkonto entry.                                */
/*  The ordered quantity(MengeBestellt) on SRC is reduced by the dispodelivery*/
/*  quantity.After that, the drestdelivery quantity of SRC will be booked on   */
/*  THIS object(NewOrderItem).                                                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedoDispoItem
(
    pxOrderItem* src                    // container item
)
{
    pxArtDispo* srcArtDispo = NULL;

    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return
    // unused variable
    // short flags = 0;

    srcArtDispo = src->ArtDispo();

    if ( srcArtDispo == NULL )
    {
       return ErrorState();
    }

    ArtDispo_ = new pxArtDispo(*srcArtDispo);
    ArtDispo_->SetOrder(KdAuftragNr_, PosNr_);

    src->nDBBeginTransaction(cDBTransRecord);
    src->SetPosTyp( TypeProductStocked);
    srcArtDispo->Delete();
    src->SetNichtNachPharmos();

    if ( src->IsGoodState() )
    {
       src->nDBCommit(cDBTransRecord);
    }
    else
    {
       src->nDBRollBack();
       return ErrorState();
    }

    ArtDispo_->nDBBeginTransaction(cDBTransRecord);
    ArtDispo_->Put();
    if ( ArtDispo_->IsGoodState() )
    {
       ArtDispo_->nDBCommit(cDBTransRecord);
    }
    else
    {
       ArtDispo_->nDBRollBack();
       return ErrorState();
    }

    return ErrorState();
}
