/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxPromotionQuota methods.

REVISION HISTORY

16 Dec 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxpromotionquota.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxPromotionQuota :: pxPromotionQuota
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
pxPromotionQuota :: pxPromotionQuota
(
    pxPromotionQuota& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tPROMOTIONQUOTA structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxPromotionQuota :: pxPromotionQuota
(
    pxSession   *session,
    tPROMOTIONQUOTA& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxPromotionQuota :: pxPromotionQuota
(
    pxSession *session,
   const pxPromotionQuota *src
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
pxPromotionQuota :: pxPromotionQuota
(
    pxSession    *session,
    short        BranchNo,            // Branchnumber
    short        PromotionNo          // Promotion Number

)
    : pxDBRecord(session)
{
    Init();
    BranchNo_     = BranchNo;
    PromotionNo_  = PromotionNo;
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxPromotionQuota :: ~pxPromotionQuota()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tPROMOTIONQUOTA structure.      */
/*----------------------------------------------------------------------------*/
tPROMOTIONQUOTA&
Assign
(
    tPROMOTIONQUOTA&           dest,
    const pxPromotionQuota&       src
)
{
    dest.BranchNo                 = src.BranchNo_              ;
    dest.Promotion_No              = src.PromotionNo_           ;
    dest.BranchQuotaQty           = src.BranchQuotaQty_        ;
    dest.CustomerQuotaQty         = src.CustomerQuotaQty_      ;
    dest.SoldQtyBranch            = src.SoldQtyBranch_         ;
    dest.Upd_Flag                 = src.Upd_Flag_              ;
    dest.ArticleNo                = src.ArticleNo_              ;
    dest.CustomerMinQty           = src.CustomerMinQty_         ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tPROMOTIONQUOTA structure to                */
/*  a pxPromotionQuota object.                                                 */
/*----------------------------------------------------------------------------*/
pxPromotionQuota&
Assign
(
    pxPromotionQuota&              dest,
    const tPROMOTIONQUOTA&    src
)
{
    dest.BranchNo_                 = src.BranchNo              ;
    dest.PromotionNo_              = src.Promotion_No           ;
    dest.BranchQuotaQty_           = src.BranchQuotaQty        ;
    dest.CustomerQuotaQty_         = src.CustomerQuotaQty      ;
    dest.SoldQtyBranch_            = src.SoldQtyBranch         ;
    dest.Upd_Flag_                 = src.Upd_Flag              ;
    dest.ArticleNo_                = src.ArticleNo             ;
    dest.CustomerMinQty_           = src.CustomerMinQty         ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxPromotionQuota :: Init()
{
    tPROMOTIONQUOTA    record;
    memset(&record, 0 , sizeof(tPROMOTIONQUOTA));
    Upd_Flag_ = '0';
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tPROMOTIONQUOTA struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxPromotionQuota&
pxPromotionQuota :: operator=( const pxPromotionQuota& src)
{
    tPROMOTIONQUOTA record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tPROMOTIONQUOTA structure 'src' to                   */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxPromotionQuota&
pxPromotionQuota :: operator=( const tPROMOTIONQUOTA& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxPromotionQuota list objects being inserted in the                   */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo,MainCstNo,Date                                       */
/*----------------------------------------------------------------------------*/
int
pxPromotionQuota :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxPromotionQuota *that = (pxPromotionQuota*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > BranchNo_ ? 1 : -1);
    if ( retval == 0 )
       retval = (PromotionNo_ == that->PromotionNo_) ? 0
              : (PromotionNo_ > PromotionNo_ ? 1 : -1);
    if ( retval == 0 )
       retval = (ArticleNo_ == that->ArticleNo_) ? 0
              : (ArticleNo_ > ArticleNo_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Add quantity q  Returns quantity added.                                   */
/*----------------------------------------------------------------------------*/
long
pxPromotionQuota :: AddSoldQtyBranch
(
    const long q
)
{
    SoldQtyBranch_ += q;
    SetDirty();
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Subtract quantity q from quantity ordered. Returns quantity subtracted.   */
/*----------------------------------------------------------------------------*/
long
pxPromotionQuota :: SubSoldQtyBranch
(
    const long q                      // quantity to be subtracted
)
{
    long retval;
    // avoid negative values in stock:
    retval = ( SoldQtyBranch_ - q < 0 ) ? SoldQtyBranch_ : q;
    SoldQtyBranch_ -= retval;
    SetDirty();
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  CheckPromoQuotaUsage: check how to use promotion quota                    */
/*----------------------------------------------------------------------------*/
short
pxPromotionQuota :: CheckPromoQuotaUsage
(
)
{
    short promoUsage = 0;

    if ( BranchQuotaQty_ > 0 && CustomerQuotaQty_ == 0 )
    {
       promoUsage = pxPromotionQuota::UseBranchEntry;
    }
    else
    if ( BranchQuotaQty_ == 0 && CustomerQuotaQty_ > 0 )
    {
       promoUsage = pxPromotionQuota::UseCustomerEntry;
    }
    else
    if ( BranchQuotaQty_ > 0 && CustomerQuotaQty_ > 0 )
    {
       promoUsage = pxPromotionQuota::UseBothEntries;
    }
    return promoUsage;
}
/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxPromotionQuotaList :: pxPromotionQuotaList
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
pxPromotionQuotaList :: Select
(
    const int     count_
)
{
    tPROMOTIONQUOTA fil;
    memset(&fil, 0, sizeof(tPROMOTIONQUOTA));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo                                */
/*----------------------------------------------------------------------------*/
size_t
pxPromotionQuotaList :: Select
(
    const short   BranchNo,
    const short   PromotionNo,
    const long    ArticleNo,
    const int     count_
)
{
    tPROMOTIONQUOTA fil;
    memset(&fil, 0, sizeof(tPROMOTIONQUOTA));  // zero out entire record buffer
    fil.BranchNo    = BranchNo;
    fil.Promotion_No = PromotionNo;
    fil.ArticleNo = ArticleNo;
    int cursorid = cCRSPROMOTION_BR_PRO_ART;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxPromotionQuotaList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxPromotionQuota' object:
    pxPromotionQuota *objectp = new pxPromotionQuota(Session(), *(tPROMOTIONQUOTA*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Find return entryp depend on articleno                                    */
/*----------------------------------------------------------------------------*/
pxPromotionQuota*
pxPromotionQuotaList :: Find
(
    const long ArticleNo
)
{
    pxPromotionQuota *curp = NULL;             // ptr to current entry
    pxPromotionQuotaListIter  cursor(*this);  // define an iterator
    while ( (curp = (pxPromotionQuota*) ++cursor) != NULL )
    {
       if (curp->ArticleNo() == ArticleNo )
       {
          break;
       }
    }
    return curp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxPromotionQuota :: Get
(
    DBAccessMode mode
)

{
    tPROMOTIONQUOTA record;
    memset(&record, 0, sizeof(tPROMOTIONQUOTA));
    record.BranchNo       = BranchNo_;
    record.Promotion_No    = PromotionNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tARTICLEQUOTA struct
   /* else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_AQUOT_ENTRY_NOTFOUND, BranchNo_, CustomerNo_, ArticleNo_);
   */
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxPromotionQuota :: Put
(
)
{
    tPROMOTIONQUOTA record;
    memset(&record, 0, sizeof(tPROMOTIONQUOTA));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tPROMOTIONQUOTA));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxPromotionQuota :: Delete
(
)
{
    tPROMOTIONQUOTA record;
    memset(&record, 0, sizeof(tPROMOTIONQUOTA));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxPromotionQuota :: Read
(
    const void  *record
)
{
    return pxPromotionQuotaRead((tPROMOTIONQUOTA*)record);
}

int
pxPromotionQuota :: ReadLock
(
    const void  *record
)
{
    return pxPromotionQuotaReadLock((tPROMOTIONQUOTA*)record);
}

int
pxPromotionQuota :: Update
(
    const void  *record
)
{
    return pxPromotionQuotaUpdate((tPROMOTIONQUOTA*)record);
}

int
pxPromotionQuota :: Delete
(
    const void  *record
)
{
    return pxPromotionQuotaDelete((tPROMOTIONQUOTA*)record);
}

int
pxPromotionQuota :: Insert
(
    const void  *record
)
{
    return pxPromotionQuotaInsert((tPROMOTIONQUOTA*)record);
}

int
pxPromotionQuotaList :: EndBrowse
(
    const int  cursorid
)
{
    return pxPromotionQuotaEndBrowse(cursorid);
}


int
pxPromotionQuotaList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxPromotionQuotaGetNext((tPROMOTIONQUOTA*)record, cursorid);
}

int
pxPromotionQuotaList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxPromotionQuotaStartBrowse((tPROMOTIONQUOTA*)keys, cursorid);
}
