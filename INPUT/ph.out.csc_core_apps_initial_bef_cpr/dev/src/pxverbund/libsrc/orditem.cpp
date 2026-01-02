/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrder:
Implementation of order item entry methods.
The following overloaded "NewOrderItem" functions create a new order item
object instance, open it for item entry processing and add it to the list.
In case of a successful construction, a pointer to the new item object
is returned, otherwise a NULL pointer is returned, and an appropiate error
is stored within the nError object of the order.
*/
#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxcustomerflags.hpp"
#include "pxcustomergrpflags.hpp"
#include "pxartbas.hpp"
#include "pxartmas.hpp"
#include "pxitem.hpp"
#include "pxitemattributes.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordtyp.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxcstot.hpp"
#include "pxartcompack.hpp"
#include "pxcpvalidityperiod.hpp"
#include "pxdiscount.hpp"
#include "pxarticlecodes.hpp"
#include "pxtenderprogress.hpp"
#include "pxordtaxvalues.hpp"
#include "pxorderposevent.hpp"
#include "pxorderpospromo.hpp"
#include "pxstockbooking.hpp"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"
#include "types/pricetypeenum.inc"
#include "types/origintypeenum.inc"
#include "types/messagecodeenum.inc"
#include "pxorderremarks.hpp"
#include <libbasarcmnutil_datetime.h>
#include <tender/repository/itenderrepository.h>
#include <discount/orderpositiondiscount/orderpositiondiscountcollection.h>
#include <discount/orderpositiondiscount/orderpositiondiscount.h>
#include <discount/orderpositiondiscount/orderpositiondiscountrepositoryptr.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepository.h>
#include <discount/orderpositiondiscount/iorderpositiondiscountrepositoryptr.h>

/*----------------------------------------------------------------------------*/
/*  Create new order item for a stocked product using the product number.     */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_03
(
    long       ArtikelNr,              // must read ArtBase via this number
    long       Menge,
    long       MengeNatra,
    long       MengeNachfrage,
    PriceTypeEnum pricetype,
    pxOrderItem::BookingType btype,
    pxOrderItem::ItemType    PosTyp,   // product identification mode
    int        flags,                  // internal posting flags
    long       MengeBestelltNatra
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        bool bStockNotOk_ = false;
        bool* bStockNotOk = &bStockNotOk_;
        item->PreisTyp(pricetype);
        item->SetPreisTypSaved(pricetype);
        item->SetMengeBestelltNatra(MengeBestelltNatra);
        item->InitOrderItem_Core(ArtikelNr, Menge, MengeNatra, MengeNachfrage, btype, PosTyp, flags, "", false, bStockNotOk);
        item = addItemAndProcess(item);

        if(bStockNotOk_)
        {
            ExternalCondition(CMsgStream(), CMSG_ART_QLACK_DISC_ARTICLE, 0, MengeNatra, ArtikelNr);
        }
    }
    return item;
}

pxOrderItem* pxOrder::NewOrderItem_03_DefaultWithAutoItemAndIgnLack(long ArtikelNr, long MengeBestellt)
{
    return NewOrderItem_03(ArtikelNr, MengeBestellt,
                           0L, 0L, FREESALE_PRICE, pxOrderItem::BookingTypeDefault,
                           pxOrderItem::TypeProductStocked,
                           bPOST_AUTO_ITEM | bPOST_IGN_LACK);
}

pxOrderItem* pxOrder::NewOrderItem_03_RangeArticle(
    long ArtikelNr, long MengeBestellt, long MengeNatra, long MengeNachfrage, PriceTypeEnum pricetype)
{
    return NewOrderItem_03(ArtikelNr, MengeBestellt,
                           MengeNatra, MengeNachfrage, pricetype, pxOrderItem::BookingTypeDefault,
                           pxOrderItem::TypeProductStocked,
                           bPOST_RANGEARTICLE);
}

pxOrderItem* pxOrder::NewOrderItem_03_NatraWithRangeArticle(
    long ArtikelNr, long MengeNatra, PriceTypeEnum pricetype)
{
    return NewOrderItem_03_RangeArticle(ArtikelNr, 0L, MengeNatra, 0L, pricetype);
}

/*----------------------------------------------------------------------------*/
/*  Create new order item for a stocked product using the product number.     */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_04
(
    long       ArtikelNr,              // must read ArtBase via this number
    long       Menge,
    long       MengeNatra,
    long       MengeNachfrage,
    double     DiscountValPctMan,
    PriceTypeEnum    pricetype,
    pxOrderItem::BookingType btype,
    pxOrderItem::ItemType    PosTyp,   // product identification mode
    int        flags,                  // internal posting flags
    long       MengeBestelltNatra
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->PreisTyp(pricetype);
        item->SetPreisTypSaved(pricetype);
        item->SetDiscountValPctMan(DiscountValPctMan);
        item->SetMengeBestelltNatra(MengeBestelltNatra);
        item->InitOrderItem_Core(ArtikelNr, Menge, MengeNatra, MengeNachfrage, btype, PosTyp, flags);
        item = addItemAndProcess(item);
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create new order item for a stocked product using the product number.     */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_02
(
    long       ArtikelNr,               // must read ArtBase via this number
    long       Menge,
    long       MengeNatra,
    long       MengeNachfrage,
    short      PromoTyp,
    short      PromotionNo,
    PriceTypeEnum    pricetype,
    pxOrderItem::BookingType btype,
    pxOrderItem::ItemType    PosTyp,    // product identification mode
    int        flags                    // internal posting flags
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->PreisTyp(pricetype);
        item->SetPreisTypSaved(pricetype);
        item->SetPromoTyp(PromoTyp);
        item->SetPromotionNo(PromotionNo);
        item->InitOrderItem_Core(ArtikelNr, Menge, MengeNatra, MengeNachfrage, btype, PosTyp, flags);
        item = AddNewItem(item);         // append it to the list of items
        calcSplittBookItem(item);
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create new order item for a stocked product using the product number.     */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_05
(
    long       ArtikelNr,               // must read ArtBase via this number
    long       Menge,
    long       MengeNatra,
    long       MengeNachfrage,
    nMoney     EKApoFree,
    PriceTypeEnum  pricetype,
    pxOrderItem::BookingType btype,
    pxOrderItem::ItemType  PosTyp,      // product identification mode
    int        flags,                   // internal posting flags
    long       MengeBestelltNatra
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->PreisTyp(pricetype);
        item->SetPreisTypSaved(pricetype);
        item->SetPreisEKApoFree(EKApoFree);
        item->SetMengeBestelltNatra(MengeBestelltNatra);
        item->InitOrderItem_Core(ArtikelNr, Menge, MengeNatra, MengeNachfrage, btype, PosTyp, flags);
        item = addItemAndProcess(item);
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create new order item for a stocked product using the product number.     */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_06
(
    long       ArtikelNr,               // must read ArtBase via this number
    long       Menge,
    long       MengeNatra,
    long       MengeNachfrage,
    nMoney     EKApoFree,
    double     DiscountValPctMan,
    PriceTypeEnum  pricetype,
    pxOrderItem::BookingType btype,
    pxOrderItem::ItemType  PosTyp,      // product identification mode
    int        flags,                   // internal posting flags
    long       MengeBestelltNatra
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->PreisTyp(pricetype);
        item->SetPreisTypSaved(pricetype);
        item->SetPreisEKApoFree(EKApoFree);
        item->SetDiscountValPctMan(DiscountValPctMan);
        item->SetMengeBestelltNatra(MengeBestelltNatra);
        item->InitOrderItem_Core(ArtikelNr, Menge, MengeNatra, MengeNachfrage, btype, PosTyp, flags);
        item = addItemAndProcess(item);
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create new order item for a stocked product using the product number.     */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_07
(
    long       ArtikelNr,               // must read ArtBase via this number
    long       Menge,
    long       MengeNatra,
    long       BatchOrderNo,
    long       BatchPosNo,
    long       MengeNachfrage,
    PriceTypeEnum  pricetype,
    pxOrderItem::BookingType btype,
    pxOrderItem::ItemType  PosTyp,      // product identification mode
    int        flags                    // internal posting flags
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->PreisTyp(pricetype);
        item->SetPreisTypSaved(pricetype);
        item->InitOrderItem_Core(ArtikelNr, Menge, MengeNatra, MengeNachfrage, btype, PosTyp, flags);
        if ( (BatchSchreiben() == cORTYPE_FR_CUSTOMER_ORDER) && item->IsNachliefern())
        {
            pxVerbund::subsequentDelivery::pxDeliveryPos* dp = item->AuxDelList()->Find(KdAuftragNr_, item->PosNr(), pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
            if (dp)
            {
                dp->SetBatchAuftragNr(BatchOrderNo);
                dp->SetBatchPosNr(BatchPosNo);
                dp->Put();
            }
        }

        // this coding has to be redesigned, because parameter for this option
        // is missing
        if ( FilialNr_ == 83 || FilialNr_ == 48 || FilialNr_ == 43 || FilialNr_ == 16 )   // Prewhole Austria and Prewhole France
        {
            SetBatchOrderNr(BatchOrderNo);   // set batchordernumber
            item->SetBatchPosNr(BatchPosNo); // set batchpositionnumber
        }
        item = addItemAndProcess(item);
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create new order AuxDeliveryItem for a stocked product using the product  */
/*  number.                                                                   */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_08
(
    long       ArtikelNr,               // must read ArtBase via this number
    long       Menge,
    short      VerbundFiliale,
    long       MengeNatra,
    long       MengeNachfrage,
    PriceTypeEnum  pricetype,
    pxOrderItem::BookingType btype,
    pxOrderItem::ItemType  PosTyp,      // product identification mode
    int        flags                    // internal posting flags
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->PreisTyp(pricetype);
        item->SetPreisTypSaved(pricetype);
        item->InitOrderItem_08(ArtikelNr, Menge, MengeNatra, MengeNachfrage, VerbundFiliale, btype, PosTyp, flags);
        item = addItemAndProcess(item);
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create new order AuxDeliveryItem for a stocked product using the product  */
/*  number include EKAPOFreePrice                                             */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_09
(
    long       ArtikelNr,               // must read ArtBase via this number
    long       Menge,
    short      VerbundFiliale,
    nMoney     EKApoFree,
    long       MengeNatra,
    long       MengeNachfrage,
    PriceTypeEnum  pricetype,
    pxOrderItem::BookingType btype,
    pxOrderItem::ItemType  PosTyp,      // product identification mode
    int        flags                    // internal posting flags
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
       item->PreisTyp(pricetype);
       item->SetPreisTypSaved(pricetype);
       item->SetPreisEKApoFree(EKApoFree);
       item->InitOrderItem_08(ArtikelNr, Menge, MengeNatra, MengeNachfrage, VerbundFiliale, btype, PosTyp, flags);
       item = addItemAndProcess(item);
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create new order with rebate and promotion type for a stocked product     */
/*  using the product                                                         */
/*  number.                                                                   */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_10
(
    long       ArtikelNr,               // must read ArtBase via this number
    long       Menge,
    long       MengeNatra,
    double     Barrabatt,
    short      PromoType,
    short      PromotionNo,
    nString&   PharmacyGroupId,
    PriceTypeEnum  pricetype
)
{
    pxOrderItem *item = NULL;
    pxOrderPosPromo* pospromo = NULL;
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    if ( PromoType == 2 )               // Promotion DiscountArticle
    {
        item =  NewOrderItem_02(ArtikelNr, 0L, Menge, 0L,
                                PromoType, PromotionNo,pricetype,
                                pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked,
                                bPOST_RANGEARTICLE);

        if (item)
        {
            item->WriteOrderPosPromo( PharmacyGroupId, 0L, 0L, 0.0, IDFNr_, PromotionNo);
        }
        return item;
    }

    item = NewItem(); // construct new item object, then let
    if (item)
    {
        item->SetDiscountValPctPromo(Barrabatt);
        item->SetPromoTyp(PromoType);
        item->SetPromotionNo(PromotionNo);
        item->SetPharmacyGroupId(PharmacyGroupId);
        item->PreisTyp(pricetype);
        item->SetPreisTypSaved(pricetype);
        item->InitOrderItem_Core(ArtikelNr, Menge, MengeNatra, 0L, pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked, bPOST_DEFAULT);
        item = AddNewItem(item);         // append it to the list of items
                                         // it create itself
        if ( item )
        {
            pospromo = item->GetOrderPosPromo(PromotionNo);
            if ( pospromo == NULL )
            {
                item->WriteOrderPosPromo( PharmacyGroupId, 0L, 0L, 0.0, IDFNr_, PromotionNo);
            }
        }
        calcSplittBookItem(item);
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create new order with rebate and promotion type for a stocked product     */
/*  using the product                                                         */
/*  number.                                                                   */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_11
(
    long       ArtikelNr,               // must read ArtBase via this number
    long       Menge,
    long       MengeNatra,
    double     Barrabatt,
    short      PromoType,
    short      PromotionNo,
    nString&   PharmacyGroupId,
    long       DiscountGrpNo,
    long       BaseQty,
    double     BaseValue,
    long       CustomerNo,
    PriceTypeEnum  pricetype
)
{
    pxOrderItem *item = NULL;
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    if ( PromoType == 2 )               // Promotion DiscountArticle
    {
        item =  NewOrderItem_02(ArtikelNr, 0L, Menge, 0L,
                                PromoType, PromotionNo, pricetype,
                                pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked,
                                bPOST_RANGEARTICLE);
        if (item )
        {
            item->WriteOrderPosPromo(PharmacyGroupId, DiscountGrpNo, BaseQty, BaseValue, CustomerNo, PromotionNo);
        }
        return item;
    }

    item = NewItem(); // construct new item object, then let
    if (item)
    {
        item->SetDiscountValPctPromo(Barrabatt);
        item->SetPromoTyp(PromoType);
        item->SetPromotionNo(PromotionNo);
        item->SetPharmacyGroupId(PharmacyGroupId);
        item->PreisTyp(pricetype);
        item->SetPreisTypSaved(pricetype);
        item->InitOrderItem_Core(ArtikelNr, Menge, MengeNatra, 0L, pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked, bPOST_DEFAULT);
        item = AddNewItem(item);         // append it to the list of items
        // take care of a well constructed item object, because
        // AddNewItem not always returns a poitive adress
        if ( item )
        {
            item->WriteOrderPosPromo(PharmacyGroupId, DiscountGrpNo, BaseQty, BaseValue, CustomerNo, PromotionNo);
        }
                                         // it create itself
        calcSplittBookItem(item);
    }
    return item;
}

pxOrderItem* pxOrder::NewOrderItem_15_DefaultWithAutoItemOCP(double freightCost)
{
    char comment[50];
    snprintf(comment, sizeof(comment), "Frais de port: %0.2f", freightCost);
    pxOrderItem* item = NULL;
    tDISPOITEM dispoItem;
    dispoItem.Bezeichnung = "Frais de port";
    dispoItem.MengeBestellt = 1;
    dispoItem.PreisEKGrosso = freightCost / 2.0; // dummy
    dispoItem.PreisEKApo = freightCost;
    dispoItem.NetPrice = freightCost;
    dispoItem.Rabattfaehig = false;
    dispoItem.MWSTSchluessel = FULLTAXFR;
    dispoItem.TaxPflichtig = true;
    dispoItem.Service_No = 0;
    dispoItem.Bemerkungen = nString(comment);

    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
    	// use the dispo item as baseline
        item->InitOrderItem_15(dispoItem, pxOrderItem::BookingTypeDefault, false);

    	// the dispo item needs to be adapted to the france specific characteristics
        item->ItemFlags().ClearBit(bTextDategAlpha); // important to remove the dispo flag to prevent wrong HOST
        item->SetPreisEKApo(nMoney(freightCost));
        item->SetPreisEKApoFree(nMoney(freightCost));
        item->SetPreisFakturFixed(nMoney(freightCost));
        item->SetBusinessTypeNo(4);
        item->Bemerkungen_ = nString(comment);
        item = AddNewItem(item);         // append it to the list of items
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create new order item for a product that is not stocked and must be       */
/*  ordered from any supplier.                                                */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_15
(
    tDISPOITEM& DispoItem,
    pxOrderItem::BookingType btype,
    bool addSubSequent
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->InitOrderItem_15(DispoItem, btype, addSubSequent);
        item = AddNewItem(item);         // append it to the list of items
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Creation of a text item.                                                  */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderTextItem
(
    const nString& Bemerkung,         // the text string
    const long    MengeBestellt       // may be 0
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->NewOrderTextItem(Bemerkung, MengeBestellt);
        item = AddNewItem(item);         // append it to the list of items
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item for a stocked product using string input.         */
/*  Mainly used when invoked via the order entry message interface.           */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItemRemarks
(
    const long ProductId,        // article identification
    const long QuanOrdered       // quantity ordered
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->NewOrderItemRemarks(ProductId, QuanOrdered);
        item = AddNewItem(item);         // append it to the list of items
        calcSplittBookItem(item);
        BookArtComPackMembers(item);     // book Steller members
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item for a stocked product using string input.         */
/*  Mainly used when invoked via the order entry message interface.           */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItemInfo
(
    const long    ProductId,        // article identification
    const long    QuanOrdered       // quantity ordered
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->NewOrderItemInfo(ProductId, QuanOrdered);
        item = AddNewItem(item);         // append it to the list of items
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item for a stocked product using string input.         */
/*  Mainly used when invoked DCT, XML                                         */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_12
(
    const long              ArticleNo,          // (internal) article identification (articleno)
    const long              QuanOrdered,        // quantity ordered
    const basar::VarString& XMLOrderreference,
    const basar::VarString& XMLLinereference,   // line reference number XML(BG)
    const bool              RemAuxDel,          // Auxdelivery
    const bool              RemRestDel,         // Restdelivery
    const bool              RemDispo,           // Dispo
    const bool              RemPartDel,         // Subset
    const PriceTypeEnum     RemPriceType,       // PriceType   allowed 0,1,2...
    const basar::VarString& Batch,
    const bool              IsFixBatch
)
{
    pxItemAttributes *attributes = new pxItemAttributes(RemAuxDel, RemRestDel, RemDispo, RemPartDel);

/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let
    if (item)
    {
//        item->SetXMLLinereference(XMLLinereference.c_str());
        item->SetXMLLinereference(XMLOrderreference.c_str()); // BG only??? store LINE reference in memory for GetProforma()
        item->setXMLReferences(XMLOrderreference, XMLLinereference);
        item->PreisTyp(RemPriceType);
        item->SetPreisTypSaved(RemPriceType);
        item->InitOrderItem_12(ArticleNo, QuanOrdered, attributes, 0, Batch, IsFixBatch);
        item = addItemAndProcess(item);
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item for a stocked product using string input.         */
/*  Mainly used when invoked DCT, XML                                         */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_13
(
    const long       ArticleNo,        // article identification
    const long       QuanOrdered,      // quantity ordered
    const basar::VarString&   XMLOrderreference,
    const basar::VarString&   XMLLinereference, // line reference number XML(BG)
    const bool       RemAuxDel,        // Auxdelivery
    const bool       RemRestDel,       // Restdelivery
    const bool       RemDispo,         // Dispo
    const bool       RemPartDel,       // Subset
    const PriceTypeEnum RemPriceType,     // PriceType   allowed 0,1,2...
    const nMoney&    PreisEKApo,
    const nMoney&    PreisEKApoFree,
    const double     DiscountValPctMan,
    const long       QtyRebateInKind,   // Natramenge
    const basar::VarString&  Batch,
    const bool       IsFixBatch
)
{
    pxItemAttributes *attributes = new pxItemAttributes(RemAuxDel, RemRestDel, RemDispo, RemPartDel);

/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let
    if (item)
    {
//        item->SetXMLLinereference(XMLLinereference.c_str());
        item->SetXMLLinereference(XMLOrderreference.c_str()); // BG only??? store LINE reference in memory for GetProforma()
        item->setXMLReferences(XMLOrderreference, XMLLinereference);
        item->PreisTyp(RemPriceType);
        item->SetPreisTypSaved(RemPriceType);
        item->SetPreisEKApo(PreisEKApo);
        item->SetPreisEKApoFree(PreisEKApoFree);
        item->SetDiscountValPctMan(DiscountValPctMan);
        item->SetMengeBestelltNatra(QtyRebateInKind);
        item->InitOrderItem_12(ArticleNo, QuanOrdered, attributes,QtyRebateInKind, Batch, IsFixBatch);
        item = addItemAndProcess(item);
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item for a stocked product using delivery position     */
/*  record.                                                                   */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItem_16
(
    pxVerbund::subsequentDelivery::pxDeliveryPos*    delpos,           // delivery position record
    pxOrderItem::BookingType btype      // btype
)
{
    nDate now;

/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    nString  Remarks( delpos->ConvertPosTyp());

    pxOrderItem* item = NewItem(); // construct new item object, then let
    if (item)
    {                                     // it create itself
        if ( delpos->IsRestDeliveryItem() || delpos->IsReserveItem() )
        {
            item->SetBookRestDelivery();
            item->SetPreisTyp( delpos->PreisTyp() );
        }

        if ( delpos->MengeNatra() > 0 )
        {
            item->InitOrderItem_Core(delpos->ArtikelNr(), delpos->Menge(),delpos->MengeNatra(),
                                     -1, pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked,
                                     bPOST_DEFAULT);
        }
        else
        {
            item->InitOrderItem_16(delpos->ArtikelNr(), delpos->Menge(), Remarks,btype);
        }
        if (!delpos->Bemerkungen().IsEmpty())
        {
             item->Bemerkungen(delpos->Bemerkungen());
        }
        if (false == Session()->isGermany())
        {
            item->SetPreisEKApoNetto(delpos->PreisEKApoNetto());
            if (delpos->PreisEKApo() > pxConstants::mZero)
            {
                item->SetPreisEKApo(delpos->PreisEKApo());
            }
            if (delpos->PreisAGP() > pxConstants::mZero)
            {
                item->SetPreisAGP(delpos->PreisAGP());
            }
        }
        if ( delpos->DatumValuta() != pxConstants::NullDate && ( !Session()->isBulgaria())  )
        {
            nDate vdate = delpos->DatumValuta();
            vdate += delpos->GetValutaDays();
            ValDate(vdate);
            SetNotUpdateValdate();
        }
        item->SetMengeBestelltOrg(delpos->MengeBestellt() );

        if ( delpos->IsPosArtDCT() )
        {
            item->SetGeraetTyp((pxDeviceType)pxDVC_DCT_SERIAL);
        }
        else
        if ( delpos->IsPosArtTelefone() )
        {
            item->SetGeraetTyp((pxDeviceType)pxDVC_VIDEO_WORKSTATION);
        }

        item->SetArticleCodeValues(delpos->CodeType(), delpos->ArticleCode() );

        item = addItemAndProcess(item);    // append it to the list of items
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create a new item to query or simulate the ordering process. The item is  */
/*  neither appended to the item list of the current order nor is it written  */
/*  into the data base. Note that                                             */
/*  Mainly used when invoked via the order entry message interface.           */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: ItemQuery
(
    const long    ProductId,        // article identification
    const long    QuanOrdered       // quantity ordered
)
{
    ClearError();                       // Order error object cleanup
    if (ItemQuery_)                     // query item exists
    {
        delete ItemQuery_;              // must delete old object
        ItemQuery_ = NULL;
    }

    ItemQuery_ = new pxOrderItem(*this, 0); // construct a temp item
    if (ItemQuery_)
    {
        nDBBeginTransaction(cDBTransSet); // Begin data base transaction
        if ( Session()->isBulgaria() )
        {
            SetBGInfoOrder();
        }
        ItemQuery_->NewOrderItemQuery(ProductId, QuanOrdered);
        Error() = (ItemQuery_->Error());     // copy error object instance
        nDBRollBack();                       // and rollback updates
        if ( ! ItemQuery_->IsGoodState() )   // then an error occurred
        {
            delete ItemQuery_;            // must delete current object
            ItemQuery_ = NULL;            // signal error
            return ItemQuery_;
        }

        // auxdelivery possible
        if ( ItemQuery_->MengeMoeglich() > 0 && Customer()->Flags().IsVerbundGanz() )
        {
            ItemQuery_->SetAuxPostPossible();
        }

        if ( QuanOrdered > 0 && Customer()->IsInfoLevelHigh() )
        {
            ItemQuery_->CompleteItemQueryResult();    // what happened
        }
        ItemQuery_->CalcAvp();
    }
    nString aCode = ItemQuery_->ArticleCode();
    aCode.Strip();                  // delete blanks
    if ( aCode.IsEmpty() )
    {
        pxArticleCodes* ArtCode = ItemQuery_->GetArticleCode(ItemQuery_->ArtikelNr());
        if ( ArtCode )
        {
            ItemQuery_->SetArticleCodeValues(ArtCode->CodeType(), ArtCode->ArticleCode());
            delete ArtCode;
        }
    }

    return ItemQuery_;
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item using an existing item Object                     */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: CopyOrderItem
(
    pxOrderItem* splittitem,
    pxOrderItem::BookingType btype,      // btype
    SplittTypeEnum s
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (setErrorOnMissingLock())
    {
        return NULL;
    }

    pxOrderItem* item = NewItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->CopyOrderItem(splittitem, btype, s);
        item = AddNewItem(item);         // append it to the list of items
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item using an existing item Object                     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: BookDiscountArticle
(
    pxOrderItem* item
)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerOrder(), "pxOrder::BookDiscountArticle()" );

    pxOrderItem *newitem  = NULL;
    Session()->Device(); // Init Device
    pxArtComPackList        *acpl = NULL;
    pxArtComPack        *acpentry = NULL;
    pxCPValidityPeriodList *cpvpl = NULL;
    pxCPValidityPeriod  *cpventry = NULL;
    pxArtBase* discountArtBase    = NULL;
    bool       bProblemState      = false;
    pxOrderPosPromo*  pospromo    = NULL;
    double DiscountValuePctMan = 0.0;

    if ( item == NULL )
    {
        BLOG_TRACE( libcsc::LoggerPool::getLoggerOrder(), "item == NULL" );
        return ErrorState();
    }

    if ( item->DiscountArticleNo() == 0 )
    {
        BLOG_TRACE( libcsc::LoggerPool::getLoggerOrder(), "item->DiscountArticleNo() == 0" );
        return ErrorState();
    }

    // INC-042823
    DiscountValuePctMan = item->GetDiscountValPctMan();
    if ( DiscountValuePctMan > 0.0 )
    {
        BLOG_TRACE( libcsc::LoggerPool::getLoggerOrder(), "DiscountValuePctMan > 0.0" );
        return ErrorState();
    }
    // INC-042823

    if( libcsc::LoggerPool::getLoggerOrder().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
    {
        std::stringstream ss;
        ss << "Rebate-in-kind article: articleNo=<" << item->DiscountArticleNo() << ">";
        libcsc::LoggerPool::getLoggerOrder().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
    }

    // check DiscountArticle_, maybe it is a Steller Article. In that case
    // we must check the type be select the cpvalidityperiod entry
    cpvpl = new pxCPValidityPeriodList(Session());
    cpvpl->Select(item->DiscountArticleNo());
    cpvpl->ReduceToValidEntries();
    if (cpvpl->Entries() == 0 )
    {
        delete cpvpl;
    }
    else
    {
        cpventry = (pxCPValidityPeriod*)(cpvpl->At(0)); // entry to be checked
    }

    if ( cpventry )
    {
        if ( cpventry->IsReplaceDiscArticle() )          // = 4 Rebate from the artcompack list
        {
            // now get the members belonging to this Pseudo article
            acpl = new pxArtComPackList(Session());
            acpl->Select( item->DiscountArticleNo());
            if (acpl->Entries() == 0 )                   // nothing found
            {
                delete acpl;
                acpl = NULL;
                return ErrorState();
            }
        }
    }
    // now book the members belonging to  item->DiscountArticleNo()
    // till now it's a bulgarian speciality
    if ( acpl )
    {
        pxArtComPackListIter iter(*acpl);
        while ( (acpentry = (pxArtComPack*) ++iter) != NULL )
        {
            bProblemState = false;
            if ( !(Session()->Device()->IsVideo() ) )
            {
                discountArtBase = pxArtBase :: CreateArticle(item->Session(), acpentry->ArticleNoElement(), FilialNr());
                if ( discountArtBase->IsGoodState() )
                {
                    if ( Session()->getStockBooking()->GetAvailableQtyInStock(*discountArtBase) < acpentry->Quantity() )   // does not fit
                    {
                        SetNoRebateQty();
                        delete discountArtBase;
                        bProblemState = true;
                    }
                }
                else
                {
                    delete discountArtBase;
                    continue;
                }
            }
            long QtyToPostNatraRangeArticle = ( ( bProblemState == true) ? (long)0 : (long)acpentry->Quantity());
            newitem = NewOrderItem_03_NatraWithRangeArticle(acpentry->ArticleNoElement(), QtyToPostNatraRangeArticle, item->PreisTyp());
            if ( newitem == NULL )
            {
                if ( ErrorNumber() != CMSG_ART_QLACK_DISC_ARTICLE )
                {
                    ClearError();                           // to prevent Error during booking
                }
            }
            else
            if ( newitem->IsGoodState() )
            {
                if ( bProblemState )
                {
                    newitem->SetProblemState((short)pxOrderItem::PDiscountNoQty );
                }
                if ( item->PromotionNo() > 0 && !bProblemState )
                {
                    pospromo = item->GetOrderPosPromo(item->PromotionNo());
                    if ( pospromo )
                    {
                        newitem->WriteOrderPosPromo(pospromo->PharmacyGroupId(), pospromo->DiscountGrpNo(), pospromo->BaseQty(), pospromo->BaseValue(),
                                                    pospromo->CustomerNo(), static_cast<short>(pospromo->PromotionNo()) , pospromo->InternalDiscount());
                    }
                }
                newitem->SetLinkPosNr(item->PosNr());   // do the cross link
                newitem->SetSperreRabattManuell();      // mark position
                newitem->SetXMLLinereference(item->XMLLinereference());
            }
        }
        delete acpl;
        delete cpvpl;
        return ErrorState();
    }

    // first check quantity in Stock. If QInStock of the discount article does not fit the  item->MengeNatraDiscountArticle,
    // we mark this item and  also  this order. This order will be deferred, so it can be manupulated by the KSC employers
    if ( !(Session()->Device()->IsVideo()) )
    {
        discountArtBase = pxArtBase :: CreateArticle(item->Session(), item->DiscountArticleNo(), FilialNr());
        if ( discountArtBase->IsGoodState() )
        {
            if ( Session()->getStockBooking()->GetAvailableQtyInStock(*discountArtBase) < item->MengeNatraDiscountArticle() )   // does not fit
            {
                SetNoRebateQty();
                item->SetProblemState((short)pxOrderItem::PDiscountNoQty);
                bProblemState = true;
             }
        }
        else
        {
            SetNoRebateQty();
            item->SetProblemState((short)pxOrderItem::PDiscountArticleNotAV);
            delete discountArtBase;
            EraseOrderpositionDiscountEntry(item);
            return ErrorState();
        }
        delete discountArtBase;
    }

    long QtyToPostNatraRangeArticle = ( ( bProblemState == true) ? (long)0 : (long)item->MengeNatraDiscountArticle());
    newitem = NewOrderItem_03_NatraWithRangeArticle(item->DiscountArticleNo(), QtyToPostNatraRangeArticle, item->PreisTyp());
    if ( newitem == NULL )
    {
        EraseOrderpositionDiscountEntry(item);

        if (ErrorNumber() != CMSG_ART_QLACK_DISC_ARTICLE)
        {
            ClearError();                           // to prevent Error during booking
        }
        else
        {
            item->UndoPromoQuota();
            item->UndoOrderPosPromo();
        }
    }
    else
    {
        if ( newitem->IsGoodState() )
        {
            if( libcsc::LoggerPool::getLoggerOrder().isEnabledFor( log4cplus::TRACE_LOG_LEVEL ) )
            {
                std::stringstream ss;
                ss << "Rebate-in-kind article: positionNo=<" << newitem->PosNr() << ">";
                libcsc::LoggerPool::getLoggerOrder().forcedLog( log4cplus::TRACE_LOG_LEVEL, ss.str().c_str(), __FILE__, __LINE__ );
            }

            if ( bProblemState )
            {
                item->UndoPromoQuota();
                item->UndoOrderPosPromo();
            }
            newitem->SetLinkPosNr(item->PosNr());      // do the cross link
            newitem->SetSperreRabattManuell();         // mark position
            newitem->SetXMLLinereference(item->XMLLinereference());
            item->SetLinkPosNr(newitem->PosNr());      // do the cross link
            if ( item->PromotionNo() > 0 && !bProblemState )
            {
                pospromo = item->GetOrderPosPromo(item->PromotionNo());
                if ( pospromo )
                {
                    newitem->WriteOrderPosPromo(pospromo->PharmacyGroupId(), pospromo->DiscountGrpNo(), pospromo->BaseQty(), pospromo->BaseValue(),
                                                pospromo->CustomerNo(), static_cast<short>(pospromo->PromotionNo()) , pospromo->InternalDiscount());
                }
            }
        }
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  BookArtComPackMembers:Create a new order item using an existing item      */
/*  object.item must be an artcompackhead article(Steller pseudo article      */
/*  For each member that belongs to this pseudo article, a new order item     */
/*  will be booked                                                            */
/*----------------------------------------------------------------------------*/
int
pxOrder :: BookArtComPackMembers
(
    pxOrderItem* item
)
{
    pxOrderItem          *newitem = NULL;
    pxArtComPackList        *acpl = NULL;
    pxCPValidityPeriodList *cpvpl = NULL;
    pxArtComPack        *acpentry = NULL;
    long            ArticleNoPack = 0;
    long            MengeBestellt = 0;

    if (   (item == NULL)
        || !item->IsGoodState()
        || !item->IsStellerKopf() )             // just if Steller Pseudo Article
        return ErrorState();

    if (Session()->isGermany())
    {
        if (item->MengeBestaetigt() == 0)
        {
            return ErrorState();
        }
    }

    // now get the members belonging to this Pseudo article
    acpl = new pxArtComPackList(Session());
    acpl->Select( item->ArtikelNr() );
    if (acpl->Entries() == 0 )                   // nothing found
    {
        delete acpl;
        return ErrorState();
    }
    // now check the quiltiness of acpl
    cpvpl = new pxCPValidityPeriodList(Session());
    cpvpl->Select(item->ArtikelNr());
    cpvpl->ReduceToValidEntries();
    if (cpvpl->Entries() == 0 )
    {
        delete acpl;
        delete cpvpl;
        return ErrorState();
    }

    if (Session()->isGermany())
    {
       MengeBestellt = item->MengeBestaetigt();
    }
    else
    {
        MengeBestellt = item->MengeBestellt();
    }

    // save steller LastStock & RestQuota
    long stellerLastStock = LastStock();
    long stellerRestQuota = RestQuota();

    ArticleNoPack = item->ArtikelNr();           // pseudo articleno
    pxArtComPackListIter iter(*acpl);
    while ( (acpentry = (pxArtComPack*) ++iter) != NULL )
    {
        newitem = NewOrderItem_03(acpentry->ArticleNoElement(), ((long)acpentry->Quantity() * MengeBestellt), 0L, 0L,
                                  FREESALE_PRICE,
                                  pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked,
                                  bPOST_DEFAULT);

        if ( newitem == NULL )
        {
            ClearError();              // to prevent Error during booking
        }
        else
        if ( newitem->IsGoodState() )
        {
            newitem->SetArticleNoPack(ArticleNoPack); // link to pseudoarticleno
            newitem->SetStellerMitglied();            // mark position as a member
            newitem->SetSperreRabattManuell();        // mark position
            newitem->SetXMLLinereference(item->XMLLinereference());
        }
    }

    // restore steller LastStock & RestQuota
    LastStock(stellerLastStock);
    RestQuota(stellerRestQuota);
    
    delete acpl;
    delete cpvpl;
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  BookTenderProgress:Create a new tenderprogress entry from an existing     */
/*  item object                                                               */
/*  OrderType must be TenderOrder and we must be in RS or BG                  */
/*----------------------------------------------------------------------------*/
int
pxOrder :: BookTenderProgress
(
    pxOrderItem* item
)
{
    pxCommType      *ct = Session()->CommTypeList(Customer()->Vertriebszentrum())->Find(KoArt_,Customer()->Vertriebszentrum());
    pxStockTrans    *st = Session()->StockTransList(Customer()->Vertriebszentrum())->Find(BuchArt_,Customer()->Vertriebszentrum() );
    basar::Int32 tenderNo = TenderNo_;

    if( !item->IsGoodState() || (item == NULL) )
    {
        return ErrorState();
    }
    if( Session()->isSwitzerland() )
    {
        // get tender no from remarks
        pxGenericOrderRemarkList remarklist( Session() );
        remarklist.SelectOrderRemarksByOrderLineAndType( KdAuftragNr(), item->PosNr(), eTenderNo );
        if( remarklist.Entries() > 0 )
        {
            pxGenericOrderRemarkListIter iter = ::pxGenericOrderRemarkListIter( remarklist );
            pxGenericOrderRemark* remark;

            if( NULL != (remark = (pxGenericOrderRemark*)++iter) )
            {
                basar::VarString strRem = basar::VarString( remark->RemarkText() );
                if ( strRem.isDigit() )
                {
                    tenderNo = atoi( strRem.c_str() );
                }
            }
        }

        if( 0 == tenderNo )
        {
            return ErrorState();
        }
    }
    else if (   (!(OrderType().IsTenderOrder()) && !(OrderType().IsTenderInvoice()))
        || ct->IsNoShipment()
        || st->IsNoTransaction()
        || (item == NULL)
        || !item->IsGoodState()
        || (TenderHead() == NULL)
        || (item->MengeGeliefert() == 0) )
        return ErrorState();
    nDate tmp = (nDate)DateTimeCreated();
    pxTenderProgress * TPGentry = new pxTenderProgress( Session(), tenderNo, item->ArtikelNr(), KdAuftragNr_, tmp, item->PosNr() );

    const libcsc::discount::TenderDiscountPtr tenderDiscount( item->getTenderDiscount() );
    if( Session()->isSwitzerland() )
    {
        if(    tenderDiscount
            && tenderDiscount->getAvailableQuantity() < item->MengeBestaetigt() )
        {
            TPGentry->SetDeliveryQty( tenderDiscount->getAvailableQuantity() );
        }
        else
        {
            TPGentry->SetDeliveryQty( item->MengeBestaetigt() );
        }
        TPGentry->SetDiscountPct( tenderDiscount->getDiscountPercent().get().toFloat64() );
    }
    else
    {
        TPGentry->SetDeliveryQty( item->MengeGeliefert() );
    }

    TPGentry->SetChargedPrice(item->TenderChargedPrice());
    TPGentry->SetOrderTime( item->UhrZeitBestNachUpd() / 10 );
    TPGentry->SetCustomerNo( IDFNr() );
    TPGentry->SetKdAuftragArt( KdAuftragArt()() );
    TPGentry->SetBranchNo( FilialNr() );
    TPGentry->SetChangeDate( basar::cmnutil::Date::getCurrent().getDate() );

    nMoney priceEK = item->PreisEKApo();
    if( nMoney( 0 ) == priceEK )
    {
        priceEK = item->PreisEKGrosso();
    }
    TPGentry->SetGEP( priceEK );

    TPGentry->Put();
    Error() = TPGentry->Error();
    delete TPGentry;

    if( Session()->isSwitzerland() )
    {
        Session()->getTenderRepository()->switchTenderState( tenderNo );
    }

    return ErrorState();
}

/*----------------------------------------------------------------------------*/
/*  Construct new order item. Performs some sanity checks, then constructs    */
/*  a new order item object and begins a data base transaction.               */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewItem
(
)
{
    ClearError();                       // Order error object cleanup
    if (ItemQuery_)                     // query item exists
    {
        delete ItemQuery_;              // must delete old object
        ItemQuery_ = NULL;
    }

    pxOrderItem *item  = NULL;
    if ( IsEntryInProgress() )          // ensure order is open
    {                                   // then construct item object instance
        item  = new pxOrderItem(*this, static_cast<long>(ItemList_->Entries() + 1));
        nDBBeginTransaction(cDBTransSet);// Begin data base transaction
    }
    else
        ExternalError(CMsgStream(), CMSG_ITM_INSERT_DENIED, KdAuftragNr_);

    return item;
}

/*----------------------------------------------------------------------------*/
/*  Add the new order item object to the item list. Returns a pointer to the  */
/*  new order item or NULL in of any error.                                   */
/*----------------------------------------------------------------------------*/
pxOrderItem* pxOrder::AddNewItem( pxOrderItem *item )
{
    // TourManager:: Tourermittlung Position!

    pxDevice* device = Session()->Device();
    pxOrderItem* retval = item;

    if ( item->IsGoodState() )          // ensure object is well constructed
    {
        nString aCode = item->ArticleCode();
        aCode.Strip();                  // delete blanks
        if (aCode.IsEmpty())
        {
            pxArticleCodes* ArtCode = item->GetArticleCode(item->ArtikelNr());
            if (ArtCode != NULL)
            {
                item->SetArticleCodeValues(ArtCode->CodeType(), ArtCode->ArticleCode());
                delete ArtCode;
            }
        }
        item->SetSubGeraetTyp(Session()->SubDeviceType());
        item->Put();                    // then write it into the data base
    }

    if ( item->IsGoodState() )          // then item has been written
    {
        pxOrderPosEvent posevent(*item, pxOrderPosEvent::EntryInProgress);  // construct order pos event
        posevent.Put();                  // write it into the data base
        ItemList_->Append(item);         // put it on the list
        if ( !device->IsVideo() )        // then: DCT or file
        {
            pxArtDispo* artDispo = item->ArtDispo();
            if (!(artDispo != NULL && artDispo->Service_No() > 0))
            {
            ++AnzPosDafue_;              // count DCT items
            if ( item->IsDispoItem() )
            {
                ++AnzAlphaText_;     // it was a text item
                SetProblemClearance();
            }
            else if (   (   !(item->IsArtStateGood() && item->IsQStateGood())
                         && item->QState() != pxOrderItem :: QStateLimitCheck )
                     || item->IsAuxPosted() )
                ++AnzPosDafueFehler_;      // any DC error or condition
            }
        }
        if (item->IsNachliefern())
        {
            SetMitNachlieferung();
        }
        item->ItemUpdateDiscountList();
        ItemValues(item);                // calc item values
        item->CalcAvp();                 // calc selling price for pharmacies
        //item->DeleteAuxStoreLocList();

        if (Session()->isBulgaria())
        {
            if ( Customer()->CustomerGroupFlagsList()->isGroupBasePriceGEP())
            {
                const double discount = item->calculateNewDiscount();
                if(discount >= 0.0)
                    item->changeDiscountInDB(discount);
            }
            if ( OrderPosDiscountList_ != NULL )
            {
                delete OrderPosDiscountList_;
                OrderPosDiscountList_ = NULL;
            }
        }

        OrdTaxValues()->SetOrderValues(item); // calc item values
        AverageItemValue();              // and average order item value
        item->ItemUpdate();              // maybe values changed
        nDBCommit(cDBTransSet);
    }
    else
    {
        Error() = item->Error();         // copy error object instance
        retval = NULL;                   // signal error
        nDBRollBack();                   // and rollback updates
        delete item;                     // and delete current object
    }
    Session()->resetStockBooking();
    return retval;
}

bool pxOrder::setErrorOnMissingLock()
{
    if ( !IsPseudoLock() && !IsLocked() )                  // order still locked ??
    {
        ExternalError(CMsgStream(), CMSG_ORD_LOCK_DISAPPEARED, KdAuftragNr_);
        return true;
    }
    return false;
}

pxOrderItem* pxOrder::addItemAndProcess(pxOrderItem* item)
{
    item = AddNewItem(item);         // append it to the list of items
    if (item == NULL)
    {
        BLOG_TRACE(libcsc::LoggerPool::getLoggerOrder(), "pxOrder::addItemAndProcess : item == NULL");
    }
    else
    {
        calcSplittBookItem(item);
        BookArtComPackMembers(item);     // book Steller members
        BookTenderProgress(item);        // book TenderProgress entry
    }
    return item;
}

void pxOrder::calcSplittBookItem(pxOrderItem* item)
{
    CalcPromotionQuota(item);        // book TenderProgress entry
    SplittPartialIBTPosition(item);  // Splitt partial IBT position
    BookDiscountArticle(item);       // may be FreeArticle
}
