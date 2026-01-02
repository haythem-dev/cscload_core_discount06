#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxcstbas.hpp"
#include "pxcustdisccondition.hpp"

#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/* CheckOverdriveState; Checks, depend on Customercondition within            */
/* table cstdiscountcont, for Minordervalue. If the Minordervalue is not      */
/* reached, so this order is placed in DF status for manual maintenance.      */
/* Take care for a well constructed pxOrder object, to prevent                */
/* unpredictable results.                                                     */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CheckOverdriveState
(
)
{
    // unused variable
    /* pxOrderEntryParam &param      = */ Param();           // main Param
    pxCustBase*       customer    = Customer();       // customer
    // unused variable
    /* short             VZ         = */ customer->Vertriebszentrum(); // customers Branchno
    const pxCustOrderType&     ot = OrderType();
    pxDevice              *device = Session()->Device();
    nMoney           MinOrderValue(0.0);

    if ( device->IsVideo() )             // just for non Video Devices
       return ErrorState();

    if ( !ot.IsOverDrive () )            // Ordetype must be OV
       return ErrorState();

    if (! customer->SubOrderType() )
    {
       if ( !SubOrderType_.IsEmpty() )
       {
          customer->DiscountConditions(KdAuftragArt_, SubOrderType_);
       }
       else
       {
          return ErrorState();
       }
    }

    if ( ! customer->CustDiscCondition() )
       return ErrorState();

    MinOrderValue = customer->CustDiscCondition()->MinOrderValue();
    if (MinOrderValue == pxConstants::mZero )
       return ErrorState();

    if ( WertLieferung_ < MinOrderValue )
    {
       SetOverDriveCondition();
       ExternalError(CMsgStream(), CMSG_ORD_ORDERVALUE_TO_LOW);
    }

    return ErrorState();
}
