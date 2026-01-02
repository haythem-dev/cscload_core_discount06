#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxartbas.hpp"

/*----------------------------------------------------------------------------*/
/*  Rollback complete item. It's like cancel .                                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: RollBackOrderPosition
(
)
{
    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return

    if ( !IsChangeable() )
       return ErrorState();

    nDBBeginTransaction(cDBTransRecord);
    if (ArtBase(cDBGET_FORUPDATE) && ArtBase()->IsGoodState())
    {
       UndoPosParking();
       UndoPromoQuota();
       UndoOrderPosPromo();
       UndoOrderPosRefund();
       UndoItemDiscount();
       CancelArtQuota();
       UndoTenderProgress();
       UndoQuantityPosting(Order().StockTrans());
       ArtBaseUpdate();
       UndoAuxPosting();
    }

    if ( IsGoodState() )
    {
       SetDirty();
    }

    return ItemUpdate();
}
