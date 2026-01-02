#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxcomtyp.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcstot.hpp"
#include "pxstktra.hpp"
#include "pxnarctransfer.hpp"
#include "pxposparking.hpp"
#include "pxstockbooking.hpp"
#include "pxorderpospromo.hpp"
#include "pxkdauftragposrefund.hpp"
#include "pxitemdiscount.hpp"
#include "pxdebitlimit.hpp"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"
#include <discount/orderpositiondiscount/orderpositiondiscountcollection.h>
#include <discount/orderpositiondiscount/orderpositiondiscount.h>
#include <discount/orderpositiondiscount/orderpositiondiscountrepositoryptr.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepository.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepositoryptr.h>
#include <ibt/ibtrequest/iibtrequest.h>

#include <exceptions/cscexceptionbase.h>

/*----------------------------------------------------------------------------*/

extern bool pxGlobalCollectiveOrderDiscountable;

/*----------------------------------------------------------------------------*/
/*  Undo quantity posting.                                                    */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: UndoQuantityPosting
(
    const pxStockTrans& stocktrans
)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerOrderItem(), "pxOrderItem::UndoQuantityPosting()");

    // Undo inventory posting:
    if ( stocktrans.IsDebit() && MengeAbgebucht() > 0 )
    {
        Session()->getStockBooking()->CancelReservationForOpenOrder(*this, this->MengeAbgebucht());
    }
    if ( stocktrans.IsReturn() && MengeBestellt() > 0 )
    {
        Session()->getStockBooking()->SubQtyInStock(*ArtBase_, MengeBestellt_, TRANSACTIONTYPE_CUSTOMERRETURNS);
    }
    if ( stocktrans.IsDemand() )
    {
       ArtBase_->NachFrage( - MengeBestellt_); // backtrack demand booking
    }

    MengeAbgebucht_   = 0;
    MengeGeliefert_   = 0;
    MengeNatra_       = 0;
    MengeNatraHerst_  = 0;
    MengeNatraGrossH_ = 0;
    MengeBestaetigt_  = 0;
    MengeVerbund_     = 0;
    VerbundFilialNr_  = 0;
    DiscountArticleNo_ = 0;
    MengeNatraDiscountArticle_ = 0;
    ClearMengenErhoehung();
}

/*----------------------------------------------------------------------------*/
/*  Undo quantity posting using old order type values passed as arguments,    */
/*  then redo it using the current values received from the order object.     */
/*  Returns 1 if the current item has gone to quantity state 'NotOnHand'      */
/*  after re-doing quantity posting.                                          */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedo
(
    const pxCustOrderType&  ordertype,  // old order type
    const pxCommType&       /*commtype*/,   // old commission type
    const pxStockTrans&     stocktrans // old stock transaction type
)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxOrderItem::UndoRedo()");

    ClearError();
    int    retval = 0;
    short  AuxFil = -1;
    long   batch  = Order().BatchSchreiben();
    long   Qdel   = MengeGeliefert_;
    nMoney FreePreisEKApo = pxConstants::mZero;

    if ( batch == cORTYPE_TRANSFER && Qdel == 0)    // maybe restdelvery
    {
       if ( IsNachliefern() )
       {
           pxVerbund::subsequentDelivery::pxDeliveryPos* delpos = AuxDelList()->Find(KdAuftragNr_, PosNr_, pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
          if (delpos)
          {
             delpos->SetKoArt(Order().KoArt());
             delpos->SetBuchArt(Order().BuchArt());
             delpos->Put();
          }
       }
       return retval;
    }
    nDBBeginTransaction(cDBTransRecord);
    if ( IsProductStocked() && !IsCancelled() && ArtBase(cDBGET_FORUPDATE) && ArtBase()->IsGoodState() )
    {
       // save old quantities:
       long       QOrdered    = MengeBestaetigt_;
       long       QDisInKind  = MengeNatra_;
       long       QDemanded   = MengeBestellt_;
       short      oldqs       = FehlerMenge_;
       long       QNatra      = 0;

       if ( MengeNatra_ > 0 && MengeGeliefert_ > 0 && LinkPosNr_ > 0 )
       {
          QNatra          = MengeNatra_;
       }

       BookingType btype       = PostType();

       UndoArtQuota();                  // Undo previous Quota calculation, take
                                        // care, after that update must be done before
                                        // rebook
       // save  DiscountValPctMan_
       DiscountValPctMan_ = GetDiscountValPctMan();

       // Undo kdauftragposrab, maybe customer change from discountable to non discountable CST
       if ( !pxGlobalCollectiveOrderDiscountable )
       {
          UndoItemDiscount();
       }

       // Test INC-041735
       UndoOrderPosPromo();

       // Test INC-032914
       UndoPromoQuota();
       // Undo
       UndoQuantityPosting(stocktrans);
       // now rewrite ArtQuota for futher calculation
       UpdateArtQuota();
       MengeBestellt_ = 0;              // to prevent unpredictable results on artaccount

       if ( IsAuxPosted() )
       {
		   libcsc::ibt::IIbtRequestPtr ibtRequest = getIbtRequest();
		   if (NULL != ibtRequest.get())
		   {
			   AuxFil = ibtRequest->getIbtBranchNo();
		   }
           UndoAuxPosting();             // return auxposted quantity
           btype = AuxDelivery;
       }


       if ( !Order().OrderType().IsDisInKindEnterable())
           QDisInKind = 0;

       // Redo
       FreePreisEKApo = PreisEKApo_;
       //DiscountValPctMan_ = GetDiscountValPctMan();
       if ( QNatra > 0 )              // this position is an additional natra positione linked to position before
       {
          PostOrderQuantity( 0, QNatra, 0, btype, bPOST_RANGEARTICLE, 0);
       }
       else
       {
          PostOrderQuantity(QOrdered, QDisInKind, QDemanded, btype, bPOST_IGN_LACK, AuxFil);
       }
       if (FreePreisEKApo != PreisEKApo_ )
           SetPreisEKApo( FreePreisEKApo );
       ArtBase_->Put();
       ItemUpdateDiscountList();


       this->Order().BookTenderProgress(this); // I-18015293 - TenderProgress muss wieder geschrieben werden wenn sie gelöscht wurde bei Änderung der Buchungsart


//       ArticleAccount(Order().OrderType(),Order().CommType(),Order().StockTrans(),Order().IDFNr());
       if ( ErrorState() == nSTATE_CONDITION )
          ClearError();
       if ( IsGoodState() )
       {
          if ( Order().Param()->IsSNOToAK() )
          {
             if ( Order().OrderType().IsActive3000() && ordertype.IsNormal() )
             {
                ETPosSchalter_.ClearBit(bDafue);
                ETPosSchalter_.ClearBit(bSeriellUebertragen);
                GeraetTyp_ = pxDVC_VIDEO_WORKSTATION;
             }
          }

          SetDirty();
          ItemUpdate();
          retval = ( FehlerMenge_ & QStateNotOnHand && oldqs != FehlerMenge_ )
                   ? 1 : 0;
       }
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  UndoItemDiscount: Looks for OrderPositionDiscount-instances               */
/*  Available instances get deleted.                                          */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoItemDiscount
(
)
{
    if ( Order().Param()->UseNewDiscountCalc() )
    {
        try
        {
            libcsc::discount::IOrderPositionDiscountRepositoryPtr opdRepository = Session()->getOrderPositionDiscountRepository();
            opdRepository->findByID(KdAuftragNr(), PosNr());

            libcsc::discount::OrderPositionDiscountListPtr opdDiscountList = getDiscountList();
            libcsc::discount::OrderPositionDiscountList::const_iterator it = opdDiscountList->begin();
            while (it != opdDiscountList->end())
            {
                opdRepository->erase(opdRepository->getOrderPositionDiscount((*it)->getPositionNo(), (*it)->getDiscountMode(), (*it)->getRebateInKindPositionNo(), (*it)->getRebateInKindOrderNo()));
                ++it;
            }
            m_DiscountList.reset();
        }
        catch (const basar::Exception & e)
        {
            std::stringstream ss;
            ss << "pxOrderItem :: UndoItemDiscount(): " << e.what().c_str();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str());
        }
    }
    else
    {
        pxItemDiscount *entriep = NULL;
        nString m_str;
        m_str = "pxOrderItem :: UndoItemDiscount";
        if (ItemDiscountList())
        {
            pxItemDiscountListIter  cursor(*ItemDiscountList_);
            {
                while ((entriep = (pxItemDiscount*) ++cursor) != NULL)
                {
                    entriep->logKdAuftragPosRab(m_str);
                    entriep->Delete();
                    delete cursor.Remove();
                    entriep = NULL;
                }
            }
        }
    }
    if( Session()->isSwitzerland() )
    {
        UndoTenderProgress();
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  UndoItemDiscountCHforRPG: Looks for OrderPositionDiscount-instances       */
/*  Available instances get deleted in defined conditions for CH and RPGs     */
/*  defined in a discount matrix (allowed combinations with RGPs)             */
/*----------------------------------------------------------------------------*/
int pxOrderItem::UndoItemDiscountCHforRPG()
{
    pxItemDiscount* entriep = NULL;
    nString	m_str;
    m_str = "pxOrderItem::UndoItemDiscountCHforRPG";
    bool del = true;
    bool omg = false;
    if (ItemDiscountList())
    {
        pxItemDiscountListIter  cursor(*ItemDiscountList_);
        {
            while ((entriep = (pxItemDiscount*) ++cursor) != NULL)
            {
                del = true;
                // define conditions why a discount should not be deleted
                if ((Order().OrderType().IsTransfer() == true) || (entriep->DiscountType() == ValuePctOMG) || (entriep->DiscountType() == LogisticAddition) || (entriep->DiscountType() == LogisticDataTransfer))
                {
                    // if its OMG discount, UW order, or logisticsadditions (standard and datatransfer) it will not be deleted
                    del = false;
                    if (entriep->DiscountType() == ValuePctOMG)
                    {
                        omg = true;
                    }
                }
                if (del == true)
                {
                    entriep->logKdAuftragPosRab(m_str);
                    entriep->Delete();
                    delete cursor.Remove();
                    entriep = NULL;
                }
            }
        }
    }
    if (omg == false)
    {
        UndoTenderProgress();
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  UndoRedoItemDiscount: Looks for ItemDiscount (kdauftragposrab for src)    */
/*  entries. If entries available, so src.Entries are deleted and new entries */
/*  for this item are inserted   .                                            */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedoItemDiscount
(
    pxOrderItem* src
)
{
    nString fun = "pxOrderItem::UndoRedoItemDiscount()";
    // discounts in orderpositiondiscount:
    if (Order().Param()->IsUseNewDiscountCalc())
    {
        try
        {
            libcsc::discount::IOrderPositionDiscountRepositoryPtr srcRepo = Session()->getOrderPositionDiscountRepository();
            libcsc::discount::IOrderPositionDiscountRepositoryPtr destRepo = Session()->getOrderPositionDiscountRepository();

            libcsc::discount::OrderPositionDiscountListPtr srcDiscounts = srcRepo->findByID(src->KdAuftragNr(), src->PosNr());
            libcsc::discount::OrderPositionDiscountList::const_iterator srcIter = srcDiscounts->begin();
            while (srcIter != srcDiscounts->end())
            {
                libcsc::discount::OrderPositionDiscountPtr srcDiscount = (*srcIter);
                libcsc::discount::OrderPositionDiscountPtr destDiscount(new libcsc::discount::OrderPositionDiscount());

                destDiscount->setOrderNo(KdAuftragNr_);
                destDiscount->setPositionNo(PosNr_);
                destDiscount->setDiscountMode(srcDiscount->getDiscountMode());
                destDiscount->setDiscountValue(srcDiscount->getDiscountValue());
                destDiscount->setDiscountPercent(srcDiscount->getDiscountPercent());
                destDiscount->setDiscountQty(srcDiscount->getDiscountQty());
                destDiscount->setRebateInKindOrderNo(srcDiscount->getRebateInKindOrderNo());
                destDiscount->setRebateInKindPositionNo(srcDiscount->getRebateInKindPositionNo());
                destDiscount->setPharmacyGroupId(srcDiscount->getPharmacyGroupId());
                destRepo->get()->push_back(destDiscount);
                destRepo->save();
                ++srcIter;
                srcRepo->erase(srcDiscount);
            }

            srcRepo->reset();
            destRepo->reset();

            srcDiscounts = srcRepo->findByIDBackward(src->KdAuftragNr(), src->PosNr());
            srcIter = srcDiscounts->begin();
            while (srcIter != srcDiscounts->end())
            {
                libcsc::discount::OrderPositionDiscountPtr srcDiscount = (*srcIter);
                libcsc::discount::OrderPositionDiscountPtr destDiscount(new libcsc::discount::OrderPositionDiscount());

                destDiscount->setOrderNo(srcDiscount->getOrderNo());
                destDiscount->setPositionNo(srcDiscount->getPositionNo());
                destDiscount->setDiscountMode(srcDiscount->getDiscountMode());
                destDiscount->setDiscountValue(srcDiscount->getDiscountValue());
                destDiscount->setDiscountPercent(srcDiscount->getDiscountPercent());
                destDiscount->setDiscountQty(srcDiscount->getDiscountQty());
                destDiscount->setRebateInKindOrderNo(KdAuftragNr_);
                destDiscount->setRebateInKindPositionNo(PosNr_);
                destDiscount->setPharmacyGroupId(srcDiscount->getPharmacyGroupId());
                destRepo->get()->push_back(destDiscount);
                destRepo->save();
                ++srcIter;
                srcRepo->erase(srcDiscount);
            }
        }
        catch (const libcsc::exceptions::CSCExceptionBase & e)
        {
            std::stringstream ss;
            ss << fun() << ": Error during discount splitting: " << e.reason().c_str();
            BLOG_ERROR(libcsc::LoggerPool::getLoggerOrderPositionDiscount(), ss.str().c_str());
        }
    }
    // discount in kdauftragposrab
    else
    {
        pxItemDiscount *entriep = NULL;
        pxItemDiscount *newentriep = NULL;
        pxItemDiscountList* srcdlist = src->ItemDiscountList();
        if (srcdlist)
        {
            pxItemDiscountListIter  cursor(*srcdlist);
            while ((entriep = (pxItemDiscount*) ++cursor) != NULL)
            {
                newentriep = new pxItemDiscount(Session(), KdAuftragNr_, PosNr_,
                    entriep->DiscountType(), entriep->PharmacyGroupId(), entriep->PaymentTargetNo());
                if (newentriep->Get())
                {
                    newentriep->SetDiscountValuePct(entriep->DiscountValuePct());
                    newentriep->SetPaymentTargetNo(entriep->PaymentTargetNo());
                    newentriep->SetDiscountValPctMan(entriep->DiscountValPctMan());
                    newentriep->SetSurchargePct(entriep->SurchargePct());
                    newentriep->SetDiscountCategory(entriep->DiscountCategory());
                    newentriep->SetInternalDiscountFlag(entriep->InternalDiscountFlag());
                    newentriep->SetRefundValuePct(entriep->RefundValuePct());
                    newentriep->logKdAuftragPosRab(fun);
                    newentriep->Put();
                    ItemDiscountList()->Append(newentriep);
                }
                if (src->MengeGeliefert() == 0)
                {
                    entriep->logKdAuftragPosRab(fun);
                    entriep->Delete();
                    delete cursor.Remove();
                    entriep = NULL;
                }
            }
        }
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  DeleteNarcTransfer: Looks for NarcTransfer entries                        */
/*  (narctransactiontransfer). Available entries are deleted.                 */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: DeleteNarcTransfer
(
)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxOrderItem::DeleteNarcTransfer()");

    pxNarcTransfer*    NarcEntry = NULL;
    pxNarcTransferList* narclist = new pxNarcTransferList( Session());
    pxNarcTransferListIter iter(*narclist);

    narclist->Select(KdAuftragNr_, PosNr_);

    while ( (NarcEntry = (pxNarcTransfer*) ++iter) != NULL )
    {
       NarcEntry->Delete();
       delete  iter.Remove();
       NarcEntry = NULL;
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  InsertNarcTransfer: a new Narctransactiontransfer entry are written to the  */
/*  database, depend on values within this item, so that you to take care for */
/*  a well constructed pxOrderItem object                                     */
/*  This feature is just controled by param.IsNarcTransfer                    */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: InsertNarcTransfer
(
)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "pxOrderItem::InsertNarcTransfer()");

    if (IsCancelled())
        return ErrorState();
    if (ArtikelNr() == 0)
        return ErrorState();
    if (!IsKnownProduct())
        return ErrorState();
    if (MengeAbgebucht() <= 0)
        return ErrorState();

    if (ArtBase()->ArtClass().IsOpiat() && Order().Param()->IsNarcTransfer())
    {
        pxNarcTransfer NarcEntry(Session(), ArtBase_->FilialNr(), ArtikelNr_ ,KdAuftragNr_,PosNr_);
        NarcEntry.CustomerSupplierNo(Order().IDFNr());
        nString tmp = nString(TRANSACTIONTYPE_DEBIT);
        NarcEntry.TransactionType(tmp);
        NarcEntry.CompletedFlag('0');
        NarcEntry.QtyTransaction(MengeAbgebucht());
        long qtyTotal = Session()->getStockBooking()->GetTotalQtyInStock(*ArtBase_);
        NarcEntry.QtyInStock(qtyTotal);
        NarcEntry.SetTourId(Order().TourId());
        NarcEntry.Put();
        if (!(NarcEntry.IsGoodState()))
        {
            BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), NarcEntry.ErrorMsg());
            ExternalError(CMsgStream(), CMSG_ITM_ACCOUNT_INSERT_DENIED, KdAuftragNr_,ArtikelNr_);
        }
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  UndoPosParking: Looks for PositionParking entries for this item           */
/*  Available entries are deleted.                                            */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoPosParking
(
)
{
    pxPosParking*            Parkp = NULL;
    pxPosParkingList*     ParkList = NULL;
    nDate                 today;
    short                BranchNo = Order().Customer()->Vertriebszentrum();
    long               CustomerNo = Order().Customer()->IDFNr();

    if ( !Order().Param()->IsRoundPackageUnit() )
       return ErrorState();

    // look first for exiting positionparking entries
    ParkList = new pxPosParkingList(Session());
    ParkList->Select(BranchNo, CustomerNo, ArtikelNr_, today, KdAuftragNr_);
    pxPosParkingListIter Iter(*ParkList);
    while ( (Parkp = (pxPosParking*) ++Iter) != NULL )
    {
       Parkp->Delete();        // delete from database
       delete Iter.Remove();   // delete from list
    }
    delete ParkList;
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  UndoItem: Rollback this item completely but do not write this item        */
/*  to the database.                                                          */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoItem
(
)
{
    ClearError();
    if (IsCancelled())
       return ErrorState();             // already done, simply return

    if ( !IsChangeable() )
       return ErrorState();

    nDBBeginTransaction(cDBTransRecord);
    if (ArtBase(cDBGET_FORUPDATE) && ArtBase()->IsGoodState())
    {
       UndoPosParking();
       UndoItemDiscount();
       CancelArtQuota();
       UndoQuantityPosting(Order().StockTrans());
       ArtBaseUpdate();
       UndoAuxPosting();
    }
    ItemUpdate();
    if ( ArtBase_ )
    {
       nError::operator = (ArtBase_->Error()); // copy error object
       delete ArtBase_;             // and delete the artbase object
       ArtBase_ = NULL;
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  RedoItem: Rebook this item                                                */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: RedoItem
(
    const pxCustOrderType&  ordertype  // old order type
)
{
    int    retval = 0;
   // short AuxFil = -1;
    ClearError();

    nDBBeginTransaction(cDBTransRecord);
    if ( IsProductStocked() && !IsCancelled() && ArtBase(cDBGET_FORUPDATE) && ArtBase()->IsGoodState() )
    {
       // save old quantities:
       long       QOrdered    = MengeBestellt_;
       long       QDisInKind  = MengeNatra_;
       long       QDemanded   = MengeBestellt_;
       short      oldqs       = FehlerMenge_;

       BookingType btype       = PostType();

       MengeBestellt_ = 0;              // to prevent unpredictable results on artaccount

       if ( !Order().OrderType().IsDisInKindEnterable())
           QDisInKind = 0;

       // Redo
       OrderQuantity(QOrdered, QDisInKind, QDemanded, btype, bPOST_IGN_LACK);

     /*  PostOrderQuantity(QOrdered, QDisInKind, QDemanded, btype, bPOST_IGN_LACK, AuxFil, GetChargenNr().c_str(), IsFixBatch());
       ArtBase_->Put();
    */
       if ( ErrorState() == nSTATE_CONDITION )
          ClearError();
       if ( IsGoodState() )
       {
          if ( Order().Param()->IsSNOToAK() )
          {
             if ( Order().OrderType().IsActive3000() && ordertype.IsNormal() )
             {
                ETPosSchalter_.ClearBit(bDafue);
                ETPosSchalter_.ClearBit(bSeriellUebertragen);
                GeraetTyp_ = pxDVC_VIDEO_WORKSTATION;
             }
          }

          SetDirty();
          //ItemUpdate();
          retval = ( FehlerMenge_ & QStateNotOnHand && oldqs != FehlerMenge_ )
                   ? 1 : 0;
       }
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  UndoCommission:                                                           */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoCommission
(
)
{
    nDBBeginTransaction(cDBTransRecord);
    ClearToCommission();
    SetDirty();
    ItemUpdate();
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  DoCommission:                                                             */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: DoCommission
(
)
{
    const pxCommType&       ct = Order().CommType();
    const pxCustOrderType&  ot = Order().OrderType();
    nDBBeginTransaction(cDBTransRecord);

       if (ArtBase() && ArtBase()->IsGoodState())
       {
          if ( MengeGeliefert_ > 0 && !ct.IsNoShipment() && !ArtBase_->ArtClass().IsOpiat())
          {
             SetToCommission();
          }
          if ( ArtBase_->ArtClass().IsOpiat() )
          {
             if ( !(ot.IsService() || ot.IsBuyBack()) )
             {
                SetToCustomerService();
                if ( Order().Param()->IsBTMKommi() )
                SetToCommission();
             }
          }
          SetDirty();
          ItemUpdate();
       }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  UndoOrderPosPromo: Looks for OrderPosPromo (kdauftragpospromo) entries    */
/*  Available entries are deleted.                                            */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoOrderPosPromo
(
)
{
    pxOrderPosPromo *entriep = NULL;
    if ( Order().Param()->IsNewDiscount() )
    {
       if ( OrderPosPromoList() )
       {
          pxOrderPosPromoListIter  cursor(*OrderPosPromoList_);
          {
             while ( (entriep = (pxOrderPosPromo*) ++cursor) != NULL )
             {
                entriep->Delete();
                delete cursor.Remove();
                entriep = NULL;
                SetPromotionNo( (short)0);
             }
          }
       }
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  UndoProductPromotion Undo's the give Productpromotion in the case of      */
/*  Natra Rebate                                                              */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoProductPromotion
(
    pxOrderItemList* ItemListProforma
)
{
    pxOrderItem* pos = NULL;
    if ( Order().Param()->IsNewDiscount() )
    {
       if ( MengeNatra() > 0 )
       {
          SetMengeNatra(0);
          //INC-045233 --->>> Krückenlösung
          nDBBeginTransaction(cDBTransRecord);
          //INC-045233 --->>> Krückenlösung
       }
       if ( ItemListProforma != NULL )
       {
          if ( LinkPosNr() > 0 && IsGoodState() )
          {
              pos = (pxOrderItem*)Order().ItemListProforma()->At(LinkPosNr() - 1); // get item
             if (pos)
             {
                if ( pos->IsSperreRabattManuell() )
                {
                   pos->OrderQuantityRange_NatraWithRangeArticle(0L);
                   pos->UndoPromoQuota();
                   pos->UndoOrderPosPromo();
                }
             }
          }
       }
       else
       if ( LinkPosNr() > 0 && IsGoodState() )
       {
           pos = (pxOrderItem*)Order().ItemList()->At(LinkPosNr() - 1); // get item
          if (pos)
          {
             if ( pos->IsSperreRabattManuell() )
             {
                pos->OrderQuantityRange_NatraWithRangeArticle(0L);
                pos->UndoPromoQuota();
                pos->UndoOrderPosPromo();
             }
          }
          UndoOrderPosPromo();
       }
       else
       {
          UndoOrderPosPromo();
       }
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  UndoOrderPosRefund: Looks for oOrderPosRefund (kdauftragposrefund) entries*/
/*  Available entries are deleted                                             */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoOrderPosRefund
(
)
{
    pxKdAuftragPosRefund *entriep = NULL;
    if ( Order().Param()->IsNewDiscount() )
    {
       if ( KdAuftragPosRefundList() )
       {
          pxKdAuftragPosRefundListIter  cursor(*KdAuftragPosRefundList_);
          {
             while ( (entriep = (pxKdAuftragPosRefund*) ++cursor) != NULL )
             {
                entriep->Delete();
                delete cursor.Remove();
                entriep = NULL;
             }
          }
       }
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  UndoRedoOrderPosPromo: Looks for OrderPosPromo(kdauftragpospromo for src) */
/*  entries. If entries available, so src.Entries are deleted and new entries */
/*  for this item are inserted   .                                            */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoRedoOrderPosPromo
(
    pxOrderItem* src
)
{
    pxOrderPosPromo *entriep      = NULL;
    pxOrderPosPromo *newentriep   = NULL;

    if ( Order().Param()->IsNewDiscount() )
    {
        pxOrderPosPromoList* srcdlist = src->OrderPosPromoList();
       if (srcdlist)
       {
          pxOrderPosPromoListIter  cursor(*srcdlist);
          while ( (entriep = (pxOrderPosPromo*) ++cursor) != NULL )
          {
             if (OrderPosPromoList()->Entries() == 0 )
             {
                newentriep = new pxOrderPosPromo(Session(), KdAuftragNr_, PosNr_);

                newentriep->SetPharmacyGroupId(entriep->PharmacyGroupId());
                newentriep->SetDiscountGrpNo(entriep->DiscountGrpNo());
                newentriep->SetBaseQty(entriep->BaseQty());
                newentriep->SetBaseValue(entriep->BaseValue());
                newentriep->SetCustomerNo(entriep->CustomerNo());
                newentriep->SetPromotionNo(static_cast<short>(entriep->PromotionNo()));
                newentriep->SetInternalDiscount(entriep->InternalDiscount());
                newentriep->SetDiscountValuePct(entriep->DiscountValuePct());
                newentriep->Put();
                OrderPosPromoList()->Append(newentriep);
             }
             entriep->Delete();
             delete cursor.Remove();
             entriep = NULL;

          }
       }
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  UndoCreditDayTurnOver : this methode is called by the batch program       */
/*  PVHX01 in the bulgarien order entry environment.                          */
/*  It happens if MengeBestaetigt of this item was reduced (complete or       */
/*  partial) by the Pharmos Kommi                                             */
/*  This item values will be returned to the customers credit limit(K1/K2)    */
/*  SumDayTurnOver                                                            */
/*  OldOrderValuesDebtlimit is the value before MengeBestaetigt_ was reduced  */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoCreditDayTurnOver
(
    nMoney OldOrderValuesDebtlimit,
    nMoney NewOrderValuesDebtlimit

)
{
    pxCustBase*  customer         = Order().Customer();
    pxDebitLimit *lmK2  = NULL;
    pxDebitLimit *lmK1  = NULL;
    bool   cCashPayerHEALTHFUND = false;

    if ( Order().isCashOrder() ||  Order().OrderType().IsDiscountAccount())
    {
       return ErrorState();
    }
    if (!Session()->isBulgaria())
    {
       return ErrorState();
    }

    if ( customer->IsCashPayer( PreisTyp_ , &Order()) )
    {
       if ( PreisTyp_ == HEALTHFUND_PRICE )
       {
          cCashPayerHEALTHFUND = true;
       }
       else
       {
          return ErrorState();
       }
    }
    if ( cCashPayerHEALTHFUND )
    {
       if ( !(IsArticleListFiveMember()) )
       {
          return ErrorState();
       }
       if ( (customer->IsCashPayer(LISTFIVE_PRICE , &Order())) )
       {
          return ErrorState();
       }
    }

    lmK2 = customer->DebitLimitK2();
    if (lmK2 )
    {
       lmK2->Get(cDBGET_READONLY );
       if ( !lmK2->IsGoodState() )
       {
          return ErrorState();
       }

       if (lmK2->Limit() == pxConstants::mZero)
       {
          return ErrorState();
       }

       nDBBeginTransaction(cDBTransRecord);
       {
          lmK2->DecreaseDayTurnOver(OldOrderValuesDebtlimit -  NewOrderValuesDebtlimit);
          //Customer()->DebitLimit()->DecreaseDayTurnOver(GetOrderValuesDebtlimit());
       }
       lmK2->Put();
       if ( !lmK2->IsGoodState() )
       {
          nDBRollBack();
       }
       else
       {
          nDBCommit(cDBTransRecord);
       }
    }

    lmK1 = customer->DebitLimitK1();
    if (lmK1 )
    {
       lmK1->Get(cDBGET_READONLY );
       if ( !lmK1->IsGoodState() )
       {
          return ErrorState();
       }

       if (lmK1->Limit() == pxConstants::mZero)
       {
          return ErrorState();
       }

       if ( !(lmK1->IsListe5()) && IsArticleListFiveMember() )
       {
          return ErrorState();
       }

       nDBBeginTransaction(cDBTransRecord);
       {
          lmK1->DecreaseDayTurnOver(OldOrderValuesDebtlimit -  NewOrderValuesDebtlimit);
          //Customer()->DebitLimit()->DecreaseDayTurnOver(GetOrderValuesDebtlimit());
       }
       lmK1->Put();
       if ( !lmK1->IsGoodState() )
       {
          nDBRollBack();
       }
       else
       {
          nDBCommit(cDBTransRecord);
       }
    }
    return ErrorState();
}
