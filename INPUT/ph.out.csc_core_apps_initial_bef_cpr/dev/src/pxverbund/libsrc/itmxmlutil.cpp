/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Implementation of oveloaded order item entry methods.

REVISION HISTORY

30 March 2007 V1.00 REV 00 written by Ysbrand Bouma
*/

#include "pxitem.hpp"
#include "pxdiscountdef.h"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustbaseinformation.hpp"
#include "pxartbas.hpp"
#include "pxorder.hpp"
#include "pxarticleinfo.hpp"
#include "pxitemdiscount.hpp"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/*  ArticleInfoRequest; this methode is used in XML Applications              */
/*----------------------------------------------------------------------------*/
pxArticleInfo*
pxOrderItem :: ArticleInfoRequest
(
   const long      ArticleNo,
   const long      Qty
)
{
    pxCustBase* customer = Order().Customer();
    nString Sprache;
    Sprache.Clear();
    Sprache = "DE";
    if (Session()->isSwitzerland())
    {
       Sprache = customer->Sprache();
    }
    short BranchNo = customer->Vertriebszentrum();
    pxArticleInfo* ArtInfo = NULL;         // return object for the caller
    if ( ArticleNo > 0 )
    {
       ArtInfo = new pxArticleInfo(Session(), BranchNo, ArticleNo, Qty );
       ArtInfo->Build(Sprache);
       if (!ArtInfo->IsGoodState() )
       {
          delete ArtInfo;
          ArtInfo = NULL;
       }
    }
    return ArtInfo;
}

/*----------------------------------------------------------------------------*/
/*  GetLegallBreizhPrice; for Legall/Breizh customer (french application) and */
/*  Legall/Breizh article: if there is a calculated fixprice and if there is  */
/*  logistic addoncharge, this methode returns a nMoney object following the  */
/*  rule:                                                                     */
/*  Returnvalue = FixedPrice * (1+(LogisticAddOn%/100).In all other case, this*/
/*  nullmoney = 0.0                                                           */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: GetLegallBreizhPrice
(
)
{
    nMoney retval = 0.0;             // return Value
    pxCustBase&       customer   = *(Order().Customer());
	if(ArtBase() == NULL || !ArtBase()->IsGoodState())
       return retval;
    pxArtBase&        artbase    = *ArtBase();
    // unused variable
    /* pxArtClass&       artclass   = */ artbase.ArtClass();
    pxItemDiscount   *entryp = NULL;

    if (!Session()->isFrance())
       return retval;
    if ( !customer.ArtClass().IsLegallLinkage() && !customer.ArtClass().IsBreizhLinkage())
       return retval;

	if ( ArtBase() && ArtBase()->IsGoodState() )
    {
       if ( PreisEKApoNetto_ == pxConstants::mZero )
          return retval;
       if ( ItemDiscountList()->Entries() == 0 )
          return retval;
       if ( (entryp = ItemDiscountList()->Find( BestBuy_LogisticAddition )) == NULL )
          return retval;
       if ( entryp->DiscountValuePct() == 0.0)
          return retval;
       retval = PreisEKApoNetto_ * (1+(entryp->DiscountValuePct()/100) );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetLogisticAddition: this methode searches within the ItemDiscountList    */
/*  for an entry of type logisticaddition. On a valid entry,the percentage    */
/*  value of this entry will be returned, otherwise returnvakue = 0.0         */
/*----------------------------------------------------------------------------*/
double
pxOrderItem :: GetLogisticAddition
(
)
{
    pxCustBase&       customer   = *(Order().Customer());
    double  retval = pxConstants::dZero;
    pxItemDiscount* dentry = ItemDiscountList()->Find((int)BestBuy_LogisticAddition);
    if (dentry)
    {
        retval =dentry->DiscountValuePct();
        return retval;
    }
    if ( retval == pxConstants::dZero )
    {
       if ( customer.CustBaseInformation() )
       {
          retval = customer.CustBaseInformation()->LogistikAufschlag();
       }
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  BasePrice : Special Price for the Swiss Application  (kscserver)          */
/*----------------------------------------------------------------------------*/
nMoney
pxOrderItem :: BasePrice
(
)
{
    nMoney BasePrice = 0.0;          // return Value
    pxCustBase&       customer   = *(Order().Customer());
    char  PreisLevel = customer.XMLPreisLevel();
    double  percentage;

    if(ArtBase() == NULL || !ArtBase()->IsGoodState())
       return BasePrice;

    if ( ArtPrice_ == NULL )
       return BasePrice;

    if ( PreisAGP() != pxConstants::mZero )
    {
       BasePrice = PreisAGP();
    }
    else
    {
       BasePrice = PreisEKGrosso();
    }
    if ( PreisLevel >= '2' ) // == DB: Kunde.XMLPeisLevel (char)
    {
        pxItemDiscount* dentry = ItemDiscountList()->Find((int)BestBuy_ValuePctCash);
       if (dentry)
       {
          percentage = dentry->DiscountValuePct(); // == DB: KDAuftragPosRab.DiscountValuePct where DiscountType = 7 (BestBuy_ValuePctCash) AND KdAuftragNr_ AND PosNr_
          if ( BasePrice != pxConstants::mZero )
          {
              // CH-BarRabattlogik: BasePrice = AGP - (Rabattwert auf Basis GEP)
             BasePrice = BasePrice - (PreisEKGrosso() * (percentage / 100));
          }
       }
    }
    return BasePrice;
}
