#include "pxcuststockreserved.hpp"
#include "tcststockrsrvd.h"
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCustStockReserved :: pxCustStockReserved
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
pxCustStockReserved :: pxCustStockReserved
(
    pxCustStockReserved& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCSTSTOCKRESERVED structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxCustStockReserved :: pxCustStockReserved
(
    pxSession   *session,
    tCSTSTOCKRESERVED& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxCustStockReserved :: pxCustStockReserved
(
    pxSession    *session,
    const short       BranchNo,
    const long        CustomerNo,
    const long        ArticleNo,
	const basar::DateTime& DateTimeFrom,
    const ReservationTypeEnum ReservType
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_          = BranchNo;
    CustomerNo_        = CustomerNo;
    ArticleNo_         = ArticleNo;
	DateTimeFrom_      = DateTimeFrom;
    ReservType_        = ReservType;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustStockReserved :: ~pxCustStockReserved()
{
}

/*----------------------------------------------------------------------------*/
/* Assign the values of the 'src' object to a tCSTSTOCKRESERVED structure     */
/*----------------------------------------------------------------------------*/
tCSTSTOCKRESERVED&
pxCustStockReserved :: AssignTo
(
    tCSTSTOCKRESERVED&           dest
) const
{
    dest.BranchNo                  = BranchNo_;
    dest.CustomerNo                = CustomerNo_;
    dest.ArticleNo                 = ArticleNo_;
    dest.ReservedQty               = ReservedQty_;
    dest.DateFrom                  = DateTimeFrom_.getDate();
    dest.TimeFrom                  = DateTimeFrom_.getTime() / 1000;
    dest.DateTo                    = DateTimeTo_.getDate();
    dest.TimeTo                    = DateTimeTo_.getTime() / 1000;
    dest.KdAuftragNr               = KdAuftragNr_;
    dest.ReservType                = static_cast<short>(ReservType_);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCSTSTOCKRESERVED structure to             */
/*  a pxCustStockReserved object.                                             */
/*----------------------------------------------------------------------------*/
pxCustStockReserved&
pxCustStockReserved :: AssignFrom
(
//    pxCustStockReserved&              dest,
    const tCSTSTOCKRESERVED&    src
)
{
    BranchNo_                 = src.BranchNo;
    CustomerNo_               = src.CustomerNo;
    ArticleNo_                = src.ArticleNo;
    ReservedQty_              = src.ReservedQty;
	DateTimeFrom_             = basar::DateTime(src.DateFrom, src.TimeFrom * 1000);
    DateTimeTo_               = basar::DateTime(src.DateTo, src.TimeTo * 1000);
    KdAuftragNr_              = src.KdAuftragNr;
	ReservType_               = static_cast<ReservationTypeEnum>(src.ReservType);

    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustStockReserved :: Init()
{
    tCSTSTOCKRESERVED    record;
    memset(&record, 0 , sizeof(tCSTSTOCKRESERVED));
	AssignFrom(record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCSTSTOCKRESERVED struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxCustStockReserved&
pxCustStockReserved :: operator=( const pxCustStockReserved& src)
{
    tCSTSTOCKRESERVED record;               // used to export the data of 'src'
	AssignFrom(src.AssignTo(record));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCSTSTOCKRESERVED structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCustStockReserved&
pxCustStockReserved :: operator=( const tCSTSTOCKRESERVED& src)
{
    return AssignFrom(src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustStockReserved :: Get
(
    DBAccessMode mode
)

{
    tCSTSTOCKRESERVED record;
    memset(&record, 0, sizeof(tCSTSTOCKRESERVED));
    record.BranchNo      = BranchNo_;
    record.CustomerNo    = CustomerNo_;
    record.ArticleNo     = ArticleNo_;
    record.DateFrom      = DateTimeFrom_.getDate();
	record.ReservType    = static_cast<short>(ReservType_);

    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tCSTSTOCKRESERVED struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustStockReserved :: Put
(
)
{
    tCSTSTOCKRESERVED record;
    memset(&record, 0, sizeof(tCSTSTOCKRESERVED));
    AssignTo(record);
    return nDBWrite(&record, sizeof(tCSTSTOCKRESERVED));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxCustStockReserved :: Delete
(
)
{
    tCSTSTOCKRESERVED record;
    memset(&record, 0, sizeof(tCSTSTOCKRESERVED));
    AssignTo(record);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Add quantity q from quantity ordered. Returns quantity added.             */
/*----------------------------------------------------------------------------*/
long
pxCustStockReserved :: AddQuantity
(
    const long q
)
{
    ReservedQty_ += q;
    SetDirty();
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Subtract quantity q from quantity ordered. Returns quantity subtracted.   */
/*----------------------------------------------------------------------------*/
long
pxCustStockReserved :: SubQuantity
(
    const long q                      // quantity to be subtracted
)
{
    long retval;
    // avoid negative values in stock:
    retval = ( ReservedQty_ - q < 0 ) ? ReservedQty_ : q;
    ReservedQty_ -= retval;
    SetDirty();
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCustStockReserved :: Read
(
    const void  *record
)
{
	tCSTSTOCKRESERVED* recordp = (tCSTSTOCKRESERVED*)record;
	return pxCustStockReservedRead(recordp, Session()->getDatabaseName(recordp->BranchNo).c_str());
}

int
pxCustStockReserved :: ReadLock
(
    const void  *record
)
{
	tCSTSTOCKRESERVED* recordp = (tCSTSTOCKRESERVED*)record;
	return pxCustStockReservedReadLock(recordp, Session()->getDatabaseName(recordp->BranchNo).c_str());
}

int
pxCustStockReserved :: Update
(
    const void  *record
)
{
	tCSTSTOCKRESERVED* recordp = (tCSTSTOCKRESERVED*)record;
	return pxCustStockReservedUpdate(recordp, Session()->getDatabaseName(recordp->BranchNo).c_str());
}

int
pxCustStockReserved :: Delete
(
    const void  *record
)
{
	tCSTSTOCKRESERVED* recordp = (tCSTSTOCKRESERVED*)record;
	return pxCustStockReservedDelete(recordp, Session()->getDatabaseName(recordp->BranchNo).c_str());
}

int
pxCustStockReserved :: Insert
(
    const void  *record
)
{
	tCSTSTOCKRESERVED* recordp = (tCSTSTOCKRESERVED*)record;
    return pxCustStockReservedInsert(recordp, Session()->getDatabaseName(recordp->BranchNo).c_str());
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCustStockReserved list objects being inserted in the            */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxCustStockReserved :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxCustStockReserved *that = (pxCustStockReserved*)That;
    int retval = (ArticleNo_ == that->ArticleNo_) ? 0
                : (ArticleNo_ > that->ArticleNo_ ? 1 : -1);
    if ( retval == 0 )
       retval = (DateTimeFrom_ == that->DateTimeFrom_) ? 0
                : (DateTimeFrom_ > that->DateTimeFrom_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustStockReservedList :: pxCustStockReservedList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
pxCustStockReservedList :: ~pxCustStockReservedList
(
)
{
	Clear();
}

pxSession*
pxCustStockReservedList :: Session
(
)
{
	return (pxSession*) DataBase();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via Branchno and ArticleNo                    */
/*----------------------------------------------------------------------------*/
size_t
pxCustStockReservedList :: SelectAllReservations
(
    const short   BranchNo,
    const long    ArticleNo
)
{
    tCSTSTOCKRESERVED fil;
    memset(&fil, 0, sizeof(tCSTSTOCKRESERVED));  // zero out entire record buffer
    fil.BranchNo     = BranchNo;
    fil.ArticleNo    = ArticleNo;
    int cursorid    = cCRSCSTSTOCKRESERVED_AllReservations;
    nDBSelect(&fil, cursorid, cDEFAULT);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via Branchno, ArticleNo and CustomerNo        */
/*----------------------------------------------------------------------------*/
size_t
pxCustStockReservedList :: SelectCustomerReservations
(
    const short   BranchNo,
    const long    ArticleNo,
    const long    CustomerNo
)
{
    tCSTSTOCKRESERVED record;
    memset(&record, 0, sizeof(tCSTSTOCKRESERVED));  // zero out entire record buffer
    record.BranchNo   = BranchNo;
    record.CustomerNo = CustomerNo;
    record.ArticleNo  = ArticleNo;
    int cursorid     = cCRSCSTSTOCKRESERVED_CustomerReservations;
    nDBSelect(&record, cursorid, cDEFAULT);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via Branchno, DateTo and TimeTo               */
/*----------------------------------------------------------------------------*/
size_t
pxCustStockReservedList :: SelectOldReservations
(
	const short BranchNo,
	const basar::DateTime&  DateTimeTo
)
{
	tCSTSTOCKRESERVED record;
	memset(&record, 0, sizeof(tCSTSTOCKRESERVED));  // zero out entire record buffer
	record.BranchNo = BranchNo;
	record.DateTo   = DateTimeTo.getDate();
	record.TimeTo   = DateTimeTo.getTime() / 1000;
	int cursorid	= cCRSCSTSTOCKRESERVED_OldReservations;
	nDBSelect(&record, cursorid, cDEFAULT);
	return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustStockReservedList :: AddToList
(
    const void  *record,
    const int  /*row*/
)

{
    // construct new 'pxCustStockReserved' object:
    pxCustStockReserved *objectp = new pxCustStockReserved(Session(), *(tCSTSTOCKRESERVED*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
int
pxCustStockReservedList :: EndBrowse
(
    const int  /*cursorid*/
)
{
    return pxCustStockReservedEndBrowse();
}


/*----------------------------------------------------------------------------*/
int
pxCustStockReservedList :: GetNext
(
    const void  *record,
    const int  /*cursorid*/
)
{
    return pxCustStockReservedGetNext((tCSTSTOCKRESERVED*)record);
}

/*----------------------------------------------------------------------------*/
int
pxCustStockReservedList :: StartBrowse
(
    const void  *record,
    const int  cursorid
)
{
	tCSTSTOCKRESERVED* recordp = (tCSTSTOCKRESERVED*)record;
	return pxCustStockReservedStartBrowse(recordp, Session()->getDatabaseName(recordp->BranchNo).c_str(), cursorid);
}

/*----------------------------------------------------------------------------*/
