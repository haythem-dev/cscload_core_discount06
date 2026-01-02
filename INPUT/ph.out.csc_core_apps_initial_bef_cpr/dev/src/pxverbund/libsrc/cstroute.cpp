#include "pxcstrou.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "tourutil.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustRoute :: pxCustRoute
(
    pxSession *session
)
    :pxRoute(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustRoute :: pxCustRoute
(
    const pxCustRoute& src
)
    : pxRoute((const pxRoute&)src)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTOURPLANTAG structure to construct this instance.                    */
/*----------------------------------------------------------------------------*/
pxCustRoute :: pxCustRoute
(
    pxSession *session,
    tTOURPLANTAG& src,
    short FilialNr
)
    : pxRoute(session, src.TourId, nDate(src.DatumKommi), FilialNr)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustRoute :: ~pxCustRoute()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTOURPLANTAG structure.        */
/*----------------------------------------------------------------------------*/
tTOURPLANTAG&
Assign
(
    tTOURPLANTAG&     dest,
    const pxCustRoute& src
)
{
    dest.IDFNr           = src.IDFNr_;
    dest.DatumKommi      = src.DatumKommi_.GetYYYYMMDD();
    dest.TourId[0] = ' ';
    src.TourId_.GetData(dest.TourId);
    dest.ReihenFolgeNr   = src.ReihenFolgeNr_;
    dest.FahrtZeit       = src.FahrtZeit_;
    dest.Bemerkungen[0] = ' ';
    src.Bemerkungen_.GetData(dest.Bemerkungen);
    dest.KZUpd           = src.KZUpd_;
    dest.IstVerbundTour =  src.IstVerbundTour_;
    dest.VertriebszentrumNr = src.VertriebszentrumNr_;
    dest.KundenNr = src.KundenNr_;
    dest.KoArt    = src.KoArt_ ;
    dest.TourInaktiv     = src.TourInaktiv_;
    dest.KippZeit        = src.KippZeit_;
    dest.KZAutoZuord     = src.KZAutoZuord_;
    dest.IstVaTour       =  src.IstVaTour_;
    dest.KdAuftragArt[0] = ' ';
    src.KdAuftragArt_.GetData(dest.KdAuftragArt);
    dest.DeliverBranchNo = src.DeliverBranchNo_;
    dest.SencloserDone   = src.SencloserDone_;
    dest.OrderLabelCount  = src. OrderLabelCount_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTOURPLANTAG structure to a pxCustRoute    */
/*                                                              object.       */
/*----------------------------------------------------------------------------*/
pxCustRoute&
Assign
(
    pxCustRoute&    dest,
    const tTOURPLANTAG&  src
)
{
    dest.IDFNr_          = src.IDFNr;
    dest.DatumKommi_     = nDate(src.DatumKommi);
    dest.TourId_         = src.TourId;
    dest.ReihenFolgeNr_  = src.ReihenFolgeNr;
    dest.FahrtZeit_      = src.FahrtZeit;
    dest.Bemerkungen_    = src.Bemerkungen;
    dest.Bemerkungen_.Strip();
    dest.KZUpd_          = src.KZUpd;
    dest.IstVerbundTour_ =  src.IstVerbundTour;
    dest.VertriebszentrumNr_ = src.VertriebszentrumNr;
    dest.KundenNr_ = src.KundenNr;
    dest.KoArt_    = src.KoArt;
    dest.TourInaktiv_    = src.TourInaktiv;
    dest.KippZeit_       = src.KippZeit;
    dest.KZAutoZuord_    = src.KZAutoZuord;
    dest.IstVaTour_      =  src.IstVaTour;
    dest.KdAuftragArt_   = src.KdAuftragArt;
    dest.DeliverBranchNo_ = src.DeliverBranchNo;
    dest.SencloserDone_   = src.SencloserDone;
    dest.OrderLabelCount_  = src. OrderLabelCount;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual function inherited from nCollectable.                    */
/*  CompareTo Function ensures object to inserted into a container in         */
/*  ascending sequence.                                                       */
/*----------------------------------------------------------------------------*/
int
pxCustRoute :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustRoute* that = (pxCustRoute *) That;
    pxCustRoute* self = (pxCustRoute *) this;
    #if 0
    int retval = (IDFNr_ == that->IDFNr_) ? 0
                 : (IDFNr_ > that->IDFNr_ ? 1 : -1);
    #endif
    int retval = (KundenNr_ == that->KundenNr_) ? 0
               : (KundenNr_ > that->KundenNr_ ? 1 : -1);

    if (retval == 0)
    {
        retval = (VertriebszentrumNr_ == that->VertriebszentrumNr_) ? 0
               : (VertriebszentrumNr_ > that->VertriebszentrumNr_ ? 1 : -1);
    }
    if ( retval == 0 )
    {
         retval = ( self->DateTimePick() == that->DateTimePick()) ? 0
                : (self->DateTimePick() > that->DateTimePick() ? 1 : -1);
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustRoute :: Init()
{
    tTOURPLANTAG record;
    memset(&record, 0, sizeof(tTOURPLANTAG));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tTOURPLANTAG        */
/*  struct and then imported to self.                                         */
/*----------------------------------------------------------------------------*/
pxCustRoute&
pxCustRoute :: operator=( const pxCustRoute& src)
{
    tTOURPLANTAG record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTOURPLANTAG structure to this instance.         */
/*----------------------------------------------------------------------------*/
pxCustRoute&
pxCustRoute :: operator=( const tTOURPLANTAG& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustRoute :: Get
(
    DBAccessMode mode
)
{
    tTOURPLANTAG record;
    memset(&record, 0, sizeof(tTOURPLANTAG));
    Assign(record, *this);              // easily gets keys
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustRoute :: Put
(
)
{
    tTOURPLANTAG record;
    memset(&record, 0, sizeof(tTOURPLANTAG));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tTOURPLANTAG));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustRoute :: Read
(
    const void *record
)
{
    return pxTourPlanTagRead((tTOURPLANTAG*)record);
}

int
pxCustRoute :: ReadLock
(
    const void *record
)
{
    return pxTourPlanTagReadLock((tTOURPLANTAG*)record);
}

int
pxCustRoute :: Update
(
    const void *record
)
{
    return pxTourPlanTagUpdate((tTOURPLANTAG*)record);
}

int
pxCustRoute :: Insert
(
    const void *record
)
{
    return pxTourPlanTagInsert((tTOURPLANTAG*)record);
}

/*----------------------------------------------------------------------------*/
/*  GetTourIdSeconds:this function returns a long containing the seconds      */
/*  depend on TourId                                                          */
/*----------------------------------------------------------------------------*/
long
pxCustRoute :: GetTourIdSeconds
(
)
{
    long retval = 0;
    retval = atol((char*)(nString)(TourId_(0, 2))) * 3600 +
             atol((char*)(nString)(TourId_(2, 2))) * 60;
    return retval;
}

/*----------------------------------------------------------------------------*/
bool pxCustRoute::IsPseudoTour() const
{
    return TourUtil::isPseudoTour( TourId_ );
}

/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxCustRouteList :: pxCustRouteList
(
    pxSession *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using single  LONG  value arguments.                 */
/*----------------------------------------------------------------------------*/
#if 0
size_t
pxCustRouteList :: Select
(
    const long    IDFNr,
    const int     count_                // Max number of records to read
)
{
    tTOURPLANTAG record;
    memset(&record, 0, sizeof(tTOURPLANTAG));     // zero out entire record buffer
    record.IDFNr = IDFNr;
    return Select(&record, count_);
}
#endif

size_t
pxCustRouteList :: Select
(
    short   VertriebszentrumNr,
    long    KundenNr,
    short   FilialNr,
    const nDate&   Datum,
    int     count_                // Max number of records to read
)
{
    tTOURPLANTAG record;
    memset(&record, 0, sizeof(tTOURPLANTAG));     // zero out entire record buffer
    record.VertriebszentrumNr = VertriebszentrumNr;
    record.KundenNr = KundenNr;
    FilialNr_ = FilialNr;
    record.DatumKommi = Datum.GetYYYYMMDD(); // store key
    return Select(&record, count_);
}

size_t
pxCustRouteList :: Select
(
    short   VertriebszentrumNr,
    long    KundenNr,
    short   FilialNr,
    char    vbtour,
    const nDate&   Datum,
    int     count_                // Max number of records to read
)
{
    tTOURPLANTAG record;
    memset(&record, 0, sizeof(tTOURPLANTAG));     // zero out entire record buffer
    record.VertriebszentrumNr = VertriebszentrumNr;
    record.KundenNr = KundenNr;
    FilialNr_ = FilialNr;
    record.IstVerbundTour  = vbtour;
    record.DatumKommi = Datum.GetYYYYMMDD(); // store key
    int cursorid = cCRSTOURPTG_ISAUXREM;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tTOURPLANTAG structure.*/
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxCustRouteList :: Select
(
    tTOURPLANTAG  *recordp,
    const int     count_
)
{
    // Set the cursor id:
    int cursorid = cCRS_DEFAULT;
    nDBSelect(recordp, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustRouteList :: AddToList
(
    const void *record,
    const int  /* row */
)
{
    pxCustRoute *objectp = new pxCustRoute(Session(),*(tTOURPLANTAG*) record, FilialNr_);
    if ( objectp->IsActive() )          // ensure base object has been read
        InsertAscending(objectp);       // before we do the insert
    else                                // failure during object construction
    {
        delete objectp;
        objectp = NULL;
    }
    return objectp;
}

int
pxCustRouteList :: EndBrowse
(
    const int cursorid
)
{
    return pxTourPlanTagEndBrowse(cursorid);
}

int
pxCustRouteList :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxTourPlanTagGetNext((tTOURPLANTAG*)record, cursorid);
}

int
pxCustRouteList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    return pxTourPlanTagStartBrowse((tTOURPLANTAG*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  Shrink the list to contain only routes having a pick date/time stamp      */
/*  equal to or above the time limit passed as argument.                      */
/*  Returns number of entries remaining in the list.                          */
/*----------------------------------------------------------------------------*/
int
pxCustRouteList :: Shrink
(
    const nTime& TimeLimit
)
{
    nTime  Limit = TimeLimit;
    long   timelimit = (Limit.GetHours() * 3600) + (Limit.GetMinutes() * 60 + Limit.GetSeconds());
    nTime  ctime;
    int    anzday = Limit.GetDayOfWeek() - ctime.GetDayOfWeek();
    timelimit += (anzday*(24*60*60));

    pxCustRoute* route;
    pxCustRouteListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        if ( route->IsClosed() || timelimit > route->GetTourIdSeconds() || route->IsTourInaktiv())
            delete cursor.Remove();
    }
    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  Shrink the list to contain only routes having a pick date/time stamp      */
/*  equal to or above the time limit passed as argument.                      */
/*  Returns number of entries remaining in the list.                          */
/*----------------------------------------------------------------------------*/
int
pxCustRouteList :: Shrink
(
    const nTime&  TimeLimit,
    long        *KippZeit
)
{
    pxCustRoute* route;
    pxCustRouteListIter cursor(*this);   // define an iterator
    *KippZeit = 0;
    nTime  Limit = TimeLimit;
    long   timelimit = (Limit.GetHours() * 3600) + (Limit.GetMinutes() * 60 + Limit.GetSeconds());
    nTime   ctime;
    int    anzday = Limit.GetDayOfWeek() - ctime.GetDayOfWeek();
    timelimit += (anzday*(24*60*60));

    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        *KippZeit = route->KippZeit();
        if ( route->IsClosed() || (timelimit + (*KippZeit*60L)) > route->GetTourIdSeconds() || route->IsTourInaktiv())
            delete cursor.Remove();
    }
    if ( Entries() )
    {
        *KippZeit = ((pxCustRoute*)(At(0)))->KippZeit();
    }

    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  Shrink the list to contain only routes depend on kdauftragart             */
/*  Returns number of entries remaining in the list.                          */
/*----------------------------------------------------------------------------*/
int
pxCustRouteList :: Shrink
(
    const nString& KdAuftragArt
)
{
    pxCustRoute* route;
    pxCustRouteListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        nString aa(route->KdAuftragArt());
        aa.Strip();                        // strip off blanks
        if (!aa.IsEmpty() && aa != KdAuftragArt && route->IsAutoAllocation())
            delete cursor.Remove();
    }
    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  ShrinkForOrderType;this list is shrinked to a list wich contains only     */
/*  entries where KdAuftragArt > "" and  where                                */
/*  Returns number of entries remaining in the list.                          */
/*----------------------------------------------------------------------------*/
int
pxCustRouteList :: ShrinkForOrderType
(
    const nString& KdAuftragArt
)
{
    if ( KdAuftragArt.IsEmpty() )
    {
        return static_cast<int>(Entries());
    }

    nString OrderType = KdAuftragArt;
    pxCustRoute* route;
    pxCustRouteListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        nString aa(route->KdAuftragArt());
        aa.Strip();                        // strip off blanks
        if (!aa.IsEmpty() && aa.Length() == 1)
        {
            OrderType.Trim(1L);
        }
        if (aa.IsEmpty()  && route->IsAutoAllocation() )
            delete cursor.Remove();
        if (!aa.IsEmpty() && aa != OrderType && route->IsAutoAllocation())
            delete cursor.Remove();
        OrderType = KdAuftragArt;
    }
    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  ShrinkForOrderType;this list is shrinked to a list wich contains only     */
/*  entries where KdAuftragArt > "" and  where                                */
/*  Returns number of entries remaining in the list.                          */
/*----------------------------------------------------------------------------*/
int
pxCustRouteList :: ShrinkForOrderType
(
)
{
    pxCustRoute* route;
    pxCustRouteListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        nString aa(route->KdAuftragArt());
        aa.Strip();                        // strip off blanks
        if ( aa.IsEmpty()  && route->IsAutoAllocation() )
            delete cursor.Remove();
    }
    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  OrderTypesInList; this method looks for entries with KdAuftragArt > ""    */
/*  If found one, true is returned, otherwise false                           */
/*----------------------------------------------------------------------------*/
bool
pxCustRouteList :: OrderTypesInList
(
)
{
    bool retval = false;
    pxCustRoute* route;
    pxCustRouteListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        nString aa(route->KdAuftragArt());
        aa.Strip();                        // strip off blanks
        if ( !aa.IsEmpty() )
        {
            retval = true;
            break;
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  IsOrderTypeInList; this method looks for entries with  the given          */
/*  KdAuftragArt.If found, true is returned, otherwise false                  */
/*----------------------------------------------------------------------------*/
bool
pxCustRouteList :: IsOrderTypeInList
(
    const nString& KdAuftragArt
)
{
    bool retval = false;
    pxCustRoute* route;
    nString OrderType = KdAuftragArt;
    pxCustRouteListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        nString aa(route->KdAuftragArt());
        aa.Strip();                        // strip off blanks
        if (!aa.IsEmpty() && aa.Length() == 1)
        {
            OrderType.Trim(1L);
        }
        if ( aa == OrderType )
        {
            retval = true;
            break;
        }
        OrderType = KdAuftragArt;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  NewList: This methode coies this list and returs the pointer to the new   */
/*  list. Please take care for a well contructed pxCustRouteList              */
/*----------------------------------------------------------------------------*/
pxCustRouteList*
pxCustRouteList :: NewList
(
)
{
    pxCustRouteList* newlist = NULL;
    pxCustRoute* route;
    pxCustRoute* newentry;
    newlist = new pxCustRouteList(Session());
    pxCustRouteListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        newentry = new pxCustRoute(*route);
        newlist->Append(newentry);
    }
    return newlist;
}

/*----------------------------------------------------------------------------*/
/*  Find the first route having a pick date/time stamp above or equal to the  */
/*  time limit passed as argument.                                            */
/*  Returns a pointer to that route or NULL if no such route could be found.  */
/*----------------------------------------------------------------------------*/
pxCustRoute*
pxCustRouteList :: Find
(
    const nTime&  TimeLimit
)
{
    pxCustRoute* route;
    pxCustRouteListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        if ( route->DateTimePick() >= TimeLimit )
            break;
    }
    return route;
}

/*----------------------------------------------------------------------------*/
/*  Find first occurence of TourId and return a pointer to that instance.     */
/*----------------------------------------------------------------------------*/
pxCustRoute*
pxCustRouteList :: Find
(
    const nString& TourId
)
{
    pxCustRouteListIter cursor(*this);   // define an iterator
    pxCustRoute* route;
    while ( ( (route = (pxCustRoute*) ++cursor) != NULL) && route->TourId() != TourId )
    ;
    return route;
}

/*----------------------------------------------------------------------------*/
/*  Get a default tour.                                                       */
/*----------------------------------------------------------------------------*/
pxCustRoute*
pxCustRouteList :: GetDefault
(
)
{
    return (pxCustRoute*)At(0);
}

/*----------------------------------------------------------------------------*/
/*  Get the last tour within the list                                         */
/*----------------------------------------------------------------------------*/
pxCustRoute*
pxCustRouteList :: GetLast
(
)
{
    pxCustRouteListIter cursor(*this);   // define an iterator
    pxCustRoute* route;
    cursor.ToLast();                     // scan List backward
    while ( ( (route = (pxCustRoute*) --cursor) != NULL ) && ( route->IsPseudoTour()) )
    ;
    return route;
}

/*----------------------------------------------------------------------------*/
/*  FindAllocatableRoute This function looks for a route where kzautozuord = 1*/
/*  within a routelist that has been already shrinked by all dependencies     */
/*  p.a Kippzeit current time etc                                             */
/*----------------------------------------------------------------------------*/
pxCustRoute*
pxCustRouteList :: FindAllocatableRoute
(
)
{
    pxCustRouteListIter cursor(*this);   // define an iterator
    pxCustRoute* route = NULL;
    while ( ( (route = (pxCustRoute*) ++cursor) != NULL ) && !route->IsAutoAllocation() )
    ;
    return route;
}

/*----------------------------------------------------------------------------*/
/*  FindNextAllocatableRoute This function looks for a route higher then      */
/*  tourid and kzautozuord = 1                                                */
/*  within a routelist that has been already shrinked by all dependencies     */
/*  p.a Kippzeit current time etc                                             */
/*----------------------------------------------------------------------------*/
pxCustRoute*
pxCustRouteList :: FindNextAllocatableRoute
(
    const nString& tourid
)
{
    pxCustRouteListIter cursor(*this);   // define an iterator
    pxCustRoute* route = NULL;
    long tour = atol(tourid);
    tour  = tour/100;
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        if ( route->IsAutoAllocation() )
        {
            long ctour = atol((char*)(route->TourId())) / 100;
            if ( ctour > tour )
                break;
        }
    }
    return route;
}

/*----------------------------------------------------------------------------*/
/*  FindNextAllocatableRoute This function looks for a route higher then      */
/*  tourid and kzautozuord = 1                                                */
/*  within a routelist that has been already shrinked by all dependencies     */
/*  p.a Kippzeit current time etc                                             */
/*----------------------------------------------------------------------------*/
pxCustRoute*
pxCustRouteList :: FindNextAllocatableRoute
(
    const nString& tourid,
    const nTime& time
)
{
    pxCustRouteListIter cursor(*this);   // define an iterator
    pxCustRoute* route = NULL;
    long tour = atol(tourid);
    long ctour = 0;
    tour = tour / 100;
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        if ( route->DateTimePick() >= time && route->IsAutoAllocation() )
        {
            ctour = atol((char*)(route->TourId())) / 100;
            if ( ctour > tour )
                break;
        }
    }
    if(route == NULL)   // if no autoallocated route
    {
        cursor.Reset();
        while ( (route = (pxCustRoute*) ++cursor) != NULL )
        {
            if ( route->DateTimePick() >= time )
            {
                ctour = atol((char*)(route->TourId())) / 100;
                if ( ctour > tour )
                    break;
            }
        }
    }
    return route;
}

/*----------------------------------------------------------------------------*/
/*  This function calculates the Day of Week to hold it this object           */
/*  Base for Calculation id DateTimePick                                      */
/*----------------------------------------------------------------------------*/
int
pxCustRouteList :: SetWeekDay
(
)
{
    int retval = 0;
    pxCustRouteListIter cursor(*this);   // define an iterator
    pxCustRoute* route = NULL;
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        WeekDay_ = (short)route->DatumKommi().GetDayOfWeek();
        break;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  This function calculates the Day of Week to hold it this object           */
/*  Base for Calculation id DateTimePick                                      */
/*----------------------------------------------------------------------------*/
pxCustRoute*
pxCustRouteList :: FindVaTour
(
)
{
    pxCustRouteListIter cursor(*this);   // define an iterator
    pxCustRoute* route = NULL;
    while ( (route = (pxCustRoute*) ++cursor) != NULL )
    {
        if ( route->IsVaTour() )
        break;
    }
    return route;
}

/*----------------------------------------------------------------------------*/
/*  This function calculates the arrival time for the current route entry     */
/*----------------------------------------------------------------------------*/
nTime
pxCustRoute :: Arrival
(
)
{
    nTime arrivalTime;
    nTime tv = ZeitVersand();             // time Versand
    tv = tv + ((long) FahrtZeit_ * 60L);  // time Versand + Fahrtzeit
    nDate ad(tv);                         // arrival Date

    arrivalTime = nTime((int)ad.GetYear(),
                        (int)ad.GetMonth(),
                        (int)ad.GetDay(),
                        (int)tv.GetHours(),
                        (int)tv.GetMinutes(),
                        (int)tv.GetSeconds());

    return arrivalTime;
}
