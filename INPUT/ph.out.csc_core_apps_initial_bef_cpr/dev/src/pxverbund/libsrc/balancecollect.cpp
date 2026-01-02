/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxBalanceCollect.

REVISION HISTORY

08 January 2008 V1.00 REV 00 written by Ysbrand Bouma.
*/
#include "pxbalancecollect.hpp"
#include "pxrecord.h"
#include "pxsess.hpp"


/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxBalanceCollect :: pxBalanceCollect
(
    const nMoney& TotalBalance,          // Balance
    const nMoney& Balance,               // Balance
    const short   TaxLevel               // TaxLevel
)
{
    TotalBalance_     = TotalBalance;
    Balance_          = Balance;
    TaxLevel_         = TaxLevel;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxBalanceCollect :: pxBalanceCollect
(
    const pxBalanceCollect& src
)
{
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxBalanceCollect :: ~pxBalanceCollect()
{
    ;
}
/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxBalanceCollect&
pxBalanceCollect :: operator=( const pxBalanceCollect& src)
{
    TotalBalance_     = src.TotalBalance_;
    Balance_          = src.Balance_;
    TaxLevel_         = src.TaxLevel_;
    return *this;
}
/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRangeCollec list objects being inserted in the following        */
/*  ascending  sequence:                                                      */
/*  BranchNo, DiscountGrpNo                                                   */
/*----------------------------------------------------------------------------*/
int
pxBalanceCollect :: CompareTo
(
    const nCollectable   * /* That */,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    int retval = 0;
    // pxBalanceCollect *that = (pxBalanceCollect*)That;

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  This methode just increases Balance_ by value                             */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollect :: IncreaseBalance
(
    nMoney  value
)
{
    Balance_ += value;
    return Balance_;

}
/*----------------------------------------------------------------------------*/
/*  This methode just increases TotalBalance_ by value                        */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollect :: IncreaseTotalBalance
(
    nMoney  value
)
{
    TotalBalance_ += value;
    return TotalBalance_;

}
/*----------------------------------------------------------------------------*/
/*  This methode just decreases Balance_ by value                             */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollect :: DecreaseBalance
(
    nMoney  value
)
{
    Balance_ -= value;
    return Balance_;

}
/*----------------------------------------------------------------------------*/
/*  This methode just decreases TotalBalance_ by value                        */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollect :: DecreaseTotalBalance
(
    nMoney  value
)
{
    TotalBalance_ -= value;
    return TotalBalance_;

}
/*----------------------------------------------------------------------------*/
/*  This methode just sets Balance_ by value                                  */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollect :: SetBalance
(
    nMoney  value
)
{
    Balance_ = (TotalBalance_ - value);
    return Balance_;

}
/*---------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
void
pxBalanceCollectList :: Clear()
{

    pxBalanceCollect  *curp;
    pxBalanceCollectListIter cursor(*this);
    while ( (curp = (pxBalanceCollect*) ++cursor) != NULL )
    {
       cursor.Remove();
       delete curp;
    }
}

/*----------------------------------------------------------------------------*/
/* GetBalance Returns the Balance                                             */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollectList :: GetBalance
(
    const   short    TaxLevel
)
{
    nMoney  balance(0.0);
    pxBalanceCollect  *curp = NULL;    // pointer to listentry
    curp = Find(TaxLevel);
    if ( curp )
    {
       balance += curp->Balance();
    }
    return   balance;                       // return value
}
/*----------------------------------------------------------------------------*/
/* GetTotalBalance Returns the Balance                                        */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollectList :: GetTotalBalance
(
    const   short    TaxLevel
)
{
    nMoney  totalbalance(0.0);
    pxBalanceCollect  *curp = NULL;    // pointer to listentry
    curp = Find(TaxLevel);
    if ( curp )
    {
       totalbalance += curp->TotalBalance();
    }
    return   totalbalance;                       // return value
}
/*----------------------------------------------------------------------------*/
/*  This methode just increases Balance_                                      */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollectList :: IncreaseBalance
(
    nMoney  value,
    const   short    TaxLevel
)
{
    nMoney  balance(0.0);
    pxBalanceCollect  *curp = NULL;    // pointer to listentry

    curp = Find(TaxLevel);
    if ( curp )
    {
       curp->IncreaseBalance(value);
       balance = curp->Balance();
    }
    return balance;

}
/*----------------------------------------------------------------------------*/
/*  This methode just increases TotalBalance_                                 */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollectList :: IncreaseTotalBalance
(
    nMoney  value,
    const   short    TaxLevel
)
{
    nMoney  totalbalance(0.0);
    pxBalanceCollect  *curp = NULL;    // pointer to listentry

    curp = Find(TaxLevel);
    if ( curp )
    {
       curp->IncreaseTotalBalance(value);
       totalbalance = curp->TotalBalance();
    }
    return totalbalance;

}
/*----------------------------------------------------------------------------*/
/*  This methode just decreases Balance_                                      */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollectList :: DecreaseBalance
(
    nMoney  value,
    const short    TaxLevel
)
{
    nMoney  balance(0.0);
    pxBalanceCollect  *curp = NULL;    // pointer to listentry
    curp = Find(TaxLevel);
    if ( curp )
    {
       curp->DecreaseBalance(value);
       balance += curp->Balance();
    }
    return balance;
}

/*----------------------------------------------------------------------------*/
/*  This methode just Sets Balance_                                           */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollectList :: SetBalance
(
    nMoney  value,
    const short    TaxLevel
)
{
    nMoney  balance(0.0);
    pxBalanceCollect  *curp = NULL;    // pointer to listentry
    curp = Find(TaxLevel);
    if ( curp )
    {
       curp->SetBalance(value);
       balance += curp->Balance();
    }
    return balance;
}

/*----------------------------------------------------------------------------*/
/*  This methode just decreases TotalBalance_                                 */
/*----------------------------------------------------------------------------*/
nMoney
pxBalanceCollectList :: DecreaseTotalBalance
(
    nMoney  value,
    const short    TaxLevel
)
{
    nMoney  totalbalance(0.0);
    pxBalanceCollect  *curp = NULL;    // pointer to listentry
    curp = Find(TaxLevel);
    if ( curp )
    {
       curp->DecreaseTotalBalance(value);
       totalbalance += curp->TotalBalance();
    }
    return totalbalance;
}

/*----------------------------------------------------------------------------*/
/* Find returns a pxBalanceCollectList pointer to the corresponding entry     */
/* depend on given TaxLevel. If entry is not found within the list , so NULLP */
/* will be returned                                                           */
/*----------------------------------------------------------------------------*/
pxBalanceCollect*
pxBalanceCollectList :: Find
(
    const short    TaxLevel
)
{
    pxBalanceCollectListIter   iter( *this );          // define iterator
    pxBalanceCollect           *entryp = NULL;         // pointer to listentry

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxBalanceCollect*) ++iter) != NULL ) // browse list
    {
       if ( (entryp->TaxLevel() == TaxLevel) )
          break;
    }
    return   entryp;                               // return entrypointer
}
