/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrderItem:
Calculate what kind of discount is given on this product, depend
on entries within table discount.

REVISION HISTORY

07 April 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitem.hpp"
#include "pxsess.hpp"
#include "pxitemdiscount.hpp"

/*----------------------------------------------------------------------------*/
/* AddOnDiscountPct                                                           */
/*----------------------------------------------------------------------------*/
bool
pxOrderItem :: AddOnDiscountPct
(
    double ValuePct,
    double DiffValuePct
)
{
    bool retval = false;
	nString m_str;
	m_str = "pxOrderItem :: AddOnDiscountPct";

    pxItemDiscount*   entryp = NULL;
    if ( ItemDiscountList()->Entries() > 0 )
    {
       pxItemDiscountListIter iter( *ItemDiscountList_);

       while ( (entryp = ( pxItemDiscount*) ++iter) != NULL )
       {
          if (entryp->DiscountValuePct() > 0)
          {
             entryp->SetDiscountValuePct((entryp->DiscountValuePct() + ValuePct) - DiffValuePct );
             entryp->nDBBeginTransaction(cDBTransRecord);
			 entryp->logKdAuftragPosRab(m_str);
             entryp->Put();
             if ( entryp->IsGoodState() )
             {
                entryp->nDBCommit(cDBTransRecord);          // commit changes
             }
             else
             {
                entryp->nDBRollBack();                      // roll them back in case of any error
             }
             retval = true;
             break;
          }
       }
    }
    return retval;
}
