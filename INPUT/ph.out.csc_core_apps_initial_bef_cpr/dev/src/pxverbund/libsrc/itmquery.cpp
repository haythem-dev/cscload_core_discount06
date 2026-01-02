#include "pxitem.hpp"
#include "pxdiscountdef.h"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxartprc.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcstbas.hpp"
#include "pxcstprint.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxcstot.hpp"
#include "pxorderposcalcmode.hpp"
#include "pxkdauftragposrefund.hpp"
#include "tourassignmentutil.hpp"
#include "pxarticlequota.hpp"
#include "pxorderremarks.hpp"
#include "pxpromotioncollect.hpp"
#include "pxorderpospromo.hpp"
#include "pxtenderpos.hpp"
#include "pxitemdiscount.hpp"
#include "pxrangemember.hpp"
#include "articlesubstitutionutil.hpp"
#include "pxvartikellokallist.hpp"
#include <discount/orderpositiondiscount/iorderpositiondiscountfinder.h>
#include <discount/orderpositiondiscount/orderpositiondiscount.h>
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"
#include <boost/numeric/conversion/cast.hpp>
#include <ibt/ibtrequest/iibtrequest.h>
#include <ibt/ibtrequest/iibtrequestrepository.h>

bool pxOrderItem::hasArticleQuota()
{
    return (NULL == ArtQuota()) ? false : true;
}

/*----------------------------------------------------------------------------*/
/*  ArticleQuota                                                              */
/*  This function returns a pxArticleQuota pointer or NULL.                   */
/*----------------------------------------------------------------------------*/
pxArticleQuota*
pxOrderItem :: ArtQuota
(
    DBAccessMode mode
)
{
    ///////////////////////////////////////////////////////////////////////////////
    // logical & technical preconditions
    ///////////////////////////////////////////////////////////////////////////////
    if( Order().OrderType().IsNoQuota() )
    {
        return  m_ArticleQuota.get();
    }
    if( NULL != m_ArticleQuota.get() )
    {
        return m_ArticleQuota.get();
    }
    if( m_ArticleQuota.isSearchRegistered() )
    {
        return m_ArticleQuota.get();
    }

    ///////////////////////////////////////////////////////////////////////////////
    // Loading ArticleQuota
    ///////////////////////////////////////////////////////////////////////////////
    pxCustBase* customer = Order().Customer();
    const short branchNo = (0 == customer->OriginalFilialNr() ? customer->Vertriebszentrum() : customer->OriginalFilialNr());

    pxArticleQuotaList artQuotaList( Session() );
    artQuotaList.SelectOriginal(branchNo, customer->IDFNr(), ArtikelNr_);
    if (artQuotaList.Entries())
    {
        pxArticleQuota* artQuota = NULL;
        pxArticleQuotaListIter it( artQuotaList );
        while( (artQuota =(pxArticleQuota*)++it) != NULL)
        {
            /*ArtQuota_ = new pxArticleQuota(*artQuota);
            ArtQuota_->Get(mode);*/

            m_ArticleQuota.create(artQuota);
            m_ArticleQuota.get()->Get(mode);
            break;
        }
    }
    else if( false == customer->CustomerGroupFlagsList()->isGroupNoQuotaInheritance() )
    {
        ///////////////////////////////////////////////////////////////////////////////
        // Loading ArticleQuota (basic entry)
        ///////////////////////////////////////////////////////////////////////////////
        artQuotaList.SelectBasic( branchNo, ArtikelNr_ );
        if( artQuotaList.Entries() )
        {
            pxArticleQuota* artQuota = NULL;
            pxArticleQuota* newpxArticleQuota = NULL;
            pxArticleQuotaListIter it(artQuotaList);
            while( (artQuota = (pxArticleQuota*)++it) != NULL)
            {
                newpxArticleQuota = new pxArticleQuota(*artQuota);
                newpxArticleQuota->SetCustomerNo( customer->IDFNr() );
                newpxArticleQuota->Put(); // BB: put?
                if (newpxArticleQuota->IsGoodState())
                {
                    /*ArtQuota_ = newpxArticleQuota;
                    ArtQuota_->Get(mode);*/
                    m_ArticleQuota.set(newpxArticleQuota);
                    m_ArticleQuota.get()->Get(mode);
                }
                break;
            }
        }
    }

    m_ArticleQuota.registerSearch();
    return m_ArticleQuota.get();
}

/*----------------------------------------------------------------------------*/
/*  pxItemDiscountList                                                        */
/*  This function returns a pxItemDiscountList pointer or a NULLP             */
/*----------------------------------------------------------------------------*/
pxItemDiscountList*
pxOrderItem :: ItemDiscountList
(
)
{

    if ( !ItemDiscountList_ )
    {
       ItemDiscountList_ = new pxItemDiscountList(Session());
       ItemDiscountList_->Select(KdAuftragNr_,PosNr_);
    }

    return ItemDiscountList_;
}


/*----------------------------------------------------------------------------*/
/*  pxKdAuftragPosRefundList                                                  */
/*  This function returns a pxKdAuftragPosRefundList pointer or a NULLP       */
/*----------------------------------------------------------------------------*/
pxKdAuftragPosRefundList*
pxOrderItem :: KdAuftragPosRefundList
(
)
{
    if ( !KdAuftragPosRefundList_ )
    {
       KdAuftragPosRefundList_ = new pxKdAuftragPosRefundList(Session());
       KdAuftragPosRefundList_->Select(KdAuftragNr_,PosNr_);
    }

    return KdAuftragPosRefundList_;
}

/*----------------------------------------------------------------------------*/
/*  IsOrderParamArticle:                                                      */
/*----------------------------------------------------------------------------*/
bool
pxOrderItem :: IsOrderParamArticle
(
)
{
    return  ( ArtikelNr_ == Order().Param()->PZNKuehlBox1()  ) ||
            ( ArtikelNr_ == Order().Param()->PZNKuehlBox2()  ) ||
            ( ArtikelNr_ == Order().Param()->PZNWerbefach()  ) ||
            ( ArtikelNr_ == Order().Param()->PZNWerbefach2() ) ||
            ( ArtikelNr_ == Order().Param()->PZNBTMSchein()  ) ||
            ( ArtikelNr_ == Order().Param()->PZNZytostatika());
}

/*----------------------------------------------------------------------------*/
/*  ArtPriceList                                                              */
/*  This function returns a pxArtPriceList pointer or a NULLP                 */
/*----------------------------------------------------------------------------*/
pxArtPriceList*
pxOrderItem :: ArtPriceList
(
)
{
    if ( !ArtPriceList_ )
    {
       ArtPriceList_ = new pxArtPriceList(Session());
       ArtPriceList_->Select(ArtikelNr_);
       ArtPriceList_->DeleteExpired();       // remove expired prices, so only
    }                                        // guilty entries stay in the list
    return ArtPriceList_;
}
/*----------------------------------------------------------------------------*/
/*  GetDiscountValuePct                                                      */
/*  This function gets the discountvaluepct from this item kdauftragposrab    */
/*  entry                                                                     */
/*----------------------------------------------------------------------------*/
double
pxOrderItem :: GetDiscountValuePct
(
)
{
    if (Order().Param()->IsUseNewDiscountCalc())
    {
        basar::Decimal retval = basar::Decimal(0.0);
        libcsc::discount::OrderPositionDiscountListPtr l = getDiscountList();
        libcsc::discount::OrderPositionDiscountList::const_iterator it = l->begin();
        while (it != l->end())
        {
            if (true == (*it)->isDiscountValid())
            {
                if (true == (*it)->isDiscountValuePercent())
                {
                    retval += (*it)->getDiscountPercent().get();
                }
            }
            ++it;
        }
        return retval.toFloat64();
    }

    double retval = 0.0;
    pxItemDiscount* dentry = ItemDiscountList()->FindDiscountValuePct();

    if (dentry)
    {
       if ( dentry->DiscountValPctMan() != pxConstants::dZero )
       {
          retval = dentry->DiscountValPctMan();
       }
       else
       {
          retval = dentry->DiscountValuePct();
       }
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  GetDiscountValPctMan                                                      */
/*  This function gets the discountvalpctman from this item kdauftragposrab   */
/*  entry                                                                     */
/*----------------------------------------------------------------------------*/
double
pxOrderItem :: GetDiscountValPctMan
(
)
{
    double retval = 0.0;
    if (Order().Param()->IsUseNewDiscountCalc())
    {
        return retval;
    }

    pxItemDiscount* dentry = ItemDiscountList()->Find((int)BestBuy_ValuePctCash);
    if (dentry)
    {
        retval = dentry->DiscountValPctMan();
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  GetDiscountValue                                                          */
/*  This function gets the discountvalue from this item orderpositiondiscount */
/*  entry                                                                     */
/*----------------------------------------------------------------------------*/
double
pxOrderItem::getOrderPositionDiscountDiscountValue
(
)
{
    basar::Decimal retval = basar::Decimal(0.0);
    if (Order().Param()->IsUseNewDiscountCalc())
    {
        libcsc::discount::OrderPositionDiscountListPtr l = getDiscountList();
        libcsc::discount::OrderPositionDiscountList::const_iterator it = l->begin();
        while (it != l->end())
        {
            if (true == (*it)->isDiscountValid())
            {
                if (true == (*it)->isDiscountFixedPrice())
                {
                    retval += (*it)->getDiscountValue().get();
                }
            }
            ++it;
        }
    }
    return retval.toFloat64();
}


/*----------------------------------------------------------------------------*/
/*  Return a pointer to the TenderPos Entry, if available  .                  */
/*  This entry is selected by TenderNo, ArticleNo.                            */
/*----------------------------------------------------------------------------*/
pxTenderPos*
pxOrderItem :: TenderPos
(
)
{
    const pxCustOrderType&  ot = Order().OrderType();

    if ( !(ot.IsTenderOrder()) && !(ot.IsTenderInvoice()) )
       return (TenderPos_ = NULL);

    if ( Order().TenderNo() == 0 )
       return (TenderPos_ = NULL);

    if (! TenderPos_ )         // if not selected yet
    {
       TenderPos_ = new pxTenderPos(Session(), Order().TenderNo(), ArtikelNr_);
       if ( TenderPos_->Get(cDBGET_READONLY))
       {
          delete TenderPos_;
          TenderPos_ = NULL;
       }
    }
    return TenderPos_;
}
/*-------------------------------------------------------------------------------------*/
/*  GetMaxAvp : Return pxConstants::mZero if there is no maxavp, otherwise MaxAvp from */
/*  ArtikelPreis will be returned(Bulgarien Application).                              */
/*-------------------------------------------------------------------------------------*/
nMoney
pxOrderItem :: GetMaxAvp
(
)
{
    nMoney retval = pxConstants::mZero;

    if (!Session()->isBulgaria())
       return retval;

    GetBasePrices(PreisTyp_);
    if ( ArtPrice_ )
    {
       retval = ArtPrice_->MaxAvp();
    }
    return retval;
}
/*----------------------------------------------------------------------------------------*/
/*  GetCalcAvp : Return pxConstants::mZero if there is no CalcAvp, otherwise CalcAvp from */
/*  KdAuftrPosRechArt will be returned(Bulgarien Application).                            */
/*----------------------------------------------------------------------------------------*/
nMoney
pxOrderItem :: GetCalcAvp
(
)
{
    nMoney retval = pxConstants::mZero;;
    // unused variable
    // pxOrderPosCalcMode* calcmode = NULL;
    if (!Session()->isBulgaria())
       return retval;

    if ( OrderPosCalcMode() )
    {
       retval = OrderPosCalcMode()->CalcAvp();
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  OrderPosCalcMode:                                                         */
/*  Pointer to KdAuftrPosRechArt will be returned(Bulgarien Application)      */
/*----------------------------------------------------------------------------*/
pxOrderPosCalcMode*
pxOrderItem :: OrderPosCalcMode
(
)
{
    if (!Session()->isBulgaria())
       return OrderPosCalcMode_;

    if ( !OrderPosCalcMode_ )
    {
       OrderPosCalcMode_ = new pxOrderPosCalcMode(Session(), KdAuftragNr_, PosNr_);
       if ( OrderPosCalcMode_->Get())
       {
          delete OrderPosCalcMode_;
          OrderPosCalcMode_ = NULL;;
       }
    }
    return OrderPosCalcMode_;
}

/*----------------------------------------------------------------------------*/
/*  IsArticleListFiveMember: checks ListFive membership depend on             */
/*  customers DiscountGrpMemListFive_ list                                    */
/*----------------------------------------------------------------------------*/
bool
pxOrderItem :: IsArticleListFiveMember
(
)
{
    pxCustBase   *customer  = Order().Customer();  // customer
    pxRangeMemberList* rml  = NULL;

    if (!Session()->isBulgaria())
       return false;

    if ( !IsPriceTypeHealthFund())
       return false;

    rml = customer->DiscountGrpMemListFive();
    if (rml == NULL)
       return false;

    if (ArtBase() && ArtBase()->IsGoodState())
    {
        return rml->Find(ArtikelNr_, ArtBase()->HerstellerNr());
    }
    return false;
}

/*----------------------------------------------------------------------------*/
/*  OrderPosPromo:                                                            */
/*  Pointer to OrderPosPromo(kdauftragpospromo) will be                       */
/*  returned(Bulgarien Application)                                           */
/*----------------------------------------------------------------------------*/
pxOrderPosPromoList*
pxOrderItem :: OrderPosPromoList
(
)
{
    if (!Session()->isBulgaria())
       return OrderPosPromoList_;

    if ( !OrderPosPromoList_ )
    {
       OrderPosPromoList_ = new pxOrderPosPromoList(Session());
       OrderPosPromoList_->Select(KdAuftragNr_, PosNr_);
    }
    return OrderPosPromoList_;
}
/*----------------------------------------------------------------------------*/
/*  WriteOrderPosPromo:                                                       */
/*  Inserts a OrderPosProm object to the Database                             */
/*  (Bulgarien Application)                                                   */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: WriteOrderPosPromo
(
    const nString& PharmacyGroupId,
    long    DiscountGrpNo,
    long    BaseQty,
    double BaseValue,
    long    CustomerNo,
    short   PromotionNo,
    char    InternalDiscount,
    double DiscountValuePct

)
{
    pxOrderPosPromo* PosPromo = NULL;
    if (!Session()->isBulgaria())
       return ErrorState();

    if ( OrderPosPromoList() )
    {
       PosPromo = OrderPosPromoList()->Find( PromotionNo);
       if ( PosPromo == NULL )
       {
          PosPromo = new pxOrderPosPromo(Session(), KdAuftragNr_, PosNr_);
       }
       PosPromo->SetPharmacyGroupId( PharmacyGroupId);
       PosPromo->SetDiscountGrpNo( DiscountGrpNo);
       PosPromo->SetBaseQty(BaseQty);
       PosPromo->SetBaseValue(BaseValue);
       PosPromo->SetCustomerNo(CustomerNo);
       PosPromo->SetPromotionNo(PromotionNo);
       PosPromo->SetInternalDiscount(InternalDiscount);
       PosPromo->SetDiscountValuePct(DiscountValuePct);
      // PosPromo->nDBBeginTransaction(cDBTransRecord);
       PosPromo->Put();
       if ( PosPromo->IsGoodState() )
       {
         // PosPromo->nDBCommit(cDBTransRecord);
          if (!OrderPosPromoList()->Find( PromotionNo) )
          {
             OrderPosPromoList()->Append(PosPromo);
          }
       }

       Error() = PosPromo->Error();
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  GetOrderPosPromo:                                                         */
/*  Returns a pxOrderPosPromo pointer from the OrderPosPromoList              */
/*  (Bulgarien Application)                                                   */
/*----------------------------------------------------------------------------*/
pxOrderPosPromo*
pxOrderItem :: GetOrderPosPromo
(
    const short   PromotionNo
)
{
    pxOrderPosPromo* PosPromo = NULL;
    if (!Session()->isBulgaria())
       return PosPromo;

    if ( OrderPosPromoList() )
    {
       PosPromo = OrderPosPromoList()->Find( PromotionNo);
    }
    return PosPromo;
}
/*----------------------------------------------------------------------------*/
/*  PromoCollectList;Returns pointer to PromoCollectList_                     */
/*----------------------------------------------------------------------------*/
pxPromoCollectList*
pxOrderItem :: PromoCollectList
(
)
{
    if ( !PromoCollectList_ )
        PromoCollectList_ = new pxPromoCollectList();
    return PromoCollectList_;
}

/*----------------------------------------------------------------------------*/
pxGenericOrderRemarkList* pxOrderItem::getGenericOrderRemarks()
{
    if (NULL == GenericOrderRemarkList_)
    {
        GenericOrderRemarkList_ = new pxGenericOrderRemarkList(Session());
    }
    GenericOrderRemarkList_->Clear();
    GenericOrderRemarkList_->SelectOrderRemarksByOrderLine(KdAuftragNr(), PosNr());
    return GenericOrderRemarkList_;
}

/*----------------------------------------------------------------------------*/
ArticleSubstitutionUtil* pxOrderItem::getArticleSubstitutionUtil()
{
    if( NULL == m_ArticleSubstitutionUtil )
    {
        m_ArticleSubstitutionUtil = new ArticleSubstitutionUtil(this);
    }
    return m_ArticleSubstitutionUtil;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  GetPosPromoDiscountValuePct                                               */
/*  This function gets the discountvaluepct from this item kdauftragpospromo  */
/*  entry                                                                     */
/*----------------------------------------------------------------------------*/
double
pxOrderItem :: GetPosPromoDiscountValuePct
(
)
{
    return OrderPosPromoList()->GetDiscountValuePct();
}
/*----------------------------------------------------------------------------*/
/*  CopyItemDiscountList: Looks for ItemDiscount (kdauftragposrab for src)    */
/*  entries. If entries available, so src.Entries are deleted and new entries */
/*  for this item are inserted   .                                            */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CopyItemDiscountList
(
    pxOrderItem* src
)
{
    pxItemDiscount *entriep = NULL;
    pxItemDiscount *newentriep = NULL;

    pxItemDiscountList* srcdlist = src->ItemDiscountList();
    if (srcdlist)
    {
       pxItemDiscountListIter  cursor(*srcdlist);
       while ( (entriep = (pxItemDiscount*) ++cursor) != NULL )
       {
          newentriep = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_,
                                  entriep->DiscountType(), entriep->PharmacyGroupId());
          newentriep->SetDiscountValuePct(entriep->DiscountValuePct());
          newentriep->SetPaymentTargetNo(entriep->PaymentTargetNo());
          newentriep->SetDiscountValPctMan(entriep->DiscountValPctMan());
          ItemDiscountList()->Append(newentriep);
       }
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  DeleteAuxStoreLocList                                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: DeleteAuxStoreLocList
(
)
{
    int retval = 0;
    if ( AuxStoreLocList_ )
    {
       delete AuxStoreLocList_;
       AuxStoreLocList_ = NULL;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
const libcsc::discount::OrderPositionDiscountListPtr pxOrderItem::getDiscountList()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerOrderItem(), "pxOrderItem::getDiscountList()" );

    if( NULL == m_DiscountList.get() )
    {
        libcsc::discount::IOrderPositionDiscountFinderPtr finder = Session()->getOrderPositionDiscountFinder();
        m_DiscountList = finder->findByID( KdAuftragNr(), PosNr() );
    }

    return m_DiscountList;
}

/*----------------------------------------------------------------------------*/
TourInfo* pxOrderItem::getItemTourInformation( bool ibt /* = false */) const
{
    if( ibt )
    {
        if( NULL == m_ItemTourInfoIBT )
        {
            m_ItemTourInfoIBT = new TourInfo( this->Order().getTourAssignmentUtil()->getTourInformation( this->KdAuftragNr(), this->PosNr(), true ) );
        }
        return this->m_ItemTourInfoIBT;
    }
    else
    {
        if( NULL == m_ItemTourInfo )
        {
            m_ItemTourInfo = new TourInfo( this->Order().getTourAssignmentUtil()->getTourInformation( this->KdAuftragNr(), this->PosNr() ) );
            if( !m_ItemTourInfo->getTourFound() )
            {
                delete m_ItemTourInfo;
                m_ItemTourInfo = NULL;
                m_ItemTourInfo = new TourInfo( *this->Order().getTourInformation() );
            }
        }
        return this->m_ItemTourInfo;
    }
}

/*----------------------------------------------------------------------------*/
long pxOrderItem::getIBTCustomerNo()
{
    TourInfo* ibttourinfo = this->getItemTourInformation(true);
    if( ibttourinfo )
    {
        return ibttourinfo->getIBTCustomerNo();
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
long pxOrderItem::getIBTCustomerDeliveryDate()
{
    return this->getItemTourInformation(true)->getCustomerDeliveryDateTimeMin().GetYYYYMMDD();
}

/*----------------------------------------------------------------------------*/
long pxOrderItem::getItemDeliveryTime(char& tourid, bool ibt /*= false*/)
{
    this->getItemTourInformation(ibt)->getTourID().GetData( &tourid );
    nDate x = this->getItemTourInformation(ibt)->getCustomerDeliveryDateTimeMin();
    return x.GetHours() * 100 + x.GetMinutes();
}

/*----------------------------------------------------------------------------*/
long pxOrderItem::getItemDeliveryDate(bool ibt /*= false*/)
{
    return getItemTourInformation(ibt)->getCustomerDeliveryDateTimeMin().GetYYYYMMDD();
}

/*----------------------------------------------------------------------------*/
const nString& pxOrderItem::TourId() const
{
    return getItemTourInformation()->getTourID();
}

/*----------------------------------------------------------------------------*/
long pxOrderItem::getItemTourDate(bool ibt /*= false*/)
{
    return this->getItemTourInformation(ibt)->getTourDate().GetYYYYMMDD();
}

/*----------------------------------------------------------------------------*/
short pxOrderItem::getItemDeliveryTimeBuffer(bool ibt /*= false*/)
{
    return this->getItemTourInformation(ibt)->getDeliveryTimeBuffer();
}

/*----------------------------------------------------------------------------*/
bool pxOrderItem::IsDayIBT()
{
    return this->getItemTourInformation(true)->isDayIBT();
}

/*----------------------------------------------------------------------------*/
short pxOrderItem::IBTType()
{
    return this->getItemTourInformation(true)->getIBTType();
}

/*----------------------------------------------------------------------------*/
void pxOrderItem::removeItemTourAssignments()
{
    this->Order().getTourAssignmentUtil()->resetItemTourAssignments( this );
}

/*----------------------------------------------------------------------------*/
void pxOrderItem::assignItemIBTTour( short ibtbranchno, short nlevelibttype )
{
    TourInfo ti = this->determineItemIBTTour(ibtbranchno, nlevelibttype);
    if( ti.getTourFound() )
    {
        this->IBTType_ = ti.getIBTType();
        this->IBTTourWeekDay_ = static_cast<short>(ti.getTourDate().GetDayOfWeek());
        this->TourIdIBT_ = ti.getTourID();
    }
}

/*----------------------------------------------------------------------------*/
TourInfo pxOrderItem::determineItemIBTTour( short ibtbranchno, short nlevelibttype )
{
    this->Order().getTourAssignmentUtil()->resetInjections();
    this->Order().getTourAssignmentUtil()->injectIBTBranchNo( ibtbranchno );
    this->Order().getTourAssignmentUtil()->injectIBTTypeArticle( this->ArtBase()->getIBTType(), nlevelibttype );
    this->Order().getTourAssignmentUtil()->injectArticle( this->ArtBase() );
    this->Order().getTourAssignmentUtil()->injectOrderPosNo( this->PosNr() );
    this->Order().getTourAssignmentUtil()->assignItemTour( this );
    TourInfo ti = this->Order().getTourAssignmentUtil()->getLastTourInfo();
    return ti;
}

/*----------------------------------------------------------------------------*/
void pxOrderItem::assignItemTour()
{
    if( !this->Order().hasTourInformation() )
    {
        this->Order().getTourInformation();
    }

    if( this->MengeGeliefert() > 0 )
    {
        if( NULL != this->ArtBase() && this->ArtBase()->IsGoodState() )
        {
            if( this->Order().getTourAssignmentUtil()->specialTourPossible( this->ArtBase() ) )
            {
                this->Order().getTourAssignmentUtil()->resetInjections();
                this->Order().getTourAssignmentUtil()->injectArticle( this->ArtBase() );
                this->Order().getTourAssignmentUtil()->injectOrderPosNo( this->PosNr() );
                this->Order().getTourAssignmentUtil()->assignItemTour( this );
                TourInfo ti = this->Order().getTourAssignmentUtil()->getLastTourInfo();
                if( ti.getTourFound() )
                {
                    this->TourId_ = ti.getTourID();
                }
            }
        }
    }
}

/*----------------------------------------------------------------------------*/
nMoney pxOrderItem::getPharmacySellPrice()
{
    nMoney retval = pxConstants::mZero;
    pxCstPrint* CstPrint = NULL;
    short deduction = (short)0;
    if (!Session()->isBulgaria())
    {
       return this->PreisVKApo();
    }
    pxCustBase *customer = Order().Customer();
    if(!customer) // ERROR
    {
        return this->PreisVKApo();
    }

    if ( customer->CstPrintList() )
    {
        CstPrint = customer->CstPrintList()->Find(PreisTyp());
        if(CstPrint != NULL)
        {
            deduction = CstPrint->DeductionAvp();
        }
    }

    // SR-17097017
    if ( deduction == 0 )
    {
        if (this->OrderPosCalcMode())
        {
            return ((OrderPosCalcMode()->CalcAvp() == (double)pxConstants::mZero) ? this->PreisVKApo() : (nMoney)OrderPosCalcMode()->CalcAvp());
        }
    }

    if ( this->OrderPosCalcMode() )
    {
        retval = ( (OrderPosCalcMode()->CalcAvpDis() == (double) pxConstants::mZero) ? this->PreisVKApo() : (nMoney) OrderPosCalcMode()->CalcAvpDis() );
    }
    else
    {
        retval = this->PreisVKApo();
    }
    return retval;
}

int  pxOrderItem :: CopyOrderPosCalcMode ( pxOrderItem* src)
{
   if ( src->OrderPosCalcMode_ != NULL )
   {
      OrderPosCalcMode_ = new pxOrderPosCalcMode(*src->OrderPosCalcMode_);
   }
   return ErrorState();
}

bool pxOrderItem::isIbtBookingCompleted()
{
    if( false == IsAuxPosted() )
    {
        return false;
    }

    libcsc::ibt::IIbtRequestPtr ibtRequest = getIbtRequest();
    if( ibtRequest.get() == NULL )
    {
        return false;
    }

    // reload from DB because of asynchronous processing (ibtorderimport on other server)
    Order().getIbtRequestRepository()->reloadIbtRequest( ibtRequest );
    return ibtRequest->isProcessed();
}
