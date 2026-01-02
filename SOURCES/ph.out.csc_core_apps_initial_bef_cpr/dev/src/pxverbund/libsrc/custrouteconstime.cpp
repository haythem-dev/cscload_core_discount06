/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxCustRouteConsTime methods.

REVISION HISTORY

28 April 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxcustrouteconstime.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustRouteConsTime :: pxCustRouteConsTime
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
pxCustRouteConsTime :: pxCustRouteConsTime
(
    const pxCustRouteConsTime& src
)
    : pxDBRecord(((pxCustRouteConsTime&) src) .Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTOURPLANCONSTIME structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxCustRouteConsTime :: pxCustRouteConsTime
(
    pxSession *session,
    tTOURPLANCONSTIME& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustRouteConsTime :: pxCustRouteConsTime
(
    pxSession      *session,
    const short   VertriebszentrumNr,
    const long    KundenNr,
    const nString& TourId,                     // Read via string input
    const nDate&   DatumKommi,
    const nClock&  ConsTime,
    DBAccessMode   mode
)
    : pxDBRecord(session)
{
    Init();
    VertriebszentrumNr_   = VertriebszentrumNr;
    KundenNr_             = KundenNr;
    TourId_               = TourId;
    DatumKommi_           = DatumKommi;
    ConsTime_             = ConsTime;
    Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustRouteConsTime :: ~pxCustRouteConsTime()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTOURPLANCONSTIME structure.   */
/*----------------------------------------------------------------------------*/
tTOURPLANCONSTIME&
Assign
(
    tTOURPLANCONSTIME&     dest,
    const pxCustRouteConsTime& src
)
{
    dest.VertriebszentrumNr     = src.VertriebszentrumNr_        ;
    dest.KundenNr               = src.KundenNr_;
    dest.TourId[0] = ' ';
    src.TourId_.GetData(dest.TourId);
    dest.DatumKommi             = src.DatumKommi_.GetYYYYMMDD();
    dest.ConsTime               = src.ConsTime_.GetHHMMSS();
    dest.ProcessState           = src.ProcessState_     ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTOURPLANCONSTIME structure to             */
/*  a pxCustRouteConsTime object                                              */
/*----------------------------------------------------------------------------*/
pxCustRouteConsTime&
Assign
(
    pxCustRouteConsTime&    dest,
    const tTOURPLANCONSTIME&  src
)
{
    dest.VertriebszentrumNr_    = src.VertriebszentrumNr        ;
    dest.KundenNr_              = src.KundenNr;
    dest.TourId_                = src.TourId           ;
    dest.DatumKommi_            = nDate(src.DatumKommi);
    dest.ConsTime_              = src.ConsTime         ;
    dest.ProcessState_          = src.ProcessState     ;
    return dest;

}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual function inherited from nCollectable.                    */
/*  CompareTo Function ensures object to inserted into a container in         */
/*  ascending sequence.                                                       */
/*----------------------------------------------------------------------------*/
int
pxCustRouteConsTime :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustRouteConsTime* that = (pxCustRouteConsTime *) That;
    pxCustRouteConsTime* self = (pxCustRouteConsTime *) this;
    int retval = (KundenNr_ == that->KundenNr_) ? 0
                 : (KundenNr_ > that->KundenNr_ ? 1 : -1);

    if (retval == 0)
    {
        retval = (VertriebszentrumNr_ == that->VertriebszentrumNr_) ? 0
                     : (VertriebszentrumNr_ > that->VertriebszentrumNr_ ? 1 : -1);
    }
    if ( retval == 0 )
    {
         retval = ( self->DatumKommi() == that->DatumKommi()) ? 0
                  : (self->DatumKommi() > that->DatumKommi() ? 1 : -1);
    }
    if ( retval == 0 )
    {
         retval = ( self->ConsTime() == that->ConsTime()) ? 0
                  : (self->ConsTime() > that->ConsTime() ? 1 : -1);
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustRouteConsTime :: Init()
{
    tTOURPLANCONSTIME    record;
    memset(&record, 0 , sizeof(tTOURPLANCONSTIME));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tTOURPLANCONSTIME   */
/*  struct and then imported to self.                                         */
/*----------------------------------------------------------------------------*/
pxCustRouteConsTime&
pxCustRouteConsTime :: operator=( const pxCustRouteConsTime& src)
{
    tTOURPLANCONSTIME    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTOURPLANCONSTIME structure to this instance.    */
/*----------------------------------------------------------------------------*/
pxCustRouteConsTime&
pxCustRouteConsTime :: operator=( const tTOURPLANCONSTIME& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustRouteConsTime :: Get
(
    DBAccessMode mode
)

{
    tTOURPLANCONSTIME record;
    memset(&record, 0, sizeof(tTOURPLANCONSTIME));
    Assign(record, *this);              // easily gets keys
    int retval = ( mode == cDBGET_FORUPDATE )
                    ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustRouteConsTime :: Put
(
)
{
    tTOURPLANCONSTIME record;
    memset(&record, 0, sizeof(tTOURPLANCONSTIME));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tTOURPLANCONSTIME));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxCustRouteConsTime :: Delete
(
)
{
    tTOURPLANCONSTIME record;
    memset(&record, 0, sizeof(tTOURPLANCONSTIME));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustRouteConsTime :: Read
(
    const void  *record
)
{

    return pxTourPlanConsTimeRead((tTOURPLANCONSTIME*)record);
}

int
pxCustRouteConsTime :: ReadLock
(
    const void  *record
)
{
    return pxTourPlanConsTimeReadLock((tTOURPLANCONSTIME*)record);
}

int
pxCustRouteConsTime :: Update
(
    const void  *record
)
{
    return pxTourPlanConsTimeUpdate((tTOURPLANCONSTIME*)record);
}

int
pxCustRouteConsTime :: Delete
(
    const void  *record
)
{
    return pxTourPlanConsTimeDelete((tTOURPLANCONSTIME*)record);
}

int
pxCustRouteConsTime :: Insert
(
    const void  *record
)
{
    return pxTourPlanConsTimeInsert((tTOURPLANCONSTIME*)record);
}

/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxCustRouteConsTimeList :: pxCustRouteConsTimeList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using single  LONG  value arguments.                 */
/*----------------------------------------------------------------------------*/
size_t
pxCustRouteConsTimeList :: Select
(
    const short   VertriebszentrumNr,
    const long    KundenNr,
    const nString& TourId,
    const nDate&   DatumKommi,
    const int     count_                // Max number of records to read
)

{

    tTOURPLANCONSTIME record;
    memset(&record, 0, sizeof(tTOURPLANCONSTIME));     // zero out entire record buffer
    record.VertriebszentrumNr = VertriebszentrumNr;
    record.KundenNr = KundenNr;
    record.TourId[0]    = ' ';
    TourId.GetData(record.TourId);
    record.DatumKommi   = DatumKommi.GetYYYYMMDD();
    int cursorid = cCRS_DEFAULT;
    return nDBSelect(&record,cursorid, count_);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using single  LONG  value arguments.                 */
/*----------------------------------------------------------------------------*/
size_t
pxCustRouteConsTimeList :: Select
(
    const short   VertriebszentrumNr,
    const nDate&   DatumKommi,
    const nClock&  ConsTime,
    const char    ProcessState,
    const int     count_                // Max number of records to read
)

{

    tTOURPLANCONSTIME record;
    memset(&record, 0, sizeof(tTOURPLANCONSTIME));     // zero out entire record buffer
    record.VertriebszentrumNr = VertriebszentrumNr;
    record.DatumKommi   = DatumKommi.GetYYYYMMDD();
    record.ConsTime   = (ConsTime.GetHHMMSS()/100);
    record.ProcessState = ProcessState;
    int cursorid = cCRSTPLCONSTIME_CTIMEPSTATE;
    return nDBSelect(&record,cursorid, count_);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustRouteConsTimeList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    pxCustRouteConsTime *objectp = new pxCustRouteConsTime(Session(),*(tTOURPLANCONSTIME*) record);
    InsertAscending(objectp);        // before we do the insert
    return objectp;
}

int
pxCustRouteConsTimeList :: EndBrowse
(
    const int  cursorid
)
{

    return pxTourPlanConsTimeEndBrowse(cursorid);
}


int
pxCustRouteConsTimeList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{

    return pxTourPlanConsTimeGetNext((tTOURPLANCONSTIME*)record, cursorid);
}

int
pxCustRouteConsTimeList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{

    return pxTourPlanConsTimeStartBrowse((tTOURPLANCONSTIME*)keys, cursorid);
}
