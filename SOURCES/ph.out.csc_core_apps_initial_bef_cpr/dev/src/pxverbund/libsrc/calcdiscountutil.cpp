#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxcustpharmgroup.hpp"
#include "pxcalcdiscount.hpp"
#include "pxdiscount.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxcstbas.hpp"
#include "pxarticlegroup.hpp"
/*----------------------------------------------------------------------------*/
/*  ShrinkMultipleEntries: delete equal entries from this list                */
/*  Please take care for a well contructed pxCalcDiscountList object          */
/*----------------------------------------------------------------------------*/
size_t
pxCalcDiscountList :: ShrinkMultipleEntries
(
)
{
    pxCalcDiscount *calcp;
    pxCalcDiscountListIter calcit(*this);
    short cDiscountBestBuy = 0;
    short cPaymentTargetNo = 0;


    while ( (calcp = (pxCalcDiscount*) ++calcit) != NULL )
    {
       if (  calcp->DiscountBestBuy() > 0 && cDiscountBestBuy == 0 )       // first entry
       {
          cDiscountBestBuy = calcp->DiscountBestBuy();
          cPaymentTargetNo = calcp->PaymentTargetNo();
          continue;
       }
       if ( cDiscountBestBuy == calcp->DiscountBestBuy() && cPaymentTargetNo == calcp->PaymentTargetNo() )
       {
          delete calcit.Remove();
          continue;
       }
       else
       {
          cDiscountBestBuy = calcp->DiscountBestBuy();
          cPaymentTargetNo = calcp->PaymentTargetNo();
       }
    }
    return this->Entries();
}
