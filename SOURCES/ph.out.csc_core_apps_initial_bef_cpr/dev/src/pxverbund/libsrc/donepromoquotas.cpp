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
#include "pxdonepromoquotas.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxDonePromoQuotas :: pxDonePromoQuotas
(
    const short PromotionNo,           // promotionNo
    const long  ArticleNo              // articleno
)
{
    PromotionNo_      = PromotionNo;
    ArticleNo_        = ArticleNo;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDonePromoQuotas :: pxDonePromoQuotas
(
    const pxDonePromoQuotas& src
)
{
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxDonePromoQuotas :: ~pxDonePromoQuotas()
{
    ;
}
/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxDonePromoQuotas&
pxDonePromoQuotas :: operator=( const pxDonePromoQuotas& src)
{
    PromotionNo_      = src.PromotionNo_;
    ArticleNo_        = src.ArticleNo_;
    return *this;
}
/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRangeCollec list objects being inserted in the following        */
/*  ascending  sequence:                                                      */
/*  BranchNo, DiscountGrpNo                                                   */
/*----------------------------------------------------------------------------*/
int
pxDonePromoQuotas :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxDonePromoQuotas *that = (pxDonePromoQuotas*)That;
    int retval = (PromotionNo_ == that->PromotionNo_) ? 0
                  : (PromotionNo_ > that->PromotionNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
void
pxDonePromoQuotasList :: Clear()
{

    pxDonePromoQuotas  *curp;
    pxDonePromoQuotasListIter cursor(*this);
    while ( (curp = (pxDonePromoQuotas*) ++cursor) != NULL )
    {
       cursor.Remove();
       delete curp;
    }
}

/*----------------------------------------------------------------------------*/
/*  Find return entryp depend on articleno and discountgrpno                  */
/*----------------------------------------------------------------------------*/
bool
pxDonePromoQuotasList :: Find
(
    const short PromotionNo,
    const long ArticleNo
)
{
    bool cFound = false;
    pxDonePromoQuotas *curp = NULL;             // ptr to current entry
    pxDonePromoQuotasListIter  cursor(*this);  // define an iterator
    while ( (curp = (pxDonePromoQuotas*) ++cursor) != NULL )
    {
       if (curp->ArticleNo() == ArticleNo && curp->PromotionNo() == PromotionNo )
       {
          cFound = true;
       }
    }
    return cFound;
}

/*----------------------------------------------------------------------------*/
/* DeleteInvalidEntries delete all entries corredponding to DiscountGrpNo     */
/*----------------------------------------------------------------------------*/
int
pxDonePromoQuotasList :: DeleteEntry
(
    const short PromotionNo,
    const long ArticleNo
)
{
    int retval = 0;
    pxDonePromoQuotas *curp = NULL;             // ptr to current entry
    pxDonePromoQuotasListIter  cursor(*this);   // define an iterator

    while ( (curp = (pxDonePromoQuotas*) ++cursor) != NULL )
    {
       if (curp->ArticleNo() == ArticleNo && curp->PromotionNo() == PromotionNo )
       {
          delete cursor.Remove();
          break;
       }
    }
    return retval;
}
