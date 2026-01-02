#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxartcompack.hpp"
#include "pxcpvalidityperiod.hpp"
#include "pxtenderprogress.hpp"
#include "types/messagecodeenum.inc"

extern bool pxGlobalNoDatabaseWrite;

/*----------------------------------------------------------------------------*/
/*  Create new order item for a stocked product using the product number.     */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: CalcOrderItem
(
    long       ArtikelNr,              // must read ArtBase via this number
    long       Menge,
    long       MengeNatra,
    long       MengeNachfrage,
    PriceTypeEnum    pricetype,
    pxOrderItem::BookingType btype,
    pxOrderItem::ItemType    PosTyp,    // product identification mode
    int         flags                   // internal posting flags
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if ( !IsPseudoLock() )
    {
        if ( !IsLocked() )                  // order still locked ??
        {
            ExternalError(CMsgStream(),CMSG_ORD_LOCK_DISAPPEARED, KdAuftragNr_);
            return NULL;
        }
    }

    pxOrderItem* item = NewCalcItem();
    if (item)            // construct new item object, then let
    {                                        // it create itself
        pxGlobalNoDatabaseWrite = true;
        item->SetProFormaBooking();          // mark this item for further use
        item->PreisTyp(pricetype);
        item->CalcOrderItem(ArtikelNr, Menge, MengeNatra, MengeNachfrage,
                            btype, PosTyp, flags);
        item = AddNewCalcItem(item);     // append it to the list of items
        pxGlobalNoDatabaseWrite = false;
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Construct new order item. Performs some sanity checks, then constructs    */
/*  a new order item object and begins a data base transaction.               */
/*  This is is just proforma. It's for the bulgarian application              */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewCalcItem
(
)
{
    ClearError();                       // Order error object cleanup

    pxOrderItem *item  = NULL;
    if ( IsEntryInProgress() )          // ensure order is open
    {                                   // then construct item object instance
        item  = new pxOrderItem(*this, static_cast<long>(ItemList_->Entries() + 1));
    }
    else
        ExternalError(CMsgStream(), CMSG_ITM_INSERT_DENIED, KdAuftragNr_);

    return item;
}

/*----------------------------------------------------------------------------*/
/*  Add the new order item object to the item list. Returns a pointer to the  */
/*  new order item or NULL in of any error. This is just proforma, item is not*/
/*  written to the database. It's for the bulgarien application               */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: AddNewCalcItem
(
    pxOrderItem *item
)
{
    // unused variable
    /* pxDevice *device = */ Session()->Device();
    pxOrderItem*   retval = item;

    if ( item->IsGoodState() )          // ensure object is well constructed
    {
        item->InvoiceValue();           // calc item invoice price
        item->CalcAvp();                // calc selling price for pharmacies
    }
    else
    {
        Error() = (item->Error());      // copy error object instance
        retval = NULL;                  // signal error
        delete item;                    // and delete current object
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Create new order item for a stocked product using the product number.     */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: ItemDiscountInfo
(
    long          ArtikelNr,               // must read ArtBase via this number
    PriceTypeEnum pricetype
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/

    if ( !IsPseudoLock() )
    {
        if ( !IsLocked() )                  // order still locked ??
        {
            ExternalError(CMsgStream(),CMSG_ORD_LOCK_DISAPPEARED, KdAuftragNr_);
            return NULL;
        }
    }

    pxOrderItem* item = NewDiscountInfoItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->PreisTyp(pricetype);
        item->SetProFormaBooking();          // mark this item for further use
        item->ItemDiscountInfo(ArtikelNr);
        item = AddNewDiscountInfoItem(item); // append it to the list of items ==> ERRATA: This method does NOT append the item (BB: 02.12.2021)
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Construct new order item. Performs some sanity checks, then constructs    */
/*  a new order item object and begins a data base transaction.               */
/*  This is is just proforma. It's for the bulgarian application              */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewDiscountInfoItem
(
)
{
    ClearError();                       // Order error object cleanup

    pxOrderItem *item  = NULL;
    item  = new pxOrderItem(*this, static_cast<long>(ItemList_->Entries() + 1));
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Add the new order item object to the item list. Returns a pointer to the  */
/*  new order item or NULL in of any error. This is just proforma, item is not*/
/*  written to the database. It's for the bulgarien application               */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: AddNewDiscountInfoItem
(
    pxOrderItem *item
)
{
    // unused variable
    /* pxDevice *device = */ Session()->Device();
    pxOrderItem*   retval = item;

    if ( !item->IsGoodState() )          // ensure object is well constructed
    {
        Error() = (item->Error());       // copy error object instance
        retval = NULL;                   // signal error
        delete item;                     // and delete current object
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Construct new order item. Performs some sanity checks, then constructs    */
/*  a new order item object and begins a data base transaction.               */
/*  This is is just proforma. It's for the bulgarian application              */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewProformaItem
(
)
{
    ClearError();                       // Order error object cleanup

    pxOrderItem *item  = NULL;
    item  = new pxOrderItem(*this, static_cast<long>(ItemListProforma()->Entries() + 1));
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Add the new order item object to the item list. Returns a pointer to the  */
/*  new order item or NULL in of any error. This is just proforma, item is not*/
/*  written to the database. It's for the bulgarien application               */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: AddNewProformaItem
(
    pxOrderItem *item
)
{
    Session()->Device();
    pxOrderItem*   retval = item;

    if ( item->IsGoodState() )          // ensure object is well constructed
    {
        ItemListProforma()->Append(item);         // put it on the list
    }
    else
    {
        Error() = (item->Error());       // copy error object instance
        retval = NULL;                   // signal error
        delete item;                     // and delete current object
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Create new order item for a stocked product using the product number.     */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderItemProforma
(
    long       ArtikelNr,              // must read ArtBase via this number
    long       Menge,
    long       MengeNatra,
    long       MengeNachfrage,
    PriceTypeEnum    pricetype,
    pxOrderItem::BookingType btype,
    pxOrderItem::ItemType    PosTyp,    // product identification mode
    int         flags                   // internal posting flags
)
{
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if ( !IsPseudoLock() )
    {
        if ( !IsLocked() )                  // order still locked ??
        {
            ExternalError(CMsgStream(),CMSG_ORD_LOCK_DISAPPEARED, KdAuftragNr_);
            return NULL;
        }
    }

    pxGlobalNoDatabaseWrite = true; // do not
    pxOrderItem* item = NewProformaItem(); // construct new item object, then let it create itself
    if (item)
    {
        item->PreisTyp(pricetype);
        item->InitOrderItem_Core(ArtikelNr, Menge, MengeNatra, MengeNachfrage, btype, PosTyp, flags);
        item = AddNewProformaItem(item); // append it to the list of items
    }
    if ( !IsPseudoLock() )
    {
        pxGlobalNoDatabaseWrite = false; // do not
    }
    return item;
}

pxOrderItem* pxOrder::NewOrderItemProforma_NatraWithRangeArticle(long ArtikelNr, long MengeNatra, PriceTypeEnum pricetype)
{
    return NewOrderItemProforma(
        ArtikelNr, 0L, MengeNatra, 0L, pricetype, pxOrderItem::BookingTypeDefault, pxOrderItem::TypeProductStocked, bPOST_RANGEARTICLE);
}
