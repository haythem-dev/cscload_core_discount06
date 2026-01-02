/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxPromotionQuotaCstCst methods.

REVISION HISTORY

16 Dec 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxpromotionquotacst.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxPromotionQuotaCst :: pxPromotionQuotaCst
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
pxPromotionQuotaCst :: pxPromotionQuotaCst
(
    pxPromotionQuotaCst& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tPROMOTIONQUOTACST structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxPromotionQuotaCst :: pxPromotionQuotaCst
(
    pxSession   *session,
    tPROMOTIONQUOTACST& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxPromotionQuotaCst :: pxPromotionQuotaCst
(
    pxSession *session,
   const pxPromotionQuotaCst *src
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
pxPromotionQuotaCst :: pxPromotionQuotaCst
(
    pxSession    *session,
    short        BranchNo,            // Branchnumber
    short        PromotionNo,         // Promotion Number
    long         CustomerNo           // CustomerNo

)
    : pxDBRecord(session)
{
    Init();
    BranchNo_     = BranchNo;
    PromotionNo_  = PromotionNo;
    CustomerNo_   = CustomerNo;
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxPromotionQuotaCst :: ~pxPromotionQuotaCst()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tPROMOTIONQUOTACST structure.  */
/*----------------------------------------------------------------------------*/
tPROMOTIONQUOTACST&
Assign
(
    tPROMOTIONQUOTACST&           dest,
    const pxPromotionQuotaCst&       src
)
{
    dest.BranchNo                 = src.BranchNo_              ;
    dest.Promotion_No              = src.PromotionNo_           ;
    dest.CustomerQuotaQty         = src.CustomerQuotaQty_      ;
    dest.SoldQtyCst               = src.SoldQtyCst_            ;
    dest.CustomerNo               = src.CustomerNo_            ;
    dest.ArticleNo                = src.ArticleNo_              ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tPROMOTIONQUOTACST structure to            */
/*  a pxPromotionQuotaCst object.                                             */
/*----------------------------------------------------------------------------*/
pxPromotionQuotaCst&
Assign
(
    pxPromotionQuotaCst&              dest,
    const tPROMOTIONQUOTACST&    src
)
{
    dest.BranchNo_                 = src.BranchNo              ;
    dest.PromotionNo_              = src.Promotion_No          ;
    dest.CustomerQuotaQty_         = src.CustomerQuotaQty      ;
    dest.SoldQtyCst_               = src.SoldQtyCst            ;
    dest.CustomerNo_               = src.CustomerNo            ;
    dest.ArticleNo_                = src.ArticleNo             ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxPromotionQuotaCst :: Init()
{
    tPROMOTIONQUOTACST    record;
    memset(&record, 0 , sizeof(tPROMOTIONQUOTACST));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tPROMOTIONQUOTACST struct and then imported to self.                      */
/*----------------------------------------------------------------------------*/
pxPromotionQuotaCst&
pxPromotionQuotaCst :: operator=( const pxPromotionQuotaCst& src)
{
    tPROMOTIONQUOTACST record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tPROMOTIONQUOTACST structure 'src' to            */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxPromotionQuotaCst&
pxPromotionQuotaCst :: operator=( const tPROMOTIONQUOTACST& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxPromotionQuotaCst list objects being inserted in the            */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo,MainCstNo,Date                                       */
/*----------------------------------------------------------------------------*/
int
pxPromotionQuotaCst :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxPromotionQuotaCst *that = (pxPromotionQuotaCst*)That;
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
pxPromotionQuotaCst :: AddSoldQtyCst
(
    const long q
)
{
    SoldQtyCst_ += q;
    SetDirty();
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Subtract quantity q from quantity ordered. Returns quantity subtracted.   */
/*----------------------------------------------------------------------------*/
long
pxPromotionQuotaCst :: SubSoldQtyCst
(
    const long q                      // quantity to be subtracted
)
{
    long retval;
    // avoid negative values in stock:
    retval = ( SoldQtyCst_ - q < 0 ) ? SoldQtyCst_ : q;
    SoldQtyCst_ -= retval;
    SetDirty();
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxPromotionQuotaCstList :: pxPromotionQuotaCstList
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
pxPromotionQuotaCstList :: Select
(
    const int     count_
)
{
    tPROMOTIONQUOTACST fil;
    memset(&fil, 0, sizeof(tPROMOTIONQUOTACST));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo                                */
/*----------------------------------------------------------------------------*/
size_t
pxPromotionQuotaCstList :: Select
(
    const short   BranchNo,
    const short   PromotionNo,
    const long    CustomerNo,
    const long    ArticleNo,
    const int     count_
)
{
    tPROMOTIONQUOTACST fil;
    memset(&fil, 0, sizeof(tPROMOTIONQUOTACST));  // zero out entire record buffer
    fil.BranchNo     = BranchNo;
    fil.Promotion_No = PromotionNo;
    fil.CustomerNo   = CustomerNo;
    fil.ArticleNo    = ArticleNo;
    int cursorid = cCRSPROMOTIONCST_BR_PRO_CST_ART;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Find return entryp depend on articleno                                    */
/*----------------------------------------------------------------------------*/
pxPromotionQuotaCst*
pxPromotionQuotaCstList :: Find
(
    const long ArticleNo
)
{
    pxPromotionQuotaCst *curp = NULL;             // ptr to current entry
    pxPromotionQuotaCstListIter  cursor(*this);  // define an iterator
    while ( (curp = (pxPromotionQuotaCst*) ++cursor) != NULL )
    {
       if (curp->ArticleNo() == ArticleNo )
       {
          break;
       }
    }
    return curp;
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxPromotionQuotaCstList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxPromotionQuotaCst' object:
    pxPromotionQuotaCst *objectp = new pxPromotionQuotaCst(Session(), *(tPROMOTIONQUOTACST*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxPromotionQuotaCst :: Get
(
    DBAccessMode mode
)

{
    tPROMOTIONQUOTACST record;
    memset(&record, 0, sizeof(tPROMOTIONQUOTACST));
    record.BranchNo       = BranchNo_;
    record.Promotion_No    = PromotionNo_;
    record.CustomerNo      = CustomerNo_;
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
pxPromotionQuotaCst :: Put
(
)
{
    tPROMOTIONQUOTACST record;
    memset(&record, 0, sizeof(tPROMOTIONQUOTACST));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tPROMOTIONQUOTACST));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxPromotionQuotaCst :: Delete
(
)
{
    tPROMOTIONQUOTACST record;
    memset(&record, 0, sizeof(tPROMOTIONQUOTACST));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxPromotionQuotaCst :: Read
(
    const void  *record
)
{
    return pxPromotionQuotaCstRead((tPROMOTIONQUOTACST*)record);
}

int
pxPromotionQuotaCst :: ReadLock
(
    const void  *record
)
{
    return pxPromotionQuotaCstReadLock((tPROMOTIONQUOTACST*)record);
}

int
pxPromotionQuotaCst :: Update
(
    const void  *record
)
{
    return pxPromotionQuotaCstUpdate((tPROMOTIONQUOTACST*)record);
}

int
pxPromotionQuotaCst :: Delete
(
    const void  *record
)
{
    return pxPromotionQuotaCstDelete((tPROMOTIONQUOTACST*)record);
}

int
pxPromotionQuotaCst :: Insert
(
    const void  *record
)
{
    return pxPromotionQuotaCstInsert((tPROMOTIONQUOTACST*)record);
}

int
pxPromotionQuotaCstList :: EndBrowse
(
    const int  cursorid
)
{
    return pxPromotionQuotaCstEndBrowse(cursorid);
}


int
pxPromotionQuotaCstList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxPromotionQuotaCstGetNext((tPROMOTIONQUOTACST*)record, cursorid);
}

int
pxPromotionQuotaCstList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxPromotionQuotaCstStartBrowse((tPROMOTIONQUOTACST*)keys, cursorid);
}
