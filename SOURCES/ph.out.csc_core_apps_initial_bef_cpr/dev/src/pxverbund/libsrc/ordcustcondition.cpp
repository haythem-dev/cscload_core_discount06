/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrder
Implementation of Customer Discount Conditions hanling

REVISION HISTORY

04 Dec 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/
#include "pxsess.hpp"
#include "pxrecord.h"
#include "pxcstbas.hpp"
#include "pxdevice.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxcustdisccondition.hpp"
#include "pxsubordertype.hpp"
#include "pxitemdiscount.hpp"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/*  ReduceCustConditions: this methode is used within the french application  */
/*  The purpose of this methode is, to check ordervalue depend on             */
/*  customer discount condition and subordertype conditions.                  */
/*  Action takes place just if orders subordertype not is empty.              */
/*  Take care for a well constructed pxOrder object                           */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ReduceCustConditions
(
)
{

    double LossInDiscount;               // Loss in Discount (Abschlag)
    double iDiscount;               // Loss in Discount (Abschlag)
    pxCustDiscCondition* CustCond = NULL;  // Customer discount conditions
    pxSubOrderType*      SubCond  = NULL;  // discountlist entryp
    pxItemDiscountList*  dikl     = NULL;
    pxItemDiscount*      dikp     = NULL;
    nString sot = SubOrderType_;
    sot.Strip();               // todo Krükke: alle Strings aus der DB trimmen???
    if ( sot.IsEmpty() )       // do work just if SubOrderType_ is not empty (or "   ")
       return ErrorState();

    if ( (Customer_->DiscountConditions(KdAuftragArt_,SubOrderType_) ) == 0 )
    {
       CustCond = Customer_->CustDiscCondition();
       SubCond  = Customer_->SubOrderType();

       if (  CustCond > NULL && SubCond > NULL )    // just if both are available
       {
          LossInDiscount = CustCond->LossInDiscount();
          if ( !(WertAuftrag_ <  (nMoney)CustCond->MinOrderValue()) ) // ordervalue satisfied ??
             return ErrorState();                 // go back to caller

          dikl = new  pxItemDiscountList(Session());
          if (!(dikl->Select( KdAuftragNr())) )
          {
             delete dikl;
             dikl = NULL;
             return ErrorState();                 // go back to caller
          }
          pxItemDiscountListIter cursor(*dikl);
          while ( (dikp = (pxItemDiscount*) ++ cursor) != NULL )
          {
             nDBBeginTransaction(cDBTransRecord);
             iDiscount = dikp->DiscountValuePct();
             iDiscount = iDiscount - ((iDiscount/100) * LossInDiscount);
             if ( iDiscount == pxConstants::dZero )
             {
                dikp->Delete();
                delete cursor.Remove();
                continue;
             }
             dikp->SetDiscountValuePct(iDiscount);
             dikp->Put();
             if ( dikp->IsGoodState() )
                nDBCommit(cDBTransRecord);
            else
                nDBRollBack();
          }
       }
    }
    return ErrorState();
}

