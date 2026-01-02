/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

                 (c) Copyright 1994-2002 by NORDAT Network GmbH
                              All rights reserved

Implementation of class pxStockRevNextDay methods.

REVISION HISTORY

13 Sept 2001 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxstkrev.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxStockRev :: pxStockRev
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
pxStockRev :: pxStockRev
(
    const pxStockRev& src
)
    : pxDBRecord(((pxStockRev&) src).Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use LAGERREVISION structure to construct this instance.                           */
/*----------------------------------------------------------------------------*/
pxStockRev :: pxStockRev
(
    pxSession   *session,
    tLAGERREVISION&      src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}


/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxStockRev :: pxStockRev
(
    pxSession      *session,
    const short   FilialNr,                     // Read via string input
    const long    ArtikelNr,
    DBAccessMode   mode
)
    : pxDBRecord(session)
{
    Init();
    FilialNr_  = FilialNr;
    ArtikelNr_ = ArtikelNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Construct a new Object                                                    */
/*----------------------------------------------------------------------------*/
pxStockRev :: pxStockRev
(
    pxSession      *session,
          short   FilialNr,                     // Read via string input
    const long    ArtikelNr,
    const long    BestandKSC,
    const long    BestandVSE
)
    : pxDBRecord(session)
{
    Init();
        DBAccessMode mode = cDBGET_READONLY;
    nDate      today;
    nClock     ctime;

    Datum_      = today;
    UhrZeit_    = ctime;
    FilialNr_   = FilialNr;
    ArtikelNr_  = ArtikelNr;
    BestandKSC_ = BestandKSC;
    BestandVSE_ = BestandVSE;
    int retval = Get(mode );
    if ( retval )
    {
       Put();
    }
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxStockRev :: ~pxStockRev()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a LAGERREVISION structure.               */
/*----------------------------------------------------------------------------*/
tLAGERREVISION&
Assign
(
    tLAGERREVISION&     dest,
    const pxStockRev& src
)
{
    dest.FilialNr        = src.FilialNr_;
    dest.ArtikelNr       = src.ArtikelNr_;
    dest.Datum           = (src.Datum()).GetYYYYMMDD();
    dest.UhrZeit         = (src.UhrZeit()).GetHHMMSS();
    dest.BestandKSC      = src.BestandKSC_;
    dest.BestandVSE      = src.BestandVSE_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' LAGERREVISION structure to a pxStockRev object.        */
/*----------------------------------------------------------------------------*/
pxStockRev&
Assign
(
    pxStockRev&    dest,
    const tLAGERREVISION&  src
)
{
    dest.FilialNr_       = src.FilialNr;
    dest.ArtikelNr_      = src.ArtikelNr;
    dest.Datum_          = (nDate)src.Datum;
    dest.UhrZeit_        = src.UhrZeit;
    dest.BestandKSC_     = src.BestandKSC;
    dest.BestandVSE_     = src.BestandVSE;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxStockRev :: Init()
{
    tLAGERREVISION    record;
    memset(&record, 0 , sizeof(tLAGERREVISION));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the LAGERREVISION               */
/*  struct and then imported to self.                                         */
/*----------------------------------------------------------------------------*/
pxStockRev&
pxStockRev :: operator=( const pxStockRev& src)
{
    tLAGERREVISION    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the LAGERREVISION structure to this instance.                */
/*----------------------------------------------------------------------------*/
pxStockRev&
pxStockRev :: operator=( const tLAGERREVISION& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxStockRev :: Get
(
    DBAccessMode mode
)

{
    tLAGERREVISION record;
    memset(&record, 0, sizeof(tLAGERREVISION));
    //Assign(record, *this);              // easily gets keys
    record.FilialNr  = FilialNr_;
    record.ArtikelNr = ArtikelNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record)
                                               : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from LAGERREVISION struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxStockRev :: Put
(
)
{
    tLAGERREVISION record;
    memset(&record, 0, sizeof(tLAGERREVISION));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tLAGERREVISION));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxStockRev :: Delete
(
)
{
    tLAGERREVISION record;
    memset(&record, 0, sizeof(tLAGERREVISION));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*----------------------------------------------------------------------------*/
int
pxStockRev :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxStockRev* that = (pxStockRev *) That;
    int   retval = ( FilialNr_ == that->FilialNr_) ? 0
                  : (FilialNr_ > that->FilialNr_ ? 1 : -1);
    if ( retval == 0 )
       retval = ( ArtikelNr_ == that->ArtikelNr_) ? 0
                   : (ArtikelNr_ > that->ArtikelNr_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxStockRev :: Read
(
    const void  *record
)
{

    return pxLagerRevisionRead((tLAGERREVISION*)record);
}

int
pxStockRev :: Delete
(
    const void  *record
)
{
    return pxLagerRevisionDelete((tLAGERREVISION*)record);
}

int
pxStockRev :: Insert
(
    const void  *record
)
{
    return pxLagerRevisionInsert((tLAGERREVISION*)record);
}

/*----------------------------------------------------------------------------*/
/*  Methods of pxStockRevList class.                                              */
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*  Constructor.                                                              */
/*----------------------------------------------------------------------------*/
pxStockRevList :: pxStockRevList
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
/*size_t
pxStockRevList :: Select
(
    const nDate&   date,
    const int     count_                // Max number of records to read
)

{

    tLAGERREVISION record;
    memset(&record, 0, sizeof(tLAGERREVISION));     // zero out entire record buffer
    record.Datum = date.GetYYYYMMDD(); // store selection key
    return Select(&record, count_);
}*/

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a LAGERREVISION structure.       */
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxStockRevList :: Select
(
    const short   FilialNr,
    const long    ArtikelNr,
    const int     count_                // Max number of records to read
)

{

    tLAGERREVISION record;
    memset(&record, 0, sizeof(tLAGERREVISION));     // zero out entire record buffer
    record.FilialNr  = FilialNr;                    // store selection key
    record.ArtikelNr = ArtikelNr;                   // store selection key
    return Select(&record, count_);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a LAGERREVISION structure.       */
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxStockRevList :: Select
(
    tLAGERREVISION       *recordp,
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
pxStockRevList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    pxStockRev *objectp = new pxStockRev(Session(),*(tLAGERREVISION*) record); // construct new object
    InsertAscending(objectp);
    return objectp;
}

int
pxStockRevList :: EndBrowse
(
    const int  cursorid
)
{

    return pxLagerRevisionEndBrowse(cursorid);
}


int
pxStockRevList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{

    return pxLagerRevisionGetNext((tLAGERREVISION*)record, cursorid);
}

int
pxStockRevList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{

    return pxLagerRevisionStartBrowse((tLAGERREVISION*)keys, cursorid);
}
