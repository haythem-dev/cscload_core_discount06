#include "pxartsto.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

extern bool pxGlobalNoDatabaseWrite;
extern bool pxGlobalNoWriteToLog;

/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxArtStoreLoc :: pxArtStoreLoc()
{
    Init();
}

pxArtStoreLoc :: pxArtStoreLoc
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
pxArtStoreLoc :: pxArtStoreLoc
(
    pxArtStoreLoc& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTIKELLAGERORT structure to construct this instance.                */
/*----------------------------------------------------------------------------*/
pxArtStoreLoc :: pxArtStoreLoc
(
    pxSession   *session,
    tARTIKELLAGERORT& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxArtStoreLoc :: pxArtStoreLoc
(
    pxSession   *session,
    long       ArtikelNr,                  // Read via this type
    short      FilialNr,
    short      LagerBereichNr,
    char    *LagerFachNr,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    ArtikelNr_ = ArtikelNr;
    FilialNr_ = FilialNr;
    LagerBereichNr_ = LagerBereichNr;
    LagerFachNr_ = LagerFachNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtStoreLoc :: ~pxArtStoreLoc()
{
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTIKELLAGERORT structure.    */
/*----------------------------------------------------------------------------*/
tARTIKELLAGERORT&
Assign
(
    tARTIKELLAGERORT&    dest,
    const pxArtStoreLoc& src
)
{
    // Copy native data types:
    dest.ArtikelNr             = src.ArtikelNr_;
    dest.FilialNr              = src.FilialNr_;
    dest.LagerBereichNr        = src.LagerBereichNr_;
    dest.DatumVerfall          = src.DatumVerfall_;
    dest.Bestand               = src.Bestand_;
    dest.VerbundArtikel        = src.VerbundArtikel_;

    // Strings:
    dest.StationNr[0]          = ' ';
    src.StationNr_.GetData     (dest.StationNr                                );
    dest.LagerFachNr[0]        = ' ';
    src.LagerFachNr_.GetData   (dest.LagerFachNr                              );

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTIKELLAGERORT structure                 */
/*  to a pxArtStoreLoc object.                                                */
/*----------------------------------------------------------------------------*/
pxArtStoreLoc&
Assign
(
    pxArtStoreLoc&          dest,
    const tARTIKELLAGERORT& src
)
{
    // Copy native data types:
    dest.ArtikelNr_            = src.ArtikelNr;
    dest.FilialNr_             = src.FilialNr;
    dest.LagerBereichNr_       = src.LagerBereichNr;
    dest.DatumVerfall_         = src.DatumVerfall;
    dest.Bestand_              = src.Bestand;
    dest.VerbundArtikel_       = src.VerbundArtikel;

    // Strings:
    dest.StationNr_            = src.StationNr;
    dest.LagerFachNr_          = src.LagerFachNr;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtStoreLoc :: Init()
{
    tARTIKELLAGERORT record;
    memset(&record, 0 , sizeof(tARTIKELLAGERORT));
    Assign(*this, record);
}

int pxArtStoreLoc::Read(const void *record)
{
    return pxLagerortRead((tARTIKELLAGERORT*) record);
}

int pxArtStoreLoc::ReadLock(const void *record)
{
    return pxLagerortReadLock((tARTIKELLAGERORT*) record);
}

int pxArtStoreLoc::Update(const void *record)
{
    return pxLagerortUpdate((tARTIKELLAGERORT*)record);
}

int pxArtStoreLoc::Insert(const void *record)
{
    return pxLagerortInsert((tARTIKELLAGERORT*)record);
}

int pxArtStoreLoc::Delete(const void *record)
{
    return pxLagerortDelete((tARTIKELLAGERORT*)record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tARTIKELLAGERORT    */
/*  structure and then imported to self.                                      */
/*----------------------------------------------------------------------------*/
pxArtStoreLoc&
pxArtStoreLoc :: operator=( const pxArtStoreLoc& src)
{
    tARTIKELLAGERORT record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTIKELLAGERORT struct 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxArtStoreLoc&
pxArtStoreLoc :: operator=( const tARTIKELLAGERORT& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Set quantity q from quantity on hand. Returns quantity set  .             */
/*----------------------------------------------------------------------------*/
long
pxArtStoreLoc :: SetQuantity
(
    const long q
)
{
    Bestand_ = q;
    SetDirty();
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Add quantity q from quantity on hand. Returns quantity added.             */
/*----------------------------------------------------------------------------*/
long
pxArtStoreLoc :: AddQuantity
(
    const long q
)
{
    Bestand_ += q;
    SetDirty();
    return q;
}
/*----------------------------------------------------------------------------*/
/*  Subtract quantity q from quantity on hand. Returns quantity subtracted.   */
/*----------------------------------------------------------------------------*/
long
pxArtStoreLoc :: SubQuantity
(
    const long q                      // quantity to be subtracted
)
{
    long retval;
    // avoid negative values in stock:
    retval = ( Bestand_ - q < 0 ) ? Bestand_ : q;
    Bestand_ -= retval;
    SetDirty();
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtStoreLoc :: Get
(
    DBAccessMode mode
)
{
    if ( pxGlobalNoDatabaseWrite)
       pxGlobalNoWriteToLog = true;

    tARTIKELLAGERORT record;
    memset(&record, 0, sizeof(tARTIKELLAGERORT));
    record.ArtikelNr        = ArtikelNr_;
    record.FilialNr         = FilialNr_;
    record.LagerBereichNr   = LagerBereichNr_;
    record.LagerFachNr[0]   = ' ';
    LagerFachNr_.GetData(record.LagerFachNr);
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record)
                                               : nDBRead(&record);
    if (!retval)
       (*this)= record;          // import the data from tARTIKELLAGERORT struct
    else if ( retval > cDBXR_NORMAL )
       DBCondition(nMessage(CMsgStream(),
                            CMSG_ART_STORELOC_NOTFOUND,
                            ArtikelNr_,
                            FilialNr_,
                            LagerBereichNr_,
                            record.LagerFachNr),
                   CMSG_ART_STORELOC_NOTFOUND);

    pxGlobalNoWriteToLog = false;
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArtStoreLoc :: Put
(
)
{
    tARTIKELLAGERORT record;
    memset(&record, 0, sizeof(tARTIKELLAGERORT) );
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTIKELLAGERORT));
}

/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxArtStoreLoc :: Delete
(
)
{
    tARTIKELLAGERORT record;
    memset(&record, 0, sizeof(tARTIKELLAGERORT) );
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtStoreLoc list objects being inserted in the following        */
/*  ascending sequence: ArtikelNr, FilialNr.                                  */
/*----------------------------------------------------------------------------*/
int
pxArtStoreLoc :: CompareTo
(
    const nCollectable   *That,
          void           * /*p*/,
    const long           /*lparm*/
)   const
{
    pxArtStoreLoc *that = (pxArtStoreLoc*) That;
    int retval;

    retval = (ArtikelNr_ == that->ArtikelNr_) ? 0
             : (ArtikelNr_ > that->ArtikelNr_ ? 1 : -1);

    if (retval == 0)
    {
       retval = (FilialNr_ == that->FilialNr_) ? 0
                : (FilialNr_ > that->FilialNr_ ? 1 : -1);
    }
    return retval;
}
