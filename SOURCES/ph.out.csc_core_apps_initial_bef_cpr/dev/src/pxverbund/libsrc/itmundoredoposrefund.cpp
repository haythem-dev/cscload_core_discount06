#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxkdauftragposrefund.hpp"

/*----------------------------------------------------------------------------*/
/*  UndoRedoOrderPosRefund: Looks for OrderPosRefund (kdauftragposrefund)     */
/*  entries. If entries available, so src.Entries are deleted and new entries */
/*  for this item are inserted   .                                            */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedoOrderPosRefund
(
    pxOrderItem* src
)
{
    pxKdAuftragPosRefund *entriep = NULL;
    pxKdAuftragPosRefund *newentriep = NULL;

    if ( Order().Param()->IsNewDiscount() )
    {
        pxKdAuftragPosRefundList* srcdlist = src->KdAuftragPosRefundList();
       if (srcdlist)
       {
          pxKdAuftragPosRefundListIter  cursor(*srcdlist);
          {
             while ( (entriep = (pxKdAuftragPosRefund*) ++cursor) != NULL )
             {
                newentriep = new pxKdAuftragPosRefund(Session(), KdAuftragNr_, PosNr_,
                                     entriep->RefundValue(), entriep-> RefundSrc(), entriep->Promotion_No());
                newentriep->Put();
                KdAuftragPosRefundList()->Append(newentriep);
                entriep->Delete();
                delete cursor.Remove();
                entriep = NULL;
             }
          }
       }
    }
    return ErrorState();
}
