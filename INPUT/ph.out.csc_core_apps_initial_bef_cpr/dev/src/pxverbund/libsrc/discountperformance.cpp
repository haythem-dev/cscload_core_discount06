#include "pxrecord.h"
#include "pxdbxx.h"
#include "pxsess.hpp"
#include "pxdiscount.hpp"

/*----------------------------------------------------------------------------*/
/*  SaveDiscountList this a special BG implementation for better performance  */
/*  (I hope so)                                                               */
/*----------------------------------------------------------------------------*/
int
pxDiscountList :: SaveDiscountList
(
    pxDiscountList* dlist,
    const short    CasCadeNo
)
{
    pxDiscount  *dikp;
    pxDiscount  *newentryp;
    pxDiscountListIter dlistiter(*dlist);  // define an iterator

    while ( (dikp = (pxDiscount*) ++dlistiter) != NULL )
    {
        newentryp = new pxDiscount(*dikp);
        newentryp->SetCasCadeNo(CasCadeNo);
        Append(newentryp);
        SetKindOffCasCade( CasCadeNo );
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/*  ReloadDiscountList this a special BG implementation for better performance*/
/*  (I hope so)                                                               */
/*----------------------------------------------------------------------------*/
int
pxDiscountList :: ReloadDiscountList
(
    pxDiscountList* dlist,
    const short    CasCadeNo
)
{
    pxDiscount  *dikp;
    pxDiscount  *newentryp;
    pxDiscountListIter iter(*this);  // define an iterator

    while ( (dikp = (pxDiscount*) ++iter) != NULL )
    {
        if ( dikp->CasCadeNo() == CasCadeNo )
        {
            newentryp = new pxDiscount(*dikp);
            newentryp->SetCasCadeNo(CasCadeNo);
            dlist->Append(newentryp);
        }
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
/*  FindCasCadeNo this a special BG implementation for better performance     */
/*  (I hope so)                                                               */
/*----------------------------------------------------------------------------*/
bool
pxDiscountList :: FindCasCadeNo
(
    const short CasCadeNo
)
{
    bool retval = false;
    pxDiscount  *dikp;
    pxDiscountListIter dlistiter(*this);  // define an iterator

    while ( (dikp = (pxDiscount*) ++dlistiter) != NULL )
    {
        if ( dikp->CasCadeNo() == CasCadeNo )
        {
            retval = true;
        }
    }

    return retval;
}
