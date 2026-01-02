#include <pxdbxx.h>
#include <nntypes.h>
#include "pxsess.hpp"
#include "pxartdsp.hpp"
#include "types/messagecodeenum.inc"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArtDispo :: pxArtDispo
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
pxArtDispo :: pxArtDispo
(
    pxArtDispo& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tDISPOARTIKEL structure to construct this instance.                   */
/*----------------------------------------------------------------------------*/
pxArtDispo :: pxArtDispo
(
    pxSession   *session,
    tDISPOARTIKEL& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Read constructors.                                                        */
/*----------------------------------------------------------------------------*/
pxArtDispo :: pxArtDispo
(
    pxSession *session,
    long     KdAuftragNr,
    long     PosNr,
    DBAccessMode mode
)
    : pxDBRecord(session)
{
    Init();
    KdAuftragNr_ = KdAuftragNr;
    PosNr_       = PosNr;
    Get(mode);
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArtDispo :: ~pxArtDispo()
{
 //   delete subobjects;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tDISPOARTIKEL structure.       */
/*----------------------------------------------------------------------------*/
tDISPOARTIKEL&
Assign
(
    tDISPOARTIKEL&     dest,
    const pxArtDispo&  src
)
{
    dest.KdAuftragNr    =  src.KdAuftragNr_;
    dest.PosNr          =  src.PosNr_;
    dest.PreisEKApo     =  src.PreisEKApo_;
    dest.PreisEKGrosso  =  src.PreisEKGrosso_;
    dest.RabattFestDM   =  src.RabattFestDM_;
    dest.RabattFest     =  src.RabattFest_;
    dest.GebuehrBearb   =  src.GebuehrBearb_;
    dest.UrsprungAuftragnr =  src.UrsprungAuftragnr_;
    dest.UrsprungPosnr  =  src.UrsprungPosnr_;
    dest.TaxLevel       =  src.TaxLevel_;
    dest.NetPrice       =  src.NetPrice_;
    dest.Service_No     =  src.Service_No_;

    dest.Bezeichnung[0]  = ' ';
    src.Bezeichnung_.GetData(dest.Bezeichnung,(mSIZEOF(tDISPOARTIKEL,Bezeichnung))-1);
    dest.Darreichform[0] = ' ';
    src.Darreichform_.GetData(dest.Darreichform,(mSIZEOF(tDISPOARTIKEL,Darreichform))-1);
    dest.Einheit[0]      = ' ';
    src.Einheit_.GetData(dest.Einheit,(mSIZEOF(tDISPOARTIKEL,Einheit))-1);
    dest.Rabattfaehig[0] = ' ';
    src.Rabattfaehig_.GetData(dest.Rabattfaehig,(mSIZEOF(tDISPOARTIKEL,Rabattfaehig))-1);
    dest.WarenGruppeEigen[0]  = ' ';
    src.WarenGruppeEigen_.GetData(dest.WarenGruppeEigen,(mSIZEOF(tDISPOARTIKEL,WarenGruppeEigen))-1);

    // Bit Map Exporting:
    src.ETArtSchalter_.Export(dest.ETArtSchalter1, dest.ETArtSchalter2,
                              dest.ETArtSchalter3, dest.ETArtSchalter4,
                              dest.ETArtSchalter5);

    src.ETArtKlasse_.Export(dest.ETArtKlasse1, dest.ETArtKlasse2);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tDISPOARTIKEL structure to a pxArtDispo    */
/*  object.                                                                   */
/*----------------------------------------------------------------------------*/
pxArtDispo&
Assign
(
    pxArtDispo&        dest,
    const tDISPOARTIKEL&   src
)
{
    dest.KdAuftragNr_   =  src.KdAuftragNr;
    dest.PosNr_         =  src.PosNr;
    dest.Darreichform_  =  src.Darreichform;
    dest.Darreichform_.Strip();
    dest.Einheit_       =  src.Einheit;
    dest.Einheit_.Strip();
    dest.Bezeichnung_   =  src.Bezeichnung;
    dest.Bezeichnung_.Strip();

    dest.PreisEKApo_    =  src.PreisEKApo;
    dest.PreisEKGrosso_ =  src.PreisEKGrosso;
    dest.RabattFestDM_  =  src.RabattFestDM;
    dest.RabattFest_    =  src.RabattFest;
    dest.Rabattfaehig_  =  src.Rabattfaehig;
    dest.WarenGruppeEigen_  =  src.WarenGruppeEigen;
    dest.GebuehrBearb_   =  src.GebuehrBearb;
    dest.UrsprungAuftragnr_ =  src.UrsprungAuftragnr;
    dest.UrsprungPosnr_ =  src.UrsprungPosnr;
    dest.TaxLevel_      =  src.TaxLevel;
    dest.NetPrice_      =  src.NetPrice;
    dest.Service_No_    =  src.Service_No;

    // Bit Map Importing:
    dest.ETArtSchalter_.Import(src.ETArtSchalter1, src.ETArtSchalter2,
                               src.ETArtSchalter3, src.ETArtSchalter4,
                               src.ETArtSchalter5);
    dest.ETArtKlasse_.Import(src.ETArtKlasse1, src.ETArtKlasse2);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArtDispo :: Init()
{
    tDISPOARTIKEL    record;
    memset(&record, 0 , sizeof(tDISPOARTIKEL));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the tDISPOARTIKEL struct*/
/*  and then imported to self.                                                */
/*----------------------------------------------------------------------------*/
pxArtDispo&
pxArtDispo :: operator=( const pxArtDispo& src)
{
    tDISPOARTIKEL    record;                 // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDISPOARTIKEL structure 'src' to this instance.  */
/*----------------------------------------------------------------------------*/
pxArtDispo&
pxArtDispo :: operator=( const tDISPOARTIKEL& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tDISPOITEM structure 'src' to this instance.     */
/*----------------------------------------------------------------------------*/
pxArtDispo&
pxArtDispo :: operator=( const tDISPOITEM& src)
{
    Darreichform_  = src.Darreichform;
    Einheit_       = src.Einheit;
    Bezeichnung_   = src.Bezeichnung;

    PreisEKApo_    = src.PreisEKApo;
    PreisEKGrosso_ = src.PreisEKGrosso;
    RabattFestDM_  = src.RabattFestDM;
    RabattFest_    = src.RabattFest;
    WarenGruppeEigen_ = src.WarenGruppeEigen;
    GebuehrBearb_  = src.GebuehrBearb;
    UrsprungAuftragnr_ = src.UrsprungAuftragnr;
    UrsprungPosnr_ = src.UrsprungPosnr;

    ArtFlags().ClearErmaessigtMwst();
    ArtClass().ClearTaxPflichtig();
    if ( src.MWSTSchluessel == HALFTAX )
        ArtFlags().SetErmaessigtMwst();
    if ( src.TaxPflichtig )
        ArtClass().SetTaxPflichtig();
    if ( src.Rabattfaehig )
        Rabattfaehig_ = "00";
    else
        Rabattfaehig_ = "01";

    SetDirty();
    TaxLevel_        =   static_cast<short>(src.MWSTSchluessel);
    NetPrice_        =   src.NetPrice;
    Service_No_      =   src.Service_No;
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArtDispo :: Get
(
    DBAccessMode mode
)
{
    tDISPOARTIKEL record;
    memset(&record, 0, sizeof(tDISPOARTIKEL));
    record.KdAuftragNr = KdAuftragNr_;
    record.PosNr = PosNr_;
    int retval = ( mode == cDBGET_FORUPDATE ) ? nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
        (*this)= record;                 // import the data from tDISPOARTIKEL struct
    else if ( retval > cDBXR_NORMAL )
        DBCondition(nMessage(CMsgStream(), CMSG_ITM_DISPOART_NOTFOUND, PosNr_, KdAuftragNr_), CMSG_ITM_DISPOART_NOTFOUND);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArtDispo :: Put
(
)
{
    tDISPOARTIKEL record;
    memset(&record, 0, sizeof(tDISPOARTIKEL));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tDISPOARTIKEL));
}

/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxArtDispo :: Delete
(
)
{
    tDISPOARTIKEL record;
    memset(&record, 0, sizeof(tDISPOARTIKEL));
    Assign(record, *this);
    return Delete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArtDispo :: Read
(
    const void  *record
)
{
    return pxDispoArtikelRead((tDISPOARTIKEL*)record);
}

int
pxArtDispo :: ReadLock
(
    const void  *record
)
{
    return pxDispoArtikelReadLock((tDISPOARTIKEL*)record);
}

int
pxArtDispo :: Update
(
    const void  *record
)
{
    return pxDispoArtikelUpdate((tDISPOARTIKEL*)record);
}

int
pxArtDispo :: Insert
(
    const void  *record
)
{
    return pxDispoArtikelInsert((tDISPOARTIKEL*)record);
}
int
pxArtDispo :: Delete
(
    const void  *record
)
{
    return pxDispoArtikelDelete((tDISPOARTIKEL*)record);
}

/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxArtDispo list objects being inserted in the following ascending  */
/*  sequence:    Bezeichnung, PackGroesse, Darreichform.                      */
/*----------------------------------------------------------------------------*/
int
pxArtDispo :: CompareTo
(
    const nCollectable   *That,
          void           * /*p*/,
    const long           /*lparm*/
)   const
{
    pxArtDispo *that = (pxArtDispo*)That;
    int retval;
    retval = (KdAuftragNr_ == that->KdAuftragNr_) ? 0
           : (KdAuftragNr_ > that->KdAuftragNr_ ? 1 : -1);
    if ( retval == 0 )
    {
        retval = (PosNr_ == that->PosNr_) ? 0
               : (PosNr_ > that->PosNr_ ? 1 : -1);
    }
    return retval;
}

bool
pxArtDispo :: SetOrder
(
    long KdAuftragNr,
    long PosNr
)
{
    KdAuftragNr_ = KdAuftragNr;
    PosNr_ = PosNr;

    return KdAuftragNr_ == KdAuftragNr && PosNr_ == PosNr;
}

void
pxArtDispo :: DispoGet
(
    tDISPOITEM& s
)
{
    s.Darreichform    = Darreichform_ ;
    s.Einheit         = Einheit_      ;
    s.Bezeichnung     = Bezeichnung_  ;

    s.PreisEKApo      = PreisEKApo_   ;
    s.PreisEKGrosso   = PreisEKGrosso_;
    s.RabattFestDM    = RabattFestDM_ ;
    s.RabattFest      = RabattFest_   ;

    //s.MWSTSchluessel = (ArtFlags().IsErmaessigtMwst()) ? HALFTAX : FULLTAX;
    s.TaxPflichtig = ArtClass().IsTaxPflichtig() ? 1 : 0;
    s.Rabattfaehig = Rabattfaehig_ == nString("00");
    s.WarenGruppeEigen = WarenGruppeEigen_;

    s.GebuehrBearb  = GebuehrBearb_;
    s.UrsprungAuftragnr = UrsprungAuftragnr_;
    s.UrsprungPosnr = UrsprungPosnr_;
    s.MWSTSchluessel = static_cast<pxMWSTSchluessel>(TaxLevel_);
    s.NetPrice       = NetPrice_;
    s.Service_No     = Service_No_;
}

/*----------------------------------------------------------------------------*/
/*  The list functions.                                                       */
/*----------------------------------------------------------------------------*/
pxArtDispoList :: pxArtDispoList
(
    pxSession   *session
)
    : nDBRecordSet(session)
{
    nDBSetList(this);
}

/*----------------------------------------------------------------------------*/
/*  Initialize selection using the customer order number.                     */
/*----------------------------------------------------------------------------*/
size_t
pxArtDispoList :: Select
(
    const long    KdAuftragNr,
    const int     count_                // Max number of records to read
)
{
    tDISPOARTIKEL a;
    memset(&a, 0, sizeof(tDISPOARTIKEL));     // zero out entire record buffer
    a.KdAuftragNr = KdAuftragNr;
    return Select(&a, count_);
}

/*----------------------------------------------------------------------------*/
/*  Do the selection based upon the values stored in a tDISPOARTIKEL struc.   */
/*  Note that unused search criteria must have the appropiate default values, */
/*  i.e. '\0' for a string value, 0 for an integer etc.                       */
/*----------------------------------------------------------------------------*/
size_t
pxArtDispoList :: Select
(
          tDISPOARTIKEL  *recp,
    const int           count_
)
{
    // Set the cursor id:
    int cursorid = cCRS_DEFAULT;
    nDBSelect(recp, cursorid, count_);
    return Entries();
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from nDBRecordSet.                   */
/*----------------------------------------------------------------------------*/
nCollectable*
pxArtDispoList :: AddToList
(
    const void  *record,
    const int  /* row */
)
{
    // construct new object:
    pxArtDispo *objectp = new pxArtDispo(Session(), *(tDISPOARTIKEL*) record);
    InsertAscending(objectp);
    return objectp;
}

int
pxArtDispoList :: EndBrowse
(
    const int  cursorid
)
{
    return pxDispoArtikelEndBrowse(cursorid);
}


int
pxArtDispoList :: GetNext
(
    const void  *record,
    const int  cursorid
)
{
    return pxDispoArtikelGetNext((tDISPOARTIKEL*)record, cursorid);
}

int
pxArtDispoList :: StartBrowse
(
    const void  *keys,
    const int  cursorid
)
{
    return pxDispoArtikelStartBrowse((tDISPOARTIKEL*)keys, cursorid);
}
