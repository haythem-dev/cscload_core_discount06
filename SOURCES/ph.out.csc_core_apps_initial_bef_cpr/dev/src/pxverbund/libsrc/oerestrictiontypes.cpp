/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxOeRestrictionTypes methods.

REVISION HISTORY

06 Aug 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxoerestrictiontypes.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOeRestrictionTypes :: pxOeRestrictionTypes
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
pxOeRestrictionTypes :: pxOeRestrictionTypes
(
    pxOeRestrictionTypes& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERPROUP structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxOeRestrictionTypes :: pxOeRestrictionTypes
(
    pxSession   *session,
    tOERESTRICTIONTYPES& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxOeRestrictionTypes :: pxOeRestrictionTypes
(
    pxSession   *session,
    short      RestrictionType,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    RestrictionType_        = RestrictionType;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOeRestrictionTypes :: ~pxOeRestrictionTypes()
{
        ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tOERESTRICTIONTYPES structure.       */
/*----------------------------------------------------------------------------*/
tOERESTRICTIONTYPES&
Assign
(
    tOERESTRICTIONTYPES&    dest,
    const pxOeRestrictionTypes&  src
)
{
    // Copy native data types:
    dest.RestrictionType        = src.RestrictionType_;
    // Strings:
    dest.RestrictionName[0] = ' ';
    src.RestrictionName_.GetData(dest.RestrictionName);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' structure to a pxOeRestrictionTypes object.     */
/*----------------------------------------------------------------------------*/
pxOeRestrictionTypes&
Assign
(
    pxOeRestrictionTypes&           dest,
    const tOERESTRICTIONTYPES&   src
)
{
    dest.RestrictionType_        = src.RestrictionType;
    dest.RestrictionName_        = src.RestrictionName;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOeRestrictionTypes :: Init()
{
    tOERESTRICTIONTYPES    record;
    memset(&record, 0 , sizeof(tOERESTRICTIONTYPES));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tOERESTRICTIONTYPES struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxOeRestrictionTypes&
pxOeRestrictionTypes :: operator=( const pxOeRestrictionTypes& src)
{
    tOERESTRICTIONTYPES record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tOERESTRICTIONTYPES structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxOeRestrictionTypes&
pxOeRestrictionTypes :: operator=( const tOERESTRICTIONTYPES& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOeRestrictionTypes :: Get
(
    DBAccessMode mode
)

{
    tOERESTRICTIONTYPES record;
    memset(&record, 0, sizeof(tOERESTRICTIONTYPES));
    record.RestrictionType        = RestrictionType_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;             // import the data from tOERESTRICTIONTYPES struct
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
pxOeRestrictionTypes :: Put
(
)
{
    tOERESTRICTIONTYPES record;
    memset(&record, 0, sizeof(tOERESTRICTIONTYPES));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tOERESTRICTIONTYPES));
}


/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOeRestrictionTypes :: Read
(
    const void  *record
)
{
    return pxOeRestrictionTypesRead((tOERESTRICTIONTYPES*)record);
}

int
pxOeRestrictionTypes :: ReadLock
(
    const void  *record
)
{
    return pxOeRestrictionTypesReadLock((tOERESTRICTIONTYPES*)record);
}

int
pxOeRestrictionTypes :: Update
(
    const void  *record
)
{
    return pxOeRestrictionTypesUpdate((tOERESTRICTIONTYPES*)record);
}

int
pxOeRestrictionTypes :: Insert
(
    const void  *record
)
{
    return pxOeRestrictionTypesInsert((tOERESTRICTIONTYPES*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxOeRestrictionTypes list  */
/*  objects being inserted in the following ascending sequence: KdGruppe.     */
/*----------------------------------------------------------------------------*/
int
pxOeRestrictionTypes :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOeRestrictionTypes *that = (pxOeRestrictionTypes*)That;
    int retval = (RestrictionType_ == that->RestrictionType_) ? 0
                : (RestrictionType_ > that->RestrictionType_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOeRestrictionTypesList :: pxOeRestrictionTypesList
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
pxOeRestrictionTypesList :: Select
(
    const int     count_
)
{
    tOERESTRICTIONTYPES record;
    memset(&record, 0, sizeof(tOERESTRICTIONTYPES));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxOeRestrictionTypesList :: Select
(
    const short   RestrictionType,
    const int     count_
)
{
    tOERESTRICTIONTYPES record;
    memset(&record, 0, sizeof(tOERESTRICTIONTYPES));  // zero out entire record buffer
    record.RestrictionType        = RestrictionType;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOeRestrictionTypesList :: AddToList
(
    const void  *recordp,
    const int  /* row */
)
{
    // construct new 'pxOeRestrictionTypes' object:
    pxOeRestrictionTypes *objectp = new pxOeRestrictionTypes(Session(), *(tOERESTRICTIONTYPES*)recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxOeRestrictionTypesList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOeRestrictionTypesEndBrowse(cursorid);
}


int
pxOeRestrictionTypesList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxOeRestrictionTypesGetNext((tOERESTRICTIONTYPES*)recordp, cursorid);
}

int
pxOeRestrictionTypesList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOeRestrictionTypesStartBrowse((tOERESTRICTIONTYPES*)keys, cursorid);
}
