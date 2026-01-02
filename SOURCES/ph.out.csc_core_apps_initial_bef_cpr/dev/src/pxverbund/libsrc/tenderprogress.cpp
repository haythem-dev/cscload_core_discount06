/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxTenderProgress methods.

REVISION HISTORY

17 Sept 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxtenderprogress.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxTenderProgress :: pxTenderProgress
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
pxTenderProgress :: pxTenderProgress
(
    pxTenderProgress& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tTENDERPROGRESS structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxTenderProgress :: pxTenderProgress
(
    pxSession   *session,
    tTENDERPROGRESS& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTenderProgress :: pxTenderProgress
(
    pxSession *session,
    const pxTenderProgress *src
)
    : pxDBRecord(session)
{
    Init();

    if (src != NULL)
        (*this) = *src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTenderProgress :: pxTenderProgress
(
    pxSession    *session,
    long         TenderNo,            // TenderNumber
    long         ArticleNo,           // Article number
    long         KdAuftragNr,         // KdAuftragNr
    nDate&       OrderDate,           // OrderDate
    long         PosNr                // Position number

)
    : pxDBRecord(session)
{
    Init();
    TenderNo_    = TenderNo;
    ArticleNo_   = ArticleNo;
    KdAuftragNr_ = KdAuftragNr;
    OrderDate_   = OrderDate;
    PosNr_       = PosNr;
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxTenderProgress :: ~pxTenderProgress()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tTENDERPROGRESS structure.     */
/*----------------------------------------------------------------------------*/
tTENDERPROGRESS&
Assign
(
    tTENDERPROGRESS&           dest,
    const pxTenderProgress&    src
)
{
    dest.TenderNo                 = src.TenderNo_              ;
    dest.ArticleNo                = src.ArticleNo_             ;
    dest.KdAuftragNr              = src.KdAuftragNr_           ;
    dest.OrderDate                = src.OrderDate_.GetYYYYMMDD();
    dest.DeliveryQty              = src.DeliveryQty_           ;
    dest.ChargedPrice             = src.ChargedPrice_          ;
    dest.PosNr                    = src.PosNr_                 ;
    dest.ReturnQty                = src.ReturnQty_             ;
    dest.OrderTime                = src.OrderTime_             ;
    dest.CustomerNo               = src.CustomerNo_            ;
    dest.AEP					  = src.AEP_                   ;
    dest.BookingTenderNo          = src.BookingTenderNo_       ;
    dest.InvoiceNo                = src.InvoiceNo_             ;
    dest.InvoiceDate              = src.InvoiceDate_           ;
    strncpy( dest.KdAuftragArt, src.KdAuftragArt_.c_str(), 2 ) ;
    dest.GEP					  = src.GEP_                   ;
    dest.InvoiceTime              = src.InvoiceTime_           ;
    dest.BranchNo                 = src.BranchNo_              ;
    dest.DiscountPct              = src.DiscountPct_           ;
    dest.ChangeDate               = src.ChangeDate_.GetYYYYMMDD();
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tTENDERPROGRESS structure to               */
/*  a pxTenderProgress object.                                                */
/*----------------------------------------------------------------------------*/
pxTenderProgress&
Assign
(
    pxTenderProgress&         dest,
    const tTENDERPROGRESS&    src
)
{
    dest.TenderNo_                 = src.TenderNo              ;
    dest.ArticleNo_                = src.ArticleNo             ;
    dest.KdAuftragNr_              = src.KdAuftragNr           ;
    dest.OrderDate_                = nDate(src.OrderDate)      ;
    dest.DeliveryQty_              = src.DeliveryQty           ;
    dest.ChargedPrice_             = src.ChargedPrice          ;
    dest.PosNr_                    = src.PosNr                 ;
    dest.ReturnQty_                = src.ReturnQty             ;
    dest.OrderTime_                = src.OrderTime             ;
    dest.CustomerNo_               = src.CustomerNo            ;
    dest.AEP_					   = src.AEP				   ;
    dest.BookingTenderNo_          = src.BookingTenderNo       ;
    dest.InvoiceNo_                = src.InvoiceNo             ;
    dest.InvoiceDate_              = src.InvoiceDate           ;
    dest.KdAuftragArt_             = src.KdAuftragArt          ;
    if( dest.KdAuftragArt_.empty() )
    {
        dest.KdAuftragArt_ = "  ";
    }
    //dest.KdAuftragArt_.trim( basar::cmnutil::BString::FIRST_END );
    dest.GEP_					   = src.GEP				   ;
    dest.InvoiceTime_              = src.InvoiceTime           ;
    dest.BranchNo_                 = src.BranchNo              ;
    dest.DiscountPct_              = src.DiscountPct           ;
    dest.ChangeDate_               = nDate( src.ChangeDate )   ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxTenderProgress :: Init()
{
    tTENDERPROGRESS record;
    memset(&record, 0 , sizeof(tTENDERPROGRESS));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tTENDERPROGRESS struct and then imported to self.                         */
/*----------------------------------------------------------------------------*/
pxTenderProgress&
pxTenderProgress :: operator=( const pxTenderProgress& src)
{
    tTENDERPROGRESS record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tTENDERPROGRESS structure 'src' to               */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxTenderProgress&
pxTenderProgress :: operator=( const tTENDERPROGRESS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxTenderProgress list objects being inserted in the               */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo                                                      */
/*----------------------------------------------------------------------------*/
int
pxTenderProgress :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxTenderProgress *that = (pxTenderProgress*)That;
    int retval = (TenderNo_ == that->TenderNo_) ? 0
               : (TenderNo_ > TenderNo_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTenderProgressList :: pxTenderProgressList
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
pxTenderProgressList :: Select
(
    const int count_
)
{
    tTENDERPROGRESS fil;
    memset(&fil, 0, sizeof(tTENDERPROGRESS));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via TenderNo,ArticleNo,KdauftragNr,OrderDate  */
/*----------------------------------------------------------------------------*/
size_t
pxTenderProgressList :: Select
(
    const long    TenderNo,
    const long    ArticleNo,
    const long    KdAuftragNr,
    const nDate&  OrderDate,
    const int     count_
)
{
    tTENDERPROGRESS fil;
    memset(&fil, 0, sizeof(tTENDERPROGRESS));  // zero out entire record buffer
    fil.TenderNo    = TenderNo;
    fil.ArticleNo   = ArticleNo;
    fil.KdAuftragNr = KdAuftragNr;
    fil.OrderDate   = OrderDate.GetYYYYMMDD(); // store key
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via TenderNo,ArticleNo,KdauftragNr,OrderDate  */
/*----------------------------------------------------------------------------*/
size_t
pxTenderProgressList :: Select
(
    const long    ArticleNo,
    const long    KdAuftragNr,
    const nDate&  OrderDate,
    const int     count_
)
{
    tTENDERPROGRESS fil;
    memset(&fil, 0, sizeof(tTENDERPROGRESS));  // zero out entire record buffer
    fil.ArticleNo   = ArticleNo;
    fil.KdAuftragNr = KdAuftragNr;
    fil.OrderDate   = OrderDate.GetYYYYMMDD(); // store key
    int cursorid = cCRTPGTENDERNOTENDERNO;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via TenderNo, ArticleNo                       */
/*----------------------------------------------------------------------------*/
size_t
pxTenderProgressList :: Select
(
    const long    TenderNo,
    const long    ArticleNo,
    const int     count_
)
{
    tTENDERPROGRESS fil;
    memset(&fil, 0, sizeof(tTENDERPROGRESS));  // zero out entire record buffer
    fil.TenderNo    = TenderNo;
    fil.ArticleNo   = ArticleNo;
    int cursorid   = cCRTPGTENDERNOARTICLENO;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxTenderProgressList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxTenderProgress' object:
    pxTenderProgress *objectp = new pxTenderProgress(Session(), *(tTENDERPROGRESS*)record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxTenderProgress :: Get
(
    DBAccessMode mode
)
{
    tTENDERPROGRESS record;
    memset(&record, 0, sizeof(tTENDERPROGRESS));
    record.TenderNo    = TenderNo_;
    record.ArticleNo   = ArticleNo_;
    record.KdAuftragNr = KdAuftragNr_;
    record.OrderDate   = OrderDate_.GetYYYYMMDD(); // store key
    record.PosNr       = PosNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;        // import the data from tARTICLEQUOTA struct
   /* else if ( retval > cDBXR_NORMAL )
        ExternalCondition(CMsgStream(), CMSG_AQUOT_ENTRY_NOTFOUND, BranchNo_, CustomerNo_, ArticleNo_);
   */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxTenderProgress :: Put
(
)
{
    tTENDERPROGRESS record;
    memset(&record, 0, sizeof(tTENDERPROGRESS));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tTENDERPROGRESS));
}

/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxTenderProgress :: Delete
(
)
{
    tTENDERPROGRESS record;
    memset(&record, 0, sizeof(tTENDERPROGRESS));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxTenderProgress :: Read
(
    const void *record
)
{
    return pxTenderProgressRead((tTENDERPROGRESS*)record);
}

int
pxTenderProgress :: ReadLock
(
    const void *record
)
{
    return pxTenderProgressReadLock((tTENDERPROGRESS*)record);
}

int
pxTenderProgress :: Update
(
    const void *record
)
{
    return pxTenderProgressUpdate((tTENDERPROGRESS*)record);
}

int
pxTenderProgress :: Delete
(
    const void *record
)
{
    return pxTenderProgressDelete((tTENDERPROGRESS*)record);
}

int
pxTenderProgress :: Insert
(
    const void  *record
)
{
    return pxTenderProgressInsert((tTENDERPROGRESS*)record);
}

int
pxTenderProgressList :: EndBrowse
(
    const int cursorid
)
{
    return pxTenderProgressEndBrowse(cursorid);
}

int
pxTenderProgressList :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxTenderProgressGetNext((tTENDERPROGRESS*)record, cursorid);
}

int
pxTenderProgressList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    return pxTenderProgressStartBrowse((tTENDERPROGRESS*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  SumDeliveryQty: this methode accumulates the deliveryqty of all entries   */
/*  within this list                                                          */
/*----------------------------------------------------------------------------*/
long
pxTenderProgressList :: SumDeliveryQty
(
)
{
    long sum = 0;
    pxTenderProgress *curp;
    pxTenderProgressListIter cursor(*this);
    while ( (curp = (pxTenderProgress*) ++cursor) != NULL )
    {
        sum += curp->DeliveryQty();
    }
    return sum;
}

/*----------------------------------------------------------------------------*/
/*  SumReturnQty: this methode accumulates the deliveryqty of all entries     */
/*  within this list                                                          */
/*----------------------------------------------------------------------------*/
long
pxTenderProgressList :: SumReturnQty
(
)
{
    long sum = 0;
    pxTenderProgress  *curp;
    pxTenderProgressListIter cursor(*this);
    while ( (curp = (pxTenderProgress*) ++cursor) != NULL )
    {
        sum += curp->ReturnQty();
    }
    return sum;
}
