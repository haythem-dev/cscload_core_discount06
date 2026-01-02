#include "pxitem.hpp"
#include "pxdiscountdef.h"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxartbas.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"
#include "pxmanufacturergroup.hpp"
#include "pxstockbooking.hpp"
#include "pxarticlecodes.hpp"
#include "pxitemdiscount.hpp"
#include <cscorderpos/componentmanager/cscorderposcomponentmanager.h>
#include <cscorderpos/cscorderpossplittinfo/icscorderpossplittinforepository.h>
#include <cscorderpos/cscorderpossplittinfo/icscorderpossplittinfo.h>
#include <cscorderpos/cscorderpossplittinfo/cscorderpossplittinfo.h>
#include <cscorderpos/cscorderpossplittinfo/cscorderpossplittinfoptr.h>

#include <ibt/componentmanager/ibtcomponentmanager.h>
#include <ibt/ibtrequest/ibtrequestrepository.h>
#include <ibt/ibtrequest/iibtrequestptr.h>
#include <ibt/ibtrequest/iibtrequest.h>
#include <ibt/ibtrequest/ibtrequestkey.h>

#include <ibt/ibtresponse/ibtresponserepository.h>
#include <ibt/ibtresponse/iibtresponse.h>


extern bool pxGlobalNoDatabaseWrite;
extern bool pxGlobalNoWriteToLog;

/*----------------------------------------------------------------------------*/
/*  Item entry core method. Used to identify and order stocked products.      */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: InitOrderItem_Core
(
    const long      ArtikelNr,             // must read ArtBase via this number
    const long      Menge,                 // desired product quantity
    const long      MengeNatra,            // quantity in kind
    const long      MengeNachfrage,        // quantity in kind
    BookingType     btype,                 // item/quantity booking type
    ItemType        PosTyp,                // product identification mode
    int             flags,                 // internal posting flags
    const basar::VarString& Batch,
    const bool      IsFixBatch,
    bool* bStockNotOk
)
{
    ArtikelNr_     = ArtikelNr;         // copy these
    PosTyp_        = PosTyp;            // into self
    pxCustBase&       customer   = *(Order().Customer());

    // check if article is included in Tender
    if( NULL != getOrder() )
    {
        if( getOrder()->isTenderOrder() )
        {
            if( !getOrder()->isArticlePartOfTender( ArtikelNr ) )
            {
                FehlerArtikel_ = ArtStateNotInTender;
                MengeBestellt_ = Menge;
                ExternalCondition(CMsgStream(), CMSG_ITM_ARTICLE_NOT_IN_TENDER, ArtikelNr_);
                HandleError();
                return ErrorState();
            }
        }
    }

    if ( ArtBase(cDBGET_FORUPDATE) )    // read and lock product base object
    {
        if ( !ArtBase_->IsGoodState() )
        {
            if ( pxGlobalNoDatabaseWrite)
                pxGlobalNoWriteToLog = true;
            FehlerArtikel_ = ArtStateNotFound;
            MengeBestellt_ = Menge;
            PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
            ExternalCondition(CMsgStream(), CMSG_ITM_NOT_ONSTOCK, ArtikelNr_);
            pxGlobalNoWriteToLog = false;
            HandleError();                   // product or return the error
            return ErrorState();
        }

        if (ArtBase_->IsNotSaleable())
        {
            if ( Session()->isFrance() && Order().Param()->IsAnzPrintCode() )
            {
                CodeBlocage_ = ArtBase_->CodeBlocage();
                nString CBPrintCode;
                nMessage pCode( CBPrintCode = ArtBase_->GetCBPrintCode());
                ExternalError(pCode);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ART_NOTACTIVE, ArtikelNr_);
            }
            ArtBase_->Put();              // unlock artbase
            FehlerArtikel_ = ArtStateNotFound;
            MengeBestellt_ = Menge;
            //nError::operator = (ArtBase_->Error()); // copy error object
            HandleError();                   // product or return the error
            return ErrorState();
        }

        if (ArtBase_->IsStopSelling())   // stock difference
        {
            FehlerMenge_ |= QStateNotOnHand;
            MengeBestellt_ = Menge;
            //PosTyp_ = TypeProductUnknown;    // create an order item for an unknown // Heinlein, 2014-10-02 auskommentiert CMSG_ITM_STOCK_DIFFERENCE
            ExternalCondition(CMsgStream(), CMSG_ITM_STOCK_DIFFERENCE, ArtBase_->ArtikelNr());
            SetInhibitTransferBem();      // do not transfer text to pharmos
            ArtBase_->Put();                 // unlock artbase
            HandleError();                   // product or return the error
            return ErrorState();
        }

        // Do not book Article marked as ProduserQuota for non Video devices
        if ( ArtBase_->IsProduserQuota() &&  (!Session()->Device()->IsVideo()) )
        {
            ArtBase_->Put();                         // unlock artbase
            SetProduserQuotaDefect();                 // Info for caller
            FehlerMenge_  |= QStateNotOnHand;
            FehlerArtikel_ = ArtStateNotAuthorized;
            MengeBestellt_ = Menge;
            HandleError();
            return ErrorState();
        }

        if ( ArtBase_->IsNotViaDCT() || ArtBase_->IsNotViaXML() )
        {
            if ( (!Session()->Device()->IsVideo()) && ( !(flags & bPOST_RANGEARTICLE ) ) )      // is DCT (data communication terminal)
            {
                ArtBase_->Put();                         // unlock artbase
                FehlerArtikel_ = ArtStateNotOverDct;     // Info for caller
                FehlerMenge_  |= QStateNotOnHand;
                MengeBestellt_ = Menge;
                if ( Session()->isFrance() && Order().Param()->IsAnzPrintCode() )
                {
                    CodeBlocage_ = ArtBase_->CodeBlocage();
                    nString CBPrintCode;
                    nMessage pCode( CBPrintCode = ArtBase_->GetCBPrintCode());
                    ExternalError(pCode);
                    //ArtBase_->ExternalError(pCode);
                    //nError::operator = (ArtBase_->Error()); // copy error object
                    HandleError();                   // product or return the error
                    return ErrorState();
                }
                else
                {
                    HandleError();
                    return ErrorState();
                }
            }
        }
        // check KonsigPartnerNr() in Ivrylab
        if ( Session()->isFrancePrewhole() && ArtBase_->KonsigPartnerNr() > 0 )
        {
            pxManufacturerGroupList *ManufacturerGroupList = new pxManufacturerGroupList(Session());
            ManufacturerGroupList->SetBranchNo(customer.FilialNr());
            ManufacturerGroupList->SetCustomerNo(customer.KundenNr());
            if(!ManufacturerGroupList->SelectExist(ArtBase_->KonsigPartnerNr()))
            {
                FehlerArtikel_ = ArtStateNotAuthorized;
                MengeBestellt_ = 0;
                if ( Session()->Device()->IsVideo() )      // just for video devices
                {
                    ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
                }
                else
                {
                    ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
                    ArtBase_->Put();               // unlock artbase
                }
                HandleError();
                return ErrorState();
            }
            delete ManufacturerGroupList;
        }
        // Authorization check (skipped if server's auto item posting is active):
        if ( !(flags & bPOST_AUTO_ITEM) &&
             !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
             !(ArtBase_->ArtClass().IsAuthorized(Order().Customer()->ArtClass())) )
        {                                // then: customer no authorized
            FehlerArtikel_ = ArtStateNotAuthorized;
            MengeBestellt_ = 0;
            if ( Session()->Device()->IsVideo() )      // just for video devices
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
                ArtBase_->Put();               // unlock artbase
            }
            HandleError();
            return ErrorState();
        }
        // check KonsigPartnerNr()
        if ( !(flags & bPOST_AUTO_ITEM) && ArtBase_->KonsigPartnerNr() > 0 &&
             customer.CustomerGroupFlagsList()->IsNoConsignmentPermission() )
        {                                // then: customer no authorized
            FehlerArtikel_ = ArtStateNotAuthorized;
            MengeBestellt_ = 0;
            if ( Session()->Device()->IsVideo() )      // just for video devices
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
                ArtBase_->Put();               // unlock artbase
            }
            HandleError();
            return ErrorState();
        }

        // Check MedProdABGVerord:
        if ( !(flags & bPOST_AUTO_ITEM) &&
             !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
             (ArtBase_->IsMedProdABGVerord()) && !(Order().Customer()->Flags().IsMedProdABGVerord()))
        {                                // then: customer no authorized
            FehlerArtikel_ = ArtStateNotAuthorized;
            MengeBestellt_ = 0;
            if ( Session()->Device()->IsVideo() )      // just for video devices
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
                ArtBase_->Put();               // unlock artbase
            }
            HandleError();
            return ErrorState();
        }
        // Check Psychotropical stuff:
        if ( !(flags & bPOST_AUTO_ITEM) &&
             !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
             (ArtBase_->IsKzPsychoStoffe()) && !(Order().Customer()->IsPsychoAllowed()))
        {                                // then: customer no authorized
            FehlerArtikel_ = ArtStateNotAuthorized;
            MengeBestellt_ = 0;
            if ( Session()->Device()->IsVideo() )      // just for video devices
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
                ArtBase_->Put();               // unlock artbase
            }
            HandleError();
        }
        else
        {
            // post item:
            if ( PostOrderQuantity(Menge, MengeNatra, MengeNachfrage, btype, flags, cDEFAULT, Batch.c_str(), IsFixBatch, bStockNotOk) == nSTATE_GOOD )
            {
                IBTSubstitution(Menge, MengeNatra, MengeNachfrage, btype, flags);
                if ( ArtBase_ )
                {
                    CodeBlocage_ = ArtBase_->CodeBlocage();
                    ArtBase_->Put();           // update product base table
                    ManualMaintenance();       // set userbit
                    if ( IsDelayedDelivery() )
                    {
                        FehlerMenge_ |= QStateDelayedDelivery; // set quantity state
                    }
                }
            }
            else
            {
                HandleError();
            }
        }
    }
    else                                // could not find product
    {
        FehlerArtikel_ = ArtStateNotFound;
        MengeBestellt_ = Menge;
        PosTyp_ = TypeProductUnknown;   // create an order item for an unknown
        HandleError();                  // product or return the error
    }                                   // if input is from a video device

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Item entry core method. Used to identify and order stocked products.      */
/*  AuxDelivery posting                                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: InitOrderItem_08
(
    const long  ArtikelNr,             // must read ArtBase via this number
    const long  Menge,                 // desired product quantity
    const long  MengeNatra,            // quantity in kind
    const long  MengeNachfrage,        // quantity in kind
    const short VerbundFiliale,        // auxdelivery company
    BookingType  btype,                 // item/quantity booking type
    ItemType     PosTyp,                // product identification mode
    int          flags                  // internal posting flags
)
{
   //xDevice *device = Session()->Device(); // point at device object
    ArtikelNr_     = ArtikelNr;         // copy these
    PosTyp_        = PosTyp;            // into self
    pxCustBase&       customer   = *(Order().Customer());

    if ( ArtBase(cDBGET_FORUPDATE) )    // read and lock product base object
    {
        if ( !ArtBase_->IsGoodState() )
        {
            if ( pxGlobalNoDatabaseWrite)
                pxGlobalNoWriteToLog = true;
            FehlerArtikel_ = ArtStateNotFound;
            MengeBestellt_ = Menge;
            PosTyp_ = TypeProductUnknown;    // create an order item for an unknown
            ExternalCondition(CMsgStream(), CMSG_ITM_NOT_ONSTOCK, ArtikelNr_);
            pxGlobalNoWriteToLog = false;
            HandleError();                   // product or return the error
            return ErrorState();
        }

        if (ArtBase_->IsNotSaleable())
        {
            if ( Session()->isFrance() && Order().Param()->IsAnzPrintCode() )
            {
                CodeBlocage_ = ArtBase_->CodeBlocage();
                nString CBPrintCode;
                nMessage pCode( CBPrintCode = ArtBase_->GetCBPrintCode());
                ExternalError(pCode);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ART_NOTACTIVE, ArtikelNr_);
            }
            ArtBase_->Put();              // unlock artbase
            FehlerArtikel_ = ArtStateNotFound;
            MengeBestellt_ = Menge;
            HandleError();                   // product or return the error
            return ErrorState();
        }

        if (ArtBase_->IsStopSelling())   // stock difference
        {
            FehlerMenge_ |= QStateNotOnHand;;
            MengeBestellt_ = Menge;
            //PosTyp_ = TypeProductUnknown;    // create an order item for an unknown // Heinlein, 2014-10-02 auskommentiert CMSG_ITM_STOCK_DIFFERENCE
            ExternalCondition(CMsgStream(), CMSG_ITM_STOCK_DIFFERENCE, ArtBase_->ArtikelNr());
            SetInhibitTransferBem();      // do not transfer text to pharmos
            ArtBase_->Put();                 // unlock artbase
            HandleError();                   // product or return the error
            return ErrorState();
        }

        if ( ArtBase_->IsNotViaDCT() || ArtBase_->IsNotViaXML() )
        {
            if ( (!Session()->Device()->IsVideo()) && ( !(flags & bPOST_RANGEARTICLE ) ) )      // is DCT (data communication terminal)
            {
                ArtBase_->Put();                         // unlock artbase
                FehlerArtikel_ = ArtStateNotOverDct;     // Info for caller
                FehlerMenge_ |= QStateNotOnHand;
                MengeBestellt_ = 0;
                if ( Session()->isFrance() && Order().Param()->IsAnzPrintCode() )
                {
                    CodeBlocage_ = ArtBase_->CodeBlocage();
                    nString CBPrintCode;
                    nMessage pCode( CBPrintCode = ArtBase_->GetCBPrintCode());
                    ExternalError(pCode);
                    HandleError();                   // product or return the error
                    return ErrorState();
                }
                else
                {
                    HandleError();
                    return ErrorState();
                }
            }
        }

        // Do not book Article marked as ProduserQuota for non Video devices
        if ( ArtBase_->IsProduserQuota() &&  (!Session()->Device()->IsVideo()) )
        {
            ArtBase_->Put();                         // unlock artbase
            SetProduserQuotaDefect();                 // Info for caller
            FehlerMenge_  |= QStateNotOnHand;
            FehlerArtikel_ = ArtStateNotAuthorized;
            MengeBestellt_ = Menge;
            HandleError();
            return ErrorState();
        }

        // check KonsigPartnerNr() in Ivrylab
        if ( Session()->isFrancePrewhole() && ArtBase_->KonsigPartnerNr() > 0 )
        {
            pxManufacturerGroupList *ManufacturerGroupList = new pxManufacturerGroupList(Session());
            ManufacturerGroupList->SetBranchNo(customer.FilialNr());
            ManufacturerGroupList->SetCustomerNo(customer.KundenNr());
            if(!ManufacturerGroupList->SelectExist(ArtBase_->KonsigPartnerNr()))
            {
                FehlerArtikel_ = ArtStateNotAuthorized;
                MengeBestellt_ = 0;
                if ( Session()->Device()->IsVideo() )      // just for video devices
                {
                    ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
                }
                else
                {
                    ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
                    ArtBase_->Put();               // unlock artbase
                }
                HandleError();
                return ErrorState();
            }
            delete ManufacturerGroupList;
        }
        // Authorization check (skipped if server's auto item posting is active):
        if ( !(flags & bPOST_AUTO_ITEM) &&
             !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
             !(ArtBase_->ArtClass().IsAuthorized(Order().Customer()->ArtClass())) )
        {                                // then: customer no authorized
            FehlerArtikel_ = ArtStateNotAuthorized;
            MengeBestellt_ = 0;
            if ( Session()->Device()->IsVideo() )      // just for video devices
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
                ArtBase_->Put();               // unlock artbase
            }
            HandleError();
            return ErrorState();
        }
        // check KonsigPartnerNr()
        if ( !(flags & bPOST_AUTO_ITEM) && ArtBase_->KonsigPartnerNr() > 0 &&
             customer.CustomerGroupFlagsList()->IsNoConsignmentPermission() )
        {                                // then: customer no authorized
            FehlerArtikel_ = ArtStateNotAuthorized;
            MengeBestellt_ = 0;
            if ( Session()->Device()->IsVideo() )      // just for video devices
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
                ArtBase_->Put();               // unlock artbase
            }
            HandleError();
            return ErrorState();
        }

        // Check MedProdABGVerord:
        if ( !(flags & bPOST_AUTO_ITEM) &&
             !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
             (ArtBase_->IsMedProdABGVerord()) && !(Order().Customer()->Flags().IsMedProdABGVerord()))
        {                                // then: customer no authorized
            FehlerArtikel_ = ArtStateNotAuthorized;
            MengeBestellt_ = 0;
            if ( Session()->Device()->IsVideo() )      // just for video devices
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
                ArtBase_->Put();               // unlock artbase
            }
            HandleError();
            return ErrorState();
        }
        // Check Psychotropical stuff:
        if ( !(flags & bPOST_AUTO_ITEM) &&
             !(Order().BatchSchreiben() == cORTYPE_AUXILIARY) &&
             (ArtBase_->IsKzPsychoStoffe()) && !(Order().Customer()->IsPsychoAllowed()))
        {                                // then: customer no authorized
            FehlerArtikel_ = ArtStateNotAuthorized;
            MengeBestellt_ = 0;
            if ( Session()->Device()->IsVideo() )      // just for video devices
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED);
            }
            else
            {
                ExternalCondition(CMsgStream(), CMSG_ITM_NOT_AUTHORIZED_DCT,ArtikelNr_);
                ArtBase_->Put();               // unlock artbase
            }
            HandleError();
        }
        else
        {                                // post item:
            if ( Session()->Device()->IsVideo() )      // just for video devices
            {
                if ( VerbundFiliale == cDEFAULT ) // if no auxcompany, then
                    flags |= bPOST_AUXDELIVERY;   // post from the first auxcompany
            }                                    // if possible
            if ( PostOrderQuantity(Menge, MengeNatra, MengeNachfrage, btype, flags, VerbundFiliale) == nSTATE_GOOD )
            {
                IBTSubstitution(Menge, MengeNatra, MengeNachfrage, btype, flags);
                if ( ArtBase_ )
                {
                    CodeBlocage_ = ArtBase_->CodeBlocage();
                    ArtBase_->Put();           // update product base table
                    ManualMaintenance();       // set userbit
                    if ( IsDelayedDelivery() )
                    {
                        FehlerMenge_ |= QStateDelayedDelivery; // set quantity state
                    }
                }
                else
                {
                    HandleError();
                }
            }
        }
    }
    else                                // could not find product
    {
        FehlerArtikel_ = ArtStateNotFound;
        MengeBestellt_ = Menge;
        PosTyp_ = TypeProductUnknown;   // create an order item for an unknown
        HandleError();                  // product or return the error
    }                                   // if input is from a video device

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Create a text item.                                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: NewOrderTextItem
(
    const nString& Text,                // Create a text position
    const long Menge
)
{
    ArtikelNr_     = 0;
    Bemerkungen_   = Text;
    MengeBestellt_ = Menge;
    PosTyp_        = pxOrderItem::TypeTextOnly;
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Create an item for a product not known in stock. This may be an article   */
/*  for disposal, to be ordered via customer service. That's why we call it   */
/*  a dispo item. Data entry/data query is done thru a tDISPOITEM structure.  */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: InitOrderItem_15
(
    tDISPOITEM& s,                      // dispo item structure
    BookingType btype,
    bool addSubSequent
)
{
    pxVerbund::subsequentDelivery::pxDeliveryPos* delpos = NULL;
    //Device *device = Session()->Device(); // point at device object
    ArtDispo_ = new pxArtDispo(Session());
    PosTyp_ = TypeDispoItem;
    if ( Session()->Device()->IsDCT() && !Session()->IsSubDeviceTypeOf(DISPO) )
        SetTextDategAlpha();
    ArtikelNr_ = 0;

    if ( DispoSanity(s, btype) == nSTATE_GOOD && DispoUpdate(s, btype) == nSTATE_GOOD )
    {
        PharmosDispoItem();              //special handling
        ArtDispo_->Put();
        ManualMaintenance();
        if (addSubSequent == true)
        {
            // for some special cases (eg. text items for OCP freight costs) no subsequent delivery will be created
            delpos = NewDeliveryPos( pxVerbund::subsequentDelivery::pxDPT_DISPOSAL_ITEM );
            delpos->Put();
        }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item for a stocked product using string input.         */
/*  Mainly used when invoked via the order transmission interface.            */
/*  When input is from a non-video device, input errors are flagged, but      */
/*  errors set in the nError object instance are cleared. This allows for     */
/*  entering an order item under nearly all circumstances.                    */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: NewOrderItemRemarks
(
    const long ProductId,           // article identification
    const long QuanOrdered          // quantity ordered
)
{
    if ( IsArtStateGood() )
    {
        InitOrderItem_Core(ProductId, QuanOrdered, 0, QuanOrdered, BookingTypeDefault, TypeProductStocked, bPOST_DEFAULT);
    }
    else                                // Product id format error
    {                                   // create a 'text' order item
        MengeBestellt_ = QuanOrdered;
        PosTyp_ = TypeProductUnknown;
        ArtikelNr_ = ProductId;
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item for a stocked product using string input.         */
/*  Mainly used when invoked via the order transmission interface.            */
/*  When input is from a non-video device, input errors are flagged, but      */
/*  errors set in the nError object instance are cleared. This allows for     */
/*  entering an order item under nearly all circumstances.                    */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: InitOrderItem_12
(
    const long ArticleNo,               // (internal) article identification (articleno)
    const long QuanOrdered,             // quantity ordered
    pxItemAttributes* attributes,       // ordering attributes
    const long  MengeNatra,             // quantity in kind
    const basar::VarString& Batch,
    const bool IsFixBatch
)
{
    long qtyNatra = (MengeNatra < 0) ? 0 : MengeNatra;
    pxCustBase&       customer = *(Order().Customer());
    if ( IsArtStateGood() )
    {
        ItemAttributes_ = attributes;
        InitOrderItem_Core(ArticleNo, QuanOrdered, qtyNatra, QuanOrdered, BookingTypeDefault, TypeProductStocked, bPOST_DEFAULT, Batch, IsFixBatch);
        if ( customer.Flags().IsVersandApo() || Session()->isSerbia() || Session()->isFrance() )
        {
            if( !Order().ReferenceNr().IsEmpty() )
                KdAuftragBestellNr_ = Order().ReferenceNr();
        }
    }
    else                                // Product id format error
    {                                   // create a 'text' order item
        MengeBestellt_ = QuanOrdered;
        PosTyp_ = TypeProductUnknown;
        ArtikelNr_ = ArticleNo;
    }

    if ( customer.Flags().IsVersandApo() && (Order().FirstTransPos() == Order().AnzPos()))
    {
        Order().IncreaseAnzAuf();
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item for a stocked product using input from a          */
/*  delivery position record(automatic posting of delivery positions).        */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: InitOrderItem_16
(
    const long ProductId,              // article identification
    const long QuanOrdered,            // quantity ordered
    const nString& Remarks,             // product remarks
    BookingType  bt                     // item/quantity booking type
)
{
    BookingType remarksbtype;
    BookingType btype;
    int        flags;
    remarksbtype  = ConvertRemarks(Remarks);
    btype = (( bt == BookingTypeDefault ) ? remarksbtype : bt);
    flags = (( bt == BookingTypeDefault ) ? bPOST_DEFAULT : bPOST_IGN_LACK);

    InitOrderItem_Core(ProductId, QuanOrdered, 0, QuanOrdered, btype, TypeProductStocked, flags);
    if (IsBookRestDelivery())
        SetNachLieferungVerarbeitet();
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item using pxOrderItem object.                         */
/*  There is no quantity booking,just few members are transported into        */
/*  this item                                                                 */
/*----------------------------------------------------------------------------*/
int
pxOrderItem :: CopyOrderItem
(
    pxOrderItem* src,
    BookingType  bt,                     // item/quantity booking type
    SplittTypeEnum s
)
{
    MengeBestellt_        = src->MengeBestellt();
    MengeBestaetigt_      = src->MengeBestaetigt();
    MengeGeliefert_       = src->MengeGeliefert();
    MengeAbgebucht_       = src->MengeAbgebucht();
    MengeNatra_           = src->MengeNatra();
    PosTyp_               = src->PosTyp();
    ArtikelNr_            = src->ArtikelNr();
    FehlerMenge_          = src->QState();
    Bemerkungen_          = src->Bemerkungen();
    FehlerArtikel_        = src->ArtState();
    MengeNatraGrossH_     = src->MengeNatraGrossH();
    MengeNatraHerst_      = src->MengeNatraHerst();
    PreisEKApo_           = src->PreisEKApo();
    PreisVKApo_           = src->PreisVKApo();
    PreisEKApoNetto_      = src->PreisEKApoNetto();
    PreisEKGrosso_        = src->PreisEKGrosso();
    PreisEKGrossoNA_      = src->PreisEKGrossoNA();
    RabattFest_           = src->RabattFest();
    RabattFestDM_         = src->RabattFestDM();
    ArtBestNachUpd_       = src->ArtBestNachUpd();
    UhrZeitBestNachUpd_   = src->UhrZeitBestNachUpd();
    Zuzahlung_            = src->Zuzahlung();
    SendeStatus_          = src->SendeStatus();
    MengeVorausBezug_     = src->MengeVorausBezug();
    Rabattfaehig_         = src->Rabattfaehig();
    ETPosSchalter_        = src->ItemFlags();
    ETArtKlasse_          = src->ETArtKlasse_;
    ETArtSchalter_        = src->ETArtSchalter_;
    SalesTaxRate_         = src->SalesTaxRate_;
    KdAuftragBestellNr_   = src->KdAuftragBestellNr_;
    CodeBlocage_          = src->CodeBlocage_;
    PreisEKApoFree_       = src->PreisEKApoFree();
    PreisTyp_             = src->PreisTyp();
    ArticleNoPack_        = src->ArticleNoPack();
    PreisFaktur_          = src->PreisFaktur();
    MaxTargetNo_          = src->MaxTargetNo();
    ContainerLevel_       = src->ContainerLevel();
    RefundValue_          = src->RefundValue();
    PromotionNo_          = src->PromotionNo();
    CodeType_             = src->CodeType();
    ArticleCode_          = src->ArticleCode();

    copyGenericOrderRemarks(src);

    // TODO FN evaluate UndoRedo... split methods

    if (src->MengeBestelltOrg() > 0)
    {
        MengeBestelltOrg_ = src->MengeBestelltOrg();
    }
    else
    {
        MengeBestelltOrg_ = src->MengeBestellt();
    }
    switch ( bt )
    {
        case SeparateDefect  :
        {
            //! \note keine Reservierungsumbuchung, MengeAbgebucht_ ist 0.
            SetDefektPosition();
            break;
        }
        case DelayedDelivery :
        {
            if (IsDisponieren())
            {
                Session()->getStockBooking()->CancelReservationForOpenOrder(*src, src->MengeAbgebucht());
                UndoRedoDelayedPurchaseItem(src); // calls quantity posting
            }
            else if (IsNachliefern())
            {
                Session()->getStockBooking()->CancelReservationForOpenOrder(*src, src->MengeAbgebucht());
                UndoRedoDelayedRestDeliveryItem(src); // calls quantity posting
            }
            else
            {
                Session()->getStockBooking()->CancelReservationForOpenOrder(*src, src->MengeAbgebucht());
                Session()->getStockBooking()->AddReservationForOpenOrder(*this, src->MengeAbgebucht());
            }
            break;
        }
        case SeparateContainer  :
        {
            // TODO FN calculate container
            // note container might be split into same order or in a separate order!!!!
            CalculateContainer(src);
            break;
        }
        case SeparateArticle  :
        {
            Session()->getStockBooking()->CancelReservationForOpenOrder(*src, src->MengeAbgebucht());
            Session()->getStockBooking()->AddReservationForOpenOrder(*this, src->MengeAbgebucht());
            break;
        }
        case AuxDelivery  :
        {
            UndoRedoAuxdelivery(src, MengeBestelltOrg_);
            break;
        }
        case ReferenceItem  :
        {
            UndoRedoReferenceItem(src);  // calls src->UndoItem and calls quantity posting
            break;
        }
        case AuxDeliveryComplete  :
        {
            Session()->getStockBooking()->CancelReservationForOpenOrder(*src, src->MengeAbgebucht());
            UndoRedoAuxdeliveryComplete(src);
            break;
        }
        case RestDeliveryItem  :
        {
            Session()->getStockBooking()->CancelReservationForOpenOrder(*src, src->MengeAbgebucht());
            UndoRedoRestDeliveryItem(src);
            break;
        }
        case PurchaseItem  :
        {
            Session()->getStockBooking()->CancelReservationForOpenOrder(*src, src->MengeAbgebucht());
            UndoRedoPurchaseItem(src);
            break;
        }
        case DispoItem  :
        {
            Session()->getStockBooking()->CancelReservationForOpenOrder(*src, src->MengeAbgebucht());
            UndoRedoDispoItem(src);
            break;
        }
        default :
            break;
    }

    if (src->Order().BatchSchreiben() == cORTYPE_AUXILIARY) //change ibtreponse to new Order
    {
        libcsc::ibt::IIbtResponseRepositoryPtr responseRepo = src->Session()->getIbtComponentManager()->createIbtResponseRepository();
        libcsc::ibt::IIbtResponsePtr response = responseRepo->findIbtResponse(src->KdAuftragNr(), src->PosNr());
        if (NULL != response.get())
        {
            response->setIbtOrderNo(this->KdAuftragNr());
            response->setIbtOrderPosNo(this->PosNr());
            responseRepo->saveIbtResponse(response);
        }
    }

    if (SplittType_IBT == s || SplittType_Priso == s)
    {
        WriteOrderPosSplittInfo(src, s);
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
// get IBT picking data
/*----------------------------------------------------------------------------*/
libcsc::cscorder::domMod::CSCOrderIBTPickingdataCollectionPtr pxOrderItem::getIBTPickingDataCollection()
{
    libcsc::cscorder::repo::ICSCOrderIBTPickingdataRepositoryPtr cscOrderIBTPickingdataRepository = this->Session()->getCSCOrderComponentManager()->getCSCOrderIBTPickingdataRepository();
    return cscOrderIBTPickingdataRepository->findPickingdata(this->Order().KdAuftragNr(), this->PosNr());
}

/*----------------------------------------------------------------------------*/
// get IBT quantity from splitted order/position
/*----------------------------------------------------------------------------*/
long pxOrderItem::getOriginalIBTQtyFromSplittedOrder()
{
    long retVal = 0;

    libcsc::cscorderpos::repo::ICSCOrderposSplittinfoRepositoryPtr repo;
    repo = Session()->getCSCOrderposComponentManager()->getCSCOrderposSplittinfoRepository();

    libcsc::cscorderpos::domMod::ICSCOrderposSplittinfoPtr splittInfo;
    splittInfo = repo->findSplittinfo(KdAuftragNr(), PosNr(), SplittType_IBT); // OK
    if (splittInfo.get() != NULL)
    {
        if (splittInfo->getOrderNo() > 0 && splittInfo->getOrderPosNo() > 0)
        {
            libcsc::ibt::IIbtRequestRepositoryPtr ibtRepo = this->Session()->getIbtComponentManager()->createIbtRequestRepository();
            libcsc::ibt::IIbtRequestPtr ibtRequest = ibtRepo->findIbtRequestByKey(
                libcsc::ibt::IbtRequestKey(this->Order().FilialNr(), splittInfo->getOrderNo(), splittInfo->getOrderPosNo())
            );

            if (NULL != ibtRequest.get())
            {
                if (!ibtRequest->getIbtRequestId().isUnset())
                {
                    retVal = ibtRequest->getQuantity();
                }
            }
        }
    }

    return retVal;
}

/*----------------------------------------------------------------------------*/
// get IBT quantity from splitted order/position
/*----------------------------------------------------------------------------*/
short pxOrderItem::getOriginalIBTBranchFromSplittedOrder()
{
    short retVal = 0;

    libcsc::cscorderpos::repo::ICSCOrderposSplittinfoRepositoryPtr repo;
    repo = Session()->getCSCOrderposComponentManager()->getCSCOrderposSplittinfoRepository();

    libcsc::cscorderpos::domMod::ICSCOrderposSplittinfoPtr splittInfo;
    splittInfo = repo->findSplittinfo(KdAuftragNr(), PosNr(), SplittType_IBT); // OK
    if (splittInfo.get() != NULL)
    {
        if (splittInfo->getOrderNo() > 0 && splittInfo->getOrderPosNo() > 0)
        {
            libcsc::ibt::IIbtRequestRepositoryPtr ibtRepo = this->Session()->getIbtComponentManager()->createIbtRequestRepository();
            libcsc::ibt::IIbtRequestPtr ibtRequest = ibtRepo->findIbtRequestByKey(
                libcsc::ibt::IbtRequestKey(this->Order().FilialNr(), splittInfo->getOrderNo(), splittInfo->getOrderPosNo())
            );

            if (NULL != ibtRequest.get())
            {
                if (!ibtRequest->getIbtRequestId().isUnset())
                {
                    retVal = ibtRequest->getIbtBranchNo();
                }
            }
        }
    }

    return retVal;
}

/*----------------------------------------------------------------------------*/
// write cscorderpossplittinfo
/*----------------------------------------------------------------------------*/
void pxOrderItem::WriteOrderPosSplittInfo(const pxOrderItem* src, const SplittTypeEnum splittType)
{
    libcsc::cscorderpos::repo::ICSCOrderposSplittinfoRepositoryPtr repo;
    libcsc::cscorderpos::domMod::ICSCOrderposSplittinfoPtr splittInfo;

    repo = Session()->getCSCOrderposComponentManager()->getCSCOrderposSplittinfoRepository();
    splittInfo = repo->findSplittinfo(src->KdAuftragNr(), src->PosNr(), splittType); // OK
    if (splittInfo.get() == NULL)
    {
        splittInfo = libcsc::cscorderpos::domMod::CSCOrderposSplittinfoPtr(new libcsc::cscorderpos::domMod::CSCOrderposSplittinfo());
    }
    splittInfo->setCscOrderNo(src->KdAuftragNr());
    splittInfo->setCscOrderPosNo(src->PosNr());
    splittInfo->setSplittType(splittType);
    splittInfo->setOriginal(SplittPosition);
    splittInfo->setOrderNo(this->KdAuftragNr());
    splittInfo->setOrderPosNo(this->PosNr());
    repo->saveSplittinfo(splittInfo);

    splittInfo = repo->findSplittinfo(this->KdAuftragNr(), this->PosNr(), splittType); // OK
    if (splittInfo.get() == NULL)
    {
        splittInfo = libcsc::cscorderpos::domMod::CSCOrderposSplittinfoPtr(new libcsc::cscorderpos::domMod::CSCOrderposSplittinfo());
    }
    splittInfo->setCscOrderNo(this->KdAuftragNr());
    splittInfo->setCscOrderPosNo(this->PosNr());
    splittInfo->setSplittType(splittType);
    splittInfo->setOriginal(OriginalPosition);
    splittInfo->setOrderNo(src->KdAuftragNr());
    splittInfo->setOrderPosNo(src->PosNr());
    repo->saveSplittinfo(splittInfo);
}

/*----------------------------------------------------------------------------*/
/*  Test if an error occurred and input is from a non-video device.           */
/*  The error is cleared in that case, and the error msg string is copied     */
/*  to 'Bemerkungen'.                                                         */
/*----------------------------------------------------------------------------*/
void
pxOrderItem :: HandleError(int flags)
{
    if ( !IsGoodState() && !(flags & bPOST_AUTO_ITEM) && !Session()->Device()->IsVideo() )
    {
        if (Session()->isBulgaria())
        {
            if ( ErrorNumber() != 30051 && ErrorNumber() != 30050 ) // rubbish, not fine methode, has to be worked up
            {
                Bemerkungen_ = ErrorString();
                Bemerkungen_.Strip(nString::cTRAILING, '\n');
                ClearError();                    // this prevents rejecting the order
            }
        }
        else
        {
            Bemerkungen_ = ErrorString();
            Bemerkungen_.Strip(nString::cTRAILING, '\n');
            ClearError();                    // this prevents rejecting the order
        }
    }
}

/*----------------------------------------------------------------------------*/
/*  Convert ordering remarks. Returns BookingType.                            */
/*----------------------------------------------------------------------------*/
pxOrderItem::BookingType
pxOrderItem :: ConvertRemarks
(
    const nString& Remarks
)
{
    pxCustBase *customer = Order().Customer();
    BookingType retval   = BookingTypeDefault;
    if (Remarks == (const char*)"DS")
        retval = PurchaseOrder;
    if (Remarks == (const char*)"DS" && customer->IsUnusualAuxDeliveryUser())
        retval = AuxDelivery;
    if (Remarks == (const char*)"NL")
        retval = RestDelivery;
    if (Remarks == (const char*)"VB" && !customer->IsAuxDeliveryInfoUser())
        retval = AuxDelivery;
    if (Remarks == (const char*)"NR")
        retval = ReservedRestDelivery;

    return retval;
}

//----------------------------------------------------------------------------
//  Calculate new discount for customer groups 12 and 15
//
//      Returns -1, if nothing must be calculated (no promotion)
//
//----------------------------------------------------------------------------
double
pxOrderItem :: calculateNewDiscount
(
)
{
    if(0==this->PromotionNo())
        return -1.0;

    nMoney discountValue = PreisEKGrosso_ - PreisFakturCstGr12_;

    pxCustBase& customer = *(Order().Customer());
    double discountPct=0.0;
    if(customer.IsCommercialRounding())     // commerercial calculation
        discountPct = discountValue / (PreisEKGrosso_ - discountValue);
    else    // mathematical calculation
        discountPct = discountValue / PreisEKGrosso_;

    double discount = 100.0 * discountPct;
    int i_discount=(int)discount;  // truncate
    discountPct=(double)i_discount;
    if(discountPct>100)
        discountPct=100.0;

    if(discountPct<0)
        discountPct=0.0;
    return discountPct;
}

//----------------------------------------------------------------------------
//  Changes the value inserted in kdauftragposrab before
//----------------------------------------------------------------------------
void
pxOrderItem :: changeDiscountInDB
(
    double newDiscount
)
{
    pxItemDiscountList *itemDiscList = ItemDiscountList();
    if(!itemDiscList)
        return;

    pxItemDiscount* dikp;
    pxItemDiscountListIter cursor(*itemDiscList);
    while ( (dikp = (pxItemDiscount*) ++cursor) != NULL )
    {
        if ((KdAuftragNr_ == dikp->KdAuftragNr()) && (PosNr_ == dikp->PosNr()))
        {
            // grossprofit discount is handled as cash discount, so there is only one entry in kdauftragposrab
            if ((BestBuy_ValuePctCash == dikp->DiscountType()) || (BestBuy_GrossProfitPct == dikp->DiscountType()))  // this is an entry for value pct cash in database
            {
                if (newDiscount <= 0.0)
                {
                    dikp->Delete();
                    delete cursor.Remove();
                    dikp = NULL;
                }
                else
                {
                    dikp->SetDiscountValuePct(newDiscount);
                    dikp->Put();
                }
            }
        }
    }
}

/*----------------------------------------------------------------------------*/
/*  GetArticleCode:                                                           */
/*  Look for the corresponding ArticleCode number by a given articleno and    */
/*  a preferred flag                                                          */
/*  It Returns a pxArticleCodes object pointer, if the corresponding entry    */
/*  within the table articlecodes is found, otherwise a NULLP will be returned*/
/*----------------------------------------------------------------------------*/
pxArticleCodes*
pxOrderItem :: GetArticleCode
(
    const long articleno
)
{
    pxArticleCodes* ArtCode = NULL;
    pxArticleCodesList* ArtCodeList = NULL;

    ArtCodeList = new pxArticleCodesList(Session());
    ArtCodeList->SelectPreferred(articleno);
    if ( ArtCodeList->Entries() )
    {
        ArtCode = new pxArticleCodes( *((pxArticleCodes*)(ArtCodeList->At(0))));
    }
    delete ArtCodeList;
    return ArtCode;
}
