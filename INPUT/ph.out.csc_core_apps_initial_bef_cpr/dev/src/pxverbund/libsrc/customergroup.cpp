#include "pxcustomergroup.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustomerGroup :: pxCustomerGroup
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
pxCustomerGroup :: pxCustomerGroup
(
    pxCustomerGroup& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERPROUP structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxCustomerGroup :: pxCustomerGroup
(
    pxSession   *session,
    tCUSTOMERGROUP& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustomerGroup :: pxCustomerGroup
(
    pxSession   *session,
    short      BranchNo,
    short      CustomerGroupNo,                 // Read via string input
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_        = BranchNo;
    CustomerGroupNo_ = CustomerGroupNo;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustomerGroup :: ~pxCustomerGroup()
{
        ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCUSTOMERGROUP structure.       */
/*----------------------------------------------------------------------------*/
tCUSTOMERGROUP&
Assign
(
    tCUSTOMERGROUP&    dest,
    const pxCustomerGroup&  src
)
{
    // Copy native data types:
    dest.BranchNo        = src.BranchNo_;
    dest.CustomerGroupNo = src.CustomerGroupNo_;
    dest.Block_Flag      = src.Block_Flag_;
    dest.BasisNatra_Flag = src.BasisNatra_Flag_;
    // Strings:
    dest.Name[0] = ' ';
    src.Name_.GetData(dest.Name);
    dest.Sales_Restr_PH[0] = ' ';
    src.Sales_Restr_PH_.GetData(dest.Sales_Restr_PH);


    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' structure to a pxCustomerGroup object.     */
/*----------------------------------------------------------------------------*/
pxCustomerGroup&
Assign
(
    pxCustomerGroup&           dest,
    const tCUSTOMERGROUP&   src
)
{
    // Copy native data types:
    dest.BranchNo_        = src.BranchNo;
    dest.CustomerGroupNo_ = src.CustomerGroupNo;
    dest.Block_Flag_      = src.Block_Flag;
    dest.BasisNatra_Flag_ = src.BasisNatra_Flag;

    // Strings:
    dest.Name_            = src.Name;
    dest.Sales_Restr_PH_  = src.Sales_Restr_PH;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustomerGroup :: Init()
{
    tCUSTOMERGROUP    record;
    memset(&record, 0 , sizeof(tCUSTOMERGROUP));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCUSTOMERGROUP struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxCustomerGroup&
pxCustomerGroup :: operator=( const pxCustomerGroup& src)
{
    tCUSTOMERGROUP record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCUSTOMERGROUP structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxCustomerGroup&
pxCustomerGroup :: operator=( const tCUSTOMERGROUP& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustomerGroup :: Get
(
    DBAccessMode mode
)

{
    tCUSTOMERGROUP record;
    memset(&record, 0, sizeof(tCUSTOMERGROUP));
    record.BranchNo        = BranchNo_;
    record.CustomerGroupNo = CustomerGroupNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;             // import the data from tCUSTOMERGROUP struct
    else if ( retval > cDBXR_NORMAL )
       DBCondition(nMessage(CMsgStream(),
                            CMSG_CST_GRP_NOTFOUND,
                            record.CustomerGroupNo, 0),
                   CMSG_CST_GRP_NOTFOUND);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustomerGroup :: Put
(
)
{
    tCUSTOMERGROUP record;
    memset(&record, 0, sizeof(tCUSTOMERGROUP));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCUSTOMERGROUP));
}


/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustomerGroup :: Read
(
    const void  *record
)
{
    return pxCustomerGroupRead((tCUSTOMERGROUP*)record);
}

int
pxCustomerGroup :: ReadLock
(
    const void  *record
)
{
    return pxCustomerGroupReadLock((tCUSTOMERGROUP*)record);
}

int
pxCustomerGroup :: Update
(
    const void  *record
)
{
    return pxCustomerGroupUpdate((tCUSTOMERGROUP*)record);
}

int
pxCustomerGroup :: Insert
(
    const void  *record
)
{
    return pxCustomerGroupInsert((tCUSTOMERGROUP*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxCustomerGroup list  */
/*  objects being inserted in the following ascending sequence: KdGruppe.     */
/*----------------------------------------------------------------------------*/
int
pxCustomerGroup :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustomerGroup *that = (pxCustomerGroup*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
    {
       retval = (CustomerGroupNo_ == that->CustomerGroupNo_) ? 0
              : (CustomerGroupNo_ > that->CustomerGroupNo_ ? 1 : -1);
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustomerGroupList :: pxCustomerGroupList
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
pxCustomerGroupList :: Select
(
    const int     count_
)
{
    tCUSTOMERGROUP record;
    memset(&record, 0, sizeof(tCUSTOMERGROUP));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCustomerGroupList :: Select
(
    const short   BranchNo,
    const short   CustomerGroupNo,
    const int     count_
)
{
    tCUSTOMERGROUP record;
    memset(&record, 0, sizeof(tCUSTOMERGROUP));  // zero out entire record buffer
    record.BranchNo        = BranchNo;
    record.CustomerGroupNo = CustomerGroupNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustomerGroupList :: AddToList
(
    const void  *recordp,
    const int  /* row */
)
{
    // construct new 'pxCustomerGroup' object:
    pxCustomerGroup *objectp = new pxCustomerGroup(Session(), *(tCUSTOMERGROUP*)recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxCustomerGroupList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCustomerGroupEndBrowse(cursorid);
}


int
pxCustomerGroupList :: GetNext
(
    const void  *recordp,
    const int  cursorid
)
{
    return pxCustomerGroupGetNext((tCUSTOMERGROUP*)recordp, cursorid);
}

int
pxCustomerGroupList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxCustomerGroupStartBrowse((tCUSTOMERGROUP*)keys, cursorid);
}
