/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Some undo methode on Class pxOrderItem

REVISION HISTORY

28 Feb 2013 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxartbas.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"

/*----------------------------------------------------------------------------*/
/*  UndoItem: Rollback this item completely but do not write this item        */
/*  to the database. Bulgarian application                                    */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoItemBG
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
	   UndoItemDiscount();
	   UndoOrderPosPromo ();
	   UndoOrderPosRefund();
       CancelArtQuota();
	   UndoPromoQuota();
       UndoQuantityPosting(Order().StockTrans());
       ArtBaseUpdate();
       
    }
    ItemUpdate();
    if ( ArtBase_ )
    {
       nError::operator = (ArtBase_->Error()); // copy error object
       delete ArtBase_;             // and delete the artbase object
       ArtBase_ = NULL;
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  RedoItem: Rebook this item                                                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: RedoItemBG
(
    const long QOrdered,                // Qty ordered
	const long QDisInKind,              // Qty Disinkind
	const long QDemanded
)
{
    int    retval = 0;
    ClearError();

    nDBBeginTransaction(cDBTransRecord);
    if ( IsProductStocked() && !IsCancelled() && ArtBase(cDBGET_FORUPDATE) && ArtBase()->IsGoodState())
    {
       MengeBestellt_ = 0;              // to prevent unpredictable results on artaccount

       // Redo
       OrderQuantity(QOrdered, QDisInKind, QDemanded);
            
       if ( ErrorState() == nSTATE_CONDITION )
          ClearError();
       if ( IsGoodState() )
       {
          SetDirty();
       }
    }
    return retval;
}
