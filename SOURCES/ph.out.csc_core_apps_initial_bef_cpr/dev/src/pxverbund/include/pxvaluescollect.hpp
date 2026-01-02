/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXVALUESCOLLECT.HPP

REVISION HISTORY

03 Febr 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXVALUESCOLLECT_DOTH
#define PXVALUESCOLLECT_DOTH

#include "types/pricetypeenum.inc"

class pxValuesCollect : public nCollectable
{

public:
// constructors:
                pxValuesCollect(const PriceTypeEnum PriceType);


// destructor:
                virtual  ~pxValuesCollect();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxValuesCollect&   operator=(const pxValuesCollect& src);
//  Assigns the values of 'src' to self and returns a reference to it.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
//  some methodes
    nMoney      IncreaseNetCash( nMoney value );
    nMoney      IncreaseSalesTax( nMoney value );
    void        SetValueNetCash( nMoney value)  { ValueNetCash_ = value;   }
    void        SetValueSalesTax( nMoney value) { ValueSalesTax_ = value;  }
    void        SetPriceType( PriceTypeEnum pricetype) { PriceType_ = pricetype;  }

// Some Queries
    nMoney      ValueNetCash()        { return ValueNetCash_;      }
    nMoney      ValueSalesTax()       { return ValueSalesTax_;     }
    PriceTypeEnum PriceType()         { return PriceType_;         }

protected:
    nMoney      ValueNetCash_;        // OrderValue Net
    nMoney      ValueSalesTax_;       // Sales Tax Value
    PriceTypeEnum PriceType_;         // Price Type 0 = FREESALE_PRICE (FF)
                                      //            1 = HEALTHFUND_PRICE(KK)
                                      //            2 = RETAIL_PRICE (EinzelHandel)
private:
    friend class pxValuesCollectList;
};

class pxValuesCollectList : public nDListCollect
{

public:
// constructors:

// destructor:
                virtual  ~pxValuesCollectList() {Clear();}
// member functions:
    void        Clear();
    pxValuesCollect*     Find( const PriceTypeEnum pricetype);
    void                 InitValues();
    void                 SetValueNetCash(nMoney value, const PriceTypeEnum pricetype);
    void                 SetValueSalesTax(nMoney value, const PriceTypeEnum pricetype);

protected:
private:
    friend class pxValuesCollectListIter;
};

class pxValuesCollectListIter : public nDListCollectIter
{

public:
// constructors:
    pxValuesCollectListIter(pxValuesCollectList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxValuesCollectListIter() {;}
};
#endif
