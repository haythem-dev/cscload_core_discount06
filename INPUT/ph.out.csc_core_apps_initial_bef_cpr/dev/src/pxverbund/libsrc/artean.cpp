#include "pxartean.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArtEan :: pxArtEan
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
pxArtEan :: pxArtEan
(
    pxArtEan& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTIKELNUMMERN structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxArtEan :: pxArtEan
(
    pxSession   *session,
    tARTIKELNUMMERN& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxArtEan :: pxArtEan
(
    pxSession    *session,
    const nString&     Ean,            // Read via this type and
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    Ean_ = Ean;
    Get(mode);
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtEan :: ~pxArtEan()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTIKELNUMMERN structure.      */
/*----------------------------------------------------------------------------*/
tARTIKELNUMMERN&
Assign
(
    tARTIKELNUMMERN&           dest,
    const pxArtEan&       src
)
{
    dest.Pzn                       = src.Pzn_;
    dest.ArtikelNr                 = src.ArtikelNr_;                              ;

    dest.Ean[0] = ' ';
    src.Ean_.GetData(dest.Ean);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTIKELNUMMERN structure to                */
/*  a pxArtEan object.                                                   */
/*----------------------------------------------------------------------------*/
pxArtEan&
Assign
(
    pxArtEan&              dest,
    const tARTIKELNUMMERN&    src
)
{
    dest.Pzn_                    = src.Pzn;
    dest.ArtikelNr_              = src.ArtikelNr;
    dest.Ean_                    = src.Ean;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtEan :: Init()
{
    tARTIKELNUMMERN    record;
    memset(&record, 0 , sizeof(tARTIKELNUMMERN));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTIKELNUMMERN struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxArtEan&
pxArtEan :: operator=( const pxArtEan& src)
{
    tARTIKELNUMMERN record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTIKELNUMMERN structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxArtEan&
pxArtEan :: operator=( const tARTIKELNUMMERN& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtEan :: Get
(
    DBAccessMode mode
)

{
    tARTIKELNUMMERN record;
    memset(&record, 0, sizeof(tARTIKELNUMMERN));
    record.Ean[0] = ' ';
    Ean_.GetData(record.Ean);
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tARTIKELNUMMERN struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(),
                         CMSG_ARTEAN_ENTRY_NOTFOUND, Ean_());
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArtEan :: Read
(
    const void  *record
)
{
    return pxArtikelNummernRead((tARTIKELNUMMERN*)record);
}

int
pxArtEan :: ReadLock
(
    const void  *record
)
{
    return pxArtikelNummernReadLock((tARTIKELNUMMERN*)record);
}

int
pxArtEan :: Update
(
    const void  *record
)
{
    return pxArtikelNummernUpdate((tARTIKELNUMMERN*)record);
}

int
pxArtEan :: Delete
(
    const void  *record
)
{
    return pxArtikelNummernDelete((tARTIKELNUMMERN*)record);
}

int
pxArtEan :: Insert
(
    const void  *record
)
{
    return pxArtikelNummernInsert((tARTIKELNUMMERN*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtEan list objects being inserted in the                  */
/*  following ascending sequence:                                             */
/*  KdAuftragNr,PosNr                                                         */
/*----------------------------------------------------------------------------*/
int
pxArtEan :: CompareTo
(
    const nCollectable   *That,
          void           * /*p*/,
    const long           /*lparm*/
)   const

{
    pxArtEan *that = (pxArtEan*)That;
    int retval = (Ean_ == that->Ean_) ? 0
                : (Ean_ > that->Ean_ ? 1 : -1);

    return retval;
}

/*----------------------------------------------------------------------------*/
/*  List Constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtEanList :: pxArtEanList
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
pxArtEanList :: Select
(
    const int     count_
)
{
    tARTIKELNUMMERN fil;
    memset(&fil, 0, sizeof(tARTIKELNUMMERN));  // zero out entire record buffer
    int cursorid = cCRS_NOWHERE;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via EanNumber                                 */
/*----------------------------------------------------------------------------*/
size_t
pxArtEanList :: Select
(
    const nString& Ean,
    const int     count_
)
{
    tARTIKELNUMMERN fil;
    memset(&fil, 0, sizeof(tARTIKELNUMMERN));  // zero out entire record buffer
    fil.Ean[0] = ' ';
    Ean.GetData(fil.Ean);
    int cursorid    = cCRS_DEFAULT;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Initialize and do selection via artikelnr                                 */
/*----------------------------------------------------------------------------*/
size_t
pxArtEanList :: Select
(
    const long    ArtikelNr,
    const int     count_
)
{
    tARTIKELNUMMERN fil;
    memset(&fil, 0, sizeof(tARTIKELNUMMERN));  // zero out entire record buffer
    fil.ArtikelNr = ArtikelNr;
    int cursorid    = cCRSARTNUM_ARTIKELNR;
    nDBSelect(&fil, cursorid, count_);

    return Entries();
}
/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArtEanList :: AddToList
(
    const void  *record,
    const int  /* row */
)

{
    // construct new 'pxArtEan' object:
    pxArtEan *objectp = new pxArtEan(Session(), *(tARTIKELNUMMERN*) record);
    InsertAscending(objectp);
    return objectp;
}

int
pxArtEanList :: EndBrowse
(
    const int  cursorid
)
{
    return pxArtikelNummernEndBrowse(cursorid);
}


int
pxArtEanList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxArtikelNummernGetNext((tARTIKELNUMMERN*)record, cursorid);
}

int
pxArtEanList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxArtikelNummernStartBrowse((tARTIKELNUMMERN*)keys, cursorid);
}

