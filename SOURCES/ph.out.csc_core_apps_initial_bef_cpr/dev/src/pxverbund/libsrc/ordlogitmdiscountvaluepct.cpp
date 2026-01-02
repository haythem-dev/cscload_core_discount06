#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxcomtyp.hpp"
#include "pxstktra.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordervalues.hpp"
#include "pxordevt.hpp"
#include "pxcstot.hpp"
#include "pxcstrou.hpp"
#include "pxoclpar.hpp"
#include "pxeventreason.hpp"
#include "cremamailhandler.h"
#include "pxstockbooking.hpp"
#include "pxtxtdoc.hpp"
#include <logger/loggerpool.h>

int pxOrder::logItemDiscountValuePct()
{
    if (!Session()->isBulgaria())
    {
        return ErrorState();
    }
    if ( IsPseudoLock() )
    {
        return ErrorState();
    }
    double discountvaluepct(0.0);
    pxOrderItemListIter it(*ItemList_);
    pxOrderItem *item;
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
        if ( !item->IsCancelled() )
        {
            discountvaluepct = item->GetDiscountValuePct();
            std::stringstream s;
            s << "Auftrag= " << KdAuftragNr_ << ", PosNr=" << item->PosNr() << ", DiscountValuePct=" << (double)discountvaluepct;
            BLOG_DEBUG( libcsc::LoggerPool::getLoggerDiscountCalc(), s.str() );
        }
    }
    return ErrorState();
}
