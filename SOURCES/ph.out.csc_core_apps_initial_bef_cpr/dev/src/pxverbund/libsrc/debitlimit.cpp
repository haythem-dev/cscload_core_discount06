#include "pxdebitlimit.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxbase/pxconstants.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxDebitLimit :: pxDebitLimit
(
    pxSession* session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDebitLimit :: pxDebitLimit
(
    pxDebitLimit& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tDEBTLIMIT structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxDebitLimit :: pxDebitLimit
(
    pxSession* session,
    tDEBTLIMIT& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDebitLimit :: pxDebitLimit
(
    pxSession*   session,
    long         PartnerNo,          // partner number
    short        LimitType,
    DBAccessMode mode

)
    : pxDBRecord(session)
{
    Init();
    PartnerNo_ = PartnerNo;
    LimitType_ = LimitType;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxDebitLimit :: ~pxDebitLimit()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tDEBTLIMIT structure.         */
/*----------------------------------------------------------------------------*/
tDEBTLIMIT&
Assign
(
    tDEBTLIMIT&         dest,
    const pxDebitLimit& src
)
{
    dest.PartnerNo      = src.PartnerNo_;
    dest.PartnerName[0] = ' ';
    src.PartnerName_.GetData((char*)dest.PartnerName);
    dest.Limit          = src.Limit_;
    dest.Sum_DebitSide  = src.SumDebitSide_;
    dest.Sum_CreditSide = src.SumCreditSide_;
    dest.Sum_MonTurnOver = src.SumMonTurnOver_;
    dest.Sum_DayTurnOver = src.SumDayTurnOver_;
    dest.Sum_Returns    = src.SumReturns_;
    dest.Sum_GoodsReceipt = src.SumGoodsReceipt_;
    dest.LimitType      = src.LimitType_;
    dest.Liste5         = src.Liste5_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tDEBTLIMIT structure to                   */
/*  a pxDebitLimit object.                                                    */
/*----------------------------------------------------------------------------*/
pxDebitLimit&
Assign
(
    pxDebitLimit&     dest,
    const tDEBTLIMIT& src
)
{
    dest.PartnerNo_       = src.PartnerNo;
    dest.PartnerName_     = src.PartnerName;
    dest.Limit_           = src.Limit;
    dest.SumDebitSide_    = src.Sum_DebitSide;
    dest.SumCreditSide_   = src.Sum_CreditSide;
    dest.SumMonTurnOver_  = src.Sum_MonTurnOver;
    dest.SumDayTurnOver_  = src.Sum_DayTurnOver;
    dest.SumReturns_      = src.Sum_Returns;
    dest.SumGoodsReceipt_ = src.Sum_GoodsReceipt;
    dest.LimitType_       = src.LimitType;
    dest.Liste5_          = src.Liste5;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxDebitLimit :: Init()
{
    tDEBTLIMIT record;
    memset(&record, 0 , sizeof(tDEBTLIMIT));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tDEBTLIMIT struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxDebitLimit&
pxDebitLimit :: operator=( const pxDebitLimit& src)
{
    tDEBTLIMIT record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDEBTLIMIT structure 'src' to                    */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxDebitLimit&
pxDebitLimit :: operator=( const tDEBTLIMIT& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  This methode returns the sum of all open positions                        */
/*----------------------------------------------------------------------------*/
nMoney
pxDebitLimit :: SumAdvanceAccount
(
)
{
    nMoney total = 0.0;
    total += SumDebitSide_;
    total += SumCreditSide_;
    total += SumMonTurnOver_;
    total += SumDayTurnOver_;
    total -= SumReturns_;
    total -= SumGoodsReceipt_;
    return total;
}

/*----------------------------------------------------------------------------*/
/*  This methode just increases SumDayTurnOver_ by value                      */
/*----------------------------------------------------------------------------*/
nMoney
pxDebitLimit :: IncreaseDayTurnOver
(
    nMoney value
)
{
    return SumDayTurnOver_ += value;
}

/*----------------------------------------------------------------------------*/
/*  This methode just decreases SumDayTurnOver_ by value                      */
/*----------------------------------------------------------------------------*/
nMoney
pxDebitLimit :: DecreaseDayTurnOver
(
    nMoney value
)
{
    return SumDayTurnOver_ -= value;
}

/*----------------------------------------------------------------------------*/
/*  This methode just sets SumCreditSide_ by value                            */
/*----------------------------------------------------------------------------*/
nMoney
pxDebitLimit :: SetSumDebitSide
(
    nMoney value
)
{
    return SumDebitSide_ = value;
}

/*----------------------------------------------------------------------------*/
/*  This methode just increases SumDebitSide_  by  value                      */
/*----------------------------------------------------------------------------*/
nMoney
pxDebitLimit :: DecreaseSumDebitSide
(
    nMoney value
)
{
    nMoney retval = ( SumDebitSide_ - value < pxConstants::mZero ) ? SumDebitSide_ : value;
    return SumDebitSide_ -= retval;
}

/*----------------------------------------------------------------------------*/
/*  This methode just increases SumDebitSide_  by  value                      */
/*----------------------------------------------------------------------------*/
nMoney
pxDebitLimit :: IncreaseSumDebitSide
(
    nMoney value
)
{
    return SumDebitSide_ += value;
}

/*----------------------------------------------------------------------------*/
/*  This methode just increases SumGoodsReceipt_  by  value                   */
/*----------------------------------------------------------------------------*/
nMoney
pxDebitLimit :: DecreaseSumGoodsReceipt
(
    nMoney value
)
{
    nMoney retval = ( SumGoodsReceipt_ - value < pxConstants::mZero ) ? SumGoodsReceipt_ : value;
    return SumGoodsReceipt_ -= retval;
}

/*----------------------------------------------------------------------------*/
/*  This methode just increases SumGoodsReceipt  by  value                    */
/*----------------------------------------------------------------------------*/
nMoney
pxDebitLimit :: IncreaseSumGoodsReceipt
(
    nMoney value
)
{
    return SumGoodsReceipt_ += value;
}

/*----------------------------------------------------------------------------*/
/*  This methode just increases SumReturns_  by  value                        */
/*----------------------------------------------------------------------------*/
nMoney
pxDebitLimit :: DecreaseSumReturns
(
    nMoney value
)
{
    nMoney retval = ( SumReturns_ - value < pxConstants::mZero ) ? SumReturns_ : value;
    return SumReturns_ -= retval;
}

/*----------------------------------------------------------------------------*/
/*  This methode just increases SumReturns  by  value                         */
/*----------------------------------------------------------------------------*/
nMoney
pxDebitLimit :: IncreaseSumReturns
(
    nMoney value
)
{
    return SumReturns_ += value;
}

/*----------------------------------------------------------------------------*/
/*  RestCreditLimit: return Nullm or customer rest creditlimit                */
/*----------------------------------------------------------------------------*/
nMoney
pxDebitLimit :: RestCreditLimit
(
)
{
    return (Limit_ - SumAdvanceAccount());
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxDebitLimit :: Get
(
    DBAccessMode mode
)
{
    tDEBTLIMIT record;
    memset(&record, 0, sizeof(tDEBTLIMIT));
    record.PartnerNo = PartnerNo_;
    record.LimitType = LimitType_;
    int retval = (mode == cDBGET_FORUPDATE) ? nDBReadLock(&record) : nDBRead(&record);
    if (retval == 0)
       (*this) = record;        // import the data from tDEBTLIMIT struct
    else if (retval > cDBXR_NORMAL)
       ExternalCondition(CMsgStream(), CMSG_DEBITLIMIT_NOTFOUND, PartnerNo_);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxDebitLimit :: Put
(
)
{
    tDEBTLIMIT record;
    memset(&record, 0, sizeof(tDEBTLIMIT));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tDEBTLIMIT));
}

/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxDebitLimit :: Delete
(
)
{
    tDEBTLIMIT record;
    memset(&record, 0, sizeof(tDEBTLIMIT));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxDebitLimit :: Read
(
    const void* record
)
{
    return pxDebitLimitRead((tDEBTLIMIT*)record);
}

int
pxDebitLimit :: ReadLock
(
    const void* record
)
{
    return pxDebitLimitReadLock((tDEBTLIMIT*)record);
}

int
pxDebitLimit :: Update
(
    const void* record
)
{
    return pxDebitLimitUpdate((tDEBTLIMIT*)record);
}

int
pxDebitLimit :: Delete
(
    const void* record
)
{
    return pxDebitLimitDelete((tDEBTLIMIT*)record);
}

int
pxDebitLimit :: Insert
(
    const void* record
)
{
    return pxDebitLimitInsert((tDEBTLIMIT*)record);
}

int
pxDebitLimitList :: EndBrowse
(
    const int cursorid
)
{
    return pxDebitLimitEndBrowse(cursorid);
}


int
pxDebitLimitList :: GetNext
(
    const void* record,
    const int   cursorid
)
{
    return pxDebitLimitGetNext((tDEBTLIMIT*)record, cursorid);
}

int
pxDebitLimitList :: StartBrowse
(
    const void* keys,
    const int   cursorid
)
{
    return pxDebitLimitStartBrowse((tDEBTLIMIT*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxDebitLimit list objects being inserted in the                   */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxDebitLimit :: CompareTo
(
    const nCollectable* That,
    void*      /* p */,
    const long /* lparm */
)   const
{
    pxDebitLimit* that = (pxDebitLimit*)That;
    int retval = (PartnerNo_ == that->PartnerNo_) ? 0
                : (PartnerNo_ > that->PartnerNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxDebitLimitList :: pxDebitLimitList
(
    pxSession* session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxDebitLimitList :: Select
(
    const int count_
)
{
    tDEBTLIMIT fil;
    memset(&fil, 0, sizeof(tDEBTLIMIT));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxDebitLimitList :: AddToList
(
    const void* record,
    const int   /* row */
)
{
    // construct new 'pxDebitLimit' object:
    pxDebitLimit* objectp = new pxDebitLimit(Session(), *(tDEBTLIMIT*)record);
    InsertAscending(objectp);
    return objectp;
}
