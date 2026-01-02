#include "pxartspecialcond.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArtSpecialCond :: pxArtSpecialCond
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
pxArtSpecialCond :: pxArtSpecialCond
(
    pxArtSpecialCond& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTSPECIALCOND structure to construct this instance.                 */
/*----------------------------------------------------------------------------*/
pxArtSpecialCond :: pxArtSpecialCond
(
    pxSession   *session,
    tARTSPECIALCOND& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtSpecialCond :: pxArtSpecialCond
(
    pxSession *session,
   const pxArtSpecialCond *src
)
    : pxDBRecord(session)
{
    Init();

    if (src != NULL)
       (*this) = *src;
}

/*----------------------------------------------------------------------------*/
/*  read one table entry to construct this instance                           */
/*----------------------------------------------------------------------------*/
pxArtSpecialCond :: pxArtSpecialCond
(
    pxSession *session,
    const long    ArticleNo,                      // Article number
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    ArticleNo_ = ArticleNo;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtSpecialCond :: ~pxArtSpecialCond()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTSPECIALCOND structure.   */
/*----------------------------------------------------------------------------*/
tARTSPECIALCOND&
Assign
(
    tARTSPECIALCOND&           dest,
    const pxArtSpecialCond&       src
)
{
    dest.ArticleNo                 = src.ArticleNo_              ;
    dest.Invoice_Rebate_Pct        = src.InvoiceRebatePct_       ;
    dest.Rebate_In_Kind_Pct        = src.RebateInKindPct_        ;
    dest.Annual_Inv_Reb_Pct        = src.AnnualInvRebPct_        ;
    dest.Annual_Reb_I_K_Pct        = src.AnnualRebIKPct_         ;
    dest.Cust_Reb_Red_Pct          = src.CustRebRedPct_          ;
    dest.Hi_ReimBursement          = src.HiReimBursement_        ;
    dest.Suppl_Hi_Reimb            = src.SupplHiReimb_           ;
    dest.Suppl_Fs_Reimb            = src.SupplFsReimb_           ;
    dest.Suppl_Discount_Pct        = src.SupplDiscountPct_       ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTSPECIALCOND structure to               */
/*  a pxArtSpecialCond object.                                                */
/*----------------------------------------------------------------------------*/
pxArtSpecialCond&
Assign
(
    pxArtSpecialCond&              dest,
    const tARTSPECIALCOND&    src
)
{
    dest.ArticleNo_                 = src.ArticleNo              ;
    dest.InvoiceRebatePct_          = src.Invoice_Rebate_Pct     ;
    dest.RebateInKindPct_           = src.Rebate_In_Kind_Pct     ;
    dest.AnnualInvRebPct_           = src.Annual_Inv_Reb_Pct     ;
    dest.AnnualRebIKPct_            = src.Annual_Reb_I_K_Pct     ;
    dest.CustRebRedPct_             = src.Cust_Reb_Red_Pct       ;
    dest.HiReimBursement_           = src.Hi_ReimBursement       ;
    dest.SupplHiReimb_              = src.Suppl_Hi_Reimb         ;
    dest.SupplFsReimb_              = src.Suppl_Fs_Reimb         ;
    dest.SupplDiscountPct_          = src.Suppl_Discount_Pct     ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtSpecialCond :: Init()
{
    tARTSPECIALCOND    record;
    memset(&record, 0 , sizeof(tARTSPECIALCOND));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTSPECIALCOND struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxArtSpecialCond&
pxArtSpecialCond :: operator=( const pxArtSpecialCond& src)
{
    tARTSPECIALCOND record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTSPECIALCOND structure 'src' to                    */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxArtSpecialCond&
pxArtSpecialCond :: operator=( const tARTSPECIALCOND& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtSpecialCond list objects being inserted in the                   */
/*  following ascending sequence:                                             */
/*----------------------------------------------------------------------------*/
int
pxArtSpecialCond :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const

{
    pxArtSpecialCond *that = (pxArtSpecialCond*)That;
    int retval = (ArticleNo_ == that->ArticleNo_) ? 0
                : (ArticleNo_ > that->ArticleNo_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtSpecialCond :: Get
(
    DBAccessMode mode
)

{
    tARTSPECIALCOND record;
    memset(&record, 0, sizeof(tARTSPECIALCOND));
    record.ArticleNo   = ArticleNo_;
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
pxArtSpecialCond :: Put
(
)
{
    tARTSPECIALCOND record;
    memset(&record, 0, sizeof(tARTSPECIALCOND));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTSPECIALCOND));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxArtSpecialCond :: Delete
(
)
{
    tARTSPECIALCOND record;
    memset(&record, 0, sizeof(tARTSPECIALCOND));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArtSpecialCond :: Read
(
    const void  *record
)
{
    return pxArtSpecialCondRead((tARTSPECIALCOND*)record);
}

int
pxArtSpecialCond :: ReadLock
(
    const void  *record
)
{
    return pxArtSpecialCondReadLock((tARTSPECIALCOND*)record);
}

int
pxArtSpecialCond :: Update
(
    const void  *record
)
{
    return pxArtSpecialCondUpdate((tARTSPECIALCOND*)record);
}

int
pxArtSpecialCond :: Delete
(
    const void  *record
)
{
    return pxArtSpecialCondDelete((tARTSPECIALCOND*)record);
}

int
pxArtSpecialCond :: Insert
(
    const void  *record
)
{
    return pxArtSpecialCondInsert((tARTSPECIALCOND*)record);
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtSpecialCondList :: pxArtSpecialCondList
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
pxArtSpecialCondList :: Select
(
    const int     count_
)
{
    tARTSPECIALCOND fil;
    memset(&fil, 0, sizeof(tARTSPECIALCOND));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via KdAuftragNr, PosNr                        */
/*----------------------------------------------------------------------------*/
size_t
pxArtSpecialCondList :: Select
(
    const long    ArticleNo,
    const int     count_
)
{
    tARTSPECIALCOND fil;
    memset(&fil, 0, sizeof(tARTSPECIALCOND));  // zero out entire record buffer
    fil.ArticleNo   = ArticleNo;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArtSpecialCondList :: AddToList
(
    const void  *record,
    const int  /* row */
)

{
    // construct new 'pxArtSpecialCond' object:
    pxArtSpecialCond *objectp = new pxArtSpecialCond(Session(), *(tARTSPECIALCOND*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArtSpecialCondList :: EndBrowse
(
    const int  cursorid
)
{
    return pxArtSpecialCondEndBrowse(cursorid);
}


int
pxArtSpecialCondList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxArtSpecialCondGetNext((tARTSPECIALCOND*)record, cursorid);
}

int
pxArtSpecialCondList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxArtSpecialCondStartBrowse((tARTSPECIALCOND*)keys, cursorid);
}
