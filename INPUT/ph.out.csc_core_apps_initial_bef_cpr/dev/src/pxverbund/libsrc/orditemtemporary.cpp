#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxartcompack.hpp"
#include "pxcpvalidityperiod.hpp"
#include "pxtenderprogress.hpp"
#include "types/messagecodeenum.inc"

extern bool pxGlobalNoDatabaseWrite;

/*----------------------------------------------------------------------------*/
/*  Construct new order item. Performs some sanity checks, then constructs    */
/*  a new order item object and begins a data base transaction.               */
/*  This is is just proforma. It's for the bulgarian application              */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewTemporaryItem
(
)
{
    ClearError();                       // Order error object cleanup

    pxOrderItem *item  = NULL;
    if (! ItemListTemporary_ )                   // no item list constructed
    {
        item = new pxOrderItem(*this, static_cast<long>(ItemList()->Entries() + 1));
    }
    else
    {
       item  = new pxOrderItem(*this, static_cast<long>(ItemListTemporary()->Entries() + 1));
    }
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Add the new order item object to the item list. Returns a pointer to the  */
/*  new order item or NULL in of any error. This is just proforma, item is not*/
/*  written to the database. It's for the bulgarien application               */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: AddNewTemporaryItem
(
    pxOrderItem *item
)

{
    // unused variable
    /* pxDevice *device = */ Session()->Device();
    pxOrderItem*   retval = item;

    if ( item->IsGoodState() )          // ensure object is well constructed
    {
       ItemListTemporary()->Append(item);         // put it on the list
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
/*  Create new order with rebate and promotion type for a stocked product     */
/*  using the product number.                                                 */
/*  This Item will be added to the ItemListTemporary and it is not written    */
/*  to the database                                                           */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrder :: NewOrderTemporaryItem
(
    long       ArtikelNr,              // must read ArtBase via this number
    long       Menge,
    long       MengeNatra,
    double    Barrabatt,
    short      PromoType,
    short      PromotionNo,
    nString&    PharmacyGroupId,
    PriceTypeEnum  pricetype,
    pxOrderItem::BookingType btype,
    pxOrderItem::ItemType  PosTyp,      // product identification mode
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

    pxGlobalNoDatabaseWrite = true;         // do not  write to database
    pxOrderItem* item = NewTemporaryItem(); // construct new item object, then let
    if (item)
    {
       item->SetDiscountValPctPromo(Barrabatt);
       item->SetPromoTyp(PromoType);
       item->SetPromotionNo(PromotionNo);
       item->SetPharmacyGroupId(PharmacyGroupId);
       item->PreisTyp(pricetype);
       item->InitOrderItem_Core(ArtikelNr, Menge, MengeNatra, 0L,
                          btype, PosTyp, flags);
       item = AddNewTemporaryItem(item);         // append it to the list of items
    }
    if ( !IsPseudoLock() )
    {
       pxGlobalNoDatabaseWrite = false;           // clear do not write to the datatbase
    }
    return item;
}
