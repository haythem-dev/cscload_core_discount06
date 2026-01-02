#include "pxtaskcl.hpp"
#include <pxdbxx.h>
#include <time.hpp>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxTaskControl :: pxTaskControl
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
pxTaskControl :: pxTaskControl
(
    pxTaskControl& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTASKCONTROL structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxTaskControl :: pxTaskControl
(
    pxSession   *session,
    tTASKCONTROL& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Init  constructor.                                                        */
/*----------------------------------------------------------------------------*/
pxTaskControl :: pxTaskControl
(
    pxSession    *session,
    short       Vz,                     // Vertriebszentrumnr
    nString      ProgName                // Programname
)
    : pxDBRecord(session)
{
    Init();
    VertriebszentrumNr_ = Vz;
    ProgrammName_       = ProgName;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxTaskControl :: ~pxTaskControl()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTASKCONTROL structure.     */
/*----------------------------------------------------------------------------*/
tTASKCONTROL&
Assign
(
    tTASKCONTROL&           dest,
    const pxTaskControl&     src
)
{
    dest.VertriebszentrumNr =  src.VertriebszentrumNr_ ;
    dest.ZeitUnix           = src.ZeitUnix_            ;
    strcpy(dest.ProgrammName,    " ")                  ;
    src.ProgrammName_.GetData(dest.ProgrammName)       ;


    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTASKCONTROL structure to               */
/*  a pxTaskControl object.                                                  */
/*----------------------------------------------------------------------------*/
pxTaskControl&
Assign
(
    pxTaskControl&              dest,
    const tTASKCONTROL&         src
)
{
    dest.VertriebszentrumNr_ =  src.VertriebszentrumNr ;
    dest.ProgrammName_       =  src.ProgrammName       ;
    dest.ZeitUnix_           =  src.ZeitUnix           ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxTaskControl :: Init()
{
    tTASKCONTROL    record;
    memset(&record, 0 , sizeof(tTASKCONTROL));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tTASKCONTROL struct and then imported to self.                         */
/*----------------------------------------------------------------------------*/
pxTaskControl&
pxTaskControl :: operator=( const pxTaskControl& src)
{
    tTASKCONTROL record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTASKCONTROL structure 'src' to               */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxTaskControl&
pxTaskControl :: operator=( const tTASKCONTROL& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxTaskControl :: Get
(
    DBAccessMode mode
)

{
    tTASKCONTROL record;
    memset(&record, 0, sizeof(tTASKCONTROL));
    Assign(record, *this);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tTASKCONTROL struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_TASKCNTL_NOTFOUND, VertriebszentrumNr_, ProgrammName_());
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxTaskControl :: Put
(
)
{
    tTASKCONTROL record;
    memset(&record, 0, sizeof(tTASKCONTROL));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tTASKCONTROL));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxTaskControl :: Delete
(
)
{
    tTASKCONTROL record;
    memset(&record, 0, sizeof(tTASKCONTROL));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Insert or update taskcontrolentry                                         */
/*  take care for a well contructed object                                    */
/*----------------------------------------------------------------------------*/
int
pxTaskControl :: TaskControl
(
    nTime&   t
)
{
    Get( cDBGET_FORUPDATE );
    ZeitUnix_ = static_cast<long>(t.GetSecs());
    return Put();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxTaskControl :: Read
(
    const void  *record
)
{
    return pxTaskControlRead((tTASKCONTROL*)record);
}

int
pxTaskControl :: ReadLock
(
    const void  *record
)
{
    return pxTaskControlReadLock((tTASKCONTROL*)record);
}

int
pxTaskControl :: Update
(
    const void  *record
)
{
    return pxTaskControlUpdate((tTASKCONTROL*)record);
}

int
pxTaskControl :: Delete
(
    const void  *record
)
{
    return pxTaskControlDelete((tTASKCONTROL*)record);
}

int
pxTaskControl :: Insert
(
    const void  *record
)
{
    return pxTaskControlInsert((tTASKCONTROL*)record);
}

int
pxTaskControlList :: EndBrowse
(
    const int  cursorid
)
{
    return pxTaskControlEndBrowse(cursorid);
}


int
pxTaskControlList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxTaskControlGetNext((tTASKCONTROL*)record, cursorid);
}

int
pxTaskControlList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxTaskControlStartBrowse((tTASKCONTROL*)keys, cursorid);
}
/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxTaskControl list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxTaskControl :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxTaskControl *that = (pxTaskControl*)That;
    int retval = (VertriebszentrumNr_ == that->VertriebszentrumNr_) ? 0
                : (VertriebszentrumNr_ > that->VertriebszentrumNr_ ? 1 : -1);

    if ( retval == 0 )
        retval = (ProgrammName_ == that->ProgrammName_) ? 0
                  : (ProgrammName_ > that->ProgrammName_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTaskControlList :: pxTaskControlList
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
pxTaskControlList :: Select
(
    const int     count_
)
{
    tTASKCONTROL fil;
    memset(&fil, 0, sizeof(tTASKCONTROL));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxTaskControlList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxTaskControl' object:
    pxTaskControl *objectp = new pxTaskControl(Session(), *(tTASKCONTROL*) record);
    InsertAscending(objectp);
    return objectp;
}
