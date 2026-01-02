#include "pxorderdiscacc.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderDiscAcc :: pxOrderDiscAcc
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
pxOrderDiscAcc :: pxOrderDiscAcc
(
    pxOrderDiscAcc& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGDISCACC structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxOrderDiscAcc :: pxOrderDiscAcc
(
    pxSession   *session,
    tKDAUFTRAGDISCACC& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderDiscAcc :: pxOrderDiscAcc
(
    pxSession *session,
   const pxOrderDiscAcc *src
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
pxOrderDiscAcc :: pxOrderDiscAcc
(
    pxSession    *session,
    short        BranchNo,            // Branchnumber
    long         KdAuftragNr          // KdAuftragnr

)
    : pxDBRecord(session)
{
    Init();
    BranchNo_     = BranchNo;
    KdAuftragNr_  = KdAuftragNr;
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderDiscAcc :: ~pxOrderDiscAcc()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGDISCACC structure.         */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGDISCACC&
Assign
(
    tKDAUFTRAGDISCACC&           dest,
    const pxOrderDiscAcc&       src
)
{
    dest.KdAuftragNr              = src.KdAuftragNr_            ;
    dest.SwChain                  = src.SwChain_                ;
    dest.DateFrom                 = src.DateFrom_.GetYYYYMMDD() ;
    dest.DateTo                   = src.DateTo_.GetYYYYMMDD()   ;
    dest.BranchNo                 = src.BranchNo_               ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGDISCACC structure to                   */
/*  a pxOrderDiscAcc object.                                                    */
/*----------------------------------------------------------------------------*/
pxOrderDiscAcc&
Assign
(
    pxOrderDiscAcc&              dest,
    const tKDAUFTRAGDISCACC&    src
)
{
    dest.KdAuftragNr_              = src.KdAuftragNr            ;
    dest.SwChain_                  = src.SwChain                ;
    dest.DateFrom_                 = nDate(src.DateFrom)        ;
    dest.DateTo_                   = nDate(src.DateTo)          ;
    dest.BranchNo_                 = src.BranchNo               ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderDiscAcc :: Init()
{
    tKDAUFTRAGDISCACC    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGDISCACC));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGDISCACC struct and then imported to self.                              */
/*----------------------------------------------------------------------------*/
pxOrderDiscAcc&
pxOrderDiscAcc :: operator=( const pxOrderDiscAcc& src)
{
    tKDAUFTRAGDISCACC record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGDISCACC structure 'src' to                    */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxOrderDiscAcc&
pxOrderDiscAcc :: operator=( const tKDAUFTRAGDISCACC& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxOrderDiscAcc list objects being inserted in the                   */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo,MainCstNo,Date                                                      */
/*----------------------------------------------------------------------------*/
int
pxOrderDiscAcc :: CompareTo
(
    const nCollectable   *That,
          void*          ,
    const long
)   const
{
    pxOrderDiscAcc *that = (pxOrderDiscAcc*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                : (BranchNo_ > BranchNo_ ? 1 : -1);
    if ( retval == 0 )
       retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
              : (KdAuftragNr_ > KdAuftragNr_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderDiscAccList :: pxOrderDiscAccList
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
pxOrderDiscAccList :: Select
(
    const int     count_
)
{
    tKDAUFTRAGDISCACC fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGDISCACC));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo                                */
/*----------------------------------------------------------------------------*/
size_t
pxOrderDiscAccList :: Select
(
    const short   BranchNo,
    const long    KdAuftragNr,
    const int     count_
)
{
    tKDAUFTRAGDISCACC fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGDISCACC));  // zero out entire record buffer
    fil.BranchNo    = BranchNo;
    fil.KdAuftragNr = KdAuftragNr;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderDiscAccList :: AddToList
(
    const void  *record,
    const int
)
{
    // construct new 'pxOrderDiscAcc' object:
    pxOrderDiscAcc *objectp = new pxOrderDiscAcc(Session(), *(tKDAUFTRAGDISCACC*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderDiscAcc :: Get
(
    DBAccessMode mode
)
{
    tKDAUFTRAGDISCACC record;
    memset(&record, 0, sizeof(tKDAUFTRAGDISCACC));
    record.BranchNo    = BranchNo_;
    record.KdAuftragNr = KdAuftragNr_;
    int retval        = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this) = record;        // import the data from tARTICLEQUOTA struct

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxOrderDiscAcc :: Put
(
)
{
    tKDAUFTRAGDISCACC record;
    memset(&record, 0, sizeof(tKDAUFTRAGDISCACC));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGDISCACC));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxOrderDiscAcc :: Delete
(
)
{
    tKDAUFTRAGDISCACC record;
    memset(&record, 0, sizeof(tKDAUFTRAGDISCACC));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOrderDiscAcc :: Read
(
    const void  *record
)
{
    return pxOrderDiscAccRead((tKDAUFTRAGDISCACC*)record);
}

int
pxOrderDiscAcc :: ReadLock
(
    const void  *record
)
{
    return pxOrderDiscAccReadLock((tKDAUFTRAGDISCACC*)record);
}

int
pxOrderDiscAcc :: Update
(
    const void  *record
)
{
    return pxOrderDiscAccUpdate((tKDAUFTRAGDISCACC*)record);
}

int
pxOrderDiscAcc :: Delete
(
    const void  *record
)
{
    return pxOrderDiscAccDelete((tKDAUFTRAGDISCACC*)record);
}

int
pxOrderDiscAcc :: Insert
(
    const void  *record
)
{
    return pxOrderDiscAccInsert((tKDAUFTRAGDISCACC*)record);
}

int
pxOrderDiscAccList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOrderDiscAccEndBrowse(cursorid);
}


int
pxOrderDiscAccList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxOrderDiscAccGetNext((tKDAUFTRAGDISCACC*)record, cursorid);
}

int
pxOrderDiscAccList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOrderDiscAccStartBrowse((tKDAUFTRAGDISCACC*)keys, cursorid);
}
