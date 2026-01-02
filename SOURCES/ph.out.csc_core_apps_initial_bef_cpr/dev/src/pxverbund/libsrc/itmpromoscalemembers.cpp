/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
the main purpose of this methode is to collect
discountgroupmembers.

REVISION HISTORY

26 March 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxrangecollect.hpp"
#include "pxpromotionscale.hpp"


/*----------------------------------------------------------------------------*/
/*  CollectPromotionScaleMembers:first look for a promotion number of this    */
/*  item. If available, do a read from table promotionscale via this          */
/*  promotionnumber. After that do a select on table promotionscale with      */
/*  BasePromotionno from this entry and add an entry into the                 */
/*  RangeCollectList                                                          */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CollectPromotionScaleMembers
(
)
{
    pxCustBase&       customer    = *(Order().Customer());       // customer
    pxPromotionScale* PromoScaleEntry  = NULL;
    pxPromotionScaleList* PromoScaleList = NULL;

    pxRangeCollect*    rc         = NULL;
    short             VZ         = customer.Vertriebszentrum(); // customers Branchno
    long              Qty        = 0;
    long              QtyPack    = 0;

    if ( !ArtBase() || !ArtBase()->IsGoodState() )
       return ErrorState();

    if ( MengeBestaetigt_ == 0)            // just if MengeGeliefert > 0
       return ErrorState();

    if (PromotionNo_ == 0 )
       return ErrorState();

    // now read entry from promotionscale
    PromoScaleList = new pxPromotionScaleList(Session());
    PromoScaleList->Select( PromotionNo_);
    if ( PromoScaleList->Entries() )
    {
       PromoScaleEntry = (pxPromotionScale*)PromoScaleList->At(0);
    }
    else
    {
       delete PromoScaleList;
       return ErrorState();
    }

    // now select  promotionscale with BasePromotion from PromoScaleEntry
    PromoScaleList->Select( PromoScaleEntry->BasePromotion());
    if (  PromoScaleList->Entries() == 0 )
    {
       delete PromoScaleList;
       delete PromoScaleEntry;
       return ErrorState();
    }

    // now add entry to RangeCollectList for each PromoScaleList entry
    pxPromotionScaleListIter cursor(*PromoScaleList);                        // define an iterator

    while ( (PromoScaleEntry = (pxPromotionScale*) ++cursor) != NULL ) // browse promotionscale list
    {
       Qty =  MengeBestaetigt_;
       if ( ArtBase()->STDMenge() > 0 && ArtBase()->IsRoundUpToSTDQty())
       {
          QtyPack = Qty/ArtBase()->STDMenge();
       }

       rc = new pxRangeCollect(VZ,PromoScaleEntry->PromotionNo(),PosNr_,ArtikelNr_,Qty,QtyPack,
                              ArtBase()->HerstellerNr(),(double)WertBrutto(), 0, PreisTyp_);
       Order().RangeCollectList()->InsertAscending(rc);
    }
    delete PromoScaleList;
    return ErrorState();
}
