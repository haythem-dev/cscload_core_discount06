#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxartprc.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxparameter.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxcstot.hpp"
#include "pxvartikellokal.hpp"
#include "pxvartikellokallist.hpp"
#include "pxbalancecollect.hpp"
#include "pxarticlecodes.hpp"
#include "pxitemattributes.hpp"
#include "pxstockbooking.hpp"
#include "articlesubstitutionutil.hpp"
#include "tourassignmentutil.hpp"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"
#include "types/origintypeenum.inc"
#include "cscordertype/componentmanager/cscordertypecomponentmanager.h"
#include "cscordertype/repository/icscordertyperepository.h"
#include "cscordertype/icscordertype.h"
#include "cscordertype/cscordertypebatchconfig/icscordertypebatchconfig.h"
#include "stockbooking/componentmanager/stockbookingcomponentmanager.h"
#include "stockbooking/longtermlack/ilongtermlackchecker.h"

/*----------------------------------------------------------------------------*/
//  Post quantities on order item entry.                                      */
//  Better: ordered quantity.                                                 */
//  Liefert die bestellte Menge zurück an pvhx?? oder kscserver, ...          */
/*----------------------------------------------------------------------------*/
/*
    - Nachlieferung geprüft -> + Buchung
    - Alternativ-Artikel
    - Reimport-Artikel
    - Verbund
    ....
*/

int
pxOrderItem :: PostOrderQuantity
(
    long        QOrdered,               // ordered quantity
    long        QDisInKind,             // discount-in-kind quantity (manual RebateInKind -> free conditions)
    long        QDemanded,              // demanded quantity: bei neuer Position ist QOrdered = QDemanded; Abweichung muss hier durch Code-Analyse versucht werden herauszufinden
    BookingType btype,                  // item posting type
    int         flags,                  // internal posting control flags
    short       AuxFil,                 // auxdelivery company
    const nString& batchNr,             // batch/charge
    bool        isFixBatch,             // is fixed batch nr
    bool*       bStockNotOk
)
{
    std::stringstream s;
    s << "pxOrderItem::PostOrderQuantity(QOrdered=" << QOrdered <<", QDisInKind=" << QDisInKind << ", QDemanded=" << QDemanded << ", btype=" << btype <<
        ", flags=" << flags << ", AuxFil=" << AuxFil << ")";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), s.str());

    // DACH-BatchTracking: check batch validity
    MessageCodeEnum messageCode = StoreBatchInfo(batchNr, isFixBatch);

    if (CMSG_OK != messageCode)
    {
        switch (messageCode)
        {
        case CMSG_SDC_NO_BATCH_PROVIDED :
            FehlerArtikel_ = ArtStateNoBatchProvided;
            break;
        case CMSG_SDC_BATCH_GIVEN_BUT_NOT_PERMITTED :
            FehlerArtikel_ = ArtStateBatchGivenButNotProvided;
            break;
        case CMSG_SDC_DESIRED_BATCH_GIVEN_ONLY_FIXED_ALLOWED :
            FehlerArtikel_ = ArtStateDesiredBatchGivenOnlyFixedAllowed;
            break;
        case CMSG_SDC_FIXED_BATCH_GIVEN_BUT_NOT_ALLOWED :
            FehlerArtikel_ = ArtStateFixedBatchGivenButNotAllowed;
            break;
        case CMSG_SDC_BATCH_PROCESSING_NOT_POSSIBLE :
            FehlerArtikel_ = ArtStateBatchProcessingNotPossible;
            break;
        default:
            break;
        }
        MengeBestellt_ = QOrdered;
        return ExternalError(CMsgStream(), messageCode);
    }

    // <Tour>
    removeItemTourAssignments(); // neue Pos: und alte Posen: Toureninfos zurücksetzen
    if( NULL == this->Order().getTourInformation() )
    {
        this->Order().getTourAssignmentUtil()->assignTour();
    }

    if( this->Order().Param()->IsUseTourManagerWithTransportExclusion() )
    {
        if( !this->Order().getTourAssignmentUtil()->isArticleDeliverable( ArtBase_ ) )
        {
            FehlerArtikel_ = ArtStateTransportExclusion;
            MengeBestellt_ = QOrdered;
            return ExternalError(CMsgStream(), CMSG_ART_TRANSPORT_EXCLUSION );
        }
    }
    // </Tour>

    short possible_ibtbranchno = 0;
    short possible_ibtnleveltypeid = 0;

    const pxStockTrans&     st = Order().StockTrans();
    const pxCommType&       ct = Order().CommType();
    const pxCustOrderType&  ot = Order().OrderType();
    pxCustBase&       customer = *(Order().Customer());
//    pxVerbund::subsequentDelivery::pxDeliveryPos*          dp = NULL;
    pxDevice           *device = Session()->Device();
    pxVartikelLokal*       stp = NULL;
    long          QInAuxStock = 0;
    const pxArtClass &paramartclass = Order().Param()->ETArtNoNatra();
    const pxArtClass &artclass = ArtBase()->ArtClass();
    bool NewProductAlternate   = false;
    pxCustomerFlags&   cflags  = Order().Customer()->Flags();
    nMoney   cstdiscaccbalance(0.0);
    nMoney            OldValue(0.0);          // this position current value
    nMoney           DiffValue(0.0);          // exceedance of  Creditlimit
    nMoney      OldCreditValue(0.0);          // this position current value
    nMoney          OrderValue(0.0);          // this order value
    long AToPost             = 0;
    long subArticleNo = 0;

/*----------------------------------------------------------------------------*/
/*  UndoTenderProgress: special function TenderOrder in RS and BG             */
/*  it deletes an existing tenderprogress entry                               */
/*----------------------------------------------------------------------------*/
    UndoTenderProgress(); // table TenderProgress gelöscht: weil Neujustierung wieder erforderlich!

/*----------------------------------------------------------------------------*/
/*  When input is received from a device other than a video device, we assume */
/*  an order submission without an operator being interactive, thus quantity  */
/*  lacks are not flagged as an error in that case.                           */
/*----------------------------------------------------------------------------*/
// <Flags>
    if (!(flags & bPOST_AUTO_ITEM) && !(Session()->Device()->IsVideo()))
    {
        flags |= bPOST_IGN_LACK;  // ignore quantity lacks during error detection
    }
    if (!(st.IsDebit() && ArtBase_->ArtFlags().IsBestandsBuchung()))
    {
        flags |= bPOST_NO_DEBIT;  // do not debit the stock
    }

    /*----------------------------------------------------------------------------*/
    /*  Special for the Austrian Prewhole apllication)                            */
    /*----------------------------------------------------------------------------*/
    if ( (ot.IsBountyOrder() || ot.IsDestructionOrder()) && ArtBase_->ArtFlags().IsBestandsBuchung() )
       flags |= bPOST_NO_DEBIT;  // do not debit the stock

    /*----------------------------------------------------------------------------*/
    /* Special for France CC order type                                           */
    /*----------------------------------------------------------------------------*/
    /*
    if (ot.IsChronicIllnessOrder()) {
        flags |= bPOST_IGN_LACK; //do not flag quantity lack as an error
    }
    */
// </Flags>

/*----------------------------------------------------------------------------*/
/* Check long term lack table.                                                */
/*----------------------------------------------------------------------------*/
    if (true == checkLongTermLack(QOrdered, flags, btype))
    {
        return ErrorState();
    }

/*----------------------------------------------------------------------------*/
/*  Check Alternate Article  (France) CodeBlocage 9 and Reverse Substitution  */
/*----------------------------------------------------------------------------*/

    if (!(flags & bPOST_NO_DEBIT) && !ot.IsChronicIllnessOrder())
    {
        getArticleSubstitutionUtil()->resetVars();
        getArticleSubstitutionUtil()->injectBookingFlags(flags);
        getArticleSubstitutionUtil()->injectBookingType((int)btype);
        getArticleSubstitutionUtil()->injectActionCode(ArticleSubstitutionUtil::SUBSTITUTE_NEWPRODUCT);


        if (getArticleSubstitutionUtil()->isSubstitutionNecessary(this->ArtBase_))
        {
            subArticleNo = getArticleSubstitutionUtil()->getSubstituteArticleNo();
        }
        else
        {
            getArticleSubstitutionUtil()->injectActionCode(ArticleSubstitutionUtil::SUBSTITUTE_REVERSE);
            if (getArticleSubstitutionUtil()->isSubstitutionNecessary(this->ArtBase_))
            {
                subArticleNo = getArticleSubstitutionUtil()->getSubstituteArticleNo();
            }
        }
        if (subArticleNo > 0)
        {
            this->changeArtBaseToSubstitutionArticle(subArticleNo, QOrdered);
            if (!IsGoodState())
            {
                return ErrorState();
            }
            if (Session()->Device()->IsVideo())
            {
                Order().setSubArticleNo(subArticleNo);
                return ExternalError(CMsgStream(), CMSG_ART_REVERSESUBSTITUTION);
            }
            NewProductAlternate = IsQStateAlternate();
        }
    }

/*----------------------------------------------------------------------------*/
/*  <Argument sanity check.>                                                    */
/*----------------------------------------------------------------------------*/
    if ( QDemanded < QOrdered )         // Graceful ensure quantity demanded
       QDemanded = QOrdered;            // not being < than q ordered

    // Do not allow negative quantities:
    long q = (QDisInKind < 0) ? QDisInKind : QOrdered;
    if ( q < 0 )
       return ExternalError(CMsgStream(), CMSG_ITM_QUAN_INVALID, q);


    // Check certificate
    if (ArtBase_->ArtFlags().IsNotCertificated())
    {
       if ( !customer.CustomerGroupFlagsList()->IsWithoutCertificateEnabled())
       {
          FehlerArtikel_ = ArtStateNotCertificated;
          MengeBestellt_ = QDemanded;
          if ( device->IsVideo())         // is not dct
          {
             ExternalCondition(CMsgStream(), CMSG_ART_WITHOUT_CERTIFICATE,ArtikelNr_);
          }
          HandleError();
          return ErrorState();
       }
    }

    // Check Opiat in Rebate orders for the Bulgarian application
    if (Session()->isBulgaria())
    {
       if ( ArtBase()->ArtClass().IsOpiat() && ot.IsDiscountAccount() )
       {
          SetNoNarcoticsDiscAcc();
          ExternalCondition(CMsgStream(), CMSG_ITM_NONARCOTIC_DISCACC_ORDER);
          return ErrorState();
       }
    }

/*----------------------------------------------------------------------------*/
/*  Additional sanity check, for the Bulgarien application. Check PriceType   */
/*  If the Pricetype is not availbale within the ArtPriceList, so an error   */
/*  is coming up and no booking of this article takes place                   */
/*----------------------------------------------------------------------------*/
    if (Session()->isBulgaria())
    {
       if ( ArtPriceList() )
       {
          if ( PreisTyp_ != RETAIL_PRICE )
          {
             if ( !ArtPriceList()->Find(PreisTyp_) )
             {
                if ( !(flags & bPOST_RANGEARTICLE ))
                {
                   QOrdered  = 0;
                   return ExternalError(CMsgStream(), CMSG_ART_NOBASEPRICES, ArtikelNr_);
                }
             }
             if ( PreisTyp_ == HEALTHFUND_PRICE)
             {
                nString hc = ArtBase()->HealthFundCode();
                hc.Strip();
                if (hc.IsEmpty() )           // no HealthFundCode available
                {
                   QOrdered = 0;
                   return ExternalError(CMsgStream(), CMSG_ART_NOHEALTHFUNDCODE, ArtikelNr_ );
                }
             }
          }
       }
    }


        // Check Bulgarian specialities
    if(!CheckStotinki(QDisInKind, QOrdered))
    {
        QOrdered = 0;
        ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_STOTINKI);
        HandleError();
        return ErrorState();
    }// if(!CheckBulgarianConditions(MsgId))

// </Argument sanity check.>                                                    */


/*----------------------------------------------------------------------------*/
/*  <Swiss> application: prevent Purchaseorder on Ordertype SV                  */
/*----------------------------------------------------------------------------*/
    if( Session()->isSwitzerland() )
    {
       if (IsDisponieren() && ot.IsService() )
       {
          ExternalCondition(CMsgStream(), CMSG_ITM_PURCHASE_NOTALLOWED ,static_cast<char*>(Order().KdAuftragArt()));
          return ErrorState();
       }
    }
    // </Swiss>


    // <New Sanity Check>
    // Kann in die allgemeinen Sanity Check integriert werden
    // Ensure booking type be valid
    if ( btype < BookingTypeDefault || btype >= BookingTypeLimit )
       return ExternalError(CMsgStream(), CMSG_ITM_BTYPE_INVALID);

    // additional check on disinkind(depend on countries law)
    if ( QDisInKind > 0  && ot.IsDisInKindEnterable() )
    {
       if ( (artclass.IsRezeptPflichtig() && paramartclass.IsRezeptPflichtig()) ||
            (artclass.IsApothekenPflichtig() && paramartclass.IsApothekenPflichtig()) )
       {
          return ExternalCondition(CMsgStream(), CMSG_ITM_DIK_NOTENTERABLE,
                                (char*)(ot.KdAuftragArt()));
       }
    }

    // Check if discount-in-kind quantity is enterable for current order type:
    if ( QDisInKind > 0 && !ot.IsDisInKindEnterable() && !(flags & bPOST_RANGEARTICLE) && PromoTyp_ == 0 )
       return ExternalCondition(CMsgStream(), CMSG_ITM_DIK_NOTENTERABLE,
                                (char*)(ot.KdAuftragArt()));

    if ( device->IsVideo() && QOrdered > 99999)          // may be dct
    {
       ExternalCondition(CMsgStream(), CMSG_ITM_INPUT_TO_LARGE);
       HandleError();
       return ErrorState();
    }

    if ( btype == DemandBooking )       // In case of a simple Demand booking
    {
       QOrdered = 0;                    // we do no availibilty check
       QDisInKind = 0;
    }
    // </New Sanity Check>


    //BB: Tabelle Nachlieferpos: Type ....
    if ( btype == ReservedRestDelivery && !ot.IsChronicIllnessOrder()) // In case of release reserverd quantity
    {
       btype = RestDelivery;
       SetReleaseRestDelivery();
    }

    // <Verbund>
    if ( btype == AuxDelivery )        // In case of a Auxiliary booking
    {
       flags  |= bPOST_AUXDELIVERY;    // for further use
       btype   = BookingTypeDefault;   // btype was just for info. transfer
    }

    // implementation of ItemAttributes Class
    if ( ItemAttributes() )
    {
        // Verbund
        if ( ItemAttributes()->IsAuxDelivery() )
           flags  |= bPOST_AUXDELIVERY;  // for further use
    }

    if ( (flags & bPOST_AUXDELIVERY) || (AuxFil > 0) )
       AuxDelList();

    // </Verbund>

/*----------------------------------------------------------------------------*/
/*  Additional sanity check, to prevent unallowed booking of stocked products */
/*  for non autorized customers(during customerchange)                        */
/*----------------------------------------------------------------------------*/
    //<sanity check>
    if ( !(flags & bPOST_AUTO_ITEM) &&
         !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
         !(ArtBase_->ArtClass().IsAuthorized(Order().Customer()->ArtClass())) )
    {                                // then: customer no authorized
       FehlerArtikel_ = ArtStateNotAuthorized;
       QOrdered       = 0;
       if ( flags & bPOST_IGN_LACK ) //
       {
          // get canned message.
          nMessage msg(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
          nString posbem = msg.String();
          posbem.Compress('\n');
          Bemerkungen(posbem);
       }
       else
       {
          ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
          HandleError();
          return ErrorState();
       }
    }

/*----------------------------------------------------------------------------*/
/*  Additional sanity check, to prevent unallowed booking of stocked products */
/*  for psychotropical Stuff for non autorized customers                      */
/*  (during customerchange)                                                   */
/*----------------------------------------------------------------------------*/
    // <Artikel-spezifische Prüfung>
    if ( !(flags & bPOST_AUTO_ITEM) &&
         !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
          (ArtBase_->IsKzPsychoStoffe()) && !(Order().Customer()->IsPsychoAllowed()))
    {                                // then: customer no authorized
       FehlerArtikel_ = ArtStateNotAuthorized;
       QOrdered       = 0;
       if ( flags & bPOST_IGN_LACK )
       {
          // get canned message.
          nMessage msg(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
          nString posbem = msg.String();
          posbem.Compress('\n');
          Bemerkungen(posbem);
       }
       else
       {
          ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
          HandleError();
          return ErrorState();
       }
    }
    // <Artikel-spezifische Prüfung>

    //</sanity check>

/*----------------------------------------------------------------------------*/
/*  Check ArticleQuota for the current article.                               */
/*  if exceeds, no futher booking takes place.                                */
/*----------------------------------------------------------------------------*/
// <ArticleQuota>
    if (!(flags & bPOST_NO_DEBIT) && !IsReleaseRestDelivery() && !(Order().BatchSchreiben() == cORTYPE_AUXILIARY))
    {
       long Quota = 0;
       UndoArtQuota();                  // Undo previous Quota calculation
       Quota = CheckArtQuota(QOrdered);
       {
          if (QOrdered != Quota)           // limit is exeeded
          {
             if ( !(device->IsVideo()) || (flags & bPOST_IGN_LACK) )   // check for restposting
             {
                QOrdered = ((Quota > 0)  ? Quota : 0 );
                FehlerMenge_ |= QStateNotOnHand; // set quantity state
                if (btype == UpdateDelPos)       // this just comes via device IsVideo and (flags & bPOST_IGN_LACK)
                {
                    btype = RestDelivery;
                    SetNachliefern();
                }
                else
                {
                    SetQuotaExeeded();               // mark for auxdeilvery etc ...
                }
             }
             else if ( !IsNachliefern() )
             {
                Order().RestQuota(Quota);
                Order().LastStock(Session()->getStockBooking()->GetAvailableQtyInStock(*ArtBase_, *Order().Customer()) + MengeAbgebucht_);
                ExternalCondition(CMsgStream(), CMSG_ITM_ARTQUOTA_EXEEDED,ArtikelNr_);
                HandleError();
                return ErrorState();
             }
             else if (IsNachliefern() && (btype == BookingTypeDefault || btype == DeliveryConfirmed) )
             {
                Order().RestQuota(Quota);
                Order().LastStock(Session()->getStockBooking()->GetAvailableQtyInStock(*ArtBase_, *Order().Customer()) + MengeAbgebucht_);
                ExternalCondition(CMsgStream(), CMSG_ITM_ARTQUOTA_EXEEDED,ArtikelNr_);
                HandleError();
                return ErrorState();
             }
          }
       }
    }
    // </ArticleQuota>


/*----------------------------------------------------------------------------*/
/*  Availability check.                                                       */
/*----------------------------------------------------------------------------*/
    // <Article on Stock>
    long   QInStock = GetQtyInStock();

    // MengeAbgebucht_ + freier Bestand + für den Kunden reservierter Bestand
    if ( !(flags & bPOST_RANGEARTICLE ))
    {
        Order().LastStock(MengeAbgebucht_ + Session()->getStockBooking()->GetBookableQuantity(*this, *ArtBase_));
    }
    Order().AuxStock(0);             // init aux stocked quantity
    Order().AuxFil(0);               // init aux company
    Order().RestQuota(0);            // init restquota
    ClearAuxPostPossible();          // reset bit on updates
    long    QToPost = QOrdered + QDisInKind;
    if ( Session()->Device()->IsVideo() )
    {
        if (  btype == RestDelivery )
        {
            QToPost -= QDisInKind;
        }
    }
    // </Article on Stock>

/*----------------------------------------------------------------------------*/
/*  <Check alternate delivery = Verbund mögliche LIeferung>  for Video devices                               */
/*----------------------------------------------------------------------------*/

    if ( Session()->Device()->IsVideo() )
    {
        /*dp =*/ GetBackDeliveryPos();
        //if ((QInStock >= QToPost) && (dp)) // QOrdered reduced
        if ((QInStock >= QToPost) && (getIbtRequest().get() != NULL)) // QOrdered reduced
        {
            UndoAuxPosting();          // return auxposted quantity
//            dp = NULL;                 // no dp
        }
//        else if ((flags & bPOST_AUXDELIVERY) || (AuxFil > 0) || (dp))
        else if ((flags & bPOST_AUXDELIVERY) || (AuxFil > 0) || (getIbtRequest().get() != NULL))
        {
            // now video auxposting has to be done
            if ( AuxDeliveryCheck( AuxFil, flags) && !(flags & bPOST_IGN_LACK) )
                return ErrorState();
            // get the list of article storeloc entries
            if ( !(AuxStoreLocList()->Entries()) && !(flags & bPOST_IGN_LACK) )
                return ExternalError( CMsgStream(), CMSG_AD_NOTPOSSIBLE );
            // auxstorelist available, now get auxstock depend on entry
            stp = GetAuxStockEntry( AuxFil ); // find entry
            if (stp)
                QInAuxStock = stp->Bestand();    // current quantity in auxilary stock
            else
            if (!(flags & bPOST_IGN_LACK) )
                return ExternalError( CMsgStream(), CMSG_AD_NOTPOSSIBLE );
        }
    }

    QInStock    += QInAuxStock;          // add quantity in aux-stock
    FehlerMenge_ = QStateGood;           // default state: quantity available
    if ( ot.IsQuery()  && QInStock < QToPost )
        FehlerMenge_ |= QStateNotOnHand;  // set quantity state

    // </Check alternate delivery>


    // <CR-14A004>
    if( Session()->isSwitzerland() )
    {
        // nothing to do: No checks for Tender quantities in CH
    }
    else
    {
        // CR-14A004   Start
        if ( Order().isTenderOrder() && !st.IsNoTransaction() /* Bewegungsart:  */)  // no check on TI22 orders!
        {
            long freeTenderQty = 0;
            freeTenderQty = getFreeTenderQty();
            if ( freeTenderQty < QOrdered )
            {
                QOrdered  = (freeTenderQty < 0) ? 0 : freeTenderQty; // might be negative because exceedance pct!
                QDemanded = QOrdered;
                QToPost   = QDemanded;
                FehlerMenge_ |= QStateTenderQtyExceeded; // set quantity state
            }
        }
        // CR-14A004   End
    }
    // </CR-14A004>


    // <Bestand nicht ausreichend>
    if ( !(flags & bPOST_NO_DEBIT)  && QInStock < QToPost )
    {                                   // then desired quantity not available
        if ( ot.IsNoPartQty() )          // do not deliver partial quantity/ QToPost = 0
        {
            AToPost = QToPost;         // save quantity to post
            QToPost = 0;
            QDisInKind = 0;
        }
        else
        {
            // QDisInKind = 0;
            AToPost = QToPost;         // save quantity to post
            QToPost = QInStock;        // set order q to available rest
            // <SR-18030892  Start>
            if (Session()->isBulgaria())
            {
                if (ot.IsFreeConditionOrder() && QDemanded > 0 && QDisInKind > 0)
                {
                    QToPost = (QToPost > QDemanded) ? QDemanded : QToPost;
                    QDisInKind = QInStock - QToPost;
                    QToPost += QDisInKind;               // for futher use
                }
            }
            // </SR-18030892  End>
        }
        FehlerMenge_ |= QStateNotOnHand; // set quantity state

        /*----------------------------------------------------------------------------*/
        /*  The current ordered quantity of a stocked product could not be satisfied  */
        /*  from the distributors stock. If the quantity in stock = 0, so first check */
        /*  the alternate article. If the current article has an alternate article    */
        /*  and this article has a positiv quantity in stock, so Artbase_ is deleted  */
        /*  and the alternate article is now the current one. (only on DCT terminals) */
        /*----------------------------------------------------------------------------*/
        if ( QInStock == 0 ) // nichts auf Lager  -> Vorwärtssuche für Substitutionsartikel
        {
            long ArtikelNrOrg = ArtikelNr_;
            getArticleSubstitutionUtil()->resetVars();
            getArticleSubstitutionUtil()->injectBookingFlags(flags);
            getArticleSubstitutionUtil()->injectBookingType((int)btype);
            getArticleSubstitutionUtil()->injectActionCode(ArticleSubstitutionUtil::SUBSTITUTE_FORWARD);

            if ( getArticleSubstitutionUtil()->isSubstitutionNecessary( this->ArtBase_) )
            {
                subArticleNo = getArticleSubstitutionUtil()->getSubstituteArticleNo();
            }
            if ( subArticleNo > 0 )
            {
                this->changeArtBaseToSubstitutionArticle( subArticleNo, QOrdered);
                if (!IsGoodState())
                {
                    return ErrorState();
                }
                QInStock = GetQtyInStock(); // correct quantity in stock
                FehlerMenge_ = QStateGood;       // clear FehlerMenge_
                long Quota = 0;
                UndoArtQuota();                  // Undo previous Quota calculation
                m_ArticleQuota.reset();
                Quota = CheckArtQuota(QOrdered);
                if (QOrdered != Quota)           // limit is exeeded
                {
                    QOrdered = ((Quota > 0)  ? Quota : 0 );
                    FehlerMenge_ |= QStateNotOnHand; // set quantity state
                    SetQuotaExeeded();               // mark for auxdeilvery etc ...
                }
                QToPost = ( ( QInStock >= QOrdered + QDisInKind) ? (QOrdered + QDisInKind) : QInStock );
                setOrderItemAlternateRemarks( ArtikelNrOrg, (short)CMSG_ITM_ALTERNATE);
                FehlerMenge_ |= QStateAlternate; // mark item
                SetAusweichArtikelGebucht();
                // Korrektur INC-043864
                ArticleCode_.Clear();
                PreisEKApo_ = pxConstants::mZero;
                // Korrektur INC-043864
            }
        } // ENDE if ( QInStock == 0 ) // nichts auf Lager  -> Vorwärtssuche für Substitutionsartikel

        /*----------------------------------------------------------------------------*/
        /*  The current ordered quantity of a stocked product could not be satisfied  */
        /*  from the distributors stock, so we look for an alternativ deliver         */
        /*  possibility. If the customer and the wanted artikel meets the distibutors */
        /*  defined requirements, so we try to satisfy the remaining rest from an     */
        /*  alternate stock.                                                          */
        /*----------------------------------------------------------------------------*/
        if( QOrdered > QInStock && (!( AuxDeliveryCheck(AuxFil, flags, btype)) )) // für den (normaler oder Sub-)artikel wir im Verbund nach Menge gesucht!
        {
            if( !Order().Param()->IsNlevelIBT() )
            {
                if ( !(device->IsVideo()) && AuxFil > 0 )     // may be dct and AuxFil is preset
                {
                    stp = GetAuxStockEntry(AuxFil);
                }
                else
                {
                    // first look for Customers preference,
                    // Customer does not belong to own company
                    if ( Order().FilialNr()  != Order().Customer()->FilialNr() )
                    {
                        stp = AuxStoreLocList()->GetPreferedEntry((QOrdered - (QInStock - QInAuxStock)), Order().Customer()->FilialNr());
                    }
                    else
                    {
                        stp = AuxStoreLocList()->QuantityInList(QOrdered - (QInStock -QInAuxStock));
                    }
                }
            }
            else
            {
                // NLevelIBT -> Ermittlung VZ für Verbundbuchung
                long requestedIBTQty = QOrdered - (QInStock -QInAuxStock);
                stp = AuxStoreLocList()->getNLevelIBTEntryToBeUsed( requestedIBTQty );
            }

            // get availability in auxstock
            if ( stp )
            {
                Order().AuxStock(stp->Bestand()); // buffer aux stocked quantity
                Order().AuxFil(stp->FilialNr());  // buffer aux company

                possible_ibtbranchno = stp->FilialNr();
                possible_ibtnleveltypeid = stp->getNLevelIBTTypeId();

                MengeMoeglich_ = (( stp->Bestand()  > QOrdered - QInStock) ? QOrdered - QInStock : stp->Bestand() );

                if ( !(device->IsVideo()) && !(IsAuxPostPossible()) ) // should be a dct
                {
                    QInAuxStock = stp->Bestand();
                    QInStock += QInAuxStock;   // total availability
                    QToPost = ((QInStock >= QOrdered + QDisInKind) ? (QOrdered + QDisInKind) : QInStock);
                    if (QInStock >= (QOrdered + QDisInKind) && !IsQStateAlternate())
                    {
                        FehlerMenge_  = QStateGood; //clear FehlerMenge_
                    }
                }
                MengeMoeglich_ = CheckRemoteArticleQuota(stp->FilialNr(),MengeMoeglich_);
                if ( MengeMoeglich_ == 0 )
                {
                    ClearAuxPostPossible();              // auxposting not possible
                }
            }
            else
            {
                ClearAuxPostPossible();              // auxposting not possible
            }
        } // ENDE if( QOrdered > QInStock && (!( AuxDeliveryCheck(AuxFil, flags, btype)) ))


        if (!(flags & bPOST_IGN_LACK)) // then do not ignore quantity lack
        {
            if (device->IsVideo())
            {
                if ((flags & bPOST_RANGEARTICLE) && QDisInKind > 0)  // should be a Discount article
                {
                    if (bStockNotOk)
                        *bStockNotOk = true;
                }
            }
            if (!bStockNotOk
                || false == *bStockNotOk)
            {
                return ExternalCondition(CMsgStream(), CMSG_ART_QLACK, AToPost, QInStock, ArtikelNr_);
            }
        }
    } // ENDE: if (!(flags & bPOST_NO_DEBIT) && QInStock < QToPost)



    // <>
    long bs = Order().BatchSchreiben(); // => Flag auf KDAuftrag verschiedene Werte
    if ( !(Session()->Device()->IsVideo())
         && (QOrdered > Order().Param()->MaxPosMenge())
         && ( bs != cORTYPE_PARENT_COMPANY && bs != cORTYPE_CLEARING
         && bs != cORTYPE_INDUSTRIAL_RETURN))
    {
        FehlerMenge_ |= QStateLimitCheck;  // set quantity state
    }
    // </>


/*----------------------------------------------------------------------------*/
/*  Nothing in stock , perhaps we can get re-import quantity                  */
/*----------------------------------------------------------------------------*/
    // <re - import>
    if (QInStock == 0)
    {
        getArticleSubstitutionUtil()->resetVars();
        getArticleSubstitutionUtil()->injectBookingFlags(flags);
        getArticleSubstitutionUtil()->injectRequiredQuantity(QOrdered + QDisInKind);
        getArticleSubstitutionUtil()->injectActionCode(ArticleSubstitutionUtil::SUBSTITUTE_REIMPORT);
        if (getArticleSubstitutionUtil()->isSubstitutionNecessary(ArtBase_))
        {
            subArticleNo = getArticleSubstitutionUtil()->getSubstituteArticleNo();
        }
        if (subArticleNo > 0)
        {
            if (getArticleSubstitutionUtil()->isSubstitutionArticleNoPassive())
            {
                FehlerMenge_ |= QStateAlternateReimport; // set quantity state
                ArtikelNrPassiv_ = subArticleNo;
            }
            else if (cflags.IsReimportArtikel())
            {
                const long ArtikelNrOrdered = ArtikelNr_;   // origninal ordered PZN
                boost::shared_ptr<pxArticleCodes> ArtCode = boost::shared_ptr<pxArticleCodes>(GetArticleCode(ArtikelNrOrdered));
                const long articleno = (ArtCode != NULL) ? atoi(ArtCode->ArticleCode()) : ArtikelNrOrdered;

                ArtBase_->Put();
                delete ArtBase_;
                ArtBase_ = NULL;
                ArtikelNr_ = subArticleNo;  //new product number
                // read and lock alternate product base object
                if (!ArtBase(cDBGET_FORUPDATE) || !ArtBase()->IsGoodState())
                {
                    FehlerArtikel_ = ArtStateNotFound;
                    MengeBestellt_ = QOrdered;
                    PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
                    HandleError();                   // product or return the error
                    return ErrorState();
                }
                if (ArtBaseValidity(QOrdered, flags))
                {
                    return ErrorState();
                }
                // Check certificate
                if (ArtBase_->ArtFlags().IsNotCertificated())
                {
                    FehlerArtikel_ = ArtStateNotCertificated;
                    MengeBestellt_ = QDemanded;
                    ExternalCondition(CMsgStream(), CMSG_ART_WITHOUT_CERTIFICATE, ArtikelNr_);
                    HandleError();
                    return ErrorState();
                }
                FehlerMenge_ = QStateGood;          // clear FehlerMenge_
                MengeMoeglich_ = 0;                 // clear Verbundinfo für Originalartikel
                ClearAuxPostPossible();             // clear Verbundinfo für Originalartikel
                QInStock = GetQtyInStock();         // total availability
                UndoArtQuota();                     // Undo previous Quota calculation
                const long Quota = CheckArtQuota(QOrdered);
                if (QOrdered != Quota)              // limit is exeeded
                {
                    QOrdered = (Quota > 0) ? Quota : 0;
                    FehlerMenge_ |= QStateNotOnHand; // set quantity state
                    SetQuotaExeeded();               // mark for auxdeilvery etc ...
                }
                QToPost = QOrdered + QDisInKind;    // wanted
                SetReimportArtikel();
                // get canned message.
                nMessage msg(CMsgStream(), CMSG_ITM_REIMPORT_BOOKED_FOR, articleno);
                nString posbem = msg.String();
                posbem.Compress('\n');
                posbem.Trim(30);
                Bemerkungen(posbem);

                // Korrektur INC-043864
                ArticleCode_.Clear();
                PreisEKApo_ = pxConstants::mZero;
                // Korrektur INC-043864
            }
            else
            {
                FehlerMenge_ |= QStateAlternateReimport; // set quantity state
                ArtikelNrPassiv_ = subArticleNo;

                if (Order().isMSV3Order() || Order().IsMSV3InfoOrder())
                {
                    pxParameter param(Session(), 0, (nString)cPAR_KSCSERVER_GROUP, (nString)cPAR_KSCSERVER_PURPOSE_MSV3_REIMPORTPROPOSAL, (nString)cPAR_KSCSERVER_PARAMNAME_ENABLE);
                    if ((param.Get(cDBGET_READONLY) == cDBXR_NORMAL) && (param.Wert() == 1L))
                    {
                        SubstProposalArticleNo_ = subArticleNo; // Substitution proposal for "non Reimport" customers
                    }
                }
            }
        }
    }
    // </re - import>

    /*----------------------------------------------------------------------------*/
    /*  Sanity checks are thru, set quantities now.                               */
    /*----------------------------------------------------------------------------*/
    // <Sanity checks?>
    //Korrektur INC-041263   Die Menge Natra darf nicht mit in den Kreditlimit laufen
    //ONG  MengeGeliefert = (MengeBestaetigt_ + MengeNatra_) - MengeVerbund_;
    long  MengeGeliefert = MengeBestaetigt_ - MengeVerbund_;
    OldValue       = (Price() * (double)MengeGeliefert) * (1 + (SalesTaxRate_/100));
    OldCreditValue = (PreisFaktur_ * (double)MengeGeliefert) * (1 + (SalesTaxRate_/100));
    // </Sanity checks?>

    // <Grund-Initialisierung>
    UndoQuantityPosting(st);            // Undo previous stock transaction
    // </Grund-Initialisierung>

    //PostType(btype);                  // Update posting type flags in self
    MengeBestellt_ =  QDemanded;
    if (QToPost)                       // = QDemanded+QDisInKind or QInStock
    {
       QToPost -= QDisInKind;           // subtract it if it has been entered
       QToPost = (QToPost > 0) ? QToPost : 0;
    }


    /*----------------------------------------------------------------------------*/
    /*  Calc terms and prices.                                                    */
    /*----------------------------------------------------------------------------*/
    // <Übernahem von artikelspez. Werten> ==> noch erforderlich -> mit Rolf Raab klären
    ETArtKlasse_   = ArtBase_->ArtClass(); // due to old Pharmos compatibility
    ETArtSchalter_ = ArtBase_->ArtFlags(); // requirements, we must copy these
    Zuzahlung_     = ArtBase_->Zuzahlung();
    Rabattfaehig_  = ArtBase_->DiscountCode();
    // </Übernahem von artikelspez. Werten>

    GetBasePrices(PreisTyp_); //


    /*----------------------------------------------------------------------------*/
    /*  Return customers discount account (if available)                          */
    /*  The current ShipValue of this Item is returned to customers entry         */
    /*  cstdiscaccbalance contains the current Balance after this call            */
    /*----------------------------------------------------------------------------*/
    // <generell AA 'RO' (RebateOnly)>
    if ( ot.IsDiscountAccount() )
    {
       OrderValue = Order().GetOrderValueCstDiscAcc();
       cstdiscaccbalance = Order().IncreaseCstDiscAcc( ((Price() * (double)MengeGeliefert)) * (1 + (SalesTaxRate_/100)), ArtBase()->TaxLevel());
       ClearRebateAccountExceeded();
    }
    // </generell AA 'RO' (RebateOnly)>

    // <>
    if (QToPost)
    {
        checkPriceLimitations( ((flags & bPOST_IGNORE_PRICELIMIT) ? true : false), QToPost);
        if (!IsGoodState())
        {
            return ErrorState();
        }

        MengeBestaetigt_ = CalcTermsOnEntry(QToPost, QInStock);
        if ( !IsGoodState() )
        {
            MengeBestaetigt_ = 0;
            FehlerMenge_ |= QStateNotOnHand;  // set quantity state
            return ErrorState();
        }
    }
    // </>

    // SR-17088332 Just  for rebateinkind booking (MengeBestellt_ = 0 and QDisInKind > 0
    if (Session()->isBulgaria())
    {
        if (ot.IsFreeConditionOrder())
        {
            if (MengeBestellt_ == 0 && QDisInKind > 0)
            {
                QDisInKind = (QInStock < QDisInKind) ? QInStock : QDisInKind;
            }
        }
    }
    // </SR-17088332 Just  for rebateinkind booking (MengeBestellt_ = 0 and QDisInKind > 0>


    MengeNatraGrossH_ += QDisInKind;    // add discount-in-kind q entered (manually)
    MengeNatra_ = MengeNatraGrossH_ + MengeNatraHerst_ + MengeNatraDiscountArticle_;

    if( libcsc::LoggerPool::getLoggerOrderItem().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
    {
        std::stringstream ss;
        ss << "MengeNatraGrossH_=<" << MengeNatraGrossH_;
        ss << ">, MengeNatraHerst_=<" << MengeNatraHerst_ << ">, MengeNatraDiscountArticle_=<" << MengeNatraDiscountArticle_;
        ss << ">, MengeNatra_=<" << MengeNatra_ << ">";
        libcsc::LoggerPool::getLoggerOrderItem().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }

    // <IvryLab speciality???>
    if ( DiscountArticleNo_ > 0 )              // IvryLab speciality
    {
       if ( MengeNatra_ > 0 )                  // test condition
       {
          MengeNatraDiscountArticle_ = MengeNatra_;
          MengeNatra_                = 0;
       }
       else
       {
          DiscountArticleNo_ = 0;              // no Article for free
          MengeNatraDiscountArticle_ = 0;      // prevent misuse
       }
    }
    // </IvryLab speciality???>

    /*----------------------------------------------------------------------------*/
    /*  Due to the calculation of terms, the quantity values might have been      */
    /*  raised, so we again check the availability. When available,               */
    /*   discount-in-kind quantities are untouched.                               */
    /*----------------------------------------------------------------------------*/
    if (!(flags & bPOST_NO_DEBIT) && (MengeBestaetigt_ + MengeNatra_) > QInStock)
    {                            // not on stock, first cancel discount-in-kind

       if ( MengeBestaetigt_ >= QInStock ) // will it ever happen ?
       {
           MengeNatra_ = MengeNatraGrossH_ = MengeNatraHerst_ = MengeNatraDiscountArticle_ = 0;
           MengeBestaetigt_ = QInStock;
       }
       else
       {
            long origMengeNatra = MengeNatra_;           // original MengeNatra_
            MengeNatra_ = QInStock - MengeBestaetigt_;   // reduce MengeNatra_ due to insufficient stock level

            // Recalculate MengeNatraGrossH_, MengeNatraHerst_ and MengeNatraDiscountArticle_ proportionally
            // while ensuring they remain integers and their sum equals MengeNatra_
            double ratioGrossH = static_cast<double>(MengeNatraGrossH_) / origMengeNatra;
            double ratioHerst = static_cast<double>(MengeNatraHerst_) / origMengeNatra;
            MengeNatraGrossH_ = static_cast<long>(MengeNatra_ * ratioGrossH);
            MengeNatraHerst_ = static_cast<long>(MengeNatra_ * ratioHerst);
            MengeNatraDiscountArticle_ = MengeNatra_ - MengeNatraGrossH_ - MengeNatraHerst_;
       }

       // correct MengeNatra on Restdelivery(new feature OPL29)
       if  ( Session()->Device()->IsVideo() )     //just for compiler on unix
       {
          if (  btype == RestDelivery )
          {
             MengeNatraGrossH_ += QDisInKind;    // add discount-in-kind q entered
             MengeNatra_ = MengeNatraGrossH_ + MengeNatraHerst_ + MengeNatraDiscountArticle_;
             if ( DiscountArticleNo_ > 0 )              // IvryLab speciality
             {
                if ( MengeNatra_ > 0 )                  // test condition
                {
                   MengeNatraDiscountArticle_ = MengeNatra_;
                   MengeNatra_                = 0;
                }
                else
                {
                   DiscountArticleNo_ = 0;              // no Article for free
                   MengeNatraDiscountArticle_ = 0;      // prevent misuse
                }
             }
          }
       }
    }
/*----------------------------------------------------------------------------*/
/*  AuxPosting                                                                */
/*----------------------------------------------------------------------------*/
    long QToPostAux = 0;                  // preset auxquantity
    if (!(flags & bPOST_NO_DEBIT) && !(IsAuxPostPossible()) )
    {
       // if we have to do alternate delivery, calculate the quantity to post
       if ( QInAuxStock)
       {
          long qtyInStock = Session()->getStockBooking()->GetAvailableQtyInStock(*ArtBase_);
          if ( qtyInStock < MengeBestaetigt_ + MengeNatra_ )
          {
             QToPostAux    = MengeBestaetigt_ + MengeNatra_ - qtyInStock;
             if ( qtyInStock <= MengeNatra_ )
                QToPostAux += qtyInStock;
             if ( ( MengeVerbund_ = QPostAux( QToPostAux, /*dp,*/ stp)) == 0 && !(flags & bPOST_IGN_LACK)) // NLevelIBT -> Verbundbuchung!
             {
                return ExternalError( CMsgStream(), CMSG_AD_NOTPOSSIBLE );
             }
             else
             {
                // now we have to recalculate MengeBestaetigt_ and MengeNatra_
                // NLevelIBT -> Setzen IBTType NLevel in Position
                if( this->Order().Param()->IsNlevelIBT() )
                {
                    this->IBTTypeID_ = stp->getNLevelIBTTypeId();
                }
                else
                {
                    this->IBTTypeID_ = 0;
                }

                if ( MengeVerbund_ == 0 || (MengeVerbund_ < QToPostAux) )
                {
                   //if (MengeVerbund_ == 0)
                   //   QInStock    -= QInAuxStock;  // sub quantity in aux-stock
                   //else
                   QInStock  -= ( QInAuxStock - MengeVerbund_);  // reduce quantity in stock
                   if ( !(flags & bPOST_NO_DEBIT)  && QInStock < QToPost )
                   {
                      FehlerMenge_ |= QStateNotOnHand; // set quantity state
                      QDisInKind    = 0;
                      QToPost       = QInStock;        // set order q to available rest
                   }
                   ReCalculate(QToPost, QInStock, flags);
                }
             }
          }
       }
    }
/*----------------------------------------------------------------------------*/
/*  Inventory posting.                                                        */
/*----------------------------------------------------------------------------*/
    MengeAbgebucht_  = MengeGeliefert_ = (MengeBestaetigt_ + MengeNatra_)
                                         - MengeVerbund_;

/*----------------------------------------------------------------------------*/
/*  Check Customers Discount Account(Special for the bulgarien application    */
/*  Get Order Value without Tax and add this Item's ship value to the previous*/
/*  result and then mulitply the result with Tax(1.20)                        */
/*  This Result(Probable Order Value) is compared against the Total cstdiscacc*/
/*  value(TotalBalance)                                                       */
/*----------------------------------------------------------------------------*/
   // nMoney  OrderValue = Order().GetOrderValueCstDiscAcc();
    nMoney  shipvalue =   ((OrderValue + (Price() * (double)MengeGeliefert_)) * (1 + (SalesTaxRate_/100)) );
    if ( cstdiscaccbalance == pxConstants::mZero && ot.IsDiscountAccount())
    {
       SetRebateAccountExceeded();
       return ExternalCondition(CMsgStream(),CMSG_ORD_CSTDISCACC_EXHAUSTED, (double) cstdiscaccbalance);
    }

    if ( cstdiscaccbalance > pxConstants::mZero )   // there is an entry
    {
       nMoney TotalBalance = Order().BalanceCollectList()->GetTotalBalance(0);
       TotalBalance -= shipvalue;
       if ( TotalBalance < pxConstants::mZero )   // exhausted
       {
          Order().DecreaseCstDiscAcc(OldValue, ArtBase()->TaxLevel());
          SetRebateAccountExceeded();
          return ExternalCondition(CMsgStream(),CMSG_ORD_CSTDISCACC_EXHAUSTED, (double) TotalBalance);
       }
    }
/*----------------------------------------------------------------------------*/
/*  Check Customers Credit Limit. If DiffValue > 0.0 return errorstate        */
/*----------------------------------------------------------------------------*/
    if (Session()->isBulgaria() && (Order().Customer()->IsCashPayer() || !(Session()->getOrderEntryParam(Order().Customer()->Vertriebszentrum())->IsSCrema())))
    {
       DiffValue = CheckCreditLimitK2( OldCreditValue );
       if ( DiffValue > pxConstants::mZero )             // credit limit exhausted
       {
          ExternalCondition(CMsgStream(),CMSG_ORD_CREDITLIMIT_EXHAUSTED, (double) DiffValue);
          return ErrorState();
       }
       else
       {
          DiffValue = CheckCreditLimitK1( OldCreditValue );
          if ( DiffValue > pxConstants::mZero )             // credit limit exhausted
          {
             ExternalCondition(CMsgStream(),CMSG_ORD_CREDITLIMIT_EXHAUSTED, (double) DiffValue);
             return ErrorState();
          }
       }
    }

    // correct MengeAbgebucht/MengeGeliefert(new feature OPL29)
    if  ( Session()->Device()->IsVideo() )     //just for compiler on unix
    {
       if (  btype == RestDelivery )
       {
          if ( MengeNatra_ > 0  && MengeBestaetigt_ == 0 )
          {
             MengeAbgebucht_ -= MengeNatra_;
             MengeGeliefert_ -= MengeNatra_;
          }
       }
    }

    if ( (flags & bPOST_NO_DEBIT) || BookingTypeReserveCustomerStock == btype)
    {
        MengeAbgebucht_ = 0;
    }
    if (MengeAbgebucht_ > 0)
    {
        long qtyReserved = Session()->getStockBooking()->AddReservationForOpenOrder(*this, this->MengeAbgebucht_);

        if (qtyReserved < MengeAbgebucht_)
        {
            std::stringstream ss;
            ss << "Order " << KdAuftragNr_ << ", Pos " << PosNr_
                << ", Article " << ArtikelNr_ << ", MengeAbgebucht_ " << MengeAbgebucht_ << ", reserviert " << qtyReserved;
            LOG4CPLUS_ERROR(libcsc::LoggerPool::getLoggerStockBooking(), ss.str());
        }
    }

    if (!(flags & bPOST_NO_DEBIT) && !IsReleaseRestDelivery() )     // then product delivery from stock
    {
        UpdateArtQuota();
    }

    if ( st.IsReturn() )                // then: product is returned
    {
        Session()->getStockBooking()->AddQtyInStock(*ArtBase_, MengeBestellt_, TRANSACTIONTYPE_CUSTOMERRETURNS);
    }

    if ( st.IsDemand() )                // register product demand
    {
       ArtBase_->NachFrage(MengeBestellt_);
    }
    if ( !(flags & bPOST_RANGEARTICLE ))
    {
        Order().LastStock(Session()->getStockBooking()->GetBookableQuantity(*this, *ArtBase_));
    }
    ArtBestNachUpd_ = Session()->getStockBooking()->GetAvailableQtyInStock(*ArtBase_, *Order().Customer());

    nClock   now;
    UhrZeitBestNachUpd_ = now.GetHHMMSSD(); // keep update time

/*----------------------------------------------------------------------------*/
/*  Set shipment control flags.                                               */
/*----------------------------------------------------------------------------*/
    // Implementation of ItemAttributes Class
    if ( ItemAttributes() && st.IsDebit() )
    {
       if ( ItemAttributes()->IsRestDelivery() )
       {
           btype = RestDelivery;
       }
    }

    PostType(btype);                    // Update posting type flags in self
    ClearToCustomerService();
    ClearToDisposal();
    ClearToCommission();
    if ( st.IsDebit() )                 // then product delivery from stock
    {
       // Check purchase stopp
       if (IsNachliefern() && ((MengeBestaetigt_ + MengeNatra_) < MengeBestellt_) &&
            ArtBase_->ArtFlags().IsPurchaseStop() )
       {
          ClearNachliefern();
          FehlerArtikel_ = ArtStatePurchaseStop;
          //ExternalCondition(CMsgStream(), CMSG_ART_PURCHASE_STOP,ArtikelNr_);
          //HandleError();
       }
       else
       {
            AuxShipment();                   // Auxiliary shipment
            // implement Swiss/Austria Restdelivery System
            if (!IsGoodState() && !(flags & bPOST_IGN_LACK))
            {
                HandleError();
                return ErrorState();
            }

            if ( (MengeBestaetigt_ + MengeNatra_) < MengeBestellt_ )
            {
                FehlerMenge_ |= QStateNotOnHand;  // set quantity state
                if (IsDisponieren() || IsNachliefern() )
                {
                    SetToCustomerService();
                    SetToDisposal();
                }
            }
       }
    }

    if ( ArtBase_->ArtClass().IsOpiat() )
    {
       if ( !(ot.IsService() || ot.IsBuyBack()) )
       {
          SetToCustomerService();
          if ( Order().Param()->IsBTMKommi() && !ct.IsNoShipment() )
             SetToCommission();
       }
    }

    if ( MengeGeliefert_ > 0 && !ct.IsNoShipment()
         && !ArtBase_->ArtClass().IsOpiat() )
       SetToCommission();

    if ( ot.IsBountyOrder() || ot.IsDestructionOrder() )
       SetToCommission();

    if ((ArtBase_->ArtikelNr()) == (Order().Param()->PZNBTMSchein()) )
       ClearToCommission();

    if ( ArtBase_->ContainerGroesse() > 0
         && (MengeGeliefert_ >= ArtBase_->ContainerGroesse()) &&
       Order().FilialNr() != 17 && !Session()->isFrancePrewhole() )  //***** Krüke muß über Parameter laufen
    {

       SetContainerPack();
    }
    if ( IsContainerPack() )
       SetBeiPackMulti();

    if ( NewProductAlternate )
       FehlerMenge_ |= QStateAlternate; // mark item

    if ( ArtBase_->IsAllPrivatProductRange())
        KzPriso_ = '1';

    nString tourid = Order().TourId();
    SetTourId( tourid );

    assignItemTour();

    // determine ibttour also in case of ibt possible but not booked
    if( this->MengeMoeglich() > 0 && this->MengeVerbund() == 0 && possible_ibtbranchno > 0 )
    {
        assignItemIBTTour( possible_ibtbranchno, possible_ibtnleveltypeid);  // Verbundtour ermitteln
        this->SetIBTTypeID( possible_ibtnleveltypeid );
    }

    SetDirty();
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Recalculate MengeBestaetigt_ and MengeNatra_ depend on QToPost and        */
/*  QInStock                                                                  */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: ReCalculate
(
    long  QToPost,                     // wath to deliver
    long  QInStock,                    // availibility
    int   flags                        // control flags
)
{
    MengeBestaetigt_ = MengeNatra_ = 0;
    if (QToPost)
    {
       MengeBestaetigt_ = CalcTermsOnEntry(QToPost, QInStock);
       MengeNatra_ = MengeNatraGrossH_ + MengeNatraHerst_;
       if (!(flags & bPOST_NO_DEBIT) && (MengeBestaetigt_ + MengeNatra_) > QInStock)
       {                                // not on stock, first cancel discount-in-kind
          if ( MengeNatra_ > QInStock )
          {
             MengeNatra_ = QInStock;
             MengeNatraGrossH_ = (MengeNatraGrossH_ > 0 && MengeNatraGrossH_ >= QInStock) ? QInStock : 0;
             MengeNatraHerst_ = (MengeNatraHerst_ > 0 && MengeNatraHerst_ >= QInStock) ? QInStock : 0;
          }
          MengeBestaetigt_ = QInStock - MengeNatra_;
       }
    }
}

//----------------------------------------------------------------------------
//  Checks Stotinki condition for Bulgarian logic
//----------------------------------------------------------------------------
bool
pxOrderItem :: CheckStotinki
(
     long QDisInKind,             // discount-in-kind quantity
     long QOrdered
)
{
    // Stop at once, if we are not in Bulgaria.
    // This is not an error!
    if (!Session()->isBulgaria())
    {
        return true;
    }

    // If article is not a Stotinki article, everything is ok
    pxArtBase* thisArtBase=ArtBase();
    if(!thisArtBase->IsSortiment3()) // this article is not a Stotinki article
            return true;


    // If article is booked as rebate in kind, everything is ok, even if it's a Stotinki article
    if(QDisInKind > 0)
            return true;

    if ( QOrdered == 0 )
            return true;

    // If order type is not a manual promotion, everything is ok
    if(Order().OrderType().IsManualPromotion()) // this article is ordered as an MP order
            return true;

    // If customer group is one of 8,9,13,18, everything is ok
    pxCustBase& customer = *(Order().Customer());
    return ( customer.CustomerGroupFlagsList()->IsStotinkiEnabled() );

}//CheckStotinki

//----------------------------------------------------------------------------
//  Availability check.
//----------------------------------------------------------------------------
long
pxOrderItem :: GetQtyInStock
(
    pxArtBase* artBase
)
{
    pxArtBase* article = (artBase ? artBase : ArtBase_);

    long qtyInStock = Session()->getStockBooking()->GetBookableQuantity(*this, *article) + MengeAbgebucht_;
    return qtyInStock;
}

//----------------------------------------------------------------------------
//  long term lack check.
//----------------------------------------------------------------------------
bool pxOrderItem::checkLongTermLack(const long QOrdered, const int flags, const BookingType btype)
{
    bool longTermLack = false;

    // Bei "nicht Bestand buchen" kein check auf longtermlack!
    if (flags & bPOST_NO_DEBIT)
    {
        return longTermLack;
    }

    if (ReservedRestDelivery == btype)
    {
        return longTermLack;
    }

    // Bei Liefervorgabe MaxDispo kein check auf longtermlack!
    if (NULL != ItemAttributes() && true == ItemAttributes()->IsPurchaseOrder() &&  // Liefervorgabe MaxDispo
        ArtBase()->IsAktivAndNotOnStore())                                          // PseudoLagerort
    {
        return longTermLack;
    }

    // Bei Liefervorgabe MaxNachliefern kein check auf longtermlack!
    if (NULL != ItemAttributes() && true == ItemAttributes()->IsRestDelivery() &&   // Liefervorgabe MaxNachliefern
        ArtBase()->IsRestDelivery())                                                // WafoTyp == '1' --> Nachliefern möglich
    {
        return longTermLack;
    }

    // TODO FN orderentryrestrictions -> device type specific ckeck. --> muss gecached werden!!!
    //pxOeRestrictionsList oerlist(Session());
    //oerlist.Select(Order().FilialNr(), pxOeRestrictions::RestrictionType_LongTermLackCheck, 1, Session()->SubDeviceType());
    //if (0 == oerlist.Entries())
    //  return longTermLack;
    if (false == Session()->IsSubDeviceTypeOf(MSV3) && false == Session()->IsSubDeviceTypeOf(XML))
    {
        return longTermLack;
    }

    try
    {
        longTermLack = Session()->getStockBookingComponentManager()->getLongTermLackChecker()->isLongTermLack(ArtikelNr_);
    }
    catch (...)
    {
        return longTermLack;
    }

    if (true == longTermLack)
    {
        MengeBestellt_ = QOrdered;
        FehlerMenge_ |= QStateNotOnHand;
        SetLongTermLack();
        /*----------------------------------------------------------------------------*/
        /*  Calc terms and prices.                                                    */
        /*----------------------------------------------------------------------------*/
        ETArtKlasse_ = ArtBase_->ArtClass(); // due to old Pharmos compatibility
        ETArtSchalter_ = ArtBase_->ArtFlags(); // requirements, we must copy these
        Zuzahlung_ = ArtBase_->Zuzahlung();
        Rabattfaehig_ = ArtBase_->DiscountCode();
        GetBasePrices(PreisTyp_);

        // logging
        if (libcsc::LoggerPool::getLoggerSession().isEnabledFor(log4cplus::INFO_LOG_LEVEL))
        {
            std::stringstream s;
            s << "pxOrderItem::checkLongTermLack: true for articleno " << ArtikelNr_;
            libcsc::LoggerPool::getLoggerSession().forcedLog(log4cplus::INFO_LOG_LEVEL, s.str(), __FILE__, __LINE__);
        }
    }
    return longTermLack;
}
