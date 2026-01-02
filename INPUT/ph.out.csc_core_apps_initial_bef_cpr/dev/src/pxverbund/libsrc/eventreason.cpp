/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxEventReason methods.

REVISION HISTORY

06 Aug 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxeventreason.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxEventReason :: pxEventReason
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
pxEventReason :: pxEventReason
(
    pxEventReason& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERPROUP structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxEventReason :: pxEventReason
(
    pxSession   *session,
    tEVENTREASONS& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxEventReason :: pxEventReason
(
    pxSession   *session,
    EventCodes   EventCode,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    EventCode_        = EventCode;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxEventReason :: ~pxEventReason()
{
        ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tEVENTREASONS structure.       */
/*----------------------------------------------------------------------------*/
tEVENTREASONS&
Assign
(
    tEVENTREASONS&    dest,
    const pxEventReason&  src
)
{
    // Copy native data types:
    dest.EventCode        = static_cast<short>(src.EventCode_);
    // Strings:
    dest.EventDescription[0] = ' ';
    src.EventDescription_.GetData(dest.EventDescription);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' structure to a pxEventReason object.     */
/*----------------------------------------------------------------------------*/
pxEventReason&
Assign
(
    pxEventReason&           dest,
    const tEVENTREASONS&   src
)
{
    dest.EventCode_        = static_cast<pxEventReason::EventCodes>(src.EventCode);
    dest.EventDescription_        = src.EventDescription;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxEventReason :: Init()
{
    tEVENTREASONS    record;
    memset(&record, 0 , sizeof(tEVENTREASONS));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tEVENTREASONS struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxEventReason&
pxEventReason :: operator=( const pxEventReason& src)
{
    tEVENTREASONS record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tEVENTREASONS structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxEventReason&
pxEventReason :: operator=( const tEVENTREASONS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxEventReason :: Get
(
    DBAccessMode mode
)

{
    tEVENTREASONS record;
    memset(&record, 0, sizeof(tEVENTREASONS));
    record.EventCode        = static_cast<short>(EventCode_);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;             // import the data from tEVENTREASONS struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxEventReason :: Put
(
)
{
    tEVENTREASONS record;
    memset(&record, 0, sizeof(tEVENTREASONS));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tEVENTREASONS));
}


/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxEventReason :: Read
(
    const void  *record
)
{
    return pxEventReasonRead((tEVENTREASONS*)record);
}

int
pxEventReason :: ReadLock
(
    const void  *record
)
{
    return pxEventReasonReadLock((tEVENTREASONS*)record);
}

int
pxEventReason :: Update
(
    const void  *record
)
{
    return pxEventReasonUpdate((tEVENTREASONS*)record);
}

int
pxEventReason :: Insert
(
    const void  *record
)
{
    return pxEventReasonInsert((tEVENTREASONS*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxEventReason list  */
/*  objects being inserted in the following ascending sequence: KdGruppe.     */
/*----------------------------------------------------------------------------*/
int
pxEventReason :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxEventReason *that = (pxEventReason*)That;
    int retval = (EventCode_ == that->EventCode_) ? 0
                : (EventCode_ > that->EventCode_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxEventReasonList :: pxEventReasonList
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
pxEventReasonList :: Select
(
    const int     count_
)
{
    tEVENTREASONS record;
    memset(&record, 0, sizeof(tEVENTREASONS));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxEventReasonList :: Select
(
    const short   EventCode,
    const int     count_
)
{
    tEVENTREASONS record;
    memset(&record, 0, sizeof(tEVENTREASONS));  // zero out entire record buffer
    record.EventCode        = EventCode;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxEventReasonList :: AddToList
(
    const void  *recordp,
    const int  /* row */
)
{
    // construct new 'pxEventReason' object:
    pxEventReason *objectp = new pxEventReason(Session(), *(tEVENTREASONS*)recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxEventReasonList :: EndBrowse
(
    const int  cursorid
)
{
    return pxEventReasonEndBrowse(cursorid);
}


int
pxEventReasonList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxEventReasonGetNext((tEVENTREASONS*)recordp, cursorid);
}

int
pxEventReasonList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxEventReasonStartBrowse((tEVENTREASONS*)keys, cursorid);
}
