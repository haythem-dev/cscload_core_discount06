#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxartbas.hpp"
#include "pxcstbas.hpp"
#include "pxcsterm.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxtenderhead.hpp"
#include "pxtenderpos.hpp"
#include "pxtenderprogress.hpp"
/*----------------------------------------------------------------------------*/
/*  CloseTenderPos: This methode looks under special circumstances for an     */
/*  TenderOrder, loops thru the itemlist and builds per item  the sum of      */
/*  of the tenderprogress belonging to each article within this order         */
/*  If the sum per postion equals the contractqty+adddiscountpct on the       */
/*  regarding tenderpos, so the tenderpos state changes to close = '9'        */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CloseTenderPos
(
)
{
/*----------------------------------------------------------------------------*/
/*  Do some checks before calculation                                         */
/*----------------------------------------------------------------------------*/
    if ( !(OrderType().IsTenderOrder()) && !(OrderType().IsTenderInvoice()) )
       return ErrorState();

    if ( TenderNo() == 0 )            // just check for not needed work
       return ErrorState();

    // do not affect Hospital Tender in Bulgaria
    if (Session()->isBulgaria())
    {
       if ( TenderHead() )
       {
          if ( TenderHead()->IsHospitalTender() )
          {
             return ErrorState();
          }
       }
    }

/*----------------------------------------------------------------------------*/
/*  Now scan the list of positions                                            */
/*----------------------------------------------------------------------------*/
    pxOrderItemListIter it(*ItemList_);
    pxOrderItem *item;
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       item->CloseTenderPos();
       Error() = item->Error();
       if ( !IsGoodState() )
          break;
    }
    return ErrorState();
}
/*----------------------------------------------------------------------------*/
/*  CloseTenderHead: This methode closes the the tenderhead depende on        */
/*  this orders TenderNo. If there are no TenderPos entries belonging to this */
/*  TenderNo without the closestate = '9', so the the corresponsing TenderHead*/
/*  changes to the State Close == '9'                                         */
/*----------------------------------------------------------------------------*/
int
pxOrder :: CloseTenderHead
(
)
{
/*----------------------------------------------------------------------------*/
/*  Do some checks before calculation                                         */
/*----------------------------------------------------------------------------*/
    if ( !(OrderType().IsTenderOrder()) && !(OrderType().IsTenderInvoice()) )
       return ErrorState();

    if ( TenderNo() == 0 )            // just check for not needed work
       return ErrorState();

    // do not affect Hospital Tender in Bulgaria
    if (Session()->isBulgaria())
    {
       if ( TenderHead() )
       {
          if ( TenderHead()->IsHospitalTender() )
          {
             return ErrorState();
          }
       }
    }
/*----------------------------------------------------------------------------*/
/*  Now select Tenderpos entries with state not equal to '9'                  */
/*----------------------------------------------------------------------------*/
    pxTenderPosList* tpl = NULL;
    char  CloseState = '9';
    tpl = new pxTenderPosList(Session() );
    tpl->Select(TenderNo_, CloseState);
    if (tpl->Entries() == 0 )                // the is no entry without state = '9'
    {
       if ( TenderHead() )
       {
          nDBBeginTransaction(cDBTransRecord);
          TenderHead()->SetAutoBlocked();
		  if( Session()->isSwitzerland() )
		  {
				TenderHead()->SetDateTo( nDate() );
		  }
          TenderHead()->Put();
          Error() = TenderHead()->Error();
          if ( IsGoodState() )
          {
             nDBCommit(cDBTransRecord);          // commit changes
          }
          else
          {
             nDBRollBack();                      // roll them back in case of any error
          }
       }
       ClearError();                             // for safety continue
    }
    return ErrorState();
}
