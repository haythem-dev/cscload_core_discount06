#include "pxartrem.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArtRemote :: pxArtRemote
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Read constructor                                                          */
/*----------------------------------------------------------------------------*/
pxArtRemote :: pxArtRemote
(
    pxSession   *session,
    long    ArtikelNrL,                // Read via this type
    short   FilialNr,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    ArtikelNr_ = ArtikelNrL;
    FilialNr_  = FilialNr;
    DBName_ = Session()->getDatabaseName(FilialNr_).c_str();
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArtRemote :: pxArtRemote
(
    pxArtRemote& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtRemote :: ~pxArtRemote()
{
// delete subobjects
}


/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArtRemote :: Put
(
)

{
    tFARTIKEL record;
    // record is prefilled by master article
    memset(&record, 0, sizeof(tFARTIKEL));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tFARTIKEL));
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tFARTIKEL structure.            */
/*----------------------------------------------------------------------------*/
tFARTIKEL&
Assign
(
    tFARTIKEL&         dest,
    const pxArtRemote&  src
)
{
    dest.ArtikelNr             = src.ArtikelNr_;
    dest.Bestand               = src.Bestand_;
//    dest.BestandReserviert     = src.BestandReserviert_;
    dest.FilialNr              = src.FilialNr_;
    dest.Artikelaktiv          = src.Artikelaktiv_;
//    dest.VerbundArtikel        = src.VerbundArtikel_;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tFARTIKEL structure to a pxArtremote object.*/
/*----------------------------------------------------------------------------*/
pxArtRemote&
Assign
(
    pxArtRemote&        dest,
    const tFARTIKEL&   src
)
{

    dest.ArtikelNr_            = src.ArtikelNr;
    dest.Bestand_              = src.Bestand;
//    dest.BestandReserviert_    = src.BestandReserviert;
    dest.FilialNr_             = src.FilialNr;
// avoid negative value
    dest.Bestand_ = ( (dest.Bestand_ < 0) ? 0 : dest.Bestand_ );
    dest.Artikelaktiv_         = src.Artikelaktiv;
//    dest.VerbundArtikel_       = src.VerbundArtikel;
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtRemote :: Init()
{
    tFARTIKEL    record;
    memset(&record, 0 , sizeof(tFARTIKEL));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tFARTIKEL struct     */
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxArtRemote&
pxArtRemote :: operator=( const pxArtRemote& src)
{
    tFARTIKEL    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tFARTIKEL structure 'src' to this instance.       */
/*----------------------------------------------------------------------------*/
pxArtRemote&
pxArtRemote :: operator=( const tFARTIKEL& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Subtract quantity q from quantity on hand. Returns quantity subtracted.   */
/*----------------------------------------------------------------------------*/
long
pxArtRemote :: SubQuantity
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
/*  Add quantity q from quantity on hand. Returns quantity added.             */
/*----------------------------------------------------------------------------*/
long
pxArtRemote :: AddQuantity
(
    const long q
)
{
    Bestand_ += q;
    SetDirty();
    return q;
}

/*----------------------------------------------------------------------------*/
/*  set quantity q from quantity on hand. Returns quantity added.             */
/*----------------------------------------------------------------------------*/
long
pxArtRemote :: SetQuantity
(
    const long q
)
{
    Bestand_ = q;
    SetDirty();
    return q;
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtRemote :: Get
(
    DBAccessMode mode
)

{
    tFARTIKEL record;
    memset(&record, 0, sizeof(tFARTIKEL));
    record.ArtikelNr = ArtikelNr_;
    record.FilialNr = FilialNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tFARTIKEL struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(), CMSG_ART_NOTFOUND, ArtikelNr_);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Get a record from the data source.                                        */
/*----------------------------------------------------------------------------*/

int
pxArtRemote :: Read
(
    const void *record
)
{
   if (!(DBName_.IsEmpty()))
   {
      return pxRArtikelRead((tFARTIKEL*)record, DBName_());
   }
   else
   {
      return ExternalCondition(CMsgStream(), CMSG_ART_REM_NOTFOUND, ArtikelNr_, DBName_());
   }
}
/*----------------------------------------------------------------------------*/
/*  Get a record from the data source.                                        */
/*----------------------------------------------------------------------------*/

int
pxArtRemote :: ReadLock
(
    const void *record
)
{
   if (!(DBName_.IsEmpty()))
   {
      return pxRArtikelReadLock((tFARTIKEL*)record, DBName_());
   }
   else
   {
      return ExternalCondition(CMsgStream(), CMSG_ART_REM_NOTFOUND, ArtikelNr_, DBName_());
   }
}

/*----------------------------------------------------------------------------*/
/*  Update a record in the data source.                                       */
/*----------------------------------------------------------------------------*/

int
pxArtRemote :: Update
(
    const void *record
)
{
 	if (!(DBName_.IsEmpty()))
 	{
		return pxRArtikelUpdate((tFARTIKEL*)record, DBName_());
	}
	else
	{
		return ExternalCondition(CMsgStream(), CMSG_ART_REM_NOTFOUND, ArtikelNr_, DBName_());
	}
}
