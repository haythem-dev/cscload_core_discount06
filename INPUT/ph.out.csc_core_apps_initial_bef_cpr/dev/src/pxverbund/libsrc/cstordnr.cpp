#include "pxcstonr.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustOrderNumber :: pxCustOrderNumber
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
pxCustOrderNumber :: pxCustOrderNumber
(
    pxCustOrderNumber& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCUSTOMERORDERNO structure to construct this instance.                */
/*----------------------------------------------------------------------------*/
pxCustOrderNumber :: pxCustOrderNumber
(
    pxSession   *session,
    tCUSTOMERORDERNO& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Constructor with this values                                              */
/*----------------------------------------------------------------------------*/
pxCustOrderNumber :: pxCustOrderNumber
(
    pxSession    *session,
    short       BranchNo,
    long        CustomerNo,
    nMoney       OrderValue
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_    = BranchNo;
    CustomerNo_  = CustomerNo;
    OrderValue_  = OrderValue;
    ProcessNo_   = 0;
}
/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustOrderNumber :: pxCustOrderNumber
(
    pxSession    *session,
    short       BranchNo,            // Read via this type and
    long        CustomerNo,                  // this type
    const nString&     CustomerOrderNo,
    const nString&     ProcessNo,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_    = BranchNo;
    CustomerNo_    = CustomerNo;
    CustomerOrderNo_     = CustomerOrderNo;
    ProcessNo_   = atol(ProcessNo);
    Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustOrderNumber :: ~pxCustOrderNumber()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCUSTOMERORDERNO structure.    */
/*----------------------------------------------------------------------------*/
tCUSTOMERORDERNO&
Assign
(
    tCUSTOMERORDERNO&              dest,
    const pxCustOrderNumber&       src
)
{
    dest.BranchNo           = src.BranchNo_;
    dest.CustomerNo         = src.CustomerNo_;
    dest.CustomerOrderNo[0] = ' ';
    src.CustomerOrderNo_.GetData(dest.CustomerOrderNo);
    dest.ProcessNo          = src.ProcessNo_;
    dest.OrderValue         = src.OrderValue_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCUSTOMERORDERNO structure to              */
/*  a pxCustOrderNumber object.                                               */
/*----------------------------------------------------------------------------*/
pxCustOrderNumber&
Assign
(
    pxCustOrderNumber&         dest,
    const tCUSTOMERORDERNO&    src
)
{

    dest.BranchNo_           = src.BranchNo;
    dest.CustomerNo_         = src.CustomerNo;
    dest.CustomerOrderNo_    = src.CustomerOrderNo;
    dest.ProcessNo_          = src.ProcessNo;
    dest.OrderValue_         = src.OrderValue;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustOrderNumber :: Init()
{
    tCUSTOMERORDERNO    record;
    memset(&record, 0 , sizeof(tCUSTOMERORDERNO));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCUSTOMERORDERNO struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxCustOrderNumber&
pxCustOrderNumber :: operator=( const pxCustOrderNumber& src)
{
    tCUSTOMERORDERNO record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCUSTOMERORDERNO structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCustOrderNumber&
pxCustOrderNumber :: operator=( const tCUSTOMERORDERNO& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustOrderNumber :: Get
(
    DBAccessMode mode
)

{
    tCUSTOMERORDERNO record;
    memset(&record, 0, sizeof(tCUSTOMERORDERNO));
    record.BranchNo = BranchNo_;
    record.CustomerNo = CustomerNo_;
    record.CustomerOrderNo[0] = ' ';
    CustomerOrderNo_.GetData(record.CustomerOrderNo);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tCUSTOMERORDERNO struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                          CMSG_CUSTONR_ENTRY_NOTFOUND, BranchNo_,CustomerNo_, CustomerOrderNo_());
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustOrderNumber :: Put
(
)
{
    tCUSTOMERORDERNO record;
    memset(&record, 0, sizeof(tCUSTOMERORDERNO));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCUSTOMERORDERNO));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustOrderNumber :: Read
(
    const void  *record
)
{
    return pxCustOrderNumberRead((tCUSTOMERORDERNO*)record);
}

int
pxCustOrderNumber :: Insert
(
    const void  *record
)
{
    return pxCustOrderNumberInsert((tCUSTOMERORDERNO*)record);
}

int
pxCustOrderNumber :: ReadLock
(
    const void  *record
)
{
    return pxCustOrderNumberReadLock((tCUSTOMERORDERNO*)record);
}

int
pxCustOrderNumber :: Update
(
    const void  *record
)
{
    return pxCustOrderNumberUpdate((tCUSTOMERORDERNO*)record);
}

int
pxCustOrderNumber :: Delete
(
    const void  *record
)
{
    return pxCustOrderNumberDelete((tCUSTOMERORDERNO*)record);
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustOrderNumberList :: pxCustOrderNumberList
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
pxCustOrderNumberList :: Select
(
    const short  BranchNo,
    const long   CustomerNo,
    const nMoney& OrderValue,
    const int    count_
)
{
    tCUSTOMERORDERNO fil;
    memset(&fil, 0, sizeof(tCUSTOMERORDERNO));  // zero out entire record buffer
    fil.BranchNo    = BranchNo;
    fil.CustomerNo  = CustomerNo;
    fil.OrderValue  = OrderValue;
    int cursorid   = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCustOrderNumberList :: Select
(
    const short  BranchNo,
    const long   CustomerNo,
    const nMoney& OrderValue,
    const nString& CustomerOrderNo,
    const int    count_
)
{
    tCUSTOMERORDERNO fil;
    memset(&fil, 0, sizeof(tCUSTOMERORDERNO));  // zero out entire record buffer
    fil.BranchNo    = BranchNo;
    fil.CustomerNo  = CustomerNo;
    fil.OrderValue  = OrderValue;
    fil.CustomerOrderNo[0] = ' ';
    CustomerOrderNo.GetData(fil.CustomerOrderNo);
    int cursorid   = cCRSCUSTORDERNUM;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustOrderNumberList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    pxCustOrderNumber *objectp = new pxCustOrderNumber(Session(),*(tCUSTOMERORDERNO*) record);
    InsertAscending(objectp);        // before we do the insert
    return objectp;
}

int
pxCustOrderNumberList :: EndBrowse
(
    const int  cursorid
)
{

    return pxCustOrderNumberEndBrowse(cursorid);
}


int
pxCustOrderNumberList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{

    return pxCustOrderNumberGetNext((tCUSTOMERORDERNO*)record, cursorid);
}

int
pxCustOrderNumberList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{

    return pxCustOrderNumberStartBrowse((tCUSTOMERORDERNO*)keys, cursorid);
}

