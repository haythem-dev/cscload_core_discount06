#include "pxcstbtm.hpp"
#include <pxdbxx.h>
#include <nntypes.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes :: pxCustBusinessTimes
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Construct an instance with default values.                                */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes :: pxCustBusinessTimes
(
    pxSession   *session,
    short      VZNr,
    long       KdNr
)
    : pxDBRecord(session)
{
    Init();
    VertriebszentrumNr_ = VZNr;
    KundenNr_ = KdNr;
    nDate today;
    WeekDay_ = today.GetDayOfWeek();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes :: pxCustBusinessTimes
(
    pxCustBusinessTimes& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDBETRIEBSENDE structure to construct this instance.                        */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes :: pxCustBusinessTimes
(
    pxSession   *session,
    tKDBETRIEBSENDE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes :: pxCustBusinessTimes
(
    pxSession   *session,
    short       VZNr,
    long        KdNr,
    short    WeekDay,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    VertriebszentrumNr_ = VZNr;
    KundenNr_           = KdNr;
    WeekDay_            = WeekDay;
    Get(mode);
}


/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes :: ~pxCustBusinessTimes()
{
//  delete subobjects;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDBETRIEBSENDE structure.     */
/*----------------------------------------------------------------------------*/
tKDBETRIEBSENDE&
Assign
(
          tKDBETRIEBSENDE&        dest,
    const pxCustBusinessTimes&    src
)
{
    // Copy native data types:
    dest.IDFNr           = src.IDFNr_;
    dest.VertriebszentrumNr = src.VertriebszentrumNr_;
    dest.KundenNr        = src.KundenNr_;
    dest.ZeitBeginAM     = src.ZeitBeginAM_.GetHHMMSS();
    dest.ZeitEndeAM      = src.ZeitEndeAM_.GetHHMMSS();
    dest.ZeitBeginPM     = src.ZeitBeginPM_.GetHHMMSS();
    dest.ZeitEndePM      = src.ZeitEndePM_.GetHHMMSS();
    dest.WeekDay         = src.WeekDay_;

    // nStrings:
    dest.TagesTyp[0] = ' ';
    src.TagesTyp_.GetData( dest.TagesTyp,
                           (mSIZEOF(tKDBETRIEBSENDE, TagesTyp)) - 1 );

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDBETRIEBSENDE structure                        */
/*  to a pxCustBusinessTimes object.                                          */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes&
Assign
(
          pxCustBusinessTimes&    dest,
    const tKDBETRIEBSENDE&        src
)
{
    // Copy native data types:
    dest.IDFNr_          = src.IDFNr;
    dest.VertriebszentrumNr_ = src.VertriebszentrumNr;
    dest.KundenNr_       = src.KundenNr;
    dest.ZeitBeginAM_    = src.ZeitBeginAM;
    dest.ZeitEndeAM_     = src.ZeitEndeAM;
    dest.ZeitBeginPM_    = src.ZeitBeginPM;
    dest.ZeitEndePM_     = src.ZeitEndePM;
    dest.WeekDay_        = src.WeekDay;

    // Strings:
    dest.TagesTyp_       = src.TagesTyp;
    dest.TagesTyp_.Strip();

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustBusinessTimes :: Init()
{
    tKDBETRIEBSENDE    record;
    memset(&record, 0 , sizeof(tKDBETRIEBSENDE));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDBETRIEBSENDE struct and then imported to self.                         */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes&
pxCustBusinessTimes :: operator=( const pxCustBusinessTimes& src)
{
    tKDBETRIEBSENDE record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDBETRIEBSENDE structure to this instance.      */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes&
pxCustBusinessTimes :: operator=( const tKDBETRIEBSENDE& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustBusinessTimes :: Get
(
    DBAccessMode mode
)

{
    tKDBETRIEBSENDE record;
    memset(&record, 0, sizeof(tKDBETRIEBSENDE));
    //record.IDFNr = IDFNr_;
    record.VertriebszentrumNr = VertriebszentrumNr_;
    record.KundenNr = KundenNr_;
    record.WeekDay  = WeekDay_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                         nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;           // import the data from tKDBETRIEBSENDE struct
    else if ( retval > cDBXR_NORMAL )
       DBCondition(nMessage(CMsgStream(),
                            CMSG_CST_BTM_NOTFOUND,
                            record.KundenNr,
                            record.TagesTyp),
                   CMSG_CST_NOBTIMES);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustBusinessTimes :: Put
(
)
{
    tKDBETRIEBSENDE record;
    memset(&record, 0, sizeof(tKDBETRIEBSENDE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDBETRIEBSENDE));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustBusinessTimes :: Read
(
    const void  *record
)
{
    //  pxFilialeRead in pxdbxx.h vereinbaren
    return pxKundeBetriebRead((tKDBETRIEBSENDE*)record);
}

int
pxCustBusinessTimes :: ReadLock
(
    const void  *record
)
{
    return pxKundeBetriebReadLock((tKDBETRIEBSENDE*)record);
}

int
pxCustBusinessTimes :: Update
(
    const void  *record
)
{
    return pxKundeBetriebUpdate((tKDBETRIEBSENDE*)record);
}

int
pxCustBusinessTimes :: Insert
(
    const void  *record
)
{
    return pxKundeBetriebInsert((tKDBETRIEBSENDE*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxArtBase list    */
/*  objects being inserted in the following ascending sequence: KdGruppe.     */
/*----------------------------------------------------------------------------*/
int
pxCustBusinessTimes :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustBusinessTimes *that = (pxCustBusinessTimes*)That;

    return (WeekDay_ == that->WeekDay_) ? 0
           : (WeekDay_ < that->WeekDay_) ? -1 : 1;
}

/*----------------------------------------------------------------------------*/
/*  Normal list constructor.                                                  */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimesList :: pxCustBusinessTimesList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection by the customer's IDFNr.                                 */
/*----------------------------------------------------------------------------*/
size_t
pxCustBusinessTimesList :: Select
(
    const short   VZNr,
    const long    KdNr,
    const int     count_
)
{
    tKDBETRIEBSENDE record;
    memset(&record, 0, sizeof(tKDBETRIEBSENDE));   // zero out record buffer
    //record.IDFNr = IDFNr;
    record.VertriebszentrumNr = VZNr;
    record.KundenNr = KdNr;

    nDBSelect(&record, cCRS_DEFAULT, count_);       // Do the selection
    Sort();                            // Sort list ascending by day numbers

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Finds and returns the entry pointer for the specified day number.         */
/*  Returns NULL if no matching entry exist.                                  */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes *
pxCustBusinessTimesList :: Find
(
    short WeekDay
)
{
    pxCustBusinessTimesListIter iter(*this);
    pxCustBusinessTimes         *entryp;

    // Browse thru list and search for entry with matching weekday name
    iter.Reset();
    while ( (entryp = (pxCustBusinessTimes *) ++iter) != NULL)
    {
       if ( entryp->WeekDay_ == WeekDay )     // Matching entry found
          return entryp;
    }

    return (pxCustBusinessTimes *) NULL;      // No match found
}

/*----------------------------------------------------------------------------*/
/*  Finds and returns the entry pointer for the specified nDate.              */
/*  Returns NULL if no matching entry exist.                                  */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes *
pxCustBusinessTimesList :: Find
(
    nDate date
)
{
     return Find( date.GetDayOfWeek() );   // call find with weekday's number
}

/*----------------------------------------------------------------------------*/
/*  Finds and returns the entry pointer for today's date.                     */
/*  Returns NULL if no matching entry exist.                                  */
/*----------------------------------------------------------------------------*/
pxCustBusinessTimes *
pxCustBusinessTimesList :: ThisDay
(
)
{
    return Find(nDate() );           // call find with today's date
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustBusinessTimesList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxCustBusinessTimes  ' object:
    pxCustBusinessTimes *objectp = new pxCustBusinessTimes(Session(), *(tKDBETRIEBSENDE*) record);
    Append(objectp);
    return objectp;
}

int
pxCustBusinessTimesList :: EndBrowse
(
    const int  cursorid
)
{
    return pxKundeBetriebEndBrowse(cursorid);
}

int
pxCustBusinessTimesList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxKundeBetriebGetNext((tKDBETRIEBSENDE*)record, cursorid);
}

int
pxCustBusinessTimesList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxKundeBetriebStartBrowse((tKDBETRIEBSENDE*)keys, cursorid);
}
