#include "pxkdauftragposrefund.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxKdAuftragPosRefund :: pxKdAuftragPosRefund
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
pxKdAuftragPosRefund :: pxKdAuftragPosRefund
(
    pxKdAuftragPosRefund& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGPOSREFUND structure to construct this instance.          */
/*----------------------------------------------------------------------------*/
pxKdAuftragPosRefund :: pxKdAuftragPosRefund
(
    pxSession   *session,
    tKDAUFTRAGPOSREFUND& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}


/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxKdAuftragPosRefund :: pxKdAuftragPosRefund
(
    pxSession    *session,
    const long   KdAuftragNr,
    const long   PosNr,
    const double RefundValue,
    const short  RefundSrc,
    const short  Promotion_No
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_      = KdAuftragNr;
    PosNr_            = PosNr;
    RefundValue_      = RefundValue;
    RefundSrc_        = RefundSrc;
    Promotion_No_     = Promotion_No;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxKdAuftragPosRefund :: ~pxKdAuftragPosRefund()
{
}

/*----------------------------------------------------------------------------*/
/* Assign the values of the 'src' object to a tKDAUFTRAGPOSREFUND structure*/
/*----------------------------------------------------------------------------*/
tKDAUFTRAGPOSREFUND&
Assign
(
    tKDAUFTRAGPOSREFUND&           dest,
    const pxKdAuftragPosRefund&       src
)
{
    dest.KdAuftragNr                  = src.KdAuftragNr_;
    dest.PosNr                        = src.PosNr_;
    dest.RefundValue                  = src.RefundValue_;
    dest.RefundSrc                    = src.RefundSrc_;
    dest.Promotion_No                 = src.Promotion_No_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGPOSREFUND structure to           */
/*  a pxKdAuftragPosRefund object.                                                */
/*----------------------------------------------------------------------------*/
pxKdAuftragPosRefund&
Assign
(
    pxKdAuftragPosRefund&              dest,
    const tKDAUFTRAGPOSREFUND&    src
)
{
    dest.KdAuftragNr_                  = src.KdAuftragNr;
    dest.PosNr_                        = src.PosNr;
    dest.RefundValue_                  = src.RefundValue;
    dest.RefundSrc_                    = src.RefundSrc;
    dest.Promotion_No_                 = src.Promotion_No;
        return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxKdAuftragPosRefund :: Init()
{
    tKDAUFTRAGPOSREFUND    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGPOSREFUND));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGPOSREFUND struct and then imported to self.                     */
/*----------------------------------------------------------------------------*/
pxKdAuftragPosRefund&
pxKdAuftragPosRefund :: operator=( const pxKdAuftragPosRefund& src)
{
    tKDAUFTRAGPOSREFUND record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGPOSREFUND structure 'src' to        */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxKdAuftragPosRefund&
pxKdAuftragPosRefund :: operator=( const tKDAUFTRAGPOSREFUND& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxKdAuftragPosRefund :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGPOSREFUND record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSREFUND));

    record.KdAuftragNr                  = KdAuftragNr_;
    record.PosNr                        = PosNr_;
    record.RefundValue                  = RefundValue_;
    record.RefundSrc                    = RefundSrc_;
    record.Promotion_No                 = Promotion_No_;

        int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKDAUFTRAGPOSREFUND struct
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxKdAuftragPosRefund :: Put
(
)
{
    tKDAUFTRAGPOSREFUND record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSREFUND));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGPOSREFUND));
}

/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxKdAuftragPosRefund :: Delete
(
)
{
    tKDAUFTRAGPOSREFUND record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSREFUND));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxKdAuftragPosRefund :: Read
(
    const void  *record
)
{
    return pxKdAuftragPosRefundRead((tKDAUFTRAGPOSREFUND*)record);
}

int
pxKdAuftragPosRefund :: ReadLock
(
    const void  *record
)
{
    return pxKdAuftragPosRefundReadLock((tKDAUFTRAGPOSREFUND*)record);
}

int
pxKdAuftragPosRefund :: Update
(
    const void  *record
)
{
    return pxKdAuftragPosRefundUpdate((tKDAUFTRAGPOSREFUND*)record);
}

int
pxKdAuftragPosRefund :: Delete
(
    const void  *record
)
{
    return pxKdAuftragPosRefundDelete((tKDAUFTRAGPOSREFUND*)record);
}


int
pxKdAuftragPosRefund :: Insert
(
    const void  *record
)
{
    return pxKdAuftragPosRefundInsert((tKDAUFTRAGPOSREFUND*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxKdAuftragPosRefund list objects being inserted in the               */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxKdAuftragPosRefund :: CompareTo
(
    const nCollectable   *That,
        void           * /* p */,
    const long           /* lparm */
)   const
{
    pxKdAuftragPosRefund *that = (pxKdAuftragPosRefund*)That;
    int retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
                : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);
    if ( retval == 0 )
       retval = (PosNr_ == that->PosNr_) ? 0
                : (PosNr_ > that->PosNr_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxKdAuftragPosRefundList :: pxKdAuftragPosRefundList
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
pxKdAuftragPosRefundList :: Select
(
    const int     count_
)
{
    tKDAUFTRAGPOSREFUND fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGPOSREFUND));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via KdAuftragNr, PosNr                        */
/*----------------------------------------------------------------------------*/
size_t
pxKdAuftragPosRefundList :: Select
(
    const long     KdAuftragNr,
    const long     PosNr,
    const int     count_
)
{
    tKDAUFTRAGPOSREFUND fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGPOSREFUND));  // zero out entire record buffer
    fil.KdAuftragNr = KdAuftragNr;
    fil.PosNr     = PosNr;
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxKdAuftragPosRefundList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxKdAuftragPosRefund' object:
    pxKdAuftragPosRefund *objectp = new pxKdAuftragPosRefund(Session(), *(tKDAUFTRAGPOSREFUND*) record);
    InsertAscending(objectp);
    return objectp;
}

/*----------------------------------------------------------------------------*/
/* Find returns a pxKdAuftragPosRefund pointer to the corresponding entry     */
/* depend on given Params. If entry is not found within the list,so NULLP will*/
/* be returned                                                                */
/*----------------------------------------------------------------------------*/
pxKdAuftragPosRefund *
pxKdAuftragPosRefundList :: Find
(
    const short PromotionNo
)
{
    pxKdAuftragPosRefundListIter   iter( *this );        // define iterator
    pxKdAuftragPosRefund          *entryp = NULL;         // pointer to listentry

    iter.Reset();                                   // top of list
    while ( ( entryp = ( pxKdAuftragPosRefund *) ++iter) != NULL ) // browse list
    {
       if ( entryp->Promotion_No() == PromotionNo )
       {
          break;
       }
    }
    return   entryp;                               // return entrypointer
}
/*----------------------------------------------------------------------------*/
/*  Find entry within the List depend on PharmacyGroupId                      */
/*----------------------------------------------------------------------------*/
/*pxKdAuftragPosRefund*
pxKdAuftragPosRefundList :: Find
(
    const nString& PharmacyGroupId
)

{
    pxKdAuftragPosRefundListIter iter( *this );  // define iterator
    pxKdAuftragPosRefund           *entryp;      // pointer to listentry

    iter.Reset();                           // top of list
    while ( ( entryp = ( pxKdAuftragPosRefund*) ++iter) != NULL ) // browse list
    {
        if ( entryp->PharmacyGroupId() == PharmacyGroupId )
        {
            break;
        }
    }
    return entryp;
}
*/

int
pxKdAuftragPosRefundList :: EndBrowse
(
    const int  cursorid
)
{
    return pxKdAuftragPosRefundEndBrowse(cursorid);
}


int
pxKdAuftragPosRefundList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxKdAuftragPosRefundGetNext((tKDAUFTRAGPOSREFUND*)record, cursorid);
}

int
pxKdAuftragPosRefundList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxKdAuftragPosRefundStartBrowse((tKDAUFTRAGPOSREFUND*)keys, cursorid);
}

