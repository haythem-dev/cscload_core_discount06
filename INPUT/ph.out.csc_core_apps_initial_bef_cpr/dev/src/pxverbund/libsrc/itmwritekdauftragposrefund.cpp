/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
 write kdauftragposrefund depend on entries within table discount.

REVISION HISTORY

25 Sep 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxkdauftragposrefund.hpp"
#include "pxartprc.hpp"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/* WriteKdAuftragPosRefund:                                                   */
/* At the moment just for the Swiss apllication                               */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: WriteKdAuftragPosRefund
(
    long OrderNo,
    long PosNo,
    double RefundValue,
    double RefundPct,
    long QtyToBeDelivered,  // shall always be calculated on basis=1
    short RefundSrc,
    short PromotionNo
)
{

    double TotalRefundValue(0.0);

    if (!Session()->isSwitzerland())
       return ErrorState();

    if(this->ProFormaBooking_)
       return ErrorState();

    if( RefundPct>0 )
    {
       TotalRefundValue=CalculateRefundValue(RefundPct);
    }
    else
    {
       TotalRefundValue=QtyToBeDelivered*RefundValue;
    }

    pxKdAuftragPosRefund* refund=NULL;

    if (KdAuftragPosRefundList())
    {
       refund=new pxKdAuftragPosRefund(Session(), OrderNo, PosNo, TotalRefundValue, RefundSrc, PromotionNo);
       refund->Put();
       //append to list, if it's needed anywhere else:
       KdAuftragPosRefundList()->Append(refund);
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* Descr:   Calculates refund value out of refund pct.                        */
/*          Refund value is based on GEP or GEPNA or AGP, depend in which     */
/*          country we are.                                                   */
/*                                                                            */
/*          Calculate difference between GEP/GEPNA/AGP and PreisFaktur        */
/*          This is the baseValue for caculation                              */
/*          If the difference is zeroe, then NR was maybe given               */
/*          At the moment, I have no information how to handle this case      */
/* Param:   refund pct                                                        */
/*                                                                            */
/* Returns: refund value                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
double pxOrderItem :: CalculateRefundValue
(
    double RefundPct
)
{
    double RefundValue(0.0);            // help variable
    nMoney basePrice =  0.0;
    nMoney Gep       = ArtPriceList()->GetPreisEKGrosso();
    nMoney Agp       = ArtPriceList()->GetPreisAGP();
    nMoney baseValue =  0.0;
    double RebatePct = GetDiscountValuePct();
    nMoney invoicePrice = 0.0;

    if (Session()->isSwitzerland())
    {
       basePrice = Gep;
       if ( !basePrice  )
       {
          basePrice = Agp;
       }
    }

    if ( basePrice == pxConstants::mZero )
    {
       return RefundValue;
    }

    invoicePrice =  basePrice - ((basePrice*RebatePct)/100.0);     // mathematical calculation;
    baseValue = basePrice - invoicePrice;
    if ( baseValue == pxConstants::mZero )
    {
       return RefundValue;
    }
    RefundValue = RefundPct;
    RefundValue = RefundValue * (double)baseValue;
    RefundValue = RefundValue / 100.0;

    return RefundValue;
}
