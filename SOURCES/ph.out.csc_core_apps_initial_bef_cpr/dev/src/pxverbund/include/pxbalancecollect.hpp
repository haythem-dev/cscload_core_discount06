/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXBALANCECOLLECT.HPP

REVISION HISTORY

08 January 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXBALANCECCOLLECT_DOTH
#define PXBALANCECCOLLECT_DOTH

#include <dlistcol.hpp>
#include <money.hpp>

class pxBalanceCollect : public nCollectable
{

public:
// constructors:
                pxBalanceCollect(const nMoney& TotalBalance,
                                 const nMoney& Balance,
                                 const short   TaxLevel
                                );
                pxBalanceCollect(const pxBalanceCollect &src);

// destructor:
                virtual  ~pxBalanceCollect();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxBalanceCollect&   operator=(const pxBalanceCollect& src);
//  Assigns the values of 'src' to self and returns a reference to it.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;


// Update Fields
    nMoney      IncreaseBalance( nMoney value );
    nMoney      DecreaseBalance( nMoney value );
    nMoney      IncreaseTotalBalance( nMoney value );
    nMoney      DecreaseTotalBalance( nMoney value );
    nMoney      SetBalance( nMoney value );
// Some Queries
    nMoney      TotalBalance()        { return TotalBalance_ ;     }
    nMoney      Balance()             { return Balance_ ;          }
    short      TaxLevel()            { return TaxLevel_;          }

protected:
    nMoney      TotalBalance_;        // TotalBalance = Init value from the beginning
    nMoney      Balance_;             // Balance
    short      TaxLevel_;            // TaxLevel

private:
    friend class pxBalanceCollectList;
};

class pxBalanceCollectList : public nDListCollect
{

public:
// constructors:

// destructor:
                virtual  ~pxBalanceCollectList() {Clear();}
// member functions:
    void        Clear();
    nMoney      GetBalance(const short TaxLevel);
    nMoney      GetTotalBalance(const short TaxLevel);
    nMoney      IncreaseBalance( nMoney value,const short TaxLevel);
    nMoney      DecreaseBalance( nMoney value,const short TaxLevel);
    nMoney      IncreaseTotalBalance( nMoney value,const short TaxLevel);
    nMoney      DecreaseTotalBalance( nMoney value,const short TaxLevel);
    nMoney      SetBalance( nMoney value,const short TaxLevel);

    pxBalanceCollect* Find( const short TaxLevel);

protected:
private:
    friend class pxBalanceCollectListIter;
};

class pxBalanceCollectListIter : public nDListCollectIter
{

public:
// constructors:
    pxBalanceCollectListIter(pxBalanceCollectList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxBalanceCollectListIter() {;}
};
#endif
