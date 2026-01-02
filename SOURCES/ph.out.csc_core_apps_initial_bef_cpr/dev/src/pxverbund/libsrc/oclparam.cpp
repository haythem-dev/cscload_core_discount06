#include "pxoclpar.hpp"
#include "pxocldef.h"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

static const char* ORIGINNAMES[] = {"VB", "CL", "ER", "LA", "LV", "IR","SH","KF","UE","PI","UW","GO","ES", "CO", "RI", "BC", "DC", "VU", "CC", "IT"};

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderCloseParam :: pxOrderCloseParam
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
pxOrderCloseParam :: pxOrderCloseParam
(
    pxOrderCloseParam& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGENDEZEIT structure to construct this instance.              */
/*----------------------------------------------------------------------------*/
pxOrderCloseParam :: pxOrderCloseParam
(
    pxSession   *session,
    tKDAUFTRAGENDEZEIT& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxOrderCloseParam :: pxOrderCloseParam
(
    pxSession   *session,
    short      FilialNr,                 // Read via this type
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    FilialNr_ = FilialNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderCloseParam :: ~pxOrderCloseParam()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGENDEZEIT structure.  */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGENDEZEIT&
Assign
(
    tKDAUFTRAGENDEZEIT&        dest,
    const pxOrderCloseParam&         src
)
{
    dest.FilialNr                 = src.FilialNr_                      ;
    dest.BatchSchreiben           = src.BatchSchreiben_                ;
    dest.HerkunftsFilialNr        = src.HerkunftsFilialNr_             ;
    dest.AbschlussModus           = src.AbschlussModus_                ;
    dest.AbschlussZeit            = src.AbschlussZeit_.GetHHMMSS()     ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGENDEZEIT structure to            */
/*  a pxOrderCloseParam object.                                               */
/*----------------------------------------------------------------------------*/
pxOrderCloseParam&
Assign
(
    pxOrderCloseParam&              dest,
    const tKDAUFTRAGENDEZEIT&  src
)
{
    dest.FilialNr_                   = src.FilialNr                    ;
    dest.BatchSchreiben_             = static_cast<OriginTypeEnum>(src.BatchSchreiben);
    dest.HerkunftsFilialNr_          = src.HerkunftsFilialNr           ;
    dest.AbschlussModus_             = src.AbschlussModus              ;
    dest.AbschlussZeit_              = src.AbschlussZeit               ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderCloseParam :: Init()
{
    tKDAUFTRAGENDEZEIT    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGENDEZEIT));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGENDEZEIT struct and then imported to self.                      */
/*----------------------------------------------------------------------------*/
pxOrderCloseParam&
pxOrderCloseParam :: operator=( const pxOrderCloseParam& src)
{
    tKDAUFTRAGENDEZEIT record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGENDEZEIT structure 'src' to            */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxOrderCloseParam&
pxOrderCloseParam :: operator=( const tKDAUFTRAGENDEZEIT& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderCloseParam :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGENDEZEIT record;
    memset(&record, 0, sizeof(tKDAUFTRAGENDEZEIT));
    //record.FilialNr = FilialNr_;
    Assign(record, *this);

    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKDAUFTRAGENDEZEIT struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(), CMSG_OCL_PARAM_NOTFOUND, FilialNr_);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderCloseParam :: Put
(
)
{
    tKDAUFTRAGENDEZEIT record;
    memset(&record, 0, sizeof(tKDAUFTRAGENDEZEIT));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGENDEZEIT));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOrderCloseParam :: Read
(
    const void  *record
)
{
    return pxAuftragEndeZeitRead((tKDAUFTRAGENDEZEIT*)record);
}

int
pxOrderCloseParam :: ReadLock
(
    const void  *record
)
{
    return pxAuftragEndeZeitReadLock((tKDAUFTRAGENDEZEIT*)record);
}

int
pxOrderCloseParam :: Update
(
    const void  *record
)
{
    return pxAuftragEndeZeitUpdate((tKDAUFTRAGENDEZEIT*)record);
}

int
pxOrderCloseParam :: Insert
(
    const void  *record
)
{
    return pxAuftragEndeZeitInsert((tKDAUFTRAGENDEZEIT*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxOrderCloseParam list objects being inserted in the              */
/*  following ascending sequence:                                             */
/*  (FilialNr)                                                                */
/*  BatchSchreiben                                                            */
/*  HerkunftsFilialeNr                                                        */
/*  AbschlussModus                                                            */
/*----------------------------------------------------------------------------*/
int
pxOrderCloseParam :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOrderCloseParam *that = (pxOrderCloseParam*)That;
    int retval;
    if (BatchSchreiben_ > that->BatchSchreiben_)
        retval = 1;
    else if (BatchSchreiben_ < that->BatchSchreiben_)
        retval = -1;
    else
    {
        if (HerkunftsFilialNr_ > that->HerkunftsFilialNr_)
            retval = 1;
        else if (HerkunftsFilialNr_ < that->HerkunftsFilialNr_)
            retval = -1;
        else
            if (AbschlussModus_ > that->AbschlussModus_)
                retval = 1;
            else if (AbschlussModus_ < that->AbschlussModus_)
                retval = -1;
        else
        {
            if (AbschlussZeit_ > that->AbschlussZeit_)
                retval = 1;
            else if (AbschlussZeit_ < that->AbschlussZeit_)
                retval = -1;
            else
                retval = 0;
        }
    }

    return retval;
}

bool pxOrderCloseParam :: IsCloseModeImmediate()
{
    return (AbschlussModus_ == cOCL_MODE_IMMEDIATE);
}

bool pxOrderCloseParam :: IsCloseModeOnce()
{
    return (AbschlussModus_ == cOCL_MODE_ONCE);
}

bool pxOrderCloseParam :: IsCloseModePermanent()
{
    return (AbschlussModus_ == cOCL_MODE_PERMANENT);
}

bool pxOrderCloseParam :: IsCloseModeInternal()
{
    return (AbschlussModus_ == cOCL_MODE_INTERNAL);
}

bool pxOrderCloseParam :: SetModeInternal()
{
    if (IsCloseModeOnce())
        AbschlussModus_ = cOCL_MODE_INTERNAL;
    return IsCloseModeInternal();
}

bool pxOrderCloseParam :: SetModeOnce()
{
    if (IsCloseModeInternal())
        AbschlussModus_ = cOCL_MODE_ONCE;
    return IsCloseModeOnce();
}

/*----------------------------------------------------------------------------*/
/*  Convert enum type into string                                             */
/*----------------------------------------------------------------------------*/
nString pxOrderCloseParam :: ConvertBatchSchreiben
(
    OriginTypeEnum nr
)
{
    nString retvalue_;

    if (nr > 0 && nr <= (long)(sizeof(ORIGINNAMES) / sizeof(char*)) )
        retvalue_ = ORIGINNAMES[nr-1];

    return retvalue_;
}

/*----------------------------------------------------------------------------*/
/*  Convert nString into enum type                                            */
/*----------------------------------------------------------------------------*/
OriginTypeEnum pxOrderCloseParam :: ConvertBatchSchreiben
(
    const nString& batstr
)
{
    long retvalue_;
    nString kopi_ = batstr;
    kopi_.ToUpper();

    for (retvalue_ = 1;
        retvalue_-1 < (long)(sizeof(ORIGINNAMES) / sizeof(char*)) && kopi_ != nString(ORIGINNAMES[retvalue_-1]);
        ++retvalue_);

    if (retvalue_ > (long)(sizeof(ORIGINNAMES) / sizeof(char*)) )
        retvalue_ = 0;

    return static_cast<OriginTypeEnum>(retvalue_);
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderCloseParamList :: pxOrderCloseParamList
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
pxOrderCloseParamList :: Select
(
    const short FilialNr,
    const int     count_
)
{
    tKDAUFTRAGENDEZEIT fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGENDEZEIT));  // zero out entire record buffer
    fil.FilialNr = FilialNr;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderCloseParamList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxOrderCloseParam' object:
    pxOrderCloseParam *objectp = new pxOrderCloseParam(Session(), *(tKDAUFTRAGENDEZEIT*) record);
    InsertAscending(objectp);
    return objectp;
}

int
pxOrderCloseParamList :: EndBrowse
(
    const int  cursorid
)
{
    return pxAuftragEndeZeitEndBrowse(cursorid);
}


int
pxOrderCloseParamList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxAuftragEndeZeitGetNext((tKDAUFTRAGENDEZEIT*)record, cursorid);
}

int
pxOrderCloseParamList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxAuftragEndeZeitStartBrowse((tKDAUFTRAGENDEZEIT*)keys, cursorid);
}
/*----------------------------------------------------------------------------*/
/* Returns the pointer to the corresponding entry within the list.            */
/* NULL returns if the wanted entry is not found within the list.             */
/*----------------------------------------------------------------------------*/
pxOrderCloseParam*
pxOrderCloseParamList :: FindHerkunftsFilialNr
(
    short   HerkunftsFilialNr
)
{
    pxOrderCloseParamListIter  iter(*this);  // iterator OCL
    pxOrderCloseParam         *entry;

    iter.Reset();                          // top of list
    while ( ( entry = ( pxOrderCloseParam *) ++iter) != NULL )
    {
       if ( HerkunftsFilialNr == entry->HerkunftsFilialNr() )
       {
          break;
       }
    }

    return entry;
}

/*----------------------------------------------------------------------------*/
/* Returns the pointer to the corresponding entry within the list.            */
/* NULL returns if the wanted entry is not found within the list.             */
/*----------------------------------------------------------------------------*/
pxOrderCloseParam*
pxOrderCloseParamList :: Find
(
    OriginTypeEnum BatchSchreiben,
    short   HerkunftsFilialNr
)
{
    pxOrderCloseParamListIter  iter(*this);  // iterator OCL
    pxOrderCloseParam         *entry;

    iter.Reset();                          // top of list
    while ( ( entry = ( pxOrderCloseParam *) ++iter) != NULL )
    {
       if ( BatchSchreiben == entry->BatchSchreiben() &&
            HerkunftsFilialNr == entry->HerkunftsFilialNr() )
       {
          break;
       }
    }

    return entry;
}

/*----------------------------------------------------------------------------*/
/* Returns True if entry found with corresponding Batchschreiben given        */
/* by parameter, otherwise False is returned.                                 */
/*----------------------------------------------------------------------------*/
pxOrderCloseParam*
pxOrderCloseParamList :: FindBatchSchreiben
(
    OriginTypeEnum BatchSchreiben
)
{
    pxOrderCloseParamListIter  iter(*this);  // iterator OCL
    pxOrderCloseParam         *entry;

    iter.Reset();                          // top of list
    while ( ( entry = ( pxOrderCloseParam *) ++iter) != NULL )
    {
       if ( BatchSchreiben == entry->BatchSchreiben())
       {
          break;
       }
    }

    return entry;
}
