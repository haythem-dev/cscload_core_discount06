#include "pxarticlequota.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "pxcustpharmgroup.hpp"
#include <logger/loggerpool.h>

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArticleQuota :: pxArticleQuota
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
pxArticleQuota :: pxArticleQuota
(
    pxArticleQuota& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTICLEQUOTA structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxArticleQuota :: pxArticleQuota
(
    pxSession   *session,
    tARTICLEQUOTA& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArticleQuota :: pxArticleQuota
(
    pxSession    *session,
    short        BranchNo,            // Branchnumber
    long         CustomerNo,          // Customernumber
    long         ArticleNo            // Articlenumber

)
    : pxDBRecord(session)
{
    Init();
    BranchNo_    = BranchNo;
    CustomerNo_  = CustomerNo;
    ArticleNo_   = ArticleNo;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArticleQuota :: ~pxArticleQuota()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTICLEQUOTA structure.       */
/*----------------------------------------------------------------------------*/
tARTICLEQUOTA&
Assign
(
    tARTICLEQUOTA&           dest,
    const pxArticleQuota&     src
)
{
    dest.BranchNo     = src.BranchNo_;
    dest.CustomerNo   = src.CustomerNo_;
    dest.ArticleNo    = src.ArticleNo_;
    dest.Quota        = src.Quota_;
    dest.KumQty       = src.KumQty_;
    dest.Validity     = src.Validity_;
    dest.SDafueQuota  = src.SDafueQuota_;
    dest.DateFrom     = src.DateFrom_.GetYYYYMMDD() ;
    dest.DateTo       = src.DateTo_.GetYYYYMMDD()   ;
    dest.PharmacyGroupId[0] = ' ';
    src.PharmacyGroupId_.GetData(dest.PharmacyGroupId);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTICLEQUOTA structure to                 */
/*  a pxArticleQuota object.                                                  */
/*----------------------------------------------------------------------------*/
pxArticleQuota&
Assign
(
    pxArticleQuota&              dest,
    const tARTICLEQUOTA&         src
)
{
    dest.BranchNo_         = src.BranchNo;
    dest.CustomerNo_       = src.CustomerNo;
    dest.ArticleNo_        = src.ArticleNo;
    dest.Quota_            = src.Quota;
    dest.KumQty_           = src.KumQty;
    dest.Validity_         = src.Validity;
    dest.SDafueQuota_      = src.SDafueQuota;
    dest.DateFrom_         = nDate(src.DateFrom);
    dest.DateTo_           = nDate(src.DateTo);
    dest.PharmacyGroupId_  = src.PharmacyGroupId;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArticleQuota :: Init()
{
    tARTICLEQUOTA    record;
    memset(&record, 0 , sizeof(tARTICLEQUOTA));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTICLEQUOTA struct and then imported to self.                           */
/*----------------------------------------------------------------------------*/
pxArticleQuota&
pxArticleQuota :: operator=( const pxArticleQuota& src)
{
    tARTICLEQUOTA record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTICLEQUOTA structure 'src' to                 */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxArticleQuota&
pxArticleQuota :: operator=( const tARTICLEQUOTA& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Add quantity q from quantity ordered. Returns quantity added.             */
/*----------------------------------------------------------------------------*/
long
pxArticleQuota :: AddQuantity
(
    const long q
)
{
    KumQty_ += q;
    SetDirty();
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Subtract quantity q from quantity ordered. Returns quantity subtracted.   */
/*----------------------------------------------------------------------------*/
long
pxArticleQuota :: SubQuantity
(
    const long q                      // quantity to be subtracted
)
{
    long retval;
    // avoid negative values in stock:
    retval = ( KumQty_ - q < 0 ) ? KumQty_ : q;
    KumQty_ -= retval;
    SetDirty();
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  FindQuotaEntry: This methode looks for an articlequota entry depend on    */
/*  the the given values in a well constructed pxArticleQuota object.         */
//  This method is used only for interbranch transfer (Verbund)
/*  Return value = 1 if no valid entry is found, = 0 if found one             */
/*----------------------------------------------------------------------------*/
int
pxArticleQuota :: FindQuotaEntry
(
    DBAccessMode mode
)
{
    int retval = 1;                         // return value preset with 1
    pxCustPharmGroupList *phglist = NULL;    // customers pharmaygrouplist
    pxArticleQuota       *entriep = NULL;    // artquota listentry
    pxArticleQuotaList   *ArtQuotaList = NULL;

    phglist = new pxCustPharmGroupList( Session() );
    phglist->Select( CustomerNo_, BranchNo_ );

    if (phglist->Entries()  == 0)            // no  entries found
    {
       delete     phglist;
       phglist  = NULL;
    }

    ArtQuotaList = new pxArticleQuotaList(Session());
    // first look for entry with pharmacygroupid
    ArtQuotaList->Select(BranchNo_, 0L, ArticleNo_);
    if ( ArtQuotaList->Entries() && phglist)
    {
       pxArticleQuotaListIter cursor(*ArtQuotaList);
       while ( (entriep = ( pxArticleQuota*) ++ cursor) != NULL )
       {
          if ( phglist->Find(entriep->PharmacyGroupId()) )
          {
             CustomerNo_      = entriep->CustomerNo();
             PharmacyGroupId_ = entriep->PharmacyGroupId();
             retval = Get(mode);
             break;
          }
       }
    }
    if (retval == 0 )
    {
       delete ArtQuotaList;
       delete phglist;
       return retval;
    }

    if ( phglist )
       delete phglist;

    // normal entry per customer
    ArtQuotaList->Select(BranchNo_, CustomerNo_, ArticleNo_);
    if ( !ArtQuotaList->Entries() )
    {
       delete ArtQuotaList;
       return retval;
    }
    // we have at least one entry
    pxArticleQuotaListIter cursor(*ArtQuotaList);
    while ( (entriep = ( pxArticleQuota*) ++ cursor) != NULL )
    {
       retval = Get(mode);
       break;
    }
    delete ArtQuotaList;

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArticleQuota :: Get
(
    DBAccessMode mode
)

{
    std::stringstream s;
    s << "pxArticleQuota::Get(" << mode << ") ArticleNo=" << ArticleNo_ << ", BranchNo=" << BranchNo_;
    s << ", CustomerNo=" << CustomerNo_;
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), s.str());

    tARTICLEQUOTA record;
    memset(&record, 0, sizeof(tARTICLEQUOTA));
    record.BranchNo    = BranchNo_;
    record.CustomerNo  = CustomerNo_;
    record.ArticleNo   = ArticleNo_;
    if ( CustomerNo_  > 0 )
    {
       PharmacyGroupId_ = "   ";
    }
    record.PharmacyGroupId[0] = ' ';
    PharmacyGroupId_.GetData(record.PharmacyGroupId);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tARTICLEQUOTA struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArticleQuota :: Put
(
)
{
    std::stringstream s;
    s << "pxArticleQuota::Put()";
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), s.str());

    tARTICLEQUOTA record;
    memset(&record, 0, sizeof(tARTICLEQUOTA));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTICLEQUOTA));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxArticleQuota :: Delete
(
)
{
    tARTICLEQUOTA record;
    memset(&record, 0, sizeof(tARTICLEQUOTA));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArticleQuota :: Read
(
    const void  *record
)
{
    return pxArticleQuotaRead((tARTICLEQUOTA*)record);
}

int
pxArticleQuota :: ReadLock
(
    const void  *record
)
{
    return pxArticleQuotaReadLock((tARTICLEQUOTA*)record);
}

int
pxArticleQuota :: Update
(
    const void  *record
)
{
    return pxArticleQuotaUpdate((tARTICLEQUOTA*)record);
}

int
pxArticleQuota :: Delete
(
    const void  *record
)
{
    return pxArticleQuotaDelete((tARTICLEQUOTA*)record);
}

int
pxArticleQuota :: Insert
(
    const void  *record
)
{
    return pxArticleQuotaInsert((tARTICLEQUOTA*)record);
}

int
pxArticleQuotaList :: EndBrowse
(
    const int  cursorid
)
{
    return pxArticleQuotaEndBrowse(cursorid);
}


int
pxArticleQuotaList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxArticleQuotaGetNext((tARTICLEQUOTA*)record, cursorid);
}

int
pxArticleQuotaList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxArticleQuotaStartBrowse((tARTICLEQUOTA*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArticleQuota list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxArticleQuota :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const

{
    pxArticleQuota *that = (pxArticleQuota*)That;
    int retval = (CustomerNo_ == that->CustomerNo_) ? 0
                : (CustomerNo_ > that->CustomerNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArticleQuotaList :: pxArticleQuotaList
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
pxArticleQuotaList :: Select
(
    const int     count_
)
{
    tARTICLEQUOTA fil;
    memset(&fil, 0, sizeof(tARTICLEQUOTA));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxArticleQuotaList :: Select
(
    const short   BranchNo,
    const long    CustomerNo,
    const long    ArticleNo,
    const int     count_
)
{
    tARTICLEQUOTA fil;
    memset(&fil, 0, sizeof(tARTICLEQUOTA));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    fil.ArticleNo  = ArticleNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxArticleQuotaList :: SelectOriginal
(
    const short   BranchNo,
    const long    CustomerNo,
    const long    ArticleNo,
    const int     count_
)
{
    tARTICLEQUOTA fil;
    memset(&fil, 0, sizeof(tARTICLEQUOTA));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.CustomerNo = CustomerNo;
    fil.ArticleNo  = ArticleNo;
    int cursorid = cCRSARTICLEQUOTA_ORIGINAL;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection of all records.                               */
/*----------------------------------------------------------------------------*/
size_t
pxArticleQuotaList :: SelectBasic
(
    const short   BranchNo,
    const long    ArticleNo,
    const int     count_
)
{
    tARTICLEQUOTA fil;
    memset(&fil, 0, sizeof(tARTICLEQUOTA));  // zero out entire record buffer
    fil.BranchNo   = BranchNo;
    fil.ArticleNo  = ArticleNo;
    int cursorid = cCRSARTICLEQUOTA_BASIC;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArticleQuotaList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxArticleQuota' object:
    pxArticleQuota *objectp = new pxArticleQuota(Session(), *(tARTICLEQUOTA*) record);
    InsertAscending(objectp);
    return objectp;
}

