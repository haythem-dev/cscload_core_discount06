#include "pxrecord.h"
#include "pxdevice.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxartbas.hpp"
#include "pxoeparm.hpp"
#include "pxdelpos.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxordevt.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxcstot.hpp"
#include "pxcstpaymentterms.hpp"
#include "pxbranch.hpp"
#include "pxcstonr.hpp"
#include "pxseporderartgrp.hpp"
#include "pxcstprint.hpp"
#include "pxorderprolink.hpp"
#include "pxkdauftragdebtrel.hpp"
#include "pxordervalues.hpp"
#include "pxordercalcmode.hpp"
#include "pxdebitlimit.hpp"
#include "pxcremamail.hpp"
#include "pxbase/pxconstants.hpp"
#include "cremamailhandler.h"
#include "pxtxtdoc.hpp"

/*----------------------------------------------------------------------------*/
int pxOrder::SetRestDeliveryPositionsToReadyForWorkup()
{
    if ( !Param()->IsSCloseRestDeliveryAtOnce() )
    {
        return ErrorState();
    }
    pxVerbund::subsequentDelivery::pxDeliveryPos* dp = NULL;
    pxOrderItemListIter it(*ItemList_);
    pxOrderItem *item;
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsNachliefern() )
       {
          dp = item->AuxDelList()->Find(KdAuftragNr_, item->PosNr_, pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
          if (dp)
          {
              if ( dp->IsGenerated() )
              {
                  dp->SetStatus( pxVerbund::subsequentDelivery::DP_READY_FOR_WORKUP);
                  dp->Put();
                  Error() = dp->Error();
              }
          }
       }
    }
    return ErrorState();
}

/*----------------------------------------------------------------------------*/
int pxOrder::SetDisposalPositionsToReadyForWorkup()
{
    if ( !Param()->IsSCloseDispoAtOnce() )
    {
        return ErrorState();
    }
    pxVerbund::subsequentDelivery::pxDeliveryPos* dp = NULL;
    pxOrderItemListIter it(*ItemList_);
    pxOrderItem *item;
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->IsDisponieren() || item->IsDispoItem() )
       {
          dp = item->AuxDelList()->Find(KdAuftragNr_, item->PosNr_, pxVerbund::subsequentDelivery::pxDPT_DISPOSAL_ITEM);
          if (dp)
          {
              if ( dp->IsGenerated() )
              {
                  dp->SetStatus( pxVerbund::subsequentDelivery::DP_READY_FOR_WORKUP);
                  dp->Put();
                  Error() = dp->Error();
              }
          }
       }
    }
    return ErrorState();
}
