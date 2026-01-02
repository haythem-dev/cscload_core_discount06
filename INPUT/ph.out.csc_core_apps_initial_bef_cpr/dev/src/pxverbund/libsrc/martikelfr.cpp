#include "pxartmasfr.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"
#include "types/messagecodeenum.inc"

extern bool pxGlobalNoDatabaseWrite;
extern bool pxGlobalNoWriteToLog;

/*----------------------------------------------------------------------------*/
/*  Put this object into record.                                              */
/*----------------------------------------------------------------------------*/
int
pxArtMasterFr  :: Put
(
)
{
    tMARTIKELFR record;
    memset(&record, 0, sizeof(tMARTIKELFR));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tMARTIKELFR));
}
/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtBase list objects being inserted in the following ascending  */
/*  sequence:    Bezeichnung, PackGroesse, Darreichform.                      */
/*----------------------------------------------------------------------------*/
int
pxArtMasterFr :: CompareTo
(
    const nCollectable   *That,
          void           * /* p */,
    const long           /* lparm */
)   const
{
    pxArtMasterFr *that = (pxArtMasterFr*)That;
    int retval;
    if ( (retval = Bezeichnung_.Compare(that->Bezeichnung_) ) == 0 )
    {                                   // then Bezeichnung ==
       retval = Darreichform_.Compare(that->Darreichform_);
    }
    return retval;
}


/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArtMasterFr  :: pxArtMasterFr
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtMasterFr  :: Init()
{
    tMARTIKELFR    record;
    memset(&record, 0 , sizeof(tMARTIKELFR));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtMasterFr  :: Get
(
    DBAccessMode mode
)

{
    if ( pxGlobalNoDatabaseWrite)
       pxGlobalNoWriteToLog = true;

    tMARTIKELFR record;
    memset(&record, 0, sizeof(tMARTIKELFR));
    record.ArtikelNr = ArtikelNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;                 // import the data from tARTIKEL struct
    else if ( retval > cDBXR_NORMAL )
       ExternalCondition(CMsgStream(), CMSG_ART_NOTFOUND, ArtikelNr_);

    pxGlobalNoWriteToLog = false;
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtMasterFr  :: ~pxArtMasterFr()
{
// delete subobjects
   ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tMARTIKELFR structure.         */
/*----------------------------------------------------------------------------*/
tMARTIKELFR&
Assign
(
    tMARTIKELFR&         dest,
    const pxArtMasterFr&  src
)
{
// Copy native data types:
    dest.ArtikelNr             = src.ArtikelNr_;


// Strings:
    dest.MatchCode[0]          = ' ';
    src.MatchCode_.GetData     (dest.MatchCode      );
    dest.Bezeichnung[0]        = ' ';
    src.Bezeichnung_.GetData   (dest.Bezeichnung    );
    dest.Darreichform[0]       = ' ';
    src.Darreichform_.GetData  (dest.Darreichform   );
    dest.Einheit[0]            = ' ';
    src.Einheit_.GetData       (dest.Einheit        );
    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tMARTIKELFR structure to a pxArtBase object*/
/*----------------------------------------------------------------------------*/
pxArtMasterFr&
Assign
(
    pxArtMasterFr&        dest,
    const tMARTIKELFR&   src
)
{

    dest.ArtikelNr_            = src.ArtikelNr;
    dest.MatchCode_            = src.MatchCode;
    dest.Bezeichnung_          = src.Bezeichnung;
    dest.Darreichform_         = src.Darreichform;
    dest.Einheit_              = src.Einheit;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tARTIKEL struct     */
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxArtMasterFr&
pxArtMasterFr :: operator=( const pxArtMasterFr& src)
{
    tMARTIKELFR    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTIKEL structure 'src' to this instance.       */
/*----------------------------------------------------------------------------*/
pxArtMasterFr&
pxArtMasterFr :: operator=( const tMARTIKELFR& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxArtMasterFr :: pxArtMasterFr
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

int pxArtMasterFr::Read(const void *record)
{
    return pxArMasterFrRead((tMARTIKELFR*)record);
}

int pxArtMasterFr::ReadLock(const void *record)
{
    return pxArMasterFrReadLock((tMARTIKELFR*)record);
}

int pxArtMasterFr::Insert(const void *record)
{
    return pxArMasterFrInsert((tMARTIKELFR*)record);
}

int pxArtMasterFr::Update(const void *record)
{
    return pxArMasterFrUpdate((tMARTIKELFR*)record);
}
