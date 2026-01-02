#include "pxstockentry.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxStockEntry :: pxStockEntry
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
pxStockEntry :: pxStockEntry
(
    pxStockEntry& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tSTOCKENTRY structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxStockEntry :: pxStockEntry
(
    pxSession   *session,
    tSTOCKENTRY& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxStockEntry :: pxStockEntry
(
    pxSession    *session,
    nDate&       Date,                   // Date
    short       BranchNo,               // BranchNumber
    long        ArticleNo,              // Articlenumber
    DBAccessMode mode

)
    : pxDBRecord(session)
{
    Init();
    Date_       = Date;
    BranchNo_   = BranchNo;
    ArticleNo_  = ArticleNo;
    Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxStockEntry :: ~pxStockEntry()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tSTOCKENTRY structure.         */
/*----------------------------------------------------------------------------*/
tSTOCKENTRY&
Assign
(
    tSTOCKENTRY&           dest,
    const pxStockEntry&     src
)
{
    dest.Date       = src.Date_.GetYYYYMMDD();
    dest.BranchNo   = src.BranchNo_;
    dest.ArticleNo  = src.ArticleNo_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tSTOCKENTRY structure to                   */
/*  a pxStockEntry object.                                                    */
/*----------------------------------------------------------------------------*/
pxStockEntry&
Assign
(
    pxStockEntry&              dest,
    const tSTOCKENTRY&         src
)
{
    dest.Date_      = nDate(src.Date);
    dest.BranchNo_  = src.BranchNo;
    dest.ArticleNo_ = src.ArticleNo;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxStockEntry :: Init()
{
    tSTOCKENTRY    record;
    memset(&record, 0 , sizeof(tSTOCKENTRY));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tSTOCKENTRY struct and then imported to self.                         */
/*----------------------------------------------------------------------------*/
pxStockEntry&
pxStockEntry :: operator=( const pxStockEntry& src)
{
    tSTOCKENTRY record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tSTOCKENTRY structure 'src' to               */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxStockEntry&
pxStockEntry :: operator=( const tSTOCKENTRY& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxStockEntry :: Get
(
    DBAccessMode mode
)

{
    tSTOCKENTRY record;
    memset(&record, 0, sizeof(tSTOCKENTRY));
    record.Date      = Date_.GetYYYYMMDD();
    record.BranchNo  = BranchNo_;
    record.ArticleNo = ArticleNo_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tSTOCKENTRY struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_STOCKENTRY_NOTFOUND, ArticleNo_,BranchNo_);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxStockEntry :: Put
(
)
{
    tSTOCKENTRY record;
    memset(&record, 0, sizeof(tSTOCKENTRY));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tSTOCKENTRY));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxStockEntry :: Delete
(
)
{
    tSTOCKENTRY record;
    memset(&record, 0, sizeof(tSTOCKENTRY));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxStockEntry :: Read
(
    const void  *record
)
{
    return pxStockEntryRead((tSTOCKENTRY*)record);
}

int
pxStockEntry :: ReadLock
(
    const void  *record
)
{
    return pxStockEntryReadLock((tSTOCKENTRY*)record);
}

int
pxStockEntry :: Update
(
    const void  *record
)
{
    return pxStockEntryUpdate((tSTOCKENTRY*)record);
}

int
pxStockEntry :: Delete
(
    const void  *record
)
{
    return pxStockEntryDelete((tSTOCKENTRY*)record);
}

int
pxStockEntry :: Insert
(
    const void  *record
)
{
    return pxStockEntryInsert((tSTOCKENTRY*)record);
}

int
pxStockEntryList :: EndBrowse
(
    const int  cursorid
)
{
    return pxStockEntryEndBrowse(cursorid);
}


int
pxStockEntryList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxStockEntryGetNext((tSTOCKENTRY*)record, cursorid);
}

int
pxStockEntryList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxStockEntryStartBrowse((tSTOCKENTRY*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxStockEntry list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxStockEntry :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxStockEntry *that = (pxStockEntry*)That;
    int retval = (Date_ == that->Date_) ? 0
                : (Date_ > that->Date_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxStockEntryList :: pxStockEntryList
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
pxStockEntryList :: Select
(
    const int     count_
)
{
    tSTOCKENTRY fil;
    memset(&fil, 0, sizeof(tSTOCKENTRY));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxStockEntryList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxStockEntry' object:
    pxStockEntry *objectp = new pxStockEntry(Session(), *(tSTOCKENTRY*) record);
    InsertAscending(objectp);
    return objectp;
}

