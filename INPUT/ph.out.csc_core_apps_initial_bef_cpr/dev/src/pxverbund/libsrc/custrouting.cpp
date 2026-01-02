#include "pxcustrouting.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "tourutil.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustRouting :: pxCustRouting
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
pxCustRouting :: pxCustRouting
(
    pxCustRouting& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERROUTING structure to construct this instance.                */
/*----------------------------------------------------------------------------*/
pxCustRouting :: pxCustRouting
(
    pxSession   *session,
    tCUSTOMERROUTING& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustRouting :: pxCustRouting
(
    pxSession    *session,
    long        CustomerNo,          // this type
    short       BranchNo,            // Read via this type and
    const nClock&      TimeFrom,
    short       WeekDay,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    CustomerNo_  = CustomerNo;
    BranchNo_    = BranchNo;
    TimeFrom_    = TimeFrom;
    WeekDay_     = WeekDay;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustRouting :: ~pxCustRouting()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCUSTOMERROUTING structure.    */
/*----------------------------------------------------------------------------*/
tCUSTOMERROUTING&
Assign
(
    tCUSTOMERROUTING&           dest,
    const pxCustRouting&       src
)
{
    dest.CustomerNo                = src.CustomerNo_                         ;
    dest.BranchNo                  = src.BranchNo_                           ;
    dest.TimeFrom                  = src.TimeFrom_.GetHHMMSS()               ;
    dest.TimeTo                    = src.TimeTo_.GetHHMMSS()                 ;
    dest.DestBranchNo              = src.DestBranchNo_                       ;
    dest.DayOfWeek[0] = ' ';
    src.DayOfWeek_.GetData(dest.DayOfWeek);
    dest.WeekDay                   = src.WeekDay_                            ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCUSTOMERROUTING structure to              */
/*  a pxCustRouting object.                                                   */
/*----------------------------------------------------------------------------*/
pxCustRouting&
Assign
(
    pxCustRouting&              dest,
    const tCUSTOMERROUTING&    src
)
{
    dest.BranchNo_                 = src.BranchNo                            ;
    dest.CustomerNo_               = src.CustomerNo                          ;
    dest.TimeFrom_                 = src.TimeFrom*100                        ;
    dest.TimeTo_                   = src.TimeTo*100                          ;
    dest.DestBranchNo_             = src.DestBranchNo                        ;
    dest.DayOfWeek_                = src.DayOfWeek                           ;
    dest.WeekDay_                  = src.WeekDay                             ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustRouting :: Init()
{
    tCUSTOMERROUTING    record;
    memset(&record, 0 , sizeof(tCUSTOMERROUTING));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCUSTOMERROUTING struct and then imported to self.                        */
/*----------------------------------------------------------------------------*/
pxCustRouting&
pxCustRouting :: operator=( const pxCustRouting& src)
{
    tCUSTOMERROUTING record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCUSTOMERROUTING structure 'src' to              */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCustRouting&
pxCustRouting :: operator=( const tCUSTOMERROUTING& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustRouting :: Get
(
    DBAccessMode mode
)

{
    tCUSTOMERROUTING record;
    memset(&record, 0, sizeof(tCUSTOMERROUTING));
    record.BranchNo      = BranchNo_;
    record.CustomerNo    = CustomerNo_;
    record.TimeFrom      = TimeFrom_.GetHHMMSS();
    record.WeekDay       = WeekDay_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tCUSTOMERROUTING struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_CUSTROUTING_ENTRY_NOTFOUND,BranchNo_,CustomerNo_);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustRouting :: Put
(
)
{
    tCUSTOMERROUTING record;
    memset(&record, 0, sizeof(tCUSTOMERROUTING));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCUSTOMERROUTING));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxCustRouting :: Delete
(
)
{
    tCUSTOMERROUTING record;
    memset(&record, 0, sizeof(tCUSTOMERROUTING));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustRouting :: Read
(
    const void  *record
)
{
    return pxCustRoutingRead((tCUSTOMERROUTING*)record);
}

int
pxCustRouting :: ReadLock
(
    const void  *record
)
{
    return pxCustRoutingReadLock((tCUSTOMERROUTING*)record);
}

int
pxCustRouting :: Update
(
    const void  *record
)
{
    return pxCustRoutingUpdate((tCUSTOMERROUTING*)record);
}

int
pxCustRouting :: Delete
(
    const void  *record
)
{
    return pxCustRoutingDelete((tCUSTOMERROUTING*)record);
}

int
pxCustRouting :: Insert
(
    const void  *record
)
{
    return pxCustRoutingInsert((tCUSTOMERROUTING*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCustRouting list objects being inserted in the                  */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxCustRouting :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustRouting *that = (pxCustRouting*)That;
    int retval = (CustomerNo_ == that->CustomerNo_) ? 0
                : (CustomerNo_ > that->CustomerNo_ ? 1 : -1);
    if ( retval == 0 )
       retval = (TimeFrom_ == that->TimeFrom_) ? 0
                : (TimeFrom_ > that->TimeFrom_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/* Checkt current time against entry timeinwindow                             */
/* Returns true if it does fit, otherwise false                             */
/*----------------------------------------------------------------------------*/
bool
pxCustRouting :: TimeInWindow
(
)
{
    nClock ctime;         // current time
    nClock from = TimeFrom();
    nClock to   = TimeTo();
    return (ctime > TimeFrom() && ctime < TimeTo());
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustRoutingList :: pxCustRoutingList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
bool pxCustRoutingList::hasRoutingStartingToday( const short BranchNo, const long CustomerNo, const short DestinationBranchNo )
{
    int count_ = 1;
    nTime now;
    tCUSTOMERROUTING data;
    memset(&data, 0, sizeof(tCUSTOMERROUTING));
    
    data.BranchNo = BranchNo;
    data.CustomerNo = CustomerNo;
    data.DestBranchNo = DestinationBranchNo;
    data.TimeFrom = TourUtil::getLongTime( now );
    data.WeekDay = TourUtil::getCurrentWeekday();

    int cursorid= cCRSCUSTOMERROUTING_HASROUTINGSTARTINGTODAY;
    nDBSelect(&data, cursorid, count_);
    if( Entries() > 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*----------------------------------------------------------------------------*/

size_t
pxCustRoutingList :: SelectRoutingBackward
(
    const long CustomerNo,
    const short DestinationBranchNo
)
{
    nTime now;
    tCUSTOMERROUTING data;
    memset(&data, 0, sizeof(tCUSTOMERROUTING));
    
    data.CustomerNo = CustomerNo;
    data.DestBranchNo = DestinationBranchNo;
    data.TimeFrom = TourUtil::getLongTime( now );
    data.WeekDay = TourUtil::getCurrentWeekday();

    nDBSelect(&data, cCRSCUSTOMERROUTING_ISROUTED, cDEFAULT);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCustRoutingList :: Select
(
    const int     count_
)
{
    tCUSTOMERROUTING fil;
    memset(&fil, 0, sizeof(tCUSTOMERROUTING));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via KdAuftragNr, PosNr                        */
/*----------------------------------------------------------------------------*/
size_t
pxCustRoutingList :: Select
(
    const long    CustomerNo,
    const short   BranchNo,
    const short   WeekDay,
    const int     count_
)
{
    tCUSTOMERROUTING fil;
    memset(&fil, 0, sizeof(tCUSTOMERROUTING));  // zero out entire record buffer
    fil.CustomerNo   = CustomerNo;
    fil.BranchNo     = BranchNo;
    fil.WeekDay      = WeekDay;
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustRoutingList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxCustRouting' object:
    pxCustRouting *objectp = new pxCustRouting(Session(), *(tCUSTOMERROUTING*) record);
    InsertAscending(objectp);
    return objectp;
}

int
pxCustRoutingList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCustRoutingEndBrowse(cursorid);
}


int
pxCustRoutingList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxCustRoutingGetNext((tCUSTOMERROUTING*)record, cursorid);
}

int
pxCustRoutingList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxCustRoutingStartBrowse((tCUSTOMERROUTING*)keys, cursorid);
}

