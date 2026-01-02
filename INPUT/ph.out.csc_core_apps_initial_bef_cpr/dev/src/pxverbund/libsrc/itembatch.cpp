/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxItemBatch  methods.

REVISION HISTORY

04 May 2010 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxitembatch.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxItemBatch :: pxItemBatch
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
pxItemBatch :: pxItemBatch
(
    pxItemBatch& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGPOSCHARGE structure to construct this instance.             */
/*----------------------------------------------------------------------------*/
pxItemBatch :: pxItemBatch
(
    pxSession   *session,
    tKDAUFTRAGPOSCHARGE& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxItemBatch :: pxItemBatch
(
    pxSession    *session,
    const long   KdAuftragNr,         // customer ordernumber
    const long   PosNr                // Positionnumber
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_      = KdAuftragNr;
    PosNr_            = PosNr;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxItemBatch :: ~pxItemBatch()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGPOSCHARGE structure. */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGPOSCHARGE&
Assign
(
    tKDAUFTRAGPOSCHARGE&           dest,
    const pxItemBatch&     src
)
{
    dest.KdAuftragNr            = src.KdAuftragNr_     ;
    dest.PosNr                  = src.PosNr_           ;
    dest.ChargenNr[0]           = ' ';
    src.BatchNr_.GetData(dest.ChargenNr);
    dest.QuantityOrdered        = src.QuantityOrdered_ ;
    dest.FixBatch               = src.FixBatch_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGPOSCHARGE structure to           */
/*  a pxItemBatch object.                                                    */
/*----------------------------------------------------------------------------*/
pxItemBatch&
Assign
(
    pxItemBatch&              dest,
    const tKDAUFTRAGPOSCHARGE&         src
)
{
    dest.KdAuftragNr_           = src.KdAuftragNr     ;
    dest.PosNr_                 = src.PosNr           ;
    dest.BatchNr_               = src.ChargenNr       ;
    dest.QuantityOrdered_       = src.QuantityOrdered ;
    dest.FixBatch_              = src.FixBatch        ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxItemBatch :: Init()
{
    tKDAUFTRAGPOSCHARGE    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGPOSCHARGE));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGPOSCHARGE struct and then imported to self.                        */
/*----------------------------------------------------------------------------*/
pxItemBatch&
pxItemBatch :: operator=( const pxItemBatch& src)
{
    tKDAUFTRAGPOSCHARGE record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGPOSCHARGE structure 'src' to           */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxItemBatch&
pxItemBatch :: operator=( const tKDAUFTRAGPOSCHARGE& src)
{
    return Assign(*this, src);
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxItemBatch :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGPOSCHARGE record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSCHARGE));
    record.KdAuftragNr    = KdAuftragNr_ ;
    record.PosNr          = PosNr_       ;

    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tKDAUFTRAGPOSCHARGE struct
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
pxItemBatch :: Put
(
)
{
    tKDAUFTRAGPOSCHARGE record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSCHARGE));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGPOSCHARGE));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxItemBatch :: Delete
(
)
{
    tKDAUFTRAGPOSCHARGE record;
    memset(&record, 0, sizeof(tKDAUFTRAGPOSCHARGE));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxItemBatch :: Read
(
    const void  *record
)
{
    return pxItemChargeRead((tKDAUFTRAGPOSCHARGE*)record);
}

int
pxItemBatch :: ReadLock
(
    const void  *record
)
{
    return pxItemChargeReadLock((tKDAUFTRAGPOSCHARGE*)record);
}

int
pxItemBatch :: Update
(
    const void  *record
)
{
    return pxItemChargeUpdate((tKDAUFTRAGPOSCHARGE*)record);
}

int
pxItemBatch :: Delete
(
    const void  *record
)
{
    return pxItemChargeDelete((tKDAUFTRAGPOSCHARGE*)record);
}

int
pxItemBatch :: Insert
(
    const void  *record
)
{
    return pxItemChargeInsert((tKDAUFTRAGPOSCHARGE*)record);
}

int
pxItemBatchList :: EndBrowse
(
    const int  cursorid
)
{
    return pxItemChargeEndBrowse(cursorid);
}


int
pxItemBatchList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxItemChargeGetNext((tKDAUFTRAGPOSCHARGE*)record, cursorid);
}

int
pxItemBatchList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxItemChargeStartBrowse((tKDAUFTRAGPOSCHARGE*)keys, cursorid);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxItemBatch list objects being inserted in the                    */
/*  following ascending sequence:                                             */
/*  ProgrammPartner                                                           */
/*----------------------------------------------------------------------------*/
int
pxItemBatch :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxItemBatch *that = (pxItemBatch*)That;

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
pxItemBatchList :: pxItemBatchList
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
pxItemBatchList :: Select
(
    const long   KdAuftragNr,
    const long   PosNr,
    const int    count_
)
{
    tKDAUFTRAGPOSCHARGE fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGPOSCHARGE));  // zero out entire record buffer
    fil.KdAuftragNr  = KdAuftragNr;
    fil.PosNr        = PosNr;
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxItemBatchList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxItemBatch' object:
    pxItemBatch *objectp = new pxItemBatch(Session(), *(tKDAUFTRAGPOSCHARGE*) record);
    InsertAscending(objectp);
    return objectp;
}
