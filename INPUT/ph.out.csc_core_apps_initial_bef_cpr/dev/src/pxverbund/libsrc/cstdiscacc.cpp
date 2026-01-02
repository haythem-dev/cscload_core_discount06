#include "pxcstdiscacc.hpp"
#include <pxdbxx.h>
#include <money.hpp>
#include "pxsess.hpp"
#include "pxbase/pxconstants.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxCstDiscAcc :: pxCstDiscAcc
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
pxCstDiscAcc :: pxCstDiscAcc
(
    pxCstDiscAcc& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tCSTDISCACC structure to construct this instance.                     */
/*----------------------------------------------------------------------------*/
pxCstDiscAcc :: pxCstDiscAcc
(
    pxSession   *session,
    tCSTDISCACC& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCstDiscAcc :: pxCstDiscAcc
(
    pxSession *session,
    const pxCstDiscAcc *src
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
pxCstDiscAcc :: pxCstDiscAcc
(
    pxSession    *session,
    short        BranchNo,            // Branchnumber
    long         CustomerNo           // Customernumber

)
    : pxDBRecord(session)
{
    Init();
    BranchNo_    = BranchNo;
    CustomerNo_  = CustomerNo;
   // Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCstDiscAcc :: pxCstDiscAcc
(
    pxSession    *session,
    short         BranchNo,            // Branchnumber
    long          CustomerNo,          // Customernumber
    nDate&        InvoiceDate,         // InvoiceDate
    nString&      InvoiceNo,           // InvoiceNumber
    nString&      VoucherTyp           // VoucherTyp
)
    : pxDBRecord(session)
{
    Init();
    BranchNo_       = BranchNo;
    CustomerNo_     = CustomerNo;
    Date_           = InvoiceDate;
    InvoiceNumber_  = InvoiceNo;
    VoucherTyp_     = VoucherTyp;
   // Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCstDiscAcc :: ~pxCstDiscAcc()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tCSTDISCACC structure.         */
/*----------------------------------------------------------------------------*/
tCSTDISCACC&
Assign
(
    tCSTDISCACC&           dest,
    const pxCstDiscAcc&    src
)
{
    dest.BranchNo                 = src.BranchNo_              ;
    dest.CustomerNo               = src.CustomerNo_            ;
    dest.MainCstNo                = src.MainCstNo_             ;
    dest.Balance                  = src.Balance_               ;
    dest.KdAuftragNr              = src.KdAuftragNr_           ;
    dest.Date                     = src.Date_.GetYYYYMMDD()    ;
    dest.InvoiceAmount            = src.InvoiceAmount_         ;
    dest.Preis_Typ                = static_cast<short>(src.PreisTyp_);
    dest.Priority                 = src.Priority_              ;
    dest.KdAuftragNrSplit         = src.KdAuftragNrSplit_      ;
    dest.InvoicePaid              = src.InvoicePaid_           ;
    dest.PaymentTarget            = src.PaymentTarget_         ;
    dest.LfdNr                    = src.LfdNr_                 ;

   // strings
    dest.InvoiceNumber[0] = ' ';
    src.InvoiceNumber_.GetData(dest.InvoiceNumber);
    dest.VoucherTyp[0] = ' ';
    src.VoucherTyp_.GetData(dest.VoucherTyp);
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tCSTDISCACC structure to                   */
/*  a pxCstDiscAcc object.                                                    */
/*----------------------------------------------------------------------------*/
pxCstDiscAcc&
Assign
(
    pxCstDiscAcc&         dest,
    const tCSTDISCACC&    src
)
{
    dest.BranchNo_                 = src.BranchNo              ;
    dest.CustomerNo_               = src.CustomerNo            ;
    dest.MainCstNo_                = src.MainCstNo             ;
    dest.Balance_                  = src.Balance               ;
    dest.KdAuftragNr_              = src.KdAuftragNr           ;
    dest.Date_                     = nDate(src.Date)           ;
    dest.InvoiceNumber_            = src.InvoiceNumber         ;
    dest.InvoiceAmount_            = src.InvoiceAmount         ;
    dest.VoucherTyp_               = src.VoucherTyp            ;
    dest.PreisTyp_                 = static_cast<PriceTypeEnum>(src.Preis_Typ);
    dest.Priority_                 = src.Priority              ;
    dest.KdAuftragNrSplit_         = src.KdAuftragNrSplit      ;
    dest.InvoicePaid_              = src.InvoicePaid           ;
    dest.PaymentTarget_            = src.PaymentTarget         ;
    dest.LfdNr_                    = src.LfdNr                 ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCstDiscAcc :: Init()
{
    tCSTDISCACC record;
    memset(&record, 0, sizeof(tCSTDISCACC));
    Assign(*this, record);
    RemainInList_ = false;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tCSTDISCACC struct and then imported to self.                             */
/*----------------------------------------------------------------------------*/
pxCstDiscAcc&
pxCstDiscAcc :: operator=( const pxCstDiscAcc& src)
{
    tCSTDISCACC record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tCSTDISCACC structure 'src' to                   */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxCstDiscAcc&
pxCstDiscAcc :: operator=( const tCSTDISCACC& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxCstDiscAcc list objects being inserted in the                   */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo,MainCstNo,Date                                       */
/*----------------------------------------------------------------------------*/
int
pxCstDiscAcc :: CompareTo
(
    const nCollectable   *That,
          void           *,
    const long
)   const
{
    pxCstDiscAcc *that = (pxCstDiscAcc*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
               : (BranchNo_ > BranchNo_ ? 1 : -1);
    if ( retval == 0 )
        retval = (CustomerNo_ == that->CustomerNo_) ? 0
               : (CustomerNo_ > CustomerNo_ ? 1 : -1);
    if ( retval == 0 )
        retval = (MainCstNo_ == that->MainCstNo_) ? 0
               : (MainCstNo_ > that->MainCstNo_ ? 1 : -1);
    if ( retval == 0 )
        retval = (Date_ == that->Date_) ? 0
               : (Date_ > that->Date_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCstDiscAccList :: pxCstDiscAccList
(
    pxSession *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
    for (ArrayBranchNoIndex_ = 0; ArrayBranchNoIndex_ < 10; ++ArrayBranchNoIndex_)
    {
        ArrayBranchNo_[ArrayBranchNoIndex_] = 0;
    }
    ArrayBranchNoIndex_ = 0;
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxCstDiscAccList :: Select
(
    const int count_
)
{
    tCSTDISCACC fil;
    memset(&fil, 0, sizeof(tCSTDISCACC));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo                                */
/*----------------------------------------------------------------------------*/
size_t
pxCstDiscAccList :: Select
(
    const short   BranchNo,
    const long    CustomerNo,
    const short   /*TaxLevel*/,
    const nDate&  Date,
    const int     count_
)
{
    tCSTDISCACC fil;
    memset(&fil, 0, sizeof(tCSTDISCACC));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    fil.Date       = Date.GetYYYYMMDD();
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo,DateFrom.DateTo                */
/*----------------------------------------------------------------------------*/
size_t
pxCstDiscAccList :: Select
(
    const short   BranchNo,
    const long    CustomerNo,
    const nDate&  DateFrom,
    const nDate&  DateTo,
    const int     count_
)
{
    tCSTDISCACC fil;
    memset(&fil, 0, sizeof(tCSTDISCACC));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    fil.Date       = DateFrom.GetYYYYMMDD();
    DateTo_        = DateTo;
    int cursorid  = cCRCDACUSTOMERNO;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via MainCstNo,DateFrom.DateTo                 */
/*----------------------------------------------------------------------------*/
size_t
pxCstDiscAccList :: Select
(
    const long    MainCstNo,
    const nDate&  DateFrom,
    const nDate&  DateTo,
    const int     count_
)
{
    tCSTDISCACC fil;
    memset(&fil, 0, sizeof(tCSTDISCACC));  // zero out entire record buffer
    fil.MainCstNo  = MainCstNo;
    fil.Date       = DateFrom.GetYYYYMMDD();
    DateTo_        = DateTo;
    int cursorid  = cCRCDAMAINCSTNO;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo,DateFrom.DateTo                */
/*----------------------------------------------------------------------------*/
size_t
pxCstDiscAccList :: Select
(
    const short    BranchNo,
    const long     CustomerNo,
    const nDate&   DateFrom,
    const nDate&   DateTo,
    const nString& VoucherTyp,
    const int      count_
)
{
    tCSTDISCACC fil;
    memset(&fil, 0, sizeof(tCSTDISCACC));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    fil.Date       = DateFrom.GetYYYYMMDD();
    DateTo_        = DateTo;
    fil.VoucherTyp[0] = ' ';
    VoucherTyp.GetData(fil.VoucherTyp);
    int cursorid = cCRCDACUSTOMERNOVOUCHERTYP;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via MainCstNo,DateFrom.DateTo                 */
/*----------------------------------------------------------------------------*/
size_t
pxCstDiscAccList :: Select
(
    const long     MainCstNo,
    const nDate&   DateFrom,
    const nDate&   DateTo,
    const nString& VoucherTyp,
    const int      count_
)
{
    tCSTDISCACC fil;
    memset(&fil, 0, sizeof(tCSTDISCACC));  // zero out entire record buffer
    fil.MainCstNo  = MainCstNo;
    fil.Date       = DateFrom.GetYYYYMMDD();
    DateTo_        = DateTo;
    fil.VoucherTyp[0] = ' ';
    VoucherTyp.GetData(fil.VoucherTyp);
    int cursorid = cCRCDAMAINCSTNOVOUCHERTYP;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via MainCstNo,DateFrom.DateTo                 */
/*----------------------------------------------------------------------------*/
size_t
pxCstDiscAccList :: Select
(
    const long    KdAuftragNr,
    const int     count_
)
{
    tCSTDISCACC fil;
    memset(&fil, 0, sizeof(tCSTDISCACC));  // zero out entire record buffer
    fil.KdAuftragNr  = KdAuftragNr;
    int cursorid  = cCRCDAKDAUFTRAGNR;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCstDiscAccList :: AddToList
(
    const void  *record,
    const int
)
{
    // construct new 'pxCstDiscAcc' object:
    pxCstDiscAcc *objectp = new pxCstDiscAcc(Session(), *(tCSTDISCACC*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  This methode just increases Balance_ by value                             */
/*----------------------------------------------------------------------------*/
nMoney
pxCstDiscAcc :: IncreaseBalance
(
    nMoney value
)
{
    Balance_ += value;
    SetDirty();
    return Balance_;
}

/*----------------------------------------------------------------------------*/
/*  This methode just decreases Balance_ by value                             */
/*----------------------------------------------------------------------------*/
nMoney
pxCstDiscAcc :: DecreaseBalance
(
    nMoney value
)
{
    Balance_ -= value;

    return Balance_;
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCstDiscAcc :: Get
(
    DBAccessMode mode
)
{
    tCSTDISCACC record;
    memset(&record, 0, sizeof(tCSTDISCACC));
    record.BranchNo   = BranchNo_;
    record.CustomerNo = CustomerNo_;
    record.Date       = Date_.GetYYYYMMDD();

    record.InvoiceNumber[0] = ' ';
    InvoiceNumber_.GetData(record.InvoiceNumber);
    record.VoucherTyp[0] = ' ';
    VoucherTyp_.GetData(record.VoucherTyp);
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;        // import the data from tCSTDISCACC struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/* CalcPaymentTarget.                                                         */
/*----------------------------------------------------------------------------*/
void
pxCstDiscAcc :: CalcPaymentTarget
(
    long DueDate,
    long LastPaymentDate
)
{
    nDate now;
    nDate Fdate(DueDate);
    nDate Ldate(LastPaymentDate);
    long nowDays    = now.GetAbsday();
    long FdateDays  = Fdate.GetAbsday();
    long LdateDays  = Ldate.GetAbsday();
    PaymentTarget_ = 0;

    if ( DueDate == 0 )
    {
       PaymentTarget_ = 0;
    }
    else
    if ( FdateDays >= nowDays &&  Ldate == pxConstants::NullDate && ( InvoiceAmount() - InvoicePaid() > pxConstants::dZero ) )
    {
       PaymentTarget_ = 0;
    }
    else
    if ( FdateDays > nowDays  &&  LdateDays < FdateDays )
    {
       PaymentTarget_ = 0;
    }
    else
    if ( FdateDays < nowDays &&  Ldate == pxConstants::NullDate && ( InvoiceAmount() - InvoicePaid() > pxConstants::dZero ) )
    {
       PaymentTarget_ = (short)(nowDays - FdateDays);
    }
    else
    if ( FdateDays < nowDays &&  LdateDays < FdateDays &&  ( InvoiceAmount() - InvoicePaid() == pxConstants::dZero ) )
    {
       PaymentTarget_ = 0;
    }
    else
    if ( FdateDays < nowDays &&  LdateDays < FdateDays &&  ( InvoiceAmount() - InvoicePaid() > pxConstants::dZero ) )
    {
       PaymentTarget_ = (short)(nowDays - FdateDays);
    }
    else
    if ( FdateDays < nowDays &&  LdateDays > FdateDays &&  ( InvoiceAmount() - InvoicePaid() == pxConstants::dZero ) )
    {
       PaymentTarget_ = (short)(LdateDays - FdateDays);
    }
    else
    if ( FdateDays < nowDays &&  LdateDays > FdateDays &&  ( InvoiceAmount() - InvoicePaid() > pxConstants::dZero ) )
    {
       PaymentTarget_ = (short)(nowDays - FdateDays);
    }
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCstDiscAcc :: Put
(
)
{
    tCSTDISCACC record;
    memset(&record, 0, sizeof(tCSTDISCACC));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tCSTDISCACC));
}

/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxCstDiscAcc :: Delete
(
)
{
    tCSTDISCACC record;
    memset(&record, 0, sizeof(tCSTDISCACC));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxCstDiscAcc :: Read
(
    const void *record
)
{
    return pxCstDiscAccRead((tCSTDISCACC*)record);
}

int
pxCstDiscAcc :: ReadLock
(
    const void *record
)
{
    return pxCstDiscAccReadLock((tCSTDISCACC*)record);
}

int
pxCstDiscAcc :: Update
(
    const void *record
)
{
    return pxCstDiscAccUpdate((tCSTDISCACC*)record);
}

int
pxCstDiscAcc :: Delete
(
    const void *record
)
{
    return pxCstDiscAccDelete((tCSTDISCACC*)record);
}

int
pxCstDiscAcc :: Insert
(
    const void *record
)
{
    return pxCstDiscAccInsert((tCSTDISCACC*)record);
}

int
pxCstDiscAccList :: EndBrowse
(
    const int cursorid
)
{
    return pxCstDiscAccEndBrowse(cursorid);
}

int
pxCstDiscAccList :: GetNext
(
    const void *record,
    const int  cursorid
)
{
    return pxCstDiscAccGetNext((tCSTDISCACC*)record, cursorid);
}

int
pxCstDiscAccList :: StartBrowse
(
    const void *keys,
    const int  cursorid
)
{
    long  dateto = DateTo_.GetYYYYMMDD();
    return pxCstDiscAccStartBrowse((tCSTDISCACC*)keys, cursorid,dateto);
}

/*----------------------------------------------------------------------------*/
/* Find returns a pxCstDiscAcc pointer to the corresponding entry depend on   */
/* given TaxLevel. If entry is not found within the list , so NULLP will      */
/* be returned                                                                */
/*----------------------------------------------------------------------------*/
pxCstDiscAcc*
pxCstDiscAccList :: Find
(
)
{
    pxCstDiscAccListIter   iter( *this );           // define iterator
    pxCstDiscAcc           *entryp = NULL;         // pointer to listentry

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        break;
    }
    return entryp;                               // return entrypointer
}

/*----------------------------------------------------------------------------*/
/* Find returns a pxCstDiscAcc pointer to the corresponding entry depend on   */
/* given Params. If entry is not found within the list , so NULLP will        */
/* be returned                                                                */
/*----------------------------------------------------------------------------*/
pxCstDiscAcc*
pxCstDiscAccList :: Find
(
    const short BranchNo,
    const long CustomerNo,
    const nString& InvoiceNo,
    const nString& VoucherTyp,
    const long    LfdNr
)
{
    pxCstDiscAccListIter   iter( *this );           // define iterator
    pxCstDiscAcc           *entryp = NULL;         // pointer to listentry

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        if ( entryp->BranchNo() == BranchNo && entryp->CustomerNo() == CustomerNo &&
             entryp->InvoiceNumber() == InvoiceNo &&
             entryp->VoucherTyp() == VoucherTyp &&  entryp->LfdNr() == LfdNr )
        {
            break;
        }
    }
    return   entryp;                               // return entrypointer
}

/*----------------------------------------------------------------------------*/
/* Find returns a pxCstDiscAcc pointer to the corresponding entry depend on   */
/* given Params. If entry is not found within the list , so NULLP will        */
/* be returned                                                                */
/*----------------------------------------------------------------------------*/
pxCstDiscAcc*
pxCstDiscAccList :: Find
(
    const short BranchNo,
    const long CustomerNo,
    const nDate& InvoiceDate,
    const nString& InvoiceNo,
    const nString& VoucherTyp
)
{
    pxCstDiscAccListIter   iter( *this );           // define iterator
    pxCstDiscAcc           *entryp = NULL;         // pointer to listentry

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        if ( entryp->BranchNo() == BranchNo && entryp->CustomerNo() == CustomerNo &&
             entryp->Date() == InvoiceDate && entryp->InvoiceNumber() == InvoiceNo &&
             entryp->VoucherTyp() == VoucherTyp )
        {
            break;
        }
    }
    return   entryp;                               // return entrypointer
}

/*----------------------------------------------------------------------------*/
/* ShrinkAndUnlockRemainInList: this methode looks for entries without        */
/* setting the remaininlist flag. These members are deleted from the list.    */
/* The member KdAuftragNr will be set to Zero on the database                 */
/*----------------------------------------------------------------------------*/
size_t
pxCstDiscAccList :: ShrinkAndUnlockRemainInList
(
)
{
    pxCstDiscAccListIter   iter( *this );           // define iterator
    pxCstDiscAcc           *entryp = NULL;          // pointer to listentry

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        if ( !entryp->IsRemainInList() )
        {
            // now unlock entryp
            entryp->nDBBeginTransaction(cDBTransRecord);
            entryp->Get(cDBGET_FORUPDATE);
            if ( entryp->IsGoodState() )
            {
                entryp->SetKdAuftragNr(0);
                entryp->Put();
                if ( entryp->IsGoodState() )
                {
                    entryp->nDBCommit(cDBTransRecord);
                }
                else
                {
                    entryp->nDBRollBack();
                }
            }
            else
            {
                entryp->nDBRollBack();
            }
            delete iter.Remove();
        }
    }
    return   Entries();                       // return entries
}

/*----------------------------------------------------------------------------*/
/* MarkEntriesRemainInList: this methode sets every entry within this list    */
/* to  remaininlist.                                                          */
/*----------------------------------------------------------------------------*/
size_t
pxCstDiscAccList :: MarkEntriesRemainInList
(
)
{
    pxCstDiscAccListIter   iter( *this );          // define iterator
    pxCstDiscAcc           *entryp = NULL;         // pointer to listentry

    iter.Reset();                                  // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        entryp->SetRemainInList();
    }
    return   Entries();                       // return entries
}

/*----------------------------------------------------------------------------*/
/* GetBalance Returns the Balance of the entry given by TaxLevel              */
/*----------------------------------------------------------------------------*/
double
pxCstDiscAccList :: GetBalance
(
)
{
    double balance(0.0);

    pxCstDiscAcc *entryp = Find();          // Find entry
    if ( entryp )                           // entry found
    {
        balance = entryp->Balance();
    }
    return   balance;                       // return value
}

/*----------------------------------------------------------------------------*/
/*  This methode just increases Balance_ by value depend on TaxLevel          */
/*----------------------------------------------------------------------------*/
nMoney
pxCstDiscAccList :: IncreaseBalance
(
    nMoney value
)
{
    double balance(0.0);
    pxCstDiscAcc    *entryp = Find();       // Find entry
    if ( entryp )                           // entry found
    {
        entryp->IncreaseBalance(value);
        entryp->SetDirty();
        balance = entryp->Balance();
    }
    return balance;
}

/*----------------------------------------------------------------------------*/
/*  This methode just decreases Balance_ by value depend on TaxLevel          */
/*----------------------------------------------------------------------------*/
int
pxCstDiscAccList :: DecreaseBalance
(
    nMoney value
)
{
    nMoney balance = value;
    int  retval = 0;
    pxCstDiscAccListIter   iter( *this );           // define iterator
    pxCstDiscAcc           *entryp = NULL;         // pointer to listentry

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxCstDiscAcc*) ++iter) != NULL ) // browse list
    {
        if ( entryp->Balance() == pxConstants::dZero )
        {
            continue;
        }
        if ( (double) balance <= entryp->Balance() )
        {
            entryp->DecreaseBalance(balance);
            SetArrayBranchNo(entryp->BranchNo());
        }
        else
        {
            balance -= entryp->Balance();
            entryp->DecreaseBalance(entryp->Balance());
            SetArrayBranchNo(entryp->BranchNo());
            continue;
        }
        break;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  FindArrayBranchno: returns true if BranchNo is available within           */
/*  the ArrayBranchNo,otherwise false will be returned                        */
/*----------------------------------------------------------------------------*/
bool
pxCstDiscAccList :: FindArrayBranchno
(
    const short BranchNo
)
{
    bool retval = false;
    for (ArrayBranchNoIndex_ = 0; ArrayBranchNoIndex_ < 10; ++ArrayBranchNoIndex_)
    {
        if ( ArrayBranchNo_[ArrayBranchNoIndex_] == BranchNo )
        {
            retval = true;
            break;
        }
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  SetArrayBranchNo: if  BranchNo is  already within the ArrayBranchNo       */
/*  no action takes place, otherwise BranchNo will be stored on the next free */
/*  within the ArrayBranchNo                                                  */
/*----------------------------------------------------------------------------*/
void
pxCstDiscAccList :: SetArrayBranchNo
(
    const short BranchNo
)
{
    if ( FindArrayBranchno(BranchNo) )
        return;

    // now place BranchNo
    for (ArrayBranchNoIndex_ = 0; ArrayBranchNoIndex_ < 10; ++ArrayBranchNoIndex_)
    {
        if ( ArrayBranchNo_[ArrayBranchNoIndex_] == 0 )
        {
            ArrayBranchNo_[ArrayBranchNoIndex_] = BranchNo;
            break;
        }
    }
}
