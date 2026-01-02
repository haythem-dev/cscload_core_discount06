/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Internal order item posting methods for a stocked product.

REVISION HISTORY

20 December 2011 V1.00 REV 00 written by Ysbrand Bouma
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxdiscount.hpp"
#include "pxdonepromoquotas.hpp"
#include "pxorder.hpp"
#include "pxpromotionquota.hpp"
#include "pxpromotionquotacst.hpp"
#include "pxorderpospromo.hpp"

/*----------------------------------------------------------------------------*/
/*  CheckPromoQuota:                                                          */
/*  FirstCheck: Look for an entry within the table PROMOTIONQUOTA selected by */
/*              BranchNo and PromotionNO. If entry not found, return false   */
/*  SecondCheck: Look for entry wihin PROMOTIONQUOTACST select by BranchNo,   */
/*               Customerno and PromotionNo. If not found, insert entry.      */
/*  Entry Promotionquota: if BranchQuotaQty_ == SoldQtyBranch, return true   */
/*  Entry PromotionquotaCst:if CustomerQuotaQty_ == SoldQtyCst, return true  */
/*----------------------------------------------------------------------------*/
bool
pxOrderItem :: CheckPromoQuota
(
    const short   BranchNo,
    const short   PromotionNo,
    const long    PromoBaseQty
)
{
    bool  PromoExceeded         = false;                // false = not exceeded, true = exceeded
    short      promoUsage       = 0;
    pxPromotionQuotaList*    pQuotaBranchList    = NULL;
    pxPromotionQuotaCstList* pQuotaCustomerList  = NULL;

    pxPromotionQuota*       PromoQuotaBranch    = NULL;
    pxPromotionQuotaCst*    PromoQuotaCustomer  = NULL;

    if ( PromotionNo == 0 )
       return false;

    if(!Session()->isBulgaria())
    {
       return false;
    }
    // Get Main Branch Promoquota
    pQuotaBranchList = new pxPromotionQuotaList(Session());
    pQuotaBranchList->Select(BranchNo, PromotionNo, ArtikelNr() );
    if ( pQuotaBranchList->Entries() == 0 )
    {
       delete pQuotaBranchList;
       return false;
    }
    PromoQuotaBranch = pQuotaBranchList->Find( ArtikelNr() );
    if (PromoQuotaBranch == NULL )
    {
       PromoQuotaBranch = (pxPromotionQuota*)(pQuotaBranchList->At(0) );
    }
    if ( PromoQuotaBranch == NULL )        // just for  being save
    {
       delete pQuotaBranchList;
       return false;
    }

    // now check how the main parameter is configured
    promoUsage = PromoQuotaBranch->CheckPromoQuotaUsage();

    switch ( promoUsage )
    {
       case pxPromotionQuota::UseBranchEntry :
       {
          // check for promoexceeded
          if ( ( PromoQuotaBranch->SoldQtyBranch() ) ==  PromoQuotaBranch->BranchQuotaQty() )
          {
             PromoExceeded = true;
          }
          else  if ( (PromoQuotaBranch->SoldQtyBranch() + PromoBaseQty) > PromoQuotaBranch->BranchQuotaQty() )
          {
              PromoExceeded = true;
          }
          break;
       }
       case pxPromotionQuota::UseCustomerEntry :
       {
          // Get Customer PromoQuota
          pQuotaCustomerList = new pxPromotionQuotaCstList(Session());
          pQuotaCustomerList->Select(BranchNo, PromoQuotaBranch->PromotionNo(), Order().IDFNr() ,PromoQuotaBranch->ArticleNo() );
          if ( pQuotaCustomerList->Entries() == 0 )
          {
             break;
          }
          PromoQuotaCustomer = pQuotaCustomerList->Find(PromoQuotaBranch->ArticleNo());
          if (PromoQuotaCustomer)
          {
             if ( (PromoQuotaCustomer->SoldQtyCst()) ==  PromoQuotaCustomer->CustomerQuotaQty() )
             {
                PromoExceeded = true;
             }
             else if ( (PromoQuotaCustomer->SoldQtyCst() + PromoBaseQty) > PromoQuotaCustomer->CustomerQuotaQty() )
             {
                PromoExceeded = true;
             }
             break;
          }
          PromoQuotaCustomer = (pxPromotionQuotaCst*)(pQuotaCustomerList->At(0));
          if (PromoQuotaCustomer)
          {
             if ( (PromoQuotaCustomer->SoldQtyCst()) ==  PromoQuotaCustomer->CustomerQuotaQty() )
             {
                PromoExceeded = true;
             }
             else if ( (PromoQuotaCustomer->SoldQtyCst() + PromoBaseQty) > PromoQuotaCustomer->CustomerQuotaQty() )
             {
                PromoExceeded = true;
             }

          }
          break;
       }
       case pxPromotionQuota::UseBothEntries :
       {
          // check for promoexceeded
          if ( ( PromoQuotaBranch->SoldQtyBranch() ) ==  PromoQuotaBranch->BranchQuotaQty() )
          {
             PromoExceeded = true;
             break;
          }
          else  if ( (PromoQuotaBranch->SoldQtyBranch() + PromoBaseQty) > PromoQuotaBranch->BranchQuotaQty() )
          {
              PromoExceeded = true;
          }

          // Get Customer PromoQuota
          pQuotaCustomerList = new pxPromotionQuotaCstList(Session());
          pQuotaCustomerList->Select(BranchNo, PromoQuotaBranch->PromotionNo(), Order().IDFNr() ,PromoQuotaBranch->ArticleNo() );
          if ( pQuotaCustomerList->Entries() == 0 )
          {
             break;
          }
          PromoQuotaCustomer = pQuotaCustomerList->Find(PromoQuotaBranch->ArticleNo());
          if (PromoQuotaCustomer)
          {
             if ( (PromoQuotaCustomer->SoldQtyCst()) ==  PromoQuotaCustomer->CustomerQuotaQty() )
             {
                PromoExceeded = true;
             }
             else if ( (PromoQuotaCustomer->SoldQtyCst() + PromoBaseQty) > PromoQuotaCustomer->CustomerQuotaQty() )
             {
                PromoExceeded = true;
             }

             break;
          }
          PromoQuotaCustomer = (pxPromotionQuotaCst*)(pQuotaCustomerList->At(0));
          if (PromoQuotaCustomer)
          {
             if ( (PromoQuotaCustomer->SoldQtyCst()) ==  PromoQuotaCustomer->CustomerQuotaQty() )
             {
                PromoExceeded = true;
             }
             else if ( (PromoQuotaCustomer->SoldQtyCst() + PromoBaseQty) > PromoQuotaCustomer->CustomerQuotaQty() )
             {
                PromoExceeded = true;
             }
          }
          break;
       }
       default :
       {
          break;
       }
    }

    if ( pQuotaBranchList )
       delete  pQuotaBranchList;
    if ( pQuotaCustomerList )
       delete  pQuotaCustomerList;

    return PromoExceeded;
}
/*----------------------------------------------------------------------------*/
/*  UndoPromoQuota:                                                           */
/*  Look for entries within KDAUFTRAGPOSPROMO, if there are entries, undo     */
/*  promotion within tables promotionquota and promotionquotacst              */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: UndoPromoQuota
(
)
{

    int  retval = 0;
    pxOrderPosPromo      *entriep = NULL;
    pxPromotionQuota     *PromoQuotaBranch    = NULL;
    pxPromotionQuotaList *pQuotaBranchList    = NULL;
    pxPromotionQuotaCst  *PromoQuotaCustomer  = NULL;
    short  BranchNo   = Order().Customer()->Vertriebszentrum();
    short  promoUsage       = 0;
    pxCustBase* customer = Order().Customer();
    pxDonePromoQuotasList* DonePromos = customer->DonePromoQuotaList();


    if(!Session()->isBulgaria())
    {
       return retval;
    }

    // look at OrderposPromoList
    if ( OrderPosPromoList() == NULL )
    {
       return retval;
    }
    pxOrderPosPromoListIter  cursor(*OrderPosPromoList_);
    while ( (entriep = (pxOrderPosPromo*) ++cursor) != NULL )
    {
       // look at OrderposPromoList, onl entries with BaseQty() > 0 are affected
       // What to doe with BaseValue on discount entries is not decided at this moment
       if ( entriep->BaseQty() == 0 )
          break;

       // Get Main Branch Promoquota
       pQuotaBranchList = new pxPromotionQuotaList(Session());
       pQuotaBranchList->Select(BranchNo, static_cast<short>(entriep->PromotionNo()), ArtikelNr() );
       if ( pQuotaBranchList->Entries() == 0 )
       {
          delete PromoQuotaBranch;
          break;
       }
       PromoQuotaBranch = pQuotaBranchList->Find( ArtikelNr() );
       if (PromoQuotaBranch == NULL )
       {
          PromoQuotaBranch = (pxPromotionQuota*)(pQuotaBranchList->At(0) );
       }
       if ( PromoQuotaBranch == NULL )        // just for  being save
       {
          delete pQuotaBranchList;
          break;
       }

       // now check how the main parameter is configured
       promoUsage = PromoQuotaBranch->CheckPromoQuotaUsage();
       switch ( promoUsage )
       {
          case pxPromotionQuota::UseBranchEntry :
          {
             nDBBeginTransaction(cDBTransRecord);
             PromoQuotaBranch->SubSoldQtyBranch(MengeBestellt_);
             PromoQuotaBranch->Put();
             if ( PromoQuotaBranch->IsGoodState() )
             {
                nDBCommit(cDBTransRecord);
             }
             break;
          }
          case pxPromotionQuota::UseCustomerEntry :
          {
             // Get Customer PromoQuota
             PromoQuotaCustomer = Order().GetEntryPromotionQuotaCst( PromoQuotaBranch );
             if ( PromoQuotaCustomer == NULL )        // must be an error
                break;
             PromoQuotaCustomer->ForceUpdate();       // Set Active

             nDBBeginTransaction(cDBTransRecord);
             PromoQuotaCustomer->SubSoldQtyCst(MengeBestellt_);
             PromoQuotaCustomer->Put();                     // insert into Database
             if ( PromoQuotaBranch->IsGoodState() )
             {
                nDBCommit(cDBTransRecord);
             }
             if ( DonePromos )
             {
                DonePromos->DeleteEntry( PromoQuotaCustomer->PromotionNo(),PromoQuotaCustomer->ArticleNo() );
             }
             break;
          }
          case pxPromotionQuota::UseBothEntries :
          {
             nDBBeginTransaction(cDBTransRecord);
             PromoQuotaBranch->SubSoldQtyBranch(MengeBestellt_);
             PromoQuotaBranch->Put();
             if ( PromoQuotaBranch->IsGoodState() )
             {
                nDBCommit(cDBTransRecord);
             }

             // Get Customer PromoQuota
             PromoQuotaCustomer = Order().GetEntryPromotionQuotaCst( PromoQuotaBranch );
             if ( PromoQuotaCustomer == NULL )        // must be an error
                break;
             PromoQuotaCustomer->ForceUpdate();       // Set Active

             nDBBeginTransaction(cDBTransRecord);
             PromoQuotaCustomer->SubSoldQtyCst(MengeBestellt_);
             PromoQuotaCustomer->Put();                     // insert into Database
             if ( PromoQuotaCustomer->IsGoodState() )
             {
                nDBCommit(cDBTransRecord);
             }
             break;
          }
          default :
          {
             break;
          }
       }
    }

    if ( pQuotaBranchList )
       delete pQuotaBranchList;

    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  GetLowerPromoCondition                                                    */
/*  Look for entries within DISCOUNT, for a lower condition based on          */
/*  <= restPromoQty                                                           */
/*  Returns DISCOUNT->BaseQty if found, otherwise 0                           */
/*  Methode is used for correct promotionquota calculation.                   */
/*----------------------------------------------------------------------------*/
long
pxOrderItem :: GetLowerPromoCondition
(
    const long restPromoQty,
    const long PromoBaseQty
)
{
    long newPromoBaseQty = 0;
    pxDiscountList*  dlist = NULL;
    pxDiscount*     entryp = NULL;
    pxCustBase  *customer  = Order().Customer();  // customer

    dlist =  new  pxDiscountList(Session());
    dlist->SelectPromotion(Order().FilialNr(),PromotionNo_,ArtikelNr_,customer->IDFNr(),0);
    if (dlist->Entries() == 0 )
    {
       delete dlist;
       return  PromoBaseQty;
    }
    pxDiscountListIter  cursor(*dlist);;
    while ( (entryp = (pxDiscount*) ++cursor) != NULL )
    {
       if ( entryp->BaseQty() >= PromoBaseQty  )
          delete cursor.Remove();
    }
    cursor.Reset();
    while ( (entryp = (pxDiscount*) ++cursor) != NULL )
    {
       if ( restPromoQty >= entryp->BaseQty() )
       {
          newPromoBaseQty = entryp->BaseQty();
          break;
       }
    }

    delete dlist;
    return newPromoBaseQty;
}
/*----------------------------------------------------------------------------*/
/*  ReleasePromoQuota                                                         */
/*  Look for entries within KDAUFTRAGPOSPROMO, if there are entries, reduce   */
/*  quanty depend on qty within tables promotionquota and promotionquotacst,  */
/*  depend on configuration. This methode is called within the program pvhx01 */
/*  during UpdateKdAuftragPos (Satzart AP Kommi Correction) in the bulgarian  */
/*  environment.                                                              */
/*  Please take care on a well constructed item object to prevent             */
/*  unpredictable results.                                                    */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: ReleasePromoQuota
(
    const long Qty
)
{

    int  retval = 0;
    pxOrderPosPromo      *entriep = NULL;
    pxPromotionQuota     *PromoQuotaBranch    = NULL;
    pxPromotionQuotaList *pQuotaBranchList    = NULL;
    pxPromotionQuotaCst  *PromoQuotaCustomer  = NULL;
    short  BranchNo   = Order().Customer()->Vertriebszentrum();
    short  promoUsage       = 0;
    pxCustBase* customer = Order().Customer();
    pxDonePromoQuotasList* DonePromos = customer->DonePromoQuotaList();

    if(!Session()->isBulgaria())
    {
       return retval;
    }

    // look at OrderposPromoList
    if ( OrderPosPromoList() == NULL )
    {
       return retval;
    }
    pxOrderPosPromoListIter  cursor(*OrderPosPromoList_);
    while ( (entriep = (pxOrderPosPromo*) ++cursor) != NULL )
    {
       // look at OrderposPromoList, onl entries with BaseQty() > 0 are affected
       // What to doe with BaseValue on discount entries is not decided at this moment
       if ( entriep->BaseQty() == 0 )
          break;

       // Get Main Branch Promoquota
       pQuotaBranchList = new pxPromotionQuotaList(Session());
       pQuotaBranchList->Select(BranchNo, static_cast<short>(entriep->PromotionNo()), ArtikelNr() );
       if ( pQuotaBranchList->Entries() == 0 )
       {
          delete PromoQuotaBranch;
          break;
       }
       PromoQuotaBranch = pQuotaBranchList->Find( ArtikelNr() );
       if (PromoQuotaBranch == NULL )
       {
          PromoQuotaBranch = (pxPromotionQuota*)(pQuotaBranchList->At(0) );
       }
       if ( PromoQuotaBranch == NULL )        // just for  being save
       {
          delete pQuotaBranchList;
          break;
       }

       // now check how the main parameter is configured
       promoUsage = PromoQuotaBranch->CheckPromoQuotaUsage();
       switch ( promoUsage )
       {
          case pxPromotionQuota::UseBranchEntry :
          {
             nDBBeginTransaction(cDBTransRecord);
             PromoQuotaBranch->SubSoldQtyBranch(Qty);
             PromoQuotaBranch->Put();
             if ( PromoQuotaBranch->IsGoodState() )
             {
                nDBCommit(cDBTransRecord);
             }
             break;
          }
          case pxPromotionQuota::UseCustomerEntry :
          {
             // Get Customer PromoQuota
             PromoQuotaCustomer = Order().GetEntryPromotionQuotaCst( PromoQuotaBranch );
             if ( PromoQuotaCustomer == NULL )        // must be an error
                break;
             PromoQuotaCustomer->ForceUpdate();       // Set Active

             nDBBeginTransaction(cDBTransRecord);
             PromoQuotaCustomer->SubSoldQtyCst(Qty);
             PromoQuotaCustomer->Put();                     // insert into Database
             if ( PromoQuotaBranch->IsGoodState() )
             {
                nDBCommit(cDBTransRecord);
             }
             if ( DonePromos )
             {
                DonePromos->DeleteEntry( PromoQuotaCustomer->PromotionNo(),PromoQuotaCustomer->ArticleNo() );
             }
             break;
          }
          case pxPromotionQuota::UseBothEntries :
          {
             nDBBeginTransaction(cDBTransRecord);
             PromoQuotaBranch->SubSoldQtyBranch(Qty);
             PromoQuotaBranch->Put();
             if ( PromoQuotaBranch->IsGoodState() )
             {
                nDBCommit(cDBTransRecord);
             }

             // Get Customer PromoQuota
             PromoQuotaCustomer = Order().GetEntryPromotionQuotaCst( PromoQuotaBranch );
             if ( PromoQuotaCustomer == NULL )        // must be an error
                break;
             PromoQuotaCustomer->ForceUpdate();       // Set Active

             nDBBeginTransaction(cDBTransRecord);
             PromoQuotaCustomer->SubSoldQtyCst(Qty);
             PromoQuotaCustomer->Put();                     // insert into Database
             if ( PromoQuotaCustomer->IsGoodState() )
             {
                nDBCommit(cDBTransRecord);
             }
             break;
          }
          default :
          {
             break;
          }
       }
    }

    if ( pQuotaBranchList )
       delete pQuotaBranchList;

    return ErrorState();
}
