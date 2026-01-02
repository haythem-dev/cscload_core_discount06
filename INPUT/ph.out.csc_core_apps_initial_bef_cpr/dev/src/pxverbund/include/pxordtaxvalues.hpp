/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXORDTAXVALUES
Order valuse depend on taxlevel

REVISION HISTORY

27 Oct 20098 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXORDTAXVALUES_INC
#define PXORDTAXVALUES_INC

#include <map>

class pxSession;
class pxOrder;
class pxOrderItem;
class pxTaxRates;
class pxTaxRatesList;


/*----------------------------------------------------------------------------*/
/*  Structure OrderValues                                                     */
/*----------------------------------------------------------------------------*/

struct tORDERVALUE
{
    short         TaxLevel;              // Taxlevel
    double        ShipValue;             // Ship value
    double        TaxValue;              // Tax Value
    double        SalesTaxRate;          // Tax rate
};

typedef std::map<short, tORDERVALUE> OrderTaxValueMap;

class pxOrdTaxValues
{

public:


// constructors:
                      pxOrdTaxValues();

// destructor:
    virtual           ~pxOrdTaxValues();

// public member operators
    pxOrdTaxValues&    operator=(const pxOrdTaxValues& src);

// public member functions
    void              InitTaxLevels( pxTaxRatesList* taxrateslist);


//  Field updates
    void              SetOrderValues(pxOrderItem* item);
    void              ReCalcOrderValues(pxOrder* order);

// Queries:
    const OrderTaxValueMap& GetOrdTaxValueMap() { return OrdTaxValMap_; }

    void              Init();

private:
	OrderTaxValueMap OrdTaxValMap_;      // ordervalue buffer
};
#endif
