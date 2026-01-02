#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxoclpar.hpp"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/*  CheckPromotionValidity checks this order items for promotion validity     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CheckPromotionValidity
(
   const  Order::States state
)
{
    pxCustOrderType   *ot   =  OrderType_;
    bool doRecalculateOrder = false;
    nDate today;

    if (!Session()->isBulgaria())
    {
       return ErrorState();
    }

    if ( !(state == Order::EntryClosed) )
    {
       return ErrorState();
    }

    if ( DatumAuslieferung() == pxConstants::NullDate )
    {
       return ErrorState();
    }

    if (  ot->IsDiscountAccount() || ot->IsManualPromotion() || ot->IsFreeConditionOrder() ) // does not affect CO and RO and MP and FC
    {
       return ErrorState();
    }

    // now check what to do, recalculation or not
    doRecalculateOrder = mustDoRecalculateOrder();
    if ( doRecalculateOrder == false )
    {
        return ErrorState();
    }

    int count = CountItems(bCOUNT_ITEMTYPE, (long) pxOrderItem::TypeProductStocked);

    if ( IsGoodState() && count > 0 )
    {
        if (!(isCashOrder() && IsNoDebtLimitCheck()))
        {
            UndoCreditDayTurnOver();
        }
       this->SetNoCreditLimitCheck();                   // Ticket SR-15068713
       nDBBeginTransaction(cDBTransSet);
       pxOrderItemListIter it(*ItemList_);
       pxOrderItem *item;
       while ( ((item = (pxOrderItem*) ++it) != NULL) && IsGoodState() )
       {
          if ( item->IsProductStocked() && !item->IsCancelled())
          {
             if ( item->IsSperreRabattManuell() )
             {
                 continue;
             }
             // Check Defekt (INC-044072)
             if (item->MengeBestaetigt() == 0 && item->MengeGeliefert() == 0 && item->MengeAbgebucht() == 0 )
             {
                 continue;
             }
             // Check Defekt (INC-044072)

             // Check Targetpromotion
             if ( item->IsArticleDiscountPromotion() )
             {
                item->SetPromoTyp((short)0);
             }
             item->SetDiscountValPctMan(item->GetDiscountValPctMan());
             item->RollBackOrderPosition();
             if ( IsGoodState() )
             {
                item->OrderQuantity( item->MengeBestellt(),0,item->MengeBestellt() );
             }
             Error() = item->Error();
          }
       }

       if ( IsGoodState() )
       {
          ReCalcValues();
       }
    }
    return ErrorState();
}
