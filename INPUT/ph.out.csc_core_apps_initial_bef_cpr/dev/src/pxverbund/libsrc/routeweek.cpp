/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxRouteWeek  methods.

REVISION HISTORY

10 May 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxrouteweek.hpp"
#include <pxdbxx.h>
#include <nntypes.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxRouteWeek :: pxRouteWeek
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRouteWeek :: pxRouteWeek
(
    const pxRouteWeek& src
)
    : pxDBRecord(((pxRouteWeek&) src) .Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTOURPLANWOCHE structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxRouteWeek :: pxRouteWeek
(
    pxSession   *session,
    tTOURPLANWOCHE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRouteWeek :: pxRouteWeek
(
    pxSession      *session,
    const short   FilialNr,
    const nString& TourId,                     // Read via string input
    const nString& TagesTyp,                   // Read via string input
    DBAccessMode   mode
)
    : pxDBRecord(session)
{
    Init();
    FilialNr_   = FilialNr;
    TourId_     = TourId;
    TagesTyp_   = TagesTyp;
    Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxRouteWeek :: ~pxRouteWeek()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTOURPLANWOCHE structure.       */
/*----------------------------------------------------------------------------*/
tTOURPLANWOCHE&
Assign
(
    tTOURPLANWOCHE&           dest,
    const pxRouteWeek&     src
)
{
    dest.FilialNr               = src.FilialNr_        ;
    dest.TourId[0] = ' ';
    src.TourId_.GetData(dest.TourId);
    dest.TagesTyp[0] = ' ';
    src.TagesTyp_.GetData( dest.TagesTyp,
                           (mSIZEOF(tTOURPLANTAGWOCHE, TagesTyp)) - 1 );
    dest.WeekDay                = src.WeekDay_;
    dest.LagRechTour            = src.LagRechTour_;
    dest.KarenzZeit             = src.KarenzZeit_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTOURPLANWOCHE structure to                 */
/*  a pxRouteWeek object.                                                  */
/*----------------------------------------------------------------------------*/
pxRouteWeek&
Assign
(
    pxRouteWeek&              dest,
    const tTOURPLANWOCHE&         src
)
{
    dest.FilialNr_              = src.FilialNr         ;
    dest.TourId_                = src.TourId           ;
    dest.TagesTyp_              = src.TagesTyp         ;
    dest.TagesTyp_.Strip();
    dest.WeekDay_               = src.WeekDay;
    dest.LagRechTour_           = src.LagRechTour;
    dest.KarenzZeit_            = src.KarenzZeit;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxRouteWeek :: Init()
{
    tTOURPLANWOCHE    record;
    memset(&record, 0 , sizeof(tTOURPLANWOCHE));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tTOURPLANWOCHE struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxRouteWeek&
pxRouteWeek :: operator=( const pxRouteWeek& src)
{
    tTOURPLANWOCHE record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTOURPLANWOCHE structure 'src' to                 */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxRouteWeek&
pxRouteWeek :: operator=( const tTOURPLANWOCHE& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxRouteWeek :: Get
(
    DBAccessMode mode
)

{
    tTOURPLANWOCHE record;
    memset(&record, 0, sizeof(tTOURPLANWOCHE));
    Assign(record, *this);              // easily gets keys
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tTOURPLANWOCHE struct
   /* else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_AQUOT_ENTRY_NOTFOUND, BranchNo_, CustomerNo_, ArticleNo_);
   */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxRouteWeek :: Put
(
)
{
    tTOURPLANWOCHE record;
    memset(&record, 0, sizeof(tTOURPLANWOCHE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tTOURPLANWOCHE));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxRouteWeek :: Delete
(
)
{
    tTOURPLANWOCHE record;
    memset(&record, 0, sizeof(tTOURPLANWOCHE));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxRouteWeek :: Read
(
    const void  *record
)
{
    return pxTourPlanWocheRead((tTOURPLANWOCHE*)record);
}

int
pxRouteWeek :: ReadLock
(
    const void  *record
)
{
    return pxTourPlanWocheReadLock((tTOURPLANWOCHE*)record);
}

int
pxRouteWeek :: Update
(
    const void  *record
)
{
    return pxTourPlanWocheUpdate((tTOURPLANWOCHE*)record);
}

int
pxRouteWeek :: Delete
(
    const void  *record
)
{
    return pxTourPlanWocheDelete((tTOURPLANWOCHE*)record);
}

int
pxRouteWeek :: Insert
(
    const void  *record
)
{
    return pxTourPlanWocheInsert((tTOURPLANWOCHE*)record);
}

int
pxRouteWeekList :: EndBrowse
(
    const int  cursorid
)
{
    return pxTourPlanWocheEndBrowse(cursorid);
}


int
pxRouteWeekList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxTourPlanWocheGetNext((tTOURPLANWOCHE*)record, cursorid);
}

int
pxRouteWeekList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxTourPlanWocheStartBrowse((tTOURPLANWOCHE*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRouteWeek list objects being inserted in the                    */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxRouteWeek :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxRouteWeek *that = (pxRouteWeek*)That;

    int retval = (TourId_ == that->TourId_) ? 0
                : (TourId_ > that->TourId_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRouteWeekList :: pxRouteWeekList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxRouteWeekList :: Select
(
    const short   FilialNr,
    const nString& TourId,
    const int     count_
)
{
    tTOURPLANWOCHE fil;
    memset(&fil, 0, sizeof(tTOURPLANWOCHE));  // zero out entire record buffer
    fil.FilialNr     = FilialNr;
    fil.TourId[0]    = ' ';
    TourId.GetData(fil.TourId);
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxRouteWeekList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxRouteWeek' object:
    pxRouteWeek *objectp = new pxRouteWeek(Session(), *(tTOURPLANWOCHE*) record);
    InsertAscending(objectp);
    return objectp;
}

