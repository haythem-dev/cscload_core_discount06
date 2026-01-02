/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxOeOriginTypes methods.

REVISION HISTORY

06 Aug 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxoeorigintypes.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOeOriginTypes :: pxOeOriginTypes
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
pxOeOriginTypes :: pxOeOriginTypes
(
    pxOeOriginTypes& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERPROUP structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxOeOriginTypes :: pxOeOriginTypes
(
    pxSession   *session,
    tOEORIGINTYPES& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxOeOriginTypes :: pxOeOriginTypes
(
    pxSession   *session,
    short      OriginType,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    OriginType_        = OriginType;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOeOriginTypes :: ~pxOeOriginTypes()
{
        ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tOEORIGINTYPES structure.       */
/*----------------------------------------------------------------------------*/
tOEORIGINTYPES&
Assign
(
    tOEORIGINTYPES&    dest,
    const pxOeOriginTypes&  src
)
{
    // Copy native data types:
    dest.OriginType        = src.OriginType_;
    // Strings:
    dest.OriginDevice[0] = ' ';
    src.OriginDevice_.GetData(dest.OriginDevice);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' structure to a pxOeOriginTypes object.     */
/*----------------------------------------------------------------------------*/
pxOeOriginTypes&
Assign
(
    pxOeOriginTypes&           dest,
    const tOEORIGINTYPES&   src
)
{
    dest.OriginType_        = src.OriginType;
    dest.OriginDevice_      = src.OriginDevice;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOeOriginTypes :: Init()
{
    tOEORIGINTYPES    record;
    memset(&record, 0 , sizeof(tOEORIGINTYPES));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tOEORIGINTYPES struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxOeOriginTypes&
pxOeOriginTypes :: operator=( const pxOeOriginTypes& src)
{
    tOEORIGINTYPES record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tOEORIGINTYPES structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxOeOriginTypes&
pxOeOriginTypes :: operator=( const tOEORIGINTYPES& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOeOriginTypes :: Get
(
    DBAccessMode mode
)

{
    tOEORIGINTYPES record;
    memset(&record, 0, sizeof(tOEORIGINTYPES));
    record.OriginType        = OriginType_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;             // import the data from tOEORIGINTYPES struct
    /*se if ( retval > cDBXR_NORMAL )
       DBCondition(nMessage(CMsgStream(),
                            CMSG_CST_GRP_NOTFOUND,
                            record.CustomerGroupNo, 0),
                   CMSG_CST_GRP_NOTFOUND);
    */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxOeOriginTypes :: Put
(
)
{
    tOEORIGINTYPES record;
    memset(&record, 0, sizeof(tOEORIGINTYPES));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tOEORIGINTYPES));
}


/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOeOriginTypes :: Read
(
    const void  *record
)
{
    return pxOeOriginTypesRead((tOEORIGINTYPES*)record);
}

int
pxOeOriginTypes :: ReadLock
(
    const void  *record
)
{
    return pxOeOriginTypesReadLock((tOEORIGINTYPES*)record);
}

int
pxOeOriginTypes :: Update
(
    const void  *record
)
{
    return pxOeOriginTypesUpdate((tOEORIGINTYPES*)record);
}

int
pxOeOriginTypes :: Insert
(
    const void  *record
)
{
    return pxOeOriginTypesInsert((tOEORIGINTYPES*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxOeOriginTypes list  */
/*  objects being inserted in the following ascending sequence: KdGruppe.     */
/*----------------------------------------------------------------------------*/
int
pxOeOriginTypes :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOeOriginTypes *that = (pxOeOriginTypes*)That;
    int retval = (OriginType_ == that->OriginType_) ? 0
                : (OriginType_ > that->OriginType_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOeOriginTypesList :: pxOeOriginTypesList
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
pxOeOriginTypesList :: Select
(
    const int     count_
)
{
    tOEORIGINTYPES record;
    memset(&record, 0, sizeof(tOEORIGINTYPES));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxOeOriginTypesList :: Select
(
    const nString&   OriginDevice,
    const int     count_
)
{
    tOEORIGINTYPES record;
    memset(&record, 0, sizeof(tOEORIGINTYPES));  // zero out entire record buffer
    record.OriginDevice[0] = ' ';
    OriginDevice.GetData(record.OriginDevice);
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOeOriginTypesList :: AddToList
(
    const void  *recordp,
    const int  /* row */
)
{
    // construct new 'pxOeOriginTypes' object:
    pxOeOriginTypes *objectp = new pxOeOriginTypes(Session(), *(tOEORIGINTYPES*)recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxOeOriginTypesList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOeOriginTypesEndBrowse(cursorid);
}


int
pxOeOriginTypesList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxOeOriginTypesGetNext((tOEORIGINTYPES*)recordp, cursorid);
}

int
pxOeOriginTypesList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOeOriginTypesStartBrowse((tOEORIGINTYPES*)keys, cursorid);
}
