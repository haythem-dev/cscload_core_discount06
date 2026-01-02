/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Class pxOrdTaxValues
Collecting order values depend on positions taxrates

REVISION HISTORY

27 Oct 2009 V1.00 REV 00 written by Ysbrand Bouma
*/
#include "pxordtaxvalues.hpp"
#include "pxtaxrates.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxartbas.hpp"

/*----------------------------------------------------------------------------*/
/*  Constructor for this object                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
pxOrdTaxValues :: pxOrdTaxValues()
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Destructor  for direct booking object                                     */
/*                                                                            */
/*----------------------------------------------------------------------------*/
pxOrdTaxValues :: ~pxOrdTaxValues
()
{
}

/*----------------------------------------------------------------------------*/
/*  Init                                                                      */
/*----------------------------------------------------------------------------*/
void pxOrdTaxValues :: Init()
{
    OrdTaxValMap_.clear();
}
/*----------------------------------------------------------------------------*/
/*  InitTaxLevels                                                             */
/*----------------------------------------------------------------------------*/
void pxOrdTaxValues::InitTaxLevels( pxTaxRatesList* TaxRatesList )
{
    pxTaxRates*    entriep = NULL;
    pxTaxRatesListIter cursor((*TaxRatesList));

    while ( (entriep = (pxTaxRates*) ++cursor) != NULL )
    {
        tORDERVALUE v;
        v.TaxLevel = entriep->TaxLevel();
        v.SalesTaxRate = entriep->SalesTaxRate();
        OrdTaxValMap_.insert(std::pair<short, tORDERVALUE>(v.TaxLevel, v));
    }
}

/*----------------------------------------------------------------------------*/
/* SetOrderValues                                                             */
/*----------------------------------------------------------------------------*/
void pxOrdTaxValues :: SetOrderValues(pxOrderItem* item)
{
    nMoney   shiptaxvalue(0.0);
    if (item->ArtBase() != NULL)
    {
        OrderTaxValueMap::iterator it = OrdTaxValMap_.find(item->ArtBase()->TaxLevel());
        if (it != OrdTaxValMap_.end())
        {
            shiptaxvalue = (item->ShipValue() * item->SalesTaxRate()) / 100.0;
            shiptaxvalue += (item->NaturalRebateValue() * item->SalesTaxRate()) / 100.0;
            (*it).second.ShipValue += item->ShipValue();
            (*it).second.TaxValue += shiptaxvalue;
        }
    }
}
/*----------------------------------------------------------------------------*/
/* ReCalcOrderValues                                                          */
/*----------------------------------------------------------------------------*/
void pxOrdTaxValues :: ReCalcOrderValues (    pxOrder* order )
{
    
    pxOrderItemList* ItemList = order->ItemList();
    pxOrderItemListIter it(*ItemList);
    pxOrderItem* item;
    while ( (item = (pxOrderItem*) ++it) != NULL )
    {
       SetOrderValues(item);
    }
}

