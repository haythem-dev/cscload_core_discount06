/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Internal order item posting methods for a stocked product.

REVISION HISTORY

21 November 2007 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include <pxrecord.h>
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "tourassignmentutil.hpp"
#include "types/origintypeenum.inc"

/*----------------------------------------------------------------------------*/
/*  UndoRedoAuxdelivery: This is a split function for auxdelivery positions   */
/*  On the the original position(src), the auxdelivery quantity will be       */
/*  canceled by an negativ artikelkonto entry.                                */
/*  The ordered quantity(MengeBestellt) on SRC is reduced by the auxdelivery  */
/*  quantity.After that, the auxdelivery quantity of SRC will be booked on    */
/*  THIS object(NewOrderItem).                                                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedoAuxdelivery( pxOrderItem* src, const long QOrderedOriginal)
{
    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return
    short flags = 0;

    long MengeBestellt = src->MengeBestellt();

    long    MengeVerbund   = src->MengeVerbund();
    short   VerbundFiliale = src->VerbundFilialNr();

    //first undo auyposting on src
    src->nDBBeginTransaction(cDBTransRecord);
    if ( MengeVerbund > 0 )
    {
       src->UndoArtQuota( MengeVerbund );
    }
    src->UndoAuxPosting();              // undo auxposting
    // reduce MengeBestaetig and MengeBestellt by auxdelivery quantity
    src->MengeBestaetigt( src->MengeBestaetigt() - MengeVerbund);
    src->MengeBestellt( src->MengeBestellt() - MengeVerbund);
    if (src->MengeBestellt() <= 0 ) //SR-21083884: to avoid setting -1
    {
       src->MengeBestellt(MengeBestellt);
    }
    if (src->MengeBestaetigt() < 0) //SR-21083884
    {
       src->MengeBestaetigt(0L);
    }
    src->SetMengeVerbund( 0L);

    // remove tour information for undone ibt booking
    Order().getTourAssignmentUtil()->removeIBTTourAssignment(src);

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
    flags |= bPOST_IBTPOSREBOOK;
    flags |= bPOST_AUXDELIVERY;

    /*
    SR-21083884: For CH when we have an IBT article with Natra and in the ordering br. 13 we have 0 or 1 piece available and the remaining has to be deliverd from IBT br.12,since the request is being created for IBT branch 12 we just need to get the quantity requested not to again calculate natra by the ibt branch.
    so we subtract the natra qty. this condition applies when from ordering br.13 the liefert is 0, since our system books the natra qty from ordering br 13. if it has bestand more than 1 piece available in stock.
    */
    if(Session()->isSwitzerland() && src->MengeGeliefert_ == 0)
    {
        if(this->MengeNatra_ > 0)
        {
            if ((MengeVerbund - this->MengeNatra_) > 0 )
            {
                MengeVerbund = MengeVerbund - MengeNatra_;
            }
        }
    }

    InitOrderItem_08(ArtikelNr_, MengeVerbund,0L,0L, VerbundFiliale,
                 pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked,
                 flags);
    // Recalculate rebates for the new item depend on the quantity ordered by the original
    // position.(QOrderedOriginal)
    if ( QOrderedOriginal > 0 )
    {
        this->calculateRebateForOrderedQuantity(QOrderedOriginal);
    }

    if (!IsGoodState())
    {
       ClearError();
    }
    return 0;
}
/*----------------------------------------------------------------------------*/
/*  GetIBTQuantityOfLinkedPosition: This is a function that looks for Inter Branch            */
/*  Transfer quantity delivered for this item.                                */
/*  This Item should be linked to the real IBT Position within the order for  */
/*  item. This function is called during order transfer to PHARMOS (pvhx04)   */
/*  Take care for a well constructed item object.                             */
/*----------------------------------------------------------------------------*/
long pxOrderItem::GetIBTQuantityOfLinkedPosition()
{
    long IBTQuantitity = 0;

    if ( LinkPosNr() == 0 )
       return  IBTQuantitity;

    pxOrderItem* pos = (pxOrderItem*)Order().ItemList()->At(LinkPosNr() - 1); // get item
    if (pos)
    {
       IBTQuantitity = pos->MengeVerbund();
    }

    return IBTQuantitity;
}
/*----------------------------------------------------------------------------*/
/*  UndoRedoAuxdeliveryComplete: This is a split function for the complete    */
/*  auxdelivery positions                                                     */
/*  On the the original position(src), the auxdelivery quantity will be       */
/*  canceled by an negativ artikelkonto entry.                                */
/*  The ordered quantity(MengeBestellt) on SRC is reduced by the auxdelivery  */
/*  quantity.After that, the auxdelivery quantity of SRC will be booked on    */
/*  THIS object(NewOrderItem).                                                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedoAuxdeliveryComplete
(
    pxOrderItem* src                    // container item
)
{
    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return
    short flags = 0;

    long MengeBestellt = src->MengeBestellt();
    short   VerbundFiliale = src->VerbundFilialNr();

    //first undo auxposting on src
    src->nDBBeginTransaction(cDBTransRecord);
    src->UndoAuxPosting();              // undo auxposting

    // reduce MengeBestaetig and MengeBestellt by auxdelivery quantity
    src->MengeBestaetigt( 0L );
    src->MengeBestellt( 0L );
    src->SetMengeVerbund( 0L);
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
    flags |= bPOST_IBTPOSREBOOK;
    flags |= bPOST_AUXDELIVERY;

    InitOrderItem_08(ArtikelNr_, MengeBestellt,0L,0L, VerbundFiliale,
                 pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked,
                 flags);

    if (!IsGoodState())
    {
       ClearError();
    }
    return 0;
}
