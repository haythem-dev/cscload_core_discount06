/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxItemDiscount  methods.

REVISION HISTORY

19 Dec 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitemdiscount.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include <logger/loggerpool.h>
#include "pxbase/pxconstants.hpp"

extern bool pxGlobalNoDatabaseWrite;

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxItemDiscount::pxItemDiscount
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
pxItemDiscount::pxItemDiscount
(
    pxItemDiscount& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGPOSRAB structure to construct this instance.                */
/*----------------------------------------------------------------------------*/
pxItemDiscount::pxItemDiscount
(
    pxSession   *session,
    tKDAUFTRAGPOSRAB& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxItemDiscount::pxItemDiscount
(
    pxSession    *session,
    const long   KdAuftragNr,         // customer ordernumber
    const long   PosNr,               // Positionnumber
    const short  DisCountType,        // Discounttype
    const nString& PharmacyGroupId,    // PharmacyGroupId
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    // avoid "unused" compiler warning
    { mode = mode; }

    Init();
    KdAuftragNr_      = KdAuftragNr;
    PosNr_            = PosNr;
    DiscountType_     = DisCountType;
    PharmacyGroupId_  = PharmacyGroupId;
    //Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxItemDiscount::pxItemDiscount
(
    pxSession    *session,
    const long   KdAuftragNr,         // customer ordernumber
    const long   PosNr,               // Positionnumber
    const short  DisCountType,        // Discounttype
    const nString& PharmacyGroupId,    // PharmacyGroupId
    const short  PaymentTargetNo,     // PaymentTargetNo
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    // avoid "unused" compiler warning
    { mode = mode; }

    Init();
    KdAuftragNr_      = KdAuftragNr;
    PosNr_            = PosNr;
    DiscountType_     = DisCountType;
    PharmacyGroupId_  = PharmacyGroupId;
    PaymentTargetNo_  = PaymentTargetNo;
    //Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxItemDiscount::~pxItemDiscount()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGPOSRAB structure.    */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGPOSRAB& Assign
(
    tKDAUFTRAGPOSRAB&         dest,
    const pxItemDiscount&     src
)
{
    dest.KdAuftragNr            = src.KdAuftragNr_     ;
    dest.PosNr                  = src.PosNr_           ;
    dest.DiscountType           = src.DiscountType_    ;
    dest.DiscountValuePct       = src.DiscountValuePct_;
    dest.PharmacyGroupId[0] = ' ';
    src.PharmacyGroupId_.GetData(dest.PharmacyGroupId);
    dest.PaymentTargetNo        = src.PaymentTargetNo_ ;
    dest.DiscountValPctMan      = src.DiscountValPctMan_;
    dest.SurchargePct           = src.SurchargePct_;
    dest.DiscountCategory       = static_cast<short>(src.DiscountCategory_);
    dest.InternalDiscountFlag   = src.InternalDiscountFlag_;
    dest.RefundValuePct         = src.RefundValuePct_;
    dest.FixedPrice             = src.FixedPrice_;
    dest.DiscountCalcFrom       = src.DiscountCalcFrom_;
    dest.DiscountApplyTo        = src.DiscountApplyTo_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGPOSRAB structure to              */
/*  a pxItemDiscount object.                                                  */
/*----------------------------------------------------------------------------*/
pxItemDiscount& Assign
(
    pxItemDiscount&              dest,
    const tKDAUFTRAGPOSRAB&      src
)
{
    dest.KdAuftragNr_           = src.KdAuftragNr     ;
    dest.PosNr_                 = src.PosNr           ;
    dest.DiscountType_          = src.DiscountType    ;
    dest.DiscountValuePct_      = src.DiscountValuePct;
    dest.PharmacyGroupId_       = src.PharmacyGroupId ;
    dest.PaymentTargetNo_       = src.PaymentTargetNo ;
    dest.DiscountValPctMan_     = src.DiscountValPctMan;
    dest.SurchargePct_          = src.SurchargePct;
    dest.DiscountCategory_      = static_cast<tDiscountCategory>(src.DiscountCategory);
    dest.InternalDiscountFlag_  = src.InternalDiscountFlag;
    dest.RefundValuePct_        = src.RefundValuePct;
    dest.FixedPrice_            = src.FixedPrice;
    dest.DiscountCalcFrom_      = src.DiscountCalcFrom;
    dest.DiscountApplyTo_       = src.DiscountApplyTo;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void pxItemDiscount::Init()
{
    tKDAUFTRAGPOSRAB    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGPOSRAB));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGPOSRAB struct and then imported to self.                        */
/*----------------------------------------------------------------------------*/
pxItemDiscount& pxItemDiscount::operator=( const pxItemDiscount& src)
{
    tKDAUFTRAGPOSRAB record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGPOSRAB structure 'src' to              */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxItemDiscount& pxItemDiscount::operator=( const tKDAUFTRAGPOSRAB& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int pxItemDiscount::Get( DBAccessMode mode )
{
    tKDAUFTRAGPOSRAB record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSRAB));
    record.KdAuftragNr    = KdAuftragNr_ ;
    record.PosNr          = PosNr_       ;
    record.DiscountType   = DiscountType_;
    record.PaymentTargetNo= PaymentTargetNo_;

    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKDAUFTRAGPOSRAB struct
   /* else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(), CMSG_AQUOT_ENTRY_NOTFOUND, BranchNo_, CustomerNo_, ArticleNo_);
   */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int pxItemDiscount::Put( )
{
    if ( pxGlobalNoDatabaseWrite == false )
    {
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxItemDiscount :: Put()");
    }
    if (DiscountValuePct_ > 100.0f)
    {
        DiscountValuePct_ = 100.0f;
    }
    tKDAUFTRAGPOSRAB record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSRAB));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGPOSRAB));
}

/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int pxItemDiscount::Delete( )
{
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerDiscountCalc(), "pxItemDiscount :: Delete()");
    tKDAUFTRAGPOSRAB record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSRAB));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int pxItemDiscount::Read( const void  *record )
{
    return pxItemDiscountRead((tKDAUFTRAGPOSRAB*)record);
}

int pxItemDiscount::ReadLock( const void  *record )
{
    return pxItemDiscountReadLock((tKDAUFTRAGPOSRAB*)record);
}

int pxItemDiscount::Update( const void  *record )
{
    return pxItemDiscountUpdate((tKDAUFTRAGPOSRAB*)record);
}

int pxItemDiscount::Delete( const void  *record )
{
    return pxItemDiscountDelete((tKDAUFTRAGPOSRAB*)record);
}

int pxItemDiscount::Insert( const void  *record )
{
    return pxItemDiscountInsert((tKDAUFTRAGPOSRAB*)record);
}

int pxItemDiscountList::EndBrowse( const int  cursorid )
{
    return pxItemDiscountEndBrowse(cursorid);
}

int pxItemDiscountList::GetNext( const void  *record, const int  cursorid )
{
    return pxItemDiscountGetNext((tKDAUFTRAGPOSRAB*)record, cursorid);
}

int pxItemDiscountList::StartBrowse( const void  *keys, const int  cursorid )
{
    return pxItemDiscountStartBrowse((tKDAUFTRAGPOSRAB*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxItemDiscount list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxItemDiscount :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxItemDiscount *that = (pxItemDiscount*)That;

    int retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
               : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);

    if (retval == 0 )
        retval = (PosNr_ == that->PosNr_) ? 0
               : (PosNr_ > that->PosNr_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxItemDiscountList :: pxItemDiscountList
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
pxItemDiscountList :: Select
(
    const long   KdAuftragNr,
    const long   PosNr,
    const int    count_
)
{
    tKDAUFTRAGPOSRAB fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGPOSRAB));  // zero out entire record buffer
    fil.KdAuftragNr  = KdAuftragNr;
    fil.PosNr        = PosNr;
    int cursorid     = cCRS_DEFAULT;
    if ( PosNr == 0)
        cursorid    = cCRSPOSRAB_KDAUFTRAGNR;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxItemDiscountList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxItemDiscount' object:
    pxItemDiscount *objectp = new pxItemDiscount(Session(), *(tKDAUFTRAGPOSRAB*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Find  Discounttype                                                        */
/*----------------------------------------------------------------------------*/
pxItemDiscount*
pxItemDiscountList :: Find
(
    const int  discounttype
)
{
    pxItemDiscountListIter cursor(*this);
    pxItemDiscount   *entryp = NULL;
    while ( (entryp = (pxItemDiscount*) ++cursor) != NULL )
    {
        if ( entryp->DiscountType_ == discounttype )
            break;
    }
    return entryp;
}

/*----------------------------------------------------------------------------*/
/*  Find  DiscountValuePct                                                    */
/*----------------------------------------------------------------------------*/
pxItemDiscount*
pxItemDiscountList :: FindDiscountValuePct
(
)
{
    pxItemDiscountListIter cursor(*this);
    pxItemDiscount   *entryp = NULL;
    while ( (entryp = (pxItemDiscount*) ++cursor) != NULL )
    {
        if ( entryp->DiscountValuePct_ != pxConstants::dZero )
            break;
    }
    return entryp;
}

/*----------------------------------------------------------------------------*/
/*  Find  DiscountValuePctPosNr                                               */
/*----------------------------------------------------------------------------*/
pxItemDiscount*
pxItemDiscountList :: FindDiscountValuePctPosNr
(
    const long PosNr
)
{
    pxItemDiscountListIter cursor(*this);
    pxItemDiscount   *entryp = NULL;
    while ( (entryp = (pxItemDiscount*) ++cursor) != NULL )
    {
        if ( entryp->PosNr() == PosNr )
        {
            if ( entryp->DiscountValuePct_ != pxConstants::dZero )
            {
                break;
            }
        }
    }
    return entryp;
}

/*----------------------------------------------------------------------------*/
/*  GetEntry  Returns entry pointer to the corresponding posnr or a NULLP     */
/*  returns                                                                   */
/*----------------------------------------------------------------------------*/
pxItemDiscount*
pxItemDiscountList :: GetEntry
(
    const int  PosNr
)
{
    pxItemDiscountListIter cursor(*this);
    pxItemDiscount   *entryp = NULL;
    while ( (entryp = (pxItemDiscount*) ++cursor) != NULL )
    {
        if ( entryp->PosNr_ == PosNr )
            break;
    }
    return entryp;
}
/*----------------------------------------------------------------------------*/
/*  Find  FixedPrice                                                          */
/*----------------------------------------------------------------------------*/
pxItemDiscount*
pxItemDiscountList::FindFixedPrice
(
)
{
    pxItemDiscountListIter cursor(*this);
    pxItemDiscount   *entryp = NULL;
    while ((entryp = (pxItemDiscount*) ++cursor) != NULL)
    {
        if (entryp->FixedPrice_ != pxConstants::dZero)
            break;
    }
    return entryp;
}

