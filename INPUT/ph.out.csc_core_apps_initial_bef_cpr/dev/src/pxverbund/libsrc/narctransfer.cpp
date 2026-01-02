#include "pxnarctransfer.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxNarcTransfer :: pxNarcTransfer
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
pxNarcTransfer :: pxNarcTransfer
(
    pxNarcTransfer& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tNARCTRANSACTIONTRANSFER structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxNarcTransfer :: pxNarcTransfer
(
    pxSession   *session,
    const tNARCTRANSACTIONTRANSFER& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use pxOrderItem to construct this instance.                               */
/*----------------------------------------------------------------------------*/
pxNarcTransfer :: pxNarcTransfer
(

   pxSession   *session,
   const short BranchNo,
   const long  ArticleNo,
   const long  OrderNo,
   const long  PosNo
)
    : pxDBRecord(session)
{
    nClock  currentime;
    nDate   now;
    Init();

    TransferID_        = 0;                        // serial   number
    BranchNo_          = BranchNo;                 // BranchNumber
    ArticleNo_         = ArticleNo;                // ArticleNumber
    OrderNo_           = OrderNo;                  // OrderNumber
    PosNo_             = PosNo;                    // Positionnumber
    TransactionDate_   = now;                      // date
    TransactionTime_   = currentime;               // time
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxNarcTransfer :: ~pxNarcTransfer()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to tNARCTRANSACTIONTRANSFER structure. */
/*----------------------------------------------------------------------------*/
tNARCTRANSACTIONTRANSFER&
Assign
(
    tNARCTRANSACTIONTRANSFER&           dest,
    const pxNarcTransfer&       src
)
{
    dest.TransferID                = src.TransferID_                         ;
    dest.BranchNo                  = src.BranchNo_                           ;
    dest.ArticleNo                 = src.ArticleNo_                          ;
    dest.TransactionDate           = src.TransactionDate_.GetYYYYMMDD()      ;
    dest.TransactionTime           = src.TransactionTime_.GetHHMMSS()        ;
    dest.CustomerSupplierNo        = src.CustomerSupplierNo_                 ;
    dest.PurchaseOrderNo           = src.PurchaseOrderNo_                    ;
    dest.OrderNo                   = src.OrderNo_                            ;
    dest.QtyTransaction            = src.QtyTransaction_                     ;
    dest.QtyInStock                = src.QtyInStock_                         ;
    dest.CompletedFlag             = src.CompletedFlag_                      ;
    dest.PosNo                     = src.PosNo_                              ;

    strcpy(dest.TransactionType,    " ");
    src.TransactionType_.GetData(dest.TransactionType);
    strcpy(dest.TourId,    " ");
    src.TourId_.GetData(dest.TourId);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tNARCTRANSACTIONTRANSFER structure  constructv*/
/*  a pxNarcTransfer object.                                                  */
/*----------------------------------------------------------------------------*/
pxNarcTransfer&
Assign
(
    pxNarcTransfer&              dest,
    const tNARCTRANSACTIONTRANSFER&        src
)
{
    dest.TransferID_               = src.TransferID                          ;
    dest.BranchNo_                 = src.BranchNo                            ;
    dest.ArticleNo_                = src.ArticleNo                           ;
    dest.TransactionDate_          = nDate(src.TransactionDate)              ;
    dest.TransactionTime_          = src.TransactionTime                     ;
    dest.CustomerSupplierNo_       = src.CustomerSupplierNo                  ;
    dest.PurchaseOrderNo_          = src.PurchaseOrderNo                     ;
    dest.OrderNo_                  = src.OrderNo                             ;
    dest.QtyTransaction_           = src.QtyTransaction                      ;
    dest.QtyInStock_               = src.QtyInStock                          ;
    dest.CompletedFlag_            = src.CompletedFlag                       ;
    dest.TransactionType_          = src.TransactionType                     ;
    dest.PosNo_                    = src.PosNo                               ;
    dest.TourId_                   = src.TourId                              ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxNarcTransfer :: Init()
{
    tNARCTRANSACTIONTRANSFER    record;
    memset(&record, 0 , sizeof(tNARCTRANSACTIONTRANSFER));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tNARCTRANSACTIONTRANSFER struct and then imported to self.                */
/*----------------------------------------------------------------------------*/
pxNarcTransfer&
pxNarcTransfer :: operator=( const pxNarcTransfer& src)
{
    tNARCTRANSACTIONTRANSFER record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tNARCTRANSACTIONTRANSFER structure 'src' to      */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxNarcTransfer&
pxNarcTransfer :: operator=( const tNARCTRANSACTIONTRANSFER& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxNarcTransfer :: Get
(
    DBAccessMode mode
)

{
    tNARCTRANSACTIONTRANSFER record;
    memset(&record, 0, sizeof(tNARCTRANSACTIONTRANSFER));
    record.TransferID = TransferID_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record)
                                               : nDBRead(&record);
    if (!retval)
       (*this)= record;          // import the data from tNARCTRANSACTIONTRANSFER
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                        CMSG_NARC_ENTRY_NOTFOUND, TransferID_);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxNarcTransfer :: Put
(
)
{
    tNARCTRANSACTIONTRANSFER record;
    memset(&record, 0, sizeof(tNARCTRANSACTIONTRANSFER));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tNARCTRANSACTIONTRANSFER));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxNarcTransfer :: Delete
(
)
{
    tNARCTRANSACTIONTRANSFER record;
    memset(&record, 0, sizeof(tNARCTRANSACTIONTRANSFER));
    Assign(record, *this);
    return Delete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxNarcTransfer :: Read
(
    const void  *record
)
{
    return pxNarcTransferRead((tNARCTRANSACTIONTRANSFER*)record);
}

int
pxNarcTransfer :: ReadLock
(
    const void  *record
)
{
    return pxNarcTransferReadLock((tNARCTRANSACTIONTRANSFER*)record);
}

int
pxNarcTransfer :: Update
(
    const void  *record
)
{
    return pxNarcTransferUpdate((tNARCTRANSACTIONTRANSFER*)record);
}

int
pxNarcTransfer :: Delete
(
    const void  *record
)
{
    return pxNarcTransferDelete((tNARCTRANSACTIONTRANSFER*)record);
}

int
pxNarcTransfer :: Insert
(
    const void  *record
)
{
    return pxNarcTransferInsert((tNARCTRANSACTIONTRANSFER*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxNarcTransfer list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxNarcTransfer :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxNarcTransfer *that = (pxNarcTransfer*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxNarcTransferList :: pxNarcTransferList
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
pxNarcTransferList :: Select
(
    const int     count_
)
{
    tNARCTRANSACTIONTRANSFER fil;
    memset(&fil, 0, sizeof(tNARCTRANSACTIONTRANSFER));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records belongs to KdAufftragNr. of    */
/*  the current customer.                                                     */
/*----------------------------------------------------------------------------*/
size_t
pxNarcTransferList :: Select
(
    const short    BranchNo,
    const long     ArticleNo,
    const long     OrderNo,
    const int     count_
)
{
    tNARCTRANSACTIONTRANSFER fil;
    memset(&fil, 0, sizeof(tNARCTRANSACTIONTRANSFER));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.ArticleNo  = ArticleNo;
    fil.OrderNo    = OrderNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records belongs to KdAufftragNr. of    */
/*  the current customer.                                                     */
/*----------------------------------------------------------------------------*/
size_t
pxNarcTransferList :: Select
(
    const short    BranchNo,
    const long     OrderNo,
    const int      count_
)
{
    tNARCTRANSACTIONTRANSFER fil;
    memset(&fil, 0, sizeof(tNARCTRANSACTIONTRANSFER));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.OrderNo    = OrderNo;
    int cursorid = cCRSNARCTRANSFER_ORDERART;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records belongs to KdAufftragNr. of    */
/*  the current customer.                                                     */
/*----------------------------------------------------------------------------*/
size_t
pxNarcTransferList :: Select
(
    const long    OrderNo,
    const long    PosNo,
    const int     count_
)
{
    tNARCTRANSACTIONTRANSFER fil;
    memset(&fil, 0, sizeof(tNARCTRANSACTIONTRANSFER));  // zero out entire record buffer
    fil.OrderNo   = OrderNo;
    fil.PosNo     = PosNo;
    int cursorid = cCRSNARCTRANSFER_ORDERPOS;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxNarcTransferList :: AddToList
(
    const void  *record,
    const int  /*row*/
)

{
    // construct new 'pxNarcTransfer' object:
    pxNarcTransfer *objectp = new pxNarcTransfer(Session(), *(tNARCTRANSACTIONTRANSFER*) record);
    InsertAscending(objectp);
    return objectp;
}

int
pxNarcTransferList :: EndBrowse
(
    const int  cursorid
)
{
    return pxNarcTransferEndBrowse(cursorid);
}


int
pxNarcTransferList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxNarcTransferGetNext((tNARCTRANSACTIONTRANSFER*)record, cursorid);
}

int
pxNarcTransferList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxNarcTransferStartBrowse((tNARCTRANSACTIONTRANSFER*)keys, cursorid);
}

