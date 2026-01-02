/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxKdAuftragDebtRel  methods.

REVISION HISTORY

08 June 2012 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxkdauftragdebtrel.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxKdAuftragDebtRel :: pxKdAuftragDebtRel
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
pxKdAuftragDebtRel :: pxKdAuftragDebtRel
(
    pxKdAuftragDebtRel& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGDEBTREL structure to construct this instance.                */
/*----------------------------------------------------------------------------*/
pxKdAuftragDebtRel :: pxKdAuftragDebtRel
(
    pxSession   *session,
    tKDAUFTRAGDEBTREL& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxKdAuftragDebtRel :: pxKdAuftragDebtRel
(
    pxSession    *session,
    const long   KdAuftragNr,         // customer ordernumber
    const long   relCounter
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_      = KdAuftragNr;
    RelCounter_       = relCounter;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxKdAuftragDebtRel :: ~pxKdAuftragDebtRel()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGDEBTREL structure.    */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGDEBTREL&
Assign
(
    tKDAUFTRAGDEBTREL&           dest,
    const pxKdAuftragDebtRel&     src
)
{
    dest.KdAuftragNr            = src.KdAuftragNr_     ;
    dest.RelReason[0] = ' ';
    src.RelReason_.GetData(dest.RelReason)              ;
    dest.RelComment[0] = ' ';
    src.RelComment_.GetData(dest.RelComment)            ;
    dest.RelUser[0] = ' ';
    src.RelUser_.GetData(dest.RelUser)                  ;
    dest.IsReleased = src.IsReleased_                 ;
    dest.DiscussionNeeded = src.DiscussionNeeded_ ;
    dest.RelCounter = src.RelCounter_                 ;
    dest.CancelCounter = src.CancelCounter_         ;
    dest.ApprovalCounter = src.ApprovalCounter_           ;
    dest.DebtLimit = src.DebtLimit_           ;
    dest.UsedDebtLimit = src.UsedDebtLimit_           ;
    dest.OrderValue = src.OrderValue_           ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGDEBTREL structure to              */
/*  a pxKdAuftragDebtRel object.                                                  */
/*----------------------------------------------------------------------------*/
pxKdAuftragDebtRel&
Assign
(
    pxKdAuftragDebtRel&              dest,
    const tKDAUFTRAGDEBTREL&         src
)
{
    dest.KdAuftragNr_          = src.KdAuftragNr     ;
    dest.RelReason_            = src.RelReason       ;
    dest.RelComment_           = src.RelComment      ;
    dest.RelUser_              = src.RelUser         ;
    dest.IsReleased_           = src.IsReleased      ;
    dest.DiscussionNeeded_     = src.DiscussionNeeded;
    dest.RelCounter_           = src.RelCounter      ;
    dest.CancelCounter_        = src.CancelCounter   ;
    dest.ApprovalCounter_      = src.ApprovalCounter ;
    dest.DebtLimit_            = src.DebtLimit       ;
    dest.UsedDebtLimit_        = src.UsedDebtLimit   ;
    dest.OrderValue_           = src.OrderValue      ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxKdAuftragDebtRel :: Init()
{
    tKDAUFTRAGDEBTREL    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGDEBTREL));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGDEBTREL struct and then imported to self.                        */
/*----------------------------------------------------------------------------*/
pxKdAuftragDebtRel&
pxKdAuftragDebtRel :: operator=( const pxKdAuftragDebtRel& src)
{
    tKDAUFTRAGDEBTREL record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGDEBTREL structure 'src' to              */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxKdAuftragDebtRel&
pxKdAuftragDebtRel :: operator=( const tKDAUFTRAGDEBTREL& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxKdAuftragDebtRel :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGDEBTREL record;
    memset(&record, 0, sizeof(tKDAUFTRAGDEBTREL));
    record.KdAuftragNr    = KdAuftragNr_ ;
    record.RelCounter     = RelCounter_;

    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKDAUFTRAGDEBTREL struct
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
pxKdAuftragDebtRel :: Put
(
)
{
    tKDAUFTRAGDEBTREL record;
    memset(&record, 0, sizeof(tKDAUFTRAGDEBTREL));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGDEBTREL));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxKdAuftragDebtRel :: Delete
(
)
{
    tKDAUFTRAGDEBTREL record;
    memset(&record, 0, sizeof(tKDAUFTRAGDEBTREL));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxKdAuftragDebtRel :: Read
(
    const void  *record
)
{
    return pxKdauftragDebtRelRead((tKDAUFTRAGDEBTREL*)record);
}

int
pxKdAuftragDebtRel :: ReadLock
(
    const void  *record
)
{
    return pxKdauftragDebtRelReadLock((tKDAUFTRAGDEBTREL*)record);
}

int
pxKdAuftragDebtRel :: Update
(
    const void  *record
)
{
    return pxKdauftragDebtRelUpdate((tKDAUFTRAGDEBTREL*)record);
}

int
pxKdAuftragDebtRel :: Delete
(
    const void  *record
)
{
    return pxKdauftragDebtRelDelete((tKDAUFTRAGDEBTREL*)record);
}

int
pxKdAuftragDebtRel :: Insert
(
    const void  *record
)
{
    return pxKdauftragDebtRelInsert((tKDAUFTRAGDEBTREL*)record);
}

int
pxKdAuftragDebtRelList :: EndBrowse
(
    const int  cursorid
)
{
    return pxKdauftragDebtRelEndBrowse(cursorid);
}


int
pxKdAuftragDebtRelList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxKdauftragDebtRelGetNext((tKDAUFTRAGDEBTREL*)record, cursorid);
}

int
pxKdAuftragDebtRelList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxKdauftragDebtRelStartBrowse((tKDAUFTRAGDEBTREL*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxKdAuftragDebtRel list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxKdAuftragDebtRel :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxKdAuftragDebtRel *that = (pxKdAuftragDebtRel*)That;

    int retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
                : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);

    if(retval == 0)
    {
        retval = (RelCounter_ == that->RelCounter_) ? 0
                : (RelCounter_ > that->RelCounter_ ? 1 : -1);
    }

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxKdAuftragDebtRelList :: pxKdAuftragDebtRelList
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
pxKdAuftragDebtRelList :: Select
(
    const long   KdAuftragNr,
    const int    count_
)
{
    tKDAUFTRAGDEBTREL fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGDEBTREL));  // zero out entire record buffer
    fil.KdAuftragNr  = KdAuftragNr;
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

int
pxKdAuftragDebtRelList :: SelectDataForMaxRelCount
(
        const long   KdAuftragNr,
        const int    count_
)
{
    tKDAUFTRAGDEBTREL record;
    memset(&record, 0, sizeof(tKDAUFTRAGDEBTREL));
    record.KdAuftragNr    = KdAuftragNr ;

    int cursorid = cCRSDEBTREL_GETDATAFORMAXRELCOUNT;
    nDBSelect(&record, cursorid, count_);

    return static_cast<int>(Entries());
}

size_t
pxKdAuftragDebtRelList :: SelectApprovalData
(
    const long   KdAuftragNr,
    const int    count_
)
{
    tKDAUFTRAGDEBTREL fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGDEBTREL));  // zero out entire record buffer
    fil.KdAuftragNr  = KdAuftragNr;
    int cursorid    = cCRSDEBTREL_GETAPPROVALDATAFORORDER;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

int pxKdAuftragDebtRelList :: SelectUserVote
(
    const long   KdAuftragNr,
    const nString& userName,
    const int count_
)
{
     tKDAUFTRAGDEBTREL record;
    memset(&record, 0, sizeof(tKDAUFTRAGDEBTREL));
    record.KdAuftragNr    = KdAuftragNr ;
    strncpy(record.RelUser,userName, 30);

    int cursorid = cCRSDEBTREL_CHECKUSERVOTE;
    nDBSelect(&record, cursorid, count_);

    return static_cast<int>(Entries());
}

int pxKdAuftragDebtRelList :: SelectVote
(
        const long KdAuftragNr,
        const int count_
)
{
    tKDAUFTRAGDEBTREL record;
    memset(&record, 0, sizeof(tKDAUFTRAGDEBTREL));
    record.KdAuftragNr    = KdAuftragNr ;

    int cursorid = cCRSDEBTREL_CHECKVOTE;
    nDBSelect(&record, cursorid, count_);

    return static_cast<int>(Entries());
}

int pxKdAuftragDebtRelList :: SelectForCopy
(
        const long KdAuftragNr,
        const int count_
)
{
    tKDAUFTRAGDEBTREL record;
    memset(&record, 0, sizeof(tKDAUFTRAGDEBTREL));
    record.KdAuftragNr    = KdAuftragNr ;

    int cursorid = cCRSDEBTREL_SELECTFORCOPY;
    nDBSelect(&record, cursorid, count_);

    return static_cast<int>(Entries());
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxKdAuftragDebtRelList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxKdAuftragDebtRel' object:
    pxKdAuftragDebtRel *objectp = new pxKdAuftragDebtRel(Session(), *(tKDAUFTRAGDEBTREL*) record);
    Append(objectp);
    return objectp;
}

