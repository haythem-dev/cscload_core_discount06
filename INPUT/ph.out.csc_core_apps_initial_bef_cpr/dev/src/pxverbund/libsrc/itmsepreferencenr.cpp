/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Internal order item posting methods for a stocked product.

REVISION HISTORY

31 March 2008 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"

/*----------------------------------------------------------------------------*/
/*  UndoRedoReferenceItem                                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedoReferenceItem
(
    pxOrderItem* src                    // container item
)
{
    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return
    long MengeBestellt = src->MengeBestellt();

    //first undo orignal item
    src->UndoItem();
    // reset some src members
    src->MengeBestaetigt( 0L);
    src->MengeGeliefert( 0L);
    src->MengeAbgebucht( 0L);
    src->MengeNatra( 0L);

    // Init some member
    MengeBestellt_   = 0;
    MengeAbgebucht_  = 0;
    MengeGeliefert_  = 0;
    MengeBestaetigt_ = 0;
    InitOrderItem_08(ArtikelNr_, MengeBestellt,0L,0L, (short) 0,
                 pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked,
                 bPOST_DEFAULT);

    return ErrorState();
}
