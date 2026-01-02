/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
the main purpose of this methode is to collect
discountgroupmembers.

REVISION HISTORY

23 Feb 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxrange.hpp"
#include "pxrangemember.hpp"
#include "pxrangecollect.hpp"
#include "pxarticlegroup.hpp"
#include "pxdiscount.hpp"


/*----------------------------------------------------------------------------*/
/*  CollectRangeMember: first look for an rangememberentry on the database    */
/*  If available, insert this entry corresponding to an existing              */
/*  rangepharmagroup entry into orders RangeCollectList                       */
/*----------------------------------------------------------------------------*/
int
pxOrderItem::CollectRangeMember
(
)
{
	pxRangeMemberList*  rml = NULL;
	pxRangeMember*      rm = NULL;
	pxDiscountList*     discl = NULL;
	pxDiscount*         discp = NULL;
	pxCustBase&         customer = *(Order().Customer()); // customer
	pxRangeCollect*     rc = NULL;
	pxRange*            Rangep = NULL;
	short               VZ = customer.Vertriebszentrum(); // customers Branchno
	long                Qty = 0;
	long                QtyPack = 0;
	pxArticleGroupList* ArtGrpList = NULL;
	pxArticleGroup*     ArtGrpEntry = NULL;
	long                ArtCategoryNo = 0;
	double              cInvoiceValue;
	double              cNaturalRebateValue;

    if (!ArtBase() || !ArtBase()->IsGoodState())
        return ErrorState();

    if (PromoTyp_ > 0)                  // belongs to an allready booked Promotion
        return ErrorState();

    // set qty depend param.SrangeCalcBase(CR-14A034)
    if (Order().Param()->IsSRangeCalcBaseQtyConfirmed())
    {
        if (MengeBestaetigt_ == 0)
        {
            return ErrorState();
        }
        Qty = MengeBestaetigt_;
    }
    else
    {
        Qty = ((MengeBestaetigt_ > MengeBestellt_) ? MengeBestaetigt_ : MengeBestellt_);
    }

    cInvoiceValue = calculateInvoiceValue();
    cNaturalRebateValue = calculateNaturalRebateValue();

    rml = new  pxRangeMemberList(Session());
    if (ArtBase()->IsRangeMember())     // just if Artikel = rangemember
    {
        rml->Select(VZ, ArtikelNr_);        // select discountgroupmember
        pxRangeMemberListIter cursor(*rml);     // define an iterator
        while ((rm = (pxRangeMember*) ++cursor) != NULL)
        {
            // Check DiscountGrp, just to prevent unpredictable results(Serbia)
            if (Session()->isSerbia() || Session()->isBulgaria())
            {
                Rangep = new pxRange(Session(), VZ, rm->DiscountGrpNo());
                if (Rangep->Get(cDBGET_READONLY))
                {
                    delete Rangep;
                    Rangep = NULL;
                    continue;
                }
                else
                    //           if ( Rangep->IsGroupOfArticle() )
                    if (!Rangep->IsRange())
                    {
                        delete Rangep;
                        Rangep = NULL;
                        continue;
                    }
            }
            if (ArtBase()->STDMenge() > 0 && ArtBase()->IsRoundUpToSTDQty())
            {
                QtyPack = Qty / ArtBase()->STDMenge();
            }
            ArtGrpList = new pxArticleGroupList(Session());
            ArtGrpList->Select(ArtikelNr_);
            if (ArtGrpList->Entries())
            {
                ArtGrpEntry = (pxArticleGroup*)ArtGrpList->At(0);
                ArtCategoryNo = ArtGrpEntry->ArtCategoryNo();
            }
            delete ArtGrpList;

            rc = new pxRangeCollect(VZ, rm->DiscountGrpNo(), PosNr_, ArtikelNr_, Qty, QtyPack,
                rm->ManufacturerNo(), (double)ShipValue(), ArtCategoryNo, PreisTyp_);
            rc->SetInvoiceValue(cInvoiceValue);
            rc->SetNaturalRebateValue(cNaturalRebateValue);
            Order().RangeCollectList()->InsertAscending(rc);
            if (Rangep)
            {
                delete Rangep;
                Rangep = NULL;
            }
        }
    }

    rml->SelectManuFacturer(VZ, ArtBase()->HerstellerNr());   // select discountgroupmember via ManufacturerNo
    pxRangeMemberListIter cursor(*rml);     // define an iterator
    while ((rm = (pxRangeMember*) ++cursor) != NULL)
    {
        // Check DiscountGrp, just to prevent unpredictable results(Serbia)
        if (Session()->isSerbia() || Session()->isBulgaria())
        {
            Rangep = new pxRange(Session(), VZ, rm->DiscountGrpNo());
            if (Rangep->Get(cDBGET_READONLY))
            {
                delete Rangep;
                Rangep = NULL;
                continue;
            }
            else
                //          if ( Rangep->IsGroupOfArticle() )
                if (!Rangep->IsRange())
                {
                    delete Rangep;
                    Rangep = NULL;
                    continue;
                }
        }
        if (ArtBase()->STDMenge() > 0 && ArtBase()->IsRoundUpToSTDQty())
        {
            QtyPack = Qty / ArtBase()->STDMenge();
        }
        ArtGrpList = new pxArticleGroupList(Session());
        ArtGrpList->Select(ArtikelNr_);
        if (ArtGrpList->Entries())
        {
            ArtGrpEntry = (pxArticleGroup*)ArtGrpList->At(0);
            ArtCategoryNo = ArtGrpEntry->ArtCategoryNo();
        }
        delete ArtGrpList;

        rc = new pxRangeCollect(VZ, rm->DiscountGrpNo(), PosNr_, ArtikelNr_, Qty, QtyPack,
            rm->ManufacturerNo(), (double)ShipValue(), ArtCategoryNo, PreisTyp_);
        rc->SetInvoiceValue(cInvoiceValue);
        rc->SetNaturalRebateValue(cNaturalRebateValue);
        Order().RangeCollectList()->InsertAscending(rc);
        if (Rangep)
        {
            delete Rangep;
            Rangep = NULL;
        }
    }
    delete rml;

    // For HR CPR-250101: select from discount
    if (Session()->isCroatia()) 
    {
        discl = new pxDiscountList(Session());
        discl->Select(21, VZ, ArtikelNr_, customer.IDFNr());

        pxDiscountListIter cursor(*discl);
        while ((discp = (pxDiscount*) ++cursor) != NULL)
        {
            if (ArtBase()->STDMenge() > 0 && ArtBase()->IsRoundUpToSTDQty())
                QtyPack = Qty / ArtBase()->STDMenge();

            rc = new pxRangeCollect(VZ, discp->DiscountGrpNo(), PosNr_, ArtikelNr_, Qty, QtyPack,
                                    discp->ManufacturerNo(), (double)ShipValue(), ArtCategoryNo, PreisTyp_);
            rc->SetInvoiceValue(cInvoiceValue);
            rc->SetNaturalRebateValue(cNaturalRebateValue);
            Order().RangeCollectList()->InsertAscending(rc);
            break; // insert only one record
        }
        delete discl;
    }
	return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  CollectTargetPromoMembers: first look for an Targetmemberentry on the     */
/*  database                                                                  */
/*  If available, insert this entry into orders RangeCollectList              */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CollectTargetPromoMembers
(
)
{
    pxRangeMemberList* rml        = NULL;
    pxRangeMember*     rm         = NULL;
    pxCustBase&       customer    = *(Order().Customer());       // customer
    pxRangeCollect*    rc         = NULL;
    short             VZ         = customer.Vertriebszentrum(); // customers Branchno
    long              Qty        = 0;
    long              QtyPack    = 0;
    long ArtCategoryNo           = 0;


/*----------------------------------------------------------------------------*/
/*  do some sanity checks                                                     */
/*----------------------------------------------------------------------------*/
	if ( !ArtBase() || !ArtBase()->IsGoodState() )
       return ErrorState();

    if ( MengeBestaetigt_ == 0)             // just if MengeGeliefert > 0
       return ErrorState();

    if ( PromoTyp_ > 0 )                    // belongs to an allready booked Promotion
       return ErrorState();

   // if (!ArtBase()->IsRangeMember() )       // just if Artikel = rangemember
   //    return ErrorState();

    // set qty depend param.SrangeCalcBase(CR-14A034)
    if (Order().Param()->IsSRangeCalcBaseQtyConfirmed() )
    {
       Qty =  MengeBestaetigt_;
    }
    else
    {
       Qty =  MengeBestellt_;
    }

    rml = new  pxRangeMemberList(Session());
    rml->Select(  VZ, ArtikelNr_, ArtBase()->HerstellerNr());    // select discountgroupmember
    pxRangeMemberListIter cursor(*rml);     // define an iterator
    while ( (rm = (pxRangeMember*) ++cursor) != NULL )
    {
       if ( ArtBase()->STDMenge() > 0 && ArtBase()->IsRoundUpToSTDQty())
       {
          QtyPack = Qty/ArtBase()->STDMenge();
       }
       rc = new pxRangeCollect(VZ,rm->DiscountGrpNo(),PosNr_,ArtikelNr_,Qty,QtyPack,
                               rm->ManufacturerNo(),(double)WertBrutto(), ArtCategoryNo, PreisTyp_);
       Order().RangeCollectList()->InsertAscending(rc);
    }
    delete rml;
    return ErrorState();
}
