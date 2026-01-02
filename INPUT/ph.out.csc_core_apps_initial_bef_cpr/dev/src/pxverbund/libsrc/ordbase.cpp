#include "pxorder.hpp"
#include <pxdbxx.h>
#include <nntypes.h>
#include "pxdefs.hpp"
#include "pxsess.hpp"
#include "pxbranch.hpp"
#include "pxcstbas.hpp"
#include "pxnumb.hpp"
#include "pxtenderhead.hpp"
#include "pxtenderpos.hpp"
#include "pxordvtr.hpp"
#include "pxorderremarks.hpp"
#include "pxorderrelationno.hpp"
#include "pxparameter.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

// Only for destructor deletes:
#include "pxoeparm.hpp"
#include "pxseporderartgrp.hpp"
#include "tourutil.hpp"
#include "tourassignmentutil.hpp"
#include "pxtxtdoc.hpp"
#include "pxrangecollect.hpp"
#include "pxorderdiscacc.hpp"
#include "pxcstdiscacc.hpp"
#include "pxordtaxvalues.hpp"
#include "pxbalancecollect.hpp"
#include "pxvaluescollect.hpp"
#include "pxordervalues.hpp"
#include "pxordercalcmode.hpp"
#include "pxdiscount.hpp"
#include "pxttype.hpp"
#include "pxartbas.hpp"
#include "pxcustdeldelivery.hpp"
#include "pxcstot.hpp"
#include "pxcustomerflags.hpp"

#include <boost/make_shared.hpp>
#include <ibt/componentmanager/ibtcomponentmanager.h>
#include <cscorder/componentmanager/cscordercomponentmanager.h>
#include <cscorder/componentmanager/cscordercomponentmanagerptr.h>

#include <cscordertype/componentmanager/cscordertypecomponentmanager.h>
#include <cscordertype/componentmanager/cscordertypecomponentmanagerptr.h>
#include <cscordertype/repository/icscordertyperepository.h>
#include <cscordertype/icscordertype.h>
#include "cscordertype/cscordertypebatchconfig/icscordertypebatchconfig.h"

#include <cscorder/cscorderflags/icscorderflagsrepository.h>
#include <cscorder/cscorderflags/icscorderflags.h>


extern bool pxGlobalDataBaseSort;

static const int   cOrdFlagEntries  = 6;
static const long  cPMSwapDelay = 30L * 60L; // delay in seconds before swapping from AM to PM


MessageCodeEnum pxOrder::isBatchValid(const nString &batchNr, bool isFixBatch)
{
    nString batch = batchNr;
    batch.Strip();

    libcsc::cscordertype::ICSCOrderTypePtr cscOrderType = getCscOrderType();

    const libcsc::Bool isDesiredBatchAllowed = cscOrderType->getBatchConfig()->getAllowDesiredBatch();
    const libcsc::Bool isFixedBatchAllowed = cscOrderType->getBatchConfig()->getAllowFixedBatch();

    if (batch.IsEmpty())
    {
        /*
        if (!isFixBatch && !isDesiredBatchAllowed && !isFixedBatchAllowed)
        {
            return CMSG_OK;
        }
        */

        /*
        if (!isFixBatch && !isDesiredBatchAllowed && isFixedBatchAllowed)
        {
            return CMSG_OK;
        }
        */

        /*
        if (!isFixBatch && isDesiredBatchAllowed && !isFixedBatchAllowed)
        {
            return CMSG_OK;
        }
        */

        if (!isFixBatch && isDesiredBatchAllowed && isFixedBatchAllowed)
        {
            return CMSG_SDC_BATCH_PROCESSING_NOT_POSSIBLE;
        }

        if (isFixBatch && !isDesiredBatchAllowed && !isFixedBatchAllowed)
        {
            return CMSG_SDC_NO_BATCH_PROVIDED;
        }

        if (isFixBatch && !isDesiredBatchAllowed && isFixedBatchAllowed)
        {
            return CMSG_SDC_NO_BATCH_PROVIDED;
        }

        if (isFixBatch && isDesiredBatchAllowed && !isFixedBatchAllowed)
        {
            return CMSG_SDC_NO_BATCH_PROVIDED;
        }

        if (isFixBatch && isDesiredBatchAllowed && isFixedBatchAllowed)
        {
            return CMSG_SDC_BATCH_PROCESSING_NOT_POSSIBLE;
        }
    }
    else
    {
        if (!isFixBatch && !isDesiredBatchAllowed && !isFixedBatchAllowed)
        {
            return CMSG_SDC_BATCH_GIVEN_BUT_NOT_PERMITTED; // TESTED
        }

        if (!isFixBatch && !isDesiredBatchAllowed && isFixedBatchAllowed)
        {
            return CMSG_SDC_DESIRED_BATCH_GIVEN_ONLY_FIXED_ALLOWED; // TESTED
        }

        /*
        if (!isFixBatch && isDesiredBatchAllowed && !isFixedBatchAllowed)
        {
            return CMSG_OK;
        }
        */

        if (!isFixBatch && isDesiredBatchAllowed && isFixedBatchAllowed)
        {
            return CMSG_SDC_BATCH_PROCESSING_NOT_POSSIBLE;
        }

        if (isFixBatch && !isDesiredBatchAllowed && !isFixedBatchAllowed)
        {
            return CMSG_SDC_FIXED_BATCH_GIVEN_BUT_NOT_ALLOWED; // TESTED
        }

        /*
        if (isFixBatch && !isDesiredBatchAllowed && isFixedBatchAllowed)
        {
            return CMSG_OK;
        }
        */

        if (isFixBatch && isDesiredBatchAllowed && !isFixedBatchAllowed)
        {
            return CMSG_SDC_FIXED_BATCH_GIVEN_BUT_NOT_ALLOWED; // TESTED
        }

        if (isFixBatch && isDesiredBatchAllowed && isFixedBatchAllowed)
        {
            return CMSG_SDC_BATCH_PROCESSING_NOT_POSSIBLE;
        }
    }

    return CMSG_OK;
}

/*----------------------------------------------------------------------------*/
void pxOrder::setNoDelayedDelivery(bool nodelayeddelivery /* = true */)
{
    getCSCOrderFlags()->setNoDelayedDelivery(nodelayeddelivery);
}

/*----------------------------------------------------------------------------*/
bool pxOrder::getNoDelayedDelivery() const
{
    return getCSCOrderFlags()->isNoDelayedDelivery();
}

/*----------------------------------------------------------------------------*/
void pxOrder::setWaitForIbtPicking(bool waitForIbtPicking /* = true */)
{
    getCSCOrderFlags()->setWaitForIbtPicking(waitForIbtPicking);
}

/*----------------------------------------------------------------------------*/
bool pxOrder::getWaitForIbtPicking() const
{
    return getCSCOrderFlags()->isWaitForIbtPicking();
}

/*----------------------------------------------------------------------------*/
libcsc::cscorder::domMod::ICSCOrderFlagsPtr pxOrder::getCSCOrderFlags() const
{
    if( 0 == m_CSCOrderFlags.get() )
    {
        m_CSCOrderFlags = getCSCOrderFlagsRepository()->findCSCOrderFlags(KdAuftragNr_);
        if( 0 == m_CSCOrderFlags->getCscOrderNo() ) { m_CSCOrderFlags->setCscOrderNo( KdAuftragNr_ ); }
    }
    return m_CSCOrderFlags;
}

/*----------------------------------------------------------------------------*/
libcsc::cscorder::repo::ICSCOrderFlagsRepositoryPtr pxOrder::getCSCOrderFlagsRepository() const
{
    if( 0 == m_CSCOrderFlagsRepository.get() )
    {
        m_CSCOrderFlagsRepository = Session()->getCSCOrderComponentManager()->getCSCOrderFlagsRepository();
    }
    return m_CSCOrderFlagsRepository;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
libcsc::ibt::IIbtRequestRepositoryPtr pxOrder::getIbtRequestRepository() const
{
    if( 0 == m_IbtRequestRepository.get() )
    {
        m_IbtRequestRepository = Session()->getIbtComponentManager()->createIbtRequestRepository( this );
    }
    return m_IbtRequestRepository;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::closeIBTAtOnce()
{
    if (this->Param()->IsSCloseIBTAtonce()) // prüfen ob Verbund-Sofortabschluss aktiv ist
    {
        return true;
    }

    if (this->BatchSchreiben() == cORTYPE_PURE_IBT_ORDER) // prüfen ob der Auftrag aus dem ANNA Verbundsplit stammt, dann auch Sofort-Abschluss für Verbund
    {
        return true;
    }

    return false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::IsAvailableForOrderConsolidation()
{
    // Keine Auftragszusammenführung für den Kunden
    if( ! this->Customer()->Flags().IsAuftragZusammen() )
    {
        return false;
    }

    // Flag für keine Auftragszusammenführung ist gesetzt
    if( true == IsDoNotAppend() ) return false;

    // Keine Auftragszusammenführung für bestimmte Auftragsarten
    pxCustOrderTypeList *otlp = this->Customer()->OrderTypeList();
    pxCustOrderType *otp = otlp->Find( this->KdAuftragArt(), this->FilialNr(), this->IDFNr() );
    if ( otp && !otp->IsOrderCons() )
    {
        return false;
    }

    // Gesplittet, nicht anhängen
    if( this->KdAuftragNrOrg() > 0 ) { return false; } // verzögerte Aufträge sollten eine KdAuftragNrOrg haben! Nicht anhängen! (Ist leider nicht immer der Fall!)

    // Max. Anzahl Positionen pro Auftrag erreicht?
    if( this->Param()->MaxPosAuftrag() > 0 )
    {
        if( this->AnzPos() >= this->Param()->MaxPosAuftrag() ) { return false; }
    }

    // Verzögerte Auslieferung für Kühlartikel und BTM prüfen
    if( TourUtil::isNullOrCurrentDate(this->DatumAuslieferung()) && this->AnzPos() > 0 )
    {
        pxCustDelDelivery custdeldelivery(this->Session(), this->FilialNr(), this->IDFNr(), TourUtil::getCurrentWeekday() );
        if( 0 == custdeldelivery.Get(cDBGET_READONLY)  )
        {
            if( custdeldelivery.Activ() )
            {
                OrderItemCounts c = this->GetOrderItemCounts();
                long delayedqty = 0;

                // Verzögerung für Kühlartikel
                if( custdeldelivery.IsCool08() )        { delayedqty += c.CoolBelow8Lines;  }
                if( custdeldelivery.IsCool20() )        { delayedqty += c.CoolBelow20Lines; }
                if( custdeldelivery.IsColdChain() )     { delayedqty += c.CoolChainLines;   }

                // Verzögerung für BTMs
                if( custdeldelivery.IsNarCotic() )      { delayedqty += c.NarcoticLines;    }

                // Keine Auftragszusammenführung mit Aufträgen die nur verzögerte Artikel enthalten
                if( this->AnzPos() <= delayedqty )
                {
                    return false;
                }
            }
        }
    }

    return true;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxOrder::updateItemTours()
{
    // if an order has already an ItemList_ the order open will fail due to order already opened! so set the state of the ItemList_ back to the old state afterwards!
    bool set_itemlist_to_null = true;
    if( this->ItemList() ) set_itemlist_to_null = false;

    pxOrderItemListIter it(*this->ItemList());
    pxOrderItem *item;
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        if( 0 == item->MengeGeliefert() ) continue;
        item->assignItemTour();
    }

    if( set_itemlist_to_null )
    {
        delete ItemList_;
        ItemList_ = NULL;
    }
}

/*----------------------------------------------------------------------------*/
pxOrder::OrderItemCounts pxOrder::GetOrderItemCounts()
{
    OrderItemCounts retval;

    pxArtBase* artbase = NULL;
    bool delete_artbase = false;

    // if an order has already an ItemList_ the order open will fail due to order already opened! so set the state of the ItemList_ back to the old state afterwards!
    bool set_itemlist_to_null = true;
    if( ItemList_ ) { set_itemlist_to_null = false; }

    pxOrderItemListIter it(*ItemList());
    pxOrderItem *item;
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        if( 0 == item->MengeGeliefert() ) continue;

        long itemTourDate = item->getItemTourDate();
        long orderTourDate = getTourDate();
        nString itemTourID = item->TourId();
        nString orderTourID = TourId();

        if( itemTourDate != orderTourDate || itemTourID != orderTourID )
        {
            ++retval.DifferingTourLines;
        }

        artbase = item->ArtBase(); delete_artbase = false;
        if( NULL == artbase )
        {
            artbase = pxArtBase::CreateArticle(Session(), item->ArtikelNr(), this->FilialNr());
            delete_artbase = true;
        }

        if( artbase->IsGoodState() )
        {
            if( artbase->ArtFlags().IsKuehlKette() )    { ++retval.CoolChainLines; }
            if( artbase->ArtFlags().IsGekuehlt08() )    { ++retval.CoolBelow8Lines; }
            if( artbase->ArtFlags().IsGekuehlt20() )    { ++retval.CoolBelow20Lines; }
            if( artbase->ArtClass().IsOpiat() )         { ++retval.NarcoticLines; }
        }

        if( delete_artbase && NULL != artbase )
        {
            delete artbase;
            artbase = NULL;
        }
    }

    if( set_itemlist_to_null )
    {
        delete ItemList_;
        ItemList_ = NULL;
    }

    return retval;
}
/*----------------------------------------------------------------------------*/

libcsc::cscordertype::ICSCOrderTypePtr pxOrder::getCscOrderType()
{
    if(m_CscOrderType.get() == 0)
    {
        m_CscOrderType =
            this->Session()->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->findOrderType(
            Session()->Branch()->FilialNr(), static_cast<basar::VarString>(OrderType().KdAuftragArt()));
    }
    else if(m_CscOrderType->getOrderType() != static_cast<basar::VarString>(OrderType().KdAuftragArt()))
    {
        m_CscOrderType =
            this->Session()->getCSCOrderTypeComponentManager()->getCSCOrderTypeRepository()->findOrderType(
            Session()->Branch()->FilialNr(), static_cast<basar::VarString>(OrderType().KdAuftragArt()));
    }

    return m_CscOrderType;
}


/*----------------------------------------------------------------------------*/
bool pxOrder::isTenderOrder()
{
    if( TenderNo_ > 0 )
    {
        return true;
    }
    return false;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::isArticlePartOfTender( const long articleno )
{
    // check if articleno is part of the current tender
    pxTenderPosList tpl( Session() );
    tpl.Select(TenderNo_, articleno);
    if( tpl.Entries() > 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxOrder::SetTenderNo(const long TenderNo)
{
    if( TenderNo_ > 0 )
    {
        char temp[200];
        sprintf((char*)temp,"%d SetTenderNo Error: Tried to set TenderNo twice! Branch %d Customer %d TenderNo %d NewTenderNo %d", (int)KdAuftragNr(), (int)FilialNr(), (int)IDFNr(), (int)TenderNo_, (int) TenderNo );
        nString message(temp);
        pxGenericOrderRemarkList remarklist( Session() );
        remarklist.AddOrderRemark( KdAuftragNr(), 0, eErrorLogging, message() );
        return;
    }

    TenderNo_ = TenderNo ;

    pxTenderHead th( Session(), TenderNo_ );
        if( 0 == th.Get() )
        {
            if( th.TenderNo() == TenderNo_ )
            {
                setTenderContractId( th.ContractNo() );
            }
            else
            {
                char temp[200];
                sprintf((char*)temp,"%d SetTenderNo Error: Branch %d Customer %d TenderNo %d", (int)KdAuftragNr(), (int)FilialNr(), (int)IDFNr(), (int)TenderNo_ );
                nString message(temp);
                pxGenericOrderRemarkList remarklist( Session() );
                remarklist.AddOrderRemark( KdAuftragNr(), 0, eErrorLogging, message() );
            }
        }
    }
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
bool pxOrder::setTenderContractId(const  nString& tendercontractid)
{
    pxGenericOrderRemarkList remarklist( Session() );
    return remarklist.AddOrderRemark( KdAuftragNr(), 0, eTenderContractId, tendercontractid() );
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
void pxOrder::SetOrderRemarkText(const nString& RemarkText)
{
    pxGenericOrderRemarkList remarklist(Session());
    if (remarklist.SelectOrderRemarksByOrderNoAndType(KdAuftragNr(), eRemarkText))
    {
        if (RemarkText.IsEmpty())
        {
            remarklist.RemoveOrderRemark(KdAuftragNr(), 0, eRemarkText, RemarkText());
        }
        else
        {
            remarklist.ChangeOrderRemark(KdAuftragNr(), 0, eRemarkText, RemarkText());
        }
    }
    else
    {
        if (!RemarkText.IsEmpty())
        {
            remarklist.AddOrderRemark(KdAuftragNr(), 0, eRemarkText, RemarkText());
        }
    }
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
pxGenericOrderRemarkList pxOrder::getGenericOrderRemarks()
{
    pxGenericOrderRemarkList remarklist( Session() );
    remarklist.SelectOrderRemarksByOrderNo( KdAuftragNr() );
    return remarklist;
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  Construct an instance with a customer object reference.                   */
/*----------------------------------------------------------------------------*/
pxOrder :: pxOrder
(
    pxSession *session,
    pxCustBase& customer
)
    : pxDBRecord(session)
{
    Init();
    Customer_ = new pxCustBase(customer); // use pxCustBase copy constructor
    IDFNr_    = Customer_->IDFNr();     // ensure IDF-NR is there
    KundenNr_ = Customer_->KundenNr();  // internal customer id
    VertriebsZentrumNr_ = Customer_->Vertriebszentrum();
    OpenOrder(cDBOPEN_INSERT);               // open order item entry
}

/*----------------------------------------------------------------------------*/
/* check if it´s an order from a product availability request                 */
/*----------------------------------------------------------------------------*/
bool pxOrder::isProductAvailabilityRequest() const
{
    if( 9999999 == this->KdAuftragNr() )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
/*  Construct an instance with a customer object instance pointer.            */
/*----------------------------------------------------------------------------*/
pxOrder :: pxOrder
(
    pxCustBase*          customer,
    const pxOrderValidTrans*   vtp,
    const long           n,
    const long           deliverydate,
    const OriginTypeEnum batchschreiben
)
    : pxDBRecord(customer->Session())
{
    Init();
    BatchSchreiben_ = batchschreiben;
    Customer_ = customer;               // copy customer object pointer
    SetNoCustDestruct();                // avoid its deletion during destruction
    IDFNr_    = Customer_->IDFNr();     // ensure IDF-NR is there
    KundenNr_ = Customer_->KundenNr();  // internal customer id
    VertriebsZentrumNr_ = Customer_->Vertriebszentrum();
    if ( vtp )                          // then valid order transaction ptr there
    {                                   // copy order type values
        KdAuftragArt_ = vtp->KdAuftragArt();
        KoArt_        = vtp->KoArt();
        BuchArt_      = vtp->BuchArt();
    }
    if (deliverydate > 0 )
    {
        DatumAuslieferung( nDate(deliverydate));
    }
    DafueAuftragNr_ = n;                // customer's own order number
    OpenOrder(cDBOPEN_INSERT);               // open order item entry
}
/*----------------------------------------------------------------------------*/
/*  Construct an instance with a customer object and a fix ordernumber        */
/*  Type 0 = OpenInfo as it is, 1 = OpenProforma, like OpenInfo but with more */
/*  rules and results                                                         */
/*----------------------------------------------------------------------------*/
pxOrder :: pxOrder
(
    pxSession*           session,
    pxCustBase*          customer,
    const enum TypeOfInfoOrder Type
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_ = pxOrder::PSEUDO_ORDER_NUMBER;
    Customer_ = customer;               // copy customer object pointer
    SetNoCustDestruct();                // avoid its deletion during destruction
    IDFNr_    = Customer_->IDFNr();     // ensure IDF-NR is there
    KundenNr_ = Customer_->KundenNr();  // internal customer id
    VertriebsZentrumNr_ = Customer_->Vertriebszentrum();
    if ( Type == INFO_ORDER_TYPE_PROFORMA )
    {
        OpenProforma();                  // open order without insert
    }
    else
    {
        OpenInfo();                      // open order without insert
    }
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrder :: pxOrder
(
    pxOrder& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAG structure to construct this instance.                      */
/*----------------------------------------------------------------------------*/
pxOrder :: pxOrder
(
    pxSession *session,
    tKDAUFTRAG& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
    FromPharmos();                      // Translate values from old PHARMOS
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxOrder :: pxOrder
(
    pxSession *session,
    long    KdAuftragNr,                 // Read via this type
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_ = KdAuftragNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrder :: ~pxOrder()
{
    if ( ItemList_ && IsGoodState() && false == IsOrderViewing() && false == isProductAvailabilityRequest())    // then order is not properly closed
    {
        Close(Order::LeaveAsIs);                // force close with old state
    }

    if( m_TourInfo )
    {
        delete m_TourInfo;
        m_TourInfo = NULL;
    }

    if( m_TourAssignmentUtil )
    {
        delete m_TourAssignmentUtil;
        m_TourAssignmentUtil = NULL;
    }

    if( m_OrderRelationNoList )
    {
        delete m_OrderRelationNoList;
        m_OrderRelationNoList = NULL;
    }

//  delete objects linked with this order:
    if ( ItemList_ )
        delete ItemList_;
    if ( ItemListProforma_ )
        delete ItemListProforma_;
    if ( ItemListTemporary_ )
        delete ItemListTemporary_;
    if ( Customer_ && !IsNoCustDestruct())
        delete Customer_;
    if ( ShuttleCustomer_ )
        delete ShuttleCustomer_;
    //if ( oeparam_ )
    //    delete oeparam_;
    if ( ItemQuery_ )
        delete ItemQuery_;
    //if ( AuxCompanyList_ )
    //    delete AuxCompanyList_;
    if ( TailText_ )
        delete TailText_;
    if ( HeadText_ )
        delete HeadText_;
    if ( RangeCollectList_ )
        delete RangeCollectList_;
    if ( StockReservTimeList_ )
        delete StockReservTimeList_;

    if ( SepOrderArtGroupList_ != NULL )
    {
        delete SepOrderArtGroupList_;
        SepOrderArtGroupList_ = NULL;
    }
    if ( CstDiscountAccount_ != NULL )
    {
        delete CstDiscountAccount_;
        CstDiscountAccount_ = NULL;
    }
    if ( TenderHead_ != NULL )
    {
        delete TenderHead_;
        TenderHead_ = NULL;
    }
    if ( OrdTaxValues_ != NULL )
    {
        delete OrdTaxValues_;
        OrdTaxValues_ = NULL;
    }
    if ( OrderDiscAccList_ != NULL )
    {
        delete OrderDiscAccList_;
        OrderDiscAccList_ = NULL;
    }
    if ( BalanceCollectList_ != NULL )
    {
        delete BalanceCollectList_;
        BalanceCollectList_ = NULL;
    }
    if ( ValuesCollectList_ != NULL )
    {
        delete ValuesCollectList_;
        ValuesCollectList_ = NULL;
    }
    if ( OrderValues_ != NULL )
    {
        delete OrderValues_;
        OrderValues_ = NULL;
    }
    if ( OrderCalcMode_ != NULL )
    {
        delete OrderCalcMode_;
        OrderCalcMode_ = NULL;
    }
    if ( OrderPosDiscountList_ != NULL )
    {
        delete OrderPosDiscountList_;
        OrderPosDiscountList_ = NULL;
    }
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAG structure.          */
/*----------------------------------------------------------------------------*/
tKDAUFTRAG&
Assign
(
    tKDAUFTRAG&    dest,
    const pxOrder& src
)
{

    src.State_.Export(dest.KdAuftragStat, mSIZEOF(tKDAUFTRAG, KdAuftragStat)-1);
    dest.KdAuftragNr              = src.KdAuftragNr_                          ;
    dest.IDFNr                    = src.IDFNr_                                ;
    dest.PersonalNr               = src.PersonalNr_                           ;
    dest.RechnungNr               = src.RechnungNr_                           ;
    dest.FilialNr                 = src.FilialNr_                             ;
    dest.KoArt                    = src.KoArt_                                ;
    dest.BuchArt                  = src.BuchArt_                              ;
    dest.DatumValuta              = src.DatumValuta_.GetYYYYMMDD()            ;
    dest.WertAuftrag              = src.WertAuftrag_                          ;
    dest.WertLieferung            = src.WertLieferung_                        ;
    dest.WertZeilen               = src.WertZeilen_                           ;
    dest.AnzPos                   = src.AnzPos_                               ;
    dest.AnzPosOB                 = src.AnzPosOB_                             ;
    dest.AnzPosDafue              = src.AnzPosDafue_                          ;
    dest.AnzPosDafueFehler        = src.AnzPosDafueFehler_                    ;
    dest.AnzAlphaText             = src.AnzAlphaText_                         ;
    dest.AnzBTM                   = src.AnzBTM_                               ;
    dest.RabattBarProz            = src.RabattBarProz_                        ;
    dest.ZeitEndeAM               = src.ZeitEndeAM_.GetHHMMSS()               ;
    dest.ZeitEndePM               = src.ZeitEndePM_.GetHHMMSS()               ;
    dest.BatchSchreiben           = src.BatchSchreiben_                       ;
    dest.HerkunftFiliale          = src.HerkunftFiliale_                      ;
    dest.DafueAuftragNr           = src.DafueAuftragNr_                       ;
    dest.VertriebszentrumNr       = src.VertriebsZentrumNr_                   ;
    dest.KundenNr                 = src.KundenNr_                             ;
    dest.KdAuftragNrFiliale       = src.KdAuftragNrFiliale_                   ;
    dest.SendeStatus              = static_cast<short>(src.SendeStatus_)      ;
    src.RCEntryDeffered_.Export(dest.ZuGrund, mSIZEOF(tKDAUFTRAG, ZuGrund)-1);
    dest.DatumAuslieferung        = src.DatumAuslieferung_.GetYYYYMMDD()      ;
    dest.KdAuftragNrOrg           = src.KdAuftragNrOrg_                       ;
    dest.DatumOrg                 = src.DatumOrg_.GetYYYYMMDD()               ;
    dest.BatchAuftragNr           = src.BatchAuftragNr_                       ;
    dest.KzRestored = (src.KzRestored_ ? '1' : '0');
    dest.AnzAuf                   = src.AnzAuf_                               ;
    dest.DatumValutaBatch         = src.DatumValutaBatch_.GetYYYYMMDD()       ;
    dest.ValutaMonAuto            = src.ValutaMonAuto_                        ;
    dest.ValutaMonManuell         = src.ValutaMonManuell_                     ;
    dest.TenderNo                 = src.TenderNo_                             ;
    dest.DatumVersand             = src.DatumVersand_.GetYYYYMMDD()           ;
    dest.DatumBTM                 = src.DatumBTM_.GetYYYYMMDD()               ;
    dest.WertNetto                = src.WertNetto_                            ;
    dest.WertRabatt               = src.WertRabatt_                           ;
    dest.PaymentDate              = src.PaymentDate_.GetYYYYMMDD()            ;
    dest.PaymentType              = src.PaymentType_                          ;
    dest.DriverID                 = src.DriverID_                             ;
    dest.LogisticVolume           = src.LogisticVolume_                       ;
    dest.DPODays                  = src.DPODays_                              ;
    dest.OrderPeriodID            = src.OrderPeriodID_                        ;

    strcpy(dest.GeraetName,    " ");
    strcpy(dest.TourId    ,    " ");
    strcpy(dest.TourIdAlt ,    " ");
    strcpy(dest.KdAuftragArt,  " ");
    strcpy(dest.GeraetName,    " ");
    strcpy(dest.Bemerkungen,   " ");
    strcpy(dest.NaechsteTour,  " ");
    strcpy(dest.LetzteTour,    " ");
    strcpy(dest.DafueGeraeteName," ");
    strcpy(dest.SubOrderType,  " ");
    strcpy(dest.PaymentTerm,   " ");
    strcpy(dest.BTMFormularNr,   " ");
    strcpy(dest.InvoiceNumber,   " ");
    strcpy(dest.XMLReferenceNo,   " ");
    strcpy(dest.OrderLabel, " ");

    src.GeraetName_.GetData(dest.GeraetName);
    src.OrderTourId_.GetData(dest.TourId);
    src.TourIdAlt_.GetData(dest.TourIdAlt);
    src.NaechsteTour_.GetData(dest.NaechsteTour);
    src.LetzteTour_.GetData(dest.LetzteTour);
    src.KdAuftragArt_.GetData(dest.KdAuftragArt);
    src.Bemerkungen_.GetData(dest.Bemerkungen);
    src.DafueGeraeteName_.GetData(dest.DafueGeraeteName);
    src.SubOrderType_.GetData(dest.SubOrderType);
    src.PaymentTerm_.GetData(dest.PaymentTerm);
    src.BTMFormularNr_.GetData(dest.BTMFormularNr);
    src.InvoiceNumber_.GetData(dest.InvoiceNumber);
    src.XMLReferenceNo_.GetData(dest.XMLReferenceNo);
    src.OrderLabel_.GetData(dest.OrderLabel);

    // Bit Map Exporting.
    // Define an array of longs be cause the flags must be exported in one array.
    unsigned long LongArray[cOrdFlagEntries];
    src.ETAuftragSchalter_.Export(LongArray, cOrdFlagEntries, cFlagBytesPerLong);

    // Copy flag longs into record structure:
    dest.ETAuftragSchalter1 = (long) LongArray[0];
    dest.ETAuftragSchalter2 = (long) LongArray[1];
    dest.ETAuftragSchalter3 = (long) LongArray[2];
    dest.ETAuftragSchalter4 = (long) LongArray[3];
    dest.ETAuftragSchalter5 = (long) LongArray[4];
    dest.ETAuftragSchalter6 = (long) LongArray[5];

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAG structure to pxOrder object     */
/*----------------------------------------------------------------------------*/
pxOrder&
Assign
(
    pxOrder&          dest,
    const tKDAUFTRAG& src
)
{
    dest.State_.Import(src.KdAuftragStat, mSIZEOF(tKDAUFTRAG, KdAuftragStat)-1);
    dest.RCEntryDeffered_.Import(src.ZuGrund, mSIZEOF(tKDAUFTRAG, ZuGrund)-1);

    dest.KdAuftragNr_             = src.KdAuftragNr                           ;
    dest.IDFNr_                   = src.IDFNr                                 ;
    dest.GeraetName_              = src.GeraetName                            ;
    dest.OrderTourId_             = src.TourId                                ;
    dest.TourIdAlt_               = src.TourIdAlt                             ;
    dest.PersonalNr_              = src.PersonalNr                            ;
    dest.RechnungNr_              = src.RechnungNr                            ;
    dest.FilialNr_                = src.FilialNr                              ;
    dest.KdAuftragArt_            = src.KdAuftragArt                          ;
    dest.KoArt_                   = src.KoArt                                 ;
    dest.BuchArt_                 = src.BuchArt                               ;
    dest.DatumValuta_             = nDate(src.DatumValuta)                    ;
    dest.WertAuftrag_             = src.WertAuftrag                           ;
    dest.WertLieferung_           = src.WertLieferung                         ;
    dest.WertZeilen_              = src.WertZeilen                            ;
    dest.AnzPos_                  = src.AnzPos                                ;
    dest.AnzPosOB_                = src.AnzPosOB                              ;
    dest.AnzPosDafue_             = src.AnzPosDafue                           ;
    dest.AnzPosDafueFehler_       = src.AnzPosDafueFehler                     ;
    dest.AnzAlphaText_            = src.AnzAlphaText                          ;
    dest.AnzBTM_                  = src.AnzBTM                                ;
    dest.RabattBarProz_           = src.RabattBarProz                         ;
    dest.ZeitEndeAM_              = src.ZeitEndeAM                            ;
    dest.ZeitEndePM_              = src.ZeitEndePM                            ;
    dest.BatchSchreiben_          = static_cast<OriginTypeEnum>(src.BatchSchreiben);
    dest.Bemerkungen_             = src.Bemerkungen                           ;
    dest.HerkunftFiliale_         = src.HerkunftFiliale                       ;
    dest.NaechsteTour_            = src.NaechsteTour                          ;
    dest.LetzteTour_              = src.LetzteTour                            ;
    dest.DafueAuftragNr_          = src.DafueAuftragNr                        ;
    dest.DafueGeraeteName_        = src.DafueGeraeteName                      ;
    dest.VertriebsZentrumNr_      = src.VertriebszentrumNr                    ;
    dest.KundenNr_                = src.KundenNr                              ;
    dest.KdAuftragNrFiliale_      = src.KdAuftragNrFiliale                    ;
    dest.SendeStatus_             = static_cast<pxOrder::OrderSendStatusEnum>(src.SendeStatus);
    dest.DatumAuslieferung_       = nDate(src.DatumAuslieferung)              ;
    dest.KdAuftragNrOrg_          = src.KdAuftragNrOrg                        ;
    dest.DatumOrg_                = nDate(src.DatumOrg)                       ;
    dest.BatchAuftragNr_          = src.BatchAuftragNr                        ;
    dest.KzRestored_              = src.KzRestored                            ;
    dest.SubOrderType_            = src.SubOrderType                          ;
    dest.PaymentTerm_             = src.PaymentTerm                           ;
    dest.AnzAuf_                  = src.AnzAuf                                ;
    dest.DatumValutaBatch_        = nDate(src.DatumValutaBatch)               ;
    dest.ValutaMonAuto_           = src.ValutaMonAuto                         ;
    dest.ValutaMonManuell_        = src.ValutaMonManuell                      ;
    dest.TenderNo_                = src.TenderNo                              ;
    dest.DatumVersand_            = nDate(src.DatumVersand)                   ;
    dest.DatumBTM_                = nDate(src.DatumBTM)                       ;
    dest.BTMFormularNr_           = src.BTMFormularNr                         ;
    dest.WertNetto_               = src.WertNetto                             ;
    dest.WertRabatt_              = src.WertRabatt                            ;
    dest.InvoiceNumber_           = src.InvoiceNumber                         ;
    dest.PaymentDate_             = nDate(src.PaymentDate)                    ;
    dest.PaymentType_             = src.PaymentType                           ;
    dest.DriverID_                = src.DriverID                              ;
    dest.XMLReferenceNo_          = src.XMLReferenceNo                        ;
    dest.LogisticVolume_          = src.LogisticVolume                        ;
    dest.OrderLabel_              = src.OrderLabel                            ;
    dest.DPODays_                 = src.DPODays                               ;
    dest.OrderPeriodID_           = src.OrderPeriodID                         ;

    // Bit Maps:

    // define an array of longs to ensure the flags being stored in one array:
    unsigned long LongArray[cOrdFlagEntries];
    LongArray[0] = (unsigned long)src.ETAuftragSchalter1;  // copy flag longs from record struct
    LongArray[1] = (unsigned long)src.ETAuftragSchalter2;
    LongArray[2] = (unsigned long)src.ETAuftragSchalter3;
    LongArray[3] = (unsigned long)src.ETAuftragSchalter4;
    LongArray[4] = (unsigned long)src.ETAuftragSchalter5;
    LongArray[5] = (unsigned long)src.ETAuftragSchalter6;
    // Import flagssrc. into bit map:
    dest.ETAuftragSchalter_.Import(LongArray, cOrdFlagEntries, cFlagBytesPerLong);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures list objects being inserted/sorted in a sequence actually fixed   */
/*  in the pxOrderList object or to be passed as 'lparm'.                     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CompareTo
(
    const nCollectable   *That,
          void           *p,
    const long           lparm
)   const
{
    if ( pxGlobalDataBaseSort )
        return  0;

    pxOrderList *listp = (pxOrderList*) p;
    pxOrder *that = (pxOrder*)That;
    int retval = 0;
    pxOrderList::SortFields sf = listp->SortOrder();  // sort order from list object
    if ( lparm != cDEFAULT )            // then lparm is not default, use it
        sf = (pxOrderList::SortFields) lparm;   // to take the sort field spec
    switch (sf)
    {
    case pxOrderList::SortIDFNr:
        retval = (IDFNr_ == that->IDFNr_) ? 0
               : (IDFNr_ > that->IDFNr_ ? 1 : -1);
        if ( retval == 0 )
            retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
                   : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);
        break;

    case pxOrderList::SortTourId:
        retval = (OrderTourId_ == that->OrderTourId_) ? 0 : (OrderTourId_ > that->OrderTourId_ ? 1 : -1); // const
        if ( retval == 0 )
            retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
                   : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);
        break;

    case pxOrderList::SortBusyTime:
        retval = (OrderTourId_ == that->OrderTourId_) ? 0 : (OrderTourId_ > that->OrderTourId_ ? 1 : -1); // const
        if ( retval == 0 )
        {
            nClock   now;
            now += 30L * 60;
            retval = (EndAM() == that->EndAM()) ? 0
                   : (EndAM() > that->EndAM() ? 1 : -1);

            if ( now > EndAM() && now > that->EndAM() )
                retval = (EndPM() == that->EndPM()) ? 0
                       : (EndPM() > that->EndPM() ? 1 : -1);
        }
        if ( retval == 0 )
            retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
                   : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);
        break;

    default:
        retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
               : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrder :: Init()
{
    tKDAUFTRAG    record;
    memset(&record, 0 , sizeof(tKDAUFTRAG));
    Assign(*this, record);              // init object data fields

    m_NormalDeliveryTourInfo = TourInfo();
    m_TourAssignmentUtil = NULL;
    m_TourInfo = NULL;
    m_OrderRelationNoList = NULL;

    Customer_         = NULL;
    ShuttleCustomer_  = NULL;
    ItemList_         = NULL;
    ItemListProforma_ = NULL;
    ItemListTemporary_ = NULL;
    HeadText_         = NULL;
    TailText_         = NULL;
    Route_            = NULL;
    OrderType_        = NULL;
    CommType_         = NULL;
    StockTrans_       = NULL;
    CloseOptions_     = 0;
    laststock_        = 0;
    auxstock_         = 0;
    auxfil_           = 0;
    subArticleNo_     = 0;
    DefektWert_       = 0;
    ItemQuery_            = NULL;
//    AuxCompanyList_       = NULL;
    RangeCollectList_     = NULL;
    StockReservTimeList_  = NULL;
    SepOrderArtGroupList_ = NULL;
    CstDiscountAccount_   = NULL;
    TenderHead_           = NULL;
    OrdTaxValues_         = NULL;
    OrderDiscAccList_     = NULL;
    BalanceCollectList_   = NULL;
    ValuesCollectList_    = NULL;
    OrderValues_          = NULL;
    OrderCalcMode_        = NULL;
    OrderPosDiscountList_ = NULL;
    DateTimeCreated_ = 0;
    pflags_.Resize(bPFL_MAPWIDTH);
    GeraetName_    = Session()->Device()->Name();
    GeraetName_.Strip();
    PersonalNr_    = Session()->PersonnelNo();
    FilialNr_      = Session()->Branch()->FilialNr();
    KdAuftragArt_.Clear();
    DafueAuftragNr_ = 0;
    SubOrderType_.Clear();
    PseudoLock_      = false;
    BGInfoOrder_      = false;
    DoNotSplittOrder_ = false;
    FirstTransPos_ = 0;
    ROMainCstNo_   = 0;
    ROChain_       = 0;
    RODateFrom_ = pxConstants::NullDate;
    RODateTo_   = pxConstants::NullDate;
    ChangedToCashOrder_ = false;
    UpdateDebtlimitK2_  = false;
    UpdateDebtlimitK1_  = false;
    PaymentType_ = '0';
    DeliveryDatePreset_  = false;
    CstIBTDeliveryTime_  = 0;
    CstIBTDeliveryDate_  = 0;
    CstIBTTourDate_ = 0;
    NoDebtLimitCheck_    = false;
    EventCode_        = pxEventReason::NoReasonCode;
    DLPercentage_ = 0;
    OrderValue_ = 0;
    CustomerDebtLimit_ = 0;
    UsedCustomerCredit_ = 0;
    ApprovalsNeeded_ = 0;
    IsReleased_ = false;
    DiscussionNeeded_ = false;
    NoCreditLimitCheck_ = false;
}

/*----------------------------------------------------------------------------*/
IbtRequestHandler pxOrder::getIbtRequestHandler()
{
    return m_IbtRequestHandler;
}

/*----------------------------------------------------------------------------*/
pxOrderRelationNoList* pxOrder::getOrderRelationNoList()
{
    if( NULL == this->m_OrderRelationNoList )
    {
        m_OrderRelationNoList = new pxOrderRelationNoList( this->Session() );
    }
    return this->m_OrderRelationNoList;
}

/*----------------------------------------------------------------------------*/
long pxOrder::getPurchaseOrderNo()
{
    long retval = 0;
    if( this->getOrderRelationNoList()->SelectOrderRelationNoByOrderNoAndType( this->KdAuftragNr(), ePurchaseOrderNo ) )
    {
        if( this->getOrderRelationNoList()->Entries() > 0 )
        {
            pxOrderRelationNoListIter iter(*this->getOrderRelationNoList());
            pxOrderRelationNo* it = (pxOrderRelationNo*)++iter;
            if( it )
            {
                retval = it->RelationNo();
            }
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
bool pxOrder::setPurchaseOrderNo( const long purchaseorderno )
{
    if (0 == purchaseorderno)
    {
        return false;
    }
    if( this->getOrderRelationNoList()->SetOrderRelationNo( this->KdAuftragNr(), purchaseorderno, ePurchaseOrderNo ) )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
long pxOrder::getIVCVoucherNo()
{
    return getOrderRelationNo( eIVCVoucherNo );
}

/*----------------------------------------------------------------------------*/
bool pxOrder::setIVCVoucherNo( const long ivcvoucherno )
{
    return setOrderRelationNo( eIVCVoucherNo, ivcvoucherno );
}

/*----------------------------------------------------------------------------*/
bool pxOrder::removeIVCVoucherNo()
{
    return removeOrderRelationNo( eIVCVoucherNo );
}

/*----------------------------------------------------------------------------*/
long pxOrder::getOriginalInvoiceNo()
{
    return getOrderRelationNo( eOriginalInvoiceNo );
}

/*----------------------------------------------------------------------------*/
bool pxOrder::setOriginalInvoiceNo( const long originalinvoiceno )
{
    return setOrderRelationNo( eOriginalInvoiceNo, originalinvoiceno );
}

/*----------------------------------------------------------------------------*/
bool pxOrder::removeOriginalInvoiceNo()
{
    return removeOrderRelationNo( eOriginalInvoiceNo );
}

/*----------------------------------------------------------------------------*/
long pxOrder::getOrderRelationNo( OrderRelationNoTypeEnum type )
{
    long retval = 0;
    if( this->getOrderRelationNoList()->SelectOrderRelationNoByOrderNoAndType( this->KdAuftragNr(), type ) )
    {
        if( this->getOrderRelationNoList()->Entries() > 0 )
        {
            pxOrderRelationNoListIter iter(*this->getOrderRelationNoList());
            pxOrderRelationNo* it = (pxOrderRelationNo*)++iter;
            if( it )
            {
                retval = it->RelationNo();
            }
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
bool pxOrder::setOrderRelationNo( OrderRelationNoTypeEnum type, const long relationno )
{
    if( this->getOrderRelationNoList()->SetOrderRelationNo( this->KdAuftragNr(), relationno, type ) )
    {
        return true;
    }
    return false;
}

/*----------------------------------------------------------------------------*/
bool pxOrder::removeOrderRelationNo( OrderRelationNoTypeEnum type )
{
    return this->getOrderRelationNoList()->RemoveOrderRelationNo( this->KdAuftragNr(), type );
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tKDAUFTRAG struct   */
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxOrder&
pxOrder :: operator=( const pxOrder& src)
{
    tKDAUFTRAG    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAG structure 'src' to this instance.     */
/*----------------------------------------------------------------------------*/
pxOrder&
pxOrder :: operator=( const tKDAUFTRAG& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrder :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAG record;
    memset(&record, 0, sizeof(tKDAUFTRAG));
    record.KdAuftragNr = KdAuftragNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
    {
        (*this)= record;                 // import the data from tKDAUFTRAG struct
        FromPharmos();                   // Translate values from old PHARMOS

        // Read branch into session
        pxBranch CustBranch(Session(), Vertriebszentrum());
        if (CustBranch.IsGoodState())
        {
            *(Session()->Branch()) = CustBranch;
        }
    }
    else if ( retval > cDBXR_NORMAL )
        DBCondition(nMessage(CMsgStream(), CMSG_ORD_NOTFOUND, KdAuftragNr_),retval);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: Put()
{
    int retval = cDBXR_IOERROR;
    tKDAUFTRAG record;
    InitOrderMaster(record);

    if (0 == KdAuftragNr_)                  // then its a new order
    {
        pxNumber number(Session());        // construct a emptynumber object
        while (retval != cDBXR_NORMAL)
        {
            KdAuftragNr_ = number.GetNextNumberFromSequence(cNUM_Auftrag); // and assign an order number
            if ( KdAuftragNr_ > 0 )
            {
                ToPharmos();                     // Translate values for old PHARMOS
                Assign(record, *this);           // export object values
                retval = nDBWrite(&record, sizeof(tKDAUFTRAG));
            }
        }
    }
    else
    {
        record.KdAuftragNr = KdAuftragNr_; // primary key
        retval = nDBReadLock(&record);   // read-lock record for subsequent update
        if ( (retval == cDBXR_NORMAL) && (KdAuftragNr_ > 0) )
        {
            ToPharmos();                     // Translate values for old PHARMOS
            Assign(record, *this);           // export object values
            retval = nDBWrite(&record, sizeof(tKDAUFTRAG));
        }
    }
/*----------------------------------------------------------------------------*/
/*  Error check. In case of a fatal data base error, the nDBRecord base class */
/*  already did a diagnostic. Since we do not allow any error during write, an*/
/*  unsuccessful return code forces a diagnostic to be taken.                 */
/*----------------------------------------------------------------------------*/
    if ( retval > cDBXR_NORMAL )
        DataBase()->nDBDiagnostic(Error()); // retrieve diag from the database

    getCSCOrderFlagsRepository()->saveCSCOrderFlags( getCSCOrderFlags() );

    return retval;
}

void pxOrder :: InitOrderMaster(tKDAUFTRAG& rp)
{
    memset(&rp, 0, sizeof(tKDAUFTRAG));

    rp.KdAuftragStat     [0] = '0';
    rp.GeraetName        [0] = ' ';
    rp.TourId            [0] = ' ';
    rp.TourIdAlt         [0] = ' ';
    rp.MatchCode         [0] = ' ';
    rp.KdAuftragArt      [0] = ' ';
    rp.KoArt                 = '0';
    rp.BuchArt               = '0';
    rp.LagernrRechnung       = ' ';
    rp.SKdDefektAbsagen      = ' ';
    rp.Bemerkungen       [0] = ' ';
    rp.KundeText         [0] = ' ';
}

int pxOrder::Read(const void *record)
{
    return pxAuftragRead((tKDAUFTRAG*)record);
}

int pxOrder::ReadLock(const void *record)
{
    return pxAuftragReadLock((tKDAUFTRAG*)record);
}

int pxOrder::Insert(const void *record)
{
    return pxAuftragInsert((tKDAUFTRAG*)record);
}

int pxOrder::Update(const void *record)
{
    return pxAuftragUpdate((tKDAUFTRAG*)record);
}

short pxOrder::FilialNr()
{
    return FilialNr_ = Customer_->FilialNr();
}
/*----------------------------------------------------------------------------*/
/*  Subtract quantity q from AnzPosDafue. Returns quantity subtracted.        */
/*----------------------------------------------------------------------------*/
long
pxOrder :: SubAnzPosDafue
(
    const long q                      // quantity to be subtracted
)
{
    long retval;
    // avoid negative values in stock:
    retval = ( AnzPosDafue_ - q < 0 ) ? AnzPosDafue_ : q;
    AnzPosDafue_ -= retval;
    SetDirty();
    return retval;
}
