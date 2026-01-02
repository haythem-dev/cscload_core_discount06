#include "pxordevt.hpp"
#include <pxdbxx.h>
#include <nntypes.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderEvent :: pxOrderEvent
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Use a reference to the current order to construct this instance.          */
/*  A valid customer order state may be specified as event to log,            */
/*  The default is pxOrder::LeaveAsis. We try to determine the event          */
/*  automatically in that case.                                               */
/*----------------------------------------------------------------------------*/
pxOrderEvent :: pxOrderEvent
(
    pxOrder&    Order,
    Order::States Event
)
    : pxDBRecord(Order.Session())
{
    Init();
    Event_ = Event;
    KdAuftragNr_ = Order.KdAuftragNr();

    while ( Event_ == Order::LeaveAsIs )  // do not log the null state
    {
        if ( Order.IsProtected() )
        {
            Event_ = Order::Protected;
            break;
        }
        if ( Order.IsCancelled() )
        {
            Event_ = Order::Cancelled;
            EventCode_ = Order.EventCode();
            break;
        }
        if ( Order.IsInvoiced() )
        {
            Event_ = Order::Invoiced;
            break;
        }
        if ( Order.IsShipmentClosed() )
        {
            Event_ = Order::ShipmentClosed;
            break;
        }
        if ( Order.IsShipmentInProgress() )
        {
            Event_ = Order::ShipmentInProgress;
            break;
        }
        if ( Order.IsEntryClosed() )
        {
            Event_ = Order::EntryClosed;
            break;
        }
        if ( Order.IsEntryDeferred() )
        {
            Event_      = Order::EntryDeferred;
            EventCode_  = Order.EventCode();
            break;
        }
        if ( Order.IsUpdateInProgress() )
        {
            Event_ = Order::UpdateInProgress;
            break;
        }

        Event_ = Order::EntryInProgress;
        break;
    }
    if(Order.IsNoDebtLimitCheck())
    {
        if(Event_ == Order::EntryClosed) Event_ = Order::EntryClosedKL;
        else if(Event_ == Order::Cancelled) Event_ = Order::CancelledKL;
    }
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderEvent :: pxOrderEvent
(
    pxOrderEvent& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGEREIGNIS structure to construct this instance.              */
/*----------------------------------------------------------------------------*/
pxOrderEvent :: pxOrderEvent
(
    pxSession   *session,
    tKDAUFTRAGEREIGNIS& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderEvent :: pxOrderEvent
(
    pxSession   *session,
    long KdAuftragNr,
    nTime DateTime,
    Order::States Event,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_   = KdAuftragNr;
    DateTime_      = DateTime;
    Event_         = Event;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderEvent :: ~pxOrderEvent()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGEREIGNIS structure.  */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGEREIGNIS&
Assign
(
          tKDAUFTRAGEREIGNIS&  dest,
    const pxOrderEvent&        src
)
{
    dest.KdAuftragNr     = src.KdAuftragNr_;
    dest.Datum      = (src.Date()).GetYYYYMMDD();
    dest.Zeit      = (src.Clock()).GetHHMMSSmmm();
    dest.EreignisArt     = (short)src.Event_;
    dest.PersonalNr      = src.PersonalNr_;
    dest.GeraetName[0] = ' ';
    src.GeraetName_.GetData(dest.GeraetName, (mSIZEOF(tKDAUFTRAGEREIGNIS, GeraetName)) - 1);
    dest.FilialNr         = src.FilialNr_;
    dest.EventCode        = static_cast<short>(src.EventCode_);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGEREIGNIS structure                     */
/*  to a pxOrderEvent object.                                                 */
/*----------------------------------------------------------------------------*/
pxOrderEvent&
Assign
(
          pxOrderEvent&        dest,
    const tKDAUFTRAGEREIGNIS&  src
)
{
    dest.KdAuftragNr_    = src.KdAuftragNr;
    nDate    date(src.Datum);
    nClock   clock(src.Zeit/1000, src.Zeit%1000);
    dest.DateTime_ = nTime((int)date.GetYear(),
                           (int)date.GetMonth(),
                           (int)date.GetDay(),
                           (int)clock.GetHours(),
                           (int)clock.GetMinutes(),
                           (int)clock.GetSeconds(),
                           (int)clock.GetMsecs() );
    dest.Event_          = (Order::States)src.EreignisArt;
    dest.PersonalNr_     = src.PersonalNr;
    dest.GeraetName_     = src.GeraetName;
    dest.GeraetName_.Strip();
    dest.FilialNr_        = src.FilialNr;
    dest.EventCode_       = static_cast<pxEventReason::EventCodes>(src.EventCode);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderEvent :: Init()
{
    tKDAUFTRAGEREIGNIS    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGEREIGNIS));
    Assign(*this, record);
    DateTime_ = nTime();
    GeraetName_ = Session()->Device()->Name();
    PersonalNr_ = Session()->PersonnelNo();
    Event_ = Order::EntryInProgress;
    FilialNr_   = Session()->UsersFilialNr();
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGEREIGNIS struct and then imported to self.                      */
/*----------------------------------------------------------------------------*/
pxOrderEvent&
pxOrderEvent :: operator=( const pxOrderEvent& src)
{
    tKDAUFTRAGEREIGNIS record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGEREIGNIS structure to this instance.   */
/*----------------------------------------------------------------------------*/
pxOrderEvent&
pxOrderEvent :: operator=( const tKDAUFTRAGEREIGNIS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderEvent :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGEREIGNIS record;
    memset(&record, 0, sizeof(tKDAUFTRAGEREIGNIS));
    Assign(record,*this);

    int retval = ( mode == cDBGET_FORUPDATE ) ?
                         nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;           // import the data from tKDAUFTRAGEREIGNIS struct
    else if ( retval > cDBXR_NORMAL )
        DBCondition(nMessage(CMsgStream(),
                             CMSG_ORD_EVENT_NOTFOUND,
                             record.KdAuftragNr,
                             record.Datum,
                             record.Zeit),
                    CMSG_ORD_EVENT_NOTFOUND);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderEvent :: Put
(
)
{
    tKDAUFTRAGEREIGNIS record;
    memset(&record, 0, sizeof(tKDAUFTRAGEREIGNIS));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGEREIGNIS));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOrderEvent :: Read
(
    const void  *record
)
{
    return pxAuftragEreignisRead((tKDAUFTRAGEREIGNIS*)record);
}

int
pxOrderEvent :: ReadLock
(
    const void  *record
)
{
    return pxAuftragEreignisReadLock((tKDAUFTRAGEREIGNIS*)record);
}

int
pxOrderEvent :: Update
(
    const void  *record
)
{
    return pxAuftragEreignisUpdate((tKDAUFTRAGEREIGNIS*)record);
}

int
pxOrderEvent :: Insert
(
    const void  *record
)
{
    return pxAuftragEreignisInsert((tKDAUFTRAGEREIGNIS*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*----------------------------------------------------------------------------*/
int
pxOrderEvent :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOrderEvent *that = (pxOrderEvent*)That;
    int retval;

    retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
           : (KdAuftragNr_ < that->KdAuftragNr_ ? -1 : 1);
    if (retval == 0)
    {
        retval = (DateTime_ == that->DateTime_) ? 0
               : (DateTime_ < that->DateTime_ ? -1 : 1);
        if (retval == 0)
        {
            retval = (Event_ == that->Event_) ? 0
                   : (Event_ < that->Event_ ? -1 : 1);
        }
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderEventList :: pxOrderEventList
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
pxOrderEventList :: Select
(
    const int     count_
)
{
    tKDAUFTRAGEREIGNIS record;
    memset(&record, 0, sizeof(tKDAUFTRAGEREIGNIS));    // zero out record buffer

    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using KdAuftragNr.                                   */
/*----------------------------------------------------------------------------*/
size_t
pxOrderEventList :: Select
(
    const long    KdAuftragNr,
    const int     count_
)
{
    tKDAUFTRAGEREIGNIS record;
    memset(&record, 0, sizeof(tKDAUFTRAGEREIGNIS));  // zero out record buffer
    record.KdAuftragNr = KdAuftragNr;

    return Select(&record, count_);
}

/*----------------------------------------------------------------------------*/
/*  Select events matching 'KdAuftragNr' and event code 'ec'.                 */
/*----------------------------------------------------------------------------*/
size_t
pxOrderEventList :: Select
(
    const long    KdAuftragNr,         // order number
    const Order::States ec,            // event code
    const int     count_
)
{
    tKDAUFTRAGEREIGNIS record;
    memset(&record, 0, sizeof(tKDAUFTRAGEREIGNIS));  // zero out record buffer
    record.KdAuftragNr = KdAuftragNr;
    record.EreignisArt = static_cast<short>(ec);

    Select(&record, count_);             // select events for this order
    if ( Entries() )                    // then n events found
    {
        pxOrderEventListIter it(*this);
        pxOrderEvent         *event;
        while ( (event = (pxOrderEvent*) ++it) != NULL )
        {
            if ( event->Event() != ec )
                delete it.Remove();        // delete non-matching event codes
        }                                  // from the list
    }
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Do the selection with default where clause based upon the values stored   */
/*  in the record structure.                                                  */
/*----------------------------------------------------------------------------*/
size_t
pxOrderEventList :: Select
(
    const tKDAUFTRAGEREIGNIS   *recordp,
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
pxOrderEventList :: AddToList
(
    const void  *recordp,
    const int  /* row */
)
{
    // construct new 'pxOrderEvent  ' object:
    pxOrderEvent *objectp = new pxOrderEvent(Session(), *(tKDAUFTRAGEREIGNIS*) recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxOrderEventList :: EndBrowse
(
    const int  cursorid
)
{
    return pxAuftragEreignisEndBrowse(cursorid);
}

int
pxOrderEventList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxAuftragEreignisGetNext((tKDAUFTRAGEREIGNIS*)recordp, cursorid);
}

int
pxOrderEventList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxAuftragEreignisStartBrowse((tKDAUFTRAGEREIGNIS*)keys, cursorid);
}
