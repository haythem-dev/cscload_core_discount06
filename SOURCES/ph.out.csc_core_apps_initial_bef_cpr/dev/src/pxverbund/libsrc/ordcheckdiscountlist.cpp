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
#include "pxcstrou.hpp"
#include "pxoclpar.hpp"
#include "pxrangemember.hpp"
#include "pxdiscountordtyp.hpp"
#include "pxrangecontrol.hpp"
#include "pxitemdiscount.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  CheckDiscountListCroatia: This is a special methode devoloped for the     */
/*  order entry system in Croatia                                             */
/*  This methode builds up a temporary ItemDiscountList(KdAuftragPosRab) for  */
/*  all item within this order                                                */
/*  After that it runs through this list and looks for entries with           */
/*  discounttype 1 == Natra and searches entries for the same postion number  */
/*  discountvaluepct. If found, the discountvaluepct is written into the      */
/*  natra entry for later use durung order transfer to Pharmos                */
/*  correct discount percentages to the customer                              */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CheckDiscountListCroatia
(
)
{
    pxItemDiscountList* posrablist = NULL;
    pxItemDiscount*        posrabp = NULL;
    pxItemDiscount*        pctrabp = NULL;
    tKDAUFTRAGPOSRAB        record;
    pxOrderItem*              item = NULL;             // OrderItem Entry

/*----------------------------------------------------------------------------*/
/*  Basic sanity checks.                                                      */
/*----------------------------------------------------------------------------*/
     ClearError();
    if (!ItemList_ )                    // then order item processing not open
       return ExternalError(CMsgStream(), CMSG_ORD_NOTOPEN, KdAuftragNr_);
/*----------------------------------------------------------------------------*/
/*  Additional sanity checks.                                                 */
/*----------------------------------------------------------------------------*/
    if (!Session()->isCroatia())
       return NULL;

    if ( !IsPseudoLock() )
    {
       if ( !IsLocked() )                  // order still locked ??
       {
          ExternalError(CMsgStream(),CMSG_ORD_LOCK_DISAPPEARED, KdAuftragNr_);
          return NULL;
       }
    }
    if (AnzPos() == 0 )
       return ErrorState();

    // OrderType is not discountable
    if ( !OrderType().IsDiscountable() )
          return ErrorState();

/*----------------------------------------------------------------------------*/
/*  First collect all rebates  until now into a temporary                     */
/*  pxItemDiscountList(posrablist). Scan for that the order position list     */
/*----------------------------------------------------------------------------*/
    posrablist = new pxItemDiscountList(Session());
    pxOrderItemListIter it(*ItemList_);
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       if ( item->ItemDiscountList() )
       {
          pxItemDiscountListIter cursor(*item->ItemDiscountList());
          while ( (posrabp = (pxItemDiscount*) ++cursor) != NULL )
          {
             Assign(record, *posrabp);
             posrablist->AddToList(&record,0);
          }
       }
    }
/*----------------------------------------------------------------------------*/
/*  Now loop through this list and look for entries with discounttype == 1    */
/*  of the temporary itemdiscountlist posrablist                              */
/*----------------------------------------------------------------------------*/
    pxItemDiscountListIter iter(*posrablist);
    if ( posrablist->Entries() == 0 )
    {
       return ErrorState();
    }
    while ( (posrabp = (pxItemDiscount*) ++iter) != NULL )
    {
       if ( posrabp->DiscountType() == BestBuy_NatraDefault )
       {
          pctrabp = posrablist->FindDiscountValuePctPosNr(posrabp->PosNr() );
          if ( pctrabp )
          {
             posrabp->SetDiscountValuePct( pctrabp->DiscountValuePct() );
             posrabp->Put();
          }
       }
    }
    return ErrorState();
}
