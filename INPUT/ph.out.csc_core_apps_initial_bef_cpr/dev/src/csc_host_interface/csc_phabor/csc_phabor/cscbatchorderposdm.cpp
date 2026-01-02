//-------------------------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief      main interface for domain module of ifxorderheads (table pharmosbatchorderheads)
 *  \author     Julian Machata
 *  \date       17.10.2012
 */
//-------------------------------------------------------------------------------------------------------------------//

#include "cmndm.h"
#include <icsc_logger.h>
#include <csc_logger.h>

#include "cscbatchorderposdm.h"
#include "property_definitions.h"
#include "pharmosbatchorderposacc_definitions.h"
#include "cscbatchorderdm_definitions.h"
#include "ipxvbsession.h"
#include "ipxvbordertransmitptr.h"
#include "ipxvbordertransmit.h"
#include "pxvbordertransmit.h"
#include "icscorderobjectgetter.h"
#include "orderprocessingexception.h"
#include "pxitemdiscount.hpp"
#include "pxcustinf.hpp"
#include "pxoeparm.hpp"
#include "pxcstbas.hpp"
#include "pxcstot.hpp"
#include "pxdiscountdef.h"
#include "types/messagecodeenum.inc"
#include "pxartacc.hpp" // TODO FN remove dependency (article account)
#include <pxrecord.h>
#include <pxbase/pxconstants.hpp>
#include <pxcomtyp.hpp>
#include <pxstktra.hpp>

namespace domMod
{
namespace batchOrder
{
namespace processing
{

    using ::pxVerbund::subsequentDelivery::pxDeliveryPos;

//-------------------------------------------------------------------------------------------------------------------//
CSCBatchOrderPosDM::CSCBatchOrderPosDM(libcsc_utils::ICSC_LoggerPtr csc_logger)
:   m_CSC_Logger        ( csc_logger ),
    m_ArticleNotOnStore ( false )
{
    METHODNAME_DEF( CSCBatchOrderPosDM, CSCBatchOrderPosDM );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
CSCBatchOrderPosDM::~CSCBatchOrderPosDM()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, ~CSCBatchOrderPosDM );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::doInit( const InitParamsDMPtr initParamsDM )
{
    METHODNAME_DEF( CSCBatchOrderPosDM, doInit );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    m_InitParamsDMPtr = initParamsDM;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::doShutdown()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, doShutdown );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
}

//--------------------------------------------------------------------------------------------------//
// HELPER
//--------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::activateOrder(  const basar::VarString orderType,
                                         const basar::VarString orderNumber,
                                         basar::Int32 pickingType,
                                         basar::Int32 bookingType,
                                         OriginTypeEnum originTypeID )
{
    METHODNAME_DEF( CSCBatchOrderPosDM, activateOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    basar::VarString strPickingType = "";
    basar::VarString strBookingType = "";

    strPickingType.itos(pickingType);
    strBookingType.itos(bookingType);

    pxOrder* order = getPxOrder();
    order = getPxOrderTransmit()->get()->OrderType(     orderType.c_str(),
                                                        orderNumber.c_str(),
                                                        strPickingType[0],
                                                        strBookingType[0],
                                                        originTypeID );

    setPxOrder( order );

    if ( 0 == order )
    {
        basar::VarString msg = "DB error when activatng order while processing pos!";
        throw csc_phabor::exception::OrderProcessingException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
    }
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderPosDM::isBatchOrder()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, isBatchOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return getPxOrderParameter()->Wert() == m_pxOrder->BatchSchreiben();
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderPosDM::isParameterSet()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, isParameterSet );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return ( 0 != getPxOrderParameter() );
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderPosDM::isOrderSet()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, isOrderSet );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return ( 0 != m_pxOrder );
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderPosDM::isItemSet()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, isItemSet );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return ( 0 != m_pxOrderItem );
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderPosDM::hasQuantity()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, hasQuantity );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_pxOrderItem->IsQStateNotOnHand();
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderPosDM::hasToSetComment()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, hasToSetComment );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return (( m_pxOrder->OrderType().IsTransfer() || m_pxOrder->OrderType().IsScheduleQuantity()) && !m_ArticleNotOnStore && isRestDelivery() );
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderPosDM::isRestDelivery()
{
    pxCustBase&            customer    = *m_pxOrder->Customer();
    const pxCustOrderType& orderType   = m_pxOrder->OrderType();
    pxArtBase*             art         = m_pxOrderItem->ArtBase();

    // ignore special order types...
   if ( m_pxOrder->BatchSchreiben() == cORTYPE_KOMMI_ERROR    ||
        m_pxOrder->BatchSchreiben() == cORTYPE_PARENT_COMPANY ||
        m_pxOrder->BatchSchreiben() == cORTYPE_INSTALLER      ||
        m_pxOrder->BatchSchreiben() == cORTYPE_CLEARING       ||
        m_pxOrder->BatchSchreiben() == cORTYPE_FR_CUSTOMER_ORDER )
   {
       return false;
   }
   // check customer configuration
   if ( ( customer.IsIgnoreRestDeliveryService() || customer.IsNotRestDeliveryUser() ) && !orderType.IsSAlwaysRestDel() )
   {
       return false;
   }
   // artikelaktiv = 2
   if ( art != NULL && art->IsGoodState() && art->IsAktivAndNotOnStore() )
   {
       return false;
   }

   return true;
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderPosDM::isQuantityOk()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, isQuantityOk );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return ( m_pxOrderItem->MengeGeliefert() > 0 && !m_pxOrder->Param()->IsBatchTeilMenge() );
}

//-------------------------------------------------------------------------------------------------------------------//
//bool CSCBatchOrderPosDM::isOriginForSubsequentDelivery()
//{
    //METHODNAME_DEF( CSCBatchOrderPosDM, isOriginForSubsequentDelivery );
    //BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    //return (m_pxOrder->BatchSchreiben() == cORTYPE_GLOBUS_ORDER ||
    //        m_pxOrder->BatchSchreiben() == cORTYPE_EDIFAC_ORDER ||
     //       m_pxOrder->BatchSchreiben() == cORTYPE_PARENT_COMPANY);
//}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderPosDM::isIBTOrder()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, isIBTOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return ( m_pxOrder->BatchSchreiben() == cORTYPE_AUXILIARY );
}

//-------------------------------------------------------------------------------------------------------------------//
bool CSCBatchOrderPosDM::hasToConstructDeliveryPos()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, hasToConstructDeliveryPos );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return (    m_pxOrderItem->Order().BatchSchreiben() == cORTYPE_AUXILIARY    || /* VB */
                m_pxOrderItem->Order().BatchSchreiben() == cORTYPE_GLOBUS_ORDER || /* GO */
                m_pxOrderItem->Order().BatchSchreiben() == cORTYPE_EDIFAC_ORDER || /* ES */
                m_pxOrderItem->Order().BatchSchreiben() == cORTYPE_PARENT_COMPANY ); /* SH */
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::addOrderItem()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, addOrderItem );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_pxOrderItem = m_pxOrder->NewOrderItem_07( (long) getArticleNo(),
                                                (long) getQuantity(),
                                                (long) getQuantityInKind(),
                                                (long) getBatchOrderNo(),
                                                (long) getBatchOrderPosNo() );
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::updateArticleData()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, updateArticleData );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    try {
        pxArtBase* art = m_pxOrderItem->ArtBase();

        if (art)
        {
            if (art->IsGoodState())
            {
                if (art->IsAktivAndNotOnStore() )
                {
                    m_ArticleNotOnStore = true;
                }
                getPxVbSession()->get()->getStockBooking()->CancelReservationForOpenOrder(*m_pxOrderItem, m_pxOrderItem->MengeGeliefert());
            }
        }

    } catch ( csc_phabor::exception::OrderProcessingException& ex ) {
        throw ex;
    } catch ( ... ) {
        basar::VarString msg = "unknown error when processing orderhead!";
        throw csc_phabor::exception::OrderProcessingException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
    }
}

//-------------------------------------------------------------------------------------------------------------------//
//void CSCBatchOrderPosDM::createDeliveryPos()
//{
 //   METHODNAME_DEF( CSCBatchOrderPosDM, createDeliveryPos );
   // BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    // Construct NachLieferPos
    //pxDeliveryPos deliveryPos ( *m_pxOrderItem, ::pxVerbund::subsequentDelivery::pxDPT_BATCH_ITEM );
    //tNACHLIEFERPOS position_;

    // We must change some values.
    //Assign(position_, deliveryPos);

    //position_.IDFNr             = getCustomerNo();
    //position_.FilialNr1         = getOriginalBranchno();
    //position_.FilialNr2         = static_cast<basar::Int16>(get1stIBTPartner().stoi());
    //position_.FilialNr3         = static_cast<basar::Int16>(get2ndIBTPartner().stoi());
    //position_.UrsprungAuftragNr = getCustomerOrderNo();
    //position_.UrsprungPosNr     = getCustomerPosNo();

    //Assign(deliveryPos, position_);

    // Finally write it.
    //deliveryPos.Put();
//}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::createDeliveryPosByCustomer()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, createDeliveryPosByCustomer);
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    pxDeliveryPos*         deliveryPos = NULL;
    nDate                  today;
    pxArtBase*             art         = m_pxOrderItem->ArtBase();

    // Construct NachLieferPos
    deliveryPos = m_pxOrderItem->AuxDelList()->Find(m_pxOrderItem->KdAuftragNr(), m_pxOrderItem->PosNr(),
        ::pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
    if (deliveryPos != NULL)
    {
        deliveryPos->nDBBeginTransaction(cDBTransRecord);
       if ( deliveryPos->Get(cDBGET_FORUPDATE) == 0 ) // read and lock deliverypos
       {
            if ( m_pxOrderItem->MengeBestellt() != deliveryPos->Menge() &&
                 !m_pxOrder->Param()->IsBatchTeilMenge() )
            {
                createArticleAccRestDelivery(art);
            }
            tNACHLIEFERPOS position_;
            memset(&position_, 0, sizeof(tNACHLIEFERPOS));
            // We must change some values.
            nString itemtxt ( getItemText().c_str() );
            itemtxt.Strip();
            Assign(position_, *deliveryPos);
            position_.Menge          = m_pxOrderItem->MengeBestellt()-m_pxOrderItem->MengeGeliefert();
            position_.MengeNatra     = getQuantityInKind();
            position_.Bemerkungen[0] = ' ';
            itemtxt.GetData(position_.Bemerkungen);
            if ( m_pxOrderItem->PreisEKApoNetto() > pxConstants::mZero  )
            {
                position_.PreisEKApoNetto = m_pxOrderItem->PreisEKApoNetto();
            }
            Assign(*deliveryPos, position_);
            // Finally write it.
            deliveryPos->Put();
            deliveryPos->nDBCommit(cDBTransRecord);
       }
    }
    else
    {
       if (!isRestDelivery())
       {
            return;
       }
       pxDeliveryPos delivery_(*m_pxOrderItem, ::pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
       tNACHLIEFERPOS pos_;
       memset(&pos_, 0, sizeof(tNACHLIEFERPOS));
       // We must change some values.
       nString itemtxt (getItemText().c_str());
       itemtxt.Strip();
       Assign(pos_, delivery_);
       pos_.Menge          = m_pxOrderItem->MengeBestellt()-m_pxOrderItem->MengeGeliefert();
       pos_.MengeNatra     = getQuantityInKind();
       pos_.Bemerkungen[0] = ' ';
       itemtxt.GetData(pos_.Bemerkungen);
       if ( delivery_.KdAuftragArt() != "NO" )
       {
          pos_.PreisEKApo = m_pxOrderItem->PreisEKApo();
          pos_.PreisVKApo = m_pxOrderItem->PreisVKApo();
          pos_.PreisAGP   = m_pxOrderItem->PreisAGP();
       }
       if ( m_pxOrderItem->PreisEKApoNetto() > pxConstants::mZero )
       {
          pos_.PreisEKApoNetto = m_pxOrderItem->PreisEKApoNetto();
       }
       Assign(delivery_, pos_);
       // Finally write it.
       delivery_.Put();
       if ( delivery_.IsGoodState() )
       {
          m_pxOrderItem->SetNachliefern();
       }
       createArticleAccRestDelivery(art);
       // write protocol
       pxDeliveryLog dlog(*m_pxOrderItem, delivery_);
       dlog.Put();
    }
}

//-------------------------------------------------------------------------------------------------------------------//
    void CSCBatchOrderPosDM::createArticleAccRestDelivery( pxArtBase* art )
    {
        enum BookingTypeEnum st = m_pxOrder->StockTrans().StockTransactionCode();
        enum PickingTypeEnum ct = m_pxOrder->CommType().ShipCode();

        pxArtAccount acct(m_pxOrder->Session(), TRANSACTIONTYPE_SUPPLY);
        if ( acct.IsGoodState() )
        {
            acct.FilialNr(art->FilialNr());
            acct.ArtikelNr(art->ArtikelNr());
            acct.Menge(((m_pxOrderItem->MengeBestellt())-(m_pxOrderItem->MengeGeliefert())));
            acct.IDFNr(m_pxOrder->IDFNr());
            long qtyAvailable = m_pxOrder->Session()->getStockBooking()->GetAvailableQtyInStock(*art);
            long qtyReserved = m_pxOrder->Session()->getStockBooking()->GetReservedQtyInStock(*art);
            acct.MengeNeu(qtyAvailable + qtyReserved);  // set current stock amount
            acct.StockReserved(qtyReserved);  // set current stock amount
            acct.BelegNr(m_pxOrder->KdAuftragNr());
            acct.PosNr(m_pxOrderItem->PosNr());
            acct.Uid(0);
            acct.TransActionKey(st,ct);
            acct.Put();
            m_pxOrderItem->SetBewegungsArt(acct.BewegungsArt());
        }
    }

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::checkArticle()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, checkArticle );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    pxArtBase* article = m_pxOrderItem->ArtBase();
    if ( article )
    {
        if (!article->IsGoodState())
        {
            basar::VarString obranch = "";
            basar::VarString strArticle = "";
            obranch.itos(getOriginalBranchno());
            strArticle.ltos(m_pxOrderItem->ArtikelNr());
            basar::VarString msg = "Article not good state for Original Branch! Article: " + strArticle + " Original Branch: " + obranch;
            m_CSC_Logger->log(log4cplus::ERROR_LOG_LEVEL, msg.c_str());
        }
    }
}


//--------------------------------------------------------------------------------------------------//
// SETTER
//--------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::injectICSCOrderObjectGetter( domMod::batchOrder::util::ICSCOrderObjectGetterPtr cscOrderObjectGetter )
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, injectICSCOrderObjectGetter );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_CscOrderObjectGetter = cscOrderObjectGetter;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::setArticleCodeValues()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setArticleCodeValues );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_pxOrderItem->SetArticleCodeValues( (const short) getArticleType(), getArticleCode().c_str() );
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::setItemText( bool checkQty)
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setItemText );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

     // BAP-PTEXT into pxorderitem::Bemerkungen
    basar::VarString itemtxt = getItemText();
    itemtxt.trim( basar::cmnutil::BString::FIRST_END );
    if ( m_pxOrder->OrderType().IsRestDel() )
    {
        createDeliveryPosByCustomer();    // Restdelivery // INC-039882 gotta test first!
    }

    pxArtBase* art = m_pxOrderItem->ArtBase();
    if ( art->IsAktivAndNotOnStore() && checkQty )
    {
        m_ArticleNotOnStore = true;
    }

    //put the text in Bemerkungen
    if ( hasToSetComment() )
    {
        nMessage msg( m_pxOrderItem->CMsgStream(), CMSG_ITM_RESTDELIVERY_COMES );
        nString posbem = msg.String();
        posbem.Compress('\n');
        char temp[30];
        int templen = sprintf( temp,"%ld+%ld %s", m_pxOrderItem->MengeBestellt(), (long) getQuantityInKind(), (char*)posbem );
        temp[templen] = '\0';
        if ( itemtxt.empty() )
        {
            itemtxt+=temp;
        }
        else if (!this->getPxOrder()->OrderType().IsTransfer())
        {
            itemtxt = itemtxt+" "+temp;
        }
    }

    nString note = nString( itemtxt.c_str()); // AIX Error
    m_pxOrderItem->Bemerkungen( note );
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::setQuantities()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setQuantities );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_pxOrderItem->CalcConditions();
    m_pxOrderItem->MengeGeliefert(0L);
    m_pxOrderItem->MengeAbgebucht(0L);
    m_pxOrderItem->MengeBestaetigt(0L);
    m_pxOrderItem->MengeNatra(0L);
    m_pxOrderItem->MengeNatraGrossH(0L);
    m_pxOrderItem->MengeNatraHerst(0L);
    m_pxOrderItem->ClearToCommission();
    m_pxOrderItem->CancelAuxPosting();
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::setItemPrices()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setItemPrices );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    // set AEP (kdauftragpos.preisekapo)
    basar::Decimal pharmacyPurchasePrice = getPharmacyPurchasePrice();
    if (pharmacyPurchasePrice > basar::Decimal(0))
    {
        m_pxOrderItem->SetPreisEKApo(pharmacyPurchasePrice.toFloat64());
    }

    // set FAP (fixed) (kdauftragpos.preisfaktur)
    basar::Decimal invoicePrice = getInvoicePrice();
    if (invoicePrice > basar::Decimal(0) || getPriceZero() == 1)
    {
        m_pxOrderItem->SetPreisFakturFixed(invoicePrice.toFloat64());
    }
}

//-------------------------------------------------------------------------------------------------------------------//

void CSCBatchOrderPosDM::setItemDiscount()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setPrices );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    // add item discount (kdauftragposrab)
    if (m_pxOrderItem->MengeGeliefert() > 0)
    {
        basar::Decimal discountPercent = getDiscountPercentage();
        if (discountPercent > basar::Decimal(0))
        {
            nString pharmacyGroupId = "000";
            pxItemDiscount* itemDiscount = new pxItemDiscount(
                m_pxOrder->Session(),
                m_pxOrder->KdAuftragNr(),
                m_pxOrderItem->PosNr(),
                BestBuy_ValuePctCash,
                pharmacyGroupId);
            itemDiscount->SetDiscountValuePct(discountPercent.toFloat64());
            itemDiscount->Put();
            m_pxOrderItem->ItemDiscountList()->Append(itemDiscount);
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::setBatchOrderInfo()
{
    METHODNAME_DEF( CSCBatchOrderHeadDM, setBatchOrderInfo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    basar::Int32 orderNo = m_pxOrder->KdAuftragNr();

    activateOrder ( m_pxOrder->KdAuftragArt()(),
                    "0",
                    m_pxOrder->KoArt(),
                    m_pxOrder->BuchArt(),
                    m_pxOrder->BatchSchreiben()
                    );

    if ( orderNo != m_pxOrder->KdAuftragNr() )
    {
        m_pxCustomerInfo = new pxCustOrderInfo( getPxVbSession()->get() );
        m_pxCustomerInfo->CheckMembers();
        m_pxCustomerInfo->SetOrderNr(getPxOrder()->KdAuftragNr());
        m_pxCustomerInfo->SetEdiLieferSchein(getPxCustomerInfo()->EdiLieferSchein());
        m_pxCustomerInfo->SetBatchOrderNr(getPxCustomerInfo()->BatchAuftragNr());
        m_pxCustomerInfo->Put();
        delete m_pxCustomerInfo;
        m_pxCustomerInfo = 0;
    }
}

//--------------------------------------------------------------------------------------------------//
// GETTER
//--------------------------------------------------------------------------------------------------//


//-------------------------------------------------------------------------------------------------------------------//
pxCustBase* CSCBatchOrderPosDM::getPxCustomer()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getPxCustomer );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxCustomer();
}

//-------------------------------------------------------------------------------------------------------------------//
pxCustOrderInfo* CSCBatchOrderPosDM::getPxCustomerInfo()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getPxCustomerInfo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxCustomerInfo();
}

//-------------------------------------------------------------------------------------------------------------------//
pxParameter* CSCBatchOrderPosDM::getPxOrderParameter()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getPxOrderParameter );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxOrderParameter();
}

//-------------------------------------------------------------------------------------------------------------------//
pxOrder* CSCBatchOrderPosDM::getPxOrder()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getPxOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxOrder();
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::setPxCustomer( pxCustBase* customer )
{
    METHODNAME_DEF( CSCBatchOrderPosDM, setPxCustomer );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_CscOrderObjectGetter->setPxCustomer(customer);
}
//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::setPxCustomerInfo( pxCustOrderInfo* customerInfo )
{
    METHODNAME_DEF( CSCBatchOrderPosDM, setPxCustomerInfo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_CscOrderObjectGetter->setPxCustomerInfo(customerInfo);
}
//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::setPxOrderParameter( pxParameter* parameter )
{
    METHODNAME_DEF( CSCBatchOrderPosDM, setPxOrderParameter );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_CscOrderObjectGetter->setPxOrderParameter(parameter);
}
//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::setPxOrder( pxOrder* order )
{
    METHODNAME_DEF( CSCBatchOrderPosDM, setPxOrder );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_CscOrderObjectGetter->setPxOrder(order);
}

//-------------------------------------------------------------------------------------------------------------------//
pxVerbund::IPXVBOrderTransmitPtr CSCBatchOrderPosDM::getPxOrderTransmit()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getPxOrderTransmit );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxOrderTransmit();
}

//-------------------------------------------------------------------------------------------------------------------//
pxVerbund::IPXVBSessionPtr CSCBatchOrderPosDM::getPxVbSession()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getPxVbSession );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_CscOrderObjectGetter->getPxVbSession();
}

//-------------------------------------------------------------------------------------------------------------------//
basar::VarString CSCBatchOrderPosDM::getArticleCode()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getArticleCode );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getString( properties::pharmosbatchorderpos::ARTICLECODE );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int16 CSCBatchOrderPosDM::getArticleType()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getArticleType );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getInt16( properties::pharmosbatchorderpos::ARTICLETYPE );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CSCBatchOrderPosDM::getArticleNo()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getArticleNo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getInt32( properties::pharmosbatchorderpos::ARTICLENO );
}
//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CSCBatchOrderPosDM::getQuantity()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getQuantity );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getInt32( properties::pharmosbatchorderpos::ORDERQTY );
}
//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CSCBatchOrderPosDM::getQuantityInKind()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getQuantityInKind );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getInt32( properties::pharmosbatchorderpos::QTYINKIND );
}
//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CSCBatchOrderPosDM::getBatchOrderNo()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getBatchOrderNo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getInt32( properties::pharmosbatchorderpos::BATCHORDERNO );
}
//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CSCBatchOrderPosDM::getBatchOrderPosNo()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getBatchOrderPosNo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getInt32( properties::pharmosbatchorderpos::BATCHORDERPOSNO );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CSCBatchOrderPosDM::getCustomerNo()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getCustomerNo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return getPxOrderTransmit()->get()->Order()->IDFNr();
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int16 CSCBatchOrderPosDM::getOriginalBranchno()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getOriginalBranchno );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getInt16( properties::pharmosbatchorderpos::ORIGINBRANCHNO );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::VarString CSCBatchOrderPosDM::get1stIBTPartner()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, get1stIBTPartner );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getString( properties::pharmosbatchorderpos::IBTPARTNER2 );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::VarString CSCBatchOrderPosDM::get2ndIBTPartner()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, get2ndIBTPartner );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getString( properties::pharmosbatchorderpos::IBTPARTNER3 );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CSCBatchOrderPosDM::getCustomerOrderNo()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getCustomerOrderNo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getInt32( properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERNO );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int32 CSCBatchOrderPosDM::getCustomerPosNo()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getCustomerPosNo );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getInt32( properties::pharmosbatchorderpos::ORIGINCUSTOMERORDERPOSNO );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::VarString CSCBatchOrderPosDM::getItemText()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getItemText );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getString( properties::pharmosbatchorderpos::POSITIONTEXT );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::VarString CSCBatchOrderPosDM::getSalesIncreaseFlag()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getSalesIncreaseFlag );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getString( properties::pharmosbatchorderpos::SALEINCREASEFLAG );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Decimal CSCBatchOrderPosDM::getPharmacyPurchasePrice()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getPharmacyPurchasePrice );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getDecimal( properties::pharmosbatchorderpos::PHARMACYPURCHASEPRICE );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Decimal CSCBatchOrderPosDM::getDiscountPercentage()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getDiscountPercentage );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getDecimal( properties::pharmosbatchorderpos::DISCOUNTPERCENTAGE );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Decimal CSCBatchOrderPosDM::getInvoicePrice()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getInvoicePrice );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getDecimal( properties::pharmosbatchorderpos::INVOICEPRICE );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Decimal CSCBatchOrderPosDM::getLineValue()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getLineValue );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getDecimal( properties::pharmosbatchorderpos::LINEVALUE );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Decimal CSCBatchOrderPosDM::getPieceDiscountValue()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getPieceDiscountValue );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getDecimal( properties::pharmosbatchorderpos::PIECEDISCOUNTVALUE );
}

//-------------------------------------------------------------------------------------------------------------------//
basar::Int16 CSCBatchOrderPosDM::getPriceZero()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, getPriceZero );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    return m_YitOrderPos.getInt16( properties::pharmosbatchorderpos::PRICEZERO );
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::setCurrentPos( basar::db::aspect::AccessorPropertyTable_YIterator yitIfxOrderHead )
{
    METHODNAME_DEF( CSCBatchOrderPosDM, setCurrentHead );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    m_YitOrderPos = yitIfxOrderHead;
}

//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::processPosition()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, processPosition );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    // has to be moved, just for test in this method
    m_pxCustomerInfo    = 0;
    m_pxOrderItem       = 0;
    m_pxOrder           = getPxOrderTransmit()->get()->Order();

    if ( isParameterSet() )
    {
        if ( isBatchOrder() )
        {
            setBatchOrderInfo();
        }
    }

    if ( isOrderSet() )
    {
        m_pxOrder->nDBBeginTransaction(cDBTransRecord);

        addOrderItem();

        if ( !isItemSet() )
        {
            m_pxOrder->nDBRollBack();

            basar::VarString msg = "No quantity set for article!";
            throw csc_phabor::exception::OrderProcessingException( basar::ExceptInfo( fun, msg, __FILE__, __LINE__ ) );
        }
        else
        {
            // Check if quantity
            if ( hasQuantity() )    // Fehlmenge
            {
                if ( isQuantityOk() )   // Teilmenge lieferbar, aber per Parameter untersagt -> alle Mengen auf 0 kürzen
                {
                    m_pxOrder->nDBBeginTransaction(cDBTransRecord);

                    updateArticleData();
                    setQuantities();

                    //if ( isOriginForSubsequentDelivery() )
                   // {
                        // Construct NachLieferPos/Type_Batch
                    //    createDeliveryPos();
                    //}

                    // Add Herkunftsfiliale
                    m_pxOrder->HerkunftFiliale( getOriginalBranchno() );
                    setItemText();
                    setItemPrices();
                    setItemDiscount();
                    m_pxOrder->nDBCommit();
                }
                else    // Komplette Menge oder nur ein Teil fehlt, aber per Parameter erlaubt
                {
                    //if ( isOriginForSubsequentDelivery())
                    //{
                     //   createDeliveryPos();
                    //}
                    m_pxOrderItem->CalcConditions();
                    m_pxOrder->HerkunftFiliale( getOriginalBranchno() );
                    setItemText(true);
                    setItemPrices();
                    setItemDiscount();
                    m_pxOrder->nDBCommit();
                }
            }
            else    // komplett geliefert
            {
                setItemPrices();
                setItemDiscount();
                m_pxOrder->nDBCommit();

                checkArticle();

                // BAP-PTEXT into pxorderitem::Bemerkungen
                basar::VarString itemtxt = getItemText();
                nString note = nString( itemtxt.c_str() ); // AIX Error
                m_pxOrderItem->Bemerkungen( note );

                // Have we a "VB"-order ?
                if ( isIBTOrder() )
                {
                    // Set some flags within position.
                    m_pxOrderItem->ToPharmosBatch( getSalesIncreaseFlag() == domMod::batchOrder::processing::cscBatchOrderDM::PHARMOS_YES );
                }

                // Construct NachLieferPos
                if ( hasToConstructDeliveryPos() )
                {
                    createDeliveryPosByCustomer();
                }
                // Add Herkunftsfiliale
                m_pxOrder->HerkunftFiliale((short)getOriginalBranchno());

            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::processOrderHeadText()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, processOrderHeadText );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    basar::VarString orderheadtext = m_YitOrderPos.getString( properties::pharmosbatchorderpos::POSITIONTEXT );

    // \TODO ask SH why implemented
    //orderheadtext.trim(basar::cmnutil::BString::ALL); -> not in original code...
    //if( "" != orderheadtext ) -> not in original code...

    m_pxOrder = getPxOrderTransmit()->get()->Order();
    if ( isOrderSet() )
    {
        m_pxOrder->nDBBeginTransaction( cDBTransRecord );

        getPxOrderTransmit()->get()->FreeTextDoc( orderheadtext.c_str() );

        m_pxOrder->nDBCommit();
    }
}
//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::processOrderHeadType4()
{
    METHODNAME_DEF( CSCBatchOrderPosDM, processOrderHeadType4 );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    basar::VarString itemtext = m_YitOrderPos.getString( properties::pharmosbatchorderpos::POSITIONTEXT );
    //itemtext.trim(basar::cmnutil::BString::ALL); // not in original pvhx05, also result is wrong then

    basar::Int32 orderqty = m_YitOrderPos.getInt32( properties::pharmosbatchorderpos::ORDERQTY );

    m_pxOrder = getPxOrderTransmit()->get()->Order();
    if( isOrderSet() )
    {
        m_pxOrder->nDBBeginTransaction( cDBTransRecord );
        m_pxOrderItem = m_pxOrder->NewOrderTextItem( itemtext.c_str(), orderqty );
        if( !isItemSet() )
        {
            //createDeliveryPos();
            m_pxOrder->nDBCommit();
        }
        else
        {
            m_pxOrder->nDBRollBack();
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------//
void CSCBatchOrderPosDM::process( basar::db::aspect::AccessorPropertyTable_YIterator yitIfxOrderPos )
{
    METHODNAME_DEF( CSCBatchOrderPosDM, process );
    BLOG_TRACE_METHOD(  m_CSC_Logger->getLogger(), fun );

    setCurrentPos( yitIfxOrderPos );

    if( RECORDTYPE_POSITION == m_YitOrderPos.getInt16( properties::pharmosbatchorderpos::RECORDTYPE ) )
    {
        processPosition();
    }

    if( RECORDTYPE_ORDERHEADTEXT == m_YitOrderPos.getInt16( properties::pharmosbatchorderpos::RECORDTYPE ) )
    {
        processOrderHeadText();
    }

    if( RECORDTYPE_ORDERHEADTYPE4 == m_YitOrderPos.getInt16( properties::pharmosbatchorderpos::RECORDTYPE ) )
    {
        processOrderHeadType4();
    }
}

} // namespace processing
} // namespace batchOrder
} // namespace domMod
