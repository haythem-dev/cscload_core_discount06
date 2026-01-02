/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxTaxRates Class.

REVISION HISTORY

12 december 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXTAXRATES_INC
#define PXTAXRATES_INC

#include "pxbase/pxrecord.hpp"

struct tTAXRATES;

class pxTaxRates : public pxDBRecord
{

public:


// constructors:
                pxTaxRates(pxTaxRates& src);
                pxTaxRates(pxSession *session);
                pxTaxRates(pxSession *session, tTAXRATES& src);
// destructor:
                virtual  ~pxTaxRates();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxTaxRates&   operator=(const pxTaxRates& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxTaxRates&   operator=(const tTAXRATES& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxTaxRates&
                Assign(pxTaxRates& dest, const tTAXRATES& src);
    friend   tTAXRATES&
                Assign(tTAXRATES& dest, const pxTaxRates& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

//  Queries:
    short            TaxLevel()           {return TaxLevel_           ;}
    double          SalesTaxRate()       {return SalesTaxRate_       ;}

protected:
    void        Init();

    short            TaxLevel_           ;     // Taxlevel
    double          SalesTaxRate_       ;     // Salestaxrate

private:
    friend class pxTaxRatesList;

};

class pxTaxRatesList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxTaxRatesList(pxSession *session);
//  destructor:
                virtual ~pxTaxRatesList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int     count = 50);
    void        Clear()        {nDBRecordSet::Clear();}
    pxTaxRates* Find(const short TaxLevel);

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

protected:

private:
    friend class pxTaxRatesListIter;
};

class pxTaxRatesListIter : public nDListCollectIter
{

public:
// constructors:
    pxTaxRatesListIter(pxTaxRatesList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxTaxRatesListIter() {;}
};
#endif
