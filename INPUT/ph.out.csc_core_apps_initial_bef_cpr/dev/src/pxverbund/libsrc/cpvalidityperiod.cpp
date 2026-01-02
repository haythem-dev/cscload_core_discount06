#include "pxcpvalidityperiod.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCPValidityPeriod :: pxCPValidityPeriod
(
    pxSession *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCPValidityPeriod :: pxCPValidityPeriod
(
    pxCPValidityPeriod& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCPVALIDITYPERIOD structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxCPValidityPeriod :: pxCPValidityPeriod
(
    pxSession   *session,
    tCPVALIDITYPERIOD& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCPValidityPeriod :: pxCPValidityPeriod
(
    pxSession *session,
   const pxCPValidityPeriod *src
)
    : pxDBRecord(session)
{
    Init();

    if (src != NULL)
        (*this) = *src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCPValidityPeriod :: ~pxCPValidityPeriod()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCPVALIDITYPERIOD structure.   */
/*----------------------------------------------------------------------------*/
tCPVALIDITYPERIOD&
Assign
(
    tCPVALIDITYPERIOD&           dest,
    const pxCPValidityPeriod&    src
)
{
    dest.Article_No_Pack           = src.ArticleNoPack_           ;
    dest.DateFrom                  = src.DateFrom_.GetYYYYMMDD()  ;
    dest.DateTo                    = src.DateTo_.GetYYYYMMDD()    ;
    dest.Type                      = src.Type_                    ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCPVALIDITYPERIOD structure to             */
/*  a pxCPValidityPeriod object.                                              */
/*----------------------------------------------------------------------------*/
pxCPValidityPeriod&
Assign
(
    pxCPValidityPeriod&         dest,
    const tCPVALIDITYPERIOD&    src
)
{
    dest.ArticleNoPack_           = src.Article_No_Pack          ;
    dest.DateFrom_                = nDate(src.DateFrom)          ;
    dest.DateTo_                  = nDate(src.DateTo)            ;
    dest.Type_                    = src.Type                     ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCPValidityPeriod :: Init()
{
    tCPVALIDITYPERIOD record;
    memset(&record, 0, sizeof(tCPVALIDITYPERIOD));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCPVALIDITYPERIOD struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxCPValidityPeriod&
pxCPValidityPeriod :: operator=( const pxCPValidityPeriod& src)
{
    tCPVALIDITYPERIOD record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCPVALIDITYPERIOD structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCPValidityPeriod&
pxCPValidityPeriod :: operator=( const tCPVALIDITYPERIOD& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCPValidityPeriod list objects being inserted in the             */
/*  following ascending sequence:                                             */
/*----------------------------------------------------------------------------*/
int
pxCPValidityPeriod :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCPValidityPeriod *that = (pxCPValidityPeriod*)That;
    int retval = (ArticleNoPack_ == that->ArticleNoPack_) ? 0
               : (ArticleNoPack_ > that->ArticleNoPack_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCPValidityPeriodList :: pxCPValidityPeriodList
(
    pxSession *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCPValidityPeriodList :: Select
(
    const int count_
)
{
    tCPVALIDITYPERIOD fil;
    memset(&fil, 0, sizeof(tCPVALIDITYPERIOD));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via KdAuftragNr, PosNr                        */
/*----------------------------------------------------------------------------*/
size_t
pxCPValidityPeriodList :: Select
(
    const long    ArticleNoPack,
    const int     count_
)
{
    tCPVALIDITYPERIOD fil;
    memset(&fil, 0, sizeof(tCPVALIDITYPERIOD));  // zero out entire record buffer
    fil.Article_No_Pack   = ArticleNoPack;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCPValidityPeriodList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxCPValidityPeriod' object:
    pxCPValidityPeriod *objectp = new pxCPValidityPeriod(Session(), *(tCPVALIDITYPERIOD*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Reduce a list of pxCPValidityPeriodList entries to contain only valid     */
/*  entries.                                                                  */
/*----------------------------------------------------------------------------*/
int
pxCPValidityPeriodList :: ReduceToValidEntries
(
)
{
    pxCPValidityPeriod  *entryp;        // ptr to list entry
    nDate          today;               // this days date
    pxCPValidityPeriodListIter  cursor(*this);  // define an iterator
    while ( (entryp = (pxCPValidityPeriod*) ++cursor) != NULL )
    {
        if ( (today > entryp->DateTo_ || today < entryp->DateFrom_))
            delete cursor.Remove();       // entryr expired
        if ( entryp->IsNoActivity() )     // type Display(German application
            delete cursor.Remove();       // entryr expired
    }
    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCPValidityPeriodList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCPValidityPeriodEndBrowse(cursorid);
}

int
pxCPValidityPeriodList :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxCPValidityPeriodGetNext((tCPVALIDITYPERIOD*)record, cursorid);
}

int
pxCPValidityPeriodList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    return pxCPValidityPeriodStartBrowse((tCPVALIDITYPERIOD*)keys, cursorid);
}
