/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Calculate Overdrive Condition depend on quantity ordered and
quantity on stock

REVISION HISTORY

04 December 2007 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxcstbas.hpp"
#include "pxorder.hpp"
#include "pxoeparm.hpp"
#include "pxcstot.hpp"
#include "pxsubordertype.hpp"
#include "pxordercriteria.hpp"

/*----------------------------------------------------------------------------*/
/*  Calulate Overdrive Condition depend on QToPost and QInStock and entry     */
/*  within table odercriteria for the ordered Article.                        */
/*  This function is only active on ordertype "OV" == Overdrive and just      */
/*  for non Video devices                                                     */
/*----------------------------------------------------------------------------*/
long
pxOrderItem :: OverDriveCondition
(
    const long QToPost,           // quantity to post
    const long QInStock           // quantity currently available in stock
)
{
    long                   orderq = QToPost;         // garantee constancy
    long                 qinstock = QInStock;        // garantee constancy
    // unused variable
    /* pxOrderEntryParam       &param =  */ Order().Param();
    pxOrderCriteria*            oc = NULL;
    pxOrderCriteriaList*       ocl = NULL;
    const pxCustOrderType&      ot = Order().OrderType();
    pxCustBase&           customer = *(Order().Customer());
    short                      VZ = customer.Vertriebszentrum();
    pxDevice               *device = Session()->Device();

/*----------------------------------------------------------------------------*/
/*  Do some pre tests                                                         */
/*----------------------------------------------------------------------------*/
    if ( device->IsVideo() )             // just for non Video Devices
       return orderq;

    if ( !ot.IsOverDrive () )
       return orderq;

    if (! customer.SubOrderType() )
       return orderq;
/*----------------------------------------------------------------------------*/
/*  Try to find  and entry for the ordered articleno within the table         */
/*  odercriteria                                                              */
/*----------------------------------------------------------------------------*/
    ocl = new  pxOrderCriteriaList(Session());
    ocl->Select(VZ,ArtikelNr_,Order().KdAuftragArt(),
                (customer.SubOrderType())->PharmacyGroupId());
    if ( ocl->Entries() == NULL )
    {
       delete ocl;
       return orderq;
    }
    oc = (pxOrderCriteria*)ocl->At(0);
    if (oc->IsGoodState() )
    {
       if ( !oc->IsRoundupToLimit() )
       {
          delete ocl;
          return orderq;
       }

       long  MinQty   = oc->MinOrderQty();
       nMoney MinValue = oc->MinOrderValue();
       // raise orderq until orderq > MinQty
       for ( ; orderq < MinQty; ++orderq )
       {
          if ( orderq > qinstock )
          {
              --orderq;
              break;
          }
       }
       // raise orderq until PosValue > MinValue
       for ( ;((double)orderq*Price() < MinValue);++orderq )
       {
          if ( orderq > qinstock )
          {
              --orderq;
              break;
          }
       }
       delete ocl;
    }

    return orderq;
}
