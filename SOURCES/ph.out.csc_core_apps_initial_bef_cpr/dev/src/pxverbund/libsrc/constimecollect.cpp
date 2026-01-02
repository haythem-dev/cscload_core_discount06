/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxConsTimeCollect.

REVISION HISTORY

05 May 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/
#include "pxconstimecollect.hpp"
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

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxConsTimeCollect :: pxConsTimeCollect
(
    const short   BranchNo,              // Branchnumber
    const long    CustomerNo,
    const nString& TourId,
    const nDate&   DatumKommi,
    const nClock&  ConsTime
)
{
    BranchNo_         = BranchNo;
    CustomerNo_       = CustomerNo;
    TourId_           = TourId;
    DatumKommi_       = DatumKommi;
    ConsTime_         = ConsTime;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxConsTimeCollect :: pxConsTimeCollect
(
    const pxConsTimeCollect& src
)
{
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxConsTimeCollect :: ~pxConsTimeCollect()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxConsTimeCollect&
pxConsTimeCollect :: operator=( const pxConsTimeCollect& src)
{
    BranchNo_         = src.BranchNo_;
    CustomerNo_       = src.CustomerNo_;
    TourId_           = src.TourId_;
    DatumKommi_       = src.DatumKommi_;
    ConsTime_         = src.ConsTime_;
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRangeCollec list objects being inserted in the following        */
/*  ascending  sequence:                                                      */
/*  BranchNo, DiscountGrpNo                                                   */
/*----------------------------------------------------------------------------*/
int
pxConsTimeCollect :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxConsTimeCollect *that = (pxConsTimeCollect*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
               : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
        retval = (CustomerNo_ == that->CustomerNo_) ? 0
               : (CustomerNo_ > that->CustomerNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
void
pxConsTimeCollectList :: Clear()
{

    pxConsTimeCollect  *curp;
    pxConsTimeCollectListIter cursor(*this);
    while ( (curp = (pxConsTimeCollect*) ++cursor) != NULL )
    {
        cursor.Remove();
        delete curp;
    }
}

/*----------------------------------------------------------------------------*/
/*  Find in List: Depend on CustomeNo, TourId, ConsTime                       */
/*----------------------------------------------------------------------------*/
bool
pxConsTimeCollectList :: Find
(
    const long     CustomerNo,
    const nString& TourId,
    const nClock&  ConsTime
)
{
    bool retval = false;
    pxConsTimeCollect  *curp;
    pxConsTimeCollectListIter cursor(*this);
    while ( (curp = (pxConsTimeCollect*) ++cursor) != NULL )
    {
        if ( curp->CustomerNo() == CustomerNo &&
             curp->TourId()     == TourId     &&
             curp->ConsTime()   == ConsTime)
        {
            retval = true;
        }
    }
    return retval;
}
