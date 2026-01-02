#include "pxttype.hpp"
#include <pxdbxx.h>
#include <date.hpp>
#include <nntypes.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxTimeType :: pxTimeType
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
pxTimeType :: pxTimeType
(
    pxTimeType& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tZEITARTEN structure to construct this instance.                      */
/*----------------------------------------------------------------------------*/
pxTimeType :: pxTimeType
(
    pxSession   *session,
    tZEITARTEN& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTimeType :: pxTimeType
(
    pxSession   *session,
    long       ZeitArt,
    const nString& ZeitSchluessel,
    const short WeekDay,
    short VertriebszentrumNr,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    ZeitArt_        = ZeitArt;
    ZeitSchluessel_ = ZeitSchluessel;
    WeekDay_        = WeekDay;
    VertriebszentrumNr_ = VertriebszentrumNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxTimeType :: ~pxTimeType()
{
//  delete subobjects;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tZEITARTEN structure           */
/*----------------------------------------------------------------------------*/
tZEITARTEN&
Assign
(
          tZEITARTEN&      dest,
    const pxTimeType&      src
)
{
    // Copy native data types:
    dest.LfdNr              = src.LfdNr_                      ;
    dest.ZeitArt            = src.ZeitArt_                    ;
    dest.ZeitBegin          = src.ZeitBegin_.GetHHMMSS()      ;
    dest.ZeitEnde           = src.ZeitEnde_.GetHHMMSS()       ;
    dest.ZeitZusatz         = src.ZeitZusatz_                 ;
    dest.VertriebszentrumNr = src.VertriebszentrumNr_;
    dest.WeekDay            = src.WeekDay_;
    // nStrings:
    dest.ZeitSchluessel[0] = ' ';
    src.ZeitSchluessel_.GetData( dest.ZeitSchluessel,
                           (mSIZEOF(tZEITARTEN, ZeitSchluessel)) - 1 );
    dest.TagesTyp[0] = ' ';
    src.TagesTyp_.GetData( dest.TagesTyp,
                           (mSIZEOF(tZEITARTEN, TagesTyp)) - 1 );

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tZEITARTEN structure to a pxTimeype object.      */
/*----------------------------------------------------------------------------*/
pxTimeType&
Assign
(
          pxTimeType&       dest,
    const tZEITARTEN&       src
)
{
    // Copy native data types:
    dest.LfdNr_           = src.LfdNr;
    dest.ZeitArt_         = src.ZeitArt;
    dest.ZeitBegin_       = src.ZeitBegin;
    dest.ZeitEnde_        = src.ZeitEnde;
    dest.ZeitZusatz_      = src.ZeitZusatz;
    dest.VertriebszentrumNr_ = src.VertriebszentrumNr;
    dest.WeekDay_           = src.WeekDay;

    // Strings:
    dest.ZeitSchluessel_  = src.ZeitSchluessel;
    dest.ZeitSchluessel_.Strip();
    dest.TagesTyp_        = src.TagesTyp;
    dest.TagesTyp_.Strip();

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxTimeType :: Init()
{
    tZEITARTEN    record;
    memset(&record, 0 , sizeof(tZEITARTEN));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self. The values of the source */
/*  instance are exported to the tZEITARTEN struct and then imported to self. */
/*----------------------------------------------------------------------------*/
pxTimeType&
pxTimeType :: operator=( const pxTimeType& src)
{
    tZEITARTEN record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tZEITARTEN structure to this instance.           */
/*----------------------------------------------------------------------------*/
pxTimeType&
pxTimeType :: operator=( const tZEITARTEN& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxTimeType :: Get
(
    DBAccessMode mode
)

{
    tZEITARTEN record;
    memset(&record, 0, sizeof(tZEITARTEN));
    record.ZeitArt = ZeitArt_;
    record.WeekDay = WeekDay_;
    ZeitSchluessel_.GetData( record.ZeitSchluessel );
    record.VertriebszentrumNr = VertriebszentrumNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                         nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;           // import the data from tZEITARTEN struct
    else if ( retval > cDBXR_NORMAL )
         DBCondition(nMessage(CMsgStream(),
                            CMSG_TMT_ENTRY_NOTFOUND,
                            record.ZeitArt,
                            record.ZeitSchluessel,
                            record.TagesTyp),
                   CMSG_TMT_NOTIMETYPES);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxTimeType :: Put
(
)
{
    tZEITARTEN record;
    memset(&record, 0, sizeof(tZEITARTEN));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tZEITARTEN));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxTimeType :: Read
(
    const void  *record
)
{
    //  pxFilialeRead in pxdbxx.h vereinbaren
    return pxZeitArtenRead((tZEITARTEN*)record);
}

int
pxTimeType :: ReadLock
(
    const void  *record
)
{
    return pxZeitArtenReadLock((tZEITARTEN*)record);
}

int
pxTimeType :: Update
(
    const void  *record
)
{
    return pxZeitArtenUpdate((tZEITARTEN*)record);
}

int
pxTimeType :: Insert
(
    const void  *record
)
{
    return pxZeitArtenInsert((tZEITARTEN*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxTimeType        */
/*  list objects being inserted in the following ascending sequence:Zeitart,  */
/*  ZeitSchluessel                                                            */
/*----------------------------------------------------------------------------*/
int
pxTimeType :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    int retval      = 0;
    pxTimeType *that = (pxTimeType*)That;

    retval =  (ZeitArt_ == that->ZeitArt_) ? 0
             : (ZeitArt_ < that->ZeitArt_) ? -1 : 1;

    if ( retval == 0 )
       retval = (ZeitSchluessel_ == that->ZeitSchluessel_) ? 0
                      : (ZeitSchluessel_ > that->ZeitSchluessel_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/* Checkt current time against entry timeinwindow                             */
/* Returns true if it does fit, otherwise false                             */
/*----------------------------------------------------------------------------*/
bool
pxTimeType :: TimeInWindow
(
)
{
    nClock ctime;         // current time

    return ( ctime > WindowStart() && ctime < WindowEnd() );
}

/*----------------------------------------------------------------------------*/
/*  Normal list constructor.                                                  */
/*----------------------------------------------------------------------------*/
pxTimeTypeList :: pxTimeTypeList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection by ZeitArt, ZeitSchluessel,Tagestype                     */
/*----------------------------------------------------------------------------*/
size_t
pxTimeTypeList :: Select
(
    const long     ZeitArt,
    const nString&  ZeitSchluessel,
    short VertriebszentrumNr,
    const int      count_
)
{
    nDate    date;
    tZEITARTEN record;
    memset(&record, 0, sizeof(tZEITARTEN));   // zero out record buffer
    record.ZeitArt  = ZeitArt;                // TimeType
    record.ZeitSchluessel[0]   = ' ' ;
    ZeitSchluessel.GetData(record.ZeitSchluessel);
    record.WeekDay  = date.GetDayOfWeek();
    record.VertriebszentrumNr = VertriebszentrumNr;
    nDBSelect(&record, cCRS_DEFAULT, count_);  // Do the selection

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxTimeTypeList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxTimeType  ' object:
    pxTimeType *objectp = new pxTimeType(Session(), *(tZEITARTEN*) record);
    Append(objectp);
    return objectp;
}

int
pxTimeTypeList :: EndBrowse
(
    const int  cursorid
)
{
    return pxZeitArtenEndBrowse(cursorid);
}

int
pxTimeTypeList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxZeitArtenGetNext((tZEITARTEN*)record, cursorid);
}

int
pxTimeTypeList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxZeitArtenStartBrowse((tZEITARTEN*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/* TimeInWindow checks the current time against the timewindow within         */
/* the pxTimeType entries.                                                    */
/* returnvalues: false    = current outside window                           */
/*               true     = current within  window                           */
/*----------------------------------------------------------------------------*/
bool
pxTimeTypeList :: TimeInWindow
(
)
{
    pxTimeTypeListIter   iter(*this);      // define iterator
    pxTimeType           *entryp;          // entrypointer
    bool                 retval = false;   // return value
    nClock               ctime;            // current time
    iter.Reset();                          // top of list

    while ( ( entryp = ( pxTimeType *) ++iter) != NULL )
    {
       if ( ctime > entryp->WindowStart() && ctime < entryp->WindowEnd())
       {
          retval = true ;
          break;
       }
    }

    return   retval;
}
/*----------------------------------------------------------------------------*/
/* Find looks for an entry where filialnr = entry->filialnr and the current   */
/* time does fit the entry->timeinwindow                                      */
/* entryp  is returned on match                                               */
/*----------------------------------------------------------------------------*/
pxTimeType*
pxTimeTypeList :: Find
(
    const short FilialNr
)
{
    pxTimeTypeListIter   iter(*this);      // define iterator
    pxTimeType           *entryp;          // entrypointer
    // unused variable
    // int                 retval = 0;       // return value
    nClock               ctime;            // current time
    nString key;
    key = FilialNr;
    iter.Reset();                          // top of list

    while ( ( entryp = ( pxTimeType *) ++iter) != NULL )
    {
       if ( (entryp->TimeKey() == key) && entryp->TimeInWindow() )
       {
          break;
       }
    }

    return   entryp;
}
/*----------------------------------------------------------------------------*/
/* FindDayOfWeek looks for the corresponding day of week within the           */
/* table. if found, true will be returned.                                    */
/*----------------------------------------------------------------------------*/
bool
pxTimeTypeList :: FindDayOfWeek
(
    const short dow
)
{
    pxTimeTypeListIter   iter(*this);      // define iterator
    pxTimeType           *entryp;          // entrypointer
    bool                 retval = false;   // return value
    iter.Reset();                          // top of list

    while ( ( entryp = ( pxTimeType *) ++iter) != NULL )
    {
       if ( entryp->WeekDay() == dow )
       {
          retval = true;
          break;
       }
    }

    return retval;
}
