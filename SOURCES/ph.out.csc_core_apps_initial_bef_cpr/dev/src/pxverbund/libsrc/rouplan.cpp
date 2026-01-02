/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-1995 by NORDAT Network GmbH
                              All rights reserved

Implementation of class pxRoute methods.

REVISION HISTORY

8 Aug 1995 V1.00 REV 00 written by Dietmar Schloetel.
*/

#include "pxroute.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxRoute :: pxRoute
(
    pxSession *session
)
    :pxDBRecord(session)
{
    Init();
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRoute :: pxRoute
(
    const pxRoute& src
)
    : pxDBRecord(((pxRoute&) src).Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTOUR structure to construct this instance.                           */
/*----------------------------------------------------------------------------*/
pxRoute :: pxRoute
(
    pxSession   *session,
    tTOUR&      src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}


/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxRoute :: pxRoute
(
    pxSession      *session,
    const nString& TourId,                     // Read via string input
    const nDate&   DatumKommi,
    short FilialNr,
    DBAccessMode   mode
)
    : pxDBRecord(session)
{
    Init();
    TourId_ = TourId;
    DateTimePick_ = DatumKommi;
    FilialNr_ = FilialNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxRoute :: ~pxRoute()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTOUR structure.               */
/*----------------------------------------------------------------------------*/
tTOUR&
Assign
(
    tTOUR&     dest,
    const pxRoute& src
)
{
    dest.TourId[0] = ' ';
    src.TourId_.GetData(dest.TourId);
    dest.DatumKommi      = (src.DatumKommi()).GetYYYYMMDD();
    dest.ZeitKoEnde      = (src.ZeitKommiEnde()).GetHHMMSS();
    dest.DatumVersand    = (src.DatumVersand()).GetYYYYMMDD();
    dest.ZeitVersand     = (src.ZeitVersand()).GetHHMMSS();
    dest.BahnhofVersand  = src.BahnhofVersand_;
    dest.TourStat        = static_cast<char>(src.TourStat_);
    dest.LagRechTour     = src.LagRechTour_;
    dest.FilialNr        = src.FilialNr_;
    dest.KdAuftragArt[0] = ' ';
    src.KdAuftragArt_.GetData(dest.KdAuftragArt);
    dest.TourInaktiv     = src.TourInaktiv_;
    dest.ErsatzFilialNr  = src.ErsatzFilialNr_;
    dest.KippZeit        = src.KippZeit();
    dest.CheckTimeToTour = src.CheckTimeToTour_;
    dest.ScheckOrder     = src.ScheckOrder_;
    dest.KarenzZeit      = src.KarenzZeit_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTOUR structure to a pxRoute object.       */
/*----------------------------------------------------------------------------*/
pxRoute&
Assign
(
    pxRoute&    dest,
    const tTOUR&  src
)
{
    nDate    date(src.DatumKommi);
    nClock   clock(src.ZeitKoEnde);
    dest.DateTimePick_ = nTime((int)date.GetYear(),
                               (int)date.GetMonth(),
                               (int)date.GetDay(),
                               (int)clock.GetHours(),
                               (int)clock.GetMinutes(),
                               (int)clock.GetSeconds());
    date = nDate(src.DatumVersand);
    clock = src.ZeitVersand;
    dest.DateTimeShip_ = nTime((int)date.GetYear(),
                               (int)date.GetMonth(),
                               (int)date.GetDay(),
                               (int)clock.GetHours(),
                               (int)clock.GetMinutes(),
                               (int)clock.GetSeconds());
    dest.TourId_         = src.TourId;
    dest.BahnhofVersand_ = src.BahnhofVersand;

    //dest.TourStat_       = (pxRoute::tRouteState)(src.TourStat-48);
    dest.TourStat_ = pxRoute::RouteStateDefault;

    /*
    if( '0' == src.TourStat )
    {
        dest.TourStat_ = pxRoute::RouteStateDefault;
    }
    else if( '1' == src.TourStat )
    {
        dest.TourStat_ = pxRoute::PickingInProgress;
    }
    else if( '2' == src.TourStat )
    {
        dest.TourStat_ = pxRoute::ClosedForOrderEntry;
    }
    else if( '4' == src.TourStat )
    {
        dest.TourStat_ = pxRoute::DeliveryInProgress;
    }
    else
    {
        dest.TourStat_ = pxRoute::RouteStateDefault;
    }
    */

    dest.LagRechTour_    = src.LagRechTour;
    dest.FilialNr_       = src.FilialNr;
    dest.KdAuftragArt_   = src.KdAuftragArt;
    dest.TourInaktiv_    = src.TourInaktiv;
    dest.ErsatzFilialNr_ = src.ErsatzFilialNr;
    dest.TiltingTime_    = src.KippZeit;
    dest.CheckTimeToTour_ = src.CheckTimeToTour;
    dest.ScheckOrder_    = src.ScheckOrder;
    dest.KarenzZeit_     = src.KarenzZeit;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxRoute :: Init()
{
    tTOUR    record;
    memset(&record, 0 , sizeof(tTOUR));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tTOUR               */
/*  struct and then imported to self.                                         */
/*----------------------------------------------------------------------------*/
pxRoute&
pxRoute :: operator=( const pxRoute& src)
{
    tTOUR    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTOUR structure to this instance.                */
/*----------------------------------------------------------------------------*/
pxRoute&
pxRoute :: operator=( const tTOUR& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxRoute :: Get
(
    DBAccessMode mode
)
{
    tTOUR record;
    memset(&record, 0, sizeof(tTOUR));
    //Assign(record, *this);              // easily gets keys
    TourId_.GetData(record.TourId);
    record.DatumKommi      = (DatumKommi()).GetYYYYMMDD();
    record.FilialNr = FilialNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;                 // import the data from tTOUR struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*----------------------------------------------------------------------------*/
int
pxRoute :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxRoute* that = (pxRoute *) That;
    int   retval = ( DateTimeShip_ == that->DateTimeShip_) ? 0
                 : (DateTimeShip_ > that->DateTimeShip_ ? 1 : -1);
    if ( retval == 0 )
        retval = ( TourId_ == that->TourId_) ? 0
               : (TourId_ > that->TourId_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxRoute :: Read
(
    const void  *record
)
{
    return pxTourRead((tTOUR*)record);
}

/*----------------------------------------------------------------------------*/
/*  Methods of pxRouteList class.                                              */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxRouteList :: pxRouteList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using single string value arguments.                 */
/*----------------------------------------------------------------------------*/
size_t
pxRouteList :: Select
(
    const nDate&   date,
    const int     count_                // Max number of records to read
)
{
    tTOUR record;
    memset(&record, 0, sizeof(tTOUR));     // zero out entire record buffer
    record.DatumKommi = date.GetYYYYMMDD(); // store selection key
    return Select(&record, count_);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tTOUR structure.       */
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxRouteList :: Select
(
    tTOUR       *recordp,
    const int  count_
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
pxRouteList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    pxRoute *objectp = new pxRoute(Session(),*(tTOUR*) record); // construct new object
    InsertAscending(objectp);
    return objectp;
}

int
pxRouteList :: EndBrowse
(
    const int  cursorid
)
{
    return pxTourEndBrowse(cursorid);
}

int
pxRouteList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxTourGetNext((tTOUR*)record, cursorid);
}

int
pxRouteList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxTourStartBrowse((tTOUR*)keys, cursorid);
}
