#include "pxitem.hpp"
#include <date.hpp>
#include "pxsess.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxdelpos.hpp"
#include "pxorder.hpp"
#include "pxcstot.hpp"
#include "ibtbrancheslist.hpp"
#include "ibtbranches.hpp"
#include "ibtbrancharticleconfig.h"
#include "ibtassortmenttype.h"
#include "pxoeparm.hpp"
#include "types/messagecodeenum.inc"
#include <ibt/ibtrequest/iibtrequest.h>
/*----------------------------------------------------------------------------*/
/*  Return a pointer to the aux delivery pos.list. If no list is currently    */
/*  linked to the item object, a new list is constructed, and, if an active   */
/*  item record is in core, its records are selected from the database.       */
/*----------------------------------------------------------------------------*/
pxVerbund::subsequentDelivery::pxDeliveryPosList*
pxOrderItem :: AuxDelList
(
)
{
    if (! AuxDelList_ )                 // no delivery pos list constructed
    {
       nDate today;                     // current date
       nDate dayOffcreation;            // date created
       // get dayOffcreation
       if ( !(&Order()) )               // should not happen(just safety case)
       {
          dayOffcreation = today;
       }
       else
       {
          dayOffcreation = Order().DateTimeCreated();
       }
       AuxDelList_ = new pxVerbund::subsequentDelivery::pxDeliveryPosList( Session() );
       if ( IsAuxPosted() || IsDisponieren() || IsNachliefern() || IsVerbundAuftragsPosition() || IsDayNightMergePosition() || IsDispoItem() )
          AuxDelList_->SelectByOrderPosAndDate(KdAuftragNr_, PosNr_, dayOffcreation); // select them
    }
    return AuxDelList_;
}

/*----------------------------------------------------------------------------*/
/*  Checks the requirements for the usage of the alternate delivery service   */
/*   -- artikel                                                               */
/*   -- customer                                                              */
/*   -- alternate deliver companies                                           */
/*   -- timewindows                                                           */
/*  Returns ErrorState or message.                                            */
/*----------------------------------------------------------------------------*/
int pxOrderItem::AuxDeliveryCheck( short ibtbranchno, int flags /* control flags */, BookingType btype /* item posting type */ )
{
	return this->CheckPossibilityForIBTDelivery( ibtbranchno, flags, btype );			
}
/*----------------------------------------------------------------------------*/
/*  Construct a new delivery pos                                              */
/*----------------------------------------------------------------------------*/
pxVerbund::subsequentDelivery::pxDeliveryPos*
pxOrderItem :: NewDeliveryPos
(
    const pxVerbund::subsequentDelivery::pxDelPosTyp PosTyp
)
{
    ClearError();                       // Item error object cleanup

    return new pxVerbund::subsequentDelivery::pxDeliveryPos(*this, PosTyp);
}
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  This function returns the quantity as Restdelivery                        */
/*----------------------------------------------------------------------------*/
long
pxOrderItem :: MengeNachgeliefert
(
)
{
    long                 retval = 0;

    if (IsNachliefern())                // there should exist a deliverypos entry
    {
       if ( AuxDelList() )
       {
           pxVerbund::subsequentDelivery::pxDeliveryPos* dp = AuxDelList_->Find(KdAuftragNr_, PosNr_, pxVerbund::subsequentDelivery::pxDPT_RESTDELIVERY_ITEM);
          if (dp)
          {
             if (dp->IsRestDeliveryItem())
                 retval = dp->Menge();
          }
       }
    }

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  This function returns the quantity as Purchase Order Quantity             */
/*----------------------------------------------------------------------------*/
long
pxOrderItem :: MengeDisponiert
(
)
{
    long                 retval = 0;

    if (IsDisponieren() )           // there should exist a deliverypos entry
    {
       if ( AuxDelList() )
       {
          pxVerbund::subsequentDelivery::pxDeliveryPos* dp = AuxDelList_->Find(KdAuftragNr_, PosNr_, pxVerbund::subsequentDelivery::pxDPT_DISPOSAL_ITEM);
          if (dp)
          {
             if (dp->IsDisPosalItem())
                 retval = dp->Menge();
          }
       }
    }

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  This function returns the auxiliarycompanynumber from  where the quantity */
/*  is posted from.                                                           */
/*----------------------------------------------------------------------------*/
short pxOrderItem::VerbundFilialNr()
{
    if ( VerbundFilialNr_ > 0 )             // if already exist in item object
       return VerbundFilialNr_;

    if ( IsAuxPosted() || IsDayNightMergePosition() )   // there should exist a deliverypos entry
    {
        libcsc::ibt::IIbtRequestPtr ibtRequest = getIbtRequest();
        if (NULL != ibtRequest.get())
        {
            VerbundFilialNr_ = ibtRequest->getIbtBranchNo();
        }
    }
    return VerbundFilialNr_;
}

/*----------------------------------------------------------------------------*/
/*  This function returns the IDFNr for what customer the quantity has to be  */
/*  posted.                                                                   */
/*----------------------------------------------------------------------------*/
long pxOrderItem::VerbundUrIDFNr()
{
    long customerNo = 0;

    if ( IsAuxPosted() || IsDayNightMergePosition() )      // there should exist a deliverypos entry
    {
        libcsc::ibt::IIbtRequestPtr ibtRequest = getIbtRequest();
        if (NULL != ibtRequest.get())
        {
			customerNo = ibtRequest->getCustomerNo();
        }
    }
    return customerNo;
}
/*----------------------------------------------------------------------------*/
/*  This function returns the IDFNr for what customer the quantity has to be  */
/*  posted.                                                                   */
/*----------------------------------------------------------------------------*/
long pxOrderItem::VerbundUrKaufNr()
{
    long orderNo = 0;

    if ( IsAuxPosted() || IsDayNightMergePosition() )      // there should exist a deliverypos entry
    {
        libcsc::ibt::IIbtRequestPtr ibtRequest = getIbtRequest();
        if (NULL != ibtRequest.get())
        {
            orderNo = ibtRequest->getCscOrderNo();
        }
    }
    return orderNo;
}
