#include "pxartalt.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxArtAltern :: pxArtAltern
(
)
{
    Init();
}

pxArtAltern :: pxArtAltern
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
pxArtAltern :: pxArtAltern
(
    pxArtAltern& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTIKELALTERN structure to construct this instance.                  */
/*----------------------------------------------------------------------------*/
pxArtAltern :: pxArtAltern
(
    pxSession   *session,
    tARTIKELALTERN& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxArtAltern :: pxArtAltern
(
    pxSession   *session,
    long ArtikelNr,
    long ArtikelAlternNr,
    short FilialNr,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    ArtikelNr_ = ArtikelNr;
    ArtikelAlternNr_ = ArtikelAlternNr;
        FilialNr_  = FilialNr;
    Get(mode);
}


/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtAltern :: ~pxArtAltern()
{
//  delete subobjects;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTIKELALTERN structure.      */
/*----------------------------------------------------------------------------*/
tARTIKELALTERN&
Assign
(
          tARTIKELALTERN&   dest,
    const pxArtAltern&      src
)
{
    // Copy native data types:
    dest.ArtikelNr       = src.ArtikelNr_;
    dest.ArtikelAlternNr = src.ArtikelAlternNr_;
    dest.FilialNr        = src.FilialNr_;

    // nStrings:
    dest.Bemerkungen[0]  = ' ';
    src.Bemerkungen_.GetData(dest.Bemerkungen);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTIKELALTERN structure                         */
/*  to a pxArtAltern object.                                                  */
/*----------------------------------------------------------------------------*/
pxArtAltern&
Assign
(
          pxArtAltern&      dest,
    const tARTIKELALTERN&   src
)
{
    // Copy native data types:
    dest.ArtikelNr_         = src.ArtikelNr;
    dest.ArtikelAlternNr_   = src.ArtikelAlternNr;
    dest.FilialNr_          = src.FilialNr;

    // Strings:
    dest.Bemerkungen_       = src.Bemerkungen;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtAltern :: Init()
{
    tARTIKELALTERN    record;
    memset(&record, 0 , sizeof(tARTIKELALTERN));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTIKELALTERN struct and then imported to self.                          */
/*----------------------------------------------------------------------------*/
pxArtAltern&
pxArtAltern :: operator=( const pxArtAltern& src)
{
    tARTIKELALTERN record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTIKELALTERN structure to this instance.       */
/*----------------------------------------------------------------------------*/
pxArtAltern&
pxArtAltern :: operator=( const tARTIKELALTERN& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtAltern :: Get
(
    DBAccessMode mode
)

{
    tARTIKELALTERN record;
    memset(&record, 0, sizeof(tARTIKELALTERN));
    record.ArtikelNr = ArtikelNr_;
    record.ArtikelAlternNr = ArtikelAlternNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                         nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;           // import the data from tARTIKELALTERN struct
    else if ( retval > cDBXR_NORMAL )
       DBCondition(nMessage(CMsgStream(),
                            CMSG_ART_ALTERN_NOTFOUND,
                            record.ArtikelNr,
                            record.ArtikelAlternNr),
                   CMSG_ART_ALTERN_NOTFOUND);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArtAltern :: Put
(
)
{
    tARTIKELALTERN record;
    memset(&record, 0, sizeof(tARTIKELALTERN));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTIKELALTERN));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArtAltern :: Read
(
    const void  *record
)
{
    return pxArtikelAlternRead((tARTIKELALTERN*)record);
}

int
pxArtAltern :: ReadLock
(
    const void  *record
)
{
    return pxArtikelAlternReadLock((tARTIKELALTERN*)record);
}

int
pxArtAltern :: Update
(
    const void  *record
)
{
    return pxArtikelAlternUpdate((tARTIKELALTERN*)record);
}

int
pxArtAltern :: Insert
(
    const void  *record
)
{
    return pxArtikelAlternInsert((tARTIKELALTERN*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable. Ensures pxArtBase list    */
/*  objects being inserted in the following ascending sequence: KdGruppe.     */
/*----------------------------------------------------------------------------*/
int
pxArtAltern :: CompareTo
(
    const nCollectable   *That,
          void           * /*p*/,
    const long           /*lparm*/
)   const
{
    pxArtAltern *that = (pxArtAltern*)That;
    int retval;

    retval = (ArtikelNr_ == that->ArtikelNr_) ? 0
             : (ArtikelNr_ < that->ArtikelNr_ ? -1 : 1);
    if (retval == 0)
    {
       retval = (ArtikelAlternNr_ == that->ArtikelAlternNr_) ? 0
                : (ArtikelAlternNr_ < that->ArtikelAlternNr_ ? -1 : 1);
    }

    return retval;
}
