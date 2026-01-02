#include "pxcustomergrpflags.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustomerGrpFlags :: pxCustomerGrpFlags
(
    pxSession *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustomerGrpFlags :: pxCustomerGrpFlags
(
    pxCustomerGrpFlags& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERPROUP structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxCustomerGrpFlags :: pxCustomerGrpFlags
(
    pxSession   *session,
    tCUSTOMERGRPFLAGS& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustomerGrpFlags :: pxCustomerGrpFlags
(
    pxSession  *session,
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
pxCustomerGrpFlags :: ~pxCustomerGrpFlags()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCUSTOMERGRPFLAGS structure.   */
/*----------------------------------------------------------------------------*/
tCUSTOMERGRPFLAGS&
Assign
(
    tCUSTOMERGRPFLAGS&    dest,
    const pxCustomerGrpFlags&  src
)
{
    // Copy native data types:
    dest.BranchNo        = src.BranchNo_;
    dest.CustomerGroupNo = src.CustomerGroupNo_;
    dest.CustGrpFlagType = src.CustGrpFlagType_;
    dest.CustomerGrpFlag = src.CustomerGrpFlag_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' structure to a pxCustomerGrpFlags object.  */
/*----------------------------------------------------------------------------*/
pxCustomerGrpFlags&
Assign
(
    pxCustomerGrpFlags&        dest,
    const tCUSTOMERGRPFLAGS&   src
)
{
    // Copy native data types:
    dest.BranchNo_        = src.BranchNo;
    dest.CustomerGroupNo_ = src.CustomerGroupNo;
    dest.CustGrpFlagType_ = src.CustGrpFlagType;
    dest.CustomerGrpFlag_ = src.CustomerGrpFlag;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustomerGrpFlags :: Init()
{
    tCUSTOMERGRPFLAGS record;
    memset(&record, 0, sizeof(tCUSTOMERGRPFLAGS));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCUSTOMERGRPFLAGS struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxCustomerGrpFlags&
pxCustomerGrpFlags :: operator=( const pxCustomerGrpFlags& src)
{
    tCUSTOMERGRPFLAGS record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*-------------------------------------------------------------------------------*/
/*  Assign the values of the tCUSTOMERGRPFLAGS structure 'src' to this instance. */
/*-------------------------------------------------------------------------------*/
pxCustomerGrpFlags&
pxCustomerGrpFlags :: operator=( const tCUSTOMERGRPFLAGS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustomerGrpFlags :: Get
(
    DBAccessMode mode
)
{
    tCUSTOMERGRPFLAGS record;
    memset(&record, 0, sizeof(tCUSTOMERGRPFLAGS));
    record.BranchNo        = BranchNo_;
    record.CustomerGroupNo = CustomerGroupNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;             // import the data from tCUSTOMERGRPFLAGS struct
    else if ( retval > cDBXR_NORMAL )
        DBCondition(nMessage(CMsgStream(), CMSG_CST_GRP_NOTFOUND, record.CustomerGroupNo, 0), CMSG_CST_GRP_NOTFOUND);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustomerGrpFlags :: Put
(
)
{
    tCUSTOMERGRPFLAGS record;
    memset(&record, 0, sizeof(tCUSTOMERGRPFLAGS));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCUSTOMERGRPFLAGS));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustomerGrpFlags :: Read
(
    const void *record
)
{
    return pxCustomerGrpFlagsRead((tCUSTOMERGRPFLAGS*)record);
}

int
pxCustomerGrpFlags :: ReadLock
(
    const void *record
)
{
    return pxCustomerGrpFlagsReadLock((tCUSTOMERGRPFLAGS*)record);
}

int
pxCustomerGrpFlags :: Update
(
    const void *record
)
{
    return pxCustomerGrpFlagsUpdate((tCUSTOMERGRPFLAGS*)record);
}

int
pxCustomerGrpFlags :: Insert
(
    const void *record
)
{
    return pxCustomerGrpFlagsInsert((tCUSTOMERGRPFLAGS*)record);
}

/*----------------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxCustomerGrpFlags list */
/*  objects being inserted in the following ascending sequence: KdGruppe.           */
/*----------------------------------------------------------------------------------*/
int
pxCustomerGrpFlags :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustomerGrpFlags *that = (pxCustomerGrpFlags*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
               : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
    {
        retval = (CustomerGroupNo_ == that->CustomerGroupNo_) ? 0
               : (CustomerGroupNo_ > that->CustomerGroupNo_ ? 1 : -1);;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustomerGrpFlagsList :: pxCustomerGrpFlagsList
(
    pxSession *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}


/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCustomerGrpFlagsList :: Select
(
    const int count_
)
{
    tCUSTOMERGRPFLAGS record;
    memset(&record, 0, sizeof(tCUSTOMERGRPFLAGS));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&record, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCustomerGrpFlagsList :: Select
(
    const short   BranchNo,
    const short   CustomerGroupNo,
    const int     count_
)
{
    tCUSTOMERGRPFLAGS record;
    memset(&record, 0, sizeof(tCUSTOMERGRPFLAGS));  // zero out entire record buffer
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
pxCustomerGrpFlagsList :: AddToList
(
    const void *recordp,
    const int  /* row */
)
{
    // construct new 'pxCustomerGrpFlags' object:
    pxCustomerGrpFlags *objectp = new pxCustomerGrpFlags(Session(), *(tCUSTOMERGRPFLAGS*)recordp);
    InsertAscending(objectp);
    return objectp;
}

int
pxCustomerGrpFlagsList :: EndBrowse
(
    const int cursorid
)
{
    return pxCustomerGrpFlagsEndBrowse(cursorid);
}

int
pxCustomerGrpFlagsList :: GetNext
(
    const void *recordp,
    const int  cursorid
)
{
    return pxCustomerGrpFlagsGetNext((tCUSTOMERGRPFLAGS*)recordp, cursorid);
}

int
pxCustomerGrpFlagsList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    return pxCustomerGrpFlagsStartBrowse((tCUSTOMERGRPFLAGS*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  Find                                                                      */
/*----------------------------------------------------------------------------*/
pxCustomerGrpFlags*
pxCustomerGrpFlagsList :: Find
(
    const short FlagType
)
{
    pxCustomerGrpFlags* entriep;              // entry from list
    pxCustomerGrpFlagsListIter cursor(*this); // iterator on list
    while ( (entriep = (pxCustomerGrpFlags*) ++cursor) != NULL )
    {
        if ( entriep->CustGrpFlagType() == FlagType )
        {
            break;
        }
    }
    return entriep;
}

/*----------------------------------------------------------------------------*/
/*  IsKscDiscountEnabled                                                      */
/*----------------------------------------------------------------------------*/
bool
pxCustomerGrpFlagsList :: IsKscDiscountEnabled
(
)
{
    bool retval = false;
    pxCustomerGrpFlags* entriep = Find(static_cast<short>(pxCustomerGrpFlags::KscDiscountEnabled)); // entry from list
    if (entriep)
    {
        retval = ( entriep->CustomerGrpFlag() == (short)1 );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  IsWithoutCertificateEnabled                                               */
/*----------------------------------------------------------------------------*/
bool
pxCustomerGrpFlagsList :: IsWithoutCertificateEnabled
(
)
{
    bool retval = false;
    pxCustomerGrpFlags* entriep = Find(static_cast<short>(pxCustomerGrpFlags::WithoutCertificateEnabled)); // entry from list
    if (entriep)
    {
        retval = ( entriep->CustomerGrpFlag() == (short)1 );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  IsNoConsignmentPermission                                                 */
/*----------------------------------------------------------------------------*/
bool
pxCustomerGrpFlagsList :: IsNoConsignmentPermission
(
)
{
    bool retval = false;
    pxCustomerGrpFlags* entriep = Find(static_cast<short>(pxCustomerGrpFlags::NoConsignmentPermission)); // entry from list
    if (entriep)
    {
        retval = ( entriep->CustomerGrpFlag() == (short)1 );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  IsNoDiminishDiscount                                                      */
/*----------------------------------------------------------------------------*/
bool
pxCustomerGrpFlagsList :: IsNoDiminishDiscount
(
)
{
    bool retval = false;
    pxCustomerGrpFlags* entriep = Find(static_cast<short>(pxCustomerGrpFlags::NoDiminishDiscount));// entry from list
    if (entriep)
    {
        retval = ( entriep->CustomerGrpFlag() == (short)1 );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  IsStotinkiEnabled                                                         */
/*----------------------------------------------------------------------------*/
bool
pxCustomerGrpFlagsList :: IsStotinkiEnabled
(
)
{
    bool retval = false;
    pxCustomerGrpFlags* entriep = Find(static_cast<short>(pxCustomerGrpFlags::StotinkiEnabled)); // entry from list
    if (entriep)
    {
        retval = ( entriep->CustomerGrpFlag() == (short)1 );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  IsNoReduceDiscountForExclusiveArticle                                     */
/*----------------------------------------------------------------------------*/
bool
pxCustomerGrpFlagsList :: IsNoReduceDiscountForExclusiveArticle
(
)
{
    bool retval = false;
    pxCustomerGrpFlags* entriep = Find(static_cast<short>(pxCustomerGrpFlags::NoReduceDiscountForExclusiveArticle)); // entry from list
    if (entriep)
    {
        retval = ( entriep->CustomerGrpFlag() == (short)1 );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  isGroupBasePriceAEP                                                       */
/*----------------------------------------------------------------------------*/
bool
pxCustomerGrpFlagsList :: isGroupBasePriceAEP()
{
    bool retval = false;
    pxCustomerGrpFlags* entriep = Find(static_cast<short>(pxCustomerGrpFlags::GroupPriceBase)); // entry from list
    if (entriep)
    {
        retval = ( entriep->CustomerGrpFlag() == (short) pxCustomerGrpFlags::GroupBasePriceAEP );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  isGroupBasePriceGEP                                                       */
/*----------------------------------------------------------------------------*/
bool
pxCustomerGrpFlagsList :: isGroupBasePriceGEP()
{
    bool retval = false;
    pxCustomerGrpFlags* entriep = Find(static_cast<short>(pxCustomerGrpFlags::GroupPriceBase));// entry from list
    if (entriep)
    {
        retval = ( entriep->CustomerGrpFlag() == (short) pxCustomerGrpFlags::GroupBasePriceGEP );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  isGroupBasePriceGEPNA                                                     */
/*----------------------------------------------------------------------------*/
bool
pxCustomerGrpFlagsList :: isGroupBasePriceGEPNA()
{
    bool retval = false;
    pxCustomerGrpFlags* entriep = Find(static_cast<short>(pxCustomerGrpFlags::GroupPriceBase)); // entry from list
    if (entriep)
    {
        retval = ( entriep->CustomerGrpFlag() == (short) pxCustomerGrpFlags::GroupBasePriceGEPNA );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  isGroupBasePriceDGEP                                                      */
/*----------------------------------------------------------------------------*/
bool
pxCustomerGrpFlagsList :: isGroupBasePriceDGEP()
{
    bool retval = false;
    pxCustomerGrpFlags* entriep = Find(static_cast<short>(pxCustomerGrpFlags::GroupPriceBase)); // entry from list
    if (entriep)
    {
        retval = ( entriep->CustomerGrpFlag() == (short) pxCustomerGrpFlags::GroupBasePriceDGEP );
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  isGroupNoQuotaInheritance                                                 */
/*----------------------------------------------------------------------------*/
bool
pxCustomerGrpFlagsList :: isGroupNoQuotaInheritance()
{
    bool retval = false;
    pxCustomerGrpFlags* entriep = Find(static_cast<short>(pxCustomerGrpFlags::GroupNoQuotaInheritance)); // entry from list
    if (entriep)
    {
        retval = (entriep->CustomerGrpFlag() == 1);
    }
    return retval;
}
