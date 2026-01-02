/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxOeRestrictions methods.

REVISION HISTORY

06 Aug 2014 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxoerestrictions.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOeRestrictions :: pxOeRestrictions
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
pxOeRestrictions :: pxOeRestrictions
(
    pxOeRestrictions& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERPROUP structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxOeRestrictions :: pxOeRestrictions
(
    pxSession   *session,
    tORDERENTRYRESTRICTIONS& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxOeRestrictions :: pxOeRestrictions
(
    pxSession   *session,
    short      BranchNo,
    short      RestrictionType,                 // Read via string input
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_        = BranchNo;
    RestrictionType_ = RestrictionType;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOeRestrictions :: ~pxOeRestrictions()
{
        ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tORDERENTRYRESTRICTIONS structure.       */
/*----------------------------------------------------------------------------*/
tORDERENTRYRESTRICTIONS&
Assign
(
    tORDERENTRYRESTRICTIONS&    dest,
    const pxOeRestrictions&  src
)
{
    // Copy native data types:
    dest.BranchNo         = src.BranchNo_;
    dest.RestrictionType  = src.RestrictionType_;
    dest.RestrictionValue = src.RestrictionValue_;
    dest.OriginType       = src.OriginType_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' structure to a pxOeRestrictions object.    */
/*----------------------------------------------------------------------------*/
pxOeRestrictions&
Assign
(
    pxOeRestrictions&           dest,
    const tORDERENTRYRESTRICTIONS&   src
)
{
    // Copy native data types:
    dest.BranchNo_         = src.BranchNo;
    dest.RestrictionType_  = src.RestrictionType;
    dest.RestrictionValue_ = src.RestrictionValue;
    dest.OriginType_       = src.OriginType;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOeRestrictions :: Init()
{
    tORDERENTRYRESTRICTIONS    record;
    memset(&record, 0 , sizeof(tORDERENTRYRESTRICTIONS));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tORDERENTRYRESTRICTIONS struct and then imported to self.                 */
/*----------------------------------------------------------------------------*/
pxOeRestrictions&
pxOeRestrictions :: operator=( const pxOeRestrictions& src)
{
    tORDERENTRYRESTRICTIONS record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tORDERENTRYRESTRICTIONS structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxOeRestrictions&
pxOeRestrictions :: operator=( const tORDERENTRYRESTRICTIONS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOeRestrictions :: Get
(
    DBAccessMode mode
)

{
    tORDERENTRYRESTRICTIONS record;
    memset(&record, 0, sizeof(tORDERENTRYRESTRICTIONS));
    record.BranchNo        = BranchNo_;
    record.RestrictionType = RestrictionType_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;             // import the data from tORDERENTRYRESTRICTIONS struct
   /* else if ( retval > cDBXR_NORMAL )
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
pxOeRestrictions :: Put
(
)
{
    tORDERENTRYRESTRICTIONS record;
    memset(&record, 0, sizeof(tORDERENTRYRESTRICTIONS));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tORDERENTRYRESTRICTIONS));
}


/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOeRestrictions :: Read
(
    const void  *record
)
{
    return pxOeRestrictionsRead((tORDERENTRYRESTRICTIONS*)record);
}

int
pxOeRestrictions :: ReadLock
(
    const void  *record
)
{
    return pxOeRestrictionsReadLock((tORDERENTRYRESTRICTIONS*)record);
}

int
pxOeRestrictions :: Update
(
    const void  *record
)
{
    return pxOeRestrictionsUpdate((tORDERENTRYRESTRICTIONS*)record);
}

int
pxOeRestrictions :: Insert
(
    const void  *record
)
{
    return pxOeRestrictionsInsert((tORDERENTRYRESTRICTIONS*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxOeRestrictions list  */
/*  objects being inserted in the following ascending sequence: KdGruppe.     */
/*----------------------------------------------------------------------------*/
int
pxOeRestrictions :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOeRestrictions *that = (pxOeRestrictions*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
    {
       retval = (RestrictionType_ == that->RestrictionType_) ? 0
                : (RestrictionType_ > that->RestrictionType_ ? 1 : -1);;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOeRestrictionsList :: pxOeRestrictionsList
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
pxOeRestrictionsList :: Select
(
    const int     count_
)
{
    tORDERENTRYRESTRICTIONS record;
    memset(&record, 0, sizeof(tORDERENTRYRESTRICTIONS));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxOeRestrictionsList :: Select
(
    const short   BranchNo,
    const int     count_
)
{
    tORDERENTRYRESTRICTIONS record;
    memset(&record, 0, sizeof(tORDERENTRYRESTRICTIONS));  // zero out entire record buffer
    record.BranchNo        = BranchNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxOeRestrictionsList :: Select
(
    const short   BranchNo,
    const short   RestrictionType,
    const short   RestrictionValue,
    const short   OriginType,
    const int     count_
)
{
    tORDERENTRYRESTRICTIONS record;
    memset(&record, 0, sizeof(tORDERENTRYRESTRICTIONS));  // zero out entire record buffer
    record.BranchNo         = BranchNo;
    record.RestrictionType  = RestrictionType;
    record.RestrictionValue = RestrictionValue;
    record.OriginType       = OriginType;
    int cursorid =cCRSOERESTRICTIONS_OVERALL;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOeRestrictionsList :: AddToList
(
    const void  *recordp,
    const int  /* row */
)
{
    // construct new 'pxOeRestrictions' object:
    pxOeRestrictions *objectp = new pxOeRestrictions(Session(), *(tORDERENTRYRESTRICTIONS*)recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxOeRestrictionsList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOeRestrictionsEndBrowse(cursorid);
}


int
pxOeRestrictionsList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxOeRestrictionsGetNext((tORDERENTRYRESTRICTIONS*)recordp, cursorid);
}

int
pxOeRestrictionsList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOeRestrictionsStartBrowse((tORDERENTRYRESTRICTIONS*)keys, cursorid);
}

