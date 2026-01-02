/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxOrderProLink methods.

REVISION HISTORY

21 July 2011 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxorderprolink.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxOrderProLink :: pxOrderProLink
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
pxOrderProLink :: pxOrderProLink
(
    pxOrderProLink& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tKDAUFTRAGPROLINK structure to construct this instance.               */
/*----------------------------------------------------------------------------*/
pxOrderProLink :: pxOrderProLink
(
    pxSession   *session,
    tKDAUFTRAGPROLINK& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderProLink :: pxOrderProLink
(
    pxSession *session,
   const pxOrderProLink *src
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
pxOrderProLink :: pxOrderProLink
(
    pxSession    *session,
    long         KdAuftragNr          // KdAuftragnr

)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_  = KdAuftragNr;
   // Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxOrderProLink :: ~pxOrderProLink()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tKDAUFTRAGPROLINK structure.   */
/*----------------------------------------------------------------------------*/
tKDAUFTRAGPROLINK&
Assign
(
    tKDAUFTRAGPROLINK&           dest,
    const pxOrderProLink&       src
)
{
    dest.KdAuftragNr              = src.KdAuftragNr_            ;
    strcpy(dest.InvoiceNumberPro,   " ");
    strcpy(dest.InvoiceNumber,   " ");
    src.InvoiceNumberPro_.GetData(dest.InvoiceNumberPro);
    src.InvoiceNumber_.GetData(dest.InvoiceNumber);
    dest.DateProforma             = src.DateProforma_.GetYYYYMMDD() ;
    dest.KdAuftragNrPro           = src.KdAuftragNrPro_            ;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tKDAUFTRAGPROLINK structure to             */
/*  a pxOrderProLink object.                                                  */
/*----------------------------------------------------------------------------*/
pxOrderProLink&
Assign
(
    pxOrderProLink&              dest,
    const tKDAUFTRAGPROLINK&    src
)
{
    dest.KdAuftragNr_              = src.KdAuftragNr            ;
    dest.InvoiceNumberPro_         = src.InvoiceNumberPro       ;
    dest.InvoiceNumber_            = src.InvoiceNumber          ;
    dest.DateProforma_             = nDate(src.DateProforma)    ;
    dest.KdAuftragNrPro_           = src.KdAuftragNrPro         ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxOrderProLink :: Init()
{
    tKDAUFTRAGPROLINK    record;
    memset(&record, 0 , sizeof(tKDAUFTRAGPROLINK));
    Assign(*this, record);

}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tKDAUFTRAGPROLINK struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxOrderProLink&
pxOrderProLink :: operator=( const pxOrderProLink& src)
{
    tKDAUFTRAGPROLINK record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tKDAUFTRAGPROLINK structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxOrderProLink&
pxOrderProLink :: operator=( const tKDAUFTRAGPROLINK& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxOrderProLink list objects being inserted in the                 */
/*  following ascending sequence:                                             */
/*  BranchNo, CustomerNo,MainCstNo,Date                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderProLink :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxOrderProLink *that = (pxOrderProLink*)That;
    int  retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
              : (KdAuftragNr_ > KdAuftragNr_ ? 1 : -1);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxOrderProLinkList :: pxOrderProLinkList
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
pxOrderProLinkList :: Select
(
    const int     count_
)
{
    tKDAUFTRAGPROLINK fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGPROLINK));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via CustomerNo                                */
/*----------------------------------------------------------------------------*/
size_t
pxOrderProLinkList :: Select
(
    const long    KdAuftragNr,
    const int     count_
)
{
    tKDAUFTRAGPROLINK fil;
    memset(&fil, 0, sizeof(tKDAUFTRAGPROLINK));  // zero out entire record buffer
    fil.KdAuftragNr = KdAuftragNr;
    int cursorid = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxOrderProLinkList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new 'pxOrderProLink' object:
    pxOrderProLink *objectp = new pxOrderProLink(Session(), *(tKDAUFTRAGPROLINK*) record);
    InsertAscending(objectp);
    return objectp;
}
/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxOrderProLink :: Get
(
    DBAccessMode mode
)

{
    tKDAUFTRAGPROLINK record;
    memset(&record, 0, sizeof(tKDAUFTRAGPROLINK));
    record.KdAuftragNr = KdAuftragNr_;
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
pxOrderProLink :: Put
(
)
{
    tKDAUFTRAGPROLINK record;
    memset(&record, 0, sizeof(tKDAUFTRAGPROLINK));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tKDAUFTRAGPROLINK));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxOrderProLink :: Delete
(
)
{
    tKDAUFTRAGPROLINK record;
    memset(&record, 0, sizeof(tKDAUFTRAGPROLINK));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxOrderProLink :: Read
(
    const void  *record
)
{
    return pxOrderProLinkRead((tKDAUFTRAGPROLINK*)record);
}

int
pxOrderProLink :: ReadLock
(
    const void  *record
)
{
    return pxOrderProLinkReadLock((tKDAUFTRAGPROLINK*)record);
}

int
pxOrderProLink :: Update
(
    const void  *record
)
{
    return pxOrderProLinkUpdate((tKDAUFTRAGPROLINK*)record);
}

int
pxOrderProLink :: Delete
(
    const void  *record
)
{
    return pxOrderProLinkDelete((tKDAUFTRAGPROLINK*)record);
}

int
pxOrderProLink :: Insert
(
    const void  *record
)
{
    return pxOrderProLinkInsert((tKDAUFTRAGPROLINK*)record);
}

int
pxOrderProLinkList :: EndBrowse
(
    const int  cursorid
)
{
    return pxOrderProLinkEndBrowse(cursorid);
}


int
pxOrderProLinkList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxOrderProLinkGetNext((tKDAUFTRAGPROLINK*)record, cursorid);
}

int
pxOrderProLinkList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxOrderProLinkStartBrowse((tKDAUFTRAGPROLINK*)keys, cursorid);
}
