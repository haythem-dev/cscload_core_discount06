#include "pxcustgrpflagtypes.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustGrpFlagTypes :: pxCustGrpFlagTypes
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
pxCustGrpFlagTypes :: pxCustGrpFlagTypes
(
    pxCustGrpFlagTypes& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERPROUP structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxCustGrpFlagTypes :: pxCustGrpFlagTypes
(
    pxSession   *session,
    tCUSTGRPFLAGTYPES& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustGrpFlagTypes :: pxCustGrpFlagTypes
(
    pxSession   *session,
    short      BranchNo,
    short      CustGrpFlagType,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_        = BranchNo;
    CustGrpFlagType_ = CustGrpFlagType;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustGrpFlagTypes :: ~pxCustGrpFlagTypes()
{
        ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCUSTGRPFLAGTYPES structure.       */
/*----------------------------------------------------------------------------*/
tCUSTGRPFLAGTYPES&
Assign
(
    tCUSTGRPFLAGTYPES&    dest,
    const pxCustGrpFlagTypes&  src
)
{
    // Copy native data types:
    dest.BranchNo        = src.BranchNo_;
    dest.CustGrpFlagType = src.CustGrpFlagType_;
    dest.Index_DKKGR     = src.Index_DKKGR_;

    dest.Description[0] = ' ';
    src.Description_.GetData(dest.Description);


    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' structure to a pxCustGrpFlagTypes object.     */
/*----------------------------------------------------------------------------*/
pxCustGrpFlagTypes&
Assign
(
    pxCustGrpFlagTypes&           dest,
    const tCUSTGRPFLAGTYPES&   src
)
{
    // Copy native data types:
    dest.BranchNo_        = src.BranchNo;
    dest.CustGrpFlagType_ = src.CustGrpFlagType;
    dest.Description_     = src.Description;
    dest.Index_DKKGR_     = src.Index_DKKGR;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustGrpFlagTypes :: Init()
{
    tCUSTGRPFLAGTYPES    record;
    memset(&record, 0 , sizeof(tCUSTGRPFLAGTYPES));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCUSTGRPFLAGTYPES struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxCustGrpFlagTypes&
pxCustGrpFlagTypes :: operator=( const pxCustGrpFlagTypes& src)
{
    tCUSTGRPFLAGTYPES record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCUSTGRPFLAGTYPES structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxCustGrpFlagTypes&
pxCustGrpFlagTypes :: operator=( const tCUSTGRPFLAGTYPES& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustGrpFlagTypes :: Get
(
    DBAccessMode mode
)

{
    tCUSTGRPFLAGTYPES record;
    memset(&record, 0, sizeof(tCUSTGRPFLAGTYPES));
    record.BranchNo        = BranchNo_;
    record.CustGrpFlagType = CustGrpFlagType_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;             // import the data from tCUSTGRPFLAGTYPES struct
    /*else if ( retval > cDBXR_NORMAL )
       DBCondition(nMessage(CMsgStream(),
                            CMSG_CST_GRP_NOTFOUND,
                            record.CustomerGroupNo, 0),
                   CMSG_CST_GRP_NOTFOUND);*/
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustGrpFlagTypes :: Put
(
)
{
    tCUSTGRPFLAGTYPES record;
    memset(&record, 0, sizeof(tCUSTGRPFLAGTYPES));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCUSTGRPFLAGTYPES));
}


/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustGrpFlagTypes :: Read
(
    const void  *record
)
{
    return pxCustGrpFlagTypesRead((tCUSTGRPFLAGTYPES*)record);
}

int
pxCustGrpFlagTypes :: ReadLock
(
    const void  *record
)
{
    return pxCustGrpFlagTypesReadLock((tCUSTGRPFLAGTYPES*)record);
}

int
pxCustGrpFlagTypes :: Update
(
    const void  *record
)
{
    return pxCustGrpFlagTypesUpdate((tCUSTGRPFLAGTYPES*)record);
}

int
pxCustGrpFlagTypes :: Insert
(
    const void  *record
)
{
    return pxCustGrpFlagTypesInsert((tCUSTGRPFLAGTYPES*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxCustGrpFlagTypes list  */
/*  objects being inserted in the following ascending sequence: KdGruppe.     */
/*----------------------------------------------------------------------------*/
int
pxCustGrpFlagTypes :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustGrpFlagTypes *that = (pxCustGrpFlagTypes*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustGrpFlagTypesList :: pxCustGrpFlagTypesList
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
pxCustGrpFlagTypesList :: Select
(
    const int     count_
)
{
    tCUSTGRPFLAGTYPES record;
    memset(&record, 0, sizeof(tCUSTGRPFLAGTYPES));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCustGrpFlagTypesList :: Select
(
    const short   BranchNo,
    const int     count_
)
{
    tCUSTGRPFLAGTYPES record;
    memset(&record, 0, sizeof(tCUSTGRPFLAGTYPES));  // zero out entire record buffer
    record.BranchNo        = BranchNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustGrpFlagTypesList :: AddToList
(
    const void  *recordp,
    const int  /* row */
)
{
    // construct new 'pxCustGrpFlagTypes' object:
    pxCustGrpFlagTypes *objectp = new pxCustGrpFlagTypes(Session(), *(tCUSTGRPFLAGTYPES*)recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxCustGrpFlagTypesList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCustGrpFlagTypesEndBrowse(cursorid);
}


int
pxCustGrpFlagTypesList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxCustGrpFlagTypesGetNext((tCUSTGRPFLAGTYPES*)recordp, cursorid);
}

int
pxCustGrpFlagTypesList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxCustGrpFlagTypesStartBrowse((tCUSTGRPFLAGTYPES*)keys, cursorid);
}
