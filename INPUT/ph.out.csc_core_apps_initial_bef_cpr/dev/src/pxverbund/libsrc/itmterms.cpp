/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Class pxOrderItem:
Fix terms and conditions for a stocked product.

REVISION HISTORY

24 May 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxcsterm.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"

long
pxOrderItem :: CalcTermsOnEntry
(
    long QToPost,                      // quantity to post
    long QInStock                      // quantity currently available in stock
)
{
    pxCustBase&       customer    = *(Order().Customer());
    pxCustTerms&      cterms      = customer.Terms();
    pxArtBase&        artbase     = *ArtBase();
    const pxOrderType& ordertype  = Order().OrderType();

    long             parkq       = 0;
    long        deltaroundqty    = 0;
    RabattFestDM_     = pxConstants::mZero;
    long orderq      = QToPost;
    long qdiscount   = 0;

    // set qdiscount depend param.SDiscountCalcBase(CR-14A034)
    if ( Order().Param()->IsSDiscountCalcBaseQtyConfirmed() )
    {
       qdiscount = QToPost;
    }
    else
    {
       qdiscount = MengeBestellt_;
    }

    // just for the french application collectiv orders ordertype "CV"
    // KoArt_ and BuchArt_ must be 22, otherwise no discount calculation
    if ( ordertype.IsCollectiveOrder() )
    {
       if (!( Order().IsCollectiveOrderDiscountable() ) )
       {
          return orderq;
       }
    }

    // changed coding outside rebate condition logic
    if ( artbase.STDMenge() > 0 && artbase.IsRoundUpToSTDQty() )
    {
        deltaroundqty  = artbase.STDMenge() - (orderq%artbase.STDMenge());
        orderq += deltaroundqty;
        if (QInStock < orderq)
           orderq -= deltaroundqty;    // but this is not available in stock
    }
    else
    if ( !Order().Param()->IsRoundPackageUnit())
    {
       long packq = artbase.VerkaufEinheit(); // quantity in package unit
       // special
       if ( Session()->isFrance() || Session()->isFrancePrewhole() )
       {
          packq = artbase.ContainerGroesse();
       }

       long percentage = (long)(cterms.BuendelRundungProz() * 10);
       if (packq > 0 && percentage > 0 )
       {                                // then calc delta to package unit
          long deltaq = packq - (orderq % packq);
          if ( ( deltaq < packq )       // respect customer's limit:
               && deltaq <= ((packq * percentage + 500) / 1000) )
          {
             orderq += deltaq;       // raise order quantity to fit package size
             if (QInStock < orderq)
                orderq -= deltaq;    // but this is not available in stock
          }
       }
    }
    else
    {
       parkq  = CheckPackageUnit( QToPost,QInStock);
       if ( !(parkq < 0 ) )
          orderq = parkq;
    }
/*-------------------------------------------------------------------------*/
/*   Discountcalculation System using the common discount table            */
/*-------------------------------------------------------------------------*/
    // this is a very very French/Serbian speciality
    if ( PreisEKApoFree_ != pxConstants::mZero && (Session()->isFrance() || Session()->isFrancePrewhole()) )
    {
       RabattFestDM_ = ( PreisEKApo_ > PreisEKApoFree_ ) ? (PreisEKApo_ - PreisEKApoFree_) :
                                                          (-(PreisEKApoFree_ - PreisEKApo_));
       return orderq;
    }
    if ( PreisEKApoFree_ != pxConstants::mZero && Session()->isSerbia() )
    {
       RabattFestDM_ = ( PreisEKApo_ > PreisEKApoFree_ ) ? (PreisEKApo_ - PreisEKApoFree_) :
                                                          (-(PreisEKApoFree_ - PreisEKApo_));
       SetFreierPreis();
       return orderq;
    }

    // Do not calculate rebates for new suivra orders
    if (Session()->isFrance())
    {
       if ( Order().BatchSchreiben() == cORTYPE_AUXILIARY )
       {
          return orderq;
       }
    }

    // Tender rebate logic
    // TODO is this the right place?
    // TODO Really return here?
    if (CalcTenderDiscount())
    {
        if (orderq > QToPost)
            SetMengenErhoehung();
        return orderq;
    }

    // rebate logic
    if ( customer.CustomerGroupFlagsList()->IsKscDiscountEnabled() && ordertype.IsDiscountable() )
    {
/*----------------------------------------------------------------------------*/
/*  Product package unit alignment algorithm.                                 */
/*  For products packed in boxes and/or containers (wines, mineral waters     */
/*  etc.), we try to raise the order quantity until the product package unit  */
/*  is met. However, order quantity raising is limited by a rounding          */
/*  percentage set in the customer's terms.                                   */
/*----------------------------------------------------------------------------*/
        // Impementation Swiss Overdrive
        orderq = OverDriveCondition(orderq, QInStock);
        if ( orderq > QToPost && orderq > qdiscount )
        {
           orderq = CalcDiscount(orderq, QInStock);         // with raised quantity
        }
        else
        {
           qdiscount = CalcDiscount( qdiscount, QInStock);  // with quantity ordered
           if( Session()->isSwitzerland() )
           {
               if( orderq > qdiscount )
               {
                  orderq = qdiscount;
               }
           }
        }
        if ( !IsGoodState() )
        {
            return ErrorState();
        }
        // this is a very very French/Serbian speciality
        if ( PreisEKApoFree_ != pxConstants::mZero && (Session()->isFrance() || Session()->isFrancePrewhole()) )
        {
           RabattFestDM_ = ( PreisEKApo_ > PreisEKApoNetto_ ) ? (PreisEKApo_ - PreisEKApoNetto_) :
                                                               (-(PreisEKApoNetto_ - PreisEKApo_));
        }
        if ( PreisEKApoFree_ != pxConstants::mZero && Session()->isSerbia() )
        {
           RabattFestDM_ = ( PreisEKApo_ > PreisEKApoFree_ ) ? (PreisEKApo_ - PreisEKApoFree_) :
                                                              (-(PreisEKApoFree_ - PreisEKApo_));
           SetFreierPreis();
        }
        if ( FixedPricePaymentterms_ != pxConstants::mZero && Session()->isSerbia() )
        {
           RabattFestDM_ = ( PreisEKApo_ > FixedPricePaymentterms_ ) ? (PreisEKApo_ - FixedPricePaymentterms_) :
                                                              (-(FixedPricePaymentterms_ - PreisEKApo_));
        }
        if (orderq > QToPost)
           SetMengenErhoehung();
        return orderq;
    }
    return orderq;
}

/*----------------------------------------------------------------------------*/
/*  CalcConditions: this function calculates all special conditions depend    */
/*  on defined customer and article conditions                                */
/*  The resuls, depend on quantity ordered, are directly stored within this   */
/*  item.                                                                     */
/*  This public fuction has been  build for external use.                     */
/*----------------------------------------------------------------------------*/
long
pxOrderItem :: CalcConditions
(
)
{
    long qdiscount   = 0;
    qdiscount = CalcDiscount( MengeBestellt_);
    if (MengeGeliefert_  == 0 )
    {
       UndoItemDiscount();
    }
    return qdiscount;
 }
