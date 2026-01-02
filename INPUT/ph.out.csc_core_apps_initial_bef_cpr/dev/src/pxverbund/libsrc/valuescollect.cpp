#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxcstbas.hpp"
#include "pxvaluescollect.hpp"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxValuesCollect :: pxValuesCollect
(
    const PriceTypeEnum PriceType              // Price Type
)
{
    PriceType_ = PriceType;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxValuesCollect :: ~pxValuesCollect()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxValuesCollect&
pxValuesCollect :: operator=( const pxValuesCollect& src)
{
    PriceType_        = src.PriceType_;
    ValueNetCash_     = src.ValueNetCash_;
    ValueSalesTax_    = src.ValueSalesTax_;
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRangeCollec list objects being inserted in the following        */
/*  ascending  sequence:                                                      */
/*  BranchNo, DiscountGrpNo                                                   */
/*----------------------------------------------------------------------------*/
int
pxValuesCollect :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxValuesCollect *that = (pxValuesCollect*)That;
    int retval = (PriceType_ == that->PriceType_) ? 0
               : (PriceType_ > that->PriceType_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  This methode just increases IncreaseNetCash_ by value                     */
/*----------------------------------------------------------------------------*/
nMoney
pxValuesCollect :: IncreaseNetCash
(
    nMoney value
)
{
    ValueNetCash_ += value;
    return ValueNetCash_;
}

/*----------------------------------------------------------------------------*/
/*  This methode just decreases DecreaseSalesTax_ by value                    */
/*----------------------------------------------------------------------------*/
nMoney
pxValuesCollect :: IncreaseSalesTax
(
    nMoney value
)
{
    ValueSalesTax_ += value;
    return ValueSalesTax_;
}

/*----------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
void
pxValuesCollectList :: Clear()
{
    pxValuesCollect  *curp;
    pxValuesCollectListIter cursor(*this);
    while ( (curp = (pxValuesCollect*) ++cursor) != NULL )
    {
        cursor.Remove();
        delete curp;
    }
}

/*----------------------------------------------------------------------------*/
/* Find returns a pxValuesCollect pointer to the corresponding entry          */
/* depend on given PriceType. If entry is not found within the list, so NULLP */
/* will be returned                                                           */
/*----------------------------------------------------------------------------*/
pxValuesCollect*
pxValuesCollectList :: Find
(
    const PriceTypeEnum PriceType
)
{
    pxValuesCollectListIter   iter( *this );          // define iterator
    pxValuesCollect           *entryp = NULL;         // pointer to listentry

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxValuesCollect*) ++iter) != NULL ) // browse list
    {
        if ( (entryp->PriceType() == PriceType ) )
            break;
    }
    return   entryp;                               // return entrypointer
}

/*----------------------------------------------------------------------------*/
/* InitValues: Inits the values with every available entry within this list   */
/*----------------------------------------------------------------------------*/
void
pxValuesCollectList :: InitValues
(
)
{
    pxValuesCollectListIter   iter( *this );          // define iterator
    pxValuesCollect           *entryp = NULL;         // pointer to listentry
    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxValuesCollect*) ++iter) != NULL ) // browse list
    {
        entryp->SetValueNetCash(pxConstants::mZero);
        entryp->SetValueSalesTax(pxConstants::mZero);
        entryp->SetPriceType(FREESALE_PRICE);
    }
}

/*----------------------------------------------------------------------------*/
/* SetValueNetCash:                                                           */
/*----------------------------------------------------------------------------*/
void
pxValuesCollectList :: SetValueNetCash
(
    nMoney        value,
    const PriceTypeEnum pricetype
)
{
    pxValuesCollectListIter   iter( *this );        // define iterator

    pxValuesCollect *entryp = Find(pricetype);      // pointer to listentry
    if (entryp != NULL)
    {
        entryp->IncreaseNetCash(value);
    }
    else
    {
        entryp = new pxValuesCollect(pricetype);
        entryp->SetValueNetCash(pxConstants::mZero);
        entryp->SetValueSalesTax(pxConstants::mZero);
        entryp->IncreaseNetCash(value);
        Append(entryp);
    }
}

/*----------------------------------------------------------------------------*/
/* SetValueSalesTax:                                                          */
/*----------------------------------------------------------------------------*/
void
pxValuesCollectList :: SetValueSalesTax
(
    nMoney        value,
    const PriceTypeEnum   pricetype
)
{
    pxValuesCollectListIter   iter( *this );        // define iterator

    pxValuesCollect *entryp = Find(pricetype);      // pointer to listentry
    if (entryp != NULL)
    {
        entryp->IncreaseSalesTax(value);
    }
    else
    {
        entryp = new pxValuesCollect(pricetype);
        entryp->SetValueNetCash(pxConstants::mZero);
        entryp->SetValueSalesTax(pxConstants::mZero);
        entryp->IncreaseSalesTax(value);
        Append(entryp);
    }
}
