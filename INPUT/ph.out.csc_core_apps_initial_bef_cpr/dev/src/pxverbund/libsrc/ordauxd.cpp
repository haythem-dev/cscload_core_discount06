#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "pxdellog.hpp"
#include "pxarticlequota.hpp"
#include "pxstockbooking.hpp"
#include <logger/loggerpool.h>
#include "types/origintypeenum.inc"

/*----------------------------------------------------------------------------*/
/* This methode searches for deliverable Restdelivery positions of the        */
/* current customer. If the quantity to post fits the quantity on stock,      */
/* so an OrderItem will be generated and the Delivery Position entry is       */
/* deleted from the database. A special handling for MSV3 orders is           */
/* implemented.                                                               */
/*----------------------------------------------------------------------------*/
int  pxOrder :: PostRestDelivery()
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerOrder(), "pxOrder::PostRestDelivery()" );

    int retval = 0;                      // count items
    pxVerbund::subsequentDelivery::pxDeliveryPosList     *dlist = new pxVerbund::subsequentDelivery::pxDeliveryPosList( Session() );
    pxCustBase*  customer = Customer();
    const pxCustOrderType&    ot = OrderType();
    nDate today;
/*----------------------------------------------------------------------------*/
/*  Sanity check                                                              */
/*----------------------------------------------------------------------------*/
    if (!ot.IsNormal() )
    {
        return retval;
    }

    // Do nothing for Croatia . See Ticket SR-064132
    if( Session()->isCroatia() )                // if Croatia
    {
        return retval;
    }

    //2015-01-14 Crema Problem mit abgetrenntem Defektauftrag
    if (IsSepDefectOrder() )
    {
        return retval;
    }

    // 2015-01-07 YB: do not add subsequent deliveries if it´s an VerbundAuftrag(batchschreiben == 1)
    if ( BatchSchreiben() == cORTYPE_AUXILIARY )
    {
        return retval;
    }
    // ignore customers with NachlieferTyp == 4 or 5
    // may be this is just a temporary change, so i did not changed the futher logik.
    if (customer->IsImmediateRestDeliveryUser() ||
        customer->IsParkRestDeliveryOrder()     ||
        customer->IsAskRestDeliveryUser() )
    {
        return retval;
    }

    retval = checkRestDeliveryPosList( dlist);
    if (dlist->Entries() == 0 )
    {
        delete dlist;
        return retval;
    }

    // reset stockbooking cache between quantity check and position booking.
    Session()->resetStockBooking();

    // 2014-04-24 SH: do not add subsequent deliveries if it´s an MSV3 order without default order label
    if( isMSV3Order() )
    {
        retval = MSV3PostRestDelivery(dlist);
        delete dlist;
        return retval;
    }

    retval = releaseRestDeliveryItems(dlist);
    delete dlist;

    if ( IsGoodState() )                      // if all ok, then
       return retval;                          // return count

    return ErrorState();
}

