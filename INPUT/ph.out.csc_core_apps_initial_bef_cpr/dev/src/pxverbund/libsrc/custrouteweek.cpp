/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxCustRouteWeek  methods.

REVISION HISTORY

27 April 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxcustrouteweek.hpp"
#include <pxdbxx.h>
#include <clock.hpp>
#include <date.hpp>
#include <nntypes.h>
#include "pxsess.hpp"
#include "pxroutedef.h"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustRouteWeek :: pxCustRouteWeek
(
    pxSession   *session
)
    :pxRouteWeek(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustRouteWeek :: pxCustRouteWeek
(
    pxCustRouteWeek& src
)
    : pxRouteWeek((const pxRouteWeek&)src)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTOURPLANTAGWOCHE structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxCustRouteWeek :: pxCustRouteWeek
(
    pxSession   *session,
    tTOURPLANTAGWOCHE& src
)
    : pxRouteWeek(session, src.VertriebszentrumNr, src.TourId, src.TagesTyp)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustRouteWeek :: ~pxCustRouteWeek()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTOURPLANTAGWOCHE structure.   */
/*----------------------------------------------------------------------------*/
tTOURPLANTAGWOCHE&
Assign
(
    tTOURPLANTAGWOCHE&           dest,
    const pxCustRouteWeek&       src
)
{
    dest.VertriebszentrumNr  = src.VertriebszentrumNr_;
    dest.KundenNr            = src.KundenNr_;
    dest.WeekDay             = src.WeekDay_;
    dest.TourId[0] = ' ';
    src.TourId_.GetData(dest.TourId);
    dest.TagesTyp[0] = ' ';
    src.TagesTyp_.GetData( dest.TagesTyp, (mSIZEOF(tTOURPLANTAGWOCHE, TagesTyp)) - 1 );
    dest.IstVerbundTour      =  src.IstVerbundTour_;
    dest.KdAuftragArt[0] = ' ';
    src.KdAuftragArt_.GetData(dest.KdAuftragArt);
    dest.FahrtZeit            = src.FahrtZeit_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTOURPLANTAGWOCHE structure to             */
/*  a pxCustRouteWeek object.                                                 */
/*----------------------------------------------------------------------------*/
pxCustRouteWeek&
Assign
(
    pxCustRouteWeek&             dest,
    const tTOURPLANTAGWOCHE&     src
)
{
    dest.VertriebszentrumNr_     = src.VertriebszentrumNr;
    dest.KundenNr_               = src.KundenNr;
    dest.TourId_                 = src.TourId;
    dest.TagesTyp_               = src.TagesTyp;
    dest.TagesTyp_.Strip();
    dest.WeekDay_                = src.WeekDay;
    dest.IstVerbundTour_         =  src.IstVerbundTour;
    dest.KdAuftragArt_           = src.KdAuftragArt;
    dest.FahrtZeit_              = src.FahrtZeit;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustRouteWeek :: Init()
{
    tTOURPLANTAGWOCHE record;
    memset(&record, 0, sizeof(tTOURPLANTAGWOCHE));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tTOURPLANTAGWOCHE struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxCustRouteWeek&
pxCustRouteWeek :: operator=( const pxCustRouteWeek& src)
{
    tTOURPLANTAGWOCHE record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTOURPLANTAGWOCHE structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCustRouteWeek&
pxCustRouteWeek :: operator=( const tTOURPLANTAGWOCHE& src)
{

    Assign(*this, src);
    WochenTag_ = ConvertDayTyp(TagesTyp_);
    return *this;
}

int
pxCustRouteWeekList :: EndBrowse
(
    const int cursorid
)
{
    return pxTourPlanTagWocheEndBrowse(cursorid);
}

/*----------------------------------------------------------------------------*/
/*  ConvertDayTyp Converts TagesTyp from char to int                          */
/*  MO = 1, DI = 2, MI = 3 ,DO = 4, FR = 5, SA = 6, SO = 0                    */
/*----------------------------------------------------------------------------*/
int
pxCustRouteWeek :: ConvertDayTyp
(
    const nString& TagesTyp
)
{
    int retval = 0;;
    int x = sizeof(cDayTonDayTable) / sizeof(DAYTabEntry);  // index calculation
    for (int i = 0; i < x; i++)
    {
       if ( TagesTyp == (nString)cDayTonDayTable[i].cDayType )
       {
          retval = cDayTonDayTable[i].nDayType;         // match
          break;
       }
    }
    return retval;
}

int
pxCustRouteWeekList :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxTourPlanTagWocheGetNext((tTOURPLANTAGWOCHE*)record, cursorid);
}

int
pxCustRouteWeekList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    return pxTourPlanTagWocheStartBrowse((tTOURPLANTAGWOCHE*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCustRouteWeek list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxCustRouteWeek :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustRouteWeek *that = (pxCustRouteWeek*)That;

    int retval = (VertriebszentrumNr_ == that->VertriebszentrumNr_) ? 0
               : (VertriebszentrumNr_ > that->VertriebszentrumNr_ ? 1 : -1);

    if ( retval == 0 )
        retval = (KundenNr_ == that->KundenNr_) ? 0
               : (KundenNr_ > that->KundenNr_ ? 1 : -1);
    if ( retval == 0 )
        retval = (WeekDay_ == that->WeekDay_) ? 0
               : (WeekDay_ > that->WeekDay_ ? 1 : -1);
    if ( retval == 0 )
        retval = (TourId_ == that->TourId_) ? 0
               : (TourId_ > that->TourId_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetTourIdHHMM:this function returns a long containing the HH + MM         */
/*  depend on TourId                                                          */
/*----------------------------------------------------------------------------*/
long
pxCustRouteWeek :: GetTourIdHHMM
(
)
{
    long retval = 0;
    retval = atol((char*)(nString)(TourId_(0, 2))) * 100 +
             atol((char*)(nString)(TourId_(2, 2)));
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetTourIdHHMM:this function returns a long containing the HH + MM         */
/*  depend on TourId                                                          */
/*----------------------------------------------------------------------------*/
long
pxCustRouteWeek :: Arrival
(
)
{
    long retval = 0;
    nClock arrival(GetTourIdHHMM() * 100);
    arrival = arrival + (FahrtZeit() * 60);
    retval = arrival.GetHHMMSS() / 100;
    retval = (retval < 2400 ) ? retval : retval - 2400;
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustRouteWeekList :: pxCustRouteWeekList
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
pxCustRouteWeekList :: Select
(
    const short   VertriebszentrumNr,
    const long    KundenNr,
    const short   FilialNr,
    const int     count_
)
{
    tTOURPLANTAGWOCHE fil;
    memset(&fil, 0, sizeof(tTOURPLANTAGWOCHE));  // zero out entire record buffer
    fil.VertriebszentrumNr = VertriebszentrumNr;
    fil.KundenNr           = KundenNr;
    FilialNr_              = FilialNr;
    int cursorid   = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCustRouteWeekList :: Select
(
    const short   VertriebszentrumNr,
    const long    KundenNr,
    const short   FilialNr,
    const short   DayType,
    const int     count_
)
{
    tTOURPLANTAGWOCHE fil;
    memset(&fil, 0, sizeof(tTOURPLANTAGWOCHE));  // zero out entire record buffer
    fil.VertriebszentrumNr = VertriebszentrumNr;
    fil.KundenNr           = KundenNr;
    FilialNr_              = FilialNr;
    fil.WeekDay            = DayType;
    int cursorid   = cCRSTPLTWOCHE_DAYTYPE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCustRouteWeekList :: Select
(
    const short   VertriebszentrumNr,
    const long    KundenNr,
    const short   FilialNr,
    const char    IBTFlag,
    const int     count_
)
{
    tTOURPLANTAGWOCHE fil;
    memset(&fil, 0, sizeof(tTOURPLANTAGWOCHE));  // zero out entire record buffer
    fil.VertriebszentrumNr = VertriebszentrumNr;
    fil.KundenNr           = KundenNr;
    FilialNr_              = FilialNr;
    fil.IstVerbundTour     = IBTFlag;
    int cursorid   = cCRSTPLTWOCHE_IBT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustRouteWeekList :: AddToList
(
    const void *record,
    const int  /* row */
)
{
    // construct new 'pxCustRouteWeek' object:
    pxCustRouteWeek *objectp = new pxCustRouteWeek(Session(), *(tTOURPLANTAGWOCHE*) record);
    if ( objectp->IsActive() )          // ensure base object has been read
        InsertAscending(objectp);       // before we do the insert
    else                                // failure during object construction
    {
        delete objectp;
        objectp = NULL;
    }
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  GetNextDayFromNow: this methode is searching for the next WochenTag       */
/*  from now on. pxCustRouteWeekList is sorted by WochenTag starting with     */
/*  0 = Sunday, 1 = Monday etc.                                               */
/*  Example: the current = 3 = Wednesday and the list contains entries for    */
/*  2 = Tuesday and 5 = Friday, so this methode returns 5.  On Saturday       */
/*  it returns 2                                                              */
/*----------------------------------------------------------------------------*/
long
pxCustRouteWeekList :: GetNextDayFromNow
(
    const long Day
)
{
    long   nextday    = 0;                   // return value
    nDate  now;                              // current date
    long   currentday = now.GetDayOfWeek();  // current day of week
    if (Day > 0 )
    {
        currentday = Day;
    }

    pxCustRouteWeekListIter cursor(*this);
    pxCustRouteWeek* entryp = NULL;

    while ( (entryp = (pxCustRouteWeek*) ++cursor) != NULL )
    {
        if ( entryp->WeekDay() > currentday )
        {
            nextday = entryp->WeekDay();
            break;
        }
    }

    if (nextday == 0 )                        // no nextday found until now
    {
        nextday = ((pxCustRouteWeek*)At(0))->WeekDay();
    }
    return nextday;
}

/*----------------------------------------------------------------------------*/
/*  FindNextDay:this methode returns the first pxCustRouteWeek entry that     */
/*  matches dayofweek. If not Found, a NULL pointer returns                   */
/*----------------------------------------------------------------------------*/
pxCustRouteWeek*
pxCustRouteWeekList :: FindNextDay
(
    const long dayofweek,
    const nString& KdAuftragArt
)
{
    pxCustRouteWeekListIter cursor(*this);
    pxCustRouteWeek* entryp    = NULL;
    pxCustRouteWeek* KAentriep = NULL;      // first entry with KdAuftragArt nextday
    nString ot = KdAuftragArt;

    while ( (entryp = (pxCustRouteWeek*) ++cursor) != NULL )
    {
        if ( entryp->WeekDay() == dayofweek )
        {
            break;
        }
    }
    if ( entryp && !ot.IsEmpty() )
    {
        KAentriep = Find(dayofweek, ot);
        if (KAentriep)
        {
            return KAentriep;
        }
    }

    return entryp;
}

/*----------------------------------------------------------------------------*/
/*  Find:this methode looks for entries depending dayofweek and KdAuftragArt  */
/*  If no entry is found, which matches dayofweek and KdAuftragArt, a Null    */
/*  pointer is returned, otherwise, pointer to the matched entry              */
/*  Please take care for a well construncted list container                   */
/*----------------------------------------------------------------------------*/
pxCustRouteWeek*
pxCustRouteWeekList :: Find
(
    const long     dayofweek,
    const nString& KdAuftragArt
)
{
    pxCustRouteWeekListIter cursor(*this);
    pxCustRouteWeek* entryp = NULL;
    nString ot;

    while ( (entryp = (pxCustRouteWeek*) ++cursor) != NULL )
    {
        if ( entryp->WeekDay() ==  dayofweek )
        {
            nString aa(entryp->KdAuftragArt());
            aa.Strip();               // srtip off blanks
            ot = KdAuftragArt;
            if ( !aa.IsEmpty() && aa.Length() == 1)
            {
                ot.Trim(1);
            }
            if ( aa == ot )
            {
                break;
            }
            ot.Clear();
        }
    }
    return entryp;
}

/*----------------------------------------------------------------------------*/
/*  ShrinkForOrderType;this list is shrinked to a list wich contains only     */
/*  entries where KdAuftragArt > "" and  where                                */
/*  Returns number of entries remaining in the list.                          */
/*----------------------------------------------------------------------------*/
int
pxCustRouteWeekList :: ShrinkForOrderType
(
)
{
    pxCustRouteWeek* route;
    pxCustRouteWeekListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRouteWeek*) ++cursor) != NULL )
    {
        nString aa(route->KdAuftragArt());
        aa.Strip();                        // strip off blanks
        if ( aa.IsEmpty() )
            delete cursor.Remove();
    }
    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  ShrinkForOrderType;this list is shrinked to a list wich contains only     */
/*  entries where KdAuftragArt > "" and  where     */
/*  Returns number of entries remaining in the list.                          */
/*----------------------------------------------------------------------------*/
int
pxCustRouteWeekList :: ShrinkForOrderType
(
    const nString& KdAuftragArt
)
{
    if ( KdAuftragArt.IsEmpty() )
    {
        return static_cast<int>(Entries());
    }
    nString OrderType = KdAuftragArt;
    pxCustRouteWeek* route;
    pxCustRouteWeekListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRouteWeek*) ++cursor) != NULL )
    {
        nString aa(route->KdAuftragArt());
        aa.Strip();                        // strip off blanks
        if (!aa.IsEmpty() && aa.Length() == 1)
        {
            OrderType.Trim(1L);
        }
        if ( aa.IsEmpty() )
            delete cursor.Remove();
        if ( !aa.IsEmpty() && aa != OrderType)
            delete cursor.Remove();
        OrderType = KdAuftragArt;
    }
    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  OrderTypesInList; this method looks for entries with KdAuftragArt > ""    */
/*  If found one, true is returned, otherwise false                           */
/*----------------------------------------------------------------------------*/
bool
pxCustRouteWeekList :: OrderTypesInList
(
)
{
    bool retval = false;
    pxCustRouteWeek* route;
    pxCustRouteWeekListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRouteWeek*) ++cursor) != NULL )
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
pxCustRouteWeekList :: IsOrderTypeInList
(
    const nString& KdAuftragArt
)
{
    bool retval = false;
    pxCustRouteWeek* route;
    nString OrderType = KdAuftragArt;
    pxCustRouteWeekListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRouteWeek*) ++cursor) != NULL )
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
/*  list. Please take care for a well contructed pxCustRouteWeekList          */
/*----------------------------------------------------------------------------*/
pxCustRouteWeekList*
pxCustRouteWeekList :: NewList
(
)
{
    pxCustRouteWeekList* newlist = NULL;
    pxCustRouteWeek* route;
    pxCustRouteWeek* newentry;
    newlist = new pxCustRouteWeekList(Session());
    pxCustRouteWeekListIter cursor(*this);   // define an iterator
    while ( (route = (pxCustRouteWeek*) ++cursor) != NULL )
    {
        newentry = new pxCustRouteWeek(*route);
        newlist->Append(newentry);
    }
    return newlist;
}

/*----------------------------------------------------------------------------*/
/*  Find:this methode looks for entries depending dayofweek and TourId        */
/*  If no entry is found, which matches dayofweek and TourId, a false        */
/*  is returned, otherwise, true will be returned                            */
/*  Please take care for a well construncted list container                   */
/*----------------------------------------------------------------------------*/
bool
pxCustRouteWeekList :: Find
(
    const nString&    TourId,
    const long       dayofweek
)
{
    bool retval = false;
    pxCustRouteWeekListIter cursor(*this);
    pxCustRouteWeek* entryp = NULL;

    while ( (entryp = (pxCustRouteWeek*) ++cursor) != NULL )
    {
        if ( entryp->WeekDay() == dayofweek && entryp->TourId() == TourId )
        {
            retval = true;
            break;
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetEntry:this methode looks for entries depending dayofweek and TourId    */
/*  If no entry is found, NULLP returns, otherwise pointer to matching entry  */
/*  Please take care for a well construncted list container                   */
/*----------------------------------------------------------------------------*/
pxCustRouteWeek*
pxCustRouteWeekList :: GetEntry
(
    const nString&    TourId,
    const long       dayofweek
)
{
    pxCustRouteWeekListIter cursor(*this);
    pxCustRouteWeek* entryp = NULL;

    while ( (entryp = (pxCustRouteWeek*) ++cursor) != NULL )
    {
        if ( entryp->WeekDay() == dayofweek && entryp->TourId() == TourId )
        {
            break;
        }
    }
    return entryp;
}

/*----------------------------------------------------------------------------*/
/*  GetNextTourId: find the next TourId higher then TourId                    */
/*  If no entry is found,  a false  is returned, otherwise, true will be      */
/*  returned                                                                  */
/*  is returned, otherwise, true will be returned                             */
/*  Please take care for a well construncted list container                   */
/*----------------------------------------------------------------------------*/
nString
pxCustRouteWeekList :: GetNextTourId
(
    const nString&    tourId,
    const long       dayofweek
)
{
    nString retval;
    retval.Strip();
    pxCustRouteWeekListIter cursor(*this);
    pxCustRouteWeek* entryp = NULL;
    long tour = atol(tourId);
    tour = tour / 100;

    while ( (entryp = (pxCustRouteWeek*) ++cursor) != NULL )
    {
        if ( entryp->WeekDay() ==  dayofweek )
        {
            long ctour = atol((char*)(nString)(entryp->TourId())(0, 4));
            if ( ctour > tour )
            {
                retval = entryp->TourId();
                break;
            }
        }
    }
    return retval;
}
