#include "pxartprc.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Default constructor.                                                      */
/*----------------------------------------------------------------------------*/
pxArtPrice :: pxArtPrice()
{
    Init();
}

pxArtPrice :: pxArtPrice
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
pxArtPrice :: pxArtPrice
(
    pxArtPrice& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTIKELPREIS structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxArtPrice :: pxArtPrice
(
    pxSession   *session,
    tARTIKELPREIS& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtPrice :: pxArtPrice
(
    pxSession   *session,
    long    ArtikelNrL,                // Read via this type
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    ArtikelNr_ = ArtikelNrL;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtPrice :: ~pxArtPrice()
{
 //   delete subobjects;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTIKELPREIS structure.       */
/*----------------------------------------------------------------------------*/
tARTIKELPREIS&
Assign
(
    tARTIKELPREIS&     dest,
    const pxArtPrice&  src
)
{
    dest.RabattFestDM       = 0;

    dest.ArtikelNr          = src.ArtikelNr_;
    dest.DatumGueltigAb     = src.DatumGueltigAb_.GetYYYYMMDD();
    dest.DatumGueltigBis    = src.DatumGueltigBis_.GetYYYYMMDD();
    dest.PreisEKApo         = src.PreisEKApo_;
    dest.PreisVKApo         = src.PreisVKApo_;
    dest.PreisEKGrosso      = src.PreisEKGrosso_;
    dest.PreisEKGrossoNA    = src.PreisEKGrossoNA_;
    dest.RabattFest         = src.RabattFest_;

    dest.PreisFest          = src.PreisFest_;
    dest.PreisProzent       = src.PreisProzent_;
    dest.PreisAGP           = src.PreisAGP_;
    dest.Preis_Typ          = static_cast<short>(src.Preis_Typ_);
    dest.MaxAvp             = src.MaxAvp_;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTIKELPREIS structure to a pxArtPrice    */
/*  object.                                                                   */
/*----------------------------------------------------------------------------*/
pxArtPrice&
Assign
(
    pxArtPrice&          dest,
    const tARTIKELPREIS& src
)
{
    dest.ArtikelNr_         = src.ArtikelNr;
    dest.DatumGueltigAb_    = nDate(src.DatumGueltigAb);
    dest.DatumGueltigBis_   = nDate(src.DatumGueltigBis);
    dest.PreisEKApo_        = src.PreisEKApo;
    dest.PreisVKApo_        = src.PreisVKApo;
    dest.PreisEKGrosso_     = src.PreisEKGrosso;
    dest.PreisEKGrossoNA_   = src.PreisEKGrossoNA;
    dest.RabattFest_        = src.RabattFest;

    dest.PreisFest_         = src.PreisFest;
    dest.PreisProzent_      = src.PreisProzent;
    dest.PreisAGP_          = src.PreisAGP;
    dest.Preis_Typ_         = static_cast<PriceTypeEnum>(src.Preis_Typ);
    dest.MaxAvp_            = src.MaxAvp;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtPrice :: Init()
{
    tARTIKELPREIS    record;
    memset(&record, 0 , sizeof(tARTIKELPREIS));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tARTIKELPREIS struct*/
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxArtPrice&
pxArtPrice :: operator=( const pxArtPrice& src)
{
    tARTIKELPREIS    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTIKELPREIS structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxArtPrice&
pxArtPrice :: operator=( const tARTIKELPREIS& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtPrice :: Get
(
    DBAccessMode mode
)

{
    tARTIKELPREIS record;
    memset(&record, 0, sizeof(tARTIKELPREIS));
    Assign(record, *this);              // resolve keys
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tARTIKELPREIS struct
    else if ( retval > cDBXR_NORMAL )
       DBCondition(nMessage(CMsgStream(), CMSG_ART_NOBASEPRICES,
                   ArtikelNr_),retval);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArtPrice :: Put
(
)

{
    tARTIKELPREIS record;
    memset(&record, 0, sizeof(tARTIKELPREIS));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTIKELPREIS));
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArtPrice :: Read
(
    const void  *record
)
{
    return pxArtikelpreisRead((tARTIKELPREIS*)record);
}

int
pxArtPrice :: ReadLock
(
    const void  *record
)
{
    return pxArtikelpreisReadLock((tARTIKELPREIS*)record);
}

int
pxArtPrice :: Update
(
    const void  *record
)
{
    return pxArtikelpreisUpdate((tARTIKELPREIS*)record);
}

int
pxArtPrice :: Insert
(
    const void  *record
)
{

    return pxArtikelpreisInsert((tARTIKELPREIS*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtPrice list objects being inserted in the following ascending */
/*  sequence:    ArtikelNr, DatumGueltigAb, DatumGueltigBis.                  */
/*----------------------------------------------------------------------------*/
int
pxArtPrice :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxArtPrice *that = (pxArtPrice*)That;
    int retval = (ArtikelNr_ == that->ArtikelNr_) ? 0
                  : (ArtikelNr_ > that->ArtikelNr_ ? 1 : -1);

    if ( retval == 0 )               // then ArtikelNr ==
        retval = (DatumGueltigAb_ == that->DatumGueltigAb_) ? 0
                  : (DatumGueltigAb_ > that->DatumGueltigAb_ ? 1 : -1);

    if ( retval == 0 )               // then ArtikelNr ==
        retval = (DatumGueltigBis_ == that->DatumGueltigBis_) ? 0
                  : (DatumGueltigBis_ > that->DatumGueltigBis_ ? 1 : -1);

    return retval;
}
