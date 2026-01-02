#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxordtyp.hpp"
#include "pxordvtr.hpp"
#include "pxcstot.hpp"
#include "pxholiday.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

extern bool pxGlobalNoDatabaseWrite;

/*----------------------------------------------------------------------------*/
/*  ReCalculateOrder:                                                         */
/*  The current order will be recalculated depend on DatumAuslieferung.       */
/*  If DatumAuslieferung > 0, we do an undo/redo of all positions within this */
/*  order during order closing to get eventualy new discount conditions       */
/*  depend on validity date. This is a special function wihin the bulgarian   */
/*  application.                                                              */
/*----------------------------------------------------------------------------*/
int
pxOrder :: ReCalculateOrder()
{
    int   retval = 0;
    nDate currentdate;
    long  QOrdered    = 0;
    long  QDisInKind  = 0;
    long  QDemanded   = 0;
    // unused variable
    // short      oldqs       = 0;
    ClearError();

    if (!Session()->isBulgaria())
       return ErrorState();

    if ( DatumAuslieferung() == pxConstants::NullDate )
        return ErrorState();

    if ( DatumAuslieferung() > currentdate )
        return ErrorState();

/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if ( !IsChangeable() )
       return retval;             // order not changeable

    if ( !IsPseudoLock() )
    {
       if ( !IsLocked() )                  // order still locked ??
       {
          ExternalError(CMsgStream(),CMSG_ORD_LOCK_DISAPPEARED, KdAuftragNr_);
          return NULL;
       }
    }
    if ( OrderType_->IsDiscountAccount() || OrderType_->IsManualPromotion() || OrderType_->IsRetailSalesOrder() ) // does not affect CO and RO and MP and EH
       return ErrorState();


/*----------------------------------------------------------------------------*/
/*  Quantity posting and calculation of terms and conditions for stocked      */
/*  product items must  be re-done in case og DatumAuslieferung > 0           */
/*  be re-done in that case.                                                  */
/*----------------------------------------------------------------------------*/
    nDBBeginTransaction(cDBTransSet);   // embed the following in a transaction
    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    UndoCreditDayTurnOver();
    while ( ((item = (pxOrderItem*) ++it) != NULL) && IsGoodState() )
    {
        if ( item->LinkPosNr() > 0 )
        {
            if ( item->LinkPosNr() < item->PosNr() )
            {
                continue;
            }
        }
        if ( item->IsProductStocked() )
        {
            // save old quantities:
            QOrdered    = item->MengeBestellt_;
            QDisInKind  = 0;
            QDemanded   = item->MengeBestellt_;

            item->UndoItemBG();
            Error() = item->Error();
            if ( IsGoodState() )
            {
                item->RedoItemBG(QOrdered,QDisInKind,QDemanded );
                CalcPromotionQuota(item);        // redo Promotionquota
            }
        }
    }

/*----------------------------------------------------------------------------*/
/*  Update order, then write it into the data base.                           */
/*----------------------------------------------------------------------------*/
    if ( IsGoodState() )
    {
       ReCalcValues();
       //Put();                        // update data base
    }

    /*if ( IsGoodState() )
       nDBCommit(cDBTransSet);          // commit changes
    else
       nDBRollBack();                   // or roll them back in case of any error
    */
    if ( pxGlobalNoDatabaseWrite)
       ClearError();
    return retval;
}
