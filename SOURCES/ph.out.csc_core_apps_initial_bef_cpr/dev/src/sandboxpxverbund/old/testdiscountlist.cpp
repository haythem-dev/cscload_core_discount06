#include <UnitTest++/UnitTest++.h>
#include "SessionUtil.h"

using namespace std;

// ------------------------------------------------------------------------------------------- //
void testDiscountList(pxOrderTransmit* xmit )
{	
	short branchno = 75;
	int discountgroupno = 5109;
	int customerno = 240307;
	int qtyinrange = 2;
	//double shipvalue = 0.0;

	pxDiscountList*  diskl = new pxDiscountList(xmit->Session());
	diskl->SelectRange( branchno, discountgroupno, customerno );
	
	pxDiscountListIter cursor(*diskl);
	pxDiscount* diskentry = NULL;
	if( diskl->ReduceToValidOffers() )
	{
		for ( cursor.ToLast(); (diskentry = (pxDiscount*)cursor.Current()) != NULL; --cursor )
		{
			cout << "cursor geholt" << endl;

			if( diskentry->BaseQty() > 0  && diskentry->ArticleNo() == 0 )
			{
				if( qtyinrange >= diskentry->BaseQty() )
				{
					cout << "break 1" << endl;
					break;
				}
			}
			else if( diskentry->BaseMultSTDQty() > 0 && diskentry->ArticleNo() == 0 )
			{
				if( qtyinrange >= diskentry->BaseMultSTDQty() )
				{
					cout << "break 2" << endl;
					break;
				}
			}
			else if( diskentry->BaseValue() > 0.0 )
			{
				/*
				if( shipvalue >= (nMoney)diskentry->BaseValue() )
				{
					cout << "break 3" << endl;					
					break;
				}
				*/
			}
		}
	}

	if( diskentry != NULL )
    {
		cout << "diskentry != null" << endl;
    }
    delete diskl;
}

/*pxDiscount*
pxRangeControl :: RangeCondition
(
    pxSession   *session,
    pxOrder*    order
)
{
    
    pxDiscountListIter cursor(*diskl);
    pxDiscount*      diskentry = NULL;
    pxRangeCollectList* rcl = order->RangeCollectList();
    pxCustBase&       customer   = *order->Customer();
    pxCustPharmGroupList *phglist   = customer.PharmGroupList();
    diskl->SelectRange(BranchNo_, DiscountGrpNo_,CustomerNo_);
    diskl->ShrinkGroupExcluded(phglist);
    diskl->ShrinkDiscountPriceType(PreisTyp_);
    diskl->ShrinkCashPaymentPriceType(order, PreisTyp_);
	//diskl->ShrinkDateDelivery(order);

    if (diskl->ReduceToValidOffers())
    {
       for ( cursor.ToLast();(diskentry = (pxDiscount*)cursor.Current() ); --cursor )
       {
          if ( (diskentry->BaseQty() > 0  && diskentry->ArticleNo() == 0 ))
          {
             if ( QtyInRange_ >= diskentry->BaseQty() )
                break;
          }
          else
          if  ( diskentry->BaseMultSTDQty() > 0 && diskentry->ArticleNo() == 0 )
          {
             if ( QtyPackInRange_ >= diskentry->BaseMultSTDQty() )
                break;
          }
          else
          if  ( diskentry->BaseValue() > 0.0 )
          {
             if ( ShipValue_ >= (nMoney)diskentry->BaseValue() )
                break;
          }
       }
    }
    if ( diskentry != NULL )
    {
       RangeCondition_ = new pxDiscount(*diskentry);
       if ( diskl->Entries() > 1 )          // more then one entry found
       {
          if (!(IsValidMultyCondRange(diskl,rcl)) )
          {
             delete RangeCondition_;
             RangeCondition_ = NULL;
             delete diskl;
             return RangeCondition_;
          }
       }
       DefineRangeDiscountTyp(diskl,rcl);
    }
    delete diskl;
    return RangeCondition_;
	*/

