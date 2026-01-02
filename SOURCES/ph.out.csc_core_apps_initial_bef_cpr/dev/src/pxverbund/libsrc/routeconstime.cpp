/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxRouteConsTime  methods.

REVISION HISTORY

27 April 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxrouteconstime.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxRouteConsTime :: pxRouteConsTime
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
pxRouteConsTime :: pxRouteConsTime
(
    const pxRouteConsTime& src
)
    : pxDBRecord(((pxRouteConsTime&) src) .Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTOURCONSTIME structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxRouteConsTime :: pxRouteConsTime
(
    pxSession   *session,
    tTOURCONSTIME& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRouteConsTime :: pxRouteConsTime
(
    pxSession      *session,
    const short   FilialNr,
    const nString& TourId,                     // Read via string input
    const nDate&   DatumKommi,
    const nClock&  ConsTime,
    DBAccessMode   mode
)
    : pxDBRecord(session)
{
    Init();
    FilialNr_   = FilialNr;
    TourId_     = TourId;
    DatumKommi_ = DatumKommi;
    ConsTime_   = ConsTime;
    Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxRouteConsTime :: ~pxRouteConsTime()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTOURCONSTIME structure.       */
/*----------------------------------------------------------------------------*/
tTOURCONSTIME&
Assign
(
    tTOURCONSTIME&           dest,
    const pxRouteConsTime&     src
)
{
    dest.FilialNr               = src.FilialNr_        ;
    dest.TourId[0] = ' ';
    src.TourId_.GetData(dest.TourId);
    dest.DatumKommi             = src.DatumKommi_.GetYYYYMMDD();
    dest.ConsTime               = src.ConsTime_.GetHHMMSS();
    dest.ProcessState           = src.ProcessState_     ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTOURCONSTIME structure to                 */
/*  a pxRouteConsTime object.                                                  */
/*----------------------------------------------------------------------------*/
pxRouteConsTime&
Assign
(
    pxRouteConsTime&              dest,
    const tTOURCONSTIME&         src
)
{
    dest.FilialNr_              = src.FilialNr         ;
    dest.TourId_                = src.TourId           ;
    dest.DatumKommi_            = nDate(src.DatumKommi);
    dest.ConsTime_              = src.ConsTime         ;
    dest.ProcessState_          = src.ProcessState     ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxRouteConsTime :: Init()
{
    tTOURCONSTIME    record;
    memset(&record, 0 , sizeof(tTOURCONSTIME));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tTOURCONSTIME struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxRouteConsTime&
pxRouteConsTime :: operator=( const pxRouteConsTime& src)
{
    tTOURCONSTIME record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTOURCONSTIME structure 'src' to                 */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxRouteConsTime&
pxRouteConsTime :: operator=( const tTOURCONSTIME& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxRouteConsTime :: Get
(
    DBAccessMode mode
)

{
    tTOURCONSTIME record;
    memset(&record, 0, sizeof(tTOURCONSTIME));
    Assign(record, *this);              // easily gets keys
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tTOURCONSTIME struct
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
pxRouteConsTime :: Put
(
)
{
    tTOURCONSTIME record;
    memset(&record, 0, sizeof(tTOURCONSTIME));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tTOURCONSTIME));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxRouteConsTime :: Delete
(
)
{
    tTOURCONSTIME record;
    memset(&record, 0, sizeof(tTOURCONSTIME));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxRouteConsTime :: Read
(
    const void  *record
)
{
    return pxTourConsTimeRead((tTOURCONSTIME*)record);
}

int
pxRouteConsTime :: ReadLock
(
    const void  *record
)
{
    return pxTourConsTimeReadLock((tTOURCONSTIME*)record);
}

int
pxRouteConsTime :: Update
(
    const void  *record
)
{
    return pxTourConsTimeUpdate((tTOURCONSTIME*)record);
}

int
pxRouteConsTime :: Delete
(
    const void  *record
)
{
    return pxTourConsTimeDelete((tTOURCONSTIME*)record);
}

int
pxRouteConsTime :: Insert
(
    const void  *record
)
{
    return pxTourConsTimeInsert((tTOURCONSTIME*)record);
}

int
pxRouteConsTimeList :: EndBrowse
(
    const int  cursorid
)
{
    return pxTourConsTimeEndBrowse(cursorid);
}


int
pxRouteConsTimeList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxTourConsTimeGetNext((tTOURCONSTIME*)record, cursorid);
}

int
pxRouteConsTimeList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxTourConsTimeStartBrowse((tTOURCONSTIME*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRouteConsTime list objects being inserted in the                */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxRouteConsTime :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxRouteConsTime *that = (pxRouteConsTime*)That;

    int retval = (TourId_ == that->TourId_) ? 0
                : (TourId_ > that->TourId_ ? 1 : -1);

    if (retval == 0 )
       retval = (DatumKommi_ == that->DatumKommi_) ? 0
                : (DatumKommi_ > that->DatumKommi_ ? 1 : -1);

    if (retval == 0 )
       retval = (ConsTime_ == that->ConsTime_) ? 0
                : (ConsTime_ > that->ConsTime_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRouteConsTimeList :: pxRouteConsTimeList
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
pxRouteConsTimeList :: Select
(
    const short   FilialNr,
    const nString& TourId,
    const nDate&   DatumKommi,
    const int     count_
)
{
    tTOURCONSTIME fil;
    memset(&fil, 0, sizeof(tTOURCONSTIME));  // zero out entire record buffer
    fil.FilialNr     = FilialNr;
    fil.TourId[0]    = ' ';
    TourId.GetData(fil.TourId);
    fil.DatumKommi   = DatumKommi.GetYYYYMMDD();
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxRouteConsTimeList :: Select
(
    const short   FilialNr,
    const nDate&   DatumKommi,
    const nClock&  ConsTime,
    const int     count_
)
{
    tTOURCONSTIME fil;
    memset(&fil, 0, sizeof(tTOURCONSTIME));  // zero out entire record buffer
    fil.FilialNr      = FilialNr;
    fil.DatumKommi   = DatumKommi.GetYYYYMMDD();
    fil.ConsTime      = (ConsTime.GetHHMMSS()/100);
    int cursorid     = cCRSTCONSTIME_CTIMEPSTATE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxRouteConsTimeList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxRouteConsTime' object:
    pxRouteConsTime *objectp = new pxRouteConsTime(Session(), *(tTOURCONSTIME*) record);
    InsertAscending(objectp);
    return objectp;
}

