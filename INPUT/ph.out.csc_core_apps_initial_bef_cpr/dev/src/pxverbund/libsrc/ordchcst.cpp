#include "pxorder.hpp"
#include <pxrecord.h>
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcstbtm.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxcstot.hpp"
#include "pxordvtr.hpp"
#include "types/messagecodeenum.inc"
#include "pxoeparm.hpp"

/*----------------------------------------------------------------------------*/
/*  Set Customer identification number.                                       */
/*  Returns number of order items that have gone into quantity state          */
/*  'NotOnHand' during re-doing quantity posting, otherwise 0 is returned.    */
/*  To catch errors and conditions, the error object must be explicitly       */
/*  tested.                                                                   */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ChangeCustomer
(
    long    NewIDFNr,
    short   BranchNo
)
{
    int  retval            = 0;                    // return value
    long MengeNatra        = 0;
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;

    int count = CountItems(bCOUNT_ITEMTYPE, (long) pxOrderItem::TypeProductStocked);
/*----------------------------------------------------------------------------*/
/*  SR-15004144 Check contents of order. If there are already worked up       */
/*  IBT positions or daynightmerge positions within this order, so change of  */
/*  order type or customer or Branch is not allowed.                          */
/*----------------------------------------------------------------------------*/
    if ( count > 0 )
    {
        if ( hasAtLeastOneCompletedIbtBooking() || CountDayNightMergePositions() > 0 || CountSeparatedPositions() > 0 )
        {
            if ( BranchNo > 0 )                // change order to branche
            {
                ExternalError(CMsgStream(), CMSG_ORD_CHANGE_OF_BRANCH_NOT_ALLOWED);
            }
            else
            {
                ExternalError(CMsgStream(), CMSG_ORD_CHANGE_OF_CUSTOMER_NOT_ALLOWED);
            }
            return retval;
        }
    }

    if ( BranchNo == 0)
        BranchNo = VertriebsZentrumNr_;

    if  ( IDFNr_  == NewIDFNr && VertriebsZentrumNr_ == BranchNo) // on equal, no change
        return retval;

    if ( !IsChangeable() )
        return retval;                          // order not changeable
/*----------------------------------------------------------------------------*/
/*  First get the new customer from the database                              */
/*----------------------------------------------------------------------------*/
    pxCustBase    *newcustomer =  new pxCustBase(Session(), BranchNo, NewIDFNr);
    if ( !(newcustomer->IsGoodState()) )          // then customer not found
    {
        ExternalError(CMsgStream(), CMSG_CST_NOTFOUND, NewIDFNr);
        return retval;
    }

/*----------------------------------------------------------------------------*/
/*  Locate table entries for order type, commission type and stock transaction*/
/*  for the new customer                                                      */
/*----------------------------------------------------------------------------*/
    pxCustOrderType *ot = newcustomer->OrderTypeList()->Find(KdAuftragArt_, newcustomer->Vertriebszentrum(), newcustomer->KundenNr());
    pxCommType      *ct = Session()->CommTypeList(newcustomer->Vertriebszentrum())->Find(KoArt_, newcustomer->Vertriebszentrum());
    pxStockTrans    *st = Session()->StockTransList(newcustomer->Vertriebszentrum())->Find(BuchArt_, newcustomer->Vertriebszentrum());
    if ( !ot )
    {
        ExternalError(CMsgStream(), CMSG_ORD_TYPE_CUST, (char*)KdAuftragArt_, NewIDFNr);
        return retval;
    }
    if ( !ct )
    {
        ExternalError(CMsgStream(), CMSG_ORD_INVALID_COMMTYPE, (int)KoArt_);
        return retval;
    }
    if ( !st )
    {
        ExternalError(CMsgStream(), CMSG_ORD_INVALID_STOCKTRANS, (int)BuchArt_);
        return retval;
    }

    // Test for a valid combination:
    if ( !(Session()->OrderValidTransList(newcustomer->Vertriebszentrum())->Find(KdAuftragArt_, KoArt_ - '0', BuchArt_ - '0', newcustomer->Vertriebszentrum())) )
    {
        ExternalError(CMsgStream(), CMSG_ORD_TYPE_COMB, (char*)KdAuftragArt_, (int) KoArt_, (int) BuchArt_);
        return retval;
    }

/*----------------------------------------------------------------------------*/
/*  First rollback the complete order, but do not cancel this order           */
/*  This is necessary, because after that we change customer and Branchno     */
/*----------------------------------------------------------------------------*/
    nDBBeginTransaction(cDBTransSet);   // embed the following in a transaction
    if  ( count > 0 )
    {
        while ( ((item = (pxOrderItem*) ++it) != NULL) && IsGoodState() )
        {
            if ( item->IsProductStocked() )
            {
                MengeNatra       = item->MengeNatra();
                item->UndoItem();
                item->MengeNatra(MengeNatra);
                Error() = item->Error();
            }
        }
    }
/*----------------------------------------------------------------------------*/
/*  Update order, then write it into the data base.                           */
/*----------------------------------------------------------------------------*/
    if ( IsGoodState() )
    {
        nDBCommit(cDBTransSet);       // commit changes
    }
    else
    {
        nDBRollBack();                // or roll them back in case of any error
        return retval;
    }

/*----------------------------------------------------------------------------*/
/*  Now the new customer and his related entries are located.                 */
/*  Delete the current customer from the order object and build a new one     */
/*----------------------------------------------------------------------------*/
    if  ( Customer_ )
    {
        delete Customer_;                // delete the current customer object
        Customer_  = NULL;               // end set pointer to 0
        OrderTourId_.Clear();                 // clear route assignment
        Route_     = NULL;               // clear route assignment
        OrderType_ = NULL;               // clear route assignment
    }

    Customer_ = newcustomer;            // new customer becomes currency
    IDFNr_ = Customer()->IDFNr();       // new customer ID
    OrderType_     =  ot;               // store table pointers
    CommType_      =  ct;
    StockTrans_    =  st;

    KundenNr_ = Customer()->KundenNr();  // internal customer id
    VertriebsZentrumNr_ = Customer()->Vertriebszentrum();

    pxCustBusinessTimes& btime = Customer()->BusyTime();
    ZeitEndeAM_ = btime.EndAM();        // copy customer's business times
    ZeitEndePM_ = btime.EndPM();
    if ( Session()->Device()->IsVideo() && !(CommType().IsNoShipment()) )
        RouteAssign();                   // assign a default route

/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if ( IsEntryInProgress() && CommType_->IsNoShipment() )
    {
        RouteAssignClearTourAssignment();
    }
    SetDirty();                         // must update order record

    if ( IsEntryInProgress() && CommType_->IsNoShipment() )
    {
        RouteAssignClearTourAssignment();
    }

    if ( !IsGoodState() )
    {
        return retval;
    }

/*----------------------------------------------------------------------------*/
/*  Test for order type and/or stock transaction changes. Quantity posting    */
/*  and calculation of terms and conditions for stocked product items must    */
/*  be re-done in that case.                                                  */
/*----------------------------------------------------------------------------*/
    nDBBeginTransaction(cDBTransDataBase);   // embed the following in a transaction
    if  ( count > 0 )
    {
        it.Reset();
        while ( ((item = (pxOrderItem*) ++it) != NULL) && IsGoodState() )
        {
            if (item->IsSperreRabattManuell())
            {
               continue;
            }

            if ( item->IsProductStocked() )
            {
                item->RedoItem(*ot);
                Error() = item->Error();
            }
        }
    }

/*----------------------------------------------------------------------------*/
/*  Update order, then write it into the data base.                           */
/*----------------------------------------------------------------------------*/
    if ( IsGoodState() )
    {
        if (Param()->IsUseNewDiscountCalc())
        {
            nDBBeginTransaction(cDBTransRecord);
        }
        ReCalcValues();
        Put();
        if (Param()->IsUseNewDiscountCalc()){
            // update data base
            if ( IsGoodState() )
                nDBCommit(cDBTransRecord);          // commit changes
            else
                nDBRollBack();                   // or roll them back in case of any error
        }
    }

    if ( IsGoodState() )
        nDBCommit(cDBTransDataBase);          // commit changes
    else
        nDBRollBack();                   // or roll them back in case of any error

    return retval;
}
