/*(c)
 ********************* PHARMX Customer Order Entry Server *********************



Implementation of class pxOrderPosEvent methods.

REVISION HISTORY

15 Oct 2014 V1.00 REV 00 written by Ysbrand Bouma.

*/

#include "pxorderposevent.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxorder.hpp"
#include "pxitem.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderPosEvent :: pxOrderPosEvent
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Use a reference to the current Item  to construct this instance.          */
/*  A valid  EventType may be specified as event to log,                      */
/*  The default is pxOrderPosEvent::LeaveAsis. We try to determine the event          */
/*  automatically in that case.                                               */
/*----------------------------------------------------------------------------*/
pxOrderPosEvent :: pxOrderPosEvent
(
    pxOrderItem&    Item,
    pxOrderPosEvent::EventType PosEreignisArt
)
    : pxDBRecord(Item.Session())
{
    Init();
    PosEreignisArt_   = PosEreignisArt;
    KdAuftragNr_      = Item.KdAuftragNr();
    PosNr_            = Item.PosNr();
    SendId_           = Item.Order().FirstTransPos() + 1;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderPosEvent :: pxOrderPosEvent
(
    pxOrderPosEvent& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGPOSEREIGNIS structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxOrderPosEvent :: pxOrderPosEvent
(
    pxSession   *session,
    tKDAUFTRAGPOSEREIGNIS& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderPosEvent :: pxOrderPosEvent
(
    pxSession   *session,
    long KdAuftragNr,
    long PosNr,
    nTime DateTime,
    pxOrderPosEvent::EventType Event,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_   = KdAuftragNr;
    PosNr_         = PosNr;
    DateTime_      = DateTime;
    PosEreignisArt_ = Event;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderPosEvent :: ~pxOrderPosEvent()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGPOSEREIGNIS structure.  */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGPOSEREIGNIS&
Assign
(
          tKDAUFTRAGPOSEREIGNIS&  dest,
    const pxOrderPosEvent&        src
)
{
    dest.Datum           = (src.Date()).GetYYYYMMDD();
    dest.KdAuftragNr     = src.KdAuftragNr_;
    dest.SendId          = src.SendId_;
    dest.PosEreignisArt  = (short)src.PosEreignisArt_;
    dest.PosNr           = src.PosNr_;
    dest.UhrZeit         = (src.Clock()).GetHHMMSSmmm();

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGPOSEREIGNIS structure                  */
/*  to a pxOrderPosEvent object.                                              */
/*----------------------------------------------------------------------------*/
pxOrderPosEvent&
Assign
(
          pxOrderPosEvent&        dest,
    const tKDAUFTRAGPOSEREIGNIS&  src
)
{
    dest.KdAuftragNr_    = src.KdAuftragNr;
    dest.PosNr_          = src.PosNr;
    dest.SendId_         = src.SendId;
    nDate    date(src.Datum);
    nClock   clock(src.UhrZeit/1000, src.UhrZeit%1000);
    dest.DateTime_ = nTime((int)date.GetYear(),
                           (int)date.GetMonth(),
                           (int)date.GetDay(),
                           (int)clock.GetHours(),
                           (int)clock.GetMinutes(),
                           (int)clock.GetSeconds(),
                           (int)clock.GetMsecs() );
    dest.PosEreignisArt_  = (pxOrderPosEvent::EventType) src.PosEreignisArt;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderPosEvent :: Init()
{
    tKDAUFTRAGPOSEREIGNIS    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGPOSEREIGNIS));
    Assign(*this, record);
    DateTime_ = nTime();
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGPOSEREIGNIS struct and then imported to self.                      */
/*----------------------------------------------------------------------------*/
pxOrderPosEvent&
pxOrderPosEvent :: operator=( const pxOrderPosEvent& src)
{
    tKDAUFTRAGPOSEREIGNIS record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGPOSEREIGNIS structure to this instance.   */
/*----------------------------------------------------------------------------*/
pxOrderPosEvent&
pxOrderPosEvent :: operator=( const tKDAUFTRAGPOSEREIGNIS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderPosEvent :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGPOSEREIGNIS record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSEREIGNIS));
    Assign(record,*this);

    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;           // import the data from tKDAUFTRAGPOSEREIGNIS struct
    /*else if ( retval > cDBXR_NORMAL )
        DBCondition(nMessage(CMsgStream(),
                             CMSG_ORD_EVENT_NOTFOUND,
                             record.KdAuftragNr,
                             record.Datum,
                             record.Zeit),
                    CMSG_ORD_EVENT_NOTFOUND);
    */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderPosEvent :: Put
(
)
{
    tKDAUFTRAGPOSEREIGNIS record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSEREIGNIS));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGPOSEREIGNIS));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOrderPosEvent :: Read
(
    const void  *record
)
{
    return pxOrderPosEventRead((tKDAUFTRAGPOSEREIGNIS*)record);
}

int
pxOrderPosEvent :: ReadLock
(
    const void  *record
)
{
    return pxOrderPosEventReadLock((tKDAUFTRAGPOSEREIGNIS*)record);
}

int
pxOrderPosEvent :: Update
(
    const void  *record
)
{
    return pxOrderPosEventUpdate((tKDAUFTRAGPOSEREIGNIS*)record);
}

int
pxOrderPosEvent :: Insert
(
    const void  *record
)
{
    return pxOrderPosEventInsert((tKDAUFTRAGPOSEREIGNIS*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*----------------------------------------------------------------------------*/
int
pxOrderPosEvent :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOrderPosEvent *that = (pxOrderPosEvent*)That;
    int retval;

    retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
           : (KdAuftragNr_ < that->KdAuftragNr_ ? -1 : 1);
    if (retval == 0)
    {
        retval = (DateTime_ == that->DateTime_) ? 0
               : (DateTime_ < that->DateTime_ ? -1 : 1);
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderPosEventList :: pxOrderPosEventList
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
pxOrderPosEventList :: Select
(
    const int     count_
)
{
    tKDAUFTRAGPOSEREIGNIS record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSEREIGNIS));    // zero out record buffer

    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using KdAuftragNr.                                   */
/*----------------------------------------------------------------------------*/
size_t
pxOrderPosEventList :: Select
(
    const long    KdAuftragNr,
    const int     count_
)
{
    tKDAUFTRAGPOSEREIGNIS record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSEREIGNIS));  // zero out record buffer
    record.KdAuftragNr = KdAuftragNr;

    return Select(&record, count_);
}

/*----------------------------------------------------------------------------*/
/*  Select events matching 'KdAuftragNr' and event code 'ec'.                 */
/*----------------------------------------------------------------------------*/
size_t
pxOrderPosEventList :: Select
(
    const long    KdAuftragNr,         // order number
    const pxOrderPosEvent::EventType pec,  // Pos event code
    const int     count_
)
{
    tKDAUFTRAGPOSEREIGNIS record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSEREIGNIS));  // zero out record buffer
    record.KdAuftragNr = KdAuftragNr;
    record.PosEreignisArt = static_cast<short>(pec);

    Select(&record, count_);             // select events for this order
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Do the selection with default where clause based upon the values stored   */
/*  in the record structure.                                                  */
/*----------------------------------------------------------------------------*/
size_t
pxOrderPosEventList :: Select
(
    const tKDAUFTRAGPOSEREIGNIS   *recordp,
    const int                 count_
)
{
    int cursorid = cCRS_DEFAULT;
    nDBSelect(recordp, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderPosEventList :: AddToList
(
    const void  *recordp,
    const int  /* row */
)
{
    // construct new 'pxOrderPosEvent  ' object:
    pxOrderPosEvent *objectp = new pxOrderPosEvent(Session(), *(tKDAUFTRAGPOSEREIGNIS*) recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxOrderPosEventList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOrderPosEventEndBrowse(cursorid);
}

int
pxOrderPosEventList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxOrderPosEventGetNext((tKDAUFTRAGPOSEREIGNIS*)recordp, cursorid);
}

int
pxOrderPosEventList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOrderPosEventStartBrowse((tKDAUFTRAGPOSEREIGNIS*)keys, cursorid);
}
