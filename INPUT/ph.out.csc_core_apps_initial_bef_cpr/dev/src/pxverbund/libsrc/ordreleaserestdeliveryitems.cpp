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
#include "pxcstot.hpp"
#include "pxdellog.hpp"
#include "pxarticlequota.hpp"
#include "pxstockbooking.hpp"
#include <logger/loggerpool.h>
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* This methode releases the deliverable entries within dlist                 */
/* An OrderItem will be booked and deletes the rest delivery entry from the   */
/* database.                                                                  */
/*----------------------------------------------------------------------------*/
int  pxOrder :: releaseRestDeliveryItems(pxVerbund::subsequentDelivery::pxDeliveryPosList* dlist)
{
    BLOG_TRACE_METHOD( libcsc::LoggerPool::getLoggerOrder(), "pxOrder::releaseRestDeliveryItems()" );

    int retval = 0;                      // count items
	pxVerbund::subsequentDelivery::pxDeliveryPosListIter  cursor(*dlist);
	pxVerbund::subsequentDelivery::pxDeliveryPos         *dpos;

    cursor.Reset();                  // top of list
    while ( ( dpos = (pxVerbund::subsequentDelivery::pxDeliveryPos *) ++cursor ) != NULL )
    {
		dpos->nDBBeginTransaction(cDBTransRecord);
		dpos->Get(cDBGET_FORUPDATE);
		if (!dpos->IsGoodState())
		{
			delete cursor.Remove(); // delete object from list and
			nDBCommit(cDBTransRecord);
			continue;
		}
		if ( dpos->Status() >= pxVerbund::subsequentDelivery::DP_WORKUP_DONE)
		{
			delete cursor.Remove(); // delete object from list and
			nDBCommit(cDBTransRecord);
			continue;
		}

		dpos->SetStatus(pxVerbund::subsequentDelivery::DP_WORK_INPROGRESS);
		dpos->Put();
		nDBCommit(cDBTransRecord);
		
        pxOrderItem* item = NewOrderItem_16(dpos); // make item
		if (item)
		{
			nMessage text(CMsgStream(), CMSG_ITM_RESTDELIVERY);
			nString bem = text.String();
			bem.Compress('\n');
			item->Bemerkungen(bem);
			pxDeliveryLog/*&*/ dlog /*= pxDeliveryLog*/(*item, *dpos);
			nDBBeginTransaction(cDBTransSet);
			dlog.Put();
			Error() = dlog.Error();       // catch error from dlog object
			if ( IsGoodState() )
			{
				if ( Param()->IsSCloseRestDeliveryAtOnce() )
				{
					dpos->SetStatus(pxVerbund::subsequentDelivery::DP_WORKUP_DONE);
					dpos->Put();
				}
				else
				{		
					dpos->Delete();            // delete entry
				}
				Error() = dpos->Error();   // catch error fro delete
				if ( IsGoodState() )       // if ok
				{
                    delete cursor.Remove(); // delete object from list and
					nDBCommit(cDBTransSet); // commit changes
				}
			}
			else
			{
				nDBRollBack();             // rollback changes and
				break;
			}
		}
	}
	if ( IsGoodState() )                      // if all ok, then
       return retval;                          // return count

    return ErrorState();
}
