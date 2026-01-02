#include "pxcstot.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"
#include <boost/numeric/conversion/cast.hpp>

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustOrderType :: pxCustOrderType
(
    const pxCustOrderType& src
)
    : pxOrderType(((pxOrderType&) src).Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Construct an instance using the session                                   */
/*----------------------------------------------------------------------------*/
pxCustOrderType::pxCustOrderType(pxSession* session)
: pxOrderType(session)
{
}

/*----------------------------------------------------------------------------*/
/*  Construct an instance using the key values as arguments.                  */
/*----------------------------------------------------------------------------*/
pxCustOrderType :: pxCustOrderType
(
    pxSession     *session,
    const nString& KdAuftragArt,
    const short   VZNr,
    const long    KdNr
)
    : pxOrderType(session, session->OrderTypeList(VZNr)->Find(KdAuftragArt,VZNr))
{
    if ( KdAuftragArt_.IsEmpty() )
        ExternalError(session->CMsgStream(), CMSG_CST_OT_UNKNOWN, (char*)KdAuftragArt);
    else
    {
        VertriebszentrumNr_ = VZNr;
        KundenNr_ = KdNr;
        if ( IsGlobal() )
        {
            ValutaMonAuto_   = 0;
            SKdAuftragartDD_ = '0';
            OrderLabelCount_ = 0;
            SWMSV3_ = 0;
            SWPartDel_ = 1;
        }
    }
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxCustOrderType :: pxCustOrderType
(
    pxSession *session,
    const nString& KdAuftragart,
    const short   VZNr,           // Read via VZNr / KundeNr / Auftragart
    const long    KdNr,
    DBAccessMode mode
)
    : pxOrderType(session, session->OrderTypeList(VZNr)->Find(KdAuftragart,VZNr))
{
    if ( KdAuftragArt_.IsEmpty() )
        ExternalError(session->CMsgStream(), CMSG_CST_OT_UNKNOWN, (char*)KdAuftragart);
    else
    {
        VertriebszentrumNr_ = VZNr;
        KundenNr_ = KdNr;
        Get(mode);
    }
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxCustOrderType :: ~pxCustOrderType()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a 'dest' record structure.       */
/*----------------------------------------------------------------------------*/
tAUFTRAGARTKD&
Assign
(
    tAUFTRAGARTKD&     dest,
    const pxCustOrderType& src
)
{
    dest.VertriebszentrumNr = src.VertriebszentrumNr_;
    dest.KundenNr = src.KundenNr_;
    dest.KdAuftragArt[0] = ' ';
    src.KdAuftragArt_.GetData(dest.KdAuftragArt);
    dest.ValutaMonate          = src.ValutaMonate_;
    dest.SKdAuftragartNatra    = src.SKdAuftragartNatra_;
    dest.SKdAuftragartNetto    = src.SKdAuftragartNetto_;
    dest.SKdAuftragartBANR     = src.SKdAuftragartBANR_ ;
    dest.SKdAuftragartMonat    = src.SKdAuftragartMonat_;
    dest.SkdAuftragVerbund     = src.SKdAuftragartVerbund_;
    dest.SKdAuftragartValS     = src.SKdAuftragartValS_ ;
    dest.SKdAuftragartDD       = src.SKdAuftragartDD_;
    dest.ValutaMonAuto         = src.ValutaMonAuto_;
    dest.OrderLabelCount       = src.OrderLabelCount_;
    dest.SWMSV3                = src.SWMSV3_;
    dest.SWPartDel             = src.SWPartDel_;
    dest.OrderIdentificatio[0] = ' ';
    src.OrderIdentificatio_.GetData(dest.OrderIdentificatio);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the record structure to the object instance.         */
/*----------------------------------------------------------------------------*/
pxCustOrderType&
Assign
(
    pxCustOrderType&    dest,
    const tAUFTRAGARTKD&  src
)
{
    dest.VertriebszentrumNr_   = src.VertriebszentrumNr;       // Vertriebszentrum
    dest.KundenNr_             = src.KundenNr;       // Kundennummer
    dest.KdAuftragArt_         = src.KdAuftragArt;
    dest.ValutaMonate_         = boost::numeric_cast<int>(src.ValutaMonate);
    dest.SKdAuftragartNatra_   = src.SKdAuftragartNatra;
    dest.SKdAuftragartNetto_   = src.SKdAuftragartNetto;
    dest.SKdAuftragartBANR_    = src.SKdAuftragartBANR ;
    dest.SKdAuftragartMonat_   = src.SKdAuftragartMonat;
    dest.SKdAuftragartVerbund_ = src.SkdAuftragVerbund;
    dest.SKdAuftragartValS_    = src.SKdAuftragartValS ;
    dest.SKdAuftragartDD_      = src.SKdAuftragartDD;
    dest.ValutaMonAuto_        = src.ValutaMonAuto;
    dest.OrderLabelCount_      = src.OrderLabelCount;
    dest.SWMSV3_               = src.SWMSV3;
    dest.SWPartDel_            = src.SWPartDel;
    dest.OrderIdentificatio_   = src.OrderIdentificatio;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxCustOrderType :: Init()
{
    VertriebszentrumNr_ = 0;
    KundenNr_ = 0;
    OrderLabelCount_ = 0;
    SWMSV3_ = 0;
    SWPartDel_ = 1;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxCustOrderType&
pxCustOrderType :: operator=( const pxCustOrderType& src)
{
    pxOrderType::operator=(src);
    VertriebszentrumNr_ = src.VertriebszentrumNr_;
    KundenNr_ = src.KundenNr_;
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tAUFTRAGARTKD structure to this instance.        */
/*----------------------------------------------------------------------------*/
pxCustOrderType&
pxCustOrderType :: operator=( const tAUFTRAGARTKD& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxCustOrderType :: Get
(
    DBAccessMode mode
)
{
    tAUFTRAGARTKD record;
    memset(&record, 0, sizeof(tAUFTRAGARTKD));
    Assign(record, *this);
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;          // import the data from tAUFTRAGARTKD struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  get object from data source                                SH, 22.08.2013 */
/*----------------------------------------------------------------------------*/
int pxCustOrderType::getCustomerOrderType( const short VZNr, const long KdNr, const nString& Auftragart )
{
    KdAuftragArt_ = Auftragart;
    VertriebszentrumNr_ = VZNr;
    KundenNr_ = KdNr;
    return Get();
}

/*----------------------------------------------------------------------------*/
/*  check if orderlabel is default orderlabel of order type    SH, 23.08.2013 */
/*----------------------------------------------------------------------------*/
bool pxCustOrderType::isDefaultOrderLabel( const nString& orderlabel ) const
{
    if ( !KdAuftragArt_.IsEmpty() )
    {
        nString ordertype_orderlabel(OrderIdentificatio_);
        ordertype_orderlabel.Strip();
        nString orderlabel_passed(orderlabel);
        orderlabel_passed.Strip();
        if( 0 == ordertype_orderlabel.Compare(orderlabel_passed) )
        {
            return true;
        }
    }
    return false;
}

/*----------------------------------------------------------------------------*/
/*  check if ordertype may be used for MSV3                    SH, 23.08.2013 */
/*----------------------------------------------------------------------------*/
bool pxCustOrderType::isAllowedForMSV3() const
{
    return IsMSV3();
}

bool pxCustOrderType::isPartialDeliveryAllowed() const
{
    return IsMSV3() && IsPartDel();
}

/*----------------------------------------------------------------------------*/
/*  check if usage of custom orderlabels is allowed            SH, 23.08.2013 */
/*----------------------------------------------------------------------------*/
bool pxCustOrderType::isUsageOfCustomOrderLabelsAllowed() const
{
    return ( OrderLabelCount_ > 0 );
}

/*----------------------------------------------------------------------------*/
/*  get default orderlabel for ordertype                       SH, 23.08.2013 */
/*----------------------------------------------------------------------------*/
const nString& pxCustOrderType::getDefaultOrderLabel() const
{
    return OrderIdentificatio_;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxCustOrderType :: Put
(
)
{
    tAUFTRAGARTKD record;
    memset(&record, 0, sizeof(tAUFTRAGARTKD));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tAUFTRAGARTKD));
}

/*----------------------------------------------------------------------------*/
/*  Virtual CompareTo function redefined from nCollectable.                   */
/*----------------------------------------------------------------------------*/
int
pxCustOrderType :: CompareTo
(
    const nCollectable   *That,
          void           * /*p*/,
    const long           /*lparm*/
)   const
{
    pxCustOrderType *that = (pxCustOrderType*)That;
    int retval = (VertriebszentrumNr_ == that->VertriebszentrumNr_) ? 0
               : (VertriebszentrumNr_ > that->VertriebszentrumNr_ ? 1 : -1);
    if ( retval == 0 )
        retval = (KundenNr_ == that->KundenNr_) ? 0
               : (KundenNr_ > that->KundenNr_ ? 1 : -1);
    if ( retval == 0 )
        retval = (KdAuftragArt_ == that->KdAuftragArt_) ? 0
               : (KdAuftragArt_ > that->KdAuftragArt_ ? 1 : -1);
    return retval;
}

int pxCustOrderType::Insert(const void *record)
{
    return pxAuftragArtKdInsert((tAUFTRAGARTKD*)record);
}

int pxCustOrderType::Update(const void *record)
{
    return pxAuftragArtKdUpdate((tAUFTRAGARTKD*)record);
}

int pxCustOrderType::Read(const void *record)
{
    return pxAuftragArtKdRead((tAUFTRAGARTKD*)record);
}

int pxCustOrderType::ReadLock(const void *record)
{
    return pxAuftragArtKdReadLock((tAUFTRAGARTKD*)record);
}

/*----------------------------------------------------------------------------*/
/*  Construct the list.                                                       */
/*----------------------------------------------------------------------------*/
pxCustOrderTypeList :: pxCustOrderTypeList
(
    pxSession *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Build a list of order types available for a customer.                     */
/*  Automatically includes order types defined as global and not explicitly   */
/*  allocated to the named customer.                                          */
/*----------------------------------------------------------------------------*/
size_t pxCustOrderTypeList::Build( const short VZNr, const long KdNr )
{
    Session()->OrderTypeList(VZNr);
    Select(VZNr, KdNr);
    pxOrderTypeListIter it(*(Session()->OrderTypeList(VZNr)));
    pxOrderType         *otp;
    while ( (otp = (pxOrderType*) ++it) != NULL )
    {
        if ( otp->IsGlobal() && otp->BranchNo() == VZNr)
            NewItem(otp->KdAuftragArt(), VZNr, KdNr);
    }
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the default order type.                               */
/*  First tries to find the 'Normal' order type and return it as the default. */
/*  If order type 'Normal' is not allowed for the customer, we scan the list  */
/*  for another order type flagged as the default.                            */
/*  Returns NULL if no default order type could be found.                     */
/*----------------------------------------------------------------------------*/
pxCustOrderType*
pxCustOrderTypeList :: GetDefault() const
{
    pxCustOrderTypeListIter it(*((pxCustOrderTypeList*)this));
    pxCustOrderType         *otp;
    while ( (otp = (pxCustOrderType*) ++it) != NULL )
    {
        if ( otp->IsNormal() && otp->IsDefault() )
            return otp;
    }

    it.Reset();
    while ( ( (otp = (pxCustOrderType*) ++it) != NULL ) && !otp->IsDefault() )
    ;
    if ( !otp )                         // no default defined
        otp = (pxCustOrderType*)(*this).At(0); // take the first in list (if any)
    return otp;
}

/*----------------------------------------------------------------------------*/
/*  Return a pointer to the default order type.                               */
/*  First tries to find the 'Default' order type and return it as the default.*/
/*  If order type 'Normal' is not allowed for the customer, we scan the       */
/*  common ordertypelist for the default one to add it to the customerorder   */
/*  list. Return after that, the default ordertype.                           */
/*----------------------------------------------------------------------------*/
pxCustOrderType*
pxCustOrderTypeList :: AddDefault
(
    const short VZNr,
    const long  KdNr
)
{
    pxCustOrderTypeListIter cit(*((pxCustOrderTypeList*)this));
    pxOrderTypeListIter it((*Session()->OrderTypeList(VZNr)));
    pxCustOrderType     *cotp;
    pxOrderType         *otp;

    cit.Reset();
    while ( ( (cotp = (pxCustOrderType*) ++cit) != NULL ) && !cotp->IsDefault() )
    ;

    if ( !cotp )                       // no default found
    {
        while ( (otp = (pxOrderType*) ++it) != NULL )
        {
            if ( otp->IsNormal() && otp->IsDefault() )
            {
                NewItem(otp->KdAuftragArt(), VZNr, KdNr);
                break;
            }
        }
    }

    return GetDefault();
}

/*----------------------------------------------------------------------------*/
/*  Select all order types for a customer.                                    */
/*----------------------------------------------------------------------------*/
size_t
pxCustOrderTypeList :: Select
(
    const short VZNr,
    const long  KdNr,
    const int   count_                // Max number of records to read
)
{
    tAUFTRAGARTKD record;
    memset(&record, 0, sizeof(tAUFTRAGARTKD));  // zero out entire record buffer
    record.VertriebszentrumNr = VZNr;
    record.KundenNr = KdNr;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&record, cursorid, count_);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Find an object instance with matching keys. Returns a pointer to the      */
/*  first occurence of that instance or NULL if the key could not be found.   */
/*----------------------------------------------------------------------------*/
pxCustOrderType*
pxCustOrderTypeList :: Find
(
    const nString& KdAuftragArt,
    const short    VZNr,
    const long     KdNr
)
{
    pxCustOrderType *temp = NULL;
    pxCustOrderTypeListIter cursor(*this);
    while ( (temp = (pxCustOrderType*) ++cursor) != NULL )
    {
        if ( temp->KdAuftragArt_ == KdAuftragArt && temp->BranchNo_ == VZNr && temp->KdNr() == KdNr )
            break;
    }

    return temp;

//    pxCustOrderType *ot = NULL;
//    pxCustOrderType temp(Session(), KdAuftragArt, VZNr, KdNr);
//    if ( temp.IsGoodState() )
//       ot = (pxCustOrderType*) nDListCollect::Find(&temp);
//    return ot;
}

/*----------------------------------------------------------------------------*/
/*  Construct a new item and insert it into the list.                         */
/*  Returns pointer to new object instance or NULL if an instance with the    */
/*  same key is already in the list.                                          */
/*----------------------------------------------------------------------------*/
pxCustOrderType*
pxCustOrderTypeList :: NewItem
(
    const nString& KdAuftragArt,
    const short    VZNr,
    const long     KdNr
)
{
    if ( Find(KdAuftragArt, VZNr, KdNr) )
        return NULL;                     // avoid duplicates
    if ( NULL == Session()->OrderTypeList(VZNr)->Find(KdAuftragArt, VZNr) )
        return NULL;                    // avoid ordertypes which are not defined for customer but not globally in branch

    pxCustOrderType *objectp = new pxCustOrderType(Session(), KdAuftragArt, VZNr, KdNr);
    if ( objectp->IsGoodState() )       // ensure order type is valid
        InsertAscending(objectp);
    else
    {
        delete objectp;
        objectp = NULL;
    }
    return objectp;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxCustOrderTypeList :: AddToList
(
    const void  *record,
    const int  /*row*/
)
{
    tAUFTRAGARTKD* recordp = (tAUFTRAGARTKD*) record;
    pxCustOrderType *itemp = NewItem(recordp->KdAuftragArt, recordp->VertriebszentrumNr, recordp->KundenNr);
    if (itemp)                          // object constructed,
        Assign(*itemp, *recordp);        // copy values from the record buffer
    return itemp;
}

int pxCustOrderTypeList::StartBrowse(const void *keys, const int cursorid)
{
    return pxAuftragArtKdStartBrowse((tAUFTRAGARTKD*)keys, cursorid);
}

int pxCustOrderTypeList::GetNext(const void* record, const int cursorid)
{
    return pxAuftragArtKdGetNext((tAUFTRAGARTKD*)record, cursorid);
}

int pxCustOrderTypeList::EndBrowse(const int cursorid)
{
    return pxAuftragArtKdEndBrowse(cursorid);
}
