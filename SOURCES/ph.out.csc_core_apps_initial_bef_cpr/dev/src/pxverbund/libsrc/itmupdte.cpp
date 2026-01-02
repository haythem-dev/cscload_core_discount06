#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxorder.hpp"
#include "pxartcompack.hpp"
#include "pxcstot.hpp"
#include "pxdiscountdef.h"
#include "pxorderposevent.hpp"
#include "pxorderpospromo.hpp"
#include "pxstockbooking.hpp"
#include "pxitemdiscount.hpp"
#include "pxvartikellokallist.hpp"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"
#include "pxoeparm.hpp"
#include <discount/orderpositiondiscount/orderpositiondiscount.h>
#include <discount/orderpositiondiscount/orderpositiondiscountrepositoryptr.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepository.h>

using namespace libcsc::discount;

/*----------------------------------------------------------------------------*/
/*  Open order item update processing.                                        */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: Open
(
)
{
    ClearError();
    ArtBase();                           // reference article
    ArtDispo();                          // reference dispo item
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Close order item update processing.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: Close
(
)
{
    ClearError();
    if ( !IsCancelled() )
    {
       nDBBeginTransaction(cDBTransRecord);
       ItemUpdate();
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Order quantity : a special RangeControl funtionality                      */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: OrderQuantityRange
(
    long       Menge,
    long       MengeNatra,
    long       MengeNachfrage,
    BookingType btype,
    int         flags                  // internal posting flags
)
{
    ClearError();
    if ( !IsChangeable() )
       return ErrorState();
    if ( Order().IsShipmentInProgress() || Order().IsShipmentClosed() )
       return ExternalCondition(CMsgStream(), CMSG_ITM_ORDERQ_DENIED,
                                PosNr_, KdAuftragNr_);

    if (Session()->isBulgaria())      // only BG
    {
       if ( Session()->Device()->IsVideo() )
       {
          SetNotSaveDiscountList();
       }
    }
    nDBBeginTransaction(cDBTransRecord);
    if (ArtBase(cDBGET_FORUPDATE) && ArtBase()->IsGoodState())
    {
       PostOrderQuantity(Menge,MengeNatra,MengeNachfrage,btype,flags, cDEFAULT);
       ArtBaseUpdate();
    }
    else                                // product not stocked
    {
       MengeBestellt_ = Menge;
       MengeNatra_    = MengeNatra;
       SetDirty();
    }
    return ItemUpdate();
}

int pxOrderItem::OrderQuantityRange_RangeArticle(long Menge, long MengeNatra, long MengeNachfrage)
{
    return OrderQuantityRange(Menge, MengeNatra, MengeNachfrage, BookingTypeDefault, bPOST_RANGEARTICLE);
}

int pxOrderItem::OrderQuantityRange_NatraWithRangeArticle(long MengeNatra)
{
    return OrderQuantityRange_RangeArticle(0L, MengeNatra, 0L);
}

/*----------------------------------------------------------------------------*/
/*  Order quantity API.                                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: OrderQuantity
(
    long            Menge,
    long            MengeNatra,
    long            MengeNachfrage,
    BookingType     btype,
    int             flags,
    short           Company,
    double          DiscountValuePct,
    long            MengeBestelltNatra,
    const nString&  batch,
    bool            isFixBatch
)
{
    ClearError();
    if ( !IsChangeable() )
        return ErrorState();
    if ( Order().IsShipmentInProgress() || Order().IsShipmentClosed() )
        return ExternalCondition(CMsgStream(), CMSG_ITM_ORDERQ_DENIED, PosNr_, KdAuftragNr_);

    this->SetMengeBestelltNatra(MengeBestelltNatra);
    // Check IBT->Processingstate
    if ( Company > 0 )
    {
        // Verbund already booked ?
        if ( IsPartialIBTQantity() && LinkPosNr() > 0 )
        {
            pxOrderItem* LinkPos = (pxOrderItem*)Order().ItemList()->At(LinkPosNr()-1);
            if ( LinkPos )
            {
                if (LinkPos->isIbtBookingCompleted())
                {
                    return ExternalCondition(CMsgStream(), CMSG_ITM_IBTPOS_ALREADY_WORKEDUP, LinkPosNr_);
                }
                else
                if  (LinkPos->VerbundFilialNr() != Company )
                {
                    return ExternalCondition(CMsgStream(), CMSG_ITM_IBTPOS_BOOKED_IN_BRANCH, LinkPosNr_, LinkPos->VerbundFilialNr() );
                }
            }
        }
    }

    if ( IsArticleDiscountPromotion() )    // special Bulgaria
    {
        DiscountValPctPromo_    = 0.0;
        DiscountValPctProforma_ = 0.0;
        if ( DiscountValuePct > 0.0 )
        {
            DiscountValPctPromo_ = DiscountValuePct;
        }
    }

    if (Session()->isBulgaria())      // only BG
    {
        if ( Session()->Device()->IsVideo() )
        {
            SetNotSaveDiscountList();
        }
    }

    if (Order().Param()->IsUseNewDiscountCalc())
	{
		UndoItemDiscount();
	}
    UndoPromoQuota();
    UndoOrderPosRefund();

    nDBBeginTransaction(cDBTransRecord);
    // Update the Qty in MengeBestelltOrg_ upon receiving the update.
    if (IsGoodState() && this->MengeBestelltOrg() > 0)
    {
        long UpdMenge = 0L;
	if ( IsPartialIBTQantity() && LinkPosNr() > 0)
	{
            // Update the Qty in IBT order item MengeBestelltOrg_ upon receiving the update.
	    pxOrderItem* LinkPos = (pxOrderItem*)Order().ItemList()->At(LinkPosNr()-1);
	    if ( LinkPos )
	    {
		UpdMenge = Menge + LinkPos->MengeVerbund();
		this->SetMengeBestelltOrg(UpdMenge);
		LinkPos->SetMengeBestelltOrg(UpdMenge);
		LinkPos->CalcDiscount(UpdMenge);
        	LinkPos->SetDirty();
	    }
	}
	else
	{
	    // Update the Qty in Orignal order item MengeBestelltOrg_ upon receiving the update.
	    pxOrderItem* OriginalPos = (pxOrderItem*)Order().ItemList()->GetItemFromSplitIbtPos(this->PosNr());
	    if ( OriginalPos )
	    {
		UpdMenge = OriginalPos->MengeBestellt() + Menge;
		this->SetMengeBestelltOrg(UpdMenge);
		OriginalPos->SetMengeBestelltOrg(UpdMenge);
		OriginalPos->CalcDiscount(UpdMenge);
		OriginalPos->SetDirty();
	    }
	}
    }

    if (ArtBase(cDBGET_FORUPDATE) && ArtBase()->IsGoodState())
    {
        PostOrderQuantity(Menge, MengeNatra, MengeNachfrage, btype, flags, Company, batch, isFixBatch);
		ArtBaseUpdate();
		if (Session()->isCroatia())
		{ 
            ItemUpdateDiscountListHR(); // for HR if we have a discountvalpctman, we have to update orderpositiondiscount
		}
        else
        {
            ItemUpdateDiscountList();  // may there is a discountvalpctman within this object

        }
	}
    else                                // product not stocked
    {
        MengeBestellt_ = Menge;
        MengeNatra_    = MengeNatra;
        SetDirty();
    }

    // Maybe Positionchange from Dafue to Video
    if (Session()->Device()->IsVideo() )  // Video activ
    {
        if ( IsDafue() )
        {
            ETPosSchalter_.ClearBit(bDafue);;
            ETPosSchalter_.ClearBit(bSeriellUebertragen);
            GeraetTyp_     = Session()->Device()->Type();
            Order().SubAnzPosDafue(1L);
        }
    }

    if ( IsGoodState() )
    {
        CalcAvp();                            // calc selling price for pharmacies
    }
    ItemUpdate();
    if ( IsGoodState() )
    {
        Order().CalcPromotionQuota(this);
        ItemUpdateIBTPos(this);
        ItemUpdateDiscountPos(this);
        ItemUpdateComPackMembers(this);
        Order().BookTenderProgress(this);     // book TenderProgress entry
        if (!Session()->Device()->IsVideo())
        {
            Order().ReCalcValues();            // recalc order values(XML)
        }
        // now write kdauftragposereignis type update
        pxOrderPosEvent posevent(*this, pxOrderPosEvent::UpdateInProgress);  // construct order pos event
        posevent.nDBBeginTransaction(cDBTransRecord);
        posevent.Put();                  // write it into the data base
        if (posevent.IsGoodState() )
        {
            posevent.nDBCommit(cDBTransRecord);
        }
        else
        {
            posevent.nDBRollBack();
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Cancel entire order item.                                                 */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CancelItem
(
    const pxOrderItem::CancelOption option
)
{
    nString m_str;
    m_str = "pxOrderItem :: CancelItem";
    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return

    if ( !IsChangeable() )
       return ErrorState();

    nDBBeginTransaction(cDBTransRecord);
    if (ArtBase(cDBGET_FORUPDATE) && ArtBase()->IsGoodState())
    {
       UndoPosParking();
       UndoPromoQuota();
       UndoOrderPosPromo();
       UndoOrderPosRefund();
       BLOG_DEBUG( libcsc::LoggerPool::getLoggerDiscountCalc(), m_str() );
       UndoItemDiscount();
       CancelArtQuota();
       UndoTenderProgress();
       UndoQuantityPosting(Order().StockTrans());
       ArtBaseUpdate();
       UndoAuxPosting();
    }

    if ( IsGoodState() )
    {
       if ( option == ClearMengeBestellt )
       {
          MengeBestellt_ = 0;
       }
       SetCancelled();
       SetDirty();
    }

    return ItemUpdate();
}
/*----------------------------------------------------------------------------*/
/*  Cancel and delete entire item                                             */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CancelAndDeleteItem
(
)
{
    nString m_str;
    m_str = "pxOrderItem :: CancelAndDeleteItem";
    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return

    if ( !IsChangeable() )
       return ErrorState();

    nDBBeginTransaction(cDBTransRecord);
    if ( IsUnKnownProduct() )
    {
       if ( IsGoodState() )
       {
          Delete();
          SetDirty();
       }
       if ( IsGoodState() )
       {
          nDBCommit(cDBTransRecord);
       }
       else
       {
          nDBRollBack();
       }
       ClearDirty();
       return ErrorState();
    }
    if (ArtBase(cDBGET_FORUPDATE) && ArtBase()->IsGoodState())
    {
       UndoPosParking();
       UndoPromoQuota();
       UndoOrderPosPromo();
       UndoOrderPosRefund();
       BLOG_DEBUG( libcsc::LoggerPool::getLoggerDiscountCalc(), m_str() );
       UndoItemDiscount();
       CancelArtQuota();
       UndoTenderProgress();
       UndoQuantityPosting(Order().StockTrans());
       ArtBaseUpdate();
       UndoAuxPosting();
    }

    if ( IsDispoItem() )
    {
       if (ArtDispo_)                   // then we have articledispo item
        ArtDispo_->Delete();            // delete this one
    }

    if ( IsGoodState() )
    {
       Delete();
       SetDirty();
    }

    if ( IsGoodState() )
       nDBCommit(cDBTransRecord);
    else
       nDBRollBack();
    ClearDirty();

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  CancelAuxPosting : This function is called if an orderitem is canceled.   */
/*  If a deliverypos exist,so the posted quantity is returned to the          */
/*  corresponding auxstock. The deliveryposentry is deleted                   */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CancelAuxPosting
(
)
{
    ClearError();
    if ( IsAuxPosted() )
    {
       UndoAuxPosting();
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  Private helper function performing the article data base object update.   */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: ArtBaseUpdate
(
)
{
    if ( ! IsGoodState() )              // then item object is in error,
       ArtBase_->UnLock();              // must unlock ArtBase object
    else
    {
       ArtBase_->Put();                 // re-write and unlock
       Error() = ArtBase_->Error();     // copy error object
       if ( !IsGoodState() )            // Then error occured during
       {                                // data base update.
          delete ArtBase_;              // Force new read construction
          ArtBase_ = NULL;              // for article object.
       }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  ItemUpdateDiscountPos                                                 .   */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: ItemUpdateDiscountPos
(
    pxOrderItem* item
)
{
    pxOrderPosPromo*  pospromo    = NULL;
    double DiscountValuePctMan = 0.0;
    if ( item == NULL)
       return ErrorState();
    if ( IsPartialIBTQantity() )
       return ErrorState();

    // INC-042823
    DiscountValuePctMan = GetDiscountValPctMan();
    if ( DiscountValuePctMan > 0.0 )
       return ErrorState();
    // INC-042823

    if ( item->LinkPosNr() > 0 && item->IsGoodState())
    {
        pxOrderItem* pos = (pxOrderItem*)Order().ItemList()->At(item->LinkPosNr() - 1); // get item
       if (pos)
       {
          pos->OrderQuantityRange_NatraWithRangeArticle(item->MengeNatraDiscountArticle());

          if (Session()->isBulgaria())
          {
             if (  item->MengeNatraDiscountArticle() == 0 )
             {
                pos->UndoOrderPosPromo();
                pos->SetPromotionNo(0);
             }
             else
             {
                pospromo = item->GetOrderPosPromo(item->PromotionNo());
                if ( pospromo )
                {
                   pos->UndoOrderPosPromo();
                   pos->WriteOrderPosPromo(pospromo->PharmacyGroupId(), pospromo->DiscountGrpNo(), pospromo->BaseQty(), pospromo->BaseValue(),
                                           pospromo->CustomerNo(), static_cast<short>(pospromo->PromotionNo()) , pospromo->InternalDiscount());
                }
             }
          }
       }
    }
    else
    if ( item->DiscountArticleNo() > 0 && item->MengeNatraDiscountArticle() > 0 )
    {
       Order().BookDiscountArticle(this);
    }

    return   ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  Private helper. Updates the item data base record and ends the            */
/*  record-based data base transaction. Note that a transaction must have     */
/*  begun prior to call this method.                                          */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: ItemUpdate
(
)
{
    if ( IsGoodState() && IsDirty() && IsActive() && !Order().IsOrderViewing() )
    {
       // Workarround for a unknown Bug. It happens sometimes that the TexSatz bit
       // within etposschalter1 is set and it is until now not clear how it happens
       // And it only happens during inter branch bookings
       // The result is a Verbundrechnung with value zero
       // 29.02.2012
       // This problem happened at 25.02.2012 in Bulgaria also for an normal position
       // I was searching again the whole day to find out how this Bit comes up
       // Now result, so I expand this workarround also on normal positions
       //if ( IsTextSatz() && IsAuxPosted() && IsProductStocked() )
       //{
       //   ClearTextSatz();
       //}
       //else
       //if ( IsTextSatz()  && IsProductStocked() )
       //{
       //   ClearTextSatz();
       //}// end workarround

       SetPreisTypSaved(PreisTyp_);     // SR-16039137( Bulgaria )
       if (IsArticleListFiveMember() )
       {
          SetPreisTypSaved(LISTFIVE_PRICE);
       }
       Put();                           // then re-write this item
    }

    if ( IsGoodState() )
    {
        nDBCommit(cDBTransRecord);

      /* pxOrderPosEvent posevent(*this, pxOrderPosEvent::UpdateInProgress);  // construct order pos event
       posevent.nDBBeginTransaction(cDBTransRecord);
       posevent.Put();                  // write it into the data base
       if (posevent.IsGoodState() )
       {
          posevent.nDBCommit(cDBTransRecord);
       }
    else
    {
          posevent.nDBRollBack();
       }
       */
    }
    else
    {
       nDBRollBack();
       ItemRollBack();            // you never know wether the item will be reused
    }
    ClearDirty();
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  Roll Back the Item in case of error which forced a database rollback.     */
/*  The video user maybe reuses the item in case of error to try another shot.*/
/*  This will lead to bad results in some cases when the object seems to      */
/*  have booked something, which in fact is already rollbacked.               */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: ItemRollBack
(
)
{
    // Verbund
    // Storelocliste: Ein Entry hat geaenderte Menge
    if (AuxStoreLocList_)
    {
       delete AuxStoreLocList_;
       AuxStoreLocList_ = 0;
    }
    // Falsche Deliverypos kann als Objekt existieren.
    if (AuxDelList_)
    {
       delete AuxDelList_;
       AuxDelList_ = 0;
    }
    // Normal
    nError SaveError = Error();
    // Falsche Mengen führen zu falschen Rückbuchungen bei Mengenänderung
    Get(); // Restore Object as is on database
    Error() = SaveError;
}
/*----------------------------------------------------------------------------*/
/*  ItemUpdateComPackMembers: this methode updates the members of this item   */
/*  marked as ComPackHead                                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: ItemUpdateComPackMembers
(
    pxOrderItem* /*item*/
)
{
    pxArtComPackList      *acpl = NULL;
    long                 PosNr = 0;

    if ( !IsStellerKopf() )                  // just if Steller Pseudo Article
       return ErrorState();

    PosNr = PosNr_;
    long QuantityOrdered = 0;
    QuantityOrdered = (Session()->isGermany() ? this->MengeBestaetigt() : this->MengeBestellt());

    // now get the members belonging to this Pseudo article
    acpl = new pxArtComPackList(Session());
    acpl->Select( ArtikelNr() );
    if (acpl->Entries() == 0 )                   // nothing found
    {
        delete acpl;
        return ErrorState();
    }
    // now loop thru
    while ( !(PosNr > Order().AnzPos()) )
    {
        pxOrderItem* pos = (pxOrderItem*)Order().ItemList()->At(PosNr);
       if (pos) // get item
       {
          if ( !(pos->ArticleNoPack() == ArtikelNr()) )
             break;
          pxArtComPack* acpentry = acpl->Find(pos->ArtikelNr());
          if (acpentry)
          {
             pos->OrderQuantity (QuantityOrdered *(acpentry->Quantity()),0,0);
          }
       }
       ++PosNr;
    }
    delete acpl;
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  ItemUpdateDiscountList: this methode updates the members of the           */
/*  ItemDiscountList marked as ValuePctCash(7)                                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: ItemUpdateDiscountList
(
)
{
    pxItemDiscount*   entryp = NULL;
    double SurchargePct = 0.0;
    const pxCustOrderType&  ot = Order().OrderType();
    nString  m_str = "pxOrderItem :: ItemUpdateDiscountList";

    if ( DiscountValPctMan_ == pxConstants::dZero )
        return ErrorState();

    if ( ItemDiscountList()->Entries() > 0 )
    {
       pxItemDiscountListIter iter( *ItemDiscountList_);

       while ( (entryp = ( pxItemDiscount*) ++iter) != NULL )
       {
          SurchargePct = entryp->SurchargePct();
          if ( entryp->PaymentTargetNo() == 0 )
          {
             entryp->Delete();
             delete iter.Remove();
          }
       }
       // INC-043823
       delete  ItemDiscountList_;
       ItemDiscountList_ = NULL;
       ItemDiscountList();
       // INC-043823
    }

    if (Session()->isBulgaria())
    {
       // INC-044448
       if ( !(ot.IsSNoPromotions()) )
       {
          // INC-043823
          UndoProductPromotion();
          // INC-043823
       }
       // INC-044448
    }
    // now insert only a fix rebate entry for this position
    entryp = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_, BestBuy_ValuePctCash, "000",0);
    entryp->SetDiscountValuePct(DiscountValPctMan_);
    entryp->SetDiscountValPctMan(DiscountValPctMan_);
    entryp->SetSurchargePct(SurchargePct);
    entryp->logKdAuftragPosRab(m_str);
    // INC-043823
   //entryp->nDBBeginTransaction(cDBTransRecord);
    // INC-043823
    entryp->Put();
    // INC-042823
    //entryp->nDBCommit(cDBTransRecord);
    // INC-043823
    ItemDiscountList()->Append(entryp);
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  ItemUpdateDiscountListHR: this methode updates                            */
/*  discountpercent in table orderpositiondiscount for HR                     */
/*----------------------------------------------------------------------------*/
int
pxOrderItem::ItemUpdateDiscountListHR
(
)
{
	if (Order().Param()->IsUseNewDiscountCalc())
	{
		libcsc::discount::IOrderPositionDiscountRepositoryPtr Repo = Session()->getOrderPositionDiscountRepository();
		libcsc::discount::OrderPositionDiscountListPtr Discounts = Repo->findByID(KdAuftragNr_, PosNr_);

		if (Discounts->empty())
		{
            if (DiscountValPctMan_ != pxConstants::dZero)
            {
				libcsc::discount::OrderPositionDiscountPtr destDiscount(new libcsc::discount::OrderPositionDiscount());

				destDiscount->setOrderNo(KdAuftragNr_);
				destDiscount->setPositionNo(PosNr_);
				destDiscount->setDiscountMode(DM_WHOLESALE_INDUSTRY_PERCENT_MODE);
				destDiscount->setDiscountValue(libcsc::Decimal(basar::Decimal(0)));
				destDiscount->setDiscountPercent(libcsc::Decimal(basar::Decimal(DiscountValPctMan_)));
				destDiscount->setDiscountQty(0);
				destDiscount->setRebateInKindOrderNo(0);
				destDiscount->setRebateInKindPositionNo(0);
                destDiscount->setPharmacyGroupId(basar::VarString("000"));
				Repo->get()->push_back(destDiscount);
				Repo->save();
			}
		}
		else
		{
			libcsc::discount::OrderPositionDiscountList::const_iterator Iter = Discounts->begin();
			while (Iter != Discounts->end())
			{
				libcsc::discount::OrderPositionDiscountPtr Discount = (*Iter);

				if (Discount->getDiscountMode().get() == libcsc::discount::DM_WHOLESALE_PERCENT_MODE ||
					Discount->getDiscountMode().get() == libcsc::discount::DM_WHOLESALE_INDUSTRY_PERCENT_MODE)
				{
                    if (DiscountValPctMan_ == pxConstants::dZero) 
                    {
                        ++Iter;
                        Repo->erase(Discount);
                    }
                    else
                    {
                        Discount->setDiscountPercent(libcsc::Decimal(basar::Decimal(DiscountValPctMan_)));
                        Repo->save();
                        ++Iter;
                    }
				}
                else 
                {
                    ++Iter;
                }
			}
		}

		Repo->reset();
	}
	return ErrorState();
}
/*----------------------------------------------------------------------------*/
/* SetMengeNatra                                                              */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: SetMengeNatra
(
   const long       MengeNatra
)
{
    ClearError();
    if ( !IsChangeable() )
       return ErrorState();
    if ( Order().IsShipmentInProgress() || Order().IsShipmentClosed() )
       return ExternalCondition(CMsgStream(), CMSG_ITM_ORDERQ_DENIED,
                                PosNr_, KdAuftragNr_);

    nDBBeginTransaction(cDBTransRecord);
    if (ArtBase(cDBGET_FORUPDATE) && ArtBase()->IsGoodState())
    {
       if ( MengeNatraGrossH_ == MengeNatra_ )
          MengeNatraGrossH_ = MengeNatra;
       if ( MengeNatraHerst_ == MengeNatra_ )
          MengeNatraHerst_ = MengeNatra;
       MengeAbgebucht_ -= MengeNatra_;
       MengeGeliefert_ -= MengeNatra_;
       if (MengeNatra_ > 0)
       {
          Session()->getStockBooking()->CancelReservationForOpenOrder(*this, MengeNatra_);
       }
       MengeNatra_ = MengeNatra;
       MengeAbgebucht_ += MengeNatra_;
       MengeGeliefert_ += MengeNatra_;
       if (MengeNatra_ > 0)
       {
          Session()->getStockBooking()->AddReservationForOpenOrder(*this, MengeNatra_);
       }
       ArtBaseUpdate();
    }
    else                                // product not stocked
    {
       MengeNatra_    = MengeNatra;
       SetDirty();
    }
    ItemUpdate();
    return ErrorState();
}
