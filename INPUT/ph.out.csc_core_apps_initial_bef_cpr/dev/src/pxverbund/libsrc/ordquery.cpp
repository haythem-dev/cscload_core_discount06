#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxoeparm.hpp"
#include "pxdelpos.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxordevt.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxcustomerflags.hpp"
#include "pxcstot.hpp"
#include "pxbranch.hpp"
#include "pxcstonr.hpp"
#include "pxseporderartgrp.hpp"
#include "pxcstprint.hpp"
#include "pxcstseporderartgrp.hpp"
#include "pxtendercustomer.hpp"
#include "pxoerestrictions.hpp"
#include "pxdiscount.hpp"
#include "pxtxtdoc.hpp"
#include "pxrangecollect.hpp"
#include "pxcstdiscacc.hpp"
#include "pxtenderhead.hpp"
#include "pxordtaxvalues.hpp"
#include "pxorderdiscacc.hpp"
#include "pxbalancecollect.hpp"
#include "pxvaluescollect.hpp"
#include "pxordervalues.hpp"
#include "pxordercalcmode.hpp"
#include "pxorderposcalcmode.hpp"
#include "pxttype.hpp"
#include <boost/numeric/conversion/cast.hpp>
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"
#include <logger/loggerpool.h>

#include <liblockmanager/lockguard/ilockguard.h>
#include <liblockmanager/exceptions/alreadylockedexception.h>

static nString TextDocKey(const long n);

/*----------------------------------------------------------------------------*/
bool pxOrder::lock4Corpha()
{
    if( m_LockGuard.get() == NULL )
    {
        m_LockGuard = Session()->createCustomerOrderLockGuard( "corpha", KdAuftragNr() );
    }

    try
    {
        m_LockGuard->lock();
    }
    catch(  libLockManager::exceptions::AlreadyLockedException& alex )
    {
        m_LockGuard.reset();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), alex.what());
        return false;
    }
    catch( basar::cmnutil::BasarException& bex )
    {
        m_LockGuard.reset();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), bex.what());
        return false;
    }
    catch( std::exception& sex )
    {
        m_LockGuard.reset();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), sex.what());
        return false;
    }
    catch( ... )
    {
        m_LockGuard.reset();
        BLOG_ERROR(libcsc::LoggerPool::getLoggerSession(), "Error in LockGuard->lock()");
        return false;
    }

    return true;
}

/*----------------------------------------------------------------------------*/
void pxOrder::unlock4Corpha()
{
    if( IsLocked() )
    {
        m_LockGuard.reset();
    }
}

/*----------------------------------------------------------------------------*/
/*  Return customer base class pointer. If the customer base class is not     */
/*  already referenced, its read constructor is called.                       */
/*----------------------------------------------------------------------------*/
pxCustBase*
pxOrder :: Customer
(
)
{
    if (Customer_ == NULL)                     // then no customer reference there
    {                                   // construct pxCustBase object
        Customer_ = new pxCustBase(Session(), VertriebsZentrumNr_, IDFNr_);
        if ( !(Customer_->IsGoodState()) )  // then customer not found
        {
            nError::operator = (Customer_->Error()); // copy error object
            delete Customer_;             // and delete the customer object
            Customer_ = NULL;
        }
        else
        {
            KundenNr_ = Customer_->KundenNr();  // internal customer id
            VertriebsZentrumNr_ = Customer_->Vertriebszentrum();
            FilialNr_ = Customer_->FilialNr();
        }
    }
    return Customer_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the order item list. If no list is currently linked   */
/*  with the order object, a new list is constructed, and, if an active order */
/*  record is in core, its item records are selected from the database.       */
/*----------------------------------------------------------------------------*/
pxOrderItemList*
pxOrder :: ItemList
(
)
{
    if (! ItemList_ )                   // no item list constructed
    {
        ItemList_ = new pxOrderItemList(*this);
        if ( !IsNewOrder() )            // then not a new order
            ItemList_->Select();        // read its items
    }
    return ItemList_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the order item proforma list. If no list is currently */
/*  linked with the order object,a new list is constructed, and after that    */
/*  ItemList is copied. It is a special list for the bulgarien application    */
/*----------------------------------------------------------------------------*/
pxOrderItemList*
pxOrder :: ItemListProforma
(
    const short pricetype /* = -1 */
)
{
    pxOrderItem*         item;
    pxOrderItem*         newitem;
    if (! ItemListProforma_ )                   // no item list constructed
    {
        ItemListProforma_ = new pxOrderItemList(*this);
        if ( ItemList_ )                 //  if there is already an itemlist
        {
            pxOrderItemListIter it(*ItemList_);
            while ( (item = (pxOrderItem*) ++it) != NULL )
            {
                if ( -1 == pricetype || item->PreisTyp() == pricetype )
                {
                    newitem = new pxOrderItem(*item);
                    newitem->MengeVerbund_ = item->MengeVerbund();
                    newitem->CopyItemDiscountList(item);
                    newitem->CopyOrderPosCalcMode( item);
                    newitem->SetActive();
                    ItemListProforma_->Append(newitem);
                }
            }
        }
    }
    return ItemListProforma_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the order item  temporarylist.                        */
/*  If no list is currently linked with the order object,a new list is        */
/*  constructed                                                               */
/*  This list contains just temporary itmes for late calculations.            */
/*  This is a special list for the bulgarien application (ID232)              */
/*----------------------------------------------------------------------------*/
pxOrderItemList*
pxOrder :: ItemListTemporary
(
    const short/* pricetype */
)

{

    if (! ItemListTemporary_ )                   // no item list constructed
    {
        ItemListTemporary_ = new pxOrderItemList(*this);
    }
    return ItemListTemporary_;
}

/*----------------------------------------------------------------------------*/
/*  Return date and time when order was created.                              */
/*----------------------------------------------------------------------------*/
const nTime&
pxOrder :: DateTimeCreated
(
)
{
    if ( DateTimeCreated_ == nTime(time_t(0L)) )        // then time stamp not there
    {
        if ( !IsNewOrder() )             // For an existing order, we read the
        {                                // the lowest entry from the event log
            pxOrderEventList  elist(Session());
            elist.Select(KdAuftragNr_, Order::EntryInProgress, 100);
            if ( elist.Entries() )
            {
                pxOrderEvent *event = (pxOrderEvent*) elist.At(0);
                DateTimeCreated_ = event->DateTime();
            }
        }
    }
    return DateTimeCreated_;
}

/*----------------------------------------------------------------------------*/
/*  Test if current order object may be updated anyway.                       */
/*  Deny update if order not open, opened for viewing, entirely cancelled or  */
/*  otherwise protected.                                                      */
/*----------------------------------------------------------------------------*/
bool pxOrder::IsChangeable()
{
    if( !this->IsOpen() )
    {
        ExternalError(CMsgStream(), CMSG_ORD_UPDATE_DENIED, KdAuftragNr_);
        return false;
    }

    if( this->IsOrderViewing() )
    {
        ExternalError(CMsgStream(), CMSG_ORD_UPDATE_DENIED, KdAuftragNr_);
        return false;
    }

    if( this->IsCancelled() )
    {
        ExternalError(CMsgStream(), CMSG_ORD_UPDATE_DENIED, KdAuftragNr_);
        return false;
    }

    if( this->IsProtected() )
    {
        ExternalError(CMsgStream(), CMSG_ORD_UPDATE_DENIED, KdAuftragNr_);
        return false;
    }
    return true;
}

/*----------------------------------------------------------------------------*/
/*  Test if current order object belongs to the Order Consolidation           */
/*  Facility                                                                  */
/*  If so, 1 is returned, otherwise 0.                                        */
/*----------------------------------------------------------------------------*/
bool
pxOrder :: IsOrderConsolidation
(
)
{
    if( !isMSV3Order() )
    {
        return ( Param()->IsOrderConsolidation()          &&
                 Customer()->Flags().IsAuftragZusammen() &&
               //OrderType().IsNormal()                  &&
                 OrderType().IsOrderCons()               &&
                 CommType().IsShipNormal()               &&
                 StockTrans().IsDefaultTransaction() );
    }
    else
    {
        return IsOrderConsolidationMSV3();
    }
}

/*----------------------------------------------------------------------------*/
/*  Check order consolidation for MSV3                                        */
/*----------------------------------------------------------------------------*/
bool pxOrder::IsOrderConsolidationMSV3()
{
    return ( Customer()->Flags().IsAuftragZusammen() && OrderType().IsOrderCons() && CommType().IsShipNormal() && StockTrans().IsDefaultTransaction() );
}

/*----------------------------------------------------------------------------*/
/*  Test if the current order has a lockentry within the lockmanager. If so,  */
/*  the lockentry within this object must match the entry within the          */
/*  lockmanager. TRUE = Match otherwise FALSE                                 */
/*----------------------------------------------------------------------------*/
bool
pxOrder :: IsLocked
(
) const
{
    return m_LockGuard.get() != 0 && m_LockGuard->isLocked();
}

/*----------------------------------------------------------------------------*/
/*  Return a reference to the order entry parameter object. If an object      */
/*  instance does not exist, its read constructor is called.                  */
/*  To resolve the default values, the object instance is not deleted, if a   */
/*  param table row could not be read from the database.                      */
/*----------------------------------------------------------------------------*/
pxOrderEntryParamPtr
pxOrder :: Param
(
)
{
    return Session()->getOrderEntryParam(Customer()->Vertriebszentrum());
}

/*----------------------------------------------------------------------------*/
/*  Count no. of order items matching a search criteria passed in lparm.      */
/*  A function code of bCOUNT_XX must be set in 'what' to specify what item   */
/*  match criteria to use. Depending on the function code set, 'lparm' may    */
/*  be useless and will therefore default to cDEFAULT. For example, to count  */
/*  the number of items having DCT transmission errors flagged, there is no   */
/*  additional argument required.                                             */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CountItems
(
    int   what,
    long  lparm
)
{
    int count = 0;
    pxOrderItem::ItemType      it = (pxOrderItem::ItemType) lparm;
    pxOrderItem::ArticleState  as = (pxOrderItem::ArticleState) lparm;
    pxOrderItem::QuantityState qs = (pxOrderItem::QuantityState) lparm;

    pxOrderItemListIter iterator(*ItemList());
    pxOrderItem *item;
    while ( (item = (pxOrderItem*) ++iterator) != NULL ) // browse item list
    {
        switch ( what )
        {
        case bCOUNT_ITEMTYPE:         // count no. of items having type lparm
            count += (it == item->PosTyp()) ? 1 : 0;
            break;

        case bCOUNT_ARTSTATE:         // count items with article state 'lparm'
            count += (as == item->ArtState()) ? 1 : 0;
            break;

        case bCOUNT_QSTATE:           // count items matching quantity state lparm
            count += (qs == item->QState()) ? 1 : 0;
            break;

        case bCOUNT_DCT_ERRORS:       // count no. of items with DCT errors
            count += ( !(item->IsArtStateGood() && item->IsQStateGood()) );
            break;

        case bCOUNT_OPIATES:          // count no. of opiate items
            if (  !item->IsCancelled() && item->MengeGeliefert() > 0
                && item->IsProductStocked()
                && item->ArtBase()->ArtClass().IsOpiat() )
            ++count;
            break;

        case bCOUNT_COOLERS:          // count no. of items requring coolers
            if (  !item->IsCancelled() && item->MengeGeliefert() > 0
                && item->IsProductStocked()
                && item->ArtBase()->ArtFlags().IsKuehlKette() )
            ++count;
            break;

        case bCOUNT_TO_COMMISSION:    // count no. of items to picked in stock
            if (  !item->IsCancelled() && item->MengeGeliefert() > 0
                && item->IsProductStocked()
                && item->IsToCommission() )
            ++count;
            break;

        case bCOUNT_ITEM_FLAG:        // no. of items where flag 'lparm' is set
            count += ( item->ItemFlags().TestBit((size_t)lparm) );
            break;

        case bCOUNT_TARGET_PROMOTION:    // count no. of items haveing promotionno > 0 and promotyp = 1
            if (  !item->IsCancelled() && item->MengeGeliefert() > 0
                && item->IsProductStocked()
                && item->IsToCommission()
                && item->PromotionNo() > 0 && item->IsArticleDiscountPromotion() )
            ++count;
            break;


        }
    }
    return count;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the order head text document.                         */
/*----------------------------------------------------------------------------*/
pxTextDoc*
pxOrder :: HeadText
(
)
{
    if ( HeadText_ == NULL)
    {
        HeadText_ = new pxTextDoc(Session(), pxDOC_ORDERHEAD, TextDocKey(KdAuftragNr_));
        if ( !IsNewOrder() )             // for an existing order,
            HeadText_->Get();             // we read the document from the db
    }
    return HeadText_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the order head text document.                         */
/*----------------------------------------------------------------------------*/
pxTextDoc*
pxOrder :: TailText
(
)
{
    if ( TailText_ == NULL)
    {
        TailText_ = new pxTextDoc(Session(), pxDOC_ORDERTAIL, TextDocKey(KdAuftragNr_));
        if ( !IsNewOrder() )             // for an existing order,
            TailText_->Get();              // we read the document from the db
    }
    return TailText_;
}

/*----------------------------------------------------------------------------*/
/*  Convert Order number to build the text document key.                      */
/*----------------------------------------------------------------------------*/
nString TextDocKey(const long n)
{
    char buffer[sizeof(long) * 3];
    sprintf(buffer, "%li", n);
    nString key = buffer;
    return key;
}

/*----------------------------------------------------------------------------*/
/*  Return the total amount booked for the specified article.                 */
/*----------------------------------------------------------------------------*/
pxRangeCollectList*
pxOrder :: RangeCollectList
(
)
{
    if ( !RangeCollectList_ )
        RangeCollectList_ = new pxRangeCollectList();
    return RangeCollectList_;
}

/*----------------------------------------------------------------------------*/
/*  CheckDoubleOrder: takes the product from WertAuftrag and AnzPos           */
/*  Try to find the result in table Customeorderno.                           */
/*  Found:     returns Errornumber and in message the Errortext.              */
/*  Not Found: returns 0 and inserts the value in table customerorderno.      */
/*  Used in XML/KSCSERVER application                                         */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CheckDoubleOrder
(
    char*     message
)
{
    int   retval = 0;
    nMoney ordervalue = 0.0;
    nMoney SumPos     = 0.0;
    pxCustOrderNumber * cnum = NULL;
    pxCustOrderNumberList* cnumlist = NULL;

    if ( AnzPos_ > 0 )
    {
        //ordervalue = (WertAuftrag_ * ((double)AnzPos_ - (double)FirstTransPos_));

/*----------------------------------------------------------------------------*/
/*  Now scan the list of positions                                            */
/*----------------------------------------------------------------------------*/
        pxOrderItemListIter it(*ItemList_);
        pxOrderItem *item;
        it += FirstTransPos_;
        while ( (item = (pxOrderItem*) ++it) != NULL )
        {
            if ( !item->IsCancelled() )
            {
                SumPos += ((double)item->MengeBestellt() * item->PreisEKApo()) + (double)item->ArtikelNr();
            }
        }

        ordervalue += (double)SumPos;
        cnumlist = new pxCustOrderNumberList(Session());
        cnumlist->Select( VertriebsZentrumNr_, IDFNr_, ordervalue);
        if ( cnumlist->Entries() )
        {
            retval = CMSG_ORD_DOUBLE_ORDER;
            nMessage answer (Session()->CMsgStream(), retval, 0);
            sprintf(message,answer.String());
        }
        else
        {
            cnum = new pxCustOrderNumber(Session(),VertriebsZentrumNr_, IDFNr_,ordervalue);
            cnum->Put();
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  CheckDoubleOrder: takes the product from WertAuftrag and AnzPos           */
/*  Try to find the result in table Customeorderno.                           */
/*  Found:     returns Errornumber                                            */
/*  Not Found: returns 0 and inserts the value in table customerorderno.      */
/*  Used in XMIT environment application (umk/bytec/hmk)                      */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CheckDoubleOrder
(
)
{
    int    retval = 0;
    nMoney ordervalue = 0.0;
    nMoney SumPos     = 0.0;
    pxCustOrderNumber * cnum = NULL;
    pxCustOrderNumberList* cnumlist = NULL;
    nString   sapDelNo;

    if ( AnzPos_ > 0 )
    {
        // ordervalue = (WertAuftrag_ * ((double)AnzPos_ - (double)FirstTransPos_));
/*----------------------------------------------------------------------------*/
/*  Now scan the list of positions                                            */
/*----------------------------------------------------------------------------*/
        pxOrderItemListIter it(*ItemList_);
        pxOrderItem *item;
        it += FirstTransPos_;
        while ( (item = (pxOrderItem*) ++it) != NULL )
        {
            if ( !item->IsCancelled() )
            {
                SumPos += ((double)item->MengeBestellt() * item->PreisEKApo()) + (double)item->ArtikelNr();
            }
        }

        ordervalue += (double)SumPos;
        cnumlist = new pxCustOrderNumberList(Session());

        if ( VertriebsZentrumNr_ == 48 )
        {
            cnumlist->Select( VertriebsZentrumNr_, IDFNr_, ordervalue,ReferenceNr_ );
        }
        else
        {
            cnumlist->Select( VertriebsZentrumNr_, IDFNr_, ordervalue);
        }

        pxCustOrderNumberListIter cursor(*cnumlist);
        if ( cnumlist->Entries() )
        {
            retval = CMSG_ORD_DOUBLE_ORDER;
        }
        else
        {
            cnum = new pxCustOrderNumber(Session(),VertriebsZentrumNr_, IDFNr_,ordervalue);
            // Prewhole Frankreich insert ReferenceNr_ = Sap_Delno (Batch)
            if ( VertriebsZentrumNr_ == 48 )
            {
                if ( !ReferenceNr_.IsEmpty() )
                {
                    cnum->SetCustomerOrderNo( ReferenceNr_);
                }
            }
            cnum->Put();
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  StockReservTimeList: this methode looks within the Table Zeitarten depend */
/*  on zeitart = 6 and zeitschluessel = "VZ"                                  */
/*----------------------------------------------------------------------------*/
pxTimeTypeList*
pxOrder :: StockReservTimeList
(
)
{
    short VZ = Customer()->Vertriebszentrum();
    if ( !StockReservTimeList_ )
    {
        nString  key;
        key = VZ;
        StockReservTimeList_  = new pxTimeTypeList( Session() );
        StockReservTimeList_->Select( Type_ADS_NO_RESERVATION, key, VZ);
    }
    return StockReservTimeList_;
}

/*----------------------------------------------------------------------------*/
/*  SepOrderArtGroupList: Returns Pointer to SepOrderArtGroupList_            */
/*----------------------------------------------------------------------------*/
pxSepOrderArtGroupList*
pxOrder :: SepOrderArtGroupList
(
)
{
    pxCustBase*     customer = Customer();
    short           BranchNo = customer->Vertriebszentrum();
    pxCstSepOrderArtGroup* custentryp = NULL;
    pxSepOrderArtGroup*        entryp = NULL;

    if ( SepOrderArtGroupList_ )
        return SepOrderArtGroupList_;

    if ( !customer->CstSepOrderArtGroupList() )
    {
        return  Session()->SepOrderArtGroupList(BranchNo);
    }

    SepOrderArtGroupList_ = new pxSepOrderArtGroupList(Session());
    pxCstSepOrderArtGroupListIter it(* customer->CstSepOrderArtGroupList());

    while ( (custentryp = (pxCstSepOrderArtGroup*) ++it) != NULL )
    {
        entryp = new pxSepOrderArtGroup(Session());
        tSEPORDERARTGRP record;
        record.BranchNo       = custentryp->BranchNo();
        record.ArtGrp         = custentryp->ArtGrp();
        record.KoArt          = custentryp->KoArt();
        record.BuchArt        = custentryp->BuchArt();
        record.DeferOrder     = custentryp->DeferOrder();

        strcpy(record.KdAuftragArt,  " ");
        custentryp->KdAuftragArt().GetData(record.KdAuftragArt);
        Assign(*entryp, record);
        SepOrderArtGroupList_->Append(entryp);
    }

    return SepOrderArtGroupList_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the Customer(Dealer) Discount Account List .          */
/*  if an active order record is in core, the records are selected from the   */
/*  database. Until now, this is a special of the BG/RS application           */
/*----------------------------------------------------------------------------*/
pxCstDiscAccList*
pxOrder :: CstDiscountAccount
(
)
{
    if ( !Session()->isBulgaria() && !Session()->isSerbia() )
        return (CstDiscountAccount_ = NULL);

    if ( RODateFrom_ == pxConstants::NullDate && RODateTo_ == pxConstants::NullDate )
        return (CstDiscountAccount_ = NULL);

    if ( KdAuftragNrOrg() > 0 )
        return (CstDiscountAccount_ = NULL);

    if (! CstDiscountAccount_ )        // not selects yet
    {
        CstDiscountAccount_ = new pxCstDiscAccList( Session() );
        if ( IsNewOrder() )
        {
            if ( ROChain_ == 0 )
            {
                CstDiscountAccount_->Select(Customer()->Vertriebszentrum(),IDFNr_,RODateFrom_,RODateTo_);
            }
            else
            {
                CstDiscountAccount_->Select( Customer()->MainCstNo(), RODateFrom_, RODateTo_);
            }

            if ( CstDiscountAccount_->Entries() == 0 )
            {
                delete CstDiscountAccount_;
                return CstDiscountAccount_ = NULL;
            }

            LockCstDiscAccEntries();

            if ( ROChain_ != 0 )  // FIXME: Should KdAuftragNrOrgRO_ be set if ROChain_ != 0 even on error?
                SetKdAuftragNrOrgRO(KdAuftragNr());

            if ( !IsGoodState() )
            {
                delete CstDiscountAccount_;
                return CstDiscountAccount_ = NULL;
            }
            SetKdAuftragNrOrgRO( KdAuftragNr());
            return CstDiscountAccount_;
        }
        else
        {
            if ( IsDoNotConnectDKRAK() )           // order is delivered delayed
            {
                SetKdAuftragNrOrgRO( KdAuftragNr());
                return  CstDiscountAccount_;
            }

            CstDiscountAccount_->Select(KdAuftragNr() );
            if ( CstDiscountAccount_->Entries() == 0 )
            {
                delete CstDiscountAccount_;
                return CstDiscountAccount_ = NULL;
            }
            RODateFrom_  = ((pxCstDiscAcc*)CstDiscountAccount_->At(0))->Date();
            RODateTo_    = ((pxCstDiscAcc*)CstDiscountAccount_->Last())->Date();
            ROMainCstNo_ = GetCstDiscAccMainCstNo();
            SetKdAuftragNrOrgRO( KdAuftragNr() );
            if ( ROMainCstNo_ )
            {
                ROChain_ = (short)1;
            }
        }
    }
    return CstDiscountAccount_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the TenderHead Entry, if available  .                 */
/*  This entry is selected by TenderNo.                                       */
/*----------------------------------------------------------------------------*/
pxTenderHead*
pxOrder :: TenderHead
(
)
{
    if ( !(OrderType().IsTenderOrder()) && !(OrderType().IsTenderInvoice()) )
        return (TenderHead_ = NULL);

    if ( TenderNo_ == 0 )
        return (TenderHead_ = NULL);

    if (NULL == TenderHead_)
    {
        TenderHead_ = new pxTenderHead(Session(), TenderNo_);
        if ( TenderHead_->Get(cDBGET_READONLY))
        {
            delete TenderHead_;
            TenderHead_ = NULL;
        }
    }
    return TenderHead_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the pxOrdTaxValues, if available.   .                 */
/*----------------------------------------------------------------------------*/
pxOrdTaxValues* pxOrder::OrdTaxValues()
{
    if (! OrdTaxValues_ )             // entry not initialized
    {
        OrdTaxValues_ = new pxOrdTaxValues();
        OrdTaxValues_->InitTaxLevels( Session()->TaxRatesList() );
    }
    return OrdTaxValues_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the pxOrderDiscAccList, if available.                 */
/*----------------------------------------------------------------------------*/
pxOrderDiscAccList*
pxOrder :: OrderDiscAccList
(
)
{
    if (! OrderDiscAccList_ )             // List not initialized
    {
        OrderDiscAccList_ = new pxOrderDiscAccList(Session());
    }
    return OrderDiscAccList_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the pxBalanceCollectList, if available.               */
/*----------------------------------------------------------------------------*/
pxBalanceCollectList*
pxOrder :: BalanceCollectList
(
)
{
    if (! BalanceCollectList_ )             // List not initialized
    {
        BalanceCollectList_ = new pxBalanceCollectList();
    }
    return BalanceCollectList_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the pxValuesCollectList, if available.                */
/*----------------------------------------------------------------------------*/
pxValuesCollectList*
pxOrder :: ValuesCollectList
(
)
{
    if (!ValuesCollectList_ )             // List not initialized
    {
        ValuesCollectList_ = new pxValuesCollectList();
    }
    return ValuesCollectList_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the pxOrderValues(KDAUFTRAGWERTE, if available.       */
/*  Take care for a well contructed pxOrder object                            */
/*----------------------------------------------------------------------------*/
pxOrderValues*
pxOrder :: OrderValues
(
)
{
    if (!Session()->isBulgaria())
        return OrderValues_ = NULL;

    if ( !OrderValues_ )
    {
        OrderValues_ = new pxOrderValues(Session(),KdAuftragNr_);
        if ( !IsNewOrder() )
        {
            if ( OrderValues_->Get(cDBGET_READONLY) )
            {
                delete OrderValues_;
                OrderValues_ = NULL;
                OrderValues_ = new pxOrderValues(Session(),KdAuftragNr_);
                ReCalcValuesOrderValues();
            }
            else
            {
                ReCalcValuesOrderValues();
            }
        }
    }
    return OrderValues_;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the pxOrderCalcMode(KDAUFTRAGRECHART, if available.   */
/*  Take care for a well contructed pxOrder object                            */
/*----------------------------------------------------------------------------*/
pxOrderCalcMode*
pxOrder :: OrderCalcMode
(
)
{
    if (!Session()->isBulgaria())
        return OrderCalcMode_ = NULL;
    pxCstPrint* cstprint = NULL;
    // unused variable
    // short   InvoiceEmail = 0;
    if ( !OrderCalcMode_ )
    {
        OrderCalcMode_ = new pxOrderCalcMode(Session(),KdAuftragNr_);
        if ( !IsNewOrder() )
        {
            if ( OrderCalcMode_->Get(cDBGET_READONLY) )
            {
                delete OrderCalcMode_;
                OrderCalcMode_ = NULL;
            }
        }
        else
        if ( Customer()->CstPrintList() )
        {
            cstprint = Customer()->CstPrintList()->Find ( FREESALE_PRICE );
            if ( cstprint )
            {
                OrderCalcMode_->SetPrint(cstprint->Print());
                OrderCalcMode_->SetDeductionAep(cstprint->DeductionAep());
                OrderCalcMode_->SetDeductionAvp(cstprint->DeductionAvp());
                OrderCalcMode_->SetWithColumnNr(cstprint->WithColumnNr());
                OrderCalcMode_->SetByEmail(cstprint->InvoiceEmail());
                OrderCalcMode_->Put();
            }
            else
            {
                OrderCalcMode_->SetPrint((short)1);
                OrderCalcMode_->SetDeductionAep((short)0);
                OrderCalcMode_->SetDeductionAvp((short)0);
                OrderCalcMode_->SetWithColumnNr((short)0);
                OrderCalcMode_->SetByEmail((short)0);
                OrderCalcMode_->Put();
            }
        }
    }
    return OrderCalcMode_;
}

/*----------------------------------------------------------------------------*/
/*  Return the total amount booked for the specified article corresponding    */
/*  pricetype                                                                 */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CountPriceTypeItems
(
    PriceTypeEnum pricetype
)
{
    int totalamount = 0;                       // return value
    pxOrderItemListIter iterator(*ItemList());
    pxOrderItem *item;
    while ( (item = (pxOrderItem*) ++iterator) != NULL ) // browse item list
    {
        if ( item->PreisTyp() == pricetype )
        {
            totalamount ++;
        }
        else
        if (  pricetype ==  LISTFIVE_PRICE )
        {
            if (item->IsArticleListFiveMember() )
            {
                totalamount ++;
            }
        }
    }

    return totalamount;
}
/*----------------------------------------------------------------------------*/
/*  Returns the total count booked items for destination branch               */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CountIBTDestinationBranchItems( const short destBranchNo )
{
    int count = 0;                       // return value
    pxOrderItemListIter iterator(*ItemList());
    pxOrderItem *item;
    while ( (item = (pxOrderItem*) ++iterator) != NULL ) // browse item list
    {
        if ( item->IsDayNightMergePosition() )
        {
           continue;
        }
        if (item->IsAuxPosted() )
        {
            if ( item->VerbundFilialNr() == destBranchNo )
            {
                count++;
            }
        }
    }

    return count;
}

/*----------------------------------------------------------------------------*/
/*  Return the total amount booked for the specified article corresponding    */
/*  pricetype                                                                 */
/*----------------------------------------------------------------------------*/
int
pxOrder :: countPriceTypeTargetItems
(
    PriceTypeEnum pricetype
)
{
    int totalamount = 0;                       // return value
    pxOrderItemListIter iterator(*ItemList());
    pxOrderItem *item;
    while ( (item = (pxOrderItem*) ++iterator) != NULL ) // browse item list
    {
        if ( item->PreisTyp() == pricetype
                && !item->IsCancelled() && item->MengeGeliefert() > 0
                && item->IsProductStocked()
                && item->IsToCommission()
                && item->PromotionNo() > 0 && item->IsArticleDiscountPromotion() )
        {
                totalamount ++;
        }
    }

    return totalamount;
}

/*----------------------------------------------------------------------------*/
/*  Return the total amount booked for the specified article corresponding    */
/*  pricetype                                                                 */
/*----------------------------------------------------------------------------*/
int
pxOrder::countPriceTypeProductPromotionItems
(
    PriceTypeEnum pricetype
)
{
    int totalamount = 0;                       // return value
    pxOrderItemListIter iterator(*ItemList());
    pxOrderItem *item;
    while ((item = (pxOrderItem*) ++iterator) != NULL) // browse item list
    {
        if (item->PreisTyp() == pricetype
            && !item->IsCancelled() && item->MengeGeliefert() > 0
            && item->IsProductStocked()
            && item->IsToCommission()
            && item->PromotionNo() > 0 && item->PromoTyp() == 0 )
        {
            totalamount++;
        }
    }

    return totalamount;
}

/*----------------------------------------------------------------------------*/
/*  OrderDiscAcc: this function tries to find a kdauftragdiscacc record for   */
/*  this order. It is only for Bulgaria and Ordertype RO                      */
/*  If an entry was found RODateFrom_ and RODateTo_ are set into this order   */
/*  for late use                                                              */
/*----------------------------------------------------------------------------*/
int
pxOrder :: OrderDiscAcc
(
)
{
    pxOrderDiscAcc *DiscAccEntryp = NULL;
    if (!Session()->isBulgaria())
        return ErrorState();

    if ( !(OrderType().IsDiscountAccount()) )
        return ErrorState();


    if (OrderDiscAccList() )
    {
        DiscAccEntryp = new  pxOrderDiscAcc(Session(), Customer()->Vertriebszentrum(), KdAuftragNr_);
        if ( !DiscAccEntryp->Get(cDBGET_READONLY) )   // record exist
        {
            OrderDiscAccList()->Append( DiscAccEntryp);
            RODateFrom_ = DiscAccEntryp->DateFrom();
            RODateTo_   = DiscAccEntryp->DateTo();
            ROChain_    = DiscAccEntryp->SwChain();
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Return pointer to  the total amount booked for the specified article.     */
/*----------------------------------------------------------------------------*/
pxDiscountList*
pxOrder :: OrderPosDiscountList
(
)
{
    if ( !OrderPosDiscountList_ )
        OrderPosDiscountList_ = new pxDiscountList(Session());
    return OrderPosDiscountList_;
}

/*----------------------------------------------------------------------------*/
/*  DeleteOrderPosDiscountList                                                */
/*----------------------------------------------------------------------------*/
int
pxOrder :: DeleteOrderPosDiscountList
(
)
{
    int retval = 0;
    if ( OrderPosDiscountList_ )
    {
        delete OrderPosDiscountList_;
        OrderPosDiscountList_ = NULL;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  DeleteOrderValues                                                         */
/*----------------------------------------------------------------------------*/
int
pxOrder :: DeleteOrderValues
(
)
{
    int retval = 0;
    if (  OrderValues_ )
    {
        delete OrderValues_;
        OrderValues_ = NULL;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/* IsCollectiveOrderDiscountable                                              */
/*----------------------------------------------------------------------------*/
bool
pxOrder :: IsCollectiveOrderDiscountable
(
)
{
    return ( OrderType().IsCollectiveOrder() && CommType().IsNoShipment() && StockTrans().IsNoTransaction() );
}

/*----------------------------------------------------------------------------*/
/* DeleteRangeCollectList                                                     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: DeleteRangeCollectList
(
)
{
    int retval = 0;

    if ( RangeCollectList_ )
    {
        delete RangeCollectList_;
        RangeCollectList_ = NULL;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/* SetDatumAuslieferung                                                       */
/*----------------------------------------------------------------------------*/
int
pxOrder :: SetDatumAuslieferung
(
    const long date
)
{
    int retval = 0;
    DatumAuslieferung_ = nDate(date);
    if (!Session()->isBulgaria())
        return ErrorState();

    /*if ( IsGoodState() && !IsOrderViewing() && !IsCancelled() )
    {
        ReCalculateOrder();
    }*/
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  DeleteItemListTemporary                                                   */
/*----------------------------------------------------------------------------*/
int
pxOrder :: DeleteItemListTemporary
(
)
{
    int retval = 0;
    if ( ItemListTemporary_ )
    {
        delete ItemListTemporary_;
        ItemListTemporary_ = NULL;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  CheckOrderEntryRestrictions                                               */
/*----------------------------------------------------------------------------*/
bool
pxOrder :: checkOrderEntryRestrictions
(
    const long ManufacturerNo
)
{
    bool retval = false;
  //  pxOeRestrictions* oerentry = NULL;
    pxOeRestrictionsList* oerlist = NULL;

    oerlist = new pxOeRestrictionsList(Session());
    try
    {
        oerlist->Select( Customer()->Vertriebszentrum(), static_cast<short>(pxOeRestrictions::RestrictionType_Manufacturer),
                         boost::numeric_cast<short>(ManufacturerNo), Session()->SubDeviceType() );
        if (oerlist->Entries() > 0 )
        {
            retval = true;
        }
    }
    catch (boost::bad_numeric_cast)
    {
    }
    delete oerlist;
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  checkQuantityLimit() This methode checks quantity limits on positions     */
/*  cursor ItemList_ + FirstTransPos_. This is necessary on consolidated      */
/*  orders. Prevent order status DF during appending new position to the      */
/*  consolidated order.                                                       */
/*----------------------------------------------------------------------------*/
bool pxOrder :: checkQuantityLimit()
{
    bool    retval = false;
    int     limitcheckq = 0;         // items with quantity limit check
    if ( AnzPos_ > 0 )
    {
        pxOrderItemListIter it(*ItemList_);
        pxOrderItem *item;
        it += FirstTransPos_;
        while ( (item = (pxOrderItem*) ++it) != NULL )
        {
            if ( !item->IsCancelled() )
            {
                limitcheckq += item->IsQStateLimitCheck();
            }
        }
        if ( limitcheckq > 0 )
        {
            retval = true;
        }
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  setPreisTypSaveForAllItemsInItemlist()    SR-16039137                     */
/*  Sets item->PreisTyp_ to item->PreisTypSaved_ on each item within list     */
/*  item->PreisTypSaved is an application help member of pxOrderItem          */
/*----------------------------------------------------------------------------*/
void pxOrder :: injectPreisTypSavedForAllItemsInItemlist()
{
    if (!Session()->isBulgaria()) // calcultion differs from other countries
          return;

    if ( AnzPos_ > 0 )
    {
        pxOrderItemListIter it(*ItemList_);
        pxOrderItem *item;
        while ( (item = (pxOrderItem*) ++it) != NULL )
        {
           item->SetPreisTypSaved(item->PreisTyp());     // SR-16039137( Bulgaria )
           if (item->IsArticleListFiveMember() )
           {
              item->SetPreisTypSaved(LISTFIVE_PRICE);
           }
        }
    }
}
/*-----------------------------------------------------------------------------*/
/*  getWithTransportExclusion                                                  */
/*----------------------------------------------------------------------------*/
bool pxOrder :: getWithTransportExclusion()
{
    bool withTransportExclusion = false;
    if ( Param()->IsUseTourManagerWithTransportExclusion() )
    {
       withTransportExclusion = true;
    }
    return withTransportExclusion;
}
