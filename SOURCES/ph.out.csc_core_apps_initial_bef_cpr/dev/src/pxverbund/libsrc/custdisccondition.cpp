/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxCustDiscCondition  methods.

REVISION HISTORY

29  November 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxcustdisccondition.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustDiscCondition :: pxCustDiscCondition
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
pxCustDiscCondition :: pxCustDiscCondition
(
    pxCustDiscCondition& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCSTDISCOUNTCONT structure to construct this instance.                */
/*----------------------------------------------------------------------------*/
pxCustDiscCondition :: pxCustDiscCondition
(
    pxSession   *session,
    tCSTDISCOUNTCONT& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustDiscCondition :: pxCustDiscCondition
(
    pxSession    *session,
    const short       BranchNo,            // Read via this type and
    const long        CustomerNo,          // this type
    const nString&     OrderType,          // this type
    const nString&     SubOrderType        // this type
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_          = BranchNo;
    CustomerNo_        = CustomerNo;
    OrderType_         = OrderType;
    SubOrderType_      = SubOrderType;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustDiscCondition :: ~pxCustDiscCondition()
{
    ;
}

/*----------------------------------------------------------------------------*/
/* Assign the values of the 'src' object to a tCSTDISCOUNTCONT structure      */
/*----------------------------------------------------------------------------*/
tCSTDISCOUNTCONT&
Assign
(
    tCSTDISCOUNTCONT&           dest,
    const pxCustDiscCondition&       src
)
{
    dest.BranchNo                  = src.BranchNo_;
    dest.CustomerNo                = src.CustomerNo_;
    dest.OrderType[0] = ' ';
    src.OrderType_.GetData(dest.OrderType);
    dest.SubOrderType[0] = ' ';
    src.SubOrderType_.GetData(dest.SubOrderType);
    dest.PaymentTerm[0] = ' ';
    src.PaymentTerm_.GetData(dest.PaymentTerm);
    dest.ValutaDays        = src.ValutaDays_;
    dest.MinOrderValue     = src.MinOrderValue_;
    dest.MinTubes          = src.MinTubes_;
    dest.LossInDiscount    = src.LossInDiscount_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCSTDISCOUNTCONT structure to              */
/*  a pxCustDiscCondition object.                                             */
/*----------------------------------------------------------------------------*/
pxCustDiscCondition&
Assign
(
    pxCustDiscCondition&              dest,
    const tCSTDISCOUNTCONT&    src
)
{
    dest.BranchNo_                 = src.BranchNo;
    dest.CustomerNo_               = src.CustomerNo;
    dest.OrderType_                = src.OrderType;
    dest.SubOrderType_             = src.SubOrderType;
    dest.PaymentTerm_              = src.PaymentTerm;
    dest.ValutaDays_               = src.ValutaDays;
    dest.MinOrderValue_            = src.MinOrderValue;
    dest.MinTubes_                 = src.MinTubes;
    dest.LossInDiscount_           = src.LossInDiscount;

    return dest;
}
/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustDiscCondition :: Init()
{
    tCSTDISCOUNTCONT    record;
    memset(&record, 0 , sizeof(tCSTDISCOUNTCONT));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCSTDISCOUNTCONT struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxCustDiscCondition&
pxCustDiscCondition :: operator=( const pxCustDiscCondition& src)
{
    tCSTDISCOUNTCONT record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCSTDISCOUNTCONT structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCustDiscCondition&
pxCustDiscCondition :: operator=( const tCSTDISCOUNTCONT& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustDiscCondition :: Get
(
    DBAccessMode mode
)

{
    tCSTDISCOUNTCONT record;
    memset(&record, 0, sizeof(tCSTDISCOUNTCONT));
    record.BranchNo      = BranchNo_;
    record.CustomerNo    = CustomerNo_;
    record.OrderType[0] = ' ';
    OrderType_.GetData(record.OrderType);
    record.SubOrderType[0] = ' ';
    SubOrderType_.GetData(record.SubOrderType);

    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tCSTDISCOUNTCONT struct

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustDiscCondition :: Read
(
    const void  *record
)
{
    return pxCustDiscConditionRead((tCSTDISCOUNTCONT*)record);
}

int
pxCustDiscCondition :: ReadLock
(
    const void  *record
)
{
    return pxCustDiscConditionReadLock((tCSTDISCOUNTCONT*)record);
}
int
pxCustDiscConditionList :: EndBrowse
(
    const int  cursorid
)
{
    return pxCustDiscConditionEndBrowse(cursorid);
}


int
pxCustDiscConditionList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxCustDiscConditionGetNext((tCSTDISCOUNTCONT*)record, cursorid);
}

int
pxCustDiscConditionList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxCustDiscConditionStartBrowse((tCSTDISCOUNTCONT*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCustDiscCondition list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxCustDiscCondition :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustDiscCondition *that = (pxCustDiscCondition*)That;

    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    if ( retval == 0 )
         retval = (CustomerNo_ == that->CustomerNo_) ? 0
                  : (CustomerNo_ > that->CustomerNo_ ? 1 : -1);

    if ( retval == 0 )
         retval = (OrderType_ == that->OrderType_) ? 0
                  : (OrderType_ > that->OrderType_ ? 1 : -1);
    if ( retval == 0 )
         retval = (SubOrderType_ == that->SubOrderType_) ? 0
                  : (SubOrderType_ > that->SubOrderType_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustDiscConditionList :: pxCustDiscConditionList
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
pxCustDiscConditionList :: Select
(
    const short   BranchNo,
    const long    CustomerNo,
    const nString& OrderType,
    const int     count_
)
{
    tCSTDISCOUNTCONT fil;
    memset(&fil, 0, sizeof(tCSTDISCOUNTCONT*));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    fil.OrderType[0] = ' ';
    OrderType.GetData(fil.OrderType);
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustDiscConditionList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxCustDiscCondition' object:
    pxCustDiscCondition *objectp = new pxCustDiscCondition(Session(), *(tCSTDISCOUNTCONT*) record);
    InsertAscending(objectp);
    return objectp;
}
