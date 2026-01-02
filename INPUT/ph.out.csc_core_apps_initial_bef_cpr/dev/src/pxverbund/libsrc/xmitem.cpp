/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Class pxOrderTransmit:
Overloaded order item entry methods.
All methods return a pointer to the new item object instance if entering the
item was successful, otherwise NULL is returned.

REVISION HISTORY

19 Jan 1995 V1.00 REV 00 written by Wolfgang Hoppe.
*/
#include "pxxmit.hpp"
#include "pxorder.hpp"

/*----------------------------------------------------------------------------*/
/*  Create a new order item for a product using the product identification    */
/*  number.                                                                   */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrderTransmit :: NewOrderItem_12
(
    const long     ArticleNo,
    const long     QuanOrdered,
    const basar::VarString& XMLOrderReference,
	const basar::VarString& XMLLinereference,
    const bool     RemAuxDel,        // Auxdelivery
    const bool     RemRestDel,       // Restdelivery
    const bool     RemDispo,         // Dispo
    const bool     RemPartDel,       // Subset
    const PriceTypeEnum RemPriceType,      // PriceType   allowed 0,1,2...
	const basar::VarString& Batch,
	const bool	   IsFixBatch
)
{
    if ( Order_ )                       // ensure order is open
       Item_ = Order_->NewOrderItem_12(ArticleNo, QuanOrdered, XMLOrderReference, XMLLinereference, RemAuxDel,
                                    RemRestDel, RemDispo, RemPartDel,RemPriceType, Batch, IsFixBatch);
    if ( Item_ )
    {
       Error() = Item_->Error();
    }
    return ItemPtr();                   // check if success, then return *item

}

/*----------------------------------------------------------------------------*/
/*  Create a new order item for a product using the product identification    */
/*  number.                                                                   */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrderTransmit :: NewOrderItem_13
(
    const long     ArticleNo,
    const long     QuanOrdered,
    const basar::VarString& XMLOrderReference,
	const basar::VarString& XMLLinereference,
    const bool     RemAuxDel,        // Auxdelivery
    const bool     RemRestDel,       // Restdelivery
    const bool     RemDispo,         // Dispo
    const bool     RemPartDel,       // Subset
    const PriceTypeEnum RemPriceType,     // PriceType   allowed 0,1,2...
    const nMoney&  PreisEKApo,
    const nMoney&  PreisEKApoFree,
    const double   DiscountValPctMan,
    const long     QtyRebateInKind,	// Natramenge
	const basar::VarString& Batch,
	const bool	   IsFixBatch
)
{
    if ( Order_ )                       // ensure order is open
       Item_ = Order_->NewOrderItem_13(ArticleNo, QuanOrdered,XMLOrderReference,XMLLinereference,RemAuxDel,
                                    RemRestDel, RemDispo, RemPartDel,RemPriceType,
                                    PreisEKApo, PreisEKApoFree, DiscountValPctMan, QtyRebateInKind, Batch, IsFixBatch);
    if ( Item_ )
    {
       Error() = Item_->Error();
    }
    return ItemPtr();                   // check if success, then return *item

}

/*----------------------------------------------------------------------------*/
/*  Create a temp order item for a product using the product identification   */
/*  number. This method maybe used for an inquiry of terms and conditions.    */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrderTransmit :: ItemQuery
(
    const long ProductId,
    const long QuanOrdered
)
{
    pxOrderItem *item;
    if ( Order_ )                       // ensure order is open
       Item_ = Order_->ItemQuery(ProductId, QuanOrdered);
    item = ItemPtr();                   // check success
    Item_ = NULL;                       // there is no order item current
    return item;
}

/*----------------------------------------------------------------------------*/
/*  Create a new order item for a product using the product identification    */
/*  number.                                                                   */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrderTransmit :: NewOrderItemInfo
(
    const long ProductId,
    const long QuanOrdered
)
{
    if ( Order_ )                       // ensure order is open
       Item_ = Order_->NewOrderItemInfo(ProductId, QuanOrdered);
    return ItemPtr();                   // check if success, then return *item

}

/*----------------------------------------------------------------------------*/
/*  Create a new order item containing only a text.                           */
/*  Returns item pointer or NULL in case of a fatal error.                    */
/*----------------------------------------------------------------------------*/
pxOrderItem*
pxOrderTransmit :: NewOrderTextItem
(
    const nString& text
)
{
    if ( Order_ )
    {
       Item_ = Order_->NewOrderTextItem(text, 0L);
       Item_->ToPharmosHMKText();
    }
    return ItemPtr();
}
