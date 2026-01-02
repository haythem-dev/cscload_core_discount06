#include "pxrefnrcollect.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxRefnrCollect :: pxRefnrCollect
(
    const nString& KdAuftragBestellNr     // Refrencenumber
)
{
    KdAuftragBestellNr_ = KdAuftragBestellNr;
    RefNrCount_         = 0;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRefnrCollect :: pxRefnrCollect
(
    const pxRefnrCollect& src
)
{
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxRefnrCollect :: ~pxRefnrCollect()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxRefnrCollect&
pxRefnrCollect :: operator=( const pxRefnrCollect& src)
{
    KdAuftragBestellNr_ = src.KdAuftragBestellNr_;
    RefNrCount_         = src.RefNrCount_;
    return *this;
}
/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRangeCollec list objects being inserted in the following        */
/*  ascending  sequence:                                                      */
/*  BranchNo, DiscountGrpNo                                                   */
/*----------------------------------------------------------------------------*/
int
pxRefnrCollect :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxRefnrCollect *that = (pxRefnrCollect*)That;
    int retval = (KdAuftragBestellNr_ == that->KdAuftragBestellNr_) ? 0
                  : (KdAuftragBestellNr_ > KdAuftragBestellNr_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
void
pxRefnrCollectList :: Clear()
{

    pxRefnrCollect  *curp;
    pxRefnrCollectListIter cursor(*this);
    while ( (curp = (pxRefnrCollect*) ++cursor) != NULL )
    {
       cursor.Remove();
       delete curp;
    }
}

/*----------------------------------------------------------------------------*/
/*  Find KdAuftragBestellNr                                                   */
/*----------------------------------------------------------------------------*/
bool
pxRefnrCollectList :: Find
(
    const nString& KdAuftragBestellNr
)
{

    bool retval = false;
    pxRefnrCollect* curp;
    pxRefnrCollectListIter cursor(*this);
    while ( (curp = (pxRefnrCollect*) ++cursor) != NULL )
    {
       if ( curp->KdAuftragBestellNr() == KdAuftragBestellNr )
       {
          retval = true;
          break;
       }
    }
    return retval;
}
